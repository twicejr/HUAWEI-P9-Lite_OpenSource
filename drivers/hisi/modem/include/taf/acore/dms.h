

#ifndef __DMS_H__
#define __DMS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "mdrv.h"
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define DMS_LOG_STATIC_BUF_NUM          (16)
#define DMS_LOG_STATIC_ONE_BUF_SIZE     (5120)

#define NVE_AT_SERVER_INDEX             (294)
#define NVE_READ_OPERATE                (1)
#define NVE_WRITE_OPERATE               (0)

/* 通道断开连接通知机制
 */
#define DMS_DISNNECT                    (0)
#define DMS_CONNECT                     (1)

#define DMS_VCOM_OM_CHAN_CTRL           (DMS_OM_CHAN_LTE_CTRL)
#define DMS_VCOM_OM_CHAN_DATA           (DMS_OM_CHAN_LTE_DATA)
#define DMS_VCOM_OM_CHAN_BUTT           (DMS_OM_CHAN_BUTT)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/* 以下的枚举值不能随便修改*/
typedef enum
{
    DMS_PHY_BEAR_BEGIN                 = 0,
    DMS_PHY_BEAR_RESERVE1,
    DMS_PHY_BEAR_RESERVE2,
    DMS_PHY_BEAR_RESERVE3,
    DMS_PHY_BEAR_RESERVE4,
    DMS_PHY_BEAR_RESERVE5,
    DMS_PHY_BEAR_RESERVE6,
    DMS_PHY_BEAR_RESERVE7,
    DMS_PHY_BEAR_USB_PCUI,
    DMS_PHY_BEAR_USB_CTRL,
    DMS_PHY_BEAR_USB_PCUI2,
    DMS_PHY_BEAR_USB_NCM,
    DMS_PHY_BEAR_LAST
} DMS_PHY_BEAR_ENUM;

typedef enum
{
    DMS_CHANNEL_DIAG                    = 0,                /* channel identifier, DIAG */
    DMS_CHANNEL_AT,                                         /* channel identifier, AT */
    DMS_CHANNEL_GU,
    DMS_CHANNEL_LAST
} DMS_LOGIC_CHAN_ENUM;

typedef enum
{
    STATIC_BUF_STA_IDLE                 = 0,
    STATIC_BUF_STA_BUSY,
    STATIC_BUF_STA_BUTT
} DMS_BUF_STATUS_ENUM;

typedef enum
{
    DMS_BUF_TYP_DYMIC                   = 0,
    DMS_BUF_TYP_STATIC,
    DMS_BUF_TYP_BUTT
} DMS_BUF_TYP_ENUM;

enum PDP_STATUS_ENUM
{
    PDP_STATUS_DEACT                    = 0,
    PDP_STATUS_ACT                      = 1,
    PDP_STATUS_BUTT
};
typedef VOS_UINT32 PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名称: DMS_CHAN_EVT_ENUM
 枚举说明: 通道事件枚举
*****************************************************************************/
enum DMS_CHAN_EVT_ENUM
{
    DMS_CHAN_EVT_CLOSE                  = 0,
    DMS_CHAN_EVT_OPEN,

    DMS_CHAN_EVT_BUTT
};
typedef VOS_UINT32 DMS_CHAN_EVT_ENUM_UINT32;

/*****************************************************************************
 枚举名称: DMS_OM_CHAN_ENUM
 枚举说明: 通道类型枚举
*****************************************************************************/
enum DMS_OM_CHAN_ENUM
{
    DMS_OM_CHAN_LTE_CTRL                = 0,
    DMS_OM_CHAN_LTE_DATA,
    DMS_OM_CHAN_GU_DATA,

