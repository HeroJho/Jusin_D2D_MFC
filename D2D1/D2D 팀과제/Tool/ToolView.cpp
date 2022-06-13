
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "MiniView.h"

#include "ScrollMgr.h"
#include "ViewMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)


	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pDevice(CDevice::Get_Instance())
	//, m_pSingle(nullptr)
{
	
}

CToolView::~CToolView()
{
	//Safe_Delete(m_pSingle);
	
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes: ��ũ�� ���� ����� �����ϴ� CScrollView�� ��� �Լ�
	// MM_TEXT : �ȼ� ������ ũ�⸦ �����ϰڴٴ� �ɼ�
	// CSize : ��ũ�� ����, ���� ������

	//CSize : mfc���� �����ϴ� ������� ���õ� �����͸� �����ϴ� Ŭ����
	int iX = CScrollMgr::Get_Instance()->GetMaxScroll_X() / TILECX;
	int iY = CScrollMgr::Get_Instance()->GetMaxScroll_Y() / TILECY;
	SetScrollSizes(MM_TEXT, CSize(WINCX + TILECX * iX, WINCY + TILECY * iY));


	// AfxGetMainWnd : ���� ���� �����츦 ��ȯ�ϴ� ���� �Լ�
	// �θ�Ÿ���� ��ȯ�ϱ⿡ �ڽ� Ÿ������ �� ��ȯ�Ͽ� ���
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT		rcWnd{};

	// GetWindowRect : ���� �������� RECT ������ ���� ������ִ� �Լ�
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : ������ �μ��� RECT�� ������ ������ִ� �Լ�
	// ���� 0, 0 ��ǥ �������� �ٽ� RECT�� �����ϰ� �ִ�.
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	//GetClientRect : ���� viewâ�� RECT ������ ������ �Լ�
	GetClientRect(&rcMainView);

	// ���� â�� Viewâ�� ����, ���� ����� ���� ������ ����, ������ ���͹��� ����
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	//SetWindowPos : �μ���� ���Ӱ� ������ ��ġ�� ũ�⸦ �����ϴ� �Լ�
	// 1���� : ���� ������ ���ΰ�?
	// SWP_NOZORDER : ���� ������ �����ϰڴٴ� �÷���
	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);


	g_hWnd = m_hWnd;

	if (FAILED(m_pDevice->Initialize()))
	{
		AfxMessageBox(L"m_pDevice ���� ����");
		return;
	}


	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->Set_MainView(this);

	CViewMgr::Get_Instance()->Initialize();
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	m_pDevice->Render_Begin();

	m_pTerrain->Render();
	
	m_pDevice->Render_End();

}

#pragma region ���ʿ�
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}


BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����
#pragma endregion ���ʿ�

// CToolView �μ�


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);


	m_pTerrain->Create_Tile(D3DXVECTOR3((float)point.x + CScrollMgr::Get_Instance()->GetScroll_X(), (float)point.y + CScrollMgr::Get_Instance()->GetScroll_Y(), 0.f), 0);


	CViewMgr::Get_Instance()->All_Invalidate();

}
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);

	//if (GetAsyncKeyState(VK_LBUTTON))
	//{
	//	m_pTerrain->Tile_Change(D3DXVECTOR3(float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f), 0);
	//	Invalidate(FALSE);

	//	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	//	CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

	//	pMiniView->Invalidate(FALSE);

	//}


}


void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();


	Safe_Delete<CTerrain*>(m_pTerrain);

	CTextureMgr::Get_Instance()->Destroy_Instance();
	CViewMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();

	m_pDevice->Destroy_Instance();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}




void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if ('D' == nChar)
		CScrollMgr::Get_Instance()->IncreaseScroll_X();
	if ('A' == nChar)
		CScrollMgr::Get_Instance()->DecreaseScroll_X();
	if ('W' == nChar)
		CScrollMgr::Get_Instance()->IncreaseScroll_Y();
	if ('S' == nChar)
		CScrollMgr::Get_Instance()->DecreaseScroll_Y();


	Cal_Scroll();


	CViewMgr::Get_Instance()->All_Invalidate();

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CToolView::Cal_Scroll(void)
{

	int iX = CScrollMgr::Get_Instance()->GetMaxScroll_X() / TILECX;
	int iY = CScrollMgr::Get_Instance()->GetMaxScroll_Y() / TILECY;

	float totalX = WINCX + TILECX * iX;
	float totalY = WINCY + TILECY * iY;

	SetScrollSizes(MM_TEXT, CSize(totalX, totalY));


	CSize tempSize;
	GetScrollBarSizes(tempSize);

	if (tempSize.cx < totalX)
		SetScrollPos(SB_HORZ, totalX, true);
	if (tempSize.cy < totalY)
		SetScrollPos(SB_VERT, totalY, true);

}