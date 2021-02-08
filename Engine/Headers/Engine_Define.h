#pragma once
#ifndef __ENGINE_DEFINE_H__

#define PRINT_LOG(caption, message)	MessageBox(0, message, caption, MB_OK)

#define NO_EVENT		0
#define CHANGE_SCENE	1

#ifdef EXPORTS_ENGINE
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;

#define NO_COPY(ClassName)							\
private:											\
	ClassName(const ClassName&) = delete;			\
	ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* Get_Instance();		\
	static _uint Destroy_Instance();		\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)				\
ClassName* ClassName::m_pInstance = nullptr;		\
ClassName* ClassName::Get_Instance()				\
{													\
	if (nullptr == m_pInstance)						\
	{												\
		m_pInstance = new ClassName;				\
	}												\
	return m_pInstance;								\
}													\
_uint ClassName::Destroy_Instance()					\
{													\
	_uint iRefCount = 0;							\
	if (m_pInstance)								\
	{												\
		iRefCount = m_pInstance->Release();			\
		m_pInstance = nullptr;						\
	}												\
	return iRefCount;								\
}

#define __ENGINE_DEFINE_H__
#endif

