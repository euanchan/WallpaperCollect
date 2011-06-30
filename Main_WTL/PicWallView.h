#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	// 默认位于程序所在目录的Cache\Thumbnail文件夹下
	CPicWallView(const wstring &cacheFilePath = _T(""));
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CChannelTreeCtrl)    
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRBtnClicked)
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

	LRESULT OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

public:
	bool InitWithCollectInfo(const TPackagePageInfo *packagePageInfo);

private:
	bool InitWithImgInfoList();
private:
	CImageList *imgList;      // 

	wstring cachePathRoot;   // 临时文件存放根目录

	vector<TCollectInfo*> thumbnailInfoList;
};
