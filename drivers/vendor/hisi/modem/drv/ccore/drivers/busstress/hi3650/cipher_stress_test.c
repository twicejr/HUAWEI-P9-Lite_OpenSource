/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  cipher_kdf_bus_stress.c
*
*   作    者 :  
*
*   描    述 :  cipher总线压力测试
*
*   修改记录 :  2013年03月12日  v1.00  w00228729 修改
*************************************************************************/
#include <string.h>
#include "securec.h"
#include <hi_cipher.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include <mdrv_cipher.h>
#include <bsp_softtimer.h>
#include <bsp_om.h>
#include "cipher_balong.h"
#include "bsp_busstress.h"


#define CIPHER_DEBUG_ENABLE         (1)
#define cipher_print(fmt, ...) bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, fmt, ##__VA_ARGS__)
/*
 * CIPHER_STRESS_TEST设置为0时，多通道并发测试会遍历所有cipher操作(除DMA外)，用于获取性能数据
 * CIPHER_STRESS_TEST设置为1时，多通道并发只测试callback方式提交，而且数据块变为60KB，同时不打印日志，用于压力测试
 * 该配置下专门用于总线压力测试
 */
#define CIPHER_STRESS_TEST          (1)
#define PDCP_SIGNAL_CHN             (1)
#define PDCP_DATA_CHN_1             (2)
#define PDCP_DATA_CHN_2             (3)
#define CHAIN_MAX_BLOCK_NUM         (4)
#define MAC_SIZE_SHORT              (2)
#define MAC_SIZE_LONG               (4)
#define MAC_SIZE                    (4)
#define SEQNUM_SIZE                 (1)
#define PH_SIZE                     (1)
#define MIN_CALLBACK_OPT_ID         (1)  
#define BLOCK_MAX_SIZE              (64*1024 + 4 + 20)
#define UP_LINK                     (0)
#define DOWN_LINK                   (1)
#define PDCP_DATA_TASK_NUM          (2)
#define TASK_STACK                  (0x8000)
#define DEFAULT_THRESHOLD           (1024)
#define MIN_THRESHOLD               (0)
#define MAX_THRESHOLD               (8192)
#define CONTINUE_SUBM_MAX_SCP_NUM   (32)
#define TEST_TASK_PRIORITY          (35)
#define TEST_TASK_STACK_SIZE        (10000)

#define CIPHER_TEST_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "[CIPHER]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

typedef struct tag_cipher_data_block
{
    unsigned int u32DataAddr;
    unsigned int u32DataLen;
    unsigned int pNextBlock;
}CIPHER_DATA_BLOCK;

struct cipher_stress_tsk_para
{
	unsigned int         chnid;
	unsigned int         loops;
	int                  bDone;
	CIPHER_SUBMIT_TYPE_E enSubmit;
};

struct cipher_stress_debug
{
	/*cipher stress test*/
	unsigned int callback_success;
	unsigned int callback_failed;
	unsigned int hold_success;
	unsigned int hold_failed;

	/*kdf stress test*/
	unsigned int kdf_success;
	unsigned int kdf_failed;

	/*acc stress test*/
	unsigned int *acc_success;
	unsigned int *acc_failed;
};

static int                   g_cipher_test_inited = 0;
static CIPHER_DATA_BLOCK     cipherInBlock [CIPHER_CHN_NUM];
static CIPHER_DATA_BLOCK     cipherTmpBlock[CIPHER_CHN_NUM];
static CIPHER_DATA_BLOCK     cipherOutBlock[CIPHER_CHN_NUM];
static osl_sem_id            cipherChnCbSem[CIPHER_CHN_NUM];
static CIPHER_NOTIFY_STAT_E  g_notify_stat [CIPHER_CHN_NUM] = {0};
static CIPHER_SINGLE_CFG_S          g_cipher_uplink_cfg  [CIPHER_CHN_NUM];
static CIPHER_SINGLE_CFG_S          g_cipher_downlink_cfg[CIPHER_CHN_NUM];
static unsigned int          g_check_err[CIPHER_CHN_NUM] = {0};
static unsigned int          g_FreeInMem_Num  = 0;
static unsigned int          g_FreeOutMem_Num = 0;
//static int                   s32LoopforMulti  = 0;
static struct softtimer_list sft_timer_list;
static osl_sem_id            cipher_send_sem;
static int                   cipher_stress_run = 0;
extern unsigned int g_acc_busstress_test_ok_cnt;
extern unsigned int g_acc_busstress_test_fail_cnt;


static void cipherCbFunc(unsigned int u32ChNum, unsigned int u32SourAddr, unsigned int u32DestAddr,
	CIPHER_NOTIFY_STAT_E enStatus, unsigned int u32Private)
{
	g_notify_stat[u32ChNum] = enStatus;

    if(enStatus == CIPHER_STAT_CHECK_ERR)
           g_check_err[u32ChNum]++;
    osl_sem_up(&cipherChnCbSem[u32ChNum]);
}
#if 0
static void cipherCbFunc_forMulti(unsigned int u32ChNum, unsigned int u32SourAddr,
	unsigned int u32DestAddr,CIPHER_NOTIFY_STAT_E enStatus, unsigned int u32Private)
{
	g_notify_stat[u32ChNum] = enStatus;

	if(enStatus == CIPHER_STAT_CHECK_ERR)
		g_check_err[u32ChNum]++;

	if((s32LoopforMulti >= 0x11)||(s32LoopforMulti == 0))
		osl_sem_up(&cipherChnCbSem[u32ChNum]);
	s32LoopforMulti++;
}
#endif
static void cipherInBufFree(void* pMemAddr)
{
	g_FreeInMem_Num++;
}

static void cipherOutBufFree(void* pMemAddr)
{
	g_FreeOutMem_Num++;
}

static void cipher_print_hex_dump(unsigned int *data, unsigned int len)
{
	unsigned int i;
	for(i=0; i< len / 4; i++ ) {
		if((i+1)%4 == 0 || i==((len/4)-1))
			cipher_print("0x%08x\n", *(data + i));
		else
			cipher_print("0x%08x\t", *(data + i));
		if((i+1)%0x40)
			osl_task_delay(1);
	}
}


static int cipher_memcmp_ext(unsigned int* p1, unsigned int* p2, unsigned int u32Len)
{
    unsigned int i = 0;
	int ret = 0;
	
    for(i=0; i<u32Len/4; i++)
    {
        if(*(p1+i) != *(p2+i))
        {
        	cipher_print("The %dth data compare error!\n", i);
			cipher_print("p1:0x%08x,p2:0x%08x\n", *(p1+i), *(p2+i));
			cipher_print("p1 addr:0x%p,p2 addr:0x%p\n", p1, p2);
        	ret = -1;
            break;
        }
    }

	if(ret){
		cipher_print("p2>>>>>>\n");
		cipher_print_hex_dump(p2, u32Len);
		cipher_print("p1>>>>>>\n");
		cipher_print_hex_dump(p1, u32Len);
	}
	
    return ret;
}

static int cipherDataCmp(CIPHER_DATA_BLOCK* pBlk1,CIPHER_DATA_BLOCK* pBlk2)
{
    int s32CmpResult = -1;

    CIPHER_DATA_BLOCK* pTempBlk1 = pBlk1;
    CIPHER_DATA_BLOCK* pTempBlk2 = pBlk2;

    if((pBlk1 == NULL)||(pBlk2 == NULL))
    {
        return -1;
    }

    do
    {
        s32CmpResult = cipher_memcmp_ext((unsigned int*)pTempBlk1->u32DataAddr,
					(unsigned int*)pTempBlk2->u32DataAddr,pTempBlk1->u32DataLen);
        if(s32CmpResult != 0)
            return -1;
        else
        {
            pTempBlk1 = (CIPHER_DATA_BLOCK*)pTempBlk1->pNextBlock;
            pTempBlk2 = (CIPHER_DATA_BLOCK*)pTempBlk2->pNextBlock;
        }
    }while((pTempBlk1 != NULL) && (pTempBlk2 != NULL));

    return 0;
}

