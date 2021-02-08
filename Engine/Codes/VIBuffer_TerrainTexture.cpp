#include "..\Headers\VIBuffer_TerrainTexture.h"

USING(Engine)

CVIBuffer_TerrainTexture::CVIBuffer_TerrainTexture(
	LPDIRECT3DDEVICE9 pDevice, 
	_size iVertexCountX, 
	_size iVertexCountZ, 
	_float fVertexInterval)
	: CVIBuffer(pDevice)
	, m_iVertexCountX(iVertexCountX)
	, m_iVertexCountZ(iVertexCountZ)
	, m_fVertexInterval(fVertexInterval)
{
}

CVIBuffer_TerrainTexture::CVIBuffer_TerrainTexture(const CVIBuffer_TerrainTexture & other)
	: CVIBuffer(other)
	, m_iVertexCountX(other.m_iVertexCountX)
	, m_iVertexCountZ(other.m_iVertexCountZ)
	, m_fVertexInterval(other.m_fVertexInterval)
{
}

HRESULT CVIBuffer_TerrainTexture::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_TEXTURE);
	m_iVertexCount = m_iVertexCountX * m_iVertexCountZ;
	m_iTriCount = (m_iVertexCountX - 1) * (m_iVertexCountZ - 1) * 2;
	m_iFVF = FVF_TEXTURE;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFMT = D3DFMT_INDEX16;

	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;

	/*
	버텍스버퍼가 가진 버텍스 정보를 변경하려면 반드시 lock, unlock 사이에서 진행.
	lock함수를 통해서 버텍스버퍼가 갖고있는 버텍스배열의 주소를 얻어낼 수 있다.
	*/
	VTX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	_size index = 0;

	for (_size z = 0; z < m_iVertexCountZ; ++z)
	{
		for (_size x = 0; x < m_iVertexCountX; ++x)
		{
			index = z * m_iVertexCountX + x;
			if(m_iVertexCount <= index)
				continue;

			pVertices[index].vPosition = _float3(x * m_fVertexInterval, 0.f, z * m_fVertexInterval);
			pVertices[index].vUV = _float2(x / (m_iVertexCountX - 1.f), 1.f - z / (m_iVertexCountZ - 1.f));
		}
	}

	m_pVB->Unlock();

	INDEX16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);	

	_size iTriIndex = 0;

	for (_size z = 0; z < m_iVertexCountZ - 1; ++z)
	{
		for (_size x = 0; x < m_iVertexCountX - 1; ++x)
		{
			index = z * m_iVertexCountX + x;
			if (m_iVertexCount <= index)
				continue;

			/* 오른쪽 삼각형 */
			pIndices[iTriIndex]._1 = index + m_iVertexCountX;
			pIndices[iTriIndex]._2 = index + m_iVertexCountX + 1;
			pIndices[iTriIndex++]._3 = index + 1;

			/* 왼쪽 삼각형 */
			pIndices[iTriIndex]._1 = index + m_iVertexCountX;
			pIndices[iTriIndex]._2 = index + 1;
			pIndices[iTriIndex++]._3 = index;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_TerrainTexture::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer_TerrainTexture::Render_Buffer()
{
	if (FAILED(CVIBuffer::Render_Buffer()))
		return E_FAIL;	

	/* 장치에게 전달한 버텍스와 인덱스를 가지고 도형을 그리는 함수 */
	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_TerrainTexture * CVIBuffer_TerrainTexture::Create(
	LPDIRECT3DDEVICE9 pDevice, 
	_size iVertexCountX, 
	_size iVertexCountZ, 
	_float fVertexInterval)
{
	CVIBuffer_TerrainTexture* pInstance = new CVIBuffer_TerrainTexture(pDevice, iVertexCountX, iVertexCountZ, fVertexInterval);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_TerrainTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_TerrainTexture::Clone(void * pArg/* = nullptr*/)
{
	CVIBuffer_TerrainTexture* pClone = new CVIBuffer_TerrainTexture(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_TerrainTexture");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_TerrainTexture::Free()
{
	CVIBuffer::Free();
}
