/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_CtrLayer.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年05月04日
  最近修改   :
  功能描述   : DSPP协议传输层处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年05月13日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_DSPP_CTRLAYER_H__
#define __BST_DSPP_CTRLAYER_H__

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_DSPP_LayerProcBase.h"
#include "BST_DSPP_Define.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DSPP_OFFSET_ADDR_MIN        ( 0x0001 )
#define BST_DSPP_OFFSET_ADDR_MAX        ( BST_DSPP_OFFSET_ADDR_MIN + BST_MAX_APP_NUMBER )
#define BST_DSPP_BROADCASE_ADDRESS      ( 0x0000 )

#define BST_DSPP_CPC_GET_COMMAND(usFlg) ((BST_UINT16)((usFlg)&0x0FU))
#define BST_DSPP_CPC_IPADDR_TYPE(usFlg) ((BST_UINT16)(((usFlg)>>4)&0x3U))
#define BST_DSPP_CPC_GET_PROCLVL(usFlg) ((BST_UINT16)(((usFlg)>>8)&0x0FU))
#define BST_DSPP_CPC_GET_PROTYPE(usFlg) ((BST_UINT8)(((usFlg)>>6)&0x03U))
#define BST_DSPP_CPC_GET_PROTOCL(usFlg) ((BST_UINT8)(((usFlg)>>12)&0x03U))
#define BST_DSPP_CPC_GET_PKTADDR(usFlg) ((BST_UINT8)(((usFlg)>>14)&0x03U))

#define BST_DSPP_CPC_SET_COMMAND(usFlg, ucCmd) \
                                        (((usFlg)&=0xFFF0U)|=((ucCmd)&0x0FU))
#define BST_DSPP_CPC_SET_IPADDR_TYPE(usFlg, ucType)\
                                        (((usFlg)&=0xFFCFU)|=(((ucType)&0x03U)<<4))
#define BST_DSPP_CPC_SET_PROC_LVL(usFlg, ucType)\
                                        (((usFlg)&=0xF0FFU)|=(((ucType)&0x0FU)<<8))
#define BST_DSPP_CPC_SET_PROP_TYPE(usFlg, ucUsed)\
                                        (((usFlg)&=0xFF3FU)|=(((ucUsed)&0x03U)<<6))
#define BST_DSPP_CPC_SET_PROTOCL(usFlg, ucPrtc) \
                                        (((usFlg)&=0xCFFFU)|=(((ucPrtc)&0x03U)<<12))
#define BST_DSPP_CPC_SET_PKTADDR(usFlg, ucPkta) \
                                        (((usFlg)&=0x3FFFU)|=(((ucPkta)&0x03U)<<14))
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum
{
    BST_DSPP_CP_OBJT_ADD_L              = 0x00,
    BST_DSPP_CP_OBJT_ADD_H,
    BST_DSPP_CP_OFST_ADD_L,
    BST_DSPP_CP_OFST_ADD_H,
    BST_DSPP_CP_OPRT_ERR,
    BST_DSPP_CP_APL_VER,
    BST_DSPP_CP_RESERVED_1,
    BST_DSPP_CP_RESERVED_2,
    BST_DSPP_CPA_HEAD_LEN
};

enum
{
    BST_DSPP_CPC_LINK_ID1_0              = 0x00,
    BST_DSPP_CPC_LINK_ID1_1,
    BST_DSPP_CPC_LINK_ID1_2,
    BST_DSPP_CPC_LINK_ID1_H,
    BST_DSPP_CPC_LINK_ID2_0,
    BST_DSPP_CPC_LINK_ID2_1,
    BST_DSPP_CPC_LINK_ID2_2,
    BST_DSPP_CPC_LINK_ID2_H,
    BST_DSPP_CPC_FLAGS_L,
    BST_DSPP_CPC_FLAGS_H,
    BST_DSPP_CPC_HEAD_LEN
};

