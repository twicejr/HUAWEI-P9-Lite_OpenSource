/******************************************************************************

                  版权所有 (C), 1998-2012, 华为技术有限公司

*******************************************************************************
  文 件 名   : ftm_lte_def.c
  版 本 号   : V1.0
  作    者   : l00169177
  生成日期   : 2012-12-24
  功能描述   : 定义了LTE协议相关的变量和函数

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2012-12-24
    作    者 : l00169177
    修改内容 : 创建文件

  2.日    期 : 2013-08-13
    作    者 : l00169177
    修改内容 : 完善MT工位AT命令 DTS2013081300992

******************************************************************************/
#include <ftm_errno.h>
#include <osm.h>
#include <gen_msg.h>
#include <ftm.h>
#include "LMspLPhyInterface.h"
#include "ftm_ct.h"
#include <LNvCommon.h>
#include "RrcNvInterface.h"
#include "msp_nvim.h"

/*lint --e{830,539,525}*/

/* LTE频段信息表 */
const FTM_BAND_INFO_STRU g_stBandInfo[] = {
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band0 Not Used */
    {  21100,      0,    599,  19200,  18000,  18599,  EN_FCHAN_MODE_FDD_LTE,       0 }, /* Band1  */
    {  19300,    600,   1199,  18500,  18600,  19199,  EN_FCHAN_MODE_FDD_LTE,       1 }, /* Band2  */
    {  18050,   1200,   1949,  17100,  19200,  19949,  EN_FCHAN_MODE_FDD_LTE,       2 }, /* Band3  */
    {  21100,   1950,   2399,  17100,  19950,  20399,  EN_FCHAN_MODE_FDD_LTE,       3 }, /* Band4  */
    {   8690,   2400,   2649,   8240,  20400,  20649,  EN_FCHAN_MODE_FDD_LTE,       7 }, /* Band5  */
    {   8750,   2650,   2749,   8300,  20650,  20749,  EN_FCHAN_MODE_FDD_LTE,      21 }, /* Band6  */
    {  26200,   2750,   3449,  25000,  20750,  21449,  EN_FCHAN_MODE_FDD_LTE,      10 }, /* Band7  */
    {   9250,   3450,   3799,   8800,  21450,  21799,  EN_FCHAN_MODE_FDD_LTE,       6 }, /* Band8  */
    {  18449,   3800,   4149,  17499,  21800,  22149,  EN_FCHAN_MODE_FDD_LTE,      13 }, /* Band9  */
    {  21100,   4150,   4749,  17100,  22150,  22749,  EN_FCHAN_MODE_FDD_LTE,      14 }, /* Band10  */
    {  14759,   4750,   4949,  14279,  22750,  22949,  EN_FCHAN_MODE_FDD_LTE,       5 }, /* Band11  */
    {   7290,   5010,   5179,   6990,  23010,  23179,  EN_FCHAN_MODE_FDD_LTE,      16 }, /* Band12  */
    {   7460,   5180,   5279,   7770,  23180,  23279,  EN_FCHAN_MODE_FDD_LTE,      17 }, /* Band13  */
    {   7580,   5280,   5379,   7880,  23280,  23379,  EN_FCHAN_MODE_FDD_LTE,      19 }, /* Band14  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band15  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band16  */
    {   7340,   5730,   5849,   7040,  23730,  23849,  EN_FCHAN_MODE_FDD_LTE,      18 }, /* Band17  */
    {   8600,   5850,   5999,   8150,  23850,  23999,  EN_FCHAN_MODE_FDD_LTE,       8 }, /* Band18  */
    {   8750,   6000,   6149,   8300,  24000,  24149,  EN_FCHAN_MODE_FDD_LTE,      22 }, /* Band19  */
    {   7910,   6150,   6449,   8320,  24150,  24449,  EN_FCHAN_MODE_FDD_LTE,      20 }, /* Band20  */
    {  14959,   6450,   6599,  14479,  24450,  24599,  EN_FCHAN_MODE_FDD_LTE,      23 }, /* Band21  */
    {  35100,   6600,   7399,  34100,  24600,  25399,  EN_FCHAN_MODE_FDD_LTE,     255 }, /* Band22  */
    {  21800,   7500,   7699,  20000,  25500,  25699,  EN_FCHAN_MODE_FDD_LTE,     255 }, /* Band23  */
    {  15250,   7700,   8039,  16265,  25700,  26039,  EN_FCHAN_MODE_FDD_LTE,       4 }, /* Band24  */
    {  19300,   8040,   8689,  18500,  26040,  26689,  EN_FCHAN_MODE_FDD_LTE,      31 }, /* Band25  */
    {   8590,   8690,   9039,   8140,  26690,  27039,  EN_FCHAN_MODE_FDD_LTE,      32 }, /* Band26  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band27  */
    {   7580,   9210,   9659,   7030,  27210,  27659,  EN_FCHAN_MODE_FDD_LTE,     34 }, /* Band28  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band29  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band30  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band31  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band32  */
    {  19000, 36000,   36199,  19000,  36000,  36199,  EN_FCHAN_MODE_TDD_LTE,     25 }, /* Band33  */
    {  20100, 36200,   36349,  20100,  36200,  36349,  EN_FCHAN_MODE_TDD_LTE,     24 }, /* Band34  */
    {  18500, 36350,   36949,  18500,  36350,  36949,  EN_FCHAN_MODE_TDD_LTE,     12 }, /* Band35  */
    {  19300, 36950,   37549,  19300,  36950,  37549,  EN_FCHAN_MODE_TDD_LTE,      9 }, /* Band36  */
    {  19100, 37550,   37749,  19100,  37550,  37749,  EN_FCHAN_MODE_TDD_LTE,     26 }, /* Band37  */
    {  25700, 37750,   38249,  25700,  37750,  38249,  EN_FCHAN_MODE_TDD_LTE,     15 }, /* Band38  */
    {  18800, 38250,   38649,  18800,  38250,  38649,  EN_FCHAN_MODE_TDD_LTE,     27 }, /* Band39  */
    {  23000, 38650,   39649,  23000,  38650,  39649,  EN_FCHAN_MODE_TDD_LTE,     11 }, /* Band40  */
    {  24960, 39650,   41589,  24960,  39650,  41589,  EN_FCHAN_MODE_TDD_LTE,     28 }, /* Band41  */
    {  34000, 41590,   43589,  34000,  41590,  43589,  EN_FCHAN_MODE_TDD_LTE,     29 }, /* Band42  */
    {  36000, 43590,   45589,  36000,  43590,  45589,  EN_FCHAN_MODE_TDD_LTE,     30 }, /* Band43  */

    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band44  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band45  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band46  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band47  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band48  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band49  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band50  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band51  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band52  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band53  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band54  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band55  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band56  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band57  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band58  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band59  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band60  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band61  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band62  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band63  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band64  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band65  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band66  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band67  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band68  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band69  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band70  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band71  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band72  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band73  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band74  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band75  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band76  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band77  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band78  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band79  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band80  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band81  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band82  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band83  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band84  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band85  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band86  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band87  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band88  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band89  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band90  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band91  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band92  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band93  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band94  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band95  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band96  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band97  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band98  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band99  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band100  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band101  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band102  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band103  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band104  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band105  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band106  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band107  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band108  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band109  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band110  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band111  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band112  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band113  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band114  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band115  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band116  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band117  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band118  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band119  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band120  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band121  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band122  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band123  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band124  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band125  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band126  */
    {      0,      0,      0,      0,      0,      0,  EN_FCHAN_MODE_UNKONWN,    255 }, /* Band127  */
    {   7805,   9435,   9659,   7255,  27435,  27659,  EN_FCHAN_MODE_FDD_LTE,    128 }, /* Band128  */
};