static void cipherTestInit(void)
{
	int i = 0;
	int s32Ret = 0;

	if(g_cipher_test_inited)
		return;

	for(i = 0; i < CIPHER_CHN_NUM; i++)
	{
		memset_s((void*)&cipherInBlock[i], sizeof(cipherInBlock[i]), 0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&cipherTmpBlock[i],sizeof(cipherTmpBlock[i]),0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&cipherOutBlock[i],sizeof(cipherOutBlock[i]),0, sizeof(CIPHER_DATA_BLOCK));
		memset_s((void*)&(g_cipher_uplink_cfg[i]),  sizeof(g_cipher_uplink_cfg[i]),   0, sizeof(CIPHER_SINGLE_CFG_S));
		memset_s((void*)&(g_cipher_downlink_cfg[i]),sizeof(g_cipher_downlink_cfg[i]), 0, sizeof(CIPHER_SINGLE_CFG_S));

		cipherInBlock[i].pNextBlock   = 0;
		cipherInBlock[i].u32DataLen   = BLOCK_MAX_SIZE;
		cipherInBlock[i].u32DataAddr  = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		cipherTmpBlock[i].pNextBlock  = 0;
		cipherTmpBlock[i].u32DataLen  = BLOCK_MAX_SIZE;
		cipherTmpBlock[i].u32DataAddr = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		cipherOutBlock[i].pNextBlock  = 0;
		cipherOutBlock[i].u32DataLen  = BLOCK_MAX_SIZE;
		cipherOutBlock[i].u32DataAddr = (unsigned int)osl_cachedma_malloc(BLOCK_MAX_SIZE);
		if(!cipherInBlock[i].u32DataAddr ||
			!cipherTmpBlock[i].u32DataAddr ||
			!cipherOutBlock[i].u32DataAddr)
		{
			CIPHER_TEST_PRINT("The %dth DataAddr malloc fail,addr:0x%x\n",i,
											cipherInBlock[i].u32DataAddr,0,0);
			return;
		}

		s32Ret = osl_sem_bcreate(&cipherChnCbSem[i], OSL_SEM_Q_FIFO, OSL_SEM_Q_PRIORITY);
		if(s32Ret)
		{
			CIPHER_TEST_PRINT("Sem create faile,ret\n",0,0,0,0,0);
			return;
		}

		(void)mdrv_cipher_register_notify_cb((CIPHER_NOTIFY_CB_T)cipherCbFunc);
		(void)mdrv_cipher_register_memfree_cb((unsigned int)i, 0, (CIPHER_FREEMEM_CB_T)cipherInBufFree);
		(void)mdrv_cipher_register_memfree_cb((unsigned int)i, 1, (CIPHER_FREEMEM_CB_T)cipherOutBufFree);
		(void)mdrv_cipher_set_dbuf_para((unsigned int)i, 0x0, 0x0, 0x4, 0x8);
		(void)mdrv_cipher_set_dbuf_para((unsigned int)i, 0x1, 0x0, 0x4, 0x8);
	}
	g_cipher_test_inited = 1;
}

static int build_blk_chain(CIPHER_DATA_BLOCK* pCipherInBlock,CIPHER_DATA_BLOCK CipherBlkChain[],
	unsigned int u32TestLen,unsigned int blk_num,unsigned int blk_len[])
{
	int i;
	unsigned int total_len = 0;
	unsigned int tmpAddr   = 0;

    for(i = 0; i <(int) blk_num; i++)
        total_len += blk_len[i];
	
    if(u32TestLen != total_len)
    {
        CIPHER_TEST_PRINT("chain total len(%d) not equal to test len(%d).\n", total_len, u32TestLen);
        return -1;
    }
    tmpAddr = pCipherInBlock->u32DataAddr;
    for(i = 0; i <(int) blk_num; i++)
    {
        CipherBlkChain[i].u32DataAddr = tmpAddr;
        CipherBlkChain[i].u32DataLen  = blk_len[i];
        if(i == (int)(blk_num -1))
             CipherBlkChain[i].pNextBlock = 0;
        else
        {
           CipherBlkChain[i].pNextBlock  = (unsigned int)&CipherBlkChain[i + 1];
           tmpAddr += blk_len[i];
        }
    }
    return 0;
}

