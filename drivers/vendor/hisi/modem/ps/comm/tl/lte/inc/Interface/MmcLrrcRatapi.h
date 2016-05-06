
#ifndef __MMCLRRCRATAPI_H__
#define __MMCLRRCRATAPI_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/




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
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/* Max num of CDMA PNs configured by LTE for SIB8 measurements per band. it shall be 16*/
#define MMC_MAX_SIB8_REC_NUM            (7)     /* limited by hw */

/* Max number of CDMA PNs being configured by LTE for measurement. From 36.331, it shall be 32*/
#define MMC_MAX_NUM_MEAS_CDMA_PN        (7)  /* limited by hw */

/*Maximum number of entries in each of the cell lists in a measurement object, it's 32 in TS 36.331*/
#define MMC_MAX_CELL_MEAS_NUM           (7)

/* Max num of PLMNs configured by CDMA for LTE neighboring cell measurements*/
#define MMC_MAX_NUM_EUTRA_PLMN          (8)

/* Max num of measurement stop commands sent by LTE to stop ongoing IRAT measurements.
At any point of time there could be either 2 SIB8 based or 1 IRAT based meas may be ongoing.
This needs to be increased in order to support more RATs in later phases of MMC */
#define MMC_MAX_NUM_MEAS_STOP           (2)

/* Max number of CDMA BANDs being configured by LTE for SIB8 measurement. From 36.331, it shall be 32*/
#define MMC_MAX_NUM_SIB8_CDMA_BAND      (3)     /* limited by hw */


#define MMC_RAT_API_BASE    0x0400
/* The invalid value macro of the U8,U16 and U32 data type*/
#define INVALID_U8                      (0xff)
#define INVALID_U16                     (0xffff)
#define INVALID_U32                     (0xffffffff)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum CL_BOOL_ENUM
{
    CL_FALSE                            = 0,
    CL_TRUE                             = 1,
    CL_BOOL_BUTT
};
typedef VOS_UINT8   CL_BOOL_ENUM_UINT8;

typedef enum
{
  UTRA_FDD,
  UTRA_TDD
}UTRANCELLTYPE_ENUM/* UtranCellTypeT */;
typedef VOS_UINT8 UTRANCELLTYPE_ENUM_UINT8;

typedef enum
{
  GERAN_DCS1800,
  GERAN_PCS1900
}GERANBANDIND_ENUM/* GeranBandIndT */;
typedef VOS_UINT8 GERANBANDIND_ENUM_UINT8;

typedef enum
{
  EXPLICIT_ARFCN,
  EQUALLY_SPACED,
  VARIABLE_BITMAP
}GERANARFCNTYPE_ENUM/* GeranArfcnTypeT */;
typedef VOS_UINT8 GERANARFCNTYPE_ENUM_UINT8;

typedef enum
{
   MBW6,
   MBW15,
   MBW25,
   MBW50,
   MBW70,
   MBW100
}EUTRANBANDWIDTH_ENUM/* EutranBandWidthT */;
typedef VOS_UINT8 EUTRANBANDWIDTH_ENUM_UINT8;

typedef enum
{
   MMC_IRAT_1XRTT = 0,
   MMC_IRAT_HRPD,
   MMC_IRAT_NULL
}MMCCDMATYPE_ENUM;/* MmcCdmaTypeT */
typedef VOS_UINT8 MMCCDMATYPE_ENUM_UINT8;

typedef enum
{
   MMC_SYSTEM_CDMA = 0,
   MMC_SYSTEM_UTRAN,
   MMC_SYSTEM_GERAN,
   MMC_SYSTEM_EUTRAN,
   MMC_SYSTEM_INVALID
}MMCSYSTEMTYPE_ENUM;/* MmcSystemTypeT */
typedef VOS_UINT8 MMCSYSTEMTYPE_ENUM_UINT8;

typedef enum
{
   MMC_RAT_NULL,
   MMC_CDMA2K1X = 2,   /* 1X */
   MMC_GERAN,          /* GSM */
   MMC_CDMA2KHRPD,     /* DO */
   MMC_UTRAN,          /* 3GPP */
   MMC_CDMA2KAI,       /*1X&DO, for matching type MMSS_SYS_CDMA2000_AI*/
   MMC_EUTRAN = 9,     /* LTE */
   MMC_3GPPAI,         /* GSM&UMTS&LTE, for matching type MMSS_SYS_3GPP_AI*/
   MMC_RAT_NUM
}MMCRATID_ENUM;/* MmcRatIdT */
typedef VOS_UINT8 MMCRATID_ENUM_UINT8;

typedef enum
{
   MMC_REDIRECTION=0,
   MMC_RESELECTION,
   MMC_CELLCHANGEORDER,
   MMC_HANDOVER,
   MMC_HO_INVALID
}MMCIRATHOCAUSE_ENUM;/* MmcIratHOCauseT */
typedef VOS_UINT8 MMCIRATHOCAUSE_ENUM_UINT8;
typedef enum
{
   MMC_IRAT=0,
   MMC_SIB8,
   MMC_CMD_INVALID
}MMCSTOPCMDTYPE_ENUM;/* MmcStopCmdTypeT */
typedef VOS_UINT8 MMCSTOPCMDTYPE_ENUM_UINT8;

typedef enum
{
   MMC_CDMA_MEAS_SUCCESS= 0,   /* Measurement completed successfully */
   MMC_CDMA_MEAS_1X_ONCALL,    /* Measurement failed since 1xRTT is on call */
   MMC_CDMA_ACQ_FAIL,          /* Measurement failed since system could not be acquired from the specified channels */
   MMC_CDMA_EMPTY_PNLIST,      /* Measurement failed since the PN list of all channels specified were empty */
   MMC_CDMA_BAND_NOT_SUPPORT,  /* Measurement failed since all the bands specified are not supported */
   MMC_CDMA_MEAS_FAIL          /* Measurement failed for other reasons */
}MMCCDMAMEASRESULT_ENUM;/* MmcCdmaMeasResultT */
typedef VOS_UINT8 MMCCDMAMEASRESULT_ENUM_UINT8;

typedef enum
{
   MMC_MEAS_RES_SUCCESS= 0,        /* Measurement completed successfully */
   MMC_MEAS_RES_ACQ_FAIL,          /* Measurement failed since system could not be acquired from the specified channels */
   MMC_MEAS_RES_BAND_NOT_SUPPORT,  /* Measurement failed since all the bands specified are not supported */
   MMC_MEAS_REG_FAIL,               /* Measurement failed for other reasons */
   MMC_MEAS_CMD_INVALID  /*invalid command*/
}MMCMEASRESULTSTATUS_ENUM;/* MmcMeasResultStatusT */
typedef VOS_UINT8  MMCMEASRESULTSTATUS_ENUM_UINT8;

typedef enum
{
  MMC_IRAT_SUCCESS=0,        /* Success */
  MMC_IRAT_ACQ_FAIL,         /* System could not be acquired */
  MMC_IRAT_PS_REG_FAIL,      /* PS registration failed on the system */
  MMC_IRAT_PS_SESSION_FAIL,  /* PS session could not be opened on the system */
  MMC_IRAT_FAIL,              /* Failure due to other unknown reasons */
  MMC_IRAT_CMD_INVALID,  /*invalid command*/
  MMC_IRAT_HRPD_SUCCESS    /* System Change to HRPD Success */
}MMCRATSTATUS_ENUM;/* MmcRatStatusT */
typedef VOS_UINT8 MMCRATSTATUS_ENUM_UINT8;


enum MMCRATAPIID_ENUM
{
    RAT_MMC_API_POWERUP_REQ = MMC_RAT_API_BASE,
    RAT_MMC_API_POWERDOWN_REQ,
    RAT_MMC_API_RAT_ONLY_MODE_REQ,
    RAT_MMC_API_RAT_3GPP_MODE_REQ,
    RAT_MMC_API_ACQ_REQ,
    RAT_MMC_API_MCC_SEARCH_REQ,
    RAT_MMC_API_PS_REG_REQ,
    RAT_MMC_API_NO_SERVICE_REQ,
    RAT_MMC_API_CELL_GLOBAL_ID_RSP,
    RAT_MMC_API_DATACONNECTION_CMD_REQ,
    RAT_MMC_API_DEFAULTBEARER_REQ,
    RAT_MMC_API_DEDICATEDBEARER_REQ,
    RAT_MMC_API_BEARER_DISCONNECT_REQ,
    RAT_MMC_API_BEARER_DETACH_REQ,
    RAT_MMC_API_IRAT_MEAS_IND,
    RAT_MMC_API_IRAT_SYSTEM_CHG_RSP,
    RAT_MMC_API_IRAT_SIB8_MEAS_IND,  /* _H2ASN_MsgChoice RATMMCAPI_IRAT_SIB8_MEAS_IND_STRU */

    RAT_MMC_API_RAT_MEASCMD,

    RAT_MMC_API_RAT_RESELMEASCMD,

    RAT_MMC_API_STOP_IRAT_RATMEAS_CMD,

    RAT_MMC_API_CELL_INFO_PS_REG_REQ,
    RAT_MMC_API_CDMA_TXPWR_RSP,
    RAT_MMC_API_IRAT_RESELMEAS_IND,
    RAT_MMC_API_IRAT_HANDOVER_RSP,
    RAT_MMC_API_RAT_HANDOVER_PS_REG_REQ,
    RAT_MMC_API_SET_IDLEMODEMOBILITYINFO,
    RAT_MMC_API_PACKET_STATISTICS_RSP,
    RAT_MMC_API_PDN_TABLE_SETUP_REQ,
    RAT_MMC_API_RAT_MODE_REQ,
    RAT_MMC_API_CMD_MAX,

    MMC_RAT_API_POWERUP_RSP = (MMC_RAT_API_BASE + 0x80),
    MMC_RAT_API_POWERDOWN_RSP,
    MMC_RAT_API_CMD_REJ_IND,
    MMC_RAT_API_RAT_ONLY_MODE_RSP,
    MMC_RAT_API_RAT_3GPP_MODE_RSP,
    MMC_RAT_API_ACQ_RSP,
    MMC_RAT_API_MCC_SEARCH_RSP,
    MMC_RAT_API_PS_REG_RSP,
    MMC_RAT_API_NO_SERVICE_RSP,
    MMC_RAT_API_NWT_ST_CHG_IND,
    MMC_RAT_API_CELL_GLOBAL_ID_REQ,
    MMC_RAT_API_DATACONNECTION_CMD_RSP,
    MMC_RAT_API_DEFAULTBEARER_RSP,
    MMC_RAT_API_DEDICATEDBEARER_IND,
    MMC_RAT_API_DEDICATEDBEARER_RSP,
    MMC_RAT_API_BEARER_DISCONNECT_RSP,
    MMC_RAT_API_BEARER_DISCONNECT_IND,
    MMC_RAT_API_BEARER_DETACH_RSP,
    MMC_RAT_API_IRAT_MEAS_CMD,
    MMC_RAT_API_IRAT_SYSTEM_CHG_REQ,
    MMC_RAT_API_IRAT_SIB8_MEAS_CMD,
    MMC_RAT_API_RAT_MEASIND,
    MMC_RAT_API_RAT_RESELMEASIND,
    MMC_RAT_API_STOP_IRAT_MEAS_CMD,
    MMC_RAT_API_CELL_INFO_PS_REG_RSP,
    MMC_RAT_API_CDMA_TXPWR_REQ,
    MMC_RAT_API_RAT_HANDOVER_PS_REG_RSP,
    MMC_RAT_API_IRAT_HANDOVER_REQ,
    MMC_RAT_API_IRAT_RESELMEAS_CMD,
    MMC_RAT_API_SET_IDLEMODEMOBILITYINFO,
    MMC_RAT_API_PACKET_STATISTICS_REQ,
    MMC_RAT_API_PDN_TABLE_SETUP_RSP,
    MMC_RAT_API_MODE_RSP,
    MMC_RAT_API_IRAT_SYSTEM_CHG_ABORT_CMD,
    MMC_RAT_API_LOOKBACK_TEST_REQ = (MMC_RAT_API_BASE + 0xcc),
    MMC_RAT_API_CMD_MAX
};
typedef VOS_UINT16 MMCRATAPIID_ENUM_UINT16;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    MMCRATAPIID_ENUM_UINT16             enCmmcaCmdId;
    VOS_UINT8                           aucMsg[2];
}CMMCA_MSG_DATA_STRU;

/* MmcMeasObjectCdma_Rpc_T */
typedef struct
{
   MMCCDMATYPE_ENUM_UINT8               enType;    /* Type of the CDMA system, 1xRTT or HRPD */
  VOS_UINT16                            usCellToReportCGI;  /* cell which need acquire CGI. 0xffff means not specified */

   VOS_UINT8                            ucBand;              /* Contains CDMA band for which this measurement result is valid */
   VOS_UINT16                           usChannel;          /* Contains CDMA channel for which this measurement result is valid */
   VOS_UINT8                            ucSearchWinSize;     /* Contains CDMA pilot search window size */
   VOS_UINT8                            ucNumPn;             /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_NUM_MEAS_CDMA_PN */
   VOS_UINT16                           ausPilot[MMC_MAX_NUM_MEAS_CDMA_PN]; /* List of CDMA pilots to be measured. Total number of elements in Pilot[] shall not exceed NumPn */
} MMCMEASOBJECTCDMA_RPC_STRU;

/* UtranCellsList_Rpc_T */
typedef struct
{
  VOS_UINT8                             uccellIndex;       /*index of cell, (1-MMC_MAX_CELL_MEAS_NUM)*/
  VOS_UINT16                            usphysCellId;    /*physical layer identity of the cell, FDD is (0-511), TDD is (0-125)*/
}UTRANCELLSLIST_RPC_STRU;

/* UtranCellToRptCgi_Rpc_T */
typedef struct
{
  VOS_UINT16                            usphysCellId; /*physical layer identity of the cell, FDD is (0-511), TDD is (0-125).*/
}UTRANCELLTORPTCGI_RPC_STRU;

/* MmcMeasObjectUtran_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  VOS_UINT16                            usArfcn;                 /*UTRAN carrier frequency, 0-16383*/
  VOS_UINT16                            usoffsetFreq;            /*Q-OffsetRangeInterRAT, default 0*/
  UTRANCELLTYPE_ENUM_UINT8              encellType;
  VOS_UINT8                             uccellNum;               /*number of UTRAN cells*/
  UTRANCELLSLIST_RPC_STRU               astcellList[MMC_MAX_CELL_MEAS_NUM];
  CL_BOOL_ENUM_UINT8                    enbCgiRpt;  /*if false, CellToReportCgi is ignored*/
  UTRANCELLTORPTCGI_RPC_STRU            stCellToReportCGI; /*This parameter is for CGI. It indicates the cell which needs to acquire CGI.*/
}MMCMEASOBJECTUTRAN_RPC_STRU;

/* ExplicitListOfArfcn_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucnum;  /*number of following words sizes*/
  VOS_UINT16                            ausArfcn[32]; /*the remaining ARFCN values in the set are explicitly listed one by one*/
} EXPLICITLISTOFARFCN_RPC_STRU;

/* EquallySpacedArfcn_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucArfcnSpacing;  /*Space d, between a set of equally spaced ARFCN value, 1-9*/
  VOS_UINT8                             ucnumOfFollowingArfcn; /*the number of the remaining equally spaced ARFCN values in the set, 0-31*/
}EQUALLYSPACEDARFCN_RPC_STRU;

/* VariablebitMapOfArfcn_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucnum;  /*following octet size,(1-16)*/
  VOS_UINT8                             aucBitMapOfArfcn[16]; /*Bitmap field representing the remaining ARFCN values in the set.
                                                    The leading bit of the first octet in the bitmap corresponds to the ARFCN = ((s + 1) mod 1024),
                                                    the next bit to the ARFCN = ((s + 2) mod 1024), and so on. If the bitmap consist of N octets,
                                                    the trailing bit of octet N corresponds to ARFCN = ((s + 8*N) mod 1024).
                                                    The complete set of ARFCN values consists of ARFCN = s and the ARFCN values,
                                                    where the corresponding bit in the bitmap is set to "1".*/
}VARIABLEBITMAPOFARFCN_RPC_STRU;

/* GeranArfcnInfo_Rpc_T */
typedef union
{
  EXPLICITLISTOFARFCN_RPC_STRU          stExplicitListOfArfcn;
  EQUALLYSPACEDARFCN_RPC_STRU           stEquallySpacedArfcn;
  VARIABLEBITMAPOFARFCN_RPC_STRU        stVariableBitMapofArfcn;
}GERANARFCNINFO_RPC_STRU;

