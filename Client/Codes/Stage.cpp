#include "stdafx.h"
#include "..\Headers\Stage.h"
#include "Camera.h"

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CScene::Ready_Scene()))
		return E_FAIL;	

	if (FAILED(Add_Player_Layer(L"Layer_Player")))
		return E_FAIL;

	if (FAILED(Add_Tiles_Layer(L"Layer_Tiles")))
		return E_FAIL;

	if (FAILED(Add_Camera_Layer(L"Layer_Camera")))
		return E_FAIL;

	// D3DXPLANE: 평면의 정보(a, b, c, d)를 담아낸 구조체
	//D3DXPlaneFromPoints(): 현재 평면의 정보(a, b, c, d)를 반환하는 함수.

	return S_OK;
}

_uint CStage::Update_Scene(_float fDeltaTime)
{
	CScene::Update_Scene(fDeltaTime);

	return NO_EVENT;
}

_uint CStage::LateUpdate_Scene(_float fDeltaTime)
{
	CScene::LateUpdate_Scene(fDeltaTime);

	return NO_EVENT;
}

HRESULT CStage::Add_Player_Layer(const wstring & LayerTag)
{
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	if (FAILED(pManagement->Add_GameObject_ToLayer(
		(_uint)ESceneType::Static,
		L"GameObject_Player",
		(_uint)ESceneType::Stage,
		LayerTag)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CStage::Add_Tiles_Layer(const wstring & LayerTag)
{
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	if (FAILED(pManagement->Add_GameObject_ToLayer(
		(_uint)ESceneType::Stage,
		L"GameObject_Tiles",
		(_uint)ESceneType::Stage,
		LayerTag)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CStage::Add_Camera_Layer(const wstring & LayerTag)
{
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	CCamera::CAMERA_DESC CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERA_DESC));

	CameraDesc.vUp = _float3(0.f, 1.f, 0.f);
	CameraDesc.fFovY = D3DXToRadian(90.f);
	CameraDesc.fAspect = (_float)WINCX / WINCY;
	CameraDesc.fNear = 1.f;
	CameraDesc.fFar = 1000.f;

	if (FAILED(pManagement->Add_GameObject_ToLayer(
		(_uint)ESceneType::Stage,
		L"GameObject_MainCamera",
		(_uint)ESceneType::Stage,
		LayerTag,
		&CameraDesc)))
	{
		return E_FAIL;
	}

	return S_OK;
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage* pInstance = new CStage(pDevice);
	if (FAILED(pInstance->Ready_Scene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CStage");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStage::Free()
{
	CScene::Free();
}

