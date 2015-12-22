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

	void RefCounter::init()
	{
		setTerminator(terminator);
		refCount = 0;
		blankRef = 0;
	}

	void RefCounter::init(void* fRef)
	{
		void** refBuffer = new void*[1 + 2];
		refBuffer[0] = fRef;
		refBuffer[1] = terminator;
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

	// static init
	void* RefCounter::terminator = (void*)0xffff;

}
