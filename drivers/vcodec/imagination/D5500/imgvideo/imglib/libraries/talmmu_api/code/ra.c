/*!
 *****************************************************************************
 *
 * @File       ra.c
 * @Title      Resource Allocator
 * @Description    Implements generic resource allocation. The resource
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

//Issues:
// - allocationflags are passed into the resource allocator but are not currently used.
// - determination, of import size, is currently braindead.
// - debug code should be moved out to own module and #ifdef'd
 
#include "hash.h"
#include "pool.h"
#include "ra.h"
#include "trace.h"
#include "img_defs.h"
#include "img_errors.h"

//The initial, and minimum ui64Size of the live address -> boundary tag structure hash table. 
//The value(64) is a fairly arbitrary choice. 
//The hash table resizes on demand so the value choosen is not critical. 

#define MINIMUM_HASH_SIZE  (64)
#define FREE_TABLE_LIMIT   (64)

//#define RA_DUMP
//#define RA_STATS

static IMG_BOOL gbInitialised = IMG_FALSE;

//Defines whether sequential or random allocation is used 
enum
{
    RA_SEQUENTIAL_ALLOCATION = 0,
    RA_RANDOM_ALLOCATION
};

//Boundary tags, used to describe a resource segment 
struct sBT
{
    enum 
    {
        RA_BOUNDARY_TAG_TYPE_SPAN = 0,  //span markers 
        RA_BOUNDARY_TAG_TYPE_FREE,      //free resource segment 
        RA_BOUNDARY_TAG_TYPE_LIVE,      //allocated resource segment 

        RA_BOUNDARY_TAG_TYPE_MAX
    } eBTType;

    //The base resource and extent of this segment 
    IMG_UINT64 ui64Base;
    IMG_UINT64 ui64Size;

    //doubly linked ordered list of all segments within the arena 
    struct sBT * psBTNextSegment;
    struct sBT * psBTPrevSegment;

    //doubly linked un-ordered list of free segments. 
    struct sBT * psBTNextFree;
    struct sBT * psBTPrevFree;

    //a user reference associated with this span, user references are
    //* currently only provided in the callback mechanism 
    IMG_VOID * pvRef;
};

//resource allocation arena 
struct sArena
{
    //arena pszName for diagnostics output 
    IMG_CHAR * pszName;

    //allocations within this arena are quantum sized 
    size_t quantum;

    //index of the last position in the psBTHeadFree table, with available free space
    IMG_UINT32 ui32MaxIndex;

    //import interface, if provided 
    IMG_RESULT(* pfnImportAlloc)( 
        IMG_HANDLE hImport, 
        IMG_UINT64 ui64RequestedSize, 
        IMG_UINT64 * pui64ActualSize, 
        IMG_VOID ** ppvRef, 
        unsigned ui32AllocationFlags, 
        IMG_UINT64 * pui64Base);

    IMG_RESULT(* pfnImportFree)(
        IMG_VOID*, 
        IMG_UINT64,
        IMG_VOID * pvRef);

    IMG_HANDLE hImport;

    //head of list of free boundary tags for indexed by Log2 of the boundary tag size 

    //power-of-two table of free lists 
    struct sBT * psBTHeadFree[FREE_TABLE_LIMIT];

    //resource ordered segment list 
    struct sBT * psBTHeadSegment;
    struct sBT * psBTTailSegment;

    //segment address to boundary tag hash table 
    struct sHash * psHash;

#ifdef RA_STATS
    //total number of segments add to the arena 
    IMG_UINT32 ui32SpanCount;

    //number of current live segments within the arena 
    IMG_UINT32 ui32LiveSegmentCount;

    //number of current free segments within the arena 
    IMG_UINT32 ui32FreeSegmentCount;

    //number of free resource within the arena 
    IMG_UINT64 ui64FreeResourceCount;

    //total number of resources allocated from the arena 
    IMG_UINT32 ui32TotalAllocs;

    //total number of resources returned to the arena 
    IMG_UINT32 ui32TotalFrees;

    //total number of spans allocated by the callback mechanism 
    IMG_UINT32 ui32ImportCount;

    //total number of spans deallocated by the callback mechanism 
    IMG_UINT32 ui32ExportCount;
#endif
};

//pool of struct arena's
static struct sPool * gpsPoolArena = IMG_NULL;

//pool of struct sBT's
static struct sPool * gpsPoolBt = IMG_NULL;

#ifdef RA_DUMP
    IMG_VOID ra_Dump(struct sArena * psArena);
#else
    #define ra_Dump(a)
#endif

#ifdef RA_STATS
    IMG_VOID ra_Stats(struct sArena * psArena);
#else
    #define ra_Stats(a)
#endif

/*!
******************************************************************************

 @Function				ra_RequestAllocFail

 @Description

 Default callback allocator used if no callback is specified, always fails
 to allocate further resources to the arena.

 @Input	    hImport             : Callback handle.

 @Input	    ui64RequestedSize   : Requested allocation size.

 @Input	    ppvRef              : Pointer to user reference data.

 @Input	    ui32AllocationFlags : Allocation flags.

 @Output    pui64ActualSize     : Pointer to contain the actual allocated size.

 @Output	pui64Base           : Allocation base(always 0,it is failing).

 @Return    IMG_RESULT          : IMG_SUCCESS or an error code.

*****************************************************************************/
static IMG_RESULT ra_RequestAllocFail(
                                      IMG_HANDLE hImport, 
                                      IMG_UINT64 ui64RequestedSize, 
                                      IMG_UINT64 * pui64ActualSize, 
                                      IMG_VOID ** ppvRef, 
                                      IMG_UINT32 ui32AllocationFlags, 
                                      IMG_UINT64 * pui64Base
)
{
    hImport = hImport;
    ui64RequestedSize = ui64RequestedSize;
    pui64ActualSize = pui64ActualSize;
    ppvRef = ppvRef;
    ui32AllocationFlags = ui32AllocationFlags;

    if (IMG_NULL != pui64Base)
    {
       (*pui64Base) = 0;
    }

    return IMG_SUCCESS;
}

