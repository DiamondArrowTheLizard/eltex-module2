#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

typedef struct personal_info
{
    char* name;
    char* surname;
    char* patronymic;

    char* workplace;
    char* position;

    char** phone_numbers;
    char** links;

} personal_info;

personal_info* personal_info_create(char* name, char* surname);
void personal_info_clear_array(char** array);
void personal_info_destroy(personal_info* info);

void personal_info_update_field(char* old_field, char* new_field);

void personal_info_new_name(personal_info* info, char* name);
void personal_info_new_surname(personal_info* info, char* surname);
void personal_info_new_patronymic(personal_info* info, char* patronymic);
void personal_info_new_workplace(personal_info* info, char* workplace);
void personal_info_new_position(personal_info* info, char* position);
void personal_info_new_phone_numbers(personal_info* info, char** phone_numbers);
void personal_info_new_links(personal_info* info, char** links);

#endif // !PERSONAL_INFO_H
