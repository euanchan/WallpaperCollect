// PaperCol.cpp : 定义 DLL 应用程序的入口点。
//

#include  <atlbase.h>

#include "stdafx.h"
#include "WallpaperCollect.h"
#include "WebServer.h"
#include "HtmlParse.h"
#include "tinyxml.h"
#include "Log.h"
#include "Tool.h"
#include "PathInfo.h"

TSiteList gSiteList;
CLogXml Log;
bool bGlobalValueInit = false;
string keyArr[][6] = 
{
	{  // level1. 
		"picShowNameKey", "picShowNameL", "picShowNameR", 
		"picShowUrlKey", "picShowUrlL", "picShowUrlR",
	},
	{  // level2.
		"picsShowNameKey", "picsShowNameL", "picsShowNameR", 
		"picsShowUrlKey", "picsShowUrlL", "picsShowUrlR",
	},
	{
		"packageNameKey", "packageNameL", "packageNameR", 
		"packageUrlKey", "packageUrlL", "packageUrlR"
	}
};

#define WallpaperCollect_EXPORTS


CWallpaperCollect::CWallpaperCollect(void)
{
	if (!bGlobalValueInit)
	{
		Log.Init(L"log");
		LoadConfigFile();
		if (gPathInfoPtr == NULL)
		{
			gPathInfoPtr = new CPathInfo();
			gPathInfo.InitPathInfo();
		}
	}
}

CWallpaperCollect::~CWallpaperCollect(void)
{
}

bool CWallpaperCollect::LoadConfigFile()
{
	char szPath[MAX_PATH] = {0};
	string configFile;
	::GetModuleFileNameA(NULL, szPath, sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\config.xml");
	configFile = szPath;

	TiXmlDocument xmlDoc;
	if (xmlDoc.LoadFile(configFile.c_str()))
	{
		TiXmlElement *root = xmlDoc.RootElement();
		if (!root)
			return false;

		string strRoot = root->Value();
		if (0 != strcmp(strRoot.c_str(), "WallpaperCollection"))
			return false;

		TiXmlElement *secNode = root->FirstChildElement();
		while (secNode)
		{
			string strNodeV = secNode->Value();
			if (0 == strcmp(strNodeV.c_str(), "WallpaperSite"))
			{
				TSiteInfo  siteInfo;
				TiXmlElement *thdNode = secNode->FirstChildElement();
				while (thdNode)
				{
					string thdNodeStr = thdNode->Value();
					if ("Name" == thdNodeStr)
						siteInfo.siteName = thdNode->GetText() ? thdNode->GetText() : "";
					else if ("Site" == thdNodeStr)
						siteInfo.mainUrl = thdNode->GetText() ? thdNode->GetText() : "";
					else if ("Level1PageKey" == thdNodeStr)
					{
						InitLevel1PageKeyInfo(thdNode, siteInfo);
					}
					else if ("Level2PageKey" == thdNodeStr)
					{
						InitLevel2PageKeyInfo(thdNode, siteInfo);
					}
					else if ("Level3PageKey" == thdNodeStr)
					{
						InitLevel3PageKeyInfo(thdNode, siteInfo);
					}
					else
					{
						;
					}
					thdNode = thdNode->NextSiblingElement();
				}

				gSiteList.push_back(siteInfo);
				Log.AddLog(siteInfo.siteName.c_str());
			}
			else  // strcmp(strNodeV.c_str(), "WallpaperSite") != 0
			{

			}
			secNode = root->NextSiblingElement();
		}
		bGlobalValueInit = true;
		Log.Save();
	}
	return true;
}


void CWallpaperCollect::InitLevel1PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo ) 
{
	TPicShowPageKey picShowPageKey;
	TiXmlElement *siteElm = thdNode->FirstChildElement();
	while (siteElm)
	{
		string childnode = siteElm->Value();
		if (keyArr[0][0] == childnode)
			picShowPageKey.picNameKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[0][1] == childnode)
			picShowPageKey.picNameL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[0][2] == childnode)
			picShowPageKey.picNameR = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[0][3] == childnode)
			picShowPageKey.picUrlKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[0][4] == childnode)
			picShowPageKey.picUrlL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[0][5] == childnode)
			picShowPageKey.picUrlR = siteElm->GetText() ? siteElm->GetText() : "";

		siteElm = siteElm->NextSiblingElement();
	}
	siteInfo.picShowPageKey = picShowPageKey;
}

void CWallpaperCollect::InitLevel2PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo ) 
{
	TPicsShowPageKey picsShowPageKey;
	TiXmlElement *siteElm = thdNode->FirstChildElement();
	while (siteElm)
	{
		string childnode = siteElm->Value();
		if (keyArr[1][0] == childnode)
			picsShowPageKey.nameKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[1][1] == childnode)
			picsShowPageKey.nameL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[1][2] == childnode)
			picsShowPageKey.nameR = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[1][3] == childnode)
			picsShowPageKey.urlKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[1][4] == childnode)
			picsShowPageKey.urlL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[1][5] == childnode)
			picsShowPageKey.urlR = siteElm->GetText() ? siteElm->GetText() : "";

		siteElm = siteElm->NextSiblingElement();
	}
	siteInfo.picsShowPageKey = picsShowPageKey;
}

