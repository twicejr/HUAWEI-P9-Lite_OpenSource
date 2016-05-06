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

#ifndef __TTFOAMINTERFACE_H__
#define __TTFOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TTFLink.h"
#include "PsTypeDef.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define GRM_MNTN_TS_TOTAL                           (8)    /* 时隙个数，ts0-ts7共8个 */
#define GRLC_MNTN_MAX_TBF_NUM                       (1)    /* 当前支持的最大TBF规格为1，不支持多TBF */
#define  WTTF_MNTN_MAX_AM_RB_NUM                    (8)    /* 3个AM业务RB,外加RB2-RB4 三个信令RB,共计6个AM RB. 25.306 R9协议Table 5.1b升级到8个AM RB */
#define  WTTF_MNTN_MAX_TM_RB_NUM                    (4)    /* TM RB个数,RB0不计人, 3个AMR语音RB + 1个TM CSD共计4个TM RB, */
#define  WTTF_MNTN_MAX_UM_RB_NUM                    (6)    /* UM RB个数, CBS所对应的RB和RB0不计入,GCF用例要求三个以上UM业务RB,RB1为UM信令RB,共计3个UM RB ，与AM实体个数对应*/

#define  WTTF_MNTN_MAX_RB_ID                        (32)    /* INTEGER (1..32) */
#define  WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT       (10) /*最大可用变长SIZE档位数*/
#define  WTTF_MNTN_RLC_AM_MAX_SN_NUM                (4096)

#define RRM_MODEM_MAX_TASK_TYPE_NUMBER        (10)

/* 典型的RLP实体的个数 */
#define CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM   (2)

/* MFPA RLP实体的最大个数 */
#define CTTF_HRPD_MNTN_MF_RLP_MAX_NUM        (6)

/* EMPA RLP实体的最大个数 */
#define CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM       (6)

/* 根据CDMA 5.12s周期, 建议每1.28s上报一次。1.28s=64*20ms, 64作为数组下标,
（一次上报64帧的情况）, 内存可以接受 */
#define   CTTF_1X_MAC_MNTN_MAX_REPORT_NUM    (64)

/* 因为HIDS不支持动态添加、删除RLP实体, 所以讨论后决定按照协议最大值定义 */
#define    CTTF_1X_RLP_MNTN_MAX_NUM    (6)

/* 上报的MAC流最大个数，参考标杆设计 */
#define   CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM   (8)

/*
    按照协议16slot为一个MAC Layer Packet, 每一个子帧记录一次。一个子帧为4个slot,
    则16个slot会产生16/4=4组数据一个slot为1.28ms，那么16个slot对应26.66ms。
    因为640ms上报一次消息，那么消息中一个MAC流会产生有24组数据（640=48*26.66ms）。
    一组数据记录4个子帧的信息，即1.28s中每个流上报24*4= 96组。
*/
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW     (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW        (96)
#define   CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ                (96)


/**
 * It's define the num of  subframe information instances
 */
#define CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES              (3)


/* 勾包PID范围 */
#define IS_WUEPS_PID_RABM(x)            ((I0_WUEPS_PID_RABM == x) || (I1_WUEPS_PID_RABM == x) || (I2_WUEPS_PID_RABM == x))
#define IS_WUEPS_PID_PDCP(x)            (WUEPS_PID_PDCP == x)
#define IS_WUEPS_PID_RLC(x)             (WUEPS_PID_RLC == x)
#define IS_WUEPS_PID_MAC(x)             (WUEPS_PID_MAC == x)
#define IS_WUEPS_PID_WAS(x)             ((WUEPS_PID_WRR == x) || (WUEPS_PID_WCOM == x))
#define IS_UEPS_PID_SN(x)               ((I0_UEPS_PID_SN == x) || (I1_UEPS_PID_SN == x) || (I2_UEPS_PID_SN == x))
#define IS_UEPS_PID_LL(x)               ((I0_UEPS_PID_LL == x) || (I1_UEPS_PID_LL == x) || (I2_UEPS_PID_LL == x))
#define IS_UEPS_PID_GRM(x)              ((I0_UEPS_PID_GRM == x) || (I1_UEPS_PID_GRM == x) || (I2_UEPS_PID_GRM == x))
#define IS_UEPS_PID_DL(x)               ((I0_UEPS_PID_DL == x) || (I1_UEPS_PID_DL == x) || (I2_UEPS_PID_DL == x))
#define IS_UEPS_PID_MM(x)               ((I0_WUEPS_PID_MM == x) || (I1_WUEPS_PID_MM == x) || (I2_WUEPS_PID_MM == x))
#define IS_UEPS_PID_SMS(x)              ((I0_WUEPS_PID_SMS == x) || (I1_WUEPS_PID_SMS == x) || (I2_WUEPS_PID_SMS == x))
#define IS_UEPS_PID_GAS(x)              ((I0_UEPS_PID_GAS == x) || (I1_UEPS_PID_GAS == x) || (I2_UEPS_PID_GAS == x))
#define IS_UEPS_PID_GPHY(x)             ((I0_DSP_PID_GPHY == x) || (I1_DSP_PID_GPHY == x) || (I2_DSP_PID_GPHY == x))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TTF_MNTN_MSG_TYPE_ENUM
 枚举说明  : 可维可测消息类型(透明消息), 把所有的透明消息的ID都定义在这里
*****************************************************************************/
enum TTF_MNTN_MSG_TYPE_ENUM
{
/*****************************************************************************
    TTF的透明消息目前都不区分MODEM
*****************************************************************************/

    /* W模可维可测消息的编号以DO开头 */
    ID_OM_WTTF_RLC_DATA_TRANS_INFO_REQ          = 0xD001,    /*W模下RLC 实体信息上报请求,其中共包括AM，UM，TM三种模式，根据用户的请求全部或部分显示*/
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_CNF          = 0xD002,    /*W模下RLC 实体信息上报回复*/
    ID_WTTF_OM_RLC_DATA_TRANS_INFO_IND          = 0xD003,    /*W模下RLC 实体信息上报指示*/
    ID_OM_WTTF_ADVANCED_TRACE_CONFIG_REQ        = 0xD004,    /*W模下Trace 高级配置*/
    ID_WTTF_OM_ADVANCED_TRACE_CONFIG_CNF        = 0xD005,    /*W模下Trace 高级配置指示*/
    ID_OM_WTTF_RLC_PDU_SIZE_TRANS_INFO_REQ      = 0xD006,    /*W模下RLC PDU SIZE统计信息上报请求*/
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF      = 0xD007,    /*W模下RLC PDU SIZE统计信息上报回复*/
    ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_IND      = 0xD008,    /*W模下RLC PDU SIZE统计信息上报指示*/
    ID_OM_WTTF_UPA_DATA_STATUS_G_INFO_REQ       = 0xD009,    /*W模下UPA 要数信息G值上报请求*/
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_CNF       = 0xD00a,    /*W模下UPA 要数信息G值上报回复*/
    ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_IND       = 0xD00b,    /*W模下UPA 要数信息G值上报指示*/
    ID_OM_TTF_MNTN_MSG_CTTF_OM_XXX_REQ          = 0xD00c,
    ID_OM_TTF_MNTN_MSG_CTTF_OM_YYY_REQ          = 0xD00d,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_XXX_DATA_IND     = 0xD00e,
    ID_TTF_OM_MNTN_MSG_OM_CTTF_ZZZ_DATA_IND     = 0xD00f,

    /* G模可维可测消息的编号以D1开头 */
    ID_GRM_MNTN_OM_GRM_INFO_CFG_REQ             = 0xD104,   /*配置GRM信息观测功能*/
    ID_GRM_MNTN_GRM_OM_INFO_CFG_CNF             = 0xD105,
    ID_GRM_MNTN_GRM_OM_INFO                     = 0xD106,
    ID_GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ       = 0xD107,   /*OM向GRM请求配置GRM吞吐率统计信息观测功能消息项*/
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF       = 0xD108,   /*GRM向OM回复配置GRM吞吐率统计信息观测功能消息项*/
    ID_GRM_MNTN_GRM_OM_THROUGHPUT_INFO          = 0xD109,   /*GRM向OM上报GRM吞吐率统计信息消息项*/
    ID_GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ    = 0xD10a,   /*G模下Trace 高级配置开关请求*/
    ID_GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF    = 0xD10b,   /*G模下Trace 高级配置开关回复*/

    /* RRM的可维可测消息的编号以D2开头 */
    ID_RRM_OM_RESOURCE_STATE_INFO_IND           = 0xD210,    /* RRM上报的资源状态信息 */

    /* AP上的TCP协议栈的可维可测消息, 编号以D3开头 */
    ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ         = 0xD313,   /* 捕获TCP/IP协议栈 报文配置*/
    ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF         = 0xD314,   /* 捕获TCP/IP协议栈 报文指示*/
    ID_OM_IPS_MNTN_INFO_CONFIG_REQ              = 0xD315,   /* 周期性捕获TCP/IP协议栈 基础信息配置*/
    ID_IPS_OM_MNTN_INFO_CONFIG_CNF              = 0xD316,   /* 周期性捕获TCP/IP协议栈 基础信息配置指示*/
    ID_IPS_TRACE_INPUT_DATA_INFO                = 0xD317,               /*TCP/IP可维可测接收报文*/
    ID_IPS_TRACE_OUTPUT_DATA_INFO               = 0xD318,               /*TCP/IP可维可测发送报文*/
    ID_IPS_TRACE_BRIDGE_DATA_INFO               = 0xD319,               /*TCP/IP网桥中转报文*/
    ID_IPS_TRACE_RECV_ARP_PKT                   = 0xD31A,               /*TCP/IP协议栈接收的ARP控制报文*/
    ID_IPS_TRACE_SEND_ARP_PKT                   = 0xD31B,               /*TCP/IP协议栈发送的ARP控制报文*/
    ID_IPS_TRACE_RECV_DHCPC_PKT                 = 0xD31C,               /*TCP/IP协议栈接收的DHCP控制报文*/
    ID_IPS_TRACE_SEND_DHCPC_PKT                 = 0xD31D,               /*TCP/IP协议栈发送的DHCP控制报文*/
    ID_IPS_TRACE_RECV_DHCPS_PKT                 = 0xD31E,               /*TCP/IP协议栈接收的DHCP控制报文*/
    ID_IPS_TRACE_SEND_DHCPS_PKT                 = 0xD31F,               /*TCP/IP协议栈发送的DHCP控制报文*/
    ID_IPS_TRACE_APP_CMD                        = 0xD320,               /*APP控制命令信息*/
    ID_IPS_TRACE_MNTN_INFO                      = 0xD321,               /*TCP/IP协议栈基础信息*/
    ID_IPS_TRACE_BRIDGE_PRE_ROUTING_INFO        = 0xD322,
    ID_IPS_TRACE_BRIDGE_POST_ROUTING_INFO       = 0xD323,
    ID_IPS_TRACE_BRIDGE_LOCAL_IN_INFO           = 0xD324,
    ID_IPS_TRACE_BRIDGE_LOCAL_OUT_INFO          = 0xD325,
    ID_IPS_TRACE_IP4_FORWARD_INFO               = 0xD326,
    ID_IPS_TRACE_IP4_LOCAL_IN_INFO              = 0xD327,
    ID_IPS_TRACE_IP4_LOCAL_OUT_INFO             = 0xD328,
    ID_IPS_TRACE_IP6_FORWARD_INFO               = 0xD329,
    ID_IPS_TRACE_IP6_LOCAL_IN_INFO              = 0xD32A,
    ID_IPS_TRACE_IP6_LOCAL_OUT_INFO             = 0xD32B,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START     = 0xD32C,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP      = 0xD32D,
    ID_IPS_TRACE_ADS_UL                         = 0xD330,
    ID_IPS_TRACE_ADS_DL                         = 0xD331,

    /* 1X的可维可测消息的编号以D4开头 */
    ID_OM_CTTF_1X_MNTN_CONFIG_REQ               = 0xD400,   /* 1X 配置开关请求, 用于下发配置 */
    ID_CTTF_OM_1X_MNTN_CONFIG_CNF               = 0xD400,   /* 1X 配置开关回复, 用于回复配置结果 */
    ID_CTTF_OM_1X_MNTN_FWD_LINK_IND             = 0xD402,   /* 1X Forward Link Info上报 */
    ID_CTTF_OM_1X_MNTN_REV_LINK_IND             = 0xD403,   /* 1X Reverse Link Info上报 */
    ID_CTTF_OM_1X_MNTN_RLP_STATISTICS_IND       = 0xD404,   /* 1X RLP statistics上报 */
    ID_CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND       = 0xD405,   /* Common Channel statistics上报 */

    /* CP上关于IP报文、PPP帧之类的维测都归入D5中 */
    /* CP上的TCP协议栈的可维可测消息, 编号以D51开头
       考虑IP类的需求可能比较多, 多预留一些ID空间, D51~D55 */
    ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ   = 0xD513,               /* 捕获TCP/IP协议栈 报文配置 */
    ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF   = 0xD514,               /* 捕获TCP/IP协议栈 报文指示 */
    ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ        = 0xD515,               /* 周期性捕获TCP/IP协议栈 基础信息配置 */
    ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF        = 0xD516,               /* 周期性捕获TCP/IP协议栈 基础信息配置指示 */
    ID_IPS_CCORE_TRACE_INPUT_DATA_INFO          = 0xD517,               /* TCP/IP可维可测接收报文 */
    ID_IPS_CCORE_TRACE_OUTPUT_DATA_INFO         = 0xD518,               /* TCP/IP可维可测发送报文 */
    ID_IPS_CCORE_TRACE_BRIDGE_DATA_INFO         = 0xD519,               /* TCP/IP网桥中转报文 */
    ID_IPS_CCORE_TRACE_RECV_ARP_PKT             = 0xD51A,               /* TCP/IP协议栈接收的ARP控制报文 */
    ID_IPS_CCORE_TRACE_SEND_ARP_PKT             = 0xD51B,               /* TCP/IP协议栈发送的ARP控制报文 */
    ID_IPS_CCORE_TRACE_RECV_DHCPC_PKT           = 0xD51C,               /* TCP/IP协议栈接收的DHCP控制报文 */
    ID_IPS_CCORE_TRACE_SEND_DHCPC_PKT           = 0xD51D,               /* TCP/IP协议栈发送的DHCP控制报文 */
    ID_IPS_CCORE_TRACE_RECV_DHCPS_PKT           = 0xD51E,               /* TCP/IP协议栈接收的DHCP控制报文 */
    ID_IPS_CCORE_TRACE_SEND_DHCPS_PKT           = 0xD51F,               /* TCP/IP协议栈发送的DHCP控制报文 */
    ID_IPS_CCORE_TRACE_APP_CMD                  = 0xD520,               /* APP控制命令信息 */
    ID_IPS_CCORE_TRACE_MNTN_INFO                = 0xD521,               /* TCP/IP协议栈基础信息 */
    ID_IPS_MNTN_CCORE_IMS_NIC_INFO              = 0xD522,               /* IMS虚拟网卡统计信息 */
    ID_IPS_CCORE_TRACE_NIC_DATA_IND             = 0xD523,               /* TCP/IP可维可测接收报文 */
    ID_IPS_CCORE_TRACE_NIC_DATA_REQ             = 0xD524,               /* TCP/IP可维可测发送报文 */


    /* CP上的PPPC的可维可测消息, 编号以D56开头 */
    ID_OM_PPP_MNTN_CONFIG_REQ                   = 0xD560,               /*PPP收到om配置信息*/
    ID_PPP_OM_MNTN_CONFIG_CNF                   = 0xD561,               /*PPP确认收到om配置信息*/
    ID_PPP_OM_MNTN_STATISTIC_INFO               = 0xD562,               /*PPP返回维测信息*/


    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_INFO       = 0xD5F1,
    ID_IMS_NIC_MNTN_TRACE_CONFIG_PROC_RSLT      = 0xD5F2,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL        = 0xD5F3,
    ID_IMS_NIC_MNTN_TRACE_RCV_CONFIG_DEL_RSLT   = 0xD5F4,
    ID_IMS_NIC_MNTN_TRACE_RUN_CMD               = 0xD5F5,
    ID_IMS_NIC_MNTN_TRACE_DNS_CFG               = 0xD5F6,
    ID_IMS_NIC_MNTN_TRACE_DNS_DEL               = 0xD5F7,
    ID_IMS_NIC_MNTN_TRACE_LOG_MSG               = 0xD5F8,
    ID_IMS_NIC_MNTN_TRACE_TCPIP_INPUT_LOG       = 0xD5F9,


    /* EVDO的可维可测消息(含HRPD和eHRPD)的编号以D6开头 */
    ID_OM_CTTF_HRPD_MNTN_CONFIG_REQ                     = 0xD600,   /* HRPD 配置开关请求, 用于下发配置 */
    ID_CTTF_OM_HRPD_MNTN_CONFIG_CNF                     = 0xD601,   /* HRPD 配置开关回复, 用于回复配置结果 */
    ID_CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_IND      = 0xD602,   /* HRPD Module Protocol State上报 */
    ID_CTTF_OM_HRPD_MNTN_MAC_PROTOCOL_STATISTICS_IND    = 0xD603,   /* HRPD MAC Protocol Statistics上报 */
    ID_CTTF_OM_HRPD_MNTN_RLP_STATISTICS_IND             = 0xD604,   /* HRPD RLP statistics上报 */
    ID_CTTF_OM_HRPD_MNTN_MFPA_RLP_STATISTICS_IND        = 0xD605,   /* MFPA RLP statistics上报 */
    ID_CTTF_OM_HRPD_MNTN_EMPA_RLP_STATISTICS_IND        = 0xD606,   /* EMPA RLP statistics上报 */
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_PACKET_INFO_IND       = 0xD607,   /* HRPD Reverse Link Packet Info上报 */
    ID_CTTF_OM_HRPD_MNTN_REV_LINK_T2P_STATISTICS_IND    = 0xD608,   /* HRPD Reverse Link T2P statistics上报 */
    ID_CTTF_OM_HRPD_MNTN_HARQ_INFO_IND                  = 0xD609,   /* HRPD Harq Info上报 */

    TTF_MNTN_MSG_TYPE_BUTT                      = 0xFFFF
};
typedef VOS_UINT16 TTF_MNTN_MSG_TYPE_ENUM_UINT16;

enum TTF_MNTN_RPT_CMD_ENUM
{
    TTF_MNTN_RPT_CMD_STOP     = 0x00, /*停止上报*/
    TTF_MNTN_RPT_CMD_START    = 0x01  /*开始上报*/
};
typedef VOS_UINT8 TTF_MNTN_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_RLP_RPT_CMD_ENUM
{
    TTF_MNTN_RLP_RPT_CMD_STOP   = 0x00, /*停止上报*/
    TTF_MNTN_RLP_RPT_CMD_START  = 0x01, /*开始上报*/
    TTF_MNTN_RLP_RPT_CMD_CLEAR  = 0x02  /*清除*/
};
typedef VOS_UINT8 TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8;

enum TTF_MNTN_COMM_RPT_CMD_ENUM
{
    TTF_MNTN_COMM_RPT_CMD_STOP  = 0x00, /*停止上报*/
    TTF_MNTN_COMM_RPT_CMD_START = 0x01, /*开始上报*/
    TTF_MNTN_COMM_RPT_CMD_CLEAR = 0x02  /*清除*/
};
typedef VOS_UINT8 TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8;

enum IPS_MNTN_INFO_ACTION_ENUM
{
    IPS_MNTN_INFO_REPORT_STOP           = 0,                    /*开启周期性捕获TCP/IP协议栈基础信息*/
    IPS_MNTN_INFO_REPORT_START          = 1                     /*关闭周期性捕获TCP/IP协议栈基础信息*/
};
typedef VOS_UINT16 IPS_MNTN_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_RESULT_TYPE_ENUM
{
    IPS_MNTN_RESULT_OK                  = 0,
    IPS_MNTN_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_RESULT_TYPE_ENUM_UINT32;

enum GRM_MNTN_OM_REPORT_ACTION_ENUM
{
    GRM_MNTN_OM_REPORT_STOP     = 0,
    GRM_MNTN_OM_REPORT_START    = 1
};

typedef VOS_UINT16 GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16;

enum GRM_RESULT_TYPE_ENUM
{
    GRM_RESULT_OK                   = 0,
    GRM_RESULT_START_TIMER_FAIL     = 1,
    GRM_RESULT_ALLOC_MEM_FAIL       = 2,
    GRM_RESULT_ALLOC_MSG_FAIL       = 3,
    GRM_RESULT_INPUT_PARAM_ERR      = 4,
    GRM_RESULT_LOCAL_PARAM_ERR      = 5
};
typedef VOS_UINT32  GRM_RESULT_TYPE_ENUM_UINT32;

enum TOOL_GTTF_CFG_SWITCH_ENUM
{
    TOOL_GTTF_CFG_SWITCH_OFF = 0,
    TOOL_GTTF_CFG_SWITCH_ON  = 1
};
typedef VOS_UINT32 TOOL_GTTF_CFG_SWITCH_ENUM_UINT32;

enum GRM_TBF_INFO_TBF_MODE_ENUM
{
    Non_Extend_TBF = 0,
    Extend_TBF    = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TBF_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_RLC_MODE_ENUM
{
    AM    = 0,  /* RLC AM mode*/
    UM    = 1   /* RLC UM mode*/
};
typedef VOS_UINT8 GRM_TBF_INFO_RLC_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM
{
    No_Start_CV    = 0,
    Start_CV       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8;

enum GRM_TBF_INFO_TI_ENUM
{
    TLLI_Absent           = 0,
    TLLI_Not_Absent       = 1
};
typedef VOS_UINT8 GRM_TBF_INFO_TI_ENUM_UINT8;

enum GRM_TBF_INFO_FINALBLKRXED_ENUM
{
    Not_received    = 0,  /* The Final Block the current TBF is not received. */
    Received        = 1   /* The Final Block the current TBF is received. */
};
typedef VOS_UINT8 GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8;

enum GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM
{
    CS_1       = 0x0000,
    CS_2       = 0x0001,
    CS_3       = 0x0002,
    CS_4       = 0x0003,
    MCS_1      = 0x1000,
    MCS_2      = 0x1001,
    MCS_3      = 0x1002,
    MCS_4      = 0x1003,
    MCS_5      = 0x1004,
    MCS_6      = 0x1005,
    MCS_7      = 0x1006,
    MCS_8      = 0x1007,
    MCS_9      = 0x1008,
    MCS_5_7    = 0x1009,
    MCS_6_9    = 0x100a
};
typedef VOS_UINT16 GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16;

enum GRM_TBF_INFO_TEST_MODE_ENUM
{
    Test_Mode_A_Infinite      = 0, /*A模式，PDU个数无限*/
    Test_Mode_A_Normal        = 1, /*A模式，PDU个数有限*/
    Test_Mode_B               = 2, /*B模式*/
    Test_Mode_SRB_LoopBack    = 3  /*EGPRS 小环回模式*/
};
typedef VOS_UINT8 GRM_TBF_INFO_TEST_MODE_ENUM_UINT8;

enum GRM_TBF_INFO_TIMESLOT_FLAG_ENUM
{
    Not_Existed           = 0,  /* This TS is not existed */
    Existed               = 1   /* This TS is existed */
};
typedef VOS_UINT8 GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8;

enum IPS_MNTN_CCORE_INFO_ACTION_ENUM
{
    IPS_MNTN_CCORE_INFO_REPORT_STOP           = 0,                    /*开启周期性捕获TCP/IP协议栈基础信息*/
    IPS_MNTN_CCORE_INFO_REPORT_START          = 1                     /*关闭周期性捕获TCP/IP协议栈基础信息*/
};
typedef VOS_UINT16 IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_CCORE_RESULT_TYPE_ENUM
{
    IPS_MNTN_CCORE_RESULT_OK                  = 0,
    IPS_MNTN_CCORE_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_CCORE_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_CCORE_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_CCORE_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_CCORE_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32  IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32;

enum WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM     /*用于标识PHY-->MAC   ID_WTTF_PHY_MAC_DATA_IND
                                                  MAC-->PHY  ID_WTTF_MAC_PHY_DATA_REQ*/
{
    WTTF_TRACE_PHY_MAC_NULL = 0,
    WTTF_TRACE_CTRL_HEADER  = 1,
    WTTF_TRACE_WHOLE_DATA   = 2
};
typedef VOS_UINT8   WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8;

enum WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM
{
    WTTF_TRACE_MSG_NO   = 0,
    WTTF_TRACE_MSG_YES  = 1
};
typedef VOS_UINT8   WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8;

enum IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_CCORE_TRACE_NULL_CHOSEN               =   0,             /*不捕获报文信息*/
    IPS_MNTN_CCORE_TRACE_MSG_HEADER_CHOSEN         =   1,             /*捕获报文头部*/
    IPS_MNTN_CCORE_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*按照配置捕获报文*/
    IPS_MNTN_CCORE_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*捕获报文全部内容*/
};
typedef VOS_UINT32   IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32;

enum IPS_MNTN_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_TRACE_NULL_CHOSEN               =   0,             /*不捕获报文信息*/
    IPS_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,             /*捕获报文头部*/
    IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*按照配置捕获报文*/
    IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*捕获报文全部内容*/
};
typedef VOS_UINT32   IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum TTF_MNTN_TRACE_CHOSEN_ENUM
{
    TTF_MNTN_TRACE_NULL_CHOSEN               =   0,             /*不捕获报文信息*/
    TTF_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,             /*捕获报文头部*/
    TTF_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*按照配置捕获报文*/
    TTF_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3              /*捕获报文全部内容*/
};
typedef VOS_UINT32   TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32;

enum WTTF_RLC_MNTN_RB_CHOSEN_ENUM
{
    WTTF_RLC_MNTN_RB_NULL_CHOSEN                = 0x0,                  /* 取消跟踪 */
    WTTF_RLC_MNTN_RB_SIGNALLING_CHOSEN          = 0x0000000F,           /* 信令RB */
    WTTF_RLC_MNTN_RB_PS_CHOSEN                  = 0xFFFFFFF0,           /* 业务RB */
    WTTF_RLC_MNTN_RB_ALL_CHOSEN                 = 0xFFFFFFFF            /* ALL RB */
};
typedef VOS_UINT32   WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32;

/* HIDS工具, 要求每个枚举值都必须显示定义其值, 否则不能解析 */
enum CTTF_1X_MAC_MNTN_RATE_ENUM
{
    CTTF_1X_MAC_MNTN_RATE_BLANK    = 0,
    CTTF_1X_MAC_MNTN_RATE_EIGHTH    = 1,
    CTTF_1X_MAC_MNTN_RATE_QUARTER  = 2,
    CTTF_1X_MAC_MNTN_RATE_HALF      = 3,
    CTTF_1X_MAC_MNTN_RATE_FULL      = 4,
    CTTF_1X_MAC_MNTN_RATE_2X        = 5,
    CTTF_1X_MAC_MNTN_RATE_4X        = 6,
    CTTF_1X_MAC_MNTN_RATE_8X        = 7,
    CTTF_1X_MAC_MNTN_RATE_16X       = 8,
    CTTF_1X_MAC_MNTN_RATE_32X       = 9,
    CTTF_1X_MAC_MNTN_RATE_BUTT     = 10
};
typedef VOS_UINT8 CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8;

enum CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM
{
    CTTF_1X_MAC_MNTN_RESULT_OK                  = 0,
    CTTF_1X_MAC_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_1X_MAC_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_1X_MAC_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_1X_MAC_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RESULT_TYPE_ENUM_UINT32;

enum CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM
{
    CTTF_1X_MAC_MNTN_RPT_PERIOD_1280          = 1280,                    /* 上报周期1280ms */
};
typedef VOS_UINT32 CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd上报结果
*******************************************************************************/
enum CTTF_HRPD_MNTN_RESULT_TYPE_ENUM
{
    CTTF_HRPD_MNTN_RESULT_OK                  = 0,
    CTTF_HRPD_MNTN_RESULT_START_TIMER_FAIL    = 1,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    CTTF_HRPD_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    CTTF_HRPD_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    CTTF_HRPD_MNTN_RESULT_LOCAL_PARAM_ERR     = 5
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RESULT_TYPE_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd上报周期
*******************************************************************************/
enum CTTF_HRPD_MNTN_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RPT_PERIOD_1280              = 1280                          /* 上报周期1280ms */
};

typedef VOS_UINT32 CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32
 * Description : hrpd RTC 画图上报周期
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM
{
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_640           = 640                           /* 上报周期640ms */
};
typedef VOS_UINT32 CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32;


/*定义VISP日志的输出等级*/
enum IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM
{
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_CRITICAL = 0,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_ERROR,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_WARNING,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_INFO,
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_DEBUG,

    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_BUIT
};
typedef VOS_UINT8 IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM
 * Description : HRPD子协议类型
*******************************************************************************/
enum CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM
{
    CTTF_HRPD_MNTN_DEFAULT_CC_MAC_ENUM                      = 0x00,
    CTTF_HRPD_MNTN_ENHANCE_CC_MAC_ENUM                      = 0x01,
    CTTF_HRPD_MNTN_DEFAULT_AC_MAC_ENUM                      = 0x02,
    CTTF_HRPD_MNTN_ENHANCE_AC_MAC_ENUM                      = 0x03,
    CTTF_HRPD_MNTN_DEFAULT_FTC_MAC_ENUM                     = 0x04,
    CTTF_HRPD_MNTN_ENHANCE_FTC_MAC_ENUM                     = 0x05,
    CTTF_HRPD_MNTN_DEFAULT_RTC_MAC_ENUM                     = 0x06,
    CTTF_HRPD_MNTN_SUBTYPE3_RTC_MAC_ENUM                    = 0x07,
    CTTF_HRPD_MNTN_DEFAULT_AUTHENTICATION_ENUM              = 0x08,
    CTTF_HRPD_MNTN_SHA1_AUTHENTICATION_ENUM                 = 0x09,
    CTTF_HRPD_MNTN_DEFAULT_ENCRYPTION_ENUM                  = 0x0a,
    CTTF_HRPD_MNTN_AES_ENCRYPTION_ENUM                      = 0x0b,
    CTTF_HRPD_MNTN_DEFAULT_SECURITY_ENUM                    = 0x0c,
    CTTF_HRPD_MNTN_GENERIC_SECURITY_ENUM                    = 0x0d,
    CTTF_HRPD_MNTN_DEFAULT_STREAM_ENUM                      = 0x0e,
    CTTF_HRPD_MNTN_DEFAULT_SIGNALING_APP_ENUM               = 0x0f,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_RN_ENUM               = 0x10,
    CTTF_HRPD_MNTN_DEFAULT_PACKET_APP_SN_ENUM               = 0x11,
    CTTF_HRPD_MNTN_TEST_APP_ENUM                            = 0x12,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_RN_ENUM            = 0x13,
    CTTF_HRPD_MNTN_MULTI_FLOW_PACKET_APP_SN_ENUM            = 0x14,
    CTTF_HRPD_MNTN_3G1X_CIRCUIT_SERVICE_NOTIFICATION_APP_ENUM   = 0x15,
    CTTF_HRPD_MNTN_RESERVED_APP_ENUM                        = 0x16,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_RN_ENUM   = 0x17,
    CTTF_HRPD_MNTN_ENHANCED_MULTI_FLOW_PACKET_APP_SN_ENUM   = 0x18,
    CTTF_HRPD_MNTN_ENHANCED_TEST_APP_ENUM                   = 0x19,
    CTTF_HRPD_MNTN_STREAM_NOT_USED_ENUM                     = 0x1a,
    CTTF_HRPD_MNTN_NO_SUB_PROTOCOL_ENUM                     = 0x1b,
    CTTF_HRPD_MNTN_SUB_PROTOCOL_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8
 * Description : 传输模式
*******************************************************************************/
enum CTTF_HRPD_MAC_TRANS_MODE_ENUM
{
    CTTF_HRPD_MAC_TRANS_MODE_HIGH_CAPACITY  = 0x00,
    CTTF_HRPD_MAC_TRANS_MODE_LOW_LATENCY    = 0x01,
    CTTF_HRPD_MAC_TRANS_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8
 * Description : T2P工作模式
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_MODE_NORMAL                  = 0x00, /* 通常模式 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PHY_FORBIDDEN           = 0x01, /* PHY禁止发送 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SUPERVISION_FAILED      = 0x02, /* supervision failed之后，与网络失去联系 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_SILENCE_DURATION        = 0x03, /* 静默 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TEST_LOOP               = 0x04, /* 测试模式 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_PREEMPT                 = 0x05, /* 被抢占 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_RTC_SETUP_STATUS        = 0x06, /* RTC3处于setup状态 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_NEGO   = 0x07, /* 重协商改变协商参数 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_ATTR_PARA_CHANGE_GAUP   = 0x08, /* GAUP改变协商参数 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_TCH_PARA_CHANGE         = 0x09, /* TCH参数改变 */
    CTTF_HRPD_MNTN_RTC3MAC_MODE_OTHER                   = 0x0A, /* 其它 */
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_BUTT               = 0x0B
};
typedef VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_CC_STATE_ENUM
 * Description : DCC和ECC的状态,按照工具的要求, DCC和ECC的状态要定义在一起
*******************************************************************************/
enum CTTF_HRPD_MNTN_CC_STATE_ENUM
{
    CTTF_HRPD_MNTN_CC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_CC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_CC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_CC_STATE_ENUM
 * Description : SDAC和EAC的状态,按照工具的要求, DAC和EAC的状态要定义在一起
*******************************************************************************/
enum CTTF_HRPD_MNTN_AC_STATE_ENUM
{
    CTTF_HRPD_MNTN_AC_INACTIVE_STATE    = 0x0,
    CTTF_HRPD_MNTN_AC_ACTIVE_STATE      = 0x1,
    CTTF_HRPD_MNTN_AC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_FTC_STATE_ENUM
 * Description : DFTC和EFTC的状态,按照工具的要求, DFTC和EFTC的状态要定义在一起
*******************************************************************************/
enum CTTF_HRPD_MNTN_FTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_FTC_INACTIVE_STATE       = 0x0,
    CTTF_HRPD_MNTN_FTC_VARIABLE_RATE_STATE  = 0x1,
    CTTF_HRPD_MNTN_FTC_FIXED_RATE_STATE     = 0x2,
    CTTF_HRPD_MNTN_FTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_RTC_STATE_ENUM
 * Description : DRTC和ST3 RTC的状态,按照工具的要求, DRTC和ST3 RTC的状态要定义在一起
*******************************************************************************/
enum CTTF_HRPD_MNTN_RTC_STATE_ENUM
{
    CTTF_HRPD_MNTN_RTC_INACTIVE_STATE   = 0x0,
    CTTF_HRPD_MNTN_RTC_SETUP_STATE      = 0x1,
    CTTF_HRPD_MNTN_RTC_OPEN_STATE       = 0x2,
    CTTF_HRPD_MNTN_RTC_SUSPENDED_STATE  = 0x3,
    CTTF_HRPD_MNTN_RTC_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM
 * Description : 安全层协议状态
*******************************************************************************/
enum CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_NO_STATE     = 0x0,
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM
 * Description : 流控层协议状态
*******************************************************************************/
enum CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_CLOSE_STATE         = 0x0,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_OPEN_STATE          = 0x1,
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM
 * Description : 流应用层协议状态
                 工具要求Default Packet Application, Multi-flow Packet Application,
                 Enhanced Multi-flow Packet Application, Data Over Signalling,
                 Test Application, 以及Enhanced Test Application定义在一起
*******************************************************************************/
enum CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM
{
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_CLOSE_STATE   = 0x0,
    CTTF_HRPD_MNTN_STREAM_APP_RESERVATION_STATE         = 0x1,
    CTTF_HRPD_MNTN_STREAM_APP_NO_STATE                  = 0x2,
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM
 * Description : SNP协议状态
*******************************************************************************/
enum CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM
{
    CTTF_HRPD_MNTN_SNP_UP_TX_ALLOW_STATE                = 0x0,
    CTTF_HRPD_MNTN_SNP_UP_TX_NOT_ALLOW_STATE            = 0x1,
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_BUTT
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8
 * Description : Default RTC 速率限制枚举
*******************************************************************************/
enum CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM
{
    CTTF_HRPD_RTCMAC_MNTN_RATE_NULL              = 0,
    CTTF_HRPD_RTCMAC_MNTN_RATE_9K6               = 1,
    CTTF_HRPD_RTCMAC_MNTN_RATE_19K2              = 2,
    CTTF_HRPD_RTCMAC_MNTN_RATE_38K4              = 3,
    CTTF_HRPD_RTCMAC_MNTN_RATE_76K8              = 4,
    CTTF_HRPD_RTCMAC_MNTN_RATE_153K6             = 5,
    CTTF_HRPD_RTCMAC_MNTN_RATE_NO_LIMITATION     = 6,   /* 表示对Rate无限制 */
    CTTF_HRPD_RTCMAC_MNTN_RATE_BUTT              = 7    /* 表示无效 */
};
typedef VOS_UINT8 CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8;

/*****************************************************************************
 结构名     :  PPP_MNTN_OM_RESULT_TYPE_ENUM_UINT8
 说明:     ppp维测信息通知结果
*****************************************************************************/
enum PPP_MNTN_OM_RESULT_TYPE_ENUM
{
    PPP_MNTN_OM_RESULT_OK                  = 0,
    PPP_MNTN_OM_RESULT_INPUT_PARAM_ERR     = 1,
    PPP_MNTN_OM_RESULT_BUTT
};
typedef VOS_UINT8 PPP_MNTN_OM_RESULT_TYPE_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8
 * Description : Flow Protocol Identifier
                 C.R1001-H_v1.0_Administration of Parameter Value Assignments for cdma2000
                 Spread Spectrum Standards Table 11.3-1
*******************************************************************************/
enum CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_NULL                            = 0x00,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_PPP                    = 0x01,
    CTTF_HRPD_PA_MNTN_IPV4                                          = 0x02,
    CTTF_HRPD_PA_MNTN_IPV6                                          = 0x03,
    CTTF_HRPD_PA_MNTN_ROHC                                          = 0x04,
    CTTF_HRPD_PA_MNTN_IPV4_AND_IPV6                                 = 0x05,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_WITH_ALTPPP                 = 0x06,
    CTTF_HRPD_PA_MNTN_HDLC_LIKE_FRMAING_SUPPORTING_MULTIPLE_PDNS    = 0x07,
    CTTF_HRPD_PA_MNTN_PDN_MUX_FOR_IP_PDNS                           = 0x08,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_HDLC_LIKE_FRAMING     = 0x09,
    CTTF_HRPD_PA_MNTN_BCMCS_OVER_UNICAST_WITH_SEG_BASED_FRAMING     = 0x0A,
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8;

/*******************************************************************************
 * Name        : CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8
 * Description : Route Protocol Identifier
                 C.R1001-H_v1.0_Administration of Parameter Value Assignments for cdma2000
                 Spread Spectrum Standards Table 11.3-1
*******************************************************************************/
enum CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM
{
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_NULL                           = 0x00,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ROHC                           = 0x04,
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_BUTT
};
typedef VOS_UINT8 CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8
 枚举说明  : 物理层支持的PacketSize类型
*****************************************************************************/
enum CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM
{
    CTTF_HRPD_MNTN_RTC3MAC_PS_0         = 0x00,  /* PS大小为0bit<-->0Byte */
    CTTF_HRPD_MNTN_RTC3MAC_PS_128       = 0x01,  /* PS大小为128bit<-->16BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_256       = 0x02,  /* PS大小为256bit<-->32BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_512       = 0x03,  /* PS大小为512bit<-->64BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_768       = 0x04,  /* PS大小为768bit<-->96BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_1024      = 0x05,  /* PS大小为1024bit<-->128BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_1536      = 0x06,  /* PS大小为1536bit<-->192BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_2048      = 0x07,  /* PS大小为2048bit<-->256BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_3072      = 0x08,  /* PS大小为3072bit<-->384BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_4096      = 0x09,  /* PS大小为4096bit<-->512BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_6144      = 0x0A,  /* PS大小为6144bit<-->768BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_8192      = 0x0B,  /* PS大小为8192bit<-->1024BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_12288     = 0x0C,  /* PS大小为12288bit<-->1536BYTE */
    CTTF_HRPD_MNTN_RTC3MAC_PS_BUTT      = 0x0D
};
typedef  VOS_UINT8 CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* R99 Mailbox VTB 译码数据地址 */
extern VOS_UINT32  g_aulR99MailboxVtbAddr[];


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    VOS_UINT32  ulMsgId;

    VOS_UINT16  usOriginalId;
    VOS_UINT16  usTerminalId;
    VOS_UINT32  ulTimeStamp;
    VOS_UINT32  ulSN;
}DIAG_TRANS_MSG_HDR_STRU;

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
   W模可维可测消息
*****************************************************************************/
typedef struct
{
    WTTF_RLC_MNTN_RB_CHOSEN_ENUM_UINT32     enConfig;       /* 共32bit,从低到高分别代表RB1~RB32,RB0默认钩取  */
                                                            /* 信令RB: 0x000F */
                                                            /* 业务RB: 0xFFF0 */
                                                            /* ALL RB: 0xFFFF */
                                                            /* 取消跟踪: 0x0000 */
    VOS_UINT16                              usTracePduSize;
    VOS_UINT16                              usTraceCipherPduSize;
    VOS_UINT16                              usTracePduCnt;
    VOS_UINT8                               aucRsv[2];
}WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_PHY_MAC_SUB_ATTRIB_ENUM_UINT8    enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU;

typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU;
typedef WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU  WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU;

typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enConfig;
    VOS_UINT8                                   aucRsv[3];
}WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU;

typedef struct
{
    TTF_MNTN_TRACE_CHOSEN_ENUM_UINT32           enChoice;
    VOS_UINT32                                  ulTraceDataLen;              /* 当选择TTF_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN时，此值有效 */
}TTF_MNTN_TRACE_DATA_CONFIG_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU;

typedef struct
{
    IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                          ulTraceDataLen;         /* 当选择TRACE_CONFIGURABLE_LEN_CHOSEN时，此值有效 */
}IPS_MNTN_TRACE_CONFIG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_OUTPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_LOCAL_TRACE_CFG_STRU;

typedef struct
{
    IPS_MNTN_CCORE_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                                ulTraceDataLen;         /* 当选择TRACE_CONFIGURABLE_LEN_CHOSEN时，此值有效 */
}IPS_MNTN_CCORE_TRACE_CONFIG_STRU;

typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU;
typedef IPS_MNTN_CCORE_TRACE_CONFIG_STRU  IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU;


/*****************************************************************************
 结构名     : OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU
 对应消息: ID_OM_WTTF_RLC_DATA_TRANS_INFO_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;        /*开始或停止上报*/
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptAM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptUM;
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enRptTM;
    VOS_UINT32                                  ulRptPeriod;      /*【1..5】单位：秒,报告周期*/
} OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU;


/*****************************************************************************
 结构名     : TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU
 对应消息: ID_WTTF_OM_RLC_DATA_TRANS_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* 返回查询结构成功或失败 */
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU;

typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;
typedef TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_CNF_STRU TTF_OM_UPA_DATA_STATUS_G_INFO_CNF_STRU;

/*****************************************************************************
 结构名     : WTTF_TRACE_MSG_CONFIG_STRU
 对应消息: WTTF_TRACE_MSG_CONFIG_STRU
*****************************************************************************/
typedef struct
{
    WTTF_TRACE_MAC_RLC_DATA_IND_CONFIG_STRU         stTraceMacRlcDataIndCfg;
    WTTF_TRACE_RLC_MAC_DATA_REQ_CONFIG_STRU         stTraceRlcMacDataReqCfg;

    WTTF_TRACE_PHY_MAC_DATA_IND_CONFIG_STRU         stTracePhyMacDataIndCfg;
    WTTF_TRACE_MAC_PHY_DATA_REQ_CONFIG_STRU         stTraceMacPhyDataReqCfg;

    WTTF_TRACE_PHY_MAC_HS_PDU_DATA_IND_CONFIG_STRU  stTracePhyMacHsPduDataIndCfg;
    WTTF_TRACE_UPA_PHY_DATA_REQ_CONFIG_STRU         stTraceUpaPhyDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyMacInfoIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaStatusIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceUpaSchedStausIndCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacPhyAmrDataIndCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTracePhyRlcAmrDataReqCfg;

    WTTF_TRACE_PDCP_RABM_DATA_IND_CONFIG_STRU       stTracePdcpRabmDataIndCfg;
    WTTF_TRACE_RABM_PDCP_DATA_REQ_CONFIG_STRU       stTraceRabmPdcpDataReqCfg;

    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceRlcMacIPDataCfg;
    WTTF_TRACE_MSG_SIMPLE_CONFIG_STRU               stTraceMacRlcIPDataCfg;
}WTTF_TRACE_MSG_CONFIG_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    WTTF_TRACE_MSG_CONFIG_STRU        stAdvancedConfig;
}OM_TTF_WCDMA_ADVANCED_TRACE_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名     : TTF_OM_WCDMA_ADVANCED_TRACE_CONFIG_CNF_STRU
 对应消息: ID_WTTF_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* 返回查询结构成功或失败 */

} TTF_OM_WCDMA_ADVANCED_TRACE_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名     :  OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU
 对应消息:  ID_OM_WTTF_RLC_PDU_SIZE_TRANS_INFO_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stTransHdr;
    TTF_MNTN_RPT_CMD_ENUM_UINT8         enCommand;        /*开始或停止上报*/
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulRptPeriod;    /*【1..5】单位：秒,报告周期*/
} OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPduSize;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPduCount;
}WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU;

/*****************************************************************************
 结构名     :  TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU
 对应消息:  TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;
    PS_BOOL_ENUM_UINT8                  enExist;                  /*PS_TRUE:表示此RbId存在并且支持RLC PDU SIZE可变。*/
    VOS_UINT8                           ucRlcSizeLevelCnt;        /*有效的档位等级*/
    VOS_UINT8                           aucReserve1[1];
    WTTF_MNTN_RLC_PDU_SIZE_INFO_STRU    astMntnRlcPduSizeInfo[WTTF_MNTN_MAX_FLX_RLC_SIZE_LEVEL_CNT];/*有效的RLC SIZE,下标对应ucPduSizeIdx*/
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU;


/*****************************************************************************
 结构名    :WTTF_MNTN_RLC_PDU_SIZE_TRANS_INFO_OBJ_STRU
 协议表格  :可维可测实现上行RLC PDU Size选择统计
 ASN.1描述 :
 结构说明  : WTTF MNTN RLC Data Trans Info 对象
*****************************************************************************/
typedef struct{
    VOS_UINT32                                          ulSimuClock;
    OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU       stOmRlcPduSizeReq;
    TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_STRU           astMntnRlCPduSizeTransInfo[WTTF_MNTN_MAX_RB_ID + 1];
} WTTF_MNTN_RLC_PDU_SIZE_TRANS_INFO_OBJ_STRU;

/*****************************************************************************
 结构名     : TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU
 对应消息: ID_WTTF_OM_RLC_PDU_SIZE_TRANS_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* 返回查询结构成功或失败 */
} TTF_OM_WCDMA_RLC_PDU_SIZE_TRANS_INFO_CNF_STRU;


/*****************************************************************************
 结构名     :  OM_TTF_WCDMA_UPA_DATA_STATUS_G_INFO_REQ_STRU
 对应消息:  ID_OM_WTTF_UPA_DATA_STATUS_G_INFO_REQ
*****************************************************************************/
typedef OM_TTF_WCDMA_RLC_PDU_SIZE_TRANS_INFO_REQ_STRU OM_TTF_WCDMA_UPA_DATA_STATUS_G_INFO_REQ_STRU;


/*****************************************************************************
 结构名     :  TTF_OM_WCDMA_UPA_DATA_STATUS_G_INFO_CNF_STRU
 对应消息:  ID_WTTF_OM_UPA_DATA_STATUS_G_INFO_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* 返回查询结构成功或失败 */

} TTF_OM_WCDMA_UPA_DATA_STATUS_G_INFO_CNF_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlcResetNum;          /* 发生Reset次数 */
                                                                /* 以下三种情况发送方会发起Reset
                                                                1)"No_Discard after MaxDAT number of transmissions" is configured and VT(DAT) equals the value MaxDAT (see subclause 9.7.3.4);
                                                                2)VT(MRW) equals the value MaxMRW;
                                                                3)A STATUS PDU or a piggybacked STATUS PDU including "erroneous Sequence Number" is received (see clause 10);
                                                                */

    VOS_UINT32                          ulLowRlcPduTxBytes;     /*低位:发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs的字节数（其中包括新产成的数据和控制PDU，重传的PDU，Reset PDU）*/
    VOS_UINT32                          ulHighRlcPduTxBytes;    /*高位:发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs的字节数（其中包括新产成的数据和控制PDU，重传的PDU，Reset PDU）*/

    VOS_UINT32                          ulLowRlcSduTxBytes;        /*低位:发送的RLC SDU字节数：统计的是从查询时刻开始计时，总共被分段成PDU的SDUs的字节数*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*高位:发送的RLC SDU字节数：统计的是从查询时刻开始计时，总共被分段成PDU的SDUs的字节数*/

    VOS_UINT32                          ulCurPrdRlcSduTxBytes;  /* 当前上报周期内发送RLC SDU字节数 */
    VOS_UINT32                          ulRlcDataPduTxNum;        /* 发送的数据PDU个数：统计的是从查询时刻开始计时，总共发送的到MAC层的新产生的数据PDUs块数（其中不包括重传的数据PDU）*/
    VOS_UINT32                          ulRlcDataPduRetxNum;    /* 发生重传的数据PDU个数：统计的是从查询时刻开始计时，总共发生重传的PDU个数（同一个PDU重传多次，则当多次累加）,新产生的数据PDU个数＝发送的数据PDU个数 － 发生重传的数据PDU个数*/
    VOS_UINT32                          ulRlcNackedPduNum;      /* 负确认的PDU个数:统计的是从查询时刻开始计时,总共从对端收到负确认的PDU个数*/
    VOS_UINT32                          ulRlcCtrlPduTxNum;        /* 发送的控制PDU个数:统计的是从查询时刻开始计时,总共发送到MAC层的控制PDU个数(其中包括状态PDU，Reset，Reset Ack PDU)*/
    VOS_UINT16                          usRlcLastTxPduSn;       /* [0..4095]最近一次发送的SN值:VtS-1 */
    VOS_UINT16                          usRlcLastAckInseqPduSn; /* [0..4095]最后一个按序被确认的SN:VtA */
    VOS_UINT16                          usRlcVacantTxWinSize;   /* [1..4095]指VtMs-VtS */
    VOS_UINT8                           aucReserve2[2];
    VOS_UINT32                          ulRlcBo;                /* 实体BO */
    VOS_UINT32                          ulRlcDataPdu3ReTxNum;   /* 重传次数达到三次的数据PDU个数*/
    VOS_UINT32                          ulRlcDataPdu4ReTxNum;   /* 重传次数达到四次的数据PDU个数*/
    VOS_UINT32                          ulRlcDataPdu5ReTxNum;   /* 重传次数达到五次的数据PDU个数*/
    VOS_UINT32                          ulRlcDataPdu6ReTxNum;   /* 重传次数达到六次的数据PDU个数*/
    VOS_UINT32                          ulRlcDataPduMore7ReTxNum;/* 重传次数达到七次以上（包括七次）的数据PDU个数*/
} WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlcResetNum;          /* 发生Reset次数 */
    VOS_UINT32                          ulLowRlcPduRxBytes;        /* 低位:接收到的RLC PDU 字节数: 统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数（其中包括了正确或错误的数据PDU和控制PDU，以及重复接收或不在接收窗内的数据PDU，甚至是CRC错误），所指的是MAC接收的吞吐量*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /* 高位:接收到的RLC PDU 字节数: 统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数（其中包括了正确或错误的数据PDU和控制PDU，以及重复接收或不在接收窗内的数据PDU，甚至是CRC错误），所指的是MAC接收的吞吐量*/

    VOS_UINT32                          ulLowRlcSduRxBytes;     /* 低位:接收到的SDU字节数: 统计的是从查询时刻开始计时，总共重组完成的SDU字节数 */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /* 高位:接收到的SDU字节数: 统计的是从查询时刻开始计时，总共重组完成的SDU字节数 */
    VOS_UINT32                          ulCurPrdRlcSduRxBytes;    /* 当前上报周期内接收RLC SDU字节数 */
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU个数：统计的是从查询时刻开始计时，总共从MAC接收上来的CRC错误的PDU个数*/
    VOS_UINT32                          ulRlcInvalidDataPduRxNum;    /* 无效数据PDU个数: 统计的是从查询时刻开始计时，总共从MAC接收上来的无效数据PDU个数（其中包括解析错误的数据PDU，重复接收或不在接收窗内的数据PDU）*/
    VOS_UINT32                          ulRlcDataPduRxNum;      /* 接收到的数据PDU个数：统计的是从查询时刻开始计时,总共从MAC接收上来的有效数据PDU个数（其中不包括重复接收或窗外的数据PDU）*/
    VOS_UINT32                          ulRlcCtrlPduRxNum;      /* 接收到的控制PDU个数：统计的是从查询时刻开始计时，总共从MAC接收上来的控制PDU个数（其中包括了解析错误的控制PDU）*/
    VOS_UINT32                          ulRlcNackedPduNum;      /* 负确认的PDU个数:统计的是从查询时刻开始计时,总共发送到对端负确认的PDU个数*/
    VOS_UINT16                          usRlcLastRxInseqPduSn;  /*[0..4095]，下一个要接收的SN值  */
    VOS_UINT16                          usRlcHighestPduSn;      /*[0..4095]，最高接收的PDU序号*/
} WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* 表示此实体是否存在，0表示不存在，1表示存在 */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_AM_UL_DATA_TRANS_INFO_STRU    stRlcMntnAmUlDataTransInfo;
    WTTF_MNTN_RLC_AM_DL_DATA_TRANS_INFO_STRU    stRlcMntnAmDlDataTransInfo;
} WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcPduTxBytes;     /*低位: 发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs的字节数*/
    VOS_UINT32                          ulHighRlcPduTxBytes;    /*高位: 发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs的字节数*/
    VOS_UINT32                          ulLowRlcSduTxBytes;        /*低位: 发送的RLC SDU字节数：统计的是从查询时刻开始计时，总共被分段成PDU的SDUs的字节数*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*高位: 发送的RLC SDU字节数：统计的是从查询时刻开始计时，总共被分段成PDU的SDUs的字节数*/
    VOS_UINT32                          ulRlcPduTxNum;            /*发送的RLC PDU 个数，统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs个数*/
    VOS_UINT16                          usRlcLastTxPduSn;       /*[0..4095]，最近一次发送的SN值:VtUs-1*/
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulRlcBo;                /* 实体BO */
} WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcPduRxBytes;        /*低位: 接收的RLC PDU字节数：统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数，包括解析错误的PDU*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /*高位: 接收的RLC PDU字节数：统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数，包括解析错误的PDU*/
    VOS_UINT32                          ulLowRlcSduRxBytes;     /*低位: 接收到的SDU字节数:统计的是从查询时刻开始计时，总共重组完成的SDU字节数 */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /*高位: 接收到的SDU字节数:统计的是从查询时刻开始计时，总共重组完成的SDU字节数 */
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU个数：统计的是从查询时刻开始计时，总共从MAC接收上来的CRC错误的PDU个数*/
    VOS_UINT32                          ulRlcInvalidPduRxNum;   /* 无效PDU个数: 统计的是从查询时刻开始计时，总共从MAC接收上来的无效PDU个数（其中包括序号不连续、Li错误、指示前一个PDU有误的PDU）*/
    VOS_UINT32                          ulRlcValidPduRxNum;     /* 有效PDU个数: 统计的是从查询时刻开始计时，总共从MAC接收上来的有效PDU个数(除CrcError,和invalid PDU外的PDU) */
    VOS_UINT16                          usRlcLastRxInseqPduSn;  /*[0..4095]，最近一次接收到的SN值:VrUs - 1 */
    VOS_UINT8                           aucReserve1[2];
} WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* 表示此实体是否存在，0表示不存在，1表示存在 */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_UM_UL_DATA_TRANS_INFO_STRU    stRlcMntnUmUlDataTransInfo;
    WTTF_MNTN_RLC_UM_DL_DATA_TRANS_INFO_STRU    stRlcMntnUmDlDataTransInfo;
} WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcSduTxBytes;     /*低位: 发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC SDUs的字节数，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulHighRlcSduTxBytes;    /*高位: 发送的RLC PDU字节数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC SDUs的字节数，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulLowRlcDiscardSduTxBytes;  /*低位: Discard RLC SDU字节数：统计的是从查询时刻开始计时，总共丢弃的RLC SDUs的字节数，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulHightRlcDiscardSduTxBytes;  /*高位: Discard RLC SDU字节数：统计的是从查询时刻开始计时，总共丢弃的RLC SDUs的字节数，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulRlcPduTxNum;            /* 发送的RLC PDU个数：统计的是从查询时刻开始计时，总共发送到MAC层的RLC PDUs的个数*/
} WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLowRlcSduRxBytes;     /*低位: 接收到的SDU字节数:统计的是从查询时刻开始计时，总共接收到的SDU字节数，不是8bit的按8整除并向上取整 */
    VOS_UINT32                          ulHighRlcSduRxBytes;    /*高位: 接收到的SDU字节数:统计的是从查询时刻开始计时，总共接收到的SDU字节数，不是8bit的按8整除并向上取整 */
    VOS_UINT32                          ulLowRlcPduRxBytes;        /* 低位:接收到的RLC PDU 字节数: 统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数（其中包括了CrcError的PDU），所指的是MAC接收的吞吐量，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulHighRlcPduRxBytes;    /* 高位:接收到的RLC PDU 字节数: 统计的是从查询时刻开始计时，总共从MAC层接收到的RLC PDUs的字节数（其中包括了CrcError的PDU），所指的是MAC接收的吞吐量，不是8bit的按8整除并向上取整*/
    VOS_UINT32                          ulRlcCrcErrPduRxNum;    /* Crc Error PDU个数：统计的是从查询时刻开始计时，总共从MAC接收上来的CRC错误的PDU个数*/
    VOS_UINT32                          ulRlcValidPduRxNum;     /* 有效PDU个数: 统计的是从查询时刻开始计时，总共从MAC接收上来的有效PDU个数(除CrcError外的PDU) */
} WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名     :  WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU
 对应消息:  WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                          enExist;                /* 表示此实体是否存在，0表示不存在，1表示存在 */
    VOS_UINT8                                   ucRbId;
    VOS_UINT8                                   aucReserve2[2];
    WTTF_MNTN_RLC_TM_UL_DATA_TRANS_INFO_STRU    stRlcMntnTmUlDataTransInfo;
    WTTF_MNTN_RLC_TM_DL_DATA_TRANS_INFO_STRU    stRlcMntnTmDlDataTransInfo;
} WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU;

