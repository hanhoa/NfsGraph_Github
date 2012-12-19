#pragma once

#include "Types.h"
#include <stdio.h>
#include <math.h>
#include <iostream>

#define DEBUG_PRINTF(x)     std::cout << x << std::endl;

namespace NfsGraph
{
    enum MAG_LEVEL
    {
        ML_10x,
        ML_5x,
        ML_2x,
        ML_1x,
        ML_1of2x,
        ML_1of5x,
        ML_1of10x,
        ML_1of20x,
        ML_1of50x,
        ML_1of100x,
        ML_1of200x,
        ML_1of500x,
        ML_1of1000x,
        ML_Log2x,
        ML_Log5x,
        ML_Log10x,
        ML_MAXOFLEVEL
    };

    enum GRAPH_TYPE
    {
        GT_LINE,
        GT_BAR
    };

    double logB(double x, double base);
    double getRealMag(MAG_LEVEL eML, bool &bIsLog);     // This function lets you get real magnification. 
                                                        // But if bIsLog is true, the return value is the base of log function, not mag.
}

