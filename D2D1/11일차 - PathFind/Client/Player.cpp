#include "stdafx.h"
#include "Player.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"


CPlayer::CPlayer()
	: m_byDrawID(0)
{

}
CPlayer::~CPlayer()
{
	Release();
}


HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos.x = 300.f;
	m_tInfo.vPos.y = 300.f;
	m_tInfo.vPos.z = 0.f;
	m_vDestPos = m_tInfo.vPos;

	m_tInfo.vSize.x = 1.f;
	m_tInfo.vSize.y = 1.f;
	
	m_tInfo.vDir = D3DXVECTOR3{ 1.f, 0.f, 0.f };

	return E_NOTIMPL;
}

int CPlayer::Update(void)
{
	if (GetAsyncKeyState(MK_LBUTTON))
	{
		m_vDestPos = ::Get_Mouse();
	}

	D3DXVECTOR3 vDiffer = m_vDestPos - m_tInfo.vPos;
	float fDis = D3DXVec3Length(&vDiffer);
	
	if (fDis > 1.f)
	{
		D3DXVec3Normalize(&vDiffer, &vDiffer);

		m_tInfo.vPos.x += vDiffer.x * 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
		m_tInfo.vPos.y += vDiffer.y * 200.f * CTimeMgr::Get_Instance()->Get_TimeDelta();
	}
	

	UpdateAnim();
	return 0;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(void)
{
	D3DXMATRIX matWorld, matScale, matTrans;

	D3DXMatrixTranslation(&matTrans ,m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);

	matWorld = matScale * matTrans;



	CDevice::Get_Instance()->Render_Begin();


	const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Player", L"Walk", m_byDrawID);

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


	CDevice::Get_Instance()->Render_End();


}

void CPlayer::Release(void)
{
}

void CPlayer::UpdateAnim()
{

	if (0.1f < CTimeMgr::Get_Instance()->Get_SecondTime())
	{
		if (m_byDrawID < 12)
			++m_byDrawID;
		else
			m_byDrawID = 1;

		CTimeMgr::Get_Instance()->SetZero_SecondTime();
	}

}
