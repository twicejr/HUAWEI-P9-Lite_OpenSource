

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "MmaAppLocal.h"


#include "mdrv.h"
#include "mnmsgcbencdec.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"
#include "MnComm.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"

#include "MnMsgSendSpm.h"
#include "TafStdlib.h"

#if ( VOS_WIN32 == VOS_OS_VER )
#include "wchar.h"
#else
#endif
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID        PS_FILE_ID_MNMSG_SM_COMM_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

VOS_UINT32 MN_MSG_CheckMemAvailable(VOS_VOID);
#define MN_MSG_EF_FIRST_RECORD                              (1)

MN_MSG_USIM_EFUST_NEED_REFRESH_STRU stUsimFilesNeedRefreshFlag;

#define MN_MSG_USIM_FILL_BYTE                               0xff

#define MN_MSG_EFSMSP_ADDR_UNIT_LEN                         12
#define MN_MSG_MIN_SRV_PARM_LEN                             28                  /*EFSMSP文件最少的长度*/
#define MN_MSG_MAX_ACTION_NODE_NUM                          60                  /*USIM的最大节点数*/
#define MN_MSG_MAX_USIM_SMS_NUM                             255                 /*USIM中短信的最大条数*/
#define MN_MSG_MAX_USIM_SMSR_NUM                            255                 /*USIM中短信报告的最大条数*/
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         500                 /*NVIM中短信的最大条数*/
#else
#define MN_MSG_MAX_NVIM_SMS_REC_NUM                         0                   /*NVIM中短信的最大条数*/
#endif

#define MN_MSG_MAX_NVIM_SMSR_REC_NUM                        255                 /*NVIM中短信报告的最大条数*/

VOS_CHAR *g_pucSmsFileOnFlash                               = VOS_NULL_PTR;

/* SIM CARD TYPE */
#define MN_MSG_CARD_TYPE_USIM     1
#define MN_MSG_CARD_TYPE_SIM      2

#define TAF_MSG_MIN_DESTINATION_ADDRESS_LEN                 (2)
#define TAF_MSG_MAX_DESTINATION_ADDRESS_LEN                 (11)



/*存储flash短信文件句柄*/
FILE                                   *gfpSmsFlash;

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

extern VOS_UINT8                        g_ucMnOmConnectFlg;
extern VOS_UINT8                        g_ucMnOmPcRecurEnableFlg;

/*****************************************************************************
  3 类型定义
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bEfSmsrState;                           /* USIM中是否存在EfSmsr的标志*/
    VOS_UINT8                           ucSmsrRealRecNum;                       /* 从USIM获得的SMSR实际记录数 */
    VOS_UINT8                           ucSmsrCurRecNum;                        /* 无空闲的记录时,存储的位置*/
    VOS_UINT8                           aucEfSmsrList[MN_MSG_MAX_USIM_SMSR_NUM * MN_MSG_EFSMSR_LEN]; /* 缓存EfSmsr*/
}MN_MSG_USIM_EFSMSR_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmsState;                            /* USIM中是否存在EfSms的标志*/
    VOS_UINT8                           ucSmsRealRecNum;                        /* 从USIM获得的SMS实际记录数 */
    VOS_UINT8                           aucEfSmsList[MN_MSG_MAX_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* 缓存EfSms*/
    VOS_UINT8                           aucReserve[3];
}MN_MSG_USIM_EFSMS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmssState;                           /*USIM中是否存在EfSmss的标志*/
    VOS_UINT32                          ulFileLen;
    MN_MSG_SMSS_INFO_STRU               stEfSmssInfo;                           /*EFSMSS的内容*/
    VOS_UINT8                           aucReserve[1];
}MN_MSG_USIM_SMSS_INFO_STRU;

typedef struct
{
    VOS_BOOL                            bEfSmspState;                           /*USIM中是否存在EfSmsp的标志*/
    VOS_UINT8                           ucSmspRealRecNum;                       /*EFSMSP的记录数目*/
    VOS_UINT8                           aucReserve[3];
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    astEachEfSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];/*第一个为默认值*/
}MN_MSG_USIM_EFSMSP_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucList;                                 /*列表短信时,操作USIM的总记录数*/
    VOS_UINT8                           ucDelete;                               /*删除短信时,操作USIM的总记录数*/
    VOS_UINT8                           ucDeleteBegin;                          /*删除多条短信记录时,一次最多向USIM发送10条,每次向USIM发送开始记录数*/
    VOS_UINT8                           aucReserve[1];
    VOS_BOOL                            bDeleteReportFlag;                      /*删除短信结果是否已经上报给应用*/
    VOS_UINT8                           ucDeleteStaRpt;                         /*删除短信状态报告时,操作USIM的总记录数*/
    VOS_UINT8                           ucDeleteStaRptBegin;                    /*删除多条短信状态记录时,一次最多向USIM发送10条,每次向USIM发送开始记录数*/
    VOS_UINT8                           aucReserve2[2];
    VOS_BOOL                            bDeleteStaRptReportFlag;                /*删除短信状态结果是否已经上报给应用*/
    VOS_UINT8                           ucDeleteEfSmsp;                         /*删除短信文件EFSMSP时,操作USIM的总记录数*/
    VOS_UINT8                           aucReserve3[3];
    VOS_BOOL                            bDeleteEfSmspReportFlag;                /*删除短信参数结果是否已经上报给应用*/
}MN_MSG_SET_USIM_REC_STRU;

typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}MN_MSG_MO_SMS_CTRL_STRU;


#define MN_MSG_BUFFER_SMS_SEG_NUM                             1                 /*USIM中短信的最大条数*/
typedef struct
{
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
    VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
    MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
    MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST的内容*/
    MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag;
    MN_MSG_CLASS0_TAILOR_U8          g_enMsgClass0Tailor;
    VOS_UINT8                        ucMoSmsCtrlFlag;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8   enMtCustomize;
    MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
    SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
    MN_MSG_STORE_MSG_STRU            f_stMsgSmSaved[MN_MSG_BUFFER_SMS_SEG_NUM]; /**/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST;

typedef struct
{
    MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl;
    MN_OPERATION_ID_T                f_tMsgOpId;
    VOS_UINT8                        f_ucMsgInterTpMr;
    VOS_UINT8                        ucSmsRealRecNum;                        /* 从USIM获得的SMS实际记录数 */
    VOS_BOOL                         bEfSmsState;                            /* USIM中是否存在EfSms的标志*/
    VOS_BOOL                         f_bMsgCsRegFlag;
    VOS_BOOL                         f_bMsgPsRegFlag;

    MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
    MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
    MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
    MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
    MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
    VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST;

#define MN_MSG_SEG_USIM_SMS_NUM                                             10
typedef struct
{
    VOS_UINT8                           ucSeqNum;                               /*短信内容消息发送的序号，从0开始计数*/
    VOS_UINT8                           ucMsgNum;                               /*当前消息中有效短信的条数*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT8                           aucEfSmsList[MN_MSG_SEG_USIM_SMS_NUM * MN_MSG_EFSMS_LEN];/* 缓存EfSms*/
} NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST;

/*****************************************************************************
 Structure      : NAS_MSG_SDT_MSG_ST
 Description    : PC回放工程，所有MSG相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART1_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART2_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                                 usMsgID;
    VOS_UINT16                                 usReserved;                            /* 在PACK(1)到PACK(4)调整中定义的保留字节 */
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST   stOutsideCtx;
}NAS_MSG_SDT_MSG_PART3_ST;

/*****************************************************************************
  4 变量定义
*****************************************************************************/
LOCAL MN_MSG_MO_BUFFER_STRU            f_stMsgMoBuffer;
LOCAL MN_MSG_MO_ENTITY_STRU            f_stMsgMoEntity;
LOCAL MN_MSG_MT_ENTITY_STRU            f_stMsgMtEntity;
LOCAL MN_MSG_USIM_EFUST_INFO_STRU      f_stEfUstInfo;                          /*EFUST的内容*/
LOCAL MN_MSG_USIM_EFSMSR_INFO_STRU     f_stMsgEfSmsrInfo;                      /*USIM中相关文件的信息*/
LOCAL MN_MSG_USIM_EFSMS_INFO_STRU      f_stMsgEfSmsInfo;
LOCAL MN_MSG_USIM_EFSMSP_INFO_STRU     f_stMsgEfSmspInfo;
LOCAL MN_MSG_USIM_SMSS_INFO_STRU       f_stMsgEfSmssInfo;
LOCAL MN_OPERATION_ID_T                f_tMsgOpId;
LOCAL VOS_UINT8                        f_ucMsgInterTpMr;
LOCAL MN_MSG_CONFIG_PARM_STRU          f_stMsgCfgParm;
LOCAL MN_MSG_SET_USIM_INFO_STRU        f_astMsgSetUsimInfo[MN_MSG_MAX_ACTION_NODE_NUM];
LOCAL MN_MSG_SET_USIM_REC_STRU         f_stMsgSetUsimRec;
LOCAL MN_MSG_USIM_STATUS_INFO_STRU     f_stMsgUsimStatusInfo;
LOCAL MN_MSG_USIM_EFSMSP_DTL_INFO_STRU f_astMsgOrgSmspInfo[MN_MSG_MAX_USIM_EFSMSP_NUM];
LOCAL VOS_UINT8                        f_aucMsgOrgSmContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN];
LOCAL VOS_UINT8                        f_aucMsgOrgSmsrContent[MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN];
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
LOCAL VOS_UINT8                        f_aucMsgNvimSmStatus[MN_MSG_MAX_NVIM_SMS_REC_NUM];/*在内存中保留NVIM中短信的状态*/
LOCAL VOS_UINT16                       f_usMsgNvimSmsCurReNum = 0;
#endif

LOCAL MN_MSG_MO_SMS_CTRL_STRU          f_stMsgMoSmsCtrlInfo;
LOCAL VOS_UINT8                        f_ucMsgNvimSmsrCurReNum = 0;
LOCAL VOS_BOOL                         f_bMsgCsRegFlag = VOS_FALSE;
LOCAL VOS_BOOL                         f_bMsgPsRegFlag = VOS_FALSE;
LOCAL MN_MSG_LINK_CTRL_U8              f_enMsgLinkCtrl = MN_MSG_LINK_CTRL_ENABLE;
LOCAL VOS_BOOL                         f_bNeedSendUsim[MN_MSG_MAX_USIM_SMS_NUM];
LOCAL MN_MSG_SEND_FAIL_FLAG_U8         f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;
LOCAL MN_MSG_RETRY_INFO_STRU           f_stMsgRetryInfo;
LOCAL SMR_SMT_MO_REPORT_STRU           f_stMsgRpErrInfo;
MN_MSG_CLASS0_TAILOR_U8                g_enMsgClass0Tailor;
#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT8                              g_ucSetEfSmspNoRsp = 0;
VOS_UINT8                              g_ucDisableMoRetry = 0;
#endif


/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/
#ifdef __PS_WIN32_RECUR__


VOS_UINT32 NAS_MSG_RestoreContextData_Part1(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;
    VOS_UINT32                                     ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU                  stMtCustomize;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART1_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART1 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgCfgParm, &pstOutsideCtx->f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
        PS_MEM_CPY(&f_stEfUstInfo, &pstOutsideCtx->f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
        PS_MEM_CPY(f_astMsgOrgSmspInfo,
                   pstOutsideCtx->f_astMsgOrgSmspInfo,
                   (sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM));

        f_stMsgEfSmssInfo.bEfSmssState = f_stEfUstInfo.bEfSmssFlag;
        f_stMsgEfSmspInfo.bEfSmspState = f_stEfUstInfo.bEfSmspFlag;
        f_stMsgEfSmsrInfo.bEfSmsrState = f_stEfUstInfo.bEfSmsrFlag;
        f_stMsgEfSmsInfo.bEfSmsState   = f_stEfUstInfo.bEfSmsFlag;

        PS_MEM_CPY(f_aucMsgOrgSmsrContent,
                   pstOutsideCtx->f_aucMsgOrgSmsrContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));
        f_enMsgSendFailFlag = pstOutsideCtx->f_enMsgSendFailFlag;
        g_enMsgClass0Tailor = pstOutsideCtx->g_enMsgClass0Tailor;

        PS_MEM_CPY(&f_stMsgRetryInfo, &pstOutsideCtx->f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
        PS_MEM_CPY(&f_stMsgRpErrInfo, &pstOutsideCtx->f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

        stMtCustomize.ucActFlag     = MN_MSG_NVIM_ITEM_ACTIVE;
        stMtCustomize.enMtCustomize = pstOutsideCtx->enMtCustomize;
        ulRet                       = NV_Write(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                                               &stMtCustomize,
                                               sizeof(stMtCustomize));
        if (NV_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MSG_RestoreContextData_Part1: Fail to write en_NV_Item_SMS_MO_RETRY_PERIOD.");
        }

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part1 data is restored.");
    }
    return MN_ERR_NO_ERROR;
}


VOS_UINT32 NAS_MSG_RestoreContextData_Part2(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART2_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART2== pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        f_enMsgLinkCtrl = pstOutsideCtx->f_enMsgLinkCtrl;
        f_tMsgOpId = pstOutsideCtx->f_tMsgOpId;
        f_ucMsgInterTpMr = pstOutsideCtx->f_ucMsgInterTpMr;

        f_stMsgEfSmssInfo.stEfSmssInfo.ucLastUsedTpMr = f_ucMsgInterTpMr;

        f_stMsgEfSmsInfo.ucSmsRealRecNum = pstOutsideCtx->ucSmsRealRecNum;
        f_stMsgEfSmsInfo.bEfSmsState = pstOutsideCtx->bEfSmsState;
        f_bMsgCsRegFlag = pstOutsideCtx->f_bMsgCsRegFlag;
        f_bMsgPsRegFlag = pstOutsideCtx->f_bMsgPsRegFlag;

        PS_MEM_CPY(&f_stMsgUsimStatusInfo, &pstOutsideCtx->f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
        PS_MEM_CPY(&f_stMsgMoEntity, &pstOutsideCtx->f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgMtEntity,  &pstOutsideCtx->f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
        PS_MEM_CPY(&f_stMsgSetUsimRec, &pstOutsideCtx->f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
        PS_MEM_CPY(f_astMsgSetUsimInfo, pstOutsideCtx->f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
        PS_MEM_CPY(f_aucMsgOrgSmContent,
                   pstOutsideCtx->f_aucMsgOrgSmContent,
                   (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN));

        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part2 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32 NAS_MSG_RestoreContextData_Part3(struct MsgCB * pMsg)
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pRcvMsgCB;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MSG_SDT_MSG_PART3_ST *)pMsg;

    if (MN_MSG_PC_REPLAY_MSG_PART3 == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&f_stMsgEfSmsInfo.aucEfSmsList[(pstOutsideCtx->ucSeqNum * MN_MSG_EFSMS_LEN)],
                   pstOutsideCtx->aucEfSmsList,
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        MN_INFO_LOG("MSG: NAS_MSG_RestoreContextData_Part3 data is restored.");
    }

    return MN_ERR_NO_ERROR;
}

#endif


VOS_VOID NAS_MSG_SndOutsideContextData_Part1()
{
    NAS_MSG_SDT_MSG_PART1_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART1_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART1_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part1:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART1_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART1;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgCfgParm, &f_stMsgCfgParm, sizeof(MN_MSG_CONFIG_PARM_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stEfUstInfo, &f_stEfUstInfo, sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgOrgSmspInfo,
               f_astMsgOrgSmspInfo,
               sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU) * MN_MSG_MAX_USIM_EFSMSP_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmsrContent,
               f_aucMsgOrgSmsrContent,
               (MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN));

    pstOutsideCtx->f_enMsgSendFailFlag = f_enMsgSendFailFlag;
    pstOutsideCtx->g_enMsgClass0Tailor = g_enMsgClass0Tailor;

    pstOutsideCtx->ucMoSmsCtrlFlag     = f_stMsgMoSmsCtrlInfo.ucActFlg;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRetryInfo,&f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));

    pstOutsideCtx->enMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;
    MN_MSG_GetMtCustomizeInfo(&pstOutsideCtx->enMtCustomize);

    DIAG_TraceReport(pSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}


VOS_VOID NAS_MSG_SndOutsideContextData_Part2()
{
    NAS_MSG_SDT_MSG_PART2_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART2_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART2_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid    = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid      = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength         = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART2_ST) + 4;
    pSndMsgCB->usMsgID          = MN_MSG_PC_REPLAY_MSG_PART2;
    pSndMsgCB->usReserved       = 0;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->f_enMsgLinkCtrl  = f_enMsgLinkCtrl;
    pstOutsideCtx->f_tMsgOpId       = f_tMsgOpId;

    MN_MSG_GetTpMR(&pstOutsideCtx->f_ucMsgInterTpMr);
    pstOutsideCtx->ucSmsRealRecNum  = f_stMsgEfSmsInfo.ucSmsRealRecNum;

    pstOutsideCtx->bEfSmsState      = f_stMsgEfSmsInfo.bEfSmsState;
    pstOutsideCtx->f_bMsgCsRegFlag  = f_bMsgCsRegFlag;
    pstOutsideCtx->f_bMsgPsRegFlag  = f_bMsgPsRegFlag;

    PS_MEM_CPY(&pstOutsideCtx->f_stMsgUsimStatusInfo, &f_stMsgUsimStatusInfo, sizeof(MN_MSG_USIM_STATUS_INFO_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMoEntity, &f_stMsgMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgMtEntity,  &f_stMsgMtEntity,  sizeof(MN_MSG_MT_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->f_stMsgSetUsimRec, &f_stMsgSetUsimRec, sizeof(MN_MSG_SET_USIM_REC_STRU));
    PS_MEM_CPY(pstOutsideCtx->f_astMsgSetUsimInfo, f_astMsgSetUsimInfo, sizeof(MN_MSG_SET_USIM_INFO_STRU)*MN_MSG_MAX_ACTION_NODE_NUM);
    PS_MEM_CPY(pstOutsideCtx->f_aucMsgOrgSmContent,
               f_aucMsgOrgSmContent,
               MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}


VOS_VOID NAS_MSG_SndOutsideContextData_Part3()
{
    NAS_MSG_SDT_MSG_PART3_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST      *pstOutsideCtx;
    VOS_UINT8                                     ucLoop;
    VOS_UINT8                                     ucRemainMsgNum;
    VOS_UINT8                                     ucSendMsgNum;
    VOS_UINT8                                     ucTotalSegNum;

    pSndMsgCB = (NAS_MSG_SDT_MSG_PART3_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_MSG_SDT_MSG_PART3_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_MSG_SndOutsideContextData_Part2:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid        = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderPid          = WUEPS_PID_TAF;
    pSndMsgCB->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength             = sizeof(NAS_MSG_OUTSIDE_RUNNING_CONTEXT_PART3_ST) + 4;
    pSndMsgCB->usMsgID              = MN_MSG_PC_REPLAY_MSG_PART3;
    pSndMsgCB->usReserved           = 0;

    pstOutsideCtx                   = &pSndMsgCB->stOutsideCtx;
    pstOutsideCtx->ucSeqNum         = 0;
    pstOutsideCtx->aucReserved[0]   = 0;
    pstOutsideCtx->aucReserved[1]   = 0;
    ucTotalSegNum                   = (f_stMsgEfSmsInfo.ucSmsRealRecNum + (MN_MSG_SEG_USIM_SMS_NUM - 1))/
                                      MN_MSG_SEG_USIM_SMS_NUM;
    for (ucLoop = 0; ucLoop < ucTotalSegNum; ucLoop++)
    {
        ucSendMsgNum = (VOS_UINT8)(pstOutsideCtx->ucSeqNum * MN_MSG_SEG_USIM_SMS_NUM);
        ucRemainMsgNum = f_stMsgEfSmsInfo.ucSmsRealRecNum - ucSendMsgNum;
        if (ucRemainMsgNum > MN_MSG_SEG_USIM_SMS_NUM)
        {
            pstOutsideCtx->ucMsgNum = MN_MSG_SEG_USIM_SMS_NUM;
        }
        else
        {
            pstOutsideCtx->ucMsgNum = ucRemainMsgNum;
        }
        PS_MEM_CPY(pstOutsideCtx->aucEfSmsList,
                   &f_stMsgEfSmsInfo.aucEfSmsList[(ucSendMsgNum * MN_MSG_EFSMS_LEN)],
                   (pstOutsideCtx->ucMsgNum * MN_MSG_EFSMS_LEN));
        DIAG_TraceReport(pSndMsgCB);
        pstOutsideCtx->ucSeqNum++;
    }

    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}


VOS_VOID MN_MSG_PrintConfigParmStru(
    MN_MSG_CONFIG_PARM_STRU             *pstCfg
)
{
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvSmAct ", pstCfg->enRcvSmAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enSmMemStore ", pstCfg->enSmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enRcvStaRptAct ", pstCfg->enRcvStaRptAct);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enStaRptMemStore ", pstCfg->enStaRptMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enCbmMemStore ", pstCfg->enCbmMemStore);
    MN_INFO_LOG1("MN_MSG_PrintConfigParmStru:enAppMemStatus ", pstCfg->enAppMemStatus);
}


VOS_VOID MN_MSG_PrintMsgEntityStru(
    MN_MSG_MO_ENTITY_STRU               *pstEntity
)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: mo status          ", pstEntity->enSmaMoState);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: clientId           ", pstEntity->clientId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: opId               ", pstEntity->opId);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bEnvelopePending   ", (VOS_INT32)pstEntity->bEnvelopePending);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucMr               ", pstEntity->ucMr);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSendDomain       ", pstEntity->enSendDomain);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSaveArea         ", pstEntity->enSaveArea);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ulSaveIndex        ", (VOS_INT32)pstEntity->ulSaveIndex);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enTpduType         ", pstEntity->enTpduType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: enSmsMoType        ", pstEntity->enSmsMoType);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bReportFlag        ", (VOS_INT32)pstEntity->bReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: ucRpDataLen        ", pstEntity->ucRpDataLen);
    MN_INFO_LOG1("MN_MSG_PrintMsgEntityStru: bStaRptInd        ", (VOS_INT32)pstEntity->bStaRptInd);
}


VOS_VOID MN_MSG_PrintStoreMsgStru(
    MN_MSG_STORE_MSG_STRU               *pstSmSaved,
    VOS_UINT32                          ulSmNum
)
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;

    for (ulLoop1 = 0; ulLoop1 < ulSmNum; ulLoop1++)
    {
        MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: index, Used flag", (VOS_INT32)ulLoop1, (VOS_INT32)pstSmSaved->bUsed);
        MN_MSG_PrintMsgEntityStru(&pstSmSaved->stMoInfo);
        for (ulLoop2 = 0; ulLoop2 < MN_MSG_EFSMS_LEN; ulLoop2++)
        {
            MN_INFO_LOG2("MN_MSG_PrintStoreMsgStru: SMS content", (VOS_INT32)ulLoop2, (VOS_INT32)pstSmSaved->aucEfSmContent[ulLoop2]);
        }
        pstSmSaved++;
    }

}


VOS_VOID MN_MSG_PrintSmsrInfoStru(
    MN_MSG_USIM_EFSMSR_INFO_STRU        *pstUsimSmsr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr State flag", (VOS_INT32)pstUsimSmsr->bEfSmsrState);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr volume", pstUsimSmsr->ucSmsrRealRecNum);
    MN_INFO_LOG1("MN_MSG_PrintSmsrInfoStru: EfSmsr ocuppy", pstUsimSmsr->ucSmsrCurRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        /*Refer 31102 4.2.32 first byte is Zero, then this record is idle.*/
        MN_INFO_LOG2("MN_MSG_PrintSmsrInfoStru: index, SMS index related",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSmsr->aucEfSmsrList[(MN_MSG_EFSMSR_LEN * ulLoop)]);
    }
}


VOS_VOID MN_MSG_PrintSmsInfoStru(
    MN_MSG_USIM_EFSMS_INFO_STRU         *pstUsimSms
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms State flag", (VOS_INT32)pstUsimSms->bEfSmsState);
    MN_INFO_LOG1("MN_MSG_PrintSmsInfoStru: EfSms volume", pstUsimSms->ucSmsRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_SMS_NUM; ulLoop++)
    {
        MN_INFO_LOG2("MN_MSG_PrintSmsInfoStru: index, Sms Status",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstUsimSms->aucEfSmsList[(ulLoop * MN_MSG_EFSMS_LEN)]);
    }
}


VOS_VOID MN_MSG_PrintSmspInfoStru(
    MN_MSG_USIM_EFSMSP_INFO_STRU        *pstUsimSmsp
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSmsp;

    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp State flag", (VOS_INT32)pstUsimSmsp->bEfSmspState);
    MN_INFO_LOG1("MN_MSG_PrintSmspInfoStru: EfSmsp volume", pstUsimSmsp->ucSmspRealRecNum);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_USIM_EFSMSP_NUM; ulLoop++)
    {
        pstSmsp = &pstUsimSmsp->astEachEfSmspInfo[ulLoop];
        MN_INFO_LOG2("MN_MSG_PrintSmspInfoStru: index, bUsed flag",
                     (VOS_INT32)ulLoop,
                     (VOS_INT32)pstSmsp->bUsed);
        /*打印MN_MSG_USIM_EFSMSP_DTL_INFO_STRU内容*/
        MN_MSG_PrintSrvParamStru(&pstUsimSmsp->astEachEfSmspInfo[ulLoop].stParm);
    }
}


VOS_VOID MN_MSG_PrintSmssInfoStru(
    MN_MSG_SMSS_INFO_STRU          *pstUsimSmss
)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: ucLastUsedTpMr", pstUsimSmss->ucLastUsedTpMr);
    MN_INFO_LOG1("MN_MSG_PrintSmssInfoStru: enMemCapExcNotFlag", pstUsimSmss->enMemCapExcNotFlag);
}


VOS_VOID MN_MSG_PrintEfUstInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmssFlag", (VOS_INT32)f_stEfUstInfo.bEfSmssFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmsrFlag", (VOS_INT32)f_stEfUstInfo.bEfSmsrFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bEfSmspFlag", (VOS_INT32)f_stEfUstInfo.bEfSmspFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bMoSmsCtrlFlag", (VOS_INT32)f_stEfUstInfo.bMoSmsCtrlFlag);
    MN_INFO_LOG1("MN_MSG_PrintEfUstInfo: EF UST bSmsPpDataFlag", (VOS_INT32)f_stEfUstInfo.bSmsPpDataFlag);
}


VOS_VOID MN_MSG_PrintMsgMoEntity(VOS_VOID)
{
    MN_MSG_PrintMsgEntityStru(&f_stMsgMoEntity);
}


VOS_VOID MN_MSG_PrintMsgMtEntity(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintMsgMtEntity: f_stMsgMtEntity.enSmaMtState is ",
                 f_stMsgMtEntity.enSmaMtState);
}


VOS_VOID MN_MSG_PrintSmsrInfo(VOS_VOID)
{
    MN_MSG_PrintSmsrInfoStru(&f_stMsgEfSmsrInfo);
}


VOS_VOID MN_MSG_PrintSmsInfo(VOS_VOID)
{
    MN_MSG_PrintSmsInfoStru(&f_stMsgEfSmsInfo);
}


VOS_VOID MN_MSG_PrintSmspInfo(VOS_VOID)
{
    MN_MSG_PrintSmspInfoStru(&f_stMsgEfSmspInfo);
}


VOS_VOID MN_MSG_PrintSmssInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSmssInfo: bEfSmssState", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    MN_MSG_PrintSmssInfoStru(&f_stMsgEfSmssInfo.stEfSmssInfo);
}


VOS_VOID MN_MSG_PrintInterTpMr(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintInterTpMr: TpMr", f_ucMsgInterTpMr);
}


VOS_VOID MN_MSG_PrintCfgParm(VOS_VOID)
{
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}


VOS_VOID MN_MSG_PrintUsimStatusInfo(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: ucUsimStatus", f_stMsgUsimStatusInfo.ucUsimStatus);
    MN_INFO_LOG1("MN_MSG_PrintUsimStatusInfo: enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}


VOS_VOID MN_MSG_PrintSetUsimRec(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucList", f_stMsgSetUsimRec.ucList);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDelete", f_stMsgSetUsimRec.ucDelete);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteBegin", f_stMsgSetUsimRec.ucDeleteBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRpt", f_stMsgSetUsimRec.ucDeleteStaRpt);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteStaRptBegin", f_stMsgSetUsimRec.ucDeleteStaRptBegin);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteStaRptReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteStaRptReportFlag);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: ucDeleteEfSmsp", f_stMsgSetUsimRec.ucDeleteEfSmsp);
    MN_INFO_LOG1("MN_MSG_PrintSetUsimRec: bDeleteEfSmspReportFlag", (VOS_INT32)f_stMsgSetUsimRec.bDeleteEfSmspReportFlag);
}


VOS_VOID MN_MSG_PrintOpId(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_PrintOpId: f_tMsgOpId", f_tMsgOpId);
}


VOS_VOID MN_MSG_PrintDomainRegFlag(
    VOS_VOID
)
{
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgCsRegFlag ", (VOS_INT32)f_bMsgCsRegFlag);
    MN_INFO_LOG1("MN_MSG_PrintDomainRegFlag:f_bMsgPsRegFlag ", (VOS_INT32)f_bMsgPsRegFlag);
}



MN_MSG_LINK_CTRL_U8 MN_MSG_GetLinkCtrlParam(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetLinkCtrlParam:f_enMsgLinkCtrl ", f_enMsgLinkCtrl);
    return f_enMsgLinkCtrl;
}


VOS_UINT32 MN_MSG_UpdateLinkCtrlParam(
    MN_MSG_LINK_CTRL_U8                 setValue
)
{
    if (setValue >= MN_MSG_LINK_CTRL_BUTT)
    {
        MN_ERR_LOG("MN_MSG_SetLinkCtrl: invalid set value.");
        return MN_ERR_INVALIDPARM;
    }

    f_enMsgLinkCtrl = setValue;
    return MN_ERR_NO_ERROR;
}

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST  == FEATURE_ON)
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)

VOS_VOID MSG_InitFlashMsg(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRealSmsNum;
    VOS_UINT32                          ulFileSize;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucContent[MN_MSG_EFSMS_LEN];

    /* 如果FLASH 文件不存在，则不读取FLASH短信记录 */
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_NORM_LOG("MSG_InitFlashMsg: SmsFile not exist.");
        return;
    }

    /* 初始化所有ME短信状态为空闲 */
    PS_MEM_SET(f_aucMsgNvimSmStatus, 0X00, sizeof(f_aucMsgNvimSmStatus));

    PS_MEM_SET(aucContent, 0xff, sizeof(aucContent));

    /* 获取FLASH短信文件长度 */
    ulRet = MN_GetFileSize(gfpSmsFlash, &ulFileSize);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_InitFlashMsg: Get File Size error.");

        return;
    }

    /* 根据FLASH短信文件长度获取有效ME短信容量 */
    ulRealSmsNum = ulFileSize / MN_MSG_EFSMS_LEN;
    if (f_usMsgNvimSmsCurReNum < ulRealSmsNum)
    {
        ulRealSmsNum = f_usMsgNvimSmsCurReNum;
    }

    /* FLASH中的短信序号从0开始逐个读取到指定容量 */
    for (ulIndex = 0; ulIndex < ulRealSmsNum; ulIndex++)
    {
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex, aucContent);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MSG_InitFlashMsg: Read FLASH SMS Error");
        }
        else
        {
            f_aucMsgNvimSmStatus[ulIndex] = aucContent[0];
        }
    }

    return;
}
#else



LOCAL VOS_VOID MSG_InitNvMsg(VOS_VOID)
{
    /* NV_Read接口已经不支持ME短信，进入此函数意味着异常 */
    MN_WARN_LOG("MSG_InitNvMsg: Get File Size error.");

    return;
}

#endif


VOS_VOID MSG_InitMeMsg(VOS_VOID)
{

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    MSG_InitFlashMsg();
#else
    MSG_InitNvMsg();
#endif

}
#endif



LOCAL VOS_VOID MSG_GetNvimParmInfo(VOS_VOID)
{
    VOS_UINT32                                      ulRet;
    MN_MSG_NVIM_RETRY_PERIOD_STRU                   stNvimRetryPeriod;
    MN_MSG_NVIM_RETRY_INTERVAL_STRU                 stNvimRetryInterval;
    MN_MSG_NVIM_CLASS0_TAILOR_STRU                  stClass0Tailor;
    TAF_MSG_NVIM_RETRY_CM_SRV_REJ_CFG_STRU           stNvimRetryCmSrvRejCfg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;

    MN_INFO_LOG("MSG_GetNvimParmInfo: Step into function.");


    PS_MEM_SET(&stNvimRetryPeriod,0,sizeof(stNvimRetryPeriod));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_PERIOD, &stNvimRetryPeriod, sizeof(stNvimRetryPeriod));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryPeriod.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryPeriod = 1000 *stNvimRetryPeriod.ulRetryPeriod;    /* 需要转化为秒 */
    }
    else
    {
        f_stMsgRetryInfo.ulRetryPeriod = 0;
    }

    PS_MEM_SET(&stNvimRetryInterval,0,sizeof(stNvimRetryInterval));
    ulRet = NV_Read(en_NV_Item_SMS_MO_RETRY_INTERVAL, &stNvimRetryInterval, sizeof(stNvimRetryInterval));
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stNvimRetryInterval.ucActFlg))
    {
        f_stMsgRetryInfo.ulRetryInterval = 1000 *stNvimRetryInterval.ulRetryInterval;/* 需要转化为秒 */
    }
    else
    {
        /* 周期和间隔有一个未激活,则默认为两者都没有激活 */
        f_stMsgRetryInfo.ulRetryPeriod = 0;
        f_stMsgRetryInfo.ulRetryInterval = 0;
    }
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_PERIOD,f_stMsgRetryInfo.ulRetryPeriod);
    MN_MSG_UpdateRetryPeriod(MN_MSG_ID_WAIT_RETRY_INTERVAL,f_stMsgRetryInfo.ulRetryInterval);

    PS_MEM_SET(&stClass0Tailor,0,sizeof(stClass0Tailor));

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_CLASS0_TAILOR, &ulLength);

    ulRet = NV_Read(en_NV_Item_SMS_CLASS0_TAILOR, &stClass0Tailor, ulLength);
    if ( (NV_OK == ulRet)
      && (MN_MSG_NVIM_ITEM_ACTIVE == stClass0Tailor.ucActFlg))
    {
        g_enMsgClass0Tailor = stClass0Tailor.enClass0Tailor;
    }
    else
    {
        g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MSG_InitMeMsg();
#endif

    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);

    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG, &ulLength);

    if (ulLength > sizeof(stNvimRetryCmSrvRejCfg))
    {
        f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
        return;
    }

    PS_MEM_SET(&stNvimRetryCmSrvRejCfg, 0x0, sizeof(stNvimRetryCmSrvRejCfg));

    ulRet = NV_Read(en_NV_Item_SMS_RETRY_CM_SRV_REJ_CAUSE_CFG,
                    &stNvimRetryCmSrvRejCfg,
                    sizeof(stNvimRetryCmSrvRejCfg));

    if (NV_OK != ulRet)
    {
       f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = 0;
       return;
    }

    if (stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum > TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM)
    {
        stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum = TAF_NVIM_SMS_RETRY_CAUSE_MAX_NUM;
    }

    f_stMsgRetryInfo.ucSmsRetryCmSrvRejNum = stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum;

    PS_MEM_CPY(f_stMsgRetryInfo.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.aucSmsRetryCmSrvRejCause,
               stNvimRetryCmSrvRejCfg.ucSmsRetryCmSrvRejCauseNum);
}


VOS_UINT32  MN_MSG_ReadAddressFromUsim(
    const VOS_UINT8                     *pucAddrStr,
    VOS_BOOL                            bRpAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr
)
{
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    VOS_UINT32                          ulAddrLen;
    VOS_UINT32                          ulRet;

    ulAddrLen = pucAddrStr[0];

    if (MN_MSG_USIM_FILL_BYTE != ulAddrLen)
    {
        ulRet = MN_MSG_DecodeAddress(pucAddrStr,
                                     bRpAddr,
                                     &stAsciiAddr,
                                     &ulAddrLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        ulRet = TAF_STD_ConvertAsciiAddrToBcd(&stAsciiAddr, pstBcdAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    else
    {
        PS_MEM_SET(pstBcdAddr, 0x00, sizeof(MN_MSG_BCD_ADDR_STRU));
    }

    return MN_ERR_NO_ERROR;
}


LOCAL VOS_VOID MSG_ParseSmsp(
    VOS_UINT8                           ucLen,
    const VOS_UINT8                     *pucSmspContent,
    VOS_BOOL                            *pbSrvParmPresent,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();


    if (ucLen < MN_MSG_MIN_SRV_PARM_LEN)
    {
        *pbSrvParmPresent = VOS_FALSE;
        return;
    }

    *pbSrvParmPresent = VOS_TRUE;

    /*alpha identifier data:*/
    pstSrvParam->stAlphaIdInfo.ulLen = ucLen - MN_MSG_MIN_SRV_PARM_LEN;
    PS_MEM_CPY(pstSrvParam->stAlphaIdInfo.aucData,
               pucSmspContent,
               pstSrvParam->stAlphaIdInfo.ulLen);

    ulPos       = pstSrvParam->stAlphaIdInfo.ulLen;

    /*parameter idicator data:*/
    /*lint -e961*/
    pstSrvParam->ucParmInd = pucSmspContent[ulPos++];
    /*lint +e961*/

    /*TP-destination address data:*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_FALSE,
                                           &pstSrvParam->stDestAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get Destination.");
            PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stDestAddr), 0x00, sizeof(pstSrvParam->stDestAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP-service centre address data:*/
    /* 在解析短信中心号码前，先判断一下短信中心号码长度字节，如果长度有效，
       就把ind的标示bit置为存在短信中心号码，9061 nv项可配置
       24011 8.2.5.2 Destination address element
       In the case of MO transfer, this element contains the destination Service Centre address.
       The RP Destination Address information element is coded as shown in figure 8.6/3GPP TS 24.011.
       The RP Destination Address is a type 4 information element. In the mobile station to network
       direction the minimum value of the length octet is 2 and the maximum value is 11. In the network to mobile station direction,
       the value of the length octet of the element is set to 0.*/
    if ((MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetScAddrIgnoreScIndication)
     && (pucSmspContent[ulPos] >= TAF_MSG_MIN_DESTINATION_ADDRESS_LEN)
     && (pucSmspContent[ulPos] <= TAF_MSG_MAX_DESTINATION_ADDRESS_LEN))
    {
        pstSrvParam->ucParmInd &= ~MN_MSG_SRV_PARM_MASK_SC_ADDR;
    }

    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
    {
        ulRet = MN_MSG_ReadAddressFromUsim(&pucSmspContent[ulPos],
                                           VOS_TRUE,
                                           &pstSrvParam->stScAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG("MSG_ParseSmsp: Fail to get service centre.");
            PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
        }
    }
    else
    {
        PS_MEM_SET(&(pstSrvParam->stScAddr), 0x00, sizeof(pstSrvParam->stScAddr));
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-PID:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
        {
            pstSrvParam->ucPid = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucPid = 0;
        }
    }
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
        /*TP-DCS:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
        {
            pstSrvParam->ucDcs = pucSmspContent[ulPos];
        }
        else
        {
            pstSrvParam->ucDcs = 0;
        }
    }
    ulPos++;

    if ( MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucGetCsmpParaFromUsimSupportFlg )
    {
         /*TP-VP:*/
        if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
        {
            /*lint -e961*/
            pstSrvParam->ucValidPeriod = pucSmspContent[ulPos++];
            /*lint +e961*/
        }
        else
        {
            pstSrvParam->ucValidPeriod = 0;
        }
    }

    return;
}


LOCAL VOS_UINT32 MSG_GetUsimFileReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

    ulRet = USIMM_API_WRONG_PARA;

    switch (usEfId)
    {
        case USIMM_USIM_EFUST_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
#if ( VOS_WIN32 == VOS_OS_VER )
            if (0 == g_ucSetEfSmspNoRsp)
            {
                ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
            }
#else
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, MN_MSG_EF_FIRST_RECORD);
#endif

            break;
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            ulRet = MN_MSG_SndUsimGetMaxRecReq(usEfId);
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            ulRet = MN_MSG_SndUsimGetFileReq(usEfId, 0);
            break;
        default:
            break;
    }

    return ulRet;
}


 VOS_VOID MN_MSG_SetSmsFileRefreshFlag (VOS_UINT16 usEfId, VOS_UINT8 ucFileRefreshFlag)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSP_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMS_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag = ucFileRefreshFlag;
             break;

        case USIMM_USIM_EFSMSR_ID:
             stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag = ucFileRefreshFlag;
             break;

       default:
            MN_WARN_LOG("MN_MSG_SetSmsFileRefreshFlag: The input file name is invalid.");
            break;
    }
}


VOS_UINT8 MN_MSG_GetSmsFileRefreshFlag (VOS_UINT16 usEfId)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmssNeedRefreshFlag;

        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmspNeedRefreshFlag;

        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsNeedRefreshFlag;

        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
             return stUsimFilesNeedRefreshFlag.ucEfSmsrNeedRefreshFlag;

       default:
            MN_WARN_LOG("MN_MSG_GetSmsFileRefreshFlag: The input file name is invalid.");
            return VOS_FALSE;
    }
}


VOS_VOID MN_MSG_GetUsimParmReq(
    VOS_UINT16                          usEfId
)
{
    VOS_UINT32                          ulRet;

     /* 读取文件的条件发生变化，由文件存在就读取改为文件存在且需要更新才读取 */

    switch (usEfId)
    {
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmssFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                        break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmspFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            /* fall through */
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }
            /* fall through */
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stEfUstInfo.bEfSmsrFlag)
            {
                if (VOS_TRUE == MN_MSG_GetSmsFileRefreshFlag(usEfId))
                {
                    ulRet = MSG_GetUsimFileReq(usEfId);
                    if (USIMM_API_SUCCESS == ulRet)
                    {
                         break;
                    }
                }
            }

            /* fall through */
       default:
            /*所有节点都加入失败,则置上电完成*/
            f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;

            /*向应用上报初始化完成*/
            MN_MSG_SmInitFinish(MN_CLIENT_ALL);

            #ifndef __PS_WIN32_RECUR__

            if ( (VOS_TRUE == g_ucMnOmConnectFlg)
              && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
            {
                NAS_MSG_SndOutsideContextData_Part1();
                NAS_MSG_SndOutsideContextData_Part2();
                NAS_MSG_SndOutsideContextData_Part3();
            }
            #endif

            break;
    }
}


VOS_VOID  MN_MSG_ReadMsgNvimInfo( VOS_VOID )
{
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 enMeStorageEnable;

    MN_MSG_GetSmsServicePara(&f_stMsgCfgParm, &enMeStorageEnable);
    MN_MSG_MtSpecificFeatureInit();

    MN_MSG_CloseSmsCapabilityFeatureInit();
}


