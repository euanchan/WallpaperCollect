// PaperCol.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "WallpaperCollect.h"
#include "WebServer.h"
#include "HtmlParse.h"
#include "tinyxml.h"

TSitePairList siteList;
bool configfileLoaded = false;

#define WallpaperCollect_EXPORTS


CWallpaperCollect::CWallpaperCollect(void)
{
	if (!configfileLoaded)
		LoadConfigFile();
}

CWallpaperCollect::~CWallpaperCollect(void)
{
}

bool CWallpaperCollect::LoadConfigFile()
{
	char szPath[MAX_PATH] = {0};
	string configFile;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\config.xml");
	configFile = szPath;

	TiXmlDocument xmlDoc;
	if (xmlDoc.LoadFile(configFile.c_str(), TIXML_ENCODING_UTF8))
	{
		TiXmlElement *root = xmlDoc.RootElement();
		if (!root)
			return false;

		string strRoot = root->Value();
		if (0 != strcmp(strRoot.c_str(), "WallPaperCollection"))
			return false;

		TiXmlElement *secNode = root->FirstChildElement();
		while (secNode)
		{
			string strNodeV = secNode->Value();
			if (0 == strcmp(strNodeV.c_str(), "wallpaperSite"))
			{
				TSitePair sitePair;
				TSiteInfo  siteInfo;
				TChildpageKey childKey;
				TiXmlElement *siteElm = secNode->FirstChildElement();
				while (siteElm)
				{
					string childnode = siteElm->Value();
					if ("name" == childnode)
						sitePair.first = siteElm->GetText();
					else if ("site" == childnode)
						siteInfo.mainUrl = siteElm->GetText();
					else if ("htmlpicnamekey" == childnode)
						childKey.picNameKey = siteElm->GetText();
					else if ("htmlpicnamel" == childnode)
						childKey.picNameL = siteElm->GetText();
					else if ("htmlpicnamer" == childnode)
						childKey.picNameR = siteElm->GetText();
					else if ("htmlpicurlkey" == childnode)
						childKey.picUrlKey = siteElm->GetText();
					else if ("htmlpicurll" == childnode)
						childKey.picUrlL = siteElm->GetText();
					else if ("htmlpicurlr" == childnode)
						childKey.picUrlR = siteElm->GetText();

					siteElm = secNode->NextSiblingElement();
				}
				siteInfo.child = childKey;
				sitePair.second = siteInfo;
				siteList.push_back(sitePair);
			}
			else
			{

			}
			secNode = root->NextSiblingElement();
		}
		configfileLoaded = true;
	}
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
	TChildpageKey htmlKey;
	THtmlPicAtt htmlPic;
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