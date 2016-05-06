/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : PhyGrmInterface.h
  Version     : V100R001
  Date        : 2007-01-135
  Description :
  History     :
  1. Date:2007-01-13
     Author: z47725
     Modification:Create
*******************************************************************************/

#ifndef _PHY_GRM_INTERFACE_H_
#define _PHY_GRM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "EdgeInterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*====================*/ /* 消息ID定义 */
enum GRM_PHY_MSG_ID_ENUM
{
    /* GRM与PHY之间的原语 */
    ID_PHP_UL_START_TIME_IND                = 0x7506,   /*_H2ASN_MSGChoice PHP_START_TIME_IND*/
    ID_PHP_DL_START_TIME_IND                = 0x7501,   /*_H2ASN_MSGChoice PHP_START_TIME_IND*/
    ID_PHP_PACKET_SEND_IND                  = 0x7503,   /*_H2ASN_MSGChoice PHP_PACKET_SEND_IND*/
    ID_PHP_PACKET_DATA_REQ                  = 0x5701,   /*_H2ASN_MSGChoice PHP_PACKET_DATA_REQ*/
    ID_PHP_PACKET_DATA_IND                  = 0x7502,   /*_H2ASN_MSGChoice PHP_PACKET_DATA_IND*/
    ID_PHP_RRBP_FN_REQ                      = 0x5703,   /*_H2ASN_MSGChoice PHP_RRBP_FN_REQ*/
    ID_PHY_RRBP_FN_IND                      = 0x7507,   /*_H2ASN_MSGChoice PHY_RRBP_FN_IND*/
    ID_PHP_RRBP_MSG_REQ                     = 0x5702,   /*_H2ASN_MSGChoice PHP_RRBP_MSG_REQ*/
    ID_PHP_RRBP_MSG_CNF                     = 0x7505,   /*_H2ASN_MSGChoice PHP_RRBP_MSG_CNF*/
    ID_PHP_EGPRS_SRB_REQ                    = 0x5706,   /*EGPRS Srb环回模式时对物理层发送环回请求*/
    ID_PHP_EGPRS_SRB_CNF                    = 0x7508,   /*EGPRS Srb环回模式时，物理层对环回请求的确认*/
    ID_PHP_HARQ_INFO_IND                    = 0x5707,   /*PHP_HARQ_INFO_IND_MSG 通知物理层下行数据块的状态，以便其处理HARQ缓存*/
    ID_PHP_RRBP_MSG_BUTT
};

typedef VOS_UINT16 GRM_PHY_MSG_ID_ENUM_UINT16;


/*====================*/ /* 其他定义 */
#define GRM_BLKDATA_MAX_SIZE                40          /* GRM每个数据块以32比特为单位的个数 */
#define GRM_UL_BSN_CNF_MAX_NUM              8           /* 一次最多确认RLC数据块对应BSN的个数 */

/*物理层新增定位信息，该BSN代表rrbp发送成功*/
#define GRM_BSN_FOR_RRBP                    0x88FF

/*物理层新增定位信息，该BSN代表上行控制块发送成功*/
#define GRM_BSN_FOR_UL_CTRL                 0x66FF

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*================*/ /* 凿孔方式枚举 */
enum PHY_EGPRS_PS_ENUM
{
    PHY_EGPRS_PS_1                          = 0,
    PHY_EGPRS_PS_2                          = 1,
    PHY_EGPRS_PS_3                          = 2,
    PHY_EGPRS_PS_BUTT
};

typedef VOS_UINT16 PHY_EGPRS_PS_ENUM_UINT16;

/* 注意，下面这个定义仅协议栈使用，物理层不能使用UINT8类型 */
typedef VOS_UINT8  PHY_EGPRS_PS_ENUM_UINT8;


/*================*/ /* 错误码枚举 */
enum PHY_ERR_CODE_ENUM
{
    PHY_ERR_CODE_ALL_OK                     = 0,    /*0: 没有错误；*/
    PHY_ERR_CODE_HDR_OK_DATA1_ERR           = 1,    /*1: 头部正确，数据块一错误；*/
    PHY_ERR_CODE_HDR_OK_DATA2_ERR           = 2,    /*2：头部正确，数据块二错误；*/
    PHY_ERR_CODE_HDR_OK_DATA_ALL_ERR        = 3,    /*3：头部正确，数据块全部错误；*/
    PHY_ERR_CODE_ALL_ERR                    = 4     /*4：头部和数据全部错误。*/
};
typedef VOS_UINT16 PHY_ERR_CODE_ENUM_UINT16;

/*================*/ /* 译码类型枚举 */
enum PHY_DECODE_DATA_TYPE_ENUM
{
    PHY_DECODE_DATA_TYPE_NORMAL             = 0,    /*0: 正常译码；*/
    PHY_DECODE_DATA_TYPE_HARQ               = 1,    /*1: HARQ译码；*/
    PHY_DECODE_DATA_TYPE_BUTT               = 2
};
typedef VOS_UINT16 PHY_DECODE_DATA_TYPE_ENUM_UINT16;

enum EDGE_HARQ_DATA_STATUS
{
    EDGE_HARQ_DATA_STATUS_FULL_RXED         = 0,    /* 对应BSN的数据块, 全部译码正确 */
    EDGE_HARQ_DATA_STATUS_NOT_RXED          = 1,    /* 对应BSN的数据块, 没有译码正确 */
    EDGE_HARQ_DATA_STATUS_BUTT
};
typedef VOS_UINT16 EDGE_HARQ_DATA_STATUS_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/
#pragma pack(4)

typedef struct
{
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_MsgChoice_Export      GRM_PHY_MSG_ID_ENUM_UINT16*/
    VOS_UINT16                              usMsgBlock;
    /******************************************************************************************************
        _H2ASN_MsgChoice_When_Comment          GRM_PHY_MSG_ID_ENUM_UINT16
    ******************************************************************************************************/
}GRM_PHY_MSG_DATA;
/*_H2ASN_Length UINT32*/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_DATA                        stMsgData;
}PhyGrmInterface_MSG;

/*================*/ /* PHP_START_TIME_IND消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;            /*_H2ASN_Skip*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;               /* Starting time帧号，GRM根据此帧号决定是激活上行tbf,
                                                                   还是下行tbf，或者是上下行tbf同时激活*/
}PHP_START_TIME_IND;

/*================*/ /* 数据块结构 */
typedef struct
{
    VOS_UINT16                              usBsn1;                             /* EGPRS下指BSN1,GPRS下指BSN */
    VOS_UINT16                              usBsn2;                             /* EGPRS下使用MCS7-MCS9时有效 */
    EDGE_CODE_SCHEME_ENUM_UINT16            enCodeScheme;                       /* 调制和编码方式 */
    PHY_EGPRS_PS_ENUM_UINT16                enPS1;                              /* EGPRS下有效，第一块凿孔方式 */
    PHY_EGPRS_PS_ENUM_UINT16                enPS2;                              /* EGPRS下有效，第二块凿孔方式，只在MCS7-MCS9使用 */
    VOS_UINT16                              usStatusRpt;                        /* 数据块发出后需要向GRR发送的状态报告 */
    VOS_UINT32                              aulBlkData[GRM_BLKDATA_MAX_SIZE];   /* GRPS或EGPRS RLC/MAC块 */
}BLK_ENCODE_DATA_ST;

/*================*/ /* PHP_PACKET_DATA_REQ消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBlkNum;                           /* 发送的数据块数   */
    BLK_ENCODE_DATA_ST                      astBlkData[EDGE_UL_TS_MAX_NUM];
}PHP_PACKET_DATA_REQ;

/*================*/ /* BLK_DECODE_DATA_ST结构 */
typedef struct
{
    VOS_UINT16                              usTN;                               /* 接收数据的时隙号 */
    EDGE_CODE_SCHEME_ENUM_UINT16            enCodeScheme;                       /* 调制和编码方式 */
    PHY_ERR_CODE_ENUM_UINT16                enErrCode;                          /* 0: 没有错误；1:头部正确，数据块一错误；2：头部正确，数据块二错误；3：头部正确，数据块全部错误；4：头部和数据全部错误。目的是为了获取可能的RRBP指示 */
    PHY_DECODE_DATA_TYPE_ENUM_UINT16        enDecodeDataType;                   /* 译码类型枚举,枚举值仅用于低8位,表示译码类型;高8位表示TFI是否匹配.1:是自己的数据,0:不是自己的数据 */
    VOS_UINT32                              aulBlkData[GRM_BLKDATA_MAX_SIZE];   /* GRPS或EGPRS RLC/MAC块*/
}BLK_DECODE_DATA_ST;

/*================*/ /* PHP_RRBP_FN_REQ消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    EDGE_YES_OR_NO_ENUM_UINT16              enRptMeas;                          /* 是否需要上报测量报告 */
    VOS_UINT32                              ulFN;                               /* 发送RRBP消息的块周期的首帧帧号 */
}PHP_RRBP_FN_REQ;

/*================*/ /* PHY_RRBP_FN_IND消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;                               /* 发送RRBP的帧号 */
}PHY_RRBP_FN_IND;


