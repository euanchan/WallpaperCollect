// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Main.h"

#include "WallpaperCollect.h"
#include "ComDef.h"

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
	wchar_t szPath[MAX_PATH] = {0};
	wstring cachePath;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	wcscpy(wcsrchr(szPath, '\\'), _T("\\Cache\\"));
	cachePath = szPath;

	CWallpaperCollect wpCol;
	TChannelAttri channelAtt;

	wpCol.SetSite("http://www.deskcity.com/");
	wpCol.SetSaveDir(cachePath);
	//wpCol.ColChannelTree(channelAtt);
	wpCol.ColFromPackagePages("http://www.deskcity.com/details/index/152.html", cachePath);
	wpCol.SetSaveDir(cachePath);
	//wpCol.ColFromPicListPage("http://www.deskcity.com/details/picture/4074.html");
	//wpCol.ColFromPicViewPage("http://www.deskcity.com/details/show/4074/83985.html");

}