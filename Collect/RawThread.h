#if !defined(_CRAWTHREAD_H)
#define _CRAWTHREAD_H

typedef void (* RawThreadFunc)( void* );   //线程执行函数指针

class __declspec(dllexport) CRawThread
{
public:
	CRawThread();
	virtual ~CRawThread();

	bool Start( RawThreadFunc aFunc, void* aParam = NULL );
	void Stop();

protected:
	static DWORD WINAPI ThreadProc( void* aParam );	//内置线程函数

	DWORD			iID;				//线程ID
	HANDLE			iHandle;			//线程句柄
	RawThreadFunc	iThreadFunc;		//用户定义线程函数
	void*			iParam;				//用户线程参数
};

#endif  //_CRAWTHREAD_H
