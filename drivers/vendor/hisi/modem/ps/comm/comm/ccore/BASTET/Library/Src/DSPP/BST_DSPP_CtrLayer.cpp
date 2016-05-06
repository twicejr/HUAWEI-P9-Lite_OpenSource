/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_CtrLayer.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : DSPP协议控制层相关类实现
  函数列表   :

  修改历史   :
  1.日    期 : 2014年04月16日
    作    者 : d00173029
    修改内容 : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_DSPP_TrsLayer.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_DSPP_AppLayer.h"
#include "BST_DBG_MemLeak.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_CTRLAYER_CPP
/*lint +e767*/
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DSPP_CP_OFFSET_ADDR         ( BST_DSPP_TPA_OFFSET_ADDR )
/*****************************************************************************
  3 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrDlVa::GetInstance
 功能描述   : BST_DSPP_CCtrDlVa类单例模式获取入库
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVa *BST_DSPP_CCtrDlVa::GetInstance( BST_VOID )
{
    static BST_DSPP_CCtrDlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CCtrDlVa ();
    }
    return s_pInstance;
}

/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrDlVa
 功能描述   : BST_DSPP_CCtrDlVa类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVa::BST_DSPP_CCtrDlVa ( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_CTR, BST_DSPP_VER_A )
{
}
/*****************************************************************************
 函 数 名   : ~BST_DSPP_CCtrDlVa
 功能描述   : BST_DSPP_CCtrDlVa类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVa::~BST_DSPP_CCtrDlVa ( BST_VOID )
{
}
/*****************************************************************************
 函 数 名   : ParseHeadInfo
 功能描述   : 解析控制层包头
 输入参数   : pstHead: 包头结构体指针
              pucData: 数据段头指针
              usLength: 数据段长度
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrDlVa::ParseHeadInfo(
    BST_DSPP_HEAD_STRU           *const pstHead,
    BST_UINT8 const              *pucData,
    BST_UINT16                    usLength )
{
    if ( BST_NULL_PTR == pstHead )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == pucData )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( usLength < BST_DSPP_CPA_HEAD_LEN )
    {
        BST_RLS_LOG1( "BST_DSPP_CCtrDlVa::ParseHeadInfo usLength=%u",
                      usLength );
        return BST_ERR_PAR_LEN;
    }
    pstHead->stCpVerA.usObjtAddr    = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OBJT_ADD_L],
                                                          pucData[BST_DSPP_CP_OBJT_ADD_H] );
    pstHead->stCpVerA.usOfstAddr    = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OFST_ADD_L],
                                                          pucData[BST_DSPP_CP_OFST_ADD_H] );
    pstHead->stCpVerA.ucActType     = ( BST_ERR_ENUM_UINT8 )pucData[BST_DSPP_CP_OPRT_ERR];
    pstHead->enApVer                = ( BST_DSPP_VERION_ENUM_UINT8 )pucData[BST_DSPP_CP_APL_VER];
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名   : UnpackInternal
 功能描述   : 解析数据包
 输入参数   : pstRxHeadInfo: 包头结构体指针
              penNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrDlVa::UnpackInternal (
    BST_DSPP_HEAD_STRU          *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8  *const penNextVer )
{
    BST_ERR_ENUM_UINT8              ucRtnVal;

    if ( ( BST_NULL_PTR == pstRxHeadInfo )
      || ( BST_NULL_PTR == penNextVer ) )
    {
        return BST_ERR_LAYER_VER;
    }
    if ( ( BST_NULL_PTR == pstRxHeadInfo->pucData )
      || ( 0 == pstRxHeadInfo->usLength ) )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return BST_ERR_LAYER_VER;
    }

    ucRtnVal                        = ParseHeadInfo( pstRxHeadInfo,
                                      pstRxHeadInfo->pucData,
                                      pstRxHeadInfo->usLength );
    if ( BST_NO_ERROR_MSG != ucRtnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CCtrDlVa::UnpackInternal ParseHeadInfo Err=%u",
                      ucRtnVal );
        return BST_ERR_LAYER_VER;
    }
    pstRxHeadInfo->usLength        -= BST_DSPP_CPA_HEAD_LEN;
    if ( BST_DSPP_VER_VOID != pstRxHeadInfo->enApVer )
    {
        pstRxHeadInfo->pucData     += BST_DSPP_CPA_HEAD_LEN;
    }
    else
    {
        pstRxHeadInfo->pucData      = BST_NULL_PTR;
    }
   *penNextVer                      = BST_DSPP_VER_A;
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名   : GetNextStrategy
 功能描述   : 获取下一层解析策略
 输入参数   : enNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_DSPP_CDlLayerBase类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CDlLayerBase *BST_DSPP_CCtrDlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_A:
            return ( BST_DSPP_CAppDlVa::GetInstance () );

        default:
            break;
    }

    return BST_NULL_PTR;
}


/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrUlVa::GetInstance
 功能描述   : BST_DSPP_CCtrUlVa类单例模式获取入库
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVa *BST_DSPP_CCtrUlVa::GetInstance( BST_VOID )
{
    static BST_DSPP_CCtrUlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CCtrUlVa ();
    }
    return s_pInstance;
}
/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrUlVa
 功能描述   : BST_DSPP_CCtrUlVa类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVa::BST_DSPP_CCtrUlVa ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_CTR, BST_DSPP_VER_A )
{
}
/*****************************************************************************
 函 数 名   : ~BST_DSPP_CCtrUlVa
 功能描述   : BST_DSPP_CCtrUlVa类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVa::~BST_DSPP_CCtrUlVa ( BST_VOID )
{
}
/*****************************************************************************
 函 数 名   : CheckObjtAdd
 功能描述   : 校验代理类型(Email/HeartBeat/MainTask)是否合法
 输入参数   : usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrUlVa::CheckObjtAdd(
    BST_DSPP_OBJTADDR_T  usObjtAddr )
{
    if ( BST_DSPP_IsObjIdValid ( usObjtAddr ) )
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
 函 数 名   : CheckOfstAdd
 功能描述   : 校验task ID是否合法
 输入参数   : usOfstAddr: task ID, modem具体任务
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrUlVa::CheckOfstAdd (
    BST_DSPP_OFSTADDR_T  usOfstAddr )
{
    if ( ( BST_DSPP_BROADCASE_ADDRESS != usOfstAddr )
      && ( BST_DSPP_INVALID_ADDR != usOfstAddr ) )
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
 函 数 名   : PackInternal
 功能描述   : 打包数据包
 输入参数   : pstTxHeadInfo: 包头结构体指针
 输出参数   : penNextVer: 下一个协议版本
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrUlVa::PackInternal (
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_UINT8              *pucSdu;
    BST_ERR_ENUM_UINT8      enRtnVal;

    enRtnVal                = BST_NO_ERROR_MSG;
    if ( ( BST_NULL_PTR == pstTxHeadInfo )
      || ( BST_NULL_PTR == pstNextVer ) )
    {
        enRtnVal            = BST_ERR_UNREACHABLE;
        goto err_drop;
    }

    if ( BST_NULL_PTR == pstTxHeadInfo->pucData )
    {
        enRtnVal            = BST_ERR_NO_MEMORY;
        goto err_drop;
    }

    enRtnVal                = CheckObjtAdd ( pstTxHeadInfo->stCpVerA.usObjtAddr );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CCtrUlVa::PackInternal CheckObjtAdd Err=%u",
                      enRtnVal );
        enRtnVal            = BST_ERR_UNREACHABLE;
        goto err_drop;
    }

    enRtnVal                = CheckOfstAdd ( pstTxHeadInfo->stCpVerA.usOfstAddr );
    if ( BST_NO_ERROR_MSG != enRtnVal)
    {
        BST_RLS_LOG1( "BST_DSPP_CCtrUlVa::PackInternal CheckOfstAdd Err=%u",
                      enRtnVal );
        enRtnVal            = BST_ERR_UNREACHABLE;
        goto err_drop;
    }

    pucSdu                  = pstTxHeadInfo->pucData + BST_DSPP_CP_OFFSET_ADDR;

    pucSdu[ BST_DSPP_CP_OBJT_ADD_L ]    = BST_DSPP_U16_TO_U8L
                                        ( pstTxHeadInfo->stCpVerA.usObjtAddr );
    pucSdu[ BST_DSPP_CP_OBJT_ADD_H ]    = BST_DSPP_U16_TO_U8H
                                        ( pstTxHeadInfo->stCpVerA.usObjtAddr );
    pucSdu[ BST_DSPP_CP_OFST_ADD_L ]    = BST_DSPP_U16_TO_U8L
                                        ( pstTxHeadInfo->stCpVerA.usOfstAddr );
    pucSdu[ BST_DSPP_CP_OFST_ADD_H ]    = BST_DSPP_U16_TO_U8H
                                        ( pstTxHeadInfo->stCpVerA.usOfstAddr );
    pucSdu[ BST_DSPP_CP_OPRT_ERR   ]    = pstTxHeadInfo->stCpVerA.ucActType;
    pucSdu[ BST_DSPP_CP_APL_VER    ]    = pstTxHeadInfo->enApVer;
    pucSdu[ BST_DSPP_CP_RESERVED_1 ]    = 0; /*四字节对齐保留字段，暂无实际含义*/
    pucSdu[ BST_DSPP_CP_RESERVED_2 ]    = 0; /*四字节对齐保留字段，暂无实际含义*/
    pstTxHeadInfo->usLength            += BST_DSPP_CPA_HEAD_LEN;
    pstTxHeadInfo->enTpVer              = BST_DSPP_VER_A;
    *pstNextVer                         = pstTxHeadInfo->enTpVer;
    return BST_NO_ERROR_MSG;

