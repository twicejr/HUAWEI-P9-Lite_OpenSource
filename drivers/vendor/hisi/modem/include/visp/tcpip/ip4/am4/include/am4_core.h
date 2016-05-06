/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_core.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: AM4中core的函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _AM4_CORE_H_
#define _AM4_CORE_H_


/* 地址标志位的宏，标识不同类型的地址。在地址的ipif_ulAddrFlag中保存
 * 地址类型的标志
 */
#define IP_NO              0    /* 未配置地址 */ 
#define IP_OWN          0x01    /* 有自己的主地址 */
#define IP_NEGOTIATE    0x02    /* 主地址由协商得来 */
#define IP_BORROW       0x04    /* 主地址是借用的 */
#define IP_LEND         0x08    /* 借给别人地址 */
#define IP_LENDANDOWN   (IP_OWN|IP_LEND)
#define IP_LENDANDNEGO  (IP_LEND|IP_NEGOTIATE)
#define IP_DHCP         0x10    /* 接口配置DHCP获得的地址 */ 
#define IP_NODHCPFLAG   0x10    /* DHCP地址的优先级低于接口地址方式使能DHCP的标志位 */ 
#define IP_NODHCP       0x20    /* 接口不配置DHCP获得的地址 */ 


/* Start of 以太网的公共函数返回值 */
#define IP_ARP_IPIFNET_ERR      1
#define IP_ARP_ONESEFIP         14
#define IP_ARP_DSTIP_NOTSAMENET 15
#define IP_ARP_SRCIP_BROADCAST  16
#define IP_ARP_INVALIDADDR      17
#define IP_ARP_DSTIPISNET       18
#define IP_ARP_SRCIP_NOTSAMENET 19
#define IP_ARP_DSTADD_NOTMY     20
/* End of 以太网的公共函数返回值 */

typedef ULONG(*AM4_SHELL_HA_CALLBACK_FUNC_PTR)();


typedef struct tagIP_AM4_MOD_INFO
{
    ULONG ulModID;
    ULONG ulModSubId;
    ULONG ulAddrCmdRpcChannel;
    ULONG ulVlinkFlag ;
    ULONG ulDhcpAddrCfgMode;
} IP_AM4_MOD_INFO_S; 


typedef struct tagAM4_SHELL_HA_CALLBACK_FUNC_SET
{
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetBoardType;
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetMainBoardId;
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetSlaveBoardId;
} AM4_SHELL_HA_CALLBACK_FUNC_SET_S;


typedef struct tagAm4ICCallbackSet
{
    ULONG (*pfIP_AM4_SH_SendDebugInfoToIC)(CHAR *szBuf);
}IP_AM4_IC_CALLBACK_SET_S;

/*数据结构IP_AM4_IF_ADDR_S已经挪到am4_api.h, by z00104207*/

/*枚举enum_IP_AM4_ERR已经挪到am4_api.h, by z00104207*/

#endif  /* _AM4_CORE_H_  */


#ifdef  __cplusplus
}
#endif