/*!
*****************************************************************************

 @Function				ra_Log2

 @Description

 Calculates the Log2(n) with n being a 64-bit value.

 @Input	    ui64Value           : Input value.

 @Output    None

 @Return    ui32Result          : Log2(ui64Value).

*****************************************************************************/
static IMG_UINT32 ra_Log2(IMG_UINT64 ui64Value)
{
    IMG_UINT32 ui32Result = 0;
    ui64Value >>= 1;
    while(ui64Value > 0)
    {
        ui64Value >>= 1;
        ui32Result++;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_SegmentListInsertAfter

 @Description

 Insert a boundary tag into an arena segment list after a specified boundary tag.

 @Input	    psArena         : Pointer to the input arena.

 @Input	    psBTHere        : The boundary tag before which psBTToInsert 
                              will be added .

 @Input	    psBTToInsert    : The boundary tag to insert.

 @Output    None

 @Return    None

*****************************************************************************/
static IMG_VOID ra_SegmentListInsertAfter(
        struct sArena * psArena, 
        struct sBT * psBTHere, 
        struct sBT * psBTToInsert
)
{
    //Assuming to validate in the external functions
    //IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBTHere);
    //IMG_ASSERT(IMG_NULL != psBTToInsert);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBTHere ||
    //    IMG_NULL != psBTToInsert)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    psBTToInsert->psBTNextSegment = psBTHere->psBTNextSegment;
    psBTToInsert->psBTPrevSegment = psBTHere;

    if (IMG_NULL == psBTHere->psBTNextSegment)
    {
        psArena->psBTTailSegment = psBTToInsert;
    }
    else
    {
        psBTHere->psBTNextSegment->psBTPrevSegment = psBTToInsert; 
    }
    psBTHere->psBTNextSegment = psBTToInsert;

//    ui32Result = IMG_SUCCESS;
//
//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_SegmentListInsert

 @Description

 Insert a boundary tag into an arena segment list at the appropriate point.

 @Input	    psArena         : Pointer to the input arena.

 @Input	    psBTToInsert    : The boundary tag to insert.

 @Output    None

 @Return    None

*****************************************************************************/
static IMG_VOID ra_SegmentListInsert(
    struct sArena * psArena, 
    struct sBT * psBTToInsert
)
{
    //Assuming to validate in the external functions
    //IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBTToInsert);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBTToInsert)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    //insert into the segment chain 
    if (IMG_NULL == psArena->psBTHeadSegment)
    {
        psArena->psBTHeadSegment = psArena->psBTTailSegment = psBTToInsert;
        psBTToInsert->psBTNextSegment = psBTToInsert->psBTPrevSegment = IMG_NULL;
        //ui32Result = IMG_SUCCESS;
    }
    else
    {
        struct sBT * psBTScan = psArena->psBTHeadSegment;
        while( IMG_NULL != psBTScan->psBTNextSegment &&
                psBTToInsert->ui64Base >= psBTScan->psBTNextSegment->ui64Base)
        {
            psBTScan = psBTScan->psBTNextSegment;
        }
        //ui32Result = 
        ra_SegmentListInsertAfter(psArena, psBTScan, psBTToInsert);
    }

//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_SegmentListRemove

 @Description

 Insert a boundary tag into an arena segment list at the appropriate point.

 @Input	    psArena         : Pointer to the input arena.

 @Input	    psBTToInsert    : The boundary tag to insert.

 @Output    None

 @Return    None

*****************************************************************************/
static IMG_VOID ra_SegmentListRemove(
    struct sArena * psArena, 
    struct sBT * psBTToRemove
)
{
    //Assuming to validate in the external functions
    //IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBTToInsert);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBTToInsert)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    if (IMG_NULL == psBTToRemove->psBTPrevSegment)
    {
        psArena->psBTHeadSegment = psBTToRemove->psBTNextSegment;
    }
    else
    {
        psBTToRemove->psBTPrevSegment->psBTNextSegment = psBTToRemove->psBTNextSegment;
    }

    if (IMG_NULL == psBTToRemove->psBTNextSegment)
    {
        psArena->psBTTailSegment = psBTToRemove->psBTPrevSegment;
    }
    else
    {
        psBTToRemove->psBTNextSegment->psBTPrevSegment = psBTToRemove->psBTPrevSegment;
    }
//    ui32Result = IMG_SUCCESS;
//
//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_SegmentSplit

 @Description

 Split a segment into two, maintain the arena segment list. 
 The boundary tag should not be in the free table. Neither the original or
 the new psBTNeighbour bounary tag will be in the free table.

 @Input	    psArena         : Pointer to the input arena.

 @Input	    psBTToSplit     : The boundary tag to split.

 @Input	    psBTToSplit     : The required segment size of boundary tag 
                              after the split.

 @Output	None

 @Return    sBT *           : New boundary tag.

*****************************************************************************/
static struct sBT * ra_SegmentSplit(
        struct sArena * psArena, 
        struct sBT * psBTToSplit, 
        IMG_UINT64 ui64Size
)
{
    struct sBT * psBTNeighbour = IMG_NULL;
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;

    //Assuming to validate in the external functions
    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBTToSplit);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBTToSplit)
    //{
    //    psBTNeighbour = IMG_NULL;
    //    goto error;
    //}

    ui32Result = POOL_Alloc(gpsPoolBt,((IMG_HANDLE *)&psBTNeighbour));
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        psBTNeighbour = IMG_NULL;
        goto error;
    }

    psBTNeighbour->psBTPrevSegment = psBTToSplit;
    psBTNeighbour->psBTNextSegment = psBTToSplit->psBTNextSegment;
    psBTNeighbour->eBTType = RA_BOUNDARY_TAG_TYPE_FREE;
    psBTNeighbour->ui64Size =(psBTToSplit->ui64Size - ui64Size);
    psBTNeighbour->ui64Base =(psBTToSplit->ui64Base + ui64Size);
    psBTNeighbour->psBTNextFree = IMG_NULL;
    psBTNeighbour->psBTPrevFree = IMG_NULL;
    psBTNeighbour->pvRef = psBTToSplit->pvRef;

    if (IMG_NULL == psBTToSplit->psBTNextSegment)
    {
        psArena->psBTTailSegment = psBTNeighbour;
    }
    else
    {
        psBTToSplit->psBTNextSegment->psBTPrevSegment = psBTNeighbour;
    }
    psBTToSplit->psBTNextSegment = psBTNeighbour;
    psBTToSplit->ui64Size = ui64Size;

error:
    return psBTNeighbour;
}

/*!
******************************************************************************

 @Function				ra_FreeListInsert

 @Description

 Insert a boundary tag into an arena free table.

 @Input	    psArena : Pointer to the input arena.

 @Input	    psBT    : The boundary tag to insert into an arena free table.

 @Output    None

 @Return	None

*****************************************************************************/
static IMG_VOID ra_FreeListInsert(
        struct sArena * psArena, 
        struct sBT * psBT
)
{
    IMG_UINT32 ui32Index = ra_Log2(psBT->ui64Size);
    //Assuming to validate in the external functions
    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBT);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBT)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    psBT->eBTType = RA_BOUNDARY_TAG_TYPE_FREE;
    IMG_ASSERT(ui32Index < FREE_TABLE_LIMIT);
    if (ui32Index < FREE_TABLE_LIMIT)
    {
        psBT->psBTNextFree = psArena->psBTHeadFree[ui32Index];
    }
    else
    {
        psBT->psBTNextFree = IMG_NULL;
    }
    
    psBT->psBTPrevFree = IMG_NULL;

    if (IMG_NULL != psArena->psBTHeadFree[ui32Index])
    {
        psArena->psBTHeadFree[ui32Index]->psBTPrevFree = psBT;
    }

    IMG_ASSERT(ui32Index < FREE_TABLE_LIMIT);
    if (ui32Index < FREE_TABLE_LIMIT)
    {
        psArena->psBTHeadFree[ui32Index] = psBT;
    }

//  ui32Result = IMG_SUCCESS;
//
//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_FreeListRemove

 @Description

 Remove a boundary tag from an arena free table.

 @Input	    psArena : Pointer to the input arena.

 @Input	    psBT    : The boundary tag to remove from an arena free table.

 @Output    None

 @Return	None

*****************************************************************************/
static IMG_VOID ra_FreeListRemove(
    struct sArena * psArena, 
    struct sBT * psBT
)
{
    IMG_UINT32 ui32Index = ra_Log2(psBT->ui64Size);
    //Assuming to validate in the external functions
    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBT);

    //if (IMG_NULL != psArena ||
    //    IMG_NULL != psBT)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    if (psBT->psBTNextFree!=IMG_NULL)
    {
        psBT->psBTNextFree->psBTPrevFree = psBT->psBTPrevFree;
    }
    if (IMG_NULL == psBT->psBTPrevFree)
    {
        IMG_ASSERT(ui32Index < FREE_TABLE_LIMIT);
        if (ui32Index < FREE_TABLE_LIMIT)
        {
            psArena->psBTHeadFree[ui32Index] = psBT->psBTNextFree;
        }
    }
    else
    {
        psBT->psBTPrevFree->psBTNextFree = psBT->psBTNextFree;
    }
//  ui32Result = IMG_SUCCESS;
//
//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_SegmentSplit

 @Description

 Construct a span marker boundary tag.

 @Input	    psArena : The base of the boundary tag.

 @Output	None

 @Return    sBT *   : New span marker boundary tag

*****************************************************************************/
static struct sBT * ra_BuildSpanMarker(IMG_UINT64 ui64Base)
{
    struct sBT * psBT = IMG_NULL; 
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    ui32Result = POOL_Alloc(gpsPoolBt,((IMG_HANDLE *)&psBT));
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        psBT = IMG_NULL;
        goto error;
    }

    psBT->eBTType = RA_BOUNDARY_TAG_TYPE_SPAN;
    psBT->ui64Base = ui64Base;
    psBT->ui64Size = 0;
    psBT->psBTNextSegment = IMG_NULL;
    psBT->psBTPrevSegment = IMG_NULL;
    psBT->psBTNextFree = IMG_NULL;
    psBT->psBTPrevFree = IMG_NULL;
    psBT->pvRef = IMG_NULL;
error:
    return psBT;
}

