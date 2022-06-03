#pragma once

#include "Include.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	~CDevice();

public:
	HRESULT				Initialize(void);
	void				Release(void);

	void				Render_Begin(void);
	void				Render_End(HWND hWnd = nullptr);
	
private:
	void				Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp);


private:
	LPDIRECT3D9			m_pSDK;	    // 사용하고자 하는 장치를 조사하고 해당 장치를 제어하는 객체를 생성하는 상위 객체
	// ㄴIDirect3D9의 포인터 typedef
	PDIRECT3DDEVICE9	m_pDevice;	// 그래픽 장치를 통한 렌더링을 제어하는 객체
	// ㄴIDirect3DDevice9의 포인터 typedef
};

