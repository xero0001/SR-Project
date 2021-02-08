#include "stdafx.h"
#include "..\Headers\MainCamera.h"


CMainCamera::CMainCamera(LPDIRECT3DDEVICE9 pDevice)
	: CCamera(pDevice)
{
}

CMainCamera::CMainCamera(const CMainCamera & other)
	: CCamera(other)
{
}

HRESULT CMainCamera::Ready_GameObject_Prototype()
{
	if (FAILED(CCamera::Ready_GameObject_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainCamera::Ready_GameObject(void * pArg)
{
	if (FAILED(CCamera::Ready_GameObject(pArg)))
		return E_FAIL;

	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	m_pTarget = (const CTransform*)pManagement->Get_Component((_uint)ESceneType::Stage, L"Layer_Player", L"Com_Transform");
	if (nullptr == m_pTarget)
		return E_FAIL;

	//Safe_AddRef(m_pTarget);

	return S_OK;
}

_uint CMainCamera::Update_GameObject(_float fDeltaTime)
{
	if (FAILED(Movement(fDeltaTime)))
		return 0;

	return CCamera::Update_GameObject(fDeltaTime);
}

_uint CMainCamera::LateUpdate_GameObject(_float fDeltaTime)
{
	CCamera::LateUpdate_GameObject(fDeltaTime);

	return _uint();
}

HRESULT CMainCamera::Render_GameObject()
{
	if (FAILED(CCamera::Render_GameObject()))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainCamera::Movement(_float fDeltaTime)
{
	if (GetAsyncKeyState(VK_ADD) & 0x8000)
	{
		m_fDistanceToTarget -= 10.f * fDeltaTime;
	}

	if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
	{
		m_fDistanceToTarget += 10.f * fDeltaTime;
	}


	if (m_pTarget)
	{
		CTransform::TRANFORM_DESC Desc = m_pTarget->Get_TransformDesc();

		m_Desc.vAt = Desc.vPosition;

		_float3 vTargetLook;
		memcpy(&vTargetLook, &Desc.matWorld.m[2][0], sizeof(_float3));
		D3DXVec3Normalize(&vTargetLook, &vTargetLook);

		_float3 vInvLook = vTargetLook * -m_fDistanceToTarget;

		_float3 vTargetRight;
		memcpy(&vTargetRight, &Desc.matWorld.m[0][0], sizeof(_float3));
		D3DXVec3Normalize(&vTargetRight, &vTargetRight);

		/* 임의의 축 회전 */
		_float4x4 matRot;
		D3DXMatrixRotationAxis(&matRot, &vTargetRight, D3DXToRadian(45.f));
		D3DXVec3TransformNormal(&vInvLook, &vInvLook, &matRot);

		m_Desc.vEye = vInvLook + Desc.vPosition;		
	}

	return S_OK;
}

CMainCamera * CMainCamera::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CMainCamera* pInstance = new CMainCamera(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create MainCamera");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CMainCamera::Clone(void * pArg /*= nullptr*/)
{
	CMainCamera* pClone = new CMainCamera(*this);
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone MainCamera");
		Safe_Release(pClone);
	}

	return pClone;
}

void CMainCamera::Free()
{
	CCamera::Free();
}
