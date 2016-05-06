/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndInternal.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给mmc的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_INTERNAL_H
#define _NAS_MMC_SND_INTERNAL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMLAYER_INTERNAL_MSG_ID_ENUM
 结构说明  : 内部消息ID
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : MMC内部消息ID枚举
*****************************************************************************/
enum NAS_MMC_INTERNAL_MSG_ID_ENUM
{
    /* MMC收到的内部消息ID,MMC内部收到的消息ID从0x000到0x199 */
    MMCMMC_QUIT_L2FSM_REQ                       ,
    MMCMMC_INTER_SRCH_NEXT_PLMN_REQ             ,                               /* 自动或手动内部搜网请求搜索下一个网络 */
    MMCMMC_INTER_RESTART_SRCH_PLMN_REQ          ,                               /* 内部搜网请求 ,重新初始化，发出搜网请求 */
    MMCMMC_INTER_LIST_PLMN_REQ                  ,

    MMCMMC_SWITCH_ON_RSLT_CNF                ,
    MMCMMC_POWER_OFF_RSLT_CNF               ,
    MMCMMC_SRCH_PLMN_RSLT_CNF               ,
    MMCMMC_SUSPEND_RSLT_CNF                 ,

    MMCMMC_INTERNAL_MSG_ID_BUTT
};
typedef VOS_UINT32 NAS_MMC_INTERNAL_MSG_ID_ENUM_U32;

/*****************************************************************************
 枚举名    : NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32
 结构说明  : plmnsrch状态机产生的结果
*****************************************************************************/
enum NAS_MMC_PLMNSRCH_RESULT_ENUM
{
    NAS_MMC_PLMN_SRCH_SUCCESS           = 0,
    NAS_MMC_PLMN_SRCH_ALL_FAIL          = 1,
    NAS_MMC_PLMN_SRCH_QUIT              = 2,
    NAS_MMC_PLMN_SRCH_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_SUSPEND_RSLT_ENUM_UINT32
 结构说明  : SUSPEND状态机产生的结果
*****************************************************************************/
enum NAS_MMC_SUSPEND_RSLT_ENUM
{
    NAS_MMC_SUSPEND_SUCCESS            = 0,
    NAS_MMC_SUSPEND_FAIL               = 1,
    NAS_MMC_SUSPEND_QUIT               = 2,
    NAS_MMC_SUSPEND_BUTT
};
typedef VOS_UINT32 NAS_MMC_SUSPEND_RSLT_ENUM_UINT32;

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
 结构名    : NAS_MMC_QUIT_FSM_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MMC发送退出消息的结构

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 退出消息的结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulTopState;
    VOS_UINT32                          enFsmId;
}NAS_MMC_QUIT_FSM_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_INTER_PLMN_SRCH_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC->MMC,内部搜网类型标识

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 内部搜网消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MMC_PLMN_SRCH_INFO_STRU         stPlmnSrchInfo;
}NAS_MMC_INTER_PLMN_SRCH_REQ_STRU;

/*****************************************************************************
 结构名称: NAS_MMC_SWITCHON_RLST_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC->MMC,开机结果

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 开机消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                            MsgHeader;
    VOS_UINT32                                 ulResult;
} NAS_MMC_SWITCHON_RLST_STRU;


/*****************************************************************************
 结构名称: NAS_MMCMMC_PLMNSRCH_RLST_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC->MMC,搜网结果

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 开机消息的结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32 enResult;
} NAS_MMCMMC_PLMNSRCH_RLST_STRU;

/*****************************************************************************
 结构名称: NAS_MMCMMC_SUSPEND_RSLT_STRU
 协议表格:
 ASN.1 描述:
 结构说明:  MMC->MMC,挂起结果

  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 开机消息的结构
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;

    /*SUSPEND完成的结果 */
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32    enSuspendRslt;
}NAS_MMCMMC_SUSPEND_RSLT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    VOS_UINT32                          ulRslt;
}NAS_MMCMMC_POWEROFF_RSLT_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_MMC_SndQuitFsmMsg( VOS_VOID );

VOS_VOID  NAS_MMC_BuildInterPlmnSrchReq(
    VOS_UINT32                          ulMsgName,
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo,
    NAS_MMC_INTER_PLMN_SRCH_REQ_STRU   *pstPlmnSrchReq
);

VOS_UINT32  NAS_MMC_SndInterSrchNextPlmnReq(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);
VOS_UINT32  NAS_MMC_SndInterRestartPlmnSrchReq(
    NAS_MMC_PLMN_SRCH_INFO_STRU        *pstPlmnSrchInfo
);

VOS_VOID NAS_MMC_SndSwitchOnRlst(VOS_UINT32 ulResult);


VOS_VOID NAS_MMC_SndPlmnSrchRlst(
    NAS_MMC_PLMNSRCH_RESULT_ENUM_UINT32 enResult
);

VOS_VOID NAS_MMC_SndSuspendRslt(
    NAS_MMC_SUSPEND_RSLT_ENUM_UINT32    enSuspendRslt
);

VOS_VOID NAS_MMC_SndPowerOffRslt(VOS_VOID);

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

