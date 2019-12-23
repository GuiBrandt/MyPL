#include "trie_set.h"

#include <stdlib.h>
#include <string.h>

void trie_add(trie_set* t, const char* string) {
    for (int i = 0; string[i]; i++) {
        char c = string[i];

        if (!t->children[c]) {
            t->children[c] = (trie_set*)malloc(sizeof(trie_set));
            memset(t->children[c], 0, sizeof(trie_set));
        }

        t = t->children[c];
    }
    t->exists = true;
}

bool trie_contains(trie_set* t, const char* string) {
    for (int i = 0; string[i]; i++) {
        char c = string[i];

        if (!t->children[c])
            return false;

        t = t->children[c];
    }
    return t->exists;
}

void trie_free(trie_set* t) {
    for (int i = 0; i * sizeof(trie_set*) < sizeof(t->children); i++) {
        if (!t->children[i])
            continue;
        trie_free(t->children[i]);
        free(t->children[i]);
    }
}
