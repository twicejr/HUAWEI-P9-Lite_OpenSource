/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_sh_cfg.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: AM4中shell的配置函数声明
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
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_SH_CFG_H_
#define _AM4_SH_CFG_H_


#define IP_AM4_EXEC_INFO_INDEX (g_ulAM4ErrInfoIndex)


#define IP_AM4_ENABLE_CLI           1
#define IP_AM4_DISABLE_CLI          0


#define IP_AM4_RPC_CHANNEL_ID_ADDRCMD   (MID_COMP_AM4|0x0001)
#define IP_AM4_RPC_CHANNEL_ID_CMD       (MID_COMP_AM4|0x0002)
#define IP_AM4_RPC_PlugInOut            (MID_COMP_AM4|0x0003)


#define IP_DEBUG_INFO             1


/* request type to IO board. when main board processed a command, and needs
 * IO board to do some process, it will use RPC. these defines are RPC request
 * command types.
 */
#define IP_AM4_SHOW_IPIF      1
#define IP_AM4_SHOW_IPIFBRIEF 2
#define IP_AM4_SET_DEBUG      3

#define IP_PHYSTATE_MAXLENGTH   21   /* "administratively down"字符串的最大bit个数为21 */
#define IP_PROSTATE_MAXLENGTH   12   /* "up(spoofing)"字符串的最大bit个数为12 */

/* show ip interface命令中，ip消息的最大长度 */
#define ENG_LENOFIPINFO_SHOWIN (MAXADDR_ON_ONEIF * 80 + 1000)
#define CHN_LENOFIPINFO_SHOWIN (MAXADDR_ON_ONEIF * 80 + 1000)

/* 同步D21代码  x36530  2004-9-17  */
/*add by pengjimei for 8070 IP特性移植项目*/
typedef struct tagIP_RPC_MSG
{
    ULONG      IpRpc_ulFuncId;
    ULONG      IpRpc_ulifindex;
    ULONG      ulIpCmdFlag; /* per-flow load balance */

}IP_RPC_MSG_S;

#define IP_CMD_DIRECT_BROADCAST      0x00000001
#define IP_CMD_VERIFY_SOURCE_ADDRESS 0x00000002
#define IP_CMD_CLEAR_DF_FLAG         0x00000004

ULONG IP_AM4_RegBuildRun();
ULONG IP_AM4_SH_RegCmdRPC();
ULONG IP_AM4_SH_RegConfigProc( VOID );
ULONG IP_AM4_SH_RegCmd();

#endif  /* end of _AM4_SH_CFG_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

