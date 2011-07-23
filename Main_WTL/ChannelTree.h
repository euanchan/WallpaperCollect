#include "atlcrack.h"
#include <atlmisc.h>
#include "resource.h"
#pragma once

class CChannelTreeCtrl : 
	public CWindowImpl<CChannelTreeCtrl, CTreeViewCtrlEx>
{
public:
	enum { IDD = IDC_CHANNEL_TREE };

	CChannelTreeCtrl();
	virtual ~CChannelTreeCtrl(void);

	bool InitWithChannelAtt(const TChannelInfo* channelAtt);
// 	void SetScrollBar(const HWND scrollBar);
// 	void UpdateScrollBarPos(const int pos);
// 	bool NeedShowScrollBar();   // 返回false表示隐藏滚动条，true表示显示
public: 
	BEGIN_MSG_MAP(CChannelTreeCtrl)
// 		REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_ITEMEXPANDED, OnReflectedItemExpanded)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRBtnClicked)
// 		MSG_WM_MOUSEWHEEL(OnMouseWheel)
 		DEFAULT_REFLECTION_HANDLER() 
	END_MSG_MAP() 

	LRESULT OnRBtnClicked(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	LRESULT OnReflectedItemExpanded(LPNMHDR pnmh);
private:
	HTREEITEM InsertNodeItem(const string& node, const string& value, const HTREEITEM &parent);
	HTREEITEM InsertRootItem(const string& node);

	HTREEITEM lastItem;       // 保存最后一个次级子节点
	HTREEITEM lastChildItem;  // 保存最后一个子节点
private:
	HWND scrollBar;
	bool scrollAble;
};
