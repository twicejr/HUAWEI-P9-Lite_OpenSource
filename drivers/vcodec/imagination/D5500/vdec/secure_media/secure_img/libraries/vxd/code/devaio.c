/*!
 *****************************************************************************
 *
 * @File       devaio.c
 * @Title      Low-level MTX interface with DEVA PVDEC firmware
 * @Description    This file contains functions to communicate with MTX DEVA PVDEC firmware.
 *  This includes sending and receiving messages and state indicators.
 *  It is a subcomponent of the Decoder block and operates on the Decoder
 *  block state.
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

#include "img_errors.h"
#include "img_types.h"
#ifndef SYSBRG_BRIDGING
#include "gzip_fileio.h"
#endif

#include "vxd_io.h"
#include "devaio.h"
#include "report_api.h"
#include "sysos_api_km.h"
#if defined(FW_PERFORMANCE_LOGGING)
#include "xpl_pvdec.h"
#include "perflog_api.h"
#endif

#include "interface/deva_fw_msg.h"

#include "hwdefs/pvdec_core_regs.h"


#ifdef PVDEC_DEBUG_FACILITY
#include "tal.h"
#include "hwdefs/msvdx_mtx_regs.h"
#endif /* PVDEC_DEBUG_FACILITY */

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)

#if defined(FW_PERFORMANCE_LOGGING)
/* Task state definition used for xpl output */
IMG_UINT32 a32TaskStateToRange[5][10] =
{
    /*         Idle ,  setup ,      decode ,     deblock,    blt ,       limbo ,      error,   load ,          parse ,      stall */
    /* EP */ { ~0,     EP_SETUP,    EP_DECODE,   ~0,         ~0,         ~0,          ~0,      MODULE_LOAD,    HDR_PARSE    ,~0      },
    /* FE */ { ~0,     SETUP,       FE,          ~0,         ~0,         ~0,          ~0,      MODULE_LOAD,    ~0           ,~0      },
    /* BE */ { ~0,     BE_SETUP,    BE,          DEBLOCK,    DEBLOCK,    BE_LIMBO,    ~0,      MODULE_LOAD,    ~0           ,BE_SYNC },
    /* PSR */{ ~0,     ~0,          ~0,          ~0,         ~0,         ~0,          ~0,      MODULE_LOAD,    HDR_PARSE    ,~0      },
    /* ? */  { ~0,     ~0,          ~0,          ~0,          ~0,        ~0,          ~0,      MODULE_LOAD,    HDR_PARSE    ,~0      },
};
#endif

#ifndef VXD_BRIDGING
/* Set to IMG_TRUE in the Debug FIFO log file is already created.
 * This allows for logging all the firmware debug data through all the resets that can occur. */
static IMG_BOOL bDebugFifoFileOpened = IMG_FALSE;
#else
/*!
******************************************************************************

 @Function              devaio_fnDebugFifo

******************************************************************************/
static IMG_BOOL devaio_fnDebugFifo(
    IMG_VOID *  pvParam
)
{
    DEVAIO_sContext  * psContex = (DEVAIO_sContext *)pvParam;

    /* Wake up the suspended process...*/
    DEVAIO_HandleDebugFifo(psContex);

    /* Indicate that we want to be rescheduled...*/
    return IMG_TRUE;
}
#endif /* not VXD_BRIDGING */

/*!
******************************************************************************

 @Function              devaio_InitDebugFifo

******************************************************************************/
static IMG_RESULT devaio_InitDebugFifo(
    DEVAIO_sContext  * psContext
)
{
#ifdef VXD_BRIDGING
    IMG_HANDLE        hAuxTimer = IMG_NULL;
#else /* ndef VXD_BRIDGING */
    const IMG_CHAR  * pui8FileName = "mtx_debug_0.txt";
    IMG_HANDLE        hAuxFile;
#endif /* ndef VXD_BRIDGING */
    IMG_INT8 *        paui8AuxOutText = IMG_NULL;
    IMG_UINT32        ui32Result;

    /* Store some already initialised values. */
#ifdef VXD_BRIDGING
    if (IMG_NULL != psContext->sDebugFifo.hTimer)
    {
        hAuxTimer = psContext->sDebugFifo.hTimer;
    }
#else /* ndef VXD_BRIDGING */
    if (IMG_TRUE == bDebugFifoFileOpened)
    {
        hAuxFile = psContext->sDebugFifo.hFile;
    }
#endif /* ndef VXD_BRIDGING */
    if (IMG_NULL != psContext->sDebugFifo.paui8OutText)
    {
        paui8AuxOutText = psContext->sDebugFifo.paui8OutText;
    }

    /* Reset debug FIFO structure. */
    IMG_MEMSET(&psContext->sDebugFifo, 0, sizeof(psContext->sDebugFifo));

#if defined(FW_PERFORMANCE_LOGGING)
    /* Setup tasks table */
    IMG_MEMSET(&psContext->sXpl.sTaskPipeStates, ~0, sizeof(psContext->sXpl.sTaskPipeStates));

    /* Mark xpl file associated flag to put xpl header for the very first time */
    psContext->sXpl.bFirstXplWrite = IMG_TRUE;
#endif

    /* Restore some already initialised values. */
#ifdef VXD_BRIDGING
    if (IMG_NULL != hAuxTimer)
    {
        psContext->sDebugFifo.hTimer = hAuxTimer;
    }
#else /* ndef VXD_BRIDGING */
    if (IMG_TRUE == bDebugFifoFileOpened)
    {
        psContext->sDebugFifo.hFile = hAuxFile;
    }
#endif /* ndef VXD_BRIDGING */
    if (IMG_NULL != paui8AuxOutText)
    {
        psContext->sDebugFifo.paui8OutText = paui8AuxOutText;
    }

    /* Allocate output text buffer. */
    if (IMG_NULL == psContext->sDebugFifo.paui8OutText)
    {
        psContext->sDebugFifo.paui8OutText = IMG_MALLOC(DEVAIO_DEBUG_TEXT_SIZE);
        if (IMG_NULL == psContext->sDebugFifo.paui8OutText)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
                   "Failed to allocate buffer for debug output");
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

#ifdef VXD_BRIDGING
    /* Create the debug FIFO handling timer. */
    if (IMG_NULL == psContext->sDebugFifo.hTimer)
    {
        ui32Result = SYSOSKM_CreateTimer(devaio_fnDebugFifo, (IMG_VOID *)psContext, 100, &psContext->sDebugFifo.hTimer);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
                   "Failed to create debug FIFO timer");
            goto error;
        }
    }
#else /* ndef VXD_BRIDGING */
    if (IMG_FALSE == bDebugFifoFileOpened)
    {
        ui32Result = IMG_FILEIO_OpenFile(pui8FileName, "w", &psContext->sDebugFifo.hFile, IMG_FALSE);
        if (ui32Result != IMG_SUCCESS)
        {
            psContext->sDebugFifo.hFile = IMG_NULL;
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
                   "Failed to open file for saving FIFO debug output (%s)", pui8FileName);
            goto error;
        }
        bDebugFifoFileOpened = IMG_TRUE;
    }
