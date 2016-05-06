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

#ifndef __PCSC_PROC_H__
#define __PCSC_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"
#include "pamappom.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define USIMM_CARDSTATUS_IND                    100
#define SI_PIH_PCSC_DATA_CNF                    0xA5

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum USIMM_PHYCARD_TYPE_ENUM
{
    USIMM_PHYCARD_TYPE_ICC              = 0x00,
    USIMM_PHYCARD_TYPE_UICC             = 0x01,
    USIMM_PHYCARD_TYPE_NOCARD           = 0xFF,
    USIMM_PHYCARD_TYPE_BUTT
};

typedef VOS_UINT32 USIMM_PHYCARD_TYPE_ENUM_UINT32;

enum USIMM_CARD_TYPE_ENUM
{
    USIMM_CARD_SIM          = 0x00,
    USIMM_CARD_USIM         = 0x01,
    USIMM_CARD_ISIM         = 0x02,
    USIMM_CARD_UIM          = 0x03,
    USIMM_CARD_CSIM         = 0x04,
    USIMM_CARD_ROM_SIM      = 0xF0,
    USIMM_CARD_UNKNOWN      = 0xF1,
    USIMM_CARD_NOCARD       = 0xFF,
    USIMM_CARD_TYPE_BUTT
};
typedef VOS_UINT32 USIMM_CARD_TYPE_ENUM_UINT32;

enum USIMM_CARD_SERVIC_ENUM
{
    USIMM_CARD_SERVIC_ABSENT            = 0x00000000,
    USIMM_CARD_SERVIC_UNAVAILABLE       = 0x00000001,
    USIMM_CARD_SERVIC_SIM_PIN           = 0x00000002,
    USIMM_CARD_SERVIC_SIM_PUK           = 0x00000003,
    USIMM_CARD_SERVIC_NET_LCOK          = 0x00000004,
    USIMM_CARD_SERVICE_SUBNET_LOCK      = 0x00000005,
    USIMM_CARD_SERVICE_GID1_LOCK        = 0x00000006,
    USIMM_CARD_SERVICE_GID2_LOCK        = 0x00000007,
    USIMM_CARD_SERVICE_IMSI_LOCK        = 0x00000008,
    USIMM_CARD_SERVIC_AVAILABLE         = 0x00000009,
    USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT32      USIMM_CARD_SERVIC_ENUM_UINT32;

enum SI_PIH_EVENT_ENUM
{
    SI_PIH_EVENT_PIN_OPER_CNF       = 1,      /* 操作PIN码返回结果        */
    SI_PIH_EVENT_PIN_QUERY_CNF      = 2,      /* 查询PIN码返回结果        */
    SI_PIH_EVENT_PIN_INFO_IND       = 3,      /* 开机PIN码主动上报        */
    SI_PIH_EVENT_SIM_INFO_IND       = 4,      /* SIM卡信息上报            */
    SI_PIH_EVENT_GENERIC_ACCESS_CNF = 5,      /* +CSIM 回复               */
    SI_PIH_EVENT_RESTRIC_ACCESS_CNF = 6,      /* +CRSM 回复               */
    SI_PIH_EVENT_FDN_CNF            = 7,      /* FDN回复                  */
    SI_PIH_EVENT_BDN_CNF            = 8,      /* BDN回复                  */
    SI_PIH_EVENT_PERO_LOCK_CNF      = 9,      /* 锁卡回复                 */
    SI_PIH_EVENT_BUTT
};
typedef VOS_UINT32  SI_PIH_EVENT;

enum SI_PIH_REQ_ENUM
{
    SI_PIH_NULL_REQ                 = 0,
    SI_PIH_FDN_ENABLE_REQ           = 1,
    SI_PIH_FDN_DISALBE_REQ          = 2,
    SI_PIH_GACCESS_REQ              = 3,
    SI_PIH_BDN_QUERY_REQ            = 4,
    SI_PIH_FDN_QUERY_REQ            = 5,
    SI_PIH_PCSC_DATA_REQ            = 6,
    SI_PIH_REQ_BUTT
};
typedef VOS_UINT32      SI_PIH_REQ_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;       /* 消息名 */
    VOS_UINT16                          usClient;        /* 客户端ID */
    VOS_UINT8                           ucOpID;
    VOS_UINT8                           ucRsv;
    SI_PIH_EVENT                        ulEventType;
}SI_PIH_MSG_HEADER_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU          stMsgHeader;
    VOS_UINT32                      ulMsgType;
    VOS_UINT32                      ulCmdType;
    VOS_UINT32                      ulCmdLen;
    VOS_UINT8                       aucAPDU[8];
}SI_PIH_PCSC_REQ_STRU;

typedef struct
{
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardService;
} USIMM_CARD_STATUS_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyCardType;
    USIMM_CARD_STATUS_STRU              stUsimSimInfo;
    USIMM_CARD_STATUS_STRU              stCsimUimInfo;
    USIMM_CARD_STATUS_STRU              stIsimInfo;
}USIMM_CARDSTATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;          /* 消息类型 */
    VOS_UINT32                      ulResult;           /* PC/SC命令执行结果 */
    VOS_UINT32                      ulCmdType;          /* 命令类型 */
    VOS_UINT32                      ulRspLen;           /* 命令执行得到的数据长度 */
    VOS_UINT8                       aucContent[4];      /* 数据内容 */
}SI_PIH_PCSC_CNF_STRU;




#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

#endif
