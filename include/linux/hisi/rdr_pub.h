/*
 * blackbox header file (blackbox: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __BB_PUB_H__
#define __BB_PUB_H__

#include <linux/module.h>

#include <linux/hisi/rdr_types.h>
#define STR_MODULENAME_MAXLEN		16
#define STR_EXCEPTIONDESC_MAXLEN	48
#define STR_TASKNAME_MAXLEN		16
#define STR_USERDATA_MAXLEN		64

#define PATH_ROOT           "/data/hisi_logs/"
#define RDR_REBOOT_TIMES_FILE    "/data/hisi_logs/reboot_times.log"
#define RDR_ERECOVERY_REASON_FILE    "/cache/recovery/last_erecovery_entry"
#define RDR_UNEXPECTED_REBOOT_MARK_ADDR    0x2846579

#define INT_IN_FLAG             0xAAAAUL
#define INT_EXIT_FLAG           0xBBBBUL

#define BBOX_SAVE_DONE_FILENAME "/DONE"    /*异常文件目录log保存完毕的标志文件名字*/

/* 版本检测宏定义开始 */
#define EDITION_UNKNOWN             0x5A5AA5A5

#define EDITION_INFOR_MAX           5
#define INTERNEL_BETA_FILE_1        "/system/etc/log_collect_service_beta.xml"
#define INTERNEL_BETA_FILE_2        "/data/hw_init/system/etc/log_collect_service_beta.xml"
#define OVERSEA_BETA_FILE_1         "/system/etc/log_collect_service_oversea.xml"
#define OVERSEA_BETA_FILE_2          "/data/hw_init/system/etc/log_collect_service_oversea.xml"

enum EDITION_KIND {
    EDITION_USER                      = 1,
    EDITION_INTERNAL_BETA   = 2,
    EDITION_OVERSEA_BETA    = 3,
    EDITION_MAX
};
/* 版本检测宏定义结束 */

/*异常时，log保存完毕的标志*/
enum SAVE_STEP {
    BBOX_SAVE_STEP1     = 0x1,
    BBOX_SAVE_STEP2     = 0x2,
    BBOX_SAVE_STEP3     = 0x3,
    BBOX_SAVE_STEP_DONE = 0x100
};
/*
该枚举定义两个文件需完全一致
kernel\include\linux\hisi\rdr_pub.h
vendor\hisi\confidential\lpmcu\include\psci.h
*/
enum MODID_LIST {
    HISI_BB_MOD_MODEM_DRV_START             = 0x00000000,
    HISI_BB_MOD_MODEM_DRV_END               = 0x0fffffff,
    HISI_BB_MOD_MODEM_OSA_START             = 0x10000000,
    HISI_BB_MOD_MODEM_OSA_END               = 0x1fffffff,
    HISI_BB_MOD_MODEM_OM_START              = 0x20000000,
    HISI_BB_MOD_MODEM_OM_END                = 0x2fffffff,
    HISI_BB_MOD_MODEM_GU_L2_START           = 0x30000000,
    HISI_BB_MOD_MODEM_GU_L2_END             = 0x3fffffff,
    HISI_BB_MOD_MODEM_GU_WAS_START          = 0x40000000,
    HISI_BB_MOD_MODEM_GU_WAS_END            = 0x4fffffff,
    HISI_BB_MOD_MODEM_GU_GAS_START          = 0x50000000,
    HISI_BB_MOD_MODEM_GU_GAS_END            = 0x5fffffff,
    HISI_BB_MOD_MODEM_GU_NAS_START          = 0x60000000,
    HISI_BB_MOD_MODEM_GU_NAS_END            = 0x6fffffff,
    HISI_BB_MOD_MODEM_GU_DSP_START          = 0x70000000,
    HISI_BB_MOD_MODEM_GU_DSP_END            = 0x7fffffff,
    HISI_BB_MOD_AP_START                    = 0x80000000,
    HISI_BB_MOD_AP_END                      = 0x81fffcff,
    HISI_BB_MOD_ISP_START                   = 0x81fffd00,
    HISI_BB_MOD_ISP_END                     = 0x81fffeff,
    HISI_BB_MOD_EMMC_START                  = 0x81ffff00,
    HISI_BB_MOD_EMMC_END                    = 0x81ffffff,
    HISI_BB_MOD_CP_START                    = 0x82000000,
    HISI_BB_MOD_CP_END                      = 0x82ffffff,
    HISI_BB_MOD_TEE_START                   = 0x83000000,
    HISI_BB_MOD_TEE_END                     = 0x83ffffff,
    HISI_BB_MOD_HIFI_START                  = 0x84000000,
    HISI_BB_MOD_HIFI_END                    = 0x84ffffff,
    HISI_BB_MOD_LPM_START                   = 0x85000000,
    HISI_BB_MOD_LPM_END                     = 0x85ffffff,
    HISI_BB_MOD_IOM_START                   = 0x86000000,
    HISI_BB_MOD_IOM_END                     = 0x86ffffff,
    HISI_BB_MOD_RESERVED_START              = 0x87000000,
    HISI_BB_MOD_RESERVED_END                = 0x9fffffff,
    HISI_BB_MOD_MODEM_LPS_START             = 0xa0000000,
    HISI_BB_MOD_MODEM_LPS_END               = 0xafffffff,
    HISI_BB_MOD_MODEM_LMSP_START            = 0xb0000000,
    HISI_BB_MOD_MODEM_LMSP_END              = 0xbfffffff,
    HISI_BB_MOD_RANDOM_ALLOCATED_START      = 0xc0000000,
    HISI_BB_MOD_RANDOM_ALLOCATED_END        = 0xf0ffffff
};

enum CORE_LIST {
    RDR_AP      = 0x1,
    RDR_CP      = 0x2,
    RDR_TEEOS   = 0x4,
    RDR_HIFI    = 0x8,
    RDR_LPM3    = 0x10,
    RDR_IOM3    = 0x20,
    RDR_ISP     = 0x40,
    RDR_IVP     = 0x80,
    RDR_EMMC    = 0x100,
    RDR_CORE_MAX = 9
};

enum RDR_DUMPCTRL_NVE {
    RDR_DCTRL_AP        = 0x0,
    RDR_DCTRL_CP        = 0x1,
    RDR_DCTRL_TEEOS     = 0x2,
    RDR_DCTRL_HIFI      = 0x3,
    RDR_DCTRL_LPM3      = 0x4,
    RDR_DCTRL_IOM3      = 0x5,
    RDR_DCTRL_ISP       = 0x6,
    RDR_DCTRL_IVP       = 0x7,
    RDR_DCTRL_MAX       = 0x20
};

/*this is for test*/
enum rdr_except_reason_e {
        RDR_EXCE_WD         = 0x01,/*watchdog timeout*/
        RDR_EXCE_INITIATIVE,       /*initictive call sys_error*/
        RDR_EXCE_PANIC,            /*ARM except(eg:data abort)*/
        RDR_EXCE_STACKOVERFLOW,
        RDR_EXCE_DIE,
        RDR_EXCE_UNDEF,
        RDR_EXCE_MAX
};

