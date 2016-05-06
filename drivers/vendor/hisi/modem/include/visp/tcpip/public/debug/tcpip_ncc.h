/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ncc.h
*
*  Project Code: VR8C01
*   Module Name: PUBLIC
*  Date Created: 2009-4-11
*        Author: w60786
*   Description: NCC所有的类型定义,枚举定义,宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-4-11    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_NCC_H_
#define _TCPIP_NCC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/debug/tcpip_ncc_api.h"


/*******************************宏定义*****************************************/
/* NCC队列标志 */
#define NCC_QMODE                       VOS_Q_FIFO  
/* NCC队列长度 */
#define NCC_QUEDEPTH                    512       

/* NCC事件 */
#define NCC_EVENT                       0x00000001 
/* NCC定时器消息处理事件 */
#define NCC_EVENT_TIMER                 (1 << 15)

/* NCC任务优先级最大值 */
#define NCC_TASK_MAX_PRI                255
/* NCC任务栈大小16k(16384) */
#define NCC_TASK_STACKSIZE              (16*1024)

/* PPP类型NCC诊断支持的最大数目 */
#define NCC_DIAGNOSE_PPP_MAX            8

/* 存在NCC诊断,NCC任务已创建 */
#define NCC_TASK_ALREADY_START          0
/* 不存在任何NCC诊断,在启动NCC检查时需要创建NCC任务,在停止NCC诊断或者NCC诊断完成时需要删除任务 */
#define NCC_TASK_NOT_START              1

/* PPP类型NCC诊断时间最小值,单位:秒 */
#define NCC_PPP_DETECT_TIME_MIN         10
/* PPP类型NCC诊断时间最大值,单位:秒 */
#define NCC_PPP_DETECT_TIME_MAX         600
/* PPP类型NCC诊断时间默认值,单位:秒 */
#define NCC_PPP_DETECT_TIME_DEFAULT     30

/* NCC诊断项已使用 */
#define NCC_DIAGNOSE_USE                1
/* NCC诊断项未使用 */
#define NCC_DIAGNOSE_NOTUSE             0

/* NCC诊断存在 */
#define NCC_DIAGNOSE_EXIST              1
/* NCC诊断不存在 */
#define NCC_DIAGNOSE_NOTEXIST           0

/* PPP信息收集开关标记 */
#define NCC_DIAGNOSE_DOT_START_FLAG     1

/* PPP类型NCC诊断统计初始值标志 */
#define NCC_DIAGNOSE_STATISTIC_START_FLAG    1

/* PPP信息收集记录个数最大值 */
#define NCC_PPP_DIAGNOSE_NUM            8
/* PPP扫描记录个数最大值 */
#define NCC_PPP_DOT_NUM                 4

/* 诊断结束 */
#define NCC_DIAGNOSE_END                1
/* 诊断继续 */
#define NCC_DIAGNOSE_CONTINUE           2

/* 接口状态统计初值标志 */
#define NCC_PPP_IFCOUNT_FIRST           1
/* 接口状态统计结束值标志 */
#define NCC_PPP_IFCOUNT_LAST            2

/* PPP类型的NCC诊断是否使能 */
#define NCC_PPP_ISENABLE (VRP_YES == g_ulNccDiagnosePppSwitch)

