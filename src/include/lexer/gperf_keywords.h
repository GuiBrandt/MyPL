/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf src/lexer/keywords.gperf  */
/* Computed positions: -k'1' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 14 "src/lexer/keywords.gperf"

static const struct _token_type_lookup_entry* lookup_token_type(const char*, size_t);
#line 12 "src/lexer/keywords.gperf"
struct _token_type_lookup_entry { char *name; token_type type; };
enum
  {
    TOTAL_KEYWORDS = 15,
    MIN_WORD_LENGTH = 2,
    MAX_WORD_LENGTH = 8,
    MIN_HASH_VALUE = 3,
    MAX_HASH_VALUE = 20
  };

/* maximum key range = 18, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_keyword (register const char *str, register size_t len)
{
  static const unsigned char asso_values[] =
    {
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 15,  5,
      15, 15,  0, 21, 21,  5, 21, 21, 21, 21,
      10, 21, 21, 21, 21,  0,  5, 21,  5, 10,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
      21, 21, 21, 21, 21, 21
    };
  return len + asso_values[(unsigned char)str[0]];
}

static const struct _token_type_lookup_entry keywords_list[] =
  {
    {(char*)0}, {(char*)0}, {(char*)0},
#line 22 "src/lexer/keywords.gperf"
    {"for", TOKEN_KEYWORD},
#line 33 "src/lexer/keywords.gperf"
    {"self", TOKEN_LITERAL},
#line 31 "src/lexer/keywords.gperf"
    {"false", TOKEN_LITERAL},
#line 25 "src/lexer/keywords.gperf"
    {"struct", TOKEN_KEYWORD},
#line 19 "src/lexer/keywords.gperf"
    {"if", TOKEN_KEYWORD},
#line 26 "src/lexer/keywords.gperf"
    {"var", TOKEN_KEYWORD},
#line 30 "src/lexer/keywords.gperf"
    {"true", TOKEN_LITERAL},
#line 27 "src/lexer/keywords.gperf"
    {"const", TOKEN_KEYWORD},
#line 29 "src/lexer/keywords.gperf"
    {"import", TOKEN_KEYWORD},
    {(char*)0},
#line 23 "src/lexer/keywords.gperf"
    {"continue", TOKEN_KEYWORD},
#line 32 "src/lexer/keywords.gperf"
    {"null", TOKEN_LITERAL},
#line 21 "src/lexer/keywords.gperf"
    {"while", TOKEN_KEYWORD},
    {(char*)0}, {(char*)0},
#line 28 "src/lexer/keywords.gperf"
    {"def", TOKEN_KEYWORD},
#line 20 "src/lexer/keywords.gperf"
    {"else", TOKEN_KEYWORD},
#line 24 "src/lexer/keywords.gperf"
    {"break", TOKEN_KEYWORD}
  };

const struct _token_type_lookup_entry *
lookup_token_type (register const char *str, register size_t len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash_keyword (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = keywords_list[key].name;

          if (s && *str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &keywords_list[key];
        }
    }
  return 0;
}
