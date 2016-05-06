

/******************************************************************************

                  版权所有 (C), 2015-2025, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Cbtapprl.h
  版 本 号   : 初稿
  作    者   : x00263027
  生成日期   : 2015年3月2日
  最近修改   :
  功能描述   : Cbtapprl.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月2日
    作    者   : x00263027
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CBT_APPRL_H__
#define __CBT_APPRL_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "cbtrl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif





extern VOS_UINT32                       g_ulCbtAcpuDbgFlag;


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CBT_MSG_FIRST_BYTE                  (0x07)
#define BIT_LEFTMOVE_N(num)                 (0x01 <<( num))
#define CBT_ACPU_VCOM_CB                    BIT_LEFTMOVE_N(0)
#define CBT_ACPU_DISPATCH_MSG               BIT_LEFTMOVE_N(1)
#define CBT_ACPU_USB_CB                     BIT_LEFTMOVE_N(2)
/* datatype 字段长度 */
#define CBT_RL_DATATYPE_LEN                 (0x1)
#define CBT_HDLC_FCS_LEN                    (2)           /* HDLC帧中FCS未转义时的长度(单位: Byte) */
#define CBT_HDLC_BUF_MAX_LEN                (CBT_MSG_SEGMENT_LEN + CBT_RL_DATATYPE_LEN + CBT_HDLC_FCS_LEN)

/*值为CBT_READ_NV_IND_STRU结构体中，sizeof(ulErrorCode) + sizeof(ulNvId) + sizeof(ulCount)*/
#define CBT_READ_NV_HEAD_SIZE               (12)
#define CBT_WRITE_NV_HEAD_SIZE              (8)
/*长度为NVID的值+NVID长度所占内存长度*/
#define CBT_NV_ITEM_SIZE                    (4)
#define CBT_IND_RESULT_SIZE                 (4)
#define CBT_EST_IND_RSV_LEN                 (256)


#define CBT_END_FRAME                       (1)
/*#define SEG_MAX_LEN                         (4*1024)*/
/*#define MAXSEGMENT                          (16)*/
/*组包后的最大长度*/
#define CBT_TOTAL_MSG_MAX_LEN               (20*1024)/*(SEG_MAX_LEN + (SEG_MAX_LEN-CBT_MSG_HEADER_LENGTH)*(MAXSEGMENT-1))*/

#define OM_CBT_SEND_DATA_REQ                (0x030d)



#define CBT_ACPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
    if(VOS_FALSE != (g_ulCbtAcpuDbgFlag&ulSwitch)) \
    { \
        VOS_UINT32 ulOmDbgIndex; \
        vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
        { \
            vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
        } \
        vos_printf("\r\n"); \
    } \


/*OM<->APP : Restablish link*/
#define APP_OM_ESTABLISH_REQ                      0x80b1
#define OM_APP_ESTABLISH_CNF                      0x80b2

/*OM<->APP : Release link*/
#define APP_OM_RELEASE_REQ                        0x80b3
#define OM_APP_RELEASE_CNF                        0x80b4

#define APP_OM_READ_NV_REQ                        0x8021

#define OM_APP_READ_NV_IND                        0x8022

#define APP_OM_WRITE_NV_REQ                       0x8023
#define OM_APP_WRITE_NV_CNF                       0x8024


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulResult;                            /*返回执行结果*/
    VOS_UINT8  ausReserve[CBT_EST_IND_RSV_LEN];
}CBT_ESTABLISH_IND_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*要读取的NV项个数*/
    VOS_UINT16 ausNvItemId[2];      /*要读取的NV项ID数组，其中个数为ulCount*/
}CBT_READ_NV_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrorCode;        /*返回执行结果*/
    VOS_UINT32 ulErrNvId;          /*返回出现错误的NVID*/
    VOS_UINT32 ulCount;            /*返回的NV项个数*/
    VOS_UINT16 ausNVItemData[2];   /*包括NVID值、NVID内容的长度、NVID的内容*/
}CBT_READ_NV_IND_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* 消息ID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /*返回执行结果*/
    VOS_UINT32                  ulErrNvId;          /*返回出现错误的NVID*/
    VOS_UINT32                  ulCount;            /*返回的NV项个数*/
}CBT_READ_NV_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*要写入的NV项个数*/
    VOS_UINT16 ausNvItemData[2];    /*包括NVID值、NVID内容的长度、NVID的内容*/
}CBT_WRITE_NV_REQ_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* 消息ID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /*返回执行结果*/
    VOS_UINT32                  ulErrNvId;          /*返回出现错误的NVID*/
}CBT_WRITE_NV_CNF_STRU;

