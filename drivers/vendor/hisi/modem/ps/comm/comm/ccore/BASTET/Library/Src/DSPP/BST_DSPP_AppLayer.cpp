/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DSPP_AppLayer.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   :
  最近修改   :
  功能描述   : DSPP 协议的APPLayer 类文件
  函数列表   :

  修改历史   :
  1.日    期 : 2014年04月16日
    作    者 : d00173029
    修改内容 : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_DSPP_AppLayer.h"
#include "BST_DSPP_CtrLayer.h"
#include "BST_DSPP_TrsLayer.h"
#include "BST_DBG_MemLeak.h"
#include "BST_SRV_Event.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DSPP_APPLAYER_CPP
/*lint +e767*/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
******************************************************************************/

/***************************************************************
 函 数 名   : BST_DSPP_CAppDlVa
 功能描述   : BST_DSPP_CAppDlVa类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVa::BST_DSPP_CAppDlVa( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{
    m_pcTaskManager = BST_SRV_CTaskMng::GetInstance ();
}

/***************************************************************
 函 数 名   : ~BST_DSPP_CAppDlVa
 功能描述   : BST_DSPP_CAppDlVa类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVa::~BST_DSPP_CAppDlVa( BST_VOID )
{
    m_pcTaskManager                     = BST_NULL_PTR;
}

/***************************************************************
 函 数 名   : ParseHeadInfo
 功能描述   : 解析包头信息
 输入参数   : pstHead: 包头结构体指针
              pucData: 数据段起始指针
              usLength: 数据段长度
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ParseHeadInfo(
    BST_DSPP_HEAD_STRU   *const pstHead,
    BST_UINT8 const      *pucData,
    BST_UINT16            usLength )
{
    return BST_NO_ERROR_MSG;
}

/***************************************************************
 函 数 名   : ReadOut
 功能描述   : 从数据库或者应用程序读取参数值
 输入参数   :
    BST_DSPP_OBJTADDR_T     usObjtAddr,     操作对象类型
    BST_DSPP_OFSTADDR_T     usOfstAddr,     操作对象偏移地址
    BST_UINT8              *pucSrcBuff,     保存PID信息的源缓冲
    BST_UINT8              *pucDstBuff,     读出信息的目标缓冲
    BST_UINT16              usSrcLen        原缓冲区长度
    BST_UINT16              usDstLen        目标缓冲区长度

 输出参数   : 无
 返 回 值   : 实际获取长度
 被调函数   :
 调用函数   : config

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_UINT16 BST_DSPP_CAppDlVa::ReadOut(
    BST_DSPP_OBJTADDR_T     usObjtAddr,
    BST_DSPP_OFSTADDR_T     usOfstAddr,
    BST_UINT8              *pucSrcBuff,
    BST_UINT8              *pucDstBuff,
    BST_UINT16              usSrcLen,
    BST_UINT16              usDstLen )
{

    BST_CORE_PID_LEN_T                  usParamLen;
    BST_CORE_PID_ENUM_UINT16            usParamId;
    BST_UINT16                          usLooper;
    BST_UINT16                          usResBufCnt;

    usResBufCnt                         = 0;
    for ( usLooper = 0;
          usLooper < usSrcLen;
          usLooper += BST_CORE_PID_LEN )
    {

        /*
         * 读取PID编号
         */
        usParamId                       = BST_DSPP_AP_BYTE2PID
                                         ( pucSrcBuff[ usLooper ], pucSrcBuff[ usLooper + 1 ] );
        /*
         * 读取参数保存长度
         * |--PL(2 BYTE)--|--PID(2 BYTE)--|--Content( usParamLen，函数获得)--|
         * 因此，读入缓冲长度至少为BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )+BST_CORE_PID_LEN
         */
        usParamLen                      = m_pcTaskManager->Inquire
                                         ( usObjtAddr, usOfstAddr, usParamId,
                                         ( BST_UINT16 )( usDstLen - usResBufCnt
                                                       - BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                       - BST_CORE_PID_LEN ),
                                                        pucDstBuff + usResBufCnt
                                                        + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                                        + BST_CORE_PID_LEN );
        BST_DBG_LOG4( "DSPP Inquire: procid=%u, taskid=%u, pid=%u, plen=%u",
                      usObjtAddr, usOfstAddr, usParamId, usParamLen );

        /*
         * 参数长度获取成功后，复制缓冲区内容
         */
        if ( 0 != usParamLen )
        {
            usParamLen                 += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN );
            pucDstBuff[usResBufCnt]    = BST_DSPP_U16_TO_U8L ( usParamLen );
            pucDstBuff[usResBufCnt+1]  = BST_DSPP_U16_TO_U8H ( usParamLen );
            pucDstBuff[usResBufCnt+2]  = BST_DSPP_U16_TO_U8L ( usParamId );
            pucDstBuff[usResBufCnt+3]  = BST_DSPP_U16_TO_U8H ( usParamId );
            usResBufCnt               += usParamLen;
        }

        /*
         * 如果继续读取长度超限，那么将结束本次参数读取操作
         */
        if ( usResBufCnt + BST_OS_SIZEOF ( BST_CORE_PID_LEN_T ) + BST_CORE_PID_LEN > usDstLen )
        {
            break;
        }
    }
    return usResBufCnt;
}

