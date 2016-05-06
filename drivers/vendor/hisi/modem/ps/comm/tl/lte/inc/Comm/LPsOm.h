/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LPsOm.h
  Description     : PsOm.c header file
  History         :
     1.XiaoJun 58160       2009-3-19     Draft Enact
     2.XiaoJun 58160       2010-1-12     BJ9D02643,自动开机
     3.guojiyu 00149868   2010-02-1  BJ9D02655:规划修改NV项信息,把锁频、锁小区以及NV读取失败的处理综合考虑
     4.guojiyu 00149868   2010-3-11 BJ9D02829:HPA模块中增加软调信息
     5.guojiyu 00149868        2010-4-28 BJ9D02900:合入时延统计
     6.guojiyu 00149868  2010-5-14 BJ9D02926:RRC流程优化修改
	 7.wangyue 151278       2011-11-26 DTS2011112400987: 时延优化
******************************************************************************/

#ifndef __PSOM_H__
#define __PSOM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "PsLogdef.h"
#include  "PsCommonDef.h"
#include  "msp.h"
#include  "LPSCommon.h"
#include  "OmCommon.h"
#include  "AppRrcInterface.h"
#include  "LPsNvInterface.h"
#include  "TLPsPrintDict.h"
#if (VOS_OS_VER != VOS_WIN32)
#include  "securec.h"
#endif

/*#include  "LHpaMsgDebug.h" deleted by hujianbo 20130809:产品线裁剪代码时不能包含非开放头文件，故将其去掉*/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define  MAX_HMAC_HASH_SIZE              32  /* KDF算法用到的最大HMAC长度 */
#define  LPS_GAS_OM_OTA_IND                 0xA025

#define  LPS_GNAS_OM_OTA_IND                0xC103

#define  LPS_WAS_OM_OTA_IND                 0XB022

#define  EN_NV_ID_TEST_MODE_FLAG            6656

#define TLRRC_VERSION_V9R1                  0x91

#define TLRRC_VERSION_V7R2                  0x72

#define TLRRC_VERSION_V7R1                  0x71

#define TLRRC_FEATURE_ON                    1
#define TLRRC_FEATURE_OFF                   0
#define TLRRC_FEATURE_STK_V9R1              TLRRC_FEATURE_ON

#define  TLRRC_VERSION                      TLRRC_VERSION_V7R2

/*g_astMsgIdToPidTbl表格里最少的message id的界限个数*/
#define LPS_OM_MSG_TABLE_MIN_NUM             2

/*VOS_PID_BUTT无效的PID*/
#define LPS_PID_NULL                         VOS_PID_BUTT

#define LPS_OM_SPECIFY_FLG                   (0x0000000FUL)

#define TLRRC_FEATURE_ON                    1
#define TLRRC_FEATURE_OFF                   0

#define TLRRC_FAST_CSFB_FEATURE             TLRRC_FEATURE_ON
#define LHPA_DATA_ABORT_LAST_MSG           16

/*32KTime Stamp翻转一次对应的时间，秒级单位，对应右移位数*/
#define TLPS_32TSTAMP_HIGHBIT_MOVE_BIT_IN_SECOND  (17)

/*32KTime Stamp和秒的对应关系，除以32768，即左移15位*/
#define TLPS_32TSTAMP_ACCURACY_MOVE_BIT_IN_SECOND       (15)

/*32KTime Stamp 高位最大值，如果差值大于此值，即按照32位计秒达到溢出*/
#define TLPS_32TSTAMP_MAX_HIGH_VAL       (0x7FFFUL)

/* 32KTime Stamp和毫秒的对应关系，除以32.768 */
#define TLPS_32TSTAMP_ACCURACY_IN_MILL_SECOND      (32.768)

/*32KTime Stamp 高位最大值，如果差值大于此值，即按照毫秒记差值达到溢出*/
#define TLPS_32TSTAMP_MAX_HIGH_VAL_MILL_SECOND     (0x20UL)

/*TLPSPRINT2LAYER  打印参数无效值 l00285345*/
#define TLPS_PRINT2LAYER_INVALID_VALUE     (0xa5a5a5a5)

#if (VOS_OS_VER != VOS_WIN32)
#define PS_LOG_RETURN() \
            if(0 != g_ulTimeDelaySwitch) \
            {\
              return;\
            }

#define PS_LOG_RETURN_SUCC() \
            if(0 != g_ulTimeDelaySwitch) \
            {\
              return VOS_OK;\
            }

#define PS_HOOK_LOG_RETURN_SUCC() \
            if(0 != g_ulTimeDelayHookSwitch) \
            {\
              return VOS_OK;\
            }

#else
#define PS_LOG_RETURN()

#define PS_LOG_RETURN_SUCC()

#define PS_HOOK_LOG_RETURN_SUCC()
#endif

/*LOG打印*/
#define LPS_OM_INFO_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString)

#define LPS_OM_INFO_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString, lPara1)

#define LPS_OM_INFO_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString, lPara1,lPara2)

#define LPS_OM_WARNING_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString)

#define LPS_OM_WARNING_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString, lPara1)

#define LPS_OM_WARNING_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString, lPara1,lPara2)

#define LPS_OM_ERROR_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString)

#define LPS_OM_ERROR_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString, lPara1)

#define LPS_OM_ERROR_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString, lPara1,lPara2)



/*PS处理完APP发送来的消息后，把消息的空间释放*/
#define LPS_OM_FREE_APP_MSG_MEM(pAddr)   PS_MEM_FREE(PS_PID_OM, pAddr);

/* 获得时延统计信息 */
#define LPS_OM_Get_LATENCY_INFO() (&g_stPsLatencyStat)

#if (VOS_OS_VER != VOS_WIN32)
/* 设置HO流程时延 */
#define LPS_HO_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stHoLatency.aulHoLatency, ucLatencyType, LPS_HO_LATENCY_BUFF);\
}
/* 设置建链接时延 */
#define LPS_EST_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stEstLatency.aulEstLatency, ucLatencyType, LPS_EST_LATENCY_BUFF);\
}
/* 设置重建时延 */
#define LPS_REEST_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stReestLatency.aulReestLatency, ucLatencyType, LPS_REEST_LATENCY_BUFF);\
}

/* 获得建链控制面时延是否有效标志 */
#define LPS_EST_GET_LATENCY_FLAG() (g_stPsLatencyStat.stEstLatency.enContralPlaneValidFlag)

