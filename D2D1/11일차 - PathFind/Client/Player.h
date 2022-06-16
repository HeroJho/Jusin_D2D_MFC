#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	void UpdateAnim();

private:
	int m_byDrawID;
	
	D3DXVECTOR3 m_vDestPos;

};

