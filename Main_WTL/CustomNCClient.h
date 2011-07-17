#pragma once
#include <atlmisc.h>

#define COLOR_DLG_BK             RGB(222, 232, 237)
#define COLOR_DLG_MINBTN_NORMAL  RGB(255, 233, 170)
#define COLOR_DLG_MINBTN_HOVER   RGB(196, 188, 166)
#define COLOR_DLG_MINBTN_PRESS   RGB(200, 200, 110)
#define COLOR_DLG_EXITBTN_NORMAL RGB(218, 191, 255)
#define COLOR_DLG_EXITBTN_HOVER  RGB(196, 119, 128)
#define COLOR_DLG_EXITBTN_PRESS  RGB(222, 100, 100)
#define COLOR_DLG_FRAME          RGB(81, 162, 255)

// 对话框窗体绘制内嵌类
template<class T>
class CCustomNCClient : public CMessageMap
{
public:
	enum SelectedCaptionBtn{NULL_BTN, MIN_BTN, EXIT_BTN};
protected:
	
	ATL::CString strCaption;
	int     captionHeight; // 标题栏高度
	int     bottomHeight;  // 底边框高度
	int     borderWitdh;   // 两边边框宽度
	CRect   rectIcon;
	CRect   rectBtnMin;
	CRect   rectBtnExit;
	int     minBtnWidth;
	int     exitBtnWidth;
	int     minBtnHeight;
	int     exitBtnHeight;
	COLORREF minBtnHover;
	COLORREF minBtnPress;
	COLORREF exitBtnHover;
	COLORREF exitBtnPress;
	COLORREF frameColor;
// 	HBITMAP  btnBmp;

	CBrush   brMinBtnNormal;           
	CBrush   brExitBtnNormal;          
	CBrush   brushBK;                  // 对话框背景色画刷
	SelectedCaptionBtn eHoverButton;   // 当前边框悬停按钮
	SelectedCaptionBtn ePressButton;   // 当前边框按下按钮

public:
	
	CCustomNCClient(void)
		: captionHeight(24)
		, bottomHeight(1)
		, borderWitdh(2)
		, exitBtnHeight(18)
		, exitBtnWidth(47)
		, minBtnHeight(16)
		, minBtnWidth(25)
		, eHoverButton(NULL_BTN)
		, ePressButton(NULL_BTN)
		, minBtnHover(COLOR_DLG_MINBTN_HOVER)
		, minBtnPress(COLOR_DLG_MINBTN_PRESS)
		, exitBtnHover(COLOR_DLG_EXITBTN_HOVER)
		, exitBtnPress(COLOR_DLG_EXITBTN_PRESS)
		, frameColor(COLOR_DLG_FRAME)
	{
		brushBK.CreateSolidBrush(COLOR_DLG_BK);
		brMinBtnNormal.CreateSolidBrush(COLOR_DLG_MINBTN_NORMAL);
		brExitBtnNormal.CreateSolidBrush(COLOR_DLG_EXITBTN_NORMAL);
	}
	~CCustomNCClient(void){}

	BEGIN_MSG_MAP(CCustomNCClient)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CTLCOLORDLG, OnCtlColorDlg)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
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
		
		CDC memDC;
		memDC.CreateCompatibleDC(dc.m_hDC);
 		HBITMAP bitmap = CreateCompatibleBitmap(dc.m_hDC, wndRect.Width(), wndRect.Height());
		HGDIOBJ oldObj = SelectObject(memDC, bitmap);

 		DoDrawFrame(&memDC);
		
// 		BLENDFUNCTION bf;
// 		bf.BlendOp = AC_SRC_OVER;
// 		bf.BlendFlags = 0;
// 		bf.AlphaFormat = 0;
// 		bf.SourceConstantAlpha = 10;

