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
    if(info->name) strcpy(info->name, name);

    info->surname = (char*)malloc(strlen(surname) + 1);
    if(info->surname) strcpy(info->surname, surname);

    info->patronymic = NULL;
    info->workplace = NULL;
    info->position = NULL;
    info->phone_numbers = NULL;
    info->links = NULL;

    return info;
}

void personal_info_destroy(personal_info* info)
{
    if(info == NULL) return;

    free(info->name);
    free(info->surname);
    free(info->patronymic);
    free(info->workplace);
    free(info->position);

    string_array_destroy(info->phone_numbers);
    string_array_destroy(info->links);

    info->name = NULL;
    info->surname = NULL;
    info->patronymic = NULL;
    info->workplace = NULL;
    info->position = NULL;

    info->phone_numbers = NULL;
    info->links = NULL;

    free(info);
    info = NULL;
}

void personal_info_new_name(personal_info* info, char* name)
{
    if(info->name) free(info->name);
    info->name = (char*)malloc(strlen(name) + 1);
    if(info->name) strcpy(info->name, name);
}

void personal_info_new_surname(personal_info* info, char* surname)
{
    if(info->surname) free(info->surname);
    info->surname = (char*)malloc(strlen(surname) + 1);
    if(info->surname) strcpy(info->surname, surname);
}

void personal_info_new_patronymic(personal_info* info, char* patronymic)
{
    if(info->patronymic) free(info->patronymic);
    info->patronymic = (char*)malloc(strlen(patronymic) + 1);
    if(info->patronymic) strcpy(info->patronymic, patronymic);
}

void personal_info_new_workplace(personal_info* info, char* workplace)
{
    if(info->workplace) free(info->workplace);
    info->workplace = (char*)malloc(strlen(workplace) + 1);
    if(info->workplace) strcpy(info->workplace, workplace);
}

void personal_info_new_position(personal_info* info, char* position)
{
    if(info->position) free(info->position);
    info->position = (char*)malloc(strlen(position) + 1);
    if(info->position) strcpy(info->position, position);
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
