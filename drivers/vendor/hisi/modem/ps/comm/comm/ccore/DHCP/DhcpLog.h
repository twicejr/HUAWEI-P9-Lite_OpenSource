/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : DhcpLog.h
  版 本 号   : 初稿
  作    者   : w00316385
  生成日期   : 2015年9月30日
  最近修改   :
  功能描述   : DhcpLog.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月30日
    作    者   : w00316385
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DHCP_LOG__
#define __DHCP_LOG__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TTFComm.h"
#include "PsLogdef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     DHCP_LOG_PARAM_MAX_NUM      (4)
#define     DHCP_LOG_RECORD_MAX_NUM     (10)
#define     ID_CTTF_DHCP_TRACE_LOG_MSG  (0xeeee)

#define     CTTF_DHCP_INIT_LOG_ENT()    DHCP_MNTN_InitLogEnt(&g_stDhcpLogEnt)

/* DHCP日志输出 */
#define DHCP_INFO_LOG(String)                                                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_INFO_LOG1(String, Para1)                                           {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_INFO_LOG2(String, Para1, Para2)                                    {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_INFO_LOG3(String, Para1, Para2, Para3)                             {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_INFO_LOG4(String, Para1, Para2, Para3, Para4)                      {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_INFO, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}

#define DHCP_WARNING_LOG(String)                                                {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_WARNING_LOG1(String, Para1)                                        {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_WARNING_LOG2(String, Para1, Para2)                                 {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_WARNING_LOG3(String, Para1, Para2, Para3)                          {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_WARNING_LOG4(String, Para1, Para2, Para3, Para4)                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_WARNING, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}

#define DHCP_ERROR_LOG(String)                                                  {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, 0, 0, 0, 0);}
#define DHCP_ERROR_LOG1(String, Para1)                                          {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1), 0, 0, 0);}
#define DHCP_ERROR_LOG2(String, Para1, Para2)                                   {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2), 0, 0);}
#define DHCP_ERROR_LOG3(String, Para1, Para2, Para3)                            {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3), 0);}
#define DHCP_ERROR_LOG4(String, Para1, Para2, Para3, Para4)                     {DHCP_MNTN_LogSave((&g_stDhcpLogEnt), (MSPS_PID_DHCP), PS_PRINT_ERROR, THIS_FILE_ID, __LINE__, (VOS_INT32)(Para1),(VOS_INT32)(Para2),(VOS_INT32)(Para3),(VOS_INT32)(Para4));}


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
typedef struct
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          enLevel;
    PS_FILE_ID_DEFINE_ENUM_UINT32       enFile;
    VOS_UINT32                          ulLine;
    VOS_INT32                           alPara[DHCP_LOG_PARAM_MAX_NUM];
} DHCP_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                          ulCnt;                  /* 实际缓存的打印记录数目 */
    DHCP_LOG_RECORD_STRU                astData[DHCP_LOG_RECORD_MAX_NUM];
} DHCP_LOG_ENT_STRU;

typedef struct
{
    VOS_MSG_HEADER                          /* _H2ASN_Skip */
    VOS_UINT16              usMsgType;      /* _H2ASN_Skip */
    VOS_UINT16              usTransId;
    DHCP_LOG_ENT_STRU       stLogMsgCont;   /* LOG_MSG内容 */
} CTTF_DHCP_TRACE_LOG_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
extern DHCP_LOG_ENT_STRU            g_stDhcpLogEnt;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID DHCP_MNTN_InitLogEnt(DHCP_LOG_ENT_STRU *pstLogEnt);
VOS_VOID DHCP_MNTN_LogSave
(
    DHCP_LOG_ENT_STRU              *pstLogEnt,
    VOS_UINT32                      ulPid,
    LOG_LEVEL_EN                    enLevel,
    PS_FILE_ID_DEFINE_ENUM_UINT32   enFile,
    VOS_UINT32                      ulLine,
    VOS_INT32                       lpara1,
    VOS_INT32                       lpara2,
    VOS_INT32                       lpara3,
    VOS_INT32                       lpara4
);
VOS_VOID DHCP_MNTN_LogOutput(DHCP_LOG_ENT_STRU *pstLogEnt, VOS_UINT32 ulPid);


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


#endif /* end of DhcpLog.h */

