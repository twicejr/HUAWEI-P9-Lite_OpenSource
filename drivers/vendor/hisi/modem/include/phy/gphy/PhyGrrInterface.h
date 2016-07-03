

#ifndef __PHYGRRINTERFACE_H__
#define __PHYGRRINTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif /* __cplusplus */


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "EdgeInterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define GAS_INT_LEVEL_TN_MAX                            8
#define GAS_MAX_TIMESLOT_NUM                            8
#define GAS_GCOMM_MPHP_BA_MEAS_IND_REPORT_NCELL_MAX_NUM 32
#define MPHP_BA_MEAS_IND_REPORT_NCELL_MAX_NUM           32
#define GAS_MAX_HOPPING_FREQUENCY_NUM                   64
#define MPHP_MA_LIST_FREQ_MAX                           64
#define MPHP_INT_MA_CHANNEL_GROUP_MAX_NUM               4     /* 该宏必须与GasGcom.h中的GAS_GCOM_INT_MA_CHANNEL_GROUP_MAX_NUM一致 */
#define MPHP_INT_CHANNEL_GROUP_MAX_NUM                  32    /* 该宏必须与GasGcom.h中的GAS_GCOM_INT_CHANNEL_GROUP_MAX_NUM一致 */
#define GASGRR_PHY_PARAMS_INVALID_VALUE                 0xFF

/*下列宏在适配Moiri的时候专门使用, 因为MPH_ASSIGNMENT_REQ中存在方向指示*/
#define MPHP_ASSIGN_DIRECTION_UL                        0
#define MPHP_ASSIGN_DIRECTION_DL                        1


/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*接口消息ID值定义*/
/* GRR -> PHY 接口消息ID */

