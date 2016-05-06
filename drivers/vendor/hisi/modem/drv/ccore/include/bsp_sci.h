/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_sci.h
*
*   作    者 :    Y00171698
*
*   描    述 :  本文件命名为"bsp_sci.h", 为SIM/USIM卡驱动接口.h
*
*   修改记录 :
*************************************************************************/
#ifndef _BSP_SCI_H_
#define _BSP_SCI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"
#include "osl_thread.h"
#include <hi_base.h>
#include "hi_sci.h"
#include "mdrv_sci.h"
#include "bsp_dump.h"
#include "mdrv_pm.h"
#include "bsp_om.h"
#include "osl_sem.h"




#ifndef BSP_CONST
#define BSP_CONST               const
#endif

#define BSP_ERR_SCI_NOTINIT              951
#define BSP_ERR_SCI_INVALIDFREQ          952
#define BSP_ERR_SCI_USEDEFAULT           953
#define BSP_ERR_SCI_INVALIDPARA          954
#define BSP_ERR_SCI_NOCARD               955
#define BSP_ERR_SCI_NODATA               956
#define BSP_ERR_SCI_NOTREADY             957
#define BSP_ERR_SCI_DISABLED             958
#define BSP_ERR_SCI_UNSUPPORTED          959
#define BSP_ERR_SCI_INSERROR             960
#define BSP_ERR_SCI_GETAPDU_ERROR        961
#define BSP_ERR_SCI_VLTG_HIGHEST         962
#define BSP_ERR_SCI_CURRENT_STATE_ERR    963
#define BSP_ERR_SCI_CURRENT_VLTG_ERR     964
#define BSP_ERR_SCI_TIMESTOP_TIMEOUT     965


// card event
#define SCI_EVENT_CARD_IN                0x1
#define SCI_EVENT_CARD_OUT               0x2
#define SCI_EVENT_CARD_DEACTIVE_SUCCESS  0x4
#define SCI_EVENT_CARD_RESET_SUCCESS     0x8
#define SCI_EVENT_CARD_READ_DATA         0x10
#define SCI_EVENT_CARD_TX_ERR            0x20

#define SCI_DEF_CARD_OK     0x0
#define SCI_DEF_CARD_ERROR  0x1

#define BSP_SCI_VLTG_SWITCH_NONEED   (1)


typedef unsigned int (*Sci_Event_Func)(unsigned int u32Event, void* para);

#define SCI_DEF_READ_READY     1
#define SCI_DEF_READ_FORBID    0
#define SD_SCI_PROTOCOL_T0_CHAR 0
#define SD_SCI_PROTOCOL_T1_BLOCK 1
#define SD_SCI_PROTOCOL_NONE 2

#define DEACTIVE_SYNC_DELAY (150)

/*Define PPS process flag*/
#define PPS_RESPONE_READY   0xFA
#define PPS_RESPONE_WORK    0xAF
/*Define delay time to match PPS request start time point after ATR as needed*/
#define PPS_REQUEST_DELAY   40000

#define SCI_DEF_USIM_TYPE  0x2
#define SCI_DEF_SIM_TYPE  0x1
#define SCI_DEF_UNKNOWN_TYPE  0x0

/* print pack */
#define  sci_print_error(fmt, ...)      (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SCI, "[sci]: <%s> [%d]"fmt, __FUNCTION__,g_stSciHwCfg.sci_id, ##__VA_ARGS__))
#define  sci_print_info(fmt, ...)       (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_SCI, "[sci]: <%s> [%d]"fmt, __FUNCTION__,g_stSciHwCfg.sci_id,##__VA_ARGS__))
#define  sci_print_debug(fmt, ...)      (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_SCI, "[sci]: <%s> [%d]"fmt, __FUNCTION__,g_stSciHwCfg.sci_id,g_stSciHwCfg.sci_id, ##__VA_ARGS__))
#define  sci_print_warning(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_SCI, "[sci]: <%s> [%d]"fmt, __FUNCTION__,g_stSciHwCfg.sci_id, ##__VA_ARGS__))
#define  sci_print(fmt, ...)            (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SCI, "[sci]: <%s> [%d]"fmt, __FUNCTION__,g_stSciHwCfg.sci_id,##__VA_ARGS__))
#define SCI_BASE_ADDR g_stSciHwCfg.base_addr

