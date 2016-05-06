/*!
 *****************************************************************************
 *
 * @File       mem_io.h
 * @Title      Memory structure access macros.
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

#if !defined (__MEM_IO_H__)
#define __MEM_IO_H__

#if defined (__cplusplus)
extern "C" {
#endif

#include "img_types.h"

#define RND_TO_WORDS(size) (((size + 3) / 4) * 4)

#ifdef DOXYGEN_WILL_SEE_THIS
/*!
******************************************************************************

 @Function    MEMIO_READ_FIELD

 @Description

 This macro is used to extract a field from a packed memory based structure.

 @Input        vpMem : A pointer to the memory structure.

 @Input        field : The name of the field to be extracted.

 @Return    IMG_UINT : The value of the field - right aligned.
                       The actual type of the field depends on its size
                       and can be found in the header file defining the field.
                       The value read may need a cast to fit into storing
                       variable.

******************************************************************************/
IMG_UINT MEMIO_READ_FIELD(IMG_VOID * vpMem, IMG_VOID * field);

/*!
******************************************************************************

 @Function    MEMIO_READ_TABLE_FIELD

 @Description

 This macro is used to extract the value of a field in a table in a packed
 memory based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be extracted.

 @Input   ui32TabIndex : The table index of the field to be extracted.

 @Return      IMG_UINT : The value of the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.
                         The value read may need a cast to fit into storing
                         variable.

******************************************************************************/
IMG_UINT MEMIO_READ_TABLE_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT32 ui32TabIndex);

/*!
******************************************************************************

 @Function    MEMIO_READ_REPEATED_FIELD

 @Description

 This macro is used to extract the value of a repeated field in a packed
 memory based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be extracted.

 @Input   ui32RepIndex : The repeat index of the field to be extracted.

 @Return      IMG_UINT : The value of the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.
                         The value read may need a cast to fit into storing
                         variable.

******************************************************************************/
IMG_UINT MEMIO_READ_REPEATED_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT32 ui32RepIndex);

/*!
******************************************************************************

 @Function    MEMIO_READ_TABLE_REPEATED_FIELD

 @Description

 This macro is used to extract the value of a repeated field in a table
 in a packed memory based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be extracted.

 @Input   ui32TabIndex : The table index of the field to be extracted.

 @Input   ui32RepIndex : The repeat index of the field to be extracted.

 @Return      IMG_UINT : The value of the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.
                         The value read may need a cast to fit into storing
                         variable.

******************************************************************************/
IMG_UINT MEMIO_READ_TABLE_REPEATED_FIELD(IMG_VOID * vpMem, IMG_VOID * field,IMG_UINT32 ui32TabIndex, IMG_UINT32 ui32RepIndex);

/*!
******************************************************************************

 @Function    MEMIO_WRITE_FIELD

 @Description

 This macro is used to update the value of a field in a packed memory based
 structure.

 @Input     vpMem   : A pointer to the memory structure.

 @Input     field   : The name of the field to be updated.

 @Input     uiValue : The value to be written to the field - right aligned.
                      The actual type of the field depends on its size
                      and can be found in the header file defining the field.

 @Return    None.

******************************************************************************/
IMG_VOID MEMIO_WRITE_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT uiValue);

/*!
******************************************************************************

 @Function    MEMIO_WRITE_TABLE_FIELD

 @Description

 This macro is used to update the field in a table in a packed memory
 based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be updated.

 @Input   ui32TabIndex : The table index of the field to be updated.

 @Input        uiValue : The value to be written to the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.

 @Return    None.

******************************************************************************/
IMG_VOID MEMIO_WRITE_TABLE_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT32 ui32TabIndex, IMG_UINT uiValue);

/*!
******************************************************************************

 @Function    MEMIO_WRITE_REPEATED_FIELD

 @Description

 This macro is used to update a repeated field in a packed memory
 based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be updated.

 @Input   ui32RepIndex : The repeat index of the field to be updated.

 @Input        uiValue : The value to be written to the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.

 @Return    None.

******************************************************************************/
IMG_VOID MEMIO_WRITE_REPEATED_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT32 ui32RepIndex, IMG_UINT uiValue);


