#include "personal_info.h"
#include "string_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

personal_info* personal_info_create(char* name, char* surname)
{
    personal_info* info = (personal_info*)malloc(sizeof(*info));

    info->name = (char*)malloc(strlen(name) + 1);
    if(info->name) strncpy(info->name, name, strlen(name));

    info->surname = (char*)malloc(strlen(surname) + 1);
    if(info->surname) strncpy(info->surname, surname, strlen(surname));

    info->patronymic = NULL;
    info->workplace = NULL;
    info->position = NULL;
    info->phone_numbers = NULL;
    info->links = NULL;

    return info;
}

void personal_info_clear_field(char* field)
{
    if(field == NULL) return;
    free(field);
    field = NULL;
}

void personal_info_destroy(personal_info* info)
{
    if(info == NULL) return;

    personal_info_clear_field(info->name);
    personal_info_clear_field(info->surname);
    personal_info_clear_field(info->patronymic);

    personal_info_clear_field(info->workplace);
    personal_info_clear_field(info->position);
    
    string_array_destroy(info->phone_numbers);
    string_array_destroy(info->links);

    free(info);
    info = NULL;
}

void personal_info_update_field(char* old_field, char* new_field)
{
    if(old_field != NULL)
    {
        free(old_field);
        old_field = NULL;
    }

    old_field = (char*)malloc(strlen(new_field) + 1); 
    if(old_field) strncpy(old_field, new_field, strlen(new_field));
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

void personal_info_new_phone_numbers(personal_info* info, string_array* phone_numbers)
{
    string_array_destroy(info->phone_numbers);
    info->phone_numbers = phone_numbers;
}

void personal_info_new_links(personal_info* info, string_array* links)
{
    string_array_destroy(info->links);
    info->links = links;
}

void personal_info_print_field(char* field_name, char* field)
{
    if(field == NULL) return;
    printf("%s: %s\n", field_name, field);
}

void personal_info_print_array(char* field_name, string_array* array)
{
    if(array == NULL) return;
    printf("%s:\n", field_name);
    for(size_t i = 0; i < array->count; i++)
    {
        printf("    %s\n", array->strings[i]);
    }
}

void personal_info_print_all(personal_info* info)
{
    personal_info_print_field("Name", info->name);
    personal_info_print_field("Surname", info->surname);
    personal_info_print_field("Patronymic", info->patronymic);

    personal_info_print_field("Workplace", info->workplace);
    personal_info_print_field("Position",  info->position);

    personal_info_print_array("Phone Numbers", info->phone_numbers);
    personal_info_print_array("Links", info->links);
}