#define EMI_PAD_DIR_INPUT       (0)
#define EMI_PAD_DIR_OUTPUT      (1)


#define SCI_REG_DATA        (SCI_BASE_ADDR + HI_SCI_SCI_DATA_OFFSET)
#define SCI_REG_CTRL0       (SCI_BASE_ADDR + HI_SCI_SCI_CR0_OFFSET)
#define SCI_REG_CTRL1       (SCI_BASE_ADDR + HI_SCI_SCI_CR1_OFFSET)
#define SCI_REG_CTRL2       (SCI_BASE_ADDR + HI_SCI_SCI_CR2_OFFSET)
#define SCI_REG_CLKICC      (SCI_BASE_ADDR + HI_SCI_SCI_CLKICC_OFFSET)
#define SCI_REG_BAUDVALUE   (SCI_BASE_ADDR + HI_SCI_SCI_VALUE_OFFSET)
#define SCI_REG_BAUD        (SCI_BASE_ADDR + HI_SCI_SCI_BAUD_OFFSET)
#define SCI_REG_TIDE        (SCI_BASE_ADDR + HI_SCI_SCI_TIDE_OFFSET)
#define SCI_REG_DMACTRL     (SCI_BASE_ADDR + HI_SCI_SCI_DMACR_OFFSET)
#define SCI_REG_STABLE      (SCI_BASE_ADDR + HI_SCI_SCI_STABLE_OFFSET)
#define SCI_REG_ATIME       (SCI_BASE_ADDR + HI_SCI_SCI_ATIME_OFFSET)
#define SCI_REG_DTIME       (SCI_BASE_ADDR + HI_SCI_SCI_DTIME_OFFSET)
#define SCI_REG_ATRSTIME    (SCI_BASE_ADDR + HI_SCI_SCI_ATRSTIME_OFFSET)
#define SCI_REG_ATRDTIME    (SCI_BASE_ADDR + HI_SCI_SCI_ATRDTIME_OFFSET)
#define SCI_REG_STOPTIME    (SCI_BASE_ADDR + HI_SCI_SCI_STOPTIME_OFFSET)
#define SCI_REG_STARTTIME   (SCI_BASE_ADDR + HI_SCI_SCI_STARTTIME_OFFSET)
#define SCI_REG_RETRY       (SCI_BASE_ADDR + HI_SCI_SCI_RETRY_OFFSET)
#define SCI_REG_CHTIMELS    (SCI_BASE_ADDR + HI_SCI_SCI_CHTIMELS_OFFSET)
#define SCI_REG_CHTIMEMS    (SCI_BASE_ADDR + HI_SCI_SCI_CHTIMEMS_OFFSET)
#define SCI_REG_BLKTIMELS   (SCI_BASE_ADDR + HI_SCI_SCI_BLKTIMELS_OFFSET)
#define SCI_REG_BLKTIMEM    (SCI_BASE_ADDR + HI_SCI_SCI_BLKTIMEMS_OFFSET)
#define SCI_REG_CHGUARD     (SCI_BASE_ADDR + HI_SCI_SCI_CHGUARD_OFFSET)
#define SCI_REG_BLKGUARD    (SCI_BASE_ADDR + HI_SCI_SCI_BLKGUARD_OFFSET)
#define SCI_REG_RXTIME      (SCI_BASE_ADDR + HI_SCI_SCI_RXTIME_OFFSET)
#define SCI_REG_FLAG        (SCI_BASE_ADDR + HI_SCI_SCI_FIFOSTATUS_OFFSET)
#define SCI_REG_TXCOUNT     (SCI_BASE_ADDR + HI_SCI_SCI_TXCOUNT_OFFSET)
#define SCI_REG_RXCOUNT     (SCI_BASE_ADDR + HI_SCI_SCI_RXCOUNT_OFFSET)
#define SCI_REG_INTMASK     (SCI_BASE_ADDR + HI_SCI_SCI_IMSC_OFFSET)
#define SCI_REG_INTRAW      (SCI_BASE_ADDR + HI_SCI_SCI_RIS_OFFSET)
#define SCI_REG_INTSTATUS   (SCI_BASE_ADDR + HI_SCI_SCI_MIS_OFFSET)
#define SCI_REG_INTCLEAR    (SCI_BASE_ADDR + HI_SCI_SCI_ICR_OFFSET)
#define SCI_REG_SYNCACT     (SCI_BASE_ADDR + HI_SCI_SCI_SYNCACT_OFFSET)
#define SCI_REG_SYNCDATA    (SCI_BASE_ADDR + HI_SCI_SCI_SYNCTX_OFFSET)
#define SCI_REG_SYNCRAW     (SCI_BASE_ADDR + HI_SCI_SCI_SYNCRX_OFFSET)

