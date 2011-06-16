#include "stdafx.h"
#include "ComDef.h"


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

void TChildpageKey::Assign(const TSiteInfo& siteInfo)
{
	picNameKey = siteInfo.child.picNameKey;
	picNameL = siteInfo.child.picNameL;
	picNameR = siteInfo.child.picNameR;
	picUrlKey = siteInfo.child.picUrlKey;
	picUrlL = siteInfo.child.picUrlL;
	picUrlR = siteInfo.child.picUrlR;
}