static int chain_encrypt_decrypt_multitype(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],CIPHER_ALGORITHM_E alg,
	CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK* blkChain  = NULL;
    CIPHER_DATA_BLOCK* blkChain2 = NULL;
    unsigned char u8Key[32]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    unsigned int  u32KeyIndex = 0x1;
    unsigned int  u32Private  = 0x0;

    /*配置数据加解密缓冲区*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num * sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num * sizeof(CIPHER_DATA_BLOCK));

    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;

    memset_s((void*)cipherInBlock [chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr, BLOCK_MAX_SIZE, 0,dataTestLen + 20);

    for(i = 0; i <(int)cipherInBlock[chnid].u32DataLen; i++)
    {
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;
    }

    (void)mdrv_cipher_set_key(u8Key, keyLen, u32KeyIndex);

    /*完成上行业务*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;
     
    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
        osl_sem_down(&cipherChnCbSem[chnid]);

	   /*构造加密后的数据链表*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    /*完成下行业务*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;    
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;   
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

    g_notify_stat[chnid] = CIPHER_STAT_OK;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
	if(enSubmit == CIPHER_SUBM_CALLBACK)
		osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;
    }

    if((enSubmit == CIPHER_SUBM_CALLBACK) || (enSubmit == CIPHER_SUBM_BLK_HOLD))
    {
    	osl_task_delay(1);
        s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
        if(s32Ret != 0)
        {
            CIPHER_TEST_PRINT("data cmp fail.\n");
            s32TestStatus = -1;
            goto clearup;
        }
    }

clearup:

    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus)
        CIPHER_TEST_PRINT("test fail.\n");
    return s32TestStatus;
}

/*external call*/
unsigned int g_cipher_busstress_test_ok_cnt = 0;
unsigned int g_cipher_busstress_test_fail_cnt = 0;

/*internal count*/
struct cipher_stress_debug cipher_stat;

unsigned int cipher_succeeded = 0;
unsigned int cipher_failed = 0;


static int chain_encrypt_decrypt_multiTask(unsigned char* caseName,unsigned int chnid,
	unsigned int dataTestLen,unsigned int blk_num,unsigned int blk_len[],
	CIPHER_ALGORITHM_E alg, CIPHER_KEY_LEN_E keyLen, CIPHER_SUBMIT_TYPE_E enSubmit)
{
    int s32TestStatus = 0;
    int s32Ret        = 0;
    int i             = 0;
    CIPHER_DATA_BLOCK* blkChain  = NULL;
    CIPHER_DATA_BLOCK* blkChain2 = NULL;
    unsigned int u32KeyIndex     = 0x1;
    unsigned int u32Private      = 0x0;

    /*配置数据加解密缓冲区*/
    cipherInBlock[chnid].u32DataLen = dataTestLen;
    cipherInBlock[chnid].pNextBlock = 0;

    blkChain  = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));
    blkChain2 = (CIPHER_DATA_BLOCK*)osl_malloc(blk_num*sizeof(CIPHER_DATA_BLOCK));

    s32Ret = build_blk_chain(&cipherInBlock[chnid],blkChain,dataTestLen,blk_num,blk_len);
    if(s32Ret != 0)
    {
        s32TestStatus = -1;
        goto clearup;
    }    

    cipherTmpBlock[chnid].u32DataLen = dataTestLen;
    cipherOutBlock[chnid].u32DataLen = dataTestLen;
    cipherTmpBlock[chnid].pNextBlock = 0;
    cipherOutBlock[chnid].pNextBlock = 0;

    memset_s((void*)cipherInBlock [chnid].u32DataAddr,BLOCK_MAX_SIZE, 0, dataTestLen + 20);
    memset_s((void*)cipherTmpBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0, dataTestLen + 20);
    memset_s((void*)cipherOutBlock[chnid].u32DataAddr,BLOCK_MAX_SIZE, 0, dataTestLen + 20);

    for(i = 0; i < (int)cipherInBlock[chnid].u32DataLen; i++)
    {
        *((unsigned char*)(cipherInBlock[chnid].u32DataAddr+i)) = (unsigned char)i;
    }

    /*完成上行业务*/
    g_cipher_uplink_cfg[chnid].enOpt                       = CIPHER_OPT_ENCRYPT;
    g_cipher_uplink_cfg[chnid].u8BearId                    = 0;
    g_cipher_uplink_cfg[chnid].u8Direction                 = 0;
    g_cipher_uplink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_uplink_cfg[chnid].u32Count                    = 0;
    g_cipher_uplink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_uplink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_uplink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_uplink_cfg[chnid].pInMemMgr                   = (void*)blkChain;
	g_cipher_uplink_cfg[chnid].pOutMemMgr                  = (void*)&cipherTmpBlock[chnid];
	g_cipher_uplink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_uplink_cfg[chnid].u32Private                  = u32Private;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_uplink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
    if(enSubmit == CIPHER_SUBM_CALLBACK)
        osl_sem_down(&cipherChnCbSem[chnid]);

    /*完成下行业务*/
    g_cipher_downlink_cfg[chnid].enOpt                       = CIPHER_OPT_DECRYPT;
    g_cipher_downlink_cfg[chnid].u8BearId                    = 0;
    g_cipher_downlink_cfg[chnid].u8Direction                 = 0;
    g_cipher_downlink_cfg[chnid].enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
    g_cipher_downlink_cfg[chnid].u32Count                    = 0;
    g_cipher_downlink_cfg[chnid].bMemBlock                   = 0;
    g_cipher_downlink_cfg[chnid].u32BlockLen                 = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexSec = u32KeyIndex;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.u32KeyIndexInt = 0;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgSecurity  = alg;
    g_cipher_downlink_cfg[chnid].stAlgKeyInfo.enAlgIntegrity = 0;
	g_cipher_downlink_cfg[chnid].pInMemMgr                   = (void*)blkChain2;
	g_cipher_downlink_cfg[chnid].pOutMemMgr                  = (void*)&cipherOutBlock[chnid];
	g_cipher_downlink_cfg[chnid].enSubmAttr                  = enSubmit;
	g_cipher_downlink_cfg[chnid].u32Private                  = u32Private;

    /*构造加密后的数据链表*/
    s32Ret = build_blk_chain(&cipherTmpBlock[chnid],blkChain2,dataTestLen,blk_num,blk_len);
    if(s32Ret)
    {
        s32TestStatus = -1;
        goto clearup;
    }

    g_notify_stat[chnid] = CIPHER_STAT_OK;

    s32Ret = mdrv_cipher_set_bdinfo(chnid, 1, &(g_cipher_downlink_cfg[chnid]));
	if(s32Ret != CIPHER_SUCCESS)
	{
		CIPHER_TEST_PRINT("BSP_CIPHER_SubmitTask fail,ret:0x%x\n",s32Ret);
		s32TestStatus = -1;
		goto clearup;
	}
    if(enSubmit == CIPHER_SUBM_CALLBACK)
        osl_sem_down(&cipherChnCbSem[chnid]);

    if(g_notify_stat[chnid] != CIPHER_STAT_OK)
    {
        CIPHER_TEST_PRINT("CIPHER_STAT:%x\n",g_notify_stat[chnid]);
        s32TestStatus = -1;
        goto clearup;
    } 

    s32Ret = cipherDataCmp(&cipherInBlock[chnid],&cipherOutBlock[chnid]);
    if(s32Ret != 0)
    {
        CIPHER_TEST_PRINT("data cmp fail.\n");
        s32TestStatus = -1;
        goto clearup;
    }

