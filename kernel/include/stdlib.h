/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _STDLIB_H_
#define _STDLIB_H_

void itostr(char *buf, int base, int integer);
int tonumber(char c);
int isnumber(char c, int base);
int strtoi(char *s, int base, char **scan_end);
int printf(const char *format, ...);

#endif /* _STDLIB_H_ */
