#pragma once

#include "BCBuffer.h"
#include "Iterator.h"

namespace VDMaster
{
	template<typename Type>
	class WBCBuffer : public BCBuffer<Type>
	{
	public:
		WBCBuffer() : BCBuffer()
		{
			init();
		}

		WBCBuffer(const WBCBuffer& cpy) : BCBuffer(cpy)
		{
			init();
			copy(cpy);
		}

		WBCBuffer(Type* ptr, siz size = 0, Type terminator = null) : BCBuffer(ptr, size, terminator)
		{

		}

		virtual ~WBCBuffer()
		{

		}

		void push(Type* ptr)
		{

		}

		void push(WBCBuffer wBuffer)
		{

		}



	private:

		void pushBuf(Type* pTP)
		{
			siz bSize = getSize();

		}

		void pushBCBuf(BCBuffer* obj)
		{
			siz oSize = obj->getSize();
			siz cSize = getSize();
			siz nSize = oSize + cSize;
			Iterator<Type> endIt = Iterator<Type>(&(*obj)[cSize]);
			setSize(nSize);

		}
		
		void init()
		{

		}

		void copy(const WBCBuffer& cpy)
		{

		}

	};
}


