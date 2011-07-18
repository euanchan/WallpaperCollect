#pragma once

class CEScrollBar
	: public CWindowImpl<CEScrollBar, CScrollBar>
{
public:
	CEScrollBar(void);
	~CEScrollBar(void);

	BEGIN_MSG_MAP(CEScrollBar)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)

	END_MSG_MAP()

	void OnPaint(CDCHandle dc);
	BOOL OnEraseBkgnd(CDCHandle dc);
};
