#include "array_contacts.h"
#include "personal_info.h"
#include <stddef.h>
#include <stdlib.h>

#define ARRAY_CONTACTS_INIT_CAPACITY 10

array_contacts* array_contacts_init()
{
    array_contacts* array = (array_contacts*)malloc(sizeof(*array));
    array->contacts = NULL;
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
    if(array == NULL) return 0;

    if(array->count >= array->capacity)
    {
        size_t new_capacity = array->capacity == 0 ? ARRAY_CONTACTS_INIT_CAPACITY : array->capacity * 2;
        personal_info** new_contacts = realloc(array->contacts, new_capacity * sizeof(*array->contacts));
        if(new_contacts == NULL) return 0;
        array->contacts = new_contacts;
        array->capacity = new_capacity;
    }

    array->contacts[array->count++] = contact;
    return 1;
}

int array_contacts_remove(array_contacts* array, size_t index)
{
    if(array == NULL || index >= array->count) return 0;

    personal_info_destroy(array->contacts[index]);
    array->contacts[index] = NULL;

    for(size_t i = index; i < array->count - 1; i++)
    {
        array->contacts[i] = array->contacts[i+1];
    }
    array->count--;
    return 1;
}

void array_contacts_print_all(array_contacts* array)
{
    for(size_t i = 0; i < array->count; i++)
    {
        personal_info_print_all(array->contacts[i]);
    }
}

int array_contacts_print_at_index(array_contacts* array, size_t index)
{
    if(index >= array->count) return 0;
    personal_info_print_all(array->contacts[index]);
    return 1;
}
