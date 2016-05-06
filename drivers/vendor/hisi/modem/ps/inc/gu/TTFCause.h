/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : TTFCause.h
  Version     : V200R001
  Date        : 2005-06-16
  Description : TTF组使用的公共头文件
  History     :
  1. Date:2005-06-16
     Author: w29695,z47725
     Modification:Create
  2.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
*******************************************************************************/
#ifndef __TTF_CAUSE_H__
#define __TTF_CAUSE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#include "vos.h"


/*******************************************************************************
宏定义
说明:这里的错误范围从0x0000到0x0FFF
*******************************************************************************/
/*公共错误原因*/
#define TTF_CAUSE_INPUT_PARAMS          0x0101      /*输入参数错误*/
#define TTF_CAUSE_STATE                 0x0102      /*收到消息的处理状态错误*/


/*系统错误原因*/
#define TTF_CAUSE_MEM_OVERLOAD          0x0201      /*内存超过配置限制*/
#define TTF_CAUSE_MEM_ALLOC             0x0202      /*系统函数ALLOC失败*/

#define TTF_CAUSE_QUEUE_NOTEMPTY        0x0203      /*队列不空*/


/*SN与LLC共用的失败原因*/
#define SN_CAUSE_INVALID_XID_RSP        0x0301      /*Cause "invalid XID response"*/
#define SN_CAUSE_INVALID_XID_CMD        0x0302      /*Cause "invalid XID command"*/
#define SN_CAUSE_NO_PEER_RSP            0x0303      /*Cause "no peer response"*/
#define SN_CAUSE_NORMAL_REL             0x0304      /*Cause "normal release"*/
#define SN_CAUSE_DM_RCV                 0x0305      /*Cause "DM received"*/
#define SN_CAUSE_OTHER                  0x0306      /*Cause "other cause"*/

/*LLC自己增加的可维可测信息*/
#define SN_CAUSE_LL_NU_OUT_OFF_ORDER    0x0307      /*Cause "NU out of order"*/

#define SN_CAUSE_LL_RCV_RNR             0x0308      /*Cause "LL receive RNR frame"*/
#define SN_CAUSE_LL_RCV_ACK             0x0309      /*Cause "LL receive ACK frame"*/
#define SN_CAUSE_LL_RCV_SACK            0x030A      /*Cause "LL receive SACK frame"*/
#define SN_CAUSE_LL_RCV_FRMR            0x030B      /*Cause "LL receive FRMR frame"*/
#define SN_CAUSE_LL_SND_RNR             0x030C      /*Cause "LL send RNR frame"*/
#define SN_CAUSE_LL_SND_ACK             0x030D      /*Cause "LL send ACK frame"*/
#define SN_CAUSE_LL_SND_SACK            0x030E      /*Cause "LL send SACK frame"*/
#define SN_CAUSE_LL_SND_FRMR            0x030F      /*Cause "LL send FRMR frame"*/

#define SN_CAUSE_LL_RCV_SABM            0x0310      /*Cause "LL receive SABM frame"*/
#define SN_CAUSE_LL_RCV_DISC            0x0311      /*Cause "LL receive DISC frame"*/
#define SN_CAUSE_LL_RCV_UA              0x0312      /*Cause "LL receive UA frame"*/
#define SN_CAUSE_LL_RCV_DM              0x0313      /*Cause "LL receive DM frame"*/
#define SN_CAUSE_LL_RCV_XID             0x0314      /*Cause "LL receive XID frame"*/
#define SN_CAUSE_LL_SND_SABM            0x0315      /*Cause "LL send SABM frame"*/
#define SN_CAUSE_LL_SND_DISC            0x0316      /*Cause "LL send DISC frame"*/
#define SN_CAUSE_LL_SND_UA              0x0317      /*Cause "LL send UA frame"*/
#define SN_CAUSE_LL_SND_DM              0x0318      /*Cause "LL send DM frame"*/
#define SN_CAUSE_LL_SND_XID             0x0319      /*Cause "LL send XID frame"*/
#define SN_CAUSE_LL_CHK_PARAM_FAIL      0x031A      /*检查参数错误*/
#define SN_CAUSE_LL_CIPH_FAIL           0x031B      /*加解密错误"*/
#define SN_CAUSE_LL_LEN_Exceed_N201U    0x031C      /*帧长度超过N201-U"*/

/*******************************************************************************
结构定义
*******************************************************************************/
#pragma pack(4)


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*******************************************************************************
向外提供的函数声明
*******************************************************************************/



/******************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif





