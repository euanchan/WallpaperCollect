#include "StdAfx.h"
#include "ECusDialog.h"

CECusDialog::CECusDialog(void)
{
}

CECusDialog::~CECusDialog(void)
{
}


extern HINSTANCE g_hInst_;

XTSkinWindow::XTSkinWindow()
{
	bitmaptitle_.LoadBitmap( IDB_BITMAP_TITLE );
	bitmaptop_.LoadBitmap( IDB_BITMAP_TOP );
	bitmapleft_.LoadBitmap( IDB_BITMAP_LEFT );
	bitmapright_.LoadBitmap( IDB_BITMAP_RIGHT );
	bitmapbottom_.LoadBitmap( IDB_BITMAP_BOTTOM );
	bitmapclose_.LoadBitmap( IDB_BITMAP_CLOSE );
	::SetRectEmpty( &rcTitle_ );
	::SetRectEmpty( &rcIcon_ );
	::SetRectEmpty( &rcClose_ );
	type_ = BTN_NORMAL;
	oldHitTest_ = 0;
	moveHitTest_ = 0;
	downHitTest_ = 0;
}

XTSkinWindow::~XTSkinWindow()
{
}

void XTSkinWindow::OnFinalMessage( HWND hwnd /* = NULL */ )
{
	// delete this;
}


void XTSkinWindow::OnPaint( CDCHandle dc )
{
	CPaintDC dc_( m_hWnd );

	RECT clientrc_;
	GetClientRect( &clientrc_ );

	CBrush brh;
	brh.CreateSolidBrush( RGB( 255, 255, 255 ) );
	dc_.FillSolidRect( &clientrc_, RGB( 197, 227, 235 ) );
	dc_.FrameRect( &clientrc_, brh );
}

void XTSkinWindow::OnNCPaint( CRgn rgn )
{
	CWindowDC dc_( m_hWnd );

	DrawTitleBar( &dc_ );
}

BOOL XTSkinWindow::OnNCActive( BOOL bActive )
{
	OnNCPaint( 0 );
	return TRUE;
}

void XTSkinWindow::OnActivate( UINT nState, BOOL bMinimized, CWindow wndOther )
{
	OnNCPaint( 0 );
}

void XTSkinWindow::OnNCLButtonDown( UINT nHitTest, CPoint point )
{
	if ( nHitTest >= HTLEFT && nHitTest <= HTBOTTOMRIGHT ||  
		nHitTest == HTCAPTION )
	{
		DefWindowProc();
	}

	downHitTest_ = nHitTest;
	moveHitTest_ = 0;
	OnNCPaint( 0 );
}

UINT XTSkinWindow::OnNCHitTest( CPoint point )
{
	RECT rcWnd;
	GetWindowRect( &rcWnd );
	point.x -= rcWnd.left;
	point.y -= rcWnd.top;

	if( ::PtInRect( &rcClose_, point ) )
	{
		return HTCLOSE;
	}

	if( ::PtInRect( &rcTitle_, point ) )
	{
		return HTCAPTION;
	}

	return HTCLIENT;
}

void XTSkinWindow::OnNCLButtonUp( UINT nHitTest, CPoint point )
{
	downHitTest_ = 0;
	moveHitTest_ = nHitTest;
	OnNCPaint( 0 );

	if( nHitTest == HTCLOSE )
	{
		SendMessage( WM_CLOSE, 0, 0 );
		return;
	}
}

void XTSkinWindow::OnNCMouseMove( UINT nHitTest, CPoint point )
{
	if( nHitTest == HTCAPTION )
	{
		DefWindowProc();
	}

	moveHitTest_ = nHitTest;
	downHitTest_ = 0;

	if ( oldHitTest_ != nHitTest )
	{
		OnNCPaint( 0 );
		oldHitTest_ = nHitTest;
	}
}

void XTSkinWindow::OnNCLButtonDLCLK( UINT nHitTest, CPoint point )
{
	if( nHitTest == HTCAPTION )
	{
		downHitTest_ = 0;
		moveHitTest_ = 0;
		OnNCPaint( 0 );
	}
}

void XTSkinWindow::OnNCRButtonUp( UINT nHitTest, CPoint point )
{
	SetMsgHandled( FALSE );
}

