/* Copyright (C) 2004 Белоус Максим Юрьевич. */

#include "video.h"
#include "stdlib.h"

/* Вывод на экран форматированной строки текста */
int printf(const char *format, ...)
{
    char **arg = (char **) &format;
    int c;
    char buffer[20];
    arg++;
    while ((c = *format++) != 0)
    {
        if (c != '%')
        {
                put_char(c);
        }
        else
        {
                char *p;
                c = *format++;
                switch(c)
                {
                                case 'd':
                                case 'u':
                                case 'x':
                                itostr(buffer, c, *((int *) arg++));
                                p = buffer;
                                goto string;
                                break;
                                case 's':
                                p = *arg++;
                                if (! p)
                                {
                                    p = "(null)";
                                }
                                string:
                                while (*p)
                                {
                                    put_char(*p++);
                                }
                                break;
                                default:
                                put_char(*((int *) arg++));
                                break;
                }
        }
    }
	return 0;
}

