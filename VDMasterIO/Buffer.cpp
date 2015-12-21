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
		refCount = 0;
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
		Buffer* ref = (Buffer*)&cpy;
		addRef(ref);
		ref->addRef(this);
	}

	void Buffer::copyReferances(Buffer* cpy)
	{
		siz maxIndex = cpy->refCounter.getSize();
		siz oldSize = refCounter.getSize();
		siz nSize = refCounter.getSize() + maxIndex;
		refCounter.setSize(nSize);
		Iterator<Buffer*> itBegin = cpy->refCounter.begin();
		Iterator<Buffer*> itEnd = cpy->refCounter.end();
		Iterator<Buffer*> dest = &refCounter[oldSize];
		//cpyPtr<Buffer*>(itBegin, itEnd, dest);
	}

	void Buffer::addRef(Buffer* ref)
	{
		Buffer** tmp = new Buffer*[1 + 2];
		tmp[1] = nullptr;
		BCBuffer<Buffer*> pBuf = BCBuffer<Buffer*>(tmp, 1, nullptr);
		pBuf[0] = ref;
		refCounter.push(&pBuf);
		updateDeletable();
	}

	void Buffer::remRef(Buffer* ref)
	{
		siz location = refCounter.find(ref);
		if (location != (siz)-1)
			refCounter[location] = nullptr;
	}

	void Buffer::updateDeletable()
	{
		if (refCounter.getSize() > 1)
			setDeletable(false);
		else
			setDeletable(true);
	}

}


