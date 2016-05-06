/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司
*******************************************************************************
  文 件 名   : BST_APP_LongRRC.c
  版 本 号   : 初稿
  作    者   : w00346326
  生成日期   : 2015年5月19日
  最近修改   :
  功能描述   : 终端保持RRC连接状态方案的逻辑实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月23日
    作    者   : w00346326
    修改内容   : 创建文件
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_APP_LongRRC.h"

/******************************************************************************
   2 宏定义
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/
BST_VOID               BST_APP_LongRRCTimerCallback( BST_OS_TIMERID_T ulTimerId, BST_VOID *pData );
BST_VOID               BST_APP_LongRRCSendPkt( BST_VOID );

extern BST_OS_MBX_T   *BST_SRV_GetSysMsgHandle( BST_VOID );

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_APP_LONGRRC_INFO_STRU   g_stLongRRCInfo       = {BST_INVALID_FD, BST_INVALID_FD, BST_FALSE};

BST_UINT8                   g_cBstAppLongRRCPkt[] = {69,0,0,40,0,29,0,0,
                                                     255,6,174,212,202,96,135,183,
                                                     202,96,135,183,172,226,1,187,
                                                     139,176,22,73,38,139,193,202,
                                                     80,16,31,122,74,143,0,0};
/******************************************************************************
   6 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : BST_APP_LongRRCInit
 功能描述  : 初始化保持RRC连接状态模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年10月24日
      作    者   : w00346326
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_APP_LongRRCInit( BST_VOID )
{
    BST_RLS_LOG( "BST_APP_LongRRCInit: enter");
    g_stLongRRCInfo.ulIntervalId  = BST_OS_TimerCreate( BST_APP_LongRRCTimerCallback,
                                                        BST_NULL_PTR,
                                                        BST_SRV_GetSysMsgHandle() );
}

/*****************************************************************************
 函 数 名  : BST_APP_LongRRCSetNetParm
 功能描述  : 配置网络参数
 输入参数  : BST_UINT32 ulIPv4          IPv4地址
             BST_BOOL bIsNetStateUp     网卡状态是否为UP
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年10月24日
      作    者   : w00346326
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_APP_LongRRCSetNetParm( BST_UINT32 ulIPv4,  BST_BOOL bNetStateUp)
{

    BST_RLS_LOG2( "BST_APP_LongRRCSetNetParm: enter %d, %d" , ulIPv4, bNetStateUp);

    if ( (BST_TRUE == bNetStateUp)&&(BST_INVALID_IP_ADDR != ulIPv4) )
    {
        /* 修改IP数据包的源IP地址字段，在偏移包的起始位置12字节的位置 */
        BST_OS_MEMCPY( (BST_UINT8 *)g_cBstAppLongRRCPkt + BST_APP_LONGRRC_PKT_SRC_OFFSET,
                       &ulIPv4, BST_OS_SIZEOF( ulIPv4 ) );
    }
    else
    {
        /* 网卡为down的状态下，需要停止发包 */
        if ( BST_OS_IsTimerValid(g_stLongRRCInfo.ulIntervalId) )
        {
            BST_OS_TimerStop( g_stLongRRCInfo.ulIntervalId );
        }
        /* 剩余发包次数清零 */
        g_stLongRRCInfo.ulPktsLeft = 0;
    }
}

/*****************************************************************************
 函 数 名  : BST_APP_LongRRCConfig
 功能描述  : 接收AP侧配置消息，进行配置
 输入参数  : BST_UINT32 ulArgS   AP下发的配置消息
 输出参数  : 无
 返 回 值  : BST_NO_ERROR_MSG   配置成功
             others             配置失败
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年10月24日
      作    者   : w00346326
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_APP_LongRRCConfig( BST_UINT32 ulSustainS )
{
    BST_RLS_LOG1( "BST_APP_LongRRCConfig: enter %d", ulSustainS );

    /* 非法参数，则直接返回 */
    if ( BST_APP_LONGRRC_INVALID_SUSTAIN_S == ulSustainS )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    if ( ulSustainS > BST_APP_LONGRRC_SUSTAIN_MAX_S )
    {
        ulSustainS             = BST_APP_LONGRRC_SUSTAIN_MAX_S;
    }

    /* 剩余发包次数             = 配置发包总时长 / 发包间隔 */
    g_stLongRRCInfo.ulPktsLeft = ulSustainS / BST_APP_LONGRRC_INTERVAL_S;

    /* 先停止原先的Interval定时器 */
    if ( BST_OS_IsTimerValid(g_stLongRRCInfo.ulIntervalId) )
    {
        BST_OS_TimerStop( g_stLongRRCInfo.ulIntervalId );
    }

    /* 开始连续发包 */
    BST_RLS_LOG( "BST_APP_LongRRCConfig: start send packets" );
    BST_APP_LongRRCSendPkt();

    /* 启动Interval定时器 */
    BST_OS_TimerStart( g_stLongRRCInfo.ulIntervalId, BST_APP_LONGRRC_INTERVAL_S * BST_OS_MS_IN_S );

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_APP_LongRRCTimerCallback
 功能描述  : 定时器超时回调函数
 输入参数  : BST_OS_TIMERID_T ulTimerId         定时器ID
             BST_VOID *pData                    定时器附带的数据指针
 输出参数  : 无
 返 回 值  : BST_VOID
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年10月24日
      作    者   : w00346326
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_APP_LongRRCTimerCallback( BST_OS_TIMERID_T ulTimerId, BST_VOID *pData )
{
    if ( ulTimerId != g_stLongRRCInfo.ulIntervalId )
    {
        BST_RLS_LOG1( "BST_APP_LongRRCTimerCallback: invalid timer id %d", ulTimerId );
        return;
    }

    /* 如果还有剩余发包次数,则向空口发送数据包,并重新启动Interval定时器 */
    if ( 0 != g_stLongRRCInfo.ulPktsLeft )
    {
        g_stLongRRCInfo.ulPktsLeft--;
        BST_APP_LongRRCSendPkt();
        BST_OS_TimerStart( g_stLongRRCInfo.ulIntervalId, BST_APP_LONGRRC_INTERVAL_S * BST_OS_MS_IN_S );
    }
}

/*****************************************************************************
 函 数 名  : BST_APP_LongRRCSendPkt
 功能描述  : 向空口发送IP数据包
 输入参数  : BST_VOID
 输出参数  : 无
 返 回 值  : BST_VOID
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年10月24日
      作    者   : w00346326
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_APP_LongRRCSendPkt( BST_VOID )
{
    BST_DRV_IP_DATA_STRU                stIPData;
    BST_DRV_STRU                       *pNetDriver;

    stIPData.pucData                    = g_cBstAppLongRRCPkt;
    stIPData.ucDataType                 = BST_IP_BSTT_DATA;

    /* 调用驱动接口发包 */
    pNetDriver = BST_DRV_NetGetDvcHandle();
    if ( BST_NULL_PTR == pNetDriver->pfWrite )
    {
        BST_RLS_LOG( "BST_APP_LongRRCSendPkt: BST_DRV_NetGetDvcHandle()->pfWrite NULL " );
        return;
    }

    pNetDriver->pfWrite( BST_OS_SIZEOF(g_cBstAppLongRRCPkt), (BST_UINT8 *)&stIPData );

    BST_RLS_LOG1( "BST_APP_LongRRCSendPkt: ok. %d", g_stLongRRCInfo.ulPktsLeft );
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
