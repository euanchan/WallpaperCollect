
#include "stdafx.h"
#include "WebServer.h"

IMPLEMENT_DYNAMIC(CWebServer, CWnd)

CWebServer::CWebServer(void)
{
	afxCurrentAppName = "WallpaperCollect.dll";
}

CWebServer::~CWebServer(void)
{
}

BEGIN_MESSAGE_MAP(CWebServer, CWnd)
END_MESSAGE_MAP()



string CWebServer::ColPageSourceHtml(const string& pageUrl)
{
	std::string htmlStr;
	CString theUrl = pageUrl.c_str();
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
		CString  somecode;	//也可采用LPTSTR类型，将不会删除文本中的\n回车符

		// 读写网页文件，直到为空
		// 如果采用LPTSTR类型，读取最大个数nMax置0，使它遇空字符时结束
		while (file->ReadString(somecode) != NULL) 
		{
			somecode += "\n";
			htmlStr += somecode;
		}
		file->Close();
		delete file;
	}

	//////////////////////////////////////////////////////////////////////////
	char szPath[MAX_PATH] = {0};
	CString strPath;
	::GetModuleFileName(NULL,szPath,sizeof(szPath));
	strcpy(strrchr(szPath,'\\'), "\\1.html");
	strPath = szPath;

	CStdioFile data;
	if (data.Open(strPath, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite | CFile::typeText))
	{
		data.WriteString(htmlStr.c_str());
		data.Close();
	}
	//////////////////////////////////////////////////////////////////////////

	return htmlStr;
}


bool CWebServer::DownLoadFile(const string& url, const string& filePath)
{
	bool ret = false;
	CInternetSession netSess;
	CHttpFile *pHttpFile = NULL;
	try
	{
		DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD;
		pHttpFile = (CHttpFile *)netSess.OpenURL(url.c_str(), 1, dwFlag);
		if (NULL != pHttpFile)
		{
			DWORD bufSize = 1024;
			DWORD readCount = 0;
			BYTE buf[1024];
			int len = 0;
			CFile file;
			if (file.Open(_T(filePath.c_str()), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
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
		if(NULL != pHttpFile)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
	}
	netSess.Close();
	return ret;
}