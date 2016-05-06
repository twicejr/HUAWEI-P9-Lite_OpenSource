
#ifndef __MACH_RESET_H__
#define __MACH_RESET_H__

#include <linux/notifier.h>
#include <linux/semaphore.h>
#include "hifidrvinterface.h"
#include <linux/pstore_ram.h>

/*****************************************************************************
 宏定义
*****************************************************************************/
#define RESET_CPU_CCORE_STATUS_OFF            0x00000001
#define RESET_CPU_MCU_STATUS_OFF              0x00000002
#define RESET_CPU_HIFI_STATUS_OFF             0x00000004
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

/*消息结构宏定义*/
#define RESET_MCU_MSG_CORE_OFFSET               (16)
#define RESET_MCU_MSG_ID(core,phase)            ((core << RESET_MCU_MSG_CORE_OFFSET) | phase)
#define RESET_MCU_MSG_CORE(msg_id)              ((msg_id & 0xFFFF0000) >> RESET_MCU_MSG_CORE_OFFSET)
#define RESET_MCU_MSG_PHASE(msg_id)             (msg_id & 0x0000FFFF)

/*used for stop hifi watchdog1*/
#define DRV_WATCHDOG_LOCK_NUM           (0x0)           /* SP805 WATCHDOG上锁字 */
#define DRV_WATCHDOG_UNLOCK_NUM         (0x1ACCE551)    /* SP805 WATCHDOG解锁字 */
#define DRV_WATCHDOG_CONTROL_DISABLE    (0x0)           /* SP805 WATCHDOG控制字:屏蔽中断并停止，下次打开时会自动重新计数 */
#define DRV_WATCHDOG_INTCLR_NUM         (0x4455)        /* SP805 WATCHDOG中断清除字，实际上写入任意值都可清除 */
/*单独复位模块初始化任务初始化延迟时间*/
#define RESET_MOUDLE_DELAY_TIME          (2)


#define MNTN_PRINTBUF_LEN_MAX		128
#undef MNTN_SAVE_LOG_BY_FILESYS


#define MNTN_PRINT		printk

#ifndef FALSE
#define FALSE               (0)
#endif

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef __MDRV_ACORE_SYSBOOT_H__
typedef enum{
    MDRV_RESET_CB_BEFORE,   /* callback before doing the reset */
    MDRV_RESET_CB_AFTER,    /* callback after reset done */
    MDRV_RESET_RESETTING,   /* callback during doing the reset */
    MDRV_RESET_CB_INVALID,
}DRV_RESET_CB_MOMENT_E;

typedef int (*pdrv_reset_cbfun)(DRV_RESET_CB_MOMENT_E enparam, int userdata);
#endif
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

typedef struct _sreset_debug_info
{
    unsigned int    ulCcpuTaskPhase;
} sreset_debug_info;
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
    BSP_RESET_CORE_CCORE = 0x0,
    BSP_RESET_CORE_HIFI = 0x1,
    BSP_RESET_CORE_INVALID
} ereset_core_with_mcu;
typedef enum
{
    BSP_RESET_PHASE_RESET_BEFORE = 0x0,
    BSP_RESET_PHASE_RESET_AFTER = 0x1,
    BSP_RESET_PHASE_RESET_FINISH = 0x2,
    BSP_RESET_PHASE_INVALID
} ereset_phase_with_mcu;
typedef enum
{
    BSP_RESET_MCU_MSG_CCORE_RESET_BEFORE = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_BEFORE),
    BSP_RESET_MCU_MSG_CCORE_RESET_AFTER = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_AFTER),
    BSP_RESET_MCU_MSG_CCORE_RESET_FINISH = RESET_MCU_MSG_ID(BSP_RESET_CORE_CCORE, BSP_RESET_PHASE_RESET_FINISH),
    BSP_RESET_MCU_MSG_HIFI_RESET_BEFORE = RESET_MCU_MSG_ID(BSP_RESET_CORE_HIFI, BSP_RESET_PHASE_RESET_BEFORE),
    BSP_RESET_MCU_MSG_HIFI_RESET_AFTER = RESET_MCU_MSG_ID(BSP_RESET_CORE_HIFI, BSP_RESET_PHASE_RESET_AFTER),
    BSP_RESET_MCU_MSG_INVALID = RESET_MCU_MSG_ID(BSP_RESET_CORE_INVALID, BSP_RESET_PHASE_INVALID)
} ereset_msg_with_mcu;

