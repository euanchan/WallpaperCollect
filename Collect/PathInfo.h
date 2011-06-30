#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"
#include <hash_set>
using stdext::hash_set;


struct htraits 
{
	// comparisons
	bool operator()(const string& lhs,const string& rhs) const 
	{
		return !(lhs.compare(rhs) == 0); 
	}
	// hashing function
	size_t operator()(const string& key) const 
	{
		unsigned long __h = 0;
		for (size_t i = 0 ; i < key.size() ; i ++)
			__h = 5*__h + key[i];
		return size_t(__h);
	}
	// bucket information
	static const size_t bucket_size = 10u;
	static const size_t min_buckets = 20u;
};
typedef hash_set<string, htraits> TStrHashSet;


class __declspec(dllexport) CPathInfo
{
public:
	static CPathInfo* GetInstance();
	void InitPathInfo();   // 初始化程序路径
	void LoadUrlMap();     // 从本地文件加载已加载的url到hashmap
	void SaveUrlMap();     // 保存已加载url的hashmap到本地文件
	void InsertUrlToFile(const string& url);     // 将url存入hashmap中
	bool PageLoaded(const string& url); // 判断当前url是否已处理
	wstring ModulePath();
	wstring CachePath();
	wstring ThumbnailCachePath();
	wstring GetSavePathRoot();
	void SetSavePathRoot(const wstring& path);
protected:
	CPathInfo();
	virtual ~CPathInfo();

private:
	static CPathInfo *instance;
	wstring modulePath;
	wstring savePathRoot;
	wstring cachePath;
	wstring thumbnailCachePath;
};

//本地路径对象
#define gPathInfo CPathInfo::GetInstance()
// MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
// #define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
// #define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif