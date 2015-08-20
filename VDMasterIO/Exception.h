#pragma once
#include "BasicTypes.h"
class Exception
{
public:
	Exception();
	Exception(const Exception& cpy);
	Exception(const tchar* msg);
	Exception(uint errCode);
	Exception(const tchar* msg, uint errCode);
	virtual ~Exception() noexcept;

	const tchar* what() const noexcept;
	uint getErrCode() const noexcept;

private:
	const tchar* msg;
	uint errCode;
};