/* TDS频段信息表 */
const FTM_BAND_INFO_STRU g_stTdsBandInfo[] = {
    {  10050,  10050,  10125,  10050,  10050,  10125,  EN_FCHAN_MODE_TD_SCDMA,     0 }, /* Band A 2010~2025MHz */
    {   9650,   9650,   9950,   9650,   9650,   9950,  EN_FCHAN_MODE_TD_SCDMA,     3 }, /* Band B 1930~1990MHz */
    {   9550,   9550,   9650,   9550,   9550,   9650,  EN_FCHAN_MODE_TD_SCDMA,     4 }, /* Band C 1910~1930MHz */
    {  12850,  12850,  13100,  12850,  12850,  13100,  EN_FCHAN_MODE_TD_SCDMA,     5 }, /* Band D 2570~2620MHz */
    {  11500,  11500,  12000,  11500,  11500,  12000,  EN_FCHAN_MODE_TD_SCDMA,     2 }, /* Band E 2300~2400MHz */
    {   9400,   9400,   9600,   9400,   9400,   9600,  EN_FCHAN_MODE_TD_SCDMA,     1 }, /* Band F 1880~1920MHz */
};

/*****************************************************************************
 函 数 名  : at_ftm_getBandID
 功能描述  : 通过Band Swith ID和Band Mode(FDD,TDD)获得Band ID
 输入参数  : emMode     模式 (LTE TDS)
             ucBandSwitchID Band Swith ID
 输出参数  : pucBandID 获取的Band ID
 返 回 值  : 成功返回ERR_FTM_SUCCESS，失败返回ERR_FTM_FAILURE
*****************************************************************************/
/*lint -save -e958*/
VOS_UINT32 at_ftm_getBandID(FCHAN_MODE_ENUM emMode, VOS_UINT8 ucBandSwitchID, VOS_UINT8* pucBandID)
{
    VOS_UINT8 i    = 0;
    *pucBandID = 0;

    if(EN_FCHAN_MODE_TD_SCDMA == emMode) /* TDS */
    {
        for(i=0; i<FTM_MAX_TDS_BAND_NUM; i++)
        {
            if(g_stTdsBandInfo[i].ucBandSWID == ucBandSwitchID)
            {
                *pucBandID = i;
                return  ERR_FTM_SUCCESS;
            }
        }
    }
    else                                     /* LTE */
    {
        for(i=1; i<FTM_MAX_BAND_NUM; i++)
        {
            if((g_stBandInfo[i].ucBandSWID== ucBandSwitchID)
                &&(g_stBandInfo[i].ucBandMode==(VOS_UINT8)emMode))
            {
                *pucBandID = i;
                return ERR_FTM_SUCCESS;
            }
        }

    }
    return ERR_FTM_FAILURE;
}
/*lint -restore*/

