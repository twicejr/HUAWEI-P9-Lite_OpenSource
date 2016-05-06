/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcCalcFreq.c
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2014年03月04日
  最近修改   :
  功能描述   : 通过接入层传入的频点信息，计算对应的频率信息
  函数列表   :
  修改历史   :
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : 新生成

说明:
1. GU侧的函数由物理层上官声长 00266224提供
2. L侧的函数由
3. TD侧的函数由
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "MtcCalcFreq.h"
#include "MtcCtx.h"
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: j00174725; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_CALC_FREQ_C
/*lint +e767 修改人: j00174725; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_LTE)
/* FDD模式，下行最低频率FDL_low(单位100K HZ), FDD:E-UTRA Operatingn Band 取1~14或17,20 */
static VOS_UINT16 g_ausFreqDlLowFdd[] =
{21100,  19300,  18050,  21100, /* Band1 ~Band4 */
 8690,   8750,   26200,  9250,  /* Band5 ~Band8 */
 18449,  21100,  14759,  7280,  /* Band9 ~Band12 */
 7460,   7580,   0,      0,     /* Band13~Band16 */
 7340,   8600,   8750,   7910,  /* Band17~Band20 */
 14959,  35100,  21800,  15250,  /* Band21~Band24 */
 19300,  8590,   8520,  7580,     /* Band25~Band28*/
 7170,   23500,  4625            /* Band29~Band31*/
};

/* NOffs-DL, FDD:E-UTRA Operatingn Band 取1~14或17~21,24 */
static VOS_UINT16 g_ausNOffsetDlFdd[] =
{0,      600,   1200,  1950,    /* Band1 ~Band4 */
 2400,   2650,  2750,  3450,    /* Band5 ~Band8 */
 3800,   4150,  4750,  5000,    /* Band9 ~Band12 */
 5180,   5280,  0,     0,       /* Band13~Band16 */
 5730,   5850,  6000,  6150,    /* Band17~Band20 */
 6450,   6600,  7500,  7700,    /* Band21~Band24 */
 8040,   8690,  9040,  9210,     /* Band25~Band28*/
 9660,   9770,  9870            /* Band29~Band31*/
};

/* TDD模式上下行最低频率, TDD:E-UTRA Operatingn Band 取33~44 */
static VOS_UINT16 g_ausFreqLowTdd[] =
{19000,  20100,  18500,  19300,
 19100,  25700,  18800,  23000,
 24960,  34000,  36000,  7030
};

/* NOffs-DL or NOffs-UL, TDD:E-UTRA Operatingn Band 取33~44 */
static VOS_UINT16 g_ausNOffsetTdd[] =
{36000,  36200,  36350,  36950,
 37550,  37750,  38250,  38650,
 39650,  41590,  43590,  45590
};

#endif

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_GSM_GetBandInfoByArfcn
 功能描述  : 根据下行频点找到对应的Band信息
 输入参数  : VOS_UINT16 usDlFreq 下行频点
 输出参数  : 无
 返 回 值  : VOS_UINT16 返回Band NO.
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年03月10日
    作    者   : y00213812
    修改内容   : 新增函数
    说明:从GAS移植函数

*****************************************************************************/
VOS_UINT16 MTC_GSM_GetBandInfoByArfcn( VOS_UINT16 usArfcn )
{
    VOS_UINT16   usBandInfo = MTC_GAS_BAND_TYPE_UNKNOWN;

    usArfcn                 = 0x0FFF & usArfcn;

    /* 900频段 */
    if ( (usArfcn <= 124)  || ( (usArfcn >= 955) && (usArfcn <= 1023) ))
    {
        usBandInfo = MTC_GSM_BAND_TYPE_P900 | MTC_GSM_BAND_TYPE_E900 | MTC_GSM_BAND_TYPE_R900 ;
    }
    /* 重叠频段 */
    else if ( (usArfcn >= 512) && (usArfcn <= 810) )
    {
        usBandInfo = MTC_GSM_BAND_TYPE_1800 | MTC_GSM_BAND_TYPE_1900;
    }
    /* 1800频段 */
    else if ( (usArfcn > 810) && (usArfcn <= 885) )
    {
        usBandInfo = MTC_GSM_BAND_TYPE_1800;
    }
    /* 450频段 */
    else if ( (usArfcn >= 259) && (usArfcn <= 293) )
    {
        usBandInfo = MTC_GSM_BAND_TYPE_450;
    }

    /* 480频段 */
    else if ( (usArfcn >= 306) && (usArfcn <= 340) )
    {
        usBandInfo = MTC_GSM_BAND_TYPE_480;
    }

    /* 850频段 */
    else if ( (usArfcn >= 128) && (usArfcn <= 251) )
    {
        usBandInfo = MTC_GSM_BAND_TYPE_850;
    }
    else
    {
    }

    return usBandInfo;

}

/*****************************************************************************
 函 数 名  : MTC_GSM_GetBandInfoByArfcnWithBandIndicator
 功能描述  : 根据下行频点和Band指示找到对应的Band信息
 输入参数  : VOS_UINT16 usDlFreq 下行频点
             VOS_UINT8 ucBandIndicator --Band指示, 指示当前频点是 1800 系统 或 1900 系统
 输出参数  : 无
 返 回 值  : VOS_UINT16 返回Band NO.
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年03月10日
    作    者   : y00213812
    修改内容   : 新增函数
    说明:从GAS移植函数

*****************************************************************************/

