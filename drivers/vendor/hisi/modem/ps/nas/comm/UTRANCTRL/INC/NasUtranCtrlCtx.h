/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUTRANCTRLCtx.h
  版 本 号   : 初稿
  作    者   : w00167002
  生成日期   : 2012年7月12日
  最近修改   :
  功能描述   : NasUTRANCTRLCtx.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月12日
    作    者   : w00167002
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_CTX_H_
#define _NAS_UTRANCTRL_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "NasFsm.h"
#include  "NasUtranCtrlInterface.h"
#include  "NasMmlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN                    (1600)              /* 缓存的最大长度 */

#define NAS_UTRANCTRL_OCTET_MOVE_SIXTEEN_BITS               (0x10)              /* 将一个字节移动16位 */
#define NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM                     (20)                /* 最大缓存的个数 */

#define NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM (0XFF)              /* 模式自动切换中支持任意SIM卡进行UTRAN模式的切换 */
#define NAS_UTRANCTRL_TIMER_ID_START_INDEX                  (9000)              /* UTRANCTRL模块定时器ID的开始索引 */

#define NAS_UTRANCTRL_HONGKONG_MCC                          (0x40504)           /* 香港国家码 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_FSM_ID_ENUM_UINT32
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2012年7月18日
   作    者   : w00167002
   修改内容   : 新建
 2.日    期   : 2012年8月4日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_UTRANCTRL_FSM_ID_ENUM
{
    /* UTRANCTRL MAIN态状态机的名称 */
    NAS_UTRANCTRL_FSM_MAIN                                  = 0X00,

    /* UTRANCTRL 开机状态机 */
    NAS_UTRANCTRL_FSM_SWITCH_ON                             = 0X01,

    /* UTRANCTRL 关机状态机 */
    NAS_UTRANCTRL_FSM_POWER_OFF                             = 0X02,

    /* UTRANCTRL PLMN SELECTION 状态机 */
    NAS_UTRANCTRL_FSM_PLMN_SELECTION                        = 0X03,

    /* UTRANCTRL SYSCFG状态机 */
    NAS_UTRANCTRL_FSM_SYSCFG                                = 0X04,

    /* UTRANCTRL 模式改变状态机 */
    NAS_UTRANCTRL_FSM_MODE_CHANGE                           = 0X05,

    NAS_UTRANCTRL_FSM_BUTT

};
typedef VOS_UINT32 NAS_UTRANCTRL_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_WAIT_AS_START_CNF_ENUM
 结构说明  : 用于标记收到的GU接入层的开机回复消息
*****************************************************************************/
enum NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_ENUM
{
    NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL                  = 0x00,
    NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF                   = 0x01,
    NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF                   = 0x02,
    NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF                    = 0x04,
    NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF                   = 0x08,
};
typedef VOS_UINT8 NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8
 结构说明  : 当前的主模:WCDMA/TD-SCDMA/GSM/LTE
 1.日    期   : 2012年8月8日
   作    者   : s00217060
   修改内容   : 新建
*****************************************************************************/
enum NAS_UTRANCTRL_MASTER_MODE_ENUM
{
    NAS_UTRANCTRL_MASTER_MODE_WCDMA,                                            /* 主模为WCDMA */
    NAS_UTRANCTRL_MASTER_MODE_TDSCDMA,                                          /* 主模为TDSCDMA */
    NAS_UTRANCTRL_MASTER_MODE_GSM,                                              /* 主模为GSM */
    NAS_UTRANCTRL_MASTER_MODE_LTE,                                              /* 主模为LTE */
    NAS_UTRANCTRL_MASTER_MODE_BUTT
};
typedef VOS_UINT8 NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM
 结构说明  : 当前UTRAN的切换模式
 1.日    期   : 2012年8月14日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM
{
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY               = 0,                 /* 当前为FDD ONLY */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY               = 1,                 /* 当前为TDD ONLY */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO                   = 2,                 /* 当前自动切换模式 */
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_BUTT                   = 3
};
typedef VOS_UINT8 NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8
 结构说明  : 初始化UTRANCTRL CTX信息类型
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : 新增
*****************************************************************************/
enum NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM
{
    NAS_UTRANCTRL_INIT_CTX_STARTUP                    = 0,
    NAS_UTRANCTRL_INIT_CTX_POWEROFF                   = 1,
    NAS_UTRANCTRL_INIT_CTX_BUTT
};
typedef VOS_UINT32 NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : NAS_UTRANCTRL_ENTRY_MSG_STRU
 结构说明  : 需要保存的入口消息
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN];
} NAS_UTRANCTRL_ENTRY_MSG_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_CACH_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
 1.日    期   : 2012年8月6日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       stMsgEntry;     /* 缓存的具体内容 */
}NAS_UTRANCTRL_CACH_MSG_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_MSG_QUEUE_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2012年8月6日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCurrIndex;                            /* 记录当前处理缓存的index */
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[2];
    NAS_UTRANCTRL_CACH_MSG_INFO_STRU   astMsgQueue[NAS_UTRANCTRL_MAX_MSG_QUEUE_NUM]; /* MMC的消息队列数组，存储的是带通用消息头的消息 */
}NAS_UTRANCTRL_MSG_QUEUE_STRU;


