#include "..\Headers\Transform.h"

USING(Engine)

CTransform::CTransform(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
	ZeroMemory(&m_Desc, sizeof(TRANFORM_DESC));
	m_Desc.vScale = _float3(1.f, 1.f, 1.f);
}

CTransform::CTransform(const CTransform & other)
	: CComponent(other)
	, m_Desc(other.m_Desc)
{
}

const CTransform::TRANFORM_DESC & CTransform::Get_TransformDesc() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_Desc;
}

HRESULT CTransform::Ready_Component_Prototype()
{
	return S_OK;
}

HRESULT CTransform::Ready_Component(void * pArg/* = nullptr*/)
{
	if (pArg)
	{
		memcpy(&m_Desc, pArg, sizeof(TRANFORM_DESC));
	}

	return S_OK;
}

HRESULT CTransform::Update_Transform()
{
	_float4x4 matScale, matRotX, matRotY, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, m_Desc.vScale.x, m_Desc.vScale.y, m_Desc.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_Desc.vRotate.x);
	D3DXMatrixRotationY(&matRotY, m_Desc.vRotate.y);
	D3DXMatrixRotationZ(&matRotZ, m_Desc.vRotate.z);
	D3DXMatrixTranslation(&matTrans, m_Desc.vPosition.x, m_Desc.vPosition.y, m_Desc.vPosition.z);
	
	m_Desc.matWorld = matScale * matRotX * matRotY * matRotZ * matTrans;

	return S_OK;
}

void CTransform::Move_Up(_float fDeltaTime)
{
	m_Desc.vPosition.z += 1.0f;
}

void CTransform::Move_Down(_float fDeltaTime)
{
	m_Desc.vPosition.z -= 1.0f;
}


void CTransform::Move_Right(_float fDeltaTime)
{
	m_Desc.vPosition.x += 1.0f;
}

void CTransform::Move_Left(_float fDeltaTime)
{
	m_Desc.vPosition.x -= 1.0f;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTransform* pInstance = new CTransform(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Transform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone(void * pArg/* = nullptr*/)
{
	CTransform* pClone = new CTransform(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone Transform");
		Safe_Release(pClone);
	}

	return pClone;
}

void CTransform::Free()
{
	CComponent::Free();
}
