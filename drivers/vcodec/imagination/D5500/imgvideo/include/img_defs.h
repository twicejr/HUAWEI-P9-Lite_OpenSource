/*!
 *****************************************************************************
 *
 * @File       img_defs.h
 * @Title      Base type definitions using C99 headers
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#ifndef __IMG_DEFS__
#define __IMG_DEFS__

#include "img_sysdefs.h" // system specific definitions

#ifdef __cplusplus
extern "C" {
#endif

/*
 * maybe endianness could be guessed:
 * #define is_bigendian() ( ((char)1) == 0 )
 * #define BYTE_ORDER (is_bigendian() ? BIG : SMALL)
 */

/*
 * 3 different allocation
 * - default: use of SYSMALLOC and SYSFREE
 * - check: count the number of calls to malloc, calloc and free
 * - test: uses a global variable to know if malloc or calloc will fail
 */

#ifdef IMG_MALLOC_CHECK
/*
 * this version uses external global variable that the main program must define
 *
 * WARNING: this is not thread safe!
 */
#include "img_types.h"

/**
 * @brief The number of successful calls to malloc AND calloc (used if IMG_MALLOC_CHECK)
 */
extern IMG_UINT32 gui32Alloc;
/**
 * @brief The number of calls to free (used if IMG_MALLOC_CHECK)
 */
extern IMG_UINT32 gui32Free;

static void* img_malloc_check(IMG_SIZE size)
{
    void* ptr = IMG_SYSMALLOC(size);
	if ( ptr != NULL ) gui32Alloc++;
	return ptr;
}

static void* img_calloc_check(IMG_SIZE nelem, IMG_SIZE elem_size)
{
    void* ptr = IMG_SYSCALLOC(nelem, elem_size);
	if ( ptr != NULL ) gui32Alloc++;
	return ptr;
}

static void img_free_check(void* ptr)
{
    IMG_SYSFREE(ptr);
	gui32Free++;
}

#define IMG_MALLOC(size) img_malloc_check(size)
#define IMG_CALLOC(nelem, elem_size) img_calloc_check(nelem, elem_size)
#define IMG_FREE(ptr) img_free_check(ptr)

#endif

#ifdef IMG_MALLOC_TEST
/*
 * this version uses and external global variable to know if the memory allocation should fail
 */
#include "img_types.h"
 
/**
 * @brief To know if memory allocation should fail (used if IMG_MALLOC_TEST)
 *
 * The value must be set before calling IMG_MALLOC or IMG_CALLOC.
 * The functions will behave:
 * @li if the value is 0 allocation succeeds
 * @li if value is 1 allocations fails (and values becomes 0)
 * @li if value is > 0 value is decremented
 * 
 * This behaviour can be used to test allocation process (e.g. set gui32AllocFails to 5 and the 5th allocation after that will fail)
 *
 * @warning your code needs to define this variable (e.g. IMG_UINT32 guiAllocFails = 0;).
 * If your code is C++ don't forget the extern "C"
 */ 
extern IMG_UINT32 gui32AllocFails;

// return 1 when should allocate, 0 when should not
static int img_test_alloc(void)
{
	if (gui32AllocFails >= 1)
	{
		gui32AllocFails--;
		if ( gui32AllocFails == 0 )
		{
			// it was 1 -> should fail
			return 0;
		}
	}
	return 1;
}

static void* img_malloc_test(IMG_SIZE size)
{
	if (img_test_alloc())
	{
#ifdef IMG_MALLOC_CHECK
	  void* ptr = img_malloc_check(size);
#else
      void* ptr = IMG_SYSMALLOC(size);
#endif
		return ptr;
	}
	return NULL;
}
static void* img_calloc_test(IMG_SIZE nelem, IMG_SIZE elem_size)
{
	if (img_test_alloc())
	{
#ifdef IMG_MALLOC_CHECK
	  void* ptr = img_calloc_check(nelem, elem_size);
#else
      void* ptr = IMG_SYSCALLOC(nelem, elem_size);
#endif
		return ptr;
	}
	return NULL;
}

