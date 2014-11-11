/* Copyright (C) 2003 Белоус Максим Юрьевич. */
#include <dm.h>
#include <stdlib.h>
#include <ints.h>
#include <types.h>
device_info_t *devices;

void init_dm(){
    devices = NULL;
    printf("Device manager init\n");
}

int register_device(device_info_t *device){
    device_info_t *temp;
    if(device->device_call == NULL)
        return 1;
    device->sys_device_id = ((unsigned int)device->bus_id <<16) & (unsigned int)device->bus_device_id;
    device->next = NULL;
    disable_ints();
    if(devices == NULL){
        devices = device;
        enable_ints();
        return 0;
    }
    temp = devices;
    while(temp){
        if(temp->next == NULL)
                break;
        temp = temp->next;
    }
    temp->next = device;
    enable_ints();
    return 0;
}

int unregister_device(device_info_t *device){
    return 1;
}

