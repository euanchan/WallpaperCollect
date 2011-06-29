#ifndef WALLPAPERCOLLECT_H
#define WALLPAPERCOLLECT_H

#ifdef WallpaperCollect_EXPORTS
#define WallpaperCollect_API __declspec(dllexport)
#else
#define WallpaperCollect_API __declspec(dllimport)
#endif

using std::wstring;
using std::string;

class TiXmlElement;
class TSiteInfo;
class TChannelAttri;
class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect(void);
	~CWallpaperCollect(void);

	void SetSite(const string& url);
	void SetSaveDir(const wstring& saveDir);
	// bool ParseAndCollect(const char* url);

	// 获取频道信息，保存到TChannelAttri中
	bool ColChannelTree(TChannelAttri& channelInfo);

	// 除不马上下载外，功能同ColFromPackagePages
	bool GetPackagePagesInfo(const string& pageUrl,  TPackagePageAttri& collectInfo);
	// 除不马上下载外，功能同ColFromPackagePage
	bool GetPackagePageInfo(const string& pageUrl,  TPackagePageAttri& collectInfo);

	// 从一个合集(包含多个level2链接)页面获取壁纸, 如http://www.deskcity.com/details/index/152.html
	bool ColFromPackagePage(const string& pageUrl, const wstring& rootPath);
	// 若分为多页，全部获取
	bool ColFromPackagePages(const string& pageUrl, const wstring& rootPath);

	bool GetPaginationInfo(const string &pageUrl, TPaginationAttri& paginationInfo);

	// 从一个多壁纸展示(包含多个level1链接)页面(level2)获取壁纸， 如http://www.deskcity.com/details/picture/4074.html
	bool ColFromPicListPage(const string& pageUrl, const wstring& rootPath);

	// 从一个包含单张完整壁纸的页面(level1)获取壁纸，如http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl, const wstring& rootPath);

private:
	bool LoadConfigFile();

	void InitLevel1PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel2PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel3PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitPaginationKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitChannelKeyInfo   ( TiXmlElement * thdNode, TSiteInfo &siteInfo );

private:
// 	CWebServer* webServ;
// 	CHtmlParse* parser;
	string     siteUrl;  // 主域名
	wstring     saveDir;  // 壁纸保存路径
	TSiteInfo* pCurSite;  // 设置siteUrl后更新
};
#endif