/***************************************************************
 函 数 名   : Inquire
 功能描述   : 从modem读取配置信息
 输入参数   : usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
              usOfstAddr: task ID, modem具体任务
              pstRxHeadInfo: 包头结构体指针
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Inquire(
    BST_DSPP_OBJTADDR_T    usObjtAddr,
    BST_DSPP_OFSTADDR_T    usOfstAddr,
    BST_DSPP_HEAD_STRU    *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT16                  usLooper;
    BST_UINT16                  usResBufCnt;
    BST_UINT8                  *pucData;
    BST_UINT8                  *pcResBuffer;
    BST_UINT16                  usPktTotLen;

    usLooper                    = 0;
    usParamLen                  = 0;
    usPktTotLen                 = 0;
    usResBufCnt                 = 0;
    usParamId                   = BST_PID_INVALID;
    pcResBuffer                 = BST_NULL_PTR;
    pucData                     = pstRxHeadInfo->pucData;

    /*
     * 入口条件检查
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
     || ( BST_NULL_PTR == pstRxHeadInfo ) )
    {
        return BST_ERR_INVALID_PTR;
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire usObjtAddr=%u",
                      usObjtAddr );
        return BST_ERR_UNKNOW_OBJ;
    }

    if ( ( BST_NULL_PTR == pucData )
     || ( BST_CORE_PID_LEN > pstRxHeadInfo->usLength ) )
    {
        return BST_ERR_PAR_LEN;
    }

    if ( ( pstRxHeadInfo->usLength % BST_CORE_PID_LEN ) != 0 )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Inquire pstRxHeadInfo->usLength=%u",
                      pstRxHeadInfo->usLength );
        return BST_ERR_PAR_LEN;
    }

    /*
     * 首先获取预查询参数的总长度
     */
    for ( usLooper = 0;
          usLooper < pstRxHeadInfo->usLength;
          usLooper+= BST_CORE_PID_LEN )
    {
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pucData[usLooper], pucData[usLooper + 1] );
        usParamLen              = m_pcTaskManager->GetLen
                                ( usObjtAddr, usOfstAddr, usParamId );

        if ( 0 != usParamLen )
        {
            usPktTotLen        += ( BST_OS_SIZEOF ( BST_CORE_PID_LEN_T )
                                  + BST_CORE_PID_LEN
                                  + usParamLen );
        }
    }
    if ( 0 == usPktTotLen )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    /*
     * 申请目标缓冲资源
     */
    pcResBuffer                 = ( BST_UINT8 * )BST_OS_MALLOC ( usPktTotLen );
    if ( BST_NULL_PTR == pcResBuffer )
    {
        return BST_ERR_NO_MEMORY;
    }
    BST_OS_MEMSET( pcResBuffer, 0, usPktTotLen );
    /*
     * 从PID数据库或者应用程序获得参数内容
     */
    usResBufCnt                 = ReadOut( usObjtAddr, usOfstAddr, pucData, pcResBuffer,
                                           pstRxHeadInfo->usLength, usPktTotLen );
    /*
     * Memory Leak! If we malloc the space but copy none, We shoud release it here;
     */
    if ( 0 == usResBufCnt )
    {
        BST_OS_FREE ( pcResBuffer );
        pcResBuffer             = BST_NULL_PTR;
    }
    /*
     * 从新配置缓冲区内容，供应用使用
     */
    pstRxHeadInfo->pucData      = pcResBuffer;
    pstRxHeadInfo->usLength     = usResBufCnt;
    return BST_NO_ERROR_MSG;
}

/***************************************************************
 函 数 名   : Config
 功能描述   : 配置DSPP下发的数据包到协议适配层
 输入参数   : usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
              usOfstAddr: task ID, modem具体任务
              pstRxHeadInfo: 包头结构体指针
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Config(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_DSPP_HEAD_STRU *const pstRxHeadInfo )
{
    BST_CORE_PID_LEN_T          usParamLen;
    BST_CORE_PID_ENUM_UINT16    usParamId;
    BST_UINT8                  *pcData;
    BST_UINT16                  usBufCnt;
    BST_ERR_ENUM_UINT8          ucRtnVal;

    if ( BST_NULL_PTR == pstRxHeadInfo )
    {
        return BST_ERR_INVALID_PTR;
    }
    usParamLen                  = 0;
    usBufCnt                    = 0;
    usParamId                   = BST_PID_INVALID;
    ucRtnVal                    = BST_NO_ERROR_MSG;
    pcData                      = pstRxHeadInfo->pucData;

    /*
     * 入口检查
     */
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return ( BST_ERR_INVALID_PTR );
    }

    if ( !BST_DSPP_IsObjIdValid (usObjtAddr) )
    {
        BST_RLS_LOG1( "BST_DSPP_CAppDlVa::Config usObjtAddr=%u",
                      usObjtAddr );
        return ( BST_ERR_UNKNOW_OBJ );
    }

    if( BST_CORE_PID_LEN > pstRxHeadInfo->usLength )
    {
        return ( BST_ERR_PAR_LEN );
    }

    for (;;)
    {
        /*
         * 如果剩余数据长度无法获取有效PID信息，那么直接退出或返回
         */
        if ( pstRxHeadInfo->usLength - usBufCnt <= BST_DSPP_AP_CMD_HEAD_LEN )
        {
            if ( pstRxHeadInfo->usLength == usBufCnt )
            {
                ucRtnVal        = BST_NO_ERROR_MSG;
            }
            else
            {
                ucRtnVal        = BST_ERR_PAR_LEN;
            }
            break;
        }
        /*
         * 读取PID长度，PID名称等信息
         */
        usParamLen              = ( BST_CORE_PID_LEN_T )BST_DSPP_U8_TO_U16
                                  ( pcData[BST_DSPP_AP_CMD_LEN_L],
                                    pcData[BST_DSPP_AP_CMD_LEN_H] )
                                   -BST_DSPP_AP_CMD_HEAD_LEN;
        usParamId               = BST_DSPP_AP_BYTE2PID
                                ( pcData[BST_DSPP_AP_CMD_ID_L],
                                  pcData[BST_DSPP_AP_CMD_ID_H] );
        pcData                 += BST_DSPP_AP_CMD_HEAD_LEN;
        usBufCnt               += BST_DSPP_AP_CMD_HEAD_LEN;

        /*
         * 如果剩余内容长度与解析出的结果不符合，则读取识别，无法配置内容
         */
        if ( ( pstRxHeadInfo->usLength - usBufCnt ) < usParamLen )
        {
            BST_RLS_LOG3( "BST_DSPP_CAppDlVa::Config usLength=%u,usBufCnt=%u,usParamLen=%u",
                          pstRxHeadInfo->usLength, usBufCnt, usParamLen );
            ucRtnVal            = BST_ERR_PAR_LEN;
            break;
        }
        /*
         * 写入参数值
         */
        ucRtnVal                = m_pcTaskManager->Config
                                 ( usObjtAddr, usOfstAddr, usParamId,
                                   usParamLen, pcData );
        if ( BST_NO_ERROR_MSG == ucRtnVal )
        {
            pcData             += usParamLen;
            usBufCnt           += usParamLen;
        }
        else
        {
            break;
        }
    }
    return ( ucRtnVal );
}