/*Add, please keep the same as definition in reboot_reason.h in fastboot !!!!*/
/*Add, please keep the same as definition in vendor\hisi\confidential\lpmcu\include\psci.h  !!!!*/
typedef enum
{
    AP_S_COLDBOOT      = 0x0,
    BOOTLOADER         = 0x01,
    RECOVERY           = 0x02,
    RESETFACTORY       = 0x03,
    RESETUSER          = 0x04,
    SDUPDATE           = 0x05,
    CHARGEREBOOT       = 0x06,
    RESIZE             = 0x07,
    ERECOVERY          = 0x08,
    USBUPDATE          = 0x09,
    CUST               = 0x0a,
    USERSDUPDATE       = 0x0b,
    OEM_RTC            = 0x0c,
    RESERVED5          = 0x0d,
    MOUNTFAIL          = 0x0e,
    HUNGDETECT         = 0x0f,
    COLDBOOT           = 0x10,
    RESERVED1          = 0x11,
    AP_S_FASTBOOTFLASH = 0x13,
    REBOOT_REASON_LABEL1 = 0x14,    /*小于REBOOT_REASON_LABEL1的复位原因是一个域，
                                    表示非异常或非blackbox框架使用，流程上是不需要通过框架保存log的*/
    AP_S_ABNORMAL      = REBOOT_REASON_LABEL1,
    AP_S_TSENSOR0      = 0x15,
    AP_S_TSENSOR1      = 0x16,
    AP_S_AWDT          = 0x17,
    LPM3_S_GLOBALWDT   = 0x18,
    G3D_S_G3DTSENSOR   = 0x19,
    LPM3_S_LPMCURST    = 0x1a,
    CP_S_CPTSENSOR     = 0x1b,
    IOM3_S_IOMCURST    = 0x1c,
    ASP_S_ASPWD        = 0x1d,
    CP_S_CPWD          = 0x1e,
    IVP_S_IVPWD        = 0x1f,
    ISP_S_ISPWD        = 0x20,
    AP_S_DDR_UCE_WD      = 0x21,
    AP_S_DDR_FATAL_INTER = 0X22,
    OCBC_S_WD            = 0x23,
    REBOOT_REASON_LABEL2 = 0x24,    /*大于等于REBOOT_REASON_LABEL1，且小于REBOOT_REASON_LABEL2的复位原因是一个域，
                                    表示是sctrl系统状态寄存器记录的异常，流程上不需要框架记录复位原因，但是
                                    在复位之后，需要通过框架保存log*/
    AP_S_PANIC         = REBOOT_REASON_LABEL2,
    AP_S_NOC           = 0x25,
    RESERVED2          = 0x26,
    AP_S_DDRC_SEC      = 0x27,
    RESERVED3          = 0x28,
    AP_S_COMBINATIONKEY = 0x29,
    FASTBOOT_S_PANIC   = 0x2a,
    AP_S_MAILBOX       = 0x2b,
    REBOOT_REASON_LABEL3 = 0x2c,    /*大于等于REBOOT_REASON_LABEL2，且小于REBOOT_REASON_LABEL3的复位原因是一个域，
                                    表示是ap测发起的异常，流程上需要复位之后，通过框架保存log*/
    CP_S_MODEMDMSS     = REBOOT_REASON_LABEL3,
    CP_S_MODEMNOC      = 0x2d,
    CP_S_MODEMAP       = 0x2e,
    CP_S_EXCEPTION     = 0x2f,
    CP_S_RESETFAIL     = 0x30,
    CP_S_NORMALRESET   = 0x31,
    LPM3_S_EXCEPTION   = 0x32,
    SOCHIFI_S_EXCEPTION   = 0x33,
    HIFI_S_RESETFAIL   = 0x34,
    ISP_S_EXCEPTION    = 0x35,
    IVP_S_EXCEPTION    = 0x36,
    IOM3_S_EXCEPTION   = 0x37,
    TEE_S_EXCEPTION    = 0x38,
    MMC_S_EXCEPTION    = 0x39,
    CODECHIFI_S_EXCEPTION  = 0x3a,
    CP_S_RILD_EXCEPTION  = 0x3b,
    CP_S_3RD_EXCEPTION   = 0x3c,
    IOM3_S_USER_EXCEPTION = 0x3d,
    REBOOT_REASON_LABEL4 = 0x40,    /*大于等于REBOOT_REASON_LABEL3，且小于REBOOT_REASON_LABEL4的复位原因是一个域，
                                    表示是非ap发起的复位，包括lpm3、modem、hifi、isp等
                                    流程上是复位之前，通过框架保存log，复位起来之后还需要框架保存一些ap的log*/
    RESERVED4          = REBOOT_REASON_LABEL4,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_USB      = 0x41,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_SD_FORCE = 0x42,
    BR_KEY_VOLUMN_UP                      = 0x43,
    BR_KEY_POWERON_PRESS_1S               = 0x44,
    BR_KEY_POWERON_PRESS_10S              = 0x45,
    BR_CHECKPOINT_RECOVERY                = 0x46,
    BR_CHECKPOINT_ERECOVERY               = 0x47,
    BR_CHECKPOINT_SDUPDATE                = 0x48,
    BR_CHECKPOINT_USBUPDATE               = 0x49,
    BR_CHECKPOINT_RESETFACTORY            = 0x4a,
    BR_CHECKPOINT_HOTAUPDATE              = 0x4b,
    BR_CHECKPOINT_USERSDUPDATE            = 0x4c,
    BR_POWERON_BY_USB_NO_BAT              = 0x4d,
    BR_NOGUI                              = 0x4e,
    BR_FACTORY_VERSION                    = 0x4f,
    BR_RESET_HAPPEN                       = 0x50,
    BR_POWEROFF_ALARM                     = 0x51,
    BR_POWEROFF_CHARGE                    = 0x52,
    BR_POWERON_BY_SMPL                    = 0x53,
    BR_CHECKPOINT_UPDATEDATAIMG           = 0x54,
    BR_REBOOT_CPU_BUCK                    = 0x55,
    REBOOT_REASON_LABEL5                  = 0x65,    /*大于等于REBOOT_REASON_LABEL4，且小于REBOOT_REASON_LABEL5的复位原因是一个域，
                                                     表示框架无关，分配给终端产品线使用*/
    AP_S_PMU                              = REBOOT_REASON_LABEL5,
    AP_S_SMPL                             = 0x66,
    AP_S_SCHARGER                         = 0x67,
    REBOOT_REASON_LABEL6                  = 0x6A,    /*大于等于REBOOT_REASON_LABEL5，且小于REBOOT_REASON_LABEL6的复位原因是一个域，
                                                     表示PMU相关异常，此类异常ddr内容不能保证，不保存kerneldump*/
} EXCH_SOURCE;

