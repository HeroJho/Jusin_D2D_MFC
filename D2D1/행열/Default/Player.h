#pragma once
#include "Obj.h"

typedef struct Square
{

	D3DXVECTOR3 Pos_1;
	D3DXVECTOR3 Pos_2;
	D3DXVECTOR3 Pos_3;
	D3DXVECTOR3 Pos_4;

}SQUARE;


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
	SQUARE m_tSquare;
	D3DXVECTOR3 m_tPosinDir;
	float m_fDegree;

};

	