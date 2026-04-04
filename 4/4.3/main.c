#include "contacts_btree.h"
#include "ui.h"
#include <stdlib.h>

int main()
{
    tree_node* root = NULL;
    ui_run(&root);
    tree_destroy(root);
    return 0;
}
