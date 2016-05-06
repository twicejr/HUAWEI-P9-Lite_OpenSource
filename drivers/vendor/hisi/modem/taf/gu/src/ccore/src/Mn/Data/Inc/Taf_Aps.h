/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : Taf_Aps.h
  Author      : 韩鲁峰
  Version     : V200R001
  Date        : 2005-0
  Description : 该头文件定义了---
  History     :
  1. Date:2005-0 -
     Author: ---
     Modification:Create
  2. 2006-02-23 modify by 韩鲁峰 FOR A32D02144
  3. 2006-02-24 add by 韩鲁峰 for A32D01902
  4. 2006-03-03 add by h41410 for A32D02345
  5. 2006-03-13 add by L47619 for A32D02493
  6. 2006-04-10 MODIFY BY H41410 FOR A32D01902
  7. 2006-04-14 DELETE BY H41410 FOR A32D03180
  8. 2006-04-14 modify by h41410 for A32D03182
  9. 2006-04-14 modify by h41410 for A32D03185
  10.2006-04-15 modify by h41410 for A32D03206
  11.2006-04-18 modify by h41410 for A32D03235
  12.2006-07-03 modify by L47619 for A32D04540
  13.2006-08-09 modify by J60010247 for A32D03479
  14.2006-08-15 modify by L47619 for A32D05709
  15.2006-09-30 modify by L47619 for A32D06451
  16    日    期 : 2006-12-07
        作    者 : 韩鲁峰
        修改内容 : A32D07824 增加CGEQNEG的处理
  17    日    期 : 2006-12-30
        作    者 : 孙少华
        修改内容 : A32D08079
                   修改#define APS_SM_CAUSE_CONDITIONAL_IE_ERROR的值
  18.2006-09-30 modify by L47619 for A32D08332
  19 2007-07-31 Add by hanlufeng 41410 for  A32D12649

  20.日    期   : 2011年04月23日
    作    者   : L00171473
    修改内容   : for V7R1 porting
************************************************************************/

#ifndef _TAF_APS_H_
#define _TAF_APS_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "Taf_Common.h"
#include "ExtAppCmInterface.h"
#include "NasGmmInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#endif
#include "TafSmInterface.h"

#include "NVIM_Interface.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Tafm_Local.h"



#include "Taf_ApsForSndcp.h"
#include "Taf_ApsForRabm.h"      /*必须放在Taf_ApsForSndcp.h包含之后*/
#include "Taf_ApsForTafm.h"
#include "TafApsApi.h"

#include "TafClientApi.h"

/* Added by m00217266 for L-C互操作项目, 2014-1-26, begin */
#include "AdsInterface.h"
/* Added by m00217266 for L-C互操作项目, 2014-1-26, end */

/* Added by zhuli for K3V3VSIM项目, 2014-10-16, begin */
#include "siapppih.h"
/* Added by zhuli for K3V3VSIM项目, 2014-10-16, end */

/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#if (FEATURE_ON == FEATURE_LTE)
#include "ApsL4aInterface.h"
#include "AppEsmInterface.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cttf_1x_rlp_bo_pif.h"
#include "ehsm_aps_pif.h"

#endif

#include "xcc_taf_pif.h"
#include "hsm_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#pragma pack(4)

/*****************************************************************************
  2 宏定义
  #define
*****************************************************************************/
#define TAF_APS_PACKET_CDATA_INACTIVITY_TIME_LEN          ( 5 )


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for  TAF系                           */
/*=======================================================*/

#define APS_TFT_FILTER_AMOUNT           8

#define APS_MAX_LENGTH_OF_APN           101


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS base                         */
/*=======================================================*/

/*函数返回值*/
#ifndef TAF_APS_SUCC
#define TAF_APS_SUCC                 0
#endif

#ifndef TAF_APS_FAIL
#define TAF_APS_FAIL                    1
#endif

/* 分配PDPID结果的返回值 */
#define TAF_APS_ALLOC_PDPID_SUCCESS     (0)
#define TAF_APS_ALLOC_PDPID_FAIL        (1)

/*判断参数是否合法的返回值*/
#define APS_PARA_VALID                  0
#define APS_PARA_INVALID                1
#define APS_PDPID_INVALID               2
#define APS_NSAPI_INVALID               3
#define APS_PDPTYPE_INVALID             4

#define APS_SAPI_VALID                  1
#define APS_SAPI_INVALID                0

#define APS_INFO_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_INFO, String)
#define APS_NORM_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String)
#define APS_WARN_LOG(String)            TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_WARNING, String)
#define APS_ERR_LOG(String)             TAF_LOG(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_ERROR, String)
#define APS_LOG1(String, Para1)         TAF_LOG1(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String, Para1 )
#define APS_LOG2(String, Para1, Para2)  TAF_LOG2(WUEPS_PID_TAF, TAF_APS, PS_LOG_LEVEL_NORMAL, String, Para1, Para2)



#define APS_PDP_MIN_CID                 1
#define APS_PDP_RESELECT_CID            (12)
#define APS_PDP_MAX_CID                 (20)

#define  UPCASE( c ) ( (((c) >= 'a') && ((c) <= 'z')) ? ((c) - 0x20) : (c) )


#define APS_MT_DIFF_VALU                120

#define MN_APS_QOS_CSPS_MAX_UL_KBITRATE         (5760)
#define MN_APS_QOS_CSPS_MAX_DL_KBITRATE         (14400)

/*---------------------------------------------------------
    AT命令时，通过以下的QOS参数确定AT命令无法输入的参数的值
---------------------------------------------------------*/
/*QOS_TRAFFIC_CLASS*/
#define APS_QOS_TRAFFIC_CLASS_SUBSCRIBE             0
#define APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL        1
#define APS_QOS_TRAFFIC_CLASS_STREAMING             2
#define APS_QOS_TRAFFIC_CLASS_INTERACTIVE           3
#define APS_QOS_TRAFFIC_CLASS_BACKGROUND            4

/*QOS_SDU_ERR_RATIO*/
#define APS_QOS_SDU_ERR_RATIO_SUBSCRIBE             0
#define APS_QOS_SDU_ERR_RATIO_1EM2                  1
#define APS_QOS_SDU_ERR_RATIO_7EM3                  2
#define APS_QOS_SDU_ERR_RATIO_1EM3                  3
#define APS_QOS_SDU_ERR_RATIO_1EM4                  4
#define APS_QOS_SDU_ERR_RATIO_1EM5                  5
#define APS_QOS_SDU_ERR_RATIO_1EM6                  6
#define APS_QOS_SDU_ERR_RATIO_1EM10                 7
#define APS_QOS_SDU_ERR_RATIO_RESERVED              15

/*QOS_TRAFFFIC_HANDLING_PRI*/
#define APS_QOS_TRAFFF_HANDL_PRIOR_SUBSCRIBE        0
#define APS_QOS_TRAFFF_HANDL_PRIOR_1                1
#define APS_QOS_TRAFFF_HANDL_PRIOR_2                2
#define APS_QOS_TRAFFF_HANDL_PRIOR_3                3

/*QOS_RESIDUAL_BER*/
#define APS_QOS_RESIDUAL_BER_1EM3                   5
#define APS_QOS_RESIDUAL_BER_1EM4                   6

/*下边这些签署值都是以AT命令为标准的取值，也是APP认为的签署取值，不是3GPP
核心网认为的签署值*/
#define APS_APPQOS_TRAFFCLASS_SUBSCRIB              4
#define APS_APPQOS_DELIVERORDER_SUBSCRIB            2
#define APS_APPQOS_DELIVEReRRSDU_SUBSCRIB           3
#define APS_APPQOS_MAXSDUSIZE_SUBSCRIB              0
#define APS_APPQOS_MAXBITUL_SUBSCRIB                0
#define APS_APPQOS_MAXBITDL_SUBSCRIB                0
#define APS_APPQOS_RESIDUALBER_SUBSCRIB             0
#define APS_APPQOS_SDUERRRATIO_SUBSCRIB             0
#define APS_APPQOS_TRANSDELAY_SUBSCRIB              0
#define APS_APPQOS_TRAFFHANDPRIOR_SUBSCRIB          0
#define APS_APPQOS_GUARANTBITUL_SUBSCRIB            0
#define APS_APPQOS_GUARANTBITDL_SUBSCRIB            0
#define APS_APPQOS_SRCSTATISTICSDES_SUBSCRIB        0
#define APS_APPQOS_SIGNALINDICATION_SUBSCRIB        0



/*QOS_MAX_BITRATE*/
#define APS_QOS_MAX_BITRATE_SUBSCRIBE               0
#define APS_QOS_MAX_BITRATE_16KBPS                  16
#define APS_QOS_MAX_BITRATE_32KBPS                  32
#define APS_QOS_MAX_BITRATE_64KBPS                  64
#define APS_QOS_MAX_BITRATE_128KBPS                 72
#define APS_QOS_MAX_BITRATE_256KBPS                 88
#define APS_QOS_MAX_BITRATE_512KBPS                 120
#define APS_QOS_MAX_BITRATE_1024KBPS                135
#define APS_QOS_MAX_BITRATE_2048KBPS                151
#define APS_QOS_MAX_BITRATE_0KBPS                   255


/*===========================*/
/*3GPP中规定的QOS的各参数的值*/
/*TRAFFIC_CLASS*/
#define APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE                0
#define APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL           1
#define APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING                2
#define APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE              3
#define APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND               4

#define APS_3GPP_QOS_DELAYCLASS_TOP                         4
#define APS_3GPP_QOS_DELAYCLASS_4                           4
#define APS_3GPP_QOS_DELAYCLASS_3                           3
#define APS_3GPP_QOS_DELAYCLASS_2                           2
#define APS_3GPP_QOS_DELAYCLASS_1                           1
#define APS_3GPP_QOS_DELAYCLASS_BOT                         0

#define APS_3GPP_QOS_RELIABCLASS_TOP                        5
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLCRLC_UNPDATA       5
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLCRLC_PRODATA       4
#define APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA   3
#define APS_3GPP_QOS_RELIABCLASS_UNKGTP_ACKLLCRLC_PRODATA   2
#define APS_3GPP_QOS_RELIABCLASS_ACKGTPLLCRLC_PRODATA       1
#define APS_3GPP_QOS_RELIABCLASS_BOT                        0

#define APS_3GPP_QOS_PEAKTHROUGH_TOP                        9
#define APS_3GPP_QOS_PEAKTHROUGH_1000_OCTPS                 1
#define APS_3GPP_QOS_PEAKTHROUGH_BOT                        0

#define APS_3GPP_QOS_PRECEDENCECLASS_TOP                    3
#define APS_3GPP_QOS_PRECEDENCECLASS_NORMPRI                2
#define APS_3GPP_QOS_PRECEDENCECLASS_BOT                    0

#define APS_3GPP_QOS_MEANTHROUGH_TOP                        18
#define APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT                 31
#define APS_3GPP_QOS_MEANTHROUGH_BOT                        0

#define APS_3GPP_QOS_TRAFFICCLASS_TOP                       4
#define APS_3GPP_QOS_TRAFFICCLASS_BOT                       0

#define APS_3GPP_QOS_DELIVERORDER_TOP                       3
#define APS_3GPP_QOS_DELIVERORDER_SUB                       0
#define APS_3GPP_QOS_DELIVERORDER_BOT                       0

#define APS_3GPP_QOS_DELIVER_ERRSDU_TOP                     3
#define APS_3GPP_QOS_DELIVER_ERRSDU_SUB                     0
#define APS_3GPP_QOS_DELIVER_ERRSDU_BOT                     0

/*usMaxSduSize*/
#define APS_3GPP_QOS_MAXSDUSIZE_TOP                         153
#define APS_3GPP_QOS_MAXSDUSIZE_1520OCTS                    153     /*1520 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_1510OCTS                    152     /*1510 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_1502OCTS                    151     /*1502 octets*/
#define APS_3GPP_QOS_MAXSDUSIZE_BOT                         0
#define APS_3GPP_QOS_MAXSDUSIZE_SUB                         0
#define APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10                   10      /*granularity of 10 octets*/

#define APS_3GPP_QOS_RESIDUALBER_TOP                        9
#define APS_3GPP_QOS_RESIDUALBER_BOT                        0

#define APS_3GPP_QOS_SDUERRRATIO_TOP                        7
#define APS_3GPP_QOS_SDUERRRATIO_BOT                        0

/*usTransDelay*/
/*
        In MS to network direction:
        0 0 0 0 0 0     Subscribed transfer delay
        In network to MS direction:
        0 0 0 0 0 0     Reserved
        In MS to network direction and in network to MS direction:

        0 0 0 0 0 1     The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
        0 0 1 1 1 1     giving a range of values from 10 ms to 150 ms in 10 ms increments

        0 1 0 0 0 0     The transfer delay is 200 ms + ((the binary coded value in 6 bits - 010000) * 50 ms)
        0 1 1 1 1 1     giving a range of values from 200 ms to 950 ms in 50ms increments

        1 0 0 0 0 0     The transfer delay is 1000 ms + ((the binary coded value in 6 bits - 100000) * 100 ms)
        1 1 1 1 1 0     giving a range of values from 1000 ms to 4000 ms in 100ms increments

        1 1 1 1 1 1     Reserved
*/
#define APS_3GPP_QOS_TRANSDELAY_TOP                         63
#define APS_3GPP_QOS_TRANSDELAY_1000MS                      32
#define APS_3GPP_QOS_TRANSDELAY_200MS                       16
#define APS_3GPP_QOS_TRANSDELAY_BOT                         0
#define APS_3GPP_QOS_TRANSDELAY_INC_100MS                   100
#define APS_3GPP_QOS_TRANSDELAY_INC_50MS                    50
#define APS_3GPP_QOS_TRANSDELAY_INC_10MS                    10

#define APS_3GPP_QOS_TRAFFHANDLPRIOR_TOP                    3
#define APS_3GPP_QOS_TRAFFHANDLPRIOR_BOT                    0


/*  In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
                        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps
*/
/*usMaxBitUl*/
#define APS_3GPP_QOS_BIT_64KBPS                             64
#define APS_3GPP_QOS_BIT_576KBPS                            128
#define APS_3GPP_QOS_BIT_8640KBPS                           254
#define APS_3GPP_QOS_BIT_0KBPS                              255
#define APS_3GPP_QOS_BIT_INC_8KBPS                          8
#define APS_3GPP_QOS_BIT_INC_64KBPS                         64

/*R7版本中，Maximum bit rate for downlink (extended)参数的取值
  In MS to network direction and in network to MS direction:
  0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9.

                  For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9
                      and use the following value:
  0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
  0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps
                  to 16000 kbps in 100 kbps increments.

  0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
  1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

  1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
  1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
*/
#define APS_3GPP_QOS_BIT_16000KBPS                          74
#define APS_3GPP_QOS_BIT_128MBPS                            186
#define APS_3GPP_QOS_BIT_256MBPS                            250

#define APS_3GPP_QOS_BIT_INC_100KBPS                        100
#define APS_3GPP_QOS_BIT_INC_1MBPS                          1000
#define APS_3GPP_QOS_BIT_INC_2MBPS                          2000

/*
    In MS to network direction and in network to MS direction:
    0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for downlink in octet 9 and octet 15.

    For all other values: Ignore the value indicated by the Maximum bit rate for downlink in octet 9 and
    octet 15 and use the following value:
    0 0 0 0 0 0 0 1 The maximum bit rate is 256 Mbps + ((the binary coded value in 8 bits) * 4 Mbps),
    0 0 1 1 1 1 0 1 giving a range of values from 260 Mbps to 500 Mbps in 4 Mbps increments.

    0 0 1 1 1 1 1 0 The maximum bit rate is 500 Mbps + ((the binary coded value in 8 bits - 00111101) * 10 Mbps),
    1 0 1 0 0 0 0 1 giving a range of values from 510 Mbps to 1500 Mbps in 10 Mbps increments.

    1 0 1 0 0 0 1 0 The maximum bit rate is 1500 Mbps + ((the binary coded value in 8 bits - 10100001) * 100 Mbps),
    1 1 1 1 0 1 1 0 giving a range of values from 1600 Mbps to 10 Gbps in 100 Mbps increments.
*/
#define APS_3GPP_QOS_BIT_500MBPS                            61
#define APS_3GPP_QOS_BIT_1500MBPS                           161
#define APS_3GPP_QOS_BIT_10GBPS                             246

#define APS_3GPP_QOS_BIT_INC_4MBPS                          4000
#define APS_3GPP_QOS_BIT_INC_10MBPS                         10000
#define APS_3GPP_QOS_BIT_INC_100MBPS                        100000


#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
#define APS_3GPP_QOS_SSD_TOP                                15
#define APS_3GPP_QOS_SSD_BOT                                0

#define APS_3GPP_QOS_SIG_IND_TOP                            1
#define APS_3GPP_QOS_SIG_IND_BOT                            0

/* SRC STATISTICS DESCRIPTOR */
#define APS_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN                (0)
#define APS_QOS_SRC_STATS_DESCRIPTOR_SPEECH                 (1)

/* QOS_SIGNAL_IND */
#define APS_QOS_SIGNAL_IND_NOT_OPTIMISE                     (0)
#define APS_QOS_SIGNAL_IND_OPTIMISE                         (1)


/* 1.为了规避PCCW上网侧配置的Maximum bit rate for downlink (extended)高于R6版本所支持的74的问题，
     将对该参数的检查范围放宽到R7版本的250;
   2.为了避免Guaranteed bit rate for downlink (extended)参数也有同样问题，也将对该参数的检查
     范围放宽到R7版本的250*/
#define APS_3GPP_MAX_BITRATE_DOWN_TOP                       250
#define APS_3GPP_MAX_BITRATE_DOWN_BOT                       0

#define APS_3GPP_GUARANT_BITRATE_DOWN_TOP                   250
#define APS_3GPP_GUARANT_BITRATE_DOWN_BOT                   0
#endif

