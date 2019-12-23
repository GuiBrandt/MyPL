#include <stdio.h>
#include <string.h>
#include <lexer/token.h>

void test_advances_pointer() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    size_t i = next_token(string, length, NULL);

    if (string[i] == 'd')
        printf("ok - tokenizer advances\n");
    else
        printf("not ok - tokenizer does not advance\n");
}

void test_gets_word() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    token t;

    size_t i = next_token(string, length, &t);
    string += i;
    length -= i;
    
    if (t.value.small.length != 3 ||
        memcmp(t.value.small.data, "abc", 3) != 0) {
        printf("not ok - tokenizer does not get a word\n");
        return;
    } else if (t.type != TOKEN_NAME) {
        printf("not ok - mismatched token type (expected name)\n");
        return;
    }
    
    next_token(string, length, &t);

    if (t.value.small.length != 5 ||
        memcmp(t.value.small.data, "defgh", 5) != 0) {
        printf("not ok - tokenizer does not get a word\n");
        return;
    } else if (t.type != TOKEN_NAME) {
        printf("not ok - mismatched token type (expected name)\n");
        return;
    }
    
    printf("ok - tokenizer gets word\n");
}

void test_splits_on_symbol() {
    int length = 10;
    char const* string = "abc+defgh";
    token t;
    
    next_token(string, length, &t);
    
    if (t.value.small.length == 3 && memcmp(t.value.small.data, "abc", 3) == 0)
        printf("ok - tokenizer splits tokens on symbols\n");
    else
        printf("not ok - tokenizer does not treat symbols\n");
}

void test_gets_alnum() {
    int length = 13;
    char const* string = "abc123 defgh";
    token t;
    
    next_token(string, length, &t);
    
    if (t.value.small.length != 6 ||
        memcmp(t.value.small.data, "abc123", 6) != 0) {
        printf("not ok - tokenizer does not get alphanumeric tokens\n");
        return;
    }

    if (t.type != TOKEN_NAME) {
        printf("not ok - mismatched token type (expected name)\n");
        return;
    }
    
    printf("ok - tokenizer gets alphanumeric tokens\n");
}

void test_merges_operators() {
    int length = 9;
    char const* string = "+= defgh";
    token t;
    
    next_token(string, length, &t);
    
    if (t.value.small.length != 2 || memcmp(t.value.small.data, "+=", 2) != 0) {
        printf("not ok - tokenizer does not merge operators\n");
        return;
    }

    if (t.type != TOKEN_OPERATOR) {
        printf("not ok - mismatched token type (expected operator) #TODO\n");
        return;
    }
    
    printf("ok - tokenizer merges operators\n");
}

void test_gets_number() {
    int length = 12;
    char const* string = "12345 defgh";
    token t;
    
    next_token(string, length, &t);

    if (t.value.small.length != 5 ||
        memcmp(t.value.small.data, "12345", 5) != 0) {
        printf("not ok - tokenizer does not get numeric tokens # TODO\n");
        return;
    }

    if (t.type != TOKEN_LITERAL) {
        printf("not ok - mismatched token type (expected literal) # TODO: "
               "differentiate between names and literals\n");
        return;
    }

    printf("ok - tokenizer gets numeric tokens\n");
}

void test_gets_symbol() {
    int length = 8;
    char const* string = "( defgh";
    token t;
    
    next_token(string, length, &t);
    
    if (t.value.small.length != 1 || memcmp(t.value.small.data, "(", 1) != 0) {
        printf("not ok - tokenizer does not get symbol tokens\n");
        return;
    }

    if (t.type != TOKEN_SYMBOL) {
        printf("not ok - mismatched token type (expected symbol) #TODO\n");
        return;
    }
    
    printf("ok - tokenizer gets symbol tokens\n");
}

void test_gets_string() {
    int length = 17;
    char const* string = "\"abc defg\" hijkl";
    token t;
    
    next_token(string, length, &t);
    
    if (t.value.small.length != 8 ||
        memcmp(t.value.small.data, "abc defg", 8) != 0) {
        printf("not ok - tokenizer does not get string tokens #TODO\n");
        return;
    }

    if (t.type != TOKEN_STRING) {
        printf("not ok - mismatched token type (expected string)\n");
        return;
    }

    printf("ok - tokenizer gets string tokens\n");
}

void test_linebreak() {
    int length = 28;
    char const* string = "abc\nghi";

    next_token(string, length, NULL);

    token t;
    size_t i = next_token(string, length, &t);
    string += i;
    length -= i;

    if (t.type != TOKEN_LINEBREAK) {
        printf("not ok - tokenizer does not yield linebreak token #TODO\n");
        return;
    }

    next_token(string, length, &t);
    if (t.value.small.length != 3 ||
        memcmp(t.value.small.data, "ghi", 3) != 0) {
        printf("not ok - does not get token after linebreak\n");
        return;
    }
    
    printf("ok - linebreaks work\n");
}

void test_gets_comment() {
    int length = 28;
    char const* string = "# abc def\nghi jkl";

    token t;
    size_t i = next_token(string, length, &t);
    string += i;
    length -= i;
    
    if (t.value.small.length != 8 ||
        memcmp(t.value.small.data, " abc def", 8) != 0) {
        printf("not ok - tokenizer does not get comments #TODO\n");
        return;
    }

    if (t.type != TOKEN_COMMENT) {
        printf("not ok - mismatched token type (expected comment)\n");
        return;
    }

    i = next_token(string, length, &t);
    string += i;
    length -= i;
    if (t.type != TOKEN_LINEBREAK) {
        printf("not ok - tokenizer does not yield linebreak token after"
               " comment\n");
        return;
    }

    i = next_token(string, length, &t);
    string += i;
    length -= i;
    if (t.value.small.length != 3 ||
        memcmp(t.value.small.data, "ghi", 3) != 0) {
        printf("not ok - does not get token after comment\n");
        return;
    }
    
    printf("ok - tokenizer gets comment tokens\n");
}

int main(int argc, char** argv) {
    printf("1..10\n");
    test_advances_pointer();
    test_gets_word();
    test_splits_on_symbol();
    test_gets_alnum();
    test_merges_operators();
    test_gets_number();
    test_gets_symbol();
    test_gets_string();
    test_gets_comment();
    test_linebreak();
    return 0;
}