/*****************************************************************************
结构名    : OMRL_CBT_HDLC_ENCODE_MEM_CTRL
结构说明  : OMRL CBT校准通道HDLC解析控制信息结构(uncache)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucBuf;         /* 指向缓冲区虚拟首地址 */
    VOS_UINT8                          *pucRealBuf;     /* 指向缓冲区实首地址 */
    VOS_UINT32                          ulBufSize;      /* 保存缓冲区总大小 */
    VOS_UINT32                          ulRsv;          /* Reserve */
}CBT_HDLC_ENCODE_MEM_CTRL;

/*****************************************************************************
结构名    : OM_ACPU_ICC_SEND_FAIL_STRU
结构说明  : ACPU ICC通道发送失败的可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendErrNum;      /*当前发送的错误记录*/
    VOS_UINT32                          ulICCOmSendErrLen;      /*当前发送的错误总消息长度*/
    VOS_UINT32                          ulICCOmSendErrSlice;    /*当前发送的错误消息最后一条数据的时间*/
}CBT_ACPU_ICC_SEND_FAIL_STRU;

/*****************************************************************************
结构名    : OM_ACPU_ICC_SEND_SUC_STRU
结构说明  : ACPU ICC通道成功发送的可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendMsgNum;      /*当前发送的总消息数*/
    VOS_UINT32                          ulICCOmSendLen;         /*当前发送的总消息长度*/
    VOS_UINT32                          ulICCOmSendSlice;       /*当前发送的最后一条数据的时间*/
}CBT_ACPU_ICC_SEND_SUC_STRU;

/*****************************************************************************
结构名    : OM_MAINTENANCE_INFO_STRU
结构说明  : OM模块可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /* 接收或发送数据长度 */
    VOS_UINT32                          ulNum;     /* 接收或发送数据次数 */
}CBT_MAINTENANCE_INFO_STRU;

/*****************************************************************************
结构名    : OM_ACPU_PC_UE_RELEASE_INFO_STRU
结构说明  : OM模块断链操作信息记录结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlsAp2Modem;     /* AP到Modem切换 */
    VOS_UINT32                          ulRlsModem2Ap;     /* Modem到AP切换 */
    VOS_UINT32                          ulRlsDrvSuspend;   /* DRV挂起 */
    VOS_UINT32                          ulRlsPortClose;    /* 端口关闭 */
    VOS_UINT32                          ulRlsPortSwitch;   /* 端口切换 */
    VOS_UINT32                          ulSlice;           /* 最后一次收到断链的时间 */
}CBT_ACPU_PC_UE_RELEASE_INFO_STRU;

/*****************************************************************************
结构名    : CBT_ACPU_PC_UE_FAIL_STRU
结构说明  : CBT模块异常接收可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU           stLostData;         /* 记录丢掉的数据 */
    VOS_UINT32                          ulFrameDecapErr;    /* 记录发生解帧错误的次数 */

    VOS_UINT16                          usPacketLenErr;     /* 记录发生包长度小于OM_USB_FRAME_LEN错误的次数 */
    VOS_UINT16                          usLenTooShortErr;   /* 记录发生数据长度小于分段头的错误次数 */
    VOS_UINT16                          usSegLenErr;        /* 记录发生段长度错误次数 */
    VOS_UINT16                          usSegNumErr;        /* 记录发生段数目错误次数 */

    VOS_UINT16                          usDatatypeErr;      /* 记录发生datatype字段错误次数 */
    VOS_UINT16                          usMsgTooLongErr;    /* 记录发生组包后消息大于8K的错误次数 */
    VOS_UINT16                          usCpuIdErr;         /* 记录发生CPU id错误次数 */
    VOS_UINT16                          usNoMemErr;         /* 记录发生空间不足的错误次数 */

    VOS_UINT16                          usDataHeadErr;      /* 记录发生数据帧头部错误次数 */
    VOS_UINT16                          usMsgLenErr;        /* 记录发生消息长度错误次数 */
    VOS_UINT16                          usMsgSnErr;         /* 记录发生消息序号错误次数 */
    VOS_UINT16                          usTransIdErr;       /* 记录发生TransId 序号错误次数 */
    VOS_UINT16                          usPacketLostErr;    /* 记录发生包丢失的错误次数 */
    VOS_UINT16                          usTimeStampErr;     /* 记录发生包时间戳的错误次数 */

    VOS_UINT16                          usLinkDataLenErr;   /* 记录链路消息长度错误的次数 */
    VOS_UINT16                          usLinkStatusErr;    /* 记录链路关闭时收到消息包的次数 */
    VOS_UINT16                          usAllocMsg;         /* 记录消息分配失败的次数 */
    VOS_UINT16                          usRcv;

    CBT_ACPU_ICC_SEND_FAIL_STRU          stICCSendFailInfo;  /* 记录ACPU成功发送的ICC数据 */
}CBT_ACPU_PC_UE_FAIL_STRU;

