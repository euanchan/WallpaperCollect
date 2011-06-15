#ifndef COMDEF_H
#define COMDEF_H

enum SiteType
{
	kSiteDeskCity
};

typedef struct
{
	string picName;
	string picUrl;
}THtmlPicAtt;

typedef struct
{
	string picNameKey;
	string picNameL;
	string picNameR;
	string picUrlKey;
	string picUrlL;
	string picUrlR;
}TChildpageKey;

typedef struct
{
	TChildpageKey child;
	string nextChildKey;
	string mainUrl;
}TSiteInfo;


typedef pair<string, TSiteInfo> TSitePair;
typedef vector<TSitePair>      TSitePairList;

#endif