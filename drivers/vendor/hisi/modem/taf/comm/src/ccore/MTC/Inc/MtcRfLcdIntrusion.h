

#ifndef __MTCRFLCDINTRUSION_H__
#define __MTCRFLCDINTRUSION_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 宏定义
****************************************************************************/
#define  MTC_MODEM_MAX_NUM              (3)                                     /* UE最多使用3个modem */
#define  MTC_RF_FREQ_MAX_NUM            MTC_RRC_GSM_MA_ARFCN_MAX_NUM            /* UE最多使用64个跳频或临区 */
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

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


typedef struct
{
    VOS_UINT32                          ulFreqNum;
    VOS_UINT16                          ausFreq[MTC_RF_FREQ_MAX_NUM];
}MTC_RF_FREQ_LIST_STRU;



typedef struct
{
    MTC_RF_FREQ_LIST_STRU               stGsmFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stWcdmaFreq;
    MTC_RF_FREQ_LIST_STRU               stLteFreq;
    MTC_RF_FREQ_LIST_STRU               stTdsFreq;
}MTC_RF_USING_FREQ_LIST_STRU;


typedef struct
{
    VOS_UINT32                          ulScellFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stNcellFreq;
}MTC_MODEM_FREQ_LIST_STRU;


typedef struct
{
    VOS_UINT16                          usPriScellMipiClkBitMap;
    VOS_UINT16                          usPriHoppingMipiClkBitMap;
    VOS_UINT16                          usPriNcellMipiClkBitMap;
    VOS_UINT16                          usSecScellMipiClkBitMap;
    VOS_UINT16                          usSecHoppingMipiClkBitMap;
    VOS_UINT16                          usSecNcellMipiClkBitMap;

}MTC_MODEM_MIPI_CLK_PRI_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID MTC_VerdictModemBitMapPri(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
);

VOS_VOID MTC_SndMtaMipiClkInfoInd(
    VOS_UINT16                          usMipiClk
);

VOS_VOID MTC_RcvRrcUsingFreqInd(VOS_VOID *pMsg);

VOS_UINT16 MTC_GetInterBitMap(
    VOS_UINT32                          ulFreq
);

VOS_UINT16 MTC_ProcScellClkBitMap(
    VOS_UINT32                          ulScellFreq
);

VOS_UINT16 MTC_ProcHoppingClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
);

VOS_UINT16 MTC_ProcNcellClkBitMap(
    MTC_RF_FREQ_LIST_STRU              *pstFreq
);

VOS_UINT16 MTC_ProcLcdMipiClkBitMap(
    MTC_MODEM_MIPI_CLK_PRI_STRU        *pstMomdemPri
);

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

#endif


