


#ifndef __NAS_MSCC_MLPL_MSPL_PARSE_H__
#define __NAS_MSCC_MLPL_MSPL_PARSE_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define NAS_MSCC_BIT_LEN_1_BIT          ( 1 )
#define NAS_MSCC_BIT_LEN_3_BIT          ( 3 )
#define NAS_MSCC_BIT_LEN_4_BIT          ( 4 )
#define NAS_MSCC_BIT_LEN_6_BIT          ( 6 )
#define NAS_MSCC_BIT_LEN_7_BIT          ( 7 )
#define NAS_MSCC_BIT_LEN_8_BIT          ( 8 )
#define NAS_MSCC_BIT_LEN_12_BIT         ( 12 )
#define NAS_MSCC_BIT_LEN_15_BIT         ( 15 )
#define NAS_MSCC_BIT_LEN_16_BIT         ( 16 )
#define NAS_MSCC_BIT_LEN_24_BIT         ( 24 )

#define NAS_MSCC_MAX_NUM_MSPL_REC                           ( 24 )
#define NAS_MSCC_MAX_NUM_MLPL_REC                           ( 255 )
#define NAS_MSCC_MAX_NUM_MSPL_ID                            ( 255 )
#define NAS_MSCC_MAX_NUM_SYS_LOC_TAG                        ( 64 )

#define NAS_MSCC_MLPL_SYS_TAG_CDMA2000_MAX_SUBNET_BIT_LEN   ( 128 )
#define NAS_MSCC_MLPL_SYS_TAG_CDMA2000_MAX_SUBNET_OCTET_LEN ( 16 )

#define NAS_MSCC_MSPL_BIT_NETWORK_CAP_IND                   ( 0x01 )

#define NAS_MSCC_MLPL_LOC_PARAM_BIT_MCC                     ( 0x01 )
#define NAS_MSCC_MLPL_LOC_PARAM_BIT_MNC                     ( 0x02 )
#define NAS_MSCC_MLPL_LOC_PARAM_BIT_LOC_TAG                 ( 0x04 )


/* Bit lengths of header params in MSPL */
#define NAS_MSCC_MSPL_MSPL_SIZE_BIT_LEN                     (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MSPL_CUR_MMSS_P_REV_BIT_LEN                (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MSPL_MSPL_VER_ID_BIT_LEN                   (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MSPL_NUM_MSPL_ID_BIT_LEN                   (NAS_MSCC_BIT_LEN_8_BIT)

/* Bit lengths of params in MSPL ID */
#define NAS_MSCC_MSPL_MSPL_ID_BIT_LEN                       (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MSPL_NUM_MSPL_RECS_BIT_LEN                 (NAS_MSCC_BIT_LEN_8_BIT)

/* Bit lengths of params of single MSPL record */
#define NAS_MSCC_MSPL_REC_SYS_TYPE_BIT_LEN                  (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MSPL_REC_PRIO_CLASS_BIT_LEN                (NAS_MSCC_BIT_LEN_4_BIT)
#define NAS_MSCC_MSPL_REC_SYS_PRIO_BIT_LEN                  (NAS_MSCC_BIT_LEN_1_BIT)
#define NAS_MSCC_MSPL_REC_HIGHER_PRIO_SRCH_TIME_BIT_LEN     (NAS_MSCC_BIT_LEN_3_BIT)
#define NAS_MSCC_MSPL_REC_NETWRK_CAP_IND_BIT_LEN            (NAS_MSCC_BIT_LEN_1_BIT)
#define NAS_MSCC_MSPL_REC_NETWRK_CAP_BIT_LEN                (NAS_MSCC_BIT_LEN_6_BIT)

/* Min Bit lengths of single MSPL record */
#define NAS_MSCC_MSPL_REC_MIN_BIT_LEN \
        (NAS_MSCC_MSPL_REC_SYS_TYPE_BIT_LEN \
       + NAS_MSCC_MSPL_REC_PRIO_CLASS_BIT_LEN \
       + NAS_MSCC_MSPL_REC_SYS_PRIO_BIT_LEN \
       + NAS_MSCC_MSPL_REC_HIGHER_PRIO_SRCH_TIME_BIT_LEN \
       + NAS_MSCC_MSPL_REC_NETWRK_CAP_IND_BIT_LEN \
        )

/* Min Bit lengths of single MSPL ID */
#define NAS_MSCC_MSPL_ID_MIN_BIT_LEN \
        (NAS_MSCC_MSPL_MSPL_ID_BIT_LEN \
       + NAS_MSCC_MSPL_NUM_MSPL_RECS_BIT_LEN \
       + NAS_MSCC_MSPL_REC_MIN_BIT_LEN \
        )

/* Min Bit lengths of single MSPL header in MSPL */
#define NAS_MSCC_MSPL_HEADER_MIN_BIT_LEN \
        (NAS_MSCC_MSPL_MSPL_SIZE_BIT_LEN \
       + NAS_MSCC_MSPL_CUR_MMSS_P_REV_BIT_LEN \
       + NAS_MSCC_MSPL_MSPL_VER_ID_BIT_LEN \
       + NAS_MSCC_MSPL_NUM_MSPL_ID_BIT_LEN \
        )

/* Min Bit lengths of single MSPL */
#define NAS_MSCC_MSPL_MIN_BIT_LEN \
        (NAS_MSCC_MSPL_HEADER_MIN_BIT_LEN \
       + NAS_MSCC_MSPL_ID_MIN_BIT_LEN)

/* Min Bit lengths of single MSPL */
#define NAS_MSCC_MSPL_CRC_BIT_LEN       (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MLPL_CRC_BIT_LEN       (NAS_MSCC_BIT_LEN_16_BIT)

/* Bit lengths of header params in MLPL */
#define NAS_MSCC_MLPL_MLPL_SIZE_BIT_LEN                     (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MLPL_CUR_MMSS_P_REV_BIT_LEN                (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MLPL_MLPL_VER_ID_BIT_LEN                   (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MLPL_MLPL_ID_BIT_LEN                       (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MLPL_NUM_MLPL_REC_BIT_LEN                  (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_REC_LOC_PARAM_TYPE_BIT_LEN            (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN                (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_LOC_PARAM_MCC_BIT_LEN                 (NAS_MSCC_BIT_LEN_12_BIT)
#define NAS_MSCC_MLPL_LOC_PARAM_MNC_BIT_LEN                 (NAS_MSCC_BIT_LEN_12_BIT)
#define NAS_MSCC_MLPL_LOC_PARAM_NUM_SYS_LOC_TAG_BIT_LEN     (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_LOC_PARAM_SYS_TYPE_BIT_LEN            (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MLPL_LOC_PARAM_SYS_LOC_TAG_SIZE_BIT_LEN    (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_LOC_TAG_SID_BIT_LEN                   (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MLPL_LOC_TAG_NID_START_BIT_LEN             (NAS_MSCC_BIT_LEN_16_BIT)
#define NAS_MSCC_MLPL_LOC_TAG_NID_RANGE_BIT_LEN             (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_LOC_TAG_PLMN_START_BIT_LEN            (NAS_MSCC_BIT_LEN_24_BIT)
#define NAS_MSCC_MLPL_LOC_TAG_PLMN_RANGE_BIT_LEN            (NAS_MSCC_BIT_LEN_8_BIT)

#define NAS_MSCC_MLPL_LOC_TAG_SUBNET_LENGTH_BIT_LEN         (NAS_MSCC_BIT_LEN_8_BIT)
#define NAS_MSCC_MLPL_LOC_TAG_SUBNET_ID_BIT_LEN             (NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_SUBNET_ID_BIT_LEN)

#define NAS_MSCC_MLPL_LOC_PARAM_VAL_MIN_BIT_LEN             (NAS_MSCC_MLPL_LOC_PARAM_MCC_BIT_LEN)

