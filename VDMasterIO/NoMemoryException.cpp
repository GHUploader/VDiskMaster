#include "stdafx.h"
#include "NoMemoryException.h"


NoMemoryException::NoMemoryException() : Exception(ERR_NOMEMORY)
{
	init();
}

NoMemoryException::NoMemoryException(const NoMemoryException& cpy) : Exception(cpy)
{
	memSize = cpy.memSize;
}

NoMemoryException::NoMemoryException(const tchar* msg) : Exception(msg, ERR_NOMEMORY)
{
	init();
}


NoMemoryException::NoMemoryException(siz memSize) : Exception(ERR_NOMEMORY)
{
	this->memSize = memSize;
}

NoMemoryException::NoMemoryException(const tchar* msg, siz memSize) : Exception(msg, ERR_NOMEMORY)
{
	this->memSize = memSize;
}

NoMemoryException::~NoMemoryException() noexcept {}


void NoMemoryException::init()
{
	memSize = 0;
}

siz NoMemoryException::getMemSize() const noexcept
{
	return memSize;
}