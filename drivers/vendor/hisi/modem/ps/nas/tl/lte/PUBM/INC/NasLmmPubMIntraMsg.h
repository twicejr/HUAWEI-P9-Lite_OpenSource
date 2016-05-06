/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File Name       : NasLmmPubMIntraMsg.h
    Description     : NasLmmPubMIntraMsg.c header file
    History     :
    1.zhengjunyan 00148421 2011-05-28 文件名由 NasMmPubMIntraMsg.h修改为NasLmmPubMIntraMsg.h
******************************************************************************/

#ifndef __NASLMMPUBMINTRAMSG_H__
#define __NASLMMPUBMINTRAMSG_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define NAS_EMM_BUF_MSG_MAX_NUM         (8)

/* the size for intra msg queue */
#define NAS_LMM_INTRA_MSG_MAX_NUM        (16)

#define NAS_EMM_INTRA_MSG_MAX_SIZE      (1024)

#define NAS_EMM_STATUS_MSG_SIZE          1

/* FSM MSG buffer*/
#define NAS_EMM_MAIN_MAX_HIGH_MSG_NUM   (16)                /* 缓存的高优先级消息个数 */
#define NAS_EMM_MAIN_MAX_MID_MSG_NUM    (16)                /* 缓存的中优先级消息个数 暂时保留 */
#define NAS_EMM_MAIN_MAX_LOW_MSG_NUM    (4)                 /* 缓存的低优先级消息个数 暂时保留 */

#define NAS_LMM_INTRA_MSG_HEADER         0x00121200

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : NAS_LMM_INTRA_MSG_ID_ENUM_UINT32
 枚举说明  : 内部假消息类型定义

ulMsgID包括4部分:

-----------------------------------------------------------
  字节高位                                      字节低位
-----------------------------------------------------------
| BYTE1高4位 + 0000 |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------
0000：协议模块间消息|  源模块号 |  目的模块号| 消息号0-255
-----------------------------------------------------------
0001：L2 LOG        |           |            |
-----------------------------------------------------------
0010：空口消息      |           |            |
-----------------------------------------------------------
0011：普通命令      |           |            |
-----------------------------------------------------------
0100：实时监控命令  |           |            |
-----------------------------------------------------------
0101：关键事件      |           |            | 保留不用
-----------------------------------------------------------

MM层模块号为            : 0x02
MM层内部消息的编号为   : 0x000202**,只有最低一个字节区分内部消息ID
*****************************************************************************/
enum NAS_LMM_INTRA_MSG_ID_ENUM
{
    ID_NAS_LMM_INTRA_MM_MM_BEGIN                             = NAS_LMM_INTRA_MSG_HEADER|0x00,

    /* MM 公共的内部假消息,不写源和目的模块名称 */


    /* MMC 的假消息 */
    ID_NAS_LMM_INTRA_EMMC_EMM_START_REQ                       = NAS_LMM_INTRA_MSG_HEADER|0x01,
    ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF                       = NAS_LMM_INTRA_MSG_HEADER|0x02,
    ID_NAS_LMM_INTRA_EMMC_EMM_STOP_REQ                        = NAS_LMM_INTRA_MSG_HEADER|0x03,
    ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF                        = NAS_LMM_INTRA_MSG_HEADER|0x04,
    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_REQ                        = NAS_LMM_INTRA_MSG_HEADER|0x05,
    ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND                        = NAS_LMM_INTRA_MSG_HEADER|0x06,
    ID_NAS_LMM_INTRA_EMMC_EMM_CELL_SELECTION_CTRL_REQ         = NAS_LMM_INTRA_MSG_HEADER|0x07,
    ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND                    = NAS_LMM_INTRA_MSG_HEADER|0x08,
    ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND               = NAS_LMM_INTRA_MSG_HEADER|0x09,
    /*ID_NAS_LMM_INTRA_EMMC_EMM_ACTION_RESULT_REQ               = NAS_LMM_INTRA_MSG_HEADER|0x0a,*/


    /* MRRC的内部消息 */

     /* NAS_EMM_MRRC_INTRA_DATA_REQ_STRU 其他模块通过此消息请求MRRC发送空口消息*/
    ID_NAS_LMM_INTRA_MRRC_DATA_REQ                           = NAS_LMM_INTRA_MSG_HEADER|0x0b,

    /* NAS_EMM_MRRC_INTRA_REL_REQ_STRU 其他模块通过此消息请求MRRC释放RRC连接*/
    ID_NAS_LMM_INTRA_MRRC_REL_REQ                            = NAS_LMM_INTRA_MSG_HEADER|0x0c,

    /* MRRC向其他模块发送INTRA_CONNECT_FAIL_IND连接释放完成*/
    ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND                   = NAS_LMM_INTRA_MSG_HEADER|0x0d,