VOS_VOID MN_MSG_SmInit(VOS_VOID)
{
    VOS_UINT32                          i;

    PS_MEM_SET(&f_stMsgEfSmsrInfo,0X00,sizeof(f_stMsgEfSmsrInfo));
    PS_MEM_SET(&f_stMsgEfSmsInfo,0X00,sizeof(f_stMsgEfSmsInfo));
    PS_MEM_SET(&f_stMsgEfSmssInfo,0X00,sizeof(f_stMsgEfSmssInfo));
    PS_MEM_SET(&f_stMsgEfSmspInfo,0X00,sizeof(f_stMsgEfSmspInfo));

    PS_MEM_SET(&f_stEfUstInfo,0X00,sizeof(f_stEfUstInfo));
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    PS_MEM_SET(f_aucMsgNvimSmStatus,0X00,MN_MSG_MAX_NVIM_SMS_REC_NUM);
#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if(VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_NORM_LOG("MN_MSG_SmInit:Open SmsFile Fail.\n");
        }
    }
#endif
#endif
    f_ucMsgNvimSmsrCurReNum= 0;

    f_stMsgEfSmssInfo.stEfSmssInfo.enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
    f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;
    f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;


    f_stMsgCfgParm.enSmsServVersion = MN_MSG_CSMS_MSG_VERSION_PHASE2_PLUS;

    f_stMsgCfgParm.enMtType         = MN_MSG_CNMI_MT_NO_SEND_TYPE;

    MN_MSG_ReadMsgNvimInfo();

    f_ucMsgInterTpMr = 1;
    for (i = 0; i < MN_MSG_MAX_USIM_SMS_NUM; i++ )
    {
        f_bNeedSendUsim[i] = VOS_FALSE;
    }
    PS_MEM_SET(&f_stMsgRetryInfo,0,sizeof(f_stMsgRetryInfo));
    g_enMsgClass0Tailor = MN_MSG_CLASS0_DEF;

    MN_MSG_InitMoBuffer();
    MN_MSG_DestroyMoInfo();
    MN_MSG_DestroyMtInfo();

    PS_MEM_SET(f_aucMsgOrgSmContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMS_LEN);
    PS_MEM_SET(f_aucMsgOrgSmsrContent,(VOS_CHAR)0XFF,MN_MSG_MAX_ORG_REC_NUM * MN_MSG_EFSMSR_LEN);
    PS_MEM_SET(f_astMsgOrgSmspInfo,(VOS_CHAR)0XFF,MN_MSG_MAX_USIM_EFSMSP_NUM * sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_MSG_DestroyUsimNode(i);
    }

    PS_MEM_SET(&f_tMsgOpId,0X00,sizeof(f_tMsgOpId));
    PS_MEM_SET(&f_stMsgSetUsimRec,0X00,sizeof(f_stMsgSetUsimRec));
    f_enMsgSendFailFlag = MN_MSG_SEND_FAIL_NO_DOMAIN;

    /*初始化USIM中的相关参数*/
    MN_MSG_InitParm();

    MN_MSG_GetFdnMeCfg();

    /*初始化定时器相关参数*/
    MN_MSG_InitAllTimers();

    MSG_GetNvimParmInfo();

}



MN_MSG_MO_STATE_ENUM_U8 MN_MSG_GetMoState(VOS_VOID)
{
    MN_INFO_LOG1("MN_MSG_GetMoState: f_stMsgMoEntity.enSmaMoState is ", f_stMsgMoEntity.enSmaMoState);
    return f_stMsgMoEntity.enSmaMoState;
}


VOS_VOID MN_MSG_SetMoRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMoEntity.enMsgSignallingType = enMsgSignallingType;
}


TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMoRouteStackType(VOS_VOID)
{
    return f_stMsgMoEntity.enMsgSignallingType;
}


MN_MSG_MT_STATE_ENUM_U8 MN_MSG_GetMtState(VOS_VOID)
{
    return f_stMsgMtEntity.enSmaMtState;
}


VOS_VOID TAF_MSG_SetMtState(
    MN_MSG_MT_STATE_ENUM_U8             enSmaMtState
)
{
    f_stMsgMtEntity.enSmaMtState = enSmaMtState;
}



VOS_VOID MN_MSG_SetMtRouteStackType(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    f_stMsgMtEntity.enMsgSignallingType = enMsgSignallingType;
}


TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 MN_MSG_GetMtRouteStackType(VOS_VOID)
{
    return f_stMsgMtEntity.enMsgSignallingType;
}



VOS_VOID MN_MSG_GetMoEntity(
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
)
{
    PS_MEM_CPY(pstMoEntity,&f_stMsgMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));
}


VOS_UINT32 MN_MSG_GetStoreMsgIndex(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    /*获取当前空闲缓存；*/
    for(i = 0; i < f_stMsgMoBuffer.ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_FALSE == pstMoBuffer->bUsed)
        {
            ulIndex = i;
            break;
        }
    }

    return ulIndex;
}


VOS_VOID  MN_MSG_SaveStoreMsg(
    VOS_UINT32                          ulIndex,
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity,
    const VOS_UINT8                     *pucEfSmContent
)
{
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_SaveStoreMsg: Invalid enulIndex. ");
        return;
    }

    /*若缓存中已存在一个SMMA消息，则丢弃当前待缓存的SMMA消息*/
    if (MN_MSG_MO_TYPE_SMMA == pstMoEntity->enSmsMoType)
    {
        for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
        {
            pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
            if (VOS_FALSE == pstMoBuffer->bUsed)
            {
                if (MN_MSG_MO_TYPE_SMMA == pstMoBuffer->stMoInfo.enSmsMoType)
                {
                    return;
                }
            }
        }
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_TRUE;
    PS_MEM_CPY(&pstMoBuffer->stMoInfo, pstMoEntity, sizeof(MN_MSG_MO_ENTITY_STRU));
    PS_MEM_CPY(pstMoBuffer->aucEfSmContent, pucEfSmContent, MN_MSG_EFSMS_LEN);
}


VOS_UINT32  MN_MSG_GetStoreMsg(
    MN_MSG_STORE_MSG_STRU               *pstStoreMsg
)
{
    VOS_UINT32                          i;

    VOS_UINT32                          ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    for (i = 0; i < ulTotal; i++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + i;
        if (VOS_TRUE == pstMoBuffer->bUsed)
        {
            PS_MEM_CPY(pstStoreMsg, pstMoBuffer,sizeof(MN_MSG_STORE_MSG_STRU));

            ulSaveIndex = i;
            break;
        }
    }
    return ulSaveIndex;
}


VOS_VOID  MN_MSG_FreeStoreMsg(
    VOS_UINT32                          ulIndex
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    VOS_UINT32                          ulTotal;

    ulTotal = MN_MSG_GetMoBufferCap();
    if (ulIndex >= ulTotal)
    {
        MN_ERR_LOG("MN_MSG_FreeStoreMsg: Invalid enulIndex. ");
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->bUsed = VOS_FALSE;
    PS_MEM_SET(&pstMoBuffer->stMoInfo, 0X00, sizeof(MN_MSG_MO_ENTITY_STRU));
}


VOS_VOID MN_MSG_CreateMoInfo(
    const MN_MSG_MO_ENTITY_STRU         *pstMoEntity
)
{
    PS_MEM_CPY(&f_stMsgMoEntity,pstMoEntity,sizeof(MN_MSG_MO_ENTITY_STRU));

    /* 更新短信业务是否存在标志 */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }

    return;
}


VOS_VOID MN_MSG_UpdateMoSaveInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enSaveArea,
    VOS_UINT32                          ulSaveIndex
)
{
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != f_stMsgMoEntity.enSmaMoState)
    {
        return;
    }

    f_stMsgMoEntity.enSaveArea  = enSaveArea;
    f_stMsgMoEntity.ulSaveIndex = ulSaveIndex;
    return;
}


VOS_VOID MN_MSG_UpdateSmaMoState(
    MN_MSG_MO_STATE_ENUM_U8             enSmaMoState
)
{
    f_stMsgMoEntity.enSmaMoState = enSmaMoState;
}


VOS_UINT32 MN_MSG_MoRetryFlag(
    VOS_VOID
)
{
    MN_MSG_RETRY_INFO_STRU              stRetryInfo;

    PS_MEM_SET(&stRetryInfo, 0, sizeof(stRetryInfo));

    MN_MSG_GetRetryInfo(&stRetryInfo);
    if (0 != stRetryInfo.ulRetryPeriod)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo(VOS_VOID)
{
    /*
        有同时收发短信的情况，MO Destroy时，有可能还有MT流程存在
        Destroy IMS域MO时,不存在IMS域MT流程,把IMS标志置为FALSE
        Destroy CS域MO时,不存在CS域MT流程,把CS标志置为FALSE
        Destroy PS域MO时,不存在PS域MT流程,把PS标志置为FALSE
   */

    /* MT状态为NULL，清除所有的标志 */
    if (MN_MSG_MT_STATE_NULL == f_stMsgMtEntity.enSmaMtState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif

        return;
    }

    /* Destroy IMS域MO时,不存在IMS域MT流程,把IMS标志置为FALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMoEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMtEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
    else
    {
        /* Destroy CS域MO时,不存在CS域MT流程,把CS标志置为FALSE */
        if ( (MN_MSG_SEND_DOMAIN_CS == f_stMsgMoEntity.enSendDomain)
          && (MN_MSG_RCV_DOMAIN_CS != f_stMsgMtEntity.enRcvDomain) )

        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
        }
        /* Destroy PS域MO时,不存在PS域MT流程,把PS标志置为FALSE */
        else if ( (MN_MSG_SEND_DOMAIN_PS == f_stMsgMoEntity.enSendDomain)
               && (MN_MSG_RCV_DOMAIN_PS != f_stMsgMtEntity.enRcvDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }
}


VOS_VOID TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo(VOS_VOID)
{
    /*
        有同时收发短信的情况，MT Destroy时，有可能还有MO流程存在
        Destroy IMS域MT时,不存在IMS域MO流程,把IMS标志置为FALSE
        Destroy CS域MT时,不存在CS域MO流程,把CS标志置为FALSE
        Destroy PS域MT时,不存在PS域MO流程,把PS标志置为FALSE
   */

    /* MO状态为NULL，清除所有的标志 */
    if (MN_MSG_MO_STATE_NULL == f_stMsgMoEntity.enSmaMoState)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);
        TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 给MTC模块上报当前CS域业务状态 */
        TAF_SendMtcCsSrvInfoInd();
#endif
        return;
    }

    /* Destroy IMS域MT时,不存在IMS域MO流程,把IMS标志置为FALSE */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP != f_stMsgMoEntity.enMsgSignallingType)
        {
            TAF_SDC_SetImsSmsSrvExistFlg(VOS_FALSE);
        }
    }
    else
    {
        /* Destroy CS域MT时,不存在CS域MO流程,把CS标志置为FALSE */
        if ( (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
          && (MN_MSG_SEND_DOMAIN_CS != f_stMsgMoEntity.enSendDomain) )
        {

            TAF_SDC_SetCsSmsSrvExistFlg(VOS_FALSE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
        }

        /* Destroy PS域MT时,不存在PS域MO流程,把PS标志置为FALSE */
        else if ( (MN_MSG_RCV_DOMAIN_PS == f_stMsgMtEntity.enRcvDomain)
               && (MN_MSG_SEND_DOMAIN_PS != f_stMsgMoEntity.enSendDomain) )
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_FALSE);
        }
        else
        {
        }
    }

}


VOS_VOID MN_MSG_DestroyMoInfo(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* 更新业务标识时，要用到MO实体信息，要求清除实体信息放在更新标识后面 */
    TAF_MSG_UpdateSmsExistFlg_DestroyMoInfo();

    f_stMsgMoEntity.enSmaMoState = MN_MSG_MO_STATE_NULL;
    f_stMsgMoEntity.bEnvelopePending = VOS_FALSE;
    f_stMsgMoEntity.bReportFlag = VOS_FALSE;
    f_stMsgMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
    f_stMsgMoEntity.ulSaveIndex = 0x00;
    f_stMsgMoEntity.enSmsMoType = MN_MSG_MO_TYPE_MAX;
    f_stMsgMoEntity.opId = 0x00;
    f_stMsgMoEntity.clientId = 0x00;
    f_stMsgMoEntity.ucMr = 0x00;
    f_stMsgMoEntity.ucRpDataLen = 0X00;
    f_stMsgMoEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;
    f_stMsgMoEntity.enSendDomain        = MN_MSG_SEND_DOMAIN_NO;

    PS_MEM_SET(f_stMsgMoEntity.aucRpDataInfo,0X00,MN_MSG_MAX_RPDATA_LEN);
    PS_MEM_SET(&f_stMsgRpErrInfo,0,sizeof(f_stMsgRpErrInfo));

    /* 当前没有设置重发则清除发送失败记录
       避免其对后续发送流程的影响 */
    ulRet = MN_MSG_MoRetryFlag();
    if (TAF_TRUE != ulRet)
    {
        MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);
    }

}


VOS_VOID MN_MSG_CreateMtInfo(VOS_VOID)
{
    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_WAIT_REPORT_REQ;

    /* 更新短信业务是否存在标志 */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == f_stMsgMtEntity.enMsgSignallingType)
    {
        TAF_SDC_SetImsSmsSrvExistFlg(VOS_TRUE);
    }
    else
    {
        if (MN_MSG_RCV_DOMAIN_CS == f_stMsgMtEntity.enRcvDomain)
        {
            TAF_SDC_SetCsSmsSrvExistFlg(VOS_TRUE);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
            /* 给MTC模块上报当前CS域业务状态 */
            TAF_SendMtcCsSrvInfoInd();
#endif
        }
        else
        {
            TAF_SDC_SetPsSmsSrvExistFlg(VOS_TRUE);
        }
    }

    return;
}


VOS_VOID MN_MSG_DestroyMtInfo(VOS_VOID)
{

    /* 更新业务标识时，要用到MT实体信息，要求清除实体信息放在更新标识后面 */
    TAF_MSG_UpdateSmsExistFlg_DestroyMtInfo();

    f_stMsgMtEntity.enSmaMtState = MN_MSG_MT_STATE_NULL;

    f_stMsgMtEntity.enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_BUTT;

    f_stMsgMtEntity.enRcvDomain  = MN_MSG_RCV_DOMAIN_BUTT;

}



VOS_UINT32 MN_MSG_CreateNewUsimNode(
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
)
{
    VOS_UINT32                          i;

    MN_INFO_LOG("MN_MSG_CreateNewUsimNode: step into function.");
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        MN_NORM_LOG1("MN_MSG_CreateNewUsimNode: f_astMsgSetUsimInfo[i].bUsed is ", (VOS_INT32)f_astMsgSetUsimInfo[i].bUsed);
        if (VOS_FALSE == f_astMsgSetUsimInfo[i].bUsed)
        {
            PS_MEM_SET(&f_astMsgSetUsimInfo[i].stUsimInfo,0X00,sizeof(MN_MSG_USIM_INFO_STRU));
            PS_MEM_CPY(&f_astMsgSetUsimInfo[i].stUsimInfo,pstSmaUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
            *pulIndex = i;
            f_astMsgSetUsimInfo[i].bUsed = VOS_TRUE;
            return VOS_OK;
        }
    }
    /*不允许走到这里*/
    MN_ERR_LOG("MN_MSG_CreateNewUsimNode: failed to create action node.");;
    return VOS_ERR;
}


VOS_VOID MN_MSG_DestroyUsimNode(
    VOS_UINT32                          ulIndex
)
{
    if (ulIndex >= MN_MSG_MAX_ACTION_NODE_NUM)
    {
        MN_ERR_LOG("MN_MSG_DestroyUsimNode: Invalid enulIndex. ");
        return;
    }
    PS_MEM_SET(&f_astMsgSetUsimInfo[ulIndex],0X00,sizeof(MN_MSG_USIM_INFO_STRU));
}


VOS_VOID MN_MSG_UpdateUstInfo()
{
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    /* E5关闭短信功能 */
    f_stEfUstInfo.bEfSmsFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);
    f_stEfUstInfo.bEfSmssFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMS);

    /* PS RECUR因为不能通过定时器超时结束初始化过程关闭SMSR文件读取功能 E5关闭短信功能 */
#ifdef __PS_WIN32_RECUR__
    f_stEfUstInfo.bEfSmsrFlag = VOS_FALSE;
#else
    f_stEfUstInfo.bEfSmsrFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSR);
#endif

    f_stEfUstInfo.bEfSmspFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_SMSP);

    f_stEfUstInfo.bMoSmsCtrlFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_MOSMS_CONTROL);

    if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsPpDownlodSupportFlg)
    {
        f_stEfUstInfo.bSmsPpDataFlag = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_DATA_DL_SMSPP);
    }

}


VOS_UINT32 MN_MSG_MoFeatureAvailable(VOS_VOID)
{
    VOS_UINT8                           ucActFlg;

    MN_MSG_GetCloseSMSFeature(&ucActFlg);

    /* 关闭短信功能 */
    if (MN_MSG_NVIM_ITEM_ACTIVE == ucActFlg)
    {
        return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
    }

    if (VOS_TRUE == gstMmaValue.stEfustServiceCfg.ucForbidSndMsg)
    {
        if ((VOS_TRUE != f_stEfUstInfo.bEfSmsFlag)
         && (VOS_TRUE != f_stEfUstInfo.bEfSmspFlag))
        {
            return MN_ERR_CLASS_SMS_FEATURE_INAVAILABLE;
        }
    }

    return MN_ERR_NO_ERROR;
}



VOS_VOID MN_MSG_UpdateSmssInfo(
    VOS_BOOL                            bEfSmssState,
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo,
    VOS_UINT32                          ulFileLen
)
{
    f_stMsgEfSmssInfo.bEfSmssState = bEfSmssState;
    f_stMsgEfSmssInfo.ulFileLen = ulFileLen;
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));
}


VOS_VOID MN_MSG_GetTpMR(
    VOS_UINT8                           *pucTpMr
)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        *pucTpMr = stSmssInfo.ucLastUsedTpMr;
    }
    else
    {
        *pucTpMr = f_ucMsgInterTpMr;
        f_ucMsgInterTpMr++;
    }
}


VOS_VOID MN_MSG_AddTpMR(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK == ulRet)
    {
        /*设置TP-MR的值并存入USIM或NVIM中*/
        stSmssInfo.ucLastUsedTpMr++;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }
}


VOS_UINT32  MN_MSG_ReadSmssInfo(
    MN_MSG_SMSS_INFO_STRU               *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;

    MN_NORM_LOG1("MN_MSG_ReadSmssInfo: EF SMSS is available in SIM ", (VOS_INT32)f_stMsgEfSmssInfo.bEfSmssState);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSS_PARA_LEN);
    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        PS_MEM_CPY(pstSmssInfo,&f_stMsgEfSmssInfo.stEfSmssInfo,sizeof(MN_MSG_SMSS_INFO_STRU));
    }
    else
    {
        ulRet = NV_Read(en_NV_Item_SMS_EFSMSS_Para, &stSmssContent, MN_MSG_EFSMSS_PARA_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmssInfo:Read NVIM Smss Error");
            return VOS_ERR;
        }
        pstSmssInfo->ucLastUsedTpMr = (stSmssContent.aucSmsEfsmssPara)[0];
        if (MN_MSG_SIM_MEM_FULL_SET == (stSmssContent.aucSmsEfsmssPara)[1])
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_SET;
        }
        else
        {
            pstSmssInfo->enMemCapExcNotFlag = MN_MSG_MEM_FULL_UNSET;
        }
    }
    MN_MSG_PrintSmssInfoStru(pstSmssInfo);
    return VOS_OK;
}


VOS_VOID MN_MSG_Internal_SendRpt(
    VOS_BOOL                            bRpAck   ,                              /*is Rp-Ack or Rp-Error*/
    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause,                              /*used when bRpAck==FALSE*/
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause                               /*TP-Cause*/
)
{
    VOS_UINT8                           ucSendLen;
    VOS_UINT8                           aucSendData[MN_MSG_MAX_LEN];
    VOS_UINT32                          ulRet;
    MN_MSG_RP_ACK_STRU                  stRpAck;
    MN_MSG_RP_ERR_STRU                  stRpErr;
    VOS_UINT8                           ucIdx = 0;
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;

    PS_MEM_SET(aucSendData,0X00,MN_MSG_MAX_LEN);
    if (VOS_TRUE == bRpAck)
    {
        PS_MEM_SET(&stRpAck,0X00,sizeof(stRpAck));
        stRpAck.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ACK;
        stRpAck.bRpUserDataExist = VOS_FALSE;
        MN_MSG_EncodeRpAck(&stRpAck,aucSendData,&ucSendLen);
    }
    else
    {
        PS_MEM_SET(&stRpErr,0X00,sizeof(stRpErr));
        stRpErr.ucRpMsgType = MN_MSG_RP_MTI_UP_RP_ERR;
        stRpErr.ucRpCauseLen = 1;
        stRpErr.stRpCause.bDiagnosticsExist = VOS_FALSE;
        stRpErr.stRpCause.enRpCause = enRpCause;
        stRpErr.bRpUserDataExist = VOS_TRUE;
        stRpErr.ucRpUserDataIei = MN_MSG_RP_USER_DATA_IEI;
        /*lint -e961*/
        stRpErr.aucRpUserData[ucIdx++] = MN_MSG_TP_MTI_DELIVER_REPORT;          /*TP-Message type indicator*/
        stRpErr.aucRpUserData[ucIdx++] = enTpCause;                             /*Tp Cause*/
        stRpErr.aucRpUserData[ucIdx++] = 0;
        /*lint +e961*/
        stRpErr.ucRpUserDataLen = ucIdx;
        MN_MSG_EncodeRpErr(&stRpErr,aucSendData,&ucSendLen);

        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_SMS_MT_FAIL,
                        &(enRpCause),
                        sizeof(MN_MSG_RP_CAUSE_ENUM_U8));
    }

    enMsgSignallingType = MN_MSG_GetMtRouteStackType();

    ulRet = MN_MSG_SendSmsRpReportReq(aucSendData,ucSendLen, enMsgSignallingType);

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpReportReq Send Msg Failed");
    }
}


