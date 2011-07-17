#pragma once

#include <atlcrack.h>

class CEProgressBar
	: public CWindowImpl<CEProgressBar, CProgressBarCtrl>
{
public:
	CEProgressBar(void);
	~CEProgressBar(void);

	BEGIN_MSG_MAP(CEProgressBar)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()


	void OnPaint(CDCHandle dc);
	BOOL OnEraseBkgnd(CDCHandle dc);
	BOOL SetWindowText(LPCTSTR lpszString) throw()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		text = lpszString;
		return ::SetWindowText(m_hWnd, lpszString);
	}

public:
	CBitmap bitmap;
	ATL::CString text;
};
