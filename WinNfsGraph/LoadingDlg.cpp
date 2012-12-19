// LoadingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WinNfsGraph.h"
#include "LoadingDlg.h"
#include "afxdialogex.h"

#define TIMER_ID        0x3657

// CLoadingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLoadingDlg, CDialog)

CLoadingDlg::CLoadingDlg(HANDLE hThread)
	: CDialog(CLoadingDlg::IDD, NULL)
{
    m_hThread = hThread;
}

CLoadingDlg::~CLoadingDlg()
{
}

void CLoadingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoadingDlg, CDialog)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CLoadingDlg 메시지 처리기입니다.


BOOL CLoadingDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetTimer(TIMER_ID, 100, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLoadingDlg::OnTimer(UINT_PTR nIDEvent)
{
    if(WaitForSingleObject(m_hThread, 0) == WAIT_OBJECT_0)
    {
        KillTimer(TIMER_ID);
        OnOK();
    }

    CDialog::OnTimer(nIDEvent);
}

void CLoadingDlg::OnCancel()
{
    KillTimer(TIMER_ID);
    CDialog::OnCancel();
}
