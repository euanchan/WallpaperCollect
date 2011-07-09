#include "stdafx.h"
#include "WebServer.h"
#include "Tool.h"

IMPLEMENT_DYNAMIC(CWebServer, CWnd)

extern HWND gWindowHandle;

CWebServer::CWebServer(void)
: pfile(NULL)
{
	afxCurrentAppName = _T("WallpaperCollect.dll");
}

CWebServer::~CWebServer(void)
{
	if (pfile)
	{
		if (pfile->GetFileName().GetLength() > 2)
			pfile->Close();
		SAFE_DELETE(pfile);
	}
	_wunlink(curDownloadFile.c_str());
}

BEGIN_MESSAGE_MAP(CWebServer, CWnd)
END_MESSAGE_MAP()



bool CWebServer::ColPageSourceHtml( const string& pageUrl, string& htmlStr)
{
	//CString htmlWStr;
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
		tTestLog("ColPageSourceHtml:   " << pageUrl.c_str() << "  Failed!");
		file = NULL; 
		m_pException->Delete();
		return false;
	}

	if (file)
	{
		char recvBuf[1025] = {0};
		int readCount = 0;
		while ((readCount = file->Read((void*)recvBuf, 1024)) > 0) 
		{
			htmlStr.append(recvBuf, readCount);
		}
		//htmlWStr = htmlStr.c_str();  // 存储为本地文件时使用
		int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, htmlStr.c_str(), -1, NULL, 0);
		WCHAR *pUnicode = new WCHAR[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));

		MultiByteToWideChar(CP_UTF8, 0, htmlStr.c_str(), -1, pUnicode, unicodeLen);
		CString htmlWStrTmp = pUnicode;
		htmlWStrTmp.MakeLower();
		delete []pUnicode;
		htmlStr = W2A(htmlWStrTmp);

		file->Close();
		delete file;
	}

	//////////////////////////////////////////////////////////////////////////
/*
	wchar szPath[MAX_PATH] = {0};
	CString strPath = gPathInfo::CachePath() + _T("1.html");

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

	return true;
}


bool CWebServer::DownLoadFile( const string& url, const wstring& filePath )
{
	bool ret = false;

	USES_CONVERSION;
	wstring wUrl = A2W(url.c_str());
	CInternetSession netSess;
	CHttpFile *pHttpFile = NULL;

	// 文件存在
	curDownloadFile = filePath;
	MakeSurePathExists(filePath.c_str(), true);
	if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(filePath.c_str()))
	{
		return true;
	}
	try
	{
		// 获取文件名
		size_t pos = filePath.rfind(_T("\\")) + 1;
		CString fileName = filePath.substr(pos).c_str();
		UpdateCurPicName((WPARAM)fileName.GetBuffer());

		tDownloadLog("[" << url.c_str() << "]");
		tDownloadLog(" Save As [" <<  filePath.c_str() << "]");

		DWORD dwFlag = INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_RELOAD;
		pHttpFile = (CHttpFile *)netSess.OpenURL(wUrl.c_str(), 1, dwFlag);

		// 获取文件大小
		LONGLONG fileSize = 0;
		LONGLONG readedSz = 0;
		CString queryinfo;
		pHttpFile->QueryInfo(HTTP_QUERY_STATUS_CODE, queryinfo);
		if(queryinfo == "200") 
		{ 
			pHttpFile-> QueryInfo(HTTP_QUERY_CONTENT_LENGTH, queryinfo);
			fileSize = _wtoi64(queryinfo);
		}

		if (NULL != pHttpFile)
		{
			DWORD bufSize = 1024;
			DWORD readCount = 0;
			BYTE buf[1024];
			int len = 0;
			if (!pfile) 
				pfile = new CFile(); 
			if (pfile->Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
			{
				memset(buf, 0, bufSize);
				while (true)
				{
					readCount = pHttpFile->Read(buf, bufSize);
					pfile->Write(buf, readCount);
					readedSz += readCount;

					// TODO: 缩略图判断方式
					UpdateProgress(readedSz, fileSize);
					if (fileSize < 50000 && readedSz == fileSize)
					{
						NotifyThumbnailDownload((WPARAM)url.c_str(), (LPARAM)filePath.c_str());
					}
					if (readCount < bufSize)
						break;
				}
				pfile->Close();
				ret = true;
			}
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		else
		{
			tTestLog("DownLoadFile: " << url.c_str() << "  Failed! null");
		}
	}
	catch (...)
	{
		tTestLog("DownLoadFile:   " << url.c_str() << "  Failed!");
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
		ret = false;
	}
	netSess.Close();
	return ret;
}

//////////////////////////////////////////////////////////////////////////

bool CWebServer::UpdateProgress(LONGLONG index, LONGLONG total)
{
	if (gWindowHandle && total > 0)
	{
		int pos = (float)index / (float)total * 100;
		::PostMessage(gWindowHandle, MSG_UPDATE_CUR_PIC_PROCESS, pos, 0); 

		return true;
	}
	return false;
}

bool CWebServer::UpdateCurPicName(WPARAM wstrPt)
{
	if (gWindowHandle && wstrPt)
	{
		::PostMessage(gWindowHandle, MSG_UPDATE_CUR_PIC_NAME, wstrPt, 0); 
		return true;
	}
	return false;	
}

bool CWebServer::NotifyThumbnailDownload(WPARAM urlPt, LPARAM savePathPt)
{
	// 缩略图下载完成，发送消息更新图片列表
	::PostMessage(gWindowHandle, MSG_THUMBNAIL_PIC_FINISHED, urlPt, savePathPt);
	return true;
}