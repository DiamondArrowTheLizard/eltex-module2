#include "print.h"

#include "convert.h"
#include "validate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void print_permissions(char* mask)
{
    for(size_t i = 1; i < strlen(mask); i++)
    {
        printf("%c", mask[i]);
    }
    printf("\n");
}

void print_mask_bin(char* mask)
{
    if(mask == NULL)
    {
        printf("    Error: mask is empty.\n");
    }
    if(validate_numbered_mask(mask) == CONVERT_OK)
    {
        char* binary_mask = (char*)malloc(10 * sizeof(*binary_mask));
        if(convert_oct_bin(mask, binary_mask) == CONVERT_OK)
        {
            printf("    Mask: %s\n", binary_mask);
        }
        else
        {
            printf("    Error: octal values incorrect in mask %s\n", mask);
        }

        free(binary_mask);
        binary_mask = NULL;
    }
    else if(validate_lettered_mask(mask) == CONVERT_OK)
    {
        if(convert_letter_mask_bin(mask) == CONVERT_OK)
        {
            printf("    Mask: ");
            print_permissions(mask);
        }
        else
        {
            printf("    Error: format is incorrect in mask %s\n", mask);
        }
    }
    else
    {
        printf("    Error: incorrect mask format\n");
    }
}

void print_stat_masks(struct stat stat)
{
    char lettered_mask[MASK_LETTERS_LEN];
    sprintf(lettered_mask, "%b", stat.st_mode & PERMISSION_MASK);
    if(convert_bin_letter_mask(lettered_mask) == CONVERT_OK)
    {
        printf("    Octal: %o\n", stat.st_mode & PERMISSION_MASK);
        printf("    Binary: %b\n", stat.st_mode & PERMISSION_MASK);
        printf("    Lettered: %s\n", lettered_mask);
    }
    else 
    {
        printf("    Error: permissions format incorrect\n");
    }

}
