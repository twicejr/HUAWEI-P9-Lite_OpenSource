/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPublic.h
  Description     : NasMmPublic.c header file
  History           :
     1.luojian 00107747      2008-10-9  Draft Enact
     2.zhengjunyan 00148421  2011-05-28 文件名由 NasMmPublic.h修改为NasLmmPublic.h
******************************************************************************/

#ifndef __NASLMMPUBLIC_H__
#define __NASLMMPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmCore.h"
#include    "TafMtcApi.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_LMM_RIGHT_SHIFT_HALF_BYTE       4       /* 右移半个字节长度 */

#define NAS_LMM_HEX_DIGIT_F                 0x0F    /* 16进制F */

#define NAS_LMM_DEC_DIGIT_0                 0       /* 10进制0 */
#define NAS_LMM_DEC_DIGIT_1                 1       /* 10进制1 */
#define NAS_LMM_DEC_DIGIT_2                 2       /* 10进制2 */
#define NAS_LMM_DEC_DIGIT_3                 3       /* 10进制3 */
#define NAS_LMM_DEC_DIGIT_4                 4       /* 10进制4 */
#define NAS_LMM_DEC_DIGIT_5                 5       /* 10进制5 */
#define NAS_LMM_DEC_DIGIT_6                 6       /* 10进制6 */
#define NAS_LMM_DEC_DIGIT_7                 7       /* 10进制7 */
#define NAS_LMM_DEC_DIGIT_8                 8       /* 10进制8 */
#define NAS_LMM_DEC_DIGIT_9                 9       /* 10进制9 */

#define NAS_EMM_SECOND_TRANSFER_MILLISECOND    1000
#define NAS_EMM_MINUTE_TRANSFER_MILLISECOND    60000

#define NAS_LMM_LOW_HALF_BYTE_MASK          0xF0    /* 低半字节屏蔽 */
#define NAS_LMM_HIGH_HALF_BYTE_MASK         0x0F    /* 高半字节屏蔽 */

#define NAS_LMM_MIN(n1,n2)                  (((n1)>(n2))?(n2):(n1))


#define NAS_EMMC_PLMNID_INVALID              VOS_TRUE
#define NAS_EMMC_PLMNID_VALID                VOS_FALSE
#define NAS_EMM_BUFFER_MSG_COUNT            16          /*根据QUE的大小确定*/

#define NAS_LMM_HEX_DIGIT_FF                 0xff

#define NAS_LMM_NVIM_ALG_VALID_IE            0x03

#define NAS_LMM_MEM_CMP_EQUAL                0
#define NAS_LMM_NULL                         0


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*******************************************************************************
 枚举名    : NAS_LMM_ERROR_CODE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MM错误原因值定义.每个MM错误原因值共32bit, 其中bit31-16表示错误原
             因大类, bit15-0表示错误原因小类.

*******************************************************************************/
enum NAS_LMM_ERROR_CODE_ENUM
{
    NAS_LMM_SUCC                         = 0x00000000,
    NAS_LMM_FAIL                                     ,

    /*======== FSM专用，状态机不处理该消息 ========*/
    NAS_LMM_MSG_DISCARD                              ,       /* 丢弃该消息，即该消息不被该当前状态处理，也不缓存， */
    NAS_LMM_MSG_HANDLED                              ,       /* 该消息已被当前状态处理，但不是缓存 */

    NAS_LMM_STORE_HIGH_PRIO_MSG                      ,
    NAS_LMM_STORE_MID_PRIO_MSG                       ,       /*暂时保留*/
    NAS_LMM_STORE_LOW_PRIO_MSG                       ,       /*暂时保留*/

    NAS_EMMC_STORE_HIGH_PRIO_MSG                      ,
    NAS_EMMC_STORE_MID_PRIO_MSG                       ,       /*暂时保留*/
    NAS_EMMC_STORE_LOW_PRIO_MSG                       ,       /*暂时保留*/


    NAS_LMM_NOT_TRAVEL_BUFFER_MSG                    ,       /* 不处理缓存队列 */
    NAS_LMM_TRAVEL_BUFFER_MSG                        ,       /* 需要继续处理BUF里的缓存消息 */

    NAS_LMM_ERR_CODE_PARA_INVALID                    ,       /*消息内容无效*/
    NAS_LMM_ERR_CODE_PTR_NULL                        ,       /* 空指针 */
    NAS_LMM_ERR_CODE_ARRAY_OVERFLOW                  ,       /* 数组越界 */

