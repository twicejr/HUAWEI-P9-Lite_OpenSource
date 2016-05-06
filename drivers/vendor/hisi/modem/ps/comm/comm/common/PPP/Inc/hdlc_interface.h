/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */


#ifndef __HDLC_INTERFACE_H__
#define __HDLC_INTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "TTFMem.h"
#include "PsTypeDef.h"
#else
#include "ImmInterface.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/chap.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/proto.h"
#endif /* end of VOS_RTOSCK */

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

#if (VOS_RTOSCK == VOS_OS_VER)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 定义PPPC_HDLC_ST_TEST时，把PppcHdlcStTest.c编进来，在单板上运行ST用例，正式版本不定义此宏 */
/* #define PPPC_HDLC_ST_TEST */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
 软、硬件HDLC处理返回结果
*****************************************************************************/
enum PPP_HDLC_RESULT_TYPE_ENUM
{
    PPP_HDLC_RESULT_COMM_FINISH           = 0,      /* 本次处理正常完成 */
    PPP_HDLC_RESULT_COMM_CONTINUE         = 1,      /* 本次处理正常，但还有数据在队列中待下次继续处理，用于限制单次最大处理个数 */
    PPP_HDLC_RESULT_COMM_ERROR            = 2,      /* 本次处理出错 */

    PPP_HDLC_RESULT_BUTT
};
typedef VOS_UINT32   PPP_HDLC_RESULT_TYPE_ENUM_UINT32;

/*****************************************************************************
 PPP数据类型
*****************************************************************************/
enum PPP_DATA_TYPE_ENUM
{
    PPP_PULL_PACKET_TYPE = 1,                       /* IP类型上行数据 */
    PPP_PUSH_PACKET_TYPE,                           /* IP类型下行数据 */
    PPP_PULL_RAW_DATA_TYPE,                         /* PPP类型上行数据 */
    PPP_PUSH_RAW_DATA_TYPE                          /* PPP类型下行数据 */
};
typedef VOS_UINT8   PPP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT16                          usProtocol;
    VOS_UINT8                           aucReserve[4];
    TTF_MEM_ST                         *pstMem;
}HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU;

#else
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NPROTOSTAT                  (13)

extern struct link*                 pgPppLink;

#define PPP_LINK(PppId)             ((pgPppLink + PppId) - 1)
#define PPP_LINK_TO_ID(pLink)       ((pLink - pgPppLink) + 1)

#define LINK_QUEUES(link) (sizeof (link)->Queue / sizeof (link)->Queue[0])
#define LINK_HIGHQ(link) ((link)->Queue + LINK_QUEUES(link) - 1)

#define PPP_HDLC_PROC_AS_FRM_PACKET_IND         (100)

#if (VOS_WIN32 == VOS_OS_VER)
#define PPP_ST_TEST
#define PPP_ONCE_DEAL_MAX_CNT       (2000)
#else
/* 定义PPP_ST_TEST时，把PppStTest.c编进来，在单板上运行ST用例，正式版本不定义此宏 */
#define PPP_ONCE_DEAL_MAX_CNT       (100)
#endif
/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
 软、硬件HDLC处理返回结果
*****************************************************************************/
enum PPP_HDLC_RESULT_TYPE_ENUM
{
    PPP_HDLC_RESULT_COMM_FINISH           = 0,      /* 本次处理正常完成 */
    PPP_HDLC_RESULT_COMM_CONTINUE         = 1,      /* 本次处理正常，但还有数据在队列中待下次继续处理，用于限制单次最大处理个数 */
    PPP_HDLC_RESULT_COMM_ERROR            = 2,      /* 本次处理出错 */

    PPP_HDLC_RESULT_BUTT
};
typedef VOS_UINT32   PPP_HDLC_RESULT_TYPE_ENUM_UINT32;

/*****************************************************************************
 PPP数据类型
*****************************************************************************/
enum PPP_DATA_TYPE_ENUM
{
    PPP_PULL_PACKET_TYPE = 1,                       /* IP类型上行数据 */
    PPP_PUSH_PACKET_TYPE,                           /* IP类型下行数据 */
    PPP_PULL_RAW_DATA_TYPE,                         /* PPP类型上行数据 */
    PPP_PUSH_RAW_DATA_TYPE                          /* PPP类型下行数据 */
};
typedef VOS_UINT8   PPP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头和消息类型定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 软、硬件HDLC处理函数原型，在创建PPP实体的时候，根据需要可以灵活地将
 软件或硬件的实现与该实体关联
