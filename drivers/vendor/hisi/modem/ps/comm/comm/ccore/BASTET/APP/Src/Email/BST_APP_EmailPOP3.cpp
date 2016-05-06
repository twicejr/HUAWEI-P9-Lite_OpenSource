/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_APP_EmailPOP3.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2013年10月9日
  最近修改   :
  功能描述   : POP3类型邮件的处理方式
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
#include "BST_APP_EmailPOP3.h"
#include "BST_APP_EmailBox.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_APP_EMAILPOP3_CPP
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
函 数 名  : BST_APP_CEmailPOP3
功能描述  : 构造函数
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
BST_APP_CEmailPOP3::BST_APP_CEmailPOP3( const EMAIL_ACCOUNT_STRU *penInAccountInfo )
    : BST_APP_CEmailPacketProc( penInAccountInfo )
{
    m_lServerState              = BST_EMAIL_UNCONNECT;
    m_pcServerResponse0         = (BST_UINT8 *)BST_OS_MALLOC( BST_POP3_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse0 )
    {
        return;
    }
    m_pcServerResponse1         = (BST_UINT8 *)BST_OS_MALLOC( BST_POP3_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse1 )
    {
        BST_OS_FREE( m_pcServerResponse0 );
        return;
    }
    m_pcServerResponse2         = (BST_UINT8 *)BST_OS_MALLOC( BST_POP3_COLUMN_MAX );
    if ( BST_NULL_PTR == m_pcServerResponse2 )
    {
        BST_OS_FREE( m_pcServerResponse0 );
        BST_OS_FREE( m_pcServerResponse1 );
        return;
    }
    BST_OS_MEMSET( m_pcServerResponse0, 0, BST_POP3_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse1, 0, BST_POP3_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse2, 0, BST_POP3_COLUMN_MAX );
}
/*****************************************************************************
函 数 名  : ~CPop3MbxProc
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
BST_APP_CEmailPOP3::~BST_APP_CEmailPOP3( BST_VOID )
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
    BST_RLS_LOG("BST_APP_CEmailPOP3 destructor");/*remove时关键log*/
}
/*****************************************************************************
函 数 名  : ParseRespose
功能描述  : 判断邮箱的配置是否完成，通过调用父类EmailBox的配置判断函数进行判断
输入参数  : BST_UINT8 *pucData  数据指针
            BST_UINT16 usLength 数据长度
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::ParseResponse(
    BST_UINT8  *pucData,
    BST_UINT16  usLength )
{
    BST_UINT16                  i;
    BST_UINT16                  k;
    BST_UINT8                  *p;
    i                           = 0;
    k                           = 0;
    p                           = pucData;

    BST_ASSERT_0_RTN( usLength, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( pucData, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse0, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse1, BST_ERR_PAR_UNKNOW );
    BST_ASSERT_NULL_RTN( m_pcServerResponse2, BST_ERR_PAR_UNKNOW );

    while ( ( ' ' != p[i] ) && ( i < usLength ) )
    {
        BST_APP_POP3_CHECK( k );
        m_pcServerResponse0[k++]    = p[i];
        i++;
    }
    i++;
    k                               = 0;
    while ( ( ' ' != p[i] ) && ( i < usLength ) )
    {
        BST_APP_POP3_CHECK( k );
        m_pcServerResponse1[k++]    = p[i];
        i++;
    }
    i++;
    k                                   = 0;
    while ( ( ' ' != p[i] ) && ( i < usLength ) )
    {
        BST_APP_POP3_CHECK( k );
        m_pcServerResponse2[k++]    = p[i];
        i++;
    }

    return BST_NO_ERROR_MSG;
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::FirstTrsProc( BST_VOID )
{
    /*Pop3 client donot do anything immediately after connected*/
    if( !BST_OS_IsTimerValid(m_ulTimerId) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    BST_DBG_LOG1("start timerId = %u", m_ulTimerId); 
    BST_OS_TimerStart( m_ulTimerId, BST_APP_RX_TIME_OUT );/*连接上之后等待服务器的回复*/
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
函 数 名  : IsConfigOk
功能描述  : 判断邮箱的配置是否完成
输入参数  : BST_VOID
输出参数  : 无
返 回 值  : BST_TRUE  配置完成
            BST_FALSE 配置未完成
调用函数  : 调用父类EmailBox的IsBasicConfigOk函数
调用函数  :
被调函数  :
修改历史  :
1.日期    : 2014年4月17日
  作者    : z00220931
  修改内容: 新函数
*****************************************************************************/
BST_BOOL BST_APP_CEmailPOP3::IsConfigOk( BST_VOID )
{
    if ( BST_FALSE == IsBasicConfigOk() )
    {
        return BST_FALSE;
    }
    if ( BST_NULL_PTR == m_pstLastUID )
    {
        BST_RLS_LOG("Email Box POP3 config is not OK: m_pstLastUID void");
        return BST_FALSE;
    }
    if ( !BST_LIB_IsStringInit( m_pstLastUID->pLastUid ) )
    {
        BST_RLS_LOG("Email Box POP3 config is not OK: pLastUid->IsInited() not init");
        return BST_FALSE;
    }

    return BST_TRUE;
}

/*****************************************************************************
函 数 名   : SetEmailUID
功能描述   : 设置最后一封邮件的UID
输入参数   : pucUid 邮件的uid
             usLen 邮件uid的长度
输出参数   : 无
返 回 值   : 邮件UID存储的地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年6月9日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailPOP3::SetEmailUID(
    const BST_UINT8    *pucUidInfo,
    BST_UINT16          usLen )
{
    BST_ERR_ENUM_UINT8                  enRtnVal;
    const BST_UINT8                    *pTempPtr;
    BST_UINT16                          usMailBoxFolderLen;
    BST_UINT16                          usLastUidLen;

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

    pTempPtr                    = pucUidInfo;
    usMailBoxFolderLen          = UINT8_TO_UINT16( pTempPtr[BST_EMAIL_L],
                                                   pTempPtr[BST_EMAIL_H] );
    pTempPtr                   += BST_EMAIL_MULINFO_LEN_FLAG;
    enRtnVal                    = BST_LIB_StrFill( m_pstLastUID->pMailBoxFolder,
                                                   pTempPtr,
                                                   usMailBoxFolderLen );
    BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    pTempPtr                   += usMailBoxFolderLen;
    usLastUidLen                = UINT8_TO_UINT16( pTempPtr[BST_EMAIL_L],
                                                   pTempPtr[BST_EMAIL_H] );
    pTempPtr                   += BST_EMAIL_MULINFO_LEN_FLAG;
    enRtnVal                    = BST_LIB_StrFill( m_pstLastUID->pLastUid,
                                                   pTempPtr,
                                                   usLastUidLen );
    BST_ASSERT_NORM_RTN( (BST_NO_ERROR_MSG != enRtnVal), BST_NULL_PTR );
    return (BST_UINT8 *)m_pstLastUID;
}
/*****************************************************************************
函 数 名   : ConfigOtherInfo
功能描述   : 配置其他其他信息
输入参数   : enParamId 账号信息
             usLen配置信息的长度
             pData指向配置信息的指针
输出参数   : 无
返 回 值   : 配置信息的存储地址
调用函数   :
被调函数   :
修改历史   :
 1.日期    : 2014年4月17日
   作者    : z00220931
   修改内容: 新函数
*****************************************************************************/
BST_UINT8 *BST_APP_CEmailPOP3::ConfigOtherInfo(
    BST_CORE_PID_ENUM_UINT16    enParamId,
    BST_UINT16                  usLen,
    const BST_VOID             *const pData )
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
            rtn_ptr             = SetEmailUID(
                static_cast<const BST_UINT8 *>(const_cast<BST_VOID *>(pData)),
                usLen );
            break;
        default:
            break;
    }
    return rtn_ptr;
}
/*****************************************************************************
函 数 名  : HandleWelcomResp
功能描述  : 解析服务器欢迎字符
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::HandleWelcomResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;

    enErrMsg                = LoginServer();
    if ( BST_NO_ERROR_MSG == enErrMsg )
    {
        m_lServerState      = BST_EMAIL_CONNECTED;
    }
    else
    {
        return  enErrMsg;
    }
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
函 数 名  : HandleUserResp
功能描述  : 解析USER命令的回复
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::HandleUserResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;

    enErrMsg                = LoginAuth();
    if ( BST_NO_ERROR_MSG == enErrMsg )
    {
        m_lServerState      = BST_EMAIL_POP3_LOGINED;
    }
    else
    {
        return  enErrMsg;
    }
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
函 数 名  : HandlePassResp
功能描述  : 解析PASS命令的回复
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::HandlePassResp( BST_VOID )
{
    BST_ERR_ENUM_UINT8      enErrMsg;

    enErrMsg                = QueryNumOfEmail();
    if ( BST_NO_ERROR_MSG ==  enErrMsg )
    {
        m_lServerState      = BST_EMAIL_POP3_AUTHED;
    }
    else
    {
        return  enErrMsg;
    }
    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
函 数 名  : HandlePassResp
功能描述  : 解析查询邮件数量的回复
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::HandleNumResp()
{
    BST_ERR_ENUM_UINT8      enErrMsg;

    if ( 0 != BST_OS_MEMCMP( "0", m_pcServerResponse1, 1 ) )
    {
        enErrMsg            = QueryUidOfLast( m_pcServerResponse1, 
                                              BST_LIB_StrLen((BST_CHAR *)m_pcServerResponse1) );
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_POP3_QUERYNUMED;
        }
        else
        {
            return  enErrMsg;
        }
        return BST_NO_ERROR_MSG;
    }
    else/*如果邮箱为空，则跳过查询UID的流程*/
    {
        BST_RLS_LOG("CEmailPOP3 donot have new letter.");
        enErrMsg            = QuitServer();
        if ( BST_NO_ERROR_MSG == enErrMsg )
        {
            m_lServerState  = BST_EMAIL_POP3_QUERYUIDED;
        }
        else
        {
            return  enErrMsg;
        }
        return BST_NO_ERROR_MSG;
    }
}
/*****************************************************************************
函 数 名  : HandleQueryResp
功能描述  : 解析查询UID的回复
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::HandleQueryResp()
{
    BST_ERR_ENUM_UINT8      enErrMsg;

    if ( BST_NULL_PTR == m_pstLastUID )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    if ( BST_NULL_PTR == m_pcHostTask )
    {
        return BST_ERR_TASK_REMOVED;
    }
    if ( 0 != BST_OS_MEMCMP( m_pstLastUID->pLastUid->pData,
        m_pcServerResponse2, m_pstLastUID->pLastUid->usUsed) )
    {
        /*如果上报之后AP并没有更新Modem的邮件UID则Modem自己更新*/
        enErrMsg            = BST_LIB_StrFill( m_pstLastUID->pLastUid,
                                               m_pcServerResponse2, 
                                               BST_LIB_StrLen( (BST_CHAR *)m_pcServerResponse2 ) );
        if ( BST_NO_ERROR_MSG != enErrMsg )
        {
            BST_RLS_LOG1( "CEmailPOP3::HandleQueryResp Write Error: %u", enErrMsg );
        }
        enErrMsg            =  BST_NEW_EMAIL;
    }
    else
    {
        BST_RLS_LOG( "CEmailPOP3::HandleQueryResp not new letter!" );
        enErrMsg            =  BST_NO_ERROR_MSG;
    }
    if ( BST_NO_ERROR_MSG == QuitServer() )
    {
        m_lServerState      = BST_EMAIL_POP3_QUERYUIDED;
        return enErrMsg;
    }
    else
    {
        return  BST_ERR_UNREACHABLE;
    }
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
BST_VOID  BST_APP_CEmailPOP3::ResetMachine( BST_VOID )
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::RunStateMachine( BST_VOID )
{
    BST_ERR_ENUM_UINT8  enErrMsg;
    BST_DBG_LOG1( "BST_APP_CEmailPOP3::RunStateMachine m_lServerState=%d",
                  m_lServerState );

    BST_ASSERT_NULL_RTN( m_pcServerResponse0, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pcServerResponse1, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pcServerResponse2, BST_ERR_INVALID_PTR );

    enErrMsg                    = BST_NO_ERROR_MSG;
    if ( 0 != BST_OS_MEMCMP( m_pcServerResponse0, "+OK", 3 ) )
    {
        BST_RLS_LOG( "BST_APP_CEmailPOP3::RunStateMachine NO +OK responesed." );
        return BST_ERR_PAR_UNKNOW;
    }

    switch ( m_lServerState )
    {
        case BST_EMAIL_UNCONNECT:
            enErrMsg            = HandleWelcomResp();
            break;

        case BST_EMAIL_CONNECTED:
            enErrMsg            = HandleUserResp();
            break;

        case BST_EMAIL_POP3_LOGINED:
            enErrMsg            = HandlePassResp();
            break;

        case BST_EMAIL_POP3_AUTHED:
            enErrMsg            = HandleNumResp();
            break;

        case BST_EMAIL_POP3_QUERYNUMED:
            enErrMsg            = HandleQueryResp();
            break;

        case BST_EMAIL_POP3_QUERYUIDED:
            m_lServerState      = BST_EMAIL_QUITED;
            enErrMsg            = BST_NO_ERROR_MSG;
            break;

        default:
            break;
    }
    BST_OS_MEMSET( m_pcServerResponse0, 0, BST_POP3_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse1, 0, BST_POP3_COLUMN_MAX );
    BST_OS_MEMSET( m_pcServerResponse2, 0, BST_POP3_COLUMN_MAX );
    return enErrMsg;
}
/*****************************************************************************
函 数 名  : LoginServer
功能描述  : 登录邮箱账户名
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::LoginServer( BST_VOID )
{
    BST_UINT8                  *pucUserName;
    BST_UINT8                  *pucUserCmd;
    BST_UINT16                  usUserCmdLen;
    BST_UINT16                  usUserNameLen;
    BST_ERR_ENUM_UINT8          enErrMsg;

    BST_ASSERT_NULL_RTN( m_pstAccountInfo, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pstAccountInfo->pUserName, BST_ERR_INVALID_PTR );

    pucUserCmd                  = (BST_UINT8 *)BST_OS_MALLOC(BST_POP3_USER_NAME_MAX_LEN);

    BST_ASSERT_NULL_RTN( pucUserCmd, BST_ERR_NO_MEMORY );

    usUserNameLen               = m_pstAccountInfo->pUserName->usUsed;
    pucUserName                 = ( BST_UINT8 *)(m_pstAccountInfo->pUserName->pData);
    usUserCmdLen                = (BST_UINT16)snprintf( (BST_CHAR *)pucUserCmd,
                                                        BST_POP3_USER_NAME_MAX_LEN, 
                                                        "USER %.*s\r\n",
                                                        usUserNameLen,
                                                        pucUserName );
    enErrMsg                    = SendCommand( pucUserCmd, usUserCmdLen );
    BST_OS_FREE( pucUserCmd );
    return enErrMsg;
}
/*****************************************************************************
函 数 名  : LoginAuth
功能描述  : 登录邮箱的密码
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::LoginAuth( BST_VOID )
{
    BST_UINT8                  *pucPassWord;
    BST_UINT8                  *pucPassWordCmd;
    BST_UINT16                  usPassWordLen;
    BST_UINT16                  usPassWordCmdLen;
    BST_ERR_ENUM_UINT8          enErrMsg;

    BST_ASSERT_NULL_RTN( m_pstAccountInfo, BST_ERR_INVALID_PTR );
    BST_ASSERT_NULL_RTN( m_pstAccountInfo->pPassWord, BST_ERR_INVALID_PTR );

    pucPassWordCmd              = (BST_UINT8 *)BST_OS_MALLOC(BST_POP3_PASS_WORD_MAX_LEN);
    BST_ASSERT_NULL_RTN( pucPassWordCmd, BST_ERR_NO_MEMORY );

    pucPassWord                 = ( BST_UINT8 *)(m_pstAccountInfo->pPassWord->pData);
    usPassWordLen               = m_pstAccountInfo->pPassWord->usUsed;

    usPassWordCmdLen            = (BST_UINT16)snprintf( (BST_CHAR *)pucPassWordCmd,
                                                        BST_POP3_PASS_WORD_MAX_LEN,
                                                        "PASS %.*s\r\n",
                                                        usPassWordLen,
                                                        pucPassWord );
    enErrMsg                    = SendCommand( pucPassWordCmd, usPassWordCmdLen );

    BST_OS_FREE( pucPassWordCmd );
    return enErrMsg;
}
/*****************************************************************************
函 数 名  : QueryNumOfEmail
功能描述  : 查询邮箱的邮件个数
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::QueryNumOfEmail( BST_VOID )
{
    BST_UINT8                  *pucStatCmd;
    BST_UINT16                  usStatCmdLen;
    BST_ERR_ENUM_UINT8          enErrMsg;

    pucStatCmd                  = (BST_UINT8 *)BST_OS_MALLOC( BST_OTHER_CMD_MAX_LEN );
    BST_ASSERT_NULL_RTN( pucStatCmd, BST_ERR_NO_MEMORY );

    usStatCmdLen                = (BST_UINT16)snprintf( (BST_CHAR *)pucStatCmd,
                                                        BST_OTHER_CMD_MAX_LEN,
                                                        "STAT\r\n" );
    enErrMsg                    = SendCommand( pucStatCmd, usStatCmdLen );

    BST_OS_FREE( pucStatCmd );
    return enErrMsg;
}
/*****************************************************************************
函 数 名  : QueryUidOfLast
功能描述  : 查询邮箱最后一个邮件的UID
输入参数  : pucLastSeq 指向最后邮件UID的数据指针
            usLen     数据长度
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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::QueryUidOfLast(
    const BST_UINT8 *pucLastSeq,
    BST_UINT16       usLen )
{
    BST_UINT16                  usSearchCmdLen;
    BST_UINT8                  *pucSearchCmd;
    BST_ERR_ENUM_UINT8          enErrMsg;
    BST_ASSERT_NULL_RTN( pucLastSeq, BST_ERR_INVALID_PTR );
    pucSearchCmd                = (BST_UINT8 *)BST_OS_MALLOC( BST_OTHER_CMD_MAX_LEN );
    BST_ASSERT_NULL_RTN( pucSearchCmd, BST_ERR_NO_MEMORY );
    usSearchCmdLen              = (BST_UINT16)snprintf( (BST_CHAR *)pucSearchCmd,
                                                        BST_OTHER_CMD_MAX_LEN,
                                                        "UIDL %.*s\r\n",
                                                        usLen,
                                                        pucLastSeq );
    enErrMsg                    = SendCommand( pucSearchCmd, usSearchCmdLen );

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
BST_ERR_ENUM_UINT8 BST_APP_CEmailPOP3::QuitServer( BST_VOID )
{
    const BST_CHAR             *pucQuitCmd = "QUIT\r\n";
    BST_UINT16                  usQuitCmdLen;
    BST_ERR_ENUM_UINT8          enErrMsg;

    usQuitCmdLen                = BST_LIB_StrLen( pucQuitCmd );
    enErrMsg                    = SendCommand( (BST_UINT8 *)(pucQuitCmd),
                                                usQuitCmdLen );
    return enErrMsg;
}
