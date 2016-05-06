/*******************************************************************************
  File name   : AsNasApi.h
  Description : As层对Nas提供的Api接口头文件
  History     :
  1.  z49132  2003-07-25: The first version
  2.  z49132  2004.10.25  CK,IK的存储结构改为字节流
  3.日    期  : 2006年12月4日
    作    者  : luojian id:60022475
    修改内容  : 增加 #pragma pack(4)，问题单号:A32D07779
  4.日    期   : 2009年02月05日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07529,AT2D07611,AT2D08749,W搜网优化NAS修改
  5.日    期   : 2009年04月27日
    作    者   : l65478
    修改内容  : 问题单号：AT2D11554，出服务区优化
  6.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
  7.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步,删除冗余定义
*******************************************************************************/
#ifndef _AS_NAS_API_H_
#define _AS_NAS_API_H_

#include "product_config.h"
#include "Nasrrcinterface.h"
#include "TtfDrvInterface.h"
/* Added by wx270776 for OM融合, 2015-7-24, begin */
#include "NasMntn.h"
/* Added by wx270776 for OM融合, 2015-7-24, end */

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                                 /* __cpluscplus                              */
#endif                                                                                 /* __cpluscplus                              */

#pragma pack(4)


/* Define API return values */
#define AS_SUCCESS                      0                                              /* As处理成功                                */
#define AS_RB_NO_EXIST                  1                                              /* RbId不存在                                */
#define AS_DATA_LENGTH_ERR              2                                              /* 数据的长度不匹配                          */
#define AS_NO_MEMORY                    3                                              /* As申请内存失败                            */
#define AS_RB_MODE_ERR                  4                                              /* RB模式不匹配                              */
#define AS_RAB_INFO_ERR                 5                                              /* 所有的RB不属于同一个RAB用于U_CsDomainSync
                                                                                        * DataReq                                   */
#define AS_SEND_FAILED                  6                                              /* AS发送失败                                */
#define AS_GENERAL_ERR                  7                                              /* 其他错误                                  */
#define AS_PARA_MISMATCH                8                                              /* 参数不匹配                                */
#define AS_VOS_ERR                      9                                              /* AS使用VOS时发生异常                       */


/* RR_DATA_IND_FUNC中ucICResult的宏定义 */
#define IC_RSLT_BOTH_NO_START           0x00                                           /* 加密和完整性保护都未启动                  */
#define IC_RSLT_CIPH_START              0x01                                           /* 加密启动                                  */
#define IC_RSLT_INTRG_START             0x02                                           /* 完整性保护启动                            */


/* As_RabInfoRsp函数的ulResult的宏定义 */
#define AS_RAB_RSP_OK                   0                                              /* 可以建立                                  */
#define AS_RAB_RSP_NG                   1                                              /* 不能建立                                  */


/* RLC使用的宏定义 */
#define NAS_DATA_SUCCESS                0                                              /* Used by parameter Err                     */
#define NAS_DATA_ERR                    1                                              /* Used by parameter Err                     */



typedef struct paging_info_stru
{
    VOS_UINT32                   ulCnDomainId;                                              /* CN Domain ID                              */
    VOS_UINT32                   ulPagingType;                                              /* 寻呼消息类型                              */
    VOS_UINT32                   ulPagingCause;                                             /* 消息中的Paging Cause                      */
    VOS_UINT32                   ulPagingRecordTypeId;                                      /* 消息中的Paging Recorder Id                */
}PAGING_INFO_STRU;


typedef struct sys_info_stru
{
    VOS_UINT32                          bitOpPlmnId     : 1;
    VOS_UINT32                          bitOpCsDrx      : 1;
    VOS_UINT32                          bitOpPsDrx      : 1;
    VOS_UINT32                          bitSpare        : 29;
    RRC_PLMN_ID_STRU        PlmnId;                                                    /* 本小区PLMN ID                             */
    VOS_UINT32                   ulCsDrxLength;                                             /* CS域DRX长度系数                           */
    VOS_UINT32                   ulPsDrxLength;                                             /* PS域DRX长度系数                           */
    VOS_UINT8                           ucCnCommonSize;     /* CN Common信息的字节长度    */
    VOS_UINT8                           aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucCsInfoSize;       /* CS域相关信息的字节长度     */
    VOS_UINT8                           aucCsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           ucPsInfoSize;       /* PS域相关信息的字节长度     */
    VOS_UINT8                           aucPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];
    VOS_UINT8                           aucReserve1[1];     /* 保留 */
}SYSINFO_STRU;


