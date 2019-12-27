#include <stdio.h>
#include <string.h>

#include <util/splay_tree.h>

splay_tree t;

void test_contains() {
    const char* s = splay_get(&t, 3);
    if (!s) {
        printf("not ok - Splay tree get added key returns null.\n");
        return;
    } else if (strcmp(s, "c") != 0) {
        printf("not ok - Splay tree: expected \"a\", got \"%s\"\n", s);
        return;
    }

    printf("ok - Splay tree gets added key-value pair correctly.\n");
}

void test_not_contains() {
    const char* s = splay_get(&t, 5);
    if (s) {
        printf("not ok - Splay tree gets value for key that was not added.\n");
        return;
    }

    printf("ok - Splay tree returns NULL for non-existing keys.\n");
}

// TODO: Tests to ensure used node move up.

int main(int argc, char** argv) {
    splay_add(&t, 1, "a");
    splay_add(&t, 2, "b");
    splay_add(&t, 3, "c");
    splay_add(&t, 4, "d");

    printf("1..2\n");
    test_contains();
    test_not_contains();

    splay_free(&t);

    return 0;
}
