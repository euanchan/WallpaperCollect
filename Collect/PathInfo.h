#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"
#include <hash_set>
using stdext::hash_set;

// struct htraits 
// {
// 	// comparisons
// 	bool operator()(const string& lhs,const string& rhs) const 
// 	{
// 		return !(lhs.compare(rhs) == 0); 
// 	}
// 	// hashing function
// 	size_t operator()(const string& key) const 
// 	{
// 		// hash _Keyval to size_t value by pseudorandomizing transform
// 		size_t _Val = 2166136261U;
// 		size_t _First = 0;
// 		size_t _Last = key.size();
// 		size_t _Stride = 1 + _Last / 10;
// 
// 		if (_Stride < _Last)
// 			_Last -= _Stride;
// 		for(; _First < _Last; _First += _Stride)
// 			_Val = 16777619U * _Val ^ (size_t)key[_First];
// 		return (_Val);
// 	}
// 	// bucket information
// 	static const size_t bucket_size = 4u;
// 	static const size_t min_buckets = 8u;
// };
// 
// typedef hash_set<string, htraits> TStrHashSet1;
typedef hash_set<string> TStrHashSet;


class __declspec(dllexport) CPathInfo
{
public:
	static CPathInfo* GetInstance();
	void ReleaseInstance();
	void InitPathInfo();   // 初始化程序路径

	//////////////////////////////////////////////////////////////////////////
	const wchar_t* GetModulePath();
	const wchar_t* GetCachePath();
	const wchar_t* GetThumbnailCachePath();
	const wchar_t* GetSavePathRoot();
	void SetSavePathRoot(const wstring& path);


	//////////////////////////////////////////////////////////////////////////
	void LoadTaskedPicsPageUrl();     // 从本地文件导入已加载到下载任务链表的 壁纸辑url
	void SaveTaskedPicsPageUrl();     // 保存已加载到下载任务链表的 壁纸辑url 到本地文件
	void InsertTaskedPicsPageUrl(const string& url)
	{
		taskedUrlList.insert(url);
	}
	void EraserTaskedPicsPageUrl(const string& url)
	{
		taskedUrlList.erase(url);
	}
	bool CurPicsPageUrlTasked(const string& url) // 判断当前url是否在上一次程序运行时添加到下载任务中
	{
		TStrHashSet::const_iterator iter = taskedUrlList.begin();
		iter = taskedUrlList.find(url);
		return iter != taskedUrlList.end();
	}

	//////////////////////////////////////////////////////////////////////////
	void LoadFinishedPicsPageUrl();   // 从本地文件导入已完整下载的 壁纸辑url
	void SaveFinishedPicsPageUrl();   // 保存已完整下载的 壁纸辑url 到本地文件
	void InsertFinishedPicsPageUrl(const string& url)
	{
		finishedPackageUrlList.insert(url);
	}
	bool CurPicsPageUrlFinished(const string& url) // 判断当前url是否已下载完成
	{
		TStrHashSet::const_iterator iter = finishedPackageUrlList.begin();
		iter = finishedPackageUrlList.find(url);
		return iter != finishedPackageUrlList.end();
	}

	//////////////////////////////////////////////////////////////////////////
	void LoadUnfinishedPicTask(vector<TPicTaskInfo>& taskVec); // 加载未完成壁纸下载任务
	void SaveUnfinishedPicTask(vector<TPicTaskInfo>& taskVec); // 保存未完成壁纸下载任务


protected:
	CPathInfo();
	virtual ~CPathInfo();

	void DoLoadHashSet(TStrHashSet& strList, wstring filePath);
	void DoSaveHashSet(TStrHashSet& strList, wstring filePath);

private:
	static CPathInfo *instance;
	wstring modulePath;
	wstring savePathRoot;
	wstring cachePath;
	wstring thumbnailCachePath;
	TStrHashSet taskedUrlList;            // 该页面包含的所有辑上一次都添加到任务链表中，未检测是否完成
	TStrHashSet finishedPackageUrlList;   // 已检测确定该页面包含的所有辑都已下载完
};

//本地路径对象
#define gPathInfo CPathInfo::GetInstance()
// MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
// #define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
// #define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif