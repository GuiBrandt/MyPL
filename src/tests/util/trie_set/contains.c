#include <assert.h>

#include <util/trie_set.h>

#include "common.h"

int main() {
    trie_set t = {0};
    init_trie(&t);

    for (int i = 0; i * sizeof(const char*) < sizeof(WORDS); i++)
        assert(trie_contains(&t, WORDS[i]));
    
    trie_free(&t);

    return 0;
}