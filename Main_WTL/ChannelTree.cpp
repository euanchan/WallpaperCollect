#include "StdAfx.h"
#include "ChannelTree.h"
#include "ComDef.h"
#include <atlstr.h>
#include "resource.h"


CChannelTreeCtrl::CChannelTreeCtrl()
: lastItem(NULL)
, lastChildItem(NULL)
, scrollBar(NULL)
, scrollAble(false)
{
}

CChannelTreeCtrl::~CChannelTreeCtrl(void)
{
}

LRESULT CChannelTreeCtrl::OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	POINT point; 
	GetCursorPos(&point); 
	ScreenToClient(&point);
	UINT iflags;
	HTREEITEM selItem = HitTest(point, &iflags);	
	if (selItem == NULL || GetItemData(selItem) == 0)
		return false;

	SelectItem(selItem);
	
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_CHANNEL))
	{
		CMenuHandle menuH = menu.GetSubMenu(0);
		ClientToScreen(&point);
		menuH.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, GetParent().m_hWnd);
	}
	return true;
}

bool CChannelTreeCtrl::InitWithChannelAtt(const TChannelInfo* channelAtt)
{
	TChannelTree::const_iterator iter = channelAtt->tree.begin();
	HTREEITEM root = InsertRootItem(channelAtt->siteName);
	for (; iter != channelAtt->tree.end(); iter++)
	{
		HTREEITEM node = InsertNodeItem(iter->first, "", root);
		lastItem = node;
		for (size_t j = 0; j < iter->second.size(); j++)
		{
			lastChildItem = InsertNodeItem(iter->second[j].first, iter->second[j].second, node);
		}
	}
	return true;
}

HTREEITEM CChannelTreeCtrl::InsertNodeItem( const string& node, const string& value, const HTREEITEM &parent )
{
	TV_INSERTSTRUCT tvis;
	ZeroMemory( &tvis, sizeof(TV_INSERTSTRUCT) );
	tvis.hParent		= parent;
	tvis.hInsertAfter	= TVI_LAST;
	tvis.item.mask		= TVIF_TEXT | TVIF_PARAM | TVIF_HANDLE | TVIF_HANDLE;	

	CStringW wstr = node.c_str();
	tvis.item.pszText	= (LPWSTR)wstr.GetString();
	tvis.item.cChildren = 0;
	tvis.item.lParam = value.length() > 2 ? (DWORD)value.c_str() : 0;

	HTREEITEM hItem = InsertItem( &tvis );
	return hItem;
}

HTREEITEM CChannelTreeCtrl::InsertRootItem(const string& node)
{
	TV_INSERTSTRUCT tvis;
	ZeroMemory( &tvis, sizeof(TV_INSERTSTRUCT) );
	tvis.hParent		= TVI_ROOT;
	tvis.hInsertAfter	= TVI_LAST;
	tvis.item.mask		= TVIF_TEXT;

	CStringW wstr = node.c_str();
	tvis.item.pszText	= (LPWSTR)wstr.GetString();
 	tvis.item.cChildren = 1;
	tvis.item.lParam = 0;
	HTREEITEM hItem = InsertItem( &tvis );
 	SetItemState(hItem, TVIS_EXPANDED, TVIS_EXPANDED);
	
	return hItem;
}

/*
LRESULT CChannelTreeCtrl::OnReflectedItemExpanded(LPNMHDR pnmh)
{
	if (!NeedShowScrollBar())
		return 0;

	// 更新滚动条
	//ScrollWindow()
	UpdateScrollBarPos(0);
	return 0;
}


void CChannelTreeCtrl::SetScrollBar(const HWND scrollBar)
{
	_ASSERT(::IsWindow(scrollBar));
	this->scrollBar = scrollBar;

	if (NeedShowScrollBar())
	{

	}
}

void CChannelTreeCtrl::UpdateScrollBarPos(const int pos)
{
	_ASSERT(scrollBar);
	::SetScrollPos(scrollBar, SB_CTL, pos, TRUE);
}

bool CChannelTreeCtrl::NeedShowScrollBar()
{
	_ASSERT(scrollBar);

	HTREEITEM item = (HTREEITEM)::SendMessage(m_hWnd, TVM_GETNEXTITEM, TVGN_LASTVISIBLE, 0L);
	RECT lastItemRect = {0};
	RECT wndRect = {0};
	GetItemRect(item, &lastItemRect, false);
	ClientToScreen(&lastItemRect);
	GetWindowRect(&wndRect);
	if (wndRect.bottom < lastItemRect.bottom - 2)
	{
		::ShowWindow(scrollBar, SW_SHOW);
		scrollAble = true;
		//::SetScrollRange(scrollBar, SB_CTL, )
		return true;
	}
	else
	{
		::ShowWindow(scrollBar, SW_HIDE);
		scrollAble = false;
		return false;
	}
}

BOOL CChannelTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!scrollAble)
		return true;

	RECT rect = {0};
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	ScrollWindow(0, zDelta, &rect, &rect);
	UpdateWindow();
	return true;
}*/
