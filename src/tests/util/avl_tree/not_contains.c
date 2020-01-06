#include <assert.h>

#include <util/avl_tree.h>

int main() {
    avl_tree t = {0};
    
    avl_add(&t, 1, "a");
    avl_add(&t, 2, "b");
    avl_add(&t, 4, "d");
    avl_add(&t, 3, "c");
    avl_add(&t, 9, "a");
    avl_add(&t, 8, "b");
    avl_add(&t, 6, "d");
    avl_add(&t, 7, "c");

    assert(avl_get(&t, 10) == 0);
    assert(avl_get(&t, 20) == 0);
    assert(avl_get(&t, 0) == 0);
    assert(avl_get(&t, 5) == 0);
    
    avl_free(&t);

    return 0;
}