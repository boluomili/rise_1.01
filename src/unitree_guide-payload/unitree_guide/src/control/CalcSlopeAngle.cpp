#include "control/CalcSlopeAngle.h"
#include "common/mathTools.h"
#include "common/timeMarker.h"

CalcSlopeAngle::CalcSlopeAngle()
{
    Vec4 s;
    s << 1, 1, 1, 1; //权重
    _S = s.asDiagonal();//权重矩阵
}
double CalcSlopeAngle::calAngle(Vec34 PosFeet)
{
    calMatrixA(PosFeet);
    calVectorB(PosFeet);
    calConstraints();
    _G = _YM.transpose()*_S*_YM ;
    _g0T = -_ZM.transpose()*_S*_YM ;
    solveQP();
    return (atan(_Angle));
}
void CalcSlopeAngle::calMatrixA(Vec34 PosFeetxy)
{
    _YM.col(0)  = (PosFeetxy.row(0)).transpose();
    _YM.col(1) = (PosFeetxy.row(1)).transpose();
    _YM.col(2) = Vec4(1,1,1,1);
}
void CalcSlopeAngle::calVectorB(Vec34 PosFeetz)
{
    _ZM = (PosFeetz.row(2)).transpose();
}
void CalcSlopeAngle::calConstraints()
{
    _CI.setZero();
    _ci0.setZero();
    _CE.setZero();
    _ce0.setZero();

    _CI << 1,  0, 0,
           0,  1, 0,
          -1,  0, 0,
           0, -1, 0;
    _ci0 << 1.2,
            1.2,
            1.2,
            1.2;     

}
void CalcSlopeAngle::solveQP()
{
    int n = _deta.size();//3
    int m = _ce0.size();//3
    int p = _ci0.size();//4

    G.resize(n, n);//3*3
    CE.resize(n, m);//3*3
    CI.resize(n, p);//3*4
    g0.resize(n);//3*1
    ce0.resize(m);//3*1
    ci0.resize(p);//4*1
    x.resize(n);//3*1

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
    //double value = solve_quadprog(G, g0, CE, ce0, CI, ci0, x);
    cholesky_solve(G, x, g0);
    _Angle = -x[0];
    std::cout<<"_Angle ="<<_Angle<<std::endl;
    std::cout<<"_Angle12223333"<<std::endl;
}