#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <common/errors.h>
#include <common/attributes.h>

#include <util/trie_set.h>

#include <lexer/token.h>

static mypl_exception(large_token_no_end);

typedef struct _large_token_block large_token_block;

static bool issymbol(char c) { return c != '_' && ispunct(c); }
static bool isoperator(const char* c);
static bool potential_operator(const char* c);
static size_t read_large_token(
    register const char* string,
    register size_t length,
    register size_t i,
    size_t skip,
    token* tk,
    char delimiter
);

size_t next_token(register const char* string, register size_t length, token* tk) {
    if (tk) {
        tk->value.small.length = 0;
        tk->type = TOKEN_NAME;
        tk->value.large.next = NULL;
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
            mypl_catch(large_token_no_end) {
                mypl_set_last_error(MYPL_ERR_SYNTAX, "Unexpected EOF");
                return -1;
            }

            if (tk)
                tk->type = TOKEN_STRING;

            skip++;
            i = read_large_token(string, length, i, skip, tk, c);
            skip++;
            break;
        } else if (c == '#') {
            mypl_catch(large_token_no_end) break;
            
            if (tk)
                tk->type = TOKEN_COMMENT;

            skip++;
            i = read_large_token(string, length, i, skip, tk, '\n');
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

void free_large_token_block(large_token_block* block);

void free_token(token* tk) {
    if (!tk->value.large.next)
        return;
    free_large_token_block(tk->value.large.next);
}

void free_large_token_block(large_token_block* block) {
    if (block->next)
        free_large_token_block(block->next);
    free(block);
}

trie_set operators;

bool isoperator(const char* string) {
    return trie_contains(&operators, string);
}

bool potential_operator(const char* string) {
    return trie_contains_prefix(&operators, string);
}

constructor(init_token_sets) {
    static const char* _OPERATORS[] = {
        "+", "+=", "-", "-=", "*", "*=", "/", "/=", ">", ">=", "<", "<=", "%",
        "%=", ">>", "<<", ">>=", "<<=", "&", "&=", "|", "|=", "==", "!="
    };

    for (size_t i = 0; i * sizeof(char*) < sizeof(_OPERATORS); i++)
        trie_add(&operators, _OPERATORS[i]);
}

destructor(free_token_sets) {
    trie_free(&operators);
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
            mypl_throw(large_token_no_end);
    }

    return i;
}