#include "..\Headers\VIBuffer_WallTexture.h"

USING(Engine)

CVIBuffer_WallTexture::CVIBuffer_WallTexture(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_WallTexture::CVIBuffer_WallTexture(const CVIBuffer_WallTexture & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_WallTexture::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_TEXTURE);
	m_iVertexCount = 12;
	m_iTriCount = 8;
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
	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[0].vUV = _float2(0.f, (_float)8 / 13);

	pVertices[1].vPosition = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[1].vUV = _float2(1.f, (_float)8 / 13);

	pVertices[2].vPosition = _float3(-0.5f, 0.f, -0.5f);
	pVertices[2].vUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, 0.f, 0.5f);
	pVertices[3].vUV = _float2(0.f, 1.f);

	pVertices[4].vPosition = _float3(0.5f, 0.5f, -0.5f);
	pVertices[4].vUV = _float2(2.f, (_float)8 / 13);

	pVertices[5].vPosition = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vUV = _float2(3.f, (_float)8 / 13);

	pVertices[6].vPosition = _float3(0.5f, 0.f, 0.5f);
	pVertices[6].vUV = _float2(3.f, 1.f);

	pVertices[7].vPosition = _float3(0.5f, 0.f, -0.5f);
	pVertices[7].vUV = _float2(2.f, 1.f);

	pVertices[8].vPosition = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[8].vUV = _float2(0.f, 0.f);

	pVertices[9].vPosition = _float3(0.5f, 0.5f, 0.5f);
	pVertices[9].vUV = _float2(1.f, 0.f);

	pVertices[10].vPosition = _float3(0.5f, 0.5f, -0.5f);
	pVertices[10].vUV = _float2(1.f, (_float)8 / 13);

	pVertices[11].vPosition = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[11].vUV = _float2(0.f, (_float)8 / 13);

	m_pVB->Unlock();

	INDEX16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	pIndices[2]._1 = 1;
	pIndices[2]._2 = 4;
	pIndices[2]._3 = 7;

	pIndices[3]._1 = 1;
	pIndices[3]._2 = 7;
	pIndices[3]._3 = 2;

	pIndices[4]._1 = 4;
	pIndices[4]._2 = 5;
	pIndices[4]._3 = 6;

	pIndices[5]._1 = 4;
	pIndices[5]._2 = 6;
	pIndices[5]._3 = 7;

	pIndices[6]._1 = 8;
	pIndices[6]._2 = 9;
	pIndices[6]._3 = 10;

	pIndices[7]._1 = 8;
	pIndices[7]._2 = 10;
	pIndices[7]._3 = 11;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_WallTexture::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer_WallTexture::Render_Buffer()
{
	if (FAILED(CVIBuffer::Render_Buffer()))
		return E_FAIL;

	/* ��ġ���� ������ ���ؽ��� �ε����� ������ ������ �׸��� �Լ� */
	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_WallTexture * CVIBuffer_WallTexture::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_WallTexture* pInstance = new CVIBuffer_WallTexture(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_WallTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_WallTexture::Clone(void * pArg/* = nullptr*/)
{
	CVIBuffer_WallTexture* pClone = new CVIBuffer_WallTexture(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_WallTexture");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_WallTexture::Free()
{
	CVIBuffer::Free();
}
