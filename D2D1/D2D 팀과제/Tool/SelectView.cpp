// SelectView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SelectView.h"
#include "Device.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CScrollView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}


BEGIN_MESSAGE_MAP(CSelectView, CScrollView)
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


// CSelectView �޽��� ó�����Դϴ�.
