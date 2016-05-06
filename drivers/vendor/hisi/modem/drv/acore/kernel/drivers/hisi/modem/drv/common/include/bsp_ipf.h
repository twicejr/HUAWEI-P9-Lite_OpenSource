

#ifndef    _BSP_IPF_H_
#define    _BSP_IPF_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  头文件包含
**************************************************************************/
#include "hi_ipf.h"
#include <bsp_shared_ddr.h>
#ifndef __CMSIS_RTOS
#include "mdrv_ipf.h"

#else
#include "mdrv_ipf_comm.h"
#endif

#include <bsp_om.h>
#include <bsp_dump.h>
#ifdef CONFIG_BALONG_MODEM_RESET
#include "mdrv_sysboot.h"
#endif
/* #define __BSP_IPF_DEBUG__*/



/*IPF描述符地址定义*/

#define IPF_DLBD_MEM_ADDR              (unsigned long)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_IPF)
#define IPF_DLBD_MEM_SIZE               (IPF_DLBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_DLRD_MEM_ADDR              (IPF_DLBD_MEM_ADDR + IPF_DLBD_MEM_SIZE)
#define IPF_DLRD_MEM_SIZE               (IPF_DLRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_DLAD0_MEM_ADDR              (IPF_DLRD_MEM_ADDR + IPF_DLRD_MEM_SIZE)
#define IPF_DLAD0_MEM_SIZE               (IPF_DLAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLAD1_MEM_ADDR              (IPF_DLAD0_MEM_ADDR + IPF_DLAD0_MEM_SIZE)
#define IPF_DLAD1_MEM_SIZE               (IPF_DLAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLCD_MEM_ADDR              (IPF_DLAD1_MEM_ADDR  + IPF_DLAD1_MEM_SIZE)
#define IPF_DLCD_MEM_SIZE               (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

#define IPF_ULBD_MEM_ADDR              (IPF_DLCD_MEM_ADDR  + IPF_DLCD_MEM_SIZE)
#define IPF_ULBD_MEM_SIZE               (IPF_ULBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_ULRD_MEM_ADDR              (IPF_ULBD_MEM_ADDR + IPF_ULBD_MEM_SIZE)
#define IPF_ULRD_MEM_SIZE               (IPF_ULRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_ULAD0_MEM_ADDR              (IPF_ULRD_MEM_ADDR + IPF_ULRD_MEM_SIZE)
#define IPF_ULAD0_MEM_SIZE               (IPF_ULAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_ULAD1_MEM_ADDR              (IPF_ULAD0_MEM_ADDR + IPF_ULAD0_MEM_SIZE)
#define IPF_ULAD1_MEM_SIZE               (IPF_ULAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_PWRCTL_BASIC_FILTER_ADDR		(IPF_ULAD1_MEM_ADDR + IPF_ULAD1_MEM_SIZE)
#define IPF_PWRCTL_BASIC_FILTER_SIZE 		(IPF_BF_NUM * sizeof(IPF_MATCH_INFO_S))

#define IPF_EXT_FILTER_ADDR             (IPF_PWRCTL_BASIC_FILTER_ADDR + IPF_PWRCTL_BASIC_FILTER_SIZE)
#define IPF_EXT_FILTER_SIZE 		     (EXFLITER_NUM * sizeof(IPF_MATCH_INFO_S))

#define IPF_PWRCTL_INFO_ADDR		(IPF_EXT_FILTER_ADDR + IPF_EXT_FILTER_SIZE)
#define IPF_PWRCTL_INFO_SIZE           128

#define IPF_PWRCTL_ADQ_WPTR_INFO_ADDR	(IPF_PWRCTL_INFO_ADDR + IPF_PWRCTL_INFO_SIZE)
#define IPF_PWRCTL_ADQ_WPTR_INFO_SIZE       32

#define IPF_PWRCTL_ADQ_RPTR_CHCTRL_ADDR	(IPF_PWRCTL_ADQ_WPTR_INFO_ADDR + IPF_PWRCTL_ADQ_WPTR_INFO_SIZE)
#define IPF_PWRCTL_ADQ_RPTR_CHCTRL_SIZE       64

#define IPF_PWRCTL_ADDR_LIMIT_ADDR	(IPF_PWRCTL_ADQ_RPTR_CHCTRL_ADDR + IPF_PWRCTL_ADQ_RPTR_CHCTRL_SIZE)
#define IPF_PWRCTL_ADDR_LIMIT_SIZE       64