clearup:

    osl_free(blkChain);
    osl_free(blkChain2);
    if(s32TestStatus == 0)
	{
		g_cipher_busstress_test_ok_cnt++;
	}
    else
	{
		g_cipher_busstress_test_fail_cnt++;
        CIPHER_TEST_PRINT("test fail.\n");
	}
    return s32TestStatus;
}

static void cipher_hold_taskEntry_longtime_bus_stress(void * para)
{
	unsigned int blk_num     = 1;
	unsigned int blk_len[]   = {1500};
	unsigned int dataTestLen = 1500;
	int s32Ret;
	struct cipher_stress_tsk_para * tsk_pa = (struct cipher_stress_tsk_para *)para;

	while(cipher_stress_run)
	{
		osl_sem_down(&cipher_send_sem);
		s32Ret = chain_encrypt_decrypt_multitype((unsigned char*)__FUNCTION__,tsk_pa->chnid,
			dataTestLen,blk_num,blk_len, CIPHER_ALG_AES_128, CIPHER_KEY_L128, tsk_pa->enSubmit);
		if(s32Ret)
		{
			CIPHER_TEST_PRINT("cipher_hold_taskEntry_longtime_bus_stress fail,ret:0x%x\n",s32Ret);
			g_cipher_busstress_test_fail_cnt++;
			cipher_stat.hold_failed++;
			break;
		}
		g_cipher_busstress_test_ok_cnt++;
		cipher_stat.hold_success++;
	}
	tsk_pa->bDone = 1;
}

