#pragma once

class CPicWallView :
	public CWindowImpl<CPicWallView, CListViewCtrl>
{
public:
	CPicWallView();
	virtual ~CPicWallView(void);

	BEGIN_MSG_MAP(CPicWallView)
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

private:
	CImageList *imgList;      // 
	vector<TCollectInfo*> thumbnailInfoList;
	wstring  collectName;     // 当前合集名
	int      indexFlag;       // 用于下载缩略图过程中更新图片，重建列表时，更新为imagelist::count, 每次更新itemindex时更新，
};
