#include <assert.h>

#include <util/avl_tree.h>

int main() {
    avl_tree t = {0};

    avl_add(&t, 1, "a");
    avl_add(&t, 2, "b");
    avl_add(&t, 3, "c");
    avl_add(&t, 4, "d");

    assert(avl_get(&t, 1) != 0);
    assert(avl_get(&t, 2) != 0);
    assert(avl_get(&t, 3) != 0);
    assert(avl_get(&t, 4) != 0);
    
    avl_free(&t);

    return 0;
}