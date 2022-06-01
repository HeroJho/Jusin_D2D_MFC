#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

	// 항등행렬로 행렬을 초기화 하는 함수
	D3DXMatrixIdentity(&m_tInfo.matWorld);

}

CObj::~CObj()
{
}

