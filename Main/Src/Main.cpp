// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Main.h"

#include "WallpaperCollect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

void test();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		test(); 
	}

	return nRetCode;
}

void test()
{
	char szPath[MAX_PATH] = {0};
	string strPath;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\Cache\\");
	strPath = szPath;

	CWallpaperCollect wpCol;

	wpCol.SetSite("http://www.deskcity.com");
	wpCol.SetSaveDir(strPath);
	wpCol.ColFromPicViewPage("http://www.deskcity.com/details/show/4074/83985.html");
}