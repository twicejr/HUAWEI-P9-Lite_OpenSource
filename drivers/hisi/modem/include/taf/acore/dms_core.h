

#ifndef __DMS_CORE_H__
#define __DMS_CORE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "dms.h"
#include "vos.h"
#if (VOS_OS_VER == VOS_LINUX)
#include "linux/module.h"
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/signal.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <linux/dma-mapping.h>
#include <asm/dma-mapping.h>
#include <asm/io.h>
/*#include <asm/system.h>*/
#include <asm/uaccess.h>
#include <asm/bitops.h>

#include <linux/module.h>
#include <linux/list.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>
#include <linux/moduleparam.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/version.h>

#include <net/netlink.h>
#include <net/sock.h>
#include  <linux/wakelock.h>
#else
#include "Linuxstub.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DMS_WRT_SLEEP_TIME              (50)
#define DMS_RD_SLEEP_TIME               (50)
#define DMS_RD_BUF_LEN                  (1024)

/*lint -e960 修改人:l60609;原因:64bit*/
#define DMS_VFILE_CRT_LEVEL             (0770)
/*lint +e960 修改人:l60609;原因:64bit*/

#define DMS_TEST_MODE                   (0)
#define DMS_NORMAL_MODE                 (1)
#define DMS_PORTCFG_FILE_LEN            (4)

#define DMS_APP_DS_TASK_PRIORITY        (84)

#define DMS_UL_DATA_BUFF_SIZE           (1024)
#define DMS_UL_DATA_BUFF_NUM            (16)

/* slice 值为64bit, 直接用FFFFFFFFFFFFFFFF表示,16个字符+1个结束符 */
#define DMS_GET_SLICE_FILE_LEN          (17)

#if (VOS_OS_VER == VOS_LINUX)
#define DMS_CACHE_FLUSH_WITH_DEV(dev, data, len)      dma_map_single(dev, data, len, DMA_TO_DEVICE)

#define DMS_CACHE_FLUSH(data, len)      dma_map_single(0, data, len, DMA_TO_DEVICE)
#define DMS_CACHE_INVALIDATE(data, len) dma_map_single(0, data, len, DMA_FROM_DEVICE)
#else
#define DMS_CACHE_FLUSH(data, len)      (0x00001)
#define DMS_CACHE_INVALIDATE(data, len) (0x00002)
#define DMS_CACHE_FLUSH_WITH_DEV(dev, data, len)   (0x00003)
#endif

#define DMS_LOG_LEVEL_NONE              (0x00000000)
#define DMS_LOG_LEVEL_INFO              (0x00000001)
#define DMS_LOG_LEVEL_WARNING           (0x00000002)
#define DMS_LOG_LEVEL_ERROR             (0x00000004)
#define DMS_LOG_LEVEL_TOP               (DMS_LOG_LEVEL_INFO | DMS_LOG_LEVEL_WARNING | DMS_LOG_LEVEL_ERROR)

#ifdef _lint
#define DMS_DBG_PRINT(lvl, ...)
#else
#define DMS_DBG_PRINT(lvl, ...)\
            do\
            {\
                if (VOS_FALSE != (g_ulDmsDebugLevel & lvl))\
                {\
                    vos_printf(__VA_ARGS__);\
                }\
            }while(0)
#endif

#define DMS_LOG_INFO(...)               DMS_DBG_PRINT(DMS_LOG_LEVEL_INFO, __VA_ARGS__)
#define DMS_LOG_WARNING(...)            DMS_DBG_PRINT(DMS_LOG_LEVEL_WARNING, __VA_ARGS__)
#define DMS_LOG_ERROR(...)              DMS_DBG_PRINT(DMS_LOG_LEVEL_ERROR, __VA_ARGS__)

#define DMS_NLK_INVALID_PID             (0xFFFFFFFFUL)
#define DMS_NLK_DEFUALT_DATA_SIZE       (NLMSG_DEFAULT_SIZE - sizeof(DMS_NLK_PAYLOAD_STRU))

#define DMS_GET_NLK_ENTITY()                    (&g_stDmsNlkEntity)
#define DMS_GET_NLK_PHY_BEAR_PROP(bear)         (&(g_stDmsNlkEntity.astPhyBearProp[bear]))
#define DMS_GET_NLK_OM_CHAN_PROP(chan)          (&(g_stDmsNlkEntity.astOmChanProp[chan]))

