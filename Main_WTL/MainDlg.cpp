// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// 初始化频道树
	wchar_t szPath[MAX_PATH] = {0};
	wstring cachePath;
	::GetModuleFileName(NULL, szPath, sizeof(szPath));
	wcscpy(wcsrchr(szPath, '\\'), _T("\\Cache\\"));
	cachePath = szPath;


	wpCol.SetSite("http://www.deskcity.com/");
	wpCol.SetSaveDir(cachePath);
	wpCol.ColChannelTree(channelAtt);
	//wpCol.ColFromPackagePages("http://www.deskcity.com/details/index/152.html", cachePath);
	//wpCol.SetSaveDir(cachePath);



	//////////////////////////////////////////////////////////////////////////
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);

	// channelTree
	channelTree.SubclassWindow(GetDlgItem(IDC_CHANNEL_TREE));
	channelTree.InitWithChannelAtt(channelAtt);

	//
	//picWallView.Create(m_hWnd);
	picWallView.SubclassWindow(GetDlgItem(IDC_LIST_PIC));

	// Menu
	menu.Attach(LoadMenu( _Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_MENU_CHANNEL)));
	SetMenu(menu);

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

// LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
// {
// 	// TODO: Add validation code 
// 	EndDialog(wID);
// 	return 0;
// }
// 
// LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
// {
// 	EndDialog(wID);
// 	return 0;
// }

LRESULT CMainDlg::OnBnClickedBtnChangeDir(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}

LRESULT CMainDlg::OnBnClickedBtnPause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加控件通知处理程序代码

	return 0;
}

LRESULT CMainDlg::OnDownload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: 在此添加命令处理程序代码
	CTreeItem item = channelTree.GetSelectedItem();
	DWORD_PTR ptr = (DWORD_PTR)item.GetData();
	if (ptr)
	{
		string url = (char*)(item.GetData());
		wpCol.ColFromPackagePages(url, _T("F:\\"));
	}

	return 0;
}

LRESULT CMainDlg::OnPassValue(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	switch (wParam)
	{
	case MSG_W_COLLECT_URL:
		string url = (char*)lParam;
		picWallView.InitWithPageUrl(url.c_str());
		break;
	}

	return 0;
}