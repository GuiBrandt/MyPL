#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 10;
    char const* string = "abc+defgh";
    token t;
    
    next_token(string, length, &t);
    
    assert(t.value.small.length == 3);
    assert(memcmp(t.value.small.data, "abc", 3) == 0);

    return 0;
}