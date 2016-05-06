/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_func.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: 声明了AM4中的功能函数
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理 
*  2006-05-11   luyao(60000758)         为支持ARM CPU字节对齐特性，修改结构
*
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_FUNC_H_
#define _AM4_FUNC_H_

typedef struct tagIPAm4Addrmsg
{
    ULONG   ulIntfIndex;
    USHORT  usMsgType;
    UCHAR   ucPadding[2]; 
    ULONG   ulIpFlag;           /* 借用IP等标志，new in 3.0 */
    SOCKADDR_S  sLocalAddr;
    SOCKADDR_S  sNetMask;
    SOCKADDR_S  sPrimaryAddr;   /* 新的主地址, new in 3.0*/
}IP_AM4_ADDRMSG_S;

/*结构IP_ADDR_NOTIFY_MSG_S已经挪到am4_api.h*/

extern ULONG IP_AM4_SendMsgToRm(struct tagIPAm4Addrmsg* pstIPMsg);


#endif  /* end of _AM4_FUNC_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

