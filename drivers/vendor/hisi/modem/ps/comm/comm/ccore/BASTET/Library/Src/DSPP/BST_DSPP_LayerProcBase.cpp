

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_DSPP_LayerProcBase.h"
#include "BST_DBG_MemLeak.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_LAYERPROCBASE_CPP
/*lint +e767*/
/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
  3 私有定义
******************************************************************************/


/******************************************************************************
  4 全局变量定义
******************************************************************************/


/******************************************************************************
  5 函数实现
******************************************************************************/


BST_DSPP_CDlLayerBase::BST_DSPP_CDlLayerBase ( BST_DSPP_LAYER_ID_ENUM_UINT8  enLayerId,
                                               BST_DSPP_VERION_ENUM_UINT8    enLayerVer )
    : m_enLayerId ( enLayerId ), m_enLayerVer ( enLayerVer )
{
}


BST_DSPP_CDlLayerBase::~BST_DSPP_CDlLayerBase ( BST_VOID )
{
}


BST_ERR_ENUM_UINT8  BST_DSPP_CDlLayerBase::UnPack ( BST_DSPP_HEAD_STRU *const pstRxHeadInfo )
{
    BST_DSPP_CDlLayerBase              *pcNextLayer;
    BST_DSPP_VERION_ENUM_UINT8          enNextVer;
    BST_ERR_ENUM_UINT8                  ucRtnVal;

    enNextVer                           = BST_DSPP_VER_INVALID;
    pcNextLayer                         = BST_NULL_PTR;
    BST_DBG_LOG ( "BST_DSPP_CDlLayerBase::UnPack is called" );

    ucRtnVal                            =  UnpackInternal ( pstRxHeadInfo, &enNextVer );
    if ( BST_NO_ERROR_MSG != ucRtnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CDlLayerBase::UnPack UnpackInternal Err=%u",
                      ucRtnVal );
        return BST_ERR_LAYER_VER;
    }

    if ( BST_DSPP_VER_VOID == enNextVer )
    {
        return BST_ERR_LAYER_VER;
    }

    pcNextLayer                         = GetNextStrategy ( enNextVer );
    if ( BST_NULL_PTR != pcNextLayer )
    {
        ucRtnVal                        = pcNextLayer->UnPack ( pstRxHeadInfo );
    }
    else
    {
        ucRtnVal                        = BST_NO_ERROR_MSG;
    }
    return ucRtnVal;
}


BST_ERR_ENUM_UINT8  BST_DSPP_CUlLayerBase::Pack ( BST_DSPP_HEAD_STRU *const pstTxHeadInfo )
{
    BST_DSPP_CUlLayerBase              *pcNextLayer;
    BST_DSPP_VERION_ENUM_UINT8          enNextVer;
    BST_ERR_ENUM_UINT8                  ucRrnVal;

    enNextVer                           = BST_DSPP_VER_INVALID;
    pcNextLayer                         = BST_NULL_PTR;

    ucRrnVal                            = PackInternal ( pstTxHeadInfo, &enNextVer );
    if ( BST_NO_ERROR_MSG != ucRrnVal )
    {
        return BST_ERR_LAYER_VER;
    }

    if ( BST_DSPP_VER_VOID == enNextVer )
    {
        return BST_ERR_LAYER_VER;
    }

    pcNextLayer                         = GetNextStrategy ( enNextVer );
    if ( BST_NULL_PTR != pcNextLayer )
    {
        ucRrnVal                        = pcNextLayer->Pack ( pstTxHeadInfo );
    }
    else
    {
        ucRrnVal                        = BST_NO_ERROR_MSG;
    }
    return ucRrnVal;
}


BST_DSPP_CUlLayerBase::BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_ID_ENUM_UINT8  enLayerId,
                                               BST_DSPP_VERION_ENUM_UINT8    enLayerVer )
    : m_enLayerId ( enLayerId ), m_enLayerVer ( enLayerVer )
{
}


BST_DSPP_CUlLayerBase::~BST_DSPP_CUlLayerBase ( BST_VOID )
{
}

