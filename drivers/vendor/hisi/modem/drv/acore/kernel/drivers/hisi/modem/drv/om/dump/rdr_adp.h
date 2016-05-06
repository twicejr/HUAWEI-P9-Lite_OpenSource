/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __RDR_ADP_H__
#define __RDR_ADP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/semaphore.h>
#include <linux/module.h>
#include "osl_common.h"
#include "osl_list.h"

#ifndef CONFIG_HISI_BB
#define STR_MODULENAME_MAXLEN		16
#define STR_EXCEPTIONDESC_MAXLEN	48
#define RDR_ADP_MAX_WAIT_CNT        600
#define RDR_ADP_LOG_PATH            "/modem_log/dump/"

enum EDITION_KIND{
    EDITION_USER            = 1,
    EDITION_INTERNAL_BETA   = 2,
    EDITION_OVERSEA_BETA    = 3,
    EDITION_MAX
};

enum CORE_LIST
{
    RDR_AP      = 0x1,
    RDR_CP      = 0x2,
    RDR_TEEOS   = 0x4,
    RDR_HIFI    = 0x8,
    RDR_LPM3    = 0x10,
    RDR_IOM3    = 0x20,
    RDR_ISP     = 0x40,
    RDR_IVP     = 0x80,
    RDR_CORE_MAX = 8
};

enum rdr_except_reason_e
{
    RDR_EXCE_WD         = 0x01,/*watchdog timeout*/
    RDR_EXCE_INITIATIVE,       /*initictive call sys_error*/
    RDR_EXCE_PANIC,            /*ARM except(eg:data abort)*/
    RDR_EXCE_STACKOVERFLOW,
    RDR_EXCE_DIE,
    RDR_EXCE_UNDEF,
    RDR_EXCE_MAX
};

enum EXCH_SOURCE
{
    BOOTLOADER = 0x01,
    RECOVERY,
    RESETFACTORY,
    RESETUSER,
    SDUPDATE,
    CHARGEREBOOT,
    RESIZE,
    MODEMUPDATE,
    USBUPDATE,
    CUST,
    USERSDUPDATE,
    OEM_RTC,
    SOFTRESET,
    HUNGDETECT,
    MOUNTFAIL,
    COLDBOOT,
    RESERVED1 = 0x11,
    AP_S_FASTBOOTFLASH = 0x12,
    AP_S_COLDBOOT,
    AP_S_ABNORMAL,
    AP_S_TSENSOR0,
    AP_S_TSENSOR1,
    AP_S_AWDT,
    LPM3_S_GLOBALWDT,
    G3D_S_G3DTSENSOR,
    LPM3_S_LPMCURST,
    CP_S_CPTSENSOR,
    IOM3_S_IOMCURST,
    ASP_S_ASPWD,
    CP_S_CPWD,
    IVP_S_IVPWD,
    ISP_S_ISPWD,
    AP_S_DDR_SELFREFLASH,
    RESERVED2 = 0x23,
    AP_S_PANIC = 0x24,
    AP_S_NOC,
    AP_S_PMU,
    AP_S_DDRC_SEC,
    AP_S_GPIO,
    AP_S_COMBINATIONKEY,
    AP_S_DIE,
    RESERVED3 = 0x2e,
    CP_S_MODEMAP,
    CP_S_EXCEPTION,
    CP_S_RESETFAIL,
    CP_S_NORMALRESET,
    CP_S_MODEMNOC,
    CP_S_MODEMDMSS,
    CP_S_RILD_EXCEPTION,
    CP_S_3RD_EXCEPTION,
    LPM3_S_EXCEPTION,
    HIFI_S_EXCEPTION,
    HIFI_S_RESETFAIL,
    ISP_S_EXCEPTION,
    IVP_S_EXCEPTION,
    IOM3_S_EXCEPTION,
    TEE_S_EXCEPTION,
    RESERVED4 = 0x40,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_USB = 0x41,
    BR_KEY_VOLUMN_DOWN_UP_UPDATE_SD_FORCE,
    BR_KEY_VOLUMN_UP,
    BR_KEY_POWERON_PRESS_1S,
    BR_KEY_POWERON_PRESS_10S,
    BR_CHECKPOINT_SDUPDATE,
    BR_CHECKPOINT_USBUPDATE,
    BR_CHECKPOINT_RESETFACTORY,
    BR_CHECKPOINT_HOTAUPDATE,
    BR_POWERON_BY_USB_NO_BAT,
    BR_NOGUI,
    BR_FACTORY_VERSION,
    BR_RESET_HAPPEN,
    BR_POWEROFF_ALARM,
    BR_POWEROFF_CHARGE,
};

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

typedef void (*rdr_e_callback)(u32, void*);
typedef void (*pfn_cb_dump_done)(u32 modid, u64 coreid);
typedef u32  (*pfn_dump)(u32 modid, u32 etype, u64 coreid, char* logpath, pfn_cb_dump_done fndone);
typedef void (*pfn_reset)(u32 modid, u32 etype, u64 coreid);


struct rdr_exception_info_s
{
    struct list_head e_list;
    u32     e_modid;
    u32     e_modid_end;
    u32     e_process_priority;
    u32     e_reboot_priority;
    u64     e_notify_core_mask;
    u64     e_reset_core_mask;
    u64     e_from_core;
    u32     e_reentrant;
    u32     e_exce_type;
    u32     e_upload_flag;
	u8	    e_from_module[MODULE_NAME_LEN];
	u8	    e_desc[STR_EXCEPTIONDESC_MAXLEN];
    u32     e_reserve_u32;
    void*   e_reserve_p;
    rdr_e_callback e_callback;
};

struct rdr_module_ops_pub
{
    pfn_dump    ops_dump;
    pfn_reset   ops_reset;
};

struct rdr_register_module_result
{
    u64         log_addr;
    u32         log_len;
    u64         nve;
};

struct rdr_adp_ctrl_s
{
    u32         cp_done_flag;
    u32         modid;
    struct semaphore           adp_task_sem;
    struct rdr_module_ops_pub  soc_ops;
};

u32 rdr_register_exception(struct rdr_exception_info_s* e);
int rdr_register_module_ops(u64 coreid, struct rdr_module_ops_pub* ops, struct rdr_register_module_result* retinfo);
void rdr_system_error(u32 modid, u32 arg1, u32 arg2);
unsigned int bbox_check_edition(void);
#else
#include "../../adrv/adrv.h"

#endif //CONFIG_HISI_BB

/* rdr为CP分配的ID范围为0x82000000~0x82ffffff，定义在rdr_pub.h中*/
#define RDR_MODEM_AP_MOD_ID                   0x82000000  /* AP异常，保存log，整机复位，phone和mbb都有 */
#define RDR_MODEM_CP_MOD_ID                   0x82000001  /* CP异常，保存log，phone和mbb都有 */
#define RDR_MODEM_CP_WDT_MOD_ID               0x82000003  /* CP看门狗异常，保存log，phone和mbb都有 */
#define RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID  0x82000005  /* 切卡引起的CP单独复位，不保存log，phone独有 */
#define RDR_MODEM_CP_RESET_FAIL_MOD_ID        0x82000006  /* CP单独复位失败，保存log，phone独有 */
#define RDR_MODEM_CP_RESET_RILD_MOD_ID        0x82000007  /* RILD引起的CP单独复位，保存log，phone独有*/
#define RDR_MODEM_CP_RESET_3RD_MOD_ID         0x82000008  /* 3rd modem引起的CP单独复位，保存log，phone独有*/
#define RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID  0x82000009  /* CP单独复位为桩时，整机复位，保存log，phone独有*/
#define RDR_MODEM_CP_RESET_USER_RESET_MOD_ID  0x82000010  /* CP单独复位,用户发起，不保存log,PHONE 独有*/
#define RDR_MODEM_LPM3_MOD_ID                 0x82000020  /* LPM3异常, 保存log，mbb独有 */
#define RDR_MODEM_NOC_MOD_ID                  0x82000030  /* NOC异常, 保存log，phone独有, */
                                                          /*   如果要修改者定义一定要知会AP侧同步修改，否则会导致NOC异常log存储不下来 */
#define RDR_MODEM_DMSS_MOD_ID                  0x82000031  /* DMSS异常, 保存log，phone独有, */


#define RDR_DUMP_FILE_PATH_LEN                128
#define RDR_DUMP_FILE_CP_PATH                 "cp_log/"
#define RDR_MODEM_CP_RESET_TIMEOUT            (30000)
typedef struct
{
    u32     modid;
    u32     product_type;
    u64     coreid;
    char    log_path[RDR_DUMP_FILE_PATH_LEN];
    pfn_cb_dump_done    dump_done;
    struct rdr_register_module_result soc_rst;
}rdr_exc_info_s;

#ifdef __cplusplus
}
#endif

#endif //__RDR_ADP_H__

