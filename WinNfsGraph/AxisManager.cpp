#include "StdAfx.h"
#include "AxisManager.h"

#define GAP_OF_RIGHT_TOP        100

CAxisManager::CAxisManager(CNfsGraphManager *pNGM)
: m_pNGM(pNGM)
{
    m_pAxisVertical = new CAxis(AD_VERTICAL);
    m_pAxisHorizontal= new CAxis(AD_HORIZONTAL);
}


CAxisManager::~CAxisManager(void)
{
    delete m_pAxisHorizontal;
    delete m_pAxisVertical;
}

void CAxisManager::DrawAxis(CDC *pDC, LONG cx, LONG cy)
{    
    if(cx < GRAPH_LEFT_GAP || cy < GRAPH_BOTTOM_GAP) return;

    CFont font, *pOldFont;
    font.CreatePointFont(100, "Terminal");
    pOldFont = pDC->SelectObject(&font);

    m_pAxisHorizontal->SetMag(m_pNGM->GetMagX());
    m_pAxisVertical->SetMag(m_pNGM->GetMagY());

    m_pAxisVertical->SetLength(cy - GRAPH_BOTTOM_GAP);
    m_pAxisHorizontal->SetLength(cx - GRAPH_LEFT_GAP);

    m_pAxisVertical->Draw(pDC, GRAPH_LEFT_GAP, cy - GRAPH_BOTTOM_GAP);
    m_pAxisHorizontal->Draw(pDC, GRAPH_LEFT_GAP, cy - GRAPH_BOTTOM_GAP);

    pDC->SelectObject(pOldFont);
}