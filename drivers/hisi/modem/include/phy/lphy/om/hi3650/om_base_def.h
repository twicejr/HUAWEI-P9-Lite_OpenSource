/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : om_interface.h
  版 本 号   : 初稿
  作    者   : l00131321
  生成日期   : 2011年1月19日
  最近修改   :
  功能描述   : om_interface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年1月19日
    作    者   : l00131321
    修改内容   : 创建文件

  2.日    期   : 2011年2月26日
    作    者   : t52067
    修改内容   : 整理实现

  3.日    期   : 2011年05月26日
    作    者   : tuzhiguo(52067)
    修改内容   : 增加总开关、子模块开关，上报类型开关

  4.日    期   : 2011年7月13日
    作    者   : Shen Guang
    修改内容   : DTS2011071303355 新增DCOC/RXIQ特性

  5.日    期   : 2011年9月20日
    作    者   : zengshangyou
    修改内容   : DTS2011090203399 新增CT 模块邮箱ID

  6.日    期   : 2011年10月8日
    作    者   : zengshangyou
    修改内容   : DTS2011092600031 新增BT 模块邮箱ID

  7.日    期   : 2011年12月3日
    作    者   : zengshangyou
    修改内容   : DTS2011112507095 新增非信令综测 模块邮箱ID

  8.日    期   : 2012年4月18日
     作    者   : sunyanjie，yushujing，xueqiuyan
     修改内容   : [DTS2012041802974]OM优化修改
******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __OM_BASEDEF_H__
#define __OM_BASEDEF_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "type_define.h"


#define __UNIFIED_NEW_OM_MSG_TYPE__
#ifndef __UNIFIED_NEW_OM_MSG_TYPE__


/*
    定义LPHY子系统ID
*/
#define SUBSYSTEM_LPHY  (0x3)

/*
    定义LTE 子模块ID, 共5比特表示
*/
#define LPHY_RSV_MID        (0x0)
#define LPHY_RFE_MID        (0x1)
#define LPHY_AGC_MID        (0x2)
#define LPHY_AFC_MID        (0x3)
#define LPHY_CSU_MID        (0x4)
#define LPHY_CMU_MID        (0x5)
#define LPHY_EMU_MID        (0x6)
#define LPHY_CHE_MID        (0x7)
#define LPHY_DEM_MID        (0x8)
#define LPHY_LPC_MID        (0x9)
#define LPHY_CQI_MID        (0xA)
#define LPHY_CORR_MID       (0xB)
#define LPHY_SYNC_MID       (0xC)
#define LPHY_TIMING_MID     (0xD)
#define LPHY_DRX_MID        (0xE)
#define LPHY_SERV_MID       (0xF)
#define LPHY_UL_MID         (0x10)
#define LPHY_CHANCTRL_MID   (0x11)
#define LPHY_OM_MID         (0x12)
#define LPHY_DMA_MID        (0x13)
#define LPHY_VITERBI_MID    (0x14)
#define LPHY_TURBO_MID      (0x15)
#define LPHY_SCHED_MID      (0x16)
#define LPHY_INTERRUPT_MID  (0x17)
#define LPHY_DCOC_MID       (0x18)
#define LPHY_RXIQ_MID       (0x19)
#define LPHY_CT_MID         (0x1a)
#define LPHY_BT_MID         (0x1B)
#define LPHY_NCIT_MID   	(0x1C)
#define LPHY_EMBMS_MID      (0x1D)
#define LPHY_RFD_MID        (0x1E)
#define LPHY_LS_MID         (0x1F)
#define LPHY_LWCOEX_MID     LPHY_RSV_MID /*MID已经没有空余，借用保留位*/
#define LPHY_MAX_MID        (32)

/*
    定义TPHY子系统ID
*/
#define SUBSYSTEM_TPHY  (0x7)
/*
    定义TDS 子模块ID, 共5比特表示
*/
#define TPHY_TRACE_INFO     (0x0)
#define TPHY_RFDRV_MID      (0x1)
#define TPHY_AGC_MID        (0x2)
#define TPHY_AFC_MID        (0x3)
#define TPHY_CS_MID         (0x4)
#define TPHY_CMU_MID        (0x5)
#define TPHY_MEAS_MID       (0x6)
#define TPHY_CHE_MID        (0x7)
#define TPHY_DATA_MID       (0x8)
#define TPHY_CORR_MID       (0x9)       /*未定义*/
#define TPHY_CQI_MID        (0xA)
#define TPHY_PC_MID         (0xB)
#define TPHY_SYNC_MID       (0xC)
#define TPHY_TIMING_MID     (0xD)
#define TPHY_DRX_MID        (0xE)
#define TPHY_SERV_MID       (0xF)
#define TPHY_UL_MID         (0x10)
#define TPHY_CHANCTRL_MID   (0x11)
#define TPHY_OM_MID         (0x12)
#define TPHY_DMA_MID        (0x13)
#define TPHY_CD_MID         (0x14)
#define TPHY_VIT_TURBO_MID  (0x15)
#define TPHY_SCHED_MID      (0x16)
#define TPHY_INT_MID        (0x17)
#define TPHY_JD_MID         (0x18)
#define TPHY_DCOC_MID       (0x19)
#define TPHY_RXIQ_MID       (0x1a)
#define TPHY_CT_MID         (0x1B)
#define TPHY_BT_MID         (0x1C)
#define TPHY_NCIT_MID       (0x1D)
#define TPHY_MAX_MID        (32)