/*******************************枚举定义***************************************/
/* NCC诊断内部输出信息ID */
typedef enum enNCC_DiagnoseInfo
{
    NCC_INFO_START = 0,                 /* 诊断开始,打印诊断标题 */
        
    NCC_INFO_PPP_NO_INTERFACE,          /* PPP类型诊断接口不存在              */
    NCC_INFO_PPP_NO_PPPCTL,             /* 没有接口对应的PPP控制块            */
    NCC_INFO_PPP_NO_CONFIG,             /* 没有接口对应的PPP配置控制块        */
    NCC_INFO_PPP_NO_USEDCONFIG,         /* 没有接口对应的PPP生效配置控制块    */

    NCC_INFO_PPP_NORMAL_PPP,            /* 该接口是普通PPP接口                */
    NCC_INFO_PPP_MP_SUBCHANNEL,         /* 该接口是MP子接口                   */
    NCC_INFO_PPP_MP_SUBCHANNEL_NORESET, /* 该接口被配置为MP子接口,但还未生效,实际作为普通PPP接口运行 */
    NCC_INFO_PPP_NORMAL_PPP_NORESET,    /* 该接口被配置为普通PPP接口,但还未生效,实际作为MP子接口运行 */
    
    NCC_INFO_PPP_SHUTDOWN,              /* PPP类型诊断接口被shutdown          */
    NCC_INFO_PPP_PHY_UP,                /* PPP类型诊断接口物理状态UP          */
    NCC_INFO_PPP_PHY_DOWN,              /* PPP类型诊断接口物理状态DOWN        */
    NCC_INFO_PPP_PHY_UPDOWN_REPEAT,     /* PPP类型诊断接口物理状态反复UP/DOWN */
    NCC_INFO_PPP_MP_PHY_DOWN,           /* PPP类型诊断MP接口物理状态DOWN      */
    NCC_INFO_PPP_MP_PHY_UPDOWN_REPEAT,  /* PPP类型诊断MP接口物理状态反复UP/DOWN */
    NCC_INFO_PPP_LINE_UP,               /* PPP类型诊断接口协议状态UP          */
    NCC_INFO_PPP_LINE_DOWN,             /* PPP类型诊断接口协议状态DOWN        */
    NCC_INFO_PPP_LINE_UPDOWN_REPEAT,    /* PPP类型诊断接口协议状态反复UP/DOWN */
    NCC_INFO_PPP_LCP_UP,                /* PPP类型诊断LCP UP                  */
    NCC_INFO_PPP_LCP_DOWN,              /* PPP类型诊断LCP DOWN                */
    NCC_INFO_PPP_LCP_UPDOWN_REPEAT,     /* PPP类型诊断LCP 反复UP/DOWN         */
    NCC_INFO_PPP_IPCP_UP,               /* PPP类型诊断IPCP UP                 */
    NCC_INFO_PPP_IPCP_DOWN,             /* PPP类型诊断IPCP DOWN               */
    NCC_INFO_PPP_IPCP_UPDOWN_REPEAT,    /* PPP类型诊断IPCP 反复UP/DOWN        */
    NCC_INFO_PPP_SHOW_DOWNREASON,       /* PPP类型诊断显示PPP DOWN原因        */

    NCC_INFO_PPP_SHOW_PPPINFO,          /* 显示PPP信息                        */
    NCC_INFO_PPP_MPINFO,                /* 显示MP信息                         */
    NCC_INFO_PPP_SHOW_NEGPKT_STATISTIC, /* 显示PPP协商报文统计信息            */

    NCC_INFO_PPP_LCP_DOTINFO,           /* 显示LCP诊断打点扫描信息            */
    NCC_INFO_PPP_IPCP_DOTINFO,          /* 显示IPCP诊断打点扫描信息           */

    NCC_INFO_PPP_LOCAL_NOBINDTOMP,          /* 本端未加入MP,对端已加入MP */
    NCC_INFO_PPP_LOCAL_BINDTOMP_NORESET,    /* 本端已加入MP,但还未生效,对端已加入MP */
    NCC_INFO_PPP_REMOTE_NOBINDTOMP,         /* 对端未加入MP,本端已加入MP */
    NCC_INFO_PPP_LOCAL_NOBINDTOMP_NORESET,  /* 对端未加入MP,本端已移出MP,但还未生效 */

    NCC_INFO_PPP_DISCR_NEG_FAIL,            /* 本端希望协商终端描述符,但是终端描述符协商失败,
                                               协商结果不是两端都协商终端描述符,导致本端LCP协商不过 */
    NCC_INFO_PPP_DISCR_CONSISTENT_DADDR,    /* 该子接口协商到的对端的终端描述符与其MP父接口的对端的终端描述符值不相同 */
    
    NCC_INFO_PPP_MHF_PREFIX_CLASS_INVALID,  /* 对端设置了协商前缀省略,但是本端设置的前缀省略最大等级大于对端的
                                               MHF最大等级导致协商不过.
                                              (原则:MHF选项所协商的class等级数必须包容前缀省略所支持的最大等级) */

    NCC_INFO_PPP_LCP_UPCHECK_NEG_NOPAP,     /* 本端作为认证方,设置了PAP协商,但是没有协商通过,
                                               可能对端没有配置用户名和pwd */
    NCC_INFO_PPP_LCP_PAP_AUTH_FAIL,         /* 认证过程中分配PAP控制块失败,内存不足 */
    NCC_INFO_PPP_LCP_PAP_AUTH_SERVER_FAIL,  /* 认证过程中认证方SERVER PAP认证失败 */
    NCC_INFO_PPP_LCP_PAP_AUTH_CLIENT_FAIL,  /* 认证过程中被认证方CLIENT PAP认证失败 */

    NCC_INFO_PPP_LCP_UPCHECK_NEG_NOCHAP,    /* 本端作为认证方,设置了CHAP协商,但是没有协商通过,
                                               可能对端没有配置用户名和pwd */
    NCC_INFO_PPP_LCP_CHAP_AUTH_FAIL,        /* 认证过程中分配CHAP控制块失败,内存不足 */
    NCC_INFO_PPP_LCP_CHAP_AUTH_SERVER_FAIL, /* 认证过程中认证方SERVER CHAP认证失败 */
    NCC_INFO_PPP_LCP_CHAP_AUTH_CLIENT_FAIL, /* 认证过程中被认证方CLIENT CHAP认证失败 */

    NCC_INFO_PPP_MP_NOUPTOLOWLIMIT,         /* MP绑定的子链路数未达到用户指定的最小规格导致未进行NCP的协商 */
    
    NCC_INFO_PPP_NOCONFIGIP,                /* 接口上未配置地址导致IPCP协商不过 */
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIP_ZERO,   /* 本端配置为协商获取地址,但是协商获得的地址为0 */
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIP_INVALID,/* 本端配置为协商获取地址,但是协商获得的地址非法(无效IP) */
    NCC_INFO_PPP_IPCP_UPCHECK_HISIP_INVALID,/* 对端配置为协商获取地址,但是对端协商获得的地址非法(无效IP) */
    NCC_INFO_PPP_IPCP_IPCONFLICT_LOCALSAME, /* 本端配置为协商获取地址,但是协商获得的地址与本端其他IP相同(冲突) */
    NCC_INFO_PPP_IPCP_UPCHECK_IPCONFLIT_PEERSAME, /* 本端配置为协商获取地址,但是协商获得的两端IP相同(冲突),
                                                     或者两端都配置IP但是IP冲突*/
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIPCONFLIT_MODE,  /* 本端已有自己的IP,但对端仍然给本端分配IP导致冲突 */
    NCC_INFO_PPP_IPCP_UPCHECK_HISIPCONFLIT_MODE,  /* 对端已有自己的IP,但本端仍然给对端分配IP导致冲突 */

    NCC_INFO_PPP_IPCP_UPCHECK_IPHCINIT_FAIL,      /* IPHC模块初始化失败导致IPCP协商失败 */

    NCC_INFO_PPP_RCV_NO_NEGPKT,   /* 本端有发送数据,但是没有收到对端的任何数据,可能为底层不通
                                     或者对端配置为不协商LCP/IPCP */
    NCC_INFO_PPP_RCV_WRONG_PKTID, /* 收到ID不匹配的报文,可能的原因:底层上送报文不及时,底层收发时传给的PPP链路错误,
                                     底层收发报文时乱序 */

    NCC_INFO_PPP_MP_PARAMS_INCONSISTENT, /*Inconsistencies in the Group and Member link parameters*/

    NCC_INFO_PPP_RTR,                 /*Recived the Termination request*/ 

    NCC_INFO_PPP_ECHO_TIMEOUT,           /*Echo packet timed out */

    NCC_INFO_PPP_RCR,          /*Recived the Configureation request*/

    NCC_INFO_PPP_IPCP_RCR, /*Recived the Configureation request In OpenState*/

    NCC_INFO_PPP_IPCP_RTR, /*Recived the Termination request In OpenState*/

    NCC_INFO_PPP_NO_REASON, /* 没有诊断出具体原因,请给据本端和对端的参考信息进行定位 */    
    
    NCC_INFO_END           /* 诊断结束,打印诊断结束信息          */
}NCC_DIAGNOSEINFO_E;

