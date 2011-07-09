#pragma once

#include "RawThread.h"
#include "RawCriSection.h"

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

	// 保存未完成任务到本地
	void SaveUnfinishedTask();
	// 加载本地文件的未完成任务
	void LoadUnfinishedTask();
	// 发送消息到主线程，通知更新进度条
	bool UpdateProcess();

protected:
	static void ThreadFunc( void* aParam );
	void DoWork();

private:
	vector<TPicTaskInfo> taskInfoVec;
	vector<TPicTaskInfo>::iterator iter;

	CWebServer* webServ;

	bool onWork;
	CRawThread     rawThread;
	// 
	CRawCriSection rawCrisection;

	// 记录总任务数，用于显示下载总进度
	uint16  taskCount;           
	uint16  taskFinishedCount;   // 全部下载完成时置0
};