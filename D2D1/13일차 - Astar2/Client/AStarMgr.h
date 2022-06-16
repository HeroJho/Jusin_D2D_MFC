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
	// A*���� �Լ�
	void			Astar_Start(const D3DXVECTOR3& vStart, const D3DXVECTOR3& vGoal);
	void			Release(void);

private:
	// ��θ� Ž���Ѵ�. (��� �Լ�)
	// �� �Լ����� m_OpenList�� m_CloseList�� ä���.
	// �׸��� Ÿ�ϵ��� �θ� �ε������� ä���.
	bool			Make_Route(int iStartIdx, int iGoalIdx);
	// �ִܰŸ� Ÿ�ϵ��� ã�´�.
	void			Make_BestList(int iStartIdx, int iGoalIdx);

private:
	// Ŭ���� ��ǥ�� Ÿ���� ���ϱ� ���� ���(������)
	int				GetTileIndex(const D3DXVECTOR3& vPos);
	bool			Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	bool			Check_Close(int iIndex);
	bool			Check_Open(int iIndex);

private:
	// �̵��� ������ Ÿ�� (�� ����Ʈ�� �����ؼ� ���� ����� Ÿ���� ��󳽴�)
	list<int>			m_OpenList;
	// �̹� �湮�� ����Ʈ
	list<int>			m_CloseList;
	// ���������� �ϼ��� ��ã�� ����Ʈ
	list<TILE*>			m_BestList;
	// ���� �ε���
	int					m_iStartIdx;

};

