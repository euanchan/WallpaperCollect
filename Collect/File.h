#ifndef FILE_H__
#define FILE_H__

class FileOp
{
public:
	FileOp(void);
	virtual ~FileOp(void);

	//获取计数时间(返回毫秒)
	static uint32 FileOp::GetTime(void);

	//获取系统当前时间
	static TTime GetLocalTime(void);

	//获取文件修改时间:0 创建时间;1 访问时间;2 修改时间
	TTime GetFileTime(uint8 type = 2);
	
	//测试对象是否成功打开了一个文件
	BOOL IsOpened() { return m_pFILE != INVALID_HANDLE_VALUE ; }

	//打开一个文件,全是以二进制方式打开
	BOOL open(const wchar* pFileName,uint8 openMode,uint8 shareMode = E_SHARE_RW);
	enum 
	{
		E_CREATE_W			= 0x1,		//创建新文件，原来存在的删除
		E_OPEN_R_EXIST		= 0x2,		//打开文件，不存在则出错，存在则可读
		E_OPEN_W_EXIST		= 0x3,		//打开文件，不存在则出错，存在则可写
		E_OPEN_RW_EXIST		= 0x4,		//打开文件，不存在则出错，存在则可读写
		E_OPEN_R_ALWAYS		= 0x5,		//打开文件，不存在则创建，然后读
		E_OPEN_W_ALWAYS		= 0x6,		//打开文件，不存在则创建，然后写
		E_OPEN_RW_ALWAYS	= 0x7		//打开文件，不存在则创建，然后读写
	};
	enum
	{
		E_SHARE_R		= 0x01,			//共享文件读
		E_SHARE_W		= 0x02,			//共享文件写
		E_SHARE_RW		= 0x03,			//共享文件读写
		E_SHARE_NONE	= 0x04			//不共享文件读写
	};

	//关闭一个文件
	BOOL close();

	//读文件
	uint32 read(int8* pBuf,uint32 size);

	//写文件
	uint32 write(int8* pBuf,uint32 size);

	//把缓冲立即写入存储器
	BOOL  flush();

	//跟c语言的fputs类似
	void fputs(int8* pString);
	//跟c语言的fgets类似
	void fgets(int8* pString,uint32 bufsize);

	//得到文件长度
	uint32 GetLength();
	//移动文件读写指针,返回指针的当前位置
	BOOL seek(uint32 pos,uint8 from);
	enum
	{
		FILE_SEEK_BEGIN,
		FILE_SEEK_END,
		FILE_SEEK_CURRENT
	};
	//得到文件读写指针的当前位置
	uint32 GetPosition();

	//得到文件名
	const wchar* GetFileName();

	//磁盘文件操作
	static BOOL MoveFile( wchar* pSourFName, wchar* pdestFName );
	static BOOL CopyFile( wchar* pSourFName, wchar* pdestFName );
	static BOOL DelFile(const wchar* pFileName);
	static BOOL RenameFile(wchar* pOldName,wchar* pNewName);
	static BOOL CreateDirectory(wchar* pPath);
// 	static BOOL DelOldFile(wchar* pFileName,uint8 outofday );
// 	static BOOL DelDirectory(wchar * dir,uint8 outofday=0, int waittime = 0 );
// 	static uint64 GetDiskFreeSpace(wchar * pPath);

// 	static ZMList* FindFile( const wchar* pDir );//搜索目录文件，注意路径后需要“\\”
protected:
	HANDLE 	m_pFILE;				//文件指针
	wstring iFullPath;
	wstring iPath;
};



#endif





