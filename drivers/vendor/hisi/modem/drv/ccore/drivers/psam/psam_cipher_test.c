#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <osl_malloc.h>
#include <osl_cache.h>
#include <mdrv_cipher.h>
#include <bsp_softtimer.h>
#include <bsp_hardtimer.h>
#include <bsp_om.h>
#include <bsp_cipher.h>
#include "securec.h"

#ifdef CONFIG_MODULE_BUSSTRESS
#include <bsp_busstress.h>
#endif
#include <mdrv_ipf.h>
#include "psam_balong.h"

#define CIPHER_TEST_PRINT(fmt, ...)  bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CIPHER, "[CIPHER]: <%s> <%d>"fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define PSM_TEST_LONG_AD 1500
#define PSM_TEST_SHORT_AD 50

#define PACKT_DATA_VALUE 0x5a

unsigned char *adlong = NULL;
unsigned char *adshort = NULL;

static osl_sem_id test_sem_cifer_psm;
static int sem_cifer_psm_init = 0;
int cipher_psam(int type_num, int u32PakNums[], int u32BlockLen[], unsigned char data_val[], int int_inteval)
{
    int s32ret   = 0;
    int i        = 0;
	int j        = 0;
	int            toal_pkt_num  = 0;
	int            total_data_sz = 0;
    CIPHER_SINGLE_CFG_S * pstCfg        = NULL;
    void *         pInAddr       = NULL;
    void *         pTempInAddr   = NULL;
	int  *         hdled_pkt_num = NULL;

	//psam and ipf init
	psam_st_dl_init();
	
	osl_sem_down(&test_sem_cifer_psm);

	for(i = 0; i < type_num; i++)
	{
		total_data_sz += u32PakNums[i] * u32BlockLen[i];
		toal_pkt_num  += u32PakNums[i];
	}

	pstCfg        = (CIPHER_SINGLE_CFG_S *)osl_malloc(sizeof(CIPHER_SINGLE_CFG_S));
	pInAddr       = osl_malloc(total_data_sz);
	
	hdled_pkt_num = (int*)osl_malloc(type_num * sizeof(int));
	if(!pstCfg || !pInAddr || !hdled_pkt_num)
	{
		CIPHER_TEST_PRINT("fail to osl_malloc memory\n");
		goto ERRFREE;
	}
	memset_s(pstCfg,        sizeof(CIPHER_SINGLE_CFG_S),   0, sizeof(CIPHER_SINGLE_CFG_S));
	memset_s(pInAddr,       total_data_sz, 		  	0, total_data_sz);
	memset_s(hdled_pkt_num, type_num * sizeof(int), 0, type_num * sizeof(int));

	/* 在这里配置要搬移的数据 */
	pTempInAddr = pInAddr;
	while(j < toal_pkt_num)
	{
		for(i = 0; i < type_num; i++)
		{
			if(hdled_pkt_num[i] >= u32PakNums[i])
				continue;
			stmmac_EthTestBuildIpHdr(pTempInAddr, u32BlockLen[i]);
			memset_s(pTempInAddr + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), u32BlockLen[i] - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), data_val[i], u32BlockLen[i] - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
			pTempInAddr      += u32BlockLen[i];
			hdled_pkt_num[i] += 1;
			j                += 1;
		}
	}

	osl_cache_flush(OSL_DATA_CACHE, pInAddr, total_data_sz);
	
	/*配置DMA方式*/
	pTempInAddr = pInAddr;
	pstCfg->enOpt       = 0;
	pstCfg->u8Direction = 1;
	pstCfg->bMemBlock   = 1;
	pstCfg->pOutMemMgr  = NULL;
	pstCfg->enSubmAttr  = CIPHER_SUBM_NONE;
	
	osl_cache_flush(OSL_DATA_CACHE, pstCfg, sizeof(CIPHER_SINGLE_CFG_S));
	
	j = 0;
	memset_s(hdled_pkt_num, type_num * sizeof(int), 0, type_num * sizeof(int));
	while(j < toal_pkt_num)
	{
		for(i = 0; i < type_num; i++)
		{
			if(hdled_pkt_num[i] >= u32PakNums[i])
				continue;

			pstCfg->u32BlockLen = u32BlockLen[i];
			pstCfg->pInMemMgr   = pTempInAddr;

			if(toal_pkt_num == (j + 1))
				pstCfg->u32Private |= (0x1U << 31);
			else if(0 == ((j + 1) % int_inteval))
				pstCfg->u32Private |= (0x1U << 31);
			else
				pstCfg->u32Private &= ~(0x1U << 31);
			while(0 == mdrv_cipher_get_bd_num(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, BD_TYPE_FREE))
				osl_task_delay(1);
			s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, 1, pstCfg);
			if(s32ret)
			{
				CIPHER_TEST_PRINT(">>>line %d FUNC %s fail，return = 0x%x \n",(int)__LINE__, (int)__FUNCTION__, s32ret);
				goto ERRFREE;
			}

			pTempInAddr      += u32BlockLen[i];
			hdled_pkt_num[i] += 1;
			j                += 1;
		}
	}

    /*等待搬移完成*/
	while(!mdrv_cipher_chn_idle(LTE_SECURITY_CHANNEL_DL_DRB_ACORE));

    osl_free(pstCfg);
    osl_free(pInAddr);
	osl_free(hdled_pkt_num);
	osl_sem_up(&test_sem_cifer_psm);
    return 0;
