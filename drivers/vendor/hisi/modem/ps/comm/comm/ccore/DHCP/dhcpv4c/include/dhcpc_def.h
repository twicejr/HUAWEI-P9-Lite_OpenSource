/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dhcpc_def.h
  版 本 号   : 初稿
  作    者   : c57548
  生成日期   : 2007年11月3日
  最近修改   :
  功能描述   : dhcpc模块的宏定义
  函数列表   :
  修改历史   :
  1.日    期   : 2007年11月3日
    作    者   : c57548
    修改内容   : 创建文件

******************************************************************************/
#ifndef _DHCPC_DEF_H_
#define _DHCPC_DEF_H_

#ifndef AF_INET
#define AF_INET    2               /* internetwork: UDP, TCP, etc. */
#endif

#ifdef __WIN32_PLATFORM__
#include "stdio.h"
#endif

#include "v_typdef.h"
#include "TtfDrvInterface.h"
#include "PsTypeDef.h"

#ifndef VOS_PACKED
#ifdef __WIN32_PLATFORM__
#define     VOS_PACKED
#else
#define     VOS_PACKED      __attribute__ ((__packed__))
#endif
#endif


#define VOS_Assert(lExpression)                                     \
    ( (lExpression)?(VOS_VOID)0:vos_assert( __FILE__, __LINE__ ) )  \

#ifndef VOS_DBGASSERT
#define VOS_DBGASSERT(lExpression)                                  \
    ( (lExpression)?(VOS_VOID)0:vos_assert( __FILE__, __LINE__ ) )  \

#endif

#ifndef VOS_Free
#define VOS_Free(p)                                 { free((p));(p) = NULL; }
#endif

#ifndef VOS_Mem_Zero
#define VOS_Mem_Zero(pBuffPtr, ulLen)               (void)memset((pBuffPtr), (0), (ulLen))
#endif

// handle在D/E/F上都是32位的
#define PGP_MemAlloc(handle, size)  VOS_MemAlloc(handle, DYNAMIC_MEM_PT, size)
#define PGP_MemReMalloc(handle, pOldMemPtr, uvNewSize) VOS_MemAlloc(0, 0, 0)
#define PGP_MemFree(handle, ptr) VOS_MemFree(handle, ptr)
#define PGP_MemZero(ptr, size) VOS_Mem_Zero(ptr, size)

#define MSPS_PID_DHCP UEPS_PID_DHCP
#define MID_DHCPM     MSPS_PID_DHCP
#define MID_DHCPC     MSPS_PID_DHCP
#define MID_DHCPS     MSPS_PID_DHCP
#define MID_DHCPSV6   MSPS_PID_DHCP
#define FSU_TID_DHCP  MSPS_PID_DHCP


#ifndef _lint
typedef unsigned long   ULONG;
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
#endif
typedef signed long     LONG;
typedef signed short    SHORT;

#ifdef _lint
typedef signed char     CHAR;
#endif

typedef unsigned long long ULONG64;
typedef signed long long   LONG64;
#ifndef _lint
typedef unsigned long long UINT64;
#endif
typedef unsigned int    SEC_UINT32;


//typedef VOS_SIZE_T      SIZE_T;
typedef signed int      CDB_RECID;
typedef unsigned short  DMS_IID_T;
typedef unsigned int    DMS_COMMID_T;


typedef void            PF_VOID;
typedef long            PF_LONG;
typedef unsigned long   PF_ULONG;
typedef unsigned char   PF_UCHAR;
typedef short           PF_SHORT;
typedef unsigned short  PF_USHORT;
typedef signed char     PF_CHAR;
typedef unsigned long long PF_DULONG;
typedef int                         SM_LONG;
typedef unsigned int                SM_ULONG;
typedef unsigned char               SM_UCHAR;
typedef SM_ULONG                    SM_BOOL;
typedef void                        SM_VOID;
typedef unsigned long long DULONG;

typedef signed int  CDB_DBID;
typedef signed int  CDB_TBLID;


#define VOS_NTOHS(x)  ((((x)& 0xFF00)>>8) |  (((x) & 0x00FF)<<8))
#define VOS_NTOHL(x) ((((x)&0xff)<<24)|(((x)&0xff00)<<8)|(((x)&0xff0000)>>8)|(((x)&0xff000000)>>24))
#define VOS_HTONS(x)                   ((((x) & 0x00ff) << 8) | \
                                        (((x) & 0xff00) >> 8))
#define VOS_HTONL(x)                   ((((x) & 0x000000ff) << 24) | \
                                        (((x) & 0x0000ff00) <<  8) | \
                                        (((x) & 0x00ff0000) >>  8) | \
                                        (((x) & 0xff000000) >> 24))

/** CRM函数返回成功 */
#ifndef CRM_OK
#define CRM_OK    0
#endif

/** CRM函数返回错误 */
#ifndef CRM_ERROR
#define CRM_ERROR 1
#endif

/** CRM允许操作 */
#ifndef CRM_YES
#define CRM_YES   1
#endif

/** CRM不允许操作 */
#ifndef CRM_NO
#define CRM_NO    0
#endif

#ifndef MC_RWLOCK_ID
#define  MC_RWLOCK_ID    VOS_VOID*
#endif

#define LAP_DHCP_SERVER_INVALID_IP                   0

#if(VRP_MAIN_BOARD == VRP_YES)

/******************************************************************************
    函数类型：CDB_TABLE_INIT_FUN
    描述：表初始化函数类，在C中实现为一个函数，原型为
    VOS_VOID (* CDB_TABLE_INIT_FUN)(TBLID nTbl)

******************************************************************************/

typedef VOS_VOID (* CDB_TABLE_INIT_FUN)(CDB_DBID DBID, CDB_TBLID nTbl);

typedef VOS_VOID (* CDB_CALLBACK_FUN)(CDB_DBID nDBId, CDB_TBLID nTbl, ...);

#else

/******************************************************************************
    函数类型：CDB_TABLE_INIT_FUN
    描述：表初始化函数类，在C中实现为一个函数，原型为
    VOS_VOID (* CDB_TABLE_INIT_FUN)(TBLID nTbl)

******************************************************************************/

typedef VOS_VOID (* CDB_TABLE_INIT_FUN)(CDB_TBLID nTbl);

typedef VOS_VOID (* CDB_CALLBACK_FUN)(CDB_TBLID nTbl, ...);

#endif

typedef enum
{
    PTM_DBG_PRINT_MODULE_PATH,
    PTM_DBG_PRINT_MODULE_MBMS,
    PTM_DBG_PRINT_MODULE_DHCPM,
    PTM_DBG_PRINT_MODULE_PTM_COMM,
    PTM_DBG_PRINT_MODULE_PTM_HASH,
    PTM_DBG_PRINT_MODULE_UGW_BLACK_BOX,
    PTM_DBG_PRINT_MODULE_HSGW_SDU,
    PTM_DBG_PRINT_MODULE_HSGW_FA,
    PTM_DBG_PRINT_MODULE_HSGW_SD,
    PTM_DBG_PRINT_MODULE_HSGW_CMP,
    PTM_DBG_PRINT_MODULE_COMM_FSM,
    PTM_DBG_PRINT_MODULE_A11,
    PTM_DBG_PRINT_MODULE_S6B,
    PTM_DBG_PRINT_MODULE_NW,
    PTM_DBG_PRINT_MODULE_MSE_SC,
    PTM_DBG_PRINT_MODULE_MSD_SDU,
    PTM_DBG_PRINT_MODULE_VAS_SDU,
    PTM_DBG_PRINT_MODULE_BULT,
}PTM_DBG_PRINT_MODULE_E;

/** 获取本SPU板的槽位号 */
#define DVM_SELF_SLOTID (DVM_GetSelfLogicSlotID())

/** 获取本CpuID */
#define DVM_SELF_CPUID (DVM_GetSelfCpuId())

/* 单板类型宏定义 */
#define M_GGSN_CARD_GSPU  2

#define M_CDB_TABLE_FUN_TYPE_TBL_INIT (0)
#define M_CDB_TABLE_FUN_TYPE_REC_APP  (1)
#define M_CDB_TABLE_FUN_TYPE_REC_DEL  (2)
#define M_CDB_TABLE_FUN_TYPE_REC_MOD  (3)
#define M_CDB_TABLE_FUN_TYPE_TBL_MOD  (4)
#define M_CDB_TABLE_FUN_TYPE_REC_NULL (0xFF)

#define M_PTM_SYSTEM_NAME "PTM"

#define M_PTM_MODULE_DHCPM  "DHCPM"

#define M_ALM_PATHDHCPSERVERDOWN  840

#ifndef M_ALM_TYPE_RESTORE
 #define M_ALM_TYPE_RESTORE 0                               /* 恢复告警 */
 #define M_ALM_TYPE_FAULT 1                                 /* 故障告警 */
 #define M_ALM_TYPE_EVENT 2                                 /* 事件告警 */
 #define M_ALM_TYPE_SECURITY 4                              /*安全告警*/
#endif

//Cyjun: 确定是否分段: M_SPM_DPR_ALM等值业务侧明显不用，而平台又定义了这些宏
/*DWORD类型宏定义*/
typedef enum enU_SOFTPARA_DWORD_VALUE
{
    M_SPM_DPR_ALM = 1,/*配电盒告警抑制软参 Added by wangbin 63984 at 2007-11-19 PGPV2R1-NE40E-1 for SRM-PDB */
    M_SPM_DPR_ALMEX = 2,/*配电盒告警抑制软参 Added by wangbin 63984 at 2007-11-19 PGPV2R1-NE40E-1 for SRM-PDB */

    /*begin: add by wangweihua@2008-05-22 for 选择DPE的软参(默认轮选，否则按报文IP地址计算)*/
    M_SPM_PF_FLAG = 3,
    /*end: add by wangweihua@2008-05-22 for 选择DPE的软参(默认轮选，否则按报文IP地址计算)*/

    M_SPM_APN_TIME_THRESHOLD = 4,
    M_SPM_UGW_AAA_TRY_INTERVAL = 5,
    M_SPM_OCS_CONNECT_PORT = 7,  //用于控制ocs建链端口
    M_SPM_CHR_DEVNO = 8,
    M_SPM_CM_INVALID_VOLUME_QUOTA = 21, /* Added by t00159128, 2012/1/31   问题单号:DTS2012011304847 */
    /* BEGIN:Added by h00139187 at 2012-3-22 for PS9.1 DTS2012032202767 【PS9.1 IP组主动质量改进】软参兼容性修改*/
    M_SPM_PF_NEW_FLAG  =  51, /*PS9.1 新增软参使用DWORD51*/
    /* BEGIN: Added by xuyaoqiang, 2012/2/14   问题单号:PS9.2 VF DCCA V2.1 */
    M_SPM_CM_OCSC_QUOTA_ZERO_NPT  =  61,
    /* BEGIN: Added by huangbin 00139187, 2012/7/24 增加软参控制ipsqm cbs*/
    M_SPM_PF_IPSQM_CBS  =  62,
    /* END:   Added by huangbin 00139187, 2012/2/14 增加软参控制ipsqm cbs*/
    /* linyufeng 00176669 DHCPv6特性 2012-07-14 start */
    M_SPM_PTM_DHCP_SERVER_INTERVAL = 71,
    /* linyufeng 00176669 DHCPv6特性 2012-07-14 end */
    M_SPM_IPN_TCP_MSS_DEFAULT_VALUE = 72,
    /*Add by xsm00201057 20130304 for PDSNC06软参移植*/
    M_SPM_PF_PDSN_FLAG = 76,
    /*End by xsm00201057 20130304 for PDSNC06软参移植*/
    M_SPM_PDSN_AAA_TRY_INTERVAL = 78,
    /*Add by xsm00201057 20130520 for PDSN新增costos功能控制软参修改*/
    M_SPM_PF_PDSN_NEW_FLAG = 84,

    M_SPM_DEF_DWORD_END
}U_SOFTPARA_DWORD_VALUE;

/* CDB接口函数错误码 */
#define M_CFG_ERR_DBAPI                     200
#define M_CFG_DB_API_DBERROR                1L
#define M_CFG_DB_API_SUCCESS                VOS_OK
#define M_CFG_DB_API_NOTFOUND               (M_CFG_ERR_DBAPI + 2)   /*202*/
#define M_CFG_DB_API_EMPTY                  (M_CFG_ERR_DBAPI + 3)   /*203*/
#define M_CFG_DB_API_FULL                   (M_CFG_ERR_DBAPI + 4)   /*204*/
#define M_CFG_DB_API_DUPLICATE              (M_CFG_ERR_DBAPI + 5)   /*205*/
#define M_CFG_DB_API_CURSOREND              (M_CFG_ERR_DBAPI + 6)   /*206*/
#define M_CFG_DB_API_PERMISSION_DENIED      (M_CFG_ERR_DBAPI + 7)   /*207*/
#define M_CFG_DB_API_BATCH_NEEDED           (M_CFG_ERR_DBAPI + 8)   /*208*/
#define M_CFG_DB_API_TRANSFER_ERROR         (M_CFG_ERR_DBAPI + 9)   /*209*/
#define M_CFG_ERR_CONDITION_NUM_TOO_MORE    (M_CFG_ERR_DBAPI + 10)  /*210*/
#define M_CFG_ERR_CONDITION_INVALID         (M_CFG_ERR_DBAPI + 11)  /*211*/
#define M_CFG_ERR_DBAPI_UNKNOWN_OPERATOR    (M_CFG_ERR_DBAPI + 12)  /*212*/
#define M_CFG_DB_API_INVALID_PARA           (M_CFG_ERR_DBAPI + 13)  /*213*/
#define M_CFG_DB_API_NOT_MATER_TMN          (M_CFG_ERR_DBAPI + 14)  /*214*/
#define M_CFG_DB_API_RDWR_DISABLE           (M_CFG_ERR_DBAPI + 20)  /*220*/
#define M_CFG_DB_API_RDONLY_ENABLE          (M_CFG_ERR_DBAPI + 21)  /*221*/
#define M_CFG_DB_API_RDWR_ENABLE            (M_CFG_ERR_DBAPI + 22)  /*222*/
#define M_CFG_DB_API_PARAERROR              (M_CFG_ERR_DBAPI + 23)  /*223*/
#define M_CFG_DB_API_REGISTERED             (M_CFG_ERR_DBAPI + 24)  /*224*/
#define M_CFG_DB_API_PRODUCTTYPE_ERROR      (M_CFG_ERR_DBAPI + 25)  /*225*/

/* IPC发送消息成功/失败或接收到消息时的通知方式 */
#define     IPC_NOTI_VIA_NONE   0x00000000
#define     IPC_NOTI_VIA_QUEUE  0x00000001      /* 通过消息通知           */
#define     IPC_NOTI_VIA_FUNC   0x00000002      /* 通过回调函数通知       */

typedef VOID (*IPC_RTNOTIFY_FUNC)
(
    VOS_UINT32 uiFlag,
    VOS_UINT64 ul64DstCsi,
    VOS_VOID * pData,
    VOS_UINT32 uiLen
);

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define VOS_QUEUE_NO_WAIT             ((VOS_UINT32)1 << 5)


typedef enum enumPTM_LOG_LVL_E
{
    PTM_LOG_INFO,   /* 会记录日志，级别为提示，也打印串口 */
    PTM_LOG_WARNING,/* 会记录日志，级别为告警，也打印串口 */
    PTM_LOG_ERR,    /* 会记录日志，级别为错误，也打印串口 */
    PTM_LOG_DEBUG,  /* 不记录日志，只打印串口 */
    PTM_LOG_BUTT
}PTM_LOG_LVL_E;


#ifdef __WIN32_PLATFORM__
#define PTM_DebugPrint PTM_DebugOut_ForPtmDebugOut
#else
#define PTM_DebugPrint(moduletype, level, fmt...) DHCPC_DebugPrint(level, ##fmt)
#endif


#define M_PMIP_BSID_LEN 12
#define M_TWANID_SSID_LEN 32
#define M_TWANID_BSSID_LEN 6
#define M_TWANID_SSID_LEN_INCONTEXT 19

/*ip地址的ulong数目*/
#define LAP_IP_ULONG_NUM     4
/* z00175135 IPv6 Prefix Delegation特性 2012-06-18 start */
#define LAP_ULONG_BIT_NUM   32
/* z00175135 IPv6 Prefix Delegation特性 2012-06-18 end   */

/*MSISDN中用的ULONG数*/
#define LAP_MSISDN_ULONG_NUM        2

//
//msisdn define
//
#define GTP_MAX_MSISDN_LEN             8
typedef UCHAR GTP_MSISDN[GTP_MAX_MSISDN_LEN];

/*LAP2和DHCP模块间交互的消息*/
typedef struct tagLAP2_DHCP_MSG
{
    UCHAR ucMsgType;         /*消息类型，可以是原因值*/
    UCHAR ucSCID:4;            /*SC ID*/
    UCHAR ucAddressType:4;       /*地址类型*/
    UCHAR ucUserType;          /*0  GTPC    1 PPP
                               LAP2_USER_TYPE_GTP 0
                               LAP2_USER_TYPE_PPP 1 */
    UCHAR ucGtpVer;         /*用户类型:V0:0;V1:1;V2:2*/
    ULONG aulPdpAddr[LAP_IP_ULONG_NUM];       /*IP地址*/
    ULONG aulMSISDN[LAP_MSISDN_ULONG_NUM];        /*MSISDN*/
    ULONG ulIndex;             /*上下文索引*/
    /* zhangjinquan 00175135 DHCPv6特性 2012-06-30 start */
    ULONG aulAgentIP[LAP_IP_ULONG_NUM];           /*Agent IP*/
    ULONG aulPrimaryDNS[LAP_IP_ULONG_NUM];
    ULONG aulSecondaryDNS[LAP_IP_ULONG_NUM];
    /* zhangjinquan 00175135 DHCPv6特性 2012-06-30 end   */
    ULONG ulTeidc;            /*TEIDC*/
    USHORT usVpnId;           /*VPN ID*/
    USHORT usPoolIndex;        /*地址池索引*/
    USHORT usDhcpGroupIndex;   /*DHCP服务器组索引*/
    USHORT usApnIndex;         /*APN索引*/
    UCHAR ucStaticIpRouteType;  // TODO:jxm没什么用
    UCHAR ucLAPNo;
    UCHAR ucSectionNum;
#if 0
    UCHAR ucReserve;           /*保留字段*/
#endif
    UCHAR ucRabId;             /*RabId*/
    USHORT enModemId;          /*enModemId*/
}LAP2_DHCPC_MSG_S;

//
//imsi stuct define
//
typedef struct tagGTP_IMSI_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
     UCHAR MCC1  : 4;
     UCHAR MCC2  : 4;
     UCHAR MCC3  : 4;
     UCHAR MNC1  : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN8 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN10: 4;
     UCHAR SPARE : 4;        /* 用1填充 */
#else
     UCHAR MCC2  : 4;
     UCHAR MCC1  : 4;
     UCHAR MNC1  : 4;
     UCHAR MCC3  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN8 : 4;
     UCHAR SPARE : 4;        /* 用1填充 */
     UCHAR MSIN10: 4;
#endif
} GTP_IMSI_S;

#ifndef LAP_IPV4
#define LAP_IPV4 0
#endif
#ifndef LAP_IPV6
#define LAP_IPV6 1
#endif

//
//ipv6 define
//
#define   M_SDB_IPV4_LENGTH                 4
#define   M_SDB_IPV6_LENGTH                 16

/* IP 地址定义*/
typedef VOS_UINT8 DHCPC_IPV4[M_SDB_IPV4_LENGTH];
typedef VOS_UINT8 DHCPC_IPV6[M_SDB_IPV6_LENGTH];

/* IPv6 地址数据结构 */
typedef struct  tagin6_addr
{
    union
    {
        UCHAR        u6_addr8[16];
        USHORT       u6_addr16[8];
        ULONG        u6_addr32[4];
    } in6_u;
    #define s6_addr      in6_u.u6_addr8
    #define s6_addr16    in6_u.u6_addr16
    #define s6_addr32    in6_u.u6_addr32
}in6_addr;

#define M_AM_USM_INVALID_IP_ADDR        0xffffffff
#define M_AM_USM_ADDRTYPE_IPV4        0
#define M_AM_USM_ADDRTYPE_IPV6        1


/***** Type Definitions *****/
typedef struct DLL_NODE{
    struct DLL_NODE *pNext; /* Points at the next node in the list */
    struct DLL_NODE *pPrev; /* Points at the previous node in the list */
    ULONG ulHandle;	        /* 2000/4/21, 该域完全为用户所用，VOS不干涉此域，用户可用此域存储数据 */
}DLL_NODE_S;

typedef struct DLL{
    DLL_NODE_S Head;        /**** Header List Node        ****/
    ULONG      u4_Count;    /**** Number Of Nodes In List ****/
}DLL_S;

#define GNDEBUGTRACE_MAX_LENGTH_REASON 256
#define GNDEBUGTRACE_MAX_LENGTH_SUGGESTION 258

#define M_MNT_MAX_PDP_NUM 11

#define     V_MSGTYPE_DHCPV4    0x01
#define     V_MSGTYPE_DHCPV6    0x02
#define     V_MSGTYPE_ALL        0x03

#define     V_ADDRTYPE_DHCPV4    0x01 /* 1 :DHCP-V接口跟踪, 表示对端IP类型为IPV4 */
#define     V_ADDRTYPE_DHCPV6    0x02 /* 2 :DHCP-V接口跟踪, 表示对端IP类型为IPV6 */

/** SPU Group单板状态变化类型定义 */
typedef enum tagCRM_BRDSTATE_CHG_ENUM
{
    CRM_BRDSTATE_CHG_BEGIN,          /**< BEGIN */
    CRM_BRDSTATE_CHG_SPUREG = 1,     /**< 1,单板注册 */
    CRM_BRDSTATE_CHG_SPURESET,       /**< 2,单板复位 */
    CRM_BRDSTATE_CHG_SPUPULLOUT,     /**< 3,单板被拔出 */
    CRM_BRDSTATE_CHG_CPUREG,         /**< 4,CPU注册 */
    CRM_BRDSTATE_CHG_CPURESET,       /**< 5,CPU复位 */
    CRM_BRDSTATE_CHG_CPUPULLOUT,     /**< 6,CPU被拔出 */
    CRM_BRDSTATE_CHG_PGPREADY,       /**< 7,PGP READY */
    CRM_BRDSTATE_CHG_SERVICEREADY,   /**< 8,Service READY */
    CRM_BRDSTATE_CHG_CPUPGPREADY,    /**< 9,CPU PGP READY */
    CRM_BRDSTATE_CHG_CPUSERVICEREADY,/**< 10,CPU Service READY */
    CRM_BRDSTATE_CHG_SWITCHOFF,      /**< 11,单板CPU休眠消息 */
    CRM_BRDSTATE_CHG_ZOMBIE,         /**< 12,单板Zombie */
    CRM_BRDSTATE_CHG_STANDBY_TO_ACTIVE,    /**< 13,单板由备板升为主板 */
    CRM_BRDSTATE_CHG_ACTIVE_TO_STANDBY,    /**< 14,单板由主板降为备板 */
    CRM_BRDSTATE_CHG_ACTIVE_TO_ACTIVE,     /**< 15,单板注册时状态为主板 */
    CRM_BRDSTATE_CHG_STANDBY_TO_STANDBY,   /**< 16,单板注册时状态为备板 */
    CRM_BRDSTATE_CHG_SGREG,          /**< 17,SG注册 */
    CRM_BRDSTATE_CHG_SGRESET,        /**< 18,SG复位 */
    CRM_BRDSTATE_CHG_SGPGPREADY,     /**< 19,SG PGP READY */
    CRM_BRDSTATE_CHG_SGSERVICEREADY, /**< 20,SG Service READY */
    CRM_BRDSTATE_CHG_TYPE_MAX        /**< 无效单板状态变化类型 */
} CRM_SPUSTATE_CHG_ENUM;

//Cyjun: 产品侧和UFP原来使用SHR_MEM_TYPE_E
//再用宏转换成SERVICE_MEM_TYPE_E，维护成本高，乱，统一为SERVICE_MEM_TYPE_E
/*业务内存类型枚举值*/
typedef enum enSERV_MEM_TYPE_E
{
    SERVICE_MEM_TYPE_SHARE_GLOBAL = 0,
    SERVICE_MEM_TYPE_SHARE_ROUTE,
    SERVICE_MEM_TYPE_SHARE_CONTROL_PLANE,
    SERVICE_MEM_TYPE_SHARE_GM_SC,
    SERVICE_MEM_TYPE_SHARE_GM_PARSER,
    SERVICE_MEM_TYPE_SHARE_SC_DPE_PARSER,
    SERVICE_MEM_TYPE_SHARE_DPE_PARSER_RPT,
    SERVICE_MEM_TYPE_GM0_LAP2_SDU,
    SERVICE_MEM_TYPE_LOCAL,
    SERVICE_MEM_TYPE_END
}SERVICE_MEM_TYPE_E;

#ifndef M_PS_MSG_TYPE_BASE
#define M_PS_MSG_TYPE_BASE 11
#else
#if (M_PS_MSG_TYPE_BASE != 11)
#error
#endif
#endif

/* DHCPM接受队列消息类型定义 */
typedef enum
{
    DHCPM_MSG_TYPE_TIMER = M_PS_MSG_TYPE_BASE, /* 定时器消息 */
    DHCPM_MSG_TYPE_BULT,
}DHCPM_MSG_TYPE_E;

/* DHCPV4 Client接受队列消息类型定义 */
typedef enum
{
    DHCPC_MSG_TYPE_FCM = M_PS_MSG_TYPE_BASE,  /* LAP的FCM响应消息,使用于E板 */
    DHCPC_MSG_TYPE_SERVER,       /* DHCP server响应消息 */
    DHCPC_MSG_TYPE_DHCPV6_SERVER,
    DHCPC_MSG_TYPE_LAP,      /* LAP响应消息 */
    DHCPC_MSG_TYPE_TIMER,    /* 定时器消息 */
    DHCPC_MSG_TYPE_SELF,     /* 自身消息 */

    DHCPC_MSG_TYPE_BATCH_CMD_REQ, /* 处理PTM组批量处理调试命令消息 */
    DHCPC_MSG_TYPE_BULT,
}DHCPC_MSG_TYPE_E;

/* DHCPV4 Server接受队列消息类型定义 */
typedef enum
{
    DHCPS_MSG_TYPE_PF = M_PS_MSG_TYPE_BASE,  /* 来自pf的信令消息, 对应S%luDHCPv4S队列 */
    DHCPS_MSG_TYPE_USM,          /* 来自USM的消息 对应DHCPS_USM队列 */
    DHCPS_MSG_TYPE_TIMER,       /* 定时器消息 对应DST队列 */
    DHCPS_MSG_TYPE_SELF,        /* 自身消息 对应DHCI队列 */
    DHCPS_MSG_TYPE_BULT,
}DHCPS_MSG_TYPE_E;


/* DHCPV6 Server接受队列消息类型定义 */
typedef enum
{
    DHCPV6S_MSG_TYPE_PF = M_PS_MSG_TYPE_BASE, /* 来自pf的信令消息 对应S%luDHCPv6SR队列 */

    DHCPV6S_MSG_TYPE_BULT,
}DHCPV6S_MSG_TYPE_E;

typedef enum tagEMS_CODE_PTM_DHCPC_E
{
    EMS_CODE_DHCPV6C_LEASE_EXPIRE = 1,
    EMS_CODE_DHCPV6C_SERVER_NO_RSP,           /* 服务器无响应 */
    EMS_CODE_DHCPV6C_SERVER_MSG_EXCEPTION,     /* 消息异常 */
    EMS_CODE_DHCPV6C_SERVER_NO_AVAILABLE_ADDR,           /* 服务器无地址 */
    EMS_CODE_DHCPV6C_TID_EXHAUST,              /* Transaction Id耗尽 */
    EMS_CODE_DHCPC_BUFF
}EMS_CODE_PTM_DHCPC_E;

/*LAP2和DHCP之间的消息具体消息类型*/
#define LAP2_SND2_DHCPC_ADDR_REQ_MSG        1   /*LAP2发送给DHCPC的地址申请消息*/
#define LAP2_SND2_DHCPC_ADDR_CONFLICT_MSG   2   /*LAP2发送给DHCPC的地址冲突消息*/
#define LAP2_SND2_DHCPC_ADDR_REL_MSG        3   /*LAP2发送给DHCPC的地址释放消息*/
#define LAP2_SND2_DHCPC_REBUILD_ADD_MSG     4   /*LAP2发送给DHCPC的重建添加消息*/
#define LAP2_SND2_DHCPC_REBUILD_DEL_MSG     5   /*LAP2发送给DHCPC的重建删除消息*/
#define LAP2_SND2_DHCPC_ADDR_FORCE_REL_MSG  6   /*LAP2发送给DHCPC的地址强制回收消息*/
#define LAP2_SND2_DHCPC_IPADDR_RENEW        10  /*LAP2发送给DHCPC的续申请IP地址消息 */
#define LAP2_SND2_DHCPC_ADDR_REN_MSG        12  /*暂时定义待修改*/
#define DHCPC_SND2_LAP2_NO_RSP_MSG          13  /*DHCPC发送给LAP2的DHCP服务器无响应*/
#define DHCPC_SND2_LAP2_LEASE_REL           14  /*地址租期到dhcp发送去活消息给lap2*/
#define DHCPC_SND2_LAP2_REL_CONTEXT         15  /*dhcp 核查去活上下文*/
#define DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG    7
#define DHCPC_SND2_LAP2_ADDR_FAILED_MSG     8
#define DHCPC_SND2_LAP2_ADDR_REL_MSG        9   /*DHCPC发送给LAP2的地址释放消息*/


/*各种跟踪任务类型的全局枚举变量结构体的定义,跟踪类型从0x02开始*/
typedef enum tagEN_TRACE_TYPE
{
    TRC_TYPE_GNGP             = 0X00,      /* Gtpc的Gn/Gp接口跟踪 */
    TRC_TYPE_USER_TYPE          = 0x01,     /* 用户跟踪 */
    TRC_TYPE_DEBUG              = 0x02,     /* Gn免维护 */
    TRC_TYPE_GI                   = 0X03,    /* Gi与AAA的接口跟踪 */
    TRC_TYPE_GA                 = 0X04,     /* Ga接口跟踪 */
    TRC_TYPE_GMB                = 0X06,     /* Gmb接口跟踪 */
    TRC_TYPE_GY                 = 0X07,
    TRC_TYPE_MBMS_SESSION       = 0X08,
    TRC_TYPE_GX                 = 0x09,     /* GX接口跟踪 */
    //Begin:added by c00110835 for 跟踪适配
    TRC_TYPE_EXTERN_SGW_S4S11S12S1U    = 0X0A,     /* SGW的S4/S11/S12/S1-U外部接口跟踪 */
    TRC_TYPE_EXTERN_SGW_S5S8           = 0x0B,     /* SGW的S5/S8外部接口跟踪 */
    TRC_TYPE_EXTERN_PGW_S5S8S2AS2BGNGP    = 0x0C,     /* PGW的S5/S8/S2a/Gn/Gp外部接口跟踪 */
    //End:added by c00110835 for 跟踪适配
    TRC_TYPE_GIS6B              = 0x0D,     /* Gi/S6b接口跟踪 */
    TRC_TYPE_EXT_IPPM       = 0x0E,     /* IPPM外部接口跟踪 */
    TRC_TYPE_IPPM               = 0x0F,     /* IPPM接口跟踪 */
    TRC_TYPE_TCP                = 0x10,     /* TCP层的消息跟踪 */
    TRC_TYPE_IKE                 = 0x11,                          /* IKE  消息跟踪 */
    //Begin:added by c00110835 for 模块间内部跟踪
    TRC_TYPE_INTER_MODULE               = 0x15,
    TRC_TYPE_USER_INTER_TYPE            = 0x16,
    TRC_TYPE_GA_INTER                   = 0x14,
    TRC_TYPE_GI_INTER                   = 0x1D,
    //End:added by c00110835 for 模块间内部跟踪
    TRC_TYPE_SGW_S4S11S12S1U    = 0X1A,     /* SGW的S4/S11/S12/S1-U接口跟踪 */
    TRC_TYPE_SGW_S5S8           = 0x1B,     /* SGW的S5/S8接口跟踪 */
    TRC_TYPE_PGW_S5S8S2AGNGP    = 0x1C,     /* PGW的S5/S8/S2a/Gn/Gp接口跟踪 */
    /* BEGIN: Added for PN:DTS2011032301715  for gy内部跟踪 by wujin 00167715, 2011/3/24 */
    TRC_TYPE_GY_INTER                   = 0x17,
    /* END:   Added for PN:DTS2011032301715  for gy内部跟踪 by wujin 00167715, 2011/3/24 */
    TRC_TYPE_GX_INTER                   = 0x19,
    TRC_TYPE_V                  = 0x1E, /* DHCP信令的V接口跟踪 */
    TRC_TYPE_GCF                    = 0x1F,
    TRC_TYPE_PDSN_USER = 0x20,
    TRC_TYPE_PI = 0x21,
    TRC_TYPE_RPCSN = 0x22,
    TRC_TYPE_STA = 0x23,
    TRC_TYPE_SCCG_SESSION           = 0x24, /*SCCG用户跟踪*/
    TRC_TYPE_S6B              = 0x25,     /* Gi/S6b接口跟踪 */
    TRC_TYPE_EPSNUSER         = 0x26,     /*EPSN用户跟踪*/
    TRC_TYPE_S6B_INTER = 0x27,
    TRC_TYPE_BUTT

}E_TRACE_TYPE;



//
//imei stuct define
//
#define GTP_MAX_IMEI_LEN 8
typedef struct tagGTP_IMEI_S
{
    UCHAR     Value[GTP_MAX_IMEI_LEN];
} VOS_PACKED GTP_IMEI_S;


#define SDB_INVALID_IP_ADDR   0xffffffff         /* 无效的IP地址*/
#define SDB_INVALID_INDEX   0xFFFFFFFF
#define MAX_IDENTIFY_LEN 64
#define MAX_MACADDRESS_LEN 6
#define MAX_IPV6_LEN 8
#define MAX_3GPP_SESSION_LEN 24
#define MAX_BRAS_SESSION_LEN 36
#define MAX_MULTI_SESSION_LEN 36
#define MAX_CONGESTION_RPT_ULI_LEN 8
#define SCCG_MAX_L2_LEN 28
#define SCCG_MIN_L2_LEN  12
#define SDB_BUILD_OPER 0
#define SDB_DEL_OPER 1
#define SDB_STRING_CONSIST               0 /*字符串相同*/


/*===================================================================================*
* packet filter内容结构，协议中有描述                                               *
*===================================================================================*/
typedef struct tagSDB_FILTER_CONTENT_S
{
  ULONG  ulIPSecSpi;                            /* IPSec SPI */
  USHORT usSourcePortNoLowLmt;    /* 源端口号变化范围的下限 */
  USHORT usSourcePortNoHiLmt;     /* 源端口号变化范围的上限 */
  USHORT usDestPortNoLowLmt;      /* 目的端口号变化范围的下限 */
  USHORT usDestPortNoHiLmt;       /* 目的端口号变化范围的上限 */
  UCHAR  ucProtocolNum;                         /* protocol number for ipv4 or next header type for ipv6 */
  UCHAR  ucTos;                                 /* Type of service */
  UCHAR  ucTosMask;                             /* TOS mask */
  UCHAR  ucEvalIndex;                           /* packet filter evaluation precedence */

  in6_addr in6DestIP;                 /* 目的地址 */
  in6_addr in6SourceIP;               /* 源地址 */
  UCHAR    ucSourceIPMask;                        /* 源地址子网掩码长度 */
  UCHAR    ucDestIPMask;                          /* 目的地址子网掩码长度*/
  UCHAR    usIPVersionFlag  : 2;                   /*IP的版本，0:IPV4; 1:IPV6*/
  UCHAR    usSrcIPFlag      : 1;                    /*如果源IP有效，置1*/
  UCHAR    usDstIPFlag      : 1;                    /*如果目的IP有效，置1*/
  UCHAR    usIPSecSPIFlag   : 1;                    /*如果IPSecSPI有效，置1*/
  UCHAR    usSrcPortRngFlag : 1;                    /*如果源端口范围有效，置1*/
  UCHAR    usDstPortRngFlag : 1;                    /*如果目的端口范围有效，置1*/
  UCHAR    usProtocolFlag   : 1;                    /*如果协议域有效，置1*/
  UCHAR    usTOSFlag        : 1;                    /*如果TOS和TOSMask有效，置1 */
  UCHAR    usPriorityFlag   : 1;                    /*如果优先级有效，置1*/
  UCHAR    usFlowLabelFlag:1;           /*如果流标有效，置1*/
  UCHAR usGateStatusFlag : 1;          /*如果Gate关闭，为0，否则为1*/
  UCHAR usUpDir          : 1;                       /*0：表示Filter不用于上行，1：表示用于上行*/
  UCHAR usDownDir        : 1;                       /*0：表示Filter不用于下行，1：表示用于下行*/
  /* BEGIN: Added by l50262 for 静态pcc, 2009/3/25 */
  UCHAR    usSmPccCrtFlg : 1;                       /*标记为此次sm 静态pcc创建，置1*/
  UCHAR    usSmPccCrtFilter : 1;                       /*标记filter由sm 静态pcc创建，置1*/
  /* END:   Added by l50262 for 静态pcc, 2009/3/25 */
  UCHAR ucFlag;                    /*有效标记*/
  UCHAR ucIsSrcPortRng :1;  /*表示源端口为区间范围还是只有端口号:1表示范围;0表示端口*/
  UCHAR ucIsDstPortRng :1;  /*表示目的端口为区间范围还是只有端口号:1表示范围;0表示端口*/
  UCHAR ucReverd : 6;
  UCHAR ucEvalIndexUp;      /*对于PCRFC下发的一个filter同时是上下行的情况下 用于存储上行对应的网关分配的优先级*/
  UCHAR ucReserv;
  ULONG ulFlowLabel;                /*flow loabel type(ipv6)*/
} VOS_PACKED SDB_FILTER_CONTENT_S;
typedef struct tagSDB_FILTER_S
{
  UCHAR ucFilterId;
  /* Modified start by hourufeng 00139414 for Gx融合 2011.8.30*/
  /*filter操作码，目前仅供Gx融合GGSN使用，根据此操作码从filter list中判断出当前要操作的filter
    GTPC_CREATE_NEW_TFT、GTPC_DELETE_EXISTING_TFT不需要赋值*/
  UCHAR ucFilterOpCode;
  /* Modified end by hourufeng 00139414 for Gx融合 2011.8.30*/
  SDB_FILTER_CONTENT_S stFilterContent;
  ULONG ulNwFilterId;
  ULONG ulNwFilterIdSecond;
  struct tagSDB_FILTER_S * pstNext;
} VOS_PACKED SDB_FILTER_S;

/*===================================================================================*
* GSPU板上TFT信息结构                                                               *
*===================================================================================*/
typedef struct tagSDB_TFT_S
{
  SDB_FILTER_S *pstFilter;
  UCHAR         ucFilterNum;
  UCHAR         ucReserved;
  USHORT        usFilterOperIndic;/*被操作的filter标识*/
} VOS_PACKED SDB_TFT_S;

typedef struct tag3GPP_PDP_Str
{
  ULONG ulAcctSessionLen;
  UCHAR ulAcctSessionId[MAX_3GPP_SESSION_LEN];   /* acct session id */
  SDB_TFT_S* pstTft;
  struct tag3GPP_PDP_Str* pNext;
}GTP_PDP_Str;

typedef struct tagAM_IPN_MSE_PROFILE_INFO_S
{
    USHORT ausMseProfileId[8];
    UCHAR aucMseProfileIdOP[8];
    UCHAR ucMseProfileNum;
    UCHAR ucResved[7];
} AM_IPN_MSE_PROFILE_INFO_S;

/* QOS的定义 */
/*
 *上下文中保存的QoS(12 Byte) -------
 */

typedef struct tagGTP_GGSN_QOS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucReliabilityClass       : 3;
    UCHAR  ucDelayClass             : 3;
    UCHAR  ucSpare1                 : 2;
    UCHAR  ucPrecedenceClass        : 3;
    UCHAR  ucSpare2                 : 1;
    UCHAR  ucPeakThroughput         : 4;
    UCHAR  ucMeanThroughput         : 5;
    UCHAR  ucSpare3                 : 3;
    UCHAR  ucDeliveryErroSdu        : 3;
    UCHAR  ucDeliveryOrder          : 2;
    UCHAR  ucTrafficClass           : 3;
    UCHAR  ucMaxSduSize;
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucSduErrorRatio          : 4;
    UCHAR  ucResidualBer            : 4;
    UCHAR  ucTrafficHandlPriority   : 2;
    UCHAR  ucTransferDelay          : 6;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucSourceStatisticsDescriptor  : 4;
    UCHAR  ucSignallingIndication         : 1;
    UCHAR  ucSpare4                         : 3;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucAllocaRetentPriority;
#else
    UCHAR  ucSpare1                 : 2;
    UCHAR  ucDelayClass             : 3;
    UCHAR  ucReliabilityClass       : 3;
    UCHAR  ucPeakThroughput         : 4;
    UCHAR  ucSpare2                 : 1;
    UCHAR  ucPrecedenceClass        : 3;
    UCHAR  ucSpare3                 : 3;
    UCHAR  ucMeanThroughput         : 5;
    UCHAR  ucTrafficClass           : 3;
    UCHAR  ucDeliveryOrder          : 2;
    UCHAR  ucDeliveryErroSdu        : 3;
    UCHAR  ucMaxSduSize;
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucResidualBer            : 4;
    UCHAR  ucSduErrorRatio          : 4;
    UCHAR  ucTransferDelay          : 6;
    UCHAR  ucTrafficHandlPriority   : 2;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucSpare4                                    : 3;
    UCHAR  ucSignallingIndication               : 1;
    UCHAR  ucSourceStatisticsDescriptor      : 4;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucAllocaRetentPriority;
#endif
} VOS_PACKED GTP_GGSN_QOS_S,CDRF_GTP_QOS_S;

typedef struct tagGTP_SAE_QOS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR ucPreemptionVulnerability : 1;
    UCHAR ucSpare2 : 1;
    UCHAR ucAllocaRetentPriority : 4;
    UCHAR ucPreemptionCapability : 1;
    UCHAR ucSpare1 : 1;

    UCHAR  ucVer : 4;
    UCHAR  ucQosClassIdentifier    : 4;/*保存用户的业务qci，取值范围1-9，用于命令行配置以及给转发下表项*/
#else
    UCHAR ucSpare1 : 1;
    UCHAR ucPreemptionCapability : 1;
    UCHAR ucAllocaRetentPriority : 4;
    UCHAR ucSpare2 : 1;
    UCHAR ucPreemptionVulnerability : 1;

    UCHAR  ucQosClassIdentifier    : 4;/*保存用户的业务qci，取值范围1-9，用于命令行配置以及给转发下表项*/
    UCHAR  ucVer : 4;
#endif
    UCHAR  ucRealQci;  /*用来保存用户的真实qci，支持扩展，取值范围1-扩展最大值，用于封装消息*/
    UCHAR  ucTrafficHandlPriority;
    UCHAR  aucMaxBitRateUp[5];          //后4字节为主机序
    UCHAR  aucMaxBitRateDown[5];        //后4字节为主机序
    UCHAR  aucGuarantBitRateUp[5];      //后4字节为主机序
    UCHAR  aucGuarantBitRateDown[5];    //后4字节为主机序
} VOS_PACKED GTP_SAE_QOS_S;

typedef union unGTP_QOS
{
    GTP_GGSN_QOS_S    stGgsnQos; /* GGSN产品QOS类型 */
    GTP_SAE_QOS_S     stSaeQos;  /* SAE产品QOS类型 */
} VOS_PACKED unGTP_QOS;

typedef struct tagGTP_QOS_S
{
    unGTP_QOS unCommonQos;
} VOS_PACKED GTP_QOS_S;

typedef struct tagAPN_AMBR_S
{
    ULONG ulAmbrUL;
    ULONG ulAmbrDL;
}VOS_PACKED APN_AMBR_S;

typedef struct tagMEDIA_DETECT_S
{
    GTP_QOS_S           stLastSavedNormReqQos;
    GTP_QOS_S           stLastSavedNormNegQos;
    /*用于保存此次内容感知流程之前上下文中的AMBR值,当此次流程失败时进行回退*/
    APN_AMBR_S          stLastSaveAmbr;
    /*用于保存IPN发起内容感知流程前上下文中的AMBR值,或者左侧发起更新后的AMBR值,用于IPN发起qos回落流程时使用(usReqQoSLevel为0)*/

    /*4G时存储IPN触发前的QOS信息，用于老化回退*/
    GTP_QOS_S           stOriginSavedNormReqQos;
    GTP_QOS_S           stOriginSavedNormNegQos;
    APN_AMBR_S          stOriginAmbr;

}  VOS_PACKED MEDIA_DETECT_S;

//
//l2tp define
//
typedef struct tagSDB_L2TP_INFO
{
    ULONG  ulMagicNum;                            /* Magic-Number LCP */
    ULONG  ulAccm;                              /* ACCM */
    ULONG ulGiifIndex;
    USHORT usMtu;
    USHORT usLocalTunnelId;                  /* local_tunnel_id  */
    USHORT usLocalSessionId;                  /* local_session_id */
    USHORT usLocalPort;
    ULONG  ulLocalIP;
    ULONG  ulPeerIP;
    USHORT usPeerTunnelId;                  /* Peer_tunnel_id  */
    USHORT usPeerSessionId;                  /* Peer_session_id */
    ULONG  ulMSIP;
    USHORT usPeerPort;
    UCHAR  ucVer;
    UCHAR  ucPppMode;
    UCHAR  ucDpeId;
    UCHAR  Res[3];
} SDB_L2TP_INFO_S;

//
//gtpv2 servinc network define
//

typedef struct tagAM_GTPV2_SERVING_NETWORK_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif
} VOS_PACKED AM_GTPV2_SERVING_NETWORK_S;

//
//gtpv2 USER LOCATION define
//
/*USER LOCATION INFOMATION IE*/
#define GTP_MAX_USER_LOCATION_INFO_LEN 8
typedef   struct    tagGTP_USER_LOCATION_INFO_S
 {
    UCHAR  ucGeographicLocationType;
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
     UCHAR    MCC1  : 4;
     UCHAR    MCC2  : 4;
     UCHAR    MCC3  : 4;
     UCHAR    MNC3  : 4;
     UCHAR    MNC1  : 4;
     UCHAR    MNC2  : 4;

#else
     UCHAR  MCC2  : 4;
     UCHAR  MCC1  : 4;
     UCHAR  MNC3  : 4;
     UCHAR  MCC3  : 4;
     UCHAR  MNC2  : 4;
     UCHAR  MNC1  : 4;
#endif
  USHORT LAC;
   union   unCiOrSac
     {
         USHORT usCI;
         USHORT usSAC;
      } ciOrSac;

#define  CI  ciOrSac.usCI
#define  SAC   ciOrSac.usSAC
} VOS_PACKED  GTP_USER_LOCATION_INFO_S;

/*lint -align_max(push) -align_max(1)*/
//
//gtp rai define
//
typedef struct tagGTP_RAI_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  MCC1  : 4;
    UCHAR  MCC2  : 4;
    UCHAR  MCC3  : 4;
    UCHAR  MNC3  : 4;
    UCHAR  MNC1  : 4;
    UCHAR  MNC2  : 4;
    USHORT LAC;
    UCHAR  RAC;
#else
    UCHAR  MCC2  : 4;
    UCHAR  MCC1  : 4;
    UCHAR  MNC3  : 4;
    UCHAR  MCC3  : 4;
    UCHAR  MNC2  : 4;
    UCHAR  MNC1  : 4;
    USHORT LAC;
    UCHAR  RAC;
#endif
}VOS_PACKED  GTP_RAI_S;
/*lint -align_max(pop)*/

typedef struct tagGTP_GGSN_ULI_S
{
    GTP_USER_LOCATION_INFO_S stUserLocationInfo; /*8*/
    GTP_RAI_S stRAI; /*6*/
    GTP_RAI_S stOldRAI;     /*6*/
}VOS_PACKED GTP_GGSN_ULI_S;

typedef struct tagAM_GTPV2_ULI_TAI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    VOS_UINT16 usTrackingAreaCode;
} VOS_PACKED AM_GTPV2_ULI_TAI_S;

typedef struct tagAM_GTPV2_ULI_ECGI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
#if UGW_BYTE_ORDER == UGW_BIG_ENDIAN
            VOS_UINT32 btReserved:4;
            VOS_UINT32 btECI:28;
#else
            VOS_UINT32 btECI:28;
            VOS_UINT32 btReserved:4;
#endif


} VOS_PACKED AM_GTPV2_ULI_ECGI_S;

typedef struct tagAM_GTPV2_ULI_LTE_S
{
    AM_GTPV2_ULI_TAI_S stTAI;/*5*/
    AM_GTPV2_ULI_ECGI_S stECGI;/*7*/
} VOS_PACKED GTPV2_ULI_LTE_S;

//
//gtpv2 uli define
//

typedef struct tagAM_GTPV2_ULI_CGI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usCellIdentity;
} VOS_PACKED AM_GTPV2_ULI_CGI_S;

typedef struct tagAM_GTPV2_ULI_SAI_S
{
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usServiceAreaCode;
} VOS_PACKED AM_GTPV2_ULI_SAI_S;


typedef struct tagAM_GTPV2_ULI_RAI_S
{
    VOS_UINT16 usLocationAreaCode;
    VOS_UINT16 usRoutingAreaCode;
} VOS_PACKED AM_GTPV2_ULI_RAI_S;

typedef struct tagAM_GTPV2_ULI_GU_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif  /*3*/
    AM_GTPV2_ULI_CGI_S stCGI;/*7*/
    AM_GTPV2_ULI_SAI_S stSAI;/*4*/
    AM_GTPV2_ULI_RAI_S stRAI;/*4*/
} VOS_PACKED GTPV2_ULI_GU_S;

typedef union unGTP_SAE_ULI_S
{
    GTPV2_ULI_LTE_S stGtpv2LteULI;/*12*/
    GTPV2_ULI_GU_S  stGtpv2GuUli;/*18*/
} VOS_PACKED unGTP_SAE_ULI_S;

typedef struct tagAM_GTPV2_ULI_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btReserved:3;
    VOS_UINT8 btECGI:1;
    VOS_UINT8 btTAI:1;
    VOS_UINT8 btRAI:1;
    VOS_UINT8 btSAI:1;
    VOS_UINT8 btCGI:1;
#else
    VOS_UINT8 btCGI:1;
    VOS_UINT8 btSAI:1;
    VOS_UINT8 btRAI:1;
    VOS_UINT8 btTAI:1;
    VOS_UINT8 btECGI:1;
    VOS_UINT8 btReserved:3;
#endif  /*1*/
    unGTP_SAE_ULI_S unCommonULI;   /*18*/
} VOS_PACKED GTP_SAE_ULI_S;

typedef struct tagGTP_PMIP_BSID_S
{
    /*BSID PCC模块下发,传给CM*/
    UCHAR aucBSID[M_PMIP_BSID_LEN + 1];
    /*BSID是否有效标志*/
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR btBSID:1;
    UCHAR btReserved:7;
#else
    UCHAR btReserved:7;
    UCHAR btBSID:1;
#endif
    UCHAR aucReserved[2];
}VOS_PACKED GTP_PMIP_BSID_S;

/*由于目前不能增加上下文内存,因此将TWAN Identifier信元拆分成两部分来进行保存,SSID部分和uli
共用,uli结构体原有长度是20,因此虽然协议定义SSID长度最大为32,目前也只保存19个字节(SE确认目前
有局点使用到17个字节,再长的目前还没有看到)(s2a接入时肯定不会携带uli因此可以共用)*/
typedef struct tagGTP_TWAN_ID_SSID_S
{
    UCHAR ucSSIDLen;
    UCHAR aucSSID[M_TWANID_SSID_LEN_INCONTEXT];
}VOS_PACKED GTP_TWAN_ID_SSID_S;

typedef union unGTP_ULI
{
    GTP_GGSN_ULI_S stGgsnUliAndRai; /* GGSN产品QOS类型20 */
    GTP_SAE_ULI_S  stSaeULI;  /* SAE产品QOS类型 19 */
    GTP_PMIP_BSID_S stPmipBsid;
    GTP_TWAN_ID_SSID_S stTwanSSID;
} VOS_PACKED unGTP_ULI;

typedef struct tagGTP_ULI_S
{
    unGTP_ULI unCommonULI;    /*20*/
} VOS_PACKED GTP_ULI_S;

//
//pco define
//
#define GTP_MAX_ADDITIONALTRACEINFO_LEN 8
#define GTP_MAX_PROTO_CFG_OPTION_LEN   253
typedef struct tagGTP_ADDITIONALTRACEINFO_S
{
    UCHAR     Value[GTP_MAX_ADDITIONALTRACEINFO_LEN];
} VOS_PACKED GTP_ADDITIONALTRACEINFO_S;

//
//qos define
//
typedef struct tagGTP_QOS_NECESSARY_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucTrafficClass       : 4;
    UCHAR  ucDelayClass         : 4;
    UCHAR  ucPeakThroughput     : 4;
    UCHAR  ucPrecedenceClass    : 3;
    UCHAR  ucReserved           : 1;
    UCHAR  ucSpare1;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucTrafficHandlPriority;
    ULONG  ulGuarantBitRateUp;     /*该字段专用于UGW*/
    ULONG  ulGuarantBitRateDown;  /*该字段专用于UGW*/
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucSpare2;
    UCHAR  ucRealQci;
#else
    UCHAR  ucDelayClass           : 4;
    UCHAR  ucTrafficClass         : 4;
    UCHAR  ucReserved             : 1;
    UCHAR  ucPrecedenceClass      : 3;
    UCHAR  ucPeakThroughput       : 4;
    UCHAR  ucSpare1;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateDownExtended;
    UCHAR  ucTrafficHandlPriority;
    ULONG  ulGuarantBitRateUp;   /*该字段专用于UGW*/
    ULONG  ulGuarantBitRateDown; /*该字段专用于UGW*/
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucSpare2;
    UCHAR  ucRealQci;
#endif
}VOS_PACKED GTP_QOS_NECESSARY_S;

typedef struct tag3GPP_SGSN_MCC_MNC_S       /*  SGSN_MCC_MNC结构  */
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN   /*  小端字序  */
    UCHAR MCC1  : 4;
    UCHAR MCC2  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC1  : 4;
    UCHAR MNC2  : 4;
    UCHAR MNC3  : 4;
#else

    UCHAR MCC2  : 4;
    UCHAR MCC1  : 4;
    UCHAR MNC1  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC3  : 4;
    UCHAR MNC2  : 4;
#endif
    UCHAR ucFlag;   /* 是否有效的标志，取代原来的全f判断方式，并补齐了4字节。0无效，1有效 */
} T3GPP_SGSN_MCC_MNC_S; /*  SGSN_MCC_MNC结构  */

//
//am cm used define
//

typedef struct tagAM_CM_UPDATETYPE
{
    UCHAR  ucVersionChangeFlag:1; /* PDP版本变化 */
    UCHAR  ucQosChangeFlag:1;  /* QOS:表明终端用户商议的QoS变化导致DCC客户端请求更新 */
    UCHAR  ucSgsnChangeFlag:1; /* SGSN:表明SGSN IP地址变化导致DCC客户端请求更新 */
    UCHAR  ucUserLocChangeFlag:1; /* LOCATION表明终端用户位置变化导致DCC客户端请求更新 */
    UCHAR  ucRatChangeFlag:1;  /* RAT: 表明无线接入技术变化导致DCC客户端请求更新 */
    UCHAR  ucPLMNChangeFlag:1; /* 表明PLMN变化导致DCC客户端请求更新 */
    UCHAR  ucRoamingChangeFlag:1; /* 漫游变化 */
    UCHAR  ucTFTChangeFlag:1;  /* 改为TFT变换 */

    UCHAR  ucTimeZoneChangeFlag :1; /* 表明msTimeZone变化导致DCC客户端请求更新 */
    UCHAR  ucRaiChangeFlag :1;  /* 表明RAI改变 */
    UCHAR  ucRoleChangeFlag : 1;  /*表明角色改变*/
    UCHAR  ucUpdateUplink            : 1;
    UCHAR  ucUpdateDownlink          : 1;
    UCHAR  ucUpdateIndirectForward   : 1;
    UCHAR  ucUpdateLiFlag            : 1;
    UCHAR  ulUpdateEndMarkFlag       : 1; /* EndMarker标识. 1: 下发表项时需要等待转发的响应. 0: 不需要等待, 默认为0
                                             在Update User Plane 流程中,需要等待转发的响应,用于出发End Marker消息 */
    UCHAR  ucLossOfBearerFlag:1;
    UCHAR  ucRecoveryOfBearerFlag:1;
    UCHAR  ucMaxNRBearerReachedFlag:1;
    UCHAR  ucQosChangeExceedAuthFlag:1;
    UCHAR  ucIpCanChangeFlag:1;
    UCHAR  ucGWMalfunctionFlag :1;
    UCHAR  ucResourcesLimatitionFlag :1;
    UCHAR  ucNoEventTriggerFlag:1;

    UCHAR  ucCoaUserProfileChangeFlag:1;  /* AAA发起的CoA更新,UserProfile变化 */
    UCHAR  ucMMEChangeFlag:1;    /* MME IP地址变化 */
    UCHAR  ucSGWChangeFlag:1;    /* SGW IP地址变化 */
    UCHAR  ucIPAllcationFlag:1;  /* UE_IP_ADDRESS_ALLOCATE  */
    UCHAR  ucIPReleaseFlag:1;    /* UE_IP_ADDRESS_RELEASE */
    UCHAR  ucCGIPChangeFlag:1;
    UCHAR  ucSessionStopIndication:1; /* For CM last deleted bear */
    UCHAR  ucIdletimeFlag :1;

    UCHAR  ucCGIChangeFlag:1; /* ULI中的CGI变化*/
    UCHAR  ucSAIChangeFlag:1; /* ULI中的SAI变化*/
    UCHAR  ucECGIChangeFlag:1; /* ULI中的ECGI变化*/
    UCHAR  ucTAIChangeFlag:1; /* ULI中的TAI变化*/
    UCHAR  ucQosTrafficClass     :1;    /* CHANGE_IN_QOS_TRAFFIC_CLASS */
    UCHAR  ucQosRelClass         :1;    /* CHANGE_IN_QOS_RELIABILITY_CLASS */
    UCHAR  ucQosDelayClass       :1;    /* CHANGE_IN_QOS_DELAY_CLASS */
    UCHAR  ucQosPeakThr          :1;    /* CHANGE_IN_QOS_PEAK_THROUGHPUT */

    UCHAR  ucQosPrecedenceClass  :1;    /* CHANGE_IN_QOS_PRECEDENCE_CLASS */
    UCHAR  ucQosMeanThroughput   :1;    /* CHANGE_IN_QOS_MEAN_THROUGHPUT */
    UCHAR  ucQosMBRForUp         :1;    /* CHANGE_IN_QOS_MAXIMUM_BIT_RATE_FOR_UPLINK */
    UCHAR  ucQosMBRForDown       :1;    /* CHANGE_IN_QOS_MAXIMUM_BIT_RATE_FOR_DOWNLINK */
    UCHAR  ucQosResidualBer      :1;    /* CHANGE_IN_QOS_RESIDUAL_BER */
    UCHAR  ucQosSduErrRadio      :1;    /* CHANGE_IN_QOS_SDU_ERROR_RATIO */
    UCHAR  ucQosTransferDelay    :1;    /* CHANGE_IN_QOS_TRANSFER_DELAY */
    UCHAR  ucQosTrafficHandpri   :1;    /* CHANGE_IN_QOS_TRAFFIC_HANDLING_PRIORITY */

    UCHAR  ucQosGBRForUp         :1;    /* CHANGE_IN_QOS_GUARANTEED_BIT_RATE_FOR_UPLINK */
    UCHAR  ucQosGBRForDown       :1;    /* CHANGE_IN_QOS_GUARANTEED_BIT_RATE_FOR_DOWNLINK */
    UCHAR  ucLocMcc              :1;    /* CHANGE_IN_LOCATION_MCC */
    UCHAR  ucLocMnc              :1;    /* CHANGE_IN_LOCATION_MNC */
    UCHAR  ucLocRac              :1;    /* CHANGE_IN_LOCATION_RAC */
    UCHAR  ucLoclac              :1;    /* CHANGE_IN_LOCATION_LAC  */
    UCHAR  ucLocCellid           :1;    /* CHANGE_IN_LOCATION_CellId */
    UCHAR  ucTmoCoaChangeFlag    :1;    /* AAA下发Coa消息触发的更新 */

    UCHAR  ucDTChangeFlag        :1;  /* DT模式变化*/
    UCHAR  ucGtpuChangeFlag      :1;/* GTP-U地址变化*/
    UCHAR  ucQciArpChangeFlag    :1;
    UCHAR  ucAmbrChangeFlag      :1;
    UCHAR  ucEarpChangeFlag      :1;
    UCHAR  ucPcscfFaultFlag          :1;
    //UCHAR  ucVogProfileChangeFlag      :1;/* 发送到MSU的vog-profile变化*/
    UCHAR  ucCongestionChangeFlag          :1; /* add by g00131462 for 小区拥塞 */

    UCHAR  ucSubNetChangeFlag :1;
    UCHAR  ucbit2SuspendUpd:2;
    UCHAR  ucCLHandoverFlag :1;   /*标识当前是C/L互切的场景*/
    UCHAR  ucC2LSecondMatchFlag:1;  /*add by jiahong 00148456 C切L,给IPN置二次匹配标记DTS2013090206054*/
    UCHAR  uc34HOQosVersionChgFlg :1;  /* 标识3,4G互切QOS版本变化标识 DTS2013081507691 */
    UCHAR  ucRsv :3;
} VOS_PACKED AM_CM_UPDATETYPE_S;

//
//gtp ip define
//
/* 请求消息的IP地址信息 */
typedef struct tagSDB_REQ_MSG_IP_INFO_S
{
    ULONG ulPeerIp;     /* 对端地址 */
    ULONG ulLocalIp;    /* 本端地址 */
    ULONG ulVrfIndex;   /* VPN索引 */
} SDB_REQ_MSG_IP_INFO_S;

typedef struct tagGTP_QOS_SUB_S
{
    UCHAR  ucMaxBitRateUp;
    UCHAR  ucMaxBitRateDown;
    UCHAR  ucMaxBitRateUpExtended;
    UCHAR  ucMaxBitRateDownExtended;
    UCHAR  ucGuarantBitRateUp;
    UCHAR  ucGuarantBitRateDown;
    UCHAR  ucGuarantBitRateUpExtended;
    UCHAR  ucGuarantBitRateDownExtended;
} GTP_QOS_SUB_S;

typedef struct tagGTP_EVOLVED_ARP_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR ucPreemptionVulnerability  : 1;
    UCHAR ucSpare2                   : 1;
    UCHAR ucAllocaRetentPriority     : 4;
    UCHAR ucPreemptionCapability     : 1;
    UCHAR ucSpare1                   : 1;
#else
    UCHAR ucSpare1                   : 1;
    UCHAR ucPreemptionCapability     : 1;
    UCHAR ucAllocaRetentPriority     : 4;
    UCHAR ucSpare2                   : 1;
    UCHAR ucPreemptionVulnerability  : 1;
#endif
} VOS_PACKED GTP_EVOLVED_ARP;

//
//qos common flag define
//

/*
 *Common Flags IE
 */
typedef struct tagGTP_COMMON_FLAGS_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
    UCHAR  ucProhibitPayloadCompression       :1;
    UCHAR  ucMbmsServiceType                         :1;
    UCHAR  ucRanProceduresReady                    :1;
    UCHAR  ucMbmsCountingInformation            :1;
    UCHAR  ucNoQosNegotiation                          :1;
    UCHAR  ucNrsn                          :1;
    UCHAR  ucUpgradeQosSupported   :1 ;
    UCHAR  ucDualAddressBearerFlag      :1;
#else
    UCHAR  ucDualAddressBearerFlag      :1;
    UCHAR  ucUpgradeQosSupported   :1 ;
    UCHAR  ucNrsn                          :1;
    UCHAR  ucNoQosNegotiation                          :1;
    UCHAR  ucMbmsCountingInformation            :1;
    UCHAR  ucRanProceduresReady                    :1;
    UCHAR  ucMbmsServiceType                         :1;
    UCHAR  ucProhibitPayloadCompression       : 1;
#endif
} VOS_PACKED GTP_COMMON_FLAGS_S;

//
//gtp backup define
//

/* C00119457，为了Handover等流程能够回退且在Handover流程结束后PGW/SGW
能够正确删除源侧资源，需要备份一些回退数据，字段定义与SDB_GSPU_CONTEXT_S一致 */
typedef struct tagSDB_WITHDRAW_DATA_S
{
    UCHAR ucUgwRole;        /* 角色信息 */
    UCHAR ucRatType;        /* RAT Type */
    UCHAR ucLeftSigIfType;  /* 左侧控制面接口类型 */
    UCHAR ucRightSigIfType; /* 右侧控制面接口类型 */

    AM_GTPV2_SERVING_NETWORK_S stGTPV2ServingNetwork; /* Serving Network */
    UCHAR ucEPSBearId; /* NSAPI信息(协)，取值范围0～15 */

    GTP_ULI_S stULI;

    UCHAR ucSelectMode;     /* Selection Mode */
    UCHAR ucPdpType;        /* PDN Type */
    UCHAR ucRoleChanged;    /* 角色是否变化过，实际是指是否发生过切换 */
    UCHAR ucMsisdnLen;
    GTP_MSISDN szMsisdn;

    /* 下面的右侧信息并不一定都需要备份，但保险起见，暂时都进行备份 */

    ULONG ulSgwLeftPeerTeidc;     /* 左侧对端信令隧道标识 */
    ULONG ulSgwLeftLocTeidc;      /* 左侧本端信令隧道标识 */
    ULONG ulLeftPeerSigIpInHeader;/* IP头中的左侧对端信令IP */
    ULONG ulSgwLeftPeerSigIP;     /* 信元中解析出的左侧对端IP */
    ULONG ulSgwLeftLocSigIP;      /* 左侧本端信令IP */
    USHORT usSgwLeftPeerSigPort;  /* 左侧对端信令端口 */
    USHORT usSgwLeftLocSigPort;   /* 左侧本端信令端口 */
    ULONG ulSgwLeftLocDataIP;     /* 左侧本端数据IP */
    ULONG ulSgwLeftLocDataIfIndex;  /* 左侧本端数据接口索引 */
    ULONG ulSgwLeftPeerDataIP;    /* 左侧对端数据IP */
    USHORT usLeftSigPathId;       /* 左侧信令路径ID */
    USHORT usLeftDataPathId;      /* 左侧数据路径ID */

    ULONG ulS5_Gn_PeerTeidc;      /* 右侧对端信令隧道标识 */
    ULONG ulS5_Gn_LocTeidc;       /* 右侧本端信令隧道标识 */
    ULONG ulS5_Gn_PeerSigIP;      /* 右侧对端信令IP */
    ULONG ulS5_Gn_LocSigIP;       /* 右侧本端信令IP */
    USHORT usS5_Gn_PeerSigPort;   /* 右侧对端信令端口 */
    USHORT usS5_Gn_LocSigPort;  /* 右侧本端信令端口 */
    ULONG ulS5_Gn_PeerDataIP;   /* 右侧对端数据IP */
    ULONG ulS5_Gn_LocDataIP;    /* 右侧本端数据IP */
    ULONG ulS5_Gn_LocDataIfIndex; /* 右侧本端数据接口索引 */
    USHORT usRightSigPathId;    /* 右侧信令路径ID */
    USHORT usRightDataPathId;   /* 右侧数据路径ID */

    UCHAR ucLeftEncapType;     /* 左侧封装类型*/
    UCHAR ucRightEncapType;    /* 右侧封装类型*/

    /* PDN Address Allocation (PAA)信元相关的信息 */
    UCHAR ucIPv4AllocType;     /* 地址分配方式，静态，本地，RADIUS等 */
    UCHAR ucIPv6AllocType;     /* 地址分配方式，静态，本地，RADIUS等 */
    //S_GTPV2_PAA stGTPV2PAA;
    ULONG ulIPv4Addr;
    in6_addr stIPv6Addr;

    UCHAR ucChargingChar[2];   /* Charging Characteristics */
    UCHAR ucApnRestriction ;   /* Maximum APN Restriction */
    UCHAR ucLeftDataIfType;    /* 左侧数据面接口类型 */
    ULONG ulSgwLeftPeerTeidu;  /* 左侧对端数据隧道标识 */
    ULONG ulSgwLeftLocTeidu;   /* 左侧本端数据隧道标识 */
    ULONG ulS5_Gn_PeerTeidu;   /* 右侧本端数据隧道标识 */
    ULONG ulS5_Gn_LocTeidu;    /* 右侧对端数据隧道标识 */
    ULONG ulChargingId;

    GTP_ADDITIONALTRACEINFO_S stAdditionalTraceInfo;
    GTP_QOS_S stReqQos;        /* 请求的QOS信息 */
    GTP_QOS_S stNegQos;        /* 经过协商的QOS信息 */
    GTP_QOS_NECESSARY_S stOldQos;/*更新使用，保存当前已经在使用的Qos 的必需参数*/

    APN_AMBR_S stApnAmbr;
    UCHAR ucIsSecActivateFlg : 2; /* 该上下文是否是二次激活上下文的标识, normal 表示是一次激活或缺省, second表示二次或专有承载*/
    UCHAR ucGtpVer:2;  /* 协议版本号 */
    UCHAR ucDTI : 1;   /* Direct Tunnel Flag信元的DTI标志位,0表示2Tunnel,1表示1Tunnel */
    UCHAR ucSgwIsTraceFlag : 1;
    UCHAR ucPgwIsTraceFlag : 1;
    UCHAR ucSendTraceInfoToPgw : 1;
    UCHAR ucMachineState;      /* GTPV2 一级状态; GTPV1 状态 */
    UCHAR ucMachineL2State;    /* GTPV2 二级状态*/
    /* Modified start by taojixiu 00132297 at 2011-08-13 PS9.1 for VPLMN性能统计CR收编 */
    UCHAR ucUsrTypeFlg : 2;       /* 保存上下文中的用户属性信息*/
    UCHAR ucIsActByTauOrHo : 1;
    UCHAR ucReserve : 5;          /* 保留，字节对齐，后续使用请优先使用保留字段 */
    /* Modified end by taojixiu 00132297 at 2011-08-13 PS9.1 for VPLMN性能统计CR收编 */
    USHORT usTraceId;
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;

    ULONG ulSgwIfindex;      /* 用于保存组级接口的Sgw 侧的Ifindex */
    ULONG ulPgwIfindex;      /* 用于保存组级接口的Pgw or GGSN 侧的Ifindex */
    /* Added start by taojixiu 00132297 at 2011-08-13 PS9.1 for VPLMN性能统计CR收编 */
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn;
    /* Added end by taojixiu 00132297 at 2011-08-13 PS9.1 for VPLMN性能统计CR收编 */
    AM_CM_UPDATETYPE_S stUpdateType; /*4字节*/            /*更新类型:GTP_CHANGE_SGSN_IP,GTP_CHANGE_QOS,GTP_CHANGE_LOCATION,GTP_CHANGE_RAT */
    USHORT usLeftRecovery;  /*ucLeftRecovery*/
    UCHAR ucBitMsChangeExtendFlag    : 1;
    UCHAR ucVIPUserFlg               : 1;
    UCHAR ucVIPNewByUpdate           : 1;
    UCHAR ucVIPAccessPrioFlg         : 1;
    UCHAR ucRatTypeOccur             : 1;
    UCHAR ucUserLocationInfoOccur    : 1;
    UCHAR ucMSTimeZoneOccur          : 1;
    UCHAR ucAdditionalTraceInfoOccur : 1;
    UCHAR ucRAIUpdateFlag            : 1;
    UCHAR ucDataFlag:2;           /*add: CSFB保存挂起前的转发标记*/
    UCHAR ucbit1SuspendFlag :1;
    UCHAR ucReserve4                : 4;
    SDB_REQ_MSG_IP_INFO_S stReqMsgIpInfo;
    GTP_QOS_SUB_S stSubQos;
    USHORT usMSTimeZone;
    GTP_EVOLVED_ARP stEvolvedARP;
    GTP_COMMON_FLAGS_S stCommonFlags;
    USHORT usPeerDataFlowLbl;
    USHORT usPeerSigFlowLbl;
    UCHAR  ucIdlePagingIndication;      /*add: CSFB保存挂起前的paging标记*/
    UCHAR ucRightDataIfType;        /* 右侧数据面接口类型 */
    UCHAR aucRet[2];
    /* PMIP使用的字段 */
    in6_addr stPmipv6LeftPeerAddr;
    ULONG ulReqMsgVrfIndex;
}VOS_PACKED SDB_WITHDRAW_DATA_S; /* Cyjun: 暂时使用一字节对齐，在数据结构稳定下来后再调整 */

/*
 *Protocol configuration option IE
 */
typedef struct tagGTP_IE_PROTO_CONF_OPT_S
{
    UCHAR     ucType;
    USHORT    usLen;
    UCHAR     szProtoCfgOption[GTP_MAX_PROTO_CFG_OPTION_LEN];
} VOS_PACKED GTP_IE_PROTO_CONF_OPT_S;

#define M_CFG_MAX_APN_USER_LEN 64
#define M_CFG_MAX_APN_PASS_LEN 128
#ifndef MAXUSERNAMELEN
#define MAXUSERNAMELEN M_CFG_MAX_APN_USER_LEN
#endif
#ifndef MAXUSERPWDLEN
#define MAXUSERPWDLEN M_CFG_MAX_APN_PASS_LEN
#endif

#define MAX_IPCP_PARSE 8  /*最多可处理连续的8个IPCP*/
#define GTP_PCO_MAX_IPCP_OPTIONS 20
typedef struct tagGTP_IE_PCO_PARSE_IPCP_S
{
    in6_addr     stIPCPReqIpAddr;
    in6_addr     stIPCPReqDNSAddr0;
    in6_addr     stIPCPReqDNSAddr1;
    ULONG       ulIPCPReqNBNSAddr0;
    ULONG       ulIPCPReqNBNSAddr1;
    ULONG       ulIPCPReqIPCompContent;         /* 存储网络序 */
    ULONG       ulIPCPReqMobileIPV4;
    UCHAR       ucIpcpReqExist;               /* PCO是否有IPCP cfg req，0表示无,1表示有 *//*added by haifeng for BYHD02976; */
    UCHAR       ucIpcpReqConfType;               /* PCO中Ipcp协商类型，0表示无请求 */
    UCHAR       ucIpcpPktID;                     /* PCO中Ipcp协商packet ID */
    UCHAR       ucRsv;
    UCHAR       ucIPCPOptionSequence[GTP_PCO_MAX_IPCP_OPTIONS];    /*store IPCP option types as in Configure Request*/
}GTP_IE_PCO_PARSE_IPCP_S;

/* PCO解析内容结构*/
/*modified for 字节对齐 for v9_b011_t */
typedef struct tagGTP_IE_PCO_PARSE_S
{
    UCHAR       *pucCurPosofIeMem;               /* PCO消息当前指针 */
    UCHAR       *pucEndofIeMem;                  /* PCO消息结尾指针 */
    UCHAR       *pucWriteCurPos;                 /* PCO应答消息写当前指针，使用前应当先为应答消息分配内存 */
    UCHAR       *pucLcpReqOptions;

    in6_addr    stUserIP;                         /* 用户IP */
    int         iSendControlIndex;               /* 发送控制块索引 */

    USHORT      usResponseLen;                   /* 鉴权回应长度*/
    USHORT      usPwdLen;                        /* 密码长度 */

    USHORT      usAuthProto;                     /* 向AAA服务器使用的鉴权协议 PAP or CHAP    */
    UCHAR       ucAuthReqConfType;               /* PCO中使用的鉴权协议     */
    UCHAR       ucPktID;                         /* PCO中鉴权协议 packet ID */

    UCHAR       ucUsrName[MAXUSERNAMELEN + 2];   /* 用户名*/
    UCHAR       ucImsFlag;                       /*用低三位分别标识IMS信令上下文激活请求消息的PCO信源中是否携带相关内容*/
    UCHAR       ucUsrNameLen;                    /* 用户名长度 */

    UCHAR      ucNRSN;                         /*Network Request Support Network (NRSN) */
    UCHAR       ucPwd[MAXUSERPWDLEN+1];           /* 密码 */
    UCHAR       ucCallFromId[20];                /* 主叫号码 */
    UCHAR       ucCallFromIdLen;                 /* 主叫号码长度*/
    UCHAR       ucCallToId[64];                  /* 被叫号码 */
    UCHAR       ucCallToIdLen;                   /* 被叫号码长度 */
    UCHAR       ucResponse[256];                 /* 鉴权回应 */

    UCHAR      ucAddrDhcpsFlag;
    UCHAR      ucAddrNasFlag;
    UCHAR       ucIPv6DnsCount;
    UCHAR       ucIPv4DnsCount;

    UCHAR       ucMSISDN;
    UCHAR       ucLcpReqConfType;               /* PCO中Lcp协商类型，0表示无请求,1表示有 */
    UCHAR       ucLcpPktID;                     /* PCO中lcp协商packet ID */
    UCHAR       ucLcpReqLen;

    ULONG       ulPCSCFIPV4IP;
    in6_addr    stPcscfIPV6IP;
    GTP_IE_PCO_PARSE_IPCP_S stIpcp[MAX_IPCP_PARSE];
} GTP_IE_PCO_PARSE_S;

#if 0
//
//imsi stuct define
//
typedef struct tagGTP_IMSI_S
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN
     UCHAR MCC1  : 4;
     UCHAR MCC2  : 4;
     UCHAR MCC3  : 4;
     UCHAR MNC1  : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN8 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN10: 4;
     UCHAR SPARE : 4;        /* 用1填充 */
#else
     UCHAR MCC2  : 4;
     UCHAR MCC1  : 4;
     UCHAR MNC1  : 4;
     UCHAR MCC3  : 4;
     UCHAR MSIN1 : 4;
     UCHAR MNC2  : 4;
     UCHAR MSIN3 : 4;
     UCHAR MSIN2 : 4;
     UCHAR MSIN5 : 4;
     UCHAR MSIN4 : 4;
     UCHAR MSIN7 : 4;
     UCHAR MSIN6 : 4;
     UCHAR MSIN9 : 4;
     UCHAR MSIN8 : 4;
     UCHAR SPARE : 4;        /* 用1填充 */
     UCHAR MSIN10: 4;
#endif
} GTP_IMSI_S;
#endif

//
//gtp trce define
//
typedef struct tagAM_GTPV2_TRACE_INFO_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC2:4;
    VOS_UINT8 btMNC1:4;
#else
    VOS_UINT8 btMCC1:4;
    VOS_UINT8 btMCC2:4;
    VOS_UINT8 btMCC3:4;
    VOS_UINT8 btMNC3:4;
    VOS_UINT8 btMNC1:4;
    VOS_UINT8 btMNC2:4;
#endif
    VOS_UINT8 aucTraceId[3];
    VOS_UINT8 aucTriggerEvents[9];
    VOS_UINT16 usListOfNeTypes;
    VOS_UINT8 ucSessionTraceDepth;
    VOS_UINT8 aucListOfInterfaces[12];
    VOS_UINT32 ulIpOfTreceCollEntity;
} VOS_PACKED AM_GTPV2_TRACE_INFO_S;


//
//gtpv2 define
//
//typedef S_DUAL_IP S_GTPV2_PAA;
typedef struct
{
    /* IPv4 ~ 1; IPv6 ~ 2; IPv4/IPv6 ~ 3 */
    VOS_UINT8 ucPdnType;

    /* IPV6或者IPV4/IPV6有效时，指IPV6地址的前缀长度 */
    /* In GTP 29.274 Rel 8, Prefix length has a fixed value of /64 */
    VOS_UINT8 ucIPV6PrefixLen;

    VOS_UINT8 aucReserved[2];

    DHCPC_IPV4 aucIPV4;
    DHCPC_IPV6 aucIPV6;
}VOS_PACKED S_GTPV2_PAA;

#define AAA_MAX_SERVICE_LIST_NUM     10
#define M_CFG_MAX_MULTI_APN_PASS_LEN 63

//
//aaa struct define
//
typedef struct  tagAAA_Service_Node
{
    ULONG      ulServiceChargingType;
    UCHAR      ucServiceUsername[MAXUSERNAMELEN];
    UCHAR      ucPassword[M_CFG_MAX_MULTI_APN_PASS_LEN + 1];
    USHORT     usServiceIndex;
    UCHAR      ucTag;
    UCHAR      ucReserved;
}AAA_Service_Node;

typedef struct  tagAAA_Service_List
{
    UCHAR                 ucServiceListNum;              /*service的个数*/
    UCHAR                 ucPrimaryIndicator;          /*标志哪个是主service*/
    UCHAR                 ucReserved[2];
    AAA_Service_Node      astServicelist[AAA_MAX_SERVICE_LIST_NUM];
}AAA_Service_List;

typedef struct tagUGW_QOS_UPDATE_BAKUP_S
{
    UCHAR   ucQosType;
    UCHAR   ucOldRealQCI;          /* PCRFC_PDP_BEARER_RLN_S中的相应字段 */
    UCHAR   ucOldQCI;          /* PCRFC_PDP_BEARER_RLN_S中的相应字段 */
    UCHAR   ucOldArp : 4;          /* PCRFC_PDP_BEARER_RLN_S中的相应字段 */
    UCHAR   ucBit1PEC :1; //Pre-emption-Capability
    UCHAR   ucBit1PEV :1; //Pre-emption-Vulnerability
    UCHAR   ucBit2Rev :2;
    ULONG   ulApnAmbrUL;
    ULONG   ulApnAmbrDL;
    ULONG   ulGbrUpLink;
    ULONG   ulGbrDwLink;
    ULONG   ulMbrUpLink;
    ULONG   ulMbrDwLink;
} UGW_TFT_QOS_UPDATE_BAKUP_S;

//
//mcc-mnc define
//
typedef struct tag3GPP_IMSI_MCC_MNC_S       /*  IMSI_MCC_MNC结构  */
{
#if UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN   /*  小端字序  */
    UCHAR MCC1  : 4;
    UCHAR MCC2  : 4;
    UCHAR MCC3  : 4;
    UCHAR MNC1  : 4;
    UCHAR MNC2  : 4;
    /*UCHAR SPARE : 4;*/                        /*  不用添1  */
    /* BEGIN: Added by 袁昊, 2003/7/29 */
    UCHAR MNC3  : 4;
    /* END:   Added by 袁昊, 2003/7/29 */
#else

    UCHAR MCC2  : 4;
    UCHAR MCC1  : 4;
    UCHAR MNC1  : 4;
    UCHAR MCC3  : 4;
    /*UCHAR SPARE : 4;*/                        /*  不用添1  */
    /* BEGIN: Added by 袁昊, 2003/7/29 */
    UCHAR MNC3  : 4;
    /* END:   Added by 袁昊, 2003/7/29 */
    UCHAR MNC2  : 4;
#endif
} VOS_PACKED T3GPP_IMSI_MCC_MNC_S;

typedef T3GPP_IMSI_MCC_MNC_S T3GPP_GGSN_MCC_MNC_S; /*  GGSN_MCC_MNC结构  */

//
//trig define
//
/* sdb中stTriggerType的类型 */
typedef struct tagAM_AUTH_TMO_TRIGGER_TYPE
{
    UCHAR ucChangeInSgsnIp:1;
    UCHAR ucChangeInQos:1;
    UCHAR ucChangeInLocation:1;
    UCHAR ucChangeInRat:1;
    UCHAR ucChangeInQosTrafficClass:1;
    UCHAR ucChangeInQosReliabilityClass:1;
    UCHAR ucChangeInQosDelayClass:1;
    UCHAR ucChangeInQosPeakThroughput:1;
    UCHAR ucChangeInQosPrecedenceClass:1;
    UCHAR ucChangeInQosMeanThrroughput:1;
    UCHAR ucChangeInQosMBRup:1;
    UCHAR ucChangeInQosMBRdn:1;
    UCHAR ucChangeInQosResidualBer:1;
    UCHAR ucChangeInQosSDUErrorRatio:1;
    UCHAR ucChangeInQosTransferDelay:1;
    UCHAR ucChangeInQosTrafficHandPri:1;

    UCHAR ucChangeInQosGBRup:1;
    UCHAR ucChangeInQosGBRdn:1;
    UCHAR ucChangeInLocationMCC:1;
    UCHAR ucChangeInLocationMNC:1;
    UCHAR ucChangeInLocationRAC:1;
    UCHAR ucChangeInLocationLAC:1;
    UCHAR ucChangeInLocationCellID:1;
    UCHAR ucTmoAcctInterimInterval:1;
    UCHAR ucTmoAcctInterimVolume:1;
    UCHAR ucChangeInCellCongestion:1;
    UCHAR ucChangeInEcgi:1;
    UCHAR ucChangeInTai:1;
    UCHAR ucChangeInRai:1;
    UCHAR ucChangeInUli:1;
    UCHAR ucValidFlg:1;     /* 是否有效 */
    UCHAR ucRemoveFlag:1;

} VOS_PACKED AM_AUTH_TMO_TRIGGER_TYPE_S;

typedef struct tagBRAS_PDP_Str
{
    ULONG ulAcctSessionLen;
    UCHAR ulAcctSessionId[MAX_BRAS_SESSION_LEN];   /* acct session id */
    struct tagBRAS_PDP_Str*  pNext;
} BRAS_PDP_Str;

typedef struct tagBRAS_Session_Info
{
    UCHAR aucMacAddress[MAX_MACADDRESS_LEN];/* 保存MAC地址 */
    ULONG ulUplinkCommittedRate;
    ULONG ulDownlinkCommittedRate;
    ULONG ulUplinkPeakRate;
    ULONG ulDownlinkPeakRate;
    BRAS_PDP_Str* pstPdpinfo;    /* 专有承载的信息*/
} BRAS_Session_Info;

typedef union tagunSession_Info
{
    BRAS_Session_Info  stBRASSession;
}unSession_Info;

#define MAX_CFPROFILES_FROM_ONE_GX_MESSAGE        5
#define MAX_CFPROFILE_IN_PDC                      10

typedef struct tagSCCG_LICENSETYPE_S
{
    UCHAR  ucBrasFlag:1;  /*是否为固网接入的用户*/
    UCHAR  ucHotBilling:1;  /*是否为hot billing */
    UCHAR  ucPccLicenseFlag:1;    /*是否为PCC用户激活*/
    UCHAR  ucSCCGFlag:1;/*是否为radius功能用户*/
    UCHAR  ucOnlineChargeFlag:1;/*是否为在线计费用户*/
    UCHAR  ucGulFlag:1;/*是否为GGSN&PGW接入的用户 */
    UCHAR  ucContentChargingFlag:1;  /*是否为内容计费(FBC)用户*/
    UCHAR  ucIpv6SessionFlag:1;               /*是否为ipv6接入用户*/
    UCHAR  ucIpv6OnlineChargingSessFlag:1;    /*是否为ipv6计费用户*/
    UCHAR  ucIpv4v6SessionFlag:1;             /*是否为ipv4v6接入用户*/
    UCHAR  ucReserved:6;
    UCHAR  ucReserved1[2];
}SCCG_LICENSETYPE_S;

#define RELTMR_T VOS_UINT32
#if 0
/* 重要:修改如下结构体成员需要同步修改g_SdbSccgPdpcontextFieldDesc中成员属性*/
/* SDB数据结构定义 */
typedef struct  tagSDB_SCCG_CONTEXT_S
{

   /*8**/
    ULONG  ucSeqLinkNo:3;
    ULONG  ucSendToPfFlag:1;
    ULONG  ucDataFlag        : 2;      /* 数据转发标志 */
    ULONG  ucDataTrcFlg      : 2;
    ULONG ulBackupNext : 24; /*备份相关*/
    ULONG ucBackupFlag:1;
    ULONG ucBatchNotActive:1;
    ULONG bit1MSUFlagc:1;
    ULONG  ucVIPUserFlg:1;
    ULONG ucQchatFlag:1;           /* 是否为Qchat用户标志 */
    ULONG ucSupprotFPIFlag:1;/*FPI属性标志*/
    ULONG ucSupAreaCongestionRpt:1; /*小区拥塞上报*/
    ULONG ucBitAreaCongTriggerFlag:1;
    ULONG ulBackupPre : 24; /*备份相关*/

    ULONG      ulGspuBdIndex;
    ULONG      ulTeidc;         /* PDN用户上下文的TEIDC */
    ULONG      ulTeidu;       /* PDN用户上下文的TEIDU */
    ULONG      ulIPv4Addr;
    in6_addr    stIPv6Addr;
    GTP_IMSI_S   stImsi;      /* 用户IMSI信息8字节*/
    GTP_MSISDN szMsisdn;  /* 用户MSISDN信息8字节 */
    GTP_IMEI_S stIMEI;                      /*8字节*/

    UCHAR* pucAAANegoRspMsg; /* AAA鉴权响应消息指针Session和idle时长都在这里面*/
    SDB_TFT_S* pstTft;
    GTP_PDP_Str* pstPdpinfo;  /* 专有承载的信息*/
    AM_IPN_MSE_PROFILE_INFO_S *pstMseProfileInfo;  //10.1MSE Profile功能增强
    /* ckp添加 */
    VOID *pstSGWFqCsidNext;
    VOID *pstPGWFqCsidNext;
    GTP_QOS_S *pstOriginalNegoQos; /* To remove */
    MEDIA_DETECT_S * pstMediaDetectElement;
    GTP_SAE_QOS_S *pstOriginalUEReqQos; /*用于记录UE请求过的qos信息，多次累加的结果*/
    SDB_L2TP_INFO_S * pstL2TPInfo;
    SDB_WITHDRAW_DATA_S *pstWithdrawData;
    GTP_IE_PROTO_CONF_OPT_S * pstPCO;           /* Protocol Configuration Option(协) */
    GTP_IE_PCO_PARSE_S * pstPCOParse;       /* PCO解析后的内容*/
    AM_GTPV2_TRACE_INFO_S *pstTraceInfo;/*UGW 1.1:Trace info暂存指针，发送消息后指针释放*/
    S_GTPV2_PAA *pstGTPV2PAA;
    AAA_Service_List *pstServiceList; /* Servic-List指针 */
    UCHAR *pstPrcfUpdateMsg;       /* 保存PCRFC RAR更新消息 */
    /* add start by wangboyu at 2011-09-30 for PCC增强 */
    UGW_TFT_QOS_UPDATE_BAKUP_S *pstQosRollBack;     /*  用户缺省承载的QOS回退 */
    UCHAR* pucLapRspMsg; /*包含DHCPV6信息的Lap响应消息存在此处*/

    /* ckp添加 */
    UCHAR       ucAcctMultiSessionId[MAX_MULTI_SESSION_LEN];
    UCHAR       ucMultiSessionidLen;
    UCHAR       ucTimeStampFlag: 1;
    UCHAR       ucBWMUsrFlg: 1;
    UCHAR       ucNotDelGiFlg: 1;
    UCHAR       ucRever: 5;
    UCHAR    ucSessionStopInd;
    UCHAR     ucCbnCpyAckType:1;
    UCHAR      ucCongestionLevel:6;
    UCHAR      ucCongestionFlag:1;


    in6_addr     stNasIP;      /* NAS_IP_Address */
    UCHAR       ucNasIdentify[MAX_IDENTIFY_LEN]; /* NAS的设备名 */

    UCHAR       ucFrameProtocol;  /**/
    UCHAR       ucAccessType: 3;  /* 接入类型 ACCESS_3GPP,ACCESS_3GPP2,ACCESS_BRAS */
    UCHAR       ucAcctAuthentic: 2; /*健全方式*/
    UCHAR       ucIsSecActivateFlg:2;          /* 该上下文是否是二次激活上下文的标识 ,normal 表示是一次激活或缺省，second表示二次或专有承载*/
    UCHAR       ucPreCMFail      : 1;                  /* 是否CM在激活请求时失败  不可维护，最好不用 激活时，计费返回成功，后续流程失败删除时通知计费不产生话单 */
    UCHAR      ucPdpType;  /* PDP类型,取值参见gtp.h ,注意GGSN和USM间的转换*/
    UCHAR      ucRatType;             /* 接入类型*/

    UCHAR      ucUgwRole;/*网元角色*/
    UCHAR      ucEPSBearId;         /* EPS Bear ID, GGSN使用这个变量当作NSAPI，此处只保持一次上下文的值*/
    USHORT usMSTimeZone;
    ULONG      ulFilterTableIndex;             /*数据面过滤条件链表的索引n*/
    ULONG      ulGtpuIndex;             /*下发给转发面的gtpuindex*/
    RELTMR_T ulTimerId;              /* 定时器事件ID */
    RELTMR_T ulT3N3TimerId;              /* 定时器事件ID */
    UCHAR  ucCurrentBearerNum;         /* 当前承载的个数*/
    T3GPP_GGSN_MCC_MNC_S stMccMnc; /* 是GGSN,PGW,P+S HPLMN,按照stImsi从HPLMN匹配到的HPLMN，如果在SGW上，该字段表示PGW的PLMN */
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn; /* 如果是SGW，该字段表示PGW的PLMN，如果是GGSN,PGW,PS，该字段表示对端SGW,SGSN的PLMN */
    GTP_QOS_S stNegQos;      /* 经过协商的QOS信息(协) ,24字节*/
    ULONG ulSgsnAsn;         /* ASN漫游计费,AM写CM用*/
    UCHAR   ucUserLocationInfo[8];

    ULONG  stSGSNIP;        /* 用户IP */
    ULONG  stGGSNIP;       /* 用户IP */
    ULONG  ulActiveTimeStamp; /*激活时间戳*/
    UCHAR  ucDpeId;                 /* DPE 逻辑ID  */
    UCHAR  ucPccMode;
    UCHAR  ucRandomNo:3;           /* 随机跟踪*/
    UCHAR  ucTriggerChangeFlag:1;
    UCHAR  ucReserved1:3;
    UCHAR  ucReserved2:1;

    UCHAR   ucSduVcpuId;   /* SDU 表项所在的VCPU */

    ULONG   ulSlaveTimeStamp;
    ULONG  ulIdleTime;              /* 最终确认的空闲上下文时长 */

    UCHAR  ucUsername[MAXUSERNAMELEN];/*CM SM计费使用*/
    AM_CM_UPDATETYPE_S stUpdateType;   /* 更新类型*/
    UCHAR  ucChargingChar[2];    /* 计费特征(协) */
    USHORT usTokenId;     /* 上下文的TOKEN ID */

    ULONG ulCgAddr;               /* CG地址 */

    /*========G消息中携带的信元标示=======*/
    UCHAR ucIMEISVOccur:1;
    UCHAR ucRatTypeOccur:1;
    UCHAR ucUserLocationInfoOccur:1;
    UCHAR ucMSTimeZoneOccur:1;
    UCHAR ucChargingCharOccur:1;
     /*========消息中携带的信元标示=======*/
    UCHAR ucSelectMode  : 3;
    UCHAR  ucRecordType:2;  /* 流量采集类型， 0: 统计3、4层流量 ,1:统计7层流量*/
    UCHAR  ucChargeMode:2; /* 计费属性，0:离线计费 , 1:离线计费*/
    UCHAR  ucChargePropertyFlag:2;  /*标识该用户是否内容计费用户，0:普通,1:内容计费(FBC CBB),2:PDP CBB.（0：没有userprofile，1和2都绑定了userprofile）*/
    UCHAR  ucAliasMarking:1;   /* Alias Marking使能标识,0:未使能,1:使能 */
    UCHAR  ucDDosFlag:1;        /* 防DDOS攻击使能,0:未使能,1:使能 */
    USHORT usUserProfileID;   /* 该用户匹配的User Profile ID*/


    UCHAR   ucAAAUserProfileFlag:1; /*0表示userprofile是本地分配；1表示AAA指定*/
    UCHAR   ucPerfForCmcc:1;           /*标识用户是否进行cmcc性能统计，该标记有ipn处理，am需要透传给pf*/
    UCHAR   ucPccL7ProcessFlag:2;
    UCHAR   ucPppFailReason:4;             /* 保留字段 */
    UCHAR  ucBwmSubscriberEnable:2;  /* 用户级BWM带宽使能标志*/
    UCHAR  ucBwmGroupEnable:2;         /* 用户组级BWM带宽使能标志 */
    UCHAR  ucBwmGlobalEnable:2;        /* 全局级BWM带宽使能标志 */
    UCHAR  ucEMSstartmesgFlag:1;        /*EMS  激活消息判断标志位*/
    UCHAR  ucGxRelType:1;

    USHORT usUserProfileGroupID;        /* 该用户匹配的User Profile Group ID*/

    /* Cm 使用的字段 */
    ULONG ulCdrfChargingId;           /* CDRF计费ID(协) */
    ULONG ulRadiusIndex;               /* AAA计费的索引*/
    //UCHAR ucGxRelType:1;
    UCHAR ucDelCause;                 /* 去活原因值*/
    UCHAR ucULIValid:1;                  /* 标示上下文中的ULI信息合法CM组使用*/
    UCHAR ucTimeZoneValid:1;        /* 标示上下文中的Timezone信息合法CM组使用*/
    UCHAR ucIsTftExist:1;     /* 该上下文是否包含TFT的标识 */
    UCHAR ucImsFlag:2;       /* 上下文类型标志*/
    UCHAR ucSrvLevel:3;      /* 业务级别*/
    UCHAR usAcctStopCause:4;     /* 计费结束原因值 */
    UCHAR bit1OnlChrgEnabled:1;  /*1: online charging enabled; 0: online charging disabled*/
    UCHAR bit1OflChrgEnabled:1;   /*1: offline charging enabled; 0: offline charging disabled*/
    UCHAR ucOfflineBillAttrFlg:1;    /* TMO-Offline-Billing-Attr是否有效值，0表示无效，1表示有效 */
    UCHAR ucVogProfileChangeFlag      :1;/* 发送到MSU的vog-profile变化*/
    //UCHAR ucCMWaitAAAStatus     : 1;    //xuyaoqiang 2013513 for all in one
    UCHAR  ucAmRsv;   /*用来保存session中激活的上下文的个数*/
    ULONG  ulpdpActForCmStampLow;/*上下文激活时间戳--低位*/
    ULONG  ulpdpActForCmStampHig;/*上下文激活时间戳--高位*/
    ULONG  ulpdpDelForCmStampLow;  /*上下文去活时间戳--低位*/
    ULONG  ulpdpDelForCmStampHig;  /*上下文去活时间戳--高位*/


    ULONG ulSessionIndex;   /* index of session cb*/
    ULONG ulBearerIndex;    /* index of bearer cb*/
    UCHAR ucPriOfcsIndex;   /* 主offline function(CG)的索引*/
    UCHAR ucSecOfcsIndex; /* 备offline function(CG)的索引*/
    USHORT usPcrfGrpIndex;


    UCHAR ucCcSelectMode;
    UCHAR ucApnLockDelUserFlag;   /* 表示是否lock enable deactive enable去活的用户*/
    GTP_COMMON_FLAGS_S stCommonFlags;
    UCHAR ucRsv_1;    /* 定位用，用来标记该用户是否收到了去活消息。 */
    USHORT     usApnIndex; /* 该上下文对应的APN索引号 */
    UCHAR       ucMachineState;      /* 一级状态 */
    UCHAR       ucMachineL2State;  /* 二级状态 */
    ULONG  ulDefaultGspuIndex;
    ULONG ulSgwLeftLocTeidc; /*暂时保留*/
    ULONG ulS5_Gn_LocTeidc;
    ULONG ulSgwLeftPeerTeidu;
    ULONG ulS5_Gn_PeerTeidu;
    ULONG ulS5_Gn_PeerTeidc;
    UCHAR ucIPv4AllocType;      /* 地址分配方式，静态，本地，RADIUS等 */
    UCHAR ucIPv6AllocType;      /* 地址分配方式，静态，本地，RADIUS等 */
    UCHAR ucDtMode;
    UCHAR ucGtpVer;

    USHORT usTraceId;
    USHORT usAliaCdbIndex;           /* APN别名在CDB中的index(0-999)*/
    GTP_QOS_S stReqQos;              /* 请求的QOS信息 ,24字节*/
    USHORT usVirtualapnIndex;       /* 虚拟APN或者single APN*/
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;
    UCHAR ucSgwIsTraceFlag:1;
    UCHAR ucPgwIsTraceFlag:1;
    UCHAR ucVirtualapnFlag :1;        /* 是否虚拟APN映射到真实APN*/
    UCHAR ucMainContextFlag : 1;   /* 该字段仅在平滑时使用,用于标识当前用户情况*/
    UCHAR ucRadiusDisablePcc :1;  /* 标识RADIUS是否下发禁用PCC标志*/
    UCHAR ucUsrTypeFlg :2;            /* 用户归属类型，后面干掉，注意替换代码*/
    UCHAR ucAAARspCCFlag:1;       /* 已使用for Celcom Single APN，AAA返回的CC值是否合法，1为合法 */
    UCHAR ucTimeQuotaType;      /* TMO-Offline-Billing-Attr属性中Time-Quota-Type的值*/
    UCHAR ucChargingType;   /* AAA服务器下发的Billing-Type : 0=prepaid，1=post-paid，2=post-paid with credit control,
                                               3=prepaid with credit control，4=HLR, 5=wallet specific,
                                                6=wallet specific without credit control, 7=hot billing*/
    UCHAR ucHomeZoneId;           /* Home Zone模块返回的Home Zone服务器状态 */
    ULONG ulBaseTimeInterval;    /* TMO-Offline-Billing-Attr属性中Base-Time-Interval的值*/
    USHORT usPriFuncNameIdx;   /* TMO-Primary-Event-Charging-Function-Name属性对应的index，全f表示无效 */
    USHORT usSecFuncNameIdx;  /* TMO-Secondary-Event-Charging-Function-Name属性对应的index，全f表示无效 */
    ULONG ulVirtualGiId;            /* 用于存储AAA所下发的GiId*/

    AM_AUTH_TMO_TRIGGER_TYPE_S stTriggerType;  /* 对应AM_AUTH_TMO_TRIGGER_TYPE_S */
    UCHAR aucTransparentData[32]; /* TMO-Transparent-Data属性，最大长为8 */

    ULONG ulSgwLeftPeerSigIP;     /* 信元中解析出的左侧对端IP */
    ULONG ulSgwLeftLocSigIP;       /* 左侧本端信令IP */
    ULONG ulSgwLeftPeerDataIP;  /* 左侧对端数据IP */
    ULONG ulSgwLeftLocDataIP;    /* 左侧本端数据IP */
    ULONG ulSgwLeftLocTeidu;      /* 左侧本端数据隧道标识 */
    ULONG ulS5_Gn_PeerSigIP;    /* 右侧对端信令IP */
    ULONG ulS5_Gn_LocSigIP;      /* 右侧本端信令IP */
    ULONG ulS5_Gn_PeerDataIP; /* 右侧对端数据IP */
    ULONG ulS5_Gn_LocDataIP;   /* 右侧本端数据IP */
    ULONG ulS5_Gn_LocTeidu;      /* 右侧对端数据隧道标识 */

    GTP_ULI_S stULI;/* 20 */
    USHORT usExternalEvent; /* 原始激励 */
    UCHAR  bit1SgwOflChrgEnabled:1;
    UCHAR  ucHZUserFlag:1;   /* 标识该用户是否为Home Zone用户。0:非Home Zone用户；1：Home Zone用户*/
    UCHAR  ucHZApnFlag:1;    /* 标识该用户是否以Home Zone APN激活。0:非Home Zone APN；1：Home Zone APN*/
    UCHAR ucbit1TightInterwork:1; /* 0:松耦合  1:紧耦合 */
    UCHAR ucVirtualGiIdFlag:1;  /* 用于标记AAA是否下了GiId*/
    UCHAR ucMultiServiceFlg:1;     /* 记录是否是Multi-Service用户 */
    UCHAR ucMultiContextFlg:1;    /* 记录是否是Multi-Service上下文 */
    UCHAR ucRadiusServerFlag:1; /* 标识用户是否使用radius功能*/
    UCHAR ucLeftSigIfType;           /* 左侧控制面接口类型 */


    APN_AMBR_S stApnAmbr;      /* Aggregate Maximum Bit Rate AMBR */
    APN_AMBR_S stOldApnAmbr;      /* Aggregate Maximum Bit Rate AMBR */
    UCHAR  ucIpv6PrefixLength; /* radius 返回的 IPV6 前缀长度*/
    UCHAR ucChargingCharInMsg[2];   /* 用于存储SGSN携带的CC信元的值*/
    UCHAR ucPcrfLocalIndex;
    ULONG ulPdnConnectionId;            /* 用于记录缺省承载的ulCdrfChargingId */


    USHORT usNoConfigApnIndex;      /* SGW未配置APN的Index(1-3000)*/
    USHORT usServiceIndex;         /* 对于service PDP,保存当前激活的service-index; 对于default PDP,保存multiple-apn的index */
    ULONG ulDefaultPDPIndex;     /* 记录Default PDP上下文索引，该记录只对Multi-Service用户有效 */

    /* 带宽控制*/

    /* SM需要的字段*/
    ULONG  ulUsageRptCBIndex; /* Added by hourufeng for SM R8 同步*/
    UCHAR  ucRightEncapType;    /* 右侧封装类型*/
    UCHAR  ucActionSupport:1;
    UCHAR  ucBit1OnlineCharGranFlag:1;
    UCHAR  ucHZErrorFlag:1;  /* 标识该用户连接到的HomeZone Server当前是否正常运作。0:正常；1：HomeZone Server无响应*/
    UCHAR  ucHZRspFlag:1;    /* 是否收到HomeZone Server响应消息标志：初始化为0 0：没有收到 1：收到*/
    UCHAR  ucCoaNotifyUserProfileUpdated:1;  /* COA更新UserProfile标志，1,表示COA更新过,不允许SGSN的更新; 0,COA未更新,允许SGSN更新 */
    UCHAR  ucCoaQosChangedFlag:1;                /* 1,发生改变 0,未发生改变 */
    UCHAR  ucCoaUserProfileChangedFlag:1;    /* 1,发生改变 0,未发生改变 */
    UCHAR  ucPccRollBackFlag:1; /* PCRFC通知AM PCC回滚时，AM置该位为1，IPN通过此标志在备板做回滚操作，该字段在PCRFC给AM回更新响应和revoke消息时置位*/
    UCHAR  ucBitCfFlag:1;            /* 1表示CF用户，0表示不是CF用户*/
    UCHAR  ucPccIndicate:4;       /* Pcc Indicate Num, IPN写，AM负责下发该字段给PF  by penghui for 9.0 2011-2-6 */
    UCHAR  ucIsRTUser:1;          /* 报表实时用户标记*/
    UCHAR  ucRuleChangeFlag         :1;
    UCHAR  ucSAEmsFlag:1;       /*Gn免维护SA标记*/
    UCHAR  ucUserLevelServiceType;

    UCHAR ucMsisdnLen;                /* 保存msisdn长度 */
    UCHAR  ucGroupLevelServiceType;  /* 记录用户组级的业务类型， tos /non-tos*/
    USHORT usCFTemplateID;
    USHORT usUserGroupID;      /* 用户组ID，同时也是用户组级BWM_CB数组的索引号*/
    USHORT usPolicyId;              /* SM使用的Policy Id*/



    unSession_Info  unSessionInfo;

    /*chenjinbo添加*/
    ULONG       ulOutVPNIndex;      /* 用户对应的出接口*/
    ULONG       ulTimeStamp;          /* 消息自带的事件戳*/
    ULONG       ulLastTimestamp;    /* 处理上一条信息的事件戳*/
    ULONG       ulCurTimeStamp;
    UCHAR       ucL2Info[SCCG_MAX_L2_LEN];
    UCHAR       ucNsapi;        /* 该字段暂时不使用 */
    UCHAR       ucACCIdentifier;
//  AM_SCCG_PF_CTRL_Info stPfCtrlInfo;
    /*chenjinbo添加 end*/

    UCHAR      ucDTI : 1;
    UCHAR      ucIsActByTauOrHo : 1;    /* 该上下文被激活是由于TAU或HANDOVER标志,与附着区分  */
    UCHAR      ucAdcFlag           :1;/*ADC用户属性*/
    UCHAR      ucAdcRuleFlag       :1;/*是否有ADC规则*/
    UCHAR      ucAdcChangeFlag       :1;/*ADC是否更新*/
    UCHAR      ucBrasUserType:3;
    UCHAR      uceQci; /*用于保存PCRFC下发的扩展Qci,填充话单使用*/


    USHORT usFramedRouteCount;
    USHORT usMMECsId;
    ULONG  ulSGWNodeId;
    ULONG  ulSGWFqCsidIndex;
    ULONG  ulPGWNodeId;
    ULONG  ulPGWFqCsidIndex;
    ULONG  pstMMEFqCsidNext;
    ULONG  ulMMEFqCsidIndex;
    ULONG  ulMMENodeId;
    USHORT usSGWCsId;
    USHORT usPGWCsId;
    UCHAR  ucL2TPFlag;
    UCHAR ucUpAmbrCarFlag  : 2;            /* 用于标识缺省承载是否使能了上行AMBR CAR功能,以便专有承载据此判断是否需要CAR功能 */
    UCHAR ucDownAmbrCarFlag  : 2;          /* 用于标识缺省承载是否使能了下行AMBR CAR功能,以便专有承载据此判断是否需要CAR功能 */
    UCHAR  ucProcFail     : 1;                      /* 流程处理失败标记。用于集中发消息 */
    UCHAR  ucBitPcrfCarryCfFlag : 1;
    UCHAR  ucBitPcrfCfFlag : 1;
    UCHAR  ucSdbReserved : 1;
    UCHAR  ucDhcpIPV6Flg;
    UCHAR  ucLeftEncapType;


    USHORT usFirstFramedRouteIndex;
    USHORT usRightSigPathId;
    UCHAR  ucBackupType:8;
    UCHAR ucOldUpBandFlag   : 4;
    UCHAR ucOldDownBandFlag : 4;
    UCHAR ucMultiAddressInherit:1;
    UCHAR ucSlavePdpFlag:1;
    UCHAR ucNotifyPcrfcFlag:2;
    UCHAR ucActDedBearerNum:4;
    UCHAR ucUserPerfFlag  :2;    /*用户数是否计数的标记,0,未计数;1,已计数;2,不用计数*/
    UCHAR  ucPdnConnectPerfFlag:2;
    UCHAR ucDropEmsFlag:1; /*丢包免维护是否开始的标记*/
    UCHAR ucImsiInvalidFlag : 1;       /*标识当前用户是否存在可用的IMSI;0:当前用户IMSI可用;1:当前用户IMSI不可用*/
    UCHAR ucBearerPerfFlag  :1;    /*context 是否计数的标记,0,未计数;1,已计数;*/
    UCHAR  ucSlaveSessionTimeOutFlg:1;  /* 备板如果SESSION TIMEOUT超时后记录标志，平滑时删除，避免主板丢失备份导致用户残留 */
    //14
    UCHAR  ucAddrAllocDhcpsFlag:1;
    UCHAR ucLiFlag          : 1;
    UCHAR ucOcscForceDropFlag  : 1; /*tianshuang for CR20120301017*/
    UCHAR ucMSRarUpdBakFlag:1;
    UCHAR bit1MsuFlag:1;
    UCHAR ucSmoothFailFlag:3;
    UCHAR ucTempTftOperCode:3 ;
    UCHAR ucBufferOperCode:2;
    UCHAR ucNotifyDelGi: 1;
    UCHAR  ucPmipLifeTimeOP:2;
    UCHAR ucRspHZSameMsgNum;            /* 表示收到HZ模块相同的状态通知消息次数 */
    UCHAR ucPcrfcDelCause;
    USHORT usPmipLifetime;
    USHORT usTempFilterOperIndic;
    ULONG  ulIndirectForwardLocTeidu;
    ULONG  ulResource;
    ULONG  ulSessionTimeout;
    USHORT usIPv4VpnId;
    USHORT usIPv6VpnId;
    USHORT usLeftDataPathId;
    USHORT usLeftSigPathId;
    USHORT usRightDataPathId;
    USHORT usLeftRecovery;
    USHORT usS5_Gn_PeerSigPort;
    USHORT usS5_Gn_LocSigPort;
    USHORT usSgwLeftPeerSigPort;
    USHORT usSgwLeftLocSigPort;
    ULONG ulIndirectForwardPeerULTeidu;                /* 上行间接转发对端上行数据隧道标识 */
    ULONG ulSgwLeftPeerTeidc;          /* 左侧对端信令隧道标识 */

    USHORT ulControlBlockIndex;
    UCHAR ucLeftDataIfType;         /* 左侧数据面接口类型 */
    UCHAR ucRightDataIfType;        /* 右侧数据面接口类型 */
    UCHAR ucIndirectForwardInputInterfaceType;      /* 间接转发入接口类型 */
    UCHAR ucIndirectForwardOutputInterfaceType;     /* 间接转发出接口类型 */
    UCHAR ucIndirectForwardInputEncapType;          /* 间接转发入封装类型 */
    UCHAR ucIndirectForwardOutputEncapType;         /* 间接转发出封装类型 */

    ULONG ulUpInterfaceIndex;      /* 上行接口Subindex*/
    ULONG ulDnInterfaceIndex;      /* 下行接口Subindex*/
    ULONG ulIndirectFwdIndex;      /* 转发模式的接口Subindex*/
    ULONG ulIndirectForwardPeerULDataIP;               /* 上行间接转发对端数据IP */
    ULONG ulIndirectForwardPeerTeidu;                /* 下行间接转发对端数据隧道标识 */
    ULONG ulIndirectForwardPeerDataIP;               /* 下行间接转发对端数据IP */
    //34
    USHORT usCfProfileListId[MAX_CFPROFILES_FROM_ONE_GX_MESSAGE];  /*存放cf-profile id的数组*/
    UCHAR  ucCfProfileListNum;              /*cf-profile的个数*/
    UCHAR  ucAccMsgType;
    USHORT usCoaPort;
    UCHAR ucSendCoaReqN3Times;
    UCHAR ucIdentifier;
    ULONG ulPdpIndex;  /*从转发头中获取，保存TB,TP*/
    UCHAR ucRoleChanged;          /* 判断角色是否发生过变化 */
    UCHAR ucIdlePagingIndication;        /* 标识idlePaging流程,下表项时,需要根据该指示,更新idlePaging相关标识 */
    UCHAR ucPppFlag         : 4;                      /* 新增ppp标志 */
    UCHAR ucLocCOAFlag     : 1;                      /* 新增ppp标志 */
    UCHAR ucBitRatChangeTriggerFlag:1;
    UCHAR ucBitCongestionRptFlag:1;
    UCHAR ucNewRaiChangeFlag :1;
    UCHAR ucPcscfMainIpv4   :4;
    UCHAR ucPcscfMainIpv6   :4;
    UCHAR ucPcscfBkpIpv4   :4;
    UCHAR ucPcscfBkpIpv6   :4;
    SCCG_LICENSETYPE_S ucLicneseType;
    UCHAR ucCiifFlag:2;
    UCHAR ucSendPodMsgTimes:6;
    GTP_EVOLVED_ARP stEvolvedARP;  /*1字节*/
    USHORT usPcscfGrpoupIndex;
    USHORT usPcscfGrpoupIndexV6;


    /*  */
    ULONG ulPcrfcTransID;
    ULONG ulPcrfcTransIDRSV;
    ULONG ulGtpv2Scene;
    ULONG ulLeftIpAddr;
    //60
    //USHORT usMSProfilelistIndex;  /*用于记录动态策略，如果此索引非法则判断为非MSD用户, 此标记由IPN修改，AM读。 AM负责修改bit1MsdFlag 标记*/
    USHORT usNasSigPort;
    UCHAR ucAuthenticator[16];
    ULONG ulRadiusServerIP;
    UCHAR ucTetheringFlag;
    /*  Added by liuyan 00195624 on 2012-9-17 for SBR特性 */
    //UCHAR ucMseProfileListOper;
    UCHAR ucMsdLogicalSlotId;     /*MSD板的slot*/

    UCHAR ucMsdOSId;                  /*MSD板的OS*/
    UCHAR ucSGType;
    UCHAR ucMsdSgId;                   /*MSD板的SG*/
    UCHAR ucLocalLocationReportFlag;
    UCHAR ucBitRaiTriggerFlag :1;
    UCHAR ucClearFlg   :1;  /* 上下文清除标记 DTS2012101004007 */
    UCHAR ucBitTaiTriggerFlag :1;
    UCHAR ucBitEcgiTriggerFlag :1;
    UCHAR ucBitUliTriggerFlag :1;
    UCHAR bit1MsdFlag :1;  /*是否是MSD用户, 该标记在MSD返回有效SG等信息时置位*/
    UCHAR bit1MSDFlagc:1;           /*是否正在进行在线注入*/
    /*SPU向MSD-SDU发送消息后记录已发请求消息标记，后续收到MSD返回的响应消息后，清除此标记.
       如果SPU板没发送激活请求，就收到MS的响应消息，则直接丢弃该消息。*/
    UCHAR bit1SendReqFlag:1;
    /* Added end by liuyan 00195624 on 2012-9-17 for SBR特性*/
    UCHAR aucUliInfo[MAX_CONGESTION_RPT_ULI_LEN];
    UCHAR ucL2InfoLen;
    UCHAR ucContChargingAdded:1;
    UCHAR ucIpv6Added:1;
    UCHAR ucIpv6ChargingAdded:1;
    UCHAR ucIpv4v6Added:1;
    UCHAR ucBit2SelectType:2;
    UCHAR ucSendCreatHashFlag:2 ;  /* 是否需要通知SD和SDU重建表项 */
    UCHAR ucMseDataTrcUpFlag         :1;
    UCHAR ucMseDataTrcDownFlag       :1;
    UCHAR ucMseDropEmsFlag           :1;
    UCHAR ucbit1VogEmsFlag:1;
    UCHAR ucBit4Reserved:4;
}SDB_SCCG_CONTEXT_S,SDB_GSPU_CONTEXT_S;
#endif

//
//license define
//
typedef struct tagGTP_LICENSETYPE_S
{
    UCHAR  ucContextBaseBill:1;  /*是否为内容计费*/
    UCHAR  ucCamel3Prepay:1;  /*是否为camel3 预付费*/
    UCHAR  ucHotBilling:1;  /*是否为hit billing */
    UCHAR  ucL2tpFlag:1;    /*是否为l2tp*/
    UCHAR  ucIpV6Flag:1;   /*是否为IPV6*/
    UCHAR  ucIpV4V6Flag:1;   /*是否为IPv4V6*/
    UCHAR  ucPccLicenseFlag:1;    /*是否为PCC用户激活*/
    UCHAR  ucHomeZoneLicenseFlag:1;    /*是否为HZ用户激活*/
    UCHAR  ucRoutingBehindMsFlag:1;  /*是否为routing behind ms用户*/
    UCHAR   ucRadiusFlag:1;/*是否为radius功能用户*/
    UCHAR ucQchatLicenseFlag:1;    /*是否为Qchat用户激活*/
    //UCHAR ucReserve:6;
    UCHAR ucMultiServLicenseFlag:1;    /*是否为Multi Service用户激活*/
    UCHAR  ucOnlineChargeFlag:1;/*是否为在线计费用户*/
    /* Modified start at 2012-3-6 by yuanhao for 网络侧二次激活License控制 */
    UCHAR ucNetSecActFlag:1;   /* 是否网络侧二次激活，只适用于融合网关的Gn/Gp SGSN接入 */
    /* Modified start at 2012-3-6 by yuanhao for 网络侧二次激活License控制 */

    UCHAR ucDhcpv6Flg:1;
    UCHAR ucPdv6flag:1;
    ULONG ucAdcAdd: 1;    /* 1,增加过ADC的license统计 0，没有增加过ADC的license统计*/
    UCHAR reserv:7;
    UCHAR reserv1;
}VOS_PACKED GTP_LICENSETYPE_S;

//
//gtpv2 indication define
//

//from beijing UGW---
typedef struct tagAM_GTPV2_INDICATION_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    VOS_UINT8 btDAF:1;
    VOS_UINT8 btDTF:1;
    VOS_UINT8 btHI:1;
    VOS_UINT8 btDFI:1;
    VOS_UINT8 btOI:1;
    VOS_UINT8 btISRSI:1;
    VOS_UINT8 btISRAI:1;
    VOS_UINT8 btSGWCI:1;
    VOS_UINT8 btReserved:1;
    VOS_UINT8 btUIMSI:1;
    VOS_UINT8 btCFSI:1;
    VOS_UINT8 btCRSI:1;
    VOS_UINT8 btP:1;
    VOS_UINT8 btPT:1;
    VOS_UINT8 btSI:1;
    VOS_UINT8 btMSV:1;
    VOS_UINT8 btRetLoc:1;
    VOS_UINT8 btReserved1:2;
    VOS_UINT8 btS6AF:1;
    VOS_UINT8 btS4AF:1;
    VOS_UINT8 btReserved2:1;
    VOS_UINT8 btISRAU:1;
    VOS_UINT8 btCCRSI:1;
    VOS_UINT8 ucLen;

#else
    VOS_UINT8 btSGWCI:1;
    VOS_UINT8 btISRAI:1;
    VOS_UINT8 btISRSI:1;
    VOS_UINT8 btOI:1;
    VOS_UINT8 btDFI:1;
    VOS_UINT8 btHI:1;
    VOS_UINT8 btDTF:1;
    VOS_UINT8 btDAF:1;
    VOS_UINT8 btMSV:1;
    VOS_UINT8 btSI:1;
    VOS_UINT8 btPT:1;
    VOS_UINT8 btP:1;
    VOS_UINT8 btCRSI:1;
    VOS_UINT8 btCFSI:1;
    VOS_UINT8 btUIMSI:1;
    VOS_UINT8 btReserved:1;
    VOS_UINT8 btCCRSI:1;
    VOS_UINT8 btISRAU:1;
    VOS_UINT8 btReserved2:1;
    VOS_UINT8 btS4AF:1;
    VOS_UINT8 btS6AF:1;
    VOS_UINT8 btReserved1:2;
    VOS_UINT8 btRetLoc:1;
    VOS_UINT8 ucLen;
#endif
} VOS_PACKED AM_GTPV2_INDICATION_S;

#define M_MAX_BEARER_NUM        11

/*BSSID部分和stPmipv6LeftPeerAddr共用(此字段只有pmip用户使用,和s2a接入互斥,可以共用)*/
typedef struct tagGTP_TWAN_ID_BSSID_S
{
#if (UGW_BYTE_ORDER == UGW_BIG_ENDIAN)
    UCHAR btBSSID:1;       /*BSSID 是否有效标志位*/
    UCHAR btReserved:7;
#else
    UCHAR btReserved:7;
    UCHAR btBSSID:1;       /*BSSID 是否有效标志位*/
#endif
    UCHAR aucBSSID[M_TWANID_BSSID_LEN];
}VOS_PACKED GTP_TWAN_ID_BSSID_S;

/*pmip对端V6地址和twanid中的bssid的联合体*/
typedef union unGTP_PMIPV6PEERADDR_BSSID
{
    in6_addr stPmipv6LeftPeerAddr;     /* 16字节 */
    GTP_TWAN_ID_BSSID_S stBSSID;       /* 7字节 */
} VOS_PACKED unGTP_PMIPV6PEERADDR_BSSID;

typedef struct tagGTP_PMIPV6PEERADDR_BSSID
{
    unGTP_PMIPV6PEERADDR_BSSID unPmipV6addrOrBSSID;    /*16*/
} VOS_PACKED GTP_PMIPV6PEERADDR_BSSID;

//
//sdb data struct define
//


typedef struct tagSDB_GSPU_CONTEXT_S
{
    /**********************备份相关***************************/
    ULONG ucBackupType: 8;    /* 备份相关 */
    ULONG ulBackupNext : 24;  /* 备份相关 */
    ULONG ucBackupFlag: 1;    /* 备份相关 */
    ULONG ucNotifyDelGi: 1;
    ULONG ucBatchNotActive: 1;/* 批备的时候，处于更新状态的用户 */
    ULONG ucQosRleaseFlag: 1; /* SGW改变多承载切换失败 释放标识 */
    ULONG ucEarpChangeForMsgProc: 1;
    ULONG ucSgsnReqMsgWithEarp: 1;
    ULONG ucCpuxDeleteFlag: 1;
    ULONG ucCarType: 1;       /* 用来计数pdp使用的car资源类型0:AMBR CAR,1:PDP CAR.for DTS2013012804080 */
    ULONG ulBackupPre : 24;   /* 备份相关 */
    ULONG ulGspuBdIndex;      /* 该记录在SC上PDP Context表中索引 */
    ULONG ulDefaultGspuIndex; /* 专有承载所对应的缺省承载的gspu index，用于根据专有承载反查缺省承载，缺省承载该字段为全f*/

    /**************** 指针字段统一放在最前面 *********************/
    AM_IPN_MSE_PROFILE_INFO_S *pstMseProfileInfo;
    GTP_IE_PROTO_CONF_OPT_S * pstPCO; /* Protocol Configuration Option(协) */
    GTP_IE_PCO_PARSE_S * pstPCOParse; /* PCO解析后的内容*/
    AM_GTPV2_TRACE_INFO_S *pstTraceInfo;/*UGW 1.1:Trace info暂存指针，发送消息后指针释放*/
    UCHAR* pucAAANegoRspMsg;          /* AAA鉴权响应消息指针Session和idle时长都在这里面*/
    SDB_L2TP_INFO_S * pstL2TPInfo;
    S_GTPV2_PAA *pstGTPV2PAA;
    VOID *pstMMEFqCsidNext;           /* MME FQ-CSID链表中的下一个结点 */
    VOID *pstSGWFqCsidNext;           /* SGW FQ-CSID链表中的下一个结点 */
    VOID *pstPGWFqCsidNext;           /* PGW FQ-CSID链表中的下一个结点 */
    SDB_TFT_S* pstTft;
    SDB_WITHDRAW_DATA_S *pstWithdrawData;
    GTP_QOS_S *pstOriginalNegoQos;
    MEDIA_DETECT_S * pstMediaDetectElement;
    GTP_SAE_QOS_S *pstOriginalUEReqQos; /*用于记录UE请求过的qos信息，多次累加的结果*/
    AAA_Service_List *pstServiceList; /* Servic-List指针 */
    UCHAR *pstPrcfUpdateMsg;          /* 保存PCRFC RAR更新消息 */
    UGW_TFT_QOS_UPDATE_BAKUP_S *pstQosRollBack;     /* 用户缺省承载的QOS回退 */
    UCHAR* pucLapRspMsg;              /* 包含DHCPV6信息的Lap响应消息存在此处 */

    RELTMR_T ulTimerId;               /* 定时器事件ID */
    RELTMR_T ulBearCmdTimerId;        /* 定时器事件ID */

    GTP_IMSI_S stImsi;                /* 用户IMSI信息(协) ，8字节 */
    GTP_IMEI_S stIMEI;                /* 8字节 */
    GTP_MSISDN szMsisdn;              /* 用户MSISDN信息(协)，8字节 */
    ULONG ulSgwLeftLocTeidc;          /* 左侧本端信令隧道标识 */
    ULONG ulS5_Gn_LocTeidc;           /* 右侧本端信令隧道标识 */
    ULONG ulSgwLeftPeerTeidu;         /* 左侧对端数据隧道标识 */
    ULONG ulS5_Gn_PeerTeidu;          /* 右侧本端数据隧道标识 */
    ULONG ulS5_Gn_PeerTeidc;          /* 右侧对端信令隧道标识 */
    ULONG ulIPv4Addr;                 /* GGSN使用这个保存手机地址 */
    in6_addr stIPv6Addr;

    /******************************************************************************************************/
    /* 重要事项，以上字段已经保证4/8字节对齐；修改时需要注意同步修改数据字典sdbdatarecord.c、sdbproduct.h */
    /******************************************************************************************************/

    USHORT usVpnId;            /* IPV4 VPN ID */
    USHORT usIpv6VpnId;        /* IPV6 VPN ID */

    UCHAR ucPdpType;           /* PDP类型,取值参见gtp.h ,注意GGSN和USM间的转换 */
    UCHAR ucRatType;           /* 接入类型 */
    USHORT usApnIndex;         /* 该上下文对应的APN索引号(协) */

    UCHAR ucIPv4AllocType;     /* 地址分配方式，静态，本地，RADIUS等 */
    UCHAR ucIPv6AllocType;     /* 地址分配方式，静态，本地，RADIUS等 */
    UCHAR ucDpeId;             /* DPE 逻辑ID  */
    UCHAR ucRspCause;          /* 用户激活，应答消息中应携带的原因值 */

    ULONG ulFilterTableIndex;  /* 数据面过滤条件链表的索引n*/
    ULONG ulActiveTimeStamp;   /* 激活时间戳 */
    ULONG ulSessionTimeout;    /* Session 超时时间长 */

    UCHAR ucMachineState;      /* GTPV2 一级状态 */
    UCHAR ucMachineL2State;    /* GTPV2 二级状态 */
    UCHAR ucRoleChanged;       /* 判断角色是否发生过变化 */
    UCHAR ucIpResourceFlag: 1; /* 1表示占用，0表示未占用 */
    UCHAR ucNotifyPeerDel : 1;
    UCHAR ucOldUsrTypeFlg : 2;
    UCHAR ucTimezoneFlagForS1Handover: 1;   /* 切换到合一场景的S1 Handover，需要暂时存储时区是否改变的信息 for BI8D02475 */
    UCHAR ucGtpuExtendFlag: 1;   /* 用于给PF下发GTP-U封装标识*/
    UCHAR ucLeftNoCrsiFlag: 1;   /* 用于BRC消息且只有trigger变化，crsi不支持时控制网关不发update消息*/
    UCHAR ucCrsiChangeFlag: 1;   /* 存储CRSI标志是否与之前发生了变化 */

    UCHAR ucChargingChar[2];     /* 计费特征(协) */
    UCHAR ucSelectMode  : 3;     /* APN选择模式(协)，取值参见上面的宏 */
    UCHAR ucUEInitProc  : 1;     /* 由UE触发的处理，Wangyuting add for BI8D00507,2009-5-4*/
    UCHAR ucDTI : 1;             /* 更新消息里Direct Tunnel Flag信元的DTI标志位,0表示2Tunnel,1表示1Tunnel */
    UCHAR ucChargeOnlineFlag : 1;
    UCHAR ucChargeOfflineFlag : 1;
    UCHAR ucAmbrChangeFlag : 1;  /* 判断AMBR是否发生过变化 */

    UCHAR ucGtpVer      : 2;     /* 版本信息(协)，取值参见gtp.h */
    UCHAR usAcctStopCause   : 4; /* 计费结束原因值 */
    UCHAR ucIsActByTauOrHo : 1;  /* 该上下文被激活是由于TAU或HANDOVER标志,与附着区分  */
    UCHAR ucGetIpFromDhcps : 1;

    USHORT usLocSigFlowLbl;      /* 本端(GGSN)信令GTP-Flow标识(协) ，只有v0使用*/
    USHORT usLocDataFlowLbl;     /* 本端数据GTP-Flow标识 只有v0使用*/
    USHORT usPeerSigFlowLbl;     /* 对端(SGSN)信令GTP-Flow标识 只有v0使用*/
    USHORT usPeerDataFlowLbl;    /* 对端数据GTP-Flow标识 只有v0使用*/

    USHORT usMSTimeZone;
    USHORT usLeftRecovery;
    USHORT usRightRecovery;
    UCHAR ucMsdMseCompInstanceID;
    UCHAR ucChrPTI;

    GTP_ADDITIONALTRACEINFO_S stAdditionalTraceInfo;     /*跟踪信息,8字节*/

    USHORT usTraceId;
    UCHAR ucSgwListOfInterfaces;
    UCHAR ucPgwListOfInterfaces;

    ULONG ulGtpuIndex;                /*下发给转发面的gtpuindex*/
    ULONG ulSlaveTimeStamp;
    ULONG pathallowsn : 2;            /*消息冲突场景，用来判断是否是path申请的sn,不能在发消息时清掉*/
    ULONG ulPathSn: 16;
    ULONG ulNotifyPcrfChangeULI:1;
    ULONG ucPcoDir :1;    /*监听上报pco方向 VOS_TURE代表NET-UE;VOS_FALSE代表UE-NET*/
    ULONG ulUserTrafficPerf:4;        /*用户TrafficClass资源位置*/
    ULONG ulDiffUserPriPerFlag : 2;   /*保留字段暂未使用*/
    ULONG ulDiffServicePriPerFlag : 3;/*保留字段暂未使用*/
    ULONG ulUserPriPerfFlag  : 3;     /*用户优先级性能统计资源位*/

    /*========AM专用属性==============*/
    UCHAR ucIsSecActivateFlg  : 2;         /* 该上下文是否是二次激活上下文的标识 ,normal 表示是一次激活或缺省，second表示二次或专有承载*/
    UCHAR ucPreCMFail         : 1;         /* 是否CM在激活请求时失败*/
    UCHAR ucPreCMFailSendFlag : 1;         /* 上一次接收到的消息类型  */
    UCHAR ucSmResourceAdd     : 1;         /* 标记发激活消息给了SM Wangboyu:该标志位置1表示需要通知IPN释放资源，释放资源的级别为用户级别，否则会导致user-profile删除不了 */
    UCHAR ucRepeatFlag        : 1;         /* 给备板使用,用于重复激活的判断,避免多删除Gi表*/
    UCHAR ucIsMnrg            : 1;         /* 向SGSN发送的响应消息中是否携带控制面TEID ，   二次激活，就不用携带回去*/
    UCHAR ucIsReactiveFlg     : 1;         /* 判断是否为重复的上下文 0 － 非，1－重复上下文 */
    UCHAR ucPrevMsgType;                   /* 上一次接收到的消息类型  */
    UCHAR ucVirtualApnMapCounter : 2;      /* 用作记录虚拟apn映射次数，包括所有映射类型，最多三次*/
    UCHAR ucApnRestricFlag       : 1;      /* apn-restriction */
    UCHAR ucGxRelType            : 1;      /* Added by c00110835 for CR20120130050:用于表示和PCRF接口版本使用的R8接口还是R7接口*/
    UCHAR Conflict               : 2;      /* 消息冲突时，用来终结消息 */
    UCHAR ucIPReleaseFlag        : 1;      /* 激活前收到地址释放消息 */
    UCHAR ucFilterTableIndexReleaseFlag:1; /* add by mayouwei 20090407 for c01 B037 地址泄漏*/
    UCHAR ucUgwRole;                       /* 定义见UGW_NET_ELEMENT_ROLE_E */
    UCHAR ucHplmnIndex;                    /* 保存HPLMN INDEX，用户激活时保存，二次和专有上下文继承该字段 */
    T3GPP_GGSN_MCC_MNC_S stMccMnc;         /* 3字节 是GGSN,PGW,P+S HPLMN,按照stImsi从HPLMN匹配到的HPLMN，如果在SGW上，该字段表示PGW的PLMN */

    UCHAR ucUsername[MAXUSERNAMELEN];      /* 64 CM SM计费使用 */

    /*========AM处理流程标示=======*/
    UCHAR ucSgwIsTraceFlag     : 1;
    UCHAR ucPgwIsTraceFlag     : 1;
    UCHAR ucSendTraceInfoToPgw : 1;
    UCHAR ucArpChanged         : 1;        /* 用于记录上下文中的ARP是否变化 */
    UCHAR ucSendDDNFlag        : 1;        /* 记录UE是否发过DDN消息:0:没有发过DDN;1:已经发过DDN*/
    UCHAR ucUsrInforTime       : 3;        /* PPP下发表项主题 */

    UCHAR ucNoGiTableFlag    : 1;          /* 是否下发Gi表项的标记PPP协商的时候不用下发Gi表 */
    UCHAR ucVerChange        : 2;          /* 0:V0 ,1:V1,2 V0->V1 3 V1-<V0 ，GGSN专用，涉及到表项下发部分，需要修改*/
    UCHAR ucaddAllocType     : 1;          /* IPV4,标识是否采用AAA返回地址 0:表示没有采用AAA返回地址；1表示采用AAA返回地址*/
    UCHAR ucIPV6addAllocType : 1;          /* 标识是否使用aaa返回的IPV6地址，0表示不使用，1表示使用*/
    UCHAR ucCfPerfFlg        : 1;          /* cf用户性能统计标示，统计在ipn和am均会统计，为避免倒换期间误删除加入此标记*/
    UCHAR ucStaticIpRouteType: 2;          /* route下发类型:0 ALL,1 HLR,2 RADIUS,3 DISABLE*/

    USHORT usAliaCdbIndex;                 /* APN别名在CDB中的index(0-999)*/
    T3GPP_SGSN_MCC_MNC_S stSgsnPlmn;       /* 4字节 如果是SGW，该字段表示PGW的PLMN，如果是GGSN,PGW,PS，该字段表示对端SGW,SGSN的PLMN */

    /*========AM处理流程标示=======*/

    GTP_QOS_S stReqQos;                    /* 请求的QOS信息 ,24字节*/
    GTP_QOS_S stNegQos;                    /* 经过协商的QOS信息(协) ,24字节 */
    GTP_QOS_NECESSARY_S stOldQos;          /* 20字节，更新使用，保存当前已经在使用的Qos 的必需参数*/
    USHORT usVirtualapnIndex;              /* 虚拟APN或者single APN */
    UCHAR ucAuthCounter   : 3;             /* 用作记录用户鉴权次数 */
    UCHAR ucVirtualapnFlag :1;             /* 是否虚拟APN映射到真实APN */
    UCHAR ucIdleTimerOutFlag :1;           /* 是否idle 超时 */
    UCHAR ucAntiSpoofingDelFlag:1;         /* 该上下文已经发送过去活请求 */
    UCHAR ucMainContextFlag : 1;           /* 该字段仅在平滑时使用,用于标识当前用户情况*/
    UCHAR ucAddrAllocDhcpsFlag:1;          /* 是否dhcp 方式分配地址，UGW专用*/

    UCHAR ucDelCause;                    /* 去活原因值 DTS2014011806081 delcause 有7bit扩展到8bit*/


    /*分别用来保存（更新时）新增和原来的上下行带宽分别占用标记*/
    UCHAR ucUpBandFlag      : 4;
    UCHAR ucDownBandFlag    : 4;

    UCHAR ucOldUpBandFlag   : 4;
    UCHAR ucOldDownBandFlag : 4;

    UCHAR ucULIValid        : 1; /* 标示上下文中的ULI信息合法CM组使用*/
    UCHAR ucTimeZoneValid   : 1; /* 标示上下文中的Timezone信息合法CM组使用*/
    UCHAR ucNegoUsrPriResv  : 1;
    /* Added start by jiexianzhu at 2013.12.16 for 本地映射 VLRID/GT */
    UCHAR ucTransparentFromRadiusFlag : 1; /* 标记 aucTransparentData 中数据激活时从radius获取(1),从本地配置获取(0) */
    /* Added end by jiexianzhu at 2013.12.16 for 本地映射 VLRID/GT */
    /* Added start by p00114481 at 2013-11-06 UGW9811V900R011C00 for GGSN/PGW Proxy特性 */
    UCHAR ucGateWayProxyFlag : 1;      /* Proxy 上下文标记*/
    UCHAR ucProxyWaitResponseFlag : 1;  /* Proxy 上下文等待响应消息标记*/
    /* Added end by p00114481 at 2013-11-06 UGW9811V900R011C00 for GGSN/PGW Proxy特性 */
    UCHAR ucRedundancyV4Flag: 1;
    UCHAR ucRedundancyV6Flag: 1;

    UCHAR ucOldUsrPri   : 3;     /* 保存用户出于激活成功后的值，主要用于QOS更新时与新的请求QOS进行对比*/
    UCHAR ucOldSrvLevel : 5;

    ULONG ulWaitCmTimeStamp;     /* 记录删除流程中等待cm响应时间戳 */

    /* 将接口索引、IP计入用户上下文中，为了实现N+1的快转*/
    ULONG ulUpInterfaceIndex;    /* 上行接口Subindex*/
    ULONG ulDnInterfaceIndex;    /* 下行接口Subindex*/

    /*========GTP消息中携带的信元标示=======*/
    UCHAR ucIMEISVOccur              : 1;
    UCHAR ucRatTypeOccur             : 1;
    UCHAR ucUserLocationInfoOccur    : 1;
    UCHAR ucMSTimeZoneOccur          : 1;
    UCHAR ucAdditionalTraceInfoOccur : 1;
    UCHAR ucChargingCharOccur        : 1;
    UCHAR ucRAIUpdateFlag            : 1;
    UCHAR ucLifeTimeFlag                 : 1;   /* 用于PMIP场景下标识定时器类型 */

    /*========上下文类型和属性的标示=======*/
    UCHAR ucIsTftExist      : 1;       /* 该上下文是否包含TFT的标识 */
    UCHAR ucDataFlag        : 2;       /* 数据转发标志 */
    UCHAR ucL2TPFlag        : 1;       /* 新增L2TP标记 */
    UCHAR ucPppFlag         : 4;       /* 新增ppp标志 */

    UCHAR ucCmdProcess      : 1;       /*用于表示pcc用户mbc流程是否处理add by fanzhiyu on 2013.10.28 ps10.1 for DTS2013102303826*/
    UCHAR ucLiFlag          : 1;
    UCHAR ucDataTrcFlg      : 2;
    UCHAR ucIpv6RouteMsgNum : 4;       /* 以前是ucMsgNum */

    UCHAR ucFlagRsv      : 5;          /* 系统中需要保存的标志位;目前使用第0位保存当前上下文是否使用了GGSN QOS*/
    UCHAR ucImsFlag      : 2;          /* 上下文类型标志*/
    UCHAR ucDhcpFlag     : 1;          /* 增加表示是否是DHCP用户的标志  */
    /* 上面4字节对齐 */

    UCHAR ucBit2SelectType    : 2;   /*PCC使用字段: 0 基于pcrfgrp选择service；1:基于全局realmIdex选择索引；2:基于apn下的realm选择索引; 3:初始化值(又AM保证)*/
    UCHAR ucStripFlag        : 1;      /* 剥离域名标志 */
    UCHAR ucConfict : 1;
    UCHAR ucLcenseFlag       : 1;      /* added by c00110835 用于V2用户是否统计了License */
    UCHAR ucErrorIndicationDirect : 1; /* SGW上标示error indication的方向:0-表示从左侧收到，1-表示从右侧收到*/
    UCHAR ucPrepImsFlag      : 2;      /* 专有承载是IMS信令上下文的预备指示，等和PCRF交互完后即可转正*/

    UCHAR ucLapSectionV4Num;
    UCHAR ucLapSectionV6Num;
    UCHAR ucipv4LAPSequence:4;      /*ipv4地址对应的lap集中点编号*/
    UCHAR ucipv6LAPSequence:4;      /*ipv6地址对应的lap集中点编号*/
    /* 上面4字节对齐 */

    GTP_LICENSETYPE_S ucLicneseType;/* 4字节，用于license 判断的类型*/
    USHORT usPoolIndex;             /* AAA返回的地址池索引*/
    USHORT usPoolIPV6Index;         /* AAA返回的ipv6地址池索引*/

    /*========CM相关=======*/
    ULONG ulCdrfChargingId;         /* CDRF计费ID(协) */
    ULONG ulCgAddr;                 /* CG地址 */
    ULONG ulRadiusIndex;            /* AAA计费的索引*/
    ULONG ulIdleTime;               /* 最终确认的空闲上下文时长*/

    UCHAR ucChargeFlag        : 4;  /* 热计费，实时计费等标记，CM补充一下*/
    UCHAR bit1OnlChrgEnabled  : 1;  /* 1: online charging enabled; 0: online charging disabled*/
    UCHAR bit1OflChrgEnabled  : 1;  /* 1: offline charging enabled; 0: offline charging disabled*/
    UCHAR ucOfflineBillAttrFlg: 1;  /* TMO-Offline-Billing-Attr是否有效值，0表示无效，1表示有效 */
    UCHAR ucBitAccountingFlag : 1;  /* 是否使能AAA计费 */
    UCHAR ucTimeQuotaType;          /* TMO-Offline-Billing-Attr属性中Time-Quota-Type的值*/

    USHORT usMMECsId;               /* MME FQ-CSID中的CSID部分*//*Wangyuting add for UGW1.1*/
    USHORT usSGWCsId;               /* SGW FQ-CSID中的CSID部分*//*Wangyuting add for UGW1.1*/
    USHORT usPGWCsId;               /* PGW FQ-CSID中的CSID部分*//*Wangyuting add for UGW1.1*/
    ULONG ulMMENodeId;              /* MME FQ-CSID中的NODE-ID部分，暂时只IPV4地址*//*Wangyuting add for UGW1.1*/
    ULONG ulSGWNodeId;              /* SGW FQ-CSID中的NODE-ID部分，暂时只IPV4地址*//*Wangyuting add for UGW1.1*/
    ULONG ulPGWNodeId;              /* PGW FQ-CSID中的NODE-ID部分，暂时只IPV4地址*//*Wangyuting add for UGW1.1*/
    ULONG ulMMEFqCsidIndex;         /* MME FQ-CSID链表索引*//*Wangyuting add for UGW1.1*/
    ULONG ulSGWFqCsidIndex;         /* SGW FQ-CSID链表索引*//*Wangyuting add for UGW1.1*/
    ULONG ulPGWFqCsidIndex;         /* PGW FQ-CSID链表索引*//*Wangyuting add for UGW1.1*/

    ULONG ulBaseTimeInterval;       /* TMO-Offline-Billing-Attr属性中Base-Time-Interval的值*/
    ULONG ulAcctInterimVolume;      /* TMO-Acct-Interim-Volume属性 */

    USHORT usPriFuncNameIdx;        /* TMO-Primary-Event-Charging-Function-Name属性对应的index，全f表示无效 */
    USHORT usSecFuncNameIdx;        /* TMO-Secondary-Event-Charging-Function-Name属性对应的index，全f表示无效 */
    AM_AUTH_TMO_TRIGGER_TYPE_S stTriggerType;  /* 4字节 对应AM_AUTH_TMO_TRIGGER_TYPE_S */

    AM_CM_UPDATETYPE_S stUpdateType;/* 9字节更新类型:GTP_CHANGE_SGSN_IP,GTP_CHANGE_QOS,GTP_CHANGE_LOCATION,GTP_CHANGE_RAT */
    UCHAR ucHomeZoneId;             /* Home Zone模块返回的Home Zone服务器状态 */
    UCHAR ucChargingType;           /* AAA服务器下发的Billing-Type : 0=prepaid，1=post-paid，2=post-paid with credit control,
                                       3=prepaid with credit control，4=HLR, 5=wallet specific,
                                       6=wallet specific without credit control, 7=hot billing*/

    UCHAR ucIndirectForwardInputInterfaceType; /* 间接转发入接口类型 */
    UCHAR ucIndirectForwardOutputInterfaceType;/* 间接转发出接口类型 */

    UCHAR bit1SgwOflChrgEnabled: 1;
    UCHAR ucOcscForceDropFlag  : 1; /* tianshuang for CR20120301017*/
    UCHAR ucDhcpIPV6Flg        : 1; /* tianshuang for DHCP-IPV6 2012-07-10 标识用户是否为IPV6*/
    UCHAR ucBWMUsrFlg          : 1; /* 标识上下文为BWM用户,AM无法感知BWM,IPN无法感知角色切换,造成切换时相关话统不准确,增加该字段由AM在角色切换时计算 DTS2012011306321*/
    UCHAR ucBit4BearerReqMsgLeft:4;

    UCHAR ucSrvLevel         : 3;   /* 业务级别*/
    UCHAR ucL2tpChkFlg        :1;    /* l2tp用户核查标志位，用法:已经核查过置1，未核查过置0，核查过程中新接入用户置1 */
    UCHAR ucRadiusDisablePcc : 1;   /* 标识RADIUS是否下发禁用PCC标志*/
    UCHAR ucUsrTypeFlg       : 2;   /* 用户归属类型，后面干掉，注意替换代码*/
    UCHAR ucAAARspCCFlag     : 1;   /* 已使用for Celcom Single APN，AAA返回的CC值是否合法，1为合法 */

    UCHAR ucUpAmbrCarFlag    : 2;   /* 用于标识缺省承载是否使能了上行AMBR CAR功能,以便专有承载据此判断是否需要CAR功能 */
    UCHAR ucDownAmbrCarFlag  : 2;   /* 用于标识缺省承载是否使能了下行AMBR CAR功能,以便专有承载据此判断是否需要CAR功能 */
    UCHAR ucNotifyPcrfcFlag  : 2;
    UCHAR ucTeardownFlag     : 1;   /* 记录去活请求中是否携带了teardown，仅用于CHR上报时使用*/
    UCHAR ucPcoBcmMode       : 1;   /* 0表示PCO信元中携带不支持UE_NW；1表示支持UE_NW*/

    UCHAR aucTransparentData[32];   /* TMO-Transparent-Data属性，最大长为8 */

    /*========CM使用=======*/

    ULONG   ulpdpActForCmStampLow;  /* 上下文激活时间戳--低位*/
    ULONG   ulpdpActForCmStampHig;  /* 上下文激活时间戳--高位*/
    ULONG   ulpdpDelForCmStampLow;  /* 上下文去活时间戳--低位*/
    ULONG   ulpdpDelForCmStampHig;  /* 上下文去活时间戳--高位*/

    /*========SM使用=======*/
    USHORT usUserProfileID;         /* 该用户匹配的User Profile ID*/

    UCHAR  ucRecordType         : 2;/* 流量采集类型， 0: 统计3、4层流量 ,1:统计7层流量*/
    UCHAR  ucChargeMode         : 2;/* 计费属性，0:离线计费 , 1:离线计费*/
    UCHAR  ucChargePropertyFlag : 2;/* 标识该用户是否内容计费用户，0:普通,1:内容计费(FBC CBB),2:PDP CBB.（0：没有userprofile，1和2都绑定了userprofile）*/
    UCHAR  ucAliasMarking       : 1;/* Alias Marking使能标识,0:未使能,1:使能 */
    UCHAR  ucDDosFlag           : 1;/* 防DDOS攻击使能,0:未使能,1:使能 */

    UCHAR  ucAAAUserProfileFlag : 1;/* 0表示userprofile是本地分配；1表示AAA指定*/
    UCHAR  ucPerfForCmcc        : 1;/* 标识用户是否进行cmcc性能统计，该标记有ipn处理，am需要透传给pf*/
    UCHAR  ucPccL7ProcessFlag   : 2;
    UCHAR  ucPppFailReason      : 4;

    USHORT usUserProfileGroupID;    /* 该用户匹配的User Profile Group ID*/

    UCHAR  ucBwmSubscriberEnable: 2;/* 用户级BWM带宽使能标志*/
    UCHAR  ucBwmGroupEnable     : 2;/* 用户组级BWM带宽使能标志 */
    UCHAR  ucBwmGlobalEnable    : 2;/* 全局级BWM带宽使能标志 */
    UCHAR  ucActionSupport      : 1;
    UCHAR  ucBit1OnlineCharGranFlag :1;

    UCHAR  ucHZUserFlag:1;   /* 标识该用户是否为Home Zone用户。0:非Home Zone用户；1：Home Zone用户*/
    UCHAR  ucHZErrorFlag:1;  /* 标识该用户连接到的HomeZone Server当前是否正常运作。0:正常；1：HomeZone Server无响应*/
    UCHAR  ucHZRspFlag:1;    /* 是否收到HomeZone Server响应消息标志：初始化为0 0：没有收到 1：收到*/
    UCHAR  ucHZApnFlag:1;    /* 标识该用户是否以Home Zone APN激活。0:非Home Zone APN；1：Home Zone APN*/
    UCHAR  ucCoaNotifyUserProfileUpdated:1;  /* COA更新UserProfile标志，1,表示COA更新过,不允许SGSN的更新; 0,COA未更新,允许SGSN更新 */
    UCHAR  ucCoaQosChangedFlag:1;            /* 1,发生改变 0,未发生改变 */
    UCHAR  ucCoaUserProfileChangedFlag:1;    /* 1,发生改变 0,未发生改变 */
    UCHAR  ucFbcAdd:1;                       /* 1,增加过FBC的统计 0，没有增加过FBC的统计*/

    ULONG  ulUsageRptCBIndex;
    USHORT usPmipLifetime;
    UCHAR ucRadiusL2tpFlg:1;           /* 使用标记标识是radius返回的L2TP属性，记录在上下文中 */
    UCHAR ucSlaveSessionTimeOutFlg:1;  /* 备板如果SESSION TIMEOUT超时后记录标志，平滑时删除，避免主板丢失备份导致用户残留 */
    UCHAR ucActDedBearerFlag:1;        /* 用来保存session中激活的专有承载的个数，仅在相应的缺省承载下统计*/
    UCHAR ucOldGtpVer:2;
    UCHAR ucPppNotL2tpFlag:1;          /* 用来确定PPP终结用户相关性能统计是否统计过*/
    UCHAR ucSADedic:2;                /* 标识专有承载是否为DPI或L3,4层解析触发,ue触发或动态pcc场景:0，DPI:1，L34层:2*/
    UCHAR ucAmRsv;                     /* Session下曾经激活过的承载数量 */

    SDB_REQ_MSG_IP_INFO_S stReqMsgIpInfo; /* 12字节 请求消息中的IP头信息，在回响应消息时使用，不需要备份 */

    ULONG ulLeftPeerTeidcOld;          /* 用于切换保存原侧对端网元如MME、SGW的信息用户后续消息处理*/
    ULONG ulSgwLeftPeerSigIP;          /* 信元中解析出的左侧对端IP */
    ULONG ulSgwLeftLocSigIP;           /* 左侧本端信令IP */
    USHORT usSgwLeftPeerSigPort;       /* IP头中的左侧对端信令port */
    USHORT usSgwLeftLocSigPort;        /* 左侧本端信令port */
    ULONG ulSgwLeftPeerDataIP;         /* 左侧对端数据IP */
    ULONG ulSgwLeftLocDataIP;          /* 左侧本端数据IP */
    USHORT usLeftSigPathId;            /* 左侧信令路径索引*/
    USHORT usLeftDataPathId;           /* 左侧数据路径索引 */
    ULONG ulSgwLeftPeerTeidc;          /* 左侧对端信令隧道标识 */
    ULONG ulSgwLeftLocTeidu;           /* 左侧本端数据隧道标识 */
    ULONG ulLeftSendSeqNo;             /* 左侧发送的消息序列号 */
    ULONG ulLeftRcvSeqNo;              /* 左侧接收的消息序列号 */
    ULONG ulLeftTimeStamp;             /* 左侧接收消息的时间戳 */

    UCHAR ucLeftDataIfType;            /* 左侧数据面接口类型 */
    UCHAR ucLeftSigIfType;             /* 左侧控制面接口类型 */
    UCHAR ucLeftEncapType;             /* 左侧封装类型*/
    UCHAR ucRightDataIfType;           /* 右侧数据面接口类型 */

    UCHAR ucRightSigIfType;            /* 右侧控制面接口类型 */
    UCHAR ucRightEncapType;            /* 右侧封装类型*/
    USHORT usPolicyId;                 /* SM使用的Policy Id */

    ULONG ulS5_Gn_PeerSigIP;           /* 右侧对端信令IP */
    ULONG ulS5_Gn_LocSigIP;            /* 右侧本端信令IP */
    USHORT usS5_Gn_PeerSigPort;        /* 右侧对端信令port */
    USHORT usS5_Gn_LocSigPort;         /* 右侧本端信令port */
    ULONG ulS5_Gn_PeerDataIP;          /* 右侧对端数据IP */
    ULONG ulS5_Gn_LocDataIP;           /* 右侧本端数据IP */
    USHORT usRightSigPathId;           /* 右侧信令路径ID */
    USHORT usRightDataPathId;          /* 右侧数据路径ID */
    ULONG ulS5_Gn_LocTeidu;            /* 右侧对端数据隧道标识 */
    ULONG ulRightSendSeqNo;            /* 右侧发送的消息序列号 */
    ULONG ulRightRcvSeqNo;             /* 右侧接收的消息序列号 */
    ULONG ulRightTimeStamp;            /* 右侧接收消息的时间戳 */
    ULONG ulControlBlockIndex;         /* 控制块索引 */
    ULONG ulIndirectForwardPeerDataIP; /* 下行间接转发对端数据IP */
    ULONG ulIndirectForwardPeerTeidu;  /* 下行间接转发对端数据隧道标识 */
    ULONG ulIndirectForwardLocTeidu;   /* 下行间接转发本端为对端分配的数据隧道标识 */

    GTP_ULI_S stULI;                   /* 20 */

    UCHAR ucHeartBeatTimoutNum;        /* 标识心跳检测消息超时次数 */
    AM_GTPV2_SERVING_NETWORK_S stGTPV2ServingNetwork;/*3字节*/
    UCHAR  ucRevForULI;                /* SDU 表项所在的VCPU */
    UCHAR  ucSduVcpuId;                /* SDU 表项所在的VCPU */
    USHORT usTokenId;                  /* 上下文的TOKEN ID */

    AM_GTPV2_INDICATION_S  stGTPV2Indication;  /* 4字节 */

    UCHAR ucChangeReportingAction;

    UCHAR ucServingNetworkOccur: 1;    /* 消息中是否携带了Serving NetWork信元 */
    UCHAR ucNetworkSecActFlag  : 1;    /* 网络侧二次激活，为1表示该二次上下文是由网络侧触发的，只适用于融合网关下V1用户；为0表示普通的左侧激活 */
    UCHAR ucBitPcrfCfFlag      : 1;    /* pcrf下发的cf标识，默认值为 0 */
    UCHAR  ucBitPcrfCarryCfFlag: 1;    /* 1表示pcrfc 下发了cf标记，0表示pcrfc 未下发了cf标记*/
    UCHAR ucIpflag             : 1;
    UCHAR ucSeqLinkNo          : 3;    /* 用于记录分配teidc绑定的sequece链索引*/

    GTP_EVOLVED_ARP stEvolvedARP;      /* 1字节 */

    UCHAR ucEmergencyFlag     : 1;     /* 标识当前用户是不是紧急呼叫用户,0:当前用户不是紧急呼叫用户;1:当前用户是紧急呼叫用户*/
    UCHAR ucImsiInvalidFlag   : 1;     /* 标识当前用户是否存在可用的IMSI;0:当前用户IMSI可用;1:当前用户IMSI不可用*/
    UCHAR ucBitTaiTriggerFlag : 1;
    UCHAR ucBitEcgiTriggerFlag: 1;
    UCHAR ucImsLocChangeFlag  : 1;     /* ims位置上报标记位,用于表示当pcrfc通知更新时是否需要向左侧发起更新和indication字段Octet 7的bit8置1 */
    UCHAR bit1MsdFlag         : 1;     /* 是否是MSD用户, 该标记在MSD返回有效SG等信息时置位*/
    UCHAR bit1UptByIdleTimeOut: 1;     /* 是否是cm idletimeout发起的更新  DTS2014031702885 */
    UCHAR bit1SendReqFlag     : 1;     /* SPU向MSD-SDU发送消息后记录已发请求消息标记，后续收到MSD返回的响应消息后，清除此标记.
                                          如果SPU板没发送激活请求，就收到MS的响应消息，则直接丢弃该消息。*/
    /*4*/

    USHORT usExternalEvent;            /* 原始激励 */
    UCHAR ucLinkedEPSBearId;
    UCHAR ucbit1TightInterwork: 1;     /* 0:松耦合  1:紧耦合 */
    UCHAR ucTetheringFlag     : 1;
    UCHAR ucLiDirectFlg       : 1;     /* 合法监听发起方标志位 1 代表网络侧，0 代表UE侧 modify usLichnIndex to usLiDirectFlg by w00221565 at 2013-03-01 for LI DTS2013011100335   */
    UCHAR usPMIPTimeoutFlg    : 1;
    UCHAR ucCorrelationID     : 4;     /* 网络二次激活使用 */
    /*4*/

    ULONG ulCmdSeqNo;                  /* cmd 信令的序列号 */

    USHORT usCmdType;
    UCHAR ucNotifyLeftDel : 1;
    UCHAR ucNotifyRightDel: 1;
    UCHAR ucPartNum       : 6;
    UCHAR ucRatTypeOld;                /* rattype变化的时候用于统计当前rat值对应的用户数 */
    /*4*/

    UCHAR ucEPSBearId;                 /* EPS Bear ID, GGSN使用这个变量当作NSAPI*/
    UCHAR ucPTI;                       /* Procedure Transaction Id*/

    UCHAR ucBCM              :2;       /* Bearer Control Mode*/
    UCHAR ucOldDTI           :1;       /* DT用户统计使用 */
    UCHAR ucApplyAddrSuccFlag:2;       /* 保留 */
    UCHAR ucRcvLBIFlag       :1;       /* 标记在SGW 收到的Modify 响应消息中携带LBI 信元*/
    UCHAR ucApplyAddrFailFlag:2;       /* 保留*/

    UCHAR ucConvergenceLicType     :3; /* 融合license类型,借用UGW_NET_ELEMENT_ROLE_E表示*/
    UCHAR ucConvergenceLicTypeForHO:3; /* 切换场景标记需要的融合license类型,借用UGW_NET_ELEMENT_ROLE_E表示*/
    UCHAR ucVirtualGiIdFlag        :1; /* 用于标记AAA是否下了GiId*/
    UCHAR ucSendToPcrfMBCMsg       :1; /* 0表示发送MBR消息,1表示发送MBC消息 */
    /*4*/

    ULONG ulVirtualGiId;               /* 用于存储AAA所下发的GiId */
    UCHAR ucBearCmdEBINum;             /* bearer resource /delete /modify command信令用 */
    UCHAR ucBearCmdEBI[M_MAX_BEARER_NUM];
    /*16*/

    UCHAR ucAllFilterNum    :5;        /* 静态pcc时用于记录当前所有filter数*/
    UCHAR ucSendRsp2Sm      :1;        /* 是否需要给sm回消息, 1:需要，0:不需要 */
    UCHAR ucIsCreatedByUE   :1;        /* 是否是UE触发创建的专有承载, 1:是，0:不是-本地规则触发 */
    UCHAR ucNeedSaveUEReqQos:1;        /* 是否需要保存UE请求的qos, 1:是，0:不是*/

    UCHAR ucLocalFilterNum       :5;   /* DPI或者L3,4层触发的filter个数*/
    UCHAR ucIsAlreadySaveUEReqQos:1;   /* 是否已经保存UE请求的qos, 1:是，0:不是*/
    UCHAR ucSendToPfFlag         :1;
    UCHAR ucDDNCauseFlag         :1;   /* 发送DDN消息时携带原因值的标志:0:不携带;1:携带*/

    UCHAR ucApnRestrictionForRsp ;     /* 用来保存apn下的配置的APN Restriction值，以便会消息时直接从上下文中获取，节省一次读CDB操作*/
    UCHAR ucPcrfcDelCause;             /* AM给pcrfc的去活原因值 */
    ULONG ulStateMachineTrace;         /* 状态机处理位置 */
    /*8*/

    in6_addr stMainDnsIp;
    in6_addr stBackupDnsIp;
    /*32*/

    ULONG ulIpv4PriDnsIp;              /* 主IPV4 DNS地址 */
    ULONG ulIpv4SecDnsIp;              /* 备IPV4 DNS地址 */
    /*8*/

    UCHAR ucGroupLevelServiceType;     /* 记录用户组级的业务类型， tos /non-tos*/
    UCHAR ucPccMode;                   /* modify by wangboyu at 2011-08-31 for PCC 融合 */
    USHORT usUserGroupID;              /* 用户组ID，同时也是用户组级BWM_CB数组的索引号 */
    USHORT usPmipSequence;
    UCHAR ucHandoffIndicator;
    UCHAR ucIpv6PrefixLength;          /* radius 返回的 IPV6 前缀长度 */
    /*8*/

    UCHAR ucToBeRmvFlag             :1;
    UCHAR ucRATorAMBRorULIChangeFlag:1;/* create/modify时RAT或AMBR是否改变*/
    UCHAR ucRightTunnelHasCreat     :1;/* 仅供SGW使用，用来标记SGW是否已经把Right Local FTEID-U 信息发送给PGW,
                                          SGW可以在CreatSession或者Modify Bearer消息中，把信息发给PGW */
    UCHAR ucLocSccgChangeFlg        :1;
    UCHAR ucLocDst                  :2;
    UCHAR ucPmipLifeTimeOP          :2;/* PMIP LifeTime定时器操作标识:0:无效;1:启动;2:删除;3:删除后启动*/

    UCHAR ucUserAttri               :4;
    UCHAR ucSupExtendQci            :4;

    UCHAR ucIdlePagingIndication;      /* 标识idlePaging流程,下表项时,需要根据该指示,更新idlePaging相关标识 */
    UCHAR ucApnRestriction ;           /* 用来保存createsessionrequest消息中的APN Restriction值，用于与apn下配置比较及重发消息中必选信元的检查*/
    /*4*/

    USHORT usS6bCurDiamSrvIndex;
    USHORT usS6bDraRealmIndex;

    APN_AMBR_S stApnAmbr;              /* 8字节Aggregate Maximum Bit Rate AMBR */

    ULONG ulPcrfcTransID;
    ULONG ulSessionIndex;              /* index of session cb */
    ULONG ulBearerIndex;               /* index of bearer cb */

    UCHAR ucPriOfcsIndex;              /* 主offline function(CG)的索引*/
    UCHAR ucSecOfcsIndex;              /* 备offline function(CG)的索引*/

    UCHAR ucIsRTUser :1;               /* 报表实时用户标记 */
    UCHAR ucBcmChanged:1;              /* 表示收到PCRFC更新消息中的BCM是否有变化*/
    UCHAR ucUserDefaultIdleTime:1;     /* 标识未配置idle-timeout时使用默认的idle时长,目前为1天,由软参bit1157控制,默认开,对所有用户生效*/
    UCHAR ucSuspendAdd:1;              /* 1,增加过suspend的统计  0，没有增加过suspend的统计*/
    UCHAR ucSPGWCsFlag:1;              /* SPGW激活失败时响应消息中Cause值的CS位置1还是置0,1表示CS需要置1,0表示CS需要置0*/
    UCHAR ucLiBkpFlag :1;              /* DTS2013052100045合法监听N+1备份成功标志位，0代表成功，1代表失败，恢复上下文备份后，如果该字段为失败，则去活上下文*/
    UCHAR ucFupEnableFlag :1;          /* 标识PCRF启用了FUP,用于给PF下表项 */
    UCHAR ucPrivateExtensionOccur:1;   /* 标识私有扩展段是否出现 Add by liangxuyang 00171541 for DelMsg Private_Extension at 2011-12-01*/

    UCHAR ucUsmBackupFlg:1;            /* 主板是否已经备份过标志*/
    UCHAR ucPrivateDelCause:3;         /* 标识私有原因值 Add by liuyan 00195624 for DelMsg Private_Extension at 2011-12-22*/
    UCHAR ucIsQchatIdletime:1;         /* idletime是否使用 qchat的idletime*/
    UCHAR ucCoaQosFlag:1;
    UCHAR ucSAEmsFlag:1;              /* Gn免维护SA标记*/
    UCHAR ucDropEmsFlag:1;             /* 丢包免维护是否开始的标记*/

    UCHAR ucPcrfcAuthReqType       :3; /* AM 处理pcrfc请求消息时，消息预处理 0 :成功; 1: 失败*/
    UCHAR ucPcrfcDelType           :1; /* AM 和pcrfc间的消息去活类型: 1 :session; 0: bearer*/
    UCHAR ucSlavePdpFlag           :1; /* 使用标记标识是备板用户，用于平滑时性能统计恢复用 */
    UCHAR ucNeedSendToMMEFlag      :1; /* 分离重复激活为合一时使用，用于标识通知pgw删除后delete-rsp消息不发送给mme，1:不需要，0:需要*/
    UCHAR ucRadiusPCMode           :2; /* 保留 */

    UCHAR ucPccResourceFlag        :1; /* ucPccResourceFlag: 1:占用PCC资源       0:表示没有占用PCC资源*/
    UCHAR ucReportingLevelDefault  :1;
    UCHAR ucMessageCode            :6; /* modify by wangboyu at 2011-08-31 for PCC 融合 */

    UCHAR ucRuleChangeFlag         :1;
    UCHAR ucTriggerChangeFlag      :1;
    UCHAR ucPcrfcQosNegoSwitch     :1;
    UCHAR ucPcrfNotifyQosUpdateFlag:1;
    UCHAR ucPccUpdataFlag          :1; /* AM 和pcrfc间的消息更新类型: 1 :session; 0: bearer*/
    UCHAR ucPccRollQos             :1;
    UCHAR ucPccEveTriFlag          :2; /* 用于表示是否有更新需要上报PCRFC ,1 表示需要上报*/

    UCHAR ucTftOperCode     :3;        /* tft操作码，对应6种类型*/
    UCHAR ucTempTftOperCode :3;        /* 缓存场景使用，第二次filter操作码*/
    UCHAR ucBufferOperCode  :2;        /* 记录缓存场景：C+U,U+U*/

    USHORT usPcrfGrpIndex;
    USHORT usFilterIDAllocation;       /* filter id分配位图, 从低到高0~15位，1表示已分配 */
    ULONG ulGtpv2Scene;
    USHORT usFirstFramedRouteIndex;
    USHORT usFramedRouteCount;

    ULONG ulSgsnAsn;                   /* ASN漫游计费,AM写CM用 */
    UCHAR ucAsnState;                  /* 当前PDP是否在等状态*/
    UCHAR ucCcSelectMode;
    UCHAR ucPrivateCause;                /* for perf at 2013.12.2，私有原因值，标识各种非协议规定的原因，性能统计用 */
    UCHAR ucApnLockDelUserFlag;        /* 表示是否lock enable deactive enable去活的用户*/

    GTP_COMMON_FLAGS_S stCommonFlags;  /* 1字节 */
    UCHAR ucChargingCharInMsg[2];      /* 用于存储SGSN携带的CC信元的值*/
    UCHAR ucUpdatePccFlag   :1;
    UCHAR ucPccFilterType   :1;        /* ADD by g00135725 at 2009-07-21 for PCC(AM):0:标示7层，1标示3，4层*/
    UCHAR ucSendDelSessReq  :1;
    UCHAR ucSendDelBearerReq:1;
    UCHAR ucSendDelBearerCmd:1;
    UCHAR ucRcvDelBearerReq :1;
    UCHAR ucPccResved       :1;        /* 已经使用 */
    UCHAR ucBearerLevelQosChanged :1;

    USHORT usSeqNo;
    USHORT usReqQoSLevel;

    ULONG ulResource;                  /* 资源位,ugw和GGSN使用的不同，考虑使用哪个? */
    ULONG ulSgwIfindex;                /* 用于保存组级接口的Sgw 侧的Ifindex */
    ULONG ulPgwIfindex;                /* 用于保存组级接口的Pgw or GGSN 侧的Ifindex */
    ULONG ulPdnConnectionId;           /* 用于记录缺省承载的ulCdrfChargingId */
    USHORT usNoConfigApnIndex;         /* SGW未配置APN的Index(1-3000)*/
    UCHAR aucAPNOI[6];                 /* 存放APN OI信息*/

    UCHAR ucPcrfLocalIndex;
    UCHAR ucBit1HandOverSucNotify:1;   /* 11.0 EE需求 标志ePDG和LTE之间的切换 pcc回复成功发送ACK，回复失败不用发送ACK */
    UCHAR ucGul4To3TimerFlag :1;       /*GUL4切3场景增加对专有承载的保护定时器，防止出现PDN下没有切换成功的承载CR-0000057833*/
    UCHAR ucoldImsflg        :1;
    UCHAR ucAfdnsFlag        :1;       /* anti-fraud-dns标识是否是开启DNS防欺诈功能的用户 */
    UCHAR ucMseOldUsrFlg    : 1; /* 用于多业务用户性能统计标记*/
    UCHAR ucCLPdnTypeFlag: 1;              /* C->C, L->C切换场景, PBU请求消息携带双栈, 协商后返回PBA消息为单栈,
                                               需要携带pdn-type-indication扩展, 使用该标记判断 */
    UCHAR ucOverloadFlag:1;            /* 11.0信令过载抑制特性，0:向SDU发送普通的删除表项消息，1:向SDU发送信令过载抑制消息 */

    UCHAR ucBitcommendFlag : 1;  /* 表示该激活的请求消息经过板间推荐*/
    USHORT usTempFilterOperIndic;      /* 缓存场景使用，记录第二次被操作的filter标识*/

    UCHAR ucMultiServiceFlg     :1;    /* 记录是否是Multi-Service用户 */
    UCHAR ucMultiContextFlg     :1;    /* 记录Multi-Service用户的上下文,0:service pdp,1 主pdp */
    UCHAR ucMultiUpdateFlg      :2;    /* 记录service PDP处于未激活态时收到更新请求 */
    UCHAR ucMultiAddressInherit :1;    /* 记录multiple-apn下的address-inherit属性值 */
    UCHAR ucRadiusServerFlag    :1;    /* 标识用户是否使用radius功能*/
    UCHAR ucChrDelDirect        :1;    /* CHR标识用户去活方向，默认为0，GGSN发起去活 1为SGSN发起去活*/
    UCHAR ucUGWAllocSeqNo       :1;    /* 标识是否是UGW主动发起的消息，此时SeqNo由UGW进行分配:1标识UGW分配SeqNo,0标识非UGW分配*/

    UCHAR ucMsisdnLen;                 /* 保存msisdn长度 */
    USHORT usServiceIndex;             /* 对于service PDP,保存当前激活的service-index; 对于default PDP,保存multiple-apn的index */

    ULONG ulDefaultPDPIndex;           /* 记录Default PDP上下文索引，该记录只对Multi-Service用户有效 */

    UCHAR ucMultiSerDelNum:4;          /* RAR更新Serivce List时后需要删除的S-PDP个数，最大不超过10 */
    UCHAR ucMultiSerCreateNum:4;       /* RAR更新Serivce List时后需要创建的S-PDP个数，最大不超过10 */

    UCHAR ucMultiSerPcrfUdpFlg:3;      /* RAR更新AM回PCRFC响应使用返回值 成功:0 失败:1 鉴权失败:2 */
    UCHAR ucMSRarDelSerPdpFlg:1;       /* RAR更新需要删除Service PDP置标志为1 */
    UCHAR ucMSRarUpdBakFlag:1;         /* RAR更新时需要通知IPN进行备份的标志 */
    UCHAR ucPccRollBackFlag:1;         /* PCRFC通知AM PCC回滚时，AM置该位为1，IPN通过此标志在备板做回滚操作，该字段在PCRFC给AM回更新响应和revoke消息时置位*/
    UCHAR ucBitCfFlag :1;              /* 1表示CF用户，0表示不是CF用户*/
    UCHAR ucDelNullflg:1;              /* 已使用 PCC用户通过BRC消息删除filter时，如果全部filterid都无法找到相应的filter时，UGW发起更新操作，不通知PCC  modify start by wangboyu for TFT异常处理 at 2012-01-31   */

    UCHAR ucVIPDelByLicense:1;         /* 由于license不足，VIP用户接入而导致的普通用户去活 */
    UCHAR ucOldVIPUserFlg:1;           /* 用于性能统计*/
    UCHAR ucVIPAccessPrioFlg:1;        /* 标识VIP用户是否优先接入 */
    UCHAR ucVIPUserFlg:1;
    UCHAR ucSmoothFailFlag:4;          /* 平滑失败后去活类型标识:0:正常用户 1:CM平滑失败 2: */

    UCHAR ucUserLevelServiceType;

    UCHAR szHomeZoneResultCode[6];     /* 用户的resultcode */
    UCHAR ucRspHZSameMsgNum;           /* 表示收到HZ模块相同的状态通知消息次数 */
    UCHAR ucBitSendDeacToSgsn:1;       /* 是否给SGSN发送去活请求标志 */
    UCHAR ucPccIndicate:4;             /* Pcc Indicate Num, IPN写，AM负责下发该字段给PF  by penghui for 9.0 2011-2-6 */
    UCHAR ucRandomNo:3;                /* 随机跟踪*/

    ULONG ulIndirectForwardPeerULDataIP;/* 上行间接转发对端数据IP */
    ULONG ulIndirectForwardPeerULTeidu; /* 上行间接转发对端上行数据隧道标识 */
    ULONG ulIndirectForwardLocULTeidu;  /* 上行间接转发本端为对端分配的数据隧道标识 */
    ULONG ulChrProcID;                  /* CHR上报时区分同一个终端在一次上线过程中的不同流程，仅在缺省承载进行累加*/
    ULONG ulTcpChkTimeStamp;
    ULONG ulNWSessionIndex;            /* NW-AGENT模块分配的索引，可以直接索引NW上下文 */

    T3GPP_SGSN_MCC_MNC_S stOldSgsnPlmn;/* 4字节 */
    USHORT usCFTemplateID;
    USHORT usCfProfileListId[MAX_CFPROFILES_FROM_ONE_GX_MESSAGE];  /*存放cf-profile id的数组*/

    UCHAR ucBitLocReportFlag:2;        /* MS INFO Change Reporting Action:0:Stop reporting,1:start report CGI/SAI,2:start reporting rai*/
    UCHAR ucBitMsChangeExtendFlag:1;   /* 消息中是否携带MS Info Change Reporting support indication扩展头*/
    UCHAR ucBitRaiTriggerFlag:1;       /* PCRF/AAA/OCS/CG是否下发rai trigger*/
    UCHAR ucBitUliTriggerFlag:1;       /* PCRF/AAA/OCS/CG是否下发ULI trigger*/
    UCHAR ucBitMsFlag:1;               /* 当前正在处理ms info change request消息，该消息和PCRF/CM交互时，如果失败或超时不去活用户*/
    UCHAR ucAAAQosFlag:1;              /* 1,AAA下发了有效的QosId，0，AAA没有下发QosId */
    UCHAR ucQchatFlag:1;               /* 是否为Qchat用户标志 */

    UCHAR ucPerfLicenseDownFlag:4;
    UCHAR ucPerfLicenseUpFlag:4;

    UCHAR ucbitLiRoamingChgFlag:1;
    UCHAR ucBitAreaCongTriggerFlag:1;
    UCHAR ucSupAreaCongestionRpt:1;    /* 小区拥塞上报*/
    UCHAR ucSupprotFPIFlag:1;          /* FPI属性标志*/
    UCHAR ucbitTerminalFlg:1;
    UCHAR ucAdcFlag           :1;      /* ADC用户属性*/
    UCHAR ucAdcRuleFlag       :1;      /* 是否有ADC规则*/
    UCHAR ucAdcChangeFlag       :1;    /* ADC是否更新*/

    UCHAR ucAreaCongTriggerFuncFlag:1; /* add by g00131462 for 小区拥塞 */
    UCHAR ucGgsnInitUpdateBit:7;

    UCHAR ucCfProfileListNum;          /* cf-profile的个数*/
    UCHAR uceQci;                      /* 用于保存PCRFC下发的扩展Qci,填充话单使用*/
    UCHAR ucAAAQoSId;                  /* COA：AAA下发的QosId */
    UCHAR ucAcctLinkCount;

    GTP_QOS_SUB_S stSubQos;            /* 保存最大的请求Qos */

    USHORT usIriTargetMap;
    USHORT usIdpTargetMap;

    UCHAR ucPcscfGrpoupIndex :4;       /* 分别表示使用的v4主，v4备，v6主，v6备group索引*/
    UCHAR ucUsedPcscf: 4;              /* 用来寻找ue使用的pcscf地址*/

    UCHAR ucSbrVogCHOFlag:3;             /* SBR/VOG内外置切换标记 1为外置 2为内置 3为切内 4为切外*/
    UCHAR bitHoldingTimeFlag :1;       /* holding time 和Session timeout去活标记，1:holding time 0:Session timeout */
    UCHAR btUIMSI            :1;       /* IMSI是否鉴权标记 */
    UCHAR ucoldnullMisdnFlag:1;
    UCHAR ucnullMisdnFlag:1;
    UCHAR ucSessionStopIndicationPF:1; /* 删除时最后一个承载的标志，给PF用*/
    UCHAR ucPcscfMainIpv4;             /* V4 组内使用的主pcscf 索引*/
    UCHAR ucPcscfMainIpv6;             /* V6 组内使用的主pcscf 索引*/
    UCHAR ucPcscfBkpIpv4;              /* V4 组内使用的备pcscf 索引*/
    UCHAR ucPcscfBkpIpv6;              /* V6 组内使用的备pcscf 索引*/

    UCHAR ucPcscfFaultV4   :1;         /* V4 pcscf是否fault标记位,用于判断是否向左侧发送消息*/
    UCHAR ucPcscfFaultV6   :1;         /* V6 pcscf是否fault标记位,用于判断是否向左侧发送消息*/
    UCHAR bit1MsuFlag:1;
    UCHAR bit1MSUFlagc:1;
    UCHAR ucPerfRole:3;                /* 用于标记进行性能统计角色的类型:V0/V1/SGW/PGW/SPGW*/
    UCHAR ucNotifyPcrfcRel:1;          /* 用于表示是否通知PCRFC释放资源(只适用于融合网关)*/

    UCHAR ucVogProfileChangeFlag:1;
    UCHAR ucMseRebuildFlag:1;      /*重建标记，重建时计数减一，收到MSD响应时计数再加一。
                                                        1表示已经发MSD发重建消息 但没有收到响应，SPU板的计数已减.
                                                        0表示重建成功，收到MSD的响应，或是激活成功。*/
    UCHAR ucMultiUpdFirstSucFlag:1;    /*PS11.0 PCC缓存重发特性记录PCC触发的更新如果因filter分为多条Update时记录第一条是否成功标记，用于重发区分是否发送第一条*/
    UCHAR ucReactivationReDelFlag:1;              /* 已使用，表示去活时需携带reactivation原因值*/
    UCHAR ucAccessGWType:4;              /* 用户接入网关的类型：0表示GUL，1表示SCCG*/
    UCHAR ucMseProfileListOper;
    UCHAR ucMsdLogicalSlotId;          /* MSD板的slot*/
    UCHAR ucMsdOSId;                   /* MSD板的OS*/
    UCHAR ucSGType;

    USHORT usMSProfilelistIndex;       /* 用于记录动态策略，如果此索引非法则判断为非MSD用户, 此标记由IPN修改，AM读。 AM负责修改bit1MsdFlag 标记*/
    UCHAR ucMsdSgId;                   /* MSD板的SG*/
    UCHAR ucLocalLocationReportFlag;
    UCHAR ucBriTrigger;                /* y00170683 PMIP开发 */
    UCHAR ucBri3GppErrCode;

    UCHAR ucMsdTCPOptiFlag           :1;
    UCHAR ucMseDataTrcUpFlag         :1;
    UCHAR ucMseDataTrcDownFlag       :1;
    UCHAR ucMseDropEmsFlag           :1;
    UCHAR ucSGSNS4Flag               :1;
    UCHAR ucBitPmipLapFail           :1;
    UCHAR ucBitPmipDhcpFsmFlg        :1;/* PMIP 延迟分配申请地址是否已经转状态机 */
    UCHAR ucCrtByServOrForbiddentoCrt:1;/* modified by wangboyu at 2013-03-14 for DTS2013021600701 CR20130304070
                                            此标记在二次激活中表示该承载是由业务触发的。在一次激活表示该用户被惩罚，
                                            下一次的业务触发二次激活直接返回失败。仅用于GGSN。此CR经SE确认，
                                            在10.0后续版本中因为IPN业务调整可以解决此问题而不需要继承。*/

    UCHAR ucbit1SuspendFlag :1;        /* suspend 挂起状态机标记*/
    UCHAR ucbit1VoiceFlag :1;          /* Delete bearer cmd中 Voice bearer标志*/
    UCHAR ucPostLapRelease    : 2;

    UCHAR ucBit4S6bSrvSelectType:3;    /*add by jiahong 00148456 at 20131016 for 10.1 s6b_dra .s6b使用字段取值为S6B_SERVER_SELECT_TYPE_E */

    UCHAR ucbit1VogEmsFlag:1;
    GTP_PMIPV6PEERADDR_BSSID stPmipV6addrOrBSSID;     /* 16字节 */
    T3GPP_SGSN_MCC_MNC_S stPmipMnIdMccMnc;/* 4字节 */
    ULONG ulS6bSessionIdTimeStamp;
    T3GPP_IMSI_MCC_MNC_S stPmipApnOi;  /* 3字节 */
    UCHAR ucIpType :3;                /* ipv4:0, ipv6:1*/
    UCHAR ucbit1RecvSuspendAckSuccFlag:1;                  /*sgw收到suspend消息后，给pgw透传。当收到成功suspend ack时，此标示置位为VOS_TRUE*/
    UCHAR ucOldSGSNS4Flag :1;          /* 保存原有的s4SGSN标示 */
    UCHAR ucOldSupAreaCongestionRpt :1; /* 保留原有的小区拥塞的标示 */
    UCHAR ucOldSupprotFPIFlag :1;     /* 保留原有FPI的标示 */
    UCHAR ucBitSgwHoTauDelFlag :1;    /*CR-0000067599 VF SGW上SGW切换用户去活离线话单关闭原因值需求*/
}SDB_GSPU_CONTEXT_S, SIG_GGSN_PDP_CONTEXT_S;

//
//socket path define
//

/* socket 路径结构 */
typedef struct tagRM_SOCKET_PATH_S
{
    ULONG  ulPeerAddr;                    /* 对端地址 */
    ULONG  ulLocalAddr;                /* 本端地址 */
    USHORT usPeerPort;                    /* 对端端口 */
    USHORT usLocalPort;                /* 本端端口 */
    ULONG  ulVrfIndex;                //VPN索引
    ULONG  ulGroupifIndex;            //组级ifindex
    ULONG  ulLocalSubindex;           /*本端地址接口索引*/
    /* add start by wenxing 00194498 on 2014-01-06 for DTS2013120202505
        proxy ggsn/pgw 直接回复失败的时候的跟踪方向 proxy ggsn(pgw)->sgw
     */
    UCHAR ucProxyCode;
    UCHAR ucCommendFlag; /*板间推荐过来的请求消息，回响应消息是需要使用原接入的逻辑接口地址*/
    USHORT usApnIndex;   /* apn 索引，用于接口跟踪的消息上报 */
    UCHAR ucAliaApnFlag ;   /* 表示请求的是别名APN */
    UCHAR ucRev[3];
}VOS_PACKED RM_SOCKET_PATH_S;

/* BEGIN: Added for PN: 全网跟踪  by LiHairong, 2010/4/8 */
#pragma pack (1)
typedef struct
{
    /* 传入参数 */
    UCHAR *pucTrcMsg;           /* 消息体 */
    UCHAR  ucMsgType;           /* 消息类型 */
    UCHAR  ucUgwRole;           /* 网元角色 */
    USHORT usMsgLen;            /* 消息长度 */
    ULONG  ulEmsTrcDir;         /* 全网跟踪消息方向 接收 1; 发送 0 */
    ULONG  ulUsrTrcDir;         /* 用户跟踪消息方向 0x000,0x100,0x200,0x300,0x400... */
    /* 传出参数 */
    USHORT usTraceId;
    UCHAR  ucSgwTrcFlg;
    UCHAR  ucPgwTrcFlg;
    UCHAR  ucSgwTrcIf;
    UCHAR  ucPgwTrcIf;
    UCHAR  ucProType;
    UCHAR  ucMsgIntf;
    UCHAR  ucMsgSndFlg;
    UCHAR  ucReserved[3];
}VOS_PACKED S_OM_EMS_TRC_PARA;

typedef struct tagINADDR
{
    VOS_UINT32 s_ulAddr;
}INADDR_S;

typedef struct tagSOCKADDRIN
{
    UCHAR   sin_chLen;
    UCHAR   sin_chFamily;
    USHORT  sin_usPort;
    struct  tagINADDR sin_stAddr;
    char    sin_chZero_a[8];
}SOCKADDRIN_S;

typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;

typedef struct tagSOCKADDR_IN6 {
    UCHAR       ucSin6_len;         /* length of this struct(sa_family_t)*/
    UCHAR       ucSin6_family;      /* AF_INET6 (sa_family_t) */
    USHORT      usSin6_port;        /* Transport layer port # (in_port_t)*/
    ULONG       ulSin6_flowinfo;    /* IP6 flow information */
    IN6ADDR_S   stSin6_addr;    /* IP6 address */
    ULONG       ulSin6_scope_id;    /* scope zone index */
}SOCKADDR_IN6_S;

typedef struct tagPacketInfo
{
    ULONG ulVpnId;      /*VPN ID为0时认为申请一个全局接口 */
    ULONG ulFamily;      /*IP地址类型 AF_INET,AF_INET6 */
    union{
        SOCKADDRIN_S stAddrSrc;
        SOCKADDR_IN6_S stAddr6Src;
    }uaddrSrc;/* 本地IP地址、端口号 */
    union{
        SOCKADDRIN_S stAddrDst;
        SOCKADDR_IN6_S stAddr6Dst;
    }uaddrDst;/* 对端IP地址、端口号 */
    CHAR *pData;        /* 指向Mbuf中用户数据的指针 */
    ULONG ulDataLen;
    UCHAR ucControlCheckSum;
    UCHAR aucResv[3];
} UDPS_PACKET_INFO_S;

/* 自旋锁/读写锁类型结构定义 */
typedef struct tagpgp_spinlock
{
    volatile VOS_UINT32 uiSlock; /* 自旋锁变量 */
    VOS_UINT32 uiUnlockSGId : 6;
    VOS_UINT32 uiReserve    : 26;
    VOS_UINT64 ulTick;
}PGP_SPINLOCK_S;

/* 自旋锁类型定义宏 */
#define PGP_SPINLOCK_ID   PGP_SPINLOCK_S

typedef struct tagDHCP_SERVER_STATUS_S
{
    PGP_SPINLOCK_ID stSpinLockId;

    UCHAR   ucPrimarySrvStatus:3;
    UCHAR   ucPrimarySrvTest:1;
    UCHAR   ucSecondarySrvStatus:3;
    UCHAR   ucSecondarySrvTest:1;
    UCHAR   ucPrimSrvTimerStatus;       /* 主用服务器状态扫描定时器状态 */
    UCHAR   ucPrimTimeoutNum;           /* 主服务器闪断告警计数 */
    UCHAR   ucSecTimeoutNum;            /* 备服务器闪断告警计数 */

    USHORT  usPrimTryTimeInterval;      /* 主服务器变为Try的剩余时间 */
    USHORT  usSecTryTimeInterval;       /* 备服务器变为Try的剩余时间 */

    UCHAR   ucPrimRequestTimeout;
    UCHAR   ucSecRequestTimeout;
    UCHAR   ucPrimaryAlarmFlag:1;       /* 主服务器已经发送过链路断告警的标志 */
    UCHAR   ucSecondaryAlarmFlag:1;     /* 已经发送过链路断告警的标志 */
    UCHAR   ucResBit:6;               /* 保留字段 */
    UCHAR   ucReserve;            /* 保留字段 */
}DHCP_SERVER_STATUS_S;


typedef enum UGW_NET_ELEMENT_ROLE_E
{
    E_NET_ELEMENT_ROLE_GGSN = 0,
    E_NET_ELEMENT_ROLE_PGW,
    E_NET_ELEMENT_ROLE_SGW,
    E_NET_ELEMENT_ROLE_PGW_AND_SGW,
    E_NET_ELEMENT_ROLE_HSGW,
    E_NET_ELEMENT_ROLE_PDSN,
    E_NET_ELEMENT_ROLE_BUTT
}UGW_NET_ELEMENT_ROLE_E;

#define M_LAP_DHCP_TBL_MAX_TUPLE_NUM       1000    /* CDB表的最大记录数 */
#define M_LAP_DHCP_TBL_IDX_NUM                1    /* CDB表的索引个数 */
#define M_LAP_DHCP_TBL_GROUP_IDX_ID           0    /*  索引编号 */
typedef enum
{
    M_LAP_DHCP_TBL_PRIMARY_SERVER_IP_FLD_ID    ,     /* CDB表的字段01编号 */
    M_LAP_DHCP_TBL_SECONDARY_SERVER_IP_FLD_ID  ,     /* CDB表的字段02编号 */
    M_LAP_DHCP_TBL_VPN_INDEX_FLD_ID            ,     /* CDB表的字段03编号 */
    M_LAP_DHCP_TBL_SERVER_GROUP_NAME_FLD_ID    ,     /* CDB表的字段04编号 */
    M_LAP_DHCP_TBL_LEASETIME_FLD_ID            ,     /* CDB表的字段05编号 */
    M_LAP_DHCP_TBL_SERVER_GROUP_INDEX_FLD_ID   ,     /* CDB表的字段06编号 */
    M_LAP_DHCP_TBL_VPN_NAME_FLD_ID             ,     /* CDB表的字段07编号 */
    M_LAP_DHCP_TBL_IS_DHCPV6_FLD_ID            ,     /* CDB表的字段08编号 */
    M_LAP_DHCP_TBL_RETRANSMIT_NUM_FLD_ID       ,     /* CDB表的字段09编号 */
    M_LAP_DHCP_TBL_RETRANSMIT_TIMEOUT_FLD_ID   ,     /* CDB表的字段10编号 */
    M_LAP_DHCP_TBL_RESERVE_FLD_ID              ,     /* CDB表的字段11编号 */
    M_LAP_DHCP_TBL_BUTT
}E_LAP_DHCP_TBL_FLD;


/*GTPC的状态定义，注意同步修改g_ucStateMachineDescrip*/

typedef enum
{
    USM_IDLE = 0,                     /*空闲状态*/
    USM_RADIUS_NEGO,            /*RADIUS协商状态*/
    USM_IP_APPLY,                   /*申请地址的等待状态*/
    USM_PCRFC_NEGO,
    USM_SM_NEGO,                    /* SM协商的等待状态*/
    USM_ASN_NEGO,
    USM_CM_NEGO,                   /*CM协商的等待状态*/
    USM_ACTIVE,                         /*激活态*/
    USM_PCRFC_UPDATE,
    USM_ASN_UPDATE,
    USM_CM_UPDATE,                  /*10*/       /*更新等待CM*/
    USM_PCRFC_DELETE,                 /*PCRFC删除的等待状态*/
    USM_CM_DELETE,                   /*CM删除的等待状态*/
    USM_WAIT_SGSN_DELETE,
    USM_WAIT_SGSN_UPDATE,
    USM_L2TP_IPCP_NEGO,             /*15*/
    USM_WAIT_PCRF_RAR_UPDATE,        /*Pcrfc发起Rar更新，等待更新成功状态*/

    USM_DHCP_IP_APPLY,
    USM_WAIT_SGSN_INIT_RSP, /*等待SGSN发送Initiate PDP Activation Response消息*/
    USM_WAIT_NW_CREATE,                   /*等待SGSN发起网络侧的二次激活*/
    USM_END,
} E_GTPC_STATE_MACHINE_TYPE;

/* 一级状态定义 */
typedef enum tagAM_USM_L1_STATE_E
{
    E_AM_USM_L1_STATE_INIT,             /*空闲状态*/
    E_AM_USM_L1_STATE_CREATE,           /*创建状态*/
    E_AM_USM_L1_STATE_ACTIVE,           /*激活状态*/
    E_AM_USM_L1_STATE_UPDATE,           /*更新状态*/
    E_AM_USM_L1_STATE_DELETE,           /*删除状态*/

    E_AM_USM_L1_STATE_BUTT              /*无效状态*/
} AM_USM_L1_STATE_E;

/* 二级状态定义，注意以5个为一组，方便计数 */
typedef enum tagAM_USM_L2_STATE_E
{
    E_AM_USM_L2_STATE_INIT,             /*0 初始状态*/

    E_AM_USM_L2_STATE_AUTH,             /*1 认证等待状态*/
    E_AM_USM_L2_STATE_L2TP,             /*2 L2TP隧道建立等待状态*/
    E_AM_USM_L2_STATE_LAP,              /*3 lap分配地址待状态*/
    E_AM_USM_L2_STATE_PCC,              /*4 PCC等待状态*/
    E_AM_USM_L2_STATE_S6B,              /*5 S6B等待状态*/
    E_AM_USM_L2_STATE_UGW,              /*6 等待PGW或SGW回应状态*/

    E_AM_USM_L2_STATE_SM,               /*7 SM等待状态*/
    E_AM_USM_L2_STATE_ASN,              /*8 获取ASN 漫游计费属性状态*/
    E_AM_USM_L2_STATE_CM,               /*9 CM等待状态*/

    E_AM_USM_L2_STATE_BUTT              /*10 无效状态*/
} AM_USM_L2_STATE_E;

/* AM分配表ID段:300 */
#define CDB_AM_MIN_ID 50                        //50
#define CDB_AM_MAX_ID CDB_AM_MIN_ID + 300       //350

/*************************1.所有产品形态都使用的,表ID范围是0-10*************************/
typedef enum enE_CDB_AM_GLOBAL_TBL
{
    M_CHR_FILTER_TBL_ID = CDB_AM_MIN_ID,
    M_AM_LICENSE_ALARM_TBL_ID,
    M_SC_USERTRACE_TBL_ID,
    M_LAP_IPV6_TBL_ID,
    M_LAP_POOL_TBL_ID,
    M_LAP_SECTION_TBL_ID,
    M_LAP_DOMAIN_POOL_TBL_ID,
    M_LAP_CONFIGURATION_TBL_ID,
    M_AM_SOFTPARA_TBL_ID,
    M_GM_IPSQM_SHAPING_TBL_ID,
    M_GM_IPSQM_DYNAMIC_INTER_TBL_ID,

    CDB_AM_GLOBAL_END_TBl_ID,        //61
}E_CDB_AM_GLOBAL_TBL;

/***************2.GUL与PDSN产品形态使用的表,表ID必须从CDB_AM_ALL_END_TBl_ID+1开始***************/
typedef enum enE_CDB_AM_MULTI_INSTANCE_TBL
{
    M_OS_APN_DOMAINSEPARATOR_TBL_ID = CDB_AM_GLOBAL_END_TBl_ID + 1,
    M_OS_PPPCFG_TBL_ID,
    M_OS_L2TP_GROUP_TBL_ID,
    M_OS_L2TP_DEFAULT_TBL_ID,
    M_LI_TARGET_TBL_ID,
    M_LI_STANDARD_TYPE_TBL_ID,
    M_LI_DFCFG_TBL_ID,
    M_LI_GLOBAL_CFG_TBL_ID,
    M_LI_IFNETCFG_TBL_ID,
    M_LI_ADMF_TBL_ID,
    M_LI_DF_TBL_ID,
    M_LI_CHN_TIMER_TBL_ID,
    M_LI_CHN_AUTHPARA_TBL_ID,
    M_SC_APN_COMMOM_TBL_ID,
    CDB_AM_GUL_PDSN_END_TBl_ID,   //75
}E_CDB_AM_MULTI_INSTANCE_TBL;

/***************3.GUL产品形态使用的表,表ID必须从CDB_AM_GUL_PDSN_END_TBl_ID+1开始 共125个***************/
typedef enum enE_CDB_AM_GUL_TBL
{
    CDB_APN_NBNS_TBL_ID = CDB_AM_GUL_PDSN_END_TBl_ID + 1, //74
    M_AM_BATCH_DEACTIVE_RATE_TBL_ID,//75
    M_AM_GOM_HOMEZONE_CONNECTION_TBL_ID,//76
    M_AM_GOM_HOMEZONE_GROUP_TBL_ID,//77
    M_AM_GOM_HOMEZONE_SERVER_TBL_ID,//78
    M_AM_IMSIINSTANCE_BUILDING_TBL_ID,//79
    M_AM_INTELLIGENT_SELECT_DEFAULT_TBL_ID,//80

    M_AM_INTELLIGENT_SELECT_TBL_ID,//81
    M_AM_LOCAL_LOCATION_TRIGGER_ID,
    M_AM_PCRFC_APN_IMS_SWITCH_CFG_TBL_ID,
    M_AM_PCRFC_APN_IMSSIGFILTER_CFG_TBL_ID,
    M_AM_PCRFC_P_CSCF_GROUP_TBL_ID,

    M_AM_PCRFC_PCC_IMS_SWITCH_CFG_TBL_ID,//86
    M_AM_PCRFC_PCC_IMSSIGFILTER_CFG_TBL_ID,
    M_AM_PCRFC_PCSCFGROUP_BIND_APN_TBL_ID,
    M_AM_PCRFC_PCSCFGROUP_BIND_PCC_TBL_ID,
    M_AM_SGSN_ACCESS_LIST_SWITCH_TBL_ID,

    M_AM_SGSN_ACCESS_LIST_TBL_ID,//91
    M_AM_SGSN_ACCESS_LIST_TYPE_TBL_ID,
    M_AM_SGSN_SCI_CTRL_TBL_ID,
    M_APN_UE_HEART_BEAT_INFO_TBL_ID,
    M_EPRPDYN_ATTR_TBL_ID,

    M_GM_IPPM_ALARM_THRESHOLD_TBL_ID,//96
    M_GM_IPPM_CONFIG_TBL_ID,
    M_GM_IPPM_GLOBAL_TBL_ID,
    M_GM_IPPM_PERF_TBL_ID,
    M_GM_IPSQM_LOCK_PEU_TBL_ID,

    M_GM_IPSQM_PATHSHAPPING_TBL_ID, //101
    M_GM_IPSQM_PORTSHAPPING_TBL_ID,
    M_GTPC_ASN_CONFIGURATION_TBL_ID,
    M_GTPC_ASN_FUNCTION_TBL_ID,
    M_HZ_SOURCEID_TBL_ID,

    M_IP_SPOOFING_CFG_TBL_ID,//106
    M_LAP_BLACK_LIST_TBL_ID,
    M_LAP_DHCP_TBL_ID,
    M_LI_X1AUTH_TBL_ID,
    M_MBMS_CTEID_TBL_ID,

    M_NW_ENABLERGROUP_TBL_ID, //111
    M_NW_ENABLERINFO_TBL_ID,
    M_NW_HSFUNCTION_TBL_ID,
    M_NW_NWCLIENTIP_TBL_ID,
    M_NW_NWFUNCTION_TBL_ID,

    M_NW_NWSAMPLING_TBL_ID,//116
    M_NW_RETRYINTERVAL_TBL_ID,
    M_OS_APN_COMUSER_TBL_ID,
    M_OS_L2TP_GROUP_INTERFACE_TBL_ID,
    M_PCRFC_DEFAULT_P_CSCF_GROUP_TBL_ID,

    M_RCS_APN_DNS_TBL_ID,//121
    M_SC_ACCESS_CTRL_DEGREE_TBL_ID,
    M_SC_APN_ABNORMAL_CTRL_TBL_ID,
    M_SC_APN_CLIENT_IP_TBL_ID,
    M_SC_APN_COMMON_TBL_DEFAULT_FLD_ID,

    M_SC_APN_CONTROL_TBL_ID,//126
    M_SC_APN_INTERFACE_TBL_ID,
    M_SC_APN_NAS_IP_TBL_ID,
    M_SC_APN_PERF_TBL_ID,
    M_SC_APN_PRIORITY_CONTROL_TBL_ID,

    M_SC_APN_ROUTE_TBL_ID,//131
    M_SC_APNQOS_CFG_TBL_ID,
    M_SC_APNQOS_MAPINFO_TBL_ID,
    M_SC_ARP_CFG_TBL_ID,
    M_SC_ARP_PRI_MAPPING_TBL_ID,

    M_SC_COMMEND_SOLT_CPU_TBL_ID,//136
    M_SC_DEFAULT_SGSN_NODE_TBL_ID,
    M_SC_DHCPS_EXPIRED_TBL_ID,
    M_SC_DHCPS_FUNCTION_TBL_ID,
    M_SC_DHCPS_OPTION_TBL_ID,

    M_SC_DIFFSRV_FUNCTION_TBL_ID,//141
    M_SC_DIFFSVR_CFG_BW_THRESHOLD_TBL_ID,
    M_SC_DIFFSVR_CFG_PDP_THRESHOLD_TBL_ID,
    M_SC_GATEWAY_PROXY_TBL_ID,
    M_SC_GTP_PROTOCOL_TBL_ID,

    M_SC_HOMEGATEWAY_TBL_ID,//146
    M_SC_HOMEGATEWAYGROUP_TBL_ID,
    M_SC_HOMEIMSIMSISDNGROUP_TBL_ID,
    M_SC_LOCATION_REPORTING_TIMER_CTRL_TBL_ID,
    M_SC_MBMS_BMSC_CFG_TBL_ID,

    M_SC_MBMS_BMSCGROUP_CFG_TBL_ID,//151
    M_SC_MBMS_LOCAL_CFG_TBL_ID,
    M_SC_MBMS_PARA_CFG_TBL_ID,
    M_SC_MCC_MNC_TBL_ID,
    M_SC_MCC_MNCLENGTH_TBL_ID,

    M_SC_PATH_ALARM_THRESHOLD_TBL_ID,//156
    M_SC_PLMN_PRIORITY_CFG_TBL_ID,
    M_SC_PMIP_TBL_ID,
    M_SC_PUBLICAPN_TBL_ID,
    M_SC_QOS_CAR_TBL_ID,

    M_SC_QOS_CFG_TBL_ID,//161
    M_SC_QOS_FUNCTION_TBL_ID,
    M_SC_QOS_MAPINFO_TBL_ID,
    M_SC_QOS_PROFILE_TBL_ID,
    M_SC_QOS_REMARK_TBL_ID,

    M_SC_QOS_SHAPE_TBL_ID,//166
    M_SC_QOS_VER_TRANS_RULE_TBL_ID,
    M_SC_RAT_PRIORITY_CFG_TBL_ID,
    M_SC_S6B_AAA_HOST_INFO_TBL_ID,
    M_SC_S6B_DIAMSVR_GROUP_TBL_ID,

    M_SC_S6B_LOCALINFO_TBL_ID, //171
    M_SC_SERVER_GROUP_ACCEPT_ATTR_TBL_ID,
    M_SC_SERVER_GROUP_AUTH_3GPP_VSA_TBL_ID,
    M_SC_SERVER_GROUP_AUTH_ATTR_TBL_ID,
    M_SC_SERVER_GROUP_TBL_ID,

    M_SC_SGSN_PLMN_NODE_TBL_ID,//176
    M_SC_SGSN_RAT_NODE_TBL_ID,
    M_SC_SUB_QOS_TBL_ID,
    M_SC_TRAFFIC_CLASS_TBL_ID,
    M_SC_UGW_APNQOS_MAPINFO_TBL_ID,

    M_SC_UGW_GLOBALQOS_MAPINFO_TBL_ID,//181
    M_SC_UGW_QOS_DEFAULTVALUE_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_ARPQCIMAPPING_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_EXTENDQCI_TBL_ID,
    M_SC_UGW_QOS_GLOBAL_EXTQCIMAPPING_TBL_ID,

    M_SC_UGW_QOS_GLOBAL_QCILEVEL_TBL_ID,//186
    M_SC_UGW_QOS_GLOBAL_QCIPRIORITY_TBL_ID,
    M_SC_UGW_QOS_MAP_QCI2TRAFFICCLASS_TBL_ID,
    M_SC_UP_DOWN_BAND_RATE_TBL_ID,
    M_SC_USERRUNNING_TBL_ID,

    M_SC_VIP_MANAGE_FUNCTION_TBL_ID,//191
    M_SC_VIP_QOS_MAPINFO_TBL_ID,
    M_SC_VIP_RESERVE_BANDWIDTH_TBL_ID,
    M_VIRTUALAPN_DFCFG_TBL_ID,
    M_SC_S6B_GROUP_S6B_ATTR_TBL_ID,

    M_SC_S6B_PGWHOSTNAME_TBL_ID,   //196
    M_SC_PATH_PMIPV6_HEARTBEAT_TBL_ID,
    M_SC_UGW_TO2_TBL_ID,
    M_AM_UDP_CHECKSUM_TBL_ID,
    M_SC_EPC_GW_TBL_ID,

    M_LI_TARGET_FOR_SPUF1_TBL_ID,//201
    M_LI_TARGET_FOR_SPUF_TBL_ID,
    M_PATH_ECHO_LIST_SWITCH_TBL_ID,//203
    M_PATH_ECHO_LIST_TYPE_TBL_ID,
    M_PATH_ECHO_LIST_IP_TBL_ID,

    M_OS_L2TP_DEFAULT_ATTRIBUTE_TBL_ID,
    M_AM_UGW_DDN_FLOW_CONTROL_TBL_ID,
    M_SC_VIP_SWITCH_FUNCTION_TBL_ID,

    /* Added start by jiexianzhu at 2013.12.16 for 本地映射 VLRID/GT */
    M_SC_TRANSPARENT_TBL_ID,
    M_SC_PLMN_TRANSPARENT_TBL_ID,
    M_SC_DEFAULT_TRANSPARENT_TBL_ID,
    /* Added end by jiexianzhu at 2013.12.16 for 本地映射 VLRID/GT */
    M_SC_SDU_OVERLOAD_CTRL_TBL_ID,

    /* Added start by p00114481 at 2014-01-20 UGW9811V900R011C00 for GGSN/PGW Proxy特性 */
    M_SC_HOMEGROUPBINDAPN_TBL_ID,  /*211*/
    /* Added end by p00114481 at 2014-01-20 UGW9811V900R011C00 for GGSN/PGW Proxy特性 */

    M_MSG_CON_RESEND_SW_FUNCTION_TBL_ID,
    M_SC_ACCESS_REACTIVATION_REQ_DEL_TBL_ID,
    /*add by g00135725 20140215 for 管控需求*/
    M_SC_LACGROUP_TBL_ID,  /*213*/
    M_SC_TACGROUP_TBL_ID,  /*214*/
    M_SC_LACTACRAC_SECTION_TBL_ID,    /*215*/
    M_SC_RACGROUP_TBL_ID,  /*216*/
    M_SC_SPECIFICAPNVALUE_TBL_ID, /* 217 */

    /*add by g00135725 20140215 for 管控需求*/
    M_SC_CPU_UPDATARATE_TBL_ID,
    M_SC_ENGIN_REACTIVATION_REQ_DEL_TBL_ID,
    CDB_AM_GUL_END_TBL_ID = CDB_AM_MAX_ID,
}E_CDB_AM_GUL_TBL;

#define PMBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )
#define PMBUF_GET_DATA_BLOCK_NUMBER(pstMBufM) ( (pstMBufM)->ulDataBlockNumber )

typedef struct tagMBUF_USERTAGDATA_S
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
} MBUF_USERTAGDATA_S;

#define PMBUF_S_RES_SIZE 4

typedef struct tagMBUF_DataBlockDescriptor
{
    ULONG ulDataLength;         /* 数据块中数据的长度，取值范围[0, ulDataBlockLength]*/
    UCHAR * pucData;            /* 数据块中数据的起始地址, [pucDataBlock + 512, pucDataBlock + ulDataBlockLength]*/
    ULONG ulDataBlockLength;    /* 数据块的总长度,*/
    UCHAR * pucDataBlock;       /* 数据块的起始地址， NULL表示无效，其他表示有效 */
    ULONG ulType;               /* MBUF_TYPE_XXX */
    struct tagMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/* 下一个数据块描述符， Always NULL*/
}MBUF_DATABLOCKDESCRIPTOR_S,SM_MBUF_DATABLOCKDESCRIPTOR_S;    /* 数据块描述符数据结构 */

typedef struct tagMBuf
{
    struct tagMBuf * pstNextMBuf;                       /* 下一个mbuf， NULL表示无效，其他表示有效 */
    ULONG ulTotalDataLength;                            /* mbuf 中数据的总长度，同一个MBUF中的所有数据的长度和 */
    MBUF_DATABLOCKDESCRIPTOR_S stDataBlockDescriptor;   /* Mbuf 数据描述信息 */
    ULONG ulDataBlockNumber;                            /* mbuf 中数据块的个数 */
    MBUF_USERTAGDATA_S stUserTagData;                   /* Mbuf 控制信息 */
    ULONG ulResv[PMBUF_S_RES_SIZE];
    ULONG ulMagicWord;
}MBUF_S, PMBUF_S, SM_MBUF_S, TP_PMBUF_S;  /* mbuf的头标签数据结构 */

typedef struct tagPTM_COMPONENT_INFO
{
    VOS_UINT64 ullSelfCsi;      /* 本组件CSI */
    VOS_UINT64 ullSelfSgId;     /* 本组件所在SGID */
    VOS_UINT32 ulSelfCmpIdx;    /* OS内同类型组件索引 */
    VOS_UINT32 ulSelfCmpIdxInSG;/* SG内同类型组件索引 */
    VOS_UINT32 ulHandle;        /* HANDLE，用于调测 */
    USHORT usOsID;               /* 注意:不一定所有模块都初始化了 */
    USHORT usReserve990;
}PTM_COMPONENT_INFO_S;

/** SPU单板硬件类型定义 */
typedef enum tagCRM_SPU_BOARD_TYPE_ENUM
{
    CRM_BOARD_TYPE_UNKNOWN = 0,  /**< 未获取单板扩展类型，为未知类型 */
    CRM_BOARD_TYPE_SPUD,         /**< SPUD板（包含带TCAM扣卡） */
    CRM_BOARD_TYPE_SPUE,         /**< SPUE板 */
    /* Added start by s00171233 at 2012-01-06 PGPV200R005 for IPPM&IPSQM特性 */
    CRM_BOARD_TYPE_PEU,          /**< PEU板 */
    /* Added end by s00171233 at 2012-01-06 PGPV200R005 for IPPM&IPSQM特性 */
    /* Added start by jiaguochen 00178577 at 2012-03-22 PGPV2R6 for SPU-Group支持SPUF单板 */
    CRM_BOARD_TYPE_SPUF,
    /* Added end by jiaguochen 00178577 at 2012-03-22 PGPV2R6 for SPU-Group支持SPUF单板 */
    /* Added start by fenglin 00221566 at 2012-09-03 PGPV2R6C00 for CRM MSU  特性 */
    CRM_BOARD_TYPE_MSU,          /**< MSU板 */
    /* Added end by fenglin 00221566 at 2012-09-03 PGPV2R6C00 for CRM MSU  特性 */
    CRM_BOARD_TYPE_SPUF1,/* Added by gaohongfeng 00221579 at 2013-03-28 PGPV2R6C01 for 设备管理整改 */
    CRM_BOARD_TYPE_MSUF1,/* Added by gaohongfeng 00221579 at 2013-03-28 PGPV2R6C01 for 设备管理整改 */
    CRM_BOARD_TYPE_MAX,           /**< 无效硬件类型 */
}  CRM_SPU_BOARD_TYPE_ENUM ;

#define M_CDB_MAX_FIELD_LENGTH   (256 * 2)

typedef struct
{
    VOS_UINT8  ucOper;
    VOS_UINT32 udwFieldId;
    VOS_INT8   aValue[M_CDB_MAX_FIELD_LENGTH];
} S_CFG_CDB_CONDITION;

/* C00119457: DATE_T和TIME_T是基础类型，很难解除这种依赖，所以暂时保持现状 */
typedef struct
{
    ULONG  ulTick;     /* 上报发生的TICK数 */
    DATE_T stDate;
    TIME_T stTime;
}VOS_PACKED S_FAM_BAM_TRC_TIME_DATA;

#ifndef VOS_TIMER_LOOP
#define VOS_TIMER_LOOP 0x1
#endif

#define M_CFG_CDB_EQUAL             0


/* SDB返回码 */
typedef enum tagSDB_RETURNCODE_E
{
    SDB_SUCCESS              = 0,                     /* 成功返回 */
    SDB_INVALID_INPUT        = 1,                     /* 输入非法 */
    SDB_RECORD_NOT_EXIST     = 2,                     /* 未查到相应记录 */
    SDB_RECORD_EXIST         = 3,                     /*查询记录已经存在 */
    SDB_TABLE_FULL           = 4,                     /* 表已满(无记录可分配) */
    SDB_INIT_FAILURE         = 5,                     /* 初始化失败 */
    SDB_INCONSISTENT         = 6,                     /* 比较不一致 */
    SDB_FIND_IDLE_RECORD     = 7,                     /* 记录空闲 */
    SDB_INVALID_MSG          = 8,                     /* 非法消息 */
    SDB_EMPTY_HASH_CHAIN     = 9,                     /* 空哈稀冲突链 */
    SDB_SYSTEM_FAILURE       = 10,                     /* SDB模块其它错误 */
    SDB_CONTINUED_TO_SEARCH   = 11,
    NO_LICENSE =12 ,
    SDB_APN_USERCONTROL 	 = 13,					   /* APN用户数控制未通过*/
    SDB_APN_BANDCONTROL 	 = 14,					   /* APN带宽限制未通过 */
    SDB_TRAFFIC_CLASS_BANDCONTROL 	 = 15,			   /* Traffic Class带宽限制未通过 */
    SDB_APN_SPU_BANDCONTROL 	 = 16,			          /* 单板带宽限制未通过 */
    SDB_IP_CONFLICT            =  17,                   /*IP地址冲突*/
    SDB_DIFFSRV_REACH_APN_PDPNUM_TC_REJTHRD = 20,
    SDB_DIFFSRV_REACH_APN_PDPNUM_GENERAL_REJTHRD = 21,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_TC_REJTHRD = 22,
    SDB_DIFFSRV_REACH_GLOB_PDPNUM_GENERAL_REJTHRD =  23 ,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_TC_REJTHRD = 24,
    SDB_DIFFSRV_REACH_APN_BANDWIDTH_GENERAL_REJTHRD = 25,
    SDB_IMS_USER_NO_LICENSE   = 40,
    SDB_WHOLE_THROUTPUT_NO_LICENSE = 41,
    SDB_DIFFSRV_REACH_REJECT_THRESHOLD  =  100,
    SDB_DHCP_PARA_ERROR = 0xFF + 1, /* DHCP返回参数错误*/
    SDB_DHCP_POOL_ERROR = 0xFF + 2,     /* DHCP返回地址池错误*/
    SDB_DHCP_NO_IP_AVAILABLE = 0xFF + 3, /*无可用地址分配*/
    SDB_DMT_NO_RECORD        = 28101,                 /* DMT查询记录不存在 */
    SDB_DMT_INVALID_INPUT    = 28102,                 /* DMT查询输入参数无效 */
    SDB_FAILURE,
    SDB_NOT_ALLOW_CREATE_RANDOM_SDB,
    SDB_RETURNCODE_BUTT      = 0xffffffff             /* 结束标志 */

}SDB_RETURNCODE_E;

#define PTM_LOG_CNT_PREFIX_NAME_MAX_LEN  31 /* 计数前缀名称最大长度 */

typedef struct PTM_LogCnt_RecRegInfo
{
    UINT64  ul64ComCsi;             /* 组件CSI,创建定时器时使用 */
    ULONG   **ppulCntAddr;          /* 保存各计数器单元开始地址的数组 */
    VOID    (*pPreCallBack)();      /* 打印计数前,回调函数 */
    ULONG   (*pIsReady)();          /* 判断是否可以开始打印 */

    ULONG   ulDBGLogRegId;                                          /* 写诊断日志的ID */
    ULONG   ulComHandle;            /* 组件Handle,用于申请内存 */
    UCHAR   aucPrefixName[PTM_LOG_CNT_PREFIX_NAME_MAX_LEN + 1];     /* 输出内容前缀名称 */
    ULONG   ulTotalCntElemNum;      /* 一个计数器单元的总元素个数 */
    ULONG   ulCntUnitNum;           /* 计数器单元的个数 */
    ULONG   ulTimeMsgType;          /* 创建定时器时输入的消息类型  */
    ULONG   ulIsTimerSupport;       /* 注册的任务本身,是否支持处理定时消息. VOS_TRUE VOS_FALSE
                                     * 不支持要写VOS_FALSE，否则可能会造成计数无法打印日志 */
}PTM_LogCnt_RecRegInfo_S;


typedef enum
{
    PTM_BATCH_CMD_RSP_CONTINUE,
    PTM_BATCH_CMD_RSP_END,
    PTM_BATCH_CMD_RSP_ARGUMENT_NUM_ERR,
    PTM_BATCH_CMD_RSP_KEYWORD_ERR,
    PTM_BATCH_CMD_RSP_ARGUMENTS_ERR,
} PTM_BATCH_CMD_RSP_E;


#define GTP_DHCP_ALLOC_ADDR         4   /* DHCP服务器分配地址(B01不支持) */

enum enumRTDPRI
{
    RTD_PRIORITY_HIGH   = 0x1,/* 共享队列高优先级 */
    RTD_PRIORITY_MIDDLE = 0x2,/* 共享队列中优先级 */
    RTD_PRIORITY_LOW    = 0x4,/* 共享队列低优先级 */
};

/*-------------------------- BEGIN: Mbuf ------------------------------------*/
#define PMBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))
#define PMBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)(pstMBufM)->stDataBlockDescriptor.pucData)
#define PMBUF_TYPE_DATA             1

/*************************************************************************************/
/*                                命令行注册                                         */
/*************************************************************************************/
#define LINELENGTH 80

typedef struct Command_S* LPCommand_S;
typedef struct Command_Group_S* LPCommand_Group_S;

struct Command_S
{
    CHAR szCommand[LINELENGTH];
    CHAR szHelp[2*LINELENGTH];
    LPCommand_Group_S lpArgument;
    VOID (*CommandProc) (ULONG, CHAR*[]);
};

struct Command_Group_S
{
    LONG lCommandNo;
    LONG lHelpPos;
    LPCommand_S lpCommand;
};


#define GTPC_SND2_LAP_CNT_COUNT 200

/* 队列优先级定义 */
typedef enum tag_URTD_Priority_Type
{
    URTD_PRIORITY_HIGH,      /* 共享队列高优先级 */
    URTD_PRIORITY_LOW,       /* 共享队列低优先级 */
    URTD_PRIORITY_MAX_NUM
}URTD_Priority_Type_S;

#define M_EMS_TRC_SEND_MSG    0
#define M_EMS_TRC_RECV_MSG    1

#define  GTPC_GUSER_MSGTYPE_DHCPV4               0x21
#define  GTPC_GUSER_MSGTYPE_DHCPV6               0x22

#define  TRC_DIRECTION_LEFT_IN_SGW          0x000
#define  TRC_DIRECTION_RIGHT_OUT_SGW        0x100
#define  TRC_DIRECTION_LEFT_IN_PGW          0x200
#define  TRC_DIRECTION_LEFT_IN_PGW_PMIP     0x210

#define  TRC_DIRECTION_DHCPV6_IN_PGW          0x1000
#define  TRC_DIRECTION_DHCPV6_OUT_PGW         0x1100

#define  TRC_DIRECTION_DHCPV6_IN_GGSN         0x1200
#define  TRC_DIRECTION_DHCPV6_OUT_GGSN        0x1300

#define  TRC_DIRECTION_DHCPV6_IN_SGW          0x1400
#define  TRC_DIRECTION_DHCPV6_OUT_SGW         0x1500

#define  GUSER_MSGTYPE_DHCPV4           0x0200
#define  GUSER_MSGTYPE_DHCPV6           0x0400


#define M_PTM_QUE_NAME_LEN  31

typedef struct tagPTM_QUEUE_INFO
{
    VOS_UINT64 ullSelfCsi;
    VOS_UINT32 ulMsgType;
    VOS_UINT32 ulQueType;
    VOS_UINT32 ulQueLen;
    VOS_UINT32 ulEvent;
    VOS_UINT32 ulTaskId;
    VOS_CHAR szQueName[M_PTM_QUE_NAME_LEN + 1];
}PTM_QUEUE_INFO_S;

typedef enum enMSG_QUE_TYPE_E
{
    MSG_QUETYPE_MCQ = 1,
    MSG_QUETYPE_VOSQ,
    MSG_QUETYPE_LFQ,
    MSG_QUETYPE_DMSQ,
}MSG_QUE_TYPE_E;

/* 定时器事件位 */
#ifndef VOS_TIMER_EVENT
#define VOS_TIMER_EVENT                 (1 << 15 )
#endif

//这个玩意是否放这还要再看一下，如果pgp_id.h最终作为接口文件，这个定义移到pgp_id.h中
/******************************************************************************/
/*                PS COMPONONT Definition                                     */
/******************************************************************************/
enum enumPSCompType
{
    COMP_T_PSSTART = 3256,      /* !!!!!这里开始PS使用 */
    COMP_T_PSEND = 3511         /* 前面产品使用 */
};

//3256~3409为网关业务使用的组件id范围。
#define M_PS_COMP_TYPE_BASE COMP_T_PSSTART
//Cyjun: 平台UFP采用下面定义，需确认
//#define M_PS_COMP_TYPE_BASE 3100

//3410-3512为增值类业务使用的组件id范围，包括VOG/HOSTING/SBR，但是后续UGW/SCCG/PDSN/WASN不能使用此段，建议接入侧复用。
#define M_PS_VAS_COMP_TYPE_BASE (M_PS_COMP_TYPE_BASE + 154)

/* C00119457: 下面的枚举只有UFP和业务侧在用，所以放在这个文件由业务侧与UFP
共享(业务侧负责维护，UFP同步) */
/* !!!枚举顺序不可随意修改，必须和SPUCFG一致，目前组件类型已用满，各组不能自行增加!!! */
/* 实名组件类型，在此定义的组件类型会直接影响业务的部署，会写入到spucfg中 */
typedef enum enCOMP_TYPE_E
{
    // ========================= 网关组件 ================================
    // AM组件
    E_COMP_TYPE_USM  = M_PS_COMP_TYPE_BASE,   /* 非零，具体值待定 */
    E_COMP_TYPE_SDUA, //3257
    E_COMP_TYPE_SDU, //3258
    E_COMP_TYPE_SD, //3259
    E_COMP_TYPE_CKPA, //3260
    E_COMP_TYPE_CKPC, //3261
    E_COMP_TYPE_GRMA, //3262
    E_COMP_TYPE_GTRC, //3263
    E_COMP_TYPE_USM_SRU, //3264
    E_COMP_TYPE_MASTERM, //3265
    E_COMP_TYPE_AM_SCCG_CDB, //3266
    E_COMP_TYPE_NWCENTER, //3267
    E_COMP_TYPE_NWA, //3268

    // CM 组件
    E_COMP_TYPE_CMCR, //3269
    E_COMP_TYPE_GACT, //3270
    E_COMP_TYPE_GAAG, //3271
    E_COMP_TYPE_CDRF, //3272
    E_COMP_TYPE_CMOC, //3273
    E_COMP_TYPE_OCSC, //3274
    E_COMP_TYPE_OCGM, //3275
    E_COMP_TYPE_PCSD, //3276
    E_COMP_TYPE_DIAM, //3277
    E_COMP_TYPE_PCSM, //3278
    E_COMP_TYPE_PCCR, //3279
    E_COMP_TYPE_CMAC, //3280
    E_COMP_TYPE_ACCT, //3281
    E_COMP_TYPE_CM_STG, //3282
    E_COMP_TYPE_SRU_CDRF, //3283
    E_COMP_TYPE_CM_GOM, //3284
    E_COMP_TYPE_SRU_ACCT, //3285
    E_COMP_TYPE_ICPM, //3286
    E_COMP_TYPE_CM_PCRFC_GOM, //3287
    E_COMP_TYPE_CM_SRU_POSTPAID, //3288

    // PTM组件
    E_COMP_TYPE_PRPC, //3289
    E_COMP_TYPE_ASN, //3290
    E_COMP_TYPE_PAGP, //3291
    E_COMP_TYPE_CPATH, //3292
    E_COMP_TYPE_PAPI, //3293
    E_COMP_TYPE_PAGM, //3294
    E_COMP_TYPE_L2TT, //3295
    E_COMP_TYPE_PPPT, //3296
    E_COMP_TYPE_IPV6, //3297
    E_COMP_TYPE_AUTH, //3298
    E_COMP_TYPE_AAAGM, //3299
    E_COMP_TYPE_S6B, //3300
    E_COMP_TYPE_POD, //3301
    E_COMP_TYPE_GLAP2, //3302
    E_COMP_TYPE_LAP1, //3303
    E_COMP_TYPE_LAPSC, //3304
    E_COMP_TYPE_CLAP, //3305
    E_COMP_TYPE_DHCPC, //3306
    E_COMP_TYPE_DHCPCGM, //3307
    E_COMP_TYPE_DSV4, //3308
    E_COMP_TYPE_DSV6, //3309
    E_COMP_TYPE_IPPMSRU, //3310
    E_COMP_TYPE_IPPMSPU, //3311
    E_COMP_TYPE_IPPMPEU, //3312
    E_COMP_TYPE_GMBMS, //3313
    E_COMP_TYPE_CMBMS, //3314
    E_COMP_TYPE_LIX1, //3315
    E_COMP_TYPE_LIX2, //3316
    E_COMP_TYPE_LIX3, //3317
    E_COMP_TYPE_X2PA, //3318
    E_COMP_TYPE_X3PA, //3319
    E_COMP_TYPE_X2SE, //3320
    E_COMP_TYPE_X3SE, //3321
    E_COMP_TYPE_LISC, //3322
    E_COMP_TYPE_LIGM, //3323
    E_COMP_TYPE_HZT, //3324
    E_COMP_TYPE_SRUMBMS, //3325
    E_COMP_TYPE_PTMAPP, //3326
    E_COMP_TYPE_NW_HANDSHAKE, //3327
    E_COMP_TYPE_S6BM, //3328
    E_COMP_TYPE_PTM_RESERVED3, //3329
    E_COMP_TYPE_PTM_RESERVED4, //3330

    // IPN组件
    E_COMP_TYPE_RPT, //3331
    E_COMP_TYPE_ICAP, //3332
    E_COMP_TYPE_SOMT, //3333
    E_COMP_TYPE_SOMS, //3334
    E_COMP_TYPE_SOM0, //3335
    E_COMP_TYPE_SPE, //3336
    E_COMP_TYPE_ASPE, //3337
    E_COMP_TYPE_ACCESS, //3338
    E_COMP_TYPE_SM_GOM, //3339
    E_COMP_TYPE_SM_RESERVED1, //3340
    E_COMP_TYPE_SM_RESERVED2, //3341
    E_COMP_TYPE_SM_RESERVED3, //3342
    E_COMP_TYPE_SM_RESERVED4, //3343
    E_COMP_TYPE_SM_RESERVED5, //3344

    // AM组件2
    E_COMP_TYPE_AM_SEG2 = 3345,
    E_COMP_TYPE_AM_TDFI,

    // HSGW产品组件
    E_COMP_TYPE_CM_SRU_PREPAID = 3349, //3349
    E_COMP_TYPE_PDSNKERNEL, //3350
    E_COMP_TYPE_POSTPAID,   //3351
    E_COMP_TYPE_PREPAID,    //3352
    E_COMP_TYPE_CONTENT,    //3353
    E_COMP_TYPE_PDSNACCT,   //3354
    E_COMP_TYPE_TIMER,      //3355
    E_COMP_TYPE_RESV,       //3356
    E_COMP_TYPE_DIAMAUTH,   //3357
    E_COMP_TYPE_FA,         //3358
    E_COMP_TYPE_CMPM,       //3359
    E_COMP_TYPE_CSN,        //3360
    E_COMP_TYPE_DNSC,       //3361
    E_COMP_TYPE_HSGW_PMIPV6,//3362
    E_COMP_TYPE_HSGW_STACFG,//3363
    E_COMP_TYPE_CMPTHREAD,  //3364

    // PTM组件2
    E_COMP_TYPE_PTM_SEG2 = 3375,
    E_COMP_TYPE_DEBUG,      //3376

    // CM组件2
    E_COMP_TYPE_CM_SEG2 = 3390,
    E_COMP_TYPE_CM_FC, //3391
    //E_COMP_TYPE_CM_FC_TRY, //3392

    // IPN组件
    E_COMP_TYPE_IPN_SEG2 = 3400,

    // ========================= 增值业务组件 ================================
    /*MSD板组件*/
    E_COMP_TYPE_MSD_SDI = M_PS_VAS_COMP_TYPE_BASE, //3410
    E_COMP_TYPE_MSD_SDE,     //3411
    E_COMP_TYPE_MSD_SOMT,    //3412
    E_COMP_TYPE_MSD_SOM0,    //3413
    E_COMP_TYPE_MSD_SMAGENT, //3414
    E_COMP_TYPE_MSD_TCPP,    //3415

    E_COMP_TYPE_MSD_SDUA,    //3416
    E_COMP_TYPE_MSD_SDU,     //3417
    E_COMP_TYPE_MSD_UPM,     //3418
    E_COMP_TYPE_MSD_GRMA,    //3419

    E_COMP_TYPE_MSD_SOM,     //3420
    E_COMP_TYPE_PRO_DPSO,    //3421

    /*MSU板组件*/
    E_COMP_TYPE_VAS_SDUA,   //3422
    E_COMP_TYPE_VAS_SDU,    //3423
    E_COMP_TYPE_VOG_UPM,    //3424
    E_COMP_TYPE_VOG_GRMA,   //3425
    E_COMP_TYPE_VOG_RPT,    //3426
    E_COMP_TYPE_VOG_SOM,    //3427
    E_COMP_TYPE_VOG_OMA,    //3428
    E_COMP_TYPE_PGP_SOCKET, //3429
    E_COMP_TYPE_VOG_ME,     //3430
    E_COMP_TYPE_VOG_TCC,    //3431
    E_COMP_TYPE_VOG_OFFTC,  //3432
    E_COMP_TYPE_VOG_TCS,    //3433

	// OTHERS
	E_COMP_TYPE_VBS = 3511,  // HUTAF_COVERAGE


    E_COMP_TYPE_NUM,
}DHCP_COMP_TYPE_E;

/************************* MACRO & TYPE DEFINITION ***************************/
/**
* @ingroup  v_mcque
*
* 队列ID类型定义。
*/
typedef VOS_VOID* MC_QUE_ID;


typedef enum  enAM_USM_QUE_TYPE_E
{
    E_AM_USM_QUE_START = M_PS_MSG_TYPE_BASE,
    E_AM_USM_QUE_SD_UPDATE,         /* 接收到SD 的GTP更新队列，对应QGTPUPDSC%02lu 队列 */
    E_AM_USM_QUE_SD_DELETE,         /* 接收到SD 的GTP去活队列，对应QGTPDEASC%02d 队列 */
    E_AM_USM_QUE_SD_RESPONSE,       /* 接收到SD 的GTP响应队列，对应QGTPRSPSC%02d 队列 */
    E_AM_USM_QUE_SD_MSINFO,         /* 接收到SD 的ms info change notification request队列，对应QMSCSC%02d 队列 */
    E_AM_USM_QUE_SD_VIP_CREATE,     /* 接收到SD 的GTP VIP用户激活、更新队列，对应QVIPSC%02d 队列 */
    E_AM_USM_QUE_SD_VIP_DELETE,     /* 接收到SD 的GTP VIP用户去活队列，对应QVIPDSC%02d 队列 */
    E_AM_USM_QUE_SD_SECOND,         /* 接收到SD 的GTP 二次激活队列，对应QSECACTSC%02d 队列 */
    E_AM_USM_QUE_SD_CREATE1,        /* 接收到SD 的GTP 用户激活队列之优先级1，对应QACTP1SC%02d 队列 */
    E_AM_USM_QUE_SD_CREATE2,        /* 接收到SD 的GTP 用户激活队列之优先级2，对应QACTP2SC%02d 队列 */
    E_AM_USM_QUE_SD_CREATE3,        /* 接收到SD 的GTP 用户激活队列之优先级3，对应QACTP3SC%02d 队列 */
    E_AM_USM_QUE_SD_CREATE4,        /* 接收到SD 的GTP 用户激活队列之优先级4，对应QACTP4SC%02d 队列 */
    E_AM_USM_QUE_SD_CREATE5,        /* 接收到SD 的GTP 用户激活队列之优先级5，对应QACTP5SC%02d 队列 */
    E_AM_USM_QUE_SD_ERR_INDICATION, /* 接收到SD 的Error Indication队列，对应QV0V1ERRSC%02d 队列 */
    E_AM_USM_QUE_SD_GENERAL,        /* 接收到SD 的General队列，对应SGENSC%02d 队列 */
    E_AM_USM_QUE_SD_DELETE_TEID0,   /* SDU分发到SD的TEIDC为0的去激活消息，对应QDEACTIVESC%02d 队列 */
    E_AM_USM_QUE_SD_PMIP,           /* SD分发PMIP的消息，对应 QPMIP%02lu队列*/

    E_AM_USM_QUE_SC_GTPV2_MSG,      /* SC上接收到GTPv2内部消息队列，对应U_GTPV2 队列 */
    E_AM_USM_QUE_SC_GTPV2_SELF_MSG, /* SC上接收到GTPv2内部消息队列，对应U_V2SLF 队列 */
    E_AM_USM_QUE_SC_AUTH_MSG,       /* SC上接收到AUTH模块消息队列，对应U_AUTH 队列 */
    E_AM_USM_QUE_SC_SM_MSG,         /* SC上接收到IPN模块消息队列，对应U_SM 队列 */
    E_AM_USM_QUE_SC_CM_MSG,         /* SC上接收到CM模块消息队列，对应U_CM 队列 */
    E_AM_USM_QUE_SC_PMIP_MSG,       /* SC上接收到PMIP模块消息队列，对应U_PMIP 队列 */
    E_AM_USM_QUE_SC_IPC_MSG,        /* SC上接收到IPC模块消息队列，对应U_IPC 队列 */
    E_AM_USM_QUE_SC_SELF_MSG,       /* SC上接收到USM模块消息队列，对应U_SELF 队列 */
    E_AM_USM_QUE_SC_PCRF_MSG,       /* SC上接收到PCRF模块消息队列，对应U_PCRF 队列 */
    E_AM_USM_QUE_SC_PPP_MSG,        /* SC上接收到PPP模块消息队列，对应U_PPP 队列 */
    E_AM_USM_QUE_SC_L2TP_MSG,       /* SC上接收到L2TP模块消息队列，对应U_L2TP 队列 */
    E_AM_USM_QUE_SC_ERR_MSG,        /* SC上接收到USM模块消息队列，对应U_ERR 队列 */
    E_AM_USM_QUE_SC_LAP_MSG,        /* SC上接收到LAP模块消息队列，对应U_LAP 队列 */
    E_AM_USM_QUE_SC_DHCPV4S_MSG,    /* SC上接收到DHCPV4S模块消息队列，对应U_DHCPV4 队列 */
    E_AM_USM_QUE_SC_DLDN_MSG,       /* SC上接收到USM模块消息队列，对应U_DLDN 队列 */
    E_AM_USM_QUE_SC_PFUPDTBL_MSG,   /* SC上接收到模块消息队列，对应U_PFUPDTBL 队列 */
    E_AM_USM_QUE_SC_S6B_MSG,        /* SC上接收到S6B模块消息队列，对应U_S6B 队列 */
    E_AM_USM_QUE_SC_ASN_QUERY,      /* SC上接收到ASN模块消息队列，对应U_ASN 队列 */

    E_AM_USM_QUE_IPN_QOS_UPDATE,    /* 接收SM的内容感知共享消息队列，对应AMRcvSMMsgQue%02lu 队列 */

    E_AM_USM_QUE_LAP,               /* 接收LAP的共享消息队列，对应SC%02lu_V2USM_QUE 队列 */
    E_AM_USM_QUE_HOMEZONE,          /* 接收HOMEZONE共享消息队列，对应HZGT%d 队列 */
    E_AM_USM_QUE_L2TP,              /* 接收L2TP共享消息队列，对应L2TP-GTPC%lu 队列 */
    E_AM_USM_QUE_ASN,               /* 接收ASN共享消息队列，对应ASNSC%02d 队列 */

    E_AM_USM_QUE_PF_DL_NOTIFY,      /* 接收PF的downlink-data-notify通知共享消息队列，对应S%luDLNOTIFY 队列 */
    E_AM_USM_QUE_PF_TBL_OPT_FAIL,   /* 接收PF更新表项的结果的通知队列，对应DPS_TblOptFailAck_SC%2lu 队列 */

    E_AM_USM_QUE_TIMER,             /* 接收定时器消息队列，对应U_TM 队列 */
    E_AM_USM_QUE_GM_RANDOM,         /* 接收随机用户跟踪共享消息队列，对应RANDOM_GTPCRCV%2d 队列 */

    /* add start by jiexianzhu at 2012.08.25 for 计数整合 */
    E_AM_USM_QUE_SC_GRM_MSG,        /* GRM发送SC接收的用于命令的队列，对应GRMWriteSCRead%2lu 队列 */
    /* add end by jiexianzhu at 2012.08.25 for 计数整合 */

    E_AM_USM_QUE_FCM_GTP,           /* 对应FCM_SUB_MID_GTPC  相关处理 */
    E_AM_USM_QUE_FCM_GTPC_FSDB,     /* 对应FCM_SUB_MID_GTPC_FSDB CKP相关处理 */
    E_AM_USM_QUE_FCM_MSU,     /* MSU用户在线注入开始消息 */

    E_AM_USM_QUE_SELFMSG_FOR_SPUF,  /* USM 发给自己的消息,目前只用于F板没有创建相应的队列*/

    E_AM_USM_QUE_SELF_CHECK,        /* 对应原来DE板各种核查消息 */

    E_AM_USM_QUE_FCM_MSD,           /* 来自MSD的消息 */
    E_AM_USM_QUE_TYPE_END,
}AM_USM_QUE_TYPE_E;

/* 事件类型 */
#define M_AM_USM_EV_GTPV2_MSG            (1 << 0)   /*接收GTPV2发来的消息*/
#define M_AM_USM_EV_GTPV2_SELF_MSG      (1 << 0)   /*接受USM任务发送给自己的GTPV2消息事件位 */
#define M_AM_USM_EV_SELF_MSG             (1 << 0)   /*接收自己发送的的消息事件 */

#define M_AM_USM_EV_AUTH_MSG             (1 << 1)    /*接收AAA的消息事件 */
#define M_AM_USM_EV_LAP2_MSG             (1 << 2)    /*接收LAP2的消息事件 */
#define M_AM_USM_EV_RANDOM_TRC           (1 << 3)   /* GRM写给USM的随机跟踪事件位 */
#define M_AM_USM_EV_CM_MSG               (1 << 4)    /*接收CM-CORE的消息事件 */
#define M_AM_USM_EV_RCPF_MSG             (1 << 5)    /*接收RCPFC发来的消息事件*/
#define M_AM_USM_EV_IPC_EVENT_MSG       (1 << 6)    /*接收IPC消息事件 */

#ifndef VOS_NO_WAIT
#define VOS_NO_WAIT                 ((VOS_UINT32)1 << 31)
#endif

#ifndef VOS_EV_ANY
#define VOS_EV_ANY                  ((VOS_UINT32)1 << 26)
#endif

#ifndef VOS_WAIT
#define VOS_WAIT                    ((VOS_UINT32)1 << 30)
#endif

/* 读写队列模式 */
#define VOS_MCQUEUE_WAIT      ((VOS_UINT32)1 << 4) /* 等待模式   */
#define VOS_MCQUEUE_NO_WAIT   ((VOS_UINT32)1 << 5) /* 不等待模式 */


#define M_SPM_BYTE_024  24
#define M_SPM_BIT_218  218


/*----------------------------------------------------------------------*/
/*
 * 下面两个宏定义了“开”和“关”两个状态，这两个宏被后面的
 * 宏引用。例如：
 *
 *  #define VRP_MODULE_RTPRO_OSPF   VRP_NO
 *  #define VRP_MODULE_RTPRO_RIP    VRP_YES
 *
 * 表示动态路由协议OSPF被关闭，而动态路由协议RIP被开启，这
 * 样，VRP系统在编译时，就可以拆掉OSPF模块而保留RIP模块。
 * 需要注意的是有些意义上互斥的一对宏，不能被同时置为
 * “VRP_YES”或“VRP_NO”，这一点将体现在后面的叙述中。
 * 注意，请不要修改这两个宏的值。
 */
#define VRP_YES     1
#define VRP_NO      0
/*----------------------------------------------------------------------*/


/*BYTE类型宏定义*/
typedef enum enU_SOFTPARA_BYTE_VALUE
{
    //Cyjun: 既然实际是个宏的集合，业务不用的清理出去，平台以宏定义了M_SPM_ALM_SUMMUMER
    M_SPM_ALM_SUMMUMER = 2,/*告警时区夏令时*/

    M_SPM_DHCP_AGENTIP_USAGE_CTR = 3,/* 控制远端地址池Agent IP下地址的最大使用率 zhangjinquan z00175135 */

    M_SPM_DHCP_AGENTIP_NUM_CTR = 4,/* 控制APN在每个CPU上最大申请的Agent IP个数 zhangjinquan z00175135 */

    //Cyjun: 既然实际是个宏的集合，业务不用的清理出去，平台以宏定义了M_SPM_SEC_UMT
    M_SPM_SEC_UMT = 10,/*M2000UMTS5.0 and UMTS6.0,软参控制*/

    M_SPM_SGSN_GGSNACK_ACT = 13,/*用于配置控制GGSN返回给终端config-ack信息*/
    M_SPM_GGSN_TNA_ACT = 14,/*用于控制透明不鉴权用户是否把激活请求中的CHAP/PAP鉴权信息返回给终端*/
    M_SPM_GGSN_AUTH_ACT = 15,/*用于控制透明鉴权或者不透明接入是否在激活响应消息中携带CHAP/PAP鉴权信息返回给终端*/
    M_SPM_CM_ACCT_INTERVAL =    18,/*用于控制ACCT是否支持AAA鉴权下发的时间阈值:1支持不支持*/

    M_SPM_GGSN_R5SWITCH_ACT = 19,/*该开关是为了支持R5 Qos做的，控制是否支持CR411*/

    M_SPM_GGSN_VIRTUALAPNRULE_LOADSHARE = 20,/*bit2,用于控制负荷分担方式的虚拟APN，如果真实APN绑定的AAA计费服务器不可用，在配置不等AAA响应发激活响应和AAA响应超时不去激活用户时是否允许选择该APN。*/

    M_SPM_CM_DIAM_PROXY = 25,/* 用于控制在线计费时DCC消息是否支持proxy */

    M_SPM_CM_OCSC_CHECKHOST = 27,/* 控制在线计费时是否检查CCA消息的origin-host */

    M_SPM_GGSN_SAMEIMSI_ACT = 31,/*用于控制当用户激活GGSN已经存在和该用户激活请求相同的IMSI，但MSISDN不同的PDP上下文时，是否允许用户激活*/

    M_SPM_CM_OCSC_USER_EQUIPMENT_INFO = 33, /* 控制CCR消息中IMEIV信元格式为BCD码或UTF8String类型 */
    M_SPM_PLMN_ARP_CONTROL_POINT = 36,     /* 获取plmn以及差异化打点的控制点是在去AAA鉴权之前还是之后 */
    M_SPM_UGW_AAA_ALARM_INTERVAL = 41,     /* AAA告警扫描server状态的间隔 */
    M_SPM_UGW_AAA_ALARM_ACCUMULATE = 42,    /* 累计连续down的次数才上报告警 */

    M_SPM_AM_DHCP_KPN = 39,

    /*43号软参定义SC 用户发出去的请求，在T3N3超时后，是否告警，
       如果该值为0，就不会告警和路径断，如果是1到15的值，表示当前
       SC要发送由软参所设置的个请求都超时，才置该SC的路径断，并报告给SD*/
    M_SPM_AM_SFN_PATH_ALARM_SW = 43,
    M_SPM_UDP_CHECKSUM = 45,        /* 用于控制UDP CheckSum, bit0:L2tp控制消息,bit1:L2tp数据消息,bit2:Gtp, bit3:DHCP */
    /* Added start by taojixiu 00132297 at 2008-11-25 V8需求同步 for APN全大写 */
    /*控制AAA鉴权、计费以及话单，OCS中APN名是否大写*/
    M_SPM_GGSN_APN_UPPERCONTROL = 40,
    /* Added end by taojixiu 00132297 at 2008-11-25 V8需求同步 for APN全大写 */

    /* BEGIN: Added for PN:软参控制camel用户欠费处理 by baoxin 144601, 2008/12/27 */
    M_SPM_AM_ADDR_CONFLIC_CHECK_SW = 44,
    M_SPM_L2TP_UDP_CHECKSUM = 45,
    M_SPM_AM_GRM_CONTROL_TIMER = 46,
    M_SPM_GGSN_DEACTIVE_CAUSE_CTRL = 62,
    /* END: Added for PN:软参控制camel用户欠费处理 by baoxin 144601, 2008/12/27 */

    M_SPM_AM_GGSN_TAKE_CGADDRESS = 49, /*GGSN在激活和更新应答中是否携带CG地址*/

    M_SPM_CM_OCSC_FAILOVER_NODE_NUM = 50,   /* 设置Failover节点个数 */

    /* 52号软参定义了RG节点是否需要老化的标记
    取值范围为0-255，该软参默认值设置为0，如果非零，则超过30秒后老化*/
    M_SPM_SM_RG_AGE_FLAG = 52,
    /* 53号软参定义了pipeline功能是否打开标记
    取值范围为0-255，该软参默认值设置为0，pipeline功能关闭，如果非零，pipeline功能打开*/
    M_SPM_SM_PIPELINE_FLAG = 53,

    M_SPM_GGSN_ACCOUT_ACT= 54,

    M_SPM_GGSN_CHARGE_ACT = 55,/*用于控制当用户激活GGSN已经存在和该用户激活请求相同的IMSI，但MSISDN不同的PDP上下文时，是否允许用户激活*/

    M_SPM_CM_ACCT_VENDORID = 56,/*用于控制TMO扩展信元VENDORID是TMO还是HUAWEI:1是huawei ;0是TMO*/

    /* 57号软参定义了当内容计费流节点资源耗尽时的处理动作，
    最低bit为五元组节点耗尽动作，最低第二bit为RG节点耗尽动作
    0为阻塞，1为Pass不计费*/
    M_SPM_SM_SFN_RESOURCE_EXHAULT_ACT = 57,

    M_SPM_PPP_L2TP_AUTH_IPCP_SWITCH = 59, /* for M1  */

    M_SPM_L2TP_INVALID_TUNL_EXIST = 63, /* 无效L2TP隧道存活时间，单位:小时 */

    M_SPM_SM_SAM_INDENTIFY_THRESHOLD = 66, /*最大关联识别包数*/

    M_SPM_IMSIMSISDN_SELECT = 68,
    /*用于控制性能统计时用哪个APN进行统计,如果软参值为1，用虚拟APN进行性能统计,软参值为0，用真实APN进行性能统计*/
    M_SPM_CM_CAPABILITY_STAT_APN_TYPE = 75,

    /* Added start by liwei 57151 at 2008-12-22 V9R7C02 for C02V8特性移植 */
    /* 控制diameter消息called-station-id AVP标记位 */
    M_SPM_CM_DIAM_CSIAVPFLAG = 76,
    /* 1,2,3 bit控制V8 I+D需求；4 bit控制NSN对接需求 */
    M_SPM_CM_V8_SOFT_PARAM = 77,
    /* Added end by liwei 57151 at 2008-12-22 V9R7C02 for C02V8特性移植 */

    /*60号软参用来控制外层分片的老化时间，单位为250ms
      取值范围 1~255，缺省值120,若配置为0则取120*/
    M_SPM_PF_EXTERIOR_FRAG_AGING_THR = 60,

    /*61号软参用来控制内层分片的老化时间，单位为250ms
      取值范围 1~255，缺省值120,若配置为0则取120*/
    M_SPM_PF_INTERIOR_FRAG_AGING_THR = 61,

    /*64号软参用来配置计费一个BTI内的流量阈值
      取值范围 0~40，缺省值0*/
    M_SPM_PF_CHARGE_BTI_FLOW_THR = 64,

    M_SPM_CM_CDRF_CTRLIDLE = 65,

    //begin added by liuyan 39579 for R007C02 V8特性移植
    M_SPM_CM_V8_SOFT_PARA = 79,
    //end added by liuyan for R007C02 V8特性移植
    /* Bit0和Bit1两位,事件计费的类型:  00：SCUR事件计费   01：IEC  10：增强性ECUR
      Bit2位：1：开启block功能：激活触发CCR，不回CCA,Tx超时后在线转离线，后续的事件计费业务被阻塞 0：关闭block功能 */
    M_SPM_CM_IEC_ECUR_SCUR_EVENT = 80,
    M_SPM_CM_NPT_SOFT_PARA = 81,

    M_SPM_CM_CCA_TIMEOUT_ALM = 82,
    M_SPM_CM_CCA_TIMEOUT_ALM_RESTORE = 83,
    M_SPM_PF_IPv6_UDP_CHKSUM_FLAG = 84,

    M_SPM_CM_OCSC_SUPPORTED_VENDOR_ID = 85,
    /* Added start by l00129869 at 2009-07-30 GGSNV9R7C03 for 话单32位翻转 */
    /* Added end by l00129869 at 2009-07-30 GGSNV9R7C03 for 话单32位翻转 */
    M_SPM_CM_TFA_FUN_SWITCH = 87, /* 西班牙在线计费需求*/
    M_SPM_CM_CDR_ADAPT_FOR_OPERATE = 88,

    M_SPM_LI_TAI_MAXSEQNUMDELTA = 89,

    M_SPM_CM_DIAM_DEBUG_CONTROL_FLAG = 90,
    M_SPM_L2TP_PRILNS_DETECT_INTERVAL = 92, /* 无效L2TP隧道存活时间，单位:小时 */
    M_SPM_CM_DIAM_XML_FILE_OPERATOR_ID = 93,

    M_SPM_CM_DIAM_CAPABILITY_EXCHANGE_CONTROL = 91,

    M_SPM_AM_MSG_AUTHENTICATOR_FLAG = 95,
    M_SPM_AM_MSG_ACCESSPREFIX_FLAG = 96,
    /* Modified start by Libin 51420 at 2009-10-29 GGSNV9R8-IPN for 业务报表增强 */
    /* start: added by h00139187, 2010-10-25 for UGWV9R9C00 BBIT Debug Policing 补偿软参*/
    M_SPM_PF_CAR_RETRIEVE_RATE = 97,
    /* Added start by l00141244 at 2011-07-30 V9R9C00 for CR20110113007 五元组快速老化时间进行软参控制 */
    M_SPM_SM_FD_QUICK_AGE_TIME = 98,
    /* Added end by l00141244 at 2011-07-30 V9R9C00 for CR20110113007 五元组快速老化时间进行软参控制 */

    M_SPM_L2TP_ICCN_LCP_FLAG = 110,

    M_SPM_AM_FORWARDING_AGE_TIME =115,  /*转发表项老化启动时间，有效值为0-24.值为0时，默认3点。1-24时，启动时间为1-24点。*/

    /* Added start by taojixiu 00132297 at 2010-06-22 V9R8C01 for PS8.1 FLOW CONTROL 流控软参调整*/
    M_SPM_AM_GTPC_WAL_MAX = 121,
    M_SPM_AM_GTPC_WAL_PERCENT = 122,
    M_SPM_AM_GTPC_N_MIN = 123,
    M_SPM_AM_GTPC_APN_FAULT_INTERVAL = 124,
    M_SPM_AM_SD_NORMAL_CEREATE_NUM = 125,
    M_SPM_AM_SD_VIP_CEREATE_NUM = 126,
    M_SPM_AM_SD_ALARM_INTERVAL = 127,
    M_SPM_AM_SD_ALARM_TIMES = 128,
    M_SPM_AM_SD_RESTORE_ALARM_INTERVAL = 129,
    M_SPM_AM_SD_RESTORE_ALARM_TIMES = 130,
    /* Added end by taojixiu 00132297 at 2010-06-22 V9R8C01 for PS8.1 FLOW CONTROL 流控软参调整 */

    M_SPM_DHCP_SERVER_TEST_INTERVAL = 132,     /* DHCP 探测server状态定时器超时次数 */
    M_SPM_DHCP_ALARM_INTERVAL = 133,           /* DHCP 告警扫描server状态的间隔 */
    M_SPM_DHCP_ALARM_ACCUMULATE = 134,         /* 累计连续down的次数才上报告警 */

    M_SPM_WAITREL_TIME_REDIRECT = 318,
    M_SPM_WAITREL_TIME_GIDEFEND = 612,
    M_SPM_CM_TARIFF_USER_PER_SECON = 38,

    M_SPM_AM_GTPC_CACHE_TIME = 102,
    M_SPM_AM_UPM_ONLINE_INJECT = 103,
    M_SPM_IPN_RPT_SUBSCRIBER_SWITCH = 105,
    /* Modified end by Libin 51420 at 2009-10-29 GGSNV9R8-IPN for 业务报表增强 */

    /* BEGIN: Added for PN:AX4D14214 用户流间隔超过2分钟的情况导致SIG识别率低 by x00110917, 2010/3/17 */
    M_SPM_IPN_CACHE_FD_AGETIME = 107,    /* 小五元组老化时间 1-255 表示 10s~2550s */
    /* END:   Added for PN:AX4D14214 用户流间隔超过2分钟的情况导致SIG识别率低 by x00110917, 2010/3/17 */
    /* BEGIN: Added for 问题单号:AK9D04024 by j00134986, 2010/6/10 */

    M_SPM_SM_PCC_FUP_RGSID_OR_MKEY = 108,

    M_SPM_CM_OCSC_VDF = 113,

    M_SPM_AM_MULTI_ACCESS_MODE = 114,    /* 业务模式、信令模式软参，默认为信令模式 */

    /* 异常返回码动作处理动作 */
    M_SPM_CM_OCSC_RETCODE_ACTION = 116,

    M_SPM_AM_HZ_ACT_NUM_IN_SEC_MAX = 117,/*Added by c0011085 for homezone 流控*/

    /*Added Start by liuli 67542, 2011-05-25 for ps9.1 sync GGSNV9R8C01 CR20101208036 无线资源动态调控需求*/
    M_SPM_IP_2G_RES_DYN_CTRL = 131,
    /*Added end by liuli 67542, 2011-05-25 for ps9.1 sync GGSNV9R8C01 CR20101208036 无线资源动态调控需求*/

    M_SPM_PATH_RECOVERY_SWITCH = 144,

    M_SPM_UGW_DEACTIVE_CAUSE_CTRL = 200,

    M_SPM_UGW_AAA_ALM_RESUME_CONTROL = 201,

    M_SPM_CM_CDRF_CTROL_AMACCESS    = 203,

    /* Add start by wangren 00167746 at 2011-01-24 UGWV9R9C0 for dpi硬件加速 */
    M_SPM_IPN_DPILOGIC_FUNC_SWITCH = 243, /*控制DPI硬件加速功能是否使能*/
    M_SPM_IPN_DPILOGIC_FUNC_HEARTBEAT = 244,  /*控制DPI硬件心跳检测功能是否使能以及DPI心跳检测故障*/
    /* Add end by wangren 00167746 at 2011-01-24 UGWV9R9C0 for dpi硬件加速*/

    M_SPM_AM_GTP_PROXY_CONTROL = 248,
    M_SPM_LI_SINGLE_IP_MULTI_PORT_CONTROL = 249,
    /* Added start by j00171840 at 2012-4-20 UGWV9R9c01 for CR20110818056:对强制归并的流量通过软参控制计费方式*/
    M_SPM_SM_FORCE_MERGE_METHOD = 301,
    /* Added end by j00171840 at 2012-4-20 UGWV9R9c01 for CR20110818056:对强制归并的流量通过软参控制计费方式*/
    M_SPM_CM_EVENTTRIGGER_SUPPORT_DIFF_RELEASE = 302,
    M_SPM_GUL_CONFLIT = 303,
    M_SPM_QOS_NOKEY_ATTR_SAE_TO_GGSN = 304,
    M_SPM_LOGIC_TCPBUFFER_TIME = 305,
     /*Added start by lixiaochen 129881 for 控制外部跟踪是否在CPU上处理at 2013-01-14*/
    M_SPM_PF_EXTERN_TRACE = 307,
    /*Added end by lixiaochen 129881 for 控制外部跟踪是否在CPU上处理at 2013-01-14*/
    M_SPM_CM_OCSC_HOLDING_TIMER_AMAN = 309,   //阿曼需求，command层收到异常返回码后启动holding-time定时器
    M_SPM_CM_OCSC_CCR_I_WAL_PERCENT = 310,   //阿曼需求，command层收到异常返回码后启动holding-time定时器
    M_SPM_CM_OCSC_CCR_TYPE_WAL_CTRL = 311,   //阿曼需求，command层收到异常返回码后启动holding-time定时器
    M_EMS_KPI_PDP_ACTIVE_SUCCESS_RATIO_RANG = 312,
    M_SPM_KPI_FW_SUCCESS_RATIO_RANG = 313,
    M_SPM_KPI_ALARM_THRESHOLD = 315,
    M_SPM_BYTE_CAN_BOARD_ACCESS = 316,  //single IP方案控制E F板是否允许板级接入:0 允许；1 不允许

    /* BEGIN: Added for 同步维护问题单DTS2014040304358，SGSN不带Qos版本时升级到R7, jiangxu 90004782 2014/4/24 */
    M_SPM_BYTE_QOS_UPGRADE_R7 = 325,
    /* END:   Added for 同步维护问题单DTS2014040304358，SGSN不带Qos版本时升级到R7, jiangxu 90004782 2014/4/24 */

    M_SPM_IP_IPSQM_EN_PKT_NUM = 401,
    M_SPM_IP_IPSQM_DE_PKT_NUM = 402,
    /* BEGIN: Added by yuehongwei, 2012/2/8   问题单号:PS9.2 SRU流控特性*/
    M_SPM_SRU_CPU_CTRL = 403,

    /* Added start by l00227142 at 2012-11-30  for CR20121128021——“移动特通需求--流量拥塞告警” */
    M_SPM_LI_CONGEST_TIMER = 408,
    /* Added end by l00227142 at 2012-11-30  for CR20121128021——“移动特通需求--流量拥塞告警” */

    /* Added start by dengchangqi 00181262 at 2013-03-01 V9R9C02 for 50%PCC内存模式 */
    M_SPM_SM_PCC_PRODUCT_MODE = 409,
    /* Added end by dengchangqi 00181262 at 2013-03-01 V9R9C02 for 50%PCC内存模式 */
    M_SPM_SM_PCC_ADAPTER_FOR_AIS = 501,
    M_SPM_AM_PROTOCOL_UPGRADE = 502,
    /* add start by yangyang 00161651  at 2012.10.18 for tcp 优化算法配置*/
     M_SPM_IPN_TCP_OPTIMIZE_ALGORITHM = 503,
     /* add end by yangyang 00161651  at 2012.10.18 for tcp 优化算法配置*/
    M_SPM_CM_OCSC_AISBYT504 = 504,

    M_SPM_CM_OCSC_QOS_INFORMATION = 505,
    M_SPM_SM_MSD_VAS_FAULT_PKT_ACTION = 507,
    M_SPM_SM_MSD_MAX_FD_NUM_PER_USER = 508,

    M_SPM_IPN_TCP_BUFCC_SIZE = 509,

    M_SPM_SM_FUI_DNS_PASS_MAX_NUM = 511,
    M_SPM_AM_AUTH_FLOWCONTROL_FLAG = 512,/* Added by panjinlei 00248472 at 20130911 智能流控特性 */
    M_SPM_CM_AUTH_FC_INTER_CTRL = 512, /* Added pcrf,ocs,aaa auth 接口消息流控使用 by z48729 */
    M_SPM_SM_L347_BUFFMBUF_AGE_TIME = 513,

    M_SPM_LI_SPUF_X3_TCP_MAXPACKETNUM_PPS = 514,
    M_SPM_LI_SPUF_X3_UDP_MAXPACKETNUM_PPS = 515,

    M_SPM_SM_GXGY_ADAPTER_FOR_AIS = 516,

    M_SPM_SCCG_SD_NORMAL_CEREATE_NUM = 525,
    M_SPM_SCCG_TIME_STAMP = 527,

    M_SPM_IPN_NUM_HOPS_FOR_ROUTE_EPSN = 528, /* 用于SCCG的Tethering特性中设置设备之间流量经过的路由跳数 */
    M_SPM_CM_PHGW_DIAM_PROXY = 538,
    M_SPM_CM_PHGW_OCSC_CHECKHOST = 539,
    M_SPM_CM_PHGW_FT_MOD = 540,
    M_SPM_CM_PHGW_CHINATEL_MOD = 549,
    /* 57号软参在pdsn产品改为555定义了当内容计费流节点资源耗尽时的处理动作，
    最低bit为五元组节点耗尽动作，最低第二bit为RG节点耗尽动作
    0为阻塞，1为Pass不计费*/
    M_SPM_SM_SFN_RESOURCE_EXHAULT_ACT_PDSN = 555,
    /* PDSN 产品53号软参在pdsn产品改为557 , 定义了pipeline功能是否打开标记
    取值范围为0-255，该软参默认值设置为0，pipeline功能关闭，如果非零，pipeline功能打开*/
    M_SPM_SM_PIPELINE_FLAG_PDSN = 557,
    M_SPM_CM_PHGW_FT_VOIP_QHT = 559,
    M_SPM_PDSN_UDP_CHECKSUM = 569,
    M_SPM_PDSN_AAA_ALARM_INTERVAL = 546,     /* AAA告警扫描server状态的间隔 */
    M_SPM_PDSN_AAA_ALARM_ACCUMULATE = 552,    /* 累计连续down的次数才上报告警 */
    M_SPM_PDSN_L2TP_INVALID_TUNL_EXIST = 560,
    M_SPM_CM_PHGW_EXPIRED_THRESHOLD = 572,
    M_SPM_SM_PDSN_THUNDER_HTTP_DETECTION = 575,
    M_SPM_CM_PHGW_EXIST_STORAGE_FILE = 583,
    M_SPM_CM_DIAM_ROUTE_FAILOVER  = 589,
    M_SPM_PDSN_L2TP_ICCN_LCP_FLAG = 590,
    /*Add by xsm00201057 20130304 for PDSNC06软参移植*/
    /*60号软参用来控制外层分片的老化时间，单位为250ms
      取值范围 1~255，缺省值120,若配置为0则取120*/
    M_SPM_PF_PDSN_EXTERIOR_FRAG_AGING_THR = 594,
    /*61号软参用来控制内层分片的老化时间，单位为250ms
      取值范围 1~255，缺省值120,若配置为0则取120*/
    M_SPM_PF_PDSN_INTERIOR_FRAG_AGING_THR = 595,
    /*End by xsm00201057 20130304 for PDSNC06软参移植*/
    /* Added start by l00103254 at 2011-07-30 UGWV9R10C01 for PDSN 五元组快速老化时间进行软参控制 */
    /* 68号软参在pdsn产品改为596 */
    M_SPM_IMSIMSISDN_SELECT_PDSN = 596,
    /* 66号软参在pdsn产品改为597 */
    M_SPM_SM_SAM_INDENTIFY_THRESHOLD_PDSN = 597, /*最大关联识别包数*/
    /* 98号软参在pdsn产品改为598 */
    M_SPM_SM_FD_QUICK_AGE_TIME_PDSN = 598,
    /* BEGIN: Added for PN:AX4D14214 用户流间隔超过2分钟的情况导致SIG识别率低 by x00110917, 2010/3/17 */
    /* 107号软参在pdsn产品改为599 */
    M_SPM_IPN_CACHE_FD_AGETIME_PDSN = 599,    /* 小五元组老化时间 1-255 表示 10s~2550s */
    /* END:   Added for PN:AX4D14214 用户流间隔超过2分钟的情况导致SIG识别率低 by x00110917, 2010/3/17 */
    /* Added end by l00103254 at 2011-07-30 UGWV9R10C01 for PDSN 五元组快速老化时间进行软参控制 */

    M_SPM_PDSN_LI_BAN = 574, /*PDSN LI ban功能*/ /*PDSN LI 增加 */
    M_SPM_LI_PDSNTAI_MAXSEQNUMDELTA = 602, /*PDSN LI 海外TAI功能*/ /*PDSN LI 增加 */

    M_SPM_AM_AAA_ALM_RESUME_CONTROL_PDSN = 604,
    M_SPM_LI_PDSNCONGEST_TIMER = 605, /*PDSN LI 国标X3 拥塞告警功能*/ /*PDSN LI 增加 */
    M_SPM_PF_PDSN_CAR_RETRIEVE_RATE = 606,
    M_SPM_SM_PDSN_L347_BUFFMBUF_AGE_TIME = 607,
    M_SPM_IPN_PDSN_DECIDE_MODE = 608, /* PDSN 内存模式，0:普通模式；1:内容计费模式 */

    M_SPM_PF_PDSN_GIDEFEND_DNUPPKT_RATION = 610, /*PDSN中设置下行比上行报文的比例阈值，超过该阈值，视为攻击行为*/
    M_SPM_PF_PDSN_GIDEFEND_PKT_PERIOD = 611,        /*PDSN中设置检测报文的周期*/
    M_SPM_PF_UGW_GIDEFEND_DNUPPKT_RATION = 613, /*UGW 中设置下行比上行报文的比例阈值，超过该阈值，视为攻击行为*/
    M_SPM_PF_UGW_GIDEFEND_PKT_PERIOD = 614,         /*UGW 中设置检测报文的周期*/
    M_SPM_PF_PDSN_GIDEFEND_FLAGS = 619,         /*PDSN/HSGW中识别攻击的标识信息*/
    M_SPM_PF_UGW_GIDEFEND_FLAGS = 620,         /*GUL中识别攻击的标识信息*/
    M_SPM_IPN_NUM_HOPS_FOR_ROUTE = 621, /* 用于UGW的Tethering特性中设置设备之间流量经过的路由跳数 */

    M_SPM_HSGW_DNS_BYTE_616 = 616,
    M_SPM_HSGW_DNS_BYTE_617 = 617,
    M_SPM_HSGW_DNS_BYTE_618 = 618,
    M_SPM_SM_ANTI_FRAUD_DNS_VOLUMN_RATIO = 650,             /*DNS防欺诈:周期内DNS流量比例阈值，缺省为80%*/
    M_SPM_SM_ANTI_FRAUD_DNS_TOTAL_VOLUMN = 651,             /*DNS防欺诈:DNS总流量阈值，缺省10K*/
    M_SPM_SM_ANTI_FRAUD_DNS_DN_VOLUMN_DEVIATION = 652,      /*DNS防欺诈:上下行流量偏差平均值阈值，缺省10*/
    M_SPM_CM_DIAM_DEBUG_SWITCH_P_BIT = 653,               /* 控制是否检查CCA消息的P Bit位 */

    M_SPM_AM_MSG_CON_RESEND_CAUSE = 659,      /*中移动失败PCC重传配置原因值*/

    M_SPM_BYTE_GX_SAME_PEER_RETRAN_NUM = 704,
    M_SPM_BYTE_GX_SAME_PEER_RETRAN_DELAY_TIME = 705,


    M_SPM_DEF_BYTE_END
}U_SOFTPARA_BYTE_VALUE;

/**
* @ingroup vrp_timer
* 定义vrp定时器类型，单次定时器。
 */
#ifndef VOS_TIMER_NOLOOP
#define VOS_TIMER_NOLOOP             0
#endif

/** SPU单板ACTIVE/STANDBY状态 */
typedef enum tagCRM_PRIMARY_INFO_ENUM
{
    E_CRM_ACTIVE = 0,       /**< 单板为ACTIVE状态 */
    E_CRM_STANDBY,          /**< 单板为STANDBY状态 */
    E_CRM_PRIMARY_NULL      /**< 无效状态 */
}  CRM_PRIMARY_INFO_ENUM ;


#ifndef __FWD_TO_CTRL_HDR__
#define __FWD_TO_CTRL_HDR__
typedef struct
{
    PF_USHORT usCtrlFlag;
	                       /*bit 15:为1表明是静态地址用户转板的激活信令
                              bit14-bit12:res
                              bit11-bit10:区分是否是转板报文跟踪
                                        00：UGW/MSD <-> NET/SP
                                        01：UGW <-> MSD
                                        10：MSD <-> VAS
                                        11：MSD <-> MSU
                              bit9:在bit7-bit6为10时有效，标识F染色帧的COLOR
    						  bit8:块转上下文标志
                              bit8:IPPM报文是否被跟踪
                              bit7-bit6:区分出是IPPM的控制报文还是其他别的报文
                                        00：正常信令报文；
                                        01：表示是IPPM的FM帧，PF识别出来后需要填一些字段
                                        10 :IPPM的FM染色帧
                              bit5-bit4:
                                        :当bit0(GtpuFlag)置为1时(用户面报文)，表示GTP报文是出GW的左侧(下行)还是右侧(上行).
                                        表示PMIP(GRE)用户面报文出GW的左侧(下行)还是右侧(上行)。
                                        00: 左侧GTP报文(下行), 01:右侧GTP报文(上行), 10: 左侧PMIP(GRE)(下行), 11:右侧PMIP(GRE)(上行)
                              bit3 : LiFlag,0: UP , 1:DN
                              bit2-bit1 : TraceFlag,00:UP_IN,01:UP_OUT,10: DN_IN,11:DN_OUT,
                              bit0 : GtpuFlag,1:indirect forwarding,0:非间接转发报文*/
    PF_USHORT usPktType;    /*报文类型:1-psf 2-gre ping*/
    PF_ULONG  ulDpeTimeStamp;
    PF_ULONG  ulSubIndex;
    PF_ULONG  ulVcpuId;
    PF_ULONG  ulModuleId;
    PF_ULONG  ulMsgCode;
    PF_ULONG  ulPdpIndex;   /* GSDBindex,PF上送控制面时，根据gtpuindex从GTPU表中获
                               取GSDBindex,从控制面收到报文后，根据该值调用AM接口
                               获取gtpuindex */
    PF_ULONG  ulVrfIndex;
} FWD_TO_CTRL_HDR;
#endif

typedef enum tagAM_CHECKSUM_MSG_CODE
{
    AM_CHECKSUM_L2TP_CTRL,
    AM_CHECKSUM_L2TP_DATA,
    AM_CHECKSUM_GTPP,
    AM_CHECKSUM_DHCP,
    AM_CHECKSUM_BUTT
}AM_CHECKSUM_MSG_CODE_E;

/** SPU单板备份模式类型定义 */
typedef enum tagCRM_BKUP_MODE_ENUM
{
    CRM_BKUP_LOAD_SHARING = 0, /**< 负荷分担备份模式 */
    CRM_BKUP_1_PLUS_1,         /**< 1+1备份模式 */
    CRM_BKUP_N_PLUS_1,         /**< N+1备份模式 */
    CRM_BKUP_TYPE_MAX          /**< 无效备份模式类型 */
} CRM_BKUP_MODE_ENUM ;

typedef enum
{
    SDB_NOT_BACKUP = 0,                                    /* 没有定时备份 */
    SDB_CREATE_BACKUP = 1,                             /* 创建备份 */
    SDB_UPDATEVERNOTCHANGE_BACKUP = 2,   /* 更新(版本不变)备份 */
    SDB_UPDATEV1TOV0_BACKUP = 3,            /* 更新(切换到V0)备份 */
    SDB_UPDATEV0TOV1_BACKUP = 4,              /* 更新(切换到V1)备份 */
    SDB_DELETE_BACKUP = 5,                        /* 删除备份 */
    SDB_PPP_UPDATE_BACKUP = 6,
    SDB_L2TP_UPDATE_BACKUP = 7,
    SDB_UPDATESESSIONID_BACKUP = 8 ,
    SDB_INVALID_BACKUP_TYPE = 9,                  /* 无效备份类型 */
    SDB_NOT_NEED_BACKUP = 10                          /* 无需发送备份消息的类型 */
} SDB_BACKUP_TYPE_E;

/* 修改对象通知的类型 */
typedef enum E_PERF_OBJ_CHANGE_TYPE
{
    E_PERF_OBJECT_ADD = 0,      /* 对象添加成功通知 */
    E_PERF_OBJECT_DEL,          /* 对象删除成功通知 */

    E_PERF_OBJECT_BUTT,
} E_PERF_OBJ_CHANGE_TYPE;


#define GTPC_IMSI_MSISDN_LENGTH 16


#define  TRC_DIRECTION_LEFT_IN_SGW          0x000
#define  TRC_DIRECTION_RIGHT_OUT_SGW        0x100
#define  TRC_DIRECTION_LEFT_IN_PGW          0x200
#define  TRC_DIRECTION_LEFT_IN_PGW_PMIP     0x210
#define  TRC_DIRECTION_RIGHT_OUT_PGW        0x300
#define  TRC_DIRECTION_RIGHT_IN_PGW         0x400
#define  TRC_DIRECTION_LEFT_OUT_PGW         0x500
#define  TRC_DIRECTION_LEFT_OUT_PGW_PMIP    0x510
#define  TRC_DIRECTION_RIGHT_IN_SGW         0x600
#define  TRC_DIRECTION_LEFT_OUT_SGW         0x700
#define  TRC_DIRECTION_IN_GGSN              0x800 /* zhangjinquan DTS2011082501761 2011-08-24 对于GGSN形态，应该用GGSN显示方向 */
#define  TRC_DIRECTION_OUT_GGSN             0x900 /* zhangjinquan DTS2011082501761 2011-08-24 对于GGSN形态，应该用GGSN显示方向 */
#define  TRC_DIRECTION_RIGHT_IN_UGW         0xa00
#define  TRC_DIRECTION_RIGHT_OUT_UGW        0xb00
/* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 start */
#define  TRC_DIRECTION_RIGHT_IN_UGW_ERR     0xc00
/* zhangjinquan DTS2011072204836  对于spud板需要能够抓到异常的ack包 2012-01-09 end   */


/* --------------------------------------------------------------------------- */
/* -----------------------------EMS 模块定义----------------------------- */
/* --------------------------------------------------------------------------- */
typedef enum tagEMS_DEBUG_MODULE_TYPE
{
    EMS_MODULE_TYPE_AM_GTPC           = 0x01,
    EMS_MODULE_TYPE_AM_LAP            = 0x02,
    EMS_MODULE_TYPE_AM_DHCP           = 0x03,
    EMS_MODULE_TYPE_AM_AUTH           = 0x04,
    EMS_MODULE_TYPE_AM_L2TP           = 0x05,
    EMS_MODULE_TYPE_AM_VOG            = 0x06,
    EMS_MODULE_TYPE_AM_PMIP           = 0x07,
    EMS_MODULE_TYPE_AM_S6B            = 0x08,


    EMS_MODULE_TYPE_CM_OSC            = 0x011,
    EMS_MODULE_TYPE_CM_PCRF           = 0x012,
    EMS_MODULE_TYPE_CM_ACCT           = 0x013,
    EMS_MODULE_TYPE_CM_CORE           = 0x014,
    EMS_MODULE_TYPE_SM                = 0x020,
    EMS_MODULE_TYPE_SM_MSD            = 0x021,
    EMS_MODULE_TYPE_SM_VOG            = 0x022,
    EMS_MODULE_TYPE_PF                = 0x030,

    /* PDSN */
    EMS_MODULE_TYPE_AM_CSN            = 64,
    EMS_MODULE_TYPE_AM_A11            = 65,
    EMS_MODULE_TYPE_AM_PPP            = 66,
    EMS_MODULE_TYPE_AM_AAA_AUTH_PDSN  = 67,
    EMS_MODULE_TYPE_AM_DIAM_AUTH_PDSN = 68,
    EMS_MODULE_TYPE_AM_LAP_PDSN       = 69,
    EMS_MODULE_TYPE_AM_DHCP_PDSN      = 70,
    EMS_MODULE_TYPE_AM_FA             = 71,
    EMS_MODULE_TYPE_AM_PMIPV6_PDSN    = 72,
    EMS_MODULE_TYPE_AM_RSVP           = 73,

    EMS_MODULE_TYPE_HSGW_CM_CORE           = 80,
    EMS_MODULE_TYPE_HSGW_CM_CDRF           = 81,
    EMS_MODULE_TYPE_HSGW_CM_OCSC           = 82,
    EMS_MODULE_TYPE_HSGW_CM_PCEF           = 83,
    EMS_MODULE_TYPE_HSGW_CM_KERNEL         = 84,
    EMS_MODULE_TYPE_HSGW_CM_POSTPAID       = 85,
    EMS_MODULE_TYPE_HSGW_CM_PREPAID        = 86,


}E_EMS_DEBUG_MODULE_TYPE;


#define IPV6_ADDR_ANY        0x0000U
#define IPV6_ADDR_UNICAST    0x0001U
#define IPV6_ADDR_MULTICAST  0x0002U
#define IPV6_ADDR_LOOPBACK   0x0010U
#define IPV6_ADDR_NODELOCAL  0x0010U
#define IPV6_ADDR_LINKLOCAL  0x0020U
#define IPV6_ADDR_SITELOCAL  0x0040U
#define IPV6_ADDR_GLOBAL     0x0100U
#define IPV6_ADDR_COMPATv4   0x0080U
#define IPV6_ADDR_SCOPE_MASK 0x00f0U
#define IPV6_ADDR_MAPPED     0x1000U
#define IPV6_ADDR_RESERVED   0x2000U /* reserved address space */

/* VRP_MODULE_IPV6  */
#ifndef AF_INET6
#define AF_INET6        29             /* added by mayun for IPv6 */
#endif

#define AM_TRC_IPV6_LEN 16

//Begin:added by c00110835 for 跟踪适配
typedef struct tagUGW_EXTERN_INTF_TRACE_S
{
    ULONG  ulMsgClass;      //消息类型
    ULONG  ulGtpMsgType;    //消息掩码
    ULONG  ulLocalIpAddr;   //本端IP
    UCHAR  aucLocalIpv6Addr[AM_TRC_IPV6_LEN];   //本端Ipv6
    ULONG  ulVpnIndex;      //本端IP绑定的VPN索引
    ULONG  ulPeerIpAddr;    //对端IP
    UCHAR  aucPeerIpv6Addr[AM_TRC_IPV6_LEN];  //对端IPv6
    ULONG  ulMsgLen;        //消息长度
    USHORT usApnIndex;      //APN索引:GNGP APN粒度开启跟踪
    UCHAR  ucAliaApnFlag;   //别名APN标志位:GNGP APN粒度开启跟踪
    UCHAR  ucRev;
}UGW_EXTERN_INTF_TRACE_S;

typedef struct tagUGW_EXTERN_INTF_TRACE_INFO_S
{
    UCHAR* pucTrcMsg;
    UCHAR  ucMsgType;
    UCHAR  ucVersion;
    USHORT usMsgLen;
    ULONG  ulMsgClass;      //消息类型
    ULONG  ulGtpMsgType;    //消息掩码
    ULONG  ulDirection;
    ULONG  ulPeerIp;
    ULONG  ulIntfType;
    ULONG  ulLocalIp;
    ULONG  ulSourceIP;
    ULONG  ulVpnIndex;
    USHORT usPeerPort;
    USHORT usLocalPort;
    UCHAR  ucIpAddrType; //ipv4或ipv6
    USHORT usApnIndex;
    UCHAR  ucAliaApnFlag;
    UCHAR  aucLocalIpv6Addr[AM_TRC_IPV6_LEN];   //本端Ipv6
    UCHAR  aucPeerIpv6Addr[AM_TRC_IPV6_LEN];  //对端IPv6
}UGW_EXTERN_INTF_TRACE_INFO_S;


//End:added by c00110835 for 跟踪适配

/* Added end by fanlianrong kf25870 on 2010-12-04 for PGPV2R5 OMADA-TCP跟踪 */
/* SGW S4/S11接口的消息定义(业务组使用)*/
#define  S4S11_MSGTYPE_PATH         0x01
#define  S4S11_MSGTYPE_GTP          0x02
#define  S4S11_MSGTYPE_PMIPV6       0x04
#define  S4S11_MSGTYPE_DHCPV6       0x08
#define  S4S11_MSGTYPE_DHCPV4       0x10
#define  S4S11_MSGTYPE_IPV6         0x20
#define  S4S11_MSGTYPE_EMS_SIGNALING    0x40
#define  S4S11_MSGTYPE_ALL          0x7F

/* SGW S5/S8接口的消息定义(业务组使用)*/
#define  S5S8_MSGTYPE_PATH         0x01
#define  S5S8_MSGTYPE_GTP          0x02
#define  S5S8_MSGTYPE_PMIPV6       0x04
#define  S5S8_MSGTYPE_DHCPV4       0x08
#define  S5S8_MSGTYPE_DHCPV6       0x10
#define  S5S8_MSGTYPE_IPV6         0x20
#define  S5S8_MSGTYPE_ALL          0x3F

/* PGW S5/S8/S2a接口的消息定义(业务组使用)*/
#define  S5S8S2A_MSGTYPE_PATH         0x01
#define  S5S8S2A_MSGTYPE_GTP          0x02
#define  S5S8S2A_MSGTYPE_PMIPV6       0x04
#define  S5S8S2A_MSGTYPE_DHCPV4       0x08
#define  S5S8S2A_MSGTYPE_DHCPV6       0x10
#define  S5S8S2A_MSGTYPE_IPV6         0x20
#define  S5S8S2A_MSGTYPE_PPP          0x40
#define  S5S8S2A_MSGTYPE_EMS_SIGNALING          0x80
#define  S5S8S2A_MSGTYPE_ALL          0xFF

typedef struct tagUDPHDR
{
    USHORT    uh_usSPort;        /* source port */
    USHORT    uh_usDPort;        /* destination port */
    SHORT     uh_sULen;          /* udp length */
    USHORT    uh_usSum;          /* udp checksum */
}UDPHDR_S;

#define IPV6_HEADER_LEN     40
#define UDP_HEADER_LENGTH   8   /*udp 头长度*/

#define IPV6_ICMP_PRO      58
#define IPV6_UDP_PRO       17
#define SDB_MAX_CONTEXT_NUM 12500   /*1250*/

/*IPV6 FIXED HEADER */
typedef struct tagIpv6hdr {
#if (UGW_BYTE_ORDER == UGW_LITTLE_ENDIAN)
    ULONG        traffic_class_1:4,
                 version:4,
                 flow_lbl_1:4,
                 traffic_class_2:4,
                 flow_lbl_2:16;
#else
    ULONG        version:4,
                 traffic_class:8,
                 flow_lbl:20;
#endif

    USHORT       payload_len;
    UCHAR        nexthdr;
    UCHAR        hop_limit;

    in6_addr    saddr;
    in6_addr    daddr;
}VOS_PACKED IPV6HDR_S;


/**
* @ingroup  v_mcque
* 队列信息中队列名字长度(包含结束符)。
*/
#define MCQUEUE_INFO_NAME_LEN 32

/**
* @ingroup  v_mcque
*
* 该结构用于保存队列信息。
*/
typedef struct tagMCQueInfo
{
    VOS_CHAR achQueName[MCQUEUE_INFO_NAME_LEN]; /* 队列名字 */
    VOS_UINT32 ulHeader;         /* 队列魔术字 */
    VOS_UINT32 ulState;          /* 队列状态 */
    VOS_UINT32 ulMod;            /* 队列模式 */
    VOS_UINT32 ulLength;         /* 队列长度 */
    VOS_UINT32 ulCurrentLen;     /* 队列当前长度 */
} MC_QUE_Info;


#ifndef _SYS_MSG_S_
#define _SYS_MSG_S_
typedef struct  tagSYS_MSG
{
    USHORT usMessageType;              /*用于指示发送或接收*/
    USHORT usPririty;                  /*送优先级（用户自己定义）,支持4个优先级 */
    ULONG  ulSrcModuleID;               /*源模块号*/
    ULONG  ulDstModuleID;               /*目标模块号*/
    ULONG  ulSequence;                  /*发送序号,RPC专用*/

    ULONG  ulSrcSlotID;                 /* 源槽位号 */
    ULONG  ulDstSlotID;                 /* 目的槽位号 */
    UCHAR  ucMsgType;                   /* 消息类型，如PDU, TIMER, REQUEST, NOTIFY... */
    UCHAR  ucMsgBodyStyle;              /*用于指明消息头和消息体是否是一体的,在FSU中主要用于区分是否MBuf方式*/
    USHORT usMsgCode;                 /* 消息码，具体消息类型的细分 */

    USHORT   usResponseType;             /* 是否要求接收方用户应答：ACK/ NOACK/NEGACK*/
    USHORT   usFrameLen;                 /* frame content 的长度 ，用户数据区长度   */
    VOID    *ptrMsgBody;                 /*消息体指针*/
    USHORT   usAppSeqNum;                /*应用层系列号，用于发送方和接收方请求应答之间建立关联*/
    USHORT   usReserved;                 /*保留 ，以后扩充使用*/
}  MSG_HDR_S, SYS_MSG_S;
#endif

typedef struct
{
    USHORT usApnIndex;
    USHORT usDay;

    UCHAR ucHour;
    UCHAR ucMinute;
    USHORT usUnlimited;
}DHCPS_EXPIRED_REC_S;

#ifdef __WIN32_PLATFORM__
#define MAX_APN_NUM 100
#else
#define MAX_APN_NUM 3000                   /*最大可配APN数目*/
#endif

enum E_PERF_UNIT
{
    PERF_TYPE_SGW_FW,
    PERF_TYPE_SGW_APN_FW,
    PERF_TYPE_SGW_S5,
    PERF_TYPE_SGW_S5_ERR,
    PERF_TYPE_S11,
    PERF_TYPE_SGW_SM,
    PERF_TYPE_SGW_SM_APN,
    PERF_TYPE_SGW_USERS,
    PERF_TYPE_SGW_CDR,
    PERF_TYPE_PGW_FW,
    PERF_TYPE_PGW_APN_FW,
    PERF_TYPE_PGW_S5,
    PERF_TYPE_PGW_S5_ERR,
    PERF_TYPE_PGW_SM,
    PERF_TYPE_PGW_SM_APN,
    PERF_TYPE_PGW_USERS,
    PERF_TYPE_PGW_CDR,
    PERF_TYPE_GW_FW,
    PERF_TYPE_SM,
    PERF_TYPE_FW,
    PERF_TYPE_GCDR,
    PERF_TYPE_GTP,
    PERF_TYPE_AAA,
    PERF_TYPE_PPPC,
    PERF_TYPE_L2TPC,
    PERF_TYPE_DHCP,
    PERF_TYPE_SM_BY_BIZID,
    PERF_TYPE_FW_BY_BIZID,
    PERF_TYPE_USERS,
    PERF_TYPE_7PARSE,
    PERF_TYPE_GY,
    PERF_TYPE_PREPAIDSERVICE,
    PERF_TYPE_MBMS,
    PERF_TYPE_DIFF_PDPCONTEXT,
    PERF_TYPE_CLIT_PERFMEA,
    PERF_TYPE_FLOW_NODES,
    PERF_TYPE_CPU_RES,
    PERF_TYPE_BRD_RES,
    PERF_TYPE_GTP_TO_CG,
    PERF_TYPE_APN_SM_3G,
    PERF_TYPE_APN_SM_2G,
    PERF_TYPE_APN_SM_STATUS,
    PERF_TYPE_IMSI_GCDR,
    PERF_TYPE_APN_AAA,
    PERF_TYPE_APN_FW,
    PERF_TYPE_APN_SM_BY_BIZID,
    PERF_TYPE_HPLMN_SM,
    PERF_TYPE_SGSN_SM,
    PERF_TYPE_GX,
    PERF_TYPE_APN_GX,
    PERF_TYPE_PCRF_GX,
    PERF_TYPE_PCC,
    PERF_TYPE_APN_PCC,
    PERF_TYPE_PCRF_PCC,
    PERF_TYPE_SPGW_SM,
    PERF_TYPE_SPGW_SM_APN,
    PERF_TYPE_GW_SM,
    PERF_TYPE_GW_APN_FW,
    PERF_TYPE_SPGW_USERS,
    PERF_TYPE_APN_L2TPC,
    PERF_TYPE_PHYPORT,
    PERF_TYPE_ERR_CAUSE,
    PERF_TYPE_IPPM,
    PERF_TYPE_SPGW_APN_FW,
    PERF_TYPE_GW_USERS,
    PERF_TYPE_AAA_DIAMETER,
    PERF_TYPE_IPSEC_SA,
    PERF_TYPE_TUNNEL_IPSEC_SA,
    PERF_TYPE_VUGW_SM,
    PERF_TYPE_VUGW_FW,
    PERF_TYPE_HOMEZONE,
    PERF_TYPE_GRE,
    PERF_TYPE_7PARSE_HTTP_HEADER,
    PERF_TYPE_BWM,
    PERF_TYPE_PGW_CLIT_PERFMEA,
    PERF_TYPE_GCF,
    PERF_TYPE_CMD_OCS,
    PERF_TYPE_MSCC_OCS,
    PERF_TYPE_VPLMN_SM,
    PERF_TYPE_VPLMN_FW,
    PERF_TYPE_GW_SM_APN,
    PERF_TYPE_PREPAIDSERVICE_OCS,
    PERF_TYPE_IPSQM_ENODEB,
    PERF_TYPE_VUGW_TCPPROXY,
    PERF_TYPE_MSE_SERVER_IP,
    PERF_TYPE_SCCG_SM,
    PERF_TYPE_SCCG_SM_APN,
    PERF_TYPE_SCCG_SM_NASIP,
    PERF_TYPE_SCCG_FW,
    PERF_TYPE_SCCG_FW_APN,
    PERF_TYPE_SCCG_FW_NASIP,
    PERF_TYPE_SCCG_PGW_CDR,
    PERF_TYPE_SCCG_GCDR,
    PERF_TYPE_SCCG_GTP,
    PERF_TYPE_SCCG_7PARSE,
    PERF_TYPE_SCCG_7PARSE_HTTP_HEADER,
    PERF_TYPE_SGW_CLIT_PERFMEA,
    PERF_TYPE_SCCG_GY,
    PERF_TYPE_SCCG_PREPAIDSERVICE,
    PERF_TYPE_SCCG_GTP_TO_CG,
    PERF_TYPE_SCCG_GX,
    PERF_TYPE_SCCG_PCRF_GX,
    PERF_TYPE_SCCG_BWM,
    PERF_TYPE_SCCG_GCF,
    PERF_TYPE_SCCG_CMD_OCS,
    PERF_TYPE_SCCG_MSCC_OCS,
    PERF_TYPE_SCCG_PREPAIDSERVICE_OCS,
    PERF_TYPE_EPRPDYN_S5S8PGW,
    PERF_TYPE_EPRPDYN_S11SGW,
    PERF_TYPE_EPRPDYN_S4SGW,
    PERF_TYPE_EPRPDYN_S5S8SGW,
    PERF_TYPE_MSE_SERVER_GROUP,
    PERF_TYPE_MSE_USERS,
    PERF_TYPE_IPSQM,
    PERF_TYPE_URL_REDIRECT,
    PERF_TYPE_VSCCG_SM,
    PERF_TYPE_VSCCG_FW,
    PERF_TYPE_PREPAIDSERVICE_3GPP_AAA,
    PERF_TYPE_SERVICE_INSTANCE,
    PERF_TYPE_SCCG_SERVICE_INSTANCE,
    PERF_TYPE_SCTP,
    PERF_TYPE_EPSN_SCTP,
    PERF_TYPE_VOG_FW,
    PERF_TYPE_VOG_SVC_OPT,
    PERF_TYPE_PDSN_FW,
    PERF_TYPE_PDSN_A11,
    PERF_TYPE_PDSN_AAA,
    PERF_TYPE_PDSN_PPP,
    PERF_TYPE_PDSN_L2TP,
    PERF_TYPE_PDSN_FA,
    PERF_TYPE_PDSN_PMIP,
    PERF_TYPE_PDSN_RSVP,
    PERF_TYPE_PDSN_GY,
    PERF_TYPE_PDSN_OCS,
    PERF_TYPE_PDSN_SESSION,
    PERF_TYPE_PDSN_LI,
    PERF_TYPE_PDSN_L7PARSE,
    PERF_TYPE_PDSN_L7PARSE_HTTP_HEADER,
    PERF_TYPE_EPSN_PCRF_HOST_GX,
    PERF_TYPE_PDSN_PCF_FW,
    PERF_TYPE_PDSN_PCF_CM,
    PERF_TYPE_PDSN_DN_SESSION,
    PERF_TYPE_PDSN_DN_FW,
    PERF_TYPE_PDSN_VPDSN_SM,
    PERF_TYPE_PDSN_VPDSN_FW,
    PERF_TYPE_PDSN_GX,
    PERF_TYPE_PDSN_PCRF_GX,
    PERF_TYPE_IP_POOL,
    PERF_TYPE_HSGW_FW,
    PERF_TYPE_HSGW_STA,
    PERF_TYPE_HSGW_S2A,
    PERF_TYPE_HSGW_RSVP,
    PERF_TYPE_HSGW_SESSION,
    PERF_TYPE_HSGW_PCF_FW,
    PERF_TYPE_HSGW_PCF_CM,
    PERF_TYPE_HSGW_GCDR,
    PERF_TYPE_HSGW_GTP,
    PERF_TYPE_HSGW_GX,
    PERF_TYPE_HSGW_DNS,
    PERF_TYPE_DIAMETER_DRA,
    PERF_TYPE_EPSN_DIAMETER_DRA,
    PERF_TYPE_PCRF_HOST_GX,
    PERF_TYPE_PCRF_HOST_PCC,
    PERF_TYPE_ANTI_SPOOFING,
    PERF_TYPE_EPSN_ANTI_SPOOFING,
    PERF_TYPE_KEY_RESOURCES_MONITOR,
    PERF_TYPE_BUTT
};

enum E_PERF_ENTITY
{
    PERF_ENTITY_BEGIN = 10000,

    PERF_TYPE_SGW_SM_BEGIN =  13000,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_GTP_PATH_NUM,
    PERF_TYPE_SGW_SM_S5S8_GTP_PEER_EQUIP_RESTARTS,
    PERF_TYPE_SGW_SM_S5S8_GTP_C_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_GTP_U_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_PMIP_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_PMIP_PATH_NUM,
    PERF_TYPE_SGW_SM_S11_S4_CURRENT_GTP_PATH_NUM,
    PERF_TYPE_SGW_SM_S11_S4_GTP_PEER_EQUIP_RESTARTS,
    PERF_TYPE_SGW_SM_S11_S4_GTP_C_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_S11_S4_GTP_U_PATH_INTERRUPTIONS,
    PERF_TYPE_SGW_SM_CRE_BEARER_CONTEXT_REQ,
    PERF_TYPE_SGW_SM_SUCC_BEARER_CONTEXT_CRE,
    PERF_TYPE_SGW_SM_ALL_BEARER_GROSS_LIFETIME_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_ALL_BEARER_GROSS_LIFETIME_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_GROSS_NEW_CRE_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_MAX_SIM_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_AVG_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_AVG_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_AVG_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED,
    PERF_TYPE_SGW_SM_PEAK_CRE_BEARER_REQ_RATE_S11_S4,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_SDB_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_LICENSE_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_QOS_RES,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_DEL_S11_S4_NON_EXIST_CONTEXT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_VER_NOT_SUPPORT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INVAL_LENGTH,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SERVICE_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INCORRECT_MAN_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_MISS_MAN_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_INCORRECT_OPT_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SYS_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_TFT_SEM_ERR,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_TFT_SYN_ERR,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SEM_ERR_PKT_FILTER,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_SYN_ERR_PKT_FILTER,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_MISS_OR_UNKNOWN_APN,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_UNEXP_REPEATED_IE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_GRE_KEY_NOT_FOUND,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_REALLOC_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_DENIED_RAT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_PREFERED_PDN_TYPE_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_ALL_DYNAMIC_ADDR_OCCUPIED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_UE_CONTEXT_WITHOUT_TFT_ALREADY_ACT,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_PROTOCOL_NOT_SUPPORTED,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_MEM_AVAILABLE,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_USER_AUTH_FAIL,
    PERF_TYPE_SGW_SM_FAIL_BEARER_CONTEXT_CRE_S11_S4_NO_SUBSCRIPTION,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS,
    PERF_TYPE_SGW_SM_RCV_IPV6_RS_FROM_UE_PKTS,
    PERF_TYPE_SGW_SM_SEND_IPV6_RA_PKTS,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_CRT,
    PERF_TYPE_SGW_SM_MEAN_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_MEAN_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_MAX_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_MAX_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_SUCC_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_FAIL_NUM_MME_DEDICAT_BEARER_DEL,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_MOD_NO_QOS_U,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_SUCC_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_FAIL_NUM_PGW_DEDICAT_BEARER_MOD_QOS_U,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_SUCC_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_FAIL_NUM_HSS_QOS_MOD,
    PERF_TYPE_SGW_SM_ATTEMPT_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_SUCC_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_FAIL_NUM_UE_BEARER_RES_MOD,
    PERF_TYPE_SGW_SM_OWN_CUST_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_REJECT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_OWN_CUST_BEARER_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_ROAM_BEARER_REJECT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_S1_RELEASE_REJECT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_ATTEMPT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_ACCEPT_COUNT,
    PERF_TYPE_SGW_SM_NET_SERV_REQ_REJECT_COUNT,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_PDP_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_MAX,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_AVERAGE,
    PERF_TYPE_SGW_SM_MAX_SIMULTANEOUSLY_ATTACHED_ACTIVE,
    PERF_TYPE_SGW_RCV_SUSPEND_NOTIFICATION_MSG,
    PERF_TYPE_SGW_SND_SUCESS_SUSPEND_ACK_MSG,
    PERF_TYPE_SGW_RCV_RESUME_NOTIFICATION_MSG,
    PERF_TYPE_SGW_SND_SUCESS_RESUME_ACK_MSG,
    PERF_TYPE_SGW_SMFAIL_BEARER_CONTEXT_CRE_EXTERNAL,
    PERF_TYPE_SGW_SM_AUX_BEGIN,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_GTP_PATH,
    PERF_TYPE_SGW_SM_S5S8_CURRENT_PMIP_PATH,
    PERF_TYPE_SGW_SM_S11_CURRENT_GTP_PATH,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4_REALTIME,
    PERF_TYPE_SGW_SM_NUM_EPS_BEARER,
    PERF_TYPE_SGW_SM_NUM_EPS_SESSION,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_CONTEXT_CHARGE_PDP_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT_REALTIME,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_S11_S4_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CURRENT_ACT_BEARER_CONTEXTS_DEDICATED_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CURRENT_ACT_SESSIONS_S11_S4_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CRE_BEARER_CONTEXT_REQ_AUX,
    PERF_TYPE_SGW_SM_NUM_EPS_BEARER_AUX,
    PERF_TYPE_SGW_SM_NUM_EPS_SESSION_AUX,
    PERF_TYPE_SGW_SM_ROAMING_SESSION_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_ROAMING_BEARER_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_CONTENT_CHARGE_PDP_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_SIMULTANEOUSLY_ATTACHED_ACTIVE_CURRENT_REALTIME_AUX,
    PERF_TYPE_SGW_SM_END,

    PERF_TYPE_PGW_S5_BEGIN =  16000,
    PERF_TYPE_PGW_S5_RCV_GTP_ERR_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_UNEXPECTED_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_RCV_GTP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_GTP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_GTP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_GTP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_CRE_DEFAULT_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_CRE_DEFAULT_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_CRE_DEDICATED_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_CRE_DEDICATED_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_CRE_DEDICATED_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_UPD_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_UPD_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_UPD_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_DEL_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_SUCC_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_FAIL_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_DEL_BEARER_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_SUCC_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_FAIL_DEL_BEARER_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_REQ_BEARER_RES_MOD_MSG,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_ERR_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_UNEXPECTED_SIG_TRAFFIC_PKTS,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PEAK_PKTSPS,
    PERF_TYPE_PGW_S5_RCV_PMIP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_SND_PMIP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_SND_PMIP_PATH_REQ_MSG,
    PERF_TYPE_PGW_S5_RCV_PMIP_PATH_RSP_MSG,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_EQUAL_ZERO_PBU_MSG,
    PERF_TYPE_PGW_S5_SND_STATUS_SMALLER_TO128_PBA_MSG,
    PERF_TYPE_PGW_S5_SND_STATUS_BIGER_THAN128_PBA_MSG,
    PERF_TYPE_PGW_S5_SND_BRI_MSG,
    PERF_TYPE_PGW_S5_RCV_STATUS_SMALLER_TO128_BRA_MSG,
    PERF_TYPE_PGW_S5_RCV_STATUS_BIGER_THAN128_BRA_MSG,
    PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_OFFER_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_ACK_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_NAK_FROM_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_DIS_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_REQ_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_DEC_TO_SERVER_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV4_REL_TO_SERVER_PKTS,
    PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS,
    PERF_TYPE_PGW_RCV_IPV6_RS_FROM_UE_PKTS,
    PERF_TYPE_PGW_SEND_IPV6_RA_FROM_UE_PKTS,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG_FOR_HO_HSGW,
    PERF_TYPE_PGW_S5_SND_SUCC_PBA_MSG_FOR_HO_HSGW,
    PERF_TYPE_PGW_S5_RCV_LIFETIME_NOT_EQUAL_ZERO_PBU_MSG_FOR_HO_LTOC,
    PERF_TYPE_PGW_S5_SND_SUCC_PBA_MSG_FOR_HO_LTOC,
    PERF_TYPE_PGW_S5_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_CTOL,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_CTOL,
    PERF_TYPE_PGW_S2B_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S2B_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S5_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_WTOL,
    PERF_TYPE_PGW_S2A_RCV_CRE_DEFAULT_BEARER_REQ_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S2A_SND_SUCC_CRE_DEFAULT_BEARER_RSP_MSG_FOR_HO_LTOW,
    PERF_TYPE_PGW_S5_AUX_BEGIN,
    PERF_TYPE_PGW_S5_RCV_GTP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_SND_GTP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_RCV_PMIP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_SND_PMIP_SIG_TRAFFIC_PKTS_AUX,
    PERF_TYPE_PGW_S5_END,

    PERF_ENTITY_BUTT
};

/* 系统消息类型定义 */
#ifndef _MsgType_E_
#define _MsgType_E_
enum ucMsgType
{
    /* 和FSU共用的消息类型 */
    MSG_TIMER,
    MSG_PDU,
    MSG_NOTIFY,
    MSG_REQUEST,
    MSG_ACK,

    /* 只有主控板使用的消息类型 */
    MSG_CONF,
    MSG_BACKUP,     /* 数据备份消息 Added by 李乃生 */

    MSG_SPU_TEST,

    /* 请在此最加新的消息类型 */
    MSG_TYPE_END
};
#endif

typedef struct tagAM_CTX_APN_INFO_S
{
    USHORT usApnIndex;
    USHORT usVirtualapnIndex;
    USHORT usNoConfigApnIndex;
    USHORT usAliaCdbIndex;
    UCHAR ucVirtualapnFlag;
    UCHAR aucReserved[3];
}AM_CTX_APN_INFO_S;


/* 强制打印输出缓冲区的内容 */
#define PTM_PRINT_EXCEPTION_END PTM_Print_Exception_End

/* 打印异常字符窜 */
#define PTM_PRINT_EXCEPTION_INFO PTM_Print_Exception_Info
#if 0
/* 打印异常计数，形如abc=1 */
#define PTM_PRINT PTM_Print_With_Equal

/* 打印配置，形如abc:1 (这样在gm上批量执行调试命令时，不会对结果进行累加)*/
#define PTM_PRINT_WITH_DOT PTM_Print_With_Dot

/* 打印异常计数，形如abc=1 */
#define PTM_PRINT_EXCEPTION     PTM_Print_Exception
#endif
/* 循环打印某异常计数，适用场景:不对异常计数进行实际命名 */
#define PTM_PRINT_EXCEPTION_LOOP PTM_Print_Exception_Loop
#define PTM_PRINT_STRING_WITH_ARGUMENTS PTM_Print_String_With_Arguments

#ifndef __tabSPINLOCK_T__
#define __tabSPINLOCK_T__
typedef struct
{
  volatile unsigned int lock;
} spinLock, spinlock_t;
#endif


#ifdef __X86_PLATFORM__
#define PGP_SpinLockNoSchedule(pstLock)                   MEM_SpinLockCTL(pstLock,__FILE__, __LINE__)
#define PGP_SpinTryLockNoSchedule(pstLock)                MEM_SpinTryLockCTL(pstLock,__FILE__, __LINE__)
#define PGP_SpinUnlockNoSchedule(pstLock)                 MEM_SpinUnlockCTL(pstLock, __FILE__, __LINE__)

#define PGP_RWReadLockNoSchedule(pstLock)                 MEM_RWReadLockCTL(pstLock)
#define PGP_RWReadUnlockNoSchedule(pstLock)               MEM_RWReadUnlockCTL(pstLock)
#define PGP_RWWriteLockNoSchedule(pstLock)                MEM_RWWriteLockCTL(pstLock)
#define PGP_RWWriteUnlockNoSchedule(pstLock)              MEM_RWWriteUnlockCTL(pstLock)
#else
#define PGP_SpinLockNoSchedule(pstLock)                   spin_lock(pstLock)
//#define PGP_SpinTryLockNoSchedule(pstLock)                spin_trylock(pstLock)
#define PGP_SpinUnlockNoSchedule(pstLock)                 spin_unlock(pstLock)

#define PGP_RWReadLockNoSchedule(pstLock)                 VOS_MCRWReadLock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWReadUnlockNoSchedule(pstLock)               VOS_MCRWReadUnlock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWWriteLockNoSchedule(pstLock)                VOS_MCRWWriteLock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#define PGP_RWWriteUnlockNoSchedule(pstLock)              VOS_MCRWWriteUnlock(*pstLock, (VOS_CHAR*)__FILE__, __LINE__)
#endif


// SG间使用
#define PGP_ShrRWLockCreate(name,plock)  VOS_MCRWLockCreate(name,plock,1)

typedef enum tagDBG_LOG_LEVEL
{
    DBG_LOG_INFO,           /* 0 事件记录，对应诊断日志中"INFO" */
    DBG_LOG_WARNING,        /* 1告警信息，对应诊断日志中" WARNING" */
    DBG_LOG_ERROR,          /* 2 错误信息，对应诊断日志中" ERROR" */
    DBG_LOG_END             /* 3 No use */
}DBG_LOG_LEVEL_E;

#define PGP_TmNowInSec VOS_Tm_NowInSec

#define VOS_StrCmp(x,y) strcmp(x,y)


/*************************************************
**** This Macro get the handle value of DLL node ****
**************************************************/
#define DLL_GET_HANDLE(pNode)	((pNode)->ulHandle)

#define UDPS_SET_CHECK_SUM_ENABLE(pstNode) ((pstNode)->ucControlCheckSum |= 1)

#define  PGP_SYS_MSG(pMsgBuff)              ((SYS_MSG_S*)((UCHAR *)(pMsgBuff) - sizeof(SYS_MSG_S)))
#define  RTD_SET_MSGCODE(pMsg, MsgCode)     (PGP_SYS_MSG(pMsg)->usMsgCode = (MsgCode))


/*==============================================*
*      constants or macros define              *
*----------------------------------------------*/

typedef struct tag_Fwd_ComChannel
{
    PF_UCHAR  ucMsgCode;                  /* 模块的消息码，当前转发和平台都没有使用，可以留给业务做扩展使用 */

    union
    {
        PF_UCHAR  ucPriority;
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucPriority:1;  /* PF通过Priority在PPE头中做标记：
                                    Priority=H标记为Inter-CPU Message、Priority=L标记为Inter-CPU Signal */

            PF_UCHAR ucOrdered:1;  /* 报文是否保序，Ordered=1，标记报文需要保序，PF按Hash算法，
                                   将报文转发至固定的vcpu接收队列；Ordered=0，标记报文不需要保序，
                                   PF以轮询方式，将报文转发至不同的vcpu接收队列 */
            PF_UCHAR ucMsgType:6;   /*msg type*/
        #else
            PF_UCHAR ucMsgType:6;   /*msg type*/
            PF_UCHAR ucOrdered:1;  /* 报文是否保序，Ordered=1，标记报文需要保序，PF按Hash算法，
                                   将报文转发至固定的vcpu接收队列；Ordered=0，标记报文不需要保序，
                                   PF以轮询方式，将报文转发至不同的vcpu接收队列 */

            PF_UCHAR ucPriority:1;  /* PF通过Priority在PPE头中做标记：
                                    Priority=H标记为Inter-CPU Message、Priority=L标记为Inter-CPU Signal */
		#endif
        }s;
    }Priority;

    PF_USHORT usStake;                     /* 报文的开始字节偏移长度*/

    union
    {
        PF_USHORT usDstCompInfo;               /*comp type + submodule id*/
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucDstCompTypeHi:6;     /* 目的组件类型 high 6 bit*/
            PF_UCHAR ucDstCompRsv:2;
            PF_UCHAR ucDstSubModuleId:2;    /* 目的子模块Id,保留不用 */
            PF_UCHAR ucDstCompTypeLo:6;     /* 目的组件类型 low 6 bit*/
        #else
            PF_UCHAR ucDstCompRsv:2;
            PF_UCHAR ucDstCompTypeHi:6;     /* 目的组件类型 high 6 bit*/
            PF_UCHAR ucDstCompTypeLo:6;     /* 目的组件类型 low 6 bit*/
            PF_UCHAR ucDstSubModuleId:2;    /* 目的子模块Id */
        #endif
        }s;
    }DstModule;

    union
    {
        PF_USHORT usDstNode;               /* slot/cpu/vcpu的混合编码 */
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
                PF_UCHAR ucDstCpuId:3;             /* 目的CPU */
                PF_UCHAR ucDstSlotId:5;            /* 目的逻辑槽位号 */
                PF_UCHAR usDstOSSGIndex:7;         /*目的Vcpu的逻辑进程id */
                PF_UCHAR ucDstSGReserve:1;
        #else
                PF_UCHAR ucDstSlotId:5;            /* 目的逻辑槽位号 */
                PF_UCHAR ucDstCpuId:3;             /* 目的CPU */
                PF_UCHAR ucDstSGReserve:1;
                PF_UCHAR usDstOSSGIndex:7;           /*目的Vcpu的逻辑进程id */
        #endif
        }s;
   }DstNode;

    union
    {
        PF_USHORT usSrcCompInfo;            /*comp type + submodule id*/
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucSrcCompTypeHi: 6;      /* 源组件类型 high 6 bit*/
            PF_UCHAR ucSrcCompTypeRsv: 2;
            PF_UCHAR ucSrcSubModuleId: 2;     /* 源子模块Id, 保留不用*/
            PF_UCHAR ucSrcCompTypeLo: 6;      /* 源组件类型 low 6 bit*/
        #else
            PF_UCHAR ucSrcCompTypeRsv: 2;
            PF_UCHAR ucSrcCompTypeHi: 6;      /* 源组件类型 high 6 bit*/
            PF_UCHAR ucSrcCompTypeLo: 6;      /* 源组件类型 low 6 bit*/
            PF_UCHAR ucSrcSubModuleId: 2;     /* 源子模块Id, 保留不用*/
        #endif
        }s;
    }SrcModule;

    union
    {
        PF_USHORT usSrcNode;               /* slot/cpu/vcpu的混合编码 */
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
                    PF_UCHAR ucSrcCpuId: 3;            /* 源CPU ID */
                    PF_UCHAR ucSrcSlotId: 5;            /* 源逻辑槽位号 */
                    PF_UCHAR usSrcOSSGIndex: 7;           /*目的Vcpu的逻辑进程id */
                    PF_UCHAR ucSrcSGReserve: 1;
        #else
                    PF_UCHAR ucSrcSlotId: 5;            /* 源逻辑槽位号 */
                    PF_UCHAR ucSrcCpuId: 3;            /* 源CPU ID */
                    PF_UCHAR ucSrcSGReserve: 1;
                    PF_UCHAR usSrcOSSGIndex: 7;           /*目的Vcpu的逻辑进程id */
        #endif
        }s;
    }SrcNode;

    PF_ULONG ulHashGene;       /*hash因子 w00136200*/

    union
    {
        PF_USHORT usCompEntityInfo;
        struct
        {
        #if(FWD_LITTLE_ENDIAN == FWD_YES)
            PF_UCHAR ucDstCompEntityResv: 2;   /*目的SG内同类型组件实例保留字段*/
            PF_UCHAR ucDstCompEntityID: 6;   /*目的SG内同类型组件实例号*/
            PF_UCHAR ucSrcCompEntityResv: 2;   /*源SG内同类型组件实例保留字段*/
            PF_UCHAR ucSrcCompEntityID: 6;   /*源SG内同类型组件实例号*/
        #else
            PF_UCHAR ucDstCompEntityID: 6;   /*目的SG内同类型组件实例号*/
            PF_UCHAR ucDstCompEntityResv: 2;   /*目的SG内同类型组件实例保留字段*/
            PF_UCHAR ucSrcCompEntityID: 6;   /*源SG内同类型组件实例号*/
            PF_UCHAR ucSrcCompEntityResv:2;   /*源SG内同类型组件实例保留字段*/
        #endif
        }s;
    }CompEntity;

#if (FWD_LITTLE_ENDIAN == FWD_YES)
    PF_UCHAR ucRes1: 5;
    PF_UCHAR ucSendCopy: 2;
    PF_UCHAR ucMultiCast: 1;
#else
    PF_UCHAR ucMultiCast: 1;
    PF_UCHAR ucSendCopy: 2;
    PF_UCHAR ucRes1: 5;
#endif

    PF_UCHAR  ucRes[1];

}FWD_COMCHANNEL_S;

#define FWD_COMMCHANNEL_SIZE    sizeof(FWD_COMCHANNEL_S)

/* Added start by tulinglong 129941 on 2012-05-15 PGPV2R6 for FCM归一化 */
#define URTD_SET_MSGCODE(pMBuf, MsgCode) \
(((FWD_COMCHANNEL_S*)((PMBUF_MTOD((pMBuf), CHAR*)) - FWD_COMMCHANNEL_SIZE))->ucMsgCode) = (MsgCode)

#define URTD_GET_MSGCODE(pMBuf) \
((FWD_COMCHANNEL_S*)((PMBUF_MTOD((pMBuf), CHAR*)) - FWD_COMMCHANNEL_SIZE))->ucMsgCode
/* Added end by tulinglong 129941 on 2012-05-15 PGPV2R6 for FCM归一化 */

/* IMSI 和MSISDN 长度*/
#define M_SC_MSISDN_LEN  8

#ifndef __NEW_COMPILER_MSISDN__
#define __NEW_COMPILER_MSISDN__
typedef VOS_UINT8 MSISDN[ M_SC_MSISDN_LEN ]; /* MSISDN */
#endif


typedef VOID (*IPC_RPC_RECEIVE_NOTIFY)
(
        ULONG ulSrcNode,                /* 源节点ID          */
        ULONG ulSrcModuleID,            /* 源模块ID          */
        VOID *pReceiveData,             /* 接收的数据        */
        ULONG ulReceiveDataLen,         /* 接收数据的长度    */
        VOID **ppSendData,              /* 发送的数据        */
        ULONG *pulSendDataLen           /* 发送数据的长度    */
);








#define DHCPC_INNER_EVENT   1
#define DHCPC_LAP_MSG_EV    (1<<2)
#define DHCPC_V4_SVR_EV     (1<<3)
#define DHCPC_V6_SVR_EV     (1<<4)

/*DHCP控制块哈希表大小*/
#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define DHCPC_CTRLBLK_HASH_TABLE_SIZE 60
#else
#define DHCPC_CTRLBLK_HASH_TABLE_SIZE 65535
#endif

#define     MS_OPERATION_ADD    0

#define DHCPC_IPOK                      0            /*IP申请成功*/
#define DHCPC_IPFAIL                    1            /*IP申请失败*/

#define DHCPC_FIRSTSEND                 0            /* 第一次发送，需重发 */
#define DHCPC_ALREADYRESEND             1            /* 已经重发 */
#define DHCPC_SNDSRVSEND                2            /* 换服务器重发一次 */

#define DHCPC_CTRLBLK_IDLE              0            /*空闲标志*/
#define DHCPC_CTRLBLK_OCCUPIED          1            /*占用标志*/

#define DHCPC_INVALID_UDPSNO        -1            /*无效的UDPS服务号*/

#define DHCPC_TMPCTRLBLK_IDSTR         "DhcpBlk"        /*DHCP控制块标识串*/
#define DHCPC_RENEW_TIMER_LENGTH     1000    /*地址重用定时器时长1s*/
#define DHCPC_SPU_GP_EVENTBIT         0x1
#define DHCPC_SERVER_EVENTBIT        0x2

#define DHCPC_SRV_TIMER_LENGTH      (60*1000*10)   /* 主用服务器没10分钟探测一次 */

#ifdef __WIN32_PLATFORM__
#define DHCPS_DBG_ENVENTBIT            0x9
#define inline
#endif

#define DHCPC_MAXMSGS_PEREVENT        50
#define DHCPC_DEFAULT_MAX_APP_MSG_NUM   4096

#define DHCPC_4_SECONDS        4
#define DHCPC_8_SECONDS        8

#define DHCPC_RENEW_NUM            80
#if defined(__LINUX_VM__) || defined(__WIN32_PLATFORM__)
#define DHCPC_MAX_CTRLBLKNUM        4        /*DHCP临时控制块数*/
#else
#define DHCPC_MAX_CTRLBLKNUM        1300        /*DHCP临时控制块数*/
#endif

#define DHCPC_DFTCB_TIMER_INTERVAL    (1000*60*5)   /*5分钟定时器，dft上报用*/
#define DHCPC_CTRL_BLOCK_AGING_TIMER_INTERVAL    (1000*60*60*4)   /*4小时定时器，地址老化用*/
#define DHCPC_RETRANS_TIMER_LENGTH    100            /*DHCP重发定时器时长0.1s*/
#define DHCPC_RETRANS_STEPS_PERSEC    (1000/DHCPC_RETRANS_TIMER_LENGTH)            /*每秒钟的刻度数*/
#define DHCPC_TMR_CIRCLE_TIME            (8 * DHCPC_RETRANS_STEPS_PERSEC)          /*总共的刻度数*/
/* BEGIN: Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/23 */
#define DHCPC_FREE_SCAN_TIMER_LENGTH  (1000*60*60)
/* END:   Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/23 */

/* DS.UGWV9R10C0.DHCPv6.DHCP.0024支持TID使用情况的维护--半小时老化一次 */
#ifdef __WIN32_PLATFORM__
#define DHCPC_AGEING_SEQNUM_TIMER_LENGTH  (1000*6)
#else
#define DHCPC_AGEING_SEQNUM_TIMER_LENGTH  (1000*60*30)
#endif
#define DHCPC_AGEING_SEQNUM_MAX_CNT  2 /* 最大老化次数 */

#define DHCPC_INVALID_INDEX            0xffffffff    /*无效的定时器链表索引值*/
#define DHCPC_HEADNODE_TYPE            0xffffffff    /*定时器链表头结点标志*/


#define DHCPC_PKT_PORTNO                68            /*DHCP客户端端口号*/
#define DHCPS_PKT_PORTNO                67            /*DHCP服务器端口号*/

#define DHCPC_MAX_LEASE_TIME            (8*24)        /*最大IP有效时间(hour);请和主控板定义一致*/

#define DHCPC_PKT_FIXEDFIELD_LEN        ( (ULONG)sizeof(DHCP_S) )     /*=236bytes*/

#define DHCPC_PKT_LEN                    300            /*去IP/UDP头*/

#define DHCP_OP_REQUEST                1
#define DHCP_OP_REPLY                    2

#define DHCP_ETHERNETHARDWARETYPE    1
#define DHCP_ETHERNETHARDWARELEN        6

#define DHCP_PKT_ASSUME_MAX_LEN (3*1024)  /* 假定DHCP报文的最大长度为3k,超过该值认为报文异常.一般报文为0.5k左右 */

/*DHCP报文中"options"字段的CODE码  */
#define DHCP_SUBNETMASK_CODE            0x01 /*DHCP报文"options"字段含有"Subnet mask"选项的标识字*/
#define DHCP_ROUTERIP_CODE            0x03 /*DHCP报文"options"字段含有"Routet "选项的标识字*/
#define DHCP_DNSIP_CODE                0x06 /*DHCP报文"options"字段含有"DNS server "选项的标识字*/
#define DHCP_HOSTNAME_CODE            0x0c /*DHCP报文"options"字段含有"Host name"选项的标识字*/
#define DHCP_DOMAINNAME_CODE            0x0f /*DHCP报文"options"字段含有"Domain name"选项的标识字*/
/*为区分5201的CM,IDT,PC等设备而需要的选项 未用这些选项  */
#define DHCP_VENDORINFO_CODE            0x29  /*DHCP报文"options"字段含有"Vendor specific information"选项的标识字*/
#define DHCP_NBNS_CODE                0x2c /*DHCP报文"options"字段含有"Netbios name server"选项的标识字*/
#define DHCP_NBDS_CODE                0x2d /*DHCP报文"options"字段含有"Netbios data distribute server"选项的标识字*/
#define DHCP_NBNT_CODE                    0x2e /*DHCP报文"options"字段含有"Netbios node type"选项的标识字*/
#define DHCP_NBSCOPE_CODE                0x2f /*DHCP报文"options"字段含有"Netbios scope"选项的标识字*/
#define DHCP_REQUESTEDIP_CODE            0x32  /*DHCP报文"options"字段含有"Requested Ip"选项的标识字*/
#define DHCP_IPLEASETIME_CODE            0x33  /*DHCP报文"options"字段含有"Dhcp Ip address lease time"选项的标识字*/
#define DHCP_MESSAGETYPE_CODE        0x35  /*DHCP报文"options"字段含有"Dhcp Message Type"选项的标识字*/
#define DHCP_SERVERIP_CODE                0x36  /*DHCP报文"options"字段含有"Dhcp Server Ip"选项的标识字*/
#define DHCP_REQPARAM_CODE            0x37  /*DHCP报文"options"字段含有"Requested parameter list"选项的标识字*/
#define DHCP_RENEWTIME_CODE            0x3a  /*DHCP报文"options"字段含有"Renew time"选项的标识字*/
#define DHCP_REBINDTIME_CODE            0x3b  /*DHCP报文"options"字段含有"Rebind time"选项的标识字*/
#define DHCP_CLIENTID_CODE                0x3d  /*DHCP报文"options"字段含有"Dhcp client Id"选项的标识字*/
#define DHCP_TFTPSERVER_CODE            66
#define DHCP_BOOTFILE_CODE            67
#define DHCP_OPTION60                    60      /*厂商自定义属性*/
#define DHCP_OPT82_CODE                82      /*DHCP报文"options"字段含有"OPTION 82"选项的标识字*/
#define DHCP_OPT82_CIRCUITID            1
#define DHCP_OPT82_REMOTEID            2

#define DHCP_OPTION_COUNT                20
#define DCHP_MAGICCOOKIE                0x63825363
#define DHCP_ENDOFOPTIONS                0xff

/*DHCPC Error Codes:*/
#define DHCPC_MODID_ERR                1
#define DHCPC_MEM_ERR                    2
#define DHCPC_QUEWRITE_ERR                3
#define DHCPC_USER_NOT_EXIST            4

#define DHCP_MAX_MSISDN_LEN 8
#define DHCP_MAX_MSISDN_STRING_LEN GTPC_IMSI_MSISDN_LENGTH

/*DHCPC Debug Levels*/
#define DHCPC_DBG_L0    1        /*流程关键点*/
#define DHCPC_DBG_L1    2        /*异常点*/
#define DHCPC_DBG_L2    3        /*调试信息*/

#define DHCPC_DEBUGBUF_LEN                (1024 + 2)


#define DHCPC_RUN_TIME_MILLSECS     100
#define DHCPC_TASK_DELAY_MILLSECS   10


#define DHCP_VPN_INSTANCE_NAME_MAX_LENGTH  32              /*VPN名字长度*/
#define DHCP_NO_ALARM                      0               /* DHCP 没有发布链路断告警 */
#define DHCP_ALARMED                       1               /* DHCP 已经发布链路断告警 */

/* BEGIN: Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/7 */
#define DHCPC_BLOCK_USED 1
#ifdef __WIN32_PLATFORM__
#define DHCP_BLOCK_MAX_SACNNUM 3
#else
#define DHCP_BLOCK_MAX_SACNNUM 10
#endif
/* END:   Added for PN:DHCPv6特性 by tianyang 00144555, 2012/7/7 */

/* zhangjinquan 00175135 DHCPv6特性 2012-07-23 start */
/* 秒级时间槽的定时间间隔 */
#define DHCPC_SECOND_TIMER_INTERVAL 200
#define DHCPC_SECONDS_PER_HOUR 3600
#define DHCPC_MILLSECONDS_PER_SECOND 1000
#define DHCPC_SECONDS_PER_MINUTE 60
#define DHCPC_DAYS_PER_MONTH 31
#define DHCPC_HOURS_PER_DAY 24
/* 秒级时间槽，考虑到精度问题，200毫秒处理一次链，3600秒/小时*200毫秒/每次=18000 */
#define DHCPC_SECOND_TIMER_LEN (DHCPC_SECONDS_PER_HOUR*DHCPC_MILLSECONDS_PER_SECOND/DHCPC_SECOND_TIMER_INTERVAL)
/* 小时时间槽的定时间间隔 */
#define DHCPC_HOUR_TIMER_INTERVAL (DHCPC_SECONDS_PER_MINUTE*DHCPC_MILLSECONDS_PER_SECOND)
/* 小时时间槽，共31天*24小时/天=744个槽位 */
#define DHCPC_HOUR_TIMER_LEN (DHCPC_DAYS_PER_MONTH*DHCPC_HOURS_PER_DAY)

#define DHCPC_FIND_SAME_NODE_MAX_CNT 5

/* 定时器链表类型 */
typedef enum enDHCP_LIST_TYPE
{
    DHCPC_LIST_TYPE_SECOND,
    DHCPC_LIST_TYPE_HOUR,
    DHCPC_LIST_TYPE_MAX,
} DHCP_LIST_TYPE_EN;

extern ULONG g_ulDHCPCTimerListNodeNum[DHCPC_LIST_TYPE_MAX];

/* 根据时间间隔获取秒级链的插入位置 */
#define DHCPC_GET_SECOND_INSPOS(ulTimerInterval) ((DHCPC_getCurTimerSecondPos() + (ulTimerInterval)) % DHCPC_SECOND_TIMER_LEN)
/* 根据时间间隔获取小时链的插入位置 */
#define DHCPC_GET_HOUR_INSPOS(ulTimerInterval) ((DHCPC_getCurTimerHourPos() + (ulTimerInterval)) % DHCPC_HOUR_TIMER_LEN)

#define DHCPC_GET_HASHKEY(ulHashElement) (((ulHashElement) % DHCPC_CTRLBLK_HASH_TABLE_SIZE + (ulHashElement) / DHCPC_CTRLBLK_HASH_TABLE_SIZE) % DHCPC_CTRLBLK_HASH_TABLE_SIZE)

/* 定时器回调处理函数 */
typedef ULONG (* DHCPC_TIMER_CALLBACK)(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent);

typedef struct tagDHCPC_TIMER_NODE_S
{
    struct tagDHCPC_TIMER_NODE_S *pstPrevNode;     /* 时间链上的上一个节点 */
    struct tagDHCPC_TIMER_NODE_S *pstNextNode;     /* 时间链上的下一个节点 */
    struct tagDHCPC_TIMER_NODE_S *pstHashNextNode; /* 哈希链上的下一个节点 */
    DHCPC_TIMER_CALLBACK pCallBackFun;
    ULONG  ulCircleNum;   /* 租约的月数，0表示不到一个月 */
    ULONG  ulTeidc;
    USHORT usSecondField; /* 秒级时间槽应该挂的位置 */
    UCHAR  ucIpType;
    UCHAR  ucEvent;
    UCHAR  ucListType;   /* 链表类型: 0-秒级链表，1-小时链表 */
    UCHAR  aucReserve[3];
} DHCPC_TIMER_NODE_S;

typedef struct tagDHCPC_TIMER_LIST_HEAD_S
{
    DHCPC_TIMER_NODE_S *pstNextNode;
} DHCPC_TIMER_LIST_HEAD_S;

extern DHCPC_TIMER_LIST_HEAD_S *g_pstDHCPTimerHashList;

/* 秒级定时器id */
extern RELTMR_T g_ulDHCPCSecondTimerId;
/* 小时定时器id */
extern RELTMR_T g_ulDHCPCHourTimerId;
/* zhangjinquan 00175135 DHCPv6特性 2012-07-23 end   */

enum
{
    DHCPC_INNER_MSGCODE_CHECK_PDP = 1,
    DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK,
    DHCPC_INNER_MSGCODE_TIM_RESTORE,
    DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE,
};


typedef struct tagDHCPC_INNER_MSG_S
{
    ULONG ulMsgCode;
    ULONG ulPdpIndex;
    ULONG ulCtlBlockHashValue;
    ULONG ulReserve34566;
} DHCPC_INNER_MSG_S;


/*===================MACROS====================================*/
/*X34710:不计算UDP头的填充方法DHCP_LENGTHTO308*/
#define DHCP_LENGTHTO300(pulMagicCookie,pucDhcpOption) \
{\
    ULONG i;\
\
    i=(ULONG)((UCHAR *)pucDhcpOption-(UCHAR *)pulMagicCookie);\
    if(i>(DHCPC_PKT_LEN -sizeof(DHCP_S))) VOS_Assert(0);\
    for ( ; i <= (DHCPC_PKT_LEN -sizeof(DHCP_S)) ; i++ )\
    {\
        *(pucDhcpOption++) = 0;\
    }\
}

#define DHCPC_INIT_ITEM(pItem)  \
{\
    VOS_StrCpy(((CHAR *)(pItem)->ucCtrlBlkFlgStr), DHCPC_TMPCTRLBLK_IDSTR/*,VOS_StrLen(DHCPC_TMPCTRLBLK_IDSTR) for code review*/); \
    (pItem)->ulPdpIndex = NULL;      \
    (pItem)->ulModId = NULL;        \
    (pItem)->usDhcpStatus = NULL;     \
    (pItem)->ulSrvIp = NULL;     \
    (pItem)->ulUserIpAddr = NULL;    \
    (pItem)->usLease = 0;    \
    (pItem)->ulTimeStamp = NULL;    \
    (pItem)->ulXid = NULL;    \
    (pItem)->usAlreadySendFlg = DHCPC_FIRSTSEND;    \
}

#define DHCPC_INIT_CTRLBLK(pItem)  \
{\
    (pItem)->ulDHCPCtxIdx = 0;      \
    (pItem)->aulMSISDN[0] = 0;\
    (pItem)->aulMSISDN[1] = 0;\
    (pItem)->ulPDPIndex = 0;    \
    (pItem)->usDhcpStatus = 0;        \
    (pItem)->usLease = 0;     \
    (pItem)->ulTimeStamp = 0;     \
    (pItem)->ulSrvIp = 0;    \
    (pItem)->ulUserIpAddr = 0;    \
    (pItem)->ulTimeStamp = 0;    \
    (pItem)->ulTmpVar = 0;    \
}

#define DHCPC_BACKUPMSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulDHCPCtxIdx = (pMsg)->ulDHCPCtxIdx;      \
    (pItem)->ulPDPIndex = (pMsg)->ulPDPIndex;    \
    (pItem)->usDhcpStatus = (pMsg)->usDhcpStatus;        \
    (pItem)->usLease = (pMsg)->usLease;     \
    (pItem)->ulTimeStamp = (pMsg)->ulTimeStamp;     \
    (pItem)->ulSrvIp = (pMsg)->ulSrvIp;    \
    (pItem)->ulUserIpAddr = (pMsg)->ulUserIpAddr;    \
    (pItem)->ulTimeStamp = (pMsg)->ulTimeStamp;    \
    (pItem)->ulTmpVar = (pMsg)->ulTmpVar0;    \
}


#define DHCPC_MSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulPdpIndex      = (pMsg)->ulIndex ;     \
    (pItem)->ucSCID = (pMsg)->ucSCID;\
    (pItem)->usDhcpGroupIndex   = (pMsg)->usDhcpGroupIndex;   \
}


#define DHCPC_RELEASEMSG2ITEM(pMsg, pItem) \
{\
    (pItem)->ulPdpIndex    = (pMsg)->ulIndex ;     \
    (pItem)->ucSCID = (pMsg)->ucSCID; \
    (pItem)->ulUserIpAddr = (pMsg)->aulPdpAddr[0]; \
    (pItem)->aulMSISDN[0] = (pMsg)->aulMSISDN[0]; \
    (pItem)->aulMSISDN[1] = (pMsg)->aulMSISDN[1]; \
    (pItem)->usDhcpGroupIndex = (pMsg)->usDhcpGroupIndex; \
}


#define DHCPC_ITEM2MSG(pItem, pMsg) \
{\
    VOS_MemCpy(((pMsg)->szMac), ((pItem)->szMac) , 6);\
    (pMsg)->usCid   =   (pItem)->usCid ;        \
    (pMsg)->ulAddr  =   (pItem)->ulIPAddr;      \
    (pMsg)->ulMask  =   (pItem)->ulMask;        \
    (pMsg)->ulLeaseTime     =   (pItem)->ulLeaseTime;       \
    (pMsg)->ulGatewayAddr   =   (pItem)->ulGatewayAddr;     \
    (pMsg)->ulPriDnsAddr    =   (pItem)->ulPriDnsAddr;      \
    (pMsg)->ulSecDnsAddr    =   (pItem)->ulSecDnsAddr;      \
    (pMsg)->ulPriNbnsAddr   =   (pItem)->ulPriNbnsAddr;     \
    (pMsg)->ulSecNbnsAddr   =   (pItem)->ulSecNbnsAddr;     \
    (pMsg)->ulDhcpSvrAddr   =   (pItem)->ulDhcpSvrAddr;     \
}

#define DHCPC_ITEM_SETSATE(pItem, State)        \
{\
       (pItem)->usDhcpStatus/*ucState*/     = (State) ;           \
}

/*在GGSN，MAC地址可以不填，
 *具体参见RFC2131 page 23
 */
#define DHCP_FILLFIXEDFIELD(ucOpp,pstSendDhcp,ulXiid,usSecss,usFlagg,ulUserIpAddr,ulGiaddrr,ulCiaddrr,szChaddrr) \
{\
    ULONG ii; \
    \
    pstSendDhcp->ucOp     = ucOpp;\
    pstSendDhcp->ucHtype  = DHCP_ETHERNETHARDWARETYPE;\
    pstSendDhcp->ucHlen   = DHCP_ETHERNETHARDWARELEN;\
    pstSendDhcp->ucHops   = 0;\
    pstSendDhcp->ulXid    = VOS_HTONL(ulXiid);\
    pstSendDhcp->usSecs   = VOS_HTONS(usSecss);\
    pstSendDhcp->usFlag   = VOS_HTONS(usFlagg);\
    pstSendDhcp->ulYiaddr = ulUserIpAddr; \
    pstSendDhcp->ulGiaddr = ulGiaddrr;\
    pstSendDhcp->ulCiaddr = ulCiaddrr;\
    for(ii = 0; ii < DHCP_ETHERNETHARDWARELEN; ii++)\
    {\
        pstSendDhcp->szChaddr[ii] = szChaddrr[ii];\
    }\
}

#define DHCP_FILLMAGICCODE(pulMagicCookie) \
{\
    *pulMagicCookie = VOS_HTONL(DCHP_MAGICCOOKIE);\
}

#define DHCP_FILLMESSAGETYPEOPTION(pucDhcpOption,ucValue) \
{\
    *pucDhcpOption++ = DHCP_MESSAGETYPE_CODE;\
    *pucDhcpOption++ = 1;\
    *pucDhcpOption++ = ucValue;\
}

#define DHCP_FILLIPOPTION(pucDhcpOption,ulOptionId,ulValue) \
{\
    ULONG *pulRequestedIp = NULL;\
\
    *pucDhcpOption++ = ulOptionId;\
    *pucDhcpOption++ = 4;\
    pulRequestedIp   = (ULONG *)pucDhcpOption;\
    *pulRequestedIp  = (ULONG)ulValue;\
    pucDhcpOption    = (UCHAR *)(pulRequestedIp + 1);\
}

#define DHCP_FILLULONGOPTION(pucDhcpOption,ulOptionId,ulValue) \
{\
    ULONG *pulValue = NULL;\
\
    *pucDhcpOption++ = ulOptionId;\
    *pucDhcpOption++ = 4;\
    pulValue   = (ULONG *)pucDhcpOption;\
    *pulValue  = VOS_HTONL((ULONG)ulValue);\
    pucDhcpOption    = (UCHAR *)(pulValue + 1);\
}

#define DHCP_FILLENDOPTION(pucDhcpOption) \
{\
   *pucDhcpOption++   = DHCP_ENDOFOPTIONS;\
}
#define DHCP_FILLPARALISTOPTION(pucDhcpOption)\
{\
    *pucDhcpOption++ = DHCP_REQPARAM_CODE;\
    *pucDhcpOption++ = 0x02;\
    *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;\
    *pucDhcpOption++ = DHCP_DNSIP_CODE;\
}
#define DHCP_SLOT_ONE    1
#define DHCP_SLOT_THREE    3
#define DHCP_SLOT_FIVE    5
#define DHCP_SLOT_SEVEN    7

enum DHCPC_AGING_STATUS_FLAG
{
    DHCPC_NOT_AGING = 0,
    DHCPC_CHECKING_WITH_PDP,
    DHCPC_AGING,
    DHCPC_AGING_MAX,
};

#define DHCPC_GROUP_BITSIZE 16
/*m00221573 全文件pclint 2012-10-19 start*/
extern ULONG DHCPC_StartTimer(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent, ULONG ulTimerInterval, DHCPC_TIMER_CALLBACK pCallBackFun);
/*m00221573 全文件pclint 2012-10-19 end*/

#endif /* #ifndef _DHCP_DEF_H_ */
