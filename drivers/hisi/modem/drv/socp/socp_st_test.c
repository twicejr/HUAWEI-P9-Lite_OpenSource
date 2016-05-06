
 
 /******************************************************************************
   File Name       : socp_st_test.c
   Description     : SOCP模块的ST验证用例，也作为回片测试用例
                     随着SOCP版本更新，需要补充新功能的测试用例
   History         :
      1.c00326366       2015-12-02   Draft Enact
 
 ******************************************************************************/

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include "socp_balong.h"

#define SOCP_CODER_DEST_CHAN_0      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 0)
#define SOCP_CODER_DEST_CHAN_1      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 1)
#define SOCP_CODER_DEST_CHAN_2      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 2)
#define SOCP_CODER_DEST_CHAN_3      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 3)
#define SOCP_CODER_DEST_CHAN_4      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 4)
#define SOCP_CODER_DEST_CHAN_5      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 5)
#define SOCP_CODER_DEST_CHAN_6      SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, 6)

#define SOCP_DECODER_SRC_CHAN_0     SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 0)
#define SOCP_DECODER_SRC_CHAN_1     SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 1)
#define SOCP_DECODER_SRC_CHAN_2     SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 2)
#define SOCP_DECODER_SRC_CHAN_3     SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN, 3)

#define SOCP_DECODER_DEST_CHAN_0    SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0)
#define SOCP_DECODER_DEST_CHAN_1    SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 1)
#define SOCP_DECODER_DEST_CHAN_2    SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 2)
#define SOCP_DECODER_DEST_CHAN_3    SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 3)


#define SOCP_VIRT_TO_PHYS(virt) (unsigned char *)(virt_to_phys((void*)virt))
#define SOCP_PHYS_TO_VIRT(phy)  (void *)(phys_to_virt((unsigned long)phy))

static unsigned long long g_socp_dma_test_mask=0xffffffffULL;
#define SOCP_TEST_FLUSH_CACHE(ptr, size)                      \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_socp_dma_test_mask);    \
        dma_map_single(&dev, ptr, size, DMA_TO_DEVICE);  \
    }while(0)
#define SOCP_TEST_INVALID_CACHE(ptr, size)                    \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_socp_dma_test_mask);    \
        dma_map_single(&dev, ptr, size, DMA_FROM_DEVICE);  \
    }while(0)


static BSP_VOID* TM_socp_malloc(BSP_U32 u32Size)
{
    BSP_U8 *pItem= NULL;
    BSP_U32 index = 0;

    if(BSP_OK != socp_get_index(u32Size,&index))
    {
        return BSP_NULL;
    }

    index = 4;
    /* 分配内存 */
    pItem = (BSP_U8*)__get_free_pages(GFP_KERNEL,index);
    if(!pItem)
    {
        socp_printf("malloc failed\n");
        return BSP_NULL;
    }

    return (void*)pItem;
}

static BSP_S32 TM_socp_free(BSP_VOID* pMem)
{
    BSP_U32 *pItem;

    pItem = pMem;

    (void)free_pages((unsigned long)pItem,4);
    return BSP_OK;
}
static BSP_BOOL g_bInit = BSP_FALSE;

static BSP_U32 g_SocpBufCnt = 0;
static BSP_U8  *g_pSocpBuf[1000];

/* GTR自动化测试编解码测试用例，数据包接收标志 */
static u32 g_ul_rev_pkt_flag  = false;
/* GTR自动化测试编解码测试用例，异常事件标志 */
static u32 g_ul_event_flag = false;

extern BSP_S32 socp_init(void);
extern SOCP_GBL_STATE g_strSocpStat;

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

#define TAG()\
{\
    socp_printf("%s(%d)\n", __FUNCTION__, __LINE__);\
}


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
    //BSP_U32                 TaskId;
    struct task_struct*    TaskId;
    BSP_U32                 u32DataLen;
    BSP_U32                 u32DataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eEncDebugEn;
    BSP_U32                 u32EncDstThrh;
}SOCP_ST_CASE_S;


typedef struct tagSOCP_ST_CASE_DECODER_S{
    BSP_U32                 bSrcSet;
    BSP_U32                 SrcCh;
    BSP_U32                 DstCh;
    BSP_U32		            u32DebugEn;
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eMode;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
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
    struct task_struct*     TaskId;
    BSP_U32                 u32sendDataLen;
    BSP_U32                 u32sendDataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
}SOCP_ST_CASE_DECODER_S;

static BSP_U8 g_socpRxdata[4096];
static BSP_U32 g_socpRxTotal[7] = {0};
static BSP_U32 g_socpRdTotal[25] = {0};
static BSP_U32 g_socpTxTotal[25] = {0};

static BSP_S32 SocpStSetEncDst(SOCP_ST_CASE_S *pCase)
{
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    if(!pCase->bDstSet)
    {
        BSP_U8 *p;

//        p = (BSP_U8*)memalign(8, pCase->u32OutputSize);
        //p = (BSP_U8*)cacheDmaMalloc(pCase->u32OutputSize);
        //p = kmalloc(pCase->u32OutputSize, GFP_KERNEL);

        p = (BSP_U8*)TM_socp_malloc(pCase->u32OutputSize);

        socp_printf("kmalloc succussed 0x%x\n", (u32)p);

        if(BSP_NULL == p)
        {
            socp_printf("%s[%d] SET ENC DST FAILED!\n", __FUNCTION__, __LINE__);
            return BSP_ERROR;
        }
        pCase->u32OutputStart = (uintptr_t)p;
        g_pSocpBuf[g_SocpBufCnt++] = p;

        EncDstAttr.sCoderSetDstBuf.pucOutputStart = SOCP_VIRT_TO_PHYS(p);
        EncDstAttr.sCoderSetDstBuf.pucOutputEnd = SOCP_VIRT_TO_PHYS(p) + pCase->u32OutputSize - 1;
        EncDstAttr.sCoderSetDstBuf.u32Threshold = pCase->u32Threshold;
        EncDstAttr.u32EncDstThrh = pCase->u32EncDstThrh;

        g_socpRxTotal[pCase->DstCh&0xf] = 0;

        //CHECK_RET(bsp_socp_coder_set_dest_chan_attr(pCase->DstCh, &EncDstAttr), BSP_OK);
        if(BSP_OK != bsp_socp_coder_set_dest_chan_attr(pCase->DstCh, &EncDstAttr))
        {
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
            socp_printf("set enc dst channel failed!\n");

            return BSP_ERROR;
        }
        pCase->bDstSet = BSP_TRUE;

        return BSP_OK;
    }
    else
    {
        socp_printf("set enc dst channel failed, the channel has been set!\n");
        return BSP_ERROR;
    }
}

