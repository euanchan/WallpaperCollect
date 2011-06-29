#include "StdAfx.h"
#include "PicWallView.h"
#include "PathInfo.h"

HBITMAP LoadImageFile(const wstring& fileName)
{
	// Use IPicture stuff to use JPG / GIF files
	IPicture* p;
	IStream* s;
	IPersistStream* ps;
	HGLOBAL hG;
	void* pp;
	FILE* fp;


	// Read file in memory
	fp = _wfopen(fileName.c_str(), _T("rb"));
	if (!fp)
		return NULL;

	fseek(fp,0,SEEK_END);
	int fs = ftell(fp);
	fseek(fp,0,SEEK_SET);
	hG = GlobalAlloc(GPTR,fs);
	if (!hG)
	{
		fclose(fp);
		return NULL;
	}
	pp = (void*)hG;
	fread(pp,1,fs,fp);
	fclose(fp);

	// Create an IStream so IPicture can 
	CreateStreamOnHGlobal(hG,false,&s);
	if (!s)
	{
		GlobalFree(hG);
		return NULL;
	}

	OleLoadPicture(s,0,false,IID_IPicture,(void**)&p);

	if (!p)
	{
		s->Release();
		GlobalFree(hG);
		return NULL;
	}
	s->Release();
	GlobalFree(hG);

	HBITMAP hB = 0;
	p->get_Handle((unsigned int*)&hB);

	// Copy the image. Necessary, because upon p's release,
	// the handle is destroyed.
	HBITMAP hBB = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,
		LR_COPYRETURNORG);

	p->Release();
	return hBB;
}

//////////////////////////////////////////////////////////////////////////
CPicWallView::CPicWallView(const wstring &cacheFilePath/* = _T("")*/)
: imgList(NULL)
{
	if (cacheFilePath.length() < 2)
	{
		cachePathRoot = gPathInfo->ModulePath();
		cachePathRoot.append(_T("\\Cache\\Thumbnail"));
	}
	else
		cachePathRoot = cacheFilePath;
	//SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE) | LVS_ICON);
}

CPicWallView::~CPicWallView(void)
{
	if (imgList)
		imgList->Destroy();
}

LRESULT CPicWallView::OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return 0;
}

bool CPicWallView::InitWithPageUrl(const string &pageUrl)
{
	thumbnailInfoList.erase(thumbnailInfoList.begin(), thumbnailInfoList.end());
	for (int i = 0; i < 40; i++)
	{
		TCollectInfo info;
		info.index = i;
		info.displayName = _T("ËõÂÔÍ¼1111");
		wstring path = gPathInfo->ModulePath();
		path.append(_T("\\Cache\\Thumbnail\\001\\4074.jpg"));
		info.thumbSavePath = path;
		info.linkUrl = "deskcity.com/index/100";
		thumbnailInfoList.push_back(info);
	}

	InitWithImgInfoList();
	return true;
}

bool CPicWallView::InitWithImgInfoList()
{
	vector<TCollectInfo>::iterator iter = thumbnailInfoList.begin();
	if (imgList)
	{
		imgList->Destroy();
	}
	imgList = new CImageList();
	imgList->Create(160, 100, TRUE | ILC_COLOR32, thumbnailInfoList.size(), 5);
	this->SetImageList(imgList->m_hImageList, LVSIL_NORMAL);
	for (; iter != thumbnailInfoList.end(); ++iter)
	{
		HBITMAP bm = LoadImageFile(iter->thumbSavePath);
		int i = imgList->Add(bm, (HBITMAP)NULL);
		if (i == -1)
		{
			printf("Load image file \"%s\" failed!", iter->thumbSavePath);
		}
		InsertItem(iter->index, (LPCTSTR)iter->displayName.c_str(), iter->index);
	}
	return true;
}