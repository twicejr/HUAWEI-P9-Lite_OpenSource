#include <osl_malloc.h>
#include "socp_balong.h"
#include "product_config.h"
#include "osl_thread.h"
#include "osl_malloc.h"
//#include "mdrv.h"

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


//extern BSP_VOID* cacheDmaMalloc(BSP_U32  bytes);
//extern BSP_S32 cacheDmaFree(BSP_VOID*  pBuf);

#define SOCP_VIRT_TO_PHYS(virt) (virt)
#define SOCP_PHYS_TO_VIRT(phy)  (phy)

unsigned int g_socp_bus_test_ddr_to_ddr_ok_cnt = 0;
unsigned int g_socp_bus_test_ddr_to_ddr_fail_cnt = 0;
unsigned int g_socp_bus_test_axi_mem_to_ddr_ok_cnt = 0;
unsigned int g_socp_bus_test_axi_mem_to_ddr_fail_cnt = 0;
unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt = 0;
unsigned int g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt = 0;

static BSP_BOOL g_bInit = BSP_FALSE;

BSP_U32 g_SocpBufCnt = 0;
BSP_U8  *g_pSocpBuf[1000];
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#else
SOCP_RING_BUF_S g_socpEncDst[4];
SOCP_RING_BUF_S g_socpEncSrc[16];
#endif

extern BSP_S32 socp_init();
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

BSP_S32 SocpEventCB(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
{
    return 0;
}

BSP_S32 SocpRdCB(BSP_U32 u32ChanID)
{
    return 0;
}

BSP_S32 SocpAllocEncChan1(BSP_U32 u32ChanId)
{
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    BSP_U32 len = 0x1000;
    BSP_U8 *p;
    BSP_U32 ret;

    p = (BSP_U8*)osl_mem_align(8, len);

    if(BSP_NULL == p)
    {
        socp_printf("alloc chan failed, no mem\n");
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
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = p;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = p + len - 1;
    ret = bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr);
    if(BSP_OK != ret)
    {
        socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);
        return -1;
    }
    return u32ChanId;
}


BSP_S32 SocpResetAll()
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

    p1 = (BSP_U8*)osl_mem_align(8, len);

    if(BSP_NULL == p1)
    {
        socp_printf("alloc chan failed, no mem\n");
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = p1;

    p2 = (BSP_U8*)osl_mem_align(8, len2);
    if(BSP_NULL == p2)
    {
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);
        socp_printf("alloc chan failed, no mem\n");
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
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = p1;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = p1 + len - 1;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = p2;
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = p2 + len2 - 1;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 5;
    ret = bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr);
    if(BSP_OK != ret)
    {
        socp_printf("alloc chan failed, return error(0x%x)\n", ret);
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);
        osl_free(g_pSocpBuf[--g_SocpBufCnt]);

        return -1;
    }

    return u32ChanId;
}


/* 初始化成功 */
BSP_S32 SOCP_LLT_INIT_001()
{
    BSP_U32 i=0;

    CHECK_RET(socp_init(), BSP_OK);

    for(i=0;i<1000;i++)
    {
        g_pSocpBuf[i] = BSP_NULL;
    }

    socp_printf("SOCP TEST: INIT CASE 1 PASSED\n");

    return 0;
}


/* 重复初始化成功, 测试之前重启单板 */
BSP_S32 SOCP_LLT_INIT_002()
{
    CHECK_RET(socp_init(), BSP_OK);
    CHECK_RET(socp_init(), BSP_OK);

    socp_printf("SOCP TEST: INIT CASE 2 PASSED\n");
    return 0;
}

BSP_U32 SOCP_LLT_RESET_001()
{
    CHECK_RET(SocpResetAll(), BSP_OK);

    g_strSocpStat.bInitFlag = BSP_FALSE;

    socp_printf("SOCP TEST: RESET CASE 1 PASSED\n");

    return 0;
}

/* 申请编码源通道，空指针检查 */
BSP_S32 SOCP_LLT_ENC_SRC_001()
{
    DEV_INIT();

    CHECK_RET(bsp_socp_coder_set_src_chan(4, BSP_NULL), BSP_ERR_SOCP_NULL);

    socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 1 PASSED\n");
    return 0;
}


/* 申请编码源通道，无效参数 */
BSP_S32 SOCP_LLT_ENC_SRC_002(void)
{
    BSP_U32 u32ChanId = 4;
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;

    DEV_INIT();

    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004000;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;

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

    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30003800;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30008004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;

    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 0x10;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)0x30004004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)0x30004000;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30003800;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_PARA);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)BSP_NULL;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NULL);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30007fff;

    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30008004;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_NOT_8BYTESALIGN);
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30007fff;

    socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 2 PASSED\n");
    return 0;
}


