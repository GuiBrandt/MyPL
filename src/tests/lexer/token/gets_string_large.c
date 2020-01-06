#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lexer/token.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    char large[1024];
    memset(large, 'a', sizeof(large) - 1);
    large[sizeof(large) - 1] = 0;

    char* string = (char*)malloc(2000);

    sprintf(string, "abc \"%s\" def", large);
    int length = strlen(string);

    size_t i = next_token(string, length, NULL);
    string += i;
    length -= i;

    token t;
    
    i = next_token(string, length, &t);
    string += i;
    length -= i;

    struct _large_token_block* block = &t.value.large;

    char* large_p = large;
    size_t large_length = strlen(large);

    while (block) {
        assert(block->length == MIN(sizeof(block->data), large_length));
        assert(memcmp(block->data, large, block->length) == 0);

        large_length -= sizeof(block->data);
        large_p += sizeof(block->data);
        block = block->next;
    }
    assert(t.type == TOKEN_STRING);

    next_token(string, length, &t);

    assert(t.value.small.length == 3);
    assert(memcmp(t.value.small.data, "def", 3) == 0);

    return 0;
}