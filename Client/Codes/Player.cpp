#include "stdafx.h"
#include "..\Headers\Player.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CPlayer::CPlayer(const CPlayer & other)
	: CGameObject(other)
{
}

HRESULT CPlayer::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CPlayer::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	/* Com_Buffer */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_RectTexture",
		L"Com_Buffer",
		(CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* Com_Transform */
	CTransform::TRANFORM_DESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANFORM_DESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotatePerSec = D3DXToRadian(90.f);
	TransformDesc.vScale = _float3(1.f, 1.f, 1.f);
	TransformDesc.vPosition = _float3(1.f, 0.5f, 1.f);

	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransformCom,
		&TransformDesc)))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_Texture_Player",
		L"Com_Texture",
		(CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

_uint CPlayer::Update_GameObject(_float fDeltaTime)
{
	CGameObject::Update_GameObject(fDeltaTime);

	if (FAILED(Movement(fDeltaTime)))
		return 0;

	m_pTransformCom->Update_Transform();

	return _uint();
}

_uint CPlayer::LateUpdate_GameObject(_float fDeltaTime)
{
	CGameObject::LateUpdate_GameObject(fDeltaTime);

	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return 0;

	if (FAILED(pManagement->Add_GameObjectToRenderList(ERenderID::NonAlpha, this)))
		return 0;

	return _uint();
}

HRESULT CPlayer::Render_GameObject()
{
	if (FAILED(m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransformCom->Get_TransformDesc().matWorld)))
		return E_FAIL;	

	CGameObject::Render_GameObject();

	if (FAILED(m_pTextureCom->Set_Texture(0)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(255, 255, 255))))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render_Buffer()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::Movement(_float fDeltaTime)
{
	if (GetAsyncKeyState('W') & 0x0001)
	{
		m_pTransformCom->Move_Up(fDeltaTime);
	}

	if (GetAsyncKeyState('S') & 0x0001)
	{
		m_pTransformCom->Move_Down(-fDeltaTime);
	}

	if (GetAsyncKeyState('D') & 0x0001)
	{
		m_pTransformCom->Move_Right(fDeltaTime);
	}

	if (GetAsyncKeyState('A') & 0x0001)
	{
		m_pTransformCom->Move_Left(-fDeltaTime);
	}

	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer* pInstance = new CPlayer(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Player");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CPlayer::Clone(void * pArg/* = nullptr*/)
{
	CPlayer* pClone = new CPlayer(*this);
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Player");
		Safe_Release(pClone);
	}

	return pClone;
}

void CPlayer::Free()
{
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);

	CGameObject::Free();
}
