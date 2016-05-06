/******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : DiccInterface.h
  Author      : Wangrong
  Version     :
  Date        : 2011-8-18
  Description : 该头文件定义了双核通信数传面专用通道向其他模块提供的接口
  History     :
  1. Date:         2011-8-18
     Author:       Wangrong
     Modification: Create

******************************************************************************/

#ifndef __DICC_INTERFACE_H__
#define __DICC_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 其他头文件包含
******************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#if (VOS_OS_VER == VOS_WIN32)
#include "MemoryMap.h"
#endif
#if( FEATURE_ON == FEATURE_CSD )

/******************************************************************************
  2 宏定义
******************************************************************************/
#define DICC_MEM_START_PHY_ADDR                     (ECS_TTF_DICC_ADDR)             /* DICC核间通信内存起始物理地址 */


#define DICC_MEM_INIT_MAGIC_NUM_ADDR                /*lint -e{778}*/(ECS_TTF_DICC_SPINLOCK_ADDR)    /* 存放DICC同步魔术字的物理地址 */

/* 规格定义 */
#define DICC_QUEUE_MEM_SIZE                         (ECS_TTF_DICC_SIZE)                    /* DICC核间通信内存, 目前规划128KB */

/* 定义一个特殊值的宏, 获取通道中数据块数失败, 使用这个宏 */
#define DICC_INVALID_VALUE                          (0xFFFFFFFF)

/* 规格定义 */
#define DICC_INFO_BLOCK_MAX_LEN                     (16)                        /* 待传递的信息块的最大长度，单位: 字节 */
#define DICC_MAX_CHAN_NUM                           (DICC_CHAN_ID_BUTT)         /* 最多4个DICC通道 */
#define DICC_PER_QUEUE_MAX_NODE_NUM                 (395+1)                     /* 一个队列最多存放395块信息, 首尾指针机制, 必须多保留一块 */
#define DICC_BAT_OP_CNT                             (64)                        /* 批量处理个数(一次批量插入/取出的个数) */

/* 各通道按照用途进行编号 (外部通道使用者请使用宏) */
#define DICC_CHAN_ID_UL_CSD_DATA_CHAN               (DICC_CHAN_ID_0)            /* 上行CSD业务数据传递通道  */
#define DICC_CHAN_ID_UL_REL_DATA_CHAN               (DICC_CHAN_ID_1)            /* 释放上行用户业务数据传递通道  */
#define DICC_CHAN_ID_DL_CSD_DATA_CHAN               (DICC_CHAN_ID_2)            /* 下行CSD业务数据传递通道  */
#define DICC_CHAN_ID_DL_REL_DATA_CHAN               (DICC_CHAN_ID_3)            /* 释放下行用户业务数据传递通道  */

/* 各通道按照通道使用用途编号(是DICC内部使用, 外部通道使用者请用DICC_SERVICE_TYPE_ENUM_UINT8的枚举) */
#define DICC_SERVICE_TYPE_CSD_DATA                  (DICC_SERVICE_TYPE_0)       /* for CSD data */
#define DICC_SERVICE_TYPE_REL_MEM                   (DICC_SERVICE_TYPE_1)       /* for release memory */



/******************************************************************************
  3 枚举定义
******************************************************************************/
/* CPU编号 */
enum DICC_CPU_ID_ENUM
{
    DICC_CPU_ID_CCPU                                = 0,        /* Communication CPU */
    DICC_CPU_ID_ACPU                                = 1,        /* Application CPU */

    DICC_CPU_ID_BUTT
};
typedef VOS_UINT8 DICC_CPU_ID_ENUM_UINT8;

/* DICC通道编号(外部通道使用者不直接使用枚取值, 使用下边转定义的宏) */
enum DICC_CHAN_ID_ENUM
{
    DICC_CHAN_ID_0                                  = 0,
    DICC_CHAN_ID_1,
    DICC_CHAN_ID_2,
    DICC_CHAN_ID_3,

    DICC_CHAN_ID_BUTT
};
typedef VOS_UINT8 DICC_CHAN_ID_ENUM_UINT8;


