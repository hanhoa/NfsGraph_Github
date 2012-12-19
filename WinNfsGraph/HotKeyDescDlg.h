#pragma once


// CHotKeyDescDlg 대화 상자입니다.

class CHotKeyDescDlg : public CDialog
{
	DECLARE_DYNAMIC(CHotKeyDescDlg)

public:
	CHotKeyDescDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHotKeyDescDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HOTKEYDESCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
