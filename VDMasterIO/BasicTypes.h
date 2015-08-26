#pragma once

#ifndef null
#define null 0
#endif

typedef unsigned char byte;			// unsigned __int8
typedef unsigned short word;		// unsigned __int16
typedef unsigned int dword;			// unsigned __int32
typedef unsigned long long qword;	// unsigned __int64

typedef unsigned int uint;
typedef unsigned long long siz;
typedef int ptrdiff;

#ifdef _UNICODE
typedef wchar_t tchar;
#define t(c) L ## c
#else
typedef char tchar;
#define t(c) c
#endif

#define GIGABYTE  1000000000
#define MEGABYTE	 1000000
#define KILOBYTE		1000