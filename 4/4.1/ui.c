#include "ui.h"
#include "contacts_list.h"
#include "personal_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_line (char *buff, size_t sz) {
    int ch, extra;

    if (fgets (buff, sz, stdin) == NULL)
        return UI_NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? UI_TOO_LONG : UI_OK;
    }

    buff[strlen(buff)-1] = '\0';
    return UI_OK;
}

static int check_if_fail(int validator, int success_condition, char* error_message)
{
    if(validator != success_condition)
    {
        printf("%s\n", error_message);
        return UI_SIGNAL_INPUT_ERROR;
    }

    return UI_OK;
}

static string_array* read_string_array()
{
    string_array* arr = string_array_init();
    char buffer[UI_CONTACT_FIELD_BUFFER];
    int res;
    while (1) {
        printf("> ");
        res = get_line(buffer, sizeof(buffer));
        if (res != UI_OK) {
            continue;
        }
        if (strlen(buffer) == 0) {
            break;
        }
        string_array_append(arr, buffer);
    }
    return arr;
}

void ui_run(contacts_list* list)
{
    printf("Contact book\n");

    for(;;)
    {
        printf("1: Add new entry to the book\n");
        printf("2: Redact entry\n");
        printf("3: Delete entry\n");
        printf("4: Print entry\n");
        printf("5: Print all entries\n");
        printf("6: Quit program\n\n");

        char user_input[UI_USER_INPUT_SIZE] = "";
        int user_input_result;
        printf("==> ");
        user_input_result = get_line(user_input, sizeof(user_input));
        if(user_input_result == UI_NO_INPUT) 
        {
            continue;
        }

        else if(user_input_result == UI_TOO_LONG)
        {
            printf("Input is one number. Please try again.\n");
            continue;

        } else {
            printf("Input: %s\n", user_input);
            int user_choice = atoi(user_input);
            printf("Choice: %d\n", user_choice);
            int signal = ui_process_user_action(user_choice);
            
            printf("Signal: %d\n", signal);
            switch(signal)
            {
                case UI_SIGNAL_ADD:
                    printf("Adding entry\n");
                    ui_add(list);
                    break;

                case UI_SIGNAL_REDACT:
                    printf("Redacting entry\n");
                    ui_redact(list);
                    break;

                case UI_SIGNAL_DELETE:
                    printf("Deleting entry\n");
                    ui_delete(list);
                    break;

                case UI_SIGNAL_PRINT_ENTRY:
                    printf("Printing entry\n");
                    ui_print_entry(list);
                    break;

                case UI_SIGNAL_PRINT_ALL:
                    printf("Printing all entries\n");
                    ui_print_all(list);
                    break;

                case UI_SIGNAL_QUIT: 
                    printf("Quitting program\n");
                    return;

                default:
                    printf("Error: unknown signal\n");
                    break;
            }

        }
        printf("\n");
    }
}

int ui_process_user_action(int user_choice)
{
    switch(user_choice)
    {
        case 1:
            return UI_SIGNAL_ADD;
        case 2:
            return UI_SIGNAL_REDACT;
        case 3:
            return UI_SIGNAL_DELETE;
        case 4:
            return UI_SIGNAL_PRINT_ENTRY;
        case 5:
            return UI_SIGNAL_PRINT_ALL;
        case 6:
            return UI_SIGNAL_QUIT;
        default:
            return UI_SIGNAL_INPUT_ERROR;
    }
}


void ui_add(contacts_list* list)
{
    char name[UI_CONTACT_FIELD_BUFFER];
    char surname[UI_CONTACT_FIELD_BUFFER];
    int field_valid;
    printf("Enter name of the contact: ");
    field_valid = get_line(name, sizeof(name));
    if(check_if_fail(field_valid, UI_OK, "Input error. Please try again.") == UI_SIGNAL_INPUT_ERROR) return;

    printf("Enter surname of the contact: ");
    field_valid = get_line(surname, sizeof(name));
    if(check_if_fail(field_valid, UI_OK, "Input error. Please try again.") == UI_SIGNAL_INPUT_ERROR) return;

    printf("\n");

    personal_info* new_info = personal_info_create(name, surname);
    contacts_list_append(list, new_info);

    printf("New contact added:\n\n");
    contacts_list_print_last(list);


}

void ui_redact(contacts_list* list)
{
    printf("Editing entry\n");
    int id = -1;
    char index_str[20];
    printf("Enter contact id (first contact's id is 0): ");
    int res = get_line(index_str, sizeof(index_str));
    if (res != UI_OK) {
        printf("Input error.\n");
        return;
    }
    id = atoi(index_str);
    if (id < 0 || id > list_global_id) {
        printf("Error: index out of range.\n");
        return;
    }

    personal_info* info = contacts_list_get(list, id);
    if(info == NULL)
    {
        printf("Error: id %d not found.\n", id);
        return;
    }
    printf("Editing contact:\n");
    personal_info_print_all(info);
    printf("\n");

    int done = 0;
    while (!done) {
        printf("Select field to edit:\n");
        printf("1: Name\n");
        printf("2: Surname\n");
        printf("3: Patronymic\n");
        printf("4: Workplace\n");
        printf("5: Position\n");
        printf("6: Phone Numbers\n");
        printf("7: Links\n");
        printf("8: Done\n");
        printf("==> ");
        char choice_str[UI_USER_INPUT_SIZE];
        res = get_line(choice_str, sizeof(choice_str));
        if (res != UI_OK) continue;

        int choice = atoi(choice_str);
        switch (choice) {
            case 1: {
                char new_name[UI_CONTACT_FIELD_BUFFER];
                printf("Enter new name: ");
                if (get_line(new_name, sizeof(new_name)) == UI_OK)
                    personal_info_new_name(info, new_name);
                break;
            }
            case 2: {
                char new_surname[UI_CONTACT_FIELD_BUFFER];
                printf("Enter new surname: ");
                if (get_line(new_surname, sizeof(new_surname)) == UI_OK)
                    personal_info_new_surname(info, new_surname);
                break;
            }
            case 3: {
                char new_patronymic[UI_CONTACT_FIELD_BUFFER];
                printf("Enter new patronymic (empty to remove): ");
                if (get_line(new_patronymic, sizeof(new_patronymic)) == UI_OK) {
                    if (strlen(new_patronymic) == 0) {
                        free(info->patronymic);
                        info->patronymic = NULL;
                    } else {
                        personal_info_new_patronymic(info, new_patronymic);
                    }
                }
                break;
            }
            case 4: {
                char new_workplace[UI_CONTACT_FIELD_BUFFER];
                printf("Enter new workplace (empty to remove): ");
                if (get_line(new_workplace, sizeof(new_workplace)) == UI_OK) {
                    if (strlen(new_workplace) == 0) {
                        free(info->workplace);
                        info->workplace = NULL;
                    } else {
                        personal_info_new_workplace(info, new_workplace);
                    }
                }
                break;
            }
            case 5: {
                char new_position[UI_CONTACT_FIELD_BUFFER];
                printf("Enter new position (empty to remove): ");
                if (get_line(new_position, sizeof(new_position)) == UI_OK) {
                    if (strlen(new_position) == 0) {
                        free(info->position);
                        info->position = NULL;
                    } else {
                        personal_info_new_position(info, new_position);
                    }
                }
                break;
            }
            case 6: {
                printf("Enter new phone numbers (one per line, empty line to finish):\n");
                string_array* new_phones = read_string_array();
                personal_info_new_phone_numbers(info, new_phones);
                break;
            }
            case 7: {
                printf("Enter new links (one per line, empty line to finish):\n");
                string_array* new_links = read_string_array();
                personal_info_new_links(info, new_links);
                break;
            }
            case 8:
                done = 1;
                printf("Redaction complete.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
        printf("\n");
    }
}

void ui_delete(contacts_list* list)
{
    int index = UI_SIGNAL_INPUT_ERROR;
    char index_str[UI_CONTACT_FIELD_BUFFER];
    printf("Enter contact *index* (first contact in number 0): ");
    int res = get_line(index_str, sizeof(index_str));
    if(check_if_fail(res, UI_OK, "Input error.") == UI_SIGNAL_INPUT_ERROR) return;

    index = atoi(index_str);
    int valid_request = contacts_list_remove(list, index);
    if(check_if_fail(valid_request, CONTACTS_LIST_OK, "Error: index out of range.") == UI_SIGNAL_INPUT_ERROR) return;
    else printf("Entry deleted.\n");
}

void ui_print_entry(contacts_list* list)
{
    int id = UI_SIGNAL_INPUT_ERROR;
    char index_str[UI_CONTACT_FIELD_BUFFER];
    printf("Enter contact *index* (first contact in number 0): ");
    int res = get_line(index_str, sizeof(index_str));
    if(check_if_fail(res, UI_OK, "Input error.") == UI_SIGNAL_INPUT_ERROR) return;

    id = atoi(index_str);

    contacts_list_print_id(list, id);

}

void ui_print_all(contacts_list* list)
{
    contacts_list_print_all(list);
    printf("All contacts printed.\n");
}
