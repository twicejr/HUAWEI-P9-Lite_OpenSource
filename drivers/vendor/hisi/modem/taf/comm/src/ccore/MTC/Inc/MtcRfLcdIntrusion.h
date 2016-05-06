/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcRfLcdIntrusion.h
  版 本 号   : 初稿
  作    者   : 闫志吉/Y00213812
  生成日期   : 2014年03月05日
  最近修改   :
  功能描述   : MtcRfLcdIntrusion.c文件使用的数据结构和函数声明
  函数列表   :
  修改历史   :
  1.日    期   : 2014年04月05日
    作    者   : 闫志吉/Y00213812
    修改内容   : 创建文件

******************************************************************************/

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

/*******************************************************************************
 结构名    : MTC_RF_SCELL_FREQ_LIST_STRU
 结构说明  : GSM下，跳频或临区结构

 1.日    期   : 2014年03月05日
   作    者   : Y00213812
   修改内容   : 新生成
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFreqNum;
    VOS_UINT16                          ausFreq[MTC_RF_FREQ_MAX_NUM];
}MTC_RF_FREQ_LIST_STRU;


/*******************************************************************************
 结构名    : MTC_RF_USING_FREQ_LIST_STRU
 结构说明  : UE所有的服务小区列表

 1.日    期   : 2014年03月05日
   作    者   : Y00213812
   修改内容   : 新生成
*******************************************************************************/
typedef struct
{
    MTC_RF_FREQ_LIST_STRU               stGsmFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stWcdmaFreq;
    MTC_RF_FREQ_LIST_STRU               stLteFreq;
    MTC_RF_FREQ_LIST_STRU               stTdsFreq;
}MTC_RF_USING_FREQ_LIST_STRU;

/*******************************************************************************
 结构名    : MTC_MODEM_FREQ_LIST_STRU
 结构说明  : UE所有的服务小区列表

 1.日    期   : 2014年03月05日
   作    者   : Y00213812
   修改内容   : 新生成
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulScellFreq;
    MTC_RF_FREQ_LIST_STRU               stGsmHoppingFreq;
    MTC_RF_FREQ_LIST_STRU               stNcellFreq;
}MTC_MODEM_FREQ_LIST_STRU;

/*******************************************************************************
 结构名    : MTC_MODEM_MIPI_CLK_PRI_STRU
 结构说明  : MODEM的MIPICLK位图优先级

 1.日    期   : 2014年03月05日
   作    者   : Y00213812
   修改内容   : 新生成
*******************************************************************************/
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


