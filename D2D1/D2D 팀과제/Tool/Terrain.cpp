#include "stdafx.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"
#include "ScrollMgr.h"
#include "SelectView.h"

CTerrain::CTerrain()
{
	m_vecTile.reserve(TILEX * TILEY);
}

CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize(void)
{
	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/Stage/Terrain/Tile/Tile-%03d.png", TEX_MULTI, L"Terrain", L"Tile", 144)))
	{
		AfxMessageBox(L"Tile Image Insert failed");
		return;
	}
	

	// ���� Ÿ�� ����
	float fMoveSX = TILECX * 0.5f;
	float fMoveSY = TILECY * 0.5f;

	float fInvX = 0.f;
	float fInvY = 0.f;

	for (int i = 0; i < 144; ++i)
	{

		TILE* pTile = new TILE;

		int		fX = i % 8;
		int     fY = i / 8;

		pTile->vPos = { float(fX * TILECX + fMoveSX), float(fY * TILECY + fMoveSY), 0.f };
		pTile->vSize = { (float)TILECX, (float)TILECY, 0.f };
		pTile->byDrawID = (BYTE)i;
		pTile->byOption = 0;

		m_vecListTile.push_back(pTile);

		fInvX += 5.f;
		fInvY += 2.f;
	}

}

void CTerrain::Update(void)
{
}

void CTerrain::Tool_Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT	rc{};

	// ���� â ũ��� ���� â ũ���� ������ ���Ѵ�.
	::GetClientRect(m_pMainView->m_hWnd, &rc);
	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x - CScrollMgr::Get_Instance()->GetScroll_X(),
										 iter->vPos.y - CScrollMgr::Get_Instance()->GetScroll_Y(),
										 iter->vPos.z);

		matWorld = matScale *  matTrans;

		// ���� ��� ����
		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo)
			return;

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,	
													nullptr,
													&D3DXVECTOR3(fX, fY, 0.f), 
													nullptr, 
													D3DCOLOR_ARGB(255, 255, 255, 255));
	}	

}

void CTerrain::Mini_Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	TCHAR		szBuf[MIN_STR] = L"";
	int			iIndex = 0;

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x,
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale *  matTrans;

		Set_Ratio(&matWorld, 0.3f, 0.3f);

		const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo)
			return;

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fX, fY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));			
	}
}

void CTerrain::Select_Tile_Render(void)
{

	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT	rc{};

	// ���� â ũ��� ���� â ũ���� ������ ���Ѵ�.

	::GetClientRect(CViewMgr::Get_Instance()->GetView_Select()->m_hWnd, &rc);
	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	for (auto& iter : m_vecListTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x,
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale *  matTrans;

		// ���� ��� ����
		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo)
			return;

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fX, fY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	for_each(m_vecListTile.begin(), m_vecListTile.end(), CDeleteObj());
	m_vecListTile.clear();
	m_vecListTile.shrink_to_fit();
}


void CTerrain::Create_Tile(const D3DXVECTOR3 & vPos, const BYTE & byDrawID)
{
	int		iIndex = Get_TileIndex(vPos);
	
	if (-1 == iIndex)
	{ // Ÿ���� ������
		
		TILE* pTile = new TILE;

		int iCalX = ((int)vPos.x+13) / TILECX;
		int iCalY = ((int)vPos.y+13) / TILECY;

		pTile->vPos = { (float)iCalX * TILECX, (float)iCalY * TILECY, 0.f };
		pTile->vSize = { (float)TILECX, (float)TILECY, 0.f };
		pTile->byDrawID = byDrawID;
		pTile->byOption = 0;

		m_vecTile.push_back(pTile);
	}
	else
	{ // Ÿ���� ������
		// Tile_Change(vPos, 10);
	}

}
void CTerrain::Delete_Tile(const D3DXVECTOR3 & vPos)
{

}

void CTerrain::Tile_Change(const D3DXVECTOR3 & vPos, const BYTE & byDrawID)
{
	int		iIndex = Get_TileIndex(vPos);

	if (-1 == iIndex)
		return;
	
	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = 1;
}

int CTerrain::Get_TileIndex(const D3DXVECTOR3& vPos)
{
	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		if (Picking_Dot(vPos, iIndex, m_vecTile))
		{
			return iIndex;
		}
	}
	// ��ŷ ���� �� ���� ��ȯ
	return -1;
}

bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// y = ax + b;


	// 12, 3, 6, 9 �� ���� ������ ��ġ�� ����
	float	fGradient[4] = {

		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
		(TILECY / 2.f) / (TILECX / 2.f),
		(TILECY / 2.f) / (TILECX / 2.f) * -1.f,
		(TILECY / 2.f) / (TILECX / 2.f)
	};

	D3DXVECTOR3		vPoint[4] = {

		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f  },
		{ m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f }

	};

	// y = ax + b
	// -b = ax - y
	// b = y - ax		

	float	fB[4] = {

		vPoint[0].y - fGradient[0] * vPoint[0].x,
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x

	};


	//0 == ax + b - y	// ���� �� �ִ� ���
	//0 > ax + b - y  // ���� ���� �ִ� ���
	//0 < ax + b - y  // ���� �Ʒ��� �ִ� ���

	bool	bCheck[4] = { false };

	if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	if (0 > fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	if (0 > fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}
bool CTerrain::Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex, const vector<TILE*>& m_vec)
{
	D3DXVECTOR3		vPoint[4] = {

		{ m_vec[iIndex]->vPos.x, m_vec[iIndex]->vPos.y + (TILECY / 2.f), 0.f },
		{ m_vec[iIndex]->vPos.x + (TILECX / 2.f), m_vec[iIndex]->vPos.y, 0.f },
		{ m_vec[iIndex]->vPos.x, m_vec[iIndex]->vPos.y - (TILECY / 2.f), 0.f },
		{ m_vec[iIndex]->vPos.x - (TILECX / 2.f), m_vec[iIndex]->vPos.y, 0.f }

	};

	D3DXVECTOR3		vDir[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	D3DXVECTOR3		vNormal[4] = {

		{ -vDir[0].y, vDir[0].x, 0.f },
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f }
	};	

	D3DXVECTOR3	vMouseDir[4] = {

		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]		
	};
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		// ����� ��� �����̾ Ÿ�� �ܺο� ��ŷ�� ���� ��
		if (0.f < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}

	return true;
}

int CTerrain::Get_ListTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t iIndex = 0; iIndex < m_vecListTile.size(); ++iIndex)
	{
		if (Picking_Dot(vPos, iIndex, m_vecListTile))
		{
			return iIndex;
		}
	}
	// ��ŷ ���� �� ���� ��ȯ
	return -1;
}

void CTerrain::Set_Ratio(D3DXMATRIX* pOut, const float& _fX, const float& _fY, const float& fZ )
{
	pOut->_11 *= _fX;
	pOut->_21 *= _fX;
	pOut->_31 *= _fX;
	pOut->_41 *= _fX;
	
	pOut->_12 *= _fY;
	pOut->_22 *= _fY;
	pOut->_32 *= _fY;
	pOut->_42 *= _fY;


}
