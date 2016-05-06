/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmaMmcInterface.h
  Description : TAF与MMC接口头文件
  History     :
      1.  张志勇   2003.11.26   新版作成
      2.  刘飏     2005.11.20   增加3个消息结构，RSSI，SPECIALIZE PLMN REQ,
                                SPECIALIZE PLMN CNF, 修改TAF SERVICE STATUS IND

      3.日    期   : 2006年8月4日
        作    者   : liuyang id:48197
        修改内容   : 根据问题单号：A32D05223
      4.日    期   : 2007年5月22日
        作    者   : Li Jilin 60827
        修改内容   : A32D11131
      5.日    期   : 2007年7月20日
        作    者   : Li Jilin 60827
        修改内容   : A32D12536
      6.日    期   : 2007年09月30日
        作    者   : luojian id:107747
        修改内容   : A32D12980
      7.日    期   : 2008年3月17日
        作    者   : s46746
        修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
      8.日    期   : 2008年4月22日
        作    者   : s46746
        修改内容   : 问题单号:AT2D02941,小区被Bar后，进行GMM Attach没有响应
      9.日    期   : 2008年06月20日
        作    者   : l00107747
        修改内容   : 问题单号:AT2D03832,修改MMC和TAF卡状态上报接口
     10.日    期   : 2009年07月07日
        作    者   : h44270
        修改内容   : 问题单号：AT2D12792，不能显示EGPRS小区信息
     11.日    期   : 2009年11月28日
        作    者   : s46746
        修改内容   : 问题单号：AT2D15677,澳大利亚漫游定制合入
     12.日    期   : 2011年04月23日
        作    者   : L00171473
        修改内容   : for V7R1 porting, 去掉枚举成员最后的逗号，避免编译WARNING
*******************************************************************************/

#ifndef _TAF_MMC_INTERFACE_H_
#define _TAF_MMC_INTERFACE_H_

#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "TafAppMma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#pragma pack(4)

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
#define TAFMMC_CBS_NO_NETWORK_IND       (1)
#define TAFMMC_CBS_CURR_NET_MODE_IND    (2)

#define TAFMMC_APS_SERVICE_STATE_IND    (3)

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
}TAFMMC_CBS_NO_NETWORK_IND_STRU;


/* MMC发送给MSG模块的当前网络模式消息 */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT8                           ucCurNetWork;                           /* 当前接入模式 */
    VOS_UINT8                           aucReserve[3];
}TAFMMC_CBS_CURR_NET_MODE_IND_STRU;
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-8, end */


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
