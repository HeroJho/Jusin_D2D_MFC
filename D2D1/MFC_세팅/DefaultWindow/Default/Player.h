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
	void		Key_Input(void);


private:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	D3DXVECTOR3			m_vGunPoint;
	D3DXVECTOR3			m_vOriginGunPoint;

	float				m_fGunAngle = 0.f;


/*

	D3DXVECTOR3		m_vPlayerPos;	// ¿ßƒ° ∫§≈Õ
	
	D3DXVECTOR3		m_vPlayerDir;	// πÊ«‚ ∫§≈Õ
	D3DXVECTOR3		m_vPlayerLook;	// πÊ«‚ ∫§≈Õ

	D3DXVECTOR3		m_vPlayerNormal;	// π˝º± ∫§≈Õ*/
};

	