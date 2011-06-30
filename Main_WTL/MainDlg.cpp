// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "PathInfo.h"

void CMainDlg::Init()
{
	channelAtt = new TChannelInfo();

	//wstring cachePath = gPathInfo->CachePath();
	wpCol.SetSite("http://www.deskcity.com/");
	wpCol.ColChannelTree(channelAtt);
}

void CMainDlg::Release()
{
	delete channelAtt;
	
	size_t size = collectInfoVec.size();
	while (size-- > 0)
	{
		delete collectInfoVec[0];
		collectInfoVec.erase(collectInfoVec.begin());
	}
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// 初始化频道树
	Init();

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

	//////////////////////////////////////////////////////////////////////////
	// channelTree
	channelTree.SubclassWindow(GetDlgItem(IDC_CHANNEL_TREE));
	channelTree.InitWithChannelAtt(channelAtt);

	// 
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
		wchar lpStr[MAX_PATH];
		memset(lpStr, 0, MAX_PATH);
		item.GetText((LPTSTR)lpStr, MAX_PATH);
		wstring rootPath = gPathInfo->GetSavePathRoot();
		USES_CONVERSION;
		wstring tmp(lpStr);
		rootPath.append(tmp);
		rootPath.append(_T("\\"));
		wpCol.ColFromPackagePages(url, rootPath);
	}

	return 0;
}

LRESULT CMainDlg::OnTvnSelchangedChannelTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& bHandled)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

 	if (pNMTreeView->itemNew.lParam == 0)
 		return 0;

	HTREEITEM selItem = pNMTreeView->itemNew.hItem;
	string url = (char*)pNMTreeView->itemNew.lParam;

	// 查询是否本地已有缓存
	for (int i = 0; i < collectInfoVec.size(); i++)
	{
		if (url == collectInfoVec[i]->url)
		{
			picWallView.InitWithCollectInfo(collectInfoVec[i]);
			return 0;
		}
	}

	// 
	TPackagePageInfo *collectInfo = new TPackagePageInfo();
	collectInfo->url = url;
	if (wpCol.GetPackagePagesInfo(url, collectInfo))
	{
		collectInfoVec.push_back(collectInfo);
		picWallView.InitWithCollectInfo(collectInfo);
		net.Start();
	}
	else
	{
		delete collectInfo;
		return 0;
	}

	// Add thumbnail to download task
	vector<TCollectInfo>::iterator iter = collectInfo->collectInfoVec.begin();
	for (; iter != collectInfo->collectInfoVec.end(); ++iter)
	{
		net.AddTask(iter->thumbUrl, iter->thumbSavePath);
	}

	return 0;
}
