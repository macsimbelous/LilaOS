#ifndef _BITOPS_H
#define _BITOPS_H

#ifdef _SMP_
#define LOCK "lock ; "
#else
#define LOCK ""
#endif

#define ADDR (*(volatile long *) addr)

/* set_bit - устанавливает бит. */
static __inline__ void set_bit(int nr, volatile void * addr)
{
	__asm__ __volatile__( LOCK
		"btsl %1,%0"
		:"=m" ((*(volatile long *) addr))
		:"Ir" (nr));
}

/* clear_bit - отчищает бит. */
static __inline__ void clear_bit(int nr, volatile void * addr)
{
	__asm__ __volatile__( LOCK
		"btrl %1,%0"
		:"=m" ((*(volatile long *) addr))
		:"Ir" (nr));
}

/* change_bit - инвертирует бит. */
static __inline__ void change_bit(int nr, volatile void * addr)
{
	__asm__ __volatile__( LOCK
		"btcl %1,%0"
		:"=m" ((*(volatile long *) addr))
		:"Ir" (nr));
}

/* test_and_set_bit - проверяет и устанавливает бит. */
static __inline__ int test_and_set_bit(int nr, volatile void * addr)
{
	int oldbit;

	__asm__ __volatile__( LOCK
		"btsl %2,%1\n\tsbbl %0,%0"
		:"=r" (oldbit),"=m" ((*(volatile long *) addr))
		:"Ir" (nr) : "memory");
	return oldbit;
}

/* test_and_clear_bit - прверяет и очищает бит. */
static __inline__ int test_and_clear_bit(int nr, volatile void * addr)
{
	int oldbit;

	__asm__ __volatile__( LOCK
		"btrl %2,%1\n\tsbbl %0,%0"
		:"=r" (oldbit),"=m" ((*(volatile long *) addr))
		:"Ir" (nr) : "memory");
	return oldbit;
}

/* test_and_change_bit - устанавливает и инвертирует бит. */
static __inline__ int test_and_change_bit(int nr, volatile void * addr)
{
	int oldbit;

	__asm__ __volatile__( LOCK
		"btcl %2,%1\n\tsbbl %0,%0"
		:"=r" (oldbit),"=m" ((*(volatile long *) addr))
		:"Ir" (nr) : "memory");
	return oldbit;
}

/* test_bit - проверяет бит. */
static __inline__ int test_bit(int nr, volatile void * addr)
{
	int oldbit;

	__asm__ __volatile__(
		"btl %2,%1\n\tsbbl %0,%0"
		:"=r" (oldbit)
		:"m" ((*(volatile long *) addr)),"Ir" (nr));
	return oldbit;
}

/* find_first_zero_bit - ищет первый нулквой бит. */
static __inline__ int find_first_zero_bit(void * addr, unsigned size)
{
	int d0, d1, d2;
	int res;

	if (!size)
		return 0;
	__asm__ __volatile__(
		"movl $-1,%%eax\n\t"
		"xorl %%edx,%%edx\n\t"
		"repe; scasl\n\t"
		"je 1f\n\t"
		"xorl -4(%%edi),%%eax\n\t"
		"subl $4,%%edi\n\t"
		"bsfl %%eax,%%edx\n"
		"1:\tsubl %%ebx,%%edi\n\t"
		"shll $3,%%edi\n\t"
		"addl %%edi,%%edx"
		:"=d" (res), "=&c" (d0), "=&D" (d1), "=&a" (d2)
		:"1" ((size + 31) >> 5), "2" (addr), "b" (addr));
	return res;
}

/* find_next_zero_bit - ишет следуюший нулевой бит. */
static __inline__ int find_next_zero_bit(void * addr, int size, int offset)
{
	unsigned long * p = ((unsigned long *) addr) + (offset >> 5);
	int set = 0, bit = offset & 31, res;
	
	if (bit) {
		__asm__("bsfl %1,%0\n\t"
			"jne 1f\n\t"
			"movl $32, %0\n"
			"1:"
			: "=r" (set)
			: "r" (~(*p >> bit)));
		if (set < (32 - bit))
			return set + offset;
		set = 32 - bit;
		p++;
	}
	res = find_first_zero_bit (p, size - 32 * (p - (unsigned long *) addr));
	return (offset + set + res);
}

#endif /* _BITOPS_H */
