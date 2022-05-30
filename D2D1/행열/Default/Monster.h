#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	void		Set_Player(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	virtual void Initialize(void) override;

	virtual void Update(void) override;

	virtual void Render(HDC hDC) override;

	virtual void Release(void) override;

private:
	CObj*		m_pPlayer = nullptr;

};

