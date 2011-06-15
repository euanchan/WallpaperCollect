#include "stdafx.h"
#include "HtmlParse.h"
#include "Util.h"

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

THtmlPicAtt CHtmlParse::GetWallpaperImgUrl(const TChildpageKey& key)
{
	size_t pos = htmlSrc.find(key.picNameKey);
	size_t picNameL = htmlSrc.find(key.picNameL, pos);
	size_t picNameR = htmlSrc.find(key.picNameR, picNameL);
	picNameL += key.picNameL.length();
	THtmlPicAtt htmlPic;
	htmlPic.picName = htmlSrc.substr(picNameL, picNameR - picNameL);

	htmlPic.picName = UTF82GB(htmlPic.picName);

	pos = htmlSrc.find(key.picUrlKey, picNameR);
	size_t picUrlL = htmlSrc.find(key.picUrlL, pos);
	size_t picUrlR = htmlSrc.find(key.picUrlR, picUrlL);
	picUrlL += key.picUrlL.length();
	picUrlR += key.picUrlR.length();
	htmlPic.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	return htmlPic;
}