/*****************************************************************************
 结构名    : NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU
 结构说明  : 保存NV:en_NV_Item_Utran_Mode_Auto_Switch中的内容
 1.日    期   : 2012年8月6日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0：UTRAN模式为FDD 1：UTRAN模式为TDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* 支持TD网络的国家号个数 */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* 根据IMSI PLMN决定UTRAN模式是否AUTO SWITCH时，当前IMSI的PLMN在此列表中的都支持自动切换，否则固定为W模 */
    VOS_UINT8                           aucReserve[1];
    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];/* 有TD网络的国家码列表 */
    NAS_MML_PLMN_ID_STRU                astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];/* IMSI PLMN 列表 */
}NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU;



/*****************************************************************************
 结构名    : NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU
 结构说明  : NVIM项中的MS定制需求信息
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建
    
  2.日    期   : 2013年11月18日
    作    者   : w00167002
    修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                TD下不发起SMC流程。
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enCurrUtranMode;    /* NVIM中保存的UTRAN模式 */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enPreUtranMode;     /* 上次发给RRC的UTRAN模式 */

    VOS_UINT8                                               ucReserved;         /* 保留字段 */

    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;/* 当前UTRAN的自动切换模式 */
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU               stUtranModeAutoSwitch;/* 模式自动切换信息  */

    VOS_UINT8                                               ucIsUtranTddCsSmcNeeded; /* NVIM中保存的UTRANTDD CS SMC是否需要 */
    VOS_UINT8                                               ucIsUtranTddPsSmcNeeded; /* NVIM中保存的UTRANTDD PS SMC是否需要 */
    VOS_UINT8                                               aucReserved[2];

}NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_MML_MS_CFG_INFO_STRU
 结构说明  : MS支持的MS配置能力
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU  stCustomCfg;                           /* NVIM中的定制信息 */
 }NAS_UTRANCTRL_MS_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU
 结构说明  : 搜网控制块运行上下文
 1.日    期   : 2012年8月6日
   作    者   : W00176964
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSearchedSpecTdMccFlg;                 /* 记录是否有搜到中国网络标识 */
    VOS_UINT8                           aucReserve[3];
}NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_FSM_PLMN_SELECTION_CTX_STRU
 结构说明  : 搜网状态机上下文
 1.日    期   : 2012年8月06日
   作    者   : w00176964
   修改内容   : 新增

 2.日    期   : 2015年12月17日
   作    者   : w00167002
   修改内容   : 在W下搜网失败，进UTRANCTRL选择TD网络时候，收到第一阶段定
                时器超时等消息，触发打断选网状态机。当前MMC选网状态机给W发STOP REQ请求，而不是
                给TD发STOP搜网请求，这样MMC后续又搜索Lte,出现双主模异常复位. 在消息打断选网状态机时候，
                需要先退出UTRANCTRL选网流程，再打断MMC选网状态机。此时MMC收到选网状态机被MMC发送的
                abort消息打断，则可退出选网状态机。
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAbortFlg;                             /* 状态机打断标记 */

    VOS_UINT8                           ucRcvMmcAbortFsmReqMsgFlg;              /* 收到打断MMC状态机消息标记 */
    
    VOS_UINT8                           aucReserve[2];
}NAS_UTRANCTRL_FSM_PLMN_SELECTION_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_FSM_MODE_CHANGE_CTX_STRU
 结构说明  : Mode Change状态机上下文
 1.日    期   : 2012年8月7日
   作    者   : s00217060
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucWaitSlaveModeUtranModeCnfFlg;
    VOS_UINT8                                               aucReserve[3];
}NAS_UTRANCTRL_FSM_MODE_CHANGE_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_FSM_EXTRA_CTX_UNION
 结构说明  : 状态机状态描述结构,状态机上下文信息
 1.日    期   : 2012年8月7日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2012年8月11日
   作    者   : s00217060
   修改内容   : for V7R1C50_GUTL_PhaseII,新增Mode Change状态机上下文
