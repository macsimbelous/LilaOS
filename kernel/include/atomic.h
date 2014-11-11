/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include <config.h>

/*
 * Атомарные неделимые опирации над переменными типа atomic_t.
 */

#ifdef SMP
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

typedef struct { volatile int counter; } atomic_t;

/*
 * atomic_read - Читает атомарную петеменную
 */ 
#define atomic_read(v)		((v)->counter)
    		
/*
 * atomic_set - Устанавливает атомарную переменную
 */ 
#define atomic_set(v,i)		(((v)->counter) = (i))

/*
 * atomic_add - Слаживае атомную переменную с целым числом
 */
static __inline__ void atomic_add(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "addl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/*
 * atomic_sub - Отнимает от атомной переменной целое число
 */
static __inline__ void atomic_sub(int i, atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "subl %1,%0"
		:"=m" (v->counter)
		:"ir" (i), "m" (v->counter));
}

/*
 * atomic_sub_and_test - Отнимает от атомной переменной челое число и проверяет результат
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
 * atomic_inc - Увеличивает на 1 атомную переменную
 */ 
static __inline__ void atomic_inc(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/*
 * atomic_dec - Уменьшае на 1 атомную переменную
 */ 
static __inline__ void atomic_dec(atomic_t *v)
{
	__asm__ __volatile__(
		LOCK "decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

/*
 * atomic_dec_and_test - Уменьшает на 1 атомную переменную и проверяет результат
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
 * atomic_inc_and_test - Увельчивает на 1 атомную переменную и проверяет результат 
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
 * atomic_add_negative - Слаживает атомную переменную с челым числом и проверяет результат
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