#define DMS_GET_NLK_SOCK()                      (g_stDmsNlkEntity.pstSock)
#define DMS_GET_NLK_DATA_SIZE()                 (g_stDmsNlkEntity.ulDataSize)
#define DMS_GET_NLK_THRESH_SIZE()               (g_stDmsNlkEntity.ulThreshSize)
#define DMS_GET_NLK_PHY_PID(bear)               (g_stDmsNlkEntity.astPhyBearProp[bear].lPid)

#define DMS_GET_NLK_OM_CHAN_DATA_CB_FUNC(chan)  (g_stDmsNlkEntity.astOmChanProp[chan].pDataFunc)
#define DMS_GET_NLK_OM_CHAN_EVT_CB_FUNC(chan)   (g_stDmsNlkEntity.astOmChanProp[chan].pEvtFunc)
#define DMS_GET_NLK_PHY_BEAR(chan)              (g_stDmsNlkEntity.astOmChanProp[chan].enPhyBear)
#define DMS_GET_NLK_MSG_TYPE(chan)              (g_stDmsNlkEntity.astOmChanProp[chan].enMsgType)

/* netlink 套接字事件统计 */
#define DMS_DBG_NLK_CREATE_SOCK_FAIL_NUM(n)     (g_stDmsMntnNlkStats.ulCreatSockFailNum += (n))

/* netlink 上行事件统计 */
#define DMS_DBG_NLK_UL_TOTAL_MSG_NUM(n)         (g_stDmsMntnNlkStats.ulUlTotalMsgNum += (n))
#define DMS_DBG_NLK_UL_ERR_MSG_NUM(n)           (g_stDmsMntnNlkStats.ulUlErrMsgNum += (n))
#define DMS_DBG_NLK_UL_UNSUPPORT_INPUT_LOG_NUM(n) (g_stDmsMntnNlkStats.ulUlUnSupportInputLogNum+= (n))
#define DMS_DBG_NLK_UL_UNSUPPORT_WRITE_LOG_NUM(n) (g_stDmsMntnNlkStats.ulUlUnSupportWriteLogNum+= (n))
#define DMS_DBG_NLK_UL_UNKNOWN_MSG_NUM(n)       (g_stDmsMntnNlkStats.ulUlUnknownMsgNum += (n))
#define DMS_DBG_NLK_UL_SEND_MSG_NUM(type,n)     (g_stDmsMntnNlkStats.aulUlSendMsgNum[type] += (n))
#define DMS_DBG_NLK_UL_FREE_MSG_NUM(type,n)     (g_stDmsMntnNlkStats.aulUlFreeMsgNum[type] += (n))

/* netlink 下行事件统计 */
#define DMS_DBG_NLK_DL_TOTAL_PKT_NUM(n)         (g_stDmsMntnNlkStats.ulDlTotalPktNum += (n))
#define DMS_DBG_NLK_DL_ERR_PARA_PKT_NUM(n)      (g_stDmsMntnNlkStats.ulDlErrParaPktNum += (n))
#define DMS_DBG_NLK_DL_ERR_CHAN_PKT_NUM(n)      (g_stDmsMntnNlkStats.ulDlErrChanPktNum += (n))
#define DMS_DBG_NLK_DL_NORM_CHAN_PKT_NUM(chan,n) (g_stDmsMntnNlkStats.aulDlNormChanPktNum[chan] += (n))
#define DMS_DBG_NLK_DL_TOTAL_MSG_NUM(n)         (g_stDmsMntnNlkStats.ulDlTotalMsgNum += (n))
#define DMS_DBG_NLK_DL_ERR_SOCK_MSG_NUM(n)      (g_stDmsMntnNlkStats.ulDlErrSockMsgNum += (n))
#define DMS_DBG_NLK_DL_ERR_PID_MSG_NUM(n)       (g_stDmsMntnNlkStats.ulDlErrPidMsgNum += (n))
#define DMS_DBG_NLK_DL_ALLOC_MSG_FAIL_NUM(n)    (g_stDmsMntnNlkStats.ulDlAllocMsgFailNum += (n))
#define DMS_DBG_NLK_DL_PUT_MSG_FAIL_NUM(n)      (g_stDmsMntnNlkStats.ulDlPutMsgFailNum += (n))
#define DMS_DBG_NLK_DL_UNICAST_MSG_FAIL_NUM(n)  (g_stDmsMntnNlkStats.ulDlUnicastMsgFailNum += (n))
#define DMS_DBG_NLK_DL_UNICAST_MSG_SUCC_NUM(n)  (g_stDmsMntnNlkStats.ulDlUnicastMsgSuccNum += (n))

