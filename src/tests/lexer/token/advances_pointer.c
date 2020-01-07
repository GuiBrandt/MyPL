#include <assert.h>

#include <lexer/token.h>

int main() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    size_t i = next_token(string, length, NULL);
    string += i;
    length -= i;
    
    token t;
    next_token(string, length, &t);

    assert(t.value.small.data[0] == 'd');
    
    return 0;
}