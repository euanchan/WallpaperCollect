#pragma once

class CChannelTreeCtrl : public CWindowImpl<CChannelTreeCtrl, CTreeViewCtrlEx>
{
public:
	//enum { IDD = IDC_CHANNEL_TREE };

	CChannelTreeCtrl();
	virtual ~CChannelTreeCtrl(void);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL SubclassWindow( HWND hWnd );

	bool InitWithChannelAtt(const TChannelAttri& channelAtt);
public: 
	BEGIN_MSG_MAP(CChannelTreeCtrl)    
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRBtnClicked)
// 		MSG_WM_CONTEXTMENU(OnContextMenu) 
// 		NOTIFY_CODE_HANDLER(TVN_ITEMEXPANDING,OnItemExpanding) 
// 		REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_ITEMEXPANDING,   OnItemExpanding2) 
 		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

	LRESULT OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

private:
	HTREEITEM InsertNodeItem(const string& node, const string& value, const HTREEITEM &parent);
	HTREEITEM InsertRootItem(const string& node);
};