static BSP_S32 SocpStSetDecSrc(SOCP_ST_CASE_DECODER_S *pCase)
{
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;

    if(!pCase->bSrcSet)
    {
        BSP_U8 *p;

        //p = (BSP_U8*)cacheDmaMalloc(pCase->u32InputSize);
        //p = kmalloc(pCase->u32OutputSize, GFP_KERNEL);

        p = TM_socp_malloc(pCase->u32OutputSize);
        if(BSP_NULL == p)
        {
            socp_printf("%s[%d] SET DEC SRC FAILED!\n", __FUNCTION__, __LINE__);
            return BSP_ERROR;
        }
        g_pSocpBuf[g_SocpBufCnt++] = p;
        pCase->u32InputStart= (uintptr_t)p;

        DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = SOCP_VIRT_TO_PHYS(p);
        DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = SOCP_VIRT_TO_PHYS(p) + pCase->u32InputSize- 1;
        DecSrcAttr.eMode = pCase->eMode;
        DecSrcAttr.eDataTypeEn= pCase->eDataTypeEn;

        if(BSP_OK != bsp_socp_decoder_set_src_chan_attr(pCase->SrcCh, &DecSrcAttr))
        {
            socp_printf(" the dec src channel has been set failed\n");
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        }
        pCase->bSrcSet = BSP_TRUE;
    }

    return 0;
}


static BSP_S32 SocpStAllocDecDst(SOCP_ST_CASE_DECODER_S *pCase)
{
    SOCP_DECODER_DEST_CHAN_STRU DecDstAttr;
    BSP_U8 *p;

    //p = (BSP_U8*)cacheDmaMalloc(pCase->u32OutputSize);
    //p = kmalloc(pCase->u32OutputSize, GFP_KERNEL);
    p =(BSP_U8*)TM_socp_malloc(pCase->u32OutputSize);

    if(BSP_NULL == p)
    {
        socp_printf("%s[%d] ALLOC DEC DST FAILED!\n", __FUNCTION__, __LINE__);
        return BSP_ERROR;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;
    pCase->u32OutputStart = (uintptr_t)p;

    DecDstAttr.eDataType = pCase->eDataType;
    DecDstAttr.u32SrcChanID = pCase->SrcCh;
    DecDstAttr.sDecoderDstSetBuf.pucOutputStart = SOCP_VIRT_TO_PHYS(p);
    DecDstAttr.sDecoderDstSetBuf.pucOutputEnd = SOCP_VIRT_TO_PHYS(p) + pCase->u32OutputSize - 1;
    DecDstAttr.sDecoderDstSetBuf.u32Threshold = pCase->u32Threshold;

    if(BSP_OK != bsp_socp_decoder_set_dest_chan(pCase->DstCh, &DecDstAttr))
    {
        socp_printf(" the dec dst channel has been allocated failed\n");
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    return 0;
}

static BSP_S32 SocpStAllocEncSrc(SOCP_ST_CASE_S *pCase)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U8 *p;
    BSP_U8 *pRd = 0;

    p = (BSP_U8*)TM_socp_malloc(pCase->u32OutputSize);

    if(BSP_NULL == p)
    {
        socp_printf("%s[%d] ALLOC ENC SRC FAILED!\n", __FUNCTION__, __LINE__);
        return BSP_ERROR;
    }
    pCase->u32InputStart = (uintptr_t)p;
    g_pSocpBuf[g_SocpBufCnt++] = p;

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        pRd = (BSP_U8*)TM_socp_malloc(pCase->u32RDSize);
        if(BSP_NULL == pRd)
        {
            socp_printf("%s[%d] ALLOC ENC SRC RD BUF FAILED!\n", __FUNCTION__, __LINE__);
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
            return BSP_ERROR;
        }
        pCase->u32RDStart = (uintptr_t)pRd;
        g_pSocpBuf[g_SocpBufCnt++] = pRd;
    }

    pCase->u32InputStart = (uintptr_t)p;
    EncSrcAttr.eDataType = pCase->eDataType;
    EncSrcAttr.eDataTypeEn = pCase->eDataTypeEn;
    EncSrcAttr.eDebugEn = pCase->eEncDebugEn;
    EncSrcAttr.eMode = pCase->eMode;
    EncSrcAttr.ePriority = pCase->ePriority;
    EncSrcAttr.u32BypassEn = pCase->u32BypassEn;
    EncSrcAttr.u32DestChanID = pCase->DstCh;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = SOCP_VIRT_TO_PHYS(p);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = SOCP_VIRT_TO_PHYS(p) + pCase->u32InputSize - 1;
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        EncSrcAttr.sCoderSetSrcBuf.pucRDStart = SOCP_VIRT_TO_PHYS(pRd);
        EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = SOCP_VIRT_TO_PHYS(pRd) + pCase->u32RDSize - 1;
        EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = pCase->u32Threshold;
    }

    if(BSP_OK != bsp_socp_coder_set_src_chan(pCase->SrcCh, &EncSrcAttr))
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

        socp_printf("alloc enc src channel failed!\n");

        return BSP_ERROR;
    }

    return 0;
}

