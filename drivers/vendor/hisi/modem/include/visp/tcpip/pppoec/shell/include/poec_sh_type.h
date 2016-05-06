/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                          poec_sh_type.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块Shell部分数据结构定义
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME               DESCRIPTION
 *  2003-01-11      liuhui             Create file
 *  2005-09-15      t45114             Modify 
 *  2006-03-30      liai               Adjust for D00660
 *  2006/04/21      liai               Adjust for D00865
 *  2006-05-10   luyao(60000758)       为支持ARM CPU字节对齐特性，修改结构。
 *   
 ************************************************************************/

#ifndef  _POEC_SH_TYPE_H_
#define  _POEC_SH_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif



/*热插拔时所需下发的全局配置*/
typedef struct tagPoeClientHotInsertSlotMsg
{
    ULONG ulMsgType;        /*热插拔的消息类型*/

}POE_CLIENT_HOT_INSERT_SLOT_MSG_S ; 


typedef struct tagPPPOE_CLIENT_RPC_RPL_DISPLAY
{
    UINTPTR  ulWaitListHandle;
    CHAR   szBuffer[PPPOE_CLIENT_DISPLAY_INFO_BLOCK_LEN + 1];  /* 留出一个'\0'结束符 */
    UCHAR  ucPadding[3]; 
}PPPOE_CLIENT_RPC_RPL_DISPLAY_S;

typedef PPPOE_CLIENT_RPC_RPL_DISPLAY_S PPPOE_CLIENT_DISPLAY_BLOCK_S;

typedef struct tagPPPOE_CLIENT_WAITLIST_PARAM
{
    UINTPTR ulHandle;            /* WAITLIST句柄 */
    UCHAR   ucGetNextType;        /* 搜索类型 */
    UCHAR   ucPadding[3];
    VOID    *pNode;                /* 输入输出 */
}PPPOE_CLIENT_WAITLIST_PARAM_S;

typedef struct tagPPPOE_CLIENT_RPC_ENQ_DISPLAY
{
    UCHAR   ucRpcFunc;          /* RPC功能ID */
    UCHAR   ucDisplayType;      /* Display类型，PPPOE_CLIENT_DISPLAY_TYPE_EN */
    UCHAR   ucPadding[2]; 
    UINTPTR ulWaitListHandle;   /* WaitList句柄 */
    ULONG   ulBundleNumber;     /* 接口IFNET索引 */    
    ULONG   ulExecID;           /* EXEC用户ID  */
    ULONG   ulLanguage;         /* 当前语言 */
}PPPOE_CLIENT_RPC_ENQ_DISPLAY_S;

typedef struct tagPPPOE_CLIENT_RPC_ENQ
{
    UCHAR   ucRpcFunc;          /* RPC功能ID */
    UCHAR   ucPadding[3];
    ULONG   ulData;             /* 长整形的使用者数据 */
}PPPOE_CLIENT_RPC_ENQ_S;


typedef struct tagPPPOE_CLIENT_RPC_RPL
{
    ULONG   ulData;             /* 用户自定义数据 */
}PPPOE_CLIENT_RPC_RPL_S;

typedef enum tagPPPOE_CLIENT_RPC_FUNC
{
    PPPOE_CLIENT_RPC_GET_DISPLAY_INFO = 1,  /* 取得display显示信息 */
    PPPOE_CLIENT_RPC_USER_BREAK_NOTIFY,     /* 用户中断显示时通知接口板释放waitlist */
    PPPOE_CLIENT_RPC_HOT_PLUG_NOTIFY,       /* 热插拔时通知接口板恢复配置数据 */
    PPPOE_CLIENT_RPC_CLEAR_INFO
}PPPOE_CLIENT_RPC_FUNC_E;


#ifdef __cplusplus
}
#endif

#endif


