/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_cdma_on_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:35:28
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_CDMA_ON.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_CDMA_ON_INTERFACE_H__
#define __BBP_CDMA_ON_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_c_drx
 ***======================================================================***/
/* 寄存器说明：
 bit[31:21]  保留
 bit[20:16]  时钟测量结果整数部分对25取模的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。
 bit[15:11]  保留
 bit[10:0]   时钟测量结果整数部分除以25的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。
   UNION结构:  CBBP_CK_MSR_INTERGER_1X_UNION */
#define CBBP_CK_MSR_INTERGER_1X_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E00)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   时钟测量结果小数部分。精度为1/2048。
   UNION结构:  CBBP_CK_MSR_FRAC_1X_UNION */
#define CBBP_CK_MSR_FRAC_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E04)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   睡眠时间：从开始睡眠到唤醒时刻的时间。配置32k时钟个数
   UNION结构:  CBBP_SLEEP_PERIOD_1X_UNION */
#define CBBP_SLEEP_PERIOD_1X_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E08)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   正常唤醒时，从wakeup中断，到切换系统定时之间的时间。配置为32k时钟个数。最大值对应时长62.5ms。
   UNION结构:  CBBP_CK_SWITCH_CNT_1X_UNION */
#define CBBP_CK_SWITCH_CNT_1X_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E0C)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   距离wakeup时刻还有多长时间，BBP产生深睡指示。配置为32k时钟个数。
   UNION结构:  CBBP_DEEP_SLEEP_CNT_1X_UNION */
#define CBBP_DEEP_SLEEP_CNT_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E10)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      进入睡眠的模式。
             0：表示立即睡眠
             1：表示到达指定时刻再进入睡眠
             
   UNION结构:  CBBP_SLEEP_MODE_UNION */
#define CBBP_SLEEP_MODE_ADDR                          (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E14)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   软件指定的进入睡眠的时刻，Sleep_mode=1时有效。
             [29:24]，sys_cnt_1x_5p12s的值；
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms的值，chip精度；
             
   UNION结构:  CBBP_SLEEP_TIME_1X_UNION */
#define CBBP_SLEEP_TIME_1X_ADDR                       (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E18)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件配置的睡眠指令，脉冲信号。 Sleep_mode=0时，立即进入睡眠；Sleep_mode=1时，等待配置的时刻进入睡眠
   UNION结构:  CBBP_SLEEP_START_1X_UNION */
#define CBBP_SLEEP_START_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E1C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      强制唤醒指令，脉冲信号。
   UNION结构:  CBBP_SWITCH_UP_1X_UNION */
#define CBBP_SWITCH_UP_1X_ADDR                        (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E20)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      深睡指示，1有效
   UNION结构:  CBBP_DEEP_SLEEP_IND_1X_UNION */
#define CBBP_DEEP_SLEEP_IND_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E24)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   上报的睡眠时间，用32k时钟周期个数表示。
   UNION结构:  CBBP_SLEEP_CNT_32K_1X_UNION */
#define CBBP_SLEEP_CNT_32K_1X_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E28)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      唤醒种类。
             0：表示自然唤醒；
             1：表示强制唤醒
             
   UNION结构:  CBBP_WAKEUP_TYPE_1X_UNION */
#define CBBP_WAKEUP_TYPE_1X_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E2C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP处于睡眠状态指示。从sleep_start开始到int_32k_to_sys期间为1，其他时间为0。
   UNION结构:  CBBP_SLEEP_STATUS_1X_UNION */
#define CBBP_SLEEP_STATUS_1X_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E30)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      sys cnt周期选择
             0表示2s
             1表示5.12s
   UNION结构:  CBBP_SYS_CNT_PERIOD_1X_UNION */
#define CBBP_SYS_CNT_PERIOD_1X_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E34)

/* 寄存器说明：
 bit[31]     上报bbe16唤醒中断的使能
 bit[30:10]  保留
 bit[9:8]    上报bbe16唤醒中断的clr
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
 bit[7:2]    保留
 bit[1:0]    上报bbe16唤醒中断的mask，1表示屏蔽相应的中断
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
   UNION结构:  CBBP_WAKEUP_INT_BBE16_UNION */
#define CBBP_WAKEUP_INT_BBE16_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E50)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上报bbe16唤醒中断的sta，1表示相应的中断有效
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
   UNION结构:  CBBP_WAKEUP_INT_STA_BBE16_UNION */
#define CBBP_WAKEUP_INT_STA_BBE16_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E54)

/* 寄存器说明：
 bit[31]     上报arm唤醒中断的使能
 bit[30:10]  保留
 bit[9:8]    上报arm唤醒中断的clr
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
 bit[7:2]    保留
 bit[1:0]    上报arm唤醒中断的mask，1表示屏蔽相应的中断
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
   UNION结构:  CBBP_WAKEUP_INT_ARM_UNION */
#define CBBP_WAKEUP_INT_ARM_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E58)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    上报arm唤醒中断的sta，1表示相应的中断
             bit0：1x唤醒中断，
             bit1：evdo唤醒中断
   UNION结构:  CBBP_WAKEUP_INT_STA_ARM_UNION */
