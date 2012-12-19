// ModifyAlias.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WinNfsGraph.h"
#include "ModifyAlias.h"
#include "afxdialogex.h"


// CModifyAlias 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModifyAlias, CDialog)

CModifyAlias::CModifyAlias(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyAlias::IDD, pParent)
    , m_strValue(_T(""))
    , m_strAlias(_T(""))
{

}

CModifyAlias::~CModifyAlias()
{
}

void CModifyAlias::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VALUE, m_editValue);
    DDX_Control(pDX, IDC_EDIT_ALIAS, m_editAlias);
    DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
    DDX_Text(pDX, IDC_EDIT_ALIAS, m_strAlias);
}


BEGIN_MESSAGE_MAP(CModifyAlias, CDialog)
END_MESSAGE_MAP()


// CModifyAlias 메시지 처리기입니다.


BOOL CModifyAlias::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_editAlias.SetFocus();
    m_editAlias.SetSel(0, -1);

    return FALSE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
