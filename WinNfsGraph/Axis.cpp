#include "StdAfx.h"
#include "Axis.h"

#define LENGTH_OF_SHORT_MARKING     1
#define LENGTH_OF_LONG_MARKING      3


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

U32 CAxis::GetLogMarkingGap(U32 nBase)
{
    U32 nMarkingGap;

    if(nBase <= 2) nMarkingGap = DEF_CELL_SIZE * 10;
    else if(nBase <= 5) nMarkingGap = DEF_CELL_SIZE * 10;
    else if(nBase <= 10) nMarkingGap = DEF_CELL_SIZE * 10;

    return nMarkingGap;
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
                rcNumber.SetRect(nStartX + nPos - 17, nStartY + LENGTH_OF_LONG_MARKING + 5, nStartX + nPos + 17, nStartY + LENGTH_OF_LONG_MARKING + 20);
                pDC->DrawText(strNum, rcNumber, DT_CENTER);

                nMarkingNum = 0;
            }

            nMarkingNum++;
            nStartValue += nInc;
        }
    }
    else if(m_eDirection == AD_VERTICAL)
    {
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
                rcNumber.SetRect(nStartX - LENGTH_OF_LONG_MARKING - 55, nStartY - nPos - 7, nStartX - LENGTH_OF_LONG_MARKING - 5, nStartY - nPos + 7);
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
