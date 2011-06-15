#pragma once

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	THtmlPicAtt GetWallpaperImgUrl(const TChildpageKey& key);

private:
	string   htmlSrc;
};