static BSP_S32 SocpStEventCB_1(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
{
    BSP_U32 u32ChanType =  SOCP_REAL_CHAN_TYPE(u32ChanID);
    BSP_U32 u32ChanId   =  SOCP_REAL_CHAN_ID(u32ChanID);

    g_ul_event_flag = true;

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
        case SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW:
        {
            socp_printf("chan type is [%d], id is [%d], event is outbuffer threshold overflow error!\n", u32ChanType, u32ChanId);
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
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("func: SocpStReadCB_1: chan[%d] get data len=[%d]\n", u32ChanID&0xff, len);
#if 1
    if(Buffer.pBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
        memcpy(g_socpRxdata, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
        memcpy(g_socpRxdata+Buffer.u32Size, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
    }

    for(i=0; i<(int)len; i++)
    {
        socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            socp_printf("\n");
    }
    socp_printf(" the chan id is %d\n",u32ChanID&0xff);
#endif
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_S32 SocpStReadCB_2(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i, c;
    static BSP_BOOL flag = BSP_TRUE;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);

    c = u32ChanID&0xf;
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[c] += len;
    socp_printf("func: SocpStReadCB_2: c[%d] get data R=%d T=%d\n", u32ChanID&0xff, len, g_socpRxTotal[c]);
#if 1
    if(Buffer.pBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
        memcpy(g_socpRxdata, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
        memcpy(g_socpRxdata+Buffer.u32Size, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
    }

    if(flag)
    {
        for(i=0; i<(int)len; i++)
        {
            socp_printf("0x%02x ", g_socpRxdata[i]);
            if(i && (0 == i%8))
                socp_printf("\n");
        }
        flag = BSP_FALSE;
    }
#endif
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_S32 SocpStReadCB_3(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int chan;

    chan = u32ChanID&0xff;
    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[chan] += len;
    socp_printf("func: SocpStReadCB_3: chan[%d] get data R=%d T=%d\n", chan, len, g_socpRxTotal[chan]);
#if 0
    if(Buffer.pBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
        memcpy(g_socpRxdata, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
        memcpy(g_socpRxdata+ Buffer.u32Size, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
    }
#endif
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}



static BSP_S32 SocpStReadCB_4(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("func: SocpStReadCB_4: chan[%x] get data len=[%d]\n", u32ChanID, len);

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_U32 rCnt = 0;
static BSP_S32 SocpStReadCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int chan;

    chan = u32ChanID&0xff;
    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[chan] += len;
    //socp_printf("chan[%d] R=%d T=%d\n", chan, len, g_socpRxTotal[chan]);
    if(Buffer.pBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
        memcpy(g_socpRxdata, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
        memcpy(g_socpRxdata+Buffer.u32Size, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
    }

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    rCnt++;
    if(999 == rCnt%1000)
    {
        socp_printf("read cnt is %d\n",rCnt);
    }
    if(rCnt >0xFFFFFFF0)
    {
        rCnt = 0;
    }

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_U32 g_socpRDdata[8];

static BSP_S32 SocpStRdCB_1(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);
    //g_socpRDdata[0] = (BSP_U32)&Buffer;
    //g_socpRDdata[1] = len;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

//    socp_printf("chan[%d] read RD done!\n", u32ChanID);

    return 0;
}

static BSP_S32 SocpStRdCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    //socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);
    g_socpRDdata[0] = (uintptr_t)&Buffer;
    g_socpRDdata[1] = len;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

//    socp_printf("chan[%d] read RD done!\n", u32ChanID);

    return 0;
}


static BSP_S32 SocpStReadCB_6(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("chan[%d] get data len=[%d]\n", u32ChanID&0xff, len);
    if(Buffer.pBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
        memcpy(g_socpRxdata, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pBuffer), Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        SOCP_TEST_INVALID_CACHE(SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
        memcpy(g_socpRxdata+Buffer.u32Size, (BSP_U8*)SOCP_PHYS_TO_VIRT(Buffer.pRbBuffer), Buffer.u32RbSize);
    }

    for(i=0; i<(int)len; i++)
    {
        socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            socp_printf("\n");
    }
    //socp_printf(" the chan id is %d\n",u32ChanID);

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_U32 rDecCnt = 0;
static BSP_S32 SocpStReadCB_Dec_Stress(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    rDecCnt++;
    if(9999 == rDecCnt%10000)
    {
        socp_printf("decoder read cnt is %d\n",rDecCnt);
    }
    if(rDecCnt >0xFFFFFFF0)
    {
        rDecCnt = 0;
    }

    return 0;
}

static SOCP_ST_CASE_S g_stCase[31] =
{
    {
        // 0
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 1
        0, 1, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 1024, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 100,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 2
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 4, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 3
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 580, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 4, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 4
        0, 0, SOCP_CODER_DEST_CHAN_0, 1, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 5
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_1, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 6
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 100, 5, 0, 0x1000, 100, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 96, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 7
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x100, 2, SocpStEventCB_1, SocpStReadCB_4, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 8
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x100, 0, 0x40, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 64, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 9
        0, 2, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 10
        0, 3, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 11
        0, 0, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 12
        0, 0, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 13
        0, 0, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 14
        0, 0, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 15
        0, 9, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 16
        0, 10, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 17
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 1024, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 512, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 18
        0, 1, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 2048, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 512, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 19
        0, 2, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 4096, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 20
        0, 3, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 21
        0, 9, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 22
        0, 10, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 40, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 23
        0, SOCP_BBPLOG_CHN, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x2000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 4, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 24
        0, SOCP_DSPLOG_CHN, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x2000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 16, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 25
        0, SOCP_BBPDS_CHN, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x2000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_EN,
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
    {
        // 30
        0, 0, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x100, 2, SocpStEventCB_1, SocpStReadCB_4, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN, SOCP_ENC_DEBUG_EN, 50
    },
};

static SOCP_ST_CASE_DECODER_S g_stDecCase[17] =
{
    {//0
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 64, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 120,SOCP_DATA_TYPE_EN
    },
    {//1  /* 计数本来是8000000，为了GTR测试通过，改为40000，下同*/
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 120, SOCP_DATA_TYPE_EN
    },
    {//2
        0, SOCP_DECODER_SRC_CHAN_1, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 120, SOCP_DATA_TYPE_EN
    },
    {//3
        0, SOCP_DECODER_SRC_CHAN_2, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 120, SOCP_DATA_TYPE_EN
    },
    {//4
        0, SOCP_DECODER_SRC_CHAN_3, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 120, SOCP_DATA_TYPE_EN
    },
    {//5
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 32, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 29, 24, SOCP_DATA_TYPE_EN
    },
    {//6
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0x1000, 0, 0x100, 64, 0, 0x1000, 16, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 29, 32, SOCP_DATA_TYPE_EN
    },
    {//7
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0x1000, 0, 0x100, 64, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 29, 1, SOCP_DATA_TYPE_EN
    },
    {//8
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0x1000, 0, 0x100, 64, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 6, 100, SOCP_DATA_TYPE_EN
    },
    {//9
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0x2000, 0, 0x100, 64, 0, 0x2000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 2045, 2, SOCP_DATA_TYPE_EN
    },
    {//10
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_1,
        0, 0x1000, 0, 0x100, 64, 0, 0x1000, 16, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 16, 32, SOCP_DATA_TYPE_EN
    },
    {//11
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0x1000, 0, 0x100, 64, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 64, 10, SOCP_DATA_TYPE_EN
    },
    {//12  /* 以下压力测试专用 */
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_Dec_Stress, SocpStRdCB_1, 0, 116, 120, SOCP_DATA_TYPE_EN
    },
    {//13
        0, SOCP_DECODER_SRC_CHAN_1, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_Dec_Stress, SocpStRdCB_1, 0, 116, 120, SOCP_DATA_TYPE_EN
    },
    {//14
        0, SOCP_DECODER_SRC_CHAN_2, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_Dec_Stress, SocpStRdCB_1, 0, 116, 120, SOCP_DATA_TYPE_EN
    },
    {//15
        0, SOCP_DECODER_SRC_CHAN_3, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 200, SocpStEventCB_1, SocpStReadCB_Dec_Stress, SocpStRdCB_1, 0, 116, 120, SOCP_DATA_TYPE_EN
    },
    {//16
        0, SOCP_DECODER_SRC_CHAN_0, SOCP_DECODER_DEST_CHAN_0, 0, SOCP_DECSRC_CHNMODE_BYTES, SOCP_DATA_TYPE_0,
        0, 0xf000, 0, 0x100, 64, 0, 0x8000, 64, SocpStEventCB_1, SocpStReadCB_6, SocpStRdCB_1, 0, 28, 120,SOCP_DATA_TYPE_DIS
    },
};


static BSP_S32 SocpStInitChannel(SOCP_ST_CASE_S *pCase)
{
    BSP_U32 u32Ret;

    DEV_INIT();
    socp_printf("init\n");
    msleep(100);

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    u32Ret = SocpStAllocEncSrc(pCase);
    socp_printf("set enc src chnn chnn:%d\n",u32Ret);

    if(u32Ret != BSP_OK)
    {
        socp_printf("SocpStInitChannel: init enc src failed!\n");
        return BSP_ERROR;

    }
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    return BSP_OK;
}

static BSP_S32 SocpStInitDecChannel(SOCP_ST_CASE_DECODER_S *pCase)
{
    DEV_INIT();

    CHECK_RET(SocpStAllocDecDst(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->DstCh, pCase->EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);

    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    return BSP_OK;
}


static BSP_VOID SocpStGenPayLoad(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 ulTime = 0;
    BSP_U32 ulTime1 = 0;
    SOCP_PACKET_HEAD_S * pstSocpPackt = (SOCP_PACKET_HEAD_S*)pBuff;
    int i;

    /* 组包SOCP */
    ulTime                           = 0x08070605;
    ulTime1                           = 0x0d0c0b0a;
    pstSocpPackt->usSId              = 1;
    pstSocpPackt->usSSId             = 2;
    pstSocpPackt->ucServiceSessionId = 3;
    pstSocpPackt->ucMsgType          = 4;
    memcpy(pstSocpPackt->aucTimeData, &ulTime, 4);
    memcpy(pstSocpPackt->aucTimeData + 4, &ulTime1, 4);
    pstSocpPackt->ulMsgTransId = 100;
    //pBuff += 16;
    for(i=16; i<(int)u32DataLen; i++)
    {
        //pBuff[i] = i%0xff;
        pBuff[i] = 0xA5;
    }

    return;
}

static BSP_VOID SocpStGenPayLoad2(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 ulTime = 0;
    BSP_U32 ulTime1 = 0;
    SOCP_PACKET_HEAD_S * pstSocpPackt = (SOCP_PACKET_HEAD_S*)pBuff;
    int i;

    /* 组包SOCP */
    ulTime                           = 0x01010101;
    ulTime1                           = 0x02020202;
    pstSocpPackt->usSId              = 3;
    pstSocpPackt->usSSId             = 3;
    pstSocpPackt->ucServiceSessionId = 3;
    pstSocpPackt->ucMsgType          = 3;
    memcpy(pstSocpPackt->aucTimeData, &ulTime, 4);
    memcpy(pstSocpPackt->aucTimeData + 4, &ulTime1, 4);
    pstSocpPackt->ulMsgTransId = 200;
    //pBuff += 16;
    for(i=16; i<(int)u32DataLen; i++)
    {
        pBuff[i] = i+0xf;
    }

    return;
}

static BSP_VOID SocpStGenPkt(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    pBuff[0] = 0x49;
    pBuff[1] = 0x53;
    pBuff[2] = 0x49;
    pBuff[3] = 0x48;
    /*
    pBuff[0] = 0x48;
    pBuff[1] = 0x49;
    pBuff[2] = 0x53;
    pBuff[3] = 0x49;
    */
    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;
    //pBuff += 8;

    //SocpStGenPayLoad((pBuff+8), u32DataLen-16);
    SocpStGenPayLoad((pBuff+8), u32DataLen);

    return;
}


static BSP_VOID SocpStGenPkt1(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    pBuff[0] = 0x49;
    pBuff[1] = 0x53;
    pBuff[2] = 0x49;
    pBuff[3] = 0x48;
    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;
    //pBuff += 8;

    SocpStGenPayLoad2((pBuff+8), u32DataLen-16);

    return;
}


static BSP_VOID SocpStGenBD1(BSP_U32 *pBD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    pBD[0] = (uintptr_t)pBuff;
    pBD[1] = 0;
    pBD[1] |= (0xffff & u32DataLen);

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
    //packet = (BSP_U8*)kmalloc(len,GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    socp_printf("packet %p, len %d\n", packet, pCase->u32DataLen);
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(cnt)
    {

        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(20);
        }

        if(vfcnt > 50)
        {
            break;
        }
        msleep(1);
    }

    msleep(100);
    socp_printf("enc over cnt %d\n",cnt);

    //socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);
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

    //socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = kmalloc(len, GFP_KERNEL|GFP_DMA);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= 8)
        {
            if(WtBuff.u32Size >= 8)
            {
                memcpy(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), bd, 8);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), 8);
            }
            else
            {
                memcpy(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), bd, WtBuff.u32Size);
                memcpy(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), bd+WtBuff.u32Size, 8-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), 8 - WtBuff.u32Size);
            }
            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, 8), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
        msleep(0);
    }

    msleep(100);
    //kfree(packet);
    TM_socp_free(packet);
    //socp_free(SOCP_VIRT_PHY(packet));

    socp_printf("cnt is %d, chan[%d] write done! totol=0x%x size=0x%x\n", cnt, pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


static BSP_S32 socp_encode_task013(BSP_VOID *param)
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

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenPkt1(packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
        msleep(0);
    }

    msleep(100);
    //kfree(packet);
    TM_socp_free(packet);

    //socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


static BSP_U8 g_StdDecSrcT0[29] = {0x7e, 0x00, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0xe1, 0x1e, 0x7e};
static BSP_U8 g_StdDecSrcT1[29] = {0x7e, 0x01, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x9a, 0x1a, 0x7e};
static BSP_U8 g_StdDecSrcT2[29] = {0x7e, 0x02, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x17, 0x16, 0x7e};
static BSP_U8 g_StdDecSrcT3[29] = {0x7e, 0x03, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x6c, 0x12, 0x7e};

static BSP_S32 socp_decode_task001(BSP_VOID *param)
{
    SOCP_ST_CASE_DECODER_S *pCase = (SOCP_ST_CASE_DECODER_S*)param;
    int cnt = pCase->u32sendDataCnt;
    int len = pCase->u32sendDataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);

    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        socp_printf("0x%x, 0x%x, 0x%x ,0x%p\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt, WtBuff.pBuffer);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    //kfree(packet);
    TM_socp_free(packet);
    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


static BSP_S32 socp_decode_task011(BSP_VOID *param)
{
    SOCP_ST_CASE_DECODER_S *pCase = (SOCP_ST_CASE_DECODER_S*)param;
    int cnt;
    int len = pCase->u32sendDataLen;
    BSP_U8  *packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;
    cnt = (pCase->u32sendDataCnt)/4;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    //memcpy(packet, g_StdMinDecSrcT0, len);
    memcpy(packet, g_StdDecSrcT0, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    msleep(100);

    memcpy(packet, g_StdDecSrcT1, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    msleep(100);

    memcpy(packet, g_StdDecSrcT2, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    msleep(100);

    memcpy(packet, g_StdDecSrcT3, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), len);
            }
            else
            {
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), WtBuff.u32Size);
                SOCP_TEST_FLUSH_CACHE(SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), len-WtBuff.u32Size);
            }

            CHECK_RET(bsp_socp_write_done(pCase->SrcCh, len), BSP_OK);
            cnt--;
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(2);
        }

        if(vfcnt > 50)
        {
            break;
        }
    }
    msleep(2);
    //kfree(packet);
    TM_socp_free(packet);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


/* 编码测试, APP CPU发APP CPU收，固定长度块式数据包 */
BSP_S32 SOCP_ST_ENCODE_001_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;

    g_stCase[0].SrcCh = SOCP_CODER_SRC_LDSP2;
    g_stCase[0].DstCh = SOCP_CODER_DEST_CHAN_4;

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);
    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 2000), BSP_OK);

    sprintf(taskName,"socpTest%02d",1);

    g_stCase[0].TaskId = kthread_run(socp_encode_task001, (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		socp_printf("create kthread socp_enccode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

/* 编码测试, APP CPU发APP CPU收，固定长度块式数据包，关闭任务 */
BSP_S32 SOCP_ST_ENCODE_001_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);      /* 任务中打包所用内存 */

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);      /* 编码源块数据内存*/
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);  /* 编码RD buffer内存 */
    }
    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);  /* 编码目的通道内存 */
        g_stCase[0].bDstSet = FALSE;
    }

    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    if(false == g_ul_rev_pkt_flag)
    {
        return BSP_ERROR;
    }

    return 0;
}



