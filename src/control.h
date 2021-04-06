#ifndef CONTROL_H
#define CONTROL_H 1
/*
    this file implemment the algorithm of scheduling between disk and pmem
*/
#include "util.h"

void control_init(TOID(struct DirectoryTree)* root, const char* pool_file_name,const char* root_path);
int isFlushLoad(TOID(struct DirectoryTree) node);
void flush_load(TOID(struct DirectoryTree)* root);

int write_to_pmem_disk(TOID(struct DirectoryTree)* node, const char* path, 
                    const char* buffer, size_t size, off_t offset);
int read_from_pmem_disk(TOID(struct DirectoryTree), const char*, char*, size_t, off_t);
#endif