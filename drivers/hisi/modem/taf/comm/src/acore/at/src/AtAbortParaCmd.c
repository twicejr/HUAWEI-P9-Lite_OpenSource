

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_ABORTPARACMD_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 函 数 名  : AT_AbortCsgIdSearchPara
 功能描述  : 打断csg列表搜网处理函数
 输入参数  : ucIndex - AT端口的index
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月6日
    作    者   : z00161729
    修改内容   : 支持LTE CSG功能新增
*****************************************************************************/
VOS_UINT32 AT_AbortCsgIdSearchPara(
    VOS_UINT8                           ucIndex
)
{
    /* 当前只能处理列表搜的打断, 其它命令则不进行打断操作 */
    if ( AT_CMD_CSG_LIST_SEARCH == gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        /* AT向MMA发送打断列表搜的请求 */
        if (VOS_TRUE == TAF_MMA_AbortCsgListSearchReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
        {
            /* 停止csg列表搜AT的保护定时器 */
            AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);

            /* 更新当前操作类型 */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ABORT_CSG_LIST_SEARCH;

            return AT_WAIT_ASYNC_RETURN;
        }

    }

    return AT_FAILURE;
}
#endif


/*****************************************************************************
 函 数 名  : At_AbortCopsPara
 功能描述  : COPS命令的打断处理函数
 输入参数  : ucIndex: AT端口的index
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月19日
    作    者   : l00171473
    修改内容   : V7R1C50_At_Abort, 打断COPS命令的处理函数
*****************************************************************************/
VOS_UINT32 At_AbortCopsPara(
    VOS_UINT8                           ucIndex
)
{
    /* 当前只能处理列表搜的打断, 其它命令则不进行打断操作 */
    if ( AT_CMD_COPS_TEST == gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        /* AT向MMA发送打断列表搜的请求 */
        if (VOS_TRUE == TAF_MMA_AbortPlmnListReq(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
        {
            /* 停止列表搜AT的保护定时器 */
            AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);

            /* 更新当前操作类型 */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_ABORT_PLMN_LIST;

            return AT_WAIT_ASYNC_RETURN;
        }
        else
        {
            return AT_FAILURE;
        }
    }
    else
    {
        return AT_FAILURE;
    }

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

