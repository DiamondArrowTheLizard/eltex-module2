#include "convert.h"

#include <string.h>

int convert_oct_bin(char* octnum, char* binary)
{
    long int i = 0;

    while (octnum[i]) {
        switch (octnum[i]) {
        case '0':
            binary = strcat(binary, "000");
            break;
        case '1':
            binary = strcat(binary, "001");
            break;
        case '2':
            binary = strcat(binary, "010");
            break;
        case '3':
            binary = strcat(binary, "011");
            break;
        case '4':
            binary = strcat(binary, "100");
            break;
        case '5':
            binary = strcat(binary, "101");
            break;
        case '6':
            binary = strcat(binary, "110");
            break;
        case '7':
            binary = strcat(binary, "111");
            break;
        default:
            return CONVERT_BAD;
        }
        i++;
    }

    return CONVERT_OK;
}

int convert_letter_mask_bin(char* mask)
{
    for(size_t i = 1; i < strlen(mask); i++) 
    {
        switch(mask[i])
        {
            case '-':
                mask[i] = '0';
                break;

            case 'r':
            case 'w':
            case 'x':
                mask[i] = '1';
            break;
            
            default:
                return CONVERT_BAD;
        }
    }
    return CONVERT_OK;
}

/* [-1]: - l
 * [0, 3, 6]: - r
 * [1, 4, 7]: - w
 * [2, 5, 8]: - x
*/
static void convert_bin_letter_at(char* mask, size_t index)
{
    switch(index)
    {
        case 0:
        case 3:
        case 6:
            mask[index] = 'r';
            break;

        case 1:
        case 4:
        case 7:
            mask[index] = 'w';
            break;

        case 2:
        case 5:
        case 8:
            mask[index] = 'x';
            break;
    }
}

int convert_bin_letter_mask(char* mask)
{
    for(size_t i = 0; i < strlen(mask); i++) 
    {
        switch(mask[i])
        {
            case '-':
            case 'l':
            case 'd':
            case 'b':
                break;

            case '0':
                mask[i] = '-';
                break;

            case '1':
                convert_bin_letter_at(mask, i);
            break;
            
            default:
                return CONVERT_BAD;
        }
    }
    return CONVERT_OK;
}