/*****************************************************************************
 结构名    :TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ID_WTTF_OM_RLC_DATA_TRANS_INFO_IND上报查询内容
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulCurPrdRlcSduTxRate;  /* 当前上报周期内发送RLC SDU字节数 */
    VOS_UINT32                              ulCurPrdRlcSduRxRate;  /* 当前上报周期内发送RLC SDU字节数 */
    WTTF_MNTN_RLC_AM_DATA_TRANS_INFO_STRU   astMntnRlcAmDataTransInfo[WTTF_MNTN_MAX_AM_RB_NUM];
    WTTF_MNTN_RLC_UM_DATA_TRANS_INFO_STRU   astMntnRlcUmDataTransInfo[WTTF_MNTN_MAX_UM_RB_NUM];
    WTTF_MNTN_RLC_TM_DATA_TRANS_INFO_STRU   astMntnRlcTmDataTransInfo[WTTF_MNTN_MAX_TM_RB_NUM];
} TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU;

/*****************************************************************************
 结构名    :WTTF_MNTN_RLC_DATA_TRANS_INFO_OBJ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : WTTF MNTN RLC Data Trans Info 对象
*****************************************************************************/
typedef struct{
    VOS_UINT32                                     ulSimuClock;
    OM_TTF_WCDMA_RLC_DATA_TRANS_INFO_REQ_STRU      stOmRlcReq;
    TTF_OM_WCDMA_RLC_DATA_TRANS_INFO_IND_STRU      stRlcOmInd;
    VOS_UINT8                                      aucAmReTxNumPerDataPdu[WTTF_MNTN_MAX_AM_RB_NUM][WTTF_MNTN_RLC_AM_MAX_SN_NUM];
} WTTF_MNTN_RLC_DATA_TRANS_INFO_OBJ_STRU;

