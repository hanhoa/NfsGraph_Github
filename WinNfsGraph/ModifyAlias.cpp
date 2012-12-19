// ModifyAlias.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "WinNfsGraph.h"
#include "ModifyAlias.h"
#include "afxdialogex.h"


// CModifyAlias ��ȭ �����Դϴ�.

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


// CModifyAlias �޽��� ó�����Դϴ�.


BOOL CModifyAlias::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_editAlias.SetFocus();
    m_editAlias.SetSel(0, -1);

    return FALSE;  // return TRUE unless you set the focus to a control
    // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