void CWallpaperCollect::InitLevel3PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo ) 
{
	TPackagePageKey packagePageKey;
	TiXmlElement *siteElm = thdNode->FirstChildElement();
	while (siteElm)
	{
		string childnode = siteElm->Value();
		if (keyArr[2][0] == childnode)
			packagePageKey.nameKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[2][1] == childnode)
			packagePageKey.nameL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[2][2] == childnode)
			packagePageKey.nameR = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[2][3] == childnode)
			packagePageKey.urlKey = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[2][4] == childnode)
			packagePageKey.urlL = siteElm->GetText() ? siteElm->GetText() : "";
		else if (keyArr[2][5] == childnode)
			packagePageKey.urlR = siteElm->GetText() ? siteElm->GetText() : "";

		siteElm = siteElm->NextSiblingElement();
	}
	siteInfo.packagePageKey = packagePageKey;
}

void CWallpaperCollect::SetSite( const string& url )
{
	siteUrl = url;
	if ((*siteUrl.rbegin()) != '/')
		this->siteUrl.append("/");

	// 根据url中的信息在sitelist中找到匹配站点信息
	pCurSite = NULL;

	string siteName = url;
	size_t posL = siteName.find("www.");
	posL += 4;
	size_t posR = siteName.find(".", posL);
	siteName = siteName.substr(posL, posR - posL);

	size_t len = gSiteList.size();
	for (size_t i = 0; i < len; i++)
	{
		if (0 == strcmp(siteName.c_str(), gSiteList[i].siteName.c_str()))
		{
			pCurSite = &gSiteList[i];
			break;
		}
	}
}

void CWallpaperCollect::SetSaveDir(const wstring& saveDir)
{
	this->saveDir = saveDir;
	if ((*saveDir.rbegin()) != '\\')
		this->saveDir.append(_T("\\"));

	MakeSurePathExists(saveDir.c_str(), false);
}


// 分析页面内容，每取得包含(level2)页面后，调用ColFromPicListPage处理
// 如http://www.deskcity.com/details/index/152.html
bool CWallpaperCollect::ColFromPackagePage(const string& pageUrl, const wstring& rootPath)
{
	if (!pCurSite) return false;

	// 获取网页源码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析得到level2页面的url，保存
	CHtmlParse parser(pageHtml);
	TPackagePageAttri packagePageAtt;
	packagePageAtt = parser.GetLevel2PageUrls(*pCurSite);

	// 解析得到合集名，设置壁纸保存文件夹名
	packagePageAtt.name = splitFirstString(packagePageAtt.name);
	wstring curSaveDir = rootPath + packagePageAtt.name + _T("\\");
	MakeSurePathExists(curSaveDir.c_str(), false);

	// 调用ColFromPicListPage
	size_t count = packagePageAtt.urlArr.size();
	for (size_t i = 0; i < count; i++)
	{
		ColFromPicListPage(packagePageAtt.urlArr[i], curSaveDir);
	}
}

// 分析页面内容，每取得包含单张壁纸(level1)的页面后，调用ColFromPicViewPage处理
// 如http://www.deskcity.com/details/picture/4074.html
bool CWallpaperCollect::ColFromPicListPage( const string& pageUrl, const wstring& rootPath )
{
	if (!pCurSite) return false;

	// 获取网页源代码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析得到显示壁纸页面的url，存入数组
	CHtmlParse parser(pageHtml);
	TPicsShowPageAttri picsShowPageArr;
	picsShowPageArr = parser.GetLevel1PageUrls(*pCurSite);	

	// 解析TPicsShowPageAttri::name,设置壁纸保存文件夹名
	picsShowPageArr.name = splitFirstString(picsShowPageArr.name);
	wstring curSaveDir = rootPath + picsShowPageArr.name + _T("\\");
	MakeSurePathExists(curSaveDir.c_str(), false);
	
	// 调用ColFromPicViewPage下载图片
	size_t count = picsShowPageArr.urlArr.size();
	for (size_t i = 0; i < count; i++)
	{
		ColFromPicViewPage(picsShowPageArr.urlArr[i], curSaveDir);
	}
	return false;
}

// 分析页面内容，取得单张壁纸的url，根据url下载图片
// 如http://www.deskcity.com/details/show/4074/83985.html
bool CWallpaperCollect::ColFromPicViewPage( const string& pageUrl, const wstring& rootPath)
{
	if (!pCurSite) return false;

	// 获取网页源代码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析获得壁纸的链接、壁纸相关信息
	CHtmlParse parser(pageHtml);
	TPicShowPageAttri picShowPageAttri;
	picShowPageAttri = parser.GetWallpaperImgUrl(*pCurSite);

	USES_CONVERSION;
	wchar *picNameExt = A2W(pCurSite->picShowPageKey.picUrlR.c_str());
	wstring filePath = rootPath + picShowPageAttri.picName + picNameExt;

	// TODO:处理图片已存在

	// 下载图片保存到指定目录
	webServ.DownLoadFile(picShowPageAttri.picUrl, filePath);

	return true;
}