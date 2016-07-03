

#ifndef __BST_DSPP_LAYERPROCBASE_H__
#define __BST_DSPP_LAYERPROCBASE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_DSPP_Define.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 枚举定义
*****************************************************************************/


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

class BST_DSPP_CDlLayerBase
{
BST_PUBLIC:
    virtual BST_ERR_ENUM_UINT8          UnPack                  ( BST_DSPP_HEAD_STRU           *const pstRxHeadInfo );

BST_PROTECTED:
                                        BST_DSPP_CDlLayerBase   ( BST_DSPP_LAYER_ID_ENUM_UINT8  enLayerId,
                                                                  BST_DSPP_VERION_ENUM_UINT8    enLayerVer );
    virtual                            ~BST_DSPP_CDlLayerBase   ( BST_VOID );
    virtual BST_ERR_ENUM_UINT8          ParseHeadInfo           ( BST_DSPP_HEAD_STRU           *const pstHead,
                                                                  BST_UINT8 const              *pucData,
                                                                  BST_UINT16                    usLength )
    { return BST_NO_ERROR_MSG; }

    virtual BST_ERR_ENUM_UINT8          UnpackInternal          ( BST_DSPP_HEAD_STRU           *const pstRxHeadInfo,
                                                                  BST_DSPP_VERION_ENUM_UINT8   *const penNextVer )
    { return BST_NO_ERROR_MSG; }

    virtual BST_DSPP_CDlLayerBase      *GetNextStrategy         ( BST_DSPP_VERION_ENUM_UINT8    enNextVer )
    { return BST_NULL_PTR; }

    const BST_DSPP_LAYER_ID_ENUM_UINT8  m_enLayerId;
    const BST_DSPP_VERION_ENUM_UINT8    m_enLayerVer;
};

class BST_DSPP_CUlLayerBase
{
BST_PUBLIC:
    virtual BST_ERR_ENUM_UINT8          Pack                    ( BST_DSPP_HEAD_STRU           *const pstTxHeadInfo );

BST_PROTECTED:
                                        BST_DSPP_CUlLayerBase   ( BST_DSPP_LAYER_ID_ENUM_UINT8  enLayerId,
                                                                  BST_DSPP_VERION_ENUM_UINT8    enLayerVer );
    virtual                            ~BST_DSPP_CUlLayerBase   ( BST_VOID );
    virtual BST_ERR_ENUM_UINT8          PackInternal            ( BST_DSPP_HEAD_STRU           *const pstRxHeadInfo,
                                                                  BST_DSPP_VERION_ENUM_UINT8   *const penNextVer )
    { return BST_NO_ERROR_MSG; }

    virtual BST_DSPP_CUlLayerBase      *GetNextStrategy         ( BST_DSPP_VERION_ENUM_UINT8    enNextVer )
    { return BST_NULL_PTR; }

    const BST_DSPP_LAYER_ID_ENUM_UINT8  m_enLayerId;
    const BST_DSPP_VERION_ENUM_UINT8    m_enLayerVer;
};



#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
