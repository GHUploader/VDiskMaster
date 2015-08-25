#pragma once

#ifndef null
#define null 0
#endif

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

typedef unsigned int uint;
typedef unsigned long long siz;

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