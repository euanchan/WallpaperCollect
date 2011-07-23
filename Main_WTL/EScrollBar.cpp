#include "StdAfx.h"
#include "EScrollBar.h"

CEScrollBar::CEScrollBar(void)
{
}

CEScrollBar::~CEScrollBar(void)
{
}

void CEScrollBar::OnPaint(CDCHandle /*dc*/)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(&ps);

	RECT rect = {0};
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	HBRUSH brush = CreateSolidBrush(RGB(214, 233, 255));
	HBRUSH oldBr = (HBRUSH)SelectObject(hdc, (HGDIOBJ)brush);
	FillRect(hdc, &rect, brush);
	SelectObject(hdc, (HGDIOBJ)oldBr);
	DeleteObject((HGDIOBJ)brush);
// 
// 	// Draw text
// 	if (text.GetLength() > 2)
// 	{
// 		SetBkMode(hdc, TRANSPARENT);
// 		DrawText(hdc, text, text.GetLength(), &txtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
// 	}

	EndPaint(&ps);
}

BOOL CEScrollBar::OnEraseBkgnd(CDCHandle dc)
{
	
	return false;
}