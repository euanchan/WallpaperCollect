#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	THtmlPicAttri GetWallpaperImgUrl(const TChildpageKey& key);

private:
	string   htmlSrc;
};

#endif