/*!
******************************************************************************

 @Function				ra_BuildBT

 @Description

 Construct a boundary tag for a free segment.

 @Input	    ui64Base    : The base of the resource segment.

 @Input	    ui64Size    : The extent of the resource segment.

 @Output	None

 @Return    sBT *       : New boundary tag

*****************************************************************************/
static struct sBT * ra_BuildBT(
                             IMG_UINT64 ui64Base, 
                             IMG_UINT64 ui64Size
)
{
    struct sBT * psBT = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;        
        
    ui32Result = POOL_Alloc(gpsPoolBt,((IMG_HANDLE *)&psBT));

    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        psBT = IMG_NULL;
        goto error;
    }

    psBT->eBTType = RA_BOUNDARY_TAG_TYPE_FREE;
    psBT->ui64Base = ui64Base;
    psBT->ui64Size = ui64Size;
    psBT->psBTNextSegment = IMG_NULL;
    psBT->psBTPrevSegment = IMG_NULL;
    psBT->psBTNextFree = IMG_NULL;
    psBT->psBTPrevFree = IMG_NULL;
    psBT->pvRef = IMG_NULL;

error:
    return psBT;
}

/*!
******************************************************************************

 @Function				ra_InsertResource

 @Description

 Add a free resource segment to an arena.

 @Input	    ui64Base    : The base of the resource segment.

 @Input	    ui64Size    : The size of the resource segment.

 @Output	None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
static IMG_RESULT ra_InsertResource(
        struct sArena * psArena, 
        IMG_UINT64 ui64Base, 
        IMG_UINT64 ui64Size
)
{
    struct sBT * psBT = IMG_NULL;
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;
    //Assuming to validate in the external functions
    //IMG_ASSERT(IMG_NULL != psArena);
    //if (IMG_NULL != psArena)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

    psBT = ra_BuildBT(ui64Base, ui64Size);
    if (IMG_NULL == psBT)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error;
    }

    ra_SegmentListInsert(psArena, psBT);
    ra_FreeListInsert(psArena, psBT);
    psArena->ui32MaxIndex = ra_Log2(ui64Size);
    if ((IMG_UINT64)1<<psArena->ui32MaxIndex < ui64Size)
    {
        psArena->ui32MaxIndex++;
    }

#ifdef RA_STATS
    psArena->ui32SpanCount++;
#endif

    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_InsertResourceSpan

 @Description

 Add a free resource span to an arena, complete with span markers.

 @Input	    psArena     : Pointer to the input arena.

 @Input	    ui64Base    : The base of the resource segment.

 @Input	    ui64Size    : The size of the resource segment.

 @Output	None

 @Return    sBT *   : The boundary tag representing the free resource segment.

*****************************************************************************/
static struct sBT * ra_InsertResourceSpan(
        struct sArena * psArena, 
        IMG_UINT64 ui64Base, 
        IMG_UINT64 ui64Size
)
{
    struct sBT * psBT = IMG_NULL;
    struct sBT * psBTSpanStart = IMG_NULL;
    struct sBT * psBTSpanEnd = IMG_NULL;
    
    psBTSpanStart = ra_BuildSpanMarker(ui64Base);
    if (IMG_NULL == psBTSpanStart) 
    {
        psBT = IMG_NULL;
        goto error;
    }

    psBTSpanEnd = ra_BuildSpanMarker(ui64Base + ui64Size);
    if (IMG_NULL == psBTSpanEnd)
    {
        POOL_Free(gpsPoolBt, psBTSpanStart);
        psBT = IMG_NULL;
        goto error;
    }

    psBT = ra_BuildBT(ui64Base, ui64Size);
    if (IMG_NULL == psBT)
    {
        POOL_Free(gpsPoolBt, psBTSpanEnd);
        POOL_Free(gpsPoolBt, psBTSpanStart);
        psBT = IMG_NULL;
        goto error;
    }

    ra_SegmentListInsert(psArena, psBTSpanStart);
    ra_SegmentListInsertAfter(psArena, psBTSpanStart, psBT);
    ra_FreeListInsert(psArena, psBT);
    ra_SegmentListInsertAfter(psArena, psBT, psBTSpanEnd);

error:
    return psBT;
}

