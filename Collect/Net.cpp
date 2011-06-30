#include "StdAfx.h"
#include "Net.h"
#include "WebServer.h"


CNet::CNet()
:  onWork(false)
{
	webServ = new CWebServer();
}

CNet::~CNet()
{
	delete webServ;
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
		onWork = false;
	// TODO: Save unFinished task to file
}

void CNet::AddTask(const string& url, const wstring& savePath)
{
	vector<TTaskInfo>::iterator iter = taskInfoVec.begin();
	for (; iter != taskInfoVec.end(); ++iter)
	{
		if (url == iter->first)
			return;
	}
	taskInfoVec.push_back(make_pair(url, savePath));

	// TODO: resume if pause.
}

//////////////////////////////////////////////////////////////////////////
void CNet::DoWork()
{
	int failCount = 0;
	while (onWork)
	{
		if (taskInfoVec.size() > 0)
		{
			TTaskInfo info = taskInfoVec[0];
			if (webServ->DownLoadFile(info.first, info.second))
			{
				failCount = 0;
				taskInfoVec.erase(taskInfoVec.begin());
			}
			else
			{
				Sleep(1000 * 5);
				if (failCount++ > 2)
				{
					taskInfoVec.erase(taskInfoVec.begin());
					taskInfoVec.push_back(info);
					failCount = 0;
				}
			}
		}
		// TODO: if task is empty pause. wait for new task.

		// TODO: load unfinished task save as file last time.
	}
}