#define LPS_EST_SET_LATENCY_FLAG(ulFlag) (g_stPsLatencyStat.stEstLatency.enContralPlaneValidFlag = ulFlag)

/* 获得重建时延是否有效标志 */
#define LPS_REEST_GET_LATENCY_FLAG() (g_stPsLatencyStat.stReestLatency.enReestValidFlag)

#define LPS_REEST_SET_LATENCY_FLAG(ulFlag) (g_stPsLatencyStat.stReestLatency.enReestValidFlag = ulFlag)



/* mod by guojiyu 可维可测切换时延 begin */
#define LPS_GET_HO_LatencyInfo()            (&g_stPsHoInfo)

#define LPS_HO_GET_HO_TYPE()                (g_stPsHoInfo.enHoType)
#define LPS_HO_SET_HO_TYPE(enHoType)        (LPS_HO_GET_HO_TYPE() = (enHoType))

#define LPS_GET_HO_LatestHOLatency()        (g_stPsHoInfo.usLatestHOLatency)
#define LPS_GET_HO_HoLatencyInfo(enHoType)  (g_stPsHoInfo.astHOLatencyInfo + (enHoType))

#define LPS_GET_HO_AllSuccTime(enHoType)    (g_stPsHoInfo.aulAllHoSuccTime[enHoType])
/* mod by guojiyu 可维可测切换时延 end */
#define LPS_OM_GET32K_TIMESTAMP(pulHigBit,pulLowBit)  (VOS_VOID)mdrv_timer_get_accuracy_timestamp((pulHigBit),(pulLowBit))
#else
#define LPS_HO_SET_LATENCY_TIME(ucLatencyType)
/* 设置建链接时延 */
#define LPS_EST_SET_LATENCY_TIME(ucLatencyType)
/* 设置重建时延 */
#define LPS_REEST_SET_LATENCY_TIME(ucLatencyType)


/* 获得建链控制面时延是否有效标志 */
#define LPS_EST_GET_LATENCY_FLAG()                                  PS_FALSE

#define LPS_EST_SET_LATENCY_FLAG(ulFlag)

/* 获得重建时延是否有效标志 */
#define LPS_REEST_GET_LATENCY_FLAG()                                PS_FALSE

#define LPS_REEST_SET_LATENCY_FLAG(ulFlag)

/* mod by guojiyu 可维可测切换时延 begin */
#define LPS_GET_HO_LatencyInfo()

#define LPS_HO_GET_HO_TYPE()
#define LPS_HO_SET_HO_TYPE(enHoType)

#define LPS_GET_HO_LatestHOLatency()
#define LPS_GET_HO_HoLatencyInfo(enHoType)

#define LPS_GET_HO_AllSuccTime(enHoType)
/* mod by guojiyu 可维可测切换时延 end */

#define LPS_OM_GET32K_TIMESTAMP(pulHigBit,pulLowBit)  mdrv_timer_get_accuracy_timestamp((pulHigBit),(pulLowBit))


#endif
/*TDS begin*/

#if ((!defined(_lint)) && (PRINT_SWITCH == PRINT_OFF) && (VOS_WIN32 != VOS_OS_VER))

#define tra01_10tdynamicTrace(pcString, ...)
#define tgl01_21dynamicTraceToLog(pcString, ...)
#define fpv01_30SpvDynamicTraceToLog(pcString, ...)
#define fpv01_32AtrDynamicTraceToLog(pcString, ...)
#define fpv01_33AtcDynamicTraceToLog(pcString, ...)
#define fpv01_31SimDynamicTraceToLog(pcString, ...)
#define tra06_40dynamicTrace(ulId,pcString, ...)

#else
#define tra01_10tdynamicTrace TDS_OM_DiagPrint
#define tgl01_21dynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_30SpvDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_32AtrDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_33AtcDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_31SimDynamicTraceToLog TDS_OM_DiagPrint
#define tra06_40dynamicTrace TDS_OM_DiagPrint1
#endif
/*TDS end*/


#define LPS_GET_NV_MEAS_THRESHOLD()                      (&g_LPsNvCellMeasThredhold)

#define LPS_GET_NV_RSRP_THRESHOLD()                      (g_LPsNvCellMeasThredhold.sRsrpHoldThreshold) /* PHY上报的测量值小于某值 ucRsrpLowCount++*/
#define LPS_SET_NV_RSRP_THRESHOLD(sRsrpHoldThreshold)    (LPS_GET_NV_RSRP_THRESHOLD() = (sRsrpHoldThreshold)) /* PHY上报的测量值小于某值 ucRsrpLowCount++*/

#define LPS_GET_NV_RSRP_LOW_CONT()                       (g_LPsNvCellMeasThredhold.ucRsrpLowCount)  /* PHY上报的测量值小于sRsrpHoldThreshold达到两次。发起重建流程 */
#define LPS_SET_NV_RSRP_LOW_CONT(ucRsrpLowCount)         (LPS_GET_NV_RSRP_LOW_CONT() = (ucRsrpLowCount))  /* PHY上报的测量值小于sRsrpHoldThreshold达到两次。发起重建流程 */

#define LPS_GET_NV_SYNSSWITCH()                           (g_LPsNvCellMeasThredhold.ucSynsSwitch) /*是否启动测量值掉底发起重建流程 */
#define LPS_SET_NV_SYNSSWITCH(ucSynsSwitch)               (LPS_GET_NV_SYNSSWITCH() = (ucSynsSwitch)) /*是否启动测量值掉底发起重建流程 */


#define LPS_VERSION_V_NO                     (700)                                 /* V版本号 */
#define LPS_VERSION_R_NO                     (  1)                                 /* R版本号 */
#define LPS_VERSION_C_NO                     ( 10)                                 /* C版本号 */
#define LPS_VERSION_B_NO                     ( 60)                                 /* B版本号 */
#define LPS_VERSION_SPC_NO                   (000)                                 /* SPC版本号 */
#define LPS_VERSION_PRODUCT_NO               (1)                                   /* Product Version */

/* Print To Layer Begin */

#define TLPS_TIMER_LENGTH_OF_SEND_PRINT               (8000)
#define TLPS_PRINT_NUM_OF_BUFFER                      (3)
#if (VOS_OS_VER != VOS_WIN32)
#define TLPS_LOG_GetSendPrintFlagTimerAddr()   (&(g_stSendPrintFlagTimer))

