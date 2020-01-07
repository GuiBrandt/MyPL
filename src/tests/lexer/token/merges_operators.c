#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 9;
    char const* string = "+= defgh";
    token t;
    
    next_token(string, length, &t);
    
    assert(t.value.small.length == 2);
    assert(memcmp(t.value.small.data, "+=", 2) == 0);
    assert(t.type == TOKEN_OPERATOR);
    
    return 0;
}