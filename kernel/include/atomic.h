/* Copyright (C) 2003 ������ ������ �������. */
#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include <config.h>

/*
 * ��������� ��������� �������� ��� ����������� ���� atomic_t.
 */

#ifdef SMP
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

typedef struct { volatile int counter; } atomic_t;

/*
 * atomic_read - ������ ��������� ����������
 */ 
#define atomic_read(v)		((v)->counter)
    		
/*
 * atomic_set - ������������� ��������� ����������
 */ 
#define atomic_set(v,i)		(((v)->counter) = (i))

/*
 * atomic_add - �������� ������� ���������� � ����� ������
 */
static __inline__ void atomic_add(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "addl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/*
 * atomic_sub - �������� �� ������� ���������� ����� �����
 */
static __inline__ void atomic_sub(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "subl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/*
 * atomic_sub_and_test - �������� �� ������� ���������� ����� ����� � ��������� ���������
 */
static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "subl %2,%0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
	return c;
}

/*
 * atomic_inc - ����������� �� 1 ������� ����������
 */ 
static __inline__ void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/*
 * atomic_dec - �������� �� 1 ������� ����������
 */ 
static __inline__ void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/*
 * atomic_dec_and_test - ��������� �� 1 ������� ���������� � ��������� ���������
 */ 
static __inline__ int atomic_dec_and_test(atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "decl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
	return c != 0;
}

/*
 * atomic_inc_and_test - ����������� �� 1 ������� ���������� � ��������� ��������� 
 */ 
static __inline__ int atomic_inc_and_test(atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "incl %0; sete %1"
		:"=m" (v->counter), "=qm" (c)
		:"m" (v->counter) : "memory");
	return c != 0;
}

/*
 * atomic_add_negative - ��������� ������� ���������� � ����� ������ � ��������� ���������
 */ 
static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
	unsigned char c;

	__asm__ __volatile__(
		LOCK "addl %2,%0; sets %1"
		:"=m" (v->counter), "=qm" (c)
		:"ir" (i), "m" (v->counter) : "memory");
	return c;
}

#define atomic_clear_mask(mask, addr) \
__asm__ __volatile__(LOCK "andl %0,%1" \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic_set_mask(mask, addr) \
__asm__ __volatile__(LOCK "orl %0,%1" \
: : "r" (mask),"m" (*addr) : "memory")

#endif
