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

#define Socp_printf printk
#define bsp_log     printk

#if 1
#define SOCP_VIRT_TO_PHYS(virt) virt_to_phys((void*)virt)
#define SOCP_PHYS_TO_VIRT(phy)  (void *)(phys_to_virt((unsigned long)phy))
#else
#define SOCP_VIRT_TO_PHYS(virt) (virt)
#define SOCP_PHYS_TO_VIRT(phy)  (phy)
#endif

#if 1
#if 0
#define SOCP_TEST_FLUSH_CACHE(ptr, size)    __dma_single_cpu_to_dev(ptr, size, 1)
#define SOCP_TEST_INVALID_CACHE(ptr, size)  __dma_single_dev_to_cpu(ptr, size, 2)
#endif

//#define SOCP_TEST_FLUSH_CACHE(ptr, size)    dma_map_single(NULL, ptr, size, DMA_TO_DEVICE)
//#define SOCP_TEST_INVALID_CACHE(ptr, size)  dma_map_single(NULL, ptr, size, DMA_FROM_DEVICE)
unsigned long long g_socp_dma_test_mask=0xffffffffULL;
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

#else
#define SOCP_TEST_FLUSH_CACHE(ptr, size)  (0)
#define SOCP_TEST_INVALID_CACHE(ptr, size) (0)
#endif

BSP_VOID* TM_socp_malloc(BSP_U32 u32Size)
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
        bsp_log("malloc failed\n");
        return BSP_NULL;
    }

    return (void*)pItem;
}

BSP_S32 TM_socp_free(BSP_VOID* pMem)
{
    BSP_U32 *pItem;

    pItem = pMem;

    (void)free_pages((unsigned long)pItem,4);
    return BSP_OK;
}
static BSP_BOOL g_bInit = BSP_FALSE;

BSP_U32 g_SocpBufCnt = 0;
BSP_U8  *g_pSocpBuf[1000];
SOCP_RING_BUF_S g_socpEncDst[4];
SOCP_RING_BUF_S g_socpEncSrc[16];

/* GTR自动化测试编解码测试用例，数据包接收标志 */
u32 g_ul_rev_pkt_flag  = false;
/* GTR自动化测试编解码测试用例，异常事件标志 */
u32 g_ul_event_flag = false;

extern BSP_S32 socp_init(void);
extern SOCP_GBL_STATE g_strSocpStat;

#define DEV_INIT()\
do{\
    if(!g_bInit)\
    {\
        if(BSP_OK != socp_init())\
        {\
            Socp_printf("init fail...\n");\
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
        Socp_printf("%s(%d): ret(0x%x) error...\n", __FUNCTION__, __LINE__, x);\
        return x;\
    }\
}while(0)


#define CHECK_VAL(a, b)\
do{\
    if(a != b)\
    {\
        Socp_printf("%s(%d): value error... 0x%x 0x%x\n", __FUNCTION__, __LINE__, a, b);\
        return BSP_ERROR;\
    }\
}while(0)

#define TAG()\
{\
    Socp_printf("%s(%d)\n", __FUNCTION__, __LINE__);\
}

BSP_S32 SocpEventCB(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
{
    return 0;
}

BSP_S32 SocpRdCB(BSP_U32 u32ChanID)
{
    return 0;
}

BSP_S32 SocpReadCB(BSP_U32 u32ChanID)
{
    return 0;
}
BSP_S32 SocpSetEncChan1(BSP_U32 id)
{
    BSP_U32 u32ChanId = id;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    //p = (BSP_U8*)memalign(8, len);
     p = TM_socp_malloc(len);

    if(BSP_NULL == p)
    {
        Socp_printf("set chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;
    EncDstAttr.u32EncDstThrh = 0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = SOCP_VIRT_TO_PHYS(p);
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = SOCP_VIRT_TO_PHYS(p) + len -1;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x20;
    ret = bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("set chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }
    return 0;
}

BSP_S32 SocpSetEncChan2(BSP_U32 id)
{
    BSP_U32 u32ChanId = id;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    //p = (BSP_U8*)memalign(8, len);
    p = (BSP_U8*)TM_socp_malloc(len);

    if(BSP_NULL == p)
    {
        Socp_printf("set chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;

    EncDstAttr.u32EncDstThrh = 0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = SOCP_VIRT_TO_PHYS(p);
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = SOCP_VIRT_TO_PHYS(p) + len -1;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x20;
    ret = bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("set chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }

    return 0;
}

BSP_S32 SocpSetDecChan1(BSP_U32 id)
{
    BSP_U32 u32ChanId = id;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    //p = (BSP_U8*)memalign(8, len);
    p = (BSP_U8*)TM_socp_malloc(len);

    if(BSP_NULL == p)
    {
        Socp_printf("set chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;

    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    DecSrcAttr.eMode = SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = SOCP_VIRT_TO_PHYS(p);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = SOCP_VIRT_TO_PHYS(p) + len -1;
    ret = bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("set chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }

    return 0;
}


BSP_S32 SocpAllocEncChan1(BSP_U32 u32ChanId)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    //p = (BSP_U8*)memalign(8, len);
     p = (BSP_U8*)TM_socp_malloc(len);

    if(BSP_NULL == p)
    {
        Socp_printf("alloc chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;

    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = SOCP_VIRT_TO_PHYS(p);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = SOCP_VIRT_TO_PHYS(p) + len - 1;
    ret = bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }
    return u32ChanId;
}

BSP_S32 SocpResetAll(void)
{
    BSP_U32 i;
    BSP_U32 u32ResetValue;

    /* 对全局寄存器进行复位 */
    SOCP_REG_WRITE(SOCP_REG_GBLRST, 1);

    /* 等待通道复位状态自清 */
    for(i=0; i<1000; i++)
    {
        SOCP_REG_READ(SOCP_REG_GBLRST, u32ResetValue);
        if(0 == u32ResetValue)
        {
            break;
        }
    }

    if(0 != u32ResetValue)
    {
        return BSP_ERROR;
    }

    return BSP_OK;
}

BSP_S32 SocpAllocEncChan2(BSP_U32 u32ChanId)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U32 len = 0x1000;
    BSP_U32 len2 = 64;
    BSP_U8 *p1, *p2;
    BSP_U32 ret;

    //p1 = (BSP_U8*)memalign(8, len);
     p1 = (BSP_U8*)TM_socp_malloc(len);

    if(BSP_NULL == p1)
    {
        Socp_printf("alloc chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p1;

    p2 = (BSP_U8*)TM_socp_malloc(len2);
    if(BSP_NULL == p2)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        Socp_printf("alloc chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p2;

    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = SOCP_VIRT_TO_PHYS(p1);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = SOCP_VIRT_TO_PHYS(p1) + len - 1;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = SOCP_VIRT_TO_PHYS(p2);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = SOCP_VIRT_TO_PHYS(p2) + len2 - 1;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 5;
    ret = bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

        return -1;
    }

    return u32ChanId;
}

BSP_S32 SocpAllocDecChan1(BSP_U32 u32ChanId)
{
    SOCP_DECODER_DEST_CHAN_STRU DecDstAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    p = (BSP_U8*)TM_socp_malloc(len);

    if(BSP_NULL == p)
    {
        Socp_printf("alloc chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p;

    DecDstAttr.eDataType = SOCP_DATA_TYPE_0;
    DecDstAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;
    DecDstAttr.sDecoderDstSetBuf.pucOutputStart = SOCP_VIRT_TO_PHYS(p);
    DecDstAttr.sDecoderDstSetBuf.pucOutputEnd   = SOCP_VIRT_TO_PHYS(p) + len - 1;
    DecDstAttr.sDecoderDstSetBuf.u32Threshold   =  0x80;
    ret = bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDstAttr);
    if(BSP_OK != ret)
    {
        Socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }

    return u32ChanId;
}

/* 初始化成功 */
BSP_S32 SOCP_ST_INIT_001(void)
{
    BSP_U32 i=0;

    CHECK_RET(socp_init(), BSP_OK);

    for(i=0;i<1000;i++)
    {
        g_pSocpBuf[i] = BSP_NULL;
    }

    Socp_printf("SOCP TEST: INIT CASE 1 PASSED..\n");

    return 0;
}


/* 重复初始化成功, 测试之前重启单板 */
BSP_S32 SOCP_ST_INIT_002(void)
{
    CHECK_RET(socp_init(), BSP_OK);
    CHECK_RET(socp_init(), BSP_OK);

    Socp_printf("SOCP TEST: INIT CASE 2 PASSED\n");
    return 0;
}

BSP_U32 SOCP_ST_RESET_002(void)
{
    BSP_U32 i=0;

    for(i=0;i<7;i++)
    {
        CHECK_RET(socp_reset_dec_chan(i), BSP_OK);
    }
#if 0
    kthread_stop(g_strSocpStat.u32EncSrcTskID);
    kthread_stop(g_strSocpStat.u32DecDstTskID);
    kthread_stop(g_strSocpStat.u32EncDstTskID);
    kthread_stop(g_strSocpStat.u32DecSrcTskID);
#endif

    Socp_printf("SOCP TEST: RESET CASE 2 PASSED\n");

    return 0;
}


BSP_U32 SOCP_ST_INIT_004(void)
{
    CHECK_RET(socp_init(), BSP_OK);

    Socp_printf("SOCP TEST: INIT CASE 4 PASSED\n");

    return 0;
}

/* 设置编码目标通道，无效通道ID */
BSP_S32 SOCP_ST_ENC_DST_001(void)
{
    BSP_U32 u32ChanId;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_6 + 1;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET CODER DEST ATTR CASE 1 PASSED\n");
    return 0;
}

/* 设置编码目标通道，无效属性参数 */
BSP_S32 SOCP_ST_ENC_DST_002(void)
{
    BSP_U32 u32ChanId = SOCP_CODER_DEST_CHAN_0;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    DEV_INIT();

    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x1000;
    EncDstAttr.u32EncDstThrh = 0;

    EncDstAttr.sCoderSetDstBuf.pucOutputStart = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_NULL);
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;

    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004004;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;

    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30003800;   /* 起始大于结束*/
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;

    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_NULL);
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;

    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30008008;   /* 长度非8字节对齐 */
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;

    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_NULL);
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x1000;

    Socp_printf("SOCP TEST: SET CODER DEST ATTR CASE 2 PASSED\n");
    return 0;
}


/* 设置编码目标通道，设置正确属性 */
BSP_S32 SOCP_ST_ENC_DST_003(void)
{
    BSP_U32 u32ChanId = SOCP_CODER_DEST_CHAN_0;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    DEV_INIT();

    EncDstAttr.u32EncDstThrh = 0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x200;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_0), BSP_OK);

    Socp_printf("SOCP TEST: SET CODER DEST ATTR CASE 3 PASSED\n");
    return 0;
}


/* 设置编码目标通道，重复配置属性 */
BSP_S32 SOCP_ST_ENC_DST_004(void)
{
    BSP_U32 u32ChanId = SOCP_CODER_DEST_CHAN_0;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    DEV_INIT();

    EncDstAttr.u32EncDstThrh = 0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x200;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_ERR_SOCP_SET_FAIL);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_0), BSP_OK);

    Socp_printf("SOCP TEST: SET CODER DEST ATTR CASE 4 PASSED\n");
    return 0;
}


/* 设置编码目标通道，无效通道ID */
BSP_S32 SOCP_ST_ENC_DST_005(void)
{
    BSP_U32 u32ChanId = SOCP_CODER_DEST_CHAN_0;
    SOCP_CODER_DEST_CHAN_S EncDstAttr;

    DEV_INIT();

    EncDstAttr.u32EncDstThrh = 0;

    /* 配置之后立即初始化该通道*/
    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    EncDstAttr.sCoderSetDstBuf.pucOutputStart = 0x30004000;
    EncDstAttr.sCoderSetDstBuf.pucOutputEnd = 0x30007fff;
    EncDstAttr.sCoderSetDstBuf.u32Threshold = 0x200;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_0), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_1;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_1), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_2;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_2), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_3;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_3), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_4;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_4), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_5;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_5), BSP_OK);

    u32ChanId = SOCP_CODER_DEST_CHAN_6;
    CHECK_RET(bsp_socp_coder_set_dest_chan_attr(u32ChanId, &EncDstAttr), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_6), BSP_OK);


    Socp_printf("SOCP TEST: SET CODER DEST ATTR CASE 5 PASSED\n");
    return 0;
}

/* 申请编码源通道，空指针检查 */
BSP_S32 SOCP_ST_ENC_SRC_001(void)
{
    DEV_INIT();

    CHECK_RET(bsp_socp_coder_set_src_chan(0, BSP_NULL), BSP_ERR_SOCP_NULL);

    Socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 1 PASSED\n");
    return 0;
}


