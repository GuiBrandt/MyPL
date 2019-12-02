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
 * `TOKEN_LARGE` and `TOKEN_BREAKING` are not possible values, and only exist
 * to make token properties more clear.
 * 
 * Internally, `TOKEN_LARGE` marks tokens that are possible larger than 255
 * bytes, and `TOKEN_BREAKING` marks tokens that indicate token breaks (e.g.
 * symbols, when written immediately after names, should end the name token
 * processing and start its own token).
 * 
 */
typedef enum _token_type {
    TOKEN_NAME      = 0x00,
    TOKEN_KEYWORD   = 0x01,
    TOKEN_BREAKING  = 0x10,
    TOKEN_LITERAL   = 0x20,
    TOKEN_LARGE     = 0x40,
    TOKEN_SYMBOL    = TOKEN_BREAKING | 0x01,
    TOKEN_OPERATOR  = TOKEN_BREAKING | 0x02,
    TOKEN_LINEBREAK = TOKEN_BREAKING | 0x03,
    TOKEN_STRING    = TOKEN_LITERAL  | TOKEN_LARGE,
    TOKEN_COMMENT   = TOKEN_BREAKING | TOKEN_LARGE
} token_type;

/** Token value union. */
typedef union _token_value {
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
    struct _block {
        unsigned char length; /**< Block length. */
        char data[255]; /**< Block value. */

        /** Pointer to next block.
         * 
         * This should be 0 if this is the last block on the string.
         * 
         */
        struct _block* next;  
    } large;
} token_value;

/** A token. */
typedef struct _token {
    token_type type;
    token_value value;
} token;

/** Consumes the next token on a string.
 * 
 * This function will advance then pointer passed to it up until the start of
 * the next token or the end of the string, as well as change the length
 * pointer accordingly.
 * 
 * @param length a pointer to the string length.
 * @param string a pointer to the string.
 * 
 * @return token
 * 
 */
token next_token(unsigned int* const length, char const** const string);

#endif // __MYPL_TOKEN_H__
