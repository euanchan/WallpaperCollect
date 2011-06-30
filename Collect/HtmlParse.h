#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	// 解析htmlSource, 获得频道列表信息
	bool GetChannelInfo(const TSiteInfo& siteInfo, TChannelInfo *channelInfo);

	// 解析htmlSource，根据siteInfo关键词获取页面相关信息
	bool GetPageIndexInfo(const TSiteInfo& siteInfo, TPaginationInfo *paginationInfo);

	// 解析包含多个 pageLevel2 url的网页源码  pageLevel3
	bool GetLevel2PageUrls(const TSiteInfo& siteInfo, TPackagePageInfo* packagePageInfo);
	
	// 解析包含多个 pageLevel1 url的网页源码 pageLevel2
	bool GetLevel1PageUrls(const TSiteInfo& siteInfo, TPicsShowPageInfo* picsShowPageInfo);

	// 解析包含 壁纸图片url的 网页源码 pageLevel1
	bool GetWallpaperImgUrl(const TSiteInfo& siteInfo, TPicShowPageInfo* picShowPageInfo);

private:
	string   htmlSrc;
};

#endif