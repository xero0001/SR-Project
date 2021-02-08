#pragma once
#ifndef __TRANSFORM_H__

#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CTransform final : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		_float3 vScale, vRotate, vPosition;
		_float fSpeedPerSec = 0.f, fRotatePerSec = 0.f;
		_float4x4 matWorld;
	}TRANFORM_DESC;

private:
	explicit CTransform(LPDIRECT3DDEVICE9 pDevice);
	explicit CTransform(const CTransform& other);
	virtual ~CTransform() = default;

public:
	const TRANFORM_DESC& Get_TransformDesc() const;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;

public:
	HRESULT Update_Transform();
	void Move_Up(_float fDeltaTime);
	void Move_Down(_float fDeltaTime);
	void Move_Left(_float fDeltaTime);
	void Move_Right(_float fDeltaTime);

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	TRANFORM_DESC	m_Desc;
};
END

#define __TRANSFORM_H__
#endif