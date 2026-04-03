#include "contacts_list.h"
#include "personal_info.h"
#include <stdlib.h>

contacts_list* contacts_list_init(personal_info* info, int id)
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
    if(head == NULL) return;

    contacts_list* next = head->next;

    personal_info_destroy(head->contact);
    head->contact = NULL;
    head->next = NULL;
    head->prev = NULL;
    free(head);
    head = NULL;

    contacts_list_destroy(next);
}

int contacts_list_append(contacts_list* head, personal_info* info, int id)
{
    if(head == NULL) return CONTACTS_LIST_BAD;

    contacts_list* new_node = contacts_list_init(info, id);

    contacts_list* node = head;
    while(node->next != NULL)
    {
        if(new_node->id < node->id)
        {
            new_node->prev = node->prev;
            if(node->prev == NULL) head = new_node;
            if(node->prev != NULL) node->prev->next = new_node;
            node->prev = new_node;
            new_node->next = node;
            return CONTACTS_LIST_OK; 

        } else if(new_node->id == node->id) {
            return CONTACTS_LIST_BAD_ID;

        } else {
            node = node->next;

        }
    }
    
    node->next = new_node;
    new_node->prev = node;
    return CONTACTS_LIST_OK;
}

personal_info* contacts_list_get(contacts_list* head, int id)
{
    if(head == NULL) return NULL;

    for(contacts_list* node = head; node != NULL; node = node->next)
    {
        if(node->id == id)
        {
            return node->contact;
        }
    }

    return NULL;

}

int contacts_list_remove(contacts_list* head, int id)
{
    if(head == NULL) return CONTACTS_LIST_BAD;

    for(contacts_list* node = head; node != NULL; node = node->next)
    {
        if(node->id == id)
        {
            if(node->id == head->id) 
            {
                head = head->next;
                head->prev = NULL;
                return CONTACTS_LIST_OK;
            }
            if(node->next != NULL) node->next->prev = node->prev;
            node->prev->next = node->next;

            free(node);
            node = NULL;
            return CONTACTS_LIST_OK;
        }
    }
    return CONTACTS_LIST_NO_ID;
}

void contacts_list_print_id(contacts_list* head, int id)
{
    if(head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }

    for(contacts_list* node = head; node != NULL; node = node->next)
    {
        if(node->id == id)
        {
            personal_info_print_all(node->contact);
        } 
    }

}

void contacts_list_print_last(contacts_list* head)
{
    if(head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }
    contacts_list* node;
    for(node = head; node->next != NULL; node = node->next);
    printf("ID %d:\n", node->id);
    personal_info_print_all(node->contact);
}

void contacts_list_print_all(contacts_list* head)
{
    if(head == NULL)
    {
        fprintf(stderr, "Print error: contacts list is empty.\n");
        return;
    }

    for(contacts_list* node = head; node != NULL; node = node->next)
    {
        printf("ID %d:\n", node->id);
        personal_info_print_all(node->contact);
    }
}