/* GeranCarrierFreqs_Rpc_T */
typedef struct
{
  VOS_UINT16                            usStartingArfcn;   /*the first ARFCN value, (0-1023)*/
  GERANBANDIND_ENUM_UINT8               enBandIndicator;   /*indicates how to interpret ARFCN of the BCCH carrier*/
  GERANARFCNTYPE_ENUM_UINT8             enArfcnType;
  GERANARFCNINFO_RPC_STRU               stArfcnInfo;
}GERANCARRIERFREQS_RPC_STRU;

/* GeranPhysCellId_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucNwColourCode;   /*3 bits,network colour code as defined in TS 23.003*/
  VOS_UINT8                             ucBsColourCode;   /*3 bits, Base station Colour Code as defined in TS 23.003*/
}GERANPHYSCELLID_RPC_STRU;

/* MmcMeasObjectGeran_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  GERANCARRIERFREQS_RPC_STRU            stCarrierInfo;
  VOS_UINT16                            usoffseFreq;          /*Q-OffsetRangeInterRAT, default 0*/
  VOS_UINT8                             ucnccPermit; /*default 0xf. Field encoded as a bit map, where bit N is set to "0" if a BCCH carrier with NCC = N-1 is not permitted for monitoring and set to "1" if a BCCH carrier with NCC = N-1 is permitted for monitoring; N = 1 to 8; bit 1 of the bitmap is the leading bit of the bit string.*/
  CL_BOOL_ENUM_UINT8                    enbCgiRpt;  /*if false, CellToReportCgi is ignored*/
  GERANPHYSCELLID_RPC_STRU              stCellToReportCgi;
}MMCMEASOBJECTGERAN_RPC_STRU;

/* EutranMeasCellInfo_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucCellIndex;   /*1-MMC_MAX_CELL_MEAS_NUM*/
  VOS_UINT16                            usphysCellId;  /*physical cell id, 0-503*/
  //VOS_UINT8    QOffsetRange;/*db-24=0, db-22=1,etc*/
}EUTRANMEASCELLINFO_RPC_STRU;

/* MmcMeasObjectEutran_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  VOS_UINT16                            usEarfcn;                 /*EUTRAN carrier frequency, 0-65535*/
  VOS_UINT8                             ucneighCellConfig;   /*2 bits, Provides information related to MBSFN and TDD UL/DL configuration of neighbour cells of this frequency*/
  EUTRANBANDWIDTH_ENUM_UINT8            enBandWidth;
  VOS_UINT8                             ucNum;                   /*number of EUTRAN cell*/
  EUTRANMEASCELLINFO_RPC_STRU           astCellInfo[MMC_MAX_CELL_MEAS_NUM];
}MMCMEASOBJECTEUTRAN_RPC_STRU;

/* MmcMeasObjectParam_Rpc_T */
typedef  union
{
    MMCMEASOBJECTCDMA_RPC_STRU          stMeasObjectCdma;   /* Measurement parameters corresponding to CDMA system */
    MMCMEASOBJECTUTRAN_RPC_STRU         stMeasObjectUtran; /* Measurement parameters corresponding to UTRAN system. To be defined in later phase */
    MMCMEASOBJECTGERAN_RPC_STRU         stMeasObjectGeran; /* Measurement parameters corresponding to GERAN system. To be defined in later phase */
    MMCMEASOBJECTEUTRAN_RPC_STRU        stMeasObjectEutran; /* Measurement parameters corresponding to GERAN system. To be defined in later phase */
} MMCMEASOBJECTPARAM_RPC_UNION;

/* MmcMeasObjectInfo_Rpc_T */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enMeasObjectType;  /* Contains type of the system to which measurement object belongs */
   VOS_UINT32                           ulPeriod;          /* Periodicity of measurements for this measure object. Unit is in milliseconds (ms). A value of 0 means one time measurement */
   MMCMEASOBJECTPARAM_RPC_UNION         unMeasObjectParam; /* Contains measurement results corresponding to the system specified by MeasResultType */
} MMCMEASOBJECTINFO_RPC_STRU;

/* MmcMeasObjectConfig_Rpc_T */
typedef  struct
{
    VOS_UINT8                           ucMeasObjectNum;      /* Number of measurement objects included in MeasObjectInfo  max 3 paper3.2.1.4 page 21*/
    MMCMEASOBJECTINFO_RPC_STRU          astMeasObjectInfo[1];  /*Contains information about interRAT measurement objects as received from E-UTRAN */
} MMCMEASOBJECTCONFIG_RPC_STRU;

/* MmcRatAPI_IRAT_Meas_CmdT */
typedef  struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   MMCMEASOBJECTCONFIG_RPC_STRU         stMeasObjectConfig;
} MMCRATAPI_IRAT_MEAS_CMD_STRU;

/* MmcRatAPI_IRAT_Meas_Stop_CmdT */
typedef  struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
} MMCRATAPI_IRAT_MEAS_STOP_CMD_STRU;

/* MmcCarrierInfoCdma_Rpc_T */
typedef struct
{
   MMCCDMATYPE_ENUM_UINT8               enType;               /* Type of the CDMA system, 1xRTT or HRPD */
   VOS_UINT8                            ucBand;               /* Contains CDMA band information */
   VOS_UINT16                           usChannel;            /* Contains CDMA channel information */
   VOS_UINT8                            ucNumPn;              /* Number of CDMA PNs included. It shall be set to 0x00 if "Cause" of the system change is REDIRECTION.Max valid value is 16*/
   VOS_UINT16                           ausPn[MMC_MAX_SIB8_REC_NUM]; /* CDMA pilot PN list. It shall be set to Pn received in IratCdmaPilotMeasResultT of LteMmcAPI_IRAT_SIB8_Meas_Ind
                                       for which cell reselection criteria has met. Total number of elements shall not exceed NumPn*/
} MMCCARRIERINFOCDMA_RPC_STRU;

/* PlmnId_Rpc_T */
typedef struct
{
  VOS_UINT16                            usMcc;  /*3 digits*/
  VOS_UINT16                            usMnc;  /*2-3 digits*/
}PLMNID_RPC_STRU;

/* UtranCellGlobalId_Rpc_T */
typedef struct
{
  PLMNID_RPC_STRU                       stPlmnId;
  VOS_UINT32                            ulCellId;   /*28 bits*/
}UTRANCELLGLOBALID_RPC_STRU;

/* MmcCarrierInfoUtran_Rpc_T */
typedef struct
{
  VOS_UINT16                            usArfcn;   /*UTRAN carrier frequency,(0-16383)*/
  UTRANCELLTYPE_ENUM_UINT8              encellType;/*FDD=0, TDD=1*/
  VOS_UINT16                            usphysCellId;/*FDD(0-511), TDD(0-127)*/
  UTRANCELLGLOBALID_RPC_STRU            stcellGlobalId;
  VOS_UINT16                            uslocationAreaCode;
  VOS_UINT8                             ucroutingAreaCode;
  CL_BOOL_ENUM_UINT8                    enbNeedConn;
} MMCCARRIERINFOUTRAN_RPC_STRU;

/* GeranCarrierFreq_Rpc_T */
typedef struct
{
  VOS_UINT16                            usArfcn;  /*0-1023*/
  GERANBANDIND_ENUM_UINT8               enBandIndicator;
}GERANCARRIERFREQ_RPC_STRU;

/* GeranCellGlobalId_Rpc_T */
typedef struct
{
  PLMNID_RPC_STRU                       stPlmnId;
  VOS_UINT16                            uslocationAreaCode; /*16 bits*/
  VOS_UINT16                            uscellId;              /*16 bits*/
}GERANCELLGLOBALID_RPC_STRU;

/* GeranCgiInfo_Rpc_T */
typedef struct
{
  GERANCELLGLOBALID_RPC_STRU            stCellGlobalId;
  VOS_UINT8                             ucroutingAreacode;/*The RAC identity read from broadcast information, as defined in TS 23.003*/
}GERANCGIINFO_RPC_STRU;

/* MmcCarrierInfoGeran_Rpc_T */
typedef struct
{
  GERANCARRIERFREQ_RPC_STRU             stCarrierInfo;
  GERANPHYSCELLID_RPC_STRU              stPhysCellId;
  GERANCGIINFO_RPC_STRU                 stCgiInfo;
} MMCCARRIERINFOGERAN_RPC_STRU;

