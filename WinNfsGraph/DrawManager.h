#pragma once

#include "AxisManager.h"
#include "DrawGraph.h"
#include "Legend.h"

class CDrawManager
{
public:
    CDrawManager(CNfsGraphManager *pNGM);
    ~CDrawManager(void);

    void InitResource(void);
    void InitResource(CDC *pDC, int cx, int cy);
    void ClearResource(void);

    bool ReDraw(CDC *pDC);      // Delete backsurface and draw graph on it. It's for screen scroll.
    bool Flip(CDC *pDC);        // Copy backsurface to screen. It's for just displaying.
    bool ResizingGraph(CDC *pDC, int cx, int cy);   // Delete backsurface and Resize backsurface and draw. It's for resizing screen.
    bool Scroll(int xMove, int yMove);
    bool ScrollZeroX(void);
    bool ScrollZeroY(void);

    void ChangeGraph(void); // Must call this functions when changing graph.

    bool IsDrawLegend(void) { return m_bIsDrawLegend; }
    void SetDrawLegend(bool bDraw) { m_bIsDrawLegend = bDraw; }

public:
    CLegend *GetLegend(void) { return m_pLegend; }

private:
    CDrawManager(void);

    void Draw(CDC *pDC);        // Draw graph to the backsurface.

private:
    CNfsGraphManager *m_pNGM;
    CAxisManager *m_pAxisManager;
    CDrawGraph *m_pDrawGraph;
    CLegend *m_pLegend;

    CBitmap *m_pBackSurface;
    BITMAP m_bi;

    bool m_bIsDrawLegend;
};