#define IPF_INIT_ADDR                        (IPF_PWRCTL_ADDR_LIMIT_ADDR + IPF_PWRCTL_ADDR_LIMIT_SIZE)
#define IPF_INIT_SIZE                          16

#define IPF_ULBD_IDLENUM_ADDR       (IPF_INIT_ADDR + IPF_INIT_SIZE)
#define IPF_ULBD_IDLENUM_SIZE          16

#define IPF_DLCDRPTR_MEM_ADDR                (IPF_ULBD_IDLENUM_ADDR + IPF_ULBD_IDLENUM_SIZE)
#define IPF_DLCDRPTR_MEM_SIZE                sizeof(unsigned int)

#define IPF_DEBUG_INFO_ADDR           (IPF_DLCDRPTR_MEM_ADDR + IPF_DLCDRPTR_MEM_SIZE)
#define IPF_DEBUG_INFO_SIZE            (sizeof(struct ipf_debug) * 0x2)

#define IPF_TRANS_LIMIT_ADDR       (IPF_DEBUG_INFO_ADDR + IPF_DEBUG_INFO_SIZE)
#define IPF_TRANS_LIMIT_SIZE          32

#define IPF_OUT_ADDR_LIMIT_DEF		(IPF_TRANS_LIMIT_ADDR + IPF_TRANS_LIMIT_SIZE)
#define IPF_OUT_ADDR_LIMIT_SIZE		sizeof(unsigned int)

#define IPF_SHM_USED_END_ADDR    (IPF_OUT_ADDR_LIMIT_DEF + IPF_OUT_ADDR_LIMIT_SIZE)

#define IPF_DLDESC_SIZE   (IPF_DLBD_MEM_SIZE + IPF_DLRD_MEM_SIZE + IPF_DLAD0_MEM_SIZE + IPF_DLAD1_MEM_SIZE + IPF_DLCD_MEM_SIZE)

#define IPF_BF_NUM             		       64  /* 基本过滤器数目 */
#define IPF_TOTAL_FILTER_NUM            256  /* 过滤器总数目先使用一半 */
#define EXFLITER_NUM                         (IPF_TOTAL_FILTER_NUM-IPF_BF_NUM) /* 扩展过滤器数目 */
#define IPF_TAIL_INDEX                       511  /* filter标识最后一个filter */
#define IPF_DISABLE_FILTER                0  /* filter disable*/
#define IPF_FILTERHEAD                      0  /* filter链表头的数据*/
#define IPF_FILTERTYPE_MASK             0xFFFF/*filter类型标示判断位*/
#define IPF_SET_EXT_FILTER             0x10000/*filter类型标示判断位*/
#define IPF_DQ_DEPTH_MASK              0x1FF/*BD、RD队列深度寄存器MASK*/
#define IPF_DQ_PTR_MASK                  0xFF/*BD、RD队列指针MASK*/

#define TIME_OUT_ENABLE                   0x10000 /* 超时计时器使能*/
#define TIME_OUT_CFG                        65           /* 默认超时时间,时钟频率166MHZ下为0.1ms */
#define GATE_CFG                         		0x307           /*设置时钟门控为自动*/
#define IPF_BDWPTR_MUX                    0x100  /*BD写指针互斥量*/
#define IPF_INT_OPEN0                        0x00000C03        /*上行通道中断屏蔽*/
#define IPF_INT_OPEN1                        0x3D030000 /*下行通道中断屏蔽*/

#define IPF_MST_SEC_WR_ERR	  	 		0x10000000
#define IPF_MST_SEC_RD_ERR	  	  		0x20000000

#define IPF_CHANNEL_STATE_IDLE       	0x14 /*通道状态IDLE*/
#define IPF_ADQ_BUF_EPT_MASK            0x00000004
#define IPF_ADQ_BUF_FULL_MASK           0x00000008
#define IPF_ADQ_BUF_MASK                0xFFFFFFF3
#define IPF_ADQ_THR_MASK                0x0000FFFF
#define IPF_ADQ_EN_MASK                 0xFFFFFFFC
#define IPF_ULADQ_PLEN_TH                 404
#define IPF_ACORE_INIT_SUCCESS          0x10000

#define IPF_ADQ_DEFAULT_SEETING     (IPF_ULADQ_PLEN_TH<<16)|(CONFIG_IPF_ADQ_LEN<<4)|(CONFIG_IPF_ADQ_LEN<<2)|(IPF_BOTH_ADQ_EN)
#define IPF_ADQ_OFF                          (IPF_ULADQ_PLEN_TH<<16)|(CONFIG_IPF_ADQ_LEN<<4)|(CONFIG_IPF_ADQ_LEN<<2)|(IPF_NONE_ADQ_EN)

