#include <util/splay_tree.h>

#include <stdlib.h>

void splay(splay_tree node, splay_tree* tree);

splay_tree new_splay_node(uint_fast8_t key, void* value, splay_tree parent) {
    splay_tree node = (splay_tree)malloc(sizeof(struct __splay_tree_node));
    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

void splay_add(splay_tree* tree, uint_fast8_t key, void* value) {
    splay_tree node = *tree;
    if (!node) {
        *tree = new_splay_node(key, value, NULL);
        return;
    }

    splay_tree parent = NULL;
    while (node) {
        parent = node;
        if (key == node->key) {
            node->value = value;
            return;
        } else if (key > node->key) {
            node = node->right;
        } else
            node = node->left;
    }

    node = new_splay_node(key, value, parent);

    if (key < parent->key)
        parent->left = node;
    else
        parent->right = node;

    splay(node, tree);
}

void* splay_get(splay_tree* t, register uint_fast8_t key) {
    register splay_tree node = *t;
    while (node) {
        if (node->key == key) {
            splay(node, t);
            return node->value;
        } else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    return NULL;
}

void splay_free(splay_tree* t) {
    splay_tree node = *t;
    if (node->left)
        splay_free(&node->left);
    if (node->right)
        splay_free(&node->right);
    free(node);
}

void right_rotate(register splay_tree node, splay_tree* tree) {
    splay_tree grandparent = node->parent->parent;   
    if (grandparent) {
        if (node->parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    } else
        *tree = node;

    node->parent->left = node->right;
    if (node->right)
        node->right->parent = node->parent;

    node->right = node->parent;
    node->parent->parent = node;
    
    node->parent = grandparent;
}

void left_rotate(register splay_tree node, splay_tree* tree) {
    splay_tree grandparent = node->parent->parent;   
    if (grandparent) {
        if (node->parent == grandparent->left)
            grandparent->left = node;
        else
            grandparent->right = node;
    } else
        *tree = node;

    node->parent->right = node->left;
    if (node->left)
        node->left->parent = node->parent;

    node->left = node->parent;
    node->parent->parent = node;

    node->parent = grandparent;
}

void splay(register splay_tree node, register splay_tree* t) {  
    if (!node->parent)
        return;

    register splay_tree parent = node->parent,
               grandparent = parent->parent;

    if (grandparent) {
        if (node == parent->left && grandparent->left == parent) {
            right_rotate(parent, t);
            right_rotate(node, t);
        } else if (node == parent->right && grandparent->right == parent) {
            left_rotate(parent, t);
            left_rotate(node, t);
        } else if (node == parent->right) {
            left_rotate(node, t);
            right_rotate(node, t);
        } else {
            right_rotate(node, t);
            left_rotate(node, t);
        }
    } else if (node == node->parent->left)
        right_rotate(node, t);
    else
        left_rotate(node, t);
}
