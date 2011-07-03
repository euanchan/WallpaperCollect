#ifndef COMDEF_H
#define COMDEF_H

#define ZMIMPORT
#define ZMEXPORT

#define ZMDLL_EXPORT __declspec(dllexport)

//基本类型定义
typedef char				int8;
typedef short				int16;
typedef long				int32;
typedef __int64				int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long		uint32;
typedef unsigned __int64	uint64;
typedef wchar_t				wchar;


#define MSG_UPDATE_TASK_LIST_PROCESS 0x0601  // wParam为已下载数，lParam为总任务数
#define MSG_UPDATE_CUR_PIC_PROCESS   0x0602  // wParam为百分比分子
#define MSG_UPDATE_CUR_PIC_NAME      0x0603  // 更新当前下载图片名称,wParm为字符串指针
#define MSG_THUMBNAIL_PIC_FINISHED   0x0604  // 缩略图下载完成

enum SiteType
{
	kSiteDeskCity
};

//////////////////////////////////////////////////////////////////////////
class TPicShowPageInfo
{
public:
	wstring picName;
	string picUrl;
};

class TSiteInfo;
// 包含实际壁纸链接的网页(pageLevel1)关键字
class TPicShowPageKey 
{
public:
	string picNameKey; // 壁纸名称关键字
	string picNameL;
	string picNameR;
	string picUrlKey;  // 壁纸Url关键字
	string picUrlL;
	string picUrlR;

	void Log(const string& siteName) const;
};

//////////////////////////////////////////////////////////////////////////
// 包含多个pageLevel1页面链接的网页(pageLevel2)关键字信息
class TPicsShowPageKey
{
public:
	string nameKey;  // 壁纸辑目录名称关键字
	string nameL;
	string nameR;
	string urlKey;  // 单个壁纸页面链接关键字
	string urlL;
	string urlR;

	void Log(const string& siteName) const;
};

class TPicsShowPageInfo
{
public:
	wstring  name;  // 壁纸合集名称
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
class TCollectInfo
{
public:
	int     index;          // 用于保存CImageList中的下标
	wstring displayName;    // 缩略图本地保存文件名
	wstring thumbSavePath;  // 缩略图本地保存路径
	string  thumbUrl;       // 缩略图图片url
	string  linkUrl;        // 缩略图所指向level2页面的url
};

// 包含多个pageLevel2页面链接的网页(pageLevel3)关键字信息
class TPackagePageKey
{
public:
	string nameKey;  // 壁纸合集目录名称关键字
	string nameL;
	string nameR;
	string urlKey;   // 壁纸辑页面链接关键字
	string urlL;
	string urlR;
	string thumbnailUrlL;  // 缩略图图片链接
	string thumbnailUrlR; 
	string thumbnailNameL; 
	string thumbnailNameR; 
};
class TPackagePageInfo
{
public:
	wstring name;      // 合集名称
	string  url;       // 当前合集链接
	vector<TCollectInfo> collectInfoVec;
};

//////////////////////////////////////////////////////////////////////////
// 上一页、下一页关键词信息
class TPaginationKey
{
public:
	string divKey;
	string indexKey;
	string indexL;
	string indexR;
	string currentKey;
	string currentL;
	string currentR;
};

class TPaginationInfo
{
public:
	TPaginationInfo():minPage(1), maxPage(1), curPage(1){}
	string pageUrlBase;
	string extentStr;
	size_t minPage;
	size_t curPage;
	size_t maxPage;
};

//////////////////////////////////////////////////////////////////////////
// 频道目录 关键字
class TChannelKey
{
public:
	string srcPageUrl;
};

typedef pair<string, string> TChannelNodeChild;  // pair<name, url>
typedef pair<string, vector<TChannelNodeChild> > TChannelNode;
typedef vector<TChannelNode> TChannelTree;  // vector<pair<rootName, childVec> >
// vector<pair<rootName, childTreeNodeVector>>
class TChannelInfo
{
public:
	string siteName;
	TChannelTree tree;
};
class TChannelStrInfo
{
public:
	int num;
	string channelName;
	string channelUrl;
	TChannelStrInfo()
		: num(0)
	{		
	}
	TChannelStrInfo(const TChannelStrInfo& strInfo)
	{
		num = strInfo.num;
		channelName = strInfo.channelName;
		channelUrl  = strInfo.channelUrl;
	}
};

//////////////////////////////////////////////////////////////////////////
// 站点所有关键词信息
class TSiteInfo
{
public:
	TPicShowPageKey  picShowPageKey;
	TPicsShowPageKey picsShowPageKey;
	TPackagePageKey  packagePageKey;
	TPaginationKey   paginationKey;
	TChannelKey      channelKey;
	string mainUrl;
	string siteName;
};

typedef vector<TSiteInfo> TSiteList;








// 壁纸链接、壁纸保存路径信息
typedef pair<string, wstring> TPicTaskInfo;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

typedef struct _TTIME
{
	_TTIME()
	{
		memset(this,0,sizeof(_TTIME));
	}
	uint16 wYear;						//[0--]
	uint8 wMonth;						//[1--12]
	uint8 wDay;							//[1--31]
	uint8 wHour;						//[0--23]
	uint8 wMinute;						//[0--59]
	uint8 wSecond;						//[0--59]
	uint16 wMilliseconds;				//[0--999]
}TTime,*LPTTIME;



#endif