
// WinNfsGraphView.cpp : CWinNfsGraphView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinNfsGraph.h"
#endif

#include "WinNfsGraphDoc.h"
#include "WinNfsGraphView.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define REDRAW_TIMER_ID     0x100
#define SCROLL_FPS          50


// CWinNfsGraphView

IMPLEMENT_DYNCREATE(CWinNfsGraphView, CView)

BEGIN_MESSAGE_MAP(CWinNfsGraphView, CView)
	// 표준 인쇄 명령입니다.
	//ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_COMMAND(ID_SETTINGS_CONFIGURATION, &CWinNfsGraphView::OnConfiguration)
    ON_UPDATE_COMMAND_UI(ID_SETTINGS_CONFIGURATION, &CWinNfsGraphView::OnUpdateConfiguration)
    ON_COMMAND(ID_X_AXIS_ZOOMIN, &CWinNfsGraphView::OnXaxisZoomIn)
    ON_COMMAND(ID_X_AXIS_ZOOMOUT, &CWinNfsGraphView::OnXaxisZoomOut)
    ON_COMMAND(ID_Y_AXIS_ZOOMIN, &CWinNfsGraphView::OnYaxisZoomIn)
    ON_COMMAND(ID_Y_AXIS_ZOOMOUT, &CWinNfsGraphView::OnYaxisZoomOut)
    ON_COMMAND(ID_GRAPH_TYPE, &CWinNfsGraphView::OnToggleGraphType)
    ON_COMMAND(ID_SHOW_LEGEND, &CWinNfsGraphView::OnToggleLegend)
    ON_COMMAND(ID_MOVE_LEFT, &CWinNfsGraphView::OnMoveLeft)
    ON_COMMAND(ID_MOVE_RIGHT, &CWinNfsGraphView::OnMoveRight)
    ON_COMMAND(ID_MOVE_UP, &CWinNfsGraphView::OnMoveUp)
    ON_COMMAND(ID_MOVE_DOWN, &CWinNfsGraphView::OnMoveDown)
    ON_COMMAND(ID_MOVE_ZERO_X, &CWinNfsGraphView::OnMoveZeroX)
    ON_COMMAND(ID_MOVE_ZERO_Y, &CWinNfsGraphView::OnMoveZeroY)
    ON_WM_SIZE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CWinNfsGraphView 생성/소멸

CWinNfsGraphView::CWinNfsGraphView()
:m_bMouseDown(FALSE)
, m_ptChangedMousePoint(0, 0)
, m_ptMousePoint(0, 0)
{
}

CWinNfsGraphView::~CWinNfsGraphView()
{
}

BOOL CWinNfsGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}


int CWinNfsGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    InitGraph();
    SetTimer(REDRAW_TIMER_ID, 1000 / SCROLL_FPS, NULL);

    GetDocument()->GetGraphSelector()->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST, CRect(0, 0, 0, 0), this, IDC_CB_GRAPH_SELECTOR);

    return 0;
}


void CWinNfsGraphView::OnClose()
{
    KillTimer(REDRAW_TIMER_ID);

    CView::OnClose();
}


// CWinNfsGraphView 그리기

void CWinNfsGraphView::OnDraw(CDC* pDC)
{
	CWinNfsGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GetDocument()->GetDrawManager()->Flip(pDC);
}


// CWinNfsGraphView 인쇄

BOOL CWinNfsGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWinNfsGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWinNfsGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CWinNfsGraphView 진단

#ifdef _DEBUG
void CWinNfsGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CWinNfsGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinNfsGraphDoc* CWinNfsGraphView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinNfsGraphDoc)));
	return (CWinNfsGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinNfsGraphView 메시지 처리기


void CWinNfsGraphView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    CDC *pDC = GetDC();
    GetDocument()->GetDrawManager()->ResizingGraph(pDC, cx, cy);
    ReleaseDC(pDC);

    GetDocument()->GetGraphSelector()->MoveWindow(cx - 120, 10, 100, 200, TRUE);
}


void CWinNfsGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
    if((nFlags & MK_LBUTTON) == MK_LBUTTON && m_bMouseDown == TRUE)
    {
        m_ptChangedMousePoint = point;
    }
    CView::OnMouseMove(nFlags, point);
}


void CWinNfsGraphView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_ptMousePoint = m_ptChangedMousePoint = point;
    m_bMouseDown = TRUE;

    CView::OnLButtonDown(nFlags, point);
}

void CWinNfsGraphView::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_bMouseDown = FALSE;

    CView::OnLButtonUp(nFlags, point);
}


BOOL CWinNfsGraphView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
    //return CView::OnEraseBkgnd(pDC);
}

