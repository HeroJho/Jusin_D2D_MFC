#include "stdafx.h"
#include "ScrollMgr.h"


IMPLEMENT_SINGLETON(CScrollMgr)

CScrollMgr::CScrollMgr()
	: m_fScrollSpeed(30.f)
	, m_fScrollX(0.f)
	, m_fScrollY(0.f)
	, m_fMaxScrollX(0.f)
	, m_fMaxScrollY(0.f)
{
}
CScrollMgr::~CScrollMgr()
{
	Release();
}



void CScrollMgr::IncreaseScroll_X()
{
	if (0.f > m_fScrollX)
		m_fScrollX = 0.f;

	m_fScrollX += m_fScrollSpeed;

	if (m_fScrollX > m_fMaxScrollX)
		m_fMaxScrollX = m_fScrollX;
}
void CScrollMgr::DecreaseScroll_X()
{
	if (0.f > m_fScrollX)
		m_fScrollX = 0.f;

	m_fScrollX -= m_fScrollSpeed;

	if (m_fScrollX > m_fMaxScrollX)
		m_fMaxScrollX = m_fScrollX;
}
void CScrollMgr::IncreaseScroll_Y()
{
	if (0.f > m_fScrollY)
		m_fScrollY = 0.f;

	m_fScrollY -= m_fScrollSpeed;

	if (m_fScrollY > m_fMaxScrollY)
		m_fMaxScrollY = m_fScrollY;
}
void CScrollMgr::DecreaseScroll_Y()
{
	if (0.f > m_fScrollY)
		m_fScrollY = 0.f;

	m_fScrollY += m_fScrollSpeed;

	if (m_fScrollY > m_fMaxScrollY)
		m_fMaxScrollY = m_fScrollY;
}

void CScrollMgr::Release(void)
{
}