LOCAL VOS_BOOL MSG_RequireDelete(
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_UINT8                           ucStatus
)
{
    VOS_BOOL                            bDeleteFlag = VOS_FALSE;

    if (MN_MSG_DELETE_ALL == enDeleteType)
    {
        bDeleteFlag = VOS_TRUE;
    }
    else if (MN_MSG_DELETE_READ == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_UNREAD == enDeleteType)
    {
        if (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_SEND_TO_NT == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else if (MN_MSG_DELETE_NOT_SENT == enDeleteType)
    {
        if (EF_SMS_STATUS_MO_TO_BE_SEND == ucStatus)
        {
            bDeleteFlag = VOS_TRUE;
        }
    }
    else
    {
        bDeleteFlag = VOS_FALSE;
    }

    return bDeleteFlag;
}



VOS_UINT32 MN_MSG_DeleteMultiSm(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_DELETE_TYPE_ENUM_U8          enDeleteType,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT32                          *pulDeleteCount
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulSmCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;
    VOS_BOOL                            bDeleteFlag;
    VOS_UINT32                          ulDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteBegin;
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON) && (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    MN_MSG_WRITE_USIM_INFO_STRU         stWriteUsimInfo;
#else
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    *pbDeleteAll = VOS_TRUE;
    ulSmCapacity = MN_MSG_GetSmCapacity(enMemStore);
    for (i = ucBeginIndex; i < ulSmCapacity; i++)
    {
        ulRet = MN_MSG_GetStatus(enMemStore,i,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            ulRet = MN_ERR_NO_ERROR;
            continue;
        }

        bDeleteFlag = MSG_RequireDelete(enDeleteType, ucStatus);
        if (VOS_TRUE == bDeleteFlag)
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            aucSmContent[0] = EF_SMS_STATUS_FREE_SPACE;

#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)\
  || (NAS_FEATURE_SMS_FLASH_SMSEXIST != FEATURE_ON))
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = ulFileId;
            stSmaUsimInfo.enDeleteType = enDeleteType;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
            ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_TRUE,&stSmaUsimInfo,aucSmContent);
#else
            if (MN_MSG_MEM_STORE_SIM == enMemStore)
            {
                PS_MEM_SET(&stWriteUsimInfo,0X00,sizeof(stWriteUsimInfo));
                stWriteUsimInfo.stUsimInfo.clientId = clientId;
                stWriteUsimInfo.stUsimInfo.opId = opId;
                stWriteUsimInfo.stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
                stWriteUsimInfo.stUsimInfo.enDeleteType = enDeleteType;
                stWriteUsimInfo.stUsimInfo.ucRecIndex = (VOS_UINT8)i;
                stWriteUsimInfo.stUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE;
                stWriteUsimInfo.bCreateNode = VOS_TRUE;
                ulRet = MN_MSG_WriteSmsFile(enMemStore,VOS_NULL_PTR,&stWriteUsimInfo,aucSmContent);

            }
            else
            {
                ulRet = MN_MSG_WriteSmsFile(enMemStore,&i,VOS_NULL_PTR,aucSmContent);
            }
#endif
            ulDeleteCount++;
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ulDeleteCount))
            {
                break;
            }
            bDeleteFlag = VOS_FALSE;
        }
    }

    if (0 == ulDeleteCount)
    {
        *pbDeleteAll = VOS_TRUE;
        *pulDeleteCount = 0;
        return MN_ERR_NO_ERROR;
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*表明已经向APP上报删除结果*/
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteBegin = 0;
        return ulRet;
    }

    *pulDeleteCount = ulDeleteCount;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE, (VOS_UINT8)ulDeleteCount);

        /*判断是否已经删除完成*/
        if (i < ulSmCapacity)
        {
            /*未能全部删除,更新删除中相关信息,表明未能向APP上报删除结果*/
            *pbDeleteAll = VOS_FALSE;
        }

        /*表明未能向APP上报删除结果*/
        f_stMsgSetUsimRec.ucDeleteBegin = (VOS_UINT8)(i + 1);
        f_stMsgSetUsimRec.bDeleteReportFlag = VOS_FALSE;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  MN_MSG_DeleteMultiStaRpt(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            *pbDeleteAll,
    VOS_UINT8                           *pucDeleteCount
)
{
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulSmsrCapacity;
    VOS_UINT32                          i;
    VOS_UINT8                           ucDeleteCount = 0;
    VOS_UINT8                           ucBeginIndex = f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    MN_MSG_USIM_INFO_STRU               stSmaUsimInfo;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    ulSmsrCapacity = MN_MSG_GetSmsrCapacity(enMemStore);
    PS_MEM_SET(aucSmsrContent,0X00,MN_MSG_EFSMSR_LEN);

    for (i = ucBeginIndex; i < ulSmsrCapacity; i++)
    {
        ulRet = MN_MSG_ReadSmsrInfo(enMemStore, i, aucSmsrContent);
        if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
        {
            aucSmsrContent[0] = EF_SMS_STATUS_REPORT_EMPTY;
            PS_MEM_SET(&stSmaUsimInfo,0X00,sizeof(stSmaUsimInfo));
            stSmaUsimInfo.clientId = clientId;
            stSmaUsimInfo.opId = opId;
            stSmaUsimInfo.usEfId = (VOS_UINT16)ulFileId;
            stSmaUsimInfo.enDeleteType = MN_MSG_DELETE_ALL;
            stSmaUsimInfo.ucRecIndex = (VOS_UINT8)i;
            stSmaUsimInfo.enSmaUsimAction = MN_MSG_USIM_DELETE_STARPT;
            ulRet = MN_MSG_WriteSmsrFile(enMemStore,&stSmaUsimInfo,aucSmsrContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                break;
            }
            ucDeleteCount++;
            if ((MN_MSG_MEM_STORE_SIM == enMemStore)
             && (MN_MSG_MAX_DELETE_REC_NUM == ucDeleteCount))
            {
                break;
            }
        }
    }
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_DELETE_STARPT, ucDeleteCount);
    }
    *pucDeleteCount = ucDeleteCount;
    if (MN_ERR_NO_ERROR != ulRet)
    {
        /*表明已经向APP上报删除结果*/
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
        return ulRet;
    }
    /*判断是否已经删除完成*/
    if (i >= ulSmsrCapacity)
    {
        *pbDeleteAll = VOS_TRUE;
        if ((MN_MSG_MEM_STORE_SIM == enMemStore)
         && (ucDeleteCount > 0))
        {
            /*表明未能向APP上报删除结果*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = (VOS_UINT8)(i + 1);
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
        }
        else
        {
            /*表明已经向APP上报删除结果*/
            f_stMsgSetUsimRec.ucDeleteStaRptBegin = 0;
            f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_TRUE;
        }
    }
    else
    {
        /*未能全部删除,更新删除中相关信息,表明未能向APP上报删除结果*/
        *pbDeleteAll = VOS_FALSE;
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = VOS_FALSE;
    }
    return MN_ERR_NO_ERROR;
}


VOS_VOID  MN_MSG_UpdateSmsInfo(
    VOS_BOOL                            bEfSmsState,
    VOS_UINT8                           ucEFSmNum
)
{
    f_stMsgEfSmsInfo.bEfSmsState = bEfSmsState;
    f_stMsgEfSmsInfo.ucSmsRealRecNum = ucEFSmNum;
}


VOS_VOID  MN_MSG_UpdateUsimStateInfo(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState
)
{
    f_stMsgUsimStatusInfo.enPowerState = enPowerState;
}



VOS_UINT32 MN_MSG_StartMo(
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penSendDomain
)
{
    VOS_UINT32                          ulStoreIndex;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain;
    MN_MSG_STORE_MSG_STRU               stStoreMsg;
    VOS_UINT32                          ulRet;
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain;
    MN_MSG_SENDMSG_EVT_INFO_STRU        stSendMsgEvt;

    PS_MEM_SET(&stSendMsgEvt,0X00,sizeof(stSendMsgEvt));
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*1.获取最早缓存的消息*/
    PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
    ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);


    /*1.1若缓存消息类型为SMMA消息，则判断当前是否需要发送*/
    if ((MN_MSG_NO_AVAILABLE_SMS_REC != ulStoreIndex)
     && (MN_MSG_MO_TYPE_SMMA == stStoreMsg.stMoInfo.enSmsMoType))
    {

        /*获取当前UE的存储状态*/
        ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
        if (VOS_ERR == ulRet)
        {
            MN_WARN_LOG("MN_MSG_StartMo: Fail to read SMSS information.");
            return ulRet;
        }
        MN_NORM_LOG1("MN_MSG_StartMo: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

        /*若当前UE的存储状态为存储设备空闲，直接返回*/
        if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
        {
            MN_MSG_FreeStoreMsg(ulStoreIndex);
            PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
            ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
        }
        else
        {
            /*若当前UE存储设备状态不能接收短信，直接返回*/
            ulRet = MN_MSG_CheckMemAvailable();
            if (VOS_OK != ulRet)
            {
                MN_MSG_FreeStoreMsg(ulStoreIndex);
                PS_MEM_SET(&stStoreMsg,0X00,sizeof(stStoreMsg));
                ulStoreIndex = MN_MSG_GetStoreMsg(&stStoreMsg);
            }
        }
    }

    if ((MN_MSG_NO_AVAILABLE_SMS_REC == ulStoreIndex)
     || (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP == stStoreMsg.stMoInfo.enSmaMoState)
     || (MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP == stStoreMsg.stMoInfo.enSmaMoState))
    {

        MN_NORM_LOG("MN_MSG_StartMo: no buffer to send.");
        return VOS_ERR;
    }

    /*2. 判断当前是否存在可用发送域*/
    MN_MSG_GetCurSendDomain(stStoreMsg.stMoInfo.enHopeSendDomain,&enSendDomain);
    *penSendDomain = enSendDomain;
    if (MN_MSG_SEND_DOMAIN_NO == enSendDomain)
    {
        MN_WARN_LOG("MN_MSG_StartMo:No Avail Send Domain");
        return VOS_ERR;
    }

    /*3.创建发送短信时相关参数*/
    /* 更新当前实际发送域 */
    enHopeSendDomain = stStoreMsg.stMoInfo.enHopeSendDomain;
    stStoreMsg.stMoInfo.enHopeSendDomain = MN_MSG_GetRealPrefSendDomain(enSendDomain,enHopeSendDomain);
    MN_MSG_CreateMoInfo(&stStoreMsg.stMoInfo);
    MN_MSG_SendMsgToSms(&stStoreMsg.stMoInfo);
    MN_MSG_FreeStoreMsg(ulStoreIndex);

    /*此处解决STK覆盖SMMA消息问题；*/
    if (MN_MSG_MO_TYPE_BUFFER_STK == stStoreMsg.stMoInfo.enSmsMoType)
    {
        MN_MSG_StartMemNotification();
    }

    return VOS_OK;
}



VOS_VOID MN_MSG_StartMemNotification(VOS_VOID)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;

    MN_INFO_LOG("MN_MSG_StartMemNotification: into function.");
    PS_MEM_SET(&stSmssInfo,0X00,sizeof(stSmssInfo));

    /*获取当前UE的存储状态*/
    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_ERR == ulRet)
    {
        MN_WARN_LOG("MN_MSG_StartMemNotification: Fail to read SMSS information.");
        return;
    }
    MN_NORM_LOG1("MN_MSG_StartMemNotification: enMemCapExcNotFlag is ", stSmssInfo.enMemCapExcNotFlag);

    /*若当前UE的存储状态为存储设备空闲，直接返回*/
    if (MN_MSG_MEM_FULL_SET != stSmssInfo.enMemCapExcNotFlag)
    {
        return;
    }

    ulRet = MN_MSG_CheckMemAvailable();
    if (VOS_OK == ulRet)
    {
        MN_MSG_SendMemAvail();
    }

}



VOS_UINT32  MN_MSG_SendSmma(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_BOOL                            bReportFlag,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;
    VOS_UINT32                          ulRet = MN_ERR_NO_ERROR;
    MN_MSG_MO_ENTITY_STRU               stMoEntity;

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    if (MN_MSG_SEND_DOMAIN_NO == enRealDomain)
    {       
        MN_WARN_LOG("MN_MSG_SendSmma: enRealDomain IS MN_MSG_SEND_DOMAIN_NO.");
        
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

    if ( (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
      && (MN_MSG_SEND_DOMAIN_PS == enRealDomain) )
    {
        ulRet = MN_ERR_CLASS_SMS_NOAVAILDOMAIN;
        return ulRet;
    }

    ulRet = MN_MSG_SendSmsSmmaReq(enRealDomain, enMsgSignallingType);
    if (VOS_ERR == ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_INTERNAL;
        return ulRet;
    }

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    stMoEntity.clientId = clientId;
    stMoEntity.opId = opId;
    stMoEntity.enSendDomain= enRealDomain;
    stMoEntity.enSaveArea = MN_MSG_MEM_STORE_NONE;
    stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
    stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
    stMoEntity.bReportFlag = bReportFlag;
    stMoEntity.ucRpDataLen = 0;
    stMoEntity.enSmaMoState = MN_MSG_MO_STATE_WAIT_REPORT_IND;
    stMoEntity.enMsgSignallingType = enMsgSignallingType;
    MN_MSG_CreateMoInfo(&stMoEntity);
    return ulRet;
}


VOS_VOID MN_MSG_SendMemAvail(VOS_VOID)
{
    MN_MSG_MO_STATE_ENUM_U8             enMoState;
    VOS_UINT32                          ulSaveIndex;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealDomain;

    PS_MEM_SET(&stMoEntity, 0x00, sizeof(stMoEntity));

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS_PREFERRED,&enRealDomain);
    enMoState = MN_MSG_GetMoState();
    if ((MN_MSG_SEND_DOMAIN_NO == enRealDomain)
     || (MN_MSG_MO_STATE_WAIT_REPORT_IND == enMoState))
    {

        ulSaveIndex = MN_MSG_GetStoreMsgIndex();

        if (MN_MSG_NO_AVAILABLE_SMS_REC == ulSaveIndex)
        {

            MN_WARN_LOG("MN_MSG_SendMemAvail,Type:From Mem, No Enough Buffer");
            return;
        }
        /*将构造好的消息存入缓存*/
        stMoEntity.bReportFlag = VOS_FALSE;
        stMoEntity.enSendDomain = MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        stMoEntity.enSaveArea = MN_MSG_MEM_STORE_MAX;
        stMoEntity.enSmsMoType = MN_MSG_MO_TYPE_SMMA;
        stMoEntity.enTpduType = MN_MSG_TPDU_SUBMIT;
        stMoEntity.ucRpDataLen = 0;
        PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
        MN_MSG_SaveStoreMsg(ulSaveIndex,&stMoEntity,aucSmContent);
    }
    else
    {
        /* Here send SMMA request to SPM module */
#if (FEATURE_IMS == FEATURE_ON)
        /* 如果IMS宏打开需要到SPM模块做域选择，否则直接走NAS信令 */
        TAF_MSG_SendSpmSmmaInd();
#else
        (VOS_VOID)MN_MSG_SendSmma(stMoEntity.clientId, stMoEntity.opId, VOS_FALSE, TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING);
#endif
    }
}


VOS_BOOL MN_MSG_IsUsimFileExist(
    VOS_UINT16                          usEfId
)
{
    switch (usEfId)
    {
        case USIMM_USIM_EFSMS_ID:
        case USIMM_TELE_EFSMS_ID:
            if (VOS_TRUE == f_stMsgEfSmsInfo.bEfSmsState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSP_ID:
        case USIMM_TELE_EFSMSP_ID:
            if (VOS_TRUE == f_stMsgEfSmspInfo.bEfSmspState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSS_ID:
        case USIMM_TELE_EFSMSS_ID:
            if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
            {
                return VOS_TRUE;
            }
            break;
        case USIMM_USIM_EFSMSR_ID:
        case USIMM_TELE_EFSMSR_ID:
            if (VOS_TRUE == f_stMsgEfSmsrInfo.bEfSmsrState)
            {
                return VOS_TRUE;
            }
            break;
        default:
            MN_INFO_LOG("MN_MSG_IsUsimFileExist:No EF File ID");
            break;
    }

    return VOS_FALSE;
}


VOS_VOID   MN_MSG_ReadUstInfo(
    MN_MSG_USIM_EFUST_INFO_STRU         *pstEfUstInfo
)
{
    PS_MEM_CPY(pstEfUstInfo,&f_stEfUstInfo,sizeof(MN_MSG_USIM_EFUST_INFO_STRU));
    MN_MSG_PrintEfUstInfo();
}


VOS_UINT32 MN_MSG_ReadSmsInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmContent
)
{
#if ((NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)&& (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON))
    VOS_UINT32                          ulRet;
#endif
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsInfo: USIMM_USIM_EFSMS_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[ulIndex*MN_MSG_EFSMS_LEN] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmContent, (f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex*MN_MSG_EFSMS_LEN)), MN_MSG_EFSMS_LEN);
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[ulIndex] & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

#if (NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)
        ulRet = MN_MSG_ReadMsgInFlashByIndex(ulIndex,pucSmContent);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_ReadSmsInfo:Write FLASH Error");
            PS_MEM_SET(f_aucMsgNvimSmStatus, 0x00, sizeof(f_aucMsgNvimSmStatus));
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_READ, ulRet);
            return ulRet;
        }
#else
        if(NV_OK != NV_Read(en_NV_Item_SMS_Content,pucSmContent, MN_MSG_EFSMS_LEN))
        {
           MN_ERR_LOG("MN_MSG_ReadSmsInfo:Read NVIM Sms Error");
           return MN_ERR_CLASS_SMS_NVIM;
        }
#endif

    }
#endif
    else
    {
       MN_NORM_LOG("MN_MSG_ReadSmsInfo: Memory type is not support.");
       return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;
}


VOS_VOID  MN_MSG_UpdateEachMemSmInfo(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_BCD_ADDR_STRU                stScAddr;
    MN_MSG_RAW_TS_DATA_STRU             stRawData;
    VOS_UINT8                           ucEfSmsStatus;

    PS_MEM_SET(&stRawData, 0x00, sizeof(stRawData));

    if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }

    PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)),
               pucEFContent,
               ucEFSmsLen);

    ulRet = MN_MSG_ParseEFSmContent(pucEFContent, &stScAddr, &stRawData, &ucEfSmsStatus);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        *(f_stMsgEfSmsInfo.aucEfSmsList + (ulIndex * ucEFSmsLen)) = EF_SMS_STATUS_FREE_SPACE;
    }

    return;
}


VOS_UINT32 MN_MSG_ReadSmsrInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucSmsrContent
)
{
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSR_ID;
    }

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmsrInfo: USIMM_USIM_EFSMSR_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (EF_SMS_STATUS_REPORT_EMPTY == (f_stMsgEfSmsrInfo.aucEfSmsrList[ulIndex*MN_MSG_EFSMSR_LEN]))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        PS_MEM_CPY(pucSmsrContent, (f_stMsgEfSmsrInfo.aucEfSmsrList+ (ulIndex*MN_MSG_EFSMSR_LEN)), MN_MSG_EFSMSR_LEN);
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (ulIndex >= MN_MSG_MAX_NVIM_SMSR_REC_NUM)
            {
                return MN_ERR_CLASS_SMS_INVALID_REC;
            }
            if(NV_OK != NV_Read(en_NV_Item_SMS_Status,pucSmsrContent, ulLen))
            {
               MN_ERR_LOG("MN_MSG_ReadSmsrInfo:Read NVIM Smsr Error");
               return MN_ERR_CLASS_SMS_NVIM;
            }

            if (EF_SMS_STATUS_REPORT_EMPTY == *pucSmsrContent)
            {
                return MN_ERR_CLASS_SMS_EMPTY_REC;
            }
        }

        return MN_ERR_NO_ERROR;

    }
    else
    {
        MN_NORM_LOG("MN_MSG_ReadSmsrInfo: Memory type is not support.");
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;

}


VOS_VOID  MN_MSG_UpdateEachMemSmsrInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucEFContent,
    VOS_UINT8                           ucEFSmsrLen
)
{
    if (ucIndex >= f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
    {
        return;
    }
    PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (ucIndex * ucEFSmsrLen)),
               pucEFContent,
               ucEFSmsrLen);
    return;
}


VOS_VOID  MN_MSG_UpdateTotalSmsrInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucSmsrRec,
    VOS_UINT16                          usEfLen,
    VOS_UINT8                           *pucSmspContent
)
{
    VOS_UINT32                          i;

    f_stMsgEfSmsrInfo.bEfSmsrState = bEfSmspState;
    f_stMsgEfSmsrInfo.ucSmsrRealRecNum = ucSmsrRec;
    for (i = 0; i < ucSmsrRec; i++)
    {
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (MN_MSG_EFSMSR_LEN * i)),
                   (pucSmspContent + (usEfLen * i)),
                   MN_MSG_EFSMSR_LEN);
    }
}


VOS_VOID MN_MSG_UpdateEachMemSmspInfo(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bUsed,
    const MN_MSG_SRV_PARAM_STRU         *pstScvParm
)
{

    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return;
    }
    f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed = bUsed;
    PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].stParm,
               pstScvParm,
               sizeof(MN_MSG_SRV_PARAM_STRU));

    return;
}


