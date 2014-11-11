/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#include <timer.h>
#include <io.h>

#include <ints.h>
int printf(const char *format, ...);

/* Число тиков. */
static unsigned int ticks=1000;

void timer(int number){

    outb(0x20, 0x20);
    return;
    }

/* Прорецедура инициализации системного таймера. */
void init_timer(){
    
    outb(MODE_PORT, (COUNTER_0 | ACCESS_LOW | ACCESS_HIGH | MODE_3 | BINARY_COUNTER));
    outb(PORT_COUNTER_0, LOW_U8 (COUNTER_DIVISOR (ticks)));
    outb(PORT_COUNTER_0, HIGH_U8 (COUNTER_DIVISOR (ticks)));
    set_handler_irq(timer, 0);
    printf("Init Timer\n"); 
}