/* 编码测试, MODEM CPU发APP CPU收，固定长度块式数据包 */
BSP_S32 SOCP_ST_ENCODE_006_START(void)
{
    g_ul_rev_pkt_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(&g_stCase[0]), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(g_stCase[0].DstCh, g_stCase[0].ReadCb), BSP_OK);

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_006_STOP(void)
{
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);
    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 编码测试, APP CPU发APP CPU收, 测试阈值中断 */
BSP_S32 SOCP_ST_ENCODE_009_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[3]), BSP_OK);

    sprintf(taskName,"socpTest%02d",9);

    g_stCase[3].TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(&g_stCase[3]), taskName);
    if(IS_ERR(g_stCase[3].TaskId))
    {
		socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_009_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[3].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[3].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[3].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[3].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[3].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[3].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[3].TaskId)
    {
    	//kthread_stop(g_stCase[3].TaskId);
        g_stCase[3].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 编码测试, APP CPU发APP CPU收, 测试超时中断 */
BSP_S32 SOCP_ST_ENCODE_010_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;
    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[2]), BSP_OK);

    sprintf(taskName,"socpTest%02d",10);

    g_stCase[2].TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(&g_stCase[2]), taskName);
    if(IS_ERR(g_stCase[2].TaskId))
    {
		socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_010_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[2].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[2].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[2].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[2].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[2].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[2].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[2].TaskId)
    {
    	//kthread_stop(g_stCase[2].TaskId);
        g_stCase[2].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 编码测试 ,测试目的buffer 溢出中断*/
BSP_S32 SOCP_ST_ENCODE_017_START(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase = &g_stCase[7];
    BSP_U32 u32Ret;


    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    u32Ret = SocpStAllocEncSrc(pCase);
    if(u32Ret != 0)
    {
        return u32Ret;
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->DstCh, pCase->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, BSP_NULL), BSP_OK);
    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_ENABLE, 2), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    sprintf(taskName,"socpTest%02d",10);

    pCase->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase), taskName);
    if(IS_ERR(pCase->TaskId))
    {
		socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_017_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[7].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[7].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[7].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stCase[7].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[7].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[7].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[7].TaskId)
    {
    	//kthread_stop(g_stCase[7].TaskId);
        g_stCase[7].TaskId = NULL;
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


static BSP_BOOL bTestEncode19 = BSP_FALSE;
/* 编码测试，多通道测试 , 多输入，多输出*/
BSP_S32 SOCP_ST_ENCODE_019_START(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase0 = &g_stCase[0];
    SOCP_ST_CASE_S *pCase1 = &g_stCase[1];
    SOCP_ST_CASE_S *pCase2 = &g_stCase[9];
    SOCP_ST_CASE_S *pCase3 = &g_stCase[10];

    DEV_INIT();

    if(BSP_FALSE == bTestEncode19)
    {
        pCase0->RdCb = SocpStRdCB_19;
        pCase1->RdCb = SocpStRdCB_19;
        pCase2->RdCb = SocpStRdCB_19;
        pCase3->RdCb = SocpStRdCB_19;

        pCase0->ReadCb = SocpStReadCB_19;
        pCase1->ReadCb = SocpStReadCB_19;
        pCase2->ReadCb = SocpStReadCB_19;
        pCase3->ReadCb = SocpStReadCB_19;

        CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
        CHECK_RET(SocpStSetEncDst(pCase0), BSP_OK);
        CHECK_RET(SocpStSetEncDst(pCase2), BSP_OK);
        CHECK_RET(SocpStAllocEncSrc(pCase0), BSP_OK);
        CHECK_RET(SocpStAllocEncSrc(pCase1), BSP_OK);
        CHECK_RET(SocpStAllocEncSrc(pCase2), BSP_OK);
        CHECK_RET(SocpStAllocEncSrc(pCase3), BSP_OK);
        CHECK_RET(bsp_socp_register_event_cb(pCase0->SrcCh, pCase0->EventCb), BSP_OK);
        if(pCase0->eMode == SOCP_ENCSRC_CHNMODE_LIST)
        {
            CHECK_RET(bsp_socp_register_rd_cb(pCase0->SrcCh, pCase0->RdCb), BSP_OK);
        }
        CHECK_RET(bsp_socp_register_event_cb(pCase1->SrcCh, pCase1->EventCb), BSP_OK);
        if(pCase1->eMode == SOCP_ENCSRC_CHNMODE_LIST)
        {
            CHECK_RET(bsp_socp_register_rd_cb(pCase1->SrcCh, pCase1->RdCb), BSP_OK);
        }
        CHECK_RET(bsp_socp_register_event_cb(pCase2->SrcCh, pCase2->EventCb), BSP_OK);
        if(pCase2->eMode == SOCP_ENCSRC_CHNMODE_LIST)
        {
            CHECK_RET(bsp_socp_register_rd_cb(pCase2->SrcCh, pCase2->RdCb), BSP_OK);
        }
        CHECK_RET(bsp_socp_register_event_cb(pCase3->SrcCh, pCase3->EventCb), BSP_OK);
        if(pCase3->eMode == SOCP_ENCSRC_CHNMODE_LIST)
        {
            CHECK_RET(bsp_socp_register_rd_cb(pCase3->SrcCh, pCase3->RdCb), BSP_OK);
        }
        CHECK_RET(bsp_socp_register_event_cb(pCase0->DstCh, pCase0->EventCb), BSP_OK);
        CHECK_RET(bsp_socp_register_event_cb(pCase2->DstCh, pCase2->EventCb), BSP_OK);
        CHECK_RET(bsp_socp_register_read_cb(pCase0->DstCh, SocpStReadCB_3), BSP_OK);
        CHECK_RET(bsp_socp_register_read_cb(pCase2->DstCh, SocpStReadCB_3), BSP_OK);
        CHECK_RET(bsp_socp_start(pCase0->SrcCh), BSP_OK);
        CHECK_RET(bsp_socp_start(pCase1->SrcCh), BSP_OK);
        CHECK_RET(bsp_socp_start(pCase2->SrcCh), BSP_OK);
        CHECK_RET(bsp_socp_start(pCase3->SrcCh), BSP_OK);

        bTestEncode19 = BSP_TRUE;
    }

    sprintf(taskName,"socpTest%03d",190);
    pCase0->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase0), taskName);
    if(IS_ERR(pCase0->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",191);
    pCase1->TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(pCase1), taskName);
    if(IS_ERR(pCase1->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",192);

    pCase2->TaskId = kthread_run(socp_encode_task013,  (BSP_VOID*)(pCase2), taskName);
    if(IS_ERR(pCase2->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",193);
    pCase3->TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(pCase3), taskName);
    if(IS_ERR(pCase3->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_019_STOP(void)
{
    BSP_U32 i = 0;

    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[10].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[10].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[9].DstCh), BSP_OK);

    for(i=0;i<4;i++)
    {
        //kfree(g_pSocpBuf[--g_SocpBufCnt]);

        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    if(g_stCase[1].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    if(g_stCase[10].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }
    if(g_stCase[9].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[9].bDstSet = FALSE;
    }

    /*释放任务*/
	if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
    }
    if(g_stCase[1].TaskId)
    {
    	//kthread_stop(g_stCase[1].TaskId);
    }
    if(g_stCase[9].TaskId)
    {
        //kthread_stop(g_stCase[9].TaskId);
    }
    if(g_stCase[10].TaskId)
    {
        //kthread_stop(g_stCase[10].TaskId);
    }

    return 0;
}

/* 编码测试 , 双核多通道测试*/
BSP_S32 SOCP_ST_ENCODE_020_START(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase0 = &g_stCase[15];
    SOCP_ST_CASE_S *pCase1 = &g_stCase[16];
    SOCP_ST_CASE_S *pCase2 = &g_stCase[9];
    SOCP_ST_CASE_S *pCase3 = &g_stCase[10];
    SOCP_ST_CASE_S *pCase4 = &g_stCase[11];
    //SOCP_ST_CASE_S *pCase5 = &g_stCase[12];
    SOCP_ST_CASE_S *pCase6 = &g_stCase[13];
    //SOCP_ST_CASE_S *pCase7 = &g_stCase[14];

    DEV_INIT();
    memset(g_socpRdTotal, 0, sizeof(g_socpRdTotal));
    memset(g_socpRxTotal, 0, sizeof(g_socpRxTotal));
    memset(g_socpTxTotal, 0, sizeof(g_socpTxTotal));

    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase2), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase4), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase6), BSP_OK);

    CHECK_RET(SocpStAllocEncSrc(pCase0), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase1), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase2), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase3), BSP_OK);
    socp_printf("0x%x 0x%x 0x%x 0x%x\n",pCase0->SrcCh,pCase1->SrcCh,pCase2->SrcCh,pCase3->SrcCh);
    CHECK_RET(bsp_socp_register_event_cb(pCase0->SrcCh, pCase0->EventCb), BSP_OK);
    if(pCase0->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase0->SrcCh, pCase0->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase1->SrcCh, pCase1->EventCb), BSP_OK);
    if(pCase1->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase1->SrcCh, pCase1->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase2->SrcCh, pCase2->EventCb), BSP_OK);
    if(pCase2->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase2->SrcCh, pCase2->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase3->SrcCh, pCase3->EventCb), BSP_OK);
    if(pCase3->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase3->SrcCh, pCase3->RdCb), BSP_OK);
    }

    CHECK_RET(bsp_socp_register_event_cb(pCase0->DstCh, pCase0->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase2->DstCh, pCase2->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase4->DstCh, pCase4->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase6->DstCh, pCase6->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase0->DstCh, SocpStReadCB_3), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase2->DstCh, SocpStReadCB_3), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase4->DstCh, SocpStReadCB_3), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase6->DstCh, SocpStReadCB_3), BSP_OK);

    CHECK_RET(bsp_socp_start(pCase0->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase1->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase2->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase3->SrcCh), BSP_OK);

    sprintf(taskName,"socpTest%03d",200);
    pCase0->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase0), taskName);
    if(IS_ERR(pCase0->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",201);
    pCase1->TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(pCase1), taskName);
    if(IS_ERR(pCase1->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",202);

    pCase2->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase2), taskName);
    if(IS_ERR(pCase2->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",203);
    pCase3->TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(pCase3), taskName);
    if(IS_ERR(pCase3->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_020_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[10].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[10].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[15].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[15].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[16].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[16].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[9].DstCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[11].DstCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[13].DstCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[15].DstCh), BSP_OK);

    // pCase0
    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[15].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    // pCase1
    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[16].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    // pCase2
    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[9].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    // pCase3
    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[10].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    /*释放申请的内存*/
    if(g_stCase[9].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[9].bDstSet = FALSE;
    }
    if(g_stCase[11].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[11].bDstSet = FALSE;
    }
    if(g_stCase[13].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[13].bDstSet = FALSE;
    }
    if(g_stCase[15].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[15].bDstSet = FALSE;
    }

    if(g_stCase[15].TaskId)
    {
        //kthread_stop(g_stCase[15].TaskId);
    }
    if(g_stCase[16].TaskId)
    {
        //kthread_stop(g_stCase[16].TaskId);
    }
    if(g_stCase[9].TaskId)
    {
        //kthread_stop(g_stCase[9].TaskId);
    }
    if(g_stCase[10].TaskId)
    {
        //kthread_stop(g_stCase[10].TaskId);
    }

    return 0;
}

/* 编码测试 ,测试目的buffer 仲裁阈值溢出中断*/
BSP_S32 SOCP_ST_ENCODE_021_START(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase = &g_stCase[30];
    BSP_U32 u32Ret;

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    u32Ret = SocpStAllocEncSrc(pCase);
    if(u32Ret != 0)
    {
        return u32Ret;
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->DstCh, pCase->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_ENABLE, 2), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    sprintf(taskName,"socpTest%03d",210);
    pCase->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase), taskName);

    if(IS_ERR(pCase->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;

}

BSP_S32 SOCP_ST_ENCODE_021_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[30].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[30].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[30].DstCh), BSP_OK);

    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[30].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    if(g_stCase[30].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[30].bDstSet = FALSE;
    }

    if(g_stCase[30].TaskId)
    {
        //(BSP_VOID)kthread_stop(g_stCase[30].TaskId);
    }

    return 0;
}


