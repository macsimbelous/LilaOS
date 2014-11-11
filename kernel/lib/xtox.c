/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include <types.h>

int tonumber(char c){
    if (c >= '0' && c <= '9') return(c - '0');
    else if (c >= 'A' && c <= 'F') return(c - 'A' + 10);
    else if (c >= 'a' && c <= 'f') return(c - 'a' + 10);
    else return(c);
}
int isnumber(char c,int base){
    static char *digits = "0123456789ABCDEF";
    if ((c >= '0' && c <= digits[base-1]))
       return(1);
    else return(0);
}

 /* Преобразуйте целое число в строку. */
void itostr(char *buf, int base, int integer){
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = integer;
    int divisor = 10;
    if(base == 'd' && integer < 0)
    {
        *p++ = '-';
        buf++;
        ud = -integer;
    }
    else
    {
        if(base == 'x')
        {
                divisor = 16;
        }
    }

    do
    {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
    while (ud /= divisor);
    *p = 0;
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}
/* Преобразует строку в целое число. */
long int strtoi(char *s, int base, char **scan_end)
{
    int sign,value,overflow = 0;
    long int result = 0,oldresult;
    /* Evaluate sign */
    if (*s == '-') {
	sign = -1;
	s++;
    } else if (*s == '+') {
	sign = 1;
	s++;
    }
    else sign = 1;
    /* Skip trailing zeros */
    while (*s == '0') s++;
    /* Convert number */
    while (isnumber(*s,base)) {
	value = tonumber(*s++);
	if (value > base || value < 0) return(0);
	oldresult = result;
	result *= base;
	result += value;
	/* Detect overflow */
	if (oldresult > result) overflow = 1;
    }
    if (scan_end != 0L) *scan_end = s;
    if (overflow) result = INT_MAX;
    result *= sign;
    return(result);
}