/***************************************************************
 函 数 名   : Assign
 功能描述   : 为新任务分配线程资源
 输入参数   : pstRxHeadInfo:    包头结构体指针
           **ppstMbox：          指向邮箱地址的指针
              usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
 BST_ERR_ENUM_UINT8 BST_DSPP_CAppDlVa::Assign(
    BST_DSPP_HEAD_STRU     *const pstRxHeadInfo,
    BST_OS_MBX_T          **ppstMbox )
{
    BST_UINT16              usOfstAddr;
    /*
     * 入口检查
     */
    if ( ( BST_NULL_PTR == m_pcTaskManager )
      || ( BST_NULL_PTR == pstRxHeadInfo )
      || ( BST_NULL_PTR == ppstMbox ) )
    {
        return ( BST_ERR_INVALID_PTR );
    }
    /*
     * 校验PID是否有效
     */
    if ( !BST_DSPP_IsObjIdValid (pstRxHeadInfo->stCpVerA.usObjtAddr) )
    {
        return ( BST_ERR_UNKNOW_OBJ );
    }

    /*
     * 从任务管理器获取新任务的ID编号
     */
    usOfstAddr              = m_pcTaskManager->Assign 
                            ( pstRxHeadInfo->stCpVerA.usObjtAddr,
                              pstRxHeadInfo->stCpVerA.usOfstAddr, ppstMbox );
    BST_DBG_LOG2( "DSPP Assign: procid=%u, taskid=%u", pstRxHeadInfo->stCpVerA.usObjtAddr, usOfstAddr );
    if( ( BST_DSPP_INVALID_ADDR == usOfstAddr )
      ||( BST_NULL_PTR == ppstMbox ) )
    {
        return ( BST_ERR_NO_MEMORY );
    }
    /*
     * 保持参数值到入口
     */
    pstRxHeadInfo->stCpVerA.usOfstAddr  = usOfstAddr;
    pstRxHeadInfo->enApVer              = BST_DSPP_VER_VOID;
    return ( BST_NO_ERROR_MSG );
}
/***************************************************************
 函 数 名   : Remove
 功能描述   : 删除代理
 输入参数   : usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
              usOfstAddr: task ID, modem具体任务
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::Remove(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr )
{
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_DSPP_INVALID_ADDR == usOfstAddr )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    BST_DBG_LOG2( "DSPP Remove: procid=%u, taskid=%u", usObjtAddr, usOfstAddr );
    return ( m_pcTaskManager->Remove ( usObjtAddr, usOfstAddr ) );
}

/***************************************************************
 函 数 名   : ProcAction
 功能描述   : 根据解析的ACTION类型，分散调用各入口
 输入参数   :
    BST_DSPP_HEAD_STRU     *const pstRxHeadInfo,    DSPP格式接收头
    BST_DSPP_OFSTADDR_T     usOfstAddr,            类型名称
    BST_DSPP_OBJTADDR_T     usObjtAddr              编号名称

 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::ProcAction(
    BST_DSPP_HEAD_STRU             *const pstRxHeadInfo,
    BST_DSPP_OFSTADDR_T             usOfstAddr,
    BST_DSPP_OBJTADDR_T             usObjtAddr )
{
    BST_ERR_ENUM_UINT8              enRtnVal;
    BST_DSPP_CAppUlVa              *pcUlProc;

    enRtnVal                        = BST_ERR_UNKNOW_ACT;
    switch ( pstRxHeadInfo->stCpVerA.ucActType )
    {
        /*
         * 添加任务
         */
        case BST_ACTION_ADD:
            enRtnVal                = m_pcTaskManager->Create( usObjtAddr, usOfstAddr );
                /*
                 * 在添加完成后，如果有数据，那么先假设该参数需要配置
                 */
            if( ( BST_NO_ERROR_MSG == enRtnVal )
             && ( 0 != pstRxHeadInfo->usLength )
             && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
            {
                enRtnVal            = Config( usObjtAddr, usOfstAddr, pstRxHeadInfo );
            }
            /*当添加任务失败时，直接删除该任务，防止后面继续配置参数导致异常*/
            if ( enRtnVal != BST_NO_ERROR_MSG )
            {
                BST_DBG_LOG2( "procId,taskId add fail,remove", usObjtAddr, usOfstAddr );
                Remove( usObjtAddr, usOfstAddr );
            }
            break;
        /*
         * 删除任务
         */
        case BST_ACTION_REMOVE:
            enRtnVal                = Remove ( usObjtAddr, usOfstAddr ) ;
            break;
        /*
         * 开始任务，如果有参数需要先配置，而后启动任务运行
         */
        case BST_ACTION_START:
            if( ( 0 != pstRxHeadInfo->usLength )
             && ( BST_NULL_PTR != pstRxHeadInfo->pucData ) )
            {
                /*
                 * 如果配置失败，则Start动作可能引起系统异常，因此不可启动
                 */
                enRtnVal            = Config( usObjtAddr, usOfstAddr, pstRxHeadInfo );
                if ( BST_NO_ERROR_MSG == enRtnVal )
                {
                    enRtnVal        = m_pcTaskManager->Start ( usObjtAddr, usOfstAddr );
                }
            }
            else
            {
                enRtnVal            = m_pcTaskManager->Start ( usObjtAddr, usOfstAddr );
            }
            break;
        /*
         * 停止任务运行
         */
        case BST_ACTION_STOP:
            enRtnVal                = m_pcTaskManager->Stop ( usObjtAddr, usOfstAddr );
            break;

        /*
         * 查询参数
         */
        case BST_ACTION_INQUIRE:
            if ( BST_NULL_PTR != pstRxHeadInfo->pucData )
            {
                enRtnVal                = Inquire ( usObjtAddr, usOfstAddr, pstRxHeadInfo );
                if(BST_NO_ERROR_MSG != enRtnVal)
                {
                    BST_DBG_LOG1 ( "BST_DSPP_CAppDlVa::inquire error:%d",enRtnVal);
                    pstRxHeadInfo->pucData  = BST_NULL_PTR;
                    pstRxHeadInfo->usLength = 0;
                }
            }
            else
            {
                enRtnVal                = BST_ERR_LAYER_VER;
                pstRxHeadInfo->pucData  = BST_NULL_PTR;
                pstRxHeadInfo->usLength = 0;
            }
            break;
        /*
         * 设置参数
         */
        case BST_ACTION_CONFIG:
            if ( BST_NULL_PTR != pstRxHeadInfo->pucData )
            {
                enRtnVal            = Config ( usObjtAddr, usOfstAddr, pstRxHeadInfo ) ;
            }
            else
            {
                enRtnVal            = BST_ERR_LAYER_VER;
            }
            break;

        default:
            enRtnVal                = BST_ERR_PAR_UNKNOW;
            BST_DBG_LOG ( "BST_DSPP_CAppDlVa::ProcAction Error, Unknow Action" );
            break;
    }

    if ( BST_ACTION_INQUIRE != pstRxHeadInfo->stCpVerA.ucActType )
    {
        pstRxHeadInfo->pucData      = BST_NULL_PTR;
        pstRxHeadInfo->usLength     = 0;
    }
    BST_OS_FREE( pstRxHeadInfo->pucSource );
    /*
     * 应答S端ACTION结果
     */
    pcUlProc                        = BST_DSPP_CAppUlVa::GetInstance ();
    enRtnVal                        = pcUlProc->Response( pstRxHeadInfo, enRtnVal );
    return enRtnVal;
}
/***************************************************************
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
***************************************************************/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVa::UnpackInternal(
    BST_DSPP_HEAD_STRU         *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_DSPP_CAppUlVa          *pcUlProc;
    BST_OS_MBX_T               *pstRcver;
    BST_ERR_ENUM_UINT8          enRtnVal;

    pcUlProc                    = BST_DSPP_CAppUlVa::GetInstance ();
    enRtnVal                    = BST_NO_ERROR_MSG;

    /*
     * 入口检查
     */
    BST_ASSERT_NULL_RTN ( pstRxHeadInfo, BST_ERR_INVALID_PTR);
    BST_ASSERT_NULL_RTN ( pcUlProc, BST_ERR_INVALID_PTR);
    if ( BST_NULL_PTR == m_pcTaskManager )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_INVALID_PTR ) );
    }
    if ( BST_DSPP_VER_A != pstRxHeadInfo->enCpVer )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
        return ( pcUlProc->Response ( pstRxHeadInfo, BST_ERR_LAYER_VER ) );
    }
    /*
     * 如果是添加新任务，那么首先需要分配线程资源，而后在APP线程完成构建
     */
    if ( BST_ACTION_ADD == pstRxHeadInfo->stCpVerA.ucActType )
    {
        /*
         * 为新任务分配线程资源
         */
        enRtnVal                    = Assign ( pstRxHeadInfo, &pstRcver );
    }
    else
    {
        pstRcver                    = BST_SRV_GetTaskMsgHandle(
                                      pstRxHeadInfo->stCpVerA.usObjtAddr,
                                      pstRxHeadInfo->stCpVerA.usOfstAddr );
    }
    /*
     * 如果返回出错或者没有任务接收入口，那么视为失败，无需应用线程参与，直接回复S
     */
    if( ( BST_NO_ERROR_MSG != enRtnVal )
      ||( BST_NULL_PTR == pstRcver ) )
    {

        BST_OS_FREE( pstRxHeadInfo->pucSource );
        pstRxHeadInfo->usLength     = 0;
        pstRxHeadInfo->pucData      = BST_NULL_PTR;
        /*
         * 应答S端ACTION结果失败
         */
        enRtnVal                    = pcUlProc->Response( pstRxHeadInfo, enRtnVal );
    }
    else
    {
        BST_SRV_ApiSendDsppEvent(
            pstRxHeadInfo->stCpVerA.ucActType,
            BST_DSPP_VER_A,
            BST_OS_SIZEOF(BST_DSPP_HEAD_STRU),
            pstRxHeadInfo,
            pstRcver );
    }
    return enRtnVal;
}
/*lint +e438*/
/***************************************************************
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
***************************************************************/
BST_DSPP_CDlLayerBase *BST_DSPP_CAppDlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    return BST_NULL_PTR;
}

