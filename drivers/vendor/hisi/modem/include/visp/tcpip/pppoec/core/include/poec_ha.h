/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poec_ha.h
*
*  Project Code: VISP V100R006
*   Module Name: POEC  
*  Date Created: 2006-12-13
*        Author: sunmo(44939)
*   Description: POEC模块的HA头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-12-13  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _POEC_HA_H_
#define _POEC_HA_H_

#ifdef __cplusplus
extern "C"{
#endif

#define POEC_HA_OPER_SETBUNDLE 1
#define POEC_HA_OPER_DELBUNDLE 0

/* Added by Sunmo(44939) for A82D12574 */
#define POEC_HA_OPER_NEGUP   0
#define POEC_HA_OPER_NEGDOWN 1

/* PPPoE模块备份消息类型 */
enum enumPoecMsgType
{
    POEC_BAK_BUNDLE,
    POEC_BAK_SESSION,
    POEC_BAK_SET_BUNDLE,
    POEC_BAK_CREATE_SESSION,
    POEC_BAK_MOVE_SESSION,
    POEC_BAK_NO_SESSION,
    POEC_BAK_CHANGE_SESSION_STATE
};

/*每次批备份的Session控制块个数*/
#define POEC_BAK_MAXSESSION_ITEM     50
/* PPPoE模块HA备份消息头长度 */
#define POEC_BAK_HEAD_LEN            sizeof(POEC_BAK_S) + sizeof (HAMSGHEADER_S)
/* 备份g_ulDialerBundleNumber数组的消息总长度 */
#define POEC_BAK_BUNDLE_MSG_LEN      1280

/* PPPoE模块HA调试开关 */
extern ULONG g_ulPoecHaDebug;
/* PPPoE模块HA详细内容调试开关 */
extern ULONG g_ulPoecHaVerboseDebug;

/* PPPoE模块HA消息头 */
typedef struct tagPOEC_BAK
{
    USHORT   usMsgType;      /* 消息类型 */
    USHORT   usBakItems;     /* 备份项个数 */
}POEC_BAK_S;

/* PPPoE模块Session控制块的备份消息结构 */
typedef struct tagPOEC_BAK_SESSION
{
    UCHAR szOurMacAddr[PPPOE_MAC_LEN];   /* Client physical地址 */
    UCHAR szHisMacAddr[PPPOE_MAC_LEN];   /* Server physical地址 */
    ULONG ulEthIfIndex;                  /* 对应以太网接口索引 */
    ULONG ulVAIfIndex;                   /* 对应virtual access接口索引 */
    ULONG ulDialerIfIndex;               /* 对应的dialer接口索引 */
    USHORT usBundleNumber;               /* 对应的dialer口bundle number */
    USHORT usSessionId;                  /* 本Session的ID */
    UCHAR ucSessionState;                /* PPPoE Client Session所处的阶段 */
    UCHAR ucPadding[3];                  /* 保留字段 */
}POEC_BAK_SESSION_S;

/* PPPoE模块设置/删除Bundle Number实时备份消息结构 */
typedef struct tagPOEC_BAK_REAL_BUNDLE
{
    ULONG ulBundleNumber;
    ULONG ulDialerIfIndex;
}POEC_BAK_REAL_BUNDLE_S;

/* PPPoE模块Session的Discovery阶段状态变迁实时备份消息结构 */
typedef struct tagPOEC_BAK_REAL_CHANGESTATE
{
    ULONG ulBundleNumber;
}POEC_BAK_REAL_CHANGESTATE_S;

/* PPPoE模块删除Session实时备份消息结构 */
typedef struct tagPOEC_BAK_REAL_NO_SESSION
{
    ULONG ulBundleNumber;
    ULONG ulEthIfIndex;
}POEC_BAK_REAL_NO_SESSION_S;


/* HA函数定义 */
ULONG POEC_HA_BatchBundle(VOID);
ULONG POEC_HA_BatchSession(VOID);
ULONG POEC_HA_BatchBackup(VOID);
ULONG POEC_HA_Input (UCHAR * pBuf, ULONG ulMsgLen);
ULONG POEC_HA_BundleInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_SessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_SetBundleInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_CreateSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_MoveSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_NoSessionInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG POEC_HA_Smooth(VOID);
ULONG TCPIP_HA_SetPoecDbg (ULONG ulDbg);
ULONG POEC_HA_SessionStateInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG TCPIP_HA_GetPoecDbg(ULONG *pulRet);
VOID POEC_HA_DebugOutput(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
ULONG POEC_HA_SetPoecVerboseDbg (ULONG ulDbg);
ULONG POEC_HA_GetPoecVerboseDbg(ULONG *pulRet);
ULONG POEC_HA_Clean(VOID);
/* End of HA函数定义 */

extern VOID VOS_T_Delay(ULONG ulMillisecond);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _POEC_HA_H_ */