static void cipher_callback_taskEntry_longtime_bus_stress(void * para)
{
	unsigned int blk_num     = 1;
	unsigned int blk_len[]   = {1500};
	unsigned int dataTestLen = 1500;
	int s32Ret;
	struct cipher_stress_tsk_para * tsk_pa = (struct cipher_stress_tsk_para *)para;

	while(cipher_stress_run)
	{
		osl_sem_down(&cipher_send_sem);
		s32Ret = chain_encrypt_decrypt_multiTask((unsigned char*)__FUNCTION__, tsk_pa->chnid, dataTestLen,
			blk_num,blk_len,CIPHER_ALG_AES_128, CIPHER_KEY_L128, tsk_pa->enSubmit);
		if(s32Ret)
		{
		    CIPHER_TEST_PRINT("cipher_callback_taskEntry_longtime_bus_stress fail,ret:0x%x  chn:%d\n",
				s32Ret,tsk_pa->chnid);
			g_cipher_busstress_test_fail_cnt++;
			cipher_stat.callback_failed++;
		    break;
		}
		g_cipher_busstress_test_ok_cnt++;
		cipher_stat.callback_success++;
	}
	tsk_pa->bDone = 1;
}

static void cipher_timer_event(unsigned int param)
{
	osl_sem_up(&cipher_send_sem);
	bsp_softtimer_add(&sft_timer_list);
}

static OSL_TASK_ID taskId[3]  = {0};
static struct cipher_stress_tsk_para tsk_in_para[3] =
{
	{.chnid    = PDCP_SIGNAL_CHN,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_BLK_HOLD
	},
	{.chnid    = PDCP_DATA_CHN_1,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	},
	{.chnid    = PDCP_DATA_CHN_2,
	 .loops    = 1000,
	 .bDone    = 0,
	 .enSubmit = CIPHER_SUBM_CALLBACK
	},
};
int cipher_stress_test_start(int task_priority,int test_rate)
{
	int i = 0;
	int j = 0;
	int testStatus = 0;
	unsigned char* taskName[] = {(unsigned char*)"ltask1",(unsigned char*)"ltask2",(unsigned char*)"ltask3"};

	sft_timer_list.func      = cipher_timer_event;
	sft_timer_list.para      = 0;
	sft_timer_list.timeout   = test_rate;
	sft_timer_list.wake_type = SOFTTIMER_WAKE;

	//set_test_switch_stat(CIPHER, TEST_RUN);
	cipher_stress_run = 1;

	/*创建控制发送速率的信号量*/
	osl_sem_init(SEM_EMPTY, &cipher_send_sem);

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&sft_timer_list))
	{
		CIPHER_TEST_PRINT("SOFTTIMER_CREATE_TIMER fail.\n");
		osl_sema_delete(&cipher_send_sem);
		return -1;
	}
	
	cipherTestInit();
	
	if(mdrv_cipher_enable()){
		CIPHER_TEST_PRINT("ERR: fail to enable cipher\n");
		return CIPHER_ENABLE_FAILED;
	}

	for(i = 0; i < 3; i++)
	{
		if(0x0 == i)
		{
			osl_task_init((char*)taskName[i], (int)task_priority, 2048,
				(OSL_TASK_FUNC)cipher_hold_taskEntry_longtime_bus_stress, (void*)&tsk_in_para[i], &taskId[i]);
		}

		if((1 == i) || (2 == i))
		{
			osl_task_init((char*)taskName[i], (int)task_priority, 2048,
				(OSL_TASK_FUNC)cipher_callback_taskEntry_longtime_bus_stress, (void*)&tsk_in_para[i], &taskId[i]);
		}

		if(taskId[i] == 0)
		{
			testStatus = -1;
			for(j = 0; j < i; j++)
			 	osl_task_delete(&taskId[j]);
		}
	}
	bsp_softtimer_add(&sft_timer_list);
	return testStatus;
}

int cipher_stress_test_stop()
{
	int i = 0;

	//set_test_switch_stat(CIPHER, TEST_STOP);
	cipher_stress_run = 0;

	for(i = 0; i < 3; i++)
	{
		while(0 == osl_task_check(taskId[i]))
			osl_task_delay(100);
	}

	osl_sema_delete(&cipher_send_sem);

	if(sft_timer_list.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&sft_timer_list);
		bsp_softtimer_free(&sft_timer_list);
	}
	return OK;
}

/***********************************************************
KDF stress test code
************************************************************/
#define KEY_TOTAL_SIZE        (32*16)
#define KDF_SHA_S_LENGTH       7
#define KDF_DESTKEY_OFF       16
#define KDF_DESTKEY_LENGTH    16
#define KDF_SHA_KEY_LENGTH    32

