#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    token t;

    size_t i = next_token(string, length, &t);
    string += i;
    length -= i;

    assert(t.value.small.length == 3);
    assert(memcmp(t.value.small.data, "abc", 3) == 0);
    assert(t.type == TOKEN_NAME);
    
    next_token(string, length, &t);

    assert(t.value.small.length == 5);
    assert(memcmp(t.value.small.data, "defgh", 3) == 0);
    assert(t.type == TOKEN_NAME);

    return 0;
}