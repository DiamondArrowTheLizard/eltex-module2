#include "convert.h"
#include "validate.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

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

static void convert_r(char* mask, char perm_part, char bit)
{
    switch(perm_part)
    {
        case 'u':
            mask[0] = bit;
            break;

        case 'g':
            mask[3] = bit;
            break;

        case 'a':
            mask[6] = bit;
            break;

        default:
            mask[0] = bit;
            mask[3] = bit;
            mask[6] = bit;
            break;
    }
}

static void convert_w(char* mask, char perm_part, char bit)
{
    switch(perm_part)
    {
        case 'u':
            mask[1] = bit;
            break;

        case 'g':
            mask[4] = bit;
            break;

        case 'a':
            mask[7] = bit;
            break;

        default:
            mask[1] = bit;
            mask[4] = bit;
            mask[7] = bit;
            break;
    }
}

static void convert_x(char* mask, char perm_part, char bit)
{
    switch(perm_part)
    {
        case 'u':
            mask[2] = bit;
            break;

        case 'g':
            mask[5] = bit;
            break;

        case 'a':
            mask[8] = bit;
            break;

        default:
            mask[2] = bit;
            mask[5] = bit;
            mask[8] = bit;
            break;
    }
}

static int parse_chmod(char* chmod, char* mask, char perm_part, char bit)
{
    int passed_r = 0;
    int passed_w = 0;
    int passed_x = 0;

    for(size_t i = 1; i < strlen(chmod); i++)
    {
        switch(chmod[i])
        {
            case '+':
            case '-':
                break;

            case 'r':
                if (passed_r == 0) 
                {
                    passed_r = 1; 
                    convert_r(mask, perm_part, bit);
                    break;
                }
                else return CONVERT_BAD;

            case 'w':
                if (passed_w == 0) 
                {
                    convert_w(mask, perm_part, bit);
                    passed_w = 1; 
                    break;
                }
                else return CONVERT_BAD;

            case 'x':
                if (passed_x == 0)  
                {
                    passed_x = 1;
                    convert_x(mask, perm_part, bit);
                    break;
                }
                else return CONVERT_BAD;

            default:
                printf("    Parse error: bad symbol %c\n", chmod[i]);
                return CONVERT_BAD;
        }
    }
    return CONVERT_OK;
}

int convert_chmod_bin_mask(char* chmod, int permission_mask, char* mask)
{
    sprintf(mask, "%b", permission_mask);
    printf("Mask: %s\n", mask);
    char perm_part = ' ';
    switch(chmod[0])
    {
        case '+':
            if( parse_chmod(chmod, mask, perm_part, '1') == CONVERT_BAD)
            {
                printf("    Parse error: bad chmod %s\n", chmod);
                return CONVERT_BAD;
            }
            break;

        case '-':
            parse_chmod(chmod, mask, perm_part, '0');
            break;

        case 'u':
            perm_part = chmod[0];
            switch(chmod[1])
            {
                case '+':
                    if( parse_chmod(chmod, mask, perm_part, '1') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    break;

                case '-':
                    printf("Mask %s\n", mask);
                    if( parse_chmod(chmod, mask, perm_part, '0') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    printf("Mask %s\n", mask);
                    break;

                default:
                    printf("    Convert error: bad symbol [%c]\n", chmod[1]);
                    return CONVERT_BAD;
            }
            break;

        case 'g':
            perm_part = chmod[0];
            switch(chmod[1])
            {
                case '+':
                    if( parse_chmod(chmod, mask, perm_part, '1') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    break;

                case '-':
                    if( parse_chmod(chmod, mask, perm_part, '0') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    break;

                default:
                    printf("    Convert error: bad symbol [%c]\n", chmod[1]);
                    return CONVERT_BAD;
            }
            break;

        case 'a':
            perm_part = chmod[0];
            switch(chmod[1])
            {
                case '+':
                    if( parse_chmod(chmod, mask, perm_part, '1') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    break;

                case '-':
                    if( parse_chmod(chmod, mask, perm_part, '0') == CONVERT_BAD)
                    {
                        printf("    Parse error: bad chmod %s\n", chmod);
                        return CONVERT_BAD;
                    }
                    break;

                default:
                    printf("    Convert error: bad symbol [%c]\n", chmod[1]);
                    return CONVERT_BAD;
            }
            break;

        default:
            printf("    Convert error: bad symbol [%c]\n", chmod[0]);
            return CONVERT_BAD;
    }


    return CONVERT_OK;  
}