/* PPP LCP扫描点ID */
typedef enum enNCC_PPPLCPDOT
{
    LCP_REQCI_LOCAL_REJ_MRRU = 0,    /* 本端没有加入MP,对端加入MP导致本端LCP反复UP/DOWN */
    LCP_REJCI_REMOTE_REJ_MRRU,       /* 对端没有加入MP,本端加入MP导致本端LCP协商不过 */
    LCP_REQCI_MRRU_INVALID,          /* 对端的MRRU值不符合本端最小值128的要求,NAK对端 */
    LCP_NAKCI_MRRU_INVALID,          /* 由于对端NAK的值不符合要求,所以本端不再进行MRRU协商 */
    LCP_UPCHECK_NO_NEG_MRRU,         /* 本端加入了MP, 但是协商结果不是两端都加入了MP,导致在LCP UP之前检查不通过 */
    
    LCP_REQCI_DISCR_NOT_NEG,         /* 本端不允许协商终端描述符 */
    LCP_REQCI_DISCR_LEN_INVALID,     /* 终端描述符类型为LCP_DISCR_NULL时长度不为3 */
    LCP_REQCI_DISCR_TELENUM_INVALID, /* 不支持终端描述符类型,如需支持HDLC自动侦听非标需求功能,
                                        可将开关g_ulDiscrSpecial打开来支持该类型的协商 */
    LCP_REQCI_DISCR_CLASS_INVALID,   /* 无效的终端描述符类型 */    
    LCP_UPCHECK_NO_NEG_DISCR,        /* 本端加入了MP并且要求协商终端描述符, 但是协商结果不是两端都协商终端描述符,
                                        导致在LCP UP之前检查不通过 */

    LCP_MPBIND_DISCR_CONSISTENT_NEGD,       /* 绑定子链路协商到的对端是否协商MP终端描述符与父通道不一致*/
    LCP_MPBIND_DISCR_CONSISTENT_DLENCLASS,  /* 绑定子链路协商到的对端的MP终端描述符长度类型与父通道不一致*/
    LCP_MPBIND_DISCR_CONSISTENT_DADDR,      /* 绑定子链路协商到的对端的MP终端描述符值与父通道不一致*/

    LCP_UPCHECK_NEG_NOPAPCHAP,    /* 本端设置了PAP/CHAP协商,但是一个都没有协商通过 */
    LCP_UPCHECK_NEG_NOCHAP,       /* 本端设置了CHAP协商,但是没有协商通过 */
    LCP_UPCHECK_NEG_NOPAP,        /* 本端设置了PAP协商,但是没有协商通过 */
    LCP_UPCHECK_MHFCLASS,         /* 对端设置了前缀省略协商,但是对端的MHF CALSS等级数大于支持的等级数导致没有协商通过
                                     (原则:MHF选项所协商的class等级数必须包容前缀省略所支持的最大等级) */

    LCP_PAP_AUTH_SERVER_SUCCESS,                /* PAP认证过程中,认证方Server认证成功 */
    LCP_PAP_AUTH_CLIENT_SUCCESS,                /* PAP认证过程中,被认证方Client认证成功 */
    LCP_PAP_AUTH_FAIL_MALLOC_PAP,               /* PAP认证过程中,开始认证时分配PAP控制块失败 */
    LCP_PAP_AUTH_SERVER_FAIL,                   /* PAP认证过程中,认证方Server收到了对端的认证请求,但是认证方认证失败 */
    LCP_PAP_AUTH_SERVER_FAIL_WAITREQ_TIMEOUT,   /* PAP认证过程中,认证方Server等待对端发送验证请求超时 */
    LCP_PAP_AUTH_CLIENT_FAIL_SENDREQ_TIMEOUT,   /* PAP认证过程中,被认证方Client等待对端验证结果超时 */
    LCP_PAP_AUTH_CLIENT_FAIL_SERVER_NAK,        /* PAP认证过程中,被认证方Client被对端拒绝,被认证方认证失败 */
    
    LCP_CHAP_AUTH_SERVER_SUCCESS,               /* CHAP认证过程中,作为认证方Server认证成功 */
    LCP_CHAP_AUTH_CLIENT_SUCCESS,               /* CHAP认证过程中,作为被认证方Client认证成功 */
    LCP_CHAP_AUTH_FAIL_MALLOC_CHAP,             /* CHAP认证过程中,开始认证时分配CHAP控制块失败 */
    LCP_CHAP_AUTH_SERVER_FAIL,                  /* CHAP认证过程中,作为认证方Server认证失败 */
    LCP_CHAP_AUTH_CLIENT_FAIL,                  /* CHAP认证过程中,作为被认证方Client认证失败 */
    
    LCP_FSM_OPEN_RCR,             /* 在OPEN 状态下收到CR报文导致LCPDOWN */
    LCP_FSM_OPEN_RCA,             /* 在OPEN 状态下收到CA报文导致LCPDOWN */
    LCP_FSM_OPEN_RCN,             /* 在OPEN 状态下收到CN报文导致LCPDOWN */
    LCP_FSM_OPEN_RXJ_SUB_CR,      /* 在OPEN 状态下收到RXJ-(code reject)报文导致LCPDOWN */
    LCP_FSM_OPEN_RXJ_SUB_PR,      /* 在OPEN 状态下收到RXJ-(protocol reject)报文导致LCPDOWN */
    LCP_FSM_OPEN_RTR,             /* 在OPEN 状态下收到RTR(Terminate Req)报文导致LCPDOWN */
    LCP_FSM_OPEN_RTA,             /* 在OPEN 状态下收到RTA(Terminate Ack)报文导致LCPDOWN */

    LCP_FSM_REQCI_MAXNAKTOREJ,    /* LCP协商过程中NAK次数达到最大值而REJ该协商参数 */
    
    LCP_FSM_NOT_NEED_NEGO,        /* 本端配置为不协商LCP直接UP,对端设置协商LCP导致本端不处理协商报文,对端协商不过 */
    
    LCP_LOOPBACK_NAK,       /* 协商过程中发现环回,收到了对端的魔术字NAK报文.对端检测到环路,本端会重新生成魔术字后协商 */
    LCP_LOOPBACK_REJ,       /* 协商过程中发现环回,收到了对端的魔术字REJ报文.对端检测到环路,本端会重新生成魔术字后协商 */
    LCP_LOOPBACK_ECHO,      /* ECHO报文探测到环回,从收到的EchoReply报文探测到环回,报文中的魔术字和本端相同 */
    LCP_LOOPBACK_IN_SERIES, /* ECHO报文探测到链路串连,从收到的EchoReply报文探测到串连,
                               报文中的魔术字与协商到的本端魔术字和对端魔术字都不相同,则认为连接错误 */
    LCP_PPP_MP_PARAMS_INCONSISTENT,
    LCP_PPP_ECHO_TIMEOUT,
    LCP_FSM_NEG_RTR,
    LCP_DOT_MAX_END,        /* LCP最大采集数目  */
}NCC_PPPLCPDOT_E;

/* PPP IPCP扫描点ID */
typedef enum enNCC_PPPIPCPDOT
{
    IPCP_FSM_OPEN_RCR,        /* 在OPEN 状态下收到CR报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RCA,        /* 在OPEN 状态下收到CA报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RCN,        /* 在OPEN 状态下收到CN报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RXJ_SUB_CR, /* 在OPEN 状态下收到RXJ-(code reject)报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RXJ_SUB_PR, /* 在OPEN 状态下收到RXJ-(protocol reject)报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RTR,        /* 在OPEN 状态下收到RTR(Terminate Req)报文导致IPCPDOWN */
    IPCP_FSM_OPEN_RTA,        /* 在OPEN 状态下收到RTA(Terminate Ack)报文导致IPCPDOWN */

    IPCP_FSM_REQCI_MAXNAKTOREJ,     /* IPCP协商过程中NAK次数达到最大值而REJ该协商参数 */

    IPCP_FSM_NOT_NEED_NEGO,         /* 本端配置为不协商IPCP直接UP,对端设置协商IPCP导致本端不处理协商报文,对端协商不过 */

    IPCP_IPNEG_NOIPADDR,            /* 本接口未配置地址导致不进行IPCP的协商,从而IPCP协商不过 */

    IPCP_IPCONFLICT_LOCALSAME,      /* 地址协商过程中协商得来地址与本端其他IP冲突 */
    IPCP_UPCHECK_GOTIPCONFLIT_MODE, /* 地址协商过程中对端给本端分配IP，但本端有自己IP导致冲突 */
    IPCP_UPCHECK_IPCONFLIT_PEERSAME,/* 地址协商过程中协商得到的两端IP冲突 */
    IPCP_UPCHECK_HISIPCONFLIT_MODE, /* 地址协商过程中本端给对端分配IP，但对端有自己IP导致冲突 */

    IPCP_UPCHECK_GOTIP_ZERO,        /* 地址协商过程中协商得到的本端地址为0 */
    IPCP_UPCHECK_GOTIP_INVALID,     /* 地址协商过程中协商得到的本端地址无效 */
    IPCP_UPCHECK_HISIP_INVALID,     /* 地址协商过程中协商得到的对端地址无效 */
    IPCP_UPCHECK_IPHCINIT_FAIL,     /* 使能IPHC后初始化上下文失败 */

    IPCP_MPBIND_UPSUBLINKLOWLIMIT,  /* MP绑定的子链路数未到达用户设置的下限导致NCP未启动协商 */
    IPCP_MPBIND_UPTODOWN_UPSUBLINKLOWLIMIT,/* MP的子链路DOWN从MP中移出,或者更改MP下限值导致MP绑定的子链路数未
                                              到达用户设置的下限导致MP IPCP DOWN */
    
    IPCP_DOT_MAX_END,         /* IPCP最大采集数目 */
}NCC_PPPIPCPDOT_E;

