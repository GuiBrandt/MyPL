#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <util/trie_set.h>

#include "token.h"

bool issymbol(char c) { return c != '_' && ispunct(c); }
bool isoperator(const char* c);
bool potential_operator(const char* c);

typedef struct _large_token_block large_token_block;

size_t next_token(register const char* string, register size_t length, token* tk) {
    if (tk) {
        tk->value.small.length = 0;
        tk->type = TOKEN_NAME;
    }

    register size_t i, skip = 0;

    for (i = 0; i + skip < length; i++) {
        register char c = string[i + skip];

        if (c == '"' || c == '\'') {
            large_token_block* block = &tk->value.large;

            bool escape = false;

            for (skip++; escape || string[i + skip] != c; i++) {
                if (i + skip >= length)
                    exit(-1);

                if (string[i + skip] == '\\')
                    escape ^= true;
                else
                    escape = false;

                if (!tk)
                    continue;
                
                if (block->length < sizeof(block->data)) {
                    block->data[i] = string[i + skip];
                    block->length++;
                } else {
                    large_token_block* next = (large_token_block*)malloc(sizeof(large_token_block));
                    next->length = 0;
                    next->next = NULL;
                    block->next = next;
                    block = next;
                }
            }
            
            skip++;

            if (tk)
                tk->type = TOKEN_STRING;
            break;
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

            char val[4] = {0};
            register size_t j;

            for (j = 0; j < 4 && i < length; i++, j++) {
                if (!issymbol(string[i + skip]))
                    break;
                
                val[j] = string[i + skip];
                if (j > 0 && !potential_operator(val)) {
                    val[j] = 0;
                    break;
                }
            }

            if (tk) {
                tk->type = isoperator(val) ? TOKEN_OPERATOR : TOKEN_SYMBOL;
                memcpy(tk->value.small.data, val, 4);
                tk->value.small.length = j;
            }
            break;
        } else if (tk)
            tk->value.small.data[tk->value.small.length++] = c;
    }
    
    return i + skip;
}

trie_set operators;

bool isoperator(const char* string) {
    return trie_contains(&operators, string);
}

bool potential_operator(const char* string) {
    return trie_contains_prefix(&operators, string);
}

void __attribute__((constructor)) init_token_sets() {
    static const char* _OPERATORS[] = {
        "+", "+=", "-", "-=", "*", "*=", "/", "/=", ">", ">=", "<", "<=", "%",
        "%=", ">>", "<<", ">>=", "<<=", "&", "&=", "|", "|=", "==", "!="
    };

    for (size_t i = 0; i * sizeof(char*) < sizeof(_OPERATORS); i++)
        trie_add(&operators, _OPERATORS[i]);
}