/*****************************************************************************
结构名    : CBT_ACPU_PC_UE_SUC_STRU
结构说明  : CBT模块正常接收可维可测信息记录结构
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU            stTotalData;       /* 记录接收到的总数据 */
    CBT_MAINTENANCE_INFO_STRU            stHdlcDecapData;
    CBT_MAINTENANCE_INFO_STRU            stLinkData;        /* 记录收到的链路数据 */
    CBT_MAINTENANCE_INFO_STRU            stCcpuData;        /* 记录发给CCPU的数据 */
    CBT_MAINTENANCE_INFO_STRU            stAcpuData;        /* 记录发给ACPU的数据 */
    CBT_ACPU_ICC_SEND_SUC_STRU           stICCSendSUCInfo;  /* 记录ACPU成功发送的ICC数据 */
    CBT_MAINTENANCE_INFO_STRU            stRlsData;         /* 记录工具发送的Release数据 */
    CBT_ACPU_PC_UE_RELEASE_INFO_STRU     stRlsInfo;         /* 记录Release信息 */
}CBT_ACPU_PC_UE_SUC_STRU;

/*****************************************************************************
结构名    : CBTRL_MSG_COMBINE_INFO_STRU
结构说明  : CBTRL模块完成组包需要的信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotalSegNum;      /* 总的分段数 */
    VOS_UINT8                           ucExpectedSegSn;    /* 组包函数中期望得到的消息包序号 */
    VOS_UINT16                          usRsv;

    VOS_UINT32                          ulTransId;
    VOS_UINT32                          ulTimeStampL;
    VOS_UINT16                          usTimeStampH;
    VOS_UINT16                          usRsv2;

    VOS_UINT32                          ulTotalMsgLen;      /* 组包函数中组包后消息总的长度 */
    VOS_UINT32                          ulMoveLen;          /* 组包函数中每放入一消息包后的偏移 */
    MsgBlock *                          pstWholeMsg;        /*指向组包函数中完整消息包*/
}CBT_MSG_COMBINE_INFO_STRU;

/*****************************************************************************
结构名    : CBTRL_RCV_CHAN_CTRL_INFO_STRU
结构说明  : CBTRL模块通道控制信息结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCbtSwitchOnOff;
    CBT_MSG_COMBINE_INFO_STRU           stMsgCombineInfo;

    CBT_ACPU_PC_UE_FAIL_STRU            stPcToUeErrRecord;
    CBT_ACPU_PC_UE_SUC_STRU             stPcToUeSucRecord;
}CBT_RCV_CHAN_CTRL_INFO_STRU;


/*****************************************************************************
  函数声明
*****************************************************************************/
VOS_UINT32 CBT_AcpuInit(VOS_VOID);
VOS_UINT32 CBT_AcpuSendData(CBT_UNIFORM_MSG_STRU * pstMsg, VOS_UINT16 usMsgLen);

VOS_VOID CBT_AcpuSendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                            VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult);
VOS_VOID CBT_AcpuSendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                             VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg);
VOS_VOID CBT_AcpuOpenLog(VOS_UINT32 ulFlag);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