#define DMS_SET_PRINT_MODEM_LOG_TYPE(n)         (g_ucDmsPrintModemLogType = (n))
#define DMS_GET_PRINT_MODEM_LOG_TYPE()          (g_ucDmsPrintModemLogType)

#define DMS_MODEM_STATUS_FILE_LEN               (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    DMS_SDM_USB_ENABLE                  = 0,
    DMS_SDM_USB_ENABLE_ERR,
    DMS_SDM_USB_DISABLE,
    DMS_SDM_USB_DISABLE_ERR,

    DMS_SDM_VCOM_OPEN_BEGIN,
    DMS_SDM_VCOM_OPEN_PCUI              = DMS_SDM_VCOM_OPEN_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_OPEN_CTRL              = DMS_SDM_VCOM_OPEN_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_OPEN_PCUI2             = DMS_SDM_VCOM_OPEN_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_OPEN_ERR_BEGIN,
    DMS_SDM_VCOM_OPEN_ERR_PCUI          = DMS_SDM_VCOM_OPEN_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_OPEN_ERR_CTRL          = DMS_SDM_VCOM_OPEN_ERR_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_OPEN_ERR_PCUI2         = DMS_SDM_VCOM_OPEN_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_CLOSE_BEGIN,
    DMS_SDM_VCOM_CLOSE_PCUI             = DMS_SDM_VCOM_CLOSE_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_CLOSE_CTRL             = DMS_SDM_VCOM_CLOSE_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_CLOSE_PCUI2            = DMS_SDM_VCOM_CLOSE_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_CLOSE_ERR_BEGIN,
    DMS_SDM_VCOM_CLOSE_ERR_PCUI         = DMS_SDM_VCOM_CLOSE_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_CLOSE_ERR_CTRL         = DMS_SDM_VCOM_CLOSE_ERR_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_CLOSE_ERR_PCUI2        = DMS_SDM_VCOM_CLOSE_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_EVT_BEGIN,
    DMS_SDM_VCOM_EVT_PCUI               = DMS_SDM_VCOM_EVT_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_EVT_CTRL               = DMS_SDM_VCOM_EVT_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_EVT_PCUI2              = DMS_SDM_VCOM_EVT_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_RD_CB_BEGIN,
    DMS_SDM_VCOM_RD_CB_PCUI             = DMS_SDM_VCOM_RD_CB_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_RD_CB_CTRL             = DMS_SDM_VCOM_RD_CB_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_RD_CB_PCUI2            = DMS_SDM_VCOM_RD_CB_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_RD_CB_SUCC_BEGIN,
    DMS_SDM_VCOM_RD_CB_SUCC_PCUI        = DMS_SDM_VCOM_RD_CB_SUCC_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_RD_CB_SUCC_CTRL        = DMS_SDM_VCOM_RD_CB_SUCC_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_RD_CB_SUCC_PCUI2       = DMS_SDM_VCOM_RD_CB_SUCC_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_RD_CB_ERR_BEGIN,
    DMS_SDM_VCOM_RD_CB_ERR_PCUI         = DMS_SDM_VCOM_RD_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_RD_CB_ERR_CTRL         = DMS_SDM_VCOM_RD_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_RD_CB_ERR_PCUI2        = DMS_SDM_VCOM_RD_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_WRT_BEGIN,
    DMS_SDM_VCOM_WRT_PCUI               = DMS_SDM_VCOM_WRT_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_WRT_CTRL               = DMS_SDM_VCOM_WRT_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_WRT_PCUI2              = DMS_SDM_VCOM_WRT_BEGIN + DMS_PHY_BEAR_USB_PCUI2,
    DMS_SDM_VCOM_WRT_NCM                = DMS_SDM_VCOM_WRT_BEGIN + DMS_PHY_BEAR_USB_NCM,

    DMS_SDM_VCOM_WRT_SUSS_BEGIN,
    DMS_SDM_VCOM_WRT_SUSS_PCUI          = DMS_SDM_VCOM_WRT_SUSS_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_WRT_SUSS_CTRL          = DMS_SDM_VCOM_WRT_SUSS_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_WRT_SUSS_PCUI2         = DMS_SDM_VCOM_WRT_SUSS_BEGIN + DMS_PHY_BEAR_USB_PCUI2,
    DMS_SDM_VCOM_WRT_SUSS_NCM           = DMS_SDM_VCOM_WRT_SUSS_BEGIN + DMS_PHY_BEAR_USB_NCM,

    DMS_SDM_VCOM_WRT_CB_BEGIN,
    DMS_SDM_VCOM_WRT_CB_PCUI            = DMS_SDM_VCOM_WRT_CB_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_WRT_CB_CTRL            = DMS_SDM_VCOM_WRT_CB_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_WRT_CB_PCUI2           = DMS_SDM_VCOM_WRT_CB_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_VCOM_WRT_CB_ERR_BEGIN,
    DMS_SDM_VCOM_WRT_CB_ERR_PCUI        = DMS_SDM_VCOM_WRT_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI,
    DMS_SDM_VCOM_WRT_CB_ERR_CTRL        = DMS_SDM_VCOM_WRT_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_CTRL,
    DMS_SDM_VCOM_WRT_CB_ERR_PCUI2       = DMS_SDM_VCOM_WRT_CB_ERR_BEGIN + DMS_PHY_BEAR_USB_PCUI2,

    DMS_SDM_DBG_INFO_MAX
} DMS_SDM_MSG_ID_ENUM;