#endif /* ndef VXD_BRIDGING */
    /* Get fifo size */
    {
        IMG_UINT32 ui32FifoCtrl;
        IMG_UINT8  ui8Pipe = 0;
        ui32FifoCtrl = VXDIO_ReadRegister(psContext->hPvdecIoCtx,
                                          REGION_PVDEC_CORE_REGSPACE,
                                          PVDEC_CORE_CR_PROC_DEBUG_FIFO_CTRL_0_OFFSET,
                                          ui8Pipe);
        psContext->sDebugFifo.ui32FifoSize = REGIO_READ_FIELD(ui32FifoCtrl,
            PVDEC_CORE, CR_PROC_DEBUG_FIFO_CTRL_0, CR_PROC_DEBUG_FIFO_SIZE);
    }

    DEVAIO_EnableDebugFifo(psContext);

    return IMG_SUCCESS;

error:
    IMG_FREE(psContext->sDebugFifo.paui8OutText);
    psContext->sDebugFifo.paui8OutText = IMG_NULL;

    return ui32Result;
}


#define DEBUG_DATA_TYPE_STRING  1
#define DEBUG_DATA_TYPE_PARAMS  2


/*!
******************************************************************************

 @Function              devaio_DumpDebugFifo

******************************************************************************/
static IMG_VOID devaio_DumpDebugFifo(
    DEVAIO_DebugFifo  * psFifo
)
{
#if 0
    TASK* pTask = findTask( psFifo->ui32Sp );
#endif

    if(IMG_NULL != psFifo->paui8OutText)
    {
        /* format the text string */
        sprintf((IMG_CHAR *)psFifo->paui8OutText, (IMG_CHAR *)psFifo->aui8Text,
                psFifo->aui32Params[0],
                psFifo->aui32Params[1],
                psFifo->aui32Params[2],
                psFifo->aui32Params[3],
                psFifo->aui32Params[4],
                psFifo->aui32Params[5],
                psFifo->aui32Params[6],
                psFifo->aui32Params[7],
                psFifo->aui32Params[8],
                psFifo->aui32Params[9],
                psFifo->aui32Params[10]);

        REPORT(REPORT_MODULE_FW, REPORT_INFO, "FW: %s", psFifo->paui8OutText);
    }

#if 0
    switch( text[0] )
    {
        case '*': /* new task */
        {
#if 0
            static int col = 0;
            pTask = new TASK;
            pTask->name        = text.substr(1);
            pTask->sp        = sp;
            pTask->indent    = 0;
            pTask->col        = col++;
            TaskList[ sp ]    = pTask;
            //::SetConsoleTextAttribute( hStdHandle , CONSOLE_BLUE );
#endif
            break;
        }

        case '+':
        {
            break;
        }

        case '-':
        {
#if 0
            if( pTask &&  pTask->indent ) pTask->indent--;
#endif
            break;
        }
        case '@': /* Green */
        {
            //::SetConsoleTextAttribute( hStdHandle , CONSOLE_GREEN );
            break;
        }
        case '#': /* Blue */
        {
            //::SetConsoleTextAttribute( hStdHandle , CONSOLE_BLUE );
            break;
        }

        case '^': /* Elevated priority warning msg */
        {
            //::SetConsoleTextAttribute( hStdHandle , CONSOLE_YELLOW );
            break;
        }

        case '!': /* warning/Error message */
        {
            //::SetConsoleTextAttribute( hStdHandle , CONSOLE_RED );
            break;
        }

    }

    printf( "\r%70s\r", "" );
    printf( "FW_LOG " );

#if 0
    if( pTask )
    {
        printf("%i % 4s: ", pTask->col, pTask->name.c_str() );
    }
#endif
    printf( "%s\n", text);

    switch( text[0] )
    {
        case '+':
        {
#if 0
            if( pTask ) pTask->indent++;
#endif
            break;
        }
    }
#endif

    IMG_MEMSET(psFifo->aui8Text, 0, DEVAIO_DEBUG_TEXT_SIZE);
    psFifo->ui32DebugTextIdx = 0;
}

/*!
******************************************************************************

 @Function              devaio_ProcessDbgFifoData

******************************************************************************/
static IMG_VOID devaio_ProcessDbgFifoData(
    DEVAIO_DebugFifo  * psFifo,
    IMG_UINT32          ui32DataType,
    IMG_UINT32        * pui32Data,
    IMG_UINT32          ui32DataSize
)
{
    switch(ui32DataType)
    {
        case DEBUG_DATA_TYPE_STRING:
        {
            IMG_INT8    i8c;
            IMG_UINT32  ui32i = 0;
            IMG_UINT8   ui8n = 0;
            IMG_UINT32  ui32ParamsCount = 0;

            /* Extract String*/
            do
            {
                if(ui8n > 3)
                {
                    ui8n=0;
                    ui32i++;
                }
                i8c = (pui32Data[ui32i] >> (ui8n++*8)) & 0xFF;
                psFifo->aui8Text[psFifo->ui32DebugTextIdx] = i8c;
                psFifo->ui32DebugTextIdx++;
                IMG_ASSERT(psFifo->ui32DebugTextIdx < DEVAIO_DEBUG_TEXT_SIZE);

                if(i8c == '%')
                {
                    ui32ParamsCount++;
                }

            } while(i8c != 0 && ui32i < ui32DataSize);

            ui32i++;
            ui8n = 0;
            while(ui32ParamsCount != 0 && ui32i < ui32DataSize)
            {
                psFifo->aui32Params[ui8n++] = psFifo->aui32DebugData[ui32i++];
                ui32ParamsCount--;
            }

            if(ui32i < ui32DataSize)
            {
                psFifo->ui32Sp = psFifo->aui32DebugData[ui32i];
            }
            else
            {
                psFifo->ui32Sp = 0;
            }

            devaio_DumpDebugFifo(psFifo);
            break;
        }
        default:
        {
            IMG_ASSERT(0=="Unknown data type");
        }
    }
}

#if defined(FW_PERFORMANCE_LOGGING)
static IMG_VOID devaio_SaveXplData(
    DEVAIO_Xpl  * psXpl,
    IMG_UINT8     ui8Pipe,
    IMG_UINT16    ui16GroupID,
    IMG_UINT8     ui8TagType,
    IMG_UINT16    ui16TagSubject,
    IMG_UINT32    ui32Data
)
{
    IMG_UINT64 ui64PerfDataElement = 0;

    if(psXpl->bFirstXplWrite)
    {
        ui64PerfDataElement |= (IMG_UINT64)(DATA_ITEM) << 44;
        ui64PerfDataElement |= (IMG_UINT64)(XPL_VERSION) << 32;
        ui64PerfDataElement |= 2; // bits 31-0: Data
        PERFLOG_WritePerfMsg(ui64PerfDataElement);

        psXpl->bFirstXplWrite = IMG_FALSE;
    }

    IMG_ASSERT(ui8TagType <= 0xf);
    IMG_ASSERT(ui16TagSubject <= 0xfff);

    ui64PerfDataElement = ((IMG_UINT64)ui8Pipe << 60); // bits 63-56: Context ID
    ui64PerfDataElement |= ((IMG_UINT64)(ui16GroupID & 0xfff) << 48); // bits 55-48: Message ID
    ui64PerfDataElement |= ((IMG_UINT64)(ui8TagType & 0xf) << 44); // bits 47-44: Tag Type
    ui64PerfDataElement |= ((IMG_UINT64)(ui16TagSubject & 0xfff) << 32); // bits 43-32: Tag Subject
    ui64PerfDataElement |= ui32Data; // bits 31-0: Data
    PERFLOG_WritePerfMsg(ui64PerfDataElement);
}

