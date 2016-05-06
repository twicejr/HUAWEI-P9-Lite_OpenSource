/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_sAtMsgPrint.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtMsgPrint.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATMSGPRINT_H__
#define __TEST_ATMSGPRINT_H__

/*****************************************************************************
  1 其他头文件包含                            
*****************************************************************************/
#include "ATCmdProc.h"
#include "product_config.h"
#include "AtMsgPrint.h"
#include "AtCheckFunc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义 
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID        PS_FILE_ID_AT_MSG_PRINT_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
  3 枚举定义 
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

extern VOS_UINT32  AT_AsciiNumberToBcd(
           const VOS_CHAR                      *pcAsciiNumber,
           VOS_UINT8                           *pucBcdNumber,
           VOS_UINT8                           *pucBcdLen
       );
extern VOS_UINT32  AT_AsciiToBcdCode(
           VOS_CHAR                            cAsciiCode,
           VOS_UINT8                          *pucBcdCode
       );
extern VOS_UINT32 AT_BcdAddrToAscii(
           MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
           MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr
       );
extern VOS_UINT32  AT_BcdNumberToAscii(
           const VOS_UINT8                     *pucBcdNumber,
           VOS_UINT8                           ucBcdLen,
           VOS_CHAR                            *pcAsciiNumber
       );
extern VOS_UINT32  AT_BcdToAsciiCode(
           VOS_UINT8                           ucBcdCode,
           VOS_CHAR                            *pcAsciiCode
       );
extern VOS_UINT32 AT_ChkSmsNumPlan(
           MN_MSG_NPI_ENUM_U8                  enNumPlan
       );
extern VOS_UINT32 AT_ChkSmsNumType(
           MN_MSG_TON_ENUM_U8                  enNumType
       );
extern TAF_UINT32 At_GetAbsoluteTime(
           TAF_UINT8                           *pucTimeStr,
           TAF_UINT16                          usTimeStrLen,
           MN_MSG_TIMESTAMP_STRU               *pstAbsoluteTime
       );
extern TAF_UINT32  At_GetAsciiOrBcdAddr(
           TAF_UINT8                           *pucAddr,
           TAF_UINT16                          usAddrLen,
           TAF_UINT8                           ucAddrType,
           TAF_UINT16                          usNumTypeLen,
           MN_MSG_ASCII_ADDR_STRU              *pstAsciiAddr,
           MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
       );
extern TAF_VOID At_GetCpmsMemStatus(
           MN_MSG_MEM_STORE_ENUM_U8            enMemType,
           TAF_UINT32                          *pulTotalRec,
           TAF_UINT32                          *pulUsedRec
       );
extern TAF_UINT8 *At_GetCpmsMemTypeStr(
           MN_MSG_MEM_STORE_ENUM_U8            enMemType
       );
extern VOS_VOID AT_GetCpmsMtMem(MN_MSG_MEM_STORE_ENUM_U8 *penSmMemStore);
extern TAF_VOID At_GetMsgFoValue(
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
           TAF_UINT8                           *pucFo
       );
extern TAF_UINT32  At_GetScaFromInputStr(
           const TAF_UINT8                     *pucAddr,
           MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
           TAF_UINT32                          *pulLen
       );
extern TAF_UINT32 At_MsgDeleteCmdProc(
           TAF_UINT8                           ucIndex,
           MN_OPERATION_ID_T                   opId,
           MN_MSG_DELETE_PARAM_STRU            stDelete,
           TAF_UINT32                          ulDeleteTypes
       );
extern TAF_UINT16 At_MsgPrintVp(
           MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod,
           TAF_UINT8 *pDst
       );
extern TAF_VOID At_MsgResultCodeFormat(
           TAF_UINT8                           ucIndex,
           TAF_UINT16                          usLength
       );
extern TAF_UINT32 At_ParseCsmpFo(
           TAF_UINT8                           *pucFo
       );
