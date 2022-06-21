#pragma once

#include "Obj.h"

class CBullet : 	public CObj
{
public:
	CBullet();
	virtual ~CBullet();


	

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

public:
	static CBullet*		Create(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir);

};

