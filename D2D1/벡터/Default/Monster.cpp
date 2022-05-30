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

// ���� ���� : ũ�Ⱑ 1�� ����
// ������ ����ȭ : ���� ���͸� ����� ����

// ������ ������ ���� : �ݵ�� �� ���� ����(���� ����)�� ���� ����

// ���� : ��Į�� ��(����� ����� �߻�), ��ȣ�� A �� B, ������ ��� : x*x` + y*y`+ z*z`
// ���� : ���� ��(����� ���Ͱ� �߻�), ��ȣ�� A X B, ������ ��� 

/*
X		Y		Z

X`      Y`      Z`

(Y * Z` - Z * Y`, X * Z` - Z * X`, X * Y` - Y * X`);*/


// 1. ������ ������ �̿��Ͽ� �÷��̾ ����ٴϴ� ���͸� �����϶�.



// ===============================================
// �ٷ������� ����� ���ܸ� ����Ѵ�.
// ��İ��� ��Ģ �� �� �˱�!!

// �ʹ� �߿�!!!
// ����� �ʱ�ȭ�� ��� ���Ұ� 0�� ���°� �ƴϴ�!! (���� �޸�X)
// �׵� ����� ���°� �ʱ�ȭ �����̴�!!!
// �׵� ��ķ� �ʱ�ȭ�� ���������� ������ ���۳����� ����������!

// ���ý����̽�, ���彺���̽�
// ������ ��������� ��������ؼ� �׷���ī�带 ����Ѵ�.


// ũ���̰��� �� �ϱ��ϱ� ! ����!! ���� ������ �� �ʿ�!!

// ���� >> ������ �� ��� �� >> �׷���ī�� ���� >> ���������� Ŀ���͸���¡�ؼ� �������� �׷��� ī�忡 �ѱ� >> �̰� ���̴�

// ����: z�� ȸ���� �̿��Ͽ� ���Ű� ��ü�� ���� ���ư��� ��ũ�� ������