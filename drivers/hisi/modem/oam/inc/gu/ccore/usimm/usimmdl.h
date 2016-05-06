/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : UsimmDL.h
  Author      : zhuli 00100318
  Version     : V100R002
  Date        : 2008-5-15
  Description : 该头文件定义了---
  History     :
  1.Date:2008-07-02
     Author: m00128685
     Modification:Modify the definition of enum

************************************************************************/

#ifndef __USIMM_DL_H__
#define __USIMM_DL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SCI_SUCCESS_USIMM           (0)    /*函数执行成功*/
#define SCI_ERROR_USIMM             (1)    /*函数执行失败*/

#define USIMM_P3ERROR_MAXTIME       (100)

/*USIMM模块支持的最大APDU命令长度*/
#define USIMM_APDU_MAXLEN           (256)
/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum USIMMDL_DRV_API_NUM_ENUM
{
    USIMMDL_DRV_USIMMSCI_RST            = 0xF0,
    USIMMDL_DRV_USIMMSCI_CLASS_SWITCH   = 0xF1,
    USIMMDL_DRV_USIMMSCI_GET_CARD_STAU  = 0xF2,
    USIMMDL_DRV_USIMMSCI_SND_DATA1      = 0xF3,
    USIMMDL_DRV_USIMMSCI_RCV1           = 0xF4,
    USIMMDL_DRV_USIMMSCI_SND_DATA2      = 0xF5,
    USIMMDL_DRV_USIMMSCI_SND_DATA3      = 0xF6,
    USIMMDL_DRV_USIMMSCI_SND_DATA4      = 0xF7,
    USIMMDL_DRV_USIMMSCI_RCV2           = 0xF8,
    USIMMDL_DRV_USIMMSCI_RCV3           = 0xF9,
    USIMMDL_DRV_USIMMSCI_RCV4           = 0xFA,
    USIMMDL_DRV_USIMMSCI_DEACT          = 0xFB,

    USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK = 0x01F0,
    USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK = 0x01F1,
    USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK = 0x01F2,
    USIMMDL_DRV_USIMMSCI_T1_RST         = 0x01F3,
    USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1   = 0x01F4,
    USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2   = 0x01F5,
    USIMMDL_DRV_USIMMSCI_T1_RCV         = 0x01F6,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1 = 0x01F7,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2 = 0x01F8,

    USIMMDL_DRV_USIMMSCI_BUTT
};

enum USIMMDL_STATE_ENUM
{
    USIMMDL_STATE_IDLE          = 0,
    USIMMDL_STATE_SENDAPDU      = 1,
    USIMMDL_STATE_SENDDATA      = 2,
    USIMMDL_STATE_WAITACK       = 3,
    USIMMDL_STATE_WAITDATA      = 4,
    USIMMDL_STATE_WAITSW        = 5,
    USIMMDL_STATE_GETRESPONSE   = 6,
    USIMMDL_STATE_BUTT
};
typedef VOS_UINT32      USIMMDL_STATE_ENUM_UINT32;

enum USIMM_CASE_TYPE_ENUM
{
    USIMM_CMD_CASE1             = 1,
    USIMM_CMD_CASE2             = 2,
    USIMM_CMD_CASE3             = 3,
    USIMM_CMD_CASE4             = 4,
    USIMM_CMD_CASE_BUTT
};
typedef VOS_UINT32      USIMM_CASE_TYPE_ENUM_UINT32;

enum USIMMDL_ERROR_ENUM
{
    USIMMDL_NOERROR             = 0,
    USIMMDL_SCISENDAPDU_ERROR   = 1,
    USIMMDL_SCISENDLC_ERROR     = 2,
    USIMMDL_SCIRECEIVEACK_ERROR = 3,
    USIMMDL_SCIRECEIVELE_ERROR  = 4,
    USIMMDL_SCIRECEIVESW_ERROR  = 5,
    USIMMDL_STATE_ERROR         = 6,
    USIMMDL_ERROR_BUTT
};
typedef VOS_UINT32      USIMMDL_ERROR_ENUM_UINT32;

