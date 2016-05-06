#ifndef NSR_API_INCLUDED
#define NSR_API_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "tcpip/nsr/include/nsr_api_def.h"

/*******************************************************************************
*    Func Name: NSR_SetNSRCapability
* Date Created: 2013-09-27
*       Author: guojianjun178934
*      Purpose: NSR使能/去使能开关
*  Description: 
*        Input: UCHAR  ucNSRCapability: NSR_CAPABILITY_ENABLE       NSR使能
*                                       NSR_CAPABILITY_DISENABLE    NSR去使能
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-27   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_SetNSRCapability(UCHAR  ucNSRCapability);
/*******************************************************************************
*    Func Name: NSR_RegFunSendBackupMsgHook
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: 注册主板发送备份数据钩子函数
*  Description: 
*        Input: NSR_SEND_BACKUP_MSG_FUNC pfFunc: 发送备份数据钩子函数
*                                       
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_SEND_BACKUP_MSG_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunSendBackupMsgHook(NSR_SEND_BACKUP_MSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: NSR_RegFunSendControlMsgHook
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: 注册通知产品操作处理结果钩子函数(主备板都可以调用)
*  Description: 
*        Input: NSR_SEND_BACKUP_MSG_FUNC pfFunc: 通知产品操作处理结果钩子函数
*                                       
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_SEND_CONTROL_MSG_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunSendControlMsgHook(NSR_SEND_CONTROL_MSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: NSR_ReceiveBackupMsg
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: 备板接收备份消息处理函数
*  Description: 
*        Input: UCHAR *pucBuf:  备份消息指针
*               ULONG ulMsgLen: 消息长度                       
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_ReceiveBackupMsg(UCHAR *pucBuf, ULONG ulMsgLen);
/*******************************************************************************
*    Func Name: NSR_ReceiveControlMsg
* Date Created: 2012-11-28
*       Author: guojianjun178934
*      Purpose: 主/备板接收产品发送的NSR控制类消息
*  Description: 
*        Input: NSR_CONTROL_MSG *pstNSRControlMsg:  控制消息指针                     
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-28   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_ReceiveControlMsg(NSR_CONTROL_MSG *pstNSRControlMsg);
/*******************************************************************************
*    Func Name: NSR_Get_NSR_Common_Info
* Date Created: 2013-10-15
*       Author: guojianjun178934
*      Purpose: 获取NSR公共模块信息
*  Description: 
*        Input:                     
*       Output: NSR_COMMON_INFO_SHOW *pstShow: NSR公共模块信息
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-15   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_Get_NSR_Common_Info(NSR_COMMON_INFO_SHOW *pstShow);
/*******************************************************************************
*    Func Name: NSR_RegFunGetNSRBaseInfoHook
* Date Created: 2013-10-18
*       Author: guojianjun178934
*      Purpose: 产品NSR状态获取注册构造函数
*  Description: 
*        Input: NSR_GET_NSR_BASE_INFO_FUNC pfFunc:  NSR状态获取函数                 
*       Output: 
*       Return: 成功：NSR_OK
*               失败：错误码
*      Caution: 
*        Since: V300R002C00
*    Reference: NSR_GET_NSR_BASE_INFO_FUNC
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-18   guojianjun178934        Create
*
*******************************************************************************/
ULONG NSR_RegFunGetNSRBaseInfoHook(NSR_GET_NSR_BASE_INFO_FUNC pfFunc);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