enum
{
    BST_DSPP_CPC_BUFFER_NUM_0           = 0x00,
    BST_DSPP_CPC_BUFFER_NUM_1,
    BST_DSPP_CPC_BUFFER_NUM_LEN
};
enum
{
    BST_DSPP_CPC_FLOW_NUM_0           = 0x00,
    BST_DSPP_CPC_FLOW_NUM_1,
    BST_DSPP_CPC_FLOW_NUM_2,
    BST_DSPP_CPC_FLOW_NUM_3,
    BST_DSPP_CPC_FLOW_NUM_LEN
};


/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/


/*****************************************************************************
  9 类定义
*****************************************************************************/
class BST_DSPP_CCtrDlVa
    : BST_PUBLIC BST_DSPP_CDlLayerBase
{
BST_PUBLIC:
    static BST_DSPP_CCtrDlVa *GetInstance( BST_VOID );
BST_PRIVATE:
    BST_DSPP_CCtrDlVa   ( BST_VOID );
   ~BST_DSPP_CCtrDlVa   ( BST_VOID );
    BST_ERR_ENUM_UINT8      ParseHeadInfo(
        BST_DSPP_HEAD_STRU           *const pstHead,
        BST_UINT8 const              *pucData,
        BST_UINT16                    usLength );

    BST_ERR_ENUM_UINT8      UnpackInternal(
        BST_DSPP_HEAD_STRU           *const pstRxHeadInfo,
        BST_DSPP_VERION_ENUM_UINT8   *const penNextVer );

    BST_DSPP_CDlLayerBase  *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8    enNextVer );
};

class BST_DSPP_CCtrUlVa
    : BST_PUBLIC BST_DSPP_CUlLayerBase
{
BST_PUBLIC:
    static BST_DSPP_CCtrUlVa *GetInstance( BST_VOID );

BST_PRIVATE:
    BST_DSPP_CCtrUlVa   ( BST_VOID );
   ~BST_DSPP_CCtrUlVa   ( BST_VOID );

BST_PROTECTED:
    BST_ERR_ENUM_UINT8      CheckObjtAdd(
        BST_DSPP_OBJTADDR_T usObjtAddr );

    BST_ERR_ENUM_UINT8      CheckOfstAdd(
        BST_DSPP_OFSTADDR_T usOfstAddr );

    BST_ERR_ENUM_UINT8      PackInternal(
        BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
        BST_DSPP_VERION_ENUM_UINT8 *const penNextVer );

    BST_DSPP_CUlLayerBase  *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8  enNextVer );
};

class BST_DSPP_CCtrDlVc
    : BST_PUBLIC BST_DSPP_CDlLayerBase
{
BST_PUBLIC:
    static BST_DSPP_CCtrDlVc *GetInstance( BST_VOID );

BST_PRIVATE:
    BST_DSPP_CCtrDlVc   ( BST_VOID );

   ~BST_DSPP_CCtrDlVc   ( BST_VOID );

    BST_ERR_ENUM_UINT8      ParseHeadInfo(
        BST_DSPP_HEAD_STRU           *const pstHead,
        BST_UINT8 const              *pucData,
        BST_UINT16                    usLength );

    BST_ERR_ENUM_UINT8      UnpackInternal(
        BST_DSPP_HEAD_STRU           *const pstRxHeadInfo,
        BST_DSPP_VERION_ENUM_UINT8   *const penNextVer );

    BST_DSPP_CDlLayerBase  *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8    enNextVer );
};


class BST_DSPP_CCtrUlVc
    : BST_PUBLIC BST_DSPP_CUlLayerBase
{
BST_PUBLIC:
    static BST_DSPP_CCtrUlVc *GetInstance( BST_VOID );


BST_PROTECTED:
    BST_DSPP_CCtrUlVc   ( BST_VOID );

   ~BST_DSPP_CCtrUlVc   ( BST_VOID );

    BST_ERR_ENUM_UINT8      PackInternal(
        BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
        BST_DSPP_VERION_ENUM_UINT8 *const penNextVer );

    BST_DSPP_CUlLayerBase  *GetNextStrategy(
        BST_DSPP_VERION_ENUM_UINT8  enNextVer );
};

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif



#endif //CONTROL_LAYER_H

