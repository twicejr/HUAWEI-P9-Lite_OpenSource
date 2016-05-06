/******************************************************************************

                  版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtaCommInterface.h
  版 本 号   : 初稿
  作    者   : zwx247453
  生成日期   : 2015年11月02日
  最近修改   :
  功能描述   : AT, MTA与接入层之间公用的接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月02日
    作    者   : zwx247453
    修改内容   : 创建文件

 ******************************************************************************/

#ifndef __MTACOMMINTERFACE_H__
#define __MTACOMMINTERFACE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*network monitor GSM临区 上报最大个数 */
#define NETMON_MAX_GSM_NCELL_NUM                (6)

/*network monitor UTRAN 临区 上报最大个数 */
#define NETMON_MAX_UTRAN_NCELL_NUM              (16)

/*network monitor LTE 临区 上报最大个数 */
#define NETMON_MAX_LTE_NCELL_NUM                (16)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : MTA_RRC_GSM_BAND_ENUM
 结构说明  : MTA模块与GAS之间的BAND值枚举

  1.日    期   : 2014年04月25日
    作    者   : g00261581
    修改内容   : 新增
*****************************************************************************/
enum MTA_RRC_GSM_BAND_ENUM
{
    MTA_RRC_GSM_BAND_850  = 0x00,
    MTA_RRC_GSM_BAND_900,
    MTA_RRC_GSM_BAND_1800,
    MTA_RRC_GSM_BAND_1900,

    MTA_RRC_GSM_BAND_BUTT
};
typedef VOS_UINT16 MTA_RRC_GSM_BAND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : MTA_NETMON_CELL_INFO_TYPE_ENUM
 结构说明  : MTA模块与接入层间的network monitor 查询小区类型枚举定义

  1.日    期   : 2014年11月20日
    作    者   : j00204253
    修改内容   : 新增
*****************************************************************************/
enum MTA_NETMON_CELL_TYPE_ENUM
{
    MTA_NETMON_SCELL_TYPE               = 0,
    MTA_NETMON_NCELL_TYPE               = 1,
    MTA_NETMON_CELL_TYPE_BUTT
};

typedef VOS_UINT32 MTA_NETMON_CELL_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MTA_NETMON_UTRAN_TYPE_ENUM
 结构说明  : MTA模块与接入层间的network monitor UTRAN网络类型枚举定义

  1.日    期   : 2014年11月20日
    作    者   : j00204253
    修改内容   : 新增
*****************************************************************************/
enum MTA_NETMON_UTRAN_TYPE_ENUM
{
    MTA_NETMON_UTRAN_FDD_TYPE           = 0,
    MTA_NETMON_UTRAN_TDD_TYPE           = 1,
    MTA_NETMON_UTRAN_TYPE_BUTT
};
typedef VOS_UINT32 MTA_NETMON_UTRAN_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : MTA_NETMON_RESULT_ENUM
 结构说明  : MTA模块与接入层间的network monitor查询结果的枚举

  1.日    期   : 2014年11月20日
    作    者   : j00204253
    修改内容   : 新增
*****************************************************************************/
enum MTA_NETMON_RESULT_ENUM
{
    MTA_NETMON_RESULT_NO_ERR            = 0,
    MTA_NETMON_RESULT_ERR               = 1,
    MTA_NETMON_RESULT_BUTT
};
typedef VOS_UINT32 MTA_NETMON_RESULT_ENUM_UINT32;

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

/* ========以下是接入层与MTA之间的消息结构体======== */

/**************************network monitor查询临区信息结构体部分**********************************************************/

/* MTA发给接入层的消息，通用，不区分2G/3G/服务小区/邻区 */
/*****************************************************************************
 结构名    : MTA_RRC_NETMON_CELL_QRY_REQ_STRU
 结构说明  : MTA发送给GSM，查询小区信息(包括服务小区和临区)的消息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /* 消息头*/              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /*消息名称*/             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;    /*0:查询服务小区，1:查询临区*/
}MTA_RRC_NETMON_CELL_QRY_REQ_STRU;


