#include "stdafx.h"
#include "Bullet.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "BulletPoolMgr.h"


CBullet::CBullet()
{
	
}


CBullet::~CBullet()
{
	Release();
}

HRESULT CBullet::Initialize(void)
{
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_wstrObjKey = L"Effect";
	m_wstrStateKey = L"ElectronicShock";
	m_tFrame = { 0.f, 9.f };
	
	return S_OK;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.vPos += m_tInfo.vDir * 300.f * CTimeMgr::Get_Instance()->Get_TimeDelta();


	D3DXMATRIX			matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	Move_Frame();

	if (0.f >= m_tInfo.vPos.x + CObj::m_vScroll.x ||
		(float)WINCX <= m_tInfo.vPos.x + CObj::m_vScroll.x ||
		0.f >= m_tInfo.vPos.y + CObj::m_vScroll.y ||
		(float)WINCY <= m_tInfo.vPos.y + CObj::m_vScroll.y)
	{
		CBulletPoolMgr::Get_Instance()->CollectObj(this);
		return OBJ_DEAD;
	}
	
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
		
}

void CBullet::Render(void)
{
	const TEXINFO*	 pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr, // 출력할 이미지 영역에 따른 렉트 주소값, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지 중심 축에 대한 벡터3 주소값, null인 경우 0, 0이 중심 좌표
		nullptr, // 위치 좌표에 대한 벡터3 주소값, null인 경우 스크린 상 0, 0 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상 값, 출력 시 섞은 색상이 반영, 0xffffffff를 넘겨주면 원본색 유지
}

void CBullet::Release(void)
{
	
}

CBullet* CBullet::Create(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir)
{
	CBullet*		pBullet = new CBullet;

	if (FAILED(pBullet->Initialize()))
	{
		Safe_Delete(pBullet);
		return nullptr;	
	}

	pBullet->Set_Pos(vPos);
	pBullet->Set_Dir(vDir);

	return pBullet;
}
