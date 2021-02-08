#pragma once
#ifndef __VIBUFFER_FLOORTEXTURE_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_FloorTexture final : public CVIBuffer
{
protected:
	explicit CVIBuffer_FloorTexture(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_FloorTexture(const CVIBuffer_FloorTexture& other);
	virtual ~CVIBuffer_FloorTexture() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual HRESULT Render_Buffer() override;

public:
	static CVIBuffer_FloorTexture* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;
};
END

#define __VIBUFFER_FLOORTEXTURE_H__
#endif