//  		dc.AlphaBlend(0, 0, wndRect.Width(), captionHeight, memDC.m_hDC, 
//  			0, 0, wndRect.Width(), captionHeight, bf);
		dc.BitBlt(0, 0, wndRect.Width(), captionHeight, memDC.m_hDC, 0, 0, SRCCOPY);
		dc.BitBlt(0, wndRect.Height() - bottomHeight, wndRect.Width(), bottomHeight,
			memDC.m_hDC, 0, wndRect.Height() - bottomHeight, SRCCOPY);
		dc.BitBlt(0, captionHeight, borderWitdh, wndRect.Height() - bottomHeight - captionHeight,
			memDC.m_hDC, 0, captionHeight, SRCCOPY);
		dc.BitBlt(wndRect.Width() - borderWitdh, captionHeight, borderWitdh,
			wndRect.Height() - bottomHeight - captionHeight, memDC.m_hDC, 
			wndRect.Width() - borderWitdh, captionHeight, SRCCOPY);

		dc.SelectClipRgn(NULL);
		SelectObject(memDC, oldObj);

		DeleteObject((HGDIOBJ)bitmap);
		memDC.DeleteDC();
		ReleaseDC(dlg->m_hWnd, dc.m_hDC);
	}

	void DoDrawFrame(CDC *pDC)
	{
		T* pDlg = static_cast<T*>(this);

		RECT windowRect;
		pDlg->GetWindowRect(&windowRect);
		pDlg->ScreenToClient(&windowRect);
		OffsetRect(&windowRect, -windowRect.left, -windowRect.top);

		int oldDc = pDC->SaveDC();
		CBrush brush = CreateSolidBrush(frameColor);
		pDC->FillRect(&windowRect, brush);

		// 绘制程序图标
 		pDC->DrawIcon(rectIcon.left, rectIcon.top, pDlg->GetIcon());

		// 绘制最小化、退出按钮
		pDC->FillRect(&rectBtnMin, brMinBtnNormal);
		pDC->FillRect(&rectBtnExit, brExitBtnNormal);

		if (eHoverButton == MIN_BTN)
		{
			brush = CreateSolidBrush(minBtnHover);
			pDC->FillRect(&rectBtnMin, brush);
		}
		else if (eHoverButton == EXIT_BTN)
		{
			brush = CreateSolidBrush(exitBtnHover);
			pDC->FillRect(&rectBtnExit, brush);
		}

		if (ePressButton == MIN_BTN)
		{
			brush = CreateSolidBrush(minBtnPress);
			pDC->FillRect(&rectBtnMin, brush);
		}
		else if (ePressButton == EXIT_BTN)
		{
			brush = CreateSolidBrush(exitBtnPress);
			pDC->FillRect(&rectBtnExit, brush);
		}

		pDC->RestoreDC(oldDc);
	}

	LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = false;
		return 0;
	}

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pDlg = static_cast<T*>(this);

		// center the dialog on the screen
		pDlg->CenterWindow();

		// 最小化、退出按钮位置
		RECT wndRect = {0};
		pDlg->GetWindowRect(&wndRect);
		pDlg->ScreenToClient(&wndRect);
		OffsetRect(&wndRect, -wndRect.left, -wndRect.top);
		rectBtnExit.top = 0;
		rectBtnExit.left = wndRect.right - wndRect.left - exitBtnWidth - 6;
		rectBtnExit.right = wndRect.right - wndRect.left - 6;
		rectBtnExit.bottom = exitBtnHeight;

		rectBtnMin = rectBtnExit;
		rectBtnMin.OffsetRect(-minBtnWidth - 1, 0);
		rectBtnMin.right -= exitBtnWidth - minBtnWidth; 

		// 程序图标, -3为将icon部分隐藏。。
		rectIcon.top = (captionHeight - GetSystemMetrics(SM_CYICON)) / 2 - 3;
		rectIcon.left = rectIcon.top;
		rectIcon.right = rectIcon.top + GetSystemMetrics(SM_CYICON);
		rectIcon.bottom = rectIcon.top + GetSystemMetrics(SM_CYICON);

		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		pDlg->SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		pDlg->SetIcon(hIconSmall, FALSE);

