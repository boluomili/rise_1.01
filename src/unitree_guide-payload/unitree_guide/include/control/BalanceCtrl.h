/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef BALANCECTRL_H
#define BALANCECTRL_H

#include "common/mathTypes.h"
#include "thirdParty/quadProgpp/QuadProg++.hh"
#include "common/unitreeRobot.h"

#ifdef COMPILE_DEBUG
    #include "common/PyPlot.h"
#endif  // COMPILE_DEBUG
//利用二次规划方法求解机器人动力学方程的 BalanceCtrl类
class BalanceCtrl{
public:
    BalanceCtrl(double mass, Mat3 Ib, Mat6 S, double alpha, double beta);
    BalanceCtrl(QuadrupedRobot *robModel);
    Vec34 calF(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, Vec34 feetPos2B, VecInt4 contact);
    Vec34 calF(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, Vec34 feetPos2B, VecInt4 contact, double _mp, Vec3 _hatd);
#ifdef COMPILE_DEBUG
    void setPyPlot(PyPlot *plot){_testPlot = plot;}
#endif  // COMPILE_DEBUG
private:
    void calMatrixA(Vec34 feetPos2B, RotMat rotM, VecInt4 contact);
    void calVectorBd(Vec3 ddPcd, Vec3 dWbd, RotMat rotM);
    void calVectorBd(Vec3 ddPcd, Vec3 dWbd, RotMat rotM, double _mp, Vec3 _hatd);
    void calConstraints(VecInt4 contact);
    void solveQP();

    Mat12 _G, _W, _U;
    Mat6 _S;
    Mat3 _Ib;
    Vec6 _bd;
    Vec3 _g;
    Vec3 _pcb;
    Vec12 _F, _Fprev, _g0T;
    double _mass, _alpha, _beta, _fricRatio;//机器人总质量_mass
    Eigen::MatrixXd _CE, _CI;
    Eigen::VectorXd _ce0, _ci0;
    Eigen::Matrix<double, 6 , 12> _A;
    Eigen::Matrix<double, 5 , 3 > _fricMat;

    quadprogpp::Matrix<double> G, CE, CI;
    quadprogpp::Vector<double> g0, ce0, ci0, x;

#ifdef COMPILE_DEBUG
    PyPlot *_testPlot;
#endif  // COMPILE_DEBUG
};

#endif  // BALANCECTRL_H