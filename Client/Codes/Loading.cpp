#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "MainCamera.h"
#include "Tiles.h"


CLoading::CLoading(LPDIRECT3DDEVICE9 pDevice, ESceneType eNextSceneID)
	: m_pDevice(pDevice)
	, m_eNextSceneID(eNextSceneID)
{
	Safe_AddRef(m_pDevice);
}

_bool CLoading::IsFinished() const
{
	/*DWORD dwResult = 0;
	GetExitCodeThread(m_hLoadingThread, &dwResult);*/

	return m_IsFinished;
}

HRESULT CLoading::Ready_Loading()
{	
	m_hLoadingThread = (HANDLE)_beginthreadex(0, 0, ThreadMain, this, 0, 0);
	if (nullptr == m_hLoadingThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoading::Ready_StageResources()
{
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

#pragma region GameObjects
	/* For.GameObject_Tiles */
	if (FAILED(pManagement->Add_GameObject_Prototype(
		(_uint)ESceneType::Stage,
		L"GameObject_Tiles",
		CTiles::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add GameObject_Tiles");
		return E_FAIL;
	}

	/* For.GameObject_MainCamera */
	if (FAILED(pManagement->Add_GameObject_Prototype(
		(_uint)ESceneType::Stage,
		L"GameObject_MainCamera",
		CMainCamera::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add GameObject_MainCamera");
		return E_FAIL;
	}
#pragma endregion

#pragma region Components
	/* For.Component_VIBuffer_WallTexture */
	if (FAILED(pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Stage,
		L"Component_VIBuffer_WallTexture",
		CVIBuffer_WallTexture::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_WallTexture");
		return E_FAIL;
	}

	/* For.Component_VIBuffer_FloorTexture */
	if (FAILED(pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Stage,
		L"Component_VIBuffer_FloorTexture",
		CVIBuffer_FloorTexture::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_FloorTexture");
		return E_FAIL;
	}

	/* For.Component_Texture_Wall */
	if (FAILED(pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Stage,
		L"Component_Texture_Wall",
		CTexture::Create(m_pDevice, ETextureType::Auto, L"../Resources/Tiles/Wall%d.png", 1))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_Texture_Cube");
		return E_FAIL;
	}

	/* For.Component_Texture_Floor */
	if (FAILED(pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Stage,
		L"Component_Texture_Floor",
		CTexture::Create(m_pDevice, ETextureType::Auto, L"../Resources/Tiles/Floor%d.png", 1))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_Texture_Floor");
		return E_FAIL;
	}

	/* For.Component_VIBuffer_TerrainTexture */
	//if (FAILED(pManagement->Add_Component_Prototype(
	//	(_uint)ESceneType::Stage,
	//	L"Component_VIBuffer_TerrainTexture",
	//	CVIBuffer_TerrainTexture::Create(m_pDevice, 129, 129))))
	//{
	//	PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_TerrainTexture");
	//	return E_FAIL;
	//}

	/* For.Component_Texture_Terrain */
	//if (FAILED(pManagement->Add_Component_Prototype(
	//	(_uint)ESceneType::Stage,
	//	L"Component_Texture_Terrain",
	//	CTexture::Create(m_pDevice, ETextureType::Default, L"../Resources/Terrain/Terrain%d.png", 1))))
	//{
	//	PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_TerrainTexture");
	//	return E_FAIL;
	//}

#pragma endregion	

	return S_OK;
}

CLoading * CLoading::Create(LPDIRECT3DDEVICE9 pDevice, ESceneType eNextSceneID)
{
	CLoading* pInstance = new CLoading(pDevice, eNextSceneID);
	if (FAILED(pInstance->Ready_Loading()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

unsigned CLoading::ThreadMain(void * pArg)
{
	auto pLoading = (CLoading*)pArg;
	if (nullptr == pLoading)
		return 0;

	HRESULT hr = 0;

	switch (pLoading->m_eNextSceneID)
	{
	case ESceneType::Static:
		break;
	case ESceneType::Logo:
		break;
	case ESceneType::Menu:
		break;
	case ESceneType::Stage:
		hr = pLoading->Ready_StageResources();
		break;
	default:
		break;
	}

	if (FAILED(hr))
	{
		return 0;
	}

	pLoading->m_IsFinished = true;

	return 0;
}

void CLoading::Free()
{
	Safe_Release(m_pDevice);
	CloseHandle(m_hLoadingThread);
}
