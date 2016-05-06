/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcUsim.h
  版 本 号   : 初稿
  作    者   : luokaihui / 00167671
  生成日期   : 2011年5月10日
  最近修改   :
  功能描述   : NasMmcProcUsim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月10日
    作    者   : luokaihui / 00167671
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NASMMCPROCUSIM_H__
#define __NASMMCPROCUSIM_H__


#include "NasMmlCtx.h"
#include "UsimPsInterface.h"
#include "TafAppMma.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* STK功能 Network Search Mode Change Event 相关宏定义 */
#define MMC_STK_NET_SCH_MODE_MANUAL                         (0)
#define MMC_STK_NET_SCH_MODE_AUTO                           (1)

#define NAS_MMC_USIM_PSLOCI_LAC_POSITION_BEG                (10)                  /* 消息中被删除的RAI中LAC首字节的取值       */
#define NAS_MMC_USIM_PSLOCI_LAC_POSITION_END                (11)

#define NAS_MMC_USIM_FILE_CONTENT_INVALID                   (0xFF)

#define NAS_MMC_PERI_HPLMN_ATTEMP_STEP_SIZE                 (6)                 /* 周期HPLMN搜索，以6分钟位单位增加 */
#define NAS_MMC_MAX_PERI_HPLMN_ATTEMP_TIME_LEN              (480)               /* 周期HPLMN搜索，最长8小时 */

#define NAS_MMC_MNC_LENGTH_INDICATOR_POSITION               (4)                 /* 指示MNC长度的字节在EF文件中的位置 */
#define NAS_MMC_MNC_LENGTH_TWO_BYTES_IN_IMSI                (2)                 /* MNC在IMSI中的长度是2 */
#define NAS_MMC_MNC_LENGTH_THREE_BYTES_IN_IMSI              (3)                 /* MNC在IMSI中的长度是3 */

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
    USIMM_CMDHEADER_CNF_STRU            stCmdResult;
    USIMM_FILEPATH_INFO_STRU            stFilePath;
    VOS_UINT16                          usRsv;
    VOS_UINT16                          usEfLen;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucSW1;
    VOS_UINT8                           ucSW2;
    VOS_UINT8                           aucEf[255];
}PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU;


/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
typedef struct
{
    VOS_UINT16                          usEfNum;        /* 更新的文件的个数 */
    VOS_UINT8                           aucRsv[2];      /* 预留对齐 */
    USIM_REFRESH_FILE_STRU              astRefreshFile[USIMM_MAX_REFRESH_FILE_NUM];
}NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU;
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_MMC_ConverPlmnInfoFromSim(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRat
);
VOS_VOID  NAS_MMC_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
);
VOS_VOID  NAS_MMC_ConvertNasPlmnToSimFormat(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MML_SIM_FORMAT_PLMN_ID         *pstSimPlmn
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_CKIK_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_CS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMNPI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_EHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_FORBIDDEN_PLMN_LIST_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);
VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_PERI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_HPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_LRPLMNSI_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_MNC_LENGTH_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_OPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_KEY_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU           *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_PS_LOC_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_UPLMN_SEL_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_RcvAgentUsimReadFileCnf_ACTINGHPLMN_FILE_ID(
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU          *pstMsg
);

VOS_VOID NAS_MMC_SaveOperatorPlmnInfo(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID   NAS_MMC_SndUsimReadFileReq( VOS_VOID );

VOS_VOID NAS_MMC_SndUsimUpdateForbPlmnReq(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateCsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucCsSecutityInfo
);

VOS_VOID  NAS_MMC_UpdateLaiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

VOS_VOID  NAS_MMC_UpdatePsSecutityInfoFromUsimFile(
    VOS_UINT8                          *pucPsSecutityInfo
);

VOS_VOID  NAS_MMC_UpdatePtmsiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdatePtmsiSignatureFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateRaiFormPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateSimInfoFromCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateSimInfoFromPsLociFile(
    VOS_UINT8                          *pucPsLociFileContent
);

VOS_VOID  NAS_MMC_UpdateTmsiFormCsLociFile(
    VOS_UINT8                          *pucCsLociFileContent
);

TAF_PH_PLMN_SEL_MODE NAS_MMC_ConvertSrchModeToStkSrchMode(
   VOS_UINT8                            ucReselMode
);


VOS_VOID NAS_MMC_SndStkSearchModeChgEvt(
    VOS_UINT8                           ucReselMode
);

VOS_UINT32 NAS_MMC_IsNeedSndStkSearchModeChgEvt(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateOPlmnInfoFromNvim(
    VOS_UINT8                          *pucOPlmnData,
    VOS_UINT16                          usOPlmnNum
);

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, Begin */
VOS_UINT8  NAS_MMC_GetUsimAllRefreshFileNumber(VOS_VOID);
VOS_UINT16  NAS_MMC_GetUsimAllRefreshFileId(VOS_UINT8 ucIndex);

VOS_VOID NAS_MMC_BuildRefreshFileList(
    USIMM_STKREFRESH_IND_STRU                   *pstUsimRefreshInd,
    NAS_MMC_USIMM_REFRESH_FILE_CONTENT_STRU     *pstRefreshFile
);

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */


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

#endif

