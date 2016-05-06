


/******************************************************************************
  File Name       : socp_st_test.c
  Description     : SOCP模块的ST验证用例，也作为回片测试用例
                    随着SOCP版本更新，需要补充新功能的测试用例
  History         :
     1.c00326366       2015-12-02   Draft Enact

******************************************************************************/


#include <osl_malloc.h>
#include "socp_balong.h"
#include "product_config.h"
#include "arm_pbxa9.h"
#include "osl_thread.h"
#include "osl_malloc.h"

#define SOCP_CODER_DEST_CHAN_0      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 0)
#define SOCP_CODER_DEST_CHAN_1      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 1)
#define SOCP_CODER_DEST_CHAN_2      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 2)
#define SOCP_CODER_DEST_CHAN_3      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 3)


static BSP_BOOL g_bInit = BSP_FALSE;

static BSP_U32 g_SocpBufCnt = 0;
static BSP_U8  *g_pSocpBuf[1000];

extern BSP_S32 socp_init();

#define DEV_INIT()\
do{\
    if(!g_bInit)\
    {\
        if(BSP_OK != socp_init())\
        {\
            socp_printf("init fail...\n");\
            return BSP_ERROR;\
        }\
        g_bInit = BSP_TRUE;\
    }\
}while(0)

#define CHECK_SET(id)\
do{\
    if(BSP_ERR_SOCP_SET_FAIL != SocpSetEncChan1(id))\
    {\
        return BSP_ERROR;\
    }\
}while(0)


#define CHECK_RET(a, b)\
do{\
    BSP_S32 x;\
    x = a;\
    if(x != b)\
    {\
        socp_printf("%s(%d): ret(0x%x) error...\n", __FUNCTION__, __LINE__, x);\
        return x;\
    }\
}while(0)


#define CHECK_VAL(a, b)\
do{\
    if(a != b)\
    {\
        socp_printf("%s(%d): value error... 0x%x 0x%x\n", __FUNCTION__, __LINE__, a, b);\
        return BSP_ERROR;\
    }\
}while(0)


typedef struct
{
    BSP_U8   usSId;
    BSP_U8   usSSId;
    BSP_U8   ucServiceSessionId;
    BSP_U8   ucMsgType;
    BSP_U32  ulMsgTransId;
    BSP_U8   aucTimeData[8];
} SOCP_PACKET_HEAD_S;

typedef struct tagSOCP_ST_CASE_S{
    BSP_U32                 bDstSet;
    BSP_U32                 SrcCh;
    BSP_U32                 DstCh;
    BSP_U32		            u32BypassEn;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eMode;
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    BSP_U32                 u32InputStart;
    BSP_U32                 u32InputSize;
    BSP_U32                 u32RDStart;
    BSP_U32                 u32RDSize;
    BSP_U32                 u32RDThreshold;
    BSP_U32                 u32OutputStart;
    BSP_U32                 u32OutputSize;
    BSP_U32                 u32Threshold;
    socp_event_cb           EventCb;
    socp_read_cb            ReadCb;
    socp_rd_cb              RdCb;
    BSP_U32                 TaskId;
    BSP_U32                 u32DataLen;
    BSP_U32                 u32DataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eEncDebugEn;
    BSP_U32                 u32EncDstThrh;
}SOCP_ST_CASE_S;

static BSP_U32 g_socpRxTotal[7] = {0};
static BSP_U32 g_socpRdTotal[25] = {0};
static BSP_U32 g_socpTxTotal[25] = {0};

static BSP_S32 SocpStAllocEncSrc(SOCP_ST_CASE_S *pCase)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U8 *p;
    BSP_U8 *pRd = 0;

    p = (BSP_U8*)osl_cachedma_malloc(pCase->u32InputSize);

    if(BSP_NULL == p)
    {
        socp_printf("%s[%d] ALLOC ENC SRC FAILED!\n", __FUNCTION__, __LINE__);
        return BSP_ERROR;
    }
    
    pCase->u32InputStart = (BSP_U32)p;
    g_pSocpBuf[g_SocpBufCnt++] = p;

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        pRd = (BSP_U8*)osl_cachedma_malloc(pCase->u32RDSize);
        if(BSP_NULL == pRd)
        {
            socp_printf("%s[%d] ALLOC ENC SRC RD BUF FAILED!\n", __FUNCTION__, __LINE__);
            osl_free(g_pSocpBuf[--g_SocpBufCnt]);
            return BSP_ERROR;
        }
        pCase->u32RDStart = (BSP_U32)pRd;
        g_pSocpBuf[g_SocpBufCnt++] = pRd;
    }

    pCase->u32InputStart = (BSP_U32)p;
    EncSrcAttr.eDataType = pCase->eDataType;
    EncSrcAttr.eDataTypeEn = pCase->eDataTypeEn;
    EncSrcAttr.eDebugEn = pCase->eEncDebugEn;
    EncSrcAttr.eMode = pCase->eMode;
    EncSrcAttr.ePriority = pCase->ePriority;
    EncSrcAttr.u32BypassEn = pCase->u32BypassEn;
    EncSrcAttr.u32DestChanID = pCase->DstCh;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = p;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = p + pCase->u32InputSize - 1;
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        EncSrcAttr.sCoderSetSrcBuf.pucRDStart = pRd;
        EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = pRd + pCase->u32RDSize - 1;
        EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = pCase->u32Threshold;
    }

    if(BSP_OK != bsp_socp_coder_set_src_chan(pCase->SrcCh, &EncSrcAttr))
    {
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);

        socp_printf("alloc enc src channel failed!\n");

        return BSP_ERROR;
    }

    return 0;
}


