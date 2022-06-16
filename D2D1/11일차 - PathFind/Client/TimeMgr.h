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
	float			Get_SecondTime(void) { return m_fSecondTime; }
	void			SetZero_SecondTime(void) { m_fSecondTime = 0.f; }

public:
	HRESULT				Initialize();
	void				Update(void);

private:
	LARGE_INTEGER		m_CurrentTime;
	LARGE_INTEGER		m_OldTime;
	LARGE_INTEGER		m_OriginTime;
	LARGE_INTEGER		m_CpuTick;

	float				m_fTimeDelta;
	float				m_fSecondTime;
};

