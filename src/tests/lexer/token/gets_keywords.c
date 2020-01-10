#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <lexer/token.h>
#include <lexer/gperf_keywords.h>

int main() {
    char* string = (char*)malloc(1024);
    size_t length = 0;

    for (size_t i = 0; i * sizeof(keywords_list[0]) < sizeof(keywords_list); i++) {
        if (!keywords_list[i].name)
            continue;
        for (size_t j = 0; keywords_list[i].name[j]; j++)
            string[length++] = keywords_list[i].name[j];
        string[length++] = ' ';
    }

    token t;

    for (size_t i = 0; i * sizeof(keywords_list[0]) < sizeof(keywords_list); i++) {
        if (!keywords_list[i].name)
            continue;

        size_t j = next_token(string, length, &t);
        string += j;
        length -= j;

        assert(keywords_list[i].name[t.value.small.length] == 0);
        assert(strncmp(keywords_list[i].name, t.value.small.data, t.value.small.length) == 0);
        assert(t.type == keywords_list[i].type);
    }

    return 0;
}