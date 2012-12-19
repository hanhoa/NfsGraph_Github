// ConfigDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WinNfsGraph.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"

#include "ModifyAlias.h"
#include "WinNfsGraphView.h"


// CConfigDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CNfsGraphManager *pNGM, CDrawManager *pDrawManager, CWinNfsGraphView * pView, CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
    , m_bShowLegend(FALSE)
    , m_pNGM(pNGM)
    , m_pDrawManager(pDrawManager)
    , m_pView(pView)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ALIAS, m_listAlias);
    DDX_Check(pDX, IDC_CHK_SHOW_LEGEND, m_bShowLegend);
    DDX_Control(pDX, IDC_CMB_MAG_X, m_cmbMagX);
    DDX_Control(pDX, IDC_CMB_MAG_Y, m_cmbMagY);
    DDX_Control(pDX, IDC_CMB_GRAPH_TYPE, m_cmbGraphType);
    DDX_Control(pDX, IDC_LIST_MAINDATA, m_listMainData);
    DDX_Control(pDX, IDC_LIST_LEGENDDATA, m_listLegendData);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALIAS, &CConfigDlg::OnNMDblclkListAlias)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MAINDATA, &CConfigDlg::OnNMCustomdrawListMaindata)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_LEGENDDATA, &CConfigDlg::OnNMCustomdrawListLegenddata)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_MAINDATA, &CConfigDlg::OnNMDblclkListMaindata)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_LEGENDDATA, &CConfigDlg::OnNMDblclkListLegenddata)
    ON_CBN_SELCHANGE(IDC_CMB_MAG_X, &CConfigDlg::OnCbnSelchangeCmbMagX)
    ON_CBN_SELCHANGE(IDC_CMB_MAG_Y, &CConfigDlg::OnCbnSelchangeCmbMagY)
    ON_CBN_SELCHANGE(IDC_CMB_GRAPH_TYPE, &CConfigDlg::OnCbnSelchangeCmbGraphType)
    ON_BN_CLICKED(IDC_CHK_SHOW_LEGEND, &CConfigDlg::OnBnClickedChkShowLegend)
END_MESSAGE_MAP()


// CConfigDlg 메시지 처리기입니다.

struct
{
    MAG_LEVEL eLevel;
    std::string strName;
} gMagLevelTable[] =
{
    {ML_10x, "10x"},
    {ML_5x, "5x"},
    {ML_2x, "2x"},
    {ML_1x, "1x"},
    {ML_1of2x, "1/2x"},
    {ML_1of5x, "1/5x"},
    {ML_1of10x, "1/10x"},
    {ML_1of20x, "1/20x"},
    {ML_1of50x, "1/50x"},
    {ML_1of100x, "1/100x"},
    {ML_1of200x, "1/200x"},
    {ML_1of500x, "1/500x"},
    {ML_1of1000x, "1/1000x"},
    {ML_Log2x, "Log2x"},
    {ML_Log5x, "Log5x"},
    {ML_Log10x, "Log10x"},
};

