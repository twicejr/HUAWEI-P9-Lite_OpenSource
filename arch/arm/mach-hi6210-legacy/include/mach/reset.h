
#ifndef __MACH_RESET_H__
#define __MACH_RESET_H__

#include <linux/notifier.h>
#include <linux/semaphore.h>
#include "drv_global.h"
#include "drv_reset.h"
#include "drv_udi.h"
#include "drv_icc.h"
#include "hifidrvinterface.h"
/*****************************************************************************
 宏定义
*****************************************************************************/
#define RESET_CPU_CCORE_STATUS_OFF            0x00000001
#define RESET_CPU_MCU_STATUS_OFF            0x00000002
#define RESET_CPU_HIFI_STATUS_OFF            0x00000004
/*CCORE OR hifi 单独复位总控宏*/
#define BSP_C_HIFI_RESET_ALONE_FEATURE
#undef RESET_PRINK_TO_FILE

/*该宏用于控制测试代码*/
#define BSP_C_HIFI_RESET_ALONE_TESET_VALID
#define BSP_RESET_MAILBOX_MSG_PROTECT           0x5a5a5a5a

/*CCORE OR hifi 单独复位,CCORE加载需要安全校验*/
#undef BSP_C_HIFI_RESET_ALONE_SEC_FEATURE

#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)

#define DRV_RESET_MODULE_NAME_LEN       9/*exclude '\0'*/
/*reference to copy from bootloader, fastboot, starts*/
#define EFI_NAMELEN     36

/*一条信息的最大长度*/
#define     BSP_RESET_LOG_INFO_ITEM_LEN     100
/*保存log信息的文件*/
#define     BSP_RESET_LOG_FILE      "log/record/reset_sub.txt"

/*底软回调函数优先级*/
#define     BSP_DRV_CBFUN_PRIOLEVEL         5
/*****************************************************************************
数据结构定义
*****************************************************************************/
/*Record information of callback functions*/
typedef struct
{
    char		name[DRV_RESET_MODULE_NAME_LEN + 1];
    int				priolevel;
    pdrv_reset_cbfun	cbfun;
    int         userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI	*pnext;
} sreset_mgr_LLI;


typedef struct _sreset_mailbox_msg_ccore
{
    int     iproctec;
    int     idata;
    int     ireserved;
} sreset_mailbox_msg_mcu;
/*协助完成单独复位功能的数据定义*/
typedef struct
{
    sreset_mailbox_msg_mcu              smailboxmsg_mcu;
    AP_HIFI_CCPU_RESET_REQ_STRU               smailboxmsg_hifi;
    int               iccore_reset;
    int               ivalue_reg1;      /*保存寄存器原始值，用于做恢复*/
    int               ivalue_reg2;      /*保存寄存器原始值，用于做恢复*/
    unsigned int               icpustatus;           /*每一位用来表示一个cpu状态，从右到左:ccpu,mcu,hifi,0:表示工作正常，1:标示已经复位*/
	UDI_HANDLE        ccorereset_IccFd;
	ICC_CHAN_ATTR_S   attr;
	UDI_OPEN_PARAM    ccorereset_IccParam;
    struct semaphore     sem_wait_ccorereset;
    struct semaphore     sem_wait_ccorereset_ok;
    struct semaphore     sem_wait_hifireset;
    struct semaphore     sem_wait_hifi_msg;
    struct semaphore     sem_wait_mcu_msg;
} sreset_mgr_assistant;

/*****************************************************************************
枚举类型
*****************************************************************************/
/*复位功能涉及的模块*/
typedef enum
{
    BSP_RESET_MODULE_CCORE,
    BSP_RESET_MODULE_HIFI,
    BSP_RESET_MODULE_MCU,
    BSP_RESET_MODULE_ACORE,
    BSP_RESET_MODULE_INVALID
} ereset_module;

/*复位功能涉及的模块*/
typedef enum
{
    BSP_RESET_MCU_MSG_CCORE_TORESET,
    BSP_RESET_MCU_MSG_CCORE_AFTER_RESET,
    BSP_RESET_MCU_MSG_HIFI_TORESET,
    BSP_RESET_MCU_MSG_HIFI_AFTER_RESET,
    BSP_RESET_MCU_MSG_INVALID
} ereset_msg_with_mcu;

