#include "StdAfx.h"
#include "DrawManager.h"


CDrawManager::CDrawManager(CNfsGraphManager *pNGM)
:m_pNGM(pNGM), m_pBackSurface(NULL), m_pAxisManager(NULL), m_pDrawGraph(NULL), m_pLegend(NULL), m_bIsDrawLegend(true)
{
}

CDrawManager::~CDrawManager(void)
{
    ClearResource();
}

void CDrawManager::InitResource(CDC *pDC, int cx, int cy)
{
    if(!m_pAxisManager)
        m_pAxisManager = new CAxisManager(m_pNGM);

    if(!m_pLegend)
        m_pLegend = new CLegend(m_pNGM);

    if(!m_pDrawGraph)
        m_pDrawGraph = new CDrawGraph(m_pNGM, m_pAxisManager, m_pLegend);

    if(m_pBackSurface == NULL)
    {
        m_pBackSurface = new CBitmap();
    }
    else
    {
        m_pBackSurface->DeleteObject();
    }

    m_pBackSurface->CreateCompatibleBitmap(pDC, cx, cy);
    m_pBackSurface->GetObject(sizeof(BITMAP), &m_bi);

    Draw(pDC);
}

void CDrawManager::ClearResource(void)
{
    delete m_pDrawGraph; m_pDrawGraph = NULL;
    delete m_pAxisManager; m_pAxisManager = NULL;
    delete m_pLegend; m_pLegend = NULL;

    if(m_pBackSurface)
    {
        delete m_pBackSurface;
        m_pBackSurface = NULL;
    }
}

void CDrawManager::ChangeGraph(void)
{
    m_pLegend->LoadLegendValue();
}

void CDrawManager::Draw(CDC *pDC)
{
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);
    CBitmap *pOldBitmap = dcMem.SelectObject(m_pBackSurface);
    dcMem.FillSolidRect(0, 0, m_bi.bmWidth, m_bi.bmHeight, RGB(255, 255, 255));
      
    if(m_pNGM->GetTotalCount() > 0)
    {
        m_pDrawGraph->DrawGraph(pDC, &dcMem, m_bi.bmWidth, m_bi.bmHeight);
    }

    m_pAxisManager->DrawAxis(&dcMem, m_bi.bmWidth, m_bi.bmHeight);

    if(m_bIsDrawLegend)
        m_pLegend->DrawLegend(pDC, &dcMem, m_bi.bmWidth, m_bi.bmHeight);

    dcMem.SelectObject(pOldBitmap);
    dcMem.DeleteDC();
}

bool CDrawManager::Flip(CDC *pDC)
{
    if(!m_pBackSurface) return false;
    
    CDC dcMem;
    dcMem.CreateCompatibleDC(pDC);
    CBitmap *pOldBitmap = dcMem.SelectObject(m_pBackSurface);
    pDC->BitBlt(0, 0, m_bi.bmWidth, m_bi.bmHeight, &dcMem, 0, 0, SRCCOPY);
    dcMem.SelectObject(pOldBitmap);
    dcMem.DeleteDC();
    
    return true;
}

bool CDrawManager::ReDraw(CDC *pDC)
{
    if(!m_pBackSurface) return false;
    
    m_pBackSurface->DeleteObject();
    m_pBackSurface->CreateCompatibleBitmap(pDC, m_bi.bmWidth, m_bi.bmHeight);
    Draw(pDC);
    
    return true;
}

bool CDrawManager::ResizingGraph(CDC *pDC, int cx, int cy)
{
    if(!m_pBackSurface) return false;

    m_pBackSurface->DeleteObject();
    m_pBackSurface->CreateCompatibleBitmap(pDC, cx, cy);
    m_pBackSurface->GetObject(sizeof(BITMAP), &m_bi);
    Draw(pDC);

    return true;
}

bool CDrawManager::Scroll(int xMove, int yMove)
{
    if(!m_pBackSurface) return false;

    LONG nScrollPos;

    nScrollPos = (LONG)m_pAxisManager->GetScrollPosH() - xMove;
    if(nScrollPos < 0) nScrollPos = 0;
        
    /*if(nScrollPos >= 100 && m_pAxisManager->GetValueOnAxisH(nScrollPos - 100) > m_pNGM->GetTotalCount() && nScrollPos > (LONG)m_pAxisManager->GetScrollPosH())
    {
        nScrollPos = (LONG)m_pAxisManager->GetScrollPosH();
    }*/
    m_pAxisManager->SetScrollPosH(nScrollPos);
    
    nScrollPos = (LONG)m_pAxisManager->GetScrollPosV() - yMove;
    if(nScrollPos < 0) nScrollPos = 0;
    
    /*if(nScrollPos >= 100 && m_pAxisManager->GetValueOnAxisV(nScrollPos - 100) > m_pNGM->GetMaxValue() && nScrollPos > (LONG)m_pAxisManager->GetScrollPosV())
    {
        nScrollPos = (LONG)m_pAxisManager->GetScrollPosV();
    }*/
    m_pAxisManager->SetScrollPosV(nScrollPos);

    return true;
}

bool CDrawManager::ScrollZeroX(void)
{
    if(!m_pBackSurface) return false;

    m_pAxisManager->SetScrollPosH(0);

    return true;
}

bool CDrawManager::ScrollZeroY(void)
{
    if(!m_pBackSurface) return false;

    m_pAxisManager->SetScrollPosV(0);

    return true;
}