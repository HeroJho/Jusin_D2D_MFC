#include "stdafx.h"
#include "BulletPoolMgr.h"

IMPLEMENT_SINGLETON(CBulletPoolMgr)

CBulletPoolMgr::CBulletPoolMgr()
{

}


CBulletPoolMgr::~CBulletPoolMgr()
{
	Release();
}

CObj* CBulletPoolMgr::ReuseObj(const D3DXVECTOR3& vPos, const D3DXVECTOR3& vDir)
{
	CObj*		pBullet = nullptr;

	if (m_ObjectPool.empty())
	{
		pBullet = CBullet::Create(vPos, vDir);
		++m_iCount;

#ifdef _DEBUG

		cout << "총알 생성 개수 : " << m_iCount << endl;

#endif // _DEBUG
	}
	else
	{
		pBullet = m_ObjectPool.front();
		m_ObjectPool.pop_front();
	}

	if (nullptr == pBullet)
		return nullptr;

	pBullet->Set_Pos(vPos);
	pBullet->Set_Dir(vDir);

	return pBullet;
}

void CBulletPoolMgr::CollectObj(CObj* pObj)
{
	if (nullptr == pObj)
		return;

	m_ObjectPool.push_back(pObj);
}

void CBulletPoolMgr::Release(void)
{
	for (auto& iter : m_ObjectPool)
		Safe_Delete(iter);

	m_ObjectPool.clear();
}
