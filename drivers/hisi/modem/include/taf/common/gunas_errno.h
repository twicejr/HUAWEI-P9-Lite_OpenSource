/******************************************************************************

                  版权所有 (C), 2003-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : gunas_errno.h
  版 本 号   : 初稿
  作    者   : 钟水洪/wx247453
  生成日期   : 2015年8月25日
  最近修改   :
  功能描述   : gunas组件错误码接口的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月25日
    作    者   : 钟水洪/wx247453
    修改内容   : 创建文件

******************************************************************************/

#ifndef __GUNAS_ERRNO_H__
#define __GUNAS_ERRNO_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(push)
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_REBOOT_MOD_ID_ENUM
 枚举说明  : 当前重启的ID类型
 1.日    期   : 2011年12月13日
   作    者   : w00167002
   修改内容   : 新建
 2.日    期   : 2011年12月04日
   作    者   : z00359541
   修改内容   : DTS2015112803743: 将第24 Bit置位以保存其他FID的任务栈信息
*****************************************************************************/
enum NAS_REBOOT_MOD_ID_ENUM
{
    NAS_REBOOT_MOD_ID_MML     = 0X61000000,

    NAS_REBOOT_MOD_ID_MSCC    = 0X62000000,

    NAS_REBOOT_MOD_ID_DYNLOAD = 0X63000000,

    NAS_REBOOT_MOD_ID_XSD     = 0X64000000,
    NAS_REBOOT_MOD_ID_HSD     = 0X65000000,

    NAS_REBOOT_MOD_ID_RILD    = 0x66000000, /*RILD发起单独复位下DRV调用*/
    NAS_REBOOT_MOD_ID_RESET   = 0x67000000, /*单独复位失败情况下DRV调用*/

    NAS_REBOOT_MOD_ID_MEM     = 0x68000000,

    NAS_REBOOT_MOD_ID_BUTT    = 0X6FFFFFFF
};
typedef unsigned int NAS_REBOOT_MOD_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MML_REBOOT_SCEAN_ENUM
 枚举说明  : MM复位场景
 1.日    期   : 2015年1月27日
   作    者   : wx270776
   修改内容   : 新建
*****************************************************************************/
enum NAS_MML_REBOOT_SCEAN_ENUM
{
    NAS_MML_OTHER_REBOOT_SCENE                                                  = 0X00,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED                       = 0X01,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED                       = 0X02,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED                        = 0X03,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED                       = 0X04,

    NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED                     = 0X05,
    NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED                     = 0X06,
    NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED                      = 0X07,
    NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED                     = 0X08,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED                      = 0X09,

    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_LMM_RESUME_IND              = 0X0A,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_WAS_RESUME_IND              = 0X0B,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_TD_RESUME_IND               = 0X0C,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_GAS_RESUME_IND              = 0X0D,

    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_LMM_SUSPEND_IND                 = 0X0E,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_WAS_SUSPEND_IND                 = 0X0F,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_TD_SUSPEND_IND                  = 0X10,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_GAS_SUSPEND_IND                 = 0X11,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE                        = 0X12,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE                        = 0X13,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE                         = 0X14,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE                        = 0X15,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_ERR_IND                                = 0X16,
    NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE                           = 0X17,
    NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE                 = 0X18,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED                = 0x19
};
typedef unsigned char NAS_MML_REBOOT_SCENE_ENUM_UINT8;

#pragma pack(pop)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of gunas_errno.h */