typedef enum
{
    /* GRR  --> L1 */
    ID_MPHP_UL_SETUP_REQ                    =   0x4701,         /* _H2ASN_MsgChoice  MPHP_UL_SETUP_REQ_ST */
    ID_MPHP_UL_RECONFIG_REQ                 =   0x4702,         /* _H2ASN_MsgChoice  MPHP_UL_RECONFIG_REQ_ST */
    ID_MPHP_UL_RELEASE_REQ                  =   0x4703,         /* _H2ASN_MsgChoice  MPHP_UL_RELEASE_REQ_ST */
    ID_MPHP_REPEAT_UL_FIXED_ALLOC_REQ       =   0x4704,         /* _H2ASN_MsgChoice  MPHP_REPEAT_UL_FIXED_ALLOC_REQ_ST */
    ID_MPHP_PDCH_RELEASE_REQ                =   0x4705,         /* _H2ASN_MsgChoice  MPHP_PDCH_RELEASE_REQ_ST */
    ID_MPHP_SINGLE_BLOCK_REQ                =   0x4706,         /* _H2ASN_MsgChoice  MPHP_SINGLE_BLOCK_REQ_ST */
    ID_MPHP_RA_REQ                          =   0x4707,         /* _H2ASN_MsgChoice  MPHP_RA_REQ_ST */
    ID_MPHP_RA_ABORT_REQ                    =   0x4708,         /* _H2ASN_MsgChoice  MPHP_RA_ABORT_REQ_ST */
    ID_MPHP_PAGING_MODE_REQ                 =   0x4709,         /* _H2ASN_MsgChoice  MPHP_PAGING_MODE_REQ_ST */
    ID_MPHP_MSGDATA_REQ                     =   0x470a,         /* _H2ASN_MsgChoice  MPHP_MSGDATA_REQ_ST */
    ID_MPHP_TIMING_ADVANCE_REQ              =   0x470b,         /* _H2ASN_MsgChoice  MPHP_TIMING_ADVANCE_REQ_ST */
    ID_MPHP_POWER_PARAM_UPDATE_REQ          =   0x470c,         /* _H2ASN_MsgChoice  MPHP_POWER_PARAM_UPDATE_REQ_ST */
    ID_MPHP_SUSPENSION_REQ                  =   0x470e,         /* _H2ASN_MsgChoice  MPHP_SUSPENSION_REQ_ST */
    ID_MPHP_RESUME_REQ                      =   0x470f,         /* _H2ASN_MsgChoice  MPHP_RESUME_REQ_ST */
    ID_MPHP_MULTI_BLOCK_REQ                 =   0x4710,         /* _H2ASN_MsgChoice  MPHP_MULTI_BLOCK_REQ_ST */
    ID_MPHP_DL_SETUP_REQ                    =   0x4711,         /* _H2ASN_MsgChoice  MPHP_DL_SETUP_REQ_ST */
    ID_MPHP_DL_RECONFIG_REQ                 =   0x4712,         /* _H2ASN_MsgChoice  MPHP_DL_RECONFIG_REQ_ST */
    ID_MPHP_DL_RELEASE_REQ                  =   0x4713,         /* _H2ASN_MsgChoice  MPHP_DL_RELEASE_REQ_ST */
    ID_MPHP_LIMIT_SEND_POWER_REQ            =   0x4715,         /* _H2ASN_MsgChoice  MPHP_LIMIT_SEND_POWER_REQ_ST */
    /* L1 ----> GRR */
    ID_MPHP_UL_SETUP_CNF                    =   0x7401,         /* _H2ASN_MsgChoice  MPHP_UL_SETUP_CNF_ST */
    ID_MPHP_UL_RECONFIG_CNF                 =   0x7402,         /* _H2ASN_MsgChoice  MPHP_UL_RECONFIG_CNF_ST */
    ID_MPHP_UL_RELEASE_CNF                  =   0x7403,         /* _H2ASN_MsgChoice  MPHP_UL_RELEASE_CNF_ST */
    ID_MPHP_REPEAT_UL_FIXED_ALLOC_CNF       =   0x7404,         /* _H2ASN_MsgChoice  MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST */
    ID_MPHP_PDCH_RELEASE_CNF                =   0x7405,         /* _H2ASN_MsgChoice  MPHP_PDCH_RELEASE_CNF_ST */
    ID_MPHP_SINGLE_BLOCK_CNF                =   0x7406,         /* _H2ASN_MsgChoice  MPHP_SINGLE_BLOCK_CNF_ST */
    ID_MPHP_RA_CNF                          =   0x7407,         /* _H2ASN_MsgChoice  MPHP_RA_CNF_ST */
    ID_MPHP_PAGING_MODE_CNF                 =   0x7409,         /* _H2ASN_MsgChoice  MPHP_PAGING_MODE_CNF_ST */
    ID_MPHP_MSGDATA_CNF                     =   0x740a,         /* _H2ASN_MsgChoice  MPHP_MSGDATA_CNF_ST */
    ID_MPHP_TIMING_ADVANCE_CNF              =   0x740b,         /* _H2ASN_MsgChoice  MPHP_TIMING_ADVANCE_CNF_ST */
    ID_MPHP_POWER_PARAM_UPDATE_CNF          =   0x740c,         /* _H2ASN_MsgChoice  MPHP_POWER_PARAM_UPDATE_CNF_ST */
    ID_MPHP_OUT_OF_MEM_IND                  =   0x740d,         /* _H2ASN_MsgChoice  MPHP_OUT_OF_MEM_IND_ST */
    ID_MPHP_SUSPENSION_CNF                  =   0x740e,         /* _H2ASN_MsgChoice  MPHP_SUSPENSION_CNF_ST */
    ID_MPHP_RESUME_CNF                      =   0x740f,         /* _H2ASN_MsgChoice  MPHP_RESUME_CNF_ST */
    ID_MPHP_MULTI_BLOCK_CNF                 =   0x7410,         /* _H2ASN_MsgChoice  MPHP_MULTI_BLOCK_CNF_ST */
    ID_MPHP_DL_SETUP_CNF                    =   0x7411,         /* _H2ASN_MsgChoice  MPHP_DL_SETUP_CNF_ST */
    ID_MPHP_DL_RECONFIG_CNF                 =   0x7412,         /* _H2ASN_MsgChoice  MPHP_DL_RECONFIG_CNF_ST */
    ID_MPHP_DL_RELEASE_CNF                  =   0x7413,         /* _H2ASN_MsgChoice  MPHP_DL_RELEASE_CNF_ST */
    ID_MPHP_LIMIT_SEND_POWER_CNF            =   0x7415,         /* _H2ASN_MsgChoice  MPHP_LIMIT_SEND_POWER_CNF_ST */
    ID_PHY_GRR_MSG_BUTT
}PHY_GRR_MSG_ID_ENUM;

