

#ifndef __RNICDEBUG_H__
#define __RNICDEBUG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "product_config.h"
#include "RnicLinuxInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define RNIC_DBG_NET_TX_RMNETID_ERR_NUM(n)          (g_stRnicMntnStats.ulNetTxRmNetIdErrNum += (n))
#define RNIC_DBG_SPE_TX_PORTID_ERR_NUM(n)           (g_stRnicMntnStats.ulSpeTxPortIdErrNum += (n))

/* 上行统计信息 */
#define  RNIC_DBG_RECV_UL_IPV4_PKT_NUM(n, index)       (g_astRnicStats[index].ulUlRecvIpv4PktNum += (n))
#define  RNIC_DBG_RECV_UL_IPV6_PKT_NUM(n, index)       (g_astRnicStats[index].ulUlRecvIpv6PktNum += (n))
#define  RNIC_DBG_RECV_UL_IPV4V6_PKT_NUM(n, index)     (g_astRnicStats[index].ulUlRecvIpv4v6PktNum += (n))
#define  RNIC_DBG_RECV_UL_UNDIAL_PKT_NUM(n, index)     (g_astRnicStats[index].ulUlRecvUndiaPktNum += (n))
#define  RNIC_DBG_SEND_UL_PKT_NUM(n, index)            (g_astRnicStats[index].ulUlSendPktNum += (n))
#define  RNIC_DBG_SEND_UL_PKT_FAIL_NUM(n, index)       (g_astRnicStats[index].ulUlSendPktFailNum += (n))
#define  RNIC_DBG_UL_RECV_IPV4_BROADCAST_NUM(n, index) (g_astRnicStats[index].ulUlIpv4BrdcstPktNum += (n))
#define  RNIC_DBG_UL_CHANGE_IMMZC_FAIL_NUM(n, index)   (g_astRnicStats[index].ulUlImmzcFailPktNum += (n))
#define  RNIC_DBG_UL_RMV_MAC_HDR_FAIL_NUM(n, index)    (g_astRnicStats[index].ulUlRmvMacHdrFailPktNum += (n))
#define  RNIC_DBG_NETCAED_UL_DISCARD_NUM(n, index)     (g_astRnicStats[index].ulUlNetCardDiscardNum += (n))
#define  RNIC_DBG_FLOW_CTRL_UL_DISCARD_NUM(n, index)   (g_astRnicStats[index].ulUlFlowCtrlDiscardNum += (n))
#define  RNIC_DBG_RECV_UL_ERR_PKT_NUM(n, index)        (g_astRnicStats[index].ulUlRecvErrPktNum += (n))
#define  RNIC_DBG_RAB_ID_ERR_NUM(n, index)             (g_astRnicStats[index].ulUlRabIdErr += (n))
#define  RNIC_DBG_SEND_APP_DIALUP_SUCC_NUM(n, index)   (g_astRnicStats[index].ulUlSendAppDialUpSucc += (n))
#define  RNIC_DBG_SEND_APP_DIALUP_FAIL_NUM(n, index)   (g_astRnicStats[index].ulUlSendAppDialUpFail += (n))
#define  RNIC_DBG_SEND_APP_DIALDOWN_SUCC_NUM(n, index) (g_astRnicStats[index].ulUlSendAppDialDownSucc += (n))
#define  RNIC_DBG_SEND_APP_DIALDOWN_FAIL_NUM(n, index) (g_astRnicStats[index].ulUlSendAppDialDownFail += (n))
#define  RNIC_DBG_NET_ID_UL_DISCARD_NUM(n, index)      (g_astRnicStats[index].ulUlNetIdDiscardNum += (n))
#define  RNIC_DBG_MODEM_ID_UL_DISCARD_NUM(n, index)    (g_astRnicStats[index].ulUlModemIdDiscardNum += (n))
#define  RNIC_DBG_PDN_ID_ERR_NUM(n, index)             (g_astRnicStats[index].ulUlPdnIdErr += (n))

/* 下行统计信息 */
#define  RNIC_DBG_RECV_DL_IPV4_PKT_NUM(n, index)       (g_astRnicStats[index].ulDlRecvIpv4PktNum += (n))
#define  RNIC_DBG_RECV_DL_IPV6_PKT_NUM(n, index)       (g_astRnicStats[index].ulDlRecvIpv6PktNum += (n))
#define  RNIC_DBG_SEND_DL_PKT_NUM(n, index)            (g_astRnicStats[index].ulDlSendPktNum += (n))
#define  RNIC_DBG_SEND_DL_PKT_FAIL_NUM(n, index)       (g_astRnicStats[index].ulDlSendPktFailNum += (n))
#define  RNIC_DBG_RECV_DL_BIG_PKT_NUM(n, index)        (g_astRnicStats[index].ulDlRecvBigPktNum += (n))
#define  RNIC_DBG_DISCARD_DL_PKT_NUM(n, index)         (g_astRnicStats[index].ulDlDiscardPktNum += (n))
#define  RNIC_DBG_ADD_DL_MACHEAD_FAIL_NUM(n, index)    (g_astRnicStats[index].ulDlAddMacHdFailNum += (n))
#define  RNIC_DBG_NETCAED_DL_DISCARD_NUM(n, index)     (g_astRnicStats[index].ulDlNetCardDiscardNum += (n))
#define  RNIC_DBG_RECV_DL_ERR_PKT_NUM(n, index)        (g_astRnicStats[index].ulDlRecvErrPktNum += (n))
#define  RNIC_DBG_NETID_DL_DISCARD_NUM(n, index)       (g_astRnicStats[index].ulDlNetIdDiscardNum += (n))

