
// #include "Global.h"
#include "stdafx.h"
#include "File.h"

FileOp::FileOp(void)
	:m_pFILE(INVALID_HANDLE_VALUE)
{
}

FileOp::~FileOp(void)
{
	close();
}

//获取文件修改时间:0 创建时间;1 访问时间;2 修改时间
TTime FileOp::GetFileTime(uint8 type)		
{
	FILETIME filetime, localfiletime;
	SYSTEMTIME systemtime;
	TTime zmtime;
	memset(&zmtime, 0, sizeof(TTime));
	if (0 == type)
	{
		::GetFileTime(m_pFILE, &filetime, NULL, NULL);
	}
	else if ( 1 == type)
	{
		::GetFileTime(m_pFILE, NULL, &filetime, NULL);
	}
	else
	{
		::GetFileTime(m_pFILE, NULL, NULL, &filetime);
	}
	::FileTimeToLocalFileTime(&filetime, &localfiletime);
	::FileTimeToSystemTime(&localfiletime, &systemtime);

	zmtime.wYear	= systemtime.wYear;
	zmtime.wMonth	= (uint8)systemtime.wMonth;
	zmtime.wDay		= (uint8)systemtime.wDay;
	zmtime.wHour	= (uint8)systemtime.wHour;
	zmtime.wMinute	= (uint8)systemtime.wMinute;
	zmtime.wSecond	= (uint8)systemtime.wSecond;

	return zmtime;
}

//获取计数时间(返回毫秒)
uint32 FileOp::GetTime(void)
{
	return GetTickCount();
}

//获取本地当前时间
TTime FileOp::GetLocalTime(void)	
{
	SYSTEMTIME systemtime;
	TTime zmtime;
	::GetLocalTime(&systemtime);
		
	zmtime.wYear	= systemtime.wYear;
	zmtime.wMonth	= (uint8)systemtime.wMonth;
	zmtime.wDay		= (uint8)systemtime.wDay;
	zmtime.wHour	= (uint8)systemtime.wHour;
	zmtime.wMinute	= (uint8)systemtime.wMinute;
	zmtime.wSecond	= (uint8)systemtime.wSecond;
	zmtime.wMilliseconds = systemtime.wMilliseconds;

	return zmtime;
}


