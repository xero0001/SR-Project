#include "stdafx.h"
#include <string>
#include "..\Headers\Tiles.h"

CTiles::CTiles(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CTiles::CTiles(const CTiles & other)
	: CGameObject(other)
	, m_Tiles(other.m_Tiles)
	, m_Visibility(other.m_Visibility)
	, m_Lighting(other.m_Lighting)
{
}

HRESULT CTiles::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CTiles::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	/* Com_Buffer_Wall */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Stage,
		L"Component_VIBuffer_WallTexture",
		L"Com_Buffer_Wall",
		(CComponent**)&m_pVIBufferCom_Wall)))
		return E_FAIL;

	/* Com_Buffer_Floor */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Stage,
		L"Component_VIBuffer_FloorTexture",
		L"Com_Buffer_Floor",
		(CComponent**)&m_pVIBufferCom_Floor)))
		return E_FAIL;

	// 수동입력
	vector<_int> temp0(5, 1);
	vector<_int> temp1(5, 0);
	vector<_int> temp2(5, 0);
	vector<_int> temp3(5, 0);
	vector<_int> temp4(5, 1);

	temp1[0] = 1; temp1[2] = 1; temp1[4] = 1;
	temp2[0] = 1; temp2[2] = 1; temp2[4] = 1;
	temp3[0] = 1;				temp3[4] = 1;

	m_Tiles.push_back(temp0);
	m_Tiles.push_back(temp1);
	m_Tiles.push_back(temp2);
	m_Tiles.push_back(temp3);
	m_Tiles.push_back(temp4);

	temp0[0] = 2; temp0[1] = 3; temp0[2] = 2; temp0[3] = 0; temp0[4] = 0;
	temp1[0] = 3; temp1[1] = 3; temp1[2] = 3; temp1[3] = 0; temp1[4] = 0;
	temp2[0] = 2; temp2[1] = 3; temp2[2] = 2; temp2[3] = 0; temp2[4] = 0;
	temp3[0] = 1; temp3[1] = 2; temp3[2] = 1; temp3[3] = 0; temp3[4] = 0;
	temp4[0] = 0; temp4[1] = 1; temp4[2] = 1; temp4[3] = 0; temp4[4] = 0;

	m_Visibility.push_back(temp0);
	m_Visibility.push_back(temp1);
	m_Visibility.push_back(temp2);
	m_Visibility.push_back(temp3);
	m_Visibility.push_back(temp4);

	/* Com_Texture */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Stage,
		L"Component_Texture_Wall",
		L"Com_Texture_Wall",
		(CComponent**)&m_pTextureCom_Wall)))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Stage,
		L"Component_Texture_Floor",
		L"Com_Texture_Floor",
		(CComponent**)&m_pTextureCom_Floor)))
		return E_FAIL;

	return S_OK;
}

_uint CTiles::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	return _uint();
}

_uint CTiles::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return 0;

	if (FAILED(pManagement->Add_GameObjectToRenderList(ERenderID::NonAlpha, this)))
		return 0;

	return _uint();
}

HRESULT CTiles::Render_GameObject()
{


	for (_int i = 0; i < 5; ++i) {
		for (_int j = 0; j < 5; ++j) {
			D3DXMATRIX worldMat;
			D3DXMatrixTranslation(&worldMat, 1.f*j, 0.f, 1.f*i);
			if (FAILED(m_pDevice->SetTransform(D3DTS_WORLD, &worldMat)))
				return E_FAIL;

			if (m_Visibility[i][j] == 3) {
				if (FAILED(m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255))))
					return E_FAIL;
			}
			else if (m_Visibility[i][j] == 2) {
				if (FAILED(m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(128, 128, 128))))
					return E_FAIL;
			}
			else if (m_Visibility[i][j] == 1) {
				if (FAILED(m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(64, 64, 64))))
					return E_FAIL;
			}
			else {
				if (FAILED(m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(0, 0, 0))))
					return E_FAIL;
			}

			CGameObject::Render_GameObject();

			if (m_Tiles[i][j] == 0) {
				// 바닥 생성
				if (FAILED(m_pTextureCom_Floor->Set_Texture(0)))
					return E_FAIL;

				if (FAILED(m_pVIBufferCom_Floor->Render_Buffer()))
					return E_FAIL;
			}
			else if (m_Tiles[i][j] == 1) {
				// 벽 생성
				if (FAILED(m_pTextureCom_Wall->Set_Texture(0)))
					return E_FAIL;

				// Ambient
				if (FAILED(m_pVIBufferCom_Wall->Render_Buffer()))
					return E_FAIL;
			}
		}
	}

	return S_OK;
}

CTiles * CTiles::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTiles* pInstance = new CTiles(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CTiles");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTiles::Clone(void * pArg/* = nullptr*/)
{
	CTiles* pClone = new CTiles(*this);
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CTiles");
		Safe_Release(pClone);
	}

	return pClone;
}

void CTiles::Free()
{
	Safe_Release(m_pVIBufferCom_Wall);
	Safe_Release(m_pVIBufferCom_Floor);
	Safe_Release(m_pTextureCom_Wall);
	Safe_Release(m_pTextureCom_Floor);

	m_Tiles.clear();
	m_Visibility.clear();
	m_Lighting.clear();

	CGameObject::Free();
}
