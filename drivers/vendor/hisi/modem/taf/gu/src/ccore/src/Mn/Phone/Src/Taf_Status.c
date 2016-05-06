/************************************************************
  Copyright (C), 2004-2005, Huawei Tech. Co., Ltd.

  FileName: tafstatus.c

  Author:   Roger     Version :   1.00     Date:  2005.3.30

  Description:
    MAPS1000软件协议栈应用适配层核心子层STATUS模块的API接口；
    为TAFM提供APP关于MM/GMM服务功能的调用接口；
    为TAFM提供客户端关于MM/GMM服务功能的AT命令；
  Version:
    MAPS1000 V100R001

  Function List:
  History:
      <author>  <time>   <version >   <desc>
      1.Roger    05/03/30     1.0     build this moudle
      2.liuyang  05/10/07     1.1     add attach & detach funcation
      3.liuyang  05/10/10     1.2     add functions that print the gobal Data and Status
      4.liuyang  05/10/21     1.3     modified Sta_ServiceStatusInd(),
                                    Sta_CoverageAreaInd(), Sta_DetachInd() & Sta_TimeoutProc
                                    for Problem No.A32D00650

      5.日    期   : 2006年3月3日
        作    者   : liuyang id:48197
        修改内容   : 问题单号：2310，增加定时器用于内部延时

      6.日    期   : 2006年3月13日
        作    者   : liuyang id:48197
        修改内容   : 问题单号:A32D02500
                     拆分内部启动过程与依靠网侧的启动过程两部分

      7.日    期   : 2006年3月21日
        作    者   : liuyang id:48197
        修改内容   : 问题单号：A32D02602,更改启动过程状态切换

      8.日    期   : 2006年3月27日
        作    者   : liuyang id:48197
        修改内容   : 问题单号:A32D02372

      9.日    期   : 2006年5月20日
        作    者   : liuyang id:48197
        修改内容   : 问题单号:A32D00739

     10.日    期   : 2006年9月04日
        作    者   : sunxibo id:46746
        修改内容   : 问题单号:A32D05624,PLMN LIST搜网时结果为0处理遗漏

     11.日    期   : 2006年9月13日
        作    者   : sunxibo id:46746
        修改内容   : 问题单号:A32D05600
     12.日    期   : 2006年11月2日
        作    者   : sunxibo id:46746
        修改内容   : 根据问题单号：A32D06406

     13.日    期   : 2006年11月07日
        作    者   : x51137
        修改内容   : 问题单A32D06630

     14.日    期   : 2006年12月07日
        作    者   : x51137
        修改内容   : 问题单A32D06630

     15.日    期   : 2006年12月7日
        作    者   : H59254
        修改内容   : 问题单号：A32D07836 华为移动新需求

     16.日    期   : 2006年12月20日
        作    者   : x51137
        修改内容   : A32D07369
     17.日    期   : 2007年01月05日
        作    者   : s46746
        修改内容   : A32D07668

     18.日    期   : 2007年2月2日
        作    者   : x51137
        修改内容   : 问题单号：A32D08596
     19.日    期   : 2007年02月09日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号A32D08488
     20.日    期   : 2007年4月30日
        作    者   : Li Jilin 60827
        修改内容   : 根据问题单号：A32D10733
     21.日    期   : 2007年5月20日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D11051
     22.日    期   : 2007年6月11日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D11538，将PIN码操作与开机流程分离
     23.日    期   : 2007年6月22日
        作    者   : Li Jilin 60827
        修改内容   : A32D11885 stop the protection timer in function Sta_UpdateFsmFlag before clearing the timer ID.
     24.日    期   : 2007年7月15日
        作    者   : Li Jilin 60827
        修改内容   : A32D12429 Modify the timer length
     25.日    期   : 2007年7月20日
        作    者   : Li Jilin 60827
        修改内容   : A32D12536
     26.日    期   : 2007年07月24日
        作    者   : Li Jilin
        修改内容   : A32D12559
     27.日    期   : 2007年07月21日
        作    者   : l60022475
        修改内容   : A32D12535
     28.日    期   : 2007年07月30日
        作    者   : Li Jilin
        修改内容   : A32D12620 Modify
     29.日    期   : 2007年10月4日
        作    者   : l60022475
        修改内容   : A32D12980
     30.日    期   : 2007年10月27日
        作    者   : luojian id:107747
        修改内容   : 根据问题单号：A32D13236
     31.日    期   : 2008年3月17日
        作    者   : s46746
        修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
     32.日    期   : 2008年07月15日
        作    者   : s46746
        修改内容   : 问题单号：AT2D04378,RF测试，提供上电自动开机功能
     33.日    期   : 2008年7月21日
        作    者   : luojian 00107747
        修改内容   : 问题单号：AT2D04201/AT2D04536,修改IMSI DETACH流程
     34.日    期   : 2008年7月28日
        作    者   : luojian id:107747
        修改内容   : 问题单号：AT2D04707/AT2D04722，修改上报卡状态时机
     35.日    期   : 2008年8月05日
        作    者   : s46746
        修改内容   : 问题单号：AT2D04712，修改SYSINFO上报HSPA状态
     36.日    期   : 2008年8月13日
        作    者   : s46746
        修改内容   : 问题单号：AT2D05035，RF自动开机测试时，需用打开RF&BBP
     37.日    期   : 2008年09月02日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05430,修改TAF_PH_EVT_PLMN_USER_SEL和TAF_PH_EVT_PLMN_RESEL事件上报
     38.日    期   : 2008年10月16日
        作    者   : l00130025
        修改内容   : 根据问题单号：AT2D6236:添加TAF_PH_EVT_SYS_CFG_CNF信息上报
     39.日    期   : 2008年12月05日
        作    者   : x00115505
        修改内容   : 根据问题单号：AT2D07039:设置CFUN为4之后，SRVST,MODE
                     没有主动上报；设置CFUN为6之后，SIMST上报错误。
     40.日    期   : 2008年12月06日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D07317,列表搜网时，网络状态显示不准确；等待搜网搜网标识需要及时清楚；系统消息子模式显示错误；
     41.日    期   : 2008年12月08日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D07318,SYSCFG命令有Detach/Attach操作时,若底层已完成，不需等待Attach CNF；
     42.日    期   : 2008年12月15日
        作    者   : h44270
        修改内容   : 问题单号AT2D07140
     43.日    期   : 2008年12月20日
        作    者   : l65478,l00130025
        修改内容   : 问题单号：AT2D07555，AT2D07488,指定搜网处理，加入双模搜索，待有注册结果后，再上报搜网结果
     44.日    期   : 2008年12月24日
        作    者   : x00115505
        修改内容   : 问题单号：AT2D07816,AT+CFUN=4之后，^SRVST,^MODE的
                     上报早于AT+CFUN=4的设置结果上报。
     45.日    期   : 2008年12月25日
        作    者   : h44270
        修改内容   : 问题单号：AT2D07647,PUK解锁后，LED灯指示错误
                     上报早于AT+CFUN=4的设置结果上报。
     46.日    期   : 2008年12月30日
        作    者   : x00115505
        修改内容   : 问题单号：AT2D07967,HSDPA数传后去激活，进行R99数传，
                     LED点灯颜色为青灯常亮，显示错误。
     47.日    期   : 2008年12月31日
        作    者   : l65478,l00130025
        修改内容   : 问题单号：AT2D07971,ServiceStatus未及时准确上报
     48.日    期   : 2009年01月05日
        作    者   : l00130025
        修改内容   : 根据问题单AT2D07968,双模列表搜网完毕,搜网状态判断和排序调整
     49.日    期   : 2009年01月06日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D08132,接口消息ID_MMA_MMC_START_REQ中ucRoamCapability项未被初始化。
     50.日    期   : 2009年01月15日
        作    者   : l00130025
        修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
     51.日    期   : 2009年02月16日
        作    者   : x00115505
        修改内容   : 问题单号：AT2D08454,CS域注册成功，PS域注册失败，LED灯显示搜网状态
     52.日    期   : 2009年02月17日
        作    者   : o00132663
        修改内容   : 问题单号：AT2D09081,【GCF测试】GCF用例 9.4.2.2.1导致MMA,AT状态异常.
     53.日    期   : 2009年03月06日
        作    者   : o00132663
        修改内容   : 问题单号：AT2D09746,【B036】【终端自动化测试】搜网专项测试，系统模式指示项中，
                     概率出现手动搜网不可用网络成功的情况
     54.日    期   : 2009年04月03日
        作    者   : s46746
        修改内容   : 问题单号：AT2D10632,TA认证，需要上报服务状态事件以及EPLMN、FPLMN和IMSI Detach事件
     55.日    期   : 2009年04月24日
        作    者   : s62952
        修改内容   : 问题单AT2D11028
     56.日    期   : 2009年4月29日
        作    者   : h44270
        修改内容   : AT2D11218/AT2D11516
     57.日    期   : 2009年08月15日
        作    者   : x00115505
        修改内容   : AT2D13800,NV项恢复操作时间过长，一键式升级和多板加载用时都比较长
     58.日    期   : 2009年09月01日
        作    者   : x00115505
        修改内容   : AT2D14166,关机之后没有服务状态变化的主动上报^SRVST
     59.日    期   : 2009年9月7日
        作    者   : s46746
        修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
     60.日    期   : 2009年10月3日
        作    者   : s46746
        修改内容   : 问题单号：AT2D14936,Location Status Event 发送的时机和码流不正确
     61.日    期   : 2009年10月28日
        作    者   : x00115505
        修改内容   : 问题单号：AT2D15171,AT+COPS第四个注册上3G网络LED绿灯单闪一段时间后再改变回蓝灯单闪
     62.日    期   : 2009年11月13日
        作    者   : s46746
        修改内容   : 问题单号：AT2D15442,NAS下发到STK的事件Location status EVENT 过多
     63.日    期   : 2009年11月28日
        作    者   : s46746
        修改内容   : 问题单号：AT2D15677,澳大利亚漫游定制合入
     64.日    期   : 2010年01月11日
        作    者   : x00115505
        修改内容   : 问题单号：AT2D16304,V2 STK增量开发合入
     65.日    期   : 2010年04月21日
        作    者   : s46746
        修改内容   : 问题单号：AT2D18703,在需要PIN/PUK/PUK剩余次数为0以及锁卡时,AT+CFUN=1返回OK.
     66.日    期   : 2010年07月20日
        作    者   : s62952
        修改内容   : 飞行模式合入
     67.日    期   : 2012年03月7日
        作    者   : z60575
        修改内容   : 问题单DTS2012030702528
*****************************************************************************/

#include "MmaAppLocal.h"
#include "rfa.h"
#include "NasOmInterface.h"
#include "TTFMemInterface.h"
#include "NVIM_Interface.h"
#include "mdrv.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

#include "TafAppMma.h"
#include "TafMmcInterface.h"
#if ( FEATURE_ON == FEATURE_LTE )
#include "msp_nvim.h"
#endif
#include "NasUtranCtrlInterface.h"

#include "TafSdcLib.h"
#include "Taf_Status.h"

#include "NasUsimmApi.h"
#include "TafLog.h"
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
#include "TafMmaCtx.h"
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

#include "NasMtaInterface.h"

/* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
#include "NasStkInterface.h"
/* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */

/* Added by j00174725 for V9R1 干扰控制, 2013/08/13, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "MtcMmaInterface.h"
#endif
/* Added by j00174725 for V9R1 干扰控制, 2013/08/13, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
#include "TafMmaSndTaf.h"
#include "TafMmaProcNvim.h"
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
#include "TafMmaSndApp.h"
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */
#include "TafMmaMntn.h"
#include "TafMmaSndMscc.h"
#include "NasComm.h"
#include "NasMntn.h"
#include "TafMmaComFunc.h"

#include "TafMmaSndMtc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_STATUS_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */
/* STATUS 全局共享变量 */
STATUS_CONTEXT_STRU                     g_StatusContext;
extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

extern MMA_ME_PERSONALISATION_STATUS_STRU  g_stMmaMePersonalisationStatus;

MN_PH_REG_TIME_INFO_STRU            g_stRegTimeInfo = {0, 0, 0, 0};

extern MMA_TIMER_ST                            g_stPowerDownDelayTimer;

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */

extern VOS_UINT32                       g_ucUsimHotOutFlag;

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */


VOS_UINT32                              aStaTimerLen[STA_TIMER_BUTT] = {0};

/* Added by l00208543 for V9R1 STK升级, 2013-08-01, begin */
extern TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU g_stMmsStkLocStaSysInfo;
/* Added by l00208543 for V9R1 STK升级, 2013-08-01, end */

VOS_UINT8 g_MMA_IccStatus = 0xFE;

extern MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8  g_ucMmaDeactSimWhenPoweroff;

#define STA_INFO_PRINT     PS_LOG_LEVEL_INFO
#define STA_NORMAL_PRINT   PS_LOG_LEVEL_NORMAL
#define STA_WARNING_PRINT  PS_LOG_LEVEL_WARNING
#define STA_ERROR_PRINT    PS_LOG_LEVEL_ERROR


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*----------- STATUS 给TAFM提供的API接口函数 ------------*/
/*=======================================================*/

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

/*lint -save -e958 */

/*************************************************
  Function:
    Sta_MsgReqAbort
  Description:
     终止未完成的请求过程，
     并上报响应事件通知请求发起者。
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    VOS_UINT32  ulAbortType;    上报事件的参数类型
        STA_MSGABORT_OK     返回正常事件
        STA_MSGABORT_ERR    返回错误事件
  Output:
    无
  Return:
    STA_SUCCESS,        =0, 正常返回；
    STA_ERROR,          =1, 错误返回；
  Others:
      1.日    期   : 2008年10月16日
        作    者   : l00130025
        修改内容   : 根据问题单号：AT2D6236:添加TAF_PH_EVT_SYS_CFG_CNF信息上报
      2.日    期   : 2011年11月08日
        作    者   : c00173809
        修改内容   : AT Project
      3.日    期   : 2015年3月6日
        作    者   : b00269685
        修改内容   : 列表搜上报修改
*************************************************/
VOS_UINT32 Sta_MsgReqAbort ( VOS_UINT32 ulAbortType )
{
    VOS_UINT32      ulEvent;        /* 事件类型 */

    /* 未完成请求过程类型 */
    switch ( g_StatusContext.ulFsmState )
    {
        case STA_FSM_RESTART:
            ulEvent = TAF_PH_EVT_OPER_MODE_CNF;
            break;
        case STA_FSM_STOP:
            ulEvent = TAF_PH_EVT_OPER_MODE_CNF;
            break;
        case STA_FSM_PLMN_LIST:
            if (STA_MSGABORT_OK != ulAbortType)
            {
                TAF_MMA_PlmnListQryAbortReport();
            }
            else
            {
                g_StatusContext.ucOperateType |= STA_OP_PLMNLIST;
                Sta_PlmnListEventReport();
            }
            return STA_SUCCESS;
        case STA_FSM_PLMN_SEL:
            TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_NO_ERROR);
            return STA_SUCCESS;

        case STA_FSM_PLMN_RESEL:
            TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_ERROR);
            return STA_SUCCESS;


        /* 如果在SYSCFG过程，在SYSCFG状态机中处理abort。此处删除 */

        default:
            /* 未指定的请求过程，返回错误 */
            return STA_ERROR;
    }

    /* 确定返回事件错误类型 */
    if ( STA_MSGABORT_OK != ulAbortType )
    {
        g_StatusContext.ucOperateType = STA_OP_PHONEERROR;
    }

    Sta_EventReport ( g_StatusContext.ulCurOpId, ulEvent );

    return STA_SUCCESS;
}


/*****************************************************************************
 函 数 名  : MN_PH_UpdateBeginRegInfo
 功能描述  : 更新开始注册相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月8日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2013年7月30日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:g_ucMsccMsccNeedPin1全局变量删除使用SDC的SIM卡状态替换
  3.日    期   : 2014年1月28日
    作    者   : s00217060
    修改内容   : DTS2014011709107
*****************************************************************************/
VOS_VOID MN_PH_UpdateBeginRegTime( VOS_VOID  )
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    VOS_UINT8                           ucSdcSimStatus;
    VOS_UINT8                           ucIsNeedPin;

    ucSdcSimStatus          = TAF_SDC_GetSimStatus();

    /* 卡状态为需要PIN或PUK时，认为需要PIN码 */
    if ( (TAF_SDC_USIM_STATUS_SIM_PIN   == ucSdcSimStatus)
      || (TAF_SDC_USIM_STATUS_SIM_PUK   == ucSdcSimStatus) )
    {
        ucIsNeedPin = VOS_TRUE;
    }
    else
    {
        ucIsNeedPin = VOS_FALSE;
    }

    if ( ((TAF_MMA_FSM_PHONE_MODE        == TAF_MMA_GetCurrFsmId())
       || (MN_PH_REG_TIME_STATE_PINVALID == g_stRegTimeInfo.enRegTimeState))
      && (VOS_FALSE == ucIsNeedPin) )
    {
        g_stRegTimeInfo.ulBeginTick = VOS_GetSlice();
        MN_INFO_LOG1("MN_PH_UpdateBeginRegTime:first time",(VOS_INT16)g_stRegTimeInfo.ulBeginTick);
    }

    if (VOS_FALSE == ucIsNeedPin)
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
    {
        MN_INFO_LOG1("MN_PH_UpdateBeginRegTime:second time,no need pin",(VOS_INT16)g_stRegTimeInfo.ulBeginTick);
        g_stRegTimeInfo.enRegTimeState = MN_PH_REG_TIME_STATE_BEGIN;
        g_stRegTimeInfo.ulCostTime     = 0;
    }
    else
    {
        MN_INFO_LOG("MN_PH_UpdateBeginRegTime:need pin");
        g_stRegTimeInfo.enRegTimeState = MN_PH_REG_TIME_STATE_PINVALID;
    }
}

/*****************************************************************************
 函 数 名  : MN_PH_UpdateEndRegTime
 功能描述  : 更新注册结束时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月8日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2013年03月07日
    作    者   : f00179208
    修改内容   : timer由递减转换为递增
  3.日    期   : 2014年1月28日
    作    者   : s00217060
    修改内容   : DTS2014011709107:MMA报给AT时按slice上报
*****************************************************************************/
VOS_VOID  MN_PH_UpdateEndRegTime( VOS_VOID )
{
    if ( MN_PH_REG_TIME_STATE_BEGIN != g_stRegTimeInfo.enRegTimeState )
    {
        return;
    }

    g_stRegTimeInfo.ulEndTick = VOS_GetSlice();
    MN_INFO_LOG2("MN_PH_UpdateEndRegTime beginTick = 0x%x,endtick = 0x%x\r\n",
                 (VOS_INT16)g_stRegTimeInfo.ulBeginTick,(VOS_INT16)g_stRegTimeInfo.ulEndTick);

    /* 时间戳是由0开始递增，所以当前的时间戳应该大于上次。另在时间戳
       到0xFFFFFFFF时会重置到0，所以else分支处理这种情况 */
    /* MMA报给AT时，按slice上报，(32 * 1024)个slice是1S
       如果slice为0，表示没有注册成功；如果slice小于1S,AT按1S上报 */
    if (g_stRegTimeInfo.ulEndTick >= g_stRegTimeInfo.ulBeginTick)
    {
        g_stRegTimeInfo.ulCostTime
            = (g_stRegTimeInfo.ulEndTick - g_stRegTimeInfo.ulBeginTick);
    }
    else
    {
        /*lint -e961*/
        g_stRegTimeInfo.ulCostTime
            = (0xFFFFFFFF - g_stRegTimeInfo.ulBeginTick + g_stRegTimeInfo.ulEndTick);
        /*lint +e961*/
    }

    MN_INFO_LOG1("Into MN_PH_UpdateEndRegTime ulCostTime = 0x%x\r\n",(VOS_INT16)g_stRegTimeInfo.ulCostTime);
    g_stRegTimeInfo.enRegTimeState  = MN_PH_REG_TIME_STATE_END;
    g_stRegTimeInfo.ulEndTick       = 0;

}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


/*************************************************
  Function:
    Sta_PlmnList
  Description:
    PLMN搜索过程入口函数
  Calls:             被本函数调用的函数清单
  Called By:         调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;  命令操作标识
  Output:
    无
  Return:
    无
  Others:
      1.日    期   : 2011年11月08日
        作    者   : c00173809
        修改内容   : AT Project
  2.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : AT&T&DCM:冲突处理
  3.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容  : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2015年3月12日
    作    者   : b00269685
    修改内容   : 列表搜上报修改
*************************************************/
VOS_UINT32 Sta_PlmnList (VOS_VOID)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    VOS_UINT32          ulRet;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    /* PLMN_LIST状态输入条件检查异常*/
    /* 只有在ENABLE状态，或者REFRESH触发的自动搜网，才能下发list请求，否则返回错误*/
    if (VOS_TRUE != TAF_MMA_IsEnablePlmnList())
    {
        TAF_MMA_PlmnListErrorReport(TAF_ERR_PHONE_MSG_UNMATCH);

        return STA_ERROR;       /* 错误返回 */
    }


    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    ulRet = TAF_MMA_SndMsccPlmnListReq();

    if ( VOS_ERR == ulRet )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
    {
        STA_TRACE (STA_ERROR_PRINT,
            "Sta_PlmnList():ERROR: failed");

        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        return STA_ERROR;       /* 错误返回 */
    }

    /* 设置PLMN_LIST状态标志量 */
    g_StatusContext.ulFsmState = STA_FSM_PLMN_LIST;

    /* 启动PLMN_LIST状态定时器 */
    g_StatusContext.aucFsmSubFlag[0]         = STA_FSMSUB_MONO;
    g_StatusContext.aFsmSub[0].ucFsmStateSub = STA_FSMSUB_MONO;
    g_StatusContext.aFsmSub[0].TimerName     = STA_TIMER_PLMN_LIST;
    ulRet = NAS_StartRelTimer (
            &g_StatusContext.ahStaTimer[0],
            WUEPS_PID_MMA,
            aStaTimerLen[STA_TIMER_PLMN_LIST],
            TAF_MMA,
            MMA_MAKELPARAM(0, STA_TIMER_PLMN_LIST),
            VOS_RELTIMER_NOLOOP
            );
    if ( VOS_OK != ulRet )
    {
        /* 恢复原来的子状态标志 */
        if ( STA_ERROR
            == Sta_UpdateFsmFlag(STA_FSMSUB_NULL,
                STA_FSM_NULL, STA_UPDATE_MONO_CLEAR) )
        {
            STA_TRACE (STA_ERROR_PRINT,
                "Sta_PlmnList():ERROR:timer clear failed\n");
        }
        return STA_ERROR;
    }


    return STA_SUCCESS;         /* 正常返回 */
}

/* 该函数已经修改为TAF_MMA_ProcPlmnAutoReselReq_Main */

/*************************************************
  Function:
    Sta_PlmnSelect
  Description:
    指定PLMN选择过程入口函数
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    VOS_UINT32            ulOpId;   命令操作标识
    TAF_PLMN_ID_STRU  PlmnId;   指定的PLMN
    TAF_ACCESS_MODE AccessMode  指定的接入模式
    VOS_UINT8 ucReselMode       指定PLMN失败后的重选模式
  Output:
    无
  Return:
    无
  Others:
    modified by l48197 Oct.28, 2005, add a Parametre, which
    select the access mode of MS;

  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : AT&T&DCM:增加冲突处理
  2.日    期   : 2013年2月25日
    作    者   : s00217060
    修改内容   : DTS2013020206377:USIM卡禁止GSM接入并且是G单模时，不允许用户指定搜
                 SIM卡并且是L单模时，也不允许用户指定搜
  3.日    期  : 2013年4月1日
   作    者   : z00161729
   修改内容  : 主动上报AT命令控制下移至C核及mma和mscc接口调整

  4.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容  : DTS2013111103301:svlte需要关机状态支持cops设置，更新nv项搜网模式
  5.日    期   : 2014年7月22日
    作    者   : b00269685
    修改内容   : Fortify 清理
*************************************************/
VOS_VOID Sta_PlmnSelect ( VOS_UINT32 ulOpID, TAF_PLMN_ID_STRU PlmnId,
                        TAF_PH_RA_MODE AccessMode, VOS_UINT8 ucReselMode)
{
    VOS_UINT32                      ulRet;



    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    /* 记录输入参数 */
    g_StatusContext.StaPlmnId.Mcc = PlmnId.Mcc;
    g_StatusContext.StaPlmnId.Mnc = PlmnId.Mnc;

    ulRet = TAF_MMA_SndMsccPlmnSpecialReq((MMA_MSCC_PLMN_ID_STRU *)&PlmnId, AccessMode);

    if ( VOS_ERR == ulRet )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
    {
        STA_TRACE (STA_WARNING_PRINT,
            "Sta_PlmnSelect():WARNING: failed");
        return;           /* 错误返回 */
    }
    /* 记录当前的操作过程标识号 */
    g_StatusContext.ulCurOpId = ulOpID;

    /* 上报APP当前状态事件 */
    /*Sta_EventReport (ulOpID, TAF_PH_EVT_PLMN_SEL);*/

    /* 设置PLMN_SEL状态标志量 */
    g_StatusContext.ulFsmState = STA_FSM_PLMN_SEL;

    STA_TRACE1(STA_NORMAL_PRINT, "@@@@Sta_PlmnSelect:FsmState=",STA_FSM_PLMN_SEL);
    /* 启动PLMN_SEL状态定时器 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF, TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_RESEL_SET_CNF_LEN);

    /* 记录当前的操作过程标识号 */
    g_StatusContext.aFsmSub[0].ulOpId = ulOpID;
    /*
    清空当前的PLMNid
    modified by liuyang id:48197 date:2005-9-5 for V200R001
    */
    /* Sta_ClearCurPlmnId( &(g_StatusContext.CurPlmnId) ); */
    return;         /* 正常返回 */
}

/*************************************************
  Function:
    Sta_TimeoutProc
  Description:
    定时器超时处理函数
  Calls:                     被本函数调用的函数清单
  Called By:                 调用本函数的函数清单
  Input:
    REL_TIMER_MSG   *pMsg;   定时器参数结构指针
  Output:
    无
  Return:
    无
  Others:

  1.日    期   : 2006年3月14日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02500，启动过程更改，超时函数添加

  2.日    期   : 2006年3月27日
    作    者   : liuyang id:48197
    修改内容   : 问题单号:A32D02372
  3.日    期   : 2007年07月21日
    作    者   : l60022475
    修改内容   : A32D12535
  4.日    期   : 2011年09月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII 列表搜网状态机调整
  5.日    期   : 2011年12月7日
    作    者   : z00161729
    修改内容   : V7R1 PhaseIV指定搜增加abort机制修改
  6.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : AT&T&DCM:增加冲突处理
  7.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  8.日    期   : 2012年9月18日
    作    者   : s00217060
    修改内容   : for V7R1C50_At_Abort
  9.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
 10.日    期   : 2013年7月10日
    作    者   : w00176964
    修改内容   : VoLTE_Phase1项目:开关机定时器重新设计
***************************************************************************/
VOS_VOID Sta_TimeoutProc (REL_TIMER_MSG * pMsg)
{
    STA_TIMER_NAME_E                    TimerId;    /* 定时器状态名称*/
    VOS_UINT16                          TimerIndex; /* 定时器序号 */
    VOS_UINT32                          ulOpId;

    ulOpId  = STA_OPID_INVALID;

    /* 参数检查 */
    if ( VOS_NULL_PTR == pMsg )
    {
        STA_TRACE (STA_ERROR_PRINT,
            "Sta_TimeoutProc():ERROR:parameter invaild null PTR");
        return;
    }

    /*读取系统定时器消息,得到定时器ID和定时器索引*/
    TimerId     = (STA_TIMER_NAME_E)MMA_LOWORD(pMsg->ulPara);
    TimerIndex  = MMA_HIWORD(pMsg->ulPara);
    STA_TRACE1 (STA_WARNING_PRINT,
            "Sta_TimeoutProc():WARNING:Status Time Out, TimerId is ",TimerId);

    if (TimerIndex >= STA_TIMER_MAX)
    {
        STA_TRACE (STA_ERROR_PRINT,
                "Sta_TimeoutProc():TimerIndex over run.");
        return;
    }

    /* 系统定时器消息分发处理*/
    switch ( TimerId )
    {
        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, end */

        case STA_TIMER_PLMN_LIST :


            /* 暂时不向AT回复结果，收到ID_MSCC_MMA_PLMN_LIST_ABORT_CNF 后向
               AT回复*/

            /*清除当前状态标志，回到ENABLE状态*/
            /*  清除子状态描述信息 */
            /*此时应将OpId置为无效值*/
            ulOpId                                     = g_StatusContext.aFsmSub[TimerIndex].ulOpId;
            g_StatusContext.aFsmSub[TimerIndex].ulOpId = STA_OPID_INVALID;

            g_StatusContext.aFsmSub[TimerIndex].ucFsmStateSub
                = STA_FSMSUB_NULL;
            g_StatusContext.aFsmSub[TimerIndex].TimerName
                = STA_TIMER_NULL;
            g_StatusContext.aucFsmSubFlag[TimerIndex]
                = STA_FSMSUB_NULL;

            /* 调用处理函数 */
            TAF_MMA_RcvTimerPlmnListCnfExpired(ulOpId);

            break;


        default :
            /* do nothing */
            /* 输出跟踪调试信息 */
            STA_TRACE (STA_NORMAL_PRINT,
                "Sta_TimeoutProc():NORMAL:do nothing");
            return;
    }

    return;     /* 正常返回 */
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* 删除 Sta_SoftReset ( VOS_UINT8 ucResetMode )*/
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */

/* delete Sta_PlmnListAbort*/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------- 协议栈响应消息处理函数(内部使用) -----------*/
/*=======================================================*/




/*lint -e438 -e830*/


/*lint +e438 +e830*/


/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */


/*****************************************************************************
 Prototype    : Sta_SelPlmnSpecializeCnf
 Description  : 判断指定PLMN搜索是否失败
 Input        : None
 Output       : None
 Return Value : 无
 Calls        :
 Called By    :

  History        :
  1.Date         : 2005/11/6
    Author       : liuyang, id:48197
    Modification : Created function

  2.日    期   : 2006年3月30日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02372

  3.日    期   : 2007年2月2日
    作    者   : x51137
    修改内容   : 问题单号：A32D08596
  4.日    期   : 2010年12月04日
    作    者   : lijun 00171473
    修改内容   : DTS2010112602423,PDP激活时指定搜网的出错码当前为30,现改为3
  5.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  6.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  7.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容  : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT32 Sta_SelPlmnSpecializeCnf( VOS_UINT32 ulResult )
{
    STA_TRACE1(STA_NORMAL_PRINT, "@@@@Sta_SelPlmnSpecializeCnf:FsmState=",(VOS_INT32)g_StatusContext.ulFsmState);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */

    /*内部发起的指定搜网过程,只有在手动重选的过程中,完成PLMNList后会发起*/

    TAF_MMA_ReportSpecPlmnSrchResult(ulResult);
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    return MMA_SUCCESS;
}
/*****************************************************************************
 Prototype    : Sta_SelPlmnAutoSelCnf
 Description  : 判断auto PLMN搜索是否失败
 Input        : None
 Output       : None
 Return Value : VOS_UINT32
 Calls        :
 Called By    :

  History        :
  1.Date         : 2005/11/6
    Author       : liuyang, id:48197
    Modification : Created function

  2.日    期   : 2006年3月30日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02372

  3.日    期   : 2007年2月2日
    作    者   : x51137
    修改内容   : 问题单号：A32D08596
  4.日    期   : 2010年12月04日
    作    者   : lijun 00171473
    修改内容   : DTS2010112602423,PDP激活时指定搜网的出错码当前为30,现改为3
  5.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  6.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  7.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容  : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT32 Sta_SelPlmnAutoSelCnf( VOS_UINT32 ulResult )
{
    STA_TRACE1(STA_NORMAL_PRINT, "@@@@Sta_SelPlmnAutoSelCnf:FsmState=",(VOS_INT32)g_StatusContext.ulFsmState);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_REJ == ulResult))
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    {
        /*清理子状态*/
        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
        /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

         /* 上报当前指定搜网失败 */
        MMA_WARNINGLOG("Sta_SelPlmnAutoSelCnf():WARING:REJECT PLMN USER SEL");
        /* 上报APP当前状态事件 */
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_ERROR);

        return MMA_SUCCESS;
    }

    /*内部发起的指定搜网过程,只有在手动重选的过程中,完成PLMNList后会发起*/

    TAF_MMA_ReportAutoPlmnSrchResult(ulResult);

    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    return MMA_SUCCESS;
}