static unsigned char u32GoldenKey[KDF_SHA_KEY_LENGTH] = 
{
    0xbd, 0xef, 0x4e, 0xd7, 0x1a, 0x1d, 0x3a, 0x15, 
    0x00, 0x90, 0x4d, 0x83, 0xa5, 0xe8, 0x32, 0xf7, 
    0xe3, 0xe0, 0xfb, 0x1c, 0x43, 0x07, 0xcd, 0x94, 
    0xc6, 0xe6, 0x2d, 0x6a, 0x63, 0x7b, 0x76, 0x41 
};

static unsigned char u32GoldenS1[KDF_SHA_S_LENGTH] = 
{
    0x15,0x05,0x00,0x01,0x02,0x00,0x01
};
static unsigned char u32GoldenResult1[KDF_DESTKEY_LENGTH] = 
{
    0xf8,0xc0,0x2a,0x2f,0x03,0x11,0x02,0x2f, 
    0x8d,0x37,0xec,0xe9,0xf2,0x0c,0x07,0x11
};

static OSL_TASK_ID           g_Kdf_TaskId;
static struct softtimer_list kdf_timer;
static osl_sem_id            kdf_send_sem;
static int                   kdf_stress_routin_run = 0;
extern struct cipher_ctl     cipher_module_ctl;
unsigned int g_kdf_busstress_test_ok_cnt = 0;
unsigned int g_kdf_busstress_test_fail_cnt = 0;
static int kdf_stress_routine()
{
	int i;
	int s32Ret = 0;
	void *pTempAddr             = NULL;
	unsigned int      u32Length = 0;
	unsigned char     u8Key[32] = {0};
	KEY_CONFIG_INFO_S stKeyInfo = {0,0,0};
	S_CONFIG_INFO_S   stSInfo   = {0,0,0,0};
	KEY_MAKE_S        stKeyMake = {0,{0,0,0}};
	unsigned int      u32DIndex = 0x3;

	stKeyInfo.enShaKeySource = SHA_KEY_SOURCE_KEYRAM;
	stKeyInfo.u32ShaKeyIndex = 0x0;
	stKeyInfo.pKeySourceAddr = NULL;

	stSInfo.enShaSSource  = SHA_S_SOURCE_KEYRAM;
	stSInfo.u32ShaSIndex  = 0x1;
	stSInfo.u32ShaSLength = 0x7;
	stSInfo.pSAddr        = NULL;

	stKeyMake.enKeyOutput           = CIPHER_KEY_OUTPUT;
	stKeyMake.stKeyGet.enKeyLen     = CIPHER_KEY_L256;
	stKeyMake.stKeyGet.penOutKeyLen = &u32Length;
	stKeyMake.stKeyGet.pKeyAddr     = (void *)u8Key;


	pTempAddr = (void *)osl_cachedma_malloc(KDF_DESTKEY_LENGTH);

	for(i = 0; i < KDF_SHA_KEY_LENGTH / 4; i++)
	{        
	    *((unsigned int *)((unsigned long)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + (stKeyInfo.u32ShaKeyIndex) * CIPHER_KEY_LEN + 4*i))  \
	    = (((unsigned int)u32GoldenKey[4*i])<<24) | (((unsigned int)u32GoldenKey[4*i+1])<<16) \
	      | (((unsigned int)u32GoldenKey[4*i+2])<<8) | ((unsigned int)u32GoldenKey[4*i+3]);
	}

	for(i = 0; i < KDF_SHA_S_LENGTH / 4; i++)
	{
	    *((unsigned int *)((unsigned long)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + (stSInfo.u32ShaSIndex) * CIPHER_KEY_LEN + 4*i))  \
	        = (((unsigned int)u32GoldenS1[4*i])<<24) | (((unsigned int)u32GoldenS1[4*i+1])<<16) \
	        | (((unsigned int)u32GoldenS1[4*i+2])<<8) | ((unsigned int)u32GoldenS1[4*i+3]);
	}
	if((KDF_SHA_S_LENGTH % 4) == 1)
	{
	    *((unsigned int *)((unsigned long)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + (stSInfo.u32ShaSIndex) * CIPHER_KEY_LEN + 4*i))  \
	        = (((unsigned int)u32GoldenS1[4*i])<<24);
	}
	if((KDF_SHA_S_LENGTH % 4) == 2)
	{
	    *((unsigned int *)((unsigned long)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + (stSInfo.u32ShaSIndex) * CIPHER_KEY_LEN + 4*i))  \
	        = (((unsigned int)u32GoldenS1[4*i])<<24) | (((unsigned int)u32GoldenS1[4*i+1])<<16);
	}
	if((KDF_SHA_S_LENGTH % 4) == 3)
	{
	    *((unsigned int *)((unsigned long)cipher_module_ctl.reg_virt_base + HI_KEY_RAM_OFFSET + (stSInfo.u32ShaSIndex) * CIPHER_KEY_LEN + 4*i))  \
	        = (((unsigned int)u32GoldenS1[4*i])<<24) | (((unsigned int)u32GoldenS1[4*i+1])<<16) | (((unsigned int)u32GoldenS1[4*i+2])<<8);
	}

	while(kdf_stress_routin_run)
	{
		osl_sem_down(&kdf_send_sem);

		s32Ret = mdrv_cipher_gen_key(&stKeyInfo, &stSInfo, u32DIndex, &stKeyMake);
		if(0 != s32Ret)
		{
		    CIPHER_TEST_PRINT("BSP_KDF_KeyMake ERROR! \r\n");
		    osl_cachedma_free(pTempAddr);
		    return -1;
		}

		s32Ret = cipher_memcmp_ext((void *)(&u8Key[16]),
									(void *)u32GoldenResult1,
		                           (CIPHER_KEY_LEN - KDF_DESTKEY_OFF));

		if(0 != s32Ret)
		{
		    CIPHER_TEST_PRINT("cipher_memcmp_ext Error\r\n");
		    osl_cachedma_free(pTempAddr);
			g_kdf_busstress_test_fail_cnt++;
			cipher_stat.kdf_failed++;
		    return s32Ret;
		}
		g_kdf_busstress_test_ok_cnt++;
		cipher_stat.kdf_success++;
	}
	osl_cachedma_free(pTempAddr);
	return s32Ret;
}