/*!
******************************************************************************

 @Function    MEMIO_WRITE_TABLE_REPEATED_FIELD

 @Description

 This macro is used to update a repeated field in a table in a packed memory
 based structure.

 @Input          vpMem : A pointer to the memory structure.

 @Input          field : The name of the field to be updated.

 @Input   ui32TabIndex : The table index of the field to be updated.

 @Input   ui32RepIndex : The repeat index of the field to be updated.

 @Input        uiValue : The value to be written to the field - right aligned.
                         The actual type of the field depends on its size
                         and can be found in the header file defining the field.

 @Return    None.

******************************************************************************/
IMG_VOID MEMIO_WRITE_TABLE_REPEATED_FIELD(IMG_VOID * vpMem, IMG_VOID * field, IMG_UINT32 ui32TabIndex, IMG_UINT32 ui32RepIndex, IMG_UINT uiValue);

#else

#if defined(WIN32) || defined(__linux__)
#define MEMIO_CHECK_ALIGNMENT(vpMem)        \
    IMG_ASSERT((vpMem))
#else
#define MEMIO_CHECK_ALIGNMENT(vpMem)        \
    IMG_ASSERT(((IMG_UINTPTR)(vpMem) & 0x3) == 0)
#endif

/*!
******************************************************************************

 @Function    MEMIO_READ_FIELD

******************************************************************************/
#if defined __RELEASE_DEBUG__