/* MmcCarrierInfoEutran_Rpc_T */
typedef struct
{
  VOS_UINT16                            usEarfcn;
  VOS_UINT8                             ucNumCell;
  VOS_UINT16                            ausCellId[MMC_MAX_NUM_EUTRA_PLMN];
  VOS_UINT8                             ucNumPlmn;
  VOS_UINT32                            aulPlmnId[MMC_MAX_NUM_EUTRA_PLMN];
} MMCCARRIERINFOEUTRAN_RPC_STRU;

/* MmcCarrierInfoParam_Rpc_T */
typedef union
{
   MMCCARRIERINFOCDMA_RPC_STRU          stCarrierInfoCdma;  /* Contains carrier and channel information of CDMA system */
   MMCCARRIERINFOUTRAN_RPC_STRU         stCarrierInfoUtran;        /* Contains carrier and channel information of UTRAN system. To be defined in later phase */
   MMCCARRIERINFOGERAN_RPC_STRU         stCarrierInfoGeran;       /* Contains carrier and channel information of GERAN system. To be defined in later phase */
   MMCCARRIERINFOEUTRAN_RPC_STRU        stCarrierInfoEutran;       /* Contains carrier and channel information of EUTRAN system. To be defined in later phase */
} MMCCARRIERINFOPARAM_RPC_STRU;

/* MmcTargetSystemCarrierInfo_Rpc_T */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enTargetSystemType;    /* Type of the system to which CarrierInfoParam belongs */
   MMCCARRIERINFOPARAM_RPC_STRU         stCarrierInfoParam; /* Contains carrier and channel information of the system specified in TargetSystemType */
} MMCTARGETSYSTEMCARRIERINFO_RPC_STRU;

/* MmcSystemChangeReq_Rpc_T */
typedef struct
{
   MMCIRATHOCAUSE_ENUM_UINT8            enCause;                             /* Cause of the system change request from LTE to other RAT */
   MMCTARGETSYSTEMCARRIERINFO_RPC_STRU  stTargetSystemCarrierInfo; /* Contains target system type and frequency information to which system change is requested */
} MMCSYSTEMCHANGEREQ_RPC_STRU;

/* MmcRatAPI_IRAT_System_Change_ReqT */
typedef struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   MMCSYSTEMCHANGEREQ_RPC_STRU          stSystemChangeReq;
} MMCRATAPI_IRAT_SYSTEM_CHANGE_REQ_STRU;

/* MmcSystemChangeReq_Rpc_T */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enTargetSystemType;        /* Type of the system to which CarrierInfoParam belongs */
   VOS_UINT32                           ulReason; /* Reason of abort for currently ongoing system change */
} MMCSYSTEMCHANGEABORTREQ_RPC_STRU;

/* MmcRatAPI_IRAT_System_Change_Abort_CmdT */
typedef struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   MMCSYSTEMCHANGEABORTREQ_RPC_STRU     stSystemChangeStopReq;
} MMCRATAPI_IRAT_SYSTEM_CHANGE_ABORT_REQ_STRU;

/* MmcSIB8MeasCellList_Rpc_T */
typedef struct
{
  VOS_UINT16                            usCellToReportCGI;  /* cell which need acquire CGI. 0xffff means not specified */

  VOS_UINT8                             ucBand;            /* Contains CDMA band for which this measurement info is valid */
  VOS_UINT16                            usChannel;        /* Contains CDMA channel for which this measurement info is valid */
  VOS_UINT8                             ucCellReselPri;    /* Cell reselection priority of the band. 0xFF means not provided */
  VOS_UINT8                             ucNumPn;           /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_SIB8_REC_NUM */
  VOS_UINT16                            ausPn[MMC_MAX_SIB8_REC_NUM]; /* List of CDMA PNs to be measured. Total number of elements shall not exceed NumPn */
} MMCSIB8MEASCELLLIST_RPC_STRU;

/* MmcSIB8MeasInfo_Rpc_T */
typedef struct
{
  MMCCDMATYPE_ENUM_UINT8                enType;      /* Type of the CDMA system, 1xRTT or HRPD */
  VOS_UINT8                             ucSearchWinSize;     /* CDMA pilot search window size */
  VOS_UINT8                             ucListSize;          /* Number of CDMA cells included in CellList. Shall not exceed MMC_MAX_NUM_SIB8_CDMA_BAND */
  MMCSIB8MEASCELLLIST_RPC_STRU          astCellList[1];  /* List of CDMA cells as received in "neighCellList" of SIB8 from E-UTRAN. Total number of elements in CellList[] shall not exceed ListSizecell info list */
} MMCSIB8MEASINFO_RPC_STRU;

/* MmcRatAPI_IRAT_SIB8_Meas_CmdT */
typedef  struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   VOS_UINT32                           ulPeriod; /* */
   MMCSIB8MEASINFO_RPC_STRU             stIratSIB8MeasInfo;
} MMCRATAPI_IRAT_SIB8_MEAS_CMD_STRU;

/* MmcStopIratMeasCmdRec_Rpc_T */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enStopMeasRATType;    /* Type of the system to whichStop Cmd belongs */
   MMCSTOPCMDTYPE_ENUM_UINT8            enStopCmdType;        /* Type of the measurements which needs to be stopped */
   MMCCDMATYPE_ENUM_UINT8               enCDMANwType;         /* Type of the CDMA system, 1xRTT or HRPD. This param is valid only if StopMeasRATType is SystemCDMA
                                                        else this parameter shall be set to IRAT_NULL */
} MMCSTOPIRATMEASCMDREC_RPC_STRU;

/* MmcStopIratMeasCmd_Rpc_T */
typedef struct
{
   VOS_UINT8                            ucNumRec; /* Number of elements in StopIratMeasCmdRec[]. Shall not exceed MMC_MAX_NUM_MEAS_STOP */
   MMCSTOPIRATMEASCMDREC_RPC_STRU       astStopIratMeasCmdRec[MMC_MAX_NUM_MEAS_STOP]; /* Info about other RATs on which meas shall be stopped. Elements in StopIratMeasCmdRec[] shall not exceed NumRec */
} MMCSTOPIRATMEASCMD_RPC_STRU;

/* MmcRatAPI_Stop_IRAT_Meas_CmdT */
typedef struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   MMCSTOPIRATMEASCMD_RPC_STRU          stStopIratMeasCmd;
} MMCRATAPI_STOP_IRAT_MEAS_CMD_STRU;

/* MmcCdmaPilotMeasResult_Rpc_T */
typedef struct
{
   VOS_UINT16                           usPn;         /* pilot PN */
   VOS_INT16                            sPhase;       /* CDMA pilot phase, in chips */
   VOS_INT8                             cStrength;     /* CDMA pilot strength in -0.5 dB format */
} MMCCDMAPILOTMEASRESULT_RPC_STRU;

/*MmcMeasResultCdma_Rpc_T*/
typedef struct
{
  VOS_UINT8                             ucCgiAvl;  /* 0 - can't acquire CGI.  1 - CGI available */
  VOS_UINT8                             aucCgi[16];  /* EVDO cell sectorID */

   MMCCDMAMEASRESULT_ENUM_UINT8         enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_CDMA_MEAS_SUCCESS */
   MMCCDMATYPE_ENUM_UINT8               enType;    /* Type of the CDMA system, 1xRTT or HRPD */
   VOS_UINT16                           usChannel;          /* Contains CDMA channel for which this measurement result is valid */
   VOS_UINT8                            ucBand;              /* Contains CDMA band for which this measurement result is valid */
   VOS_UINT8                            ucNumPn;             /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_NUM_MEAS_CDMA_PN */
   MMCCDMAPILOTMEASRESULT_RPC_STRU      astPilot[MMC_MAX_NUM_MEAS_CDMA_PN]; /* List of CDMA pilot results. Total number of elements in Pilot[] shall not exceed NumPn */
} MMCMEASRESULTCDMA_RPC_STRU;

/* UtranCgiInfo_Rpc_T */
typedef struct
{
  UTRANCELLGLOBALID_RPC_STRU            stCellGlobalId;
  VOS_UINT16                            uslocationAreaCode;/*16 bits. A fixed length code identifing the location area within a PLMN, as defined in TS23.003.*/
  VOS_UINT8                             ucroutingAreaCode; /*8 bits. The RAC identity read from broadcast information, as defined in TS23.003.*/
  VOS_UINT8                             ucPlmnNum;
  PLMNID_RPC_STRU                       astPlmnList[5];
}UTRANCGIINFO_RPC_STRU;

