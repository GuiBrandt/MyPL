#include <util/trie_set.h>

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

trie_set* _find(register trie_set* t, register const char* string) {
    for (register int i = 0; string[i]; i++) {
        register char c = string[i];
        
        t = t->children[c];

        if (!t)
            return NULL;        
    }
    return t;
}

bool trie_contains(register trie_set* t, register const char* string) {
    t = _find(t, string);
    return t && t->exists;
}

bool trie_contains_prefix(register trie_set* t, register const char* string) {
    t = _find(t, string);
    return t != NULL;
}

void trie_free(trie_set* t) {
    for (int i = 0; i * sizeof(trie_set*) < sizeof(t->children); i++) {
        if (!t->children[i])
            continue;
        trie_free(t->children[i]);
        free(t->children[i]);
    }
}