typedef VOS_UINT16 PHY_GRR_MSG_ID_ENUM_UINT16;


/*******************************************************************************
* 跳频模式
*******************************************************************************/
typedef enum
{
    GAS_GRR_PHY_ASSIGN_NO_HOPPING           =   0,
    GAS_GRR_PHY_ASSIGN_HOPPING
}GAS_PHY_HOPPING_MODE_ENUM;

typedef VOS_UINT16 GAS_PHY_HOPPING_MODE_ENUM_UINT16;


/*******************************************************************************
* 恢复物理层的方式
*******************************************************************************/
typedef enum
{
    MPHP_RESUME_IND_NORMAL                  =   0,
    MPHP_RESUME_IND_RELEASE
}GAS_PHY_RESUME_METHOD_ENUM;

typedef VOS_UINT16 GAS_PHY_RESUME_METHOD_ENUM_UINT16;


/*******************************************************************************
* 控制消息的优先级, 0为最高，1次之
*******************************************************************************/
typedef enum
{
    PHY_CTRL_BLK_PRIO_HL                    =   0,
    PHY_CTRL_BLK_PRIO_LL
}GAS_PHY_CTRL_BLK_PRIO_ENUM;

typedef VOS_UINT16 GAS_PHY_CTRL_BLK_PRIO_ENUM_UINT16;

/*******************************************************************************
* 物理层内存指示
*******************************************************************************/
typedef enum
{
    GAS_PHY_ENOUGH_MEM                      =   0,
    GAS_PHY_OUT_OF_MEM
}GAS_PHY_MEM_IND_ENUM;

typedef VOS_UINT16 GAS_PHY_MEM_IND_ENUM_UINT16;

/*******************************************************************************
* EGPRS时多块占用的内存字节数数
*******************************************************************************/
typedef enum
{
    MPHP_NO_MULTI_BLOCK                     =   0,
    MPHP_MULTI_BLOCK_ONE                    =   12,
    MPHP_MULTI_BLOCK_TWO                    =   24
}MPHP_MULTI_BLOCK_LEN_ENUM;

typedef VOS_UINT16 MPHP_MULTI_BLOCK_LEN_ENUM_UINT16;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/
#pragma pack(1)

/*===================================================================*/
typedef struct
{
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_MsgChoice_Export      PHY_GRR_MSG_ID_ENUM_UINT16*/
    VOS_UINT8                               aucMsgBlock[4];
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          PHY_GRR_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/

}PHY_GRR_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    PHY_GRR_MSG_DATA                        stMsgData;
}PhyGrrInterface_MSG;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*******************************************************************************
* MPHP_FREQUENCY_PARAMETERS_ST结构
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usTsc;
    GAS_PHY_HOPPING_MODE_ENUM_UINT16        usHoppingMode;                              /* 是否跳频     */
    VOS_UINT16                              usArfcn;                                    /* 不跳频的频点 */
    VOS_UINT16                              usHsn;                                      /* 跳频序列号   */
    VOS_UINT16                              usMaio;                                     /* 跳频MAIO     */
    VOS_UINT16                              usFreqNum;                                  /* 跳频频点数目 */
    VOS_UINT16                              ausFnList[GAS_MAX_HOPPING_FREQUENCY_NUM];   /* 跳频频点列表 */
}MPHP_FREQUENCY_PARAMETERS_ST;

/*******************************************************************************
* MPHP_DL_RESOURCE_ALLOCATION_ST结构
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usDownlinkTFI;                      /* 下行TBF标识, [0,31] */
    VOS_UINT16                              usDownlinkTNBitmap;                 /* 下行指配时隙位图,Bit7,..bit0表示时隙0..7, 0=未指配, 1=指配 */
}MPHP_DL_RESOURCE_ALLOCATION_ST;

/*******************************************************************************
* MPHP_DYNAMIC_ALLOCATION_ST结构
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usUsfGranularity;                   /* USF粒度  0=1 block, 1=4 block */
    VOS_UINT16                              usRsv;                              /* 四字节对齐 */
    VOS_UINT16                              ausUsf[GAS_MAX_TIMESLOT_NUM];       /* USF表,[0,7],以时隙号0..7做索引，255为无效值 */
}MPHP_DYNAMIC_ALLOCATION_ST;