#define NAS_MSCC_MLPL_REC_LOC_PARAM_MCC_MNC_SYS_LOC_TAG_BITS ( 0x00 )

#define NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_SUBNET_ID_BIT_LEN     ( 1 )

#define NAS_MSCC_MLPL_LOC_TAG_PLMN_START_NUM_OCTET          ( 3 )

#define NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_COUNT            (8)

#define NSA_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_BIT_LEN \
        (NAS_MSCC_MLPL_LOC_TAG_SID_BIT_LEN \
        + NAS_MSCC_MLPL_LOC_TAG_NID_START_BIT_LEN \
        + NAS_MSCC_MLPL_LOC_TAG_NID_RANGE_BIT_LEN)

#define NAS_MSCC_MLPL_SYS_LOC_TAG_3GPP_BIT_LEN \
        (NAS_MSCC_MLPL_LOC_TAG_PLMN_START_BIT_LEN \
        + NAS_MSCC_MLPL_LOC_TAG_PLMN_RANGE_BIT_LEN)

#define NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_VAL_BIT_LEN \
        (NAS_MSCC_MLPL_LOC_TAG_SUBNET_LENGTH_BIT_LEN \
       + NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_SUBNET_ID_BIT_LEN)

#define NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_BIT_LEN \
        (NAS_MSCC_MLPL_LOC_PARAM_SYS_TYPE_BIT_LEN \
       + NAS_MSCC_MLPL_LOC_PARAM_SYS_LOC_TAG_SIZE_BIT_LEN \
       + NAS_MSCC_MLPL_SYS_LOC_TAG_MIN_VAL_BIT_LEN)

#define NAS_MSCC_MLPL_HEADER_MIN_BIT_LEN \
        (NAS_MSCC_MLPL_MLPL_SIZE_BIT_LEN \
       + NAS_MSCC_MLPL_CUR_MMSS_P_REV_BIT_LEN \
       + NAS_MSCC_MLPL_MLPL_VER_ID_BIT_LEN \
       + NAS_MSCC_MLPL_MLPL_ID_BIT_LEN \
       + NAS_MSCC_MLPL_NUM_MLPL_REC_BIT_LEN)

#define NAS_MSCC_MLPL_DEFAULT_REC_MIN_BIT_LEN \
        (NAS_MSCC_MLPL_REC_LOC_PARAM_TYPE_BIT_LEN \
       + NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN)

#define NAS_MSCC_MLPL_NORMAL_REC_MIN_BIT_LEN \
        (NAS_MSCC_MLPL_REC_LOC_PARAM_TYPE_BIT_LEN \
       + NAS_MSCC_MLPL_LOC_PARAM_VAL_MIN_BIT_LEN \
       + NAS_MSCC_MLPL_REC_MSPL_INDEX_BIT_LEN)


#define NAS_MSCC_MLPL_MIN_BIT_LEN \
        (NAS_MSCC_MLPL_HEADER_MIN_BIT_LEN \
       + NAS_MSCC_MLPL_DEFAULT_REC_MIN_BIT_LEN)


/* Max value of 16 bit variable */
#define NAS_MSCC_CRC_BIT_LEN            (NAS_MSCC_BIT_LEN_16_BIT)

#define NAS_MSCC_UPDATE_BIT_OFFSET(ucNewOffset, ucOffset) \
{ \
    (ucNewOffset) = (ucNewOffset) + (ucOffset); \
}

#define NAS_MSCC_GET_REMAIN_BIT_LEN(usBuffSize, usBitOffset) \
    (((usBuffSize) * NAS_MSCC_BIT_LEN_8_BIT) - (usBitOffset))

#define NAS_MSCC_IS_DEFAULT_MLPL_REC(ucLocParamType) \
    (!((VOS_UINT8)(NAS_MSCC_MLPL_REC_LOC_PARAM_MCC_MNC_SYS_LOC_TAG_BITS | ((ucLocParamType) << 5))))


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM
{
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI       = 0x00, /* cdma2000_AI */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI           = 0x01, /* 3GPP_AI */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_WIMAX             = 0x02, /* WiMAX */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_1X       = 0x03, /* cdma2000 1x  */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD     = 0x04, /* cdma2000 HRPD */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_GSM               = 0x05, /* GERAN (GSM) */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_UMTS              = 0x06, /* UTRAN (UMTS) */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE               = 0x07, /* EUTRAN (LTE) */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_RESERVED          = 0x08, /* Start - Reserved for future standardization */

    NAS_MSCC_MLPL_MSPL_SYS_TYPE_BUTT              = 0xFF, /* End - Reserved for future standardization */
};
typedef VOS_UINT8 NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8;



enum NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM
{
    NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME                        = 0x00, /* Home only */
    NAS_MSCC_MSPL_SYS_PRI_CLASS_HOME_AND_PREF               = 0x01, /* Home + Preferred */
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ANY                         = 0x0F, /* Any */
    NAS_MSCC_MSPL_SYS_PRI_CLASS_RESERVED                    = 0x02, /* Start - Reserved */

    NAS_MSCC_MSPL_SYS_PRI_CLASS_BUTT                        = 0x0E, /* End - Reserved */
};
typedef VOS_UINT8 NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8;



enum NAS_MSCC_MSPL_SYS_PRI_ENUM
{
    NAS_MSCC_MSPL_SYS_PRI_SAME          = 0X00,
    NAS_MSCC_MSPL_SYS_PRI_MORE          = 0X01,

    NAS_MSCC_MSPL_SYS_PRI_BUTT          = 0X02
};
typedef VOS_UINT8 NAS_MSCC_MSPL_SYS_PRI_ENUM_UINT8;



enum NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM
{
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_1_MIN                = 0x00,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_2_MIN                = 0x01,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_4_MIN                = 0x02,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_8_MIN                = 0x03,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_16_MIN               = 0x04,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_24_MIN               = 0x05,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_32_MIN               = 0x06,
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_64_MIN               = 0x07,

    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_BUTT                 = 0x08,
};
typedef VOS_UINT8 NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM_UINT8;



enum NAS_MSCC_MSPL_NETWORK_CAP_ENUM
{
    NAS_MSCC_MSPL_NETWORK_CAP_VOICE_AND_DATA                = 0x00,
    NAS_MSCC_MSPL_NETWORK_CAP_RESERVED                      = 0x01, /* Start - Reserved */
    NAS_MSCC_MSPL_NETWORK_CAP_BUTT                          = 0x3F  /* End - Reserved */
};
typedef VOS_UINT8 NAS_MSCC_MSPL_NETWORK_CAP_ENUM_UINT8;



