

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifndef __COMINTERFACE_H__
#define __COMINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum RRMM_RAT_TYPE_ENUM
{
    RRMM_RAT_TYPE_GSM = 0,                           /* GSM接入技术 */
    RRMM_RAT_TYPE_WCDMA,                             /* WCDMA接入技术 */
    RRMM_RAT_TYPE_LTE,                               /* LTE接入技术 */
    RRMM_RAT_TYPE_CDMA1X,                            /* 1x接入技术*/
    RRMM_RAT_TYPE_HRPD,                              /* HRPD接入技术*/
    RRMM_RAT_TYPE_BUTT
};
typedef VOS_UINT8 RRMM_RAT_TYPE_ENUM_UINT8;

enum RRMM_RAT_PRIO_ENUM
{
    RRMM_RAT_PRIO_NULL                = 0,               /* 该接入技术不存在    */
    RRMM_RAT_PRIO_LOW                 = 1,               /* 优先级较低   */
    RRMM_RAT_PRIO_MIDDLE              = 2,               /* 优先级中间   */
    RRMM_RAT_PRIO_HIGH                = 3,               /* 优先级较高   */
    RRMM_RAT_PRIO_BUTT
};
typedef VOS_UINT8  RRMM_RAT_PRIO_ENUM_UINT8;


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
/* 7.1 GAS和WAS公用消息 */

typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare23     :23;
}GSM_BAND_STRU;

typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;   
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpareBand10       :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}WCDMA_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulBand;
    
    GSM_BAND_STRU                       stBitBand;
}GSM_BAND_SET_UN;

typedef union
{
    VOS_UINT32                          ulBand;
    
    WCDMA_BAND_STRU                     stBitBand;
}WCDMA_BAND_SET_UN;

/*******************************************************************************
 结构名    : LTE_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE的频段定义,aulLteBand[0]代表低32,aulLteBand[1]代表高32个Band,
            例如 用户设置Band1,Band3,则aulLteBand[0]=0x05,aulLteBand[1]=0x00
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          aulLteBand[2];
}LTE_BAND_STRU;



typedef struct
{
    VOS_UINT32                          ulWcdmaBand;
}NAS_RRC_WCDMA_BAND_STRU;


typedef struct
{
    VOS_UINT32                          ulGsmBand;
}NAS_RRC_GSM_BAND_STRU;


/*******************************************************************************
 结构名    : NAS_RRC_TDSCDMA_BAND_STRU
 结构说明  : TD-SCDMA频段定义
             aulTdsBand[0]:
                           TDS_COMM_MTC_FREQ_BAND_A         = 0x01,     频点范围: 9504~9596  10054~10121
                           TDS_COMM_MTC_FREQ_BAND_E         = 0x10,     频点范围: 11504~11996
                           TDS_COMM_MTC_FREQ_BAND_F         = 0x20,     频点范围: 9404~9596
                           参见TDS_COMM_MTC_FREQ_BAND_LIST_ENUM_UINT8定义
             aulTdsBand[1]:无实际含义，与LTE结构对齐
             例如 用户设置F频段和E频段,则aulTdsBand[0]=0x06,aulTdsBand[1]=0x00
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          aulTdsBand[2];
}NAS_RRC_TDSCDMA_BAND_STRU;

/*******************************************************************************
 * Name        : CDMA_BAND_STRU
 *
 * Description : CDMA的频点
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCdmaBand;
}CDMA_BAND_STRU;


typedef struct
{
    LTE_BAND_STRU                       stLteBand;

    NAS_RRC_WCDMA_BAND_STRU             stWcdmaBand;
    NAS_RRC_GSM_BAND_STRU               stGsmBand;
    NAS_RRC_TDSCDMA_BAND_STRU           stTdsBand;
    /* NetScan Add Edn */
    CDMA_BAND_STRU                      stCdmaBand; /* CDMA频段仅对MMC通知LTE时有效，GU侧不关注 */
}NAS_RRC_USER_SET_FREQ_BAND_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
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

#endif /* end of ComInterface.h */
