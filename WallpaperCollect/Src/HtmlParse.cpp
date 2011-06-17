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

TPackagePageAttri CHtmlParse::GetWallpaperPagesUrl(const TSiteInfo& siteInfo)
{
	siteInfo.packagePageKey.Log(siteInfo.siteName);

	TPackagePageAttri packagePageAtt;

	size_t pos = htmlSrc.find(siteInfo.packagePageKey.nameKey);
	size_t namePosL = htmlSrc.find(siteInfo.packagePageKey.nameL, pos);
	size_t namePosR = htmlSrc.find(siteInfo.packagePageKey.nameR, namePosL);
	namePosL += siteInfo.packagePageKey.nameL.length();

	string packageNameStr = htmlSrc.substr(namePosL, namePosR - namePosL);
	USES_CONVERSION;
	packagePageAtt.packageName = A2W(packageNameStr.c_str());

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

TPicshowPageAttri CHtmlParse::GetWallpaperImgUrl( const TSiteInfo& siteInfo )
{
	siteInfo.picshowPageKey.Log(siteInfo.siteName);

	TPicshowPageAttri picshowPageAtt;

	size_t pos = htmlSrc.find(siteInfo.picshowPageKey.picNameKey);
	size_t picNameL = htmlSrc.find(siteInfo.picshowPageKey.picNameL, pos);
	size_t picNameR = htmlSrc.find(siteInfo.picshowPageKey.picNameR, picNameL);
	picNameL += siteInfo.picshowPageKey.picNameL.length();

	string picNameStr = htmlSrc.substr(picNameL, picNameR - picNameL);
	USES_CONVERSION;
	picshowPageAtt.picName = A2W(picNameStr.c_str());

	pos = htmlSrc.find(siteInfo.picshowPageKey.picUrlKey, picNameR);
	size_t picUrlL = htmlSrc.find(siteInfo.picshowPageKey.picUrlL, pos);
	size_t picUrlR = htmlSrc.find(siteInfo.picshowPageKey.picUrlR, picUrlL);
	picUrlL += siteInfo.picshowPageKey.picUrlL.length();
	picUrlR += siteInfo.picshowPageKey.picUrlR.length();
	picshowPageAtt.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	// 处理获得的图片url
	picshowPageAtt.picUrl.insert(0, siteInfo.mainUrl.c_str());

	return picshowPageAtt;
}