static void kdf_timer_event(unsigned int param)
{
	osl_sem_up(&kdf_send_sem);
	bsp_softtimer_add(&kdf_timer);
}
int kdf_stress_test_start(int task_priority,int test_rate)
{
	kdf_timer.func      = kdf_timer_event;
	kdf_timer.para      = 0;
	kdf_timer.timeout   = test_rate;
	kdf_timer.wake_type = SOFTTIMER_WAKE;

	//set_test_switch_stat(KDF, TEST_RUN);
	kdf_stress_routin_run = 1;

	/*创建控制发送速率的信号量*/
	osl_sem_init(SEM_EMPTY, &kdf_send_sem);

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&kdf_timer))
	{
		CIPHER_TEST_PRINT("SOFTTIMER_CREATE_TIMER fail.\n");
		osl_sema_delete(&kdf_send_sem);
		return CIPHER_UNKNOWN_ERROR; 
	}

	if(mdrv_cipher_enable()){
		CIPHER_TEST_PRINT("ERR: fail to enable cipher\n");
		return CIPHER_ENABLE_FAILED;
	}
	
	cipherTestInit();

	osl_task_init("tKdfTask", task_priority, 2048, (OSL_TASK_FUNC)kdf_stress_routine,
		NULL, &g_Kdf_TaskId);

	bsp_softtimer_add(&kdf_timer);
	return CIPHER_SUCCESS;
}

int kdf_stress_test_stop()
{
	//set_test_switch_stat(KDF, TEST_STOP);
	kdf_stress_routin_run = 0;
	while(OK == osl_task_check(g_Kdf_TaskId))
		osl_task_delay(100);

	osl_sema_delete(&kdf_send_sem);

	if( kdf_timer.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&kdf_timer);
		bsp_softtimer_free(&kdf_timer);
	}
	return OK;	
}

void cipher_stress_test_stat(void)
{
	CIPHER_TEST_PRINT("cipher task1 succeed :%d\n", cipher_stat.hold_success);
	CIPHER_TEST_PRINT("cipher task1 failed  :%d\n", cipher_stat.hold_failed);
	CIPHER_TEST_PRINT("cipher task2 succeed :%d\n", cipher_stat.callback_success);
	CIPHER_TEST_PRINT("cipher task2 failed  :%d\n", cipher_stat.callback_failed);
	CIPHER_TEST_PRINT("kdf succeed          :%d\n", cipher_stat.kdf_success);
	CIPHER_TEST_PRINT("kdf failed           :%d\n", cipher_stat.kdf_failed);

	return ;
}
