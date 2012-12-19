#pragma once

#include "AxisManager.h"
#include "Legend.h"

class CDrawGraph
{
public:
    CDrawGraph(CNfsGraphManager *pNGM, CAxisManager *pAxisManager, CLegend *pLegend);
    ~CDrawGraph(void);

    void DrawGraph(CDC *pScreenDC, CDC *pMemDC, LONG cx, LONG cy);

private:
    CDrawGraph(void);

private:
    CNfsGraphManager *m_pNGM;
    CAxisManager *m_pAxisManager;
    CLegend *m_pLegend;
};

