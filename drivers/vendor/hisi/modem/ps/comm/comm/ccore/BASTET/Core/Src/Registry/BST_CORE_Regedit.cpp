/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_CORE_Regedit.cpp
  版 本 号   : V1.1
  作    者   : d00173029
  生成日期   : 2014年6月10日
  最近修改   :
  功能描述   : 注册表相关处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2014年06月10日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_Regedit.h"
#include "BST_DBG_MemLeak.h"
#include "BST_OS_Memory.h"
#include "BST_DSPP_Define.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_REGEDIT_CPP
/*lint +e767*/
/******************************************************************************
   2 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : GetInstance
 功能描述  : 单例模式，获取注册表的实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回BST_CORE_CRegedit实例化指针
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_CRegedit *BST_CORE_CRegedit::GetInstance ( BST_VOID )
{
    static BST_CORE_CRegedit           *pcInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == pcInstance )
    {
        pcInstance                      = new BST_CORE_CRegedit;
    }
    return pcInstance;
}
/*****************************************************************************
 函 数 名  : GetLen
 功能描述  : 获取PID对应参数的长度
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             enParamId  :参数PID
 输出参数  : 无
 返 回 值  : 返回PID对应参数的长度
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT16 BST_CORE_CRegedit::GetLen(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_CORE_PID_ENUM_UINT16   enParamId )
{
    BST_CORE_PIDNODE_STRU             *pRegParam;

    pRegParam                           = Select ( usObjtAddr, usOfstAddr, enParamId );
    if ( BST_NULL_PTR == pRegParam )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::GetLen pRegParam=NULL" );
        return 0;
    }
    return pRegParam->stParamInfo.usLen;
}
/*****************************************************************************
 函 数 名  : Inquire
 功能描述  : 查询对应PID的值
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             enParamId  :参数PID
             usDataLen  :数据长度
             pData      :数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT16 BST_CORE_CRegedit::Inquire(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataSize,
    BST_VOID                 *const pData)
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_UINT16                      usInquireLen;

    if ( BST_NULL_PTR == pData )
    {
        return 0;
    }
    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    usInquireLen                    = 0;
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Inquire pstTaskNode=NULL" );
        return 0;
    }
    if ( BST_NULL_PTR == pstTaskNode->pcApAItf )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Inquire pcCallBack=NULL" );
        return 0;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        usInquireLen            = pstTaskNode->pcApAItf->Inquired
                                  ( enParamId, usDataSize, pData );
        if ( BST_CORE_INVALID_INQUIRED_LEN == usInquireLen )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: CallBack No Item Fail!" );
            return 0;
        }
        if ( 0 != usInquireLen )
        {
            return usInquireLen;
        }
        /* If the Call-back return 0, We will Try to find it in Pid Table */
        if ( 0 == pstPidNode->stParamInfo.usLen )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: usLen = 0!" );
            return 0;
        }
        if ( usDataSize < pstPidNode->stParamInfo.usLen )
        {
            BST_RLS_LOG2( "Regedit::Inquire Error: Size Fail! usData=u%, param_len=%u",\
                          usDataSize, pstPidNode->stParamInfo.usLen );
            return 0;
        }
        if ( BST_NULL_PTR == pstPidNode->stParamInfo.pvContent )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: pvContent Void!" );
            return 0;
        }
        BST_OS_MEMCPY ( pData, pstPidNode->stParamInfo.pvContent, pstPidNode->stParamInfo.usLen );
        return pstPidNode->stParamInfo.usLen;
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : Config
 功能描述  : 配置注册表的参数，重载函数
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             pstRegParam:注册表指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Config(
    BST_OBJT_ADDR_T             usObjtAddr,
    BST_OFST_ADDR_T             usOfstAddr,
    const BST_CORE_PID_STRU    *pstRegParam )
{
    if ( BST_NULL_PTR == pstRegParam )
    {
        return BST_ERR_INVALID_PTR;
    }
    return ( Config ( usObjtAddr,
                      usOfstAddr,
                      pstRegParam->enPid,
                      pstRegParam->usLen,
                      pstRegParam->pvContent ) );
}
/*****************************************************************************
 函 数 名  : Save
 功能描述  : 保持应用config相关参数信息
 输入参数  :
    BST_CORE_PIDNODE_STRU      *pstPid,     参数PID条目头信息，调用者保证有效
    BST_UINT16                  usDataLen,  输入数据长度
    BST_VOID                   *pData       输入缓冲区入口

 输出参数  : BST_ERR_ENUM_UINT8 errcode
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::Save(
    BST_CORE_CAPACallBack      *pCallBack,
    BST_CORE_PIDNODE_STRU      *pstPid,
    BST_UINT16                  usDataLen,
    BST_VOID                   *pData )
{
    BST_CORE_PID_LUT_STRU          *pstParamAttri;
    BST_UINT8                      *pNewData;
    BST_ERR_ENUM_UINT8              enRet;

    if ( BST_TRUE != InputCheck( pstPid->stParamInfo.enPid, usDataLen, pData ) )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Save InputCheck Err" );
        return BST_ERR_PAR_OVERRUN;
    }
    pstParamAttri                   = BST_CORE_GetPidHandle( pstPid->stParamInfo.enPid );
    if ( BST_NULL_PTR  == pstParamAttri )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Save BST_CORE_GetPidHandle Err" );
        return BST_ERR_INVALID_PTR;
    }

    if ( ( BST_NULL_PTR  == pstPid->stParamInfo.pvContent )
      || ( BST_CORE_PID_VAR_LEN == pstParamAttri->enLenType ) )
    {
        if ( BST_NULL_PTR == pCallBack )
        {
            BST_RLS_LOG( "BST_CORE_CRegedit::Save pstPid->pcCallBack=NULL" );
            return BST_ERR_INVALID_PTR;
        }
        enRet                   = pCallBack->Configed ( pstPid->stParamInfo.enPid,
                                                        usDataLen,
                                                        ( void * )pData,
                                                        &pNewData );
        if ( BST_NO_ERROR_MSG == enRet )
        {
            if ( BST_NULL_PTR != pNewData )
            {
                pstPid->stParamInfo.pvContent = pNewData;
                pstPid->stParamInfo.usLen     = usDataLen;
            }
        }
    }
    else if ( usDataLen == pstPid->stParamInfo.usLen )
    {
        if( ( BST_NULL_PTR != pCallBack )
          &&( BST_TRUE == pstPid->ulNotice ) )
        {
             enRet              = pCallBack->Configed ( pstPid->stParamInfo.enPid,
                                                        usDataLen,
                                                        ( void * )pData,
                                                        &pNewData );
        }
        else
        {
            BST_OS_MEMCPY ( pstPid->stParamInfo.pvContent, pData, usDataLen );
            enRet               = BST_NO_ERROR_MSG;
        }
    }
    else
    {
        BST_RLS_LOG2( "BST_CORE_CRegedit::Save usDataLen, pstPid->stParamInfo.usLen",
                      usDataLen, pstPid->stParamInfo.usLen );
        enRet                   = BST_ERR_PAR_LEN;
    }
    return enRet;
}

/*****************************************************************************
 函 数 名  : Config
 功能描述  : 配置对应PID的参数，重载函数
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             enParamId  :参数PID
             usDataLen  :数据长度
             pData      :数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Config(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataLen,
    BST_VOID                 *pData )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_ERR_ENUM_UINT8              enRet;
#ifdef BST_SSL_SUPPORT
    BST_UINT16                      usOutDataLen;
    BST_VOID                       *pOutData;
    BST_ERR_ENUM_UINT8              enDecryterCheck;
#endif

    enRet                               = BST_NO_ERROR_MSG;
    pstTaskNode                         = Select ( usObjtAddr, usOfstAddr );
#ifdef BST_SSL_SUPPORT
    usOutDataLen                        = 0;
    pOutData                            = BST_NULL_PTR;
    enDecryterCheck                     = BST_ERR_UNKNOW_OBJ;
#endif

    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
#ifdef   BST_SSL_SUPPORT
        enDecryterCheck                 = BST_CORE_DencryptChk
                                          ( enParamId, pData, usDataLen,
                                          &pOutData, &usOutDataLen );

        if ( ( BST_NO_ERROR_MSG == enDecryterCheck )
          && ( BST_NULL_PTR != pOutData )
          && ( 0 != usOutDataLen ) )
        {
            pData                       = pOutData;
            usDataLen                   = usOutDataLen;
        }
#endif

        enRet                           = Save
                                        ( pstTaskNode->pcApAItf,
                                          pstPidNode, usDataLen, pData );

#ifdef BST_SSL_SUPPORT
        if ( pOutData != BST_NULL_PTR )
        {
            BST_OS_FREE ( pOutData );
            pOutData                    = BST_NULL_PTR;
        }
#endif
        return enRet;
    }
    return BST_ERR_ITEM_NOT_EXISTED;
}

/*****************************************************************************
 函 数 名  : Update
 功能描述  : 更新对应PID的参数长度和内容
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             enParamId  :参数PID
             usDataLen  :数据长度
             pData      :数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Update(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataLen,
    BST_VOID                 *pData )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_CORE_PID_LUT_STRU          *pstParamAttri;

    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "CRegedit::Update Fail! Can't Find Task. " );
        return BST_ERR_INVALID_PTR;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        pstParamAttri               = BST_CORE_GetPidHandle ( enParamId );
        if ( BST_NULL_PTR  == pstParamAttri )
        {
            BST_RLS_LOG( "CRegedit::Update Fail! pstParamAttri INVALID_PTR " );
            return BST_ERR_INVALID_PTR;
        }
        if ( BST_CORE_PID_VAR_LEN == pstParamAttri->enLenType )
        {
            pstPidNode->stParamInfo.usLen    = usDataLen;
            pstPidNode->stParamInfo.pvContent= pData;
        }
        return BST_NO_ERROR_MSG;
    }
    BST_RLS_LOG( "CRegedit::Update Fail!ITEM_NOT_EXISTED " );
    return BST_ERR_ITEM_NOT_EXISTED;
}


/*****************************************************************************
 函 数 名  : Regist
 功能描述  : 注册一个任务的回调函数
 输入参数  : pTask      :   任务指针
             pCallBack  :   回调函数指针
             ulAPVersion:   AP层协议版本
 输出参数  : 无
 返 回 值  : BST_NO_ERROR_MSG :注册成功，其他为注册失败，返回相应的出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年05月10日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::Regist(
    BST_CTask                  *pTask, 
    BST_VOID                   *pAPInf,
    BST_UINT32                  ulAPVersion )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        pstTaskNode                     = (BST_CORE_REGNODE_STRU *)
                                          BST_OS_MALLOC ( BST_OS_SIZEOF ( BST_CORE_REGNODE_STRU ) );

        if ( BST_NULL_PTR == pstTaskNode )
        {
            return BST_ERR_NO_MEMORY;
        }

        pstTaskNode->pTask              = pTask;
        lstInit( &pstTaskNode->RegParamList );
        lstAdd( &m_RegistryList, (NODE *)pstTaskNode );
    }
    if( BST_DSPP_VER_A == ulAPVersion )
    {
        pstTaskNode->pcApAItf           = (BST_CORE_CAPACallBack *)pAPInf;
    }
    if( BST_DSPP_VER_C == ulAPVersion )
    {
        pstTaskNode->pcApCItf           = (BST_CORE_CAPCCallBack *)pAPInf;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : Regist
 功能描述  : 注册一个任务
 输入参数  : pTask     :任务指针
             ulNoticeFlag该PID是否通过pcCallBack回调
             enParamId :参数PID
             usLen     :参数PID长度
             pValue    :数据指针
 输出参数  : 无
 返 回 值  : BST_NO_ERROR_MSG :注册成功，其他为注册失败，返回相应的出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Regist(
    BST_CTask                *pTask,
    const BST_UINT32          ulNoticeFlag,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_CORE_PID_LEN_T        usLen,
    const void               *const pValue )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstNewRegItem;
    BST_CORE_PID_LUT_STRU              *pstParam;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

    pstParam                            = BST_CORE_GetPidHandle ( enParamId );
    if ( BST_NULL_PTR == pstParam )
    {
        return BST_ERR_PAR_UNKNOW;
    }

    if ( ( BST_CORE_PID_FIX_LEN == pstParam->enLenType ) && ( usLen <  pstParam->usPlen ) )
    {
        return BST_ERR_PAR_LEN;
    }
    else
    {
        usLen                           = pstParam->usPlen;
    }
    pstNewRegItem                       = Select ( pTask->m_usProcId, pTask->m_usTaskId, enParamId );
    if ( BST_NULL_PTR != pstNewRegItem )
    {
        return BST_ERR_ITEM_EXISTED;
    }

    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        pstTaskNode                     = (BST_CORE_REGNODE_STRU *)
                                          BST_OS_MALLOC ( BST_OS_SIZEOF ( BST_CORE_REGNODE_STRU ) );

        if ( BST_NULL_PTR == pstTaskNode )
        {
            return BST_ERR_NO_MEMORY;
        }

        pstTaskNode->pTask              = pTask;
        lstInit( &pstTaskNode->RegParamList );
        lstAdd( &m_RegistryList, (NODE *)pstTaskNode );
    }
   /*
    * 先建立一个PID管理列表项
    */
    pstNewRegItem                       = ( BST_CORE_PIDNODE_STRU * )BST_OS_MALLOC
                                          ( BST_OS_SIZEOF (BST_CORE_PIDNODE_STRU) );
    if ( BST_NULL_PTR == pstNewRegItem )
    {
        BST_OS_FREE ( pstTaskNode );
        return BST_ERR_NO_MEMORY;
    }

    pstNewRegItem->stParamInfo.enPid    = enParamId;
    pstNewRegItem->ulNotice             = ulNoticeFlag;
    pstNewRegItem->stParamInfo.usLen    = usLen;
    pstNewRegItem->stParamInfo.pvContent= const_cast<BST_VOID *>(pValue);
    lstAdd( &pstTaskNode->RegParamList, (NODE *)pstNewRegItem );

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : Regist
 功能描述  : 注册一个任务
 输入参数  : pTask     :任务指针
             enParamId :参数PID
             usLen     :参数PID长度
             pValue    :数据指针
 输出参数  : 无
 返 回 值  : BST_NO_ERROR_MSG :注册成功，其他为注册失败，返回相应的出错类型
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Regist(
    BST_CTask                *pTask,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_CORE_PID_LEN_T        usLen,
    const void               *const pValue )
{
    BST_UINT32                          ulRtnVal;
    ulRtnVal                            = Regist
                                        ( pTask, BST_TRUE,
                                          enParamId, usLen, pValue );
    return ulRtnVal;
}
/*lint +e438*/
/*lint +e429*/
/*****************************************************************************
 函 数 名  : unRegist
 功能描述  : 注销对应PID，重载函数
 输入参数  : pTask     : 任务指针
             enParamId : 参数PID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::unRegist(
    const BST_CTask            *pTask,
    BST_CORE_PID_ENUM_UINT16    enParamId )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstPidNode;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );

    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    * 遍历PID列表，找到对应的条目并删除其中信息
    */
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        lstDelete( &pstTaskNode->RegParamList, ( NODE * )pstPidNode );
        BST_OS_FREE ( pstPidNode );
       /*
        * 如果该任务PID列表已空，那么从注册表总表中删除相应条目
        */
        if ( 0 == lstCount( &pstTaskNode->RegParamList ) )
        {
            lstDelete( &m_RegistryList, ( NODE * )pstTaskNode );
            BST_OS_FREE ( pstTaskNode );
        }
        return BST_NO_ERROR_MSG;
    }
    return BST_ERR_ITEM_NOT_EXISTED;
}
/*****************************************************************************
 函 数 名  : unRegist
 功能描述  : 注销一个任务，重载函数
 输入参数  : BST_CTask *pTask  :任务指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::unRegist ( const BST_CTask *pTask )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstPidNode;
    BST_CORE_PIDNODE_STRU              *pstPidNextNode;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                 = Select
                                         ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }
   /*
    * 必须要辅助表指针pstPidNextNode，因为需要遍历并删除其中所有条目，当前
    * 条目删除后则无法取出NEXT项
    */
    for( pstPidNode = ( BST_CORE_PIDNODE_STRU * )lstFirst( &pstTaskNode->RegParamList );
         BST_NULL_PTR != pstPidNode;
         pstPidNode = pstPidNextNode )
    {
        pstPidNextNode          = ( BST_CORE_PIDNODE_STRU * )
                                  lstNext( ( NODE * )pstPidNode );
        lstDelete( &pstTaskNode->RegParamList,( NODE * ) pstPidNode );
        BST_OS_FREE ( pstPidNode );
    }
    lstDelete( &m_RegistryList, ( NODE * )pstTaskNode );
    BST_OS_FREE ( pstTaskNode );
    return BST_NO_ERROR_MSG;
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : ChnlCtrl
 功能描述  : 配置任务
 输入参数  : BST_SRV_CHNL_HEAD_STRU     *const pstChnHead 信道控制头部
 输出参数  : 无
 返 回 值  : BST_ERR_ENUM_UINT8
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::ChnlCtrl(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_SRV_CHNL_HEAD_STRU    *pstChnHead )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;

    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::ChnlCtrl pstTaskNode=NULL" );
        BST_SRV_FreeIpBlock( pstChnHead );
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == pstTaskNode->pcApCItf )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::ChnlCtrl pstTaskNode.pcApCItf=NULL" );
        BST_SRV_FreeIpBlock( pstChnHead );
        return BST_ERR_PAR_UNKNOW;
    }

    switch( pstChnHead->usCmdId )
    {
        case BST_DSPP_FLG_CMD_CLEAR:
            pstTaskNode->pcApCItf->ChnlCtrlClear();
            BST_SRV_FreeIpBlock( pstChnHead );
        break;

        case BST_DSPP_FLG_CMD_CLOSE:
            pstTaskNode->pcApCItf->ChnlCtrlClose();
            BST_SRV_FreeIpBlock( pstChnHead );
        break;

        case BST_DSPP_FLG_CMD_SEND:
            pstTaskNode->pcApCItf->ChnlCtrlSend( pstChnHead );
        break;

        default:
            BST_SRV_FreeIpBlock( pstChnHead );
        break;
    }

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : Select
 功能描述  : 根据PID从注册表中找到对应的注册项
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
             enParamId  :参数PID类型
 输出参数  : 无
 返 回 值  : 返回对应的注册项,若未找到,返回NULL
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_PIDNODE_STRU* BST_CORE_CRegedit::Select(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_CORE_PID_ENUM_UINT16   enParamId )
{
    BST_CORE_REGNODE_STRU      *pstTaskNode;
    BST_CORE_PIDNODE_STRU      *pstPidNode;

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                 = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_NULL_PTR;
    }
   /*
    *在该任务注册的PID列表中找到与之匹配的PID条目
    */
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid == enParamId )
        {
            return pstPidNode;
        }
    }
    return BST_NULL_PTR;
}
/*****************************************************************************
 函 数 名  : Select
 功能描述  : 根据应用的类型和偏移地址从注册表中找到对应的注册项
 输入参数  : usObjtAddr :对象索引,代理类型(Email/HeartBeat)
             usOfstAddr :偏移地址
 输出参数  : 无
 返 回 值  : 返回对应的注册项,若未找到,返回NULL
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_REGNODE_STRU* BST_CORE_CRegedit::Select(
    BST_OBJT_ADDR_T   usObjtAddr,
    BST_OFST_ADDR_T   usOfstAddr )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;

   /*
    *遍历注册表，寻找objtid,ofstid与之匹配的任务
    */
    for( pstTaskNode  = ( BST_CORE_REGNODE_STRU * )lstFirst( &m_RegistryList ); 
       ( pstTaskNode != BST_NULL_PTR );
         pstTaskNode  = ( BST_CORE_REGNODE_STRU * )
                         lstNext( ( NODE * )pstTaskNode ) )

    {
        if ( BST_NULL_PTR == pstTaskNode->pTask )
        {
            continue;
        }
        if ( ( pstTaskNode->pTask->m_usProcId == usObjtAddr )
          && ( pstTaskNode->pTask->m_usTaskId == usOfstAddr ) )
        {
            return pstTaskNode;
        }
    }
    return BST_NULL_PTR;
}
/*****************************************************************************
 函 数 名  : InputCheck
 功能描述  : 添加注册表时的入口检查
 输入参数  : enParamId : 参数PID
             usDataLen : 数据长度
             pData     : 数据指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_CORE_CRegedit::InputCheck(
    BST_CORE_PID_ENUM_UINT16    enParamId,
    BST_UINT16                  usDataLen,
    const BST_VOID             *const pData ) const
{
    BST_CORE_PID_LUT_STRU  *pstParamAttri;
    pstParamAttri           = BST_CORE_GetPidHandle ( enParamId );

   /*
    *入口检查
    */
    if ( ( BST_NULL_PTR == pstParamAttri ) || ( BST_NULL_PTR == pData ) )
    {
        return BST_FALSE;
    }
   /*
    *定长型数据，如果输入长度与设置不符合或为0，均视为无效
    */
    if ( ( ( BST_CORE_PID_FIX_LEN == pstParamAttri->enLenType )
        && ( usDataLen != pstParamAttri->usPlen ) )
        || ( 0 == usDataLen ) )
    {
        BST_RLS_LOG2( "BST_CORE_CRegedit::InputCheck usDataLen, pstParamAttri->usPlen",
                      usDataLen, pstParamAttri->usPlen );
        return BST_FALSE;
    }
    return BST_TRUE;
}
/*****************************************************************************
 函 数 名  : BST_CORE_CRegedit
 功能描述  : 构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_CORE_CRegedit::BST_CORE_CRegedit ( BST_VOID )
{
   /*
    *初始化注册表
    */
    lstInit( &m_RegistryList );
}

