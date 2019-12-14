EXEEXT = .test
check_PROGRAMS = lexer

lexer_SOURCES = token.c
lexer_CFLAGS = -I../src
lexer_LDADD = ../src/lexer/token.o

TESTS_ENVIRONMENT =
TEST_EXTENSIONS = .test

TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL)\
                    $(top_srcdir)/build-aux/tap-driver.sh

TESTS = lexer.test
EXTRA_DIST = $(TESTS)
