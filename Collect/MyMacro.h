#ifndef MYMACRO_H
#define MYMACRO_H

// 计算数组元素个数
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

#define MEMSTZERO(x,y) memset(x,0x00,sizeof(y))
#define MEMBUFZERO(x)  memset(x,0x00,sizeof(x))

// 安全的字符拷贝
#define SAFESTRNCPY(x,y)  strncpy(x,y,sizeof(x)); x[sizeof(x) -1] =0x00;

// 安全释放指针
#define SAFE_RELEASE(p) {if ((p)) { (p)->Release(); (p) = NULL; }}

// 安全删除指针(非数组指针)
#define SAFE_DELETE(p) {if ((p) != NULL) { delete (p); (p) = NULL; }}

// 安全销毁窗口
#define SAFE_DESTROYWINDOW(hwnd) {if (::IsWindow((hwnd))){::DestroyWindow(hwnd);}}

// 表达式错误则赋值
#define IFTF(b,setf1) {if (!(b)){(setf1) = 0;}}


//////////////////////////////////////////////////////////////////////////
void*& GetPtrByName( const char* aName );

#define MakeObjPtrFun( name, fun ) \
	inline void*& fun() \
{ \
	static void*& ptr = GetPtrByName( #name ); \
	return ptr; \
}

#endif