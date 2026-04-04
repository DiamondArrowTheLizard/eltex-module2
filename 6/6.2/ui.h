#ifndef UI_H
#define UI_H

#include "contacts_list.h"

#define UI_USER_INPUT_SIZE 2
#define UI_CONTACT_FIELD_BUFFER 50

#define UI_OK       0
#define UI_NO_INPUT 1
#define UI_TOO_LONG 2

#define UI_SIGNAL_INPUT_ERROR -1
#define UI_SIGNAL_ADD 1
#define UI_SIGNAL_REDACT 2
#define UI_SIGNAL_DELETE 3
#define UI_SIGNAL_PRINT_ENTRY 4
#define UI_SIGNAL_PRINT_ALL 5
#define UI_SIGNAL_QUIT 6

void ui_run(contacts_list** list);

int ui_process_user_action(int user_choice);
void ui_add(contacts_list** list);
void ui_redact(contacts_list* list);
void ui_delete(contacts_list** list);
void ui_print_entry(contacts_list* list);
void ui_print_all(contacts_list* list);

#endif