/* 用于外部使用者对通道使用用途的分类(外部通道使用者直接使用枚取值) */
enum DICC_SERVICE_TYPE_ENUM
{
    DICC_SERVICE_TYPE_0                             = 0,
    DICC_SERVICE_TYPE_1,

    DICC_SERVICE_TYPE_BUTT
};
typedef VOS_UINT8 DICC_SERVICE_TYPE_ENUM_UINT8;


/* 指示获取通道中已经存放的数据个数, 或者通道中可以继续存放的个数 */
enum DICC_GET_CHN_NODE_CNT_ENUM
{
    DICC_GET_CHN_CURR_DATA_CNT                      = 0,       /* for get current data number */
    DICC_GET_CHN_FREE_SPACE_CNT,                               /* for get free data number*/

    DICC_GET_CHN_NODE_CNT_BUTT
};
typedef VOS_UINT8 DICC_GET_CHN_NODE_CNT_ENUM_UINT8;

/* 指示通道发送端或者接收端 */
enum DICC_CHAN_ROLE_ENUM
{
    DICC_CHAN_ROLE_SENDER                           = 0,            /* sender */
    DICC_CHAN_ROLE_RECVER,                                          /* receiver */

    DICC_CHAN_ROLE_BUTT
};
typedef VOS_UINT8 DICC_CHAN_ROLE_ENUM_UINT8;

/* 通道操作编号 */
enum DICC_ERROR_CODE_ENUM
{
     DICC_OK                                        = 0,    /* 操作成功 */

     /**************************************************************************
                           DICC channel user error
     **************************************************************************/
     DICC_ERR_CHAN_BLK_NUM                          = 1,    /* 通道块数个数错误 */
     DICC_ERR_CHAN_BLK_SIZE,                                /* 通道块大小错误 */
     DICC_ERR_MEM_SIZE,                                     /* 通道内存总量错误 */
     DICC_ERR_RECV_ISR_NULL,                                /* 通道接收端信号量句柄为空 */
     DICC_ERR_CHAN_ID_UNDEFINED,                            /* 通道未注册 */
     DICC_ERR_INFO_PTR_NULL,                                /* 通道一端信息空 */
     DICC_ERR_SERVCE_UNDEFINED,                             /* 通道服务未注册 */
     DICC_ERR_EXISTED_CHAN_ID,                              /* 通道重复注册 */
     DICC_ERR_CHAN_ID_NOT_MATCH_ROLE,                       /* 通道号与角色不匹配 */
     DICC_ERR_CHAN_ALREADY_OPENED,                          /* 通道重复打开 */
     DICC_ERR_INSERT_DESP_BLK_PTR_NULL,                     /* 通道插入信息描述符为空 */
     DICC_ERR_INSERT_DESP_BLK_DATA_CNT,                     /* 通道插入信息块数错误 */
     DICC_ERR_INSERT_DESP_BLK_DATA_NULL,                    /* 传递信息为空 */
     DICC_ERR_DLV_DATA_BLK_SIZE,                            /* 传递信息块大小错误 */
     DICC_ERR_CHAN_NOT_OPEN_IN_BOTH_SIDES,                  /* 传递或取出信息时, 通道未完全打开 */
     DICC_ERR_INVALID_CHAN_ID,                              /* 不合法的通道ID */
     DICC_ERR_GET_CNT_TYPE_UNDEFINED,                       /* 获取通道块数类别错误 */
     DICC_ERR_REMOVE_DATA_PTR_NULL,                         /* 存放取出数据的指针为空 */
     DICC_ERR_REMOVE_DATA_CNT,                              /* 存放取出块数错误 */
     DICC_ERR_CPU_ID_NOT_MATCH,                             /* CPU ID不匹配 */
     DICC_ERR_CLOSE_BEFORE_SENDER_CLOSED,                   /* 接收端在发送端关闭前关闭 */
     DICC_ERR_CHAN_FULL,                                    /* 通道始数据满 */

