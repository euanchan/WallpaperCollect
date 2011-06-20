
#include  <atlbase.h>

#include "stdafx.h"
#include "WebServer.h"
#include "Tool.h"

IMPLEMENT_DYNAMIC(CWebServer, CWnd)

CWebServer::CWebServer(void)
{
	afxCurrentAppName = _T("WallpaperCollect.dll");
}

CWebServer::~CWebServer(void)
{
}

BEGIN_MESSAGE_MAP(CWebServer, CWnd)
END_MESSAGE_MAP()



string CWebServer::ColPageSourceHtml( const string& pageUrl )
{
	CString htmlWStr;
	string htmlStr;
	USES_CONVERSION;
	CString theUrl = A2W(pageUrl.c_str());
	CInternetSession session;
	CInternetFile* file = NULL;

	try
	{	
		file = (CInternetFile*) session.OpenURL(theUrl); 
	}
	catch (CInternetException* m_pException)
	{
		file = NULL; 
		m_pException->Delete();
		return FALSE;
	}

	if (file)
	{
		char recvBuf[1025] = {0};
		while (file->Read((void*)recvBuf, 1024) != NULL) 
		{
			htmlStr += recvBuf;
		}
		htmlWStr = htmlStr.c_str();  // 存储为本地文件时使用
		int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, htmlStr.c_str(), -1, NULL, 0);
		WCHAR *pUnicode = new WCHAR[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));

		MultiByteToWideChar(CP_UTF8, 0, htmlStr.c_str(), -1, pUnicode, unicodeLen);
		CString htmlWStrTmp = pUnicode; 
		delete []pUnicode;
		htmlStr = W2A(htmlWStrTmp);

		file->Close();
		delete file;
	}

	//////////////////////////////////////////////////////////////////////////
/*
	wchar szPath[MAX_PATH] = {0};
	CString strPath;
	::GetModuleFileName(NULL,szPath,sizeof(szPath));
	wcscpy(wcsrchr(szPath, _T('\\')), _T("\\Cache\\1.html"));
	strPath = szPath;

	CStdioFile data;
	if (data.Open(strPath, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite | CFile::typeText))
	{
		setlocale(LC_CTYPE, ("chs"));  
		data.WriteString(htmlWStr);
		data.Close();
	}
*/
	//////////////////////////////////////////////////////////////////////////

	return htmlStr;
}


bool CWebServer::DownLoadFile( const string& url, const wstring& filePath )
{
	bool ret = false;

	USES_CONVERSION;
	wstring wUrl = A2W(url.c_str());
	CInternetSession netSess;
	CHttpFile *pHttpFile = NULL;

	// 文件存在
	if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(filePath.c_str()))
	{
		return false;
	}
	try
	{
		DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD;
		pHttpFile = (CHttpFile *)netSess.OpenURL(wUrl.c_str(), 1, dwFlag);
		if (NULL != pHttpFile)
		{
			DWORD bufSize = 1024;
			DWORD readCount = 0;
			BYTE buf[1024];
			int len = 0;
			CFile file;
			if (file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				memset(buf, 0, bufSize);
				while (true)
				{
					readCount = pHttpFile->Read(buf, bufSize);
					file.Write(buf, readCount);
					if (readCount < bufSize)
						break;
				}
				file.Close();
				ret = true;
			}
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
	}
	catch (...)
	{
		//AfxMessageBox(_T("Download File failed"));
		if(NULL != pHttpFile)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		// 若文件写到一半，删除文件
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(filePath.c_str()))
		{
			DeleteFile(filePath.c_str());
		}
	}
	netSess.Close();
	return ret;
}