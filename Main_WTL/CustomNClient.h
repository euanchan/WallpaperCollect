#pragma once
#include <atlmisc.h>

template <class T>
class CCustomNClient : public CMessageMap
	//: public CDialogImpl<CCustomNClient>
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
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_NCACTIVATE, OnNcActivate)
		MESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONUP, OnNcLButtonUp)
		MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pt = static_cast<T*>(this);

		BOOL bRet; 
		CRgn m_rgn1, m_rgn2; 
		RECT rc; 

		pt->GetWindowRect(&rc); 
		OffsetRect(&rc, -rc.left, -rc.top); 
		m_rgn1.CreateRoundRectRgn(rc.left, rc.top, rc.right + 1,rc.top - 45,12,12); 
		m_rgn2.CreateRoundRectRgn(rc.left,rc.top + 18, rc.right + 1,rc.bottom + 2,12,12); 
		m_rgn2.CombineRgn(m_rgn1, m_rgn2, RGN_OR); 
		pt->SetWindowRgn(m_rgn2, TRUE);

		pt->SetWindowPos(NULL, 0, 0, 0, 0, 
			SWP_FRAMECHANGED|SWP_NOOWNERZORDER|SWP_NOMOVE|SWP_NOSIZE);
		return 0;
	}

	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRgn rgn = (HRGN)wParam;
		rgn.
		T* pT = static_cast<T*>(this);
		HDC hdc = pT->GetDC();
		RECT rc;
		pT->GetClientRect(&rc);
		HBRUSH brush = CreateSolidBrush(RGB(0, 200, 200));
		HBRUSH oldBr = (HBRUSH)SelectObject(hdc, (HGDIOBJ)brush);
		FillRect(hdc, &rc, brush);

		DeleteObject((HGDIOBJ)brush);

		return 0;
	}
	LRESULT OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		BOOL bActive = (BOOL)wParam;

		return 0;
	}
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bCalcValidRects = (BOOL)wParam;
		//T* pT = static_cast<T*>(this);
		//pT->OnNcCalcSize(uMsg, bCalcValidRects);

		return 0;
	}
	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		return 0;
	}
	LRESULT OnNcLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		return 0;
	}
	LRESULT OnNcMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt = _WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		return 0;
	}
};
