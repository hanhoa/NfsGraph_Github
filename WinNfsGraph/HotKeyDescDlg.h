#pragma once


// CHotKeyDescDlg ��ȭ �����Դϴ�.

class CHotKeyDescDlg : public CDialog
{
	DECLARE_DYNAMIC(CHotKeyDescDlg)

public:
	CHotKeyDescDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHotKeyDescDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HOTKEYDESCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