/* sci clk regs */
#define SCI0_CLK_SET_BIT_SHIFT       (12)
#define SCI1_CLK_SET_BIT_SHIFT       (13)


/*Define SIM clock stop mode macro*/
#define CLK_STP_NOT_ALLOWED      0x00
#define CLK_STP_NO_PF_LEVEL      0x01
#define CLK_STP_ALLOWED_HIGH     0x04
#define CLK_STP_HIGH_LEVEL       0x05
#define CLK_STP_ALLOWED_LOW      0x08
#define CLK_STP_LOW_LEVEL        0x09

#define SCI_DEF_ATR_MAX_LENGTH      32
#define SCI_DEF_SEND_MAX_LENGTH     256
#define SCI_DEF_RECEIVE_MAX_LENGTH  256

#define SCI_DEF_RESET_SUCCESS       1
#define SCI_DEF_NOT_RESET           0
#define SCI_MAX_DATA_BUF_LEN    280

/* buffer overflow Begin: */
#define SCI_BUF_MAX_LEN         288  //from 512 to 288 
/* buffer overflow End! */


#define SCI_RECORD_DATA_REAL_LEN    (20*14)
#define SCI_RECORD_PER_DATA_LEN     (14)
#define SCI_RECORD_TOTAL_CNT        (20)

#ifdef BSP_CONFIG_PHONE_TYPE
/* reset bit shift*/
#define SCI_RESET_CARD0_BIT_SHIFT   (23)  
#define SCI_RESET_CARD1_BIT_SHIFT   (24)

/* reset IP Register */
#define SCI_RESET_REG_ADDR          (0x80) 
#define SCI_UNRESET_REG_ADDR        (0x84) 
#endif

/*定义指定段的宏*/
#define __section(S)                    __attribute__((__section__(#S)))
#define __sci_cfg_data                  __section(.sci.cfg.data)
#define __sci_init_data                 __section(.sci.init.data)
#define __sci_record_data               __section(.sci.record.data)

/* card set */
#define SCI_SINGLE                      0  /*卡0*/
#define SCI_SINGLE_MODLEM1              1  /*卡1*/
#define SCI_DUAL                        2  /*双卡*/
#define SCI_THREE                       3  /*三卡*/


/*定义卡槽0、卡槽1的宏*/
#define CARD0                           0
#define CARD1                           1
#define CARD2                           2
#define CARDMAX                         0xff



/*定义卡与SCI0、SCI1之间连接关系的宏*/
#define CARD_CONNECT_SCI0               0
#define CARD_CONNECT_SCI1               1
#define CARD_CONNECT_SCI2               2


/*异常纪录文件路径的定义*/
#define SCI0_RECORD_LOG_PATH_LOST_CARD   "/modem_log/log/"
#define SCI1_RECORD_LOG_PATH_LOST_CARD   "/modem_log/log/"

/*异常纪录文件路径的定义*/
#define SCI0_RECORD_LOG_PATH_CONTROL   "/modem_log/log/sci0_log_list_file.txt"
#define SCI1_RECORD_LOG_PATH_CONTROL   "/modem_log/log/sci1_log_list_file.txt"