/***************************************************************
 函 数 名   : GetPointer
 功能描述   : 获取BST_DSPP_CAppDlVa类指针
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_DSPP_CAppDlVa类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVa *BST_DSPP_CAppDlVa::GetInstance( BST_VOID )
{
    static BST_DSPP_CAppDlVa   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CAppDlVa ();
    }
    return s_pInstance;
}

/***************************************************************
 函 数 名   : Response
 功能描述   : 应答
 输入参数   : pstOrigHeadInfo: 包头结构体指针
              enErrMsg: 需要应答返回的错误信息
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Response(
    BST_DSPP_HEAD_STRU   *const pstOrigHeadInfo,
    BST_ERR_ENUM_UINT8    enErrMsg )
{
    BST_UINT8          *pucSdu;
    pucSdu             = BST_NULL_PTR;

    /*
     * 入口检查
     */
    if ( BST_NULL_PTR == pstOrigHeadInfo )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * 校验协议版本类型是否合法
     */
    if ( !BST_DSPP_IsVersionValid ( pstOrigHeadInfo->enCpVer ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * 填写DSPP结构体内容，类型为RESPONSE
     */
    pstOrigHeadInfo->enTpVer        = BST_DSPP_VER_VOID;
    pstOrigHeadInfo->enPrmvType     = BST_DSPP_PRMTV_RESPONSE;

    /*
     * 如果源应答缓冲区有数据，那么申请空间也涵盖
     */
    if ( ( BST_NULL_PTR != pstOrigHeadInfo->pucData )
      && ( 0 != pstOrigHeadInfo->usLength ) )
    {
        pstOrigHeadInfo->enApVer= BST_DSPP_VER_A;
        pucSdu                  = ( BST_UINT8 * )BST_OS_MALLOC
                                  ( pstOrigHeadInfo->usLength+BST_DSPP_CPA_HEAD_LENGTH );
        if ( BST_NULL_PTR == pucSdu )
        {
            BST_OS_FREE( pstOrigHeadInfo->pucData );
            return BST_ERR_NO_MEMORY;
        }
        BST_OS_MEMCPY( &pucSdu[BST_DSPP_APA_OFFSET_ADDR],
                        pstOrigHeadInfo->pucData,
                        pstOrigHeadInfo->usLength );
        BST_OS_FREE( pstOrigHeadInfo->pucData );
        pstOrigHeadInfo->pucData    = pucSdu;
    }
    /*
     * 如果应对为空白，直接申请DSPP头长度即可
     */
    else
    {
        pstOrigHeadInfo->enApVer    = BST_DSPP_VER_VOID;
        pstOrigHeadInfo->usLength   = 0;
        pstOrigHeadInfo->pucData    = ( BST_UINT8 * )
                                      BST_OS_MALLOC ( BST_DSPP_CPA_HEAD_LENGTH );
        if ( BST_NULL_PTR == pstOrigHeadInfo->pucData )
        {
            return BST_ERR_NO_MEMORY;
        }
    }

    switch ( pstOrigHeadInfo->enCpVer )
    {
        case BST_DSPP_VER_A:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        case BST_DSPP_VER_B:
            pstOrigHeadInfo->stCpVerA.ucActType
                                    = enErrMsg;
            break;

        default:
            break;
    }
    /*
     * 传入下一层进行封包
     */
    return ( Pack ( pstOrigHeadInfo ) );
}

/***************************************************************
 函 数 名   : Report
 功能描述   : 报告命令消息
 输入参数   : usObjtAdd: 代理类型(Email/HeartBeat/MainTask)
              usOfstAdd: task ID, modem具体任务
              usCmdLen: 命令长度
              enCmdId: 命令ID
              pucCmdData: 命令数据段头指针
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T      usObjtAddr,
    BST_DSPP_OFSTADDR_T      usOfstAddr,
    BST_DSPP_CMDLEN_T        usCmdLen,
    BST_CORE_PID_ENUM_UINT16 enCmdId,
    BST_UINT8               *pucCmdData )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                             = BST_NULL_PTR;
    /*
     * 入口检查
     */
    if ( ( 0 == usCmdLen )
      || ( BST_NULL_PTR == pucCmdData ) )
    {
        return BST_ERR_INVALID_PTR;
    }
    /*
     * 校验类型、地址值是否有效
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }

    /*
     * 获取上报缓冲
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC ( usCmdLen
                                        + BST_DSPP_AP_CMD_HEAD_LEN + BST_DSPP_CPA_HEAD_LENGTH );
    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * 填写SDU-AP层信息
     */
    stTxHeadInfo.pucData                = pucSdu;
    pucSdu                             += BST_DSPP_APA_OFFSET_ADDR;
    pucSdu[BST_DSPP_AP_CMD_LEN_L]       = BST_DSPP_U16_TO_U8L
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_LEN_H]       = BST_DSPP_U16_TO_U8H
                                        ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    pucSdu[BST_DSPP_AP_CMD_ID_L]        = BST_DSPP_U16_TO_U8L ( enCmdId );
    pucSdu[BST_DSPP_AP_CMD_ID_H]        = BST_DSPP_U16_TO_U8H ( enCmdId );
    BST_OS_MEMCPY ( pucSdu + BST_DSPP_AP_CMD_HEAD_LEN, pucCmdData, usCmdLen );

    /*
     * 填写DSPP结构体，选择协议版本，供下层使用
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = ( usCmdLen + BST_DSPP_AP_CMD_HEAD_LEN );
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = BST_ACTION_REPORT;

    return ( Pack ( &stTxHeadInfo ) );
}
/***************************************************************
 函 数 名   : Report
 功能描述   : 报告错误消息
 输入参数   : usObjtAddr: 代理类型(Email/HeartBeat/MainTask)
              usOfstAddr: task ID, modem具体任务
              enErr: 要报告的错误信息
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::Report(
    BST_DSPP_OBJTADDR_T usObjtAddr,
    BST_DSPP_OFSTADDR_T usOfstAddr,
    BST_ERR_ENUM_UINT8  enErr )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;

    /*
     * 入口检查
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        return BST_ERR_UNREACHABLE;
    }
    stTxHeadInfo.pucData                = ( BST_UINT8 * )
                                          BST_OS_MALLOC ( BST_DSPP_CPA_HEAD_LENGTH );
    if ( BST_NULL_PTR == stTxHeadInfo.pucData )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * 填写DSPP结构体，选择协议版本，供下层使用
     */
    stTxHeadInfo.pucSource              = stTxHeadInfo.pucData;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_VOID;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.usLength               = 0;
    stTxHeadInfo.stCpVerA.usObjtAddr    = usObjtAddr;
    stTxHeadInfo.stCpVerA.usOfstAddr    = usOfstAddr;
    stTxHeadInfo.stCpVerA.ucActType     = enErr;
    return ( Pack ( &stTxHeadInfo ) );
}

