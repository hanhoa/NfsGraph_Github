
// WinNfsGraph.h : WinNfsGraph ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CWinNfsGraphApp:
// �� Ŭ������ ������ ���ؼ��� WinNfsGraph.cpp�� �����Ͻʽÿ�.
//

class CWinNfsGraphApp : public CWinApp
{
public:
	CWinNfsGraphApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinNfsGraphApp theApp;
