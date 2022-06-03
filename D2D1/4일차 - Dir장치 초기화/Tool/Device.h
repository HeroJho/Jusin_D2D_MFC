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
	LPDIRECT3D9			m_pSDK;	    // ����ϰ��� �ϴ� ��ġ�� �����ϰ� �ش� ��ġ�� �����ϴ� ��ü�� �����ϴ� ���� ��ü
	// ��IDirect3D9�� ������ typedef
	PDIRECT3DDEVICE9	m_pDevice;	// �׷��� ��ġ�� ���� �������� �����ϴ� ��ü
	// ��IDirect3DDevice9�� ������ typedef
};

