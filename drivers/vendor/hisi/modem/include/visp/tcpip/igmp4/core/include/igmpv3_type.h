/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_type.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-11
*        Author: zengshaoyang62531
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_TYPE_H
#define _IGMPV3_TYPE_H

#include "tcpip/public/tcpip_config.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_MEMBERSHIP_QUERY          0x11    /* membership query */
#define IGMPV1_MEMBERSHIP_REPORT       0x12    /* Ver. 1 membership report */
#define IGMPV2_MEMBERSHIP_REPORT       0x16    /* Ver. 2 membership report */
#define IGMPV2_LEAVE_GROUP             0x17    /* Ver. 2 Leave-group message */
#define IGMPV3_MEMBERSHIP_REPORT       0x22    /* Ver. 3 membership report */

#define IGMP_EXCLUDE                   IGMP_REPORT_MODE_EX  /*EXCLUDE过滤模式，内部使用*/
#define IGMP_INCLUDE                   IGMP_REPORT_MODE_IN  /*INCLUDE过滤模式，内部使用*/

#define IGMP_RECIEVE                   0       /* 接收方向的IGMP报文*/
#define IGMP_SEND                      1       /* 发送方向的IGMP报文*/

/*struct id,供申请内存时使用*/
#define SID_IGMPTIMERNODE_S            1
#define SID_IGMPCALLBACK_S             2
#define SID_IPMULTI_SOURCELIST_S       3
#define SID_IPMULTI_S                  4
#define SID_IPMULTI_LIST_S             5
#define SID_IGMPSTAT_S                 6

/*主动报告周期的取值范围[1 - 5s]*/
#define UNS_REPORT_INTERVAL_MIN 1         /*unsolicited report interval,min: 1s*/
#define UNS_REPORT_INTERVAL_MAX 5         /*unsolicited report interval,max: 5s*/

typedef enum tagIGMP_ERRCODE_INC
{
    IGMP_ERR_MAXSOURCE = 1,                    /*socket上多播组的源地址已达到最大值*/
    IGMP_ERR_NOTEXISTINLIST,                   /*源地址不存在于源列表中*/
    IGMP_ERR_MEMORYFAULT,                      /*内存错误*/
    IGMP_ERR_MULTINOTEXIST,                    /*多播组不存在*/
    IGMP_ERR_SOURCEEXISTINSOCK,                /*源地址已经存在于socket多播组的源列表上*/
    IGMP_ERR_SOURCELISTNULL,                   /*源列表为空*/
    IGMP_ERR_PARAM,                            /*参数错误*/
    IGMP_ERR_IF_INVALIDTYPE,                   /*接口类型无效*/
    IGMP_ERR_IF_NULL,                          /*接口为空*/
    IGMP_ERR_MULTIADDR_INVALID,                /*多播地址无效*/
    IGMP_ERR_CFGINFO_INVALID,                  /*配置信息无效*/
    IGMP_ERR_MULTIADDR_FORBID,                 /*禁止配置该多播地址*/
    IGMP_ERR_INVALIDOPT,                       /*无效的操作*/

    IGMP_ERR_END                               /*最大错误码，请在此字段之前添加错误码*/
}IGMP_ERRCODE_INC_E;

extern ULONG gulURptPeriod;                /*主动报告周期*/

typedef struct tagIGMP_DEBUG
{
    ULONG ulDstAddr;                        /*IGMP报告发送的目的地址*/
    ULONG ulReportType;                     /*IGMP报告的类型*/
    ULONG ulGroupCount;                     /*IGMP报告包含的组数目*/
    Igmpv3_Report_GrpRec_S groupRecord;     /*组记录*/
    IPMULTI_SOURCELIST_S pstSourceList;     /*组记录中的源地址*/
}IGMP_DEBUG_S;

enum enumIGMPDiscardType
{
    IGMP_DISCARD_INTERFACE_VALID = 0,       /*0，接口无效*/
    IGMP_DISCARD_WRONG_TYPE,                /*1，错误类型的IGMP报文*/
    IGMP_DISCARD_MBUF_LENGTH_WRONG,         /*2，报文长度不合法*/
    IGMP_DISCARD_MULTIADDR_INVALID,   /*3，IGMP报文中的多播地址不合法*/
    IGMP_DISCARD_CREATE_TIMER_FAIL,         /*4  创建定时器失败*/

    /*要添加类型时，请在IGMP_DISCARD_UNKNOW_ERROR前添加*/
    IGMP_DISCARD_UNKNOW_ERROR               /*未知的错误类型*/
};

enum enumIGMPEventType
{   
    IGMP_JOINGROUP,
    IGMP_LEAVEGROUP,
    IGMP_ALLOW_NEW,
    IGMP_BLOCK_OLD,
    IGMP_SETMULTIIF,
    IGMP_SETMULTITTL,
    IGMP_SETMULTILOOP,
    IGMP_ERR_JOINGROUP,
    IGMP_ERR_LEAVEGROUP,
    IGMP_ERR_WRONGPARAM,
    IGMP_ERR_UNKNOWERROR,
    IGMP_ERR_MEMORY,
    IGMP_WARNING_VERSION_CHANGE,
    IGMP_WARNING_MSGTYPE_INVALID,
    IGMP_WARNING_IF_INVALID
};

typedef struct tagIGMP_SHELLCALLBACK
{
    VOID(*pfIGMP_DebugOutput)(CHAR *pszInfo);
}IGMP_SHELLCALLBACK_S;

/* IGMP调试信息输出回调函数 */
extern IGMP_SHELLCALLBACK_S g_stIGMPShellCallbackFunc;


/* IGMP src ip callback function. */
extern IGMP_GET_SRC_IP_HOOK g_stIGMPSrcIPCallbackFunc;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
