/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _IRQ_H
#define _IRQ_H

int set_handler_irq(void *handler, unsigned char number);
int unset_handler_irq(unsigned char number);

#endif /* _IRQ_H */