/* 申请编码源通道，无效参数 */
BSP_S32 SOCP_ST_ENC_SRC_002(void)
{
    BSP_U32 u32ChanId = 0;
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;

    DEV_INIT();

    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = 0x30004000;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30007fff;

    EncSrcAttr.eDataType = SOCP_DATA_TYPE_BUTT;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;

    EncSrcAttr.eDataTypeEn= SOCP_DATA_TYPE_EN_BUTT;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_EN_BUTT;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;

    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_BUTT;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;

    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_BUTT;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;

    EncSrcAttr.u32DestChanID = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;

    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_6 + 1;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;

    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = 0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = 0x30004004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = 0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30003800;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30008004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30007fff;

    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 0x10;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = 0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = 0x30004004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = 0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30003800;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30008004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30007fff;

    Socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 2 PASSED\n");
    return 0;
}


/* 申请编码源通道，申请成功 */
BSP_S32 SOCP_ST_ENC_SRC_003(void)
{
    BSP_U32 u32ChanId = 0;
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;

    DEV_INIT();

    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = 0x30004000;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = 0x30007fff;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);

    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = 0x30001000;
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = 0x30001fff;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 10;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);

    Socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 3 PASSED\n");
    return 0;
}

/* 设置解码通道属性 */
BSP_S32 SOCP_ST_DEC_SRC_001(void)
{
    BSP_U32 u32ChanId;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_DECODER_SRC_CHAN_3+ 1;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET DECODER SRC ATTR CASE 1 PASSED\n");
    return 0;
}


/* 设置解码通道属性 */
BSP_S32 SOCP_ST_DEC_SRC_002(void)
{
    BSP_U32 u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;

    DEV_INIT();

    DecSrcAttr.eMode = SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = 0x30007fff;

    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN_BUTT;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = BSP_NULL;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_NULL);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;

    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004004;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;

    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = 0x30003800;   /* 起始大于结束*/
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = 0x30007fff;

    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = BSP_NULL;
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_NULL);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = 0x30007fff;

    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = 0x30008008;   /* 长度非8字节对齐 */
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd = 0x30007fff;

    Socp_printf("SOCP TEST: SET DECODER SRC ATTR CASE 2 PASSED\n");

    return 0;
}


/* 设置解码通道属性 */
BSP_S32 SOCP_ST_DEC_SRC_003(void)
{
    BSP_U32 u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;

    DEV_INIT();

    DecSrcAttr.eMode= SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = 0x30007fff;
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(u32ChanId),BSP_OK);

    Socp_printf("SOCP TEST: SET DECODER SRC ATTR CASE 3 PASSED\n");

    return 0;
}


/* 重复设置解码通道属性 */
BSP_S32 SOCP_ST_DEC_SRC_004(void)
{
    /* 对应通道1*/
    BSP_U32 u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;

    DEV_INIT();

    DecSrcAttr.eMode= SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = 0x30007fff;
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_OK);
    CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_ERR_SOCP_DECSRC_SET);
    CHECK_RET(socp_soft_free_decsrc_chan(u32ChanId),BSP_OK);

    Socp_printf("SOCP TEST: SET DECODER SRC ATTR CASE 4 PASSED\n");

    return 0;
}


/* 设置解码通道属性 */
BSP_S32 SOCP_ST_DEC_SRC_005(void)
{
    BSP_U32 u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    SOCP_DECODER_SRC_CHAN_STRU DecSrcAttr;
    int i;

    DEV_INIT();

    DecSrcAttr.eMode= SOCP_DECSRC_CHNMODE_BYTES;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputStart = 0x30004000;
    DecSrcAttr.sDecoderSetSrcBuf.pucInputEnd   = 0x30007fff;
    DecSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;

    /* 通道全部设置*/
    for(i=0; i<4; i++)
    {
        u32ChanId = SOCP_DECODER_SRC_CHAN_0 + i;
        CHECK_RET(bsp_socp_decoder_set_src_chan_attr(u32ChanId, &DecSrcAttr), BSP_OK);
        CHECK_RET(socp_soft_free_decsrc_chan(u32ChanId),BSP_OK);
    }

    Socp_printf("SOCP TEST: SET DECODER SRC ATTR CASE 5 PASSED\n");
    return 0;
}

/* 申请解码目的通道 */
BSP_S32 SOCP_ST_DEC_DST_001(void)
{
    BSP_U32 u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);

    DEV_INIT();

    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, 0), BSP_ERR_SOCP_NULL);

    Socp_printf("SOCP TEST: SET DECODER ALLOC CHAN CASE 1 PASSED\n");

    return 0;
}


/* 申请解码目的通道 */
BSP_S32 SOCP_ST_DEC_DST_002(void)
{
    BSP_U32 u32ChanId;
    SOCP_DECODER_DEST_CHAN_STRU DecDestAttr;

    DEV_INIT();

    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;
    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007fff;
    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 1;

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_BUTT;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_INVALID_PARA);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;

    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_3+1;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_INVALID_CHAN);
    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;

    DecDestAttr.u32SrcChanID = 0;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_INVALID_CHAN);
    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;

    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_NULL);
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;

    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_NULL);
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007fff;

    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30008000;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_INVALID_PARA);
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;

    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004004;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;

    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007ff3;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007fff;

    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 256;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_ERR_SOCP_INVALID_PARA);
    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 1;

    Socp_printf("SOCP TEST: SET DECODER ALLOC CHAN CASE 2 PASSED\n");

    return 0;
}


/* 申请解码目的通道 */
BSP_S32 SOCP_ST_DEC_DST_003(void)
{
    BSP_U32 u32ChanId;
    SOCP_DECODER_DEST_CHAN_STRU DecDestAttr;

    DEV_INIT();

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;
    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007fff;
    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 1;

    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId, &DecDestAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);

    Socp_printf("SOCP TEST: SET DECODER ALLOC CHAN CASE 3 PASSED\n");

    return 0;
}


/* 申请解码目的通道 */
BSP_S32 SOCP_ST_DEC_DST_004(void)
{
    BSP_U32 u32ChanId1, u32ChanId2, u32ChanId3, u32ChanId4;
    SOCP_DECODER_DEST_CHAN_STRU DecDestAttr;

    DEV_INIT();

    u32ChanId1 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId2 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 4);
    u32ChanId3 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 8);
    u32ChanId4 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0xC);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;
    DecDestAttr.u32SrcChanID = SOCP_DECODER_SRC_CHAN_0;
    DecDestAttr.sDecoderDstSetBuf.pucOutputStart = 0x30004000;
    DecDestAttr.sDecoderDstSetBuf.pucOutputEnd = 0x30007fff;
    DecDestAttr.sDecoderDstSetBuf.u32Threshold = 1;

    DecDestAttr.eDataType = SOCP_DATA_TYPE_0;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId1, &DecDestAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId1), BSP_OK);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_1;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId2, &DecDestAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId2), BSP_OK);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_2;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId3, &DecDestAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId3), BSP_OK);
    DecDestAttr.eDataType = SOCP_DATA_TYPE_3;
    CHECK_RET(bsp_socp_decoder_set_dest_chan(u32ChanId4, &DecDestAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId4), BSP_OK);

    Socp_printf("SOCP TEST: SET DECODER ALLOC CHAN CASE 4 PASSED\n");

    return 0;
}


/* 释放通道，释放无效通道*/
BSP_S32 SOCP_ST_FREE_CHAN_001(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|15;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 释放通道，释放未申请通道 */
BSP_S32 SOCP_ST_FREE_CHAN_002(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 释放通道，释放编码通道成功 */
BSP_S32 SOCP_ST_FREE_CHAN_003(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: FREE CHANNEL CASE 3 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 3 PASSED\n");

    return 0;
}


/* 释放通道，释放解码通道成功 */
BSP_S32 SOCP_ST_FREE_CHAN_004(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: FREE CHANNEL CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 4 PASSED\n");

    return 0;
}

/* 释放通道，释放运行中的通道 */
BSP_S32 SOCP_ST_FREE_CHAN_005(void)
{
    BSP_U32 u32ChanId;
    BSP_U32 ret;

    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: FREE CHANNEL CASE 5 FAILED\n");
        return 0;
    }
    ret = SocpSetEncChan1(SOCP_CODER_DEST_CHAN_0);
    if(-1 == (s32)ret)
    {
       Socp_printf("SOCP TEST: FREE CHANNEL CASE 5 FAILED\n");
        return 0;
    }
    //Socp_printf("g_SocpBufCnt is %d, line%d, ptr1 is 0x%x, ptr2 is 0x%x\n",g_SocpBufCnt,(int)__LINE__,(BSP_U32)(g_pSocpBuf[g_SocpBufCnt -1]),(BSP_U32)(g_pSocpBuf[g_SocpBufCnt-2]));
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_OK);

    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_CHAN_RUNNING);

    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_OK);
    //Socp_printf("g_SocpBufCnt is %d, line%d, ptr1 is 0x%x, ptr2 is 0x%x\n",g_SocpBufCnt,(int)__LINE__,(BSP_U32)(g_pSocpBuf[g_SocpBufCnt -1]),(BSP_U32)(g_pSocpBuf[g_SocpBufCnt-2]));
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(SOCP_CODER_DEST_CHAN_0), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 5 PASSED\n");
    return 0;
}