    NAS_LMM_STATE_IS_STABLE                          ,       /*  状态机处于稳态 */
    NAS_LMM_STATE_IS_UNSTABLE                        ,       /*  状态机处于非稳态 */
    NAS_LMM_STATE_IS_TRANSIENT                       ,       /*  状态机处于建链过程中*/

    /*================ PUBM-TIMER =================*/
    NAS_LMM_ERR_CODE_GET_STATE_TIMER_CTRL_ADDR_FAIL  ,       /* 获取状态定时器控制块地址失败 */
    NAS_LMM_ERR_CODE_GET_PTL_TIMER_CTRL_ADDR_FAIL    ,       /* 获取协议定时器控制块地址失败 */
    NAS_LMM_ERR_CODE_PTL_TIMER_EXCEED_MAX_BOUND      ,       /* 协议定时器超过最大时长界限   */
    NAS_LMM_ERR_CODE_RESUME_NOT_SUSPEND_STATE_TIMER  ,       /* 恢复没有被挂起的状态定时器   */

    /*================ ATTACH 模块 ================*/
    /*================ DETACH 模块 ================*/
    /*================ TAU 模块 ===================*/
    /*================ SERVICE 模块 ===============*/
    /*================ PUB 模块 ===================*/
    NAS_LMM_MSG_CAN_BE_HANDLED_BY_PRE_STATE          ,       /* NAS_EMM_JudgeFirstBufMsgCanBeProc中使用,
                                                               当前状态可以处理收到的消息 */

    NAS_LMM_ERR_CODE_HARD_USIM                       ,

    NAS_LMM_ERR_CODE_FAIL                            ,       /* 不分类的错误 */

    NAS_LMM_ERR_CODE_BUTT
};
typedef VOS_UINT32 NAS_LMM_ERROR_CODE_ENUM_UINT32;
typedef NAS_LMM_ERROR_CODE_ENUM_UINT32   NAS_EMM_ERROR_CODE_ENUM_UINT32;
typedef NAS_LMM_ERROR_CODE_ENUM_UINT32   NAS_EMMC_ERROR_CODE_ENUM_UINT32;


enum NAS_LMM_MATCH_RESULT_ENUM
{
    NAS_LMM_MATCH_FAIL                      = 0,
    NAS_LMM_MATCH_SUCCESS                   = 1,
    NAS_LMM_MATCH_PTR_NULL                  = 2,
    NAS_LMM_MATCH_RESULT_BUTT
};
typedef VOS_UINT32  NAS_LMM_MATCH_RESULT_ENUM_UINT32;


enum NAS_LMM_IE_FORMAT_ENUM
{
    NAS_LMM_IE_FORMAT_V                 = 0x00,
    NAS_LMM_IE_FORMAT_LV                = 0x01,
    NAS_LMM_IE_FORMAT_TLV               = 0x02,
    NAS_LMM_IE_FORMAT_LV_E              = 0x03,

    NAS_LMM_IE_FORMAT_BUTT
};
typedef VOS_UINT8 NAS_LMM_IE_FORMAT_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_LMM_AddPlmnInPlmnList
       (
           const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
           NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_AddTaInTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           NAS_MM_TA_LIST_STRU                 *pstTaList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_ClearPlmnList(NAS_MM_PLMN_LIST_STRU  *pstPlmnList);
extern VOS_VOID  NAS_LMM_ClearTaList(NAS_MM_FORB_TA_LIST_STRU  *pstTaList);
extern VOS_VOID    NAS_LMM_DeletePlmnFromPlmnList
       (
           const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
           NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_DeleteTaFromTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           NAS_MM_TA_LIST_STRU                 *pstTaList,
           VOS_UINT32                          ulListNumMax
       );
extern VOS_VOID    NAS_LMM_GetMccFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT8                           *pucMcc1,
           VOS_UINT8                           *pucMcc2,
           VOS_UINT8                           *pucMcc3
       );
extern VOS_VOID    NAS_LMM_GetMccMncFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT32                          *pulMCC,
           VOS_UINT32                          *pulMNC
       );
extern VOS_VOID    NAS_LMM_GetMncFromPlmn
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           VOS_UINT8                           *pucMnc1,
           VOS_UINT8                           *pucMnc2,
           VOS_UINT8                           *pucMnc3
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_HplmnMatch
       (
           const   NAS_MM_PLMN_ID_STRU         *pstHplmn,
           const   NAS_MM_PLMN_ID_STRU         *pstBcchPlmn
       );
extern  VOS_VOID    NAS_LMM_PlmnCpy
        (
            NAS_MM_PLMN_ID_STRU                *pstDestPlmn,
            const   NAS_MM_PLMN_ID_STRU        *pstOrgPlmn
        );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchPlmnList
       (
           const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
           const NAS_MM_PLMN_LIST_STRU         *pstPlmnList
       );
