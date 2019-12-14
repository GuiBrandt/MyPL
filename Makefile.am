bin_PROGRAMS = pl lex parse

noinst_LIBRARIES = lexer parser

lexer_SOURCES = src/lexer/token.c
parser_SOURCES = 

lex_SOURCES = src/lexer/main.c
lex_LDADD = lexer

parse_SOURCES = src/parser/main.c
parse_LDADD = parser

pl_SOURCES = src/main.c
pl_LDADD = lexer parser

SUBDIRS = tests

EXTRA_DIST = Makefile.dist