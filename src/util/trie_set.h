/**
 * @file trie_set.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 * 
 * @version 1.0
 * @date 2019-12-22
 * 
 * @brief Set implementation using a Trie data structure.
 * 
 * 
 * A trie (often pronounced "try") is a tree-like data structure for string
 * retrieval. Its main purpose is to reduce comparisons and space when fetching
 * data that has some sort of array as keys, and it's specially useful when
 * elements on the array have common prefixes.
 * 
 * There's a really nice article on [Medium][1] that explains how it works and
 * its use cases.
 * 
 * For our compiler, though, we're mainly interested in using tries as sets.
 * Particularly, they'll be used when checking whether a certain token falls
 * into a set of tokens (defined by value) which define some token type, such as
 * keywords and operators.
 * 
 * [1]: https://medium.com/basecs/trying-to-understand-tries-3ec6bede0014
 *  
 */

#ifndef __MYPL_TRIESET_H__
#define __MYPL_TRIESET_H__

#include <stdbool.h>

/** A Trie set. 
 * 
 * For practical reasons, a set is actually node of the trie itself.
 * 
 * FIXME: Maybe make a fixed amount of levels aligned in memory, as a way to
 * optimize cache hits. 
 * 
 */
typedef struct _trie_set {
    struct _trie_set* children[256]; /**< Pointers to this node's children. */

    /** Whether the path ending on this node exists as an element in the set. */
    bool exists; 
} trie_set;

/** Adds a string into a Trie.
 * 
 * @param out the Trie.
 * @param string the string to be added.
 * 
 */
void trie_add(trie_set* out, const char* string);

/** Checks if the set contains a given string.
 * 
 * @param t Trie set.
 * @param string the string.
 * 
 */
bool trie_contains(trie_set* t, const char* string);

/** Frees the memory allocated into the set.
 * 
 * @param t Trie set.
 * 
 */
void trie_free(trie_set* t);

#endif // __MYPL_TRIESET_H__
