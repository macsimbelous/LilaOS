/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include "string.h"
#include "ctype.h"
#include "types.h"
char *strcpy(char *dst,const char *src)
{
    char *retval = dst;
    while (*src != 0) *dst++ = *src++;
    *dst = 0;
    return(retval);
}

char *strncpy(char *dst,const char *src,int n)
{
    char *retval = dst;
    while (*src != 0 && n-- > 0) *dst++ = *src++;
    *dst = 0;
    return(retval);
}

int strcmp(const char *s1,const char *s2)
{
    while (*s1 == *s2) {
	if (*s1 == 0) return 0;
	s1++;
	s2++;
    }
    return *(unsigned const char *)s1 - *(unsigned const char *)(s2);
}

int strncmp(const char *s1,const char *s2,int n)
{
    if (n == 0) return 0;
    do {
	if (*s1 != *s2++)
	    return *(unsigned const char *)s1 - *(unsigned const char *)--s2;
	if (*s1++ == 0) break;
    } while (--n != 0);
    return 0;
}
int stricmp(const char *string1, const char *string2)
{
  int result = 0;
  while((toupper(*string1) == toupper(*string2)) && (!result))
  {
    if(!(*string1) || !(*string2))
    {
      result = 1;
    } else {
      string1++;
      string2++;
    }
  }
  result = 0;
  if(*string1 != *string2)
  {
    result = 1;
    if(toupper(*string1) < toupper(*string2))
    {
      result = -1;
    }
  }
  return(result);
}
char *strupr(char *s)
{
    char *base = s;
    while (*s != 0) {
	if (*s >= 'a' && *s <= 'z')
           *s = *s + 'A' -'a';
	s++;
    }
    return(base);
}

char *strlwr(char *s)
{
    char *base = s;
    while (*s != 0) {
	if (*s >= 'A' && *s <= 'Z')
	   *s = *s + 'a' -'A';
	s++;
    }
    return(base);
}

int strlen(const char *s)
{
    register int result = 0;
    while (*s != 0) s++ , result++;
    return(result);
}

char *strcat(char *dst,char *src)
{
    char *base = dst;
    while (*dst != 0) dst++;
    while (*src != 0) *dst++ = *src++;
    *dst = 0;
    return(base);
}

char *strscn(char *s,char *pattern)
{
    char *scan;
    while (*s != 0) {
    	scan = pattern;
    	while (*scan != 0) {
	    if (*s == *scan) return(s);
	    else scan++;
	}
	s++;
    }
    return(NULL);
}
char *strnchr(const char *string, int c,unsigned int count)
{
  char *p = NULL;
  while(*string && count > 0)
  {
    if((int)(*string) == c)
    {
      p = (char *)string;
      break;
    }
    string++;
    count--;
  }
  return(p);
}
char *strchr(char *s,int c)
{
    while (*s != 0) {
	if (*s == (char)(c)) return(s);
	else s++;
    }
    return(NULL);
}
/*
 * Concatenate src on the end of dst.  At most strlen(dst)+n+1 bytes
 * are written at dst (at most n+1 bytes being appended).  Return dst.
 */
char *strncat(char *dest, const char *src, int n)
{
	if (n != 0) {
		char *d = dest;
		const char *s = src;

		while (*d != 0)
			d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return (dest);
}
char *strrchr(const char *s, int c)
{
	char *save;

	for (save = NULL; *s != 0; s++)
		if (*s == c)
			save = (char *)s;

	return save;
}
char *strstr(const char *haystack, const char *needle)
{
	int hlen;
	int nlen;

	hlen = strlen((char *)haystack);
	nlen = strlen((char *)needle);
	while (hlen >= nlen)
	{
		if (!memcmp(haystack, needle, nlen))
			return (char *)haystack;

		haystack++;
		hlen--;
	}
	return 0;
}
void *memset(void *dest, int c, unsigned int count)
{
  char *p = dest;
  while(count)
  {
    *p = (char)c;
    p++;
    count--;
  }
  return(dest);
}
void *memcpy(void *dest, const void *src, unsigned int count)
{
  char *p1, *p2;
  p1 = (char *)src;
  p2 = (char *)dest;
  while(count)
  {
    *p2 = *p1;
    p1++;
    p2++;
    count--;
  }
  return(dest);
}

void *memmove(void *dest, const void *src, unsigned int count)
{
  char *p1, *p2;
  if(src != dest)
  {
    p1 = (char *)src;
    p2 = (char *)dest;
    if(dest > src)
    {
      p1 += (count - 1);
      p2 += (count - 1);
      while(count)
      {
        *p2 = *p1;
        p1--;
        p2--;
        count--;
      }
    } else {
      while(count)
      {
        *p2 = *p1;
        p1++;
        p2++;
        count--;
      }
    }
  }
  return(dest);
}

int memcmp(const void *buf1, const void *buf2, unsigned int count)
{
  char *p1, *p2;
  int result = 0;
  p1 = (char *)buf1;
  p2 = (char *)buf2;
  while(count)
  {
    if(*p1 != *p2)
    {
      result = 1;
      if(*p1 < *p2)
      {
        result = -1;
      }
      break;
    }
    p1++;
    p2++;
    count--;
  }
  return(result);
}

void *memchr(const void *buf, int c, unsigned int count)
{
  char *p1 = NULL;
  char *p2;
  p2 = (char *)buf;
  while(count)
  {
    if((int)(*p2) == c)
    {
      p1 = p2;
      break;
    }
    p2++;
    count--;
  }
  return(p1);
}

void *memccpy(void *dest, const void *src, int c, unsigned int count)
{
  char *p1, *p2;
  p1 = (char *)src;
  p2 = (char *)dest;
  while(count)
  {
    *p2 = *p1;
    if(*p2 == (char)c)
    {
      dest = (p2 + 1);
      break;
    }
    p2++;
    p1++;
    count--;
  }
  return(dest);
}