/* UtranMeasResult_Rpc_T */
typedef struct
{
  VOS_INT8                              cRscp; /*According to CPICH_RSCP in TS25.133 for FDD and P-CCPCH_RSCP in TS25.123 for TDD. 31 spare values. (-5-91)*/
  VOS_UINT8                             ucEcNo; /*According to CPICH_Ec/No for TDD. 14 spare values. (0-49) The field is ignored for TDD*/
}UTRANMEASRESULT_RPC_STRU;

/* MmcMeasResultUtran_Rpc_T */
typedef struct
{
  MMCMEASRESULTSTATUS_ENUM_UINT8        enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_MEAS_SUCCESS */
  VOS_UINT8                             ucMeasObjId; /*measurement object configuration id same as in MeasObjectConfigT*/
  VOS_UINT16                            usArfcn;   /*UTRAN carrier frequency,(0-16383)*/
  UTRANCELLTYPE_ENUM_UINT8              enCellType;
  VOS_UINT16                            usphysCellId; /*physical layer identity of the cell, FDD is (0-511), TDD is (0-127)*/
  UTRANCGIINFO_RPC_STRU                 stCgiInfo;
  UTRANMEASRESULT_RPC_STRU              stMeasResult;
} MMCMEASRESULTUTRAN_RPC_STRU;

/* GeranMeasResult_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucRssi; /*GERAN Carrier RSSI. RXLEV is mapped to a value between 0 and 63, TS45.008. When mapping the RXLEV value to the RSSI bit string,the first/leftmost bit of the bit string contains the most significant bit. (0-63)*/
}GERANMEASRESULT_RPC_STRU;

/* MmcMeasResultGeran_Rpc_T */
typedef struct
{
  MMCMEASRESULTSTATUS_ENUM_UINT8        enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_MEAS_SUCCESS */
  VOS_UINT8                             ucMeasObjId; /*measurement object configuration id same as in MeasObjectConfigT*/
  GERANCARRIERFREQ_RPC_STRU             stCarrierFreq;
  GERANPHYSCELLID_RPC_STRU              stPhysCellId;
  GERANCGIINFO_RPC_STRU                 stCgiInfo;
  GERANMEASRESULT_RPC_STRU              stMeasResult;
} MMCMEASRESULTGERAN_RPC_STRU;

/* EutranCgiInfo_Rpc_T */
typedef struct
{
  UTRANCELLGLOBALID_RPC_STRU            stCellGlobalId;
  VOS_UINT16                            usTrackingAreaCode; /*16 bits*/
  VOS_UINT8                             ucPlmnNum;
  PLMNID_RPC_STRU                       astPlmnList[MMC_MAX_NUM_EUTRA_PLMN];
}EUTRANCGIINFO_RPC_STRU;

/* EutranMeasResult_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucRsrp; /*(0..97).Measured RSRP result of an E UTRA cell.The rsrpResult is only reported if configured by the eNB */
  VOS_UINT8                             ucRsrq; /*(0..34).Measured RSRQ result of an E UTRA cell.The rsrqResult is only reported if configured by the eNB*/
} EUTRANMEASRESULT_RPC_STRU;

/* MmcMeasResultEutran_Rpc_T */
typedef struct
{
  MMCMEASRESULTSTATUS_ENUM_UINT8        enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_MEAS_SUCCESS */
  VOS_UINT8                             ucMeasObjId; /*measurement object configuration id same as in MeasObjectConfigT*/
  VOS_UINT16                            usEarfcn;    /*0-65535*/
  VOS_UINT16                            usPhysCellId; /*physical layer identity of the cell, FDD is (0-511), TDD is (0-127)*/
  EUTRANCGIINFO_RPC_STRU                stCgiInfo;
  EUTRANMEASRESULT_RPC_STRU             stMeasResult;
} MMCMEASRESULTEUTRAN_RPC_STRU;

/* MmcMeasResultData_Rpc_T */
typedef union
{
   MMCMEASRESULTCDMA_RPC_STRU           stMeasResultCdma; /* Measurement results corresponding to CDMA system */
   MMCMEASRESULTUTRAN_RPC_STRU          stMeasResultUtran;    /* Measurement results corresponding to UTRAN system */
   MMCMEASRESULTGERAN_RPC_STRU          stMeasResultGeran;    /* Measurement results corresponding to GERAN system */
   MMCMEASRESULTEUTRAN_RPC_STRU         stMeasResultEutran;    /* Measurement results corresponding to EUTRAN system */
} MMCMEASRESULTDATA_RPC_UNION;

/* MmcMeasResult_Rpc_T */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enMeasResultType;  /* Contains type of the system to which measurement results belong */
   MMCMEASRESULTDATA_RPC_UNION          unMeasResultData; /* Contains measurement results corresponding to the system specified by MeasResultType */
} MMCMEASRESULT_RPC_STRU;

/* MmcMeasObjectResult_Rpc_T */

#define MMC_MAX_NUM_MEAS_OBJ          3
typedef struct
{
   VOS_UINT8                            ucMeasResultNum;                             /* Number of measurement results included in MeasResult. Max value shall not exceed MMC_MAX_NUM_MEAS_OBJ */
   MMCMEASRESULT_RPC_STRU               astMeasResult[MMC_MAX_NUM_MEAS_OBJ];  /* Contains interRAT measurement results. Total number of elements in MeasResult[] shall not exceed MeasResultNum */
} MMCMEASOBJECTRESULT_RPC_STRU;


/* RatMmcAPI_IRAT_Meas_IndT  */
typedef struct
{
   /* MmcRatId_Enum_Uint8 */
   MMCRATID_ENUM_UINT8                  enRatId;

   VOS_UINT16                           usMsgLength;
   /* MmcMeasObjectResult_Rpc_T */
   MMCMEASOBJECTRESULT_RPC_STRU         stMeasObjectResult;
} RATMMCAPI_IRAT_MEAS_IND_STRU;

/* MmcSystemChangeRsp_Rpc_T */
typedef struct
{
   MMCRATSTATUS_ENUM_UINT8              enResult;       /* Contains status of interRAT system change */
   MMCIRATHOCAUSE_ENUM_UINT8            enCause;
} MMCSYSTEMCHANGERSP_RPC_STRU;

/* RatMmcAPI_IRAT_System_Change_RspT*/
typedef struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   MMCSYSTEMCHANGERSP_RPC_STRU          stSystemChangeRsp;
} RATMMCAPI_IRAT_SYSTEM_CHANGE_RSP_STRU;

/* MmcSIB8MeasResultRec_Rpc_T */
typedef struct
{
  VOS_UINT8                             ucCgiAvl;  /* 0 - CGI is invalid.  1 - CGI is valid */
  VOS_UINT8                             aucCgi[16];  /* EVDO cell sectorID */

  VOS_UINT8                             ucBand;            /* Contains CDMA band for which this measurement result is valid */
  VOS_UINT16                            usChannel;        /* Contains CDMA channel for which this measurement result is valid */
  VOS_UINT8                             ucNumPn;           /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_SIB8_REC_NUM */
  MMCCDMAPILOTMEASRESULT_RPC_STRU       astPilot[MMC_MAX_SIB8_REC_NUM]; /* CDMA pilot measure result */
} MMCSIB8MEASRESULTREC_RPC_STRU;

/* MmcMeasSIB8MeasResultData_Rpc_T */
typedef struct
{
  MMCCDMAMEASRESULT_ENUM_UINT8          enResult; /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_CDMA_MEAS_SUCCESS */
  MMCCDMATYPE_ENUM_UINT8                enType;       /* Type of the CDMA system, 1xRTT or HRPD */
  VOS_UINT8                             ucListSize;            /* Number of CDMA band results included in CellList. Shall not exceed MMC_MAX_NUM_SIB8_CDMA_BAND */
  MMCSIB8MEASRESULTREC_RPC_STRU         astCellList[1];  /* CDMA SIB8 measurement result list. One element per CDMA band */
} MMCMEASSIB8MEASRESULTDATA_RPC_STRU;

/* RatMmcAPI_IRAT_SIB8_Meas_IndT */
typedef struct
{
   MMCRATID_ENUM_UINT8                  enRatId;
   VOS_UINT16                           usMsgLength;
   MMCMEASSIB8MEASRESULTDATA_RPC_STRU   stMeasSIB8MeasResultData;
} RATMMCAPI_IRAT_SIB8_MEAS_IND_STRU;
/*===========  MeasObjectUtranT ==============*/