/* 解码通路 测试 */
BSP_S32 SOCP_ST_DECODE_001_START(void)
{
    char taskName[30] = {0};
    DEV_INIT();
    msleep(50);

    g_ul_rev_pkt_flag = false;

    g_stDecCase[0].u32sendDataCnt = 64;
    g_stDecCase[0].u32Threshold = 32;
    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",1);
    g_stDecCase[0].TaskId = kthread_run(socp_decode_task001,  (&g_stDecCase[0]), taskName);
    if(IS_ERR(g_stDecCase[0].TaskId))
    {
		socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_001_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[0].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[0].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[0].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[0].bSrcSet = FALSE;
    }
        /*释放任务*/
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stDecCase[0].TaskId)
    {
    	//kthread_stop(g_stDecCase[0].TaskId);
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


static BSP_U32 u32DecDstId[16];

/* 解码测试四对十六 */
BSP_S32 SOCP_ST_DECODE_014_START(void)
{
    char taskName[30] = {0};

    SOCP_DEC_PKTLGTH_STRU pPktlgth = {0,0};

    SOCP_ST_CASE_DECODER_S *pCaseDec0 = &g_stDecCase[1];
    SOCP_ST_CASE_DECODER_S  pCaseDec1 = g_stDecCase[1];
    SOCP_ST_CASE_DECODER_S  pCaseDec2 = g_stDecCase[1];
    SOCP_ST_CASE_DECODER_S  pCaseDec3 = g_stDecCase[1];

    SOCP_ST_CASE_DECODER_S *pCaseDec4 = &g_stDecCase[2];
    SOCP_ST_CASE_DECODER_S  pCaseDec5 = g_stDecCase[2];
    SOCP_ST_CASE_DECODER_S  pCaseDec6 = g_stDecCase[2];
    SOCP_ST_CASE_DECODER_S  pCaseDec7 = g_stDecCase[2];

    SOCP_ST_CASE_DECODER_S *pCaseDec8 = &g_stDecCase[3];
    SOCP_ST_CASE_DECODER_S  pCaseDec9 = g_stDecCase[3];
    SOCP_ST_CASE_DECODER_S  pCaseDeca = g_stDecCase[3];
    SOCP_ST_CASE_DECODER_S  pCaseDecb = g_stDecCase[3];

    SOCP_ST_CASE_DECODER_S *pCaseDecc = &g_stDecCase[4];
    SOCP_ST_CASE_DECODER_S  pCaseDecd = g_stDecCase[4];
    SOCP_ST_CASE_DECODER_S  pCaseDece = g_stDecCase[4];
    SOCP_ST_CASE_DECODER_S  pCaseDecf = g_stDecCase[4];

    pPktlgth.u32PktMax = 1024;
    pPktlgth.u32PktMin = 0;


    DEV_INIT();

    memset(u32DecDstId, 0, sizeof(BSP_U32)*16);

    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
    bsp_socp_set_dec_pkt_lgth(&pPktlgth);
    CHECK_RET(SocpStSetDecSrc(pCaseDec0), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec0->SrcCh, pCaseDec0->EventCb), BSP_OK);

    pCaseDec0->eDataType = SOCP_DATA_TYPE_0;
    CHECK_RET(SocpStAllocDecDst(pCaseDec0), BSP_OK);
    u32DecDstId[0] = pCaseDec0->DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec0->DstCh, pCaseDec0->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec0->DstCh, pCaseDec0->EventCb), BSP_OK);

    pCaseDec1.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec1.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 4);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec1), BSP_OK);
    u32DecDstId[1] = pCaseDec1.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec1.DstCh, pCaseDec1.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec1.DstCh, pCaseDec1.EventCb), BSP_OK);

    pCaseDec2.eDataType = SOCP_DATA_TYPE_2;
    pCaseDec2.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 8);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec2), BSP_OK);
    u32DecDstId[2] = pCaseDec2.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec2.DstCh, pCaseDec2.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec2.DstCh, pCaseDec2.EventCb), BSP_OK);

    pCaseDec3.eDataType = SOCP_DATA_TYPE_3;
    pCaseDec3.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 12);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec3), BSP_OK);
    u32DecDstId[3] = pCaseDec3.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec3.DstCh, pCaseDec3.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec3.DstCh, pCaseDec3.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDec4), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec4->SrcCh, pCaseDec4->EventCb), BSP_OK);

    pCaseDec4->eDataType = SOCP_DATA_TYPE_0;
    pCaseDec4->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 1);
    CHECK_RET(SocpStAllocDecDst(pCaseDec4), BSP_OK);
    u32DecDstId[4] = pCaseDec4->DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec4->DstCh, pCaseDec4->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec4->DstCh, pCaseDec4->EventCb), BSP_OK);

    pCaseDec5.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec5.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 5);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec5), BSP_OK);
    u32DecDstId[5] = pCaseDec5.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec5.DstCh, pCaseDec5.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec5.DstCh, pCaseDec5.EventCb), BSP_OK);

    pCaseDec6.eDataType = SOCP_DATA_TYPE_2;
    pCaseDec6.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 9);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec6), BSP_OK);
    u32DecDstId[6] = pCaseDec6.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec6.DstCh, pCaseDec6.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec6.DstCh, pCaseDec6.EventCb), BSP_OK);

    pCaseDec7.eDataType = SOCP_DATA_TYPE_3;
    pCaseDec7.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 13);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec7), BSP_OK);
    u32DecDstId[7] = pCaseDec7.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec7.DstCh, pCaseDec7.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec7.DstCh, pCaseDec7.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDec8), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec8->SrcCh, pCaseDec8->EventCb), BSP_OK);

    pCaseDec8->eDataType = SOCP_DATA_TYPE_0;
    pCaseDec8->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 2);
    CHECK_RET(SocpStAllocDecDst(pCaseDec8), BSP_OK);
    u32DecDstId[8] = pCaseDec8->DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec8->DstCh, pCaseDec8->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec8->DstCh, pCaseDec8->EventCb), BSP_OK);

    pCaseDec9.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec9.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 6);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec9), BSP_OK);
    u32DecDstId[9] = pCaseDec9.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec9.DstCh, pCaseDec9.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec9.DstCh, pCaseDec9.EventCb), BSP_OK);

    pCaseDeca.eDataType = SOCP_DATA_TYPE_2;
    pCaseDeca.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 10);
    CHECK_RET(SocpStAllocDecDst(&pCaseDeca), BSP_OK);
    u32DecDstId[10] = pCaseDeca.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDeca.DstCh, pCaseDeca.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDeca.DstCh, pCaseDeca.EventCb), BSP_OK);

    pCaseDecb.eDataType = SOCP_DATA_TYPE_3;
    pCaseDecb.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 14);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecb), BSP_OK);
    u32DecDstId[11] = pCaseDecb.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecb.DstCh, pCaseDecb.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecb.DstCh, pCaseDecb.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDecc), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecc->SrcCh, pCaseDecc->EventCb), BSP_OK);

    pCaseDecc->eDataType = SOCP_DATA_TYPE_0;
    pCaseDecc->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 3);
    CHECK_RET(SocpStAllocDecDst(pCaseDecc), BSP_OK);
    u32DecDstId[12] = pCaseDecc->DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecc->DstCh, pCaseDecc->ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecc->DstCh, pCaseDecc->EventCb), BSP_OK);

    pCaseDecd.eDataType = SOCP_DATA_TYPE_1;
    pCaseDecd.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 7);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecd), BSP_OK);
    u32DecDstId[13] = pCaseDecd.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecd.DstCh, pCaseDecd.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecd.DstCh, pCaseDecd.EventCb), BSP_OK);

    pCaseDece.eDataType = SOCP_DATA_TYPE_2;
    pCaseDece.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 11);
    CHECK_RET(SocpStAllocDecDst(&pCaseDece), BSP_OK);
    u32DecDstId[14] = pCaseDece.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDece.DstCh, pCaseDece.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDece.DstCh, pCaseDece.EventCb), BSP_OK);

    pCaseDecf.eDataType = SOCP_DATA_TYPE_3;
    pCaseDecf.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 15);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecf), BSP_OK);
    u32DecDstId[15] = pCaseDecf.DstCh;
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecf.DstCh, pCaseDecf.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecf.DstCh, pCaseDecf.EventCb), BSP_OK);

    sprintf(taskName,"socpTestDec014_1");
    pCaseDec0->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDec0), taskName);
    if(IS_ERR(pCaseDec0->TaskId))
    {
		socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_2");
    pCaseDec4->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDec4), taskName);
    if(IS_ERR(pCaseDec4->TaskId))
    {
		socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_3");
    pCaseDec8->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDec8), taskName);
    if(IS_ERR(pCaseDec8->TaskId))
    {
		socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_4");
    pCaseDecc->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDecc), taskName);
    if(IS_ERR(pCaseDecc->TaskId))
    {
		socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    CHECK_RET(bsp_socp_start(pCaseDec0->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDec4->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDec8->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDecc->SrcCh), BSP_OK);

    return BSP_OK;
}


BSP_S32 SOCP_ST_DECODE_014_STOP(void)
{
    BSP_U32 i = 0;

    /*停止通道*/
    for(i=1;i<5;i++)
    {
        CHECK_RET(bsp_socp_stop(g_stDecCase[i].SrcCh), BSP_OK);
        CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[i].SrcCh), BSP_OK);
    }

    for(i=0;i<16;i++)
    {
        CHECK_RET(bsp_socp_free_channel(u32DecDstId[i]), BSP_OK);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    for(i=1;i<5;i++)
    {
        g_stDecCase[i].DstCh = SOCP_DECODER_DEST_CHAN_0;
        if(g_stDecCase[i].bSrcSet)
        {
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
            g_stDecCase[i].bSrcSet = FALSE;
        }
        /*释放任务*/
        //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        //(BSP_VOID)taskDelete(g_stDecCase[i].TaskId);
        if(g_stDecCase[i].TaskId)
        {
            kthread_stop(g_stDecCase[i].TaskId);
        }
    }

    return 0;
}



