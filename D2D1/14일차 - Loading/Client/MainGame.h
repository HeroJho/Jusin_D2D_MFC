#pragma once

#include "Include.h"
#include "TextureMgr.h"

class CDevice;
class CMainGame
{
public:
	HRESULT		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	CDevice*			m_pGraphicDev = nullptr;

	TCHAR				m_szFPS[MIN_STR];
	int					m_iFps;

public:
	CMainGame();
	~CMainGame();
};

// 메모리 단편화 : 메모리 조각화, 조각난 메모리로 인해 메모리가 낭비되거나 충분한 메모리가 있음에도 불구하고 사용할 수 없는 현상

//- 내부 단편화 : 실제 필요한 메모리보다 초과되는 크기로 할당되어 이때 남는 부분이 낭비되는 것을 의미(EX : 구조체)
//- 외부 단편화 : 빈번한 메모리 할당, 해제 시 메모리가 중간중간 비게 되는 현상 

// 메모리 풀링 : 메모리를 미리 할당하여 계속적으로 재활용하는 형태를 둬서 단편화를 최소화하는 기법
