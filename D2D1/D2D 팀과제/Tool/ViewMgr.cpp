#include "stdafx.h"
#include "ViewMgr.h"

#include "MainFrm.h"
#include "MiniView.h"
#include "ToolView.h"
#include "SelectView.h"

IMPLEMENT_SINGLETON(CViewMgr)

CViewMgr::CViewMgr()
	: m_pMiniView(nullptr)
	, m_pToolView(nullptr)
	, m_pSelectView(nullptr)
	, m_iPickedTile(0)
{
}
CViewMgr::~CViewMgr()
{
	Release();
}

void CViewMgr::Initialize()
{
	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	m_pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	m_pSelectView = dynamic_cast<CSelectView*>(pMainFrm->m_MainSplitter.GetPane(0, 2));
	m_pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

}

void CViewMgr::All_Invalidate()
{
	m_pMiniView->Invalidate(FALSE);
	m_pSelectView->Invalidate(FALSE);
	m_pToolView->Invalidate(FALSE);
}

void CViewMgr::Release(void)
{
	
}
