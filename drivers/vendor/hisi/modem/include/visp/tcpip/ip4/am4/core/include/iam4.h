/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                iam4.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: 声明AM4中的接口
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _I_AM4_H_
#define _I_AM4_H_

/* vtable variables */
extern IIF_IPV4_IP_AM4_ComIntFUN g_IComInt_IP_AM4_FUN;
extern IIF_IPV4_IP_AM4_ComIntCFG g_IComInt_IP_AM4_CFG;
extern IIF_IPV4_IP_AM4_ComIntSSA g_IComInt_IP_AM4_SSA;


/* For implement of QuerfyInstance() */
typedef struct tagIP_AM4_INT_OBJ_S
{
    IIF_IPV4_IP_AM4_ComIntFUN  *pComIntFUN;
    IIF_IPV4_IP_AM4_ComIntCFG  *pComIntCFG;
    IIF_IPV4_IP_AM4_ComIntSSA  *pComIntSSA;
}IP_AM4_INT_OBJ_S;

extern IP_AM4_INT_OBJ_S g_stIP_AM4_INT_OBJ;

extern IComponentFactory m_IPAm4Factory;

/* component info for am4 */
extern ComponentInfo m_CompIPAm4Info;


#endif  /*  _I_AM4_H_  */


#ifdef  __cplusplus
}
#endif

