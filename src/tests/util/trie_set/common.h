#include <util/trie_set.h>

static const char* WORDS[] = {
    "abbess","abbreviator","abbreviators","abdications","abdicative","abdicator",
    "epanadiplosis","epanalepses","epanalepsis","epanaleptic","epanaphora",
    "epanaphoral","epanaphoras","epanodos","epanodoses","epanorthoses",
    "grosert","groserts","groset","grosets","grosgrain","grosgrains","gross",
    "grossart","grossarts","grossed"
};

void init_trie(trie_set* t) {
    for (int i = 0; i * sizeof(const char*) < sizeof(WORDS); i++)
        trie_add(t, WORDS[i]);
}