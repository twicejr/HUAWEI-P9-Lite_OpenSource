/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_psam.h
*
*   作    者 :  longyi
*
*   描    述 :  psam模块底软内部接口文件
*
*   修改记录 :  2014年08月19日  v1.00  longyi 创建
*                            
*************************************************************************/
#ifndef    _PSAM_BALONG_H_
#define    _PSAM_BALONG_H_

#include <hi_psam.h>
#include <bsp_ipf.h>
#include <bsp_psam.h>
#include <bsp_ddr.h>

#define PSAM_DLLBD_DESC_SIZE             IPF_DLBD_DESC_SIZE

#define PSAM_DLCD_DESC_SIZE              IPF_DLCD_DESC_SIZE

#define PSAM_DLBD_MEM_SIZE              IPF_DLBD_MEM_SIZE
#define PSAM_DQ_PTR_MASK                IPF_DQ_PTR_MASK
#define PSAM_DQ_DEPTH_MASK              IPF_DQ_DEPTH_MASK
#define PSAM_TRANS_LIMIT_ADDR			IPF_TRANS_LIMIT_ADDR
#define PSAM_ERR_RESETTING				BSP_ERR_IPF_CCORE_RESETTING

#define DESC_FULL  0x10
#define DESC_EMPTY 0x01

#define PSAM_LBD_EPTY_INT1  			0x0000004
#define PSAM_LBD_FULL_INT1  			0x8000000

/*lint -save -e773*/
#define PSAM_INT_OPEN1                  PSAM_LBD_EPTY_INT1 | PSAM_LBD_FULL_INT1
/*lint -restore*/

#define PSAM_CIPER_RD_CNT				3

#define PSAM_DUMP_SIZE					0x400
#define PSAM_REGS_SIZE					HI_PSAM_REG_END_OFFSET

#define PSAM_SRST_BIT					(1<<0)
#define AD_CHECK_BYPASS					(1<<4)

//tmp close func
#define ADQ_CTRL_1						(0x01)
#define ADQ_CTRL_2						(0x03)

#define PSAM_FAMA_MODEM_ATTR			(MDDR_FAMA_CHAN(1))
#define PSAM_FAMA_AP_ATTR				(0x0)

#ifndef NULL
#define NULL            (void*)0
#endif

typedef ipf_desc_attr_t psam_desc_attr_t;
typedef struct tagIPF_BD_DESC_S 	psam_bd_desc_s;
typedef struct tagIPF_LIMIT_ADDR 	psam_limit_addr_s;
/*lint -save -e761*/
typedef IPF_CONFIG_DLPARAM_S psam_config_dlparam_s;
/*lint -restore*/

typedef struct tagpsam_dl
{
    psam_bd_desc_s* psam_bdq;
    unsigned int  	idle_bd; /*record last time idle bd num*/
}psam_dl_s;

typedef struct tagpsam_cfg_desc_debug_info
{
	unsigned int cfg_suc_cnt;
	unsigned int cfg_fail_cnt;
	unsigned int cfg_lbd_num_zero;
	unsigned int cfg_dl_para_null;
	unsigned int dlbd_len_zero_cnt;
	unsigned int dlcd_empty; 
	unsigned int cd_num_p_empty;
}cfg_desc_debug_info;

typedef struct tagpsam_desc_buffer_info
{
	unsigned int vir_addr; 	//desc virtual address
	unsigned int phy_addr; 	//desc physical address
	unsigned int len;		//buffer length
	unsigned int cur_wt_p;	//current write point
	unsigned int cur_rd_p;	//current read point
	unsigned int loop;		//not use
}psam_desc_buf_info;

typedef struct tagpsam_global_var
{
	psam_dl_s g_psam_dl;
	cipher_reg_s ciphers_para;
	ipf_reg_s ipf_para;
	unsigned int regbase;
	unsigned int irqnum1;
	cfg_desc_debug_info cfg_desc_debug;
	psam_desc_buf_info lbdq_desc;

	unsigned int psam_ver;
	unsigned int dllbd_empty;
	unsigned int dllbd_full;
	unsigned int over_idlebd;
	unsigned int get_cipher_para;
	unsigned int init_af_ci_para;
	unsigned int dump_addr;
	unsigned int addr_limit;
	unsigned int addr_limit_off;
	unsigned int limit_addr_set;
	psam_limit_addr_s *sh_limit_addr;
}psam_global_var_s;


#pragma pack(push) 
#pragma pack(1)

typedef struct _IPHDR
{
    unsigned int TOL:16;
    unsigned int TOS:8;
    unsigned int HeaderLen:4;
    unsigned int Vers:4; 
    unsigned int offset:13;
    unsigned int MF:1;
    unsigned int DF:1;
    unsigned int ReservFlag:1;
    unsigned int ID:16;
    unsigned int Checksum:16;
    unsigned int Prot:8;
    unsigned int TTL:8;    
    unsigned int SourceAddr;
    unsigned int DestAddr;
}ETH_TEST_IPHDR_T;

typedef struct _IP_PACKET_FORMAT
{
    /* IP头 */
    ETH_TEST_IPHDR_T     stSCTPHdr;

    /* UDP头 */
    unsigned int DstPort:16;
    unsigned int SrcPort:16;
    unsigned int Checksum:16;
    unsigned int Length:16; 
}ETH_TEST_IP_PACKET_FORMAT_T;
#pragma pack(pop)

int psam_st_dl_init(void);
int psam_srset(void);
int psam_reinit_regs(void);
int psam_set_crdq_ctrl(unsigned int cipher_fc_head);
void stmmac_EthTestBuildIpHdr(ETH_TEST_IP_PACKET_FORMAT_T *pstPkt, unsigned int ulLen);
int psam_disable_limit_func(void);

#endif    /* End #define _PSAM_BALONG_H_ */

