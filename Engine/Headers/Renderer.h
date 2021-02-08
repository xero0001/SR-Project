#pragma once
#ifndef __RENDERER_H__
#include "Base.h"

BEGIN(Engine)
class CRenderer : public CBase
{
private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CRenderer() = default;

public:
	HRESULT Add_GameObjectToRenderList(ERenderID eRenderID, class CGameObject* pGameObject);
	HRESULT Render();

private:
	HRESULT Render_Priority();
	HRESULT Render_NonAlpha();
	HRESULT Render_Alpha();
	HRESULT Render_UI();

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

	typedef list<class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_RenderList[(_uint)ERenderID::Max];
};
END

#define __RENDERER_H__
#endif