/*******************************************************************************
* MPHP_FIXED_ALLOCATION_ST结构
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usDownlinkCtrlTn;                       /* 下行控制信道所在时隙 ,[0,7] */
    VOS_UINT16                              usAllocBitmapLen;                       /* 固定指配的位图长度 ,[0,127] */
    VOS_UINT16                              ausAllocBitmap[GAS_MAX_TIMESLOT_NUM];   /* 固定指配的位图 ,以相对StartTime的block为索引 */
}MPHP_FIXED_ALLOCATION_ST;


/*******************************************************************************
* MPHP_MEASUREMENT_MAPPING_ST结构
*******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMeasStartTime;                    /* 指示第一个测量周期的起始时间 */
    VOS_UINT16                              usMeasInterval;                     /* 指示前后两个测量周期的间隔[0, 32 ],单位为 block */
    VOS_UINT16                              usMeasBitMap;                       /* 测量映射的位图,Bit0,..bit7表示时隙0..7，0=用于接收数据，1=用于测量 */
}MPHP_MEASUREMENT_MAPPING_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usMeasEnable;                       /* TBF期间是否需要干扰测量,0=disbale,1=enable */
    VOS_UINT16                              usTimingAdvanceValue;               /* TA, [0,63],255=TA不存在 */
    VOS_UINT16                              usTimingAdvanceIndex;               /* PTCCH索引, [0,15],255=不存在 */
    VOS_UINT16                              usTimingAdvanceTS;                  /* PTCCH时隙,[0,7],255=不存在 */
    VOS_UINT16                              usAlpha;                            /* 用来计算上行发射功率*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* 用于计算上行发射功率,[0,31]*/
    VOS_UINT16                              usBepPeriod2;                       /* 用于计算BEP,[0,15]，无效值为0xFFFF */
    VOS_UINT16                              usBLOCKS_OR_BLOCK_PERIODS;          /* 固定分配bitmap使用的指示,0 bitmap为块数,1 bitmap为块周期数 */
    VOS_UINT16                              usP0;                               /* 下行功控参数,[0,15] ,255=不功控 */
    VOS_UINT16                              usPwrCtlMode;                       /* 下行功控模式,0=mode A,1=mode B */
    VOS_UINT16                              usPrMode;                           /* PR 模式,0=PR Mode A,1=PR mode B */
    VOS_UINT16                              usRsv;                              /* 四字节对齐 */
    VOS_UINT32                              ulTBFStartTime;
    VOS_UINT16                              usUplinkTFI;                        /* 上行TBF标识    [0,31] */
    VOS_UINT16                              usUplinkTNBitmap;                   /* 上行指配时隙位图 Bit7,..bit0表示时隙0..7, 0=未指配, 1=指配 */
    VOS_UINT16                              usTbfMode;                          /* 用于区分当前TBF属于GPRS还是EGPRS TBF,0表示GPRS TBF,1表示EGPRS TBF*/
    GMAC_MODE_ENUM_UINT16                   enAllocationChoice;                 /* 上行指配方式,固定分配,动态分配或动态分配;*//* _H2ASN_IeChoice_Export GMAC_MODE_ENUM_UINT16 */

    union                                                          /* _H2ASN_Skip */
    {                                                              /* _H2ASN_Skip */
        MPHP_FIXED_ALLOCATION_ST            stFixedAllocation;     /* _H2ASN_Skip */
        MPHP_DYNAMIC_ALLOCATION_ST          stDynamicAllocation;
        /******************************************************************************************************
            _H2ASN_IeChoice_When        GMAC_MODE_ENUM_UINT16
        ******************************************************************************************************/
    }u;                                                 /* _H2ASN_Skip */

    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;

}MPHP_UL_SETUP_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usNeedLimitSendPower;               /*1:SIM卡正在复位，需要把最大功率限制在27db;0:不用限制功率*/
}MPHP_LIMIT_SEND_POWER_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usNeedLimitSendPower;               /*1:SIM卡正在复位，需要把最大功率限制在27db;0:不用限制功率*/
}MPHP_LIMIT_SEND_POWER_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    EDGE_CNF_RESULT_ENUM_UINT16             enSucessInd;
}MPHP_UL_SETUP_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usMeasEnable;                       /* TBF期间是否需要干扰测量,0=disbale,1=enable */
    VOS_UINT16                              usTbfMode;                          /* 用于区分当前TBF属于GPRS还是EGPRS TBF,0表示GPRS TBF,1表示EGPRS TBF*/
    VOS_UINT16                              usMeasmentMapPresent;               /* usMeasmentMapPresent是固定模式下使用的参数，目前和以后都不会使用，
                                                                                   现利用这个参数下发RLC模式，0表示AM模式，1表示UM模式 */
    VOS_UINT16                              usTimingAdvanceValue;               /* TA, [0,63],255=TA不存在 */
    VOS_UINT16                              usTimingAdvanceIndex;               /* PTCCH索引, [0,15],255=不存在 */
    VOS_UINT16                              usTimingAdvanceTS;                  /* PTCCH时隙,[0,7],255=不存在 */
    VOS_UINT16                              usAlpha;                            /* 用来计算上行发射功率*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* 用于计算上行发射功率,[0,31]*/
    VOS_UINT16                              usBepPeriod2;                       /* 用于计算BEP */
    VOS_UINT16                              usP0;                               /* 下行功控参数,[0,15] ,255=不功控 */
    VOS_UINT16                              usPwrCtlMode;                       /* 下行功控模式,0=mode A,1=mode B */
    VOS_UINT16                              usPrMode;                           /* PR 模式,0=PR Mode A,1=PR mode B */
    VOS_UINT16                              usControlAck;                       /* ControlAck，可取值 0，1:
                                                                                   1.EVT_MPHP_DL_SETUP_REQ，忽略 ControlAck;
                                                                                   2.EVT_MPHP_DL_RECONFIG_REQ, 1:释放后再建立新的下行TBF, 0:重配置下行TBF*/
    VOS_UINT16                              usLinkQualMeasMode;                 /* 0表示既不报干扰测量，也不报BEP测量
                                                                                   1表示只报干扰测量，不报BEP测量
                                                                                   2表示只报已分配时隙的BEP，不报干扰测量
                                                                                   3表示即报BEP测量，又报干扰测量 */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulTBFStartTime;
    MPHP_DL_RESOURCE_ALLOCATION_ST          stDlResourceAlloc;
    MPHP_MEASUREMENT_MAPPING_ST             stMeasMapping;
}MPHP_DL_SETUP_REQ_ST;


