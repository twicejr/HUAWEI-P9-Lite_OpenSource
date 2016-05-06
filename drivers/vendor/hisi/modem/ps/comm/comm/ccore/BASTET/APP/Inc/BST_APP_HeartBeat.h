/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_HeartBeat.h
  版 本 号   : 初稿
  作    者   : l00242755
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : 为应用的提供的接口
  函数列表   :
  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BST_APP_HEARTBEAT_H__
#define __BST_APP_HEARTBEAT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "BST_CORE_RegistryDefine.h"
#include "BST_OS_Memory.h"
#include "BST_APP_Define.h"
#include "BST_LIB_String.h"
#include "BST_CORE_NPTask.h"
#include "BST_SRV_AsEvnt.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_HB_MAX_CONFIG_BYTES         ( 128 )

#if ( BST_OS_VER == BST_WIN32 && BST_VER_TYPE == BST_DBG_VER )
#define BST_HB_IsBaseCfged( enFlag )    ( ( ( enFlag ) & ( BST_CFGFLG_ADDR | BST_CFGFLG_CYCL |  BST_CFGFLG_TYPE ) ) \
                                                      == ( BST_CFGFLG_ADDR | BST_CFGFLG_CYCL |  BST_CFGFLG_TYPE ) )
#else
#define BST_HB_IsBaseCfged( enFlag )    ( ( ( enFlag ) & ( BST_CFGFLG_ADDR | BST_CFGFLG_CYCL |  BST_CFGFLG_TYPE | BST_CFGFLG_PRTY ) ) \
                                                      == ( BST_CFGFLG_ADDR | BST_CFGFLG_CYCL |  BST_CFGFLG_TYPE | BST_CFGFLG_PRTY ) )
#endif

#define BST_HB_IsHbSnUsed( HbPktInfo )  ( BST_TRUE == (HbPktInfo)->bSnUsed )
#define BST_HB_DEFAULT_RETRY_TIMES      ( 1 )
#define BST_HB_INVALID_RETRY_TIMES      ( 0 )

#define BST_HB_U32TOU8(d0, d1, d2, d3, ipaddr)     BST_IP_GetU8Addr(d0, d1, d2, d3, ipaddr)

#define BST_HB_IsHbSeqValid( SerNum, HbSnInfo )    ( ( (HbSnInfo)->ulSnBegin <= (HbSnInfo)->ulSnMax )   \
                                                     && ( (HbSnInfo)->ulSnBegin >= (HbSnInfo)->ulSnMin )\
                                                     && ( (SerNum) <= (HbSnInfo)->ulSnMax)              \
                                                     && ( (SerNum) >= (HbSnInfo)->ulSnMin) )
#define BST_HB_CLONE_SOCKET(ErrMsg, RtnPtr )        if ( BST_IsIpBaseCfged ( ulBaseCfged ) ){           \
                                                    (ErrMsg)              = m_pSocket->Clone();         \
                                                    if ( BST_IP_ERR_OK != (ErrMsg) ){                   \
                                                        (RtnPtr)             = BST_NULL_PTR;            \
                                                    }                                                   \
                                                    else                                                \
                                                    {                                                   \
                                                        BST_SetConfigFlag(BST_CFGFLG_CLON);             \
                                                    }                                                   \
                                                    }
#define BST_HB_IsCloned()                           ( BST_IsInfoConfiged(BST_CFGFLG_CLON) )

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : HB_CHECK_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : Modem支持的校验类型
*****************************************************************************/
enum BST_APP_HB_CHECK_TYPE_ENUM
{
    BST_APP_HB_INVALID_CHK_TYPE         = 0,            /* 非法校验类型 */
    BST_APP_HB_NO_CHK_TYPE,                             /* 无校验 */
    BST_APP_HB_CHKSUM_TYPE,                             /* checksum校验 */
    BST_APP_HB_CHKCRC_TYPE,                             /* CRC校验 */
    BST_APP_HB_CHK_TYPE_BUTT
} ;
typedef BST_UINT32                       BST_APP_HB_CHECK_TYPE_ENUM_UINT32;

