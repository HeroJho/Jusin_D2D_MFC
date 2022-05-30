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

// 1. w,a,s,d 키를 눌러 4방향 총알쏘기
// 2. 가로 세로가 100씩 작은 렉트를 만들고 사각형 범위를 벗어나면 미사일을 삭제하라