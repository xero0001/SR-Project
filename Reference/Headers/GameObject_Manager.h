#pragma once
#ifndef __GAMEOBJECT_MANAGER_H__

#include "Base.h"

BEGIN(Engine)
class CGameObject_Manager : public CBase
{
	DECLARE_SINGLETON(CGameObject_Manager)

private:
	CGameObject_Manager();
	virtual ~CGameObject_Manager() = default;

public:
	const class CGameObject* Get_GameObject(_uint iSceneIndex, const wstring& LayerTag, _size iIndex = 0);
	const class CComponent* Get_Component(_uint iSceneIndex, const wstring& LayerTag, const wstring& ComponentTag, _size iIndex = 0);

public:
	HRESULT Ready_GameObject_Manager(_size iSceneCount);
	HRESULT Add_GameObject_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject_ToLayer(_uint iFromSceneIndex, const wstring& PrototypeTag, _uint iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);
	_uint Update_GameObject(_float fDeltaTime);
	_uint LateUpdate_GameObject(_float fDeltaTime);
	HRESULT Clear_ForScene(_uint iSceneIndex);

public:
	virtual void Free() override;

private:
	// 게임 오브젝트들의 원형들을 보관.
	typedef unordered_map<wstring, class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS*	m_pGameObjects = nullptr; // 동적배열	

	// 레이어
	typedef unordered_map<wstring, class CLayer*>	LAYERS;
	LAYERS*			m_pLayers = nullptr; // 동적배열

	_size			m_iContainerSize = 0;
};
END

#define __GAMEOBJECT_MANAGER_H__
#endif