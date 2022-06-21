#pragma once

#include "Bullet.h"

class CBulletPoolMgr
{
	DECLARE_SINGLETON(CBulletPoolMgr)

private:
	CBulletPoolMgr();
	~CBulletPoolMgr();

public:
	// ���� Ǯ�� �ִ� ������Ʈ�� ����
	CObj*			ReuseObj(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir);

	// ����� ��ģ ������Ʈ�� ȸ��
	void			CollectObj(CObj* pObj);

private:
	void			Release(void);

private:
	list<CObj*>			m_ObjectPool;
	int					m_iCount = 0;
};

