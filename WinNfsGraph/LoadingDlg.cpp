// LoadingDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WinNfsGraph.h"
#include "LoadingDlg.h"
#include "afxdialogex.h"

#define TIMER_ID        0x3657

// CLoadingDlg ��ȭ �����Դϴ�.

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


// CLoadingDlg �޽��� ó�����Դϴ�.


BOOL CLoadingDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetTimer(TIMER_ID, 100, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