/*!
******************************************************************************

 @Function				ra_FreeBT

 @Description

 Free a boundary tag taking care of the segment list and the boundary tag free table.

 @Input	    psArena : Pointer to the input arena.

 @Input	    psBT    : The boundary tag to free.

 @Output    None

 @Return	None

*****************************************************************************/
static IMG_VOID ra_FreeBT(
        struct sArena * psArena, 
        struct sBT * psBT
)
{
    struct sBT * psBTNeighbour;
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;

    //IMG_ASSERT(IMG_NULL != psArena);
    //IMG_ASSERT(IMG_NULL != psBT);
    //if (IMG_NULL == psArena ||
    //    IMG_NULL ==  psBT)
    //{
    //    ui32Result = IMG_ERROR_INVALID_PARAMETERS;
    //    goto error;
    //}

#ifdef RA_STATS
    psArena->ui32LiveSegmentCount--;
    psArena->ui32FreeSegmentCount++;
    psArena->ui64FreeResourceCount += psBT->ui64Size;
#endif

    //try and coalesce with left psBTNeighbour 
    psBTNeighbour = psBT->psBTPrevSegment;
    if (IMG_NULL != psBTNeighbour && 
        psBTNeighbour->eBTType == RA_BOUNDARY_TAG_TYPE_FREE && 
        psBTNeighbour->ui64Base + psBTNeighbour->ui64Size == psBT->ui64Base)
    {
        ra_FreeListRemove(psArena, psBTNeighbour);
        ra_SegmentListRemove(psArena, psBTNeighbour);
        psBT->ui64Base = psBTNeighbour->ui64Base;
        psBT->ui64Size += psBTNeighbour->ui64Size;
        ui32Result = POOL_Free(gpsPoolBt, psBTNeighbour);
#ifdef RA_STATS
        psArena->ui32FreeSegmentCount--;
#endif
    }

    //try to coalesce with right psBTNeighbour 
    psBTNeighbour = psBT->psBTNextSegment;
    if (IMG_NULL != psBTNeighbour && 
        psBTNeighbour->eBTType == RA_BOUNDARY_TAG_TYPE_FREE && 
        psBT->ui64Base + psBT->ui64Size == psBTNeighbour->ui64Base)
    {
        ra_FreeListRemove(psArena, psBTNeighbour);
        ra_SegmentListRemove(psArena, psBTNeighbour);
        psBT->ui64Size += psBTNeighbour->ui64Size;
        ui32Result = POOL_Free(gpsPoolBt, psBTNeighbour);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            //Error Handling
        }
#ifdef RA_STATS
        psArena->ui32FreeSegmentCount--;
#endif
    }

    if (IMG_NULL != psBT->psBTNextSegment &&
        psBT->psBTNextSegment->eBTType == RA_BOUNDARY_TAG_TYPE_SPAN && 
        IMG_NULL != psBT->psBTPrevSegment && 
        psBT->psBTPrevSegment->eBTType == RA_BOUNDARY_TAG_TYPE_SPAN)
    {
        struct sBT * psBTNext = psBT->psBTNextSegment;
        struct sBT * psBTPrev = psBT->psBTPrevSegment;
        ra_SegmentListRemove(psArena, psBTNext);
        ra_SegmentListRemove(psArena, psBTPrev);
        ra_SegmentListRemove(psArena, psBT);
        psArena->pfnImportFree(psArena->hImport, psBT->ui64Base, psBT->pvRef);
#ifdef RA_STATS
        psArena->ui32SpanCount--;
        psArena->ui32ExportCount++;
        psArena->ui32FreeSegmentCount--;
        psArena->ui64FreeResourceCount -= psBT->ui64Size;
#endif
        ui32Result = POOL_Free(gpsPoolBt, psBTNext);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            //Error Handling
        }
        ui32Result = POOL_Free(gpsPoolBt, psBTPrev);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            //Error Handling
        }
        ui32Result = POOL_Free(gpsPoolBt, psBT);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            //Error Handling
        }
    } 
    else
    {
        ra_FreeListInsert(psArena, psBT);
    }

//    ui32Result = IMG_SUCCESS;
//
//error:
//    return ui32Result;
}