/*GSM 临区结构*/
/*****************************************************************************
 结构名    : MTA_NETMON_GSM_NCELL_INFO_STRU
 结构说明  : GSM 临区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBsic     : 1;
    VOS_UINT32                          bitOpCellID   : 1;
    VOS_UINT32                          bitOpLAC      : 1;
    VOS_UINT32                          bitOpSpare    : 29;
    VOS_UINT32                          ulCellID;       /*小区ID*/
    VOS_UINT16                          usLAC;          /*位置区码*/
    VOS_UINT16                          usAfrcn;        /*频点*/
    VOS_INT16                           sRSSI;          /* 频点的RSSI */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;         /* band 0-3 */
    VOS_UINT8                           ucBsic;         /*小区基站码*/
    VOS_UINT8                           aucReserved[3];
}MTA_NETMON_GSM_NCELL_INFO_STRU;


/*LTE 临区结构,暂时定义的数据结构，根据需要进行调整*/
/*****************************************************************************
 结构名    : MTA_NETMON_LTE_NCELL_INFO_STRU
 结构说明  : LTE 临区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPID;            /*物理小区ID*/
    VOS_UINT16                          usArfcn;          /*频点*/
    VOS_INT16                           sRSRP;            /* RSRP参考信号接收功率*/
    VOS_INT16                           sRSRQ;            /* RSRQ参考信号接收质量*/
    VOS_INT16                           sRSSI;            /* Receiving signal strength in dbm */
}MTA_NETMON_LTE_NCELL_INFO_STRU;


/*WCDMA 临区结构*/
/*****************************************************************************
 结构名    : MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU
 结构说明  : WCDMA 临区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;          /*频点*/
    VOS_UINT16                          usPSC;            /*主扰码*/
    VOS_INT16                           sECN0;            /*ECN0*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU;


/*TD_SCDMA 临区结构,暂时定义结构，根据需要继续调整*/
/*****************************************************************************
 结构名    : MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU
 结构说明  : TD_SCDMA 临区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;          /*频点*/
    VOS_UINT16                          usSC;             /*扰码*/
    VOS_UINT16                          usSyncID;         /*下行导频码*/
    VOS_INT16                           sRSCP;            /*RSCP*/
}MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU;


/*临区数据结构*/
/*****************************************************************************
 结构名    : MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU
 结构说明  : network monitor 所有临区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                ucGsmNCellCnt;      /*GSM 临区个数*/
    VOS_UINT8                                ucUtranNCellCnt;    /*WCDMA 临区个数*/
    VOS_UINT8                                ucLteNCellCnt;      /*LTE 临区个数*/
    VOS_UINT8                                ucReserved;
    MTA_NETMON_GSM_NCELL_INFO_STRU           astGsmNCellInfo[NETMON_MAX_GSM_NCELL_NUM];          /*GSM 临区数据结构*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32        enCellMeasTypeChoice;     /* NETMON频率信息类型:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_NCELL_INFO_FDD_STRU astFddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /* FDD临区数据结构 */
        MTA_NETMON_UTRAN_NCELL_INFO_TDD_STRU astTddNCellInfo[NETMON_MAX_UTRAN_NCELL_NUM];         /*  TDD临区数据结构 */
    }u;
    MTA_NETMON_LTE_NCELL_INFO_STRU           astLteNCellInfo[NETMON_MAX_LTE_NCELL_NUM];      /*LTE 临区数据结构*/
}RRC_MTA_NETMON_NCELL_INFO_STRU;