     /**************************************************************************
                           DICC software error
     **************************************************************************/
     DICC_ERR_CHAN_NOT_READY                        = 100,  /* 通道控制结构未准备好 */
     DICC_ERR_GET_NODE_FAIL,                                /* 获取核间传递结点失败 */
     DICC_ERR_MAGIC_NUM_CHANGED,                            /* 核间传递数据被篡改 */
     DICC_ERR_RING_QUEUE_FAIL,                              /* 核间对列操作失败 */
     DICC_ERR_LOCAL_SEMPHORE_FAIL,                          /* 本地信号量操作失败 */
     DICC_ERR_MAGIC_MEM_TEMPERED,                           /* 用于同步的Magic被篡改 */

     /**************************************************************************
                           DICC hardware error
     **************************************************************************/
     DICC_ERR_ISR_CONNECT_FAIL                      = 200,  /* 中断挂接失败 */
     DICC_ERR_USE_HW_SEMPHORE_FAIL,                         /* 硬件信号量操作失败 */
     DICC_ERR_TRIG_ISR_FAIL,                                /* 触发中断失败 */
     DICC_ERR_OP_ISR_FAIL,                                  /* 中断使能或去使能失败 */

     DICC_ERR_BUTT
};
typedef VOS_UINT32 DICC_ERROR_CODE_ENUM_UINT32;


/******************************************************************************
  4 全局变量声明
******************************************************************************/


/******************************************************************************
  5 消息头定义
******************************************************************************/


/******************************************************************************
  6 消息定义
******************************************************************************/


/******************************************************************************
  7 STRUCT定义
******************************************************************************/
#pragma pack(4)

/* 信息传递描述结构 */
typedef struct
{
    VOS_UINT8                         aucReserve[2];
    PS_BOOL_ENUM_UINT8                enAutoTrigTx;    /* 是否自动触发信息传递, 是 - TRUE，否 - FALSE */
    VOS_UINT8                         ucDataLen;       /* 待传递的信息数据长度, 单位: 字节, 不能超过16字节 */
    VOS_UINT8                        *pucUserData;     /* 待传递的信息数据内容 */
} DICC_INSERT_DSCP_BLK_STRU;

#if 0
/* 待传递的信息 */
typedef struct
{
    VOS_UINT8                         aucReserve[3];
    VOS_UINT8                         ucDataLen;       /* 待传递的信息数据长度, 单位: 字节, 不能超过16字节 */
    VOS_UINT8                        *pucUserData;     /* 待传递的信息数据内容 */
} DICC_INSERT_INFO_STRU;
#endif

/* 信息批量传递描述结构 */
typedef struct
{
    VOS_UINT8                         aucReserve[2];
    VOS_UINT8                         ucInsertCnt;     /* 批量插入个数, 不能超过DICC_BAT_OP_CNT */
    PS_BOOL_ENUM_UINT8                enAutoTrigTx;    /* 是否自动触发信息传递, 是 - TRUE，否 - FALSE */
    VOS_UINT8                         aucDataLen[DICC_BAT_OP_CNT];       /* 待传递的信息数据长度, 单位: 字节, 不能超过16字节 */
    VOS_UINT8                        *apucUserData[DICC_BAT_OP_CNT];     /* 待传递的信息数据内容 */
} DICC_BAT_INSERT_DSCP_BLK_STRU;

/* 初始化通道参数 */
typedef struct
{
    VOS_UINT16                        usChnBlkNum;     /* 通道上一次最多传递块数(通道深度), 最多395块 */
    VOS_UINT16                        usChnBlkSize;    /* 通道上传递的信息的最大字节数, 最多16B */
} DICC_BLK_CHN_INFO_STRU;

/* 发送端初始化通道参数 */
typedef struct
{
    DICC_BLK_CHN_INFO_STRU            stSndChnInfo;    /* 初始化通道参数 */
} DICC_SEND_INIT_CHN_INFO_STRU;

/* 接收端初始化通道参数 */
typedef struct
{
    VOS_VOID                          (*pfuncRecvIsr)(VOS_VOID);    /* 接收端的中断服务程序 */
} DICC_RECV_INIT_CHN_INFO_STRU;

/* 初始化通道参数 */
typedef struct
{
    DICC_CHAN_ROLE_ENUM_UINT8         enUserRole;         /* 对要初始化通道, 本端在此CPU上充当的角色 */
    VOS_UINT8                         aucReserve1[3];     /* 4字节对齐, 保留 */

    union
    {
        DICC_SEND_INIT_CHN_INFO_STRU  stSndInitInfo;     /* 发送端初始化通道参数 */
        DICC_RECV_INIT_CHN_INFO_STRU  stRcvInitInfo;     /* 接收端初始化通道参数 */
    }u;
} DICC_INIT_CHN_INFO_STRU;


