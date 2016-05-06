/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDGFnkG4/S4FxOOB/C/wNlmJJL1crdwYm/aqTyh
1nLqNLiWfZfPAW12dbT6stZWDDWKJoRnOvKlNbnridJHqzGLV/QsEBhxhLC9xnosVNT11er0
hCBdIEHWj9MnyfuwUv4/BlsfWNPrq6awrE3Dv4OYZbczDrCAZ1CF1Jg+QbD6FA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#ifndef __VFMV_CTRL_H__
#define __VFMV_CTRL_H__
#include "vfmw.h"
#include "fsp.h"
#include "sysconfig.h"
#include "syntax.h"

/*======================================================================*/
/*  常数                                                                */
/*======================================================================*/
#define VCTRL_OK                0
#define VCTRL_ERR              -1
#define VCTRL_ERR_VDM_BUSY     -2
#define VCTRL_ERR_NO_FSTORE    -3
#define VCTRL_ERR_NO_STREAM    -4
#define MAX_FRAME_SIZE 			2048*2048

#define VCTRL_FIND_PTS          0
#define VCTRL_PTS_ILLEAGLE     -1
#define VCTRL_SEEKING_PTS      -2

#define VCTRL_USER_OPTION     0
#define VCTRL_ADD_EXTRA        1
#define VCTRL_IGNOR_EXTRA     2

#define MAX_USRDEC_FRAME_NUM        (16)
/*======================================================================*/
/*  结构与枚举                                                          */
/*======================================================================*/
/* 帧存集合，用于调试: 查询有多少帧存，其内容分别为何 */
typedef struct hiVFMWFrameARRAY
{
    SINT32       s32FrameNum;
    SINT32       s32PixWidth;
    SINT32       s32PixHeight;
    SINT32       s32Stride;
    SINT32       s32ChromOfst;
    UADDR        s32PhyAddr[64];
} VFMW_FRAME_ARRAY_S;

/* 通道相关的统计信息 */
typedef struct hiVFMW_CHAN_STAT
{
    UINT32        u32FrBeginTime;   /* 计算帧率的开始时间 */
	UINT32        u32FrImgNum;      /* 帧数 */
	UINT32        u32FrFrameRate;   /* 帧率 */

	/* 丢帧统计 */
	UINT32        u32SkipFind;        /* 解到的skip帧数目 */
	UINT32        u32SkipDiscard;     /* 丢弃不解的skip帧数目 */
    UINT32        u32IsFieldFlag;     /* 当前插入队列中的帧是场图标志，用于PVR快进快退获取码流帧场属性 */
	
    VFMW_FRAME_ARRAY_S stFrameArray;
} VFMW_CHAN_STAT_S;

typedef struct hiVFMW_GLOBAL_STAT
{
    /* VDM占用率统计 */
    UINT32        u32VaBeginTime;     /* 统计VDM占用率的起始时间 */
    UINT32        u32VaLastStartTime; /* 上一次启动硬件的时间 */
	UINT32        u32VaVdmWorkTime;   /* VDM累计工作时间 */
	UINT32        u32VaVdmLoad;       /* VDM占用率 */
    
    /* VDM性能数据统计 */
    UINT32        u32PicNum;
    UINT32        u32AccVdmKiloCycle;
    UINT32        u32VaVdmKiloCycle;
    UINT32        u32StatTime;

	UINT32 	      u32IsVdhEn;
} VFMW_GLOBAL_STAT_S;

/* ArrangeMem函数调用传递的指示符类型 */
typedef enum
{
    CAP_HEVC_SPECIFIC     = -2,
    INVALID_CHAN_ID       = -1,
    VALID_CHAN_ID_START   = 0,
} ARRANGE_FLAG_E;

typedef enum
{
    VDM_SUPPORT_VP6       = 1,   /* 1<<0 */
    VDM_SUPPORT_BPD       = 2,   /* 1<<1 */
    VDM_SUPPORT_VCMP      = 4,   /* 1<<2 */
    VDM_SUPPORT_GMC       = 8,   /* 1<<3 */
} VDM_CHARACTER_E;

/* 线程的状态 */
typedef enum hiTASKSTATE_E
{
    TASK_STATE_EXIT = 0,        /* 退出, 线程未创建或已销毁 */
    TASK_STATE_STOP,            /* 停止，线程已创建，但在空转，解码停止 */
    TASK_STATE_RUNNING,         /* 运行 */
    TASK_STATE_BUTT
} TASK_STATE_E;

