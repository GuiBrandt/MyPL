/**
 * @file splay_tree.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 *
 * @version 1.0
 * @date 2019-12-26
 * 
 * @brief Splay tree implementation.
 * 
 * 
 * A splay tree is a self-balancing binary search tree in which elements that
 * are frequently accessed are moved closer to the root, thus reducing
 * effective search time. [1]
 * 
 * [1]: https://en.wikipedia.org/wiki/Splay_tree
 * 
 */

#ifndef __MYPL_SPLAY_TREE_H__
#define __MYPL_SPLAY_TREE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** A splay tree.
 * 
 * A tree is actually just a pointer to the root node. With this, we can change
 * the tree root given a pointer to the tree and also create a tree rooted at
 * some arbitrary node by just referencing it.
 * 
 */
typedef struct __splay_tree_node {
    uint_fast8_t key; /**< Stored key. */
    struct __splay_tree_node* left; /**< Left node. */
    struct __splay_tree_node* right; /**< Right node. */
    struct __splay_tree_node* parent; /**< Parent node. */
    void* value; /**< Stored value. */
} *splay_tree;

/** Adds a key-value pair to a splay tree.
 * 
 * @param out splay tree.
 * @param key the key.
 * @param value the value to be stored.
 * 
 */
void splay_add(splay_tree* out, uint_fast8_t key, void* value);

/** Gets the stored value for a given key in a splay tree.
 * 
 * @param t splay tree.
 * @param int_fast8_t the key.
 * @return void* the value stored under the given key, or NULL if the key is
 *               not present.
 */
void* splay_get(splay_tree* t, register uint_fast8_t key);

/** Frees the memory allocated into the tree.
 * 
 * @param t splay tree.
 * 
 */
void splay_free(splay_tree* t);

#ifdef __cplusplus
}
#endif

#endif // __MYPL_SPLAY_TREE_H__
