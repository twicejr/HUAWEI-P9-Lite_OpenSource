/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : NasMsgEncDec.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年8月28日
  最近修改   :
  功能描述   : NAS消息编解码的通用接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年8月28日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

******************************************************************************/
#ifndef __NAS_MSG_ENC_DEC_H__
#define __NAS_MSG_ENC_DEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasCommDef.h"


#pragma pack(4)

/*****************************************************************************
  2 类型定义
*****************************************************************************/
/* IE的格式 */
enum NAS_IE_FORMAT
{                                                                               /*  Bit 3 2 1 */
    NAS_IE_FORMAT_T                                         = 1,                /*      0 0 1 */
    NAS_IE_FORMAT_V                                         = 4,                /*      1 0 0 */
    NAS_IE_FORMAT_LV                                        = 6,                /*      1 1 0 */
    NAS_IE_FORMAT_TV                                        = 5,                /*      1 0 1 */
    NAS_IE_FORMAT_TLV                                       = 7,                /*      1 1 1 */

    NAS_IE_FORMAT_L                                         = 2                 /*      0 1 0 */
};
typedef VOS_UINT8 NAS_IE_FORMAT_ENUM_U8;

/* IE的提供形式 */
enum NAS_IE_PRESENCE
{
    NAS_IE_PRESENCE_M                                       = 0,                /* Mandatory  */
    NAS_IE_PRESENCE_O                                       = 1,                /* Optional   */
    NAS_IE_PRESENCE_C                                       = 2                 /* Condition  */
};
typedef VOS_UINT8 NAS_IE_PRESENCE_ENUM_U8;


/* IE Lookup Table Definition */
typedef struct
{
    VOS_UINT8                           ucIEI;
    VOS_UINT8                           ucIEI_Msk;
    VOS_UINT8                           ucMinLen;
    VOS_UINT8                           ucMaxLen;
    VOS_UINT32                          ulExtFlag;
}NAS_IE_TBL_STRU;

/* Msg Lookup Table Definition */
typedef struct
{
    NAS_IE_FORMAT_ENUM_U8               enIeFormat;
    NAS_IE_PRESENCE_ENUM_U8             enIePresence;
    VOS_UINT16                          usRelateIe;
    VOS_UINT32                          ulIePos;
    const NAS_IE_TBL_STRU               *pstIeTbl;
}NAS_MSG_TBL_STRU;

/* Msg Entry Definition */
typedef struct
{
    VOS_UINT32                           ulEncodeIeNum;
    NAS_MSG_TBL_STRU                    *pstEncodeMsgTbl;
    VOS_UINT32                           ulDecodeIeNum;
    NAS_MSG_TBL_STRU                    *pstDecodeMsgTbl;
}NAS_MSG_ENTRY_STRU;



/*****************************************************************************
  3 接口函数声明
*****************************************************************************/
NAS_PROTOCOL_ERR_ENUM_U8 NasEncodeMsg(
    const NAS_MSG_ENTRY_STRU            *pstMsgEntry,
    const VOS_UINT8                     *pucMsg,
    VOS_UINT8                           *pucRawData,
    VOS_UINT8                           *pucLength
);


NAS_PROTOCOL_ERR_ENUM_U8 NasDecodeMsg(
    const NAS_MSG_ENTRY_STRU           *pstMsgEntry,
    VOS_UINT16                          usTableNum,
    const VOS_UINT8                    *pucRawData,
    VOS_UINT8                           ucLength,
    VOS_UINT8                           *pucMsg
);



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

#endif /* __NAS_MSG_ENC_DEC_H__ */

