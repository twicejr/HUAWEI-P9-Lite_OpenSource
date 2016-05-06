/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsUimProc.h
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : TafXsmsUimProc.c头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XSMS_UIM_PROC_H_
#define _TAF_XSMS_UIM_PROC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"
#include "TafAppXsmsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* UIM卡中短信的最大记录数 */
#define TAF_XSMS_RECORD_NUM_MAX    (255)

/* UIM卡中短信的最大长度 */
#define TAF_XSMS_RECORD_LEN_MAX    (255)

/* UIM卡中IMSI的最大长度 */
#define TAF_XSMS_IMSI_LEN_MAX      (10)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_XSMS_UIM_MSG_STATUS_ENUM32
 枚举说明  : UIM卡中短信的状态
*****************************************************************************/
enum TAF_XSMS_UIM_MSG_STATUS_ENUM
{
    TAF_XSMS_UIM_MSG_STATUS_FREE   = 0,
    TAF_XSMS_UIM_MSG_STATUS_READ   = 1,
    TAF_XSMS_UIM_MSG_STATUS_UNREAD = 3,
    TAF_XSMS_UIM_MSG_STATUS_SEND   = 5,
    TAF_XSMS_UIM_MSG_STATUS_UNSEND = 7,
    TAF_XSMS_UIM_MSG_STATUS_BUTT   = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_UIM_MSG_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XSMS_UIM_REQ_TYPE_ENUM32
 枚举说明  : XSMS与卡交互来源
*****************************************************************************/
enum TAF_XSMS_UIM_REQ_TYPE_ENUM
{
    TAF_XSMS_UIM_REQ_TYPE_INIT     = 0,
    TAF_XSMS_UIM_REQ_TYPE_AT       = 1,
    TAF_XSMS_UIM_REQ_TYPE_MO       = 2,
    TAF_XSMS_UIM_REQ_TYPE_MT       = 3,
    TAF_XSMS_UIM_REQ_TYPE_BUTT     = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_UIM_REQ_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XSMS_INIT_STATUS_ENUM
 枚举说明  : EFSMS初始化状态
*****************************************************************************/
enum TAF_XSMS_INIT_STATUS_ENUM
{
    TAF_XSMS_INIT_STATUS_NOT_INIT  = 0,
    TAF_XSMS_INIT_STATUS_FINISH    = 1,
    TAF_XSMS_INIT_STATUS_BUTT      = 0xFFFFFFFF
};

typedef VOS_UINT32 TAF_XSMS_INIT_STATUS_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TAF_XSMS_UIM_MSG_STATUS_ENUM32
 枚举说明  : UIM卡中短信的使用状态
*****************************************************************************/
enum TAF_XSMS_EFSMS_STATUS_ENUM
{
    TAF_XSMS_EFSMS_STATUS_FREE     = 0,
    TAF_XSMS_EFSMS_STATUS_USED     = 1,
    TAF_XSMS_EFSMS_STATUS_BUTT     = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_EFSMS_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XSMS_UIM_LOCK_ENUM8
 枚举说明  : XSMS提供的对外API对卡操作的锁
*****************************************************************************/
enum TAF_XSMS_UIM_LOCK_ENUM
{
    TAF_XSMS_UIM_LOCK_UNLOCK       = 0,
    TAF_XSMS_UIM_LOCK_LOCKED       = 1,
    TAF_XSMS_UIM_LOCK_BUTT
};
typedef VOS_UINT8 TAF_XSMS_UIM_LOCK_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XSMS_FILEID_ENUM_ENUM_UINT32
 枚举说明  :
*****************************************************************************/
enum TAF_XSMS_FILEID_ENUM
{
    TAF_XSMS_EFSMS_FILEID           = 0,
    TAF_XSMS_EFSMSS_FILEID          = 1,
    TAF_XSMS_EFIMSIT_FILEID         = 2,
    TAF_XSMS_FILEID_BUTT
};
typedef VOS_UINT32 TAF_XSMS_FILEID_ENUM_ENUM_UINT32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
//extern TAF_XSMS_INIT_CTRL_INFO_STRU    g_stTAFXsmsInitCtrlInfo;
//extern TAF_XSMS_CTRL_INFO_STRU         g_stTAFXsmsReqCtrlInfo;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
 结构名    :TAF_XSMS_UIM_MSG_STRU
 结构说明  :XSMS与卡交互消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* 消息ID */
}TAF_XSMS_UIM_MSG_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_CURRENT_INIT_FILE_STRU
 结构说明  :XSMS与卡交互当前正在读取的文件结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrFile;         /* 当前在读取的文件 */
    VOS_UINT8                           ucCurrIndex;        /* 当前在读取的记录 */
    VOS_UINT8                           ucRsv;
}TAF_XSMS_CURRENT_INIT_FILE_STRU;

/*****************************************************************************
 结构名    :TAF_XSMS_INIT_CTRL_INFO_STRU
 结构说明  :XSMS初始化状态控制结构
*****************************************************************************/
typedef struct
{
    TAF_XSMS_INIT_STATUS_ENUM_UINT32    enSmsInitState;                                 /* SMS初始化状态 */
    TAF_XSMS_CURRENT_INIT_FILE_STRU     stCurrInitFile;                                 /* 当前初始化的文件 */
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;                                     /* 保存当前卡的类型，仅在UIM/CSIM时才会初始化 */
    VOS_UINT16                          usMessageId;                                    /* 短信发送时需要使用的ID */
    VOS_UINT8                           aucImsi[TAF_XSMS_IMSI_LEN_MAX];                /* EFIMSI内容 */
    VOS_UINT8                           aucFreeIndex[(TAF_XSMS_RECORD_NUM_MAX + 1)/8]; /* EFSMS使用索引 */
    VOS_UINT8                           ucMaxRecord;                                    /* EFSMS最大记录数 */
    VOS_UINT8                           ucRecordLen;                                    /* EFSMS记录长度 */
    VOS_UINT8                           ucTotalUsed;                                    /* EFSMS当前使用记录数 */
    VOS_UINT8                           ucRsv;
    VOS_UINT8                          *pucContent;                                     /* EFSMS在内存中的内容，当前暂时不使用 */
}TAF_XSMS_INIT_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    :TAF_XSMS_CTRL_INFO_STRU
 结构说明  :XSMS对外API的控制结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usClient;
    VOS_UINT8                           ucOpID;
    TAF_XSMS_UIM_LOCK_ENUM_UINT8        enUimLock;
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32   enAppMsgType;
}TAF_XSMS_CTRL_INFO_STRU;

typedef struct
{
    TAF_XSMS_FILEID_ENUM_ENUM_UINT32    enFileID;
    USIMM_DEF_FILEID_ENUM_UINT32        enUIMID;
    USIMM_DEF_FILEID_ENUM_UINT32        enCSIMID;
}TAF_XSMS_FILETABLE_STRU;

typedef struct
{
    VOS_UINT8                   ucRecordNum;    /* 文件记录号，二进制文件填0 */
    VOS_UINT8                   ucRsv;          /* 保留 */
    VOS_UINT16                  usEfLen ;       /* 更新数据长度 */
    VOS_UINT8                   *pucEfContent;  /* 更新数据内容 */
}TAF_XSMS_SETFILE_INFO_STRU;

/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 TAF_XSMS_FindFreeIndex(VOS_UINT8 *pucIndex);

extern VOS_VOID   TAF_XSMS_SetBitToBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo,VOS_UINT32 ulValue);

extern VOS_UINT32 TAF_XSMS_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo);

extern VOS_UINT32 TAF_XSMS_AtSmsDeleteReq(VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_MsgIdUpdataReq(VOS_UINT8 *pucMsgId);

extern VOS_UINT32 TAF_XSMS_AtSmsWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucData, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_PrlWriteReq(VOS_UINT8 ucLen, VOS_UINT8 *pucPrl, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_CommonFileWriteReq(VOS_UINT8 ucLen, VOS_UINT8 * pucData, VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_PrlReadReq(VOS_UINT8 ucIndex);

extern VOS_UINT32 TAF_XSMS_InitFileReadReq(VOS_UINT8 ucIndex, VOS_UINT32 enFileId);

extern VOS_VOID   TAF_XSMS_PihStatusIndProc(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_PihMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitUsimmMaxRecordRspMsgProc(USIMM_QUERYFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitEfsmsFileMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_InitTimeOutMsgProc(VOS_VOID);

extern VOS_VOID   TAF_XSMS_InitUsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_MtGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmGetFileRspMsgProc(USIMM_READFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_MtSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmSetFileRspMsgProc(USIMM_UPDATEFILE_CNF_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_UsimmMsgProc(TAF_XSMS_UIM_MSG_STRU *pstMsg);

extern VOS_UINT32 TAF_XSMS_SetFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID,
                                        VOS_UINT32                      ulSendPara,
                                        TAF_XSMS_SETFILE_INFO_STRU      *pstFileInfo);

extern VOS_UINT32 TAF_XSMS_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32   enFileID,
                                        VOS_UINT32                    ulSendPara,
                                        VOS_UINT8                      ucIndex);
extern VOS_UINT32 TAF_XSMS_QueryFileReq(TAF_XSMS_FILEID_ENUM_ENUM_UINT32 enXSMSID);

extern VOS_VOID TAF_XSMS_ChangeFileID(TAF_XSMS_FILEID_ENUM_ENUM_UINT32   enFileID,
                                      USIMM_DEF_FILEID_ENUM_UINT32      *penDefID);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
