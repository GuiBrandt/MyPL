#ifndef __MYPL_PUBLIC_ERRORS_H__
#define __MYPL_PUBLIC_ERRORS_H__

/** MyPL error codes.
 * 
 * - `MYPL_ERR_OK`: No error.
 * - `MYPL_ERR_SYNTAX`: Failed to parse code due to syntax error.
 * 
 */
typedef enum _error_code {
    MYPL_ERR_OK = 0,
    MYPL_ERR_SYNTAX
} mypl_error_code;

mypl_error_code __mypl_last_error();
const char* __mypl_last_error_message();

/** Gets the last error code.
 * 
 * @see mypl_error_code
 * @see mypl_last_error_message 
 * @return mypl_error_code
 */
#define mypl_last_error __mypl_last_error()

/** Gets the last error message.
 * 
 * @return const char* the error message.
 */
#define mypl_last_error_message __mypl_last_error_message()

#endif // __MYPL_PUBLIC_ERRORS_H__
