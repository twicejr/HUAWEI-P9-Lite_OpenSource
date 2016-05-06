/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : plat_firmware.h
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : plat_firmware.c头文件
  函数列表   :

  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PLAT_FIRMWARE_H__
#define __PLAT_FIRMWARE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "plat_type.h"
#include "oal_net.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_exception_rst.h"
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* string */
#define OS_MEM_SET(dst, data, size)         memset(dst, data, size)
#define OS_MEM_CPY(dst, src, size)          memcpy(dst, src, size)
#define OS_MEM_CMP(dst, src, size)          memcmp(dst, src, size)
#define OS_STR_CMP(dst, src)                strcmp(dst, src)
#define OS_STR_LEN(s)                       strlen(s)
#define OS_STR_CHR(str, chr)                strchr(str, chr)
#define OS_STR_STR(dst, src)                strstr(dst, src)

/* memory */
#define OS_MEM_KFREE(p)                     kfree(p)
#define OS_KMALLOC_GFP(size)                kmalloc(size, GFP_KERNEL)
#define OS_KZALLOC_GFP(size)                kzalloc(size, GFP_KERNEL)
#define OS_VMALLOC_GFP(size)                vmalloc(size)
#define OS_MEM_VFREE(p)                     vfree(p)

#define READ_MEG_TIMEOUT            (200)      /* 200ms */
#define READ_MEG_JUMP_TIMEOUT       (100000)   /* 100s */

#define FILE_CMD_WAIT_TIME_MIN      (5000)     /* 5000us */
#define FILE_CMD_WAIT_TIME_MAX      (5100)     /* 5100us */

#define SEND_BUF_LEN                (520)
#define RECV_BUF_LEN                (512)
#define VERSION_LEN                 (64)

#define READ_CFG_BUF_LEN            (2048)

#define DOWNLOAD_CMD_LEN            (32)
#define DOWNLOAD_CMD_PARA_LEN       (800)

#define HOST_DEV_TIMEOUT            (3)
#define INT32_STR_LEN               (32)

#define SHUTDOWN_TX_CMD_LEN         (64)

#define CMD_JUMP_EXEC_RESULT_SUCC   (0)
#define CMD_JUMP_EXEC_RESULT_FAIL   (1)

#define WIFI_MODE_2_4G              (0)
#define WIFI_MODE_5G                (1)

#define SOFT_WCPU_EN_ADDR           "0x50000c00"
#define SOFT_BCPU_EN_ADDR           "0x50000c04"
#define BCPU_DE_RESET_ADDR          "0x50000094"

/*以下是发往device命令的关键字*/
#define VER_CMD_KEYWORD             "VERSION"
#define JUMP_CMD_KEYWORD            "JUMP"
#define FILES_CMD_KEYWORD           "FILES"
#define SETPM_CMD_KEYWORD           "SETPM"
#define SETBUCK_CMD_KEYWORD         "SETBUCK"
#define SETSYSLDO_CMD_KEYWORD       "SETSYSLDO"
#define SETNFCRETLDO_CMD_KEYWORD    "SETNFCRETLDO"
#define SETPD_CMD_KEYWORD           "SETPD"
#define SETNFCCRG_CMD_KEYWORD       "SETNFCCRG"
#define SETABB_CMD_KEYWORD          "SETABB"
#define SETTCXODIV_CMD_KEYWORD      "SETTCXODIV"
#define RMEM_CMD_KEYWORD            "READM"
#define WMEM_CMD_KEYWORD            "WRITEM"
#define QUIT_CMD_KEYWORD            "QUIT"

/*以下命令字不会发往device，用于控制校准流程，但是会体现在cfg文件中*/
#define CALI_COUNT_CMD_KEYWORD      "CALI_COUNT"
#define CALI_BFGX_DATA_CMD_KEYWORD  "CALI_BFGX_DATA"
#define SHUTDOWN_WIFI_CMD_KEYWORD   "SHUTDOWN_WIFI"
#define SHUTDOWN_BFGX_CMD_KEYWORD   "SHUTDOWN_BFGX"

