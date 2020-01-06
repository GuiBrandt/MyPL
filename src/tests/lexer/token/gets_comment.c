#include <assert.h>
#include <string.h>

#include <lexer/token.h>

int main() {
    int length = 28;
    char const* string = "# abc def\nghi jkl";

    token t;
    size_t i = next_token(string, length, &t);
    string += i;
    length -= i;
    
    assert(t.value.small.length == 8);
    assert(memcmp(t.value.small.data, " abc def", 8) == 0);
    assert(t.type == TOKEN_COMMENT);

    i = next_token(string, length, &t);
    string += i;
    length -= i;
    assert(t.type == TOKEN_LINEBREAK);

    return 0;
}