static IMG_UINT32 devaio_MapToXplRange(
    IMG_UINT8 ui8Task,
    IMG_UINT8 ui8Idx
)
{
    return a32TaskStateToRange[ui8Task][ui8Idx];
}

static IMG_VOID devaio_perfInfo(
    DEVAIO_Xpl * psXpl,
    IMG_UINT32 * pui32PerfData
)
{
    IMG_UINT16 ui16MsgId = (pui32PerfData[0])&0xffff;
    IMG_UINT8 ui8Pipe = (pui32PerfData[0]>>16)&0xf;
    IMG_UINT8 ui8Type = (pui32PerfData[0]>>24)&0xf;
    IMG_UINT8 ui8Idx = (pui32PerfData[0]>>20)&0xf;
    IMG_UINT32 ui32Data = pui32PerfData[1];
    IMG_UINT32 ui32Tick = (pui32PerfData[0]&0x10000000) ? pui32PerfData[2] : pui32PerfData[1];

    IMG_UINT8 ui8Task;
    DEVAIO_XplTaskState * psTask;
    IMG_UINT8 ui8NewState;
    IMG_UINT32 ui32NewRange;

    REPORT(REPORT_MODULE_VXDIO, REPORT_INFO, "Writing perfInfo: msgid=%d pipe=%d type=%d idx=%d data=0x%x tick=%d",
                    ui16MsgId, ui8Pipe, ui8Type, ui8Idx, ui32Data, ui32Tick);

    switch(ui8Type)
    {
        case 1: /* Enter Range */
        {
            devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, SPAN_BEGIN, devaio_MapToXplRange(4, ui8Idx), ui32Tick);
            break;
        }

        case 2: /* exit Range */
        {
            devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, SPAN_END, devaio_MapToXplRange(4, ui8Idx), ui32Tick);
            break;
        }

        case 5: /* ep state */
        case 6: /* fe state */
        case 7: /* be state */
        case 8: /* psr state */
            {
                ui8Task = (ui8Type-5); /* ep:0 fe:1 be:2 psr:3*/
                psTask = &psXpl->sTaskPipeStates[ui8Task][ui8Pipe];
                ui8NewState = ui8Idx;

                /* End the old range */
                if(psTask->ui32XplRange != ~0)
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, psTask->ui16MsgId, RANGE_END, psTask->ui32XplRange, ui32Tick);
                }
                /* map range */
                ui32NewRange = devaio_MapToXplRange(ui8Task, ui8NewState);

                if(ui32NewRange != ~0)
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, RANGE_BEGIN, ui32NewRange, ui32Tick);
                }

                psTask->ui8State     = ui8NewState;
                psTask->ui16MsgId    = ui16MsgId;
                psTask->ui32XplRange = ui32NewRange;

                break;
            }

        case 4: /* Timing point */
            if (ui8Idx == 1) /* Idle Blip */
            {
                devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, TIMING_POINT, IDLEBLIP, ui32Tick);
            }
            break;

        case 3: /* data item */
        default:
            if(ui8Idx == 1)
            {
                devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, DATA_ITEM, SLICE_FLAGS, ui32Data);
            }
            else if(ui8Idx == 6)
            {
                if(ui32Data&(1<<0))
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, 0, TIMING_POINT, FE_EOS, ui32Tick); // MSVDX_VEC_END_OF_SLICE
                }
                if(ui32Data&(1<<18))
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, 0, TIMING_POINT, PP_EOS, ui32Tick); // VDEB_SLICE_DONE_IRQ
                }
                if(ui32Data&(1<<17))
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, 0, TIMING_POINT, PP_EOP, ui32Tick); // VDEB_PICTURE_DONE_IRQ
                }
            }
            else if(ui8Idx == 7)
            {
                if(ui32Data&(1<<0))
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, 0, TIMING_POINT, EP_EOS, ui32Tick); // ENTROPY_END_OF_SLICE
                }
                if(ui32Data&(1<<6))
                {
                    devaio_SaveXplData(psXpl, ui8Pipe, 0, TIMING_POINT, EP_ROW, ui32Tick); // ENTROPY_FRAGMENT_ROW_COMPLETE
                }
            }
            else if(ui8Idx == 0xb)
            {
                devaio_SaveXplData(psXpl, ui8Pipe, ui16MsgId, DATA_ITEM, SYNC_CMD, ui32Data);
            }
            else
            {
                /* not used */
            }
            break;
    }
}
#endif

