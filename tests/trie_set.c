#include <stdio.h>

#include <util/trie_set.h>

trie_set t;

const char* WORDS[] = {
    "abbess","abbreviator","abbreviators","abdications","abdicative","abdicator",
    "epanadiplosis","epanalepses","epanalepsis","epanaleptic","epanaphora",
    "epanaphoral","epanaphoras","epanodos","epanodoses","epanorthoses",
    "grosert","groserts","groset","grosets","grosgrain","grosgrains","gross",
    "grossart","grossarts","grossed"
};

void test_contains() {
    if (trie_contains(&t, "abbess")) {
        printf("ok - trie contains added word\n");
        return;
    } else {
        printf("not ok - trie does not contain added word\n");
        return;
    }
}

void test_not_contains() {
    if (trie_contains(&t, "word")) {
        printf("not ok - trie contains word that was not added\n");
        return;
    } else {
        printf("ok - trie does not contain word that was not added\n");
        return;
    }
}

void test_not_contains_substring() {
    if (trie_contains(&t, "abbe")) {
        printf("not ok - trie contains substring of added string that was not added\n");
        return;
    } else {
        printf("ok - trie does not contain substring that was not added of a word that was added\n");
        return;
    }
}

int main(int argc, char** argv) {
    for (int i = 0; i * sizeof(const char*) < sizeof(WORDS); i++)
        trie_add(&t, WORDS[i]);

    printf("1..3\n");
    test_contains();
    test_not_contains();
    test_not_contains_substring();

    trie_free(&t);

    return 0;
}