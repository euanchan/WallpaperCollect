#pragma once

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	HtmlPicStruct GetWallpaperImgUrl(const HtmlKeyStruct& key);

private:
	string   htmlSrc;
};