ERRFREE:
	osl_free(pstCfg);
	osl_free(pInAddr);
	osl_free(hdled_pkt_num);
	osl_sem_up(&test_sem_cifer_psm);
	return -1;
}

//只跑一种包
/*
 * pkt_num : 入参，包个数
 * pkt_len : 入参，单个包长度
 * 函数执行一次，构造一个包，发送一个，接着构造下一个，
 */
int psm_test1(int pkt_num, int pkt_len)
{
	unsigned char dat_VAL = PACKT_DATA_VALUE;
	if(!sem_cifer_psm_init)
		osl_sem_init(OS_SEM_FULL, &test_sem_cifer_psm);
	return cipher_psam(1, &pkt_num, &pkt_len, &dat_VAL, 32);
}

//两个交替
/*
 * pkt_num1 : 入参，包个数
 * pkt_len1 : 入参，单个包长度
 * pkt_num2 : 入参，包个数
 * pkt_len2 : 入参，单个包长度
 * 函数执行一次，构造一个包，发送一个，接着构造下一个，
 * 两种包交替发送，
 */
int psm_test2(int pkt_num1, int pkt_len1, int pkt_num2, int pkt_len2)
{
	unsigned char dat_VAL[2] = {PACKT_DATA_VALUE, PACKT_DATA_VALUE};
	int pktnum[2];
	int pktlen[2];

	pktnum[0] = pkt_num1;
	pktnum[1] = pkt_num2;
	pktlen[0] = pkt_len1;
	pktlen[1] = pkt_len2;
	if(!sem_cifer_psm_init)
		osl_sem_init(OS_SEM_FULL, &test_sem_cifer_psm);
	return cipher_psam(2, pktnum, pktlen, &dat_VAL[0], 32);
}

/* ========== task 3 ========= */
#define CBDQ_DEPTH  (512 + 1)
static int           tsk_3_running = 0;
static osl_sem_id    tsk_3_sem;
static OSL_TASK_ID   tsk_3_taskid;
static unsigned int  tsk_3_sent_pkt_idx = 0;
static CIPHER_SINGLE_CFG_S  tsk_3_pTempCfg;
static struct softtimer_list tsk_3_timer_id;
//static unsigned int  tst_3_last_pkt_num = 0;
//static unsigned int  tst_3_cmp[4] = {0};

