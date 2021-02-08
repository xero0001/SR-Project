#pragma once
#ifndef __VIBUFFER_TERRAINCOLOR_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_TerrainColor : public CVIBuffer
{
protected:
	explicit CVIBuffer_TerrainColor(LPDIRECT3DDEVICE9 pDevice, _size iVertexCountX, _size iVertexCountZ, _float fVertexInterval = 1.f);
	explicit CVIBuffer_TerrainColor(const CVIBuffer_TerrainColor& other);
	virtual ~CVIBuffer_TerrainColor() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual HRESULT Render_Buffer() override;

public:
	static CVIBuffer_TerrainColor* Create(LPDIRECT3DDEVICE9 pDevice, _size iVertexCountX, _size iVertexCountZ, _float fVertexInterval = 1.f);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	_size m_iVertexCountX = 0;
	_size m_iVertexCountZ = 0;
	_float m_fVertexInterval = 1.f;
};
END

#define __VIBUFFER_TERRAINCOLOR_H__
#endif