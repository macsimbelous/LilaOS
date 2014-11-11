/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _STRING_H_
#define _STRING_H_
char *strcpy(char *dst,const char *src);
char *strncpy(char *dst,const char *src,int n);
int strcmp(const char *s1,const char *s2);
int strncmp(const char *s1,const char *s2,int n);
int stricmp(const char *string1, const char *string2);
char *strupr(char *s);
char *strlwr(char *s);
int strlen(const char *s);
char *strcat(char *dst,char *src);
char *strscn(char *s,char *pattern);
char *strchr(char *s,int c);
char *strnchr(const char *string, int c,unsigned int count);
char *strncat(char *dest, const char *src, int n);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
void *memset(void *dest, int c, unsigned int count);
void *memcpy(void *dest, const void *src, unsigned int count);
void *memmove(void *dest, const void *src, unsigned int count);
int memcmp(const void *buf1, const void *buf2, unsigned int count);
void *memchr(const void *buf, int c, unsigned int count);
void *memccpy(void *dest, const void *src, int c, unsigned int count);


#endif
