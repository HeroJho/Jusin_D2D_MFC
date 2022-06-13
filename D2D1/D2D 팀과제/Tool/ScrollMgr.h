#pragma once

#include "Include.h"

#include "ViewMgr.h"
#include "ToolView.h"

class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

public:
	CScrollMgr();
	~CScrollMgr();

public:
	//float GetScroll_X() { return m_fScrollX + GetViewScroll_X(); }
	//float GetScroll_Y() { return m_fScrollY + GetViewScroll_Y(); }
	float GetScroll_X() { return m_fScrollX; }
	float GetScroll_Y() { return m_fScrollY; }
	float GetMaxScroll_X() { return m_fMaxScrollX; }
	float GetMaxScroll_Y() { return m_fMaxScrollY; }

	float GetViewScroll_X() { return (float)(CViewMgr::Get_Instance()->GetView_Tool()->GetScrollPos(0)); }
	float GetViewScroll_Y() { return (float)(CViewMgr::Get_Instance()->GetView_Tool()->GetScrollPos(1)); }

public:
	void IncreaseScroll_X();
	void DecreaseScroll_X();
	void IncreaseScroll_Y();
	void DecreaseScroll_Y();



	void Release(void);

private:
	float m_fScrollSpeed;
	
	float m_fScrollX;
	float m_fScrollY;
	
	float m_fMaxScrollX;
	float m_fMaxScrollY;

};

