#pragma once

enum AXIS_DIRECTION
{
    AD_HORIZONTAL,
    AD_VERTICAL
};

class CAxis
{
public:
    CAxis(AXIS_DIRECTION eDir);
    virtual ~CAxis(void);

    // Get/Set
    void SetMag(MAG_LEVEL eMag) { m_eMagnification = eMag; }
    void SetLength(U32 nLength) { m_nLength = nLength; }

    void SetScrollPos(U32 nScrollPos) { m_nScrollPos = nScrollPos; }
    U32  GetScrollPos(void) { return m_nScrollPos; }

    U32  GetValueOnAxis(U32 nPosOnAxis);        // in pixel.

    void Draw(CDC *pDC, U32 nStartX, U32 nStartY);
    
public:
    static U32 GetLogMarkingGap(U32 nBase);
    static U32 GetMarkingGap(double fMag, bool bLog);

private:
    CAxis(void);

private:
    AXIS_DIRECTION m_eDirection;
    U32 m_nLength;          // 화면에 그려주는 축의 길이.

    MAG_LEVEL m_eMagnification;   // 실제 값과의 배율.
    U32 m_nScrollPos;             // 스크롤 되었을 때 위치. 가장 왼쪽 혹은 가장 아랫쪽에 보여지는 부분의 Pixel값
};

