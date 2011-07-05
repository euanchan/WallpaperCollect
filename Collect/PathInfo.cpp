#include "stdafx.h"
#include "PathInfo.h"
#include "Tool.h"

CPathInfo* CPathInfo::instance = NULL;

CPathInfo* CPathInfo::GetInstance()
{
	if (!instance)
	{
		instance = new CPathInfo();
		instance->LoadFinishedPicsPageUrl();
		instance->LoadTaskedPicsPageUrl();
	}
	return instance;
}

void CPathInfo::ReleaseInstance()
{
	instance->SaveTaskedPicsPageUrl();
	instance->SaveFinishedPicsPageUrl();

	wstring iniFilePath = modulePath + _T("\\config.ini");
	::WritePrivateProfileString(_T("wallpaper"), _T("savepathRoot"), 
		savePathRoot.c_str(), iniFilePath.c_str());
	SAFE_DELETE(instance);
}

CPathInfo::CPathInfo()
{
	wchar_t pPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, pPath, MAX_PATH);
	wcscpy(wcsrchr(pPath, '\\'), _T("\0"));
	modulePath.assign(pPath);


	cachePath = modulePath + _T("\\cache\\");
	thumbnailCachePath = cachePath + _T("thumbnail\\");
	savePathRoot = modulePath + _T("\\wallpaper\\");

	// 
	wstring iniFilePath = modulePath + _T("\\config.ini");
	wchar buf[1024];
	::GetPrivateProfileString(_T("wallpaper"), _T("savepathRoot"), savePathRoot.c_str(), 
		buf, 1024, iniFilePath.c_str());
	savePathRoot = buf;
	if (savePathRoot[savePathRoot.length() - 1] != '\\')
		savePathRoot.append(_T("\\"));

	MakeSurePathExists(thumbnailCachePath.c_str(), false);
	MakeSurePathExists(savePathRoot.c_str(), false);
}

CPathInfo::~CPathInfo()
{
}

void CPathInfo::InitPathInfo()
{
}

const wchar_t* CPathInfo::GetModulePath()
{
	return modulePath.c_str();
}

const wchar_t* CPathInfo::GetCachePath()
{
	return cachePath.c_str();
}

const wchar_t* CPathInfo::GetThumbnailCachePath()
{
	return thumbnailCachePath.c_str();
}

const wchar_t* CPathInfo::GetSavePathRoot()
{
	return savePathRoot.c_str();
}

void CPathInfo::SetSavePathRoot(const wstring &path)
{
	savePathRoot = path;
	if (savePathRoot[savePathRoot.length() - 1] != '\\')
		savePathRoot.append(_T("\\"));
	MakeSurePathExists(savePathRoot.c_str(), false);
}

//////////////////////////////////////////////////////////////////////////

void CPathInfo::LoadTaskedPicsPageUrl()
{
	wstring filePath = modulePath + _T("\\taskedPUrl.data");
	DoLoadHashSet(taskedUrlList, filePath);
}

void CPathInfo::SaveTaskedPicsPageUrl()
{
	wstring filePath = modulePath + _T("\\taskedPUrl.data");
	DoSaveHashSet(taskedUrlList, filePath);
}

void CPathInfo::LoadFinishedPicsPageUrl()
{
	wstring filePath = modulePath + _T("\\finishedPUrl.data");
	DoLoadHashSet(finishedPackageUrlList, filePath);
}

void CPathInfo::SaveFinishedPicsPageUrl()  
{
	wstring filePath = modulePath + _T("\\finishedPUrl.data");
	DoSaveHashSet(finishedPackageUrlList, filePath);
}

//////////////////////////////////////////////////////////////////////////

void CPathInfo::DoLoadHashSet(TStrHashSet& strList, wstring filePath)
{
	int readCount = 0;
	FILE *file = _wfopen(filePath.c_str(), _T("r"));
	if (file != NULL)
	{
		char line[MAX_PATH]; /* or other suitable maximum line size */
		memset(line, 0, MAX_PATH);
		while (fgets(line, sizeof(line), file) != NULL) /* read a line */
		{
			int len = strlen(line);
			if (len > 1 && len < MAX_PATH)
			{
				line[len - 1] = '\0';
				strList.insert(line);
				readCount++;
			}
		}
		fclose(file);
	}
	tTestLog("[" << (long)this << "] Load " << readCount << " url From " << filePath.c_str());
}

void CPathInfo::DoSaveHashSet(TStrHashSet& strList, wstring filePath)
{
	if (strList.size() == 0) return;

	int count = 0;
	TStrHashSet::iterator iter = strList.begin();
	CFile file;
	if (file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite))
	{
		while (iter != strList.end())
		{
			string url = *iter;
			file.Write(url.c_str(), url.length());
			file.Write("\n", 1);
			iter++;
			count++;
		}
		file.Close();
	}
	tTestLog("[" << (long)this << "] Save " << count << " url To " << filePath.c_str());
}


//////////////////////////////////////////////////////////////////////////
// 加载未完成的任务到taskVec中
void CPathInfo::LoadUnfinishedPicTask(vector<TPicTaskInfo>& taskVec)
{
	wstring filePath = modulePath + _T("\\unFinishedTask.data");

	int readCount = 0;
	FILE *file = _wfopen(filePath.c_str(), _T("r"));
	if (file == NULL)
	{
		tTestLog("[" << (long)this << "] failed to open \"" << filePath.c_str() << "\"");
		return;
	}

	char line[MAX_PATH]; 
	memset(line, 0, MAX_PATH);
	while (fgets(line, sizeof(line), file) != NULL) /* read a line */
	{
		int len = strlen(line);
		if (len > 1 && len < MAX_PATH)
		{
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';
			string url = line;
			if (fgets(line, sizeof(line), file) != NULL)
			{
				USES_CONVERSION;
				wchar *wstr = A2W(line);
				int wlen = wcslen(wstr);
				if (wlen > 1 && wlen < MAX_PATH)
				{
					if (wstr[wlen - 1] == '\n')
						wstr[wlen - 1] = '\0';
					wstring savePath = wstr;
					taskVec.push_back(make_pair(url, savePath));
				}
			}
			readCount++;
		}
	}
	fclose(file);

	tTestLog("[" << (long)this << "] Load " << readCount << " url From unFinishedTask.data");
}

void CPathInfo::SaveUnfinishedPicTask(vector<TPicTaskInfo>& taskVec)
{
	wstring filePath = modulePath + _T("\\unFinishedTask.data");
	int count = 0;
	vector<TPicTaskInfo>::iterator iter = taskVec.begin();
	CFile file;
	if (file.Open(filePath.c_str(), CFile::modeCreate | CFile::modeWrite))
	{
		while (iter != taskVec.end())
		{
			string url = iter->first;
			wstring savePath = iter->second;
			USES_CONVERSION;
			string saveP = W2A(savePath.c_str());
			file.Write(url.c_str(), url.length());
			file.Write("\n", 1);
			file.Write(saveP.c_str(), saveP.length());
			file.Write("\n", 1);
			iter++;
			count++;
		}
		file.Close();
	}
	tTestLog("[" << (long)this << "] Save " << count << " url To unFinishedTask.data");
}
