#ifndef __MDRV_MSP_SLEEP_COMMON_H__
#define __MDRV_MSP_SLEEP_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_pm_common.h"

#define SLAVE_MODE_BUTT (PWC_COMM_MODE_NUMBER)

enum MasterMode_Enum
{
    MASTER_MODE_LTE = 0,
    MASTER_MODE_TDS = 1,
    MASTER_MODE_BUTT
};

struct MasterAwakeSlaveFlag
{
    unsigned int SlaveAwakeFlag[MASTER_MODE_BUTT][SLAVE_MODE_BUTT];
};

struct DspDvsFlag
{
    unsigned int DspDvsReq;            /*bit0-bit7:BBP调压请求 01高压 00低压;bit8-bit15:BBE16调压请求 01高压 00低压;
                                         bit16-bit23:请求序列号(由BBE16产生);bit24-bit31:调压请求有效标志(0x55)*/
    unsigned int DspDvsReq_timestamp;   
    unsigned int DspDvsRespond;        /*bit0-bit7:BBP电压状态 01高压 00低压;bit8-bit15:BBE16电压状态 01高压 00低压;
                                         bit16-bit23:调压应答序列号(等于调压请求序列号);bit24-bit31:调压应答有效标志(0xAA)*/   
    unsigned int DspDvsRespond_timestamp;
};

typedef struct
{
    unsigned int ulLightSleepFlag;    /*DSP深睡浅睡的标志*/
    unsigned int ulTdsPreSfn;         /*DSP锁存的子贞号*/
    unsigned int ulRfTime;            /*RF稳定时间需要1ms*/
    unsigned int dspState;            /*DSP是睡眠还是醒，0:睡 1:醒*/
    unsigned int dspTime;            	/*DSP对应着dspState打的时间戳*/
    unsigned int ulReserved[3];
}RTT_SLEEP_INFO_STRU;

typedef struct{
    RTT_SLEEP_INFO_STRU PstRttSleepInfo;     /* 由于物理层是通过首地址偏移方式使用该结构，所以如果要调整该结构及其内部成员顺序，请知会物理层同事 */
    struct DspDvsFlag DvsFlag;
    struct MasterAwakeSlaveFlag AwakeFlag;
}SRAM_SOC_TLDSP_INTERACTION_STRU;

#ifdef __cplusplus
}
#endif
#endif
  
