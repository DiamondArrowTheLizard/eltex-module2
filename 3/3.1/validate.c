#include "validate.h"
#include <ctype.h>
#include <string.h>

int validate_numbered_mask(char* mask)
{
    if(strlen(mask) != MASK_NUMBER_LEN)
    {
        return VALIDATE_BAD;
    }
    for(size_t i = 0; i < MASK_NUMBER_LEN; i++)
    {
        if(!isdigit(mask[i]))
        {
            return VALIDATE_BAD;
        }
    }
    return VALIDATE_OK;
}

int validate_char_is(char character, const char* symbols_array, size_t array_size)
{
    for(size_t i = 0; i < array_size; i++)
    {
        if(character == symbols_array[i]) return VALIDATE_OK;
    }
    return VALIDATE_BAD;
}

/* [0]: - l
 * [1, 4, 7]: - r
 * [2, 5, 8]: - w
 * [3, 6, 9]: - x
*/
int validate_lettered_mask(char* mask)
{
    if(strlen(mask) != MASK_LETTERS_LEN)
    {
        return VALIDATE_BAD;
    }

    const char* symlink = "-ldb";
    const char* read = "-r";
    const char* write = "-w";
    const char* execute = "-x";
    if(
    validate_char_is(mask[0], symlink, 4) == VALIDATE_OK &&

    validate_char_is(mask[1], read, 2) == VALIDATE_OK &&
    validate_char_is(mask[4], read, 2) == VALIDATE_OK &&
    validate_char_is(mask[7], read, 2) == VALIDATE_OK &&


    validate_char_is(mask[2], write, 2) == VALIDATE_OK &&
    validate_char_is(mask[5], write, 2) == VALIDATE_OK &&
    validate_char_is(mask[8], write, 2) == VALIDATE_OK &&


    validate_char_is(mask[3], execute, 2) == VALIDATE_OK &&
    validate_char_is(mask[6], execute, 2) == VALIDATE_OK &&
    validate_char_is(mask[9], execute, 2) == VALIDATE_OK)
    {
        return VALIDATE_OK;
    }

    else return VALIDATE_BAD;
}
