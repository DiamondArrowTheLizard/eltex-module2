#include "contacts_btree.h"
#include <stdlib.h>
#include <stdio.h>

tree_node* tree_init(personal_info* contact, int key)
{
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    node->key = key;
    node->contact = contact;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}
void tree_destroy(tree_node* root)
{
    if (!root) return;
    tree_destroy(root->left);
    tree_destroy(root->right);
    personal_info_destroy(root->contact);
    free(root);
    root = NULL;
}

int tree_get_height(tree_node* n)
{
    return n ? n->height : 0;
}

int tree_get_balance(tree_node* n)
{
    return n ? tree_get_height(n->left) - tree_get_height(n->right) : 0;
}

tree_node* tree_rotate_right(tree_node* y)
{
    tree_node* x = y->left;
    tree_node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = (tree_get_height(y->left) > tree_get_height(y->right) ? tree_get_height(y->left) : tree_get_height(y->right)) + 1;
    x->height = (tree_get_height(x->left) > tree_get_height(x->right) ? tree_get_height(x->left) : tree_get_height(x->right)) + 1;

    return x;
}

tree_node* tree_rotate_left(tree_node* x)
{
    tree_node* y = x->right;
    tree_node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = (tree_get_height(x->left) > tree_get_height(x->right) ? tree_get_height(x->left) : tree_get_height(x->right)) + 1;
    y->height = (tree_get_height(y->left) > tree_get_height(y->right) ? tree_get_height(y->left) : tree_get_height(y->right)) + 1;

    return y;
}

tree_node* tree_insert(tree_node* root, int key, personal_info* contact)
{
    if (!root)
        return tree_init(contact, key);

    if (key < root->key)
        root->left = tree_insert(root->left, key, contact);
    else if (key > root->key)
        root->right = tree_insert(root->right, key, contact);
    else
        return root;

    root->height = (tree_get_height(root->left) > tree_get_height(root->right) ? tree_get_height(root->left) : tree_get_height(root->right)) + 1;

    int balance = tree_get_balance(root);

    if (balance > 1 && key < root->left->key)
        return tree_rotate_right(root);

    if (balance < -1 && key > root->right->key)
        return tree_rotate_left(root);

    if (balance > 1 && key > root->left->key)
    {
        root->left = tree_rotate_left(root->left);
        return tree_rotate_right(root);
    }

    if (balance < -1 && key < root->right->key)
    {
        root->right = tree_rotate_right(root->right);
        return tree_rotate_left(root);
    }

    return root;
}

static tree_node* min_value_node(tree_node* node)
{
    tree_node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

tree_node* tree_remove(tree_node* root, int key)
{
    if (!root)
        return root;

    if (key < root->key)
        root->left = tree_remove(root->left, key);
    else if (key > root->key)
        root->right = tree_remove(root->right, key);
    else
    {
        if (!root->left || !root->right)
        {
            tree_node* temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else
            *root = *temp;
            personal_info_destroy(temp->contact);
            free(temp);
        }
        else
    {
            tree_node* temp = min_value_node(root->right);
            root->key = temp->key;
            root->contact = temp->contact;
            root->right = tree_remove(root->right, temp->key);
        }
    }

    if (!root)
        return root;

    root->height = (tree_get_height(root->left) > tree_get_height(root->right) ? tree_get_height(root->left) : tree_get_height(root->right)) + 1;

    int balance = tree_get_balance(root);

    if (balance > 1 && tree_get_balance(root->left) >= 0)
        return tree_rotate_right(root);

    if (balance > 1 && tree_get_balance(root->left) < 0)
    {
        root->left = tree_rotate_left(root->left);
        return tree_rotate_right(root);
    }

    if (balance < -1 && tree_get_balance(root->right) <= 0)
        return tree_rotate_left(root);

    if (balance < -1 && tree_get_balance(root->right) > 0)
    {
        root->right = tree_rotate_right(root->right);
        return tree_rotate_left(root);
    }

    return root;
}

tree_node* tree_search(tree_node* root, int key)
{
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return tree_search(root->left, key);
    return tree_search(root->right, key);
}

void tree_traverse(tree_node* root)
{
    if (root)
    {
        tree_traverse(root->left);
        tree_node_print(stdout, root);
        tree_traverse(root->right);
    }
}

void tree_node_print(FILE* stream, tree_node* node)
{
    if (node == NULL) return;
    fprintf(stream, "Key: %d\n", node->key);
    if (node->contact)
        personal_info_print_all(node->contact);
    else
        fprintf(stderr, "Error: contact data missing.\n");
}

static void tree_print_recursive(FILE* stream, tree_node* node, const char* prefix, int is_left)
{
    if (!node) return;

    fprintf(stream, "%s", prefix);
    fprintf(stream, is_left ? "├── " : "└── ");
    fprintf(stream, "%d\n", node->key);

    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "│   " : "    ");

    if (node->left && node->right)
    {
        tree_print_recursive(stream, node->left, new_prefix, 1);
        tree_print_recursive(stream, node->right, new_prefix, 0);
    }
    else if (node->left)
    {
        tree_print_recursive(stream, node->left, new_prefix, 1);
    }
    else if (node->right)
    {
        tree_print_recursive(stream, node->right, new_prefix, 0);
    }
}

void tree_print(FILE* stream, tree_node* root)
{
    if (!root) return;
    fprintf(stream, "%d\n", root->key);

    if (root->left && root->right)
    {
        tree_print_recursive(stream, root->left, "", 1);
        tree_print_recursive(stream, root->right, "", 0);
    }
    else if (root->left)
    {
        tree_print_recursive(stream, root->left, "", 1);
    }
    else if (root->right)
    {
        tree_print_recursive(stream, root->right, "", 0);
    }
}
