#include "stdafx.h"
#include "MainGame.h"
#include "Monster.h"


CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}

	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

	dynamic_cast<CMonster*>(m_pMonster)->Set_Player(m_pPlayer);

}

void CMainGame::Update(void)
{
	m_pPlayer->Update();
	m_pMonster->Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_hDC);
	m_pMonster->Render(m_hDC);
}

void CMainGame::Release(void)
{
	Safe_Delete<CObj*>(m_pMonster);
	Safe_Delete<CObj*>(m_pPlayer);

	ReleaseDC(g_hWnd, m_hDC);	
}
