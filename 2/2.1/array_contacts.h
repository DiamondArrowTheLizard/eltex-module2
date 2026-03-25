#ifndef ARRAY_CONTACTS_H
#define ARRAY_CONTACTS_H

#include "personal_info.h"
#include <stddef.h>

typedef struct array_contacts
{
    personal_info** contacts;
    size_t count;
    size_t capacity;

} array_contacts;

array_contacts* array_contacts_init();
void array_contacts_destroy(array_contacts* array);

int array_contacts_append(array_contacts* array, personal_info* contact);
int array_contacts_remove(array_contacts* array, size_t index);

#endif // !ARRAY_CONTACTS_H
