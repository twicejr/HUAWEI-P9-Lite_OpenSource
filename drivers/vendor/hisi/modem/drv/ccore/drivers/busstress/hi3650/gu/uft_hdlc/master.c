#include "sre_typedef.h"
#include "osl_thread.h"
#include "osl_malloc.h"
#include "master.h"
#include "upacc.h"
//#include "../ipf/ipf.h"
#include "hdlc_for_bbit.h"
#include "osl_bio.h"
#include "product_config.h"
#include "cicom.h"
#include "gu_busstress_type.h"
#define STRESS_TEST_BYTE 1024
#define _UNIT_DEBUG 

UINT32 addr_src_upacc = 0;
UINT32 addr_des_upacc = 0;
UINT32 addr_src_cicom0 = 0;
UINT32 addr_des_cicom0 = 0;
UINT32 addr_src_cicom1 = 0;
UINT32 addr_des_cicom1 = 0;
UINT32 src_addr_hdlc = 0;
UINT32 des_addr_hdlc = 0;
unsigned int g_gu_busstress_tsk_dealy_ticks = 0;
unsigned int g_gu_busstress_task_run_cnt = 0;

extern int get_test_switch_stat(int module_id);
int set_test_switch_stat(int module_id, int run_or_stop);

#if _UPACC_TRANS 
unsigned int g_upacc_busstress_test_ok_cnt = 0;
unsigned int g_upacc_busstress_test_fail_cnt = 0;
int upacc_test(unsigned int  data_len_upacc)
{
	//int i = 0;
	upacc_trans_config(addr_src_upacc, addr_des_upacc, data_len_upacc);
	set32( UPACC_BASEADDR, 0x2 );
	if(upacc_trans_check(addr_src_upacc, addr_des_upacc, data_len_upacc))
	{
		printf("upacc_trans_check fail\n");
		g_upacc_busstress_test_fail_cnt++;
		return 1;
	}
	if(upacc_trans_check(addr_src_upacc, addr_des_upacc, data_len_upacc))
	{
		printf("upacc_trans_check fail\n");
		g_upacc_busstress_test_fail_cnt++;
		return 1;
	}
	
	g_upacc_busstress_test_ok_cnt++;
	return 0;
}
#endif

#if _CICOM0_TRANS
unsigned int g_cicom0_busstress_test_ok_cnt = 0;
unsigned int g_cicom0_busstress_test_fail_cnt = 0;

int cicom0_test(unsigned int data_len_cicom0)
{
	cicom0_v500_trans_config(addr_src_cicom0, addr_des_cicom0, data_len_cicom0);
	cicom0_v500_trans_en();
	if(cicom0_v500_trans_check(addr_src_cicom0, addr_des_cicom0, data_len_cicom0))
	{
		printf("cicom0_v500_trans_check fail\n");
		g_cicom0_busstress_test_fail_cnt++;
		return 1;
	}

	g_cicom0_busstress_test_ok_cnt++;
	return 0;
}
#endif

#if _CICOM1_TRANS
unsigned int g_cicom1_busstress_test_ok_cnt = 0;
unsigned int g_cicom1_busstress_test_fail_cnt = 0;

int cicom1_test(unsigned int data_len_cicom1)
{
	cicom1_v500_trans_config(addr_src_cicom1, addr_des_cicom1, data_len_cicom1);
	cicom1_v500_trans_en();
	if(cicom1_v500_trans_check(addr_src_cicom1, addr_des_cicom1, data_len_cicom1))
	{
		printf("cicom1_v500_trans_check fail\n");
		g_cicom1_busstress_test_fail_cnt++;
		return 1;
	}

	g_cicom1_busstress_test_ok_cnt++;
	return 0;
}
#endif


#if _HDLC_TRANS
int hdlc_test()
{
	 mem_clr(src_addr_hdlc, 0x400);  //clear ipf source data memory
        mem_clr(des_addr_hdlc, 0x400);   //clear ipf destination data memory
       return hdlcv200_frm_def_test_bbit(src_addr_hdlc, des_addr_hdlc);
}
#endif

unsigned int g_gu_master_busstress_test_ok_cnt = 0;
unsigned int g_gu_master_busstress_test_fail_cnt = 0;

