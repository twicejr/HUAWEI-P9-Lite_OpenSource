/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasSmComm.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年03月30日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_SM_COMM_H_
#define _NAS_SM_COMM_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_SM_TRANS_SM_NW_CAUSE(SmCause)       ((SmCause) + SM_TAF_SM_NW_CAUSE_OFFSET)
#define NAS_SM_TRANS_TAF_CAUSE(TafCause)        (VOS_UINT8)((TafCause) - SM_TAF_SM_NW_CAUSE_OFFSET)

#define NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_PTR()   (g_astNasSmGmmErrCodeMapTbl)
#define NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_SIZE()  (sizeof(g_astNasSmGmmErrCodeMapTbl)/sizeof(NAS_SM_GMM_ERR_CODE_MAP_STRU))

/* 获取指定INDEX(取值范围[0, 10])的PDP CONTEXT内容 */
#define NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex) (&g_SmEntity.aPdpCntxtList[ucPdpCtxIndex])
#define NAS_SM_GetPdpTiFlg(ucPdpCtxIndex)       (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucTiFlg)
#define NAS_SM_GetPdpTiValue(ucPdpCtxIndex)     (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucTi)
#define NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex)   (NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex)->ucAddrIndex)
#define NAS_SM_GET_REGISTER_FLG()               (g_SmEntity.ucRegisterFlg)
#define NAS_SM_SET_REGISTER_FLG(ucFlg)          (g_SmEntity.ucRegisterFlg = (ucFlg))

#define NAS_SM_GET_PDP_STATE(index)             (NAS_SM_GetPdpCtxInfoAddr(index)->ucState)

/* 获取指定PDP ADDRESS INDEX的PDP ADDRESS内容 */
#define NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex)  (&g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex])
#define NAS_SM_GetPdpLinkedNsapi(ucAddrIndex)   (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[0] + SM_NSAPI_OFFSET)

/* 设置PDP ADDRESS FLAG标志位(bit) */
#define NAS_SM_SetPdpAddrFlg(ucAddrIndex)       (g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001 << (ucAddrIndex)))

/* 获取指定TI对应的PDP CONTEXT索引 */
#define NAS_SM_GetNsapiFromTiMap(ucTi)          (g_TiMapToNsapi[ucTi])

/* 设置TI与PDP INDEX的映射关系 */
#define NAS_SM_SetNsapiToTiMap(ucTi, ucNsapi)   (g_TiMapToNsapi[ucTi] = (ucNsapi))
#define NAS_SM_ClearNsapiToTiMap(ucTi)          (g_TiMapToNsapi[ucTi] = 0xFF )

/* 获取指定CR对应的PDP CONTEXT索引 */
#define NAS_SM_GetNsapiFromCrMap(ucCr)          (g_CrMapToNsapi[ucCr])

/* 设置CR与PDP INDEX的映关系*/
#define NAS_SM_SetNsapiToCrMap(ucCr, ucNsapi)   (g_CrMapToNsapi[ucCr] = (ucNsapi))
#define NAS_SM_ClearNsapiToCrMap(ucCr)          (g_CrMapToNsapi[ucCr] = 0xFF )


/*****************************************************************************
  3 枚举定义
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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/




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