VOS_UINT32 MN_MSG_ReadSmspInfo(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    VOS_BOOL                            bSrvParmPresent = VOS_FALSE;
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;
    VOS_UINT32                          ulFileId;

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }

    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        ulRet = MN_MSG_CheckUsimStatus();
        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_WARN_LOG1("MN_MSG_ReadSmspInfo: ErrCode ", (VOS_INT32)ulRet);
            if (MN_ERR_CLASS_SMS_UPDATE_USIM != ulRet)
            {
                return ulRet;
            }

            MN_MSG_GetUsimPowerState(&enPowerState);
            if (enPowerState <= MN_MSG_USIM_POWER_WAIT_EFSMSP)
            {
                return MN_ERR_CLASS_SMS_UPDATE_USIM;
            }
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_ReadSmspInfo: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (ulIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        if (VOS_TRUE != f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].bUsed)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[ulIndex].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));
    }
    else
    {
        if (NV_OK != NV_Read(en_NV_Item_SMS_EFSMSP_Para, &stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            MN_ERR_LOG("MN_MSG_ReadSmspInfo:Read NVIM Smsp Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);

        PS_MEM_CPY(pstSrvParam,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        MSG_ParseSmsp(MN_MSG_MAX_EF_LEN,aucSmspContent,&bSrvParmPresent,pstSrvParam);
        if (VOS_FALSE == bSrvParmPresent)
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
    }
    return MN_ERR_NO_ERROR;
}


VOS_VOID  MN_MSG_UpdateTotalSmspInfo(
    VOS_BOOL                            bEfSmspState,
    VOS_UINT8                           ucNumofSmsp,
    VOS_UINT8                           ucEfLen,
    const VOS_UINT8                     *pucSmspContent
)
{
    VOS_UINT32                          i;
    MN_MSG_SRV_PARAM_STRU                stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;

    PS_MEM_SET(&stSrvParm, 0, sizeof(MN_MSG_SRV_PARAM_STRU));

    MN_INFO_LOG("MN_MSG_UpdateTotalSmspInfo: step into function.");
    f_stMsgEfSmspInfo.bEfSmspState = bEfSmspState;
    MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: ucNumofSmsp", ucNumofSmsp);
    if (ucNumofSmsp < MN_MSG_MAX_USIM_EFSMSP_NUM)
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = ucNumofSmsp;
    }
    else
    {
        f_stMsgEfSmspInfo.ucSmspRealRecNum = MN_MSG_MAX_USIM_EFSMSP_NUM;
    }

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                   sizeof(stSrvParm));

        MSG_ParseSmsp(ucEfLen,
                      (pucSmspContent +  (i * ucEfLen)),
                      &bValid,
                      &stSrvParm);
        MN_NORM_LOG1("MN_MSG_UpdateTotalSmspInfo: bValid", (VOS_INT32)bValid);
        if (VOS_TRUE == bValid)
        {
            f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed = VOS_TRUE;
            PS_MEM_CPY(&f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                       &stSrvParm,
                       sizeof(MN_MSG_SRV_PARAM_STRU));
        }
    }
}


VOS_VOID MN_MSG_GetSmStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    VOS_UINT32                          *pulEachStatusRec
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucStatus;

    *pulTotalRec            = 0;
    *pulUsedRec             = 0;
    *pulEachStatusRec       = 0;
    *(pulEachStatusRec + 1) = 0;
    *(pulEachStatusRec + 2) = 0;
    *(pulEachStatusRec + 3) = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++)
        {
            ucStatus = *(f_stMsgEfSmsInfo.aucEfSmsList + (i * MN_MSG_EFSMS_LEN));
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*pulEachStatusRec)++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        *pulTotalRec = f_usMsgNvimSmsCurReNum;
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            ucStatus = f_aucMsgNvimSmStatus[i];
            if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & EF_SMS_STATUS_MO_TO_BE_SEND))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec))++;
            }
            else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & EF_SMS_STATUS_MO_SEND_TO_NT))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 1))++;
            }
            else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & EF_SMS_STATUS_MT_TO_BE_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 2))++;
            }
            else if (EF_SMS_STATUS_MT_READ == (ucStatus & EF_SMS_STATUS_MT_READ))
            {
                (*pulUsedRec)++;
                (*(pulEachStatusRec + 3))++;
            }
            else
            {
            }
        }
    }
#endif
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmStorageList: Memory type is not support.");
    }
}


VOS_VOID MN_MSG_GetSmsrStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen = MN_MSG_EFSMSR_LEN;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();


    *pulUsedRec = 0;
    *pulTotalRec = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY != f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                (*pulUsedRec)++;
            }
        }
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            *pulTotalRec = MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
            {
                PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
                if (NV_OK == NV_Read(en_NV_Item_SMS_Status, aucSmsrContent, ulLen))
                {
                    MN_ERR_LOG("MN_MSG_GetSmsrStorageList:Read NVIM Smsr Error");
                    if (EF_SMS_STATUS_REPORT_EMPTY != aucSmsrContent[0])
                    {
                        (*pulUsedRec)++;
                    }
                }
            }
        }
    }
    else
    {
       MN_WARN_LOG("MN_MSG_GetSmsrStorageList: Memory type is not support.");
    }

}


VOS_VOID MN_MSG_GetSmspStorageList(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          *pulTotalRec,
    VOS_UINT32                          *pulUsedRec,
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    MN_MSG_SRV_PARAM_STRU               stSrvParm;
    VOS_BOOL                            bValid = VOS_FALSE;
    MN_MSG_SRV_PARAM_STRU               *pTmpSrvParm;
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stEfsmsp;

    PS_MEM_SET(&stEfsmsp,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0XFF,MN_MSG_MAX_EF_LEN);
    *pulUsedRec = 0;
    pstSrvParam->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        *pulTotalRec = f_stMsgEfSmspInfo.ucSmspRealRecNum;
        pTmpSrvParm = pstSrvParam;
        for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
        {
            if (VOS_TRUE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pTmpSrvParm,
                           &f_stMsgEfSmspInfo.astEachEfSmspInfo[i].stParm,
                           sizeof(MN_MSG_SRV_PARAM_STRU));
            }
            else
            {
                pTmpSrvParm->ucParmInd = MN_MSG_SRV_PARM_TOTALABSENT;
            }
            pTmpSrvParm++;
        }
    }
    else
    {
        PS_MEM_CPY(&stSrvParm,
                   &f_stMsgEfSmspInfo.astEachEfSmspInfo[0].stParm,
                   sizeof(MN_MSG_SRV_PARAM_STRU));

        *pulTotalRec  = 1;
        if (NV_OK == NV_Read(en_NV_Item_SMS_EFSMSP_Para,&stEfsmsp, MN_MSG_EFSMSP_PARA_LEN))
        {
            PS_MEM_CPY(aucSmspContent, &stEfsmsp, MN_MSG_MAX_EF_LEN);
            /*存在NVIM中无Alpha Identifier,第一个字节表示Parameter Indicators*/
            MSG_ParseSmsp(MN_MSG_MIN_SRV_PARM_LEN,aucSmspContent,&bValid,&stSrvParm);
            if (VOS_TRUE == bValid)
            {
                (*pulUsedRec)++;
                PS_MEM_CPY(pstSrvParam,&stSrvParm,sizeof(stSrvParm));
            }
        }
        else
        {
            MN_ERR_LOG("MN_MSG_GetSmspStorageList:Read NVIM Smsp Error");
        }
    }
}


VOS_UINT32 MN_MSG_GetStatus(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex,
    VOS_UINT8                           *pucStatus
)
{
    VOS_UINT32                          ulPos;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        ulPos = MN_MSG_EFSMS_LEN * ulIndex;
        *pucStatus = f_stMsgEfSmsInfo.aucEfSmsList[ulPos];

        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }
        else
        {
            return MN_ERR_NO_ERROR;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex >= f_usMsgNvimSmsCurReNum)
        {
            return MN_ERR_CLASS_SMS_INVALID_REC;
        }

        *pucStatus = f_aucMsgNvimSmStatus[ulIndex];
        if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
        {
            return MN_ERR_CLASS_SMS_EMPTY_REC;
        }

        return MN_ERR_NO_ERROR;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetStatus: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}



VOS_UINT32 MN_MSG_GetAvailSmRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    MN_NORM_LOG("MN_MSG_GetAvailSmRecIndex: Step into function.");
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsInfo.ucSmsRealRecNum; i++ )
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: USIM ", (VOS_INT32)i, (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_stMsgEfSmsInfo.aucEfSmsList[i*MN_MSG_EFSMS_LEN] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        for (i = 0; i < f_usMsgNvimSmsCurReNum; i++)
        {
            MN_INFO_LOG2("MN_MSG_GetAvailSmRecIndex: NVIM ", (VOS_INT32)i, (f_aucMsgNvimSmStatus[i] & 0x01));
            if (EF_SMS_STATUS_FREE_SPACE == (f_aucMsgNvimSmStatus[i] & 0x01))
            {
                ulIndex = i;
                break;
            }
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;
}


VOS_UINT32 MN_MSG_GetAvailSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    VOS_UINT8                           aucSmsrContent[MN_MSG_EFSMSR_LEN];
    VOS_UINT32                          ulLen;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        for (i = 0; i < f_stMsgEfSmsrInfo.ucSmsrRealRecNum; i++)
        {
            if (EF_SMS_STATUS_REPORT_EMPTY == f_stMsgEfSmsrInfo.aucEfSmsrList[i*MN_MSG_EFSMSR_LEN])
            {
                ulIndex = i;
                break;
            }
        }
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
       if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
       {
           PS_MEM_SET(aucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
           ulLen = MN_MSG_EFSMSR_LEN;
           for (i = 0; i < MN_MSG_MAX_NVIM_SMSR_REC_NUM; i++)
           {
               if(NV_OK == NV_Read(en_NV_Item_SMS_Status,aucSmsrContent, ulLen))
               {
                   if (EF_SMS_STATUS_REPORT_EMPTY == aucSmsrContent[0])
                   {
                       ulIndex = i;
                       break;
                   }
               }
               else
               {
                   MN_ERR_LOG("MN_MSG_GetAvailSmsrRecIndex:Read NVIM Smsr Error");
               }
           }
       }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetAvailSmsrRecIndex: enMemStore is ", enMemStore);
    }
    return ulIndex;

}


VOS_UINT8 MN_MSG_GetAvailSmspRecIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex = MN_MSG_NO_AVAILABLE_REC;

    for (i = 0; i < f_stMsgEfSmspInfo.ucSmspRealRecNum; i++)
    {
        if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[i].bUsed)
        {
            ucIndex = i;
            break;
        }
    }
    return  ucIndex;
}


VOS_UINT32 MN_MSG_GetReplaceSmsrRecIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{

    VOS_UINT32                          ulSaveIndex;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    ulSaveIndex = MN_MSG_NO_AVAILABLE_SMS_REC;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (0 == f_stMsgEfSmsrInfo.ucSmsrRealRecNum)
        {
            return MN_MSG_NO_AVAILABLE_SMS_REC;
        }

        f_stMsgEfSmsrInfo.ucSmsrCurRecNum = (f_stMsgEfSmsrInfo.ucSmsrCurRecNum + 1) %
                                        (f_stMsgEfSmsrInfo.ucSmsrRealRecNum);
        ulSaveIndex = f_stMsgEfSmsrInfo.ucSmsrCurRecNum;
    }

    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            f_ucMsgNvimSmsrCurReNum = (f_ucMsgNvimSmsrCurReNum + 1) % MN_MSG_MAX_NVIM_SMSR_REC_NUM;
            ulSaveIndex = f_ucMsgNvimSmsrCurReNum;
        }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetReplaceSmsrRecIndex: enMemStore is ", enMemStore);
    }

    return ulSaveIndex;

}


VOS_VOID  MN_MSG_GetUsimPowerState(
    MN_MSG_USIM_POWER_STATE_ENUM_U8     *penPowerState
)
{
    *penPowerState = f_stMsgUsimStatusInfo.enPowerState;
    MN_INFO_LOG1("MN_MSG_GetUsimPowerState: f_stMsgUsimStatusInfo.enPowerState", f_stMsgUsimStatusInfo.enPowerState);
}


VOS_UINT32 MN_MSG_CheckUsimStatus(VOS_VOID)
{
    VOS_UINT8                           ucCardStatus;


    ucCardStatus = USIMM_CARD_SERVIC_BUTT;

    /*当前的USIM卡不在位*/
    MN_NORM_LOG1("MN_MSG_CheckUsimStatus:Usim Status is ", f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MN_MSG_SIM_NOT_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
    {
        (VOS_VOID)MMA_GetUsimStatusFromUsim(&ucCardStatus, VOS_NULL_PTR);
        if (USIMM_CARD_SERVIC_SIM_PIN == ucCardStatus)/*USIMM_CARD_SERVIC_ENUM*/
        {
            return MN_ERR_CLASS_SMS_NEED_PIN1;
        }
        else if (USIMM_CARD_SERVIC_SIM_PUK == ucCardStatus)
        {
            return MN_ERR_CLASS_SMS_NEED_PUK1;
        }
        else if (USIMM_CARD_SERVIC_UNAVAILABLE == ucCardStatus)/*USIMM_CARD_SERVIC_UNAVAILABLE,  313(U)SIM failure*/
        {
            return MN_ERR_CLASS_SMS_UNAVAILABLE;
        }
        /*USIMM_CARD_SERVIC_NET_LCOK,手机中记录了特定的HOME PLMN，若插入SIM卡的HOME PLMN不是手机NV中指定的，则要求输入密码*/
        /*USIMM_CARD_SERVIC_IMSI_LCOK,手机中记录了特定卡的IMSI，非指定IMSI的SIM卡插入手机则要求输入密码*/
        /*上述两种错误原因值的处理目前还不明确，暂时做无卡处理*/
        else
        {
            return MN_ERR_CLASS_SMS_NOUSIM;
        }
    }

    MN_NORM_LOG1("MN_MSG_CheckUsimStatus: SMS power status:", (VOS_INT32)f_stMsgUsimStatusInfo.ucUsimStatus);
    /*USIM卡正在上电过程中*/
    if (MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
    {
        return MN_ERR_CLASS_SMS_UPDATE_USIM;
    }

    return MN_ERR_NO_ERROR;
}



VOS_UINT32 MN_MSG_GetSmCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsInfo.ucSmsRealRecNum;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return f_usMsgNvimSmsCurReNum;
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmCapacity: enMemStore is ", enMemStore);
        return 0;
    }
}


VOS_UINT32 MN_MSG_GetSmspCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmspInfo.ucSmspRealRecNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        return MN_MSG_NV_SMSP_VOLUME;
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmspCapacity: enMemStore is ", enMemStore);
        return MN_MSG_FILE_NONE_REC;
    }
}


VOS_UINT32 MN_MSG_GetSmsrCapacity(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();


    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        return f_stMsgEfSmsrInfo.ucSmsrRealRecNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            return MN_MSG_MAX_NVIM_SMSR_REC_NUM;
        }
        else
        {
            return 0;
        }

    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
        return 0;
    }

}


VOS_BOOL MN_MSG_IsValidSmIndex(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_UINT32                          ulIndex
)
{
    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (ulIndex < f_stMsgEfSmsInfo.ucSmsRealRecNum)
        {
            return VOS_TRUE;
        }
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (ulIndex < f_usMsgNvimSmsCurReNum)
        {
            return VOS_TRUE;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_GetSmsrCapacity: enMemStore is ", enMemStore);
    }
    return VOS_FALSE;
}


VOS_BOOL MN_MSG_IsValidSmspIndex(
    VOS_UINT8                           ucIndex
)
{
    if (ucIndex < f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


VOS_BOOL MN_MSG_IsEmptySmsp(
    VOS_UINT8                           ucIndex
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        return VOS_TRUE;
    }
    if (VOS_FALSE == f_stMsgEfSmspInfo.astEachEfSmspInfo[ucIndex].bUsed)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


VOS_VOID  MN_MSG_GetCurCfgParm(
    MN_MSG_CONFIG_PARM_STRU             *pstCfgParm
)
{
    PS_MEM_CPY(pstCfgParm,&f_stMsgCfgParm,sizeof(MN_MSG_CONFIG_PARM_STRU));
    MN_MSG_PrintConfigParmStru(&f_stMsgCfgParm);
}


VOS_VOID  MN_MSG_UpdateRegState(
    VOS_UINT8                           ucDomain,
    VOS_BOOL                            bAttachFlag
)
{
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register domain: ", ucDomain);
    MN_NORM_LOG1("MN_MSG_UpdateRegState: current register state: ", (VOS_INT32)bAttachFlag);
    if (MN_MSG_SEND_DOMAIN_PS == ucDomain)
    {
        f_bMsgPsRegFlag = bAttachFlag;
    }
    else
    {
        f_bMsgCsRegFlag = bAttachFlag;
    }
}


VOS_UINT32  MN_MSG_UpdateRcvMsgPath(
    const MN_MSG_SET_RCVMSG_PATH_PARM_STRU *pstRcvPath
)
{
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == pstRcvPath->enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == pstRcvPath->enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == pstRcvPath->enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == pstRcvPath->enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == f_stMsgCfgParm.enAppMemStatus))
        {
            f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
            f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
            f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
            f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
            f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


            /* 保存MT信息，在<MT>=3，收到CLASS3短信时候，按照+CMT方式上报 */
            f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

            MN_INFO_LOG("MN_MSG_UpdateRcvMsgPath():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = pstRcvPath->enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = pstRcvPath->enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = pstRcvPath->enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = pstRcvPath->enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = f_stMsgCfgParm.enAppMemStatus;

    if (NV_OK != NV_Write(en_NV_Item_SMS_SERVICE_Para,
                          (stSmsSrvParam.aucSmsServicePara),
                          MN_MSG_SRV_PARAM_LEN))
    {

        MN_ERR_LOG("MN_MSG_UpdateRcvMsgPath:Fail to write RcvMsgPath To NVIM!");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enRcvSmAct = pstRcvPath->enRcvSmAct;
    f_stMsgCfgParm.enSmMemStore = pstRcvPath->enSmMemStore;
    f_stMsgCfgParm.enStaRptMemStore = pstRcvPath->enStaRptMemStore;
    f_stMsgCfgParm.enRcvStaRptAct = pstRcvPath->enRcvStaRptAct;
    f_stMsgCfgParm.enSmsServVersion = pstRcvPath->enSmsServVersion;


    /* 保存MT信息，在<MT>=3，收到CLASS3短信时候，按照+CMT方式上报 */
    f_stMsgCfgParm.enMtType         = pstRcvPath->enCnmiMtType;

    return MN_ERR_NO_ERROR;
}


VOS_VOID  MN_MSG_GetCurRcvMsgPath(
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    *pstRcvPath
)
{
    PS_MEM_SET(pstRcvPath,0,sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU));
    pstRcvPath->enRcvSmAct = f_stMsgCfgParm.enRcvSmAct;
    pstRcvPath->enSmMemStore = f_stMsgCfgParm.enSmMemStore;
    pstRcvPath->enRcvStaRptAct = f_stMsgCfgParm.enRcvStaRptAct;
    pstRcvPath->enStaRptMemStore = f_stMsgCfgParm.enStaRptMemStore;
    pstRcvPath->enSmsServVersion = f_stMsgCfgParm.enSmsServVersion;

    pstRcvPath->enCnmiMtType     = f_stMsgCfgParm.enMtType;

}


LOCAL MN_MSG_SEND_DOMAIN_ENUM_U8 MSG_PreferedGetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    MN_MSG_SEND_DOMAIN_ENUM_U8          enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    MN_MSG_DOMAIN_AVAIL_FLAG_U8         enDomainAvail = MN_MSG_NO_DOMAIN_AVAIL;
    VOS_BOOL                            bCsDomainAvailable;

    ulPsAvailable = GMM_ServiceStatusForSms();
    if ((VOS_TRUE == f_bMsgPsRegFlag)
     && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
    {
        enDomainAvail |= MN_MSG_PS_DOMAIN_AVAIL;
    }

    MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
    if (VOS_TRUE == bCsDomainAvailable)
    {
        enDomainAvail |= MN_MSG_CS_DOMAIN_AVAIL;
    }

    if (MN_MSG_CS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前仅CS域可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
    }
    else if (MN_MSG_PS_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前仅PS域可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
    }
    else if (MN_MSG_NO_DOMAIN_AVAIL == enDomainAvail)
    {
        /* 当前CSPS域都不可用 */
        enRealSendDomain = MN_MSG_SEND_DOMAIN_NO;
    }
    else
    {
        /* 当前CSPS域都可用 */
        if ( (MN_MSG_SEND_FAIL_CSPS_DOMAIN == f_enMsgSendFailFlag)
          || (MN_MSG_SEND_FAIL_PS_DOMAIN == f_enMsgSendFailFlag))
        {
            /*CSPS域都发送失败,仍然通过CS域继续发送*/
            /*PS域发送失败,通过CS域继续发送*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
        else if(MN_MSG_SEND_FAIL_CS_DOMAIN == f_enMsgSendFailFlag)
        {
            /*CS域发送失败,通过PS域继续发送*/
            enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
        else
        {
            /* CSPS域都没有发送失败,根据当前设置进行发送 */
            if(MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
            }
            else
            {
                enRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
            }
        }
    }

    return enRealSendDomain;
}


VOS_VOID   MN_MSG_GetCurSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          *penRealSendDomain
)
{
    VOS_UINT32                          ulPsAvailable;
    VOS_UINT32                          bCsDomainAvailable;

    *penRealSendDomain = MN_MSG_SEND_DOMAIN_NO ;

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
    {
        /* 快速指定搜网过程用户发短信，L不缓存，回复error ind后续靠短信重发机制再次触发发短信 ，
           此处无需判断f_bMsgPsRegFlag为VOS_TRUE */
        *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        return;
     }
#endif

    ulPsAvailable = GMM_ServiceStatusForSms();
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :f_bMsgPsRegFlag is ", (VOS_INT32)f_bMsgPsRegFlag);
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :ulPsAvailable is ", (VOS_INT32)ulPsAvailable);
    if (MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
    {
        if ((VOS_TRUE == f_bMsgPsRegFlag)
         && (GMM_SMS_SERVICE_AVAILABLE == ulPsAvailable))
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_PS;
        }
    }
    else if (MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
    {
        MN_MSG_CsDomainAvailable(&bCsDomainAvailable);
        if (VOS_TRUE == bCsDomainAvailable)
        {
            *penRealSendDomain = MN_MSG_SEND_DOMAIN_CS;
        }
    }
    else if ( (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain)
           || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain))
    {
        *penRealSendDomain = MSG_PreferedGetCurSendDomain(enHopeSendDomain);
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_GetCurSendDomain hoped domain: ", enHopeSendDomain);
    }
    MN_INFO_LOG1("MN_MSG_GetCurSendDomain :send domain is ", (VOS_INT32)*penRealSendDomain);
}


VOS_VOID  MN_MSG_GetCurAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             *penMemStatus
)
{
    *penMemStatus = f_stMsgCfgParm.enAppMemStatus;
    MN_INFO_LOG1("MN_MSG_GetCurAppMemStatus: f_stMsgCfgParm.enAppMemStatus is ", f_stMsgCfgParm.enAppMemStatus);
}


VOS_UINT32  MN_MSG_UpdateAppMemStatus(
    MN_MSG_MEM_FLAG_ENUM_U8             enMemStatus
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;


    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));

    if (NV_OK == NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN))
    {
        if ( ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] == f_stMsgCfgParm.enRcvSmAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enSmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] == f_stMsgCfgParm.enRcvStaRptAct)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] == f_stMsgCfgParm.enStaRptMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] == f_stMsgCfgParm.enCbmMemStore)
            && ((stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] == enMemStatus))
        {
            f_stMsgCfgParm.enAppMemStatus = enMemStatus;
            MN_INFO_LOG("MN_MSG_UpdateAppMemStatus():The content to write is same as NV's");
            return MN_ERR_NO_ERROR;
        }
    }
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_ACT_OFFSET] = f_stMsgCfgParm.enRcvSmAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enSmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_ACT_OFFSET] = f_stMsgCfgParm.enRcvStaRptAct;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_STARPT_MEM_STORE_OFFSET] = f_stMsgCfgParm.enStaRptMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_CBM_MEM_STORE_OFFSET] = f_stMsgCfgParm.enCbmMemStore;
    (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET] = enMemStatus;

    ulRet = NV_Write(en_NV_Item_SMS_SERVICE_Para,
                     &stSmsSrvParam,
                     MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_UpdateAppMemStatus:Write NV Failed");
        return MN_ERR_CLASS_SMS_NVIM;
    }

    f_stMsgCfgParm.enAppMemStatus = enMemStatus;

    return MN_ERR_NO_ERROR;
}



