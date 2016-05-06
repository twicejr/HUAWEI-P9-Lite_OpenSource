/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_debug.h
*
*  Project Code: VISPV1R5
*   Module Name: PUBLIC  
*  Date Created: 2006-5-22
*        Author: X36317
*   Description: 定义了DEBUG相关的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2005-3-26  X36317         Creat the first version.
*  2006-5-22  X36317         为消除PC-LINT告警所做的修改.
*  2006-6-16  X36317         第二阶段质量改进.
*  2008-2-27  f54882         For A82D23738,同步VISP三期需求,
*                            增加PPP协商时的地址冲突的告警
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_DEBUG_H_
#define _TCPIP_DEBUG_H_

#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_log.h"

extern CHAR *TCPIP_MidInfo_IPV4[];
extern CHAR *TCPIP_MidInfo_IPV6[];

extern VOID TCPIP_DebugOutput(CHAR *pDebugInfo);

extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern VOID TCPIP_CCOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
    
/* VISP告警接口，通知产品可能关心的告警信息，函数体由产品具体实现 */
extern VOID TCPIP_WarningOut(ULONG ulWarningID, VOID* pWarnParam);

ULONG IC_ErrTraceOutput(ULONG ulMid,CHAR *pucFile, CHAR *pucFunc,ULONG ulLine,ULONG ulLevel,CHAR* pucMessage);

ULONG TCPIP_SetDebugLevel (ULONG ulMid, ULONG ulDebugLevel);
ULONG TCPIP_GetDebugLevel(ULONG ulMid, ULONG* pulDebugLevel);

extern ULONG TCPIP_SelfTaskID();

extern VOID IP_ShowAllVrfIPAddr();

extern ULONG g_ulSockDbgLevel;   /*Socket4组件的调试级别*/
extern ULONG g_ulTCP4DbgLevel;   /*TCP4组件的调试级别*/
extern ULONG g_ulUDP4DbgLevel;   /*UDP4组件的调试级别*/
extern ULONG g_ulICMP4DbgLevel;  /*ICMP4组件的调试级别*/
extern ULONG g_ulPP4DbgLevel;    /*PP4组件的调试级别*/
extern ULONG g_ulEthArpDbgLevel; /*ETHARP组件的调试级别*/
extern ULONG g_ulPPPDbgLevel;    /*PP4组件的调试级别*/
extern ULONG g_ulATKDbgLevel;    /*ATK组件的调试级别*/

extern ULONG g_ulLogType;       /*LOG信息类型,默认记录所有类型信息*/
extern ULONG g_ulLogLevel;      /*LOG信息等级,默认记录MAJOR等级信息*/
extern TCPIP_LOG_HOOK_FUNC g_stTCPIPLogOutput;  /*日志输出全局结构体变量*/

extern gpfTCPIPDebugOutput      g_pfTCPIPDebugOutput;   /* 调试信息输出钩子 */
extern gpfTCPIPWarningOutput    g_pfTCPIPWarningOutput; /* 告警输出钩子 */
extern gpfTCPIPInfoOutput       g_pfTCPIPInfoOutput;    /* 查询信息输出钩子 */
extern gpfVOSAssertX            g_pfVOSAssertX;         /* 断言输出钩子 */
extern TCPIP_CC_OUTPUT_HOOK_FUNC pfTCPIP_CC_Output;     /* 用户CC诊断结果输出函数 */

/*以下宏定义是为了各组件输出调试信息时用*/
#define SOCK_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulSockDbgLevel != ERR_LEVEL_TEST) && (g_ulSockDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulSockDbgLevel) && (ulLevel == g_ulSockDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_SOCKET,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define TCP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulTCP4DbgLevel != ERR_LEVEL_TEST) && (g_ulTCP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulTCP4DbgLevel) && (ulLevel == g_ulTCP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_TCP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define UDP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulUDP4DbgLevel != ERR_LEVEL_TEST) && (g_ulUDP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulUDP4DbgLevel) && (ulLevel == g_ulUDP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_UDP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ICMP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulICMP4DbgLevel != ERR_LEVEL_TEST) && (g_ulICMP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulICMP4DbgLevel) && (ulLevel == g_ulICMP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ICMP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }
    
#define PP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulPP4DbgLevel != ERR_LEVEL_TEST) && (g_ulPP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulPP4DbgLevel) && (ulLevel == g_ulPP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_PP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ETHARP_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulEthArpDbgLevel != ERR_LEVEL_TEST) && (g_ulEthArpDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulEthArpDbgLevel) && (ulLevel == g_ulEthArpDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ETHARP,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define PPP_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulPPPDbgLevel != ERR_LEVEL_TEST) && (g_ulPPPDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulPPPDbgLevel) && (ulLevel == g_ulPPPDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_PPP,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ATK_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulATKDbgLevel != ERR_LEVEL_TEST) && (g_ulATKDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulATKDbgLevel) && (ulLevel == g_ulATKDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ATTACK,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define OUTPUT_FIX_LOG 0x1  /* 输出定长日志到com口 */
#define OUTPUT_VAR_LOG 0x2  /* 输出变长日志到com口 */
#define OUTPUT_DEBUG   0x4  /* 输出调试信息到com口 */
#define OUTPUT_INFO    0x8  /* 输出显示信息到com口 */
#define OUTPUT_CC      0x10 /* CC信息输出到com口 */

#define TCPIP_CCTYPE_DCC   1
#define TCPIP_CCTYPE_NCC   2

#define LOG_ASY_OUTPUT_MOD 0
#define LOG_SYN_OUTPUT_MOD 1


/* BFD初始化后BFD记录数目 */
#define BFDINFO_COUNT    2

/* 单跳标识 */
#define BFDINFO_ONEHOP   0

/* 多跳标识 */
#define BFDINFO_MULTIHOP 1

/* BFD初始化成功标记 */
#define BFDINIT_OK       1

/* BFD端口对外显示标志 */
#define BFDPORT_EXPOSE   1

/* BFD模块单跳的目的端口 */
#define BFDINFO_SCRPORT_ONEHOP 3784

/* BFD模块多跳的目的端口 */
#define BFDINFO_SCRPORT_MULHOP 4784

/* BFD网络状态标记 */
extern ULONG ulBFDFlag;

#endif  /* _TCPIP_DEBUG_H_ */

#ifdef  __cplusplus
}
#endif
