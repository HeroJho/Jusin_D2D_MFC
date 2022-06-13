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
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_fSpeed = 3.f;

	m_lVertaxList.push_back(D3DXVECTOR3(-50.f, -50.f, 0.f));
	m_lVertaxList.push_back(D3DXVECTOR3(50.f, -50.f, 0.f));
	m_lVertaxList.push_back(D3DXVECTOR3(50.f, 50.f, 0.f));
	m_lVertaxList.push_back(D3DXVECTOR3(-50.f, 50.f, 0.f));
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


// 정점들은 누적x
// 로컬은 고정이고 월드만 바뀌는 것이다.
// 월드 행렬은 매 프레임마다 새로운 월드행열을 구해준다.
// 원본 로컬값은 어디선가 저장을 해야한다.

// 스케일을 음수로 하면 반전이 된다.

// MFC >> 키타프로젝트 >> 비주얼 솔루션
// MFC와 WinApi 둘을 사용한다.

// 추가 셋프로젝트 MFC
// MFC가 없으면 모듈을 깔아야한다.
// 다음 단일문서 MFC표준 고유DLL에서MFC사용 마침
// MFC는 Api를 기반으로 만들어진 새로운 프로그램(클래스 기반으로)
// 객체 지향으로 프로그래밍을 할 수 있다. 하지만 구조가 복잡해서 선호하지 않는다.
// 현재는 MFC가 망해가는 추세... 따로 공부는 할 필요는 없다.
// 그럼 왜 하냐?
// MFC로 게임을 만들 수 있따 >> 하지만 클래스의 상속이 기본 4단이 되는등 클래스의 규모가 커서
// 퍼포먼스가 떨어진다. 그래서 툴을 만드는 용도로만 쓰인다.

// cWin에 헨들이 있다 객체를 생성하면 핸들을 하나씩 가지고 태어난다 >> 한객체 == 하나의 뷰
// MPC 무한루프 함수 >> 무한 루프가 어디에 도는 알기가 힘들다 콜백 함수를 등록해야한다.
// OnIdle함수를 써도됨 >> 무한루프