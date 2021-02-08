#include "..\Headers\Texture.h"

USING(Engine)

CTexture::CTexture(
	LPDIRECT3DDEVICE9 pDevice,
	ETextureType eType,
	const TCHAR* pFilePath, 
	_size iCount)
	: CComponent(pDevice)
	, m_pFilePath(pFilePath)
	, m_iCount(iCount)
	, m_eType(eType)
{
}

CTexture::CTexture(const CTexture & other)
	: CComponent(other)
	, m_Textures(other.m_Textures)
	, m_iCount(other.m_iCount)
{
	for (auto& pTexture : m_Textures)
	{
		Safe_AddRef(pTexture);
	}
}

HRESULT CTexture::Ready_Component_Prototype()
{
	HRESULT hr = 0;
	TCHAR szFullPath[128] = L"";
	IDirect3DBaseTexture9* pTexture = nullptr;

	for (_size i = 0; i < m_iCount; ++i)
	{
		// m_pFilePath = L"../Resources/Monster%d.png";
		swprintf_s(szFullPath, m_pFilePath, i);

		switch (m_eType)
		{
		case ETextureType::Default:
			hr = D3DXCreateTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		case ETextureType::Cube:
			hr = D3DXCreateCubeTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		case ETextureType::Auto:
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(szFullPath, &info);

			hr = D3DXCreateTextureFromFileEx(m_pDevice, szFullPath, info.Width, info.Height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		default:
			break;
		}

		if (FAILED(hr))
			return E_FAIL;

		m_Textures.push_back(pTexture);
	}

	return S_OK;
}

HRESULT CTexture::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CTexture::Set_Texture(_size iIndex)
{
	if (m_Textures.size() <= iIndex)
		return E_FAIL;

	if (FAILED(m_pDevice->SetTexture(0, m_Textures[iIndex])))
		return E_FAIL;

	return S_OK;
}

CTexture * CTexture::Create(
	LPDIRECT3DDEVICE9 pDevice, 
	ETextureType eType,
	const TCHAR * pFilePath, 
	_size iCount)
{
	CTexture* pInstance = new CTexture(pDevice, eType, pFilePath, iCount);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTexture::Clone(void * pArg/* = nullptr*/)
{
	CTexture* pClone = new CTexture(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CTexture");
		Safe_Release(pClone);
	}

	return pClone;
}

void CTexture::Free()
{
	for (auto& pTexture : m_Textures)
	{
		Safe_Release(pTexture);
	}

	m_Textures.clear();

	CComponent::Free();
}