VOS_UINT16 MTC_GSM_GetBandInfoByArfcnWithBandIndicator(
    VOS_UINT16                          usArfcn,
    VOS_UINT16                          usBandIndicator
)
{
    VOS_UINT16                          usBandInfo;

    usBandInfo  = MTC_GSM_GetBandInfoByArfcn(usArfcn);

    /* 属于1800和1900重合频段 */
    if ( ( MTC_GSM_BAND_TYPE_1800 | MTC_GSM_BAND_TYPE_1900 ) == usBandInfo )
    {
        /* 1800频段 */
        if (RRC_MTC_GSM_BANDINDICATOR_DCS1800 == usBandIndicator)
        {
            usBandInfo = MTC_GSM_BAND_TYPE_1800;
        }
        /* 1900频段 */
        else
        {
            usBandInfo = MTC_GSM_BAND_TYPE_1900;
        }
    }
    else
    {
          MTC_WARNING_LOG("MTC_GSM_GetBandInfoByArfcnWithBandIndicator:Can not get BAND INFO by ARFCN" );
    }

    return usBandInfo;

}
/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) Begin */
/*****************************************************************************
 函 数 名  : MTC_CalcGsmDlFreq
 功能描述  : 将频点号换算成实际频率值，扩大十倍（单位10×MHz）
 输入参数  : VOS_UINT16  uhwBand
             VOS_UINT16 uhwFreqIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : j00174725
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 MTC_CalcGsmDlFreq(
    VOS_UINT16                          ushwBand,
    VOS_UINT16                          ushwFreqIndex
)
{
    VOS_UINT16                          ushwFreqValAmpTen;
    VOS_UINT16                          ushwFreqValAmpTenTmp;

    ushwFreqValAmpTen                   = 0;

    switch( ushwBand )
    {
        case MTC_GSM_BAND_TYPE_850:             /* 850 */
            ushwFreqValAmpTenTmp = (VOS_UINT16)(8242 + (2*(ushwFreqIndex-128)));
            ushwFreqValAmpTen    = (VOS_UINT16)ushwFreqValAmpTenTmp+450;
            break;

        case MTC_GSM_BAND_TYPE_P900 | MTC_GSM_BAND_TYPE_E900 | MTC_GSM_BAND_TYPE_R900:             /* 900 */

           if(ushwFreqIndex<125)
            {
                ushwFreqValAmpTenTmp = (VOS_UINT16)(8900 + (2*ushwFreqIndex));
            }
            else
            {
                ushwFreqValAmpTenTmp = (VOS_UINT16)(8900 + (2*(ushwFreqIndex-1024)));
            }

            ushwFreqValAmpTen        = (VOS_UINT16)ushwFreqValAmpTenTmp+450;
            break;

        case MTC_GSM_BAND_TYPE_1800:             /* 1800 */
            ushwFreqValAmpTenTmp = (VOS_UINT16)(17102 + (2*(ushwFreqIndex-512)));
            ushwFreqValAmpTen    = (VOS_UINT16)ushwFreqValAmpTenTmp+950;
            break;

        case MTC_GSM_BAND_TYPE_1900:             /* 1900 */
            ushwFreqValAmpTenTmp = (VOS_UINT16)(18502 + (2*(ushwFreqIndex-512)));
            ushwFreqValAmpTen    = (VOS_UINT16)ushwFreqValAmpTenTmp+800;
            break;

        default:
            break;

         }

    return ushwFreqValAmpTen;

}

