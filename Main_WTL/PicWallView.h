#pragma once

class CPicWallView
	: public CWindowImpl<CPicWallView, CListViewCtrl>
// 	, public CCustomDraw<CPicWallView>
{
public:
	CPicWallView();
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CPicWallView)
// 		CHAIN_MSG_MAP_ALT( CCustomDraw<CPicWallView>, 1 )
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

public:
	bool InitWithCollectInfo(const TPackagePageInfo *packagePageInfo);

	bool UpdateItem(const string& thumbnailUrl);
	TCollectInfo* GetDataByIndex(int index)
	{
		if (index >= thumbnailInfoList.size() - 1)
			return NULL;
		return thumbnailInfoList[index];
	}
private:
	bool InitWithImgInfoList();

/*
public:
	// Overrideables
	DWORD OnPrePaint(int / *idCtrl* /, LPNMCUSTOMDRAW lpNMCustomDraw)
	{
// 		HBRUSH brush = CreateSolidBrush(RGB(200, 222, 10));
// 		::FillRect(lpNMCustomDraw->hdc, &lpNMCustomDraw->rc, brush);
// 		DeleteObject((HGDIOBJ)brush);
// 
// 		NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( lpNMCustomDraw );
// 		pLVCD->clrTextBk = RGB(200, 22, 11);
// 		if (lpNMCustomDraw->uItemState & CDIS_DEFAULT)
// 		{
// 			int i = 0;
// 		}
// 		else if (lpNMCustomDraw->uItemState & CDIS_CHECKED)
// 		{
// 			int i = 0;
// 		}
		return CDRF_DODEFAULT;
	}

	DWORD OnPostPaint(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

	DWORD OnPreErase(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

	DWORD OnPostErase(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

	DWORD OnItemPrePaint(int / *idCtrl* /, LPNMCUSTOMDRAW lpNMCustomDraw)
	{
		NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( lpNMCustomDraw );
		// This is the prepaint stage for an item. Here's where we set the
		// item's text color. Our return value will tell Windows to draw the
		// item itself, but it will use the new color we set here for the background
		COLORREF crText;
		if ( (pLVCD->nmcd.dwItemSpec % 2) == 0 )
			crText = RGB(200,200,255);
		else 
			crText = RGB(255,255,255);        
		// Store the color back in the NMLVCUSTOMDRAW struct.
		pLVCD->clrTextBk = crText;
		// Tell Windows to paint the control itself.

		return CDRF_DODEFAULT;
	}

	DWORD OnItemPostPaint(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

	DWORD OnItemPreErase(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

	DWORD OnItemPostErase(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}

#if (_WIN32_IE >= 0x0400)
	DWORD OnSubItemPrePaint(int / *idCtrl* /, LPNMCUSTOMDRAW / *lpNMCustomDraw* /)
	{
		return CDRF_DODEFAULT;
	}
#endif // (_WIN32_IE >= 0x0400)
*/

private:
	CImageList *imgList;      // 
	vector<TCollectInfo*> thumbnailInfoList;
	wstring  collectName;     // 当前合集名
	int      indexFlag;       // 用于下载缩略图过程中更新图片，重建列表时，更新为imagelist::count, 每次更新itemindex时更新，
};
