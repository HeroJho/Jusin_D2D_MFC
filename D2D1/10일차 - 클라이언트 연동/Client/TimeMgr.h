#pragma once

#include "Include.h"

class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

public:
	CTimeMgr();
	~CTimeMgr();

public:
	float			Get_TimeDelta(void) { return m_fTimeDelta; }

public:
	HRESULT				Initialize();
	void				Update(void);

private:
	LARGE_INTEGER		m_CurrentTime; // ���� ������ �ð�
	LARGE_INTEGER		m_OldTime;     // ���� ������ �ð�
	LARGE_INTEGER		m_OriginTime;  // ���ļ� ���ſ�
	LARGE_INTEGER		m_CpuTick;     // ���� �ϵ������ �ʴ� ���ļ�

	float				m_fTimeDelta;  // 1�ʿ� ���� �� ������ �ð�
};

