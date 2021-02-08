#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"
#include "Player.h"

CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
{
}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(m_pManagement->Ready_Engine(g_hWnd, WINCX, WINCY, EDisplayMode::WinMode, (_uint)ESceneType::Max)))
	{
		PRINT_LOG(L"Error", L"Failed To Ready Engine");
		return E_FAIL;
	}

	m_pDevice = m_pManagement->Get_Device();
	if (nullptr == m_pDevice)
	{
		PRINT_LOG(L"Error", L"m_pDevice is null");
		return E_FAIL;
	}

	if (FAILED(m_pManagement->SetUp_CurrentScene((_int)ESceneType::Logo, CLogo::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To SetUp_CurrentScene To Logo");
		return E_FAIL;
	}

	if (FAILED(Ready_Default_Setting()))
		return E_FAIL;

	if (FAILED(Ready_StaticResources()))
		return E_FAIL;

	return S_OK;
}

_uint CMainApp::Update_MainApp()
{
	_uint iEvent = 0;

	if (iEvent = m_pManagement->Update_Engine())
		return iEvent;

	if (FAILED(m_pManagement->Render_Engine()))
		return 0;

	return _uint();
}

HRESULT CMainApp::Ready_Default_Setting()
{
	/* 조명 on */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE)))
		return E_FAIL;

	/* 머티리얼 세팅 */
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient.r = 1.f;
	mtrl.Ambient.g = 1.0f;
	mtrl.Ambient.b = 1.0f;
	mtrl.Ambient.a = 1.0f;

	if (FAILED(m_pDevice->SetMaterial(&mtrl)))
		return E_FAIL;
	
	/*
	D3DCULL_CW: Clock Wise. 시계 방향인 면을 추려낸다.
	D3DCULL_CCW: Counter Clock Wise. 반시계 방향인 면을 추려낸다. 기본값.
	D3DCULL_NONE: 후면 추려내기 안함.
	*/
	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
		return E_FAIL;	

	return S_OK;
}

HRESULT CMainApp::Ready_StaticResources()
{
#pragma region GameObjects
	/* For.GameObject_Player*/
	if (FAILED(m_pManagement->Add_GameObject_Prototype(
		(_uint)ESceneType::Static,
		L"GameObject_Player",
		CPlayer::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add GameObject_Player");
		return E_FAIL;
	}
#pragma endregion

#pragma region Components
	///* For.Component_VIBuffer_TriColor */
	//if (FAILED(m_pManagement->Add_Component_Prototype(
	//	(_uint)ESceneType::Static,
	//	L"Component_VIBuffer_TriColor",
	//	CVIBuffer_TriColor::Create(m_pDevice))))
	//{
	//	PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_TriColor");
	//	return E_FAIL;
	//}

	/* For.Component_VIBuffer_RectColor */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_RectColor",
		CVIBuffer_RectColor::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_TriColor");
		return E_FAIL;
	}

	/* For.Component_VIBuffer_RectTexture */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_RectTexture",
		CVIBuffer_RectTexture::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_VIBuffer_RectTexture");
		return E_FAIL;
	}

	/* For.Component_Transform */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_Transform",
		CTransform::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_Transform");
		return E_FAIL;
	}

	/* For.Component_Texture_Player */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_Texture_Player",
		CTexture::Create(m_pDevice, ETextureType::Auto, L"../Resources/Sprites/Player%d.png", 1))))
	{
		PRINT_LOG(L"Error", L"Failed To Add Component_Texture_Player");
		return E_FAIL;
	}
#pragma endregion
	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
	{
		PRINT_LOG(L"Error", L"Failed To Create MainApp");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	if (CManagement::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CManagement");
	}
}