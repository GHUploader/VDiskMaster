#include "stdafx.h"
#include "Buffer.h"

namespace VDMaster
{
	Buffer::Buffer() : BCBuffer<byte>()
	{
		init();
	}

	Buffer::Buffer(const Buffer& cpy) : BCBuffer(cpy)
	{
		copy(cpy);
	}


	Buffer::~Buffer()
	{
	}

	void Buffer::init()
	{
		refCounter = RefCounter(this);
		objSize = 0;
		objCount = 0;
	}

	void Buffer::copy(const Buffer& cpy)
	{
		copyReferances((Buffer*)&cpy);
		objSize = cpy.objSize;
		objCount = cpy.objCount;
	}

	void Buffer::copyReferances(Buffer* cpy)
	{
		refCounter = cpy->refCounter;
		cpy->refCounter.addRef(this);

	}

	void Buffer::updateDeletable()
	{
		uint refCount = refCounter.getRefCount();
		if (refCount > 1)
		{
			if (isDeletable())
				setDeletable(false);
		}
		else
		{
			if (!isDeletable())
				setDeletable(true);
		}
	}

}


