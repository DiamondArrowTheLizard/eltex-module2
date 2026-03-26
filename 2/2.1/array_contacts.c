#include "array_contacts.h"
#include "personal_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

array_contacts* array_contacts_init()
{
    array_contacts* array = (array_contacts*)malloc(sizeof(*array));
    array->contacts = malloc(ARRAY_CONTACTS_INIT_CAPACITY * sizeof(*array->contacts));
    array->count = 0;
    array->capacity = ARRAY_CONTACTS_INIT_CAPACITY;
    return array;
}

void array_contacts_destroy(array_contacts* array)
{ if(array == NULL) return;

    for(size_t i = 0; i < array->count; i++)
    {
        personal_info_destroy(array->contacts[i]);
    }
    free(array->contacts);
    array->contacts = NULL;

    free(array);
    array = NULL;
}

int array_contacts_append(array_contacts* array, personal_info* contact)
{
    if(array == NULL) return ARRAY_CONTACTS_ERROR;

    if(array->count >= array->capacity)
    {
        if (array->capacity == 0) array->capacity = ARRAY_CONTACTS_INIT_CAPACITY;
        else array->capacity *= 2;

        array->contacts = realloc(array->contacts, array->capacity * sizeof(*array->contacts));
    }

    array->contacts[array->count++] = contact;
    return ARRAY_CONTACTS_OK;
}

int array_contacts_remove(array_contacts* array, size_t index)
{
    if(array == NULL || index >= array->count) return ARRAY_CONTACTS_ERROR;

    personal_info_destroy(array->contacts[index]);
    array->contacts[index] = NULL;

    for(size_t i = index; i < array->count - 1; i++)
    {
        array->contacts[i] = array->contacts[i+1];
    }
    array->count--;
    return ARRAY_CONTACTS_OK;
}

void array_contacts_print_all(array_contacts* array)
{
    for(size_t i = 0; i < array->count; i++)
    {
        personal_info_print_all(array->contacts[i]);
        printf("\n");
    }
}

int array_contacts_print_at_index(array_contacts* array, size_t index)
{
    if(index >= array->count) return ARRAY_CONTACTS_ERROR;
    personal_info_print_all(array->contacts[index]);
    return ARRAY_CONTACTS_OK;
}