    DMS_OM_CHAN_BUTT
};
typedef VOS_UINT32 DMS_OM_CHAN_ENUM_UINT32;


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulCalledNum;  /* 调用次数或者消息次数,或者表明该函数是否被调用 */

    VOS_UINT32                          ulRserved1;   /* 表明该位置或者其他,HAL_DIAG_SYS_DEBUG_ENUM决定 */

    VOS_UINT32                          ulRserved2;   /* 表明特殊含义或者其他,HAL_DIAG_SYS_DEBUG_ENUM决定 */

    VOS_UINT32                          ulRserved3;   /* 表明特殊含义或者其他,HAL_DIAG_SYS_DEBUG_ENUM决定 */

    VOS_UINT32                          ulRtcTime;    /* 表明最近执行过的时间 */
} DMS_DEBUG_INFO_TBL_STRU;


typedef struct
{
    VOS_INT32                           lOperatRet;         /* 0:读取成功  -1:读取失败 */
    VOS_UINT32                          ulNvValue;          /* 0:无atserver 1:有atserver */
} DMS_DEBUG_AT_SERV_NV_STRU;


typedef struct
{
    VOS_UINT8                          *pcuBuf;
    DMS_BUF_STATUS_ENUM                 enBusy;
    VOS_UINT8                           aucReserved[4];
} DMS_BUF_STA_STRU;


typedef struct
{
    DMS_BUF_TYP_ENUM                    enBufType;
    VOS_UINT8                           aucReserved[4];
    DMS_BUF_STA_STRU                    stBufSta[DMS_LOG_STATIC_BUF_NUM];
} DMS_STATIC_BUF_STRU;


/* PDP状态上报函数使用的结构体 */
typedef struct
{
    VOS_UINT32                       ulSpeed;             /* 连接速度，单位bps */
    PDP_STATUS_ENUM_UINT32           enActiveSatus;       /* 激活结果，0为成功，其他为失败 */
} NAS_PRO_STRU;


typedef VOS_UINT32 (*DMS_READ_DATA_PFN)(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 * pDataBuf, VOS_UINT32 ulLen);

typedef VOS_VOID (*DMS_CONNECT_STA_PFN)(VOS_UINT8 flag);

typedef int (*USB_NAS_BRK)(void);

typedef int (*USB_NAS_AT_CMD_RECV)(unsigned char *pBuff, unsigned short usLen);

/* 获取当前网络模式CDMA/WCDMA */
typedef unsigned long (*USB_NAS_GET_WWAN_MODE)(void);

typedef int  (*pComRecv)(unsigned char  uPortNo, unsigned char* pData, unsigned short uslength);
/*****************************************************************************
  5 UNION定义
*****************************************************************************/


/*****************************************************************************
  6 全局变量声明
*****************************************************************************/


/*****************************************************************************
  7 函数声明
*****************************************************************************/

#define DMS_COM_STATUS_CALLBACK_REGI(uPortNo,pCallback)   NULL

extern VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback);
#define DMS_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)\
            DMS_ACMRecvFuncReg(pCallback)

extern int DMS_NcmExtFuncReg(USBNdisStusChgFunc connectBrk, USB_NAS_AT_CMD_RECV atCmdRcv);
#define DMS_USB_NAS_REGFUNC(brkFunc, atRecvFunc, getWWANMode)\
            DMS_NcmExtFuncReg(brkFunc, atRecvFunc)

extern VOS_INT32 DMS_WriteData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pucData, VOS_UINT16 usLen);
#define DMS_COM_SEND(uPortNo,pData,uslength)\
            DMS_WriteData(uPortNo,pData,uslength)

extern VOS_INT32 DMS_NcmStatusChangeReg(NAS_PRO_STRU * pPdpStru);
#define DMS_USB_NAS_STATUS_CHANGE(pPdpStru)\
            DMS_NcmStatusChangeReg(pPdpStru)