err_drop:
    if( BST_NULL_PTR != pstTxHeadInfo )
    {
        BST_OS_FREE( pstTxHeadInfo->pucSource );
    }
    return enRtnVal;
}
/*****************************************************************************
 函 数 名   : GetNextStrategy
 功能描述   : 获取下一层解析策略
 输入参数   : enNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_DSPP_CUlLayerBase类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CUlLayerBase *BST_DSPP_CCtrUlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    BST_DSPP_CUlLayerBase              *pcNextStrategy;

    pcNextStrategy                      = BST_NULL_PTR;

    if ( BST_DSPP_VER_A == enNextVer )
    {
        pcNextStrategy                  = BST_DSPP_CTrsUlVa::GetInstance ();
    }
    else
    {
        pcNextStrategy                  = BST_NULL_PTR;
    }

    return pcNextStrategy;
}

/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrDlVc::GetInstance
 功能描述   : BST_DSPP_CCtrDlVc类单例模式获取入库
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVc *BST_DSPP_CCtrDlVc::GetInstance( BST_VOID )
{
    static BST_DSPP_CCtrDlVc   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CCtrDlVc ();
    }
    return s_pInstance;
}
/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrDlVc
 功能描述   : BST_DSPP_CCtrDlVc类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVc::BST_DSPP_CCtrDlVc ( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_CTR, BST_DSPP_VER_C )
{
}
/*****************************************************************************
 函 数 名   : ~BST_DSPP_CCtrDlVc
 功能描述   : BST_DSPP_CCtrDlVc类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrDlVc::~BST_DSPP_CCtrDlVc ( BST_VOID )
{
}
/*****************************************************************************
 函 数 名   : ParseHeadInfo
 功能描述   : 解析控制层包头
 输入参数   : pstHead: 包头结构体指针
              pucData: 数据段头指针
              usLength: 数据段长度
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrDlVc::ParseHeadInfo(
    BST_DSPP_HEAD_STRU             *const pstHead,
    BST_UINT8 const                *pucData,
    BST_UINT16                      usLength )
{
    BST_UINT16                      usFlags;
    if( BST_NULL_PTR == pucData )
    {
        return BST_ERR_LAYER_VER;
    }

    pstHead->stCpVerC.ulMainLinkId  = BST_DSPP_U8_TO_U32(
                                    pucData[BST_DSPP_CPC_LINK_ID1_0],
                                    pucData[BST_DSPP_CPC_LINK_ID1_1],
                                    pucData[BST_DSPP_CPC_LINK_ID1_2],
                                    pucData[BST_DSPP_CPC_LINK_ID1_H] );

    pstHead->stCpVerC.ulAuxLinkId   = BST_DSPP_U8_TO_U32(
                                    pucData[BST_DSPP_CPC_LINK_ID2_0],
                                    pucData[BST_DSPP_CPC_LINK_ID2_1],
                                    pucData[BST_DSPP_CPC_LINK_ID2_2],
                                    pucData[BST_DSPP_CPC_LINK_ID2_H] );
    usFlags                         = BST_DSPP_U8_TO_U16( 
                                    pucData[BST_DSPP_CPC_FLAGS_L],
                                    pucData[BST_DSPP_CPC_FLAGS_H] );
    pstHead->stCpVerC.usCmdId       = BST_DSPP_CPC_GET_COMMAND( usFlags );
    pstHead->stCpVerC.ucAddrType    = BST_DSPP_CPC_IPADDR_TYPE( usFlags );
    pstHead->stCpVerC.usProcLevel   = BST_DSPP_CPC_GET_PROCLVL( usFlags );
    pstHead->stCpVerC.ucPropType    = BST_DSPP_CPC_GET_PROTYPE( usFlags );
    pstHead->stCpVerC.ucIpProtocol  = BST_DSPP_CPC_GET_PROTOCL( usFlags );
    pstHead->stCpVerC.ucPktAddr     = BST_DSPP_CPC_GET_PKTADDR( usFlags );
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名   : UnpackInternal
 功能描述   : 解析数据包
 输入参数   : pstRxHeadInfo: 包头结构体指针
              penNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrDlVc::UnpackInternal (
    BST_DSPP_HEAD_STRU          *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8  *const penNextVer )
{
    BST_ERR_ENUM_UINT8              ucRtnVal;

    if ( BST_NULL_PTR == pstRxHeadInfo )
    {
        return BST_ERR_LAYER_VER;
    }
    if ( BST_NULL_PTR == penNextVer )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return BST_ERR_LAYER_VER;
    }
    if ( ( BST_NULL_PTR == pstRxHeadInfo->pucData )
      || ( pstRxHeadInfo->usLength < BST_DSPP_CPC_HEAD_LEN ) )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return BST_ERR_LAYER_VER;
    }

    ucRtnVal                        = ParseHeadInfo( pstRxHeadInfo,
                                      pstRxHeadInfo->pucData,
                                      pstRxHeadInfo->usLength );
    if ( BST_NO_ERROR_MSG != ucRtnVal )
    {
        BST_RLS_LOG1( "BST_DSPP_CCtrDlVa::UnpackInternal ParseHeadInfo Err=%u",
                      ucRtnVal );
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return BST_ERR_LAYER_VER;
    }
    pstRxHeadInfo->pucData         += BST_DSPP_CPC_HEAD_LEN;
    pstRxHeadInfo->usLength        -= BST_DSPP_CPC_HEAD_LEN;
   *penNextVer                      = BST_DSPP_VER_C;
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 函 数 名   : GetNextStrategy
 功能描述   : 获取下一层解析策略
 输入参数   : enNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_DSPP_CDlLayerBase类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月04日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CDlLayerBase *BST_DSPP_CCtrDlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    if( BST_DSPP_VER_C == enNextVer )
    {
        return BST_DSPP_CAppDlVc::GetInstance();
    }
    else
    {
        return BST_NULL_PTR;
    }
}


/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrUlVc::GetInstance
 功能描述   : BST_DSPP_CCtrUlVc类单例模式获取入库
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVc *BST_DSPP_CCtrUlVc::GetInstance( BST_VOID )
{
    static BST_DSPP_CCtrUlVc   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CCtrUlVc ();
    }
    return s_pInstance;
}
/*****************************************************************************
 函 数 名   : BST_DSPP_CCtrUlVc
 功能描述   : BST_DSPP_CCtrUlVc类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVc::BST_DSPP_CCtrUlVc ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_CTR, BST_DSPP_VER_C )
{
}
/*****************************************************************************
 函 数 名   : ~BST_DSPP_CCtrUlVc
 功能描述   : BST_DSPP_CCtrUlVc类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CCtrUlVc::~BST_DSPP_CCtrUlVc ( BST_VOID )
{
}

/*****************************************************************************
 函 数 名   : PackInternal
 功能描述   : 打包数据包
 输入参数   : pstTxHeadInfo: 包头结构体指针
 输出参数   : penNextVer: 下一个协议版本
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CCtrUlVc::PackInternal (
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_UINT8              *pucSdu;
    BST_UINT16              usFlags;
    BST_ERR_ENUM_UINT8      enRtnVal;

    enRtnVal                = BST_NO_ERROR_MSG;

    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNREACHABLE;
    }
    if ( BST_NULL_PTR == pstNextVer )
    {
        BST_OS_FREE( pstTxHeadInfo->pucSource );
        return BST_ERR_UNREACHABLE;
    }

    if ( BST_NULL_PTR == pstTxHeadInfo->pucData )
    {
        return BST_ERR_NO_MEMORY;
    }

    if( ( BST_DSPP_FLG_CMD_INVALID == pstTxHeadInfo->stCpVerC.usCmdId )
        ||( BST_DSPP_FLG_CMD_BUTT <= pstTxHeadInfo->stCpVerC.usCmdId ) )
    {
        BST_OS_FREE( pstTxHeadInfo->pucSource );
        return BST_ERR_UNREACHABLE;
    }

    usFlags                 = 0;
    BST_DSPP_CPC_SET_COMMAND    (usFlags, pstTxHeadInfo->stCpVerC.usCmdId);
    BST_DSPP_CPC_SET_IPADDR_TYPE(usFlags, pstTxHeadInfo->stCpVerC.ucAddrType );
    BST_DSPP_CPC_SET_PROC_LVL   (usFlags, pstTxHeadInfo->stCpVerC.usProcLevel);
    BST_DSPP_CPC_SET_PROP_TYPE  (usFlags, pstTxHeadInfo->stCpVerC.ucPropType);
    BST_DSPP_CPC_SET_PROTOCL    (usFlags, pstTxHeadInfo->stCpVerC.ucIpProtocol);
    BST_DSPP_CPC_SET_PKTADDR    (usFlags, pstTxHeadInfo->stCpVerC.ucPktAddr);

    pucSdu                              = pstTxHeadInfo->pucData + BST_DSPP_CP_OFFSET_ADDR;
    pucSdu[ BST_DSPP_CPC_LINK_ID1_0 ]   = BST_DSPP_U32_TO_U8_0
                                        ( pstTxHeadInfo->stCpVerC.ulMainLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID1_1 ]   = BST_DSPP_U32_TO_U8_1
                                        ( pstTxHeadInfo->stCpVerC.ulMainLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID1_2 ]   = BST_DSPP_U32_TO_U8_2
                                        ( pstTxHeadInfo->stCpVerC.ulMainLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID1_H ]   = BST_DSPP_U32_TO_U8_3
                                        ( pstTxHeadInfo->stCpVerC.ulMainLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID2_0 ]   = BST_DSPP_U32_TO_U8_0
                                        ( pstTxHeadInfo->stCpVerC.ulAuxLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID2_1 ]   = BST_DSPP_U32_TO_U8_1
                                        ( pstTxHeadInfo->stCpVerC.ulAuxLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID2_2 ]   = BST_DSPP_U32_TO_U8_2
                                        ( pstTxHeadInfo->stCpVerC.ulAuxLinkId );
    pucSdu[ BST_DSPP_CPC_LINK_ID2_H ]   = BST_DSPP_U32_TO_U8_3
                                        ( pstTxHeadInfo->stCpVerC.ulAuxLinkId );
    pucSdu[ BST_DSPP_CPC_FLAGS_L ]      = BST_DSPP_U16_TO_U8L( usFlags );
    pucSdu[ BST_DSPP_CPC_FLAGS_H ]      = BST_DSPP_U16_TO_U8H( usFlags );

    pstTxHeadInfo->usLength            += BST_DSPP_CPC_HEAD_LEN;
    pstTxHeadInfo->enTpVer              = BST_DSPP_VER_A;
   *pstNextVer                          = pstTxHeadInfo->enTpVer;

    return enRtnVal;
}
/*****************************************************************************
 函 数 名   : GetNextStrategy
 功能描述   : 获取下一层解析策略
 输入参数   : enNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_DSPP_CUlLayerBase类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
*****************************************************************************/
BST_DSPP_CUlLayerBase *BST_DSPP_CCtrUlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    BST_DSPP_CUlLayerBase              *pcNextStrategy;

    pcNextStrategy                      = BST_NULL_PTR;

    if ( BST_DSPP_VER_A == enNextVer )
    {
        pcNextStrategy                  = BST_DSPP_CTrsUlVa::GetInstance ();
    }
    else
    {
        pcNextStrategy                  = BST_NULL_PTR;
    }
    return pcNextStrategy;
}

