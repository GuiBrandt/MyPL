bin_PROGRAMS = pl lex parse

noinst_LIBRARIES = liblexer.a libparser.a libutil.a

libutil_a_SOURCES = src/util/trie_set.c src/util/splay_tree.c\
                    src/util/avl_tree.c
liblexer_a_SOURCES = src/lexer/token.c
libparser_a_SOURCES = 

lex_SOURCES = src/lexer/main.c
lex_LDADD = liblexer.a

parse_SOURCES = src/parser/main.c
parse_LDADD = libparser.a

pl_SOURCES = src/main.c
pl_LDADD = liblexer.a libparser.a

SUBDIRS = tests

EXTRA_DIST = Makefile.dist