/*以下是device对命令执行成功返回的关键字，host收到一下关键字则命令执行成功*/
#define MSG_FROM_DEV_WRITEM_OK      "WRITEM OK"
#define MSG_FROM_DEV_READM_OK       ""
#define MSG_FROM_DEV_FILES_OK       "FILES OK"
#define MSG_FROM_DEV_READY_OK       "READY"
#define MSG_FROM_DEV_JUMP_OK        "JUMP OK"
#define MSG_FROM_DEV_SET_OK         "SET OK"
#define MSG_FROM_DEV_QUIT_OK        ""

/*以下是cfg文件配置命令的参数头，一条合法的cfg命令格式为:参数头+命令关键字(QUIT命令除外)*/
#define FILE_TYPE_CMD_KEY           "ADDR_FILE_"
#define NUM_TYPE_CMD_KEY            "PARA_"

#define COMPART_KEYWORD             ' '
#define CMD_LINE_SIGN               ';'

#define CFG_INFO_RESERVE_LEN        (8)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum return_type
{
    SUCC = 0,
    EFAIL,
};

enum FIRMWARE_CFG_CMD_ENUM
{
    ERROR_TYPE_CMD = 0,            /* 错误的命令 */
    FILE_TYPE_CMD,                 /* 下载文件的命令 */
    NUM_TYPE_CMD,                  /* 下载配置参数的命令 */
    QUIT_TYPE_CMD,                 /* 退出命令 */
    SHUTDOWN_WIFI_TYPE_CMD,        /* SHUTDOWN WCPU命令 */
    SHUTDOWN_BFGX_TYPE_CMD         /* SHUTDOWN BCPU命令 */
};

/*
*1.首次开机时，使用BFGN_AND_WIFI_CFG，完成首次开机校准，host保存校准数据，完成后device下电
*2.deivce下电状态，开wifi，使用BFGN_AND_WIFI_CFG
*3.deivce下电状态，开bt，使用BFGX_CFG
*4.bt开启，再开wifi，使用WIFI_CFG
*5.wifi开启，再开bt，通过sdio解复位BCPU
*/
enum FIRMWARE_CFG_FILE_ENUM
{
    BFGX_AND_WIFI_CFG = 0,         /*加载BFGIN和wifi fimware的命令数组index，执行独立校准*/
    WIFI_CFG,                      /*只加载wifi firmware的命令数组索引，执行独立校准*/
    BFGX_CFG,                      /*只加载bfgx firmware的命令数组索引，不执行独立校准*/
    RAM_REG_TEST_CFG,              /*产线测试mem reg遍历使用*/

    CFG_FILE_TOTAL
};

enum FIRMWARE_SUBSYS_ENUM
{
    DEV_WCPU = 0,
    DEV_BCPU,
    DEV_CPU_BUTT,
};

/*****************************************************************************
  4 全局变量定义
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct cmd_type_st
{
    int32       cmd_type;
    uint8       cmd_name[DOWNLOAD_CMD_LEN];
    uint8       cmd_para[DOWNLOAD_CMD_PARA_LEN];

}CMD_TYPE_STRUCT;

typedef struct firmware_globals_st
{
    int32            al_count[CFG_FILE_TOTAL];      /*存储每个cfg文件解析后有效的命令个数*/
    CMD_TYPE_STRUCT *apst_cmd[CFG_FILE_TOTAL];      /*存储每个cfg文件的有效命令*/
    uint8            auc_CfgVersion[VERSION_LEN];   /*存储cfg文件中配置的版本号信息*/
    uint8            auc_DevVersion[VERSION_LEN];   /*存储加载时device侧上报的版本号信息*/
}FIRMWARE_GLOBALS_STRUCT;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
typedef struct file OS_KERNEL_FILE_STRU;

/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern int32 firmware_download(uint32 ul_index);
extern int32 firmware_cfg_init(void);
extern int32 firmware_cfg_clear(void);
extern int32 sdio_device_mem_dump(struct st_wifi_dump_mem_info *pst_mem_dump_info, uint32 count);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of plat_firmware.h */
