#include <stdio.h>
#include <string.h>

#include <util/avl_tree.h>

avl_tree t;

void test_contains() {
    const char* s = avl_get(&t, 3);
    if (!s) {
        printf("not ok - AVL tree get added key returns null.\n");
        return;
    } else if (strcmp(s, "c") != 0) {
        printf("not ok - AVL tree: expected \"a\", got \"%s\"\n", s);
        return;
    }

    printf("ok - AVL tree gets added key-value pair correctly.\n");
}

void test_not_contains() {
    const char* s = avl_get(&t, 5);
    if (s) {
        printf("not ok - AVL tree gets value for key that was not added.\n");
        return;
    }

    printf("ok - AVL tree returns NULL for non-existing keys.\n");
}

// TODO: Tests to ensure balancing;

int main(int argc, char** argv) {
    avl_add(&t, 1, "a");
    avl_add(&t, 2, "b");
    avl_add(&t, 3, "c");
    avl_add(&t, 4, "d");

    printf("1..2\n");
    test_contains();
    test_not_contains();

    avl_free(&t);

    return 0;
}
