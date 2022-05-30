#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos	= { 100.f, 100.f, 0.f };
	m_fSpeed		= 5.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

void CMonster::Update(void)
{

#pragma region 복습

	/*m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;
	
	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;*/

#pragma endregion 복습

#pragma region 복습 2

	/*m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	float	fDiagonal = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fDiagonal;
	m_tInfo.vDir.y /= fDiagonal;
	m_tInfo.vDir.z = 0.f;

	float	fDiagonal2 = sqrtf(m_tInfo.vLook.x * m_tInfo.vLook.x + m_tInfo.vLook.y * m_tInfo.vLook.y);

	m_tInfo.vLook.x /= fDiagonal2;
	m_tInfo.vLook.y /= fDiagonal2;
	m_tInfo.vLook.z = 0.f;

	float	fDot = m_tInfo.vDir.x * m_tInfo.vLook.x + m_tInfo.vDir.y * m_tInfo.vLook.y;

	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
	m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);*/

#pragma endregion 복습 2

	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

	// 벡터의 정규화를 수행하는 함수(1. 결과 값을 어디에 저장할 것인가 2. 단위 벡터로 만들 벡터)
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	// 벡터의 크기를 구해주는 함수
	// float fLength = D3DXVec3Length(&m_tInfo.vDir);

	// 두 방향 벡터의 내적을 수행하는 함수
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	// 두 방향 벡터의 외적을 수행하는 함수(1. 결과 값을 저장할 벡터, 2~3으로 향하는 외적 순서)

	/*D3DXVECTOR3	vAxis;
	D3DXVec3Cross(&vAxis, &m_tInfo.vDir, &m_tInfo.vLook);*/
		
	float	fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < Get_Mouse().y)
		fAngle = 2.f * D3DX_PI - fAngle;

	m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
	m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);

	
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release(void)
{
	
}
