/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCall.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月22日
  最近修改   : 2007年8月22日
  功能描述   : CCA模块的外部接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月22日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/
#ifndef  MN_CALL_H
#define  MN_CALL_H

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "TafMmcInterface.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "TafLog.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "TafMmaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/

/* Max number of supported codecs in BC*/
#define MN_CALL_BC_MAX_SPH_VER_NUM          (6)





/*****************************************************************************
  3类型定义
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulStatus;                                       /*是否激活，0不激活，1激活 */
    VOS_UINT32                  ulCustomizeService;                             /*终端说明书是1个byte，为了没有空洞，扩充成4byte，高3byte保留*/
}MN_CALL_NV_ITEM_CUSTOMIZE_SERV_STRU;







/*****************************************************************************
 结构名    : TAF_CALL_FDN_INFO_STRU
 结构说明  : CALL业务模块FDN业务特性参数结构
             ulFdnStatus        (U)SIM的FDN业务使能状态
             stFdnConfig        ME的FDN业务NV配置
1.日    期   : 2012年02月23日
  作    者   : f62575
  修改内容   : 创建
2.日    期   : 2013年6月5日
  作    者   : z00161729
  修改内容   : SVLTE 和usim接口调整修改
*****************************************************************************/
typedef struct
{
    TAF_FDN_CONFIG_STRU                   stFdnConfig;
}TAF_CALL_FDN_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_CALL_BC_STRU
 结构说明  : CALL模块BC参数数据结构解析用，参考协议24008 10.5.4.5

  1.日    期   : 2012年09月18日
    作    者   : f62575
    修改内容   : STK&DCM 项目新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLength;

    NAS_CC_IE_BC_OCTET3_STRU            Octet3;
    NAS_CC_IE_BC_OCTET3A_STRU           Octet3a;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3b;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3c;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3d;
    NAS_CC_IE_BC_OCTET3B_STRU           Octet3e;
    NAS_CC_IE_BC_OCTET4_STRU            Octet4;
    NAS_CC_IE_BC_OCTET5_STRU            Octet5;
    NAS_CC_IE_BC_OCTET5A_STRU           Octet5a;
    NAS_CC_IE_BC_OCTET5B_STRU           Octet5b;
    NAS_CC_IE_BC_OCTET6_STRU            Octet6;
    NAS_CC_IE_BC_OCTET6A_STRU           Octet6a;
    NAS_CC_IE_BC_OCTET6B_STRU           Octet6b;
    NAS_CC_IE_BC_OCTET6C_STRU           Octet6c;
    NAS_CC_IE_BC_OCTET6D_STRU           Octet6d;
    NAS_CC_IE_BC_OCTET6E_STRU           Octet6e;
    NAS_CC_IE_BC_OCTET6F_STRU           Octet6f;
    NAS_CC_IE_BC_OCTET6G_STRU           Octet6g;
    NAS_CC_IE_BC_OCTET7_STRU            Octet7;
}TAF_CALL_BC_STRU;

/*****************************************************************************
 结构名    : TAF_CS_ERR_CODE_MAP_STRU
 结构说明  : TAF与网络原因值的对应结构

  1.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目新增
*****************************************************************************/
typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    MN_CALL_CC_CAUSE_ENUM_U8            enCcCause;

} TAF_CS_ERR_CODE_MAP_STRU;
/*****************************************************************************
  4 宏定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_CALL_Init
 功能描述  : 执行CCA模块的初始化，包括所有呼叫状态的复位和全局资源的初始化
             TAF应该在系统启动时和Reset时调用该接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_Init(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcAppReqMsg
 功能描述  : 处理来自应用层的请求消息
             该函数根据请求的类型将消息分发到相应的请求处理函数去处理
 输入参数  : pstMsg - 应用层调用TAF API时由API函数打包发出的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcAppReqMsg(
    const VOS_VOID                      *pstMsg
);


/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccPrimMsg
 功能描述  : 处理来自CC的MNCC原语消息
             该函数根据原语名将消息分发到相应的MNCC原语处理函数去处理
 输入参数  : pstMsg - 来自CC的MNCC原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccPrimMsg(
    const VOS_VOID                      *pMsg
);

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
/* 删除该函数 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, end */

/*****************************************************************************
 函 数 名  : MN_CALL_ProcVCMsg
 功能描述  : 处理来自VC模块的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcVCMsg (VOS_VOID * pstMsg);

/*****************************************************************************
 函 数 名  : MN_CALL_LineInfo
 功能描述  : 收到卡在位信息后从NVIM中获取当前选择的线路
 输入参数  : enUsimStatus:当前卡是否在位
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月25日
    作    者   : z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_LineInfo(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
);

VOS_VOID MN_CALL_ProcOmMsg(
    VOS_VOID                            *pstMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_ProcCstCcPrimitive
 功能描述  : 处理CST模块发来的消息原语
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstCallPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_ProcRabmCallPrimitive
 功能描述  : 处理来自Rabm的消息。
 输入参数  : pMsg  - 定时器超时消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallPrimitive(
    const VOS_VOID                      *pMsg
);

/*****************************************************************************
 函 数 名  : MN_CALL_DispatchUsimMsg
 功能描述  : 处理从USIM过来的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_DispatchUsimMsg(struct MsgCB * pstMsg);

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 函 数 名  : MN_CALL_ProcUsimFdnInd(UT工程使用)
 功能描述  : USIM过来的FDN状态上报消息更新本地FDN状态
 输入参数  : pstFdnStatusInd - 收到的USIM过来的FDN状态上报消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_VOID MN_CALL_ProcUsimFdnInd(struct MsgCB * pstMsg);
#endif


/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, end */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */


/*****************************************************************************
 函 数 名  : MN_CALL_SupportMoCallType
 功能描述  : 获取UE对指定呼叫类型的支持状态
 输入参数  : MN_CALL_TYPE_ENUM_U8                enCallType  呼叫类型
 输出参数  : VOS_BOOL                           *pSupported  UE是否支持指定的呼叫类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_BOOL                           *pSupported
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID MN_CALL_CsCallErrRecord(
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);


VOS_VOID MN_CALL_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen
);
VOS_VOID MN_CALL_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
);

VOS_VOID MN_CALL_CsCallDiscInfoRecord(
    MN_CALL_ID_T                            ucCallId,
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
);

#endif

extern VOS_VOID MN_CALL_ReadNvimInfo(VOS_VOID);

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
VOS_VOID TAF_CALL_ProcTafMsg (
    const VOS_VOID                      *pMsg
);

VOS_VOID TAF_CALL_ProcMmaMsg (
    const VOS_VOID                      *pMsg
);
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

TAF_VC_TTYMODE_ENUM_UINT8 TAF_CALL_GetTTYMode(VOS_VOID);
VOS_BOOL TAF_CALL_IsSupportTTYMode(VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_H */


