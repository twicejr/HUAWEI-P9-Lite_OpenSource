/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司
 ******************************************************************************
  文 件 名   : BST_DRV_LinkSta.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   :
  函数列表   :

  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   : 创建文件

代号    |   英文          | 含义                      | 取值范围  |     权值
        |                 |                           |--------------------+-------------
        |                 |                           |           |  Idle  | Connected
--------+-----------------+---------------------------+----------------------------------
R       |   Rank          | 链路等级当前等级状态      | 0--不可用 | 0
        |                 |                           | 1--差网络 | S∈(0，40)
        |                 |                           | 2--中     | S∈[40，70)
        |                 |                           | 3--好     | S∈[70，100]
--------+-----------------+---------------------------+-----------+--------+-------------
S       |   Score         | 综合得分                  | 0-100     |        |
--------+-----------------+---------------------------+-----------+--------+-------------
N       |   Net Strength  |根据RSCP,ECI0综合计算得出  | 0-100     |  100%  | 40%
--------+-----------------+---------------------------+-----------+--------+-------------
Q       |   Queue State   | RRC层上行队列情况         | 0-100     |  0     | 30%
--------+-----------------+---------------------------+-----------+--------+-------------
T       |   Transimit     | 输特性，当前采用RRC重传   | 0-100     |  0     | 30%
--------+---------------------------------------------+-----------+--------+-------------
D       |   DownLinkRx    | 收到下行数据包,固定附加20 | 0         |  0%    |
-----------------------------------------------------------------------------------------

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_DRV_LinkSta.h"
#include "BST_OS_Memory.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_DRV_LINKSTA_C
/*lint +e767*/
/******************************************************************************
   2 宏定义
******************************************************************************/
/*****************************************************************************
  3 函数声明
*****************************************************************************/

/* 提供给PAL层，用于用于写入不同MODEM，不同制式的网络信号质量 */
BST_UINT32          BST_DRV_LsItf_InWriteNetStrength(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    const BST_UINT32        ulCellId,
    const BST_INT16         sRscp,
    const BST_INT16         sEcio );

/* 提供给PAL层，用于注册查询特性接口 */
BST_ERR_ENUM_UINT8 BST_DRV_LsItf_InRegInquireFun(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    BST_VOID               *pfReadTrsInfo,
    BST_VOID               *pfReadQueInfo );

/* 标准驱动IO接口 */
BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoInit(
    BST_VOID               *pvArg );

BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoWrite(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_UINT32          BST_DRV_LsItf_IoRead(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_ERR_ENUM_UINT8  BST_DRV_LsItf_IoCtrl(
    BST_UINT32              ulCmdId,
    BST_VOID               *pucData );

/* 供DRV_AS调用接口 */
BST_VOID            BST_DRV_LsItf_AsRatMode(
    BST_UINT32              ulRatMode );

BST_VOID            BST_DRV_LsItf_AsRrcState(
    BST_UINT32              ulRrcState );

BST_VOID            BST_DRV_LsItf_AsBlockedState(
    BST_UINT32              ulIsBlocked );

BST_VOID            BST_DRV_LsItf_AsRxInd( BST_VOID );

/* 供DRV_NET调用接口 */
BST_VOID            BST_DRV_LsItf_NetUsingModem(
    BST_UINT32              ulModemId );

/* 内部使用函数 */
BST_STATIC  BST_DRV_LS_RAT_SN_ENUM_UINT32 BST_DRV_LsMapRatToSn(
    BST_AS_RAT_MODE_UINT32  ulRatMode );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_RValue(
    BST_UINT32              ulSValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_SValue(
    BST_UINT32              ulNValue,
    BST_UINT32              ulTValue,
    BST_UINT32              ulQValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TValue(
    BST_DRV_LS_READ_TRS_FUNC   pfTrsFun );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_QValue(
    BST_DRV_LS_READ_QUE_FUNC   pfQueFun );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_NValue(
    BST_INT16                ulRscp,
    BST_INT16                ulEci0 );

BST_STATIC  BST_VOID BST_DRV_LsCal_RscpAvg(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0,
    BST_INT16                    *psRscpAvg,
    BST_INT16                    *psEci0Avg );

BST_STATIC  BST_VOID BST_DRV_LsCal_RscpVrc(
    BST_INT16                    sRscpAvg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_LW_NCore(
    BST_INT16                    sRscpAvg,
    BST_INT16                    sEci0Avg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TG_NCore(
    BST_INT16                    sRscpMin,
    BST_INT16                    sRscpMax,
    BST_INT16                    sRscpAvg );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_QScore(
  BST_UINT32                     ulQueLength,
  BST_UINT32                     ulQueHigh,
  BST_UINT32                     ulQueLow);

BST_STATIC  BST_UINT32 BST_DRV_LsCal_Score(
  BST_UINT32                     ulRate,
  BST_UINT32                     ulNValue,
  BST_UINT32                     ulTValue,
  BST_UINT32                     ulQValue );

BST_STATIC  BST_UINT32 BST_DRV_LsCal_TScore(
  BST_UINT32                     ulReTxRate,
  BST_UINT16                     usReTxMin,
  BST_UINT16                     usReTxMax);

BST_VOID BST_DRV_LsItf_InitThreshold( BST_VOID );

/******************************************************************************
   4 外部函数声明
******************************************************************************/
extern BST_VOID BST_PAL_LsInit( BST_VOID );
extern BST_VOID BST_PAL_LsRegCb( BST_DRV_LS_INS_STRU *pstLsIns );
extern BST_VOID BST_DRV_AsEventCallBack(
    BST_AS_EVT_ENUM_UINT32          enAsEvent,
    BST_UINT32                      ulLength,
    BST_VOID                       *pvData );

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_DRV_STRU    g_BstDrvLinkStateHandle =
{
    BST_DRV_LsItf_IoInit,
    BST_DRV_LsItf_IoWrite,
    BST_DRV_LsItf_IoRead,
    BST_DRV_LsItf_IoCtrl,
    BST_FALSE
};
BST_DRV_LS_INS_STRU g_BstDrvLsInstance = { 0 };
/******************************************************************************
   6 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_IoInit
 功能描述  : 链路质量初始化函数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoInit(
    BST_VOID       *pvArg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT16                          usCnt0, usCnt1;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulCurModemId              = BST_MODEM_MAX;
    pstLsIns->ulCurRrc                  = BST_RRC_STATE_BUTT;
    pstLsIns->ulCurRAT                  = BST_AS_RAT_NONE;
    pstLsIns->ulCellId                  = BST_AS_INVALID_CELLID;
    pstLsIns->ulBlockState              = BST_FALSE;
    pstLsIns->ulRankValue               = BST_AS_NET_RANK_INVALID;
    pstLsIns->ulLastRank                = BST_AS_NET_RANK_INVALID;
    pstLsIns->stNetSta.usCounter        = 0;
    pstLsIns->ulCurDValue               = 0;
    pstLsIns->stNetSta.usIsFull         = BST_FALSE;

    pstLsIns->stRlcStat.ulStatFlag      = BST_FALSE;
    pstLsIns->stRlcStat.ulTotalPkt      = 0;
    pstLsIns->stRlcStat.ulTotalRePkt    = 0;
    pstLsIns->usMovingState             = BST_DRV_LS_STATE_BUTT;
    pstLsIns->usStaticCounter           = 0;
    pstLsIns->ulTransScore              = BST_AS_INVALID_SCORE;

    for( usCnt0 = 0; usCnt0 < BST_DRV_LS_BUF_LENGTH; usCnt0++ )
    {
        pstLsIns->stNetSta.asRscp[usCnt0] = 0;
        pstLsIns->stNetSta.asEcI0[usCnt0] = 0;
    }

    for( usCnt0 = 0; usCnt0 < BST_MODEM_MAX; usCnt0++ )
    {
        for( usCnt1 = 0; usCnt1 < BST_DRV_LS_RAT_NUMBER; usCnt1++ )
        {
            pstLsIns->apfReadQueInfo[usCnt0][usCnt1]
                                        = BST_NULL_PTR;
            pstLsIns->apfReadTrsInfo[usCnt0][usCnt1]
                                        = BST_NULL_PTR;
        }
    }

    BST_DRV_LsItf_InitThreshold();
    BST_PAL_LsRegCb( pstLsIns );

    return BST_NO_ERROR_MSG;
}

/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_IoWrite
 功能描述  :
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoWrite(
    BST_UINT32      ulLength,
    BST_UINT8      *pucData )
{
    return BST_NO_ERROR_MSG;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_IoRead
 功能描述  : 读取网络链路等级
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_DRV_LsItf_IoRead(
    BST_UINT32      ulLength,
    BST_UINT8      *pucData )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_OS_SIZEOF(BST_UINT32) != ulLength )
    {
        BST_DBG_LOG("BST_DRV_LsItf_IoRead len is invalid");
        return 0;
    }

    if( BST_NULL_PTR == pucData )
    {
        BST_DBG_LOG("BST_DRV_LsItf_IoRead len is null ptr");
        return 0;
    }

   *( (BST_UINT32 *)pucData )           = pstLsIns->ulRankValue;
    return BST_OS_SIZEOF(BST_UINT32);
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_IoCtrl
 功能描述  :
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_DRV_LsItf_IoCtrl(
    BST_UINT32      ulCmdId,
    BST_VOID       *pucData )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulQScore;
    BST_UINT32                          ulRatSn;
    BST_UINT32                          ulModemId;

    pstLsIns                            = BST_DRV_LsGetInstance();
    ulRatSn                             = BST_DRV_LsMapRatToSn( pstLsIns->ulCurRAT );
    ulModemId                           = pstLsIns->ulCurModemId;

    if( BST_NULL_PTR == pucData )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }

    switch( ulCmdId )
    {
        case BST_DRV_CMD_GET_CONGESTION:
            if( ( BST_DRV_LS_RAT_INVALID_SN == ulRatSn )
             || ( !BST_DRV_LsMdmIdValid( ulModemId ) ) )
            {
                *( (BST_UINT32 *)pucData )     = 0;
                break;
            }

            ulQScore = BST_DRV_LsCal_QValue( pstLsIns->apfReadQueInfo[ulModemId][ulRatSn] );
            if ( ulQScore >= BST_DRV_LS_FULL_SCORE )
            {
                *( (BST_UINT32 *)pucData )     = 0;
            }
            else
            {
                *( (BST_UINT32 *)pucData )     = BST_DRV_LS_FULL_SCORE - ulQScore;
            }
            break;

        default:
            return BST_ERR_ILLEGAL_PARAM;
    }

    return BST_NO_ERROR_MSG;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_InWriteNetStrength
 功能描述  : 读取信号质量信息，评估链路等级
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_UINT32 BST_DRV_LsItf_InWriteNetStrength(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    const BST_UINT32        ulCellId,
    const BST_INT16         sRscp,
    const BST_INT16         sEcio )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_AS_NET_RANK_ENUM_UINT32         ulNewRank;
    BST_UINT32                          ulNetScore;
    BST_UINT32                          ulTrsScore;
    BST_UINT32                          ulQueueScore;
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRatSn;

    pstLsIns                            = BST_DRV_LsGetInstance();
    ulRatSn                             = BST_DRV_LsMapRatToSn( ulRatMode );
    ulNewRank                           = BST_AS_NET_RANK_INVALID;
    ulNetScore                          = 0;
    ulTrsScore                          = 0;
    ulQueueScore                        = 0;
    ulScore                             = BST_AS_INVALID_SCORE;

    /*modem id不同时，直接返回*/
    if( ulModemId != pstLsIns->ulCurModemId )
    {
        return BST_FALSE;
    }

    /*接入制式不同时，直接返回*/
    if( ulRatMode != pstLsIns->ulCurRAT )
    {
        return BST_FALSE;
    }

    /*当前数据业务所在RAT制式不是GPRS,且未获取到有效的RRC状态时,直接返回*/
    if( ( BST_DRV_AsIsRrcStateInvalid() ) && ( BST_AS_RAT_GPRS != ulRatMode ) )
    {
        return BST_FALSE;
    }

    /*如果当前接入制式或modem id为无效时，直接返回*/
    if( ( BST_DRV_LS_RAT_INVALID_SN == ulRatSn )
     || ( !BST_DRV_LsMdmIdValid( ulModemId ) ) )
    {
        return BST_FALSE;
    }

    /*Cell id发生变化，连接态RLC层重传率得分置为无效分数*/
    if( ulCellId != pstLsIns->ulCellId )
    {
        BST_DBG_LOG("Cell id is changed!");
        pstLsIns->ulCellId     = ulCellId;
        pstLsIns->ulTransScore = BST_AS_INVALID_SCORE;
    }

    BST_DBG_LOG4("ulRatMode=%d,ulCellId=%d,sRscp=%d,sEcio=%d",
                  ulRatMode, ulCellId, sRscp, sEcio);

    /************************************************************************
    * 下面根据RAT，RRC状态采用不同算法计算 ulNewRank
    * 层次化调用 BST_DRV_LsCal_xValue函数
    * IDLE态每个周期都计算，连接态每隔一段时间计算一次，得到ulNewRank
    **************************************************************************/

    /*IDLE态及GSM制式下计算链路等级，包括信号质量*/
    if( !BST_DRV_AsIsRrcExisted() || ( BST_AS_RAT_GPRS == ulRatMode ) )
    {
        ulScore = BST_DRV_LsCal_NValue( sRscp, sEcio );
        BST_DBG_LOG1("idle state ulScore=%d", ulScore);
    }
    /*RRC连接态下计算链路等级，包括信号质量、RLC重传率、队列情况*/
    else
    {
        ulNetScore   = BST_DRV_LsCal_NValue( sRscp, sEcio );
        ulTrsScore   = BST_DRV_LsCal_TValue( pstLsIns->apfReadTrsInfo[ulModemId][ulRatSn] );
        ulQueueScore = BST_DRV_LsCal_QValue( pstLsIns->apfReadQueInfo[ulModemId][ulRatSn] );
        ulScore      = BST_DRV_LsCal_SValue( ulNetScore, ulTrsScore, ulQueueScore );
        BST_DBG_LOG4("connect state ulNetScore=%d,ulTrsScore=%d,ulQueueScore=%d,ulScore=%d",
                     ulNetScore, ulTrsScore, ulQueueScore, ulScore);
    }

    ulNewRank = BST_DRV_LsCal_RValue( ulScore );
    BST_DBG_LOG3("ulCurDValue=%d, ulTransScore=%d, ulNewRank=%d",
                  pstLsIns->ulCurDValue, pstLsIns->ulTransScore, ulNewRank);

    /*无论是block状态还是unblock状态，保存上一次计算的rank等级*/
    pstLsIns->ulLastRank = ulNewRank;

    if( BST_TRUE == pstLsIns->ulBlockState )
    {
        BST_RLS_LOG("ulBlockState is true, ulRankValue is BST_AS_NET_RANK_INVALID");
        return BST_TRUE;
    }

    if( ulNewRank != pstLsIns->ulRankValue )
    {
        pstLsIns->ulRankValue           = ulNewRank;
        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK, BST_OS_SIZEOF(ulNewRank), &ulNewRank );

        BST_DBG_LOG1("ulRankValue is changed ulNewRank=%d", ulNewRank);
    }

    return BST_TRUE;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_InRegInquireFun
 功能描述  : 提供给PAL层，用于注册查询传输特性接口
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_DRV_LsItf_InRegInquireFun(
    const BST_UINT32        ulModemId,
    const BST_UINT32        ulRatMode,
    BST_VOID               *pfReadTrsInfo,
    BST_VOID               *pfReadQueInfo )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( !BST_DRV_LsMdmIdValid(ulModemId) )
    {
        return BST_ERR_UNKNOW_OBJ;
    }
    if( !BST_DRV_LsIsRatSnValid(ulRatMode) )
    {
        return BST_ERR_ITEM_NOT_EXISTED;
    }

    pstLsIns->apfReadTrsInfo[ulModemId][ulRatMode]
                                        = (BST_DRV_LS_READ_TRS_FUNC)pfReadTrsInfo;
    pstLsIns->apfReadQueInfo[ulModemId][ulRatMode]
                                        = (BST_DRV_LS_READ_TRS_FUNC)pfReadQueInfo;

    return BST_NO_ERROR_MSG;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_AsRatMode
 功能描述  : 记录当前rat mode类型
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_AsRatMode(
    BST_UINT32              ulRatMode )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ulRatMode != pstLsIns->ulCurRAT )
    {
        pstLsIns->ulCellId              = BST_AS_INVALID_CELLID;
        pstLsIns->stNetSta.usCounter    = 0;
        pstLsIns->stNetSta.usIsFull     = BST_FALSE;
        pstLsIns->ulCurRrc              = BST_RRC_STATE_BUTT;

        pstLsIns->stRlcStat.ulStatFlag  = BST_FALSE;
        pstLsIns->usMovingState         = BST_DRV_LS_STATE_BUTT;
        pstLsIns->usStaticCounter       = 0;
        pstLsIns->ulTransScore          = BST_AS_INVALID_SCORE;
    }

    pstLsIns->ulCurRAT                  = ulRatMode;
    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_NetSetDeviceState
 功能描述  : 获取当前网卡状态信息
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_NetSetDeviceState(
    BST_DRV_NET_STATE_ENUM_UINT32           ulNetDeviceStatus )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulNetDeviceState          = ulNetDeviceStatus;

    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_AsRrcState
 功能描述  : 获取当前RRC状态信息
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_AsRrcState(
    BST_UINT32              ulRrcState )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    /*当从RRC状态变化，一定要清除 ulCurDValue*/
    if( ulRrcState != pstLsIns->ulCurRrc )
    {
        pstLsIns->ulCurDValue = 0;

        if( ( BST_RRC_STATE_IDLE == ulRrcState )
         || ( BST_RRC_STATE_PCH == ulRrcState ) )
        {
            pstLsIns->stRlcStat.ulStatFlag = BST_FALSE;
        }
    }

    pstLsIns->ulCurRrc = ulRrcState;
    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_AsBlockedState
 功能描述  : 获取当前网络是否处于block状态
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_AsBlockedState(
    BST_UINT32              ulIsBlocked )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();

    pstLsIns->ulBlockState              = ulIsBlocked;
    /*
     * 当网络从可用到不可用，必须上报一次
     */
    BST_RLS_LOG1("Block state is changed new BlockeState=%d", ulIsBlocked);

    if( ( BST_AS_NET_RANK_INVALID != pstLsIns->ulRankValue )
      &&( BST_TRUE == ulIsBlocked ) )
    {
        pstLsIns->ulRankValue           = BST_AS_NET_RANK_INVALID;

        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK,
            BST_OS_SIZEOF(pstLsIns->ulRankValue),
            &pstLsIns->ulRankValue );
    }

    /*当从block到unblock状态时，上报上一次记录的网络质量等级*/
    else if( BST_FALSE == ulIsBlocked )
    {
        pstLsIns->ulRankValue           = pstLsIns->ulLastRank;

        BST_DRV_AsEventCallBack(
            BST_AS_EVT_L3_NET_RANK,
            BST_OS_SIZEOF(pstLsIns->ulRankValue),
            &pstLsIns->ulRankValue );
    }
    else
    {
    }

    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_AsRxInd
 功能描述  : 判断当前是否存在数据收发状态，若有，链路等级加分
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_AsRxInd( BST_VOID )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    pstLsIns                            = BST_DRV_LsGetInstance();
    pstLsIns->ulCurDValue               = BST_DRV_LS_TRX_ADD_SVALUE;
    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_NetUsingModem
 功能描述  : 获取当前工作的modem id类型
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_NetUsingModem(
    BST_UINT32              ulModemId )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_DRV_STRU                       *pDrvHandle;

    pDrvHandle                          = BST_DRV_LsGetDvcHandle();
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ulModemId != pstLsIns->ulCurModemId )
    {
        pstLsIns->ulCurDValue               = 0;
        pstLsIns->stNetSta.usCounter        = 0;
        pstLsIns->stNetSta.usIsFull         = BST_FALSE;
        BST_RLS_LOG1("Modem Id is changed new ulModemId=%d", ulModemId);
    }
    pstLsIns->ulCurModemId = ulModemId;

    /*ap下发modem id时，向modem各个接入层模块发送信号质量注册回调消息，只发送一次*/
    if( BST_FALSE == pDrvHandle->ulIsInited )
    {
        pDrvHandle->ulIsInited = BST_TRUE;
        BST_PAL_LsInit();
    }

    return;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsMapRatToSn
 功能描述  : rat mode类型转化
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_DRV_LS_RAT_SN_ENUM_UINT32 BST_DRV_LsMapRatToSn(
    BST_AS_RAT_MODE_UINT32  ulRatMode )
{
    switch( ulRatMode )
    {
        case BST_AS_RAT_CDMA:
            return BST_DRV_LS_RAT_INVALID_SN;

        case BST_AS_RAT_EVDO:
            return BST_DRV_LS_RAT_INVALID_SN;

        case BST_AS_RAT_GPRS:
            return BST_DRV_LS_RAT_GSM_SN;

        case BST_AS_RAT_WCDMA:
            return BST_DRV_LS_RAT_WCDMA_SN;

        case BST_AS_RAT_TDSCDMA:
            return BST_DRV_LS_RAT_TDSCDMA_SN;

        case BST_AS_RAT_LTE:
            return BST_DRV_LS_RAT_LTE_SN;

        default :
            return BST_DRV_LS_RAT_INVALID_SN;

    }
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_RValue
 功能描述  : 计算IDLE态和Connect态下链路质量等级
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_RValue(
    BST_UINT32              ulSValue )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulRank;

    ulRank                              = BST_AS_NET_RANK_GOOD;
    pstLsIns                            = BST_DRV_LsGetInstance();



    /*未计算到有效的SValue值，返回上一次的链路等级*/
    if( BST_AS_INVALID_SCORE == ulSValue )
    {
        return pstLsIns->ulLastRank;
    }

    /*当前是否有数据收发加分项，当RRC状态变化时，该值清零，
      由于GSM无RRC状态，在GSM制式时，不计算加分项*/
    if( BST_AS_RAT_GPRS != pstLsIns->ulCurRAT )
    {
        ulSValue += pstLsIns->ulCurDValue;
    }

    if( BST_DRV_LS_ZERO_SCORE == ulSValue )
    {
        ulRank = BST_AS_NET_RANK_POOR;
    }
    else if( ulSValue < BST_DRV_LS_WEAK_SCORE )
    {
        /*********************************************************
        IDLE态网络质量等级差的判断条件，wcdma、lte、tdscdma制式:
        (1)网络质量得分低于BST_DRV_LS_WEAK_SCORE;
        (2)连接态下重传率得分低于BST_DRV_LS_POOR_SCORE，若为无效分数，则不考虑此条件，
           只要满足ulSValue < BST_DRV_LS_WEAK_SCORE，即认为当前网络质量等级为poor.

        gsm制式下无RLC重传，也无RRC状态，判断条件为:
        (1)网络质量得分低于BST_DRV_LS_WEAK_SCORE;
        (2)当前制式为GSM制式.

        Connect态网络质量等级差的判断条件:
        (1)网络质量得分低于BST_DRV_LS_WEAK_SCORE;
        (2)处于RRC连接态.
        *********************************************************/
        if( (pstLsIns->ulTransScore <= BST_DRV_LS_POOR_SCORE)
           || (BST_AS_INVALID_SCORE == pstLsIns->ulTransScore)
           || ( BST_AS_RAT_GPRS == pstLsIns->ulCurRAT )
           || ( BST_DRV_AsIsRrcExisted() ) )
        {
            ulRank = BST_AS_NET_RANK_POOR;
        }
        else
        {
            ulRank = BST_AS_NET_RANK_MIDDLE;
        }
    }
    else if ( ( ulSValue >= ( BST_DRV_LS_WEAK_SCORE + BST_DRV_LS_EXTRA_SCORE ) )
         && ( ulSValue < BST_DRV_LS_MIDD_SCORE ) )
    {
        ulRank = BST_AS_NET_RANK_MIDDLE;
    }
    else if( ulSValue >= ( BST_DRV_LS_MIDD_SCORE + BST_DRV_LS_EXTRA_SCORE ) )
    {
        ulRank = BST_AS_NET_RANK_GOOD;
    }
    else
    {
        ulRank = pstLsIns->ulLastRank;
    }

    return ulRank;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_SValue
 功能描述  : 根据信号质量、重传、队列等信息给链路等级评分
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_SValue(
    BST_UINT32              ulNValue,
    BST_UINT32              ulTValue,
    BST_UINT32              ulQValue )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRate;

    ulScore                             = BST_AS_INVALID_SCORE;
    ulRate                              = BST_DRV_LS_NONE_USED_BIT;

    /*当ulTValue、ulQValue中有一个值分数为0时，则认为当前链路质量为差*/
    if( ( BST_DRV_LS_ZERO_SCORE == ulTValue )
     || ( BST_DRV_LS_ZERO_SCORE == ulQValue ) )
    {
        ulScore = BST_DRV_LS_ZERO_SCORE;
        return ulScore;
    }

    /*当ulNValue值有效时，计算该权重*/
    if( BST_AS_INVALID_SCORE != ulNValue )
    {
        ulRate = ulRate | BST_DRV_LS_N_USED_BIT;
    }

    /*当ulTValue值有效时，计算该权重*/
    if( BST_AS_INVALID_SCORE != ulTValue )
    {
        ulRate = ulRate | BST_DRV_LS_T_USED_BIT;
    }

    /*当ulQValue值有效时，计算该权重*/
    if( BST_AS_INVALID_SCORE != ulQValue )
    {
        ulRate = ulRate | BST_DRV_LS_Q_USED_BIT;
    }

    ulScore = BST_DRV_LsCal_Score( ulRate, ulNValue, ulTValue, ulQValue );

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_Score
 功能描述  : 根据N、T、Q值的有效性，选择计算权重比例，计算链路质量分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_Score(
  BST_UINT32                 ulRate,
  BST_UINT32                 ulNValue,
  BST_UINT32                 ulTValue,
  BST_UINT32                 ulQValue )
{
    BST_UINT32                          ulScore;

    ulScore                             = 0;

    switch( ulRate )
    {
        /*N、T、Q都有效,N占50%, T占25% Q占25%*/
        case BST_DRV_LS_ALL_USED_BIT:
            ulScore += ( ulNValue >> BST_DRV_LS_BIT1_FAC );
            ulScore += ( ulTValue >> BST_DRV_LS_BIT2_FAC );
            ulScore += ( ulQValue >> BST_DRV_LS_BIT2_FAC );
            break;

        /*N、Q有效,各占50%*/
        case BST_DRV_LS_NQ_USED_BIT:
            ulScore = ( ( ulNValue + ulQValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*N、T有效,各占50%*/
        case BST_DRV_LS_NT_USED_BIT:
            ulScore = ( ( ulNValue + ulTValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*T、Q有效,各占50%*/
        case BST_DRV_LS_TQ_USED_BIT:
            ulScore = ( ( ulTValue + ulQValue ) >> BST_DRV_LS_BIT1_FAC );
            break;

        /*仅有N有效*/
        case BST_DRV_LS_N_USED_BIT:
            ulScore = ulNValue;
            break;

        /*仅有Q有效*/
        case BST_DRV_LS_Q_USED_BIT:
            ulScore = ulQValue;
            break;

        /*仅有T有效*/
        case BST_DRV_LS_T_USED_BIT:
            ulScore = ulTValue;
            break;

        default:
            return BST_AS_INVALID_SCORE;
    }

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_TValue
 功能描述  : 计算重传情况计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_TValue(
    BST_DRV_LS_READ_TRS_FUNC   pfTrsFun )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulTotalPkt;
    BST_UINT32                          ulTotalRePkt;
    BST_UINT32                          ulReTxRate;
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstThold                            = BST_DRV_LsGetNetThreshold();
    ulTotalPkt                          = 0;
    ulTotalRePkt                        = 0;
    ulReTxRate                          = 0;
    ulScore                             = BST_AS_INVALID_SCORE;

    if( BST_NULL_PTR == pfTrsFun )
    {
        return BST_AS_INVALID_SCORE;
    }

    pfTrsFun( &ulTotalPkt, &ulTotalRePkt );

    if( ( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
     || ( BST_AS_RAT_TDSCDMA == pstLsIns->ulCurRAT ) )
    {
        /*第一次在连接态计算TL制式的RLC层重传率，先保存当前累积值*/
        if( BST_FALSE == pstLsIns->stRlcStat.ulStatFlag )
        {
            pstLsIns->stRlcStat.ulStatFlag   = BST_TRUE;
            pstLsIns->stRlcStat.ulTotalPkt   = ulTotalPkt;
            pstLsIns->stRlcStat.ulTotalRePkt = ulTotalRePkt;

            return BST_AS_INVALID_SCORE;
        }

        ulTotalPkt   = BST_DRV_LS_MOD_SUB( ulTotalPkt, pstLsIns->stRlcStat.ulTotalPkt );
        ulTotalRePkt = BST_DRV_LS_MOD_SUB( ulTotalRePkt, pstLsIns->stRlcStat.ulTotalRePkt );
    }

    BST_DBG_LOG2("ulTotalPkt=%d, ulTotalRePkt=%d",ulTotalPkt, ulTotalRePkt );

    /*当发送PDU样本个数小于BST_DRV_LS_TX_PKT_NUM时，不计算RLC重传率，只有当大于的时候才计算*/
    if( ulTotalPkt < BST_DRV_LS_TX_PKT_NUM )
    {
        return pstLsIns->ulTransScore;
    }

    /*计算RLC重传率，先乘以100*/
    ulReTxRate = ( ulTotalRePkt * BST_DRV_LS_ONE_HUNDRED ) / ulTotalPkt;

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->lte.usReTxMin,
                                            pstThold->lte.usReTxMax );
            break;

        case BST_AS_RAT_WCDMA:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->wcdma.usReTxMin,
                                            pstThold->wcdma.usReTxMax );
            break;

        case BST_AS_RAT_TDSCDMA:
            ulScore = BST_DRV_LsCal_TScore( ulReTxRate,
                                            pstThold->tdscdma.usReTxMin,
                                            pstThold->tdscdma.usReTxMax );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_TValue invalid rat mode");
            break;
    }

    /*记录连接态下RLC重传率得分，以供IDLE态下使用*/
    pstLsIns->ulTransScore = ulScore;

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_TScore
 功能描述  : 根据当前队列情况计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_TScore(
  BST_UINT32                            ulReTxRate,
  BST_UINT16                            usReTxMin,
  BST_UINT16                            usReTxMax)
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    if(  ulReTxRate <= usReTxMin )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    else if( ulReTxRate >= usReTxMax )
    {
        ulScore = 0;
    }
    else
    {
        /*计算值先乘以100，最后除以门限区间值*/
        ulScore = ( usReTxMax - ulReTxRate ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore / ( (BST_UINT16)( usReTxMax - usReTxMin ) );
    }

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_QValue
 功能描述  : 根据当前队列情况计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_QValue(
    BST_DRV_LS_READ_QUE_FUNC   pfQueFun )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT32                          ulScore;
    BST_UINT32                          ulQueLength;
    BST_UINT32                          ulBandWidth;

    ulQueLength                         = 0;
    ulBandWidth                         = 0;
    ulScore                             = BST_AS_INVALID_SCORE;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_NULL_PTR == pfQueFun )
    {
        return BST_AS_INVALID_SCORE;
    }

    pfQueFun( &ulQueLength, &ulBandWidth );
    BST_DBG_LOG1("ulQueLength=%d", ulQueLength);

    /*当缓存队列小于BST_DRV_LS_QUE_LEN_MIN，不计算缓存队列所占权重*/
    if( ulQueLength < BST_DRV_LS_QUE_LEN_MIN )
    {
        return BST_AS_INVALID_SCORE;
    }

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
            /*lte 上行速率默认为512k bit/s，右移9位*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT9_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_WCDMA:
            /*wcdma 上行速率默认为256k bit/s，右移8位*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT8_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_TDSCDMA:
            /*tdscdma 上行速率默认为64k bit/s，右移6位*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT6_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        case BST_AS_RAT_GPRS:
            /*gsm 上行速率默认为8k bit/s，右移3位*/
            ulScore = BST_DRV_LsCal_QScore( ulQueLength >> BST_DRV_LS_BIT3_FAC,
                                            BST_DRV_LS_QUE_HIGH,
                                            BST_DRV_LS_QUE_LOW );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_QValue invalid rat mode");
            break;
    }

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_QScore
 功能描述  : 根据当前队列情况计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_QScore(
  BST_UINT32                            ulQueLength,
  BST_UINT32                            ulQueHigh,
  BST_UINT32                            ulQueLow)
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    /*队列清空时间小于ulQueLow*/
    if( ulQueLength <= ulQueLow )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    /*队列清空时间大于ulQueHigh*/
    else if( ulQueLength >= ulQueHigh )
    {
        ulScore = 0;
    }
    else
    {
        /*计算值先乘以100，最后除以门限区间值*/
        ulScore = ( ulQueHigh - ulQueLength ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore >> BST_DRV_LS_BIT13_FAC;
    }

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_NValue
 功能描述  : 根据信号质量信息计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_NValue(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0 )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_INT16                           sRscpAvg;
    BST_INT16                           sEci0Avg;
    BST_UINT32                          ulScore;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;

    sRscpAvg                            = 0;
    sEci0Avg                            = 0;
    ulScore                             = BST_AS_INVALID_SCORE;
    pstThold                            = BST_DRV_LsGetNetThreshold();
    pstLsIns                            = BST_DRV_LsGetInstance();

    /*RSCP为异常值，返回无效分数*/
    if( sRscp >= 0 )
    {
        return BST_AS_INVALID_SCORE;
    }

    /*计算信号均值和方差*/
    BST_DRV_LsCal_RscpAvg( sRscp, sEci0, &sRscpAvg, &sEci0Avg );

    switch( pstLsIns->ulCurRAT )
    {
        case BST_AS_RAT_LTE:
        case BST_AS_RAT_WCDMA:
            ulScore = BST_DRV_LsCal_LW_NCore( sRscpAvg,
                                              sEci0Avg );
            break;

        case BST_AS_RAT_TDSCDMA:
            ulScore = BST_DRV_LsCal_TG_NCore( pstThold->tdscdma.sRscpMin,
                                              pstThold->tdscdma.sRscpMax,
                                              sRscpAvg );
            break;

        case BST_AS_RAT_GPRS:
            ulScore = BST_DRV_LsCal_TG_NCore( pstThold->gsm.sRxLevAMin,
                                              pstThold->gsm.sRxLevAMax,
                                              sRscpAvg );
            break;

        default:
            BST_RLS_LOG("BST_DRV_LsCal_NValue invalid rat mode");
            break;
    }

    return ulScore;
}


/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_RscpAvg
 功能描述  : 计算信号均值
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_VOID BST_DRV_LsCal_RscpAvg(
    BST_INT16                    sRscp,
    BST_INT16                    sEci0,
    BST_INT16                    *psRscpAvg,
    BST_INT16                    *psEci0Avg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_UINT8                           ucIndex;
    BST_INT16                           sRscpSum;
    BST_INT16                           sEci0Sum;

    BST_UINT16                          usCounter;
    BST_INT16                           sRscpAvg;
    BST_INT16                           sEci0Avg;

    sRscpSum                            = 0;
    sEci0Sum                            = 0;
    sRscpAvg                            = 0;
    sEci0Avg                            = 0;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( ( BST_NULL_PTR == psRscpAvg ) || ( BST_NULL_PTR == psEci0Avg ) )
    {
        return;
    }

    /*TL制式下采用即时值，无均值和方差的计算，WG制式下采用滑动平均值*/
    if( ( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
     || ( BST_AS_RAT_TDSCDMA == pstLsIns->ulCurRAT ) )
    {
        sRscpAvg                = sRscp;
        sEci0Avg                = sEci0;
        pstLsIns->usMovingState = BST_DRV_LS_STATE_STATIC;
    }
    else
    {
        pstLsIns->stNetSta.asRscp[pstLsIns->stNetSta.usCounter] = sRscp;
        pstLsIns->stNetSta.asEcI0[pstLsIns->stNetSta.usCounter] = sEci0;
        pstLsIns->stNetSta.usCounter++;

        if( BST_DRV_LS_BUF_LENGTH == pstLsIns->stNetSta.usCounter )
        {
            pstLsIns->stNetSta.usCounter = 0;
            pstLsIns->stNetSta.usIsFull  = BST_TRUE;
        }

        /*数据缓冲区未满时，按实际有效个数计算均值*/
        if( BST_FALSE == pstLsIns->stNetSta.usIsFull )
        {
            for( ucIndex = 0; ucIndex < pstLsIns->stNetSta.usCounter; ucIndex++ )
            {
                sRscpSum += pstLsIns->stNetSta.asRscp[ucIndex];
                sEci0Sum += pstLsIns->stNetSta.asEcI0[ucIndex];
            }
            usCounter = pstLsIns->stNetSta.usCounter;
        }
        else /*数据缓冲区已满*/
        {
            for( ucIndex = 0; ucIndex < BST_DRV_LS_BUF_LENGTH; ucIndex++ )
            {
                sRscpSum += pstLsIns->stNetSta.asRscp[ucIndex];
                sEci0Sum += pstLsIns->stNetSta.asEcI0[ucIndex];
            }
            usCounter = BST_DRV_LS_BUF_LENGTH;
        }

        sRscpAvg = ( sRscpSum / usCounter );
        sEci0Avg = ( sEci0Sum / usCounter );

        /*计算方差, WG制式下计算*/
        BST_DRV_LsCal_RscpVrc( sRscpAvg );
    }

    *psRscpAvg = sRscpAvg;
    *psEci0Avg = sEci0Avg;

    BST_DBG_LOG2("sRscpAvg=%d, sEci0Avg=%d", sRscpAvg, sEci0Avg );
}

/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_RscpVrc
 功能描述  : 计算信号方差
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_VOID BST_DRV_LsCal_RscpVrc( BST_INT16 sRscpAvg )
{
    BST_DRV_LS_INS_STRU                *pstLsIns;
    BST_INT16                           sRscpVrc;
    BST_UINT8                           ucIndex;

    sRscpVrc                            = 0;
    pstLsIns                            = BST_DRV_LsGetInstance();

    if( BST_TRUE != pstLsIns->stNetSta.usIsFull )
    {
        return;
    }

    for( ucIndex = 0; ucIndex < BST_DRV_LS_BUF_LENGTH; ucIndex++ )
    {
        sRscpVrc += (BST_INT16)(abs(pstLsIns->stNetSta.asRscp[ucIndex] - sRscpAvg));
    }

    /*根据方差值判断动静态*/
    if( sRscpVrc <= BST_DRV_LS_STATIC_VRC )
    {
        pstLsIns->usStaticCounter++;
        /*静态计数器大于BST_DRV_LS_STATIC_CNT，则认为当前处于静止状态*/
        if( pstLsIns->usStaticCounter >= BST_DRV_LS_STATIC_CNT )
        {
            pstLsIns->usStaticCounter = BST_DRV_LS_STATIC_CNT;
            pstLsIns->usMovingState   = BST_DRV_LS_STATE_STATIC;
        }
    }
    else
    {
        if( pstLsIns->usStaticCounter > 0 )
        {
            pstLsIns->usStaticCounter--;
        }
        else
        {
             pstLsIns->usStaticCounter = 0;
        }

        /*静态计数器小于BST_DRV_LS_DYNAMIC_CNT，则认为当前处于移动状态*/
        if( pstLsIns->usStaticCounter < BST_DRV_LS_DYNAMIC_CNT )
        {
            pstLsIns->usMovingState = BST_DRV_LS_STATE_DYNAMIC;
        }
    }

    BST_DBG_LOG3("sRscpVrc=%d, usStaticCounter=%d, usMovingState=%d",
                  sRscpVrc, pstLsIns->usStaticCounter, pstLsIns->usMovingState );

    return;
}

/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_LW_NCore
 功能描述  : LTE、WCDMA网络下信号质量信息计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_LW_NCore(
    BST_INT16                    sRscpAvg,
    BST_INT16                    sEci0Avg )
{
    BST_UINT32                          ulScore;
    BST_UINT32                          ulRscpScore;
    BST_UINT32                          ulEci0Score;
    BST_INT16                           sRscpMin;
    BST_INT16                           sRscpMax;
    BST_INT16                           sEci0Min;
    BST_INT16                           sEci0Max;
    BST_DRV_LS_THRESHOLD_STRU          *pstThold;
    BST_DRV_LS_INS_STRU                *pstLsIns;

    pstLsIns                            = BST_DRV_LsGetInstance();
    pstThold                            = BST_DRV_LsGetNetThreshold();
    ulScore                             = BST_AS_INVALID_SCORE;

    if( BST_AS_RAT_LTE == pstLsIns->ulCurRAT )
    {
        sRscpMin = pstThold->lte.sRsrpMin;
        sRscpMax = pstThold->lte.sRsrpMax;
        sEci0Min = pstThold->lte.sRsrqMin;
        sEci0Max = pstThold->lte.sRsrqMax;
    }
    else
    {
        sRscpMin = pstThold->wcdma.sRscpMin;
        sRscpMax = pstThold->wcdma.sRscpMax;
        sEci0Min = pstThold->wcdma.sEci0Min;
        sEci0Max = pstThold->wcdma.sEci0Max;
    }

    /*计算RSCP值得分*/
    if( sRscpAvg <= sRscpMin )
    {
        ulRscpScore = 0;
    }
    else if( sRscpAvg >= sRscpMax )
    {
        ulRscpScore = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*计算值先乘以100，最后除以门限区间值*/
        ulRscpScore = ( sRscpAvg - sRscpMin ) * BST_DRV_LS_ONE_HUNDRED;
        ulRscpScore = ulRscpScore >> BST_DRV_LS_BIT5_FAC;
    }

    /*计算ECI0值得分*/
    if( sEci0Avg <= sEci0Min )
    {
        ulEci0Score = 0;
    }
    else if( sEci0Avg >= sEci0Max )
    {
        ulEci0Score = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*计算值先乘以100，最后除以门限区间值*/
        ulEci0Score = ( sEci0Avg - sEci0Min ) * BST_DRV_LS_ONE_HUNDRED;
        ulEci0Score = ulEci0Score >> BST_DRV_LS_BIT4_FAC;
    }

    ulScore = ( ulRscpScore + ulEci0Score ) >> BST_DRV_LS_BIT1_FAC;

    return ulScore;
}

/*****************************************************************************
 函 数 名  : BST_DRV_LsCal_TG_NCore
 功能描述  : TDSCDMA、GSM网络下信号质量信息计算链路分数
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_STATIC  BST_UINT32 BST_DRV_LsCal_TG_NCore(
    BST_INT16                    sRscpMin,
    BST_INT16                    sRscpMax,
    BST_INT16                    sRscpAvg )
{
    BST_UINT32                          ulScore;

    ulScore                             = BST_AS_INVALID_SCORE;

    if( sRscpAvg <= sRscpMin )
    {
        ulScore = 0;
    }
    else if( sRscpAvg >= sRscpMax )
    {
        ulScore = BST_DRV_LS_FULL_SCORE;
    }
    else
    {
        /*计算值先乘以100，最后除以门限区间值*/
        ulScore = ( sRscpAvg - sRscpMin ) * BST_DRV_LS_ONE_HUNDRED;
        ulScore = ulScore >> BST_DRV_LS_BIT5_FAC;
    }

    return ulScore;
}

/*****************************************************************************
 函 数 名  : BST_DRV_LsItf_InitThreshold
 功能描述  : 设置GUTL制式下各个网络信号的门限值
 输入参数  :

 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年06月04日
      作    者   : l00220658
      修改内容   : 新生成函数
*****************************************************************************/
BST_VOID BST_DRV_LsItf_InitThreshold( BST_VOID )
{
    const BST_INT16                     asNetThreshold[] =
    {
        -110,    /* GSM 信号强度门限最小值 */
        -78,     /* GSM 信号强度门限最大值 */
        -117,    /* TDSCDMA 信号强度门限最小值 */
        -85,     /* TDSCDMA 信号强度门限最大值 */
        5,       /* TDSCDMA 重传率门限最小值 */
        65,      /* TDSCDMA 重传率门限最大值 */
        -120,    /* WCDMA 信号功率门限最小值 */
        -88,     /* WCDMA 信号功率门限最大值 */
        -21,     /* WCDMA 信号质量门限最小值 */
        -5,      /* WCDMA 信号质量门限最大值 */
        1,       /* WCDMA 重传率门限最小值 */
        55,      /* WCDMA 重传率门限最大值 */
        -125,    /* LTE 信号功率门限最小值 */
        -93,     /* LTE 信号功率门限最大值 */
        -21,     /* LTE 信号质量门限最小值 */
        -5,      /* LTE 信号质量门限最大值 */
        1,       /* LTE 重传率门限最小值 */
        50       /* LTE 重传率门限最大值 */
    };

    /* 网络质量门限赋值 */
    BST_OS_MEMCPY( BST_DRV_LsGetNetThreshold(),
                   &asNetThreshold[0],
                   BST_OS_SIZEOF( BST_DRV_LS_THRESHOLD_STRU ) );

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