typedef MPHP_DL_SETUP_REQ_ST    MPHP_DL_RECONFIG_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_SETUP_CNF_ST;


typedef MPHP_UL_SETUP_REQ_ST    MPHP_UL_RECONFIG_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_UL_RECONFIG_CNF_ST;

/*******************************************************************************
* MPHP_UL_RELEASE_REQ结构
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16 usRsv;
} MPHP_UL_RELEASE_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_UL_RELEASE_CNF_ST;


typedef MPHP_UL_RELEASE_REQ_ST  MPHP_DL_RELEASE_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_RELEASE_CNF_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_DL_RECONFIG_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                              /* _H2ASN_Skip */ /* 原语类型 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usOperation;
    VOS_UINT16                              usTsOveride;
    VOS_UINT16                              usReserved;
    VOS_UINT32                              ulTBFStartTime;
} MPHP_REPEAT_UL_FIXED_ALLOC_REQ_ST;

/*******************************************************************************
* MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST
*******************************************************************************/

typedef MPHP_UL_SETUP_CNF_ST    MPHP_REPEAT_UL_FIXED_ALLOC_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                  /* _H2ASN_Skip */ /* 原语类型 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usRemainTn;             /* BIT0对应时隙0,BIT7对应时隙7,对应bit为1表示保留对应时隙 */
} MPHP_PDCH_RELEASE_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_PDCH_RELEASE_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usAlpha;                /* 用来计算上行发射功率*/
    VOS_UINT16                              usGammaTn;              /* 用来计算上行发射功率*/
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA不存在 */
    VOS_UINT16                              usDlReceive;            /* 用来指示单块发送后是否需要接收下行PACCH,0不需要，1需要*/
    VOS_UINT16                              usChannelCodingType;    /* 信道编码类型,0:8-bit,1:11-bit,2:23Byte */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulFrameNumber;          /* 发送的帧号 */
    VOS_UINT16                              usTimeSlot;             /* 发送时隙号 */
    VOS_UINT16                              usDataLenth;            /* 发送的数据长度，单位byte */
    VOS_UINT16                              ausData[12];            /* 发送的数据 */

}MPHP_SINGLE_BLOCK_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_SINGLE_BLOCK_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usAlpha;                /* 用来计算上行发射功率*/
    VOS_UINT16                              usGammaTn;              /* 用来计算上行发射功率*/
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA不存在 */
    VOS_UINT16                              usDlReceive;            /* 用来指示单块发送后是否需要接收下行PACCH,0不需要，1需要*/
    VOS_UINT16                              usChannelCodingType;    /* 信道编码类型,0:8-bit,1:11-bit,2:23Byte */
    MPHP_FREQUENCY_PARAMETERS_ST            stFreqParams;
    VOS_UINT32                              ulFrameNumber;          /* 发送的帧号 */
    VOS_UINT16                              usTimeSlot;             /* 发送时隙号 */
    MPHP_MULTI_BLOCK_LEN_ENUM_UINT16        enDataLenth;            /* 发送的数据长度，单位byte */
    VOS_UINT16                              ausData[24];

}MPHP_MULTI_BLOCK_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_MULTI_BLOCK_CNF_ST;


