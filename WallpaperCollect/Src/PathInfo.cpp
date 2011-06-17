#include "stdafx.h"
#include "PathInfo.h"


CPathInfo::CPathInfo()
{
	modulePath = _T("");
}
CPathInfo::~CPathInfo()
{
}

wstring GetModulePath()
{
	wstring path;
	wchar_t pPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, pPath, MAX_PATH);
	path = pPath;
	return path;
}

void CPathInfo::InitPathInfo()
{
	modulePath = GetModulePath();
}

const wchar_t* CPathInfo::ModulePath()
{
	return modulePath.c_str();
}