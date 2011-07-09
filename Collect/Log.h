#ifndef LOG_H
#define LOG_H

#include "tinyxml.h"

class CLogXml
{
public:
	CLogXml(void);
	CLogXml(const wstring& logFileName);
public:
	BOOL LoadFile(const wstring& logFileName);
	void Init(const wstring& logFileName);
public:
	void AddLog(const char* pStrFmt, ...);
	void AddLog(const wchar* pWStrFmt, ...);
	void AddLogA(const char* strNewLog);
	void Save();
	void Close();
public:
	~CLogXml(void);
public:
	TiXmlDocument m_doc;	
	string m_strPath;
};

#define DB_BUF_SIZE 1024

class __declspec(dllexport) DbLog
{
public:
	enum EType
	{
		Time,
		Enter,
		Flush
	};
	enum EWritePos
	{
		EPBegin,
		EPEnd
	};
public:
	DbLog( const wchar_t *aFileName = NULL );
	virtual ~DbLog();
public:
	void Write( const char *awstring ); 
	void Write( const char *aData, int aLen, EWritePos aPos = EPEnd );
	void WriteHex( const char *aData, int aLen );

	DbLog& operator << ( EType type );
	DbLog& operator << ( int aValue );
	DbLog& operator << ( float aValue );
	DbLog& operator << ( uint32 aValue );
	DbLog& operator << ( const char *aStr );
	DbLog& operator << ( const wchar_t *aWStr );
public:
	wstring iFilePath;
	char iBuf[DB_BUF_SIZE];
};


#ifdef LINUX
#define tTestLog( a )
#define tMainLog( a )
#define tYZGLog( a )
#define tSkLog( a )
#else
/*if( gSystem.iNeedLog )\*/

#define tDownloadLog( a ) \
		{\
			DbLog gLog( TEXT("download.txt") );\
			gLog << DbLog::Time << a << DbLog::Enter << DbLog::Flush;\
		}
#define tTestLog( a ) \
		{\
			DbLog gLog( TEXT("TestLog.txt") );\
			gLog << DbLog::Time << a << DbLog::Enter << DbLog::Flush;\
		}
#define tMainLog( a )\
		{\
			DbLog gLog( TEXT("MainLog.txt") );\
			gLog<<DbLog::Time<<a<<DbLog::Enter<<DbLog::Flush;\
		}
#endif



#endif