extern TAF_UINT32 At_ParseCsmpVp(
                                 VOS_UINT8                           ucIndex,
                                 MN_MSG_VALID_PERIOD_STRU           *pstVp
                                 );
extern TAF_UINT16  At_PrintAddrType(
           MN_MSG_ASCII_ADDR_STRU              *pstAddr,
           TAF_UINT8                           *pDst
       );
extern TAF_UINT16 At_PrintAsciiAddr(
           MN_MSG_ASCII_ADDR_STRU              *pstAddr,
           TAF_UINT8                           *pDst
       );
extern TAF_UINT16 At_PrintBcdAddr(
           MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
           TAF_UINT8                           *pDst
       );
extern TAF_VOID  At_PrintCsmsInfo(
           TAF_UINT8                           ucIndex
       );
extern TAF_VOID At_PrintGetCpmsRsp(
           TAF_UINT8                           ucIndex
       );
extern TAF_UINT32  At_PrintListMsg(
                                   VOS_UINT8                            ucIndex,
                                   MN_MSG_EVENT_INFO_STRU              *pstEvent,
                                   MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
                                   TAF_UINT8                           *pucDst
                                   );
extern TAF_UINT16  At_PrintMsgFo(
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
           TAF_UINT8                           *pDst
       );
extern TAF_VOID At_PrintSetCpmsRsp(
           TAF_UINT8                           ucIndex
       );
extern TAF_VOID AT_PrintTimeZone(
           TAF_INT8                            cTimezone,
           TAF_UINT8                           *pucDst,
           TAF_UINT16                          *pusLength
       );
extern AT_CGSMS_SEND_DOMAIN_ENUM_U8 At_SendDomainNvimToProto(
           VOS_UINT32                           ulNvimSendDomain
       );
extern VOS_UINT32 At_SendDomainProtoToNvim(
           AT_CGSMS_SEND_DOMAIN_ENUM_U8        enProtoSendDomain
       );
extern VOS_VOID At_SendMsgFoAttr(
           VOS_UINT8                           ucIndex,
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
       );
extern VOS_UINT32  AT_SetAbsoluteValidPeriod(
           VOS_UINT8                           ucIndex,
           TAF_UINT8                          *pucPara,
           TAF_UINT16                          usParaLen,
           MN_MSG_VALID_PERIOD_STRU           *pstValidPeriod
        );
extern VOS_UINT32  AT_SetRelativeValidPeriod(
           VOS_UINT8                           ucIndex,
           TAF_UINT8                           *pucPara,
           TAF_UINT16                          usParaLen,
           MN_MSG_VALID_PERIOD_STRU            *pstValidPeriod
       );
extern TAF_UINT32 At_SmsPrintScts(
           const MN_MSG_TIMESTAMP_STRU         *pstTimeStamp,
           TAF_UINT8                           *pDst
       );
extern TAF_UINT32 At_SmsPrintState(
           AT_CMGF_MSG_FORMAT_ENUM_U8          enSmsFormat,
           MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
           TAF_UINT8                           *pDst
       );
extern TAF_VOID AT_StubClearSpecificAutoRelyMsg(
           VOS_UINT8                           ucClientIndex,
           TAF_UINT32                          ulBufferIndex
       );
extern TAF_VOID AT_StubSaveAutoReplyData(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU             *pstEvent,
           MN_MSG_TS_DATA_INFO_STRU           *pstTsDataInfo
    );
extern TAF_UINT32 AT_StubSendAutoReplyMsg(
           VOS_UINT8                            ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent,
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
       );
extern TAF_VOID AT_StubTriggerAutoReply(
                                        VOS_UINT8                           ucIndex,
                                        TAF_UINT8                           ucCfgValue
                                        );


extern TAF_UINT32 At_StubSendAutoReplyMsg(
    VOS_UINT8                            ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent,
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
    );



extern void UT_STUB_INIT(void);

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

#endif /* end of Test_AtMsgPrint.h */
