#include "StdAfx.h"
#include "Axis.h"

#define LENGTH_OF_SHORT_MARKING     1
#define LENGTH_OF_LONG_MARKING      3

#define TEXTBOX_SIZE_X_AXIS    34
#define TEXTBOX_SIZE_Y_AXIS    60



CAxis::CAxis(AXIS_DIRECTION eDir)
:m_eDirection(eDir)
, m_nLength(10)
, m_eMagnification(ML_1x)
, m_nScrollPos(0)
{
}

CAxis::~CAxis(void)
{
}

U32 CAxis::GetMarkingGap(double fMag, bool bLog)
{
    U32 nMarkingGap;

    if(bLog)
        nMarkingGap = GetLogMarkingGap((U32)fMag);
    else
    {
        if(fMag > 1.)
            nMarkingGap = DEF_CELL_SIZE * (U32)fMag;
        else
            nMarkingGap = DEF_CELL_SIZE;
    }

    return nMarkingGap;
}

void CAxis::Draw(CDC *pDC, U32 nStartX, U32 nStartY)
{
    DWORD nInc = 1;
    CString strNum;
    CRect rcNumber;

    bool bLog;
    double fMag = getRealMag(m_eMagnification, bLog);
    U32 nMarkingGap = GetMarkingGap(fMag, bLog);
    U32 nIntervalPrintingNum = 1;

    if(nMarkingGap == DEF_CELL_SIZE) nInc = (DWORD)(1. / fMag);

    if(!bLog)
    {
        if(fMag > 1.)
        {
            if(nMarkingGap <= 4)
                nIntervalPrintingNum = 10;
            else
                nIntervalPrintingNum = 5;
        }
        else
        {
            nIntervalPrintingNum = 20;
        }
    }

    DWORD nMarkingNum = m_nScrollPos / nMarkingGap;
    DWORD nStartPoint = nMarkingGap - (m_nScrollPos % nMarkingGap);

    if(nStartPoint == nMarkingGap) nStartPoint = 0;
    else nMarkingNum++;

    DWORD nStartValue = nMarkingNum * nInc;

    if(m_eDirection == AD_HORIZONTAL)
    {
        
        CFont font, *pOldFont;
        font.CreatePointFont(100, "Arial");
        pOldFont = pDC->SelectObject(&font);

        rcNumber.SetRect(nStartX, nStartY + LENGTH_OF_LONG_MARKING + 30, nStartX + m_nLength, nStartY + LENGTH_OF_LONG_MARKING + 60);
        pDC->DrawText("Time", rcNumber, DT_SINGLELINE | DT_CENTER | DT_TOP);

        pDC->SelectObject(pOldFont);

        pDC->MoveTo(nStartX, nStartY);
        pDC->LineTo(nStartX + m_nLength, nStartY);

        for(DWORD nPos = nStartPoint; nPos < m_nLength; nPos += nMarkingGap)
        { 
            if(nMarkingNum % nIntervalPrintingNum)
            {
                pDC->MoveTo(nStartX + nPos, nStartY - LENGTH_OF_SHORT_MARKING);
                pDC->LineTo(nStartX + nPos, nStartY + LENGTH_OF_SHORT_MARKING + 1);
            }
            else
            {
                pDC->MoveTo(nStartX + nPos, nStartY - LENGTH_OF_LONG_MARKING);
                pDC->LineTo(nStartX + nPos, nStartY + LENGTH_OF_LONG_MARKING + 1);

                if(bLog)
                    strNum.Format("%d^%d", (U32)fMag, nStartValue);
                else
                    strNum.Format("%d", nStartValue);
                rcNumber.SetRect(nStartX + nPos - (TEXTBOX_SIZE_X_AXIS / 2), nStartY + LENGTH_OF_LONG_MARKING + 5, nStartX + nPos + (TEXTBOX_SIZE_X_AXIS / 2), nStartY + LENGTH_OF_LONG_MARKING + 20);
                pDC->DrawText(strNum, rcNumber, DT_CENTER);

                nMarkingNum = 0;
            }

            nMarkingNum++;
            nStartValue += nInc;
        }
    }
    else if(m_eDirection == AD_VERTICAL)
    {
        SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

        if(m_strAxisTitle.compare("NoTitle"))
        {
            CFont font, font2, *pOldFont;
            LOGFONT logFont;
            font.CreatePointFont(100, "Arial");
            font.GetLogFont(&logFont);
            logFont.lfEscapement = 900;
            logFont.lfOrientation = 900;
            font2.CreateFontIndirect(&logFont);
            pOldFont = pDC->SelectObject(&font2);

            rcNumber.SetRect(nStartX - TEXTBOX_SIZE_Y_AXIS - 10, 0, nStartX + 100, nStartY);
            pDC->DrawText(m_strAxisTitle.c_str(), rcNumber, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

            pDC->SelectObject(pOldFont);
        }

        pDC->MoveTo(nStartX, nStartY);
        pDC->LineTo(nStartX, nStartY - m_nLength);

        for(DWORD nPos = nStartPoint; nPos < m_nLength; nPos += nMarkingGap)
        { 
            if(nMarkingNum % nIntervalPrintingNum)
            {
                pDC->MoveTo(nStartX - LENGTH_OF_SHORT_MARKING, nStartY - nPos);
                pDC->LineTo(nStartX + LENGTH_OF_SHORT_MARKING + 1, nStartY - nPos);
            }
            else
            {
                pDC->MoveTo(nStartX - LENGTH_OF_LONG_MARKING, nStartY - nPos);
                pDC->LineTo(nStartX + LENGTH_OF_LONG_MARKING + 1, nStartY - nPos);

                if(bLog)
                    strNum.Format("%d^%d", (U32)fMag, nStartValue);
                else
                    strNum.Format("%d", nStartValue);
                rcNumber.SetRect(nStartX - TEXTBOX_SIZE_Y_AXIS, nStartY - nPos - 7, nStartX - LENGTH_OF_LONG_MARKING - 5, nStartY - nPos + 7);
                pDC->DrawText(strNum, rcNumber, DT_RIGHT);

                nMarkingNum = 0;
            }

            nMarkingNum++;
            nStartValue += nInc;
        }
    }
}

U32 CAxis::GetValueOnAxis(U32 nPosOnAxis)
{
    DWORD nMarkingGap;
    DWORD nInc = 1;

    bool bLog;
    double fMag = getRealMag(m_eMagnification, bLog);

    nMarkingGap = GetMarkingGap(fMag, bLog);
    if(nMarkingGap == DEF_CELL_SIZE) nInc = (DWORD)(1. / fMag);

    return ((nPosOnAxis + m_nLength) / nMarkingGap) * nInc;
}
