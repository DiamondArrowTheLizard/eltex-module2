#include "personal_info.h"
#include "array_contacts.h"
#include "string_array.h"
#include "ui.h"
#include <stdlib.h>
#include <string.h>

int main()
{
    array_contacts* array = array_contacts_init();
    personal_info* info = personal_info_create("Ivan", "Ivanov");
    string_array* phones = string_array_init();
    string_array* links = string_array_init();

    char* new_name = "Vlad";
    char* new_patronymic = (char*)malloc((strlen("Ivanovich") + 1) * sizeof(*new_patronymic));
    strcpy(new_patronymic, "Ivanovich");

    personal_info_new_name(info, new_name);
    personal_info_new_patronymic(info, new_patronymic);

    string_array_append(phones, "88005553535");
    string_array_append(phones, "+78005553535");
    string_array_append(links, "t.me");
    string_array_append(links, "youtube.com");
    personal_info_new_phone_numbers(info, phones);
    personal_info_new_links(info, links);

    array_contacts_append(array, info);

    personal_info* info2 = personal_info_create("Vasiliy", "Afonovich");
    array_contacts_append(array, info2);

    personal_info* info3 = personal_info_create("Gena", "Afonovich");
    array_contacts_append(array, info3);

    ui_run(array);

    free(new_patronymic);
    array_contacts_destroy(array);
    return 0;
}