int test_routine3(void * par)
{
	int s32ret = 0;
	unsigned int rand_num = 0;
	unsigned int pkt_len  = PSM_TEST_LONG_AD;
	unsigned char * pdataBuf = NULL;
	
	srand(bsp_get_slice_value_hrt());

	tsk_3_pTempCfg.enOpt                       = 0;
	tsk_3_pTempCfg.u8BearId                    = 0;
	tsk_3_pTempCfg.u8Direction                 = 1;
	tsk_3_pTempCfg.enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	tsk_3_pTempCfg.enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	tsk_3_pTempCfg.u32Count                    = 0;
	tsk_3_pTempCfg.bMemBlock                   = 1;
	tsk_3_pTempCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
	tsk_3_pTempCfg.stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_NULL;
	tsk_3_pTempCfg.stAlgKeyInfo.u32KeyIndexInt = 0;
	tsk_3_pTempCfg.stAlgKeyInfo.u32KeyIndexSec = 0;
	tsk_3_pTempCfg.pOutMemMgr                  = NULL;
	tsk_3_pTempCfg.enSubmAttr                  = CIPHER_SUBM_NONE;
	tsk_3_pTempCfg.u32Private                  = 0;
//	tsk_3_pTempCfg.u32Offset                   = 0;
//	tsk_3_pTempCfg.u32OutLen                   = 0;
//	tsk_3_pTempCfg.iv                          = {0};

	adlong = (unsigned char *)osl_malloc(PSM_TEST_LONG_AD);
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)adlong, PSM_TEST_LONG_AD);
	memset_s(adlong + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PSM_TEST_LONG_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), 0x5b,
		PSM_TEST_LONG_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, adlong, PSM_TEST_LONG_AD);

	adshort = (unsigned char *)osl_malloc(PSM_TEST_SHORT_AD);
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)adshort, PSM_TEST_SHORT_AD);
	memset_s(adshort + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PSM_TEST_SHORT_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKT_DATA_VALUE,
		PSM_TEST_SHORT_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, adshort, PSM_TEST_SHORT_AD);

    while(tsk_3_running)
    {
		osl_sem_down(&tsk_3_sem);

		rand_num = rand();

		pkt_len = rand_num % 2 ? PSM_TEST_LONG_AD : PSM_TEST_SHORT_AD;

		pdataBuf = (pkt_len == PSM_TEST_LONG_AD)? adlong : adshort;

    	tsk_3_pTempCfg.u32BlockLen = pkt_len;

		if(0 == ((tsk_3_sent_pkt_idx + 1) % 32))
			tsk_3_pTempCfg.u32Private |= (0x1U << 31);
		else
			tsk_3_pTempCfg.u32Private &= ~(0x1U << 31);
		tsk_3_pTempCfg.pInMemMgr = pdataBuf;
		
		while(0 == mdrv_cipher_get_bd_num(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, BD_TYPE_FREE))
			osl_task_delay(1);
		s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, 1, &tsk_3_pTempCfg);
		if(s32ret)
		{
			CIPHER_TEST_PRINT(">>>line %d FUNC %s fail，return = 0x%x\n",
				(int)__LINE__, (int)__FUNCTION__, s32ret);
			return -1;
		}
		tsk_3_sent_pkt_idx++;
    }

	return 0;
}

static void timer_event3(unsigned int parm)
{
	osl_sem_up(&tsk_3_sem);
	bsp_softtimer_add(&tsk_3_timer_id);
}

/*
 * task_priority : 任务优先级
 * test_rate : 发送频率
 */
int test_start3(int task_priority, int test_rate)
{
	int s32ret   = 0;

	tsk_3_timer_id.func      = timer_event3;
	tsk_3_timer_id.para      = 0;
	tsk_3_timer_id.timeout   = test_rate;
	tsk_3_timer_id.wake_type = SOFTTIMER_NOWAKE;

	//psam and ipf init
	psam_st_dl_init();

	osl_sem_init(SEM_EMPTY, &tsk_3_sem);
	tsk_3_running = 1;

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&tsk_3_timer_id))
	{
		CIPHER_TEST_PRINT("SOFTTIMER_CREATE_TIMER fail.\n");
		return -1;
	}

	s32ret = osl_task_init("psm_test3", task_priority, 1024, (OSL_TASK_FUNC)test_routine3, NULL, &tsk_3_taskid);
	if (s32ret)
	{
		CIPHER_TEST_PRINT(">>>line %d FUNC %s fail，s32ret = %d\n", (int)__LINE__, (int)__FUNCTION__, s32ret);
		return -1;
	}
	
	bsp_softtimer_add(&tsk_3_timer_id);
    return 0;
}

