#include "avl_tree.h"

#include <stdlib.h>

inline avl_tree new_node(int_fast8_t key, void* value, avl_tree parent) {
    avl_tree node = (avl_tree)malloc(sizeof(struct __avl_tree_node));
    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->parent = parent;
    node->height = 0;
    return node;
}

inline int balance_factor(avl_tree node) {
    return (node->right ? node->right->height : 0) -
            (node->left ? node->left->height : 0);
}

void avl_right_rotate(register avl_tree node, avl_tree* tree) {
    avl_tree grandparent = node->parent->parent;   
    if (grandparent) {
        if (node->parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    } else
        *tree = node;

    node->parent->left = node->right;
    node->parent->height -= 2;

    if (node->right)
        node->right->parent = node->parent;

    node->right = node->parent;
    node->parent->parent = node;
    
    node->parent = grandparent;
    node->height++;
}

void avl_left_rotate(register avl_tree node, avl_tree* tree) {
    avl_tree grandparent = node->parent->parent;   
    if (grandparent) {
        if (node->parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    } else
        *tree = node;

    node->parent->right = node->left;
    node->parent->height -= 2;

    if (node->left)
        node->left->parent = node->parent;

    node->left = node->parent;
    node->parent->parent = node;

    node->parent = grandparent;
    node->height++;
}

void avl_add(avl_tree* tree, uint_fast8_t key, void* value) {
    avl_tree node = *tree;
    if (!node) {
        *tree = new_node(key, value, NULL);
        return;
    }

    avl_tree parent = NULL;
    while (node) {
        parent = node;
        parent->height++;
        if (key == node->key) {
            node->value = value;
            return;
        } else if (key > node->key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    node = new_node(key, value, parent);
    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;

    while (parent) {
        if (balance_factor(parent) < -1) {
            if (balance_factor(parent->left) > 0)
                avl_left_rotate(parent->left->right, tree);
            avl_right_rotate(parent->left, tree);
        } else if (balance_factor(parent) > 1) {
            if (balance_factor(parent->right) < 0)
                avl_right_rotate(parent->right->left, tree);
            avl_left_rotate(parent->right, tree);
        }
        parent = parent->parent;
    }
}

void* avl_get(avl_tree* t, register uint_fast8_t key) {
    register avl_tree node = *t;
    while (node) {
        if (node->key == key)
            return node->value;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL;
}

void avl_free(avl_tree* t) {
    avl_tree node = *t;
    if (node->left)
        avl_free(&node->left);
    if (node->right)
        avl_free(&node->right);
    free(node);
}