/*****************************************************************************
 函 数 名  : Sta_GetSysSubMode
 功能描述  : 获取W下的系统子模式
 输入参数  : STA_DATA_TRANSFER_STATUS_UINT8 ucDataTranAttri
 输出参数  : 无
 返 回 值  : VOS_UINT8 系统子模式
 调用函数  :
 修改历史      :
  1.日    期   : 2009年8月31日
    作    者   : o00132663
    修改内容   : 新生成函数

  2.日    期   : 2010年5月11日
    作    者   : o00132663
    修改内容   : AT2D18058, UE不显示HSPA+模式
  3.日    期   : 2010年08月13日
    作    者   : w00166186
    修改内容   : DTS2010081301232, 点灯问题

*****************************************************************************/
VOS_UINT8 Sta_GetSysSubMode_W(STA_DATA_TRANSFER_STATUS_UINT8      ucDataTranStatus ,
                                       STA_DATA_TRANSFER_MODE_UINT8        ucDataTranMode
                                       )
{
    VOS_UINT8                          ucSysSubMode;

    if (STA_DATA_TRANSFER_PDP_ACT == ucDataTranStatus)
    {
        switch  ( ucDataTranMode )
        {
            case STA_DATA_TRANSFER_HSDPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSDPA;
                break;
            case STA_DATA_TRANSFER_HSUPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSUPA;
                break;
            case STA_DATA_TRANSFER_HSDPA_AND_HSUPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSDPA_HSUPA;
                break;
            case STA_DATA_TRANSFER_HSPA_PLUS :
                ucSysSubMode = TAF_SYS_SUBMODE_HSPA_PLUS;
                break;

            case STA_DATA_TRANSFER_DC_HSPA_PLUS:
                ucSysSubMode = TAF_SYS_SUBMODE_DC_HSPA_PLUS;
                break;

            case STA_DATA_TRANSFER_DC_MIMO:
                ucSysSubMode = TAF_SYS_SUBMODE_DC_MIMO;
                break;



            default:
                ucSysSubMode = TAF_SYS_SUBMODE_WCDMA;
                break;
        }
    }
    else
    {
        ucSysSubMode = TAF_SYS_SUBMODE_WCDMA;
    }

    return ucSysSubMode;
}

/*****************************************************************************
 函 数 名  : Sta_GetSysSubMode_Td
 功能描述  : 获取TD下的系统子模式
 输入参数  : STA_DATA_TRANSFER_STATUS_UINT8 ucDataTranAttri
 输出参数  : 无
 返 回 值  : VOS_UINT8 系统子模式
 调用函数  :
 修改历史      :
  1.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 Sta_GetSysSubMode_Td(
    STA_DATA_TRANSFER_STATUS_UINT8      ucDataTranStatus,
    STA_DATA_TRANSFER_MODE_UINT8        ucDataTranMode
)
{
    VOS_UINT8                          ucSysSubMode;

    if (STA_DATA_TRANSFER_PDP_ACT == ucDataTranStatus)
    {
        switch  ( ucDataTranMode )
        {
            case STA_DATA_TRANSFER_HSDPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSDPA;
                break;

            case STA_DATA_TRANSFER_HSUPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSUPA;
                break;

            case STA_DATA_TRANSFER_HSDPA_AND_HSUPA :
                ucSysSubMode = TAF_SYS_SUBMODE_HSDPA_HSUPA;
                break;

            case STA_DATA_TRANSFER_HSPA_PLUS :
                ucSysSubMode = TAF_SYS_SUBMODE_HSPA_PLUS;
                break;

            default:
                ucSysSubMode = TAF_SYS_SUBMODE_TD_SCDMA;
                break;
        }
    }
    else
    {
        ucSysSubMode = TAF_SYS_SUBMODE_TD_SCDMA;
    }

    return ucSysSubMode;
}
/*****************************************************************************
 函 数 名  : Sta_ModeChangeEventReport
 功能描述  : 上报^MODE
 输入参数  : 新的系统模式/子模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 修改历史      :
  1.日    期   : 2009年8月31日
    作    者   : o00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID Sta_ModeChangeEventReport(VOS_UINT8 ucNewSysMode, VOS_UINT8 ucNewSysSubMode)
{
    TAF_MMA_MODE_CHANGE_IND_STRU        *pstModeChangeInd;

    if ( VOS_TRUE != TAF_MMA_IsModeChangeNeedRpt())
    {
        return ;
    }

    pstModeChangeInd = (TAF_MMA_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA, sizeof(TAF_MMA_MODE_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstModeChangeInd)
    {
        MMA_ERRORLOG("Sta_ModeChangeEventReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET((VOS_CHAR *)pstModeChangeInd + VOS_MSG_HEAD_LENGTH,
            0x00,
            (sizeof(TAF_MMA_MODE_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstModeChangeInd->MsgHeader.ulReceiverPid          = WUEPS_PID_AT;
    pstModeChangeInd->MsgHeader.ulMsgName              = ID_TAF_MMA_MODE_CHANGE_IND;
    pstModeChangeInd->usClientId                       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstModeChangeInd->ucOpId                           = MMA_OP_ID_INTERNAL;
    pstModeChangeInd->RatType                          = ucNewSysMode;
    pstModeChangeInd->ucSysSubMode                     = ucNewSysSubMode;

    PS_SEND_MSG(WUEPS_PID_MMA, pstModeChangeInd);

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : TAF_MMA_CheckRatValid
 功能描述  : 检查是否是有需要记录的改变的网络模式
 输入参数  : 系统模式
 输出参数  : 无
 返 回 值  : VOS_TRUE ---- 成功
             VOS_FALSE --- 失败
 调用函数  :
 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_CheckRatValid(VOS_UINT8 ucSysMode)
{
    switch (ucSysMode)
    {
        case TAF_PH_INFO_GSM_RAT:
        case TAF_PH_INFO_WCDMA_RAT:
        case TAF_PH_INFO_LTE_RAT:
        case TAF_PH_INFO_TD_SCDMA_RAT:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RatFrequentlySwitchProc
 功能描述  : 比较队列中最先进来的元素跟最后进来的元素时间差是否符合记录上报
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_RatFrequentlySwitchProc(
    NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU  *pstNewRatSwitchRecord
)
{
    NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU  stOldRatSwitchRecord;
    VOS_UINT32                          ulNvStatisticTime;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulActuallyReadLength;

    ulNvStatisticTime = TAF_SDC_GetErrlogRatSwitchStatisticTime();

    ulLength = sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU);

    /* 填充OldRatSwitchRecord结构 */
    PS_MEM_SET(&stOldRatSwitchRecord, 0x00, ulLength);

    ulFreeSize = TAF_SDC_GetRatSwitchRingBufferFreeBytes();

    /* 队列是否存满，存满则检查头部尾部数据时间差是否小于NV配置项 */
    if (0 == ulFreeSize)
    {
        ulActuallyReadLength = TAF_SDC_GetRecordFromRatSwitchRingBuf((VOS_CHAR *)&stOldRatSwitchRecord, ulLength);
        if (ulActuallyReadLength != ulLength)
        {
            return;
        }

        if ((pstNewRatSwitchRecord->ulSystemTick - stOldRatSwitchRecord.ulSystemTick)
            < (ulNvStatisticTime * PRE_SECOND_TO_TICK))
        {
            /* NV规定时间内，rat切换次数达到NV规定次数，属于频繁切换，需要记录 */
            TAF_MMA_RatFrequentlySwitchRecord();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RatSwitchRecord
 功能描述  : 存储GUTL模式切换并记录频率过高的切换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 修改历史      :
  1.日    期   : 2015年03月13日
    作    者   : zwx247453
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_RatSwitchRecord(
    VOS_UINT8                           ucNewSysMode
)
{
    NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU  stNewRatSwitchRecord;
    VOS_UINT32                          ulNvSwitchNum;                          /* NV配置的gutl切换的统计次数 */
    VOS_UINT32                          ulNvStatisticTime;                      /* NV配置的统计时间 */
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulActuallyWriteLength;
    TAF_PH_INFO_RAT_TYPE                ucOldSysMode;

    ulNvSwitchNum     = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulNvStatisticTime = TAF_SDC_GetErrlogRatSwitchStatisticTime();

    PS_MEM_SET(&stNewRatSwitchRecord, 0, sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

    stNewRatSwitchRecord.ulSystemTick   = VOS_GetTick();
    stNewRatSwitchRecord.ucRatType      = ucNewSysMode;
    NAS_MNTN_OutputPositionInfo(&stNewRatSwitchRecord.stPositionInfo);

    /* 如果当前变化的状态为无服务或者其他不需要记录的状态，则不做任何处理 */
    if (VOS_FALSE == TAF_MMA_CheckRatValid(ucNewSysMode))
    {
        return;
    }

    /* 如果NV项读取出来的数据异常，则返回 */
    if ((0 == ulNvSwitchNum)
     || (ulNvSwitchNum > NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN))
    {
        return;
    }

    if ((0 == ulNvStatisticTime)
     || (ulNvStatisticTime > NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME))
    {
        return;
    }

    /* 获取队列最后一次插入元素的模式类型 */
    ucOldSysMode = TAF_SDC_GetErrLogOldRatType();

    /* 本次切换的模式与前一次切换的模式一致，则不插入队列 */
    if (ucNewSysMode == ucOldSysMode)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU);

    /* 将元素插入到队列中 */
    ulActuallyWriteLength = TAF_SDC_PutRatSwitchRingBuf((VOS_CHAR *)&stNewRatSwitchRecord, ulLength);
    if (ulActuallyWriteLength != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RatSwitchRecord(): Push buffer error.");

        return;
    }

    /* 将这次切换的模式记录一下 */
    TAF_SDC_SetErrLogOldRatType(ucNewSysMode);

    /* 如果模式切换过于频繁，超过NV配置规定，则做记录上报 */
    TAF_MMA_RatFrequentlySwitchProc(&stNewRatSwitchRecord);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : Sta_UpdateDataTranStatusAndMode
 功能描述  : 根据MSCC上报的MSCC_DATATRAN_ATTRI_IND消息
              更新全局变量中的DataTranStatus和DataTranMode
 输入参数  : ucDataTranAttri MSCC上传得数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : for V7R1C50_GUTL_PhaseII 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2014年11月28日
   作    者   : l00305157
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID Sta_UpdateDataTranStatusAndMode(NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8 enDataTranAttri)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */

    switch (enDataTranAttri)
    {
        case NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_ACT:
            g_StatusContext.ucDataTranStatus = STA_DATA_TRANSFER_PDP_ACT;

            if ((TAF_SDC_SYS_MODE_WCDMA == TAF_SDC_GetSysMode())
             && (STA_DATA_TRANSFER_MODE_BUTT == g_StatusContext.ucDataTranMode))
            {
                g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_R99_ONLY;
            }
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_PDP_DEACT:
            g_StatusContext.ucDataTranStatus = STA_DATA_TRANSFER_PDP_DEACT;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_R99_ONLY:
            g_StatusContext.ucDataTranMode   = STA_DATA_TRANSFER_R99_ONLY;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA:
            g_StatusContext.ucDataTranMode   = STA_DATA_TRANSFER_HSDPA;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_HSUPA:
            g_StatusContext.ucDataTranMode   = STA_DATA_TRANSFER_HSUPA;
            break;
        case NAS_MSCC_PIF_DATATRAN_ATTRI_HSDPA_AND_HSUPA:
            g_StatusContext.ucDataTranMode   = STA_DATA_TRANSFER_HSDPA_AND_HSUPA;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_HSPA_PLUS:
            g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_HSPA_PLUS;
            break;

        /* Modified by z40661 for V7R1 点灯 , 2012-02-20, begin */
        case NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_DATA:
            g_StatusContext.ucDataTranStatus = STA_DATA_TRANSFER_PDP_ACT;
            g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_LTE_DATA;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_LTE_IDLE:
            g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_LTE_IDLE;
            break;
        /* Modified by z40661 for V7R1 点灯 , 2012-02-20, end */

        case NAS_MSCC_PIF_DATATRAN_ATTRI_DC_HSPA_PLUS:
            g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_DC_HSPA_PLUS;
            break;

        case NAS_MSCC_PIF_DATATRAN_ATTRI_DC_MIMO:
            g_StatusContext.ucDataTranMode = STA_DATA_TRANSFER_DC_MIMO;
            break;


        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
        default:
            STA_TRACE(STA_WARNING_PRINT, "Sta_DataTranAttri:Attri incorrect.");
            break;
    }

}

/*****************************************************************************
 函 数 名  : Sta_DataTranAttri
 功能描述  : 收到MSCC上报的MSCC_DATATRAN_ATTRI_IND消息
 输入参数  : ucDataTranAttri MSCC上传得数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年6月11日
    作    者   : sunxibo
    修改内容   : 新生成函数
  2.日    期   : 2009年9月1日
    作    者   : 欧阳飞 o00132663
    修改内容   : AT2D14178, 当系统子模式改变时，上报^mode。

  3.日    期   : 2010年5月11日
    作    者   : o00132663
    修改内容   : AT2D18058, UE不显示HSPA+模式

  4.日    期   : 2010年5月13日
    作    者   : o00132663
    修改内容   : AT2D19345,点灯优化，改为OAM点灯任务主动查询方式
  5.日    期   : 2010年8月14日
    作    者   : w00166186
    修改内容   : DTS2010081301232

  6.日    期   : 2012年2月20日
    作    者   : z40661
    修改内容   : 增加L模的点灯功能

  7.日    期   : 2012年6月1日
    作    者   : z40661
    修改内容   : DTS2012053006110,增加DC-HSPA+的上报
  8.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : for  V7R1C50_GUTL_PhaseII 3G的时候区分TD和W
  9.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
 10.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
 11.日    期   : 2014年11月29日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseI项目修改
*****************************************************************************/
VOS_UINT32 Sta_DataTranAttri(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8   ucOldWSysSubMode = TAF_SYS_SUBMODE_WCDMA;
    VOS_UINT8   ucNewWSysSubMode = TAF_SYS_SUBMODE_WCDMA;

    VOS_UINT8   ucOldTdSysSubMode = TAF_SYS_SUBMODE_TD_SCDMA;
    VOS_UINT8   ucNewTdSysSubMode = TAF_SYS_SUBMODE_TD_SCDMA;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_DATATRAN_ATTRI_IND_STRU    *pstDataTranAttri;

    pstDataTranAttri = (MSCC_MMA_DATATRAN_ATTRI_IND_STRU*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    enSysMode = TAF_SDC_GetSysMode();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    STA_TRACE1(STA_NORMAL_PRINT, "Sta_DataTranAttri:ucDataTranAttri=",(VOS_INT32)pstDataTranAttri->enDataTranAttri);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            ucOldWSysSubMode = Sta_GetSysSubMode_W(g_StatusContext.ucDataTranStatus,
                                                   g_StatusContext.ucDataTranMode);
        }
        else
        {
            ucOldTdSysSubMode = Sta_GetSysSubMode_Td(g_StatusContext.ucDataTranStatus,
                                                     g_StatusContext.ucDataTranMode);
        }
    }

    /* 更新全局变量中的DataTranStatus 和 DataTranStatus */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    Sta_UpdateDataTranStatusAndMode(pstDataTranAttri->enDataTranAttri);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */


    /* 上报^MODE事件，如果系统子模式有改变 */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
    {
        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
        {
            /* 当前UTRAN_MODE为FDD时，上报W的系统子模式 */
            ucNewWSysSubMode = Sta_GetSysSubMode_W(g_StatusContext.ucDataTranStatus,
                                                   g_StatusContext.ucDataTranMode);

            if(ucOldWSysSubMode != ucNewWSysSubMode)
            {

                Sta_ModeChangeEventReport(TAF_PH_INFO_WCDMA_RAT, ucNewWSysSubMode);

#if (FEATURE_ON == FEATURE_PTM)
                TAF_MMA_RatSwitchRecord(TAF_PH_INFO_WCDMA_RAT);
#endif
            }
        }
        else
        {
            /* 当前UTRAN_MODE为TDD时，上报TD的系统子模式 */
            ucNewTdSysSubMode = Sta_GetSysSubMode_Td(g_StatusContext.ucDataTranStatus,
                                                     g_StatusContext.ucDataTranMode);

            if(ucOldTdSysSubMode != ucNewTdSysSubMode)
            {

                Sta_ModeChangeEventReport(TAF_PH_INFO_TD_SCDMA_RAT, ucNewTdSysSubMode);

#if (FEATURE_ON == FEATURE_PTM)
                TAF_MMA_RatSwitchRecord(TAF_PH_INFO_TD_SCDMA_RAT);
#endif
            }
        }
    }

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : Sta_GetServiceStatus
 功能描述  : 得到当前的服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32  ulServiceStatus
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年2月10日
    作    者   : sunxibo
    修改内容   : 新生成函数
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT32 Sta_GetServiceStatus()
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    return TAF_SDC_GetServiceStatus();
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
}

/*****************************************************************************
 函 数 名  : Sta_IccStatusReport
 功能描述  : 得到当前的服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32  ulServiceStatus
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年2月10日
    作    者   : sunxibo
    修改内容   : 新生成函数
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年11月04日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
  4.日    期   : 2014年4月29日
    作    者   : w00176964
    修改内容   : ecall项目修改:删除TAF_SDC_SERVICE_STATUS_NO_IMSI

*****************************************************************************/
VOS_VOID Sta_IccStatusReport(
    VOS_UINT32                          ucLastSimCsRegStatus,
    VOS_UINT32                          ucLastSimPsRegStatus
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */
    VOS_UINT8                           ucSimStatus;
    VOS_UINT8                           ucSimLockStatus;
    VOS_UINT8                           ucCurSimCsRegStatus;
    VOS_UINT8                           ucCurSimPsRegStatus;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        ucSimStatus     = MMA_GetCsimStatus(VOS_FALSE);

        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetCsimMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }
    else
#endif
    {
        ucSimStatus = MMA_GetUsimStatus(VOS_FALSE);

        /* 获取锁卡状态 */
        if (MMA_SIM_IS_LOCK == MMA_GetMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }

    ucCurSimCsRegStatus = TAF_SDC_GetSimCsRegStatus();
    ucCurSimPsRegStatus = TAF_SDC_GetSimPsRegStatus();

    if (((ucLastSimCsRegStatus != ucCurSimCsRegStatus)
      && (VOS_FALSE            == ucCurSimCsRegStatus))
     || ((ucLastSimPsRegStatus != ucCurSimPsRegStatus)
      && (VOS_FALSE            == ucCurSimPsRegStatus)) )
    {
        if (TAF_PH_ME_SIM_UNLOCK == MMA_GetMeLockStatus())
        {
            TAF_MMA_SndAtIccStatusInd(ucSimStatus, ucSimLockStatus);
        }
    }
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

    return;
}

/*****************************************************************************
 函 数 名  : Sta_ReportServiceEvent
 功能描述  : 上报当前CS、PS的服务状态
 输入参数  : ulCsServiceStatus 老的CS服务状态
             ulPsServiceStatus 老的PS服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月1日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2009年8月15日
    作    者   : l65478
    修改内容   : 问题单号：AT2D13660,out of service之后，会上报两次LIMITE SERVICE事件
  3.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容  : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID Sta_ReportServiceEvent(VOS_UINT32 ulCsServiceStatus, VOS_UINT32 ulPsServiceStatus)
{
    static VOS_UINT8   ucLimitServiceSentFlg = VOS_FALSE;/* 标志limit service是否已经上报 */

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    if ((enCsServiceStatus != ulCsServiceStatus)
     || (enPsServiceStatus != ulPsServiceStatus))
    {
        if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
         && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus))
        {
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_CS_PS_SERVICE, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
            ucLimitServiceSentFlg = VOS_FALSE;
        }
        else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
        {
            /*当前仅CS处于normal service，则之前CS不为normal service或PS之前为normal service均需要上报CS_SERVICE*/
            if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != ulCsServiceStatus)
             || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulPsServiceStatus))
            {
                NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_CS_SERVICE, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
                ucLimitServiceSentFlg = VOS_FALSE;
            }
        }
        else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus)
        {
            if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != ulPsServiceStatus)
             || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulCsServiceStatus))
            {
                NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PS_SERVICE, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
                ucLimitServiceSentFlg = VOS_FALSE;
            }
        }
        else
        {
            /*当前处于limit service，则之前CS为normal service或PS之前为normal service均需要上报LIMIT_SERVICE*/
            if (((TAF_SDC_SERVICE_STATUS_NO_SERVICE != enPsServiceStatus)
             || (TAF_SDC_SERVICE_STATUS_NO_SERVICE != enCsServiceStatus))
             && (VOS_FALSE == ucLimitServiceSentFlg))
            {
                NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_LIMITED_SERVICE, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
                ucLimitServiceSentFlg = VOS_TRUE;
            }
        }
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
}


/* Added by l00208543 for V9R1 STK升级, 2013-07-26, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcCsServiceStatusChanged
 功能描述  : CS域的服务状态发生变换后的处理
 输入参数  : ucOldCsServiceStatus 在service status状态更新前的Cs域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月26日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID TAF_MMA_ProcCsServiceStatusChanged(VOS_UINT8 ucOldCsServiceStatus)
{
    if(VOS_TRUE == TAF_MMA_IsCsServiceStatusChanged(ucOldCsServiceStatus))
    {
        TAF_MMA_SndStkLocationInfoInd();
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsCsServiceStatusChanged
 功能描述  : 判断CS域的服务状态是否发生变换
 输入参数  : ucOldCsServiceStatus 在service status状态更新前的Cs域服务状态
 输出参数  : 无
 返 回 值  : VOS_UINT8 Cs域服务状态是否发生变换
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月26日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 TAF_MMA_IsCsServiceStatusChanged(VOS_UINT8 ucOldCsServiceStatus)
{
    if(ucOldCsServiceStatus != TAF_SDC_GetCsServiceStatus())
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : Sta_IsPsServiceStatusChanged
 功能描述  : 判断PS域的服务状态是否发生变换
 输入参数  : ucOldPsServiceStatus 在service status状态更新前的Ps域服务状态
 输出参数  : 无
 返 回 值  : VOS_UINT8 Ps域服务状态是否发生变换
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月26日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT8 TAF_MMA_IsPsServiceStatusChanged(VOS_UINT8 ucOldPsServiceStatus)
{
    if(ucOldPsServiceStatus != TAF_SDC_GetPsServiceStatus())
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/* Added by l00208543 for V9R1 STK升级, 2013-07-26, end */


/*****************************************************************************
 函 数 名  : TAF_SDC_IsSpecDomainUsimStatusInvalid
 功能描述  : 判断是否是永久性的原因掉网，目前只根据卡是否有效来判断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 是否是永久性的原因掉网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : l00305157
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SDC_IsSpecDomainUsimStatusInvalid(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32        enCnDomainId
)
{

    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucSimPsRegStatus;
    VOS_UINT8                           ucIsReceiveInvalidCause;

    ucSimCsRegStatus = TAF_SDC_GetSimCsRegStatus();
    ucSimPsRegStatus = TAF_SDC_GetSimPsRegStatus();

    ucIsReceiveInvalidCause = VOS_FALSE;

    switch ( enCnDomainId )
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
             if ((TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetUsimStatus())
              || (VOS_FALSE == ucSimCsRegStatus))
             {
                 ucIsReceiveInvalidCause = VOS_TRUE;
             }
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:
             if ((TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetUsimStatus())
              || (VOS_FALSE == ucSimPsRegStatus))
             {
                 ucIsReceiveInvalidCause = VOS_TRUE;
             }
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
             if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
             {
                 ucIsReceiveInvalidCause = VOS_TRUE;
             }
            break;

        default:
            /*返回错误 */
            ucIsReceiveInvalidCause = VOS_FALSE;
            break;
    }

    return ucIsReceiveInvalidCause;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsDelayRptFeatureActive
 功能描述  : 判断延时上报功能是否启用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 VOS_TRUE:启用了延时上报功能
                       VOS_FALSE:不启用延时上报功能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsDelayRptFeatureActive(VOS_VOID)
{

    if (VOS_FALSE == TAF_MMA_GetDelayReportServiceStatusFlg())
    {
        /*NV 未开启延时上报功能*/
        STA_TRACE (STA_WARNING_PRINT,
            "TAF_MMA_IsDelayRptFeatureActive():WARNING: DelayReportService NV was did not Config");
        return VOS_FALSE;
    }

    if (0 == TAF_MMA_GetDelayReportServiceStatusCfgTimerLen())
    {
        /*延时上报定时器时常配置为0,不启用延时上报功能*/
        STA_TRACE (STA_WARNING_PRINT,
            "TAF_MMA_IsDelayRptFeatureActive():WARNING: DelayReportServiceTimer Cfg is 0");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* TAF_MMA_IsSameAsAppServiceStatus 移到TafMmaComFun.c中 */



/*****************************************************************************
 函 数 名  : Sta_UpdateServiceStatus
 功能描述  : 更新变量ulServiceStatus
 输入参数  : ucDataTranAttri MSCC上传得数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年2月10日
    作    者   : sunxibo
    修改内容   : 新生成函数

  2.日    期   : 2009年4月29日
    作    者   : h44270

  3.日    期   : 2011年03月07日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2011021901753,出服务区30-40分钟后，在次进入服务区，后台仍然显示无服务，但实际可以进行业务

  4.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,进入DeepSleep状态时，Srvst与Sysinfo/Sysinfoex上报不一致
  5.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
  6.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  7.日    期   : 2015年09月11日
    作    者   : zwx247453
    修改内容   : DTS2015091001134 产品线自动化测试需求，hisi测试已经用不到
*****************************************************************************/
VOS_VOID Sta_UpdateServiceStatus(VOS_UINT32 ulServiceStatus, VOS_UINT32 ulCnDomainId)
{
    VOS_UINT32 ulPsServiceStatus;
    VOS_UINT32 ulCsServiceStatus;

    STA_TRACE1 (STA_INFO_PRINT,
        "Sta_UpdateServiceStatus():INFO:ulCnDomainId is: ", (VOS_INT32)ulCnDomainId);
    STA_TRACE1 (STA_INFO_PRINT,
        "Sta_UpdateServiceStatus():INFO:ulServiceStatus is: ", (VOS_INT32)ulServiceStatus);

    ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    /* 更新CS/PS服务状态 */
    switch (ulCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            if(NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != ulServiceStatus)
            {
                TAF_SDC_SetCsServiceStatus((VOS_UINT8)ulServiceStatus);
            }
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            if(NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != ulServiceStatus)
            {
                TAF_SDC_SetPsServiceStatus((VOS_UINT8)ulServiceStatus);
            }
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE:
        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            /* 这两种服务域只有MSCC才会上报，因此PS/CS都需要更新 */
            if(NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != ulServiceStatus)
            {
                TAF_SDC_SetCsServiceStatus((VOS_UINT8)ulServiceStatus);
                TAF_SDC_SetPsServiceStatus((VOS_UINT8)ulServiceStatus);
            }
            break;
        default:
            break;
    }

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */

    Sta_ReportServiceEvent(ulCsServiceStatus, ulPsServiceStatus);

    ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* 更新总的服务状态 */
    if (  (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == ulCsServiceStatus)
       && (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == ulPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == ulCsServiceStatus)
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
    }
    else if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == ulPsServiceStatus)
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == ulCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == ulPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == ulCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == ulPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);


        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
        {
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }

    }

    /* 更新总的服务域 */
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetServiceStatus() )
    {
        if(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == ulCnDomainId)
        {
            TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_SEARCHING);
        }
        else
        {
            switch(gstMmaValue.stSetMsClass.NewMsClassType)
            {
                case TAF_PH_MS_CLASS_A:
                case TAF_PH_MS_CLASS_B:
                    TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
                    break;
                case TAF_PH_MS_CLASS_CC:
                    TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
                    break;
                case TAF_PH_MS_CLASS_CG:
                    TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
                    break;
                case TAF_PH_MS_CLASS_NULL:
                    TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
                default:
                    TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
            }
        }
    }
    else
    {
        g_StatusContext.ulTimMaxFlg = VOS_FALSE;
    }

    if ( TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == TAF_SDC_GetServiceStatus() )
    {
        MN_PH_UpdateEndRegTime();
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
}


