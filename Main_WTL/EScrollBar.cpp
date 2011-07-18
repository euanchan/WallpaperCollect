#include "StdAfx.h"
#include "EScrollBar.h"

CEScrollBar::CEScrollBar(void)
{
}

CEScrollBar::~CEScrollBar(void)
{
}

void CEProgressBar::OnPaint(CDCHandle /*dc*/)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(&ps);

// 	RECT rect = {0};
// 	GetWindowRect(&rect);
// 	ScreenToClient(&rect);
// 	RECT txtRect = rect;
// 	UINT pos = GetPos();
// 	if (pos > 0)
// 	{
// 		rect.right -= (rect.right - rect.left) * (float)(1.00 - pos / 100.0) + 2;
// 		rect.bottom -= 2;
// 		rect.left += 2;
// 		rect.top += 2;
// 
// 		//HBRUSH brush = CreateHatchBrush(HS_BDIAGONAL, RGB(200, 50, 80));
// 		HBRUSH brush = CreatePatternBrush(bitmap);
// 		HBRUSH oldBr = (HBRUSH)SelectObject(hdc, (HGDIOBJ)brush);
// 		FillRect(hdc, &rect, brush);
// 		SelectObject(hdc, (HGDIOBJ)oldBr);
// 		DeleteObject((HGDIOBJ)brush);
// 	}
// 
// 	// Draw text
// 	if (text.GetLength() > 2)
// 	{
// 		SetBkMode(hdc, TRANSPARENT);
// 		DrawText(hdc, text, text.GetLength(), &txtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
// 	}

	EndPaint(&ps);
}