enum PROCESS_PRI {
    RDR_ERR      = 0x01,
    RDR_WARN,
    RDR_OTHER,
    RDR_PPRI_MAX
};

enum REBOOT_PRI {
    RDR_REBOOT_NOW      = 0x01,
    RDR_REBOOT_WAIT,
    RDR_REBOOT_NO,
    RDR_REBOOT_MAX
};

enum REENTRANT {
    RDR_REENTRANT_ALLOW = 0xff00da00,
    RDR_REENTRANT_DISALLOW
};

enum UPLOAD_FLAG {
    RDR_UPLOAD_YES = 0xff00fa00,
    RDR_UPLOAD_NO
};


enum RDR_RETURN {
    RDR_SUCCESSED                   = 0x9f000000,
    RDR_FAILD                       = 0x9f000001,
    RDR_NULLPOINTER                 = 0x9f0000ff
};

typedef void (*rdr_e_callback)( u32, void* );

/*
 *   struct list_head   e_list;
 *   u32 modid,			    exception id;
 *		if modid equal 0, will auto generation modid, and return it.
 *   u32 modid_end,		    can register modid region. [modid~modid_end];
		need modid_end >= modid,
 *		if modid_end equal 0, will be register modid only,
		but modid & modid_end cant equal 0 at the same time.
 *   u32 process_priority,	exception process priority
 *   u32 reboot_priority,	exception reboot priority
 *   u64 save_log_mask,		need save log mask
 *   u64 notify_core_mask,	need notify other core mask
 *   u64 reset_core_mask,	need reset other core mask
 *   u64 from_core,		    the core of happen exception
 *   u32 reentrant,		    whether to allow exception reentrant
 *   u32 exce_type,		    the type of exception
 *   char* from_module,		    the module of happen excption
 *   char* desc,		        the desc of happen excption
 *   rdr_e_callback callback,	will be called when excption has processed.
 *   u32 reserve_u32;		reserve u32
 *   void* reserve_p		    reserve void *
 */
struct rdr_exception_info_s {
	struct list_head e_list;
	u32	e_modid;
	u32	e_modid_end;
	u32	e_process_priority;
	u32	e_reboot_priority;
	u64	e_notify_core_mask;
	u64	e_reset_core_mask;
	u64	e_from_core;
	u32	e_reentrant;
    u32 e_exce_type;
    u32 e_upload_flag;
	u8	e_from_module[MODULE_NAME_LEN];
	u8	e_desc[STR_EXCEPTIONDESC_MAXLEN];
	u32	e_reserve_u32;
	void*	e_reserve_p;
	rdr_e_callback e_callback;
};

/*
 * func name: pfn_cb_dump_done
 * func args:
 *    u32   modid
 *      exception id
 *    u64   coreid
 *      which core done
 * return value		null
 */
typedef void (*pfn_cb_dump_done)( u32 modid, u64 coreid);

/*
 * func name: pfn_dump
 * func args:
 *    u32   modid
 *      exception id
 *    u64   coreid
 *      exception core
 *    u32   etype
 *      exception type
 *    char*     logpath
 *      exception log path
 *    pfn_cb_dump_done fndone
 * return       mask bitmap.
 */
typedef void (*pfn_dump)( u32 modid, u32 etype, u64 coreid,
                char* logpath, pfn_cb_dump_done fndone);
/*
 * func name: pfn_reset
 * func args:
 *    u32   modid
 *      exception id
 *    u32   coreid
 *      exception core
 *    u32   e_type
 *      exception type
 * return value		null
 */
typedef void (*pfn_reset)( u32 modid, u32 etype, u64 coreid);

struct rdr_module_ops_pub {
    pfn_dump    ops_dump;
    pfn_reset   ops_reset;
};

struct rdr_register_module_result {
    u64   log_addr;
    u32     log_len;
    RDR_NVE nve;
};

#ifdef CONFIG_HISI_BB
/*
 * func name: rdr_register_exception_type
 * func args:
 *    struct rdr_exception_info_pub* s_e_type
 * return value		e_modid
 *	< 0 error
 *	>=0 success
 */
u32 rdr_register_exception(struct rdr_exception_info_s* e);

/*
 * func name: bb_unregister_exception_type
 * func args:
 *   u32 modid,			exception id;
 * return
 *	< 0 fail
 *	>=0 success
 * u32 bb_unregister_exception(u32 modid);
 */

/*
  * func name: hisi_bbox_map
  * func args:
  *    @paddr: physical address in black box
  *    @size: size of memory
  * return:
  *    success: virtual address
  *    fail: NULL or -ENOMEM
  */
void *hisi_bbox_map(phys_addr_t paddr, size_t size);

/*
  * func name: hisi_bbox_unmap
  * func args:
  *    @addr: virtual address that alloced by hisi_bbox_map
  */
void hisi_bbox_unmap(const void *vaddr);

/*
 * func name: rdr_register_module_ops
 * func args:
 *   u32 coreid,       core id;
 *      .
 *   struct rdr_module_ops_pub* ops;
 *   struct rdr_register_module_result* retinfo
 * return value		e_modid
 *	< 0 error
 *	>=0 success
 */
int rdr_register_module_ops(
        u64 coreid,
        struct rdr_module_ops_pub* ops,
        struct rdr_register_module_result* retinfo
		);

/*
 * func name: bb_unregister_exception_type
 * func args:
 *   u64 coreid,			core id;
 * return
 *	< 0 fail
 *	>=0 success
    u64 rdr_unregister_module_ops_info(u64 coreid);
 */

/*
 * func name: rdr_system_error
 * func args:
 *   u32 modid,			modid( must be registered);
 *   u32 arg1,			arg1;
 *   u32 arg2,			arg2;
 *   char *  data,			short message.
 *   u32 length,		len(IMPORTANT: <=4k)
 * return void
 */
void rdr_system_error(u32 modid, u32 arg1, u32 arg2);

void rdr_syserr_process_for_ap(u32 modid, u64 arg1, u64 arg2);

/*
 * 函数名: bbox_check_edition
 * 函数参数:
 *     void
 * 返回值:
 *     unsigned int:	返回版本信息
 *				0x01        USER
 *				0x02        INTERNAL BETA
 *                         0x03        OVERSEA BETA
 *
 * 该函数会访问用户的data分区，因此依赖于文件系统的正确挂载。
 * 由于没有超时机制，等待文件系统挂载的过程会导致进程进入
 * 不确定时长的睡眠。综上在不能睡眠的场景不能调用该接口。
 */
unsigned int bbox_check_edition(void);

void rdr_set_wdt_kick_slice(void);
#else
static inline void *hisi_bbox_map(phys_addr_t paddr, size_t size){ return NULL; }
static inline u32 rdr_register_exception(struct rdr_exception_info_s* e){ return 0;}
static inline int rdr_register_module_ops(
        u64 coreid,
        struct rdr_module_ops_pub* ops,
        struct rdr_register_module_result* retinfo
		){ return -1; }
static inline void rdr_system_error(u32 modid, u32 arg1, u32 arg2){}
static inline void rdr_syserr_process_for_ap(u32 modid, u64 arg1, u64 arg2){}

static inline unsigned int bbox_check_edition(void){return EDITION_USER;}
static void rdr_set_wdt_kick_slice(void){return;}
#endif

void get_exception_info(unsigned long *buf, unsigned long *buf_len);
#define RDR_REBOOTDUMPINFO_FLAG     0xdd140607

#endif/* End #define __BB_PUB_H__ */