enum BST_APP_CONN_EST_TYPE_ENUM
{
    BST_APP_CONN_TYPE_AP_ERR_CLS        = 0x00U,
    BST_APP_CONN_TYPE_AP_NORMAL_CLS,
    BST_APP_CONN_TYPE_AP_NORMAL_EST,
    BST_APP_CONN_TYPE_CP_ERR_CLS,
    BST_APP_CONN_TYPE_CP_NORMAL_EST,
    BST_APP_CONN_TYPE_BEST_CONN_POINT   = 0xFFU
} ;
typedef BST_UINT32                       BST_APP_CONN_EST_TYPE_ENUM_UINT32;

/*****************************************************************************
   4 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : SERNO_HB_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义应用心跳包的seq字段
*****************************************************************************/
typedef struct
{
    BST_UINT32                          ulSnBegin;     /* 心跳包seq字段的开始值 */
    BST_UINT32                          ulSnStep;      /* 心跳包seq字段的步长 */
    BST_UINT32                          ulSnMin;       /* 心跳seq字段的最小值  */
    BST_UINT32                          ulSnMax;       /* 心跳seq字段的最大值 */
} SERNO_HB_INFO_STRU;

/*****************************************************************************
 结构名    : HB_PCKT_CONTENT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 应用心跳包的内容
*****************************************************************************/
typedef struct
{
    BST_LIB_StrStru                    *pRespContent;  /* 心跳回复包的内容 */
    BST_LIB_StrStru                    *pFixedContent; /* 心跳包固定字段的内容 */
    BST_LIB_StrStru                    *pCipherKey;    /* 加密码 */
    BST_BOOL                            bSnUsed;       /* 心跳包序号字段是否启用 */
    SERNO_HB_INFO_STRU                 *pstSnInfoPkt;  /* 心跳包seq字段的内容 */
    BST_APP_ENCRP_MODE_ENUM_UINT32      enSecMode;     /* 加密模式 */
    BST_APP_HB_CHECK_TYPE_ENUM_UINT32   enCheckType;   /* 校验类型 */
    BST_UINT16                          usHbPktLength; /* 心跳包的总长度 */
} HB_PCKT_CONTENT_STRU;

