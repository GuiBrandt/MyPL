#include <assert.h>

#include <util/splay_tree.h>

int main() {
    splay_tree t = {0};

    splay_add(&t, 1, "a");
    splay_add(&t, 2, "b");
    splay_add(&t, 3, "c");
    splay_add(&t, 4, "d");

    assert(splay_get(&t, 1) != 0);
    assert(splay_get(&t, 2) != 0);
    assert(splay_get(&t, 3) != 0);
    assert(splay_get(&t, 4) != 0);
    
    splay_free(&t);

    return 0;
}