#define TLPS_LOG_GetBufferTimer()              (TLPS_LOG_GetSendPrintFlagTimerAddr()->pucSendPrintTimer)
#define TLPS_LOG_GetSendFlag()                 (TLPS_LOG_GetSendPrintFlagTimerAddr()->enSendFlag)
#define TLPS_LOG_SetSendFlag(enFlag)           (TLPS_LOG_GetSendFlag() = (enFlag))

#define TLPS_LOG_GetPrintLevel()            (TLPS_LOG_GetSendPrintFlagTimerAddr()->enPrintLevel)
#define TLPS_LOG_SetPrintLevel(enLevel)     (TLPS_LOG_GetPrintLevel() = (enLevel))

#define TLPS_LOG_GetPrintInfoIndAddr()         (&(g_stPrintInfoInd))

#define TLPS_LOG_GetPrintListAddr()            (&(g_stPrintInfoList))
#define TLPS_LOG_GetSendPrintListAddr(ucIndex) (&(g_astSendPrintInfoList[ucIndex]))
#define TLPS_LOG_GetSendPrintListFLAG(ucIndex) (TLPS_LOG_GetSendPrintListAddr(ucIndex)->enFlag)

#define TLPS_LOG_GetCntofPrint()               (TLPS_LOG_GetPrintListAddr()->usCntofPrint)
#define TLPS_LOG_SetCntofPrint(usNum)          (TLPS_LOG_GetCntofPrint() = (usNum))

#define TLPS_LOG_GetPrintInfo(usCnt)             (&(TLPS_LOG_GetPrintListAddr()->astPrintInfo[(usCnt)]))

#define TLPS_LOG_GetStartTimeStampLow32(usCnt)              (TLPS_LOG_GetPrintInfo(usCnt)->ulStartTimeStampLow32)
#define TLPS_LOG_SetStartTimeStampLow32(usCnt, ulTimeStamp) (TLPS_LOG_GetStartTimeStampLow32(usCnt) = (ulTimeStamp))

#define TLPS_LOG_GetStartTimeStampHigh16(usCnt)             (TLPS_LOG_GetPrintInfo(usCnt)->usStartTimeStampHigh16)
#define TLPS_LOG_SetStartTimeStampHigh16(usCnt, usTimeStamp)(TLPS_LOG_GetStartTimeStampHigh16(usCnt) = (usTimeStamp))


#define TLPS_LOG_SetPrintInfoFunctionID(usCnt, enInFunctionId)  \
                                (TLPS_LOG_GetPrintInfo(usCnt)->enFunctionId = (enInFunctionId))

#define TLPS_LOG_SetPrintInfoProcFlag(usCnt, enInProcFlag) \
                                (TLPS_LOG_GetPrintInfo(usCnt)->enProcFlag = (enInProcFlag))

#define TLPS_LOG_SetPrintInfoPara1(usCnt, lInPara1)  \
                                (TLPS_LOG_GetPrintInfo(usCnt)->lPara1 = (lInPara1))

#define TLPS_LOG_SetPrintInfoPara2(usCnt, lInPara2) \
                                (TLPS_LOG_GetPrintInfo(usCnt)->lPara2 = (lInPara2))
#else
#define TLPS_LOG_SetPrintLevel(enLevel)
#endif
/***************************PRINT2LAYER  接口 begin*************************/
#if ((PRINT2LAYER_SWITCH == PRINT_OFF) || (VOS_OS_VER == VOS_WIN32))
#define TLPS_PRINT2LAYER_INFO(enFunction, enProcFlag)

#define TLPS_PRINT2LAYER_INFO1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_INFO2(enFunction, enProcFlag, lPara1, lPara2)

#define TLPS_PRINT2LAYER_WARNING(enFunction, enProcFlag)
#define TLPS_PRINT2LAYER_WARNING1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_WARNING2(enFunction, enProcFlag, lPara1, lPara2)

#define TLPS_PRINT2LAYER_ERROR(enFunction, enProcFlag)

#define TLPS_PRINT2LAYER_ERROR1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_ERROR2(enFunction, enProcFlag, lPara1, lPara2)
#else

#define TLPS_PRINT2LAYER_INFO(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_INFO1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_INFO2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#define TLPS_PRINT2LAYER_WARNING(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_WARNING1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_WARNING2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#define TLPS_PRINT2LAYER_ERROR(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_ERROR1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_ERROR2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag),(VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#endif

#define TLPS_SECU_FUNCTION_ERRNO                                (0xA0110000)
#define TLPS_SECU_FUNCTION_ERR_MAXNO                             10

#define TLPS_GetSecuFuncInfoIndex()                              g_stSecuFuncInfoList.usIndex
#define TLPS_SetSecuFuncInfoIndex(Index)                         TLPS_GetSecuFuncInfoIndex() = (Index)

#define TLPS_GetSecuFuncInfoCnt()                                g_stSecuFuncInfoList.usCnt
#define TLPS_SetSecuFuncInfoCnt(Cnt)                             TLPS_GetSecuFuncInfoCnt() = (Cnt)

#define TLPS_GetSecuFuncInfoAddr()                               (&(g_stSecuFuncInfoList.astSecuFuncInfo[TLPS_GetSecuFuncInfoIndex()]))
#define TLPS_SetSecuFuncInfoSecuFuncType(PSSecuFuncType)          TLPS_GetSecuFuncInfoAddr()->enSecuFuncType = (PSSecuFuncType)
#define TLPS_SetSecuFuncInfoErrNo(PSErroNo)                       TLPS_GetSecuFuncInfoAddr()->sErrNo = (PSErroNo)
#define TLPS_SetSecuFuncInfoDst(PSDst)                            TLPS_GetSecuFuncInfoAddr()->pDst = (PSDst)
#define TLPS_SetSecuFuncInfoMaxBuffer(PSMaxBuffer)                TLPS_GetSecuFuncInfoAddr()->ulMaxBuffer = (PSMaxBuffer)
#define TLPS_SetSecuFuncInfoSrc(PSSrc)                            TLPS_GetSecuFuncInfoAddr()->pSrc = (PSSrc)
#define TLPS_SetSecuFuncInfoLength(PSLength)                      TLPS_GetSecuFuncInfoAddr()->ulLength = (PSLength)
#define TLPS_SetSecuFuncInfoLineNO(LineNO)                        TLPS_GetSecuFuncInfoAddr()->ulLineNO = (LineNO)
#define TLPS_SetSecuFuncInfoFileID(FileID)                        TLPS_GetSecuFuncInfoAddr()->ulFileID = (FileID)
#define TLPS_SetSecuFuncInfoTimeStamp(TimeStamp)                  TLPS_GetSecuFuncInfoAddr()->ulTimeStamp = (TimeStamp)