/*================*/ /* PHP_EGPRS_SRB_REQ消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgId;
    VOS_UINT16                              usSrbPara;
}PHP_EGPRS_SRB_REQ;

/*================*/ /* PHP_EGPRS_SRB_CNF消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgId;
    VOS_UINT16                              usRsv;
}PHP_EGPRS_SRB_CNF;

/*================*/ /* PHP_PACKET_SEND_IND_MSG消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    EDGE_YES_OR_NO_ENUM_UINT16              enPrefetchPresent;                  /* Prefetch域是否有效。EDGE_YES:有效，EDGE_NO:无效 */
    VOS_UINT16                              usPrefetchNum;                      /* 预取的块数 */
    EDGE_YES_OR_NO_ENUM_UINT16              enCnfPresent;                       /* cnf域是否有效。EDGE_YES:有效，EDGE_NO:无效 */
    VOS_UINT32                              ulFN;                               /* 数据块发送所在无线块的FN1（即第2帧，帧号按照FN0、FN1、FN2、FN3编号）,不是下一块的FN1 */
    VOS_UINT16                              usCtrlBlkSentNum;                   /* 上一个块周期中， 高8位: 发送RRBP消息的数目; 低8位: 有多少USF用于发送控制消息 */
    VOS_UINT16                              usDataBlkSentNum;                   /* 上一个块周期中，有多少个USF用于发送数据块 */
    VOS_UINT16                              usStatusRpt;                        /* 物理层需要带回的状态报告 */
    VOS_UINT16                              usCnfBsnNum;                        /* 上一个块周期中，发送了多少个RLC PDU，即有多少个BSN */
    VOS_UINT16                              ausCnfBsn[GRM_UL_BSN_CNF_MAX_NUM];  /* 发出的这些RLC块的BSN号 */
}PHP_PACKET_SEND_IND_MSG;

/*================*/ /* PHP_PACKET_DATA_IND_MSG消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBlkNum;                           /* 上报的数据块数 */
    VOS_UINT32                              ulFN;                               /* 接收数据的首帧帧号 */
    BLK_DECODE_DATA_ST                      astBlkData[EDGE_DL_TS_MAX_NUM];
}PHP_PACKET_DATA_IND_MSG;

/*================*/ /* PHP_RRBP_MSG_REQ_MSG消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usTN;                               /* 发送时隙号 */
    VOS_UINT32                              ulFN;                               /* 发送块周期的首帧帧号 */
    PHY_BURST_TPYE_ENUM_UINT16              enBurstType;                        /* RRBP消息块格式类型 */
    GRR_RRBP_CNF_ENUM_UINT16                enRrbpCnf;                          /* 物理层在PHP_RRBP_MSG_CNF消息中将此值带回给GRM，GRM用以判断是否需要给GRR回复 */
    EDGE_YES_OR_NO_ENUM_UINT16              enMeasRpted;                        /* 在RRBP消息中是否发送了测量报告。EDGE_YES:发送了，EDGE_NO:没有发送 */
    EDGE_YES_OR_NO_ENUM_UINT16              enCtrlRrbpMsgFlag;                  /* 是否为控制块RRBP消息标志。EDGE_YES:是，EDGE_NO:否 */
    VOS_UINT16                              ausData[12];                        /* 数据最长为23字节 */
}PHP_RRBP_MSG_REQ_MSG;

/*================*/ /* PHP_RRBP_MSG_CNF_MSG消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    GRR_RRBP_CNF_ENUM_UINT16                enRrbpID;                           /* RRBP消息回复类型，表示是否需要给
                                                                                   GRR回复，此值是在PHP_RRBP_MSG_REQ中带给物理层的 */
    EDGE_CNF_RESULT_ENUM_UINT16             enErrInd;                           /* EDGE_CNF_RESULT_FAIL：表示成功；EDGE_CNF_RESULT_FAIL表示失败；*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulFN;                               /* 发送RRBP的帧号，以便知道是哪一个
                                                                                   RRBP发出去了，方便调试 */
}PHP_RRBP_MSG_CNF_MSG;

/*================*/ /* PHP_HARQ_INFO_IND_MSG 消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    GRM_PHY_MSG_ID_ENUM_UINT16              enMsgID;                            /*_H2ASN_Skip*/
    VOS_UINT16                              usBsn;
    EDGE_HARQ_DATA_STATUS_UINT16            enDataStatus;                       /* 数据块接收情况 */
    VOS_UINT16                              usRsv;
}PHP_HARQ_INFO_IND_MSG;

/****************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#ifdef FEATURE_DSP2ARM
extern VOS_UINT32 GPHY_GetGprsDataBufWriteIdxAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufReadIdxAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufMutexAddr(VOS_VOID);
extern VOS_UINT32 GPHY_GetGprsDataBufAddr(VOS_VOID);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PhyGrmInterface.h*/