#define CBBP_WAKEUP_INT_STA_ARM_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E5C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      自然唤醒流程中，软件已经准备好接收时钟切换中断
   UNION结构:  CBBP_DSP_READY_IND_CDRX_1X_UNION */
#define CBBP_DSP_READY_IND_CDRX_1X_ADDR               (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E60)

/* 寄存器说明：
   详      述：预定时钟切换中断后，等待最长多少个32k时钟后再产生时钟切换中断
   UNION结构 ：无 */
#define CBBP_DSP_SWITCH_DELAY_MAX_1X_ADDR             (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E64)

/* 寄存器说明：
   详      述：预定时钟切换中断后，等待了多长时间再产生时钟切换中断
   UNION结构 ：无 */
#define CBBP_SWITCH_DELAY_CNT_1X_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E68)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:16]  时钟测量结果整数部分对25取模的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。
 bit[15:11]  保留
 bit[10:0]   时钟测量结果整数部分除以25的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。
   UNION结构:  CBBP_CK_MSR_INTERGER_EVDO_UNION */
#define CBBP_CK_MSR_INTERGER_EVDO_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E80)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   时钟测量结果小数部分。精度为1/2048。
   UNION结构:  CBBP_CK_MSR_FRAC_EVDO_UNION */
#define CBBP_CK_MSR_FRAC_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E84)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   睡眠时间：从开始睡眠到唤醒时刻的时间。配置32k时钟个数
   UNION结构:  CBBP_SLEEP_PERIOD_EVDO_UNION */
#define CBBP_SLEEP_PERIOD_EVDO_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E88)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   正常唤醒时，从wakeup中断，到切换系统定时之间的时间。配置为32k时钟个数。最大值对应时长62.5ms。
   UNION结构:  CBBP_CK_SWITCH_CNT_EVDO_UNION */
#define CBBP_CK_SWITCH_CNT_EVDO_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E8C)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   距离wakeup时刻还有多长时间，BBP产生深睡指示。配置为32k时钟个数。
   UNION结构:  CBBP_DEEP_SLEEP_CNT_EVDO_UNION */
#define CBBP_DEEP_SLEEP_CNT_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E90)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      进入睡眠的模式。
             0：表示立即睡眠
             1：表示到达指定时刻再进入睡眠
             
   UNION结构:  CBBP_SLEEP_MODE_EVDO_UNION */
#define CBBP_SLEEP_MODE_EVDO_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E94)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   软件指定的进入睡眠的时刻，Sleep_mode=1时有效。
             [29:24]，sys_cnt_evdo_5p12s的值；
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值；
   UNION结构:  CBBP_SLEEP_TIME_EVDO_UNION */
#define CBBP_SLEEP_TIME_EVDO_ADDR                     (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E98)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件配置的睡眠指令，脉冲信号。 Sleep_mode=0时，立即进入睡眠；Sleep_mode=1时，等待配置的时刻进入睡眠
   UNION结构:  CBBP_SLEEP_START_EVDO_UNION */
#define CBBP_SLEEP_START_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1E9C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      强制唤醒指令，脉冲信号。
   UNION结构:  CBBP_SWITCH_UP_EVDO_UNION */
#define CBBP_SWITCH_UP_EVDO_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA0)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      深睡指示，1有效
   UNION结构:  CBBP_DEEP_SLEEP_IND_EVDO_UNION */
#define CBBP_DEEP_SLEEP_IND_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA4)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:0]   上报的睡眠时间，用32k时钟周期个数表示。
   UNION结构:  CBBP_SLEEP_CNT_32K_EVDO_UNION */
#define CBBP_SLEEP_CNT_32K_EVDO_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EA8)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      唤醒种类。
             0：表示自然唤醒；
             1：表示强制唤醒
             
   UNION结构:  CBBP_WAKEUP_TYPE_EVDO_UNION */
#define CBBP_WAKEUP_TYPE_EVDO_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EAC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBP处于睡眠状态指示。从sleep_start开始到int_32k_to_sys期间为1，其他时间为0。
   UNION结构:  CBBP_SLEEP_STATUS_EVDO_UNION */
#define CBBP_SLEEP_STATUS_EVDO_ADDR                   (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EB0)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      sys cnt周期选择
             0表示2s
             1表示5.12s
   UNION结构:  CBBP_SYS_CNT_PERIOD_EVDO_UNION */
#define CBBP_SYS_CNT_PERIOD_EVDO_ADDR                 (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EB4)

/* 寄存器说明：
 bit[31]     上报bbe16时钟切换中断的使能
 bit[30:12]  保留
 bit[11:8]   上报bbe16时钟切换中断的clr
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
 bit[7:4]    保留
 bit[3:0]    上报bbe16时钟切换中断的mask，1表示屏蔽相应的中断
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
   UNION结构:  CBBP_SWITCH_INT_BBE16_UNION */
#define CBBP_SWITCH_INT_BBE16_ADDR                    (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED0)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    上报bbe16时钟切换中断的sta，1表示相应的中断
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
   UNION结构:  CBBP_SWITCH_INT_STA_BBE16_UNION */
#define CBBP_SWITCH_INT_STA_BBE16_ADDR                (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED4)

