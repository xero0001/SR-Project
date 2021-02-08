#include "..\Headers\GameObject.h"
#include "Management.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject & other)
	: m_IsClone(true)
	, m_pDevice(other.m_pDevice)
{
	Safe_AddRef(m_pDevice);
}

const CComponent * CGameObject::Get_Component(const wstring & ComponentTag) const
{
	auto iter_find = m_Components.find(ComponentTag);
	if (m_Components.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

HRESULT CGameObject::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Ready_GameObject(void * pArg)
{
	return S_OK;
}

_uint CGameObject::Update_GameObject(_float fDeltaTime)
{
	return _uint();
}

_uint CGameObject::LateUpdate_GameObject(_float fDeltaTime)
{
	return _uint();
}

HRESULT CGameObject::Render_GameObject()
{
	return S_OK;
}

HRESULT CGameObject::Add_Component(
	_uint iSceneIndex, 
	const wstring& PrototypeTag, 
	const wstring& ComponentTag, 
	class CComponent** pOut, 
	void* pArg/* = nullptr*/)
{
	auto iter_find = m_Components.find(ComponentTag);
	if (m_Components.end() == iter_find)
	{
		CManagement* pManagement = CManagement::Get_Instance();
		if (nullptr == pManagement)
			return E_FAIL;

		CComponent* pClone = pManagement->Clone_Component(iSceneIndex, PrototypeTag, pArg);
		if (nullptr == pClone)
			return E_FAIL;

		if (pOut)
		{
			*pOut = pClone;
			Safe_AddRef(pClone);
		}

		m_Components.insert(make_pair(ComponentTag, pClone));
	}	

	return S_OK;
}

void CGameObject::Free()
{
	for (auto& MyPair : m_Components)
	{
		Safe_Release(MyPair.second);
	}

	m_Components.clear();

	Safe_Release(m_pDevice);
}