/*****************************************************************************
 函 数 名  : MTC_WCDMA_GetBandInfoByDlArfcn
 功能描述  : 根据下行频点找到对应的频段号
 输入参数  : VOS_UINT16 usDlFreq 下行频点
 输出参数  : 无
 返 回 值  : VOS_UINT16 返回Band NO.
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年03月10日
    作    者   : j00174725
    修改内容   : 新增函数
    说明:移植WAS WAS_COMM_FindFreqBandNoByUlFreq 函数

*****************************************************************************/
VOS_UINT16 MTC_WCDMA_GetBandInfoByDlArfcn(VOS_UINT16 usDlFreq)
{
    VOS_UINT32                          ulFreqBandLoop;
    VOS_UINT32                          ulFreqLoop;
    VOS_UINT16                          usFreqBandNo;

    VOS_UINT16                           usBand2DlFreqList[MTC_WAS_FREQ_BAND2_ADD_MAX_FREQ_NUM]=
                                                 {412,437,462,487,512,537,562,587,612,637,662,687};

    VOS_UINT16                           usBand4DlFreqList[MTC_WAS_FREQ_BAND4_ADD_MAX_FREQ_NUM]=
                                                 {1887,1912,1937,1962,1987,2012,2037,2062,2087};

    VOS_UINT16                           usBand5DlFreqList[MTC_WAS_FREQ_BAND5_ADD_MAX_FREQ_NUM]=
                                                 {1007,1012,1032,1037,1062,1087};
    /* 由于band6在Band5范围内，所以去掉band6 */
    /* 由于band7不用，也删除 */

    VOS_UINT16                           usBand19AddDlFreqList[MTC_WAS_FREQ_BAND19_ADD_MAX_FREQ_NUM] =
                                                 {787,812,837};

    /*初始化Band信息为无效值:PS_NULL_UINT16*/
    usFreqBandNo         = MTC_FREQ_BAND_NONE;

    /* 根据下行的频点找  */
    for (ulFreqBandLoop = 1; ulFreqBandLoop <= MTC_FREQ_BAND19; ulFreqBandLoop++)
    {
        switch ( ulFreqBandLoop )
        {
            case  MTC_FREQ_BAND1:
                if (( usDlFreq <= MTC_WAS_FREQ_BAND1_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND1_DL_LOW_FREQ))
                {
                    usFreqBandNo = MTC_FREQ_BAND1;
                }
                break;
            case MTC_FREQ_BAND2 :
                if (( usDlFreq <= MTC_WAS_FREQ_BAND2_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND2_DL_LOW_FREQ))
                {
                    usFreqBandNo = MTC_FREQ_BAND2;
                }
                else
                {
                    for ( ulFreqLoop = 0 ; ulFreqLoop < MTC_WAS_FREQ_BAND2_ADD_MAX_FREQ_NUM; ulFreqLoop++ )
                    {
                        if (  usDlFreq == usBand2DlFreqList[ulFreqLoop])
                        {
                            usFreqBandNo  = MTC_FREQ_BAND2;
                            break;
                        }
                    }
                }
                break;
            case MTC_FREQ_BAND3 :
                if (( usDlFreq <= MTC_WAS_FREQ_BAND3_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND3_DL_LOW_FREQ))
                {
                    usFreqBandNo = MTC_FREQ_BAND3;
                }
                break;
            case MTC_FREQ_BAND4 :
                if (( usDlFreq <= MTC_WAS_FREQ_BAND4_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND4_DL_LOW_FREQ))
                {
                    usFreqBandNo  = MTC_FREQ_BAND4;
                }
                else
                {
                    for ( ulFreqLoop = 0 ; ulFreqLoop < MTC_WAS_FREQ_BAND4_ADD_MAX_FREQ_NUM; ulFreqLoop++ )
                    {
                        if (  usDlFreq == usBand4DlFreqList[ulFreqLoop])
                        {
                            usFreqBandNo = MTC_FREQ_BAND4;
                            break;
                        }
                    }
                }
                break;
            case MTC_FREQ_BAND5:
                if (( usDlFreq <= MTC_WAS_FREQ_BAND5_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND5_DL_LOW_FREQ))
                {
                    usFreqBandNo = MTC_FREQ_BAND5;
                }
                else
                {
                    for ( ulFreqLoop = 0 ; ulFreqLoop < MTC_WAS_FREQ_BAND5_ADD_MAX_FREQ_NUM; ulFreqLoop++ )
                    {
                        if (  usDlFreq == usBand5DlFreqList[ulFreqLoop])
                        {
                            usFreqBandNo = MTC_FREQ_BAND5;
                            break;
                        }
                    }
                }
                break;
            /* 由于band6在Band5范围内，所以去掉band6 */
            /* 由于band7不用，也删除 */
            case MTC_FREQ_BAND8 :
                if (( usDlFreq <= MTC_WAS_FREQ_BAND8_DL_HIGH_FREQ )&&(usDlFreq >= MTC_WAS_FREQ_BAND8_DL_LOW_FREQ))
                {
                    usFreqBandNo = MTC_FREQ_BAND8;
                }
                break;
            case MTC_FREQ_BAND9 :
                if ( (usDlFreq <= MTC_WAS_FREQ_BAND9_DL_HIGH_FREQ) && (usDlFreq >= MTC_WAS_FREQ_BAND9_DL_LOW_FREQ) )
                {
                    usFreqBandNo = MTC_FREQ_BAND9;
                }
                break;
            case MTC_FREQ_BAND11 :
                if ( (usDlFreq <= MTC_WAS_FREQ_BAND11_DL_HIGH_FREQ) && (usDlFreq >= MTC_WAS_FREQ_BAND11_DL_LOW_FREQ) )
                {
                    usFreqBandNo = MTC_FREQ_BAND11;
                }
                break;
            case MTC_FREQ_BAND19 :
                if ((usDlFreq <= MTC_WAS_FREQ_BAND19_DL_HIGH_FREQ) && (usDlFreq >= MTC_WAS_FREQ_BAND19_DL_LOW_FREQ))
                {
                    usFreqBandNo         = MTC_FREQ_BAND19;
                }
                else
                {
                    for (ulFreqLoop = 0; ulFreqLoop < MTC_WAS_FREQ_BAND19_ADD_MAX_FREQ_NUM; ulFreqLoop++)
                    {
                        if (usDlFreq == usBand19AddDlFreqList[ulFreqLoop])
                        {
                            usFreqBandNo         = MTC_FREQ_BAND19;
                            break;
                        }
                    }
                }

                break;
            default:

                break;
        }

        if (MTC_FREQ_BAND_NONE != usFreqBandNo)
        {
            break;
        }

    }

    if ( MTC_FREQ_BAND_NONE == usFreqBandNo )
    {
        /*打印输入的下行频点号,返回错误*/
        MTC_WARNING1_LOG("MTC_FindFreqBandNoByDlFreq:DlFreq Can not find FreqBand",usDlFreq);
    }

    return usFreqBandNo;
}


