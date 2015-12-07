#include "stdafx.h"
#include "IndexOutOfRange.h"


IndexOutOfRange::IndexOutOfRange() : InvalidArgument(ERR_INDEX_OUTOF_RANGE)
{
	init();
}

IndexOutOfRange::IndexOutOfRange(const IndexOutOfRange& cpy) : InvalidArgument(cpy)
{
	copy(cpy);
}

IndexOutOfRange::IndexOutOfRange(siz index) : InvalidArgument(ERR_INDEX_OUTOF_RANGE)
{
	this->index = index;
}

IndexOutOfRange::IndexOutOfRange(const tchar* msg, siz index) : InvalidArgument(msg, ERR_INDEX_OUTOF_RANGE)
{
	this->index = index;
}

IndexOutOfRange::~IndexOutOfRange()
{
}

void IndexOutOfRange::init()
{
	index = 0;
}

void IndexOutOfRange::copy(const IndexOutOfRange& cpy)
{
	index = cpy.index;
}

siz IndexOutOfRange::getIndex() const noexcept
{
	return index;
}


// recovered