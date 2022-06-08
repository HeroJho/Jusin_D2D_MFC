
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)


	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	: m_pDevice(CDevice::Get_Instance())
	//, m_pSingle(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	g_hWnd = m_hWnd;

	if (FAILED(m_pDevice->Initialize()))
	{
		AfxMessageBox(L"m_pDevice ���� ����");
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

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	for (int i = 0; i < m_vImgIndex.size(); ++i)
	{
		const TEXINFO* pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", m_vImgIndex[i]);

		if (nullptr == pTexInfo)
			return;

		// ���� 10

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

		m_pDevice->Get_Sprite()->Draw(pTexInfo->pTexture,	// �׸����� �ϴ� �ؽ�ó
			nullptr, // ����� �̹��� ������ ���� rect ������, null�� ��� �̹����� 0, 0 �������� ���
			&D3DXVECTOR3(fX, fY, 0.f), // ����� �̹��� �߽� �࿡ ���� vec3 ����ü ������, null�� ��� 0, 0�� �߽� ��ǥ
			nullptr, // ��ġ ��ǥ�� ���� vec3 ����ü ������, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); //����� ���� �̹����� ���� ���� ��, ��� �� ���� ������ �ݿ�, 0xffffffff�� �Ѱ��ָ� ���� ���� ������ ���·� ���

	}

	m_pDevice->Render_End();
}

#pragma region ���ʿ�
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
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
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

		// �˻��� Ÿ���� ��ǥ�� ���´�
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

	D3DXVECTOR3 VerTex[4];    //������ ���
	float Gradiant[4];       //���� ���
	float Intercept[4];       //���� ���

							  //4���� ������ ǥ���ϱ� ���� �غ��� �������Դϴ�.
							  //������ 4���̹Ƿ�, �迭�� �����߽��ϴ�.
							  //VERTEX ��� ����ü�� ���� ���� ���� ����ü��, ���ο� x,y ��ǥ����
							  //�����ϴ�. �������� ��Ÿ���ϴ�.

	VerTex[0].x = fTX - (fTSizeX / 2);
	VerTex[0].y = fTY;
	//������
	VerTex[1].x = fTX;
	VerTex[1].y = fTY - (fTSizeY / 2);
	//����
	VerTex[2].x = fTX + (fTSizeX / 2);
	VerTex[2].y = fTY;
	//������
	VerTex[3].x = fTX;
	VerTex[3].y = fTY + (fTSizeY / 2);
	//�Ʒ���

	//�������� ��ǥ�� ���سִ� �����Դϴ�.
	//���� �ε��� Ÿ���� ��ǥ�� �����ϸ�, 
	//�� �������� ����� ������ ���س��� ��Ʈ�� �˴ϴ�.

	//���� Ÿ���� ���� �����̳ʿ� �����Ǿ� �ֽ��ϴ�.

	Gradiant[0] = ((VerTex[0].y - VerTex[1].y) /
		(VerTex[0].x - VerTex[1].x));
	//���� ����� ������ ����
	Gradiant[1] = ((VerTex[1].y - VerTex[2].y) /
		(VerTex[1].x - VerTex[2].x));
	//���� ����� ������ ����
	Gradiant[2] = ((VerTex[2].y - VerTex[3].y) /
		(VerTex[2].x - VerTex[3].x));
	//���� ����� ������ ����
	Gradiant[3] = ((VerTex[3].y - VerTex[0].y) /
		(VerTex[3].x - VerTex[0].x));
	//���� ����� ������ ����

	//��ǥ�� 2�� ���, �� �� ��ǥ�κ���, ���⸦ ���մϴ�.

	//�� ������ Ÿ���� ������� �ѹ��� �����ϰ�
	//���� �������� �����ϴ� ������ ����� �� �ֽ��ϴ�.

	//Ÿ�� ��������ε� ���� ������ �����ϸ�,
	//������� ��� ������ ���밪�� �����ϱ� �����Դϴ�. (��ȣ�� �ٲ�� �˴ϴ�.)

	//�ϴ� �� �ڵ�� �� Ǯ� �Ұ��ϴ� �ǵ����� �ۼ��Ǿ����Ƿ�,
	//4�� ������ ���⸦ ������ �� ������ �����ϰ� �ֽ��ϴ�.

	Intercept[0] = VerTex[0].y - Gradiant[0] * VerTex[0].x;
	Intercept[1] = VerTex[1].y - Gradiant[1] * VerTex[1].x;
	Intercept[2] = VerTex[2].y - Gradiant[2] * VerTex[2].x;
	Intercept[3] = VerTex[3].y - Gradiant[3] * VerTex[3].x;

	//���⸦ �˰�, �� ��ǥ�� �˰� �����Ƿ�
	//���⼭ ������ ����մϴ�.

	// ax + b = y ��
	// b = y - ax  �� �ٲ㼭 �������� Ǫ�� ���Դϴ�.

	if (Gradiant[0] * fX + Intercept[0] < fY
		&& Gradiant[1] * fX + Intercept[1] < fY
		&& Gradiant[2] * fX + Intercept[2] > fY
		&& Gradiant[3] * fX + Intercept[3] > fY)
	{
		//���� ���Ǿ����Ƿ�, �ε�ȣ�� �������� ���� �ֳ� �Ʒ��� �ֳ���
		//������ ��Ƽ� Ÿ�� ������ ǥ���մϴ�.
		//���⿡ ������ ��� true �� ��ȯ�� �浹�� ����� �˷��ݴϴ�.
		return true;
	}

	return false;

}
