#include "..\Headers\Scene_Manager.h"
#include "Scene.h"

USING(Engine)
IMPLEMENT_SINGLETON(CScene_Manager)

CScene_Manager::CScene_Manager()
{
}

HRESULT CScene_Manager::SetUp_CurrentScene(_int iSceneID, CScene* pNextScene)
{
	if (nullptr == pNextScene)
		return E_FAIL;

	if (m_iCurrentSceneID != iSceneID)
	{
		Safe_Release(m_pCurrentScene);
		m_pCurrentScene = pNextScene;
		m_iCurrentSceneID = iSceneID;
	}

	return S_OK;
}

_uint CScene_Manager::Update_Scene(_float fDeltaTime)
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->Update_Scene(fDeltaTime);
}

_uint CScene_Manager::LateUpdate_Scene(_float fDeltaTime)
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->LateUpdate_Scene(fDeltaTime);
}

void CScene_Manager::Free()
{
	Safe_Release(m_pCurrentScene);
}

