/* Copyright (C) 2004 Белоус Максим Юрьевич. */

#include <string.h>
#include <stdlib.h>
#define SIZE_BUFFER 256
int get_option(char *buffer, int size_buffer, const char *option);

static const char command_lile[4096];
char root[5];

void parse_options(char *string){
    char buffer[SIZE_BUFFER];
    strncpy((char *)command_lile, string, 4096);
    if(!get_option(buffer, 5, "root="))
        strcpy(root, "hda0");
    else
        strncpy(root, buffer, 4);
    return;
    }
int get_option(char *buffer, int size_buffer, const char *option){
    char *tmp;
    int i;
    tmp=strstr(command_lile, option);
    if(tmp==0)
        return 0;
    tmp+=strlen(option);
    for(i=0; i<size_buffer; i++){
        if(tmp[i]==' ' || tmp[i]=='\0'){
                buffer[i]='\0';
                if(i==0)
                    return 0;
                return 1;
        }
        buffer[i]=tmp[i];
    }
    return 0;
}