// 		btnBmp = (HBITMAP)LoadImage(NULL, _T("window.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		bHandled = false;  // 父类继续处理
		return false;
	}

	LRESULT OnCtlColorDlg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return (LRESULT)(HGDIOBJ)brushBK;  
	}

	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		CRgn rgn = (HRGN)wParam;
		DrawFrame();

		bHandled = true;
 		return 1;
	}
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bActive = (BOOL)wParam;
		DrawFrame();

		bHandled = false;
		return 0;
	}
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bActive = (BOOL)wParam;
		DrawFrame();

		bHandled = false;
		return 0;
	}
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 设置客户区大小
		BOOL bCalcValidRects = (BOOL)wParam;
		if (bCalcValidRects)
		{
			NCCALCSIZE_PARAMS *pNcCal = (NCCALCSIZE_PARAMS*)lParam;
			RECT& rc = pNcCal->rgrc[0];
			rc.top += captionHeight - GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYDLGFRAME);
			rc.bottom -= bottomHeight - GetSystemMetrics(SM_CYDLGFRAME);
			rc.left += borderWitdh - GetSystemMetrics(SM_CYDLGFRAME);
			rc.right -= borderWitdh - GetSystemMetrics(SM_CYDLGFRAME);
		}

		bHandled = false;
		return 0;
	}
	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UINT nHitTest = (UINT)wParam;
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		T* pDlg = static_cast<T*>(this);
		pDlg->ModifyStyle(WS_SYSMENU, NULL);
		pDlg->ScreenToClient(&pt);

		// Client point to Window point
		pt.x += borderWitdh;
		pt.y += captionHeight;

		if (rectBtnMin.PtInRect(pt))
			ePressButton = MIN_BTN;
		else if (rectBtnExit.PtInRect(pt))
			ePressButton = EXIT_BTN;
		else
			ePressButton = NULL_BTN;

		DrawFrame();

		bHandled = false;
		return 0;
	}
	LRESULT OnNcLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pDlg = static_cast<T*>(this);
		UINT nHitTest = (UINT)wParam;
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		pDlg->ScreenToClient(&pt);

		// Client point to Window point
		pt.x += borderWitdh;
		pt.y += captionHeight;

		if (rectBtnMin.PtInRect(pt))
			pDlg->SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, lParam);
		else if (rectBtnExit.PtInRect(pt))
			pDlg->SendMessage(WM_CLOSE);

		ePressButton = NULL_BTN;
		DrawFrame();

		bHandled = false;
		return 0;
	}
	LRESULT OnNcMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pDlg = static_cast<T*>(this);
		UINT nHitTest = (UINT)wParam;
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		pDlg->ScreenToClient(&pt);
		// Client point to Window point
		pt.x += borderWitdh;
		pt.y += captionHeight;

		if (rectBtnMin.PtInRect(pt))
			eHoverButton = MIN_BTN;
		else if (rectBtnExit.PtInRect(pt))
			eHoverButton = EXIT_BTN;
		else
		{
			eHoverButton = NULL_BTN;
			ePressButton = NULL_BTN;
		}

		DrawFrame();

		bHandled = false;
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pDlg = static_cast<T*>(this);
		UINT nHitTest = (UINT)wParam;
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		pDlg->ScreenToClient(&pt);
		// Client point to Window point
		pt.x += borderWitdh;
		pt.y += captionHeight;

		CRect iconRect(2, 2, captionHeight, captionHeight);
		
		if (iconRect.PtInRect(pt))
			return HTCAPTION;
		else if (rectBtnMin.PtInRect(pt) || rectBtnExit.PtInRect(pt))
			return HTSYSMENU;
		else 
			bHandled = false;

		return -1;
	}
};
