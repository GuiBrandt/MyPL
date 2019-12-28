EXEEXT = .test
check_PROGRAMS = lexer trie_set avl_tree splay_tree

lexer_SOURCES = token.c
lexer_CFLAGS = -I../src
lexer_LDADD = ../liblexer.a ../libutil.a

trie_set_SOURCES = trie_set.c
trie_set_CFLAGS = -I../src
trie_set_LDADD = ../libutil.a

avl_tree_SOURCES = avl_tree.c
avl_tree_CFLAGS = -I../src
avl_tree_LDADD = ../libutil.a

splay_tree_SOURCES = splay_tree.c
splay_tree_CFLAGS = -I../src
splay_tree_LDADD = ../libutil.a

TESTS_ENVIRONMENT =
TEST_EXTENSIONS = .test

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL)\
                    $(top_srcdir)/build-aux/tap-driver.sh

TESTS = lexer.test trie_set.test splay_tree.test avl_tree.test
EXTRA_DIST = $(TESTS)