/* PPP MUXCP扫描点ID */
typedef enum enNCC_PPPMUXCPDOT
{
    MUXCP_DOT_MAX_END = 1,          /* MUXCP最大采集数目 */
}NCC_PPPMUXCPDOT_E;


/*******************************结构类型定义***********************************/
/* NCC诊断输出信息结构 */
typedef struct tagNCC_OUTPUT
{
    ULONG  ulInfoID;            /* NCC诊断内部输出信息ID    */
    ULONG  ulResultID;          /* NCC诊断结果输出ID        */
    ULONG  ulExecID;            /* NCC诊断以用户执行ID      */
    ULONG  ulNccType;           /* NCC诊断类型              */
    ULONG  ulIfIndex;           /* NCC诊断接口索引          */
    ULONG  ulDetectTime;        /* NCC诊断时间              */
    
    ULONG  ulDiagnoseIndex;     /* 存储该NCC诊断的数组下标  */
 }NCC_OUTPUT_S;

/* PPP类型NCC PPP协商DOWN原因记录结构 */
typedef struct NCC_PPP_DOWNREASON
{
    ULONG ulDownReasonNum;                  /* 当前的Down原因记录下标,大于最大记录数目后自动翻转      */
    ULONG ulDownReason[NCC_PPP_DOT_NUM];    /* Down原因值,0表示没有记录DOWN原因,非0表示记录的DOWN原因 */
}NCC_PPP_DOWNREASON_S;




typedef struct tagNCCPPPLCPOPTION
{
    ULONG negoption;
    USHORT  mru;
    USHORT  mrru;
    UCHAR ucMhfCode; 
    UCHAR ucMhfClass;
    USHORT usGotorHis;     /* 0 - His, 1 -Got */     
    MC_PREFIXE_S stPrefixEInfo;       /*Prefix Info*/
} NCC_PPP_LCP_OPTION_S;


