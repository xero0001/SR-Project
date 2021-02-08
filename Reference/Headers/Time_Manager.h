#pragma once
#ifndef __TIME_MANAGER_H__

#include "Base.h"

BEGIN(Engine)
class CTime_Manager final : public CBase
{
	DECLARE_SINGLETON(CTime_Manager)
private:
	CTime_Manager();
	virtual ~CTime_Manager() = default;
public:
	_float Get_TimeDelta() { return m_fDeltaTime; }
public:
	HRESULT Ready_Time_Manager(); 
	_float Update_Time_Manager(); 

public:
	virtual void Free() override;

private:
	_float m_fDeltaTime ; 
	LARGE_INTEGER m_CPUCount;
	LARGE_INTEGER m_StartTime; 
	LARGE_INTEGER m_GoalTime; 

};
END

#define __TIME_MANAGER_H__
#endif