typedef struct idnns_stru
{
    VOS_UINT8                   ucIdnnsType;                                               /* IDNNS类型                                 */
    VOS_UINT8                   ucEnterPara;                                               /* 用于设置IDNNS的参数                       */
}IDNNS_STRU;


typedef struct security_info_stru
{
    VOS_UINT32                  ulRptMode;                                                  /* 报告模式                                  */
    VOS_UINT32                  ulCsCipherStatus;                                           /* CS域当前加密启动状态                      */
    VOS_UINT32                  ulPsCipherStatus;                                           /* PS域当前加密启动状态                      */
    VOS_UINT32                  ulIntegCmd;                                                 /* 完整性保护启动命令                        */
    /* added by weijiantao 05-04-15 begin: 为了对应MM/GMM向AGENT上报加密算法 */
    VOS_UINT32                  ulCsCipherAlgor;                                            /* CS域最新加密算法, 仅当CS域加密启动后有效  */
    VOS_UINT32                  ulPsCipherAlgor;                                            /* PS域最新加密算法, 仅当PS域加密启动后有效  */
}SECURITY_INFO_STRU;


typedef struct attach_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain数量                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* 该配置所指CN Domain                       */
        VOS_UINT32               ulAttach;                                                  /* Attach、Deattach标志                      */
    }aAttachInfo[RRC_NAS_MAX_CN_DOMAIN];
}ATTACH_INFO_STRU;


typedef struct usim_valid_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain数量                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* 该配置所指CN Domain                       */
        VOS_UINT32               ulUsimValid;                                               /* USIM有效标志                              */
    }aUsimInfo[RRC_NAS_MAX_CN_DOMAIN];
}USIM_VALID_INFO_STRU;


typedef struct security_key_info_stru
{
    VOS_UINT32                   ulCnt;                                                     /* CN Domain数量                             */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* 该配置所指CN Domain                       */
        /*VOS_UINT32             aulCk[4];*/
        /*VOS_UINT32             aulIk[4];*/
        VOS_UINT8               aucCk[16];                                                 /* Cipher Key                                */
        VOS_UINT8               aucIk[16];                                                 /* Integrity Key                             */
    }aKeyInfo[RRC_NAS_MAX_CN_DOMAIN];
}SECURITY_KEY_INFO_STRU;


typedef struct plmn_search_para_stru
{
    VOS_UINT32                   ulSearchType;                                              /* 搜索类型                                  */
    VOS_UINT32                   ulPlmnIdNum;                                               /* PLMN ID个数                               */
    RRC_PLMN_ID_STRU        aPlmnIdList[RRC_MAX_EQUPLMN_NUM+1];                        /* PlMN标识                                  */
    VOS_UINT32                   ulForbLaNum;                                               /* 禁止注册区的个数                          */
    RRC_FORB_LA_STRU        aForbLaList[RRC_MAX_FORBLA_NUM];                           /* 禁止注册区列表                            */
}PLMN_SEARCH_PARA_STRU;


typedef struct plmn_list_stru
{
    VOS_UINT32                   ulHighPlmnNum;                                             /* 高质量PLMN的个数                          */
    RRC_PLMN_ID_STRU        aHighPlmnList[RRC_MAX_HIGH_PLMN_NUM];                      /* 高质量PLMN列表                            */
    VOS_UINT32                   ulLowPlmnNum;                                              /* 低质量PLMN的个数                          */
    struct
    {
        RRC_PLMN_ID_STRU    PlmnId;                                                    /* PLMN ID                                   */
        VOS_INT32                lRscp;                                                     /* RSCP测量值                                */
    }aLowPlmnList[RRC_MAX_LOW_PLMN_NUM];                                               /* 低质量PLMN列表                            */
}PLMN_LIST_STRU;


typedef struct plmn_search_result_stru
{
    VOS_UINT32                   ulSearchRlt;                                               /* 搜索结果                                  */
    PLMN_LIST_STRU          PlmnIdList;                                                /* 上报的PLMN ID列表                         */
}PLMN_SEARCH_RESULT_STRU;


