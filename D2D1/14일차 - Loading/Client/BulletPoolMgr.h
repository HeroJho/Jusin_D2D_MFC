#pragma once

#include "Bullet.h"

class CBulletPoolMgr
{
	DECLARE_SINGLETON(CBulletPoolMgr)

private:
	CBulletPoolMgr();
	~CBulletPoolMgr();

public:
	// 현재 풀에 있는 오브젝트를 재사용
	CObj*			ReuseObj(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir);

	// 사용을 마친 오브젝트를 회수
	void			CollectObj(CObj* pObj);

private:
	void			Release(void);

private:
	list<CObj*>			m_ObjectPool;
	int					m_iCount = 0;
};