/*****************************************************************************
 结构名     :  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
 对应消息:  ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_BRIDGE_TRACE_CFG_STRU              stBridgeArpTraceCfg;        /*配置捕获网桥消息*/
    IPS_MNTN_INPUT_TRACE_CFG_STRU               stPreRoutingTraceCfg;       /*配置捕获TCP/IP协议栈接收消息*/
    IPS_MNTN_OUTPUT_TRACE_CFG_STRU              stPostRoutingTraceCfg;      /*配置捕获TCP/IP协议栈发送消息*/
    IPS_MNTN_LOCAL_TRACE_CFG_STRU               stLocalTraceCfg;            /*配置捕获TCP/IP协议栈发送消息*/
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8     enAdsIPConfig;
    VOS_UINT8                                   aucRsv[3];                  /* 保留位 */
}IPS_MNTN_TRACE_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
 对应消息:  OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU            stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU     stIpsAdvanceCfgReq;
}OM_IPS_ADVANCED_TRACE_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名     :  IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU
 对应消息:  ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32           enRslt;                 /* 返回查询结构成功或失败，PS_SUCC表示成功，PS_FAIL表示失败 */
}IPS_MNTN_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU         stDiagHdr;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU  stIpsAdvanceCfgCnf;
}IPS_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名     :  OM_IPS_MNTN_INFO_CONFIG_REQ_STRU
 对应消息:  ID_OM_IPS_MNTN_INFO_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                          usTimeLen;              /*单位：秒 */
}IPS_MNTN_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_INFO_CFG_REQ_STRU          stIpsMntnCfgReq;
}OM_IPS_MNTN_INFO_CONFIG_REQ_STRU;


/*****************************************************************************
 结构名     :  IPS_OM_MNTN_INFO_CONFIG_CNF_STRU
 对应消息:  ID_IPS_OM_MNTN_INFO_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    IPS_MNTN_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                           aucRsv[2];
}IPS_MNTN_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU    stDiagHdr;
    IPS_MNTN_INFO_CFG_CNF_STRU stIpsMntnCfgCnf;
}IPS_OM_MNTN_INFO_CONFIG_CNF_STRU;


/*****************************************************************************
   G模可维可测消息
*****************************************************************************/
/*****************************************************************************
 结构名     :  GRM_MNTN_COM_INFO_STRU
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulTlli;                 /* 0xffffffff:无效值 */
    GRM_TBF_INFO_TEST_MODE_ENUM_UINT8    ucTestMode;             /* GPRS环回时的实际工作模式, 0xff:无效值 */
    VOS_UINT8                            aucRsv[1];
    VOS_UINT16                           usLlcPduNum;            /* a模式下待环回的LLC PDU数目, 0xffff:无效值 */
}GRM_MNTN_COM_INFO_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_UL_TBF_STRU
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucUlRlcMode;        /* 0:GRLC_MODE_AM, 1:GRLC_MODE_UM, 0xff:无效值 */
    GRM_TBF_INFO_COUNTDOWN_FLAG_ENUM_UINT8        ucCountdownFlag;    /* 此标志只在非扩展上行TBF下使用，表示:是否进入倒计数过程.
                                                                         VOS_YES:进入了倒计数, VOS_NO:没有进入, 0xff:无效值 */
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usUlCodeType;       /* EDGE_CODE_SCHEME_BUTT: 0xffff 无效值 */
    VOS_UINT8                                     ucUlTfi;            /* 0xff: 无效值 */
    GRM_TBF_INFO_TI_ENUM_UINT8                    ucTi;               /* 1: 冲突解决未完成, 0: 冲突解决完成, 0xff: 无效值 */
    VOS_UINT8                                     aucRsv[2];
}GRM_MNTN_UL_TBF_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_UL_ENTITY_INFO_STRU 上行信息
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    /*====================*/ /* 状态信息 */
    GRM_TBF_INFO_TBF_MODE_ENUM_UINT8         ucUlTbfMode;                    /* 1:Extend 扩展TBF, 0: no-extend 非扩展, 0xff:无效值*/
    VOS_UINT8                                ucBsCvMax;                      /* Range: 0 to 15. 0xff:无效值 */
    GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucUlTsFlag[GRM_MNTN_TS_TOTAL]; /* 0xff: 无效值 */
    VOS_UINT8                                aucRsv[2];
    GRM_MNTN_UL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];  /* Tbf信息 */
}GRM_MNTN_UL_ENTITY_INFO_STRU;

