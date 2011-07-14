#pragma once
#include <atlcrack.h>
#include <atlmisc.h>
#define _WTL_USE_CSTRING
class CEButton
	: public CWindowImpl<CEButton, CButton>
	, public COwnerDraw<CEButton>
{
public:
	COLORREF frameColorNormal;
	COLORREF frameColorHover;
	COLORREF frameColorPress;
	COLORREF fontColor;
	bool     bHover;

public:
	DECLARE_WND_SUPERCLASS(NULL, _T("Button"))
	BEGIN_MSG_MAP(CEButton)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_MOUSEHOVER(OnMouseHover)
 		CHAIN_MSG_MAP_ALT(COwnerDraw<CEButton>, 1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
	CEButton(void)
		: frameColorNormal(RGB(221, 246, 255))
		, frameColorHover(RGB(124, 230, 255))
		, frameColorPress(RGB(0, 180, 255))
		, fontColor(RGB(0, 55, 22))
		, bHover(false)
	{}
	~CEButton(void){}


	void OnMouseHover(UINT, CPoint point)
	{
		if (!bHover)
		{
			bHover = true;
			Invalidate(0);
		}
	}
	BOOL OnMouseMove(UINT nFlags, CPoint point)
	{
		//跟踪鼠标信息,捕获MouseHover,MouseLeave
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		_TrackMouseEvent(&tme);

		return true;
	}
	BOOL OnMouseLeave()
	{
		bHover = false;
		Invalidate(0);
		return true;
	}
	void DrawItem(LPDRAWITEMSTRUCT ps)
	{
		HDC hdc = ps->hDC;
		DrawFrame(hdc, &ps->rcItem);
		DrawText(hdc, &ps->rcItem);
	}
	void DrawFrame(HDC& hdc, LPRECT rect);
	void DrawText(HDC& hdc, LPRECT rect);
};
