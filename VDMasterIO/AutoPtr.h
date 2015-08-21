#pragma once

#include <exception>
#include "BasicTypes.h"
#include "NoMemoryException.h"
#include "InvalidArgument.h"




namespace VDMaster
{

	template <typename Type>
	struct Alloc
	{
		Type data;

		Alloc(Type data)
		{
			this->data = data;
		}

		static void* operator new[](siz size)
		{
			try
			{
				return ::operator new(size);
			}
			catch (const std::bad_alloc& e)
			{
				throw NoMemoryException(size);
			}
			return nullptr;
		}
	};

	template <typename Type>
	class AutoPtr
	{
	private:
		Alloc<Type>* ptr;
		Alloc<Type> terminator;
		siz size;
		void(*noMemHandler)(const NoMemoryException& e);
		bool isDelete;

		void init()
		{
			ptr = null;
			terminator = null;
			size = 0;
			noMemHandler = null;
			same = null;
			isDelete = true;
		}

		void copy(const AutoPtr<Type>& cpy)
		{
			ptr = cpy.ptr;
			terminator = cpy.terminator;
			size = cpy.size;
			isDelete = cpy.isDelete;
			noMemHandler = cpy.noMemHandler;
		}

		void reset()
		{
			clear();
			init();
		}

		void clear()
		{
			if (isDelete)
				return;
			if (ptr)
				delete[] ptr;
			ptr = null;
			isDelete = true;
		}

		void alloc(siz size)
		{
			clear();
			// later an error check for size will be added
			try
			{
				ptr = new Alloc<Type>[size + 1];
			}
			catch (const NoMemoryException& e)
			{
				if (!noMemHandler)
					throw;
				noMemHandler(e);
			}
			this->size = size;
			ptr[size] = terminator;
			isDelete = false;
		}


	public:
		AutoPtr()
		{
			init();
		}

		AutoPtr(const AutoPtr<Type>& cpy)
		{
			copy(cpy);
		}

		virtual ~AutoPtr()
		{
			clear();
		}

		void setSize(siz size)
		{

		}

		void setTerminator(Type terminator)
		{
			this->terminator = Alloc(terminator);
			ptr[size] = this->terminator;
		}

		void setNoMemHandler(void(*handler)(const NoMemoryException& e))
		{
			noMemHandler = handler;
		}

		Type& operator[](siz index)
		{
			if (index < 0 || index > size)
				throw InvalidArgument(ERR_INDEX_OUTOF_RANGE);
			return ptr[index].data;
		}

		AutoPtr operator=(const AutoPtr& cpy)
		{
			copy(cpy);
			return *this;
		}

	};

}