/*================*/  /*下行信息*/
/*****************************************************************************
 结构名     :  GRM_MNTN_DL_TBF_STRU
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    /*AM:用于可维可测
    UM模式:最后接收的块的编码方式，提供给UM模式下填充使用，
    初始值为EDGE_CODE_SCHEME_BUTT，代表尚未收到正确的下行块 */
    GRM_TBF_INFO_EDGE_CODE_SCHEME_ENUM_UINT16     usDlCodeType;       /* EDGE_CODE_SCHEME_BUTT: 0xffff 无效值 */
    GRM_TBF_INFO_FINALBLKRXED_ENUM_UINT8          ucFinalBlkRxed;     /* FBI=1的块是否已经接收到, 0xff: 无效值 */
    GRM_TBF_INFO_RLC_MODE_ENUM_UINT8              ucDlRlcMode;        /* 0:AM, 1:UM, 0xff: 无效值 */
    VOS_UINT8                                     ucDlTfi;            /* TFI value 0xff: 无效值 */
    VOS_UINT8                                     aucRsv[3];
}GRM_MNTN_DL_TBF_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_DL_ENTITY_INFO_STRU
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
	GRM_TBF_INFO_TIMESLOT_FLAG_ENUM_UINT8    aucDlTsFlag[GRM_MNTN_TS_TOTAL];                 /* 下行时隙掩码 0xff: 无效值*/
    GRM_MNTN_DL_TBF_STRU                     astTbf[GRLC_MNTN_MAX_TBF_NUM];   /* 当前只支持单TBF */
}GRM_MNTN_DL_ENTITY_INFO_STRU;

/*================*/  /*上报OM的总体结构信息*/
/*****************************************************************************
 结构名     :  GRM_MNTN_GRM_OM_INFO_STRU
 对应消息:  GRM_MNTN_GRM_OM_INFO
*****************************************************************************/
typedef struct
{
    GRM_MNTN_COM_INFO_STRU          stGrmMntnComInfo;   /*公共信息*/
    GRM_MNTN_UL_ENTITY_INFO_STRU    stGrmMntnUlInfo;    /*上行信息*/
    GRM_MNTN_DL_ENTITY_INFO_STRU    stGrmMntnDlInfo;    /*下行信息*/
}GRM_MNTN_GRM_OM_INFO_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_OM_GRM_INFO_CFG_REQ_STRU
 对应消息:  ID_GRM_MNTN_OM_GRM_INFO_CFG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;      /* 透传消息头*/

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;    /* 单位: s */
}GRM_MNTN_OM_GRM_INFO_CFG_REQ_STRU;


/*****************************************************************************
 结构名     :  GRM_MNTN_GRM_OM_INFO_CFG_CNF_STRU
 对应消息:  ID_GRM_MNTN_GRM_OM_INFO_CFG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;     /* 透传消息头*/

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT16                              usRptPeriod;   /* 单位: s */
}GRM_MNTN_GRM_OM_INFO_CFG_CNF_STRU;


/*****************************************************************************
 结构名     :  GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ_STRU
 对应消息:  ID_GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_OM_GRM_THROUGHPUT_CFG_REQ_STRU;


/*****************************************************************************
 结构名     :  GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF_STRU
 对应消息:  ID_GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    GRM_RESULT_TYPE_ENUM_UINT32             enRslt;
    GRM_MNTN_OM_REPORT_ACTION_ENUM_UINT16   enStartOrStop;
    VOS_UINT8                               aucRsv[2];
}GRM_MNTN_GRM_OM_THROUGHPUT_CFG_CNF_STRU;

typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU;
typedef TTF_MNTN_TRACE_DATA_CONFIG_STRU GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU;

/*****************************************************************************
 结构名     : GTTF_TRACE_MSG_CONFIG_STRU
 对应消息: GTTF_TRACE_MSG_CONFIG_STRU
*****************************************************************************/
typedef struct
{
    GTTF_MNTN_LL_GRM_TRACE_CONFIG_STRU          stllGrmCfg;
    GTTF_MNTN_SN_LL_TRACE_CONFIG_STRU           stSnllCfg;
    GTTF_MNTN_RABM_SN_TRACE_CONFIG_STRU         stRabmSnCfg;
}GTTF_TRACE_MSG_CONFIG_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ_STRU
 对应消息:  ID_GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;
    TOOL_GTTF_CFG_SWITCH_ENUM_UINT32            enL2CfgSwitch;          /* TRACE开关0:关闭1:打开*/
    GTTF_TRACE_MSG_CONFIG_STRU                  stAdvancedConfig;
}GRM_MNTN_OM_GTTF_ADV_TRACE_SWITCH_REQ_STRU;

/*****************************************************************************
 结构名     :  GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF_STRU
 对应消息:  ID_GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stTransHdr;
    PS_RSLT_CODE_ENUM_UINT32          enRslt;         /* 返回查询结构成功或失败 */
}GRM_MNTN_GTTF_OM_ADV_TRACE_SWITCH_CNF_STRU;

/*****************************************************************************
   CP上关于IP报文、PPP帧之类的维测
*****************************************************************************/
/*****************************************************************************
 结构名     :  IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU
 对应消息:
*****************************************************************************/
typedef struct
{
    WTTF_TRACE_MSG_SIMPLE_ATTRIB_ENUM_UINT8         enVISPLogOutConfig;         /* VISP日志总开关 */
    IPS_MNTN_CCORE_TCPIP_LOG_LEVEL_E_ENUM_UINT8     enVISPRunLogLevelConfig;    /* VISP RUN日志级别配置 */
    VOS_UINT8                                       aucRsv[2];                  /* 保留位 */
}IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU
 对应消息:  ID_OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_BRIDGE_TRACE_CFG_STRU        stBridgeTraceCfg;       /*配置捕获网桥消息*/
    IPS_MNTN_CCORE_INPUT_TRACE_CFG_STRU         stInputTraceCfg;        /*配置捕获TCP/IP协议栈接收消息*/
    IPS_MNTN_CCORE_OUTPUT_TRACE_CFG_STRU        stOutputTraceCfg;       /*配置捕获TCP/IP协议栈发送消息*/
    IPS_MNTN_CCORE_VISP_LOG_CONFIG_REQ_STRU     stVispLogConfig;
}IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU               stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU  stIpsCcoreCfgReq;
}OM_IPS_CCORE_ADVANCED_TRACE_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU
 对应消息:  ID_IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32            enRslt;                 /* 返回查询结构成功或失败，PS_SUCC表示成功，PS_FAIL表示失败 */
}IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU              stDiagHdr;
    IPS_MNTN_CCORE_TRACE_CONFIG_CNF_STRU stIpsCcoreCfgCnf;
}IPS_CCORE_OM_ADVANCED_TRACE_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名     :  OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU
 对应消息:  ID_OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                                usTimeLen;              /*单位：秒 */
}IPS_MNTN_CCORE_INFO_CFG_REQ_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU           stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_REQ_STRU  stIpsCcoreMntnCfgReq;
}OM_IPS_CCORE_MNTN_INFO_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU
 对应消息:  ID_IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    IPS_MNTN_CCORE_RESULT_TYPE_ENUM_UINT32    enRslt;
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT8                                 aucRsv[2];
}IPS_MNTN_CCORE_INFO_CFG_CNF_STRU;

typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU             stDiagHdr;
    IPS_MNTN_CCORE_INFO_CFG_CNF_STRU    stIpsCcoreMntnCfgCnf;
}IPS_CCORE_OM_MNTN_INFO_CONFIG_CNF_STRU;

/*****************************************************************************
   1X的可维可测消息
*****************************************************************************/
/*****************************************************************************
 结构名    : OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU
 结构说明  : 1X下通用配置命令结构
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8             enCommand;      /* 开始或停止上报 */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* 上报周期, 单位: ms */
} OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU;

/*****************************************************************************
 结构名    : OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU
 结构说明  : 1X下RLP配置命令结构
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RLP_RPT_CMD_ENUM_UINT8         enCommand;      /* 开始或停止上报或清除 */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* 上报周期, 单位: ms */
} OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU;

/*****************************************************************************
 结构名    : OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU
 结构说明  : 1X下通用配置命令结构
*****************************************************************************/
typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;      /* 开始或停止上报或清除 */
    VOS_UINT8                               aucReserve[3];
    CTTF_1X_MAC_MNTN_RPT_PERIOD_ENUM_UINT32 enRptPeriod;    /* 上报周期, 单位: ms */
} OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU;

/*****************************************************************************
 结构名    : OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU
 结构说明  : HRPD通用配置命令结构
*****************************************************************************/
typedef struct
{
    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8        enCommand;      /* 开始或停止上报或清除 */
    VOS_UINT8                               aucReserve[3];
    CTTF_HRPD_MNTN_RPT_PERIOD_ENUM_UINT32   enRptPeriod;    /* 上报周期, 单位: ms */
} OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU;

/*****************************************************************************
 结构名    : OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU
 结构说明  : HRPD通用配置命令结构
*****************************************************************************/
typedef struct
{
    TTF_MNTN_RPT_CMD_ENUM_UINT8                 enCommand;      /* 开始或停止上报 */
    VOS_UINT8                                   aucReserve[3];
    CTTF_HRPD_MNTN_RTC_RPT_PERIOD_ENUM_UINT32   enRptPeriod; /* 上报周期, 单位: ms */
} OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU;

/*****************************************************************************
 结构名     :  OM_CTTF_1X_MNTN_CONFIG_REQ_STRU
 对应消息:  ID_OM_CTTF_1X_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    /* 根据CDMA 5.12s周期, 参考QXDM, 建议每1.28s上报一次 */
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stFwdLinkInfo;    /* 1X Forward Link Info, 上报周期: 1280ms */
    OM_CTTF_1X_MNTN_GENERIC_CONFIG_STRU         stRevLinkInfo;    /* 1X Reverse Link Info, 上报周期: 1280ms */
    OM_CTTF_1X_MNTN_RLP_GENERIC_CONFIG_STRU     stRlpStatistics;  /* 1X RLP statistics, 上报周期: 1280ms */
    OM_CTTF_1X_MNTN_COMM_GENERIC_CONFIG_STRU    stCommonStatistics;    /* Common Channel statistics, 上报周期: 1280ms */
} OM_CTTF_1X_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  OM_CTTF_HRPD_MNTN_CONFIG_REQ_STRU
 对应消息:  ID_OM_CTTF_HRPD_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    /* 根据CDMA 5.12s周期, 建议每1.28s上报一次 */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMacStatistics;    /* HRPD MAC Statistics, 上报周期: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stRlpStatistics;    /* HRPD RLP Statistics, 上报周期: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stMfpaStatistics;   /* MFPA RLP Statistics, 上报周期: 1280ms */
    OM_CTTF_HRPD_MNTN_GENERIC_CONFIG_STRU       stEmpaStatistics;   /* EMPA RLP Statistics, 上报周期: 1280ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3PktInfo;      /* RTC3 Packet Info, 上报周期: 640ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stT2pStatistics;    /* T2P Statistics, 上报周期: 640ms */
    OM_CTTF_HRPD_MNTN_COMM_CONFIG_STRU          stRtc3HarqInfo;     /* RTC3 Harq Info, 上报周期: 640ms */
} OM_CTTF_HRPD_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_HRPD_MNTN_CONFIG_CNF_STRU
 对应消息:  ID_CTTF_OM_HRPD_MNTN_CONFIG_CNF
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* 配置成功或失败 */
    VOS_UINT32                              ulReason;       /* 带具体失败的原因 */
} CTTF_OM_HRPD_MNTN_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名     :  CTTF_OM_1X_MNTN_CONFIG_CNF_STRU
 对应消息:  ID_CTTF_OM_1X_MNTN_CONFIG_CNF
 说明: 注意OM融合后, HIDS对X模的配置开关消息处理, 不同于GU模
       上报的CNF消息
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* 配置成功或失败 */
    VOS_UINT32                              ulReason;       /* 带具体失败的原因 */
} CTTF_OM_1X_MNTN_CONFIG_CNF_STRU;


/*****************************************************************************
 结构名    : CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU
 结构说明  : 某Forward信道的统计值
*****************************************************************************/
typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;  /* 无效值为BUTT */
    VOS_UINT8                              ucPercentage;    /* 成功解析的块百分比分子, [0..100], 无效值0xFF */
    VOS_UINT8                              aucReserved[2];  /* 保留字节, 按照无效值填写, 值为0 */
}CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_1X_MNTN_FWD_LINK_IND_STRU
 对应消息:  ID_CTTF_OM_1X_MNTN_FWD_LINK_IND
 说明:  主动上报消息, 在API调用时用指针指向上报内容即可
 结构说明  : 各Forward信道的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];   /* FCH统计值 */
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];  /* DCCH统计值 */
    CTTF_1X_MAC_MNTN_FWD_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];  /* SCH统计值 */
} CTTF_OM_1X_MNTN_FWD_LINK_IND_STRU;
/*****************************************************************************
 结构名     :  CTTF_OM_PPP_MNTN_CONFIG_REQ_STRU
 对应消息:  ID_OM_PPP_MNTN_CONFIG_REQ
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                     stTransHdr;

    TTF_MNTN_COMM_RPT_CMD_ENUM_UINT8            enCommand;      /* 开始、停止或清除 */
    VOS_UINT8                                   aucReserve[3];
} CTTF_OM_PPP_MNTN_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名     :  CTTF_HRPD_MNTN_PPPC_STATISTICS_REPORT_STRU
 对应消息:  pppc接口
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulSuccCnt;
    VOS_UINT32                  ulFailCnt;
    VOS_UINT32                  ulNameOrPwdAuthFailCnt;
    VOS_UINT32                  ulInvalidIpAddrCnt;
    VOS_UINT32                  ulInvalidDnsAddrCnt;
    VOS_UINT32                  ulOtherFail;
}CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_PPPC_MNTN_STATISTICS_IND_STRU
 对应消息:  ID_PPP_OM_MNTN_STATISTIC_INFO
 说明:  主动上报消息, 在API调用时用指针指向上报内容即可
 结构说明  : 1X公共信道的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PPP_STATISTICS_REPORT_STRU   stPppcStatisticInfo;
} CTTF_OM_PPPC_MNTN_STATISTICS_IND_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_PPP_MNTN_CONFIG_CNF_STRU
 对应消息:  ID_CTTF_OM_PPP_MNTN_CONFIG_CNF
 说明:
