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
// 	std::wstring GetWebPage(const std::wstring& sUrl);
// 
	// 获取HTML页面源码
	bool ColPageSourceHtml(const string& pageUrl, string &htmlSrc);

	bool DownLoadFile(const string& url, const wstring& filePath);
	bool UpdateProgress(LONGLONG index, LONGLONG total);
	bool UpdateCurPicName(WPARAM wstrPt);
	bool NotifyThumbnailDownload(WPARAM urlPt, LPARAM savePathPt);
	
private:
	wstring curDownloadFile;
	CFile  *pfile;
};