/* 寄存器说明：
 bit[31]     上报arm时钟切换中断的使能
 bit[30:12]  保留
 bit[11:8]   上报arm时钟切换中断的clr
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
 bit[7:4]    保留
 bit[3:0]    上报arm时钟切换中断的mask，1表示屏蔽相应的中断
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
   UNION结构:  CBBP_SWITCH_INT_ARM_UNION */
#define CBBP_SWITCH_INT_ARM_ADDR                      (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1ED8)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    上报arm时钟切换中断的STA，1表示相应的中断
             bit0：1x唤醒时系统定时从32k切换到122M，
             bit1：1x睡眠时系统定时从122M切换到32k
             bit2：evdo唤醒时系统定时从32k切换到122M，
             bit3：evdo睡眠时系统定时从122M切换到32k
   UNION结构:  CBBP_SWITCH_INT_STA_ARM_UNION */
#define CBBP_SWITCH_INT_STA_ARM_ADDR                  (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EDC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      自然唤醒流程中，软件已经准备好接收时钟切换中断
   UNION结构:  CBBP_DSP_READY_IND_CDRX_EVDO_UNION */
#define CBBP_DSP_READY_IND_CDRX_EVDO_ADDR             (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE0)

/* 寄存器说明：
   详      述：预定时钟切换中断后，等待最长多少个32k时钟后再产生时钟切换中断
   UNION结构 ：无 */
#define CBBP_DSP_SWITCH_DELAY_MAX_EVDO_ADDR           (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE4)

/* 寄存器说明：
   详      述：预定时钟切换中断后，等待了多长时间再产生时钟切换中断
   UNION结构 ：无 */
#define CBBP_SWITCH_DELAY_CNT_EVDO_ADDR               (SOC_BBP_CDMA_ON_BASE_ADDR + 0x1EE8)





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_c_drx
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_CK_MSR_INTERGER_1X_UNION
 结构说明  : CK_MSR_INTERGER_1X 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_interger_1x_reg;
    struct
    {
        unsigned long  ck_msr_integer_26ms_1x    : 11; /* bit[0-10] : 时钟测量结果整数部分除以25的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。 */
        unsigned long  reserved_0                : 5;  /* bit[11-15]: 保留 */
        unsigned long  ck_msr_integer_1_4chip_1x : 5;  /* bit[16-20]: 时钟测量结果整数部分对25取模的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。 */
        unsigned long  reserved_1                : 11; /* bit[21-31]: 保留 */
    } reg;
} CBBP_CK_MSR_INTERGER_1X_UNION;
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_26ms_1x_START     (0)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_26ms_1x_END       (10)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_1_4chip_1x_START  (16)
#define CBBP_CK_MSR_INTERGER_1X_ck_msr_integer_1_4chip_1x_END    (20)


/*****************************************************************************
 结构名    : CBBP_CK_MSR_FRAC_1X_UNION
 结构说明  : CK_MSR_FRAC_1X 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_1x_reg;
    struct
    {
        unsigned long  ck_msr_frac_1x : 11; /* bit[0-10] : 时钟测量结果小数部分。精度为1/2048。 */
        unsigned long  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_CK_MSR_FRAC_1X_UNION;
#define CBBP_CK_MSR_FRAC_1X_ck_msr_frac_1x_START  (0)
#define CBBP_CK_MSR_FRAC_1X_ck_msr_frac_1x_END    (10)


/*****************************************************************************
 结构名    : CBBP_SLEEP_PERIOD_1X_UNION
 结构说明  : SLEEP_PERIOD_1X 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_period_1x_reg;
    struct
    {
        unsigned long  sleep_period_1x : 23; /* bit[0-22] : 睡眠时间：从开始睡眠到唤醒时刻的时间。配置32k时钟个数 */
        unsigned long  reserved        : 9;  /* bit[23-31]: 保留 */
    } reg;
} CBBP_SLEEP_PERIOD_1X_UNION;
#define CBBP_SLEEP_PERIOD_1X_sleep_period_1x_START  (0)
#define CBBP_SLEEP_PERIOD_1X_sleep_period_1x_END    (22)


/*****************************************************************************
 结构名    : CBBP_CK_SWITCH_CNT_1X_UNION
 结构说明  : CK_SWITCH_CNT_1X 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_1x_reg;
    struct
    {
        unsigned long  ck_switch_cnt_1x : 12; /* bit[0-11] : 正常唤醒时，从wakeup中断，到切换系统定时之间的时间。配置为32k时钟个数。最大值对应时长62.5ms。 */
        unsigned long  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_CK_SWITCH_CNT_1X_UNION;
#define CBBP_CK_SWITCH_CNT_1X_ck_switch_cnt_1x_START  (0)
#define CBBP_CK_SWITCH_CNT_1X_ck_switch_cnt_1x_END    (11)


/*****************************************************************************
 结构名    : CBBP_DEEP_SLEEP_CNT_1X_UNION
 结构说明  : DEEP_SLEEP_CNT_1X 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_cnt_1x_reg;
    struct
    {
        unsigned long  deep_sleep_cnt_1x : 12; /* bit[0-11] : 距离wakeup时刻还有多长时间，BBP产生深睡指示。配置为32k时钟个数。 */
        unsigned long  reserved          : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_DEEP_SLEEP_CNT_1X_UNION;
