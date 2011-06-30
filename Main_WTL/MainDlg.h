// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ChannelTree.h"
#include "PicWallView.h"
#include "WallpaperCollect.h"
#include "Net.h"

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)	
// 		COMMAND_ID_HANDLER(IDOK, OnOK)
// 		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_BTN_CHANGE_DIR, BN_CLICKED, OnBnClickedBtnChangeDir)
		COMMAND_HANDLER(IDC_BTN_PAUSE, BN_CLICKED, OnBnClickedBtnPause)
		COMMAND_ID_HANDLER(ID_Download_CHANNEL, OnDownload)
		NOTIFY_HANDLER(IDC_CHANNEL_TREE, TVN_SELCHANGED, OnTvnSelchangedChannelTree)
		//NOTIFY_HANDLER(IDC_CHANNEL_TREE, NM_CLICK, OnNMClickChannelTree)
		REFLECT_NOTIFICATIONS() 
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
// 	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
// 	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnChangeDir(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnPause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDownload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnTvnSelchangedChannelTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

private: 
	CMenu menu;
	CChannelTreeCtrl channelTree; 
	CPicWallView     picWallView;

	CWallpaperCollect wpCol;
	CNet              net;
	TChannelInfo *channelAtt;
	vector<TPackagePageInfo*> collectInfoVec;

public:
	void Init();
	void Release();
};
