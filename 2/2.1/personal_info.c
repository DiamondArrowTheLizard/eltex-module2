#include "personal_info.h"
#include <stddef.h>
#include <stdlib.h>

personal_info* personal_info_create(char* name, char* surname)
{
    personal_info* info = (personal_info*)malloc(sizeof(*info));

    info->name = name;
    info->surname = surname;
    info->patronymic = NULL;

    info->workplace = NULL;
    info->position = NULL;

    info->phone_numbers = NULL;
    info->links = NULL;

    return info;
}

void personal_info_clear_array(char** array)
{
    for(size_t i = 0; i < sizeof(array); i++)
    {
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
    array = NULL;
}

void personal_info_destroy(personal_info* info)
{
    free(info->name);
    info->name = NULL;
    free(info->surname);
    info->surname = NULL;
    free(info->patronymic);
    info->patronymic = NULL;


    free(info->workplace);
    info->workplace = NULL;
    free(info->position);
    info->position = NULL;

    personal_info_clear_array(info->phone_numbers);
    personal_info_clear_array(info->links);
}

void personal_info_update_field(char* old_field, char* new_field)
{
    free(old_field);
    old_field = NULL;

    old_field = new_field;
}

void personal_info_new_name(personal_info* info, char* name)
{
    personal_info_update_field(info->name, name);
}

void personal_info_new_surname(personal_info* info, char* surname)
{
    personal_info_update_field(info->surname, surname);
}

void personal_info_new_patronymic(personal_info* info, char* patronymic)
{
    personal_info_update_field(info->patronymic, patronymic);
}

void personal_info_new_workplace(personal_info* info, char* workplace)
{
    personal_info_update_field(info->workplace, workplace);
}

void personal_info_new_position(personal_info* info, char* position)
{
    personal_info_update_field(info->position, position);
}

void personal_info_new_phone_numbers(personal_info* info, char** phone_numbers)
{
    personal_info_clear_array(info->phone_numbers);

    info->phone_numbers = phone_numbers;
}

void personal_info_new_links(personal_info* info, char** links)
{
    personal_info_clear_array(info->links);

    info->links = links;
}