#define CBBP_DEEP_SLEEP_CNT_1X_deep_sleep_cnt_1x_START  (0)
#define CBBP_DEEP_SLEEP_CNT_1X_deep_sleep_cnt_1x_END    (11)


/*****************************************************************************
 结构名    : CBBP_SLEEP_MODE_UNION
 结构说明  : SLEEP_MODE 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_mode_reg;
    struct
    {
        unsigned long  sleep_mode_1x : 1;  /* bit[0]   : 进入睡眠的模式。
                                                         0：表示立即睡眠
                                                         1：表示到达指定时刻再进入睡眠 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_MODE_UNION;
#define CBBP_SLEEP_MODE_sleep_mode_1x_START  (0)
#define CBBP_SLEEP_MODE_sleep_mode_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_TIME_1X_UNION
 结构说明  : SLEEP_TIME_1X 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_time_1x_reg;
    struct
    {
        unsigned long  sleep_time_1x_1p25ms : 11; /* bit[0-10] : 软件指定的进入睡眠的时刻，Sleep_mode=1时有效。
                                                                 [29:24]，sys_cnt_1x_5p12s的值；
                                                                 [21:16]，sys_cnt_1x_80ms的值；
                                                                 [10:0]，sys_cnt_1x_1p25ms的值，chip精度； */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned long  sleep_time_1x_80ms   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1           : 2;  /* bit[22-23]: 保留 */
        unsigned long  sleep_time_1x_5p12s  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2           : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_ON_SLEEP_TIME_1X_UNION;
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_START  (0)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_END    (10)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_START    (16)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_END      (21)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_START   (24)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_END     (29)


/*****************************************************************************
 结构名    : CBBP_SLEEP_START_1X_UNION
 结构说明  : SLEEP_START_1X 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_start_1x_reg;
    struct
    {
        unsigned long  sleep_start_1x : 1;  /* bit[0]   : 软件配置的睡眠指令，脉冲信号。 Sleep_mode=0时，立即进入睡眠；Sleep_mode=1时，等待配置的时刻进入睡眠 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_START_1X_UNION;
#define CBBP_SLEEP_START_1X_sleep_start_1x_START  (0)
#define CBBP_SLEEP_START_1X_sleep_start_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SWITCH_UP_1X_UNION
 结构说明  : SWITCH_UP_1X 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_1x_reg;
    struct
    {
        unsigned long  switch_up_1x : 1;  /* bit[0]   : 强制唤醒指令，脉冲信号。 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SWITCH_UP_1X_UNION;
#define CBBP_SWITCH_UP_1X_switch_up_1x_START  (0)
#define CBBP_SWITCH_UP_1X_switch_up_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_DEEP_SLEEP_IND_1X_UNION
 结构说明  : DEEP_SLEEP_IND_1X 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_1x_reg;
    struct
    {
        unsigned long  deep_sleep_ind_1x : 1;  /* bit[0]   : 深睡指示，1有效 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DEEP_SLEEP_IND_1X_UNION;
#define CBBP_DEEP_SLEEP_IND_1X_deep_sleep_ind_1x_START  (0)
#define CBBP_DEEP_SLEEP_IND_1X_deep_sleep_ind_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_CNT_32K_1X_UNION
 结构说明  : SLEEP_CNT_32K_1X 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_cnt_32k_1x_reg;
    struct
    {
        unsigned long  sleep_cnt_32k_1x : 23; /* bit[0-22] : 上报的睡眠时间，用32k时钟周期个数表示。 */
        unsigned long  reserved         : 9;  /* bit[23-31]: 保留 */
    } reg;
} CBBP_SLEEP_CNT_32K_1X_UNION;
#define CBBP_SLEEP_CNT_32K_1X_sleep_cnt_32k_1x_START  (0)
#define CBBP_SLEEP_CNT_32K_1X_sleep_cnt_32k_1x_END    (22)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_TYPE_1X_UNION
 结构说明  : WAKEUP_TYPE_1X 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_type_1x_reg;
    struct
    {
        unsigned long  wakeup_type_1x : 1;  /* bit[0]   : 唤醒种类。
                                                          0：表示自然唤醒；
                                                          1：表示强制唤醒 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_WAKEUP_TYPE_1X_UNION;
#define CBBP_WAKEUP_TYPE_1X_wakeup_type_1x_START  (0)
#define CBBP_WAKEUP_TYPE_1X_wakeup_type_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_STATUS_1X_UNION
 结构说明  : SLEEP_STATUS_1X 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_status_1x_reg;
    struct
    {
        unsigned long  sleep_status_1x : 1;  /* bit[0]   : BBP处于睡眠状态指示。从sleep_start开始到int_32k_to_sys期间为1，其他时间为0。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_STATUS_1X_UNION;
#define CBBP_SLEEP_STATUS_1X_sleep_status_1x_START  (0)
#define CBBP_SLEEP_STATUS_1X_sleep_status_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_PERIOD_1X_UNION
 结构说明  : SYS_CNT_PERIOD_1X 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_period_1x_reg;
    struct
    {
        unsigned long  sys_cnt_period_1x : 1;  /* bit[0]   : sys cnt周期选择
                                                             0表示2s
                                                             1表示5.12s */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_PERIOD_1X_UNION;
#define CBBP_SYS_CNT_PERIOD_1X_sys_cnt_period_1x_START  (0)
#define CBBP_SYS_CNT_PERIOD_1X_sys_cnt_period_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_INT_BBE16_UNION
 结构说明  : WAKEUP_INT_BBE16 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int01_mask_bbe16 : 2;  /* bit[0-1]  : 上报bbe16唤醒中断的mask，1表示屏蔽相应的中断
                                                                  bit0：1x唤醒中断，
                                                                  bit1：evdo唤醒中断 */
        unsigned long  reserved_0            : 6;  /* bit[2-7]  : 保留 */
        unsigned long  cbbp_int01_clr_bbe16  : 2;  /* bit[8-9]  : 上报bbe16唤醒中断的clr
                                                                  bit0：1x唤醒中断，
                                                                  bit1：evdo唤醒中断 */
        unsigned long  reserved_1            : 21; /* bit[10-30]: 保留 */
        unsigned long  cbbp_int01_en_bbe16   : 1;  /* bit[31]   : 上报bbe16唤醒中断的使能 */
    } reg;
} CBBP_WAKEUP_INT_BBE16_UNION;
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_mask_bbe16_START  (0)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_mask_bbe16_END    (1)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_clr_bbe16_START   (8)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_clr_bbe16_END     (9)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_en_bbe16_START    (31)
#define CBBP_WAKEUP_INT_BBE16_cbbp_int01_en_bbe16_END      (31)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_INT_STA_BBE16_UNION
 结构说明  : WAKEUP_INT_STA_BBE16 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_sta_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int01_sta_bbe16 : 2;  /* bit[0-1] : 上报bbe16唤醒中断的sta，1表示相应的中断有效
                                                                bit0：1x唤醒中断，
                                                                bit1：evdo唤醒中断 */
        unsigned long  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_WAKEUP_INT_STA_BBE16_UNION;