/* R7协议升级，扩展了max bitrate uplink(extended) 和 Guaranteed bit rate for uplink (extended)*/
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
#define APS_3GPP_MAX_BITRATE_UP_TOP                       250
#define APS_3GPP_MAX_BITRATE_UP_BOT                       0

#define APS_3GPP_GUARANT_BITRATE_UP_TOP                   250
#define APS_3GPP_GUARANT_BITRATE_UP_BOT                   0
#endif

/*===========================*/
/*APP/AT中规定的QOS的各参数的值*/
/*usMaxSduSize*/
#define APS_APP_QOS_MAXSDUSIZE_1520OCTS                     1520    /*1520 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1510OCTS                     1510    /*1510 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1502OCTS                     1502    /*1502 octets*/
#define APS_APP_QOS_MAXSDUSIZE_1500OCTS                     1500    /*1500 octets*/

/*usMaxBitUl*/
#define APS_APP_QOS_BIT_64KBPS                              64
#define APS_APP_QOS_BIT_576KBPS                             576
#define APS_APP_QOS_BIT_8640KBPS                            8640
#define APS_APP_QOS_BIT_8600KBPS                            8600
#define APS_APP_QOS_BIT_16MBPS                              16000
#define APS_APP_QOS_BIT_128MBPS                             128000
#define APS_APP_QOS_BIT_256MBPS                             256000
#define APS_APP_QOS_BIT_500MBPS                             500000
#define APS_APP_QOS_BIT_1500MBPS                            1500000
#define APS_APP_QOS_BIT_10GBPS                              10000000
#define APS_APP_QOS_BIT_0KBPS                               0

/*usTransDelay*/
#define APS_APP_QOS_TRANSDELAY_1000MS                       1000
#define APS_APP_QOS_TRANSDELAY_200MS                        200

/*ucTrafficClass*/
#define APS_TRAFFICCLASS_APP3GPP_DIFF_VAL                   1

/*ucDeliverOrder*/
#define APS_DELIVERORDER_APP3GPP_DIFF_VAL                   2

/*ucDeliverOfErrSdu*/
#define APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL                3


/*AT中规定的QOS的各参数的边界值,即APP输入的范围*/
#define APS_APP_QOS_DELAYCLASS_TOP                          4
#define APS_APP_QOS_DELAYCLASS_BOT                          0

#define APS_APP_QOS_RELIABCLASS_TOP                         5
#define APS_APP_QOS_RELIABCLASS_BOT                         0

#define APS_APP_QOS_PEAKTHROUGH_TOP                         9
#define APS_APP_QOS_PEAKTHROUGH_BOT                         0

#define APS_APP_QOS_PRECEDENCECLASS_TOP                     3
#define APS_APP_QOS_PRECEDENCECLASS_BOT                     0

#define APS_APP_QOS_MEANTHROUGH_TOP                         18
#define APS_APP_QOS_MEANTHROUGH_BOT                         0

#define APS_APP_QOS_TRAFFICCLASS_TOP                        4
#define APS_APP_QOS_TRAFFICCLASS_BOT                        0

#define APS_APP_QOS_DELIVERORDER_TOP                        2
#define APS_APP_QOS_DELIVERORDER_BOT                        0

#define APS_APP_QOS_DELIVER_ERRSDU_TOP                      3
#define APS_APP_QOS_DELIVER_ERRSDU_BOT                      0

#define APS_APP_QOS_MAXSDUSIZE_TOP                          1520
#define APS_APP_QOS_MAXSDUSIZE_BOT                          0

#define APS_APP_QOS_RESIDUALBER_TOP                         9
#define APS_APP_QOS_RESIDUALBER_BOT                         0

#define APS_APP_QOS_SDUERRRATIO_TOP                         7
#define APS_APP_QOS_SDUERRRATIO_BOT                         0

#define APS_APP_QOS_TRANSDELAY_TOP                          62
#define APS_APP_QOS_TRANSDELAY_BOT                          0

#define APS_APP_QOS_TRAFFHANDLPRIOR_TOP                     3
#define APS_APP_QOS_TRAFFHANDLPRIOR_BOT                     0


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS 流程--APS层相关              */
/*=======================================================*/
#define APS_NSAPI_MIN                   5

#ifndef APS_NSAPI_MAX
#define APS_NSAPI_MAX                   15
#endif

#define APS_FREE_ENTITY_NUM             7
#define APS_MIDDLE_TI                   7

#ifndef APS_MAX_PDP_NUM
#define APS_MAX_PDP_NUM                 11
#endif

/*VOS_UINT8     ucSNDCPActOrNot*/
#define APS_SNDCP_INACT                 0
#define APS_SNDCP_ACT                   1

/*VOS_UINT8     ucTeardown*/
#define APS_DEACT_NOTEARDOWN            0
#define APS_DEACT_TEARDOWN              1
#define APS_DEACT_BE_TEARDOWNED         2
#define APS_TEARDOWN_INVALID            255

/*VOS_UINT8     ucHowToInitAct*/
#define APS_APP_INIT_ACT                0                   /* APP主动发起激活 */
#define APS_APP_MANUL_ACT               1                   /*APP手动应答发起激活*/
#define APS_TAF_AUTO_INIT_ACT           2                   /*APS自动应答发起激活*/
#define APS_SYSCHNG_ACT_SN              3                   /*3G向2G切换后，APS自动激活SN*/
/*VOS_UINT8     ucHowToInitDeAct*/
#define APS_APP_INIT_DEACT              1
#define APS_APS_AUTO_INIT_DEACT         2
#define APS_NET_INIT_DEACT              3
#define APS_DEACT_DURING_ACTING         4

#define APS_PRI_ACT                     1                   /*主叫发起或网络发起的激活为主激活*/
#define APS_SEC_ACT                     2                   /*主叫发起或网络发起的激活为二次激活*/

#define APS_PPP_CODE_REQ                1
#define APS_PPP_CODE_ACK                2
#define APS_PPP_CODE_NAK                3
#define APS_PPP_CODE_REJ                4

#define APS_PPP_IP_ADDR_ID              0x03
#define APS_PPP_PRI_DNS_ID              0x81
#define APS_PPP_PRI_NBNS_ID             0x82
#define APS_PPP_SEC_DNS_ID              0x83
#define APS_PPP_SEC_NBNS_ID             0x84

#define APS_SYS_REL                     1

/*PCO中字节序转换的宏*/
#ifndef VOS_NTOHL
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
                         (((x) & 0x0000ff00) <<  8) | \
                         (((x) & 0x00ff0000) >>  8) | \
                         (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
                         (((x) & 0x0000ff00) <<  8) | \
                         (((x) & 0x00ff0000) >>  8) | \
                         (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
                         (((x) & 0xff00) >> 8))

#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */

#endif

#define APS_EVT_PCO_SET_0(pEvtPPP)\
                        *pEvtPPP++     = 0x00;             /*AUTH的长度2字节填0*/\
                        *pEvtPPP++     = 0x00;                                   \
                        *pEvtPPP++     = 0x00;             /*IPCP的长度2字节填0*/\
                        *pEvtPPP++     = 0x00;


/*----------------------QOS相关--------------------------*/
#define APS_SAPI_INIT                   3                   /*发起激活时向网络发送的SAPI请求参数全部为3*/
#define APS_SAPI_3                      3
#define APS_SAPI_5                      5
#define APS_SAPI_9                      9
#define APS_SAPI_11                     11


/*Refer to 24.008 10.5.7.2*/
#define APS_RADIOPRI_1                  1                   /*riority level 1 (highest)*/
#define APS_RADIOPRI_2                  2                   /*riority level 2          */
#define APS_RADIOPRI_3                  3                   /*riority level 3          */
#define APS_RADIOPRI_4                  4                   /*riority level 4 (lowest) */



#define APS_QOS_UP_TO_MIN               0                   /* 满足MINQOS 要求 */
#define APS_QOS_NOT_UP_TO_MIN           1                   /* 不满足MINQOS 要求 */

/*7代表的错SDU率最高*/
#define SDU_ERR_RATIO_HIGHEST           7

/*----------------------TFT相关--------------------------*/
#define APS_PACK_FLOW_ID_BIGGEST        127

#define APS_TFT_FILTERID_BOTTOM         0
#define APS_TFT_FILTERID_TOP            7

/*----------------------PCO相关--------------------------*/
/*PAP认证申请时Configuration protocol+ PROTOCAL ID +
PROTOCAL ID1 LEN = 3*/
#define APS_PAP_HEADER_LEN              4
#define APS_PAP_PIDOCTS_AND_LENOCT_LEN  3

#define APS_ADDR_DYNAMIC_IPV4           (0)
#define APS_ADDR_STATIC_IPV4            (1)
#define APS_ADDR_PPP                    (2)

#define APS_ADDR_INVALID                (0xFF)

#define MN_APS_ADDR_IPV6                (3)
#define MN_APS_ADDR_IPV4V6              (4)

#define APS_ADDR_ORGAN_IETF             1
#define APS_ADDR_ORGAN_ETSI             0
#define APS_ADDR_ORGAN_EMPTY_PDP_TYPE   15                  /*Empty PDP type*/



#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_SET_EVT_SM_CAUSE(PsAppEvt, ucPdpId)                              \
{                                                                               \
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpCause)                            \
    {                                                                           \
        PsAppEvt->bitOpCause     = VOS_TRUE;                                     \
        PsAppEvt->enCause        = g_PdpEntity[ucPdpId].enCause;                 \
    }                                                                           \
}
#endif

#if 0
#define APS_NETDNS_2_STRDNS(StrDns, NetDns)                                     \
            StrDns.OP_Spare = VOS_FALSE;                                         \
            if ( VOS_TRUE == NetDns.OP_PriDns)                                  \
            {                                                                   \
                StrDns.OP_PriDns    = VOS_TRUE;                                 \
                Taf_Dns2Str( NetDns.aucPriDns, StrDns.aucPriDns );              \
            }                                                                   \
            else                                                                \
            {                                                                   \
                StrDns.OP_PriDns    = VOS_FALSE;                                 \
            }                                                                   \
            if ( VOS_TRUE == NetDns.OP_SecDns)                                  \
            {                                                                   \
                StrDns.OP_SecDns    = VOS_TRUE;                                 \
                Taf_Dns2Str( NetDns.aucSecDns, StrDns.aucSecDns );              \
            }                                                                   \
            else                                                                \
            {                                                                   \
                StrDns.OP_SecDns    = VOS_FALSE;                                 \
            }/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#endif

#define APS_SET_PDPENTITY_TEATDOWN(ucPdpId, ucTeardownPara)                             \
            g_PdpEntity[ucPdpId].PdpProcTrack.ucTeardown = ucTeardownPara;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for SM 消息                          */
/*=======================================================*/
#define APS_ADDR_SAME                               0
#define APS_ADDR_DIFF                               1

#define APS_APN_SAME                                0
#define APS_APN_DIFF                                1

#define APS_PDP_TYPE_NUM_IPV4                       (0x21)
#define APS_PDP_TYPE_NUM_PPP                        (0x01)
#define MN_APS_PDP_TYPE_NUM_IPV6                    (0x57)
#define MN_APS_PDP_TYPE_NUM_IPV4V6                  (0x8D)

#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_IPV6_STR_MAX_TOKENS                  (16)    /* IPV6字符串格式使用的分隔符标记最大个数 */

#define MN_APS_IPV4_STR_DELIMITER                   '.'     /* RFC协议使用的IPV4文本表达方式使用的分隔符 */
#define MN_APS_IPV6_STR_DELIMITER                   ':'     /* RFC2373使用的IPV6文本表达方式使用的分隔符 */
#endif


/*定义下边这些宏来取出SM上传来的数组码流中的各功能值：*/
#define APS_QOS_DELAY_CLASS                         0x38    /* 0011 1000*/
#define APS_QOS_RELIABILITY_CLASS                   0x07    /* 0000 0111*/
#define APS_QOS_PEAK_THROUGHPUT                     0xF0    /* 1111 0000*/
#define APS_QOS_PRECEDENCE_CLASS                    0x07    /* 0000 0111*/
#define APS_QOS_MEAN_THROUGHPUT                     0x1F    /* 0001 1111*/
#define APS_QOS_TRAFFIC_CLASS                       0xE0    /* 1110 0000*/
#define APS_QOS_DELIVERY_ORDER                      0x18    /* 0001 1000*/
#define APS_QOS_DELIVERY_ERRORNEOUS_SDU             0x07    /* 0000 0111*/
#define APS_QOS_RESIDUAL_BER                        0xF0    /* 1111 0000*/
#define APS_QOS_SDU_ERROR_RATIO                     0x0F    /* 0000 1111*/
#define APS_QOS_TRANSFER_DELAY                      0Xfc    /* 1111 1100*/
#define APS_QOS_TRAFFIC_HANDLING_PRIORITY           0x03    /* 0000 0011*/
#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
#define APS_QOS_SSD                                 0x0F    /* 0000 1111*/
#define APS_QOS_SIGNALLING_INDICATION               0x10    /* 0001 0000*/
#endif
/*----------------------------------------------------------
        TFT中专用
----------------------------------------------------------*/
#define APS_TFT_CREAT_TFT                           0x20    /* 0010 0000*/

#define APS_TFT_REPLACE_TFT                         0x80    /* 1000 0000*/

#define APS_TFT_ONE_FILTER                          0x01
#define APS_TFT_IPV4_ADDR                           0x10
#define APS_TFT_PROTOCAL_ID                         0x30    /* 0011 0000*/
#define APS_TFT_DEST_PORT_RANG                      0x41    /* 0100 0001*/
#define APS_TFT_SOURCE_PORT_RANG                    0x51    /* 0101 0001*/
#define APS_TFT_SPI                                 0x60    /* 0110 0000 Security parameter index type*/
#define APS_TFT_TOS                                 0x70    /* 0111 0000 Type of service/Traffic class type*/
#define APS_TFT_FLOW_LABLE                          0x80    /* 1000 0000 Flow label type*/

/*将UINT16型数据填到字节码流中去时，要先发送低位字节*/
#define APS_UINT16_LOW_LOCATION_OCTET               0x00FF
#define APS_UINT16_HIGH_LOCATION_OCTET              0xFF00

#define APS_UINT32_RESERV_32_TO_25_OCTET            0xFF000000
#define APS_UINT32_RESERV_24_TO_17_OCTET            0x00FF0000
#define APS_UINT32_RESERV_16_TO_8_OCTET             0x0000FF00
#define APS_UINT32_RESERV_7_TO_0_OCTET              0x000000FF

/*TFT中filter1的length域在SM码流中的位置为3 */
#define APS_TFT_FILTER1_LENGTH_LOCATION             3

/*TFT中filter1的component域在SM码流中的开始位置为4 */
#define APS_TFT_FILTER1_COMPONENT_BEGIN             4

/*filter1中 Operation Code + filter ID+ Precedence + length
这4个域的字节数为4*/
#define APS_TFT_FILTER1_OP_ID_PRE_LEN_AMOUNT        4

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for SNDCP消息                        */
/*=======================================================*/
/*见文件Taf_ApsForSndcp.h*/
#define APS_MSGTYPELEN_PIDLEN                       4

#define APS_PACK_SN_MSG_HEADER(Msg,ApsSnIndMsg)\
                                        Msg.ulSenderCpuId   = VOS_LOCAL_CPUID;  \
                                        Msg.ulSenderPid     = WUEPS_PID_TAF;    \
                                        Msg.ulReceiverCpuId = VOS_LOCAL_CPUID;  \
                                        Msg.ulReceiverPid   = UEPS_PID_SN;      \
                                        Msg.ulLength        = sizeof(ApsSnIndMsg)\
                                                              + APS_MSGTYPELEN_PIDLEN;

#define APS_SN_P_CMP_VALID(ucPCmp)      (ucPCmp <= SN_ROHC_ALGRTH)
#define APS_SN_H_CMP_VALID(ucDCmp)      (ucDCmp <= SN_V44_ALGRTH)



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                  for APS 参数定义                     */
/*=======================================================*/
typedef VOS_VOID (*RABM_MSG_FUN_TYPE)( VOS_UINT8  ucPdpID);

/*TAF_PDP_TABLE_STRU中表征参数是否有效的宏*/
#define APS_PDP_TABLE_PARA_INVALID                  0
#define APS_PDP_TABLE_PARA_VALID                    1

typedef VOS_UINT8   APS_NVIM_ACT_TYPE;
#define APS_NVIM_ADD                                0
#define APS_NVIM_CHNG                               1
#define APS_NVIM_DELETE                             2

/*****************************************************************************
  Maximum length of challenge used in authentication. The maximum length
  challenge name is the same as challenge.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_CHALLNGE_LEN       (16)

/*****************************************************************************
  Maximum length of challenge name used in authentication.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN  (16)

/*****************************************************************************
  Maximum length of response used in authentication.
*****************************************************************************/
#define TAF_APS_PPP_CHAP_RESPONSE_LEN   (16)

/***************************************************************
AUTH_PAP (RFC 1334)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Peer-ID Length|  Peer-Id ...
+-+-+-+-+-+-+-+-+-+-+-+-+
| Passwd-Length |  Password ...
+-+-+-+-+-+-+-+-+-+-+-+-+-+
****************************************************************/
/* code(1B)+id(1B)+length(2B)+username_size(1B)+username+password_size(1B)+password */
#define TAF_APS_PPP_PAP_CODE_LEN                    1

#define TAF_APS_PPP_PAP_HEAD_OFFSET                 4

/* code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
/* code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
#define TAF_APS_PPP_CHAP_CODE_LEN                   1
#define TAF_APS_PPP_CHAP_ID_LEN                     1
#define TAF_APS_PPP_CHAP_LEN                        2
#define TAF_APS_PPP_CHAP_CHALLENGE_SIZE             1
#define TAF_APS_PPP_CHAP_RESPONSE_SIZE              1

#define TAF_APS_PPP_CHAP_HEAD_OFFSET                (TAF_APS_PPP_CHAP_CODE_LEN + TAF_APS_PPP_CHAP_ID_LEN + TAF_APS_PPP_CHAP_LEN)

#define TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET      (TAF_APS_PPP_CHAP_HEAD_OFFSET + TAF_APS_PPP_CHAP_CHALLENGE_SIZE)
#define TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET       (TAF_APS_PPP_CHAP_HEAD_OFFSET + TAF_APS_PPP_CHAP_RESPONSE_SIZE)

/*--------------------------------------------------------------
   IPCP OPTION长度必须等于6
   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + VALUE(4 bytes)
--------------------------------------------------------------*/
#define TAF_APS_PPP_IPCP_OPTION_TYPE_LEN            1
#define TAF_APS_PPP_IPCP_OPTION_LEN                 1

#define TAF_APS_PPP_IPCP_OPTION_HEAD_LEN            (TAF_APS_PPP_IPCP_OPTION_TYPE_LEN + TAF_APS_PPP_IPCP_OPTION_LEN)

/*~~~~~~~~~~~~~~~~~~~~~~~~PDP_PRI参数定义需要用的宏 ~~~~~~~~~~~~~~~~~~~~~~~~*/
#define APS_PDPPRI_DELETE(pPdpPara) ((0 == pPdpPara->bitOpApn)        \
                                 &&  (0 == pPdpPara->bitOpPdpAddr)    \
                                 &&  (0 == pPdpPara->bitOpPdpType)    \
                                 &&  (0 == pPdpPara->bitOpPdpDcomp)   \
                                 &&  (0 == pPdpPara->bitOpPdpHcomp))



/*~~~~~~~~~~~~~~~~~~~~~~~~NVIM操作需要用的宏  ~~~~~~~~~~~~~~~~~~~~~~~~*/
#define APS_NVIM_DELETE_ITEM(ucCid)    ((0 == g_TafCidTab[ucCid].ucUsed)        \
                                    &&  (0 == g_TafCidTab[ucCid].ucEpsQosInfoFlg)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucQosTabFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucMinQosFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucPfTabFlag)  \
                                    &&  (0 == g_TafCidTab[ucCid].ucDnsFlag)     \
                                    &&  (0 == g_TafCidTab[ucCid].ucPriCidFlag))

#define APS_NVIM_UPDATE_ITEM           ((1 == g_TmpPdpTab.ucUsed)        \
                                    ||  (1 == g_TmpPdpTab.ucEpsQosInfoFlg)  \
                                    ||  (1 == g_TmpPdpTab.ucQosTabFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucMinQosFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucPfTabFlag)  \
                                    ||  (1 == g_TmpPdpTab.ucDnsFlag)     \
                                    ||  (1 == g_TmpPdpTab.ucPriCidFlag))

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS 流程                        */
/*=======================================================*/
/*判断SAPI是否在有效范围的宏,如果在有效范围,则该宏为 1*/

#define APS_JUDGE_SAPI_VALID(ucSapi) Aps_JudgeSapiValid(ucSapi)

/*判断RadioPriority是否在有效范围的宏,如果在有效范围,则该宏为 1*/
#define APS_JUDGE_RADIOPRI_VALID(ucRadioPri)                                    \
                                       ((APS_RADIOPRI_1         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_2         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_3         == ucRadioPri)  \
                                    ||  (APS_RADIOPRI_4         == ucRadioPri))

/*判断ucTearDown是否在有效范围的宏,如果在有效范围,则该宏为 1*/
#define APS_JUDEG_TEARDOWN_VALID(ucTearDown)                                    \
                                       ((TAF_PDP_TEAR_DOWN      == ucTearDown)  \
                                    ||  (TAF_PDP_NOT_TEAR_DOWN  == ucTearDown))

/*判断NSAPI是否在有效范围的宏,如果在有效范围,则该宏为 1*/
#define APS_JUDGE_NSAPI_VALID(ucNsapi) ((APS_NSAPI_MIN          <= ucNsapi)     \
                                    &&  (APS_NSAPI_MAX          >= ucNsapi))

/*判断PDPID是否在有效范围的宏,如果在有效范围,则该宏为 1*/
#define APS_JUDEG_PDPID_VALID(ucPdpId) ((TAF_APS_MAX_PDPID      >  ucPdpId)     \
                                    &&  (APS_FREE_ENTITY_NUM    != ucPdpId))

#define APS_MEM_FREE(pBuffer)   VOS_MemFree(WUEPS_PID_TAF, (pBuffer))

#define APS_MEM_SET(pBuffer, chDstChar, ulCount)   VOS_MemSet((pBuffer), (chDstChar), (ulCount))

#define TAF_APS_R7_SUPP_UL16QAM_OR_DCUPA(ue_revision, stUECapa)   (((ue_revision) >= PS_PTL_VER_R7)\
                    &&( ((PS_TRUE == stUECapa.enSuppUl16QAM) && (7 == stUECapa.ucEDCHPhyCategoryExt))\
                      ||((PS_TRUE == stUECapa.enDcUpaSupport) && (9 == stUECapa.ucEDCHPhyCategoryExt2))))

/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
#define TAF_APS_MAX_PDPID               (11)

#define TAF_CID_NUMS_VALID              (1)
#define TAF_CID_NUMS_INVALID            (0)

#define TAF_MAX_IPV4_ADDR_LEN           (15)

/*如果没有定义，说明任何Qos参数APP都能接受*/
#define  TAF_PDP_MIN_QOS_DEFINED        (0)
#define  TAF_PDP_MIN_QOS_NOT_DEFINED    (1)

#define TAF_PPP_CODE_REQ                (1)
#define TAF_PPP_CODE_ACK                (2)
#define TAF_PPP_DEF_ID                  (1)

#define TAF_AP_PPP_CHAP_CHALLENGE_LEN   (16)
#define TAF_AP_PPP_CHAP_RESPONSE_LEN    (16)

#define TAF_AP_PPP_CODE_CHALLENGE       (1)
#define TAF_AP_PPP_CODE_RESPONSE        (2)

typedef TAF_UINT8 TAF_PCO_AUTH_TYPE;
#define TAF_PCO_NOT_AUTH                (0)                                     /*PDP激活时的PCO中不需要填写鉴权信息*/
#define TAF_PCO_AUTH_PAP                (1)                                     /*PDP激活时的PCO需要填写PAP方式的鉴权信息*/
#define TAF_PCO_AUTH_CHAP               (2)                                     /*PDP激活时的PCO需要填写CHAP方式的鉴权信息*/

#define TAF_PCO_AUTH_CHAP_RESPONSE_HEAD_LEN     (21)                            /*PDP激活时的PCO鉴权方式为CHAP时，RESPONSE的头固定为21个字符*/
#define TAF_PCO_AUTH_CHAP_RESPONSE_CONTENT_LEN  (106)                           /*PDP激活时的PCO鉴权方式为CHAP时，RESPONSE的内容最长为106个字符，与标杆一致*/

#define TAF_PCO_CONTENT_MAX_LEN         (255)                                   /*PCO中的每个content的长度都是由一字节的length字段决定的，故最长为255个字节*/



#define TAF_APS_CFG_EVT_CTRL_HDR(pstCtrlHdr, ModuleId, ClientId, OpId)\
            (pstCtrlHdr)->ulModuleId = WUEPS_PID_AT;\
            (pstCtrlHdr)->usClientId = ClientId;\
            (pstCtrlHdr)->ucOpId = OpId

#define TAF_APS_CFG_AT_EVT_CTRL_HDR(pstCtrlHdr, ClientId, OpId)\
            TAF_APS_CFG_EVT_CTRL_HDR(pstCtrlHdr, WUEPS_PID_AT, ClientId, OpId)

#define TAF_APS_INVALID_MODULEID                            (WUEPS_PID_AT)

#define TAF_APS_GET_MODULEID_FORM_CTRL_HDR(pstCtrl)         ((pstCtrl)->ulModuleId)
#define TAF_APS_GET_CLIENTID_FORM_CTRL_HDR(pstCtrl)         ((pstCtrl)->usClientId)

/*使用PPP拨号，数传过程中需要使用AT命令修改QOS，
  目前的正式方案中是不允许这样操作的，但为了满足测试部
  的某些相关用例的测试需求，需要打桩实现该需求。
  但导致其它拨号也需要使用该成员 */

typedef TAF_CTRL_STRU   TAF_APS_PDP_MOD_DIAL_STRU;

#if (VOS_OS_VER == VOS_WIN32)
#define TAF_APS_DEFAULT_CDATA_RAB_ID       (5)
#else
#define TAF_APS_DEFAULT_CDATA_RAB_ID       (15)
#endif

#define TAF_APS_DEFAULT_CDATA_PDN_ID       (1)

#define TAF_MAX_CALLID                  (11)
#define TAF_MIN_CALLID                  (1)


/*****************************************************************************
 结构名称   : MN_APS_IPV6_STR_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPV6 String格式枚举
              HEX为RFC2373要求使用':'作为分隔符
              DEX为RFC要求使用'.'作为分隔符
*****************************************************************************/
enum TAF_APS_ORIG_TYPE_ENUM
{
    TAF_APS_ORIG_TYPE_PS_CALL            = 0,
    TAF_APS_ORIG_TYPE_PPP_DIAL           = 1,

    TAF_APS_DIAL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_ORIG_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : TAF_PDP_TABLE_STRU
 结构说明  : PDP结构表，用于保存PDP的上下文参数信息
 修改记录  :
 1.日    期   : 2012年01月04日
   作    者   : l00198894
   修改内容   : PS Project，统一与LTE的PDP表结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0：未使用，1：使用*/
    VOS_UINT8                           ucCid;                                  /*Cid取值*/
    VOS_UINT8                           ucPriCidFlag;                           /*0: ucPriCid无效,此PDP为主PDP; 1: ucPriCid有效,此PDP为二次PDP*/
    VOS_UINT8                           ucPriCid;                               /*指向主PDP表索引*/
    TAF_PDP_PRIM_CONTEXT_STRU           CidTab;                                 /*Cid表*/

    VOS_UINT8                           ucEpsQosInfoFlg;                        /*0：EQos表无效，1：EQos表有效*/
    VOS_UINT8                           aucRsv1[3];
    TAF_EPS_QOS_STRU                    stEpsQosInfo;                           /*EQos参数表*/

    VOS_UINT8                           ucQosTabFlag;                           /*0：Qos表无效，1：Qos表有效*/
    VOS_UINT8                           aucRsv2[3];
    TAF_UMTS_QOS_STRU                   QosTab;                                 /*Qos表*/

    VOS_UINT8                           ucMinQosFlag;                           /*0:定义了最小可接受Qos,1:没有最小可接受Qos*/
    VOS_UINT8                           aucRsv3[3];
    TAF_UMTS_QOS_STRU                   MinQosTab;                              /*MINQos表*/

    VOS_UINT8                           ucPfTabFlag;                            /*0：pf表无效，1：pf表有效*/
    VOS_UINT8                           aucRsv4[2];
    VOS_UINT8                           ucPfNum;                                /* pf个数 */
    TAF_PDP_PF_STRU                     astPfTab[TAF_MAX_SDF_PF_NUM];           /* pf表 */

    VOS_UINT8                           ucDnsFlag;                              /*0：DNS表无效，1：DNS表有效*/
    VOS_UINT8                           aucRsv6[3];
    TAF_PDP_DNS_STRU                    DnsTab;                                 /*DNS表*/

    VOS_UINT16                          usNvFlag;                               /*该CID所对应的NV Table表项是否设置过: 0-未设置,1-已设置*/
    VOS_UINT8                           aucRsv7[98];                            /* 多余的98个保留字节，目的是为了和NV项对齐 */

}TAF_PDP_TABLE_STRU;

/*****************************************************************************
 结构名称: TAF_NV_PDP_PRIM_CONTEXT_STRU
 结构说明: Primary PDP上下文结构(NV)
*****************************************************************************/
typedef struct
{
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;                              /*PDP类型*/
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_APN_STRU                    stApn;
    VOS_UINT8                           aucPdpAddr[TAF_MAX_IPV4_ADDR_STR_LEN];          /*PDP IPv4地址*/
    TAF_PDP_D_COMP_ENUM_UINT8           enPdpDcomp;
    TAF_PDP_H_COMP_ENUM_UINT8           enPdpHcomp;

    /* 0 - IPv4 Address Allocation through NAS Signaling (default if omitted)
       1 - IPv4 Address Allocated through DHCP */
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAlloc;

    /* 0 - PDP context is not for emergency bearer services
       1 - PDP context is for emergency bearer services */
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
} TAF_NV_PDP_PRIM_CONTEXT_STRU;

/*****************************************************************************
 结构名称: TAF_NV_PDP_DNS_STRU
 结构说明: IPv4 DNS地址结构(NV)
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimDnsAddr    : 1;
    VOS_UINT32                          bitOpSecDnsAddr     : 1;
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimDnsAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDnsAddr[TAF_IPV4_ADDR_LEN];
} TAF_NV_PDP_DNS_STRU;

/*****************************************************************************
 结构名称: TAF_NV_PDP_TABLE_STRU
 结构说明: PDP结构表，用于保存PDP的上下文参数信息，与NV项保存的结构一致
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0：未使用，1：使用*/
    VOS_UINT8                           ucCid;                                  /*Cid取值*/
    VOS_UINT8                           ucPriCidFlag;                           /*0: ucPriCid无效,此PDP为主PDP; 1: ucPriCid有效,此PDP为二次PDP*/
    VOS_UINT8                           ucPriCid;                               /*指向主PDP表索引*/
    TAF_NV_PDP_PRIM_CONTEXT_STRU        CidTab;                                 /*Cid表*/

    VOS_UINT8                           ucEpsQosInfoFlg;                        /*0：EQos表无效，1：EQos表有效*/
    VOS_UINT8                           aucRsv1[3];
    TAF_EPS_QOS_STRU                    stEpsQosInfo;                           /*EQos参数表*/

    VOS_UINT8                           ucQosTabFlag;                           /*0：Qos表无效，1：Qos表有效*/
    VOS_UINT8                           aucRsv2[3];
    TAF_UMTS_QOS_STRU                   QosTab;                                 /*Qos表*/

    VOS_UINT8                           ucMinQosFlag;                           /*0:定义了最小可接受Qos,1:没有最小可接受Qos*/
    VOS_UINT8                           aucRsv3[3];
    TAF_UMTS_QOS_STRU                   MinQosTab;                              /*MINQos表*/

    VOS_UINT8                           ucPfTabFlag;                            /* 0：pf表无效，1：pf表有效 */
    VOS_UINT8                           aucRsv4[2];
    VOS_UINT8                           ucPfNum;                                /* pf个数 */
    TAF_PDP_PF_STRU                     astPfTab[TAF_MAX_SDF_PF_NUM];           /* pf表 */

    VOS_UINT8                           ucDnsFlag;                              /*0：DNS表无效，1：DNS表有效*/
    VOS_UINT8                           aucRsv6[3];
    TAF_NV_PDP_DNS_STRU                 DnsTab;                                 /*DNS表*/

    VOS_UINT16                          usNvFlag;                               /*该CID所对应的NV Table表项是否设置过: 0-未设置,1-已设置*/
    VOS_UINT8                           aucRsv7[106];
}TAF_NV_PDP_TABLE_STRU;

typedef struct
{
    TAF_UINT8   aucUserName[TAF_MAX_USERNAME_LEN + 1];                          /*aucUserName[0]放置用户名长度*/
    TAF_UINT8   aucPassword[TAF_MAX_PASSCODE_LEN + 1];                          /*aucPassword[0]放置密码长度*/
} TAF_PDP_PCO_AUTH_PAP_STRU;


typedef struct
{
    TAF_UINT8   aucChallenge[TAF_PCO_CONTENT_MAX_LEN + 1];                      /*aucChallenge[0]放置Challenge长度*/
    TAF_UINT8   aucResponse[TAF_PCO_CONTENT_MAX_LEN + 1];                       /*aucResponse[0]放置Response长度*/
}TAF_PDP_PCO_AUTH_CHAP_STRU;

typedef struct
{
    TAF_PCO_AUTH_TYPE           AuthType;
    TAF_UINT8                   aucResverd[3];
    union
    {
        TAF_PDP_PCO_AUTH_PAP_STRU  stPap;
        TAF_PDP_PCO_AUTH_CHAP_STRU stChap;
    }AuthContent;
} TAF_PDP_PCO_AUTH_STRU;

typedef struct
{
    TAF_UINT32              OP_Auth             : 1;
    TAF_UINT32              OP_Dns              : 1;
    TAF_UINT32              OP_Nbns             : 1;
    TAF_UINT32              OP_Spare            : 29;

    TAF_UINT8               ucCid;
    TAF_PDP_TYPE_ENUM_UINT8 PdpType;

    TAF_UINT8               aucResverd[2];
    TAF_PDP_APN_STRU        stApn;
    TAF_UINT8               aucPdpAddr[TAF_IPV4_ADDR_LEN];
    TAF_PDP_PCO_AUTH_STRU   AuthPara;
    TAF_PDP_DNS_STRU        Dns;
    TAF_PDP_NBNS_STRU       Nbns;
} TAF_PSCALL_FOR_DIAL_EXT_STRU;


/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


/*******************************************************************************
  3 枚举定义
  typedef enum
{
    模块名_意义描述_ENUM
    MAPS_TEMPLATE_ENUM1 = 0,
    MAPS_TEMPLATE_ENUM2
    MAPS_TEMPLATE_BUTT,     用这个统一的BUTT，作为最后一个枚举值。
}MAPS_TEMPLATE_ENUM;        模块名_枚举类型描述_ENUM
*******************************************************************************/

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 结构名称   : MN_APS_IPV6_STR_TYPE_ENUM
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPV6 String格式枚举
              HEX为RFC2373要求使用':'作为分隔符
              DEX为RFC要求使用'.'作为分隔符
