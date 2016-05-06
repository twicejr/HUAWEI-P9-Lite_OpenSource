/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_AsEvnt.cpp
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年07月01日
  最近修改   :
  功能描述   : 接入层事件、控制相关处理处理类成员函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月01日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_SRV_AsEvnt.h"
#include "BST_SRV_Event.h"
#include "BST_DBG_MemLeak.h"
#include "BST_DRV_As.h"
#include "BST_OS_Memory.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_SRV_ASEVNT_CPP
/*lint +e767*/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
  4 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_SRV_CAsRcver
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
BST_SRV_CAsRcver::BST_SRV_CAsRcver( BST_OS_MBX_T *pstRcverMbx )
    : m_pstRcvMbox( pstRcverMbx )
{
    BST_SRV_CAsEvt                     *pcAsMng;
    pcAsMng                             = BST_SRV_CAsEvt::GetInstance();
    m_ulEventFlagSet                    = BST_AS_EVT_NONE;
    BST_ASSERT_NULL( pcAsMng );
    pcAsMng->Attach( this );
}

/*****************************************************************************
 函 数 名  : ~BST_SRV_CAsRcver
 功能描述  : 析构函数
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
BST_SRV_CAsRcver::~BST_SRV_CAsRcver( BST_VOID )
{
    BST_SRV_CAsEvt          *pcAsMng;

    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    BST_ASSERT_NULL( pcAsMng );
    pcAsMng->Detach( this );
}

/*****************************************************************************
 函 数 名  : RegAsNotice
 功能描述  : 注册接入层事件
 输入参数  : enEvent:事件消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsRcver::RegAsNotice( BST_AS_EVT_ENUM_UINT32 enEvent )
{
    if ( BST_SRV_IsValidAsEvent( enEvent ) )
    {
        BST_SRV_SetAsFlag( m_ulEventFlagSet, enEvent );
    }
}

/*****************************************************************************
 函 数 名  : DelEvent
 功能描述  : 删除接入层事件
 输入参数  : enEvent:事件消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsRcver::DelEvent( BST_AS_EVT_ENUM_UINT32 enEvent )
{
    if ( BST_SRV_IsValidAsEvent( enEvent ) )
    {
        BST_SRV_ClrAsFlag( m_ulEventFlagSet, enEvent );
    }
}

/*****************************************************************************
 函 数 名  : GetEventSet
 功能描述  : 获取接入层事件集
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 接入层事件集
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_AS_EVT_SET_UINT32 BST_SRV_CAsRcver::GetEventSet( BST_VOID )
{
    return m_ulEventFlagSet;
}

/*****************************************************************************
 函 数 名  : GetInstance
 功能描述  : 获取BST_SRV_CAsEvt实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BST_SRV_CAsEvt实例
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_SRV_CAsEvt *BST_SRV_CAsEvt::GetInstance( BST_VOID )
{
    static BST_SRV_CAsEvt *pcAsEvtPtr   = BST_NULL_PTR;
    if ( BST_NULL_PTR == pcAsEvtPtr )
    {
        pcAsEvtPtr = new BST_SRV_CAsEvt();
    }
    return pcAsEvtPtr;
}

/*****************************************************************************
 函 数 名  : AsEventRcv
 功能描述  : 处理接入层事件
 输入参数  : enEvent: 事件
             ulLength: 参数长度
             pvData:事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsEvt::Receive(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvNextIdx;
    BST_AS_EVT_SET_UINT32       ulEventFlags;

    if ( !BST_SRV_IsValidAsEvent( enEvent ) )
    {
        return;
    }
    Save( enEvent, ulLength, pvData );
    for( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU * )lstFirst( &m_stAsRcverList );
         BST_NULL_PTR != pstRcvIdx;
         pstRcvIdx = pstRcvNextIdx )
    {
        pstRcvNextIdx           = ( BST_SRV_ASRCVER_NODE_STRU * )
                                  lstNext( ( NODE * )pstRcvIdx );
        ulEventFlags            = pstRcvIdx->pRcver->GetEventSet();

        if ( BST_SRV_AsEvntFlagUsed( ulEventFlags, enEvent ) )
        {
            BST_SRV_ApiSendAsEvent( pstRcvIdx->pRcver, enEvent, ulLength, pvData );
        }
    }
}

BST_VOID BST_SRV_CAsEvt::Forward(
    BST_SRV_CAsRcver       *pcAsRcver,
    BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32          ulLength,
        BST_VOID           *pvData )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvNextIdx;
    BST_AS_EVT_SET_UINT32       ulEventFlags;

    if ( !BST_SRV_IsValidAsEvent( enEvent ) )
    {
        return;
    }
    if ( BST_NULL_PTR == pcAsRcver)
    {
        return;
    }
    for( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU * )lstFirst( &m_stAsRcverList );
         BST_NULL_PTR != pstRcvIdx;
         pstRcvIdx = pstRcvNextIdx )
    {
        pstRcvNextIdx           = ( BST_SRV_ASRCVER_NODE_STRU * )
                                  lstNext( ( NODE * )pstRcvIdx );
        if ( pcAsRcver != pstRcvIdx->pRcver )
        {
            continue;
        }
        ulEventFlags            = pstRcvIdx->pRcver->GetEventSet();
        if ( BST_SRV_AsEvntFlagUsed( ulEventFlags, enEvent ) )
        {
            pstRcvIdx->pRcver->AsEventCallback( enEvent, ulLength, pvData );
            break;
        }
        else
        {
            return;
        }
    }
}

/*****************************************************************************
 函 数 名  : SaveAsMsg
 功能描述  : 保存接入层事件
 输入参数  : enEvent: 事件
             ulLength: 参数长度
             pvData:事件内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_SRV_CAsEvt::Save(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulBufLen,
    BST_VOID               *pvData )
{
}
/*****************************************************************************
 函 数 名  : Inquire
 功能描述  : 事件查询
 输入参数  : enEvent: 事件
             ulLength: 参数长度
             pvData:事件内容
 输出参数  : 无
 返 回 值  : BST_BOOL
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_BOOL BST_SRV_CAsEvt::Inquire(
    BST_AS_EVT_ENUM_UINT32  enEvent,
    BST_UINT32              ulBufLen,
    BST_VOID               *pvData )
{
    return BST_FALSE;
}

/*****************************************************************************
 函 数 名  : Attach
 功能描述  : 附着接入层事件接收器
 输入参数  : pcRcver: 接入层事件接收器指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
BST_VOID BST_SRV_CAsEvt::Attach( BST_SRV_CAsRcver *pcRcver )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_ASSERT_NULL( pcRcver );
    pstRcvIdx                   = ( BST_SRV_ASRCVER_NODE_STRU *)BST_OS_MALLOC
                                  ( BST_OS_SIZEOF( BST_SRV_ASRCVER_NODE_STRU ) );
    BST_ASSERT_NULL( pstRcvIdx );
    pstRcvIdx->pRcver           = pcRcver;
    lstAdd( &m_stAsRcverList, (NODE *)pstRcvIdx );
}
/*lint +e429*/
/*****************************************************************************
 函 数 名  : Detach
 功能描述  : 去附着接入层事件接收器
 输入参数  : pcRcver: 接入层事件接收器指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
/*lint -e438*/
BST_VOID BST_SRV_CAsEvt::Detach( BST_SRV_CAsRcver *pcRcver )
{
    BST_SRV_ASRCVER_NODE_STRU  *pstRcvIdx;
    BST_ASSERT_NULL( pcRcver );

    for ( pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU *)lstFirst( &m_stAsRcverList );
          BST_NULL_PTR != pstRcvIdx;
          pstRcvIdx = ( BST_SRV_ASRCVER_NODE_STRU *)lstNext( (NODE *) pstRcvIdx ) )
    {
        if ( pstRcvIdx->pRcver == pcRcver )
        {
            lstDelete( &m_stAsRcverList, (NODE *)pstRcvIdx );
            BST_OS_FREE( pstRcvIdx );
            break;
        }
    }
}
/*lint +e438*/
/*****************************************************************************
 函 数 名  : BST_SRV_CAsEvt
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
BST_SRV_CAsEvt::BST_SRV_CAsEvt( BST_VOID )
{
    lstInit( &m_stAsRcverList );
}

/*****************************************************************************
 函 数 名  : ~BST_SRV_CAsEvt
 功能描述  : 析构函数
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
BST_SRV_CAsEvt::~BST_SRV_CAsEvt( BST_VOID )
{
    BST_RLS_LOG("BST_SRV_CAsEvt destructor exception!");
}

/*****************************************************************************
 函 数 名  : BST_SRV_RcvAsEvent
 功能描述  : 接收AS事件
 输入参数  : enAsEvent:事件ID
             ulLength:参数长度
             pvData:参数内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2014年06月04日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_SRV_RcvAsEvent(
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData )
{
    BST_SRV_CAsEvt         *pcAsMng;
    pcAsMng                 = BST_SRV_CAsEvt::GetInstance();
    if ( BST_NULL_PTR == pcAsMng )
    {
        return 0;
    }
    pcAsMng->Receive( enAsEvent, ulLength, pvData );
    return ulLength;
}

