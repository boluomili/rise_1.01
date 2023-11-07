/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#include "control/BalanceCtrl.h"
#include "common/mathTools.h"
#include "common/timeMarker.h"

BalanceCtrl::BalanceCtrl(double mass, Mat3 Ib, Mat6 S, double alpha, double beta)
            : _mass(mass), _Ib(Ib), _S(S), _alpha(alpha), _beta(beta){
    _Fprev.setZero();
    _g << 0, 0, -9.81;
    _fricRatio = 0.3;
    _fricMat <<  1,  0, _fricRatio,
                -1,  0, _fricRatio,
                 0,  1, _fricRatio,
                 0, -1, _fricRatio,
                 0,  0, 1;//摩擦约束矩阵 5X3
}

BalanceCtrl::BalanceCtrl(QuadrupedRobot *robModel){
    Vec6 s;
    Vec12 w, u;

    _mass = robModel->getRobMass();
    _pcb = robModel->getPcb();
    _Ib = robModel->getRobInertial();
    _g << 0, 0, -9.81;

    w << 10, 10, 4, 10, 10, 4, 10, 10, 4, 10, 10, 4;//足端力权重
    u << 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3;//降低足端力前后突变的权重
    _alpha = 0.001;//权重w的系数
    _beta  = 0.1;//权重u的系数
    _fricRatio = 0.4;//地面与足端的静摩擦系数

    s << 20, 20, 50, 450, 450, 450; //动力学方程的权重

    _S = s.asDiagonal();//动力学方程的权重矩阵
    _W = w.asDiagonal();//足端力权重矩阵
    _U = u.asDiagonal();//降低足端力前后突变的权重矩阵
    
    _Fprev.setZero();
    _fricMat <<  1,  0, _fricRatio,
                -1,  0, _fricRatio,
                 0,  1, _fricRatio,
                 0, -1, _fricRatio,
                 0,  0, 1;//摩擦约束矩阵 5X3
}
//求解机器人动力学方程，得到优化后的足端力
Vec34 BalanceCtrl::calF(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, Vec34 feetPos2B, VecInt4 contact){
    calMatrixA(feetPos2B, rotM, contact);//feetPos2B是世界坐标系{s}下各个足端到机身几何中心的位置向量，对应(8.34)中的Pg0、Pg1、Pg2、Pg3
    calVectorBd(ddPcd, dWbd, rotM);//机身目标加速度、机身目标角加速度、机身当前姿态
    calConstraints(contact);//四个足端与地面接触状态
    //对应式（8.36）
    _G = _A.transpose()*_S*_A + _alpha*_W + _beta*_U;
    _g0T = -_bd.transpose()*_S*_A - _beta*_Fprev.transpose()*_U;

    solveQP();

    _Fprev = _F;
    return vec12ToVec34(_F);
}
Vec34 BalanceCtrl::calF(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, Vec34 feetPos2B, VecInt4 contact, double _mp, Vec3 _hatF){
    calMatrixA(feetPos2B, rotM, contact);//feetPos2B是世界坐标系{s}下各个足端到机身几何中心的位置向量，对应(8.34)中的Pg0、Pg1、Pg2、Pg3
    calVectorBd(ddPcd, dWbd, rotM, _mp, _hatF);//机身目标加速度、机身目标角加速度、机身当前姿态
    calConstraints(contact);//四个足端与地面接触状态
    //对应式（8.36）
    _G = _A.transpose()*_S*_A + _alpha*_W + _beta*_U;
    _g0T = -_bd.transpose()*_S*_A - _beta*_Fprev.transpose()*_U;



    solveQP();

    _Fprev = _F;
    return vec12ToVec34(_F);
}
//建立A矩阵 对应式（8.34）
void BalanceCtrl::calMatrixA(Vec34 feetPos2B, RotMat rotM, VecInt4 contact){
    for(int i(0); i < 4; ++i){
        _A.block(0, 3*i, 3, 3) = I3;
        _A.block(3, 3*i, 3, 3) = skew(feetPos2B.col(i) - rotM*_pcb);
    }
}
//建立bd矩阵 对应式（8.34）
void BalanceCtrl::calVectorBd(Vec3 ddPcd, Vec3 dWbd, RotMat rotM){
    _bd.head(3) = _mass * (ddPcd - _g);
    _bd.tail(3) = (rotM * _Ib * rotM.transpose()) * dWbd;
    // std::cout<<"机器人转矩:"<<_bd.tail(3).transpose()<<std::endl;
    // std::cout<<"角加速度dWbd:"<<dWbd.transpose()<<std::endl;
}
void BalanceCtrl::calVectorBd(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, double _mp, Vec3 _hatF){
    //_bd.head(3) = _mass * (ddPcd - _g) - abs(_mp) * _g ;
    // _bd.head(3) = (_mass + _mp/9.81) * ddPcd - _mass *_g + Vec3(0 , 0, _mp);
    _bd.head(3) = _mass * (ddPcd - _g) + Vec3(0 , 0, _mp);  //？？？_mp是质量，但是前面乘出来是力相加在一起
    _bd.tail(3) = (rotM * _Ib * rotM.transpose()) * dWbd + _hatF;
    std::cout<<"力矩的值是："<<_bd.tail(3).transpose()<<std::endl;
    //_bd.tail(3) = _hatF;
    // std::cout<<"机器人转矩:"<<_bd.tail(3).transpose()<<std::endl;
    // std::cout<<"角加速度dWbd:"<<dWbd.transpose()<<std::endl;
    // std::cout<<"估计的转矩_hatd:"<<_hatd.transpose()<<std::endl;
}
//计算约束矩阵，需判断腿腾空（力等式约束）还是触地（摩擦锥不等式约束）对应式（8.37）（8.38）
void BalanceCtrl::calConstraints(VecInt4 contact){
    int contactLegNum = 0;
    for(int i(0); i<4; ++i){
        if(contact(i) == 1){
            contactLegNum += 1;
        }
    }

    _CI.resize(5*contactLegNum, 12);
    _ci0.resize(5*contactLegNum);
    _CE.resize(3*(4 - contactLegNum), 12);
    _ce0.resize(3*(4 - contactLegNum));

    _CI.setZero();
    _ci0.setZero();
    _CE.setZero();
    _ce0.setZero();

    int ceID = 0;
    int ciID = 0;
    for(int i(0); i<4; ++i){
        if(contact(i) == 1){
            _CI.block(5*ciID, 3*i, 5, 3) = _fricMat;
            ++ciID;
        }else{
            _CE.block(3*ceID, 3*i, 3, 3) = I3;
            ++ceID;
        }
    }
}
//QP求解二次规划问题  对应（8.30）（8.33）
void BalanceCtrl::solveQP(){
    int n = _F.size();
    int m = _ce0.size();
    int p = _ci0.size();

    G.resize(n, n);
    CE.resize(n, m);
    CI.resize(n, p);
    g0.resize(n);
    ce0.resize(m);
    ci0.resize(p);
    x.resize(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            G[i][j] = _G(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            CE[i][j] = (_CE.transpose())(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            CI[i][j] = (_CI.transpose())(i, j);
        }
    }

    for (int i = 0; i < n; ++i) {
        g0[i] = _g0T[i];
    }

    for (int i = 0; i < m; ++i) {
        ce0[i] = _ce0[i];
    }

    for (int i = 0; i < p; ++i) {
        ci0[i] = _ci0[i];
    }

    double value = solve_quadprog(G, g0, CE, ce0, CI, ci0, x);

    for (int i = 0; i < n; ++i) {
        _F[i] = x[i];
    }
}