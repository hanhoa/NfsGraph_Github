#include "StdAfx.h"
#include "DrawGraph.h"


CDrawGraph::CDrawGraph(CNfsGraphManager *pNGM, CAxisManager *pAxisManager, CLegend *pLegend)
: m_pNGM(pNGM)
, m_pAxisManager(pAxisManager)
, m_pLegend(pLegend)
{
}

CDrawGraph::~CDrawGraph(void)
{
}

void CDrawGraph::DrawGraph(CDC *pScreenDC, CDC *pMemDC, LONG cx, LONG cy) 
{ 
    LONG nXpos, nYpos; 
    BOOL bStartDrawLine = FALSE;

    // Make another surface for graph
    CBitmap cGraphSurface;
    cGraphSurface.CreateCompatibleBitmap(pScreenDC, cx, cy);

    CDC dcMem;
    dcMem.CreateCompatibleDC(pScreenDC);
    CBitmap *pOldBitmap = dcMem.SelectObject(&cGraphSurface);
    dcMem.FillSolidRect(0, 0, cx, cy, RGB(255, 255, 255));

    // Calculate CellSize and StartIdx and EndIdx for X axis.
    DWORD nStartIdx, nEndIdx;
    bool bLogX, bLogY;
    double fMagX = getRealMag(m_pNGM->GetMagX(), bLogX);
    DWORD nCellSizeX = DEF_CELL_SIZE;
    
    if(bLogX)
    {
        nStartIdx = 0;
        nEndIdx = m_pNGM->GetTotalCount();
        
        nCellSizeX = CAxis::GetLogMarkingGap((U32)fMagX);
    }
    else
    {
        DWORD nRealCellSize = CAxis::GetMarkingGap(fMagX, bLogX);
        nStartIdx = m_pAxisManager->GetScrollPosH() / nRealCellSize;
        nEndIdx = nStartIdx + ((cx - GRAPH_LEFT_GAP) / nRealCellSize) + 2;
        if(nEndIdx > m_pNGM->GetTotalCount()) nEndIdx = m_pNGM->GetTotalCount();
    }

    LONG nAdditionLine = CAxis::GetMarkingGap(fMagX, bLogX) / DEF_CELL_SIZE / 2;
    
    // Calculate CellSize for Y axis.
    double fMagY = getRealMag(m_pNGM->GetMagY(), bLogY);
    DWORD nCellSizeY = DEF_CELL_SIZE;

    if(bLogY)
        nCellSizeY = CAxis::GetLogMarkingGap((U32)fMagY);

    CPen cPen, *pOldPen;
    U32 nLegendVal;
    
    for(DWORD nIdx = nStartIdx; nIdx < nEndIdx; nIdx++) 
    { 
        DWORD xpos, ypos;
        if(m_pNGM->GetPosCoordinate(m_pNGM->GetCurGraphNum(), nIdx, xpos, ypos) == false)
        {
            AfxMessageBox("ERROR : Can't get coordinate!");
            return;
        }

        nXpos = (LONG)(xpos * nCellSizeX);
        nXpos -= (LONG)m_pAxisManager->GetScrollPosH(); 
        nYpos = (LONG)(cy - (ypos * nCellSizeY));
        nYpos += (LONG)m_pAxisManager->GetScrollPosV(); 

        if(m_pNGM->GetLegendValue(m_pNGM->GetCurGraphNum(), nIdx, nLegendVal) == false)
        {
            AfxMessageBox("ERROR : Can't get Legend Value!");
            return;
        }
        
        cPen.CreatePen(PS_SOLID, 1, m_pLegend->GetLegendColor(nLegendVal));
        pOldPen = dcMem.SelectObject(&cPen);

        if(m_pNGM->GetGraphType() == GT_LINE)
        {
            if(bStartDrawLine == FALSE) 
            { 
                dcMem.Rectangle(nXpos-2, nYpos-2, nXpos+3, nYpos+3);
                dcMem.MoveTo(nXpos, nYpos); 
                bStartDrawLine = TRUE; 
            } 
            else 
            {
                dcMem.Rectangle(nXpos-2, nYpos-2, nXpos+3, nYpos+3);
                dcMem.LineTo(nXpos, nYpos); 
            }
        }
        else if(m_pNGM->GetGraphType() == GT_BAR)
        {
            for(LONG i = nXpos - nAdditionLine; i <= nXpos + nAdditionLine; i++)
            {
                dcMem.MoveTo(i, nYpos);
                dcMem.LineTo(i, cy);
            }
        }

        dcMem.SelectObject(pOldPen);
        cPen.DeleteObject();
    } 

    pMemDC->BitBlt(GRAPH_LEFT_GAP, 0, cx - GRAPH_LEFT_GAP, cy - GRAPH_BOTTOM_GAP, &dcMem, 0, GRAPH_BOTTOM_GAP, SRCCOPY);

    dcMem.SelectObject(pOldBitmap);
    dcMem.DeleteDC();
    cGraphSurface.DeleteObject();
}