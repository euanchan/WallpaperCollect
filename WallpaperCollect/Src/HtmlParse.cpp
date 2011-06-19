#include "stdafx.h"
#include "HtmlParse.h"
#include "Tool.h"
#include  <atlbase.h>

CHtmlParse::CHtmlParse(const string& htmlSource)
: htmlSrc(htmlSource)
{
}

CHtmlParse::~CHtmlParse(void)
{
}

void CHtmlParse::ResetSrc(const string& htmlSource)
{
	htmlSrc = htmlSource;
}

/*
// destCity:
	<div class="pagination"><a href="/details/index/152/5">上一页</a> 
	<a href="/details/index/152">1</a> 
	<a href="/details/index/152/2">2</a> 
	<a href="/details/index/152/3">3</a> 
	<a href="/details/index/152/4">4</a> 
	<a href="/details/index/152/5">5</a> 
	<span class="current">6</span> 
	<span class="disabled">下一页</span></div>

*/
// 获取下一页
TPaginationAttri CHtmlParse::GetNextPageUrl(const TSiteInfo& siteInfo)
{
	TPaginationAttri pages;
	size_t pos = 
}

TPackagePageAttri CHtmlParse::GetLevel2PageUrls(const TSiteInfo& siteInfo)
{
	//siteInfo.packagePageKey.Log(siteInfo.siteName);

	TPackagePageAttri packagePageAtt;

	size_t pos = htmlSrc.find(siteInfo.packagePageKey.nameKey);
	size_t namePosL = htmlSrc.find(siteInfo.packagePageKey.nameL, pos);
	size_t namePosR = htmlSrc.find(siteInfo.packagePageKey.nameR, namePosL);
	namePosL += siteInfo.packagePageKey.nameL.length();

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	packagePageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(siteInfo.packagePageKey.urlKey, pos)) != -1)
	{
		size_t urlPosL = htmlSrc.find(siteInfo.packagePageKey.urlL, pos);
		urlPosL += siteInfo.packagePageKey.urlL.length();
		pos = urlPosL;
		size_t urlPosR = htmlSrc.find(siteInfo.packagePageKey.urlR, urlPosL);
		pos = urlPosR;

		// 补充url
		string urlStr = htmlSrc.substr(urlPosL, urlPosR - urlPosL);
		urlStr.insert(0, siteInfo.mainUrl.c_str());

		packagePageAtt.urlArr.push_back(urlStr);
	}
	return packagePageAtt;
}


TPicsShowPageAttri CHtmlParse::GetLevel1PageUrls(const TSiteInfo& siteInfo)
{
	siteInfo.picsShowPageKey.Log(siteInfo.siteName);

	TPicsShowPageAttri picsShowPageAtt;

	size_t pos = htmlSrc.find(siteInfo.picsShowPageKey.nameKey);
	size_t namePosL = htmlSrc.find(siteInfo.picsShowPageKey.nameL, pos);
	size_t namePosR = htmlSrc.find(siteInfo.picsShowPageKey.nameR, namePosL);
	namePosL += siteInfo.picsShowPageKey.nameL.length();

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	picsShowPageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(siteInfo.picsShowPageKey.urlKey, pos)) != -1)
	{
		size_t urlPosL = htmlSrc.find(siteInfo.picsShowPageKey.urlL, pos);
		urlPosL += siteInfo.picsShowPageKey.urlL.length();
		pos = urlPosL;
		size_t urlPosR = htmlSrc.find(siteInfo.picsShowPageKey.urlR, urlPosL);
		pos = urlPosR;

		// 补充url
		string urlStr = htmlSrc.substr(urlPosL, urlPosR - urlPosL);
		urlStr.insert(0, siteInfo.mainUrl.c_str());

		picsShowPageAtt.urlArr.push_back(urlStr);
	}
	return picsShowPageAtt;
}

TPicShowPageAttri CHtmlParse::GetWallpaperImgUrl( const TSiteInfo& siteInfo )
{
	siteInfo.picShowPageKey.Log(siteInfo.siteName);

	TPicShowPageAttri picShowPageAtt;

	size_t pos = htmlSrc.find(siteInfo.picShowPageKey.picNameKey);
	size_t picNameL = htmlSrc.find(siteInfo.picShowPageKey.picNameL, pos);
	size_t picNameR = htmlSrc.find(siteInfo.picShowPageKey.picNameR, picNameL);
	picNameL += siteInfo.picShowPageKey.picNameL.length();

	string picNameStr = htmlSrc.substr(picNameL, picNameR - picNameL);
	USES_CONVERSION;
	picShowPageAtt.picName = A2W(picNameStr.c_str());

	pos = htmlSrc.find(siteInfo.picShowPageKey.picUrlKey, picNameR);
	size_t picUrlL = htmlSrc.find(siteInfo.picShowPageKey.picUrlL, pos);
	size_t picUrlR = htmlSrc.find(siteInfo.picShowPageKey.picUrlR, picUrlL);
	picUrlL += siteInfo.picShowPageKey.picUrlL.length();
	picUrlR += siteInfo.picShowPageKey.picUrlR.length();
	picShowPageAtt.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	// 处理获得的图片url
	picShowPageAtt.picUrl.insert(0, siteInfo.mainUrl.c_str());

	return picShowPageAtt;
}