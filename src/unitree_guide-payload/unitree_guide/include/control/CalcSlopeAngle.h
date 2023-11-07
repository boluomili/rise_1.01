/**********************************************************************
 Copyright (c) 2020-2023, Unitree Robotics.Co.Ltd. All rights reserved.
***********************************************************************/
#ifndef CALCSLOPEANGLE_H
#define CALCSLOPEANGLE_H

#include "common/mathTypes.h"
#include "thirdParty/quadProgpp/QuadProg++.hh"
#include "common/unitreeRobot.h"

#ifdef COMPILE_DEBUG
    #include "common/PyPlot.h"
#endif  // COMPILE_DEBUG
class CalcSlopeAngle{
public:
    CalcSlopeAngle();
    double calAngle(Vec34 PosFeet);
private:
    void calMatrixA(Vec34 PosFeetxy);
    void calVectorB(Vec34 PosFeetz);
    void calConstraints();
    void solveQP();

    Mat3 _G;
    Vec4 _ZM;
    Vec3 _deta, _g0T;
    Eigen::Matrix<double, 4 , 3 > _CI;
    Eigen::Matrix<double, 3 , 3 > _CE;
    Eigen::Matrix<double, 4 , 1 > _ci0;
    Eigen::Matrix<double, 3 , 1 > _ce0;
    Eigen::Matrix<double, 4 , 3 > _YM;
    Eigen::Matrix<double, 4 , 4> _S;

    quadprogpp::Matrix<double> G, CE, CI;
    quadprogpp::Vector<double> g0, ce0, ci0, x;

    double _Angle = 0;

#ifdef COMPILE_DEBUG
    PyPlot *_testPlot;
#endif  // COMPILE_DEBUG
};

#endif  // CALCSLOPEANGLE_H