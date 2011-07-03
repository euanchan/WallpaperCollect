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
class TChannelInfo;
class CNet;

#include "RawThread.h"
#include "RawCriSection.h"

enum ECmdType
{
	ECmdColPackagePages,  // 调用ColFromPackagePages()
	ECmdColPicListPage    // 调用ColFromPicListPage()
};

typedef struct  
{
	string url;
	wstring savePath;
	ECmdType cmdType;
}TCollectTaskInfo;

extern HANDLE ghNetEvent;
extern HANDLE ghWpCollEvent;
extern HWND   gWindowHandle;

// 将hNetEvent、hWpCollEvent设为有信号状态
__declspec(dllexport) bool SetWallpaperCollectEvent();

// 若需要从Collect.dll中发送消息，传入接收消息的窗口句柄
__declspec(dllexport) void SetMsgRecvWindowH(HWND windowHandle);

class WallpaperCollect_API CWallpaperCollect
{
public:
	CWallpaperCollect();
	~CWallpaperCollect(void);

	void SetSite(const char* url);
// 	void SetSaveDir(const wstring& saveDir);
	// bool ParseAndCollect(const char* url);

	// 获取频道信息，保存到TChannelAttri中
	bool ColChannelTree(TChannelInfo* channelInfo);

	// 除不马上下载外，功能同ColFromPackagePages
	bool GetPackagePagesInfo(const string& pageUrl,  TPackagePageInfo* collectInfo);
	// 除不马上下载外，功能同ColFromPackagePage
	bool GetPackagePageInfo(const string& pageUrl,  TPackagePageInfo* collectInfo);

	// 从一个合集(包含多个level2链接)页面获取壁纸, 如http://www.deskcity.com/details/index/152.html
	bool ColFromPackagePage(const string& pageUrl, const wstring& rootPath);
	// 若分为多页，全部获取
	bool ColFromPackagePages(const string& pageUrl, const wstring& rootPath);

	bool GetPaginationInfo(const string &pageUrl, TPaginationInfo& paginationInfo);

	// 从一个多壁纸展示(包含多个level1链接)页面(level2)获取壁纸， 如http://www.deskcity.com/details/picture/4074.html
	bool ColFromPicListPage(const string& pageUrl, const wstring& rootPath);


	//////////////////////////////////////////////////////////////////////////
	bool GetPicViewPageInfo(const string& pageUrl, const wstring& rootPath, TPicShowPageInfo& picPageInfo, wstring& savePath);

	// 从一个包含单张完整壁纸的页面(level1)获取壁纸，如http://www.deskcity.com/details/show/4074/83985.html
	bool ColFromPicViewPage(const string& pageUrl, const wstring& rootPath);


public:
	//////////////////////////////////////////////////////////////////////////
	// 在新建的线程中添加下载任务
	void AddTask(const string& url, const wstring& savePath, ECmdType type);
	void StartDownload();
	void StopDownload();

private:
	bool LoadConfigFile();

	void InitLevel1PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel2PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitLevel3PageKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitPaginationKeyInfo( TiXmlElement * thdNode, TSiteInfo &siteInfo );
	void InitChannelKeyInfo   ( TiXmlElement * thdNode, TSiteInfo &siteInfo );

private:
	CNet*      net;
	TSiteInfo* curSiteInfo;  // 设置siteUrl后更新

private:
	//////////////////////////////////////////////////////////////////////////
	static void ThreadFunc( void* aParam );
	void DoWork();

	vector<TCollectTaskInfo> taskInfoVec;
	vector<TCollectTaskInfo>::iterator iter;

	bool onWork;
	CRawThread    rawThread;
	CRawCriSection rawCrisection;
};
#endif