/* PPP类型NCC PPP扫描打点信息记录结构 */
typedef struct NCC_PPP_SCAN_DOT
{
    NCC_PPP_DOWNREASON_S stLcpDownReason;   /* LCP DOWN原因      */
    NCC_PPP_DOWNREASON_S stIpcpDownReason;  /* IPCP DOWN原因     */
    NCC_PPP_DOWNREASON_S stMuxcpDownReason; /* PPPMUXCP DOWN原因 */

    UCHAR   ucLcpScanDot[LCP_DOT_MAX_END];
    UCHAR   ucIpcpScanDot[IPCP_DOT_MAX_END];
    UCHAR   ucMuxcpScanDot[MUXCP_DOT_MAX_END];
    UCHAR   ucPadding[4-((LCP_DOT_MAX_END+(LONG)IPCP_DOT_MAX_END+(LONG)MUXCP_DOT_MAX_END)%4)];
    NCC_PPP_LCP_OPTION_S stLcpOption[2];   /*[0]- will contain the Group Option, [1]- will contain the Sublink Option.*/    
}NCC_PPP_SCAN_DOT_S;


/* PPP类型NCC 统计信息记录结构 */
typedef struct NCC_PPP_COUNT
{
    ULONG ulFirstCount;     /* 统计初始值 */
    ULONG ulLastCount;      /* 统计结束值 */
}NCC_PPP_COUNT_S;

/* PPP类型NCC报文统计结构 */
typedef struct tagNCC_PPP_PKTSTAT
{
    ULONG ulSndPktAll;     /* PPP发送的协商报文总的个数 */
    ULONG ulRcvPktAll;     /* PPP接收的协商报文总的个数 */

    ULONG ulRcvWrongID;    /* PPP收到WRONG ID报文的个数 */

    ULONG ulRcvUnknownCode;/* PPP收到Code字段不识别的报文个数 */
    
    ULONG ulSndLcpRetran;  /* PPP发送的重传报文的次数 */
    ULONG ulSndIpcpRetran; /* PPP发送的重传报文的次数 */
    ULONG ulSndMuxcpRetran;/* PPP发送的重传报文的次数 */

    ULONG ulSndLcpCR;      /* PPP发送的LCP CR协商报文个数 */
    ULONG ulSndIpcpCR;     /* PPP发送的IPCP CR协商报文个数 */
    ULONG ulSndMuxcpCR;    /* PPP发送的MUXCP CR协商报文个数 */

    ULONG ulRcvLcpCR;      /* PPP发送的LCP的CR报文的次数 */
    ULONG ulRcvIpcpCR;     /* PPP发送的收到IPCP的CR报文个数 */
    ULONG ulRcvMuxcpCR;    /* PPP发送的收到PPPMUXCP的CR报文个数 */
    

    ULONG ulSndLcpCA;      /* PPP发送的LCP CA协商报文个数 */
    ULONG ulSndIpcpCA;     /* PPP发送的IPCP CA协商报文个数 */
    ULONG ulSndMuxcpCA;    /* PPP发送的MUXCP CA协商报文个数 */

    ULONG ulRcvLcpCA;      /* PPP发送的收到LCP CA报文的总个数 */
    ULONG ulRcvIpcpCA;     /* PPP发送的收到IPCP CA报文的总个数 */
    ULONG ulRcvMuxcpCA;    /* PPP发送的收到MUXCP CA报文的总个数 */
    

    ULONG ulSndLcpNAK;      /* PPP发送的LCP NAK协商报文个数 */
    ULONG ulSndIpcpNAK;     /* PPP发送的IPCP NAK协商报文个数 */
    ULONG ulSndMuxcpNAK;    /* PPP发送的MUXCP NAK协商报文个数 */

    ULONG ulRcvLcpNAK;      /* PPP发送的收到LCP NAK报文的总个数 */
    ULONG ulRcvIpcpNAK;     /* PPP发送的收到IPCP NAK报文的总个数 */
    ULONG ulRcvMuxcpNAK;    /* PPP发送的收到MUXCP NAK报文的总个数 */
    

    ULONG ulSndLcpTR;      /* PPP发送的LCP TR协商报文个数 */
    ULONG ulSndIpcpTR;     /* PPP发送的IPCP TR协商报文个数 */
    ULONG ulSndMuxcpTR;    /* PPP发送的MUXCP TR协商报文个数 */
    
    ULONG ulRcvLcpTR;      /* PPP发送的收到LCP TR报文的总个数 */
    ULONG ulRcvIpcpTR;     /* PPP发送的收到IPCP TR报文的总个数 */
    ULONG ulRcvMuxcpTR;    /* PPP发送的收到MUXCP TR报文的总个数 */
    

    ULONG ulSndLcpTA;      /* PPP发送的LCP TA协商报文个数 */
    ULONG ulSndIpcpTA;     /* PPP发送的IPCP TA协商报文个数 */
    ULONG ulSndMuxcpTA;    /* PPP发送的MUXCP TA协商报文个数 */
    
    ULONG ulRcvLcpTA;      /* PPP发送的收到LCP TA报文的总个数 */
    ULONG ulRcvIpcpTA;     /* PPP发送的收到IPCP TA报文的总个数 */
    ULONG ulRcvMuxcpTA;    /* PPP发送的收到MUXCP TA报文的总个数 */


    ULONG ulSndLcpConfREJ;     /* PPP发送的LCP CONFREJ协商报文个数 */
    ULONG ulSndIpcpConfREJ;    /* PPP发送的IPCP CONFREJ协商报文个数 */
    ULONG ulSndMuxcpConfREJ;   /* PPP发送的MUXCP CONFREJ协商报文个数 */

    ULONG ulRcvLcpConfREJ;     /* PPP接收的LCP CONFREJ协商报文个数 */
    ULONG ulRcvIpcpConfREJ;    /* PPP接收的IPCP CONFREJ协商报文个数 */
    ULONG ulRcvMuxcpConfREJ;   /* PPP接收的MUXCP CONFREJ协商报文个数 */
    

    ULONG ulSndLcpCodeREJ;     /* PPP发送的LCP CODEREJ协商报文个数 */
    ULONG ulSndIpcpCodeREJ;    /* PPP发送的IPCP CODEREJ协商报文个数 */
    ULONG ulSndMuxcpCodeREJ;   /* PPP发送的MUXCP CODEREJ协商报文个数 */

    ULONG ulRcvLcpCodeREJ;     /* PPP接收的LCP CODEREJ协商报文个数 */
    ULONG ulRcvIpcpCodeREJ;    /* PPP接收的IPCP CODEREJ协商报文个数 */
    ULONG ulRcvMuxcpCodeREJ;   /* PPP接收的MUXCP CODEREJ协商报文个数 */
    

    ULONG ulSndProtREJ;        /* PPP发送的PROTREJ协商报文个数 */
    ULONG ulRcvProtREJ;        /* PPP接收的ROTREJ协商报文个数 */
    
    ULONG ulSndLcpEchoReq;     /* PPP发送的EHCOREQ协商报文个数 */
    ULONG ulSndLcpEchoReply;   /* PPP发送的EHCOREP协商报文个数 */
    
    ULONG ulRcvLcpEchoReq;     /* PPP接收的EHCOREQ协商报文个数 */    
    ULONG ulRcvLcpEchoReply;   /* PPP接收的EHCOREP协商报文个数 */
} NCC_PPP_PKTSTAT;

