EXEEXT = .test
check_PROGRAMS = lexer trie_set

lexer_SOURCES = token.c
lexer_CFLAGS = -I../src
lexer_LDADD = ../src/lexer/token.o

trie_set_SOURCES = trie_set.c
trie_set_CFLAGS = -I../src
trie_set_LDADD = ../src/util/trie_set.o

TESTS_ENVIRONMENT =
TEST_EXTENSIONS = .test

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL)\
                    $(top_srcdir)/build-aux/tap-driver.sh

TESTS = lexer.test trie_set.test
EXTRA_DIST = $(TESTS)
