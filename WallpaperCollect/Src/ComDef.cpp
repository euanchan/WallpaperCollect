#include "stdafx.h"
#include "ComDef.h"
#include "Log.h"


// TChildpageKey::TChildpageKey()
// {
// 
// }
// 
// TChildpageKey::~TChildpageKey()
// {
// 	SAFE_DELETE(picNameKey);
// 	SAFE_DELETE(picNameL);
// 	SAFE_DELETE(picNameR);
// 	SAFE_DELETE(picUrlKey);
// 	SAFE_DELETE(picUrlL);
// 	SAFE_DELETE(picUrlR);
// }


void TPicshowPageKey::Log(const string& siteName) const 
{
	if (picNameKey.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "PicNameKey is NULL");
	if (picNameL.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picNameL is NULL");
	if (picNameR.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picNameR is NULL");
	if (picUrlKey.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picUrlKey is NULL");
	if (picUrlL.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picUrlL is NULL");
	if (picUrlR.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picUrlR is NULL");
}

void TPackagePageKey::Log(const string& siteName) const
{
	if (nameKey.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "packageKey is NULL");
	if (nameL.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "packageL is NULL");
	if (nameR.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "packageR is NULL");
	if (urlKey.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picPageUrlKey is NULL");
	if (urlL.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picPageUrlL is NULL");
	if (urlR.length() == 0)
		tMainLog("Site:" << siteName.c_str() << "picPageUrlR is NULL");
}