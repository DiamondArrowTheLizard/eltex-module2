#ifndef VALIDATE_H
#define VALIDATE_H

#include <stddef.h>

#define VALIDATE_OK 0
#define VALIDATE_BAD -1

#define MASK_NUMBER_LEN 3
#define MASK_LETTERS_LEN 10

int validate_char_is(char character, const char* symbols_array, size_t array_size);
int validate_lettered_mask(char* mask);
int validate_numbered_mask(char* mask);

#endif // !VALIDATE_H
