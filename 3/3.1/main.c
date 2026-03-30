#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "print.h"


int main(int argc, char** argv) 
{
    if(argc <= 2)
    {
        printf("Error: too few arguments.\n");
        return 1;
    }
    const char* flag = argv[1];

    switch(flag[1])
    {
        case 'm':
            printf("Mask Translation to binary:\n");
            print_mask_bin(argv[2]);
            break;

        case 'f':
            printf("File permissions:\n");
            struct stat file_stat;
            if (stat(argv[2], &file_stat) == -1) {
                perror("stat");
                return 1;
            }
            print_stat_masks(file_stat);
            break;

        case 'c':
            printf("Change permissions:\n");
            break;

        default:
            printf("Error: unknown flag %s.\n", flag);
            return 1;
    }

    return 0;
}

