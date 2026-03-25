#include "array_contacts.h"
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
{
    for(size_t i = 0; i < array->count; i++)
    {
        free(array->contacts[i]);
        array->contacts[i] = NULL;
    }
    free(array->contacts);
    array->contacts = NULL;

    array->count = 0;
    array->capacity = 0;

    free(array);
    array = NULL;
}

int array_contacts_append(array_contacts* array, personal_info* contact)
{
    if(array == NULL) return 0;

    if(array->count >= array->capacity)
    {
        if(array->capacity == 0) array->capacity = ARRAY_CONTACTS_INIT_CAPACITY;
        else array->capacity *= 2;

        array->contacts = realloc(array->contacts, array->capacity * sizeof(*array->contacts));
        array->contacts[array->count++] = contact;
    }
    return 1;
}

int array_contacts_remove(array_contacts* array, size_t index)
{
    if(array == NULL) return 0;

    array_contacts* new_array = array_contacts_init();
    for (size_t i = 0; i < array->count; i++)
    {
        if(i == index) continue;
        else array_contacts_append(new_array, array->contacts[i]);
    }

    array_contacts_destroy(array);
    array = new_array;

    return 1;
}