/*定义任务名*/
#define SCI_CARD0_SYNC_TASK_NAME        "tSCI0SYSNC"
#define SCI_CARD1_SYNC_TASK_NAME        "tSCI1SYSNC"

/*定义任务名*/
#define SCI_CARD0_HOTPLUG_TASK_NAME        "tSCI0HOTPLUG"
#define SCI_CARD1_HOTPLUG_TASK_NAME        "tSCI1HOTPLUG"



/*DSDA相关的NV项定义*/
#define NV_SCI_LEN                      4

/* pmu nuem */
#define CARD_PM_TYPE_SIM0               "SIM0-vcc"
#define CARD_PM_TYPE_SIM1               "SIM1-vcc"


/* dump addr id */
#define CARD0_EXCP_RECORD_ADDR_NUM      DUMP_CP_SIM0
#define CARD1_EXCP_RECORD_ADDR_NUM      DUMP_CP_SIM1

#define SCI_SEM_DOWN       1
#define SCI_SEM_UP         0



#define SIM_NOT_OUT 1
#define SIM_CARD_LEAVE  3
#define  SIM_CARD_IDLE   4

/*定义SCI初始化函数的类型*/
typedef void (*SCI_INIT_FUNCP)(void);

typedef enum
{   SCI_HOT_PLUG_IDEL,
    SCI_HOT_PLUG_CARD_IN,
    SCI_HOT_PLUG_CARD_PROCESS,
    SCI_HOT_PLUG_CARD_OUT,
}SCI_HOT_PLUG_PROC_STATUS;



typedef enum 
{
    SCI_SLOT_SWITCH_NONE,
    SCI_SLOT_SWITCH_CHANGE,
    SCI_SLOT_SWITCH_BUTTON,
        
} SCI_SLOT_SWITCH_FLAG;

/* debug struct */
typedef struct
{
    u32 sci_debug_base_addr_legth;
    char* sci_debug_base_addr;
}sci_debug_str;

typedef struct
{
    u32 sci_ref_freq;
    u32 sci_work_freq;
}sci_freq_str;/*定义硬件适配的结构*/


typedef struct sem_s
{
    osl_sem_id g_SCIRecvSyncSem ;
    osl_sem_id g_SCIClockStartSem ;
    osl_sem_id g_SCIClockStopSem ;
    osl_sem_id g_SCISynSem;
    osl_sem_id g_SCIDeactiveSyncSem;
    osl_sem_id g_SCIBWTSem;
    osl_sem_id g_SCIHotPlugSem;
}SCI_SEM_S;


typedef enum
{
    AP_SCI_SYS_UNUSE = 0,
    AP_SCI_SYS_USED = 1,
}AP_SCI_SYS_FLAG;

typedef struct sci_sys
{
    AP_SCI_SYS_FLAG ap_sci_sys_flag;
    u32 phy_addr;
    void* virt_addr;
    u32 sci_rst_reg_off ;
    u32 sci_unrst_reg_off ;
    u32 sci0_bit_off;
    u32 sci1_bit_off;
}SCI_SYS_CTRL;
typedef enum
{
    SCI_IP_RST,
    SCI_IP_UNRST,
}SCI_IP_OPERATE_TYPE;

