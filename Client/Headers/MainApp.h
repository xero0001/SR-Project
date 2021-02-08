#pragma once
#ifndef __MAINAPP_H__

#include "Base.h"

USING(Engine)
class CMainApp : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT Ready_MainApp();
	_uint Update_MainApp();

private:
	HRESULT Ready_Default_Setting();
	HRESULT Ready_StaticResources();

public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	CManagement* m_pManagement = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;


};

#define __MAINAPP_H__
#endif

