#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <util/trie_set.h>

#include <lexer/token.h>

static inline bool issymbol(char c) { return c != '_' && ispunct(c); }
static inline bool isoperator(const char* c);
static inline bool potential_operator(const char* c);

static size_t read_large_token(
    register const char* string,
    register size_t length,
    register size_t i,
    size_t skip,
    token* tk,
    char delimiter
);

typedef struct _large_token_block large_token_block;

size_t next_token(register const char* string, register size_t length, token* tk) {
    if (tk) {
        tk->value.small.length = 0;
        tk->type = TOKEN_NAME;
    }

    register size_t i, skip = 0;

    if (string[0] != '\n' && isspace(string[0]))
        while (skip < length && isspace(string[skip]))
            skip++;

    if (tk && isdigit(string[skip]))
        tk->type = TOKEN_LITERAL;

    for (i = 0; i + skip < length; i++) {
        register char c = string[i + skip];

        if (c == '"' || c == '\'') {
            skip++;
            i = read_large_token(string, length, i, skip, tk, c);
            skip++;

            if (tk)
                tk->type = TOKEN_STRING;
            break;
        } else if (c == '#') {
            skip++;
            i = read_large_token(string, length, i, skip, tk, '\n');

            if (tk)
                tk->type = TOKEN_COMMENT;
            break;
        } else if (c == '\n') {
            if (i > 0)
                break;

            skip++;

            if (tk)
                tk->type = TOKEN_LINEBREAK;
            break;
        } else if (isspace(c)) {
            while (i + skip < length && isspace(string[i + skip]))
                skip++;

            break;
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

inline bool isoperator(const char* string) {
    return trie_contains(&operators, string);
}

inline bool potential_operator(const char* string) {
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

size_t read_large_token(
    register const char* string,
    register size_t length,
    register size_t i,
    size_t skip,
    token* tk,
    char delimiter
) {
    large_token_block* block;
    if (tk) {
        block = &tk->value.large;
        block->length = 0;
        block->next = NULL;
    }

    bool escape = false;
    while (escape || string[i + skip] != delimiter) {
        if (string[i + skip] == '\\')
            escape ^= true;
        else
            escape = false;

        if (!tk)
            continue;
        
        if (block->length == sizeof(block->data)) {
            large_token_block* next = (large_token_block*)malloc(sizeof(large_token_block));
            next->length = 0;
            next->next = NULL;
            block->next = next;
            block = next;
        }

        block->data[block->length] = string[i + skip];
        block->length++;

        i++;

        if (i + skip >= length)
            exit(-1);  // TODO: Create some kind of error manager
    }

    return i;
}