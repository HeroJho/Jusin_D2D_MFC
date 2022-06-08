
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)


	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	: m_pDevice(CDevice::Get_Instance())
	//, m_pSingle(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
	//Safe_Delete(m_pSingle);
	CTextureMgr::Get_Instance()->Destroy_Instance();
	m_pDevice->Destroy_Instance();
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;

	if (FAILED(m_pDevice->Initialize()))
	{
		AfxMessageBox(L"m_pDevice 생성 실패");
		return;
	}

	//m_pSingle = new CSingleTexture;
	//m_pSingle->InsertTexture(L"../Texture/Cube.png");


	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/Cube.png", TEX_SINGLE, L"Cube")))
	{
		AfxMessageBox(L"Cube Image Insert failed");
		return;
	}

	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
	{
		AfxMessageBox(L"Tile Image Insert failed");
		return;
	}


	for (int i = 0; i < 500; ++i)
	{
		m_vImgIndex.push_back(2);
	}

}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	for (int i = 0; i < m_vImgIndex.size(); ++i)
	{
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_vImgIndex[i]);

		if (nullptr == pTexInfo)
			return;

		// 가로 10

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;

		int			iPosX = i % 10;
		int			iPosY = i / 10;

		float		fTempX = 0.f;
		if (iPosY % 2 == 0)
			fTempX = fX;

		D3DXMATRIX		matWorld, matScale, matRotZ, matTrans;

		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
		D3DXMatrixTranslation(&matTrans, pTexInfo->tImgInfo.Width * iPosX + fTempX, fY * iPosY, 0.f);

		matWorld = matScale * matTrans;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		/*float		fX = m_pSingle->Get_Texture()->tImgInfo.Width / 2.f;
		float		fY = m_pSingle->Get_Texture()->tImgInfo.Height / 2.f;*/

		//const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Cube");

		m_pDevice->Render_Begin();

		m_pDevice->Get_Sprite()->Draw(pTexInfo->pTexture,	// 그리고자 하는 텍스처
			nullptr, // 출력할 이미지 영역에 대한 rect 포인터, null인 경우 이미지의 0, 0 기준으로 출력
			&D3DXVECTOR3(fX, fY, 0.f), // 출력할 이미지 중심 축에 대한 vec3 구조체 포인터, null인 경우 0, 0이 중심 좌표
			nullptr, // 위치 좌표에 대한 vec3 구조체 포인터, null인 경우 스크린 상 0,0 좌표에 출력
			D3DCOLOR_ARGB(255, 255, 255, 255)); //출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색상이 반영, 0xffffffff를 넘겨주면 원본 색상 유지된 상태로 출력

	}

	m_pDevice->Render_End();
}

#pragma region 불필요
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
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
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	for (int i = 0; i < m_vImgIndex.size(); ++i)
	{
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_vImgIndex[i]);
		if (nullptr == pTexInfo)
			return;

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;
		int			iPosX = i % 10;
		int			iPosY = i / 10;
		float		fTempX = 0.f;
		if (iPosY % 2 == 0)
			fTempX = fX;

		// 검사할 타일의 좌표를 얻어온다
		float DestX = pTexInfo->tImgInfo.Width * iPosX + fTempX;
		float DestY = fY * iPosY;

		float fChangeMPosX = point.x * 0.6f;
		float fChangeMPosY = point.y * 0.8f;

		if (Coll_Tile(fChangeMPosX, fChangeMPosY, DestX, DestY, pTexInfo->tImgInfo.Width, pTexInfo->tImgInfo.Height))
		{
			m_vImgIndex[i]++;
			break;
		}

	}



	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


bool CToolView::Coll_Tile(const float& fX, const float& fY, const float& fTX, const float& fTY , const float& fTSizeX, const float& fTSizeY)
{

	D3DXVECTOR3 VerTex[4];    //꼭지점 기록
	float Gradiant[4];       //기울기 기록
	float Intercept[4];       //절편 기록

							  //4개의 직선을 표현하기 위해 준비한 변수들입니다.
							  //직선이 4개이므로, 배열로 구성했습니다.
							  //VERTEX 라는 구조체는 제가 따로 만든 구조체로, 내부에 x,y 좌표값을
							  //가집니다. 꼭지점을 나타냅니다.

	VerTex[0].x = fTX - (fTSizeX / 2);
	VerTex[0].y = fTY;
	//왼쪽점
	VerTex[1].x = fTX;
	VerTex[1].y = fTY - (fTSizeY / 2);
	//위쪽
	VerTex[2].x = fTX + (fTSizeX / 2);
	VerTex[2].y = fTY;
	//오른쪽
	VerTex[3].x = fTX;
	VerTex[3].y = fTY + (fTSizeY / 2);
	//아래쪽

	//꼭지점의 좌표를 구해넣는 과정입니다.
	//받은 인덱스 타일의 좌표를 참조하며, 
	//이 꼭지점이 기울기와 절편을 구해내는 힌트가 됩니다.

	//현재 타일은 벡터 컨테이너에 보관되어 있습니다.

	Gradiant[0] = ((VerTex[0].y - VerTex[1].y) /
		(VerTex[0].x - VerTex[1].x));
	//음을 기울기로 가지는 직선
	Gradiant[1] = ((VerTex[1].y - VerTex[2].y) /
		(VerTex[1].x - VerTex[2].x));
	//양을 기울기로 가지는 직선
	Gradiant[2] = ((VerTex[2].y - VerTex[3].y) /
		(VerTex[2].x - VerTex[3].x));
	//음을 기울기로 가지는 직선
	Gradiant[3] = ((VerTex[3].y - VerTex[0].y) /
		(VerTex[3].x - VerTex[0].x));
	//양을 기울기로 가지는 직선

	//좌표를 2개 잡고, 이 두 좌표로부터, 기울기를 구합니다.

	//이 과정은 타일의 사이즈로 한번만 연산하고
	//음수 연산으로 변경하는 식으로 요약할 수 있습니다.

	//타일 사이즈만으로도 기울기 연산이 가능하며,
	//마름모는 모든 기울기의 절대값이 동일하기 때문입니다. (부호만 바뀌면 됩니다.)

	//일단 이 코드는 다 풀어서 소개하는 의도에서 작성되었으므로,
	//4개 직선의 기울기를 일일이 두 점으로 연산하고 있습니다.

	Intercept[0] = VerTex[0].y - Gradiant[0] * VerTex[0].x;
	Intercept[1] = VerTex[1].y - Gradiant[1] * VerTex[1].x;
	Intercept[2] = VerTex[2].y - Gradiant[2] * VerTex[2].x;
	Intercept[3] = VerTex[3].y - Gradiant[3] * VerTex[3].x;

	//기울기를 알고, 한 좌표를 알고 있으므로
	//여기서 절편을 계산합니다.

	// ax + b = y 를
	// b = y - ax  로 바꿔서 방정식을 푸는 꼴입니다.

	if (Gradiant[0] * fX + Intercept[0] < fY
		&& Gradiant[1] * fX + Intercept[1] < fY
		&& Gradiant[2] * fX + Intercept[2] > fY
		&& Gradiant[3] * fX + Intercept[3] > fY)
	{
		//식이 계산되었으므로, 부등호로 직선보다 위에 있냐 아래에 있냐의
		//범위를 모아서 타일 범위를 표현합니다.
		//검출에 성공할 경우 true 를 반환해 충돌된 사실을 알려줍니다.
		return true;
	}

	return false;

}
