#pragma once

class CUtil
{
public:
	CUtil(void);
	~CUtil(void);
};

BOOL MakeSurePathExists(const CString &path, bool fileNameIncluded);
wstring GB2UTF8(const wstring& sSrc);
wstring UTF82GB(const wstring& szSrc);