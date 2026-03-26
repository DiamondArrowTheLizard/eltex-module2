#ifndef ARRAY_CONTACTS_H
#define ARRAY_CONTACTS_H

#include "personal_info.h"
#include <stddef.h>

#define ARRAY_CONTACTS_OK 1
#define ARRAY_CONTACTS_ERROR 0

#define ARRAY_CONTACTS_INIT_CAPACITY 10

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

void array_contacts_print_all(array_contacts* array);
int array_contacts_print_at_index(array_contacts* array, size_t index);

#endif // !ARRAY_CONTACTS_H