extern VOS_UINT32 NAS_LMM_PlmnIsUndef(const NAS_MM_PLMN_ID_STRU *pstPlmnId);

extern VOS_UINT32 NAS_LMM_TacIsInvalid(const NAS_MM_TAC_STRU *pstTac);

extern VOS_UINT32 NAS_LMM_PlmnIsUnexist(const NAS_MM_PLMN_ID_STRU *pstPlmnId);
extern VOS_VOID    NAS_LMM_PlmnListCpy
       (
           NAS_MM_PLMN_LIST_STRU               *pstDestPlmnList,
           const   NAS_MM_PLMN_LIST_STRU       *pstOrgPlmnList
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnMatch
       (
           const NAS_MM_PLMN_ID_STRU           *pstLocalPlmn,
           const NAS_MM_PLMN_ID_STRU           *pstBcchPlmn
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TacMatch
       (
           const   NAS_MM_TAC_STRU             *pstTac1,
           const   NAS_MM_TAC_STRU             *pstTac2
       );
extern VOS_VOID NAS_LMM_TaCpy
       (
           NAS_MM_TA_STRU                      *pstDestTa,
           const   NAS_MM_TA_STRU              *pstOrgTa
       );
extern NAS_LMM_ERROR_CODE_ENUM_UINT32 NAS_LMM_TaIncrease
       (
           NAS_MM_TAC_STRU                     *pstTac
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatch
       (
           const   NAS_MM_TA_STRU              *pstTa1,
           const   NAS_MM_TA_STRU              *pstTa2
       );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTaList
       (
           const   NAS_MM_TA_STRU              *pstTa,
           const   NAS_MM_TA_LIST_STRU         *pstTaList
       );
extern VOS_VOID    NAS_LMM_UndefPlmn
       (
           NAS_MM_PLMN_ID_STRU                 *pstPlmnId
       );

extern VOS_VOID    NAS_LMM_UndefTac
(
    NAS_MM_TAC_STRU                 *pstTac
);
extern VOS_UINT32    NAS_LMM_TacIsUnexist
(
    const NAS_MM_TAC_STRU                 *pstTac
);
extern VOS_UINT32    NAS_LMM_CheckPlmnIsInvalid
(
    const NAS_MM_PLMN_ID_STRU                 *pstPlmnId
);
extern VOS_UINT32    NAS_LMM_CheckMccIsValid
(
    VOS_UINT8   ucMcc1,
    VOS_UINT8   ucMcc2,
    VOS_UINT8   ucMcc3
);
extern VOS_UINT32    NAS_LMM_CheckMncIsValid
(
    VOS_UINT8   ucMnc1,
    VOS_UINT8   ucMnc2,
    VOS_UINT8   ucMnc3
);

extern VOS_UINT32  NAS_LMM_CheckWhetherAnyByteIsFF( const VOS_UINT8 *pucSimRecord,
                                                           const VOS_UINT32 ulIndex,
                                                           const VOS_UINT32 ulLen);
extern VOS_UINT32  NAS_LMM_CheckWhetherAllBytesAreFF(  const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen );
extern VOS_UINT32  NAS_LMM_CheckSimRecordHeadValid( const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen );
extern VOS_VOID NAS_LMM_SetArrayAllBytesFF( VOS_UINT8 *pucArray,
                                                     const VOS_UINT32 ulLen );
extern VOS_UINT32  NAS_LMM_CheckSecuAlgValid( VOS_UINT8 ucSecuAlg);

extern VOS_UINT32  NAS_LMM_CheckModifyT3402DefaultValue( VOS_VOID);
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchHplmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
);
extern VOS_UINT32  NAS_LMM_GetPlmnExactlyComparaFlg( VOS_VOID );
extern NAS_LMM_MATCH_RESULT_ENUM_UINT32  NAS_LMM_ExactlyPlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
);
extern VOS_VOID    NAS_LMM_UndefCsgId
(
    VOS_UINT32             *pulCsgId
);
#if(FEATURE_ON == FEATURE_CSG)

extern VOS_UINT32 NAS_LMM_IsCsgCampOn( VOS_VOID );


extern NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList
(
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstAllowedCsgList,
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstOperatorCsgList
);
extern VOS_UINT32 NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId( VOS_VOID );
#endif
extern VOS_VOID  NAS_LMM_ConvertGuPlmnToLteFormat
(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MM_PLMN_ID_STRU                *pstLNasPlmn
);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPublic.h */