#if (VOS_OS_VER == VOS_WIN32)
/* 安全函数返回值 */
#define TLPS_EOK                  0
#define TLPS_ERANGE               34
#define TLPS_EINVAL               22
#define TLPS_EINVAL_AND_RESET     150
#define TLPS_ERANGE_AND_RESET     162
#define TLPS_EOVERLAP_AND_RESET   182

#define TLPS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID ) \
            memcpy_s(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength)

#define TLPS_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID ) \
            memmove_s(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength)

/* windows没有memset_s */
#define TLPS_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength, ulLineNO, ulFileID ) \
            memset(pDestBuffer, ucData, ulLength)

#else
/* 安全函数返回值 */
#define TLPS_EOK                  EOK
#define TLPS_ERANGE               ERANGE
#define TLPS_EINVAL               EINVAL
#define TLPS_EINVAL_AND_RESET     EINVAL_AND_RESET
#define TLPS_ERANGE_AND_RESET     ERANGE_AND_RESET
#define TLPS_EOVERLAP_AND_RESET   EOVERLAP_AND_RESET

#ifdef _lint
#define TLPS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID ) \
            memcpy_s(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength)

#define TLPS_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID ) \
            memmove_s(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength)
#define TLPS_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength, ulLineNO, ulFileID ) \
            memset_s(pDestBuffer, ulMaxDest, ucData, ulLength)
#else
#define TLPS_MEM_CPY_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID) \
            TLPS_Mem_Cpy_Secu((VOS_VOID *)(pDestBuffer), (VOS_UINT32)(ulMaxDest), (VOS_VOID *)(pSrcBuffer), (VOS_UINT32)(ulLength),\
                                (VOS_UINT32)(ulLineNO), (VOS_UINT32)(ulFileID))
#define TLPS_MEM_SET_S(pDestBuffer, ulMaxDest, ucData, ulLength, ulLineNO, ulFileID ) \
            TLPS_Mem_Set_Secu((VOS_VOID *)(pDestBuffer), (VOS_UINT32)(ulMaxDest), (VOS_UINT8)(ucData), (VOS_UINT32)(ulLength),\
                                (VOS_UINT32)(ulLineNO), (VOS_UINT32)(ulFileID))
#define TLPS_MEM_MOVE_S(pDestBuffer, ulMaxDest, pSrcBuffer, ulLength, ulLineNO, ulFileID ) \
            TLPS_Mem_Move_Secu((VOS_VOID *)(pDestBuffer), (VOS_UINT32)(ulMaxDest), (VOS_VOID *)(pSrcBuffer), (VOS_UINT32)(ulLength),\
                                    (VOS_UINT32)(ulLineNO), (VOS_UINT32)(ulFileID))
#endif
#endif
/***************************PRINT2LAYER  接口 end*************************/


/* Print To Layer End  */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 结构名    : LPS_PRINT_LOCATION_ENUM
 结构说明  : LRRC打印时用于标记代码位置的枚举
*****************************************************************************/
enum LPS_PRINT_LOCATION_ENUM
{
    LPS_PRINT_LOCATION_1 = 1,
    LPS_PRINT_LOCATION_2,
    LPS_PRINT_LOCATION_3,
    LPS_PRINT_LOCATION_4,
    LPS_PRINT_LOCATION_5,
    LPS_PRINT_LOCATION_6,
    LPS_PRINT_LOCATION_7,
    LPS_PRINT_LOCATION_8,
    LPS_PRINT_LOCATION_9,
    LPS_PRINT_LOCATION_10,
    LPS_PRINT_LOCATION_11,
    LPS_PRINT_LOCATION_12,
    LPS_PRINT_LOCATION_13,
    LPS_PRINT_LOCATION_14,
    LPS_PRINT_LOCATION_15,
    LPS_PRINT_LOCATION_BUTT
};
typedef VOS_UINT32 LPS_PRINT_LOCATION_ENUM_UINT32;

/* mod by guojiyu 0xffff begin */
/*****************************************************************************
 结构名    : LPS_HO_TYPE_ENUM
 结构说明  : 切换类型枚举
*****************************************************************************/
enum LPS_HO_TYPE_ENUM
{
    LPS_INTRA_FREQ_HO = 0,
    LPS_INTER_FREQ_HO,
    LPS_INTER_RAT_HO,
    LPS_HO_TYPE_BUFF
};
typedef VOS_UINT8 LPS_HO_TYPE_ENUM_UINT8;
/* mod by guojiyu 0xffff END */

/*****************************************************************************
 结构名    : LPS_HO_LATENCY_ENUM
 结构说明  : 切换时延阶段枚举
*****************************************************************************/
enum LPS_HO_LATENCY_ENUM
{
    LPS_HO_LATENCY_LRRC_SND_MEAS_RPT = 0,/* mod by guojiyu 0xffff begin */
    LPS_HO_LATENCY_LRRC_RCV_HO_RECFG,
    LPS_HO_LATENCY_LRRC_RCV_NAS_RABM_RSP,
    LPS_HO_LATENCY_LRRC_RCV_CMM_HO_CNF,
    LPS_HO_LATENCY_LRRC_RCV_STOP_PDCP_CNF,
    LPS_HO_LATENCY_LRRC_SND_DSP_HO_REQ,
    LPS_HO_LATENCY_LRRC_RCV_DSP_HO_CNF,
    LPS_HO_LATENCY_LRRC_SND_MAC_RA_REQ,
    LPS_HO_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_HO_LATENCY_LMAC_RCV_RAR,
    LPS_HO_LATENCY_LRRC_RCV_MAC_RA_CNF,
    LPS_HO_LLATENCY_RRC_SND_SMC_SECU_CFG,
    LPS_HO_LATENCY_LRRC_SND_RECFG_CMP,
    LPS_HO_LATENCY_LRRC_RCV_AM_DATA_CNF,
    LPS_HO_LATENCY_LRRC_RCV_CQI_SRS_CNF,
    LPS_HO_LATENCY_LRRC_RCV_PDCP_CONTINUE_CNF,
    LPS_HO_LATENCY_LRRC_RCV_RABM_STATUS_RSP,
    LPS_HO_LATENCY_BUFF
};

