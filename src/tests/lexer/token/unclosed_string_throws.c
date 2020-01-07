#include <assert.h>
#include <string.h>

#include <lexer/token.h>
#include <public/errors.h>

int main() {
    int length = 15;
    char const* string = "\"abc defg hijkl";
    token t;
    
    size_t i = next_token(string, length, &t);

    assert(i == -1);
    assert(mypl_last_error == MYPL_ERR_SYNTAX);

    return 0;
}