/*****************************************************************************
细节参考25.101协议
1、上下行频点的计算公式:
Uplink:     NU = 5 * (FUL - FUL_Offset),for the carrier frequency range FUL_low   FUL      FUL_high
Downlink:   ND = 5 * (FDL - FDL_Offset),for the carrier frequency range FDL_low   FDL      FDL_high

2、频带中一般频点的相关参数
UARFCN definition (general)
Band    FUL_Offset [MHz] FUL_low  FUL_high   FDL_Offset [MHz]   FDL_low FDL_high
I       0               1922.4    1977.6     0                  2112.4  2167.6
II      0               1852.4    1907.6     0                  1932.4  1987.6
III     1525            1712.4    1782.6     1575               1807.4  1877.6
IV      1450            1712.4    1752.6     1805               2112.4  2152.6
V       0               826.4     846.6      0                  871.4   891.6
VI      0               832.4     837.6      0                  877.4   882.6
VIII    340             882.4     912.6      340                927.4   957.6
IX      0               1752.4    1782.4     0                  1847.4  1877.4

3、频带中离散频点的相关参数
   离散频点的绝对频率在频带范围内，但频点号计算方式和一般频点不同
   正常频点是200khz边界，而离散频点是100khz的边界
UARFCN definition (additional channels)
Band    FUL_Offset [MHz]    FDL_Offset [MHz]
I         -                     -
II      1850.1              1850.1
III       -                     -
IV      1380.1              1735.1
V       670.1               670.1
VI      670.1               670.1
VII     2030.1              2105.1
VIII      -                     -
IX        -                     -

4、上下行频差
TX-RX frequency separation
Operating Band  TX-RX frequency separation
I               190 MHz
II              80 MHz.
III             95 MHz.
IV              400 MHz
V               45 MHz
VI              45 MHz
VIII            45 MHz
IX              95 MHz

5、频点号范围

Band    Uplink (UL)     Downlink (DL)
I       9612 to 9888    10562 to 10838
II      9262 to 9538    9662 to 9938
III     937 to 1288     1162 to 1513
IV      1312 to 1513    1537 to 1738
V       4132 to 4233    4357 to 4458
VI      4162 to 4188    4387 to 4413
VIII    2712 to 2863    2937 to 3088
IX      8762 to 8912    9237 to 9387

处理简单起见，不在正常频点号范围内的均认为是离散频点号，按照离散频点号的频率偏置来处理
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MTC_CalcWcdmaDlFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  : VOS_UINT16         uhwFreqBandId
             VOS_UINT16         uhwFreqNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : j00174725
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_UINT16 MTC_CalcWcdmaDlFreq(
    VOS_UINT16                          ushwFreqBandId,
    VOS_UINT16                          ushwDlFreqNum
)
{
    MTC_RF_WCDMA_FREQ_BAND_INFO_STRU   *pstWcdmaBandInfo;
    VOS_UINT16                          ushwFreqOffset;
    VOS_UINT16                          ushwI;
    /* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) Begin */
    MTC_RF_WCDMA_FREQ_BAND_INFO_STRU    astWFreqBandInfo[FREQ_BAND_NUM]
    = { {MTC_FREQ_BAND1, 1900, 10838, 10562,     0,     0, 9888, 9612,     0,     0, 60,21100},
        {MTC_FREQ_BAND2,  800,  9938,  9662,     0, 18501, 9538, 9262,     0, 18501, 60,19300},
        {MTC_FREQ_BAND3,  950,  1513,  1162, 15750,     0, 1288,  937, 15250,     0, 75,18050},
        {MTC_FREQ_BAND4, 4000,  1738,  1537, 18050, 17351, 1513, 1312, 14500, 13801, 45,21100},
        {MTC_FREQ_BAND5,  450,  4458,  4357,     0,  6701, 4233, 4132,     0,  6701, 25, 8690},
        {MTC_FREQ_BAND6,  450,  4413,  4387,     0,  6701, 4188, 4162,     0,  6701, 10, 8750},
        {MTC_FREQ_BAND8,  450,  3088,  2937,  3400,     0, 2863, 2712,  3400,     0, 35, 9250},
        {MTC_FREQ_BAND9,  950,  9387,  9237,     0,     0, 8912, 8762,     0,     0, 35,18449},
        {MTC_FREQ_BAND11, 480,  3787,  3712,  7360,     0, 3562, 3487,  7330,     0, 20,14759},
        {MTC_FREQ_BAND19, 450,   763,   712,  7350,  7201,  363,  312,  7700,  7551, 15, 8751}};
    /* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) End */

    /* 去除异频频点的偏移量*/
    ushwDlFreqNum                       &= DC_MIMO_REMOVEINTERFREQOFF;
    ushwFreqOffset                       = 0;

    for ( ushwI = 0; ushwI < FREQ_BAND_NUM; ushwI++ )
    {
        pstWcdmaBandInfo                 = &(astWFreqBandInfo[ushwI]);

        if ( ushwFreqBandId == pstWcdmaBandInfo->uhwFreqBandId )
        {
            /* 属于一般频点 */
            if ( ( ushwDlFreqNum <= pstWcdmaBandInfo->uhwDlGeneralFreqNum_High )
              && ( ushwDlFreqNum >= pstWcdmaBandInfo->uhwDlGeneralFreqNum_Low ) )
            {
                ushwFreqOffset           = pstWcdmaBandInfo->uhwDlGeneralOffset;
            }
            /* 属于离散频点 */
            else
            {
                ushwFreqOffset           = pstWcdmaBandInfo->uhwDlAddOffset;
            }
            break;
        }
    }

    /* 获得绝对频率 */
    return (VOS_UINT16)(( ushwDlFreqNum << 1 ) + ushwFreqOffset);

}

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) End */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : MTC_LTE_GetBandInfoByDlArfcn
 功能描述  : 根据下行频点找到对应的频段号
 输入参数  : VOS_UINT16 usDlFreq 下行频点
 输出参数  : 无
 返 回 值  : VOS_UINT16 返回Band NO.
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年03月10日
    作    者   : j00174725
    修改内容   : 新增函数
    说明:移植LTE RRC_COMM_CalculateBandIndByDlEarfcn 函数
  2.日    期   : 2015年7月20日
    作    者   : w000316404
    修改内容   : R11协议升级(LTE频点配置值扩展)
