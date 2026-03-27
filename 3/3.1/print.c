#include "print.h"

#include "convert.h"
#include "validate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