#define CBBP_WAKEUP_INT_STA_BBE16_cbbp_int01_sta_bbe16_START  (0)
#define CBBP_WAKEUP_INT_STA_BBE16_cbbp_int01_sta_bbe16_END    (1)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_INT_ARM_UNION
 结构说明  : WAKEUP_INT_ARM 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_arm_reg;
    struct
    {
        unsigned long  cbbp_int01_mask_arm : 2;  /* bit[0-1]  : 上报arm唤醒中断的mask，1表示屏蔽相应的中断
                                                                bit0：1x唤醒中断，
                                                                bit1：evdo唤醒中断 */
        unsigned long  reserved_0          : 6;  /* bit[2-7]  : 保留 */
        unsigned long  cbbp_int01_clr_arm  : 2;  /* bit[8-9]  : 上报arm唤醒中断的clr
                                                                bit0：1x唤醒中断，
                                                                bit1：evdo唤醒中断 */
        unsigned long  reserved_1          : 21; /* bit[10-30]: 保留 */
        unsigned long  cbbp_int01_en_arm   : 1;  /* bit[31]   : 上报arm唤醒中断的使能 */
    } reg;
} CBBP_WAKEUP_INT_ARM_UNION;
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_mask_arm_START  (0)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_mask_arm_END    (1)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_clr_arm_START   (8)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_clr_arm_END     (9)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_en_arm_START    (31)
#define CBBP_WAKEUP_INT_ARM_cbbp_int01_en_arm_END      (31)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_INT_STA_ARM_UNION
 结构说明  : WAKEUP_INT_STA_ARM 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_int_sta_arm_reg;
    struct
    {
        unsigned long  cbbp_int01_sta_arm : 2;  /* bit[0-1] : 上报arm唤醒中断的sta，1表示相应的中断
                                                              bit0：1x唤醒中断，
                                                              bit1：evdo唤醒中断 */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_WAKEUP_INT_STA_ARM_UNION;
#define CBBP_WAKEUP_INT_STA_ARM_cbbp_int01_sta_arm_START  (0)
#define CBBP_WAKEUP_INT_STA_ARM_cbbp_int01_sta_arm_END    (1)


/*****************************************************************************
 结构名    : CBBP_DSP_READY_IND_CDRX_1X_UNION
 结构说明  : DSP_READY_IND_CDRX_1X 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_cdrx_1x_reg;
    struct
    {
        unsigned long  dsp_ready_ind_cdrx_1x : 1;  /* bit[0]   : 自然唤醒流程中，软件已经准备好接收时钟切换中断 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DSP_READY_IND_CDRX_1X_UNION;
#define CBBP_DSP_READY_IND_CDRX_1X_dsp_ready_ind_cdrx_1x_START  (0)
#define CBBP_DSP_READY_IND_CDRX_1X_dsp_ready_ind_cdrx_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_CK_MSR_INTERGER_EVDO_UNION
 结构说明  : CK_MSR_INTERGER_EVDO 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_interger_evdo_reg;
    struct
    {
        unsigned long  ck_msr_integer_26ms_evdo    : 11; /* bit[0-10] : 时钟测量结果整数部分除以25的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。 */
        unsigned long  reserved_0                  : 5;  /* bit[11-15]: 保留 */
        unsigned long  ck_msr_integer_1_4chip_evdo : 5;  /* bit[16-20]: 时钟测量结果整数部分对25取模的结果。时钟测量结果整数部分表示1个32k时钟内，有多少个122.88MHz时钟。 */
        unsigned long  reserved_1                  : 11; /* bit[21-31]: 保留 */
    } reg;
} CBBP_CK_MSR_INTERGER_EVDO_UNION;
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_26ms_evdo_START     (0)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_26ms_evdo_END       (10)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_1_4chip_evdo_START  (16)
#define CBBP_CK_MSR_INTERGER_EVDO_ck_msr_integer_1_4chip_evdo_END    (20)


