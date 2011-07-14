#pragma once

class CECusDialog 
	: public CDialogImpl<CECusDialog>
{
public:
	DECLARE_WND_CLASS(_T("CECusDialog"))

	BEGIN_MSG_MAP(CECusDialog)
		
	END_MSG_MAP()
public:
	CECusDialog(void);
	~CECusDialog(void);
};


#include <atlbase.h>
#include <atlwin.h>
#include <atlapp.h>
#include <atluser.h>
#include <atlcrack.h>
#include <atlmisc.h>

#include "XTSkinButton.h"

class XTSkinWindow : public CWindowImpl<XTSkinWindow>
{
	typedef enum{ BTN_NORMAL, BTN_MOVE, BTN_PRESS } BTN_TYPE;
public:
	DECLARE_WND_CLASS( _T("SkinWindow_BLACKMAN") )

public:
	XTSkinWindow();
	virtual~XTSkinWindow();
	//////////////////////////////////////////////////////////////////////////
	BEGIN_MSG_MAP_EX(XTSkinWindow)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestory)
		MSG_WM_ACTIVATE(OnActivate)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_NCPAINT(OnNCPaint)
		MSG_WM_NCACTIVATE(OnNCActive)
		MSG_WM_NCRBUTTONUP(OnNCRButtonUp)
		MSG_WM_NCRBUTTONDOWN(OnNCRButtonDown)
		MSG_WM_NCLBUTTONDOWN(OnNCLButtonDown)
		MSG_WM_NCLBUTTONUP(OnNCLButtonUp)
		MSG_WM_NCLBUTTONDBLCLK(OnNCLButtonDLCLK)
		MSG_WM_NCMOUSEMOVE(OnNCMouseMove)
		MSG_WM_NCHITTEST(OnNCHitTest)
		MSG_WM_INITMENUPOPUP(OnInitMenuPop)
		MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_SETICON(OnSetIcon)
		MSG_WM_SETTEXT(OnSetText)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		COMMAND_ID_HANDLER_EX(10, OnPress)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	//////////////////////////////////////////////////////////////////////////

public:
	virtual void OnFinalMessage( HWND hwnd = NULL );
	void OnShowWindow( BOOL bShow, UINT nStatus );
	void OnInitMenuPop( CMenu menuPopup, UINT nIndex, BOOL bSysMenu );
	void OnPaint( CDCHandle dc );
	void OnNCPaint( CRgn rgn );
	BOOL OnNCActive( BOOL bActive );
	void OnNCRButtonUp( UINT nHitTest, CPoint point );
	void OnNCRButtonDown( UINT nHitTest, CPoint point );
	void OnNCLButtonDown( UINT nHitTest, CPoint point );
	void OnNCLButtonUp( UINT nHitTest, CPoint point );
	void OnNCLButtonDLCLK( UINT nHitTest, CPoint point );
	void OnNCMouseMove( UINT nHitTest, CPoint point );
	void OnSysCommand( UINT nID, CPoint point );
	int OnSetText( LPCTSTR lpstrText );
	HICON OnSetIcon( UINT uType, HICON hIcon );
	UINT OnNCHitTest( CPoint point );
	int OnCreate( LPCREATESTRUCT lpCreateStruct );
	void OnDestory();
	void OnActivate( UINT nState, BOOL bMinimized, CWindow wndOther );

	LRESULT OnPress( WORD wNotifyCode, WORD wID, HWND hWndCtl );

private:
	BOOL DrawTitleBar( CDC* pDC );

private:
	CBitmap bitmaptitle_;
	CBitmap bitmaptop_;
	CBitmap bitmapleft_;
	CBitmap bitmapright_;
	CBitmap bitmapbottom_;
	CBitmap bitmapclose_;

	RECT rcTitle_;
	RECT rcIcon_;
	RECT rcClose_;

	BTN_TYPE type_;
	UINT oldHitTest_;
	UINT moveHitTest_;
	UINT downHitTest_;

	XTSkinButton skinbutton_;
};