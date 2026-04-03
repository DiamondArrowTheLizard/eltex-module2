#include "contacts_list.h"
#include "personal_info.h"
#include <stdlib.h>

static contacts_list* contacts_list_init(personal_info* info, int id)
{
    contacts_list* list = (contacts_list*)malloc(sizeof(*list));
    list->contact = info;
    list->id = id;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

void contacts_list_destroy(contacts_list* head)
{
    if (head == NULL) return;
    contacts_list* next = head->next;
    personal_info_destroy(head->contact);
    free(head);
    contacts_list_destroy(next);
}

int contacts_list_append(contacts_list** head, personal_info* info)
{
    static int next_id = 0;
    if (head == NULL) return CONTACTS_LIST_BAD;

    int new_id = next_id++;
    contacts_list* new_node = contacts_list_init(info, new_id);

    if (*head == NULL)
    {
        *head = new_node;
        return new_id;
    }

    if (new_id < (*head)->id)
    {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
        return new_id;
    }

    contacts_list* current = *head;
    while (current->next != NULL && current->next->id < new_id)
    {
        current = current->next;
    }

    new_node->next = current->next;
    if (current->next != NULL)
    {
        current->next->prev = new_node;
    }
    current->next = new_node;
    new_node->prev = current;

    return new_id;
}

personal_info* contacts_list_get(contacts_list* head, int id)
{
    for (contacts_list* node = head; node != NULL; node = node->next)
    {
        if (node->id == id)
            return node->contact;
    }
    return NULL;
}

int contacts_list_remove(contacts_list** head, int id)
{
    if (head == NULL || *head == NULL) return CONTACTS_LIST_BAD;

    contacts_list* node = *head;
    while (node != NULL && node->id != id)
    {
        node = node->next;
    }
    if (node == NULL) return CONTACTS_LIST_NO_ID;

    if (node == *head)
    {
        *head = node->next;
        if (*head != NULL) (*head)->prev = NULL;
    }
    else
    {
        node->prev->next = node->next;
        if (node->next != NULL) node->next->prev = node->prev;
    }

    personal_info_destroy(node->contact);
    free(node);
    return CONTACTS_LIST_OK;
}

void contacts_list_print_id(contacts_list* head, int id)
{
    if (head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }
    for (contacts_list* node = head; node != NULL; node = node->next)
    {
        if (node->id == id)
        {
            personal_info_print_all(node->contact);
            return;
        }
    }
}

void contacts_list_print_last(contacts_list* head)
{
    if (head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }
    contacts_list* node;
    for (node = head; node->next != NULL; node = node->next);
    printf("ID %d:\n", node->id);
    personal_info_print_all(node->contact);
}

void contacts_list_print_all(contacts_list* head)
{
    if (head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }
    for (contacts_list* node = head; node != NULL; node = node->next)
    {
        printf("ID %d:\n", node->id);
        personal_info_print_all(node->contact);
    }
}