/*定义硬件适配的结构*/
typedef struct
{
    unsigned int card_id;               /*0x00: 卡序号*/
    unsigned int sci_id;                /*0x04:SCI的序列号*/
    unsigned int base_addr;             /*0x08: SCI基地址*/
    unsigned int int_number;            /*0x0C: SCI中断号*/
    unsigned int clk_en_reg;            /*0x10: SCI时钟使能寄存器*/
    unsigned int clk_en_bit;            /*0x14: SCI时钟使能比特*/
    unsigned int clk_dis_reg;           /*0x18: SCI时钟禁止寄存器*/
    unsigned int clk_dis_bit;           /*0x30: SCI时钟禁止比特*/
    unsigned int dma_chan;              /*0x34: SCI读操作DMA通道号*/
    unsigned int record_enum;           /*0x38: 卡对应的异常记录区起始地址*/
    unsigned int icc_chnl;              /* sim detect icc channel */
    char *       record_file;           /*0x44: 卡对应的异常记录文件全路径*/
    unsigned int clk_gate;              /*0x48: 时钟门控的序号*/
    unsigned int sleep_vote;            /*0x4C: 睡眠投票的序号*/
    char * pwr_type;                    /*0x50: 供电类型*/
    char *       syncTaskName;          /*0x68: sync任务名*/  
    char *       hotPlugTaskName;          /*0x68: sync任务名*/
    sci_freq_str sci_freq;
    struct clk*  clk;                   /*0x72:系统时钟*/
    SCI_SLOT_SWITCH_FLAG slot_switch_flag;       /*0x72:   是否进行过卡槽切换*/
    struct regulator* sci_pmu;
    irq_handler_t sci_int_handler;
    OSL_TASK_ID  sync_task_id;    
    OSL_TASK_ID  hotplug_task_id;
    sci_debug_str  g_sci_debug_base;
    SCI_SEM_S  sci_sem;
    SCI_SYS_CTRL sci_sys_ctrl;
}SCI_CFG_STRU;

/*定义NV项的结构*/
typedef union
{
    unsigned int      value;
    struct
    {
    /* bit[0-2]    : 指示支持的多卡的模式:
                        0：单卡0模式；
                        1:     单卡1模式；
                        2：双卡模式；
                        其余：多卡，暂不支持
   */
        unsigned int  card_num      : 3;
        unsigned int  reserved_0    : 5;  /* bit[3-7]    : 保留。 */
        unsigned int  sci0         : 3;  /* bit[8-10]   : 卡0使用的SCI接口。
                                                           0：使用SCI0；
                                                           1：使用SCI1；
                                                         其余值:多卡，暂不支持 */
        unsigned int  sci1         : 3;  /* bit[11-13]  : 卡1使用的SCI接口。
                                                           0：使用SCI0；
                                                           1：使用SCI1；
                                                         其余值:多卡，暂不支持 */
        unsigned int  sci2         : 3;  /* bit[11-13]  : 卡1使用的SCI接口。
                                                           0：使用SCI0；
                                                           1：使用SCI1；
                                                         其余值:多卡，暂不支持*/ 
        unsigned int  reserved_1    : 15;  /* bit[14-31]  : 保留 */
    } cfg;
} NV_SCI_CFG_UNION;

typedef struct RecData
{
    u16 usLength;
    u16 usPrelen;
    u16 usStart;
    u16 *usOutBuf;     /*SCI DMA Rx Data Buffer Pointer*/
    u8  ucRecBuf[SCI_BUF_MAX_LEN]; /* data block */
} SCI_REC_DATA;


/* sim set select  */
typedef enum
{
    SIM_SET_0 = 0,
    SIM_SET_1 = 1
} SCI_SET_SELECT;

typedef struct
{
    u32 ulSciSetAddr;
    u32 ulSciIntNum;
} SCI_SET_SELECT_STR;
/*
 * SCI Rx Mode Flag
 * SCI data receive working mode flag:
 * SCI_RX_CPU_MODE - use CPU to receive data from SCI Rx FIFO;
 * SCI_RX_DMA_MODE - use DMA to receive data from SCI Rx FIFO;
 */
typedef enum sciRxModeFlag
{
    SCI_RX_CPU_MODE = 0,
    SCI_RX_DMA_MODE
}SCI_RX_MODE_FLAG;

/*
 * SCI Rx Data Receive Flag,
 * SCI data receive path:
 * 1 - data rx start -> satisfied -> process -> satisfied -> process -> over;
 * 2 - data rx start -> process -> satisfied -> process -> over;
 * 3 - data rx start -> satisfied -> process -> over;
 */
typedef enum sciRxDataReceiveFlag
{
    SCI_RX_DATA_REC_START     = 0,
    SCI_RX_DATA_REC_OVER      = 1,
    SCI_RX_DATA_REC_SATISFIED = 2,
    SCI_RX_DATA_REC_PROCESS   = 3,
    SCI_RX_DATA_REC_ERROR     = 4
}SCI_RX_DATA_RECEIVE_FLAG;