#define IPF_UL_RPT_INT0                     0x1            /*上行结果上报中断0*/
#define IPF_UL_RDQ_FULL                     (0x1 << 8)

#define IPF_UL_TIMEOUT_INT0             0x2            /*上行结果上报超时中断0*/
#define IPF_UL_ADQ0_EPTY_INT0         0x400         /*上行ADQ0空中断0*/
#define IPF_UL_ADQ1_EPTY_INT0         0x800         /*上行ADQ1空中断0*/
#define	IPF_UL_BDQ_EPTY_INT1		  0x200			/*Upload BD empty interrupt*/

#define IPF_DL_RPT_INT1                     0x10000       /*下行结果上报中断0*/
#define IPF_DL_RDQ_FULL                     (0x1 << 24)

#define IPF_DL_TIMEOUT_INT1             0x20000       /*下行结果上报超时中断0*/
#define IPF_DL_RD_FULL_INT1         	0x1000000	  /*下行rd满中断1*/
#define IPF_DL_ADQ0_EPTY_INT1         0x4000000    /*下行ADQ0空中断0*/
#define IPF_DL_ADQ1_EPTY_INT1         0x8000000    /*下行ADQ1空中断0*/

#define SCH_ALL_DESC   	 1
#define	IPF_TIMER_RATIO	(32768)					/*one second*/
#define	IPF_RD_TMOUT	(2 * IPF_TIMER_RATIO)   /*must less than 16 second*/
#define	IPF_LEN_RATIO	(1024*1024)
#define MAX_PM_OM_SAVE_SIZE 	40				/*dpm first packet print cnt*/

#define IPF_PRINT(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, fmt,##__VA_ARGS__)

//K3V5与V711都没有版本控制寄存器
#define IPF_VER_120A	(0x31323061)
#define IPF_VER_130A	(0x31333061)
#define IPF_VER_130B	(0x31333062)
#define IPF_VER_140A	(0x31343061)
enum ipf_version{
	IPF_VERSION_0000  = 0x0,
	IPF_VERSION_120a  = 0x1,		
	IPF_VERSION_130a  = 0x2,
	IPF_VERSION_130b  = 0x3,
	IPF_VERSION_140a  = 0x4,
	IPF_VERSTION_BOTTOM
};

/**************************************************************************
  枚举定义
**************************************************************************/
typedef enum ipf_enable
{
    ipf_disable, 
    ipf_enable, 
    ipf_en_bottom
}ipf_enable_t;

typedef enum tagIPF_FORRESET_CONTROL_E
{
    IPF_FORRESET_CONTROL_ALLOW = 0xabcd1234,     /*允许发送*/
    IPF_FORRESET_CONTROL_FORBID,    /*禁止发送*/
    IPF_FORRESET_CONTROL_MAX
}IPF_FORRESET_CONTROL_E;

/**************************************************************************
  STRUCT定义
**************************************************************************/
typedef struct ipf_ddr {
	unsigned int start;
	
	unsigned int ul_start;

	unsigned int filter_pwc_start;

	unsigned int pwc_info_start;

	unsigned int dlcdrptr;

	unsigned int debug_dlcd_start;
	unsigned int debug_dlcd_size;
	unsigned int end;
	unsigned int len;
} ipf_ddr_t;

struct ipf_debug
{
	int	debug;
	int	init_ok;
	int	mdrv_called_not_init;
	int	ad_epty_intr[IPF_AD_MAX];
	int	ad_epty_cb;
	int	ad_epty_cb_null;
	int	ad_not_enough[IPF_AD_MAX];
	unsigned int ad_thred;
	int	time_out_intr;
	int	rd_comp_intr;
	int	rd_full_intr;
	int	rd_full;
	int	rd_cb;
	int	rd_cb_null;	
	int	bd_epty_intr;
	int	bd_epty_cb;
	int	bd_epty_cb_null;
	int flt_chain_loop;
	int get_rd_times;
	int get_rd_num_times;
	unsigned int	get_rd_cnt[IPF_AD_MAX];
	int get_ad_num_times;
	int cfg_ad_times;
	unsigned int	cfg_ad_cnt[IPF_AD_MAX];
	int	ad_out_ptr_null[IPF_AD_MAX];
	int	busy_cnt;
	int	occupy_cnt;
	int get_bd_num_times;
	int	cfg_bd_times;
	unsigned int	cfg_bd_cnt;
	int	bd_full;
	int	bd_len_zero_err;
	int	cd_not_enough;
	int	suspend;
	int	resume;
	int	resume_with_intr;
	int	timestamp_en;
	int rd_len_update;
	int	rd_len;
	unsigned int	rd_ts;
	int	rate_en;
	int	dump_mem_alloc_ok;
	int invalid_para;
	ipf_ddr_t share_ddr_info;
	int reg_scur_wr_err;
	int reg_scur_rd_err;
	unsigned int ccore_rst_err;
};




