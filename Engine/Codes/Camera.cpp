#include "..\Headers\Camera.h"

USING(Engine)

CCamera::CCamera(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
	ZeroMemory(&m_Desc, sizeof(CAMERA_DESC));
}

CCamera::CCamera(const CCamera & other)
	: CGameObject(other)
	, m_Desc(other.m_Desc)
{
}

HRESULT CCamera::Ready_GameObject_Prototype()
{
	if (FAILED(CGameObject::Ready_GameObject_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera::Ready_GameObject(void * pArg/* = nullptr*/)
{
	if (FAILED(CGameObject::Ready_GameObject(pArg)))
		return E_FAIL;

	if (pArg)
	{
		memcpy(&m_Desc, pArg, sizeof(CAMERA_DESC));
	}

	return S_OK;
}

_uint CCamera::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	D3DXMatrixLookAtLH(&m_Desc.matView, &m_Desc.vEye, &m_Desc.vAt, &m_Desc.vUp);
	D3DXMatrixPerspectiveFovLH(&m_Desc.matProj, m_Desc.fFovY, m_Desc.fAspect, m_Desc.fNear, m_Desc.fFar);

	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &m_Desc.matView)))
		return 0;
	if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &m_Desc.matProj)))
		return 0;

	return _uint();
}

_uint CCamera::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	return _uint();
}

HRESULT CCamera::Render_GameObject()
{
	if (FAILED(CGameObject::Render_GameObject()))
		return E_FAIL;

	return S_OK;
}

void CCamera::Free()
{
	CGameObject::Free();
}
