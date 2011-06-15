#pragma once

#include <afxinet.h>

class CWebServer :	public CWnd
{
	DECLARE_DYNAMIC(CWebServer)

public:
	CWebServer();
	virtual ~CWebServer();

protected:
	DECLARE_MESSAGE_MAP()

public:
	// 获取指定URL的面面内容
// 	std::string GetWebPage(const std::string& sUrl);
// 
	// 获取HTML页面源码
	string ColPageSourceHtml(const string& pageUrl);

	bool DownLoadFile(const string& url, const string& filePath);
};
