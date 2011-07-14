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

public:
	DECLARE_WND_SUPERCLASS(NULL, _T("Button"))
	BEGIN_MSG_MAP(CEButton)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
 		CHAIN_MSG_MAP_ALT(COwnerDraw<CEButton>, 1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
	CEButton(void)
		: frameColorNormal(RGB(200, 180, 255))
		, frameColorHover(RGB(0, 180, 255))
		, frameColorPress(RGB(200, 180, 0))
		, fontColor(RGB(0, 55, 22))
	{}
	~CEButton(void){}

	BOOL OnMouseMove(UINT nFlags, CPoint point)
	{
		//¸ú×ÙÊó±êÐÅÏ¢
		SetState(true);

		UpdateWindow();
		return true;
	}
	BOOL OnMouseLeave()
	{
		SetState(true);
		UpdateWindow();
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