/*****************************************************************************
 结构名    : CBBP_CK_MSR_FRAC_EVDO_UNION
 结构说明  : CK_MSR_FRAC_EVDO 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_frac_evdo_reg;
    struct
    {
        unsigned long  ck_msr_frac_evdo : 11; /* bit[0-10] : 时钟测量结果小数部分。精度为1/2048。 */
        unsigned long  reserved         : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_CK_MSR_FRAC_EVDO_UNION;
#define CBBP_CK_MSR_FRAC_EVDO_ck_msr_frac_evdo_START  (0)
#define CBBP_CK_MSR_FRAC_EVDO_ck_msr_frac_evdo_END    (10)


/*****************************************************************************
 结构名    : CBBP_SLEEP_PERIOD_EVDO_UNION
 结构说明  : SLEEP_PERIOD_EVDO 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_period_evdo_reg;
    struct
    {
        unsigned long  sleep_period_evdo : 23; /* bit[0-22] : 睡眠时间：从开始睡眠到唤醒时刻的时间。配置32k时钟个数 */
        unsigned long  reserved          : 9;  /* bit[23-31]: 保留 */
    } reg;
} CBBP_SLEEP_PERIOD_EVDO_UNION;
#define CBBP_SLEEP_PERIOD_EVDO_sleep_period_evdo_START  (0)
#define CBBP_SLEEP_PERIOD_EVDO_sleep_period_evdo_END    (22)


/*****************************************************************************
 结构名    : CBBP_CK_SWITCH_CNT_EVDO_UNION
 结构说明  : CK_SWITCH_CNT_EVDO 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_switch_cnt_evdo_reg;
    struct
    {
        unsigned long  ck_switch_cnt_evdo : 12; /* bit[0-11] : 正常唤醒时，从wakeup中断，到切换系统定时之间的时间。配置为32k时钟个数。最大值对应时长62.5ms。 */
        unsigned long  reserved           : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_CK_SWITCH_CNT_EVDO_UNION;
#define CBBP_CK_SWITCH_CNT_EVDO_ck_switch_cnt_evdo_START  (0)
#define CBBP_CK_SWITCH_CNT_EVDO_ck_switch_cnt_evdo_END    (11)


/*****************************************************************************
 结构名    : CBBP_DEEP_SLEEP_CNT_EVDO_UNION
 结构说明  : DEEP_SLEEP_CNT_EVDO 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_cnt_evdo_reg;
    struct
    {
        unsigned long  deep_sleep_cnt_evdo : 12; /* bit[0-11] : 距离wakeup时刻还有多长时间，BBP产生深睡指示。配置为32k时钟个数。 */
        unsigned long  reserved            : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_DEEP_SLEEP_CNT_EVDO_UNION;
#define CBBP_DEEP_SLEEP_CNT_EVDO_deep_sleep_cnt_evdo_START  (0)
#define CBBP_DEEP_SLEEP_CNT_EVDO_deep_sleep_cnt_evdo_END    (11)


/*****************************************************************************
 结构名    : CBBP_SLEEP_MODE_EVDO_UNION
 结构说明  : SLEEP_MODE_EVDO 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_mode_evdo_reg;
    struct
    {
        unsigned long  sleep_mode_evdo : 1;  /* bit[0]   : 进入睡眠的模式。
                                                           0：表示立即睡眠
                                                           1：表示到达指定时刻再进入睡眠 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_MODE_EVDO_UNION;
#define CBBP_SLEEP_MODE_EVDO_sleep_mode_evdo_START  (0)
#define CBBP_SLEEP_MODE_EVDO_sleep_mode_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_TIME_EVDO_UNION
 结构说明  : SLEEP_TIME_EVDO 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_time_evdo_reg;
    struct
    {
        unsigned long  sleep_time_evdo_26ms  : 15; /* bit[0-14] : 软件指定的进入睡眠的时刻，Sleep_mode=1时有效。
                                                                  [29:24]，sys_cnt_evdo_5p12s的值；
                                                                  [17:16]，sys_cnt_evdo_80ms的值；
                                                                  [14:0]，sys_cnt_evdo_26ms的值； */
        unsigned long  reserved_0            : 1;  /* bit[15]   : 保留 */
        unsigned long  sleep_time_evdo_80ms  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1            : 6;  /* bit[18-23]: 保留 */
        unsigned long  sleep_time_evdo_5p12s : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2            : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_ON_SLEEP_TIME_EVDO_UNION;
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_START   (0)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_END     (14)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_START   (16)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_END     (17)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_START  (24)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_END    (29)


