#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
	: m_fDegree(0.f)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tSquare = {};

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_fSpeed = 3.f;

	m_tSquare.Pos_1.x = -50.f;
	m_tSquare.Pos_1.y = -50.f;

	m_tSquare.Pos_2.x = 50.f;
	m_tSquare.Pos_2.y = -50.f;

	m_tSquare.Pos_3.x = -50.f;
	m_tSquare.Pos_3.y = 50.f;

	m_tSquare.Pos_4.x = 50.f;
	m_tSquare.Pos_4.y = 50.f;
}

void CPlayer::Update(void)
{
	D3DXVECTOR3 vMousePos = Get_Mouse();

	m_tPosinDir = vMousePos - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tPosinDir, &m_tPosinDir);

	Key_Input();

	ResetVec();

	D3DXMATRIX	matScale, matRotZ, matTrans;

	// 크기 변환 행렬 생성 함수
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	// z축 회전 행렬 생성 함수
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fDegree));

	// 이동 행렬 생성 함수
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;


	// 위치 벡터와 행렬을 곱셈하여 최종적인 위치 벡터를 반환하는 함수
	D3DXVec3TransformCoord(&m_tSquare.Pos_1, &m_tSquare.Pos_1, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_tSquare.Pos_2, &m_tSquare.Pos_2, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_tSquare.Pos_3, &m_tSquare.Pos_3, &m_tInfo.matWorld);
	D3DXVec3TransformCoord(&m_tSquare.Pos_4, &m_tSquare.Pos_4, &m_tInfo.matWorld);

	// 방향 벡터와 행렬을 곱셈하여 최종적인 방향 벡터를 반환하는 함수
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
}

void CPlayer::Render(HDC hDC)
{
	// 4점을 사용해서 그리기
	MoveToEx(hDC, (int)m_tSquare.Pos_1.x, (int)m_tSquare.Pos_1.y, nullptr);
	LineTo(hDC, (int)(int)m_tSquare.Pos_2.x, (int)(int)m_tSquare.Pos_2.y);
	MoveToEx(hDC, (int)m_tSquare.Pos_2.x, (int)m_tSquare.Pos_2.y, nullptr);
	LineTo(hDC, (int)(int)m_tSquare.Pos_4.x, (int)(int)m_tSquare.Pos_4.y);
	MoveToEx(hDC, (int)m_tSquare.Pos_4.x, (int)m_tSquare.Pos_4.y, nullptr);
	LineTo(hDC, (int)(int)m_tSquare.Pos_3.x, (int)(int)m_tSquare.Pos_3.y);
	MoveToEx(hDC, (int)m_tSquare.Pos_3.x, (int)m_tSquare.Pos_3.y, nullptr);
	LineTo(hDC, (int)(int)m_tSquare.Pos_1.x, (int)(int)m_tSquare.Pos_1.y);

	// 정면 표시
	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)(m_tInfo.vPos.x + m_tInfo.vDir.x * 50), (int)(m_tInfo.vPos.y + m_tInfo.vDir.y * 50));
	
	// 포신
	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)(m_tInfo.vPos.x + m_tPosinDir.x * 100), (int)(m_tInfo.vPos.y + m_tPosinDir.y * 100));
}

void CPlayer::Release(void)
{
	
}

void CPlayer::ResetVec()
{
	m_tSquare.Pos_1.x = -50.f;
	m_tSquare.Pos_1.y = -50.f;

	m_tSquare.Pos_2.x = 50.f;
	m_tSquare.Pos_2.y = -50.f;

	m_tSquare.Pos_3.x = -50.f;
	m_tSquare.Pos_3.y = 50.f;

	m_tSquare.Pos_4.x = 50.f;
	m_tSquare.Pos_4.y = 50.f;

	m_tInfo.vDir = { 1.f, 0.f, 0.f };
}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState(VK_LEFT))
		m_fDegree -= 5.f;

	if (GetAsyncKeyState(VK_RIGHT))
		m_fDegree += 5.f;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.vPos += m_fSpeed * m_tInfo.vDir;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.vPos -= m_fSpeed * m_tInfo.vDir;
}