/*!
******************************************************************************

 @Function              DEVAIO_HandleDebugFifo

******************************************************************************/
IMG_VOID DEVAIO_HandleDebugFifo(
    DEVAIO_sContext  * psContext
)
{
    DEVAIO_DebugFifo  * psFifo = &psContext->sDebugFifo;
#if defined(FW_PERFORMANCE_LOGGING)
    DEVAIO_Xpl  * psXpl = &psContext->sXpl;
#endif

    IMG_UINT32  ui32FifoCtrl;
    IMG_UINT32  ui32Idx = 0;
    IMG_UINT8   ui8Pipe = 0;

    if(IMG_TRUE != psFifo->bReady)
    {
        return;
    }

    DEVAIO_DisableDebugFifo(psContext);

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " + Processing debug fifo");
#endif

    do
    {
        IMG_UINT32 ui32Words, ui32FifoCount;
        ui32FifoCtrl = VXDIO_ReadRegister(psContext->hPvdecIoCtx,
                                          REGION_PVDEC_CORE_REGSPACE,
                                          PVDEC_CORE_CR_PROC_DEBUG_FIFO_CTRL_0_OFFSET,
                                          ui8Pipe);
        ui32FifoCount = REGIO_READ_FIELD(ui32FifoCtrl,
            PVDEC_CORE, CR_PROC_DEBUG_FIFO_CTRL_0, CR_PROC_DEBUG_FIFO_COUNT);

        if(ui32FifoCount == 0)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_WARNING, "Debug fifo overflow.");
        }

        ui32Words = psFifo->ui32FifoSize - ui32FifoCount;
        if(ui32Words == 0)
        {
            break;
        }

        while(ui32Words--)
        {
            IMG_UINT32 ui32Val = VXDIO_ReadRegister(psContext->hPvdecIoCtx,
                                                    REGION_PVDEC_CORE_REGSPACE,
                                                    PVDEC_CORE_CR_PROC_DEBUG_FIFO_OFFSET,
                                                    ui8Pipe);

#ifndef VXD_BRIDGING
            if (psFifo->hFile != IMG_NULL)
            {
                IMG_FILEIO_Printf(psFifo->hFile, "MTX write to memory mapped register 04800508 = %08X\n", ui32Val);
            }
#endif /* not VXD_BRIDGING */

            if (psFifo->ui32Collecting == 0 && psFifo->ui32Count == 0 &&
                (ui32Val & 0xf0000000) == 0x60000000 ) /* Expect single word */
            {
                ui32Idx = 0;
                psFifo->ui32Count = 1;
                psFifo->ui32Collecting = 0;
                psFifo->aui32Data[ui32Idx++] = ui32Val;
            }
            else if (psFifo->ui32Collecting == 0 && psFifo->ui32Count == 0 &&
                (ui32Val & 0xf0000000) == 0x70000000 ) /* expect 2 words */
            {
                ui32Idx = 0;
                psFifo->ui32Count = 2;
                psFifo->ui32Collecting = 0;
                psFifo->aui32Data[ui32Idx++] = ui32Val;
            }
            else if (psFifo->ui32Collecting == 0 && psFifo->ui32Count)
            {
                psFifo->aui32Data[ui32Idx++] = ui32Val;
                psFifo->ui32Count--;
                if(psFifo->ui32Count == 0)
                {
#if defined(FW_PERFORMANCE_LOGGING)
                    /* push performance data into xpl file */
                    devaio_perfInfo(psXpl, psFifo->aui32Data);
#endif
                }
            }
            else
            {
                switch(psFifo->ui32Collecting)
                {
                    case 0: /* header*/
                    {
                        psFifo->ui32DataType = ui32Val >> 24;
                        psFifo->ui32DataSize = 0;
                        psFifo->ui32DataIndex = 0;
                        psFifo->ui32Collecting = psFifo->ui32DataType;
                        break;
                    }
                    case DEBUG_DATA_TYPE_STRING: /* string*/
                    {
                        IMG_UINT32  ui32I;
                        psFifo->aui32DebugData[psFifo->ui32DataIndex++] = ui32Val;
                        for(ui32I=0; ui32I<(sizeof(ui32Val)); ui32I++)
                        {
                            if((ui32Val&0xFF) == '%')
                            {
                                psFifo->ui32DataSize++;
                            }
                            else if((ui32Val&0xFF) == 0)
                            {
                                psFifo->ui32Collecting = DEBUG_DATA_TYPE_PARAMS;
                                break;
                            }
                            ui32Val = ui32Val>>8;
                        }
                        psFifo->ui32DataSize++;
                        IMG_ASSERT((psFifo->ui32DataSize+1)*4 < sizeof(psFifo->aui32DebugData));
                        break;
                    }
                    case DEBUG_DATA_TYPE_PARAMS:
                    {
                        if(psFifo->ui32DataIndex < psFifo->ui32DataSize)
                        {
                            /*Collecting params*/
                            psFifo->aui32DebugData[psFifo->ui32DataIndex++] = ui32Val;
                        }
                        else
                        {
                            /*Collect the stack pointer/ task pointer*/
                            psFifo->aui32DebugData[psFifo->ui32DataIndex] = ui32Val;
                            psFifo->ui32DataSize++;
                            psFifo->ui32Collecting = 0;
                            devaio_ProcessDbgFifoData(psFifo,
                                                      psFifo->ui32DataType,
                                                      (IMG_UINT32 *)psFifo->aui32DebugData,
                                                      psFifo->ui32DataSize);
                        }
                        break;
                    }
                }
            }
        }
    }
    while(1);

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " + Processing debug fifo done");
#endif
    DEVAIO_EnableDebugFifo(psContext);
}

