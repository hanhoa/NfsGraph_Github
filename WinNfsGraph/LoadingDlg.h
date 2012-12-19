#pragma once


// CLoadingDlg 대화 상자입니다.

class CLoadingDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(HANDLE hThread);   // 표준 생성자입니다.
	virtual ~CLoadingDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOADINGDLG };

private:
    CLoadingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.

    HANDLE m_hThread;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual void OnCancel();
};
