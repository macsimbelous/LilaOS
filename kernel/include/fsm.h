/* Copyright (C) 2004 Белоус Максим Юрьевич. */
#ifndef _FSM_H
#define _FSM_H

struct _file_info_t
{
    unsigned int       dwFileAttributes; 
    unsigned int    ftCreationTime; 
    unsigned int    ftLastAccessTime; 
    unsigned int    ftLastWriteTime; 
    unsigned int       nFileSizeHigh; 
    unsigned int       nFileSizeLow; 
    unsigned int       dwReserved0; 
    unsigned int       dwReserved1; 
    char        cFileName[ 255 ]; 
};
typedef struct _file_info_t file_info_t;

struct _fs_info_t
{
    void * (*create_file)(const char * file_path, unsigned int open_mode, unsigned int share_mode, unsigned int creation_disposition, unsigned int flags);
    unsigned int (*close_file)(void * file);
    unsigned int (*set_file_pointer)(void * file, unsigned int new_pos, unsigned int move_method);
    unsigned int (*get_file_pointer)(void * file);
    unsigned int (*read_file)(void * file, unsigned int no_of_bytes, void * buffer);
    unsigned int (*write_file)(void * file, unsigned int no_of_bytes, void * buffer);

    unsigned int (*delete_file)(const char * file_name);
    unsigned int (*move_file)(const char * in_file_name, const char * out_file_name);
    unsigned int (*get_file_attributes)(const char * file_name, file_info_t * finfo);
    
    void * (*find_first_file)(const char * file_name, file_info_t * finfo);
    unsigned int (*find_next_file)(void * file, file_info_t * finfo);
    unsigned int (*find_close)(void * file);
}; 
typedef struct _fs_info_t fs_info_t;

void init_fsm();

#endif /* _FSM_H */