void XTSkinWindow::OnNCRButtonDown( UINT nHitTest, CPoint point )
{
	SetMsgHandled( FALSE );
}

void XTSkinWindow::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CMenuHandle menuhandler_;
	menuhandler_.Attach( GetSystemMenu( FALSE ) );
	menuhandler_.RemoveMenu( SC_SIZE, MF_BYCOMMAND );
	menuhandler_.RemoveMenu( SC_RESTORE, MF_BYCOMMAND );
	menuhandler_.RemoveMenu( SC_MINIMIZE, MF_BYCOMMAND );
	menuhandler_.RemoveMenu( SC_MAXIMIZE, MF_BYCOMMAND );
	menuhandler_.Detach();
}

void XTSkinWindow::OnInitMenuPop( CMenu menuPopup, UINT nIndex, BOOL bSysMenu )
{
	OnNCPaint( 0 );
}

void XTSkinWindow::OnSysCommand( UINT nID, CPoint point )
{
	if ( nID == SC_MAXIMIZE )
	{
	}
	else if ( nID == SC_RESTORE )
	{
	}
	else if ( nID == SC_RESTORE )
	{
		OnNCPaint( 0 );
	}
	else
	{
		DefWindowProc();
	}
}

int XTSkinWindow::OnSetText( LPCTSTR lpstrTextr )
{
	DefWindowProc();
	OnNCPaint( 0 );

	return 0;
}

HICON XTSkinWindow::OnSetIcon( UINT uType, HICON hIcon )
{
	DefWindowProc();
	OnNCPaint( 0 );
	return NULL;
}