/*****************************************************************************
 结构名    : CBBP_SLEEP_START_EVDO_UNION
 结构说明  : SLEEP_START_EVDO 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_start_evdo_reg;
    struct
    {
        unsigned long  sleep_start_evdo : 1;  /* bit[0]   : 软件配置的睡眠指令，脉冲信号。 Sleep_mode=0时，立即进入睡眠；Sleep_mode=1时，等待配置的时刻进入睡眠 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_START_EVDO_UNION;
#define CBBP_SLEEP_START_EVDO_sleep_start_evdo_START  (0)
#define CBBP_SLEEP_START_EVDO_sleep_start_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SWITCH_UP_EVDO_UNION
 结构说明  : SWITCH_UP_EVDO 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_up_evdo_reg;
    struct
    {
        unsigned long  switch_up_evdo : 1;  /* bit[0]   : 强制唤醒指令，脉冲信号。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SWITCH_UP_EVDO_UNION;
#define CBBP_SWITCH_UP_EVDO_switch_up_evdo_START  (0)
#define CBBP_SWITCH_UP_EVDO_switch_up_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_DEEP_SLEEP_IND_EVDO_UNION
 结构说明  : DEEP_SLEEP_IND_EVDO 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      deep_sleep_ind_evdo_reg;
    struct
    {
        unsigned long  deep_sleep_ind_evdo : 1;  /* bit[0]   : 深睡指示，1有效 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DEEP_SLEEP_IND_EVDO_UNION;
#define CBBP_DEEP_SLEEP_IND_EVDO_deep_sleep_ind_evdo_START  (0)
#define CBBP_DEEP_SLEEP_IND_EVDO_deep_sleep_ind_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_CNT_32K_EVDO_UNION
 结构说明  : SLEEP_CNT_32K_EVDO 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_cnt_32k_evdo_reg;
    struct
    {
        unsigned long  sleep_cnt_32k_evdo : 23; /* bit[0-22] : 上报的睡眠时间，用32k时钟周期个数表示。 */
        unsigned long  reserved           : 9;  /* bit[23-31]: 保留 */
    } reg;
} CBBP_SLEEP_CNT_32K_EVDO_UNION;
#define CBBP_SLEEP_CNT_32K_EVDO_sleep_cnt_32k_evdo_START  (0)
#define CBBP_SLEEP_CNT_32K_EVDO_sleep_cnt_32k_evdo_END    (22)


/*****************************************************************************
 结构名    : CBBP_WAKEUP_TYPE_EVDO_UNION
 结构说明  : WAKEUP_TYPE_EVDO 寄存器结构定义。地址偏移量:0x00AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      wakeup_type_evdo_reg;
    struct
    {
        unsigned long  wakeup_type_evdo : 1;  /* bit[0]   : 唤醒种类。
                                                            0：表示自然唤醒；
                                                            1：表示强制唤醒 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_WAKEUP_TYPE_EVDO_UNION;
#define CBBP_WAKEUP_TYPE_EVDO_wakeup_type_evdo_START  (0)
#define CBBP_WAKEUP_TYPE_EVDO_wakeup_type_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_STATUS_EVDO_UNION
 结构说明  : SLEEP_STATUS_EVDO 寄存器结构定义。地址偏移量:0x00B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_status_evdo_reg;
    struct
    {
        unsigned long  sleep_status_evdo : 1;  /* bit[0]   : BBP处于睡眠状态指示。从sleep_start开始到int_32k_to_sys期间为1，其他时间为0。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SLEEP_STATUS_EVDO_UNION;
#define CBBP_SLEEP_STATUS_EVDO_sleep_status_evdo_START  (0)
#define CBBP_SLEEP_STATUS_EVDO_sleep_status_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_PERIOD_EVDO_UNION
 结构说明  : SYS_CNT_PERIOD_EVDO 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_period_evdo_reg;
    struct
    {
        unsigned long  sys_cnt_period_evdo : 1;  /* bit[0]   : sys cnt周期选择
                                                               0表示2s
                                                               1表示5.12s */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_PERIOD_EVDO_UNION;
#define CBBP_SYS_CNT_PERIOD_EVDO_sys_cnt_period_evdo_START  (0)
#define CBBP_SYS_CNT_PERIOD_EVDO_sys_cnt_period_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_SWITCH_INT_BBE16_UNION
 结构说明  : SWITCH_INT_BBE16 寄存器结构定义。地址偏移量:0x00D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int02_mask_bbe16 : 4;  /* bit[0-3]  : 上报bbe16时钟切换中断的mask，1表示屏蔽相应的中断
                                                                  bit0：1x唤醒时系统定时从32k切换到122M，
                                                                  bit1：1x睡眠时系统定时从122M切换到32k
                                                                  bit2：evdo唤醒时系统定时从32k切换到122M，
                                                                  bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved_0            : 4;  /* bit[4-7]  : 保留 */
        unsigned long  cbbp_int02_clr_bbe16  : 4;  /* bit[8-11] : 上报bbe16时钟切换中断的clr
                                                                  bit0：1x唤醒时系统定时从32k切换到122M，
                                                                  bit1：1x睡眠时系统定时从122M切换到32k
                                                                  bit2：evdo唤醒时系统定时从32k切换到122M，
                                                                  bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved_1            : 19; /* bit[12-30]: 保留 */
        unsigned long  cbbp_int02_en_bbe16   : 1;  /* bit[31]   : 上报bbe16时钟切换中断的使能 */
    } reg;
} CBBP_SWITCH_INT_BBE16_UNION;
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_mask_bbe16_START  (0)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_mask_bbe16_END    (3)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_clr_bbe16_START   (8)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_clr_bbe16_END     (11)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_en_bbe16_START    (31)
#define CBBP_SWITCH_INT_BBE16_cbbp_int02_en_bbe16_END      (31)