*****************************************************************************/
VOS_UINT16  MTC_LTE_GetBandInfoByDlArfcn( VOS_UINT32 ulDlEarfcn)
{
    VOS_UINT8                           ucLoop = 0;
    VOS_UINT16                          usFreqBand;
    VOS_UINT32                          aulDlEarfcn[][2] = {{0, 0},
      {0     , 599   }, {600,  1199  }, {1200, 1949 }, {1950, 2399},     /* Band1 ~Band4 */
      {2400 , 2649  }, {2650, 2749  }, {2750, 3449 }, {3450, 3799},     /* Band5 ~Band8 */
      {3800 , 4149  }, {4150, 4749  }, {4750, 4949 }, {5000, 5179},     /* Band9 ~Band12 */
      {5180 , 5279  }, {5280, 5379  }, {0    , 0     }, {0,    0    },     /* Band13~Band16 */
      {5730 , 5849  }, {5850, 5999  }, {6000, 6149  }, {6150, 6449},    /* Band17~Band20 */
      {6450 , 6599  }, {6600, 7390  }, {7500, 7699  }, {7700, 8039},    /* Band21~Band24 */
      {8040 , 8689  }, {8690, 9039  }, {9040, 9209  }, {9210, 9659},    /* Band25~Band28 */
      {9660 , 9769  }, {9770, 9869  }, {9870, 9919  }, {0    , 0   },     /* Band29~Band32 */
      {36000, 36199}, {36200, 36349}, {36350, 36949}, {36950, 37549}, /* Band33~Band36 */
      {37550, 37749}, {37750, 38249}, {38250, 38649}, {38650, 39649}, /* Band37~Band40 */
      {39650, 41589}, {41590, 43589}, {43590, 45589}, {45590, 46589}};/* Band41~Band44 */

    /* 初始化频带指示 */
    usFreqBand = MTC_FREQ_BAND_NONE;

    /* 根据36.101协议中表 5.7.3-1推算DlEarfcn所在的频带 */
    for (ucLoop = MTC_FREQ_BAND1; ucLoop <= MTC_FREQ_BAND44; ucLoop++)
    {
        if ((ulDlEarfcn >= aulDlEarfcn[ucLoop][0]) && (ulDlEarfcn <= aulDlEarfcn[ucLoop][1]))
        {
            usFreqBand = ucLoop;

            break;
        }
    }

    return usFreqBand;
}

/*****************************************************************************
 函 数 名  : MTC_CalcLteDlFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  : VOS_UINT16         uhwFreqBandId
             VOS_UINT16         uhwFreqNum
 输出参数  : VOS_UINT16         *puhwDlAbsFreq
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
  2.日    期   : 2015年7月20日
   作    者   : w000316404
   修改内容   : R11协议升级(LTE频点配置值扩展)

*****************************************************************************/
VOS_UINT16  MTC_CalcLteDlFreq(
    VOS_UINT16                          ucFreqBandIndicator,
    VOS_UINT32                          ulDlEarfcn
)
{
    VOS_UINT16                          usDlFreq;

    usDlFreq = 0;

    /* 频带指示1~14,17~21,24为FDD频带，33~44为TDD频带 */
    if (MTC_COMM_CHECK_IS_FDD_BAND_IND(ucFreqBandIndicator))
    {
        /* 36.101: FDL = FDL_low + 0.1(NDL - NOffs-DL), 下行频率FDL的单位为MHZ，
        为了去浮点化，对公式放大10倍处理，所以实际计算频率单位为100KHZ */
        usDlFreq = (g_ausFreqDlLowFdd[ucFreqBandIndicator-1] + (VOS_UINT16)ulDlEarfcn - g_ausNOffsetDlFdd[ucFreqBandIndicator-1]);
    }
    else if (MTC_COMM_CHECK_IS_PROCOL_TDD_BAND_IND(ucFreqBandIndicator))
    {
        /* 36.101: FDL = FDL_low + 0.1(NDL - NOffs-DL), 下行频率FDL的单位为MHZ，
        为了去浮点化，对公式放大10倍处理，所以实际计算频率单位为100KHZ */
        usDlFreq = (g_ausFreqLowTdd[ucFreqBandIndicator-33] + (VOS_UINT16)ulDlEarfcn - g_ausNOffsetTdd[ucFreqBandIndicator-33]);
    }
    else
    {
    }

    return usDlFreq;

}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : MTC_CalcTdsDlFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  : VOS_UINT16         uhwFreqNum
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_UINT16  MTC_CalcTdsDlFreq(VOS_UINT16 usDlEarfcn)
{
    return (VOS_UINT16)(usDlEarfcn * MTC_TDS_FRQ_UNIN);
}

/*****************************************************************************
 函 数 名  : MTC_TDS_GetBandInfoByDlArfcn
 功能描述  : 根据下行频点找到对应的Band
 输入参数  : VOS_UINT16 usDlFreq 下行频点
 输出参数  : 无
 返 回 值  : VOS_UINT16 返回Band NO.
 调用函数  :
 被调函数  :

 修改历史  :
  1.日    期   : 2014年03月10日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_UINT16  MTC_TDS_GetBandInfoByDlArfcn(VOS_UINT32 ulDlEarfcn)
{
    VOS_UINT8                           ucLoop = 0;
    VOS_UINT16                          usFreqBand;
    VOS_UINT32                          aulDlEarfcn[][2] = {{0, 0},
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band1 ~Band4 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band5 ~Band8 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band9 ~Band12 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band13~Band16 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band17~Band20 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band21~Band24 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band25~Band28 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     },             /* Band29~Band32 */
      {0, 0}, {20100, 20250}, {0     , 0     }, {0     , 0     },             /* Band33~Band36 */
      {0, 0}, {0     , 0     }, {18800, 19200}, {23200, 23700},             /* Band37~Band40 */
      {0, 0}, {0     , 0     }, {0     , 0     }, {0     , 0     }};            /* Band41~Band44 */

    /* 初始化频带指示 */
    usFreqBand = 0;

    for (ucLoop = MTC_FREQ_BAND1; ucLoop <= MTC_FREQ_BAND44; ucLoop++)
    {
        if ((ulDlEarfcn >= aulDlEarfcn[ucLoop][0]) && (ulDlEarfcn <= aulDlEarfcn[ucLoop][1]))
        {
            usFreqBand = ucLoop;

            break;
        }
    }

    return usFreqBand;
}


#endif

