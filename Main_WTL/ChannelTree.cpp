#include "StdAfx.h"
#include "ChannelTree.h"
#include "ComDef.h"
#include <atlstr.h>
#include "resource.h"


CChannelTreeCtrl::CChannelTreeCtrl()
{
}

CChannelTreeCtrl::~CChannelTreeCtrl(void)
{
}

BOOL CChannelTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	return FALSE;
}

BOOL CChannelTreeCtrl::SubclassWindow( HWND hWnd )
{
	return CWindowImpl::SubclassWindow( hWnd );
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
		for (size_t j = 0; j < iter->second.size(); j++)
		{
			InsertNodeItem(iter->second[j].first, iter->second[j].second, node);
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