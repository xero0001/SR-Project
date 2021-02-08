#pragma once
#ifndef __LAYER_H__

#include "Base.h"

BEGIN(Engine)
class CLayer : public CBase
{
public:
	CLayer();
	virtual ~CLayer() = default;

public:
	const class CGameObject* Get_GameObject(_size iIndex = 0);

public:
	HRESULT Add_GameObject(class CGameObject* pGameObject);
	_uint Update_GameObject(_float fDeltaTime);
	_uint LateUpdate_GameObject(_float fDeltaTime);

public:
	static CLayer* Create();
	virtual void Free() override;

private:
	typedef list<class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	// 오브젝트들의 복제본들을 보관.
};
END

#define __LAYER_H__
#endif