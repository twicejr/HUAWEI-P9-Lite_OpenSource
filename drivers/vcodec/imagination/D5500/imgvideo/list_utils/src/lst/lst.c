/*!
 *****************************************************************************
 *
 * @File       lst.c
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

/*__TITLE__(Lists - single linked queues)*/
/*
** FILE NAME:     lst.c
**
** PROJECT:       Meta/DSP Software Library
**
** AUTHOR:        Ensigma Technologies
**
** DESCRIPTION:   List processing primitives
**
*/

/* controls for inline compilation */
#define LST_COMPILE
#ifdef LST_INLINE
#ifndef LST_CINCLUDE
#undef LST_COMPILE /* only compile through the H file when inlining */
#endif
#endif

#ifdef LST_COMPILE

#ifndef LST_INLINE
#include "lst.h"  /* don't re-include H file if inlining */
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#include "system.h"
LST_FQUALS void LST_add(LST_T *list, void *item)
{
    if (list->first == NULL)
    {
        list->first = item;
        list->last = item;
    }
    else
    {
        *(list->last) = item;   /* link to last item   */
        list->last = item;      /* update tail pointer */
    }
    *((void **)item) = NULL; /* terminate list      */
}
IMGVIDEO_EXPORT_SYMBOL(LST_add)

LST_FQUALS void LST_addHead(LST_T *list, void *item)
{
    if (list->first == NULL)
    {
        list->first = item;
        list->last = item;
        *((void **)item) = NULL; /* terminate list      */
    }
    else
    {
        *((void **)item) = list->first;
        list->first = item;   /* link to first item   */
//Original        *(list->first) = item;   /* link to first item   */
    }
}
IMGVIDEO_EXPORT_SYMBOL(LST_addHead)
LST_FQUALS int LST_empty(LST_T *list)
{
    return list->first == NULL;
}
IMGVIDEO_EXPORT_SYMBOL(LST_empty)

LST_FQUALS void *LST_first(LST_T *list)
{
    return list->first;
}
IMGVIDEO_EXPORT_SYMBOL(LST_first)

LST_FQUALS void LST_init(LST_T *list)
{
    list->first = NULL;
    list->last = NULL;
}

IMGVIDEO_EXPORT_SYMBOL(LST_init)
LST_FQUALS void *LST_last(LST_T *list)
{
    return list->last;
}
IMGVIDEO_EXPORT_SYMBOL(LST_last)

LST_FQUALS void *LST_next(void *item)
{
    return *((void **)item);
}
IMGVIDEO_EXPORT_SYMBOL(LST_next)

LST_FQUALS void *LST_removeHead(LST_T *list)
{
    void **temp = list->first;
    if (temp != NULL)
    {
        if ((list->first = *temp) == NULL)
        {
            list->last = NULL;
        }
    }
    return temp;
}
IMGVIDEO_EXPORT_SYMBOL(LST_removeHead)

LST_FQUALS void *LST_remove(LST_T *list, void *item)
{
    void **p;
    void **q;

    p = (void **)list;
    q = *p;
    while (q != NULL)
    {
        if (q == item)
        {
            *p = *q; /* unlink item */
            if (list->last == q)
            {
                list->last = p; /* update tail pointer when last item removed */
            }
            return item; /* premature return if item located and removed */
        }
        p = q;
        q = *p;
    }

    return NULL;
}
IMGVIDEO_EXPORT_SYMBOL(LST_remove)

LST_FQUALS int LST_check(LST_T *list, void *item)
{
    void **p;
    void **q;

    p = (void **)list;
    q = *p;
    while (q != NULL)
    {
        if (q == item)
        {
            return 1; /* premature return if item located */
        }
        p = q;
        q = *p;
    }

    return 0;
}
IMGVIDEO_EXPORT_SYMBOL(LST_check)

#endif



