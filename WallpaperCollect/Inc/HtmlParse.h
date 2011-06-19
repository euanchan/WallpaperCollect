#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	TPaginationAttri GetNextPageUrl(const TSiteInfo& siteInfo);

	// 解析包含多个 pageLevel2 url的网页源码  pageLevel3
	TPackagePageAttri GetLevel2PageUrls(const TSiteInfo& siteInfo);
	
	// 解析包含多个 pageLevel1 url的网页源码 pageLevel2
	TPicsShowPageAttri GetLevel1PageUrls(const TSiteInfo& siteInfo);

	// 解析包含 壁纸图片url的 网页源码 pageLevel1
	TPicShowPageAttri GetWallpaperImgUrl(const TSiteInfo& siteInfo);

private:
	string   htmlSrc;
};

#endif