/* 申请编码源通道，申请成功 */
BSP_S32 SOCP_LLT_ENC_SRC_003(void)
{
    BSP_U32 u32ChanId = 4;
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;

    DEV_INIT();

    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_0;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_0;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_0;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004000;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);

    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_LIST;
    EncSrcAttr.sCoderSetSrcBuf.pucRDStart = (u8*)0x30001000;
    EncSrcAttr.sCoderSetSrcBuf.pucRDEnd = (u8*)0x30001fff;
    EncSrcAttr.sCoderSetSrcBuf.u32RDThreshold = 10;
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);

    socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 3 PASSED\n");
    return 0;
}


/* 申请编码源通道，申请全部通道，最后无空闲通道 */
BSP_S32 SOCP_LLT_ENC_SRC_004(void)
{
    BSP_U32 u32ChanId;
    SOCP_CODER_SRC_CHAN_S EncSrcAttr;
    int i;

    DEV_INIT();

    EncSrcAttr.eDataTypeEn = SOCP_DATA_TYPE_EN;
    EncSrcAttr.eDebugEn = SOCP_ENC_DEBUG_DIS;
    EncSrcAttr.eDataType = SOCP_DATA_TYPE_2;
    EncSrcAttr.eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;
    EncSrcAttr.ePriority = SOCP_CHAN_PRIORITY_3;
    EncSrcAttr.u32BypassEn = BSP_FALSE;
    EncSrcAttr.u32DestChanID = SOCP_CODER_DEST_CHAN_4;
    EncSrcAttr.sCoderSetSrcBuf.pucInputStart = (u8*)0x30004000;
    EncSrcAttr.sCoderSetSrcBuf.pucInputEnd = (u8*)0x30007fff;

    for(i=SOCP_ENCSRC_CHN_BASE; i<(SOCP_ENCSRC_CHN_BASE+SOCP_ENCSRC_CHN_NUM); i++)
    {
        u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
        CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_OK);
        socp_printf("chanid is %d\n", u32ChanId);
    }
    u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
    CHECK_RET(bsp_socp_coder_set_src_chan(u32ChanId, &EncSrcAttr), BSP_ERR_SOCP_INVALID_CHAN);
    socp_printf("set enc src chan success\n");
    for(i=SOCP_ENCSRC_CHN_BASE; i<(SOCP_ENCSRC_CHN_BASE+SOCP_ENCSRC_CHN_NUM); i++)
    {
        u32ChanId = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN, i);
        CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);
    }

    socp_printf("SOCP TEST: ALLOC CODER SRC CHAN CASE 4 PASSED\n");
    return 0;
}


