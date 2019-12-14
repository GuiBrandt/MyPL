#include <stdio.h>
#include <string.h>
#include <lexer/token.h>

void test_advances_pointer() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    next_token(&length, &string);

    if (string[0] == 'd')
        printf("ok 1 - tokenizer advances\n");
    else
        printf("not ok 1 - tokenizer does not advance #TODO\n");
}

void test_updates_length() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    next_token(&length, &string);
    
    if (length == 16)
        printf("ok 2 - tokenizer updates string length\n");
    else
        printf("not ok 2 - tokenizer does not update string length #TODO\n");
}

void test_gets_word() {
    int length = 20;
    char const* string = "abc defgh ijklm nop";
    token t = next_token(&length, &string);
    
    if (memcmp(t.value.small.data, "abc", t.value.small.length) == 0)
        printf("ok 3 - tokenizer gets word\n");
    else
        printf("not ok 3 - tokenizer does not get a word #TODO\n");
}

void test_splits_on_symbol() {
    int length = 20;
    char const* string = "abc+defgh";
    token t = next_token(&length, &string);
    
    if (strcmp(t.value.small.data, "abc") == 0)
        printf("ok 4 - tokenizer splits tokens on symbols\n");
    else
        printf("not ok 4 - tokenizer does not treat symbols #TODO\n");
}

int main(int argc, char** argv) {
    printf("1..4\n");
    test_advances_pointer();
    test_updates_length();
    test_gets_word();
    test_splits_on_symbol();
    return 0;
}