/*****************************************************************************
 结构名    : LPS_REEST_LATENCY_ENUM
 结构说明  : 重建时延阶段枚举
*****************************************************************************/
enum LPS_REEST_LATENCY_ENUM
{
    LPS_REEST_LATENCY_LRRC_RCV_REESTIND,
    LPS_REEST_LATENCY_LRRC_SND_CELL_SEARCH_REQ,
    LPS_REEST_LATENCY_LRRC_RCV_CELLSEARCH_IND,
    LPS_REEST_LATENCY_LRRC_RCV_SI,
    LPS_REEST_LATENCY_LRRC_CAMP_REQ,
    LPS_REEST_LATENCY_LRRC_CAMP_CNF,
    LPS_REEST_LATENCY_LRRC_SND_LMAC_RA_REQ ,
    LPS_REEST_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_REEST_LATENCY_LMAC_RCV_RAR,
    LPS_REEST_LATENCY_LRRC_RCV_LMAC_RA_CNF,
    LPS_REEST_LATENCY_LMAC_SND_MSG3,
    LPS_REEST_LATENCY_LRRC_RCV_REEST,
    LPS_REEST_LATENCY_LRRC_SND_REEST_CMPL,
    LPS_REEST_LATENCY_BUFF
};
typedef VOS_UINT8 LPS_REEST_LATENCY_ENUM_UINT8;

/*****************************************************************************
 结构名    : LPS_EST_LATENCY_ENUM
 结构说明  : 控制面时延阶段枚举
*****************************************************************************/
enum LPS_EST_LATENCY_ENUM
{
    LPS_EST_LATENCY_LRRC_SND_LMAC_RA_REQ = 0,
    LPS_EST_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_EST_LATENCY_LMAC_RCV_RAR,
    LPS_EST_LATENCY_LRRC_RCV_LMAC_RA_CNF,
    LPS_EST_LATENCY_LMAC_SND_MSG3,
    LPS_EST_LATENCY_LRRC_RCV_SETUP,
    LPS_EST_LATENCY_LRRC_SND_SETUP_CMP,
    LPS_EST_LATENCY_LRRC_RCV_CAP_ENQ,
    LPS_EST_LATENCY_LRRC_SND_CAP_INFO,
    LPS_EST_LATENCY_LRRC_RCV_SEC_CMD,
    LPS_EST_LATENCY_LRRC_RCV_RECFG,
    LPS_EST_LATENCY_LRRC_SND_SEC_CMD_CMP,
    LPS_EST_LATENCY_LRRC_SND_RECFG_CMP,
    LPS_EST_LATENCY_BUFF
};
typedef VOS_UINT8 LPS_EST_LATENCY_ENUM_UINT8;

/*****************************************************************************
 枚举名    : LPS_REBOOT_MOD_ID_ENUM
 枚举说明  : 当前重启的ID类型
 1.日    期   : 2011年12月13日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
enum LPS_REBOOT_MOD_ID_ENUM
{
    LPS_REBOOT_MOD_ID_MML   = 0Xa0000000,
    LPS_REBOOT_MOD_ID_BUTT  = 0X6FFFFFFF
};
typedef VOS_UINT32 LPS_REBOOT_MOD_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TL_KPI_TYPE_ENUM
 枚举说明  : KPI类型枚举
 1.日    期   : 2015年6月3日
   作    者   : leixiantiao 00258641
   修改内容   : 新建
*****************************************************************************/
typedef enum
{
    TL_KPI_TYPE_EST         = 0x0,
    TL_KPI_TYPE_KEEP        = 0x1,
    TL_KPI_TYPE_MOBILITY    = 0x2,
    TL_KPI_TYPE_DELAY       = 0x3,
    TL_KPI_TYPE_BUTT
}TL_KPI_TYPE_ENUM;
typedef VOS_UINT32 TL_KPI_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : TLPS_PID_ENUM
 枚举说明  : 模块对应的下标
 1.日    期   : 2015年5月25日
   作    者   : l00285345
   修改内容   : 新建
*****************************************************************************/

enum TLPS_PRINT_LEVEL_ENUM
{
    TLPS_PRINT_INFO = 0,
    TLPS_PRINT_WARNING,
    TLPS_PRINT_ERROR,
    TLPS_PRINT_CLOSE,
    TLPS_PRINT_BUTT
};
typedef VOS_UINT8 TLPS_PRINT_LEVEL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : SECU_FUNC_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 安全函数定义
*****************************************************************************/
enum SECU_FUNC_TYPE_ENUM
{
    MEM_CPY_TYPE  = 0,
    MEM_SET_TYPE     ,
    MEM_MOVE_TYPE    ,
    MEM_SECU_BUTT
};
typedef VOS_UINT8   SECU_FUNC_TYPE_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


#define TLPS_EXC_BUILD_MSG_PID(ulSendPid, ulRcvPid) \
            ((ulSendPid << 16) | (ulRcvPid & 0xffff))

#define TLPS_EXC_MSG_PRIVATE_OFFSET        6
#define TLPS_EXC_MAX_SAVE_MSG_NUM          200
#define TLPS_EXC_HPA_SEND_FAIL_MSG_NUM      8

typedef struct
{
    VOS_UINT32 ulTimeStamp; /* 时间戳*/
    VOS_UINT32 ulCompPid;   /* ulSendPid | ulRcvPid */
    VOS_UINT32 ulMsgId;     /* 消息ID */
    VOS_UINT32 ulPrivate;   /* 用来保存一些重要消息的关键参数*/
}TLPS_EXC_MSG_ELEMENT_STRU;


typedef struct
{
    VOS_UINT32                ulNextIndex;
    TLPS_EXC_MSG_ELEMENT_STRU astMsgList[TLPS_EXC_MAX_SAVE_MSG_NUM];
}TLPS_EXC_MSG_MNTN_STRU;

