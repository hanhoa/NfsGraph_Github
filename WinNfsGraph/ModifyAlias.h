#pragma once
#include "afxwin.h"


// CModifyAlias 대화 상자입니다.

class CModifyAlias : public CDialog
{
	DECLARE_DYNAMIC(CModifyAlias)

public:
	CModifyAlias(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModifyAlias();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MODIFYALIAS };

    void SetValue(CString strValue) { m_strValue = strValue; }
    void SetAlias(CString strAlias) { m_strAlias = strAlias; }

    CString GetValue(void) { return m_strValue; }
    CString GetAlias(void) { return m_strAlias; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
    CEdit m_editValue;
    CEdit m_editAlias;
    CString m_strValue;
    CString m_strAlias;
public:
    virtual BOOL OnInitDialog();
};
