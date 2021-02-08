#include "..\Headers\Layer.h"
#include "GameObject.h"

USING(Engine)

CLayer::CLayer()
{
}

const CGameObject * CLayer::Get_GameObject(_size iIndex)
{
	if (m_GameObjects.size() <= iIndex)
		return nullptr;

	auto iter = m_GameObjects.begin();
	if (m_GameObjects.end() == iter)
		return nullptr;

	for (_size i = 0; i < iIndex; ++i, ++iter);		

	return *iter;
}

HRESULT CLayer::Add_GameObject(CGameObject* pGameObject)
{
	auto iter_find = find(m_GameObjects.begin(), m_GameObjects.end(), pGameObject);
	if (m_GameObjects.end() == iter_find)
	{
		m_GameObjects.push_back(pGameObject);
	}

	return S_OK;
}

_uint CLayer::Update_GameObject(_float fDeltaTime)
{
	_uint iEvent = 0;

	for (auto& pGameObject : m_GameObjects)
	{
		if (iEvent = pGameObject->Update_GameObject(fDeltaTime))
			return iEvent;
	}

	return _uint();
}

_uint CLayer::LateUpdate_GameObject(_float fDeltaTime)
{
	_uint iEvent = 0;

	for (auto& pGameObject : m_GameObjects)
	{
		if (iEvent = pGameObject->LateUpdate_GameObject(fDeltaTime))
			return iEvent;
	}

	return _uint();
}

CLayer * CLayer::Create()
{
	return new CLayer;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
	{
		Safe_Release(pGameObject);
	}

	m_GameObjects.clear();
}