typedef struct
{
    VOS_UINT32 ulTimeStamp; /* 时间戳*/
    VOS_UINT32 ulCompPid;   /* ulSendPid | ulRcvPid */
    VOS_UINT32 ulMsgId;     /* 消息ID */
    VOS_UINT32 ulPrivate;   /* 用来保存一些重要消息的关键参数*/
    VOS_UINT16 usTrrcPreState;
    VOS_UINT16 usTrrcCurState;
    VOS_UINT16 usTmacPreState;
    VOS_UINT16 usTmacCurState;
    VOS_UINT32 ulFileName;
    VOS_UINT32 ulLineNum;
}TRRC_EXC_MSG_ELEMENT_STRU;

typedef struct
{
    VOS_UINT32                ulNextIndex;
    TRRC_EXC_MSG_ELEMENT_STRU astMsgList[TLPS_EXC_MAX_SAVE_MSG_NUM];
}TRRC_EXC_MSG_MNTN_STRU;



 /*****************************************************************************
 结构名    : LPS_HO_LATENCY_STRU
 结构说明  : PS切换时延统计信息数据结构(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enHoValidFlag;                          /* 本次测量值是否有效 */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulHoLatency[LPS_HO_LATENCY_BUFF];        /* 记录每个关键点的测试值 */
}LPS_HO_LATENCY_STRU;
/*****************************************************************************
 结构名    : LPS_REEST_LATENCY_STRU
 结构说明  : PS重建时延统计信息数据结构(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enReestValidFlag;                       /* 本次测量值是否有效 */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulReestLatency[LPS_REEST_LATENCY_BUFF];  /* 记录每个关键点的测试值 */
}LPS_REEST_LATENCY_STRU;

/*****************************************************************************
 结构名    : LPS_EST_LATENCY_STRU
 结构说明  : PS控制面时延统计信息数据结构(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enContralPlaneValidFlag;                /* 本次测量值是否有效 */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulEstLatency[LPS_EST_LATENCY_BUFF];      /* 记录每个关键点的测试值 */
}LPS_EST_LATENCY_STRU;

/*****************************************************************************
 结构名    : LPS_LATENCY_STAT_STRU
 结构说明  : PS时延统计信息数据结构(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                   enReportFlg;                            /* 时延信息是否上报标志 */
    VOS_UINT8                            aucReserved[3];
    LPS_HO_LATENCY_STRU                  stHoLatency;                         /* 切换时延统计信息 */
    LPS_REEST_LATENCY_STRU               stReestLatency;                      /* 重建时延统计信息 */
    LPS_EST_LATENCY_STRU                 stEstLatency;                          /* 连接建立时延统计信息 */
}LPS_LATENCY_STAT_STRU;
/*****************************************************************************
 结构名    : LPS_OM_MSG_PID_PAIR_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 消息ID的取值段起始值和PID的对应关系对
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulMsgIdStartVal;
    VOS_PID                         ulPid;
}LPS_OM_MSG_PID_PAIR_STRU;


/*****************************************************************************
 结构名    : LPS_OM_MSG_ID_SEARCH_COMM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : ulMsgId的取值和ulSpare的对应关系对
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulMsgId;
    VOS_UINT32                      ulSpare;
}LPS_OM_MSG_ID_SEARCH_COMM_STRU;

/*added by guojiyu*/
/*****************************************************************************
 结构名    : LPS_HANDOVER_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulAllHoSuccTime[LPS_HO_TYPE_BUFF];
    VOS_UINT16                          usLatestHOLatency;      /*最近一次切换时延*/
    VOS_UINT16                          usAverageHOLatency;     /*平均切换时延*/
    LPS_HO_TYPE_ENUM_UINT8              enHoType;
    VOS_UINT8                           ucResvd[3];
    LPS_HO_STAT_INFO_STRU               astHOLatencyInfo[LPS_HO_TYPE_BUFF];
}LPS_HANDOVER_INFO_STRU;

/*****************************************************************************
 修改历史      :
  1.日    期   : 2008年4月21日
    作    者   : 杨龙 y58800
    修改内容   : 新生成结构 GU模的消息头结构

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                   /* VOS消息头 */
    VOS_UINT16    usTransPrimId;     /* 固定值 0x5001 */
    VOS_UINT16    usRsv1;            /* 保留 */
    VOS_UINT8     ucFuncType;        /* 消息跟踪，固定值 2 */
    VOS_UINT8     ucReserve;         /* 保留 */
    VOS_UINT16    usLength;          /* 下一字节至包尾的长度，单位为字节 */
    VOS_UINT32    ulSn;              /* 上报消息的序列号 */
    VOS_UINT32    ulTimeStamp;       /* 消息的时间戳 */
    VOS_UINT16    usPrimId;          /* 原语ID */
    VOS_UINT16    usRsv2;             /* 保留 */
    VOS_UINT16    usOtaMsgID;
    VOS_UINT8     ucUpDown;
    VOS_UINT8     ucRsv;
    VOS_UINT32    ulLengthASN;
    VOS_UINT8     aucData[4];
}LTE_GAS_OM_OTA_IND_STRUCT;

/*h00159435上行发送数据消息的统计量Begin*/
/*****************************************************************************
 结构名    : T_DlRecvMsgStat
 协议表格  :
 ASN.1描述 :
 结构说明  : 记录TDS下行接收数据消息的统计量
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulSccpchReadIndNum;
    VOS_UINT32    ulDpchReadIndNum;
    VOS_UINT32    ulHspdschReadIndNum;
    VOS_UINT32    ulHsUpaInfoIndNum;
}T_DlRecvMsgStat;
/*h00159435上行发送数据消息的统计量End*/
typedef struct
{
    VOS_UINT32      ulTimeStamp;
    VOS_UINT32      ulPid;
    VOS_UINT32      ulOpId;
    VOS_UINT32      MsgId;
}LHPA_DATA_ABORT_MSG_STRU;

typedef struct
{
    VOS_UINT32                    ulDownCurrCnt;
    VOS_UINT32                    ulUpCurrCnt;
    LHPA_DATA_ABORT_MSG_STRU      ulForMailBoxDownDataAbortMsg[LHPA_DATA_ABORT_LAST_MSG];
    LHPA_DATA_ABORT_MSG_STRU      ulForMailBoxUpDataAbortMsg[LHPA_DATA_ABORT_LAST_MSG];
    VOS_UINT32                    ulCurrMailBoxLen;
}LHPA_MAILBOX_DATAABORT_STRU;

