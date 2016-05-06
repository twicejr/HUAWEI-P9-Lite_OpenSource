/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : EdgeInterface.h
  Version     : V100R001
  Date        : 2007-01-13
  Description :
  History     :
  1. Date:2007-01-13
     Author: z47725
     Modification:Create
*******************************************************************************/

#ifndef __EDGEINTERFACE_H__
#define __EDGEINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define EDGE_CODE_SCHEME_MCS_MASK           0x1000      /* EGPRS编码方式掩码 */
#define EDGE_UL_TS_MAX_NUM                  4           /* 上行最大时隙能力 */
#define EDGE_DL_TS_MAX_NUM                  5           /* 下行最大时隙能力 */
#define GPRS_WITHOUT_START_TIME             0x80000000  /* START TIME为立即生效的宏 */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*========================*/ /*定义编码方式的枚举*/
enum EDGE_CODE_SCHEME_ENUM
{
    EDGE_CODE_SCHEME_CS_1                   = 0x0000,
    EDGE_CODE_SCHEME_CS_2                   = 0x0001,
    EDGE_CODE_SCHEME_CS_3                   = 0x0002,
    EDGE_CODE_SCHEME_CS_4                   = 0x0003,
    EDGE_CODE_SCHEME_MCS_1                  = 0x1000,
    EDGE_CODE_SCHEME_MCS_2                  = 0x1001,
    EDGE_CODE_SCHEME_MCS_3                  = 0x1002,
    EDGE_CODE_SCHEME_MCS_4                  = 0x1003,
    EDGE_CODE_SCHEME_MCS_5                  = 0x1004,
    EDGE_CODE_SCHEME_MCS_6                  = 0x1005,
    EDGE_CODE_SCHEME_MCS_7                  = 0x1006,
    EDGE_CODE_SCHEME_MCS_8                  = 0x1007,
    EDGE_CODE_SCHEME_MCS_9                  = 0x1008,
    EDGE_CODE_SCHEME_MCS_5_7                = 0x1009,
    EDGE_CODE_SCHEME_MCS_6_9                = 0x100a,
    EDGE_CODE_SCHEME_BUTT
};

typedef VOS_UINT16 EDGE_CODE_SCHEME_ENUM_UINT16;

/*================*/ /* RRBP消息块格式类型枚举 */
enum PHY_BURST_TPYE_ENUM
{
    PHY_ACCESS_BURST_8_BIT                  = 0,
    PHY_ACCESS_BURST_11_BIT                 = 1,
    PHY_NORMAL_BURST_23_BYTE                = 2
};

typedef VOS_UINT16 PHY_BURST_TPYE_ENUM_UINT16;

/*================*/ /* RRBP消息回复类型的枚举 */
enum GRR_RRBP_CNF_ENUM
{
    GRR_RRBP_NO_CNF                         = 0,
    GRR_RRBP_UL_CNF                         = 1,
    GRR_RRBP_DL_CNF                         = 2
};

typedef VOS_UINT16 GRR_RRBP_CNF_ENUM_UINT16;

/*========================*/ /* GMAC模式的枚举 */
enum GMAC_MODE_ENUM
{
    GMAC_MODE_SINGLE_BLOCK_ALLOC            = 0,
    GMAC_MODE_MULTI_BLOCK_ALLOC,
    GMAC_MODE_DYNAMIC_ALLOC,                        /* _H2ASN_MsgChoice  MPHP_DYNAMIC_ALLOCATION_ST*/
    GMAC_MODE_EXT_DYNAMIC_ALLOC,                    /* _H2ASN_MsgChoice  MPHP_DYNAMIC_ALLOCATION_ST*/
    GMAC_MODE_FIXED_ALLOC,                          /* _H2ASN_MsgChoice  MPHP_FIXED_ALLOCATION_ST*/
    GMAC_MODE_BUTT
};

typedef VOS_UINT16 GMAC_MODE_ENUM_UINT16;

/*========================*/ /* EDGE回复结果的枚举 */
enum EDGE_CNF_RESULT_ENUM
{
   EDGE_CNF_RESULT_SUCCESS                  = 0,
   EDGE_CNF_RESULT_FAIL
};

typedef VOS_UINT16 EDGE_CNF_RESULT_ENUM_UINT16;

/*========================*/ /* EDGE是、否的枚举 */
enum EDGE_YES_OR_NO_ENUM
{
   EDGE_YES                                 = 1,
   EDGE_NO                                  = 0
};

typedef VOS_UINT16 EDGE_YES_OR_NO_ENUM_UINT16;

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
#pragma pack(4)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* EdgeInterface.h */