/*****************************************************************************
 结构名    : CBBP_SWITCH_INT_STA_BBE16_UNION
 结构说明  : SWITCH_INT_STA_BBE16 寄存器结构定义。地址偏移量:0x00D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_sta_bbe16_reg;
    struct
    {
        unsigned long  cbbp_int02_sta_bbe16 : 4;  /* bit[0-3] : 上报bbe16时钟切换中断的sta，1表示相应的中断
                                                                bit0：1x唤醒时系统定时从32k切换到122M，
                                                                bit1：1x睡眠时系统定时从122M切换到32k
                                                                bit2：evdo唤醒时系统定时从32k切换到122M，
                                                                bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved             : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_SWITCH_INT_STA_BBE16_UNION;
#define CBBP_SWITCH_INT_STA_BBE16_cbbp_int02_sta_bbe16_START  (0)
#define CBBP_SWITCH_INT_STA_BBE16_cbbp_int02_sta_bbe16_END    (3)


/*****************************************************************************
 结构名    : CBBP_SWITCH_INT_ARM_UNION
 结构说明  : SWITCH_INT_ARM 寄存器结构定义。地址偏移量:0x00D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_arm_reg;
    struct
    {
        unsigned long  cbbp_int02_mask_arm : 4;  /* bit[0-3]  : 上报arm时钟切换中断的mask，1表示屏蔽相应的中断
                                                                bit0：1x唤醒时系统定时从32k切换到122M，
                                                                bit1：1x睡眠时系统定时从122M切换到32k
                                                                bit2：evdo唤醒时系统定时从32k切换到122M，
                                                                bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved_0          : 4;  /* bit[4-7]  : 保留 */
        unsigned long  cbbp_int02_clr_arm  : 4;  /* bit[8-11] : 上报arm时钟切换中断的clr
                                                                bit0：1x唤醒时系统定时从32k切换到122M，
                                                                bit1：1x睡眠时系统定时从122M切换到32k
                                                                bit2：evdo唤醒时系统定时从32k切换到122M，
                                                                bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved_1          : 19; /* bit[12-30]: 保留 */
        unsigned long  cbbp_int02_en_arm   : 1;  /* bit[31]   : 上报arm时钟切换中断的使能 */
    } reg;
} CBBP_SWITCH_INT_ARM_UNION;
#define CBBP_SWITCH_INT_ARM_cbbp_int02_mask_arm_START  (0)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_mask_arm_END    (3)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_clr_arm_START   (8)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_clr_arm_END     (11)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_en_arm_START    (31)
#define CBBP_SWITCH_INT_ARM_cbbp_int02_en_arm_END      (31)


/*****************************************************************************
 结构名    : CBBP_SWITCH_INT_STA_ARM_UNION
 结构说明  : SWITCH_INT_STA_ARM 寄存器结构定义。地址偏移量:0x00DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      switch_int_sta_arm_reg;
    struct
    {
        unsigned long  cbbp_int02_sta_arm : 4;  /* bit[0-3] : 上报arm时钟切换中断的STA，1表示相应的中断
                                                              bit0：1x唤醒时系统定时从32k切换到122M，
                                                              bit1：1x睡眠时系统定时从122M切换到32k
                                                              bit2：evdo唤醒时系统定时从32k切换到122M，
                                                              bit3：evdo睡眠时系统定时从122M切换到32k */
        unsigned long  reserved           : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_SWITCH_INT_STA_ARM_UNION;
#define CBBP_SWITCH_INT_STA_ARM_cbbp_int02_sta_arm_START  (0)
#define CBBP_SWITCH_INT_STA_ARM_cbbp_int02_sta_arm_END    (3)


/*****************************************************************************
 结构名    : CBBP_DSP_READY_IND_CDRX_EVDO_UNION
 结构说明  : DSP_READY_IND_CDRX_EVDO 寄存器结构定义。地址偏移量:0x00E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_ready_ind_cdrx_evdo_reg;
    struct
    {
        unsigned long  dsp_ready_ind_cdrx_evdo : 1;  /* bit[0]   : 自然唤醒流程中，软件已经准备好接收时钟切换中断 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DSP_READY_IND_CDRX_EVDO_UNION;
#define CBBP_DSP_READY_IND_CDRX_EVDO_dsp_ready_ind_cdrx_evdo_START  (0)
#define CBBP_DSP_READY_IND_CDRX_EVDO_dsp_ready_ind_cdrx_evdo_END    (0)




/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of bbp_cdma_on_interface.h */
