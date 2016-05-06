/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_comm_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-05-14 15:26:33
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月14日
    作    者   : l00165286
    修改内容   : 从《K3V5 MODEM寄存器手册_COMM.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_COMM_INTERFACE_H__
#define __BBP_COMM_INTERFACE_H__

#include "bbp_common_interface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_bbpmst
 ***======================================================================***/
/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA800)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的输入时钟域选择：
             1）3’b001：该写通道的输入接口使用第一种时钟域
             2）3’b010：该写通道的输入接口使用第二种时钟域
             3）3’b100：该写通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA804)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH0_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA808)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH0_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA80C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA810)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA814)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA820)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的输入时钟域选择：
             1）3’b001：该写通道的输入接口使用第一种时钟域
             2）3’b010：该写通道的输入接口使用第二种时钟域
             3）3’b100：该写通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA824)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH1_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA828)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH1_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA82C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA830)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA834)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA840)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的输入时钟域选择：
             1）3’b001：该写通道的输入接口使用第一种时钟域
             2）3’b010：该写通道的输入接口使用第二种时钟域
             3）3’b100：该写通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA844)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH2_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA848)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH2_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA84C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA850)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA854)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA860)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的输入时钟域选择：
             1）3’b001：该写通道的输入接口使用第一种时钟域
             2）3’b010：该写通道的输入接口使用第二种时钟域
             3）3’b100：该写通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA864)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH3_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA868)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH3_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA86C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA870)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA874)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA880)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该写通道的输入时钟域选择：
             1）3’b001：该写通道的输入接口使用第一种时钟域
             2）3’b010：该写通道的输入接口使用第二种时钟域
             3）3’b100：该写通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA884)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH4_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA888)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH4_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA88C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA890)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA894)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19]     读通道3的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[18]     读通道2的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[17]     读通道1的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[16]     读通道0的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[15:5]   保留
 bit[4]      写通道4的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[3]      写通道3的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[2]      写通道2的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[1]      写通道1的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[0]      写通道0的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
   UNION结构:  BBPCOMM_BBPMST_CH_BUSY_UNION */
#define BBPCOMM_BBPMST_CH_BUSY_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xA898)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA900)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的输入时钟域选择：
             1）3’b001：该读通道的输入接口使用第一种时钟域
             2）3’b010：该读通道的输入接口使用第二种时钟域
             3）3’b100：该读通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA904)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH0_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA908)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA90C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA910)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA920)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的输入时钟域选择：
             1）3’b001：该读通道的输入接口使用第一种时钟域
             2）3’b010：该读通道的输入接口使用第二种时钟域
             3）3’b100：该读通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA924)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH1_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA928)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA92C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA930)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA940)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的输入时钟域选择：
             1）3’b001：该读通道的输入接口使用第一种时钟域
             2）3’b010：该读通道的输入接口使用第二种时钟域
             3）3’b100：该读通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA944)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH2_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA948)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA94C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA950)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
             1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
             2）3'b001：通道配置给第一组接口使用
             3）3'b010：通道配置给第二组接口使用
             4）3'b100：通道配置给第三组接口使用
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xA960)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    该读通道的输入时钟域选择：
             1）3’b001：该读通道的输入接口使用第一种时钟域
             2）3’b010：该读通道的输入接口使用第二种时钟域
             3）3’b100：该读通道的输入接口使用第三种时钟域
             在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
             在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
             在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA964)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH3_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA968)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xA96C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      本通道所选择使用的master口：
             1'b0：该通道使用master口1
             1'b1：该通道使用master口2
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xA970)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA974)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道1每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA978)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道2每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含16个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA97C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道3每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA980)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      axi口0写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[1]      axi口0读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[0]      axi口0的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
   UNION结构:  BBPCOMM_BBPMST_AXI0_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI0_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xAB00)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      axi口1的写通道状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[1]      axi口1的读通道状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[0]      axi口1的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
   UNION结构:  BBPCOMM_BBPMST_AXI1_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI1_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xAB04)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型0
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB08)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型1
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB0C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型2
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB10)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型3
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xAB14)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址0
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR0_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB18)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址1
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR1_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB1C)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址2
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR2_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB20)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址3
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR3_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xAB24)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      bbpmst读写错误中断清除寄存器。当BBPMST读写发生错误时，bbpmst_error_int会直接拉成电平送给BBE16\CCPU，软件收到中断后配置该寄存器清除中断电平。
   UNION结构:  BBPCOMM_BBPMST_ERROR_INT_CLR_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xAB28)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL0_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB2C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL1_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB30)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST写通道写请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB34)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST读通道读请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB38)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST写通道写请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB3C)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST读通道读请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xAB40)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口0当前写响应ID
 bit[7:5]    保留
 bit[4]      AXI口0当前写响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口0当前写响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_WR0_STATE_UNION */
#define BBPCOMM_AXI_WR0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB44)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口0当前读响应ID
 bit[7:5]    保留
 bit[4]      AXI口0当前读响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口0当前读响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_RD0_STATE_UNION */
#define BBPCOMM_AXI_RD0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB48)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口1当前写响应ID
 bit[7:5]    保留
 bit[4]      AXI口1当前写响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口1当前写响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_WR1_STATE_UNION */
#define BBPCOMM_AXI_WR1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB4C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口1当前读响应ID
 bit[7:5]    保留
 bit[4]      AXI口1当前读响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口1当前读响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_RD1_STATE_UNION */
#define BBPCOMM_AXI_RD1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xAB50)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST写通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB54)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST读通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB58)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST写通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB5C)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST读通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xAB60)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写错误中断使能
   UNION结构:  BBPCOMM_BBPMST_ERROR_INT_EN_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_EN_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xAB64)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写错误中断屏蔽信号
   UNION结构:  BBPCOMM_BBPMST_ERROR_INT_MASK_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xAB68)



/***======================================================================***
                     (2/2) register_define_irm_ps
 ***======================================================================***/
/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    用于irm_ps网络模式选择，影响irm_ps内部时钟切换和模式切换，默认都为0。.
             6'b000001，GBBP1模式；
             6'b000110，UMTS模式；
             6'b001000，LTE模式；
             6'b010000，TDS-CDMA模式；
             6'b100000，CDMA模式。
             注：GBBP1固定为主卡（G0/U/L/T）。
   UNION结构:  BBPCOMM_IRM_PS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_PS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      GBBP2，默认为0，1为使能。
             注：GBBP2固定为辅卡。
             V8R1不使用。
   UNION结构:  BBPCOMM_IRM_PS_GSM2_CTRL_UNION */
#define BBPCOMM_IRM_PS_GSM2_CTRL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xB004)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      irm_ps模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。
   UNION结构:  BBPCOMM_IRM_PS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_PS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xB008)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_TURBO_UNION */
#define BBPCOMM_MEM_CTRL0_TURBO_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB010)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_TURBO_UNION */
#define BBPCOMM_MEM_CTRL1_TURBO_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xB014)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_PS_UNION */
#define BBPCOMM_MEM_CTRL0_PS_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB020)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_PS_UNION */
#define BBPCOMM_MEM_CTRL1_PS_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0xB024)

/* 寄存器说明：
 bit[31:16]  turbo译码子模块级门控旁路使能，高电平有效。
 bit[15:0]   turbo译码子模块级门控旁路使能，高电平有效。
   UNION结构:  BBPCOMM_TUBO_CKG_UNION */
#define BBPCOMM_TUBO_CKG_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB028)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（L模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_L_TYPE_UNION */
#define BBPCOMM_U_L_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB02C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（T模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_T_TYPE_UNION */
#define BBPCOMM_U_T_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB030)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Turbo译码模式选择信号（C模）。
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
             3'b000，U模；
             3'b001，L模；
             3'b010，T模；
             3'b100，C模；
             其他，无意义。
   UNION结构:  BBPCOMM_U_C_TYPE_UNION */
#define BBPCOMM_U_C_TYPE_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0xB034)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:14]  SOC AP配置给ps ram的occupy配置信号。
 bit[13:12]  
 bit[11:10]  
 bit[9:8]    
 bit[7:6]    
 bit[5:4]    
 bit[3:2]    
 bit[1:0]    
   UNION结构:  BBPCOMM_SOC_AP_OCCUPY_GRP_UNION */
#define BBPCOMM_SOC_AP_OCCUPY_GRP_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xB038)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1]      W SDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。
 bit[0]      W SDR模式开关使能。
   UNION结构:  BBPCOMM_PS_W_SDR_EN_UNION */
#define BBPCOMM_PS_W_SDR_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0xB03C)





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
                     (1/2) register_define_bbpmst
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_MODE_UNION
 结构说明  : BBPMST_WR_CH0_MODE 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_mode : 3;  /* bit[0-2] : 该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION
 结构说明  : BBPMST_WR_CH0_CLK_SEL 寄存器结构定义。地址偏移量:0x0004，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_clk_sel : 3;  /* bit[0-2] : 该写通道的输入时钟域选择：
                                                                 1）3’b001：该写通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该写通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该写通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_bbpmst_wr_ch0_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_bbpmst_wr_ch0_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH0_BURST_BEAT 寄存器结构定义。地址偏移量:0x0010，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH0_AXI_SEL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch0_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch0_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_MODE_UNION
 结构说明  : BBPMST_WR_CH1_MODE 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_mode : 3;  /* bit[0-2] : 该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION
 结构说明  : BBPMST_WR_CH1_CLK_SEL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_clk_sel : 3;  /* bit[0-2] : 该写通道的输入时钟域选择：
                                                                 1）3’b001：该写通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该写通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该写通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_bbpmst_wr_ch1_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_bbpmst_wr_ch1_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH1_BURST_BEAT 寄存器结构定义。地址偏移量:0x0030，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH1_AXI_SEL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch1_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch1_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_MODE_UNION
 结构说明  : BBPMST_WR_CH2_MODE 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_mode : 3;  /* bit[0-2] : 该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION
 结构说明  : BBPMST_WR_CH2_CLK_SEL 寄存器结构定义。地址偏移量:0x0044，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_clk_sel : 3;  /* bit[0-2] : 该写通道的输入时钟域选择：
                                                                 1）3’b001：该写通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该写通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该写通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_bbpmst_wr_ch2_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_bbpmst_wr_ch2_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH2_BURST_BEAT 寄存器结构定义。地址偏移量:0x0050，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH2_AXI_SEL 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch2_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch2_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_MODE_UNION
 结构说明  : BBPMST_WR_CH3_MODE 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_mode : 3;  /* bit[0-2] : 该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION
 结构说明  : BBPMST_WR_CH3_CLK_SEL 寄存器结构定义。地址偏移量:0x0064，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_clk_sel : 3;  /* bit[0-2] : 该写通道的输入时钟域选择：
                                                                 1）3’b001：该写通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该写通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该写通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_bbpmst_wr_ch3_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_bbpmst_wr_ch3_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH3_BURST_BEAT 寄存器结构定义。地址偏移量:0x0070，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH3_AXI_SEL 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch3_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch3_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_MODE_UNION
 结构说明  : BBPMST_WR_CH4_MODE 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_mode_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_mode : 3;  /* bit[0-2] : 该写通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_wr_ch0_mode代表写通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的axi接口不再发出新的读/写请求，如果所有的读写通道都没有新请求了，且axi口以及总线被释放（是否被释放的状态在cpu接口有上报），软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_mode_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION
 结构说明  : BBPMST_WR_CH4_CLK_SEL 寄存器结构定义。地址偏移量:0x0084，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_clk_sel : 3;  /* bit[0-2] : 该写通道的输入时钟域选择：
                                                                 1）3’b001：该写通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该写通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该写通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_bbpmst_wr_ch4_clk_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_bbpmst_wr_ch4_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH4_BURST_BEAT 寄存器结构定义。地址偏移量:0x0090，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH4_AXI_SEL 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_wr_ch4_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_wr_ch4_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_CH_BUSY_UNION
 结构说明  : BBPMST_CH_BUSY 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_ch_busy_reg;
    struct
    {
        unsigned long  wr_ch0_busy : 1;  /* bit[0]    : 写通道0的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  wr_ch1_busy : 1;  /* bit[1]    : 写通道1的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  wr_ch2_busy : 1;  /* bit[2]    : 写通道2的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  wr_ch3_busy : 1;  /* bit[3]    : 写通道3的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  wr_ch4_busy : 1;  /* bit[4]    : 写通道4的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  reserved_0  : 11; /* bit[5-15] : 保留 */
        unsigned long  rd_ch0_busy : 1;  /* bit[16]   : 读通道0的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  rd_ch1_busy : 1;  /* bit[17]   : 读通道1的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  rd_ch2_busy : 1;  /* bit[18]   : 读通道2的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  rd_ch3_busy : 1;  /* bit[19]   : 读通道3的空闲/忙碌状态：
                                                        1'b0：通道已排空，处于空闲态
                                                        1'b1：通道处于忙碌状态 */
        unsigned long  reserved_1  : 12; /* bit[20-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_CH_BUSY_UNION;
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch0_busy_START  (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch0_busy_END    (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch1_busy_START  (1)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch1_busy_END    (1)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch2_busy_START  (2)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch2_busy_END    (2)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch3_busy_START  (3)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch3_busy_END    (3)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch4_busy_START  (4)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch4_busy_END    (4)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch0_busy_START  (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch0_busy_END    (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch1_busy_START  (17)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch1_busy_END    (17)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch2_busy_START  (18)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch2_busy_END    (18)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch3_busy_START  (19)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch3_busy_END    (19)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_MODE_UNION
 结构说明  : BBPMST_RD_CH0_MODE 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_mode : 3;  /* bit[0-2] : 该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION
 结构说明  : BBPMST_RD_CH0_CLK_SEL 寄存器结构定义。地址偏移量:0x0104，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_clk_sel : 3;  /* bit[0-2] : 该读通道的输入时钟域选择：
                                                                 1）3’b001：该读通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该读通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该读通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_bbpmst_rd_ch0_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_bbpmst_rd_ch0_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH0_BURST_BEAT 寄存器结构定义。地址偏移量:0x010C，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH0_AXI_SEL 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_MODE_UNION
 结构说明  : BBPMST_RD_CH1_MODE 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_mode : 3;  /* bit[0-2] : 该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION
 结构说明  : BBPMST_RD_CH1_CLK_SEL 寄存器结构定义。地址偏移量:0x0124，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_clk_sel : 3;  /* bit[0-2] : 该读通道的输入时钟域选择：
                                                                 1）3’b001：该读通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该读通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该读通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_bbpmst_rd_ch1_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_bbpmst_rd_ch1_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH1_BURST_BEAT 寄存器结构定义。地址偏移量:0x012C，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH1_AXI_SEL 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_MODE_UNION
 结构说明  : BBPMST_RD_CH2_MODE 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_mode : 3;  /* bit[0-2] : 该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION
 结构说明  : BBPMST_RD_CH2_CLK_SEL 寄存器结构定义。地址偏移量:0x0144，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_clk_sel : 3;  /* bit[0-2] : 该读通道的输入时钟域选择：
                                                                 1）3’b001：该读通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该读通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该读通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_bbpmst_rd_ch2_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_bbpmst_rd_ch2_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH2_BURST_BEAT 寄存器结构定义。地址偏移量:0x014C，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH2_AXI_SEL 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_MODE_UNION
 结构说明  : BBPMST_RD_CH3_MODE 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_mode_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_mode : 3;  /* bit[0-2] : 该读通道的工作模式：每个通道可以由最多3个不同时发生的数据流复用；bbpmst_rd_ch0_mode代表读通道0的工作模式
                                                              1）3'b000 ：通道非使能，此时该通道向前级的BBP输出valid/ready为0，向后级的读写控制不再发出新的读/写请求，如果所有的读写通道都没有新请求，则master口被释放，总线状态在cpu接口上报，软件结合该状态可启动门控或掉电流程
                                                              2）3'b001：通道配置给第一组接口使用
                                                              3）3'b010：通道配置给第二组接口使用
                                                              4）3'b100：通道配置给第三组接口使用 */
        unsigned long  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_mode_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_mode_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION
 结构说明  : BBPMST_RD_CH3_CLK_SEL 寄存器结构定义。地址偏移量:0x0164，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_clk_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_clk_sel : 3;  /* bit[0-2] : 该读通道的输入时钟域选择：
                                                                 1）3’b001：该读通道的输入接口使用第一种时钟域
                                                                 2）3’b010：该读通道的输入接口使用第二种时钟域
                                                                 3）3’b100：该读通道的输入接口使用第三种时钟域
                                                                 在v8r1中的第一种接口时钟为：104MHz，为g模的工作时钟
                                                                 在v8r1中的第二种接口时钟为：122.88MHz，为C模以及U模中除译码外的逻辑的工作时钟，且各模的cpu接口也使用该时钟域
                                                                 在v8r1中的第三种接口时钟为：245.76MHz，为U模中译码的工作时钟 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_CLK_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_bbpmst_rd_ch3_clk_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_bbpmst_rd_ch3_clk_sel_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH3_BURST_BEAT 寄存器结构定义。地址偏移量:0x016C，初值:0x00000008，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_burst_beat_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_burst_beat : 4;  /* bit[0-3] : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH3_AXI_SEL 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_axi_sel_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_axi_sel : 1;  /* bit[0]   : 本通道所选择使用的master口：
                                                                 1'b0：该通道使用master口1
                                                                 1'b1：该通道使用master口2 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH0_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0174，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch0_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch0_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据； */
        unsigned long  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH1_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0178，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch1_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch1_bit_width_ind : 2;  /* bit[0-1] : 读通道1每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据； */
        unsigned long  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH2_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x017C，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch2_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch2_bit_width_ind : 2;  /* bit[0-1] : 读通道2每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含16个有效数据； */
        unsigned long  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH3_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0180，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_rd_ch3_bit_width_ind_reg;
    struct
    {
        unsigned long  bbpmst_rd_ch3_bit_width_ind : 2;  /* bit[0-1] : 读通道3每个64比特读数据有效数据个数指示：0，表示每个64比特读数据含10个有效数据；1，表示每个64比特读数据含16个有效数据；2，表示每个64比特读数据含1个有效数据； */
        unsigned long  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_AXI0_STATUS_UNION
 结构说明  : BBPMST_AXI0_STATUS 寄存器结构定义。地址偏移量:0x0300，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_axi0_status_reg;
    struct
    {
        unsigned long  bbpmst_axi0_status    : 1;  /* bit[0]   : axi口0的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  bbpmst_axi0_rd_status : 1;  /* bit[1]   : axi口0读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  bbpmst_axi0_wr_status : 1;  /* bit[2]   : axi口0写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_AXI0_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_START     (0)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_END       (0)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_START  (1)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_END    (1)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_START  (2)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_AXI1_STATUS_UNION
 结构说明  : BBPMST_AXI1_STATUS 寄存器结构定义。地址偏移量:0x0304，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_axi1_status_reg;
    struct
    {
        unsigned long  bbpmst_axi1_status    : 1;  /* bit[0]   : axi口1的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  bbpmst_axi1_rd_status : 1;  /* bit[1]   : axi口1的读通道状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  bbpmst_axi1_wr_status : 1;  /* bit[2]   : axi口1的写通道状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_AXI1_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_START     (0)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_END       (0)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_START  (1)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_END    (1)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_START  (2)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION
 结构说明  : BBPMST_ERROR_BURST_BEAT0 寄存器结构定义。地址偏移量:0x0308，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat0_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat0 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型0 */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION
 结构说明  : BBPMST_ERROR_BURST_BEAT1 寄存器结构定义。地址偏移量:0x030C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat1_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat1 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型1 */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION
 结构说明  : BBPMST_ERROR_BURST_BEAT2 寄存器结构定义。地址偏移量:0x0310，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat2_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat2 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型2 */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION
 结构说明  : BBPMST_ERROR_BURST_BEAT3 寄存器结构定义。地址偏移量:0x0314，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_burst_beat3_reg;
    struct
    {
        unsigned long  bbpmst_error_burst_beat3 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型3 */
        unsigned long  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_INT_CLR_UNION
 结构说明  : BBPMST_ERROR_INT_CLR 寄存器结构定义。地址偏移量:0x0328，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_clr_reg;
    struct
    {
        unsigned long  bbpmst_error_int_clr : 1;  /* bit[0]   : bbpmst读写错误中断清除寄存器。当BBPMST读写发生错误时，bbpmst_error_int会直接拉成电平送给BBE16\CCPU，软件收到中断后配置该寄存器清除中断电平。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_CLR_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_BBPMST_UNION
 结构说明  : MEM_CTRL0_BBPMST 寄存器结构定义。地址偏移量:0x032C，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_bbpmst_reg;
    struct
    {
        unsigned long  mem_ctrl_s_bbpmst      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned long  mem_ctrl_d_1w2r_bbpmst : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_START       (0)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_END         (15)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_START  (16)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_BBPMST_UNION
 结构说明  : MEM_CTRL1_BBPMST 寄存器结构定义。地址偏移量:0x0330，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_bbpmst_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_bbpmst : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned long  rom_ctrl_bbpmst          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned long  reserved                 : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_START  (0)
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_END    (15)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_START           (16)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_END             (23)


/*****************************************************************************
 结构名    : BBPCOMM_AXI_WR0_STATE_UNION
 结构说明  : AXI_WR0_STATE 寄存器结构定义。地址偏移量:0x0344，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_wr0_state_reg;
    struct
    {
        unsigned long  axi_wr0_ready  : 1;  /* bit[0]    : AXI口0当前写响应可接收数据指示 */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  axi_wr0_valid  : 1;  /* bit[4]    : AXI口0当前写响应数据有效指示 */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  axi_wr0_cur_id : 3;  /* bit[8-10] : AXI口0当前写响应ID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_AXI_WR0_STATE_UNION;
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_START   (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_END     (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_START   (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_END     (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_START  (8)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_END    (10)


/*****************************************************************************
 结构名    : BBPCOMM_AXI_RD0_STATE_UNION
 结构说明  : AXI_RD0_STATE 寄存器结构定义。地址偏移量:0x0348，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_rd0_state_reg;
    struct
    {
        unsigned long  axi_rd0_ready  : 1;  /* bit[0]    : AXI口0当前读响应可接收数据指示 */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  axi_rd0_valid  : 1;  /* bit[4]    : AXI口0当前读响应数据有效指示 */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  axi_rd0_cur_id : 3;  /* bit[8-10] : AXI口0当前读响应ID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_AXI_RD0_STATE_UNION;
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_START   (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_END     (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_START   (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_END     (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_START  (8)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_END    (10)


/*****************************************************************************
 结构名    : BBPCOMM_AXI_WR1_STATE_UNION
 结构说明  : AXI_WR1_STATE 寄存器结构定义。地址偏移量:0x034C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_wr1_state_reg;
    struct
    {
        unsigned long  axi_wr1_ready  : 1;  /* bit[0]    : AXI口1当前写响应可接收数据指示 */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  axi_wr1_valid  : 1;  /* bit[4]    : AXI口1当前写响应数据有效指示 */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  axi_wr1_cur_id : 3;  /* bit[8-10] : AXI口1当前写响应ID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_AXI_WR1_STATE_UNION;
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_START   (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_END     (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_START   (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_END     (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_START  (8)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_END    (10)


/*****************************************************************************
 结构名    : BBPCOMM_AXI_RD1_STATE_UNION
 结构说明  : AXI_RD1_STATE 寄存器结构定义。地址偏移量:0x0350，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      axi_rd1_state_reg;
    struct
    {
        unsigned long  axi_rd1_ready  : 1;  /* bit[0]    : AXI口1当前读响应可接收数据指示 */
        unsigned long  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  axi_rd1_valid  : 1;  /* bit[4]    : AXI口1当前读响应数据有效指示 */
        unsigned long  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  axi_rd1_cur_id : 3;  /* bit[8-10] : AXI口1当前读响应ID */
        unsigned long  reserved_2     : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_AXI_RD1_STATE_UNION;
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_START   (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_END     (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_START   (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_END     (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_START  (8)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_END    (10)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_INT_EN_UNION
 结构说明  : BBPMST_ERROR_INT_EN 寄存器结构定义。地址偏移量:0x0364，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_en_reg;
    struct
    {
        unsigned long  bbpmst_error_int_en : 1;  /* bit[0]   : BBPMST读写错误中断使能 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_EN_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_INT_MASK_UNION
 结构说明  : BBPMST_ERROR_INT_MASK 寄存器结构定义。地址偏移量:0x0368，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbpmst_error_int_mask_reg;
    struct
    {
        unsigned long  bbpmst_error_int_mask : 1;  /* bit[0]   : BBPMST读写错误中断屏蔽信号 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_MASK_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_MASK_bbpmst_error_int_mask_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_MASK_bbpmst_error_int_mask_END    (0)


/***======================================================================***
                     (2/2) register_define_irm_ps
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_RAM_CTRL_UNION
 结构说明  : IRM_PS_RAM_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_ram_ctrl_reg;
    struct
    {
        unsigned long  irm_ps_ram_ctrl : 6;  /* bit[0-5] : 用于irm_ps网络模式选择，影响irm_ps内部时钟切换和模式切换，默认都为0。.
                                                           6'b000001，GBBP1模式；
                                                           6'b000110，UMTS模式；
                                                           6'b001000，LTE模式；
                                                           6'b010000，TDS-CDMA模式；
                                                           6'b100000，CDMA模式。
                                                           注：GBBP1固定为主卡（G0/U/L/T）。 */
        unsigned long  reserved        : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_START  (0)
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_GSM2_CTRL_UNION
 结构说明  : IRM_PS_GSM2_CTRL 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_gsm2_ctrl_reg;
    struct
    {
        unsigned long  irm_ps_gsm2_ctrl : 1;  /* bit[0]   : GBBP2，默认为0，1为使能。
                                                            注：GBBP2固定为辅卡。
                                                            V8R1不使用。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_GSM2_CTRL_UNION;
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_START  (0)
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_IRM_PS_CLK_BYPASS_UNION
 结构说明  : IRM_PS_CLK_BYPASS 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      irm_ps_clk_bypass_reg;
    struct
    {
        unsigned long  irm_ps_clk_bypass : 1;  /* bit[0]   : irm_ps模块时钟门控旁路开关。默认为0，即开启时钟门控。配置1则开启旁路功能，时钟门控失效。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_IRM_PS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_START  (0)
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_TURBO_UNION
 结构说明  : MEM_CTRL0_TURBO 寄存器结构定义。地址偏移量:0x010，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_turbo_reg;
    struct
    {
        unsigned long  mem_ctrl_s_turbo      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned long  mem_ctrl_d_1w2r_turbo : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_TURBO_UNION;
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_START       (0)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_END         (15)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_START  (16)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_TURBO_UNION
 结构说明  : MEM_CTRL1_TURBO 寄存器结构定义。地址偏移量:0x014，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_turbo_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_turbo : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned long  rom_ctrl_turbo          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned long  reserved                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_TURBO_UNION;
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_START  (0)
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_END    (15)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_START           (16)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_END             (23)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL0_PS_UNION
 结构说明  : MEM_CTRL0_PS 寄存器结构定义。地址偏移量:0x020，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl0_ps_reg;
    struct
    {
        unsigned long  mem_ctrl_s_ps      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned long  mem_ctrl_d_1w2r_ps : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} BBPCOMM_MEM_CTRL0_PS_UNION;
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_START       (0)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_END         (15)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_START  (16)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_MEM_CTRL1_PS_UNION
 结构说明  : MEM_CTRL1_PS 寄存器结构定义。地址偏移量:0x024，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mem_ctrl1_ps_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_ps : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned long  rom_ctrl_ps          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned long  reserved             : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_MEM_CTRL1_PS_UNION;
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_START  (0)
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_END    (15)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_START           (16)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_END             (23)


/*****************************************************************************
 结构名    : BBPCOMM_TUBO_CKG_UNION
 结构说明  : TUBO_CKG 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tubo_ckg_reg;
    struct
    {
        unsigned long  tubo_ram_ckg_en : 16; /* bit[0-15] : turbo译码子模块级门控旁路使能，高电平有效。 */
        unsigned long  tubo_mod_ckg_en : 16; /* bit[16-31]: turbo译码子模块级门控旁路使能，高电平有效。 */
    } reg;
} BBPCOMM_TUBO_CKG_UNION;
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_START  (0)
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_END    (15)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_START  (16)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_U_L_TYPE_UNION
 结构说明  : U_L_TYPE 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      u_l_type_reg;
    struct
    {
        unsigned long  u_l_type : 1;  /* bit[0]   : Turbo译码模式选择信号（L模）。
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                    3'b000，U模；
                                                    3'b001，L模；
                                                    3'b010，T模；
                                                    3'b100，C模；
                                                    其他，无意义。 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_L_TYPE_UNION;
#define BBPCOMM_U_L_TYPE_u_l_type_START  (0)
#define BBPCOMM_U_L_TYPE_u_l_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_U_T_TYPE_UNION
 结构说明  : U_T_TYPE 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      u_t_type_reg;
    struct
    {
        unsigned long  u_t_type : 1;  /* bit[0]   : Turbo译码模式选择信号（T模）。
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                    3'b000，U模；
                                                    3'b001，L模；
                                                    3'b010，T模；
                                                    3'b100，C模；
                                                    其他，无意义。 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_T_TYPE_UNION;
#define BBPCOMM_U_T_TYPE_u_t_type_START  (0)
#define BBPCOMM_U_T_TYPE_u_t_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_U_C_TYPE_UNION
 结构说明  : U_C_TYPE 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      u_c_type_reg;
    struct
    {
        unsigned long  u_c_type : 1;  /* bit[0]   : Turbo译码模式选择信号（C模）。
                                                    {U_C_TYPE, U_T_TYPE, U_L_TYPE}三个控制bit拼接组合后含义如下：
                                                    3'b000，U模；
                                                    3'b001，L模；
                                                    3'b010，T模；
                                                    3'b100，C模；
                                                    其他，无意义。 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_U_C_TYPE_UNION;
#define BBPCOMM_U_C_TYPE_u_c_type_START  (0)
#define BBPCOMM_U_C_TYPE_u_c_type_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SOC_AP_OCCUPY_GRP_UNION
 结构说明  : SOC_AP_OCCUPY_GRP 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      soc_ap_occupy_grp_reg;
    struct
    {
        unsigned long  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  :  */
        unsigned long  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  :  */
        unsigned long  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  :  */
        unsigned long  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  :  */
        unsigned long  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  :  */
        unsigned long  soc_ap_occupy_grp6 : 2;  /* bit[10-11]:  */
        unsigned long  soc_ap_occupy_grp7 : 2;  /* bit[12-13]:  */
        unsigned long  soc_ap_occupy_grp8 : 2;  /* bit[14-15]: SOC AP配置给ps ram的occupy配置信号。 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_SOC_AP_OCCUPY_GRP_UNION;
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_START  (0)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_END    (1)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_START  (2)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_END    (3)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_START  (4)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_END    (5)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_START  (6)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_END    (7)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_START  (8)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_END    (9)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_START  (10)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_END    (11)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_START  (12)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_END    (13)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_START  (14)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_PS_W_SDR_EN_UNION
 结构说明  : PS_W_SDR_EN 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ps_w_sdr_en_reg;
    struct
    {
        unsigned long  ps_w_sdr_en          : 1;  /* bit[0]   : W SDR模式开关使能。 */
        unsigned long  ps_w_sdr_dec_clk_sel : 1;  /* bit[1]   : W SDR模式下译码时钟选择。0，译码采用122m时钟；1，译码采用245m时钟。 */
        unsigned long  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_PS_W_SDR_EN_UNION;
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_START           (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_END             (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_START  (1)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_END    (1)




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

#endif /* end of bbp_comm_interface.h */