/*!
******************************************************************************

 @Function              DEVAIO_CloseDebugFifo

******************************************************************************/
IMG_RESULT DEVAIO_CloseDebugFifo(
    DEVAIO_sContext  * psContext
)
{
#if !defined(VXD_BRIDGING)
    if (psContext->sDebugFifo.hFile != IMG_NULL)
    {
        IMG_FILEIO_CloseFile(psContext->sDebugFifo.hFile);
    }
#else /* def VXD_BRIDGING */
    if(IMG_NULL != psContext->sDebugFifo.hTimer)
    {
        /* Destroy the debug FIFO handling timer. */
        SYSOSKM_DestroyTimer(psContext->sDebugFifo.hTimer);
        psContext->sDebugFifo.hTimer = IMG_NULL;
    }
#endif /* def VXD_BRIDGING */

    if(IMG_NULL != psContext->sDebugFifo.paui8OutText)
    {
        IMG_FREE(psContext->sDebugFifo.paui8OutText);
        psContext->sDebugFifo.paui8OutText = IMG_NULL;
    }

    DEVAIO_DisableDebugFifo(psContext);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              DEVAIO_DisableDebugFifo

******************************************************************************/
IMG_VOID DEVAIO_DisableDebugFifo(
    DEVAIO_sContext * psContext
)
{
    DEVAIO_DebugFifo  * psFifo = &psContext->sDebugFifo;
    psFifo->bReady = IMG_FALSE;
}

/*!
******************************************************************************

 @Function              DEVAIO_EnableDebugFifo

******************************************************************************/
IMG_VOID DEVAIO_EnableDebugFifo(
    DEVAIO_sContext * psContext
)
{
    DEVAIO_DebugFifo * psFifo = &psContext->sDebugFifo;
    psFifo->bReady = IMG_TRUE;
}

/*!
******************************************************************************

 @Function              DEVAIO_GetDebugFifoSize

******************************************************************************/
IMG_UINT32 DEVAIO_GetDebugFifoSize(
    DEVAIO_sContext  * psContext
)
{
    DEVAIO_DebugFifo * psFifo = &psContext->sDebugFifo;
    return psFifo->ui32FifoSize;
}

#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

/*!
******************************************************************************

 @Function              devaio_fnTimer

******************************************************************************/
static IMG_BOOL devaio_fnTimer(
    IMG_VOID *  pvParam
)
{
    IMG_HANDLE  hEventHandle = (IMG_HANDLE)pvParam;

    /* Wake up the suspended process...*/
    SYSOSKM_SignalEventObject(hEventHandle);

    /* Indicate that we want to be rescheduled...*/
    return IMG_TRUE;
}


#ifdef PVDEC_DEBUG_FACILITY
/*
******************************************************************************

 @Function              devaio_dumpRegisters

 @Description

 This function dumps some of register spaces, MTX registers and MTX RAM.
 Can be used for debuging purposes, to diagnose FW/HW bring-up issues.

******************************************************************************/
static IMG_RESULT devaio_dumpRegisters(
        DEVAIO_sContext  * psContext
)
{
    #define DEVAIO_MAX_REGSPACE_WRDS 0x1000
    #define DEVAIO_MTX_CORE_MEMORY  0x18

    #define DEVAIO_PRINT_MTX_REG(_NAME_) \
        do { \
            IMG_UINT32 ui32Value; \
            VXDIO_WriteRegister(psContext->hPvdecIoCtx, REGION_PVDEC_MTX_CORE_REGSPACE, \
                    MTX_CORE_CR_MTX_REGISTER_READ_WRITE_REQUEST_OFFSET, ui32RegVal, \
                    0xffffffff, 0); \
            ui32Value = VXDIO_ReadRegister(psContext->hPvdecIoCtx, REGION_PVDEC_MTX_CORE_REGSPACE, \
                    MTX_CORE_CR_MTX_REGISTER_READ_WRITE_DATA_OFFSET, 0); \
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, _NAME_ ": 0x%08x", ui32Value); \
        } while (0);

    typedef struct _DEVAIO_regspace {
        const IMG_UINT8 * pui8Name;
        MEM_REGIONS_PVDEC eMemReg;
        IMG_UINT32 ui32Size;
    } DEVAIO_regspace;

    DEVAIO_regspace asRegSpaces[] = {
        { (IMG_UINT8 *)"CORE", REGION_PVDEC_CORE_REGSPACE, 0x3ff },
        { (IMG_UINT8 *)"BUS4_MMU", REGION_IMG_VIDEO_BUS4_MMU_REGSPACE, 0x1ff },
        { (IMG_UINT8 *)"VLR", REGION_PVDEC_VLR_REGSPACE, 0xfff },
        { (IMG_UINT8 *)"PIXEL PIPE", REGION_PVDEC_PIXEL_PIPE_REGSPACE, 0x1ff },
        { (IMG_UINT8 *)"PIXEL DMA", REGION_PVDEC_PIXEL_DMA_REGSPACE, 0x1ff },
        /* CSIM aborts when register 0x34c is read without active DMA. */
        { (IMG_UINT8 *)"MTX CORE", REGION_PVDEC_MTX_CORE_REGSPACE, 0x3ff /* 0x34c */ }
    };

    IMG_UINT32 ui32i, ui32RegVal, ui32RamId;
    IMG_RESULT ui32Result = IMG_SUCCESS;
    IMG_HANDLE * pahMemSpaces = IMG_NULL;
    IMG_UINT32 ui32MTXBankSize, ui32RamInfo;
    IMG_UINT32 ui32NumWrdsToDump = 0x8000, ui32DumpOffsetWrds = 0x0;

    IMG_UINT32 * pui32Buf = IMG_MALLOC(DEVAIO_MAX_REGSPACE_WRDS*sizeof(IMG_UINT32));

    if (pui32Buf == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to allocate buffer for registers dump!");
        return IMG_ERROR_MALLOC_FAILED;
    }

    ui32Result = VXDIO_GetMemSpacesHandles(0, &pahMemSpaces);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to get register spaces handles!");
        IMG_FREE(pui32Buf);
        return IMG_SUCCESS;
    }

    for (ui32i = 0; ui32i < sizeof(asRegSpaces)/sizeof(DEVAIO_regspace); ui32i++)
    {
        IMG_UINT32 ui32Word, ui32Offset, ui32SizeWrds = asRegSpaces[ui32i].ui32Size/sizeof(IMG_UINT32);
        IMG_UINT64 ui64RegspaceOffset;

        ui32Result = TAL_GetMemSpaceOffset(pahMemSpaces[asRegSpaces[ui32i].eMemReg],
                                           &ui64RegspaceOffset);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to get offset of %d memspace.",
                   asRegSpaces[ui32i].eMemReg);
            goto finish;
        }
        ui32Offset = IMG_UINT64_TO_UINT32(ui64RegspaceOffset);

        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Dumping register space %s (id %d), offset: %08x, size 0x%08x",
               asRegSpaces[ui32i].pui8Name, asRegSpaces[ui32i].eMemReg, ui32Offset, asRegSpaces[ui32i].ui32Size);

        if (ui32SizeWrds > DEVAIO_MAX_REGSPACE_WRDS)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Size of register space is larger than"
                   " supplied buffer (%u > %u), clipping!", ui32SizeWrds, DEVAIO_MAX_REGSPACE_WRDS);
            ui32SizeWrds = DEVAIO_MAX_REGSPACE_WRDS;
        }

        IMG_MEMSET(pui32Buf, 0, DEVAIO_MAX_REGSPACE_WRDS*sizeof(IMG_UINT32));
        ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                        asRegSpaces[ui32i].eMemReg,
                                        0,
                                        ui32SizeWrds,
                                        pui32Buf,
                                        IMG_FALSE);
        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to read register area %d",
                   asRegSpaces[ui32i].eMemReg);
            goto finish;
        }

        for (ui32Word = 0; ui32Word < ui32SizeWrds; ui32Word+=4)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x",
                   ui32Offset + ui32Word*sizeof(IMG_UINT32),
                   pui32Buf[ui32Word],
                   (ui32Word + 1) < ui32SizeWrds ? pui32Buf[ui32Word + 1] : 0,
                   (ui32Word + 2) < ui32SizeWrds ? pui32Buf[ui32Word + 2] : 0,
                   (ui32Word + 3) < ui32SizeWrds ? pui32Buf[ui32Word + 3] : 0);
        }
    }

    ui32RegVal = 0;
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RNW, 1);         // Read
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_USPECIFIER, 5);  // PC or PCX
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RSPECIFIER, 0);  // PC
    DEVAIO_PRINT_MTX_REG("MTX PC");

    ui32RegVal = 0;
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RNW, 1);         // Read
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_USPECIFIER, 5);  // PC or PCX
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RSPECIFIER, 1);  // PCX
    DEVAIO_PRINT_MTX_REG("MTX PCX");

    ui32RegVal = 0;
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RNW, 1);         // Read
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_USPECIFIER, 3);  // A0StP
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RSPECIFIER, 0);
    DEVAIO_PRINT_MTX_REG("MTX A0STP");

    ui32RegVal = 0;
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RNW, 1);         // Read
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_USPECIFIER, 3);  // A0FrP
    REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_REGISTER_READ_WRITE_REQUEST, MTX_RSPECIFIER, 1);
    DEVAIO_PRINT_MTX_REG("MTX A0FRP");

    ui32RamInfo = VXDIO_ReadRegister(psContext->hPvdecIoCtx, REGION_PVDEC_CORE_REGSPACE,
                                     PVDEC_CORE_CR_PROC_DEBUG_OFFSET, 0);
    ui32MTXBankSize = REGIO_READ_FIELD(ui32RamInfo, PVDEC_CORE, CR_PROC_DEBUG, CR_MTX_RAM_BANK_SIZE);
    ui32MTXBankSize = 1 << (ui32MTXBankSize + 2);

    REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Trying to dump 0x%x words from MTX RAM at 0x%x, bank: 0x%x",
           ui32NumWrdsToDump, ui32DumpOffsetWrds, ui32MTXBankSize);
    ui32RamId = 0;
    for (ui32i = ui32DumpOffsetWrds; ui32i < ui32NumWrdsToDump; ui32i+=4)
    {
        IMG_UINT32 aui32Value[4], ui32j, ui32Addr;

        for (ui32j = 0; ui32j < 4; ui32j++)
        {
            ui32RegVal = 0, ui32Addr = (ui32i + ui32j)*sizeof(IMG_UINT32);

            if ((DEVAIO_MTX_CORE_MEMORY + (ui32Addr / ui32MTXBankSize)) != ui32RamId)
            {
                ui32RamId = (DEVAIO_MTX_CORE_MEMORY + (ui32Addr / ui32MTXBankSize));
            }

            REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_RAM_ACCESS_CONTROL, MTX_MCMID, ui32RamId);
            REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_RAM_ACCESS_CONTROL, MTX_MCM_ADDR, ui32i + ui32j);
            REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_RAM_ACCESS_CONTROL, MTX_MCMAI, 0);
            REGIO_WRITE_FIELD(ui32RegVal, MTX_CORE, CR_MTX_RAM_ACCESS_CONTROL, MTX_MCMR, 1);

            VXDIO_WriteRegister(psContext->hPvdecIoCtx, REGION_PVDEC_MTX_CORE_REGSPACE,
                                MTX_CORE_CR_MTX_RAM_ACCESS_CONTROL_OFFSET, ui32RegVal,
                                0xffffffff, 0);

            aui32Value[ui32j] = VXDIO_ReadRegister(psContext->hPvdecIoCtx, REGION_PVDEC_MTX_CORE_REGSPACE,
                                                   MTX_CORE_CR_MTX_RAM_ACCESS_DATA_EXCHANGE_OFFSET, 0);
        }
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x",
               ui32i*sizeof(IMG_UINT32), aui32Value[0], aui32Value[1], aui32Value[2], aui32Value[3]);
    }

