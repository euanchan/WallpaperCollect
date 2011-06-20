#include "StdAfx.h"

#include <time.h>
#include <io.h>

#include "Log.h"
#include "Tool.h"
#include "PathInfo.h"
#include "File.h"

CLogXml::CLogXml(void)
{

}

CLogXml::CLogXml(const wstring& logFileName)
{
	Init(logFileName);	
}

CLogXml::~CLogXml(void)
{

}

void CLogXml::Save()
{
	m_doc.SaveFile(m_strPath.c_str());
}

void CLogXml::Close()
{
	m_doc.SaveFile(m_strPath.c_str());
	m_doc.Clear();
}
BOOL CLogXml::LoadFile(const wstring& logFileName)
{
	if (_T("") == logFileName)
	{
		return FALSE;
	}
	Init(logFileName);

	return TRUE;
}
void CLogXml::Init(const wstring& logFileName)
{
	wchar szPath[MAX_PATH] = {0};
	CString strPath;

	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	wcscpy(wcsrchr(szPath, _T('\\')), _T("\\Log\\"));
	strPath = szPath;

	MakeSurePathExists(strPath, FALSE);
	if (strPath.Find('\\') + 1 != strPath.GetLength())
	{
		strPath += '\\';
	}
	wstring wstrPath = strPath + logFileName.c_str() + _T(".xml");

	USES_CONVERSION;
	m_strPath = W2A(wstrPath.c_str());

	TiXmlNode* pNode = NULL;
	TiXmlElement* pChild = NULL;
	if (_access(m_strPath.c_str(), 0) != -1)
	{
		m_doc.LoadFile(m_strPath.c_str());
	}
	else
	{
		TiXmlDeclaration* dec = new TiXmlDeclaration( "1.0" , "UTF-8","yes");
		m_doc.LinkEndChild(dec);

		TiXmlElement* RootElement;
		RootElement=new TiXmlElement("LogFile");
		if (RootElement)
		{
			m_doc.LinkEndChild(RootElement);
		}
	}

}

void CLogXml::AddLog(const char* pStrFmt, ...)
{
	USES_CONVERSION;
	CStringA strNewLog = "";
	va_list args;
	va_start(args, pStrFmt);
	strNewLog.FormatV(pStrFmt, args);
	va_end(args);

	AddLogA(strNewLog);
}

void CLogXml::AddLog(const wchar* pWStrFmt, ...)
{
	CString strNewLog = _T("");
	va_list args;
	va_start(args, pWStrFmt);
	strNewLog.FormatV(pWStrFmt, args);
	va_end(args);

	USES_CONVERSION;
	AddLogA(W2A(strNewLog));	
}