/*********************network monitor查询GSM 小区信息部分************************************************/
/*****************************************************************************
 结构名    : MTA_GRR_NETMON_TA_QRY_REQ_STRU
 结构说明  : MTA发送给GSM，查询TA的消息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /* 消息头 */             /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;     /* 消息名称 */           /*_H2ASN_Skip*/
}MTA_GRR_NETMON_TA_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NETMON_TA_QRY_CNF_STRU
 结构说明  : GAS返回MTA TA查询结果的消息结构体

  1.日    期   : 2014年10月27日
    作    者   : jumingxuan
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* 消息头 */        /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;          /* 消息名称 */      /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;           /* 返回结果 */
    VOS_UINT16                          usTa;               /* 返回的TA值 */
    VOS_UINT8                           aucReserved[2];     /* 四字节对齐的保留位 */
}GRR_MTA_NETMON_TA_QRY_CNF_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NETMON_SCELL_INFO_STRU
 结构说明  : MTA发送ID_MTA_GRR_NETMON_CELL_QRY_REQ给GAS，GAS回复的服务小区信息的结构体

  1.日    期   : 2014年10月27日
    作    者   : w00146666
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;              /* 移动国家码 */
    VOS_UINT32                          ulMnc;              /* 移动网络码 */
    VOS_UINT32                          ulCellID;           /* 小区ID */
    VOS_UINT16                          usLac;              /* 位置区码 */
    VOS_UINT16                          usArfcn;            /* 绝对频点号 */
    VOS_INT16                           sRssi;              /* Receiving signal strength in dbm */
    MTA_RRC_GSM_BAND_ENUM_UINT16        enBand;             /* GSM频段(0-3) */
    VOS_UINT8                           ucBsic;             /* 小区基站码 */
    VOS_UINT8                           ucRxQuality;        /* IDLE态下或者PS数传态下无效,专用态下填充信道质量值，范围[0,7] ,无效值99*/
    VOS_UINT8                           aucReserved[2];     /* 四字节对齐的保留位 */
}GRR_MTA_NETMON_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : GRR_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 结构说明  : MTA发送ID_MTA_GRR_NETMON_CELL_QRY_REQ给GAS，GAS回复消息ID_GRR_MTA_NETMON_CELL_QRY_CNF的结构体

  1.日    期   : 2014年10月27日
    作    者   : w00146666
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /* 消息名称 */          /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32       enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;     /* 0:查询服务小区，1:查询临区 */
    union
    {
        GRR_MTA_NETMON_SCELL_INFO_STRU  stSCellinfo;    /* GSM下的服务小区信息 */
        RRC_MTA_NETMON_NCELL_INFO_STRU  stNCellinfo;    /* GSM下的邻区信息 */
    }u;
}GRR_MTA_NETMON_CELL_QRY_CNF_STRU;

/******************************network monitor查询UTRAN 小区信息部分****************************************************/


/*FDD 服务小区信息结构*/
/*****************************************************************************
 结构名    : MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU
 结构说明  : WCDAM服务小区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDRX      : 1;
    VOS_UINT32                          bitOpURA      : 1;
    VOS_UINT32                          bitOpSpare    : 30;
    VOS_UINT32                          ulDrx;          /* Discontinuous reception cycle length */
    VOS_INT16                           sECN0;          /*ECN0*/
    VOS_INT16                           sRSSI;          /* Receiving signal strength in dbm */
    VOS_INT16                           sRSCP;          /*Received Signal Code Power in dBm，接收信号码功率*/
    VOS_UINT16                          usPSC;          /*主扰码*/
    VOS_UINT16                          usURA;          /* UTRAN Registration Area Identity */
    VOS_UINT8                           aucReserved[2];

} MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU;


/*TDD 服务小区信息结构预留，待确认后填充*/
/*****************************************************************************
 结构名    : MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU
 结构说明  :  TD_SCDAM服务小区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrx;              /* Discontinuous reception cycle length */
    VOS_UINT16                          usSC;               /*扰码*/
    VOS_UINT16                          usSyncID;           /*下行导频码*/
    VOS_UINT16                          usRac;              /*RAC*/
    VOS_INT16                           sRSCP;              /*RSCP*/
} MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU;



 /*UTRAN 服务小区结构*/
 /*****************************************************************************
  结构名    : RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU
  结构说明  : UTRAN服务小区信息结构体

   1.日    期   : 2014年10月27日
     作    者   : j00204253
     修改内容   : 创建
 *****************************************************************************/
