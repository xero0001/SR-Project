#pragma once
#ifndef __VIBUFFER_H__

#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer(const CVIBuffer& other);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Ready_Component_Prototype() = 0;
	virtual HRESULT Ready_Component(void * pArg = nullptr) = 0;
	virtual HRESULT Render_Buffer() = 0;

public:
	virtual CComponent * Clone(void * pArg = nullptr) = 0;
	virtual void Free() = 0;

protected:
	/*
	LPDIRECT3DVERTEXBUFFER9: 
	사용자가 생성해놓은 버텍스들을 배열로 보관 및 관리하는 Com객체의 포인터
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	_size m_iVertexCount = 0; // 정점개수
	_size m_iVertexSize = 0;  // 정점의 개당 메모리 크기
	_size m_iTriCount = 0; // 폴리곤 개수
	_uint m_iFVF = 0; // Flexible Vertex Format	

	/*
	LPDIRECT3DINDEXBUFFER9: 
	사용자가 생성해놓은 인덱스들을 배열로 보관 및 관리하는 Com객체의 포인터
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB = nullptr;
	D3DFORMAT m_IndexFMT = D3DFMT_INDEX16;
	_size m_iIndexSize = 0; /* 인덱스 자료형의 크기 */

	
	
};
END

#define __VIBUFFER_H__
#endif