*****************************************************************************/
typedef union
{
    NAS_UTRANCTRL_FSM_PLMN_SELECTION_CTX_STRU               stPlmnSelectionCtx;

    NAS_UTRANCTRL_FSM_MODE_CHANGE_CTX_STRU                  stModeChangeCtx;
}NAS_UTRANCTRL_FSM_EXTRA_CTX_UNION;


/*****************************************************************************
 结构名    : NAS_UTRANCTRL_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2012年7月19日
   作    者   : w00167002
   修改内容   : 新建
 2.日    期   : 2012年8月7日
   作    者   : w00176964
   修改内容   : 增加状态机上下文
*****************************************************************************/
typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enFsmId;

    /* 当前状态 */
    VOS_UINT32                          ulState;                                /* L1状态 */

    /* 入口消息MSGID和内容  */
    NAS_UTRANCTRL_ENTRY_MSG_STRU        stEntryMsg;

    /* 状态机数据 */
    NAS_UTRANCTRL_FSM_EXTRA_CTX_UNION   unFsmCtx;

}NAS_UTRANCTRL_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU
 结构说明  : UTRANCTRL模块主控制信息结构
 1.日    期   : 2012年8月8日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2014年11月25日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReplaceMmcMsgFlg;                     /* 替换发给MMC的消息标记:VOS-TRUE:需要用缓存的消息替换发给MMC的消息；VOS_FALSE:不需要替换发给MMC的消息 */

    VOS_UINT8                           ucSwitchOnPlmnSearchFlag;            /* 标识是否为开机搜网场景，只有开机搜网场景才有跳过tds的处理，VOS_TRUE:是开机搜网 */
    VOS_UINT8                           aucReserve[2];

    NAS_UTRANCTRL_ENTRY_MSG_STRU        stBufferUtranSndMmcMsg;                 /* 缓存的W/TD发送给MMC的消息 */
    NAS_UTRANCTRL_ENTRY_MSG_STRU        stBufferMmcSndUtranMsg;                 /* 缓存的MMC发送给W/TD的消息 */
}NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU
 结构说明  : NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU信息
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII新建:UTRANCTRL模块的可谓可测信息结构体
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeSndPcRecurFlg;                      /* PC回放是否需要导出全局变量,VOS_TRUE:需要, VOS_FALSE:不需要, */
    VOS_UINT8                           aucRsv3[3];
}NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU;

/*****************************************************************************
 结构名    : NAS_UTRANCTRL_MAINTAIN_CTX_STRU
 结构说明  : NAS_UTRANCTRL_MAINTAIN_CTX_STRU信息
 1.日    期   : 2012年8月16日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII新建:UTRANCTRL模块的可谓可测信息结构体
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_UE_MAINTAIN_INFO_STRU                     stUeMaintainInfo;   /* PC回放信息结构体 */

}NAS_UTRANCTRL_MAINTAIN_CTX_STRU;


/*****************************************************************************
 结构名    : NAS_UTRANCTRL_CTX_STRU
 结构说明  : UTRANCTRL运行上下文信息
 1.日    期   : 2012年7月12日
   作    者   : w00167002
   修改内容   : 新建
 2.日    期   : 2012年8月6日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_UTRANCTRL_FSM_CTX_STRU                              stCurFsm;               /* 当前的状态机信息 */
    NAS_UTRANCTRL_MS_CFG_INFO_STRU                          stMsCfgInfo;            /* MS的配置信息 */

    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU                       stMainCtrlInfo;         /* 状态机栈信息 */
    NAS_UTRANCTRL_MSG_QUEUE_STRU                            stBufferEntryMsgQueue;  /* NAS UNTRANCTRL缓存消息队列 */
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU                 stPlmnSearchCtrl;       /* PLMN搜网控制上下文 */
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                         stMaintainInfo;         /* 可谓可测上下文 */
}NAS_UTRANCTRL_CTX_STRU;
#endif

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
NAS_UTRANCTRL_CTX_STRU* NAS_UTRANCTRL_GetUtranCtrlCtx( VOS_VOID );
VOS_VOID  NAS_UTRANCTRL_InitCustomCfgInfo(
    NAS_UTRANCTRL_CUSTOM_CFG_INFO_STRU   *pstCustomCfg
);

VOS_VOID  NAS_UTRANCTRL_InitMsCfgCtx(
    NAS_UTRANCTRL_MS_CFG_INFO_STRU       *pstMsCfgInfo
);

VOS_VOID  NAS_UTRANCTRL_InitCurrFsmCtx(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurrFsmCtx
);
NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_GetPreUtranMode(VOS_VOID);
VOS_VOID NAS_UTRANCTRL_SetPreUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
);