/*Usimm DL调用返回值*/
enum USIMM_DLHANDLE_RESULT_ENUM
{
    USIMM_DL_SUCESS             = VOS_OK,
    USIMM_DL_SEND_ERROR,
    USIMM_DL_RECEIVE_ERROR,
};

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLeValue;                          /* 接收数据长度 */
    VOS_UINT32                          ulLcValue;                          /* 发送数据长度 */
    VOS_UINT32                          ulRecDataLen;
    VOS_UINT8                           ucResult;
    VOS_UINT8                           ucACK;                              /*接收的ACK*/
    VOS_UINT8                           ucSW1;                              /*命令结束后的SW1*/
    VOS_UINT8                           ucSW2;                              /*命令结束后的SW2*/
    VOS_UINT8                           ucApduSW1;                          /*命令第一次发送的SW1*/
    VOS_UINT8                           ucApduSW2;                          /*命令第一次发送的SW2*/
    VOS_UINT8                           aucAPDU[USIMM_APDU_HEADLEN];        /*命令的APDU*/
    VOS_UINT8                           aucGetRepAPDU[USIMM_APDU_HEADLEN];  /*Get Response命令的APDU*/
    VOS_UINT8                           aucRecvBuf[USIMM_APDU_MAXLEN];      /* 接收数据内容*/
    VOS_UINT8                           aucSendBuf[USIMM_APDU_MAXLEN];      /* 发送数据内容*/
}USIMM_APDU_ST;

typedef struct
{
    VOS_UINT32                  ulSendDataLen;      /* 当前发送数据长度 */
    VOS_UINT32                  ulRecDataLen;       /* 当前接收数据长度 */
    USIMMDL_STATE_ENUM_UINT32   enDLState;          /* 当前链路层状态 */
    USIMMDL_ERROR_ENUM_UINT32   enDLError;          /* 当前链路层错误信息*/
    USIMM_CASE_TYPE_ENUM_UINT32 enCMDCase;          /* 当前命令类型*/
    VOS_UINT32                  ulSendAPDUTime;     /* 当前发送命令头的次数 */
    VOS_BOOL                    bSendRep;           /* 1为需要发送Get Response*/
    VOS_UINT32                  ulP3ErrorTime;      /* 接收P3错误的次数 */
}USIMMDL_CONTROL_ST;

typedef VOS_UINT32 (*PUSIMMDLPROC)(USIMM_APDU_ST *pstAPDUData);

typedef struct
{
    USIMMDL_STATE_ENUM_UINT32   enStateId;        /* 状态ID */
    PUSIMMDLPROC                pProcFun;        /* 处理函数 */
}USIMMDL_FUNC_STATUS;


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMMDL_CONTROL_ST   gstUSIMMDLControl;


