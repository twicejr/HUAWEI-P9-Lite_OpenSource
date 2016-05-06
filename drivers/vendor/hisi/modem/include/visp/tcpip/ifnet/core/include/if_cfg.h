/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_CFG.H  
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/03/20 
 *        Author: YuXiaoHan
 *   Description: Ifnet配置头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/03/20      YuXiaoHan       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2007/11/22      f54882          For SWID00244,删除函数IF_GetIfIndexbyName()申明
 *
 ************************************************************************/

/*
 * 请将这里的模块宏换成该头文件所属模块的模块宏。
 * 例如，对于链路层协议模块PPP的头文件ppp_var.h，应该改为：
 *
 *    #if( VRP_MODULE_LINK_PPP == VRP_YES )
 *
 * 引用该宏的目的是为了通过手工配置在编译时裁减VRP软件，请每个文件保留。
 * 所有的这些模块宏都由VRP3.0的配置管理员管理，在头文件vrpcfg.h中定义。
 */

#ifndef _IF_CFG_H_
#define _IF_CFG_H_
/*
 * 该宏的定义方式为："_" + "全部大写的文件名" + "_" + "H" + "_"
 * 例如，对于链路层协议模块PPP的头文件ppp_var.h，应该定义为：
 *
 *#ifndef _PPP_VAR_H_
 *#define _PPP_VAR_H_
 *
 * 定义该宏的目的在去除重复包含一个头文件的可能性
 */

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct tagIFGetVAInfo        /* For Get VA Info. */
{
    ULONG  ulLanguage;
    ULONG  ulVTNo;
    ULONG  ulVANo;
    CHAR   szUserName[40];
    ULONG ulCfgVTNo;
    ULONG ulCfgVANo;
    ULONG ulCfgIp;
    ULONG  ulInfoSize;
}IF_GetVAInfo_S;

/************************************************************************************
进行接口名称检查、帮助、补齐的钩子函数                                              *
                                                                                    *
函数作用:  设置查询条件，                                                           *
             并根据参数ulFunc转入相应的接口类型、编号、名称的检查帮助函数           *
函数返回值:  所转入的检查帮助函数的返回值(参见IF_CheckIfType、IF_HelpIfType等函数)  *
*************************************************************************************/
ULONG IF_HookForQuery(ULONG ulFunc, CHAR * szType , CHAR * szInput , ULONG pHelpVec) ;
/************************************************************************************/

ULONG IF_GetConfigMTU(IFNET_S* pIf);
ULONG IF_GetMTU(IFNET_S* pIf);
VOID IF_GetDefaultEthMac(UCHAR *szMac);

ULONG IF_VT_FindVA( IF_GetVAInfo_S *pVAInfo); 

ULONG IF_SetMTU(IFNET_S* , ULONG ulMTU ) ;
ULONG IF_SetVTMTU(IFNET_S* pIf, ULONG ulMTU);
ULONG IF_SetDescript(IFNET_S* pIf, CHAR * pDescript);
ULONG IF_SetKeepAliveValue( IFNET_S* pIf, ULONG ulValue );
ULONG IF_SetBandWidthValue(ULONG ulSlot, IFNET_S* pIf, ULONG ulValue);

VOID IF_SelectMtu(IFNET_S * , ULONG * , ULONG * ) ;

/*added by fujibin for simple name D18451*/
ULONG IF_GetSimpleName( CHAR *szIfName, CHAR *szSimpleName );


ULONG IF_GetIPSecSaEntryHead(ULONG ulIfIndex, VOID **ppstHeadTemp);
ULONG IF_SetIPSecSaEntryHead(ULONG  ulIfIndex, ULONG ulTdbEntryHead);
ULONG IF_GetPortType(IFNET_S * pIf, ULONG *pulPortType );
ULONG IF_GetPhyType(IFNET_S * pIf, ULONG *pulPhyType );
BOOL_T IF_IsValidIfIndex(ULONG ulIfIndex);
CHAR *IF_GetIfNamebyIndex(ULONG ulIfIndex);
ULONG IF_GetPortTypeByIndex(ULONG ulIfIndex);
ULONG IF_GetMTUByIndex(ULONG ulIfIndex);

#if (TCPIP_MODULE_MINI == VRP_YES)

ULONG IF_Addr_IsInvalidIP4Address(ULONG ulV4Addr);
ULONG IF_IsInvalidIP6Address(IN6ADDR_S  *pstIn6Addr,ULONG ulJudgeFlg);
ULONG IF_CheckAddrWithLocal(IN6ADDR_S  *pstIn6Addr,ULONG ulIfIndex);
ULONG IF_GetMatchIfIndex(ULONG *pulIndex);
ULONG IF_SelectSourceAddr(IN6ADDR_S *pstIp6DestAddr,IN6ADDR_S *pstSrcAddr, ULONG ulIfIndex);
ULONG IF_HaveAddrCheck(ULONG ulIfIndex,ULONG ulFlag);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _IF_CFG_H_ */