/***************************************************************
 函 数 名   : GetPointer
 功能描述   : 获取BST_DSPP_CAppUlVa类指针
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_DSPP_CAppUlVa类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVa *BST_DSPP_CAppUlVa::GetInstance ( BST_VOID )
{
    static BST_DSPP_CAppUlVa           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CAppUlVa ();
    }

    return s_pInstance;
}

/***************************************************************
 函 数 名   : BST_DSPP_CAppUlVa
 功能描述   : BST_DSPP_CAppUlVa类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVa::BST_DSPP_CAppUlVa ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{

}
/***************************************************************
 函 数 名   : ~BST_DSPP_CAppUlVa
 功能描述   : BST_DSPP_CAppUlVa类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年06月04日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVa::~BST_DSPP_CAppUlVa ( BST_VOID )
{

}
/***************************************************************
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
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVa::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if ( BST_NULL_PTR != penNextVer )
    {
        *penNextVer                          = pstTxHeadInfo->enCpVer;
    }
    return BST_NO_ERROR_MSG;
}

/***************************************************************
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
***************************************************************/
BST_DSPP_CUlLayerBase *BST_DSPP_CAppUlVa::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_A:
            return ( BST_DSPP_CCtrUlVa::GetInstance() );

        case BST_DSPP_VER_C:
            return ( BST_DSPP_CCtrUlVc::GetInstance() );
        default:
            break;
    }
    return BST_NULL_PTR;
}
/***************************************************************
 函 数 名   : BST_PbufStatusCallBack
 功能描述   : pbuf内存状态回调函数
 输入参数   : usStatus   0   内存不足
                        1....内存充足
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年08月05日
   作    者 : z00128442
   修改内容 : 新增函数
***************************************************************/
BST_VOID BST_PbufStatusCallBack( BST_UINT16 usStatus )
{
    BST_DSPP_CAppUlVc::GetInstance()->ReportBuffer( usStatus );
}

/***************************************************************
 函 数 名   : BST_DSPP_CAppDlVc
 功能描述   : BST_DSPP_CAppDlVc类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVc::BST_DSPP_CAppDlVc( BST_VOID )
    : BST_DSPP_CDlLayerBase( BST_DSPP_LAYER_APP, BST_DSPP_VER_C )
{
}

/***************************************************************
 函 数 名   : ~BST_DSPP_CAppDlVc
 功能描述   : BST_DSPP_CAppDlVc类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVc::~BST_DSPP_CAppDlVc( BST_VOID )
{
}

/***************************************************************
 函 数 名   : UnpackInternal
 功能描述   : 解析数据包
 输入参数   : pstRxHeadInfo: 包头结构体指针
              penNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月05日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppDlVc::UnpackInternal(
    BST_DSPP_HEAD_STRU         *const pstRxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const pstNextVer )
{
    BST_ERR_ENUM_UINT8          enRtnVal;
    BST_SRV_CHNL_HEAD_STRU     *pstPktHead;
    BST_OS_MBX_T               *pstRcver;
    /*
     * 入口检查
     */
    pstPktHead                  = BST_NULL_PTR;
    pstRcver                    = BST_NULL_PTR;
    if( BST_NULL_PTR == pstRxHeadInfo )
    {
        enRtnVal                = BST_ERR_INVALID_PTR;
        goto err_out;
    }
    if( BST_NULL_PTR == pstNextVer )
    {
        enRtnVal                = BST_ERR_INVALID_PTR;
        goto err_out;
    }
    enRtnVal                    = BST_NO_ERROR_MSG;

    pstPktHead              = BST_SRV_AlocIpBlock();

    if( BST_NULL_PTR == pstPktHead )
    {
        enRtnVal                = BST_ERR_NO_MEMORY;
        goto err_out;
    }
    pstPktHead->pNext           = BST_NULL_PTR;

    pstRcver                    = ParseHeadInfo( pstRxHeadInfo, pstPktHead );
    if( BST_NULL_PTR == pstRcver )
    {
        enRtnVal                = BST_ERR_LAYER_VER;
        goto err_out;
    }

    pstRxHeadInfo->usLength     = 0;
    pstRxHeadInfo->pucData      = BST_NULL_PTR;
    BST_OS_FREE( pstRxHeadInfo->pucSource );

    BST_SRV_ApiSendDsppEvent(
        pstRxHeadInfo->enPrmvType,
        BST_DSPP_VER_C,
        BST_OS_SIZEOF(BST_SRV_CHNL_HEAD_STRU),
        pstPktHead,
        pstRcver );
    return BST_NO_ERROR_MSG;

err_out:
    if( BST_NULL_PTR != pstPktHead )
    {
        BST_SRV_FreeIpBlock(pstPktHead);
    }
    if( BST_NULL_PTR != pstRxHeadInfo )
    {
        BST_OS_FREE( pstRxHeadInfo->pucSource );
    }
    return enRtnVal;
}
/*lint +e438*/


/***************************************************************
 函 数 名   : ParseHeadInfo
 功能描述   : 解析包头信息
 输入参数   : BST_DSPP_HEAD_STRU     *const pstDsppHead, DSPP头
              BST_SRV_CHNL_HEAD_STRU *pstChnHead    信道信息头
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年04月16日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_OS_MBX_T  *BST_DSPP_CAppDlVc::ParseHeadInfo(
    BST_DSPP_HEAD_STRU     *const pstDsppHead,
    BST_SRV_CHNL_HEAD_STRU *pstChnHead )
{
    BST_UINT16                  usLength;
    BST_UINT8                  *pucData;
    BST_OS_MBX_T               *pstRcver;

    /*
     * 入口检查
     */
    BST_ASSERT_NULL_RTN( pstDsppHead, BST_NULL_PTR );
    BST_ASSERT_NULL_RTN( pstChnHead, BST_NULL_PTR );
    pucData                     = pstDsppHead->pucData;
    usLength                    = pstDsppHead->usLength;
   /*
    * 获取IP Address
    */
    if ( BST_DSPP_FLG_ADDTYPE_INET == pstDsppHead->stCpVerC.ucAddrType )
    {
        if( usLength < BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) )
        {
            return BST_NULL_PTR;
        }
        BST_OS_MEMCPY( &pstChnHead->stAddr.stInet, pucData, BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T ) );
        pucData                += BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T );
        usLength               -= BST_OS_SIZEOF( BST_IP_SOCKET_ADD_T );
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_INET;
        pstRcver                = BST_SRV_GetChnlCtrlHandle( 0 );
    }
    else if( BST_DSPP_FLG_ADDTYPE_TASK == pstDsppHead->stCpVerC.ucAddrType )
    {
        if( usLength < BST_OS_SIZEOF( pstChnHead->stAddr.stTask ) )
        {
            return BST_NULL_PTR;
        }

        pstChnHead->stAddr.stTask.usProcId
                                = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OBJT_ADD_L],
                                                      pucData[BST_DSPP_CP_OBJT_ADD_H] );
        pstChnHead->stAddr.stTask.usTaskId
                                = BST_DSPP_U8_TO_U16( pucData[BST_DSPP_CP_OFST_ADD_L],
                                                      pucData[BST_DSPP_CP_OFST_ADD_H] );
        pucData                += BST_OS_SIZEOF( pstChnHead->stAddr.stTask );
        usLength               -= BST_OS_SIZEOF( pstChnHead->stAddr.stTask );
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_TASK;
        pstRcver                = BST_SRV_GetTaskMsgHandle(
                                    pstChnHead->stAddr.stTask.usProcId,
                                    pstChnHead->stAddr.stTask.usTaskId );

    }
    else
    {
        pstChnHead->ucAddrType  = BST_DSPP_FLG_ADDTYPE_VOID;
        pstRcver                = BST_SRV_GetChnlCtrlHandle( 0 );
    }

    BST_ASSERT_NULL_RTN( pstRcver, BST_NULL_PTR );
   /*
    * 获取Socket property
    */

    BST_OS_MEMSET( &pstChnHead->stProp, 0, BST_OS_SIZEOF(BST_IP_SKT_PROPTY_STRU) );
    switch( pstDsppHead->stCpVerC.ucPropType )
    {
        case BST_IP_SKT_PROP_NONE:        /*0 没有property*/
        break;

        case BST_IP_SKT_PROP_SEQNO:       /*1 只有seqno*/
            if( usLength < BST_OS_SIZEOF( BST_UINT32 ) )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp.ulSeqNum, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
        break;

        case BST_IP_SKT_PROP_SEQNO_TS:    /* 2 只有seqno+timestamp */
            if( usLength < BST_OS_SIZEOF( BST_UINT32 )*2 )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp.ulSeqNum, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
            BST_OS_MEMCPY( &pstChnHead->stProp.ulTsCurrent, pucData, BST_OS_SIZEOF(BST_UINT32) );
            pucData            += BST_OS_SIZEOF( BST_UINT32 );
            usLength           -= BST_OS_SIZEOF( BST_UINT32 );
        break;

        case BST_IP_SKT_PROP_TOTAL:       /*3 完整property*/
            if( usLength < BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU ) )
            {
                return BST_NULL_PTR;
            }
            BST_OS_MEMCPY( &pstChnHead->stProp, pucData, BST_OS_SIZEOF(BST_IP_SKT_PROPTY_STRU) );
            pucData            += BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU );
            usLength           -= BST_OS_SIZEOF( BST_IP_SKT_PROPTY_STRU );
        break;

        default:                            /*4 无效*/
             return BST_NULL_PTR;
        break;
    }
    pstChnHead->ucPropType      = pstDsppHead->stCpVerC.ucPropType;

   /*
    *识别Send时候Buffer使用情况
    */
    if( BST_DSPP_FLG_CMD_SEND == pstDsppHead->stCpVerC.usCmdId )
    {
        if( ( usLength == 0 ) || ( usLength > BST_SRV_BLOCK_SIZE ) )
        {
            return BST_NULL_PTR;
        }
        pstChnHead->ulUsed      = usLength;
        BST_OS_MEMCPY( &pstChnHead->aucData[0], pucData, usLength );
    }
    else
    {
        pstChnHead->ulUsed      = 0;
    }
    pstChnHead->ulMainLinkId    = pstDsppHead->stCpVerC.ulMainLinkId;
    pstChnHead->ulAuxLinkId     = pstDsppHead->stCpVerC.ulAuxLinkId;
    pstChnHead->usCmdId         = pstDsppHead->stCpVerC.usCmdId;
    pstChnHead->usProcLevel     = pstDsppHead->stCpVerC.usProcLevel;
    pstChnHead->ucIpProtocol    = pstDsppHead->stCpVerC.ucIpProtocol;
    pstChnHead->ucPktAddr       = pstDsppHead->stCpVerC.ucPktAddr;
    return pstRcver;
}

