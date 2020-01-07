/**
 * @file attributes.h
 * @author Guilherme Brandt (gui.g.brandt@gmail.com)
 * 
 * @version 0.1
 * @date 2020-01-06
 * 
 * @brief Portable __attribute__ directives.
 *  
 */

#ifndef __MYPL_ATTRIBUTES_H__
#define __MYPL_ATTRIBUTES_H__

#ifdef _MSC_VER
    #pragma section(".CRT$XCU", read)
    #define __constructor(f, p)\
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f ## _)(void) = f; \
        __pragma(comment(linker,"/include:" p # f "_")) \
        static void f(void)
    #ifdef _WIN64
        #define constructor(f) __constructor(f, "")
    #else
        #define constructor(f) __constructor(f, "_")
    #endif
#else
    #define constructor(f) static void __attribute__((constructor)) f(void)
#endif

#ifdef _MSC_VER
    #pragma section(".CRT$XTX", read)
    #define __destructor(f, p)\
        static void f(void); \
        __declspec(allocate(".CRT$XTX")) void (*f ## _)(void) = f; \
        __pragma(comment(linker,"/include:" p # f "_")) \
        static void f(void)
    #ifdef _WIN64
        #define destructor(f) __destructor(f, "")
    #else
        #define destructor(f) __destructor(f, "_")
    #endif
#else
    #define destructor(f) static void __attribute__((destructor)) f(void)
#endif

#endif // __MYPL_ATTRIBUTES_H__
