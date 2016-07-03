


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







