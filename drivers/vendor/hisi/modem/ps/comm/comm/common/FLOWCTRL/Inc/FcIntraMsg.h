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

#ifndef __FCINTRAMSG_H__
#define __FCINTRAMSG_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "FcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 枚举定义
*****************************************************************************/
enum FC_MSG_TYPE_ENUM
{
    ID_FC_CPU_A_OVERLOAD_IND            = 0x0001,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_CPU_A_UNDERLOAD_IND           = 0x0002,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_TEMPERATURE_OVERLOAD_IND      = 0x0003,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_TEMPERATURE_UNDERLOAD_IND     = 0x0004,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_TEMPERATURE_RECOVER_IND       = 0x0005,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_SET_FLOWCTRL_IND              = 0x0006,           /* _H2ASN_MsgChoice FC_SET_FLOWCTRL_IND_STRU */
    ID_FC_STOP_FLOWCTRL_IND             = 0x0007,           /* _H2ASN_MsgChoice FC_STOP_FLOWCTRL_IND_STRU */
    ID_FC_SET_POINT_FLOWCTRL_IND        = 0x0008,           /* _H2ASN_MsgChoice FC_SET_POINT_FLOWCTRL_IND_STRU */
    ID_FC_STOP_POINT_FLOWCTRL_IND       = 0x0009,           /* _H2ASN_MsgChoice FC_STOP_POINT_FLOWCTRL_IND_STRU */
    ID_FC_REG_POINT_IND                 = 0x000A,           /* _H2ASN_MsgChoice FC_REG_POINT_IND_STRU */
    ID_FC_DEREG_POINT_IND               = 0x000B,           /* _H2ASN_MsgChoice FC_DEREG_POINT_IND_STRU */
    ID_FC_CHANGE_POINT_IND              = 0x000C,           /* _H2ASN_MsgChoice FC_CHANGE_POINT_IND_STRU */
    ID_FC_ADD_RAB_FCID_MAP_IND          = 0x000D,           /* _H2ASN_MsgChoice FC_ADD_RAB_FCID_MAP_IND_STRU */
    ID_FC_DEL_RAB_FCID_MAP_IND          = 0x000E,           /* _H2ASN_MsgChoice FC_DEL_RAB_FCID_MAP_IND_STRU */
    ID_FC_MEM_UP_TO_TARGET_PRI_IND      = 0x000F,           /* _H2ASN_MsgChoice FC_MEM_UP_TO_TARGET_PRI_IND_STRU */
    ID_FC_MEM_DOWN_TO_TARGET_PRI_IND    = 0x0010,           /* _H2ASN_MsgChoice FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU */
    ID_FC_CPU_C_OVERLOAD_IND            = 0x0011,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_CPU_C_UNDERLOAD_IND           = 0x0012,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_C_FLOWCTRL_NOTIFY             = 0x0013,           /* _H2ASN_MsgChoice FC_FLOWCTRL_NOTIFY_STRU */
    ID_FC_ACORE_CRESET_START_IND        = 0x0014,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_IND_STRU */
    ID_FC_ACORE_CRESET_END_IND          = 0x0015,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_IND_STRU */
    ID_FC_ACORE_CRESET_START_RSP        = 0x0016,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_RSP_STRU */
    ID_FC_ACORE_CRESET_END_RSP          = 0x0017,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_RSP_STRU */

    ID_FC_MSG_TYPE_BUTT                 = 0xFFFF
};
typedef VOS_UINT16 FC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCpuLoad;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDlRate;
}FC_CPULOAD_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usTemperature;
}FC_TEMPERATURE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_RATMODE_ENUM_UINT32             enRateMode;
}FC_SET_FLOWCTRL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_RATMODE_ENUM_UINT32             enRateMode;
}FC_FLOWCTRL_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_RATMODE_ENUM_UINT32             enRateMode;
}FC_STOP_FLOWCTRL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[1];
}FC_SET_POINT_FLOWCTRL_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[1];
}FC_STOP_POINT_FLOWCTRL_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_REG_POINT_STRU                   stFcPoint;
}FC_REG_POINT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           aucRsv[7];
}FC_DEREG_POINT_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT8                    enFcId;
    FC_POLICY_ID_ENUM_UINT8             enPolicyId;
    FC_PRI_ENUM_UINT8                   enPri;
    VOS_UINT8                           aucRsv[5];
}FC_CHANGE_POINT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[6];
} FC_ADD_RAB_FCID_MAP_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[7];
} FC_DEL_RAB_FCID_MAP_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usMemFreeCnt;
    FC_PRI_ENUM_UINT8                   enTargetPri;
    VOS_UINT8                           aucRsv[7];
} FC_MEM_UP_TO_TARGET_PRI_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usMemFreeCnt;
    FC_PRI_ENUM_UINT8                   enTargetPri;
    VOS_UINT8                           aucRsv[7];
} FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU;

/*****************************************************************************
 结构名    : FC_ACORE_CRESET_IND_STRU
 协议表格  : 无
 ASN.1描述 : 无
 结构说明  : C核单独复位特性中，底软通知FcACore的指示结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
}FC_ACORE_CRESET_IND_STRU;

/*****************************************************************************
 结构名    : FC_ACORE_CRESET_RSP_STRU
 协议表格  : 无
 ASN.1描述 : 无
 结构说明  : C核单独复位特性中，FcACore完成回调事务后的通知消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulResult;
}FC_ACORE_CRESET_RSP_STRU;

/*****************************************************************************
  5 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    FC_MSG_TYPE_ENUM_UINT16             enMsgID;    /*_H2ASN_MsgChoice_Export FC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          FC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}FC_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    FC_INTRA_MSG_DATA                   stMsgData;
}FcIntraMsg_MSG;


/******************************************************************************
   6 外部函数声明
******************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* FcIntraMsg.h */


