#pragma once

typedef	struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;		

}INFO;


// dx에서는 4x4짜리 float형 16개짜리 멤버 변수가 있는 행렬을 제공한다.
