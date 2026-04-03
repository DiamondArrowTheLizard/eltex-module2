#include "personal_info.h"
#include "contacts_list.h"
#include "string_array.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    char* name = (char*)malloc((strlen("Vlad") + 1) * sizeof(*name));
    strcpy(name, "Vlad");
    char* surname = (char*)malloc((strlen("Ivanov") + 1) * sizeof(*surname));
    strcpy(surname, "Vlad");
    char* patronymic = (char*)malloc((strlen("Ivanovich") + 1) * sizeof(*patronymic));
    strcpy(patronymic, "Ivanovich");

    personal_info* info = personal_info_create(name, surname);

    contacts_list* list = contacts_list_init(info, 0);
    string_array* phones = string_array_init();
    string_array* links = string_array_init();

    string_array_append(phones, "88005553535");
    string_array_append(phones, "+78005553535");
    string_array_append(links, "t.me");
    string_array_append(links, "youtube.com");
    personal_info_new_phone_numbers(info, phones);
    personal_info_new_links(info, links);

    contacts_list_destroy(list);

    free(name);
    free(surname);
    free(patronymic);
    return 0;
}