VOS_UINT32  MN_MSG_FindNodeByUsimResult(
    VOS_UINT8                           ucRecIndex,
    VOS_UINT16                          usEfId,
    MN_MSG_USIM_INFO_STRU               *pstSmaUsimInfo,
    VOS_UINT32                          *pulIndex
)
{
    VOS_UINT32                          i;
    for (i = 0; i < MN_MSG_MAX_ACTION_NODE_NUM; i++)
    {
        if (VOS_TRUE == f_astMsgSetUsimInfo[i].bUsed)
        {
            if ((ucRecIndex == f_astMsgSetUsimInfo[i].stUsimInfo.ucRecIndex)
             && (usEfId == f_astMsgSetUsimInfo[i].stUsimInfo.usEfId))
            {
                PS_MEM_CPY(pstSmaUsimInfo,&f_astMsgSetUsimInfo[i].stUsimInfo,sizeof(MN_MSG_USIM_INFO_STRU));
                *pulIndex = i;
                return VOS_OK;
            }
        }
    }
    return VOS_ERR;
}


VOS_UINT8  MN_MSG_GetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        return f_stMsgSetUsimRec.ucList;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        return f_stMsgSetUsimRec.ucDelete;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteBegin;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRpt;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        return f_stMsgSetUsimRec.ucDeleteStaRptBegin;
    }
    else
    {
        return f_stMsgSetUsimRec.ucDeleteEfSmsp;
    }
}


VOS_BOOL  MN_MSG_GetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        return f_stMsgSetUsimRec.bDeleteReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        return f_stMsgSetUsimRec.bDeleteStaRptReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        return f_stMsgSetUsimRec.bDeleteEfSmspReportFlag;
    }
    else
    {
        return VOS_TRUE;
    }
}


VOS_VOID  MN_MSG_SetDeleteReportFlag(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_BOOL                            bReportFlag
)
{
    if (MN_MSG_SET_USIM_DELETE == enType )
    {
        f_stMsgSetUsimRec.bDeleteReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.bDeleteStaRptReportFlag = bReportFlag;
    }
    else if (MN_MSG_SET_USIM_DELETE_EFSMSP == enType)
    {
        f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = bReportFlag;
    }
    else
    {
        return ;
    }
}


VOS_VOID  MN_MSG_SetUsimRec(
    MN_MSG_SET_USIM_ENUM_U8                enType,
    VOS_UINT8                           ucRec
)
{
    if (MN_MSG_SET_USIM_LIST == enType)
    {
        f_stMsgSetUsimRec.ucList = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE == enType)
    {
        f_stMsgSetUsimRec.ucDelete = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteBegin = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRpt = ucRec;
    }
    else if (MN_MSG_SET_USIM_DELETE_STARPT_BEGIN == enType)
    {
        f_stMsgSetUsimRec.ucDeleteStaRptBegin = ucRec;
    }
    else
    {
        f_stMsgSetUsimRec.ucDeleteEfSmsp = ucRec;
    }
}


VOS_UINT32  MN_MSG_MoSmsControlEnvelopeReq(
    VOS_UINT16                          usClientId,
    MN_MSG_BCD_ADDR_STRU               *pstRpDestAddr,
    MN_MSG_BCD_ADDR_STRU               *pstTpDestAddr
)
{
    VOS_UINT8                           aucLI[MN_MO_CTRL_LAI_LEN];
    SI_STK_ENVELOPE_STRU                stENStru;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stENStru, 0, sizeof(SI_STK_ENVELOPE_STRU));

    stENStru.enEnvelopeType     = SI_STK_ENVELOPE_SMSCRTL;
    stENStru.DeviceId.ucSDId    = SI_STK_DEV_TERMINAL;
    stENStru.DeviceId.ucDDId    = SI_STK_DEV_UICC;

    stENStru.uEnvelope.MOSMSCtrl.OP_Addr1 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Addr2 = 1;
    stENStru.uEnvelope.MOSMSCtrl.OP_Local = 1;

    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucNumType    = pstRpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.ucLen        = pstRpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr1.pucAddr      = pstRpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucNumType    = pstTpDestAddr->addrType;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.ucLen        = pstTpDestAddr->ucBcdLen;
    stENStru.uEnvelope.MOSMSCtrl.Addr2.pucAddr      = pstTpDestAddr->aucBcdNum;

    stENStru.uEnvelope.MOSMSCtrl.LocInfo.pucATSLI   = aucLI;

    /* 获取ENVELOPE消息参数: 服务小区信息 */
    TAF_SDC_Get3GppCurrentLai(aucLI, &stENStru.uEnvelope.MOSMSCtrl.LocInfo.ulLen);


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, usClientId, &stENStru);

    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_MoSmsControlEnvelopeReq: Usim Returns Error");
        return MN_ERR_CLASS_SMS_MO_CTRL_USIM_PARA_ERROR;
    }
    else
    {
        return MN_ERR_NO_ERROR;
    }
}


VOS_UINT32  MN_MSG_SmsPPEnvelopeReq(
    const MN_MSG_BCD_ADDR_STRU          *pstAddr,
    const VOS_UINT8                     *pucTpduData,
    const VOS_UINT32                    ulTpduLen
)
{
    SI_STK_ENVELOPE_STRU stDataDownLoad;
    SI_STK_SMS_PP_DOWNLOAD_STRU *pstPPDown;
    VOS_UINT32 ulRet = VOS_ERR;
    VOS_UINT32 ulOffset;

    if(SI_STK_DATA_MAX_LEN <(pstAddr->ucBcdLen+ulTpduLen))
    {
        return VOS_ERR;
    }

    PS_MEM_SET(&stDataDownLoad, 0, sizeof(stDataDownLoad));

    stDataDownLoad.enEnvelopeType   = SI_STK_ENVELOPE_PPDOWN;
    stDataDownLoad.DeviceId.ucSDId  = SI_DEVICE_NETWORK;
    stDataDownLoad.DeviceId.ucDDId  = SI_DEVICE_UICC;

    pstPPDown = &stDataDownLoad.uEnvelope.PPDown;
    /*填写短信中心地址*/
    pstPPDown->OP_Addr = 1;
    pstPPDown->Addr.ucNumType = pstAddr->addrType;
    pstPPDown->Addr.ucLen     = pstAddr->ucBcdLen;

    PS_MEM_CPY(stDataDownLoad.aucData, pstAddr->aucBcdNum, pstPPDown->Addr.ucLen);

    pstPPDown->Addr.pucAddr = stDataDownLoad.aucData;

    ulOffset = pstPPDown->Addr.ucLen;

    /*填写短信PDU内容*/
    pstPPDown->OP_TPDU = 1;
    pstPPDown->TPDU.ulLen = ulTpduLen;

    PS_MEM_CPY(&stDataDownLoad.aucData[ulOffset], pucTpduData, pstPPDown->TPDU.ulLen);

    pstPPDown->TPDU.pucTPDU = &stDataDownLoad.aucData[ulOffset];


    ulRet = NAS_STKAPI_EnvelopeDownload(WUEPS_PID_TAF, MN_CLIENT_ID_BROADCAST,&stDataDownLoad);

/*
    调用USIM提供的envelope data download函数将内容下发的USIM
    if 函数返回成功
        返回 TAF_OK
    else
        返回 MN_ERR
*/

    return ulRet;
}


VOS_VOID  MN_MSG_WriteSmssFile(
    const MN_MSG_SMSS_INFO_STRU         *pstSmssInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucWriteData[MN_MSG_MAX_EF_LEN];
    VOS_UINT32                          ulUsimIndex = 0;
    MN_MSG_USIM_INFO_STRU               stUsimInfo;
    TAF_MMA_NVIM_SMS_EFSMSS_PARA_STRU   stSmssContent;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSS_ID;
    }
    ulRet       = 0;

    PS_MEM_SET(aucWriteData,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    PS_MEM_SET(&stSmssContent,(VOS_CHAR)0x00,MN_MSG_EFSMSS_PARA_LEN);

    aucWriteData[0] = pstSmssInfo->ucLastUsedTpMr;
    if (MN_MSG_MEM_FULL_SET == pstSmssInfo->enMemCapExcNotFlag)
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_SET;
    }
    else
    {
        aucWriteData[1] = MN_MSG_SIM_MEM_FULL_UNSET;
    }

    /*先更新内存中的信息*/
    PS_MEM_CPY(&f_stMsgEfSmssInfo.stEfSmssInfo,pstSmssInfo,sizeof(f_stMsgEfSmssInfo.stEfSmssInfo));

    if (VOS_TRUE == f_stMsgEfSmssInfo.bEfSmssState)
    {
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSS_ID, aucWriteData, (VOS_UINT8)f_stMsgEfSmssInfo.ulFileLen, MN_MSG_USIM_DEF_REC);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmssFile:Add Usim Node Failed");
            return ;
        }
        PS_MEM_SET(&stUsimInfo,0X00, sizeof(stUsimInfo));


        stUsimInfo.opId = 0;
        stUsimInfo.enDeleteType = MN_MSG_DELETE_MAX;
        stUsimInfo.usEfId = (VOS_UINT16)ulFileId;
        stUsimInfo.ucRecIndex = MN_MSG_USIM_DEF_REC;
        stUsimInfo.enSmaUsimAction = MN_MSG_USIM_SET_EFSMSS;

        ulRet = MN_MSG_CreateNewUsimNode(&stUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:CreateNewUsimNode Error");
        }
    }
    else
    {
        PS_MEM_CPY(&stSmssContent, (VOS_VOID*)aucWriteData, MN_MSG_MAX_EF_LEN);
        ulRet = NV_Write(en_NV_Item_SMS_EFSMSS_Para,(VOS_VOID*)&stSmssContent,MN_MSG_MAX_EF_LEN);
        if (NV_OK != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmssFile:Write NVIM Error");
        }
    }
}

#if ((NAS_FEATURE_SMS_FLASH_SMSEXIST == FEATURE_ON)\
  && (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON))

VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const VOS_UINT32                   *pulMeIndex,
    const MN_MSG_WRITE_USIM_INFO_STRU  *pstWriteUsimInfo,
    VOS_UINT8                          *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    ulRet       = 0;

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_NULL_PTR == pstWriteUsimInfo)
        {
            return MN_ERR_NULLPTR;
        }

        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }

        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstWriteUsimInfo->stUsimInfo.ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == pstWriteUsimInfo->bCreateNode)
        {
            /*设置USIM时,需要将原始的短信保留下来*/
            ucOrgIndex = pstWriteUsimInfo->stUsimInfo.ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),(VOS_CHAR)0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(&(pstWriteUsimInfo->stUsimInfo),&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstWriteUsimInfo->stUsimInfo.ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (VOS_NULL_PTR == pulMeIndex)
        {
            return MN_ERR_NULLPTR;
        }

        ulRet = MN_MSG_WriteMsgInFlashByIndex(*pulMeIndex,pucContentInfo);

        if (MN_ERR_NO_ERROR != ulRet)
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write FLASH Error");
            MN_MNTN_RecordSmsMeError(MNTN_ME_OPERATION_WRITE, ulRet);
            return ulRet;
        }
        else
        {
            /*更新内存中NVIM中的短信状态*/
            f_aucMsgNvimSmStatus[*pulMeIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}
#else

VOS_UINT32  MN_MSG_WriteSmsFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    VOS_BOOL                            bCreateNode,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMS_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMS_ID;
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile: EFSMS is not available.");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID,pucContentInfo,MN_MSG_EFSMS_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }

        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }
        if (VOS_TRUE == bCreateNode)
        {
            /*设置USIM时,需要将原始的短信保留下来*/
            ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
            PS_MEM_SET((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),0XFF,MN_MSG_EFSMS_LEN);
            PS_MEM_CPY((f_aucMsgOrgSmContent + (ucOrgIndex * MN_MSG_EFSMS_LEN)),
                       (f_stMsgEfSmsInfo.aucEfSmsList+ (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                       MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
            if (VOS_OK != ulRet)
            {
                return MN_ERR_CLASS_SMS_CREATE_NODE;
            }
        }
        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsInfo.aucEfSmsList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMS_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMS_LEN);
        return MN_ERR_NO_ERROR;
    }
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    else if (MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_Content,
                              (VOS_VOID*)pucContentInfo,
                              MN_MSG_EFSMS_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmsFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
        else
        {
            /*更新内存中NVIM中的短信状态*/
            f_aucMsgNvimSmStatus[pstSmaUsimInfo->ucRecIndex] = *pucContentInfo;
            return MN_ERR_NO_ERROR;
        }
    }
#endif
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
}

#endif


VOS_UINT32  MN_MSG_WriteSmsrFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    VOS_UINT8                           *pucContentInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT8                           ucOrgIndex;
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType   = TAF_SDC_GetSimType();
    ulRet       = 0;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        /*设置USIM时,需要将原始的短信状态报告保留下来*/
        ucOrgIndex = pstSmaUsimInfo->ucRecIndex%MN_MSG_MAX_ORG_REC_NUM;
        PS_MEM_SET((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),0X00,MN_MSG_EFSMSR_LEN);
        PS_MEM_CPY((f_aucMsgOrgSmsrContent + (ucOrgIndex * MN_MSG_EFSMSR_LEN)),
                   (f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   MN_MSG_EFSMSR_LEN);
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSR_ID,pucContentInfo,MN_MSG_EFSMSR_LEN,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmsrFile:Add Usim Node Failed");
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*更新内存中的信息*/
        PS_MEM_CPY((f_stMsgEfSmsrInfo.aucEfSmsrList + (pstSmaUsimInfo->ucRecIndex * MN_MSG_EFSMSR_LEN)),
                   pucContentInfo,
                   MN_MSG_EFSMSR_LEN);
    }
    else if(MN_MSG_MEM_STORE_NV == enMemStore)
    {
        if (MN_MSG_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucSmsNvSmsRexitSupportFlg)
        {
            if (NV_OK != NV_Write(en_NV_Item_SMS_Status,pucContentInfo,MN_MSG_EFSMSR_LEN))
            {
                MN_ERR_LOG("MN_MSG_WriteSmsrFile:Write NVIM Error");
                return MN_ERR_CLASS_SMS_NVIM;
            }
        }
    }
    else
    {
        MN_WARN_LOG1("MN_MSG_WriteSmsrFile: enMemStore is ", enMemStore);
        return MN_ERR_INVALIDPARM;
    }
    return MN_ERR_NO_ERROR;

}


VOS_UINT32  MN_MSG_WriteSmspFile(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    const MN_MSG_USIM_INFO_STRU         *pstSmaUsimInfo,
    const MN_MSG_SRV_PARAM_STRU         *pstSrvParam
)
{
    VOS_UINT32                          ulUsimIndex = 0;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulAlphaIdLen;
    VOS_UINT32                          ulAddrlen;
    VOS_UINT32                          ulPos = 0;
    VOS_UINT8                           aucSmspContent[MN_MSG_MAX_EF_LEN];
    TAF_MMA_NVIM_SMS_EFSMSP_PARA_STRU   stSmspContent;
    VOS_UINT8                           ucLen;
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstEfSmspRec;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT32                          ulFileId;

    enSimType   = TAF_SDC_GetSimType();
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {
        ulFileId    = USIMM_USIM_EFSMSP_ID;
    }
    else
    {
        ulFileId    = USIMM_TELE_EFSMSP_ID;
    }
    ulRet       = 0;

    MN_INFO_LOG("MN_MSG_WriteSmspFile: step into function.");

    PS_MEM_SET(&stSmspContent,(VOS_CHAR)0x00,MN_MSG_EFSMSP_PARA_LEN);
    PS_MEM_SET(aucSmspContent,(VOS_CHAR)0xFF,MN_MSG_MAX_EF_LEN);
    pstEfSmspRec = &f_stMsgEfSmspInfo.astEachEfSmspInfo[pstSmaUsimInfo->ucRecIndex];
    ucLen = (VOS_UINT8)(MN_MSG_MIN_SRV_PARM_LEN + pstEfSmspRec->stParm.stAlphaIdInfo.ulLen);

    /*Alpha Identifier*/
    if (pstSrvParam->stAlphaIdInfo.ulLen > pstEfSmspRec->stParm.stAlphaIdInfo.ulLen)
    {
        ulAlphaIdLen = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;
    }
    else
    {
        ulAlphaIdLen = pstSrvParam->stAlphaIdInfo.ulLen;
    }

    PS_MEM_CPY(aucSmspContent,pstSrvParam->stAlphaIdInfo.aucData,ulAlphaIdLen);

    /*将游标移至ALPHAID数据项后，ALPHAID数据数据区的长度为固定值，与用户输入的实际数据长度无关*/
    ulPos = pstEfSmspRec->stParm.stAlphaIdInfo.ulLen;

    /*Parameter Indicators*/
    MN_INFO_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->ucParmInd", pstSrvParam->ucParmInd);
    /*lint -e961*/
    aucSmspContent[ulPos++] = pstSrvParam->ucParmInd;
    /*lint +e961*/

    /*TP Destination Address*/
    MN_NORM_LOG1("MN_MSG_WriteSmspFile: pstSrvParam->stDestAddr.ucBcdLen", pstSrvParam->stDestAddr.ucBcdLen);
    PS_MEM_SET(&aucSmspContent[ulPos], (VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DEST_ADDR))
     && (0 != pstSrvParam->stDestAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU*)&pstSrvParam->stDestAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_FALSE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TS Service Centre Address*/
    PS_MEM_SET(&aucSmspContent[ulPos],(VOS_CHAR)MN_MSG_USIM_FILL_BYTE, MN_MSG_EFSMSP_ADDR_UNIT_LEN);
    if ((0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_SC_ADDR))
     && (0 != pstSrvParam->stScAddr.ucBcdLen))
    {
        ulRet = MN_MSG_BcdAddrToAscii((MN_MSG_BCD_ADDR_STRU *)&pstSrvParam->stScAddr, &stAsciiAddr);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
        ulRet = MN_MSG_EncodeAddress(&stAsciiAddr, VOS_TRUE, &aucSmspContent[ulPos], &ulAddrlen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }
    ulPos += MN_MSG_EFSMSP_ADDR_UNIT_LEN;

    /*TP Protocol Identifier*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_PID))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucPid;
        /*lint +e961*/
    }

    /*TP Data Coding Scheme*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_DCS))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucDcs;
        /*lint +e961*/
    }

    /*TP Validity Period*/
    if (0 == (pstSrvParam->ucParmInd & MN_MSG_SRV_PARM_MASK_VALIDITY))
    {
        /*lint -e961*/
        aucSmspContent[ulPos++] = pstSrvParam->ucValidPeriod;
        /*lint +e961*/
    }
    PS_MEM_CPY(&stSmspContent, aucSmspContent, MN_MSG_MAX_EF_LEN);

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        if (VOS_FALSE == MN_MSG_IsUsimFileExist((VOS_UINT16)ulFileId))
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile: USIMM_USIM_EFSMSP_ID Not Exist");
            return MN_ERR_CLASS_SMS_FILE_NOEXIST;
        }
        if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {
            ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMSP_ID,aucSmspContent,ucLen,pstSmaUsimInfo->ucRecIndex + 1);
        }
        else
        {
            ulRet = USIMM_API_FAILED;
        }
        if (USIMM_API_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_MSG_WriteSmspFile:Add Usim Node Failed");
            if (MN_MSG_USIM_DELETE_EFSMSP == pstSmaUsimInfo->enSmaUsimAction)
            {
                f_stMsgSetUsimRec.bDeleteEfSmspReportFlag = VOS_TRUE;
            }
            return MN_ERR_CLASS_SMS_UPDATE_USIM;
        }

        ulRet = MN_MSG_CreateNewUsimNode(pstSmaUsimInfo,&ulUsimIndex);
        if (VOS_OK != ulRet)
        {
            return MN_ERR_CLASS_SMS_CREATE_NODE;
        }

        /*更新内存中的信息*/
        if (MN_MSG_SRV_PARM_TOTALABSENT == ((pstSrvParam->ucParmInd) & MN_MSG_SRV_PARM_TOTALABSENT))
        {
            pstEfSmspRec->bUsed = VOS_FALSE;
        }
        else
        {
            pstEfSmspRec->bUsed = VOS_TRUE;
        }

        /*将老的短信服务参数保留下来*/
        PS_MEM_CPY(&f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex],
                   pstEfSmspRec,
                   sizeof(f_astMsgOrgSmspInfo[pstSmaUsimInfo->ucRecIndex]));

        PS_MEM_CPY(&pstEfSmspRec->stParm, pstSrvParam, sizeof(pstEfSmspRec->stParm));
        pstEfSmspRec->stParm.stAlphaIdInfo.ulLen = ulAlphaIdLen;
    }
    else
    {
        if (NV_OK != NV_Write(en_NV_Item_SMS_EFSMSP_Para,stSmspContent.aucSmsEfsmspPara,MN_MSG_MAX_EF_LEN))
        {
            MN_ERR_LOG("MN_MSG_WriteSmspFile:Write NVIM Error");
            return MN_ERR_CLASS_SMS_NVIM;
        }
    }

    return MN_ERR_NO_ERROR;
}



