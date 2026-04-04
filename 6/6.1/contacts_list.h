#ifndef CONTACTS_LIST_H
#define CONTACTS_LIST_H

#include "personal_info.h"
#include <stdio.h>

#define CONTACTS_LIST_OK 0
#define CONTACTS_LIST_BAD -1
#define CONTACTS_LIST_BAD_ID -2
#define CONTACTS_LIST_NO_ID -3

typedef struct contacts_double_linked_list
{
    personal_info* contact;
    int id;
    struct contacts_double_linked_list* next;
    struct contacts_double_linked_list* prev;
} contacts_list;

void contacts_list_destroy(contacts_list* head);

int contacts_list_append(contacts_list** head, personal_info* info);
personal_info* contacts_list_get(contacts_list* head, int id);
int contacts_list_remove(contacts_list** head, int id);

void contacts_list_print_id(contacts_list* head, int id);
void contacts_list_print_last(contacts_list* head);
void contacts_list_print_all(contacts_list* head);

#endif
