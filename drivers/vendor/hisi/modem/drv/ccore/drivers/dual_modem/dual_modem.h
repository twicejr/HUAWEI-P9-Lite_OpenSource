/*************************************************************************
*   版权所有(C) 1987-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  dual_modem.h
*
*   作    者 :  张良栋 z00265007
*
*   描    述 :  该文件为双modem通信ccore内部使用头文件
*
*   修改记录 :  2014年02月20日  v1.00  z00265007  创建
*************************************************************************/
/*lint --e{762,760}*/
#ifndef _DUAL_MODEM_H_
#define _DUAL_MODEM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_om.h"
#include "bsp_softtimer.h"
#include "bsp_wakelock.h"
#include "bsp_nvim.h"
#include "bsp_icc.h"
#include "bsp_dpm.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "drv_comm.h"
#include "osl_spinlock.h"
#include "hi_armip_uart.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define UART_RECV_BUF_SIZE     		(1024)

#define DUAL_MODEM_TASK_PRO			28
#define DUAL_MODEM_TASK_STK			3072

#define LPm3_UART5_IQR_ENABLE		(0xaa)
#define LPm3_UART5_IQR_DISABLE		(0)
#define UART_INIT_ENABLE			(0x02)
#define VIA_WAKEUP_BALONG			(0x01)
#define CBP_WAKEUP_DELAY_TIME_MS    (2)

#define dm_print_err(fmt, ...)    	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DUAL_MODEM, "dual_modem: "fmt, ##__VA_ARGS__))
#define dm_trace(fmt, ...)			(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DUAL_MODEM, fmt, ##__VA_ARGS__))
#define dm_debug_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_DUAL_MODEM, "dual_modem: "fmt, ##__VA_ARGS__))

#define DUAL_DUMP_COUNT_SIZE		(0x100)
#define DUAL_DUMP_RX_BUFF_SIZE		(0x800)
#define DUAL_DUMP_TX_BUFF_SIZE		(0x800)
#define GPIO_HIGH		            1
#define GPIO_LOW		            0
#define DUMP_EXT_DUAL_MODEM_SIZE    (0x1400)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum UART_SWITCH_ENUM
{
    DUAl_MODEM_DISABLE = 0,
    DUAl_MODEM_ENABLE  = 1,

	CPCP_FLASE = 0,
	CPCP_TRUE = 1,
    UART_SWITCH_BUTT
};

enum WAKEUP_ENUM
{
	DO_WAKEUP_3RD =0,
	NOT_WAKEUP_V3,	
};

typedef struct DUAL_MODEM_RECV_STR
{
    unsigned int ulRead;
    unsigned int ulWrite;
    unsigned int ulTotalNum;
	unsigned int recv_task_id;
    unsigned int uart_recv_poll_id;
	unsigned int max_size;
    unsigned char ucData[UART_RECV_BUF_SIZE];
}RECV_STR;

struct UART_OPS;

typedef struct _S_UART_PORT_
{
    unsigned int base_addr;
    unsigned int irq_num;
    unsigned int clk;
    unsigned int baudrate;
    pUARTRecv   recv_callback;
    osl_sem_id  send_mutex;
    struct UART_OPS *ops;
	RECV_STR circ_buf;
	unsigned int rts_mask;
}UART_PORT;

struct UART_OPS
{
    int(*send)(UART_PORT *uart_port, unsigned char *pbuf ,unsigned int size);
};

struct dm_dump_info
{
	unsigned int irq_cnt;
    unsigned int irq_SemGive_cnt;
    unsigned int rtask_SemTake_cnt;  			//信号量获取计数	
    unsigned int cbpa_send_cnt;
	unsigned int callback_fail_cnt;
	unsigned int send_mutex_cnt;
	unsigned int recv_register_cnt;
	unsigned int balong_wakeup_via_cnt;			//唤醒重发次数
	unsigned int via_wakeup_balong_cnt;
	unsigned int modem_sleeptimer_cnt;
	unsigned int frame_err_cnt;
	unsigned int circ_buff_err_cnt;
	unsigned int tx_cur_size;
	unsigned int tx_total_size;
	unsigned int rx_cur_size;
	unsigned int rx_total_size;
	unsigned int send_time_stamp;
	unsigned int recv_time_stamp;
	unsigned int suspend_cnt;
	unsigned int resume_cnt;
	unsigned int uart_reg_val[7];
	unsigned int rx_cur_offset;
	unsigned int tx_cur_offset;
	unsigned char *rx_dump_addr;
	unsigned char *tx_dump_addr;
};

struct ap_uart_crg{
	unsigned int crg_addr;
	unsigned int clk_uart_peren;
	unsigned int clk_uart_perdis;
	unsigned int clk_uart_perclken;
	unsigned int clk_uarth_clkdiv;
	unsigned int bit_shift;
};

struct dual_modem_control
{
	struct softtimer_list hold_wake_timer;   //240ms内双方modem通信不用唤醒
	struct softtimer_list sleep_timer;       //300ms内modem不投睡眠票
	struct wake_lock wakelock;				 //睡眠投票
	struct ap_uart_crg ap_uart;
	osl_sem_id wait_reply_mutex;			 //等待对方应答信号量
	osl_sem_id recv_mutex;
	UART_PORT uart_port;
	unsigned int  wakeup_3rdmodem_flag;				 //发送前是否需要唤醒对方标志
	unsigned int init_flag;
	unsigned int log_flag;
	unsigned int nv_flag;
	unsigned int stop_timer_flag;
	unsigned int wakeup_gpio;
	spinlock_t lock;
};

struct dual_modem_icc_msg_str
{
	unsigned int dual_modem_init_flag;
	unsigned int icc_msgs_flag;
};

void dual_modem_restart_timer(struct softtimer_list * softtimer);
int wakeup_via_modem(void);
int dm_print_info(unsigned char *pData, unsigned int ulLength);
int bsp_dual_modem_init(void);
void cpcp_msg_count_record(unsigned int *cnt, char *name);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif /* end of _DUAL_MODEM_H_ */
