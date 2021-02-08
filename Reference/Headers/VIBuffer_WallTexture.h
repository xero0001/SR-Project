#pragma once
#ifndef __VIBUFFER_WALLTEXTURE_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_WallTexture final : public CVIBuffer
{
protected:
	explicit CVIBuffer_WallTexture(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_WallTexture(const CVIBuffer_WallTexture& other);
	virtual ~CVIBuffer_WallTexture() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual HRESULT Render_Buffer() override;

public:
	static CVIBuffer_WallTexture* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;
};
END

#define __VIBUFFER_WALLTEXTURE_H__
#endif