#pragma once
#include <assert.h>
#include "AutoPtr.h"

namespace VDMaster
{
	template <typename Type>
	class BCBuffer
	{
	public:
		BCBuffer()
		{
			init();
		}

		BCBuffer(const BCBuffer<Type>& cpy)
		{
			init();
			copy(cpy);
		}

		virtual ~BCBuffer() 
		{

		}

		void setSize(siz size)				// should adjust buffer size
		{
			checkSize(size);
		}

		void setBuffer(Type* ptr, siz size = 0, Type terminator = getTerminator())
		{
			siz pSize;
			if (size == 0)
				pSize = ptrSiz(ptr, terminator);
			assert(ptr[pSize] == terminator);
			aPtr.setPtr(ptr, pSize, terminator);
			iPtr.setPtr(ptr, pSize, terminator);
		}

		void setTerminator(Type val)
		{
			iPtr.setTerminator(val);
		}

		void setDeletable(bool isDeletable)
		{
			aPtr.setDeletable(isDeletable);
		}

		bool isDeletable() const
		{
			return aPtr.getDeletable();
		}

		Type getTerminator() const
		{
			return iPtr.getTerminator();
		}

		siz getSize() const
		{
			return iPtr.getTLocation();
		}

		siz find(Type t)
		{
			siz index = 0;
			while (aPtr[index] != t)
			{
				if (index == aPtr.getSize())
					return (siz)-1;
				index++;
			}
			return index;
		}

		BCBuffer* SCopy()			// add iPtr copy
		{
			BCBuffer* ret = new BCBuffer();
			Type* cpyPtr = ptrCpy(aPtr.getPtr(), aPtr.getTLocation());
			ret->aPtr.setNoMemHandler(aPtr.getNoMemHandler());
			ret->aPtr.setPtr(cpyPtr, aPtr.getTLocation(), aPtr.getTerminator());
			ret->iPtr.setNoMemHandler(iPtr.getNoMemHandler());
			ret->iPtr.setPtr(cpyPtr, iPtr.getTLocation(), iPtr.getTerminator());
			return ret;
		}

	private:
		AutoPtr<Type> aPtr;			// TLocation is aways at the end of the allocated
		AutoPtr<Type> iPtr;			// points to the same ptr, but TLocation might be closer to the beginning and is the buufer the user sees

		void init()
		{
			aPtr = AutoPtr<Type>();
			iPtr = AutoPtr<Type>();
			iPtr.setDeletable(false);		// both objects point to the same buffer
		}

		void copy(const BCBuffer& cpy)
		{
			aPtr = cpy.aPtr;
			iPtr = cpy.iPtr;
		}

		void bigger(siz nSize)
		{
			if (aPtr.getSize() <= nSize)
			{
				incSize(nSize);
			}
			else
			{
				iPtr.setTLocation(nSize);
			}
		}

		void incSize(siz nSize)
		{
			assert(iPtr.getTLocation() <= aPtr.getTLocation());
			assert(aPtr.getTLocation() <= nSize);
			siz aSize = nSize + 10;									// for push/pop operatins, so no reallocation is needed every time
			Type* nPtr = ptrCpy(aPtr.getPtr(), aPtr.getTLocation());
			aPtr.setPtr(nPtr, aSize, aPtr.getTerminator());
			iPtr.setPtr(nPtr, nSize, iPtr.getTerminator());
		}

		void checkSize(siz newSize)
		{
			if (newSize > iPtr.getTLocation())
				bigger(newSize);
			else
				iPtr.setTLocation(newSize);
		}

		siz ptrSiz(Type* ptr, Type tEnd)
		{
			siz index = 0;
			for (; ptr[index] != tEnd; index++);
			return index;
		}

		void cpyPtr(Type* fPtr, Type* lPtr, Type* dest)
		{
			while (fPtr != lPtr)
			{
				*dest = *fPtr;
				fPtr++;
				dest++;
			}
		}

		Type* ptrCpy(Type* ptr, siz size)
		{
			AutoPtr<Type> nPtr = AutoPtr<Type>();
			nPtr.allocate(size);
			Type* fPtr = ptr;
			Type* lPtr = &ptr[size];
			cpyPtr(fPtr, lPtr, nPtr.getPtr());
			nPtr.setDeletable(false);
			return nPtr.getPtr();
		}

	};

}