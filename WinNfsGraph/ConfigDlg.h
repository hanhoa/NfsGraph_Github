#pragma once
#include "afxcmn.h"

#include "NfsGraphManager.h"
#include "DrawManager.h"
#include "afxwin.h"


// CConfigDlg ��ȭ �����Դϴ�.

class CWinNfsGraphView;
class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CNfsGraphManager *pNGM, CDrawManager *pDrawManager, CWinNfsGraphView * pView, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConfigDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CONFIGDLG };

private:
    void InitAliasList(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
    virtual BOOL OnInitDialog();
    virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:
    CNfsGraphManager *m_pNGM;
    CDrawManager *m_pDrawManager;
    CWinNfsGraphView * m_pView;

    CListCtrl m_listAlias;
    CListCtrl m_listMainData;
    CListCtrl m_listLegendData;
    CComboBox m_cmbMagX;
    CComboBox m_cmbMagY;
    CComboBox m_cmbGraphType;  

    BOOL m_bShowLegend;

public:
    afx_msg void OnNMDblclkListAlias(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawListMaindata(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawListLegenddata(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkListMaindata(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkListLegenddata(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCbnSelchangeCmbMagX();
    afx_msg void OnCbnSelchangeCmbMagY();
    afx_msg void OnCbnSelchangeCmbGraphType();
    afx_msg void OnBnClickedChkShowLegend();
};