*****************************************************************************/
enum MN_APS_IPV6_STR_TYPE_ENUM
{
    MN_APS_IPV6_STR_TYPE_HEX       ,
    MN_APS_IPV6_STR_TYPE_DEC       ,

    MN_APS_IPV6_STR_TYPE_BUTT
};
typedef VOS_UINT8 MN_APS_IPV6_STR_TYPE_ENUM_UINT8;
#endif


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for  APP相关                        */
/*=======================================================*/
typedef enum
{
    APS_CID_PPP                         = 1,
    APS_CID_IP,
    APS_CID_EMPTY,
    APS_CID_BUTT                        = 0xFF
} TAF_CID_TYPE_EN;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SELF                        */
/*=======================================================*/
/*激活方式*/
typedef enum
{
    APS_PDP_ACT_PRI                     = 0,
    APS_PDP_ACT_SEC,
    APS_PDP_ACT_BUTT                    = 0xFF
}APS_PDP_ACT_TYPE_ENUM;

typedef VOS_UINT8 APS_PDP_ACT_TYPE_ENUM_UINT8;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SM相关                      */
/*=======================================================*/
typedef enum
{
    APS_ACT_CNF                         = 0,
    APS_SEC_ACT_CNF,
    APS_MDF_CNF,
    APS_MDF_IND,
    APS_BUTT                            = 0xFF
} APS_QOS_NOT_SATISFY_MSGTYPE_ENUM;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM相关                    */
/*=======================================================*/

typedef enum
{
    MN_PS_MSG_PROC_MODE_GU,
    MN_PS_MSG_PROC_MODE_LTE,
    MN_PS_MSG_PROC_MODE_BUTT
} MN_PS_MSG_PROC_MODE_ENUM;
typedef VOS_UINT8 MN_PS_MSG_PROC_MODE_ENUM_UINT8;


/*****************************************************************************
 枚举名称: TAF_PDP_ACTIVE_STATUS_ENUM
 枚举说明: PDP去激活清除标志
 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_TEAR_DOWN_ENUM
{
    TAF_PDP_NOT_TEAR_DOWN               = 0x00,                                 /*PDP去激活时不需清除*/
    TAF_PDP_TEAR_DOWN                   = 0x01,                                 /*PDP去激活时需要清除*/

    TAF_PDP_TEAR_DOWN_BUTT              = 0xFF
};
typedef VOS_UINT8 TAF_TEAR_DOWN_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_APS_RAT_TYPE_ENUM_UINT32
 结构说明  : 当前的接入技术
 1.日    期   : 2014年10月19日
   作    者   : Y00213812
   修改内容   : 新建
*****************************************************************************/
enum TAF_APS_RAT_TYPE_ENUM
{
    TAF_APS_RAT_TYPE_NULL,          /* 当前未在任何网络上驻留 */
    TAF_APS_RAT_TYPE_GSM,           /* GSM接入技术 */
    TAF_APS_RAT_TYPE_WCDMA,         /* WCDMA接入技术 */
    TAF_APS_RAT_TYPE_LTE,           /* LTE接入技术 */
    TAF_APS_RAT_TYPE_1X,            /* CDMA-1X接入技术 */
    TAF_APS_RAT_TYPE_HRPD,          /* CDMA-HRPD接入技术 */
    TAF_APS_RAT_TYPE_EHRPD,         /* CDMA-EHRPD接入技术 */
    TAF_APS_RAT_TYPE_BUTT           /* 无效的接入技术 */
};
typedef VOS_UINT32 TAF_APS_RAT_TYPE_ENUM_UINT32;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PPP_STATE_ENUM
 *
 * Description : PPP当前的激活状态
 *******************************************************************************/
enum TAF_APS_CDATA_PPP_STATE_ENUM
{
    TAF_APS_CDATA_PPP_STATE_INACTIVE            = 0x00,             /* PPP未处于激活态 */
    TAF_APS_CDATA_PPP_STATE_ACTIVATING          = 0x01,             /* PPP处于激活协商过程中 */
    TAF_APS_CDATA_PPP_STATE_ACTIVE              = 0x02,             /* PPP处于激活态 */
    TAF_APS_CDATA_PPP_STATE_DEACTIVATING        = 0x03,             /* PPP处于去激活协商过程中 */
    TAF_APS_CDATA_PPP_STATE_BUTT                = 0x04
};
typedef VOS_UINT8 TAF_APS_CDATA_PPP_STATE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_AIR_LINK_STATUS_ENUM
 *
 * Description : 空口链路状态
 *******************************************************************************/
enum TAF_APS_CDATA_AIR_LINK_STATUS_ENUM
{
    TAF_APS_CDATA_AIR_LINK_NO_LINK           = 0x00,             /* 无空口链路 */
    TAF_APS_CDATA_AIR_LINK_CONNECTING        = 0x01,             /* 空口链路建立过程中 */
    TAF_APS_CDATA_AIR_LINK_DISCONNECTING     = 0x02,             /* 空口链路释放过程中 */
    TAF_APS_CDATA_AIR_LINK_CONNECTED         = 0x03,             /* 空口链路建链成功 */

    TAF_APS_CDATA_AIR_LINK_BUTT              = 0x04
};
typedef VOS_UINT8 TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_SO_TYPE_ENUM_UINT16
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_SO_TYPE_ENUM
{
    TAF_APS_CDATA_SO_2_LOOPBACK              = 0x0002,
    TAF_APS_CDATA_SO_3_EVRC                  = 0x0003,
    TAF_APS_CDATA_SO_6_SMS                   = 0x0006,
    TAF_APS_CDATA_SO_7_PPP_PKT_DATA_PRE707   = 0x0007,
    TAF_APS_CDATA_SO_14_RS2_SMS              = 0x000E,
    TAF_APS_CDATA_SO_33_PPP_PKT_DATA         = 0x0021,
    TAF_APS_CDATA_SO_68_EVRC_B               = 0x0044,
    TAF_APS_CDATA_SO_73_EVRC_NW              = 0x0049,
    TAF_APS_CDATA_SO_BUTT                    = 0x004A
};
typedef VOS_UINT16 TAF_APS_CDATA_SO_TYPE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PS_STATE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_PS_STATE_ENUM
{
    TAF_APS_CDATA_PS_STATE_INACTIVE,
    TAF_APS_CDATA_PS_STATE_ACTIVATING,
    TAF_APS_CDATA_PS_STATE_DEACTIVATING,
    TAF_APS_CDATA_PS_STATE_ACTIVE,

    TAF_APS_CDATA_PS_STATE_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_PS_STATE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_APS_CDATA_PS_STATE_ENUM_UINT8
 * Description :
 *******************************************************************************/
enum TAF_APS_CDATA_REDIAL_TYPE_ENUM
{
    TAF_APS_CDATA_REDIAL_TYPE_NONE,
    TAF_APS_CDATA_REDIAL_TYPE_DRS_TRUE,
    TAF_APS_CDATA_REDIAL_TYPE_DRS_FALSE,

    TAF_APS_CDATA_REDIAL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 STRUCT定义
  typedef struct
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_ST;
*****************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS BASE                        */
/*=======================================================*/
typedef struct                                              /*详见TS24008 10.5.6.4 */
{
    VOS_UINT8                           ucPdpTypeNum;       /*APS_ADDR_DYNAMIC_IPV4
                                                              APS_ADDR_STATIC_IPV4
                                                              APS_ADDR_PPP
                                                              MN_APS_ADDR_DYNAMIC_IPV6
                                                              MN_APS_ADDR_IPV6
                                                              MN_APS_ADDR_IPV4V6
                                                            */
    VOS_UINT8                           ucPdpTypeOrgan;     /*0 - ETSI allocated address
                                                              1 - IETF allocated address
                                                              15- Empty PDP type
                                                            */
    VOS_UINT8                           aucReserved[2];     /* 四字节对齐  */

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucIpV6Addr[TAF_IPV6_ADDR_LEN];
#endif

} APS_PDP_ADDR_ST;

typedef struct
{
    VOS_UINT32                          OP_PriDns   : 1;
    VOS_UINT32                          OP_SecDns   : 1;
    VOS_UINT32                          OP_Spare    : 30;

    VOS_UINT8                           aucPriDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV4_ADDR_LEN];
}APS_PDP_DNS_ST;

typedef struct
{
    VOS_UINT32                          OP_PriNbns   : 1;
    VOS_UINT32                          OP_SecNbns   : 1;
    VOS_UINT32                          OP_Spare    : 30;

    VOS_UINT8                           aucPriNbns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[TAF_IPV4_ADDR_LEN];
}APS_PDP_NBNS_ST;

/*****************************************************************************
 结构名称   : MN_APS_PDP_GATEWAY_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPCP报文中的GATEWAY信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpGateWay    : 1;
    VOS_UINT32                          bitOpSpare      : 31;

    VOS_UINT8                           aucGateWay[TAF_IPV4_ADDR_LEN];
} MN_APS_PDP_GATEWAY_STRU;

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 结构名称   : MN_APS_PDP_IPV6_DNS_STRU
 协议表格   :
 ASN.1 描述 :
 结构说明   : IPCP报文中的IPv6 DNS信息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[TAF_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV6_ADDR_LEN];
} MN_APS_PDP_IPV6_DNS_STRU;

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#endif


typedef struct                                              /*详见TS24008 10.5.6.1*/
{
    VOS_UINT8                           ucLength;           /*aucValue[MAX_LENGTH_OF_APN]
                                                              中有效数据的长度*/
    VOS_UINT8                           aucValue[APS_MAX_LENGTH_OF_APN];
                                                            /*24008中定义的APN码流中长度
                                                              字节后的字节*/
    VOS_UINT8                           aucRsv[2];         /* 4字节对齐 */
}APS_PDP_APN_ST ;

/* 用于PDP实体中的TFT结构体 */
typedef struct
{
    VOS_UINT32                          OP_SourcePort           : 1;
    VOS_UINT32                          OP_DestPort             : 1;
    VOS_UINT32                          OP_SourceIpAddrAndMask  : 1;
    VOS_UINT32                          OP_ProtocolId           : 1;
    VOS_UINT32                          OP_ulSecuParaIndex      : 1;

    VOS_UINT32                          OP_ucTypeOfService      : 1;
    VOS_UINT32                          OP_Spare                : 26;


    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucPrecedence;       /*packet filter evaluation precedence*/
    VOS_UINT8                           aucRsv[2];         /* 4字节对齐 */
    VOS_UINT16                          usSrcPortHighLimit;
    VOS_UINT16                          usSrcPortLowLimit;
    VOS_UINT16                          usDstPortHighLimit;
    VOS_UINT16                          usDstPortLowLimit;
    VOS_UINT8                           aucSrcIpAddress[TAF_IPV4_ADDR_LEN];
                                                            /*ucSourceIpAddress[0]为IP地址高字节位
                                                              ucSourceIpAddress[3]为低字节位*/
    VOS_UINT8                           aucSrcIpMask[TAF_IPV4_ADDR_LEN];
                                                            /*ucSourceIpMask[0]为IP地址高字节位 ,
                                                              ucSourceIpMask[3]为低字节位*/
    VOS_UINT32                          ulSecuParaIndex;    /*SPI*/
    VOS_UINT8                           ucProtocolId;       /*协议号*/
    VOS_UINT8                           ucTypeOfService;    /*TOS*/
    VOS_UINT8                           ucTypeOfServiceMask;/*TOS Mask*/
    VOS_UINT8                           ucRsv;              /* 4字节对齐 */
}APS_PDP_TFT_ST;

typedef struct
{
    VOS_UINT8                           ucDelayClass;
    VOS_UINT8                           ucReliabClass;
    VOS_UINT8                           ucPeakThrough;
    VOS_UINT8                           ucPrecedenceClass;
    VOS_UINT8                           ucMeanThrough;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucDeliverOrder;
    VOS_UINT8                           ucDeliverOfErrSdu;
    VOS_UINT8                           ucMaximSduSize;
    VOS_UINT8                           ucMaxBitRateForUp;
    VOS_UINT8                           ucMaxBitRateForDown;
    VOS_UINT8                           ucResidualBer;
    VOS_UINT8                           ucSduErrRatio;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucGuarantBitRateForUp;
    VOS_UINT8                           ucGuarantBitRateForDown;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;
    VOS_UINT8                           ucMaxBitRateForDownExt;
    VOS_UINT8                           ucGuarantBitRateForDownExt;
    VOS_UINT8                           ucMaxBitRateForUpExt;
    VOS_UINT8                           ucGuarantBitRateForUpExt;
    VOS_UINT8                           ucMaxBitRateForDownExt_2;
    VOS_UINT8                           ucGuarantBitRateForDownExt_2;
    VOS_UINT8                           ucMaxBitRateForUpExt_2;
    VOS_UINT8                           ucGuarantBitRateForUpExt_2;
    VOS_UINT8                           aucRsv[1];         /* 4字节对齐 */
} APS_PDP_QOS_ST;
typedef APS_PDP_QOS_ST          APS_PDP_QOS_STRU;

typedef struct
{
    VOS_UINT32                          Op_Sapi             : 1;
    VOS_UINT32                          Op_RadioPriority    : 1;
    VOS_UINT32                          Op_Xid_PCmp         : 1;
    VOS_UINT32                          Op_Xid_DCmp         : 1;
    VOS_UINT32                          Op_TransMode        : 1;

    VOS_UINT32                          OP_PacketFlowId     : 1;
    VOS_UINT32                          Op_Spare            : 26;

    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2
                                                              1: riority level 1 (highest)
                                                              2: riority level 2
                                                              3: riority level 3
                                                              4: riority level 4 (lowest) */

    VOS_UINT8                           ucPCmprAlgrth;      /*#define SN_1144_ALGRTH    0
                                                              #define SN_2507_ALGRTH    1
                                                              #define SN_ROHC_ALGRTH    2 */

    VOS_UINT8                           ucDCmprAlgrth;      /*#define SN_V42_ALGRTH     0
                                                              #define SN_V44_ALGRTH     1 */
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved[3];
    RABM_TRANS_MODE_ENUM                TransMode;
} APS_GPRS_PARA_ST;

/*API区分各APP发起的各次PDP呼叫需要多个参数，这些参数之间的对应关系在PDP状态
机中保存。*/
typedef struct
{
    VOS_UINT32                          aulModuleId[TAF_MAX_CID + 1];
    VOS_UINT16                          ausClientId[TAF_MAX_CID + 1];
    VOS_UINT8                           aucId[TAF_MAX_CID + 1];                 /* CallId, Smi, OpId */
    TAF_PDP_TYPE_ENUM_UINT8             aenPdpType[TAF_MAX_CID + 1];            /* 记录发起激活的PDP类型 */
    VOS_UINT32                          ulBitCidMask;                               /* PS呼叫时用于记录呼叫所对应cid索引,以掩码方式记录 */
    VOS_UINT8                           ucCid;
    VOS_UINT8                           aucReserved[3];
} TAF_APS_CLIENT_INFO_STRU;


typedef struct
{
    /*SNDCP是否已经激活
      #define                           APS_SNDCP_INACT             0
      #define                           APS_SNDCP_ACT               1*/
    VOS_UINT8                           ucSNDCPActOrNot;

    /*怎样发起的激活:APP主动,APP手动,APS自动
      #define                           APS_APP_INIT_ACT            1
      #define                           APS_APP_MANUL_ACT           2
      #define                           APS_TAF_AUTO_INIT_ACT       3 */
    VOS_UINT8                           ucHowToInitAct;

    /*怎样发起的去激活:APP主动,APS自动,网络发起的去激活,激活过程中的去激活,
      #define                           APS_APP_INIT_DEACT          1
      #define                           APS_APS_AUTO_INIT_DEACT     2
      #define                           APS_NET_INIT_DEACT          3
      #define                           APS_DEACT_DURING_ACTING     4 */
    VOS_UINT8                           ucHowToInitDeAct;

    /*UE收到网络的MDF_IND或ACT_CNF时可能会修改ADDR,在收到SNDCP的响应后,根据此标识决
      定是否向APP上报ADDR信息.
      收到MDF_IND或ACT_CNF,如果收到的ADDR与原来的ADDR不同,则此标识设置为APS_NETIND_ADDR_DIFF,
      若网络没有发来ADDR或发来的ADDR与原来的相同,则设置为APS_NETIND_ADDR_SAME
      #define                           APS_NETIND_ADDR_SAME        0
      #define                           APS_NETIND_ADDR_DIFF        1 */
    VOS_UINT8                           ucMdfIndAddrDiffOrNot;

    /*此次去激活的TEARSOWN参数
      #define                           APS_DEACT_NOTEARDOWN        0
      #define                           APS_DEACT_TEARDOWN          1
      #define                           APS_DEACT_BE_TEARDOWNED     2
      #define                           APS_TEARDOWN_INVALID        255 */
    VOS_UINT8                           ucTeardown;

    VOS_UINT8                           aucRsv[3];
} APS_PDP_PROC_TRACK_ST;

typedef struct
{

    VOS_UINT8                           ucPdnId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucSrId;


    VOS_UINT8                           ucConnectId;
    VOS_UINT8                           ucConRef;
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSo;

    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlg;           /**<  data ready to send */
    VOS_UINT8                           ucIsL2ErrReOrig;    /**<  reason of re orig is L2 error */
    VOS_UINT8                           ucReOrigCount;      /**<  coutinous count */

    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enPsState;
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;
    TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8      enAirLinkStatus;
    VOS_UINT8                           ucDoQuickAcqProtect;

}TAF_APS_CDATA_CONTEXT_ENTITY_STRU;

/*结构体APS_PDP_CONTEXT_ENTITY_ST用于描述PDP实体,每一个PDP上下文,对应一个该
结构体的实体。*/
typedef struct
{
    VOS_UINT32                          PdpNsapiFlag        :   1;
    VOS_UINT32                          PdpAddrFlag         :   1;
    VOS_UINT32                          PdpApnFlag          :   1;
    VOS_UINT32                          PdpDnsFlag          :   1;
    VOS_UINT32                          PdpTftFlag          :   1;

    VOS_UINT32                          PdpQosFlag          :   1;
    VOS_UINT32                          PdpAuthFlag         :   1;
    VOS_UINT32                          PdpGprsParaFlag     :   1;
    VOS_UINT32                          PdpProcTrackFlag    :   1;

    VOS_UINT32                          bitOpPdpNbns        :   1;
    VOS_UINT32                          bitOpPdpGateWay     :   1;
    VOS_UINT32                          bitOpTransId        :   1;
    VOS_UINT32                          bitOpIpv6RaInfo     :   1;
    VOS_UINT32                          bitOpCause          :   1;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          bitOpPf             :   1;
    VOS_UINT32                          bitOpEpsQos         :   1;
#endif

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    VOS_UINT32                          bitOpImCnSigalFlag  :   1;
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          bitOpSpare          :   15;
#else
    VOS_UINT32                          bitOpSpare          :   17;
#endif /* (FEATURE_ON == FEATURE_LTE) */

    VOS_UINT32                          ulUsedFlg;          /* 当前实体是否被使用的标示，VOS_TRUE:已经使用，VOS_FALSE:没有使用 */

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucLinkedNsapi;      /*主激活的NSAPI,若激活类型是
                                                              二次激活,则此成员有效*/
    APS_PDP_ACT_TYPE_ENUM_UINT8         ActType;            /*激活类型*/

    APS_PDP_ADDR_ST                     PdpAddr;
    APS_PDP_APN_ST                      PdpApn;
    APS_PDP_DNS_ST                      PdpDns;
    APS_PDP_NBNS_ST                     stPdpNbns;
    MN_APS_PDP_GATEWAY_STRU             stPdpGateWay;

    TAF_PDP_PCSCF_STRU                  stPdpPcscf;

    APS_PDP_TFT_ST                      PdpTft[APS_TFT_FILTER_AMOUNT + 1];

    APS_PDP_QOS_ST                      PdpQos;

    TAF_EPS_QOS_STRU                    stEpsQos;

    TAF_PDP_PCO_AUTH_STRU               AuthTab;

    APS_GPRS_PARA_ST                    GprsPara;           /*双模必须使用的参数,单模不用*/

    TAF_APS_CLIENT_INFO_STRU            stClientInfo;

    APS_PDP_PROC_TRACK_ST               PdpProcTrack;       /*PDP操作记录*/

    /* 收到dhcp IPv4, IPv6 协商完成标志，从而判断收到消息次序  */
    VOS_UINT8                           ucRcvDhcpDnsFlgIpv4;
    VOS_UINT8                           ucRcvDhcpDnsFlgIpv6;
    /* 作为协商开始标志位，结束清零 */
    VOS_UINT8                           ucNeedGetDnsFlg;
    VOS_UINT8                           ucRcvNdClientNtyFlg;

    MN_APS_PDP_IPV6_DNS_STRU            stPdpIpV6Dns;       /* IPv6 DNS */
    TAF_PDP_IPV6_PCSCF_STRU             stPdpIpv6Pcscf;     /* IPv6 P-CSCF */
    TAF_PDP_IPV6_RA_INFO_STRU           stIpv6RaInfo;       /* IPv6 RA参数信息 */
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    SM_TAF_TRANS_ID_STRU                stTransId;

#if (FEATURE_ON == FEATURE_LTE)
    SM_ESM_TFT_STRU                     stTft;              /* Packet Filter */
#endif
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyFlg;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    /* 用于内部去激活后, 是否上报PDP_DEACTIVATE_IND事件标识  */
    VOS_UINT8                           ucInterDeactNotifyFlg;

    /* 默认承载的标志 */
    VOS_UINT8                           ucDefaultBearerFlag;

    TAF_APS_PDP_MOD_DIAL_STRU           stModDial;

    TAF_APS_CDATA_CONTEXT_ENTITY_STRU   stCdataInfo;

    VOS_INT16                           sRssi;
    VOS_UINT8                           ausReserved[2];

}APS_PDP_CONTEXT_ENTITY_ST;

typedef APS_PDP_CONTEXT_ENTITY_ST TAF_APS_PDN_CONTEXT_STRU;


/*入呼TI记录表，有效索引为1-7*/
typedef struct
{
    VOS_UINT8   ucIncomCallNum;
    VOS_UINT8   ucTi[APS_MIDDLE_TI + 1];
}APS_INCOM_CALL_TI_TABLE;

/*用来存放网络返回的CPO*/
typedef struct
{
    VOS_UINT32                          ulFlg;              /*VOS_TRUE:有效
                                                              VOS_FALSE:无效*/
    SM_TAF_PROT_CFG_OPT_STRU            ApsNetPco;
} APS_NET_PCO_ST;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS 流程入口                    */
/*=======================================================*/
typedef struct
{
    VOS_UINT32                          OP_APN      : 1;
    VOS_UINT32                          OP_AUTH     : 1;
    VOS_UINT32                          OP_DNS      : 1;
    VOS_UINT32                          OP_NBNS     : 1;
    VOS_UINT32                          OP_Sapi     : 1;
    VOS_UINT32                          Op_Xid_PCmp : 1;
    VOS_UINT32                          Op_Xid_DCmp : 1;

    VOS_UINT32                          OP_SPARE    : 25;


    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucSapi;         /*Add SAPI for 2G
                                                          0 0 0 0  LLC SAPI not assigned
                                                          0 0 1 1  SAPI 3
                                                          0 1 0 1  SAPI 5
                                                          1 0 0 1  SAPI 9
                                                          1 0 1 1  SAPI 11*/

    VOS_UINT8                           ucPdpType;      /*#define APS_ADDR_DYNAMIC_IPV4 0
                                                          #define APS_ADDR_STATIC_IPV4  1
                                                          #define APS_ADDR_PPP          2 */

    VOS_UINT8                           ucPCmprAlgrth;  /*#define SN_1144_ALGRTH        0
                                                          #define SN_2507_ALGRTH        1
                                                          #define SN_ROHC_ALGRTH        2 */

    VOS_UINT8                           ucDCmprAlgrth;  /*#define SN_V42_ALGRTH         0
                                                          #define SN_V44_ALGRTH         1 */

    VOS_UINT8                           aucApn[APS_MAX_LENGTH_OF_APN];
                                                        /*24008中规定的APN长度和码流*/
    VOS_UINT8                           aucReserved[2];

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];

    APS_PDP_QOS_ST                      ReqQos;
    TAF_PDP_PCO_AUTH_STRU               PdpAuth;
    TAF_PDP_DNS_STRU                    PdpDns;
    TAF_PDP_NBNS_STRU                   PdpNbns;
}APS_PDP_ACT_REQ_ST;


typedef struct
{
    VOS_UINT32                          OP_Sapi     : 1;    /*Add SAPI for 2G*/
    VOS_UINT32                          Op_Tft      : 1;
    VOS_UINT32                          Op_Xid_PCmp : 1;
    VOS_UINT32                          Op_Xid_DCmp : 1;
    VOS_UINT32                          Op_Spare    : 28;

    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucPriPdpId;
    VOS_UINT8                           ucSapi;             /*Add SAPI for 2G*/
    VOS_UINT8                           ucPCmprAlgrth;      /*#define SN_1144_ALGRTH        0
                                                              #define SN_2507_ALGRTH        1
                                                              #define SN_ROHC_ALGRTH        2 */

    VOS_UINT8                           ucDCmprAlgrth;      /*#define SN_V42_ALGRTH         0
                                                              #define SN_V44_ALGRTH         1*/
    VOS_UINT8                           aucRsv[3];
    APS_PDP_QOS_ST                      Qos;
    APS_PDP_TFT_ST                      Tft;
} APS_PDP_SEC_ACT_REQ_ST;

typedef struct
{
    VOS_UINT32                          Op_Qos      :1;
    VOS_UINT32                          Op_Tft      :1;

    /*Add SAPI for 双模*/
    VOS_UINT32                          OP_Sapi     :1;
    VOS_UINT32                          Op_Spare    :29;

    /*Add SAPI for 双模*/
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucRsv[2];
    APS_PDP_QOS_ST                      Qos;
    APS_PDP_TFT_ST                      Tft;
} APS_PDP_MDF_REQ_ST;

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucTearDown;
    SM_TAF_CAUSE_ENUM_UINT16            enCause;
} APS_PDP_DEACT_REQ_ST;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SM返回参数                  */
/*=======================================================*/
typedef struct {
    VOS_UINT32                          OP_PdpAddr          : 1;
    VOS_UINT32                          OP_ProtCfgOpt       : 1;
    VOS_UINT32                          OP_Sapi             : 1;
    VOS_UINT32                          OP_RadioPriority    : 1;
    VOS_UINT32                          OP_PacketFlowId     : 1;

    VOS_UINT32                          OP_Spare            : 27;

    VOS_UINT8                           ucNsapi;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2*/
    VOS_UINT8                           ucPacketFlowId;
    APS_PDP_QOS_ST                      PdpQos;
    APS_PDP_ADDR_ST                     PdpAddr;
    APS_PDP_DNS_ST                      PcoDns;
    APS_PDP_NBNS_ST                     PcoNbns;
    MN_APS_PDP_GATEWAY_STRU             stPcoGateWay;
#if (FEATURE_ON == FEATURE_LTE)
    SM_TAF_TRANS_ID_STRU                stTransId;
#endif
} APS_ACTCNF_PARA_ST;

typedef struct
{
    VOS_UINT32                               OP_Sapi             : 1;
    VOS_UINT32                               OP_RadioPriority    : 1;
    VOS_UINT32                               OP_PacketFlowId     : 1;
    VOS_UINT32                               OP_Spare            : 29;

    APS_PDP_QOS_ST                      PdpQos;
    VOS_UINT8                           ucNsapi;

    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
#if (FEATURE_ON == FEATURE_LTE)
    SM_TAF_TRANS_ID_STRU                stTransId;
#endif
} APS_ACTSECCNF_PARA_ST;




typedef struct
{
    VOS_UINT32                          OP_QOS              : 1;
    VOS_UINT32                          OP_SAPI             : 1;
    VOS_UINT32                          OP_RadioPri         : 1;
    VOS_UINT32                          OP_PFI              : 1;
    VOS_UINT32                          OP_SPARE            : 28;

    APS_PDP_QOS_ST                      PdpQos;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;    /*Refer to 24.008 10.5.7.2
                                                            1: riority level 1 (highest)
                                                            2: riority level 2
                                                            3: riority level 3
                                                            4: riority level 4 (lowest)*/
    VOS_UINT8                           ucPacketFlowId;

    VOS_UINT8                           aucReserved[1];
} APS_MDFCNF_PARA_ST;

typedef struct
{
    VOS_UINT32                          OP_PdpAddr          : 1;
    VOS_UINT32                          OP_Nsapi            : 1;

    /*Add SAPI、RadioPriority for 2G */
    VOS_UINT32                          OP_Sapi             : 1;
    VOS_UINT32                          OP_RadioPriority    : 1;
    VOS_UINT32                          OP_PacketFlowId     : 1;
    VOS_UINT32                          OP_Spare            : 27;

    APS_PDP_QOS_ST                      NewQos;
    APS_PDP_ADDR_ST                     PdpAddr;
    VOS_UINT8                           ucNsapi;

    /*Add SAPI、RadioPriority for 2G */
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
} APS_MDFIND_PARA_ST;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS 发给SNDCP的参数             */
/*=======================================================*/

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
    SM_TAF_QOS_STRU                    *pQos;
} APS_INNER_SN_ACT_ST;

typedef struct
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
    SM_TAF_QOS_STRU                    *pQos;
} APS_INNER_SN_MDF_ST;



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SNDCP发给APS的参数          */
/*=======================================================*/
/*见 Taf_ApsForSndcp.h*/


typedef struct
{
    VOS_UINT32                          ulTLLI;
    VOS_UINT8                           ucSapi;
    VOS_UINT8                           aucReserved[3];
    APS_SNDCP_XID_REQ_TAB_ST            XidReqTab[APS_NSAPI_MAX + 1];
                                                            /*该数组的位置为NSAPI的索引*/
}APS_SNDCP_ACT_REQ_ST;


typedef struct{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgType;          /*消息类型*/

    /*即ucNsapi;范围与意义见SN_DATA_REQ_ST中的说明该字段在消息中以子进程表示*/
    VOS_UINT16                          usPId;

    VOS_VOID                           *pSnMsg;
} APS_SNDCP_COMMON_MSG;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS MONITOR 热保护相关                    */
/*=======================================================*/
typedef struct
{
    VOS_UINT32  ulModPdpFlg;      /* 0 - 热保护模块未发起MODIFY PDP操作;  1 - 热保护模块发起了MODIFY PDP操作 */
    VOS_UINT8   ucPdpId;
    VOS_UINT8   ucCid;
    VOS_UINT8   aucRsv[2];
}APS_MONITOR_MOD_PDP_INFO_STRU;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   终端可配置需求增加的结构体          */
/*=======================================================*/

/* 终端可配置需求: Mean throughput 配置 */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV有效标志位，0：无效 */
    VOS_UINT8   ucMeanThrough;
}APS_MEAN_THROUGH_CUSTOMIZE_STRU;

/*****************************************************************************
 结构名  : TAF_APS_SM_ERROR_MAP_STRU
 结构说明: TAF错误码与SM错误码映射结构

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCuase;
    SM_TAF_CAUSE_ENUM_UINT16            enSmCause;
    VOS_UINT8                           aucRsv[2];

} TAF_APS_SM_ERR_CODE_MAP_STRU;

/*****************************************************************************
 结构名  : TAF_APS_ESM_ERR_CODE_MAP_STRU
 结构说明: TAF错误码与ESM错误码映射结构

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    VOS_UINT32                          ulEsmCause;

} TAF_APS_ESM_ERR_CODE_MAP_STRU;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 结构名  : TAF_APS_XCC_ERR_CODE_MAP_STRU
 结构说明: TAF错误码与XCC错误码映射结构

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;

} TAF_APS_XCC_ERR_CODE_MAP_STRU;

/*****************************************************************************
 结构名  : TAF_APS_HSM_ERR_CODE_MAP_STRU
 结构说明: TAF错误码与HSM错误码映射结构

 修改历史      :
  1.日    期   : 2015年01月12日
    作    者   : y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    HSM_APS_CAUSE_ENUM_UINT32           enHsmCause;

} TAF_APS_HSM_ERR_CODE_MAP_STRU;


/*****************************************************************************
 结构名  : TAF_APS_EHSM_ERR_CODE_MAP_STRU
 结构说明: TAF错误码与EHSM错误码映射结构

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;
    EHSM_APS_CAUSE_ENUM_UINT32          enEhsmCause;

} TAF_APS_EHSM_ERR_CODE_MAP_STRU;

/*****************************************************************************
 结构名  : TAF_APS_3GPD_FILEID_FLAG_MAP_STRU
 结构说明: TAF读取3gpd 文件id 和读取标志位的map结构

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32                            usEfId;
    TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32                  enSimFileCnfFlg;

} TAF_APS_3GPD_FILEID_FLAG_MAP_STRU;
#endif

typedef VOS_UINT32 (*MN_PS_MSG_FUNC)(VOS_VOID *pMsgData);

/*****************************************************************************
 结构名称: ID_MN_PS_EVT_ID_ENUM
 结构说明: MN和APP之间的事件原语
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    MN_PS_MSG_FUNC                      pMsgFunc;
} MN_PS_MSG_FUNC_TBL_STRU;

typedef struct
{
    const MN_PS_MSG_FUNC_TBL_STRU      *pstMsgFuncTbl;
    const VOS_UINT32                    ulMsgTblSize;
} MN_PS_MSG_TBL_ENTRY_STRU;

/*****************************************************************************
 结构名称: TAF_APS_CHAP_PARAM_STRU
 结构说明: The struct contains the parameter of CHAP.
           ulChallengeLen     - Length of challenge
           aucChallenge       - Array of challenge
           ulChallengeNameLen - Length of challenge name
           aucChallengeName   - Array of challenge name (system name "HUAWEI_CHAP_SRVR")
           ulResponseLen      - Length of response
           aucResponse        - Array of response
           ucResponseNameLen  - Length of response name (username)
           aucResponseName    - Array of response name (username)

           The Response Value is the one-way hash calculated over a stream of
           octets consisting of the Identifier, followed by (concatenated with)
           the "secret", followed by (concatenated with) the Challenge Value.
           The length of the Response Value depends upon the hash algorithm
           used (16 octets for MD5). Refer to RFC[1994] section 4.1.

 1.日    期   : 2012年08月20日
   作    者   : f00179208
   修改内容   : Added for LTE PPP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulChallengeLen;
    VOS_UINT8                           aucChallenge[TAF_APS_PPP_CHAP_CHALLNGE_LEN];
    VOS_UINT32                          ulChallengeNameLen;
    VOS_UINT8                           aucChallengeName[TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN];
    VOS_UINT32                          ulResponseLen;
    VOS_UINT8                           aucResponse[TAF_APS_PPP_CHAP_RESPONSE_LEN];
    VOS_UINT8                           ucResponseNameLen;
    VOS_UINT8                           aucResponseName[TAF_MAX_USERNAME_LEN];

} TAF_APS_CHAP_PARAM_STRU;

/*****************************************************************************
 结构名称: TAF_APS_PAP_PARAM_STRU
 结构说明: The struct contains the parameter of PAP.
           ucUsernameLen - Length of username
           aucUsername   - Array of username
           ucPasswordLen - Length of password
           aucPassword   - Array of password

 1.日    期   : 2012年08月20日
   作    者   : f00179208
   修改内容   : Added for LTE PPP
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsernameLen;
    VOS_UINT8                           aucUsername[TAF_MAX_USERNAME_LEN];
    VOS_UINT8                           ucPasswordLen;
    VOS_UINT8                           aucPassword[TAF_MAX_PASSCODE_LEN];

} TAF_APS_PAP_PARAM_STRU;

/*****************************************************************************
 结构名称: TAF_APS_AUTH_INFO_STRU
 结构说明: The struct contains the authentication information.
           enAuthType  - Auth type (NONE/PAP/CHAP)
           ucAuthId    - Identifier
           stChapParam - Parameters of CHAP
           stPapParam  - Parameters of PAP

 1.日    期   : 2012年08月20日
   作    者   : f00179208
   修改内容   : Added for LTE PPP
*****************************************************************************/
typedef struct
{
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enAuthType;
    VOS_UINT8                           ucAuthId;
    VOS_UINT8                           aucRsv[2];

    union
    {
        TAF_APS_CHAP_PARAM_STRU         stChapParam;
        TAF_APS_PAP_PARAM_STRU          stPapParam;
    } unAuthParam;

} TAF_APS_AUTH_INFO_STRU;


