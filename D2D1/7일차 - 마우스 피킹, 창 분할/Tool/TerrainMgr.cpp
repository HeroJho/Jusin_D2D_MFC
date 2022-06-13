#include "stdafx.h"
#include "TerrainMgr.h"

IMPLEMENT_SINGLETON(CTerrainMgr)

CTerrainMgr::CTerrainMgr()
	: m_pTerrain(nullptr)
	, m_pMiniView(nullptr)
	, m_pToolView(nullptr)
{
}


CTerrainMgr::~CTerrainMgr()
{
	Release();
}


void CTerrainMgr::Initialize(void)
{
	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
}

void CTerrainMgr::Release(void)
{
	Safe_Delete<CTerrain*>(m_pTerrain);
}
