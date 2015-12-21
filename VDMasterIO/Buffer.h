#pragma once

#ifdef VDMASTERIO_EXPORTS
#define VDMASTERIO_API __declspec(dllexport)
#else
#define VDMASTERIO_API __declspec(dllimport)
#endif

#include "BCBuffer.h"

namespace VDMaster
{
	class VDMASTERIO_API Buffer :
		public BCBuffer<byte>
	{
	public:
		Buffer();
		Buffer(const Buffer&);
		virtual ~Buffer();

		void setObjectCount(siz);
		void setObjectSize(siz);
		void addObject(void*);

	private:
		siz objSize;
		siz objCount;
		BCBuffer<Buffer*> refCounter;
		uint refCount;

		void init();
		void initBuffer();
		void copy(const Buffer&);
		void copyReferances(Buffer*);

		void addRef(Buffer*);
		void remRef(Buffer*);
		void updateDeletable();
	};
}



