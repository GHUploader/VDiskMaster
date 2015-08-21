#pragma once

#ifdef VDMASTERIO_EXPORTS
#define VDMASTERIO_API __declspec(dllexport)
#else
#define VDMASTERIO_API __declspec(dllimport)
#endif

#include "BasicTypes.h"
#include "errCodes.h"

class VDMASTERIO_API Exception
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