*****************************************************************************/
typedef struct
{
    DIAG_TRANS_MSG_HDR_STRU                 stDiagHdr;

    PS_RSLT_CODE_ENUM_UINT32                enRslt;         /* 配置成功或失败 */
    VOS_UINT32                              ulReason;       /* 带具体失败的原因 */
} CTTF_OM_PPP_MNTN_CONFIG_CNF_STRU;


/* CTTF_OM_1X_MNTN_xxx_IND_STRU上报消息中头的长度，sizeof(usPrimId)+sizeof(usToolId) */
#define  CTTF_OM_1X_MNTN_IND_HEAD_BYTE_SIZE     (4)

/* CTTF_OM_HRPD_MNTN_xxx_IND_STRU上报消息中头的长度，sizeof(usPrimId)+sizeof(usToolId) */
#define  CTTF_OM_HRPD_MNTN_IND_HEAD_BYTE_SIZE   (4)


/*****************************************************************************
 结构名    : CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU
 结构说明  : 某Reverse信道的统计值
*****************************************************************************/
typedef struct
{
    CTTF_1X_MAC_MNTN_RATE_ENUM_UINT8       enRate;  /* 无效值为BUTT */
    VOS_UINT8                              aucReserved[3]; /* 保留字节, 按照无效值填写, 值为0 */
} CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_1X_MNTN_REV_LINK_IND_STRU
 对应消息:  ID_CTTF_OM_1X_MNTN_REV_LINK_IND
 说明:  主动上报消息, 在API调用时用指针指向上报内容即可
 结构说明  : 各Reverse信道的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;

    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astFch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astDcch[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
    CTTF_1X_MAC_MNTN_REV_LINK_PER_INFO_STRU     astSch0[CTTF_1X_MAC_MNTN_MAX_REPORT_NUM];
} CTTF_OM_1X_MNTN_REV_LINK_IND_STRU;


/*****************************************************************************
 结构名    : CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU
 结构说明  : 某RLP实体的REV方向统计值
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;  /* 发送的帧的总字节数（高32bit）, 2015年工具不支持64bit类型, 故分拆开上报。无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFrameTotalByte;   /* 发送的帧的总字节数（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByteHigh;   /* 上层软件发送的总字节（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByte;   /* 上层软件发送的总字节（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulIdleFrameCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFchNewDataFrameCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFchRetxFrameCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSchNewDataFrameCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSchRetxFrameCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakSingle;    /* 重传一次后接收成功的次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakDouble;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakTriple;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbove;    /* 重传超过3次的次数, 无效值: 0xFFFFFFFF */
} CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 结构名    : CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU
 结构说明  : 某RLP实体的FWD方向统计值
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulFrameTotalByteHigh;  /* 接收的帧的总字节数（高32bit）, 2015年工具不支持64bit类型。无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFrameTotalByte;  /* 接收的帧的总字节数（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByteHigh;   /* 上层软件接收的总字节（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulUpperTotalByte;   /* 上层软件总接收的总字节（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulIdleFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFillFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulBlankFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNullFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFchNewDataFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulFchRetxFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSchNewDataFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSchRetxFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakCtrlFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortTimes;   /* NAK abort次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulInsufficentQualityFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidFcsFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidTypeFieldFrameCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidCtlFieldFrameCnt;    /* 无效值: 0xFFFFFFFF */
} CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 结构名    : CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU
 结构说明  : 某RLP实体的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT8            ucSrId;   /* 区分RLP实体的唯一编号, 无效值: 0xFF */
    VOS_UINT8            ucMeasuredRtt;  /* 最近一次测量的RTT, 无效值: 0xFF */
    VOS_UINT8            aucReserved[2];  /* 保留字节, 按照无效值填写, 值为0 */
    VOS_UINT16           usBSTriggeredResetTimes;  /* AT收到AN的复位RLP请求而复位RLP的次数，无效值: 0xFFFF */
    VOS_UINT16           usMSTriggeredResetTimes;   /* AT主动复位RLP的次数，无效值: 0xFFFF */
    VOS_UINT32           ulCurrentBo;  /* 实时BO, 无效值: 0xFFFFFFFF */
    CTTF_1X_RLP_MNTN_REV_STATISTICS_PER_ENTITY_STRU  stRevInfo;
    CTTF_1X_RLP_MNTN_FWD_STATISTICS_PER_ENTITY_STRU  stFwdInfo;
}CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_1X_MNTN_RLP_STATISTICS_IND_STRU
 对应消息:  ID_CTTF_OM_1X_MNTN_RLP_STATISTICS_IND
 结构说明  : 各RLP实体的统计值
 说明:  主动上报消息, 在API调用时用指针指向上报内容即可
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPrimId;
    VOS_UINT16                                      usToolId;

    CTTF_1X_RLP_MNTN_STATISTICS_PER_ENTITY_STRU     astRlpEntity[CTTF_1X_RLP_MNTN_MAX_NUM];
} CTTF_OM_1X_MNTN_RLP_STATISTICS_IND_STRU;


/*****************************************************************************
 结构名    : CTTF_1X_MNTN_PCH_STATISTIC_STRU
 结构说明  : PCH的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulTotalEncapPduFragCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ul96BitEncapPduFragCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ul192BitEncapPduFragCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalEncapPduCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulInvalidCrcEncapPduCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulChanLostCnt;   /* 无效值: 0xFFFFFFFF */
} CTTF_1X_MNTN_PCH_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_1X_MNTN_ACH_STATISTIC_STRU
 结构说明  : ACH的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulRequestTypeSduCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulResponseTypeSduCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe1Cnt;   /* 接入1次成功的次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe2Cnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe3Cnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe4Cnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbe5Cnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAccessProbeAboveCnt;    /* 接入5次以上才成功的次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulUnsucessfulAccessAttemptCnt;   /* 接入attempt失败次数, 无效值: 0xFFFFFFFF */
} CTTF_1X_MNTN_ACH_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU
 结构说明  : PAGE的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulGpmMatchedCnt;   /* 匹配上的GPM，无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSlotPageMatchedCnt;   /* Slot模式匹配的Page，无效值: 0xFFFFFFFF */
    VOS_UINT32    ulMismatchedPageCnt;    /* 所有的不匹配的Page，无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAddrMatchedOtherMsgCnt; /* 除了Page消息外，所有的地址匹配的消息数，无效值: 0xFFFFFFFF */
} CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU;

/*****************************************************************************
 结构名     :  CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND_STRU
 对应消息:  ID_CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND
 说明:  主动上报消息, 在API调用时用指针指向上报内容即可
 结构说明  : 1X公共信道的统计值
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usToolId;

    CTTF_1X_MNTN_PCH_STATISTIC_STRU     stPch;
    CTTF_1X_MNTN_ACH_STATISTIC_STRU     stAch;
    CTTF_1X_MNTN_PAGE_MSG_STATISTIC_STRU stPage;

} CTTF_OM_1X_MNTN_COMMON_CHANNEL_STATISTICS_IND_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU
 结构说明  : HRPD RTC3MAC 每个MAC Flow的包统计
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucFlowId;               /* MAC流ID，无效值: 0xFF */
    VOS_UINT8       aucReserved[1];         /* 保留字节, 按照无效值填写, 值为0xFF */
    VOS_UINT16      usActualAllocation;     /* 单位: 字节，无效值: 0xFFFF */
    VOS_UINT16      usSuggestAllocation;    /* 单位: 字节，无效值: 0xFFFF */
    VOS_UINT16      usRequiredQueueSize;    /* 单位: 字节，无效值: 0xFFFF */
    VOS_UINT16      usQOutflow;             /* 单位: 字节，无效值: 0xFFFF */
    VOS_UINT8       aucReserved1[2];        /* 保留字节, 按照无效值填写, 值为0xFF */
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU
 结构说明  : HRPD RTC3MAC 包信息统计,PacketId定义为有符号数，可以初始化为-128，
             从-128，图行看起来更自然。从0xFFFF跳到正数(0...9),看起来不习惯。
*****************************************************************************/
typedef  struct
{
    CTTF_HRPD_MAC_TRANS_MODE_ENUM_UINT8                     enTransMode;        /* 无效值: BUTT */
    CTTF_HRPD_MNTN_RTC3MAC_PAKETSIZE_INDEX_ENUM_UINT8       enPktSize;          /* 无效值: BUTT */
    VOS_UINT16                                              usPaddingByteSize;  /* 单位: 字节，无效值: 0xFFFF */
    VOS_INT8                                                cPacketId;          /* 无效值: -128,有效值0-9 */
    VOS_INT8                                                cTxT2pMax;          /* 单位:dB,无效值: -128 */
    VOS_INT8                                                cPotentialT2p;      /* 单位:dB, 无效值: -128 */
    VOS_UINT8                                               aucReserved[1];     /* 保留字节, 按照无效值填写, 值为0xFF */

    /* 各个MAC流的数据 */
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_PER_MAC_FLOW_STRU    astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU;

/*****************************************************************************
 结构名    : CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_PACKET_REPORT_STRU
 结构说明  : HRPD RTC3MAC 包信息统计上报
 对应消息  : ID_CTTF_OM_HRPD_MNTN_REV_LINK_PACKET_INFO_IND
 说明      : 主动上报消息, 在API调用时用指针指向上报内容即可
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU astLinkPktData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_PACKET_PER_FLOW];
} CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_PACKET_REPORT_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_LINK_PACKET_STRU
 结构说明  : HRPD RTC3MAC 每个MAC Flow的T2P信息统计
*****************************************************************************/
typedef struct
{
    VOS_UINT8       ucFlowId;       /* MAC流ID，无效值: 0xFF */
    VOS_INT8        cQrab;          /* -1:为unloaded, 1:loaded, 无效值: -128 */
    VOS_INT8        cDeltaT2p;      /* 无效值: -128 */
    VOS_INT8        cBucketFactor;  /* 无效值: -128 */
    VOS_INT16       sT2pInflow;     /* 无效值: -32768 */
    VOS_INT16       sT2pOutflow;    /* 无效值: -32768 */
    VOS_INT16       sBucketLevel;   /* 无效值: -32768 */
    VOS_INT16       sBucketLevelSat;/* Saturation Bucket Level, 无效值: -32768 */
} CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU
 结构说明  : HRPD RTC3MAC T2P信息统计
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_WORK_MODE_ENUM_UINT8         enWorkMode;     /* 无效值: BUTT */
    VOS_INT8                                            cQRABn;         /* -1:为unloaded, 1:loaded, 无效值: -128 */
    VOS_INT16                                           sFrab;          /* 无效值: -32768 */

    /* 各个MAC流的数据 */
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_PER_MAC_FLOW_STRU   astMacFlow[CTTF_HRPD_RTC3MAC_MNTN_FLOW_MAX_NUM];
}CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU;

/*****************************************************************************
 结构名    : CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_T2P_REPORT_STRU
 结构说明  : HRPD RTC3MAC T2P信息统计上报
 对应消息  : ID_CTTF_OM_HRPD_MNTN_REV_LINK_T2P_STATISTICS_IND
 说明      : 主动上报消息, 在API调用时用指针指向上报内容即可
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_LINK_T2P_STRU    astLinkT2pData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_T2P_PER_FLOW];
}CTTF_OM_HRPD_MNTN_RTC3MAC_LINK_T2P_REPORT_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU
 结构说明  : HRPD RTC3MAC Harq信息，ProcessId等定义为有符号数，可以初始化为-128，
             从-128到正数符号一般思维，图形看起来更自然。从0xFF跳到正数(0...9),
             看起来不习惯。
*****************************************************************************/
typedef struct
{
    VOS_INT8                                            cProcessId;     /* Invalid value:-128, the processer id of the next sub frame, value range is 0~2 */
    VOS_INT8                                            cSubPacketId;   /* Invalid value:-128, 0:first time,1:second time,2:third time,3:fouth time */
    VOS_INT8                                            cDataType;      /* Invalid value:-128, it indicates which type data will CSDR_HRPD_SUBFRAME_DATA_TYPE_ENUM_UINT16 end. Possible values are : 0:no data to send, 1:new data, 2:retransmission data, 3:silence duration */
    VOS_INT8                                            cPacketId;      /* Invalid value:-128, value range is 0~9 */
} CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU
 结构说明  : 一个子帧内(4slots)Harq信息
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_RTC3MAC_HARQ_INFO_STRU   astHarqInfo[CTTF_HRPD_MNTN_NUM_SUBFRAME_INFO_INSTANCES];/* sub-frame information instances */
} CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU;

