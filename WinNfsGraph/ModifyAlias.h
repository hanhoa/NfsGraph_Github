#pragma once
#include "afxwin.h"


// CModifyAlias ��ȭ �����Դϴ�.

class CModifyAlias : public CDialog
{
	DECLARE_DYNAMIC(CModifyAlias)

public:
	CModifyAlias(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModifyAlias();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MODIFYALIAS };

    void SetValue(CString strValue) { m_strValue = strValue; }
    void SetAlias(CString strAlias) { m_strAlias = strAlias; }

    CString GetValue(void) { return m_strValue; }
    CString GetAlias(void) { return m_strAlias; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
    CEdit m_editValue;
    CEdit m_editAlias;
    CString m_strValue;
    CString m_strAlias;
public:
    virtual BOOL OnInitDialog();
};