BOOL CConfigDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_listMainData.InsertColumn(0, "Title", LVCFMT_LEFT, 180);
    m_listLegendData.InsertColumn(0, "Title", LVCFMT_LEFT, 180);

    for(U32 i = 0; i < m_pNGM->GetNumOfParams(); i++)
    {
        m_listMainData.InsertItem(i, m_pNGM->GetDataTitle(i).c_str());
        m_listLegendData.InsertItem(i, m_pNGM->GetDataTitle(i).c_str());
    }

    m_listMainData.SetExtendedStyle(m_listMainData.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_listLegendData.SetExtendedStyle(m_listLegendData.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    for(U32 i = 0; i < (int)ML_MAXOFLEVEL; i++)
    {
        if(i < (U32)ML_Log2x) m_cmbMagX.AddString(gMagLevelTable[i].strName.c_str());
        m_cmbMagY.AddString(gMagLevelTable[i].strName.c_str());
    }

    m_cmbMagX.SetCurSel(m_pNGM->GetMagX());
    m_cmbMagY.SetCurSel(m_pNGM->GetMagY());

    m_cmbGraphType.AddString("Line");
    m_cmbGraphType.AddString("Bar");
    m_cmbGraphType.SetCurSel(m_pNGM->GetGraphType());

    m_bShowLegend = m_pDrawManager->IsDrawLegend() ? TRUE : FALSE;
    UpdateData(FALSE);

    m_listAlias.SetExtendedStyle(m_listAlias.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_listAlias.InsertColumn(0, "Value", LVCFMT_LEFT, 60);
    m_listAlias.InsertColumn(1, "Alias", LVCFMT_LEFT, 100);
    InitAliasList();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CConfigDlg::InitAliasList(void)
{
    m_listAlias.DeleteAllItems();

    U32 nLegendValue;
    CString strNumber;
    for(U32 i = 0; i < m_pDrawManager->GetLegend()->GetNumOfLegendItem(); i++)
    {
        nLegendValue = m_pDrawManager->GetLegend()->GetLegendValue(i);
        strNumber.Format("%d", nLegendValue);
        m_listAlias.InsertItem(i, strNumber);
        m_listAlias.SetItemText(i, 1, m_pNGM->GetLegendString(nLegendValue).c_str());
    }
}

void CConfigDlg::OnNMDblclkListAlias(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    CString strValue, strAlias;
    CModifyAlias dlg;

    strValue = m_listAlias.GetItemText(pNMItemActivate->iItem, 0);
    strAlias = m_listAlias.GetItemText(pNMItemActivate->iItem, 1);

    dlg.SetValue(strValue);
    dlg.SetAlias(strAlias);

    if(dlg.DoModal() == IDOK)
    {
        m_listAlias.SetItemText(pNMItemActivate->iItem, 1, dlg.GetAlias());

        U32 nValue;
        nValue = atoi((LPCSTR)strValue);
        m_pNGM->SetLegendString(pNMItemActivate->iItem, nValue, (LPCSTR)dlg.GetAlias());
        m_pView->RedrawGraph();
    }

    *pResult = 0;
}


void CConfigDlg::OnNMCustomdrawListMaindata(NMHDR *pNMHDR, LRESULT *pResult)
{
    //LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    NMLVCUSTOMDRAW *pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
    
    if(CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if(CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        if(m_pNGM->GetMainDataCol() == pLVCD->nmcd.dwItemSpec)
        {
            pLVCD->clrTextBk = PC_LIGHTBLUE;
            pLVCD->clrText = RGB(255, 255, 255);
        }

        *pResult = CDRF_DODEFAULT;
    }
}


void CConfigDlg::OnNMCustomdrawListLegenddata(NMHDR *pNMHDR, LRESULT *pResult)
{
    //LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    NMLVCUSTOMDRAW *pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

    if(CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        *pResult = CDRF_NOTIFYITEMDRAW;
    }
    else if(CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
    {
        if(m_pNGM->GetLegendCol() == pLVCD->nmcd.dwItemSpec)
        {
            pLVCD->clrTextBk = PC_LIGHTBLUE;
            pLVCD->clrText = RGB(255, 255, 255);
        }

        *pResult = CDRF_DODEFAULT;
    }
}


void CConfigDlg::OnNMDblclkListMaindata(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    m_pNGM->SetMainDataCol(pNMItemActivate->iItem);
    m_listMainData.Invalidate(TRUE);

    m_pDrawManager->ChangeGraph();
    m_pView->RedrawGraph();
    *pResult = 0;
}


void CConfigDlg::OnNMDblclkListLegenddata(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    m_pNGM->SetLegendCol(pNMItemActivate->iItem);
    m_listLegendData.Invalidate(TRUE);

    m_pDrawManager->ChangeGraph();
    m_pView->RedrawGraph();

    InitAliasList();
    *pResult = 0;
}


void CConfigDlg::OnCbnSelchangeCmbMagX()
{
    m_pNGM->SetMagX((MAG_LEVEL)m_cmbMagX.GetCurSel());
    m_pView->RedrawGraph();
}


void CConfigDlg::OnCbnSelchangeCmbMagY()
{
    m_pNGM->SetMagY((MAG_LEVEL)m_cmbMagY.GetCurSel());
    m_pView->RedrawGraph();
}


void CConfigDlg::OnCbnSelchangeCmbGraphType()
{
    m_pNGM->SetGraphType((GRAPH_TYPE)m_cmbGraphType.GetCurSel());
    m_pView->RedrawGraph();
}


void CConfigDlg::OnBnClickedChkShowLegend()
{
    UpdateData(TRUE);
    m_pDrawManager->SetDrawLegend(m_bShowLegend ? true : false);
    m_pView->RedrawGraph();
}

void CConfigDlg::OnOK()
{
    m_pNGM->SaveConfigFile((LPCSTR)m_pView->GetDocument()->GetConfigFileName());
    CDialog::OnOK();
}
