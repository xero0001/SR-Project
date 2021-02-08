#pragma once
#ifndef __LOADING_H__

#include "Base.h"

USING(Engine)
class CLoading : public CBase
{
private:
	explicit CLoading(LPDIRECT3DDEVICE9 pDevice, ESceneType eNextSceneID);
	virtual ~CLoading() = default;

public:
	_bool IsFinished() const;

public:
	HRESULT Ready_Loading();
	HRESULT Ready_StageResources();

public:
	static CLoading* Create(LPDIRECT3DDEVICE9 pDevice, ESceneType eNextSceneID);
	static unsigned __stdcall ThreadMain(void* pArg);
	virtual void Free() override;


private:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	HANDLE m_hLoadingThread;
	ESceneType m_eNextSceneID;
	_bool m_IsFinished = false;
};

#define __LOADING_H__
#endif
