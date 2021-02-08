#pragma once
#ifndef __STAGE_H__

#include "Scene.h"

USING(Engine)
class CStage : public CScene
{
private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStage() = default;

public:
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(_float fDeltaTime) override;
	virtual _uint LateUpdate_Scene(_float fDeltaTime) override;

private:
	HRESULT Add_Player_Layer(const wstring& LayerTag);
	HRESULT Add_Tiles_Layer(const wstring& LayerTag);
	HRESULT Add_Camera_Layer(const wstring& LayerTag);

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

	
};

#define __STAGE_H__
#endif