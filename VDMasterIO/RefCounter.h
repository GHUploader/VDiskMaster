#pragma once
#include "BCBuffer.h"

namespace VDMaster
{

	class RefCounter :
		private BCBuffer<void*>
	{
	public:
		RefCounter();
		RefCounter(const RefCounter&);
		RefCounter(void*);
		virtual ~RefCounter();

		void addRef(void*);
		void remRef(siz index);
		bool remRef(void*);

		siz getRefCount() const;

	private:
		uint refCount;
		uint blankRef;
		static void* terminator;

		void init();
		void init(void*);
		void copy(const RefCounter&);
		void copyRefBuffer(const RefCounter&);

	};

}

