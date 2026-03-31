#ifndef CONVERT_H
#define CONVERT_H

#define CONVERT_OK 0
#define CONVERT_BAD -1

int convert_oct_bin(char* octnum, char* binary);
int convert_letter_mask_bin(char* mask);
int convert_bin_letter_mask(char* mask);
int convert_chmod_bin_mask(char* chmod, int permission_mask, char* mask);

#endif // !CONVERT_H
