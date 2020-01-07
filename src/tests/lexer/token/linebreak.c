#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 7;
    char const* string = "abc\nghi";

    size_t i = next_token(string, length, NULL);
    string += i;
    length -= i;

    token t;
    
    i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.type == TOKEN_LINEBREAK);

    next_token(string, length, &t);

    assert(t.value.small.length == 3);
    assert(memcmp(t.value.small.data, "ghi", 3) == 0);

    return 0;
}