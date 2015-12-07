#include "stdafx.h"
#include "InvalidArgument.h"


InvalidArgument::InvalidArgument() : Exception() {}
InvalidArgument::InvalidArgument(const tchar* msg) : Exception(msg) {}
InvalidArgument::InvalidArgument(uint errCode) : Exception(errCode) {}
InvalidArgument::InvalidArgument(const tchar* msg, uint errCode) : Exception(msg, errCode) {}
InvalidArgument::InvalidArgument(const InvalidArgument& cpy) : Exception(cpy) {}
InvalidArgument::~InvalidArgument() noexcept {}

// change