VOS_VOID  MN_MSG_RecoverOrgSrvParm(
    VOS_UINT8                           ucIndex,
    MN_MSG_USIM_EFSMSP_DTL_INFO_STRU    *pstSrvParam
)
{
    if (ucIndex >= f_stMsgEfSmspInfo.ucSmspRealRecNum)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pstSrvParam,0X00,sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
    PS_MEM_CPY(pstSrvParam,&f_astMsgOrgSmspInfo[ucIndex],sizeof(MN_MSG_USIM_EFSMSP_DTL_INFO_STRU));
}


VOS_VOID  MN_MSG_RecoverOrgSm(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmContent
)
{
    if (ucIndex >= MN_MSG_MAX_ORG_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSrvParm:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
    PS_MEM_CPY(pucSmContent,
              (f_aucMsgOrgSmContent + (ucIndex * MN_MSG_EFSMS_LEN)),
              MN_MSG_EFSMS_LEN);
}


VOS_VOID  MN_MSG_RecoverOrgSmsr(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           *pucSmsrContent
)
{
    if (ucIndex >= MN_MSG_MAX_DELETE_REC_NUM)
    {
        MN_ERR_LOG("MN_MSG_RecoverOrgSmsr:Invalid ucIndex. ");
        return;
    }

    PS_MEM_SET(pucSmsrContent,(VOS_CHAR)0xFF,MN_MSG_EFSMSR_LEN);
    PS_MEM_CPY(pucSmsrContent,
               (f_aucMsgOrgSmsrContent + (ucIndex * MN_MSG_EFSMSR_LEN)),
               MN_MSG_EFSMSR_LEN);
}


VOS_VOID MN_MSG_SmCfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_INFO_LOG("MN_MSG_SmCfgDataInit:Step into function.");


    MN_INFO_LOG1("MN_MSG_SmCfgDataInit:enUsimStatus is ", (VOS_INT32)enUsimStatus);
    MN_INFO_LOG1("MN_MSG_SmCfgDataInit: current enUsimStatus is ",f_stMsgUsimStatusInfo.ucUsimStatus);
    if (MNPH_USIM_STATUS_AVILABLE == enUsimStatus)
    {
        if (MN_MSG_SIM_EXIST == f_stMsgUsimStatusInfo.ucUsimStatus)
        {
            MN_NORM_LOG("MN_MSG_CfgDataInit:Rcv Usim Exist Flag Again");
            if ((MN_MSG_USIM_POWER_ON != f_stMsgUsimStatusInfo.enPowerState)
             && (MN_MSG_USIM_POWER_BEGIN != f_stMsgUsimStatusInfo.enPowerState))
            {
                MN_MSG_StopTimer(MN_MSG_TID_WAIT_GET_EF_RSP);
                MN_NORM_LOG("MN_MSG_CfgDataInit:Stop Timer");
            }
        }
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_BEGIN;

        MN_MSG_UpdateUstInfo();

        /*获取USIM相关参数*/
        if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
        {
            MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
        }
        else
        {
            MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
        }
    }
    else
    {
        f_stMsgUsimStatusInfo.ucUsimStatus = MN_MSG_SIM_NOT_EXIST;
        f_stMsgUsimStatusInfo.enPowerState = MN_MSG_USIM_POWER_ON;
    }
}


VOS_VOID MN_MSG_CreateEFSmContent(
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    VOS_UINT8                           ucStatus,
    VOS_UINT8                           *pucContent
)
{
    VOS_UINT32                          ulWriteSet = 0;

    PS_MEM_SET(pucContent, (VOS_CHAR)0xff, MN_MSG_EFSMS_LEN);
    *pucContent = ucStatus;
    if (pstScAddr->ucBcdLen > 0)
    {
        *(pucContent + 1 ) = (pstScAddr->ucBcdLen + 1);
        *(pucContent + 2 ) = pstScAddr->addrType;
        PS_MEM_CPY(pucContent + 3,pstScAddr->aucBcdNum ,pstScAddr->ucBcdLen);
        ulWriteSet = 1 + pstScAddr->ucBcdLen + 2;
    }
    else
    {
        *(pucContent + 1 ) = 0;
        ulWriteSet = 1 + 1;
    }

    if (ulWriteSet >=  MN_MSG_EFSMS_LEN)
    {
        return;
    }
    if (pstRawData->ulLen > (MN_MSG_EFSMS_LEN - ulWriteSet))
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,MN_MSG_EFSMS_LEN - ulWriteSet);
    }
    else
    {
        PS_MEM_CPY(pucContent + ulWriteSet,pstRawData->aucData,pstRawData->ulLen);
    }
}


VOS_UINT32 MSG_DecodeScAddress(
    const VOS_UINT8                     *pucAddr,
    MN_MSG_BCD_ADDR_STRU                *pstBcdAddr,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT32                          ulRet;
    MN_MSG_ASCII_ADDR_STRU              stAsciiAddr;

    if ((VOS_NULL_PTR == pucAddr)
     || (VOS_NULL_PTR == pstBcdAddr)
     || (VOS_NULL_PTR == pulLen))
    {
        MN_ERR_LOG("MSG_DecodeScAddress: Parameter of the function is null.");
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_MSG_DecodeAddress(pucAddr, VOS_TRUE, &stAsciiAddr, pulLen);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        pstBcdAddr->ucBcdLen = (VOS_UINT8)(stAsciiAddr.ulLen + 1)/2;
        /* 根据协议23040 9.1.2.5 地址类型域格式如下所示
            bit7   bit6    -   bit4             bit3    -   bit0
             1      type of number      Numbering-plan-identification */
        pstBcdAddr->addrType = 0x80;
        pstBcdAddr->addrType |= (stAsciiAddr.enNumPlan & 0x0f);
        pstBcdAddr->addrType |= (VOS_UINT8)((stAsciiAddr.enNumType << 4) & 0x70);
        ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)stAsciiAddr.aucAsciiNum,
                                    pstBcdAddr->aucBcdNum,
                                    &pstBcdAddr->ucBcdLen);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    return ulRet;
}


VOS_UINT32 MSG_GetTpduLen(
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
    VOS_UINT32                          *pulLen
)
{
    MN_MSG_RAW_TS_DATA_STRU             *pstTmpRawData;
    VOS_UINT32                          ulRet;

    pstTmpRawData = (MN_MSG_RAW_TS_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_RAW_TS_DATA_STRU));
    if (VOS_NULL_PTR == pstTmpRawData)
    {
        MN_ERR_LOG("MSG_GetTpduLen: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }
    ulRet = MN_MSG_Encode(pstTsDataInfo, pstTmpRawData);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_GetTpduLen: Fail to encode msg.");
    }
    else
    {
        *pulLen = pstTmpRawData->ulLen;
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTmpRawData);
    return ulRet;
}


VOS_UINT32 MN_MSG_ParseEFSmContent(
    const VOS_UINT8                     *pucContent,
    MN_MSG_BCD_ADDR_STRU                *pstScAddr,
    MN_MSG_RAW_TS_DATA_STRU             *pstRawData,
    VOS_UINT8                           *pucStatus
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulScaLen;
    VOS_UINT8                           ucFo;
    MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo;
    VOS_UINT8                           ucSmStatus;
    MN_MSG_TPDU_TYPE_ENUM_U8            aucMtiMapTpduType[4] = {MN_MSG_TPDU_DELIVER,
                                                                MN_MSG_TPDU_SUBMIT,
                                                                MN_MSG_TPDU_COMMAND,
                                                                MN_MSG_TPDU_MAX};

    *pucStatus = *pucContent;
    if (EF_SMS_STATUS_FREE_SPACE == ((*pucStatus) & 0x01))
    {
        return MN_ERR_CLASS_SMS_EMPTY_REC;
    }
    ulRet = MSG_DecodeScAddress((pucContent + 1), pstScAddr, &ulScaLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid SC address.");
        return ulRet;
    }

    ucFo = *(pucContent + (1 + ulScaLen));
    pstRawData->enTpduType = aucMtiMapTpduType[(ucFo & 0x03)];
    if (MN_MSG_TPDU_COMMAND == pstRawData->enTpduType)
    {
         /*短信命令和短信状态报告的TP-MTI均为4，这里通过SMS的发送状态来确认是否为短信状态报告*/
         ucSmStatus = ((*pucStatus)& EF_SMS_STATUS_MO_SEND_TO_NT);
         if (EF_SMS_STATUS_MO_SEND_TO_NT != ucSmStatus)
         {
            pstRawData->enTpduType = MN_MSG_TPDU_STARPT;
         }
    }

    if (MN_MSG_TPDU_MAX == pstRawData->enTpduType)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: invalid TPDU type.");
        return MN_ERR_CLASS_SMS_INVALID_TPDUTYPE;
    }

    pstRawData->ulLen = MN_MSG_EFSMS_LEN - (1 + ulScaLen);
    PS_MEM_CPY(pstRawData->aucData,
               (pucContent + (1 + ulScaLen)),
               pstRawData->ulLen);

    while (0 != pstRawData->ulLen)
    {
        if (MN_MSG_USIM_FILL_BYTE == pstRawData->aucData[pstRawData->ulLen - 1])
        {
            pstRawData->ulLen--;
        }
        else
        {
            break;
        }
    }

    pstTsDataInfo = (MN_MSG_TS_DATA_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                        sizeof(MN_MSG_TS_DATA_INFO_STRU));
    if (VOS_NULL_PTR == pstTsDataInfo)
    {
        MN_ERR_LOG("MN_MSG_ParseEFSmContent: Fail to alloc memory.");
        return MN_ERR_NOMEM;
    }

    ulRet = MN_MSG_Decode(pstRawData, pstTsDataInfo);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to decode message.");
        return ulRet;
    }

    /*获取消息的真实长度截取冗余字段*/
    ulRet = MSG_GetTpduLen(pstTsDataInfo, &pstRawData->ulLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MN_MSG_ParseEFSmContent: Fail to get message length.");
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstTsDataInfo);
    return ulRet;
}


VOS_VOID MN_MSG_GetAppStatus(
    VOS_UINT8                           ucStatus,
    MN_MSG_STATUS_TYPE_ENUM_U8          *penStatus
)
{
    if (EF_SMS_STATUS_MO_TO_BE_SEND == (ucStatus & 0x07))
    {
        *penStatus = MN_MSG_STATUS_MO_NOT_SENT;
    }
    else if (EF_SMS_STATUS_MO_SEND_TO_NT == (ucStatus & 0x05))
    {
        *penStatus = MN_MSG_STATUS_MO_SENT;
    }
    else if (EF_SMS_STATUS_MT_TO_BE_READ == (ucStatus & 0x03))
    {
        *penStatus = MN_MSG_STATUS_MT_NOT_READ;
    }
    else if (EF_SMS_STATUS_MT_READ == (ucStatus & 0x01))
    {
        *penStatus = MN_MSG_STATUS_MT_READ;
    }
    else
    {
        *penStatus = MN_MSG_STATUS_MAX;
    }
}


VOS_VOID MN_MSG_GetPsStatus(
    MN_MSG_STATUS_TYPE_ENUM_U8          enStatus,
    VOS_UINT8                           *pucStatus
)
{
    if (MN_MSG_STATUS_MT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_READ;
    }
    else if (MN_MSG_STATUS_MT_NOT_READ == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MT_TO_BE_READ;
    }
    else if (MN_MSG_STATUS_MO_NOT_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_TO_BE_SEND;
    }
    else if (MN_MSG_STATUS_MO_SENT == enStatus)
    {
        *pucStatus = EF_SMS_STATUS_MO_SEND_TO_NT;
    }
    else
    {
        *pucStatus = EF_SMS_STATUS_FREE_SPACE;
    }
}


VOS_VOID MSG_BuildDeliverEvtParm(
    const MN_MSG_CONFIG_PARM_STRU       *pstCfgParm,
    const MN_MSG_BCD_ADDR_STRU          *pstScAddr,
    const MN_MSG_RAW_TS_DATA_STRU       *pstRawData,
    MN_MSG_DELIVER_EVT_INFO_STRU        *pstDeliverEvt
)
{
    PS_MEM_SET(pstDeliverEvt,0X00,sizeof(MN_MSG_DELIVER_EVT_INFO_STRU));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stScAddr,
               pstScAddr,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stScAddr));
    PS_MEM_CPY(&pstDeliverEvt->stRcvMsgInfo.stTsRawData,
               pstRawData,
               sizeof(pstDeliverEvt->stRcvMsgInfo.stTsRawData));
    pstDeliverEvt->enMemStore = pstCfgParm->enSmMemStore;
    pstDeliverEvt->enRcvSmAct = pstCfgParm->enRcvSmAct;
}


MN_OPERATION_ID_T  MN_MSG_GetBCopId(VOS_VOID)
{
    return f_tMsgOpId++;
}


VOS_VOID MN_MSG_UpdateNeedSendUsim(
    VOS_UINT32                          ulInedx,
    VOS_BOOL                            bUpdateStatus
)
{
    if (ulInedx >= f_stMsgEfSmsInfo.ucSmsRealRecNum)
    {
        return;
    }
    f_bNeedSendUsim[ulInedx] = bUpdateStatus;
}


VOS_VOID MN_MSG_GetNeedSendUsim(
    VOS_UINT32                          *pulRealRec,
    VOS_BOOL                            *pbNeedSendUsim
)
{
    *pulRealRec = f_stMsgEfSmsInfo.ucSmsRealRecNum;
    PS_MEM_CPY(pbNeedSendUsim,f_bNeedSendUsim,sizeof(VOS_BOOL)*MN_MSG_MAX_USIM_SMS_NUM);
}


LOCAL VOS_UINT32 MN_MSG_CheckMemFull(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_BOOL                            bUnavailableFlag;
    VOS_BOOL                            bSmUnavailableFlag;
    MN_MSG_CONFIG_PARM_STRU             stCfgParm;

    MN_INFO_LOG("MN_MSG_CheckMemFull: step into function.");

    PS_MEM_SET(&stCfgParm, 0, sizeof(stCfgParm));

    /* 获取用户的短信接收存储配置 */
    MN_MSG_GetCurCfgParm(&stCfgParm);

    /* 若用户配置的短信存储方式为非MODEM存储，则检查APP短信接收功能是否可用 */
    if (MN_MSG_RCVMSG_ACT_STORE != stCfgParm.enRcvSmAct)
    {
        ulRet = MN_MSG_AppStorageUnavailable(stCfgParm.enRcvSmAct,
                                            stCfgParm.enAppMemStatus,
                                            &bUnavailableFlag);
    }
    /* 若用户配置的短信存储方式为MODEM存储，则检查用户设置的存储介质是否可用 */
    else
    {
        ulRet = MN_MSG_UeStorageUnavailable(stCfgParm.enSmMemStore, &bUnavailableFlag);
    }

    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    ulRet = MN_MSG_UeStorageUnavailable(MN_MSG_MEM_STORE_SIM, &bSmUnavailableFlag);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return VOS_FALSE;
    }

    /* 仅当用户指定存储空间满且(U)SIM卡满情况下返回短信存储空间满 */
    if ((VOS_TRUE == bUnavailableFlag)
     && (VOS_TRUE == bSmUnavailableFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


VOS_VOID MN_MSG_FailToWriteEfsms(
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore,
    MN_MSG_WRITE_EFSMS_CAUSE_ENUM_U32   enFailCause
)
{
    VOS_UINT32                          ulRet;
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_TP_CAUSE_ENUM_U8             enTpCause;
    MN_MSG_MT_CUSTOMIZE_ENUM_UINT8      enMtCustomize;

    /* 根据协议51010 34.2.5.3 SIM卡存储短信异常回复错误原因值9240，UE处理同
       SM存储区满 */
    if ((MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL != enFailCause)
     && (MN_MSG_WRITE_EFSMS_CAUSE_MEM_PROBLEM != enFailCause))
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                MN_MSG_TP_CAUSE_ERR_IN_MS);
        return;
    }

    /* 此处是否需要判断待确认 */
    if (MN_MSG_WRITE_EFSMS_CAUSE_MEM_FULL == enFailCause)
    {
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportMemExceed(bcOpId, enMemStore);
    }

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        enTpCause = MN_MSG_TP_CAUSE_SIM_FULL;
    }
    else
    {
        enTpCause = MN_MSG_TP_CAUSE_MEMORY_FULL;
    }

     /*The MS shall return a "protocol error, unspecified" error message
    (see 3GPP TS 24.011 [6]) if the short message cannot be stored in the
    (U)SIM and there is other short message storage available at the MS.
    If all the short message storage at the MS is already in use, the MS
    shall return "memory capacity exceeded". */
    ulRet = MN_MSG_CheckMemFull();
    if (VOS_TRUE == ulRet)
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_MEMORY_EXCEEDED,
                                enTpCause);

        MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);

    }
    else
    {
        MN_MSG_Internal_SendRpt(VOS_FALSE,
                                MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED,
                                enTpCause);

        enMtCustomize       = MN_MSG_MT_CUSTOMIZE_NONE;
        MN_MSG_GetMtCustomizeInfo(&enMtCustomize);
        if (MN_MSG_MT_CUSTOMIZE_DCM == enMtCustomize)
        {
            MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FULL_SET);
        }
    }

    return;
}

/*****************************************************************************
*  Prototype       : MN_MSG_UpdateSendFailFlag
*  Description     : 更新当前发送失败的域
*  Input           : enSendFailFlag --- 当前发送失败的域;
*  Output          :
*  Return Value    : void
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 VOS_VOID MN_MSG_UpdateSendFailFlag(
    MN_MSG_SEND_FAIL_FLAG_U8            enSendFailFlag
)
{
    f_enMsgSendFailFlag = enSendFailFlag;
}

/*****************************************************************************
*  Prototype       : MN_MSG_GetSendFailFlag
*  Description     : 获取当前发送失败的域
*  Input           : 无;
*  Output          :
*  Return Value    : 当前发送失败的域
*  Calls           :
*  Called By       :
*  History         :
*  1. Date         : 2009-07-13
*     Author       : z40661
*     Modification : Created function
*****************************************************************************/
 MN_MSG_SEND_FAIL_FLAG_U8 MN_MSG_GetSendFailFlag(VOS_VOID)
{
    return f_enMsgSendFailFlag;
}


VOS_VOID MN_MSG_GetRetryInfo(
    MN_MSG_RETRY_INFO_STRU              *pstRetryInfo
)
{
    VOS_UINT32                          bTestCard;

#if ( VOS_WIN32 == VOS_OS_VER )
    if (0 != g_ucDisableMoRetry)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
        return;
    }
#endif

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        PS_MEM_SET(pstRetryInfo, 0x00, sizeof(f_stMsgRetryInfo));
    }
    else
    {
        PS_MEM_CPY(pstRetryInfo, &f_stMsgRetryInfo,sizeof(f_stMsgRetryInfo));
    }

    return;
}


VOS_VOID MN_MSG_SaveRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstMsg)
{
    PS_MEM_CPY(&f_stMsgRpErrInfo, pstMsg, sizeof(f_stMsgRpErrInfo));
}


VOS_VOID MN_MSG_GetRpErrInfo(SMR_SMT_MO_REPORT_STRU *pstRpErrInfo)
{
    PS_MEM_CPY(pstRpErrInfo,&f_stMsgRpErrInfo,sizeof(f_stMsgRpErrInfo));
}


MN_MSG_CLASS0_TAILOR_U8 MN_MSG_GetClass0Tailor(VOS_VOID)
{
    VOS_UINT32                          bTestCard;

    bTestCard = NAS_USIMMAPI_IsTestCard();
    if (VOS_TRUE == bTestCard)
    {
        return MN_MSG_CLASS0_VIVO;
    }
    else
    {
        return g_enMsgClass0Tailor;
    }
}


VOS_VOID MN_MSG_SetClass0Tailor(MN_MSG_CLASS0_TAILOR_U8                 enClass0Tailor)
{
    g_enMsgClass0Tailor = enClass0Tailor;
}