/*!
******************************************************************************

 @Function				ra_AttemptAllocAligned

 @Description

 Attempt ti allocate from an arena.

 @Input	    psArena     : Pointer to the input arena.

 @Input	    ui64Size    : The requested allocation size.

 @Input 	ppvRef      : The user references associated with the allocated segment.

 @Input	    alignment   : Required alignment.

 @Output 	pui64Base   : Allocated resource size.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
static IMG_RESULT ra_AttemptAllocAligned(
        struct sArena * psArena,
        IMG_UINT64 ui64Size,
        IMG_VOID ** ppvRef,
        IMG_UINT64 ui64Alignment,
        IMG_UINT64 * pui64Base
)
{
    IMG_UINT32 ui32Index;
    IMG_UINT32 ui32AlignmentLog2;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psArena);
    IMG_ASSERT(IMG_NULL != pui64Base);
    if (IMG_NULL == psArena ||
        IMG_NULL ==  pui64Base)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    //take the log of the alignment to get number of bits to shift left/right for multiply/divide.
    //Assumption made here is that alignment has to be a power of 2 value. Aserting otherwise. 

    IMG_ASSERT(!(ui64Alignment &(ui64Alignment -1 )));
    ui32AlignmentLog2 = ra_Log2(ui64Alignment);

    //search for a near fit free boundary tag, start looking at the log2 free table for our required
    //size and work on up the table. 
    ui32Index = ra_Log2(ui64Size);    

    //If the Size required is exactly 2**n then use the n bucket, because we know that every 
    //free block in that bucket is larger than 2**n, otherwise start at then next bucket up. 
    
    if ((1ull<<ui32Index) < ui64Size)
    {
        ui32Index++;
    }

    while((ui32Index < FREE_TABLE_LIMIT) &&(IMG_NULL == psArena->psBTHeadFree[ui32Index]))
    {
        ui32Index++;
    }
    while(ui32Index < FREE_TABLE_LIMIT)
    {
        if (IMG_NULL != psArena->psBTHeadFree[ui32Index])
        {
            //we have a cached free boundary tag 
            struct sBT * psBT = psArena->psBTHeadFree[ui32Index];
            while(IMG_NULL != psBT)
            {
                IMG_UINT64 ui64AlignmentBase;
                if (ui64Alignment >(IMG_UINT64)1)
                {
                    ui64AlignmentBase =((psBT->ui64Base + ui64Alignment - 1)  >> ui32AlignmentLog2 ) << ui32AlignmentLog2;
                }
                else
                {
                    ui64AlignmentBase = psBT->ui64Base;
                }
                trace(("  ra:ra_AttemptAllocAligned(), checking boundary tag\n"));
                if ((psBT->ui64Base + psBT->ui64Size) >=(ui64AlignmentBase + ui64Size))
                {
                    ra_FreeListRemove(psArena, psBT);

                    IMG_ASSERT(RA_BOUNDARY_TAG_TYPE_FREE == psBT->eBTType );

#ifdef RA_STATS
                    psArena->ui32LiveSegmentCount++;
                    psArena->ui32FreeSegmentCount--;
                    psArena->ui64FreeResourceCount -= psBT->ui64Size;
#endif
                    //with ui64Alignment we might need to discard the front of this segment 
                    if (ui64AlignmentBase > psBT->ui64Base)
                    {
                        struct sBT * psBTNeighbour;
                        psBTNeighbour = ra_SegmentSplit(psArena, psBT,(ui64AlignmentBase - psBT->ui64Base));
                        //partition the buffer, create a new boundary tag 
                        if (IMG_NULL == psBTNeighbour)
                        {
                            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                            goto error;
                        }
                        ra_FreeListInsert(psArena, psBT);
#ifdef RA_STATS
                        psArena->ui32FreeSegmentCount++;
                        psArena->ui64FreeResourceCount += psBT->ui64Size;
#endif
                        psBT = psBTNeighbour;
                    }

                    //the segment might be too big, if so, discard the back of the segment 
                    if (psBT->ui64Size > ui64Size)
                    {
                        struct sBT * psBTNeighbour;
                        psBTNeighbour = ra_SegmentSplit(psArena, psBT, ui64Size);
                        //partition the buffer, create a new boundary tag 
                        if (IMG_NULL == psBTNeighbour)
                        {
                            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                            goto error;
                        }
                        ra_FreeListInsert(psArena, psBTNeighbour);
#ifdef RA_STATS
                        psArena->ui32FreeSegmentCount++;
                        psArena->ui64FreeResourceCount += psBTNeighbour->ui64Size;
#endif
                    }

                    psBT->eBTType = RA_BOUNDARY_TAG_TYPE_LIVE;

                    ui32Result = VID_HASH_Insert(psArena->psHash, psBT->ui64Base,(IMG_UINTPTR)psBT);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        ra_FreeBT(psArena, psBT);
                        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                       (*pui64Base) = 0;
                        goto error;
                    }

                    if (IMG_NULL != ppvRef)
                    {
                       (*ppvRef) = psBT->pvRef;
                    }

                   (*pui64Base) = psBT->ui64Base;
                    ui32Result = IMG_SUCCESS;
                    goto success;
                }
                psBT = psBT->psBTNextFree;
            }
        }
        ui32Index++;
    }

success:
    ui32Result = IMG_SUCCESS;
error:
    return ui32Result;
}

#if !defined(IMG_KERNEL_MODULE)
/*!
******************************************************************************

 @Function				ra_AttemptRandomAllocAligned

 @Description

 Attempt ti allocate from an arena, selecting randomly the base address.

 @Input	    psArena     : Pointer to the input arena.

 @Input	    ui64Size    : The requested allocation size.

 @Input 	ppvRef      : The user references associated with the allocated segment.

 @Input	    alignment   : Required alignment.
.
 @Output 	pui64Base   : Allocated resource size.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
static IMG_RESULT ra_AttemptRandomAllocAligned(
        struct sArena * psArena,
        IMG_UINT64 ui64Size,
        IMG_VOID ** ppvRef,
        IMG_UINT64 ui64Alignment,
        IMG_UINT64 * pui64Base
)
{
    IMG_UINT32 ui32MinIndex;
    IMG_UINT32 ui32RandomIndex;
    IMG_UINT32 ui32Index;
    IMG_BOOL bBackwards = IMG_FALSE;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psArena);
    IMG_ASSERT(IMG_NULL != pui64Base);
    if (IMG_NULL == psArena ||
        IMG_NULL ==  pui64Base)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    //Determine the minimum possible index for the requested size in the log-based table.
    //Search for a near fit free boundary tag, start looking at the log2 free table for our 
    //required size and work on up the table. 
    ui32MinIndex = ra_Log2(ui64Size);

    //If the size required is exactly 2**n then use the n bucket, because we know that 
    //every free block in that bucket is larger than 2**n, otherwise start at then next bucket up. 
    if (1ull<<ui32MinIndex < ui64Size)
    {
        ui32MinIndex++;
    }

    //Select randomly an Index between the minimun and the maximum(determined by the size of the block) 
    ui32RandomIndex =(rand() %(psArena->ui32MaxIndex - ui32MinIndex + 1)) + ui32MinIndex;
    ui32Index = ui32RandomIndex;

    //From the Index selected, look forwards for the first Index where there are free segments 
    while((ui32Index <= psArena->ui32MaxIndex) &&(ui32Index < FREE_TABLE_LIMIT) &&(IMG_NULL == psArena->psBTHeadFree[ui32Index]))
    {
        ui32Index++;
    }

    if (ui32Index > psArena->ui32MaxIndex)
    {
        bBackwards = IMG_TRUE;

        //If not found forwards, look bBackwards from the selected ui32Index 
        ui32Index =(ui32RandomIndex - 1);
        while((ui32Index >= ui32MinIndex) &&(ui32Index < FREE_TABLE_LIMIT) &&(IMG_NULL == psArena->psBTHeadFree[ui32Index]))
        {
            ui32Index--;
        }

        //Not enough space in this block for the requested ui64Size 
        if (ui32Index < ui32MinIndex)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
    }

    //Starting from the selected position of the table, iterate to find suitable segments 
    while((ui32Index <= psArena->ui32MaxIndex) &&(ui32Index >= ui32MinIndex) &&(ui32Index < FREE_TABLE_LIMIT))
    {
        IMG_UINT64 ui64AlignmentBase;
        if (IMG_NULL != psArena->psBTHeadFree[ui32Index])
        {
            //we have a cached free boundary tag 
            struct sBT * psBT = IMG_NULL;
            IMG_UINT32 ui32NoFreeSegments = 0;
            IMG_UINT32 ui32RandomSegment;
            IMG_UINT64 ui32RandValue;
            IMG_UINT64 ui64PosNum;
            IMG_UINT64 ui32BreakDown;

            psBT = psArena->psBTHeadFree[ui32Index];

            //Count for the number of free segments in the list, large enough to allocate the requested ui64Size 
            while(IMG_NULL != psBT)
            {
                if (ui64Alignment >(IMG_UINT64)1)
                {
                    ui64AlignmentBase =((psBT->ui64Base + ui64Alignment - 1) / ui64Alignment) * ui64Alignment;
                }
                else
                {
                    ui64AlignmentBase = psBT->ui64Base;
                }

                if (psBT->ui64Base + psBT->ui64Size >= ui64AlignmentBase + ui64Size)
                {
                    ui32NoFreeSegments++;
                }
                psBT = psBT->psBTNextFree;
            }
            if (ui32NoFreeSegments == 0)
            {
                if (IMG_FALSE == bBackwards)
                {
                    ui32Index++;
                }
                else
                {
                    ui32Index--;
                }
                if (ui32Index > psArena->ui32MaxIndex)
                {
                    ui32Index = ui32RandomIndex-1;
                    bBackwards = IMG_TRUE;
                }
                continue;
            }

            //Select randomly one of the counted segments 
            ui32RandomSegment =(rand() % ui32NoFreeSegments) + 1;

            //Find the selected segment 
            psBT = psArena->psBTHeadFree [ui32Index];
            ui32NoFreeSegments = 0;

            while(IMG_NULL != psBT)
            {
                if (ui64Alignment >(IMG_UINT64)1)
                {
                    ui64AlignmentBase =((psBT->ui64Base + ui64Alignment - 1) / ui64Alignment) * ui64Alignment;
                }
                else
                {
                    ui64AlignmentBase = psBT->ui64Base;
                }

                if ((psBT->ui64Base + psBT->ui64Size) >=(ui64AlignmentBase + ui64Size))
                {
                    ui32NoFreeSegments++;
                    if (ui32NoFreeSegments == ui32RandomSegment)
                    {
                        break;
                    }
                }
                psBT = psBT->psBTNextFree;
            }

            //Select randomly a base address(properly aligned according to the alignment), within the segment 
            //Number of possible base addresses
            ui64PosNum =(psBT->ui64Base + psBT->ui64Size - ui64AlignmentBase - ui64Size) / ui64Alignment + 1;  

            //Gap between possible addresses
            ui32BreakDown =(IMG_UINT32)(ui64PosNum /(RAND_MAX+(IMG_UINT64)1) + 1); 

            //(possibilities have to be within the range of rand() ) 
            ui32RandValue = rand() %(ui64PosNum / ui32BreakDown);

            //Calculate the random ui64Base address
            ui64AlignmentBase +=(ui32RandValue * ui64Alignment * ui32BreakDown);	

            ra_FreeListRemove(psArena, psBT);
            IMG_ASSERT(RA_BOUNDARY_TAG_TYPE_FREE == psBT->eBTType);

#ifdef RA_STATS
            psArena->ui32LiveSegmentCount++;
            psArena->ui32FreeSegmentCount--;
            psArena->ui64FreeResourceCount-=psBT->ui64Size;
#endif

            //With alignment we might need to discard the front of this segment 
            if (ui64AlignmentBase > psBT->ui64Base)
            {
                struct sBT * psBTNeighbour = IMG_NULL;
                psBTNeighbour = ra_SegmentSplit(psArena, psBT, ui64AlignmentBase-psBT->ui64Base);

                //partition the buffer, create a new boundary tag 
                if (IMG_NULL == psBTNeighbour)
                {
                    ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                    goto error;
                }
                ra_FreeListInsert(psArena, psBT);
#ifdef RA_STATS
                psArena->ui32FreeSegmentCount++;
                psArena->ui64FreeResourceCount+=psBT->ui64Size;
#endif
                psBT = psBTNeighbour;
            }

            //The segment might be too big, if so, discard the back of the segment 
            if (psBT->ui64Size > ui64Size)
            {
                struct sBT * psBTNeighbour = IMG_NULL;
                psBTNeighbour = ra_SegmentSplit(psArena, psBT, ui64Size);

                //partition the buffer, create a new boundary tag 
                if (IMG_NULL == psBTNeighbour)
                {
                    ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                    goto error;
                }
                ra_FreeListInsert(psArena, psBTNeighbour);
#ifdef RA_STATS
                psArena->ui32FreeSegmentCount++;
                psArena->ui64FreeResourceCount+=psBTNeighbour->ui64Size;
#endif
            }

            psBT->eBTType = RA_BOUNDARY_TAG_TYPE_LIVE;

            ui32Result = VID_HASH_Insert(psArena->psHash, psBT->ui64Base,(IMG_UINTPTR)psBT);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if (IMG_SUCCESS != ui32Result)
            {
                ra_FreeBT(psArena, psBT);
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }

            if (IMG_NULL != ppvRef)
            {
               (*ppvRef) = psBT->pvRef;
            }

           (*pui64Base) = psBT->ui64Base;
            ui32Result = IMG_SUCCESS;
            goto success;

        }
        if (bBackwards == IMG_FALSE)
        {
            ui32Index++;
        }
        else
        {
            ui32Index--;
        }
        if (ui32Index > psArena->ui32MaxIndex)
        {
            ui32Index = ui32RandomIndex-1;
            bBackwards = IMG_TRUE;
        }
    }

success:
    ui32Result = IMG_SUCCESS;
error:
    return ui32Result;
}

#endif

/*!
******************************************************************************

 @Function				VID_RA_Initialise

 @Description

 Initialises the RA module. Must be called before any other ra API function.

 @Input	    None

 @Output 	None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    trace(("VID_RA_Initialise()\n"));

    IMG_ASSERT(IMG_FALSE == gbInitialised);
    if (!gbInitialised)
    {
        IMG_ASSERT(IMG_NULL == gpsPoolArena);
        IMG_ASSERT(IMG_NULL == gpsPoolBt);

        ui32Result = POOL_Create("img-arena", sizeof(struct sArena), &gpsPoolArena);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        ui32Result = POOL_Create("img-sBT", sizeof(struct sBT), &gpsPoolBt);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = POOL_Delete(gpsPoolArena);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            gpsPoolArena = IMG_NULL;
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
        gbInitialised = IMG_TRUE;
        ui32Result = IMG_SUCCESS;
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Finalise

 @Description

 Finalizes the RA module.

 @Input	    None

 @Output 	None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Finalise(IMG_VOID)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if (gbInitialised)
    {
        if (IMG_NULL != gpsPoolArena)
        {
            ui32Result = POOL_Delete(gpsPoolArena);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            gpsPoolArena = IMG_NULL;
        }
        if (IMG_NULL != gpsPoolBt)
        {
            ui32Result = POOL_Delete(gpsPoolBt);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            gpsPoolBt = IMG_NULL;
        }
        gbInitialised = IMG_FALSE;
        ui32Result = IMG_SUCCESS;
    }
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Create

 @Description

 Used to create a resource arena.

 @Input     pszName              : The name of the arena for diagnostic purposes.
    
 @Input     ui64Base             : The base of an initial resource span or 0.

 @Input     ui64Size             : The size of an initial resource span or 0.

 @Input     quantum              : The arena allocation quantum.

 @Input    (* pfnImportAlloc)   : A resource allocation callback or IMG_NULL.

 @Input    (* pfnImportFree)    : A resource de-allocation callback or IMG_NULL.

 @Input     hImport              : Handle passed to alloc and free or IMG_NULL.

 @Output    phArena              : The handle for the arene being created, or IMG_NULL.

 @Return    IMG_RESULT          : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Create(const IMG_CHAR * const pszName,
                      IMG_UINT64 ui64Base,
                      IMG_UINT64 ui64Size,		
                      size_t quantum,	
                      IMG_RESULT(* pfnImportAlloc)(IMG_HANDLE const hImport, 
                                                    IMG_UINT64 ui64RequestedSize, 
                                                    IMG_UINT64 * const pui64ActualSize, 
                                                    IMG_VOID ** const ppvRef, 
                                                    IMG_UINT32 ui32AllocationFlags, 
                                                    IMG_UINT64 * const pui64Base),
                      IMG_RESULT(* pfnImportFree)(IMG_HANDLE const hImport, 
                                                   IMG_UINT64 ui64ImportBase, 
                                                   IMG_VOID * const pvImportRef),
                      IMG_HANDLE hImport,
                      IMG_HANDLE * phArena
)
{
    struct sArena * psArena = IMG_NULL;
    IMG_UINT32 ui32Idx = 0;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != phArena);
    if (IMG_NULL == phArena)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    *(phArena) = IMG_NULL;

    IMG_ASSERT(gbInitialised);
    if (gbInitialised)
    {
        ui32Result = POOL_Alloc(gpsPoolArena,((IMG_HANDLE *)&psArena));
        IMG_ASSERT(IMG_NULL != psArena);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_NULL == psArena ||
            IMG_SUCCESS != ui32Result) 
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
        psArena->pszName = IMG_NULL;
        if (IMG_NULL != pszName)
        {
            psArena->pszName = IMG_STRDUP((IMG_CHAR *)pszName);
        }
        if (IMG_NULL != pfnImportAlloc)
        {
            psArena->pfnImportAlloc = pfnImportAlloc;
        }
        else
        {
            psArena->pfnImportAlloc = ra_RequestAllocFail;
        }
        psArena->pfnImportFree = pfnImportFree;
        psArena->hImport = hImport;

        for(ui32Idx = 0; ui32Idx < FREE_TABLE_LIMIT; ui32Idx++)
        {
            psArena->psBTHeadFree[ui32Idx] = IMG_NULL;
        }
        psArena->psBTHeadSegment = IMG_NULL;
        psArena->psBTTailSegment = IMG_NULL;
        psArena->quantum = quantum;

#ifdef VID_RA_STATS
        psArena->ui32SpanCount = 0;
        psArena->ui32LiveSegmentCount = 0;
        psArena->ui32FreeSegmentCount = 0;
        psArena->ui64FreeResourceCount = ui64Size;
        psArena->ui32TotalAllocs = 0;
        psArena->ui32TotalFrees = 0;
        psArena->ui32ImportCount = 0;
        psArena->ui32ExportCount = 0;
#endif

        ui32Result = VID_HASH_Create(MINIMUM_HASH_SIZE, &psArena->psHash);

        if (IMG_NULL == psArena->psHash)
        {
            VID_HASH_Delete(psArena->psHash);
            if (IMG_NULL != psArena->pszName)
            {
                IMG_FREE(psArena->pszName);
                psArena->pszName = IMG_NULL;
            }
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
        if (ui64Size >(IMG_UINT64)0)
        {

//Floats are not allowed in the kernel 
#if  !defined(IMG_KERNEL_MODULE)	
            ui64Size =(ui64Size + quantum - 1) / quantum * quantum;
#endif
            ui32Result = ra_InsertResource(psArena, ui64Base, ui64Size);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if (IMG_SUCCESS != ui32Result) 
            {
                VID_HASH_Delete(psArena->psHash);
                POOL_Free(gpsPoolArena, psArena);
                if (IMG_NULL != psArena->pszName)
                {
                    IMG_FREE(psArena->pszName);
                    psArena->pszName = IMG_NULL;
                }
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }
        }
        *(phArena) = psArena;
        ui32Result = IMG_SUCCESS;
    }
error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Delete

 @Description

 Used to delete a resource arena. All resources allocated from the arena must
 be freed before deleting the arena.

 @Input	    hArena      : The handle to the the arena to delete.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Delete(IMG_HANDLE const hArena)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;
    struct sArena * psArena = IMG_NULL;
    IMG_UINT32 ui32Idx;

    IMG_ASSERT(IMG_NULL != hArena);
    if (IMG_NULL == hArena)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    trace(("VID_RA_Delete: pszName=%s\n", psArena->pszName));

    IMG_ASSERT(gbInitialised);
    if (gbInitialised)
    {
        psArena =(struct sArena *)hArena;
        if (IMG_NULL != psArena->pszName)
        {
            IMG_FREE(psArena->pszName);
            psArena->pszName = IMG_NULL;
        }
        for(ui32Idx = 0; ui32Idx < FREE_TABLE_LIMIT; ui32Idx++)
        {
            psArena->psBTHeadFree[ui32Idx] = IMG_NULL;
        }

        while(IMG_NULL != psArena->psBTHeadSegment)
        {
            struct sBT * psBT = psArena->psBTHeadSegment;
            IMG_ASSERT(RA_BOUNDARY_TAG_TYPE_FREE == psBT->eBTType);
            ra_SegmentListRemove(psArena, psBT);
#ifdef RA_STATS
            psArena->ui32SpanCount--;
#endif
        }
        ui32Result = VID_HASH_Delete(psArena->psHash);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        ui32Result = POOL_Free(gpsPoolArena, psArena);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Add

 @Description

 Used to add a resource span to an arena. 
 The span must not overlapp with any span previously added to the arena.

 @Input	    ui64Base    : The ui64Base of the span.

 @Input	    ui64Size    : The size of the span.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Add(IMG_HANDLE const hArena, 
                  IMG_UINT64 ui64Base, 
                  IMG_UINT64 ui64Size
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;
    struct sArena * psArena = IMG_NULL;

    IMG_ASSERT(IMG_NULL != hArena);
    if (IMG_NULL == hArena)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(gbInitialised);
    if (gbInitialised)
    {
        psArena =(struct sArena *)hArena;

#if  !defined(IMG_KERNEL_MODULE)	//Floats are not allowed in the kernel 
        ui64Size =(ui64Size + psArena->quantum - 1) / psArena->quantum * psArena->quantum;
#endif	//#if  !defined(IMG_KERNEL_MODULE)	//Floats are not allowed in the kernel 

        ui32Result = ra_InsertResource(psArena, ui64Base, ui64Size);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            goto error;
        }
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Alloc

 @Description

 Used to allocate resource from an arena.

 @Input	    hArena              : The handle to the the arena to create the resource.

 @Input	    request_size        : The requested size of resource segment.

 @Input	    pui64ActualSize     : The actualSize of resource segment.

 @Input	    ppvRef              : The user reference associated with allocated resource span.

 @Input	    ui32AllocationFlags : AllocationFlags influencing allocation policy.

 @Input	    ui64Alignment       : The alignment constraint required for the allocated segment.

 @Output    ui64Base            : The base of the allocated resource.

 @Return    IMG_RESULT          : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Alloc(IMG_HANDLE const hArena, 
                    IMG_UINT64 request_size,
                    IMG_UINT64 * const pui64ActualSize,
                    IMG_VOID ** const ppvRef, 
                    IMG_UINT32 ui32AllocationFlags,
                    IMG_UINT64 ui64Alignment,
                    IMG_UINT64 * const ui64Base
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;
    struct sArena * psArena = IMG_NULL;
    IMG_UINT64 ui64Size = request_size;
    IMG_ASSERT(IMG_NULL != hArena);
    if (IMG_NULL == hArena)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(gbInitialised);
    if (gbInitialised)
    {
        psArena =(struct sArena *)hArena;

        //Floats are not allowed in the kernel 
#if  !defined(IMG_KERNEL_MODULE)	
        ui64Size =((ui64Size + psArena->quantum - 1)/psArena->quantum)*psArena->quantum;
#endif

        if (IMG_NULL != pui64ActualSize)
        {
           (*pui64ActualSize) = ui64Size;
        }

        trace(("VID_RA_Alloc  : pszName='%s'  ui64Size=0x%lx(0x%lx) ...\n", psArena->pszName, ui64Size, request_size));

        //if allocation failed then we might have an import source which
        //can provide more resource, else we will have to fail the allocation to the caller.
        if (RA_SEQUENTIAL_ALLOCATION == ui32AllocationFlags)
        {
           ui32Result = ra_AttemptAllocAligned(psArena, ui64Size, ppvRef, ui64Alignment, ui64Base);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if (IMG_SUCCESS != ui32Result)
            {
                //Error handling
            }
        }
        else if (RA_RANDOM_ALLOCATION == ui32AllocationFlags)
        {
#if !defined(IMG_KERNEL_MODULE)
            ui32Result = ra_AttemptRandomAllocAligned(psArena, ui64Size, ppvRef, ui64Alignment, ui64Base);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if (IMG_SUCCESS != ui32Result)
            {
                //Error handling
            }
#else
            IMG_ASSERT(IMG_FALSE);		//Not supported in kernel mode. 
            ui32Result = IMG_ERROR_FATAL;
            goto error;
#endif
        }

        if (IMG_SUCCESS != ui32Result)
        {
            IMG_VOID * pvImportRef = IMG_NULL;
            IMG_UINT64 ui64ImportBase =(IMG_UINT64)0;
            IMG_UINT64 ui64ImportRequestedSize = ui64Size;
            IMG_UINT64 ui64ImportActualSize =(IMG_UINT64)0;

            ui32Result = psArena->pfnImportAlloc(
                psArena->hImport, 
                ui64ImportRequestedSize, 
                &ui64ImportActualSize,
                &pvImportRef, 
                ui32AllocationFlags,
                &ui64ImportBase);

            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if (IMG_SUCCESS != ui32Result)
            {
                //Error handling
            }

            if (IMG_SUCCESS == ui32Result)
            {
                struct sBT * psBT = ra_InsertResourceSpan(psArena, ui64ImportBase, ui64ImportActualSize);
                
                //Successfully import more resource, create a span to represent it and retry the allocation attempt
                if (IMG_NULL == psBT)
                {
                    //insufficient resources to insert the newly acquired span, so free it back again
                    psArena->pfnImportFree(psArena->hImport, ui64ImportBase, pvImportRef);
                    trace(("  RA_Alloc: pszName='%s'  ui64Size=0x%x = IMG_NULL\n", psArena->pszName, ui64Size));
                    ra_Dump(psArena);
                    ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                    goto error;
                }
                psBT->pvRef = pvImportRef;
#ifdef RA_STATS
                psArena->ui32FreeSegmentCount++;
                psArena->ui64FreeResourceCount += ui64ImportActualSize;
                psArena->ui32ImportCount++;
                psArena->ui32SpanCount++;
#endif
                if (RA_SEQUENTIAL_ALLOCATION == ui32AllocationFlags)
                {
                    ui32Result = ra_AttemptAllocAligned(psArena, ui64Size, ppvRef, ui64Alignment, ui64Base);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        //Error handling
                    }
                }
                else if (RA_RANDOM_ALLOCATION == ui32AllocationFlags)
                {
#if !defined(IMG_KERNEL_MODULE)
                    ui32Result = ra_AttemptRandomAllocAligned(psArena, ui64Size, ppvRef, ui64Alignment, ui64Base);
                    IMG_ASSERT(IMG_SUCCESS == ui32Result);
                    if (IMG_SUCCESS != ui32Result)
                    {
                        //Error handling
                    }
#else
                    IMG_ASSERT(IMG_FALSE);		//Not supported in kernel mode. 
                    ui32Result = IMG_ERROR_FATAL;
                    goto error;
#endif
                }
            }
        }
#ifdef RA_STATS
        if (IMG_SUCCESS == ui32Result)
        {
            psArena->ui32TotalAllocs++;
        }
#endif    
        trace(("  RA_Alloc: pszName=%s ui64Size=0x%lx = 0x%lx\n", psArena->pszName, ui64Size, ui64Base));

        ra_Dump(psArena);
        ra_Stats(psArena);
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_RA_Free

 @Description

 Used to free a resource segment.

 @Input	    hArena      : The arena the segment was originally allocated from.

 @Input	    ui64Base    : The ui64Base of the span.

 @Output    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

*****************************************************************************/
IMG_RESULT VID_RA_Free(IMG_HANDLE const hArena, 
                   IMG_UINT64 ui64Base
)
{
    IMG_RESULT ui32Result = IMG_ERROR_FATAL;
    struct sArena * psArena = IMG_NULL;
    struct sBT * psBT = IMG_NULL;
    IMG_UINTPTR uipResult;

    IMG_ASSERT(IMG_NULL != hArena);
    if (IMG_NULL == hArena)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if (gbInitialised)
    {
        psArena =(struct sArena *)hArena;

        ui32Result = VID_HASH_Remove(psArena->psHash, ui64Base, &uipResult);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            goto error;
        }
        psBT =(struct sBT *)uipResult;

        IMG_ASSERT(psBT->ui64Base == ui64Base);

#ifdef RA_STATS
        psArena->ui32TotalFrees++;
#endif

        ra_FreeBT(psArena, psBT);

        trace(("RA_Free: pszName=%s ui64Base=0x%lx\n", psArena->pszName, ui64Base));
        ra_Dump(psArena);
    }