#if 0
/*****************************************************************************
 函 数 名  : MTC_FillGsmNcellFreq
 功能描述  : Gsm主模时计算邻区
 输入参数  : pstRfUsingFreqList
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_FillGsmNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    VOS_UINT32                          i;

    if (pstRfUsingFreqList->stGsmFreq.ulFreqNum > 1)
    {
        for (i = 1; i < pstRfUsingFreqList->stGsmFreq.ulFreqNum; i++)
        {
            pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stGsmFreq.ausFreq[i];
            pstRfFreqList->ulFreqNum++;
        }
    }

    for (i = 0; i < pstRfUsingFreqList->stWcdmaFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stWcdmaFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    for (i = 0; i < pstRfUsingFreqList->stLteFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stLteFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

    for (i = 0; i < pstRfUsingFreqList->stTdsFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stTdsFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }
#endif

}

/*****************************************************************************
 函 数 名  : MTC_FillWcdmaNcellFreq
 功能描述  : WCDMA主模时计算邻区
 输入参数  : pstRfUsingFreqList
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_FillWcdmaNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    VOS_UINT32                          i;

    if (pstRfUsingFreqList->stWcdmaFreq.ulFreqNum > 1)
    {
        for (i = 1; i < pstRfUsingFreqList->stWcdmaFreq.ulFreqNum; i++)
        {
            pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stWcdmaFreq.ausFreq[i];
            pstRfFreqList->ulFreqNum++;
        }
    }

    for (i = 0; i < pstRfUsingFreqList->stGsmFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stGsmFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

#if (FEATURE_ON == FEATURE_LTE)
    for (i = 0; i < pstRfUsingFreqList->stLteFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stLteFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

    for (i = 0; i < pstRfUsingFreqList->stTdsFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stTdsFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }
#endif

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : MTC_FillLteNcellFreq
 功能描述  : LTE主模时计算邻区
 输入参数  : pstRfUsingFreqList
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_FillLteNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    VOS_UINT32                          i;

    if (pstRfUsingFreqList->stLteFreq.ulFreqNum > 1)
    {
        for (i = 1; i < pstRfUsingFreqList->stLteFreq.ulFreqNum; i++)
        {
            pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stLteFreq.ausFreq[i];
            pstRfFreqList->ulFreqNum++;
        }
    }

    for (i = 0; i < pstRfUsingFreqList->stGsmFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stGsmFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

    for (i = 0; i < pstRfUsingFreqList->stWcdmaFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stWcdmaFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

    for (i = 0; i < pstRfUsingFreqList->stTdsFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stTdsFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 函 数 名  : MTC_FillTdsNcellFreq
 功能描述  : TDS主模时计算邻区
 输入参数  : pstRfUsingFreqList
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_FillTdsNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    VOS_UINT32                          i;

    if (pstRfUsingFreqList->stTdsFreq.ulFreqNum > 1)
    {
        for (i = 1; i < pstRfUsingFreqList->stTdsFreq.ulFreqNum; i++)
        {
            pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stTdsFreq.ausFreq[i];
            pstRfFreqList->ulFreqNum++;
        }
    }

    for (i = 0; i < pstRfUsingFreqList->stGsmFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stGsmFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

    for (i = 0; i < pstRfUsingFreqList->stWcdmaFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stWcdmaFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

    for (i = 0; i < pstRfUsingFreqList->stLteFreq.ulFreqNum; i++)
    {
        pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum] = pstRfUsingFreqList->stLteFreq.ausFreq[i];
        pstRfFreqList->ulFreqNum++;
    }

}
#endif
#endif

/*****************************************************************************
 函 数 名  : MTC_FillNcellFreq
 功能描述  : TDS主模时计算邻区
 输入参数  : pstRfUsingFreqList
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_FillNcellFreq(
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfUsingFreqList,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    /* 填GSM频率到队列中 */
    pstRfFreqList->ulFreqNum = 0;
    PS_MEM_CPY(&pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum],
               &pstRfUsingFreqList->stGsmFreq.ausFreq[0],
               pstRfUsingFreqList->stGsmFreq.ulFreqNum * sizeof(VOS_UINT16));

    pstRfFreqList->ulFreqNum += pstRfUsingFreqList->stGsmFreq.ulFreqNum;

    /* 填WCDMA频率到队列中 */
    PS_MEM_CPY(&pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum],
               &pstRfUsingFreqList->stWcdmaFreq.ausFreq[0],
               pstRfUsingFreqList->stWcdmaFreq.ulFreqNum * sizeof(VOS_UINT16));

    pstRfFreqList->ulFreqNum += pstRfUsingFreqList->stWcdmaFreq.ulFreqNum;

#if (FEATURE_ON == FEATURE_LTE)
    /* 填LTE频率到队列中 */
    PS_MEM_CPY(&pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum],
               &pstRfUsingFreqList->stLteFreq.ausFreq[0],
               pstRfUsingFreqList->stLteFreq.ulFreqNum * sizeof(VOS_UINT16));

    pstRfFreqList->ulFreqNum += pstRfUsingFreqList->stLteFreq.ulFreqNum;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* 填TDS频率到队列中 */
    PS_MEM_CPY(&pstRfFreqList->ausFreq[pstRfFreqList->ulFreqNum],
               &pstRfUsingFreqList->stTdsFreq.ausFreq[0],
               pstRfUsingFreqList->stTdsFreq.ulFreqNum * sizeof(VOS_UINT16));

    pstRfFreqList->ulFreqNum += pstRfUsingFreqList->stTdsFreq.ulFreqNum;
#endif
}

