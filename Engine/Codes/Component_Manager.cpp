#include "..\Headers\Component_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CComponent_Manager)

CComponent_Manager::CComponent_Manager()
{
}

HRESULT CComponent_Manager::Ready_Component_Manager(_size iSceneCount)
{
	m_pComponents = new COMPONENTS[iSceneCount];
	m_iContainerSize = iSceneCount;

	return S_OK;
}

HRESULT CComponent_Manager::Add_Component_Prototype(
	_uint iSceneIndex, 
	const wstring & PrototypeTag, 
	CComponent * pPrototype)
{
	if (m_iContainerSize <= iSceneIndex)
		return E_FAIL;

	if (nullptr == pPrototype)
		return E_FAIL;

	auto iter_find = m_pComponents[iSceneIndex].find(PrototypeTag);
	if (m_pComponents[iSceneIndex].end() == iter_find)
	{
		//m_pComponents[iSceneIndex][PrototypeTag] = pPrototype;
		m_pComponents[iSceneIndex].insert(make_pair(PrototypeTag, pPrototype));
	}

	return S_OK;
}

CComponent * CComponent_Manager::Clone_Component(
	_uint iSceneIndex, 
	const wstring & PrototypeTag,
	void* pArg/* = nullptr*/)
{
	if (m_iContainerSize <= iSceneIndex)
		return nullptr;

	auto iter_find = m_pComponents[iSceneIndex].find(PrototypeTag);
	if (m_pComponents[iSceneIndex].end() == iter_find)
		return nullptr;

	return iter_find->second->Clone(pArg);
}

HRESULT CComponent_Manager::Clear_ForScene(_uint iSceneIndex)
{
	if (m_iContainerSize <= iSceneIndex)
		return E_FAIL;

	for (auto& MyPair : m_pComponents[iSceneIndex])
	{
		Safe_Release(MyPair.second);
	}

	m_pComponents[iSceneIndex].clear();

	return S_OK;
}

void CComponent_Manager::Free()
{
	for (_size i = 0; i < m_iContainerSize; ++i)
	{
		for (auto& MyPair : m_pComponents[i])
		{
			Safe_Release(MyPair.second);
		}

		m_pComponents[i].clear();
	}

	Safe_Delete_Array(m_pComponents);
}
