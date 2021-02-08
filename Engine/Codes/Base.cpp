#include "..\Headers\Base.h"

USING(Engine)

CBase::CBase()
{
}

_uint CBase::AddRef()
{
	return m_iRefCount++;
}

_uint CBase::Release()
{
	if (0 == m_iRefCount)
	{
		Free();
		delete this;

		return 0;
	}

	return m_iRefCount--;
}