finish:
    IMG_FREE(pahMemSpaces);
    IMG_FREE(pui32Buf);
    return ui32Result;
}
#endif /* PVDEC_DEBUG_FACILITY */


/*
******************************************************************************

 @Function              devaio_GetCommsConfigFromMTX

******************************************************************************/
static IMG_RESULT devaio_GetCommsConfigFromMTX(
    DEVAIO_sContext  * psContext
)
{
    IMG_RESULT  ui32Result;
    IMG_UINT32  ui32Reg;

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       "Poll for FW signature");
#endif

    ui32Result = VXDIO_Poll(psContext->hPvdecIoCtx,
                            REGION_PVDEC_VLRFE_REGSPACE,
                            PVDEC_COM_RAM_SIGNATURE_OFFSET,
                            FW_READY_SIGNATURE,
                            0xffffffff,
                            VXDIO_POLL_EQUAL);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to poll for firmware signature!");
#ifdef PVDEC_DEBUG_FACILITY
        if (IMG_SUCCESS != devaio_dumpRegisters(psContext))
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to dump registers!");
        }
#endif /* PVDEC_DEBUG_FACILITY */
        return ui32Result;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       "Getting comms config from MTX");
#endif

    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRFE_REGSPACE,
                                    PVDEC_COM_RAM_TO_MTX_BUF_SIZE_AND_OFFSET_OFFSET,
                                    1,
                                    &ui32Reg,
                                    IMG_FALSE);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to read buffer size and offset!");
        return ui32Result;
    }

    psContext->sToMtxBuf.ui32Size   = PVDEC_COM_RAM_BUF_GET_SIZE(ui32Reg, TO_MTX);
    psContext->sToMtxBuf.ui32Offset = PVDEC_COM_RAM_BUF_GET_OFFSET(ui32Reg, TO_MTX);

    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRFE_REGSPACE,
                                    PVDEC_COM_RAM_TO_HOST_BUF_SIZE_AND_OFFSET_OFFSET,
                                    1,
                                    &ui32Reg,
                                    IMG_FALSE);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to read buffer size and offset!");
        return ui32Result;
    }

    psContext->sToHostBuf.ui32Size   = PVDEC_COM_RAM_BUF_GET_SIZE(ui32Reg, TO_HOST);
    psContext->sToHostBuf.ui32Offset = PVDEC_COM_RAM_BUF_GET_OFFSET(ui32Reg, TO_HOST);

    psContext->bReady = IMG_TRUE;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              devaio_CommsWriteWords

******************************************************************************/
static IMG_VOID devaio_CommsWriteWords(
    DEVAIO_sContext *  psContext,
    IMG_UINT32         ui32Offset,
    IMG_UINT32         ui32NumWords,
    IMG_UINT32 *       pui32Values,
    MEM_REGIONS_PVDEC  eMemSpace
)
{
#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, eMemSpace,
                       "Writing data to VLR");
#endif
    VXDIO_VLRWriteWords(psContext->hPvdecIoCtx, eMemSpace,
                        ui32Offset, ui32NumWords, pui32Values);
}


/*!
******************************************************************************

 @Function              devaio_CommsReadWords

******************************************************************************/
static IMG_VOID devaio_CommsReadWords(
    DEVAIO_sContext  * psContext,
    IMG_UINT32         ui32Offset,
    IMG_UINT32         ui32NumWords,
    IMG_UINT32       * pui32Values,
    IMG_BOOL           bValidate
)
{
#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       "Reading data from VLR");
#endif
    VXDIO_VLRReadWords(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       ui32Offset, ui32NumWords, pui32Values, bValidate);
}


/*!
******************************************************************************

 @Function              devaio_WaitForCommsSpace

******************************************************************************/
static IMG_VOID devaio_WaitForCommsSpace(
    DEVAIO_sContext *  psContext,
    IMG_UINT32         ui32WriteIdx,
    IMG_UINT32         ui32MessageSize,
    IMG_UINT32         ui32BufferSize,
    IMG_HANDLE         hPvdecIoCtx
)
{
    IMG_UINT32  ui32ReadIndex;
    IMG_UINT32  ui32WaitRetry = MSVDX_MAX_NUM_COMMS_SPACE_RETRIES;

    /* setup wait object */
    IMG_HANDLE  hEventHandle = IMG_NULL;
    IMG_HANDLE  hTimerHandle = IMG_NULL;
    IMG_RESULT  ui32Result;

    /* create an event object */
    ui32Result = SYSOSKM_CreateEventObject( &hEventHandle );
    IMG_ASSERT( ui32Result == IMG_SUCCESS );
    if ( ui32Result != IMG_SUCCESS )
    {
        return;
    }
    /* create a timer and attach to the event object */
    ui32Result = SYSOSKM_CreateTimer(devaio_fnTimer, hEventHandle, 1, &hTimerHandle);
    IMG_ASSERT( ui32Result == IMG_SUCCESS );
    if ( ui32Result != IMG_SUCCESS )
    {
        SYSOSKM_DestroyEventObject(hEventHandle);
        return;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " + Waiting for free space in VLR comms area");
#endif
    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRFE_REGSPACE,
                                    PVDEC_COM_RAM_TO_MTX_RD_INDEX_OFFSET,
                                    1,
                                    &ui32ReadIndex,
                                    IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    while (
           (ui32WaitRetry--)
           &&
           (
            /* write pointer will overtake read pointer */
            (
             (ui32WriteIdx < ui32ReadIndex) &&
             ((ui32WriteIdx + ui32MessageSize) >= ui32ReadIndex)
            )
            ||
            /* or message will fill buffer and hit read pointer at start of buffer */
            (
             (ui32ReadIndex == 0) &&
             ((ui32WriteIdx + ui32MessageSize) == ui32BufferSize)
            )
           )
          )
    {
        /* wait for a millisecond */
        SYSOSKM_WaitEventObject( hEventHandle, IMG_TRUE );

        ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                        REGION_PVDEC_VLRFE_REGSPACE,
                                        PVDEC_COM_RAM_TO_MTX_RD_INDEX_OFFSET,
                                        1,
                                        &ui32ReadIndex,
                                        IMG_FALSE);
    }

    /* remove the timer before the event object */
    /* remove wait object */
    if ( hTimerHandle )
    {
        SYSOSKM_DestroyTimer( hTimerHandle );
    }

    /* remove wait object */
    if ( hEventHandle )
    {
        SYSOSKM_DestroyEventObject( hEventHandle );
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    {
        VXDIO_PDUMPPollCircBuff(psContext->hPvdecIoCtx,
                                REGION_PVDEC_VLRFE_REGSPACE,
                                PVDEC_COM_RAM_TO_MTX_RD_INDEX_OFFSET,
                                ui32WriteIdx,
                                ui32MessageSize,
                                ui32BufferSize);
    }
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " - Waiting for free space in VLR comms area done");
#endif
}


