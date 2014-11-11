/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _DM_H
#define _DM_H

void init_dm();

struct _device_info_t
{
    unsigned short bus_id;
    unsigned short bus_device_id;
    unsigned short vendor_id;
    unsigned short revision_id;
    unsigned short sub_class_id;
	unsigned short class_id;
	unsigned int sys_device_id;
    int (*device_call)(int function, void * parameters);
    void * next;
}; 
typedef struct _device_info_t device_info_t;

int register_device(device_info_t *device);
int unregister_device(device_info_t *device);
#endif /* _DM_H */

