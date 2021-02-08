#pragma once
#ifndef __GAMEOBJECT_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);
	explicit CGameObject(const CGameObject& other);
	virtual ~CGameObject() = default;

public:
	const class CComponent* Get_Component(const wstring& ComponentTag) const;

public:
	virtual HRESULT Ready_GameObject_Prototype() = 0;
	virtual HRESULT Ready_GameObject(void* pArg = nullptr) = 0;
	virtual _uint Update_GameObject(_float fDeltaTime) = 0;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) = 0;
	virtual HRESULT Render_GameObject() = 0;

protected:
	HRESULT Add_Component(_uint iSceneIndex, const wstring& PrototypeTag, const wstring& ComponentTag, class CComponent** pOut, void* pArg = nullptr);

public:
	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	typedef unordered_map<wstring, class CComponent*>	COMPONENTS;	// 컴포넌트들의 복제본들을 보관.
	COMPONENTS	m_Components;

	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	_bool				m_IsClone = false;
};
END

#define __GAMEOBJECT_H__
#endif