BOOL FileOp::open(const wchar* pFileName,uint8 openMode,uint8 shareMode)
{
	if( NULL == pFileName ) return FALSE;
	if( INVALID_HANDLE_VALUE != m_pFILE ) close();
	uint32 accessM = 0;
	uint32 shareM = 0;
	uint32 openM = 0;

	bool bBuildDirectory = false;
	switch (openMode)			
	{
		case E_CREATE_W:	
			openM = CREATE_ALWAYS;
			accessM = GENERIC_WRITE;
			bBuildDirectory = true;
			break;
		case E_OPEN_R_EXIST:
			openM = OPEN_EXISTING;
			accessM = GENERIC_READ;
			break;
		case E_OPEN_W_EXIST:
			openM = OPEN_EXISTING;
			accessM = GENERIC_WRITE;
			break;
		case E_OPEN_RW_EXIST:
			openM = OPEN_EXISTING;
			accessM = GENERIC_READ|GENERIC_WRITE;
			break;
		case E_OPEN_R_ALWAYS:
			openM = OPEN_ALWAYS;
			accessM = GENERIC_READ;
			bBuildDirectory = true;
			break;
		case E_OPEN_W_ALWAYS:
			openM = OPEN_ALWAYS;
			accessM = GENERIC_WRITE;
			bBuildDirectory = true;
			break;
		case E_OPEN_RW_ALWAYS: 
			openM = OPEN_ALWAYS;
			accessM = GENERIC_READ | GENERIC_WRITE;
			bBuildDirectory = true;
			break;
		default:
			return FALSE;
	};

	switch(shareMode)
	{
		case E_SHARE_R:
			shareM = FILE_SHARE_READ;
			break;
		case E_SHARE_W:
			shareM = FILE_SHARE_WRITE ;
			break;
		case E_SHARE_RW:
			shareM = FILE_SHARE_WRITE|FILE_SHARE_READ;
			break;
		case E_SHARE_NONE:	
			shareM = 0;
			break;		
		default:
			return FALSE;
	};

	//iFullPath = pFileName;
	//TODO
	//iPath = iFullPath.SplitFilePath();

	if (bBuildDirectory)
	{
// 		TUnicode path = pFileName;
// 		ZMPathSplit( path, &path );
// 		BuildDirectory( path );
	}
	m_pFILE = ::CreateFile(pFileName,accessM,shareM,NULL,openM, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD err = GetLastError();
 
	return m_pFILE != INVALID_HANDLE_VALUE ;
}

BOOL FileOp::close()
{
	if( INVALID_HANDLE_VALUE != m_pFILE )
	{
		if(CloseHandle(m_pFILE) )
			m_pFILE = INVALID_HANDLE_VALUE;
		else
			return FALSE;
	}

	return TRUE;
}

void FileOp::fputs(int8* pString)
{
	//if( INVALID_HANDLE_VALUE != m_pFILE )
		//::fputs(pString,m_pFILE);
}

void FileOp::fgets(int8* pString,uint32 bufsize)
{
	//if( INVALID_HANDLE_VALUE != m_pFILE )
		//::fgets(pString,bufsize,m_pFILE);
}

uint32 FileOp::read(int8* pBuf,uint32 size)
{
	if( INVALID_HANDLE_VALUE == m_pFILE ) return 0;
	DWORD wr=0;
	::ReadFile(m_pFILE,pBuf,size,&wr,NULL);	
	return wr;
}
uint32 FileOp::write(int8* pBuf,uint32 size)
{
// 	bool bFull = false;
	int fcurr = GetPosition();
	int fsize = GetLength();
	//存储空间检查
// 	if( (fcurr + size > fsize) && !IsFreeSpaceEnough( iPath.Ptr() ) )
// 	{
// 		PostMSG( ZMMSG_ERROR_TIP, TEXT_CUNCUKONGJIANBUZU, 0 );
// 		bFull = true;
// 	}

	if( INVALID_HANDLE_VALUE == m_pFILE ) return 0;
	DWORD wr=0;
	::WriteFile(m_pFILE,pBuf,size,&wr,NULL);
	if (0 == wr) wr = -1;	// 各平台返回-1为写失败

// 	if( wr == -1 && !IsFreeSpaceEnough( iPath.Ptr() ) )
// 	{
// 		PostMSG( ZMMSG_ERROR_TIP, TEXT_CUNCUKONGJIANBUZU, 0 );
// 		return -1;
// 	}
// 	if( bFull )
// 	{
// 		return -1;
// 	}
	return wr;	
}

uint32 FileOp::GetLength()
{
	if( INVALID_HANDLE_VALUE == m_pFILE ) return 0;
	return ::GetFileSize(m_pFILE,NULL);
}


BOOL FileOp::seek(uint32 pos,uint8 from)
{
	if( INVALID_HANDLE_VALUE == m_pFILE ) return FALSE;
	uint32 origin;
	switch(from)
	{
		case FILE_SEEK_BEGIN:
			origin = FILE_BEGIN ;
			break;
		case FILE_SEEK_CURRENT:
			origin = FILE_CURRENT ;
			break;
		case FILE_SEEK_END:
			origin = FILE_END;
			break;
		default:
			return FALSE;
	}
	::SetFilePointer(m_pFILE,pos,NULL,origin);
	return TRUE;
}

BOOL FileOp::flush()
{
	if( INVALID_HANDLE_VALUE == m_pFILE ) return FALSE;
	return ::FlushFileBuffers(m_pFILE);
}

uint32 FileOp::GetPosition()
{
	if( INVALID_HANDLE_VALUE == m_pFILE ) return 0;

	return ::SetFilePointer(m_pFILE,0,NULL,FILE_CURRENT);
}

const wchar* FileOp::GetFileName()
{
	// TODO
 	return iFullPath.c_str();
}

BOOL FileOp::MoveFile( wchar* pSourFName, wchar* pdestFName )
{
	return ::MoveFile( pSourFName, pdestFName );
}

BOOL FileOp::CopyFile( wchar* pSourFName, wchar* pdestFName )
{
	return ::CopyFile( pSourFName, pdestFName, FALSE );
}

BOOL FileOp::DelFile( const wchar* pFileName )
{
	return ::DeleteFile(pFileName);
}

BOOL FileOp::RenameFile(wchar* pOldName,wchar* pNewName)
{
	return ::MoveFile(pOldName,pNewName);
	//return ::CopyFile(pOldName,pNewName,FALSE);
}

BOOL FileOp::CreateDirectory(wchar* pPath)
{
	return ::CreateDirectory(pPath,NULL);
}

// BOOL ZMFile::DelOldFile(wchar* pFileName,uint8 outofday)
// {
// 	ZMFile file;
// 	file.open(pFileName,ZMFile::ZM_OPEN_R_EXIST);
// 	ZMTIME filewtime = file.ZMGetFileTime(1);
// 	ZMTIME comparetime = ZMFile::ZMGetLocalTime();
// 	file.close();
// 
// 	int def = CompareZmTime( comparetime, filewtime );
// 	if( def >= max(1,outofday) )
// 		return ::DeleteFile(pFileName);
// 	else
// 		return FALSE;
// }

// TODO:9
// BOOL ZMFile::DelDirectory(wchar * dir,uint8 outofday, int waittime /*= 0*/ )
// {
// 	HANDLE hSearch;
// 	WIN32_FIND_DATA fd;
// 	memset(&fd,0,sizeof(fd));
// 	wchar fname[MAX_PATH];
// 	memset(fname,0,sizeof(fname));
// 	zmstrcat(fname, dir); 
// 	zmstrcat(fname, TEXT("\\"));
// 	zmstrcat(fname, TEXT("*.*")); 
// 
// 	hSearch = FindFirstFile(fname, &fd);
// 	if( !hSearch )
// 	{
// 		return TRUE;
// 	}
// 	while( 0==lstrcmp(TEXT("."),fd.cFileName) || 0==lstrcmp(TEXT(".."),fd.cFileName))
// 	{
// 		memset(&fd,0,sizeof(fd));
// 		FindNextFile(hSearch, &fd);
// 	}
// 	if( lstrlen(fd.cFileName) )
// 	{
// 		memset(fname,0,sizeof(fname));
// 		zmstrcat(fname, dir); 
// 		zmstrcat(fname, TEXT("\\")); 
// 		zmstrcat(fname,fd.cFileName);
// 
// 		if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))	
// 		{
// 			DelDirectory(fname,outofday);
// 			::RemoveDirectory(fname); 
// 		}
// 		else
// 		{
// 			if(outofday)
// 				DelOldFile(fname,outofday);
// 			else
// 			{
// 				::DeleteFile(fname);
// 			}
// 		}
// 
// 		uint32 begintime = GetTickCount();
// 		while(1)
// 		{
// 			if( FindNextFile(hSearch, &fd) )
// 			{
// 				memset(fname,0,sizeof(fname));
// 				zmstrcat(fname, dir); 
// 				zmstrcat(fname, TEXT("\\")); 
// 				zmstrcat(fname,fd.cFileName);	
// 
// 				if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))		
// 				{	
// 					DelDirectory(fname,outofday);
// 					::RemoveDirectory(fname); 
// 				}
// 				else 
// 				{
// 					if(outofday)
// 						DelOldFile(fname,outofday);
// 					else
// 					{
// 						::DeleteFile(fname);
// 					}
// 				}
// 				//if( IsStopClear( begintime, waittime ) )
// 				//	break;
// 			}
// 			else	
// 			{
// 				break;	//查找结束
// 			}
// 		}
// 	}
// 	FindClose(hSearch);	
// 
// 	if(!RemoveDirectory(dir))
// 		return FALSE;
// 	
// 	return TRUE;
// }
//当前磁盘剩余空间

// uint64 ZMFile::GetDiskFreeSpace(wchar * pPath)
// { 
// 	if(NULL==pPath) return 0;
// 	uint64 iFreeBytesToCaller=0, iTotalBytes=0, iFreeBytes=0;
// 	if(GetDiskFreeSpaceEx(pPath,(PULARGE_INTEGER)&iFreeBytesToCaller, (PULARGE_INTEGER)&iTotalBytes, (PULARGE_INTEGER)&iFreeBytes))
// 	{
// 		return iFreeBytesToCaller;
// 	}
// 	return 0;
// }

// TODO:
// ZMList* ZMFile::FindFile( const wchar* pDir )
// {
// 	ZMList* pFileList = new ZMList();
// 	HANDLE hSearch;
// 	WIN32_FIND_DATA fd = {0};
// 	wchar fname[MAX_PATH] = {0};
// 	zmstrcat(fname, pDir); 
// 	zmstrcat(fname, TEXT("*.*"));
// 
// 	int len = 0;
// 	wchar* pFileName = NULL;
// 	hSearch = FindFirstFile(fname, &fd);
// 	while( hSearch )
// 	{
// 		if( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
// 		{
// 			len = zmstrlen( fd.cFileName ) + 1;
// 			pFileName = new wchar[len];
// 			memcpy( pFileName, fd.cFileName, len*2 );
// 			pFileList->Add( pFileName );
// 		}
// 		if( !FindNextFile(hSearch, &fd) )
// 		{
// 			break;
// 		}
// 	}
// 	return pFileList;
// }