#ifdef IMG_MALLOC_CHECK
#undef IMG_MALLOC
#undef IMG_CALLOC
#endif

#define IMG_MALLOC(size) img_malloc_test(size)
#define IMG_CALLOC(nelem, elem_size) img_calloc_test(nelem, elem_size)

#endif

#ifdef IMG_MEM_ERROR_INJECTION
//#warning "Memory Error Injector redefines IMG_MALLOC, IMG_CALLOC, IMG_REALLOC, IMG_FREE!"
#include "mem_error_injector.h"
#ifdef IMG_MALLOC
#undef IMG_MALLOC
#endif
#define IMG_MALLOC(size)              MEMERRINJ_Malloc(size)
#ifdef IMG_CALLOC
#undef IMG_CALLOC
#endif
#define IMG_CALLOC(nelem, elem_size)  MEMERRINJ_Calloc(nelem, elem_size)
#ifdef IMG_FREE
#undef IMG_FREE
#endif
#define IMG_FREE(ptr)                 MEMERRINJ_Free(ptr)
#ifdef IMG_REALLOC
#undef IMG_REALLOC
#endif
#define IMG_REALLOC(ptr, size)        MEMERRINJ_Realloc(ptr, size)
#ifdef IMG_STRDUP
#undef IMG_STRDUP
#endif
#define IMG_STRDUP(ptr)               MEMERRINJ_Strdup(ptr)
#ifdef IMG_BIGALLOC
#undef IMG_BIGALLOC
#endif
#define IMG_BIGALLOC(size)          MEMERRINJ_BigMalloc(size)
#ifdef IMG_BIGFREE
#undef IMG_BIGFREE
#endif
#define IMG_BIGFREE(ptr)             MEMERRINJ_BigFree(ptr)
#endif /* IMG_MEM_ERROR_INJECTION */
/*
 * default use system allocation
 */
#ifndef IMG_MALLOC 
#define IMG_MALLOC(size)              IMG_SYSMALLOC(size)
#endif
#ifndef IMG_CALLOC
#define IMG_CALLOC(nelem, elem_size)  IMG_SYSCALLOC(nelem, elem_size)
#endif
#ifndef IMG_FREE
#define IMG_FREE(ptr)                 IMG_SYSFREE(ptr)
#endif
#ifndef IMG_REALLOC
#define IMG_REALLOC(ptr, size)        IMG_SYSREALLOC(ptr, size)
#endif
#ifndef IMG_STRDUP
#define IMG_STRDUP(ptr)               IMG_SYS_STRDUP(ptr)
#endif
#ifndef IMG_BIGALLOC
#define IMG_BIGALLOC(size)          IMG_SYSBIGALLOC(size)
#endif
#ifndef IMG_BIGFREE
#define IMG_BIGFREE(ptr)             IMG_SYSBIGFREE(ptr)
#endif

/// @note maybe this should be done in a function to know if it worked with another way than just assert...
#define IMG_UINT64_TO_UINT32(ui64Check) (IMG_ASSERT(((ui64Check) >> 32) == 0), (IMG_UINT32)(ui64Check))

/**
 * @brief Maximum of two integers without branches
 *
 * From http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 */
#define IMG_MAX_INT(x, y) ( (x) ^ ( ((x) ^ (y)) & -((x) < (y)) ) )

/**
 * @brief Minimum of two integers without branches
 *
 * From http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax
 */
#define IMG_MIN_INT(x, y) ( (y) ^ ( ((x) ^ (y)) & -((x) < (y)) ) )

/// compile time assert (e.g. for enum values)
#define IMG_STATIC_ASSERT( condition, name )\
	typedef char assert_failed_ ## name [ (condition) ? 1 : -1 ];

#ifdef __cplusplus
}
#endif

#endif // __IMG_DEFS__