/*****************************************************************************
  Function:
    Sta_UpdateLocalState
  Description:
    判断是否是正常服务
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    MSCC_MMA_SERVICE_STATUS_IND_STRU *pServiceStatus; 输入参数结构指针
  Output:
    无
  Return:
    VOS_VOID
  Others:
  1 author:   L65478 2008-12-19
  2.日    期   : 2012年4月07日
    作    者   : l00130025
    修改内容   : DTS2012032600471,删除停止定时器的处理，场景:指定搜网过程中，收到服务状态上报，导致MMA的保护定时器被停止
  3.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID Sta_UpdateLocalState(
    MSCC_MMA_SERVICE_STATUS_IND_STRU    *pServiceStatus,
    VOS_UINT8                           ucFsmSubOperate
)
{
    STA_PHONE_DATA_S                    Update;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    Update.ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    Update.ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();
    Update.ucDomainFlag      = NAS_MSCC_PIF_SRVDOMAIN_CS_PS;
    Update.ulCsCause         = 0;
    Update.ulPsCause         = 0;

    Update.PlmnId.Mcc        = pstPlmnId->ulMcc;
    Update.PlmnId.Mnc        = pstPlmnId->ulMnc;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    Update.ucFsmSubOperate   = ucFsmSubOperate;
    Update.ulFsmState        = STA_FSM_ENABLE;
    Update.ucFsmStateSub     = STA_FSMSUB_NULL;
    Update.ucFsmUpdateFlag   = STA_UPDATE_MONO_CLEAR;

    if ( STA_ERROR == Sta_UpdateData (&Update) )
    {
        STA_TRACE (STA_WARNING_PRINT,
            "Sta_UpdateLocalState():WARNING:Sta_UpdateData failed");
    }
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_IsPsSrvStatusChanged
 功能描述  : 判断PS的服务状态是否发生改变
 输入参数  : enCnDomainId-----指定域
             enServiceStatus----当前服务状态
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月12日
    作    者   : w00176964
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsPsSrvStatusChanged(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enServiceStatus
)
{
    if ((NAS_MSCC_PIF_SRVDOMAIN_PS    == enCnDomainId)
     || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId))
    {
        if (TAF_SDC_GetPsServiceStatus() != enServiceStatus)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedDelayReportServiceStatus
 功能描述  : 判断是否需要延时上报注册状态
 输入参数  : enOldPsSrvSta          -- 旧的的ps域服务状态
             enOldCsSrvSta          -- 旧的的cs域服务状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要延时上报
             VOS_FALSE: 不需要延时上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportServiceStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32  enServiceStatus
)
{
    TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstAppServPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulCellInfoChg;
    VOS_UINT8                           ucIsNeedDelayRpt;


    pstAppServPlmnInfo  = &(TAF_SDC_GetAppNetworkInfo()->stAppSysInfo.stServPlmnInfo);
    ulCellInfoChg       = TAF_MMA_IsAppNetworkInfoCellChange(pstAppServPlmnInfo);
    ucIsNeedDelayRpt    = VOS_TRUE;

    /* 延迟特性NV关闭，需要立即上报 */
    if (VOS_FALSE == TAF_MMA_IsDelayRptFeatureActive())
    {
        return VOS_FALSE;
    }


    /* 当卡无效时需要立即上报 */
    if (VOS_TRUE == TAF_SDC_IsSpecDomainUsimStatusInvalid(enCnDomainId))
    {
        return VOS_FALSE;
    }

    /* 用户操作导致的服务状态改变,不起用延时上报 */
    if ((TAF_MMA_FSM_SYS_CFG == TAF_MMA_GetCurrFsmId())
     || (STA_FSM_ENABLE      != g_StatusContext.ulFsmState))
    {
        /* 用户操作导致的服务状态改变,不起用延时上报 */
        return VOS_FALSE;
    }


    /* MMC中没有上报MMA_MMC_SERVICE_STATUS_NO_IMSI/MMA_MMC_SERVICE_STATUS_NO_CHANGE/MMA_MMC_SERVICE_STATUS_DEEP_SLEEP的地方 */

    switch(enServiceStatus)
    {
        case NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE:

            /* 如果本次上报的服务状态为正常服务, */
            ucIsNeedDelayRpt    = VOS_FALSE;
            break;

         case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE:
         case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION:
         case NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE:

            /* APP中的服务状态是非normal service，需要直接上报 */
            if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus())
            {
                ucIsNeedDelayRpt    = VOS_FALSE;
            }
            else
            {
                /* APP中显示的是正常服务: 如果延迟定时器正在运行，表示当前域的服务状态正在延迟，或另外一个域的服务状态/注册状态正在延迟，需要继续延迟 */
                if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
                {
                    return VOS_TRUE;
                }

                /* APP中显示的是正常服务，延迟定时器不在运行,CS/PS域同时变为非正常服务，需要延迟上报 */
                if ((NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId)
                 || (NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == enCnDomainId))
                {
                    return VOS_TRUE;
                }

                /* APP中显示的是正常服务:如果延迟定时器不在运行，并且APP中的驻留信息与SDC中的相同，
                   表示当前域的注册状态需要上报已经更新了APP中的驻留信息，或者另外一个域的服务状态/注册状态需要上报已经更新了APP中的驻留信息
                   这两种情况都可以立即上报当前域的服务状态 */
                if (VOS_FALSE == ulCellInfoChg)
                {
                    return VOS_FALSE;
                }
            }

            break;

        default:
            break;

    }

    return ucIsNeedDelayRpt;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportServiceStatus_DelayRptTimerRun
 功能描述  : 延时定时器运行期间，是否需要上报服务状态确保和注册状态上报一致
 输入参数  : enCnDomainId             -- 服务域
             enServiceStatus          -- 域服务状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedReportServiceStatus_DelayRptTimerRun(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8  enCsSrvSta;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8  enPsSrvSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8      enAppCsRegState;
    TAF_SDC_REG_STATUS_ENUM_UINT8      enAppPsRegState;

    /*获取APP的上报保存的注册状态*/
    enAppCsRegState   = TAF_SDC_GetAppCsRegStatus();
    enAppPsRegState   = TAF_SDC_GetAppPsRegStatus();

    /*获取NETWORKINFO保存的内部保存的服务状态变量*/
    enCsSrvSta     = TAF_SDC_GetCsServiceStatus();
    enPsSrvSta     = TAF_SDC_GetPsServiceStatus();


    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enCsSrvSta)
     && ((NAS_MSCC_PIF_SRVDOMAIN_CS                 == enCnDomainId)
      || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS              == enCnDomainId)))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enPsSrvSta)
     && ((NAS_MSCC_PIF_SRVDOMAIN_PS                 == enCnDomainId)
      ||(NAS_MSCC_PIF_SRVDOMAIN_CS_PS               == enCnDomainId)))
    {
        return VOS_TRUE;
    }

    /*保持注册状态和服务状态上报一致*/
    if ((NAS_MSCC_PIF_SRVDOMAIN_CS           == enCnDomainId)
     && (TAF_SDC_REG_REGISTERED_HOME_NETWORK != enAppCsRegState)
     && (TAF_SDC_REG_REGISTERED_ROAM         != enAppCsRegState))
    {
        return VOS_TRUE;
    }

    if ((NAS_MSCC_PIF_SRVDOMAIN_PS           == enCnDomainId)
     && (TAF_SDC_REG_REGISTERED_HOME_NETWORK != enAppPsRegState)
     && (TAF_SDC_REG_REGISTERED_ROAM         != enAppPsRegState))
    {
        return VOS_TRUE;

    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportServiceStatus
 功能描述  : 判断是否需要上报服务状态
 输入参数  : enCnDomainId             -- 服务域
             enServiceStatus          -- 域服务状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedReportServiceStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32                      enCnDomainId,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus
)
{
    VOS_UINT8                           ucEnableDaleyRptSrvSta;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enDelayTimerStatus;


    ucEnableDaleyRptSrvSta = VOS_FALSE;
    enDelayTimerStatus     = TAF_MMA_TIMER_STATUS_BUTT;

    /*获取是否开启延时上报功能*/
    ucEnableDaleyRptSrvSta = TAF_MMA_GetDelayReportServiceStatusFlg();

    if (VOS_TRUE == ucEnableDaleyRptSrvSta)
    {
        enDelayTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
    }

    /*与APP保存状态相同则应需要不需要上报*/
    if (VOS_TRUE == TAF_MMA_IsSameAsAppServiceStatus((TAF_SDC_SERVICE_STATUS_ENUM_UINT8)enServiceStatus, enCnDomainId))
    {
        return VOS_FALSE;
    }

    /*要更新的域的卡状态为无效，则需要上报*/
    if (VOS_TRUE == TAF_SDC_IsSpecDomainUsimStatusInvalid(enCnDomainId))
    {
        return VOS_TRUE;
    }

    /*更新的服务状态时normal，需要上报*/
    if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enServiceStatus)
    {
        return VOS_TRUE;
    }

    if (TAF_MMA_TIMER_STATUS_RUNING == enDelayTimerStatus)
    {
        /*延时定时器运行期间，确保域注册状态保持一致*/
        if (VOS_FALSE == TAF_MMA_IsNeedReportServiceStatus_DelayRptTimerRun(enCnDomainId))
        {
            return VOS_FALSE;
        }

    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcServiceStatusReport
 功能描述  : 服务状态指示的消息上报处理
 输入参数  : ucNewSrvSta--MMA上报的服务状态消息
             ucOldSrvSta--MMA old 的服务状态信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  2.日    期   : 2015年10月21日
    作    者   : l00324781
    修改内容   : CDMA Iteration 18 函数名修改
*****************************************************************************/
VOS_VOID TAF_MMA_ProcServiceStatusReport(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    ucNewSrvSta,
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    ucOldSrvSta
)
{
    if (ucOldSrvSta != ucNewSrvSta)
    {
        TAF_MMA_ReportSrvStatus();
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedDelayReportRegStatus
 功能描述  : 判断注册状态0(REG_NOT_REGISTERED_NOT_SEARCH)是否需要延时上报注册状态
 输入参数  : enNewRegState           -- 注册状态

 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要延时上报
             VOS_FALSE: 不需要延时上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月21日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportRegStatus_NotRegNotSearch(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState
)
{
    TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstAppServPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulCellInfoChg;


    pstAppServPlmnInfo  = &(TAF_SDC_GetAppNetworkInfo()->stAppSysInfo.stServPlmnInfo);
    ulCellInfoChg       = TAF_MMA_IsAppNetworkInfoCellChange(pstAppServPlmnInfo);

    /* 该函数只处理NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH时是否需要延迟上报 */
    if (NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH != enNewRegState)
    {
        return VOS_TRUE;
    }

    /* 如果APP中显示的是非正常服务，不需要延迟，直接上报 */
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus())
    {
        return VOS_FALSE;
    }

    /* APP中显示的是正常服务: 如果延迟定时器正在运行，表示当前域的服务状态正在延迟，或另外一个域的服务状态/注册状态正在延迟，需要继续延迟 */
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
    {
        return VOS_TRUE;
    }

    /* APP中显示的是正常服务:如果延迟定时器不在运行，并且APP中的驻留信息与SDC中的相同，
       表示当前域的服务状态需要上报已经更新了APP中的驻留信息，或者另外一个域的服务状态/注册状态需要上报已经更新了APP中的驻留信息
       这两种情况都可以立即上报当前域的注册状态 */
    if (VOS_FALSE == ulCellInfoChg)
    {
        return VOS_FALSE;
    }

    /* 有没有可能CS+PS:normal service,周期性LAU/RAU/TAU时失败?这种场景ulCellInfoChg判不出来 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedDelayReportRegStatus
 功能描述  : 判断是否需要延时上报注册状态
 输入参数  : enCnDomainId           -- 服务域
             enNewRegState          -- 域的注册状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要延时上报
             VOS_FALSE: 不需要延时上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportRegStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState
)
{
    VOS_UINT8                           ucIsNeedDelayRpt;

    ucIsNeedDelayRpt                    = VOS_TRUE;


    /*延时上报功能未启用*/
    if (VOS_FALSE == TAF_MMA_IsDelayRptFeatureActive())
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == TAF_SDC_IsSpecDomainUsimStatusInvalid(enCnDomainId))
    {
        return VOS_FALSE;
    }

    if ((TAF_MMA_FSM_SYS_CFG == TAF_MMA_GetCurrFsmId())
     || (STA_FSM_ENABLE      != g_StatusContext.ulFsmState))
    {
        /*用户操作导致的服务状态改变,不起用延时上报*/
        return VOS_FALSE;
    }

    switch(enNewRegState)
    {
        case NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK:
        case NAS_MSCC_PIF_REG_REGISTERED_ROAM:

            /*恢复到normal register status直接上报*/
            ucIsNeedDelayRpt = VOS_FALSE;
            break;

        case NAS_MSCC_PIF_REG_NOT_REGISTERED_SEARCHING:

            if (VOS_TRUE == TAF_SDC_IsCurrentNormalRegStatus())
            {
                /*从normal到搜网需要延时*/
                ucIsNeedDelayRpt = VOS_TRUE;
            }
            else
            {
                ucIsNeedDelayRpt = VOS_FALSE;
            }
            break;

        case NAS_MSCC_PIF_REG_REGISTERED_DENIED:

            ucIsNeedDelayRpt = VOS_FALSE;
            break;

        case NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH:

            if (VOS_FALSE == TAF_MMA_IsNeedDelayReportRegStatus_NotRegNotSearch(NAS_MSCC_PIF_REG_NOT_REGISTERED_NOT_SEARCH))
            {
                ucIsNeedDelayRpt = VOS_FALSE;
            }
            break;

        default:
            break;
    }

    return ucIsNeedDelayRpt;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedDelayReportApsNoServiceStatus
 功能描述  : 判断是否需要延时上报APS DO或DO + L无服务状态
 输入参数  : TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM_UINT8 enDelayType:延迟类型(DO或者DO+L)
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要延时上报
             VOS_FALSE: 不需要延时上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年01月09日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportApsNoServiceStatus(
    TAF_MMA_DELAY_CL_REPORT_TYPE_ENUM_UINT8                 enDelayType
)
{
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubSysMode;
    TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU                   *pstClNoServiceDelayRpt  = VOS_NULL_PTR;

    enSubSysMode            = TAF_SDC_GetAppSysSubMode();
    pstClNoServiceDelayRpt  = TAF_MMA_GetCLNoServiceDelayRptInfo();

    if (enDelayType >= TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT)
    {
        MMA_WARNINGLOG("TAF_MMA_IsNeedDelayReportApsNoServiceStatus: enDelayType >= BUTT! Return False");

        return VOS_FALSE;
    }

    /* 正在延迟过程中，不上报消息 */
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE))
    {
        MMA_INFOLOG("TAF_MMA_IsNeedDelayReportApsNoServiceStatus: CL Delay Timer Already Running!");

        return VOS_TRUE;
    }

    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE))
    {
        MMA_INFOLOG("TAF_MMA_IsNeedDelayReportApsNoServiceStatus: DO Delay Timer Already Running!");

        return VOS_TRUE;
    }

    /* EHPRD LTE下才延迟上报APS DO 或者DO + L无服务 */
    if ((TAF_SDC_SYS_SUBMODE_EHRPD      != enSubSysMode)
     && (TAF_SDC_SYS_SUBMODE_LTE        != enSubSysMode))
    {
        MMA_INFOLOG1("TAF_MMA_IsNeedDelayReportApsNoServiceStatus:Current SubMode Not In Lte Or Hrpd, SubMode:", (VOS_UINT32)enSubSysMode);

        return VOS_FALSE;
    }

    pstClNoServiceDelayRpt->enDelayType   = enDelayType;

    if (TAF_SDC_SYS_SUBMODE_EHRPD == enSubSysMode)
    {
        if (0 == pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen)
        {
            MMA_INFOLOG("TAF_MMA_IsNeedDelayReportApsNoServiceStatus:enDelayType DO,TimerLen 0,No Need Delay!");

            return VOS_FALSE;
        }

        TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE, (pstClNoServiceDelayRpt->ucDoNoServiceDelayRptLen * 1000));

        return VOS_TRUE;
    }

    if (0 == pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen)
    {
        MMA_INFOLOG("TAF_MMA_IsNeedDelayReportApsNoServiceStatus:enDelayType DO+LTE,TimerLen 0,No Need Delay!");

        return VOS_FALSE;
    }

    TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE, (pstClNoServiceDelayRpt->ucCLNoServiceDelayRptLen * 1000));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Proc3gppMsccServiceStatusIndInGulMode
 功能描述  : GUL收到MSCC的服务状态指示的消息处理
 输入参数  : pstServiceStatus--MSCC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月24日
    作    者   : h00313353
    修改内容   : 新生成函数
  2.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  3.日    期   : 2015年9月17日
    作    者   : s00217060
    修改内容   : DTS2015091409113修改
  4.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccServiceStatusIndInGulMode(
    MSCC_MMA_SERVICE_STATUS_IND_STRU    *pstServiceStatus
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldAppSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldAppSysSubMode;
    TAF_SDC_SERVICED_PLMN_INFO_STRU     stOldAppPlmnInfo;
    VOS_UINT8                           ucOldCsSrvSta;
    VOS_UINT8                           ucOldPsSrvSta;

    ucOldPsSrvSta   = TAF_SDC_GetPsServiceStatus();
    ucOldCsSrvSta   = TAF_SDC_GetCsServiceStatus();

    /* 更新stAppNetworkInfo之前先获取一下旧的系统模式和新的服务状态 */
    enOldAppSysMode = TAF_SDC_GetAppSysMode();

    enOldAppSysSubMode = TAF_SDC_GetAppSysSubMode();

    PS_MEM_SET(&stOldAppPlmnInfo, 0, sizeof(TAF_SDC_SERVICED_PLMN_INFO_STRU));
    PS_MEM_CPY(&stOldAppPlmnInfo, &(TAF_SDC_GetAppNetworkInfo()->stAppSysInfo.stServPlmnInfo), sizeof(TAF_SDC_SERVICED_PLMN_INFO_STRU));

    Sta_UpdateServiceStatus(pstServiceStatus->enServiceStatus, pstServiceStatus->enCnDomainId);

#if (FEATURE_ON == FEATURE_BASTET)
    /* 降圈复杂度:和zhongwenguo确认，NO RF导致的无服务也需要上报 */
    TAF_MMA_ProcBastetServiceStatusInd(ucOldCsSrvSta, ucOldPsSrvSta);
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return;
    }
#endif

    /* PS服务状态发生变化通知IMSA或SPM模块 */
    TAF_MMA_NotifySrvInfoToSpm(pstServiceStatus->enCnDomainId, pstServiceStatus->enServiceStatus, ucOldPsSrvSta);

    /* 通知STK SERVICE INFO */
    TAF_MMA_ProcCsServiceStatusChanged(ucOldCsSrvSta);
    TAF_MMA_ProcLociStatusEvent();

    /* 上报准则:
        1.延迟特性NV关闭时立即上报
        2.正常服务立即上报
        3.注册被拒导致卡无效或者卡不在位立即上报
        4.用户操作导致的服务状态变化立即上报
        5.另外一个域已经上报(通过比较APP中的驻留信息和SDC中的驻留信息来判断)，当前域也立即上报
        6.非正常服务状态变化到另一个非正常服务状态立即上报
        7.正常服务化到非正常服务，并且延迟NV打开，卡有效，延迟上报
    */

    /* 收到MMC的服务状态时，对服务状态是否需要上报给AP的处理 */
    TAF_MMA_ProcServiceStatusReport_ServiceStatusInd(pstServiceStatus);

    /* 收到MMC的服务状态时，对注册状态是否需要上报给AP的处理 */
    TAF_MMA_ProcRegStatusReport_ServiceStatusInd(enOldAppSysMode, enOldAppSysSubMode, &stOldAppPlmnInfo);

    /* 收到MMC的服务状态时，对信号强度是否需要上报给AP的处理 */
    TAF_MMA_ProcRssiReport_ServiceStatusInd(enOldAppSysMode);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertSdcStaToReportSta
 功能描述  : 将SDC服务状态转为Rpt状态
 输入参数  : pstServiceStatus--MSCC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月24日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_MMA_ConvertSdcStaToReportSta(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE:
            return TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE:
        case TAF_SDC_SERVICE_STATUS_NO_IMSI:
            return TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION:
            return TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE;

        case TAF_SDC_SERVICE_STATUS_NO_SERVICE:
            return TAF_SDC_REPORT_SRVSTA_NO_SERVICE;

        case TAF_SDC_SERVICE_STATUS_NO_CHANGE:
            return TAF_SDC_GetServiceStatus();

        case TAF_SDC_SERVICE_STATUS_DEEP_SLEEP:
            return TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP;

        default:
            return TAF_SDC_REPORT_SRVSTA_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_Update3GppServiceStatusAndDomainCLMode
 功能描述  : CL模下，更新lte(PS域)的服务状态和总服务状态、域
 输入参数  : pstServiceStatus--MSCC上报的服务状态消息
 输出参数  :
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月13日
    作    者   : l00324781
    修改内容   : Iteration 18 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_Update3GppServiceStatusAndDomainCLMode(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enSrvStatus;

    /* 在使用SysMode之前，该值必须先刷新，此处必须使用新的SysMode */
    enSysMode   = TAF_SDC_GetSysMode();
    enSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstServiceStatus->enServiceStatus;

    /* 消除coverity告警 */
    if (TAF_SDC_SYS_MODE_BUTT == enSysMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_Update3GppServiceStatusAndDomainCLMode: System Mode is BUTT!");
    }

    /* 更新PS域服务状态 */
    TAF_SDC_SetPsServiceStatus(enSrvStatus);

    /* 更新服务域 */
    TAF_MMA_UpdateServiceDomainInClMode(enSysMode);


    /* 更新总服务状态,根据CS域服务状态和PS域服务状态更新总服务状态 */
    TAF_MMA_UpdateReportService();
}

#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcMsccServiceStatusInd
 功能描述  : 收到MSCC的服务状态指示的消息处理
 输入参数  : pstServiceStatus--MSCC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年11月25日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI项目修改
  3.日    期   : 2015年01月28日
    作    者   : y00245242
    修改内容   : iteration 9开发，下移IMSA接口到MSCC模块
  4.日    期   : 2015年4月27日
    作    者   : b00269685
    修改内容   : 上报rssi时需要判断一下rat
  5.日    期   : 2015年5月26日
    作    者   : h00313353
    修改内容   : 添加处理LTE和SVLTE
  6.日    期   : 2015年10月13日
    作    者   : l00324781
    修改内容   : Iteration 18 修改
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccServiceStatusInd(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enOldRptSrvStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    enSysMode                           = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                           = TAF_SDC_SYS_SUBMODE_BUTT;
    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 如果这时上报的不是PS域的服务状态，则直接过滤掉 */
        if ((NAS_MSCC_PIF_SRVDOMAIN_PS == pstServiceStatus->enCnDomainId)
         || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstServiceStatus->enCnDomainId))
        {
            /* 服务状态延时可维可测 */
            TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

            if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
            {
                TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);
                Mma_ModeChgReport(enSysMode, enSubMode);

                TAF_SDC_SetSysMode(enSysMode);
                TAF_SDC_SetSysSubMode(enSubMode);

                TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE);
                TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE);
                TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;
            }

            /* 保存老的总服务状态 */
            enOldRptSrvStatus = TAF_SDC_GetServiceStatus();

            /* 更新PS域服务状态，总状态，域类型 */
            TAF_MMA_Update3GppServiceStatusAndDomainCLMode(pstServiceStatus);

            /* 服务状态有更新时才进入函数处理 */
            if (enOldRptSrvStatus != TAF_SDC_GetServiceStatus())
            {
                TAF_MMA_ReportHrpdAndLteServiceState();
            }
            else
            {
                /* 更新PS域相关信息 */
                if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
                {
                    TAF_MMA_UpdateAppPsSrvInfoInClMode();
                }
            }

            TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

        }

    }
    else
#endif
    {
        /* 处理GU */
        TAF_MMA_Proc3gppMsccServiceStatusIndInGulMode(pstServiceStatus);
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_Proc3gppMsccRegStatusInd
 功能描述  : 收到MMC的注册状态状态指示的消息处理
 输入参数  : pstServiceStatus--MMC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  3.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改,原来的TAF_MMA_Proc3gppMsccRegStatusInd
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccRegStatusIndGulMode(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState;
    VOS_UINT32                          ucIsNeedRptRegStatus;
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldAppSysMode;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;
#endif

    /* 更新stAppNetworkInfo之前先获取一下旧的系统模式 */
    enOldAppSysMode                     = TAF_SDC_GetAppSysMode();

    enCnDomainId                        = pstServiceStatus->enCnDomainId;

    ucIsNeedRptRegStatus                = VOS_FALSE;

    enOldCsRegState                     = TAF_SDC_GetCsRegStatus();
    enOldPsRegState                     = TAF_SDC_GetPsRegStatus();

#if (FEATURE_ON == FEATURE_PTM)
    ucIsCLWork       = TAF_SDC_IsConfigCLInterWorkCOutside();
    ucIsUsimSrvAvail = TAF_MMA_IsUsimServiceAvailable();
#endif

    /* CL模式下，应该过滤CS的注册状态 */



    /*更新内部变量中保存RoamFlag*/
    TAF_MMA_UpdateRoamFlag((TAF_SDC_REG_STATUS_ENUM_UINT8)pstServiceStatus->enRegState);

    /*更新内部变量保存的注册状态*/
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        TAF_SDC_SetCsRegStatus(pstServiceStatus->enRegState);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        TAF_SDC_SetPsRegStatus(pstServiceStatus->enRegState);
    }
    else
    {
        STA_TRACE (STA_WARNING_PRINT,
            "TAF_MMA_ProcMsccRegStatusInd():WARNING:enCurRegStatus is TAF_SDC_REG_STATUS_BUTT");
    }

#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return;
    }
#endif

    /* 上报准则:
        1.延迟特性NV关闭时立即上报
        2.注册成功立即上报
        3.注册被拒导致卡无效或者卡不在位立即上报
        4.用户操作导致的注册状态立即上报
        5.另外一个域已经上报(通过比较APP中的驻留信息和SDC中的驻留信息来判断)，当前域也立即上报
        6.非注册成功状态变化到另一个非注册成功状态立即上报
        7.注册成功变化到非注册成功状态，并且延迟NV打开，卡有效，延迟上报
    */

    /*判断是否需要上报*/
    ucIsNeedRptRegStatus = TAF_MMA_IsNeedReportRegStatus_RegStatusInd(enCnDomainId,
                                                                      enOldCsRegState,
                                                                      enOldPsRegState,
                                                                      pstServiceStatus->enRegState);

    /*需要上报给AT*/
    if (VOS_TRUE == ucIsNeedRptRegStatus)
    {
        /*需要开启延时上报定时器*/
        if (VOS_TRUE == TAF_MMA_IsNeedDelayReportRegStatus(enCnDomainId, pstServiceStatus->enRegState))
        {
            /* 处理服务状态或注册状态延迟上报 */
            TAF_MMA_ProcDelayReport();
        }
        else
        {
            /* 省电优化场景识别 */
            if (VOS_TRUE == TAF_SDC_IsNeedReportRegStatusWhenNonnormalService((TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8)enCnDomainId, pstServiceStatus->enRegState))
            {
                /*上报注册状态*/
                TAF_MMA_SndAtRegStatus(enCnDomainId, pstServiceStatus->enRegState);
            }

            /*停止定时器*/
            if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == pstServiceStatus->enRegState)
             || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == pstServiceStatus->enRegState))
            {
                TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
            }

            /*更新APP中保存的注册状态*/
            TAF_MMA_UpdateAppRegStatusInfo(enCnDomainId);
        }
    }
    else
    {

        /*停止定时器*/
        if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == pstServiceStatus->enRegState)
         || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == pstServiceStatus->enRegState))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
        }
    }

