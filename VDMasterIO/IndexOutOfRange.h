#pragma once
#include "InvalidArgument.h"
class VDMASTERIO_API IndexOutOfRange :
	public InvalidArgument
{
public:
	IndexOutOfRange();
	IndexOutOfRange(siz index);
	IndexOutOfRange(const tchar* msg, siz index);
	IndexOutOfRange(const IndexOutOfRange& cpy);
	
	virtual ~IndexOutOfRange() noexcept;

	siz getIndex() const noexcept;

private:
	siz index;

	void init();
	void copy(const IndexOutOfRange& cpy);
};

