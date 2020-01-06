#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 13;
    char const* string = "abc123 defgh";
    token t;
    
    next_token(string, length, &t);

    assert(t.value.small.length == 6);
    assert(memcmp(t.value.small.data, "abc123", 6) == 0);
    assert(t.type == TOKEN_NAME);

    return 0;
}