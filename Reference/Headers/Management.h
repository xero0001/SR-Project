#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Device_Manager.h"
#include "Renderer.h"
#include "Scene_Manager.h"
#include "GameObject_Manager.h"
#include "Component_Manager.h"
#include "Time_Manager.h"

BEGIN(Engine)
class ENGINE_DLL CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	virtual ~CManagement() = default;

public: /* For.General */
	HRESULT Ready_Engine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplay, _uint iSceneCount);
	_uint Update_Engine();
	HRESULT Render_Engine();
	HRESULT Clear_ForScene(_uint iSceneIndex);


public:	/* For.Device Manager */
	LPDIRECT3DDEVICE9 Get_Device() const;

public: /* For.Scene Manager */
	HRESULT SetUp_CurrentScene(_int iSceneID, class CScene* pNextScene);

public: /* For.Renderer */
	HRESULT Add_GameObjectToRenderList(ERenderID eRenderID, class CGameObject* pGameObject);

public: /* For.GameObject Manager */	
	const class CGameObject* Get_GameObject(_uint iSceneIndex, const wstring& LayerTag, _size iIndex = 0);
	const class CComponent* Get_Component(_uint iSceneIndex, const wstring& LayerTag, const wstring& ComponentTag, _size iIndex = 0);
	HRESULT Add_GameObject_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject_ToLayer(_uint iFromSceneIndex, const wstring& PrototypeTag, _uint iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);

public: /* For.Component Manager */	
	HRESULT Add_Component_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iSceneIndex, const wstring& PrototypeTag, void* pArg = nullptr);	

public: /* For.Time_Manager */
	_float Get_DeltaTime() const;

public:
	virtual void Free() override;

private:
	CDevice_Manager*		m_pDevice_Manager = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CScene_Manager*			m_pScene_Manager = nullptr;
	CGameObject_Manager*	m_pGameObject_Manager = nullptr;
	CComponent_Manager*		m_pComponent_Manager = nullptr;
	CTime_Manager*			m_pTime_Manager = nullptr;
};
END

#define __MANAGEMENT_H__
#endif
