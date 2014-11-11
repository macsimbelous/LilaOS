/* Copyright (C) 2004 */

#ifndef _SHARED_
#define _SHARED_	1

#define HAVE_ASM_USCORE 1

#ifdef HAVE_ASM_USCORE
# define EXT_C(sym) _ ## sym
#else
# define EXT_C(sym) sym
#endif

#define MAX_CMDLINE 4096

#define CR0_PE_ON	0x1
#define CR0_PE_OFF	0xfffffffe
#define PROT_MODE_CSEG	0x8
#define PROT_MODE_DSEG  0x10
#define PSEUDO_RM_CSEG	0x18
#define PSEUDO_RM_DSEG	0x20
#define STACKOFF	(0x2000)
#define PROTSTACKINIT   (0x7C00)
#define REALSTACK   0x2000


/*
 * Assembly code defines
 *
 * "EXT_C" is assumed to be defined in the Makefile by the configure
 *   command.
 */

#define ENTRY(x) .globl EXT_C(x) ; EXT_C(x):
#define VARIABLE(x) ENTRY(x)


#ifndef ASM_FILE

#undef NULL
#define NULL         ((void *) 0)

/* Reboot the system.  */
void reboot (void) __attribute__ ((noreturn));



/* memory probe routines */
int get_memsize (int type);

/* Return the data area immediately following our code. */
int get_code_end (void);

int read_disk(int drive, int addr, int sectors, int *buffer);
int write_disk(int drive, int addr, int sectors, int *buffer);



int getrtsecs (void);
int currticks (void);



#endif /* ASM_FILE */

#endif /* _SHARED_ */
