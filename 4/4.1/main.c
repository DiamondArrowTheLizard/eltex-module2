#include "personal_info.h"
#include "contacts_list.h"
#include "string_array.h"
#include "ui.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    contacts_list* list = NULL;

    char* name = malloc(strlen("Vlad") + 1);
    strcpy(name, "Vlad");
    char* surname = malloc(strlen("Ivanov") + 1);
    strcpy(surname, "Ivanov");
    personal_info* info = personal_info_create(name, surname);
    free(name);
    free(surname);

    string_array* phones = string_array_init();
    string_array* links = string_array_init();
    string_array_append(phones, "88005553535");
    string_array_append(phones, "+78005553535");
    string_array_append(links, "t.me");
    string_array_append(links, "youtube.com");
    personal_info_new_phone_numbers(info, phones);
    personal_info_new_links(info, links);

    contacts_list_append(&list, info);

    ui_run(&list);
    contacts_list_destroy(list);
    return 0;
}