#if (FEATURE_ON == FEATURE_PTM)
    /* 在非CL的形态下才上报 */
    if ((VOS_FALSE == ucIsCLWork)
     && (VOS_TRUE  == ucIsUsimSrvAvail))
    {
        TAF_MMA_ProcErrlogOosReport(enOldCsRegState,
                                    enOldPsRegState,
                                    pstServiceStatus);
    }
#endif


    /* MMC有可能先报注册状态，MMA会把appnetwork里的信息更新，收到服务状态时判不出来信号是否需要上报 */
    TAF_MMA_ProcRssiReport_ServiceStatusInd(enOldAppSysMode);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_MMA_Proc3gppMsccRegStatusIndClMode
 功能描述  : 收到MMC的注册状态状态指示的消息处理
 输入参数  : pstServiceStatus--MMC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  3.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改

  4.日    期   : 2015年11月19日
    作    者   : Y00213812
    修改内容   : 上报^MODE,删除冗余逻辑
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccRegStatusIndClMode(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    TAF_MMA_UpdateRoamFlag((TAF_SDC_REG_STATUS_ENUM_UINT8)pstServiceStatus->enRegState);

    /*如果不存在PS域，不处理 */
    if((NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstServiceStatus->enCnDomainId)
    || (NAS_MSCC_PIF_SRVDOMAIN_PS == pstServiceStatus->enCnDomainId))
    {
        /* 服务状态延时可维可测 */
        TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

        /* 更新本地的模式并上报 */
        if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == pstServiceStatus->enRegState)
         || (NAS_MSCC_PIF_REG_REGISTERED_ROAM == pstServiceStatus->enRegState))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);
            Mma_ModeChgReport(enSysMode, enSubMode);

            TAF_SDC_SetSysMode(enSysMode);
            TAF_SDC_SetSysSubMode(enSubMode);

            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE);
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE);
            TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;

            /* 通知APS当前的服务模式 */
            TAF_MMA_SndTafCLServiceStatusInd(MMA_TAF_RAT_TYPE_LTE, VOS_FALSE);

            /* CS延时定时器可能在运行，所以不能直接更新 */
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(TAF_SDC_LTE_NETWORK_EXIST);

            /* 根据SubMode更新服务域 */
            TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
        }


        TAF_MMA_ReportPsRegStatusInClMode(pstServiceStatus->enRegState);

        TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_Proc3gppMsccRegStatusInd
 功能描述  : 收到MMC的注册状态状态指示的消息处理
 输入参数  : pstServiceStatus--MMC上报的服务状态消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月1日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  3.日    期   : 2015年9月30日
    作    者   : j00354216
    修改内容   : CDMA Iteration 18 修改
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppMsccRegStatusInd(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 处理CL */
        TAF_MMA_Proc3gppMsccRegStatusIndClMode(pstServiceStatus);
    }
    else
#endif
    {
        /* 处理GU */
        TAF_MMA_Proc3gppMsccRegStatusIndGulMode(pstServiceStatus);
    }

    return;
}

/*************************************************
  Function:
    Sta_ServiceStatusInd
  Description:
    处理MSCC_SERVICE_STATUS_IND消息
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    MSCC_MMA_SERVICE_STATUS_IND_STRU *pServiceStatus; 输入参数结构指针
  Output:
    无
  Return:
    STA_SUCCESS         =0, 正常返回
    STA_ERROR           =1, 错误返回
  Others:
    author:   l48197 2005-10-21
    modified:
        在attach,detach过程中收到service_status_ind，直接返回，
        enable状态下，将当前子状态清零
  2.日    期   : 2006年12月7日
    作    者   : H59254
    修改内容   : 问题单号：A32D07836

  3.日    期   : 2010年5月13日
    作    者   : o00132663
    修改内容   : AT2D19345,点灯优化，改为OAM点灯任务主动查询方式

  3.日    期   : 2012年10月16日
    作    者   : z40661
    修改内容   : DTS202090604118
  4.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  5.日    期   : 2013年06月3日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，注册状态关机也需要上报
  6.日    期   : 2013年07月26日
    作    者   : l00208543
    修改内容   : CS服务状态变化时，向STK发送服务状态变化消息
  7.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  8.日    期   : 2013年07月27日
    作    者   : y00245242
    修改内容   : VoLTE_PhaseI项目修改:PS业务状态发生改变，通知IMSA
  9.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
 10.日    期   : 2013年07月27日
    作    者   : y00245242
    修改内容   : VoLTE_PhaseI项目修改:PS业务状态发生改变，通知IMSA
 12.日    期   : 2013年10月9日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII项目:服务状态的上报处理封装成函数
 13.日    期   : 2013年11月15日
    作    者   : l65478
    修改内容   : DTS2013111808478:关机过程中服务状态查询的结果时正常服务
 14.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0和1
 15.日    期   : 2014年3月20日
    作    者   : s00246516
    修改内容   : L-C互操作项目，向CMMCA上报服务状态
 16.日    期   : 2014年4月30日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整:上报SIMST的地方上移到这里
 17.日    期   : 2014年6月16日
    作    者   : w00167002
    修改内容   : 若有no rf标志，则直接不处理
 18.日    期   : 2014年11月25日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
 19.日    期   : 2015年4月1日
    作    者   : B00269685
    修改内容   : 在收到注册状态时更新roam flg
 20.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
*************************************************/
VOS_UINT32 Sta_ServiceStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    STA_PHONE_DATA_S                    Update;         /* 需要更新的全局数据 */
    VOS_UINT32                          ulRet;
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;

    VOS_UINT8                           ucLastSimCsRegStatus;
    VOS_UINT8                           ucLastSimPsRegStatus;

#if ((FEATURE_MULTI_MODEM == FEATURE_ON) || (FEATURE_CL_INTERWORK == FEATURE_ON))
    VOS_UINT32                          ulOldUsimValidStatus;
    VOS_UINT32                          ulNewUsimValidStatus;
#endif
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

#if (FEATURE_CL_INTERWORK == FEATURE_ON)
    VOS_UINT8                           ulOldSrvSta;
#endif

    MSCC_MMA_SERVICE_STATUS_IND_STRU    *pServiceStatus;

    pServiceStatus = (MSCC_MMA_SERVICE_STATUS_IND_STRU*)pstMsg;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();

#if (FEATURE_CL_INTERWORK == FEATURE_ON)
    ulOldSrvSta     = TAF_SDC_GetServiceStatus();
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    ulOldUsimValidStatus = TAF_SDC_IsUsimStausValid();
#endif

    ucLastSimCsRegStatus    = TAF_SDC_GetSimCsRegStatus();
    ucLastSimPsRegStatus    = TAF_SDC_GetSimPsRegStatus();

    /* 更新SDC中的SIM卡的CS/PS的注册状态 */
    TAF_SDC_SetSimCsRegStatus(pServiceStatus->ucSimCsRegStatus);
    TAF_SDC_SetSimPsRegStatus(pServiceStatus->ucSimPsRegStatus);

    Sta_IccStatusReport(ucLastSimCsRegStatus, ucLastSimPsRegStatus);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    ulNewUsimValidStatus = TAF_SDC_IsUsimStausValid();

    /* 如果cs ps卡状态发生改变需要通知mtc */
    if (ulOldUsimValidStatus != ulNewUsimValidStatus)
    {
        TAF_MMA_SndMtcRegStatusInd((VOS_UINT8)ulNewUsimValidStatus);
    }
#endif

    enSysMode = TAF_SDC_GetSysMode();

    /* 更新本地的服务状态 */
    if (VOS_TRUE == pServiceStatus->bitOpSrvSta)
    {
        if (((TAF_SDC_SYS_MODE_EVDO == enSysMode)
          || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
          && (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE != pServiceStatus->enServiceStatus))
        {
        }
        else
        {
            TAF_MMA_Proc3gppMsccServiceStatusInd(pServiceStatus);
        }
    }

    /*注册状态上报处理*/
    if (VOS_TRUE == pServiceStatus->bitOpRegSta)
    {
        if (((TAF_SDC_SYS_MODE_EVDO == enSysMode)
          || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
          && (NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != pServiceStatus->enRegState)
          && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != pServiceStatus->enRegState))
        {

        }
        else
        {
            TAF_MMA_Proc3gppMsccRegStatusInd(pServiceStatus);
        }
    }

#if (FEATURE_CL_INTERWORK == FEATURE_ON)
    if ((ulOldSrvSta != TAF_SDC_GetServiceStatus())
     || (ulOldUsimValidStatus != ulNewUsimValidStatus))
    {
        if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
        {
            TAF_MMA_SndCmmcaServiceInd();
        }
    }
#endif

    switch ( g_StatusContext.ulFsmState )
    {/* 系统状态 */
        case  STA_FSM_PLMN_SEL:

            Sta_UpdateLocalState(pServiceStatus, STA_FSMSUB_UPDATE);

            break;

        case  STA_FSM_ENABLE:

            /*取得PS和CS域的服务信息*/
            /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
            Update.ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
            Update.ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();
            Update.ucDomainFlag      = (VOS_UINT8)pServiceStatus->enCnDomainId;
            Update.ulCsCause         = 0;
            Update.ulPsCause         = 0;

            Update.PlmnId.Mcc        = pstPlmnId->ulMcc;
            Update.PlmnId.Mnc        = pstPlmnId->ulMnc;

            /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

            Update.ucFsmSubOperate   = STA_FSMSUB_FINISH;
            Update.ulFsmState        = STA_FSM_ENABLE;
            Update.ucFsmStateSub     = STA_FSMSUB_NULL;
            Update.ucFsmUpdateFlag   = STA_UPDATE_DUAL_CLEAR;


            ulRet = Sta_UpdateData (&Update);
            if ( STA_ERROR == ulRet )
            {
                STA_TRACE (STA_WARNING_PRINT,
                    "Sta_ServiceStatusInd():WARNING:Sta_UpdateData failed");
            }

            break;

        default:

            break;
    }

    return VOS_TRUE;         /* 正常返回 */
}

/*************************************************
  Function:
    Sta_DetachInd
  Description:
    处理MSCC_DETACH_IND消息
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    ST_MSCC_DETACH_IND   *pDetachInd; 输入参数结构指针
  Output:
    无
  Return:
    STA_SUCCESS         =0, 正常返回
    STA_ERROR           =1, 错误返回
  Others:
     author:   l48197 2005-10-21
     modified:
        在attach,detach过程中收到service_status_ind，直接返回，
        enable状态下，将当前子状态清零
 2.日    期   : 2013年4月2日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
 3.日    期   : 2013年7月26日
   作    者   : l00208543
   修改内容   : STK升级项目
 4.日    期   : 2012年07月15日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*************************************************/
VOS_UINT32 Sta_DetachInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    STA_PHONE_DATA_S                    Update; /* 需要更新的全局数据 */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulOldSrvSta;
    /* Added by l00208543 for V9R1 STK升级, 2013-07-26, begin */
    VOS_UINT8                           ucOldCsSrvSta;
    /* Added by l00208543 for V9R1 STK升级, 2013-07-26, end */

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_DETACH_IND_STRU            *pDetachInd;

    pDetachInd = (MSCC_MMA_DETACH_IND_STRU*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

   /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */

    /* ENABLE状态*/
    if ( g_StatusContext.ulFsmState & STA_FSM_ENABLE )
    {
        ulOldSrvSta = TAF_SDC_GetServiceStatus();

        /* Added by l00208543 for V9R1 STK升级, 2013-07-26, begin */
        ucOldCsSrvSta = TAF_SDC_GetCsServiceStatus();
        /* Added by l00208543 for V9R1 STK升级, 2013-07-26, end */

        Sta_UpdateServiceStatus(pDetachInd->enServiceStatus, pDetachInd->enCnDomainId);

        /* Added by l00208543 for V9R1 STK升级, 2013-07-26, begin */
        TAF_MMA_ProcCsServiceStatusChanged(ucOldCsSrvSta);
        /* Added by l00208543 for V9R1 STK升级, 2013-07-26, end */

        /*取得PS和CS域的服务信息*/
        Update.ulCsServiceStatus = TAF_SDC_GetCsServiceStatus();
        Update.ulPsServiceStatus = TAF_SDC_GetPsServiceStatus();
        Update.ulCsCause         = 0;
        Update.ulPsCause         = 0;
        Update.ucDomainFlag      = (VOS_UINT8)pDetachInd->enCnDomainId;

        Update.ucFsmSubOperate   = STA_FSMSUB_FINISH;
        Update.ulFsmState        = STA_FSM_ENABLE;
        Update.ucFsmStateSub     = STA_FSMSUB_NULL;
        Update.ucFsmUpdateFlag   = STA_UPDATE_DUAL_CLEAR;
        ulRet = Sta_UpdateData (&Update);
        if ( STA_ERROR == ulRet )
        {
            STA_TRACE (STA_WARNING_PRINT,
                "Sta_DetachInd():WARNING:Sta_UpdateData failed");
        }

        if (ulOldSrvSta != TAF_SDC_GetServiceStatus())
        {
            TAF_MMA_ReportSrvStatus();
        }

        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
        return VOS_TRUE;
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    /* 没有做处理 */
    STA_TRACE (STA_WARNING_PRINT,
        "Sta_DetachInd():WARNING:invalid state, do nothing");

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*************************************************
  Function:
    Sta_ReOrderPlmnList
  Description:
    对双模列表搜网的上报结果,进行重排序,当前驻留PLMN有多个接入技术时,将当前注册的列表项调整到前面
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    TAF_PLMN_LIST_STRU    *pPlmnList; 输入参数结构指针
  Output:
    无
  Return:
    无
  Others:
  1.日    期   : 2008年01月05日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D07968
  2.日    期   : 2011年6月29日
    作    者   : z00161729
    修改内容   : V7R1 phase II支持syscfgex命令修改
  3.日    期   : 2011年09月14日
    作    者   : w00166186
    修改内容   : V7R1 phase II支持L模列表搜
*************************************************/
VOS_VOID Sta_ReOrderPlmnList (TAF_PLMN_LIST_STRU* pPlmnList)
{
    VOS_UINT32   ulRegPlmnIndx = TAF_MAX_PLMN_NUM;
    VOS_UINT32   ulSamePlmnIndx = TAF_MAX_PLMN_NUM;
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder = VOS_NULL_PTR;
    VOS_UINT32   ulIndx = 0;

    TAF_PLMN_ID_STRU    stPlmnId;
    TAF_PLMN_STATUS_STRU    stStatus;
    PS_MEM_SET(&stPlmnId, 0, sizeof(stPlmnId));
    PS_MEM_SET(&stStatus, 0, sizeof(stStatus));

    pstRatOrder     = TAF_MMA_GetRatPrioListAddr();

    /* 上报列表数小于2或当前模式非双模,可直接返回 */
    if( (pPlmnList->ucPlmnNum < 2 )
     || (pstRatOrder->ucRatOrderNum <= 1) )
    {
        return;
    }
    /* 确定当前是否有注册的PLMN */
    for( ulIndx = 0; ulIndx < pPlmnList->ucPlmnNum; ++ulIndx)
    {
        if( TAF_PH_NETWORK_STATUS_CURRENT == pPlmnList->PlmnInfo[ulIndx].PlmnStatus)
        {
            ulRegPlmnIndx = ulIndx;
        }
    }
    if(TAF_MAX_PLMN_NUM == ulRegPlmnIndx)
    {
        return; /* 上报列表中没有注册的PLMN 返回错误*/
    }
    stPlmnId.Mcc = pPlmnList->Plmn[ulRegPlmnIndx].Mcc;
    stPlmnId.Mnc = pPlmnList->Plmn[ulRegPlmnIndx].Mnc;
    /* 当前是双模且有注册的PLMN,确定列表中是否有其它列表项与当前注册的PLMN相同 */
    for( ulIndx = 0; ulIndx < pPlmnList->ucPlmnNum; ++ulIndx)
    {
        if( (stPlmnId.Mnc == pPlmnList->Plmn[ulIndx].Mnc)
            && (stPlmnId.Mcc == pPlmnList->Plmn[ulIndx].Mcc)
            && (ulIndx != ulRegPlmnIndx) )
        {
            ulSamePlmnIndx = ulIndx;
        }
    }
    if(TAF_MAX_PLMN_NUM == ulSamePlmnIndx)
    {
       return; /* 上报列表中没有与注册PLMN相同的列表项 */
    }
    if(ulRegPlmnIndx < ulSamePlmnIndx)
    {
       return; /* 上报列表中的注册PLMN的顺序已正常 ,返回*/
    }
    /* 调整注册PLMN项到前面 返回*/
    PS_MEM_CPY(&stStatus, &(pPlmnList->PlmnInfo[ulSamePlmnIndx]), sizeof(TAF_PLMN_STATUS_STRU));
    PS_MEM_CPY(&(pPlmnList->PlmnInfo[ulSamePlmnIndx]), &(pPlmnList->PlmnInfo[ulRegPlmnIndx]), sizeof(TAF_PLMN_STATUS_STRU));
    PS_MEM_CPY(&(pPlmnList->PlmnInfo[ulRegPlmnIndx]), &stStatus, sizeof(TAF_PLMN_STATUS_STRU));
    return; /* 上报列表中的注册PLMN的顺序调整完毕,返回*/
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : TAF_MMA_ClearCsgListSearchOperCtx
 功能描述  : 释放csg列表搜时分配的OperCtx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID TAF_MMA_ClearCsgListSearchOperCtx(VOS_VOID)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
    {
        return;
    }

    /* 清除CTX中内容,这里的para前面肯定分配过  */
    if (VOS_NULL_PTR != pstMmaOperCtx[ucCtxIndex].pPara)
    {
        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaOperCtx[ucCtxIndex].pPara);
        pstMmaOperCtx[ucCtxIndex].pPara = VOS_NULL_PTR;
    }

    TAF_MMA_ClearOperCtx(ucCtxIndex);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportCsgListSearchResult
 功能描述  : 列表搜结果上报
 输入参数  : pstCtrl         - 控制信息
             pstPlmnListCtrl - at csg list请求信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月28日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增

*****************************************************************************/
VOS_VOID TAF_MMA_ReportCsgListSearchResult(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl
)
{
    TAF_MMA_CSG_LIST_CNF_PARA_STRU     *pstPlmnListCnfPara = VOS_NULL_PTR;
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx      = VOS_NULL_PTR;
    VOS_UINT32                          ulSendNum;
    VOS_UINT32                          ulLeftNum;
    VOS_UINT32                          ulCurrIndex;
    VOS_UINT32                          ulIndex;
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU stAtOperName;

    PS_MEM_SET(&stAtOperName, 0, sizeof(stAtOperName));
    ulSendNum     = 0;
    ulLeftNum     = 0;
    ulCurrIndex   = 0;
    ulIndex       = 0;
    pstCsgListCtx = TAF_MMA_GetCsgListCtxAddr();

    pstPlmnListCnfPara = (TAF_MMA_CSG_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_CSG_LIST_CNF_PARA_STRU));

    if (VOS_NULL_PTR == pstPlmnListCnfPara)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"TAF_MMA_ReportCsgListSearchResult:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0, sizeof(TAF_MMA_CSG_LIST_CNF_PARA_STRU));

    pstPlmnListCnfPara->ucOpError          = VOS_FALSE;
    pstPlmnListCnfPara->ulCurrIndex        = pstPlmnListCtrl->usCurrIndex;
    pstPlmnListCnfPara->ucPlmnWithCsgIdNum = 0;

    ulSendNum = pstPlmnListCtrl->usReadNum;

    /* 如果要求读取的index大于等于csg PLmn list的总数目，认为是最后一次上报，上报一个空列表 */
    if (pstPlmnListCtrl->usCurrIndex >= (VOS_UINT16)pstCsgListCtx->ulPlmnWithCsgIdNum)
    {
        ulSendNum = 0;
    }
    else
    {
        ulLeftNum = (pstCsgListCtx->ulPlmnWithCsgIdNum - pstPlmnListCtrl->usCurrIndex);

        if (ulSendNum > ulLeftNum)
        {
            ulSendNum = ulLeftNum;
        }
    }

    for (ulIndex = 0; ulIndex < ulSendNum; ulIndex++)
    {
        if (ulIndex >= TAF_MMA_MAX_CSG_ID_LIST_NUM)
        {
            break;
        }

        ulCurrIndex = ulIndex + pstPlmnListCtrl->usCurrIndex;

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stPlmnId.Mcc = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stPlmnId.Mcc;
        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stPlmnId.Mnc = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stPlmnId.Mnc;
        MMA_PlmnId2Bcd(&(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stPlmnId));

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].ulCsgId = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].ulCsgId;

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stCsgType.ucCsgTypeLen;
        PS_MEM_CPY(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType, \
                   pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stCsgType.aucCsgType,  \
                   TAF_SDC_MIN(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen, TAF_MMA_MAX_CSG_TYPE_LEN));

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].enPlmnWithCsgIdType = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].enPlmnWithCsgIdType;

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen;
        PS_MEM_CPY(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName, \
                   pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].stCsgIdHomeNodeBName.aucHomeNodeBName,  \
                   TAF_SDC_MIN(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen, TAF_MMA_MAX_HOME_NODEB_NAME_LEN));

        pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].ucRaMode = pstCsgListCtx->astCsgIdListInfo[ulCurrIndex].ucRaMode;

        PS_MEM_SET(&stAtOperName,0,sizeof(stAtOperName));
        stAtOperName.OperName.PlmnId.Mcc  = pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stPlmnId.Mcc;
        stAtOperName.OperName.PlmnId.Mnc  = pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].stPlmnId.Mnc;
        stAtOperName.ListOp               = TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME;

        /* 获取优先网络的长短名 */
        if (MMA_SUCCESS == Taf_PhoneGetNetworkNameForListPlmn(&stAtOperName))
        {
            PS_MEM_CPY(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].aucOperatorNameLong, stAtOperName.OperName.aucOperatorNameLong,TAF_PH_OPER_NAME_LONG);
            PS_MEM_CPY(pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].aucOperatorNameShort, stAtOperName.OperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        }
        else
        {
            pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].aucOperatorNameLong[0]  = '\0';
            pstPlmnListCnfPara->astCsgIdListInfo[ulIndex].aucOperatorNameShort[0] = '\0';
        }

        pstPlmnListCnfPara->ucPlmnWithCsgIdNum++;
    }

    /* 上报 */
    TAF_MMA_SndCsgListSearchCnf(pstCtrl, pstPlmnListCnfPara);

    TAF_MMA_ClearCsgListSearchOperCtx();

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportCsgListError
 功能描述  : CSG列表搜错误结果上报
 输入参数  : pstCtrl - mma ctrl信息
             enError - 错误码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月30日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_VOID TAF_MMA_ReportCsgListError(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enError
)
{
    TAF_MMA_CSG_LIST_CNF_PARA_STRU     *pstPlmnListCnfPara = VOS_NULL_PTR;
    pstPlmnListCnfPara = (TAF_MMA_CSG_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_CSG_LIST_CNF_PARA_STRU));

    if (VOS_NULL_PTR == pstPlmnListCnfPara)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR, "TAF_MMA_ReportCsgListError:ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0, sizeof(TAF_MMA_CSG_LIST_CNF_PARA_STRU));

    /* 构造CSG LIST网回复事件 */
    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
    pstPlmnListCnfPara->enPhoneError = enError;

    TAF_MMA_SndCsgListSearchCnf(pstCtrl, pstPlmnListCnfPara);

    /* 清除csg list搜网oper ctx */
    TAF_MMA_ClearCsgListSearchOperCtx();

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    return;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnListReport
 功能描述  : 列表搜结果上报
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月6日
    作    者   : b00269685
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_MMA_PlmnListReport(
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_REQ, &ucCtxIndex))
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"TAF_MMA_PlmnListReport:ERROR: GET CTX FAIL.");
        return;
    }

    /* 上报 */
    TAF_MMA_SndPlmnListCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstPlmnListCnfPara);

    TAF_MMA_PlmnListClearOperCtx();

    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnListClearOperCtx
 功能描述  : 释放列表搜时分配的OperCtx
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月3日
    作    者   : c00318887
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_MMA_PlmnListClearOperCtx(VOS_VOID)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_REQ, &ucCtxIndex))
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"TAF_MMA_PlmnListReport:ERROR: GET CTX FAIL.");
        return;
    }

    /* 清除CTX中内容,这里的para前面肯定分配过  */
    if (VOS_NULL_PTR != pstMmaOperCtx[ucCtxIndex].pPara)
    {
        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaOperCtx[ucCtxIndex].pPara);
        pstMmaOperCtx[ucCtxIndex].pPara = VOS_NULL_PTR;
    }

    TAF_MMA_ClearOperCtx(ucCtxIndex);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnListErrorReport
 功能描述  : 列表搜错误结果上报
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月6日
    作    者   : b00269685
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_MMA_PlmnListErrorReport(
    TAF_ERROR_CODE_ENUM_UINT32          enError
)
{
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    if (VOS_NULL_PTR == pstPlmnListCnfPara)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR, "TAF_MMA_PlmnListErrorReport:ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* 构造LIST搜网回复事件 */
    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
    pstPlmnListCnfPara->enPhoneError = enError;

    TAF_MMA_PlmnListReport(pstPlmnListCnfPara);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnListQryAbortReport
 功能描述  : 列表搜错误结果上报
 输入参数  : ulOpID - operation ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月6日
    作    者   : b00269685
    修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_MMA_PlmnListQryAbortReport()
{
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    if (VOS_NULL_PTR == pstPlmnListCnfPara)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR, "TAF_MMA_PlmnListQryAbortReport:ERROR:ALLOC MEMORY FAIL.");

        return;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* 检查SIM卡状态,LIST搜网事件被打断的情况在有卡回复空列表,无卡回复ERROR */
    if (TAF_ERR_NO_ERROR == MMA_CheckUsimStatusForPlmnSel())
    {
        /* 构造LIST搜网回复事件 */
        pstPlmnListCnfPara->ulPlmnNum    = 0;
        pstPlmnListCnfPara->ucOpError    = VOS_FALSE;

        TAF_MMA_PlmnListReport(pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return;
    }

    pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
    pstPlmnListCnfPara->enPhoneError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;

    /* 上报 */
    TAF_MMA_PlmnListReport(pstPlmnListCnfPara);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    return;
}

/*****************************************************************************
 函 数 名  : Sta_PlmnListEventReport
 功能描述  : 列表搜结果上报
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月5日
    作    者   : c00173809
    修改内容   : AT融合项目，列表搜结果上报给A核
  2.日    期   : 2015年3月6日
    作    者   : b00269685
    修改内容   : 改为分段上报
*****************************************************************************/

VOS_VOID Sta_PlmnListEventReport(VOS_VOID)
{
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    VOS_UINT8                           ucSendNum;
    VOS_UINT8                           ucLeftNum;
    VOS_UINT8                           ucCurrIndex;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulIndex;
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU stAtOperName;

    PS_MEM_SET(&stAtOperName, 0, sizeof(stAtOperName));
    ucSendNum   = 0;
    ucLeftNum   = 0;
    ucCurrIndex = 0;
    ulIndex     = 0;
    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();


    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_REQ, &ucCtxIndex))
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"Sta_PlmnListEventReport:ERROR: GET CTX FAIL.");
        return;
    }

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    if (VOS_NULL_PTR == pstPlmnListCnfPara)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"Sta_PlmnListEventReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    pstPlmnListCnfPara->ucOpError    = VOS_FALSE;
    pstPlmnListCnfPara->ulCurrIndex  = pstPlmnListCtrl->usCurrIndex;
    pstPlmnListCnfPara->ulPlmnNum    = 0;

    ucSendNum = (VOS_UINT8)pstPlmnListCtrl->usReadNum;

    /* 如果要求读取的index大于等于PLmn list的总数目，认为是最后一次上报，上报一个空列表 */
    if (pstPlmnListCtrl->usCurrIndex >= (VOS_UINT16)g_StatusContext.PlmnList.ucPlmnNum)
    {
        ucSendNum = 0;
    }
    else
    {
        ucLeftNum = (g_StatusContext.PlmnList.ucPlmnNum - (VOS_UINT8)pstPlmnListCtrl->usCurrIndex);

        if (ucSendNum > ucLeftNum)
        {
            ucSendNum = ucLeftNum;
        }
    }

    for (ulIndex = 0; ulIndex < ucSendNum; ulIndex++)
    {
        if (ulIndex >= TAF_MMA_MAX_PLMN_NAME_LIST_NUM)
        {
            break;
        }

        ucCurrIndex = (VOS_UINT8)ulIndex + (VOS_UINT8)pstPlmnListCtrl->usCurrIndex;

        pstPlmnListCnfPara->astPlmnName[ulIndex].PlmnId.Mcc = g_StatusContext.PlmnList.Plmn[ucCurrIndex].Mcc;
        pstPlmnListCnfPara->astPlmnName[ulIndex].PlmnId.Mnc = g_StatusContext.PlmnList.Plmn[ucCurrIndex].Mnc;
        MMA_PlmnId2Bcd(&(pstPlmnListCnfPara->astPlmnName[ulIndex].PlmnId));
        pstPlmnListCnfPara->astPlmnInfo[ulIndex].PlmnStatus = g_StatusContext.PlmnList.PlmnInfo[ucCurrIndex].PlmnStatus;
        pstPlmnListCnfPara->astPlmnInfo[ulIndex].RaMode     = g_StatusContext.PlmnList.PlmnInfo[ucCurrIndex].RaMode;

        PS_MEM_SET(&stAtOperName,0,sizeof(stAtOperName));
        stAtOperName.OperName.PlmnId.Mcc  = pstPlmnListCnfPara->astPlmnName[ulIndex].PlmnId.Mcc;
        stAtOperName.OperName.PlmnId.Mnc  = pstPlmnListCnfPara->astPlmnName[ulIndex].PlmnId.Mnc;
        stAtOperName.ListOp               = TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME;

        /* 获取优先网络的长短名 */
        if (MMA_SUCCESS == Taf_PhoneGetNetworkNameForListPlmn(&stAtOperName))
        {
            PS_MEM_CPY(pstPlmnListCnfPara->astPlmnName[ulIndex].aucOperatorNameLong, stAtOperName.OperName.aucOperatorNameLong,TAF_PH_OPER_NAME_LONG);
            PS_MEM_CPY(pstPlmnListCnfPara->astPlmnName[ulIndex].aucOperatorNameShort, stAtOperName.OperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        }
        else
        {
            pstPlmnListCnfPara->astPlmnName[ulIndex].aucOperatorNameLong[0]  = '\0';
            pstPlmnListCnfPara->astPlmnName[ulIndex].aucOperatorNameShort[0] = '\0';
        }

        pstPlmnListCnfPara->ulPlmnNum++;
    }

    TAF_MMA_PlmnListReport(pstPlmnListCnfPara);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    return;
}

/*************************************************
  Function:
    Sta_PlmnListInd
  Description:
    处理MSCC_PLMN_LIST_IND消息
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    ST_MSCC_PLMN_LIST_IND    *pPlmnListInd; 输入参数结构指针
  Output:
    无
  Return:
    STA_SUCCESS         =0, 正常返回
    STA_ERROR           =1, 错误返回
  Others:

  1.日    期   : 2006年3月27日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D02372
  2.日    期   : 2009年01月05日
    作    者   : l00130025
    修改内容   : 根据问题单AT2D07968,双模列表搜网完毕,搜网状态判断和排序调整
  3.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  4.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  5.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*************************************************/
VOS_UINT32 Sta_PlmnListInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_PLMN_LIST_CNF_STRU         *pPlmnListInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           n;          /* 循环次数 */

    pPlmnListInd = (MSCC_MMA_PLMN_LIST_CNF_STRU*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    /* 系统状态 */
    switch ( g_StatusContext.ulFsmState )
    {
        case  STA_FSM_PLMN_LIST:
            /* 关闭状态定时器 */

            ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                     g_StatusContext.aFsmSub[0].TimerName,
                                     &g_StatusContext.ahStaTimer[0]);

            if ( VOS_OK != ulRet )
            {
                STA_TRACE (STA_WARNING_PRINT,
                    "Sta_PlmnListInd():WARNING:NAS_StopRelTimer failed");
            }
            g_StatusContext.ahStaTimer[0] = 0;

            /* 保存参数结果 */
            for ( n = 0; n < pPlmnListInd->ulCnt; n++ )
            {
                g_StatusContext.PlmnList.Plmn[n].Mcc
                    = pPlmnListInd->aPlmnList[n].ulMcc;
                g_StatusContext.PlmnList.Plmn[n].Mnc
                    = pPlmnListInd->aPlmnList[n].ulMnc;
                /*增加每个PLMN的状态和接入模式*/
                g_StatusContext.PlmnList.PlmnInfo[n].PlmnStatus
                    = pPlmnListInd->aucPlmnStatus[n];
                g_StatusContext.PlmnList.PlmnInfo[n].RaMode
                    = pPlmnListInd->aucRaMode[n];
            }
            g_StatusContext.PlmnList.ucPlmnNum = (VOS_UINT8)pPlmnListInd->ulCnt;

            /*对上报的PLMN列表进行调整 */
            Sta_ReOrderPlmnList(&g_StatusContext.PlmnList);
            /* 向APP上报事件*/
            g_StatusContext.ucOperateType = STA_OP_PLMNLIST;

            /* 列表搜回复结果通过专有的事件回复 */
            Sta_PlmnListEventReport();
            break;

        case  STA_FSM_PLMN_RESEL:

            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return VOS_TRUE;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
        case STA_FSM_ENABLE:
            /*直接上报列表*/
            for ( n = 0; n < pPlmnListInd->ulCnt; n++ )
            {
                g_StatusContext.PlmnList.Plmn[n].Mcc
                    = pPlmnListInd->aPlmnList[n].ulMcc;
                g_StatusContext.PlmnList.Plmn[n].Mnc
                    = pPlmnListInd->aPlmnList[n].ulMnc;
                /*增加每个PLMN的状态和接入模式*/
                g_StatusContext.PlmnList.PlmnInfo[n].PlmnStatus
                    = pPlmnListInd->aucPlmnStatus[n];
                g_StatusContext.PlmnList.PlmnInfo[n].RaMode
                    = pPlmnListInd->aucRaMode[n];
            }
            g_StatusContext.PlmnList.ucPlmnNum = (VOS_UINT8)pPlmnListInd->ulCnt;
            /*应该上报plmn列表*/
            g_StatusContext.ucOperateType = STA_OP_PLMNLIST
                                           |STA_OP_PLMNRESELMODE;
            Sta_EventReport (g_StatusContext.ulCurOpId,
                             TAF_PH_EVT_PLMN_LIST_IND);

            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return VOS_TRUE;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
        default :
            /* do nothing */
            STA_TRACE (STA_WARNING_PRINT,
                "Sta_PlmnListInd():WARNING:invalid state, do nothing");

            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return VOS_TRUE;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }

    /*清除子状态*/
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRet = Sta_UpdateFsmFlag(STA_FSMSUB_NULL, STA_FSM_ENABLE, STA_UPDATE_MONO_CLEAR);
    if (STA_ERROR == ulRet)
    {
        STA_TRACE(STA_WARNING_PRINT, "Sta_PlmnListInd():WARNING:Sta_UpdateFsmFlag failed\n");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcGULCoverageAreaInd
 功能描述  : 处理GUL模式下系统消息上报
 输入参数  : MSCC_MMA_3GPP_SYS_INFO_IND_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified:将MMA收到丢网消息的函数，拆成GUL和CL模式的两部分
*****************************************************************************/
VOS_VOID TAF_MMA_Proc3gppCoverageAreaIndInGulMode(
    MSCC_MMA_COVERAGE_AREA_IND_STRU    *pstCoverageAreaInd
)
{
    STA_PHONE_DATA_S                                        Update;         /* 需要更新的全局数据 */
    VOS_UINT32                                              ulRet;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */

    TAF_SDC_SYS_MODE_ENUM_UINT8                             ucSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          ucSysSubmode;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                    stSndMtcPlmnInfo;
#endif

    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return;
    }
#endif

    g_StatusContext.ulTimMaxFlg = pstCoverageAreaInd->ulTimMaxFlg;

    if (NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST == pstCoverageAreaInd->enCoverageChgMode)
    {
        /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, begin */
        TAF_SDC_SetCampOnFlag(VOS_FALSE);
        /* Added by y00245242 for VoLTE_PhaseII 项目, 2013-10-11, end */

        TAF_MMA_SndMtaAreaLostInd();

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        if (VOS_TRUE == TAF_SDC_GetUtranSkipWPlmnSearchFlag())
        {
            PS_MEM_SET(&stSndMtcPlmnInfo, 0, sizeof(stSndMtcPlmnInfo));
            stSndMtcPlmnInfo.enRatMode             = MTC_RATMODE_BUTT;
            stSndMtcPlmnInfo.ucIsForbiddenPlmnFlag = VOS_FALSE;
            stSndMtcPlmnInfo.ucPsAttachAllowFlag   = TAF_SDC_GetPsAttachAllowFlg();
            stSndMtcPlmnInfo.stPlmnId.ulMcc        = TAF_SDC_INVALID_MCC;
            stSndMtcPlmnInfo.stPlmnId.ulMnc        = TAF_SDC_INVALID_MCC;
            TAF_MMA_SndMtcCurrCampPlmnInfoInd(&stSndMtcPlmnInfo);
        }
#endif

        ucSysMode = TAF_SDC_GetSysMode();
        ucSysSubmode = TAF_SDC_GetSysSubMode();
        if ((TAF_SDC_SYS_MODE_BUTT    != ucSysMode)
         || (TAF_SDC_SYS_SUBMODE_NONE != ucSysSubmode)){
            Mma_ModeChgReport(TAF_SDC_SYS_MODE_BUTT, TAF_SYS_SUBMODE_NONE);
            TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_BUTT);
            TAF_SDC_SetSysSubMode(TAF_SYS_SUBMODE_NONE);
        }
    }

    switch ( g_StatusContext.ulFsmState )
    {
        case  STA_FSM_ENABLE :
            /*进出服务区时，MSCC均会向MMA发送service status ind，指示CS/PS服务状态
              以及PLMNID，因此删除下面代码*/
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

        case  STA_FSM_PLMN_RESEL: /* PLMN_RESEL状态 */
            /* 子状态为自动重选模式*/
            if ( STA_FSMSUB_PLMN_RESEL_AUTO
                == g_StatusContext.aFsmSub[0].ucFsmStateSub )
            {
                /* 参数为进入覆盖区*/
                if ( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_ENTER == pstCoverageAreaInd->enCoverageChgMode )
                { /* PLMN驻留区 */
                    /* do nothing */
                    STA_TRACE (STA_NORMAL_PRINT,
                                "Sta_CoverageAreaInd():NORMAL:resident PLMN indicator,\
                                do nothing");
                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                    return;
                    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
                }
                else /* 出覆盖区*/
                {
                    /* 关闭PLMN_RESEL状态定时器*/
                    if ( 0 != g_StatusContext.ahStaTimer[0] )
                    {
                        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                                 g_StatusContext.aFsmSub[0].TimerName,
                                                 &g_StatusContext.ahStaTimer[0]);


                        if ( VOS_OK != ulRet )
                        {
                            STA_TRACE (STA_WARNING_PRINT,
                                        "Sta_CoverageAreaInd():WARNING:\
                                        NAS_StopRelTimer failed");
                        }
                        g_StatusContext.ahStaTimer[0] = 0;
                    }

                    /* 保存参数结果 */
                    Update.ulCsServiceStatus = pstCoverageAreaInd->enCsSvcSta;
                    Update.ulPsServiceStatus = pstCoverageAreaInd->enPsSvcSta;

                    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
                    Update.ulCsCause         = NAS_MSCC_PIF_CAUSE_NULL;
                    Update.ulPsCause         = NAS_MSCC_PIF_CAUSE_NULL;
                    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

                    Update.ucFsmSubOperate   = STA_FSMSUB_FINISH;
                    Update.ulFsmState        = STA_FSM_ENABLE;
                    Update.ucFsmStateSub     = STA_FSMSUB_NULL;
                    Update.ucFsmUpdateFlag   = STA_UPDATE_MONO_CLEAR;
                    ulRet = Sta_UpdateData (&Update);
                    if ( STA_ERROR == ulRet )
                    {
                        STA_TRACE (STA_WARNING_PRINT,
                                    "Sta_CoverageAreaInd():WARNING:\
                                    Sta_UpdateData failed");
                    }

                    /* 向APP上报事件*/
                    g_StatusContext.ucOperateType = STA_OP_CSSERVICESTATUS
                        |STA_OP_PSSERVICESTATUS|STA_OP_PLMNRESELMODE;
                    TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_ERROR);
                }
                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                return;
                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
            }/* 结束 子状态为自动重选模式 */

            /* 子状态为手动重选模式 */
            if ( STA_FSMSUB_PLMN_RESEL_MANUAL
                == g_StatusContext.aFsmSub[0].ucFsmStateSub )
            {
                /* 参数为出覆盖区*/
                if ( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST == pstCoverageAreaInd->enCoverageChgMode )
                {
                    /* 关闭PLMN_RESEL状态定时器*/
                    if ( 0 != g_StatusContext.ahStaTimer[0] )
                    {
                        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                                 g_StatusContext.aFsmSub[0].TimerName,
                                                 &g_StatusContext.ahStaTimer[0]);


                        if ( VOS_OK != ulRet )
                        {
                            STA_TRACE (STA_WARNING_PRINT,
                                "Sta_CoverageAreaInd():WARNING:\
                                NAS_StopRelTimer failed  ");
                        }
                        g_StatusContext.ahStaTimer[0] = 0;
                    }

                    /* 保存参数结果 */
                    Update.ulCsServiceStatus = pstCoverageAreaInd->enCsSvcSta;
                    Update.ulPsServiceStatus = pstCoverageAreaInd->enPsSvcSta;

                    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
                    Update.ulCsCause         = NAS_MSCC_PIF_CAUSE_NULL;
                    Update.ulPsCause         = NAS_MSCC_PIF_CAUSE_NULL;
                    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

                    Update.ucFsmSubOperate   = STA_FSMSUB_FINISH;
                    Update.ulFsmState        = STA_FSM_ENABLE;
                    Update.ucFsmStateSub     = STA_FSMSUB_NULL;
                    Update.ucFsmUpdateFlag   = STA_UPDATE_MONO_CLEAR;
                    ulRet = Sta_UpdateData (&Update);
                    if ( STA_ERROR == ulRet )
                    {
                        STA_TRACE (STA_WARNING_PRINT,
                            "Sta_CoverageAreaInd():WARNING:Sta_UpdateData failed  ");
                    }

                    /* 向APP上报事件*/
                    TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_ERROR);
                }
                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
                return;
                /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
            }
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */
        case  STA_FSM_PLMN_SEL:  /* PLMN_SEL状态 */
            /* 参数为进入覆盖区*/
            /* 删除之前在这里的保护处理,目前用户指定搜网时,MSCC都会上报指定搜网结果
               无需此处进行保护 */
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

        default:
            STA_TRACE (STA_WARNING_PRINT,
                "Sta_CoverageAreaInd():WARNING:invalid state, do nothing  ");
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
            return;
            /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }
}
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcCLCoverageAreaInd
 功能描述  : 处理GUL模式下系统消息上报
 输入参数  : MSCC_MMA_3GPP_SYS_INFO_IND_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : w00242748
    修改内容   : CDMA Iteration 15 modified:将MMA收到丢网消息的函数，拆成GUL和CL模式的两部分
*****************************************************************************/
VOS_UINT32 TAF_MMA_Proc3gppCoverageAreaIndInClMode(
    MSCC_MMA_COVERAGE_AREA_IND_STRU    *pstCoverageAreaInd
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SYS_SUBMODE_ENUM_UINT8                              enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncUpdateSysModSrvRegSta;

    TAF_SDC_SRV_REG_INFO_STRU                               stSrvRegInfo;
    PS_MEM_SET(&stSrvRegInfo, 0x00, sizeof(stSrvRegInfo));

    /* 服务状态延时可维可测 */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    pFuncUpdateSysModSrvRegSta          = VOS_NULL_PTR;
    enSysMode                           = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                           = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return VOS_TRUE;
    }

    if (NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST == pstCoverageAreaInd->enCoverageChgMode)
    {
        TAF_SDC_SetCampOnFlag(VOS_FALSE);

        TAF_MMA_SndMtaAreaLostInd();

        /* todo conver to network existance */
        TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_NOT_EXIST,
                                                       &enSysMode,
                                                       &enSubMode,
                                                       &pFuncUpdateSysModSrvRegSta);

        /* 执行更新服务状态与注册状态函数 */
        if (VOS_NULL_PTR != pFuncUpdateSysModSrvRegSta)
        {
            pFuncUpdateSysModSrvRegSta(&stSrvRegInfo);

            /* 判断服务状态、注册状态是否变化，变化的话，就上报 */
            TAF_MMA_UpdateSrvRegSta_Main(&stSrvRegInfo, TAF_PH_ACCESS_TECH_E_UTRAN);
        }

    }

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}
#endif

/*************************************************
  Function:
    Sta_CoverageAreaInd
  Description:
    处理MSCC_COVERAGE_AREA_IND消息
  Calls:             被本函数调用的函数清单
  Called By:         调用本函数的函数清单
  Input:
    ST_MSCC_COVERAGE_AREA_IND *pCoverageAreaInd; 输入参数结构指针
  Output:
    无
  Return:
    STA_SUCCESS     =0, 正常返回
    STA_ERROR       =1, 错误返回
  Others:
    author:   l48197 2005-10-21
    modified:
        在attach,detach过程中收到service_status_ind，直接返回，
        enable状态下，将当前子状态清零

  2.日    期   : 2006年3月30日
    作    者   : liuyang id: 48197
    修改内容   : 问题单号：A32D02372
  3.日    期   : 2009年01月14日
    作    者   : l65478
    修改内容   : 问题单号：AT2D07971,在搜网状态下上报的接入技术错误
  4.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  5.日    期   : 2012年12月13日
    作    者   : w00176964
    修改内容   : DTS2012111204234:U下指定搜网过程中,用户指定搜网,MMA收到MSCC的
                 出服务区指示,提前返回搜网失败
  6.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  7.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  8.日    期   : 2013年11月22日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
  9.日    期   : 2014年05月31日
    作    者   : s00246516
    修改内容   : 路由区更新过程中出服务区，如果有缓存的Detach，没有回复
 10.日    期   : 2014年6月16日
    作    者   : w00167002
    修改内容   : 若有no rf标志，则直接不处理
*************************************************/
VOS_UINT32 Sta_CoverageAreaInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_COVERAGE_AREA_IND_STRU    *pstCoverageAreaInd = VOS_NULL_PTR;

    pstCoverageAreaInd = (MSCC_MMA_COVERAGE_AREA_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_MMA_Proc3gppCoverageAreaIndInClMode(pstCoverageAreaInd);
    }
    else
#endif
    {
        TAF_MMA_Proc3gppCoverageAreaIndInGulMode(pstCoverageAreaInd);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ReportSpecPlmnSrchResult
 功能描述  : 根据搜网的结果通知用户
 输入参数  : VOS_UINT32                  ulResult
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月7日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2011年11月15日
    作    者   : 傅映君/f62575
    修改内容   : E5宏开关打开后编译问题
  3.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_ReportSpecPlmnSrchResult(
    VOS_UINT32                  ulResult
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    if ( NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS == ulResult )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */
    {
        /* 上报当前指定搜网成功 */
        if(STA_FSM_PLMN_SEL == g_StatusContext.ulFsmState)
        {
            /* 设置上报事件类型，并上报APP搜网成功 */
            TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_NO_ERROR);
        }
        else
        {
        }
    }
    else
    {
        /* 上报当前指定搜网失败 */
        /* 上报APP当前状态事件 */
        if(STA_FSM_PLMN_SEL == g_StatusContext.ulFsmState)
        {
            /* 上报APP当前状态事件 */
            TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_NO_NETWORK_SERVICE);

            STA_TRACE(STA_NORMAL_PRINT, "TAF_MMA_ReportSpecPlmnSrchResult: TAF_PH_EVT_PLMN_SEL_CNF reported to AT!");
        }
        else
        {
        }
    }
}
/*****************************************************************************
 函 数 名  : TAF_MMA_ReportAutoPlmnSrchResult
 功能描述  : 根据搜网的结果通知用户
 输入参数  : VOS_UINT32                  ulResult
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月7日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2011年11月15日
    作    者   : 傅映君/f62575
    修改内容   : E5宏开关打开后编译问题
  3.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_ReportAutoPlmnSrchResult(
    VOS_UINT32                  ulResult
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    if ( NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS == ulResult )
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */
    {
        /* 上报当前auto搜网成功 */
        if (STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
        {
            /* 上报APP当前状态事件 */
            TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_ERROR);
            STA_TRACE(STA_NORMAL_PRINT, "TAF_MMA_ReportAutoPlmnSrchResult: TAF_PH_EVT_PLMN_RESEL_CNF reported to AT!");
        }
        else
        {
        }
    }
    else
    {
        /* 上报当前auto搜网失败 */
        MMA_NORMAILLOG("TAF_MMA_ReportAutoPlmnSrchResult():NORMAIL:SPECIALIZE THE PLMN FAILURE!");
        /* 上报APP当前状态事件 */
        if (STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
        {
            /* 上报APP当前状态事件 */
            TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_NETWORK_SERVICE);
            STA_TRACE(STA_NORMAL_PRINT, "TAF_MMA_ReportAutoPlmnSrchResult: TAF_PH_EVT_PLMN_RESEL_CNF reported to AT!");
        }
        else
        {
        }
    }
}

/*************************************************
  Function:
    Sta_PlmnListRej
  Description:
    处理MSCC_PLMN_LIST_REJ消息
  Calls:             被本函数调用的函数清单
  Called By:         调用本函数的函数清单
  Input:
    ST_MSCC_PLMN_LIST_REJ *pPlmnListRej; 输入参数结构指针
  Output:
    无
  Return:
    STA_SUCCESS     =0, 正常返回
    STA_ERROR       =1, 错误返回
  Others:
  1.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位
  2.日    期   : 2012年8月10日
    作    者   : y00213812
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  4.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  5.日    期   : 2015年3月13日
    作    者   : b00269685
    修改内容   : 列表搜上报接口调整
*************************************************/
VOS_UINT32 Sta_PlmnListRej(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32          ulRet;

    /* 不是PLMN_LIST状态 */
    if ( VOS_FALSE == (g_StatusContext.ulFsmState & STA_FSM_PLMN_LIST) )
    {
        g_StatusContext.PhoneError = TAF_ERR_PHONE_MSG_UNMATCH;

        /* 输出跟踪调试信息 */
        STA_TRACE (STA_WARNING_PRINT,
            "Sta_PlmnListInd():WARNING:unmatched system FSM state\n" );

        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
        return VOS_TRUE;
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }

    /* 关闭状态定时器*/

    ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                             g_StatusContext.aFsmSub[0].TimerName,
                             &g_StatusContext.ahStaTimer[0]);


    if ( VOS_OK != ulRet )
    {
        STA_TRACE (STA_WARNING_PRINT,
            "Sta_PlmnListRej():WARNING:NAS_StopRelTimer failed  ");
    }
    g_StatusContext.ahStaTimer[0]    = 0;
    /* 空闲标志 */
    g_StatusContext.aucFsmSubFlag[0] = STA_FSMSUB_NULL;

    /*清除子状态*/
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    ulRet = Sta_UpdateFsmFlag(STA_FSMSUB_NULL, STA_FSM_ENABLE, STA_UPDATE_MONO_CLEAR);
    if (STA_ERROR == ulRet)
    {
        STA_TRACE(STA_WARNING_PRINT, "Sta_PlmnListRej():WARNING:Sta_UpdateFsmFlag failed\n");
    }
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    /* 协议栈拒绝PLMN搜索*/
    /* 向APP上报事件*/
    TAF_MMA_PlmnListErrorReport(TAF_ERR_CMD_TYPE_ERROR);

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}
/*****************************************************************************
 函 数 名  : Sta_PlmnListAortCnf
 功能描述  : MMA收到MSCC_PLMN_LIST_ABORT_CNF的处理
 输入参数  : ST_MSCC_PLMN_LIST_ABORT_CNF* pPlmnListAbortCnf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年09月14日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年11月08日
    作    者   : c00173809
    修改内容   : AT Project
  3.日    期   : 2012年5月28日
    作    者   : z00161729
    修改内容   : GUL BG搜网修改
  4.日    期   : 2012年9月22日
    作    者   : s00217060
    修改内容   : for V7R1C50_At_Abort
  5.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID Sta_PlmnListAortCnf (MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU *pPlmnListAbortCnf)
{

    VOS_UINT32                          ulIndex;

    VOS_UINT32                          ulRet;

    /* stop cnf和search cnf对冲时有可能带上来的列表不为空，需要上报*/
    if (pPlmnListAbortCnf->ulCnt > 0)
    {
        for ( ulIndex = 0; ulIndex < pPlmnListAbortCnf->ulCnt; ulIndex++ )
        {
            g_StatusContext.PlmnList.Plmn[ulIndex].Mcc
                = pPlmnListAbortCnf->aPlmnList[ulIndex].ulMcc;
            g_StatusContext.PlmnList.Plmn[ulIndex].Mnc
                = pPlmnListAbortCnf->aPlmnList[ulIndex].ulMnc;

            /*增加每个PLMN的状态和接入模式*/
            g_StatusContext.PlmnList.PlmnInfo[ulIndex].PlmnStatus
                = pPlmnListAbortCnf->aucPlmnStatus[ulIndex];
            g_StatusContext.PlmnList.PlmnInfo[ulIndex].RaMode
                = pPlmnListAbortCnf->aucRaMode[ulIndex];

        }
        g_StatusContext.PlmnList.ucPlmnNum = (VOS_UINT8)pPlmnListAbortCnf->ulCnt;

        /*对上报的PLMN列表进行调整 */
        Sta_ReOrderPlmnList(&g_StatusContext.PlmnList);

        /* 向APP上报事件*/
        g_StatusContext.ucOperateType = STA_OP_PLMNLIST;

        /* 列表搜回复结果通过专有的事件回复 */
        Sta_PlmnListEventReport();
    }
    else
    {
        /* 向AT回复列表搜超时结果 */

        TAF_MMA_PlmnListErrorReport(TAF_ERR_TIME_OUT);

    }


    /* 更新状态标志 */
    ulRet = Sta_UpdateFsmFlag (STA_FSMSUB_NULL, STA_FSM_ENABLE, STA_UPDATE_MONO_CLEAR);

    if (STA_ERROR == ulRet)
    {
        STA_TRACE(STA_WARNING_PRINT, "Sta_PlmnListAortCnf():WARNING:Sta_UpdateFsmFlag failed\n");
    }

    /* 设置当前没有处理用户列表搜打断过程 */
    g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnListAbortCnfUserAbort
 功能描述  : MMA收到MSCC_PLMN_LIST_ABORT_CNF的处理,Abort原因值为用户打断
 输入参数  : ST_MMC_PLMN_LIST_ABORT_CNF* pPlmnListAbortCnf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_PlmnListAbortCnfUserAbort (MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU *pPlmnListAbortCnf)
{
    /* 向AT回复列表搜打断 */
    TAF_MMA_ProcPlmnListAbortCnf(TAF_ERR_NO_ERROR);
    /* 更新状态标志 */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* 设置当前没有处理用户列表搜打断过程 */
    g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPlmnListAbortCnf
 功能描述  : MMA收到MSCC_PLMN_LIST_ABORT_CNF的处理
 输入参数  : ST_MSCC_PLMN_LIST_ABORT_CNF* pPlmnListAbortCnf
 输出参数  : 无
 返 回 值  : STA_SUCCESS: 函数处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnListAbortCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU   *pPlmnListAbortCnf;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF);

    pPlmnListAbortCnf = (MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */

    /* 当前不是PLMN LIST状态，直接返回 */
    if (STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState)
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvPlmnListAbortCnf():WARNING:Sta_UpdateFsmFlag failed\n");
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
        return VOS_TRUE;
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }

    /* 异常保护：当前没有正在处理用户列表搜打断，直接返回 */
    if (TAF_MMA_PLMN_LIST_ABORT_BUTT == g_StatusContext.ucPlmnListAbortProc)
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvPlmnListAbortCnf():WARNING:Sta_UpdateFsmFlag failed\n");
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
        return VOS_TRUE;
        /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
    }


    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    /* 定时器超时导致的PLMN LIST ABORT的处理 */
    if ( TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == g_StatusContext.ucPlmnListAbortProc)
    {
        Sta_PlmnListAortCnf(pPlmnListAbortCnf);
    }
    else
    {
        TAF_MMA_PlmnListAbortCnfUserAbort(pPlmnListAbortCnf);
    }

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
函 数 名  : TAF_MMA_RcvSpecPlmnSearchAbortCnf
功能描述  : MMA收到TAFMSCC_SPEC_PLMN_SEARCH_ABORT_CNF的处理
输入参数  : pSpecPlmnSearchAbortCnf - AFMSCC_SPEC_PLMN_SEARCH_ABORT_CNF消息内容
输出参数  : 无
返 回 值  : STA_SUCCESS: 函数处理消息成功
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2011年11月28日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2013年4月2日
  作    者   : z00161729
  修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
3.日    期   : 2012年07月15日
  作    者   : w00176964
  修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSpecPlmnSearchAbortCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF);
    /* 上报APP当前状态事件 */
    TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_TIME_OUT);

    /* 迁移状态到ENABLE状态 */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, begin */
/* 函数Sta_MsgInd删除 */
/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-10, end */