/*****************************************************************************
 结构名称: TAF_APS_IPCP_INFO_STRU
 结构说明: The struct contains the IPCP information.
           aucIpAddr   - IP address
           aucPrimDns  - Primary DNS address
           aucSecDns   - Secondary DNS address
           aucPrimNbns - Primary NBNS address
           aucSecNbns  - Secondary NBNS address

 1.日    期   : 2012年08月20日
   作    者   : f00179208
   修改内容   : Added for LTE PPP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpAddr         :1;
    VOS_UINT32                          bitOpPrimDns        :1;
    VOS_UINT32                          bitOpSecDns         :1;
    VOS_UINT32                          bitOpPrimNbns       :1;
    VOS_UINT32                          bitOpSecNbns        :1;
    VOS_UINT32                          bitOpSpare          :27;

    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucPrimNbns[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecNbns[TAF_IPV4_ADDR_LEN];

} TAF_APS_IPCP_INFO_STRU;

/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */

typedef struct
{
    VOS_UINT8                           ucCode;                                 /* Request code */
    VOS_UINT8                           ucId;                                   /* Identification */
    VOS_UINT16                          usLength;                               /* Length of packet */
} TAF_PPP_FRAME_HEAD_STRU;


/*****************************************************************************
 结构名称: TAF_NDIS_AUTHDATA_TABLE_STRU
 结构说明: NDIS鉴权参数表结构

 修改历史      :
  1.日    期   : 2013年07月18日
    作    者   : Y00213812
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUsed;                                 /*0：未使用，1：使用*/
    VOS_UINT8                           aucReserved[3];
    TAF_PDP_AUTHDATA_STRU               stAuthData;                             /*鉴权参数*/

} TAF_NDIS_AUTHDATA_TABLE_STRU;


typedef struct
{
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      enAnsMode;
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8      enAnsType;
    VOS_UINT16                          usClientId;
}TAF_PS_ANSWER_MODE_STRU;

/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

typedef struct
{
    VOS_UINT32                          ulNum;
    VOS_UINT8                           aucCid[TAF_MAX_CID + 1];
}TAF_APS_BITCID_INFO_STRU;

/*****************************************************************************
 结构名称: TAF_APS_MATCH_PARAM_STRU
 结构说明: 拨号参数匹配结构

 修改历史      :
  1.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrimaryPdpFlg;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    VOS_UINT8                           aucReserved[1];
    TAF_PDP_APN_STRU                    stApn;
} TAF_APS_MATCH_PARAM_STRU;

/*****************************************************************************
 结构名称: TAF_APS_CID_IMS_CFG_TBL_STRU
 结构说明: CID IMS配置表

 修改历史      :
  1.日    期   : 2015年7月30日
    作    者   : z00301431
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8            aucImsFlag[TAF_MAX_CID + 1];
}TAF_APS_CID_IMS_CFG_TBL_STRU;


/*****************************************************************************
 结构名称  : TAF_APS_GPRS_DATA_STRU
 结构说明  : GPRS数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucNsapi;
    VOS_UINT16                          usSendTimes;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulMillSecs;

} TAF_APS_GPRS_DATA_STRU;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM相关                    */
/*=======================================================*/

/*****************************************************************************
  5 UNION定义
  typedef union
{
    VOS_UINT8    ucTemplate;
    VOS_UINT8    aucData[2];
} MAPS_TEMPLATE_UNION;
*****************************************************************************/

/*****************************************************************************
  6 消息头定义
    模块名＋意义＋HEADER
#define MAPS_TEMPLATE_HEADER    VOS_UINT16    usTotalsMsgLen;\
                                VOS_UINT32    ulSendModuleId;\
                                VOS_UINT32    ulRecvModuleId;
*****************************************************************************/

/*****************************************************************************
  7 消息定义
  typedef struct
{
    MAPS_TEMPLATE_HEADER
    VOS_UINT8    aucData[2];     消息体
} MAPS_TEMPLATE_MSG;
*****************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS RABM相关                    */
/*=======================================================*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                   for APS SNDCP相关                   */
/*=======================================================*/

/*****************************************************************************
  8 全局变量声明
extern VOS_UINT8* pgucMapsTemplateBuffer;指针＋全局标识＋类型＋模块名＋意义描述
*****************************************************************************/
extern  VOS_UINT8                       g_ucApsInitFlg;

/*----------------------------------------------------------------------------
variable name   : g_PdpModifyReqTable
type            :
description     : 全局变量,UE要求修改参数,将要修改为的值先填充在该表中,等网络侧
                  返回消息后,根据消息类型确定是用此处的参数修改上下文表中的参数,
                  还是用网络返回的消息修改上下文表中的参数.

                  APS_PDP_MDF_REQ_ST中的成员OP_SPARE将作为一个有用的标识被使用:
                  OP_SPARE被设置为0,作为无效状态;
                  当APS发起修改时,若不申请新QOS参数,OP_SPARE被设置为0;
                  当APS发起修改时,若申请新QOS,把申请的新QOS参数填入时,OP_SPARE被设置为1;
                  当SM返回MDF_CNF信息后,若状态机中更新QOS,则将此标识设置为2;
                  当SM返回MDF_CNF信息后,若状态机中不更新QOS,则将此标识设置为0;

                  APS_PDP_MDF_REQ_ST    g_PdpModifyReqTable[APS_MAX_PDP_NUM + 1 ]
value range     : APS_MAX_PDP_NUM宏定义为14。g_PdpModifyReqTable[i]中i的取值范围
                  为闭区间[0,6]和[8,14],注意不能等于7.
used by         :
----------------------------------------------------------------------------*/
extern  APS_PDP_MDF_REQ_ST             *g_PdpModifyReqTable;
#define APS_MDF_NO_QOS                  0
#define APS_MDF_HAS_QOS                 1
#define APS_MDF_CNF_RENEW_QOS           2

/*----------------------------------------------------------------------------
variable name   : g_TafCidTab
type            : TAF_PDP_TABLE_STRU
description     : PDP全局数据表，以CID为索引，是FLASH中PDP数据表在内存中的映像.
                  索引0在拨号激活时会使用,在CGACT时不会使用.

                  TAF_PDP_TABLE_STRU    g_TafCidTab[TAF_MAX_CID + 1]
value range     :
used by         :
----------------------------------------------------------------------------*/
extern  TAF_PDP_TABLE_STRU             *g_TafCidTab;

/*----------------------------------------------------------------------------
variable name   : g_PdpEntity
type            : VOS_UINT8
description     : APS的状态机,共支持11个PDP.在系统初始化1时申请内存空间，在系统
                  初始化2时进行初始化.

                  APS_PDP_CONTEXT_ENTITY_ST g_PdpEntity[APS_MAX_PDP_NUM +1]
value range     :
used by         : APS模块的所有涉及到状态机操作的函数.
----------------------------------------------------------------------------*/
extern  APS_PDP_CONTEXT_ENTITY_ST      *g_PdpEntity;

/*TAF通信参数表-PS*/
extern  TAF_PS_ANSWER_MODE_STRU         g_PsAnsMode;    /*PS应答模式存储表*/

extern VOS_UINT16                       g_PsRabToClientId[TAF_MAX_RABID + 1];

/*数传接口RabId与ClientId对应表*/
extern VOS_UINT16                       g_CsRabToClientId[TAF_MAX_RABID + 1];


/*----------------------------------------------------------------------------
Varible Name    : g_TimerTable
type            : STRUCT 数组
description     : APS_MAX_PDP_NUM 个上下文与该数组中的APS_MAX_PDP_NUM 个TIMER一
                  一对应。进入某个PENDING状态, 就要启动对应此PdpId的TIMER;结束
                  某个PENDING状态,也要停止对应此PdpId的TIMER;某PdpId的 TIMER超
                  时,根据PdpId和当前上下文的状态进行time expired 处理,同时Clean
                  此 TIMER 。
value range     : APS_MAX_PDP_NUM宏定义为14。g_TimerTable[i]中i的取值范围
                  为闭区间[0, 6]和[8, 14], 注意不能等于7。
usage           : 用DOPRA提供 TIMER 操作的函数来实现对 TIMER 的操作。
----------------------------------------------------------------------------*/
extern  HTIMER                          g_TimerTable[TAF_APS_MAX_PDPID];

/*暂存将被操作的PDP项，待操作结束后，与操作后的PDP项作比较，以决定需要对NVIM中
的数据进行怎样的修改*/
extern  TAF_PDP_TABLE_STRU              g_TmpPdpTab;

/*参数查询是否结束的标识*/
extern  VOS_UINT32                      g_AllRateTmpList[TAF_MAX_CID][3];

extern  const RABM_MSG_FUN_TYPE         g_RabmMsgFunMatrix[2][8];

/* 终端可配置需求:2G拨号请求禁止Spare_bit3等参数 */
#define APS_2G_BIT3_DISABLE              0    /*2G拨号时PDP激活消息携带Spare_bit3等参数  */
#define APS_2G_BIT3_ENABLE               1    /*2G拨号时PDP激活请求消息不携带bit3等参数  */
extern  VOS_UINT8   g_ucDisable2GR5QosExt;

/*Mean throughput定制 */
extern  VOS_UINT8   g_ucMeanThrough;

/* WINS可配置需求 */
extern  VOS_UINT8   g_ApsWins;

/*WIN7 NDIS特性新增:用于保存^AUTHDATA命令的鉴权数据*/
extern  TAF_NDIS_AUTHDATA_TABLE_STRU    *g_ApsNdisAuthdataTab;

extern  TAF_APS_CID_IMS_CFG_TBL_STRU   g_stCidImsCfgTable;

/*****************************************************************************
  9 FUNCTIONS定义
*****************************************************************************/
/*APS获取自动发起激活时PDP信息接口*/

/*-------------------------------------------------------*/
/*      APS-API(APS向TAFM提供的参数设置查询函数接口)     */
/*-------------------------------------------------------*/

/*定义、修改、删除PDP context，*/
VOS_VOID Aps_DefPsPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPara,
    VOS_UINT32                         *pulErrCode
);

/*定义、修改、删除Secondary PDP Context*/
VOS_VOID Aps_DefPsSecPdpContext (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_SEC_CONTEXT_EXT_STRU       *pPara,
    VOS_UINT32                         *pulErrCode
);


/*定义、修改、删除PDP Context中的DNS参数*/
VOS_VOID Aps_DefPsDns(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_DNS_EXT_STRU               *pDnsPara,
    VOS_UINT32                         *pulErrCode
);

/*定义、修改、删除PDP Context中的3G QOS参数*/
VOS_VOID Aps_DefPs3gReqQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
);

