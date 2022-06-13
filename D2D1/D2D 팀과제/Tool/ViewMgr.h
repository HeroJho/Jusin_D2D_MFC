#pragma once

#include "Include.h"

class CMiniView;
class CToolView;

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

	CMiniView* GetView_Mini() { return m_pMiniView; }
	CToolView* GetView_Tool() { return m_pToolView; }

public:
	void All_Invalidate();


	void		Release(void);

private:
	CMiniView* m_pMiniView;
	CToolView* m_pToolView;

};

