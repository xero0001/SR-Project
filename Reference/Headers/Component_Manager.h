#pragma once
#ifndef __COMPONENT_MANAGER_H__

#include "VIBuffer_TriColor.h"
#include "VIBuffer_RectColor.h"
#include "VIBuffer_RectTexture.h"
#include "VIBuffer_TerrainColor.h"
#include "VIBuffer_TerrainTexture.h"
#include "VIBuffer_WallTexture.h"
#include "VIBuffer_FloorTexture.h"
#include "Transform.h"
#include "Texture.h"

BEGIN(Engine)
class CComponent_Manager : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)

private:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	HRESULT Ready_Component_Manager(_size iSceneCount);
	HRESULT Add_Component_Prototype(_uint iSceneIndex, const wstring& PrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iSceneIndex, const wstring& PrototypeTag, void* pArg = nullptr);
	HRESULT Clear_ForScene(_uint iSceneIndex);

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CComponent*>	COMPONENTS; /* 컴포넌트들의 원형들을 보관 */
	COMPONENTS*	m_pComponents = nullptr;	// 동적배열
	_size		m_iContainerSize = 0;
};
END

#define __COMPONENT_MANAGER_H__
#endif