typedef enum 
{
    RESET_TYPE_FAILGET_MSG_FROM_MCU,  /*处理c核复位，没有收到MCU消息*/
    RESET_TYPE_FAILGET_MSG_FROM_HIFI, /*处理c核复位，没有收到hifi消息*/        
    RESET_TYPE_MSG_FROM_MCU_WRONG,      /*处理c核复位，mcu回复的消息不正确*/
    RESET_TYPE_MSG_FROM_HIFI_WRONG, /*处理c核复位，hifi回复的消息不正确*/
    RESET_TYPE_CRESET_RUNCB_STEP1_FAIL,   /*处理c核复位，加载前运行回调函数出错*/
    RESET_TYPE_CRESET_RUNCB_STEP2_FAIL,   /*处理c核复位，加载后运行回调函数出错*/
    RESET_TYPE_CRESET_LOAD_BIN_FAIL,   /*处理c核复位，加载出错*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP1_FAIL,   /*处理HIFI核复位，加载前运行回调函数出错*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP2_FAIL,   /*处理HIFI核复位，加载后运行回调函数出错*/
    RESET_TYPE_HIFIRESET_LOAD_BIN_FAIL,     /*处理HIFI核复位，加载出错*/
    RESET_TYPE_CRESET_CRUN_NO_OK,           /*c核单独复位后，启动不成功*/

    /*add new above,please!!*/
    RESET_TYPE_FOR_TEST,        /*用于测试*/
    RESET_TYPE_MAX,
} ereset_type;
/*****************************************************************************
函数引用
*****************************************************************************/
extern int ccorereset_loadcbin(void);
extern int ccorereset_loadbbebin(void);
extern int hifireset_loadhifibin(void);
extern void mailbox_recfun_mcu(void  *UserHandle,void *MailHandle,unsigned int MailLen);
extern void mailbox_recfun_hifi(void  *UserHandle,void *MailHandle,unsigned long MailLen);
extern sreset_mgr_LLI * reset_do_regcbfunc(sreset_mgr_LLI *plink, const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
extern int ccorereset_task(void *arg);
extern int hifireset_task(void *arg);
extern int reset_sub_mgr_init (void);
extern int ccorereset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam);
extern int hifireset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam);
extern sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit);
extern int ccorereset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int hifireset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int ccorereset_setCresetFlag(void);
extern int ccorereset_doreset(void);
extern int ccorereset_dostart(void);
extern unsigned int ccorereset_icc_cok_notify(unsigned int chenalId,signed int u32size);
extern int drv_ccorereset_cbfun(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
extern int reset_icc_open(void);
extern int  set_for_cshell(DRV_RESET_CALLCBFUN_MOMENT eparam);
extern int  close_all_filehandle(DRV_RESET_CALLCBFUN_MOMENT eparam);
extern void  do_reset_system(int ireset_type);
extern int reset_no_ok_savelog(char *pname, int iresult, DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule);
extern int reset_for_savelog(char *pstr);
extern void reset_ccore_up_semaphone(void);
extern void reset_hifi_up_semaphone(void);
extern void finish_reset_sub(void);
extern void reset_clean_wdt_int(ereset_module emodule);

/*register the notifier to the notify events below*/
int mcu_panic_regsister_notifier(struct notifier_block *n);
int modem_panic_regsister_notifier(struct notifier_block *n);
int modem_freeze_regsister_notifier(struct notifier_block *n);
int modem_reboot_regsister_notifier(struct notifier_block *n);
int hifi_freeze_regsister_notifier(struct notifier_block *n);
int android_freeze_regsister_notifier(struct notifier_block *n);
int mcu_freeze_regsister_notifier(struct notifier_block *n);
int android_reboot_regsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_regsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_regsister_notifier(struct notifier_block *n);
int mcu_puzzle_regsister_notifier(struct notifier_block *n);

/*unregister the notifier from the notify events below*/
int mcu_panic_unregsister_notifier(struct notifier_block *n);
int modem_panic_unregsister_notifier(struct notifier_block *n);
int modem_reboot_unregsister_notifier(struct notifier_block *n);
int modem_freeze_unregsister_notifier(struct notifier_block *n);
int hifi_freeze_unregsister_notifier(struct notifier_block *n);
int android_freeze_unregsister_notifier(struct notifier_block *n);
int mcu_freeze_unregsister_notifier(struct notifier_block *n);
int android_reboot_unregsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_unregsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcu_puzzle_unregsister_notifier(struct notifier_block *n);
void save_mcu_log_info(void);
#endif