/* Added by l00208543 for V9R1 STK升级, 2013-08-01, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertTafSrvStaToStkType
 功能描述  : 转换service status的类型，deep sleep为no service, regional limited service 转换为limited service
 输入参数  : enTafSrvType
 输出参数  : 无
 返 回 值  : 转换后的service type
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_MMA_ConvertTafSrvStaToStkType(
                                    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8  enTafSrvType
                                    )
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enRtType;

    enRtType = enTafSrvType;

    if(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE == enTafSrvType)
    {
        enRtType = TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE;
    }

    if(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP == enTafSrvType)
    {
        enRtType = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    }

    return enRtType;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertSrvTypeForStk
 功能描述  : 转换service status的类型，deep sleep为no service, regional limited service 转换为limited service
 输入参数  : enTafSrvType
 输出参数  : 无
 返 回 值  : 转换后的service type
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_MMA_ConvertSrvTypeForStk(
                                    TAF_SDC_SERVICE_STATUS_ENUM_UINT8  enTafSrvType
                                    )
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enRtType;

    enRtType = enTafSrvType;

    if (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == enTafSrvType)
    {
        enRtType = TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE;
    }

    if (TAF_SDC_SERVICE_STATUS_DEEP_SLEEP == enTafSrvType)
    {
        enRtType = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    }

    return enRtType;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_GetSrvTypeForStk
 功能描述  : 按照CS PS的服务状态，判断总的服务状态(按照新的规则，以满足给STK上报LOCI事件的需求)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 转换后的service type
 调用函数  :
 被调函数  :
  获取enTafSrvType
 1.    CS PS 转成NORMAL NO SERVICE LIMIT
 2.    CS            PS
     NORMAL          NORMAL          NORMAL
     NORMAL          LIMIT           NORMAL
     NORMAL          NO SERVICE      NORMAL
     LIMIT           NORMAL          NORMAL
     LIMIT           LIMIT           LIMIT
     LIMIT           NO SERVICE      NO SERVICE(cs+ps or ps only)   MN_MMA_GetLastSyscfgSetAddr()->ucSrvDomain
     LIMIT           NO SERVICE      LIMIT(cs only)
     NO SERVICE      NORMAL          NORMAL
     NO SERVICE      LIMIT           NO SERVICE
     NO SERVICE      NO SERVICE      NO SERVICE

 修改历史      :
  1.日    期   : 2013年8月7日
    作    者   : l00208543
    修改内容   : 新生成函数
  2.日    期   : 2015年4月9日
    作    者   : h00313353
    修改内容   : SysCfg SrvDomain宏定义转枚举类型
*****************************************************************************/

TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_MMA_GetSrvTypeForStk(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enRtType;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstSysCfg;

    pstSysCfg         = TAF_MMA_GetLastSyscfgSetAddr();

    enCsServiceStatus = TAF_MMA_ConvertSrvTypeForStk(TAF_SDC_GetCsServiceStatus());
    enPsServiceStatus = TAF_MMA_ConvertSrvTypeForStk(TAF_SDC_GetPsServiceStatus());

    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus))
    {
        enRtType = TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE;
    }
    else if ((TAF_SDC_SERVICE_STATUS_NO_SERVICE == enCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_NO_SERVICE == enPsServiceStatus))
    {
        if ((TAF_MMA_SERVICE_DOMAIN_CS == pstSysCfg->enSrvDomain)
         && (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus))
        {
            enRtType = TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE;
        }
        else
        {
            enRtType = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
        }
    }
    else
    {
        enRtType = TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE;
    }

    return enRtType;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcServiceStaReportForStk
 功能描述  : 转换service status的类型，deep sleep为no service, regional limited service 转换为limited service
 输入参数  : enTafSrvType
 输出参数  : 无
 返 回 值  : 转换后的service type
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月1日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID TAF_MMA_ProcLociStatusEvent(VOS_VOID)
{
   TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enStkServiceType;

   enStkServiceType = TAF_MMA_GetSrvTypeForStk();

   if (enStkServiceType != g_stMmsStkLocStaSysInfo.enServiceStatus)
   {
       if (VOS_FALSE == MN_MMA_GetRoamingBrokerFlg())
       {
          NAS_MMA_ReportLociStatus();
       }
       else
       {
           if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == enStkServiceType)
           {
               NAS_MMA_ReportLociStatus();
           }
       }
   }
}
/* Added by l00208543 for V9R1 STK升级, 2013-08-01, end */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*--------------- STATUS内部数据处理函数  ---------------*/
/*=======================================================*/

/*************************************************
  Function:
    Sta_EventReport
  Description:
    向TAFM发送事件状态报告
  Calls:                     被本函数调用的函数清单
  Called By:                 调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;         命令操作标识
    VOS_UINT32  ulEventType;    事件类型
  Output:
    无
  Return:
    无
  Others:
  History:
  1. s46746  2006-09-04 根据问题单A32D05624修改
  2.日    期   : 2011年7月11日
    作    者   : sunxibo 46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
  3.日    期   : 2012年04月10日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012041003283, USMI热插拔特性
  4.日    期   : 2012年6月15日
    作    者   : w00176964
    修改内容   : DTS2012061408865:LIST搜网过程中拔卡上报32个空网络
  5.日    期   : 2013年4月3日
   作    者   : z00161729
   修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2013年8月1日
   作    者   : l00208543
   修改内容   : STK升级
  7.日    期   : 2013年8月1日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目:开关机期间的simst的上报目前都由卡状态指示触发
  8.日    期   : 2015年3月4日
   作    者   : b00269685
   修改内容   : 列表搜改为分段上报
*************************************************/
VOS_VOID Sta_EventReport ( VOS_UINT32 ulOpID, VOS_UINT32 ulEventType )
{
    TAF_PHONE_EVENT_INFO_STRU      *pstPhoneEvent;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */


    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"Sta_EventReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /* 清除结构变量标志 */
    pstPhoneEvent->OP_CsServiceStatus    = 0;
    pstPhoneEvent->OP_PhoneError         = 0;
    pstPhoneEvent->OP_PlmnReselMode      = 0;
    pstPhoneEvent->OP_PsServiceStatus    = 0;
    pstPhoneEvent->OP_RegPlmn            = 0;
    pstPhoneEvent->OP_Spare              = 0;
    /*增加上报事件选项初始化*/
    pstPhoneEvent->OP_CurRegSta          = 0;
    pstPhoneEvent->OP_Rssi               = 0;
    pstPhoneEvent->OP_BatteryPower       = 0;
    pstPhoneEvent->OP_Pin                = 0;
    pstPhoneEvent->OP_Srvst              = 0;

    /* 填写上报事件参数 */
    /* 必填参数 */
    pstPhoneEvent->OpId = (VOS_UINT8)ulOpID;         /*写入ulOpId*/
    pstPhoneEvent->PhoneEvent = (TAF_PHONE_EVENT)ulEventType;
    pstPhoneEvent->PhoneError = TAF_ERR_NO_ERROR;
    /* 可选参数设置 */
    if ( STA_OP_REGPLMN & g_StatusContext.ucOperateType )
    {
        pstPhoneEvent->OP_RegPlmn = 1;
        pstPhoneEvent->RegPlmn.Mcc= g_StatusContext.StaPlmnId.Mcc;
        pstPhoneEvent->RegPlmn.Mnc= g_StatusContext.StaPlmnId.Mnc;
        MMA_PlmnId2Bcd(&(pstPhoneEvent->RegPlmn));
    }

    if ( STA_OP_PLMNLIST & g_StatusContext.ucOperateType )
    {
        /* 此处不需要填参数 */
    }

    if ( STA_OP_PLMNRESELMODE & g_StatusContext.ucOperateType )
    {
        pstPhoneEvent->OP_PlmnReselMode = 1;
        pstPhoneEvent->PlmnReselMode
            = (TAF_PLMN_RESEL_MODE_TYPE)g_StatusContext.ucReselMode;
    }

    if ( STA_OP_CSSERVICESTATUS & g_StatusContext.ucOperateType )
    {
        pstPhoneEvent->OP_CsServiceStatus = 1;

        /* CS域服务状态值 */
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
        pstPhoneEvent->CsServiceStatus
            = (TAF_PHONE_SERVICE_STATUS)enCsServiceStatus;
        /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    }

    if ( STA_OP_PSSERVICESTATUS & g_StatusContext.ucOperateType )
    {
        pstPhoneEvent->OP_PsServiceStatus = 1;

        /* PS域服务状态值 */
        pstPhoneEvent->PsServiceStatus
            = (TAF_PHONE_SERVICE_STATUS)enPsServiceStatus;
    }

    if ( STA_OP_PHONEERROR & g_StatusContext.ucOperateType )
    {
        pstPhoneEvent->OP_PhoneError = 1;
        pstPhoneEvent->PhoneError    = g_StatusContext.PhoneError;
    }




    /* 调用电话管理事件上报函数 向APP发送应答事件*/
    Taf_PhoneEvent (pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, begin */

    /* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-8-1, end */

    return ;    /* 正常返回 */
}

/*************************************************
  Function:
    Sta_IsFsmSubValid
  Description:
     判断子状态是否匹配FSM主状态
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    VOS_UINT8   ucFsmSub;   子状态值
    VOS_UINT32  ulFsm;      FSM状态值
  Output:
    无
  Return:
    STA_TRUE,  有效的子状态值，匹配；
    STA_FALSE, 无效的子状态值，不匹配；
  Others:
  1.日    期   : 2007年07月24日
    作    者   : l60022475
    修改内容   : A32D12535
*************************************************/
VOS_BOOL Sta_IsFsmSubValid ( VOS_UINT8 ucFsmSub, VOS_UINT32 ulFsm )
{
    switch ( ulFsm )
    {
        case STA_FSM_RESTART:
        case STA_FSM_STOP:
        case STA_FSM_PLMN_LIST:
        case STA_FSM_PLMN_SEL:
            /* ==>A32D12535 */
            if ( (STA_FSMSUB_MONO == ucFsmSub)
               ||(STA_FSM_RESTART == ucFsmSub)
                )
            /* <==A32D12535 */
            {
                return STA_TRUE;
            }
            return STA_FALSE;

        /*
          增加CS&PS同时DETACH或ATTACH状态的合法性；
          modified by roger in 2005-07-11
        */

        case STA_FSM_PLMN_RESEL:
            if ( (STA_FSMSUB_PLMN_RESEL_AUTO == ucFsmSub)
              || (STA_FSMSUB_PLMN_RESEL_MANUAL == ucFsmSub) )
            {
                return STA_TRUE;
            }
            return STA_FALSE;

        /* 内部函数调用时使用的中间状态，允许为有效状态 */
        case STA_FSM_NO_UPDATE:
        /* FSM的稳态，对子状态值没有匹配要求 */
        case STA_FSM_ENABLE:
        case STA_FSM_NULL:
            return STA_TRUE;

        default :
            return STA_FALSE;
    }
}

/*************************************************
  Function:
    Sta_IsInvalidOpId
  Description:
    是否是无效的OPID
  Calls:                  被本函数调用的函数清单
  Called By:              调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;      命令标识
  Output:
    无
  Return:
    STA_TRUE,   指定的ulOpId无效；
    STA_FALSE,  指定的ulOpId有效；
  Others:
*************************************************/
VOS_BOOL Sta_IsInvalidOpId ( VOS_UINT32 ulOpId )
{
    if ( STA_OPID_INSIDE == ulOpId )
    {
        return STA_FALSE;
    }

    if ( ulOpId <= STA_OPID_MAX )
    {
        return STA_FALSE;
    }

    return STA_TRUE;
}


/*此函数已经作废*/
/*************************************************
  Function:
    Sta_IsDualFsmSub
  Description:
    是否存在两个子状态同时有效，针对同一个OPID
  Calls:                  被本函数调用的函数清单
  Called By:              调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;      命令标识
  Output:
    无
  Return:
    STA_TRUE,   存在双重有效子状态；
    STA_FALSE,  不存在双重有效子状态；
  Others:
*************************************************/
VOS_UINT32 Sta_IsDualFsmSub ( VOS_VOID )
{
    /*当前所有的双重子状态的OpId都是一样的，
    因此判断当子状态标志位都为相同时,此状态为双重子状态*/
    if  ( g_StatusContext.aucFsmSubFlag[0]
          != g_StatusContext.aucFsmSubFlag[1])
    {
        return STA_FALSE;
    }
    /* 子状态OPID不相同，不是双重子状态 */
    /*if ( g_StatusContext.aFsmSub[0].ulOpId
        != g_StatusContext.aFsmSub[1].ulOpId )
    {
        return STA_FALSE;
    }
    */
    return STA_TRUE;
}

/*************************************************
  Function:
    Sta_FindFsmSubBySubSta
  Description:
     查找指定命令操作标识的对应子状态索引号
  Calls:                  被本函数调用的函数清单
  Called By:              调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;       命令标识
  Output:
    无
  Return:
    STA_FSMSUB_INDEX_NULL, 无效的子状态索引值；
    0< ret <STA_TIMER_MAX, 允许的索引值ret；
  Others:
*************************************************/
/*
VOS_UINT32 Sta_FindFsmSubBySubSta ( VOS_UINT32 ulOpId )
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       n;

    ucIndex = STA_FSMSUB_INDEX_NULL;
    for ( n = 0; n < STA_TIMER_MAX; n++ )
    {
        if ( ulOpId == g_StatusContext.aFsmSub[n].ulOpId )
        {
            ucIndex = n;
            break;
        }
    }

    return ucIndex;
}
*/
/*************************************************
  Function:
    Sta_FindFsmSubBySubSta
  Description:
     查找指定指定子状态的对应子状态索引号
  Calls:                  被本函数调用的函数清单
  Called By:              调用本函数的函数清单
  Input:
    VOS_UINT8  ucFsmSubSta;       命令标识
  Output:
    无
  Return:
    STA_FSMSUB_INDEX_NULL, 无效的子状态索引值；
    0< ret <STA_TIMER_MAX, 允许的索引值ret；
  Others:
*************************************************/
VOS_UINT8 Sta_FindFsmSubBySubSta ( VOS_UINT8 ucFsmSubSta )
{
    VOS_UINT8       ucIndex;
    VOS_UINT8       n;

    ucIndex = STA_FSMSUB_INDEX_NULL;

    for ( n = 0; n < STA_TIMER_MAX; n++ )
    {
        if (ucFsmSubSta == g_StatusContext.aFsmSub[n].ucFsmStateSub)
        {
            ucIndex = n;
            break;
        }
    }

    return ucIndex;
}

/*************************************************
  Function:
    Sta_FindIdleFsmSub
  Description:
     查找指定子状态值的对应的空闲资源索引号
  Calls:                  被本函数调用的函数清单
  Called By:              调用本函数的函数清单
  Input:
    VOS_UINT32  ulOpId;      命令标识
  Output:
    无
  Return:
    STA_FSMSUB_INDEX_NULL, 无效的子状态索引值；
    0< ret <STA_TIMER_MAX, 允许的索引值ret；
  Others:
*************************************************/
VOS_UINT32 Sta_FindIdelFsmSub ( VOS_UINT8 ucSubState )
{
    VOS_UINT8       ucRetIndex;
    VOS_UINT8       n;                  /* 循环次数 */

    ucRetIndex = STA_FSMSUB_INDEX_NULL;

    /* 查找空闲子状态 */
    for ( n = 0; n < STA_TIMER_MAX; n++ )
    {
        if ( STA_FSMSUB_NULL == g_StatusContext.aucFsmSubFlag[n] )
        {
            ucRetIndex = n;
            break;
        }
    }

    /* 无可用的子状态资源，直接返回无效索引值 */
    if ( STA_FSMSUB_INDEX_NULL == ucRetIndex )
    {
        return STA_FSMSUB_INDEX_NULL;      /* 返回无效值 */
    }


    /* 特殊状态直接返回空闲子状态索引 */
    if ( (STA_FSMSUB_NULL == ucSubState)
        || (STA_FSMSUB_OK == ucSubState)
        || (STA_FSMSUB_MONO == ucSubState) )
    {
        return ucRetIndex;
    }

    /* 非空闲的子状态只允许存在一个 */
    for ( n = 0; n < STA_TIMER_MAX; n++ )
    {
        if ( ucSubState == g_StatusContext.aucFsmSubFlag[n] )
        {
            return STA_FSMSUB_INDEX_NULL;   /* 返回无效值 */
        }
    }

    return ucRetIndex;
}

/*************************************************
  Function:
    Sta_UpdateFsmFlag
  Description:
     更新状态机的状态描述标志
  Calls:                 被本函数调用的函数清单
  Called By:             调用本函数的函数清单
  Input:
    VOS_UINT8   ucFsmSub;   子状态值
    VOS_UINT32  ulFsm;      FSM状态值
    VOS_UINT32  ulType;     更新类型
  Output:
    无
  Return:
    STA_SUCCESS,        =0, 正常返回
    STA_ERROR,          =1, 错误返回
  Others:
  1.日    期   : 2012年4月11日
    作    者   : l00130025
    修改内容   : DTS2012032600471,定时器停止动作没有钩包，不利于问题定位

  2.日    期   : 2012年5月31日
    作    者   : z40661
    修改内容   : DTS2012052902643:使用AT^CGCATT=1,3，再次去激活MMA直接返回失败

*************************************************/
VOS_UINT32 Sta_UpdateFsmFlag ( VOS_UINT8 ucFsmSub,
                           VOS_UINT32 ulFsm,
                           VOS_UINT32 ulType )
{
    VOS_UINT8                           n;                  /* 循环次数*/

    /* 按照更新类型进行操作 */
    switch ( ulType )
    {
        case STA_UPDATE_SETNEW:
            if (  STA_FSM_NO_UPDATE == ulFsm )
            {
               return STA_SUCCESS;
            }

            /* 双重子状态的单一更新 */

            /* 单重子状态的更新 */
            g_StatusContext.aFsmSub[0].ucFsmStateSub  = ucFsmSub;
            g_StatusContext.aucFsmSubFlag[0]          = ucFsmSub;
            break;

        /* 单重子状态的更新,并清除定时器等资源 */
        case STA_UPDATE_MONO_CLEAR:

            if (VOS_NULL_PTR != g_StatusContext.ahStaTimer[0])
            {
                if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA,
                                 g_StatusContext.aFsmSub[0].TimerName,
                                &g_StatusContext.ahStaTimer[0]))
                {
                    STA_TRACE(STA_WARNING_PRINT, "Sta_UpdateFsmFlag():WARNING:NAS_StopRelTimer failed!");
                }
            }
            g_StatusContext.aFsmSub[0].ucFsmStateSub  = ucFsmSub;
            g_StatusContext.aucFsmSubFlag[0]          = ucFsmSub;
            g_StatusContext.aFsmSub[0].TimerName      = STA_TIMER_NULL;
            g_StatusContext.ahStaTimer[0]             = VOS_NULL_PTR;



            if ( STA_FSM_INVALID != ulFsm )
            {
                g_StatusContext.ulFsmState = ulFsm;
            }

            /*设置OpID无效值*/
            g_StatusContext.aFsmSub[0].ulOpId        = STA_OPID_INVALID;
            /*清除当前操作标志*/
            g_StatusContext.aucStaPhoneOperator[0]   = STA_FSMSUB_NULL;
            break;

        /* 双重子状态同时更新, 并清除相关资源，如定时器 */
        case STA_UPDATE_DUAL_CLEAR:

            for ( n = 0; n < STA_TIMER_MAX; n++ )
            {
                if (VOS_NULL_PTR != g_StatusContext.ahStaTimer[n])
                {
                    if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA,
                                     g_StatusContext.aFsmSub[n].TimerName,
                                    &g_StatusContext.ahStaTimer[n]))
                    {
                        STA_TRACE(STA_WARNING_PRINT, "Sta_UpdateFsmFlag():WARNING:NAS_StopRelTimer failed!");
                    }
                }
                g_StatusContext.aFsmSub[n].ucFsmStateSub  = ucFsmSub;
                g_StatusContext.aucFsmSubFlag[n]          = ucFsmSub;
                g_StatusContext.aFsmSub[n].TimerName      = STA_TIMER_NULL;
                g_StatusContext.ahStaTimer[n]             = VOS_NULL_PTR;


                /*设置OpID无效值*/
                g_StatusContext.aFsmSub[n].ulOpId        = STA_OPID_INVALID;

                /*清除当前操作标志*/
                g_StatusContext.aucStaPhoneOperator[n]   = STA_FSMSUB_NULL;
            }
            if ( (STA_FSM_INVALID != ulFsm)
                && (STA_FSM_NO_UPDATE != ulFsm) )
            {
                g_StatusContext.ulFsmState = ulFsm;
            }
            break;

       /* 双重子状态的单一更新，并清除定时器等资源 */
        case STA_UPDATE_SINGL_CLEAR:

            break;

        /* 未使用的状态，返回错误 */
        default:
            STA_TRACE (STA_WARNING_PRINT,
                "Sta_UpdateFsmFlag():WARNING:unused state, do nothing  ");
            return STA_ERROR;
    }

    return STA_SUCCESS;
}

/*************************************************
  Function:
    Sta_UpdateData
  Description:
    更新共享全局变量的内容。
  Calls:             被本函数调用的函数清单
  Called By:         调用本函数的函数清单
  Input:
    STA_PHONE_DATA_S   *pData;更新数据内容的结构指针
  Output:
    无
  Return:
    STA_SUCCESS     =0,返回成功
    STA_ERROR       =1,返回失败
  Others:
  2.日    期   : 2009年01月14日
    作    者   : l65478
    修改内容   : 问题单号：AT2D07971,在搜网状态下上报的接入技术错误
  3.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*************************************************/
VOS_UINT32 Sta_UpdateData ( STA_PHONE_DATA_S *pData )
{
    VOS_UINT32  ulRet;
    VOS_UINT8   ucFsmSub;
    VOS_UINT32  ulFsm;
    VOS_UINT8   ucFsmFlag;

    /* 参数指针有效性由调用者保证，默认有效 */
    ucFsmSub  = pData->ucFsmStateSub;
    ulFsm     = pData->ulFsmState;
    ucFsmFlag = pData->ucFsmUpdateFlag;

    /* 判断子状态值是否有效 */
    if ( VOS_FALSE == Sta_IsFsmSubValid (ucFsmSub,ulFsm) )
    {
        STA_TRACE (STA_WARNING_PRINT,
            "Sta_UpdateData():WARNING:unmatched FSM state  ");

        return STA_ERROR;     /* 错误返回 */
    }

    /* 按照子状态的更新模式来处理 */
    switch ( pData->ucFsmSubOperate )
    {
        /* 设置FSM状态标志量，开始新的子状态 */
        case STA_FSMSUB_NEW:
            g_StatusContext.ulCurOpId = pData->ulOpId;  /*记录命令标识号*/
            ulRet = Sta_UpdateFsmFlag (ucFsmSub, ulFsm, STA_UPDATE_SETNEW);
            if ( STA_ERROR == ulRet )
            {
                STA_TRACE (STA_WARNING_PRINT,
                    "Sta_UpdateData():WARNING:Sta_UpdateFsmFlag failed  ");
            }
            break;

        /* 刷新子状态描述信息 */
        case STA_FSMSUB_UPDATE:
            g_StatusContext.ulNewOpId = pData->ulOpId;  /* 本次更新的标识号*/
            break;

        /* 子状态操作完成，清除子状态标志 */
        case STA_FSMSUB_FINISH:
            ulRet = Sta_UpdateFsmFlag (ucFsmSub, ulFsm, ucFsmFlag);
            if ( STA_ERROR == ulRet )
            {
                STA_TRACE (STA_WARNING_PRINT,
                    "Sta_UpdateData():WARNING:Sta_UpdateFsmFlag failed  ");
            }
            break;

        /* 其他模式不支持，直接返回 */
        default:
            STA_TRACE (STA_WARNING_PRINT,
                "Sta_UpdateData():WARNING:invalid operate ");
            return STA_ERROR;
    }

    /* 更新STATUS业务信息记录 */
    g_StatusContext.StaPlmnId.Mcc       = pData->PlmnId.Mcc;
    g_StatusContext.StaPlmnId.Mnc       = pData->PlmnId.Mnc;

    g_StatusContext.ulMmProc            = pData->ulMmProc ;
    g_StatusContext.ucDomainFlag        = pData->ucDomainFlag;
    /*保证每次只对有效的域返回的服务状态更新全局变量*/
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    switch ( pData->ucDomainFlag )
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS :
            TAF_SDC_SetCsServiceStatus((VOS_UINT8)pData->ulCsServiceStatus);
            g_StatusContext.ulCsCause = pData->ulCsCause;
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            TAF_SDC_SetPsServiceStatus((VOS_UINT8)pData->ulPsServiceStatus);
            g_StatusContext.ulPsCause = pData->ulPsCause;
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
            TAF_SDC_SetCsServiceStatus((VOS_UINT8)pData->ulCsServiceStatus);
            TAF_SDC_SetPsServiceStatus((VOS_UINT8)pData->ulPsServiceStatus);
            g_StatusContext.ulCsCause = pData->ulCsCause;
            g_StatusContext.ulPsCause = pData->ulPsCause;
            break;
        default :
            break;
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    return STA_SUCCESS;       /* 正常返回 */
}




/*
    在进入PLMN的稳态之后，通过MSCC的上报信息更新
    增添两个函数
    modified by liuyang id:48197 date:2005-9-5 for V200R001
*/
/*****************************************************************************
 函 数 名  : ClearCurPlmnId
 功能描述  : 将PLMNID置零，即为无效PLMN
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月5日
    作    者   : liuyang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   Sta_ClearCurPlmnId(TAF_PLMN_ID_STRU *pstNewPlmnId)
{
    pstNewPlmnId->Mcc  = 0;
    pstNewPlmnId->Mnc  = 0;
}

/*****************************************************************************
 函 数 名  : Sta_InitCurPlmnId
 功能描述  : 将当前PLMNid装入当前全局变量
 输入参数  : TAF_PLMN_ID_STRU NewPlmnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月5日
    作    者   : liuyang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID   Sta_InitCurPlmnId(TAF_PLMN_ID_STRU    stSrcPlmnId,
                             TAF_PLMN_ID_STRU   *pstDstPlmnId)
{
    *pstDstPlmnId = stSrcPlmnId;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

/*****************************************************************************
 函 数 名  : Sta_StopAllRunningTimer
 功能描述  : 停止所有运行的定时器，并清除定时器状态变量名相关的变量
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2006年1月19日
    作    者   : liuyang id:48197
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Sta_StopAllRunningTimer()
{
    VOS_UINT32      ulI;
    VOS_UINT32      ulRet = VOS_OK;

    for ( ulI = 0; ulI < STA_TIMER_MAX; ulI++ )
    {
        if (STA_TIMER_NULL != g_StatusContext.aFsmSub[ulI].TimerName )
        {
            ulRet = VOS_StopRelTimer (&g_StatusContext.ahStaTimer[ulI]);
            if ( VOS_OK != ulRet )
            {
                STA_TRACE (STA_WARNING_PRINT,
                    "Sta_StopAllRunningTimer():WARNING:VOS_StopRelTimer failed ");
            }
            g_StatusContext.aFsmSub[ulI].TimerName = STA_TIMER_NULL;
        }
    }
    return ulRet;
}



/*****************************************************************************
 函 数 名  : Sta_GetStatusForSat
 功能描述  : 将底层上报的状态转换为对SAT的状态
 输入参数  : ucServiceStatus
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月25日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_UINT8 Sta_GetStatusForSat(VOS_UINT32 ulServiceStatus)
{
    VOS_UINT8 ucSatServiceStatus;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    switch (ulServiceStatus)
    {
        case NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE:
            ucSatServiceStatus = STA_SAT_LOCATION_NORMAL_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE :
        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION :
        case NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI :
            ucSatServiceStatus = STA_SAT_LOCATION_LIMIT_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE:
            ucSatServiceStatus = STA_SAT_LOCATION_NO_SERVICE;
            break;

        default :
            ucSatServiceStatus = STA_SAT_LOCATION_NO_SERVICE;
            break;
    }
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

    return ucSatServiceStatus;
}

/*****************************************************************************
 函 数 名  : Sta_SndSatLocationStatus
 功能描述  : MMA处理Location Status Event
 输入参数  : pServiceStatus
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月25日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
*****************************************************************************/
VOS_VOID Sta_GetLocInfoForSat(
    MMA_MSCC_PLMN_ID_STRU                stPlmnId,
    VOS_UINT16                          usLac,
    VOS_UINT16                          usCellId,
    VOS_UINT8                          *pucLocInfo
)
{
    VOS_UINT8 ucSn = 0;
    /*lint -e961*/
    pucLocInfo[ucSn]    = (VOS_UINT8)(stPlmnId.ulMcc & 0x0000000f);
    pucLocInfo[ucSn++] |= (VOS_UINT8)((stPlmnId.ulMcc & 0x00000f00) >> 4);
    pucLocInfo[ucSn]    = (VOS_UINT8)((stPlmnId.ulMcc & 0x000f0000) >> 16);
    pucLocInfo[ucSn++] |= (VOS_UINT8)((stPlmnId.ulMnc & 0x000f0000) >> 12);
    pucLocInfo[ucSn]    = (VOS_UINT8)(stPlmnId.ulMnc & 0x0000000f);
    pucLocInfo[ucSn++] |= (VOS_UINT8)((stPlmnId.ulMnc & 0x00000f00) >> 4);

    pucLocInfo[ucSn++]  = (VOS_UINT8)(usLac >> 8);
    pucLocInfo[ucSn++]  = (VOS_UINT8)(usLac & 0x000000ff);

    pucLocInfo[ucSn++]  = (VOS_UINT8)(usCellId >> 8);
    pucLocInfo[ucSn++]  = (VOS_UINT8)(usCellId & 0x000000ff);
    /*lint +e961*/

    for (ucSn = 0; ucSn < STA_SAT_LOCATION_INFORMATON_LEN; ucSn ++)
    {
        STA_TRACE1(STA_INFO_PRINT,
                   "Sta_GetLocInfoForSat():INFO:Locinfo:",pucLocInfo[ucSn]);
    }

    return;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */


/*****************************************************************************
 函 数 名  : Mma_ModeChgReport
 功能描述  : 系统模式、系统子模式变化主动上报
 输入参数  : MSCC_CUR_NETWORK CurNetWork
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年03月27日
    作    者   : x00115505
    修改内容   : 新生成函数


  2.日    期   : 2010年6月11日
    作    者   : 欧阳飞
    修改内容   : 当异系统切换或者GSM下子模式发生改变时，需要上报^MODE通知应
                 用，上报的数传态下的子模式。
  3.日    期   : 2011年8月4日
    作    者   : z00161729
    修改内容   : V7R1 phase II修改
  4.日    期   : 2012年8月8日
    作    者   : s00217060
    修改内容   : for V7R1C50_GUTL_PhaseII修改
  5.日    期   : 2013年4月7日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  6.日    期   : 2015年2月26日
    作    者   : w00208541
    修改内容   : 增加CDMA相关上报
  7.日    期   : 2015年08月22日
    作    者   : y00307564
    修改内容   : DTS2015081005519修改
*****************************************************************************/
VOS_VOID Mma_ModeChgReport(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enCurNetWork,
    VOS_UINT8                           ucSysSubMode
)
{
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */

    VOS_UINT8                            ucModeChangeFlg;

    ucModeChangeFlg = TAF_MMA_IsModeChange(enCurNetWork, ucSysSubMode);

    if (VOS_TRUE == ucModeChangeFlg)
    {
        if (TAF_SDC_SYS_MODE_WCDMA == enCurNetWork)
        {
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                /* G->W下，先上报缺省模式: ^MODE:5,4,后续上报时根据RRMM_AT_MSG_IND更新 */
                Sta_ModeChangeEventReport(TAF_PH_INFO_WCDMA_RAT, TAF_SYS_SUBMODE_WCDMA);

#if (FEATURE_ON == FEATURE_PTM)
                TAF_MMA_RatSwitchRecord(TAF_PH_INFO_WCDMA_RAT);
#endif
            }
            else
            {
                /* G->TD下，先上报缺省模式: ^MODE:15,8,后续上报时根据RRMM_AT_MSG_IND更新 */
                Sta_ModeChangeEventReport(TAF_PH_INFO_TD_SCDMA_RAT, TAF_SYS_SUBMODE_TD_SCDMA);

#if (FEATURE_ON == FEATURE_PTM)
                TAF_MMA_RatSwitchRecord(TAF_PH_INFO_TD_SCDMA_RAT);
#endif
            }

            /* 更新全局变量中保存的UtranMode */
            g_StatusContext.ucPreUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        }
        else if (TAF_SDC_SYS_MODE_GSM == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_GSM_RAT, ucSysSubMode);

#if (FEATURE_ON == FEATURE_PTM)
            TAF_MMA_RatSwitchRecord(TAF_PH_INFO_GSM_RAT);
#endif
        }
        else if (TAF_SDC_SYS_MODE_LTE == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_LTE_RAT, ucSysSubMode);

#if (FEATURE_ON == FEATURE_PTM)
            TAF_MMA_RatSwitchRecord(TAF_PH_INFO_LTE_RAT);
#endif
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        else if (TAF_SDC_SYS_MODE_CDMA_1X == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_CDMA_1X_RAT, ucSysSubMode);
        }
        else if (TAF_SDC_SYS_MODE_EVDO == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_HRPD_RAT, ucSysSubMode);
        }
        else if (TAF_SDC_SYS_MODE_HYBRID == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_HYBRID_RAT, ucSysSubMode);
        }
