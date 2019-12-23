#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>

#include "token.h"

bool issymbol(char c) { return c != '_' && ispunct(c); }

size_t next_token(const char* string, size_t length, token* tk) {
    if (tk)
        tk->type = TOKEN_NAME;

    size_t i, skip = 0;

    for (i = 0; i + skip < length; i++) {
        char c = string[i + skip];

        if (c == '"') {
            // TODO: String
        } else if (c == '#') {
            // TODO: Comment
        } else if (isspace(c)) {
            while (i + skip < length && isspace(string[i + skip]))
                skip++;
            
            if (i > 0)
                break;
            else {
                i--;
                continue;
            }
        } else if (issymbol(c)) {
            if (i > 0)
                break;

            if (tk) {
                tk->type = TOKEN_SYMBOL;
                for (; i < length && issymbol(string[i]); i++)
                    tk->value.small.data[i] = string[i];
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