/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/
extern VOS_UINT32 USIMM_DLHandle(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLResetCard(
    VOS_UINT32                          ulResetType, 
    VOS_INT32                           *plVoltageSwitchRst);

extern VOS_UINT32 USIMM_DLReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_CglaDLHandle(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaReceiveSW(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaGetResponse(
    USIMM_APDU_ST                       *pstAPDUData);

extern VOS_VOID USIMM_DLJudgeCmdCase(
    USIMM_APDU_ST                       *pstAPDUData);

/*外部接口*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#else

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "usimmapdu.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SCI_SUCCESS_USIMM   0    /*函数执行成功*/
#define SCI_ERROR_USIMM     1    /*函数执行失败*/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum USIMMDL_DRV_API_NUM_ENUM
{
    USIMMDL_DRV_USIMMSCI_RST            = 0xF0,
    USIMMDL_DRV_USIMMSCI_CLASS_SWITCH   = 0xF1,
    USIMMDL_DRV_USIMMSCI_GET_CARD_STAU  = 0xF2,
    USIMMDL_DRV_USIMMSCI_SND_DATA1      = 0xF3,
    USIMMDL_DRV_USIMMSCI_RCV1           = 0xF4,
    USIMMDL_DRV_USIMMSCI_SND_DATA2      = 0xF5,
    USIMMDL_DRV_USIMMSCI_SND_DATA3      = 0xF6,
    USIMMDL_DRV_USIMMSCI_SND_DATA4      = 0xF7,
    USIMMDL_DRV_USIMMSCI_RCV2           = 0xF8,
    USIMMDL_DRV_USIMMSCI_RCV3           = 0xF9,
    USIMMDL_DRV_USIMMSCI_RCV4           = 0xFA,
    USIMMDL_DRV_USIMMSCI_DEACT          = 0xFB,

    USIMMDL_DRV_USIMMSCI_T1_SND_R_BLOCK = 0x01F0,
    USIMMDL_DRV_USIMMSCI_T1_SND_I_BLOCK = 0x01F1,
    USIMMDL_DRV_USIMMSCI_T1_SND_S_BLOCK = 0x01F2,
    USIMMDL_DRV_USIMMSCI_T1_RST         = 0x01F3,
    USIMMDL_DRV_USIMMSCI_T1_SET_BWT_1   = 0x01F4,
    USIMMDL_DRV_USIMMSCI_T1_RST_BWT_2   = 0x01F5,
    USIMMDL_DRV_USIMMSCI_T1_RCV         = 0x01F6,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_1 = 0x01F7,
    USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2 = 0x01F8,

    USIMMDL_DRV_USIMMSCI_BUTT
};

enum USIMMDL_STATE_ENUM
{
    USIMMDL_STATE_IDLE          = 0,
    USIMMDL_STATE_SENDAPDU      = 1,
    USIMMDL_STATE_SENDDATA      = 2,
    USIMMDL_STATE_WAITACK       = 3,
    USIMMDL_STATE_WAITDATA      = 4,
    USIMMDL_STATE_WAITSW        = 5,
    USIMMDL_STATE_GETRESPONSE   = 6,
    USIMMDL_STATE_BUTT
};
typedef VOS_UINT32      USIMMDL_STATE_ENUM_UINT32;

enum USIMM_CASE_TYPE_ENUM
{
    USIMM_CMD_CASE1             = 1,
    USIMM_CMD_CASE2             = 2,
    USIMM_CMD_CASE3             = 3,
    USIMM_CMD_CASE4             = 4,
    USIMM_CMD_CASE_BUTT
};
typedef VOS_UINT32      USIMM_CASE_TYPE_ENUM_UINT32;


enum USIMMDL_ERROR_ENUM
{
    USIMMDL_NOERROR             = 0,
    USIMMDL_SCISENDAPDU_ERROR   = 1,
    USIMMDL_SCISENDLC_ERROR     = 2,
    USIMMDL_SCIRECEIVEACK_ERROR = 3,
    USIMMDL_SCIRECEIVELE_ERROR  = 4,
    USIMMDL_SCIRECEIVESW_ERROR  = 5,
    USIMMDL_STATE_ERROR         = 6,
    USIMMDL_ERROR_BUTT
};
typedef VOS_UINT32      USIMMDL_ERROR_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT32                  ulSendDataLen;      /* 当前发送数据长度 */
    VOS_UINT32                  ulRecDataLen;       /* 当前接收数据长度 */
    USIMMDL_STATE_ENUM_UINT32   enDLState;          /* 当前链路层状态 */
    USIMMDL_ERROR_ENUM_UINT32   enDLError;          /* 当前链路层错误信息*/
    USIMM_CASE_TYPE_ENUM_UINT32 enCMDCase;          /* 当前命令类型*/
    VOS_UINT32                  ulSendAPDUTime;     /* 当前发送命令头的次数 */
    VOS_BOOL                    bSendRep;           /* 1为需要发送Get Response*/
}USIMMDL_CONTROL_ST;

typedef VOS_UINT32 (*PUSIMMDLPROC)(USIMM_APDU_ST *pstAPDUData);

typedef struct
{
    USIMMDL_STATE_ENUM_UINT32   enStateId;        /* 状态ID */
    PUSIMMDLPROC                pProcFun;        /* 处理函数 */
}USIMMDL_FUNC_STATUS;


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMMDL_CONTROL_ST   gstUSIMMDLControl;

/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/
extern VOS_UINT32 USIMM_DLHandle(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_DLResetCard(VOS_UINT32 ulResetType, VOS_INT32 *plVoltageSwitchRst);

extern VOS_UINT32 USIMM_DLReceiveSW(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_CglaDLHandle(USIMM_APDU_ST* pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaReceiveSW(USIMM_APDU_ST *pstAPDUData);

extern VOS_UINT32 USIMM_DLCglaGetResponse(USIMM_APDU_ST* pstAPDUData);

extern VOS_VOID USIMM_DLJudgeCmdCase(USIMM_APDU_ST* pstAPDUData);

/*外部接口*/
extern VOS_VOID HPA_USIMLowPowerLock( VOS_UINT32 ulPid );

extern VOS_VOID HPA_USIMLowPowerUnLock( VOS_UINT32 ulPid );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of UsimmDL.h*/