extern VOS_VOID  Dms_FreeStaticBuf( VOS_UINT8 * buf);
extern VOS_UINT8* Dms_GetStaticBuf(VOS_UINT32 ulLen);
extern VOS_BOOL Dms_IsStaticBuf(VOS_UINT8 *buf);
extern VOS_VOID Dms_StaticBufInit(VOS_VOID);
extern VOS_VOID DMS_NcmProcCbReg(USBNdisStusChgFunc connectBrk,USB_NAS_AT_CMD_RECV atCmdRcv);
extern UDI_HANDLE DMS_GetPortHandle(DMS_PHY_BEAR_ENUM enPhyBear);
extern VOS_UINT32 DMS_VcomPcuiOpen(VOS_VOID);
extern VOS_UINT32 DMS_VcomCtrlOpen(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcui2Open(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcuiClose(VOS_VOID);
extern VOS_UINT32 DMS_VcomCtrlClose(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcui2Close(VOS_VOID);
extern VOS_VOID DMS_VcomPcuiEvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomCtrlEvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomPcui2EvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomPcuiReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomCtrlReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomPcui2ReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomPcuiWrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_VcomCtrlWrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_VcomPcui2WrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_UsbPortReadCB(DMS_PHY_BEAR_ENUM enPhyBear);
extern VOS_VOID DMS_UsbPortWrtCB(DMS_PHY_BEAR_ENUM enPhyBear, VOS_CHAR * pcVirAddr, VOS_CHAR * pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_UsbPortEvtCB(DMS_PHY_BEAR_ENUM enPhyBear, ACM_EVT_E enEvt);

extern VOS_UINT32 DMS_NcmOpen(VOS_VOID);
extern VOS_UINT32 DMS_NcmClose(VOS_VOID);
extern VOS_UINT32 DMS_NcmSendData(VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_UINT32 DMS_VcomWriteAsync(DMS_PHY_BEAR_ENUM enPhyBear ,VOS_UINT8 *pucDataBuf, VOS_UINT32 ulLen);
extern DMS_CONNECT_STA_PFN DMS_GetConnStaFun(VOS_VOID);
extern VOS_VOID DMS_UsbDisableCB(VOS_VOID);
extern VOS_VOID DMS_UsbEnableCB(VOS_VOID);
extern DMS_READ_DATA_PFN DMS_GetDataReadFun(VOS_VOID);
extern VOS_VOID DMS_SetConnStaCB(DMS_CONNECT_STA_PFN pfnReg);

/*****************************************************************************
 函 数 名  : DMS_GetHsicPortStatus
 功能描述  : 获取HSIC口打开状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0-未打开状态;1-打开状态
 ****************************************************************************/
extern VOS_UINT32 DMS_GetHsicPortStatus(VOS_VOID);

extern VOS_VOID DMS_SetNdisChanStatus(ACM_EVT_E enStatus);


typedef VOS_UINT32 (*DMS_OM_CHAN_DATA_READ_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);
typedef VOS_VOID (*DMS_OM_CHAN_EVENT_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_CHAN_EVT_ENUM_UINT32 enEvt);

/*****************************************************************************
 函 数 名  : DMS_RegOmChanDataReadCB
 功能描述  : 注册OM通道数据接收回调
 输入参数  : enChan --- 逻辑通道
             pFunc  --- 函数指针
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanDataReadCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_DATA_READ_CB_FUNC pFunc);


/*****************************************************************************
 函 数 名  : DMS_RegOmChanEventCB
 功能描述  : 注册OM通道事件接收回调
 输入参数  : enChan --- 逻辑通道
             pFunc  --- 函数指针
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanEventCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_EVENT_CB_FUNC pFunc);


/*****************************************************************************
 函 数 名  : DMS_WriteOmData
 功能描述  : 写OM通道数据
 输入参数  : enChan   --- 逻辑通道
             pucData  --- 数据地址
             ulLength --- 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_WriteOmData(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);

VOS_VOID DMS_SetModemStatus(MODEM_ID_ENUM_UINT16 enModemId);
VOS_UINT8 DMS_GetModemStatus(MODEM_ID_ENUM_UINT16 enModemId);
VOS_VOID DMS_InitModemStatus(VOS_VOID);

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*__DMS_H__*/

