#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void ResetVec();

private:
	void		Key_Input(void);

private:
	D3DXVECTOR3 m_tPosinDir;
	float m_fDegree;

};

	