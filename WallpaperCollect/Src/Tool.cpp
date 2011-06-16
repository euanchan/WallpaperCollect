#include "stdafx.h"
#include "Tool.h"
#include <io.h>

CUtil::CUtil(void)
{
}

CUtil::~CUtil(void)
{
}

BOOL MakeSurePathExists(const CString &strPath, bool fileNameIncluded)
{
	int Pos=0;
	while ((Pos = strPath.Find('\\', Pos + 1)) != -1) 
		CreateDirectory(strPath.Left(Pos), NULL);
	if (!fileNameIncluded)
		CreateDirectory(strPath, NULL);

// 判断文件是否可读写
// 	return ((!fileNameIncluded) ? 
// 		!_access(strPath, 0) :
// 		!_access(strPath.Left(strPath.ReverseFind('\\')), 0));
	return true;
}

wstring GB2UTF8(const wstring& sSrc)
{
	wstring sRet;

// 	if(sSrc.length() > 0)
// 	{
// 		int iWLen = MultiByteToWideChar(936, 0, sSrc.c_str(), -1, NULL, 0);
// 		WCHAR* wc = new WCHAR[iWLen*sizeof(WCHAR)];
// 		MultiByteToWideChar(936, 0, sSrc.c_str(), -1, wc, iWLen);
// 
// 		int iDesLen = WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, NULL, 0, 0, 0);
// 		char* pBuf = new char[iDesLen+1];
// 		WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, pBuf, iDesLen, 0, 0);
// 		sRet = pBuf;
// 		delete []pBuf;
// 		delete []wc;
// 	}

	return sRet;
}

// 将UTF8编码转化为GB2312
wstring UTF82GB(const wstring& szSrc)
{
	wstring sRet;

// 	if(szSrc.length() > 0)
// 	{
// 		size_t iWLen = MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), NULL, 0);
// 		WCHAR* wc = new WCHAR[iWLen];
// 		MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), wc, iWLen);
// 
// 		int iDesLen = WideCharToMultiByte(936, 0, wc, iWLen, NULL, 0, 0, 0);
// 		char* pBuf = new char[iDesLen+1];
// 		WideCharToMultiByte(936, 0, wc, iWLen, pBuf, iDesLen, 0, 0);
// 		pBuf[iDesLen] = 0;
// 		sRet = pBuf;
// 		delete []pBuf;
// 		delete []wc;
// 	}

	return sRet;
}