
// WinNfsGraphView.h : CWinNfsGraphView Ŭ������ �������̽�
//

#pragma once
#include "WinNfsGraphDoc.h"


class CWinNfsGraphView : public CView
{
protected: // serialization������ ��������ϴ�.
	CWinNfsGraphView();
	DECLARE_DYNCREATE(CWinNfsGraphView)

// Ư���Դϴ�.
public:
	CWinNfsGraphDoc* GetDocument() const;

// �۾��Դϴ�.
public:
    void InitGraph(void);
    void RedrawGraph(void);

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
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

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // WinNfsGraphView.cpp�� ����� ����
inline CWinNfsGraphDoc* CWinNfsGraphView::GetDocument() const
   { return reinterpret_cast<CWinNfsGraphDoc*>(m_pDocument); }
#endif