int gu_master_test(void)
{
   
    //int loop_temp;
    //UINT32 temp_data;
    
    //int init_data = 0x5a5a5a5a;
    int i=0;
    //UINT32 EdmacDataWidth=0;
    //UINT32 BurstType;
    //UINT32 EdmacBurstType = 0;
    //UINT32 EdmacTransferSize;
    //UINT32 BBPBurstType = 0;
	 
    //UINT32 BBPTransferSize;
   // UINT32 high_addr,data;
    //UINT32 reg_read,addr;
    #if _UPACC_TRANS 
    UINT32 data_len_upacc = STRESS_TEST_BYTE;
	#endif

	#if _CICOM0_TRANS
    UINT32 data_len_cicom0 = STRESS_TEST_BYTE;
	#endif
    #if _CICOM1_TRANS
    UINT32 data_len_cicom1 = STRESS_TEST_BYTE;
    #endif
	
	
    if (!(addr_src_upacc && addr_des_upacc 
		 && addr_src_cicom0 && addr_des_cicom0 
		 && addr_src_cicom1 && addr_des_cicom1
		 && src_addr_hdlc && des_addr_hdlc))
    {
        printf("cacheDmaMalloc Fail!\n");
        return ERROR;
    }
    
    #if _UPACC_TRANS 
    i+=upacc_test(data_len_upacc);
    #endif
    
    #if _CICOM0_TRANS
    i+=cicom0_test(data_len_cicom0);
    #endif

    #if _CICOM1_TRANS
    i+=cicom1_test(data_len_cicom1);
    #endif
        
    #if _HDLC_TRANS
    i+=hdlc_test();
    #endif
    
    if(i==0)
    {   
		g_gu_master_busstress_test_ok_cnt++;
        return 0;
    } 
    else
    {
		g_gu_master_busstress_test_fail_cnt++;
        return 1;
    }

}

void gu_master_routine(void *param)
{		
	while (get_test_switch_stat(8))
	{
		gu_master_test();
		osl_task_delay(1);
		g_gu_busstress_task_run_cnt++;
	}
	return ;
}
OSL_TASK_ID  gu_stress_test_task_id = 0;
int gu_master_stress_test_start(int task_priority, int delayticks)
{
	//UINT32 reg = 0x1F80000;  
	/*?a?¡ä??*/
	int ret = 0;
	writel(SYSCTRL_CRG_VALUE, SYSCTRL_CRG);  

	addr_src_upacc  = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	addr_des_upacc  = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	addr_src_cicom0 = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	addr_des_cicom0 = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	addr_src_cicom1 = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	addr_des_cicom1 = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	src_addr_hdlc   = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	des_addr_hdlc   = (UINT32)osl_cachedma_malloc(STRESS_TEST_BYTE);
	set_test_switch_stat(8,1);

	ret = osl_task_init ("guTask", task_priority, 80000, (OSL_TASK_FUNC)gu_master_routine, (void *)0, &gu_stress_test_task_id);
	if(ret == -1)
	{
		printf("taskSpawn gmacSendTask fail.\n");
	}

	return ret;	
}

int gu_master_stress_test_stop()
{
	set_test_switch_stat(8,0);
	while(0 == osl_task_check(gu_stress_test_task_id))
	{
		osl_task_delay(100);
	}
	return 0;
}

int gu_master_busstress_test_show_cnt(void)
{
	printf("gu_master_busstress_test_ok_cnt=%d\n", g_gu_master_busstress_test_ok_cnt);
	printf("gu_master_busstress_test_fail_cnt=%d\n", g_gu_master_busstress_test_fail_cnt);
	
    #if _CICOM0_TRANS
	    printf("cicom0 busstress test ok cnt=%d\n", g_cicom0_busstress_test_ok_cnt);
	    printf("cicom0 busstress test fail cnt=%d\n", g_cicom0_busstress_test_fail_cnt);
	#else
	    printf("cicom0 busstress test is not excuted\n");
	#endif

    #if _UPACC_TRANS
	    printf("upacc busstress test ok cnt=%d\n", g_upacc_busstress_test_ok_cnt);
	    printf("upacc busstress test fail cnt=%d\n", g_upacc_busstress_test_fail_cnt);
    #else
	    printf("upacc busstress test is not excuted\n");
    #endif

    return 0;
}

