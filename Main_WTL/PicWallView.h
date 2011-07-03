#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	CPicWallView();
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CChannelTreeCtrl)
		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

public:
	bool InitWithCollectInfo(const TPackagePageInfo *packagePageInfo);

	bool UpdateItem(const string& thumbnailUrl);
private:
	bool InitWithImgInfoList();

private:
	CImageList *imgList;      // 
	vector<TCollectInfo*> thumbnailInfoList;
	wstring  collectName;     // 当前合集名
};
