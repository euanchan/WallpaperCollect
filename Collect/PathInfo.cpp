#include "stdafx.h"
#include "PathInfo.h"
#include "Tool.h"
TStrHashSet urlHashSet;

CPathInfo* CPathInfo::instance = NULL;

CPathInfo* CPathInfo::GetInstance()
{
	if (!instance)
		instance = new CPathInfo();
	return instance;
}

wstring GetModulePath()
{
	wstring path;
	wchar_t pPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, pPath, MAX_PATH);
	wcscpy(wcsrchr(pPath, '\\'), _T("\0"));

	path = pPath;
	return path;
}

CPathInfo::CPathInfo()
{
	modulePath = GetModulePath();
	cachePath = modulePath + _T("\\cache\\");
	thumbnailCachePath = cachePath + _T("thumbnail\\");
	savePathRoot = modulePath + _T("\\wallpaper\\");
	MakeSurePathExists(thumbnailCachePath.c_str(), false);
	MakeSurePathExists(savePathRoot.c_str(), false);
}
CPathInfo::~CPathInfo()
{
}


void CPathInfo::InitPathInfo()
{
	LoadUrlMap();
}

wstring CPathInfo::ModulePath()
{
	return modulePath;
}

wstring CPathInfo::CachePath()
{
	return cachePath;
}

wstring CPathInfo::ThumbnailCachePath()
{
	return thumbnailCachePath;
}

void CPathInfo::LoadUrlMap()     // 从本地文件加载已加载的url到hashmap
{
	wstring filePath = modulePath + _T("\\loadedUrl.data");

	FILE *file = _wfopen(filePath.c_str(), _T("r"));
	if (file != NULL)
	{
		char line[128]; /* or other suitable maximum line size */
		while (fgets(line, sizeof(line), file) != NULL) /* read a line */
		{
			if (strlen(line) > 1)
				urlHashSet.insert(line);
		}
		fclose(file);
	}
}

void CPathInfo::SaveUrlMap()  // 保存已加载url的hashmap到本地文件
{
	wstring filePath = modulePath + _T("\\loadedUrl.data");
	TStrHashSet::iterator iter = urlHashSet.begin();
	CFile file;
	if (file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite))
	{
		while (iter != urlHashSet.end())
		{
			string url = *iter;
			file.Write(url.c_str(), url.length());
			file.Write("\n", 1);
			iter++;
		}
		file.Close();
	}
}

void CPathInfo::InsertUrlToFile(const string& url) // 将url存入hashmap中
{
	urlHashSet.insert(url);
}

bool CPathInfo::PageLoaded(const string& url)  // 
{
	TStrHashSet::const_iterator iter = urlHashSet.begin();
	iter = urlHashSet.find(url);
	return iter != urlHashSet.end();
}


wstring CPathInfo::GetSavePathRoot()
{
	return savePathRoot;
}

void CPathInfo::SetSavePathRoot(const wstring &path)
{
	savePathRoot = path;
	MakeSurePathExists(savePathRoot.c_str(), false);
}