typedef struct equivalent_plmn_stru
{
    VOS_UINT32                   ulEquPlmnNum;                                              /* 等效的PLMN的个数                          */
    RRC_PLMN_ID_STRU        aEquPlmnIdList[RRC_MAX_EQUPLMN_NUM + 1];                   /* 等效的PLMNID列表                          */
} EQUIVALENT_PLMN_STRU;


typedef struct forbiden_la_list_stru
{
    VOS_UINT32                   ulForbLaNum;                                               /* 禁止注册区的个数                          */
    struct
    {
        RRC_PLMN_ID_STRU    PlmnId;                                                    /* PlMN标识                                  */
        VOS_UINT32               ulForbLac;                                                 /* 禁止注册区信息                            */
    }aForbLaList[RRC_MAX_FORBLA_NUM];                                                  /* 禁止注册区列表                            */
} FORBIDEN_LA_LIST_STRU;


typedef struct rab_status_info_stru
{
    VOS_UINT32                   ulOpId;
    VOS_UINT32                   ulRabChangeType;                                           /* RAB的操作类型                             */
    VOS_UINT32                   ulRabCnt;                                                  /* 本次RAB操作的数量                         */
    struct
    {
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulCnDomainId;                                              /* 该RAB所属CN Domain                        */
        VOS_UINT32               ulRbNum;                                                   /* 该RAB包含RB数量                           */
        VOS_UINT32               aulRbId[RRC_NAS_MAX_RB_PER_RAB];                           /* 该RAB包含RB ID                            */
    }aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RAB_STATUS_INFO_STRU;


typedef struct rab_rsp_info_stru
{
    VOS_UINT32                   ulOpId;                                                    /* 与建立RAB的IND原语相同                    */
    VOS_UINT32                   ulRabCnt;                                                  /* 建立RAB数量                               */
    struct
    {
        VOS_UINT32               ulCnDomainId ;                                             /* 所属CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulPppValid;                                                /* 是否采用PPP协议                           */
        VOS_UINT32               ulDeliveryErrSdu;
    }aRabInfo[RRC_NAS_MAX_RAB_SETUP];
}RAB_RSP_INFO_STRU;


typedef struct sync_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* 需要同步RAB数量                           */
    struct
    {
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulCnDomainId;                                              /* 该RAB所属域                               */
        VOS_UINT32               ulRabSyncInfo;                                             /* 该RAB的同步指示                           */
    }NasSyncInfo[RRC_NAS_MAX_RAB_SETUP];
}SYNC_INFO_STRU;


typedef struct rab_sc_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* RAB数量                                   */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* 所属CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
    }aRab[RRC_NAS_MAX_RAB_SETUP];
    VOS_UINT32                   ulStatus;                                                  /* RAB对应操作类型                           */
}RAB_SC_INFO_STRU;


typedef struct qos_info_stru
{
    VOS_UINT32                   ulRabCnt;                                                  /* RAB数量                                   */
    struct
    {
        VOS_UINT32               ulCnDomainId;                                              /* 所属CN Domain                             */
        VOS_UINT32               ulRabId;                                                   /* RAB ID                                    */
        VOS_UINT32               ulPppValid;                                                /* 是否采用PPP协议                           */
        VOS_UINT32               ulDeliveryErrSdu;                                          /* 错误的SDU的处理模式                       */
    }aRab[RRC_NAS_MAX_RAB_SETUP];
}QOS_INFO_STRU;

typedef struct avail_plmn_stru
{
    VOS_UINT32                  ulAvailPlmnNum;
    RRC_PLMN_ID_STRU            astAvailPlmnIdList[NAS_RRC_MAX_AVAILPLMN_NUM];       /* PlMN标识 */
}AVAIL_PLMN_STRU;


/* Define the function prototypes of the AS layer API */
VOS_INT32 NAS_CsDomainDataReq(VOS_INT8  cRbId,VOS_UINT32 ulDataLength,VOS_UINT8   *pucData);

VOS_INT32 NAS_PsDomainTcDataReq(VOS_UINT8 ucRbId, VOS_UINT32 ulDataBitLen, TTF_MEM_ST *pstDataMem);

VOS_INT32 As_RrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);

VOS_INT32 As_RrDataReq(VOS_UINT8, VOS_UINT8, VOS_UINT32, VOS_INT8*);
VOS_INT32 As_RabInfoRsp(VOS_UINT32 ulResult,RAB_RSP_INFO_STRU* pRabInfo);
VOS_INT32 As_RabQosUpdate(QOS_INFO_STRU*);

