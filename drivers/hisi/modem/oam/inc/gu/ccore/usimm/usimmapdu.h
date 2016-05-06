/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : UsimmAPDU.h
  Author      : zhuli 00100318
  Version     : V100R002
  Date        : 2008-5-15
  Description : 该头文件定义了---
  History     :
  1.Date:2008-07-02
     Author: m00128685
     Modification:Modify the definition of enum

************************************************************************/

#ifndef __USIMM_APDU_H__
#define __USIMM_APDU_H__

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
#include "usimmdl.h"
#include "omnvinterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*SW check定义*/
#define USIMM_SIMSW_MAXNUMBER       (24)
#define USIMM_USIMSW_MAXNUMBER      (40)

#define USIMM_STORE_ESNMEID_MAX     (8)
#define USIMM_BS_RANDSEED_MAX       (4)

#define USIMM_APDU_3GPP_CLA         (0x80)

#define USIMM_APDU_CHANNEL_4        (3)
#define USIMM_APDU_CHANNEL_20       (19)

/*读取文件*/
#define USIMM_READ_ALLRECORD        (0)


#define USIMM_APDU_BASECHANNEL      (0)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*SW定义值由于返回具体错误原因值需要移出到对外声明头文件中*/
typedef VOS_UINT16      USIMM_SWCHECK_ENUM_UINT16;

enum UICC_STORE_ESN_MEID_P1
{
    UICC_STORE_ESN_P1           = 0x00,
    UICC_STORE_MEID_P1          = 0x01,
    UICC_STORE_ESN_MEID_P1_BUTT
};
typedef VOS_UINT8       UICC_STORE_ESN_MEID_P1_UINT8;

enum USIMM_SENDAPDU_RESULT_ENUM
{
    USIMM_SENDAPDU_OK           = VOS_OK,
    USIMM_SENDAPDU_RETRY,
    USIMM_SENDAPDU_FAIL,
    USIMM_SENDAPDU_RESULT_BUTT
};
typedef VOS_UINT32      USIMM_SENDAPDU_RESULT_ENUM_UINT32;

typedef USIMM_SENDAPDU_RESULT_ENUM_UINT32 (*PFAPDUFUNC)(USIMM_APDU_ST *pstApduInfo, VOS_UINT32 ulSendCnt);

