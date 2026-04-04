#ifndef CONTACTS_BTREE_H
#define CONTACTS_BTREE_H

#include "personal_info.h"
#include <stdio.h>

typedef struct contacts_tree_node
{
    int key;
    personal_info* contact;
    struct contacts_tree_node* left;
    struct contacts_tree_node* right;
    int height;
} tree_node;

tree_node* tree_init(personal_info* contact, int key);
void tree_destroy(tree_node* root);

void tree_traverse(tree_node* root);

int tree_get_height(tree_node* n);
tree_node* tree_rotate_right(tree_node* y);
tree_node* tree_rotate_left(tree_node* x);
int tree_get_balance(tree_node* n);

tree_node* tree_insert(tree_node* root, int key, personal_info* contact);
tree_node* tree_search(tree_node* root, int key);
tree_node* tree_remove(tree_node* root, int key);

void tree_node_print(FILE* stream, tree_node* node);
void tree_print(FILE* stream, tree_node* root);

#endif