/*****************************************************************************
   5 类定义
*****************************************************************************/
class HeartBeat: BST_PUBLIC BST_IP_CNetRcver, BST_PUBLIC BST_CORE_CNPTask,
    BST_PUBLIC BST_OS_CTimerCb, BST_PUBLIC BST_CORE_CAPCCallBack, BST_SRV_CAsRcver
{
BST_PUBLIC:
    HeartBeat( BST_PROCID_T usInProcID, BST_TASKID_T usInTaskID );
    ~HeartBeat( BST_VOID );

BST_PRIVATE:
    BST_BOOL                 InitHeartBeat( BST_VOID );

    BST_BOOL                 InitRegedit( BST_VOID );

    BST_VOID                 Entry( BST_VOID );

    BST_BOOL                 SendHbPkt( BST_VOID );

    BST_IP_ERR_T             Connectd( BST_IP_CSocket *pcSocket );

    BST_IP_PKTPROC_MODE_ENUM Received(
        BST_IP_CSocket             *pcSocket,
        const BST_UINT8            *const pucData,
        const BST_UINT16            usLength );

    BST_VOID                 IpErr (
        BST_IP_CSocket             *pcSocket,
        BST_IP_ERR_T                InIpErrMsg );


    BST_VOID                 Acked (
        BST_IP_CSocket             *pcSocket,
        const BST_UINT32            ulMinNumber,
        const BST_UINT32            ulMaxNumber );

    BST_ERR_ENUM_UINT8       ParsePkt(
        const BST_UINT8            *pucRcvData,
        const BST_UINT16            usLength );

    BST_UINT8               *ComposeHbPkt(
        BST_UINT8                  *pucCmpsData,
        BST_UINT16                 *pusSndLen,
        BST_UINT16                  usCmpsLen );

    BST_BOOL                 IsRespPkt(
        const BST_UINT8            *pucData,
        BST_UINT8                  *pRespData,
        BST_UINT16                  usDataLen,
        BST_UINT16                  usRespLen ) const;

    BST_BOOL                 IsConfigOk( BST_VOID ) const;

    BST_VOID                 TimerExpired(
        BST_OS_TIMERID_T            ulId,
        BST_VOID                   *pvPara );

    BST_UINT16               PidInquired(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usDataSize,
        BST_VOID *const             pData );

    /* 以下接口用于配置AP侧下发的心跳信息 */
    BST_ERR_ENUM_UINT8       PidConfiged(
        BST_CORE_PID_ENUM_UINT16    enParamId,
        BST_UINT16                  usLen,
        const BST_VOID             *const pData,
        BST_UINT32                  ulBaseCfged,
        BST_UINT8                 **pucNewAddr );

    BST_BOOL                 SetSocketInfo( BST_SCKT_TYPE_ENUM_UINT32 enSocketType );

    BST_UINT8               *ConfigType(
        const BST_VOID             *const pData,
        BST_UINT16                  usLen );

    BST_UINT8               *SetHbSnInfo(
        const BST_VOID             *const pData,
        BST_UINT16                  usLen );

    BST_UINT8               *SetCipherKey(
        BST_UINT8                  *pucCipherKey,
        BST_UINT16                  usLength );

    BST_UINT8               *SetEncrypType(
        BST_UINT8                  *pData,
        BST_UINT16                  usLen );

    BST_UINT8               *SetCheckType(
        BST_UINT8                  *pData,
        BST_UINT16                  usLen );

    BST_UINT8               *SetFixedContent(
        BST_UINT8                  *pucFixContent,
        BST_UINT16                  usFixLength );

    BST_UINT8               *SetRespContent(
        BST_UINT8                  *pucRespContent,
        BST_UINT16                  usRespLength );

    BST_UINT8               *SetAppTxRetry(
        const BST_VOID             *const pData,
        BST_UINT16                  usLen );

    BST_VOID                RxAnsTimerProc(
        BST_VOID                   *pvPara );

    BST_SRV_CHNL_LINK_STRU *GetChnlInstance( BST_VOID );

    BST_VOID                ChnlCtrlClose( BST_VOID );

    BST_VOID                ChnlCtrlClear( BST_VOID );

    BST_VOID                ChnlCtrlSend(
        BST_SRV_CHNL_HEAD_STRU     *pstPktItem );

    BST_VOID                ChnlCtrlTimerProc(
        BST_VOID                    *pvPara );

    BST_VOID                ReBuildLink( BST_UINT32 ulNeedReport );

    BST_VOID                AsEventCallback(
        BST_AS_EVT_ENUM_UINT32    enEvent,
        BST_UINT32                ulLength,
        BST_VOID                 *pvData );
    /**
     *重构PTASK 接口
     */
    BST_VOID                onCycleError ( BST_VOID );
    BST_VOID                onUpdateCycle(
        BST_UINT16                  ulDetCycle );


    BST_TASK_STATE_ENUM_UINT8       ProcEstState(
        BST_APP_CONN_EST_TYPE_ENUM_UINT32 enNewSta );

    HB_PCKT_CONTENT_STRU           *m_pstHbPktContent;
    BST_UINT32                      m_ulHbSerNum;
    TX_HB_RETRY_TIMER_STRU          m_stHbTxRetry;
    BST_OS_TIMERID_T                m_ChnlTimerId;
    BST_SRV_CHNL_LINK_STRU         *m_pstChnlLinker;
    /*
     * Start/Stop功能，是代表整个托管开关是否运行，可以控制心跳、链路重建所有功能
     * 心跳的启停，可以采用心跳周期为0判断
     * 托管重联的启动与否，受到PID控制:BST_PID_LH_RELINK_ENABLE
     */
    BST_UINT32                      m_ulConnEstState;
    BST_UINT32                      m_ulIsReLinkEn;     /* 重联是否允许 */
    BST_UINT32                      m_ulIsDetector;     /* 当前任务是否为探测器 */
};

/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