/*定义、修改、删除PDP Context中的3G最小可接受QOS参数*/
VOS_VOID Aps_DefPs3gMinAcceptQos(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_UMTS_QOS_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID    Aps_DefNdisAuthdata (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_AUTHDATA_EXT_STRU              *pPara,
    VOS_UINT32                         *pulErrCode);

VOS_UINT32  Aps_ChngAuthdata( TAF_AUTHDATA_EXT_STRU *pAuthdataPara,
                                      VOS_UINT8                   ucCid   );

VOS_VOID  Aps_DefAuthdata( TAF_AUTHDATA_EXT_STRU *pAuthdataPara,
                                  VOS_UINT8               ucCid   );


/*-------------------------------------------------------*/
/*      APS-API(APS向TAFM提供的流程操作函数接口)         */
/*-------------------------------------------------------*/
/*PDP激活*/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallOrig(VOS_UINT8 ucPdpId);

/*拨号用PDP激活*/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallForDial(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr,
    TAF_PDP_APN_STRU                   *pstApn,
    PPP_REQ_CONFIG_INFO_STRU           *pstPppConfigInfo
);

/*PDP修改*/
VOS_VOID Aps_PsCallModify(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
);

/*PDP去激活*/
VOS_VOID Aps_PsCallEnd(
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
);

/*提供给ATC以查询CID的PDP类型*/
TAF_PDP_TYPE_ENUM_UINT8 Taf_GetCidType(VOS_UINT8 ucCid);

/*-------------------------------------------------------*/
/*               for   Aps_Assistant.c                   */
/*-------------------------------------------------------*/

VOS_VOID    Aps_PdpTabInit(             VOS_VOID    );
VOS_VOID    Aps_AuthdataTabInit(VOS_VOID);
VOS_VOID    Aps_PdpEntityInit(          VOS_VOID    );

VOS_VOID    Aps_RelSmLocResource(       VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_ReleaseSndcpResource(   VOS_UINT8                   ucPdpId );


VOS_VOID    Aps_ReleaseApsResource  (   VOS_UINT8                   ucPdpId );

/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

VOS_VOID    Taf_IpAddr2LenStr(CONST     VOS_UINT8                      *pucIpAddr,
                                        VOS_UINT8                      *pucStr);
VOS_VOID    Taf_Apn2Lenstr(             VOS_UINT8                      *pucApn,
                                        VOS_UINT8                      *pucStr);
VOS_VOID    Aps_LenStr2Str(             VOS_UINT8                   ucMaxLen,
                                        VOS_UINT8                  *pLenStr,
                                        VOS_UINT8                  *pStr );

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : MN_APS_Itoa
 功能描述  : 根据转换基数(10或16), 将整数转换为ASCII码, 将结果输出至字符串
 输入参数  : usValue    - 待转换为ASCII码的整数
             pcStr      - 输出结果的字符串
             usRadix    - 转换基数
 输出参数  : 无
 返 回 值  : VOS_CHAR*
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_CHAR* MN_APS_Itoa(
    VOS_UINT16                          usValue,
    VOS_CHAR                           *pcStr,
    VOS_UINT16                          usRadix
);


/*****************************************************************************
 函 数 名  : MN_APS_ConvertIpv6AddrToStr
 功能描述  : 将IPV6地址格式转换为字符串格式
 输入参数  : aucIpAddr[]    - IPV6地址(协议格式)
             enIpStrType    - IPV6字符串格式表达类型
 输出参数  : aucAddrStr[]   - IPV6地址(字符串格式)
 返 回 值  : VOS_OK         - 转换成功
             VOS_ERR        - 转换失败
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_ConvertIpv6AddrToStr(
    VOS_UINT8                           aucAddrStr[],
    VOS_UINT8                           aucIpAddr[],
    MN_APS_IPV6_STR_TYPE_ENUM_UINT8     enIpStrType
);
#endif

VOS_VOID    Aps_3GQos2AppQos(           APS_PDP_QOS_STRU           *pApsQos,
                                        TAF_UMTS_QOS_STRU           *pTafQos);


VOS_VOID  Taf_PsParaSetResult(              VOS_UINT16               ClientId,
                                        VOS_UINT8                      OpId,
                                        TAF_PARA_SET_RESULT         Result,
                                        TAF_PARA_TYPE               ParaType,
                                        VOS_VOID                       *pPara );

VOS_UINT32 Taf_CheckActCid(                 VOS_UINT8                       ucCid);

VOS_UINT32  Aps_ChngDns(                TAF_PDP_DNS_EXT_STRU       *pDnsPara,
                                        VOS_UINT8                   ucCid  );


/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_UINT32    Aps_SetEvtAddr(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr
);
VOS_UINT32    Aps_SetEvtApn(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_APN_STRU                   *pstPdpApn
);

VOS_VOID    Aps_SetEvtCmp(              VOS_UINT8                    ucPdpId,
                                        TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *pPsAppEvt);

VOS_VOID    Aps_SetEvtDns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_DNS_STRU                   *pstDns,
    TAF_PDP_IPV6_DNS_STRU              *pstIpv6Dns
);

/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


/*****************************************************************************
 函 数 名  : MN_APS_SetEvtNbns
 功能描述  : 填写NBNS至事件
 输入参数  : VOS_UINT8                           ucPdpId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SetEvtNbns(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_NBNS_STRU                  *pstNbns
);

/*****************************************************************************
 函 数 名  : MN_APS_SetEvtGateWay
 功能描述  : 填写GATE WAY至事件
 输入参数  : VOS_UINT8                           ucPdpId
             TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SetEvtGateWay(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPsCallEvt
);


/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */



/*****************************************************************************
 函 数 名  : TAF_APS_SetEvtPcscf
 功能描述  : 填写P-CSCF信息至PS呼叫事件
 输入参数  : ucPdpId                    - PDP ID
             pstPsCallEvt               - PS呼叫事件
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TAF_APS_SetEvtPcscf(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_PCSCF_STRU                 *pstPcscf,
    TAF_PDP_IPV6_PCSCF_STRU            *pstIpv6Pcscf
);


VOS_VOID    Aps_GlobVarFree(            VOS_VOID);
VOS_UINT32  Aps_JudgeSapiValid(         VOS_UINT8                   ucSapi);

/*-------------------------------------------------------*/
/*          APS内部提供的参数定义函数接口                */
/*-------------------------------------------------------*/
VOS_UINT32  Aps_ChngPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
);

VOS_VOID Aps_DefPdpPri(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pPdpPriPara,
    VOS_UINT8                           ucCid
);

VOS_VOID    Aps_ChngSecPara(            TAF_PDP_SEC_CONTEXT_EXT_STRU       *pSecPara );
VOS_VOID    Aps_DefSecPara(             TAF_PDP_SEC_CONTEXT_EXT_STRU       *pSecPara );


VOS_VOID    Aps_ChngQos(                TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID    Aps_DefQos(                 TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID    Aps_ChngMinQos(             TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );
VOS_VOID    Aps_DefMinQos(              TAF_UMTS_QOS_EXT_STRU       *pQosPara,
                                        VOS_UINT8                   ucCid   );

VOS_VOID Aps_QuePri(
    VOS_UINT8                           ucCid,
    TAF_PRI_PDP_QUERY_INFO_STRU        *pPdpPriPara,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueSec(
    VOS_UINT8                           ucCid,
    TAF_PDP_SEC_CONTEXT_STRU           *pPdpSecPara,
    VOS_UINT32                         *pulErrorCode
);


VOS_VOID Aps_QueQosNeg(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pQosNeg,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueState(
    VOS_UINT8                           ucCid,
    TAF_CID_STATE_STRU                 *pPsState,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueRealIpAddr(
    VOS_UINT8                           ucCid,
    TAF_PDP_ADDR_QUERY_INFO_STRU       *paucIpAddr,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueAuthdata(
    VOS_UINT8                           ucCid,
    TAF_AUTHDATA_QUERY_INFO_STRU       *pAuthDataPara,
    VOS_UINT32                         *pulErrorCode
);

VOS_UINT32  Aps_NvimAct (               VOS_UINT8                   ucCid   );

APS_NVIM_ACT_TYPE Aps_JudegNvimActType( VOS_UINT8                   ucCid   );

VOS_VOID Aps_SetPsAnsMode(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      ucAnsMode,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID Aps_QueDns(
    VOS_UINT8                           ucCid,
    TAF_DNS_QUERY_INFO_STRU            *paucDns,
    VOS_UINT32                         *pulErrorCode
);

VOS_VOID    TAF_APS_SndCidInactiveEvt(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid
);


VOS_UINT8   *Aps_GetParaPointer(       TAF_PARA_TYPE       ParaType,
                                        VOS_UINT8            *pPrePtr);

VOS_VOID MN_APS_GetUtmsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID MN_APS_GetUtmsQosMinInfo(
    VOS_UINT8                           ucCid,
    TAF_UMTS_QOS_QUERY_INFO_STRU       *pstUmtsQosQueryInfo,
    VOS_UINT32                         *pulErrCode
);


VOS_VOID TAF_APS_SetTftInfo(
    TAF_TFT_EXT_STRU                   *pstTftInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID TAF_APS_FillTftQryParam(
    VOS_UINT8                           ucCid,
    TAF_TFT_QUREY_INFO_STRU            *pPdpTftPara
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_SetEpsQosInfo(
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
);

VOS_VOID TAF_APS_QueEpsQosInfo(
    VOS_UINT8                           ucCid,
    TAF_EPS_QOS_EXT_STRU               *pstEpsQosInfo,
    VOS_UINT32                         *pulErrCode
);
#endif

VOS_VOID Aps_DeleteLinkedCidSecPdpContext(
    VOS_UINT8                           ucCid
);


/*-------------------------------------------------------*/
/*          APS内部提供的流程操作类函数接口              */
/*-------------------------------------------------------*/
/*=======================激活流程========================*/
VOS_VOID  Aps_ActJudgePriOrSecAct (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                  *pucResult );


VOS_UINT32  Aps_PackApsActReqPara (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID  Aps_CopyAuthToActReqPara(
    CONST TAF_PDP_PCO_AUTH_STRU    *pAuthTab,
    TAF_PDP_PCO_AUTH_STRU          *pActReqParaAuth
);

VOS_VOID  Aps_CopyAddrToActReqPara(
    CONST  VOS_UINT8               *pucIpAddr,
    APS_PDP_ACT_REQ_ST             *pApsActReq
);

TAF_PS_CAUSE_ENUM_UINT32 Aps_PsCallOrigNormCid(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
);


VOS_UINT32  Aps_PackDialActReqPara(     VOS_UINT8                   ucPdpId,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pPsCallDialPara,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID  Taf_FillQos(                      TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_QOS_STRU           *pApsQos   );

VOS_VOID  Taf_FillMinQos(                   TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_QOS_STRU           *pApsQos   );

VOS_VOID Taf_LenStr2Apn(
    CONST TAF_PDP_APN_STRU              *pstApn,
    VOS_UINT8                           *pucApn
);

VOS_VOID  Taf_LenStr2IpAddr(CONST VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr);

VOS_UINT32  Aps_PackApsSecActReqPara (  VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq );

VOS_UINT32  Aps_FillTft(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_TFT_ST             *pApsTft );

VOS_VOID    Aps_FillXid(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID    Aps_FillDns(                TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_ACT_REQ_ST         *pApsActReq  );

VOS_VOID    Aps_FillSecXid(             TAF_PDP_TABLE_STRU         *pTafPdp,
                                        APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq  );

VOS_VOID    Aps_GetIpcpInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara);

VOS_UINT32  Aps_GetAuthInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara);

VOS_VOID    Aps_PPPAddr2ApsAddr(        APS_PCO_PPP_ST             *pOneIpcp,
                                        VOS_UINT8                  *pIpAddr);

VOS_UINT32  Aps_CheckOutOneIpcpOneId(   APS_PCO_IPCP_PPP_ST        *pOneIpcp,
                                        VOS_UINT8                   ucIpcpId,
                                        APS_PPP_ID_ST              *pPppId);

/*=======================修改流程========================*/


/*-------------------------------------------------------*/
/*       Aps_DealApiFlowMsgSmAct.c 模块的函数接口        */
/*-------------------------------------------------------*/
/*=======================激活流程========================*/
VOS_UINT32  Aps_PdpActReq(              APS_PDP_ACT_REQ_ST         *pActReq );
VOS_UINT32  Aps_PackSmActReqMsg (       APS_PDP_ACT_REQ_ST         *pActReq,
                                        SMREG_PDP_ACTIVATE_REQ_STRU        *pStPdpActReq);

VOS_VOID    Aps_ActReqFillState(        APS_PDP_ACT_REQ_ST         *pActReq);
VOS_VOID    TAF_APS_SndPdpActivateRej   (        VOS_UINT8                   ucPdpId,
                                        TAF_PS_CAUSE_ENUM_UINT32    enCause );

VOS_UINT32  Aps_PdpSecActReq(           APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);

VOS_VOID    Aps_SecActReqFillState(     APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);

VOS_UINT32  Aps_PdpSecActReqParaCheck ( APS_PDP_SEC_ACT_REQ_ST     *pSecActReq);
VOS_VOID    Aps_PackSmSecActReqMsg(     APS_PDP_SEC_ACT_REQ_ST     *pSecActReq,
                                                    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pStSecActReq );

/*=======================修改流程========================*/
VOS_UINT32  Aps_PdpMdfReq(              APS_PDP_MDF_REQ_ST         *pMdfReq);

VOS_VOID    Aps_PackSmMdfReqMsg(        APS_PDP_MDF_REQ_ST         *pMdfReq,
                                            SMREG_PDP_MODIFY_REQ_STRU       *pStPdpMdfReq   );

VOS_UINT32  Aps_PackApsMdfReqPara (     VOS_UINT8                   ucCid,
                                        VOS_UINT8                   ucPdpId,
                                        APS_PDP_MDF_REQ_ST*         pApsMdfReq  );
VOS_VOID    TAF_APS_SndPdpModifyRej   (        VOS_UINT8                   ucPdpId,
                                        TAF_PS_CAUSE_ENUM_UINT32    enCause );
VOS_VOID    Aps_PdpMdfRsp(              VOS_UINT8                   ucPdpId);

/*=======================去激活流程======================*/
VOS_UINT32 Aps_AppDeactReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

VOS_UINT32 Aps_PdpDeActReq(
    APS_PDP_DEACT_REQ_ST               *pDeActReq
);
VOS_VOID    Aps_PdpDeActOneReq(         APS_PDP_DEACT_REQ_ST       *pDeActReq,
                                        VOS_UINT8                   ucRelSmType);
VOS_UINT32  Aps_PdpDeActReqParaCheck(   APS_PDP_DEACT_REQ_ST       *pDeActReq );

/*=======================流程公共使用======================*/


VOS_VOID    Aps_PackSmQos   (           APS_PDP_QOS_ST             *pApsQos,
                                        SM_TAF_QOS_STRU                   *pSmQos  );

VOS_VOID  Aps_PackSmTft   (             VOS_UINT8                   ucPdpId,
                                        APS_PDP_TFT_ST*             pApsTft,
                                        SM_TAF_TFT_STRU*            pSmTft  );

VOS_UINT32  Aps_PackSmAddr  (           VOS_UINT8*                  pucPdpType,
                                        VOS_UINT8*                  pucAppAddr,
                                        SM_TAF_PDP_ADDR_STRU*       pSmAddr );

VOS_VOID    Aps_PackSmApn(              VOS_UINT8                  *pucAppApn,
                                        SM_TAF_APN_STRU                    *pSmApn      );

VOS_UINT32      Aps_QosValidOrNot(          APS_PDP_QOS_STRU           *psQos);

VOS_UINT32  Aps_PackSmPco(              APS_PDP_ACT_REQ_ST         *pActReq,
                                        SM_TAF_PROT_CFG_OPT_STRU           *pSmPco );

VOS_UINT8  *Aps_PackPcoAuth(            APS_PDP_ACT_REQ_ST         *pActReq,
                                        VOS_UINT8                  *pPcoAuthBegin);

VOS_UINT8  *Aps_PackPcoIpcp(            APS_PDP_ACT_REQ_ST         *pActReq,
                                        VOS_UINT8                  *pPcoIpcpBegin);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT8* MN_APS_FillPcoIpV6DnsPara(
    VOS_UINT8                          *pucPcoPkt
);
#endif


/*-------------------------------------------------------*/
/*          Aps_DealSmMsg.c 模块的函数接口               */
/*-------------------------------------------------------*/
/*=======================公共函数========================*/
VOS_UINT32  Aps_UnpackSmQos (  SM_TAF_QOS_STRU*            pSmQos,
                                        VOS_UINT8*                  pucQosLen,
                                        APS_PDP_QOS_ST*             pApsQos );

/*****************************************************************************
 函 数 名  : MN_APS_DecodeIpcpConfigReqPkt
 功能描述  : 解码IPCP包中的CONFIG_REQ
 输入参数  : pstPdpEntity       - PDP实体
             pucProtocolPacket  - 待解码的CONFIG_REQ的Packet地址
             usPktLen           - 存放CONFIG_REQ的Packet长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpConfigReqPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
);


/*****************************************************************************
 函 数 名  : MN_APS_DecodeIpcpConfigNakAckRejPkt
 功能描述  : 解码IPCP包中的CONFIG_NAK/CONFIG_ACK/CONFIG_REJ
 输入参数  : pstPdpEntity       - PDP实体
             pucProtocolPacket  - 待解码的CONFIG_NAK/CONFIG_ACK/CONFIG_REJ的Packet地址
             usPktLen           - 存放CONFIG_NAK/CONFIG_ACK/CONFIG_REJ的Packet长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpConfigNakAckRejPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
);


/*****************************************************************************
 函 数 名  : MN_APS_DecodeIpcpProtocolPkt
 功能描述  : 解码IPCP包
 输入参数  : pstPdpEntity       - PDP实体
             pucProtocolPkt     - 待解码的IPCP的Packet地址
             usProtocolPktLen   - 存放IPCP的Packet长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeIpcpProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPkt,
    VOS_UINT16                          usProtocolPktLen
);


/*****************************************************************************
 函 数 名  : TAF_APS_DecodeIpv4PcscfProtocolPkt
 功能描述  : 解码IPv4 P-CSCF Container
 输入参数  : pstPdpEntity           - PDP实体
             pucIpv6PcscfNum        - 已解码的IPv6 P-CSCF的数量
             pucProtocolPacket      - 待解码的IPv6 P-CSCF的Packet地址
             usProtocolPacketLen    - 存放IPv6 P-CSCF的Packet长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TAF_APS_DecodeIpv4PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv4PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : MN_APS_DecodeIpV6DnsProtocolPkt
 功能描述  : 解码IPV6 DNS Container
 输入参数  : pstPdpEntity           - PDP实体
             pucIpV6DnsNum          - 已解码的IPV6 DNS的数量
             pucProtocolPacket      - 待解码的IPV6 DNS的Packet地址
             usProtocolPacketLen    - 存放IPV6 DNS的Packet长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_DecodeIpV6DnsProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpV6DnsNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);


/*****************************************************************************
 函 数 名  : TAF_APS_DecodeIpv6PcscfProtocolPkt
 功能描述  : 解码IPV6 P-CSCF Container
 输入参数  : pstPdpEntity           - PDP实体
             pucIpv6PcscfNum        - 已解码的IPv6 P-CSCF的数量
             pucProtocolPacket      - 待解码的IPv6 P-CSCF的Packet地址
             usProtocolPacketLen    - 存放IPv6 P-CSCF的Packet长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TAF_APS_DecodeIpv6PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv6PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
);
#endif


/*****************************************************************************
 函 数 名  : MN_APS_DecodeProtocolConfigPara
 功能描述  : 解码PCO的参数
 输入参数  : pstPdpEntity       - PDP实体
             pstProtoCfgOptions - PCO参数内容
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_DecodeProtocolConfigPara(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions
);


/*****************************************************************************
 函 数 名  : MN_APS_UnpackProtocolOptionsList
 功能描述  : 根据Protocol ID拆出PCO的参数列表
 输入参数  : pstProtoCfgOptions - PCO参数内容
             pstSmPco           - PCO原始码流(OTA码流)
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_UnpackProtocolOptionsList(
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
);


/*****************************************************************************
 函 数 名  : MN_APS_UnpackPco
 功能描述  : 拆出PCO中DNS/NBNS等信息
 输入参数  : pstPdpEntity   - PDP实体
             pstSmPco       - PCO原始码流(OTA码流)
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_UnpackPco(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
);

VOS_UINT32  Aps_CheckOutPcoAuth(        SM_TAF_PROT_CFG_OPT_STRU            *pSmPco,
                                        APS_PCO_AUTH_PPP_ST        *pAuthPcoPPP);

VOS_UINT32  Aps_CheckOutPcoOneIpcp(     APS_PCO_IPCP_PPP_ST        *pIpcpPcpPPP,
                                        VOS_UINT8                   ucPcoCode,
                                        APS_PCO_PPP_ST             *pOneIpcp);

VOS_VOID    Aps_PPPDns2ApsDns(          APS_PCO_PPP_ST             *pOneIpcp,
                                        APS_PDP_DNS_ST             *pPdpDns);
VOS_VOID    Aps_PPPNbns2ApsNbns(          APS_PCO_PPP_ST     *pOneIpcp,
                                        APS_PDP_NBNS_ST     *pPdpNbns);
VOS_VOID    Aps_FillEvtPcoIpcpInfo(VOS_UINT8 *pucIpcpInfo, SM_TAF_PROT_CFG_OPT_STRU *pSmPco);

VOS_UINT32      Aps_DetachSmAddrStru (      SM_TAF_PDP_ADDR_STRU*         pSmAddr,
                                        APS_PDP_ADDR_ST*            pApsAddr  );

VOS_VOID    Aps_DetachSmApn  (          SM_TAF_APN_STRU*   pSmApn,
                                        APS_PDP_APN_ST*             pApsApn );
VOS_UINT32      Aps_CompareQos   (          APS_PDP_QOS_STRU*           pNetNegotQos,
                                        APS_PDP_QOS_STRU*           pUeMinQos,
                                        VOS_UINT8*                      pucQosOkOrNot   );
VOS_VOID    Aps_DecideTransMode(        VOS_UINT8                   ucPdpId,
                                        RABM_TRANS_MODE_ENUM       *pTransMode   );
VOS_UINT32  Aps_CheckPdpType(VOS_UINT8 ucPdpId, SM_TAF_PDP_ADDR_STRU *pSmAddr);
VOS_VOID    Aps_ValidPacketFlowId(VOS_UINT8 *pucPacketFlowId);

/*=======================激活流程========================*/
VOS_UINT32  Aps_PdpActCnfParaCheck  (   SMREG_PDP_ACTIVATE_CNF_STRU         *pSmActCnfMsg,
                                        APS_ACTCNF_PARA_ST         *pActCnfPara );

VOS_UINT32  Aps_CheckQosSatisify (      VOS_UINT8                   ucPdpId,
                                        APS_PDP_QOS_STRU*           pNetNegotQos);

VOS_UINT32      Aps_GetPsMinQos(            VOS_UINT8                   ucPdpId,
                                        VOS_UINT8                      *pDefinedOrNot,
                                        APS_PDP_QOS_STRU           *pQos );
VOS_VOID    Aps_PdpActCnfQosSatisfy (   VOS_UINT8          ucPdpId,
                                        APS_ACTCNF_PARA_ST          *pActCnfPara,
                                        SMREG_PDP_ACTIVATE_CNF_STRU *pStCnf   );
VOS_VOID    TAF_APS_SndPdpActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);
VOS_VOID TAF_APS_SndPdpActivateInd(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID    Aps_PdpQosNotSatisfy (      VOS_UINT8                   ucPdpId,
                                        APS_QOS_NOT_SATISFY_MSGTYPE_ENUM  QosMsgType );

VOS_UINT32 TAF_APS_SndPdpManageInd(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd
);
VOS_UINT32 Aps_ActIndAutoAns(
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8                     AnswerType,
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd,
    APS_PDP_ACT_REQ_ST                 *pstApsPdpActReq
);
VOS_UINT32      TAF_APS_GetPsReqPdp(            APS_PDP_ACT_REQ_ST         *pReqPdp);
VOS_VOID    Aps_ActIndRejRsp(           VOS_UINT8                   ucPdpId );

VOS_UINT32  Aps_PdpActSecCnfParaCheck(  SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pStSecCnf,
                                        APS_ACTSECCNF_PARA_ST      *pActSecCnfPara );

VOS_VOID    Aps_PdpActSecCnfQosSatisfy( VOS_UINT8                   ucPdpId,
                                        APS_ACTSECCNF_PARA_ST      *pSecCnfPara,
                                        SMREG_PDP_ACTIVATE_SEC_CNF_STRU   *pStSecCnf   );

VOS_VOID  Aps_GetPsAnswerMode  (
    TAF_PDP_ANSWER_MODE_ENUM_UINT8            *pAnswerMode,
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8            *pAnswerType);
VOS_UINT32  Taf_ComparePdp(             APS_PDP_ACT_REQ_ST         *pApsPdp,
                                        TAF_PDP_PRIM_CONTEXT_STRU           *pTafCidPdp);

VOS_VOID    Aps_CheckAddrWithActPdp(    VOS_UINT8           ucPdpId,
                                        VOS_UINT8          *pucIpAddr);

/*=======================修改流程========================*/
VOS_UINT32  Aps_PdpMdfCnfParaCheck (    SMREG_PDP_MODIFY_CNF_STRU    *pStMdfCnf,
                                        APS_MDFCNF_PARA_ST         *pMdfCnfPara );
VOS_VOID    Aps_PdpMdfCnfQosSatisfy (   VOS_UINT8                   ucPdpId,
                                        APS_MDFCNF_PARA_ST         *pMdfCnfPara,
                                        SMREG_PDP_MODIFY_CNF_STRU  *pMdfCnf);

VOS_VOID    TAF_APS_SndPdpModifyCnf( VOS_UINT8                   ucPdpId );


VOS_UINT32  Aps_PdpMdfIndParaCheck (    SMREG_PDP_MODIFY_IND_STRU     *pStMdfInd,
                                        APS_MDFIND_PARA_ST         *pMdfIndPara );
VOS_VOID    Aps_PdpMdfIndQosSatisfy (   VOS_UINT8                   ucPdpId,
                                        APS_MDFIND_PARA_ST         *pMdfIndPara,
                                        SMREG_PDP_MODIFY_IND_STRU  *pStMdfInd  );
VOS_VOID    TAF_APS_SndPdpModifyInd( VOS_UINT8                   ucPdpId );

/*=======================去激活流程======================*/
VOS_VOID    TAF_APS_SndPdpDeActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID    TAF_APS_SndPdpDeActivateInd(
   VOS_UINT8                           ucPdpId,
   TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*=======================指示SNDCP流程========================*/
VOS_VOID  Aps_SmMsgModSnActInd  (     APS_INNER_SN_ACT_ST        *pInnerSnActInd,
                                        VOS_UINT8                   ucActCause);
VOS_VOID    Aps_SmMsgModSnActIndParaPack
                            (           APS_INNER_SN_ACT_ST        *pInnerSnActInd,
                                        APS_SNDCP_ACTIVATE_IND_ST  *pSnActIndPara  );

VOS_VOID    Aps_SetSnXidPara(           VOS_UINT8                   ucPdpId,
                                        SN_XID_REQ_ST              *pSnXid  );

VOS_VOID  Aps_SmMsgModSnMdfInd  (     APS_INNER_SN_MDF_ST        *pInnerSnMdfInd );

VOS_VOID    Aps_SmMsgModSnMdfIndParaPack
                            (           APS_INNER_SN_MDF_ST        *pInnerSnMdfInd,
                                        APS_SNDCP_MODIFY_IND_ST    *pSnMdfIndPara   );
VOS_UINT32  Aps_SmMsgModSnDeActInd (    VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_SmMsgModSnDeActIndParaPack
                            (           VOS_UINT8                   ucPdpId,
                                        APS_SNDCP_DEACTIVATE_IND_ST *pSnDeActIndPara );

/*-------------------------------------------------------*/
/*          Aps_DealSNDCPMsg.c 模块的函数接口            */
/*-------------------------------------------------------*/
VOS_VOID    Aps_SnMsgModSnActRsp   (    APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp );

VOS_UINT32  Aps_SnMsgModSnActRspParaCheck
                                   (    APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp);
VOS_VOID    Aps_SnMsgModSnMdfRsp   (    APS_SNDCP_MODIFY_RSP_ST*    pSnMdfRsp );

VOS_UINT32  Aps_SnMsgModSnMdfRspParaCheck
                                   (    APS_SNDCP_MODIFY_RSP_ST*    pSnActRsp);

VOS_UINT32  Aps_SnMsgModSnDeActRspParaCheck
                                   (    APS_SNDCP_DEACTIVATE_RSP_ST *pSnActRsp);

VOS_VOID    Aps_SnMsgModSnStatusReq(    APS_SNDCP_STATUS_REQ_ST    *pSnStatusReq );

VOS_UINT32  Aps_SnMsgModSnStatusReqParaCheck
                                   (    APS_SNDCP_STATUS_REQ_ST    *pSnActRsp);
VOS_VOID    Aps_FindSapiPdp(            VOS_UINT8                   ucSapi);
VOS_VOID    Aps_FindSapiTransModePdp(   VOS_UINT8                   ucSapi);

VOS_VOID    Aps_SnMsgModSnXidReq(       APS_SN_XID_REQ_MSG         *pSnXidReqMsg );

VOS_UINT32  Aps_SnMsgModSnXidReqParaCheck(
                                        APS_SN_XID_REQ_MSG         *pSnXidReqMsg);

VOS_VOID    Aps_SnMsgModSnXidCnf(       VOS_UINT8                   ucNsapi,
                                        SN_XID_REQ_ST              *pXid );

VOS_VOID    Aps_XidReqEvt(              VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_SnMsgModSnXidRsp(       APS_SN_XID_RSP_MSG         *pSnXidRspMsg );

VOS_VOID    Aps_SnActRspChngEntity(     APS_SNDCP_ACTIVATE_RSP_ST  *pSnActRsp,
                                        VOS_UINT8                   ucPdpId);
VOS_VOID    Aps_SnMdfRspChngEntity(     APS_SNDCP_MODIFY_RSP_ST    *pSnMdfRsp,
                                        VOS_UINT8                   ucPdpId);
VOS_UINT32  Aps_SetRabmTransMode(       RABM_APS_SET_TRANS_MODE_ST *pApsRabmSetTRansMod);

/*-------------------------------------------------------*/
/*          Aps_DealRABMMsg.c 模块的函数接口             */
/*-------------------------------------------------------*/
VOS_VOID    Aps_RabmMsgModStateCheck (  VOS_UINT8                   ucPdpId,
                                        VOS_UINT8                  *pucMatrixRow);

VOS_VOID    Aps_Nop  (                  VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_G2WOnActPending  ( VOS_UINT8    ucPdpId );
VOS_VOID    Aps_RabmMsgDeAct (          VOS_UINT8                   ucPdpId );
VOS_VOID    Aps_RabmMsgDeActSndcp (     VOS_UINT8                   ucPdpId );

VOS_VOID    Aps_RabmMsgActSndcp (       VOS_UINT8                   ucPdpId );
/*
VOS_UINT32  Aps_GetAllNegoRate  (       APS_RABM_ALL_RATE_ST       *pAllRate);

VOS_VOID    Aps_GetOneNegoRate  (       VOS_UINT8                   ucPdpId,
                                        APS_RABM_ONE_RATE_ST       *pOneRate    );
*/
VOS_UINT32  Aps_ChngQosRate2UserRate(
        VOS_UINT8                           ucQosRateExt,
        VOS_UINT8                           ucQosRate
);

VOS_VOID    Aps_DeactAllPdp( VOS_VOID );
VOS_VOID    Aps_Init( VOS_VOID );
VOS_VOID    Aps_DbInit( VOS_VOID );
VOS_VOID    Aps_LoadDefault(VOS_VOID);
VOS_VOID    Aps_PowerOff(VOS_VOID);


/*****************************************************************************
 函 数 名  : MN_APS_GetPdpCidPara
 功能描述  : 获取PDP CID表信息
 输入参数  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo,
    VOS_UINT8                           ucCid
);

/*****************************************************************************
 函 数 名  : TAF_APS_FindCidForDial
 功能描述  : 查找空闲的CID, 用于拨号
 输入参数  : entityState --- PDP实体状态
 输出参数  : 无
 返 回 值  : VOS_UINT8
*****************************************************************************/
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid);

/*****************************************************************************
 函 数 名  : MN_APS_SetPdpCidPara
 功能描述  : 设置PDP上下文
 输入参数  : VOS_UINT16                          usClientId
             TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_SetPdpCidPara(
    VOS_UINT16                          usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);


/* 其他模块提供的API接口 */

VOS_VOID Aps_UpdateWinsConfig(VOS_UINT8 ucWins);

VOS_UINT8   Taf_PsCallForDialParaCheck( PPP_REQ_CONFIG_INFO_STRU *pPsDialPara);


/*****************************************************************************
 函 数 名  : TAF_APS_SndPsEvt
 功能描述  : 发送PS域事件
 输入参数  : ulEvtId                    - 事件ID
             pData                      - 事件数据内容(不包含消息头)
             ulLength                   - 事件数据长度
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送消息成功
             VOS_ERR                    - 发送消息失败
*****************************************************************************/
VOS_UINT32 TAF_APS_SndPsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvCallOrigReq
 功能描述  : 处理ID_MN_PS_CALL_ORIG_REQ消息
 输入参数  : ucPdpId      --- APS实体索引
             pstDialParam --- 拨号参数
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvCallOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParam
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvCallModifyReq
 功能描述  :
 输入参数  : ucPdpId                    - APS实体索引
             pstCallOrigReq             - 修改PDP参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvCallModifyReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq,
    VOS_UINT8                          *pucErrCode
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpCtxStateReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpCtxStateReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetPrimPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPrimPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetSecPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetSecPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_VOID MN_APS_RcvGetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetTftInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetTftInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetTftInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetTftInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetUmtsQosInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetUmtsQosInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetUmtsQosMinInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetUmtsQosMinInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvGetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicUmtsQosInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetDynamicUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpIpAddrInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpIpAddrInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetAnsModeInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID MN_APS_RcvSetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetAnsModeInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicPrimPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicSecPdpCtxInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetDynamicTftInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetDynamicTftInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvSetPdpDnsInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvSetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
);
/*****************************************************************************
 函 数 名  : MN_APS_RcvGetPdpDnsInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
);


/*****************************************************************************
 函 数 名  : MN_APS_RcvConfigNbnsFunctionReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvConfigNbnsFunctionReq(
    VOS_VOID                           *pMsgData
);


/*****************************************************************************
 函 数 名  : MN_APS_RcvSetAuthDataInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
*****************************************************************************/
VOS_VOID MN_APS_RcvSetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetAuthDataInfoReq
 功能描述  :
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID MN_APS_RcvGetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvGetGprsActiveTypeReq
 功能描述  : 处理ID_MSG_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ消息
 输入参数  : pMsgData                   - 消息内容(不包含消息头)
 输出参数  : 无
 返 回 值  : VOS_OK                     - 成功
             VOS_ERR                    - 失败
*****************************************************************************/
VOS_UINT32 MN_APS_RcvGetGprsActiveTypeReq(
    VOS_VOID                           *pMsgData
);

/*****************************************************************************
 函 数 名  : MN_APS_RcvPppDialOrigReq
 功能描述  : 处理ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输入参数  : ucPdpId            --- APS实体索引
             pstPppDialParaInfo --- PPP拨号参数
 输出参数  : 无
 返 回 值  : TAF_PS_CAUSE_ENUM
*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvPppDialOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo
);

VOS_VOID TAF_APS_SndCallOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallEndCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallModifyCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndSetPdpCtxStateCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_APS_SndCallAnswerCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucErrCode
);

VOS_VOID TAF_APS_SndCallHangupCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucErrCode
);
VOS_VOID TAF_APS_SndPppDialOrigCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT32  TAF_APS_SndSetDialModeCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          enCause
);

VOS_UINT32  TAF_APS_SndGetCgmtuValueCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulMtuValue
);

VOS_UINT32  TAF_APS_SndCgmtuValueChangeInd(
    VOS_UINT32                          ulMtuValue
);

VOS_UINT32  TAF_APS_SndGetGprsActiveTypeCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_CID_GPRS_ACTIVE_TYPE_STRU      *pstCidGprsActiveType
);

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID TAF_APS_SndIpv6RaInfoNotifyInd(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU           *pstIpv6RaInfo
);
#endif

VOS_UINT32 TAF_APS_ValidatePdpForSnStatusReq(
    VOS_UINT8                           ucPdpId,
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_FillCallEvtPdpAvtivateIndFromEsm(
    TAF_PS_CALL_PDP_MANAGE_IND_STRU    *pstCallEvt,
    APP_ESM_PDP_MANAGER_IND_STRU       *pstEsmPdpManageInd
);
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_FillEvtPdpType
 功能描述  : 填写PS域呼叫事件的PDP类型
 输入参数  : pstCallEvtInfo - PS域呼叫事件
             ucPdpId        - 实体索引
 输出参数  : penPdpType
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID TAF_APS_FillEvtPdpType(
    TAF_PDP_TYPE_ENUM_UINT8            *penPdpType,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);



/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)


VOS_VOID    Aps_DefPsPdprofmod (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PDP_PROFILE_EXT_STRU           *pPara,
    VOS_UINT32                         *pulErrCode
);


#endif
/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

VOS_VOID TAF_APS_RcvSetCidPara_PdpActLimit(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);
VOS_VOID TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU    *pstSetPdpCtxInfoReq
);

/* Deleted by wx270776 for OM融合, 2015-7-1, begin */

/* Deleted by wx270776 for OM融合, 2015-7-1, end */

/*****************************************************************************
 函 数 名  : TAF_APS_SndDsFlowOMRptInd
 功能描述  : 将流量信息通过消息ID_NAS_OM_DSFLOW_RPT_IND主动上报到OM
 输入参数  : pstDsFlowRptInfo   --流量信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增

*****************************************************************************/
VOS_VOID TAF_APS_SndDsFlowOMRptInd(
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
);

VOS_UINT8 TAF_APS_FindCidForAns(VOS_VOID);

VOS_VOID TAF_APS_MakeIpTypeAnsExtActReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
);

VOS_UINT32 TAF_APS_GetPdpCidQosPara(
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara,
    VOS_UINT8                           ucCid
);
VOS_UINT32 TAF_APS_SetPdpCidQosPara(
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
);


/*****************************************************************************
 函 数 名  : TAF_APS_GetSdfParaInfo
 功能描述  : 获取所有NV的SDF参数
 输入参数  : ucCid                      - CID
 输出参数  : pstSdfParaInfo             - CID对应的SDF参数
 返 回 值  : VOS_OK                     - CID对应的SDF参数有效, 获取成功
             VOS_ERR                    - CID对应的SDF参数无效, 获取失败
*****************************************************************************/
VOS_UINT32 TAF_APS_GetSdfParaInfo(
    VOS_UINT8                           ucCid,
    TAF_SDF_PARA_STRU                  *pstSdfParaInfo
);

VOS_VOID  Aps_MakeAnsActReq (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
);


#if(FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatusCommFun(
    VOS_UINT8                           ucPdpId
);
#endif


/*****************************************************************************
 函 数 名  : TAF_APS_ConvertLocalPdpTab2NvPdpTab
 功能描述  : LOCAL PDP表结构转换成NV PDP表结构
 输入参数  : pstLocalPdpTab --- LOCAL PDP TABLE
 输出参数  : pstNvPdpTab    --- NV PDP TABLE
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_ConvertLocalPdpTab2NvPdpTab(
    CONST TAF_PDP_TABLE_STRU           *pstLocalPdpTab,
    TAF_NV_PDP_TABLE_STRU              *pstNvPdpTab
);

/*****************************************************************************
 函 数 名  : TAF_APS_ConvertNvPdpTab2LocalPdpTab
 功能描述  : NV PDPPDP表结构转换成LOCAL PDP表结构
 输入参数  : pstNvPdpTab    --- NV PDP TABLE
 输出参数  : pstLocalPdpTab --- LOCAL PDP TABLE
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_ConvertNvPdpTab2LocalPdpTab(
    CONST TAF_NV_PDP_TABLE_STRU        *pstNvPdpTab,
    TAF_PDP_TABLE_STRU                 *pstLocalPdpTab
);

/* Added by m00217266 for L-C互操作项目, 2014-2-12, begin */
VOS_UINT32  TAF_APS_SndSetUmtsQosInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
);

VOS_UINT32  TAF_APS_SndSetUmtsQosMinInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
);
/* Added by m00217266 for L-C互操作项目, 2014-2-12, end */

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_SetEvtTftInfo(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TFT_STRU                   *pstTft
);
#endif


VOS_VOID TAF_APS_SndStkPsCallEvent(VOS_VOID);

#if 0
VOS_VOID TAF_APS_ProcUsimMsg(
    struct MsgCB                       *pstMsg
);
#endif

VOS_VOID TAF_APS_GprsDataReq(VOS_UINT8 ucMode, VOS_UINT8 ucNsapi, VOS_UINT32 ulLen, VOS_UINT8 ucTimes, VOS_UINT32 ulMillSecs);


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

#endif /* end of Taf_Aps.h*/