/* 释放通道，释放无效通道*/
BSP_S32 SOCP_LLT_FREE_CHAN_001()
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_DEST_CHAN << 16)|4;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|8;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: FREE CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 释放通道，释放未申请通道 */
BSP_S32 SOCP_LLT_FREE_CHAN_002()
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|7;
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: FREE CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 释放通道，释放编码通道成功 */
BSP_S32 SOCP_LLT_FREE_CHAN_003()
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(7);
    if(-1 == (s32)u32ChanId)
    {
        socp_printf("SOCP TEST: FREE CHANNEL CASE 3 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_free_channel(u32ChanId), BSP_OK);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);

    socp_printf("SOCP TEST: FREE CHANNEL CASE 3 PASSED\n");

    return 0;
}

/* 释放通道，反复申请释放 */
BSP_S32 SOCP_LLT_FREE_CHAN_006()
{
    BSP_U32 u32ChanId[8];
    BSP_S32 n=9;
    BSP_S32 i, j, ret;

    DEV_INIT();

    for(j=0; j<10; j++)
    {
        for(i=4; i<n; i++)
        {
            u32ChanId[i] = SocpAllocEncChan1(i);
            if(-1 == (s32)u32ChanId[i])
            {
                socp_printf("alloc channel error\n");
                socp_printf("SOCP TEST: FREE CHANNEL CASE 6 FAILED\n");
                return 0;
            }
            //socp_printf(" u32ChanId[%d] is %d\n", i, u32ChanId[i]);
        }

        for(i=n-1; i>=4; i--)
        {
            ret = bsp_socp_free_channel(u32ChanId[i]);
            //socp_printf(" u32ChanId[%d] is %d\n", i, u32ChanId[i]);
            if(BSP_OK != ret)
            {
                socp_printf("free channel error, ret=0x%x\n", ret);
                socp_printf("SOCP TEST: FREE CHANNEL CASE 6 FAILED\n");
                return 0;
            }
            osl_free(g_pSocpBuf[--g_SocpBufCnt]);
        }
    }

    socp_printf("SOCP TEST: FREE CHANNEL CASE 6 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置无效通道的事件回调函数 */
BSP_S32 SOCP_LLT_SET_EVENT_001()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_6 + 1;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_DECODER_SRC_CHAN_3 + 1;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|16;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: SET EVENT CB CASE 1 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置未申请通道的事件回调函数 */
BSP_S32 SOCP_LLT_SET_EVENT_002()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|7;
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId, SocpEventCB), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: SET EVENT CB CASE 2 PASSED\n");
    return 0;
}

/* 设置事件回调函数，设置有效事件回调函数 */
BSP_S32 SOCP_LLT_SET_EVENT_004()
{
    BSP_U32 u32ChanId1;
    DEV_INIT();

    u32ChanId1 = SocpAllocEncChan1(4);
    if(-1 == (s32)u32ChanId1)
    {
        socp_printf("SOCP TEST: SET EVENT CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId1, SocpEventCB), BSP_OK);
    bsp_socp_free_channel(u32ChanId1);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: SET EVENT CB CASE 4 PASSED\n");
    return 0;
}


/* 设置事件回调函数，设置事件回调函数为空 */
BSP_S32 SOCP_LLT_SET_EVENT_005()
{
    BSP_U32 u32ChanId1;
    DEV_INIT();

    u32ChanId1 = SocpAllocEncChan1(4);
    if(-1 == (s32)u32ChanId1)
    {
        socp_printf("SOCP TEST: SET EVENT CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_event_cb(u32ChanId1, BSP_NULL), BSP_OK);
    bsp_socp_free_channel(u32ChanId1);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: SET EVENT CB CASE 5 PASSED\n");
    return 0;
}

/* 设置RD回调函数，设置无效通道的RD回调函数 */
BSP_S32 SOCP_LLT_SET_RD_001()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|12;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SOCP_CODER_DEST_CHAN_0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_SRC_CHAN << 16)|4;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_DECODER_DEST_CHAN << 16)|0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: SET RD CB CASE 1 PASSED\n");
    return 0;
}

/* 设置RD回调函数，设置未申请通道的RD回调函数 */
BSP_S32 SOCP_LLT_SET_RD_002()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|7;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: SET RD CB CASE 2 PASSED\n");
    return 0;
}

/* 设置RD回调函数，设置非LIST方式的RD回调函数 */
BSP_S32 SOCP_LLT_SET_RD_004()
{
    BSP_U32 u32ChanId;

    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(4);
    if(-1 == (s32)u32ChanId)
    {
        socp_printf("SOCP TEST: SET RD CB CASE 4 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_ERR_SOCP_CHAN_MODE);

    bsp_socp_free_channel(u32ChanId);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: SET RD CB CASE 4 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置有效RD回调函数 */
BSP_S32 SOCP_LLT_SET_RD_005()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SocpAllocEncChan2(4);
    if(-1 == (s32)u32ChanId)
    {
        socp_printf("SOCP TEST: SET RD CB CASE 5 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, SocpRdCB), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: SET RD CB CASE 5 PASSED\n");
    return 0;
}


/* 设置RD回调函数，设置RD回调函数为空 */
BSP_S32 SOCP_LLT_SET_RD_006()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SOCP_DECODER_SRC_CHAN_0;
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, BSP_NULL), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = SocpAllocEncChan2(4);
    if(-1 == (s32)u32ChanId)
    {
        socp_printf("SOCP TEST: SET RD CB CASE 6 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_register_rd_cb(u32ChanId, BSP_NULL), BSP_OK);

    bsp_socp_free_channel(u32ChanId);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: SET RD CB CASE 6 PASSED\n");
    return 0;
}


/* 通道控制，启动无效通道 */
BSP_S32 SOCP_LLT_START_001()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (4 << 16)|4;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|11;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: START CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 通道控制，启动未申请通道 */
BSP_S32 SOCP_LLT_START_002()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|7;
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: START CHANNEL CASE 2 PASSED\n");
    return 0;
}


/* 通道控制，启动时，目的通道未设置 */
BSP_S32 SOCP_LLT_START_003()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = SocpAllocEncChan1(7);
    if(-1 == (s32)u32ChanId)
    {
        socp_printf("alloc encoder src chan failed\n");
        socp_printf("SOCP TEST: START CHANNEL CASE 3 FAILED\n");
        return 0;
    }
    CHECK_RET(bsp_socp_start(u32ChanId), BSP_ERR_SOCP_DEST_CHAN);

    bsp_socp_free_channel(u32ChanId);
    osl_free(g_pSocpBuf[--g_SocpBufCnt]);
    socp_printf("SOCP TEST: START CHANNEL CASE 3 PASSED\n");
    return 0;
}


/* 通道控制，停止无效通道 */
BSP_S32 SOCP_LLT_STOP_001()
{
    BSP_U32 u32ChanId;
    BSP_U32 u32Ret;
    DEV_INIT();

    u32ChanId = (4 << 16)|4;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|11;
    u32Ret = bsp_socp_stop(u32ChanId);
    socp_printf(" the u32Ret is %d\n", u32Ret);
    CHECK_RET(u32Ret, BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: STOP CHANNEL CASE 1 PASSED\n");
    return 0;
}


/* 通道控制，停止未申请通道 */
BSP_S32 SOCP_LLT_STOP_002()
{
    BSP_U32 u32ChanId;
    DEV_INIT();

    u32ChanId = (SOCP_CODER_SRC_CHAN << 16)|7;
    CHECK_RET(bsp_socp_stop(u32ChanId), BSP_ERR_SOCP_INVALID_CHAN);

    socp_printf("SOCP TEST: STOP CHANNEL CASE 2 PASSED\n");
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
    BSP_U32                 TaskId;
    BSP_U32                 u32DataLen;
    BSP_U32                 u32DataCnt;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eEncDebugEn;
    BSP_U32                 u32EncDstThrh;
}SOCP_ST_CASE_S;

#if 0
static BSP_U8 g_socpRxdata[4096];
#endif
BSP_U32 g_socpRxTotal[7] = {0};
BSP_U32 g_socpRdTotal[25] = {0};
BSP_U32 g_socpTxTotal[25] = {0};

BSP_S32 SocpStAllocEncSrc(SOCP_ST_CASE_S *pCase)
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


BSP_S32 SocpStEventCB_1(BSP_U32 u32ChanID, SOCP_EVENT_ENUM_UIN32 u32Event, BSP_U32 u32Param)
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


BSP_S32 SocpStReadCB_1(BSP_U32 u32ChanID)
{
#if 0
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("func: SocpStReadCB_1: chan[%d] get data len=[%d]\n", u32ChanID&0xff, len);
    if(Buffer.pBuffer)
    {
        Socp_Memcpy(g_socpRxdata, Buffer.pBuffer, Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        Socp_Memcpy(g_socpRxdata+Buffer.u32Size, Buffer.pRbBuffer, Buffer.u32RbSize);
    }

    for(i=0; i<len; i++)
    {
        socp_printf("0x%02x ", g_socpRxdata[i]);
        if(i && (0 == i%8))
            socp_printf("\n");
    }
    socp_printf(" the chan id is %d\n",u32ChanID);

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

#endif
    return 0;
}

BSP_S32 SocpStReadCB_2(BSP_U32 u32ChanID)
{
#if 0
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int i, c;
    static BSP_BOOL flag = BSP_TRUE;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);

    c = u32ChanID&0xf;
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[c] += len;
    socp_printf("func: SocpStReadCB_2: c[%d] get data R=%d T=%d\n", u32ChanID&0xff, len, g_socpRxTotal[c]);
    /*if(Buffer.pBuffer)
    {
        Socp_Memcpy(g_socpRxdata, Buffer.pBuffer, Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        Socp_Memcpy(g_socpRxdata+Buffer.u32Size, Buffer.pRbBuffer, Buffer.u32RbSize);
    }

    if(flag)
    {
        for(i=0; i<len; i++)
        {
            socp_printf("0x%02x ", g_socpRxdata[i]);
            if(i && (0 == i%8))
                socp_printf("\n");
        }
        flag = BSP_FALSE;
    }*/
    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

#endif
    return 0;
}

BSP_S32 SocpStReadCB_3(BSP_U32 u32ChanID)
{
#if 0
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;
    int chan;

    chan = u32ChanID&0xff;
    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    g_socpRxTotal[chan] += len;
    socp_printf("func: SocpStReadCB_3: chan[%d] get data R=%d T=%d\n", chan, len, g_socpRxTotal[chan]);
    if(Buffer.pBuffer)
    {
        Socp_Memcpy(g_socpRxdata, Buffer.pBuffer, Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        Socp_Memcpy(g_socpRxdata+Buffer.u32Size, Buffer.pRbBuffer, Buffer.u32RbSize);
    }

    CHECK_RET(bsp_socp_read_data_done(u32ChanID, len), BSP_OK);

#endif
    return 0;
}

BSP_S32 SocpStReadCB_4(BSP_U32 u32ChanID)
{
#if 0
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_read_buff(u32ChanID, &Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    socp_printf("func: SocpStReadCB_4: chan[%x] get data len=[%d]\n", u32ChanID, len);
#endif
    return 0;
}


BSP_U32 rCnt = 0;
BSP_S32 SocpStReadCB_19(BSP_U32 u32ChanID)
{
#if 0
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
        Socp_Memcpy(g_socpRxdata, Buffer.pBuffer, Buffer.u32Size);
    }
    if(Buffer.pRbBuffer)
    {
        Socp_Memcpy(g_socpRxdata+Buffer.u32Size, Buffer.pRbBuffer, Buffer.u32RbSize);
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
#endif
    return 0;
}

//static BSP_U32 g_socpRDdata[8];

BSP_S32 SocpStRdCB_1(BSP_U32 u32ChanID)
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

BSP_S32 SocpStRdCB_19(BSP_U32 u32ChanID)
{
    BSP_U32 len;
    SOCP_BUFFER_RW_STRU Buffer;

    CHECK_RET(bsp_socp_get_rd_buffer(u32ChanID, (SOCP_BUFFER_RW_STRU *)&Buffer), BSP_OK);
    len = Buffer.u32Size + Buffer.u32RbSize;
    //socp_printf("%d chan[0x%x] get RD len=[%d]\n", __LINE__, u32ChanID, len);
    //g_socpRDdata[0] = (BSP_U32)&Buffer;
    //g_socpRDdata[1] = len;

    CHECK_RET(bsp_socp_read_rd_done(u32ChanID, len), BSP_OK);

//    socp_printf("chan[%d] read RD done!\n", u32ChanID);

    return 0;
}

SOCP_ST_CASE_S g_stCase[30] =
{
    {
        // 0
        0, 7, SOCP_CODER_DEST_CHAN_6, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 100, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 1
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 100,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 2
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 256, SocpStEventCB_1, SocpStReadCB_2, SocpStRdCB_1, 0, 24, 4, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 3
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 580, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 4,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 4
        0, 7, SOCP_CODER_DEST_CHAN_0, 1, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 5
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_1, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 24, 10,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 6
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 100, 5, 0, 0x1000, 100, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 96, 100,SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 7
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x100, 2, SocpStEventCB_1, SocpStReadCB_4, SocpStRdCB_1, 0, 24, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 8
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x100, 0, 0x40, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_1, SocpStRdCB_1, 0, 64, 10, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 9
        0, 7, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 10
        0, 7, SOCP_CODER_DEST_CHAN_1, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 2000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 11
        0, 7, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 12
        0, 7, SOCP_CODER_DEST_CHAN_2, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 13
        0, 7, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 256, 5, 0, 0x1000, 512, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 14
        0, 7, SOCP_CODER_DEST_CHAN_3, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 15
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 0x40, 5, 0, 0x1000, 64, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 24, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 16
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_LIST, SOCP_CHAN_PRIORITY_0,
        0, 0x1000, 0, 160, 40, 0, 0x1000, 2048, SocpStEventCB_1, SocpStReadCB_3, SocpStRdCB_1, 0, 1024, 10000, SOCP_DATA_TYPE_EN,
        SOCP_ENC_DEBUG_DIS, 0
    },
    {
        // 17
        0, 7, SOCP_CODER_DEST_CHAN_0, 0, SOCP_DATA_TYPE_0, SOCP_ENCSRC_CHNMODE_CTSPACKET, SOCP_CHAN_PRIORITY_3,
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

BSP_S32 SocpStInitChannel(SOCP_ST_CASE_S *pCase)
{
    BSP_U32 u32Ret;
    BSP_U32 i;

    DEV_INIT();

    u32Ret = SocpStAllocEncSrc(pCase);
    if(u32Ret == BSP_ERR_SOCP_NO_CHAN)
    {
        for(i=SOCP_ENCSRC_CHN_BASE;i<(SOCP_ENCSRC_CHN_BASE + SOCP_ENCSRC_CHN_NUM);i++)
        {
            CHECK_RET(bsp_socp_stop(i), BSP_OK);
            CHECK_RET(bsp_socp_free_channel(i), BSP_OK);
        }
        CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    }
    else if(u32Ret != BSP_OK)
    {
        socp_printf("alloc enc src failed!\n");
        return BSP_ERROR;

    }
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    return BSP_OK;
}

BSP_VOID SocpStGenPayLoad(BSP_U8 *pBuff, BSP_U32 u32DataLen)
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
    //pBuff += 16;
    for(i=16; i<(int)u32DataLen; i++)
    {
        //pBuff[i] = i%0xff;
        pBuff[i] = 0xA5;
    }

    return;
}

BSP_VOID SocpStGenPkt(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    // 组包头

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

    // 组消息包
    SocpStGenPayLoad((pBuff+8), u32DataLen-16);

    return;
}

BSP_VOID SocpStGenPkt2(BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    BSP_U32 *pWord;

    // 组包头

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

    // 组包头

    pBuff[0] = 0x01;
    pBuff[1] = 0x21;
    pBuff[2] = 0xed;
    pBuff[3] = 0x37;

    pWord = (BSP_U32*)(pBuff+4);
    pWord[0] = u32DataLen;
    //pBuff += 8;

    // 组消息包
    SocpStGenPayLoad((pBuff+8), u32DataLen-16);

    return;
}

BSP_VOID SocpStGenBD1(BSP_U32 *pBD, BSP_U8 *pBuff, BSP_U32 u32DataLen)
{
    // 组包头
    pBD[0] = (BSP_U32)pBuff;
    pBD[1] = 0;
    pBD[1] |= (0xffff & u32DataLen);

    // 组消息包
    SocpStGenPayLoad(pBuff, u32DataLen);

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


int socp_encode_task005(void *param)
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
//
    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

BSP_U32 u32StrEncSendCnt = 0;
BSP_S32 socp_encode_dcore_task_stress(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
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

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(1)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
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
            g_socpTxTotal[c]++;
			if(BSP_OK != bsp_socp_write_done(pCase->SrcCh, len))
			{
				g_socp_bus_test_ddr_to_ddr_fail_cnt ++;
				return -1;
			}
			g_socp_bus_test_ddr_to_ddr_ok_cnt++;
        }
        else
        {
            vfcnt++;
            osl_task_delay(2);
        }

        u32StrEncSendCnt++;
        if(9999 == u32StrEncSendCnt%10000)
        {
            socp_printf("encoder stress send cnt is %d\n",u32StrEncSendCnt);
        }
        if(u32StrEncSendCnt >0xFFFFFFF0)
        {
            u32StrEncSendCnt = 0;
        }
        osl_task_delay(1);
    }

    return BSP_OK;
}


BSP_S32 socp_encode_task006(BSP_VOID *param)
{
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S*)param;
    int cnt = pCase->u32DataCnt;
    int len = pCase->u32DataLen;
    BSP_U8* packet;
    SOCP_BUFFER_RW_STRU WtBuff;
    BSP_U8 bd[8];

    DEV_INIT();

    CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc failed chan=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh);
        return -1;
    }

    g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenBD1((BSP_U32*)bd, packet, pCase->u32DataLen);

    while(cnt--)
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
        }
        else
        {
            osl_task_delay(2);
        }
    }

    osl_task_delay(100);
    osl_cachedma_free(packet);

    socp_printf("chan[%d] write done!\n", pCase->SrcCh);

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

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;
    SocpStGenPkt2(packet, len);

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
    osl_task_delay(50);
    //osl_free(packet);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

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

    packet = osl_cachedma_malloc((u32)len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }
    g_pSocpBuf[g_SocpBufCnt++] = packet;

    SocpStGenPkt3(packet, pCase->u32DataLen);

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
   // osl_free(packet);

    socp_printf("chan[%d] write done! totol=0x%x size=0x%x\n", pCase->SrcCh, g_socpTxTotal[c], g_socpTxTotal[c]*len);

    return 0;
}