void CWinNfsGraphView::InitGraph(void)
{
    m_ptChangedMousePoint.SetPoint(0, 0);
    m_ptMousePoint.SetPoint(0, 0);

    CRect rcClient;
    GetClientRect(rcClient);

    CDC *pDC = GetDC();
    
    KillTimer(REDRAW_TIMER_ID);
    Sleep(1000 / SCROLL_FPS);
    GetDocument()->GetDrawManager()->ClearResource();
    GetDocument()->GetDrawManager()->InitResource(pDC, rcClient.Width(), rcClient.Height());
    SetTimer(REDRAW_TIMER_ID, 1000 / SCROLL_FPS, NULL);

    GetDocument()->GetDrawManager()->ReDraw(pDC);
    ReleaseDC(pDC);

    Invalidate(FALSE);
}

void CWinNfsGraphView::RedrawGraph(void)
{
    CDC *pDC = GetDC();
    GetDocument()->GetDrawManager()->Scroll(m_ptChangedMousePoint.x - m_ptMousePoint.x, m_ptMousePoint.y - m_ptChangedMousePoint.y);
    GetDocument()->GetDrawManager()->ReDraw(pDC);
    ReleaseDC(pDC);

    Invalidate(FALSE);
}

void CWinNfsGraphView::OnTimer(UINT_PTR nIDEvent)
{
    static bool bStartTimer = false;

    if(nIDEvent == REDRAW_TIMER_ID && bStartTimer == false)
    {
        bStartTimer = true;    
    
        if(m_ptMousePoint != m_ptChangedMousePoint)
        {
            RedrawGraph();
            m_ptMousePoint = m_ptChangedMousePoint;
        }

        bStartTimer = false;
    }

    CView::OnTimer(nIDEvent);
}

void CWinNfsGraphView::OnConfiguration()
{
    CConfigDlg dlg(GetDocument()->GetNfsGraphManager(), GetDocument()->GetDrawManager(), this);
    dlg.DoModal();
}

void CWinNfsGraphView::OnUpdateConfiguration(CCmdUI *pCmdUI)
{
    if(!GetDocument()->IsLoadFile())
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->Enable(TRUE);
    }
}

void CWinNfsGraphView::OnXaxisZoomIn(void)
{
    MAG_LEVEL eLevel;
    eLevel = GetDocument()->GetNfsGraphManager()->GetMagX();
    if(eLevel == ML_10x) return;

    eLevel = (MAG_LEVEL)((LONG)eLevel - 1);

    GetDocument()->GetNfsGraphManager()->SetMagX((MAG_LEVEL)eLevel);
    RedrawGraph();
}

void CWinNfsGraphView::OnXaxisZoomOut(void)
{
    MAG_LEVEL eLevel;
    eLevel = (MAG_LEVEL)((LONG)GetDocument()->GetNfsGraphManager()->GetMagX() + 1);
    if(eLevel == ML_MAXOFLEVEL) return;

    GetDocument()->GetNfsGraphManager()->SetMagX((MAG_LEVEL)eLevel);
    RedrawGraph();
}

void CWinNfsGraphView::OnYaxisZoomIn(void)
{
    MAG_LEVEL eLevel;
    eLevel = GetDocument()->GetNfsGraphManager()->GetMagY();
    if(eLevel == ML_10x) return;

    eLevel = (MAG_LEVEL)((LONG)eLevel - 1);

    GetDocument()->GetNfsGraphManager()->SetMagY((MAG_LEVEL)eLevel);
    RedrawGraph();
}

void CWinNfsGraphView::OnYaxisZoomOut(void)
{
    MAG_LEVEL eLevel;
    eLevel = (MAG_LEVEL)((LONG)GetDocument()->GetNfsGraphManager()->GetMagY() + 1);
    if(eLevel == ML_MAXOFLEVEL) return;

    GetDocument()->GetNfsGraphManager()->SetMagY((MAG_LEVEL)eLevel);
    RedrawGraph();
}

void CWinNfsGraphView::OnToggleGraphType(void)
{
    GRAPH_TYPE eGraphType = GetDocument()->GetNfsGraphManager()->GetGraphType();

    if(eGraphType == GT_LINE) eGraphType = GT_BAR;
    else if(eGraphType == GT_BAR) eGraphType = GT_LINE;

    GetDocument()->GetNfsGraphManager()->SetGraphType((GRAPH_TYPE)eGraphType);
    RedrawGraph();
}

void CWinNfsGraphView::OnToggleLegend(void)
{
    bool bIsDrawLegend = GetDocument()->GetDrawManager()->IsDrawLegend();

    bIsDrawLegend = !bIsDrawLegend;

    GetDocument()->GetDrawManager()->SetDrawLegend(bIsDrawLegend);
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveLeft(void)
{
    GetDocument()->GetDrawManager()->Scroll(800, 0);
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveRight(void)
{
    GetDocument()->GetDrawManager()->Scroll(-800, 0);
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveUp(void)
{
    GetDocument()->GetDrawManager()->Scroll(0, -400);
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveDown(void)
{
    GetDocument()->GetDrawManager()->Scroll(0, 400);
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveZeroX(void)
{
    GetDocument()->GetDrawManager()->ScrollZeroX();
    RedrawGraph();
}

void CWinNfsGraphView::OnMoveZeroY(void)
{
    GetDocument()->GetDrawManager()->ScrollZeroY();
    RedrawGraph();
}