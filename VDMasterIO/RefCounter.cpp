#include "stdafx.h"
#include "RefCounter.h"

namespace VDMaster
{



	RefCounter::RefCounter() : BCBuffer()
	{
		init();
	}

	RefCounter::RefCounter(const RefCounter& cpy) : BCBuffer()
	{
		init();
		copy(cpy);
	}

	RefCounter::RefCounter(void* firstRef) : BCBuffer()
	{
		init(firstRef);
	}

	RefCounter::~RefCounter()
	{
	}

	void RefCounter::addRef(void* ref)
	{
		void** refPtr = BCBuffer<void*>::compatPtr(1, terminator);
		refPtr[0] = ref;
		BCBuffer<void*> pushVal = BCBuffer(refPtr, 1, terminator);
		push(&pushVal);
		++refCount;
	}

	void RefCounter::remRef(siz index)
	{
		this->operator[](index) = nullptr;
		--refCount;
		++blankRef;
		if (getSize() - refCount == 10)
			flush();
	}

	bool RefCounter::remRef(void* ref)
	{
		siz loc = find(ref);
		if (loc != (siz)-1)
		{
			remRef(loc);
			return false;
		}
		return true;		// ref was not found
	}

	siz RefCounter::getRefCount() const
	{
		return refCount;
	}

	Iterator<void*> RefCounter::getIterator()
	{
		return BCBuffer<void*>::getIterator();
	}

	Iterator<void*> RefCounter::begin()
	{
		return BCBuffer<void*>::begin();
	}

	Iterator<void*> RefCounter::end()
	{
		return BCBuffer<void*>::end();
	}

	RefCounter& RefCounter::operator=(const RefCounter& cpy)
	{
		if (&cpy == this)
			return *this;
		copy(cpy);
		return *this;
	}

	void RefCounter::init()
	{
		setTerminator(terminator);
		refCount = 0;
		blankRef = 0;
	}

	void RefCounter::init(void* fRef)
	{

		void** refBuffer = BCBuffer<void*>::compatPtr(1, terminator);
		refBuffer[0] = fRef;
		setBuffer(refBuffer, 1, terminator);
		refCount = 1;
		blankRef = 0;
	}

	void RefCounter::copy(const RefCounter& cpy)
	{
		copyRefBuffer(cpy);
		refCount = cpy.refCount;
		blankRef = cpy.blankRef;
	}

	void RefCounter::copyRefBuffer(const RefCounter& cpy)
	{
		RefCounter* cpyPtr = (RefCounter*)&cpy;
		BCBuffer<void*>* tmp = cpyPtr->SCopy();
		copyContruct(*tmp);
		tmp->setDeletable(false);
		setDeletable(true);
		delete tmp;
	}

	void RefCounter::flush()				// flush null referances
	{
		assert(getSize() - refCount >= 10);
		void** flushedPtr = BCBuffer<void*>::compatPtr(getSize(), terminator);
		BCBuffer<void*> flushed = BCBuffer(flushedPtr, getSize(), terminator);
		siz flIndex = 0;
		siz maxSize = getSize();
		for (siz i = 0; i < maxSize; i++)
		{
			if (this->operator[](i) != nullptr)
			{
				flushed[flIndex] = this->operator[](i);
				++flIndex;
			}
		}
		copyContruct(flushed);
		flushed.setDeletable(false);
		setDeletable(true);
	}

	// static init
	void* RefCounter::terminator = (void*)0xffff;

}
