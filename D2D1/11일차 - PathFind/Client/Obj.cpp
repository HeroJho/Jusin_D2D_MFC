#include "stdafx.h"
#include "Obj.h"

D3DXVECTOR3 CObj::m_vScroll{};

CObj::CObj()
{

	ZeroMemory(&m_tInfo, sizeof(tagInfo));
	D3DXMatrixIdentity(&m_tInfo.matWorld);

}

CObj::~CObj()
{

}
