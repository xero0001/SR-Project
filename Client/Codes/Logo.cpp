#include "stdafx.h"
#include "..\Headers\Logo.h"
#include "Stage.h"
#include "Loading.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CLogo::Ready_Scene()
{
	if (FAILED(CScene::Ready_Scene()))
		return E_FAIL;

	m_pLoading = CLoading::Create(m_pDevice, ESceneType::Stage);
	if (nullptr == m_pLoading)
		return E_FAIL;

	return S_OK;
}

_uint CLogo::Update_Scene(_float fDeltaTime)
{
	CScene::Update_Scene(fDeltaTime);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000 &&
		m_pLoading->IsFinished())
	{
		CManagement* pManagement = CManagement::Get_Instance();
		if (nullptr == pManagement)
			return 0;

		if (FAILED(pManagement->SetUp_CurrentScene((_int)ESceneType::Stage, CStage::Create(m_pDevice))))
		{
			PRINT_LOG(L"Error", L"Failed To SetUp_CurrentScene To Stage");
			return NO_EVENT;
		}

		return CHANGE_SCENE;
	}

	return NO_EVENT;
}

_uint CLogo::LateUpdate_Scene(_float fDeltaTime)
{
	CScene::LateUpdate_Scene(fDeltaTime);

	return NO_EVENT;
}


CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo* pInstance = new CLogo(pDevice);
	if (FAILED(pInstance->Ready_Scene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Logo");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLogo::Free()
{
	Safe_Release(m_pLoading);

	CScene::Free();
}
