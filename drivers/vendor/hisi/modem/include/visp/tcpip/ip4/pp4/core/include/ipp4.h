/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipp4.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2004-03-12
*        Author: chenshuanglong(28510)
*   Description: PP4模块的组件接口相关变量声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-03-12   chenshuanglong(28510)   Create
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_PP4_H_
#define _I_PP4_H_

extern IIF_IPV4_IP_PP4_ComIntFUN g_IComInt_IP_PP4_FUN;
extern IIF_IPV4_IP_PP4_ComIntCFG g_IComInt_IP_PP4_CFG;
extern IIF_IPV4_IP_PP4_ComIntSSA g_IComInt_IP_PP4_SSA;

/* For implement of QuerfyInstance() */
typedef struct tagIP_PP4_INT_OBJ_S
{
    IIF_IPV4_IP_PP4_ComIntFUN  *pComIntFUN;
    IIF_IPV4_IP_PP4_ComIntCFG  *pComIntIFG;
    IIF_IPV4_IP_PP4_ComIntSSA  *pComIntSSA;
}IP_PP4_INT_OBJ_S;

extern IP_PP4_INT_OBJ_S g_stIP_PP4_INT_OBJ;

extern IComponentFactory m_IPPp4Factory;

extern ComponentInfo m_CompIPPp4Info;

#endif  /*  _I_PP4_H_  */


#ifdef  __cplusplus
}
#endif

