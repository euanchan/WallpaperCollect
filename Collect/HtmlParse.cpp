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
	TPaginationKey *pCurKey = const_cast<TPaginationKey *>(&siteInfo.paginationKey);
	TPaginationAttri pages;
	int divBegPos = htmlSrc.find(pCurKey->divKey);
	int divEndPos = htmlSrc.find("/div>", divBegPos);
	if (divBegPos == -1 || divEndPos == -1)
		return pages;
	
	string paginationStr = htmlSrc.substr(divBegPos, divEndPos - divBegPos);

	int pos = 0;
	while ((pos = paginationStr.find(pCurKey->indexKey, pos)) != -1)
	{
		int pageIndexPosL = paginationStr.find(pCurKey->indexL, pos);
		pageIndexPosL += pCurKey->indexL.length();
		int pageIndexPosR = paginationStr.find(pCurKey->indexR, pageIndexPosL);

		if (pageIndexPosR == -1 || pageIndexPosL == (pCurKey->indexL.length() - 1))
			break;

		pos = pageIndexPosR;

		string pageIndexStr = paginationStr.substr(pageIndexPosL, pageIndexPosR - pageIndexPosL);
		int pageIndex = atoi(pageIndexStr.c_str());
		if (pageIndex > pages.maxPage)
			pages.maxPage = pageIndex;
	}
	pos = paginationStr.find(pCurKey->currentKey);
	int curIndexPosL = paginationStr.find(pCurKey->currentL, pos);
	curIndexPosL += pCurKey->currentL.length();
	int curIndexPosR = paginationStr.find(pCurKey->currentR, curIndexPosL);

	if (curIndexPosR == -1 || curIndexPosL == (pCurKey->currentL.length() - 1))
		return pages;


	string curIndexStr = paginationStr.substr(curIndexPosL, curIndexPosR - curIndexPosL);
	pages.curPage = atoi(curIndexStr.c_str());

	return pages;
}

TPackagePageAttri CHtmlParse::GetLevel2PageUrls(const TSiteInfo& siteInfo)
{
	TPackagePageKey *pCurKey = const_cast<TPackagePageKey *>(&siteInfo.packagePageKey);
	//pCurKey->Log(siteInfo.siteName);

	TPackagePageAttri packagePageAtt;

	int pos = htmlSrc.find(pCurKey->nameKey);
	int namePosL = htmlSrc.find(pCurKey->nameL, pos);
	namePosL += pCurKey->nameL.length();
	int namePosR = htmlSrc.find(pCurKey->nameR, namePosL);

	if (namePosR == -1 || namePosL == (pCurKey->nameL.length() - 1))
		return packagePageAtt;


	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	packagePageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(pCurKey->urlKey, pos)) != -1)
	{
		int urlPosL = htmlSrc.find(pCurKey->urlL, pos);
		urlPosL += pCurKey->urlL.length();
		int urlPosR = htmlSrc.find(pCurKey->urlR, urlPosL);

		if (urlPosR == -1 || urlPosL == (pCurKey->urlL.length() - 1)) 
			break;

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
	TPicsShowPageKey *pCurKey = const_cast<TPicsShowPageKey *>(&siteInfo.picsShowPageKey);
	pCurKey->Log(siteInfo.siteName);

	TPicsShowPageAttri picsShowPageAtt;

	int pos = htmlSrc.find(pCurKey->nameKey);
	int namePosL = htmlSrc.find(pCurKey->nameL, pos);
	namePosL += pCurKey->nameL.length();
	int namePosR = htmlSrc.find(pCurKey->nameR, namePosL);

	if (namePosR == -1 || namePosL == (pCurKey->nameL.length() - 1))
		return picsShowPageAtt;

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	picsShowPageAtt.name = A2W(packageNameStr.c_str());

	pos = namePosR;
	while ((pos = htmlSrc.find(pCurKey->urlKey, pos)) != -1)
	{
		int urlPosL = htmlSrc.find(pCurKey->urlL, pos);
		urlPosL += pCurKey->urlL.length();
		int urlPosR = htmlSrc.find(pCurKey->urlR, urlPosL);

		if (urlPosR == -1 || urlPosL == (pCurKey->urlL.length() - 1)) 
			break;

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
	TPicShowPageKey *pCurKey = const_cast<TPicShowPageKey *>(&siteInfo.picShowPageKey);
	pCurKey->Log(siteInfo.siteName);

	TPicShowPageAttri picShowPageAtt;

	int pos = htmlSrc.find(pCurKey->picNameKey);
	int picNameL = htmlSrc.find(pCurKey->picNameL, pos);
	picNameL += pCurKey->picNameL.length();

	int picNameR = htmlSrc.find(pCurKey->picNameR, picNameL);

	if (picNameR == -1 || picNameL == (pCurKey->picNameL.length() - 1))
		return picShowPageAtt;

	string picNameStr = htmlSrc.substr(picNameL, picNameR - picNameL);
	USES_CONVERSION;
	picShowPageAtt.picName = A2W(picNameStr.c_str());

	pos = htmlSrc.find(pCurKey->picUrlKey, picNameR);
	int picUrlL = htmlSrc.find(pCurKey->picUrlL, pos);
	picUrlL += pCurKey->picUrlL.length();
	int picUrlR = htmlSrc.find(pCurKey->picUrlR, picUrlL);

	if (picUrlR == -1 || (picUrlL == pCurKey->picUrlL.length() - 1))
		return picShowPageAtt;

	picUrlR += pCurKey->picUrlR.length();

	picShowPageAtt.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	// 处理获得的图片url
	picShowPageAtt.picUrl.insert(0, siteInfo.mainUrl.c_str());

	return picShowPageAtt;
}