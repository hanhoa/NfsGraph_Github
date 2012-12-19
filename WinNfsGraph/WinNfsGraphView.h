
// WinNfsGraphView.h : CWinNfsGraphView 클래스의 인터페이스
//

#pragma once
#include "WinNfsGraphDoc.h"


class CWinNfsGraphView : public CView
{
protected: // serialization에서만 만들어집니다.
	CWinNfsGraphView();
	DECLARE_DYNCREATE(CWinNfsGraphView)

// 특성입니다.
public:
	CWinNfsGraphDoc* GetDocument() const;

// 작업입니다.
public:
    void InitGraph(void);
    void RedrawGraph(void);

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CWinNfsGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CPoint m_ptMousePoint;
    CPoint m_ptChangedMousePoint;
    BOOL m_bMouseDown;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnConfiguration(void);
    afx_msg void OnUpdateConfiguration(CCmdUI *pCmdUI);
    afx_msg void OnXaxisZoomIn(void);
    afx_msg void OnXaxisZoomOut(void);
    afx_msg void OnYaxisZoomIn(void);
    afx_msg void OnYaxisZoomOut(void);
    afx_msg void OnToggleGraphType(void);
    afx_msg void OnToggleLegend(void);
    afx_msg void OnMoveLeft(void);
    afx_msg void OnMoveRight(void);
    afx_msg void OnMoveUp(void);
    afx_msg void OnMoveDown(void);
    afx_msg void OnMoveZeroX(void);
    afx_msg void OnMoveZeroY(void);
};

#ifndef _DEBUG  // WinNfsGraphView.cpp의 디버그 버전
inline CWinNfsGraphDoc* CWinNfsGraphView::GetDocument() const
   { return reinterpret_cast<CWinNfsGraphDoc*>(m_pDocument); }
#endif