/*****************************************************************************
 函 数 名  : at_ftm_get_ulchan
 功能描述  : 通过某频点获得其对应的上行频点
 输入参数  : emMode 模式
             usChan 要获得其对应下行频点的某频点
 输出参数  : 无
 返 回 值  : 对应的下行频点, 返回65535为无效值
*****************************************************************************/
VOS_UINT16 at_ftm_get_ulchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan)
{
    VOS_UINT16 i         =  0;
    VOS_UINT16 usUlChan  =  65535;
    VOS_UINT16 usTblSize = 0;

    if(emMode == EN_FCHAN_MODE_TD_SCDMA)
    {
        usUlChan = usChan;
    }
    else
    {
        usTblSize = sizeof(g_stBandInfo)/sizeof(FTM_BAND_INFO_STRU);
        for(i=1; i<usTblSize; i++)
        {
            /* 判断该频点是否为某频段下行频点，如果为下行频点则计算对应的上行频点 */
            if((usChan>=g_stBandInfo[i].usDlLowChan)
                && (usChan<=g_stBandInfo[i].usDlHigChan))
            {
                usUlChan = g_stBandInfo[i].usUlLowChan + usChan - g_stBandInfo[i].usDlLowChan;
                break;
            }

            /* 判断该频点是否为某频段的上行频点，如果为上行频点则直接返回该频点*/
            if((usChan>=g_stBandInfo[i].usUlLowChan)
                && usChan<=g_stBandInfo[i].usUlHigChan)
            {
                usUlChan = usChan;
                break;
            }
        }
    }

    return usUlChan;
}

/*****************************************************************************
 函 数 名  : at_ftm_get_dlchan
 功能描述  : 通过某频点获得其对应的下行频点
 输入参数  : emMode 模式
             usChan 要获得其对应上行频点的某频点
 输出参数  : 无
 返 回 值  : 对应的下行频点, 返回65535为无效值
*****************************************************************************/
VOS_UINT16 at_ftm_get_dlchan(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan)
{
    VOS_UINT16 i         = 0;
    VOS_UINT16 usDlChan  = 65535;
    VOS_UINT16 usTblSize = 0;

    if(emMode == EN_FCHAN_MODE_TD_SCDMA) /* TDS */
    {
        usDlChan = usChan;
    }
    else                                 /* LTE */
    {
        usTblSize = sizeof(g_stBandInfo)/sizeof(FTM_BAND_INFO_STRU);
        for(i=1; i<usTblSize; i++)
        {
            /* 判断该频点是否为某频段下行频点，如果为下行频点则直接返回该频点 */
            if((usChan>=g_stBandInfo[i].usDlLowChan)
                && (usChan<=g_stBandInfo[i].usDlHigChan))
            {
                usDlChan = usChan;
                break;
            }

            /* 判断该频点是否为某频段的上行频点，如果为上行频点则计算对应的下行频点 */
            if((usChan>=g_stBandInfo[i].usUlLowChan)
                && (usChan<=g_stBandInfo[i].usUlHigChan))
            {
                usDlChan = g_stBandInfo[i].usDlLowChan + usChan - g_stBandInfo[i].usUlLowChan;
                break;
            }
        }
    }

    return usDlChan;
}