error:
    return ui32Result;
}

#ifdef RA_DUMP

static const IMG_CHAR * apszBTTypeString[RA_BOUNDARY_TAG_TYPE_MAX+1] =
{
    "span",     //span markers 
    "free",     //free resource segment 
    "live",     //allocated resource segment 
    "junk"
};

/*****************************************************************************

 @Function				ra_Dump

 @Description

 Used to dump a readable description of an arena. Diagnostic only.

 @Input	    psArena : The arena to dump information from.

 @Output    None

 @Return    None

*****************************************************************************/
IMG_VOID ra_Dump(struct sArena * psArena)
{
    struct sBT * psBT = IMG_NULL;
    IMG_ASSERT(IMG_NULL != psArena);
    if (IMG_NULL != psArena)
    {
        fprintf(stderr, "Arena %s\n", psArena->pszName);
        fprintf(stderr, "  alloc=%p free=%p handle=%p quantum=%d\n", 
            psArena->pfnImportAlloc, 
            psArena->pfnImportFree, 
            psArena->hImport,
            psArena->quantum);
        fprintf(stderr, "  segment Chain:\n");
        if (IMG_NULL != psArena->psBTHeadSegment && 
            IMG_NULL != psArena->psBTHeadSegment->psBTPrevSegment)
        {
            fprintf(stderr, "  error: head boundary tag has invalid psBTPrevSegment\n");
        }
        if (psArena->psBTTailSegment!=IMG_NULL && psArena->psBTTailSegment->psBTNextSegment!=IMG_NULL)
        {
            fprintf(stderr, "  error: tail boundary tag has invalid psBTNextSegment\n");
        }

        for(psBT = psArena->psBTHeadSegment; IMG_NULL != psBT; psBT = psBT->psBTNextSegment)
        {
            fprintf(stderr, "\tbase=0x%08x %08x ui64Size=0x%08x %08x type=%s  hRef=%p\n", 
               (IMG_UINT32)((psBT->ui64Base >> 32) & 0xFFFFFFFF), 
               (IMG_UINT32)((psBT->ui64Base) & 0xFFFFFFFF), 
               (IMG_UINT32)((psBT->ui64Size >> 32) & 0xFFFFFFFF), 
               (IMG_UINT32)((psBT->ui64Size) & 0xFFFFFFFF), 
               (psBT->eBTType < RA_BOUNDARY_TAG_TYPE_MAX) ? apszBTTypeString[psBT->eBTType] : apszBTTypeString[RA_BOUNDARY_TAG_TYPE_MAX],
                psBT->pvRef);
        }
    }
#ifdef HASH_TRACE
    VID_HASH_Dump(psArena->psHash);
#endif
}
#endif