/*!
******************************************************************************

 @Function              devaio_CopyMessageData

******************************************************************************/
static IMG_UINT32 devaio_CopyMessageData(
    DEVAIO_sContext  * psContext,
    IMG_UINT32         ui32ReadIdx,
    IMG_UINT32         ui32HostWriteIdx,
    IMG_UINT32         ui32HostReadIdx,
    IMG_UINT32         ui32MessageSize,
    IMG_UINT32         ui32BufferSize,
    VXDIO_sHISRMsg   * psMessage,
    IMG_UINT32       * pui32CopyMsgBuf
)
{
    /* set the write index into the internal DEVAIO buffer */
    if ( (ui32HostWriteIdx + ui32MessageSize) > MSVDX_SIZE_MSG_BUFFER )
    {
        ui32HostWriteIdx = 0;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       " + Obtaining message Data");
#endif

    // Sanity check - message container has been provided.
    IMG_ASSERT( psMessage );

    /* sanity check - message will fit in internal MTXIO buffer */
    IMG_ASSERT( (ui32HostWriteIdx + ui32MessageSize) <= MSVDX_SIZE_MSG_BUFFER );
    IMG_ASSERT( (ui32HostReadIdx <= ui32HostWriteIdx) || (ui32HostWriteIdx + ui32MessageSize) <= ui32HostReadIdx);

    /* record the location of the message in the internal DEVAIO buffer */
    psMessage->ui32MsgIndex = ui32HostWriteIdx;
    psMessage->ui32MsgSize = ui32MessageSize;

    /* if the message wraps in the MTX buffer, read the portion the the end of the buffer */
    if ( (ui32ReadIdx + ui32MessageSize) >= ui32BufferSize )
    {
        IMG_UINT32 ui32FirstPartSize = ui32BufferSize - ui32ReadIdx;

        devaio_CommsReadWords(psContext,
                              psContext->sToHostBuf.ui32Offset + (ui32ReadIdx << 2),
                              ui32FirstPartSize,
                              &pui32CopyMsgBuf[ui32HostWriteIdx],
                              IMG_TRUE);

        ui32ReadIdx = 0;
        ui32MessageSize -= ui32FirstPartSize;
        ui32HostWriteIdx += ui32FirstPartSize;
    }

    if (ui32MessageSize > 0)
    {
        devaio_CommsReadWords(psContext,
                              psContext->sToHostBuf.ui32Offset + (ui32ReadIdx << 2),
                              ui32MessageSize,
                              &pui32CopyMsgBuf[ui32HostWriteIdx],
                              IMG_TRUE);
    }

    ui32ReadIdx += ui32MessageSize;
    ui32HostWriteIdx += ui32MessageSize;

    /* update DEVAIO internal buffer write index */
    psMessage->ui32NewWriteIndex = ui32HostWriteIdx;

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       " - Obtaining message Data done");
#endif

    return ui32ReadIdx;
}


/*!
******************************************************************************

 @Function              DEVAIO_InitMTXComms

******************************************************************************/
IMG_RESULT DEVAIO_InitMTXComms(
    IMG_HANDLE       * hPvdecIoCtx,
    DEVAIO_sContext  * psContext
)
{
    IMG_RESULT  ui32Result = IMG_SUCCESS;
    IMG_UINT32  ui32FwDbgLevel = 0xffffffff;
    IMG_UINT32  ui32FwSignature = 0;
    IMG_UINT32  ui32FwFlags = FWFLAG_FORCE_FS_FLOW | FWFLAG_DISABLE_GENC_FLUSHING | FWFLAG_DISABLE_AUTONOMOUS_RESET;

    psContext->hPvdecIoCtx = hPvdecIoCtx;

    /* Set firmware debug level */
    devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_FW_ID_OFFSET,
                           1, &ui32FwDbgLevel, REGION_PVDEC_VLRFE_REGSPACE);
    /* Set firmware flags */
    devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_FLAGS_OFFSET,
                           1, &ui32FwFlags, REGION_PVDEC_VLRFE_REGSPACE);
    /* Reset signature. */
    devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_SIGNATURE_OFFSET,
                           1, &ui32FwSignature, REGION_PVDEC_VLRFE_REGSPACE);

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
    /* Initialise debug FIFO. */
    ui32Result = devaio_InitDebugFifo(psContext);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to initialize debug FIFO context!");
    }
#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

    return ui32Result;
}


