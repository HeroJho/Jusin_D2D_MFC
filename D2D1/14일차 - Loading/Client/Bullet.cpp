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
		nullptr, // ����� �̹��� ������ ���� ��Ʈ �ּҰ�, null�� ��� �̹����� 0, 0 �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // ����� �̹��� �߽� �࿡ ���� ����3 �ּҰ�, null�� ��� 0, 0�� �߽� ��ǥ
		nullptr, // ��ġ ��ǥ�� ���� ����3 �ּҰ�, null�� ��� ��ũ�� �� 0, 0 ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ���� ��, ��� �� ���� ������ �ݿ�, 0xffffffff�� �Ѱ��ָ� ������ ����
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