/* 编码测试, MODEM CPU发APP CPU收，固定长度块式数据包 */
BSP_S32 SOCP_LLT_ENCODE_006_START()
{
    char task_name[30] = {0};

    DEV_INIT();

    sprintf_s(task_name,30,"socpTest%02d",6);
    //g_stCase[0].TaskId = taskSpawn(task_name, 100, 0, 0x1000,(FUNCPTR)socp_encode_task005, (int)(&g_stCase[0]),0,0,0,0,0,0,0,0,0);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task005, &g_stCase[0], &(g_stCase[0].TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_LLT_ENCODE_006_STOP()
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


/* 编码测试, MODEM CPU发APP CPU收，固定长度BD链表 */
BSP_S32 SOCP_LLT_ENCODE_007_START()
{
    char task_name[30] = {0};

    DEV_INIT();

    sprintf_s(task_name,30,"socpTest%02d",7);
    //g_stCase[1].TaskId = taskSpawn(task_name,100, 0,0x1000,(FUNCPTR)socp_encode_task006, (int)(&g_stCase[1]),0,0,0,0,0,0,0,0,0);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task006, &g_stCase[1], &(g_stCase[1].TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_LLT_ENCODE_007_STOP()
{
    /*停止通道*/
    CHECK_RET(bsp_socp_stop(g_stCase[1].SrcCh), BSP_OK);
    CHECK_RET(bsp_socp_free_channel(g_stCase[1].SrcCh), BSP_OK);

    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);    //任务中打包所用内存
    osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);      //编码源块数据内存
    if(g_stCase[1].eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        osl_cachedma_free(g_pSocpBuf[--g_SocpBufCnt]);  //编码RD buffer内存
    }
    /*释放任务*/
    (BSP_VOID)osl_task_delete(&g_stCase[1].TaskId);

    return 0;
}


