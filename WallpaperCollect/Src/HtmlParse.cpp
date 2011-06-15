#include "stdafx.h"
#include "HtmlParse.h"

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

HtmlPicStruct CHtmlParse::GetWallpaperImgUrl(const HtmlKeyStruct& key)
{
	int pos = htmlSrc.find(key.picNameKey);
	int picNameL = htmlSrc.find(key.picNameL, pos);
	int picNameR = htmlSrc.find(key.picNameR, picNameL);
	picNameL += key.picNameL.length();
	HtmlPicStruct htmlPic;
	htmlPic.picName = htmlSrc.substr(picNameL, picNameR - picNameL);

	int len = ::WideCharToMultiByte(CP_ACP, NULL, 
		htmlPic.picName.c_str(), htmlPic.picName.length(), NULL,    0 ); 
	char* nameStr = new char[len + 1];
	memset(nameStr, 0, len);
	::WideCharToMultiByte(CP_ACP, NULL, htmlPic.picName.c_str(), 
		htmlPic.picName.length(), nameStr, len); 
	nameStr[len]=L'\0 ';

	pos = htmlSrc.find(key.picUrlKey, picNameR);
	int picUrlL = htmlSrc.find(key.picUrlL, pos);
	int picUrlR = htmlSrc.find(key.picUrlR, picUrlL);
	picUrlL += key.picUrlL.length();
	picUrlR += key.picUrlR.length();
	htmlPic.picUrl = htmlSrc.substr(picUrlL, picUrlR - picUrlL);

	return htmlPic;
}