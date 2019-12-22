#include <ctype.h>

#include "token.h"

size_t next_token(const char* string, size_t length, token* tk) {
    if (tk)
        tk->type = TOKEN_NAME;

    size_t i, skip = 0;

    for (i = 0; i < length; i++) {
        char c = string[i];

        if (c == '"') {
            // TODO: String
        } else if (c == '#') {
            // TODO: Comment
        } else if (isspace(c)) {
            while (i + skip < length && isspace(string[i + skip]))
                skip++;
            break;
        } else if (ispunct(c)) {
            if (i > 0)
                break;

            if (tk) {
                tk->type = TOKEN_SYMBOL;
                tk->value.small.data[i++] = c;
                break;
            }
        }

        if (tk)
            tk->value.small.data[i] = c;
    }

    if (tk)
        tk->value.small.length = i;
    
    return i + skip;
}