/***************************************************************
 函 数 名   : GetNextStrategy
 功能描述   : 获取下一层解析策略
 输入参数   : enNextVer: 下一个协议版本
 输出参数   : 无
 返 回 值   : BST_DSPP_CDlLayerBase类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月05日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CDlLayerBase *BST_DSPP_CAppDlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    return BST_NULL_PTR;
}

/***************************************************************
 函 数 名   : GetPointer
 功能描述   : 获取BST_DSPP_CAppDlVc类指针
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_DSPP_CAppDlVc类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月05日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppDlVc *BST_DSPP_CAppDlVc::GetInstance( BST_VOID )
{
    static BST_DSPP_CAppDlVc   *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance             = new BST_DSPP_CAppDlVc ();
    }
    return s_pInstance;
}

/***************************************************************
 函 数 名   : ProcAction
 功能描述   : 根据解析的ACTION类型，分散调用各入口
 输入参数   :
    BST_SRV_CHNL_HEAD_STRU *const pstChnHead,   链路分级数据入口

 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 修改历史   :
 1.日    期 : 2015年05月05日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8 BST_DSPP_CAppDlVc::ProcAction(
    BST_SRV_CHNL_HEAD_STRU     *pstChnHead )
{
    BST_CORE_CRegedit          *m_pcRegedit;
    BST_ERR_ENUM_UINT8          enRtnVal = BST_NO_ERROR_MSG;

    BST_ASSERT_NULL_RTN( pstChnHead, BST_ERR_INVALID_PTR );

    BST_DBG_LOG1( "CPC_PACKET_DROP usAddrType", pstChnHead->ucAddrType );
    if ( BST_DSPP_FLG_ADDTYPE_INET == pstChnHead->ucAddrType )
    {
        enRtnVal                        = BST_SRV_CHNL_Itf( pstChnHead );
    }
    else if( BST_DSPP_FLG_ADDTYPE_TASK == pstChnHead->ucAddrType )
    {
        m_pcRegedit                     = BST_CORE_CRegedit::GetInstance();

        BST_ASSERT_NULL_RTN( pstChnHead, BST_ERR_INVALID_PTR );
        enRtnVal                        = m_pcRegedit->ChnlCtrl(
                                          pstChnHead->stAddr.stTask.usProcId,
                                          pstChnHead->stAddr.stTask.usTaskId,
                                          pstChnHead );
    }
    else
    {
        BST_SRV_FreeIpBlock( pstChnHead );
        enRtnVal                        = BST_ERR_UNKNOW_OBJ;
    }

    return enRtnVal;
}

/***************************************************************
 函 数 名   : Report(以任务为对象)
 功能描述   : 报告命令消息
 输入参数   : enCmdId,      AP_C命令ID
              ulLinkId0     LinkId Main部分
              ulLinkId1     LinkId Aux部分
              usObjtAddr    对应CP_A版本的ProcId
              usOfstAddr    对应CP_A版本的TaskId
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1,
    BST_DSPP_OBJTADDR_T         usObjtAddr,
    BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;
    BST_UINT32                          ulSduLen;
    BST_BOOL                            bUseTaskId;

    pucSdu                              = BST_NULL_PTR;
    bUseTaskId                          = BST_TRUE;
    ulSduLen                            = 0;

    /*
     * 校验类型、地址值是否有效
     */
    if ( (!BST_DSPP_IsObjIdValid ( usObjtAddr ) )
      || ( BST_DSPP_INVALID_ADDR == usOfstAddr ) )
    {
        if ( ( BST_DSPP_INVALID_LINK_ID == ulLinkId0 )
          || ( BST_DSPP_INVALID_LINK_ID == ulLinkId1 ) )
        {
            return BST_ERR_UNREACHABLE;
        }
        bUseTaskId                      = BST_FALSE;
        ulSduLen                        = BST_DSPP_CPC_HEAD_LENGTH;
    }
    else
    {
        bUseTaskId                      = BST_TRUE;
        ulSduLen                        = BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_APC_ADDRESS_LEN;
    }

    /*
     * 获取上报缓冲
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC( ulSduLen );
    if ( BST_NULL_PTR == pucSdu )
    {
        return BST_ERR_NO_MEMORY;
    }
    /*
     * 填写SDU-AP层信息
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    if( BST_TRUE == bUseTaskId )
    {
        pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
        pucSdu[BST_DSPP_APC_PROCID_ADD_L]   = BST_DSPP_U16_TO_U8L
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_PROCID_ADD_H]   = BST_DSPP_U16_TO_U8H
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_TASKID_ADD_L]   = BST_DSPP_U16_TO_U8L
                                            ( usObjtAddr );
        pucSdu[BST_DSPP_APC_TASKID_ADD_H]   = BST_DSPP_U16_TO_U8H
                                            ( usObjtAddr );
        stTxHeadInfo.usLength               = BST_DSPP_APC_ADDRESS_LEN;
        stTxHeadInfo.stCpVerC.ulMainLinkId  = BST_DSPP_COMMON_LINK_ID;
        stTxHeadInfo.stCpVerC.ulAuxLinkId   = BST_DSPP_COMMON_LINK_ID;
        stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_TASK;
    }
    else
    {
        stTxHeadInfo.usLength               = 0;
        stTxHeadInfo.stCpVerC.ulMainLinkId  = ulLinkId0;
        stTxHeadInfo.stCpVerC.ulAuxLinkId   = ulLinkId1;
        stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    }
    /*
     * 填写DSPP结构体，选择协议版本，供下层使用
     */
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = enCmdId;
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    return ( Pack ( &stTxHeadInfo ) );
}

