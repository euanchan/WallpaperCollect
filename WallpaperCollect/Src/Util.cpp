#include "stdafx.h"
#include "Util.h"

CUtil::CUtil(void)
{
}

CUtil::~CUtil(void)
{
}

string GB2UTF8(const string& sSrc)
{
	string sRet;

	if(sSrc.length() > 0)
	{
		int iWLen = MultiByteToWideChar(936, 0, sSrc.c_str(), -1, NULL, 0);
		WCHAR* wc = new WCHAR[iWLen*sizeof(WCHAR)];
		MultiByteToWideChar(936, 0, sSrc.c_str(), -1, wc, iWLen);

		int iDesLen = WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, NULL, 0, 0, 0);
		char* pBuf = new char[iDesLen+1];
		WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, pBuf, iDesLen, 0, 0);
		sRet = pBuf;
		delete []pBuf;
		delete []wc;
	}

	return sRet;
}

// 将UTF8编码转化为GB2312
string UTF82GB(const string& szSrc)
{
	string sRet;

	if(szSrc.length() > 0)
	{
		int iWLen = MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), NULL, 0);
		WCHAR* wc = new WCHAR[iWLen];
		MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), wc, iWLen);

		int iDesLen = WideCharToMultiByte(936, 0, wc, iWLen, NULL, 0, 0, 0);
		char* pBuf = new char[iDesLen+1];
		WideCharToMultiByte(936, 0, wc, iWLen, pBuf, iDesLen, 0, 0);
		pBuf[iDesLen] = 0;
		sRet = pBuf;
		delete []pBuf;
		delete []wc;
	}

	return sRet;
}