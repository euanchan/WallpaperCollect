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
// 获取当前页面的页码信息
TPaginationAttri CHtmlParse::GetPageIndexInfo(const TSiteInfo& siteInfo)
{
	TPaginationAttri pages;
	int divBegPos = htmlSrc.find(siteInfo.paginationKey.divKey);
	int divEndPos = htmlSrc.find("/div>", divBegPos);
	if (divBegPos == -1 || divEndPos == -1)
		return pages;
	
	string paginationStr = htmlSrc.substr(divBegPos, divEndPos - divBegPos);

	int pos = 0;
	while ((pos = paginationStr.find(siteInfo.paginationKey.indexKey, pos)) != -1)
	{
		int pageIndexPosL = paginationStr.find(siteInfo.paginationKey.indexL, pos);
		pageIndexPosL += siteInfo.paginationKey.indexL.length();
		int pageIndexPosR = paginationStr.find(siteInfo.paginationKey.indexR, pageIndexPosL);
		pos = pageIndexPosR;
		if (pageIndexPosL == -1 || pageIndexPosR == -1)
			break;

		string pageIndexStr = paginationStr.substr(pageIndexPosL, pageIndexPosR - pageIndexPosL);
		int pageIndex = atoi(pageIndexStr.c_str());
		if (pageIndex > pages.maxPage)
			pages.maxPage = pageIndex;
	}
	pos = paginationStr.find(siteInfo.paginationKey.currentKey);
	int curIndexPosL = paginationStr.find(siteInfo.paginationKey.currentL, pos);
	curIndexPosL += siteInfo.paginationKey.currentL.length();
	int curIndexPosR = paginationStr.find(siteInfo.paginationKey.currentR, curIndexPosL);
	if (curIndexPosL == -1 || curIndexPosR == -1)
		return pages;

	string curIndexStr = paginationStr.substr(curIndexPosL, curIndexPosR - curIndexPosL);
	pages.curPage = atoi(curIndexStr.c_str());

	return pages;
}

TPackagePageAttri CHtmlParse::GetLevel2PageUrls(const TSiteInfo& siteInfo)
{
	//siteInfo.packagePageKey.Log(siteInfo.siteName);

	TPackagePageAttri packagePageAtt;

	int pos = htmlSrc.find(siteInfo.packagePageKey.nameKey);
	int namePosL = htmlSrc.find(siteInfo.packagePageKey.nameL, pos);
	int namePosR = htmlSrc.find(siteInfo.packagePageKey.nameR, namePosL);
	namePosL += siteInfo.packagePageKey.nameL.length();
	if (namePosL == -1 || namePosR == -1)
		return packagePageAtt;

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	packagePageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(siteInfo.packagePageKey.urlKey, pos)) != -1)
	{
		int urlPosL = htmlSrc.find(siteInfo.packagePageKey.urlL, pos);
		urlPosL += siteInfo.packagePageKey.urlL.length();
		pos = urlPosL;
		int urlPosR = htmlSrc.find(siteInfo.packagePageKey.urlR, urlPosL);
		pos = urlPosR;

		if (urlPosL == -1 || urlPosR == -1) 
			break;

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

	int pos = htmlSrc.find(siteInfo.picsShowPageKey.nameKey);
	int namePosL = htmlSrc.find(siteInfo.picsShowPageKey.nameL, pos);
	int namePosR = htmlSrc.find(siteInfo.picsShowPageKey.nameR, namePosL);
	namePosL += siteInfo.picsShowPageKey.nameL.length();
	if (namePosL == -1 || namePosR == -1)
		return picsShowPageAtt;

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	picsShowPageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(siteInfo.picsShowPageKey.urlKey, pos)) != -1)
	{
		int urlPosL = htmlSrc.find(siteInfo.picsShowPageKey.urlL, pos);
		urlPosL += siteInfo.picsShowPageKey.urlL.length();
		pos = urlPosL;
		int urlPosR = htmlSrc.find(siteInfo.picsShowPageKey.urlR, urlPosL);
		pos = urlPosR;

		if (urlPosL == -1 || urlPosR == -1) 
			break;

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

	int pos = htmlSrc.find(siteInfo.picShowPageKey.picNameKey);
	int picNameL = htmlSrc.find(siteInfo.picShowPageKey.picNameL, pos);
	int picNameR = htmlSrc.find(siteInfo.picShowPageKey.picNameR, picNameL);
	picNameL += siteInfo.picShowPageKey.picNameL.length();
	if (picNameL == -1 || picNameR == -1)
		return picShowPageAtt;

	string picNameStr = htmlSrc.substr(picNameL, picNameR - picNameL);
	USES_CONVERSION;
	picShowPageAtt.picName = A2W(picNameStr.c_str());

	pos = htmlSrc.find(siteInfo.picShowPageKey.picUrlKey, picNameR);
	int picUrlL = htmlSrc.find(siteInfo.picShowPageKey.picUrlL, pos);
	picUrlL += siteInfo.picShowPageKey.picUrlL.length();
	int picUrlR = htmlSrc.find(siteInfo.picShowPageKey.picUrlR, picUrlL);
	picUrlR += siteInfo.picShowPageKey.picUrlR.length();
	if (picUrlL == -1 || picUrlR == -1)
		return picShowPageAtt;

	picShowPageAtt.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	// 处理获得的图片url
	picShowPageAtt.picUrl.insert(0, siteInfo.mainUrl.c_str());

	return picShowPageAtt;
}