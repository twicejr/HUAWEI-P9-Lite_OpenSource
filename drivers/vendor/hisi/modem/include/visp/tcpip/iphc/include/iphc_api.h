/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iphc_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name: IPHC api头文件  
*  Date Created: 2008-3-15
*        Author: y62007
*   Description: IPHC api头文件  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-15   y62007          Create the first version.
*
*******************************************************************************/
#ifndef _IPHC_API_H_
#define _IPHC_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

enum eIPHC_ERR_CODE
{
    IPHC_OK = 0,
    IPHC_ERR,
    IPHC_ERR_COM_NULL,        /* 组件为空 */
    IPHC_ERR_NULL_POINTER,    /* 输入指针为空 */
    IPHC_ERR_IFNET_NOEXIST,   /* 获取IFNET失败 */
    IPHC_ERR_PPPCB_NOEXIST,   /* PPP控制块不存在 */
    IPHC_ERR_CONTEXT_NOEXIST, /* IPHC CONTEXT不存在 */
    IPHC_ERR_NOTPPPTYPE       /* 非PPP接口 */ 
};

/*******************************************************************************
*    Func Name: TCPIP_DebugIPHCAll
*  Description: 打开IPHC组件所有调试开关。
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
LONG TCPIP_DebugIPHCAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugIPHCAll
*  Description: 关闭IPHC组件所有调试开关。
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
LONG TCPIP_NoDebugIPHCAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCNonTcpDebug
*  Description: 设置非TCP压缩类型调试开关
*        Input: ULONG ulSetYes: 1-开启，0-关闭
*       Output: O--成功
*             : 其它失败
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetIPHCNonTcpDebug(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCTcpDebug
*  Description: 设置TCP压缩类型调试开关
*        Input: ULONG ulSetYes: 1-开启，0-关闭
*       Output: 
*       Return: O--成功
*             : 其它失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    yebo(62007)      Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetIPHCTcpDebug(ULONG ulSetYes);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _IPHC_API_H_ */

