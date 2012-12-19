
// WinNfsGraphDoc.h : CWinNfsGraphDoc Ŭ������ �������̽�
//

#pragma once

#include "DrawManager.h"

class CWinNfsGraphDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CWinNfsGraphDoc();
	DECLARE_DYNCREATE(CWinNfsGraphDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
    CDrawManager *GetDrawManager(void) { return m_pDrawManager; }
    CComboBox *GetGraphSelector(void) { return &m_cbGraphSelector; }
    CNfsGraphManager *GetNfsGraphManager(void) { return m_pNGM; }

    BOOL IsLoadFile(void) { return m_bLoadLogFile; }

    CString GetConfigFileName(void) { return m_strConfigFile; }

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CWinNfsGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
    CNfsGraphManager *m_pNGM;
    CDrawManager *m_pDrawManager;

    CComboBox m_cbGraphSelector;

    CString m_strConfigFile;

    BOOL m_bLoadLogFile;

private:
    afx_msg void OnFileOpenLog();
    afx_msg void OnSelChangeGraphSelector();
    afx_msg void OnHotKeyDesc();

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
