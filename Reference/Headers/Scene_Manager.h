#pragma once
#include "Base.h"

#ifndef __SCENE_MANAGER_H__

BEGIN(Engine)
class CScene_Manager : public CBase
{
	DECLARE_SINGLETON(CScene_Manager)

private:
	CScene_Manager();
	virtual ~CScene_Manager() = default;

public:
	HRESULT SetUp_CurrentScene(_int iSceneID, class CScene* pNextScene);
	_uint Update_Scene(_float fDeltaTime);
	_uint LateUpdate_Scene(_float fDeltaTime);

public:
	virtual void Free() override;

private:
	class CScene*	m_pCurrentScene = nullptr;
	_int			m_iCurrentSceneID = -1;
};
END

#define __SCENE_MANAGER_H__
#endif

