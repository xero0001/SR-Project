#include "..\Headers\Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pDevice_Manager(CDevice_Manager::Get_Instance())
	, m_pScene_Manager(CScene_Manager::Get_Instance())
	, m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pTime_Manager(CTime_Manager::Get_Instance())
{
}

HRESULT CManagement::Ready_Engine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplay, _uint iSceneCount)
{
	if (nullptr == m_pDevice_Manager ||
		nullptr == m_pScene_Manager ||
		nullptr == m_pGameObject_Manager ||
		nullptr == m_pComponent_Manager ||
		nullptr == m_pTime_Manager)
		return E_FAIL;

	if (FAILED(m_pDevice_Manager->Ready_Device(hWnd, iWinCX, iWinCY, eDisplay)))
	{
		PRINT_LOG(L"Error", L"Failed To Ready_Device");
		return E_FAIL;
	}

	m_pRenderer = CRenderer::Create(m_pDevice_Manager->Get_Device());
	if (nullptr == m_pRenderer)
	{
		PRINT_LOG(L"Error", L"Failed To Renderer");
		return E_FAIL;
	}

	if (FAILED(m_pGameObject_Manager->Ready_GameObject_Manager(iSceneCount)))
	{
		PRINT_LOG(L"Error", L"Failed To Ready_GameObject_Manager");
		return E_FAIL;
	}

	if (FAILED(m_pComponent_Manager->Ready_Component_Manager(iSceneCount)))
	{
		PRINT_LOG(L"Error", L"Failed To Ready_Component_Manager");
		return E_FAIL;
	}

	if (FAILED(m_pTime_Manager->Ready_Time_Manager()))
	{
		PRINT_LOG(L"Error", L"Failed To Ready_Time_Manager");
		return E_FAIL;
	}

	return S_OK;
}

_uint CManagement::Update_Engine()
{
	if (nullptr == m_pScene_Manager ||
		nullptr == m_pGameObject_Manager ||
		nullptr == m_pTime_Manager)
		return 0;

	_float fDeltaTime = m_pTime_Manager->Update_Time_Manager();
	_uint iEvent = 0;

	if (iEvent = m_pScene_Manager->Update_Scene(fDeltaTime))
		return iEvent;

	if (iEvent = m_pGameObject_Manager->Update_GameObject(fDeltaTime))
		return iEvent;

	if (iEvent = m_pScene_Manager->LateUpdate_Scene(fDeltaTime))
		return iEvent;

	if (iEvent = m_pGameObject_Manager->LateUpdate_GameObject(fDeltaTime))
		return iEvent;

	return _uint();
}

HRESULT CManagement::Render_Engine()
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Render();
}

HRESULT CManagement::Clear_ForScene(_uint iSceneIndex)
{
	if (nullptr == m_pGameObject_Manager ||
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (FAILED(m_pGameObject_Manager->Clear_ForScene(iSceneIndex)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Clear_ForScene(iSceneIndex)))
		return E_FAIL;

	return S_OK;
}

LPDIRECT3DDEVICE9 CManagement::Get_Device() const
{
	if (nullptr == m_pDevice_Manager)
		return nullptr;

	return m_pDevice_Manager->Get_Device();
}

HRESULT CManagement::SetUp_CurrentScene(_int iSceneID, CScene * pNextScene)
{
	if (nullptr == m_pScene_Manager)
		return E_FAIL;

	return m_pScene_Manager->SetUp_CurrentScene(iSceneID, pNextScene);
}

HRESULT CManagement::Add_GameObjectToRenderList(
	ERenderID eRenderID, 
	CGameObject * pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_GameObjectToRenderList(eRenderID, pGameObject);
}

const CGameObject * CManagement::Get_GameObject(_uint iSceneIndex, const wstring & LayerTag, _size iIndex)
{
	if(nullptr == m_pGameObject_Manager)
		return nullptr;

	return m_pGameObject_Manager->Get_GameObject(iSceneIndex, LayerTag, iIndex);
}

const CComponent * CManagement::Get_Component(_uint iSceneIndex, const wstring & LayerTag, const wstring & ComponentTag, _size iIndex)
{
	if (nullptr == m_pGameObject_Manager)
		return nullptr;

	return m_pGameObject_Manager->Get_Component(iSceneIndex, LayerTag, ComponentTag, iIndex);
}

HRESULT CManagement::Add_GameObject_Prototype(
	_uint iSceneIndex, 
	const wstring & PrototypeTag, 
	CGameObject * pPrototype)
{
	if (nullptr == m_pGameObject_Manager)
		return E_FAIL;

	return m_pGameObject_Manager->Add_GameObject_Prototype(iSceneIndex, PrototypeTag, pPrototype);
}

HRESULT CManagement::Add_GameObject_ToLayer(
	_uint iFromSceneIndex, 
	const wstring & PrototypeTag, 
	_uint iToSceneIndex, 
	const wstring & LayerTag, 
	void * pArg)
{
	if (nullptr == m_pGameObject_Manager)
		return E_FAIL;

	return m_pGameObject_Manager->Add_GameObject_ToLayer(iFromSceneIndex, PrototypeTag, iToSceneIndex, LayerTag, pArg);
}

HRESULT CManagement::Add_Component_Prototype(
	_uint iSceneIndex, 
	const wstring & PrototypeTag, 
	CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Component_Prototype(iSceneIndex, PrototypeTag, pPrototype);
}

CComponent * CManagement::Clone_Component(_uint iSceneIndex, const wstring & PrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iSceneIndex, PrototypeTag, pArg);
}

_float CManagement::Get_DeltaTime() const
{
	if (nullptr == m_pTime_Manager)
		return 0.f;

	return m_pTime_Manager->Get_TimeDelta();
}

void CManagement::Free()
{
	if (Safe_Release(m_pRenderer))
	{
		PRINT_LOG(L"Warning", L"Failed To Release m_pRenderer");
	}

	if (CTime_Manager::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CTime_Manager");
	}

	if (CComponent_Manager::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CComponent_Manager");
	}

	if (CGameObject_Manager::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CGameObject_Manager");
	}

	if (CScene_Manager::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CScene_Manager");
	}

	if (CDevice_Manager::Destroy_Instance())
	{
		PRINT_LOG(L"Warning", L"Failed To Destroy_Instance CDevice_Manager");
	}
}
