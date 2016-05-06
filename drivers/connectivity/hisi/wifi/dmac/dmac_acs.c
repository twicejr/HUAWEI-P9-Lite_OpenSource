/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_acs.c
  版 本 号   : 初稿
  作    者   : wangshanbo
  生成日期   : 2013年12月10日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月10日
    作    者   : wangshanbo
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_SUPPORT_ACS

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_regdomain.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "mac_frame.h"
#include "dmac_main.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_alg_if.h"
#include "dmac_scan.h"
#include "dmac_acs.h"
#if defined(_PRE_WLAN_CHIP_TEST)
#include "dmac_acs_test.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ACS_C

//#define _PRE_SUPPORT_DYNA_ACS

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/***********************************************************
    device级acs结构体
***********************************************************/
OAL_STATIC dmac_acs_stru g_ast_acs[MAC_RES_MAX_DEV_NUM];


OAL_STATIC dmac_acs_vap_internal_stru*  dmac_acs_add_vap(mac_vap_stru *pst_vap);
OAL_STATIC oal_void  dmac_acs_del_vap(mac_vap_stru *pst_vap);
OAL_STATIC dmac_acs_user_internal_stru* dmac_acs_add_user(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
OAL_STATIC oal_void  dmac_acs_del_user(mac_vap_stru *pst_vap, mac_user_stru *pst_user);
OAL_STATIC dmac_acs_vap_internal_stru*  dmac_acs_find_internal_vap(dmac_acs_stru *pst_acs, oal_uint8  uc_vap_id);
OAL_STATIC dmac_acs_user_internal_stru* dmac_acs_find_internal_user(dmac_acs_stru *pst_acs, oal_uint8  uc_vap_id, oal_uint16 us_assoc_id);

oal_uint8 g_auc_ack_time[WLAN_PROTOCOL_BUTT] = {40, 208, 40, 40, 40, 32, 32, 32, 32};
const char *g_acs_cmd_type[] =
{
    "set_best_channel",
    "get_vap_perf_info",
    "get_avail_channel",
    "get_net_info",
    "do_offchan_cac",
    "do_scan",
    "do_csa",
    "do_duration_stats",
    "do_butt",
    "create_vap",
    "delete_vap",
    "add_user",
    "del_user",
    "cfg_channel",
    "cfg_bandwidth",
    "radar_detected",
};
#ifdef _PRE_SUPPORT_DYNA_ACS
static dmac_acs_rate_table_stru g_ast_11n_table[36] = {
     /*              Valid         Nss                   bandwidth                  mcs               rate    theory      max        protocol          20M     40M  */
     /*              for                                                                                      rate        aggr       mode              rate    rate */
     /*              short GI                                                                                 num                                      code    code */
     /*  6.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS0},     6500,      0,       3220,      WLAN_HT_MODE,       0,      18},
     /*   13 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS1},     13000,     0,       6440,      WLAN_HT_MODE,       1,      19},
     /* 19.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS2},     19500,     0,       9660,      WLAN_HT_MODE,       2,      20},
     /*   26 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS3},     26000,     0,      12880,      WLAN_HT_MODE,       3,      21},
     /*   39 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS4},     39000,     0,      19320,      WLAN_HT_MODE,       4,      22},
     /*   52 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS5},     52000,     0,      25760,      WLAN_HT_MODE,       5,      23},
     /* 58.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS6},     58500,     0,      28980,      WLAN_HT_MODE,       6,      24},
     /*   65 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS7},     65000,     0,      32200,      WLAN_HT_MODE,       7,      25},
     /* 72.2 Mb */ { OAL_TRUE,     WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS7},     72200,     0,      35760,      WLAN_HT_MODE,       8,      26},
     /*   13 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS8},     13000,     0,       6640,      WLAN_HT_MODE,       9,      27},
     /*   26 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS9},     26000,     0,      12870,      WLAN_HT_MODE,      10,      28},
     /*   39 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS10},    39000,     0,      19300,      WLAN_HT_MODE,      11,      29},
     /*   52 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS11},    52000,     0,      25740,      WLAN_HT_MODE,      12,      30},
     /*   78 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS12},    78000,     0,      38610,      WLAN_HT_MODE,      13,      31},
     /*  104 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS13},   104000,     0,      51480,      WLAN_HT_MODE,      14,      32},
     /*  117 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS14},   117000,     0,      57910,      WLAN_HT_MODE,      15,      33},
     /*  130 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS15},   130000,     0,      64350,      WLAN_HT_MODE,      16,      34},
     /*144.4 Mb */ { OAL_TRUE,     WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,   {WLAN_HT_MCS15},   144400,     0,      71470,      WLAN_HT_MODE,      17,      35},
     /* 13.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS0},     13500,     0,       6680,      WLAN_HT_MODE,       0,      18},
     /*   27 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS1},     27000,     0,      13370,      WLAN_HT_MODE,       1,      19},
     /* 40.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS2},     40500,     0,      20060,      WLAN_HT_MODE,       2,      20},
     /*   54 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS3},     54000,     0,      26750,      WLAN_HT_MODE,       3,      21},
     /*   81 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS4},     81000,     0,      40130,      WLAN_HT_MODE,       4,      22},
     /*  108 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS5},    108000,     0,      53510,      WLAN_HT_MODE,       5,      23},
     /*121.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS6},    121500,     0,      60200,      WLAN_HT_MODE,       6,      24},
     /*  135 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS7},    135000,     0,      66890,      WLAN_HT_MODE,       7,      25},
     /* 150  Mb */ { OAL_TRUE,     WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS7},    150000,     0,      74300,      WLAN_HT_MODE,       8,      26},
     /*   27 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS8},     27000,     0,      13370,      WLAN_HT_MODE,       9,      27},
     /*   54 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS9},     54000,     0,      26730,      WLAN_HT_MODE,      10,      28},
     /*   81 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS10},    81000,     0,      40090,      WLAN_HT_MODE,      11,      29},
     /*  108 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS11},   108000,     0,      53460,      WLAN_HT_MODE,      12,      30},
     /*  162 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS12},   162000,     0,      80190,      WLAN_HT_MODE,      13,      31},
     /*  216 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS13},   216000,     0,     106920,      WLAN_HT_MODE,      14,      32},
     /*  243 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS14},   243000,     0,     120280,      WLAN_HT_MODE,      15,      33},
     /*  270 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS15},   270000,     0,     133650,      WLAN_HT_MODE,      16,      34},
     /*  300 Mb */ { OAL_TRUE,     WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,   {WLAN_HT_MCS15},   300000,     0,     148500,      WLAN_HT_MODE,      17,      35},
};

static dmac_acs_rate_table_stru g_ast_11ac_table[64] = {
     /*              Valid         Nss                   bandwidth                 mcs                  rate      theory    max       protocol          20M     40M     80M   */
     /*              for                                                                                          rate      aggr      mode              rate    rate    rate  */
     /*              short GI                                                                                     num                                   code    code    code */
     /*  6.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS0},      6500,      0,       3220,     WLAN_VHT_MODE,      0,      20,     42},
     /*   13 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS1},      13000,     0,       6440,     WLAN_VHT_MODE,      1,      21,     43},
     /* 19.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS2},      19500,     0,       9660,     WLAN_VHT_MODE,      2,      22,     44},
     /*   26 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS3},      26000,     0,      12880,     WLAN_VHT_MODE,      3,      23,     45},
     /*   39 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS4},      39000,     0,      19320,     WLAN_VHT_MODE,      4,      24,     46},
     /*   52 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS5},      52000,     0,      25760,     WLAN_VHT_MODE,      5,      25,     47},
     /* 58.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS6},      58500,     0,      28980,     WLAN_VHT_MODE,      6,      26,     48},
     /*   65 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS7},      65000,     0,      32200,     WLAN_VHT_MODE,      7,      27,     49},
     /*   78 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS8},      78000,     0,      38640,     WLAN_VHT_MODE,      8,      28,     50},
     /* 86.7 Mb */ { OAL_TRUE,     WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS8},      86700,     0,      49240,     WLAN_VHT_MODE,      9,    0xff,   0xff},
     /*   13 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS0},      13000,     0,       6640,     WLAN_VHT_MODE,     10,      31,     53},
     /*   26 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS1},      26000,     0,      12870,     WLAN_VHT_MODE,     11,      32,     54},
     /*   39 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS2},      39000,     0,      19300,     WLAN_VHT_MODE,     12,      33,     55},
     /*   52 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS3},      52000,     0,      25740,     WLAN_VHT_MODE,     13,      34,     56},
     /*   78 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS4},      78000,     0,      38610,     WLAN_VHT_MODE,     14,      35,     57},
     /*  104 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS5},     104000,     0,      51480,     WLAN_VHT_MODE,     15,      36,     58},
     /*  117 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS6},     117000,     0,      57910,     WLAN_VHT_MODE,     16,      37,     59},
     /*  130 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS7},     130000,     0,      64350,     WLAN_VHT_MODE,     17,      38,     60},
     /*  156 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS8},     156000,     0,      77220,     WLAN_VHT_MODE,     18,      39,     61},
     /*173.3 Mb */ { OAL_TRUE,     WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_20M,  {WLAN_VHT_MCS8},     173300,     0,      85780,     WLAN_VHT_MODE,     19,    0xff,   0xff},
     /* 13.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS0},      13500,     0,       6680,     WLAN_VHT_MODE,      0,      20,     42},
     /*   27 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS1},      27000,     0,      13370,     WLAN_VHT_MODE,      1,      21,     43},
     /* 40.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS2},      40500,     0,      20060,     WLAN_VHT_MODE,      2,      22,     44},
     /*   54 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS3},      54000,     0,      26750,     WLAN_VHT_MODE,      3,      23,     45},
     /*   81 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS4},      81000,     0,      40130,     WLAN_VHT_MODE,      4,      24,     46},
     /*  108 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS5},     108000,     0,      53510,     WLAN_VHT_MODE,      5,      25,     47},
     /*121.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS6},     121500,     0,      60200,     WLAN_VHT_MODE,      6,      26,     48},
     /*  135 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS7},     135000,     0,      66890,     WLAN_VHT_MODE,      7,      27,     49},
     /*  162 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS8},     162000,     0,      80270,     WLAN_VHT_MODE,      8,      28,     50},
     /*  180 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS9},     180000,     0,      89190,     WLAN_VHT_MODE,   0xff,      29,     51},
     /*  200 Mb */ { OAL_TRUE,     WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS9},     200000,     0,      99074,     WLAN_VHT_MODE,   0xff,      30,     52},
     /*   27 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS0},      27000,     0,      13370,     WLAN_VHT_MODE,     10,      31,     53},
     /*   54 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS1},      54000,     0,      26730,     WLAN_VHT_MODE,     11,      32,     54},
     /*   81 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS2},      81000,     0,      40090,     WLAN_VHT_MODE,     12,      33,     55},
     /*  108 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS3},     108000,     0,      53460,     WLAN_VHT_MODE,     13,      34,     56},
     /*  162 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS4},     162000,     0,      80190,     WLAN_VHT_MODE,     14,      35,     57},
     /*  216 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS5},     216000,     0,     106920,     WLAN_VHT_MODE,     15,      36,     58},
     /*  243 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS6},     243000,     0,     120280,     WLAN_VHT_MODE,     16,      37,     59},
     /*  270 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS7},     270000,     0,     133650,     WLAN_VHT_MODE,     17,      38,     60},
     /*  324 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS8},     324000,     0,     160540,     WLAN_VHT_MODE,     18,      39,     61},
     /*  360 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS9},     360000,     0,     178200,     WLAN_VHT_MODE,   0xff,      40,     62},
     /*  400 Mb */ { OAL_TRUE,     WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_40M,  {WLAN_VHT_MCS9},     400000,     0,     198000,     WLAN_VHT_MODE,   0xff,      41,     63},
     /* 29.3 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS0},      29300,     0,      14510,     WLAN_VHT_MODE,      0,      20,     42},
     /* 58.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS1},      58500,     0,      28980,     WLAN_VHT_MODE,      1,      21,     43},
     /* 87.8 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS2},      87800,     0,      43500,     WLAN_VHT_MODE,      2,      22,     44},
     /*  117 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS3},     117000,     0,      57970,     WLAN_VHT_MODE,      3,      23,     45},
     /*175.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS4},     175500,     0,      86960,     WLAN_VHT_MODE,      4,      24,     46},
     /*  234 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS5},     234000,     0,     115940,     WLAN_VHT_MODE,      5,      25,     47},
     /*263.3 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS6},     263300,     0,     130460,     WLAN_VHT_MODE,      6,      26,     48},
     /*292.5 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS7},     292500,     0,     144930,     WLAN_VHT_MODE,      7,      27,     49},
     /*  351 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS8},     351000,     0,     173920,     WLAN_VHT_MODE,      8,      28,     50},
     /*  390 Mb */ { OAL_FALSE,    WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS9},     390000,     0,     193240,     WLAN_VHT_MODE,      9,      29,     51},
     /*433.3 Mb */ { OAL_TRUE,     WLAN_SINGLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS9},     433300,     0,     214640,     WLAN_VHT_MODE,     10,      30,     52},
     /* 58.5 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS0},      58500,     0,      28980,     WLAN_VHT_MODE,     11,      31,     53},
     /*  117 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS1},     117000,     0,      57910,     WLAN_VHT_MODE,     12,      32,     54},
     /*175.5 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS2},     175500,     0,      86870,     WLAN_VHT_MODE,     13,      33,     55},
     /*  234 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS3},     234000,     0,     115830,     WLAN_VHT_MODE,     14,      34,     56},
     /*  351 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS4},     351000,     0,     173740,     WLAN_VHT_MODE,     15,      35,     57},
     /*  468 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS5},     468000,     0,     231660,     WLAN_VHT_MODE,     16,      36,     58},
     /*526.5 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS6},     526500,     0,     260610,     WLAN_VHT_MODE,     17,      37,     59},
     /*  585 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS7},     585000,     0,     289570,     WLAN_VHT_MODE,     18,      38,     60},
     /*  702 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS8},     702000,     0,     347490,     WLAN_VHT_MODE,     19,      39,     61},
     /*  780 Mb */ { OAL_FALSE,    WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS9},     780000,     0,     386100,     WLAN_VHT_MODE,   0xff,      40,     62},
     /*866.7 Mb */ { OAL_TRUE,     WLAN_DOUBLE_NSS,      WLAN_BAND_ASSEMBLE_80M,  {WLAN_VHT_MCS9},     866700,     0,     429010,     WLAN_VHT_MODE,   0xff,      41,     63},
};
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_acs_skip_notify
 功能描述  : 判断是否跳过给定的VAP上的信道/带宽改变事件
 输入参数  : mac_vap_stru *pst_mac_vap
 输出参数  : 无
 返 回 值  : oal_bool_enum_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月29日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_acs_skip_notify(mac_vap_stru *pst_mac_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
#if 0
    mac_device_stru *pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    oal_bool_enum_uint8    en_in_scan = OAL_FALSE;

    if (OAL_PTR_NULL != pst_mac_dev && MAC_SCAN_STATE_RUNNING == pst_mac_dev->en_curr_scan_state)
    {
        en_in_scan =  OAL_TRUE;
    }

    OAL_IO_PRINT("in scan=%d vap state=%d en=%d\n", pst_mac_dev->en_curr_scan_state,
            pst_mac_vap->en_vap_state, en_in_scan);
    /* 不启动hostapd时，VAP在WAIT START状态下扫描 */
    /* 启动hostapd时，VAP在UP状态下扫描 */
    if ( (en_in_scan && pst_mac_vap->en_vap_state == MAC_VAP_STATE_AP_WAIT_START)
      || (!en_in_scan && pst_mac_vap->en_vap_state == MAC_VAP_STATE_UP))
    {
        return OAL_TRUE;
    }
#endif

    if (en_type != CH_BW_CHG_TYPE_MOVE_WORK)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
/*****************************************************************************
 函 数 名  : dmac_acs_setup_vap_info
 功能描述  : 设置VAP信息
 输入参数  : dmac_acs_vap_info_stru *pst_info
             mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月23日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_acs_setup_vap_info(dmac_acs_vap_info_stru *pst_info, mac_vap_stru *pst_vap)
{
    oal_memcopy(pst_info->auc_bssid, pst_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_info->en_vap_mode       = pst_vap->en_vap_mode;
    pst_info->uc_vap_id         = pst_vap->uc_vap_id;
    pst_info->en_protocol       = pst_vap->en_protocol;
    pst_info->en_bandwidth      = pst_vap->st_channel.en_bandwidth;
    pst_info->uc_channel        = pst_vap->st_channel.uc_chan_number;
    pst_info->en_bandwidth_cap  = pst_vap->st_channel.en_bandwidth; // VAP带宽不会改变，初始带宽即为最大带宽
}

/*****************************************************************************
 函 数 名  : dmac_acs_setup_user_info
 功能描述  : 设置USER信息
 输入参数  : dmac_acs_user_info_stru *pst_info
             mac_vap_stru *pst_vap
             mac_user_stru *pst_user
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月23日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_acs_setup_user_info(dmac_acs_user_info_stru *pst_info, mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_user_stru  *pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);;

    if(OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ACS, "dmac_acs_setup_user_info:get dmac_user failed, assoc_id=%d", pst_user->us_assoc_id);
        return;
    }

    oal_memcopy(pst_info->auc_user_mac_addr, pst_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
    pst_info->us_assoc_id          = pst_user->us_assoc_id;
    pst_info->uc_assoc_vap_id      = pst_user->uc_vap_id;
    pst_info->en_cur_bandwidth     = pst_user->en_cur_bandwidth;
    pst_info->en_cur_protocol_mode = pst_user->en_cur_protocol_mode;
    pst_info->bit_bandwidth_cap    = pst_user->en_bandwidth_cap;
    pst_info->bit_spectrum_mgmt    = (oal_uint8)pst_user->st_cap_info.bit_spectrum_mgmt;
    pst_info->c_rx_rssi            = pst_dmac_user->c_rx_rssi;
}

/*****************************************************************************
 函 数 名  : dmac_acs_reply_ex
 功能描述  : 回复APP层的请求,有额外数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月16日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_reply_ex(oal_uint8 uc_chip_id, oal_uint8 uc_device_id,
                            dmac_acs_cmd_enum_uint8 en_cmd, oal_uint32 ul_cmd_id,
                            oal_uint8 *puc_buffer, oal_uint32 ul_len)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    mac_acs_response_hdr_stru  *pst_msg_hdr;
    oal_uint32                  ul_size = OAL_SIZEOF(mac_acs_response_hdr_stru) + ul_len;
    mac_device_stru            *pst_mac_device;

    pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ACS, "{dmac_acs_reply_ex:device = null}");
        return OAL_FAIL;
    }

    if (mac_get_acs_switch(pst_mac_device) ==  MAC_ACS_SW_NONE)
    {
        return OAL_SUCC;
    }


    /* 抛扫描请求事件到HMAC/WAL, 申请事件内存 */
    /* 该内存在HMAC和WAL复用，只在本函数最后释放一次 */
    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)ul_size);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{dmac_acs_sendup_event_ex::alloc failed, size=%d}", ul_size);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 填写事件 */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       DMAC_WLAN_CRX_EVENT_SUB_TYPE_ACS_RESP,
                       (oal_uint16)ul_size,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       uc_chip_id,
                       uc_device_id,
                       0);

    pst_msg_hdr = (mac_acs_response_hdr_stru *)pst_event->auc_event_data;

    pst_msg_hdr->uc_cmd       = en_cmd;
    pst_msg_hdr->uc_chip_id   = uc_chip_id;
    pst_msg_hdr->uc_device_id = uc_device_id;
    pst_msg_hdr->ul_len       = ul_size;
    pst_msg_hdr->ul_cmd_cnt   = ul_cmd_id;

    oal_memcopy(pst_msg_hdr + 1, puc_buffer, ul_len);

    OAL_IO_PRINT("<<< rsp %d:%s\n", en_cmd, g_acs_cmd_type[en_cmd]);

    /* 分发事件 */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_acs_clear_stats
 功能描述  : 为信道统计做初始化准备
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月9日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_clear_stats(dmac_acs_stru *pst_acs)
{
    oal_dlist_head_stru         *pst_dlist_pos1, *pst_dlist_pos2;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;

    pst_acs->ul_mac_free_time_us  = 0;
    pst_acs->ul_mac_stats_time_us = 0;
    pst_acs->ul_phy_free_power    = 0;

    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos1, &pst_acs->st_vap_dlist_head)
    {
        pst_vap_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos1, dmac_acs_vap_internal_stru, st_dlist_head);
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos2, &pst_vap_internal->st_user_dlist_head)
        {
            pst_user_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos2, dmac_acs_user_internal_stru, st_dlist_head);
            pst_user_internal->ul_rx_duration_us = 0;
            pst_user_internal->ul_tx_duration_us = 0;
            pst_user_internal->ul_tx_pkt_bytes   = 0;
            pst_user_internal->ul_tx_pkt_cnt     = 0;
            pst_user_internal->ul_rx_pkt_bytes   = 0;
            pst_user_internal->ul_rx_pkt_cnt     = 0;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_vap_perf
 功能描述  : 搜集指定VAP的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月23日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_acs_do_vap_perf(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
    mac_vap_stru                     *pst_mac_vap;
    mac_user_stru                    *pst_mac_user;
    dmac_user_stru                   *pst_dmac_user;
    oal_dlist_head_stru              *pst_entry;
    dmac_tid_stru                    *pst_tid_queue;
    hal_tx_dscr_stru                 *pst_dscr;
    oal_netbuf_stru                  *pst_net_buf;
    mac_tx_ctl_stru                  *pst_tx_ctrl;
    oal_time_us_stru                  st_time;
    oal_uint8                         uc_index;
    oal_uint8                         uc_csa_sta_num;
    oal_uint32                        ul_mpdu_num;
    oal_uint32                        ul_time_delta_us;
    oal_uint16                        us_len;
    dmac_acs_vap_perf_reply_stru     *pst_acs_vap_info;
    oal_dlist_head_stru              *pst_dlist_pos;
    dmac_acs_stru                    *pst_acs;
    dmac_acs_vap_internal_stru       *pst_vap_internal;
    dmac_acs_user_internal_stru      *pst_user_internal;
    acs_vap_perf_user_stat_stru      *pst_stat;

    /***********************************************************************************/
    /********************************VAP PERF 报文格式**********************************/
    /*---------------------------------------------------------------------------------*/
    /*|VAP perf stru|ACS duration|User1 addr|User1 assoc_id|User1 duration|...|User N| */
    /*---------------------------------------------------------------------------------*/
    pst_acs = (dmac_acs_stru *)p_acs;
    pst_acs->en_in_stats = OAL_FALSE;
    pst_mac_vap          = (mac_vap_stru *)mac_res_get_mac_vap(pst_cmd->auc_arg[0]);
    pst_vap_internal     = dmac_acs_find_internal_vap(pst_acs, pst_cmd->auc_arg[0]);
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_vap_internal))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "{dmac_acs_do_vap_perf::null param.}");

        return;
    }

    us_len = (oal_uint16)(OAL_SIZEOF(dmac_acs_vap_perf_reply_stru)
                         + pst_mac_vap->us_user_nums * OAL_SIZEOF(acs_vap_perf_user_stat_stru));
    pst_acs_vap_info = (dmac_acs_vap_perf_reply_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, us_len, OAL_TRUE);
    if (OAL_PTR_NULL == pst_acs_vap_info)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ACS, "{dmac_acs_do_vap_perf::alloc memory failed, size=%d}", us_len);
        return;
    }
    OAL_MEMZERO(pst_acs_vap_info, us_len);

    if (0 == pst_mac_vap->us_user_nums)
    {
        pst_acs_vap_info->uc_vap_id = pst_mac_vap->uc_vap_id;

        dmac_acs_reply_ex(pst_mac_dev->uc_chip_id, pst_mac_dev->uc_device_id, DMAC_ACS_CMD_GET_VAP_PERF_INFO, pst_cmd->ul_cmd_cnt, (oal_uint8 *)pst_acs_vap_info, OAL_SIZEOF(dmac_acs_vap_perf_reply_stru));

        OAL_MEM_FREE(pst_acs_vap_info, OAL_TRUE);

        return;
    }

    /* 开始统计MPDU个数，TID时延，CSA STA个数 */
    ul_mpdu_num    = 0;
    uc_csa_sta_num = 0;

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_mac_user  = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
        {
            OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_acs_do_vap_perf::null pointer,pst_dmac_user[%d].}", pst_mac_user->us_assoc_id);
            continue;
        }

        pst_user_internal = dmac_acs_find_internal_user(pst_acs, pst_mac_vap->uc_vap_id, pst_mac_user->us_assoc_id);
        if (OAL_PTR_NULL != pst_user_internal)
        {
            pst_user_internal->c_rx_rssi = pst_dmac_user->c_rx_rssi;
        }

        /* 忽略组播用户 */
        if (OAL_TRUE == pst_mac_user->en_is_multi_user)
        {
            continue;
        }

        /* 记录CSA USER个数 */
        uc_csa_sta_num += pst_mac_user->st_cap_info.bit_spectrum_mgmt;

        /* 遍历该USER的所有TID，计算TID最大时延 */
        for (uc_index = 0; uc_index < WLAN_TID_MAX_NUM; uc_index++)
        {
            pst_tid_queue = &pst_dmac_user->ast_tx_tid_queue[uc_index];

        #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
            if (OAL_TRUE != oal_dlist_is_empty(&pst_tid_queue->st_retry_q))
            {
                 /* 获得TID中第一个NETBUF */
                pst_dlist_pos = pst_tid_queue->st_retry_q.pst_next;
                pst_dscr      = OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                pst_net_buf   = pst_dscr->pst_skb_start_addr;
            }
            else if (OAL_TRUE != oal_netbuf_list_empty(&pst_tid_queue->st_buff_head))
            {
                pst_net_buf = pst_tid_queue->st_buff_head.pst_next;
            }
            else
            {
                continue;
            }
        #else
            if (OAL_TRUE == oal_dlist_is_empty(&pst_tid_queue->st_hdr))
            {
                continue;
            }

             /* 获得TID中第一个NETBUF */
            pst_dlist_pos = pst_tid_queue->st_hdr.pst_next;
            pst_dscr      = OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            pst_net_buf   = pst_dscr->pst_skb_start_addr;
        #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
            ul_mpdu_num += pst_tid_queue->us_mpdu_num;

            /* 获取netbuf对应的CB字段 */
            pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
            oal_time_get_stamp_us(&st_time);

            /* 计算延迟 */
            ul_time_delta_us = (oal_uint32)((((oal_int64)st_time.i_sec * 1000000) + st_time.i_usec) - (((oal_int64)pst_tx_ctrl->st_timestamp_us.i_sec * 1000000) + pst_tx_ctrl->st_timestamp_us.i_usec));

            if ((ul_time_delta_us >> 10) > pst_acs_vap_info->aus_max_delay[uc_index])
            {
                pst_acs_vap_info->aus_max_delay[uc_index] = (oal_uint16)(ul_time_delta_us >> 10);
            }
        }
    }

    pst_acs_vap_info->uc_vap_id      = pst_mac_vap->uc_vap_id;
    pst_acs_vap_info->uc_csa_sta_num = uc_csa_sta_num;
    pst_acs_vap_info->ul_mpdu_num    = ul_mpdu_num;
    pst_acs_vap_info->us_sta_nums    = pst_mac_vap->us_user_nums;

    /* TBD赋值全局的TX/RX DURATION记录 */ // TODO
    pst_acs_vap_info->uc_mac_free_time_rate = 0; // pst_acs->ul_mac_free_time_us;
    pst_acs_vap_info->us_mac_stats_time_ms  = 0;// pst_acs->ul_mac_stats_time_us;
    pst_acs_vap_info->c_phy_free_power      = 0; // pst_acs->ul_phy_free_power;

    pst_stat = (acs_vap_perf_user_stat_stru *)(pst_acs_vap_info + 1);

    /* 加入VAP下所有USER的TX/RX DURATION */
    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_vap_internal->st_user_dlist_head)
    {
        pst_user_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_acs_user_internal_stru, st_dlist_head);
        /* 复制STA 的MAC地址以及ASSOC ID 8-bytes */
        oal_memcopy(pst_stat->auc_user_addr, pst_user_internal->auc_user_addr, WLAN_MAC_ADDR_LEN);
        pst_stat->us_assoc_id = pst_user_internal->us_assoc_id;
        pst_stat->c_rx_rssi   = pst_user_internal->c_rx_rssi;
        // TODO: update
        pst_stat->uc_tx_duration_rate = 0; //pst_user_internal->ul_tx_duration_us;
        pst_stat->uc_rx_duration_rate = 0;// pst_user_internal->ul_rx_duration_us;
        pst_stat->ul_tx_pkt_bytes   = pst_user_internal->ul_tx_pkt_bytes;
        pst_stat->ul_tx_pkt_cnt     = pst_user_internal->ul_tx_pkt_cnt;
        pst_stat->ul_rx_pkt_bytes   = pst_user_internal->ul_rx_pkt_bytes;
        pst_stat->ul_rx_pkt_cnt     = pst_user_internal->ul_rx_pkt_cnt;
        pst_stat++;
    }

    dmac_acs_reply_ex(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, DMAC_ACS_CMD_GET_VAP_PERF_INFO, pst_cmd->ul_cmd_cnt, (oal_uint8 *)pst_acs_vap_info, us_len);

    OAL_MEM_FREE(pst_acs_vap_info, OAL_TRUE);

    return;
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_csa
 功能描述  : 通过指定VAP发送CSA帧或指定USER发送带宽改变帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月14日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_csa(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_acs_cmd)
{
    dmac_vap_stru               *pst_dmac_vap;
    dmac_acs_vap_internal_stru  *pst_vap_int;
    mac_vap_stru                *pst_mac_vap;
    dmac_acs_csa_stru           *pst_csa_info;
    dmac_acs_stru               *pst_acs;
    oal_uint32                   ul_ret;

    /* ARG0 保存需要进行信道切换的VAP ID */
    pst_acs     = (dmac_acs_stru *)p_acs;
    pst_mac_vap = mac_res_get_mac_vap(pst_acs_cmd->auc_arg[0]);
    pst_vap_int = dmac_acs_find_internal_vap(pst_acs, pst_acs_cmd->auc_arg[0]);
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_vap_int))
    {
        return;
    }

    /* 从pst_acs_cmd中解析命令 */
    pst_csa_info = (dmac_acs_csa_stru *)pst_acs_cmd->auc_data;

    /* 发送信道迁移CSA ACTION帧 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "{dmac_acs_scan_cb::pst_dmac_vap null.}");
        return;
    }

    ul_ret = dmac_mgmt_send_csa_action(pst_dmac_vap, pst_csa_info->uc_channel_num, pst_csa_info->uc_tbtt_cnt, pst_csa_info->uc_bandwidth);
    if (OAL_SUCC == ul_ret)
    {
        pst_vap_int->en_dfs_wait_for_csa_sent = OAL_TRUE;
        pst_vap_int->en_in_csa_phase          = OAL_FALSE;
        pst_vap_int->ast_best_channel_per_band[pst_csa_info->uc_band].en_bandwidth      = pst_csa_info->uc_bandwidth;
        pst_vap_int->ast_best_channel_per_band[pst_csa_info->uc_band].en_valid          = OAL_TRUE;
        pst_vap_int->ast_best_channel_per_band[pst_csa_info->uc_band].uc_channel_number = pst_csa_info->uc_channel_num;
        pst_vap_int->auc_tbtt_cnt[pst_csa_info->uc_band] = pst_csa_info->uc_tbtt_cnt;
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_avl_channel
 功能描述  : 回复可用信道列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_avl_channel(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
    oal_uint8   auc_buf[OAL_SIZEOF(dmac_acs_avail_channel_reply_stru) + WLAN_MAX_CHANNEL_NUM * OAL_SIZEOF(dmac_acs_channel_stru)];

    dmac_acs_avail_channel_reply_stru *pst_avail_channel = (dmac_acs_avail_channel_reply_stru *)auc_buf;
    dmac_acs_channel_stru             *pst_chan = (dmac_acs_channel_stru *)(pst_avail_channel + 1);
    dmac_acs_stru                     *pst_acs;

	oal_uint8                         uc_tot;
	oal_uint8                         uc_idx;
	oal_uint8                         uc_chan_num;

    pst_acs = (dmac_acs_stru *)p_acs;
    OAL_MEMZERO(pst_avail_channel, OAL_SIZEOF(dmac_acs_avail_channel_reply_stru));
    pst_avail_channel->uc_chip_id           = pst_acs->uc_chip_id;
    pst_avail_channel->uc_device_id         = pst_acs->uc_device_id;

    uc_tot = 0;
    for (uc_idx = 0; uc_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_idx++)
    {
        if(OAL_SUCC == mac_is_channel_idx_valid(WLAN_BAND_2G, uc_idx))
        {
            mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_idx, &uc_chan_num);
            pst_chan->en_valid     = OAL_TRUE;
            pst_chan->en_bandwidth = WLAN_BAND_WIDTH_20M;
            pst_chan->uc_channel_number = uc_chan_num;
            pst_chan++;
            uc_tot++;
        }
    }
    for (uc_idx = 0; uc_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_idx++)
    {
        if(OAL_SUCC == mac_is_channel_idx_valid(WLAN_BAND_5G, uc_idx))
        {
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_idx, &uc_chan_num);
            pst_chan->en_valid     = OAL_TRUE;
            pst_chan->en_bandwidth = WLAN_BAND_WIDTH_20M;
            pst_chan->uc_channel_number = uc_chan_num;
            pst_chan++;
            uc_tot++;
        }
    }

    pst_avail_channel->uc_avail_channel_num = uc_tot;

    dmac_acs_reply_ex(pst_mac_dev->uc_chip_id, pst_mac_dev->uc_device_id, DMAC_ACS_CMD_GET_AVAIL_CHANNEL, pst_cmd->ul_cmd_cnt, auc_buf, uc_tot * OAL_SIZEOF(dmac_acs_channel_stru) + OAL_SIZEOF(dmac_acs_avail_channel_reply_stru));
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_scan
 功能描述  : 接收并处理APP的扫描请求，并将扫描请求提交给DMAC SCAN模块
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_scan(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
#if 0
    oal_uint8                    uc_idx, uc_cnt;
    mac_scan_req_stru            st_scan_req;
    wlan_channel_band_enum_uint8 en_band;
    dmac_acs_stru               *pst_acs;

    if (pst_cmd->ul_cmd_len % 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{dmac_acs_do_scan:: invalid cmd_len[%d].}", pst_cmd->ul_cmd_len);
        return;
    }

    pst_acs = (dmac_acs_stru *)p_acs;
    OAL_MEMZERO(&st_scan_req, OAL_SIZEOF(st_scan_req));

    st_scan_req.ul_request_id = pst_cmd->ul_cmd_cnt;
    st_scan_req.en_scan_mode  = pst_cmd->auc_arg[0];
    st_scan_req.en_scan_type  = pst_cmd->auc_arg[1];
    st_scan_req.uc_scan_func  = pst_cmd->auc_arg[2];
    st_scan_req.p_fn_cb       = dmac_acs_scan_cb;
    if (st_scan_req.uc_scan_func & MAC_SCAN_FUNC_BSS)
    {
        st_scan_req.en_bss_type = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    }

    uc_cnt = 0;
    for (uc_idx = 0; uc_idx < pst_cmd->ul_cmd_len; uc_idx += 2)
    {
        en_band = pst_cmd->auc_data[uc_idx];
        if (OAL_TRUE != mac_is_channel_num_valid(en_band, pst_cmd->auc_data[uc_idx + 1]))
        {
            continue;
        }

        st_scan_req.ast_channel_list[uc_cnt++].uc_chan_number = pst_cmd->auc_data[uc_idx + 1];
    }

    if (uc_cnt != 0)
    {
        st_scan_req.uc_channel_nums = uc_cnt;
        dmac_scan_add_req(pst_mac_dev, &st_scan_req);
        pst_acs->en_in_scan = OAL_TRUE;
    }
#else
    return;
#endif
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_set_best_channel
 功能描述  : 设置最佳信道
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_set_best_channel(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
    dmac_acs_csa_stru           *pst_best_channel;
    dmac_acs_vap_internal_stru  *pst_vap_int;
    dmac_acs_stru               *pst_acs;

    pst_acs = (dmac_acs_stru *)p_acs;
    pst_best_channel = (dmac_acs_csa_stru *)pst_cmd->auc_data;
    if (OAL_TRUE == pst_best_channel->en_global)
    {
        pst_acs->ast_best_channel_per_band[pst_best_channel->uc_band].en_bandwidth      = pst_best_channel->uc_bandwidth;
        pst_acs->ast_best_channel_per_band[pst_best_channel->uc_band].en_valid          = OAL_TRUE;
        pst_acs->ast_best_channel_per_band[pst_best_channel->uc_band].uc_channel_number = pst_best_channel->uc_channel_num;
    }
    else
    {
        pst_vap_int = dmac_acs_find_internal_vap(pst_acs, pst_best_channel->uc_vap_id);
        if (OAL_PTR_NULL != pst_vap_int)
        {
            pst_vap_int->ast_best_channel_per_band[pst_best_channel->uc_band].en_bandwidth      = pst_best_channel->uc_bandwidth;
            pst_vap_int->ast_best_channel_per_band[pst_best_channel->uc_band].en_valid          = OAL_TRUE;
            pst_vap_int->ast_best_channel_per_band[pst_best_channel->uc_band].uc_channel_number = pst_best_channel->uc_channel_num;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_do_duration_stats
 功能描述  : 开始统计TX/RX DURATION
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月21日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_duration_stats(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
    dmac_acs_stru *pst_acs;

    pst_acs = (dmac_acs_stru *)p_acs;
    dmac_acs_clear_stats(pst_acs);
    pst_acs->en_in_stats = OAL_TRUE;
}
/*****************************************************************************
 函 数 名  : dmac_acs_do_get_net_info
 功能描述  : 获得当前的BSS分布信息
 输入参数  : mac_device_stru *pst_mac_dev
             oal_void *p_acs
             mac_acs_cmd_stru *pst_cmd
 输出参数  : 无
 返 回 值  : OAL_STATIC oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月23日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_do_get_net_info(mac_device_stru *pst_mac_dev, oal_void *p_acs, mac_acs_cmd_stru *pst_cmd)
{
    dmac_acs_stru *pst_acs = (dmac_acs_stru *)p_acs;
    dmac_acs_vap_internal_stru       *pst_vap_internal;
    dmac_acs_user_internal_stru      *pst_user_internal;
    oal_dlist_head_stru              *pst_vap_list, *pst_user_list;
    oal_uint8                         auc_buf[256]; // FIXME
    dmac_acs_net_info_stru           *pst_info = (dmac_acs_net_info_stru *)auc_buf;
    dmac_acs_vap_info_stru           *pst_vap_info = (dmac_acs_vap_info_stru *)(pst_info + 1);
    dmac_acs_user_info_stru          *pst_user_info;

    mac_vap_stru                     *pst_vap;
    mac_user_stru                    *pst_user;

    pst_info->uc_vap_cnt = 0;
    pst_info->us_user_cnt = 0;

    OAL_DLIST_SEARCH_FOR_EACH(pst_vap_list, &pst_acs->st_vap_dlist_head)
    {
        pst_vap_internal = OAL_DLIST_GET_ENTRY(pst_vap_list, dmac_acs_vap_internal_stru, st_dlist_head);
        pst_vap = mac_res_get_mac_vap(pst_vap_internal->uc_vap_id);
        if (pst_vap == OAL_PTR_NULL)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ACS, "{dmac_acs_do_get_net_info::get vap failed, vap id=%d}", pst_vap_internal->uc_vap_id);
            continue;
        }
        pst_info->uc_vap_cnt++;
        dmac_acs_setup_vap_info(pst_vap_info++, pst_vap);
    }

    pst_user_info = (dmac_acs_user_info_stru *)pst_vap_info;

    OAL_DLIST_SEARCH_FOR_EACH(pst_vap_list, &pst_acs->st_vap_dlist_head)
    {
        pst_vap_internal = OAL_DLIST_GET_ENTRY(pst_vap_list, dmac_acs_vap_internal_stru, st_dlist_head);
        pst_vap = mac_res_get_mac_vap(pst_vap_internal->uc_vap_id);
        if (pst_vap == OAL_PTR_NULL)
        {
            continue;
        }

        OAL_DLIST_SEARCH_FOR_EACH(pst_user_list, &pst_vap_internal->st_user_dlist_head)
        {
            pst_user_internal = OAL_DLIST_GET_ENTRY(pst_user_list, dmac_acs_user_internal_stru, st_dlist_head);
            pst_user = mac_res_get_mac_user(pst_user_internal->us_assoc_id);
            if (pst_user == OAL_PTR_NULL)
            {
            	OAM_WARNING_LOG1(0, OAM_SF_ACS, "{dmac_acs_do_get_net_info::get user failed, assoc id=%d}", pst_user_internal->us_assoc_id);
            	continue;
            }
            dmac_acs_setup_user_info(pst_user_info++, pst_vap, pst_user);
            pst_info->us_user_cnt++;
        }
    }

    dmac_acs_reply_ex(pst_mac_dev->uc_chip_id, pst_mac_dev->uc_device_id,
        DMAC_ACS_CMD_GET_NET_INFO, pst_cmd->ul_cmd_cnt, auc_buf,
        OAL_SIZEOF(dmac_acs_net_info_stru)
        + (oal_uint32)pst_info->uc_vap_cnt  * OAL_SIZEOF(dmac_acs_vap_info_stru)
        + (oal_uint32)pst_info->us_user_cnt * OAL_SIZEOF(dmac_acs_user_info_stru));
}
/*****************************************************************************
 函 数 名  : dmac_config_acs
 功能描述  : ACS相关参数配置接口
 输入参数  : mac_vap_stru *pst_mac_vap
             oal_uint8 us_len
             oal_uint8 *puc_param
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月23日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_config_acs(mac_vap_stru *pst_mac_vap, oal_uint8 us_len, oal_uint8 *puc_param)
{
    mac_device_stru       *pst_mac_device;
    oal_int8              *pc_token;
    oal_int8              *pc_end;
    oal_int8              *pc_ctx;
    oal_int8              *pc_sep = " ";
    oal_bool_enum_uint8    en_val;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* 获取命令类型 */
    pc_token = oal_strtok((oal_int8 *)puc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (0 == oal_strcmp(pc_token, "sw"))
    {
        pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        en_val = (oal_bool_enum_uint8)oal_strtol(pc_token, &pc_end, 10);

        OAL_IO_PRINT("set acs sw=%d in dmac\n", en_val);
    }
    else
    {
        return OAL_SUCC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_recv_msg
 功能描述  : dmac acs接收来自应用层的命令
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_recv_msg(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_acs_cmd_stru        *pst_acs_cmd;
    mac_device_stru         *pst_mac_dev;
    dmac_acs_stru           *pst_acs;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param) || (0 == uc_len))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ACS, "{dmac_acs_recv_msg::invalid param. pst_mac_vap=%d uc_len=%d puc_param=%d}",
                       pst_mac_vap, uc_len, puc_param);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{dmac_acs_recv_msg::pst_mac_dev null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_mac_dev->pst_acs)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{dmac_acs_recv_msg::pst_acs null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;

    pst_acs_cmd = (mac_acs_cmd_stru *)puc_param;
    if (pst_acs_cmd->uc_cmd >= DMAC_ACS_CMD_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{dmac_acs_recv_msg::invalid command=%d.}", pst_acs_cmd->uc_cmd);
        return OAL_FAIL;
    }

    if (OAL_PTR_NULL == pst_acs->apfn_cmd_handler[pst_acs_cmd->uc_cmd])
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ACS, "{dmac_acs_recv_msg::no command handlerd.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    OAL_IO_PRINT(">>> got=%d:%s\n", pst_acs_cmd->uc_cmd, g_acs_cmd_type[pst_acs_cmd->uc_cmd]);
    pst_acs->apfn_cmd_handler[pst_acs_cmd->uc_cmd](pst_mac_dev, (oal_void *)pst_acs, pst_acs_cmd);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_add_vap
 功能描述  : 增加ACS内部VAP维护记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
            成功:VAP指针
            失败:OAL_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC dmac_acs_vap_internal_stru*  dmac_acs_add_vap(mac_vap_stru *pst_vap)
{
    dmac_acs_stru               *pst_acs;
    mac_device_stru             *pst_mac_dev;
    dmac_acs_vap_internal_stru  *pst_vap_internal;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        return OAL_PTR_NULL;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    if (OAL_PTR_NULL == pst_acs)
    {
        return OAL_PTR_NULL;
    }

    /* 没有找到，是新加入的VAP */
    pst_vap_internal = dmac_acs_find_internal_vap(pst_acs, pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_vap_internal)
    {
        pst_vap_internal = (dmac_acs_vap_internal_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_ALG_LOCAL, OAL_SIZEOF(dmac_acs_vap_internal_stru), OAL_TRUE);
        if (OAL_PTR_NULL != pst_vap_internal)
        {
            OAL_MEMZERO(pst_vap_internal, OAL_SIZEOF(dmac_acs_vap_internal_stru));
            oal_memcopy(pst_vap_internal->auc_bssid, pst_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
            pst_vap_internal->uc_vap_id = pst_vap->uc_vap_id;
            oal_dlist_init_head(&pst_vap_internal->st_user_dlist_head);
            oal_dlist_add_tail(&pst_vap_internal->st_dlist_head, &pst_acs->st_vap_dlist_head);
        }
    }

    return pst_vap_internal;
}
/*****************************************************************************
 函 数 名  : dmac_acs_del_vap
 功能描述  : 删除ACS内部VAP维护记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_del_vap(mac_vap_stru *pst_vap)
{
    dmac_acs_stru               *pst_acs;
    mac_device_stru             *pst_mac_dev;
    oal_dlist_head_stru         *pst_dlist_pos;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        return;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    if (OAL_PTR_NULL == pst_acs)
    {
        return;
    }

    pst_vap_internal = dmac_acs_find_internal_vap(pst_acs, pst_vap->uc_vap_id);
    if (OAL_PTR_NULL != pst_vap_internal)
    {
        while(OAL_FALSE == oal_dlist_is_empty(&pst_vap_internal->st_user_dlist_head))
        {
            pst_dlist_pos = oal_dlist_delete_head(&pst_vap_internal->st_user_dlist_head);
            pst_user_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_acs_user_internal_stru, st_dlist_head);
            OAL_MEM_FREE(pst_user_internal, OAL_TRUE);
        }
        oal_dlist_delete_entry(&pst_vap_internal->st_dlist_head);
        OAL_MEM_FREE(pst_vap_internal, OAL_TRUE);
    }
}


/*****************************************************************************
 函 数 名  : dmac_acs_add_user
 功能描述  : 增加ACS内部USER维护记录
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
            成功:指针
            失败:OAL_ERR_CODE_PTR_NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC dmac_acs_user_internal_stru*  dmac_acs_add_user(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_acs_stru               *pst_acs;
    mac_device_stru             *pst_mac_dev;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        return OAL_PTR_NULL;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    if (OAL_PTR_NULL == pst_acs)
    {
        return OAL_PTR_NULL;
    }

    pst_vap_internal  = dmac_acs_find_internal_vap(pst_acs, pst_vap->uc_vap_id);
    pst_user_internal = OAL_PTR_NULL;
    if (OAL_PTR_NULL != pst_vap_internal)
    {
        pst_user_internal = dmac_acs_find_internal_user(pst_acs, pst_vap->uc_vap_id, pst_user->us_assoc_id);
        /* 没到找到，表示这是一个新用户 */
        if (OAL_PTR_NULL == pst_user_internal)
        {
            pst_user_internal = (dmac_acs_user_internal_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_ALG_LOCAL, OAL_SIZEOF(dmac_acs_user_internal_stru), OAL_TRUE);
            if (OAL_PTR_NULL != pst_user_internal)
            {
                OAL_MEMZERO(pst_user_internal, OAL_SIZEOF(dmac_acs_user_internal_stru));
                oal_memcopy(pst_user_internal->auc_user_addr, pst_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
                pst_user_internal->us_assoc_id = pst_user->us_assoc_id;
                oal_dlist_add_tail(&pst_user_internal->st_dlist_head, &pst_vap_internal->st_user_dlist_head);
                pst_vap_internal->us_sta_num += 1;
            }
            else
            {
                OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ACS, "alloc mem for user failed, size=%d",OAL_SIZEOF(dmac_acs_user_internal_stru));
            }
        }
    }

    return pst_user_internal;
}

/*****************************************************************************
 函 数 名  : dmac_acs_del_user
 功能描述  : 删除ACS内部USER维护记录s
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月28日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void  dmac_acs_del_user(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_acs_stru               *pst_acs;
    mac_device_stru             *pst_mac_dev;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        return;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    if (OAL_PTR_NULL == pst_acs)
    {
        return;
    }

    pst_vap_internal  = dmac_acs_find_internal_vap(pst_acs, pst_vap->uc_vap_id);
    pst_user_internal = OAL_PTR_NULL;
    if (OAL_PTR_NULL != pst_vap_internal)
    {
        pst_user_internal = dmac_acs_find_internal_user(pst_acs, pst_vap->uc_vap_id, pst_user->us_assoc_id);
        if (OAL_PTR_NULL != pst_user_internal)
        {
            oal_dlist_delete_entry(&pst_user_internal->st_dlist_head);
            OAL_MEM_FREE(pst_user_internal, OAL_TRUE);
            pst_vap_internal->us_sta_num -= 1;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_find_internal_vap
 功能描述  : 根据全局唯一的VAP_ID查找ACS内部维护的VAP结构
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC dmac_acs_vap_internal_stru * dmac_acs_find_internal_vap(dmac_acs_stru *pst_acs, oal_uint8  uc_vap_id)
{
    dmac_acs_vap_internal_stru *pst_vap_internal;
    oal_dlist_head_stru        *pst_dlist_pos;

    OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_acs->st_vap_dlist_head)
    {
        pst_vap_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_acs_vap_internal_stru, st_dlist_head);

        if (pst_vap_internal->uc_vap_id == uc_vap_id)
        {
            return pst_vap_internal;
        }
    }

    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : dmac_acs_find_internal_user
 功能描述  : 根据全局唯一的VAP_ID，以及USER的关联ID，
            查找ACS内部维护的USER结构
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC dmac_acs_user_internal_stru * dmac_acs_find_internal_user(dmac_acs_stru *pst_acs, oal_uint8  uc_vap_id, oal_uint16 us_assoc_id)
{
    oal_dlist_head_stru         *pst_dlist_pos;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;

    pst_vap_internal  = dmac_acs_find_internal_vap(pst_acs, uc_vap_id);
    if (OAL_PTR_NULL != pst_vap_internal)
    {
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_vap_internal->st_user_dlist_head)
        {
            pst_user_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos, dmac_acs_user_internal_stru, st_dlist_head);

            if (pst_user_internal->us_assoc_id == us_assoc_id)
            {
                return pst_user_internal;
            }
        }
    }

    return OAL_PTR_NULL;
}

/*****************************************************************************
 函 数 名  : dmac_acs_create_vap_handler
 功能描述  : dmac acs负责处理创建VAP事件的函数
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_create_vap_handler(mac_vap_stru *pst_vap)
{
    dmac_acs_vap_info_stru  st_acs_vap_info;

    if (OAL_PTR_NULL == pst_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_acs_add_vap(pst_vap);

    dmac_acs_setup_vap_info(&st_acs_vap_info, pst_vap);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id,
            DMAC_ACS_NOTIFY_CREATE_VAP,
            0,  // FIXME: cmd_id ?
            (oal_uint8 *)&st_acs_vap_info,
            OAL_SIZEOF(dmac_acs_vap_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_delete_vap_handler
 功能描述  : dmac acs负责处理删除VAP事件的函数
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_delete_vap_handler(mac_vap_stru *pst_vap)
{
    dmac_acs_vap_info_stru      st_acs_vap_info;

    if (OAL_PTR_NULL == pst_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_acs_del_vap(pst_vap);

    dmac_acs_setup_vap_info(&st_acs_vap_info, pst_vap);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id, DMAC_ACS_NOTIFY_DELETE_VAP, 0, (oal_uint8 *)&st_acs_vap_info, OAL_SIZEOF(dmac_acs_vap_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_cfg_channel_handler
 功能描述  : dmac acs负责处理配置VAP工作信道事件的函数
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_cfg_channel_handler(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_acs_vap_channel_info_stru  st_acs_channel;

    if(OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "dmac_acs_cfg_channel_handler:NULL PTR");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (dmac_acs_skip_notify(pst_vap, en_type))
    {
        return OAL_SUCC;
    }

    dmac_acs_setup_vap_info(&st_acs_channel.st_vap_info, pst_vap);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id, DMAC_ACS_NOTIFY_CFG_CHANNEL, 0, (oal_uint8 *)&st_acs_channel, OAL_SIZEOF(dmac_acs_vap_channel_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_cfg_bandwidth_handler
 功能描述  : dmac acs负责处理配置VAP工作带宽事件的函数
 输入参数  : mac_vap_stru *pst_vap
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_cfg_bandwidth_handler(mac_vap_stru *pst_vap, dmac_alg_channel_bw_chg_type_uint8 en_type)
{
    dmac_acs_vap_channel_info_stru  st_acs_channel;

    if(OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "dmac_acs_cfg_bandwidth_handler:NULL PTR");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (dmac_acs_skip_notify(pst_vap, en_type))
    {
        return OAL_SUCC;
    }

    dmac_acs_setup_vap_info(&st_acs_channel.st_vap_info, pst_vap);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id, DMAC_ACS_NOTIFY_CFG_BANDWIDTH, 0, (oal_uint8 *)&st_acs_channel, OAL_SIZEOF(dmac_acs_vap_channel_info_stru));

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_acs_add_assoc_user_handler
 功能描述  : dmac acs负责处理新用户关联到某个VAP的事件处理函数
 输入参数  : mac_vap_stru *pst_vap
             mac_user_stru *pst_user
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_add_assoc_user_handler(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_acs_user_info_stru st_acs_user_info;

    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG4(pst_vap->uc_vap_id, OAM_SF_ACS, "dmac_acs_add_assoc_user_handler:: assoc_id=%d, en_is_multi_user=%d, mac = XX:XX:XX:XX:%02X:%02X.",
                   (oal_uint32)pst_user->us_assoc_id,
                    pst_user->en_is_multi_user,
                   pst_user->auc_user_mac_addr[4]&0xff,
                   pst_user->auc_user_mac_addr[5]&0xff);

    /* 组播用户不会进行ACS管理 */
    if (OAL_TRUE == pst_user->en_is_multi_user)
    {
        return OAL_SUCC;
    }

    /* 通知ACS记录该USER */
    dmac_acs_add_user(pst_vap, pst_user);
    dmac_acs_setup_user_info(&st_acs_user_info, pst_vap, pst_user);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id, DMAC_ACS_NOTIFY_ADD_USER, 0, (oal_uint8 *)&st_acs_user_info, OAL_SIZEOF(dmac_acs_user_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_del_assoc_user_handler
 功能描述  : dmac acs负责处理某个已关联用户从某个VAP去关联的事件处理函数
 输入参数  : mac_vap_stru *pst_vap
             mac_user_stru *pst_user
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_del_assoc_user_handler(mac_vap_stru *pst_vap, mac_user_stru *pst_user)
{
    dmac_acs_user_info_stru st_acs_user_info;

    if ((OAL_PTR_NULL == pst_vap) || (OAL_PTR_NULL == pst_user))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_acs_del_user(pst_vap, pst_user);

    dmac_acs_setup_user_info(&st_acs_user_info, pst_vap, pst_user);

    dmac_acs_reply_ex(pst_vap->uc_chip_id, pst_vap->uc_device_id, DMAC_ACS_NOTIFY_DEL_USER, 0, (oal_uint8 *)&st_acs_user_info, OAL_SIZEOF(dmac_acs_user_info_stru));

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_acs_beacon_tbtt_trace
 功能描述  : 处理AP在CSA过程中的TBTT计数过程
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月22日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_beacon_tbtt_trace(dmac_vap_stru *pst_dmac_vap)
{
    mac_device_stru            *pst_mac_dev;
    mac_vap_stru               *pst_mac_vap;
    dmac_acs_stru              *pst_acs;
    oal_uint8                   uc_vap_id;
    oal_uint8                   uc_band;
    dmac_acs_vap_internal_stru *pst_vap_int;

    /* 跟踪信道切换时的TBTT计数 */
    pst_mac_dev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        return;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    if (OAL_PTR_NULL == pst_acs)
    {
        return;
    }

    pst_mac_vap = (mac_vap_stru *)pst_dmac_vap;
    uc_band     = pst_mac_vap->st_channel.en_band;
    uc_vap_id   = pst_mac_vap->uc_vap_id;
    pst_vap_int = dmac_acs_find_internal_vap(pst_acs, uc_vap_id);
    if (OAL_PTR_NULL == pst_vap_int)
    {
        return;
    }

    if (OAL_TRUE == pst_vap_int->en_in_csa_phase)
    {
        if (pst_vap_int->auc_tbtt_cnt[uc_band] > 0)
        {
            pst_vap_int->auc_tbtt_cnt[uc_band] -= 1;
        }
        else
        {
            /* TBD fcs 信道切换 */


            pst_vap_int->en_in_csa_phase = OAL_FALSE;
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_radar_detected_handler
 功能描述  : ACS负责处理雷达检测的函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC:表示该雷达事件由ACS负责处理并进行信道切换
             OAL_FAIL:表示该雷达事件无法由ACS处理，交由DFS完成信道切换
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_acs_radar_detected_handler(mac_device_stru *pst_mac_device, hal_radar_det_event_stru *pst_radar_det_info)
{
    dmac_acs_radar_info_stru  st_dmac_acs_radar_info;
    dmac_acs_stru            *pst_acs;

    if (OAL_PTR_NULL == pst_mac_device->pst_acs)
    {
        return OAL_FAIL;
    }
    pst_acs = (dmac_acs_stru *)pst_mac_device->pst_acs;

    /* 如果当前正在扫描，丢弃该雷达检测事件 */
    if (OAL_TRUE == pst_acs->en_in_scan)
    {
        return OAL_SUCC;
    }

    /* NETLINK方式通知APP */
    OAL_MEMZERO(&st_dmac_acs_radar_info, OAL_SIZEOF(dmac_acs_radar_info_stru));
    st_dmac_acs_radar_info.uc_channel_number = pst_radar_det_info->uc_channel_num;
    st_dmac_acs_radar_info.en_bandwidth_mode = pst_radar_det_info->uc_working_bw;
    st_dmac_acs_radar_info.uc_radar_bw       = pst_radar_det_info->uc_radar_bw;
    st_dmac_acs_radar_info.uc_freq_offset    = pst_radar_det_info->uc_radar_freq_offset;
    dmac_acs_reply_ex(pst_mac_device->uc_chip_id, pst_mac_device->uc_device_id, DMAC_ACS_NOTIFY_RADAR_DETECTED, 0, (oal_uint8 *)&st_dmac_acs_radar_info, OAL_SIZEOF(dmac_acs_radar_info_stru));

    /* TBD 由ACS完成信道切换 */


    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_acs_report_support_chan
 功能描述  : 上报可用信道列表
 输入参数  : mac_vap_stru *pst_mac_vap
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_report_support_chan(mac_vap_stru *pst_mac_vap)
{
    mac_acs_cmd_stru   st_acs_cmd;
    mac_device_stru   *pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        return;
    }
    st_acs_cmd.ul_cmd_cnt = 0;

    dmac_acs_do_avl_channel(pst_mac_device, (oal_void *)(&g_ast_acs[pst_mac_vap->uc_device_id]), &st_acs_cmd);
}

#ifdef _PRE_SUPPORT_DYNA_ACS
/*****************************************************************************
 函 数 名  : dmac_acs_get_rate_num
 功能描述  : 获取速率的数量
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_acs_get_rate_num(mac_device_stru *pst_device,
                hal_tx_txop_per_rate_params_union  un_rate_info,
                oal_uint32                        *pul_num)
{
    wlan_protocol_enum_uint8    en_protocol;
    oal_uint32                  ul_rate_num = 0;

    en_protocol = un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    switch(en_protocol)
    {
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_LEGACY_11B_MODE:
            hal_get_rate_80211g_num(pst_device->pst_device_stru, &ul_rate_num);
            break;

        case WLAN_HT_MODE:
            ul_rate_num = 36;
            break;

        case WLAN_VHT_MODE:
            ul_rate_num = 64;
            break;

        default:
            return OAL_FALSE;
    }

    *pul_num = ul_rate_num;

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : dmac_acs_judge_rate_condition
 功能描述  : 根据协议，判断速率索引的速率是否正确
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  dmac_acs_judge_rate_condition(mac_device_stru *pst_device,
                                    oal_uint8                           uc_rate_idx,
                                    hal_tx_txop_per_rate_params_union   un_rate_info,
                                    hal_channel_assemble_enum_uint8     en_bandwidth,
                                    oal_uint32                         *pul_rate_kbps)
{
    oal_bool_enum_uint8         en_found = OAL_FALSE;
    oal_uint8                   uc_mcs;
    wlan_protocol_enum_uint8    en_protocol;

    en_protocol = un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    switch(en_protocol)
    {
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_LEGACY_11B_MODE:
            uc_mcs = un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;
            if (pst_device->st_mac_rates_11g[uc_rate_idx].uc_phy_rate == uc_mcs)
            {
                *pul_rate_kbps = pst_device->st_mac_rates_11g[uc_rate_idx].uc_mbps * 1000;
                en_found = OAL_TRUE;
            }
            break;

        case WLAN_HT_MODE:
            uc_mcs = un_rate_info.rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs;
            if ((g_ast_11n_table[uc_rate_idx].un_nss_rate.en_ht_mcs == uc_mcs) &&
                (un_rate_info.rate_bit_stru.bit_short_gi_enable == g_ast_11n_table[uc_rate_idx].en_short_gi)        &&
                (en_bandwidth == g_ast_11n_table[uc_rate_idx].en_bandwidth))
            {
                *pul_rate_kbps = g_ast_11n_table[uc_rate_idx].ul_rate_kbps;
                en_found = OAL_TRUE;
            }
            break;

        case WLAN_VHT_MODE:
            uc_mcs = un_rate_info.rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs;
            if ((g_ast_11ac_table[uc_rate_idx].un_nss_rate.en_vht_mcs == uc_mcs) &&
                (un_rate_info.rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode ==
                 g_ast_11ac_table[uc_rate_idx].en_nss) &&
                (un_rate_info.rate_bit_stru.bit_short_gi_enable ==
                 g_ast_11ac_table[uc_rate_idx].en_short_gi) &&
                (en_bandwidth == g_ast_11ac_table[uc_rate_idx].en_bandwidth))
            {
                *pul_rate_kbps = g_ast_11ac_table[uc_rate_idx].ul_rate_kbps;
                en_found = OAL_TRUE;
            }
            break;

        default:
            break;
    }

    return en_found;
}


/*****************************************************************************
 函 数 名  : dmac_acs_get_rate_kbps
 功能描述  : 获取具体的速率，单位Kbps
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月25日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  dmac_acs_get_rate_kbps(mac_device_stru           *pst_device,
                                                        hal_tx_txop_per_rate_params_union  un_rate_info,
                                                        hal_channel_assemble_enum_uint8    en_bandwidth,
                                                        oal_uint32                        *pul_rate_kbps)
{
    oal_bool_enum_uint8         en_found     = OAL_FALSE;
    oal_uint32                  ul_rate_num;
    oal_uint8                   uc_rate_idx;

    if (OAL_TRUE != dmac_acs_get_rate_num(pst_device, un_rate_info, &ul_rate_num))
    {
        return OAL_FALSE;
    }

    for (uc_rate_idx = 0; uc_rate_idx < ul_rate_num; uc_rate_idx++)
    {
        if (OAL_TRUE == dmac_acs_judge_rate_condition(pst_device, uc_rate_idx, un_rate_info, en_bandwidth, pul_rate_kbps))
        {

            en_found = OAL_TRUE;
            break;
        }
    }

    return en_found;
}

/*****************************************************************************
 函 数 名  : dmac_acs_in_chan_stats
 功能描述  : 判断是否需要进行DURATION统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_TRUE 需要 OAL_FALSE 不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月20日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_acs_in_chan_stats(oal_uint8 uc_device_id, mac_device_stru **ppst_mac_dev, dmac_acs_stru **ppst_acs_ref)
{
    dmac_acs_stru   *pst_acs;
    mac_device_stru *pst_mac_dev;

    if ((OAL_PTR_NULL == ppst_mac_dev) ||(OAL_PTR_NULL == ppst_acs_ref))
    {
        return OAL_FALSE;
    }

    pst_mac_dev = mac_res_get_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        *ppst_mac_dev = OAL_PTR_NULL;
        *ppst_acs_ref = OAL_PTR_NULL;
        return OAL_FALSE;
    }

    if (OAL_PTR_NULL == pst_mac_dev->pst_acs)
    {
        *ppst_mac_dev = OAL_PTR_NULL;
        *ppst_acs_ref = OAL_PTR_NULL;
        return OAL_FALSE;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_dev->pst_acs;
    *ppst_acs_ref = pst_acs;
    *ppst_mac_dev = pst_mac_dev;

    return (OAL_TRUE == pst_acs->en_in_stats) || (pst_acs->uc_csa_vap_cnt > 0);
}

/*****************************************************************************
 函 数 名  : dmac_acs_tx_notify
 功能描述  : 发送完成中断，用于跟踪CSA是否完成发送，以便进行TBTT计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_tx_notify(dmac_acs_stru *pst_acs, oal_uint8 uc_vap_id, oal_netbuf_stru *pst_buf)
{
    oal_uint8                           *puc_frame_body;
    dmac_acs_vap_internal_stru          *pst_vap_internal;

    if (0 == pst_acs->uc_csa_vap_cnt)
    {
        return;
    }

    pst_vap_internal = dmac_acs_find_internal_vap(pst_acs, uc_vap_id);
    if ((OAL_PTR_NULL != pst_vap_internal) && (OAL_TRUE == pst_vap_internal->en_dfs_wait_for_csa_sent))
    {
        if ((WLAN_MANAGEMENT == mac_frame_get_type_value(oal_netbuf_header(pst_buf)))
            && (OAL_TRUE == mac_ieeee80211_is_action(oal_netbuf_header(pst_buf))))
        {
            /* 判断是否是CHANNEL SWITCH ANNOUNCEMENT帧 */
            puc_frame_body  = (oal_uint8 *)OAL_NETBUF_HEADER(pst_buf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            puc_frame_body  = (oal_uint8 *)OAL_NETBUF_DATA(pst_buf);
#else
            puc_frame_body  = (oal_uint8 *)OAL_NETBUF_HEADER(pst_buf) + MAC_80211_FRAME_LEN;
#endif

            /* Category(1B) + Action(1B) + ChannelSwitchIE ID(1B) */
            if ((puc_frame_body[0] == 0) && (puc_frame_body[1] == 4) && (puc_frame_body[2] == 37))
            {
                pst_vap_internal->en_dfs_wait_for_csa_sent = OAL_FALSE;
                pst_vap_internal->en_in_csa_phase          = OAL_TRUE;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_tx_update
 功能描述  : 统计发送帧的时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月20日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_tx_update(mac_user_stru *pst_mac_user, oal_netbuf_stru *pst_buf, hal_tx_dscr_ctrl_one_param *pst_tx_dscr_one)
{
    wlan_protocol_enum_uint8             en_protocol;
    oal_bool_enum_uint8                  en_found = OAL_FALSE;
    oal_uint32                           ul_rate_kbps;
    oal_uint32                           ul_one_duration;
    oal_uint32                           ul_duration = 0;
    oal_uint32                           ul_bytes;
    oal_uint16                           us_ack_time;
    oal_uint8                            uc_last_rank;
    oal_uint8                            uc_rate_rank;
    oal_uint8                            uc_max_tries, uc_total_tries;
    mac_device_stru                     *pst_mac_device;
    dmac_acs_stru                       *pst_acs;
    dmac_acs_user_internal_stru         *pst_user_internal;

    if (OAL_TRUE != dmac_acs_in_chan_stats(pst_mac_user->uc_device_id, &pst_mac_device, &pst_acs))
    {
        return OAL_SUCC;
    }

    /* 仅仅在动态调整开启时才统计*/
    if (mac_get_acs_switch(pst_mac_device) < MAC_ACS_SW_DYNA)
    {
        return OAL_SUCC;
    }

    /* 跟踪CSA是否成功发送 */
    dmac_acs_tx_notify(pst_acs, pst_mac_user->uc_vap_id, pst_buf);

    /* 找到最后一个速率等级 */
    uc_last_rank = pst_tx_dscr_one->uc_last_rate_rank;

    /* 累计计算发送时长 */
    ul_bytes       = 0;
    uc_total_tries = 0;
    for (uc_rate_rank = 0; uc_rate_rank <= uc_last_rank; uc_rate_rank++)
    {
        en_protocol = pst_tx_dscr_one->ast_per_rate[uc_rate_rank].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
        en_found = dmac_acs_get_rate_kbps(pst_mac_device, pst_tx_dscr_one->ast_per_rate[uc_rate_rank], pst_tx_dscr_one->uc_bandwidth, &ul_rate_kbps);
        if (OAL_FALSE == en_found)
        {
            continue;
        }

        /* 计算以该速率传输该报文的近似时间(含IFS和ACK时间) */
        us_ack_time = g_auc_ack_time[en_protocol % WLAN_PROTOCOL_BUTT];
        /* Duration = DIFS +  Payload + SIFS + ACK */
        ul_one_duration =  28
                            + ((((((oal_uint32)pst_tx_dscr_one->us_mpdu_len * pst_tx_dscr_one->uc_mpdu_num)) << 3) * 1000 + (ul_rate_kbps >> 1))/ ul_rate_kbps)
                            + 10
                            + us_ack_time;

        uc_max_tries    = pst_tx_dscr_one->ast_per_rate[uc_rate_rank].rate_bit_stru.bit_tx_count;
        uc_total_tries += uc_max_tries;
        ul_duration    += ul_one_duration * uc_max_tries;
        ul_bytes       += (pst_tx_dscr_one->us_mpdu_len * pst_tx_dscr_one->uc_mpdu_num) * uc_max_tries;
    }

    /* 更新ACS TX DURATION USER DURATION 统计记录 */
    pst_user_internal = dmac_acs_find_internal_user(pst_acs, pst_mac_user->uc_vap_id, pst_mac_user->us_assoc_id);
    if (OAL_PTR_NULL != pst_user_internal)
    {
        pst_user_internal->ul_tx_duration_us  += ul_duration;
        pst_user_internal->ul_tx_pkt_cnt      += uc_total_tries;
        pst_user_internal->ul_tx_pkt_bytes    += ul_bytes;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_rx_update
 功能描述  : 统计接收帧的发送时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月20日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_rx_update(mac_vap_stru *pst_mac_vap,
                mac_user_stru                       *pst_mac_user,
                oal_netbuf_stru                     *pst_buf,
                hal_rx_statistic_stru               *pst_rx_stats)
{
    oal_uint32                           ul_duration;
    oal_uint32                           ul_frame_len;
    oal_uint32                           ul_rate_kbps;
    oal_uint16                           us_ack_time;
    wlan_protocol_enum_uint8             en_protocol;
    mac_device_stru                     *pst_mac_device;
    dmac_acs_user_internal_stru         *pst_user_internal;
    dmac_acs_stru                       *pst_acs;
    hal_tx_txop_per_rate_params_union    un_rate_info;
    dmac_rx_ctl_stru                    *pst_cb_ctrl;


    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_mac_user) ||
        (OAL_PTR_NULL == pst_buf) || (OAL_PTR_NULL == pst_rx_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "{dmac_acs_rx_update::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if ((OAL_PTR_NULL == pst_mac_device) || (OAL_PTR_NULL == pst_mac_device->pst_acs))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 仅仅在动态调整开启时才统计*/
    if (mac_get_acs_switch(pst_mac_device) < MAC_ACS_SW_DYNA)
    {
        return OAL_SUCC;
    }

    pst_acs = (dmac_acs_stru *)pst_mac_device->pst_acs;
    pst_cb_ctrl = (dmac_rx_ctl_stru*)oal_netbuf_cb(pst_buf);

    en_protocol  = pst_rx_stats->un_nss_rate.st_legacy_rate.bit_protocol_mode;
    ul_frame_len = pst_cb_ctrl->st_rx_info.us_frame_len;
    un_rate_info.ul_value = 0;
    un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = pst_cb_ctrl->st_rx_statistic.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = pst_cb_ctrl->st_rx_statistic.un_nss_rate.st_legacy_rate.bit_legacy_rate;
    un_rate_info.rate_bit_stru.un_nss_rate.st_legacy_rate.bit_reserved1     = pst_cb_ctrl->st_rx_statistic.un_nss_rate.st_legacy_rate.bit_reserved1;
    un_rate_info.rate_bit_stru.bit_short_gi_enable                          = pst_cb_ctrl->st_rx_status.bit_GI;
    if (OAL_FALSE == dmac_acs_get_rate_kbps(pst_mac_device, un_rate_info, pst_cb_ctrl->st_rx_status.bit_freq_bandwidth_mode, &ul_rate_kbps))
    {
        return OAL_SUCC;
    }

    if (0 != ul_rate_kbps)
    {
        us_ack_time = g_auc_ack_time[en_protocol % WLAN_PROTOCOL_BUTT];

        /* Duration = DIFS +  Payload + SIFS + ACK */
        ul_duration =  28
                        + (((ul_frame_len << 3) * 1000 + ((ul_rate_kbps) >> 1)) / ul_rate_kbps)
                        + 10
                        + us_ack_time;

        /* 更新该帧对应的USER的 RX 空口占用时间 */
        pst_user_internal = dmac_acs_find_internal_user(pst_acs, pst_mac_vap->uc_vap_id, pst_mac_user->us_assoc_id);
        if (OAL_PTR_NULL != pst_user_internal)
        {
            pst_user_internal->ul_rx_duration_us  += ul_duration;
            pst_user_internal->ul_rx_pkt_cnt      += 1;
            pst_user_internal->ul_rx_pkt_bytes    += ul_frame_len;
        }
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_acs_request_switch_channel
 功能描述  : ACS导出给其他模块的接口函数，用于请求选择更好的信道。
 输入参数  : dmac_acs_rsn_enum_uint8 en_reason
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月16日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_request_switch_channel(mac_acs_rsn_enum_uint8 en_reason)
{
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_acs_init
 功能描述  : dmac acs初始化函数
 输入参数  : pst_device:指向mac_device_stru结构的指针
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_init(mac_device_stru *pst_device)
{
    dmac_acs_stru *pst_acs;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "{dmac_acs_init::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device->pst_acs = &g_ast_acs[pst_device->uc_device_id];

    pst_acs = (dmac_acs_stru *)pst_device->pst_acs;
    OAL_MEMZERO(pst_acs, OAL_SIZEOF(dmac_acs_stru));
    pst_acs->uc_chip_id   = pst_device->uc_chip_id;
    pst_acs->uc_device_id = pst_device->uc_device_id;

    pst_acs->ast_best_channel_per_band[WLAN_BAND_2G].en_valid = OAL_TRUE;
    pst_acs->ast_best_channel_per_band[WLAN_BAND_2G].en_bandwidth = WLAN_BAND_WIDTH_20M;
    pst_acs->ast_best_channel_per_band[WLAN_BAND_2G].uc_channel_number = 1;

    pst_acs->ast_best_channel_per_band[WLAN_BAND_5G].en_valid = OAL_TRUE;
    pst_acs->ast_best_channel_per_band[WLAN_BAND_5G].en_bandwidth = WLAN_BAND_WIDTH_20M;
    pst_acs->ast_best_channel_per_band[WLAN_BAND_5G].uc_channel_number = 149; // note: maybe not valid

    oal_dlist_init_head(&pst_acs->st_vap_dlist_head);
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_SET_BEST_CHANNEL]  = dmac_acs_do_set_best_channel;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_GET_VAP_PERF_INFO] = dmac_acs_do_vap_perf;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_GET_AVAIL_CHANNEL] = dmac_acs_do_avl_channel;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_DO_OFFCHAN_CAC]    = dmac_acs_do_scan;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_DO_SCAN]           = dmac_acs_do_scan;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_DO_CSA]            = dmac_acs_do_csa;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_DO_DURATION_STATS] = dmac_acs_do_duration_stats;
    pst_acs->apfn_cmd_handler[DMAC_ACS_CMD_GET_NET_INFO]      = dmac_acs_do_get_net_info;

    /* 注册ACS运行需要的钩子: */
    /* (1)VAP 创建/删除       */
    /* (2)USER 关联/去关联    */
    /* (3)设置VAP信道/带宽    */
    dmac_alg_register_add_vap_notify_func(DMAC_ALG_ADD_VAP_NOTIFY_ACS, dmac_acs_create_vap_handler);
    dmac_alg_register_del_vap_notify_func(DMAC_ALG_DEL_VAP_NOTIFY_ACS, dmac_acs_delete_vap_handler);
    dmac_alg_register_add_user_notify_func(DMAC_ALG_ADD_USER_NOTIFY_ACS, dmac_acs_add_assoc_user_handler);
    dmac_alg_register_del_user_notify_func(DMAC_ALG_DEL_USER_NOTIFY_ACS, dmac_acs_del_assoc_user_handler);
    dmac_alg_register_cfg_channel_notify_func(DMAC_ALG_CFG_CHANNEL_NOTIFY_ACS, dmac_acs_cfg_channel_handler);
    dmac_alg_register_cfg_bandwidth_notify_func(DMAC_ALG_CFG_BANDWIDTH_NOTIFY_ACS, dmac_acs_cfg_bandwidth_handler);
#ifdef _PRE_SUPPORT_DYNA_ACS
    dmac_alg_register_tx_complete_notify_func(DMAC_ALG_TX_COMPLETE_ACS, dmac_acs_tx_update);
    dmac_alg_register_rx_notify_func(DMAC_ALG_RX_ACS, dmac_acs_rx_update);
#endif

#if defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    dmac_acs_verify_init();
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_acs_exit
 功能描述  : dmac acs卸载函数
 输入参数  : pst_device:指向mac_device_stru结构的指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : 王山博196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_acs_exit(mac_device_stru *pst_device)
{
    dmac_acs_stru               *pst_acs;
    dmac_acs_vap_internal_stru  *pst_vap_internal;
    dmac_acs_user_internal_stru *pst_user_internal;
    oal_dlist_head_stru         *pst_dlist_pos1, *pst_dlist_pos2;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "{dmac_acs_exit::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL != pst_device->pst_acs)
    {
        pst_acs = (dmac_acs_stru *)pst_device->pst_acs;

        /* 删除所有内部的VAP/USER */
        while(OAL_FALSE == oal_dlist_is_empty(&pst_acs->st_vap_dlist_head))
        {
            pst_dlist_pos1   = oal_dlist_delete_head(&pst_acs->st_vap_dlist_head);
            pst_vap_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos1, dmac_acs_vap_internal_stru, st_dlist_head);

            while(OAL_FALSE == oal_dlist_is_empty(&pst_vap_internal->st_user_dlist_head))
            {
                pst_dlist_pos2    = oal_dlist_delete_head(&pst_vap_internal->st_user_dlist_head);
                pst_user_internal = OAL_DLIST_GET_ENTRY(pst_dlist_pos2, dmac_acs_user_internal_stru, st_dlist_head);
                OAL_MEM_FREE(pst_user_internal, OAL_TRUE);
            }

            OAL_MEM_FREE(pst_vap_internal, OAL_TRUE);
        }

        /* 取消注册钩子 */
        dmac_alg_unregister_add_vap_notify_func(DMAC_ALG_ADD_VAP_NOTIFY_ACS);
        dmac_alg_unregister_del_vap_notify_func(DMAC_ALG_DEL_VAP_NOTIFY_ACS);
        dmac_alg_unregister_add_user_notify_func(DMAC_ALG_ADD_USER_NOTIFY_ACS);
        dmac_alg_unregister_del_user_notify_func(DMAC_ALG_DEL_USER_NOTIFY_ACS);
        dmac_alg_unregister_cfg_channel_notify_func(DMAC_ALG_CFG_CHANNEL_NOTIFY_ACS);
        dmac_alg_unregister_cfg_bandwidth_notify_func(DMAC_ALG_CFG_BANDWIDTH_NOTIFY_ACS);
        dmac_alg_unregister_tx_complete_notify_func(DMAC_ALG_TX_COMPLETE_ACS);
        dmac_alg_unregister_rx_notify_func(DMAC_ALG_RX_ACS);

        pst_device->pst_acs = OAL_PTR_NULL;
        #if defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        dmac_acs_verify_exit();
        #endif
    }

    return OAL_SUCC;
}

#endif  /* #ifdef _PRE_SUPPORT_ACS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
