#pragma once
#ifndef __MAINCAMERA_H__

#include "Camera.h"

USING(Engine)
class CMainCamera final : public CCamera
{
private:
	explicit CMainCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CMainCamera(const CMainCamera& other);
	virtual ~CMainCamera() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject(_float fDeltaTime) override;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) override;
	virtual HRESULT Render_GameObject() override;

private:
	HRESULT Movement(_float fDeltaTime);

public:
	static CMainCamera* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	const CTransform* m_pTarget = nullptr;
	_float m_fDistanceToTarget = 5.f;
};

#define __MAINCAMERA_H__
#endif