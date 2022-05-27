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
}

void CMonster::Update(void)
{
	m_tInfo.vDir = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;

	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
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