typedef union ipf_desc_attr
{
	struct
	{
		unsigned short    int_en        : 1; 
		unsigned short    mode         : 2;
		unsigned short    cd_en         : 1; 
		unsigned short    fc_head      : 3; 
		unsigned short    reserved     : 9; 
	} bits;

	unsigned short u16;
}ipf_desc_attr_t;
	
typedef void (*ipf_bd_empty)(void);

typedef struct tagIPF_UL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;
    unsigned int* pu32IdleBd; /* 记录上一次获取的空闲BD 数 */
#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
    BSP_IPF_WakeupUlCb pFnUlIntCb; /* 中断中唤醒的PS任务 */
    BSP_IPF_AdqEmptyUlCb pAdqEmptyUlCb;/*上行AD空回调C核*/
#endif

#ifdef __KERNEL__
    ipf_bd_empty handle_bd_empty; /* Upload BD empty handler */
#endif

}IPF_UL_S;

typedef struct tagIPF_DL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;

    IPF_CD_DESC_S* pstIpfCDQ;
	
#ifdef __KERNEL__
    BSP_IPF_WakeupDlCb pFnDlIntCb; /* 中断中唤醒的PS任务 */
    BSP_IPF_AdqEmptyDlCb pAdqEmptyDlCb;/*下行AD空回调，A核心*/

/*ACore硬件使用的物理地址*/
    IPF_BD_DESC_S* pstIpfPhyBDQ;
    IPF_RD_DESC_S* pstIpfPhyRDQ;
    IPF_AD_DESC_S* pstIpfPhyADQ0;
    IPF_AD_DESC_S* pstIpfPhyADQ1;

#endif
    unsigned int *u32IpfCdRptr; /* 当前可以读出的位置 */
    unsigned int u32IpfCdWptr;
    unsigned int u32IdleBd; /* 记录上一次获取的空闲BD 数 */
}IPF_DL_S;



typedef struct tagIPF_DEBUG_INFO_S
{
#ifdef __BSP_IPF_DEBUG__
    unsigned int u32IpfDebug;
#endif
    unsigned int u32UlBdqOverflow; /* 中断上报上行BD队列溢出次数 */
    unsigned int u32DlBdqOverflow; /* 中断上报下行BD队列溢出次数 */

    unsigned int ipf_ccore_not_init_count;    /*初始化失败或者ccore单独复位期间试图数传*/
    unsigned int ipf_acore_not_init_count;    /*初始化失败或者ccore单独复位期间试图数传*/

    unsigned int u32UlBdNotEnough;       /* 上行配置BD,BD不够用次数 */
    unsigned int u32UlAd0NotEnough;       /* 上行配置BD,BD不够用次数 */
    unsigned int u32UlAd1NotEnough;       /* 上行配置BD,BD不够用次数 */
    unsigned int u32UlRdNotEnough;       /* 上行配置BD,BD不够用次数 */
    unsigned int u32DlBdNotEnough;       /* 下行配置BD,BD不够用次数 */
    unsigned int u32DlAd0NotEnough;       /* 下行配置BD,BD不够用次数 */
    unsigned int u32DlAd1NotEnough;       /* 下行配置BD,BD不够用次数 */
    unsigned int u32DlRdNotEnough;       /* 下行配置BD,BD不够用次数 */

    unsigned int u32UlAdq0Overflow; /* 中断上报下行BD队列溢出次数 */
    unsigned int u32UlAdq1Overflow; /* 中断上报下行BD队列溢出次数 */
    unsigned int u32DlAdq0Overflow; /* 中断上报下行BD队列溢出次数 */
    unsigned int u32DlAdq1Overflow; /* 中断上报下行BD队列溢出次数 */
    unsigned int u32DlCdNotEnough;       /* 下行配置CD,CD不够用次数 */
    unsigned int u32UlIPFBusyNum;       /* 上行IPF忙次数 */
    unsigned int u32DlIPFBusyNum;       /* 下行IPF忙次数 */
    unsigned int u32UlIPFOccupyNum;       /* 上行IPF核间互斥次数 */
    unsigned int u32DlIPFOccupyNum;       /* 下行IPF核间互斥次数 */

    unsigned int ipf_ulbd_len_zero_count;
    unsigned int ipf_ulad0_error_count;
    unsigned int ipf_ulad1_error_count;
    unsigned int ipf_dlbd_len_zero_count;
    unsigned int ipf_dlad0_error_count;
    unsigned int ipf_dlad1_error_count;

    unsigned int ipf_timestamp_ul_en;
    unsigned int ipf_cfg_ulbd_count;
    unsigned int ipf_ulbd_done_count;
    unsigned int ipf_get_ulrd_count;
    unsigned int ipf_cfg_ulad0_count;
    unsigned int ipf_cfg_ulad1_count;
    unsigned int ipf_ccore_suspend_count;
    unsigned int ipf_ccore_resume_count;
    unsigned int ipf_wakeup_ccore_intr_count;

    unsigned int ipf_timestamp_dl_en;
	unsigned int ipf_rdrate_en;
    unsigned int ipf_cfg_dlbd_count;
    unsigned int ipf_dlbd_done_count;
    unsigned int ipf_get_dlrd_count;
    unsigned int ipf_cfg_dlad0_count;
    unsigned int ipf_cfg_dlad1_count;
    unsigned int ipf_acore_suspend_count;
    unsigned int ipf_acore_resume_count;
    unsigned int ipf_wakeup_acore_intr_count;

	unsigned int dlrd_len_update;	/*Download RD's Total length*/
	unsigned int ulrd_len_update;

	unsigned int dlrd_len;			/*Download RD's Total length for calculating rd rate*/
	unsigned int ulrd_len;
	unsigned int dlrd_ts;			/*Download RD's Timestamp for calculating rd rate*/
	unsigned int ulrd_ts;
	unsigned int dlrd_rate;			/*Download RD's processing rate*/
	unsigned int ulrd_rate;

	ipf_ddr_t share_ddr_info;

	unsigned int ulbd_empty_int;	/*Upload BD empty interrupt count*/
}IPF_DEBUG_INFO_S;