/* 对线程发出的指令 */
typedef enum hiTASKCMD_E
{
    TASK_CMD_NONE = 0,        /* 无指令 */
    TASK_CMD_START,           /* 启动指令：启动处于停止状态的线程 */
    TASK_CMD_STOP,            /* 停止指令：停止处于运行状态的线程 */
    TASK_CMD_KILL,            /* 销毁指令：使处于运行或停止状态的线程自然退出 */
    TASK_CMD_BUTT
} TASK_CMD_E;

/* 最后一帧状态跟踪 */
typedef enum hiLastFrameState
{
    LAST_FRAME_INIT = 0,
    LAST_FRAME_RECEIVE,
    LAST_FRAME_REPORT_SUCCESS,
    LAST_FRAME_REPORT_FAILURE,
    LAST_FRAME_REPORT_FRAMEID,
	LAST_FRAME_BUTT
} LAST_FRAME_STATE_E;

/* 通道控制状态 */
typedef enum
{
    CHAN_NORMAL,             //通道正在Run
    CHAN_FRAME_STORE_ALLOC,  //通道正在分配帧存
    CHAN_DESTORY,            //通道正在销毁         
} VFMW_CHANNEL_CONTROL_STATE_E;

typedef enum
{
    FRAME_NODE_STATE_PRE = 0,
    FRAME_NODE_STATE_MMZ,
    FRAME_NODE_STATE_PRE_LOCK,
    FRAME_NODE_STATE_MMZ_LOCK,
    FRAME_NODE_STATE_FREE = 0xFF,
} CHAN_FRAME_NODE_STATE_E;

typedef struct hiDRV_MEM_S
{
    MEM_RECORD_S  stVdmHalMem[MAX_VDH_NUM]; /* VDM 公共内存  */
    MEM_RECORD_S  stScdCmnMem;              /* SCD 公共内存  */
    MEM_RECORD_S  stVdhReg;                 /* 解码器寄存器  */
    MEM_RECORD_S  stExtHalMem;              /* 外部配HAL内存 */
} DRV_MEM_S;

/* 解码器控制数据集 */
typedef struct hiVFMW_CTRL_DATA_S
{
    SINT32        s32IsVCTRLOpen;        /* 标志VCTRL是否被全局打开 */
    SINT32        s32ThreadPos;          /* 线程位置 */
    SINT32        s32ThisChanIDPlus1;    /* 当前正在进行语法解码的通道号 */

    TASK_STATE_E  eTaskState;            /* 线程状态 */
    TASK_CMD_E    eTaskCommand;          /* 线程指令 */
    OSAL_TASK     hThread;               /* 线程句柄 */
    DRV_MEM_S     stDrvMem;
    
    EXT_FN_EVENT_CALLBACK  pfnEventReport_Vdec;
    EXT_FN_EVENT_CALLBACK  pfnEventReport_OmxVdec;
    EXT_FN_POWER_ON        pfnPowerON;
    EXT_FN_POWER_OFF       pfnPowerOFF;
} VFMW_CTRL_DATA_S;

typedef struct hiVFMW_CHAN_FRM_BUF_S
{
    MEM_RECORD_S stFrameBuffer;
    CHAN_FRAME_NODE_STATE_E eBufferNodeState; //0:预分配得到的节点, 1:动态分配得到的节点, 2:预分配且被后继模块占用的节点，3:动态分配且被后继模块占用的节点, 0xFF:空闲节点
} VFMW_CHAN_FRM_BUF_S;

/* 解码通道内存记录 */
typedef struct hiVFMW_CHAN_MEM_S
{
    UINT32         u32DynamicAllocEn;        /* 是否为动态帧存方式 */
    SINT32         s32SelfAllocChanMem_vdh;  /* 标识通道 vdh 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32         s32SelfAllocChanMem_scd;  /* 标识通道 scd 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32         s32SelfAllocChanMem_ctx;  /* 标识通道 ctx 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    MEM_RECORD_S   stChanMem;                /* 该通道的存储资源 */
    MEM_RECORD_S   stChanMem_vdh;            /* 该通道的帧存存储资源 */
    MEM_RECORD_S   stChanMem_scd;            /* 该通道的SCD存储资源 */
    MEM_RECORD_S   stChanMem_ctx;            /* 该通道的上下文存储资源 */ 
    MEM_RECORD_S   stChanMem_dsp;            /* 该通道的dsp上下文存储资源 */
    VFMW_CHAN_FRM_BUF_S* pstChanFrmBuf;
    VFMW_CHAN_FRM_BUF_S* pstChanPmvBuf;
} VFMW_CHAN_MEM_S;

typedef struct hiVFMW_MEM_ARRANGE_INFO_S
{
    VDMHAL_MEM_ARRANGE_S stMemArrange;
    SINT32 ImgSlotLen;
    SINT32 PmvSlotLen;
} VFMW_MEM_ARRANGE_INFO_S;

typedef struct hiVFMW_DYNAMIC_FS_TIMESTAMP_S
{
    UINT32 u32StartTime;
    UINT32 u32AllTime;
} VFMW_DYNAMIC_FS_TIMESTAMP_S;

/* 解码通道 */
typedef struct hiVFMW_CHAN_S
{
    SINT32                        s32ChanID;                /* 通道ID */
    SINT32                        s32IsOpen;                /* 0: 未打开，1: 打开 */
    SINT32                        s32IsRun;                 /* 0: 不被调度, 1: 运行，可被调度  */
    SINT32                        s32Priority;              /* 优先级，0：最低优先级(从不调度) ~ 255(最高优先级，最优先调度) */
    SINT32                        s32StopSyntax;            /* 停掉syntax解码，用于在stop通道的时候先停上游，让下游自由运行，把已生成
                                                               的DecParam消耗干净，从而实现安全的通道stop和reset操作 */
    VID_STD_E                     eVidStd;                  /* 通道对应的协议类型 */
    VDEC_ADAPTER_TYPE_E           eAdapterType;             /* 指示该通道是由vdec/omxvdec创建 */
    VDEC_CHAN_CAP_LEVEL_E         eChanCapLevel;            /* 通道的能力级别 */
    UINT32                        u32timeLastDecParamReady;
	
    VDEC_CHAN_CFG_S               stChanCfg;                /* 保存用户配置，便于查询接口实现 */
    STREAM_INTF_S                 stStreamIntf;             /* 码流接口 */

    SINT32                        s32SCDInstID;             /* 该通道对应的SCD实例ID */
    SINT32                        s32VDMInstID;             /* 该通道对应的VDM实例ID */

    SINT32                        s32OneChanMem;            /*该通道内存由外部分配为一块，映射等操作时需要作为整体来处理*/
    MEM_RECORD_S                  stChanMem;                /* 该通道的存储资源 */

    MEM_RECORD_S                  stChanMem_vdh;            /* 该通道的帧存存储资源 */
    MEM_RECORD_S                  stChanMem_scd;            /* 该通道的SCD存储资源 */
    MEM_RECORD_S                  stChanMem_ctx;            /* 该通道的上下文存储资源 */ 
    
    SINT32                        s32SelfAllocChanMem_vdh;  /* 标识通道 vdh 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32                        s32SelfAllocChanMem_scd;  /* 标识通道 scd 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    SINT32                        s32SelfAllocChanMem_ctx;  /* 标识通道 ctx 是否是自己分配的，1: 自己分配, 0: 外部分配 */
    UADDR                         s32VdmChanMemAddr;
    SINT32                        s32VdmChanMemSize;        /* VDM通道所占据的存储空间大小 */
    UADDR                         s32ScdChanMemAddr;
    SINT32                        s32ScdChanMemSize;        /* SCD通道所占据的存储空间大小 */
    UADDR                         s32BpdChanMemAddr;
    SINT32                        s32BpdChanMemSize;        /* BPD通道所占据的存储空间大小 */
    UADDR                         s32Vp8SegIdChanMemAddr;
    SINT32                        s32Vp8SegIdChanMemSize;   /* SegId通道所占据的存储空间大小 */	
    SINT32                        s32NoStreamFlag;          /* 由于该通道没有足够码流导致未能生成解码参数decparam */
    UINT32                        stRecentImgformat;
    FRAME_PACKING_TYPE_E          stRecentImgPackingType;
    LAST_FRAME_STATE_E            eLastFrameState;          /* 描述最后一帧标记的状态 */
	
    SYNTAX_EXTRA_DATA_S           stSynExtraData;
    SM_INSTANCE_S                 SmInstArray;
    FSP_INST_S                    FspInst;

    /* 动态帧存相关 */
    UINT32                        u32CurFrameWidth; 
    UINT32                        u32CurFrameHeight; 
    SINT32                        s32RefFrameNum; 
    SINT32                        s32RefFrameSize;
    SINT32                        s32RefPmvSize; 
    SINT32                        s32ActualFrameNum;
    VFMW_CHAN_FRM_BUF_S           stFrmBuf[MAX_FRAME_NUM];
	VFMW_CHAN_FRM_BUF_S           stPmvBuf[MAX_FRAME_NUM];
    VFMW_MEM_ARRANGE_INFO_S       stMemArrangeInfo;
    VFMW_DYNAMIC_FS_TIMESTAMP_S   stDynamicFSTimestamp;
    
    /*此成员必须放在最后一个定义,创建通道时即使mvc support，但是配置的能力集不是mvc相关的，
      该结构体内存也只分配次大的CTX所需，以达到内存裁剪目的。 l00225186*/
    SYNTAX_CTX_S                  stSynCtx;

} VFMW_CHAN_S;

