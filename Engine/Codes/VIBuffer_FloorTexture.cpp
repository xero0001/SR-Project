#include "..\Headers\VIBuffer_FloorTexture.h"

USING(Engine)

CVIBuffer_FloorTexture::CVIBuffer_FloorTexture(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_FloorTexture::CVIBuffer_FloorTexture(const CVIBuffer_FloorTexture & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_FloorTexture::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_TEXTURE);
	m_iVertexCount = 4;
	m_iTriCount = 2;
	m_iFVF = FVF_TEXTURE;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFMT = D3DFMT_INDEX16;

	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;

	/*
	���ؽ����۰� ���� ���ؽ� ������ �����Ϸ��� �ݵ�� lock, unlock ���̿��� ����.
	lock�Լ��� ���ؼ� ���ؽ����۰� �����ִ� ���ؽ��迭�� �ּҸ� �� �� �ִ�.
	*/
	VTX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	// ���� ������ ����
	pVertices[0].vPosition = _float3(-0.5f, 0.f, 0.5f);
	pVertices[0].vUV = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.f, 0.5f);
	pVertices[1].vUV = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, 0.f, -0.5f);
	pVertices[2].vUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, 0.f, -0.5f);
	pVertices[3].vUV = _float2(0.f, 1.f);

	m_pVB->Unlock();

	INDEX16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_FloorTexture::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer_FloorTexture::Render_Buffer()
{
	if (FAILED(CVIBuffer::Render_Buffer()))
		return E_FAIL;

	/* ��ġ���� ������ ���ؽ��� �ε����� ������ ������ �׸��� �Լ� */
	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_FloorTexture * CVIBuffer_FloorTexture::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_FloorTexture* pInstance = new CVIBuffer_FloorTexture(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_FloorTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_FloorTexture::Clone(void * pArg/* = nullptr*/)
{
	CVIBuffer_FloorTexture* pClone = new CVIBuffer_FloorTexture(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_FloorTexture");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_FloorTexture::Free()
{
	CVIBuffer::Free();
}