/* UtranCellsListT */
typedef struct
{
  VOS_UINT8                             ucCellIndex;       /*index of cell, (1-MMC_MAX_CELL_MEAS_NUM)*/
  VOS_UINT16                            usPhysCellId;    /*physical layer identity of the cell, FDD is (0-511), TDD is (0-125)*/
}UTRAN_CELLSLIST_STRU;

/* UtranCellToRptCgiT */
typedef struct
{
  VOS_UINT16                            usPhysCellId; /*physical layer identity of the cell, FDD is (0-511), TDD is (0-125).*/
}UTRAN_CELLTORPTCGI_STRU;

/* MmcMeasObjectUtranT */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  VOS_UINT16                            usArfcn;                 /*UTRAN carrier frequency, 0-16383*/
  VOS_UINT16                            usoffsetFreq;            /*Q-OffsetRangeInterRAT, default 0*/
  UTRANCELLTYPE_ENUM_UINT8              enCellType;
  VOS_UINT8                             ucCellNum;               /*number of UTRAN cells*/
  UTRAN_CELLSLIST_STRU                  astCellList[MMC_MAX_CELL_MEAS_NUM];
  CL_BOOL_ENUM_UINT8                    enCgiRpt;  /*if false, CellToReportCgi is ignored*/
  UTRAN_CELLTORPTCGI_STRU               stCellToReportCGI; /*This parameter is for CGI. It indicates the cell which needs to acquire CGI.*/
}MMC_MEAS_OBJECT_UTRAN_STRU;

/* ExplicitListOfArfcnT */
typedef struct
{
  VOS_UINT8                             ucNum;  /*number of following words sizes*/
  VOS_UINT16                            ausArfcn[32]; /*the remaining ARFCN values in the set are explicitly listed one by one*/
} EXPLICITLIST_OF_ARFCN_STRU;

/* EquallySpacedArfcnT */
typedef struct
{
  VOS_UINT8                             ucArfcnSpacing;  /*Space d, between a set of equally spaced ARFCN value, 1-9*/
  VOS_UINT8                             ucNumOfFollowingArfcn; /*the number of the remaining equally spaced ARFCN values in the set, 0-31*/
}EQUALLY_SPACED_ARFCN_STRU;

/* VariablebitMapOfArfcnT */
typedef struct
{
  VOS_UINT8                             ucNum;  /*following octet size,(1-16)*/
  VOS_UINT8                             ucBitMapOfArfcn[16]; /*Bitmap field representing the remaining ARFCN values in the set.
                                              The leading bit of the first octet in the bitmap corresponds to the ARFCN = ((s + 1) mod 1024),
                                              the next bit to the ARFCN = ((s + 2) mod 1024), and so on. If the bitmap consist of N octets,
                                              the trailing bit of octet N corresponds to ARFCN = ((s + 8*N) mod 1024).
                                              The complete set of ARFCN values consists of ARFCN = s and the ARFCN values,
                                              where the corresponding bit in the bitmap is set to "1".*/
}VARIABLE_BITMAP_OF_ARFCN_STRU;

/* GeranArfcnInfoT */
typedef union
{
  EXPLICITLIST_OF_ARFCN_STRU            stExplicitListOfArfcn;
  EQUALLY_SPACED_ARFCN_STRU             stEquallySpacedArfcn;
  VARIABLE_BITMAP_OF_ARFCN_STRU         stVariableBitMapofArfcn;
}GERAN_ARFCN_INFO_UNION;

/* GeranCarrierFreqsT */
typedef struct
{
  VOS_UINT16                            usStartingArfcn;   /*the first ARFCN value, (0-1023)*/
  GERANBANDIND_ENUM_UINT8               enBandIndicator;   /*indicates how to interpret ARFCN of the BCCH carrier*/
  GERANARFCNTYPE_ENUM_UINT8             enArfcnType;
  GERAN_ARFCN_INFO_UNION                unArfcnInfo;
}GERAN_CARRIER_FREQ_STRU;

/* GeranPhysCellIdT */
typedef struct
{
  VOS_UINT8                             ucNwColourCode;   /*3 bits,network colour code as defined in TS 23.003*/
  VOS_UINT8                             ucBsColourCode;   /*3 bits, Base station Colour Code as defined in TS 23.003*/
}GERAN_PHYSCELLID_STRU;

/* MmcMeasObjectGeranT */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  GERAN_CARRIER_FREQ_STRU               stCarrierInfo;
  VOS_UINT16                            usOffseFreq;          /*Q-OffsetRangeInterRAT, default 0*/
  VOS_UINT8                             ucNccPermit; /*default 0xf. Field encoded as a bit map, where bit N is set to "0" if a BCCH carrier with NCC = N-1 is not permitted for monitoring and set to "1" if a BCCH carrier with NCC = N-1 is permitted for monitoring; N = 1 to 8; bit 1 of the bitmap is the leading bit of the bit string.*/
  CL_BOOL_ENUM_UINT8                    enCgiRpt;  /*if false, CellToReportCgi is ignored*/
  GERAN_PHYSCELLID_STRU                 stCellToReportCgi;
}MMC_MEASOBJECT_GERAN_STRU;

/*===========  MeasObjectEutranT ==============*/
/* EutranMeasCellInfoT */
typedef struct
{
  VOS_UINT8                             ucCellIndex;   /*1-MMC_MAX_CELL_MEAS_NUM*/
  VOS_UINT16                            usPhysCellId;  /*physical cell id, 0-503*/
 /* VOS_UINT8    QOffsetRange;db-24=0, db-22=1,etc*/
}EUTRAN_MEAS_CELLINFO_STRU;

/* MmcMeasObjectEutranT */
typedef struct
{
  VOS_UINT8                             ucMeasObjId;             /*Identify a meaurement object configuration*/
  VOS_UINT16                            usEarfcn;                 /*EUTRAN carrier frequency, 0-65535*/
  VOS_UINT8                             ucNeighCellConfig;   /*2 bits, Provides information related to MBSFN and TDD UL/DL configuration of neighbour cells of this frequency*/
  EUTRANBANDWIDTH_ENUM_UINT8            enBandWidth;
  VOS_UINT8                             ucNum;                   /*number of EUTRAN cell*/
  EUTRAN_MEAS_CELLINFO_STRU             astCellInfo[MMC_MAX_CELL_MEAS_NUM];
}MMC_MEAS_OBJECTE_UTRAN_STRU;

/* MmcMeasObjectParamT */
typedef union
{
  /*MmcMeasObjectCdmaT                  MeasObjectCdma;    Measurement parameters corresponding to CDMA system */
  MMC_MEAS_OBJECT_UTRAN_STRU            stMeasObjectUtran; /* Measurement parameters corresponding to UTRAN system. */
  MMC_MEASOBJECT_GERAN_STRU             stMeasObjectGeran; /* Measurement parameters corresponding to GERAN system.  */
  MMC_MEAS_OBJECTE_UTRAN_STRU           stMeasObjectEutran; /* Measurement parameters corresponding to EUTRAN system. */
} MMC_MEAS_OBJECT_PARAM_STRU;
/* MmcMeasObjectInfoT */
typedef struct
{
   MMCSYSTEMTYPE_ENUM_UINT8             enMeasObjectType;  /* Contains type of the system to which measurement object belongs */
   VOS_UINT32                           ulPeriod;                  /* Periodicity of measurements for this measure object. Unit is in milliseconds (ms). A value of 0 means one time measurement */
   MMC_MEAS_OBJECT_PARAM_STRU           stMeasObjectParam; /* Contains measurement object corresponding to the system specified by MeasObjectType */
} MMC_MEAS_OBJECT_INFO_STRU;

typedef struct
{
   MMCRATID_ENUM_UINT8                  enSourceRat;
   VOS_UINT8                            ucMeasObjectNum;      /* Number of measurement objects included in MeasObjectInfo */
   MMC_MEAS_OBJECT_INFO_STRU            astMeasObjectInfo[1]; /*Contains information about interRAT measurement objects as received from E-UTRAN */
} MmcMeasObjectConfigT;
/*--------------------resel meas ----------------------------*/

/* MmcCdmaPilotMeasResultT */
typedef struct
{
   VOS_UINT16                           usPn;         /* pilot PN */
   VOS_INT16                            sPhase;       /* CDMA pilot phase, in chips */
   VOS_INT8                             cStrength;     /* CDMA pilot strength in -0.5 dB format */
} MMC_CDMA_PILOT_MEAS_RESULT_STRU;

