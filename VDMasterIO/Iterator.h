#pragma once
#include <iterator>
#include "BasicTypes.h"
#include "IndexOutOfRange.h"

namespace VDMaster
{

	template<typename Type>
	class Iterator
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;

		Iterator()
		{
			init();
		}

		Iterator(const Iterator& cpy)
		{
			init();
			copy(cpy);
		}

		Iterator(Type* begin, Type* ptr, Type* end)
		{
			this->begin = begin;
			this->ptr = ptr;
			this->end = end;
		}

		virtual ~Iterator()
		{

		}

		Iterator getNext(uint jmp = 0) const
		{
			Type* tPtr = ptr + jmp;
			return Iterator(begin, tPtr, end);
		}

		Iterator getPrevious(uint jmp = 0) const
		{
			Type* tPtr = ptr - jmp;
			return Iterator(begin, tPtr, end);
		}

		siz getSize() const
		{
			return end - begin;
		}

		bool hasNext(Type* end = this->end) const
		{
			return ptr < end;
		}

		bool hasPrevious(Type* begin = this->begin) const
		{
			return begin < ptr;
		}

		Type& operator[](siz index) throw(IndexOutOfRange)
		{
			if (&ptr[index] < begin || &ptr[index] > end)
				throw IndexOutOfRange(t("Iterator<Type>::operator[](siz index)"), index);
			return ptr[index];
		}

		Iterator& operator=(const Iterator& cpy)
		{
			copy(cpy);
			return *this;
		}

		Iterator& operator=(Type* ptr)
		{
			init();
			this->ptr;
			isManaged = false;
			return *this;
		}

		Type& operator*()
		{
			return *ptr;
		}

		Iterator operator+(const Iterator& cpy)
		{
			Type* nPtr = ptr + cpy.ptr;
			if (cpy.isManaged)
			{

			}
		}

	private:
		Type* begin;
		Type* ptr;
		Type* end;
		bool isManaged;

		void maxPtr(Type* ptr)
		{

		}

		void init()
		{
			begin = null;
			ptr = null;
			end = null;
			isManaged = false;
		}

		void copy(const Iterator& cpy)
		{
			begin = cpy.begin;
			ptr = cpy.ptr;
			end = cpy.end;
			isManaged = cpy.isManaged;
		}

	};
}