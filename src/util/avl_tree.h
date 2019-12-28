/**
 * @file avl_tree.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 *
 * @version 1.0
 * @date 2019-12-26
 * 
 * @brief AVL tree implementation.
 * 
 * 
 * An AVL tree (named after inventors Adelson-Velsky and Landis) is a
 * self-balancing binary search tree. [1]
 * 
 * Essentially, this data structure guarantees that the overall tree is
 * balanced by ensuring that the heights of the two child subtrees of any node
 * differ by at most one. Rebalancing is done by rotating nodes whenever this
 * property is lost.
 * 
 * [1]: https://en.wikipedia.org/wiki/AVL_tree
 * 
 */

#ifndef __MYPL_AVL_TREE_H__
#define __MYPL_AVL_TREE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __avl_tree_node {
    uint_fast8_t key; /**< Stored key. */
    uint_fast8_t height; /**< Tree height. */
    struct __avl_tree_node* left; /**< Left node. */
    struct __avl_tree_node* right; /**< Right node. */
    struct __avl_tree_node* parent; /**< Parent node. */
    void* value; /**< Stored value. */
} *avl_tree;

/** Adds a key-value pair to a AVL tree.
 * 
 * @param out AVL tree.
 * @param key the key.
 * @param value the value to be stored.
 * 
 */
void avl_add(avl_tree* out, uint_fast8_t key, void* value);

/** Gets the stored value for a given key in a AVL tree.
 * 
 * @param t AVL tree.
 * @param int_fast8_t the key.
 * @return void* the value stored under the given key, or NULL if the key is
 *               not present.
 */
void* avl_get(avl_tree* t, register uint_fast8_t key);

/** Frees the memory allocated into the tree.
 * 
 * @param t AVL tree.
 * 
 */
void avl_free(avl_tree* t);

#ifdef __cplusplus
}
#endif

#endif // __MYPL_AVL_TREE_H__
