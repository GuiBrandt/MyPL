#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <lexer/token.h>

int main() {
    char const* string = "\"abc \\\" \\\\ defg \\\\\" hijkl";
    int length = strlen(string);

    token t;
    
    size_t i = next_token(string, length, &t);

    assert(t.value.large.length == 17);
    assert(memcmp(t.value.large.data, "abc \\\" \\\\ defg \\\\", 8) == 0);
    assert(t.type == TOKEN_STRING);

    string += i;
    length -= i;
    next_token(string, length, &t);

    assert(t.value.small.length == 5);
    assert(memcmp(t.value.small.data, "hijkl", 5) == 0);

    return 0;
}