/* 编码测试,目标通道接收数据唯一性测试*/
BSP_S32 SOCP_LLT_ENCODE_012_START()
{
    char task_name[30] = {0};
    int i;
    BSP_U32 u32Ret;
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    DEV_INIT();

    u32Ret = SocpStAllocEncSrc(pCase);
    if(u32Ret == BSP_ERR_SOCP_NO_CHAN)
    {
        for(i=SOCP_ENCSRC_CHN_BASE;i<(SOCP_ENCSRC_CHN_BASE + SOCP_ENCSRC_CHN_NUM);i++)
        {
            CHECK_RET(bsp_socp_stop(i), BSP_OK);
            CHECK_RET(bsp_socp_free_channel(i), BSP_OK);
        }
        CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    }
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);

    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    sprintf_s(task_name,30,"socpTest%02d",10);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task001, pCase, &pCase->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_LLT_ENCODE_012_STOP()
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

/* 编码测试,测试数据包长为1的情况*/
BSP_S32 SOCP_LLT_ENCODE_014_START()
{
    char task_name[30] = {0};
    SOCP_ST_CASE_S *pCase = &g_stCase[0];

    DEV_INIT();

    pCase->u32DataLen = 1;
    pCase->u32DataCnt = 200;
    pCase->eDataType  = SOCP_DATA_TYPE_3;

    CHECK_RET(SocpStAllocEncSrc(pCase), BSP_OK);
    CHECK_RET(bsp_socp_register_event_cb(pCase->SrcCh, pCase->EventCb), BSP_OK);
    if(pCase->eMode == SOCP_ENCSRC_CHNMODE_LIST)
    {
        CHECK_RET(bsp_socp_register_rd_cb(pCase->SrcCh, pCase->RdCb), BSP_OK);
    }
    CHECK_RET(bsp_socp_start(pCase->SrcCh), BSP_OK);

    sprintf_s(task_name,30,"socpTest%02d",10);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task009, pCase, &pCase->TaskId))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_LLT_ENCODE_014_STOP()
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

