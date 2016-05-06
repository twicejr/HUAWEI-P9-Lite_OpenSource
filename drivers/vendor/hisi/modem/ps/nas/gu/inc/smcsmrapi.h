/********************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmcEnt.h
  Description : SMC实体结构定义
  History     :
      1.  张志勇   2004.2.24   新版作成
      2. Date         : 2007-08-20
         Author       : z40661
         Modification : 问题单号:A32D12705
      3.日    期   : 2010年1月9日
        作    者   : f62575
        修改内容   : 问题单号：AT2D16263，无效代码删除 SMC_SndEstReq外部引用
*******************************************************************************/
#ifndef _SMC_SMR_API_H_
#define _SMC_SMR_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */


#pragma pack(4)

/* 消息类型定义 */
#define MNSMS_DATA_REQ              0x00
#define MNSMS_DATA_IND              0x01
#define MNSMS_EST_REQ               0x02
#define MNSMS_EST_IND               0x03
#define MNSMS_ERROR_REQ             0x04
#define MNSMS_ERR_IND               0x05
#define MNSMS_ABORT_REQ             0x06
#define MNSMS_REL_REQ               0x07

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
#define NAS_SMS_RP_ERROR_OFFSET     (3)
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulDataLen;
    VOS_UINT8            aucData[4];
}MNSMS_DATA_REQ_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulDataLen;
    VOS_UINT8            aucData[4];
}MNSMS_EST_REQ_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulCause;
}MNSMS_ABORT_REQ_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulMtFlg;
    VOS_UINT32            ulCause;
}MNSMS_REL_REQ_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulMtFlg;
    VOS_UINT32            ulCause;
}MNSMS_ERR_IND_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulDataLen;
    VOS_UINT32            aucData[4];
}MNSMS_EST_IND_STRU;

typedef struct{
    MSG_HEADER_STRU  MsgHdr;
    VOS_UINT32            ulDataLen;
    VOS_UINT32            aucData[4];
}MNSMS_DATA_IND_STRU;


typedef VOS_VOID (*SMRSMC_DATA_REQ)(VOS_UINT8 *pucData, VOS_UINT16 usLen);
typedef VOS_VOID (*SMRSMC_EST_REQ)(VOS_UINT8 *pucData, VOS_UINT32 ulLen);
typedef VOS_VOID (*SMRSMC_ABORT_REQ)(VOS_UINT8 ucCause);
typedef VOS_VOID (*SMRSMC_REL_REQ)(VOS_UINT8 ucCause, VOS_UINT8 ucMtFlg);
typedef VOS_VOID (*SMRSMC_DATA_IND)(VOS_UINT8 *pucData, VOS_UINT32 ulLen);
typedef VOS_VOID (*SMRSMC_EST_IND)(VOS_UINT8 *pucData, VOS_UINT32 ulLen);
typedef VOS_VOID (*SMRSMC_ERROR_IND)(VOS_UINT8 ucCause, VOS_UINT8 ucMtFlg);
typedef struct sm_imported_func_list_stru
{
    SMRSMC_DATA_REQ SmrSmcDataReq;
    SMRSMC_EST_REQ SmrSmcEstReq;
    SMRSMC_ABORT_REQ SmrSmcAbortReq;
    SMRSMC_REL_REQ SmrSmcRelReq;
    SMRSMC_DATA_IND SmrSmcDataInd;
    SMRSMC_EST_IND SmrSmcEstInd;
    SMRSMC_ERROR_IND SmrSmcErrorInd;
}SMR_SMC_IMPORTED_FUNC_LIST_STRU;

extern SMR_SMC_IMPORTED_FUNC_LIST_STRU   g_SmrSmcApiFunc;                       /* api函数实体声明                          */

/* SmcSmrApi.c */

extern VOS_VOID SMC_SmrDataReq(VOS_UINT8 *pucData,VOS_UINT16 usLen);
extern VOS_VOID SMC_SmrEstReq(VOS_UINT8 *pucData,VOS_UINT32 ulLen);
extern VOS_VOID SMC_SmrAbortReq(VOS_UINT8     ucCause);
extern VOS_VOID SMC_SmrRelReq(VOS_UINT8     ucRelCause,VOS_UINT8     ucMtFlg);

extern VOS_UINT32 SMR_SmcApiDataInd(VOS_UINT8 *pucData,VOS_UINT32 ulLen);
/* 参数改变:增加接收域 */
extern VOS_UINT32 SMR_SmcApiEstInd(VOS_UINT8 *pucData,VOS_UINT32 ulLen, VOS_UINT8 ucRcvDomain);

/* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
extern VOS_VOID SMR_SmcApiErrorInd(
    SMR_SMT_ERROR_ENUM_UINT32           enErrorCode,
    VOS_UINT8                           ucMtFlag
);
/* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

extern VOS_VOID SMS_SmrApiDataReq(VOS_UINT8 *pucData,VOS_UINT16 usLen);
extern VOS_VOID SMS_SmrApiEstReq(VOS_UINT8 *pucData,VOS_UINT8 ucLen);
extern VOS_VOID SMS_SmrApiAbortReq(VOS_UINT8     ucCause);
extern VOS_VOID SMS_SmrApiRelReq(VOS_UINT8     ucRelCause,VOS_UINT8     ucMtFlg);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif

