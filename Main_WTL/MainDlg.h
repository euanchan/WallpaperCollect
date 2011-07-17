// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CustomNCClient.h"
#include "ChannelTree.h"
#include "PicWallView.h"
#include "EButton.h"
#include "EProgressBar.h"
#include "WallpaperCollect.h"
#include "Net.h"


class CMainDlg 
	: public CDialogImpl<CMainDlg>
	, public CWinDataExchange<CMainDlg>
	, public CCustomNCClient<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP(CMainDlg)
		CHAIN_MSG_MAP(CCustomNCClient<CMainDlg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)	
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
		MESSAGE_HANDLER(MSG_UPDATE_TASK_LIST_PROCESS, OnUpdateTotalProgress)
		MESSAGE_HANDLER(MSG_UPDATE_CUR_PIC_PROCESS, OnUpdateCurProgress)
		MESSAGE_HANDLER(MSG_UPDATE_CUR_PIC_NAME, OnUpdateCurPicName)
		MESSAGE_HANDLER(MSG_THUMBNAIL_PIC_FINISHED, ONNotifyThumbPicFinished)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_HANDLER(IDC_BTN_CHANGE_DIR, BN_CLICKED, OnBnClickedBtnChangeDir)
		COMMAND_HANDLER(IDC_BTN_PAUSE, BN_CLICKED, OnBnClickedBtnPause)
		COMMAND_ID_HANDLER(ID_Download_CHANNEL, OnDownloadCollect)
		NOTIFY_HANDLER(IDC_CHANNEL_TREE, TVN_SELCHANGED, OnTvnSelchangedChannelTree)
		NOTIFY_HANDLER(IDC_LIST_PIC, NM_CLICK, OnNMClickListPic)
		NOTIFY_HANDLER(IDC_LIST_PIC, NM_RCLICK, OnNMRclickListPic)
		COMMAND_ID_HANDLER(ID_DOWNLOAD_PICS, OnDownloadPackage)
		COMMAND_ID_HANDLER(ID_DOWNLOAD_SEL, OnDownloadSelectPackage)
		COMMAND_ID_HANDLER(ID_SELECT_ALL, OnSelectAll)
		COMMAND_ID_HANDLER(ID_SELECT_INVERT, OnSelectInvert)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DDX_MAP(CMainDlg)
		DDX_TEXT(IDC_EDIT_SAVEDIR, (LPTSTR)(LPCTSTR)savePathRoot)
	END_DDX_MAP() 
// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnCtlColorStatic(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnUpdateTotalProgress(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnUpdateCurProgress(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnUpdateCurPicName(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT ONNotifyThumbPicFinished(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	
	LRESULT OnTvnSelchangedChannelTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

	LRESULT OnBnClickedBtnChangeDir(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedBtnPause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	// 壁纸列表鼠标消息处理
	LRESULT OnNMClickListPic(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnNMRclickListPic(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

	LRESULT OnSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSelectInvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnDownloadCollect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDownloadPackage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDownloadSelectPackage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void RefreshControl(UINT uCtlID);

public:
	void Init();
	void Release();
protected:
	// 根据当前频道树展开情况 获取保存路径
	wstring GetSavePathByChannelTreeState();
private: 
	CMenu menuChannelTree;
	CChannelTreeCtrl channelTree; 
	CPicWallView     picWallView;
	CEProgressBar    progressTotal;
	CEProgressBar    progressCur;
	CEdit            savePathEdit;
	CEButton         btnChangeDir;
	CEButton         btnPause;

	ATL::CString          savePathRoot;           // 壁纸保存目录根路径

	vector<TPackagePageInfo*> collectInfoVec;

	CWallpaperCollect wpCol;
	TChannelInfo  *channelAtt;
	CNet  netThumbnail;
};
