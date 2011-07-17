#include "StdAfx.h"
#include "EProgressBar.h"
#include "Resource.h"

CEProgressBar::CEProgressBar(void)
{
	bitmap.LoadBitmap(IDB_BITMAP_PROGRESS);
}

CEProgressBar::~CEProgressBar(void)
{
}

void CEProgressBar::OnPaint(CDCHandle /*dc*/)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(&ps);

	RECT rect = {0};
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	RECT txtRect = rect;
	UINT pos = GetPos();
	if (pos <= 0) return;
	rect.right -= (rect.right - rect.left) * (float)(1.00 - pos / 100.0) + 2;
	rect.bottom -= 2;
	rect.left += 2;
	rect.top += 2;

	//HBRUSH brush = CreateHatchBrush(HS_BDIAGONAL, RGB(200, 50, 80));
	HBRUSH brush = CreatePatternBrush(bitmap);
	HBRUSH oldBr = (HBRUSH)SelectObject(hdc, (HGDIOBJ)brush);
	FillRect(hdc, &rect, brush);

	// Draw text
	if (text.GetLength() > 2)
	{
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, text, text.GetLength(), &txtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	SelectObject(hdc, (HGDIOBJ)oldBr);
	DeleteObject((HGDIOBJ)brush);

	EndPaint(&ps);
}

BOOL CEProgressBar::OnEraseBkgnd(CDCHandle /*dc*/)
{
	CDC dc = GetWindowDC();
	RECT rect = {0};
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	CPen pen = CreatePen(PS_SOLID, 1, RGB(24, 101, 55));
	HPEN oldPen = dc.SelectPen(pen);
	CBrush brush = CreateSolidBrush(RGB(250, 240, 240));
	HBRUSH oldBr = dc.SelectBrush(brush);
	dc.Rectangle(&rect);
	dc.SelectPen(oldPen);
	dc.SelectBrush(oldBr);
	return true;
}