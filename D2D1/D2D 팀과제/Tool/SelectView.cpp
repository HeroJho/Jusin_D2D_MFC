// SelectView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SelectView.h"
#include "Device.h"

#include "ToolView.h"

#include "ViewMgr.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CScrollView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}


BEGIN_MESSAGE_MAP(CSelectView, CScrollView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSelectView �׸����Դϴ�.

void CSelectView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CSelectView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();


	CDevice::Get_Instance()->Render_Begin();


	CViewMgr::Get_Instance()->GetView_Tool()->Get_Terrain()->Select_Tile_Render();


	CDevice::Get_Instance()->Render_End(m_hWnd);

}


// CSelectView �����Դϴ�.

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


void CSelectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	int iIndex = CViewMgr::Get_Instance()->GetView_Tool()->Get_Terrain()->Get_ListTileIndex(D3DXVECTOR3((float)point.x, (float)point.y, 0.f));
	if(-1 != iIndex)
		CViewMgr::Get_Instance()->Set_PickedTile(iIndex);

	CScrollView::OnLButtonDown(nFlags, point);
}
