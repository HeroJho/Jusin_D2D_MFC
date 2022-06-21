#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "TextureMgr.h"
#include "Device.h"



CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	InitializeCriticalSection(&m_Crt);

	//int	iHp = 0;

	m_hThread = (HANDLE)_beginthreadex(nullptr,		// 보안속성(핸들의 상속 여부, nullptr이면 상속에서 제외)
										0,			// 디폴트 스택 사이즈	
										CLogo::ImgLoadThreadFunc, // 쓰레드로 동작할 함수(__stdcall 방식)
										(LPVOID)this, // 쓰레드 함수의 전달하고자하는 매개 변수
										0,				// 쓰레드 생성 및 실행을 조절하기 위한 flag, 기본 값 0
										nullptr);		// 쓰레드 id반환(dword 타입의 주소)
	
	return S_OK;
}

void CLogo::Update_Scene()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		CSceneMgr::Get_Instance()->Change_SceneMgr(CSceneMgr::STAGE);
		return ;
	}
}

void CLogo::Late_Update_Scene()
{
	
}

void CLogo::Render_Scene()
{
	const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Logo");

	if (nullptr == pTexInfo)
		return;

	float		fX = pTexInfo->tImgInfo.Width / 2.f;
	float		fY = pTexInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, WINCX / 2.f, WINCY / 2.f, 0.f);

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fX, fY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	wstring	wstrFullPath = CTextureMgr::Get_Instance()->Get_String();

	D3DXMatrixTranslation(&matTrans, 50.f, 500.f, 0.f);
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);

	CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
		wstrFullPath.c_str(),
		wstrFullPath.length(),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 0, 0, 0));

}

void CLogo::Release_Scene()
{
	
}

size_t		__stdcall CLogo::ImgLoadThreadFunc(void* lpParam)
{
	CLogo*	pLogo = reinterpret_cast<CLogo*>(lpParam);

	EnterCriticalSection(&pLogo->Get_Crt());		// lock

	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/JusinLogo.png", TEX_SINGLE, L"Logo")))
	{
		ERR_MSG(L"Logo Image");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::Get_Instance()->ReadImgPath(L"../Data/ImgPath.txt")))
	{
		ERR_MSG(L"ImgPath Load failed");
		return E_FAIL;
	}

	CTextureMgr::Get_Instance()->Set_String(L"로딩완료");

	LeaveCriticalSection(&pLogo->Get_Crt());		// unlock

	return 0;
}