/* 编码测试,测试数据包长为2048的情况*/
BSP_S32 SOCP_LLT_ENCODE_015_START()
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

BSP_S32 SOCP_LLT_ENCODE_015_STOP()
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

/* 编码测试,测试包头错误 */
BSP_S32 SOCP_LLT_ENCODE_016_START()
{
    char task_name[30] = {0};

    DEV_INIT();

    CHECK_RET(SocpStInitChannel(&g_stCase[0]), BSP_OK);

    sprintf_s(task_name,30,"socpTest%02d",10);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_task011, &g_stCase[0], &(g_stCase[0].TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

BSP_S32 SOCP_LLT_ENCODE_016_STOP()
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
BSP_S32 SOCP_LLT_ENCODE_020_START()
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

BSP_S32 SOCP_LLT_ENCODE_020_STOP()
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

/*双核编码测试，M核上发送，A核上接收*/
BSP_S32 SOCP_LLT_ENCODE_DCORE_STRESS()
{
    char task_name[30] = {0};

    DEV_INIT();

    sprintf_s(task_name,30,"socpTest%02d",230);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_dcore_task_stress, &g_stCase[0], &(g_stCase[0].TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;
}

extern void  bsp_socp_enable_lte_dsp_bbp(u32 ulChanId);
BSP_S32 socp_encode_nonddr_task_stress(BSP_VOID *param)
{
    BSP_U8* packet;
    SOCP_ST_CASE_S *pCase = (SOCP_ST_CASE_S *)param;
    u32 len;
    SOCP_BUFFER_RW_STRU WtBuff;
    int vfcnt = 0;

    len = pCase->u32DataLen+8;

    packet = (BSP_U8*)osl_cachedma_malloc(len);
    if(!packet)
    {
        socp_printf("%s(%d): malloc faile chan=0x%x len=0x%x\n", __FUNCTION__, __LINE__, pCase->SrcCh, len);
        return -1;
    }

	socp_printf("%s,%d malloc successed! len = %d\n",__FUNCTION__,__LINE__,len);
    SocpStGenPkt(packet, pCase->u32DataLen);

    while(1)
    {
        CHECK_RET(bsp_socp_get_write_buff(pCase->SrcCh, &WtBuff), BSP_OK);
        if(WtBuff.u32Size + WtBuff.u32RbSize >= (u32)len)
        {
            if(WtBuff.u32Size >= (u32)len)
            {
                Socp_Memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, len);
            }
            else
            {
                Socp_Memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pBuffer), packet, WtBuff.u32Size);
                Socp_Memcpy((BSP_U8*)SOCP_PHYS_TO_VIRT(WtBuff.pRbBuffer), packet+WtBuff.u32Size, len-WtBuff.u32Size);
            }

            if(BSP_OK != bsp_socp_write_done(pCase->SrcCh, len))
            {
                if(pCase->SrcCh == SOCP_CODER_SRC_LDSP1)/*fail count*/
                {
                    g_socp_bus_test_bbe16dtcm_to_ddr_fail_cnt++;
                }
                else
                {
                    g_socp_bus_test_axi_mem_to_ddr_fail_cnt++;
                }
                osl_cachedma_free(packet);
                return -1;
            }
	        if(pCase->SrcCh == SOCP_CODER_SRC_LDSP1)/*ok count*/
	        {
	            g_socp_bus_test_bbe16dtcm_to_ddr_ok_cnt++;
	        }
	        else
	        {
	            g_socp_bus_test_axi_mem_to_ddr_ok_cnt++;
	        }
        }
        else
        {
            vfcnt++;
			osl_task_delay(2);
        }

        osl_task_delay(2);
    }

    osl_cachedma_free(packet);
    return BSP_OK;

}


