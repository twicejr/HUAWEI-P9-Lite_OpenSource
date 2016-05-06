//#include <vxWorks.h>
//#include <semLib.h>
//#include <taskLib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <gu_busstress_type.h>
#include "common.h"
#include "baseaddr.h"
#include "BasicFunc.h"
#include "mem_fun.h"
//#include "../dmac.h"
//#include "../dma/dma_reg.h"


#define _ZSP_TRANS 0
#define _CEVA_TRANS 0
#define _DSP_TRANS 0
#define _ZDMAC_TRANS 0

#define _DM_TRANS 0
#define _CICOM0_TRANS 1
#define _CICOM1_TRANS 1
#define _HIFI_TRANS 0

#define _HDLC_TRANS 1
#define _UPACC_TRANS 1
#define _ARM_TRANS 0
#define _EDMAC_TRANS 0
#define _IPF_TRANS 0
#define _SOCP_TRANS 0
#define _BBP_TRANS 0

#define DATA_INIT    0x5a5a5a5a;
#define DATA_CHANGE    0x55555555;

#if _HIFI_TRANS
    #define SLV_NUM      3;
#else
    #define SLV_NUM      2;
#endif

int master_test(
		    UINT32 des_addr_dsp,
		    UINT32 src_addr_edma,
		    UINT32 des_addr_edma,
	        UINT32 src_addr_zdma,
		    UINT32 des_addr_zdma,
	        UINT32 data_len_zdma,
	        UINT32 addr_src_dm,
	        UINT32 addr_des_dm,
	        UINT32 data_len_dm,
	        UINT32 addr_src_upacc,
	        UINT32 addr_des_upacc,
	        UINT32 data_len_upacc,
	        UINT32 addr_src_cicom0,
	        UINT32 addr_des_cicom0,
	        UINT32 addr_src_cicom1,
	        UINT32 addr_des_cicom1
	        );

int random_master(UINT32 addr_ddr, UINT32 addr_hifi,UINT32 times);

int v9_master_test(
		    UINT32 src_addr_edma,
		    UINT32 des_addr_edma,
		    UINT32 data_len_edma,
	        UINT32 addr_src_p500,
	        UINT32 addr_des_p500,
	        UINT32 data_len_p500,
	        UINT32 addr_src_upacc,
	        UINT32 addr_des_upacc,
	        UINT32 data_len_upacc,
	        UINT32 addr_src_cicom0,
	        UINT32 addr_des_cicom0,
	        UINT32 data_len_cicom0,
	        UINT32 addr_src_ipf,
	        UINT32 addr_des_ipf,
	        UINT32 bqrq_pointer_ipf,
	        UINT32 addr_src_socp,
	        UINT32 addr_des_socp,
		    UINT32 src_addr_bbp,
		    UINT32 des_addr_bbp,
		    UINT32 data_len_bbp,
		    UINT32 src_addr_hdlc,
			UINT32 des_addr_hdlc
	        );

int v9_random_master (UINT32 addr_ddr, UINT32 addr_sram,UINT times, UINT32 bbp_addr);