typedef struct
{
    VOS_UINT32                                  bitOpCellID  : 1;
    VOS_UINT32                                  bitOpLAC     : 1;
    VOS_UINT32                                  bitOpSpare   : 30;
    VOS_UINT32                                  ulMcc;                  /*移动国家码*/
    VOS_UINT32                                  ulMnc;                  /*移动网络码*/
    VOS_UINT32                                  ulCellID;               /*小区ID*/
    VOS_UINT16                                  usArfcn;                /*频点*/
    VOS_UINT16                                  usLAC;                  /*位置区码*/
    MTA_NETMON_UTRAN_TYPE_ENUM_UINT32           enCellMeasTypeChoice;   /* NETMON频率信息类型:FDD,TDD */
    union
    {
        MTA_NETMON_UTRAN_SCELL_INFO_FDD_STRU    stCellMeasResultsFDD;    /* FDD */
        MTA_NETMON_UTRAN_SCELL_INFO_TDD_STRU    stCellMeasResultsTDD;    /*  TDD */
    }u;
}RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU;


/*****************************************************************************
 结构名    : RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 结构说明  : MTA发送ID_MTA_RRC_NETMON_CELL_QRY_REQ给WAS，WAS回复消息ID_RRC_MTA_NETMON_CELL_QRY_CNF的结构体

  1.日    期   : 2014年10月27日
    作    者   : w00146666
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*消息名称*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:查询服务小区，1:查询临区*/
    union
    {
        RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU  stSCellinfo;      /* UTRAN下的服务小区信息 */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* UTRAN下的邻区信息 */
    }u;
}RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;

/*LTE 服务小区结构*/
/*****************************************************************************
 结构名    : MTA_NETMON_EUTRAN_SCELL_INFO_STRU
 结构说明  : LTE服务小区信息结构体

  1.日    期   : 2014年10月27日
    作    者   : j00204253
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulMcc;                  /*移动国家码*/
    VOS_UINT32                                  ulMnc;                  /*移动网络码*/
    VOS_UINT32                                  ulCellID;               /*小区ID*/
    VOS_UINT32                                  ulPID;                  /*物理小区ID*/
    VOS_UINT16                                  usArfcn;                /*频点*/
    VOS_UINT16                                  usTAC;
    VOS_INT16                                   sRSRP;
    VOS_INT16                                   sRSRQ;
    VOS_INT16                                   sRSSI;
    VOS_UINT8                                   aucReserved[2];
} MTA_NETMON_EUTRAN_SCELL_INFO_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_NETMON_CELL_QRY_REQ_STRU
 结构说明  : MTA发送ID_MTA_LRRC_NETMON_CELL_QRY_REQ给LRR消息结构体

  1.日    期   : 2014年10月27日
    作    者   : w00146666
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */                /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;   /* 消息名称 */             /*_H2ASN_Skip*/
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype;  /* 0：查询服务小区，1：查询临区 */
}MTA_LRRC_NETMON_CELL_QRY_REQ_STRU;

/*****************************************************************************
 结构名    : LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU
 结构说明  : MTA发送ID_MTA_LRRC_NETMON_CELL_QRY_REQ给LRR，WAS回复消息ID_LRRC_MTA_NETMON_CELL_QRY_CNF的结构体

  1.日    期   : 2014年10月27日
    作    者   : w00146666
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /* 消息头*/     /*_H2ASN_Skip*/
    VOS_UINT32                                ulMsgName;        /*消息名称*/    /*_H2ASN_Skip*/
    MTA_NETMON_RESULT_ENUM_UINT32             enResult;
    MTA_NETMON_CELL_TYPE_ENUM_UINT32          enCelltype;       /*0:查询服务小区，1:查询临区*/
    union
    {
        MTA_NETMON_EUTRAN_SCELL_INFO_STRU     stSCellinfo;      /* LTE下的服务小区信息 */
        RRC_MTA_NETMON_NCELL_INFO_STRU        stNCellinfo;      /* LTE下的邻区信息 */
    }u;
}LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU;


/*****************************************************************************
  10 函数声明
*****************************************************************************/

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

#endif /* end of MtaCommInterface.h */
