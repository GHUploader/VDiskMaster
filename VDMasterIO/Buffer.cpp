#include "stdafx.h"
#include "Buffer.h"

namespace VDMaster
{
	Buffer::Buffer() : BCBuffer<byte>()
	{
		init();
	}

	Buffer::Buffer(const Buffer& cpy) : BCBuffer()
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

	void Buffer::copyParent(const BCBuffer& cpy)
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

}


