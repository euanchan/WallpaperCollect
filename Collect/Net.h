#pragma once

#include "RawThread.h"

class CWebServer;
class __declspec(dllexport) CNet
{
public:
	CNet();
	~CNet();

	void Start();
	void Pause();
	void Stop();
	void AddTask(const string& url, const wstring& savePath);

protected:
	static void ThreadFunc( void* aParam );
	void DoWork();

private:
	typedef pair<string, wstring> TTaskInfo;
	vector<TTaskInfo> taskInfoVec;

	CWebServer* webServ;

	bool onWork;
	CRawThread     rawThread;
	//CRawCriSection rawCrisection;
};