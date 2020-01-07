/**
 * @file token.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 * 
 * @version 0.1
 * @date 2019-12-01
 * 
 * @brief Lexemes definition and utils.
 * 
 * 
 * In computing, a lexical token or simply token is a string with assigned and
 * thus identified meaning [1]. 
 * 
 * The tokenization process (i.e., the conversion from a string to a collection
 * of tokens) is the first step in processing source code into meaningful
 * structure that can be analysed and executed as a sequence of instructions.
 * This would not be necessary if our language's syntax was simple enough that
 * simple string comparisons alone could handle it, but that's not the case
 * here.
 * 
 * [1]: https://en.wikipedia.org/wiki/Lexical_analysis#Token
 *  
 */

#ifndef __MYPL_TOKEN_H__
#define __MYPL_TOKEN_H__

#include <stddef.h>

/** Token type enumeration.
 * 
 * - `TOKEN_NAME`: Identifiers, such as variable names.
 * - `TOKEN_KEYWORD`: `if`, `else`, `while`, etc.
 * - `TOKEN_SYMBOL`: `(`, `)`, `,`, `:`, etc. 
 * - `TOKEN_OPERATOR`: `+`, `!=`, `^`, `<`, etc.
 * - `TOKEN_LITERAL`: Numbers, `null`, `true`/`false`, etc.
 * - `TOKEN_STRING`: Text strings.
 * - `TOKEN_COMMENT`: Comments, of course.
 * - `TOKEN_LINEBREAK`: Obviously, line breaks. This is used in analysis to
 *    determine where an error comes from.
 * 
 * The values here are specially assigned in a way that checks can be done
 * efficiently later with some bit-masking.
 * 
 * `TOKEN_LARGE` is not a possible value, and only exists to make token
 * properties more clear.
 * 
 * Internally, `TOKEN_LARGE` marks tokens that are possible larger than 255
 * bytes.
 * 
 */
typedef enum _token_type {
    TOKEN_NAME      = 0x00,
    TOKEN_KEYWORD   = 0x01,
    TOKEN_SYMBOL    = 0x02,
    TOKEN_OPERATOR  = 0x03,
    TOKEN_LINEBREAK = 0x04,
    TOKEN_LITERAL   = 0x10,
    TOKEN_LARGE     = 0x20,
    TOKEN_STRING    = TOKEN_LITERAL  | TOKEN_LARGE,
    TOKEN_COMMENT   = TOKEN_LARGE
} token_type;

/** Token value union. */
union _token_value {
    /** Small token value (default).
     * 
     * Usually, tokens won't need more than 255 bytes.
     * This represents a string with a given length.
     * 
     */
    struct {
        unsigned char length; /**< String length. */
        char data[255]; /**< Actual token value. */
    } small;

    /** Large token value.
     * 
     * For strings and comments, tokens might extrapolate the 255 byte limit.
     * This is actually a linked list of strings of length 255.
     * 
     * Don't worry about comparison efficiency and the sorts though: this is
     * used only during the tokenization and parsing stages, where all we will
     * be doing with those large tokens is moving pointers to them around and
     * eventually writing them out somewhere else.
     * 
     */
    struct _large_token_block {
        unsigned char length; /**< Block length. */
        char data[255]; /**< Block value. */

        /** Pointer to next block.
         * 
         * This should be 0 if this is the last block on the string.
         * 
         */
        struct _large_token_block* next;  
    } large;
};

/** A token. */
typedef struct _token {
    enum _token_type type; /**< Token type */
    union _token_value value; /**< Token contents */
} token;

/** Consumes the next token on a string.
 * 
 * @param string the string.
 * @param length the string length.
 * @param out an output pointer to a token. If this is NULL, the token will be
 *            skipped.
 * 
 * @return size_t number of bytes until the end of the read token.
 * 
 */
size_t next_token(const char* string, size_t length, token* out);

/** Frees allocated memory for a token.
 * 
 * This function will free all blocks created for a large token.
 * It WILL NOT free the given pointer.
 * 
 * @param tk pointer to the token. Notice this pointer will not be freed.
 * 
 */
void free_token(token* tk);

#endif // __MYPL_TOKEN_H__
