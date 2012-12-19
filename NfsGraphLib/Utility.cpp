#include "StdAfx.h"
#include "gdefine.h"

namespace NfsGraph
{

double getRealMag(MAG_LEVEL eML, bool &bIsLog)
{
    switch(eML)
    {
    case ML_10x:
        bIsLog = false;
        return 10.0;
    case ML_5x:
        bIsLog = false;
        return 5.0;
    case ML_2x:
        bIsLog = false;
        return 2.0;
    case ML_1x:
        bIsLog = false;
        return 1.0;
    case ML_1of2x:
        bIsLog = false;
        return 0.5;
    case ML_1of5x:
        bIsLog = false;
        return 0.2;
    case ML_1of10x:
        bIsLog = false;
        return 0.1;
    case ML_1of20x:
        bIsLog = false;
        return 0.05;
    case ML_1of50x:
        bIsLog = false;
        return 0.02;
    case ML_1of100x:
        bIsLog = false;
        return 0.01;
    case ML_1of200x:
        bIsLog = false;
        return 0.005;
    case ML_1of500x:
        bIsLog = false;
        return 0.002;
    case ML_1of1000x:
        bIsLog = false;
        return 0.001;
    case ML_Log2x:
        bIsLog = true;
        return 2.;
    case ML_Log5x:
        bIsLog = true;
        return 5.;
    case ML_Log10x:
        bIsLog = true;
        return 10.;
    default:
        bIsLog = false;
        return 1.0;
    }
}

double logB(double x, double base)
{
    return log(x) / log(base);
}

}