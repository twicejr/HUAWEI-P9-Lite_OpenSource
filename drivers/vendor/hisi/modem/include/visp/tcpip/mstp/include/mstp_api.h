/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mstp_api.h
*
*  Project Code: V100R007
*   Module Name:   
*  Date Created: 2008-10-22
*        Author: lianglong111779
*   Description: mstp cbb对外接口
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
#ifndef _MSTP_API_H_
#define _MSTP_API_H_


#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/mstp/include/mstp_cbb_api.h"

/*******************************************************************************
*    Func Name: MSTP_PPI_HookRegister
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: MSTP PPI钩子注册函数
*        Input: MSTP_PPI_HOOK_FUNC pfMSTPPpiHook:函数指针
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_HookRegister(MSTP_PPI_HOOK_FUNC pfMSTPPpiHook);

/*******************************************************************************
*    Func Name: MSTP_PPI_SetDebugSwitch
* Date Created: 2008-10-22
*       Author: zhangchi(00142640)
*  Description: 设置MSTP PPI调试开关
*        Input: ULONG ulSwitch:开关,1打开,0关闭
*       Output: 无
*       Return: 成功返回MSTP_OK，其他返回错误码 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi(00142640)         Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_SetDebugSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: MSTP_PPI_Count_Get
* Date Created: 2008-10-22
*       Author: zhangchi(00142640)
*  Description: 获取MSTP PPI统计
*        Input: MSTP_PPI_COUNT_S *pstCount:PPI下发次数指针
*       Output: 
*       Return: 成功返回MSTP_OK，其他返回错误码 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi(00142640)        Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_Count_Get(MSTP_PPI_COUNT_S *pstCount);

/*******************************************************************************
*    Func Name: MSTP_PPI_ShowCount
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: 显示MSTP PPI下发统计信息
*        Input: VOID
*       Output: 无
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID MSTP_PPI_ShowCount(VOID);

/*******************************************************************************
*    Func Name: MSTP_PPI_Count_Reset
* Date Created: 2008-07-29
*       Author: wuhailan
*  Description: 清除MSTP PPI下发统计信息
*        Input: VOID
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_Count_Reset(VOID);

/*******************************************************************************
*    Func Name: MSTP_PPI_ComputeUpdateCost
* Date Created: 2008-12-09
*       Author: zhangchi(00142640)
*  Description: 使能计算MSTP PPI下发时延开关
*        Input: ULONG ulSetYes:使能开关:1使能,0去使能
*       Output: 无
*       Return: 成功MSTP_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-09   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG MSTP_PPI_ComputeUpdateCost(ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_PPI_ShowUpdateCost
* Date Created: 2008-12-10
*       Author: zhangchi(00142640)
*  Description: 显示PPI下发时延信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID MSTP_PPI_ShowUpdateCost(VOID);

#ifdef  __cplusplus
}
#endif

#endif