/*****************************************************************************
 结构名    : CTTF_OM_HRPD_MNTN_RTC3MAC_HARQ_REPORT_STRU
 结构说明  : HRPD RTC3MAC Harq信息统计上报
 对应消息  : ID_CTTF_OM_HRPD_MNTN_HARQ_INFO_IND
 说明      : 主动上报消息, 在API调用时用指针指向上报内容即可
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_RTC3MAC_SUBFRAME_HARQ_STRU   astHarqData[CTTF_HRPD_RTC3MAC_MNTN_MAX_RECORD_HARQ];
} CTTF_OM_HRPD_MNTN_RTC3MAC_HARQ_REPORT_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 板侧上报的发送方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* 发送的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* 发送的总字节数（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakRequestCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoredAnNakCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 板侧上报的接收方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* 接收的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* 接收的总字节数（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedNakRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;        /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Default RLP每个实体的统计信息
*****************************************************************************/
typedef  struct
{
    VOS_UINT8            ucStreamId;                    /* 区分RLP实体的唯一编号, 无效值: 0xFF */
    VOS_UINT8            aucReserved[3];                /* 保留字节，按照无效值填写，值为0 */
    VOS_UINT32           ulAnResetRequestCnt;           /* 无效值: 0xFFFFFFFF */
    VOS_UINT32           ulAtResetRequestCnt;           /* 无效值: 0xFFFFFFFF */
    VOS_UINT32           ulRxAnResetAckCnt;             /* 无效值: 0xFFFFFFFF */
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_DEFAULT_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Default RLP的统计信息
 对应消息  : ID_CTTF_OM_HRPD_MNTN_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                       usPrimId;
    VOS_UINT16                                       usToolId;
    CTTF_HRPD_MNTN_PER_DEFAULT_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_DEFAULT_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_DEFAULT_RLP_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MFPA板侧上报的发送方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;   /* 发送的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* 发送的总字节数（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /*（低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakRequestCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoredAnNakCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* 无效值: 0xFFFFFFFF */
}CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MFPA板侧上报的接收方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulTotalByteCntHigh;  /* 接收的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;    /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;   /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;    /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /* （高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;    /* （低32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedNakRequestCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt; /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MFPA每个RLP实体的统计信息
*****************************************************************************/
typedef  struct
{
    VOS_UINT8            ucRlpFlowId;   /* 区分RLP实体的唯一编号, 无效值: 0xFF */
    VOS_UINT8            aucReserved[3]; /* 保留字节，按照无效值填写，值为0 */
    CTTF_HRPD_MNTN_PER_MF_RLP_REV_STATISTICS_STRU  stRevInfo;
    CTTF_HRPD_MNTN_PER_MF_RLP_FWD_STATISTICS_STRU  stFwdInfo;
}CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_MF_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MFPA的可维可测信息
 对应消息  : ID_CTTF_OM_HRPD_MNTN_MFPA_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                  usPrimId;
    VOS_UINT16                                  usToolId;
    CTTF_HRPD_MNTN_PER_MF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_MF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_MF_RLP_STATISTICS_STRU;


/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMPA板侧上报的发送方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSelectRouteBCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCntHigh;   /* 发送的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /* （高32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /* （高32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTxNakReportCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulIgnoreAnNakCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRlpFlushCnt;        /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMPA板侧上报的发送方向的统计
*****************************************************************************/
typedef  struct
{
    VOS_UINT32    ulSelectRouteACnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulSelectRouteBCnt;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCntHigh;   /* 接收的总字节数（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalByteCnt;       /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCntHigh;     /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewByteCnt;         /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCntHigh;    /*（高32bit）无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxByteCnt;        /* （低32bit） 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulDuplicateByteCnt;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulTotalPacketCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNewPacketCnt;       /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRetxPacketCnt;      /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxNakReportCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulNakAbortCnt;        /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAnResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulAtResetRequestCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32    ulRxedAnResetAckCnt;  /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMPA 每个RLP实体的可维可测信息
*****************************************************************************/
typedef  struct
{
    VOS_UINT8                                     ucLinkFlowId;    /* 区分RLP实体的唯一编号, 无效值: 0xFF */
    CTTF_HRPD_PA_MNTN_FLOW_PROTOCOL_ENUM_UINT8    enFlowProtocol;    /* 不支持FlowProtocol时，按照无效值上报，值为0xFF */
    CTTF_HRPD_PA_MNTN_ROUTE_PROTOCOL_ENUM_UINT8   enRouteProtocol;   /* 不支持RouteProtocol时，按照无效值上报，值为0xFF */
    VOS_UINT8                                     aucReserved[1];    /* 保留字节，按照无效值填写，值为0 */
    CTTF_HRPD_MNTN_PER_EMF_RLP_REV_STATISTICS_STRU   stRevInfo;
    CTTF_HRPD_MNTN_PER_EMF_RLP_FWD_STATISTICS_STRU   stFwdInfo;
} CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_MNTN_EMF_RLP_STATISTICS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EMPA的可维可测信息
 对应消息  : ID_CTTF_OM_HRPD_MNTN_EMPA_RLP_STATISTICS_IND
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                                   usPrimId;
    VOS_UINT16                                   usToolId;
    CTTF_HRPD_MNTN_PER_EMF_RLP_STATISTICS_STRU   astRlpEntity[CTTF_HRPD_MNTN_EMF_RLP_MAX_NUM];
} CTTF_OM_HRPD_MNTN_EMF_RLP_STATISTICS_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Acmac可维可测信息统计
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;                   /* C.H1001中subprotocol的值，无效值0xFF */
    VOS_UINT8                               aucReserve[3];                   /* 保留字节，按照无效值填写，值为0xFF */
    VOS_UINT32                              ulSuccAttemptCnt;                /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulMaxProbeFailCnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAdjacentProbeTimerExpiredCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulMailboxFailCnt;                /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulCprocFailCnt;                  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulSndErrorIndCnt;                /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe1Cnt;               /* Access Probe 1成功次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe2Cnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe3Cnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe4Cnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbe5Cnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulAccessProbeAboveCnt;           /* 多于Access Probe 5才成功次数, 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;               /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt;              /* 无效值: 0xFFFFFFFF */
}CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Ccmac可维可测信息统计
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001中subprotocol的值，无效值0xFF */
    VOS_UINT8                               aucReserve[3];      /* 保留字节，按照无效值填写，值为0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulMacLayerPktCnt;   /* 无效值: 0xFFFFFFFF */
}CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RTCMAC可维可测信息统计
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001中subprotocol的值，无效值0xFF */
    CTTF_HRPD_RTCMAC_MNTN_RATE_ENUM_UINT8   enRateLimit;        /* 无效值0xFF  */
    VOS_UINT8                               aucReserve[2];      /* 保留字节，按照无效值填写，值为0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt768BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1536BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt2048BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt3072BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt4096BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt6144BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt8192BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt12288BitCnt;/* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulSndErrorIndCnt;   /* 无效值: 0xFFFFFFFF */
} CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FTCMAC可维可测信息统计
*****************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8  enSubProtocol;      /* C.H1001中subprotocol的值，无效值0xFF */
    VOS_UINT8                               aucReserve[3];      /* 保留字节，按照无效值填写，值为0xFF */
    VOS_UINT32                              ulPhyPkt128BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt256BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt512BitCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt1024BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt2048BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt3072BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt4096BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulPhyPkt5120BitCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotPhyPktCnt;     /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMacLayPktCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotSingUserPktCnt;  /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMultiUserPktCnt; /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulMaxSecLayPktNum;    /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotalMacPacketBytes;      /* MAC Packet Byte Size,不包含2bits MAC trailer；无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotMyAtMacPayloadBytes;   /* 无效值: 0xFFFFFFFF */
    VOS_UINT32                              ulTotOtherAtMacPayloadBytes;/* 无效值: 0xFFFFFFFF */
}CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU;

/*****************************************************************************
 结构名    : CTTF_OM_HRPD_MAC_MNTN_STATISTIC_STRU
 结构说明  : HRPD MAC 信息统计上报
 对应消息  : ID_CTTF_OM_HRPD_MNTN_MAC_PROTOCOL_STATISTICS_IND
 说明      : 主动上报消息, 在API调用时用指针指向上报内容即可
*****************************************************************************/
typedef  struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    CTTF_HRPD_ACMAC_MNTN_STATISTIC_STRU     stAcMac;
    CTTF_HRPD_CCMAC_MNTN_STATISTIC_STRU     stCcMac;
    CTTF_HRPD_RTCMAC_MNTN_STATISTIC_STRU    stRtcMac;
    CTTF_HRPD_FTCMAC_MNTN_STATISTIC_STRU    stFtcMac;
} CTTF_OM_HRPD_MAC_MNTN_STATISTIC_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU
 * Description : DCC和ECC协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*无效值: BUTT */
    CTTF_HRPD_MNTN_CC_STATE_ENUM_UINT8                      enState;            /* 无效值: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU
 * Description : DAC和EAC协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*无效值: BUTT */
    CTTF_HRPD_MNTN_AC_STATE_ENUM_UINT8                      enState;            /* 无效值: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU
 * Description : DFTC和EFTC协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                  enSubProtocol;      /*无效值: BUTT */
    CTTF_HRPD_MNTN_FTC_STATE_ENUM_UINT8                     enState;            /* 无效值: BUTT */
    VOS_UINT8                                               aucReserve[2];      /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU
 * Description : DRTC和ST3 RTC协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_RTC_STATE_ENUM_UINT8                         enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU
 * Description : 鉴权协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU
 * Description : 加密协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU
 * Description : 安全协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_SECURITY_LAYER_PROTOCOL_STATE_ENUM_UINT8     enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU
 * Description : 流控协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_STREAM_FLOW_CTRL_PROTOCOL_STATE_ENUM_UINT8   enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU
 * Description : 流应用协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_STREAM_APP_PROTOCOL_STATE_ENUM_UINT8         enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU
 * Description : SNP协议状态结构
*******************************************************************************/
typedef struct
{
    CTTF_HRPD_MNTN_SUB_PROTOCOL_ENUM_UINT8                      enSubProtocol;  /*无效值: BUTT */
    CTTF_HRPD_MNTN_SNP_UP_TX_STATE_ENUM_UINT8                   enState;        /* 无效值: BUTT */
    VOS_UINT8                                                   aucReserve[2];  /* 保留字节，按照无效值填写，值为0 */
}CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU;

/*******************************************************************************
 * Name        : CTTF_HRPD_MNTN_MODULE_PROTOCOL_STATE_STRU
 * Description : 模块协议状态结构
 * 对应消息  : ID_CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_IND
*******************************************************************************/
typedef struct
{
    VOS_UINT16                                                  usPrimId;
    VOS_UINT16                                                  usToolId;

    CTTF_HRPD_MNTN_MODULE_CC_MAC_PROTOCL_STATE_STRU             stCcMac;
    CTTF_HRPD_MNTN_MODULE_AC_MAC_PROTOCL_STATE_STRU             stAcMac;
    CTTF_HRPD_MNTN_MODULE_FTC_MAC_PROTOCL_STATE_STRU            stFtcMac;
    CTTF_HRPD_MNTN_MODULE_RTC_MAC_PROTOCL_STATE_STRU            stRtcMac;
    CTTF_HRPD_MNTN_MODULE_AUTHENTICATION_PROTOCL_STATE_STRU     stAuth;
    CTTF_HRPD_MNTN_MODULE_ENCRYPTION_PROTOCL_STATE_STRU         stEncryption;
    CTTF_HRPD_MNTN_MODULE_SECURITY_PROTOCL_STATE_STRU           stSecurity;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream0;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream1;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream2;
    CTTF_HRPD_MNTN_MODULE_STREAM_FLOW_CTRL_PROTOCL_STATE_STRU   stStream3;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream0App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream1App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream2App;
    CTTF_HRPD_MNTN_MODULE_STREAM_APP_PROTOCL_STATE_STRU         stStream3App;
    CTTF_HRPD_MNTN_MODULE_SNP_UP_TX_STATE_STRU                  stSnpUplinkTx;
}CTTF_OM_HRPD_MNTN_MODULE_PROTOCOL_STATE_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
#ifndef COMM_ITT
extern VOS_VOID TTF_TraceModuleSet(VOS_UINT8 *paucModuleId);
#endif

extern VOS_VOID TTF_TraceSet(VOS_UINT32 ulOption);     /* L2消息跟踪类型设定接口 */
extern VOS_VOID *TTF_FilterMsgCallBack(MsgBlock *pMsg);
extern VOS_VOID WTTF_TraceModuleCfgReq(VOS_VOID* pMsg);
extern VOS_VOID WTTF_MAC_R99MailBox_ReadForIpcHalt(VOS_VOID);
extern VOS_VOID WTTF_R99MailboxInitForCbt(VOS_VOID);


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

#endif /* end of TtfOamInterface.h */

