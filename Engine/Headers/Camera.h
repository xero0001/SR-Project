#pragma once
#ifndef __CAMERA_H__

#include "GameObject.h"

BEGIN(Engine)
class ENGINE_DLL CCamera abstract :	public CGameObject
{
public:
	typedef struct tagCameraDesc
	{
		_float4x4 matView, matProj;
		_float3 vEye, vAt, vUp;
		_float fFovY, fAspect, fNear, fFar;
	}CAMERA_DESC;

protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CCamera(const CCamera& other);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() = 0;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) = 0;
	virtual _uint Update_GameObject(_float fDeltaTime) = 0;
	virtual _uint LateUpdate_GameObject(_float fDeltaTime) = 0;
	virtual HRESULT Render_GameObject() = 0;

public:	
	//virtual CGameObject * Clone(void * pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	CAMERA_DESC	m_Desc;
};
END

#define __CAMERA_H__
#endif