extern LHPA_MAILBOX_DATAABORT_STRU  g_stHpaMailBoxDataAbortMsg;

#define     TDS_AIR_MSG_MAX    64

typedef struct
{
    VOS_UINT32                    ulTimeStamp;
    VOS_UINT32                    ulMsgId;
}TDS_AIR_MSG_STRU;

typedef struct
{
    VOS_UINT32                    ulMsgCnt;
    TDS_AIR_MSG_STRU              ulTdsMsg[TDS_AIR_MSG_MAX];

}TDS_AIR_MSG_RECORD_STRU;

extern TDS_AIR_MSG_RECORD_STRU  g_stTdsAirMsgRecord;

/*****************************************************************************
 结构名    : TL_KPI_HDR_STRU
 结构说明  : KPI上报消息公共头
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;
    TL_KPI_TYPE_ENUM_UINT32     enType;
}TL_KPI_HDR_STRU;
/*****************************************************************************
 结构名    : TL_KPI_DELAY_HDR_STRU
 结构说明  : 时延上报公共头
*****************************************************************************/
typedef struct
{
    TL_KPI_HDR_STRU     stKpiHdr;
    VOS_UINT32          ulStartTime;
    VOS_UINT32          ulEnd;
    VOS_UINT32          ulDelay;
    VOS_UINT32          ulAvgDelay;
}TL_KPI_DELAY_HDR_STRU;
/* Print To Layer Begin */

/*****************************************************************************
  结构名    : TLPS_PRINT_SEND_TIMER_STRU
  结构说明  : 用于保存发送标志和timer
   1.日    期   : 2015年5月9日
     作    者   : l00285345
     修改内容   : 创建
*****************************************************************************/

typedef struct
{
    TLPS_PRINT_LEVEL_ENUM_UINT8            enPrintLevel;
    PS_BOOL_ENUM_UINT8                     enSendFlag;
    VOS_UINT8                              aucRev[2];
    HTIMER                                 pucSendPrintTimer;
}TLPS_PRINT_SEND_TIMER_STRU;


/*****************************************************************************
  结构名    : TLPS_SET_TLPS_PRINT2LAYER_REQ_STRU
  结构说明  : 配置打印接口
   1.日    期   : 2015年5月16日
     作    者   : l00285345
     修改内容   : 创建
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
    APP_MSG_HEADER
    TLPS_PRINT_LEVEL_ENUM_UINT8         enPrintLevel;
    UINT8                               aucReserve[3];
} TLPS_SET_TLPS_PRINT2LAYER_REQ_STRU;

typedef  TLPS_SET_TLPS_PRINT2LAYER_REQ_STRU TLPS_SET_TLPS_PRINT2LAYER_CNF_STRU;

/* Print To Layer End */

typedef struct
{
    VOS_UINT32   ulTimeStamp;
    VOS_UINT32   ulFileID;
    VOS_UINT32   ulLineNO;
    SECU_FUNC_TYPE_ENUM_UINT8 enSecuFuncType;/*函数类型*/
    VOS_UINT8    ucRsv;
    VOS_INT16    sErrNo;/*错误值*/
    VOS_VOID *   pDst;/*目的地址*/
    VOS_UINT32   ulMaxBuffer;/*目的缓存长度*/
    VOS_VOID *   pSrc;/*源地址*/
    VOS_UINT32   ulLength;/*实际长度*/
}TLPS_SECU_FUNCTION_INFO_STRU;

typedef struct
{
   VOS_UINT16 usCnt;
   VOS_UINT8  usIndex;
   VOS_UINT8  ucRsv;
   TLPS_SECU_FUNCTION_INFO_STRU astSecuFuncInfo[TLPS_SECU_FUNCTION_ERR_MAXNO];
}TLPS_SECU_FUNCTION_INFO_LIST_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*#if (VOS_OS_VER != VOS_WIN32)
 */
extern LPS_LATENCY_STAT_STRU               g_stPsLatencyStat;
/*#endif
 */
#if (VOS_OS_VER != VOS_WIN32)
extern MSW_VER_INFO_S g_stPSVersionInfo;
#endif

/* mod by guojiyu 可维可测切换时延 begin */
/* 切换时延统计全局变量 */
extern LPS_HANDOVER_INFO_STRU          g_stPsHoInfo;
/* mod by guojiyu 可维可测切换时延 end */

/* gaojishan-remove-kdf-hmac-sha */

extern VOS_UINT32                       g_ulPsBandwidthSupportFlg;
extern VOS_UINT32                       g_ulPsFreqInAllBandWidthFlg;

extern LPS_NV_MEAS_THRESHOLD_STRU g_LPsNvCellMeasThredhold;

extern VOS_UINT32 g_ulNasPlainRejMsgFlag;

extern VOS_UINT32 g_ulNasCsfbTauType2Flag;
#if (VOS_OS_VER != VOS_WIN32)
extern DIAG_TRANS_IND_STRU                    g_stPrintInfoInd;
extern TLPS_PRINT_INFO_LIST_STRU              g_stPrintInfoList;
extern TLPS_SEND_PRINT_BUFFER_STRU            g_astSendPrintInfoList[TLPS_PRINT_NUM_OF_BUFFER];
extern TLPS_PRINT_SEND_TIMER_STRU             g_stSendPrintFlagTimer;
#endif

extern TLPS_SECU_FUNCTION_INFO_STRU g_stSecuFuncInfo;
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  LPS_OM_PidMsgProc(const MsgBlock *pMsg  );
extern VOS_UINT32 LPS_OM_SearchMsgIdTbl( VOS_UINT32 ulMsgId,
                                                 CONST LPS_OM_MSG_ID_SEARCH_COMM_STRU *pstTbl,
                                                 VOS_UINT32 ulTblSize,
                                                 VOS_UINT32 *pulTblIdx);
extern VOS_UINT32 LPS_OM_SearchMsgIdTblForHpa( VOS_UINT32 ulMsgId,
                                          CONST LPS_OM_MSG_ID_SEARCH_COMM_STRU *pstTbl,
                                          VOS_UINT32 ulTblSize,
                                          VOS_UINT32 *pulTblIdx);
extern VOS_UINT32 LPS_OM_TraceMsgHook( VOS_VOID *pMsg );

