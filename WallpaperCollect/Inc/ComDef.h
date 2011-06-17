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
class TPicshowPageAttri
{
public:
	wstring picName;
	string picUrl;
};

class TSiteInfo;
// 包含实际壁纸链接的网页(pageLevel1)关键字
class TPicshowPageKey 
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
class TPackagePageKey
{
public:
	string nameKey;  // 壁纸合集目录名称关键字
	string nameL;
	string nameR;
	string urlKey;  // 单个壁纸页面链接关键字
	string urlL;
	string urlR;

	void Log(const string& siteName) const;
};

class TPackagePageAttri
{
public:
	wstring  packageName;  // 壁纸合集名称
	vector<string> urlArr;
};

//////////////////////////////////////////////////////////////////////////
// 包含多个pageLevel2页面链接的网页(pageLevel3)关键字信息
class TPackagesPageKey
{

};

class TSiteInfo
{
public:
	TPicshowPageKey picshowPageKey;
	TPackagePageKey packagePageKey;
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