VOS_INT32 As_RrEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    VOS_UINT32                          ulCallType,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
);

/* Define the callback function prototypes of the NAS layer API */
typedef VOS_VOID    NAS_CALLBACK_TYPE;

typedef NAS_CALLBACK_TYPE (*EXT_MemFreeFunc)( VOS_UINT32 ulLabel, VOS_VOID *p );
typedef NAS_CALLBACK_TYPE (*RR_DATA_IND_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT32 ulSize, VOS_UINT8 *pData);
typedef NAS_CALLBACK_TYPE (*PAGING_IND_FUNC)(PAGING_INFO_STRU *pPagingInfo);
typedef NAS_CALLBACK_TYPE (*SYSTEM_INFO_IND_FUNC)(SYSINFO_STRU *pSysInfo);
typedef NAS_CALLBACK_TYPE (*RR_EST_CNF_FUNC)(VOS_UINT32 ulOpId, VOS_UINT32 ulResult,VOS_UINT32 ulCnDomainId);
typedef NAS_CALLBACK_TYPE (*RR_REL_IND_FUNC)(VOS_UINT8 ucCnDomain, VOS_UINT32 ulRelCause, VOS_UINT32 ulRrcConnStatus);
typedef NAS_CALLBACK_TYPE (*SECURITY_IND_FUNC)(VOS_UINT8);
typedef NAS_CALLBACK_TYPE (*PLMN_SEARCH_CNF_FUNC)(PLMN_SEARCH_RESULT_STRU *pSearchResult);
typedef NAS_CALLBACK_TYPE (*PLMN_LIST_IND_FUNC)(PLMN_LIST_STRU *pPlmnList);
typedef NAS_CALLBACK_TYPE (*COVERAGE_LOST_IND_FUNC)( VOS_UINT32 ulRptMode );
typedef NAS_CALLBACK_TYPE (*RAB_STATUS_INFO_IND_FUNC)(RAB_STATUS_INFO_STRU *pRabInfo);
typedef NAS_CALLBACK_TYPE (*RR_SYNC_IND_FUNC)(SYNC_INFO_STRU *pSyncInfo);
typedef NAS_CALLBACK_TYPE (*RAB_SC_IND_FUNC)(RAB_SC_INFO_STRU *pScInfo);
typedef NAS_CALLBACK_TYPE (*RR_POWER_OFF_CNF_FUNC)(VOS_VOID);
typedef NAS_CALLBACK_TYPE (*RR_START_CNF_FUNC)(VOS_VOID);
typedef NAS_CALLBACK_TYPE (*RRMM_AC_INFO_CHANGE_IND_FUNC)( VOS_UINT32  ulAcChangeInd );


typedef struct imported_func_list_stru
{

    struct
    {
        RR_DATA_IND_FUNC                RrDataIndFunc;
        PAGING_IND_FUNC                 RrPagingIndFunc;
        SYSTEM_INFO_IND_FUNC            RrSysInfoIndFunc;
    }SigDataTransfer;

    struct
    {
        RR_EST_CNF_FUNC                 RrEstCnfFunc;
        RR_REL_IND_FUNC                 RrRelIndFunc;
        SECURITY_IND_FUNC               RrSecurityIndFunc;
        RR_POWER_OFF_CNF_FUNC           RrPowerOffCnfFunc;
        RR_START_CNF_FUNC               RrStartCnfFunc;
    }SigConnCtrl;

    struct
    {
        PLMN_SEARCH_CNF_FUNC            PlmnSearchCnfFunc;
        PLMN_LIST_IND_FUNC              PlmnListIndFunc;
        COVERAGE_LOST_IND_FUNC          CoverageLostIndFunc;
    }PlmnSearch;

    struct
    {
        RAB_STATUS_INFO_IND_FUNC        RabStatusIndFunc;
        RR_SYNC_IND_FUNC                RrSyncIndFunc;
        RAB_SC_IND_FUNC                 RabScIndFunc;
    }RbMng;

    struct
    {
        RRMM_AC_INFO_CHANGE_IND_FUNC    RrAcInfoChangeIndFunc;
    }RrcInfoInd;

    struct{
        EXT_MemFreeFunc                 ExtMemFree;
    }ext_memfree_api;

}IMPORTED_FUNC_LIST_STRU;

extern IMPORTED_FUNC_LIST_STRU          ImportFunc;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                                 /* __cpluscplus                              */

#endif
