
 
#ifndef __PSMUX_H__
#define __PSMUX_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "TTFUtil.h"
#include    "AtMuxInterface.h"
#include    "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MUX_DLCI_PAYLOAD_LEN_MAX        (1852)      /*最大的帧内数据长度*/

#define MUX_DLCI_ID_OFFSET              (1)         /* 当前DLCI的定义是1到16, 因此有一个1的偏移量 */

#define MUX_FRAME_FLAG                  (0XF9)      /*Mux帧的起始和结束标志符*/

#define MUX_CONTROL_UIH                 (0xEF)

#define MUX_FRAME_LEN_0                 (0)
#define MUX_FRAME_LEN_1                 (1)
#define MUX_FRAME_LEN_2                 (2)
#define MUX_FRAME_LEN_3                 (3)
#define MUX_FRAME_LEN_4                 (4)
#define MUX_FRAME_LEN_5                 (5)
#define MUX_FRAME_LEN_6                 (6)
#define MUX_FRAME_LEN_7                 (7)
#define MUX_FRAME_LEN_8                 (8)

#define MUX_FRAME_LEN_128               (128)


/* 获取ADS下行RAB INFO地址 */
#define MUX_AT_UL_GET_DLCI_INFO_PTR(Dlci)           (&(g_stMuxAtUlDlciInfo[Dlci - MUX_DLCI_ID_OFFSET]))

/* 获取MUX上行数据回调函数指针 */
#define MUX_AT_UL_DLCI_GET_DATA_CALLBACK_FUNC(Dlci) (MUX_AT_UL_GET_DLCI_INFO_PTR(Dlci)->pRcvUlDlciDataFunc)

/*获得接收时组帧用相关参数*/
#define MUX_GET_UL_RX_STAT()                        (&g_stMuxUnframeState.ucUnframeState)
#define MUX_GET_UL_RX_BUFF()                        (g_stMuxUnframeState.pUnframeBuf)
#define MUX_GET_UL_RX_HEAD()                        (g_stMuxUnframeState.aucHeadBuff)
#define MUX_GET_UL_RX_LEN()                         (&g_stMuxUnframeState.usLeftInfoLen)

/*获得接收缓冲*/
#define MUX_GET_RX_Q_ADDR()                         (&(g_stMuxUlQue))


#define MUX_SET_116_BIT(a,b,c)     (VOS_UINT8)(((VOS_UINT8)((a) & 0x01)) \
                                    | ((VOS_UINT8)(((b) << 1) & 0x02)) \
                                    | ((VOS_UINT8)(((c) << 2) & 0xFC)))

#define MUX_GET_116_BIT(uc, b)      (b) = (VOS_UINT8)(((uc) & 0xFC)>>2);

#define MUX_SET_17_BIT(a,b)         (VOS_UINT8)(((VOS_UINT8)((a) & 0x01) ) \
                                    |(VOS_UINT8)(((b) << 1) & 0xFE))

#define MUX_GET_17_BIT(uc, a, b)    (a) = ((VOS_UINT8)(uc) & 0x01);\
                                    (b) = (VOS_UINT8)(((uc) & 0xFE)>>1);


/*下行统计信息*/
#define  MUX_DBG_DL_SEND_SUCC_PKT_NUM(n)            (g_stMuxStaticInfo.ulSuccSendDlPacketNums += (n))
#define  MUX_DBG_DL_SEND_FAIL_PKT_NUM(n)            (g_stMuxStaticInfo.ulFailSendDlPacketNums += (n))
#define  MUX_DBG_DL_FREE_PKT_NUM(n)                 (g_stMuxStaticInfo.ulFreeDlPacketNums += (n))


/*上行统计信息*/
#define  MUX_DBG_UL_SEND_SUCC_PKT_NUM(n)            (g_stMuxStaticInfo.ulSuccSendUlPacketNums += (n))
#define  MUX_DBG_UL_SEND_FAIL_PKT_NUM(n)            (g_stMuxStaticInfo.ulFailSendUlPacketNums += (n))
#define  MUX_DBG_UL_GET_SUCC_PKT_NUM(n)             (g_stMuxStaticInfo.ulSuccGetUlPacketNums += (n))
#define  MUX_DBG_UL_DISCARD_PKT_NUM(n)              (g_stMuxStaticInfo.ulDiscardUlPacketNums += (n))
#define  MUX_DBG_UL_CALLBACK_FAIL_NUM(n)            (g_stMuxStaticInfo.ulGetDataFailNums += (n))
#define  MUX_DBG_GET_INVALID_UDI_HANDLE_NUM(n)      (g_stMuxStaticInfo.ulInvalidUdiHandleNums += (n))


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 可维可测使用消息 */
typedef enum
{
    ID_MUX_TRACE_UL_DATA                   = 0x1001,   /* 上行数据勾包 */
    ID_MUX_TRACE_DL_DATA                   = 0x1002,   /* 下行数据勾包 */
    ID_MUX_TRACE_TYPE_BUTT
}MUX_TRACE_MSG_TYPE_ENUM;
typedef VOS_UINT32 MUX_TRACE_MSG_TYPE_ENUM_UINT32;

