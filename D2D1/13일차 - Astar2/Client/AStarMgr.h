#pragma once

#include "Include.h"

class CAStarMgr
{
	DECLARE_SINGLETON(CAStarMgr)

private:
	CAStarMgr();
	~CAStarMgr();

public:
	list<TILE*>&	Get_BestList(void) { return m_BestList; }

public:
	// A*시작 함수
	void			Astar_Start(const D3DXVECTOR3& vStart, const D3DXVECTOR3& vGoal);
	void			Release(void);

private:
	// 경로를 탐색한다. (재귀 함수)
	// 이 함수에서 m_OpenList와 m_CloseList를 채운다.
	// 그리고 타일들의 부모 인덱스값을 채운다.
	bool			Make_Route(int iStartIdx, int iGoalIdx);
	// 최단거리 타일들을 찾는다.
	void			Make_BestList(int iStartIdx, int iGoalIdx);

private:
	// 클릭한 좌표의 타일을 구하기 위해 사용(도착점)
	int				GetTileIndex(const D3DXVECTOR3& vPos);
	bool			Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	bool			Check_Close(int iIndex);
	bool			Check_Open(int iIndex);

private:
	// 이동이 가능한 타일 (이 리스트를 정렬해서 가장 가까운 타일을 골라낸다)
	list<int>			m_OpenList;
	// 이미 방문한 리스트
	list<int>			m_CloseList;
	// 최종적으로 완성된 길찾기 리스트
	list<TILE*>			m_BestList;
	// 시작 인덱스
	int					m_iStartIdx;

};

