
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)


	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

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

	// SetScrollSizes: 스크롤 바의 사이즈를 지정하는 CScrollView의 멤버 함수
	// MM_TEXT : 픽셀 단위로 크기를 조정하겠다는 옵션
	// CSize : 스크롤 가로, 세로 사이즈

	//CSize : mfc에서 제공하는 사이즈와 관련된 데이터를 관리하는 클래스
	int iX = CScrollMgr::Get_Instance()->GetMaxScroll_X() / TILECX;
	int iY = CScrollMgr::Get_Instance()->GetMaxScroll_Y() / TILECY;
	SetScrollSizes(MM_TEXT, CSize(WINCX + TILECX * iX, WINCY + TILECY * iY));


	// AfxGetMainWnd : 현재 메인 윈도우를 반환하는 전역 함수
	// 부모타입을 반환하기에 자식 타입으로 형 변환하여 사용
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT		rcWnd{};

	// GetWindowRect : 현재 윈도우의 RECT 정보를 얻어와 기록해주는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 지정한 인수로 RECT의 정보를 기록해주는 함수
	// 현재 0, 0 좌표 기준으로 다시 RECT를 조정하고 있다.
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	//GetClientRect : 현재 view창의 RECT 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	// 메인 창과 View창의 가로, 세로 사이즈를 통해 프레임 가로, 세로의 인터벌을 구함
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	//SetWindowPos : 인수대로 새롭게 윈도우 위치와 크기를 조정하는 함수
	// 1인자 : 순수 변경할 것인가?
	// SWP_NOZORDER : 현재 순서를 유지하겠다는 플래그
	pMainFrm->SetWindowPos(nullptr, 0, 0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);


	g_hWnd = m_hWnd;

	if (FAILED(m_pDevice->Initialize()))
	{
		AfxMessageBox(L"m_pDevice 생성 실패");
		return;
	}


	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->Set_MainView(this);

	CViewMgr::Get_Instance()->Initialize();
}

// CToolView 그리기

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

#pragma region 불필요
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}


BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}


CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기
#pragma endregion 불필요

// CToolView 인쇄


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);


	m_pTerrain->Create_Tile(D3DXVECTOR3((float)point.x + CScrollMgr::Get_Instance()->GetScroll_X(), (float)point.y + CScrollMgr::Get_Instance()->GetScroll_Y(), 0.f), 0);


	CViewMgr::Get_Instance()->All_Invalidate();

}
void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}




void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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