typedef enum
{
    RESET_TYPE_FAILGET_MSG_FROM_MCU,        /*处理c核复位，没有收到MCU消息*/
    RESET_TYPE_FAILGET_MSG_FROM_HIFI,       /*处理c核复位，没有收到hifi消息*/
    RESET_TYPE_MSG_FROM_MCU_WRONG,          /*处理c核复位，mcu回复的消息不正确*/
    RESET_TYPE_MSG_FROM_HIFI_WRONG,         /*处理c核复位，hifi回复的消息不正确*/
    RESET_TYPE_CRESET_NOTIFY_BEFORE,        /*处理c核复位，复位前通知出错*/
    RESET_TYPE_CRESET_NOTIFY_AFTER,         /*处理c核复位，复位后通知出错*/
    RESET_TYPE_CRESET_NOTIFY_FINISH,        /*处理c核复位，复位完成通知出错*/
    RESET_TYPE_CRESET_RUNCB_STEP1_FAIL,     /*处理c核复位，加载前运行回调函数出错*/
    RESET_TYPE_CRESET_RUNCB_STEP2_FAIL,     /*处理c核复位，加载后运行回调函数出错*/
    RESET_TYPE_CRESET_DORESET,              /*处理c核复位，复位出错*/
    RESET_TYPE_CRESET_LOAD_BBE16_FAIL,      /*处理c核复位，加载bbe16出错*/
    RESET_TYPE_CRESET_LOAD_CCPU_FAIL,       /*处理c核复位，加载ccpu出错*/
    RESET_TYPE_CRESET_CRUN_NO_OK,           /*c核单独复位后，启动不成功*/

    RESET_TYPE_HIFIRESET_RUNCB_STEP1_FAIL,  /*处理HIFI核复位，加载前运行回调函数出错*/
    RESET_TYPE_HIFIRESET_RUNCB_STEP2_FAIL,  /*处理HIFI核复位，加载后运行回调函数出错*/
    RESET_TYPE_HIFIRESET_LOAD_BIN_FAIL,     /*处理HIFI核复位，加载出错*/

    /*add new above,please!!*/
    RESET_TYPE_FOR_TEST,        /*用于测试*/
    RESET_TYPE_MAX,
} ereset_type;

/*复位类型*/
typedef enum
{
    BSP_RESET_NONE,
    BSP_RESET_TYPE_MDM_PANIC,
    BSP_RESET_TYPE_MCU_PANIC
} ereset_irq_type;

/*域空间枚举定义*/
typedef enum access_domain_type
{
    ACCESS_DOMAIN_NONE,
    ACCESS_DOMAIN_MODEM_SC, /*modem 控制器域*/
    ACCESS_DOMAIN_PERI_SC,  /*外设控制器域*/
    ACCESS_DOMAIN_MEDIA_SC,  /*媒体控制寄存 器域*/
    ACCESS_DOMAIN_MEDIA_NOC,  /*media noc控制寄存器域*/
    ACCESS_DOMAIN_BBE16_DTCM,  /*bbe16 dtcm域*/    
    
    /*Please add above*/
    ACCESS_DOMAIN_MAX
} eACCESS_DOMAIN_TYPE;

/*****************************************************************************
函数引用
*****************************************************************************/
extern int hifireset_runcbfun (DRV_RESET_CB_MOMENT_E eparam);
extern int hifireset_tonotify(DRV_RESET_CB_MOMENT_E eparam, ereset_module emodule);
extern void hifi_freeze_give_semaphone(void);
extern int hifireset_loadhifibin(void);
extern void mailbox_recfun_hifi(void  *UserHandle,void *MailHandle,unsigned int MailLen);
extern sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit);
extern int reset_no_ok_savelog(char *pname, int iresult, DRV_RESET_CB_MOMENT_E eparam, ereset_module emodule);
extern int reset_for_savelog(char *pstr);
extern void reset_hifi_up_semaphone(void);
extern void finish_reset_sub(void);

/*register the notifier to the notify events below*/
int mcu_panic_regsister_notifier(struct notifier_block *n);
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
int hifi_freeze_unregsister_notifier(struct notifier_block *n);
int android_freeze_unregsister_notifier(struct notifier_block *n);
int mcu_freeze_unregsister_notifier(struct notifier_block *n);
int android_reboot_unregsister_notifier(struct notifier_block *n);
int wdg_rstlog_save_unregsister_notifier(struct notifier_block *n);
int acpuwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mculocalwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
int mcuglbwdg_historylog_write_unregsister_notifier(struct notifier_block *n);
void reset_clean_wdt_int(ereset_module emodule);
int mcu_puzzle_unregsister_notifier(struct notifier_block *n);
void save_mcu_log_info(void);
void test_fiq(void);
int drv_read_bin(const char *partion_name, unsigned int offset, unsigned length, char *buffer);
int is_mcu_exception(void);
void set_acore_state(unsigned int core, int state);
void clear_acore_state(unsigned int core);
/*END*/

extern int get_domain_access_status(eACCESS_DOMAIN_TYPE etype);

#endif

