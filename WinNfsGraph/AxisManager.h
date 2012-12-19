#pragma once

#include "Axis.h"

class CAxisManager
{
public:
    CAxisManager(CNfsGraphManager *pNGM);
    ~CAxisManager(void);

    void DrawAxis(CDC *pDC, LONG cx, LONG cy);

    void SetScrollPosV(U32 nPos) { m_pAxisVertical->SetScrollPos(nPos); }
    void SetScrollPosH(U32 nPos) { m_pAxisHorizontal->SetScrollPos(nPos); }

    U32 GetScrollPosV(void) { return m_pAxisVertical->GetScrollPos(); }
    U32 GetScrollPosH(void) { return m_pAxisHorizontal->GetScrollPos(); }

    U32  GetValueOnAxisV(U32 nPosOnAxis) { return m_pAxisVertical->GetValueOnAxis(nPosOnAxis); }
    U32  GetValueOnAxisH(U32 nPosOnAxis) { return m_pAxisHorizontal->GetValueOnAxis(nPosOnAxis); }

private:
    CAxisManager(void);

private:
    CNfsGraphManager *m_pNGM;
    CAxis *m_pAxisVertical, *m_pAxisHorizontal;
};