/*
******************************************************************************

 @Function              DEVAIO_SendMTXMsg

******************************************************************************/
IMG_RESULT DEVAIO_SendMTXMsg(
    DEVAIO_sContext   * psContext,
    const IMG_VOID    * psMsgHdr,
    const IMG_HANDLE    hPvdecIoCtx
)
{
    IMG_RESULT    ui32Result;
    IMG_UINT32    ui32NumTxWords, ui32ReadIndex, ui32WriteIndex;
    IMG_UINT32  * pui32Msg = (IMG_UINT32*)psMsgHdr;

    if (!psContext->bReady)
    {
        ui32Result = devaio_GetCommsConfigFromMTX(psContext);
        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_VXDIO, REPORT_ERR, "Failed to initialize communication area!");
            return ui32Result;
        }
    }

    ui32NumTxWords = MEMIO_READ_FIELD(pui32Msg, FW_DEVA_GENMSG_MSG_SIZE);

    IMG_ASSERT(ui32NumTxWords <= psContext->sToMtxBuf.ui32Size);

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " + Sending message to MTX");
#endif

    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRFE_REGSPACE,
                                    PVDEC_COM_RAM_TO_MTX_RD_INDEX_OFFSET,
                                    1,
                                    &ui32ReadIndex,
                                    IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRFE_REGSPACE,
                                    PVDEC_COM_RAM_TO_MTX_WRT_INDEX_OFFSET,
                                    1,
                                    &ui32WriteIndex,
                                    IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    /* Will the message wrap, if so need to send a pad message */
    if (ui32WriteIndex + ui32NumTxWords > psContext->sToMtxBuf.ui32Size)
    {
        IMG_UINT8 aui8Msg[FW_DEVA_GENMSG_SIZE]; // buffer for FW message
        IMG_INT32 i32PaddingWords = psContext->sToMtxBuf.ui32Size - ui32WriteIndex;
        IMG_UINT32 ui32MsgSizeWords = FW_DEVA_GENMSG_SIZE/4;
        IMG_ASSERT(i32PaddingWords > 0);
        IMG_MEMSET(&aui8Msg[0], 0, sizeof(aui8Msg));

        MEMIO_WRITE_FIELD(&aui8Msg[0], FW_DEVA_GENMSG_MSG_SIZE, i32PaddingWords);
        MEMIO_WRITE_FIELD(&aui8Msg[0], FW_DEVA_GENMSG_MSG_TYPE, MSG_TYPE_PADDING);

        devaio_WaitForCommsSpace(psContext, ui32WriteIndex, i32PaddingWords, psContext->sToMtxBuf.ui32Size, hPvdecIoCtx);

        devaio_CommsWriteWords(psContext, psContext->sToMtxBuf.ui32Offset + (ui32WriteIndex << 2),
                               ui32MsgSizeWords, (IMG_UINT32 *)&aui8Msg[0], REGION_PVDEC_VLRFE_REGSPACE);

        ui32WriteIndex = 0;
        devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_TO_MTX_WRT_INDEX_OFFSET,
                               1, &ui32WriteIndex, REGION_PVDEC_VLRFE_REGSPACE);

        PVDECIO_KickMTX(hPvdecIoCtx);
    }

    devaio_WaitForCommsSpace(psContext, ui32WriteIndex, ui32NumTxWords, psContext->sToMtxBuf.ui32Size, hPvdecIoCtx);

    devaio_CommsWriteWords(psContext, psContext->sToMtxBuf.ui32Offset + (ui32WriteIndex << 2),
                           ui32NumTxWords, pui32Msg, REGION_PVDEC_VLRFE_REGSPACE);

    ui32WriteIndex += ui32NumTxWords;

    if (ui32WriteIndex == psContext->sToMtxBuf.ui32Size)
    {
        ui32WriteIndex = 0;
    }

    devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_TO_MTX_WRT_INDEX_OFFSET,
                           1, &ui32WriteIndex, REGION_PVDEC_VLRFE_REGSPACE);

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRFE_REGSPACE,
                       " - Sending message to MTX done");
#endif

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              DEVAIO_ProcessMTXMsgs

******************************************************************************/
IMG_RESULT DEVAIO_ProcessMTXMsgs(
    DEVAIO_sContext  * psContext,
    VXD_sMsgQueue    * psMsgQStatus
)
{
    IMG_UINT32        ui32ReadIndex, ui32WriteIndex, ui32BufferSize, ui32FirstWord;
    IMG_UINT32        ui32MessageSize; /* in bytes */
    IMG_UINT16        ui16MsgType;
    IMG_UINT32      * pui32FirstWord;
    VXDIO_sHISRMsg  * psMessage;
    IMG_RESULT        ui32Result;

    // Initialise the output flags.
    IMG_ASSERT(psMsgQStatus);
    psMsgQStatus->bEmpty = IMG_FALSE;
    psMsgQStatus->bQueued = IMG_FALSE;
    IMG_ASSERT(!LST_empty(&psMsgQStatus->sFreeMsgList));
    IMG_ASSERT(LST_empty(&psMsgQStatus->sNewMsgList));

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       " + Processing MTX message");
#endif

    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRBE_REGSPACE,
                                    PVDEC_COM_RAM_TO_HOST_RD_INDEX_OFFSET,
                                    1,
                                    &ui32ReadIndex,
                                    IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    ui32Result = VXDIO_VLRReadWords(psContext->hPvdecIoCtx,
                                    REGION_PVDEC_VLRBE_REGSPACE,
                                    PVDEC_COM_RAM_TO_HOST_WRT_INDEX_OFFSET,
                                    1,
                                    &ui32WriteIndex,
                                    IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    ui32BufferSize = psContext->sToHostBuf.ui32Size;

    IMG_MEMSET(&ui32FirstWord, 0, sizeof(ui32FirstWord));

    /* While there are messages to read and somewhere to put them. */
    while (ui32ReadIndex != ui32WriteIndex &&
           LST_first(&psMsgQStatus->sFreeMsgList))
    {
#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
        VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                           "Wait for FW message");
        /* reproduce message reading in a pdump script */
        VXDIO_Poll(psContext->hPvdecIoCtx,
                   REGION_PVDEC_VLRBE_REGSPACE,
                   PVDEC_COM_RAM_TO_HOST_WRT_INDEX_OFFSET,
                   ui32ReadIndex,
                   0xffffffff,
                   VXDIO_POLL_NOT_EQUAL);
#endif

        /* read the first word of the message */
        devaio_CommsReadWords(psContext,
                              psContext->sToHostBuf.ui32Offset + (ui32ReadIndex << 2),
                              1,
                              &ui32FirstWord,
                              IMG_TRUE);


        pui32FirstWord = &ui32FirstWord;
        ui32MessageSize = MEMIO_READ_FIELD(pui32FirstWord, FW_DEVA_GENMSG_MSG_SIZE);
        ui16MsgType = MEMIO_READ_FIELD(pui32FirstWord, FW_DEVA_GENMSG_MSG_TYPE);

        /* sanity check - message fits in buffer */
        IMG_ASSERT(ui32MessageSize < ui32BufferSize);
        IMG_ASSERT((ui32ReadIndex > ui32WriteIndex) || ((ui32ReadIndex + ui32MessageSize) <= ui32WriteIndex));
        /* sanity check - message is of the MTX -> Host type */
        IMG_ASSERT(ui16MsgType >= FW_DEVA_COMPLETED);

        psMessage = LST_removeHead(&psMsgQStatus->sFreeMsgList);
        IMG_ASSERT(psMessage);

        /* copy message into internal buffer and get new read index */
        ui32ReadIndex = devaio_CopyMessageData(psContext,
                                               ui32ReadIndex,
                                               psMsgQStatus->ui32WriteIdx,
                                               psMsgQStatus->ui32ReadIdx,
                                               ui32MessageSize,
                                               ui32BufferSize,
                                               psMessage,
                                               psMsgQStatus->aui32MsgBuf);

        psMsgQStatus->ui32WriteIdx = psMessage->ui32NewWriteIndex;

        /* Add the message to the HISR active list */
        LST_add(&psMsgQStatus->sNewMsgList, psMessage);

        /* update the read index */
        devaio_CommsWriteWords(psContext, PVDEC_COM_RAM_TO_HOST_RD_INDEX_OFFSET,
                               1, &ui32ReadIndex, REGION_PVDEC_VLRBE_REGSPACE);

        psMsgQStatus->bQueued = IMG_TRUE;
    }

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
    VXDIO_PDUMPComment(psContext->hPvdecIoCtx, REGION_PVDEC_VLRBE_REGSPACE,
                       " - Processing MTX message done");
#endif

    /* report success or otherwise */
    psMsgQStatus->bEmpty = ((ui32ReadIndex == ui32WriteIndex) ? IMG_TRUE: IMG_FALSE);

    return IMG_SUCCESS;
}


/* EOF */