typedef enum
{
    ID_MPHP_PACKET_OTHER_MSG                = 0x0000,
    
    ID_MPHP_PACKET_CELL_CHANGE_FAILURE      = 0x0100,
    ID_MPHP_PACKET_MOBILE_TBF_STATUS        = 0x0106,
    ID_MPHP_PACKET_PSI_STATUS               = 0x0107,
    ID_MPHP_PACKET_CELL_CHANGE_NOTIFICATION = 0x010C,
    ID_MPHP_PACKET_SI_STATUS                = 0x010D
}PHY_GRR_AIR_MSG_TYPE_ENUM;

typedef VOS_UINT16 PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    GAS_PHY_CTRL_BLK_PRIO_ENUM_UINT16       usPrio;             /* 控制消息的优先级 */
    PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16        usAirMsgType;       /* 空口消息类型 */
    VOS_UINT16                              usReserved;
    VOS_UINT16                              ausData[12];
}MPHP_MSGDATA_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    PHY_GRR_AIR_MSG_TYPE_ENUM_UINT16        usAirMsgType;       /* 空口消息类型 */
}MPHP_MSGDATA_CNF_ST;


/*****************************************************************************
* MPHP_SUSPENSION_REQ结构
*******************************************************************************/
typedef MPHP_UL_RELEASE_REQ_ST  MPHP_SUSPENSION_REQ_ST;

/*******************************************************************************
* MPHP_SUSPENSION_CNF结构
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usReserved;
} MPHP_SUSPENSION_CNF_ST;

/*******************************************************************************
* MPHP_RESUME_REQ结构
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    GAS_PHY_RESUME_METHOD_ENUM_UINT16       usResumeInd;        /* 0: 恢复到挂起之前状态,1: 离开挂起, 释放数据传输信道*/
} MPHP_RESUME_REQ_ST;

/*******************************************************************************
* MPHP_RESUME_CNF结构
*******************************************************************************/
typedef MPHP_UL_SETUP_CNF_ST    MPHP_RESUME_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usABType;           /* 接入数据长度,0为8bit，1为11bit */
    VOS_UINT16                              usTsc;              /* 8PSK用TSC1;GMSK用TSC0 */
    VOS_UINT16                              usRachData;         /* 接入请求数据,8bit数据或11bit数据 */
    VOS_UINT16                              usSkipFrames;       /* 发送PRACH前需要等待的帧数数,最大值 217+50,参见44060 Table 12.14.2 */
    VOS_UINT16                              usRsv;              /* 为四字节对齐而添加的保留字 */
}MPHP_RA_REQ_ST;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usAcsBurstType;     /* 接入类型,8bit或11bit */
    VOS_UINT32                              ulFn;               /* 帧号 */
    VOS_UINT16                              usRachData;         /* 接入请求数据,8bit数据或11bit数据 */
    VOS_UINT16                              SuccessInd;         /* 成功标志,0为成功, 1为失败 */
}MPHP_RA_CNF_ST;


