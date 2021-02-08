#pragma once
#ifndef __ENGINE_STRUCT_H__

typedef struct tagVertexColor
{
	_float3 vPosition;
	_uint iColor;
}VTX_COLOR;

const _uint FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertexTexture
{
	_float3 vPosition;
	_float2 vUV;
}VTX_TEXTURE;

const _uint FVF_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct tagIndex16
{
	WORD _1, _2, _3;
}INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3;
}INDEX32;

#define __ENGINE_STRUCT_H__
#endif

