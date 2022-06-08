#pragma once

#include "SingleTexture.h"
#include "MultiTexture.h"

#include "Terrain.h"
#include "ToolView.h"
#include "MiniView.h"

class CTerrainMgr
{
	DECLARE_SINGLETON(CTerrainMgr)

private:
	CTerrainMgr();
	~CTerrainMgr();

public:
	CTerrain* Get_Terrain() { return m_pTerrain; }

	void Set_ToolView(CToolView* _pToolView) { m_pToolView = _pToolView; }
	void Set_MiniView(CMiniView* _pMiniView) { m_pMiniView = _pMiniView; }

	CToolView* Get_ToolView() { return m_pToolView; }
	CMiniView* Get_MiniView() { return m_pMiniView; }

public:
	void		Initialize(void);
	void		Release(void);

private:
	CTerrain*			m_pTerrain;

	CMiniView* m_pMiniView;
	CToolView* m_pToolView;
};