/* STATUS命令枚举 即下发数据单元的p1参数，参见协议102.221第11.1.2 */
enum USIMM_STATUS_P1_PARA_ENUM
{
    USIMM_STATUS_NO_INDICATION        = 0x00, /* No indication */
    USIMM_STATUS_CURAPP_INITIALIZED   = 0x01, /* Current application is initialized in the terminal */
    USIMM_STATUS_TERMINATION_CURAPP   = 0x02, /* the terminal will initiate the termination of the current application */
    USIMM_STATUS_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P1_PARA_ENUM_UINT8;

/* STATUS命令枚举 即下发数据单元的p2参数，参见协议102.221第11.1.2 */
enum USIMM_STATUS_P2_PARA_ENUM
{
    USIMM_STATUS_FCP_RETURNED       = 0x00,  /* response paremeters and data identical to the response paremeters and data of the select command */
    USIMM_STATUS_DF_NAME_RETURNED   = 0x01,  /* the DF name TLV-object of the currently selected application is returned */
    USIMM_STATUS_NO_DATA_RETURNED   = 0x0C,  /* No data returned */
    USIMM_STATUS_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_STATUS_P2_PARA_ENUM_UINT8;


/* USIM卡select命令P1参数含义，协议TS102221 11.1.1.2 */
enum USIMM_SELECT_P1_PARA_ENUM
{
    USIMM_SELECT_BY_FILE_ID         = 0x00,   /* select DF,EF or MF by file id */
    USIMM_SELECT_CHILD_DF           = 0X01,   /* select child DF of the current DF */
    USIMM_SELECT_PARENT_DF          = 0X03,   /* select parent DF of the current DF */
    USIMM_SELECT_BY_DF_NAME         = 0x04,   /* selection by DF name,this is selection by AID */
    USIMM_SELECT_BY_PATH_FROM_MF    = 0x08,   /* select by path from MF */
    USIMM_SELECT_BY_PATH_FROM_CURDF = 0x09,   /* select by path from current DF */
    USIMM_SELECT_P1_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P1_PARA_ENUM_UINT8;


/* USIM卡select命令P2参数含义，协议TS102221 11.1.1.2 */
enum USIMM_SELECT_P2_PARA_ENUM
{
    USIMM_SELECT_ACTIVATE_AID         = 0x00,   /* Application session control,激活应用，仅当P1参数为04时，这个值才有意义 */
    USIMM_SELECT_TERMINATION_AID      = 0x40,   /* Application session control,终止应用，仅当P1参数为04时，这个值才有意义*/
    USIMM_SELECT_RETURN_FCP_TEMPLATE  = 0x04,   /* 需要带回FCP */
    USIMM_SELECT_NO_DATA_RETURNED     = 0x0C,   /* 没有数据带回 */
    USIMM_SELECT_P2_PARA_BUTT
};
typedef VOS_UINT8      USIMM_SELECT_P2_PARA_ENUM_UINT8;

enum USIMM_MANAGECH_P1_PARA_ENUM
{
    USIMM_MANAGECH_OPENCH             = 0x00,
    USIMM_MANAGECH_CLOSECH            = 0x01,
    USIMM_MANAGECH_P1_BUTT
};
typedef VOS_UINT8      USIMM_MANAGECH_P1_PARA_ENUM_UINT8;

enum USIMM_MANAGECH_P2_PARA_ENUM
{
    USIMM_MANAGECH_ASSIGNED_CARD      = 0x00,
    USIMM_MANAGECH_CH1                = 0x01,
    USIMM_MANAGECH_CH2                = 0x02,
    USIMM_MANAGECH_CH3                = 0x03,
    USIMM_MANAGECH_CH4                = 0x04,
    USIMM_MANAGECH_CH5                = 0x05,
    USIMM_MANAGECH_CH6                = 0x06,
    USIMM_MANAGECH_CH7                = 0x07,
    USIMM_MANAGECH_CH8                = 0x08,
    USIMM_MANAGECH_CH9                = 0x09,
    USIMM_MANAGECH_CH10               = 0x10,
    USIMM_MANAGECH_CH11               = 0x11,
    USIMM_MANAGECH_CH12               = 0x12,
    USIMM_MANAGECH_CH13               = 0x13,
    USIMM_MANAGECH_CH14               = 0x14,
    USIMM_MANAGECH_CH15               = 0x15,
    USIMM_MANAGECH_CH16               = 0x16,
    USIMM_MANAGECH_CH17               = 0x17,
    USIMM_MANAGECH_CH18               = 0x18,
    USIMM_MANAGECH_CH19               = 0x19,
    USIMM_MANAGECH_P2_BUTT
};
typedef VOS_UINT8      USIMM_MANAGECH_P2_PARA_ENUM_UINT8;

enum USIMM_RECORD_P2_PARA_ENUM
{
    USIMM_RECORD_NEXT                 = 0x02,
    USIMM_RECORD_PREVIOUS             = 0x03,
    USIMM_RECORD_ABSOLTE              = 0x04,
    USIMM_RECORD_P2_BUTT
};
typedef VOS_UINT8      USIMM_RECORD_P2_PARA_ENUM_UINT8;

enum USIMM_APDUCMD_ATTRIBUTE_ENUM
{
    USIMM_APDUCMD_COMMON            = 0x00,
    USIMM_APDUCMD_UIM               = 0x01,
    USIMM_APDUCMD_CSIM              = 0x02,
};
typedef VOS_UINT8      USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT8                   ucSW1;
    VOS_UINT8                   ucSW2;
    USIMM_SWCHECK_ENUM_UINT16   enResult;
}USIMM_SWCHECK_ST;

typedef struct
{
    VOS_UINT8                           ucINS;
    VOS_UINT8                           ucCLABit;
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute;
    VOS_UINT8                           ucRsv;
    PFAPDUFUNC                          pProcFun;
}USIMM_APDU_FUNC_LIST;

typedef struct
{
    VOS_UINT8                   ucChannel;
    VOS_UINT8                   ucINS;
    VOS_UINT8                   ucP1;
    VOS_UINT8                   ucP2;
    VOS_UINT8                   ucP3;
    VOS_UINT8                   aucRsv[3];
}USIMM_APDU_HEAD_STRU;

typedef struct
{
    VOS_UINT8                   ucChannel;
    VOS_UINT8                   ucCLA;
    VOS_UINT8                   ucINS;
    VOS_UINT8                   ucP1;
    VOS_UINT8                   ucP2;
    VOS_UINT8                   ucP3;
    VOS_UINT8                   aucRsv[2];
}USIMM_TPDU_HEAD_STRU;

typedef struct
{
    VOS_UINT8                   ucSW1;
    VOS_UINT8                   ucSW2;
    VOS_UINT8                   ucApduSW1;
    VOS_UINT8                   ucApduSW2;
    VOS_UINT16                  usRsv;
    VOS_UINT16                  usRspLen;
    VOS_UINT8                   aucRsp[USIMM_APDU_MAXLEN];
}USIMM_APDU_RSP_STRU;

typedef struct
{
    VOS_UINT32                  ulLeValue;                          /* 接收数据长度 */
    VOS_UINT32                  ulLcValue;                          /* 发送数据长度 */
    VOS_UINT32                  ulRecDataLen;
    VOS_UINT8                   ucResult;
    VOS_UINT8                   ucACK;                              /*接收的ACK*/
    VOS_UINT8                   ucSW1;                              /*命令结束后的SW1*/
    VOS_UINT8                   ucSW2;                              /*命令结束后的SW2*/
    VOS_UINT8                   ucApduSW1;                          /*命令第一次发送的SW1*/
    VOS_UINT8                   ucApduSW2;                          /*命令第一次发送的SW2*/
    VOS_UINT8                   aucAPDU[USIMM_APDU_HEADLEN];        /*命令的APDU*/
    VOS_UINT8                   aucGetRepAPDU[USIMM_APDU_HEADLEN];  /*Get Response命令的APDU*/
    VOS_UINT8                   aucRecvBuf[USIMM_APDU_MAXLEN];      /* 接收数据内容*/
    VOS_UINT8                   aucSendBuf[USIMM_APDU_MAXLEN];      /* 发送数据内容*/
}USIMM_TPDUDATA_STRU;


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMM_APDU_ST    gstUSIMMAPDU;

extern USIMM_SWCHECK_ST gausSimSWCheck[USIMM_SIMSW_MAXNUMBER];

extern USIMM_SWCHECK_ST gausUsimSWCheck[USIMM_USIMSW_MAXNUMBER];

/*****************************************************************************
  6 函数声明
*****************************************************************************/
extern VOS_UINT32 USIMM_CheckSW(
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucSW1,
    VOS_UINT8                           ucSW2);

extern VOS_UINT8 USIMM_MakeApduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucINS,
    VOS_UINT8                           ucCLABit,
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute);

extern VOS_UINT8 USIMM_MakeTpduCLA(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucCLA,
    VOS_UINT8                           ucINS);

extern VOS_UINT32 USIMM_UiccPinOperationResultProc(
    VOS_UINT8                           ucINS,
    VOS_UINT32                          ulResult);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SelectFile_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_Status_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageChannel_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_TerminalCapability_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_StoreESNMEID_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageSsd_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_ManageSsd_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_GenerateKeyVpm_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_BSChallenge_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendCase4_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulRetryCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendOneTime_APDU(
    USIMM_APDU_ST                       *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern USIMM_SENDAPDU_RESULT_ENUM_UINT32 USIMM_SendAndRetry_APDU(
    USIMM_APDU_ST                      *pstApduInfo,
    VOS_UINT32                          ulSendCnt);

extern VOS_VOID USIMM_MakeAPDUCmdData(
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_VOID USIMM_AttApduSWCheck(VOS_VOID);

extern USIMM_SWCHECK_ENUM_UINT32 USIMM_SendAPDUHandle(
    USIMM_APDUCMD_ATTRIBUTE_ENUM_UINT8  enAttribute,
    USIMM_APDU_HEAD_STRU                *pstApduHead,
    USIMM_U8_LVDATA_STRU                *pstApduData,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_UINT32 USIMM_T1SendIFSD_APDU(
    VOS_UINT8                           ucData);

extern USIMM_SWCHECK_ENUM_UINT32 USIMM_SendTPDUHandle(
    USIMM_TPDU_HEAD_STRU                *pstTpduHead,
    USIMM_U8_LVDATA_STRU                *pstTpduData,
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_UINT32 USIMM_SendStatusApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3);

extern VOS_UINT32 USIMM_SendStatusPollingApdu(
    USIMM_APDU_RSP_STRU                 *pstRspData);

extern VOS_UINT32 USIMM_SendCloseChannelApdu(
    VOS_UINT8                           ucP2);

extern VOS_UINT32 USIMM_SendOpenChannelApdu(
    VOS_UINT8                          *pucChannelID);

extern VOS_UINT32 USIMM_SendUpdateRecordApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucMode,
    VOS_UINT8                           ucRecordNum,
    VOS_UINT8                          *pucData,
    VOS_UINT8                           ucLen);

extern VOS_UINT32 USIMM_SendUpdateBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usLen,
    VOS_UINT8                           *pucData);

extern VOS_UINT32 USIMM_SendReadRecordApdu(
    VOS_UINT8                           ucChannel,
    VOS_UINT8                           ucTotalNum,
    VOS_UINT8                           ucRecordLen,
    VOS_UINT8                           ucRecordIndex,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32 USIMM_SendReadBinaryApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT16                          usOffset,
    VOS_UINT16                          usNeedLen,
    VOS_UINT8                           *pucContent);

extern VOS_UINT32 USIMM_SendUnblockPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPukData,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendChangePinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    VOS_UINT8                          *pucNewPinData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendVerifyPinApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPinType,
    VOS_UINT8                          *pucPinData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendTerminalCapabilityApdu(
        VOS_UINT8                           ucP1,
        VOS_UINT8                           ucP2,
        USIMM_TERMINAL_CAPABILITY_STRU     *pstTerminalCapability);

extern VOS_UINT32 USIMM_SendBSChallengeApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendGenerateKeyVpmApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendManageSsdApdu(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SendConfirmSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SendUpdateSsdApdu(
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SendAuthenticationApdu(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT8                           ucP1,
    VOS_UINT8                           ucP2,
    VOS_UINT8                           ucP3,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendDeactivateApdu(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_SendActivateApdu(
    VOS_UINT8                           ucChannelID);

extern VOS_UINT32 USIMM_SendTermimalProfileDownloadApdu(
    VOS_UINT8                           ucLen,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 USIMM_SendStoreESNMEIDApdu(
    UICC_STORE_ESN_MEID_P1_UINT8        enDataType,
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                          *pucData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendComputeIPApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_COMPUTEIP_AUTH_ENUM_UINT32	enP1,
    VOS_UINT8                           ucP2,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendBCMCSApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_BCMCS_AUTH_ENUM_UINT32	    enP1,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData);

extern VOS_UINT32 USIMM_SendAppAuthApdu(
    VOS_UINT8                           ucChannelID,
    USIMM_U8_DATA_STRU                 *pstCmdData,
    USIMM_APDU_RSP_STRU                *pstRspData);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#else

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "usimmbase.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*SW check定义*/
#define USIMM_SIMSW_MAXNUMBER      (24)
#define USIMM_USIMSW_MAXNUMBER     (40)

#define USIMM_STORE_ESNMEID_MAX     (8)
#define USIMM_BS_RANDSEED_MAX       (4)

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*SW定义值由于返回具体错误原因值需要移出到对外声明头文件中*/
typedef VOS_UINT16      USIMM_SWCHECK_ENUM_UINT16;

enum UICC_STORE_ESN_MEID_P1
{
    UICC_STORE_ESN_P1 = 0x00,
    UICC_STORE_MEID_P1= 0x01,
    UICC_STORE_ESN_MEID_P1_BUTT
};
typedef VOS_UINT8       UICC_STORE_ESN_MEID_P1_UINT8;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct
{
    VOS_UINT8                   ucSW1;
    VOS_UINT8                   ucSW2;
    USIMM_SWCHECK_ENUM_UINT16   enResult;
}USIMM_SWCHECK_ST;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMM_APDU_ST    gstUSIMMAPDU;

extern USIMM_SWCHECK_ST gausSimSWCheck[USIMM_SIMSW_MAXNUMBER];

extern USIMM_SWCHECK_ST gausUsimSWCheck[USIMM_USIMSW_MAXNUMBER];

/*****************************************************************************
  6 函数声明
*****************************************************************************/
extern VOS_UINT32 USIMM_CheckSW(USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_ReselectFileAPDU(USIMM_APDU_ST   *pstApduInfo);

extern VOS_UINT32 USIMM_SelectFile_APDU(USIMM_APDU_ST   *pstApduInfo);

extern VOS_UINT32 USIMM_Status_APDU(VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3);

extern VOS_UINT32 USIMM_ReadBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3);

extern VOS_UINT32 USIMM_UpdateBinary_APDU(VOS_UINT16 usOffset, VOS_UINT8 ucP3, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_ReadRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen);

extern VOS_UINT32 USIMM_UpdateRecord_APDU(VOS_UINT8 ucRecordNum, VOS_UINT8 ucMode, VOS_UINT8 ucLen, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_Search_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_Increase_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_PINVerify_APDU(VOS_UINT8 ucCmdType,VOS_UINT8 ucPINType, VOS_UINT8* pucPINData);

extern VOS_UINT32 USIMM_ChangePIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucOldPIN, VOS_UINT8* pucNewPIN);

extern VOS_UINT32 USIMM_UnblockPIN_APDU(VOS_UINT8 ucPINType, VOS_UINT8* pucPUKData, VOS_UINT8* pucPINData);

extern VOS_UINT32 USIMM_DeactivateFile_APDU(VOS_VOID);

extern VOS_UINT32 USIMM_ActivateFile_APDU(VOS_VOID);

extern VOS_UINT32 USIMM_Authentication_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucMode, VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);

extern VOS_UINT32 USIMM_Envelope_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_Fetch_APDU(VOS_UINT8 ucLen);

extern VOS_UINT32 USIMM_TerminalResponse_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_TermimalProfile_APDU(VOS_UINT8 ucLen, VOS_UINT8* pucData);

extern VOS_UINT32 USIMM_FormatCsimApdu(USIMM_GACCESS_REQ_STRU *pstMsg, USIMM_APDU_ST *pstUsimmApdu);

extern VOS_UINT32 USIMM_FormatIsdbApdu(USIMM_ISDB_ACCESS_REQ_STRU *pstMsg, USIMM_APDU_ST *pstUsimmApdu);

extern VOS_UINT32 USIMM_Manage_Channel_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, VOS_UINT8 ucP3);

extern VOS_UINT32 USIMM_Terminal_Capability_APDU(VOS_UINT8 ucP1, VOS_UINT8 ucP2, USIMM_TERMINAL_CAPABILITY_STRU *pstTerminalCapability);

extern VOS_UINT32 USIMM_SelectFileByChannelID_APDU(VOS_UINT8 ucChannelID, USIMM_APDU_ST *pstApduInfo);

extern VOS_UINT32 USIMM_StatusByChannelID_APDU(VOS_UINT8 ucChannelID, VOS_UINT8 ucP1,VOS_UINT8 ucP2,VOS_UINT8 ucP3);

extern VOS_UINT32 USIMM_FormatStandardApdu(VOS_UINT8 *pucData, VOS_UINT16 usLen, USIMM_APDU_ST *pstUsimmApdu);

extern VOS_UINT32 USIMM_T1SendIFSD_APDU(VOS_UINT8 ucData);

extern VOS_UINT32 USIMM_StoreESNMEID_APDU(UICC_STORE_ESN_MEID_P1_UINT8 enDataType, VOS_UINT8 *pucData, USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_UpdateSsdAPDU(VOS_UINT8  ucLen, VOS_UINT8 *pucData, USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_ConfirmSsdAPDU(VOS_UINT8 ucLen, VOS_UINT8 *pucData, USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_ManageSsdAPDU(VOS_UINT8 ucCmd, VOS_UINT8 ucLen, VOS_UINT8 *pucData, USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_GenerateKeyVpmAPDU(VOS_UINT8 ucLen, VOS_UINT8 *pucData, USIMM_APDU_ST *pstUSIMMAPDU);

extern VOS_UINT32 USIMM_BSChallengeAPDU(VOS_UINT8 *pucRandSeed, USIMM_APDU_ST *pstUSIMMAPDU);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif /* #if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of UsimmAPDU.h*/

