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
	����ڰ� �����س��� ���ؽ����� �迭�� ���� �� �����ϴ� Com��ü�� ������
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	_size m_iVertexCount = 0; // ��������
	_size m_iVertexSize = 0;  // ������ ���� �޸� ũ��
	_size m_iTriCount = 0; // ������ ����
	_uint m_iFVF = 0; // Flexible Vertex Format	

	/*
	LPDIRECT3DINDEXBUFFER9: 
	����ڰ� �����س��� �ε������� �迭�� ���� �� �����ϴ� Com��ü�� ������
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB = nullptr;
	D3DFORMAT m_IndexFMT = D3DFMT_INDEX16;
	_size m_iIndexSize = 0; /* �ε��� �ڷ����� ũ�� */

	
	
};
END

#define __VIBUFFER_H__
#endif