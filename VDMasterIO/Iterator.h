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
		typedef Type value_type;			// iterator standard typedefs
		typedef ptrdiff diference_type;
		typedef Type* pointer;
		typedef Type& reference;
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
			init();
			this->begin = begin;
			this->ptr = ptr;
			this->end = end;
			isManaged = true;
		}

		Iterator(Type* ptr)
		{
			init();
			this->ptr = ptr;
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

		reference operator[](siz index) throw(IndexOutOfRange)
		{
			if (&ptr[index] < begin || &ptr[index] > end && isManaged)
				throw IndexOutOfRange(t("Iterator<Type>::operator[](siz index)"), index);
			return ptr[index];
		}

		Iterator& operator=(const Iterator& cpy)
		{
			init();
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

		Iterator& operator+=(const Iterator& cpy)
		{
			Iterator it = this->operator+(cpy);
			copy(it);
			return *this;
		}

		Iterator& operator-=(const Iterator& cpy)
		{
			Iterator it = this->operator-(cpy);
			copy(it);
			return it;
		}

		reference operator*()
		{
			return *ptr;
		}

		pointer operator->()
		{
			return ptr;
		}

		Iterator operator+(const Iterator& cpy) const
		{
			Type* nPtr = ptr + cpy.ptr;
			Iterator it = addSubIter(cpy, true);
			it.ptr = nPtr;
			return it;
		}

		Iterator operator-(const Iterator& cpy) const
		{
			Type* nPtr = ptr - cpy.ptr;
			Iterator it = addSubIter(cpy, false);
			it.ptr = nPtr;
			return it;
		}

		Iterator& operator++()
		{
			ptr++;
			checkPtr();
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator it = *this;
			ptr++;
			checkPtr();
			return it;
		}

		Iterator& operator--()
		{
			ptr--;
			checkPtr();
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator it = *this;
			ptr--;
			checkPtr();
			return it;
		}

		bool operator<(const Iterator& cpy) const
		{
			return ptr < cpy.ptr;
		}

		bool operator<=(const Iterator& cpy) const
		{
			return ptr <= cpy.ptr;
		}

		bool operator>(const Iterator& cpy) const
		{
			return ptr > cpy.ptr;
		}

		bool operator>=(const Iterator& cpy) const
		{
			return ptr >= cpy.ptr;
		}

		bool operator==(const Iterator& cpy) const
		{
			return ptr == cpy.ptr;
		}

		bool operator!=(const Iterator& cpy) const
		{
			return !this->operator==(cpy);
		}

	private:
		Type* begin;
		Type* ptr;
		Type* end;
		bool isManaged;

		void checkPtr()
		{
			if (ptr == end || ptr == begin)
			{
				Type* tmp = ptr;
				init();
				ptr = tmp;
			}
		}

		static Type* addSubPtr(Type* ptr, Type* _ptr, bool add)
		{
			if (add)
				return ptr + _ptr;
			return ptr - _ptr;
		}

		bool isAddSubItManaged(const Iterator* it, bool add) const
		{
			if (it->isManaged && isManaged)
			{
				if (ptrIsInRange(addSubPtr(ptr, it->ptr, add)))
					return true;
			}
			return false;
		}

		Iterator addSubIter(const Iterator& cpy, bool add) const
		{
			if (isAddSubItManaged(&cpy, add) || cpy.isAddSubItManaged(this, add))
			{
				if (isAddItSubManaged(&cpy, add))
					return Iterator{ begin, begin, end };
				return Iterator{ cpy.begin, cpy.begin, cpy.end };
			}
			return Iterator();
		}

		bool ptrIsInRange(Type* ptr)
		{
			if (ptr >= begin || ptr < end)
				return true;
			return false;
		}

		static Type* maxPtr(Type* ptr, Type* _ptr)
		{
			if (ptr <= _ptr)
				return _ptr;
			return ptr;
		}

		Type* maxPtr(Type* ptr)
		{
			return maxPtr(this->ptr, ptr);
		}

		Type* maxEnd(Type* end)
		{
			return maxPtr(this->end, end);
		}

		void minBegin(Type* begin)
		{
			if (maxPtr(this->begin, begin) == begin)
				return this->begin;
			return begin;
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