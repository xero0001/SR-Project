#pragma once
#ifndef __TILES_H__

#include "GameObject.h"

USING(Engine)
class CTiles : public CGameObject
{
private:
	explicit CTiles(LPDIRECT3DDEVICE9 pDevice);
	explicit CTiles(const CTiles& other);
	virtual ~CTiles() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual HRESULT Render_GameObject() override;

public:
	static CTiles* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	CVIBuffer*			 m_pVIBufferCom_Wall = nullptr;
	CVIBuffer*			 m_pVIBufferCom_Floor = nullptr;

	CTexture*			 m_pTextureCom_Wall = nullptr;
	CTexture*			 m_pTextureCom_Floor = nullptr;

	typedef vector<vector<_int>> MAPSTATE;
	MAPSTATE  m_Tiles;
	MAPSTATE  m_Visibility;
	MAPSTATE  m_Lighting;
};

#define __TILES_H__
#endif