int test_stop3(void)
{
	tsk_3_running = 0;
	tsk_3_sent_pkt_idx = 0;
	while(0 == osl_task_check(tsk_3_taskid))
	{
		osl_task_delay(3);
	}
	osl_sema_delete(&tsk_3_sem);
	if(tsk_3_timer_id.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&tsk_3_timer_id);
		bsp_softtimer_free(&tsk_3_timer_id);
	}

	return 0;
}

//200个50的short ad
int cipher_psam_straight_101()
{
	return psm_test1(200, 50);
}

//long ad
int cipher_psam_straight_102()
{
	return psm_test1(200, 1500);
}

//iv_sel = 0, iv_num = 0,
int cipher_psam_straight_103()
{
	return psm_test2(100, 50, 100, 1500);
}

//iv_sel = 0, iv_num = 1, xxxx
int cipher_psam_straight_104()
{
	return psm_test2(100, 200, 100, 1500);
}

//iv_sel = 1, iv_num = 1, xxxx
int cipher_psam_straight_105()
{
	return psm_test2(100, 200, 100, 1500);
}

/* packets of 50, 500, 1500,   第二个参数不能为0
** psam_dl_rpt1_switch 1/0  	-enable/disable ipf dl rd wakeup interrupt
** mdrv_cipher_purge_chan 5  	-reset cipher psam direct channel
*/
int cipher_psam_straight_106()
{
	return test_start3(29, 10);
}

#ifdef CONFIG_MODULE_BUSSTRESS

#ifndef CONFIG_MODULE_BUSSTRESS
typedef enum tagTestModule
{
	GMAC = 0,
	ACC = 1,
	CIPHER = 2,
	KDF =3,
	DMA_DSP =4,
	EDMAC = 5,
	IPF_UL = 6,
	IPF_DL = 7,
	LCD = 8
}TestModule;
typedef enum tagTestSwitch
{
	TEST_STOP = 0,
	TEST_RUN =1
}TestSwitch;

static int get_test_switch_stat(int module_id)
{
	return 1;
}

static int set_test_switch_stat(int module_id, int run_or_stop)
{
	return 0;
}
#endif