/***************************************************************
 函 数 名   : Report(以任务为对象)
 功能描述   : 报告命令消息
 输入参数   : enCmdId,      AP_C命令ID
              ulLinkId0     LinkId Main部分
              ulLinkId1     LinkId Aux部分
              usObjtAddr    对应CP_A版本的ProcId
              usOfstAddr    对应CP_A版本的TaskId
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_OBJTADDR_T         usObjtAddr,
    BST_DSPP_OFSTADDR_T         usOfstAddr )
{
    return Report( enCmdId,
                   BST_DSPP_INVALID_LINK_ID, BST_DSPP_INVALID_LINK_ID,
                   usObjtAddr, usOfstAddr );

}
/***************************************************************
 函 数 名   : Report(以LinkId为对象)
 功能描述   : 报告错误消息
 输入参数   : enCmdId,      AP_C命令ID
              ulLinkId0     LinkId Main部分
              ulLinkId1     LinkId Aux部分
 输出参数   : 无
 返 回 值   : BST_ERR_ENUM_UINT8
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::Report(
    BST_DSPP_FLG_CMD_ENUM_UINT8 enCmdId,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1 )
{
    return Report( enCmdId, ulLinkId0, ulLinkId1,
                   BST_DSPP_INVALID_ADDR,
                   BST_DSPP_INVALID_ADDR );
}
/*****************************************************************************
 函 数 名   : ReportBuffer
 功能描述   : 打包数据包
 输入参数   : ulBufferNumber: 上报剩余buffer数量
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月11日
   作    者 : z00220931
   修改内容 : 创建函数
*****************************************************************************/
BST_VOID BST_DSPP_CAppUlVc::ReportBuffer( BST_UINT16 ulBufferStatus )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                              = BST_NULL_PTR;

    /*
     * 获取上报缓冲
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC(
                                          BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_CPC_BUFFER_NUM_LEN );
    if ( BST_NULL_PTR == pucSdu )
    {
        return;
    }

    /*
     * 填写SDU-AP层信息
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
    pucSdu[BST_DSPP_CPC_BUFFER_NUM_0]   = BST_DSPP_U16_TO_U8L
                                        ( ulBufferStatus );
    pucSdu[BST_DSPP_CPC_BUFFER_NUM_1]   = BST_DSPP_U16_TO_U8H
                                        ( ulBufferStatus );
    stTxHeadInfo.usLength               = BST_DSPP_CPC_BUFFER_NUM_LEN;
    stTxHeadInfo.stCpVerC.ulMainLinkId  = BST_DSPP_COMMON_LINK_ID;
    stTxHeadInfo.stCpVerC.ulAuxLinkId   = BST_DSPP_COMMON_LINK_ID;
    stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = BST_DSPP_FLG_CMD_BUFFER;
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    Pack( &stTxHeadInfo );
}
/*****************************************************************************
 函 数 名   : ReportFlow
 功能描述   : 上报IP型高优先级数据的流量
 输入参数   : stFlowInfo: 上报流量的结构体
             ulLinkId0 ： MainLinkID
             ulLinkId1 ： AuxLinkID
 输出参数   : 无
 返 回 值   : 无
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2015年05月11日
   作    者 : z00220931
   修改内容 : 创建函数
*****************************************************************************/
BST_VOID BST_DSPP_CAppUlVc::ReportFlow(
    BST_IP_TRAFFIC_FLOW_STRU   *pstFlowInfo,
    BST_DSPP_LINKID1_T          ulLinkId0,
    BST_DSPP_LINKID1_T          ulLinkId1 )
{
    BST_DSPP_HEAD_STRU                  stTxHeadInfo;
    BST_UINT8                          *pucSdu;

    pucSdu                              = BST_NULL_PTR;

    /*
     * 获取上报缓冲
     */
    pucSdu                              = ( BST_UINT8 * )BST_OS_MALLOC(
                                          BST_DSPP_CPC_HEAD_LENGTH
                                        + BST_DSPP_CPC_FLOW_NUM_LEN );
    if ( BST_NULL_PTR == pucSdu )
    {
        return;
    }

    /*
     * 填写SDU-AP层信息
     */
    stTxHeadInfo.pucData                = pucSdu;
    stTxHeadInfo.pucSource              = pucSdu;

    pucSdu                             += BST_DSPP_APC_OFFSET_ADDR;
    pucSdu[BST_DSPP_CPC_FLOW_NUM_0]   = BST_DSPP_U32_TO_U8_0
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_1]   = BST_DSPP_U32_TO_U8_1
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_2]   = BST_DSPP_U32_TO_U8_2
                                        ( pstFlowInfo->ulTxByte );
    pucSdu[BST_DSPP_CPC_FLOW_NUM_3]   = BST_DSPP_U32_TO_U8_3
                                        ( pstFlowInfo->ulTxByte );

    stTxHeadInfo.usLength               = BST_DSPP_CPC_FLOW_NUM_LEN;
    stTxHeadInfo.stCpVerC.ulMainLinkId  = ulLinkId0;
    stTxHeadInfo.stCpVerC.ulAuxLinkId   = ulLinkId1;
    stTxHeadInfo.stCpVerC.ucAddrType    = BST_DSPP_FLG_ADDTYPE_VOID;
    stTxHeadInfo.enCpVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enApVer                = BST_DSPP_VER_C;
    stTxHeadInfo.enTpVer                = BST_DSPP_VER_A;
    stTxHeadInfo.enPrmvType             = BST_DSPP_PRMTV_REPORT;
    stTxHeadInfo.usPktNum               = BST_DSPP_TP_INVALID_PKTNUM;
    stTxHeadInfo.stCpVerC.usCmdId       = BST_DSPP_FLG_CMD_TRAFFIC; /*流量*/
    stTxHeadInfo.stCpVerC.ucIpProtocol  = BST_DSPP_FLG_PROTYPE_TCP;
    stTxHeadInfo.stCpVerC.usProcLevel   = BST_DSPP_FLG_LVLTYPE_NORMAL;
    stTxHeadInfo.stCpVerC.ucPropType    = BST_IP_SKT_PROP_NONE;
    stTxHeadInfo.stCpVerC.ucPktAddr     = BST_DSPP_FLG_PKTADDR_SINGLE;
    Pack( &stTxHeadInfo );
}

/***************************************************************
 函 数 名   : GetInstance
 功能描述   : 获取BST_DSPP_CAppUlVc类指针
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_DSPP_CAppUlVc类指针
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVc *BST_DSPP_CAppUlVc::GetInstance ( BST_VOID )
{
    static BST_DSPP_CAppUlVc           *s_pInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == s_pInstance )
    {
        s_pInstance                     = new BST_DSPP_CAppUlVc ();
    }

    return s_pInstance;
}

/***************************************************************
 函 数 名   : BST_DSPP_CAppUlVc
 功能描述   : BST_DSPP_CAppUlVc类的构造函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVc::BST_DSPP_CAppUlVc ( BST_VOID )
    : BST_DSPP_CUlLayerBase ( BST_DSPP_LAYER_APP, BST_DSPP_VER_A )
{
    /*注册pbuf类型内存状态回调函数*/
    BST_OS_RegisgerMemStatus(BST_MEM_TYPE_PBUF,BST_PbufStatusCallBack);
}
/***************************************************************
 函 数 名   : ~BST_DSPP_CAppUlVc
 功能描述   : BST_DSPP_CAppUlVc类的析构函数
 输入参数   : BST_VOID
 输出参数   : 无
 返 回 值   : BST_VOID
 被调函数   :
 调用函数   :

 修改历史   :
 1.日    期 : 2014年05月11日
   作    者 : d00173029
   修改内容 : 创建文件
***************************************************************/
BST_DSPP_CAppUlVc::~BST_DSPP_CAppUlVc ( BST_VOID )
{

}
/***************************************************************
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
***************************************************************/
BST_ERR_ENUM_UINT8  BST_DSPP_CAppUlVc::PackInternal(
    BST_DSPP_HEAD_STRU         *const pstTxHeadInfo,
    BST_DSPP_VERION_ENUM_UINT8 *const penNextVer )
{
    if ( BST_NULL_PTR == pstTxHeadInfo )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if ( BST_NULL_PTR != penNextVer )
    {
       *penNextVer                          = pstTxHeadInfo->enCpVer;
    }
    return BST_NO_ERROR_MSG;
}

/***************************************************************
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
***************************************************************/
BST_DSPP_CUlLayerBase *BST_DSPP_CAppUlVc::GetNextStrategy(
    BST_DSPP_VERION_ENUM_UINT8 enNextVer )
{
    switch ( enNextVer )
    {
        case BST_DSPP_VER_C:
            return BST_DSPP_CCtrUlVc::GetInstance();
        default:
            break;
    }
    return BST_NULL_PTR;
}
