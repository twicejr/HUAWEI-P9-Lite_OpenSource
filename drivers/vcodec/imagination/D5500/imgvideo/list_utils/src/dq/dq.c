/*!
 *****************************************************************************
 *
 * @File       dq.c
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

/*__TITLE__(dqueues module) */
/*
** FILE NAME:     dq.c
**
** PROJECT:       Meta/DSP Software Library
**
** AUTHOR:        Ensigma Technologies
**
** DESCRIPTION:   Utility module for doubly linked queues
**
*/
/* controls for inline compilation */
#define DQ_COMPILE
#ifdef DQ_INLINE
#ifndef DQ_CINCLUDE
#undef DQ_COMPILE /* only compile through the H file when inlining */
#endif
#endif

#include "img_defs.h"

#ifdef DQ_COMPILE

#ifndef DQ_INLINE
#include "dq.h"  /* don't re-include H file if inlining */
#endif

#include "system.h"
#ifndef NULL
#define NULL ((void *)0)
#endif

#define DQ_EMPTY(Q) ((Q)->DQ_link.fwd == (DQ_LINKAGE_T *)(Q))

DQ_FQUALS void DQ_init(DQ_T *queue)
{
    queue->DQ_link.fwd = (DQ_LINKAGE_T *)queue;
    queue->DQ_link.back= (DQ_LINKAGE_T *)queue;
}

IMGVIDEO_EXPORT_SYMBOL(DQ_init)
DQ_FQUALS void DQ_addHead(DQ_T *queue, void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return;
    }

    ((DQ_LINKAGE_T *)item)->back = (DQ_LINKAGE_T *)queue;
    ((DQ_LINKAGE_T *)item)->fwd = ((DQ_LINKAGE_T *)queue)->fwd;
    ((DQ_LINKAGE_T *)queue)->fwd->back = (DQ_LINKAGE_T *)item;
    ((DQ_LINKAGE_T *)queue)->fwd = (DQ_LINKAGE_T *)item;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_addHead)

DQ_FQUALS void DQ_addTail(DQ_T *queue, void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return;
    }

    ((DQ_LINKAGE_T *)item)->fwd = (DQ_LINKAGE_T *)queue;
    ((DQ_LINKAGE_T *)item)->back = ((DQ_LINKAGE_T *)queue)->back;
    ((DQ_LINKAGE_T *)queue)->back->fwd = (DQ_LINKAGE_T *)item;
    ((DQ_LINKAGE_T *)queue)->back = (DQ_LINKAGE_T *)item;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_addTail)


DQ_FQUALS int DQ_empty(DQ_T *queue)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return 1;
    }

    return DQ_EMPTY(queue);
}
IMGVIDEO_EXPORT_SYMBOL(DQ_empty)

DQ_FQUALS void *DQ_first(DQ_T *queue)
{
    DQ_LINKAGE_T *temp = queue->DQ_link.fwd;

    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return NULL;
    }

    return temp == (DQ_LINKAGE_T *)queue ? NULL : temp;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_first)

DQ_FQUALS void *DQ_last(DQ_T *queue)
{
    DQ_LINKAGE_T *temp = queue->DQ_link.back;

    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return NULL;
    }

    return temp == (DQ_LINKAGE_T *)queue ? NULL : temp;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_last)

DQ_FQUALS void *DQ_next(void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->fwd != NULL);

    if(((DQ_LINKAGE_T *)item)->back == NULL ||
        ((DQ_LINKAGE_T *)item)->fwd == NULL)
    {
        return NULL;
    }

    return ((DQ_LINKAGE_T *)item)->fwd;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_next)

DQ_FQUALS void *DQ_previous(void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->fwd != NULL);

    if(((DQ_LINKAGE_T *)item)->back == NULL ||
        ((DQ_LINKAGE_T *)item)->fwd == NULL)
    {
        return NULL;
    }

    return ((DQ_LINKAGE_T *)item)->back;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_previous)

