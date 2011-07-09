#include "StdAfx.h"
#include "Net.h"
#include "WebServer.h"
#include "PathInfo.h"

extern HANDLE ghNetEvent;
extern HWND gWindowHandle;

CNet::CNet()
:  onWork(false)
,  taskCount(0)
,  taskFinishedCount(0)
{
	rawCrisection.Create();
	webServ = new CWebServer();
}

CNet::~CNet()
{
	rawThread.Stop();
	delete webServ;
	taskInfoVec.erase(taskInfoVec.begin(), taskInfoVec.end());
}

void CNet::ThreadFunc( void* aParam )
{
	CNet *net = (CNet*)aParam;
	net->DoWork();
}

void CNet::Start()
{
	if (!onWork)
	{
		tTestLog("[" << (long)this << "]" << "CNet::Start.");
		onWork = true;
		rawThread.Stop();
		rawThread.Start(ThreadFunc, this);
	}
}

void CNet::Pause()
{
	// TODO:
	// 	if (onWork)
	// 		onWork = false;
}

void CNet::Stop()
{
	if (onWork)
	{
		onWork = false;
		tTestLog("[" << (long)this << "]" << "CNet::Stop.");
	}
	// TODO: Save unFinished task to file
}

// TODO: 未去重
void CNet::AddTask(const string& url, const wstring& savePath)
{
	rawCrisection.Wait();

	iter = taskInfoVec.begin();
	for (; iter != taskInfoVec.end(); ++iter)
	{
		if (url == iter->first)
		{
			rawCrisection.Signal();
			return;
		}
	}
	taskInfoVec.push_back(make_pair(url, savePath));
	taskCount++;
	UpdateProcess();
// 	tTestLog("Net task push_back: " << url.c_str() << "  ___  " << savePath.c_str());

	rawCrisection.Signal();
	// TODO: resume if pause.
}

void CNet::SaveUnfinishedTask()
{
	gPathInfo->SaveUnfinishedPicTask(taskInfoVec);
}

void CNet::LoadUnfinishedTask()
{
	gPathInfo->LoadUnfinishedPicTask(taskInfoVec);
	taskCount = taskInfoVec.size();
	if (taskInfoVec.size() > 0)
		Start();
}

//////////////////////////////////////////////////////////////////////////
void CNet::DoWork()
{
	tTestLog("[" << (long)this << "]" << " CNet::DoWork Begin.");
	int failCount = 0;
	while (onWork)
	{
		if (taskInfoVec.size() > 0)
		{
			TPicTaskInfo info = *taskInfoVec.begin();
			if (webServ->DownLoadFile(info.first, info.second))
			{
				failCount = 0;
				rawCrisection.Wait();
				iter = taskInfoVec.erase(taskInfoVec.begin());
				taskFinishedCount++;
				UpdateProcess();
				rawCrisection.Signal();
			}
			else
			{
				Sleep(1000 * 5);
				if (failCount++ > 2)
				{
					rawCrisection.Wait();
					iter = taskInfoVec.erase(taskInfoVec.begin());
					taskInfoVec.push_back(info);
					rawCrisection.Signal();
					failCount = 0;
				}
			}
		}
		else
		{
			int i = WaitForSingleObject(ghNetEvent, INFINITE);
		}
		// TODO: if task is empty pause. wait for new task.

		// TODO: load unfinished task save as file last time.
	}
}

// 根据全局的窗口句柄，发送UI更新信息。完成一轮任务后，归0
bool CNet::UpdateProcess()
{
	if (gWindowHandle)
	{
		::PostMessage(gWindowHandle, MSG_UPDATE_TASK_LIST_PROCESS, taskFinishedCount, taskCount);
		if (taskFinishedCount == taskCount)
		{
			taskFinishedCount = 0;
			taskCount = 0;
		}
		return true;
	}
	return false;
}