#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 17;
    char const* string = "\"abc defg\" hijkl";
    token t;
    
    next_token(string, length, &t);

    assert(t.value.small.length == 8);
    assert(memcmp(t.value.small.data, "abc defg", 8) == 0);
    assert(t.type == TOKEN_STRING);

    return 0;
}