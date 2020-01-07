#include <assert.h>
#include <string.h>

#include <lexer/token.h>

#include <stdio.h>

// TODO: Do better than this.
int main() {
    char const* string = "abc false cde null fgh true ijk self lmn";
    int length = strlen(string);

    size_t i = next_token(string, length, NULL);
    string += i;
    length -= i;

    token t;
    
    i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.value.small.length == 5);
    assert(memcmp(t.value.small.data, "false", 5) == 0);
    assert(t.type == TOKEN_LITERAL);
    
    i = next_token(string, length, NULL);
    string += i;
    length -= i;

    i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.value.small.length == 4);
    assert(memcmp(t.value.small.data, "null", 4) == 0);
    assert(t.type == TOKEN_LITERAL);

    i = next_token(string, length, NULL);
    string += i;
    length -= i;

    i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.value.small.length == 4);
    assert(memcmp(t.value.small.data, "true", 4) == 0);
    assert(t.type == TOKEN_LITERAL);

    i = next_token(string, length, NULL);
    string += i;
    length -= i;

    i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.value.small.length == 4);
    assert(memcmp(t.value.small.data, "self", 4) == 0);
    assert(t.type == TOKEN_LITERAL);

    return 0;
}