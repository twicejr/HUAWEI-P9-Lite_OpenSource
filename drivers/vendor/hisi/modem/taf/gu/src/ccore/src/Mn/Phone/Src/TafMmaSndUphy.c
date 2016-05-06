/******************************************************************************

                  版权所有 (C), 2013-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndUphy.c
  版 本 号   : 初稿
  作    者   : l00198894
  生成日期   : 2015年6月15日
  最近修改   :
  功能描述   : MMA模块发送到UPHY的消息文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月15日
    作    者   : l00198894
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafMmaSndUphy.h"
#include "MmaUphyInterface.h"

#include "PsTypeDef.h"
#include "TafLog.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_UPHY_C

/*****************************************************************************
   2 全局变量定义和宏
****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_SndUphyPowerOnReq
 功能描述  : MMA通知UPHY开机请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndUphyPowerOnReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_ON_REQ_STRU         *pstPowerOn = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_ON_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPowerOn  = (MMA_UPHY_POWER_ON_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOn)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Alloc Msg Failed!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPowerOn + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPowerOn->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOn->usMsgID                 = ID_MMA_UPHY_POWER_ON_REQ;
    pstPowerOn->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOn))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOnReq: Snd Msg Failed!");
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndUphyPowerOffReq
 功能描述  : MMA通知UPHY关机请求
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月2日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndUphyPowerOffReq(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MMA_UPHY_POWER_OFF_REQ_STRU        *pstPowerOff = VOS_NULL_PTR;

    ulLenth     = sizeof(MMA_UPHY_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPowerOff  = (MMA_UPHY_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerOff)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Alloc Msg Failed!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPowerOff + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPowerOff->ulReceiverPid           = DSP_PID_STARTUP;
    pstPowerOff->usMsgID                 = ID_MMA_UPHY_POWER_OFF_REQ;
    pstPowerOff->enModemId               = VOS_GetModemIDFromPid(WUEPS_PID_MMA);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerOff))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndUphyPowerOffReq: Snd Msg Failed!");
    }

    return;

}





#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif







