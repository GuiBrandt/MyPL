/**
 * @file errors.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 * 
 * @version 0.1
 * @date 2020-01-06
 * 
 * @brief Error management.
 *  
 */

#ifndef __MYPL_ERRORS_H__
#define __MYPL_ERRORS_H__

#include <public/errors.h>

#include <setjmp.h>

#define __mypl_exception_name(exception) __mypl_ex_ ## exception

/** Sets error information.
 * 
 * @param code the error code.
 * @param message the error message.
 * 
 */
void mypl_set_last_error(mypl_error_code code, const char* message);

/** Declares a possible exception.
 * 
 * @param exception the exception name.
 * 
 */
#define mypl_exception(exception) jmp_buf __mypl_exception_name(exception)

/** Defines behavior for handling an exception.
 * 
 * @param exception the exception name.
 * 
 */
#define mypl_catch(exception) if (setjmp(__mypl_exception_name(exception)))

/** Throws an exception.
 * 
 * @param exception the exception name.
 * 
 * @see mypl_exception
 * @see mypl_catch
 * 
 */
#define mypl_throw(exception) longjmp(__mypl_exception_name(exception), 1);

#endif // __MYPL_ERRORS_H__