/*ipf dl stress test*/
int psam_cipher_dl_stress_test_routine(int dtime)
{
    int s32ret = 0;
	unsigned int rand_num = 0;
	unsigned int pkt_len  = PSM_TEST_LONG_AD;
	unsigned char * pdataBuf = NULL;
	
	srand(bsp_get_slice_value_hrt());

	tsk_3_pTempCfg.enOpt                       = 0;
	tsk_3_pTempCfg.u8BearId                    = 0;
	tsk_3_pTempCfg.u8Direction                 = 1;
	tsk_3_pTempCfg.enAppdHeaderLen             = CIPHER_HDR_BIT_TYPE_0;
	tsk_3_pTempCfg.enHeaderLen                 = CIPHER_HDR_BIT_TYPE_0;
	tsk_3_pTempCfg.u32Count                    = 0;
	tsk_3_pTempCfg.bMemBlock                   = 1;
	tsk_3_pTempCfg.stAlgKeyInfo.enAlgIntegrity = CIPHER_ALG_NULL;
	tsk_3_pTempCfg.stAlgKeyInfo.enAlgSecurity  = CIPHER_ALG_NULL;
	tsk_3_pTempCfg.stAlgKeyInfo.u32KeyIndexInt = 0;
	tsk_3_pTempCfg.stAlgKeyInfo.u32KeyIndexSec = 0;
	tsk_3_pTempCfg.pOutMemMgr                  = NULL;
	tsk_3_pTempCfg.enSubmAttr                  = CIPHER_SUBM_NONE;
	tsk_3_pTempCfg.u32Private                  = 0;
//	tsk_3_pTempCfg.u32Offset                   = 0;
//	tsk_3_pTempCfg.u32OutLen                   = 0;
//	tsk_3_pTempCfg.iv                          = {0};

	adlong = (unsigned char *)osl_malloc(PSM_TEST_LONG_AD);
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)adlong, PSM_TEST_LONG_AD);
	memset_s(adlong + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PSM_TEST_LONG_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), 0x5b,
		PSM_TEST_LONG_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, adlong, PSM_TEST_LONG_AD);

	adshort = (unsigned char *)osl_malloc(PSM_TEST_SHORT_AD);
	stmmac_EthTestBuildIpHdr((ETH_TEST_IP_PACKET_FORMAT_T*)adshort, PSM_TEST_SHORT_AD);
	memset_s(adshort + sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PSM_TEST_SHORT_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T), PACKT_DATA_VALUE,
		PSM_TEST_SHORT_AD - sizeof(ETH_TEST_IP_PACKET_FORMAT_T));
	osl_cache_flush(OSL_DATA_CACHE, adshort, PSM_TEST_SHORT_AD);

	while(get_test_switch_stat(IPF_DL))
    {
		osl_sem_down(&tsk_3_sem);

		rand_num = rand();

		pkt_len = rand_num % 2 ? PSM_TEST_LONG_AD : PSM_TEST_SHORT_AD;

		pdataBuf = (pkt_len == PSM_TEST_LONG_AD)? adlong : adshort;

    	tsk_3_pTempCfg.u32BlockLen = pkt_len;

		if(0 == ((tsk_3_sent_pkt_idx + 1) % 32))
			tsk_3_pTempCfg.u32Private |= (0x1U << 31);
		else
			tsk_3_pTempCfg.u32Private &= ~(0x1U << 31);
		tsk_3_pTempCfg.pInMemMgr = pdataBuf;
		
		while(0 == mdrv_cipher_get_bd_num(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, BD_TYPE_FREE))
			osl_task_delay(1);
		s32ret = mdrv_cipher_set_bdinfo(LTE_SECURITY_CHANNEL_DL_DRB_ACORE, 1, &tsk_3_pTempCfg);
		if(s32ret)
		{
			CIPHER_TEST_PRINT(">>>line %d FUNC %s fail，return = 0x%x\n",
				(int)__LINE__, (int)__FUNCTION__, s32ret);
			return -1;
		}
		//while(!mdrv_cipher_chn_idle(LTE_SECURITY_CHANNEL_DL_DRB_ACORE));
		tsk_3_sent_pkt_idx++;
    }

	return 0;
}

int psam_cipher_dl_stress_test_start(int task_priority,int dtime)
{
	int s32ret   = 0;
	
	set_test_switch_stat(IPF_DL,TEST_RUN);
	tsk_3_running = 1;

	tsk_3_timer_id.func      = timer_event3;
	tsk_3_timer_id.para      = 0;
	tsk_3_timer_id.timeout   = dtime;
	tsk_3_timer_id.wake_type = SOFTTIMER_WAKE;

	//psam and ipf init
	psam_st_dl_init();

	osl_sem_init(SEM_EMPTY, &tsk_3_sem);

	/*创建控制发送速率 的软timer*/
	if(bsp_softtimer_create(&tsk_3_timer_id))
	{
		CIPHER_TEST_PRINT("SOFTTIMER_CREATE_TIMER fail.\n");
		return -1;
	}

	s32ret = osl_task_init("psam_cipher_dl_stress_task", task_priority, 1024, (OSL_TASK_FUNC)psam_cipher_dl_stress_test_routine, NULL, &tsk_3_taskid);
	if (s32ret)
	{
		CIPHER_TEST_PRINT(">>>line %d FUNC %s fail，s32ret = %d\n", (int)__LINE__, (int)__FUNCTION__, s32ret);
		return -1;
	}
	
	bsp_softtimer_add(&tsk_3_timer_id);
    return 0;
}
int psam_cipher_dl_stress_test_stop()
{
	set_test_switch_stat(IPF_DL,TEST_STOP);
	tsk_3_running = 0;
	
	tsk_3_sent_pkt_idx = 0;
	while(0 == osl_task_check(tsk_3_taskid))
	{
		osl_task_delay(3);
	}
	osl_sema_delete(&tsk_3_sem);
	if(tsk_3_timer_id.init_flags == TIMER_INIT_FLAG)
	{
		bsp_softtimer_delete(&tsk_3_timer_id);
		bsp_softtimer_free(&tsk_3_timer_id);
	}

	return 0;
}
#endif

#ifdef __cplusplus
}
#endif
