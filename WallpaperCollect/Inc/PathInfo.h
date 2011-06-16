#ifndef CPATHINFO_H
#define CPATHINFO_H

#include "MyMacro.h"

class CPathInfo
{
public:
	CPathInfo();
	virtual ~CPathInfo();

	void InitPathInfo();   // 初始化程序路径
	const wchar_t* ModulePath();

	wstring modulePath;
};

//本地路径对象
MakeObjPtrFun( CPathInfo, GetObjPtr_ZMPathInfo )
#define gPathInfoPtr ((CPathInfo*&)GetObjPtr_ZMPathInfo())
#define gPathInfo (*(CPathInfo*&)GetObjPtr_ZMPathInfo())

#endif