#define MEMIO_READ_FIELD(vpMem, field)                                                                         \
    ( MEMIO_CHECK_ALIGNMENT(vpMem),                                                                            \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & field##_MASK) >> field##_SHIFT)) )

#else

#if 1
#define MEMIO_READ_FIELD(vpMem, field)                                                                         \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & field##_MASK) >> field##_SHIFT))
#else
#define MEMIO_READ_FIELD(vpMem, field)                                                                         \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) >> field##_SHIFT) & field##_LSBMASK) )
#endif

#endif

/*!
******************************************************************************

 @Function    MEMIO_READ_TABLE_FIELD

******************************************************************************/
#if defined __RELEASE_DEBUG__

#define MEMIO_READ_TABLE_FIELD(vpMem, field, ui32TabIndex)                                                                                     \
    ( MEMIO_CHECK_ALIGNMENT(vpMem), IMG_ASSERT((ui32TabIndex < field##_NO_ENTRIES) || (field##_NO_ENTRIES == 0)),                              \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * ui32TabIndex)))) & field##_MASK) >> field##_SHIFT)) ) \

#else

#define MEMIO_READ_TABLE_FIELD(vpMem, field, ui32TabIndex)                                                                                     \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * ui32TabIndex)))) & field##_MASK) >> field##_SHIFT))   \

#endif


/*!
******************************************************************************

 @Function    MEMIO_READ_REPEATED_FIELD

******************************************************************************/
#if defined __RELEASE_DEBUG__

#define MEMIO_READ_REPEATED_FIELD(vpMem, field, ui32RepIndex)                                                                                                                     \
    ( MEMIO_CHECK_ALIGNMENT(vpMem),    IMG_ASSERT(ui32RepIndex < field##_NO_REPS),                                                                                                \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & (field##_MASK >> (ui32RepIndex * field##_SIZE))) >> (field##_SHIFT - (ui32RepIndex * field##_SIZE)))) ) \

#else

#define MEMIO_READ_REPEATED_FIELD(vpMem, field, ui32RepIndex)                                                                                                                     \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & (field##_MASK >> (ui32RepIndex * field##_SIZE))) >> (field##_SHIFT - (ui32RepIndex * field##_SIZE))) )  \

#endif
/*!
******************************************************************************

 @Function    MEMIO_READ_TABLE_REPEATED_FIELD

******************************************************************************/
#if defined __RELEASE_DEBUG__

#define MEMIO_READ_TABLE_REPEATED_FIELD(vpMem, field, ui32TabIndex, ui32RepIndex)                                                                                                                                  \
    ( MEMIO_CHECK_ALIGNMENT(vpMem), IMG_ASSERT((ui32TabIndex < field##_NO_ENTRIES) || (field##_NO_ENTRIES == 0)), IMG_ASSERT(ui32RepIndex < field##_NO_REPS), \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * ui32TabIndex)))) & (field##_MASK >> (ui32RepIndex * field##_SIZE))) >> (field##_SHIFT - (ui32RepIndex * field##_SIZE))))) \

#else

#define MEMIO_READ_TABLE_REPEATED_FIELD(vpMem, field, ui32TabIndex, ui32RepIndex)                                                                                                                                  \
    ((((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * ui32TabIndex)))) & (field##_MASK >> (ui32RepIndex * field##_SIZE))) >> (field##_SHIFT - (ui32RepIndex * field##_SIZE))))  \

#endif

/*!
******************************************************************************

 @Function    MEMIO_WRITE_FIELD

******************************************************************************/
#define MEMIO_WRITE_FIELD(vpMem, field, uiValue)                                                       \
    MEMIO_CHECK_ALIGNMENT(vpMem);                                                                      \
    (*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) =                                 \
    (field##_TYPE)(((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & ~(field##_TYPE)field##_MASK) | \
        (field##_TYPE)(( (uiValue) << field##_SHIFT) & field##_MASK));

#define MEMIO_WRITE_FIELD_LITE(vpMem, field, uiValue)                                                  \
    MEMIO_CHECK_ALIGNMENT(vpMem);                                                                      \
     (*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) =                                \
    ((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) |                                \
        (field##_TYPE) (( (uiValue) << field##_SHIFT)) );

/*!
******************************************************************************

 @Function    MEMIO_WRITE_TABLE_FIELD
******************************************************************************/
#define MEMIO_WRITE_TABLE_FIELD(vpMem, field, ui32TabIndex, uiValue)                                                                           \
    MEMIO_CHECK_ALIGNMENT(vpMem); IMG_ASSERT(((ui32TabIndex) < field##_NO_ENTRIES) || (field##_NO_ENTRIES == 0));                              \
    (*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * (ui32TabIndex))))) =                                     \
        ((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * (ui32TabIndex))))) & (field##_TYPE)~field##_MASK) | \
        (field##_TYPE)(((uiValue) << field##_SHIFT) & field##_MASK);

/*!
******************************************************************************

 @Function    MEMIO_WRITE_REPEATED_FIELD

******************************************************************************/
#define MEMIO_WRITE_REPEATED_FIELD(vpMem, field, ui32RepIndex, uiValue)                                                                       \
    MEMIO_CHECK_ALIGNMENT(vpMem); IMG_ASSERT((ui32RepIndex) < field##_NO_REPS);                                                               \
    (*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) =                                                                        \
    ((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET))) & (field##_TYPE)~(field##_MASK >> ((ui32RepIndex) * field##_SIZE)) |    \
        (field##_TYPE)(((uiValue) << (field##_SHIFT - ((ui32RepIndex) * field##_SIZE))) & (field##_MASK >> ((ui32RepIndex) * field##_SIZE))));

/*!
******************************************************************************

 @Function    MEMIO_WRITE_TABLE_REPEATED_FIELD

******************************************************************************/
#define MEMIO_WRITE_TABLE_REPEATED_FIELD(vpMem, field, ui32TabIndex, ui32RepIndex, uiValue)                                                                                         \
    MEMIO_CHECK_ALIGNMENT(vpMem); IMG_ASSERT(((ui32TabIndex) < field##_NO_ENTRIES) || (field##_NO_ENTRIES == 0)); IMG_ASSERT((ui32RepIndex) < field##_NO_REPS);                     \
    (*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * (ui32TabIndex))))) =                                                                          \
        ((*((field##_TYPE *)(((IMG_UINTPTR)(vpMem)) + field##_OFFSET + (field##_STRIDE * (ui32TabIndex))))) & (field##_TYPE)~(field##_MASK >> ((ui32RepIndex) * field##_SIZE))) | \
        (field##_TYPE)(((uiValue) << (field##_SHIFT - ((ui32RepIndex) * field##_SIZE))) & (field##_MASK >> ((ui32RepIndex) * field##_SIZE)));

#endif


#if defined (__cplusplus)
}
#endif

#endif