/*****************************************************************************
 枚举名称: DMS_NLK_MSG_TYPE_ENUM
 枚举说明: netlink消息类型
*****************************************************************************/
enum DMS_NLK_MSG_TYPE_ENUM
{
    DMS_NLK_MSG_TYPE_LTE_CFG            = 0,                /* TL配置 */
    DMS_NLK_MSG_TYPE_LTE_CTRL,                              /* TL命令 */
    DMS_NLK_MSG_TYPE_LTE_DATA,                              /* TL数据 */
    DMS_NLK_MSG_TYPE_GU_CFG,                                /* GU配置 */
    DMS_NLK_MSG_TYPE_GU_DATA,                               /* GU数据 */

    DMS_NLK_MSG_TYPE_BUTT
};
typedef VOS_UINT32 DMS_NLK_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名称: DMS_NLK_CFG_TYPE_ENUM
 枚举说明: netlink配置类型
*****************************************************************************/
enum DMS_NLK_CFG_TYPE_ENUM
{
    DMS_NLK_CFG_TYPE_OPEN               = 0,                /* 建立netlink */
    DMS_NLK_CFG_TYPE_CLOSE,                                 /* 关闭netlink */

    DMS_NLK_CFG_TYPE_BUTT
};
typedef VOS_UINT32 DMS_NLK_CFG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名称: DMS_NLK_PHY_BEAR_ENUM
 枚举说明: netlink通道类型
*****************************************************************************/
enum DMS_NLK_PHY_BEAR_ENUM
{
    DMS_NLK_PHY_BEAR_LTE                = 0,                /* LTE通道 */
    DMS_NLK_PHY_BEAR_GU,                                    /* GU通道  */

    DMS_NLK_PHY_BEAR_BUTT
};
typedef VOS_UINT32 DMS_NLK_PHY_BEAR_ENUM_UINT32;


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

/* 最后使能的逻辑通道和物理通道的对应关系
 */
typedef struct
{
    DMS_PHY_BEAR_ENUM                   enPhyChan;
    VOS_UINT8                           aucReserved[4];
} DMS_LOGIC_PHY_MATCH_STRU;

/* 物理通道所对应的逻辑属性结构体
 */
typedef struct
{
    UDI_HANDLE                          lPortHandle;
    DMS_LOGIC_CHAN_ENUM                 enLogicChan;
    VOS_UINT8                           ucChanStat;
    VOS_UINT8                           ucHdlcFlag;         /*0 标示非HDLC数据，1表示是HDLC数据*/
    VOS_UINT8                           aucReserved[6];
} DMS_PHY_BEAR_PROPERTY_STRU;


