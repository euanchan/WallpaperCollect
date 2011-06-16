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

TSiteList gSiteList;
CLogXml Log;
bool bGlobalValueInit = false;

#define WallpaperCollect_EXPORTS


CWallpaperCollect::CWallpaperCollect(void)
{
	if (!bGlobalValueInit)
	{
		Log.Init(L"log");
		LoadConfigFile();
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
				TChildpageKey childKey;
				TiXmlElement *siteElm = secNode->FirstChildElement();
				while (siteElm)
				{
					string childnode = siteElm->Value();
					if ("Name" == childnode)
						siteInfo.siteName = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("Site" == childnode)
						siteInfo.mainUrl = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicNameKey" == childnode)
						childKey.picNameKey = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicNameL" == childnode)
						childKey.picNameL = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicNameR" == childnode)
						childKey.picNameR = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicUrlKey" == childnode)
						childKey.picUrlKey = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicUrlL" == childnode)
						childKey.picUrlL = siteElm->GetText() ? siteElm->GetText() : "";
					else if ("HtmlPicUrlR" == childnode)
						childKey.picUrlR = siteElm->GetText() ? siteElm->GetText() : "";

					siteElm = siteElm->NextSiblingElement();
				}
				siteInfo.child = childKey;
				gSiteList.push_back(siteInfo);

				Log.AddLog(siteInfo.siteName.c_str());
			}
			else
			{

			}
			secNode = root->NextSiblingElement();
		}
		bGlobalValueInit = true;
		Log.Save();
	}
	return true;
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

// 分析页面内容，每取得包含单张壁纸的页面后，调用ColFromPicViewPage处理
bool CWallpaperCollect::ColFromPicListPage( const string& pageUrl )
{
	return false;
}

// 分析页面内容，取得单张壁纸的url，根据url下载图片
bool CWallpaperCollect::ColFromPicViewPage( const string& pageUrl )
{
	if (!pCurSite) return false;

	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析获得壁纸的链接、壁纸相关信息
	CHtmlParse parser(pageHtml);
	TChildpageKey htmlKey;
	THtmlPicAttri htmlPic;
	htmlKey.Assign(*pCurSite);
	htmlPic = parser.GetWallpaperImgUrl(htmlKey);

	// 处理获得的图片url
	htmlPic.picUrl.insert(0, siteUrl.c_str());

	USES_CONVERSION;
	wchar *picNameExt = A2W(htmlKey.picUrlR.c_str());

	wstring filePath = saveDir + htmlPic.picName + picNameExt;

	// 下载图片保存到指定目录
	webServ.DownLoadFile(htmlPic.picUrl, filePath);

	return true;
}