#ifndef PRINT_H
#define PRINT_H

#include <unistd.h>
#include <sys/stat.h>

#define PERMISSION_MASK (S_IRWXU | S_IRWXG | S_IRWXO)

void print_permissions(char* mask);
void print_mask_bin(char* mask);
void print_stat_masks(struct stat stat);
void print_stat_masks_modified(struct stat stat, char* chmod);

#endif // !PRINT_H
