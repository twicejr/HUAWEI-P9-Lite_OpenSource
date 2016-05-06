/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : lpc_om_def.h
  版 本 号   : 初稿
  作    者   : Hong Huiyong
  生成日期   : 2013年6月15日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.	日    期   : 2013年6月215
     	作    者   : Hong Huiyong
    	修改内容   : 创建文件
******************************************************************************/
#include "balong_lte_dsp.h"

#ifndef __LPC_OM_DEF_H__
#define __LPC_OM_DEF_H__

#define MAX_LPC_CMD_CONTEXT_LENGTH		(120)
#define HSO_RFIN_COLLECTION_STOP_CMD    (0x40001810)

typedef enum   __HSO_SMP_CMD_OPID_ENUM__
{
	LPC_SMP_START,
	LPC_SMP_QUERY,
	LPC_SMP_STOP,
	LPC_SMP_CLEAR,
	LPC_SMP_START_ONE_ROUND,
}HSO_SMP_CMD_OPID_ENUM;
typedef UINT16 HSO_SMP_CMD_OPID_ENUM_UINT16;

typedef enum   __HSO_SMP_CMD_REG_CFG_TYPE_ENUM__
{
	LPC_SMP_REG_FULL_REG_CFG,
	LPC_SMP_REG_PART_REG_CFG,
}HSO_SMP_CMD_REG_CFG_TYPE_ENUM;
typedef UINT8	HSO_SMP_CMD_REG_CFG_TYPE_ENUM_UINT8;


typedef	struct __LPHY_LPC_HSO_SMP_CMD_STRU__
{
	UINT32							ulMsgID;
	HSO_SMP_CMD_OPID_ENUM_UINT16	enOpID;
	UINT16							usPDMap;
#ifndef MS_VC6_PLATFORM
	UINT32  						aulPayload[0];
#else
	UINT32  						aulPayload[2];
#endif
}LPHY_LPC_HSO_SMP_CMD_STRU;

typedef	struct __LPHY_LPC_HSO_SMP_RPT_STRU__
{
	UINT32							ulMsgID;
	HSO_SMP_CMD_OPID_ENUM_UINT16	enOpID;
	UINT16							usValid;
#ifndef MS_VC6_PLATFORM
	UINT32							aulPayload[0];
#else
	UINT32							aulPayload[2];
#endif
}LPHY_LPC_HSO_SMP_RPT_STRU;

typedef	struct __LPHY_LPC_HSO_CFG_REG_STRU__
{
	UINT32	ulAddr;
	UINT32	ulBitMask;
	UINT32  ulValue;
}LPHY_LPC_HSO_CFG_REG_STRU;

typedef	struct __LPHY_LPC_HSO_RPT_REG_STRU__
{
	UINT32	ulAddr;
	UINT32	ulValue;
}LPHY_LPC_HSO_RPT_REG_STRU;

typedef struct
{
    UINT32 ulMsg;
}LPHY_LPC_RFIN_COLLECTION_STOP_STRU;


/*****************************************************************************
 数据结构说明  : LPHY_CSU_OM_REQ_类型定义
*****************************************************************************/
typedef enum __LPHY_OM_REQ_LPC_ID_ENUM__
{
	LPHY_LPC_OM_REQ_RESERVED 	= OM_CMD_ID(LPHY_LPC_MID, OM_TYPE_REQ, 	0x0),
	LPHY_LPC_OM_REQ_HSO_SMP,
}LPHY_OM_REQ_LPC_ID_ENUM;

typedef enum __LPHY_SG_MSGID_LPC_SG_ENUM__
{
    LPHY_SG_LPC_RESERVED        = OM_CMD_ID(LPHY_LPC_MID,OM_TYPE_SG,	0x0),
    LPHY_SG_LPC_HSO_SMP_RPT,
    LPHY_SG_LPC_DATA_RFIN_STOP,
	LPHY_SG_LPC_RPT_BUTT,
}LPHY_SG_MSGID_LPC_SG_ENUM;

#endif
