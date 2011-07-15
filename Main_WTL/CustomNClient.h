#pragma once
#include <atlmisc.h>

template<class T>
class CCustomNClient : public CMessageMap
{
protected:
	CBrush  brBkground;
	ATL::CString strCaption;
	CRect   rectWnd;
	int     captionHeight;
	CRect   rectButtons;
	CRect   rectIcon;
	CRect   rectBtnMin;
	CRect   rectBtnMax;
	CRect   rectBtnExit;
	BOOL    bNCActive;    // 窗口是否活动

public:
	
	CCustomNClient(void)
	{
	}
	~CCustomNClient(void){}

	BEGIN_MSG_MAP(CCustomNClient)
		MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_NCACTIVATE, OnNcActivate)
		MESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONUP, OnNcLButtonUp)
		MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
	END_MSG_MAP()

	void DrawFrame()
	{
		T* dlg = static_cast<T*>(this);
		CWindowDC dc(dlg->m_hWnd);
		CRect wndRect;
		dlg->GetWindowRect(&wndRect);
		
		//dc.ExcludeClipRect(0, 0, wndRect.Width(), 20);
		// Draw Frame

		HBRUSH brush = CreateSolidBrush(RGB(0, 200, 200));
		HBRUSH oldBr = (HBRUSH)SelectObject(dc.m_hDC, (HGDIOBJ)brush);
		FillRect(dc.m_hDC, &wndRect, brush);

		SelectObject(dc.m_hDC, (HGDIOBJ)oldBr);
		dc.SelectClipRgn(NULL);
	}

	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		CRgn rgn = (HRGN)wParam;
		DrawFrame();

 		return 1;
	}
	LRESULT OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		BOOL bActive = (BOOL)wParam;
		DrawFrame();

		bHandled = false;
		return 0;
	}
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bCalcValidRects = (BOOL)wParam;
		//T* pT = static_cast<T*>(this);
		//pT->OnNcCalcSize(uMsg, bCalcValidRects);

		bHandled = false;
		return -1;
	}
	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		bHandled = false;
		return 0;
	}
	LRESULT OnNcLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		bHandled = false;
		return 0;
	}
	LRESULT OnNcMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		bHandled = false;
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
		// 屏蔽最大最小关闭消息.
		if (lRet==HTZOOM || lRet == HTMINBUTTON || lRet == HTCLOSE)
			return HTCAPTION;
		else
			return lRet;
	}
};