/* MmcMeasResultCdmaT */
typedef struct
{
  VOS_UINT8                             ucCgiAvl;  /* 0 - can't acquire CGI.  1 - CGI available */
  VOS_UINT8                             ucCgi[16];  /* EVDO cell sectorID */

   MMCCDMAMEASRESULT_ENUM_UINT8         enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_CDMA_MEAS_SUCCESS */
   MMCCDMATYPE_ENUM_UINT8               enType;    /* Type of the CDMA system, 1xRTT or HRPD */
   VOS_UINT16                           usChannel;          /* Contains CDMA channel for which this measurement result is valid */
   VOS_UINT8                            ucBand;              /* Contains CDMA band for which this measurement result is valid */
   VOS_UINT8                            ucNumPn;             /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_NUM_MEAS_CDMA_PN */
   MMC_CDMA_PILOT_MEAS_RESULT_STRU      astPilot[MMC_MAX_NUM_MEAS_CDMA_PN]; /* List of CDMA pilot results. Total number of elements in Pilot[] shall not exceed NumPn */
} MMC_MEAS_RESULT_CDMA_STRU;

/* UtranCellGlobalIdT */
typedef struct
{
  PLMNID_RPC_STRU                       stPlmnId;
  VOS_UINT32                            ulCellId;   /*28 bits*/
}UTRAN_CELL_GLOBAL_ID_STRU;

/* MmcReselMeasResultUtranT */
typedef struct
{
  VOS_UINT16                            usArfcn;   /*UTRAN carrier frequency,(0-16383)*/
  UTRANCELLTYPE_ENUM_UINT8              encellType;
  VOS_UINT16                            usphysCellId; /*physical layer identity of the cell, FDD IS (0-511), tdd IS (0-127)*/
  UTRAN_CELL_GLOBAL_ID_STRU             stcellGlobalId;
  VOS_UINT16                            uslocationAreaCode; /*16 bits*/
  VOS_UINT8                             ucroutingAreaCode;  /*8 bits*/
  VOS_UINT8                             ucPlmnNum;
  PLMNID_RPC_STRU                       astPlmnIdList[MMC_MAX_NUM_EUTRA_PLMN];
  VOS_UINT8                             aucSrxlev[MMC_MAX_NUM_EUTRA_PLMN]; /*Received power level value in dB. PlmnNum of valid values*/
}MMC_RESEL_MEAS_RESULT_UTRAN_STRU;

/* GeranCarrierFreqT */
typedef struct
{
  VOS_UINT16                            usArfcn;  /*0-1023*/
  GERANBANDIND_ENUM_UINT8               enBandIndicator;
}GERAN_CARRIERFREQ_STRU;

/* GeranCellGlobalIdT */
typedef struct
{
  PLMNID_RPC_STRU                       stPlmnId;
  VOS_UINT16                            uslocationAreaCode; /*16 bits*/
  VOS_UINT16                            usCellId;              /*16 bits*/
}GERAN_CELL_GLOBAL_ID_STRU;

/* GeranCgiInfoT */
typedef struct
{
  GERAN_CELL_GLOBAL_ID_STRU             stCellGlobalId;
  VOS_UINT8                             ucRoutingAreacode;/*The RAC identity read from broadcast information, as defined in TS 23.003*/
}GERAN_CGI_INFO_STRU;

/* MmcReselMeasResultGeranT */
typedef struct
{
  GERAN_CARRIERFREQ_STRU                stCarrierInfo;
  GERAN_PHYSCELLID_STRU                 stPhysCellId;
  GERAN_CGI_INFO_STRU                   stCgiInfo;
  VOS_UINT8                             ucSrxlev;
}MMC_RESEL_MEAS_RESULT_GERAN_STRU;

/* MmcEutranReselMeasResRecT */
typedef struct
{
   VOS_UINT32                           ulPlmnId;    /*PLMN ID of the EUTRAN system for which this measurement result is valid*/
   VOS_UINT16                           usCellId;    /* E-UTRAN cell Identity under this PLMN for which this measurement result is valid */
   VOS_INT16                            sQmeas;     /* Cell selection RX level value in dBm evaluated as per 36.304 for the E-UTRAN cell specified in CellId */
} MMC_EUTRAN_RESEL_MEAS_RESREC_STRU;


/* MmcReselMeasResultEutranT */
typedef struct
{
  VOS_UINT16                            usEarfcn;             /* E-UTRAN channel number as received in CDMA overhead message */
  VOS_UINT8                             ucNumCell;             /* Number of PLMNs on this EARFCN channel present in PlmnId[] */
  MMC_EUTRAN_RESEL_MEAS_RESREC_STRU     astMeasResult[MMC_MAX_NUM_EUTRA_PLMN]; /*PLMN ID of the neighbor EUTRAN system. This list is not valid if NumPlmn is 0*/

}MMC_RESEL_MEAS_RESULT_EUTRAN_STRU;

/* MmcMeasReselResultT */
typedef union
{
  MMC_MEAS_RESULT_CDMA_STRU             stReselResultCdma;
  MMC_RESEL_MEAS_RESULT_UTRAN_STRU      stReselResultUtran;
  MMC_RESEL_MEAS_RESULT_GERAN_STRU      stReselResultGeran;
  MMC_RESEL_MEAS_RESULT_EUTRAN_STRU     stReselResultEutran;
}MMC_MEAS_RESEL_RESULT_STRU;

/* MmcMeasReselResultObjT */
typedef struct
{
  MMCMEASRESULTSTATUS_ENUM_UINT8        enResult;  /* Status of measurements. Rest of the parameters are valid only in case this is set to MMC_MEAS_SUCCESS */
  MMC_MEAS_RESEL_RESULT_STRU            stMeasReselResult;
}MMC_MEAS_RESEL_RESULT_OBJ_STRU;

/* MmcIratReselMeasResT */
typedef struct
{
  MMCSYSTEMTYPE_ENUM_UINT8              enMeasRatType;  /* Contains type of the system to which measurement object belongs */
  VOS_UINT8                             ucMeasResultNum;
  MMC_MEAS_RESEL_RESULT_OBJ_STRU        astMeasReselResultObj[1];
} MMC_IRAT_RESEL_MEAS_RES_STRU;

typedef struct
{
    MMCRATID_ENUM_UINT8                 enRatId;
    MMC_IRAT_RESEL_MEAS_RES_STRU        stIratReselMeasInd;
}MMC_IRAT_RESEL_MEAS_IND_STRU;
/*---------resel meas req ---------------------------------- */

/* MmcMeasObjectCdmaT */
typedef struct
{
   MMCCDMATYPE_ENUM_UINT8               enType;    /* Type of the CDMA system, 1xRTT or HRPD */
  VOS_UINT16                            usCellToReportCGI;  /* cell which need acquire CGI. 0xffff means not specified */

   VOS_UINT8                            ucBand;              /* Contains CDMA band for which this measurement result is valid */
   VOS_UINT16                           usChannel;          /* Contains CDMA channel for which this measurement result is valid */
   VOS_UINT8                            ucSearchWinSize;     /* Contains CDMA pilot search window size */
   VOS_UINT8                            ucNumPn;             /* Number of CDMA pilot results included. The maximum value shall not exceed MMC_MAX_NUM_MEAS_CDMA_PN */
   VOS_UINT16                           ausPilot[1]; /* List of CDMA pilots to be measured. Total number of elements in Pilot[] shall not exceed NumPn */
} MMC_MEAS_OBJECT_CDMA_STRU;

/* carrierFreqListUtranFddT */
typedef struct
{
  VOS_UINT16                            usArfcn;    /*UTRAN carrier frequency, (0-16383)*/
  VOS_UINT8                             ucThreshXHigh;   /*(0-31),ReselectionThreshold, is used to indicate an Rx level threshold for cell reselection. Actual value of threshold = IE value * 2 [dB].*/
  VOS_UINT8                             ucThreshXLow;  /*(0-31),ReselectionThreshold, is used to indicate an Rx level threshold for cell reselection. Actual value of threshold = IE value * 2 [dB].*/
  VOS_INT8                              cQRxLevMin;   /*(-60..33). Actual value=IE value*2+1 (dBm)*/
  VOS_INT8                              cPTxMax;   /*(-50..33), the allowed max transmission power on the (uplink) carrier frequency, in dBm*/
  CL_BOOL_ENUM_UINT8                    bRsrq;    /*If the threshServingLowq is present in systeminformationBlockType3, bRsrq=TRUE.*/
  VOS_UINT8                             ucThreshXHighQ;  /*(0-31), present if bRsrq=TRUE*/
  VOS_UINT8                             ucThreshXLowQ;  /*(0-31), present if bRsrq=TRUE*/
}CARRIER_FREQ_LIST_UTRAN_FDD_STRU;