BSP_S32 SOCP_LLT_ENCODE_STRESS_TCM(u32 addr,u32 ulDatalen)
{
    SOCP_ST_CASE_S *pCase = &g_stCase[3];
    u32 ret;
    char task_name[30] = {0};

    pCase->SrcCh = SOCP_CODER_SRC_LDSP1;
    pCase->eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;

    ret = bsp_socp_init_lte_dsp(SOCP_CODER_SRC_LDSP1,addr,ulDatalen);
    if(ret)
    {
        socp_printf("bsp_socp_init_lte_dsp init failed!\n");
        return 1;
    }

    bsp_socp_enable_lte_dsp_bbp(SOCP_CODER_SRC_LDSP1);


    sprintf(task_name,"socpTest%02d",231);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_nonddr_task_stress, (void*)pCase, (OSL_TASK_ID *)(&pCase->TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;


}

#ifdef CONFIG_HI3650_TLBBP_DS

BSP_S32 SOCP_LLT_ENCODE_STRESS_SRAM(u32 addr,u32 ulDatalen)
{
    SOCP_ST_CASE_S *pCase = &g_stCase[2];
    u32 ret;
    char task_name[30] = {0};

    pCase->SrcCh = SOCP_CODER_SRC_BBP_LOG;
    pCase->eMode = SOCP_ENCSRC_CHNMODE_CTSPACKET;

    ret = bsp_socp_init_lte_bbp_log(pCase->SrcCh,addr,ulDatalen);
    if(ret)
    {
        socp_printf("bsp_socp_init_lte_dsp init failed!\n");
        return 1;
    }

    bsp_socp_enable_lte_dsp_bbp(pCase->SrcCh);

    sprintf(task_name,"socpTest%02d",232);
    if(BSP_OK != osl_task_init(task_name, 20, 0x1000, (OSL_TASK_FUNC)socp_encode_nonddr_task_stress, (void*)pCase, (OSL_TASK_ID *)(&pCase->TaskId)))
    {
        return BSP_ERROR;
    }

    return 0;

}
#endif 

extern void socp_help(void);
extern void socp_show_debug_gbl(void);
extern u32 socp_show_enc_src_chan_cur(u32 u32UniqueId);
extern u32 socp_show_enc_src_chan_add(u32 u32UniqueId);
extern void socp_show_enc_src_chan_all(void);
extern void socp_debug_cnt_show(void);
extern void  bsp_socp_enable_lte_dsp_bbp(u32 ulChanId);
extern u32  bsp_socp_init_lte_dsp(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
extern u32  bsp_socp_init_lte_bbp_log(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);
extern u32  bsp_socp_int_lte_bbp_ds(u32 ulChanId,u32 ulPhyAddr,u32 ulSize);

BSP_S32 SOCP_LLT_DEBUG_TEST(void)
{
    u8 * buffer;

    buffer = (u8 *)osl_cachedma_malloc((u32)0x2000);

    socp_help();
    socp_show_debug_gbl();
    if(socp_show_enc_src_chan_cur(4) != BSP_OK)
    {
        socp_printf("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(socp_show_enc_src_chan_add(4) != BSP_OK)
    {
        socp_printf("%s: failed\n", __FUNCTION__);
        return BSP_ERROR;
    }
    socp_show_enc_src_chan_all();
    socp_debug_cnt_show();

    (void)bsp_socp_init_lte_dsp(14, (u32)buffer, 0x2000);
    (void)bsp_socp_init_lte_bbp_log(16, (u32)buffer, 0x2000);
    (void)bsp_socp_int_lte_bbp_ds(17, (u32)buffer,0x2000);
    bsp_socp_enable_lte_dsp_bbp(14);
    (void)bsp_socp_free_channel(14);
    (void)bsp_socp_free_channel(16);
    (void)bsp_socp_free_channel(17);

    socp_printf("%s PASSED\n", __FUNCTION__);

    return BSP_OK;
}

