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


enum SiteType
{
	kSiteDeskCity
};

//////////////////////////////////////////////////////////////////////////
class TPicShowPageAttri
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

class TPicsShowPageAttri
{
public:
	wstring  name;  // 壁纸合集名称
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
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
};
class TPackagePageAttri
{
public:
	wstring name;
	vector<string> urlArr;
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

class TPaginationAttri
{
public:
	TPaginationAttri():minPage(1), maxPage(1), curPage(1){}
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
class TChannelAttri
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
	//string nextChildKey;
	string mainUrl;
	string siteName;
};

typedef vector<TSiteInfo> TSiteList;

typedef struct _ZMTIME
{
	_ZMTIME()
	{
		memset(this,0,sizeof(_ZMTIME));
	}
	uint16 wYear;						//[0--]
	uint8 wMonth;						//[1--12]
	uint8 wDay;							//[1--31]
	uint8 wHour;						//[0--23]
	uint8 wMinute;						//[0--59]
	uint8 wSecond;						//[0--59]
	uint16 wMilliseconds;				//[0--999]
}ZMTIME,*LPZMTIME;



#endif