/******************************************************************************
  8 UNION定义
******************************************************************************/


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  9 OTHERS定义
******************************************************************************/
/******************************************************************************
 Function       : DICC_TriggerChanDataTx
 Description    : 触发核间通信中断API
 Input          : ulPid  - 调用此接口的PID
                  ucChanId - 通道ID
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     : 触发核间通信中断, 以知会对端接收传递的信息
******************************************************************************/
extern VOS_UINT32 DICC_TriggerChanDataTx(VOS_UINT32 ulPid, VOS_UINT8 ucChanId,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);

#if 0    /* IPC硬件不能确定在频繁使能和去使能时, 互斥信号量有时失败的原因, 商量决定暂不进行频繁使能和去使能 */
/******************************************************************************
 Function       : DICC_EnableIsr
 Description    : 使能核间通信中断API
 Input          : ulPid - 操作PID
                  enServiceType - 服务号
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     :
******************************************************************************/
extern VOS_UINT32 DICC_EnableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);

/******************************************************************************
 Function       : DICC_DisableIsr
 Description    : 去使能核间通信中断API
 Input          : ulPid - 操作PID
                  enServiceType - 服务号
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     :
******************************************************************************/
extern VOS_UINT32 DICC_DisableIsr(VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                      DICC_CPU_ID_ENUM_UINT8 enCpuId);
#endif

/******************************************************************************
 Function       : DICC_InsertChannelData
 Description    : 将待传递的信息数据转移到核间API
 Input          : ulPid - 调用此接口的PID
                  ucChanId - 通道ID
                  pstDscpBlk - 核间传递描述字段
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     : (1) 如果描述块结构中enAutoTrigTx置为0时, 不会触发传递行为,
                  此时需要由发送端来触发调用DICC_TriggerChanDataTx传递;
                  (2) 只有在通道打开后, 信息才会真正传递到对端
                  发送端和接收端任意一端未打开, 向核间转移待传递的信息数据操作失败;
                  (3) 外部使用者请不要直接使用DICC_InsertChannelDataAction,
                  而是使用宏DICC_InsertChannelData
******************************************************************************/
extern VOS_UINT32 DICC_InsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                               VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                               DICC_INSERT_DSCP_BLK_STRU *pstDscpBlk,
                                               DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_InsertChannelData(ulPid, ucChnId, pstDscpBlk, enCpuId)\
            DICC_InsertChannelDataAction(THIS_FILE_ID, __LINE__, (ulPid), (ucChnId), (pstDscpBlk), (enCpuId))

/******************************************************************************
 Function       : DICC_RemoveChannelData
 Description    : 将传递的信息从核间环形共享缓冲中取出API
 Input          : ulPid - 调用此接口的PID
                  ucChanId - 通道ID
 Output         : pucUsrData - 从核间取出的数据拷贝到此, 外部使用者保证指针非空
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     :
******************************************************************************/
extern VOS_UINT32 DICC_RemoveChannelData(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                         VOS_UINT8 *pucUsrData,
                                         DICC_CPU_ID_ENUM_UINT8 enCpuId);

/******************************************************************************
 Function       : DICC_OpenChannel
 Description    : 按照角色打开核间通信通道API
 Input          : ulPid - 调用此接口的PID
                  ucChanId - 通道ID
                  enUserRole - 在当前CPU上本端在通道上扮演的角色
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     :
******************************************************************************/
extern VOS_UINT32 DICC_OpenChannel(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                   DICC_CHAN_ROLE_ENUM_UINT8 enUserRole,
                                   DICC_CPU_ID_ENUM_UINT8 enCpuId);

