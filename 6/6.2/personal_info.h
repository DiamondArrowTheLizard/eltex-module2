#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

#include "string_array.h"
#include <stddef.h>

typedef struct personal_info
{
    char* name;
    char* surname;
    char* patronymic;

    char* workplace;
    char* position;

    string_array* phone_numbers;
    string_array* links;

} personal_info;

personal_info* personal_info_create(char* name, char* surname);
void personal_info_destroy(personal_info* info);

void personal_info_new_name(personal_info* info, char* name);
void personal_info_new_surname(personal_info* info, char* surname);
void personal_info_new_patronymic(personal_info* info, char* patronymic);
void personal_info_new_workplace(personal_info* info, char* workplace);
void personal_info_new_position(personal_info* info, char* position);
void personal_info_new_phone_numbers(personal_info* info, string_array* phone_numbers);
void personal_info_new_links(personal_info* info, string_array* links);

void personal_info_print_field(char* field_name, char* field);
void personal_info_print_array(char* array_name, string_array* array);
void personal_info_print_all(personal_info* info);

#endif // !PERSONAL_INFO_H