DQ_FQUALS void DQ_remove(void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)item)->fwd != NULL);

    if(((DQ_LINKAGE_T *)item)->back == NULL ||
        ((DQ_LINKAGE_T *)item)->fwd == NULL)
    {
        return;
    }

    ((DQ_LINKAGE_T *)item)->fwd->back = ((DQ_LINKAGE_T *)item)->back;
    ((DQ_LINKAGE_T *)item)->back->fwd = ((DQ_LINKAGE_T *)item)->fwd;

    /* make item linkages safe for "orphan" removes */
    ((DQ_LINKAGE_T *)item)->fwd = item;
    ((DQ_LINKAGE_T *)item)->back = item;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_remove)

DQ_FQUALS void *DQ_removeHead(DQ_T *queue)
{
    DQ_LINKAGE_T *temp;
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return NULL;
    }
    
    if (DQ_EMPTY(queue))
        return NULL;

    temp = ((DQ_LINKAGE_T *)queue)->fwd;
    temp->fwd->back = temp->back;
    temp->back->fwd = temp->fwd;

    /* make item linkages safe for "orphan" removes */
    temp->fwd = temp;
    temp->back = temp;
    return temp;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_removeHead)

DQ_FQUALS void *DQ_removeTail(DQ_T *queue)
{
    DQ_LINKAGE_T *temp;
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)queue)->fwd != NULL);

    if(((DQ_LINKAGE_T *)queue)->back == NULL ||
        ((DQ_LINKAGE_T *)queue)->fwd == NULL)
    {
        return NULL;
    }

    if (DQ_EMPTY(queue))
        return NULL;

    temp = ((DQ_LINKAGE_T *)queue)->back;
    temp->fwd->back = temp->back;
    temp->back->fwd = temp->fwd;

    /* make item linkages safe for "orphan" removes */
    temp->fwd = temp;
    temp->back = temp;

    return temp;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_removeTail)

DQ_FQUALS void DQ_addBefore(void *successor, void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)successor)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)successor)->fwd != NULL);

    if(((DQ_LINKAGE_T *)successor)->back == NULL ||
        ((DQ_LINKAGE_T *)successor)->fwd == NULL)
    {
        return;
    }

    ((DQ_LINKAGE_T *)item)->fwd = (DQ_LINKAGE_T *)successor;
    ((DQ_LINKAGE_T *)item)->back = ((DQ_LINKAGE_T *)successor)->back;
    ((DQ_LINKAGE_T *)item)->back->fwd = (DQ_LINKAGE_T *)item;
    ((DQ_LINKAGE_T *)successor)->back = (DQ_LINKAGE_T *)item;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_addBefore)

DQ_FQUALS void DQ_addAfter(void *predecessor, void *item)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)predecessor)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)predecessor)->fwd != NULL);

    if(((DQ_LINKAGE_T *)predecessor)->back == NULL ||
        ((DQ_LINKAGE_T *)predecessor)->fwd == NULL)
    {
        return;
    }

    ((DQ_LINKAGE_T *)item)->fwd = ((DQ_LINKAGE_T *)predecessor)->fwd;
    ((DQ_LINKAGE_T *)item)->back = (DQ_LINKAGE_T *)predecessor;
    ((DQ_LINKAGE_T *)item)->fwd->back = (DQ_LINKAGE_T *)item;
    ((DQ_LINKAGE_T *)predecessor)->fwd = (DQ_LINKAGE_T *)item;
}
IMGVIDEO_EXPORT_SYMBOL(DQ_addAfter)

DQ_FQUALS void DQ_move(DQ_T *from, DQ_T *to)
{
    IMG_ASSERT(((DQ_LINKAGE_T *)from)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)from)->fwd != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)to)->back != NULL);
    IMG_ASSERT(((DQ_LINKAGE_T *)to)->fwd != NULL);

    if(((DQ_LINKAGE_T *)from)->back == NULL ||
        ((DQ_LINKAGE_T *)from)->fwd == NULL ||
        ((DQ_LINKAGE_T *)to)->back == NULL ||
        ((DQ_LINKAGE_T *)to)->fwd == NULL)
    {
        return;
    }

    if (DQ_EMPTY(from))
        DQ_init(to);
    else
    {
        *to = *from;
        to->DQ_link.fwd->back = (DQ_LINKAGE_T *)to;
        to->DQ_link.back->fwd = (DQ_LINKAGE_T *)to;
        DQ_init(from);
    }
}
IMGVIDEO_EXPORT_SYMBOL(DQ_move)

#endif