typedef enum
{
    PHY_MONI_PAGCH_FLG_NEEDLESS             =   0,
    PHY_MONI_PAGCH_FLG_NEED                 =   1
}PHY_MONI_PAGCH_FLG_ENUM;
typedef VOS_UINT16 PHY_MONI_PAGCH_FLG_ENUM_UINT16;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              enMonitorPagch;     /* 指示PHY是否监听PAGCH,0表示不再监听，1表示继续监听 */
}MPHP_RA_ABORT_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usTimingAdvanceValue;   /* TA, [0,63],255=TA不存在 */
    VOS_UINT16                              usTimingAdvanceIndex;   /* PTCCH索引, [0,15],255=不存在 */
    VOS_UINT16                              usTimingAdvanceTS;      /* PTCCH时隙,[0,7],255=不存在 */
}MPHP_TIMING_ADVANCE_REQ_ST;


typedef MPHP_UL_SETUP_CNF_ST    MPHP_TIMING_ADVANCE_CNF_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usAlpha;                            /* 用来计算上行发射功率*/
    VOS_UINT16                              ausGammaTn[GAS_MAX_TIMESLOT_NUM];   /* 用于计算上行发射功率,[0,31]*/
    VOS_UINT16                              usKTAvgT;                           /* 分组传输模式下功率控制中计算信号强度滤波周期参数 */
    VOS_UINT16                              usKTAvgW;                           /* 分组传输模式下功率控制中计算信号强度滤波周期参数 */
    VOS_UINT16                              usKTAvgI;                           /* 功率控制中计算干扰强度滤波器参数                 */
    VOS_UINT16                              usPcMeasCh;                         /* 测量的信道                                       */
    VOS_UINT16                              usPb;                               /* Pbcch块上相对于BCCH载波的功率减小值              */
    VOS_UINT16                              usReserved;
} MPHP_POWER_PARAM_UPDATE_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                            /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usCause;
} MPHP_POWER_PARAM_UPDATE_CNF_ST;

/*******************************************************************************
* MPHP_ARFCN_CHANNEL_GROUP结构:沿用当前定义
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usTimeSlotAllocation;
}MPHP_ARFCN_CHANNEL_GROUP_ST;

/*******************************************************************************
* MPHP_MA_CHANNEL_GROUP结构:沿用当前定义
*******************************************************************************/
typedef struct
{
    VOS_UINT16                              usHSN;
    VOS_UINT16                              usMAIO;
    VOS_UINT16                              usMaNum;                            /* 频率列表中的频点个数 */
    VOS_UINT16                              ausMaList[MPHP_MA_LIST_FREQ_MAX];
    VOS_UINT16                              usTimeSlotAllocation;
}MPHP_MA_CHANNEL_GROUP_ST;

/*******************************************************************************
* MPHP_INT_MEAS_CHANNEL_LIST结构:沿用当前定义
*******************************************************************************/
typedef struct
{
   VOS_UINT16                               usArfcnChannelGroupNumber;
   MPHP_ARFCN_CHANNEL_GROUP_ST              astArfcnChannelGroupList[MPHP_INT_CHANNEL_GROUP_MAX_NUM];
   VOS_UINT16                               usMaChannelGroupNumber;
   MPHP_MA_CHANNEL_GROUP_ST                 astMaChannelGroupList[MPHP_INT_MA_CHANNEL_GROUP_MAX_NUM];
}MPHP_INT_MEAS_CHANNEL_LIST_ST;


/*******************************************************************************
* MPHP_QUALITY_MEAS_REQ_ST结构: 沿用当前定义
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    MPHP_INT_MEAS_CHANNEL_LIST_ST           stIntMeasChannelList;   /*如果有INT_MEAS_CHANNEL_LIST时的干扰测量信道。*/
    VOS_UINT16                              Reserved;
} MPHP_QUALITY_MEAS_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    GAS_PHY_MEM_IND_ENUM_UINT16             usState;                /* 1表示IR内存不足，0表示退出内存不足状态 */
}MPHP_OUT_OF_MEM_IND_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usPagingMode;           /* 0:Normal;1:Extended;2:ReOrganization;3:Same as before; */
}MPHP_PAGING_MODE_REQ_ST;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* 消息头 */
    PHY_GRR_MSG_ID_ENUM_UINT16              usMsgID;                /*_H2ASN_Skip */ /* 原语类型 */
    VOS_UINT16                              usSuccessInd;
}MPHP_PAGING_MODE_CNF_ST;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/******************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 函数申明
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif /* __cplusplus */


#endif /* __PHY_GRR_INTERFACE_H__ */