MN_MSG_SEND_DOMAIN_ENUM_U8  MN_MSG_GetRealPrefSendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeDomain
)
{
    if (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }


    if (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeDomain)
    {
        if (MN_MSG_SEND_DOMAIN_PS == enSendDomain)
        {
            return MN_MSG_SEND_DOMAIN_PS_PREFERRED;
        }
        else
        {
            return MN_MSG_SEND_DOMAIN_CS_PREFERRED;
        }
    }

    return enHopeDomain;
}


VOS_VOID  MN_MSG_GetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          *penPid,
    MN_MSG_DCS_CODE_STRU                *pstDcs
)
{
    *penPid = f_stMsgMtEntity.enPid;
    PS_MEM_CPY(pstDcs, &f_stMsgMtEntity.stDcs, sizeof(f_stMsgMtEntity.stDcs));
}


VOS_VOID  MN_MSG_SetMtTpPidAndDcs(
    MN_MSG_TP_PID_TYPE_ENUM_U8          enPid,
    MN_MSG_DCS_CODE_STRU                stDcs
)
{
    f_stMsgMtEntity.enPid = enPid;
    PS_MEM_CPY(&f_stMsgMtEntity.stDcs, &stDcs, sizeof(f_stMsgMtEntity.stDcs));
}


VOS_VOID MSG_UpdateUsimForList(
    MN_CLIENT_ID_T                      clientId,
    VOS_UINT8                           ucChangeNum,
    MN_MSG_MEM_STORE_ENUM_U8            enMemStore
)
{
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
            MN_OPERATION_ID_T                   bcOpId;
#endif

    if (MN_MSG_MEM_STORE_SIM == enMemStore)
    {
        MN_MSG_SetUsimRec(MN_MSG_SET_USIM_LIST,ucChangeNum);
    }
    else
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
        /*广播上报NVIM中短信已发生了改变*/
        bcOpId = MN_MSG_GetBCopId();
        MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
#endif
    }
}

/*lint -e438 -e830*/


VOS_VOID MN_MSG_RptMsg(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList,
    MN_MSG_LIST_EVT_INFO_STRU           *pstListRptEvt
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT8                           ucEventNum  = 0;
    VOS_UINT32                          ulCapality;
    static VOS_UINT32                   ulBeginIdx = 0;
    VOS_UINT8                           ucListStatus;
    static VOS_UINT8                    ucChangeNum = 0;
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    MN_OPERATION_ID_T                   bcOpId;
#endif

    /* 获取需列表短信状态 */
    ucListStatus = EF_SMS_STATUS_FREE_SPACE;
    if (MN_MSG_STATUS_NONE != pstList->enStatus)
    {
        MN_MSG_GetPsStatus(pstList->enStatus, &ucListStatus);
    }

    ulCapality = MN_MSG_GetSmCapacity(pstList->enMemStore);

    PS_MEM_CPY( &(pstListRptEvt->stReceivedListPara), pstList, sizeof(MN_MSG_LIST_PARM_STRU) );

    /* 遍历需上报短信,达到列表上限后启动定时器退出 */
    for (; ulBeginIdx < ulCapality; ulBeginIdx++)
    {
        ulRet = MN_MSG_GetStatus(pstList->enMemStore,ulBeginIdx,&ucStatus);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            continue;
        }

        if ((MN_MSG_STATUS_NONE == pstList->enStatus)
         || (ucListStatus == ucStatus))
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(pstList->enMemStore,ulBeginIdx,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            ulRet = MN_MSG_ParseEFSmContent(aucSmContent,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stScAddr,
                                            &pstListRptEvt->astSmInfo[ucEventNum].stMsgInfo.stTsRawData,
                                            &ucStatus);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                pstListRptEvt->bSuccess = VOS_FALSE;
                pstListRptEvt->bLastListEvt = VOS_TRUE;
                pstListRptEvt->ulReportNum = ucEventNum;
                pstListRptEvt->ulFailCause = ulRet;
                MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
                break;
            }
            MN_MSG_GetAppStatus(ucStatus,&pstListRptEvt->astSmInfo[ucEventNum].enStatus);
            pstListRptEvt->astSmInfo[ucEventNum].ulIndex = ulBeginIdx;
            ucEventNum++;

            if ((VOS_TRUE == pstList->bChangeFlag)
             && (EF_SMS_STATUS_MT_TO_BE_READ == ucStatus))
            {
                ulRet = MSG_ChangeSmStatus(pstList->enMemStore,
                                           clientId,
                                           opId,
                                           MN_MSG_USIM_LIST,
                                           ulBeginIdx,
                                           aucSmContent,
                                           &ucChangeNum);

                if (MN_ERR_NO_ERROR == ulRet )
                {
                    ucChangeNum++;
                }
            }
        }

        if ((ulLeftReportNum != ucEventNum)
         && (MN_MSG_MAX_REPORT_EVENT_NUM != ucEventNum))
        {
            continue;
        }

        /* 列表短信完成后直接上报,否则启动定时器等待定时器超时后上报 */
        if (ulLeftReportNum == ucEventNum)
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_TRUE;
            pstListRptEvt->ulReportNum = ulLeftReportNum;
            ulBeginIdx = 0;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);
            if (ucChangeNum > 0)
            {
                /* 更新USIM文件中短信状态 */
                if (MN_MSG_MEM_STORE_SIM == pstList->enMemStore)
                {
                    MSG_UpdateUsimForList(clientId,ucChangeNum,pstList->enMemStore);
                }
                #if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
                else if (MN_MSG_MEM_STORE_NV == pstList->enMemStore)
                {
                    /*广播上报NVIM中短信已发生了改变*/
                    bcOpId = MN_MSG_GetBCopId();
                    MN_MSG_ReportSmChanged(clientId,bcOpId,VOS_TRUE,MN_MSG_MEM_STORE_NV);
                }
                #endif
                else
                {
                }
            }
            ucChangeNum = 0;
        }
        else
        {
            pstListRptEvt->bSuccess = VOS_TRUE;
            pstListRptEvt->bLastListEvt = VOS_FALSE;
            pstListRptEvt->ulReportNum = MN_MSG_MAX_REPORT_EVENT_NUM;
            ulLeftReportNum = ulLeftReportNum - MN_MSG_MAX_REPORT_EVENT_NUM;
            ucEventNum = 0;
            /* 此处+1的原语为,该index短信已被列表,需列表下一条短信 */
            ulBeginIdx++;
            MN_MSG_ReportListEvent(clientId,opId,pstListRptEvt,MN_MSG_EVT_LIST);


            MN_MSG_UpdateListInfo(clientId,opId,ulLeftReportNum,pstList);
        }
        break;
    }

}
/*lint +e438 +e830*/


VOS_VOID  MN_MSG_InitRcvPath( VOS_VOID )
{
    MN_OPERATION_ID_T                   bcOpId;
    MN_MSG_RCVMSG_PATH_EVT_INFO_STRU    stRcvPathEvt;

    f_stMsgCfgParm.enRcvSmAct       = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enSmMemStore     = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enRcvStaRptAct   = MN_MSG_RCVMSG_ACT_STORE;
    f_stMsgCfgParm.enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
    f_stMsgCfgParm.enCbmMemStore    = MN_MSG_MEM_STORE_NONE;

    stRcvPathEvt.enRcvSmAct         = f_stMsgCfgParm.enRcvSmAct;
    stRcvPathEvt.enSmMemStore       = f_stMsgCfgParm.enSmMemStore;
    stRcvPathEvt.enRcvStaRptAct     = f_stMsgCfgParm.enRcvStaRptAct;
    stRcvPathEvt.enStaRptMemStore   = f_stMsgCfgParm.enStaRptMemStore;
    stRcvPathEvt.enCbmMemStore      = f_stMsgCfgParm.enCbmMemStore;

    bcOpId = MN_MSG_GetBCopId();
    MN_MSG_ReportRcvPathEvent(MN_CLIENT_ALL, bcOpId, VOS_TRUE, &stRcvPathEvt, MN_MSG_EVT_RCVMSG_PATH_CHANGED);

}


VOS_VOID MN_MSG_OutputSmsMoFailureInfo(
    TAF_MSG_ERROR_ENUM_UINT32           enErrorCode,
    NAS_MNTN_SMS_MO_INFO_STRU          *pstSmsMo
)
{
    /* 获取短信发送相关的服务数据 */
    pstSmsMo->stUstInfo.bEfSmssFlag     = f_stEfUstInfo.bEfSmssFlag;
    pstSmsMo->stUstInfo.bEfSmsFlag      = f_stEfUstInfo.bEfSmsFlag;
    pstSmsMo->stUstInfo.bEfSmsrFlag     = f_stEfUstInfo.bEfSmsrFlag;
    pstSmsMo->stUstInfo.bEfSmspFlag     = f_stEfUstInfo.bEfSmspFlag;
    pstSmsMo->stUstInfo.bMoSmsCtrlFlag  = f_stEfUstInfo.bMoSmsCtrlFlag;

    /* 获取短信模块初始化状态数据 */
    PS_MEM_CPY(&pstSmsMo->stMsgStatus,
               &f_stMsgUsimStatusInfo,
               sizeof(pstSmsMo->stMsgStatus));

    /* 获取目的号码和短信中心号码 */
    MN_MSG_GetAddressFromSubmit(f_stMsgMoEntity.aucRpDataInfo,
                                f_stMsgMoEntity.ucRpDataLen,
                                &pstSmsMo->stScAddr,
                                &pstSmsMo->stDestAddr);

    pstSmsMo->ulMoFailCause = enErrorCode;

    return;
}


VOS_UINT32 MN_MSG_ReadMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                	*fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*判断短信文件是否打开*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_ReadFlashByIndex: SmsFile Not Exit.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_NOTEXIST_FILE;
    }

    fp = gfpSmsFlash;

    /*获取文件大小*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if (((ulIndex + 1) * MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*定位到索引位置*/
    lRst = mdrv_file_seek(fp, (VOS_INT32)(ulIndex * MN_MSG_EFSMS_LEN), SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*读文件*/
    /* 低软接口修改，调整了参数 */
    lRst = mdrv_file_read(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if ((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:read error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_READ_FILE;
    }

    return MN_ERR_NO_ERROR;

}


VOS_UINT32 MN_MSG_WriteMsgInFlashByIndex(
    VOS_UINT32                          ulIndex,
    VOS_UINT8                          *pucSmContent
)
{
    FILE                                *fp;
    VOS_INT32                           lRst;
    VOS_UINT32                          ulFileSize;

    /*如果短信文件不存在，需要创建该文件*/
    if(VOS_NULL_PTR == gfpSmsFlash)
    {
        /*创建文件*/
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"wb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Create SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_CREATE_FILE;
        }

        /*读写方式打开文件*/
        (VOS_VOID)mdrv_file_close(gfpSmsFlash);
        gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
        if (VOS_NULL_PTR == gfpSmsFlash)
        {
            MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
            return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
        }
    }

    fp = gfpSmsFlash;

    /*获取文件大小*/
    lRst = (VOS_INT32)MN_GetFileSize(fp,&ulFileSize);
    if(MN_ERR_NO_ERROR != lRst)
    {
        MN_WARN_LOG("MN_MSG_ReadMsgInFlashByIndex:Get File Size error\n");
        return (VOS_UINT32)lRst;
    }

    if ((ulIndex*MN_MSG_EFSMS_LEN) > ulFileSize)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Para error.\n");
        return MN_ERR_INVALIDPARM;
    }

    /*定位到索引位置*/
    lRst = mdrv_file_seek(fp,(VOS_INT32)(ulIndex*MN_MSG_EFSMS_LEN),SEEK_SET);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:LSEEK error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_SEEK_FILE;
    }

    /*写文件*/
    /* 低软接口修改，调整了参数 */
    lRst = mdrv_file_write(pucSmContent, MN_MSG_EFSMS_LEN, 1, fp);
    if((-1) == lRst)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:write error\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_WRITE_FILE;
    }

    (VOS_VOID)mdrv_file_close(gfpSmsFlash);

    gfpSmsFlash = mdrv_file_open(g_pucSmsFileOnFlash,"rb+");
    if (VOS_NULL_PTR == gfpSmsFlash)
    {
        MN_WARN_LOG("MN_MSG_WriteMsgInFlashByIndex:Open SmsFile Fail.\n");
        return MN_ERR_CLASS_SMS_FLASH_MEM_OPEN_FILE;
    }

    return MN_ERR_NO_ERROR;
}


VOS_VOID MN_MSG_GetSmsServicePara(
    MN_MSG_CONFIG_PARM_STRU             *pstMsgCfgParm,
    MN_MSG_ME_STORAGE_STATUS_ENUM_UINT8 *penMeStorageEnable
)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU      stSmsSrvParam;
    /* 短信接收存储介质保存在NV配置文件的使能标志
       VOS_TRUE        短信接收存储介质保存在NV配置文件
       VOS_FALSE       短信接收存储介质不保存在NV配置文件，每次上电后恢复为SM存储 */
    VOS_BOOL                            bSmMemEnable;
    MN_MSG_ME_STORAGE_PARM_STRU         stMeStorageParm;

    MN_MSG_NVIM_MO_SMS_CTRL_STRU        stMnMsgSrvPara;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stSmsSrvParam, 0x00, sizeof(TAF_NVIM_SMS_SERVICE_PARA_STRU));
    PS_MEM_SET(&stMnMsgSrvPara, 0x00, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_BUTT;
    stMeStorageParm.usMeStorageNum    = 0;


    MN_MSG_InitSmsServiceData(pstMsgCfgParm);
    *penMeStorageEnable = MN_MSG_ME_STORAGE_DISABLE;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read Service Parm From Nvim Failed");
        return;
    }

    pstMsgCfgParm->enAppMemStatus = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_APP_MEM_STATUS_OFFSET];
    bSmMemEnable                  = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_SM_MEM_ENABLE_OFFSET];
    ulRet = NV_Read(en_NV_Item_Sms_Me_Storage_Info, &stMeStorageParm, sizeof(stMeStorageParm));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara: Read en_NV_Item_Sms_MeStorageEnable Failed");
        stMeStorageParm.enMeStorageStatus = MN_MSG_ME_STORAGE_DISABLE;
        f_usMsgNvimSmsCurReNum = 0;
        return;
    }

    if (MN_MSG_ME_STORAGE_ENABLE == stMeStorageParm.enMeStorageStatus)
    {
        if (VOS_TRUE == bSmMemEnable)
        {
            pstMsgCfgParm->enSmMemStore = (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_RCV_SM_MEM_STORE_OFFSET];
        }

        if (stMeStorageParm.usMeStorageNum > MN_MSG_MAX_NVIM_SMS_REC_NUM)
        {
            f_usMsgNvimSmsCurReNum = MN_MSG_MAX_NVIM_SMS_REC_NUM;
        }
        else
        {
            f_usMsgNvimSmsCurReNum = stMeStorageParm.usMeStorageNum;
        }
    }
    else
    {
        f_usMsgNvimSmsCurReNum = 0;
    }

    *penMeStorageEnable = stMeStorageParm.enMeStorageStatus;

    (VOS_VOID)NV_GetLength(en_NV_Item_MO_SMS_CONTROL_FEATURE, &ulLength);
    ulRet = NV_Read(en_NV_Item_MO_SMS_CONTROL_FEATURE, &stMnMsgSrvPara, ulLength);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_GetSmsServicePara:Read MO_SMS_CONTROL_FEATURE From Nvim Failed");
        f_stMsgMoSmsCtrlInfo.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    PS_MEM_CPY(&f_stMsgMoSmsCtrlInfo, &stMnMsgSrvPara, sizeof(MN_MSG_NVIM_MO_SMS_CTRL_STRU));

    return;
}


VOS_VOID MN_MSG_GetMoSmsCtrlFlag(
    VOS_UINT8                           *pucMoSmsCtrlFlag
)
{
    *pucMoSmsCtrlFlag = f_stMsgMoSmsCtrlInfo.ucActFlg;
    return;
}


VOS_VOID MN_MSG_UpdateMoSmsCtrlFlag(
    VOS_UINT8                           ucMoSmsCtrlFlag
)
{
    f_stMsgMoSmsCtrlInfo.ucActFlg = ucMoSmsCtrlFlag;
    return;
}


VOS_VOID MN_MGS_UpdateSmsCapability(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_UINT32                          ulNum
)
{
    if (MN_MSG_MEM_STORE_SIM == enSmMemStore)
    {
        f_stMsgEfSmsInfo.ucSmsRealRecNum = (VOS_UINT8)ulNum;
    }
    else if (MN_MSG_MEM_STORE_NV == enSmMemStore)
    {
        f_usMsgNvimSmsCurReNum = (VOS_UINT8)ulNum;
    }
    else
    {
        return;
    }
}


VOS_UINT32 MN_MSG_GetSpecificStatusMoEntity(
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus,
    VOS_BOOL                           *pbBufferEntity,
    VOS_UINT32                         *pulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity
)
{
    VOS_UINT32                          ulTotal;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    *pbBufferEntity = VOS_FALSE;
    *pulIndex = MN_MSG_NO_AVAILABLE_SMS_REC;
    MN_MSG_GetMoEntity(pstMoEntity);
    if (enMoStatus == pstMoEntity->enSmaMoState)
    {
        return MN_ERR_NO_ERROR;
    }

    ulTotal = MN_MSG_GetMoBufferCap();
    for(ulLoop = 0; ulLoop < ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        if (enMoStatus == pstMoBuffer->stMoInfo.enSmaMoState)
        {
            *pbBufferEntity = VOS_TRUE;
            *pulIndex       = ulLoop;
            PS_MEM_CPY(pstMoEntity, &pstMoBuffer->stMoInfo, sizeof(pstMoBuffer->stMoInfo));
            return MN_ERR_NO_ERROR;
        }
    }

    return MN_ERR_UNSPECIFIED;
}


VOS_VOID MN_MSG_CreateMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_ENTITY_STRU              *pstMoEntity,
    VOS_UINT8                           aucEfSmContent[]
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_CreateMoInfo(pstMoEntity);
        return;
    }

    MN_MSG_SaveStoreMsg(ulIndex, pstMoEntity, aucEfSmContent);
    return;
}


VOS_VOID MN_MSG_UpdateSpecificMoEntityStatus(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex,
    MN_MSG_MO_STATE_ENUM_U8             enMoStatus
)
{
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;

    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_UpdateSmaMoState(enMoStatus);
        return;
    }

    pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulIndex;
    pstMoBuffer->stMoInfo.enSmaMoState = enMoStatus;
}


VOS_VOID MN_MSG_DestroySpecificMoEntity(
    VOS_BOOL                            bBufferEntity,
    VOS_UINT32                          ulIndex
)
{
    if (VOS_TRUE != bBufferEntity)
    {
        MN_MSG_DestroyMoInfo();
        return;
    }

    MN_MSG_FreeStoreMsg(ulIndex);

    return;
}


VOS_VOID MN_MSG_InitMoBuffer(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    MN_MSG_STORE_MSG_STRU              *pstMoBuffer = VOS_NULL_PTR;
    NAS_MN_NVIM_TOTAL_MSG_STRU          stTotalMsg;

    if (VOS_NULL_PTR != f_stMsgMoBuffer.pstMoBuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, f_stMsgMoBuffer.pstMoBuffer);
        f_stMsgMoBuffer.ulTotal = 0;
    }

    stTotalMsg.ulTotalMsg = 0;

    ulRet = NV_Read(en_NV_Item_NVIM_SMS_BUFFER_CAPABILITY,
                    &stTotalMsg,
                    sizeof(stTotalMsg));

    f_stMsgMoBuffer.ulTotal = stTotalMsg.ulTotalMsg;

    if (NV_OK != ulRet)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    if (0 == f_stMsgMoBuffer.ulTotal)
    {
        return;
    }

    f_stMsgMoBuffer.pstMoBuffer = (MN_MSG_STORE_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                            sizeof(MN_MSG_STORE_MSG_STRU) * f_stMsgMoBuffer.ulTotal);
    if (VOS_NULL_PTR == f_stMsgMoBuffer.pstMoBuffer)
    {
        f_stMsgMoBuffer.ulTotal = 0;
    }

    for (ulLoop = 0; ulLoop < f_stMsgMoBuffer.ulTotal; ulLoop++)
    {
        pstMoBuffer = f_stMsgMoBuffer.pstMoBuffer + ulLoop;
        PS_MEM_SET(pstMoBuffer, 0, sizeof(MN_MSG_STORE_MSG_STRU));
    }

    return;
}


VOS_UINT32 MN_MSG_GetMoBufferCap(VOS_VOID)
{
    return f_stMsgMoBuffer.ulTotal;
}


VOS_VOID TAF_MSG_SetUsimStatus(
    VOS_UINT8                           ucUsimStatus
)
{
    f_stMsgUsimStatusInfo.ucUsimStatus = ucUsimStatus;
}


VOS_UINT8 TAF_MSG_GetUsimStatus(VOS_VOID)
{
    return f_stMsgUsimStatusInfo.ucUsimStatus;
}


VOS_VOID TAF_MSG_UpdateMtRcvDomain(
    VOS_UINT8                           ucRcvDomain
)
{
    if ( (MN_MSG_RCV_DOMAIN_CS != ucRcvDomain)
      && (MN_MSG_RCV_DOMAIN_PS != ucRcvDomain) )
    {
        f_stMsgMtEntity.enRcvDomain = MN_MSG_RCV_DOMAIN_BUTT;
    }
    else
    {
        f_stMsgMtEntity.enRcvDomain = ucRcvDomain;
    }

    return;
}


MN_MSG_RCV_DOMAIN_ENUM_U8 TAF_MSG_GetMtRcvDomain(VOS_VOID)
{
    return f_stMsgMtEntity.enRcvDomain;
}



/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