/* 释放通道，反复申请释放 */
BSP_S32 SOCP_ST_FREE_CHAN_006(void)
{
    BSP_U32 u32ChanId[6];
    BSP_S32 n=4;
    BSP_S32 i, j, ret;

    DEV_INIT();

    for(j=0; j<10; j++)
    {
        for(i=0; i<n; i++)
        {
            u32ChanId[i] = SocpAllocEncChan1(i);
            if(-1 == (s32)u32ChanId[i])
            {
                Socp_printf("alloc channel error\n");
                Socp_printf("SOCP TEST: FREE CHANNEL CASE 6 FAILED\n");
                return 0;
            }
            //Socp_printf(" u32ChanId[%d] is %d\n", i, u32ChanId[i]);
        }

        for(i=n-1; i>=0; i--)
        {
            ret = bsp_socp_free_channel(u32ChanId[i]);
            //Socp_printf(" u32ChanId[%d] is %d\n", i, u32ChanId[i]);
            if(BSP_OK != ret)
            {
                Socp_printf("free channel error, ret=0x%x\n", ret);
                Socp_printf("SOCP TEST: FREE CHANNEL CASE 6 FAILED\n");
                return 0;
            }
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        }
    }

    Socp_printf("SOCP TEST: FREE CHANNEL CASE 6 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置无效通道的事件回调函数 */
BSP_S32 SOCP_ST_SET_EVENT_001(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_6 + 1;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_DECODER_SRC_CHAN_3 + 1;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|6;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|16;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET EVENT CB CASE 1 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置未申请通道的事件回调函数 */
BSP_S32 SOCP_ST_SET_EVENT_002(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET EVENT CB CASE 2 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置未配置通道的事件回调函数 */
BSP_S32 SOCP_ST_SET_EVENT_003(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET EVENT CB CASE 3 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置有效事件回调函数 */
BSP_S32 SOCP_ST_SET_EVENT_004(void)
{
    BSP_U32 u32ChanId1;
    BSP_U32 u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId1)
    {
        Socp_printf("SOCP TEST: SET EVENT CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId1, SocpEventCB), BSP_OK);

    u32ChanId2 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId2 = SocpAllocDecChan1(u32ChanId2);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("SOCP TEST: SET EVENT CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId2, SocpEventCB), BSP_OK);

    bsp_socp_free_channel(u32ChanId2);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    bsp_socp_free_channel(u32ChanId1);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET EVENT CB CASE 4 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置事件回调函数为空 */
BSP_S32 SOCP_ST_SET_EVENT_005(void)
{
    BSP_U32 u32ChanId1;
    BSP_U32 u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId1)
    {
        Socp_printf("SOCP TEST: SET EVENT CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId1, BSP_NULL), BSP_OK);

    u32ChanId2 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId2 = SocpAllocDecChan1(u32ChanId2);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("SOCP TEST: SET EVENT CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId2, BSP_NULL), BSP_OK);

    bsp_socp_free_channel(u32ChanId2);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    bsp_socp_free_channel(u32ChanId1);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET EVENT CB CASE 5 PASSED\n");
    return 0;
}

/* 设置事件回调函数，非申请通道:DSP\BBP LOG\BBP DS*/
BSP_S32 SOCP_ST_SET_EVENT_006(void)
{
    BSP_U32 u32ChanId;
    BSP_U32 i;
    DEV_INIT();

    u32ChanId = SOCP_DSPLOG_CHN;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, BSP_NULL), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_OK);

    for(i=SOCP_BBPLOG_CHN;i<SOCP_BBPDS_CHN;i++)
    {
        CHECK_RET(bsp_socp_register_event_cb(u32ChanId, BSP_NULL), BSP_OK);
        CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_OK);
    }

    u32ChanId = SOCP_BBPDS_CHN;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, BSP_NULL), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_OK);

    Socp_printf("SOCP TEST: SET EVENT CB CASE 6 PASSED\n");
    return 0;
}

/* 设置数据读取回调函数，设置无效通道的数据读取回调函数 */
BSP_S32 SOCP_ST_SET_READ_001(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_6 + 1;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|16;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET READ CB CASE 1 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET READ CB CASE 1 PASSED\n");
    return 0;
}


/* 设置数据读取回调函数，设置未申请的解码目的通道 数据读取回调函数*/
BSP_S32 SOCP_ST_SET_READ_002(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET READ CB CASE 2 PASSED\n");
    return 0;
}


/* 设置数据读取回调函数，设置未配置的数据读取回调函数，编码目的通道 */
BSP_S32 SOCP_ST_SET_READ_003(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET READ CB CASE 3 PASSED\n");
    return 0;
}


/* 设置数据读取回调函数，设置有效数据读取回调函数 */
BSP_S32 SOCP_ST_SET_READ_004(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);

    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET READ CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, SocpReadCB), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET READ CB CASE 4 PASSED\n");
    return 0;
}


/* 设置数据读取回调函数，设置数据读取回调函数为空 */
BSP_S32 SOCP_ST_SET_READ_005(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(SocpSetEncChan1(u32ChanId), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, BSP_NULL), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(u32ChanId), BSP_OK);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET READ CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_read_cb(u32ChanId, BSP_NULL), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: SET READ CB CASE 5 PASSED\n");
    return 0;
}

/* 设置RD回调函数，设置无效通道的RD回调函数 */
BSP_S32 SOCP_ST_SET_RD_001(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);

    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 1 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    bsp_socp_free_channel(u32ChanId);

    Socp_printf("SOCP TEST: SET RD CB CASE 1 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置未申请通道的RD回调函数 */
BSP_S32 SOCP_ST_SET_RD_002(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET RD CB CASE 2 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置未配置的RD回调函数 */
BSP_S32 SOCP_ST_SET_RD_003(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: SET RD CB CASE 3 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置非LIST方式的RD回调函数 */
BSP_S32 SOCP_ST_SET_RD_004(void)
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_CHAN_MODE);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET RD CB CASE 4 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置有效RD回调函数 */
BSP_S32 SOCP_ST_SET_RD_005(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SocpAllocEncChan2(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET RD CB CASE 5 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置RD回调函数为空 */
BSP_S32 SOCP_ST_SET_RD_006(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, BSP_NULL), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SocpAllocEncChan2(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 6 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, BSP_NULL), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: SET RD CB CASE 6 PASSED\n");
    return 0;
}


/* 通道控制，启动无效通道 */
BSP_S32 SOCP_ST_START_001(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);

    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 1 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: START CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 通道控制，启动未申请通道 */
BSP_S32 SOCP_ST_START_002(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|0;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: START CHANNEL CASE 2 PASSED\n");
    return 0;
}


/* 通道控制，启动时，目的通道未设置 */
BSP_S32 SOCP_ST_START_003(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("alloc encoder src chan failed\n");
        Socp_printf("SOCP TEST: START CHANNEL CASE 3 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_DEST_CHAN);

    bsp_socp_free_channel(u32ChanId);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: START CHANNEL CASE 3 PASSED\n");
    return 0;
}

/* 通道控制，启动成功 */
BSP_S32 SOCP_ST_START_004(void)
{
    BSP_U32 u32ChanId1, u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SOCP_CODER_DEST_CHAN_0;
    if(-1 == SocpSetEncChan1(u32ChanId1))
    {
        Socp_printf("set encoder dest chan failed\n");
        Socp_printf("SOCP TEST: START CHANNEL CASE 4 FAILED\n");

        return 0;
    }

    u32ChanId2 = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("alloc encoder src chan failed\n");
        Socp_printf("SOCP TEST: START CHANNEL CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId2), BSP_OK);
    CHECK_RET(bsp_socp_stop(u32ChanId2), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId2), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(u32ChanId1), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: START CHANNEL CASE 4 PASSED\n");
    return 0;
}

/* 通道控制，重复启动 */
BSP_S32 SOCP_ST_START_005(void)
{
    BSP_U32 u32ChanId1, u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SOCP_DECODER_SRC_CHAN_0;
    if(BSP_OK != SocpSetDecChan1(u32ChanId1))
    {
        Socp_printf("set decoder src chan failed\n");
        Socp_printf("SOCP TEST: START CHANNEL CASE 5 FAILED\n");
        return 0;
    }

    u32ChanId2 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId2 = SocpAllocDecChan1(u32ChanId2);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("alloc decoder dest chan failed\n");
        Socp_printf("SOCP TEST: START CHANNEL CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId1), BSP_OK);
    CHECK_RET(bsp_socp_stop(u32ChanId1), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId2), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(u32ChanId1), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: START CHANNEL CASE 5 PASSED\n");
    return 0;
}


/* 通道控制，停止无效通道 */
BSP_S32 SOCP_ST_STOP_001(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);

    u32ChanId = SocpAllocDecChan1(u32ChanId);
    if(-1 == (s32)u32ChanId)
    {
        Socp_printf("SOCP TEST: SET RD CB CASE 1 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    bsp_socp_free_channel(u32ChanId);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: STOP CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 通道控制，停止未申请通道 */
BSP_S32 SOCP_ST_STOP_002(void)
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|8;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    Socp_printf("SOCP TEST: STOP CHANNEL CASE 2 PASSED\n");
    return 0;
}



/* 通道控制，停止成功 */
BSP_S32 SOCP_ST_STOP_003(void)
{
    BSP_U32 u32ChanId1, u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SOCP_CODER_DEST_CHAN_0;
    if(BSP_OK != SocpSetEncChan1(u32ChanId1))
    {
        Socp_printf("set coder dest chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 3 FAILED\n");
        return 0;
    }

    u32ChanId2 = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("alloc encoder src chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 3 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId2), BSP_OK);
    CHECK_RET(bsp_socp_stop(u32ChanId2), BSP_OK);

    CHECK_RET(bsp_socp_free_channel(u32ChanId2), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(u32ChanId1), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    Socp_printf("SOCP TEST: STOP CHANNEL CASE 3 PASSED\n");
    return 0;
}


/* 通道控制，重复停止 */
BSP_S32 SOCP_ST_STOP_004(void)
{
    BSP_U32 u32ChanId1, u32ChanId2;
    DEV_INIT();

    u32ChanId1 = SOCP_DECODER_SRC_CHAN_0;
    if(BSP_OK != SocpSetDecChan1(u32ChanId1))
    {
        Socp_printf("set decoder src chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 4 FAILED\n");
        return 0;
    }

    u32ChanId2 = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 0);
    u32ChanId2 = SocpAllocDecChan1(u32ChanId2);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("alloc decoder dest chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId1), BSP_OK);
    CHECK_RET(bsp_socp_stop(u32ChanId1), BSP_OK);

    CHECK_RET(bsp_socp_free_channel(u32ChanId2), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(u32ChanId1), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: STOP CHANNEL CASE 4 PASSED\n");
    return 0;
}


/* 通道控制，反复打开、停止 */
BSP_S32 SOCP_ST_STOP_005(void)
{
    BSP_U32 u32ChanId1, u32ChanId2, i;
    DEV_INIT();

    u32ChanId1 = SOCP_CODER_DEST_CHAN_0;
    if(BSP_OK != SocpSetEncChan1(u32ChanId1))
    {
        Socp_printf("set encoder dst chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 5 FAILED\n");
        return 0;
    }

    u32ChanId2 = SocpAllocEncChan1(0);
    if(-1 == (s32)u32ChanId2)
    {
        Socp_printf("alloc encoder src chan failed\n");
        Socp_printf("SOCP TEST: STOP CHANNEL CASE 5 FAILED\n");
        return 0;
    }
    for(i=0; i<100; i++)
    {
        CHECK_RET(bsp_socp_start(u32ChanId2), BSP_OK);
        CHECK_RET(bsp_socp_stop(u32ChanId2), BSP_OK);
    }

    bsp_socp_free_channel(u32ChanId2);
    CHECK_RET(socp_soft_free_encdst_chan(u32ChanId1), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    Socp_printf("SOCP TEST: STOP CHANNEL CASE 5 PASSED\n");
    return 0;
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
BSP_U32 g_socpRxTotal[7] = {0};
BSP_U32 g_socpRdTotal[25] = {0};
BSP_U32 g_socpTxTotal[25] = {0};

BSP_S32 SocpStSetEncDst(SOCP_ST_CASE_S *pCase)
{
    SOCP_CODER_DEST_CHAN_S EncDstAttr;
    void   *pVirtAdd;
    dma_addr_t  ulAddress;
    struct device    dev;

    memset(&dev, 0, sizeof(dev));
    if(!pCase->bDstSet)
    {
        BSP_U8 *p;

        p = (BSP_U8*)dma_alloc_coherent(&dev, pCase->u32OutputSize, &ulAddress, GFP_KERNEL);
        if(BSP_NULL == p)
        {
            Socp_printf("%s[%d] SET ENC DST FAILED!\n", __FUNCTION__, __LINE__);
            return BSP_ERROR;
        }
        Socp_printf("%s[%d] malloc success 0x%p!\n", __FUNCTION__, __LINE__,p);
        pCase->u32OutputStart = (uintptr_t)p;

        EncDstAttr.sCoderSetDstBuf.pucOutputStart = ulAddress;
        EncDstAttr.sCoderSetDstBuf.pucOutputEnd = ulAddress + pCase->u32OutputSize - 1;
        EncDstAttr.sCoderSetDstBuf.u32Threshold = pCase->u32Threshold;
        EncDstAttr.u32EncDstThrh = pCase->u32EncDstThrh;
        EncDstAttr.sCoderSetDstBuf.u32Threshold = pCase->u32Threshold;

        if(BSP_OK != bsp_socp_coder_set_dest_chan_attr(pCase->DstCh, &EncDstAttr))
        {
            Socp_printf("set enc dst channel failed!\n");

            return BSP_ERROR;
        }
        pCase->bDstSet = BSP_TRUE;

        return BSP_OK;
    }
    else
    {
        Socp_printf("set enc dst channel failed, the channel has been set!\n");
        return BSP_ERROR;
    }
}

BSP_S32 SocpStSetDecSrc(SOCP_ST_CASE_DECODER_S *pCase)
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
            Socp_printf("%s[%d] SET DEC SRC FAILED!\n", __FUNCTION__, __LINE__);
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
            Socp_printf(" the dec src channel has been set failed\n");
            TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        }
        pCase->bSrcSet = BSP_TRUE;
    }

    return 0;
}


BSP_S32 SocpStAllocDecDst(SOCP_ST_CASE_DECODER_S *pCase)
{
    SOCP_DECODER_DEST_CHAN_STRU DecDstAttr;
    BSP_U8 *p;

    //p = (BSP_U8*)cacheDmaMalloc(pCase->u32OutputSize);
    //p = kmalloc(pCase->u32OutputSize, GFP_KERNEL);
    p =(BSP_U8*)TM_socp_malloc(pCase->u32OutputSize);

    if(BSP_NULL == p)
    {
        Socp_printf("%s[%d] ALLOC DEC DST FAILED!\n", __FUNCTION__, __LINE__);
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
        Socp_printf(" the dec dst channel has been allocated failed\n");
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    return 0;
}

BSP_S32 SocpStAllocEncSrc(SOCP_ST_CASE_S *pCase)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U8 *p;
    BSP_U8 *pRd = 0;

    p = (BSP_U8*)TM_socp_malloc(pCase->u32OutputSize);

    if(BSP_NULL == p)
    {
        Socp_printf("%s[%d] ALLOC ENC SRC FAILED!\n", __FUNCTION__, __LINE__);
        return BSP_ERROR;
    }
    pCase->u32InputStart = (uintptr_t)p;
    g_pSocpBuf[g_SocpBufCnt++] = p;

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        pRd = (BSP_U8*)TM_socp_malloc(pCase->u32RDSize);
        if(BSP_NULL == pRd)
        {
            Socp_printf("%s[%d] ALLOC ENC SRC RD BUF FAILED!\n", __FUNCTION__, __LINE__);
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

        Socp_printf("alloc enc src channel failed!\n");

        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SocpStEventCB_1(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
{
    BSP_U32 u32ChanType =  SOCP_REAL_CHAN_TYPE(u32ChanID);
    BSP_U32 u32ChanId   =  SOCP_REAL_CHAN_ID(u32ChanID);

    g_ul_event_flag = true;

    switch(u32Event)
    {
        case SOCP_EVENT_PKT_HEADER_ERROR:
        {
            Socp_printf("chan type is [%d], id is [%d], event is packet header check error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_OUTBUFFER_OVERFLOW:
        {
            Socp_printf("chan type is [%d], id is [%d], event is outbuffer overflow!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_HDLC_HEADER_ERROR:
        {
            Socp_printf("chan type is [%d], id is [%d], event is 0x7e error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_CRC_ERROR:
        {
            Socp_printf("chan type is [%d], id is [%d], event is crc error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_PKT_LENGTH_ERROR:
        {
            Socp_printf("chan type is [%d], id is [%d], event is pkt length error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_DATA_TYPE_ERROR:
        {
            Socp_printf("chan type is [%d], id is [%d], event is data type error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_DECODER_UNDERFLOW:
        {
            Socp_printf("chan type is [%d], id is [%d], event is inbuf underflow error!\n", u32ChanType, u32ChanId);
            break;
        }
        case SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW:
        {
            Socp_printf("chan type is [%d], id is [%d], event is outbuffer threshold overflow error!\n", u32ChanType, u32ChanId);
            break;
        }
        default:
        {
            Socp_printf("the event:0x%x is valid!\n", u32Event);
            return BSP_ERROR;
        }

    }

    return BSP_OK;
}


BSP_S32 SocpStReadCB_1(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    Socp_printf("func: SocpStReadCB_1: chan[%d] get data len=[%d]\n", u32ChanID&0xff, len);
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
        Socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            Socp_printf("\n");
    }
    Socp_printf(" the chan id is %d\n",u32ChanID&0xff);
#endif
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

BSP_S32 SocpStReadCB_2(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i, c;
    static BSP_BOOL flag = BSP_TRUE;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);

    c = u32ChanID&0xf;
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[c] += len;
    Socp_printf("func: SocpStReadCB_2: c[%d] get data R=%d T=%d\n", u32ChanID&0xff, len, g_socpRxTotal[c]);
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
            Socp_printf("0x%02x ", g_socpRxdata[i]);
            if(i && (0 == i%8))
                Socp_printf("\n");
        }
        flag = BSP_FALSE;
    }
#endif
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

BSP_S32 SocpStReadCB_3(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int chan;

    chan = u32ChanID&0xff;
    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[chan] += len;
    Socp_printf("func: SocpStReadCB_3: chan[%d] get data R=%d T=%d\n", chan, len, g_socpRxTotal[chan]);
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


BSP_U32 rEncCnt = 0;
BSP_S32 SocpStReadCB_Enc_Stress(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);
    rEncCnt++;
    if(9999 == rEncCnt%10000)
    {
        Socp_printf("encoder read cnt is %d\n",rEncCnt);
    }
    if(rEncCnt >0xFFFFFFF0)
    {
        rEncCnt = 0;
    }

    return 0;
}


BSP_S32 SocpStReadCB_4(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    Socp_printf("func: SocpStReadCB_4: chan[%x] get data len=[%d]\n", u32ChanID, len);

    g_ul_rev_pkt_flag = true;

    return 0;
}

BSP_U32 rCnt = 0;
BSP_S32 SocpStReadCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int chan;

    chan = u32ChanID&0xff;
    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[chan] += len;
    //Socp_printf("chan[%d] R=%d T=%d\n", chan, len, g_socpRxTotal[chan]);
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
        Socp_printf("read cnt is %d\n",rCnt);
    }
    if(rCnt >0xFFFFFFF0)
    {
        rCnt = 0;
    }

    g_ul_rev_pkt_flag = true;

    return 0;
}

static BSP_U32 g_socpRDdata[8];

BSP_S32 SocpStRdCB_1(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    Socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);
    //g_socpRDdata[0] = (BSP_U32)&Buffer;
    //g_socpRDdata[1] = len;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

//    Socp_printf("chan[%d] read RD done!\n", u32ChanID);

    return 0;
}

BSP_S32 SocpStRdCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    //Socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);
    g_socpRDdata[0] = (uintptr_t)&Buffer;
    g_socpRDdata[1] = len;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

//    Socp_printf("chan[%d] read RD done!\n", u32ChanID);

    return 0;
}
BSP_S32 SocpStReadCB_5(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    Socp_printf("chan[%x] get data len=[%d]\n", u32ChanID, len);
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
        Socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            Socp_printf("\n");
    }

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

BSP_S32 SocpStReadCB_6(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    Socp_printf("chan[%d] get data len=[%d]\n", u32ChanID&0xff, len);
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
        Socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            Socp_printf("\n");
    }
    //Socp_printf(" the chan id is %d\n",u32ChanID);

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    g_ul_rev_pkt_flag = true;

    return 0;
}

BSP_U32 rDecCnt = 0;
BSP_S32 SocpStReadCB_Dec_Stress(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

    rDecCnt++;
    if(9999 == rDecCnt%10000)
    {
        printk("decoder read cnt is %d\n",rDecCnt);
    }
    if(rDecCnt >0xFFFFFFF0)
    {
        rDecCnt = 0;
    }

    return 0;
}

SOCP_ST_CASE_S g_stCase[31] =
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
        SOCP_ENC_DEBUG_DIS, 0x100
    },
    {
        // 18
        0, 1, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 2048, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 512, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x100
    },
    {
        // 19
        0, 2, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 4096, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x100
    },
    {
        // 20
        0, 3, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x100
    },
    {
        // 21
        0, 9, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x100
    },
    {
        // 22
        0, 10, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_3,
        0, 0x1000, 0, 8192, 40, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_19, SocpStRdCB_19, 0, 1024, 2000,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0x100
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

SOCP_ST_CASE_DECODER_S g_stDecCase[17] =
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

BSP_BOOL bEncSrc0Set = FALSE;
BSP_BOOL bEncSrc1Set = FALSE;
BSP_BOOL bEncSrc2Set = FALSE;
BSP_BOOL bEncSrc3Set = FALSE;

BSP_BOOL bDecSrc0Set = FALSE;
BSP_BOOL bDecSrc1Set = FALSE;
BSP_U32  bDecDest0Alloc = FALSE;
BSP_U32  bDecDest1Alloc = FALSE;

BSP_S32 SocpStInitChannel(SOCP_ST_CASE_S *pCase)
{
    BSP_U32 u32Ret;

    DEV_INIT();
    bsp_log("init\n");
    msleep(100);

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    u32Ret = SocpStAllocEncSrc(pCase);
    bsp_log("set enc src chnn chnn:%d\n",u32Ret);

    if(u32Ret != BSP_OK)
    {
        Socp_printf("SocpStInitChannel: init enc src failed!\n");
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

BSP_S32 SocpStInitDecChannel(SOCP_ST_CASE_DECODER_S *pCase)
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


BSP_VOID SocpStGenPayLoad(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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

BSP_VOID SocpStGenPayLoad2(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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

BSP_VOID SocpStGenPkt(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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

BSP_VOID SocpStGenPkt01(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    /* 组包头 */
    /*
    pBuff[0] = 0x49;
    pBuff[1] = 0x53;
    pBuff[2] = 0x49;
    pBuff[3] = 0x48;
    */
    pBuff[0] = 0x48;
    pBuff[1] = 0x49;
    pBuff[2] = 0x53;
    pBuff[3] = 0x49;

    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;
    //pBuff += 8;

    /* 组消息包 */
    SocpStGenPayLoad((pBuff+8), u32DataLen-16);

    return;
}


BSP_VOID SocpStGenPkt1(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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

BSP_VOID SocpStGenPkt2(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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
    pWord[0] = (u32DataLen - 8);

    pBuff[8] = 0xA5;


    return;
}

BSP_VOID SocpStGenPkt3(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    pBuff[0] = 0x01;
    pBuff[1] = 0x21;
    pBuff[2] = 0xed;
    pBuff[3] = 0x37;

    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;
    //pBuff += 8;

    SocpStGenPayLoad((pBuff+8), u32DataLen-16);

    return;
}

BSP_VOID SocpStGenBD1(BSP_U32 *pBD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    pBD[0] = (uintptr_t)pBuff;
    pBD[1] = 0;
    pBD[1] |= (0xffff & u32DataLen);

    SocpStGenPayLoad(pBuff, u32DataLen);

    return;
}


BSP_VOID SocpStGenBD2(BSP_U32 *pBD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    pBD[0] = (uintptr_t)pBuff;
    pBD[1] = 0;
    pBD[1] |= (0xffff & u32DataLen);

    SocpStGenPayLoad(pBuff, u32DataLen);

    return;
}

BSP_VOID SocpStGenBD3(BSP_U32 *pBD, BSP_U32 *pCD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 ulTime = 0;
    BSP_U32 ulTime1 = 0;
    SOCP_PACKET_HEAD_S * pstSocpPackt = (SOCP_PACKET_HEAD_S*)pBuff;
    int i;

    ulTime                           = 0x08070605;
    ulTime1                          = 0x0d0c0b0a;
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
        pBuff[i] = i;
    }

    pBD[0] = (uintptr_t)pCD;
    pBD[1] = 0x10001;

    pCD[0] = (uintptr_t)pBuff;
    pCD[1] = 0x10;
    pCD[2] = (uintptr_t)pBuff+0x10;
    pCD[3] = 0x18;
    pCD[4] = (uintptr_t)pBuff+0x10+0x18;
    u32DataLen = u32DataLen - 0x18;
    pCD[5] = 0x10000|u32DataLen;

    return;
}


BSP_VOID SocpStGenBD4(BSP_U32 *pBD, BSP_U32 *pCD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    int i;

    for(i=0; i<16; i++)
    {
        pBuff[i] = i;
    }

    pBD[0] = (uintptr_t)pCD;
    pBD[1] = 0x10001;

    pCD[0] = (uintptr_t)pBuff;
    pCD[1] = 0x10000|u32DataLen;
#if 0
    pCD[2] = (BSP_U32)pBuff+0x10;
    pCD[3] = 0x18;
    pCD[4] = (BSP_U32)pBuff+0x10+0x18;
    u32DataLen = u32DataLen - 0x18;
    pCD[5] = 0x10000|u32DataLen;

#endif
    return;
}

BSP_S32 socp_encode_task001(BSP_VOID *param)
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

    //Socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = (BSP_U8*)kmalloc(len,GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    bsp_log("packet %p, len %d\n", packet, pCase->u32DataLen);
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
    bsp_log("enc over cnt %d\n",cnt);

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);
    return 0;
}

// added by yangzhi for variable packet
BSP_S32 socp_encode_task002(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen + 8;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int i;

    //packet = (BSP_U8*)kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }

    SocpStGenPkt(packet, pCase->u32DataLen);

    for(i=0;i<(cnt/2);i++)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
        }
        else
        {
            msleep(2);
        }
    }
    msleep(20);
    //kfree(packet);
    TM_socp_free(packet);

    len = (pCase->u32DataLen * 2) +8;
    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenPkt(packet, pCase->u32DataLen * 2);

    for(i=(cnt/2);i<cnt;i++)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
        }
        else
        {
            msleep(2);
        }
    }

    msleep(100);
    //kfree(packet);
    TM_socp_free(packet);
    Socp_printf("chan[%d] write done!\n", pCase->SrcCh);

    return 0;
}

BSP_S32 socp_encode_task003(BSP_VOID *param)
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

    //Socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = kmalloc(len, GFP_KERNEL|GFP_DMA);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
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

    Socp_printf("cnt is %d, chan[%d] write done! totol=0x%x size=0x%x\n", cnt, pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task004(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    BSP_U8 bd[8];
    SOCP_BUFFER_RW_STRU Buffer;

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_rd_buffer(pCase->SrcCh, &Buffer), BSP_OK);
        len = Buffer.u32Size + Buffer.u32RbSize;
        Socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, pCase->SrcCh, len);
        if(len)
        {
            CHECK_RET(bsp_socp_read_rd_done(pCase->SrcCh, len), BSP_OK);
        }

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
        }
        else
        {
            msleep(2);
        }
    }

    msleep(50);
    //kfree(packet);
    TM_socp_free(packet);

    Socp_printf("chan[%d] write done!\n", pCase->SrcCh);

    return 0;
}


BSP_S32 socp_encode_task005(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen + 8;
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

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenPkt(packet, pCase->u32DataLen);


    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            vfcnt = 0;
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
    //kfree(packet);
    TM_socp_free(packet);
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task006(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);

    return 0;
}

BSP_S32 socp_encode_task007(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);

    return 0;
}

BSP_S32 socp_encode_task008(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }

    //g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenPkt(packet, pCase->u32DataLen);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    msleep(50);
    //kfree(packet);
    TM_socp_free(packet);
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task009(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenPkt2(packet, len);

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
    }
    msleep(50);
    //kfree(packet);
    TM_socp_free(packet);

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task010(BSP_VOID *param)
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

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;

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
            Socp_printf("packet[%d] is 0x%x\n", i, packet[i]);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task011(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenPkt3(packet, pCase->u32DataLen);

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
    }
    //kfree(packet);
    TM_socp_free(packet);

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task013(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
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

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


u32 g_ulSocpDelay = 100;

void socp_set_task_stress(u32 para)
{
    g_ulSocpDelay = para;
}

BSP_S32 socp_encode_task_stress_001(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int len = pCase->u32DataLen + 8;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //Socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(1)
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
            //g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 0x0FFFFFFF)
        {
            Socp_printf(" socp_encode_task_stress_001 break!\n");
            break;
        }
        msleep(g_ulSocpDelay);
    }

    //msleep(100);
    //kfree(packet);
    TM_socp_free(packet);

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task_stress_002(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int len = pCase->u32DataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    BSP_U8 bd[8];
    int vfcnt = 0;
    int c;
    SOCP_BUFFER_RW_STRU Buffer;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //Socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);

    if(!packet)
    {
        Socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(1)
    {
        CHECK_RET(bsp_socp_get_rd_buffer(pCase->SrcCh, &Buffer), BSP_OK);
        len = Buffer.u32Size + Buffer.u32RbSize;
        if(len)
        {
            CHECK_RET(bsp_socp_read_rd_done(pCase->SrcCh, len), BSP_OK);
        }

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
            //g_socpTxTotal[c]++;
        }
        else
        {
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 0x0FFFFFFF)
        {
            Socp_printf(" socp_encode_task_stress_002 break!\n");
            break;
        }
        msleep(g_ulSocpDelay);
    }

    //msleep(100);
    //kfree(packet);
    TM_socp_free(packet);

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


BSP_S32 socp_encode_task_stress_003(BSP_VOID *param)
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
    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);

    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
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
            //cnt--;
            //g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 0x0FFFFFFF)
        {
            Socp_printf(" socp_encode_task_stress_003 break!\n");
            break;
        }
        msleep(g_ulSocpDelay);
    }

    //msleep(100);
    //kfree(packet);
    TM_socp_free(packet);

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_encode_task_stress_004(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int len = pCase->u32DataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    BSP_U8 bd[8];
    int vfcnt = 0;
    int c;
    SOCP_BUFFER_RW_STRU Buffer;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //Socp_printf("%s[%d], chan=%d\n", __FUNCTION__, __LINE__, pCase->SrcCh);
    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);

    if(!packet)
    {
        Socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(1)
    {
        CHECK_RET(bsp_socp_get_rd_buffer(pCase->SrcCh, &Buffer), BSP_OK);
        len = Buffer.u32Size + Buffer.u32RbSize;
        if(len)
        {
            CHECK_RET(bsp_socp_read_rd_done(pCase->SrcCh, len), BSP_OK);
        }

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
            //g_socpTxTotal[c]++;
        }
        else
        {
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 0x0FFFFFFF)
        {
            Socp_printf(" socp_encode_task_stress_004 break!\n");
            break;
        }
        msleep(g_ulSocpDelay);
    }

    //msleep(100);
    //kfree(packet);
    TM_socp_free(packet);

    //Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_U8 g_StdDecSrcT0[29] = {0x7e, 0x00, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0xe1, 0x1e, 0x7e};
BSP_U8 g_StdDecSrcT1[29] = {0x7e, 0x01, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x9a, 0x1a, 0x7e};
BSP_U8 g_StdDecSrcT2[29] = {0x7e, 0x02, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x17, 0x16, 0x7e};
BSP_U8 g_StdDecSrcT3[29] = {0x7e, 0x03, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                            0x07, 0x6c, 0x12, 0x7e};

BSP_U8 g_StdMinDecSrcT0[6] = {0x7e, 0x00, 0xa5, 0xe0, 0xfd, 0x7e};
BSP_U8 g_StdMinDecSrcT1[6] = {0x7e, 0x01, 0xa5, 0x38, 0xe4, 0x7e}; // min and max correspding to data type 1
BSP_U8 g_StdMinDecSrcT2[6] = {0x7e, 0x02, 0xa5, 0x50, 0xce, 0x7e};
BSP_U8 g_StdMinDecSrcT3[6] = {0x7e, 0x03, 0xa5, 0x88, 0xd7, 0x7e};

BSP_U8 g_StdMaxDecSrcHead[18] = {0x7e, 0x01, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00, 0x00, 0x05,
                               0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c, 0x0d};
BSP_U8 g_StdMaxDecSrcEnd[3]  = {0x98, 0x1d, 0x7e};

BSP_U8 g_StdDecSrcNoDataType[28] = {0x7e, 0x01, 0x02, 0x03, 0x04, 0x64, 0x00, 0x00,
                            0x00, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c,
                            0x0d, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                            0xee, 0x35, 0x2e, 0x7e};

BSP_U32 u32StrDecSendCnt = 0;

BSP_S32 socp_decode_task001(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        Socp_printf("0x%x, 0x%x, 0x%x ,0x%p\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt, WtBuff.pBuffer);
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
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task013(BSP_VOID *param)
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
        bsp_log("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcNoDataType, len);

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
    }

    TM_socp_free(packet);
    bsp_log("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task002(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdMinDecSrcT1, len);
    Socp_printf(" len is %d\n",len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);

    return 0;
}


BSP_S32 socp_decode_task003(BSP_VOID *param)
{
    SOCP_ST_CASE_DECODER_S *pCase = (SOCP_ST_CASE_DECODER_S*)param;
    int cnt = pCase->u32sendDataCnt;
    int len = pCase->u32sendDataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int i,j,c;
    BSP_U8  packetMain[258];

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;

    for(i=0;i<(0x7e);i++)
    {
        packetMain[i] = i;
    }
    packetMain[0x7e] = 0x5d;
    packetMain[0x7f] = 0x7d;
    packetMain[0x80] = 0x5e;
    for(i= 0x81;i<0x102;i++)
    {
        packetMain[i] = i-2;
    }

    /*for(i=0;i<258;i++)
    {
        Socp_printf("line %d :the value is %d\n",i, packetMain[i]);
    }*/
    memcpy(packet, g_StdMaxDecSrcHead, 18);
    for(j=0;j<7;j++)
    {
        memcpy(packet+18+(j*258), packetMain, 258);
    }
    memcpy(packet+1824, packetMain, 218);
    memcpy(packet+2042, g_StdMaxDecSrcEnd, 3);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task004(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);
    packet[0] = 0xa5;

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task005(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);
    packet[27] = 0xa5;

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);
    return 0;
}

BSP_S32 socp_decode_task006(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);
    packet[1] = 0x06;

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);
    return 0;
}

BSP_S32 socp_decode_task007(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);
    return 0;
}

BSP_S32 socp_decode_task008(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task009(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT0, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    msleep(10);

    memcpy(packet, g_StdDecSrcT1, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    msleep(10);

    memcpy(packet, g_StdDecSrcT2, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    msleep(10);

    memcpy(packet, g_StdDecSrcT3, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);

    return 0;
}

BSP_S32 socp_decode_task010(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    //memcpy(packet, g_StdMinDecSrcT0, len);
    memcpy(packet, g_StdDecSrcT0, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    //memcpy(packet, g_StdMinDecSrcT1, len);
    memcpy(packet, g_StdDecSrcT1, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    //memcpy(packet, g_StdMinDecSrcT2, len);
    memcpy(packet, g_StdDecSrcT2, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    //memcpy(packet, g_StdMinDecSrcT3, len);
    memcpy(packet, g_StdDecSrcT3, len);
    cnt = (pCase->u32sendDataCnt)/4;
    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_S32 socp_decode_task011(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    //memcpy(packet, g_StdMinDecSrcT0, len);
    memcpy(packet, g_StdDecSrcT0, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}


BSP_S32 socp_decode_task_stress_001(BSP_VOID *param)
{
    SOCP_ST_CASE_DECODER_S *pCase = (SOCP_ST_CASE_DECODER_S*)param;
    int lenDiv;
    int len = pCase->u32sendDataLen;
    BSP_U8  *packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;
    int c;
    lenDiv = len/4;

    c = pCase->SrcCh&0xff;
    g_socpTxTotal[c] = 0;

    //packet = kmalloc(len, GFP_KERNEL);
    packet = (BSP_U8*)TM_socp_malloc(len);
    if(!packet)
    {
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT0, lenDiv);
    memcpy((packet+lenDiv), g_StdDecSrcT1, lenDiv);
    memcpy((packet+lenDiv*2), g_StdDecSrcT2, lenDiv);
    memcpy((packet+lenDiv*3), g_StdDecSrcT3, lenDiv);

    while(1)
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
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 0x0FFFFFFF)
        {
            break;
        }
        msleep(g_ulSocpDelay);
    }

    //kfree(packet);
    TM_socp_free(packet);
    bsp_log("socp_decode_task_stress_001 done.\n");

    return BSP_OK;
}

BSP_S32 socp_decode_task012(BSP_VOID *param)
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    //g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(cnt)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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

    Socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);
    //kfree(packet);
    TM_socp_free(packet);

    return 0;
}

BSP_S32 socp_decode_dcore_task_stress(BSP_VOID *param)
{
    SOCP_ST_CASE_DECODER_S *pCase = (SOCP_ST_CASE_DECODER_S*)param;
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
        Socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    memcpy(packet, g_StdDecSrcT1, len);

    while(1)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
//        Socp_printf("0x%x, 0x%x, 0x%x\n", WtBuff.u32Size, WtBuff.u32RbSize, cnt);
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
            g_socpTxTotal[c]++;
        }
        else
        {
            vfcnt++;
            msleep(g_ulSocpDelay);
        }

        if(vfcnt > 50)
        {
            break;
        }
        u32StrDecSendCnt++;
        if(9999 == u32StrDecSendCnt%10000)
        {
            Socp_printf("decoder stress send cnt is %d\n",u32StrDecSendCnt);
        }
        if(u32StrDecSendCnt >0xFFFFFFF0)
        {
            u32StrDecSendCnt = 0;
        }
        msleep(g_ulSocpDelay);
    }

    TM_socp_free(packet);
    bsp_log("socp_decode_dcore_task_stress break.\n");

    return BSP_OK;
}

/* 编码测试, APP CPU发APP CPU收，固定长度块式数据包 */
BSP_S32 SOCP_ST_ENCODE_001_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);
    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 2000), BSP_OK);

    sprintf(taskName,"socpTest%02d",1);

    g_stCase[0].TaskId = kthread_run(socp_encode_task001, (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		Socp_printf("create kthread socp_enccode_task001 failed!\n");
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

/* 编码测试, APP CPU发APP CPU收，不固定长度块式数据包 */
BSP_S32 SOCP_ST_ENCODE_002_START(void)
{
    char taskName[30] = {0};

    Socp_printf("SOCP_ST_ENCODE_002\n");

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",2);

    g_stCase[0].TaskId = kthread_run(socp_encode_task002, (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_002_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 编码测试, APP CPU发APP CPU收，固定长度BD链表 */
BSP_S32 SOCP_ST_ENCODE_003_START(void)
{
    char taskName[30] = {0};

    Socp_printf("SOCP_ST_ENCODE_003\n");

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitChannel(&g_stCase[1]), BSP_OK);

    sprintf(taskName,"socpTest%02d",3);

    g_stCase[1].TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(&g_stCase[1]), taskName);
    if(IS_ERR(g_stCase[1].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_003_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[1].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[1].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[1].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[1].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[1].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[1].TaskId)
    {
    	//kthread_stop(g_stCase[1].TaskId);
        g_stCase[1].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 编码测试, APP CPU发APP CPU收，固定长度BD链表，发BD前回收RD */
BSP_S32 SOCP_ST_ENCODE_004_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitChannel(&g_stCase[1]), BSP_OK);

    sprintf(taskName,"socpTest%02d",4);

    g_stCase[1].TaskId = kthread_run(socp_encode_task004,  (BSP_VOID*)(&g_stCase[1]), taskName);
    if(IS_ERR(g_stCase[1].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_004_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[1].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[1].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[1].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[1].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[1].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[1].TaskId)
    {
    	//kthread_stop(g_stCase[1].TaskId);
        g_stCase[1].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
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


/* 编码测试, MODEM CPU发APP CPU收，固定长度BD链表 */
BSP_S32 SOCP_ST_ENCODE_007_START(void)
{
    g_ul_rev_pkt_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStSetEncDst(&g_stCase[1]), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(g_stCase[1].DstCh, g_stCase[1].ReadCb), BSP_OK);

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_007_STOP(void)
{
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[1].DstCh), BSP_OK);
    /*释放申请的内存*/
    if(g_stCase[1].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[1].bDstSet = FALSE;
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
		Socp_printf("create kthread socp_decode_task001 failed!\n");
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
		Socp_printf("create kthread socp_decode_task001 failed!\n");
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


/* 编码测试, APP CPU发APP CPU收, 测试bypass模式 */
BSP_S32 SOCP_ST_ENCODE_011_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;
    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[4]), BSP_OK);

    sprintf(taskName,"socpTest%02d",10);

    g_stCase[4].TaskId = kthread_run(socp_encode_task008,  (BSP_VOID*)(&g_stCase[4]), taskName);
    if(IS_ERR(g_stCase[4].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_011_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[4].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[4].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[4].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[4].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[4].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[4].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[4].TaskId)
    {
    	//kthread_stop(g_stCase[4].TaskId);
        g_stCase[4].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }
    return 0;
}

/* 编码测试,目标通道接收数据唯一性测试*/
BSP_U32 g_ulEncDstChanID;
BSP_S32 SOCP_ST_ENCODE_012_START(void)
{
    int i;
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    /* 保存目的通道ID */
    g_ulEncDstChanID = g_stCase[0].DstCh;

    DEV_INIT();

    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        pCase->bDstSet = FALSE;
        pCase->DstCh = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
        CHECK_RET(SocpStSetEncDst(pCase), BSP_OK);
    }

    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        pCase->DstCh = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
        CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_012_STOP(void)
{
    BSP_U32 i = 0;
    BSP_U32 dstChanID;

    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        dstChanID = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN, i);
        CHECK_RET(socp_soft_free_encdst_chan(dstChanID), BSP_OK);
    }

    /*释放申请的内存*/
    for(i=0;i<SOCP_MAX_ENCDST_CHN;i++)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    //编码目的通道内存
    g_stCase[0].bDstSet = FALSE;
    /* 恢复目的通道ID */
    g_stCase[0].DstCh = g_ulEncDstChanID;

    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    return 0;
}

/* 编码测试,改变data type 测试*/
BSP_S32 SOCP_ST_ENCODE_013_START(void)
{
    char taskName[30] = {0};

    g_ul_rev_pkt_flag = false;
    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[5]), BSP_OK);

    sprintf(taskName,"socpTest%02d",10);

    g_stCase[5].TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(&g_stCase[5]), taskName);
    if(IS_ERR(g_stCase[5].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_013_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[5].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[5].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[5].DstCh), BSP_OK);

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[5].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[5].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[5].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[5].TaskId)
    {
    	//kthread_stop(g_stCase[5].TaskId);
        g_stCase[5].TaskId = NULL;
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 编码测试,测试数据包长为1的情况*/
BSP_S32 SOCP_ST_ENCODE_014_START(void)
{
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    g_ul_rev_pkt_flag = false;

    DEV_INIT();
    pCase->u32DataLen = 1;
    pCase->u32DataCnt = 200;
    pCase->eDataType  = SOCP_DATA_TYPE_3;

    CHECK_RET(SocpStSetEncDst(&g_stCase[0]), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_014_STOP(void)
{
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }
    Socp_printf("dstsetflag is %d,line is %d\n",g_stCase[0].bDstSet,__LINE__);

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 编码测试,测试数据包长为2048的情况*/
BSP_S32 SOCP_ST_ENCODE_015_START(void)
{
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    g_ul_rev_pkt_flag = false;

    DEV_INIT();

    pCase->u32InputSize = 0x10000;
    pCase->u32OutputSize = 0x2000;
    pCase->u32Threshold = 1024;
    pCase->u32DataLen = 2024;
    pCase->u32DataCnt = 1;

    CHECK_RET(SocpStSetEncDst(&g_stCase[0]), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase->DstCh, pCase->ReadCb), BSP_OK);

    return 0;

}

BSP_S32 SOCP_ST_ENCODE_015_STOP(void)
{
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }
    Socp_printf("dstsetflag is %d,line is %d\n",g_stCase[0].bDstSet,__LINE__);

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 编码测试,测试包头错误 */
BSP_S32 SOCP_ST_ENCODE_016_START(void)
{
    char taskName[30] = {0};

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",10);

    g_stCase[0].TaskId = kthread_run(socp_encode_task011,  (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_016_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //
    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }

    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    if(g_ul_event_flag == false)
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
		Socp_printf("create kthread socp_decode_task001 failed!\n");
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


/* 编码测试，多通道测试 */
BSP_S32 SOCP_ST_ENCODE_018_START(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase1 = &g_stCase[0];
    SOCP_ST_CASE_S *pCase2 = &g_stCase[1];

    DEV_INIT();

    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase1), BSP_OK);
    //CHECK_RET(SocpStSetEncDst(pCase2), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase1), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase2), BSP_OK);
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
    CHECK_RET(bsp_socp_register_event_cb(pCase1->DstCh, pCase1->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase1->DstCh, SocpStReadCB_3), BSP_OK);
    //CHECK_RET(bsp_socp_register_event_cb(pCase2->DstCh, pCase2->EventCb), BSP_OK);
    //CHECK_RET(bsp_socp_register_read_cb(pCase2->DstCh, SocpStReadCB_3), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase1->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase2->SrcCh), BSP_OK);

    sprintf(taskName,"socpTest%03d",181);

    pCase1->TaskId = kthread_run(socp_encode_task013,  (BSP_VOID*)(pCase1), taskName);
    if(IS_ERR(pCase1->TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    pCase2->TaskId = kthread_run(socp_encode_task003,  (BSP_VOID*)(pCase2), taskName);
    if(IS_ERR(pCase2->TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_ENCODE_018_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_stop(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[1].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);
    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[1].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }
    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }
    if(g_stCase[1].TaskId)
    {
    	//kthread_stop(g_stCase[1].TaskId);
        g_stCase[1].TaskId = NULL;
    }

    return 0;
}


BSP_BOOL bTestEncode19 = BSP_FALSE;
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
    Socp_printf("0x%x 0x%x 0x%x 0x%x\n",pCase0->SrcCh,pCase1->SrcCh,pCase2->SrcCh,pCase3->SrcCh);
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

/* SOCP工作状态测试: 忙碌 */
BSP_S32 SOCP_ST_ENCODE_022_START(void)
{
    char taskName[30] = {0};
    SOCP_STATE_ENUM_UINT32 state;

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);
    sprintf(taskName,"socpTest%02d",1);

    g_stCase[0].TaskId = kthread_run(socp_encode_task001, (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		Socp_printf("create kthread socp_enccode_task001 failed!\n");
        return BSP_ERROR;
    }

    msleep(20);
    state = bsp_socp_get_state();
    if(SOCP_BUSY == state)
    {
        printk("SOCP_ST_ENCODE_022: BUSY TEST SUCCEED\n");
    }
    else
    {
        printk("SOCP_ST_ENCODE_022: BUSY TEST FAILED\n");
    }

    return 0;
}

/* SOCP工作状态测试: 忙碌 */
BSP_S32 SOCP_ST_ENCODE_022_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }

    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    return 0;
}

/* SOCP工作状态测试: 空闲 */
BSP_S32 SOCP_ST_ENCODE_023_START(void)
{
    char taskName[30] = {0};

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);
    sprintf(taskName,"socpTest%02d",1);

    g_stCase[0].TaskId = kthread_run(socp_encode_task001, (BSP_VOID*)(&g_stCase[0]), taskName);
    if(IS_ERR(g_stCase[0].TaskId))
    {
		Socp_printf("create kthread socp_enccode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

/* SOCP工作状态测试: 空闲 */
BSP_S32 SOCP_ST_ENCODE_023_STOP(void)
{
    SOCP_STATE_ENUM_UINT32 state;
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[0].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[0].SrcCh), BSP_OK);

    CHECK_RET(socp_soft_free_encdst_chan(g_stCase[0].DstCh), BSP_OK);

    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stCase[0].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }
    /*释放申请的内存*/
    if(g_stCase[0].bDstSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stCase[0].bDstSet = FALSE;
    }

    /*释放任务*/
    if(g_stCase[0].TaskId)
    {
    	//kthread_stop(g_stCase[0].TaskId);
        g_stCase[0].TaskId = NULL;
    }

    msleep(500);
    state = bsp_socp_get_state();
    if(SOCP_IDLE == state)
    {
        printk("SOCP_ST_ENCODE_022: IDLE TEST SUCCEED\n");
    }
    else
    {
        printk("SOCP_ST_ENCODE_022: IDLE TEST FAILED\n");
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
		Socp_printf("create kthread socp_decode_task001 failed!\n");
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



/* 解码测试传输阈值测试 */
BSP_S32 SOCP_ST_DECODE_002_START(void)
{
    char taskName[30] = {0};
    DEV_INIT();

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[5]), BSP_OK);
    //bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 2000);

    sprintf(taskName,"socpTest%02d",2);
    g_stDecCase[5].TaskId = kthread_run(socp_decode_task001,  (BSP_VOID*)(&g_stDecCase[5]), taskName);
    if(IS_ERR(g_stDecCase[5].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_002_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[5].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[5].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[5].DstCh), BSP_OK);


    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[5].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[5].bSrcSet = FALSE;
    }

    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
    //(BSP_VOID)taskDelete(g_stDecCase[5].TaskId);
    if(g_stDecCase[5].TaskId)
    {
    	//kthread_stop(g_stDecCase[5].TaskId);
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试 测试data type匹配*/
BSP_S32 SOCP_ST_DECODE_003_START(void)
{
    char taskName[30] = {0};
    DEV_INIT();

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[6]), BSP_OK);
    //bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 0);

    sprintf(taskName,"socpTest%02d",3);
    g_stDecCase[6].TaskId = kthread_run(socp_decode_task001,  (BSP_VOID*)(&g_stDecCase[6]), taskName);
    if(IS_ERR(g_stDecCase[6].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_003_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[6].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[6].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[6].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[6].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[6].bSrcSet = FALSE;
    }
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    //(BSP_VOID)taskDelete(g_stDecCase[6].TaskId);
    if(g_stDecCase[6].TaskId)
    {
    	//kthread_stop(g_stDecCase[6].TaskId);
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 解码测试发送一个数据包测试 */
BSP_S32 SOCP_ST_DECODE_004_START(void)
{
    char taskName[30] = {0};
    DEV_INIT();

    g_ul_rev_pkt_flag = false;

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[7]), BSP_OK);
    //bsp_socp_set_timeout(SOCP_TIMEOUT_TRF, 0);

    sprintf(taskName,"socpTest%02d",4);
    g_stDecCase[7].TaskId = kthread_run(socp_decode_task001,  (BSP_VOID*)(&g_stDecCase[7]), taskName);
    if(IS_ERR(g_stDecCase[7].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_004_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[7].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[7].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[7].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[7].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[7].bSrcSet = FALSE;
    }
    //socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    //(BSP_VOID)taskDelete(g_stDecCase[7].TaskId);
    if(g_stDecCase[7].TaskId)
    {
    	//kthread_stop(g_stDecCase[7].TaskId);
    }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试数据包长度为6，最小值 */
BSP_S32 SOCP_ST_DECODE_005_START(void)
{
    char taskName[30] = {0};
    SOCP_DEC_PKTLGTH_STRU  pPktlgth;
    pPktlgth.u32PktMax = 2;
    pPktlgth.u32PktMin = 6;

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[8]), BSP_OK);
    bsp_socp_set_dec_pkt_lgth(&pPktlgth);

    sprintf(taskName,"socpTest%02d",5);
    g_stDecCase[8].TaskId = kthread_run(socp_decode_task002,  (BSP_VOID*)(&g_stDecCase[8]), taskName);
    if(IS_ERR(g_stDecCase[8].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_005_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[8].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[8].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[8].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[8].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[8].bSrcSet = FALSE;
    }
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    if(g_stDecCase[8].TaskId)
    {
    	//kthread_stop(g_stDecCase[8].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试最大数据包长度 2024 */
BSP_S32 SOCP_ST_DECODE_006_START(void)
{
    char taskName[30] = {0};
    SOCP_DEC_PKTLGTH_STRU  pPktlgth;
    pPktlgth.u32PktMax = 2;
    pPktlgth.u32PktMin = 0;

    g_ul_rev_pkt_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[9]), BSP_OK);
    bsp_socp_set_dec_pkt_lgth(&pPktlgth);

    sprintf(taskName,"socpTest%02d",6);
    g_stDecCase[9].TaskId = kthread_run(socp_decode_task003,  (BSP_VOID*)(&g_stDecCase[9]), taskName);
    if(IS_ERR(g_stDecCase[9].TaskId))
    {
		Socp_printf("create kthread socp_decode_task001 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_006_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[9].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[9].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[9].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[9].bSrcSet = FALSE;
    }
   // kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    //(BSP_VOID)taskDelete(g_stDecCase[9].TaskId);
   if(g_stDecCase[9].TaskId)
   {
      // kthread_stop(g_stDecCase[9].TaskId);
   }

    if(g_ul_rev_pkt_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试 包头异常*/
BSP_S32 SOCP_ST_DECODE_007_START(void)
{
    char taskName[30] = {0};

    g_ul_event_flag = false;
    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",7);
    g_stDecCase[0].TaskId = kthread_run(socp_decode_task004,  (BSP_VOID*)(&g_stDecCase[0]), taskName);
    if(IS_ERR(g_stDecCase[0].TaskId))
    {
		Socp_printf("create kthread socp_decode_task004 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}


BSP_S32 SOCP_ST_DECODE_007_STOP(void)
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
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    //(BSP_VOID)taskDelete(g_stDecCase[0].TaskId);
    if(g_stDecCase[0].TaskId)
    {
    	//kthread_stop(g_stDecCase[0].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试crc校验错 */
BSP_S32 SOCP_ST_DECODE_008_START(void)
{
    char taskName[30] = {0};

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",8);
    g_stDecCase[0].TaskId = kthread_run(socp_decode_task005,  (BSP_VOID*)(&g_stDecCase[0]), taskName);
    if(IS_ERR(g_stDecCase[0].TaskId))
    {
		Socp_printf("create kthread socp_decode_task004 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_ST_DECODE_008_STOP(void)
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
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    if(g_stDecCase[0].TaskId)
    {
    	//kthread_stop(g_stDecCase[0].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}



/* 解码测试,包长错误,小于 最小包长，需要重启单板 */
BSP_S32 SOCP_ST_DECODE_009_START(void)
{
    char taskName[30] = {0};
    SOCP_DEC_PKTLGTH_STRU pPktlgth;
    pPktlgth.u32PktMax = 1;
    pPktlgth.u32PktMin = 20;

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[8]), BSP_OK);
    bsp_socp_set_dec_pkt_lgth(&pPktlgth);

    sprintf(taskName,"socpTest%02d",1);
    g_stDecCase[8].TaskId = kthread_run(socp_decode_task002,  (BSP_VOID*)(&g_stDecCase[8]), taskName);
    if(IS_ERR(g_stDecCase[8].TaskId))
    {
		Socp_printf("create kthread socp_decode_task002 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}


BSP_S32 SOCP_ST_DECODE_009_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[8].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[8].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[8].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[8].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[8].bSrcSet = FALSE;
    }
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    //(BSP_VOID)taskDelete(g_stDecCase[8].TaskId);
    if(g_stDecCase[8].TaskId)
    {
    	//kthread_stop(g_stDecCase[8].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }


    return 0;
}

/* 解码测试,包长错误,大 于 最大包长 */
BSP_S32 SOCP_ST_DECODE_010_START(void)
{
    char taskName[30] = {0};
    SOCP_DEC_PKTLGTH_STRU pPktlgth;

    g_ul_event_flag = false;

    pPktlgth.u32PktMax = 5;
    pPktlgth.u32PktMin = 0;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[9]), BSP_OK);
    bsp_socp_set_dec_pkt_lgth(&pPktlgth);

    sprintf(taskName,"socpTest%02d",1);

    g_stDecCase[9].TaskId = kthread_run(socp_decode_task003,  (BSP_VOID*)(&g_stDecCase[9]), taskName);
    if(IS_ERR(g_stDecCase[9].TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}


BSP_S32 SOCP_ST_DECODE_010_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[9].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[9].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[9].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);

    if(g_stDecCase[9].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[9].bSrcSet = FALSE;
    }
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    if(g_stDecCase[9].TaskId)
    {
    	//kthread_stop(g_stDecCase[9].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码测试 data type测试 无效值*/
BSP_S32 SOCP_ST_DECODE_011_START(void)
{
    char taskName[30] = {0};

    g_ul_event_flag = false;


    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[0]), BSP_OK);

    sprintf(taskName,"socpTest%02d",1);
    g_stDecCase[0].TaskId = kthread_run(socp_decode_task006,  (BSP_VOID*)(&g_stDecCase[0]), taskName);
    if(IS_ERR(g_stDecCase[0].TaskId))
    {
		Socp_printf("create kthread socp_decode_task006 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}


BSP_S32 SOCP_ST_DECODE_011_STOP(void)
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
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    if(g_stDecCase[0].TaskId)
    {
    	//kthread_stop(g_stDecCase[0].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

/* 解码测试buffer下溢错误 */
BSP_S32 SOCP_ST_DECODE_012_START(void)
{
    char taskName[30] = {0};

    g_ul_event_flag = false;

    DEV_INIT();

    CHECK_RET(SocpStInitDecChannel(&g_stDecCase[10]), BSP_OK);

    sprintf(taskName,"socpTest%02d",1);
    g_stDecCase[10].TaskId = kthread_run(socp_decode_task007,  (BSP_VOID*)(&g_stDecCase[10]), taskName);
    if(IS_ERR(g_stDecCase[10].TaskId))
    {
		Socp_printf("create kthread socp_decode_task002 failed!\n");
        return BSP_ERROR;
    }

    return 0;
}


BSP_S32 SOCP_ST_DECODE_012_STOP(void)
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[10].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[10].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stDecCase[10].DstCh), BSP_OK);

    TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    if(g_stDecCase[10].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[10].bSrcSet = FALSE;
    }
    //kfree(g_pSocpBuf[--g_SocpBufCnt]);
        /*释放任务*/
    if(g_stDecCase[10].TaskId)
    {
    	//kthread_stop(g_stDecCase[10].TaskId);
    }

    if(g_ul_event_flag == false)
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_U32 u32DecDstId[16];
/* 解码测试输入输出一对四 */
BSP_S32 SOCP_ST_DECODE_013_START(void)
{
    char taskName[30] = {0};

    SOCP_ST_CASE_DECODER_S *pCaseDec0 = &g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec1 = g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec2 = g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec3 = g_stDecCase[0];


    DEV_INIT();

    memset(u32DecDstId, 0, sizeof(BSP_U32)*16);
    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
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

    sprintf(taskName,"socpTestDec013");
    pCaseDec0->TaskId = kthread_run(socp_decode_task009,  (BSP_VOID*)(pCaseDec0), taskName);
    if(IS_ERR(pCaseDec0->TaskId))
    {
		Socp_printf("create kthread socp_decode_task009 failed!\n");
        return BSP_ERROR;
    }

    CHECK_RET(bsp_socp_start(pCaseDec0->SrcCh), BSP_OK);

    return BSP_OK;
}


BSP_S32 SOCP_ST_DECODE_013_STOP(void)
{
    BSP_U32 i = 0;
    BSP_U32 u32DstId = 0;

    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stDecCase[0].SrcCh), BSP_OK);
    CHECK_RET(socp_soft_free_decsrc_chan(g_stDecCase[0].SrcCh), BSP_OK);
    for(i=0;i<4;i++)
    {
        u32DstId = u32DecDstId[i];
        CHECK_RET(bsp_socp_free_channel(u32DstId), BSP_OK);
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
    }

    if(g_stDecCase[0].bSrcSet)
    {
        TM_socp_free(g_pSocpBuf[--g_SocpBufCnt]);
        g_stDecCase[0].bSrcSet = FALSE;
    }

    /* 恢复目的通道ID */
    g_stDecCase[0].DstCh = SOCP_DECODER_DEST_CHAN_0;
    /*释放任务*/
    if(g_stDecCase[0].TaskId)
    {
        kthread_stop(g_stDecCase[0].TaskId);
    }

    return 0;
}


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
		Socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_2");
    pCaseDec4->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDec4), taskName);
    if(IS_ERR(pCaseDec4->TaskId))
    {
		Socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_3");
    pCaseDec8->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDec8), taskName);
    if(IS_ERR(pCaseDec8->TaskId))
    {
		Socp_printf("create kthread socp_decode_task011 failed!\n");
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTestDec014_4");
    pCaseDecc->TaskId = kthread_run(socp_decode_task011,  (BSP_VOID*)(pCaseDecc), taskName);
    if(IS_ERR(pCaseDecc->TaskId))
    {
		Socp_printf("create kthread socp_decode_task011 failed!\n");
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

BSP_S32 SOCP_ST_BUSSTRESS_TEST(void)
{
    SOCP_ST_CASE_S *pCase0 = &g_stCase[17];
    SOCP_ST_CASE_S *pCase1 = &g_stCase[19];

    pCase0->u32OutputSize = 0x400000;
    pCase0->u32EncDstThrh = 0x2110;
    pCase0->u32Threshold = 0x300000;

    pCase1->u32OutputSize  = 0x400000;
    pCase1->u32EncDstThrh  = 0x2110;
    pCase1->u32Threshold = 0x300000;

    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase1), BSP_OK);

    CHECK_RET(bsp_socp_register_read_cb(pCase0->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase1->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);

    return 0;
}

//BSP_BOOL bTestEncodeStress = BSP_FALSE;
/* 编码测试，多通道测试 , 多输入，多输出*/
BSP_S32 SOCP_ST_ENCODE_STRESS(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase0 = &g_stCase[17];
    SOCP_ST_CASE_S *pCase1 = &g_stCase[18];
    SOCP_ST_CASE_S *pCase2 = &g_stCase[19];
    SOCP_ST_CASE_S *pCase3 = &g_stCase[20];
    SOCP_ST_CASE_S *pCase4 = &g_stCase[21];
    SOCP_ST_CASE_S *pCase5 = &g_stCase[22];

    DEV_INIT();

    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase0), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase2), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase4), BSP_OK);
    CHECK_RET(SocpStSetEncDst(pCase5), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase0), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase1), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase2), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase3), BSP_OK);;
    CHECK_RET(SocpStAllocEncSrc(pCase4), BSP_OK);
    CHECK_RET(SocpStAllocEncSrc(pCase5), BSP_OK);
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
    if(pCase4->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase4->SrcCh, pCase4->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase4->SrcCh, pCase4->EventCb), BSP_OK);
    if(pCase5->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase5->SrcCh, pCase5->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase0->DstCh, pCase0->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase2->DstCh, pCase2->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase4->DstCh, pCase4->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase5->DstCh, pCase5->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase0->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase2->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase4->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCase5->DstCh, SocpStReadCB_Enc_Stress), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase0->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase1->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase2->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase3->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase4->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCase5->SrcCh), BSP_OK);


    sprintf(taskName,"socpTest%03d",210);
    pCase0->TaskId = kthread_run(socp_encode_task_stress_001,  (BSP_VOID*)(pCase0), taskName);
    if(IS_ERR(pCase0->TaskId))
    {
        return BSP_ERROR;
    }
    sprintf(taskName,"socpTest%03d",211);
    pCase1->TaskId = kthread_run(socp_encode_task_stress_002,  (BSP_VOID*)(pCase1), taskName);
    if(IS_ERR(pCase1->TaskId))
    {
        return BSP_ERROR;
    }
    sprintf(taskName,"socpTest%03d",212);
    pCase2->TaskId = kthread_run(socp_encode_task_stress_003,  (BSP_VOID*)(pCase2), taskName);
    if(IS_ERR(pCase2->TaskId))
    {
        return BSP_ERROR;
    }
    sprintf(taskName,"socpTest%03d",213);
    pCase3->TaskId = kthread_run(socp_encode_task_stress_004,  (BSP_VOID*)(pCase3), taskName);
    if(IS_ERR(pCase3->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",215);
    pCase5->TaskId = kthread_run(socp_encode_task_stress_004,  (BSP_VOID*)(pCase5), taskName);
    if(IS_ERR(pCase3->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}


/* 解码压力测试，四对十六通道测试*/
BSP_S32 SOCP_ST_DECODE_STRESS(void)
{
    char taskName[30] = {0};

    SOCP_DEC_PKTLGTH_STRU pPktlgth = {0,0};

    SOCP_ST_CASE_DECODER_S *pCaseDec0 = &g_stDecCase[12];
    SOCP_ST_CASE_DECODER_S  pCaseDec1 = g_stDecCase[12];
    SOCP_ST_CASE_DECODER_S  pCaseDec2 = g_stDecCase[12];
    SOCP_ST_CASE_DECODER_S  pCaseDec3 = g_stDecCase[12];

    SOCP_ST_CASE_DECODER_S *pCaseDec4 = &g_stDecCase[13];
    SOCP_ST_CASE_DECODER_S  pCaseDec5 = g_stDecCase[13];
    SOCP_ST_CASE_DECODER_S  pCaseDec6 = g_stDecCase[13];
    SOCP_ST_CASE_DECODER_S  pCaseDec7 = g_stDecCase[13];

    SOCP_ST_CASE_DECODER_S *pCaseDec8 = &g_stDecCase[14];
    SOCP_ST_CASE_DECODER_S  pCaseDec9 = g_stDecCase[14];
    SOCP_ST_CASE_DECODER_S  pCaseDeca = g_stDecCase[14];
    SOCP_ST_CASE_DECODER_S  pCaseDecb = g_stDecCase[14];

    SOCP_ST_CASE_DECODER_S *pCaseDecc = &g_stDecCase[15];
    SOCP_ST_CASE_DECODER_S  pCaseDecd = g_stDecCase[15];
    SOCP_ST_CASE_DECODER_S  pCaseDece = g_stDecCase[15];
    SOCP_ST_CASE_DECODER_S  pCaseDecf = g_stDecCase[15];

    pPktlgth.u32PktMax = 1;
    pPktlgth.u32PktMin = 0;


    DEV_INIT();

    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);

    bsp_socp_set_dec_pkt_lgth(&pPktlgth);
    CHECK_RET(SocpStSetDecSrc(pCaseDec0), BSP_OK);


    pCaseDec0->eDataType = SOCP_DATA_TYPE_0;
    CHECK_RET(SocpStAllocDecDst(pCaseDec0), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec0->DstCh, pCaseDec0->ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec0->SrcCh, pCaseDec0->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec0->DstCh, pCaseDec0->EventCb), BSP_OK);

    pCaseDec1.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec1.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 4);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec1), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec1.DstCh, pCaseDec1.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec1.SrcCh, pCaseDec1.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec1.DstCh, pCaseDec1.EventCb), BSP_OK);

    pCaseDec2.eDataType = SOCP_DATA_TYPE_2;
    pCaseDec2.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 8);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec2), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec2.DstCh, pCaseDec2.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec2.SrcCh, pCaseDec2.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec2.DstCh, pCaseDec2.EventCb), BSP_OK);

    pCaseDec3.eDataType = SOCP_DATA_TYPE_3;
    pCaseDec3.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 12);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec3), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec3.DstCh, pCaseDec3.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec3.SrcCh, pCaseDec3.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec3.DstCh, pCaseDec3.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDec4), BSP_OK);

    pCaseDec4->eDataType = SOCP_DATA_TYPE_0;
    pCaseDec4->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 1);
    CHECK_RET(SocpStAllocDecDst(pCaseDec4), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec4->DstCh, pCaseDec4->ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec4->SrcCh, pCaseDec4->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec4->DstCh, pCaseDec4->EventCb), BSP_OK);

    pCaseDec5.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec5.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 5);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec5), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec5.DstCh, pCaseDec5.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec5.SrcCh, pCaseDec5.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec5.DstCh, pCaseDec5.EventCb), BSP_OK);

    pCaseDec6.eDataType = SOCP_DATA_TYPE_2;
    pCaseDec6.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 9);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec6), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec6.DstCh, pCaseDec6.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec6.SrcCh, pCaseDec6.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec6.DstCh, pCaseDec6.EventCb), BSP_OK);

    pCaseDec7.eDataType = SOCP_DATA_TYPE_3;
    pCaseDec7.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 13);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec7), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec7.DstCh, pCaseDec7.ReadCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec7.SrcCh, pCaseDec7.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec7.DstCh, pCaseDec7.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDec8), BSP_OK);

    pCaseDec8->eDataType = SOCP_DATA_TYPE_0;
    pCaseDec8->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 2);
    CHECK_RET(SocpStAllocDecDst(pCaseDec8), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec8->DstCh, pCaseDec8->ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec8->SrcCh, pCaseDec8->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec8->DstCh, pCaseDec8->EventCb), BSP_OK);

    pCaseDec9.eDataType = SOCP_DATA_TYPE_1;
    pCaseDec9.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 6);
    CHECK_RET(SocpStAllocDecDst(&pCaseDec9), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDec9.DstCh, pCaseDec9.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDec9.SrcCh, pCaseDec9.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDec9.DstCh, pCaseDec9.EventCb), BSP_OK);

    pCaseDeca.eDataType = SOCP_DATA_TYPE_2;
    pCaseDeca.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 10);
    CHECK_RET(SocpStAllocDecDst(&pCaseDeca), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDeca.DstCh, pCaseDeca.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDeca.SrcCh, pCaseDeca.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDeca.DstCh, pCaseDeca.EventCb), BSP_OK);

    pCaseDecb.eDataType = SOCP_DATA_TYPE_3;
    pCaseDecb.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 14);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecb), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecb.DstCh, pCaseDecb.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDecb.SrcCh, pCaseDecb.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecb.DstCh, pCaseDecb.EventCb), BSP_OK);

    CHECK_RET(SocpStSetDecSrc(pCaseDecc), BSP_OK);

    pCaseDecc->eDataType = SOCP_DATA_TYPE_0;
    pCaseDecc->DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 3);
    CHECK_RET(SocpStAllocDecDst(pCaseDecc), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecc->DstCh, pCaseDecc->ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDecc->SrcCh, pCaseDecc->EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecc->DstCh, pCaseDecc->EventCb), BSP_OK);

    pCaseDecd.eDataType = SOCP_DATA_TYPE_1;
    pCaseDecd.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 7);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecd), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecd.DstCh, pCaseDecd.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDecd.SrcCh, pCaseDecd.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecd.DstCh, pCaseDecd.EventCb), BSP_OK);

    pCaseDece.eDataType = SOCP_DATA_TYPE_2;
    pCaseDece.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 11);
    CHECK_RET(SocpStAllocDecDst(&pCaseDece), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDece.DstCh, pCaseDece.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDece.SrcCh, pCaseDece.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDece.DstCh, pCaseDece.EventCb), BSP_OK);

    pCaseDecf.eDataType = SOCP_DATA_TYPE_3;
    pCaseDecf.DstCh = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN, 15);
    CHECK_RET(SocpStAllocDecDst(&pCaseDecf), BSP_OK);
    CHECK_RET(bsp_socp_register_read_cb(pCaseDecf.DstCh, pCaseDecf.ReadCb), BSP_OK);

    CHECK_RET(bsp_socp_register_event_cb(pCaseDecf.SrcCh, pCaseDecf.EventCb), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCaseDecf.DstCh, pCaseDecf.EventCb), BSP_OK);

    sprintf(taskName,"socpTest%03d",220);
    pCaseDec0->TaskId = kthread_run(socp_decode_task_stress_001,  (BSP_VOID*)(pCaseDec0), taskName);
    if(IS_ERR(pCaseDec0->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",221);
    pCaseDec4->TaskId = kthread_run(socp_decode_task_stress_001,  (BSP_VOID*)(pCaseDec4), taskName);
    if(IS_ERR(pCaseDec4->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",222);
    pCaseDec8->TaskId = kthread_run(socp_decode_task_stress_001,  (BSP_VOID*)(pCaseDec8), taskName);
    if(IS_ERR(pCaseDec8->TaskId))
    {
        return BSP_ERROR;
    }

    sprintf(taskName,"socpTest%03d",223);
    pCaseDecc->TaskId = kthread_run(socp_decode_task_stress_001,  (BSP_VOID*)(pCaseDecc), taskName);
    if(IS_ERR(pCaseDecc->TaskId))
    {
        return BSP_ERROR;
    }

    CHECK_RET(bsp_socp_start(pCaseDec0->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDec4->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDec8->SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_start(pCaseDecc->SrcCh), BSP_OK);

    return BSP_OK;
}

/*双核编码测试，M核上发送，A核上接收*/
BSP_S32 SOCP_ST_ENCODE_DCORE_STRESS(void)
{
    DEV_INIT();

    if(bEncSrc0Set == BSP_FALSE)
    {
        CHECK_RET(SocpStSetEncDst(&g_stCase[0]), BSP_OK);
        bEncSrc0Set = BSP_TRUE;
    }
    g_stCase[0].ReadCb = SocpStReadCB_Enc_Stress;
    CHECK_RET(bsp_socp_register_read_cb(g_stCase[0].DstCh, g_stCase[0].ReadCb), BSP_OK);

    return 0;
}


#if (FEATURE_SOCP_DECODE_INT_TIMEOUT == FEATURE_ON)
/*测试编解码传输超时中断*/
BSP_S32 SOCP_ST_TIMEOUT(void)
{
    CHECK_RET(bsp_socp_set_decode_timeout_register(DECODE_TIMEOUT_BUTTON),BSP_ERR_SOCP_INVALID_PARA);
    CHECK_RET(bsp_socp_set_decode_timeout_register(DECODE_TIMEOUT_INT_TIMEOUT),BSP_OK);
    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_TRF,256),BSP_ERR_SOCP_INVALID_PARA);
    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_DECODE_TRF,256),BSP_ERR_SOCP_INVALID_PARA);

    return BSP_OK;
}
/*测试设置超时寄存器*/
BSP_S32 SOCP_ST_SET_TIMEOUT(void)
{

    char taskName[30] = {0};
    BSP_U32 time;

    SOCP_ST_CASE_DECODER_S *pCaseDec0 = &g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec1 = g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec2 = g_stDecCase[0];
    SOCP_ST_CASE_DECODER_S pCaseDec3 = g_stDecCase[0];


    DEV_INIT();

    memset(u32DecDstId, 0, sizeof(BSP_U32)*16);
    //CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_BUFOVF_DISABLE, 0), BSP_OK);
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

    sprintf(taskName,"socpTestDec013");
    pCaseDec0->TaskId = kthread_run(socp_decode_task009,  (BSP_VOID*)(pCaseDec0), taskName);
    if(IS_ERR(pCaseDec0->TaskId))
    {
		Socp_printf("create kthread socp_decode_task009 failed!\n");
        return BSP_ERROR;
    }

    CHECK_RET(bsp_socp_start(pCaseDec0->SrcCh), BSP_OK);

    /*2014-2-28 17:18:06 l00258701 新增 的代码*/
    bsp_socp_set_timeout(SOCP_TIMEOUT_TRF,0xFF);

    SOCP_REG_READ(SOCP_REG_INTTIMEOUT,time);
    /*这里设定为0xFF的用意还有测试SOCP_REG_SETBITS
          这个宏后面的一个参数到底应该写什么*/
    if(time == 0xFF)
    {
         Socp_printf("SOCP TEST: DYNAMIC SETTR TIME OUT REGISTER SUCCESS\n");
    }

    return BSP_OK;
}

