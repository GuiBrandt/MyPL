#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 8;
    char const* string = "( defgh";
    token t;
    
    next_token(string, length, &t);

    assert(t.value.small.length == 1);
    assert(memcmp(t.value.small.data, "(", 1) == 0);
    assert(t.type == TOKEN_SYMBOL);

    return 0;
}