#endif
        else if (TAF_SDC_SYS_MODE_SVLTE == enCurNetWork)
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_SVLTE_SRLTE_RAT, ucSysSubMode);
        }
        else
        {
            Sta_ModeChangeEventReport(TAF_PH_INFO_NONE_RAT, TAF_SYS_SUBMODE_NONE);
        }
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
    return;
}

/* Added by l00208543 for V9R1 STK升级, 2013-07-22, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertMmaRatToStkRat
 功能描述  : 将MMA的Rat Type转换成上报给STK的Rat Type
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8    enCurNetWork
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : l00208543
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 TAF_MMA_ConvertMmaRatToStkRat(
                                         TAF_SDC_SYS_MODE_ENUM_UINT8 enMmaRatType
                                         )
{
    switch (enMmaRatType)
    {
        case TAF_SDC_SYS_MODE_GSM:
             return TAF_MMA_RAT_GSM;

        case TAF_SDC_SYS_MODE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case TAF_SDC_SYS_MODE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            MN_ERR_LOG("TAF_MMA_ConvertMmaRatToStkRat: The input is invalid");
            return TAF_MMA_RAT_BUTT;
    }
}
/* Added by l00208543 for V9R1 STK升级, 2013-07-22, end */

/* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, begin */
/* 删除TAF_MMA_SndStkAccTechChgEvt */
/* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, end */

/*****************************************************************************
 函 数 名  : Sta_MmInfo
 功能描述  : 处理MM INFO消息上报
 输入参数  : MSCC_MMA_MM_INFO_IND_STRU *pstMmInfo - MM INFO结构指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月23日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  4.日    期   : 2015年2月25日
    作    者   : z00161729
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_UINT32 Sta_MmInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    TAF_MMA_TIME_CHANGE_IND_STRU        *pstTimeChangeInd      = VOS_NULL_PTR;
    MSCC_MMA_MM_INFO_IND_STRU           *pstMmInfo             = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    TAF_SDC_MM_INFO_STRU                *pstSdcMmInfo = VOS_NULL_PTR;

    pstSdcMmInfo = TAF_SDC_GetMmInfo();

    pstMmInfo             = (MSCC_MMA_MM_INFO_IND_STRU*)pstMsg;
    pstCurcRptCtrl        = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl = TAF_SDC_GetUnsolicitedRptCtrl();

    if ( VOS_TRUE != TAF_MMA_IsTimeChangeNeedRpt())
    {
        return VOS_TRUE;
    }

    pstTimeChangeInd = (TAF_MMA_TIME_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA, sizeof(TAF_MMA_TIME_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstTimeChangeInd)
    {
        MMA_ERRORLOG("Sta_MmInfo:ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_CHAR *)pstTimeChangeInd + VOS_MSG_HEAD_LENGTH,
            0x00,
            (sizeof(TAF_MMA_TIME_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstTimeChangeInd->MsgHeader.ulReceiverPid          = WUEPS_PID_AT;
    pstTimeChangeInd->MsgHeader.ulMsgName              = ID_TAF_MMA_TIME_CHANGE_IND;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    pstSdcMmInfo->stOperatorPlmnId.ulMcc        = pstMmInfo->stName.stOperatorPlmnId.ulMcc;
    pstSdcMmInfo->stOperatorPlmnId.ulMnc        = pstMmInfo->stName.stOperatorPlmnId.ulMnc;

    pstSdcMmInfo->stOperatorNameLong.ucLength   = 0;

    if (0 != pstMmInfo->stName.aucOperatorNameLong[0])
    {
        pstSdcMmInfo->stOperatorNameLong.ucLength   = pstMmInfo->stName.aucOperatorNameLong[0] - 1;
        pstSdcMmInfo->stOperatorNameLong.bitExt     = (pstMmInfo->stName.aucOperatorNameLong[1] & 0x80) >> TAF_SDC_OCTET_MOVE_SEVEN_BITS;
        pstSdcMmInfo->stOperatorNameLong.bitCoding  = (pstMmInfo->stName.aucOperatorNameLong[1] & 0x70) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
        pstSdcMmInfo->stOperatorNameLong.bitSpare   = pstMmInfo->stName.aucOperatorNameLong[1] & 0x07;
        pstSdcMmInfo->stOperatorNameLong.bitAddCi   = pstMmInfo->stName.aucOperatorNameLong[1] & 0x08;

        if (pstSdcMmInfo->stOperatorNameLong.ucLength > TAF_SDC_MAX_OPER_NAME_NUM)
        {
            pstSdcMmInfo->stOperatorNameLong.ucLength = TAF_SDC_MAX_OPER_NAME_NUM;
        }

    }

    pstSdcMmInfo->stOperatorNameShort.ucLength = 0;

    if (0 != pstMmInfo->stName.aucOperatorNameShort[0])
    {
        pstSdcMmInfo->stOperatorNameShort.ucLength  = pstMmInfo->stName.aucOperatorNameShort[0] - 1;
        pstSdcMmInfo->stOperatorNameShort.bitExt    = (pstMmInfo->stName.aucOperatorNameShort[1] & 0x80) >> TAF_SDC_OCTET_MOVE_SEVEN_BITS;
        pstSdcMmInfo->stOperatorNameShort.bitCoding = (pstMmInfo->stName.aucOperatorNameShort[1] & 0x70) >> TAF_SDC_OCTET_MOVE_FOUR_BITS;
        pstSdcMmInfo->stOperatorNameShort.bitSpare  = pstMmInfo->stName.aucOperatorNameShort[1] & 0x07;
        pstSdcMmInfo->stOperatorNameShort.bitAddCi  = pstMmInfo->stName.aucOperatorNameShort[1] & 0x08;

        if (pstSdcMmInfo->stOperatorNameShort.ucLength > TAF_SDC_MAX_OPER_NAME_NUM)
        {
            pstSdcMmInfo->stOperatorNameShort.ucLength = TAF_SDC_MAX_OPER_NAME_NUM;
        }
    }

    PS_MEM_CPY(pstSdcMmInfo->stOperatorNameLong.aucOperatorName, &pstMmInfo->stName.aucOperatorNameLong[2], pstSdcMmInfo->stOperatorNameLong.ucLength);
    PS_MEM_CPY(pstSdcMmInfo->stOperatorNameShort.aucOperatorName, &pstMmInfo->stName.aucOperatorNameShort[2], pstSdcMmInfo->stOperatorNameShort.ucLength);
    PS_MEM_CPY(pstTimeChangeInd->aucLSAID, pstMmInfo->aucLSAID, sizeof(pstTimeChangeInd->aucLSAID));
    pstTimeChangeInd->stUniversalTimeandLocalTimeZone  = pstMmInfo->stUniversalTimeandLocalTimeZone;
    pstTimeChangeInd->cLocalTimeZone                   = pstMmInfo->cLocalTimeZone;
    pstTimeChangeInd->ucDST                            = pstMmInfo->ucDST;
    pstTimeChangeInd->ucIeFlg                          = pstMmInfo->ucIeFlg;
    pstTimeChangeInd->usClientId                       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstTimeChangeInd->ucOpId                           = MMA_OP_ID_INTERNAL;
    PS_MEM_CPY(pstTimeChangeInd->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    PS_MEM_CPY(pstTimeChangeInd->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    PS_SEND_MSG(WUEPS_PID_MMA, pstTimeChangeInd);
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertServiceTypeToAtType
 功能描述  : 将MMA的PlmnSelRslt转换成上报给At的PlmnSelRslt Type
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8    enCurNetWork
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : l00208543
    修改内容   : 新生成函数

*****************************************************************************/

TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32 TAF_MMA_ConvertServiceTypeToAtType(
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32 enMmaServiceType
)
{
    switch (enMmaServiceType)
    {
        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE:
             return TAF_PH_PLMN_SELECTION_RESULT_NORMAL_SERVICE;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE:
             return TAF_PH_PLMN_SELECTION_RESULT_LIMITED_SERVICE;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE:
             return TAF_PH_PLMN_SELECTION_RESULT_NO_SERVICE;

        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT:
        case NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF:
             return TAF_PH_PLMN_SELECTION_RESULT_INTERRUPT;

        default:
            MN_ERR_LOG("TAF_MMA_ConvertServiceTypeToAtType: The input is invalid");
            return TAF_PH_PLMN_SELECTION_RESULT_BUTT;
    }
}



