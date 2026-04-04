#ifndef UI_H
#define UI_H

#include "contacts_btree.h"

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

void ui_run(tree_node** root);

int ui_process_user_action(int user_choice);
void ui_add(tree_node** root);
void ui_redact(tree_node* root);
void ui_delete(tree_node** root);
void ui_print_entry(tree_node* root);
void ui_print_all(tree_node* root);

#endif