/* PPP类型NCC 收集信息记录结构 */
typedef struct NCC_PPP_INFO
{
    ULONG ulDiagnoseNum;                        /* 当前的状态记录下标,大于最大记录数目后自动翻转 */
    UCHAR ucIfPhyState[NCC_PPP_DIAGNOSE_NUM];   /* 接口物理状态                                  */
    UCHAR ucIfLineState[NCC_PPP_DIAGNOSE_NUM];  /* 接口IP协议状态                                */
    UCHAR ucLcpState[NCC_PPP_DIAGNOSE_NUM];     /* 接口LCP状态                                   */
    UCHAR ucIpcpState[NCC_PPP_DIAGNOSE_NUM];    /* 接口IPCP协议状态                              */
    UCHAR ucMuxcpState[NCC_PPP_DIAGNOSE_NUM];   /* 接口PPPMUXCP协议状态                          */

    NCC_PPP_COUNT_S stPhyUpCount;               /* 接口底层上报有效物理UP次数                    */
    NCC_PPP_COUNT_S stPhyDownCount;             /* 接口底层上报有效物理DOWN次数                  */    
    NCC_PPP_COUNT_S stLineUpCount;              /* 接口IP协议UP次数                              */
    NCC_PPP_COUNT_S stLineDownCount;            /* 接口IP协议DOWN次数                            */
    ULONG ulLcpOpenCount;                       /* 接口LCP协议UP次数                             */
    ULONG ulLcpDownCount;                       /* 接口LCP协议DOWN次数                           */
    ULONG ulIpcpOpenCount;                      /* 接口IPCP协议UP次数                            */
    ULONG ulIpcpDownCount;                      /* 接口IPCP协议DOWN次数                          */
    ULONG ulMuxcpOpenCount;                     /* 接口PPPMUXCP协议UP次数                        */
    ULONG ulMuxcpDownCount;                     /* 接口PPPMUXCP协议DOWN次数                      */
    
    NCC_PPP_SCAN_DOT_S stPppScanDot;            /* 打点扫描收集的信息                            */
    NCC_PPP_PKTSTAT    stPppStat;               /* PPP协商报文统计信息 */

    VOID *pInfo; /* 该空间由各子信息诊断diagnose过程按需要自己申请并且完成通知在diagnoseoutput时释放 */
}NCC_PPP_INFO_S;

/* PPP类型NCC 诊断信息记录结构 */
typedef struct NCC_DIAGNOSE_PPP
{
    ULONG ulIsUsed;                 /* 该诊断表项是否已被使用,即是否存在诊断.1表示已使用,0表示未使用       */
    ULONG ulExecID;                 /* 用户传入的执行ID,不能为0                                            */
    ULONG ulDetectTime;             /* 用户传入的诊断时间,单位:秒                                          */
    ULONG ulIfIndex;                /* 用户传入的诊断接口索引                                              */
    ULONG ulTimeCount;              /* 循环定时器超时次数,当计数减为0时表示诊断时间到,开始分析输出诊断结果 */
    ULONG ulTimeBase;               /* 循环定时器基数,单位:秒                                              */
    ULONG ulStatisticStartFlag;     /* 获取统计初始值标志,1表示需要获取统计初值,否则(0)不获取              */
    NCC_PPP_INFO_S stNccPppInfo;    /* 记录收集的诊断信息                                                  */
}NCC_DIAGNOSE_PPP_S;


