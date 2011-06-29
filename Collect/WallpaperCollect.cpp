// PaperCol.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"

#define WallpaperCollect_EXPORTS

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
	gPathInfo->SaveUrlMap();
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
					else if ("PaginationKey" == thdNodeStr)
					{
						InitPaginationKeyInfo(thdNode, siteInfo);
					}
					else if ("ChannelKey" == thdNodeStr)
					{
						InitChannelKeyInfo(thdNode, siteInfo);
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
	TiXmlElement *curKeyElm = thdNode->FirstChildElement();
	while (curKeyElm)
	{
		string childnode = curKeyElm->Value();
		if (keyArr[0][0] == childnode)
			picShowPageKey.picNameKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[0][1] == childnode)
			picShowPageKey.picNameL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[0][2] == childnode)
			picShowPageKey.picNameR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[0][3] == childnode)
			picShowPageKey.picUrlKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[0][4] == childnode)
			picShowPageKey.picUrlL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[0][5] == childnode)
			picShowPageKey.picUrlR = curKeyElm->GetText() ? curKeyElm->GetText() : "";

		curKeyElm = curKeyElm->NextSiblingElement();
	}
	siteInfo.picShowPageKey = picShowPageKey;
}

void CWallpaperCollect::InitLevel2PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo ) 
{
	TPicsShowPageKey picsShowPageKey;
	TiXmlElement *curKeyElm = thdNode->FirstChildElement();
	while (curKeyElm)
	{
		string childnode = curKeyElm->Value();
		if (keyArr[1][0] == childnode)
			picsShowPageKey.nameKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[1][1] == childnode)
			picsShowPageKey.nameL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[1][2] == childnode)
			picsShowPageKey.nameR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[1][3] == childnode)
			picsShowPageKey.urlKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[1][4] == childnode)
			picsShowPageKey.urlL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[1][5] == childnode)
			picsShowPageKey.urlR = curKeyElm->GetText() ? curKeyElm->GetText() : "";

		curKeyElm = curKeyElm->NextSiblingElement();
	}
	siteInfo.picsShowPageKey = picsShowPageKey;
}

void CWallpaperCollect::InitLevel3PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo ) 
{
	TPackagePageKey packagePageKey;
	TiXmlElement *curKeyElm = thdNode->FirstChildElement();
	while (curKeyElm)
	{
		string childnode = curKeyElm->Value();
		if (keyArr[2][0] == childnode)
			packagePageKey.nameKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[2][1] == childnode)
			packagePageKey.nameL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[2][2] == childnode)
			packagePageKey.nameR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[2][3] == childnode)
			packagePageKey.urlKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[2][4] == childnode)
			packagePageKey.urlL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if (keyArr[2][5] == childnode)
			packagePageKey.urlR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("thumbnailUrlL" == childnode)
			packagePageKey.thumbnailUrlL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("thumbnailUrlR" == childnode)
			packagePageKey.thumbnailUrlR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("thumbnailNameL" == childnode)
			packagePageKey.thumbnailNameL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("thumbnailNameR" == childnode)
			packagePageKey.thumbnailNameR = curKeyElm->GetText() ? curKeyElm->GetText() : "";


		curKeyElm = curKeyElm->NextSiblingElement();
	}
	siteInfo.packagePageKey = packagePageKey;
}

void CWallpaperCollect::InitPaginationKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo )
{
	TPaginationKey paginationKey;
	TiXmlElement *curKeyElm = thdNode->FirstChildElement();
	while (curKeyElm)
	{
		string childNode = curKeyElm->Value();
		if ("divKey" == childNode)
			paginationKey.divKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("indexKey" == childNode)
			paginationKey.indexKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("indexL" == childNode)
			paginationKey.indexL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("indexR" == childNode)
			paginationKey.indexR = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("currentKey" == childNode)
			paginationKey.currentKey = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("currentL" == childNode)
			paginationKey.currentL = curKeyElm->GetText() ? curKeyElm->GetText() : "";
		else if ("currentR" == childNode)
			paginationKey.currentR = curKeyElm->GetText() ? curKeyElm->GetText() : "";

		curKeyElm = curKeyElm->NextSiblingElement();
	}
	siteInfo.paginationKey = paginationKey;
}

void CWallpaperCollect::InitChannelKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo )
{
	TChannelKey channelKey;
	TiXmlElement *curKeyElm = thdNode->FirstChildElement();
	while (curKeyElm)
	{
		string childNode = curKeyElm->Value();
		if ("srcUrl" == childNode)
			channelKey.srcPageUrl = curKeyElm->GetText() ? curKeyElm->GetText() : "";

		curKeyElm = curKeyElm->NextSiblingElement();
	}
	siteInfo.channelKey = channelKey;
}

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////

// 获取频道信息，保存到TChannelAttri中
bool CWallpaperCollect::ColChannelTree(TChannelAttri& channelInfo)
{
	if (!pCurSite) return false;

	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pCurSite->channelKey.srcPageUrl);

	CHtmlParse parser(pageHtml);
	channelInfo = parser.GetChannelInfo(*pCurSite);
	return true;
}

