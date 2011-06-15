// PaperCol.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "WallpaperCollect.h"
#include "WebServer.h"
#include "HtmlParse.h"

#define WallpaperCollect_EXPORTS

// CWinApp theApp;
// 
// int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
// {
// 	int nRetCode = 0;
// 
// 	// 初始化 MFC 并在失败时显示错误
// 	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
// 	{
// 		// TODO: 更改错误代码以符合您的需要
// 		_tprintf(_T("错误: MFC 初始化失败\n"));
// 		nRetCode = 1;
// 	}
// 	else
// 	{
// 		// TODO: 在此处为应用程序的行为编写代码。
// 	}
// 
// 	return nRetCode;
// }


CWallpaperCollect::CWallpaperCollect(void)
{
}

CWallpaperCollect::~CWallpaperCollect(void)
{
}

void CWallpaperCollect::SetSite(const string& url)
{
	siteUrl = url;
	if ((*siteUrl.rbegin()) != '/')
		this->siteUrl.append("/");
}

void CWallpaperCollect::SetSaveDir(const string& saveDir)
{
	this->saveDir = saveDir;
	if ((*saveDir.rbegin()) != '\\')
		this->saveDir.append("\\");
}

// 分析页面内容，每取得包含单张壁纸的页面后，调用ColFromPicViewPage处理
bool CWallpaperCollect::ColFromPicListPage(const string& pageUrl)
{
	return false;
}

// 分析页面内容，取得单张壁纸的url，根据url下载图片
bool CWallpaperCollect::ColFromPicViewPage(const string& pageUrl)
{
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析获得壁纸的链接、壁纸相关信息
	CHtmlParse parser(pageHtml);
	HtmlKeyStruct htmlKey;
	HtmlPicStruct htmlPic;
	htmlKey.picNameKey = "imginfo";
	htmlKey.picNameL = "<strong>";
	htmlKey.picNameR = "</strong>";
	htmlKey.picUrlKey = "s_img";
	htmlKey.picUrlL = "src=\"";
	htmlKey.picUrlR = ".jpg";
	htmlPic = parser.GetWallpaperImgUrl(htmlKey);

	// 处理获得的图片url
	htmlPic.picUrl.insert(0, siteUrl.c_str());

	string filePath = saveDir + htmlPic.picName + htmlKey.picUrlR;

	// 下载图片保存到指定目录
	webServ.DownLoadFile(htmlPic.picUrl, filePath);

	return true;
}