extern VOS_VOID LPS_OM_SetLatency(VOS_UINT32* pulLatency,
                            VOS_UINT8 ucLatencyType,VOS_UINT32 ulLatencyBuff);

extern VOS_VOID LNAS_LPSOM_GetNvRaMod ( VOS_UINT32       *pulPsCfgDspRatMod);
extern     VOS_VOID LNAS_LPSOM_GetCampedCellInfo(LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
        LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo);
extern  VOS_VOID LNAS_LPSOM_GetIpAddrInfo(APP_LPS_CAMPED_CELL_INFO_STRU *pstCampedCellInfo);
extern VOS_VOID LRRC_LPSOM_GetCampedCellInfo(APP_LPS_CAMPED_CELL_INFO_STRU *pstCampedCellInfo);
extern VOS_VOID LPS_OM_GetHoInfo(APP_LPS_HANDOVER_INFO_STRU *psPsOmGetHoinfo);
extern  VOS_VOID L2_LPSOM_GetMacPrachInfo(APP_LPS_PRACH_SR_INFO_STRU *pstLMacOmInfo);
extern  VOS_VOID L2_LPSOM_GetMacBsrInfo(APP_LPS_BSR_INFO_STRU *pstLMacOmBsrInfo);

VOS_VOID LPS_OM_CampedCellInfoInd(VOS_VOID);
VOS_VOID LPS_OM_CellHOInfoInd(VOS_VOID);
VOS_VOID LPS_OM_CampedCellInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_CellHOInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_PrachSrInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_BsrInfoReq(APP_OM_MSG_STRU *pMsg);
extern VOS_UINT32 LTE_MsgHook( VOS_VOID *pMsg );
extern VOS_UINT32 LRrc_Om_MsgHookNoFilter( VOS_VOID *pMsg );
extern VOS_VOID  LPS_OM_StatInit(VOS_VOID);
/* gaojishan-Dug-mod-Begin */
/* gaojishan-reboot-save-lrrc-para-for-nas-reboot */
extern VOS_VOID LPS_SoftReBoot_SaveLRrc( VOS_VOID );
extern VOS_UINT32 LPS_SoftReBoot_WithLineNoAndFileID(VOS_UINT32 ulDbgNum,VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID);
/* gaojishan-Dug-mod-End */

extern VOS_VOID LHPA_ProcGetSelfAdjustPara( VOS_VOID );
#if (VOS_OS_VER != VOS_WIN32)

extern VOS_UINT32 LPS_OM_GetTmode(FTM_TMODE_ENUM* penFtmMode);
#endif
extern VOS_UINT32 LPS_OM_IsTestMode(VOS_VOID);

#if (FEATURE_ON == FEATURE_VERSION_V8)
#if (VOS_OS_VER != VOS_WIN32)
extern VOS_VOID TLPS_ExcLog_Save(cb_buf_t *pstData);
#endif
#else
extern VOS_VOID TLPS_ExcLog_Save(VOS_VOID);
#endif
extern VOS_UINT32 TLPS_TaskDelay(VOS_UINT32 ulLength);

/*封装取得时间戳函数*/
/*由于低软封装的宏DRV_32K_GET_TICK()无法使用，所以只能这样定义，FPGA无法使用32K所以不用*/
#define PS_GET_TICK()    VOS_GetTick()


extern VOS_UINT32 TDS_OM_DiagPrint(const VOS_CHAR *pcString, ...);
extern VOS_UINT32 TDS_OM_DiagPrint1(VOS_UINT32 ulId, const VOS_CHAR *pcString, ...);

extern VOS_VOID LPS_OM_StatInfoMsgProc(MsgBlock CONST *pMsg);
extern VOS_VOID TRRC_GetCurrentState(VOS_UINT8 *pCurrentProtocolState,
           VOS_UINT8 *pCurrentState  );

extern VOS_VOID TLPS_ExcLog_SaveMsgList(VOS_VOID *pMsg);
extern VOS_UINT32 PS_OM_SendMsg(VOS_UINT32 Pid, VOS_VOID *pMsg);
extern VOS_UINT32 LPsOm_GetTimeDiffByStampWithSecondUnit(LPS_32K_TIMESTAMP *pstOldTStamp,
                                                                         LPS_32K_TIMESTAMP *pstNewTStamp);

extern VOS_VOID  TLPS_Print2Layer(VOS_UINT16  enFunction, \
                                      VOS_UINT16 enProcFlag, \
                                      VOS_INT32 lPara1, VOS_INT32 lPara2);
extern VOS_VOID  TLPS_ProcPrint2LayerLevel(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16 enProcFlag);
extern  VOS_VOID  TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16 enProcFlag, \
                                           VOS_INT32 lPara1);

extern  VOS_VOID  TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16  enProcFlag, \
                                           VOS_INT32 lPara1, VOS_INT32 lPara2);
extern VOS_VOID  TLPS_COMM_SendAndFreePrintInfoInd(VOS_UINT32 ulSize, TLPS_SEND_PRINT_BUFFER_STRU * pData);
extern TLPS_SEND_PRINT_BUFFER_STRU * TLPS_AllocAndCopyPrintInfo(VOS_UINT32 ulSize);
extern VOS_VOID  TLPS_SendPrintBufferInfo(VOS_VOID);
extern VOS_VOID  TLPS_ProcSendPrintBufferExpire(VOS_VOID);
extern VOS_VOID  TLPS_StopPrint2LayerBufferTimer(VOS_VOID);
extern VOS_VOID  TLPS_StartPrint2LayerBufferTimer(VOS_VOID);
extern VOS_VOID LPS_ReadIdleDiscardPagingNV(VOS_VOID);
extern VOS_VOID TLPS_SaveSecuFuncFailInfo(const TLPS_SECU_FUNCTION_INFO_STRU * pstSecuFuncInfo);
extern VOS_VOID TLPS_ResetSecuFuncFail(VOS_VOID);
extern VOS_INT32 TLPS_Mem_Cpy_Secu(VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc, VOS_UINT32  ulLength,\
                        VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID);
extern VOS_INT32 TLPS_Mem_Set_Secu(VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_UINT8 ucData, VOS_UINT32  ulLength,\
                            VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID);
extern VOS_INT32 TLPS_Mem_Move_Secu(VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc, VOS_UINT32  ulLength,\
                            VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/







#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LPsOm.h */
