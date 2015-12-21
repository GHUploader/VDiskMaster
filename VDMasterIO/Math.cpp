#include "stdafx.h"
#include "VDMath.h"

namespace Math
{
	siz mins(siz a, siz b)
	{
		if (a < b)
			return a;
		return b;
	}
}