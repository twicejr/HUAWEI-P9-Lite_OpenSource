/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : NasCommDef.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2006年8月25日
  最近修改   :
  功能描述   : NAS公共数据定义和公共接口声明
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月28日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_COMM_DEFS_H__
#define __NAS_COMM_DEFS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"


#pragma pack(4)


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/* 新增IMSI长度定义 */

#define   NAS_MAX_IMSI_LENGTH                       (9)

/* 新增IE的偏移 */

#define IE_OFFSET(s,m)                              ((VOS_UINT32)((VOS_VOID *)(&(((s *)0)->m))))

/* network capability能力 */
#define NAS_GMM_NETWORK_EMM_COMB_CAPABILITY_POS     (0x20)
#define NAS_GMM_NETWORK_EMM_ISR_POS                 (0x10)
#define NAS_GMM_NETWORK_EMM_EPC_CAPABILITY_POS      (0x08)


#define NAS_SET_GMM_NETWORK_EMM_COMB_CAPABILITY(ucFo, ucCapabFlag) ((ucFo) |= (ucCapabFlag))
#define NAS_SET_GMM_NETWORK_EMM_ISR_SUPPORT(ucFo, ucCapabFlag)     ((ucFo) |= (ucCapabFlag))
#define NAS_SET_GMM_NETWORK_EMM_EPC_CAPABILITY(ucFo, ucCapabFlag)  ((ucFo) |= (ucCapabFlag))




/*****************************************************************************
  3 类型定义
*****************************************************************************/
/* NAS协议相关的错误码定义。参考3GPP 24.008 - 8 */
enum NAS_PROTOCOL_ERR_ENUM
{
    NAS_PROT_ERR_NO_ERROR,
    NAS_PROT_ERR_MSG_TOO_SHORT,
    NAS_PROT_ERR_TI_UNKNOWN,
    NAS_PROT_ERR_MSG_TYPE_UNKNOWN,
    NAS_PROT_ERR_INCOMPATIBLE_STATE,
    NAS_PROT_ERR_MANDATORY_IE_ERR,
    NAS_PROT_ERR_NON_SEM_IE_ERR,
    NAS_PROT_ERR_OPTIONAL_IE_ERR,
    NAS_PROT_ERR_CONDITIONAL_IE_ERR,
    NAS_PROT_ERR_INCORRECT_CONTENT,
    NAS_PROT_ERR_INCOMPATIBLE_DESTINATION,
    NAS_PROT_ERR_NOT_SPECIFIED
};
typedef VOS_UINT8 NAS_PROTOCOL_ERR_ENUM_U8;


/*****************************************************************************
 枚举名    : NAS_MM_COM_SERVICE_STATUS_ENUM
 结构说明  : MM服务状态
*****************************************************************************/
enum NAS_MM_COM_SERVICE_STATUS_ENUM
{
    MM_COM_SRVST_NORMAL_SERVICE         = 0 ,
    MM_COM_SRVST_LIMITED_SERVICE,
    MM_COM_SRVST_LIMITED_SERVICE_REGION,
    MM_COM_SRVST_NO_IMSI,
    MM_COM_SRVST_NO_SERVICE,
    MM_COM_SRVST_NO_CHANGE,
    MM_COM_SRVST_DEEP_SLEEP,
    MM_COM_SRVST_BUTT
};
typedef VOS_UINT8   NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MM_COM_SERVICE_STATUS_ENUM
 结构说明  : MM服务域
*****************************************************************************/
enum NAS_MM_COM_SERVICE_DOMAIN_ENUM
{
    MM_COM_SRVDOMAIN_NO_DOMAIN          = 0 ,
    MM_COM_SRVDOMAIN_CS,
    MM_COM_SRVDOMAIN_PS,
    MM_COM_SRVDOMAIN_CS_PS,
    MM_COM_SRVDOMAIN_NO_CHANGE,
    MM_COM_SRVDOMAIN_Not_Reg_PLMN_Searching,
    MM_COM_SRVDOMAIN_BUTT
};
typedef VOS_UINT8   NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8;



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

#endif /* __NAS_COMM_DEFS_H__ */

