/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_nsr.h
*
*  Project Code: VISPV100R006C02B100
*   Module Name: bfd gr头文件
*  Date Created: 2008-8-16
*        Author: wangtong(00207740)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-8-16  wujie(61195)         Creat the first version.
*
*******************************************************************************/
#ifndef _BFD_NSR_H_
#define _BFD_NSR_H_

#ifdef __cplusplus
extern "C"{
#endif


typedef struct bfd_fsm_entry
{
  UCHAR ucNextState;
  UCHAR ucAction;
} BFD_FSM_ENTRY;

typedef enum tagBFD_NSR_MSG_TYPE_E
{
    BFD_NSR_MASTER_BOARD = 0,   /* 通知当前为主板 */
    BFD_NSR_RESUME_SESS,        /* 恢复会话消息 */
    BFD_NSR_RESUME_FINISH,      /* 转发面恢复会话完成 */
    BFD_NSR_CONFIG_FINISH,      /* 配置会话完成 */
    BFD_NSR_IF_READY,           /* 通知物理接口就绪 */
    BFD_NSR_START_SMOOTH,       /* 开始平滑(内部消息)*/
    BFD_NSR_MSG_STOP_NSR,       /* 停止NSR  */
    BFD_NSR_ERROR,              /* 内部错误  */
    BFD_NSR_DEL_NPSESS,         /* NP完成回退删除会话操作 */
    BFD_NSR_MAX
}BFD_NSR_MSG_TYPE_E;

typedef enum tagBFD_NSR_STATES_TYPE_E
{
    BFD_NSR_STATE_KEEPALIVE = 0,   /* 备板NSR初始状态 */
    BFD_NSR_STATE_RESUME,          /* 备升主NSR恢复状态 */
    BFD_NSR_STATE_SMOOTH,          /* 备升主NSR平滑状态*/
    BFD_NSR_STATE_QUIT,            /* 退出NSR流程状态 */
    BFD_NSR_STATE_NORMAL,          /* 主板NSR初始状态 */
    BFD_NSR_STATES_MAX
}BFD_NSR_STATES_TYPE_E;

typedef struct tagBFD_NSR_BAK_VRF_E
{
    ULONG ulResumeSessionNum;
    BFD_PPI_S **ppstBfdPPIInfoArray;
}BFD_NSR_BAK_VRF_E;

typedef struct tagBFD_NSR_BAK_DATA_E
{
    ULONG ulCacheNum;                   /*缓存大小*/
    ULONG ulCacheIndex;                 /*平滑过程中当前处理缓存索引*/
    BFD_PPI_S **ppstBfdPPIInfoCache;    /*存放NP上报会话信息缓存*/   
    BFD_NSR_BAK_VRF_E *pstVrfArray;     /*用于查找NP上报会话索引*/
}BFD_NSR_BAK_DATA_E;

typedef struct tagBFD6_NSR_BAK_VRF_E
{
    ULONG ulResumeSessionNum;
    BFD6_PPI_S **ppstBfd6PPIInfoArray;
}BFD6_NSR_BAK_VRF_E;

typedef struct tagBFD6_NSR_BAK_DATA_E
{
    ULONG ulCacheNum;                       /*缓存大小*/
    ULONG ulCacheIndex;                     /*平滑过程中当前处理缓存索引*/
    BFD6_PPI_S **ppstBfd6PPIInfoCache;      /*存放NP上报会话信息缓存*/   
    BFD6_NSR_BAK_VRF_E *pstVrf6Array;       /*用于查找NP上报会话索引*/
}BFD6_NSR_BAK_DATA_E;

#define BFD_ACT_NA 0
#define BFD_ACT_ERR 1
#define BFD_ACT_A 2
#define BFD_ACT_B 3
#define BFD_ACT_C 4
#define BFD_ACT_D 5
#define BFD_ACT_E 6
#define BFD_ACT_F 7
#define BFD_ACT_G 8
#define BFD_ACT_H 9

#define BFD_NSR_ENABLE      1
#define BFD_NSR_DISABLE     0
#define BFD_NSR_DISABLING   2

/* 会话当前标记，用来记录会话的当前的状态 */
#define BFD_NSR_FLAG_NORMAL_SESSION     0x00000000
#define BFD_NSR_FLAG_CONFIG_SESSION     0x00000001
#define BFD_NSR_FLAG_RESUME_SESSION     0x00000002

#define BFD_NSR_CLEAR_FLAG(ulState) ((ulState) = BFD_NSR_FLAG_NORMAL_SESSION)

#define BFD_NSR_CHECK_FLAG_CONFIG_SESSION(ulState)  ((ulState) & BFD_NSR_FLAG_CONFIG_SESSION)
#define BFD_NSR_SET_FLAG_CONFIG_SESSION(ulState)    ((ulState) = (ulState) | BFD_NSR_FLAG_CONFIG_SESSION)
#define BFD_NSR_CLR_FLAG_CONFIG_SESSION(ulState)    ((ulState) = (ulState) & ~BFD_NSR_FLAG_CONFIG_SESSION)

#define BFD_NSR_CHECK_FLAG_RESUME_SESSION(ulState)  ((ulState) & BFD_NSR_FLAG_RESUME_SESSION)
#define BFD_NSR_SET_FLAG_RESUME_SESSION(ulState)    ((ulState) = (ulState) | BFD_NSR_FLAG_RESUME_SESSION)

#define BFD_NSR_STAT_SESS_NUM_BEFORE_NSR    0X01               /* 触发NSR过程前，BFD会话个数*/
#define BFD_NSR_STAT_RESUME_SESSION         0X02         /* 转发面上报的会话个数*/
#define BFD_NSR_STAT_ADD_SESSION            0x03         /* NSR过程中配置add的会话数*/
#define BFD_NSR_STAT_DEL_SESSION            0x04         /* NSR过程中配置delete的会话数*/
#define BFD_NSR_STAT_PPI_CREATE             0x05  /* PPI下发 create 的会话数*/
#define BFD_NSR_STAT_PPI_DEL                0x06 /* PPI下发 delete 的会话数*/
#define BFD_NSR_STAT_PPI_DOWN               0x07 /* PPI下发 down 的会话数*/
#define BFD_NSR_STAT_PPI_UP                 0x08 /* PPI下发 up 的会话数*/
#define BFD_NSR_STAT_RCV_ADMINDOWN          0x09      /* NSR过程中收到admindown报文的会话数*/
#define BFD_NSR_STAT_ADMINDOWN              0x0A     /* NSR过程中配置admindown的会话数*/

#define BFD_NSR_ONEHOP_DSTPORT              3784
#define BFD_NSR_MULTHOP_DSTPORT             4784

typedef struct tagBFD_NSR_TIME_STAT_S
{
    ULONG ulBfdNsrResumeTotalTime;
    ULONG ulBfdNsrSmoothTotalTime;
}BFD_NSR_TIME_STAT_S;

extern ULONG g_ulBfdNsrStateFlag;
extern ULONG g_ulBfdNsrEnable;

extern ULONG BFD_NSR_Core_Enable(UCHAR ucType);
extern ULONG BFD_NSR_Core_GetSessionInfo(ULONG ulSessionId,BFD_NSR_SESS_INFO_S *pstSessInfo,ULONG ulVrfIndex);
extern ULONG BFD_NSR_Core_GetGlobalInfo(BFD_NSR_GLOBAL_INFO_S *pstBfdNsrGlobalInfo);
extern VOID BFD_NSR_SessionDelete(BFD_SESS_ENTRY_S *pstBFDSessEntry);
extern VOID BFD_NSR_Fsm(UCHAR ucEvent,VOID *pstData);
extern VOID BFD_NSR_ReceiveMsgFromNsr (ULONG ulMsg, UCHAR *pucData, ULONG ulLength);
extern ULONG BFD_NSR_Core_SetBfdNsrTimer(ULONG ulTime);
extern ULONG BFD_NSR_Core_GetBfdNsrTimer(VOID);
extern VOID BFD_NSR_Core_Stat(ULONG ulType, ULONG ulIpVer);
extern ULONG BFD_NSR_Init(ULONG ulNpMode);
extern ULONG BFD6_NSR_Core_GetSessionInfo(ULONG ulSessionId,BFD6_NSR_SESS_INFO_S *pstSessInfo,ULONG ulVrfIndex);
extern ULONG BFD_NSR_Core_GetBfd6TotalSessionNum(VOID);
extern ULONG BFD_NSR_PPICheck(BFD_PPI_S *pstBfdPpiInfo);
extern ULONG BFD6_NSR_PPICheck(BFD6_PPI_S *pstBfd6PpiInfo);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef _BFD_NSR_H_ */






