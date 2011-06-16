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

typedef struct
{
	wstring picName;
	string picUrl;
}THtmlPicAttri;

class TSiteInfo;
class TChildpageKey
{
public:
	string picNameKey;
	string picNameL;
	string picNameR;
	string picUrlKey;
	string picUrlL;
	string picUrlR;

	void Assign(const TSiteInfo& siteInfo);
};

class TSiteInfo
{
public:
	TChildpageKey child;
	string nextChildKey;
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