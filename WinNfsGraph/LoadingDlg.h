#pragma once


// CLoadingDlg ��ȭ �����Դϴ�.

class CLoadingDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(HANDLE hThread);   // ǥ�� �������Դϴ�.
	virtual ~CLoadingDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOADINGDLG };

private:
    CLoadingDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.

    HANDLE m_hThread;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual void OnCancel();
};