void CLogXml::AddLogA(const char* strNewLog)
{
	TiXmlElement* RootElement = m_doc.RootElement();
	if (NULL != RootElement)
	{
		TiXmlElement *LogElement = new TiXmlElement("LogItem");

		// 日期时间
		SYSTEMTIME st;
		GetLocalTime(&st);
		char strDate[20], strTime[30];
		sprintf(strDate, "%d-%d-%d", st.wYear, st.wMonth, st.wDay);
		sprintf(strTime, "%d-%d-%d", st.wHour, st.wMinute, st.wSecond);

		TiXmlElement *DateElement = new TiXmlElement("Date");
		TiXmlText* pDateText = new TiXmlText(strDate);
		DateElement->LinkEndChild(pDateText);

		LogElement->LinkEndChild(DateElement);

		TiXmlElement *TimeElement = new TiXmlElement("Time");
		TiXmlText* pTimeText = new TiXmlText(strTime);
		TimeElement->LinkEndChild(pTimeText);

		LogElement->LinkEndChild(TimeElement);

		TiXmlElement *ContentElement = new TiXmlElement("Content");
		TiXmlText* pContentText = new TiXmlText(strNewLog);
		ContentElement->LinkEndChild(pContentText);
		LogElement->LinkEndChild(ContentElement);

		TiXmlElement *ErrElement = new TiXmlElement("ErrId");
		TiXmlText* pErrText = new TiXmlText("0");
		ErrElement->LinkEndChild(pErrText);
		LogElement->LinkEndChild(ErrElement);

		RootElement->LinkEndChild(LogElement);
	}
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
DbLog::DbLog( const wchar_t *aFileName /*= NULL*/ )
{
	iFilePath = gPathInfo.ModulePath();

	iFilePath += aFileName;

	iBuf[0] = '\0';
}

DbLog::~DbLog()
{
}
void DbLog::Write( const char *aString )
{
	if( aString != NULL )
	{
		Write( aString, strlen(aString) );
	}
}
void DbLog::Write(const char *aData, int aLen, EWritePos aPos /*= EPEnd*/ )
{
	if( aData != NULL && aLen > 0 )
	{
		FileOp f;
		if( f.open( iFilePath.c_str(), FileOp::ZM_OPEN_W_ALWAYS) )
		{
			if(aPos == EPEnd /*  &&f.GetLength() > gSystem.iLogSizeLimit */)
			{
				f.close();
				if(FileOp::DelFile(iFilePath.c_str()))
				{
					Write(aData, aLen, EPBegin);
				}
				return;
			}
			f.seek(0, aPos);
			f.write((int8*)aData, aLen);
		}
		f.close();
	}
}
void DbLog::WriteHex(const char *aData, int aLen)
{
	if (aData != NULL && aLen > 0)
	{
		char *pHex = new char[aLen*3+10];
		memset( pHex, 0, aLen*3+10 );
		for( int i=0;i<aLen;i++ )
		{
			sprintf(pHex+i*3, "%02x ", (uint8)aData[i]);
		}
		Write( pHex, strlen(pHex) );
		delete []pHex;
	}
}

DbLog& DbLog::operator<<(EType type)
{
	switch( type )
	{
	case Time:
		{
			ZMTIME t = FileOp::ZMGetLocalTime();
			sprintf( iBuf + strlen(iBuf), "[%02d:%02d:%02d:%03d]", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds );
		}
		break;
	case Enter:
		strcat( iBuf, "\r\n" );
		break;
	case Flush:
		Write( iBuf );
		iBuf[0] = '\0';
		break;
	default:
		break;
	}
	return (*this);
}
DbLog& DbLog::operator << ( int aValue )
{
	int len = strlen(iBuf);
	if( len + 20 < DB_BUF_SIZE )
	{
		sprintf( iBuf + strlen(iBuf), "%d", aValue );
	}
	return (*this);
}
DbLog& DbLog::operator << ( float aValue )
{
	int len = strlen(iBuf);
	if( len + 20 < DB_BUF_SIZE )
	{
		sprintf( iBuf + strlen(iBuf), "%.2f", aValue );
	}
	return (*this);
}
DbLog& DbLog::operator << ( uint32 aValue )
{
	int len = strlen(iBuf);
	if( len + 20 < DB_BUF_SIZE )
	{
		sprintf( iBuf + strlen(iBuf), "0x%04x", aValue );
	}
	return (*this);
}
DbLog& DbLog::operator << ( const char *aStr )
{
	if( aStr )
	{
		int len = strlen(iBuf);
		if( len + strlen(aStr) < DB_BUF_SIZE - 20 )
		{
			strcat( iBuf, aStr );
		}
		else
		{
			memcpy( iBuf + len, aStr, DB_BUF_SIZE - len - 20 );
			iBuf[DB_BUF_SIZE - 20] = '\0';
		}
	}
	return (*this);
}
DbLog& DbLog::operator << ( const wchar *aWStr )
{
	if( aWStr )
	{
		int len = strlen(iBuf);
		int wlen = wcslen(aWStr);

		USES_CONVERSION;
		char* str = W2A(aWStr);
		if( len + wlen*3 < DB_BUF_SIZE - 20 )
		{
			strcat( iBuf, str );
			//UnicodeToUTF8( aWStr, iBuf + len, wlen+1 );
		}
		else
		{
			//UnicodeToUTF8( aWStr, iBuf + len, (DB_BUF_SIZE - 20 - len)/3 );
			memcpy( iBuf + len, str, DB_BUF_SIZE - len - 20 );
			iBuf[DB_BUF_SIZE - 20] = '\0';
		}
	}
	return (*this);
}