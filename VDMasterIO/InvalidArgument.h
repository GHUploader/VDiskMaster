#pragma once
#include "Exception.h"

class InvalidArgument :
	public Exception
{
public:
	InvalidArgument();
	InvalidArgument(const tchar* msg);
	InvalidArgument(uint errCode);
	InvalidArgument(const tchar* msg, uint errCode);
	InvalidArgument(const InvalidArgument& cpy);
	virtual ~InvalidArgument() noexcept;

private:
	typedef Exception super;
};