enum NAS_MSCC_PARSE_CRC_RSLT_ENUM
{
    NAS_MSCC_PARSE_CRC_RSLT_SUCCESS,
    NAS_MSCC_PARSE_CRC_RSLT_FAIL,
    NAS_MSCC_PARSE_CRC_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32;



enum NAS_MSCC_PARSE_MLPL_RSLT_ENUM
{
    NAS_MSCC_PARSE_MLPL_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MLPL_RSLT_MALLOC_FAIL,
    NAS_MSCC_PARSE_MLPL_RSLT_HDR_PARSE_FAIL,
    NAS_MSCC_PARSE_MLPL_RSLT_MLPL_REC_PARSE_FAIL,
    NAS_MSCC_PARSE_MLPL_RSLT_FAIL,
    NAS_MSCC_PARSE_MLPL_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32;



enum NAS_MSCC_PARSE_MLPL_HDR_RSLT_ENUM
{
    NAS_MSCC_PARSE_MLPL_HDR_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MLPL_HDR_RSLT_FAIL,
    NAS_MSCC_PARSE_MLPL_HDR_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MLPL_HDR_RSLT_ENUM_UINT32;



enum NAS_MSCC_PARSE_MLPL_REC_RSLT_ENUM
{
    NAS_MSCC_PARSE_MLPL_REC_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MLPL_REC_RSLT_FAIL,
    NAS_MSCC_PARSE_MLPL_REC_RSLT_INSUFFICIENT_DATA_LEN,
    NAS_MSCC_PARSE_MLPL_REC_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MLPL_REC_RSLT_ENUM_UINT32;


enum NAS_MSCC_PARSE_MSPL_RSLT_ENUM
{
    NAS_MSCC_PARSE_MSPL_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MSPL_RSLT_MALLOC_FAIL,
    NAS_MSCC_PARSE_MSPL_RSLT_HDR_PARSE_FAIL,
    NAS_MSCC_PARSE_MSPL_RSLT_MSPL_ID_PARSE_FAIL,
    NAS_MSCC_PARSE_MSPL_RSLT_FAIL,
    NAS_MSCC_PARSE_MSPL_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32;



enum NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM
{
    NAS_MSCC_PARSE_MSPL_HDR_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MSPL_HDR_RSLT_FAIL,
    NAS_MSCC_PARSE_MSPL_HDR_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM_UINT32;



enum NAS_MSCC_PARSE_MSPL_ID_RSLT_ENUM
{
    NAS_MSCC_PARSE_MSPL_ID_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MSPL_ID_RSLT_FAIL,
    NAS_MSCC_PARSE_MSPL_ID_RSLT_INSUFFICIENT_DATA_LEN,
    NAS_MSCC_PARSE_MSPL_ID_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MSPL_ID_RSLT_ENUM_UINT32;


enum NAS_MSCC_PARSE_MSPL_REC_RSLT_ENUM
{
    NAS_MSCC_PARSE_MSPL_REC_RSLT_SUCCESS,
    NAS_MSCC_PARSE_MSPL_REC_RSLT_INSUFFICIENT_DATA_LEN,
    NAS_MSCC_PARSE_MSPL_REC_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_PARSE_MSPL_REC_RSLT_ENUM_UINT32;


enum NAS_MSCC_MLPL_MSPL_PARSE_TYPE_ENUM
{
    NAS_MSCC_MLPL_MSPL_PARSE_TYPE_MLPL,
    NAS_MSCC_MLPL_MSPL_PARSE_TYPE_MSPL,

