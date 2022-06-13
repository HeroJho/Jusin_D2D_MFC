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
	m_fSpeed		= 1.f;
}

void CMonster::Update(void)
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;
	float	fLengthM = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);
	float	fLengthP = sqrtf(m_pPlayer->Get_Info().vDir.x * m_pPlayer->Get_Info().vDir.x + m_pPlayer->Get_Info().vDir.y * m_pPlayer->Get_Info().vDir.y);
	float	fCos = (m_tInfo.vDir.x / fLengthM) * (m_pPlayer->Get_Info().vDir.x / fLengthP) + (m_tInfo.vDir.y / fLengthM) * (m_pPlayer->Get_Info().vDir.y / fLengthP);
	float fDegree = acosf(fCos);

	if (m_tInfo.vPos.y < m_pPlayer->Get_Info().vPos.y)
		fDegree *= -1;

	m_tInfo.vPos.x += m_fSpeed * cosf(fDegree);
	m_tInfo.vPos.y -= m_fSpeed * sinf(fDegree);
	m_tInfo.vDir.z = 0.f;

	// m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
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

// 단위 벡터 : 크기가 1인 벡터
// 벡터의 정규화 : 단위 벡터를 만드는 과정

// 벡터의 내적과 외적 : 반드시 두 방향 벡터(단위 벡터)를 통해 연산

// 내적 : 스칼라 곱(결과로 상수가 발생), 기호가 A ● B, 내적의 결과 : x*x` + y*y`+ z*z`
// 외적 : 벡터 곱(결과로 벡터가 발생), 기호가 A X B, 외적의 결과 

/*
X		Y		Z

X`      Y`      Z`

(Y * Z` - Z * Y`, X * Z` - Z * X`, X * Y` - Y * X`);*/


// 1. 벡터의 내적을 이용하여 플레이어를 따라다니는 몬스터를 구현하라.



// ===============================================
// 다렉에서는 행렬의 곱쌤만 사용한다.
// 행렬곱셈 법칙 꼭 꼭 알기!!

// 너무 중요!!!
// 행렬의 초기화는 모든 원소가 0인 상태가 아니다!! (제로 메모리X)
// 항등 행렬인 상태가 초기화 상태이다!!!
// 항등 행렬로 초기화를 하지않으면 포폴이 아작날수도 있을정도로!

// 로컬스페이스, 월드스페이스
// 점마다 월드행렬을 곱해줘야해서 그래픽카드를 써야한다.


// 크자이공부 꼭 암기하기 ! 과제!! 곱셈 순서는 꼭 필요!!

// 조명 >> 연산이 또 배로 늠 >> 그래픽카드 죽음 >> 파이프라인 커스터마이징해서 조명연산을 그래픽 카드에 넘긴 >> 이게 쉐이더

// 숙제: z축 회전을 이용하여 포신과 몸체가 따로 돌아가는 탱크를 만들어라