/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_fun.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunk模块的函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_NSR_H_
#define _TRUNK_NSR_H_

#ifdef __cplusplus
extern "C"{
#endif

#define TRUNK_NSR_STATE_MASTER              0x00100000
#define TRUNK_NSR_STATE_SLAVE               0x00200000
#define TRUNK_NSR_STATE_RESTORE             0x00400000
#define TRUNK_NSR_STATE_SMOOTH              0X00800000


/* TRUNK NSR 使能/去使能/去使能中 状态 */
#define TRUNK_NSR_DISABLE   0
#define TRUNK_NSR_ENABLE    1
#define TRUNK_NSR_DISABLING 2

#define g_pfTCPIP_PPI_NsrTrunk_Update  g_pfTrunkNsrPpiHook

/*统计类型*/
#define TRUNK_NSR_STAT_TIMEOUT                0x01  /* Trunk Nsr 超时 */
#define TRUNK_NSR_STAT_ADD_PORT               0x02  /* NSR过程中，用户添加成员端口数目*/
#define TRUNK_NSR_STAT_REMOVE_PORT            0x03  /* NSR过程中，用户移除成员端口数目*/
#define TRUNK_NSR_STAT_SUCCESS_RESUME_LINK    0x04  /* 恢复成功链路数量 */
#define TRUNK_NSR_STAT_RESUME_WRONG_INFO      0x05  /* 转发面恢复信息错误 */
#define TRUNK_NSR_STAT_RESUME_WRONG_MAC       0x06  /* 转发面恢复以太mac不一致 */
#define TRUNK_NSR_STAT_RESUME_LINK_NOT_EXIST  0x07  /* 没有从底层获取到链路信息 */
#define TRUNK_NSR_STAT_SUCCESS_SMOOTH_LINK    0x08  /* 平滑成的链路数量 */
#define TRUNK_NSR_STAT_FAIL_SMOOTH_LINK       0x09  /* 平滑失败链路数量 */
#define TRUNK_NSR_STAT_FAIL_SMOOTH_WRONG_MAC  0x0A  /* 因恢复的trunk的mac不是trunk任何一个成员端口的mac，平滑失败链路数量 */

/*trunk 某一条链路 nsr 过程失败原因*/
enum enTrunkFailReason
{
    TK_NSR_FAIL_LOCAL_WRONG_LINK_STATUS = 1,                  /* 1本端链路状态错误 */
    TK_NSR_FAIL_REMOTE_WRONG_LINK_STATUS,                     /* 2对端链路状态错误 */
    TK_NSR_FAIL_WRONG_LINK_KEY,
    TK_NSR_FAIL_WRONG_LINK_PORT_NO,
    TK_NSR_FAIL_LOCAL_WRONG_LINK_EXPIRED,
    TK_NSR_FAIL_REMOTE_WRONG_LINK_EXPIRED,
    TK_NSR_FAIL_WRONG_LINK_SYSMAC,
    TK_NSR_FAIL_NEGOTBL_NULL,
    TK_NSR_FAIL_TIMEOUT,
    TK_NSR_FAIL_RESUME_MAC_INCONSISTENT,
    TK_NSR_FAIL_SMOOTH_MAC_INCONSISTENT,
    TK_NSR_FAIL_GET_LINK_NOT_EXIST,
};

typedef struct tagTrunkNsrTimer
{
    ULONG ulTrunkNsrTimerId;
    ULONG ulTrunkNsrPeriod;

}TRUNK_NSR_TIMER_S;

extern ULONG TRUNK_NSR_RecoverLacpLink(VOID);
extern ULONG TRUNK_NSR_SmoothLacpLink(VOID);
extern ULONG TRUNK_NSR_SetTrunkNsrTimer(ULONG ulTime);
extern ULONG TRUNK_NSR_PpiDownLoadHookRegister(TRUNK_NSR_PPI_HOOK pstTrunkNspPpiHook);
extern ULONG TRUNK_NSR_GetTrunkNsrTimer(ULONG *pulTime);
extern ULONG TRUNK_NSR_GetGlobalInformation(TRUNK_NSR_GLOBAL_INFO_S *pstTrunkNsrGlobalInfo);
extern ULONG TRUNK_NSR_GetLinkInfo(CHAR *pIfName, TRUNK_NSR_LINK_INFO_S *pstTrunkNsrLinkInfo);
extern ULONG TRUNK_NSR_SetTrunkNsrEnable(UCHAR ucEnable);
extern VOID TRUNK_NSR_Stat(ULONG ulType);
extern ULONG TRUNK_NSR_Init(VOID);


extern ULONG g_ulCurrentTrunkNSRState;
extern UCHAR g_ulTrunkNsrEnableFlag;
extern TRUNK_NSR_TIMER_S g_stTrunkNsrTimer;
extern TRUNK_NSR_PPI_HOOK g_pfTrunkNsrPpiHook;


#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_NSR_H_ */
