#include <assert.h>

#include <util/trie_set.h>

#include "common.h"

int main() {
    trie_set t = {0};
    init_trie(&t);

    assert(!trie_contains(&t, "abbe"));
    assert(!trie_contains(&t, "apple"));
    assert(!trie_contains(&t, "grow"));
    assert(!trie_contains(&t, "specific"));
    
    trie_free(&t);

    return 0;
}