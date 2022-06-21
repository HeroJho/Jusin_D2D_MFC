#include "stdafx.h"
#include "Player.h"
#include "TextureMgr.h"
#include "Device.h"
#include "AStarMgr.h"
#include "TimeMgr.h"
#include "BulletPoolMgr.h"
#include "ObjMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos	= { 100.f, 200.f, 0.f };
	m_wstrObjKey	= L"Player";
	m_wstrStateKey	= L"Dash";

	m_tFrame = { 0.f, 11.f };

	return S_OK;
}

int CPlayer::Update(void)
{
	Fire_Bullet();

	D3DXMATRIX	matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + CObj::m_vScroll.x, 
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	Move_Frame();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		CAStarMgr::Get_Instance()->Astar_Start(m_tInfo.vPos, ::Get_Mouse() - CObj::m_vScroll);
	}

	Move_Route();
}

void CPlayer::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fX = pTexInfo->tImgInfo.Width / 2.f;
	float		fY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release(void)
{
	
}

void CPlayer::Move_Route(void)
{
	list<TILE*>& BestList = CAStarMgr::Get_Instance()->Get_BestList();

	if (!BestList.empty())
	{
		int	iIndex = BestList.front()->iIndex;

		D3DXVECTOR3	vDir = BestList.front()->vPos - m_tInfo.vPos;

		float fDistance = D3DXVec3Length(&vDir);
		D3DXVec3Normalize(&vDir, &vDir);

		m_tInfo.vPos += vDir * 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

		// 타일에 가까워졌을 때 다음 길을 찾기 위해 맨 앞에 원소를 제거
		if (3.f >= fDistance)
			BestList.pop_front();
	}
}

void CPlayer::Fire_Bullet(void)
{
	m_fFireItv += CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_fFireItv < 3.f)
		return;

	m_fFireItv = 0.f;

	D3DXMATRIX	matRot, matTrans, matWorld;
	D3DXVECTOR3	vDir{ 1.f, 0.f, 0.f };

	for (m_fFireAngle = 0.f; m_fFireAngle < 360.f; ++m_fFireAngle)
	{
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(-m_fFireAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x,
			m_tInfo.vPos.y, 0.f);

		matWorld = matRot * matTrans;

		D3DXVec3TransformNormal(&vDir, &vDir, &matWorld);

		CObj*		pBullet = CBulletPoolMgr::Get_Instance()->ReuseObj(m_tInfo.vPos, vDir);

		//CBullet*		pBullet = CBullet::Create(m_tInfo.vPos, vDir);

		CObjMgr::Get_Instance()->Add_Object(CObjMgr::BULLET, pBullet);

		//++m_iCount;
	}

#ifdef _DEBUG

	//cout << "총알 생성 개수 : " << m_iCount << endl;

#endif // _DEBUG
}

