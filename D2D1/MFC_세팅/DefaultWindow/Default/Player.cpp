#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };


	m_vPoint[0] = { m_tInfo.vPos.x - 50.f,  m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 50.f,  m_tInfo.vPos.y - 50.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 50.f,  m_tInfo.vPos.y + 50.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 50.f,  m_tInfo.vPos.y + 50.f, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];


	// 포신
	m_vGunPoint = { m_tInfo.vPos.x, m_tInfo.vPos.y - 100.f, 0.f };

	m_vOriginGunPoint = m_vGunPoint;


	m_fSpeed = 5.f;
}

void CPlayer::Update(void)
{
	// 연산을 진행
	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];

		m_vPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);		
	}

	m_vGunPoint = m_vOriginGunPoint;

	m_vGunPoint -= { 400.f, 300.f, 0.f };
	D3DXVec3TransformCoord(&m_vGunPoint, &m_vGunPoint, &m_tInfo.matWorld);


#pragma region 벡터만 사용
	
	/*for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vTemp = m_vOriginPoint[i];

		vTemp -= { 400.f, 300.f, 0.f };

		// 회전 적용
		m_vPoint[i].x = vTemp.x * cosf(m_fAngle) - vTemp.y * sinf(m_fAngle);
		m_vPoint[i].y = vTemp.x * sinf(m_fAngle) + vTemp.y * cosf(m_fAngle);

		// 이동 적용
		m_vPoint[i] += m_tInfo.vPos;
	}

	D3DXVECTOR3		vTemp = m_vOriginGunPoint;

	vTemp -= { 400.f, 300.f, 0.f };

	// 회전 적용
	m_vGunPoint.x = vTemp.x * cosf(m_fGunAngle) - vTemp.y * sinf(m_fGunAngle);
	m_vGunPoint.y = vTemp.x * sinf(m_fGunAngle) + vTemp.y * cosf(m_fGunAngle);

	// 이동 적용
	m_vGunPoint += m_tInfo.vPos;*/

#pragma endregion 벡터만 사용

}

void CPlayer::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if(i > 0)
			continue;

		Ellipse(hDC,
			(int)m_vPoint[i].x - 5.f,
			(int)m_vPoint[i].y - 5.f,
			(int)m_vPoint[i].x + 5.f,
			(int)m_vPoint[i].y + 5.f);
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	// 포신 그리기

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);

	LineTo(hDC, (int)m_vGunPoint.x, (int)m_vGunPoint.y);

}

void CPlayer::Release(void)
{
	
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}
	
	if (GetAsyncKeyState('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_fAngle += D3DXToRadian(3.f);

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fGunAngle -= D3DXToRadian(3.f);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fGunAngle += D3DXToRadian(3.f);
	}

}