/*****************************************************************************
 函 数 名  : MTC_CalcWcdmaDlFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  :

 输出参数  : VOS_UINT16         *puhwDlAbsFreq
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_CalcHoppingFreq(
    MTC_RF_FREQ_LIST_STRU              *pstGsmFreqInfo,
    MTC_RF_FREQ_LIST_STRU              *pstRfFreqList
)
{
    pstRfFreqList->ulFreqNum = pstGsmFreqInfo->ulFreqNum;

    PS_MEM_CPY(&pstRfFreqList->ausFreq[0],
               &pstGsmFreqInfo->ausFreq[0],
               pstGsmFreqInfo->ulFreqNum * sizeof(VOS_UINT16));

}

/*****************************************************************************
 函 数 名  : MTC_ChangeRfArfcnToFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  : pstUsingFreq
 输出参数  : *pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增

*****************************************************************************/
VOS_VOID  MTC_ChangeRfArfcnToFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq,
    MTC_RF_USING_FREQ_LIST_STRU        *pstRfFreqList
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulLteArfNum;
    VOS_UINT16                          usArfNum;
    VOS_UINT16                          usBandNum;
    VOS_UINT16                          usBandIndicator;

    /* 初始化可维可测信息 */
    MTC_DEBUG_InitRfUsingFreqListInfo();

    /* 转换GSM的频点为频率 */
    pstRfFreqList->stGsmFreq.ulFreqNum = pstUsingFreq->stGsmFreqInfo.ucGsmArfcnNum;
    for (ulIndex = 0; ulIndex < pstUsingFreq->stGsmFreqInfo.ucGsmArfcnNum; ulIndex++)
    {
        usBandIndicator = (VOS_UINT8)(pstUsingFreq->stGsmFreqInfo.astGsmArfcnList[ulIndex].enBandInd);
        usArfNum         = pstUsingFreq->stGsmFreqInfo.astGsmArfcnList[ulIndex].usGsmArfcn;
        usBandNum        = MTC_GSM_GetBandInfoByArfcnWithBandIndicator(usArfNum, usBandIndicator);

        pstRfFreqList->stGsmFreq.ausFreq[ulIndex] = MTC_CalcGsmDlFreq(usBandNum, usArfNum);

        /* 记录可维可测信息 */
        MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(stGsmFreq);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmFreq, usArfcn, usArfNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmFreq, usBandId, usBandNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmFreq, usFreq, pstRfFreqList->stGsmFreq.ausFreq[ulIndex], ulIndex);
    }

    /* 转换GSM的跳时频频率 */
    pstRfFreqList->stGsmHoppingFreq.ulFreqNum = pstUsingFreq->stGsmFreqInfo.ucGsmMaArfcnNum;
    for (ulIndex = 0; ulIndex < pstUsingFreq->stGsmFreqInfo.ucGsmMaArfcnNum; ulIndex++)
    {
        usBandIndicator = (VOS_UINT8)(pstUsingFreq->stGsmFreqInfo.astGsmMaArfcnList[ulIndex].enBandInd);
        usArfNum         = pstUsingFreq->stGsmFreqInfo.astGsmMaArfcnList[ulIndex].usGsmArfcn;
        usBandNum        = MTC_GSM_GetBandInfoByArfcnWithBandIndicator(usArfNum, usBandIndicator);

        pstRfFreqList->stGsmHoppingFreq.ausFreq[ulIndex] = MTC_CalcGsmDlFreq(usBandNum, usArfNum);

        /* 记录可维可测信息 */
        MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(stGsmHoppingFreq);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmHoppingFreq, usArfcn, usArfNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmHoppingFreq, usBandId, usBandNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stGsmHoppingFreq, usFreq, pstRfFreqList->stGsmHoppingFreq.ausFreq[ulIndex], ulIndex);
    }

    /* 转换WCDMA的频点为频率 */
    pstRfFreqList->stWcdmaFreq.ulFreqNum = pstUsingFreq->stWcdmaFreqInfo.ucWcdmaArfcnNum;
    for (ulIndex = 0; ulIndex < pstUsingFreq->stWcdmaFreqInfo.ucWcdmaArfcnNum; ulIndex++)
    {
        usArfNum         = pstUsingFreq->stWcdmaFreqInfo.ausWcdmaArfcnList[ulIndex];
        usBandNum        = MTC_WCDMA_GetBandInfoByDlArfcn(usArfNum);
        pstRfFreqList->stWcdmaFreq.ausFreq[ulIndex] = MTC_CalcWcdmaDlFreq(usBandNum, usArfNum);

        /* 记录可维可测信息 */
        MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(stWcdmaFreq);
        MTC_DEBUG_SAVE_RF_USING_INFO(stWcdmaFreq, usArfcn, usArfNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stWcdmaFreq, usBandId, usBandNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stWcdmaFreq, usFreq, pstRfFreqList->stWcdmaFreq.ausFreq[ulIndex], ulIndex);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 转换LTE的频点为频率 */
    pstRfFreqList->stLteFreq.ulFreqNum = pstUsingFreq->stLteFreqInfo.ucLteArfcnNum;
    for (ulIndex = 0; ulIndex < pstUsingFreq->stLteFreqInfo.ucLteArfcnNum; ulIndex++)
    {
        ulLteArfNum      = pstUsingFreq->stLteFreqInfo.aulLteArfcnList[ulIndex];
        usBandNum        = MTC_LTE_GetBandInfoByDlArfcn(ulLteArfNum);
        pstRfFreqList->stLteFreq.ausFreq[ulIndex] = MTC_CalcLteDlFreq(usBandNum, ulLteArfNum);

        /* 记录可维可测信息 */
        MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(stLteFreq);
        MTC_DEBUG_SAVE_RF_USING_INFO(stLteFreq, ulArfcn, ulLteArfNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stLteFreq, usBandId, usBandNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stLteFreq, usFreq, pstRfFreqList->stLteFreq.ausFreq[ulIndex], ulIndex);
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* 转换TDS的频点为频率 */
    pstRfFreqList->stTdsFreq.ulFreqNum = pstUsingFreq->stTdsFreqInfo.ucTdsArfcnNum;
    for (ulIndex = 0; ulIndex < pstUsingFreq->stTdsFreqInfo.ucTdsArfcnNum; ulIndex++)
    {
        usArfNum         = pstUsingFreq->stTdsFreqInfo.ausTdsArfcnList[ulIndex];
        pstRfFreqList->stTdsFreq.ausFreq[ulIndex] = MTC_CalcTdsDlFreq(usArfNum);

        /* 记录可维可测信息 */
        MTC_DEBUG_SAVE_AS_RF_USING_INFO_NUM(stTdsFreq);
        MTC_DEBUG_SAVE_RF_USING_INFO(stTdsFreq, usArfcn, usArfNum, ulIndex);
        MTC_DEBUG_SAVE_RF_USING_INFO(stTdsFreq, usFreq, pstRfFreqList->stTdsFreq.ausFreq[ulIndex], ulIndex);
    }
#endif
}


/*****************************************************************************
 函 数 名  : MTC_CalcWcdmaDlFreq
 功能描述  : 传入频段号和下行频点号，输出下行绝对频率，以100khz为单位
 输入参数  : pstUsingFreq
 输出参数  : pstRfFreqList
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年03月06日
    作    者   : Y00213812
    修改内容   : RF&LCD干扰规避项目新增
*****************************************************************************/
VOS_VOID MTC_CalcRfDlFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq,
    MTC_MODEM_FREQ_LIST_STRU           *pstModemFreq
)
{
    MTC_RF_USING_FREQ_LIST_STRU         stRfUsingFreq;

    PS_MEM_SET(&stRfUsingFreq, 0, sizeof(MTC_RF_USING_FREQ_LIST_STRU));

    /* 把接入层频点转换成绝对频率(单位统一为0.1MHz/100KHz) */
    MTC_ChangeRfArfcnToFreq(pstUsingFreq, &stRfUsingFreq);

    /* 划分服务小区、跳频和邻区 */
    switch (pstUsingFreq->stMsgHeader.ulSenderPid)
    {
        case I1_UEPS_PID_GAS:
        case I0_UEPS_PID_GAS:
            /* 业务存在时取业务信道上频点,无业务时取BCCH频率 */
            if (stRfUsingFreq.stGsmHoppingFreq.ulFreqNum >= 1)
            {
                pstModemFreq->ulScellFreq = stRfUsingFreq.stGsmHoppingFreq.ausFreq[0];
            }
            else
            {
                pstModemFreq->ulScellFreq = stRfUsingFreq.stGsmFreq.ausFreq[0];
            }

            MTC_CalcHoppingFreq(&stRfUsingFreq.stGsmHoppingFreq, &pstModemFreq->stGsmHoppingFreq);

            break;

        case WUEPS_PID_WRR:
            if (stRfUsingFreq.stWcdmaFreq.ulFreqNum > 0)
            {
                pstModemFreq->ulScellFreq = stRfUsingFreq.stWcdmaFreq.ausFreq[0];
            }
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:
            if (stRfUsingFreq.stLteFreq.ulFreqNum > 0)
            {
                pstModemFreq->ulScellFreq = stRfUsingFreq.stLteFreq.ausFreq[0];
            }
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case TPS_PID_RRC:
            if (stRfUsingFreq.stTdsFreq.ulFreqNum > 0)
            {
                pstModemFreq->ulScellFreq = stRfUsingFreq.stTdsFreq.ausFreq[0];
            }
            break;
#endif
        default:
            return;
    }

    MTC_FillNcellFreq(&stRfUsingFreq, &pstModemFreq->stNcellFreq);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_GetTLBandInfoFromUsingFreq
 功能描述  : 当modem0为GU模式时，根据接入层上报的邻区信息，计算TL的Band信息
 输入参数  : pstUsingFreq
 输出参数  :
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月05日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_GetTLBandInfoFromUsingFreq(
    RRC_MTC_USING_FREQ_IND_STRU        *pstUsingFreq
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulLteArfNum;
    VOS_UINT16                          usBandNum;
    VOS_UINT16                          usArfNum;
    VOS_UINT16                          usTDSRealArf;

#if (FEATURE_ON == FEATURE_LTE)
    /* 转换LTE的频点为Band */
    for (ulIndex = 0; ulIndex < pstUsingFreq->stLteFreqInfo.ucLteArfcnNum; ulIndex++)
    {
        ulLteArfNum      = pstUsingFreq->stLteFreqInfo.aulLteArfcnList[ulIndex];
        if (0 == ulLteArfNum)
        {
            continue;
        }

        usBandNum        = MTC_LTE_GetBandInfoByDlArfcn(ulLteArfNum);
        if (MTC_FREQ_BAND_NONE != usBandNum)
        {
            /* 记录Band信息,由于上下文中记录的band信息是bit0代表band1,所以需要-1 */
            MTC_SetModemNCellBandInfo(MODEM_ID_0, usBandNum - 1);
        }
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    /* 转换TDS的频点为Band */
    for (ulIndex = 0; ulIndex < pstUsingFreq->stTdsFreqInfo.ucTdsArfcnNum; ulIndex++)
    {
        usArfNum         = pstUsingFreq->stTdsFreqInfo.ausTdsArfcnList[ulIndex];
        if (0 == usArfNum)
        {
            continue;
        }

        /*  计算出真实的频率 */
        usTDSRealArf        = MTC_CalcTdsDlFreq(usArfNum);

        /*  查找出对应的band信息 */
        usBandNum       = MTC_TDS_GetBandInfoByDlArfcn(usTDSRealArf);
        if (MTC_FREQ_BAND_NONE != usBandNum)
        {
            /* 记录Band信息,由于上下文中记录的band信息是bit0代表band1,所以需要-1 */
            MTC_SetModemNCellBandInfo(MODEM_ID_0, usBandNum - 1);
        }
    }
#endif

    return;
}



/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