/*测试当寄存器设定为0时，不上报中断*/
BSP_S32 SOCP_ST_NO_INT_REPORT(void)
{
    char taskName[30] = {0};
    SOCP_ST_CASE_S *pCase = &g_stCase[30];
    BSP_U32 u32Ret;
    u32 IntFlag   = 0;


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

    /*将中断超时寄存器设定为0*/
    CHECK_RET(bsp_socp_set_timeout(SOCP_TIMEOUT_TRF,0),BSP_OK);
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    //sprintf(taskName,"socpTest%03d",210);
    pCase->TaskId = kthread_run(socp_encode_task001,  (BSP_VOID*)(pCase), taskName);

    if(IS_ERR(pCase->TaskId))
    {
        return BSP_ERROR;
    }

    SOCP_REG_READ(SOCP_REG_GBL_INTSTAT, IntFlag);
    /*判断是否有中断上报*/
    if ((IntFlag & SOCP_APP_ENC_TFRINT_MASK) == 0 )
    {
         Socp_printf("SOCP TEST: DYNAMIC SETTR TIME OUT REGISTER SUCCESS\n");
         return BSP_OK;
    }

    return BSP_ERROR;
}
#endif

extern void socp_help(void);
extern void socp_show_debug_gbl(void);
extern void socp_show_ccore_head_err_cnt(void);
extern u32 socp_show_enc_src_chan_cur(u32 u32UniqueId);
extern u32 socp_show_enc_src_chan_add(u32 u32UniqueId);
extern void  socp_show_enc_src_chan_all(void);
extern u32 socp_show_enc_dst_chan_cur(u32 u32UniqueId);
extern u32 socp_show_enc_dst_chan_add(u32 u32UniqueId);
extern void socp_show_enc_dst_chan_all(void);
extern u32 socp_show_dec_src_chan_cur(u32 u32UniqueId);
extern u32 socp_show_dec_src_chan_add(u32 u32UniqueId);
extern void socp_show_dec_src_chan_all(void);
extern u32 socp_show_dec_dst_chan_cur(u32 u32UniqueId);
extern u32 socp_show_dec_dst_chan_add(u32 u32UniqueId);
extern void socp_show_dec_dst_chan_all(void);
extern void socp_debug_cnt_show(void);

BSP_S32 SOCP_ST_DEBUG_TEST(void)
{
    socp_help();
    socp_show_debug_gbl();
    socp_show_ccore_head_err_cnt();

    if(socp_show_enc_src_chan_cur(0) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(socp_show_enc_src_chan_add(0) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    socp_show_enc_src_chan_all();

    if(socp_show_enc_dst_chan_cur(0x10000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(socp_show_enc_dst_chan_add(0x10000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    socp_show_enc_dst_chan_all();

    if(socp_show_dec_src_chan_cur(0x20000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(socp_show_dec_src_chan_add(0x20000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    socp_show_dec_src_chan_all();

    if(socp_show_dec_dst_chan_cur(0x30000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(socp_show_dec_dst_chan_add(0x30000) != BSP_OK)
    {
        printk("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    socp_show_dec_dst_chan_all();

    socp_debug_cnt_show();

    printk("%s PASSED\n", __FUNCTION__);

    return BSP_OK;
}