BOOL XTSkinWindow::DrawTitleBar( CDC* pDC )
{
	if( ::IsWindow( m_hWnd ) )
	{
		DWORD dwStyle = GetStyle();

		pDC->SetBkMode( TRANSPARENT );

		RECT wndrc_;
		RECT wndrctitle_;

		GetWindowRect( &wndrc_ );

		wndrctitle_.left = ::GetSystemMetrics( SM_CXFRAME ) - 2;
		wndrctitle_.top = ::GetSystemMetrics( SM_CYFRAME ) - 2;
		wndrctitle_.right = wndrc_.right - wndrc_.left - ::GetSystemMetrics( SM_CXFRAME ) + 2;
		wndrctitle_.bottom = wndrctitle_.top + ::GetSystemMetrics( SM_CYSMCAPTION ) + 1;

		pDC->ExcludeClipRect( 0, 0, wndrc_.right - wndrc_.left, wndrctitle_.bottom - wndrctitle_.top );
		pDC->SelectClipRgn( NULL );

		::CopyRect( &rcTitle_, &wndrctitle_ );

		CDC memdc_;
		memdc_.CreateCompatibleDC( pDC->m_hDC );

		POINT point;
		SIZE sizebmp_;

		int WndWidth = wndrc_.right - wndrc_.left;
		int WndHeight = wndrc_.bottom - wndrc_.top;

		point.x = WndWidth;
		point.y = GetSystemMetrics( SM_CYFRAME ) - 1;
		bitmaptop_.GetSize( sizebmp_ );
		HBITMAP oldbitmap = memdc_.SelectBitmap( bitmaptop_ );
		pDC->StretchBlt( 0, 0, point.x, point.y, memdc_, 0, 0, sizebmp_.cx, sizebmp_.cy, SRCCOPY );
		memdc_.SelectBitmap( oldbitmap );

		point.x = GetSystemMetrics( SM_CXFRAME ) - 1;
		point.y = WndHeight;
		bitmapleft_.GetSize( sizebmp_ );
		oldbitmap = memdc_.SelectBitmap( bitmapleft_ );
		pDC->StretchBlt( 0, 0, point.x, point.y, memdc_, 0, 0, sizebmp_.cx, sizebmp_.cy, SRCCOPY );
		memdc_.SelectBitmap( oldbitmap );

		point.x = GetSystemMetrics( SM_CXFRAME ) - 1;
		point.y = WndHeight;
		bitmapright_.GetSize( sizebmp_ );
		oldbitmap = memdc_.SelectBitmap( bitmapright_ );
		pDC->StretchBlt( WndWidth - point.x, 0, point.x, point.y, memdc_, 0, 0, sizebmp_.cx, sizebmp_.cy, SRCCOPY );
		memdc_.SelectBitmap( oldbitmap );

		point.x = WndWidth;
		point.y = GetSystemMetrics( SM_CXFRAME ) - 1;
		bitmapbottom_.GetSize( sizebmp_ );
		oldbitmap = memdc_.SelectBitmap( bitmapbottom_ );
		pDC->StretchBlt( 0, WndHeight - point.y, point.x, point.y, memdc_, 0, 0, sizebmp_.cx, sizebmp_.cy, SRCCOPY );
		memdc_.SelectBitmap( oldbitmap );

		bitmaptitle_.GetSize( sizebmp_ );
		oldbitmap = memdc_.SelectBitmap( bitmaptitle_ );
		pDC->StretchBlt( wndrctitle_.left, wndrctitle_.top, wndrctitle_.right - wndrctitle_.left, wndrctitle_.bottom - wndrctitle_.top, memdc_, 0, 0, sizebmp_.cx, sizebmp_.cy, SRCCOPY );
		memdc_.SelectBitmap( oldbitmap );

		if( dwStyle & WS_SYSMENU )
		{
			CIcon hicon_;
			hicon_.LoadIcon( IDI_TESTSKIN );

			rcIcon_.left = GetSystemMetrics( SM_CXFRAME );
			rcIcon_.top = GetSystemMetrics( SM_CYFRAME ) - 1;
			rcIcon_.right = ::GetSystemMetrics( SM_CYSMCAPTION );
			rcIcon_.bottom = ::GetSystemMetrics( SM_CYSMCAPTION );
			hicon_.DrawIconEx( pDC->m_hDC, rcIcon_.left, rcIcon_.top, 16, 16, 0, 0, DI_NORMAL );
		}

		if( dwStyle & WS_CAPTION )
		{
			CFont font_;
			font_.CreateFont( 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial") );
			HFONT hOldfont_ = pDC->SelectFont( font_ );
			pDC->SetTextColor( RGB( 255, 255, 255 ) );
			TCHAR buf_[256] = { 0 };
			GetWindowText( buf_, 256 );
			pDC->TextOut( rcIcon_.right + 5, rcIcon_.top, buf_ );
			pDC->SelectFont( hOldfont_ );
		}

		bitmapclose_.GetSize( sizebmp_ );
		rcClose_.left = wndrc_.right - wndrc_.left - ::GetSystemMetrics( SM_CXFRAME ) - sizebmp_.cx / 3;
		rcClose_.top = ::GetSystemMetrics( SM_CYFRAME ) - 2;
		rcClose_.right = wndrc_.right - wndrc_.left - ::GetSystemMetrics( SM_CXFRAME );
		rcClose_.bottom = rcClose_.top + ::GetSystemMetrics( SM_CYSMCAPTION );
		oldbitmap = memdc_.SelectBitmap( bitmapclose_ );
		if( moveHitTest_ == HTCLOSE )
		{
			pDC->BitBlt( rcClose_.left, rcClose_.top, sizebmp_.cx / 3, sizebmp_.cy, memdc_, sizebmp_.cx / 3 , 0, SRCCOPY );
		}
		else if( downHitTest_ == HTCLOSE )
		{
			pDC->BitBlt( rcClose_.left, rcClose_.top, sizebmp_.cx / 3, sizebmp_.cy, memdc_, ( sizebmp_.cx / 3 ) * 2 , 0, SRCCOPY );
		}
		else
		{
			pDC->BitBlt( rcClose_.left, rcClose_.top, sizebmp_.cx / 3, sizebmp_.cy, memdc_, 0, 0, SRCCOPY );
		}

		memdc_.SelectBitmap( oldbitmap );
	}

	return TRUE;
}

int XTSkinWindow::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	RECT rc = { 10, 10, 60, 32 };
	skinbutton_.Create( m_hWnd, rc, _T("…Ë÷√"), WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | BS_OWNERDRAW, 0, 10 );
	return 0;
}

void XTSkinWindow::OnDestory()
{
	skinbutton_.DestroyWindow();
}

LRESULT XTSkinWindow::OnPress( WORD wNotifyCode, WORD wID, HWND hWndCtl )
{
	MessageBox( TEXT("test"), TEXT("test"), 0 );
	return 0;
}