#define RNIC_DBG_SET_SEM_INIT_FLAG(flag)               (g_astRnicStats[0].ulSemInitFlg = (flag))
#define RNIC_DBG_SAVE_BINARY_SEM_ID(sem_id)            (g_astRnicStats[0].hBinarySemId = (sem_id))
#define RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)         (g_astRnicStats[0].ulCreateBinarySemFailNum += (n))
#define RNIC_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)           (g_astRnicStats[0].ulLockBinarySemFailNum += (n))
#define RNIC_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)      (g_astRnicStats[0].ulLastBinarySemErrRslt = (rslt))
#define RNIC_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)        (g_astRnicStats[0].ulResetSucessNum += (n))

#define RNIC_DBG_CONFIGCHECK_ADD_TOTLA_NUM()            (g_stRnicRmnetConfigCheckInfo.ucTotlaCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_MODEMTYPE_ERR_NUM()    (g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_IPTYPE_ERR_NUM()       (g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_MODEMID_ERR_NUM()      (g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_PDNID_ERR_NUM()        (g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RABID_ERR_NUM()        (g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RMNETID_ERR_NUM()      (g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_RMNETSTATUS_ERR_NUM()  (g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_SND_ERR_NUM()          (g_stRnicRmnetConfigCheckInfo.ucSendErrCnt++)
#define RNIC_DBG_CONFIGCHECK_ADD_SUCC_NUM()             (g_stRnicRmnetConfigCheckInfo.ucSuccCnt++)

#define RNIC_DBG_PRINT_UL_DATA(skb) \
            if (VOS_TRUE == g_ulRnicPrintUlDataFlg) \
            { \
                RNIC_ShowDataFromIpStack(skb); \
            }

#if (VOS_OS_VER == VOS_LINUX)
#define RNIC_DEV_ERR_PRINTK(pcString)     printk(KERN_ERR "%s", pcString);
#else
#define RNIC_DEV_ERR_PRINTK(pcString)     PS_PRINTF("%s", pcString);
#endif


