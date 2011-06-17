#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	
	// 解析包含多个 page1 url的网页源码 pageLevel2
	TPackagePageAttri GetWallpaperPagesUrl(const TSiteInfo& siteInfo);
	// 解析包含 壁纸图片url的 网页源码 pageLevel1
	TPicshowPageAttri GetWallpaperImgUrl(const TSiteInfo& siteInfo);

private:
	string   htmlSrc;
};

#endif