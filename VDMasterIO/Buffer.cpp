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
		initBuffer();
		objSize = 0;
		objCount = 0;
	}

	void Buffer::initBuffer()
	{
		Buffer** ptr = new Buffer*[1 + 2];
		ptr[1] = nullptr;
		refCounter = BCBuffer<Buffer*>(ptr, 1, nullptr);
		refCounter[0] = this;
	}

	void Buffer::copy(const Buffer& cpy)
	{
		objSize = cpy.objSize;
		objCount = cpy.objCount;
	}

	void Buffer::copyReferances(Buffer* cpy)
	{

	}

	void Buffer::addRef(Buffer* ref)
	{
		Buffer** tmp = new Buffer*[1 + 2];
		tmp[1] = nullptr;
		BCBuffer<Buffer*> pBuf = BCBuffer<Buffer*>(tmp, 1, nullptr);
		pBuf[0] = ref;
		refCounter.push(&pBuf);
	}

	uint Buffer::numRefNotNull()
	{
		uint nNull = 0;
		for (siz i = 0; i < refCounter.getSize(); ++i)
		{
			if (refCounter[i] != nullptr)
				++nNull;
		}
		return nNull;
	}

	void Buffer::updateDeletable()
	{
		uint nNull = numRefNotNull();
		if (nNull > 1)
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


