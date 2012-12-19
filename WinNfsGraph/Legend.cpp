#include "StdAfx.h"
#include "Legend.h"

#define LEGEND_GAP_X      20
#define LEGEND_GAP_Y      40

CLegend::CLegend(CNfsGraphManager *pNGM)
:m_pNGM(pNGM)
{
    COLORREF crPalette[MAX_OF_COLORS] = 
    {
        PC_LIGHTRED,
        PC_LIGHTGREEN,
        PC_LIGHTBLUE,
        PC_CYAN,
        PC_LIGHTMAGENTA,
        PC_BROWN,
        PC_LIGHTGRAY,
        PC_RED,
        PC_YELLOW,
        PC_GREEN,
        PC_DARKGRAY,
        PC_BLUE,
        PC_LIGHTCYAN,
        PC_MAGENTA,        
        PC_BLACK
    };
    memcpy(m_crPalette, crPalette, sizeof(crPalette));

    LoadLegendValue();
}

CLegend::~CLegend(void)
{
}

void CLegend::LoadLegendValue(void)
{
    U32 nValue;
    U32 nColorIdx = 0;

    m_mapLegendValues.clear();
    for(U32 i = 0; i < m_pNGM->GetTotalCount(); i++)
    {
        if(m_pNGM->GetLegendValue(m_pNGM->GetCurGraphNum(), i, nValue) == false) break;
        if(nColorIdx >= MAX_OF_COLORS) break;

        if(m_mapLegendValues.find(nValue) == m_mapLegendValues.end())
        {
            m_mapLegendValues[nValue] = m_crPalette[nColorIdx];
            nColorIdx++;
        }
    }
}

COLORREF CLegend::GetLegendColor(U32 nLegendVal)
{
    if(m_mapLegendValues.find(nLegendVal) != m_mapLegendValues.end())
    {
        return m_mapLegendValues[nLegendVal];
    }
    return PC_BLACK;
}

U32 CLegend::GetLegendValue(U32 nIdx)
{
    std::map<U32, COLORREF>::iterator it = m_mapLegendValues.begin();
    if(nIdx >= m_mapLegendValues.size()) return 0;

    for(U32 i = 0; i < nIdx; i++) it++;

    return it->first;
}


void CLegend::DrawLegend(CDC *pScreenDC, CDC *pMemDC, LONG cx, LONG cy)
{
    U32 nCount = m_mapLegendValues.size();
    if(nCount == 0) return;

    // Draw Outline
    U32 nWidth = 150;
    U32 nHeight = 30 * nCount + 10;

    pMemDC->Rectangle(cx - nWidth - LEGEND_GAP_X, LEGEND_GAP_Y, cx - LEGEND_GAP_X, nHeight + LEGEND_GAP_Y);
    pMemDC->MoveTo(cx - nWidth - LEGEND_GAP_X, nHeight + LEGEND_GAP_Y);
    pMemDC->LineTo(cx - LEGEND_GAP_X, nHeight + LEGEND_GAP_Y);
    pMemDC->MoveTo(cx - LEGEND_GAP_X, LEGEND_GAP_Y);
    pMemDC->LineTo(cx - LEGEND_GAP_X, nHeight + LEGEND_GAP_Y);

    // Make another surface for legend
    CBitmap cLegendSurface;
    cLegendSurface.CreateCompatibleBitmap(pScreenDC, nWidth, nHeight);

    CDC dcMem;
    dcMem.CreateCompatibleDC(pScreenDC);
    CBitmap *pOldBitmap = dcMem.SelectObject(&cLegendSurface);
    dcMem.FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
    
    CRect colorRect(10, 10, 30, 30);
    CRect nameRect(40, 10, nWidth - 10, 30);
    CBrush brush;

    CString strName;
    std::map<U32, COLORREF>::iterator it;

    for(it = m_mapLegendValues.begin(); it != m_mapLegendValues.end(); it++)
    {
        brush.CreateSolidBrush(it->second);

        dcMem.FillRect(colorRect, &brush);
        colorRect.OffsetRect(0, 30);

        strName = m_pNGM->GetLegendString(it->first).c_str();
        dcMem.DrawText(strName, nameRect, DT_LEFT);
        nameRect.OffsetRect(0, 30);

        brush.DeleteObject();
    }

    pMemDC->BitBlt(cx - nWidth - LEGEND_GAP_X + 1, LEGEND_GAP_Y + 1, nWidth - 2, nHeight - 2, &dcMem, 0, 0, SRCCOPY);

    dcMem.SelectObject(pOldBitmap);
    dcMem.DeleteDC();
    cLegendSurface.DeleteObject();
}