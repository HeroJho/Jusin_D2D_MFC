#pragma once

#include "Include.h"

class CMiniView;
class CToolView;
class CSelectView;

class CViewMgr
{
	DECLARE_SINGLETON(CViewMgr)

public:
	CViewMgr();
	~CViewMgr();

public:
	void Initialize();

public:
	void SetView_Mini(CMiniView* _pMiniView) { m_pMiniView = _pMiniView; }
	void SetView_Tool(CToolView* _pToolView) { m_pToolView = _pToolView; }
	void SetView_Select(CSelectView* _pSelectView) { m_pSelectView = _pSelectView; }

	CMiniView* GetView_Mini() { return m_pMiniView; }
	CToolView* GetView_Tool() { return m_pToolView; }
	CSelectView* GetView_Select() { return m_pSelectView; }

	int Get_PickedTile() { return m_iPickedTile; }
	void Set_PickedTile(int _iPickedTile) { m_iPickedTile = _iPickedTile; }


public:
	void All_Invalidate();

	void		Release(void);

private:
	CMiniView* m_pMiniView;
	CToolView* m_pToolView;
	CSelectView* m_pSelectView;

	int m_iPickedTile;

};