/*接收数据状态*/
typedef enum
{
    MUX_DLCI_UNFRAME_STATE_FNDING_F9        = 0,
    MUX_DLCI_UNFRAME_STATE_FNDING_ADDR,
    MUX_DLCI_UNFRAME_STATE_FNDING_CTRL,
    MUX_DLCI_UNFRAME_STATE_FNDING_LEN1,
    MUX_DLCI_UNFRAME_STATE_FNDING_LEN2,
    MUX_DLCI_UNFRAME_STATE_FNDING_INFO,
    MUX_DLCI_UNFRAME_STATE_FNDING_FCS,
    MUX_DLCI_UNFRAME_STATE_FNDING_EOF,
    MUX_DLCI_UNFRAME_STATE_FNDING_BUTT
}MUX_DLCI_UNFRAME_STATE_FNDING_ENUM;
typedef VOS_UINT8 MUX_DLCI_UNFRAME_STATE_FNDING_ENUM_UINT8;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*帧头部格式*/
typedef struct
{
    VOS_UINT8               ucStartFlag;        /*0x9F*/
    VOS_UINT8               ucAddr;             /*bit:1,1,6 EA/CR/DLCI
                                                EA:固定为1表示为最后一个字段
                                                CR:command or response 回复为回填，
                                                初始发送填写为APP:1 PS:0*/
    VOS_UINT8               ucControl;          /*帧类型*/
    VOS_UINT8               ucLen1;             /*bit:1,7 EA/LEN
                                                EA:表示为最后一个字段，0表示还有一个字段*/
    VOS_UINT8               ucLen2;             /*如果一个字节无法表示长度，
                                                则该字段表示长度的低字节*/
    VOS_UINT8               ucRsv[3];           /*保留*/
} MUX_FRAME_HEAD;


/*Mux接收对应状态结构*/
typedef struct
{
    VOS_UINT8               ucUnframeState;     /* 解帧状态 */
    VOS_UINT8               aucHeadBuff[5];     /* 用来存放数据头部的数据缓冲*/
    VOS_UINT16              usLeftInfoLen;      /* 未接收的信息域长度 */
    TTF_MBUF_ST            *pUnframeBuf;        /* 接收帧的缓冲 */
} MUX_UNFRAME_STATE_ST;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
结构名    : MUX_AT_UL_DLCI_INFO_STRU
结构说明  : MUX上行DLCI信息管理

  1.日    期   : 2011年8月10日
    作    者   : h00163499
    修改内容   : 定义MUX上行DLCI信息管理
*****************************************************************************/
typedef struct
{
    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;                                 /* 链路号 */
    VOS_UINT8                           aucRsv[3];                              /* 保留 */
    RCV_UL_DLCI_DATA_FUNC               pRcvUlDlciDataFunc;                     /* 对应的上行接收函数 */
}MUX_AT_UL_DLCI_INFO_STRU;

/* 记录设备的信息 */
typedef struct
{
    UDI_DEVICE_ID_E               enUdiDevId;                     /* 底软实际和MUX一起使用的设备ID */
    UDI_HANDLE                  slUdiMuxAcmHdl;                 /* 设备对应的句柄 */
    VOS_UINT32                  (*pMuxAcmUlRxFunc)(VOS_VOID);   /* 该句柄上报数据时MUX调用的回调函数指针 */
}MUX_DEV_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulInvalidUdiHandleNums;         /* 获取底软UDI句柄错误的次数 */
    VOS_UINT32                  ulGetDataFailNums;              /* 底软回调后获取不到数据的次数 */
    VOS_UINT32                  ulDiscardUlPacketNums;          /* 上行因为状态不对等原因丢弃的数据包个数 */
    VOS_UINT32                  ulSuccGetUlPacketNums;          /* 上行Hsic通道成功获取的数据包个数 */
    VOS_UINT32                  ulFailSendUlPacketNums;         /* 上行向AT通道发送失败的数据包个数 */
    VOS_UINT32                  ulSuccSendUlPacketNums;         /* 上行向AT通道成功发送的数据包个数*/
    VOS_UINT32                  ulFailSendDlPacketNums;         /* 下行调用底软通道发送失败的数据包个数 */
    VOS_UINT32                  ulSuccSendDlPacketNums;         /* 下行调用底软通道发送成功的数据包个数 */
    VOS_UINT32                  ulFreeDlPacketNums;             /* 下行调用底软通道释放成功的数据包个数 */
} MUX_DEV_STATIC_INFO_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 MUX_DlciDlUsbAcmFreeDataCB(VOS_UINT8 *pucBuf);
extern VOS_UINT32 MUX_DlciUlHsicFreeDataBuf(
    UDI_HANDLE                          ulUdiHdl,
    VOS_UINT8                          *pucBuf,
    VOS_UINT16                          usLen
);
extern VOS_UINT32 MUX_DlciDlDataProc (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pucSendBuf,
    VOS_UINT16 *pusSendDataLen, VOS_UINT8* pucBuf, VOS_UINT16 usDataLen);

extern VOS_VOID MUX_TraceUlData(VOS_UINT32 ulDeviceId, VOS_UINT8 *pucBuf, VOS_UINT16 usLen);
extern VOS_VOID MUX_TraceDlData(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8 *pData, VOS_UINT16 usDataLen);
extern VOS_VOID MUX_StaticInfoInit( VOS_VOID );
extern VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock );

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

#endif /* end of PsHsic.h */

