/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailIMAP.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : IMAP邮箱的处理方法
  函数列表   :

  修改历史   :
  1.日    期   : 2013年10月9日
    作    者   : d00173029
    修改内容   : 创建文件
  2.日    期   : 2014年4月17日
    作    者   : z00220931
    修改内容   :
******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_APP_EmailBox.h"
#include "BST_APP_EmailIMAP.h"
#include "BST_SRV_TaskMng.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_APP_EMAILIMAP_CPP
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/

/******************************************************************************
   6 函数实现
******************************************************************************/
/*****************************************************************************
函 数 名  : BST_APP_CEmailIMAP
功能描述  : 构造函数
输入参数  : penInAccountInfo: 账号信息
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_APP_CEmailIMAP::BST_APP_CEmailIMAP( const EMAIL_ACCOUNT_STRU *penInAccountInfo )
    : BST_APP_CEmailPacketProc( penInAccountInfo )
{
    m_usTag                     = BST_IMAP_START_TAG;
    m_lServerState              = BST_EMAIL_UNCONNECT;

    m_pcServerResponse0         = (BST_UINT8 *)BST_OS_MALLOC( BST_IMAP_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse0 )
    {
        return;
    }
    m_pcServerResponse1         = (BST_UINT8 *)BST_OS_MALLOC( BST_IMAP_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse1 )
    {
        BST_OS_FREE( m_pcServerResponse0 );
        return;
    }
    m_pcServerResponse2         = (BST_UINT8 *)BST_OS_MALLOC( BST_IMAP_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse2 )
    {
        BST_OS_FREE( m_pcServerResponse0 );
        BST_OS_FREE( m_pcServerResponse1 );
        return;
    }
    BST_OS_MEMSET( m_pcServerResponse0, 0, BST_IMAP_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse1, 0, BST_IMAP_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse2, 0, BST_IMAP_COLUMN_MAX );
}

/*****************************************************************************
函 数 名  : ~CImapMbxProc
功能描述  : 析构函数
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_APP_CEmailIMAP::~BST_APP_CEmailIMAP()
{
    if ( BST_NULL_PTR != m_pcServerResponse0 )
    {
        BST_OS_FREE( m_pcServerResponse0 );
    }
    if ( BST_NULL_PTR != m_pcServerResponse1 )
    {
        BST_OS_FREE( m_pcServerResponse1 );
    }
    if ( BST_NULL_PTR != m_pcServerResponse2 )
    {
        BST_OS_FREE( m_pcServerResponse2 );
    }
    if ( BST_NULL_PTR!= m_pstrImapIDCmd )
    {
        BST_LIB_StrDelete( m_pstrImapIDCmd );
    }
    BST_RLS_LOG("BST_APP_CEmailIMAP destructor");
}
/*****************************************************************************
函 数 名  : InitEmailProc
功能描述  : 判断邮箱的配置是否完成，通过调用父类EmailBox的配置判断函数进行判断
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailIMAP::InitEmailProc( BST_CORE_CNPTask *pTaskProp )
{
    BST_CORE_CRegedit                  *pcRegedit;
    BST_ERR_ENUM_UINT8                  enRtnVal;
    BST_OS_CTimerCb                    *pcTimerCb;
    BST_IP_CNetRcver                   *pNetReceiver;
    BST_IP_ERR_T                        enIpErr;

    m_pstLastUID                        = ( BST_EMAIL_UID_INFO_STRU *)BST_OS_MALLOC
                                          ( BST_OS_SIZEOF( BST_EMAIL_UID_INFO_STRU ) );
    if ( BST_NULL_PTR == m_pstLastUID )
    {
        return BST_FALSE;
    }
    m_pstLastUID->pMailBoxFolder        = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstLastUID->pMailBoxFolder )
    {
        return BST_FALSE;
    }
    m_pstLastUID->pLastUid              = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstLastUID->pLastUid )
    {
        return BST_FALSE;
    }
    m_pstrImapIDCmd                     = BST_LIB_StrCreat( BST_LIB_SHORT_STR_LEN );
    if ( BST_NULL_PTR == m_pstrImapIDCmd )
    {
        return BST_FALSE;
    }
    pcRegedit                           = BST_CORE_CRegedit::GetInstance();
    if ( BST_NULL_PTR == pcRegedit )
    {
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( pTaskProp,
                                                             BST_PID_IMAP_ID_CMD,
                                                             BST_OS_SIZEOF( BST_LIB_StrStru ),
                                                             m_pstrImapIDCmd );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG1( "BST_APP_CEmailPacketProc::InitEmailProc enRtnVal=%d",
                      enRtnVal );
        return BST_FALSE;
    }
    enRtnVal                            = pcRegedit->Regist( pTaskProp,
                                                             BST_PID_EMAIL_LAST_UID,
                                                             BST_OS_SIZEOF( BST_EMAIL_UID_INFO_STRU ),
                                                             m_pstLastUID );
    if ( BST_NO_ERROR_MSG != enRtnVal )
    {
        BST_RLS_LOG1( "BST_APP_CEmailPacketProc::InitEmailProc enRtnVal=%d",
                      enRtnVal );
        return BST_FALSE;
    }
    m_pcHostTask                        = pTaskProp;
    m_pSyncSocket                       = pTaskProp->m_pSocket;

    /*
     *  创建定时器，注册接收回调函数
     */
    pNetReceiver                        = this;
    if ( BST_NULL_PTR == m_pSyncSocket )
    {
        return BST_FALSE;
    }

    enIpErr                             = m_pSyncSocket->IoCtrl( BST_SCKT_CMD_REG_CALLBACK,
                                                                 pNetReceiver );
    if ( BST_IP_ERR_OK != enIpErr )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::InitEmailProc register callback error" );
        return BST_FALSE;
    }

    pcTimerCb                           = this;
    m_ulTimerId                         = BST_OS_TimerCreateCpp( pcTimerCb,
                                                                 BST_NULL_PTR,
                                                                 BST_SRV_GetTaskMsgHandle
                                                               ( pTaskProp->m_usProcId,
                                                                 pTaskProp->m_usTaskId ) );
    if ( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        BST_RLS_LOG( "BST_APP_CEmailPacketProc::InitEmailProc BST_OS_TimerCreateCpp error" );
        return BST_FALSE;
    }
    return BST_TRUE;
}
/*****************************************************************************
函 数 名  : IsConfigOk
功能描述  : 判断邮箱的配置是否完成，通过调用父类EmailBox的配置判断函数进行判断
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailIMAP::IsConfigOk( BST_VOID )
{
    if ( BST_FALSE == IsBasicConfigOk() )
    {
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == m_pstLastUID )
    {
        BST_RLS_LOG("Email Box IMAP config is not OK: m_pstLastUID void");
        return BST_FALSE;
    }
    if ( !BST_LIB_IsStringInit( m_pstLastUID->pMailBoxFolder ))
    {
        BST_RLS_LOG("Email Box IMAP config is not OK: pMailBoxFolder->IsInited");
        return BST_FALSE;
    }
    if ( !BST_LIB_IsStringInit( m_pstLastUID->pLastUid ))
    {
        BST_RLS_LOG("Email Box IMAP config is not OK: pLastUid->IsInited");
        return BST_FALSE;
    }
    return BST_TRUE;
}

/*****************************************************************************
函 数 名   : SetEmailUID
功能描述   : 设置最后一封邮件的UID
输入参数   : pucUidInfo: 邮件的uid
             usLen: 邮件uid的长度
输出参数   : 无
返 回 值   : 邮件UID存储的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailIMAP::SetEmailUID(
    const BST_UINT8    *pucUidInfo,
    BST_UINT16          usLen )
{
    BST_ERR_ENUM_UINT8      enRtnVal;
    const BST_UINT8        *pTempPtr;
    BST_UINT16              usMailBoxFolderLen;
    BST_UINT16              usLastUidLen;

    if ( BST_NULL_PTR == pucUidInfo )
    {
        return BST_NULL_PTR;
    }
    if ( 0 == usLen )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstLastUID )
    {
        return BST_NULL_PTR;
    }

    pTempPtr                = pucUidInfo;
    usMailBoxFolderLen      = UINT8_TO_UINT16( pTempPtr[BST_EMAIL_L],
                                               pTempPtr[BST_EMAIL_H] );
    pTempPtr               += BST_EMAIL_MULINFO_LEN_FLAG;
    enRtnVal                = BST_LIB_StrFill( m_pstLastUID->pMailBoxFolder,
                                               pTempPtr,
                                               usMailBoxFolderLen );
    BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    pTempPtr               += usMailBoxFolderLen;
    usLastUidLen            = UINT8_TO_UINT16( pTempPtr[BST_EMAIL_L],
                                               pTempPtr[BST_EMAIL_H] );
    pTempPtr               += BST_EMAIL_MULINFO_LEN_FLAG;
    enRtnVal                = BST_LIB_StrFill( m_pstLastUID->pLastUid,
                                               pTempPtr,
                                               usLastUidLen );
    BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    return (BST_UINT8 *)(m_pstLastUID);
}
/*****************************************************************************
函 数 名   : SetImapIDCmd
功能描述   : 设置Imap的ID命令
输入参数   : pucImapIDCmd: ID命令
             usLen: ID命令的长度
输出参数   : 无
返 回 值   : ID命令的存储地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailIMAP::SetImapIDCmd(
    const BST_UINT8 *pucImapIDCmd,
    BST_UINT16       usLen )
{
    BST_ERR_ENUM_UINT8      enRtnVal;

    if ( BST_NULL_PTR == pucImapIDCmd )
    {
        return BST_NULL_PTR;
    }
    if ( 0 == usLen )
    {
        return BST_NULL_PTR;
    }
    if ( BST_NULL_PTR == m_pstrImapIDCmd )
    {
        BST_RLS_LOG( "BST_APP_CEmailExchange::SetDeviceID m_pDeviceID=NULL" );
        return BST_NULL_PTR;
    }

    enRtnVal        = BST_LIB_StrFill( m_pstrImapIDCmd, pucImapIDCmd, usLen );
    BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    return ( BST_UINT8 *)(m_pstrImapIDCmd->pData);
}

/*****************************************************************************
函 数 名   : ConfigOtherInfo
功能描述   : 配置其他其他信息
输入参数   : enParamId: 账号信息
             usLen: 配置信息的长度
             pData: 指向配置信息的指针
输出参数   : 无
返 回 值   : 配置信息的存储地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailIMAP::ConfigOtherInfo(
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usLen,
    const BST_VOID           *const pData )
{
    BST_UINT8                  *rtn_ptr;
    rtn_ptr                     = BST_NULL_PTR;
    if ( BST_NULL_PTR == pData )
    {
        return BST_NULL_PTR;
    }
    switch ( enParamId )
    {
        case BST_PID_EMAIL_LAST_UID:
            rtn_ptr             = SetEmailUID( (BST_UINT8 *)pData, usLen);
            break;
        case BST_PID_IMAP_ID_CMD:
            rtn_ptr             = SetImapIDCmd( (BST_UINT8 *)pData, usLen);
            break;

        default:
            break;
    }
    return rtn_ptr;
}

/*****************************************************************************
函 数 名  : ParseRespose
功能描述  : 解析服务器的回复，并将其存储到数组中
输入参数  : pucData: 回复命令指针
            usLength: 长度
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_APP_CEmailIMAP::ParseResponse(
    BST_UINT8          *pucData,
    const BST_UINT16    usLength )
{
    BST_UINT16                      i;
    BST_UINT16                      k;
    BST_UINT8                      *p;
    i                               = 0;
    k                               = 0;
    p                               = pucData;

    BST_ASSERT_0_RTN( usLength, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( pucData, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse0, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse1, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse2, BST_ERR_PAR_UNKNOW );

    while ( ( ' ' != p[i] ) && ( i < usLength ) )
    {
        BST_APP_IMAP_CHECK(k);
        m_pcServerResponse0[k++]    = p[i];
        i++;
    }
    i++;
    k                               = 0;
    while ( ( ' ' != p[i] ) && ( i < usLength ) )
    {
        BST_APP_IMAP_CHECK(k);
        m_pcServerResponse1[k++]    = p[i];
        i++;
    }
    i++;
    k                               = 0;
    while ( (' ' != p[i]) && ( BST_APP_CR != p[i] ) && ( i < usLength ) )/*如果是回车符，也要退出循环*/
    {
        BST_APP_IMAP_CHECK(k);
        m_pcServerResponse2[k++]    = p[i];
        i++;
    }

    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
函 数 名   : HandleWelcomResp
功能描述   : 处理欢迎回复的数据
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleWelcomResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;
    if ( 0 == BST_OS_MEMCMP( m_pcServerResponse1, "OK", 2 ) )
    {
        enErrMsg            = SendID();
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_CONNECTED;
        }
        return enErrMsg;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
函 数 名   : HandleImapIDResp
功能描述   : 处理ID命令的回复
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleImapIDResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;
    if ( 0 == BST_OS_MEMCMP( m_pcServerResponse0, "*", 1 ) )
    {
        enErrMsg            = LoginServer();
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_IMAP_ID;
        }
        return enErrMsg;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}

/*****************************************************************************
函 数 名   : HandleAuthResp
功能描述   : 处理认证回复的数据
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleAuthResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;
    if ( 0 == BST_OS_MEMCMP( m_pcServerResponse1, "OK", 2 ) )
    {
        enErrMsg            = SelectInBox();
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_IMAP_LOGINED;
        }
        return enErrMsg;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
函 数 名   : HandleSelectResp
功能描述   : 处理select回复的数据
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleSelectResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;
    if ( 0 == BST_OS_MEMCMP( m_pcServerResponse0, "*", 1 ) )
    {
        enErrMsg            = QueryServer( m_pcServerResponse1,
                                               BST_LIB_StrLen( (BST_CHAR *)m_pcServerResponse1) );
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_IMAP_SELECTED;
        }
        return enErrMsg;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
函 数 名   : HandleQueryResp
功能描述   : 处理查询回复的数据
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleQueryResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enRtnVal;

    if ( BST_NULL_PTR == m_pstLastUID )
    {
        return BST_ERR_PAR_UNKNOW;
    }
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        return BST_ERR_TASK_REMOVED;
    }
    if ( 0 != BST_OS_MEMCMP( m_pcServerResponse0, "*", 1 ) )
    {
        return BST_ERR_UNREACHABLE;
    }
    if ( 0 != BST_OS_MEMCMP( m_pstLastUID->pLastUid->pData,
                             m_pcServerResponse2,
                             m_pstLastUID->pLastUid->usUsed) )
    {
        /*
         * Modem自己更新邮件的UID值
         */
        enRtnVal            = BST_LIB_StrFill( m_pstLastUID->pLastUid,
                            ( BST_UINT8 *)m_pcServerResponse2,
                            BST_LIB_StrLen( (BST_CHAR *)m_pcServerResponse2 ) );
        if ( BST_NO_ERROR_MSG != enRtnVal )
        {
            BST_RLS_LOG1( "CEmailIMAP::HandleQueryResp Write Error: %u", enRtnVal );
        }
        enRtnVal            = BST_NEW_EMAIL;
    }
    else
    {
        enRtnVal            = BST_NO_ERROR_MSG;
    }
    if ( BST_NO_ERROR_MSG == QuitServer() )
    {
        m_lServerState      = BST_EMAIL_IMAP_QUERYED;
        return enRtnVal;
    }
    else
    {
        return  BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
函 数 名   : HandleQuitResp
功能描述   : 处理退出回复的数据
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::HandleQuitResp( BST_VOID )
{
    if ( 0 == BST_OS_MEMCMP( m_pcServerResponse1, "BYE", BST_LIB_StrLen("BYE") ) )
    {
        BST_DBG_LOG2( "CEmailIMAP ProcId=%d,TaskId=%d run successfully.",
                      m_pcHostTask->m_usProcId, m_pcHostTask->m_usTaskId );
        m_lServerState      = BST_EMAIL_QUITED;
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_UNREACHABLE;
    }
}
/*****************************************************************************
函 数 名   : FirstTrsProc
功能描述   : 连上服务器后的数据交互处理
输入参数   : BST_VOID
输出参数   : 无
返 回 值   : 无
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::FirstTrsProc( BST_VOID )
{
    /*Imap client donot do anything immediately after connected*/
    if( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    BST_DBG_LOG1("start timerId = %u", m_ulTimerId);
    BST_OS_TimerStart( m_ulTimerId, BST_APP_RX_TIME_OUT );
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
函 数 名  : ResetMachine
功能描述  : 复位状态机
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : d00173029
  修改内容: 新函数
*****************************************************************************/
BST_VOID  BST_APP_CEmailIMAP::ResetMachine( BST_VOID )
{
    m_lServerState          = BST_EMAIL_UNCONNECT;
}
/*****************************************************************************
函 数 名  : RunStateMachine
功能描述  : 运行状态机完成邮件的查询流程
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_APP_CEmailIMAP::RunStateMachine( BST_VOID )
{
    BST_ERR_ENUM_UINT8          enErrMsg;

    BST_DBG_LOG1( "CEmailIMAP::RunStateMachine m_lServerState =%d",
                  m_lServerState );

    BST_ASSERT_NULL_RTN( m_pcServerResponse0, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pcServerResponse1, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pcServerResponse2, BST_ERR_INVALID_PTR );

    enErrMsg                    = BST_NO_ERROR_MSG;
    switch ( m_lServerState )
    {
        case BST_EMAIL_UNCONNECT:
            enErrMsg            = HandleWelcomResp();
            break;
        case BST_EMAIL_CONNECTED:
            enErrMsg            = HandleImapIDResp();
            break;

        case BST_EMAIL_IMAP_ID:
            enErrMsg            = HandleAuthResp();
            break;

        case BST_EMAIL_IMAP_LOGINED:
            enErrMsg            = HandleSelectResp();
            break;

        case BST_EMAIL_IMAP_SELECTED:
            enErrMsg            = HandleQueryResp();
            break;

        case BST_EMAIL_IMAP_QUERYED:
            enErrMsg            = HandleQuitResp();
            break;
        default:
            break;
    }
    BST_OS_MEMSET( m_pcServerResponse0, 0, BST_IMAP_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse1, 0, BST_IMAP_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse2, 0, BST_IMAP_COLUMN_MAX );
    return enErrMsg;
}
/*****************************************************************************
函 数 名  : MakeImapID
功能描述  : 组Imap ID命令
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_UINT16 组成命令的长度
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_UINT16 BST_APP_CEmailIMAP::MakeImapID( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enRtnVal;
    /*如果没有初始化，则使用默认的ID命令*/
    if (!BST_LIB_IsStringInit( m_pstrImapIDCmd ))
    {
        enRtnVal        = BST_LIB_StrFill( m_pstrImapIDCmd,
                                          (BST_UINT8 *)BST_DEFAULT_IMAP_ID_CMD,
                                          (BST_UINT16)strlen(BST_DEFAULT_IMAP_ID_CMD));
        BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    }
    return m_pstrImapIDCmd->usUsed;
}
/*****************************************************************************
函 数 名  : SendID
功能描述  : 发送ID命令
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_UINT16 组成命令的长度
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::SendID( BST_VOID )
{
    BST_CHAR           *pucSendIDCmd;
    BST_UINT16          usSendIDCmdLen;
    BST_UINT16          usImapIDLen;
    BST_ERR_ENUM_UINT8  enErrMsg;

    pucSendIDCmd        = (BST_CHAR *)BST_OS_MALLOC( BST_IMAP_ID_CMD_MAX_LEN );
    if ( BST_NULL_PTR == pucSendIDCmd )
    {
        return BST_ERR_INVALID_PTR;
    }
    usImapIDLen         = MakeImapID();

    usSendIDCmdLen      = ( BST_UINT16 )snprintf(
                              pucSendIDCmd,
                              BST_IMAP_ID_CMD_MAX_LEN,
                              "%d %.*s",
                              m_usTag,
                              usImapIDLen,
                              m_pstrImapIDCmd->pData);

    enErrMsg            = SendCommand( (BST_UINT8 *)pucSendIDCmd, usSendIDCmdLen );
    BST_OS_FREE(pucSendIDCmd);
    BST_APP_UPDATE_IMAP_TAG( m_usTag );

    return enErrMsg;
}

/*****************************************************************************
函 数 名  : LoginServer
功能描述  : 登录邮箱
输入参数  : 无
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::LoginServer( BST_VOID )
{
    BST_UINT8          *pucLoginCmd;
    BST_UINT8          *pucUserName;
    BST_UINT8          *pucPassWord;
    BST_UINT16          usLoginCmdLen;
    BST_UINT16          usUserNameLen;
    BST_UINT16          usPassWordLen;
    BST_ERR_ENUM_UINT8  enErrMsg;

    if ( BST_NULL_PTR == m_pstAccountInfo )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo->pUserName )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == m_pstAccountInfo->pPassWord )
    {
        return BST_ERR_INVALID_PTR;
    }
    pucUserName         = ( BST_UINT8 *)( m_pstAccountInfo->pUserName->pData );
    usUserNameLen       = m_pstAccountInfo->pUserName->usUsed;

    pucPassWord         = ( BST_UINT8 *)(m_pstAccountInfo->pPassWord->pData);
    usPassWordLen       = m_pstAccountInfo->pPassWord->usUsed;
    pucLoginCmd         = (BST_UINT8 *)BST_OS_MALLOC(BST_IMAP_AUTH_CMD_MAX_LEN);
    if ( BST_NULL_PTR == pucLoginCmd )
    {
        return BST_ERR_NO_MEMORY;
    }
    usLoginCmdLen       = (BST_UINT16)snprintf(
                          (BST_CHAR *)pucLoginCmd,
                          BST_IMAP_AUTH_CMD_MAX_LEN,
                          "%d LOGIN %.*s %.*s\r\n",
                          m_usTag,
                          usUserNameLen,
                          pucUserName,
                          usPassWordLen,
                          pucPassWord );

    enErrMsg            = SendCommand( pucLoginCmd, usLoginCmdLen);
    BST_APP_UPDATE_IMAP_TAG( m_usTag );
    BST_OS_FREE( pucLoginCmd );
    return enErrMsg;
}

/*****************************************************************************
函 数 名  : SelectInBox
功能描述  : 选择收件箱
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::SelectInBox( BST_VOID )
{
    BST_CHAR               *pcSelectCmd;
    BST_UINT16              usSelectCmdLen;
    BST_ERR_ENUM_UINT8      enErrMsg;

    pcSelectCmd             = (BST_CHAR *)BST_OS_MALLOC( BST_OTHER_CMD_MAX_LEN );
    if ( BST_NULL_PTR == pcSelectCmd )
    {
        return BST_ERR_INVALID_PTR;
    }

    usSelectCmdLen          = (BST_UINT16)snprintf(
                              pcSelectCmd,
                              BST_OTHER_CMD_MAX_LEN,
                              "%d Select \"INBOX\"\r\n",
                              m_usTag );
    enErrMsg                = SendCommand( (BST_UINT8 *)pcSelectCmd, usSelectCmdLen );
    BST_APP_UPDATE_IMAP_TAG( m_usTag );
    BST_OS_FREE( pcSelectCmd );
    return enErrMsg;
}

/*****************************************************************************
函 数 名  : QueryServer
功能描述  : 查询收件箱中最后一封邮件的UID
输入参数  : pucLastNum: 最后一封邮件的UID
            usLen: 长度
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::QueryServer(
    const BST_UINT8 *pucLastNum,
    BST_UINT16       usLen )
{
    BST_ERR_ENUM_UINT8  enErrMsg;
    BST_CHAR           *pucSearchCmd;
    BST_UINT16          usSearchCmdLen;

    if ( BST_NULL_PTR == pucLastNum )
    {
        return BST_ERR_INVALID_PTR;
    }
    if ( 0 == usLen )
    {
        return BST_ERR_PAR_LEN;
    }
    pucSearchCmd        = (BST_CHAR *)BST_OS_MALLOC(BST_OTHER_CMD_MAX_LEN);
    if ( BST_NULL_PTR == pucSearchCmd)
    {
        return BST_ERR_NO_MEMORY;
    }

    usSearchCmdLen      = (BST_UINT16)snprintf(
                          pucSearchCmd,
                          BST_OTHER_CMD_MAX_LEN,
                          "%d UID Search %.*s\r\n",
                          m_usTag,
                          usLen,
                          pucLastNum );
    enErrMsg            = SendCommand( (BST_UINT8 *)pucSearchCmd, usSearchCmdLen );
    BST_APP_UPDATE_IMAP_TAG( m_usTag );

    BST_OS_FREE( pucSearchCmd );
    return enErrMsg;
}

/*****************************************************************************
函 数 名  : QuitServer
功能描述  : 退出服务器
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  成功
            BST_FALSE 失败
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_CEmailIMAP::QuitServer( BST_VOID )
{
    BST_CHAR           *pucLogoutCmd;
    BST_UINT16          usLogoutCmdLen;
    BST_ERR_ENUM_UINT8  enErrMsg;

    pucLogoutCmd        = (BST_CHAR *)BST_OS_MALLOC(BST_OTHER_CMD_MAX_LEN);
    BST_ASSERT_NULL_RTN( pucLogoutCmd, BST_ERR_NO_MEMORY );

    usLogoutCmdLen      = ( BST_UINT16 )snprintf(
                              pucLogoutCmd,
                              BST_OTHER_CMD_MAX_LEN,
                              "%d LOGOUT\r\n",
                              m_usTag );
    enErrMsg            = SendCommand( (BST_UINT8 *)pucLogoutCmd, usLogoutCmdLen );
    BST_APP_UPDATE_IMAP_TAG( m_usTag );

    BST_OS_FREE( pucLogoutCmd );
    return enErrMsg;
}