typedef struct
{
    DMS_READ_DATA_PFN                   pfnRdDataCallback;
    DMS_CONNECT_STA_PFN                 pfnConnectCallBack;
    DMS_LOGIC_PHY_MATCH_STRU            stLogicPhy[DMS_CHANNEL_LAST];
    DMS_PHY_BEAR_PROPERTY_STRU          stPhyProperty[DMS_PHY_BEAR_LAST];
    VOS_BOOL                            bPortCfgFlg;
    VOS_BOOL                            bPortOpenFlg;
    VOS_UINT32                          ulPortCfgValue;
    VOS_UINT8                           aucReserved[4];

    struct wake_lock                    stwakelock;
    VOS_UINT8                           aucModemStatus[3];
    VOS_UINT8                           aucReserved1[5];
} DMS_MAIN_INFO;

/*****************************************************************************
 结构名称: DMS_NLK_CFG_STRU
 结构说明: netlink 配置结构
*****************************************************************************/
typedef struct
{
    DMS_NLK_CFG_TYPE_ENUM_UINT32        enCfg;
    VOS_UINT8                           aucReserved[4];
} DMS_NLK_CFG_STRU;

/*****************************************************************************
 结构名称: DMS_NLK_PAYLOAD_STRU
 结构说明: netlink 透明数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;
    VOS_UINT8                           aucReserved[4];
    VOS_UINT8                           aucData[0];
} DMS_NLK_PAYLOAD_STRU;

/*****************************************************************************
 结构名称: DMS_NLK_PHY_BEAR_PROPERTY_STRU
 结构说明: netlink 物理承载属性结构
*****************************************************************************/
typedef struct
{
    VOS_UINT                            lPid;
    VOS_UINT8                           aucReserved[4];
} DMS_NLK_PHY_BEAR_PROPERTY_STRU;

/*****************************************************************************
 结构名称: DMS_NLK_OM_CHAN_PROPERTY_STRU
 结构说明: netlink 逻辑通道属性结构
*****************************************************************************/
typedef struct
{
    DMS_OM_CHAN_DATA_READ_CB_FUNC       pDataFunc;
    DMS_OM_CHAN_EVENT_CB_FUNC           pEvtFunc;
    DMS_NLK_PHY_BEAR_ENUM_UINT32        enPhyBear;
    DMS_NLK_MSG_TYPE_ENUM_UINT32        enMsgType;
} DMS_NLK_OM_CHAN_PROPERTY_STRU;

/*****************************************************************************
 结构名称: DMS_NLK_ENTITY_STRU
 结构说明: netlink 上下文结构
*****************************************************************************/
typedef struct
{
    struct sock                        *pstSock;
    VOS_UINT32                          ulDataSize;
    VOS_UINT32                          ulThreshSize;
    DMS_NLK_PHY_BEAR_PROPERTY_STRU      astPhyBearProp[DMS_NLK_PHY_BEAR_BUTT];
    DMS_NLK_OM_CHAN_PROPERTY_STRU       astOmChanProp[DMS_OM_CHAN_BUTT];
} DMS_NLK_ENTITY_STRU;

/*****************************************************************************
 结构名称: DMS_MNTN_NLK_STATS_STRU
 结构说明: netlink 可维可测结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCreatSockFailNum;

    VOS_UINT32                          ulUlTotalMsgNum;
    VOS_UINT32                          ulUlErrMsgNum;
    VOS_UINT32                          ulUlUnSupportInputLogNum;
    VOS_UINT32                          ulUlUnSupportWriteLogNum;
    VOS_UINT32                          ulUlUnknownMsgNum;
    VOS_UINT32                          aulUlSendMsgNum[DMS_NLK_MSG_TYPE_BUTT];
    VOS_UINT32                          aulUlFreeMsgNum[DMS_NLK_MSG_TYPE_BUTT];

    VOS_UINT32                          ulDlTotalPktNum;
    VOS_UINT32                          ulDlErrParaPktNum;
    VOS_UINT32                          ulDlErrChanPktNum;
    VOS_UINT32                          aulDlNormChanPktNum[DMS_OM_CHAN_BUTT];

    VOS_UINT32                          ulDlTotalMsgNum;
    VOS_UINT32                          ulDlErrSockMsgNum;
    VOS_UINT32                          ulDlErrPidMsgNum;
    VOS_UINT32                          ulDlAllocMsgFailNum;
    VOS_UINT32                          ulDlPutMsgFailNum;
    VOS_UINT32                          ulDlUnicastMsgFailNum;
    VOS_UINT32                          ulDlUnicastMsgSuccNum;

} DMS_MNTN_NLK_STATS_STRU;


/*****************************************************************************
  5 UNION定义
*****************************************************************************/


