#pragma once


#ifdef VDMASTERIO_EXPORTS
#define VDMASTERIO_API __declspec(dllexport)
#else
#define VDMASTERIO_API __declspec(dllimport)
#endif

#include "BasicTypes.h"

namespace Math
{
	VDMASTERIO_API siz mins(siz a, siz b);
}
