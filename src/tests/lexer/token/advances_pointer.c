#include <assert.h>

#include <lexer/token.h>

int main() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    size_t i = next_token(string, length, NULL);

    assert(string[i] == 'd');
    
    return 0;
}