typedef struct tagIPF_LIMIT_ADDR{
	unsigned int block_sum;
	unsigned int block1_start;
	unsigned int block1_end;
	unsigned int block2_start;
	unsigned int block2_end;
	unsigned int block_err;
}IPF_LIMIT_ADDR_S;

int bsp_ipf_srest(void);
void bsp_ipf_set_debug_para(void ** psam_get_debug);
void bsp_set_init_status(int stat);
int bsp_get_init_status(void);

#if defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
int IPF_ConfigCD(void* pstTtf, unsigned short* pu16TotalDataLen, unsigned int* pu32BdInPtr);
void bsp_ipf_dl_rpt1_switch(int value);
int ipf_init(void);
IPF_FORRESET_CONTROL_E bsp_ipf_get_control_flag_for_ccore_reset(void);
void ipf_check_filter_restore(void);

#ifdef CONFIG_MODULE_BUSSTRESS
int ipf_ul_stress_test_start(int task_priority);
#endif

#endif

#ifdef __CMSIS_RTOS
/*****************************************************************************
* 函 数 名       : ipf_drx_bak_reg
*
* 功能描述  : 提供的低功耗接口，保存IPF相关信息
*
* 输入参数  : 无
*
* 输出参数  : 无
* 返 回 值     : IPF_SUCCESS     IPF可以下电，相关信息已经保存
*                           IPF_ERROR        IPF不可以下电
*
* 修改记录  : 2011年2月14日   鲁婷  创建
*****************************************************************************/
int ipf_drx_bak_reg(void);

/*****************************************************************************
* 函 数 名       : ipf_drx_restore_reg
*
* 功能描述  : 提供的低功耗接口，用于IPF上电恢复
*
* 输入参数  : 无
*
* 输出参数  : 无
* 返 回 值     : 无
*
* 注意:该函数需要在锁中断的情况下调用
* 修改记录  : 2011年2月14日   鲁婷  创建
*****************************************************************************/
void ipf_drx_restore_reg(void);
int	bsp_ipf_init(void);

#ifdef CONFIG_BALONG_MODEM_RESET
/*****************************************************************************
* 函 数 名  : bsp_ipf_reset_ccore_lpm3_cb
*
* 功能描述  : 在ccore单独复位流程中，设置ipf reset标记
*
* 输入参数  : 
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2012年11月29日   z00212992  创建
*****************************************************************************/
int bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CB_MOMENT_E eparam, int userdata);
#endif

#endif

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif    /* End #define _BSP_DMAC_H_ */