/*****************************************************************************
  6 全局变量声明
*****************************************************************************/

extern VOS_UINT32                       g_ulDmsDebugLevel;
extern VOS_UINT32                       g_ulNdisCfgFlag ;
extern DMS_DEBUG_AT_SERV_NV_STRU        g_dms_debug_atserv_nv_info;
extern DMS_DEBUG_INFO_TBL_STRU          g_astDmsSdmInfoTable[DMS_SDM_DBG_INFO_MAX];
extern DMS_MAIN_INFO                    g_stDmsMainInfo;
extern pComRecv                         pfnAcmReadData;
extern DMS_NLK_ENTITY_STRU              g_stDmsNlkEntity;
extern DMS_MNTN_NLK_STATS_STRU          g_stDmsMntnNlkStats;
extern VOS_UINT8                       g_ucDmsPrintModemLogType;


/*****************************************************************************
  7 函数声明
*****************************************************************************/

extern VOS_VOID DMS_Debug(DMS_SDM_MSG_ID_ENUM ulType,VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3);
#define DMS_DBG_SDM_FUN(enType,ulRserved1,ulRserved2,ulRserved3)\
            DMS_Debug(enType,ulRserved1,ulRserved2,ulRserved3)

extern VOS_VOID DMS_Init(VOS_VOID);

extern DMS_PHY_BEAR_PROPERTY_STRU* DMS_GetPhyBearProperty(DMS_PHY_BEAR_ENUM enPhyBear);
extern DMS_MAIN_INFO * DMS_GetMainInfo(VOS_VOID);

extern VOS_UINT32 Dms_AtReadData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pDataBuf, VOS_UINT32 ulLen);

extern VOS_VOID DMS_NcmWrtCB (char* pDoneBuff, int status);

VOS_INT DMS_InitPorCfgFile(VOS_VOID);

ssize_t DMS_ReadPortCfgFile(struct file  *file,
                                   char __user  *buf,
                                   size_t        len,
                                   loff_t       *ppos);
ssize_t DMS_WritePortCfgFile(struct file        *file,
                                   const char __user  *buf,
                                   size_t              len,
                                   loff_t             *ppos);

extern VOS_VOID APP_VCOM_SendDebugNvCfg(
    VOS_UINT32                          ulPortIdMask,
    VOS_UINT32                          ulDebugLevel
);

VOS_VOID DMS_ReadPortDebugCfgNV(VOS_VOID);

VOS_UINT32 DMS_NLK_CfgOpen(struct nlmsghdr *pstNlHdr, DMS_NLK_PHY_BEAR_ENUM_UINT32 enBear);
VOS_UINT32 DMS_NLK_CfgClose(struct nlmsghdr *pstNlHdr, DMS_NLK_PHY_BEAR_ENUM_UINT32 enBear);
VOS_VOID DMS_NLK_InitEntity(VOS_VOID);
VOS_VOID DMS_NLK_ProcLteCfgMsg(struct nlmsghdr *pstNlHdr);
VOS_VOID DMS_NLK_ProcGuCfgMsg(struct nlmsghdr *pstNlHdr);
VOS_VOID DMS_NLK_ProcLteCtrlMsg(struct nlmsghdr *pstNlHdr);
VOS_VOID DMS_NLK_ProcLteDataMsg(struct nlmsghdr *pstNlHdr);
VOS_VOID DMS_NLK_ProcGuDataMsg(struct nlmsghdr *pstNlHdr);
VOS_INT DMS_NLK_Send(DMS_NLK_PHY_BEAR_ENUM_UINT32 enPhyBear, DMS_NLK_MSG_TYPE_ENUM_UINT32 enMsgType, VOS_UINT8 *pucData, VOS_UINT32 ulLength);
VOS_VOID DMS_NLK_Input(struct sk_buff *pstSkb);
VOS_INT __init DMS_NLK_Init(VOS_VOID);
VOS_VOID __exit DMS_NLK_Exit(VOS_VOID);


extern VOS_INT DMS_InitGetSliceFile(VOS_VOID);

extern ssize_t DMS_ReadGetSliceFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
);

VOS_INT __init DMS_InitModemStatusFile(VOS_VOID);
ssize_t DMS_ReadModemStatusFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
);

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /*__DMS_CORE_H__ */
