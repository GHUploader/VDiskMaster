#include "stdafx.h"
#include "Exception.h"

Exception::Exception()
{
	msg = null;
	errCode = 0;
}

Exception::Exception(uint errCode)
{
	this->errCode = errCode;
	msg = null;
}

Exception::Exception(const tchar* msg, uint errCode)
{
	this->msg = msg;
	this->errCode = errCode;
}

Exception::Exception(const Exception& cpy)
{
	msg = cpy.msg;
	errCode = cpy.errCode;
}

Exception::Exception(const tchar* msg)
{
	this->msg = msg;
	errCode = 0;
}


Exception::~Exception() noexcept
{

}

const tchar* Exception::what() const noexcept
{
	return msg;
}

uint Exception::getErrCode() const noexcept
{
	return this->errCode;
}