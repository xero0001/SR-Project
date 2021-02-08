#include "..\Headers\VIBuffer_TriColor.h"

USING(Engine)

CVIBuffer_TriColor::CVIBuffer_TriColor(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_TriColor::CVIBuffer_TriColor(const CVIBuffer_TriColor & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_TriColor::Ready_Component_Prototype()
{
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = 3;
	m_iTriCount = 1;
	m_iFVF = FVF_COLOR;

	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;

	/*
	버텍스버퍼가 가진 버텍스 정보를 변경하려면 반드시 lock, unlock 사이에서 진행.
	lock함수를 통해서 버텍스버퍼가 갖고있는 버텍스배열의 주소를 얻어낼 수 있다.
	*/
	VTX_COLOR* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	// 정점 정보를 변경
	pVertices[0].vPosition = _float3(0.f, 1.f, 0.f);
	pVertices[0].iColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[1].vPosition = _float3(1.f, -1.f, 0.f);
	pVertices[1].iColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVertices[2].vPosition = _float3(-1.f, -1.f, 0.f);
	pVertices[2].iColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_TriColor::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer_TriColor::Render_Buffer()
{
	if (FAILED(CVIBuffer::Render_Buffer()))
		return E_FAIL;

	/* 장치에게 전달한 버텍스를 가지고 도형을 그리는 함수 */
	return m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iTriCount);
}

CVIBuffer_TriColor * CVIBuffer_TriColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_TriColor* pInstance = new CVIBuffer_TriColor(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_TriColor");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_TriColor::Clone(void * pArg/* = nullptr*/)
{
	CVIBuffer_TriColor* pClone = new CVIBuffer_TriColor(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_TriColor");
		Safe_Release(pClone);
	}

	return pClone;
}

void CVIBuffer_TriColor::Free()
{
	CVIBuffer::Free();
}
