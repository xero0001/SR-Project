#include "Time_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTime_Manager)

CTime_Manager::CTime_Manager()
	:m_fDeltaTime(0.f)
{
	ZeroMemory(&m_CPUCount, sizeof(LARGE_INTEGER)); 
	ZeroMemory(&m_StartTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_GoalTime, sizeof(LARGE_INTEGER));
}

HRESULT CTime_Manager::Ready_Time_Manager()
{
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceCounter(&m_GoalTime);
	QueryPerformanceFrequency(&m_CPUCount);

	return S_OK;
}

_float CTime_Manager::Update_Time_Manager()
{
	QueryPerformanceFrequency(&m_CPUCount);
	QueryPerformanceCounter(&m_GoalTime);
	m_fDeltaTime = float(m_GoalTime.QuadPart - m_StartTime.QuadPart) / m_CPUCount.QuadPart; 
	m_StartTime.QuadPart = m_GoalTime.QuadPart;

	return m_fDeltaTime;
}

void CTime_Manager::Free()
{
}