    /* REG的内部消息 */

    /* 其他模块发起ATTACH的内部消息 */
    ID_NAS_LMM_INTRA_ATTACH_REQ                              = NAS_LMM_INTRA_MSG_HEADER|0x0f,

    /* DEREG的内部消息 其他模块发起DETACH的内部消息*/
    ID_NAS_LMM_INTRA_DETACH_REQ                              = NAS_LMM_INTRA_MSG_HEADER|0x10,

    /* TAU内部消息 */
    ID_NAS_LMM_INTRA_TAU_REQ                                 = NAS_LMM_INTRA_MSG_HEADER|0x11,


    /*各模块通过该消息转发网侧空口消息*/
    ID_NAS_LMM_INTRA_DATA_IND                                = NAS_LMM_INTRA_MSG_HEADER|0x15,

    /*收到RRC_REL_IND或者INTRA_REL_IND消息，发送该消息，将NAS连接态从CONN变为IDLE*/
    ID_NAS_LMM_INTRA_CONN2IDLE_REQ                           = NAS_LMM_INTRA_MSG_HEADER|0x16,

    /* EMM收到UsimStatusInd消息，转发给MMC */
    ID_NAS_LMM_INTRA_EMMC_EMM_USIM_STATUS_IND                = NAS_LMM_INTRA_MSG_HEADER|0x17,

    /* LMM在cs/ps1 mode需要DISABLE LTE时给自己发这条内部消息 */
    /* SECU模块在EIA0启动时给EMM模块发送这条内部消息 */
    ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY                         = NAS_LMM_INTRA_MSG_HEADER|0x19,

    ID_NAS_LMM_INTRA_MSG_TYPE_BUTT                           = NAS_LMM_INTRA_MSG_HEADER|0x1F
};
typedef VOS_UINT32 NAS_LMM_INTRA_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 结构名    : NasMmIntraMsgCB
 结构说明  : NAS_LMM内部消息结构,同VOS申请时分配的结构 MsgCB
*****************************************************************************/
struct NasMmIntraMsgCB
{
    VOS_MSG_HEADER
    VOS_UINT8 aucValue[4];
};

typedef struct NasMmIntraMsgCB          NasMmIntraMsgBlock;

/*****************************************************************************
 结构名    : NAS_LMM_INTRA_MSG_STRU
 结构说明  : NAS_LMM内部消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NAS_LMM_INTRA_MSG_ID_ENUM_UINT32     ulMsgId;                /* 消息 ID */
    VOS_UINT8                           aucMsgData[4];          /* 整条消息存储 */
}NAS_LMM_INTRA_MSG_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_INTRA_DATA_IND_STRU
 结构说明  : NAS_LMM内部空口消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    NAS_LMM_INTRA_MSG_ID_ENUM_UINT32     ulMsgId;                /* 消息 ID */
    LRRC_LNAS_MSG_STRU                    stNasMsg;               /* 空口消息的内容*/
}NAS_LMM_INTRA_DATA_IND_STRU;

/*****************************************************************************
 结构名    : NAS_LMM_INTER_MSG_QUEUE_STRU
 结构说明  : NAS_LMM内部消息队列结构
             usHeader   : 指向下一个出队的消息
             usTail     : 指向下一个入队的消息将被放入的位置，该位置当前为空
                          即aucMsgBuff[usTail]，当前为空
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usHeader;                                   /* 队头 */
    VOS_UINT16                      usTail;                                     /* 队尾 */
    VOS_UINT8                       aucMsgBuff[NAS_LMM_INTRA_MSG_MAX_NUM][NAS_EMM_INTRA_MSG_MAX_SIZE];    /* 消息存放区域 */
}NAS_LMM_INTRA_MSG_QUEUE_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern  VOS_UINT32  NAS_LMM_MMSendIntraMsg(  VOS_VOID          **pucIntraMsg );
extern  NasMmIntraMsgBlock * NAS_LMM_GetSendIntraMsgBuffAddr( VOS_UINT32 ulBuffSize );/*lint -e826*/
extern  VOS_VOID    NAS_LMM_MAIN_EnQueue(VOS_VOID);
extern  VOS_UINT8 * NAS_LMM_GetIntraMsgFromQueue( VOS_VOID  );
extern  VOS_VOID    NAS_LMM_DeQueue(VOS_VOID);
extern  MsgBlock *  NAS_LMM_GetLmmMmcMsgBuf( VOS_UINT32 ulBuffSize );
extern  VOS_VOID    NAS_LMM_SendLmmMmcMsg( const VOS_VOID *pstLmmMmcMsg );

#define NAS_LMM_SendIntraMsg(pMsg )     NAS_LMM_MMSendIntraMsg( (VOS_VOID**)(&(pMsg)))/*lint +e826*/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasLmmPubMIntraMsg.h*/
