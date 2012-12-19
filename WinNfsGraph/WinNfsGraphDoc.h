
// WinNfsGraphDoc.h : CWinNfsGraphDoc 클래스의 인터페이스
//

#pragma once

#include "DrawManager.h"

class CWinNfsGraphDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CWinNfsGraphDoc();
	DECLARE_DYNCREATE(CWinNfsGraphDoc)

// 특성입니다.
public:

// 작업입니다.
public:
    CDrawManager *GetDrawManager(void) { return m_pDrawManager; }
    CComboBox *GetGraphSelector(void) { return &m_cbGraphSelector; }
    CNfsGraphManager *GetNfsGraphManager(void) { return m_pNGM; }

    BOOL IsLoadFile(void) { return m_bLoadLogFile; }

    CString GetConfigFileName(void) { return m_strConfigFile; }

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
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

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