/* 线程的状态 */
typedef enum hiDSPSTATE_E
{
    DSP_STATE_NORMAL = 0,      /* DSP 还没有加载任何代码  */
    DSP_STATE_SCDLOWDLY,       /* DSP 已经加载了SCD低延的代码，说明已有一个通道处于低延迟模式 */
    DSP_STATE_AVS,             /* DSP 已经加载了AVS+的代码，说明已有一个通道正在跑AVS协议 */
    DSP_STATE_BUTT
} DSP_STATE_E;

/*======================================================================*/
/*  全局变量                                                            */
/*======================================================================*/
extern SINT32             g_VdmCharacter;
extern VFMW_CHAN_STAT_S   g_VfmwChanStat[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern VDM_VERSION_E      g_eVdmVersion;

/*======================================================================*/
/*  函数申明                                                            */
/*======================================================================*/
SINT32 VCTRL_SetCallBack(VDEC_ADAPTER_TYPE_E type, INIT_INTF_S *pIntf);
VOID   VCTRL_PowerOn(VOID);
VOID   VCTRL_PowerOff(VOID);
SINT32 VCTRL_StopTask(VOID);
SINT32 VCTRL_StartTask(VOID);
SINT32 VCTRL_OpenDrivers(DRV_MEM_S *pstDrvMem);
SINT32 VCTRL_CloseDrivers(DRV_MEM_S *pstDrvMem);
SINT32 VCTRL_OpenVfmw(VDEC_OPERATION_S *pArgs);
SINT32 VCTRL_CloseVfmw(VOID);
VOID   VCTRL_Suspend(VOID);
VOID   VCTRL_Resume(VOID);
SINT32 VCTRL_CreateChan(VDEC_CHAN_CAP_LEVEL_E eCapLevel, MEM_DESC_S *pChanMem);
SINT32 VCTRL_CreateChanWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, SINT32 flag, SINT32 OneChanMemFlag);
SINT32 VCTRL_DestroyChan(SINT32 ChanID);
SINT32 VCTRL_DestroyChanWithOption(SINT32 ChanID);
SINT32 VCTRL_StartChan(SINT32 ChanID);
SINT32 VCTRL_StopChan(SINT32 ChanID);
SINT32 VCTRL_StopChanWithCheck(SINT32 ChanID);
SINT32 VCTRL_GetChanCfg(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_CmpConfigParameter(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
VOID   VCTRL_GetVdecCapability(VDEC_CAP_S *pCap);
SINT32 VCTRL_ConfigChan(SINT32 ChanID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 VCTRL_ResetChanWithOption(SINT32 ChanID, VDEC_CHAN_RESET_OPTION_S *pOption);
SINT32 VCTRL_ReleaseStream(SINT32 ChanID);
SINT32 VCTRL_ResetChan(SINT32 ChanID);
SINT32 VCTRL_GetChanMemSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32 *VdmMemSize, SINT32 *ScdMemSize);
VOID   VCTRL_GetChanState(SINT32 ChanID, VDEC_CHAN_STATE_S *pstChanState);
SINT32 VCTRL_SetStreamInterface( SINT32 ChanID, VOID *pIntf );
SINT32 VCTRL_GetChanMemSizeWithOption(VDEC_CHAN_CAP_LEVEL_E eCapLevel, VDEC_CHAN_OPTION_S *pChanOption, DETAIL_MEM_SIZE *pDetailMemSize,SINT32 flag);
VOID   VCTRL_GetChanCtxSize(VDEC_CHAN_CAP_LEVEL_E eCapLevel, SINT32* s32ChanCtxSize);
SINT32 VCTRL_GetStreamSize(SINT32 ChanID, SINT32 *pArgs);
VOID*  VCTRL_GetDecParam(SINT32 ChanId);
VOID   VCTRL_VdmPostProc( SINT32 ChanId, SINT32 ErrRatio, UINT32 Mb0QpInCurrPic, LUMA_INFO_S *pLumaInfo,SINT32 VdhId);
SINT32 VCTRL_GetChanImage( SINT32 ChanID, IMAGE *pImage );
SINT32 VCTRL_ReleaseChanImage( SINT32 ChanID, IMAGE *pImage );
SINT32 VCTRL_RunProcess(VOID);
VOID   VCTRL_InformVdmFree(SINT32 ChanID);
SINT32 VCTRL_GetImageBuffer( SINT32 ChanId );
SINT32 VCTRL_GetChanIDByCtx(VOID *pCtx);
SINT32 VCTRL_IsChanDecable( SINT32 ChanID );
SINT32 VCTRL_IsChanSegEnough( SINT32 ChanID );
SINT32 VCTRL_IsChanActive( SINT32 ChanID );
VOID   VCTRL_GetChanImgNum( SINT32 ChanID, SINT32 *pRefImgNum, SINT32 *pReadImgNum, SINT32 *pNewImgNum );
SINT32 VCTRL_SetMoreGapEnable(SINT32 ChanID, SINT32 MoreGapEnable);
VOID   VCTRL_MaskAllInt(VOID);
VOID   VCTRL_EnableAllInt(VOID);
SINT32 VCTRL_SetDbgOption ( UINT32 opt, UINT8* p_args );
SINT32 VCTRL_GetChanWidth(SINT32 ChanID);
SINT32 VCTRL_GetChanHeight(SINT32 ChanID);
VOID   VCTRL_SetLastFrameState(SINT32 ChanID, LAST_FRAME_STATE_E eState);       
SINT32 VCTRL_OutputLastFrame(SINT32 ChanId);  
SINT32 VCTRT_SetChanCtrlState(SINT32 ChanID, VFMW_CHANNEL_CONTROL_STATE_E ChanCtrlState);
VOID   VCTRL_SetChanFsPartitionState(SINT32 ChanID, FSP_PARTITION_STATE_E state);
SINT32 VCTRL_RlsAllFrameNode(SINT32 ChanID);
VOID   VCTRL_SetFsParamToChan(SINT32 ChanID, VDEC_CHAN_FRAME_STORES* stParams); 
VOID   VCTRL_OpenHardware(SINT32 ChanID);
VOID   VCTRL_CloseHardware(VOID);

VID_STD_E              VCTRL_GetVidStd(SINT32 ChanId);
STREAM_INTF_S*         VCTRL_GetStreamInterface(SINT32 ChanID);
VDEC_CHAN_CAP_LEVEL_E  VCTRL_GetChanCapLevel(SINT32 ChanID);
IMAGE_VO_QUEUE*        VCTRL_GetChanVoQue(SINT32 ChanID);

#if defined(VFMW_SCD_LOWDLY_SUPPORT) || defined(VFMW_AVSPLUS_SUPPORT)
SINT32 VCTRL_LoadDspCode(SINT32 ChanID);
#endif

#ifdef ENV_ARMLINUX_KERNEL
VOID   VCTRL_WriteYuv_Linear( OSAL_FILE *fpYuv, UADDR YPhyAddr, UADDR CPhyAddr, UINT32 Width, UINT32 Height,  UINT32 Stride, UINT32 chroma_idc);
VOID   VCTRL_WriteYuv_Tile( OSAL_FILE *fpYuv, UADDR YPhyAddr, UADDR CPhyAddr, UINT32 Width, UINT32 Height, UINT32 PicStructure, UINT32 Stride, UINT32 chroma_idc, UINT32 LeftOffset,UINT32 RightOffset,UINT32 TopOffset,UINT32 BottomOffset);
#endif

#endif