/*
    定义消息类型的宏，占3比特
*/
#define OM_TYPE_REQ         (0x0)           /*HiStudio下发的原语命令类型*/
#define OM_TYPE_CNF         (0x1)           /*收到HiStudio的原语后，立即回复的确认*/
#define OM_TYPE_DT          (0x2)           /*回复现场测试原语，对外给客户*/
#define OM_TYPE_SG          (0x3)           /*回复算法图形需求，内部观测用*/
#define OM_TYPE_TRACE       (0x4)           /*主动上报各个子模块的运行历史轨迹*/
#define OM_TYPE_DEBUG       (0x5)           /*主动上报的DEBUG信息*/
#define OM_TYPE_ERROR       (0x6)           /*主动上报的状态错误信息*/
#define OM_TYPE_IND         (0x7)           /*其它上报的类型*/

/*
    定义消息ID函数组成方法
    将子系统ID, 子模块ID, 类型，各个子模块内部的消息id合成一个消息ID
*/
#define OM_CMD_ID(mid, type, msg_id)  ((SUBSYSTEM_LPHY<<28)|(mid<<19)|(type<<16)|(msg_id))
#define OM_LCMD_ID(mid, type, msg_id) ((SUBSYSTEM_LPHY<<28)|(mid<<19)|(type<<16)|(msg_id))
#define OM_TCMD_ID(mid, type, msg_id) ((SUBSYSTEM_TPHY<<28)|(mid<<19)|(type<<16)|(msg_id))


#define OM_GET_SYS(om_msg_id) 	((om_msg_id >> 28) & 0x0007)
#define OM_GET_MID(om_msg_id) 	((om_msg_id >> 19) & 0x001f)
#define OM_GET_TYPE(om_msg_id) 	((om_msg_id >> 16) & 0x0007)
#define OM_GET_ID(om_msg_id)  	((om_msg_id >> 00) & 0xffff)

#else

/*
    定义LPHY子系统ID
*/
#define PHY_SUBSYSTEM_ID    (0x3)

#define PHY_LPHY_SUB_ID     (0x0)
#define PHY_TPHY_SUB_ID     (0x1)
#define PHY_GPHY_SUB_ID     (0x2)
#define PHY_WPHY_SUB_ID     (0x3)
#define PHY_XPHY_SUB_ID     (0x4)
#define PHY_EVDO_SUB_ID     (0x5)
#define PHY_PUB__SUB_ID     (0xf)

/*兼容原版本*/
#define SUBSYSTEM_LPHY      (PHY_LPHY_SUB_ID)
#define SUBSYSTEM_TPHY      (PHY_TPHY_SUB_ID)


#define PHY_L1_MSG_SUB_ID   (0x0)
#define PHY_L1_PRN_SUB_ID   (0x9)


/*
    定义LTE 子模块ID, 共5比特表示
*/
#define LPHY_RSV_MID        (0x0)
#define LPHY_RFE_MID        (0x1)
#define LPHY_AGC_MID        (0x2)
#define LPHY_AFC_MID        (0x3)
#define LPHY_CSU_MID        (0x4)
#define LPHY_CMU_MID        (0x5)
#define LPHY_EMU_MID        (0x6)
#define LPHY_CHE_MID        (0x7)
#define LPHY_DEM_MID        (0x8)
#define LPHY_LPC_MID        (0x9)
#define LPHY_CQI_MID        (0xA)
#define LPHY_CORR_MID       (0xB)
#define LPHY_SYNC_MID       (0xC)
#define LPHY_TIMING_MID     (0xD)
#define LPHY_DRX_MID        (0xE)
#define LPHY_SERV_MID       (0xF)
#define LPHY_UL_MID         (0x10)
#define LPHY_CHANCTRL_MID   (0x11)
#define LPHY_OM_MID         (0x12)
#define LPHY_DMA_MID        (0x13)
#define LPHY_VITERBI_MID    (0x14)
#define LPHY_TURBO_MID      (0x15)
#define LPHY_SCHED_MID      (0x16)
#define LPHY_INTERRUPT_MID  (0x17)
#define LPHY_DCOC_MID       (0x18)
#define LPHY_RXIQ_MID       (0x19)
#define LPHY_CT_MID         (0x1a)
#define LPHY_BT_MID         (0x1B)
#define LPHY_NCIT_MID   	(0x1C)
#define LPHY_EMBMS_MID      (0x1D)
#define LPHY_RFD_MID        (0x1E)
#define LPHY_LS_MID         (0x1F)
#define LPHY_LWCOEX_MID     LPHY_RSV_MID /*MID已经没有空余，借用保留位*/
#define LPHY_MAX_MID        (64)

/*
    定义TPHY子系统ID
*/
/*
    定义TDS 子模块ID, 共5比特表示
*/
#define TPHY_TRACE_INFO     (0x0)
#define TPHY_RFDRV_MID      (0x1)
#define TPHY_AGC_MID        (0x2)
#define TPHY_AFC_MID        (0x3)
#define TPHY_CS_MID         (0x4)
#define TPHY_CMU_MID        (0x5)
#define TPHY_MEAS_MID       (0x6)
#define TPHY_CHE_MID        (0x7)
#define TPHY_DATA_MID       (0x8)
#define TPHY_CORR_MID       (0x9)       /*未定义*/
#define TPHY_CQI_MID        (0xA)
#define TPHY_PC_MID         (0xB)
#define TPHY_SYNC_MID       (0xC)
#define TPHY_TIMING_MID     (0xD)
#define TPHY_DRX_MID        (0xE)
#define TPHY_SERV_MID       (0xF)
#define TPHY_UL_MID         (0x10)
#define TPHY_CHANCTRL_MID   (0x11)
#define TPHY_OM_MID         (0x12)
#define TPHY_DMA_MID        (0x13)
#define TPHY_CD_MID         (0x14)
#define TPHY_VIT_TURBO_MID  (0x15)
#define TPHY_SCHED_MID      (0x16)
#define TPHY_INT_MID        (0x17) 
#define TPHY_JD_MID         (0x18)
#define TPHY_DCOC_MID       (0x19)
#define TPHY_RXIQ_MID       (0x1a)
#define TPHY_CT_MID         (0x1B)
#define TPHY_BT_MID         (0x1C)
#define TPHY_NCIT_MID       (0x1D)
#define TPHY_MAX_MID        (64)


/*
    定义消息类型的宏，占3比特
*/
#define OM_TYPE_REQ         (0x0)           /*HiStudio下发的原语命令类型*/
#define OM_TYPE_CNF         (0x1)           /*收到HiStudio的原语后，立即回复的确认*/
#define OM_TYPE_DT          (0x2)           /*回复现场测试原语，对外给客户*/
#define OM_TYPE_SG          (0x3)           /*回复算法图形需求，内部观测用*/
#define OM_TYPE_TRACE       (0x4)           /*主动上报各个子模块的运行历史轨迹*/
#define OM_TYPE_DEBUG       (0x5)           /*主动上报的DEBUG信息*/
#define OM_TYPE_ERROR       (0x6)           /*主动上报的状态错误信息*/
#define OM_TYPE_IND         (0x7)           /*其它上报的类型*/

/*
    定义消息ID函数组成方法
    将子系统ID, 子模块ID, 类型，各个子模块内部的消息id合成一个消息ID
*/
#define OM_CMD_ID(mid, type, msg_id)  ((PHY_SUBSYSTEM_ID<<28)|(PHY_LPHY_SUB_ID<<24)|(PHY_L1_MSG_SUB_ID<<19)|(type<<16)|(mid<<10)|(msg_id))
#define OM_LCMD_ID(mid, type, msg_id) ((PHY_SUBSYSTEM_ID<<28)|(PHY_LPHY_SUB_ID<<24)|(PHY_L1_MSG_SUB_ID<<19)|(type<<16)|(mid<<10)|(msg_id))
#define OM_TCMD_ID(mid, type, msg_id) ((PHY_SUBSYSTEM_ID<<28)|(PHY_TPHY_SUB_ID<<24)|(PHY_L1_MSG_SUB_ID<<19)|(type<<16)|(mid<<10)|(msg_id))
#define OM_PRNT_ID(mid, type, msg_id) ((PHY_SUBSYSTEM_ID<<28)|(PHY_LPHY_SUB_ID<<24)|(PHY_L1_PRN_SUB_ID<<19)|(type<<16)|(mid<<10)|(msg_id))


#define OM_GET_SYS(om_msg_id) 	((om_msg_id >> 24) & 0x000f)
#define OM_GET_MID(om_msg_id) 	((om_msg_id >> 10) & 0x003f)
#define OM_GET_TYPE(om_msg_id) 	((om_msg_id >> 16) & 0x0007)
#define OM_GET_ID(om_msg_id)  	((om_msg_id >> 00) & 0x03ff)


#endif



/*OM定义公共使能开关*/
typedef enum __OM_REQ_ENABLE__
{
    OM_REQ_DISABLE = 0,
    OM_REQ_ENABLE = 1
}OM_REQ_ENABLE_ENUM;
typedef UINT16 OM_REQ_ENABLE_ENUM_UINT16;

/*OM定义模块*/
typedef enum __OM_REQ_TYPE__
{
	OM_REQ_TYPE_PRINT = 0,
    OM_REQ_TYPE_L1MSG = 1,
    OM_REQ_TYPE_BUTT
}OM_REQ_TYPE_ENUM;
typedef UINT16 OM_REQ_TYPE_ENUM_UINT16;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OM_BASEDEF_H__ */