    NAS_MSCC_MLPL_MSPL_PARSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_MLPL_MSPL_PARSE_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


typedef struct
{
    VOS_UINT8                           aucPlmnStart[NAS_MSCC_MLPL_LOC_TAG_PLMN_START_NUM_OCTET];
    VOS_UINT8                           ucPlmnRange;
}NAS_MSCC_MLPL_SYS_LOC_TAG_3GPP_STRU;


typedef struct
{
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNidStart;
    VOS_UINT8                           ucNidRange;
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_STRU;


typedef struct
{
    VOS_UINT8                           ucSubnetLen;
    VOS_UINT8                           aucSubnetId[NAS_MSCC_MLPL_SYS_TAG_CDMA2000_MAX_SUBNET_OCTET_LEN];
    VOS_UINT8                           aucReserved[3];
}NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU;


typedef union
{
    NAS_MSCC_MLPL_SYS_LOC_TAG_3GPP_STRU                     stSysLocTag3GPP;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_STRU                 stSysLocTagCdma2000;
    NAS_MSCC_MLPL_SYS_LOC_TAG_CDMA2000_HRPD_STRU            stSysLocTagCdma2000Hrpd;
}NAS_MSCC_MLPL_SYS_LOC_TAG_UNION;


typedef struct
{
    /* To indicate if current MSPL record in MSPL_ID is valid or not */
    VOS_UINT8                                               ucIsValid;

    /* System Type identification */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;

    /* Priority Class defines the selection priority to be used in a
       system as allowed in that system */
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;

    /* This field indicates the relative priority of systems in the
       MMSS system priority table. The relative priority can be
       more(1) or same(0) */
    NAS_MSCC_MSPL_SYS_PRI_ENUM_UINT8                        enSysPri;

    /* Set to the time between searches of higher priority systems of
       other radio access technologies that the mobile station may use
       when this entry is the current system */
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM_UINT8           enHigherPriSrchTime;

    /* If a NETWORK_CAP is to be included in this MSPL record this field
       shall be set to '1'*/
    VOS_UINT8                                               ucNetwrkCapInd;

    /* If the NETWORK_CAP_IND is set to '1' this field shall be set to a
       value from, Otherwise, it is omitted */
    NAS_MSCC_MSPL_NETWORK_CAP_ENUM_UINT8                    enNetwrkCap;
    VOS_UINT8                                               ucReserved;
}NAS_MSCC_MSPL_REC_STRU;



typedef struct
{
    /* To indicate if current MSPL_ID is valid or not */
    VOS_UINT8                           ucIsMsplIdValid;

    /* MSPL_ID is the unique identifier of an MSPL table assigned by the base station */
    VOS_UINT8                           ucMsplId;

    /* This field is set to the number of MMSS system priority records
       contained in the MSPL block */
    VOS_UINT8                           ucNumMsplRec;
    VOS_UINT8                           ucReserved;

    /* ucNumMsplRec instances of MSPL record structure */
    NAS_MSCC_MSPL_REC_STRU              astMsplRec[NAS_MSCC_MAX_NUM_MSPL_REC];
}NAS_MSCC_MSPL_ID_STRU;



typedef struct
{
    /* This field is set to the total size, in octets, of the MMSS
       System Priority List, including the MSPL_SIZE  and MSPL_CRC fields */
    VOS_UINT16                          usMsplSize;

    /* The mobile station shall set this field to the value of the
       MMSS_P_REV associated with this MSPL */
    VOS_UINT8                           ucCurrProtRev;
    VOS_UINT8                           ucReserved1;

    /* The mobile station shall set this field to the value of the MSPL
       Version Identification assigned for the MSPL (MSP_LISTs-p) by the
       base station */
    VOS_UINT16                          usMsplVerId;

    /* NUM_MSPL_ID:This field is set to the number of MSPL_IDs in this set of MSPL_IDs */
    VOS_UINT8                           ucNumMsplId;
    VOS_UINT8                           ucReserved2;
}NAS_MSCC_MSPL_HEADER_STRU;



typedef struct
{
    /* To indicate if current MSPL is valid or not */
    VOS_UINT8                           ucIsMsplValid;
    VOS_UINT8                           ucReserved1[3];

    /* MSPL header information */
    NAS_MSCC_MSPL_HEADER_STRU           stMsplHdr;

    /* NUM_MSPL_ID instances of MSPL_ID structure */
    NAS_MSCC_MSPL_ID_STRU              *apstMsplId[NAS_MSCC_MAX_NUM_MSPL_ID];

    /* MSPL CRC */
    VOS_UINT16                          usMsplCrc;
    VOS_UINT8                           ucReserved2[2];
}NAS_MSCC_MSPL_STRU;



typedef struct
{
    /* To indicate if current System Location Tag in MLPL locataion param is valid or not. */
    VOS_UINT8                                               ucIsLocTagValid;

    /* System Type */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;

    /* System Location Tag Size, in bits */
    VOS_UINT8                                               ucSysLocTagSize;
    VOS_UINT8                                               ucReserved;

    /* System Location Tag, based on system type */
    NAS_MSCC_MLPL_SYS_LOC_TAG_UNION                         unSysLocTag;
}NAS_MSCC_MLPL_SYS_LOC_TAG_STRU;



typedef struct
{
    /* Mobile Country Code */
    VOS_UINT16                          usMcc;

    /* Mobile Network Code */
    VOS_UINT16                          usMnc;

    /* Number of System Location Tags */
    VOS_UINT8                           ucNumSysLocTag;
    VOS_UINT8                           aucReserve[3];

    /* ucNumSysLocTag instances of System Location Tags */
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU      astSysLocTag[NAS_MSCC_MAX_NUM_SYS_LOC_TAG];
}NAS_MSCC_MLPL_LOC_PARAM_STRU;



typedef struct
{
    /* To indicate if current MLPL record is valid or not. */
    VOS_UINT8                           ucIsRecValid;

    /* This field identifies the parameter used for Location grouping */
    VOS_UINT8                           ucLocParamType;
    VOS_UINT8                           aucReserved1[2];

    /* LOC_PARAM_VAL is the value of the Location Parameter used.
       The length of this field is variable in length and depends on the
       LOC_PARAM_TYPE used for location grouping */
    NAS_MSCC_MLPL_LOC_PARAM_STRU        stLocParamVal;

    /* This field is set to the MSPL_ID of the MMSS System Priority List
       scorresponding to an MLPL entry */
    VOS_UINT8                           ucMsplIndex;
    VOS_UINT8                           aucReserved2[3];
}NAS_MSCC_MLPL_RECORD_STRU;



typedef struct
{
    /* This field is set to the total size, in octets, of the MLPL,including
       the MLPL_SIZE and MLPL_CRC fields*/
    VOS_UINT16                   usMlplSize;

    /* The mobile station shall set this field to the value of the
       MMSS_P_REV associated with this MLPL */
    VOS_UINT8                    ucCurrProtRev;
    VOS_UINT8                    ucReserved1;

    /* The mobile station shall set this field to the value of the MLPL
       Version Identification assigned for the MLPL (MLP_LISTs-p) by the
       base station */
    VOS_UINT16                   usMlplVerId;

    /* Unique identification for the MLPL assigned by the base station */
    VOS_UINT8                    ucMlplId;

    /* This field is set to the number of entries in the MLPL */
    VOS_UINT8                    ucNumMlplRec;
}NAS_MSCC_MLPL_HEADER_STRU;



typedef struct
{
    /* Indicatesif MLP list is valid. */
    VOS_UINT8                           ucIsMlplValid;
    VOS_UINT8                           ucIsContainDefRec;
    VOS_UINT8                           ucMsplIdxInFirstDefRec;
    VOS_UINT8                           ucReserved;

    /* Contains header information of MLP list. */
    NAS_MSCC_MLPL_HEADER_STRU           stMlplHdr;

    /* List of MLPL records in MLP list. */
    NAS_MSCC_MLPL_RECORD_STRU          *apstMlplRec[NAS_MSCC_MAX_NUM_MLPL_REC];

    /* CRC in MLPL list. */
    VOS_UINT16                          usMlplCrc;
    VOS_UINT8                           aucReserve2[2];
}NAS_MSCC_MLPL_STRU;



typedef struct
{
    VOS_UINT8                          *pucMsplSrcBuff;
    VOS_UINT16                          usBuffSize;
    VOS_UINT16                          usBitOffset;
    VOS_UINT8                           ucNumValidMsplId;
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT32                          ulParsedMsplIdBitLen;
    NAS_MSCC_MSPL_STRU                 *pstMsplInfo;
}NAS_MSCC_MSPL_PARSE_CTX_STRU;



typedef struct
{
    VOS_UINT8                          *pucMlplSrcBuff;
    VOS_UINT16                          usBuffSize;
    VOS_UINT8                           aucReserve1[2];
    VOS_UINT16                          usBitOffset;
    VOS_UINT8                           ucNumValidMlplRec;
    VOS_UINT8                           ucReserve2;
    VOS_UINT32                          ulParsedMlplRecBitLen;
    NAS_MSCC_MLPL_STRU                 *pstMlplInfo;
}NAS_MSCC_MLPL_PARSE_CTX_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT8  NAS_MSCC_ExtractBitStringToOctet(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
);

VOS_UINT16 NAS_MSCC_ExtractBitStringToWord(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
);

NAS_MSCC_PARSE_CRC_RSLT_ENUM_UINT32 NAS_MSCC_CheckMlplMsplCrcChecksum(
    VOS_UINT8                          *pMsplMlplBuff
);

NAS_MSCC_PARSE_MSPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplBitStream(
    VOS_UINT8                          *pucMsplBuff,
    VOS_UINT16                          usBuffSize
);

NAS_MSCC_PARSE_MSPL_HDR_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplHeader(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx
);

NAS_MSCC_PARSE_MSPL_ID_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplId(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_ID_STRU              *pstMsplId
);

NAS_MSCC_PARSE_MSPL_REC_RSLT_ENUM_UINT32 NAS_MSCC_ParseMsplRecord(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_REC_STRU             *pstMsplRec
);

VOS_UINT8 NAS_MSCC_IsMsplRecValid(
    NAS_MSCC_MSPL_REC_STRU              *pstTempMsplRec
);

VOS_VOID NAS_MSCC_UpdateMsplIdInfo(
    NAS_MSCC_MSPL_PARSE_CTX_STRU       *pstMsplParseCtx,
    NAS_MSCC_MSPL_ID_STRU              *pstMsplId,
    VOS_UINT8                           ucIndex
);

NAS_MSCC_PARSE_MLPL_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplBitStream(
    VOS_UINT8                          *pucMlplBuff,
    VOS_UINT16                          usBuffSize
);

NAS_MSCC_PARSE_MLPL_HDR_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplHeader(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx
);

NAS_MSCC_PARSE_MLPL_REC_RSLT_ENUM_UINT32 NAS_MSCC_ParseMlplRec(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_RECORD_STRU          *pstMlplRec,
    VOS_UINT8                          *pucIsDefaultRec
);

VOS_VOID NAS_MSCC_ParseMlplSysLocTag(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
);

VOS_VOID NAS_MSCC_ParseMlplSysLocTagCdma2000(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
);

VOS_VOID NAS_MSCC_ParseMlplSysLocTag3Gpp(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
);

VOS_VOID NAS_MSCC_ParseMlplSysLocTagCdma2000Hrpd(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_SYS_LOC_TAG_STRU     *pstSysLocTag
);

VOS_UINT8 NAS_MSCC_IsEnoughBitLenToParseLocParamVal(
    VOS_UINT8                           ucLocParamType,
    VOS_UINT32                          ulRemainBitLength
);

VOS_VOID NAS_MSCC_UpdateMlplRecInfo(
    NAS_MSCC_MLPL_PARSE_CTX_STRU       *pstMlplParseCtx,
    NAS_MSCC_MLPL_RECORD_STRU          *pstMlplRec,
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucIsDefaultRec
);

VOS_UINT8 NAS_MSCC_IsSystemTypeValid(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
);

VOS_VOID NAS_MSCC_ProcResrvBitsInBuff(
    VOS_UINT32                          ulParsedBitLen,
    VOS_UINT16                         *pusBitOffset
);

VOS_VOID NAS_MSCC_ResetMsplInfo(
    NAS_MSCC_MSPL_STRU                 *pstMsplInfo,
    VOS_UINT8                           ucMaxIndex
);

VOS_VOID NAS_MSCC_ResetMlplInfo(
    NAS_MSCC_MLPL_STRU                 *pstMlplInfo,
    VOS_UINT8                           ucMaxIndex
);

VOS_UINT8 NAS_MSCC_ConvertMsplBsrTimerLenToMillisec(
    NAS_MSCC_MSPL_HIGHER_PRI_SRCH_TIME_ENUM_UINT8           enInPriSrchTime,
    VOS_UINT32                                             *pusOutMillSec
);

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

#endif /* end of NasMsccMlplMsplParse.h */