/*****************************************************************************
 函 数 名  : MN_PH_GetRegCostTime
 功能描述  : 返回当前开机搜网成功注册花费的时间
 输入参数  : 无
 输出参数  : VOS_UINT32:开机搜网注册花费的时间,单位为s
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月8日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  MN_PH_GetRegCostTime( VOS_VOID )
{
    return g_stRegTimeInfo.ulCostTime;
}

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

/*****************************************************************************
 函 数 名  : MMA_GetCurrPhMode
 功能描述  : 获取当前手机模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : TAF_PH_MODE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PH_MODE MMA_GetCurrPhMode(VOS_VOID)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, begin */
    return TAF_SDC_GetCurPhoneMode();
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-12, end */
}

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseI项目, 2013-7-11, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_ReportPlmnModeEvent
 功能描述  : 上报+PACSP
 输入参数  : VOS_UINT8 ucPlmnMode
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ReportPlmnModeEvent(VOS_UINT8 ucPlmnMode)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("TAF_MMA_ReportPlmnModeEvent:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    pstPhoneEvent->OP_PlmnMode  = VOS_TRUE;
    pstPhoneEvent->PhoneEvent   = TAF_PH_EVT_NSM_STATUS_IND;
    pstPhoneEvent->ucPlmnMode   = ucPlmnMode;

    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsEnablePlmnList
 功能描述  : 根据当前状态，判断是否允许用户发起list搜网请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsEnablePlmnList(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    /* refresh触发的自动搜网 */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsEnablePlmnSelect
 功能描述  : 根据当前状态，判断是否允许用户发起指定搜网请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsEnablePlmnSelect(VOS_VOID)
{
    TAF_MMA_PLMN_MODE_ENUM_UINT8        enPlmnMode;

    enPlmnMode = TAF_MMA_GetPlmnMode_Refresh();

    /* 只有在ENABLE状态，并且网络没有disable掉网络选择菜单，才能进行指定搜网 */
    if ((STA_FSM_ENABLE == g_StatusContext.ulFsmState)
     && (TAF_MMA_PLMN_MODE_ENUM_ENABLE == enPlmnMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsEnableDeAttach
 功能描述  : 根据当前状态，判断是否允许用户发起ATTACH和DETACH请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsEnableDeAttach(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }



    /* refresh触发的自动搜网 */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    /* refresh触发的SYSCFG，在收到CNF之后可能会触发attach。
       此时用户下发attach或者detach，不能打断SYSCFG。
       而且MMA目前没有缓存机制，所以直接给用户返回ERROR。
    */

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndAutoPlmnReselect_Refresh
 功能描述  : 发送Refresh触发的自动搜网请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID TAF_MMA_SndAutoPlmnReselect_Refresh(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    ulRet = TAF_MMA_SndMsccPlmnUserReselReq(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

    if (VOS_ERR == ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAutoPlmnReselect_Refresh(): send msg fail");
        return;
    }

    /* 记录PLMN重新类型 */
    g_StatusContext.ucReselMode   = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */

    /* 记录当前的主状态 */
    g_StatusContext.ulPreFsmState = g_StatusContext.ulFsmState;

    /* 设置主状态 */
    g_StatusContext.ulFsmState    = STA_FSM_PLMN_RESEL;

    /* 设置子状态 */
    g_StatusContext.aucFsmSubFlag[0]         = STA_FSMSUB_PLMN_RESEL_AUTO;
    g_StatusContext.aFsmSub[0].ucFsmStateSub = STA_FSMSUB_PLMN_RESEL_AUTO;
    g_StatusContext.aFsmSub[0].TimerName     = STA_TIMER_PLMN_RESEL;

    /* 启动PLMN_RESEL状态定时器 */
    ulRet = NAS_StartRelTimer(&g_StatusContext.ahStaTimer[0],
                              WUEPS_PID_MMA,
                              aStaTimerLen[STA_TIMER_PLMN_RESEL],
                              TAF_MMA,
                              MMA_MAKELPARAM(0, STA_TIMER_PLMN_RESEL),
                              VOS_RELTIMER_NOLOOP
                              );
    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAutoPlmnReselect_Refresh(): start timer fail");
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccPlmnReselCnf
 功能描述  : MMA收at+cops=0的回复的处理
 输入参数  : MSCC_MMA_PLMN_RESEL_CNF_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月14日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPlmnReselCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_PLMN_RESEL_CNF_STRU        *pstPlmnReselCnfMsg;

    pstPlmnReselCnfMsg = (MSCC_MMA_PLMN_RESEL_CNF_STRU*)pstMsg;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_MMA_SetPlmnSelectionMode(TAF_PH_PLMN_SEL_MODE_AUTO);

    /* 如果是6F15文件refresh触发的自动搜网 */
    if (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == TAF_MMA_GetAutoPlmnSelUser())
    {
        /* MSCC给MMA回复指定搜和自动搜都是D_MSCC_PLMN_SEL_CNF消息，refresh只会触发自动搜网 */
        if (STA_FSM_PLMN_RESEL != g_StatusContext.ulFsmState)
        {
            return VOS_TRUE;
        }

        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    }
    /* AT发起的自动搜网或指定搜网，按原有流程 */
    else
    {
        (VOS_VOID)Sta_SelPlmnAutoSelCnf(pstPlmnReselCnfMsg->enResult);
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccPlmnSpecialSelCnf
 功能描述  : MMA收到MSCC 用户指定搜网回复消息
 输入参数  : MMA_MSCC_PLMN_SPECIAL_REQ_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
  3.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容   : DTS2013111103301: svlte需要关机状态支持cops设置，更新nv项搜网模式
  4.日    期   : 2014年3月7日
    作    者   : w00176964
    修改内容   : DTS2014030610626:关机模式设置手动模式需要刷新全局变量

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPlmnSpecialSelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU  *pstPlmnSpecSelCnfMsg;

    pstPlmnSpecSelCnfMsg = (MSCC_MMA_PLMN_SPECIAL_SEL_CNF_STRU*)pstMsg;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF);

    /* svlte nv开启允许关机状态设置cops */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_MMA_SetPlmnSelectionMode(NAS_MSCC_PIF_PLMN_SEL_MODE_MANUAL);

        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, begin */
    TAF_MMA_SetPlmnSelectionMode(TAF_PH_PLMN_SEL_MODE_MANUAL);

    (VOS_VOID)Sta_SelPlmnSpecializeCnf(pstPlmnSpecSelCnfMsg->enResult);

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-2, end */

    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}

/*****************************************************************************
 函 数 名  : TAF_MMA_StopStatusCtxTimer
 功能描述  : 停止状态机的定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_StopStatusCtxTimer(VOS_VOID)
{
    VOS_UINT32                            ulRet;

    /* 关闭当前状态的定时器保护*/
    if (VOS_NULL != g_StatusContext.ahStaTimer[0])
    {
        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                 g_StatusContext.aFsmSub[0].TimerName,
                                 &g_StatusContext.ahStaTimer[0]);
        if ( VOS_OK != ulRet )
        {
            STA_TRACE (STA_WARNING_PRINT,
                "TAT_MMA_ProcPhoneStop_NotEnableStatus():WARNING:NAS_StopRelTimer failed  ");
        }
        g_StatusContext.ahStaTimer[0] = VOS_NULL;
    }

    if ( VOS_NULL != g_StatusContext.ahStaTimer[1] )
    {
        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                 g_StatusContext.aFsmSub[1].TimerName,
                                 &g_StatusContext.ahStaTimer[1]);


        if ( VOS_OK != ulRet )
        {
            STA_TRACE (STA_WARNING_PRINT,
                "TAT_MMA_ProcPhoneStop_NotEnableStatus():WARNING:NAS_StopRelTimer failed  ");
        }
        g_StatusContext.ahStaTimer[1] = VOS_NULL;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcPhoneStop_NotEnableStatus
 功能描述  : 在非ENABLE状态，处理协议栈停止的函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcPhoneStop_NotEnableStatus(VOS_VOID)
{
    VOS_UINT32                            ulRet;
    VOS_UINT32                            ulIsRefreshAutoPlmnSel;
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    ulIsRefreshAutoPlmnSel = VOS_FALSE;

    /* refresh触发的自动搜网 */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        ulIsRefreshAutoPlmnSel = VOS_TRUE;
    }

    /* 如果在SYSCFG过程，在SYSCFG状态机中处理abort。此处删除 */

    /* 如果是Refresh触发的自动搜网，不需要上报响应事件通知APP*/
    if (VOS_TRUE != ulIsRefreshAutoPlmnSel)
    {
        /* 终止当前的请求过程，上报响应事件通知APP */
        ulRet = Sta_MsgReqAbort (STA_MSGABORT_ERR);
        if (STA_ERROR == ulRet)
        {
            NAS_WARNING_LOG(WUEPS_PID_MMA,
                "TAF_MMA_ProcPhoneStop_NotEnableStatus(): different request abort failed  ");
        }
    }

    TAF_MMA_StopStatusCtxTimer();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_DeleteRatType
 功能描述  : 从接入技术列表中删除指定的模式
 输入参数  : TAF_MMA_RAT_TYPE_ENUM_UINT8           ucRatType
             MMA_MSCC_PLMN_RAT_PRIO_STRU           *pstPlmnRatPrioList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月28日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2013年4月4日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
*****************************************************************************/
VOS_VOID TAF_MMA_DeleteRatType(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          ucRatType,
    TAF_MMA_RAT_ORDER_STRU              *pstPlmnRatPrioList
)
{
    VOS_UINT32                          i;

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, begin */
    TAF_MMA_RAT_ORDER_STRU              stOldPlmnRatPrioList;

    PS_MEM_SET(&stOldPlmnRatPrioList, 0, sizeof(TAF_MMA_RAT_ORDER_STRU));

    /* 记录输入的接入技术列表 */
    PS_MEM_CPY(&stOldPlmnRatPrioList, pstPlmnRatPrioList, sizeof(TAF_MMA_RAT_ORDER_STRU));


    pstPlmnRatPrioList->ucRatOrderNum = 0;

    /* 接入技术初始化为BUTT */
    for (i = 0 ; i < TAF_PH_MAX_GUL_RAT_NUM; i++)
    {
        pstPlmnRatPrioList->aenRatOrder[i] = TAF_SDC_SYS_MODE_BUTT;
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-4, end */

    if (stOldPlmnRatPrioList.ucRatOrderNum > TAF_PH_MAX_GUL_RAT_NUM)
    {
        stOldPlmnRatPrioList.ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    }

    for (i = 0 ; i < stOldPlmnRatPrioList.ucRatOrderNum; i++)
    {
        if (ucRatType == stOldPlmnRatPrioList.aenRatOrder[i])
        {
            continue;
        }
        pstPlmnRatPrioList->aenRatOrder[pstPlmnRatPrioList->ucRatOrderNum] = stOldPlmnRatPrioList.aenRatOrder[i];
        pstPlmnRatPrioList->ucRatOrderNum++;
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_GetAvailablePlmnRatPrio
 功能描述  : 获取有效的接入技术列表
 输入参数  : MMA_MSCC_PLMN_RAT_PRIO_STRU *pstPlmnRatPrioList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月18日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年11月09日
    作    者   : s00217060
    修改内容   : DTS2012102902559 调整：SIM卡时，开机和SYSCFG设为LTE only，也不删除L模
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2012年12月28日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加平台接入技术能力判断
  5.日    期   : 2013年3月26日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核项目把mscc部分全局变量移至sdc
  6.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  7.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID TAF_MMA_GetAvailablePlmnRatPrio(TAF_MMA_RAT_ORDER_STRU *pstPlmnRatPrioList)
{

    VOS_UINT32                          ulGsmAccessForbidden;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucCardType;
    VOS_UINT32                          ulGsmForbidden;
    VOS_UINT8                           i;

    VOS_UINT8                           ucRatBalancingEnableFlg;

    ucRatBalancingEnableFlg = TAF_MMA_GetRatBalancingEnableFlg();

    ucCardType = 0;
#endif


    ulGsmAccessForbidden = TAF_MMA_IsGsmAccessForbidden();

    /* 如果UE不支持GSM接入，当设置非G单模去掉G模，如果是G单模，由MSCC控制提供限制服务 */
    if ((VOS_FALSE == MN_MMA_IsGOnlyMode((TAF_MMA_RAT_ORDER_STRU *)pstPlmnRatPrioList))
     && (VOS_TRUE == ulGsmAccessForbidden))
    {
        TAF_MMA_DeleteRatType(TAF_MMA_RAT_GSM, pstPlmnRatPrioList);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* SIM卡校正去掉L模 */
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;

    /* SIM卡时，如果是LTE only，不删除L模 */
    if ( (USIMM_CARD_SIM == ucCardType)
      && (VOS_TRUE == ucRatBalancingEnableFlg) )
    {
        TAF_MMA_DeleteRatType(TAF_MMA_RAT_LTE, pstPlmnRatPrioList);
    }

    /* 如果个数为0,即当前仅存在L单模也接入禁止时,默认为GW模 */
    if (0 == pstPlmnRatPrioList->ucRatOrderNum)
    {
        i = 0;
        if (VOS_TRUE == TAF_SDC_IsPlatformSupportUtran())
        {
            pstPlmnRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_WCDMA;
            i ++;
        }

        ulGsmForbidden = MMA_IsGsmForbidden();
        if ((VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
         && ((VOS_FALSE == ulGsmForbidden)))
        {
            pstPlmnRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_GSM;
            i ++;
        }
        pstPlmnRatPrioList->ucRatOrderNum      = i;
    }
#endif

    return;

}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsModeChange
 功能描述  : 判断模式(包括系统模式、系统子模式)是否变化
 输入参数  : MSCC_CUR_NETWORK ucCurNetWork :当前网络
              VOS_UINT8       ucSysSubMode :系统子模式
 输出参数  : 无
 返 回 值  : VOS_FALSE :模式没变化
              VOS_TRUE : 模式变化
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年08月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年4月3日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2013年6月4日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2013年7月24日
    作    者   : z00161729
    修改内容   : V9R1 STK升级修改
*****************************************************************************/
VOS_UINT8 TAF_MMA_IsModeChange(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enCurNetWork,
    VOS_UINT8                           ucSysSubMode
)
{
    VOS_UINT8                           ucModeChangeFlg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    ucModeChangeFlg = VOS_FALSE;

    /* 如果接入技术不相同，需要上报Mode */
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
    if (enCurNetWork != TAF_SDC_GetSysMode())
    {
        ucModeChangeFlg = VOS_TRUE;
#ifndef __PS_WIN32_RECUR__
        /* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, begin */
        /* Deleted by z00161729 for V9R1 STK升级, 2013-7-24, end */
#endif
    }
    /* 接入技术为G时，系统子模式不同时，需要上报Mode */
    else if (TAF_SDC_SYS_MODE_GSM == enCurNetWork)
    {
        if (ucSysSubMode != TAF_SDC_GetSysSubMode())
        {
            ucModeChangeFlg = VOS_TRUE;
        }
    }

    /* 当前网络为WCDMA时，有可能TD->W或W->TD,需要进一步判断UtranMode
       如果UtranMode发生变化，需要上报Mode */
    else if (TAF_SDC_SYS_MODE_WCDMA == enCurNetWork)
    {
        if (enCurrUtranMode != g_StatusContext.ucPreUtranMode)
        {
            ucModeChangeFlg             = VOS_TRUE;
        }
    }

    else if ((TAF_SDC_SYS_MODE_CDMA_1X == enCurNetWork)
          || (TAF_SDC_SYS_MODE_EVDO    == enCurNetWork)
          || (TAF_SDC_SYS_MODE_HYBRID  == enCurNetWork))
    {
        if (ucSysSubMode != TAF_SDC_GetSysSubMode())
        {
            ucModeChangeFlg = VOS_TRUE;
        }
    }

    else
    {
    }

    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

    return ucModeChangeFlg;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMsccPlmnReselCnf
 功能描述  : MMA收到MSCC D_MSCC_PLMN_SEL_CNF消息的处理
 输入参数  : MSCC_PLMN_SEL_CNF_ST *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2013年4月2日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
  3.日    期   : 2012年07月15日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseI项目修改:修改函数参数和返回值
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccUserPlmnRej(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF);

    /* 上报当前指定搜网失败 */
    MMA_NORMAILLOG("NAS_MN_ReportPlmnSrchResult():NORMAIL:SPECIALIZE THE PLMN FAILURE!");

    /* 上报APP当前状态事件 */
    TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_CMD_TYPE_ERROR);

    STA_TRACE(STA_NORMAL_PRINT, "NAS_MN_ReportPlmnSrchResult: TAF_PH_EVT_PLMN_SEL_CNF reported to AT!");

    g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, begin */
    return VOS_TRUE;

    /* Modified by w00176964 for VoLTE_PhaseI项目, 2013-7-15, end */
}




/*****************************************************************************
 函 数 名  : TAF_MMA_RcvTimerPlmnListCnfExpired
 功能描述  : Plmn List被打断的处理
 输入参数  : VOS_UINT32 OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年4月1日
    作    者   : z00161729
    修改内容   : 主动上报AT命令控制下移至C核及mma和mscc接口调整
*****************************************************************************/
VOS_VOID  TAF_MMA_RcvTimerPlmnListCnfExpired( VOS_UINT32 ulOpId )
{
    VOS_UINT32                          ulRet;

    /* 当前状态不是PLMN LIST状态，直接返回 */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvUserAbortPlmnList():WARNING: no plmn list searching");
        return;
    }

    /* MMA的LIST搜网保护定时器超时则主动向MSCC发送停止LIST搜网请求
       收到MSCC的回复后再向AT回复 */
    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, begin*/
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, begin */
    ulRet = TAF_MMA_SndMsccPlmnListAbortReq();

    if (VOS_ERR == ulRet)
    /* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-1, end */
    {
        STA_TRACE(STA_ERROR_PRINT, "TAF_MMA_AbortPlmnList():ERROR: failed");
    }


    /* 启动STA_TIMER_PLMN_LIST_ABORT 10s定时器，如果超时未收到MSCC的回复则上报AT失败 */
    /* 启动STA_TIMER_PLMN_LIST_ABORT 10s定时器，如果超时未收到MSCC的回复则上报AT失败 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF, TAF_MMA_GetPlmnListAbortTimerLen());

    /*modified by Y00213812 for DTS2012082204471 TQE清理, 2012-08-10, end*/

    /* 设置当前正在处理定时器超时的列表搜打断过程 */
    g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPlmnListAbortReq_Main
 功能描述  : Plmn List被打断的处理
 输入参数  : VOS_UINT32 OpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月25日
    作    者   : f00279542
    修改内容   : CDMA Iteration 11 重构修改
*****************************************************************************/
VOS_UINT32  TAF_MMA_RcvPlmnListAbortReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_LIST_ABORT_REQ_STRU    *pstPlmnListAbortMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulRet;
    VOS_UINT8                            ucCtxIndex;

    pstPlmnListAbortMsg = (TAF_MMA_PLMN_LIST_ABORT_REQ_STRU *)pstMsg;

    /* MMA上报PLMN LIST CNF和列表搜打断对冲时，当前状态已不是PLMN LIST状态，
       直接给AT回复TAF_PH_EVT_PLMN_LIST_ABORT_CNF */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        STA_TRACE(STA_ERROR_PRINT, "TAF_MMA_RcvPlmnListAbortReq_Main():WARNING: no plmn list searching");

        /* 上报AT当前状态事件 */
        TAF_MMA_SndPlmnListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    /* 定时器超时打断列表搜和用户打断列表搜对冲时，以用户打断为准 */
    if (TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == g_StatusContext.ucPlmnListAbortProc)
    {
        STA_TRACE(STA_ERROR_PRINT, "TAF_MMA_RcvPlmnListAbortReq_Main():WARNING: plmn list abort processing");

        /* 设置当前正在处理用户打断列表搜过程 */
        g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT;

        return VOS_TRUE;
    }

    /* 停列表搜定时器 */
    if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA,
                                   STA_TIMER_PLMN_LIST,
                                  &g_StatusContext.ahStaTimer[0]))
    {
        STA_TRACE(STA_ERROR_PRINT, "TAF_MMA_RcvPlmnListAbortReq_Main():WARNING: NAS_StopRelTimer failed");
    }

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_LIST_ABORT_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_LIST_ABORT_REQ))
    {
        /* 直接回复PLMN LIST ABORT设置失败 */
        TAF_MMA_SndPlmnListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnListAbortMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_LIST_ABORT_REQ, ucCtxIndex);

    /* MMA的LIST搜网保护定时器超时则主动向MSCC发送停止LIST搜网请求
       收到MSCC的回复后再向AT回复 */
    ulRet = TAF_MMA_SndMsccPlmnListAbortReq();
    if (VOS_ERR == ulRet)
    {
        STA_TRACE(STA_ERROR_PRINT, "TAF_MMA_RcvPlmnListAbortReq_Main():ERROR: failed");
    }

    /* 启动STA_TIMER_PLMN_LIST_ABORT 10s定时器，如果超时未收到MSCC的回复则上报AT失败 */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF, TAF_MMA_GetPlmnListAbortTimerLen());
    /* 设置当前正在进行用户打断列表搜过程 */
    g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT;
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_IsGsmAccessForbidden
 功能描述  : 判断是否禁止GSM接入
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:禁止GSM接入
              VOS_FALSE:允许GSM接入
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目
  2.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
  3.日    期   : 2013年7月29日
    作    者   : y00245242
    修改内容   : 适配新的USIM接口
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsGsmAccessForbidden(VOS_VOID)
{
    VOS_UINT32   ulEfustGsmAccess;
    VOS_UINT32   ulEfustGsmSecContext;
    VOS_UINT8    ucSimStatus;
    VOS_UINT8    ucSimType;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == gstMmaValue.stEfustServiceCfg.ucForbidReg2GNetWork)
    {
        /*获取卡状态和卡类型*/
        (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
        (VOS_VOID)MMA_PhoneGetUsimType(&ucSimType);

        if ( ( MMA_USIM_PRESENT == ucSimStatus )
            && (MMA_USIM_TYPE_USIM == ucSimType) )
        {
            /* 根据USIM卡文件中EFust，第27和38项判断是否允许GSM接入 */
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, begin */
            ulEfustGsmAccess     = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_ACCESS_IN_USIM);
            ulEfustGsmSecContext = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_GSM_SECURITY_CONTEXT);
            /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-29, end */

            if ((0 == ulEfustGsmAccess) && (0 == ulEfustGsmSecContext))
            {
                return VOS_TRUE;
            }
        }

    }

    return VOS_FALSE;
}

/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, begin */
/* TAF_MMA_InitTimerLen移动位置 */
/* Deleted by s00217060 for VoLTE_PhaseI  项目, 2013-07-13, end */


/*****************************************************************************
 函 数 名  : TAF_MMA_IsExistPlmnRatAllowAccess
 功能描述  : 判断是否存在可以发起接入的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:存在可以发起接入的接入技术
              VOS_FALSE:不存在可以发起接入的接入技术
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年02月25日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2013年06月5日
    作    者   : w00242748
    修改内容   : svlte和usim接口调整
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsExistPlmnRatAllowAccess(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU              *pstRatPrioList = VOS_NULL_PTR;
    VOS_UINT32                          ulGOnlyModeFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulLOnlyModeFlg;
    VOS_UINT8                           ucCardType;

	ucCardType = 0;
#endif

    ulGOnlyModeFlg = VOS_FALSE;
    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();
    ulGOnlyModeFlg = MN_MMA_IsGOnlyMode(pstRatPrioList);

#if (FEATURE_ON == FEATURE_LTE)
    ulLOnlyModeFlg = VOS_FALSE;
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType);
    ulLOnlyModeFlg = MN_MMA_IsLOnlyMode(pstRatPrioList);
#endif

    /* USIM卡禁止GSM接入并且是G单模时，不允许用户指定搜 */
    if ((VOS_TRUE == TAF_MMA_IsGsmAccessForbidden())
     && (VOS_TRUE == ulGOnlyModeFlg))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* SIM卡并且是L单模时，也不允许用户指定搜 */
    if ((USIMM_CARD_SIM == ucCardType)
     && (VOS_TRUE == ulLOnlyModeFlg))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;

}

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_ReportRegStatus
 功能描述  : 注册状态上报
 输入参数  : enCsRegState - 注册状态
             enCnDomainId - 服务域
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月3日
    作    者   : z00161729
    修改内容   : 新增函数
  2.日    期   : 2013年06月3日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，注册状态关机也需要上报
  3.日    期   : 2014年2月18日
    作    者   : y00245242
    修改内容   : 问题单号dts2014021501200, CGREG/CREG主动上报命令无法上报
  4.日    期   : 2015年2月15日
    作    者   : s00217060
    修改内容   : reg state report修改：变化了再上报，不变化无需要上报
  5.日    期   : 2015年5月15日
    作    者   : w00281933
    修改内容   : Service_State_Optimize_PhaseII修改
  6.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_MMA_ReportRegStatus(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8        enRegState,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId
)
{
    VOS_UINT32                          ulCellInfoChg;
    TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstAppServPlmnInfo;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enServiceStatus;
    TAF_SDC_CEREG_TYPE_ENUM_UINT8       enCeregType;

    enCeregType                         = TAF_SDC_CEREG_TYPE_BUTT;
    enServiceStatus                     = TAF_SDC_GetServiceStatus();
    pstAppServPlmnInfo                  = &(TAF_SDC_GetAppNetworkInfo()->stAppSysInfo.stServPlmnInfo);
    ulCellInfoChg                       = TAF_MMA_IsAppNetworkInfoCellChange(pstAppServPlmnInfo);

    /*指定域的注册改变，上报注册状态*/
    if (VOS_TRUE == TAF_SDC_IsAppSepcDomainRegStaChg((TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8)enCnDomainId,enRegState))
    {
        TAF_MMA_SndAtRegStatus(enCnDomainId, enRegState);
    }
    else
    {
        /* CREG/CGREG上报类型为2时，包含lac,cellid,rat，因此这三个参数或者PLMN变化时，需要上报 */
        if ((VOS_TRUE                             == ulCellInfoChg)
         && (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == enServiceStatus))
        {
            /* CREG为2时 */
            if ((TAF_SDC_CREG_TYPE_ENTIRE == TAF_SDC_GetCregType())
             && (NAS_MSCC_PIF_SRVDOMAIN_CS     == enCnDomainId))
            {
                TAF_MMA_SndAtRegStatus(NAS_MSCC_PIF_SRVDOMAIN_CS, TAF_SDC_GetCsRegStatus());
            }

            /* CGREG或CEREG为2 */
            enCeregType = TAF_SDC_GetCeregType();

            if (((TAF_SDC_CGREG_TYPE_ENTIRE == TAF_SDC_GetCgregType())
              || (TAF_SDC_CEREG_TYPE_ENTIRE == enCeregType))
             && (NAS_MSCC_PIF_SRVDOMAIN_PS       == enCnDomainId))
            {
                TAF_MMA_SndAtRegStatus(NAS_MSCC_PIF_SRVDOMAIN_PS, TAF_SDC_GetPsRegStatus());
            }
        }
    }

    /* SPN INFO未看到有使用的地方，处理逻辑删除 */


    return;
}



/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

/*****************************************************************************
 函 数 名  : TAF_MMA_IsCsServDomainAvail
 功能描述  : 根据手机模式判断CS域能力是否可用
 输出参数  : 无
 返 回 值  : VOS_TRUE:CS域能力可用；VOS_FALSE:CS域能力不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCsServDomainAvail(
    TAF_PH_MS_CLASS_TYPE                enMsClassType
)
{
    /* 手机模式是A模式或者CC模式，则认为CS域可用，其他情况认为CS域不可用 */
    if ( (TAF_PH_MS_CLASS_A  == enMsClassType)
      || (TAF_PH_MS_CLASS_CC == enMsClassType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsPsServDomainAvail
 功能描述  : 根据手机模式判断PS域能力是否可用
 输出参数  : 无
 返 回 值  : VOS_TRUE:PS域能力可用；VOS_FALSE:PS域能力不可用
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月25日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsPsServDomainAvail(
    TAF_PH_MS_CLASS_TYPE                enMsClassType
)
{
    /* 手机模式是A模式或者CG模式，则认为PS域可用，其他情况认为PS域不可用 */
    if ( (TAF_PH_MS_CLASS_A  == enMsClassType)
      || (TAF_PH_MS_CLASS_CG == enMsClassType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndStkCsServiceChangeNotify
 功能描述  : 给STK发送模式变更通知
 输入参数  : enCsState - cs服务域能力
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月3日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndStkCsServiceChangeNotify(
    TAF_CS_SERVICE_ENUM_UINT32          enCsState
)
{
    VOS_UINT32                          ulRet;
    TAF_STK_CS_SERVICE_IND             *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_STK_CS_SERVICE_IND *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                           sizeof(TAF_STK_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "TAF_MMA_SndStkCsServiceChangeNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(TAF_STK_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = NAS_GetOamReceivePid(MAPS_STK_PID);
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_TAF;
    pstMsg->ulLength         = sizeof(TAF_STK_CS_SERVICE_IND) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgName        = TAF_STK_CS_STATE_IND;
    pstMsg->enCSState        = enCsState;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_TAF, pstMsg );

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "TAF_MMA_SndStkCsServiceChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;

}

/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, begin */

/* Deleted by w00176964 for VoLTE_PhaseII 项目, 2013-10-10, end */



/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedSndStkEvt
 功能描述  : 接入技术变化是否需要上报给STK,SVLTE形态下，如果没有CS域能力，无需上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要；VOS_FALSE:不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedSndStkEvt(VOS_VOID)
{
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
       if (VOS_TRUE == TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
       {
           return VOS_TRUE;
       }
       return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndMtaAreaLostInd
 功能描述  : MMA给MTA发送丢网指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : z60575
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtaAreaLostInd(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    NAS_MTA_AREA_LOST_IND_STRU         *pstMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstMsg = (NAS_MTA_AREA_LOST_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                           sizeof(NAS_MTA_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMtaAreaLostInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(NAS_MTA_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MTA;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(NAS_MTA_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName        = ID_NAS_MTA_AREA_LOST_IND;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMA, pstMsg );

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMsgCsServiceChangeNotify:ERROR:PS_SEND_MSG FAILURE");
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_PlmnReselectAutoReq_PowerOff
 功能描述  : MMA关机状态下收到at+cops=0的处理
 输入参数  : ulOpId - 命令操作标识
             stPlmnId - 指定的PLMN
             ucAccessMode - 指定的接入模式
             ucReselMode - 指定PLMN失败后的重选模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月04日
    作    者   : z00161729
    修改内容   : 新增函数
  2.日    期   : 2014年3月7日
    作    者   : w00176964
    修改内容   : DTS2014030610626:MMA写NV时需要刷新全局变量

*****************************************************************************/
VOS_UINT32  TAF_MMA_PlmnReselectAutoReq_PowerOff(VOS_UINT32 ulOpID)
{
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo = VOS_NULL_PTR;

    pstMsCapInfo = TAF_SDC_GetMsCapInfo();
    TAF_SDC_InitSvlteSupportFlag(TAF_SDC_INIT_CTX_STARTUP, pstMsCapInfo);

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* 直接写8214 nv项*/
        TAF_MMA_WritePlmnSelectionModeNvim(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

        TAF_MMA_SetPlmnSelectionMode(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

        /* 直接上报结果 */
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_NO_ERROR);
        return STA_SUCCESS;
    }

    /* svlte nv关闭上报error */
    TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_PHONE_MSG_UNMATCH);
    return STA_ERROR;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_RcvPlmnSelectionReq_PowerOff
 功能描述  : MMA关机状态下收到cops的处理
 输入参数  : stCtrl - MODULE OPID
             stPlmnId - 指定的PLMN
             ucAccessMode - 指定的接入模式
             ucReselMode - 指定PLMN失败后的重选模式
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月04日
    作    者   : z00161729
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_RcvPlmnSelectionReq_PowerOff(
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnUserSelMsg,
    TAF_PLMN_ID_STRU                    stPlmnId,
    TAF_PH_RA_MODE                      ucAccessMode,
    VOS_UINT8                           ucReselMode
)
{
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMsCapInfo = TAF_SDC_GetMsCapInfo();
    TAF_SDC_InitSvlteSupportFlag(TAF_SDC_INIT_CTX_STARTUP, pstMsCapInfo);

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        (VOS_VOID)TAF_MMA_SndMsccPlmnSpecialReq((MMA_MSCC_PLMN_ID_STRU *)&stPlmnId, ucAccessMode);
        g_StatusContext.ulCurOpId = pstPlmnUserSelMsg->stCtrl.ucOpId;
        g_StatusContext.StaPlmnId.Mcc = stPlmnId.Mcc;
        g_StatusContext.StaPlmnId.Mnc = stPlmnId.Mnc;

        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF, TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_RESEL_SET_CNF_LEN);

        /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_SPEC_SEL_REQ类型结构正在被使用 */
        if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ))
        {
            /* 直接回复SEL设置失败 */
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_ERROR);
            return VOS_TRUE;
        }

        /* 找不到未被使用的，回复失败 */
        if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
        {
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_ERROR);
            return VOS_TRUE;
        }

        /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
        TAF_MMA_SetOperCtx(pstPlmnUserSelMsg->stCtrl,
                           TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, ucCtxIndex);

        return STA_SUCCESS;
    }

    /* svlte nv关闭上报error */
    TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_ERROR);

    return STA_ERROR;

}

/* 移到TafMmaComFun.c中 */


/*****************************************************************************
 函 数 名  : TAF_MMA_NotifySrvInfoToSpm
 功能描述  : 将服务状态信息通知到SPM模块
 输入参数  : enCnDomainId          --服务状态域信息
             enServiceStatus       --服务状态
             enOldPsServiceStatus  --旧的PS服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_NotifySrvInfoToSpm(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32          enCnDomainId,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enOldPsServiceStatus
)
{

#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE  == TAF_SDC_GetImsSupportFlag())
    {
        /* PS服务状态发生变化通知IMSA或SPM模块 */
        if (((NAS_MSCC_PIF_SRVDOMAIN_PS    == enCnDomainId)
          || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId))
         && (enOldPsServiceStatus != enServiceStatus))
        {
            /* 通知SPM服务状态变更，触发SPM处理缓存的消息，消息中不带服务域和服务状态，由SPM取SDC全局变量中的 */
            TAF_MMA_SndSpmServiceStatusChangeNotify();
        }
    }
#endif

    return;
}



/*lint -restore */


/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportRegStatus_ServiceStatusInd
 功能描述  : 收到服务状态时，是否需要上报注册状态
 输入参数  : 旧的系统模式
             旧的系统子模式
             旧的位置信息
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月15日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2015年06月10日
    作    者   : w00281933
    修改内容   : 新增函数 Service_State_Optimize_PhaseII
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedReportRegStatus_ServiceStatusInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldAppSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldAppSysSubMode,
    TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstOldPlmnInfo
)
{

    TAF_SDC_SYS_INFO_STRU              *pstCurCampInfo = VOS_NULL_PTR;

    pstCurCampInfo = TAF_SDC_GetSysInfo();

    /*延时定时器运行期间,不要上报*/
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
    {
        return VOS_FALSE;
    }

    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetServiceStatus())
    {
        return VOS_FALSE;
    }

    if (enOldAppSysSubMode != (TAF_SDC_GetSysSubMode()))
    {
        return VOS_TRUE;
    }

    /* CREG/CGREG上报类型为2时，包含lac,cellid,rat，因此这三个参数或者PLMN变化时，需要上报 */
    /* rat是否变化 */
    if (enOldAppSysMode != (TAF_SDC_GetSysMode()))
    {
        return VOS_TRUE;
    }

    /* PLMN是否变化 */
    if ( (pstOldPlmnInfo->stServicePlmnId.ulMcc) != (pstCurCampInfo->st3gppSysInfo.stPlmnId.ulMcc)
      || (pstOldPlmnInfo->stServicePlmnId.ulMnc) != (pstCurCampInfo->st3gppSysInfo.stPlmnId.ulMnc) )
    {
        return VOS_TRUE;
    }

    /* lac是否变化 */
    if ((pstOldPlmnInfo->usServiceLac) != (pstCurCampInfo->st3gppSysInfo.usLac))
    {
        return VOS_TRUE;
    }

    /* rac是否变化 */
    if ((pstOldPlmnInfo->ucServiceRac) != (pstCurCampInfo->st3gppSysInfo.ucRac))
    {
        return VOS_TRUE;
    }

    /* cellid是否变化 */
    if ((pstOldPlmnInfo->ulServiceCellId) != (pstCurCampInfo->st3gppSysInfo.ulCellId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportRegState_DelayRptTimerRun
 功能描述  : 延时定时器运行期间，是否需要上报注册状态和服务状态保持一致
 输入参数  : enCnDomainId             -- 服务域
             enRegState               -- 域注册抓过那天
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月11日
    作    者   : w00281933
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedReportRegState_DelayRptTimerRun(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8  enAppCsSrvSta;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8  enAppPsSrvSta;
    TAF_SDC_REG_STATUS_ENUM_UINT8      enCsRegState;
    TAF_SDC_REG_STATUS_ENUM_UINT8      enPsRegState;

    enAppCsSrvSta   = TAF_SDC_GetAppCsServiceStatus();
    enAppPsSrvSta   = TAF_SDC_GetAppPsServiceStatus();

    /*获取内部保存的注册状态信息*/
    enCsRegState = TAF_SDC_GetCsRegStatus();
    enPsRegState = TAF_SDC_GetPsRegStatus();

    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enRegState)
     || (TAF_SDC_REG_REGISTERED_ROAM         == enRegState))
    {
        return VOS_TRUE;
    }

    /*延时定时器运行时,内部保存的注册状态都是非正常注册,不能上报
      否则会导致上层立即显示无服务*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK  != enPsRegState)
     && (TAF_SDC_REG_REGISTERED_ROAM          != enPsRegState)
     && (TAF_SDC_REG_REGISTERED_HOME_NETWORK  != enCsRegState)
     && (TAF_SDC_REG_REGISTERED_ROAM          != enCsRegState))
    {
        return VOS_FALSE;
    }

    /*保持上报的注册状态和上报的服务状态一直*/
    if ((NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enAppCsSrvSta))
    {
        return VOS_TRUE;
    }
    else if ((NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
          && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enAppPsSrvSta))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsNeedReportRegStatus_RegStatusInd
 功能描述  : 收到注册状态时，是否需要上报注册状态
 输入参数  : 服务域，旧的注册状态，新的注册状态
 输出参数  : 无
 返 回 值  : VOS_TRUE:  需要上报
             VOS_FALSE: 不需要上报
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月15日
    作    者   : s00217060
    修改内容   : 新增函数
  2.日    期   : 2015年04月11日
    作    者   : w00281933
    修改内容   : 服务状态优化Phase II
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedReportRegStatus_RegStatusInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
)
{
    VOS_UINT8                           ucIsSpecDomainUsimInvalid;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enDelayTimerStatus;

    enDelayTimerStatus    = TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);

    /*获取指定域的卡状态是否有效*/
    ucIsSpecDomainUsimInvalid = TAF_SDC_IsSpecDomainUsimStatusInvalid(enCnDomainId);

    /* 判断当前注册状态与APP中保存的不相同需上报 */
    if (VOS_FALSE == TAF_SDC_IsAppSepcDomainRegStaChg((TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8)enCnDomainId,enRegState))
    {
        return VOS_FALSE;
    }

    /*normal 需要上报*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enRegState)
     || (TAF_SDC_REG_REGISTERED_ROAM == enRegState))
    {
        return VOS_TRUE;
    }

    /*指定域卡状态无效，需要上报*/
    if (VOS_TRUE == ucIsSpecDomainUsimInvalid)
    {
        return VOS_TRUE;
    }

    if (TAF_MMA_TIMER_STATUS_RUNING == enDelayTimerStatus)
    {
        if (VOS_FALSE == TAF_MMA_IsNeedReportRegState_DelayRptTimerRun(enCnDomainId,enRegState))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_BASTET)
/*****************************************************************************
 函 数 名  : TAF_MMA_ProcBastetServiceStatusInd
 功能描述  : 收到MMC的服务状态上报时，处理是否通知Bastet服务状态
 输入参数  : 旧的CS域服务状态和旧的PS域服务状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月15日
    作    者   : s00217060
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcBastetServiceStatusInd(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enOldCsSrvSta,
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enOldPsSrvSta
)
{

    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enBstNewCsSrvSta;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enBstNewPsSrvSta;

    enBstNewCsSrvSta   =  TAF_SDC_GetCsServiceStatus();
    enBstNewPsSrvSta   =  TAF_SDC_GetPsServiceStatus();

    if(VOS_TRUE == TAF_SDC_GetBastetSupportFlag())
    {
        /* cs域服务状态变化或ps域服务状态变化，通知BASTET */
        if ((enOldCsSrvSta != enBstNewCsSrvSta)
          ||(enOldPsSrvSta != enBstNewPsSrvSta))
        {
            TAF_MMA_SndBastetServiceStatusInd();
        }
    }

    return;
}
#endif


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcAppServPlmnInfo_SysInfoInd
 功能描述  : 收到系统消息时，对AppServPlmnInfo更新的处理
 输入参数  : MMC_MMA_SYS_INFO_IND_STRU          *pstSysInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcAppServPlmnInfo_SysInfoInd(
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstSysInfoInd
)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppSrvState;

    enAppSrvState   = TAF_SDC_GetAppServiceStatus();

    switch(pstSysInfoInd->enCurNetWork)
    {
        case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
        case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
        case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:

            /* 如果APP里的服务状态为limited service，也更新到驻留信息到APP里，
               因为limited service->limited service时MMC不上报服务状态和注册状态，可能导致小区信息未更新过来 */
            if ( (TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE          == enAppSrvState)
              || (TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE == enAppSrvState) )
            {
                TAF_MMA_UpdateAppServPlmnInfo();
            }

            break;

        default:

            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcAppServPlmnInfo_SysInfoInd: enCurNetWork ERROR");

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_ProcServiceStatusReport_ServiceStatusInd
 功能描述  : 收到MMC的服务状态时，对服务状态是否需要上报给AP的处理
 输入参数  : MMC_MMA_SERVICE_STATUS_IND_STRU    *pstServiceStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcServiceStatusReport_ServiceStatusInd(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    VOS_UINT32                          ucIsNeedRptSrvSta;
    VOS_UINT32                          ucIsNeedDelayRptSrvSta;

    ucIsNeedRptSrvSta      = VOS_FALSE;
    ucIsNeedDelayRptSrvSta = VOS_FALSE;

    /*判断是否需要上报服务状态*/
    ucIsNeedRptSrvSta = TAF_MMA_IsNeedReportServiceStatus(pstServiceStatus->enCnDomainId, pstServiceStatus->enServiceStatus);

    if (VOS_TRUE == ucIsNeedRptSrvSta)
    {
        /*需要延时上报服务状态*/
        ucIsNeedDelayRptSrvSta = TAF_MMA_IsNeedDelayReportServiceStatus(pstServiceStatus->enCnDomainId, pstServiceStatus->enServiceStatus);

        if (VOS_TRUE == ucIsNeedDelayRptSrvSta)
        {
            /* 处理服务状态或注册状态延迟上报 */
            TAF_MMA_ProcDelayReport();
        }
        else
        {
            /* 处理服务状态立即上报 */
            TAF_MMA_ProcServiceStatusImmediatelyReport(pstServiceStatus);
        }
    }
    else
    {
        /* 处理服务状态不上报 */
        TAF_MMA_ProcServiceStatusNotReport(pstServiceStatus);
    }


    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcRegStatusReport_ServiceStatusInd
 功能描述  : 收到MMC的服务状态时，对注册状态是否需要上报给AP的处理
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8         enOldAppSysMode
             TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldAppSysSubMode
             TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstOldPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ProcRegStatusReport_ServiceStatusInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldAppSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldAppSysSubMode,
    TAF_SDC_SERVICED_PLMN_INFO_STRU    *pstOldPlmnInfo
)
{
    TAF_SDC_CEREG_TYPE_ENUM_UINT8       enCeregType;

    /* 收到注册状态时，APP里保存的驻留信息还未更新，无法判断小区是否发生变化；
       所以在收到服务状态时，如果小区发生变化，需要补报一次AT CREG/CGREG */
    if (VOS_TRUE == TAF_MMA_IsNeedReportRegStatus_ServiceStatusInd(enOldAppSysMode, enOldAppSysSubMode, pstOldPlmnInfo))
    {
        /* CREG为2时 */
        if (TAF_SDC_CREG_TYPE_ENTIRE == TAF_SDC_GetCregType())
        {
            TAF_MMA_SndAtRegStatus(NAS_MSCC_PIF_SRVDOMAIN_CS, TAF_SDC_GetCsRegStatus());
        }

        /* CGREG或CEREG为2 */
        enCeregType = TAF_SDC_GetCeregType();
        if ((TAF_SDC_CGREG_TYPE_ENTIRE == TAF_SDC_GetCgregType())
         || (TAF_SDC_CEREG_TYPE_ENTIRE == enCeregType))
         {
            TAF_MMA_SndAtRegStatus(NAS_MSCC_PIF_SRVDOMAIN_PS, TAF_SDC_GetPsRegStatus());
         }

        /*同步更新驻留信息到APPINFO*/
        TAF_MMA_UpdateAppRegStatusInfo(NAS_MSCC_PIF_SRVDOMAIN_CS_PS);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_ProcRssiReport_ServiceStatusInd
 功能描述  : 收到MMC上报状态时，对信号强度是否需要上报给AP的处理
 输入参数  : TAF_SDC_SYS_MODE_ENUM_UINT8         enOldSysMode
             TAF_SDC_SYS_MODE_ENUM_UINT8         enNewSysMode
             TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enOldSrvSta
             TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNewSrvSta
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月17日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年9月17日
    作    者   : s00217060
    修改内容   : DTS2015091409113修改函数入参
  3.日    期   : 2015年10月8日
    作    者   : l00324781
    修改内容   : Iteration 18 ,CL模服务状态显示优化
*****************************************************************************/
VOS_VOID TAF_MMA_ProcRssiReport_ServiceStatusInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldSysMode
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNetworkInfo   = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNetworkInfo   = VOS_NULL_PTR;

    pstCurNetworkInfo   = TAF_SDC_GetCurrNetworkInfo();
    pstAppNetworkInfo   = TAF_SDC_GetAppNetworkInfo();

    /* 接入技术由A->B,B接入层已经上报过信号强度，并且APP中显示的已经是B的注册状态或服务状态，补报一次B下的信号强度 */
    if ((pstCurNetworkInfo->stSigQuaInfo.st3GppRssiInfo.enRat == pstAppNetworkInfo->stAppSysInfo.enSysMode)
     && (pstCurNetworkInfo->stSigQuaInfo.st3GppRssiInfo.enRat != enOldSysMode))
    {
        TAF_MMA_SndAtRssiInd();
    }

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

