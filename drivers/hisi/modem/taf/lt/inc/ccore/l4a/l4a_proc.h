

#ifndef __L4A_PROC_H__
#define __L4A_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "gen_msg.h"
#include  "hi_list.h"
#include  "msp_errno.h"
#include  "ApsL4aInterface.h"
#include  "AppRrcInterface.h"
#include  "AppL2Interface.h"
#include "LMspLPhyInterface.h"


#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

extern VOS_UINT32 g_L4aPrintCtrl;

#define L4A_INFO_LOG    if(g_L4aPrintCtrl) (VOS_VOID)vos_printf

#define L4A_ERROR_LOG (VOS_VOID)vos_printf

#define L4A_REQ_FLAG 0
#define L4A_CNF_FLAG 1

#define L4A_CURC_RPT_CFG_PARA_LEN        (16)

/* wait for 45s */
#define L4A_CMD_TIMEOUT_TIME_LEN        (45000)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/
typedef enum
{
    L4A_RPT_CMD_MODE            = 0,
    L4A_RPT_CMD_RSSI            = 1,
    L4A_RPT_CMD_ANLEVEL         = 8,
    L4A_RPT_CMD_CERSSI          = 48,
    L4A_RPT_CMD_LWURC           = 49,
    L4A_RPT_CMD_LCACELLURC      = 54,
    L4A_RPT_CMD_BUTT            = 64
}L4A_RPT_CMD_INDEX_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct _L4A_RX_INFO_STRU
{
    VOS_UINT32  ulReqMsgId;         /* 从AT/TAF接收到的请求命令ID */
    VOS_UINT32  ulCnfMsgId;         /* 从LPS接收到的应答命令ID */

    HTIMER      fwCtrlTimer;        /* 每个节点启一个TIMER，判断是否超时 */

    VOS_UINT16  usClientId;
    VOS_UINT8   ucRevData[2];

    HI_LIST_S      HiL4aList;          /* 指向下一个缓存节点命令数据 */

    VOS_UINT32  ulCidNum;           /* 请求的总cid个数 */
    VOS_UINT32  ulCidIndex;         /* 当前处理的cid个数 */

    VOS_VOID    *pData;             /* 缓存请求数据信息 */

    VOS_VOID    *pCnfData;          /* 缓存应答数据信息 */

}L4A_RX_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32               ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32               ulOpId;
    VOS_UINT8                pContext[0];       /* 数据起始地址*/
} L4A_PS_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;

    APS_L4A_APPCTRL_STRU                stCtrl;
    VOS_UINT8                           pContext[0];       /* 数据起始地址*/
} L4A_REQ_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;
    VOS_UINT8                           pContext[0];       /* 数据起始地址*/
} L4A_CNF_MSG_STRU;

typedef struct
{
	VOS_MSG_HEADER
	VOS_UINT32				enMsgId;			 /*_H2ASN_Skip*/
	VOS_UINT8				pContext[0];	   /* 数据其实地址*/
}L4A_DATA_MSG_STRU;


typedef VOS_UINT32 (*PFN_L4A_REQ_MSG_FUN)(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
typedef VOS_UINT32 (*PFN_L4A_IND_MSG_FUN)(L4A_PS_MSG_STRU* pData);
typedef VOS_UINT32 (*PFN_L4A_CNF)(L4A_PS_MSG_STRU* pData, VOS_VOID* pstTable,VOS_UINT16 usClientId);
typedef VOS_UINT32 (*PFN_L4A_TIMEOUT_PROC)(VOS_VOID);
typedef VOS_UINT32 (*PFN_L4A_CHECK)(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);

/* 消息函数表*/
typedef struct
{
    VOS_UINT32                  ulAtReqMsgId;
    VOS_UINT32                  ulPsReqMsgId;
    VOS_UINT32                  ulPsReqPid;
    PFN_L4A_REQ_MSG_FUN         pfnReqFun;
    VOS_UINT32                  ulPsCnfMsgId;
    PFN_L4A_CNF                 pfnCnfFun;
    VOS_UINT32                  ulAtCnfMsgId;
    PFN_L4A_CHECK               pfnCheck;
    const VOS_CHAR              *ATCmdName;         /* for mntn, can't be NULL */
} L4A_FW_MSG_FUN_TABLE_STRU;

typedef struct
{
    VOS_UINT32                  ulPsIndMsgId;
    PFN_L4A_IND_MSG_FUN         pfnIndFun;
    const VOS_CHAR              *ATCmdName;         /* for mntn, can't be NULL */
} L4A_IND_MSG_FUN_TABLE_STRU;

/* 可维可测信息 */

#define         L4A_MNTN_MSG_NUM        64         /* 消息ID存储个数 */

typedef struct
{
    VOS_UINT32              aulMsgId[L4A_MNTN_MSG_NUM];
    VOS_UINT32              aulTime[L4A_MNTN_MSG_NUM];
    VOS_UINT32              ulptr;
} L4A_MNTN_MSG_INFO_STRU;

typedef struct
{
    L4A_MNTN_MSG_INFO_STRU  stMsgInfoRx;         /* 记录从AT/TAF/PS接收的消息 */
    L4A_MNTN_MSG_INFO_STRU  stMsgInfoTx;         /* 记录给AT/TAF/PS发送的消息 */
    L4A_MNTN_MSG_INFO_STRU  stunMsg;             /* 不识别的消息 */
} L4A_MNTN_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT8    g_aucL4aCurcRptCfg[L4A_CURC_RPT_CFG_MAX_SIZE];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_UINT32 l4aPacket2Aps(VOS_VOID *pstDataCnf, VOS_UINT32 ulSize);
extern VOS_UINT32 l4aPacket2At(VOS_VOID *pstDataCnf, VOS_UINT32 ulSize);
extern VOS_UINT32 l4aPacket2Ps(VOS_UINT32 ulRecverId, VOS_VOID *pData, VOS_UINT32 ulLen);
extern VOS_UINT32 l4aPacket2PsNoCnf(VOS_UINT32 ulRecverId, VOS_VOID *pData, VOS_UINT32 ulLen);
extern VOS_BOOL L4A_GetRptCmdStatus( L4A_RPT_CMD_INDEX_ENUM_UINT32 enRptCmdIndex );
extern VOS_VOID L4A_SetRptCmdStatus( L4A_RPT_CMD_INDEX_ENUM_UINT32 enRptCmdIndex, VOS_BOOL bFlag );
extern VOS_VOID l4a_MsgProc(MsgBlock* pMsgBlock);
extern VOS_UINT32 l4a_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 l4a_StartTimer(HTIMER *phTimerId, L4A_RX_INFO_STRU* pNewNode, VOS_UINT32 ulms);
extern VOS_UINT32 l4a_StopTimer(HTIMER *phTimerId);
extern VOS_UINT32 MSP_L4FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern L4A_FW_MSG_FUN_TABLE_STRU * FwProGetMsgFunTbl(VOS_UINT32 * pulTableLenth);
extern L4A_IND_MSG_FUN_TABLE_STRU* l4a_FwProGetPsIndFun(VOS_UINT32 ulMsgId);

extern VOS_UINT32 L4A_MailboxMsgProc(VOS_VOID);
extern VOS_VOID l4a_MailboxCb(MAILBOX_INT_TYPE_E enIntType);
extern VOS_VOID l4a_MailboxProc(VOS_UINT32 ulPara1, VOS_UINT32 ulPara2,
                                VOS_UINT32 ulPara3, VOS_UINT32 ulPara4);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of l4a_proc.h */
