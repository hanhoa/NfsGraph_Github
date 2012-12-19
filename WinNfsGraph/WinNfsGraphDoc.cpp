
// WinNfsGraphDoc.cpp : CWinNfsGraphDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinNfsGraph.h"
#endif

#include "WinNfsGraphDoc.h"
#include "WinNfsGraphView.h"

#include "LoadingDlg.h"
#include "HotKeyDescDlg.h"

#include <propkey.h>
#include <process.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWinNfsGraphDoc

IMPLEMENT_DYNCREATE(CWinNfsGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinNfsGraphDoc, CDocument)
    ON_COMMAND(ID_FILE_OPENLOG, &CWinNfsGraphDoc::OnFileOpenLog)
    ON_COMMAND(ID_HELP_HOTKEYDESC, &CWinNfsGraphDoc::OnHotKeyDesc)
    ON_CBN_SELCHANGE(IDC_CB_GRAPH_SELECTOR, &CWinNfsGraphDoc::OnSelChangeGraphSelector)
END_MESSAGE_MAP()


// CWinNfsGraphDoc 생성/소멸

CWinNfsGraphDoc::CWinNfsGraphDoc()
:m_bLoadLogFile(FALSE)
{
	m_pNGM = new CNfsGraphManager();
    m_pDrawManager = new CDrawManager(m_pNGM);
}

CWinNfsGraphDoc::~CWinNfsGraphDoc()
{
    delete m_pDrawManager;
    delete m_pNGM;
}

BOOL CWinNfsGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//m_pNGM->ReadLogFile("SnoopInternalAccCycle", "SnoopInternalAccCycle.cfg");

	return TRUE;
}

struct ThreadData
{
    CNfsGraphManager *pNGM;
    std::string strFileName;
    std::string strCfgName;
};

unsigned int __stdcall ReadLogFileThread(void *pArg)
{
    ThreadData *pData = (ThreadData*)pArg;

    if(pData->pNGM->ReadLogFile(pData->strFileName, pData->strCfgName) == false)
    {
        return 1;
    }
    return 0;
}

void CWinNfsGraphDoc::OnFileOpenLog()
{
    char szFilter[] = "All Files(*.*)";
    CFileDialog cFD(TRUE, NULL, "*.*", OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, szFilter);
    if(cFD.DoModal() == IDCANCEL) return;

    ThreadData tData;
    tData.pNGM = m_pNGM;
    tData.strCfgName = (LPCSTR)cFD.GetPathName();
    std::string::size_type indexFind = tData.strCfgName.rfind('.');
    if(indexFind == std::string::npos)
        tData.strCfgName += ".cfg";
    else
    {
        tData.strCfgName.erase(indexFind);
        tData.strCfgName += ".cfg";
    }

    tData.strFileName = (LPCSTR)cFD.GetPathName();

    bool bExistCfgFile;
    std::ifstream inFile(tData.strCfgName.c_str());
    if(!inFile)
        bExistCfgFile = false;
    else
    {
        bExistCfgFile = true;
        inFile.close();
    }

    
    HANDLE hThread = (HANDLE)_beginthreadex(0, 0, ReadLogFileThread, (void*)&tData, 0, 0);

    CLoadingDlg cLoadingDlg(hThread);
    if(cLoadingDlg.DoModal() == IDCANCEL)
    {
        m_pNGM->StopReadingLogFile();
        WaitForSingleObject(hThread, INFINITE);

        m_pNGM->ClearResource();
        m_pNGM->InitResource();
    }
    else
    {
        DWORD nExitCode;
        GetExitCodeThread(hThread, &nExitCode);
        if(nExitCode == 1)
        {
            AfxMessageBox(m_pNGM->GetErrorMsg().c_str());
        }
        else
        {
            POSITION pos = GetFirstViewPosition();
            CWinNfsGraphView *pView = (CWinNfsGraphView*)GetNextView(pos);
            pView->InitGraph();

            CString strGraph;
            m_cbGraphSelector.ResetContent();
            for(U32 i = 1; i <= m_pNGM->GetTotalNumOfGraph(); i++)
            {
                strGraph.Format("Graph #%d", i);
                m_cbGraphSelector.AddString((LPCSTR)strGraph);
            }
            m_cbGraphSelector.SetCurSel(0);

            SetTitle((LPCSTR)cFD.GetPathName());

            m_strConfigFile = tData.strCfgName.c_str();
            m_bLoadLogFile = TRUE;

            if(!bExistCfgFile)
            {
                pView->OnConfiguration();
            }
        }
    }

    CloseHandle(hThread);
}

void CWinNfsGraphDoc::OnSelChangeGraphSelector()
{
    m_pNGM->SetCurGraphNum(m_cbGraphSelector.GetCurSel());
    m_pDrawManager->ChangeGraph();
 
    POSITION pos = GetFirstViewPosition();
    CWinNfsGraphView *pView = (CWinNfsGraphView*)GetNextView(pos);
    pView->RedrawGraph();
}

void CWinNfsGraphDoc::OnHotKeyDesc()
{
    CHotKeyDescDlg dlg;
    dlg.DoModal();
}

// CWinNfsGraphDoc serialization

void CWinNfsGraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CWinNfsGraphDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CWinNfsGraphDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWinNfsGraphDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWinNfsGraphDoc 진단

#ifdef _DEBUG
void CWinNfsGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinNfsGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWinNfsGraphDoc 명령
