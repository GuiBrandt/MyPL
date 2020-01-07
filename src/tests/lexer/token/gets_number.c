#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 12;
    char const* string = "12345 defgh";
    token t;
    
    next_token(string, length, &t);

    assert(t.value.small.length == 5);
    assert(memcmp(t.value.small.data, "12345", 5) == 0);
    assert(t.type == TOKEN_LITERAL);

    return 0;
}