/******************************************************************************
 Function       : DICC_CloseChannel
 Description    : 关闭核间通信通道API
 Input          : ulPid - 调用此接口的PID
                  ucChanId - 通道ID
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
 Commitment     : 关闭顺序要求: 发送端需要先关闭后, 接收端才能够关闭,
                  防止出现只有接收端关闭, 发送端不关闭, 从而数据残留在通道内。
                  且只有在两端都关闭后, 通道才真正关闭
******************************************************************************/
extern VOS_UINT32 DICC_CloseChannel(VOS_UINT32 ulPid, VOS_UINT8 ucChnId,
                                    DICC_CPU_ID_ENUM_UINT8 enCpuId);

/******************************************************************************
 Function       : DICC_SingleChnInit
 Description    : DICC用户单通道初始化API(按照服务类别初始化一个通道)
 Input          : ulPid - 调用此接口的PID
                  enServiceType - 服务类别号
                  stInitChanInfo - 要初始化的通道的具体参数
 Output         : 无
 Return Value   : 操作成功与否, DICC_OK - 成功, 其它 - 失败
******************************************************************************/
extern VOS_UINT32 DICC_SingleChnInitAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                     VOS_UINT32 ulPid, DICC_SERVICE_TYPE_ENUM_UINT8 enServiceType,
                                     DICC_INIT_CHN_INFO_STRU *pstInitChanInfo,
                                     DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_SingleChnInit(ulPid, enServiceType, pstInitChanInfo, enCpuId)\
            DICC_SingleChnInitAction(THIS_FILE_ID, __LINE__, (ulPid), (enServiceType), (pstInitChanInfo), (enCpuId))


/******************************************************************************
函 数 名  : DICC_GetChannelNodeCnt
功能描述  : 检查获取通道中数据块数的参数
输入参数  : ulPid - 调用此接口的PID
            ucChanId - 通道ID
            enGetChnNodeCntType - 指示获取通道中已经存放的数据个数,
                                  或者通道中可以继续存放的个数
输出参数  : 无
返 回 值  : 操作成功与否, DICC_OK - 成功, 其它 - 失败
说    明  : 外部使用者请不要使用DICC_GetChannelNodeCnt,
            而是使用宏DICC_GetChannelCurrDataCnt和DICC_GetChannelFreeSpaceCnt
******************************************************************************/
extern VOS_UINT32 DICC_GetChannelNodeCnt(VOS_UINT32                       ulPid,
                                         DICC_CHAN_ID_ENUM_UINT8          ucChnId,
                                         DICC_GET_CHN_NODE_CNT_ENUM_UINT8 enGetChnNodeCntType,
                                         DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define  DICC_GetChannelCurrDataCnt(ulPid, ucChnId, enCpuId)   (DICC_GetChannelNodeCnt((ulPid), (ucChnId), DICC_GET_CHN_CURR_DATA_CNT, (enCpuId)))
#define  DICC_GetChannelFreeSpaceCnt(ulPid, ucChnId, enCpuId)  (DICC_GetChannelNodeCnt((ulPid), (ucChnId), DICC_GET_CHN_FREE_SPACE_CNT, (enCpuId)))

extern VOS_UINT32 DICC_BatInsertChannelDataAction(VOS_UINT32 ulFileId, VOS_UINT32 ulLineNum,
                                        VOS_UINT32 ulPid, DICC_CHAN_ID_ENUM_UINT8 ucChnId,
                                        DICC_BAT_INSERT_DSCP_BLK_STRU    *pstBatDscpBlk,
                                        DICC_CPU_ID_ENUM_UINT8 enCpuId);
#define DICC_BatInsertChannelData(ulPid, ucChnId, pstBatDscpBlk, enCpuId)\
            DICC_BatInsertChannelDataAction(THIS_FILE_ID, __LINE__, (ulPid), (ucChnId), (pstBatDscpBlk), (enCpuId))

extern VOS_UINT32 DICC_BatRemoveChannelData(VOS_UINT32            ulPid,
                                  DICC_CHAN_ID_ENUM_UINT8  ucChnId,
                                  VOS_UINT8                aucUsrData[],
                                  VOS_UINT16               usNeedRemoveCnt,
                                  VOS_UINT16              *pusActiveRemoveCnt,
                                  DICC_CPU_ID_ENUM_UINT8   enCpuId);

#endif  /*FEATURE_ON == FEATURE_CSD*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* DiccInterface.h */



