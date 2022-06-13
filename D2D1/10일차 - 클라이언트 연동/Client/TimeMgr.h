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
	LARGE_INTEGER		m_CurrentTime; // 현재 프레임 시간
	LARGE_INTEGER		m_OldTime;     // 이전 프레임 시간
	LARGE_INTEGER		m_OriginTime;  // 주파수 갱신용
	LARGE_INTEGER		m_CpuTick;     // 현재 하드웨어의 초당 주파수

	float				m_fTimeDelta;  // 1초에 따른 한 프레임 시간
};

