#pragma once
#include "Exception.h"
class VDMASTERIO_API NoMemoryException :
	public Exception
{
public:
	NoMemoryException();
	NoMemoryException(const NoMemoryException& cpy);
	NoMemoryException(const tchar* msg);
	NoMemoryException(siz memSize);
	NoMemoryException(const tchar* msg, siz memSize);
	virtual ~NoMemoryException() noexcept;

	siz getMemSize() const noexcept;

private:
	typedef Exception super;
	siz memSize;

	void init();

};

