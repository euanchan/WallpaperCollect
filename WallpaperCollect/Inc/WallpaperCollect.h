#ifndef WALLPAPERCOLLECT_H
#define WALLPAPERCOLLECT_H

#ifdef WallpaperCollect_EXPORTS
#define WallpaperCollect_API __declspec(dllexport)
#else
#define WallpaperCollect_API __declspec(dllimport)
#endif

using std::wstring;
using std::string;

class TSiteInfo;
class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect(void);
	~CWallpaperCollect(void);

	void SetSite(const string& url);
	void SetSaveDir(const wstring& saveDir);
	// bool ParseAndCollect(const char* url);


	// 从一个展示多个壁纸的页面获取壁纸，
	// 如http://www.deskcity.com/details/picture/4074.html
	bool ColFromPicListPage(const string& pageUrl);

	// 从一个包含单张完整壁纸的页面获取壁纸，
	// 如http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl);

private:
	bool LoadConfigFile();

private:
// 	CWebServer* webServ;
// 	CHtmlParse* parser;
	string     siteUrl;  // 主域名
	wstring     saveDir;  // 壁纸保存路径
	TSiteInfo* pCurSite;  // 设置siteUrl后更新
};
#endif