#include "..\Headers\GameObject_Manager.h"
#include "Layer.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGameObject_Manager)

CGameObject_Manager::CGameObject_Manager()
{
}

const CGameObject * CGameObject_Manager::Get_GameObject(
	_uint iSceneIndex,
	const wstring & LayerTag, 
	_size iIndex)
{
	if (nullptr == m_pLayers ||
		m_iContainerSize <= iSceneIndex)
		return nullptr;

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() == iter_find)
		return nullptr;

	return iter_find->second->Get_GameObject(iIndex);
}

const CComponent * CGameObject_Manager::Get_Component(
	_uint iSceneIndex, 
	const wstring & LayerTag, 
	const wstring & ComponentTag, 
	_size iIndex)
{
	const CGameObject* pObject = Get_GameObject(iSceneIndex, LayerTag, iIndex);
	if (nullptr == pObject)
		return nullptr;

	return pObject->Get_Component(ComponentTag);
}

HRESULT CGameObject_Manager::Ready_GameObject_Manager(_size iSceneCount)
{
	m_pGameObjects = new GAMEOBJECTS[iSceneCount];
	m_pLayers = new LAYERS[iSceneCount];
	m_iContainerSize = iSceneCount;

	return S_OK;
}

HRESULT CGameObject_Manager::Add_GameObject_Prototype(
	_uint iSceneIndex, 
	const wstring& PrototypeTag, 
	CGameObject * pPrototype)
{
	if (m_iContainerSize <= iSceneIndex)
		return E_FAIL;

	if (nullptr == pPrototype)
		return E_FAIL;

	auto iter_find = m_pGameObjects[iSceneIndex].find(PrototypeTag);
	if (m_pGameObjects[iSceneIndex].end() == iter_find)
	{
		//m_pGameObjects[iSceneIndex][PrototypeTag] = pPrototype;
		m_pGameObjects[iSceneIndex].insert(make_pair(PrototypeTag, pPrototype));
	}

	return S_OK;
}

HRESULT CGameObject_Manager::Add_GameObject_ToLayer(
	_uint iFromSceneIndex, 
	const wstring & PrototypeTag,
	_uint iToSceneIndex, 
	const wstring & LayerTag, 
	void * pArg)
{
	if (m_iContainerSize <= iFromSceneIndex ||
		m_iContainerSize <= iToSceneIndex)
		return E_FAIL;

	auto iter_find_Prototype = m_pGameObjects[iFromSceneIndex].find(PrototypeTag);
	if (m_pGameObjects[iFromSceneIndex].end() == iter_find_Prototype)
	{
		TCHAR szLogMessage[128] = L"";
		swprintf_s(szLogMessage, L"%s Prototype Not Found", PrototypeTag.c_str());
		PRINT_LOG(L"Error", szLogMessage);
		return E_FAIL;
	}

	CGameObject* pClone = iter_find_Prototype->second->Clone(pArg);
	if (nullptr == pClone)
		return E_FAIL;

	auto iter_find_Layer = m_pLayers[iToSceneIndex].find(LayerTag);
	if (m_pLayers[iToSceneIndex].end() == iter_find_Layer)
	{
		m_pLayers[iToSceneIndex].insert(make_pair(LayerTag, CLayer::Create()));
	}

	if (FAILED(m_pLayers[iToSceneIndex][LayerTag]->Add_GameObject(pClone)))
	{
		TCHAR szLogMessage[128] = L"";
		swprintf_s(szLogMessage, L"Failed To Add_GameObject In %s ", LayerTag.c_str());
		PRINT_LOG(L"Error", szLogMessage);
		return E_FAIL;
	}

	return S_OK;
}

_uint CGameObject_Manager::Update_GameObject(_float fDeltaTime)
{
	_uint iEvent = 0;

	for (_size i = 0; i < m_iContainerSize; ++i)
	{
		for (auto& MyPair : m_pLayers[i])
		{
			if (iEvent = MyPair.second->Update_GameObject(fDeltaTime))
				return iEvent;
		}
	}

	return _uint();
}

_uint CGameObject_Manager::LateUpdate_GameObject(_float fDeltaTime)
{
	_uint iEvent = 0;

	for (_size i = 0; i < m_iContainerSize; ++i)
	{
		for (auto& MyPair : m_pLayers[i])
		{
			if (iEvent = MyPair.second->LateUpdate_GameObject(fDeltaTime))
				return iEvent;
		}
	}

	return _uint();
}

HRESULT CGameObject_Manager::Clear_ForScene(_uint iSceneIndex)
{
	if (m_iContainerSize <= iSceneIndex)
		return E_FAIL;

	for (auto& MyPair : m_pGameObjects[iSceneIndex])
	{
		Safe_Release(MyPair.second);
	}

	for (auto& MyPair : m_pLayers[iSceneIndex])
	{
		Safe_Release(MyPair.second);
	}

	m_pGameObjects[iSceneIndex].clear();
	m_pLayers[iSceneIndex].clear();

	return S_OK;
}

void CGameObject_Manager::Free()
{
	for (_size i = 0; i < m_iContainerSize; ++i)
	{
		for (auto& MyPair : m_pGameObjects[i])
		{
			Safe_Release(MyPair.second);
		}

		m_pGameObjects[i].clear();
	}

	for (_size i = 0; i < m_iContainerSize; ++i)
	{
		for (auto& MyPair : m_pLayers[i])
		{
			Safe_Release(MyPair.second);
		}

		m_pLayers[i].clear();
	}

	Safe_Delete_Array(m_pGameObjects);
	Safe_Delete_Array(m_pLayers);
}
