/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _VIDEO_H_
#define _VIDEO_H_


void init_video();
void clear_video(void);
void move_cursor(unsigned char x, unsigned char y);
void scroll_video(void);
void put_char(const char c);

#endif /* _VIDEO_H_ */

