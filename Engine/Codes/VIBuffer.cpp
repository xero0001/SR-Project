#include "..\Headers\VIBuffer.h"

USING(Engine)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & other)
	: CComponent(other)
	, m_pVB(other.m_pVB)
	, m_pIB(other.m_pIB)
	, m_iVertexCount(other.m_iVertexCount)
	, m_iVertexSize(other.m_iVertexSize)
	, m_iTriCount(other.m_iTriCount)
	, m_iFVF(other.m_iFVF)
	, m_iIndexSize(other.m_iIndexSize)
	, m_IndexFMT(other.m_IndexFMT)
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Ready_Component_Prototype()
{
	/* 버텍스버퍼 Com객체 생성 함수 */
	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_iVertexCount * m_iVertexSize, /* 버텍스 배열의 총 메모리 사이즈 */
		0, /* 사용방식 D3DUSAGE_DYNAMIC외의 인수들은 정적버퍼를 의미 */
		m_iFVF,
		D3DPOOL_MANAGED, /* 메모리 보관 방식 */
		&m_pVB,
		nullptr)))
	{
		PRINT_LOG(L"Error", L"Failed To CreateVertexBuffer");
		return E_FAIL;
	}

	/* 인덱스버퍼 Com객체 생성 함수 */
	if (FAILED(m_pDevice->CreateIndexBuffer(
		m_iTriCount * m_iIndexSize, /* 인덱스 배열의 총 메모리 사이즈 */
		0, /* 사용방식 D3DUSAGE_DYNAMIC외의 인수들은 정적버퍼를 의미 */
		m_IndexFMT,
		D3DPOOL_MANAGED, /* 메모리 보관 방식 */
		&m_pIB,
		nullptr)))
	{
		PRINT_LOG(L"Error", L"Failed To CreateIndexBuffer");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVIBuffer::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer::Render_Buffer()
{
	/* 장치에게 현재 버텍스버퍼를 넘겨준다. */
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize)))
		return E_FAIL;

	/* 장치에게 FVF 전달 */
	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	/* 장치에게 인덱스 버퍼 전달 */
	if (FAILED(m_pDevice->SetIndices(m_pIB)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	CComponent::Free();
}
