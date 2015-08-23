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

		Alloc()
		{
			data = null;
		}

		static void* operator new[](siz tLocation)
		{
			try
			{
				return ::operator new(tLocation);
			}
			catch (const std::bad_alloc& e)
			{
				throw NoMemoryException(tLocation);
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
		siz tLocation;
		void(*noMemHandler)(const NoMemoryException& e);
		bool isDelete;
		bool isDeletable;

		void init()
		{
			ptr = null;
			terminator = null;
			tLocation = 0;
			noMemHandler = null;
			isDeletable = true;
			isDelete = true;
		}

		void copy(const AutoPtr<Type>& cpy)
		{
			ptr = cpy.ptr;
			terminator = cpy.terminator;
			tLocation = cpy.tLocation;
			isDelete = cpy.isDelete;
			isDeletable = cpy.isDeletable;
			noMemHandler = cpy.noMemHandler;
		}

		void reset()
		{
			clear();
			init();
		}

		void clear()
		{
			if (!isDeletable)
				return;
			if (ptr)
				delete[] ptr;
			ptr = null;
			updateDeleteStatus();
		}

		void alloc(siz tLocation) throw(NoMemoryException)
		{
			reset();
			// later an error check for tLocation will be added
			try
			{
				ptr = new Alloc<Type>[tLocation + 2];		// one for user terminator, the other for null terminator
			}
			catch (const NoMemoryException& e)
			{
				if (!noMemHandler)
					throw;
				noMemHandler(e);
			}
			updateDeleteStatus();
			putT();
		}

		void updateDeleteStatus()
		{
			if (ptr)
				isDelete = true;
			else
				isDelete = false;
		}

		void putT()
		{
			if (isDelete)
				return;
			ptr[tLocation].data = terminator;
			ptr[tLocation + 1].data = null;
		}

		void putNT(Type nT)
		{
			terminator = Alloc<Type>(nT);
			putT();
		}

		void setNT(Type nT, siz loc)
		{
			tLocation = loc;
			putNT(nT);
		}


	public:
		AutoPtr()
		{
			init();
		}

		AutoPtr(const AutoPtr<Type>& cpy)
		{
			init();
			copy(cpy);
		}

		AutoPtr(Type* ptr, siz tLocation, Type terminator)
		{
			init();
			setPtr(ptr, tLocation, terminator);
		}

		virtual ~AutoPtr()
		{
			clear();
		}

		void allocate(siz tLocation) throw(NoMemoryException)
		{
			alloc(tLocation);
		}

		void setTLocation(siz tLocation)			
		{
			this->tLocation = tLocation;
			putT();
		}

		void unmountPtr()			// removes ptr without deleting and resets object
		{
			init();
		}

		void setTerminator(Type terminator)
		{
			putNT(terminator);
		}

		void setDeletable(bool isDeletable)
		{
			this->isDeletable = isDeletable;
		}

		void setNoMemHandler(void(*handler)(const NoMemoryException& e))
		{
			noMemHandler = handler;
		}

		void setPtr(Type* ptr, siz tLocation, Type terminator)
		{
			clear();												// this will delete the old ptr if isDeletable is set ( it is by default )
			this->ptr = ptr;
			updateDeleteStatus();
			setNT(terminator, tLocation);
		}

		void setData(Type data, siz location)
		{
			this->operator[](location) = data;
		}

		Type getData(siz location)
		{
			return this->operator[](location);
		}

		Type* getPtr() const
		{
			return (Type*)ptr;
		}

		bool getDeletable() const
		{
			return isDeletable;
		}

		Type getTerminator() const
		{
			return terminator;
		}

		bool isDeleted() const
		{
			return isDelete;
		}

		siz getTLocation() const
		{
			return tLocation;
		}

		void(*getNoMemHandler()(const NoMemoryException&))
		{
			return noMemHandler;
		}



		Type& operator[](siz index) throw(InvalidArgument)
		{
			if (index < 0 || index > tLocation)
				throw InvalidArgument(ERR_INDEX_OUTOF_RANGE);
			return ptr[index].data;
		}

		AutoPtr& operator=(const AutoPtr& cpy)
		{
			copy(cpy);
			return *this;
		}

	};

}