#ifdef RA_STATS
/*!
******************************************************************************

 @Function				ra_Stats

 @Description

 Used to dump the statistics associated with an arena.

 @Input	    psArena : The arena to dump statistics from.

 @Output    None

 @Return    None

*****************************************************************************/
IMG_VOID ra_Stats(struct sArena * psArena)
{
    IMG_ASSERT(IMG_NULL != psArena);
    if (IMG_NULL != psArena)
    {
        fprintf(stderr, "Arena %s\n", psArena->pszName);
        fprintf(stderr, "\tspan count = %d\n", psArena->ui32SpanCount);
        fprintf(stderr, "\tlive segment count = %d\n", psArena->ui32LiveSegmentCount);
        fprintf(stderr, "\tfree segment count = %d\n", psArena->ui32FreeSegmentCount);
        fprintf(stderr, "\tfree resource count = 0x%08x %08x\n",(IMG_UINT32)((psArena->ui64FreeResourceCount >> 32) & 0xFFFFFFFF),(IMG_UINT32)(psArena->ui64FreeResourceCount & 0xFFFFFFFF));
        fprintf(stderr, "\ttotal allocs = %d\n", psArena->ui32TotalAllocs);
        fprintf(stderr, "\ttotal frees = %d\n", psArena->ui32TotalFrees);
        fprintf(stderr, "\timport count = %d\n", psArena->ui32ImportCount);
        fprintf(stderr, "\texport count = %d\n", psArena->ui32ExportCount);
        fprintf(stderr, "\n");
    }
}
#endif
