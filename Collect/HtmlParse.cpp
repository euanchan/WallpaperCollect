#include "stdafx.h"
#include "HtmlParse.h"
#include "Tool.h"
#include <atlbase.h>
#include <atlstr.h>

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

//////////////////////////////////////////////////////////////////////////
/*
// destCity:
	d.add(1, 0,'风光','');
	d.add(31,1,'风光其他','/details/index/31');
*/
TChannelAttri CHtmlParse::GetChannelInfo(const TSiteInfo& siteInfo)
{
	TChannelAttri channelAtt;
	channelAtt.siteName = siteInfo.siteName;
	vector<string> infoVec;  // 分离出 31,1,'风光其他','/details/index/31'
	int pos = 0;
	while ((pos = htmlSrc.find("add(", pos)) != -1)
	{
		pos += 4;
		int rPos = htmlSrc.find(")", pos);
		infoVec.push_back(htmlSrc.substr(pos, rPos - pos));
		pos = rPos;
	}
	
	vector<TChannelStrInfo> channelVec;
	for (int i = 0; i < infoVec.size(); i++)
	{
		char *info = const_cast<char*>(infoVec[i].c_str());
		char *key = ",\'";
		char *token = strtok(info, key);
		token = strtok(NULL, key);
		TChannelStrInfo channelInfo;
		channelInfo.num = atoi(token);
		token = strtok(NULL, key);
		channelInfo.channelName = token ? token : "";
		token = strtok(NULL, key);
		channelInfo.channelUrl = token ? token : "";
		channelVec.push_back(channelInfo);
	}

	for (int i = 0; i < channelVec.size(); i++)
	{
		if (channelVec[i].num == 0)
		{
			TChannelNode node;
			node.first = channelVec[i].channelName;
			channelAtt.tree.push_back(node);
		}
		else if (channelVec[i].num > 0)
		{
			int index = channelVec[i].num;
			ASSERT(index <= channelAtt.tree.size());
			TChannelNode *node = &channelAtt.tree[index - 1];
			TChannelNodeChild child;
			child.first = channelVec[i].channelName;
			string url = siteInfo.mainUrl + channelVec[i].channelUrl;
			child.second = url;
			node->second.push_back(child);
		}
	}

	return channelAtt;
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