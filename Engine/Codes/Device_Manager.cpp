#include "..\Headers\Device_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDevice_Manager)

CDevice_Manager::CDevice_Manager()
{
}

LPDIRECT3DDEVICE9 CDevice_Manager::Get_Device() const
{
	return m_pDevice;
}

HRESULT CDevice_Manager::Ready_Device(
	HWND hWnd, 
	_uint iWinCX, 
	_uint iWinCY, 
	EDisplayMode eDisplay)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (nullptr == m_pSDK)
	{
		PRINT_LOG(L"Error", L"Failed To Direct3DCreate9");
		return E_FAIL;
	}

	D3DCAPS9 d3dcaps9;
	ZeroMemory(&d3dcaps9, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps9)))
	{
		PRINT_LOG(L"Error", L"Failed To GetDeviceCaps");
		return E_FAIL;
	}

	_uint vp = 0;
	if (d3dcaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = (BOOL)eDisplay;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &m_pDevice)))
	{
		PRINT_LOG(L"Error", L"Failed To CreateDevice");
		return E_FAIL;
	}

	return S_OK;
}

void CDevice_Manager::Free()
{
	if (Safe_Release(m_pDevice))
	{
		PRINT_LOG(L"Warning", L"Failed To Release m_pDevice");
	}

	if (Safe_Release(m_pSDK))
	{
		PRINT_LOG(L"Warning", L"Failed To Release m_pSDK");
	}
}