/* carrierFreqListUtranTddT */
typedef struct
{
  VOS_UINT16                            usArfcn;    /*UTRAN carrier frequency, (0-16383)*/
  VOS_UINT8                             ucThreshXHigh;   /*(0-31),ReselectionThreshold, is used to indicate an Rx level threshold for cell reselection. Actual value of threshold = IE value * 2 [dB].*/
  VOS_UINT8                             ucThreshXLow;  /*(0-31),ReselectionThreshold, is used to indicate an Rx level threshold for cell reselection. Actual value of threshold = IE value * 2 [dB].*/
  VOS_INT8                              cQRxLevMin;   /*(-60..33). Actual value=IE value*2+1 (dBm)*/
  VOS_INT8                              cPTxMax;   /*(-50..33), the allowed max transmission power on the (uplink) carrier frequency, in dBm*/
}CARRIER_FREQ_LIST_UTRANTDD_STRU;

/* UtranCarrierFreqInfoFddv8h0T */
typedef struct
{
  VOS_UINT8                             ucMultiBandNum;
  VOS_UINT8                             aucFreqBandIndicator[8];  /*(1-86).Indicates the list of  frequency bands in addition to the band represented by Arfcn  for which UTRA cell reselection parameters are common.*/
}UTRAN_CARRIER_FREQ_INFO_FDD_V8H0_STRU;

/* SysInfoBlockType6v8h0T */
typedef struct
{
  VOS_UINT8                             ucV8h0Num;
  UTRAN_CARRIER_FREQ_INFO_FDD_V8H0_STRU astCarrierFreqInfoFddv8h0[MMC_MAX_CELL_MEAS_NUM];
}SYSINFO_BLOCKTYPE6V8H0_STRU;

/* MmcMeasReselUtranT */
typedef struct
{
  VOS_UINT8                             ucNumFdd;   /*number of FDD freq list*/
  CARRIER_FREQ_LIST_UTRAN_FDD_STRU      astFreqFddList[MMC_MAX_CELL_MEAS_NUM];
  VOS_UINT8                             ucNumTdd;   /*number of TDD freq list*/
  CARRIER_FREQ_LIST_UTRANTDD_STRU       astFreqTddList[MMC_MAX_CELL_MEAS_NUM];
  SYSINFO_BLOCKTYPE6V8H0_STRU           stlateNonCriticalExtv8h0Ies;
}MMC_MEAS_RESEL_UTRAN_STRU;

/* GeranCommonInfoT */
typedef struct
{
  VOS_UINT8                             ucnccPermitted;/*Field encoded as a bit map, where bit N is set to "0" if a BCCH carrier with NCC = N-1 is not permitted for monitoring and set to "1" if the BCCH carrier with NCC = N-1 is permitted for monitoring; N = 1 to 8; bit 1 of the bitmap is the leading bit of the bit string.*/
  VOS_UINT8                             ucQRxLevMin;  /*(0-45).Parameter "Qrxlevmin" in TS 36.304 [1], minimum required RX level in the GSM cell. The actual value of Qrxlevmin in dBm = (IE value * 2)   115.*/
  VOS_UINT8                             ucPMaxGeran; /*(0-39), 0xff means NULL.*/
  VOS_UINT8                             ucThreshXHigh; /*(0..31). Parameter "ThreshX, HighP" in TS 36.304 */
  VOS_UINT8                             ucThreshXLow; /*(0..31). Parameter "ThreshX, LowP" in TS 36.304 */
}GERAN_COMMON_INFO_STRU;

/* MmcMeasReselGeranT */
typedef struct
{
  GERAN_CARRIER_FREQ_STRU               stcarrierFreq;
  GERAN_COMMON_INFO_STRU                stCommonInfo;
}MMC_MEAS_RESEL_GERAN_STRU;

/*==== MmcMeasReselEutranT =======*/
typedef struct
{
  VOS_UINT16                            usEarfcn;             /* E-UTRAN channel number as received in CDMA overhead message */
  VOS_INT16                             sRxLevMinEutra;       /* Min ref power level received in CDMA overhead message. To be used by LTE to calculate Srxlev of measured cell */
  VOS_UINT8                             ucRxLevMinEutraOffset; /* Offset to min ref power level received in CDMA overhead message. To be used by LTE to calculate Srxlevmeasured cell.
                                                                A value of 0xFF means this is not provided and default value of this parameter shall be used */
  VOS_UINT8                             ucPeMax;               /* Max TX power level received in CDMA overhead message. LTE may use this when transmitting up-link in E-UTRAN */
  VOS_UINT8                             ucMeasBandWidth;       /*3 bits, it is defined by the parameter Transmission Bandwidth Configuration, Nrb(TS36.304). The values indicate the number of resource blocks over which the UE could measure. */
                                           /*field value to Nrb:0->6, 1->15, 2->25,3->50, 4->75, 5->100*/
  /*uint8  QOffset;                  is used to indicate a cell or frequency specific offset to be applied when evaluating candidates for cell re-selection or when evaluating triggering conditions for measurement reporting. The value in dB.
                                            db-24=0, Value dB-24 corresponds to -24 dB, dB-22 corresponds to -22 dB and so on*/

  VOS_UINT8                             ucPlmnNum;             /* Number of PLMNs on this EARFCN channel present in PlmnId[] */
  VOS_UINT32                            aulPlmnId[MMC_MAX_NUM_EUTRA_PLMN]; /*PLMN ID of the neighbor EUTRAN system. This list is not valid if NumPlmn is 0*/
} MMC_MEAS_RESEL_EUTRAN_STRU;

/* MmcMeasReselDataT */
typedef union
{
  MMC_MEAS_OBJECT_CDMA_STRU             stMeasReselCdma;   /* Measurement parameters corresponding to CDMA system */
  MMC_MEAS_RESEL_UTRAN_STRU             stMeasReseltUtran; /* Measurement parameters corresponding to UTRAN system. */
  MMC_MEAS_RESEL_GERAN_STRU             stMeasReselGeran; /* Measurement parameters corresponding to GERAN system.  */
  MMC_MEAS_RESEL_EUTRAN_STRU            stMeasReselEutran; /* Measurement parameters corresponding to EUTRAN system. */
} MMC_MEAS_RESEL_DATA_STRU;

/* MmcMeasReselObjT */
typedef struct
{
  VOS_UINT32                            ulPeriod;                  /* Periodicity of measurements for this measure object. Unit is in milliseconds (ms). A value of 0 means one time measurement */
 MMC_MEAS_RESEL_DATA_STRU               stMeasReselData;
} MMC_MEAS_RESEL_OBJ_STRU;

/* MmcIratReselMeasT */
typedef struct
{
  MMCRATID_ENUM_UINT8                   enSourceRat;
  MMCSYSTEMTYPE_ENUM_UINT8              enMeasObjectType;  /* Contains type of the system to which measurement object belongs */
  VOS_UINT8                             ucMeasObjectNum;
  MMC_MEAS_RESEL_OBJ_STRU               astMeasReselObject[1]; /* Contains measurement object corresponding to the system specified by MeasObjectType */
} MMC_IRAT_RESEL_MEAS_STRU;

/*--------------------resel meas ----------------------------*/

/*****************************************************************************
 结构名    : LRRC_CMMCA_DATA_MSG_DATA
 协议表格  :
 ASN.1描述 :
 结构说明  : LRRC_CMMCA_DATA_MSG_DATA数据结构，用于生成ASN文件
*****************************************************************************/
typedef struct
{
    MMCRATAPIID_ENUM_UINT16                          enMsgID;            /*_H2ASN_MsgChoice_Export MMCRATAPIID_ENUM_UINT16 */
    VOS_UINT8                                        aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMCRATAPIID_ENUM_UINT16
    ****************************************************************************/
}LRRC_CMMCA_DATA_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 结构名    : LRrcCmmcaDataInterface_MSG
 协议表格  :
 ASN.1描述 :
 结构说明  : LRrcCdmaInterface_MSG数据结构,用于生成ASN文件
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    LRRC_CMMCA_DATA_MSG_DATA                                stMsgData;
}LRrcCmmcaDataInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


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


#endif

