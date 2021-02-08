#pragma once
#ifndef __VIBUFFER_TERRAINTEXTURE_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_TerrainTexture : public CVIBuffer
{
protected:
	explicit CVIBuffer_TerrainTexture(LPDIRECT3DDEVICE9 pDevice, _size iVertexCountX, _size iVertexCountZ, _float fVertexInterval = 1.f);
	explicit CVIBuffer_TerrainTexture(const CVIBuffer_TerrainTexture& other);
	virtual ~CVIBuffer_TerrainTexture() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual HRESULT Render_Buffer() override;

public:
	static CVIBuffer_TerrainTexture* Create(LPDIRECT3DDEVICE9 pDevice, _size iVertexCountX, _size iVertexCountZ, _float fVertexInterval = 1.f);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	_size m_iVertexCountX = 0;
	_size m_iVertexCountZ = 0;
	_float m_fVertexInterval = 1.f;
};
END

#define __VIBUFFER_TERRAINTEXTURE_H__
#endif