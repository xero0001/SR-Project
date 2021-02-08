#pragma once
#ifndef __DEVICE_MANAGER_H__

#include "Base.h"

BEGIN(Engine)
class CDevice_Manager : public CBase
{
	DECLARE_SINGLETON(CDevice_Manager)

private:
	CDevice_Manager();
	virtual ~CDevice_Manager() = default;

public:
	LPDIRECT3DDEVICE9 Get_Device() const;

public:
	HRESULT Ready_Device(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplay);

public:
	virtual void Free() override;

private:
	LPDIRECT3D9			m_pSDK = nullptr;
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
};
END

#define __DEVICE_MANAGER_H__
#endif