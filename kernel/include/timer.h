/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _TIMER_H
#define _TIMER_H

#include <types.h>

/* Номера портов. */

#define PORT_BASE                0x40
#define PORT_COUNTER_0     (PORT_BASE + 0)
#define PORT_COUNTER_1           (PORT_BASE + 1)
#define PORT_COUNTER_2           (PORT_BASE + 2)
#define MODE_PORT           (PORT_BASE + 3)

/* Каналы. */

#define COUNTER_0        (0)
#define COUNTER_1        (BIT_VALUE (6))
#define COUNTER_2        (BIT_VALUE (7))
#define READ_BACK_COUNTER (BIT_VALUE (7) | BIT_VALUE (6))



/* Порядок доступа. */
#define ACCESS_LOW   (BIT_VALUE (4))
#define ACCESS_HIGH  (BIT_VALUE (5))
#define COUNTER_LATCH_COMMAND   (0)

/* Режимы. */

#define MODE_0           (0)
#define MODE_1           (BIT_VALUE (1))
#define MODE_2           (BIT_VALUE (2))
#define MODE_3           (BIT_VALUE (2) | BIT_VALUE (1))
#define MODE_4           (BIT_VALUE (3))
#define MODE_5           (BIT_VALUE (3) | BIT_VALUE (1))

/* Режимы счётчика. */
#define BINARY_COUNTER          (0)
#define BCD_COUNTER             (BIT_VALUE (0))

/* Чистота системного таймара. */

#define CLOCK_TICK_RATE         1193180

/* Для получения нужного числа тиков делим чистоту таймера на нужное число тиков. */

#define COUNTER_DIVISOR(hz)     (CLOCK_TICK_RATE / hz)

#endif /* !_TIMER_H */
