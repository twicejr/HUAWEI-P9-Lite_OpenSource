/**
 * @file
 * Defines makros for comepile time checks.
 * @author    f73150
 * @author    Frans Roselius
 * @version
 * @date      1990-2011
 * @copyright Huawei Technologies Sweden AB
 *
 * @code
 * Global functions:
 *   STATIC_ASSERT
 *   GLOBAL_STATIC_ASSERT
 *@endcode
 */

/**
 * Compile time assert to use in functions
 *
 * @param[in] expr Expresion to verify.
 * @param[in] msg Message printed by the compiler in
 *                case of assertion failure. Can not comtain space.
 */
#ifndef FWK_STATIC_ASSERT_H
#define FWK_STATIC_ASSERT_H
#if !(defined( _lint ) || defined( __COVERITY__ ))

#define STATIC_ASSERT(expr,msg)                     \
    {                                               \
        char STATIC_ASSERTION__##msg[(expr)?1:-1];  \
        (void)STATIC_ASSERTION__##msg[0];           \
    }

#define GLOBAL_STATIC_ASSERT(expr,msg)                                  \
    extern char STATIC_ASSERTION__##msg[1];                             \
    extern char STATIC_ASSERTION__##msg[(expr)?1:2]

#else
void lint_silencer(void);

/* When using static asserts. Silent lint 19 (Useless Declaration) */

#define STATIC_ASSERT(expr,msg)
#define GLOBAL_STATIC_ASSERT(expr,msg)   /*lint -save -e19, Useless Declaration */ /*lint -restore */

#endif
#endif /* FWK_STATIC_ASSERT_H */
