#include "stdafx.h"
#include "RawThread.h"

CRawThread::CRawThread() : iID( 0 ), iHandle( NULL ), iThreadFunc( NULL ), iParam( NULL )
{
}

CRawThread::~CRawThread(void)
{
	Stop();
}

bool CRawThread::Start( RawThreadFunc aFunc, void* aParam /*= NULL*/ )
{
	if( iHandle == NULL )
	{
		iThreadFunc = aFunc;
		iParam = aParam;
		iHandle = ::CreateThread( NULL, 0, ThreadProc, this, 0, &iID );
	}
	return iHandle != NULL;
}

DWORD CRawThread::ThreadProc( void* aParam )
{
	CRawThread* pThread = (CRawThread*)aParam;
	pThread->iThreadFunc( pThread->iParam );
	return 0;
}

void CRawThread::Stop()
{
	if( iHandle )
	{
		::TerminateThread( iHandle, 0 );
		iHandle = NULL;
	}
}