VOS_VOID NAS_UTRANCTRL_SetCurrUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8   enUtranMode
);

VOS_VOID NAS_UTRANCTRL_SetUtranTddCsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded
);

VOS_VOID NAS_UTRANCTRL_SetUtranTddPsSmcNeededFlg(
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded
);
NAS_UTRANCTRL_FSM_CTX_STRU* NAS_UTRANCTRL_GetCurFsmAddr(VOS_VOID);

NAS_FSM_DESC_STRU* NAS_UTRANCTRL_GetCurFsmDesc(VOS_VOID);

NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetCurrEntryMsgAddr(VOS_VOID);

NAS_UTRANCTRL_FSM_ID_ENUM_UINT32 NAS_UTRANCTRL_GetCurrFsmId(VOS_VOID);

VOS_UINT32 NAS_UTRANCTRL_GetCurrFsmEventType(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 NAS_UTRANCTRL_FSM_GetCurrState(VOS_VOID);


VOS_VOID  NAS_UTRANCTRL_InitInternalMsgQueue(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstMsgQueue
);

VOS_VOID  NAS_UTRANCTRL_SwitchCurrFsmCtx(
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enNewFsmId
);

VOS_VOID  NAS_UTRANCTRL_InitMainCtrlInfo(
    NAS_UTRANCTRL_MAIN_CTRL_INFO_STRU  *pstMainCtrl
);

VOS_VOID  NAS_UTRANCTRL_InitFsmBufferEntryMsgQueueCtx(
    NAS_UTRANCTRL_MSG_QUEUE_STRU       *pstBufferEntryMsgQueue
);

VOS_VOID  NAS_UTRANCTRL_InitFsmPlmnSearchCtrlCtx(
    NAS_UTRANCTRL_PLMN_SEARCH_CTRL_CTX_STRU       *pstPlmnSearchCtrl
);

VOS_VOID  NAS_UTRANCTRL_InitMaintainInfo(
    NAS_UTRANCTRL_INIT_CTX_TYPE_ENUM_UINT8                  enInitType,
    NAS_UTRANCTRL_MAINTAIN_CTX_STRU                        *pstMaintainInfo
);

VOS_VOID NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag
);
VOS_UINT8 NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag(VOS_VOID);



VOS_VOID NAS_UTRANCTRL_SetReplaceMmcMsgFlg(
    VOS_UINT8       ucReplaceFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetReplaceMmcMsgFlg(VOS_VOID);

NAS_UTRANCTRL_MSG_QUEUE_STRU* NAS_UTRANCTRL_GetCachMsgBufferAddr(VOS_VOID);
VOS_VOID* NAS_UTRANCTRL_GetNextCachBufferMsg(VOS_VOID);
VOS_VOID  NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_UTRANCTRL_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Main(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_SwitchOn(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PowerOff(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_PlmnSelection(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_Syscfg(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_InitFsmCtx_ModeChange(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT8 NAS_UTRANCTRL_GetSearchedSpecTdMccFlg(VOS_VOID);

VOS_UINT32* NAS_UTRANCTRL_GetSpecTdMccList(VOS_VOID);

VOS_UINT8   NAS_UTRANCTRL_GetSpecTdMccListNum(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_SetCurUtranSwitchMode(
    VOS_UINT8                               ucSwitchMode
);

VOS_UINT8 NAS_UTRANCTRL_GetUePcRecurFlg(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SetUePcRecurFlg(
    VOS_UINT8                           ucUePcRecurFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetCurUtranSwitchMode(VOS_VOID);


VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg(VOS_VOID);
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr(VOS_VOID);
VOS_UINT32 NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(VOS_VOID);


/* 搜网状态机上下文操作函数 */
VOS_VOID NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(
    VOS_UINT8       ucAbortFlg
);
VOS_UINT8 NAS_UTRANCTRL_GetAbortFlg_PlmnSelection(VOS_VOID);

VOS_VOID NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(
    VOS_UINT8                           ucRcvMmcAbortFsmReqMsgFlg
);

VOS_UINT8 NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_VOID);


VOS_VOID NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
NAS_UTRANCTRL_ENTRY_MSG_STRU* NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr(VOS_VOID);


NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU* NAS_UTRANCTRL_GetUtranModeAutoSwtich(VOS_VOID);


VOS_UINT8  NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange(VOS_VOID);

VOS_VOID  NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg
);

VOS_VOID  NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(
    VOS_UINT8                           ucWaitUtranModeCnfFlg
);

VOS_VOID  NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange(VOS_VOID);


#endif





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

#endif /* end of NasNAS_UTRANCTRLCtx.h */