/*****************************************************************************
 函 数 名  : at_ftm_get_freq
 功能描述  : 通过某频点获得其对应的实际频率值(LTE单位100KHz, TDS单位为200Khz)
 输入参数  : emMode 模式 (LTE TDS)
             usChan 频点
 输出参数  : 无
 返 回 值  : 频率值, 返回0代表未找到对应的频点
*****************************************************************************/
VOS_UINT16 at_ftm_get_freq(FCHAN_MODE_ENUM emMode, VOS_UINT16 usChan)
{
    VOS_UINT16 usFreq  = 0;

    VOS_UINT16 i         = 0;
    VOS_UINT16 usTblSize = 0;

    VOS_UINT32 ulNvId =0,ulRet =0;
    LTE_COMM_NON_STANDARD_BAND_COMM_STRU stLpsNonstandBand = {0};

    /* TDS */
    if(EN_FCHAN_MODE_TD_SCDMA == emMode)
    {
        HAL_SDMLOG(" TDS, get freq  = %d!\n",usChan);
        return  usChan;
    }

    /* LTE */
    usTblSize = sizeof(g_stBandInfo)/sizeof(FTM_BAND_INFO_STRU);
    for(i=1; i<usTblSize; i++)
    {
        /* 判断该频点是否为某频段下行频点，如果为下行频点则计算该频点的频率 */
        if((usChan>=g_stBandInfo[i].usDlLowChan)
            && (usChan<=g_stBandInfo[i].usDlHigChan))
        {
            usFreq = g_stBandInfo[i].usDlLowFreq + usChan - g_stBandInfo[i].usDlLowChan;
            return usFreq;
        }

        /* 判断该频点是否为某频段的上行频点，如果为上行频点则计算该频点的频率 */
        if((usChan>=g_stBandInfo[i].usUlLowChan)
            && (usChan<=g_stBandInfo[i].usUlHigChan))
        {
            usFreq = g_stBandInfo[i].usUlLowFreq + usChan - g_stBandInfo[i].usUlLowChan;
            return usFreq;
        }
    }

    /* 搜索非标频段, 搜索到则将非标频点转换为频率 */
    for(i=0; i<(LTE_COMM_NONSTANDARD_BAND_END-LTE_COMM_NONSTANDARD_BAND_BEGIN); i++)
    {
		ulNvId = i + EN_NV_ID_BANDNon1_BAND_INFO  ;
	    ulRet  = NVM_Read(ulNvId, (VOS_VOID*) &stLpsNonstandBand, sizeof(LTE_COMM_NON_STANDARD_BAND_COMM_STRU));

		if(ERR_FTM_SUCCESS != ulRet)
		{
		   HAL_SDMLOG("read non stand band nv fail,ulNvId =%d!\n",ulNvId);
		   return 0;
		}

        if((usChan >= stLpsNonstandBand.stDlFreqInfo.usRangOfNLow) &&
            (usChan <= stLpsNonstandBand.stDlFreqInfo.usRangOfNHigh))
        {
        	usFreq = (VOS_UINT16)(stLpsNonstandBand.stDlFreqInfo.usFLow+usChan-stLpsNonstandBand.stDlFreqInfo.usRangOfNLow);
			HAL_SDMLOG("stDlFreqInfo:usGetReq = %d!\n", usFreq);
			return usFreq;
        }

	    if((usChan >= stLpsNonstandBand.stUlFreqInfo.usRangOfNLow) &&
            (usChan <= stLpsNonstandBand.stUlFreqInfo.usRangOfNHigh))
        {
        	usFreq = (VOS_UINT16)(stLpsNonstandBand.stUlFreqInfo.usFLow+usChan-stLpsNonstandBand.stUlFreqInfo.usRangOfNLow);
			HAL_SDMLOG("stUlFreqInfo:usGetReq = %d!\n", usFreq);
			return usFreq;
        }
    }

    return 0;
}