static BSP_S32 SocpStEventCB_1(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
{
    BSP_U32 u32ChanType =  SOCP_REAL_CHAN_TYPE(u32ChanID);
    BSP_U32 u32ChanId   =  SOCP_REAL_CHAN_ID(u32ChanID);

    switch(u32Event)
    {
        case SOCP_EVENT_PKT_HEADER_ERROR:
        {
            socp_printf("chan type is [%d], id is [%d], event is packet header check error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_OUTBUFFER_OVERFLOW:
        {
            socp_printf("chan type is [%d], id is [%d], event is outbuffer overflow!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_HDLC_HEADER_ERROR:
        {
            socp_printf("chan type is [%d], id is [%d], event is 0x7e error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_CRC_ERROR:
        {
            socp_printf("chan type is [%d], id is [%d], event is crc error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_PKT_LENGTH_ERROR:
        {
            socp_printf("chan type is [%d], id is [%d], event is pkt length error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_DATA_TYPE_ERROR:
        {
            socp_printf("chan type is [%d], id is [%d], event is data type error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_DECODER_UNDERFLOW:
        {
            socp_printf("chan type is [%d], id is [%d], event is inbuf underflow error!\n", u32ChanType, u32ChanId);
            break;
        }
        default:
        {
            socp_printf("the event:0x%x is valid!\n", u32Event);
            return BSP_ERROR;
        }

    }

    return BSP_OK;
}


static BSP_S32 SocpStReadCB_1(BSP_U32 u32ChanID)
{
    return 0;
}

static BSP_S32 SocpStReadCB_2(BSP_U32 u32ChanID)
{
    return 0;
}

static BSP_S32 SocpStReadCB_3(BSP_U32 u32ChanID)
{
    return 0;
}

static BSP_S32 SocpStReadCB_4(BSP_U32 u32ChanID)
{
    return 0;
}


static BSP_S32 SocpStReadCB_19(BSP_U32 u32ChanID)
{
    return 0;
}

static BSP_S32 SocpStRdCB_1(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

    return 0;
}

static BSP_S32 SocpStRdCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

    return 0;
}

static SOCP_ST_CASE_S g_stCase[30] =
{
    {
        // 0    源通道4，目的通道0，连续数据包环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长24，循环发送100次
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 1    源通道4，目的通道0，链式环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长24，循环发送100次
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 100,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 2
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 4, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 3
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 580, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 4,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 4
        0, 4, SOCP_CODER_DEST_CHAN_0, 1, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 5
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_1, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 6
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 100, 5, 0, 0x1000, 100, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 96, 100,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 7
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x100, 2, SocpStEventCB_1, SocpStReadCB_4, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 8
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x100, 0, 0x40, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 64, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 9
        0, 4, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 10
        0, 4, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 11   源通道4，目的通道2，数据包环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长24，循环发送10000次
        0, 4, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 12   源通道5，目的通道2，链式环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长1024，循环发送10000次
        0, 5, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 13   源通道6，目的通道3，数据包环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长24，循环发送10000次
        0, 6, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 14   源通道7，目的通道3，链式环形buffer，源buffer size 0x1000，目的buffer size 0x1000
        //      单包包长1024，循环发送10000次
        0, 7, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 15
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 16
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 17
        0, 4, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 18
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 19
        0, 0, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 24, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 20
        0, 0, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 21
        0, 0, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 24, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 22
        0, 0, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 26
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x3000, 0, 160, 40, 0, 0x3000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 2043, 1, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },

    {
        // 27
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_DIS,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 28
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x1000
    },
    {
        // 29
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 1, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_EN, 0x0
    },
};

static BSP_VOID SocpStGenPayLoad(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 ulTime = 0;
    BSP_U32 ulTime1 = 0;
    SOCP_PACKET_HEAD_S * pstSocpPackt = (SOCP_PACKET_HEAD_S*)pBuff;
    int i;

    // 组包SOCP
    ulTime                           = 0x08070605;
    ulTime1                           = 0x0d0c0b0a;
    pstSocpPackt->usSId              = 1;
    pstSocpPackt->usSSId             = 2;
    pstSocpPackt->ucServiceSessionId = 3;
    pstSocpPackt->ucMsgType          = 4;
    Socp_Memcpy(pstSocpPackt->aucTimeData, &ulTime, 4);
    Socp_Memcpy(pstSocpPackt->aucTimeData + 4, &ulTime1, 4);
    pstSocpPackt->ulMsgTransId = 100;

    for(i=16; i<(int)u32DataLen; i++)
    {
        pBuff[i] = 0xA5;
    }

    return;
}

static BSP_VOID SocpStGenPkt(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    // 组包头
    pBuff[0] = 0x49;
    pBuff[1] = 0x53;
    pBuff[2] = 0x49;
    pBuff[3] = 0x48;

    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;


    // 组消息包
    SocpStGenPayLoad((pBuff+8), u32DataLen-16);

    return;
}


static BSP_VOID SocpStGenBD1(BSP_U32 *pBD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    // 组包头
    pBD[0] = (BSP_U32)pBuff;
    pBD[1] = 0;
    pBD[1] |= (0xffff & u32DataLen);

    // 组消息包
    SocpStGenPayLoad(pBuff, u32DataLen);

    return;
}

static BSP_S32 socp_encode_task001(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen + 8;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, len);
            }
            else
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, WtBuff.u32Size);
                Socp_Memcpy(WtBuff.pRbBuffer, packet+WtBuff.u32Size, len-WtBuff.u32Size);
            }
            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            osl_task_delay(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
        osl_task_delay(0);
    }

    osl_task_delay(100);
    osl_cachedma_free(packet);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

static BSP_S32 socp_encode_task003(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    BSP_U8 bd[8];
    int vfcnt = 0;
    int c;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= 8)
        {
            if(WtBuff.u32Size >= 8)
            {
                Socp_Memcpy(WtBuff.pBuffer, bd, 8);
            }
            else
            {
                Socp_Memcpy(WtBuff.pBuffer, bd, WtBuff.u32Size);
                Socp_Memcpy(WtBuff.pRbBuffer, bd+WtBuff.u32Size, 8-WtBuff.u32Size);
            }
            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, 8), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            osl_task_delay(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
        osl_task_delay(0);
    }

    osl_task_delay(100);
    osl_cachedma_free(packet);

    socp_printf("cnt is %d, chan[%d] write done! totol=0x%x size=0x%x\n", cnt, pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


static int socp_encode_task005(void *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen + 8;    // 块式环形buffer需要增加HISI头和长度8个字节
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;

    CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenPkt(packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        
        socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            vfcnt = 0;
            if(WtBuff.u32Size >= (u32)len)
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, len);
            }
            else
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, WtBuff.u32Size);
                Socp_Memcpy(WtBuff.pRbBuffer, packet+WtBuff.u32Size, len-WtBuff.u32Size);
            }
            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            osl_task_delay(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }

    osl_task_delay(100);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


static BSP_S32 socp_encode_task010(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen + 8;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;
    int i;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;

    for(i=0;i<(int)(pCase->u32DataLen);i++)
    {
        /*if((0 != i%100) && (i != 0x7e))
        {
            packet[i] = i%256;
        }
        else
        {
            packet[i] = 0x7e;
        }*/
        packet[i] = i%256;
        if(0x7e == packet[i] || (0x7d == packet[i]))
        {
            packet[i] = 0x12;
            socp_printf("packet[%d] is 0x%x\n", i, packet[i]);
        }
    }
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, len);
            }
            else
            {
                Socp_Memcpy(WtBuff.pBuffer, packet, WtBuff.u32Size);
                Socp_Memcpy(WtBuff.pRbBuffer, packet+WtBuff.u32Size, len-WtBuff.u32Size);
            }
            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            osl_task_delay(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    //osl_free(packet);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


/* 编码测试, MODEM CPU发APP CPU收，固定长度块式数据包 */
/* 与APP CPU上SOCP_ST_ENCODE_006_START用例匹配 */
BSP_S32 SOCP_ST_ENCODE_006_START()
{
    char task_name[30] = {0};

    DEV_INIT();

    sprintf_s(task_name,30,"socpTest%02d",6);

    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task005, &g_stCase[0], &(g_stCase[0].TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_006_STOP()
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);
    
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);    //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    
    /*释放任务*/
    (BSP_VOID)osl_task_delete(&g_stCase[0].TaskId);

    return 0;
}



/* 编码测试,测试数据包长为2048的情况*/
BSP_S32 SOCP_ST_ENCODE_015_START()
{
    char task_name[30] = {0};
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    DEV_INIT();

    pCase->u32InputSize = 0x10000;
    pCase->u32OutputSize = 0x2000;
    pCase->u32Threshold = 1024;
    pCase->u32DataLen = 2024;
    pCase->u32DataCnt = 1;

    CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    sprintf_s(task_name,30,"socpTest%02d",10);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task010, pCase, &pCase->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_015_STOP()
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    /*释放任务*/
    (BSP_VOID)osl_task_delete(&g_stCase[0].TaskId);

    return 0;
}

/* 编码测试 , 双核多通道测试*/
BSP_S32 SOCP_ST_ENCODE_020_START()
{
    char task_name[30] = {0};
    SOCP_ST_CASE_S *pCase0 = &g_stCase[15];
    SOCP_ST_CASE_S *pCase1 = &g_stCase[16];
    SOCP_ST_CASE_S *pCase2 = &g_stCase[9];
    SOCP_ST_CASE_S *pCase3 = &g_stCase[10];
    SOCP_ST_CASE_S *pCase4 = &g_stCase[11];
    SOCP_ST_CASE_S *pCase5 = &g_stCase[12];
    SOCP_ST_CASE_S *pCase6 = &g_stCase[13];
    SOCP_ST_CASE_S *pCase7 = &g_stCase[14];

    DEV_INIT();
    Socp_Memset(g_socpRdTotal, 0, sizeof(g_socpRdTotal));
    Socp_Memset(g_socpRxTotal, 0, sizeof(g_socpRxTotal));
    Socp_Memset(g_socpTxTotal, 0, sizeof(g_socpTxTotal));

    CHECK_RET(SocpStAllocEncSrc(pCase4), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase5), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase6), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase7), BSP_OK);
    
    socp_printf("0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",pCase0->SrcCh,pCase1->SrcCh,pCase2->SrcCh,pCase3->SrcCh,
        pCase4->SrcCh,pCase5->SrcCh,pCase6->SrcCh,pCase7->SrcCh);
    
    CHECK_RET(bsp_socp_register_event_cb(pCase4->SrcCh, pCase4->EventCb), BSP_OK);
    if(pCase4->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase4->SrcCh, pCase4->RdCb), BSP_OK);
    }
    
    CHECK_RET(bsp_socp_register_event_cb(pCase5->SrcCh, pCase5->EventCb), BSP_OK);
    if(pCase5->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase5->SrcCh, pCase5->RdCb), BSP_OK);
    }
    
    CHECK_RET(bsp_socp_register_event_cb(pCase6->SrcCh, pCase6->EventCb), BSP_OK);
    if(pCase6->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase6->SrcCh, pCase6->RdCb), BSP_OK);
    }
    
    CHECK_RET(bsp_socp_register_event_cb(pCase7->SrcCh, pCase7->EventCb), BSP_OK);
    if(pCase7->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase7->SrcCh, pCase7->RdCb), BSP_OK);
    }

    CHECK_RET(bsp_socp_start(pCase4->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase5->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase6->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase7->SrcCh), BSP_OK);

    sprintf_s(task_name,30,"socpTest%03d",194);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task001, pCase4, &(pCase4->TaskId)))
    {
        return BSP_ERROR;
    }

    sprintf_s(task_name,30,"socpTest%03d",195);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task003, pCase5, &(pCase5->TaskId)))
    {
        return BSP_ERROR;
    }

    sprintf_s(task_name,30,"socpTest%03d",196);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task001, pCase6, &(pCase6->TaskId)))
    {
        return BSP_ERROR;
    }

    sprintf_s(task_name,30,"socpTest%03d",197);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task003, pCase7, &(pCase7->TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_020_STOP()
{
   /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[11].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[11].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[12].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[12].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[13].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[13].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[14].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[14].SrcCh), BSP_OK);
    // pCase4
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[11].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    // pCase5
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[12].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    // pCase6
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[13].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    // pCase7
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[14].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }

    (BSP_VOID)osl_task_delete(&g_stCase[11].TaskId);
    (BSP_VOID)osl_task_delete(&g_stCase[12].TaskId);
    (BSP_VOID)osl_task_delete(&g_stCase[13].TaskId);
    (BSP_VOID)osl_task_delete(&g_stCase[14].TaskId);

    return 0;
}