// 除不马上下载外，功能同ColFromPackagePages
bool CWallpaperCollect::GetPackagePagesInfo( const string& pageUrl, TPackagePageAttri& collectInfo )
{
	TPaginationAttri paginationInfo;
	if (!GetPaginationInfo(pageUrl, paginationInfo))
		return false;
	
	if (paginationInfo.maxPage <= 1)
		GetPackagePageInfo(pageUrl, collectInfo);
	else
	{
		GetPackagePageInfo(paginationInfo.pageUrlBase, collectInfo);
		for (int i = 2; i < paginationInfo.maxPage; i++)
		{
			char indexStr[4];
			itoa(i, indexStr, 10);
			string url = paginationInfo.pageUrlBase + "/" + indexStr;
			GetPackagePageInfo(url, collectInfo);
		}
	}
	return true;
}

// 除不马上下载外，功能同ColFromPackagePage
bool CWallpaperCollect::GetPackagePageInfo( const string& pageUrl, TPackagePageAttri& collectInfo )
{
	if (!pCurSite) return false;

	// 获取网页源码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析得到level2页面的url，保存
	CHtmlParse parser(pageHtml);
	collectInfo = parser.GetLevel2PageUrls(*pCurSite);
	if (collectInfo.name.length() <= 1)
		return false;
	return true;
}

// 查找是否页面中有上下页信息，若有对每个页面调用ColFromPackagePage()
bool CWallpaperCollect::ColFromPackagePages(const string& pageUrl, const wstring& rootPath)
{
	TPaginationAttri paginationInfo;
	if (!GetPaginationInfo(pageUrl, paginationInfo))
		return false;

	// 解析得到
	if (paginationInfo.maxPage <= 1)
		ColFromPackagePage(pageUrl, rootPath);
	else
	{
		ColFromPackagePage(paginationInfo.pageUrlBase, rootPath);
		for (int i = 2; i < paginationInfo.maxPage; i++)
		{
			char indexStr[4];
			itoa(i, indexStr, 10);
			string url = paginationInfo.pageUrlBase + "/" + indexStr;
			ColFromPackagePage(url, rootPath);
		}
	}
	return true;
}

bool CWallpaperCollect::GetPaginationInfo(const string &pageUrl, TPaginationAttri& paginationInfo) 
{
	if (!pCurSite) return false;

	// 获取网页源码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析判断是否包含上下页信息
	CHtmlParse parser(pageHtml);
	paginationInfo = parser.GetPageIndexInfo(*pCurSite);

	// 
	string separateStr;
	if (paginationInfo.curPage > 1)
		separateStr = "/";
	else
		separateStr = ".htm";
	int sepPos = pageUrl.rfind(separateStr);
	paginationInfo.pageUrlBase = pageUrl.substr(0, sepPos);

	return true;
}

// 分析页面内容，每取得包含(level2)页面后，调用ColFromPicListPage处理
// 如http://www.deskcity.com/details/index/152.html
bool CWallpaperCollect::ColFromPackagePage(const string& pageUrl, const wstring& rootPath)
{
	TPackagePageAttri collectInfo;
	if (!GetPackagePageInfo(pageUrl, collectInfo))
		return false;

	// 解析得到合集名，设置壁纸保存文件夹名
	collectInfo.name = splitFirstString(collectInfo.name);
	wstring curSaveDir = rootPath + collectInfo.name + _T("\\");
	MakeSurePathExists(curSaveDir.c_str(), false);

	// 调用ColFromPicListPage
	size_t count = collectInfo.collectInfoVec.size();
	for (size_t i = 0; i < count; i++)
	{
		ColFromPicListPage(collectInfo.collectInfoVec[i].linkUrl, curSaveDir);
	}
	return true;
}

// 分析页面内容，每取得包含单张壁纸(level1)的页面后，调用ColFromPicViewPage处理
// 如http://www.deskcity.com/details/picture/4074.html
bool CWallpaperCollect::ColFromPicListPage( const string& pageUrl, const wstring& rootPath )
{
	if (!pCurSite) return false;
	if (gPathInfo->pageLoaded(pageUrl)) 
		return false;

	// 获取网页源代码
	CWebServer webServ;
	string pageHtml = webServ.ColPageSourceHtml(pageUrl);

	// 解析得到显示壁纸页面的url，存入数组
	CHtmlParse parser(pageHtml);
	TPicsShowPageAttri picsShowPageArr;
	picsShowPageArr = parser.GetLevel1PageUrls(*pCurSite);
	if (picsShowPageArr.name.length() <= 1)
		return false;

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

	// 当前辑的壁纸已下载，存入url，下次遇到相同url时不再解析
	gPathInfo->InsertUrlToFile(pageUrl); 
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
	if (picShowPageAttri.picName.length() <= 1 ||
		picShowPageAttri.picUrl.length() <= 1)
		return false;

	USES_CONVERSION;
	wchar *picNameExt = A2W(pCurSite->picShowPageKey.picUrlR.c_str());
	wstring filePath = rootPath + picShowPageAttri.picName + picNameExt;

	// TODO:处理图片已存在

	// 下载图片保存到指定目录
	webServ.DownLoadFile(picShowPageAttri.picUrl, filePath);

	return true;
}