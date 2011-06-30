#include "stdafx.h"
#include "RawCriSection.h"

CRawCriSection::CRawCriSection() : iCriSession( NULL )
{
}

CRawCriSection::~CRawCriSection()
{
	Close();
}

bool CRawCriSection::Create()
{
	if( !iCriSession )
	{
		iCriSession = new CRITICAL_SECTION;
		::InitializeCriticalSection( iCriSession );
	}
	return true;
}

void CRawCriSection::Wait()
{
	::EnterCriticalSection( iCriSession );
}

void CRawCriSection::Signal()
{
	::LeaveCriticalSection( iCriSession );	
}

void CRawCriSection::Close()
{
	if( iCriSession )
	{
		::DeleteCriticalSection( iCriSession );
		delete iCriSession;
		iCriSession = NULL;
	}
}

