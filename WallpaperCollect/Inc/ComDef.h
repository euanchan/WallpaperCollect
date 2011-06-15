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
}HtmlPicStruct;

typedef struct
{
	string picNameKey;
	string picNameL;
	string picNameR;
	string picUrlKey;
	string picUrlL;
	string picUrlR;
}HtmlKeyStruct;


#endif