/*****************************************************************************
  3 枚举定义
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

typedef struct
{
    VOS_UINT32                          ulNetTxRmNetIdErrNum;
    VOS_UINT32                          ulSpeTxPortIdErrNum;

} RNIC_MNTN_STATS_STRU;

/*****************************************************************************
 结构名    : RNIC_STATS_INFO_STRU
 结构说明  : RNIC统计量
  1.日    期   : 2012年1月20日
    作    者   : S62952
    修改内容   : 创建文件
*****************************************************************************/
typedef struct
{
    /* 上行统计信息 */
    VOS_UINT32              ulUlRecvIpv4PktNum;                                 /* RNIC收到上行IPV4数据的个数 */
    VOS_UINT32              ulUlRecvIpv6PktNum;                                 /* RNIC收到上行IPV6数据的个数 */
    VOS_UINT32              ulUlRecvIpv4v6PktNum;                               /* IPV4V6类型激活时RNIC收到上行数据的个数(IPV4、IPV6) */
    VOS_UINT32              ulUlRecvUndiaPktNum;                                /* RNIC未激活时收到上行数据的个数 */
    VOS_UINT32              ulUlSendPktNum;                                     /* RNIC上行发送给ADS数据的个数 */
    VOS_UINT32              ulUlSendPktFailNum;                                 /* RNIC调ADS发送上行数据失败的个数 */
    VOS_UINT32              ulUlIpv4BrdcstPktNum;                               /* RNIC未拨上号前上行收到IPV4广播包的个数 */
    VOS_UINT32              ulUlImmzcFailPktNum;                                /* RNIC上行转换为IMM_ZC失败的个数 */
    VOS_UINT32              ulUlRmvMacHdrFailPktNum;                            /* RNIC上行去除MAC头失败的个数 */
    VOS_UINT32              ulUlNetCardDiscardNum;                              /* RNIC网卡私有数据错误丢掉上行数据包的个数 */
    VOS_UINT32              ulUlFlowCtrlDiscardNum;                             /* RNIC网卡流控丢掉上行数据包的个数 */
    VOS_UINT32              ulUlRecvErrPktNum;                                  /* RNIC收到错误数据包的个数(非ipv4、ipv6包) */
    VOS_UINT32              ulUlSendAppDialUpSucc;                              /* RNIC成功上报APP按需拨号 */
    VOS_UINT32              ulUlSendAppDialUpFail;                              /* RNIC上报APP按需拨号失败 */
    VOS_UINT32              ulUlSendAppDialDownSucc;                            /* RNIC成功上报APP断开拨号 */
    VOS_UINT32              ulUlSendAppDialDownFail;                            /* RNIC上报APP断开拨号失败 */
    VOS_UINT32              ulUlRabIdErr;                                       /* Rab id错误 */
    VOS_UINT32              ulUlNetIdDiscardNum;                                /* RNIC网卡ID错误丢掉上行数据包的个数 */
    VOS_UINT32              ulUlModemIdDiscardNum;                              /* RNIC Modem ID错误丢掉上行数据包的个数 */

    /* 下行统计信息 */
    VOS_UINT32              ulDlRecvIpv4PktNum;                                 /* RNIC收到下行IPV4数据的个数 */
    VOS_UINT32              ulDlRecvIpv6PktNum;                                 /* RNIC收到下行IPV6数据的个数 */
    VOS_UINT32              ulDlSendPktNum;                                     /* RNIC发送下行数据的个数 */
    VOS_UINT32              ulDlSendPktFailNum;                                 /* RNIC发送下行数据失败的个数 */
    VOS_UINT32              ulDlRecvBigPktNum;                                  /* RNIC收到下行数据包大于MTU的个数 */
    VOS_UINT32              ulDlDiscardPktNum;                                  /* RNIC网卡未激活丢弃的数据个数 */
    VOS_UINT32              ulDlAddMacHdFailNum;                                /* RNIC下行加MAC头失败的个数 */
    VOS_UINT32              ulDlNetCardDiscardNum;                              /* RNIC网卡私有数据错误丢掉下行数据包的个数 */
    VOS_UINT32              ulDlRecvErrPktNum;                                  /* RNIC收到错误数据包的个数(非ipv4、ipv6包) */
    VOS_UINT32              ulDlNetIdDiscardNum;                                /* RNIC网卡ID错误丢掉下行数据包的个数 */
    VOS_UINT8               aucReserved[4];

    /* 复位信号量信息 */
    VOS_SEM                 hBinarySemId;                                       /* 二进制信号量ID */
    VOS_UINT32              ulSemInitFlg;                                       /* 初始化标识, VOS_TRUE: 成功; VOS_FALSE: 失败 */
    VOS_UINT32              ulCreateBinarySemFailNum;                           /* 创建二进制信号量失败次数 */
    VOS_UINT32              ulLockBinarySemFailNum;                             /* 锁二进制信号量失败次数 */
    VOS_UINT32              ulLastBinarySemErrRslt;                             /* 最后一次锁二进制信号量失败结果 */
    VOS_UINT32              ulResetSucessNum;                                   /* C核复位成功的次数 */

    VOS_UINT32              ulUlPdnIdErr;                                       /* Pdn id错误 */
}RNIC_STATS_INFO_STRU;

/* Added by m00217266 for L-C互操作项目, 2014-2-19, begin */
/*****************************************************************************
 结构名    : RNIC_RMNET_CONFIG_CHECK_INFO_STRU
 结构说明  : RNIC 网卡配置检验信息统计
  1.日    期   : 2014年2月19日
    作    者   : m00217266
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotlaCnt;
    VOS_UINT8                           ucModemTypeErrCnt;
    VOS_UINT8                           ucRmNetIdErrCnt;
    VOS_UINT8                           ucModemIdErrCnt;
    VOS_UINT8                           ucPdnIdErrCnt;
    VOS_UINT8                           ucRabIdErrCnt;
    VOS_UINT8                           ucRmnetStatusErrCnt;
    VOS_UINT8                           ucIpTypeErrCnt;
    VOS_UINT8                           ucSendErrCnt;
    VOS_UINT8                           ucSuccCnt;
}RNIC_RMNET_CONFIG_CHECK_INFO_STRU;

/* Added by m00217266 for L-C互操作项目, 2014-2-19, end */

/*****************************************************************************
  8 全局变量声明
*****************************************************************************/

extern RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats;
extern RNIC_STATS_INFO_STRU                    g_astRnicStats[];
extern RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
extern VOS_UINT32                              g_ulRnicPrintUlDataFlg;
extern VOS_UINT32                              g_ulRnicPrintDlDataFlg;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
);

VOS_VOID RNIC_ShowResetStats(VOS_VOID);
VOS_VOID RNIC_Help(VOS_VOID);


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

#endif /* end of AdsTest.h */