/*SCI Rx Status Structure*/
/*SCI Rx Status Structure*/
typedef struct sciRxStateStru
{
   SCI_RX_MODE_FLAG         RxModeFlag;
   int                      DmaChnNo;
   SCI_RX_DATA_RECEIVE_FLAG RxDataRecFlag;
}SCI_RX_STATE_STRU;

typedef enum api_mode
{
    SCI_API_NORMAL,
    SCI_API_LLT
}SCI_API_MODE;

typedef enum
{
    SCI_LOWPWR_USIM = 0,
    SCI_LOWPWR_HOTPLUG,
    SCI_LOWPWR_BUTT,
}SCI_LOWPWR_VOTE_E;



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/
extern SCI_CFG_STRU   g_stSciHwCfg;
extern int _sci_cfg_data_start;
extern int _sci_cfg_data_end;
extern int _sci_init_data_start;
extern int _sci_init_data_end;
extern int _sci_record_data_start;
extern int _sci_record_data_end;

/*****************************************************************************
* functions
*
*****************************************************************************/
void sci_init(void);
void I1_sci_init(void);
void I2_sci_init(void);


//
void bsp_sci_func_register(OMSCIFUNCPTR omSciFuncPtr);
void I1_bsp_sci_func_register(OMSCIFUNCPTR omSciFuncPtr);
void I2_bsp_sci_func_register(OMSCIFUNCPTR omSciFuncPtr);


//
s32 bsp_sci_reset(RESET_MODE_E rstMode);
s32 I1_bsp_sci_reset(RESET_MODE_E rstMode);
s32 I2_bsp_sci_reset(RESET_MODE_E rstMode);


//
u32 bsp_sci_card_status_get (void);
u32 I1_bsp_sci_card_status_get (void);
u32 I2_bsp_sci_card_status_get (void);


//
s32 bsp_sci_data_send(u32 ulDataLength, unsigned char *pucDataBuffer);
s32 I1_bsp_sci_data_send(u32 ulDataLength, unsigned char *pucDataBuffer);
s32 I2_bsp_sci_data_send(u32 ulDataLength, unsigned char *pucDataBuffer);


//
s32 bsp_sci_data_read_sync(u32 ulLength, u8 *pucRecData);
s32 I1_bsp_sci_data_read_sync(u32 ulLength, u8 *pucRecData);
s32 I2_bsp_sci_data_read_sync(u32 ulLength, u8 *pucRecData);


//
s32 bsp_sci_all_data_read(u32 *pulLength, u8 *pucRecData);
s32 I1_bsp_sci_all_data_read(u32 *pulLength, u8 *pucRecData);
s32 I2_bsp_sci_all_data_read(u32 *pulLength, u8 *pucRecData);


//
s32 bsp_sci_atr_get(u8 * pulLen, u8 *pucATRData,SCI_ATRINFO_S* stSCIATRInfo);
s32 I1_bsp_sci_atr_get(u8 * pulLen, u8 *pucATRData,SCI_ATRINFO_S* stSCIATRInfo);
s32 I2_bsp_sci_atr_get(u8 * pulLen, u8 *pucATRData,SCI_ATRINFO_S* stSCIATRInfo);


//
u32 bsp_sci_deactive( void );
u32 I1_bsp_sci_deactive( void );
u32 I2_bsp_sci_deactive( void );


//
s32 bsp_sci_vltg_class_switch(void);
s32 I1_bsp_sci_vltg_class_switch(void);
s32 I2_bsp_sci_vltg_class_switch(void);


//
u32 bsp_sci_show_vltg_val(u32 * pu32Vltgval);
u32 I1_bsp_sci_show_vltg_val(u32 * pu32Vltgval);
u32 I2_bsp_sci_show_vltg_val(u32 * pu32Vltgval);


//
u32 bsp_sci_reg_event(u32 u32Event, Sci_Event_Func pFunc);
u32 I1_bsp_sci_reg_event(u32 u32Event, Sci_Event_Func pFunc);
u32 I2_bsp_sci_reg_event(u32 u32Event, Sci_Event_Func pFunc);


//
s32 bsp_sci_get_clk_status(u32 *pulSciClkStatus);
s32 I1_bsp_sci_get_clk_status(u32 *pulSciClkStatus);
s32 I2_bsp_sci_get_clk_status(u32 *pulSciClkStatus);


//
s32 bsp_sci_clk_status_cfg(u32 ucClkStatusMode);
s32 I1_bsp_sci_clk_status_cfg(u32 ucClkStatusMode);
s32 I2_bsp_sci_clk_status_cfg(u32 ucClkStatusMode);

//
s32 bsp_sci_excreset_times(u32 ExcResetTimes) ;
s32 I1_bsp_sci_excreset_times(u32 ExcResetTimes) ;
s32 I2_bsp_sci_excreset_times(u32 ExcResetTimes) ;


//
u32 bsp_sci_record_data_save(SCI_LOG_MODE log_mode) ;
u32 I1_bsp_sci_record_data_save(SCI_LOG_MODE log_mode) ;
u32 I2_bsp_sci_record_data_save(SCI_LOG_MODE log_mode) ;


//appl131 functions
STATUS appl131_get_clk_freq(u32 *len, unsigned char *pbuf);
STATUS I1_appl131_get_clk_freq(u32 *len, unsigned char *pbuf);
STATUS I2_appl131_get_clk_freq(u32 *len, unsigned char *pbuf);


//
STATUS appl131_get_baud_rate(u32 *len, unsigned char *pbuf);
STATUS I1_appl131_get_baud_rate(u32 *len, unsigned char *pbuf);
STATUS I2_appl131_get_baud_rate(u32 *len, unsigned char *pbuf);


//
STATUS appl131_get_pcsc_paremeter(unsigned char *pbuf);
STATUS I1_appl131_get_pcsc_paremeter(unsigned char *pbuf);
STATUS I2_appl131_get_pcsc_paremeter(unsigned char *pbuf);




int bsp_sci_set_bwt(u32 nBWT);
int I1_bsp_sci_set_bwt(u32 nBWT);
int I2_bsp_sci_set_bwt(u32 nBWT);



int bsp_sci_protocol_switch(PROTOCOL_MODE_E enSIMProtocolMode);
int I1_bsp_sci_protocol_switch(PROTOCOL_MODE_E enSIMProtocolMode);
int I2_bsp_sci_protocol_switch(PROTOCOL_MODE_E enSIMProtocolMode);


int bsp_sci_blk_rcv(unsigned char *pu8Data,u32 *pulLength);
int I1_bsp_sci_blk_rcv(unsigned char *pu8Data,u32 *pulLength);
int I2_bsp_sci_blk_rcv(unsigned char *pu8Data,u32 *pulLength);



s32 bsp_sci_record_log_read(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);
s32 I1_bsp_sci_record_log_read(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);
s32 I2_bsp_sci_record_log_read(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);


s32 bsp_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2);
s32 I1_bsp_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2);
s32 I2_bsp_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2);


s32 bsp_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2);
s32 I1_bsp_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2);
s32 I2_bsp_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2);



void sci_set_api_llt_mode();
void sci_clear_api_llt_mode();


void sci_lowpower_vote_lock(SCI_LOWPWR_VOTE_E module);

void sci_lowpower_vote_unlock(SCI_LOWPWR_VOTE_E module);





int bsp_sci_cfg_init(void);

int bsp_sci_cfg(unsigned int card_id, unsigned int sci_id);

int bsp_sci_parse_nv(NV_SCI_CFG_UNION * nv);

int bsp_sci_get_nv(unsigned int * value);

/*pow and clk*/
void pwrctrl_sci_soft_clk_dis(void);

void pwrctrl_sci_soft_clk_en(void);

int pwrctrl_sci_low_power_enter(void);

int pwrctrl_sci_low_power_exit(void);

#endif /*end #ifndef _BSP_DRV_SCI_H_*/



