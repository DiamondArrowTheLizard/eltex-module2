#include "personal_info.h"
#include "array_contacts.h"
#include <stdio.h>

int main()
{
    array_contacts* array = array_contacts_init();
    personal_info* info = personal_info_create("Ivan", "Ivanov");
    
    personal_info_print_all(info);

    char* new_name = "Vlad";
    personal_info_new_name(info, new_name);
    printf("\n[%s]\n\n", info->name);

    personal_info_print_all(info);

    personal_info_destroy(info);
    array_contacts_destroy(array);
    return 0;
}