*****************************************************************************/
typedef PPP_HDLC_RESULT_TYPE_ENUM_UINT32 (* PPP_HDLC_PROC_DATA_FUNC )
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

/*****************************************************************************
 处理PPP协议栈输出的协议包，需要封装后发给PC，主要在PPP协商期间调用
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC )
(
    struct link *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32 ulPri,
    VOS_UINT16 usProtocol
);

/*****************************************************************************
 处理PPP协议栈输出的协议包，进行封装的处理函数，主要在PPP协商期间调用
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_AS_FRM_PACKET_FUNC )
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);

/*****************************************************************************
 去使能HDLC函数原型，硬件HDLC需要实现此接口，软件不需要
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_DISABLE_FUNC )(VOS_VOID);

struct link {
  VOS_INT32 type;                           /* _LINK type */
  VOS_INT32 len;                            /* full size of parent struct */
  const VOS_CHAR *name;                     /* Points to datalink::name */
  struct {
    unsigned gather : 1;                    /* Gather statistics ourself ? */
    struct pppThroughput total;             /* Link throughput statistics */
    struct pppThroughput *parent;           /* MP link throughput statistics */
  } stats;
  struct ppp_mqueue Queue[2];               /* Our output queue of mbufs */

  VOS_UINT32 proto_in[NPROTOSTAT];          /* outgoing protocol stats */
  VOS_UINT32 proto_out[NPROTOSTAT];         /* incoming protocol stats */

  struct lcp lcp;                           /* Our line control FSM */

  VOS_UINT32 phase;                         /* Curent phase */
  VOS_INT32 timer_state;
  struct ipcp ipcp;
  struct pap  pap;
  struct chap chap;                         /* Authentication using chap, added by liukai */

  struct async async;
  struct hdlc hdlc;

  struct layer const *layer[LAYER_MAX];     /* i/o layers */
  VOS_INT32 nlayers;

  VOS_UINT32 DropedPacketFromGgsn;
};

/*****************************************************************************
 软硬件HDLC配置结构体
*****************************************************************************/
typedef struct _PPP_HDLC_CONFIG_STRU
{
    PPP_HDLC_PROC_DATA_FUNC                 pFunProcData;           /* 指向软件或硬件处理队列数据函数指针 */
    PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC      pFunProcProtocolPacket; /* 指向软件或硬件处理协议栈输出数据函数指针 */
    PPP_HDLC_DISABLE_FUNC                   pFunDisable;            /* 指向软件或硬件功能去使能函数指针 */
    PPP_HDLC_PROC_AS_FRM_PACKET_FUNC        pFunProcAsFrmData;      /* 指向软件或硬件功能以封装方式处理函数指针 */
}PPP_HDLC_CONFIG_STRU;
extern PPP_HDLC_CONFIG_STRU        *g_pstHdlcConfig;

/*****************************************************************************
 协议栈输出协商包消息结构体
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT16                          usProtocol;
    VOS_UINT8                           aucReserve[4];
    PPP_ZC_STRU                        *pstMem;
}HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : PPP_HDLC_ProcIpModeUlData
 功能描述  : IP类型拨号，软件或硬件解封装完成后，调用此接口处理输出数据
 输入参数  : pstLink    -   PPP链路信息
             pstMem     -   解封装后单个输出数据包
             usProto    -   数据包对应的协议
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_ProcIpModeUlData
(
    struct link *pstLink,
    PPP_ZC_STRU *pstMem,
    VOS_UINT16  usProto
);

/*****************************************************************************
 函 数 名  : PPP_HDLC_ProcPppModeUlData
 功能描述  : PPP类型拨号，软件或硬件解封装完成后，调用此接口处理输出数据
 输入参数  : usPppId    -   PPP实体ID
             pstMem     -   解封装后单个输出数据包
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_ProcPppModeUlData
(
    PPP_ID      usPppId,
    PPP_ZC_STRU *pstMem
);


/*****************************************************************************
 函 数 名  : PPP_HDLC_ProcDlData
 功能描述  : 软件或硬件封装完成后，调用此接口处理输出数据
 输入参数  : usPppId    -   PPP实体ID
             pstMem     -   封装后IP包对应的PPP帧数据，整个IP包封装后可能分成多段
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月10日
    作    者   : l00164359
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_HDLC_ProcDlData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem);

#endif /* end of VOS_RTOSCK */

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of hdlc_interface.h */

