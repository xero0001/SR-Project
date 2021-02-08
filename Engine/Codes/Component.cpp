#include "..\Headers\Component.h"

USING(Engine)

CComponent::CComponent(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

CComponent::CComponent(const CComponent & other)
	: m_IsClone(true)
	, m_pDevice(other.m_pDevice)
{
	Safe_AddRef(m_pDevice);
}

/* ������Ÿ�� �ʱ�ȭ */
HRESULT CComponent::Ready_Component_Prototype()
{
	return S_OK;
}

/* Ŭ�� �ʱ�ȭ */
HRESULT CComponent::Ready_Component(void* pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	Safe_Release(m_pDevice);
}