/*******************************全局变量声明***********************************/
/* 记录PPP诊断信息的全局数组变量 */
extern NCC_DIAGNOSE_PPP_S g_stNccDiagnosePpp[NCC_DIAGNOSE_PPP_MAX];

/* PPP类型NCC诊断开关 */
extern ULONG g_ulNccDiagnosePppSwitch;


/*******************************函数声明***********************************/
extern ULONG NCC_InitCom(ULONG ulType);
extern VOID NCC_Release(VOID);
extern VOID NCC_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);
extern ULONG NCC_StartTask(ULONG ulTaskPri);
extern ULONG NCC_IsTaskStart(VOID);
extern ULONG NCC_IsExistUserID(ULONG ulExecID, ULONG *pulType, ULONG *pulDiagnoseIndex);
extern ULONG NCC_IsExistDiagnoseByType(ULONG ulType);
extern ULONG NCC_CheckUserID(ULONG ulExecID);
extern ULONG NCC_CheckParaByType(ULONG ulType, ULONG ulDetectTime, VOID *pstPara, ULONG *pulNccDetectTime);
extern ULONG NCC_CreateTimerByType(ULONG ulType, ULONG *pTimeBase);
extern ULONG NCC_DeleteTimerByType(ULONG ulType);
extern ULONG NCC_SetDiagnoseNccInfo(ULONG ulExecID, ULONG ulDetectTime, ULONG ulType, 
                                            VOID * pstPara, ULONG ulTimeBase);
extern VOID NCC_NotifyRelease(VOID);

extern VOID NCC_DiagnosePppTimerOut(VOID *);
extern ULONG NCC_DiagnosePpp(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppType(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIsShutdown(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppPhyState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLineState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLcpState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIpcpState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLcpDot(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIpcpDot(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppMpInfo(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppStatistic(ULONG ulDiagnoseIndex);

extern VOID NCC_RecordPppState(ULONG ulDiagnoseIndex, IFNET_S *pstIfnet);
extern VOID NCC_RecordIfStatusCount(ULONG ulDiagnoseIndex, IFNET_S *pstIfnet, ULONG ulType);
extern VOID NCC_RecordPppDownReason(ULONG ulIfIndex, ULONG ulDownReason, USHORT usProtoType);
extern VOID NCC_RecordPppLcpDot(ULONG ulLcpDotIndex, ULONG ulIfIndex);
extern VOID NCC_RecordPppIpcpDot(ULONG ulIpcpDotIndex, ULONG ulIfIndex);
extern VOID NCC_RecordPppStateStatistic(ULONG ulIfIndex, UCHAR ucState, USHORT usProtocol);

extern VOID NCC_RecordPppRcvWrongID(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRetran(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvUnknownCode(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndNAK(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvNAK(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndTR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvTR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndTA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvTA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndConfREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvConfREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCodeREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCodeREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndProtREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvProtREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndEchoReq(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvEchoReq(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndEchoReply(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvEchoReply(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndAll(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvAll(PPPFSM_S *pstFsm);

extern VOID NCC_ReleaseOfInfoEnd(ULONG ulType, ULONG ulDiagnoseIndex);
extern VOID NCC_InfoOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
extern VOID NCC_AsynOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
extern VOID NCC_DiagnoseOutput(NCC_OUTPUT_S *pszOutput);
extern VOID NCC_ShowStartInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppUpdownStatistic(ULONG ulDiagnoseIndex, ULONG ulStatType, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppDownReason(NCC_OUTPUT_S *pszOutput, USHORT usProtoType, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppLcpDotInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppIpcpDotInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppDiagnoseInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowMpDiagnoseInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppNegPktStatistic(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);

extern VOID NCC_ShowPppCfgInfo(ULONG ulExecID, ULONG ulDiagnoseIndex);

extern VOID NCC_PrintPppState(ULONG ulPppState, CHAR *szOutBuf, ULONG ulStrLen);

extern VOID NCC_RecordPppInsconsistentOptions(ULONG ulIfIndex, PPP_LCP_OPTION_S *pstGrpOption,
        PPP_LCP_OPTION_S *pstLinkOption,USHORT ulGotFlag);

extern VOID NCC_ShowMPParameterDiffernce(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);

extern VOID NCC_ShowLCPOption(NCC_PPP_LCP_OPTION_S *pstLcpOption, CHAR *pstInfo, ULONG ulStrLen);


#ifdef  __cplusplus 
}
#endif

#endif /* _TCPIP_NCC_H_ */


