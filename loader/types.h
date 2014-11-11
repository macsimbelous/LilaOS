/* Copyright 2004 Maxim Belous. */

#ifndef _TYPES_H
#define _TYPES_H

/* Лимиты типов данных. */

#define CHAR_BIT	8
#define CHAR_MAX	255
#define CHAR_MIN	0
#define SCHAR_MAX	127
#define SCHAR_MIN	-128

#define INT_MAX    	2147483647
#define INT_MIN		(-INT_MAX - 1)
#define UINT_MAX  	4294967295U

#define LONG_MAX	2147483647L
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	4294967295UL

typedef unsigned long uint32;
typedef long long int64;
typedef unsigned long long uint64;

#define NULL ((void *) 0)

#define KB ((unsigned long) 1024)
#define MB ((unsigned long) 1024 * KB)
#define GB ((unsigned long) 1024 * MB)

#define LOW_U16(x)                      (unsigned short)((x) & 0xFFFF)
#define HIGH_U16(x)                     (unsigned short)((x) >> 16)
#define LOW_U8(x)                       ((x) & 0xFF)
#define HIGH_U8(x)                      ((x) >> 8)

#define DWORD_SHIFT			2
#define DWORD_SIZE			(1UL << DWORD_SHIFT)
#define DWORD_MASK			(~(DWORD_SIZE-1))
#define DWORD_ALIGN(addr)		(((addr)+DWORD_SIZE-1)&DWORD_MASK)



#define BIT_VALUE(x) (1 << (x))

#endif
