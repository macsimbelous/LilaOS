/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _CMD_H
#define _CMD_H

int get_option(char *buffer, int size_buffer, const char *option);
void parse_options(char *string);
extern char root[];

#endif /* _CMD_H */
