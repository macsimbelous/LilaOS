/* Copyright (C) 2004 Белоус Максим Юрьевич. */

#include <video.h>
#include <string.h>
#include <io.h>
/* количество символов в строке */
#define COLUMNS			80
/* номер последней строки */
#define LINES			25
/* VGA регистры. */
#define VGA_CRT_ADDRESS 0x3D4
#define VGA_CRT_DATA    0x3D5
#define VGA_CRT_CURSOR_H_LOCATION 0x0E
#define VGA_CRT_CURSOR_L_LOCATION 0x0F
/* адрес видео памяти */
#define VIDEO			0xB8000
/* позиция по X */
static int position_x;
/* позиция по Y */
static int position_y;
/* указатель на видео память */
static unsigned char *video_memory;

void init_video(){
	video_memory = (unsigned char *) VIDEO;
	clear_video();
	}
/* очищяет экран */
void clear_video(void){
    int i;
    for (i = 0; i < COLUMNS * LINES * 2; i+=2)
    {
        *(video_memory + i) = 0;
    }
	move_cursor(0, 0);
}
/* Перемещает курсор в указанные координаты. */
void move_cursor(unsigned char x, unsigned char y){
    unsigned short offset=(y*COLUMNS)+(x);
    if ( x >= COLUMNS || y >= LINES )
        return;
	position_x=x;
	position_y=y;
    
    outb(VGA_CRT_ADDRESS, VGA_CRT_CURSOR_H_LOCATION);
    outb(VGA_CRT_DATA, offset>>8);
    outb(VGA_CRT_ADDRESS, VGA_CRT_CURSOR_L_LOCATION);
    outb(VGA_CRT_DATA, (offset<<8)>>8);
}
/* Прокручивает экран на одну строку. */
void scroll_video(){
	int i;
	memcpy( video_memory, video_memory + COLUMNS * 2, ( LINES - 1 ) * COLUMNS * 2 );
	for ( i = ( LINES - 1 ) * COLUMNS * 2; i < LINES * COLUMNS * 2; i += 2 )
		video_memory[i] = ' ';
}
/* Выводит символ в текущюю позицию курсора. */
void put_char(const char c){
	if (c == '\n'){
		position_x = 0;
		if ( ++position_y >= LINES ){
			scroll_video();
			position_y--;
		}
	} else if (c == '\r'){
		position_x = 0;
	} else if (c == '\t'){
		put_char(' ');
		put_char(' ');
		put_char(' ');
		put_char(' ');
		put_char(' ');
		put_char(' ');
		put_char(' ');
		put_char(' ');
	} else if (c == '\v'){
		switch (position_x % 8){
		case 0:
			put_char(' ');
		case 7:
			put_char(' ');
		case 6:
			put_char(' ');
		case 5:
			put_char(' ');
		case 4:
			put_char(' ');
		case 3:
			put_char(' ');
		case 2:
			put_char(' ');
		case 1:
			put_char(' ');
		}
	} else {
		video_memory [ ( position_x + COLUMNS * position_y ) * 2 ] = c;
		if ( ++position_x >= COLUMNS ){
			position_x = 0;
			if ( ++position_y >= LINES ){
				scroll_video();
				position_y--;
			}
		}
	}
	move_cursor(position_x, position_y);
}

