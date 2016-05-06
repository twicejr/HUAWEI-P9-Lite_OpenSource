/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bbp_cdma_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-10-30 15:35:35
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月30日
    作    者   : p00277817
    修改内容   : 从《K3V5 MODEM寄存器手册_CDMA.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_CDMA_INTERFACE_H__
#define __BBP_CDMA_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/20) register_define_c_glb
 ***======================================================================***/
/* 寄存器说明：
 bit[31:16]  1w2r双口RAM延时控制。
 bit[15:0]   单口RAM延时控制。
   UNION结构:  CBBP_VIRAGE_RM_CTRL_C_0_UNION */
#define CBBP_VIRAGE_RM_CTRL_C_0_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  ROM延时控制。
 bit[15:0]   1rw2rw双口RAM延时控制。
   UNION结构:  CBBP_VIRAGE_RM_CTRL_C_1_UNION */
#define CBBP_VIRAGE_RM_CTRL_C_1_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26]     G软化前端数据
 bit[25]     G软化中断
 bit[24]     G软化定时
 bit[23]     G软化时钟测量
 bit[22]     射频前端控制模块。
 bit[21]     前端数据接口模块。
 bit[20]     编码模块。
 bit[19]     译码模块。
 bit[18]     搜索测量模块。
 bit[17]     中断模块。
 bit[16]     系统时钟域CLK控制。在对各模块进行时钟控制时，将对应bit置1表示打开该模块的时钟；反之，将对应bit置0表示关闭该模块的时钟。
             定时模块。
 bit[15:11]  保留
 bit[10]     G软化前端数据
 bit[9]      G软化中断
 bit[8]      G软化定时
 bit[7]      G软化时钟测量
 bit[6]      射频前端控制模块。
 bit[5]      前端数据接口模块。
 bit[4]      编码模块。
 bit[3]      译码模块。
 bit[2]      搜索测量模块。
 bit[1]      中断模块。
 bit[0]      系统时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit复位为0。
             定时模块。
   UNION结构:  CBBP_SYS_RST_CTRL_C_UNION */
#define CBBP_SYS_RST_CTRL_C_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x8)

/* 寄存器说明：
 bit[31:26]  保留
 bit[25]     G软化中断
 bit[24]     G软化定时
 bit[23]     G软化时钟测量
 bit[22]     射频前端控制模块。
 bit[21]     前端数据接口模块。
 bit[20]     编码模块。
 bit[19]     译码模块。
 bit[18]     搜索测量模块。
 bit[17]     中断模块。
 bit[16]     IMI地址片选控制屏蔽使能，高电平有效。该信号有效表示对应模块未被选中时屏蔽BBP内部该模块IMI地址。
             定时模块。
 bit[15:10]  保留
 bit[9]      G软化中断
 bit[8]      G软化定时
 bit[7]      G软化时钟测量
 bit[6]      射频前端控制模块。
 bit[5]      前端数据接口模块。
 bit[4]      编码模块。
 bit[3]      译码模块。
 bit[2]      搜索测量模块。
 bit[1]      中断模块。
 bit[0]      IMI时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit复位为0。
             定时模块。
   UNION结构:  CBBP_IMI_RST_CTRL_C_UNION */
#define CBBP_IMI_RST_CTRL_C_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC)

/* 寄存器说明：
   详      述：版本寄存器。
   UNION结构 ：无 */
#define CBBP_VERSION_C_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x10)



/***======================================================================***
                     (2/20) register_define_c_timing
 ***======================================================================***/
/* 寄存器说明：
 bit[31:18]  保留
 bit[17:0]   时钟测量时间，32k时钟个数。最长支持5.12s。
             说明：取值为0无意义。
   UNION结构:  CBBP_C_CK_MSR_PERIOD_UNION */
#define CBBP_C_CK_MSR_PERIOD_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      时钟测量使能。BBP检测上升沿，启动时钟测量。如果软件配置为0，BBP停止时钟测量。
   UNION结构:  CBBP_C_CK_MSR_EN_UNION */
#define CBBP_C_CK_MSR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x1004)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   时钟测量结果。上报了在ck_msr_period内的122.88MHz时钟个数
   UNION结构:  CBBP_CK_MSR_RPT_UNION */
#define CBBP_CK_MSR_RPT_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x1008)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    更新sys_cnt_1x的时刻：
             [28:24]，base_cnt_2s上的时刻，取值范围0~24；
             [23:22]，base_cnt_80ms上的时刻，取值范围0~2；
             [21:5]，base_cnt_26ms上的时刻，取值范围0~32768*4-1；
             [4:0]，1/4chip内计数，取值范围0~24
             
   UNION结构:  CBBP_SYS_CNT_1X_GET_POS_UNION */
#define CBBP_SYS_CNT_1X_GET_POS_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1020)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:18]  
 bit[17:5]   
 bit[4:0]    sys_cnt_get_pos时刻sys_cnt_1x的值：
             [29:24]，sys_cnt_1x_5p12s的值；
             [23:18]，sys_cnt_1x_80ms的值；
             [17:5]，sys_cnt_1x_1p25ms的值，取值范围0~1536*4-1；
             [4:0]，1/4chip内计数，取值范围0~24
             
   UNION结构:  CBBP_SYS_CNT_1X_GET_VALUE_UNION */
#define CBBP_SYS_CNT_1X_GET_VALUE_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1024)

/* 寄存器说明：
   详      述：sys_cnt_get_pos时刻sys_cnt_1x的值，单位5.12s或2s
   UNION结构 ：无 */
#define CBBP_SYS_CNT_1X_GET_VALUE_HIGH_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x10B0)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    1X定时突变后sys_cnt_1x  80ms帧头在base_cnt上的位置。
             Bit[4:0]：1/4chip内计数0~24
             bit[21:5]：26ms内计数0~32768*4-1
             bit[23:22]：80ms内计数0~2
   UNION结构:  CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x10C4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Sys_cnt_1x定时获取指示。
             BBP接收到此指示后，等待base_cnt上sys_cnt_1x_get_pos时刻，将sys_cnt_1x更新为sys_cnt_1x_get_value。
             
   UNION结构:  CBBP_SYS_CNT_1X_GET_RDY_UNION */
#define CBBP_SYS_CNT_1X_GET_RDY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1028)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      系统定时调整方向。
             0：表示往左边调整6clk；
             1：表示往右边调整6clk；
             说明：定时采用100倍时钟，因此，6clk时间为6/100chip
             
   UNION结构:  CBBP_SYS_1X_CHANGE_DIRECTION_UNION */
#define CBBP_SYS_1X_CHANGE_DIRECTION_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x102C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      系统定时调整指示。
             BBP在接收到此指示后，在最近的PCG完成系统定时
             
   UNION结构:  CBBP_SYS_1X_CHANGE_RDY_UNION */
#define CBBP_SYS_1X_CHANGE_RDY_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1030)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件读取sys_cnt_1x_80ms_pos的指示，BBP接收到此信号后锁存本地的计数值
   UNION结构:  CBBP_SYS_CNT_1X_80MS_POS_RD_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_RD_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1034)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     sys_cnt_1x_80ms_pos有效指示，1表示读取的结果有效
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_1x  80ms帧头在base_cnt上的位置。
             Bit[4:0]：1/4chip内计数0~24
             bit[21:5]：26ms内计数0~32768*4-1
             bit[23:22]：80ms内计数0~2
   UNION结构:  CBBP_SYS_CNT_1X_80MS_POS_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1038)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      sys_cnt_1x_80ms_pos_valid清零信号，在完成sys_cnt_1x_80ms_pos读取后，使用此寄存器将其有效标志清除
   UNION结构:  CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION */
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0x103C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时突变时，定时中断的mask指示。
             0：表示不mask；
             1：表示mask配置范围内的中断；
             
   UNION结构:  CBBP_TIMING_INT_1X_MASK_UNION */
#define CBBP_TIMING_INT_1X_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1040)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   定时突变时，定时中断的mask区间，chip为单位。
   UNION结构:  CBBP_TIMING_INT_1X_MASK_DIS_UNION */
#define CBBP_TIMING_INT_1X_MASK_DIS_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1044)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int1在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1048)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int1中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT1_1X_PERIOD_UNION */
#define CBBP_TIMING_INT1_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x104C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int1的使能。
             0：表示不产生int1中断；
             1：表示产生int1中断；
             
   UNION结构:  CBBP_TIMING_INT1_1X_EN_UNION */
#define CBBP_TIMING_INT1_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1050)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1054)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT2_1X_PERIOD_UNION */
#define CBBP_TIMING_INT2_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1058)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT2_1X_EN_UNION */
#define CBBP_TIMING_INT2_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x105C)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1060)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT3_1X_PERIOD_UNION */
#define CBBP_TIMING_INT3_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1064)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT3_1X_EN_UNION */
#define CBBP_TIMING_INT3_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1068)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x106C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT4_1X_PERIOD_UNION */
#define CBBP_TIMING_INT4_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1070)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT4_1X_EN_UNION */
#define CBBP_TIMING_INT4_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1074)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1078)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT5_1X_PERIOD_UNION */
#define CBBP_TIMING_INT5_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x107C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT5_1X_EN_UNION */
#define CBBP_TIMING_INT5_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1080)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   Int在sys_cnt_1x上的位置：
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度；
             
   UNION结构:  CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION */
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1084)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1.25ms；
             5：表示中断周期为5ms；
             6：表示中断周期为10ms；
             7：表示中断周期为20ms；
             8：表示中断周期为40ms；
             9：表示中断周期为80ms；
             10:表示中断周期为384chip；
             
   UNION结构:  CBBP_TIMING_INT6_1X_PERIOD_UNION */
#define CBBP_TIMING_INT6_1X_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1088)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT6_1X_EN_UNION */
#define CBBP_TIMING_INT6_1X_EN_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x108C)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_1x值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1090)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:5]   保留
 bit[4:0]    软件配置的第一个上报定时信息的中断时刻的sys_cnt_1x的值：
             
             [21:16]，sys_cnt_1x_80ms的值；
             [4:0]，sys_cnt_1x_1p25ms的值,64chip精度；
             
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT1_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT1_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1094)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_1x值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1098)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:5]   保留
 bit[4:0]    软件配置的第2个上报定时信息的中断时刻的sys_cnt_1x的值：
             
             [21:16]，sys_cnt_1x_80ms的值；
             [4:0]，sys_cnt_1x_1p25ms的值,64chip精度；
             
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT2_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT2_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x109C)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_1x值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x10A0)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:16]  
 bit[15:5]   保留
 bit[4:0]    软件配置的第3个上报定时信息的中断时刻的sys_cnt_1x的值：
             
             [21:16]，sys_cnt_1x_80ms的值；
             [4:0]，sys_cnt_1x_1p25ms的值,64chip精度；
             
   UNION结构:  CBBP_SYS_CNT_1X_RPT_INT3_UNION */
#define CBBP_SYS_CNT_1X_RPT_INT3_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x10A4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1x系统计数器sys_cnt_1x的周期
             0表示周期为2s；
             1表示周期为5.12s
   UNION结构:  CBBP_SYS_CNT_1X_PERIOD_UNION */
#define CBBP_SYS_CNT_1X_PERIOD_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x10A8)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   sys_cnt_1x的值：
             [29:24]，sys_cnt_1x_5p12s的值；
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms的值,chip精度；
             
             软件直接读取，BBP未做锁存处理；建议软件读取2~3次，确认读取到稳定的结果再使用
             
   UNION结构:  CBBP_SYS_CNT_1X_RPT2_UNION */
#define CBBP_SYS_CNT_1X_RPT2_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x10B8)

/* 寄存器说明：
   详      述：sys_cnt_1x高位上报结果，与SYS_CNT_1X_RPT一起上报。
            软件直接读取，BBP未做锁存处理
   UNION结构 ：无 */
#define CBBP_SYS_CNT_1X_HIGH_RPT2_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x10BC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      当前系统中是否存在1x定时。
             1：表示存在1x定时；
             
   UNION结构:  CBBP_C_TIMING_MODE_1X_UNION */
#define CBBP_C_TIMING_MODE_1X_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x10C0)

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
#define CBBP_SLEEP_TIME_1X_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x10C8)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    唤醒时，使用串行口传输定时信息的时间，单位chip
   UNION结构:  CBBP_SSI_TRANS_COMP_1X_UNION */
#define CBBP_SSI_TRANS_COMP_1X_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x10D0)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    更新sys_cnt_evdo的时刻：
             [28:24]，base_cnt_2s上的时刻，，取值范围0~24；
             [23:22]，base_cnt_80ms上的时刻，取值范围0~2；
             [21:5]，base_cnt_26ms上的时刻，取值范围0~32768*32-1；
             [4:0],1/4chip内计数，取值范围0~24
             
   UNION结构:  CBBP_SYS_CNT_EVDO_GET_POS_UNION */
#define CBBP_SYS_CNT_EVDO_GET_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1100)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_evdo_get_pos时刻sys_cnt_evdo的值：
             [28:24]，sys_cnt_evdo_5p12s的值；
             [31:22]，sys_cnt_evdo_80ms的值；
             [21:5]，sys_cnt_evdo_26ms的值；
             [4:0]，1/4chip内计数，0~24
             
   UNION结构:  CBBP_SYS_CNT_EVDO_GET_VALUE_UNION */
#define CBBP_SYS_CNT_EVDO_GET_VALUE_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x1104)

/* 寄存器说明：
   详      述：sys_cnt_get_pos时刻sys_cnt_evdo的值，单位5.12s或2s
   UNION结构 ：无 */
#define CBBP_SYS_CNT_EVDO_GET_VALUE_HIGH_ADDR         (SOC_BBP_CDMA_BASE_ADDR + 0x1180)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    定时突变后sys_cnt_evdo  80ms帧头在base_cnt上的位置。
             Bit[4:0]：1/4chip内计数0~24
             bit[21:5]：26ms内计数0~32768*4-1
             bit[23:22]：80ms内计数0~2
   UNION结构:  CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x1224)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      Sys_cnt_evdo定时获取指示。
             BBP接收到此指示后，等待base_cnt上sys_cnt_evdo_get_pos时刻，将sys_cnt_evdo更新为sys_cnt_evdo_get_value。
             
   UNION结构:  CBBP_SYS_CNT_EVDO_GET_RDY_UNION */
#define CBBP_SYS_CNT_EVDO_GET_RDY_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1108)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      系统定时调整方向。
             0：表示往左边调整6clk；
             1：表示往右边调整6clk；
             说明：定时采用100倍时钟，因此，6clk时间为6/100chip
             
   UNION结构:  CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION */
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0x110C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      系统定时调整指示。
             BBP在接收到此指示后，在最近的时隙头完成系统定时调整。
             
   UNION结构:  CBBP_SYS_EVDO_CHANGE_RDY_UNION */
#define CBBP_SYS_EVDO_CHANGE_RDY_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1110)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件读取sys_cnt_evdo_80ms_pos的指示
   UNION结构:  CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1114)

/* 寄存器说明：
 bit[31]     读取sys_cnt_evdo_80ms_pos有效指示，1有效
 bit[30:24]  保留
 bit[23:22]  
 bit[21:5]   
 bit[4:0]    sys_cnt_evdo  80ms帧头在base_cnt上的位置。
             Bit[4:0]：1/4chip内计数0~24
             bit[21:5]：26ms内计数0~32768*4-1
             bit[23:22]：80ms内计数0~2
   UNION结构:  CBBP_SYS_CNT_EVDO_80MS_POS_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1118)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      sys_cnt_evdo_80ms_pos_valid清零信号
   UNION结构:  CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION */
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_ADDR     (SOC_BBP_CDMA_BASE_ADDR + 0x111C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时突变时，定时中断的mask。
             0：表示不mask；
             1：表示mask配置范围内的中断；
             
   UNION结构:  CBBP_TIMING_INT_EVDO_MASK_UNION */
#define CBBP_TIMING_INT_EVDO_MASK_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x1120)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   定时突变时，定时中断的mask区间，chip为单位。
   UNION结构:  CBBP_TIMING_INT_EVDO_MASK_DIS_UNION */
#define CBBP_TIMING_INT_EVDO_MASK_DIS_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1124)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1128)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT1_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT1_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x112C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT1_EVDO_EN_UNION */
#define CBBP_TIMING_INT1_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1130)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1134)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT2_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT2_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1138)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT2_EVDO_EN_UNION */
#define CBBP_TIMING_INT2_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x113C)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1140)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT3_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT3_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1144)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT3_EVDO_EN_UNION */
#define CBBP_TIMING_INT3_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1148)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x114C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT4_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT4_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1150)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT4_EVDO_EN_UNION */
#define CBBP_TIMING_INT4_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1154)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1158)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT5_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT5_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x115C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT5_EVDO_EN_UNION */
#define CBBP_TIMING_INT5_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1160)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   Int在sys_cnt_evdo上的位置：
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
   UNION结构:  CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION */
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_ADDR        (SOC_BBP_CDMA_BASE_ADDR + 0x1164)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    Int中断周期选择：
             0：表示中断周期为64chip；
             1：表示中断周期为128chip；
             2：表示中断周期为256chip；
             3：表示中断周期为512chip；
             4：表示中断周期为1024chip；
             5：表示中断周期为2048chip；
             6：表示中断周期为4096chip；
             7：表示中断周期为8192chip；
             8：表示中断周期为16384chip；
             9：表示中断周期为32768chip；
             10：表示中断周期为80ms；
             
   UNION结构:  CBBP_TIMING_INT6_EVDO_PERIOD_UNION */
#define CBBP_TIMING_INT6_EVDO_PERIOD_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x1168)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      定时中断int的使能。
             0：表示不产生int中断；
             1：表示产生int中断；
             
   UNION结构:  CBBP_TIMING_INT6_EVDO_EN_UNION */
#define CBBP_TIMING_INT6_EVDO_EN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x116C)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_evdo值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1170)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
             
             [10:0]，sys_cnt_evdo的值，64chip精度；
             
             
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT1_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT1_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1174)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_evdo值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1178)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
             
             [10:0]，sys_cnt_evdo的值，64chip精度；
             
             
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT2_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT2_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1184)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1x系统计数器sys_cnt_evdo的周期
             0表示周期为2s；
             1表示周期为5.12s
   UNION结构:  CBBP_SYS_CNT_EVDO_PERIOD_UNION */
#define CBBP_SYS_CNT_EVDO_PERIOD_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x117C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   sys_cnt_evdo的值：
             [29:24]，sys_cnt_evdo_5p12s的值；
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
             
             软件直接读取BBP结果，BBP未做锁存处理，建议软件读取2~3次，确保读取到稳定结果
             
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT2_UNION */
#define CBBP_SYS_CNT_EVDO_RPT2_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1188)

/* 寄存器说明：
   详      述：sys_cnt_evdo高位上报结果，与SYS_CNT_EVDO_RPT一起上报
            
            建议软件读取2~3次，确保读取到稳定结果
   UNION结构 ：无 */
#define CBBP_SYS_CNT_EVDO_HIGH_RPT2_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0x118C)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    软件配置上报中断时刻sys_cnt_evdo值的mask：
             bit0，为1表示上报中断1时刻的定时；
             bit1，为1表示上报中断2时刻的定时；
             …
             注意：同一时刻只能有1bit为1
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x1190)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
             
             [10:0]，sys_cnt_evdo的值，64chip精度；
             
             
   UNION结构:  CBBP_SYS_CNT_EVDO_RPT_INT3_UNION */
#define CBBP_SYS_CNT_EVDO_RPT_INT3_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1194)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      当前系统中是否存在evdo定时。
             1：表示存在evdo定时；
             
   UNION结构:  CBBP_C_TIMING_MODE_EVDO_UNION */
#define CBBP_C_TIMING_MODE_EVDO_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1198)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      C DBG模块定时选择，0表示选择1x定时，1表示选择evdo定时
   UNION结构:  CBBP_C_TIMING_SEL_DBG_UNION */
#define CBBP_C_TIMING_SEL_DBG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1200)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件同时读取1x与evdo定时的指示信号
   UNION结构:  CBBP_SYS_CNT_BOTH_RD_UNION */
#define CBBP_SYS_CNT_BOTH_RD_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1204)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件同时读取1x与evdo定时的有效信号，1表示上报的结果有效
   UNION结构:  CBBP_SYS_CNT_BOTH_RD_VALID_UNION */
#define CBBP_SYS_CNT_BOTH_RD_VALID_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1208)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:24]  
 bit[23:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   base_cnt的值：
             [28:24]，base_cnt_2s上的时刻，，取值范围0~24；
             [17:16]，base_cnt_80ms上的时刻，取值范围0~2；
             [14:0]，base_cnt_26ms上的时刻，取值范围0~32767，chip精度；
             
   UNION结构:  CBBP_BASE_CNT_BOTH_RPT_UNION */
#define CBBP_BASE_CNT_BOTH_RPT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x120C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:22]  保留
 bit[21:16]  
 bit[15:11]  保留
 bit[10:0]   sys_cnt_1x的值：
             [29:24]，sys_cnt_1x_5p12s的值；
             [21:16]，sys_cnt_1x_80ms的值；
             [10:0]，sys_cnt_1x_1p25ms的值,chip精度；
   UNION结构:  CBBP_SYS_CNT_1X_BOTH_RPT_UNION */
#define CBBP_SYS_CNT_1X_BOTH_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1210)

/* 寄存器说明：
   详      述：sys_cnt_1x高位上报结果，与SYS_CNT_1X_BOTH_RPT一起上报
   UNION结构 ：无 */
#define CBBP_SYS_CNT_1X_HIGH_BOTH_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0x1214)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  
 bit[23:18]  保留
 bit[17:16]  
 bit[15]     保留
 bit[14:0]   sys_cnt_evdo的值：
             [29:24]，sys_cnt_evdo_5p12s的值；
             [17:16]，sys_cnt_evdo_80ms的值；
             [14:0]，sys_cnt_evdo_26ms的值，chip精度；
   UNION结构:  CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION */
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x1218)

/* 寄存器说明：
   详      述：sys_cnt_evdo高位上报结果，与SYS_CNT_EVDO_BOTH_RPT一起上报
            
   UNION结构 ：无 */
#define CBBP_SYS_CNT_EVDO_HIGH_BOTH_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0x121C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      软件同时读取1x与evdo定时的有效指示信号的清零信号
   UNION结构:  CBBP_SYS_CNT_BOTH_RD_CLR_UNION */
#define CBBP_SYS_CNT_BOTH_RD_CLR_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1220)

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
#define CBBP_SLEEP_TIME_EVDO_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1228)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    唤醒时，使用串行口传输定时信息的时间，单位chip
   UNION结构:  CBBP_SSI_TRANS_COMP_EVDO_UNION */
#define CBBP_SSI_TRANS_COMP_EVDO_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x122C)



/***======================================================================***
                     (3/20) register_define_c_intr
 ***======================================================================***/
/* 寄存器说明：
   详      述：定时中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
            bit[0] CDMA 1X 可配定时中断（建议用于每个时隙产生一次，DSP根据此中断配置下个时隙的RFIC SSI、MIPI等控制字）；   
            bit[1] CDMA 1X可配定时中断2；       
            bit[2] CDMA 1X可配定时中断3；       
            bit[3] CDMA 1X可配定时中断4；       
            bit[4] CDMA 1X可配定时中断5；
            bit[5] CDMA 1X可配定时中断6；
            bit[6] Reserve for timing
            bit[7] Reserve for timing
            bit[8] Reserve for timing
            bit[9] Reserve for timing
            bit[10] Reserve for timing
            bit[11] Reserve for timing
            bit[12] Reserve for timing
            bit[13] Reserve for timing
            bit[14] Reserve for timing
            bit[15] Reserve for timing
            bit[16] CDMA EVDO可配定时中断16（建议用于每个时隙产生一次，DSP根据此中断配置下个时隙的RFIC SSI、MIPI等控制字）；
            bit[17] CDMA EVDO可配定时中断17；
            bit[18] CDMA EVDO可配定时中断18；
            bit[19] CDMA EVDO可配定时中断19；
            bit[20] CDMA EVDO可配定时中断20；
            bit[21] CDMA EVDO可配定时中断21；
            bit[22] Reserve for timing
            bit[23] Reserve for timing
            bit[24] Reserve for timing
            bit[25] Reserve for timing
            bit[26] Reserve for timing
            bit[27] Reserve for timing
            bit[28] Reserve for timing
            bit[29] Reserve for timing
            bit[30] Reserve for timing
            bit[31] 时钟测量中断
   UNION结构 ：无 */
#define CBBP_ARM_INT04_STA_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1800)

/* 寄存器说明：
   详      述：上报给ARM的定时中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构 ：无 */
#define CBBP_ARM_INT04_MASK_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1804)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断04使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  CBBP_ARM_INT04_EN_UNION */
#define CBBP_ARM_INT04_EN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x1808)

/* 寄存器说明：
   详      述：定时中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构 ：无 */
#define CBBP_ARM_INT04_CLR_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x180C)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7]      ARM_INT04超时使能，高电平有效。
 bit[6:0]    ARM_INT04超时时间。
             超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE
   UNION结构:  CBBP_ARM_OVERTIME_CFG_UNION */
#define CBBP_ARM_OVERTIME_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1810)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   防中断漏检的延迟时间，单位IMI时钟。0，禁止配置；1，表示延迟一个IMI时钟；……。必须配置为非0值。
   UNION结构:  CBBP_INT_DELAY_CLK_UNION */
#define CBBP_INT_DELAY_CLK_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1818)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   arm_int04中断超时次数。
   UNION结构:  CBBP_ARM_INT4_OT_NUM_UNION */
#define CBBP_ARM_INT4_OT_NUM_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x181C)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:0]   1ms内IMI时钟个数。软件根据当前IMI时钟频率配置，默认值为IMI时钟频率为200MHz时的1ms内时钟个数。
   UNION结构:  CBBP_OVERTIME_BASE_UNION */
#define CBBP_OVERTIME_BASE_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x1820)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:0]    多径搜索/小区测量中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
             bit[0] 多径搜索/小区测量单元0中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)       
             bit[1] 多径搜索/小区测量单元1中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
             bit[2] 多径搜索/小区测量单元2中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
             bit[3] 多径搜索/小区测量单元3中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
             bit[4] 小区搜索和多径搜索数据存储结束中断；
             bit[5] 小区和多径搜索合并中断0
             bit[6] 小区和多径搜索合并中断1
             如果配置了中断合并，如单元0和单元1合并上报，则只上报合并中断，不单独上报单元0，1的中断。
   UNION结构:  CBBP_BBE16_INT03_STA_UNION */
#define CBBP_BBE16_INT03_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1830)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:0]    多径搜索/小区测量中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT03_MASK_UNION */
#define CBBP_BBE16_INT03_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1834)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  CBBP_BBE16_INT03_EN_UNION */
#define CBBP_BBE16_INT03_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1838)

/* 寄存器说明：
 bit[31:7]   保留
 bit[6:0]    多径搜索/小区测量中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT03_CLR_UNION */
#define CBBP_BBE16_INT03_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x183C)

/* 寄存器说明：
   详      述：定时中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
            bit[0] CDMA 1X 可配定时中断（建议用于每个时隙产生一次，DSP根据此中断配置下个时隙的RFIC SSI、MIPI等控制字）；   
            bit[1] CDMA 1X可配定时中断2；       
            bit[2] CDMA 1X可配定时中断3；       
            bit[3] CDMA 1X可配定时中断4；       
            bit[4] CDMA 1X可配定时中断5；
            bit[5] CDMA 1X可配定时中断6；
            bit[6] Reserve for timing
            bit[7] Reserve for timing
            bit[8] Reserve for timing
            bit[9] Reserve for timing
            bit[10] Reserve for timing
            bit[11] Reserve for timing
            bit[12] Reserve for timing
            bit[13] Reserve for timing
            bit[14] Reserve for timing
            bit[15] Reserve for timing
            bit[16] CDMA EVDO可配定时中断16（建议用于每个时隙产生一次，DSP根据此中断配置下个时隙的RFIC SSI、MIPI等控制字）；
            bit[17] CDMA EVDO可配定时中断17；
            bit[18] CDMA EVDO可配定时中断18；
            bit[19] CDMA EVDO可配定时中断19；
            bit[20] CDMA EVDO可配定时中断20；
            bit[21] CDMA EVDO可配定时中断21；
            bit[22] Reserve for timing
            bit[23] Reserve for timing
            bit[24] Reserve for timing
            bit[25] Reserve for timing
            bit[26] Reserve for timing
            bit[27] Reserve for timing
            bit[28] Reserve for timing
            bit[29] Reserve for timing
            bit[30] Reserve for timing
            bit[31] 时钟测量中断
   UNION结构 ：无 */
#define CBBP_BBE16_INT04_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1840)

/* 寄存器说明：
   详      述：定时中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构 ：无 */
#define CBBP_BBE16_INT04_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1844)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断04使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  CBBP_BBE16_INT04_EN_UNION */
#define CBBP_BBE16_INT04_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1848)

/* 寄存器说明：
   详      述：定时中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构 ：无 */
#define CBBP_BBE16_INT04_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x184C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    译码/编码中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
             bit[0]下行译码完成中断；
             bit[1] Reserve for timing       
             bit[2] Reserve for timing
             bit[3] Reserve for timing
             bit[4]编码上报中断，通知软件读取编码数据； 
   UNION结构:  CBBP_BBE16_INT05_STA_UNION */
#define CBBP_BBE16_INT05_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1850)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    译码/编码中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT05_MASK_UNION */
#define CBBP_BBE16_INT05_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1854)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  CBBP_BBE16_INT05_EN_UNION */
#define CBBP_BBE16_INT05_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1858)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    译码/编码中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT05_CLR_UNION */
#define CBBP_BBE16_INT05_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x185C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    射频上报/数据搬移中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
             bit[0]每个时隙产生一次，DSP收到此中断后读取PD结果再计算；
             bit[1]下行天线1前端数据搬运出错上报中断；   
             bit[2]下行天线2前端数据搬运出错上报中断；     
             bit[3]上行前端数据搬运出错上报中断； 
             bit[4]上行前端数据BBPMST搬运完成中断。
   UNION结构:  CBBP_BBE16_INT06_STA_UNION */
#define CBBP_BBE16_INT06_STA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x1860)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    射频上报/数据搬移中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT06_MASK_UNION */
#define CBBP_BBE16_INT06_MASK_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x1864)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      中断使能寄存器。1，表示使能中断；0，表示不使能中断。
   UNION结构:  CBBP_BBE16_INT06_EN_UNION */
#define CBBP_BBE16_INT06_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x1868)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    射频上报/数据搬移中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。
   UNION结构:  CBBP_BBE16_INT06_CLR_UNION */
#define CBBP_BBE16_INT06_CLR_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x186C)

/* 寄存器说明：
 bit[31]     BBE16_INT06超时使能，高电平有效。
 bit[30:24]  BBE16_INT06超时时间。
             超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE
 bit[23]     bbe16_INT05超时使能，高电平有效。
 bit[22:16]  bbe16_INT05超时时间。
             超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE
 bit[15]     bbe16_INT04超时使能，高电平有效。
 bit[14:8]   bbe16_INT04超时时间。
             超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE
 bit[7]      bbe16_INT03超时使能，高电平有效。
 bit[6:0]    bbe16_INT03超时时间。
             超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE
   UNION结构:  CBBP_BBE16_OVERTIME_CFG_UNION */
#define CBBP_BBE16_OVERTIME_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1870)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    中断超时指示，高电平有效。
             bit[0]：bbe16_INT03。
             bit[1]：bbe16_INT04。
             bit[2]：bbe16_INT05。
             bit[3]：bbe16_INT06。
             bit[4]：arm_INT04。
   UNION结构:  CBBP_INT_OVERTIME_FLAG_UNION */
#define CBBP_INT_OVERTIME_FLAG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x1874)

/* 寄存器说明：
 bit[31:16]  BBE16_int04中断超时次数。
 bit[15:0]   bbe16_int03中断超时次数。
   UNION结构:  CBBP_BBE16_INT34_OT_NUM_UNION */
#define CBBP_BBE16_INT34_OT_NUM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x1878)

/* 寄存器说明：
 bit[31:16]  BBE16_int06中断超时次数。
 bit[15:0]   bbe16_int05中断超时次数。
   UNION结构:  CBBP_BBE16_INT56_OT_NUM_UNION */
#define CBBP_BBE16_INT56_OT_NUM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x187C)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:5]    小区和多径搜索Group1中断合并上报模式，[8:5]表示对应单元3~0中断，bit[9]表示存储单元中断；
             对应bit配置为1表示对应单元中断在Group1合并上报。合并中断的配置说明，见接口说明书的《中断》章节
 bit[4:0]    小区和多径搜索Group0中断合并上报模式，[3:0]表示对应单元3~0中断，bit[4]表示存储单元中断；
             对应bit配置为1表示对应单元中断在Group1合并上报。合并中断的配置说明，见接口说明书的《中断》章节
   UNION结构:  CBBP_CS_MPS_GRP_INT_MODE_UNION */
#define CBBP_CS_MPS_GRP_INT_MODE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x1880)



/***======================================================================***
                     (4/20) register_define_c_cs_mps_store
 ***======================================================================***/
/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   存储数据长度，chip单位，
             按照目前算法：
             1x小区搜索时，存储长度2048chip
             Evdo小区搜索时，存储长度64x32=2048chip或64x16=1024chip或64x8=512chip
             1x小区测量时，64x12（相干）x4（非相干）=3072chip；
             Evdo小区测量时，96x4（相干）x8（非相干）=3072chip。
             
   UNION结构:  CBBP_DATA_STORE_LENGTH_UNION */
#define CBBP_DATA_STORE_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2F00)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    数据存储方式：
             0表示连续存储，
             1表示每1024chip缓存64chip，
             2表示每1024chip缓存96chip，
             3表示每1024chip缓存128chip，
             4表示每1024chip缓存256chip，
             5表示每1024chip缓存512chip，
             
   UNION结构:  CBBP_DATA_STORE_MODE_UNION */
#define CBBP_DATA_STORE_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2F04)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   存储数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度
   UNION结构:  CBBP_DATA_STORE_POS_UNION */
#define CBBP_DATA_STORE_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2F08)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      存储数据天线选择：
             为0表示存储接收天线1的数据
             为1表示存储接收天线2的数据
             
   UNION结构:  CBBP_DATA_STORE_ANT_UNION */
#define CBBP_DATA_STORE_ANT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2F0C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      存储数据起始位置选择信号，
             0表示可以就近开始存储数据；
             1表示必须等到 Data_store_pos，才能开始存储数据；
             
   UNION结构:  CBBP_DATA_STORE_POS_SEL_UNION */
#define CBBP_DATA_STORE_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2F10)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      自动时钟门控bypass，1表示时钟常开
   UNION结构:  CBBP_DATA_STORE_CK_BYPASS_UNION */
#define CBBP_DATA_STORE_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2F14)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      数据存储模块使能，作为本模块的总使能，并控制本模块的时钟开关
             在 Data_store_start之前配置为1，在接收到中断后，配置为0
             
   UNION结构:  CBBP_DATA_STORE_EN_UNION */
#define CBBP_DATA_STORE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x2F18)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      存储数据启动脉冲信号
   UNION结构:  CBBP_DATA_STORE_START_UNION */
#define CBBP_DATA_STORE_START_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2F1C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      FPGA专用
             物理层读取缓存数据的开始信号，BBP检测到此信号后，将读取地址恢复到第一个数据的位置
   UNION结构:  CBBP_DSP_RD_DATA_START_UNION */
#define CBBP_DSP_RD_DATA_START_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2F20)

/* 寄存器说明：
   详      述：FPGA专用
            物理层软件从BBP读取的缓存数据
   UNION结构 ：无 */
#define CBBP_DSP_RD_DATA_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x2F24)



/***======================================================================***
                     (5/20) register_define_c_cs_mps_unit0
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元时钟频率选择
             0：表示搜索单元128倍时钟；
             1：表示搜索单元64倍时钟
             默认不需要软件配置
             
   UNION结构:  CBBP_UNIT0_CLK_MODE_UNION */
#define CBBP_UNIT0_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2000)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
             此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
             对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
             对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
             对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果；
             
   UNION结构:  CBBP_UNIT0_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT0_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2004)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
             此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
             仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置
   UNION结构:  CBBP_UNIT0_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT0_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2008)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据天线选择
             0：表示输入接收天线1的数据；
             1：表示输入接收天线2的数据；
             
   UNION结构:  CBBP_UNIT0_ANT_SEL_UNION */
#define CBBP_UNIT0_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x200C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    模式选择。
             0：表示初始小区搜索
             1：表示pn列表小区搜索
             2：表示多径搜索、小区测量（仅完成相干累加）
             3：表示小区测量（完成相干累加与非相干累加）
             
   UNION结构:  CBBP_UNIT0_MODE_UNION */
#define CBBP_UNIT0_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2010)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    搜索窗宽，单位为64chip，配置范围为1~512。
             
             初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
             PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
             多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
             小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip
             
   UNION结构:  CBBP_UNIT0_WIN_UNION */
#define CBBP_UNIT0_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2014)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据选择。
             0：表示使用实时数据；
             1：表示使用缓存的数据
             
   UNION结构:  CBBP_UNIT0_DATA_SEL_UNION */
#define CBBP_UNIT0_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2018)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
             0表示连续存储，
             1表示每1024chip存储64chip，
             2表示每1024chip存储96chip，
             3表示每1024chip存储128chip，
             4表示每1024chip存储256chip，
             5表示每1024chip存储512chip，
             
   UNION结构:  CBBP_UNIT0_DATA_STORE_MODE_UNION */
#define CBBP_UNIT0_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x201C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度
             
   UNION结构:  CBBP_UNIT0_DATA_POS_UNION */
#define CBBP_UNIT0_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2020)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      使用实时数据时有效。
             0：表示可以就近开始搜索；
             1：必须等待Unit0_data_pos时，才能开始搜索；
             
   UNION结构:  CBBP_UNIT0_DATA_POS_SEL_UNION */
#define CBBP_UNIT0_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2024)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    输入数据取数方式：
             0表示连续取数，
             1表示每1024chip取数64chip，
             2表示每1024chip取数96chip，
             3表示每1024chip取数128chip，
             4表示每1024chip取数256chip，
             5表示每1024chip存储512chip，
             
             说明：
             对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
             对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。
             
   UNION结构:  CBBP_UNIT0_DATA_MODE_UNION */
#define CBBP_UNIT0_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2028)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    Pn列表小区搜索时，pn offset个数，支持1~16个
   UNION结构:  CBBP_UNIT0_PN_NUM_UNION */
#define CBBP_UNIT0_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x202C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    相干长度
             0：32
             1：64
             2：96
             3：128
             4：256
             5：96*4=384
             6：64*12=768
             7：512
             算法推荐：
             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。
             
   UNION结构:  CBBP_UNIT0_CORR_LENGTH_UNION */
#define CBBP_UNIT0_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2030)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    非相干长度
             0：1
             1：2
             2：3
             3：4
             4：8
             5：16
             6：32
             7：96
             
             
             
             
   UNION结构:  CBBP_UNIT0_NCORR_LENGTH_UNION */
#define CBBP_UNIT0_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2034)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   绝对噪声门限
   UNION结构:  CBBP_UNIT0_ABS_TH_UNION */
#define CBBP_UNIT0_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2038)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元使能信号
   UNION结构:  CBBP_UNIT0_EN_UNION */
#define CBBP_UNIT0_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x203C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   单元0本次小区搜索上报的噪声门限
   UNION结构:  CBBP_UNIT0_NOISE_ENERGY_UNION */
#define CBBP_UNIT0_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2040)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
             0：表示上报搜索窗与配置搜索窗完全一致
             1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip
             
   UNION结构:  CBBP_UNIT0_FRAME_SHIFT_UNION */
#define CBBP_UNIT0_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2044)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
             如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN0_FRAME_POS_UNION */
#define CBBP_UNIT0_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2048)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN1_FRAME_POS_UNION */
#define CBBP_UNIT0_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x204C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN2_FRAME_POS_UNION */
#define CBBP_UNIT0_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2050)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN3_FRAME_POS_UNION */
#define CBBP_UNIT0_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2054)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN4_FRAME_POS_UNION */
#define CBBP_UNIT0_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2058)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN5_FRAME_POS_UNION */
#define CBBP_UNIT0_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x205C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN6_FRAME_POS_UNION */
#define CBBP_UNIT0_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2060)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN7_FRAME_POS_UNION */
#define CBBP_UNIT0_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2064)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN8_FRAME_POS_UNION */
#define CBBP_UNIT0_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2068)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN9_FRAME_POS_UNION */
#define CBBP_UNIT0_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x206C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN10_FRAME_POS_UNION */
#define CBBP_UNIT0_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2070)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN11_FRAME_POS_UNION */
#define CBBP_UNIT0_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2074)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN12_FRAME_POS_UNION */
#define CBBP_UNIT0_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2078)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN13_FRAME_POS_UNION */
#define CBBP_UNIT0_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x207C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN14_FRAME_POS_UNION */
#define CBBP_UNIT0_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2080)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT0_PN15_FRAME_POS_UNION */
#define CBBP_UNIT0_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2084)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索模式选择
             0表示1x搜索
             1表示evdo搜索
   UNION结构:  CBBP_UNIT0_CS_1X_MODE_UNION */
#define CBBP_UNIT0_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2088)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      搜索单元上报模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[1]      搜索单元排队模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[0]      搜索单元控制部分时钟门控bypass
             0表示时钟门控有效
             1表示时钟常开
   UNION结构:  CBBP_UNIT0_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT0_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x208C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    噪声门限滤波系数：
             0：1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION结构:  CBBP_UNIT0_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT0_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2090)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    从缓存数据中取数偏移，chip单位。
             使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定
   UNION结构:  CBBP_UNIT0_DATA_STORE_OFF_UNION */
#define CBBP_UNIT0_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2094)



/***======================================================================***
                     (6/20) register_define_c_cs_mps_unit1
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元时钟频率选择
             0：表示搜索单元128倍时钟；
             1：表示搜索单元64倍时钟
             默认不需要软件配置
             
   UNION结构:  CBBP_UNIT1_CLK_MODE_UNION */
#define CBBP_UNIT1_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2300)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
             此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
             对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
             对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
             对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果；
             
   UNION结构:  CBBP_UNIT1_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT1_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2304)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
             此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
             仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置
   UNION结构:  CBBP_UNIT1_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT1_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2308)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据天线选择
             0：表示输入接收天线1的数据；
             1：表示输入接收天线2的数据；
             
   UNION结构:  CBBP_UNIT1_ANT_SEL_UNION */
#define CBBP_UNIT1_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x230C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    模式选择。
             0：表示初始小区搜索
             1：表示pn列表小区搜索
             2：表示多径搜索、小区测量（仅完成相干累加）
             3：表示小区测量（完成相干累加与非相干累加）
             
   UNION结构:  CBBP_UNIT1_MODE_UNION */
#define CBBP_UNIT1_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2310)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    搜索窗宽，单位为64chip，配置范围为1~512。
             
             初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
             PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
             多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
             小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip
             
   UNION结构:  CBBP_UNIT1_WIN_UNION */
#define CBBP_UNIT1_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2314)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据选择。
             0：表示使用实时数据；
             1：表示使用缓存的数据
             
   UNION结构:  CBBP_UNIT1_DATA_SEL_UNION */
#define CBBP_UNIT1_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2318)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
             0表示连续存储，
             1表示每1024chip存储64chip，
             2表示每1024chip存储96chip，
             3表示每1024chip存储128chip，
             4表示每1024chip存储256chip
             5表示每1024chip存储512chip，
             
   UNION结构:  CBBP_UNIT1_DATA_STORE_MODE_UNION */
#define CBBP_UNIT1_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x231C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度
             
   UNION结构:  CBBP_UNIT1_DATA_POS_UNION */
#define CBBP_UNIT1_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2320)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      使用实时数据时有效。
             0：表示可以就近开始搜索；
             1：必须等待Unit0_data_pos时，才能开始搜索；
             
   UNION结构:  CBBP_UNIT1_DATA_POS_SEL_UNION */
#define CBBP_UNIT1_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2324)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    输入数据取数方式：
             0表示连续取数，
             1表示每1024chip取数64chip，
             2表示每1024chip取数96chip，
             3表示每1024chip取数128chip，
             4表示每1024chip取数256chip
             5表示每1024chip存储512chip，
             
             说明：
             对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
             对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。
             
   UNION结构:  CBBP_UNIT1_DATA_MODE_UNION */
#define CBBP_UNIT1_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2328)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    Pn列表小区搜索时，pn offset个数，支持1~16个
   UNION结构:  CBBP_UNIT1_PN_NUM_UNION */
#define CBBP_UNIT1_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x232C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    相干长度
             0：32
             1：64
             2：96
             3：128
             4：256
             5：96*4=384
             6：64*12=768
             7：512
             算法推荐：
             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。
             
   UNION结构:  CBBP_UNIT1_CORR_LENGTH_UNION */
#define CBBP_UNIT1_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2330)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    非相干长度
             0：1
             1：2
             2：3
             3：4
             4：8
             5：16
             6：32
             7：96
             
             
             
             
   UNION结构:  CBBP_UNIT1_NCORR_LENGTH_UNION */
#define CBBP_UNIT1_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2334)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   绝对噪声门限
   UNION结构:  CBBP_UNIT1_ABS_TH_UNION */
#define CBBP_UNIT1_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2338)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元使能信号
   UNION结构:  CBBP_UNIT1_EN_UNION */
#define CBBP_UNIT1_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x233C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   单元0本次小区搜索上报的噪声门限
   UNION结构:  CBBP_UNIT1_NOISE_ENERGY_UNION */
#define CBBP_UNIT1_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2340)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
             0：表示上报搜索窗与配置搜索窗完全一致
             1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip
             
   UNION结构:  CBBP_UNIT1_FRAME_SHIFT_UNION */
#define CBBP_UNIT1_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2344)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
             如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN0_FRAME_POS_UNION */
#define CBBP_UNIT1_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2348)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN1_FRAME_POS_UNION */
#define CBBP_UNIT1_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x234C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN2_FRAME_POS_UNION */
#define CBBP_UNIT1_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2350)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN3_FRAME_POS_UNION */
#define CBBP_UNIT1_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2354)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN4_FRAME_POS_UNION */
#define CBBP_UNIT1_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2358)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN5_FRAME_POS_UNION */
#define CBBP_UNIT1_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x235C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN6_FRAME_POS_UNION */
#define CBBP_UNIT1_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2360)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN7_FRAME_POS_UNION */
#define CBBP_UNIT1_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2364)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN8_FRAME_POS_UNION */
#define CBBP_UNIT1_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2368)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN9_FRAME_POS_UNION */
#define CBBP_UNIT1_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x236C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN10_FRAME_POS_UNION */
#define CBBP_UNIT1_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2370)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN11_FRAME_POS_UNION */
#define CBBP_UNIT1_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2374)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN12_FRAME_POS_UNION */
#define CBBP_UNIT1_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2378)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN13_FRAME_POS_UNION */
#define CBBP_UNIT1_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x237C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN14_FRAME_POS_UNION */
#define CBBP_UNIT1_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2380)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT1_PN15_FRAME_POS_UNION */
#define CBBP_UNIT1_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2384)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索模式选择
             0表示1x搜索
             1表示evdo搜索
   UNION结构:  CBBP_UNIT1_CS_1X_MODE_UNION */
#define CBBP_UNIT1_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2388)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      搜索单元上报模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[1]      搜索单元排队模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[0]      搜索单元控制部分时钟门控bypass
             0表示时钟门控有效
             1表示时钟常开
   UNION结构:  CBBP_UNIT1_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT1_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x238C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    噪声门限滤波系数：
             0：1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION结构:  CBBP_UNIT1_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT1_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2390)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    从缓存数据中取数偏移，chip单位。
             使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定
   UNION结构:  CBBP_UNIT1_DATA_STORE_OFF_UNION */
#define CBBP_UNIT1_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2394)



/***======================================================================***
                     (7/20) register_define_c_cs_mps_unit2
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元时钟频率选择
             0：表示搜索单元128倍时钟；
             1：表示搜索单元64倍时钟
             默认不需要软件配置
             
   UNION结构:  CBBP_UNIT2_CLK_MODE_UNION */
#define CBBP_UNIT2_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2600)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
             此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
             对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
             对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
             对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果；
             
   UNION结构:  CBBP_UNIT2_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT2_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2604)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
             此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
             仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置
   UNION结构:  CBBP_UNIT2_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT2_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2608)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据天线选择
             0：表示输入接收天线1的数据；
             1：表示输入接收天线2的数据；
             
   UNION结构:  CBBP_UNIT2_ANT_SEL_UNION */
#define CBBP_UNIT2_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x260C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    模式选择。
             0：表示初始小区搜索
             1：表示pn列表小区搜索
             2：表示多径搜索、小区测量（仅完成相干累加）
             3：表示小区测量（完成相干累加与非相干累加）
             
   UNION结构:  CBBP_UNIT2_MODE_UNION */
#define CBBP_UNIT2_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2610)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    搜索窗宽，单位为64chip，配置范围为1~512。
             
             初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
             PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
             多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
             小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip
             
   UNION结构:  CBBP_UNIT2_WIN_UNION */
#define CBBP_UNIT2_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2614)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据选择。
             0：表示使用实时数据；
             1：表示使用缓存的数据
             
   UNION结构:  CBBP_UNIT2_DATA_SEL_UNION */
#define CBBP_UNIT2_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2618)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
             0表示连续存储，
             1表示每1024chip存储64chip，
             2表示每1024chip存储96chip，
             3表示每1024chip存储128chip，
             4表示每1024chip存储256chip
             5表示每1024chip存储512chip，
             
   UNION结构:  CBBP_UNIT2_DATA_STORE_MODE_UNION */
#define CBBP_UNIT2_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x261C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度
             
   UNION结构:  CBBP_UNIT2_DATA_POS_UNION */
#define CBBP_UNIT2_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2620)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      使用实时数据时有效。
             0：表示可以就近开始搜索；
             1：必须等待Unit0_data_pos时，才能开始搜索；
             
   UNION结构:  CBBP_UNIT2_DATA_POS_SEL_UNION */
#define CBBP_UNIT2_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2624)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    输入数据取数方式：
             0表示连续取数，
             1表示每1024chip取数64chip，
             2表示每1024chip取数96chip，
             3表示每1024chip取数128chip，
             4表示每1024chip取数256chip
             5表示每1024chip存储512chip，
             
             说明：
             对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
             对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。
             
   UNION结构:  CBBP_UNIT2_DATA_MODE_UNION */
#define CBBP_UNIT2_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2628)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    Pn列表小区搜索时，pn offset个数，支持1~16个
   UNION结构:  CBBP_UNIT2_PN_NUM_UNION */
#define CBBP_UNIT2_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x262C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    相干长度
             0：32
             1：64
             2：96
             3：128
             4：256
             5：96*4=384
             6：64*12=768
             7：512
             算法推荐：
             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。
             
   UNION结构:  CBBP_UNIT2_CORR_LENGTH_UNION */
#define CBBP_UNIT2_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2630)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    非相干长度
             0：1
             1：2
             2：3
             3：4
             4：8
             5：16
             6：32
             7：96
             
             
             
             
   UNION结构:  CBBP_UNIT2_NCORR_LENGTH_UNION */
#define CBBP_UNIT2_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2634)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   绝对噪声门限
   UNION结构:  CBBP_UNIT2_ABS_TH_UNION */
#define CBBP_UNIT2_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2638)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元使能信号
   UNION结构:  CBBP_UNIT2_EN_UNION */
#define CBBP_UNIT2_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x263C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   单元0本次小区搜索上报的噪声门限
   UNION结构:  CBBP_UNIT2_NOISE_ENERGY_UNION */
#define CBBP_UNIT2_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2640)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
             0：表示上报搜索窗与配置搜索窗完全一致
             1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip
             
   UNION结构:  CBBP_UNIT2_FRAME_SHIFT_UNION */
#define CBBP_UNIT2_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2644)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
             如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN0_FRAME_POS_UNION */
#define CBBP_UNIT2_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2648)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN1_FRAME_POS_UNION */
#define CBBP_UNIT2_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x264C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN2_FRAME_POS_UNION */
#define CBBP_UNIT2_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2650)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN3_FRAME_POS_UNION */
#define CBBP_UNIT2_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2654)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN4_FRAME_POS_UNION */
#define CBBP_UNIT2_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2658)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN5_FRAME_POS_UNION */
#define CBBP_UNIT2_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x265C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN6_FRAME_POS_UNION */
#define CBBP_UNIT2_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2660)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN7_FRAME_POS_UNION */
#define CBBP_UNIT2_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2664)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN8_FRAME_POS_UNION */
#define CBBP_UNIT2_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2668)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN9_FRAME_POS_UNION */
#define CBBP_UNIT2_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x266C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN10_FRAME_POS_UNION */
#define CBBP_UNIT2_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2670)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN11_FRAME_POS_UNION */
#define CBBP_UNIT2_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2674)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN12_FRAME_POS_UNION */
#define CBBP_UNIT2_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2678)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN13_FRAME_POS_UNION */
#define CBBP_UNIT2_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x267C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN14_FRAME_POS_UNION */
#define CBBP_UNIT2_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2680)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT2_PN15_FRAME_POS_UNION */
#define CBBP_UNIT2_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2684)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索模式选择
             0表示1x搜索
             1表示evdo搜索
   UNION结构:  CBBP_UNIT2_CS_1X_MODE_UNION */
#define CBBP_UNIT2_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2688)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      搜索单元上报模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[1]      搜索单元排队模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[0]      搜索单元控制部分时钟门控bypass
             0表示时钟门控有效
             1表示时钟常开
   UNION结构:  CBBP_UNIT2_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT2_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x268C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    噪声门限滤波系数：
             0：1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION结构:  CBBP_UNIT2_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT2_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2690)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    从缓存数据中取数偏移，chip单位。
             使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定
   UNION结构:  CBBP_UNIT2_DATA_STORE_OFF_UNION */
#define CBBP_UNIT2_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2694)



/***======================================================================***
                     (8/20) register_define_c_cs_mps_unit3
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元时钟频率选择
             0：表示搜索单元128倍时钟；
             1：表示搜索单元64倍时钟
             默认不需要软件配置
             
   UNION结构:  CBBP_UNIT3_CLK_MODE_UNION */
#define CBBP_UNIT3_CLK_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2900)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
             此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
             对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
             对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
             对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果；
             
   UNION结构:  CBBP_UNIT3_CORR_RPT_PERIOD_UNION */
#define CBBP_UNIT3_CORR_RPT_PERIOD_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x2904)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
             此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
             仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置
   UNION结构:  CBBP_UNIT3_CORR_WAIT_CHIP_UNION */
#define CBBP_UNIT3_CORR_WAIT_CHIP_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2908)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据天线选择
             0：表示输入接收天线1的数据；
             1：表示输入接收天线2的数据；
             
   UNION结构:  CBBP_UNIT3_ANT_SEL_UNION */
#define CBBP_UNIT3_ANT_SEL_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x290C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    模式选择。
             0：表示初始小区搜索
             1：表示pn列表小区搜索
             2：表示多径搜索、小区测量（仅完成相干累加）
             3：表示小区测量（完成相干累加与非相干累加）
             
   UNION结构:  CBBP_UNIT3_MODE_UNION */
#define CBBP_UNIT3_MODE_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x2910)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    搜索窗宽，单位为64chip，配置范围为1~512。
             
             初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
             PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
             多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
             小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip；
             
   UNION结构:  CBBP_UNIT3_WIN_UNION */
#define CBBP_UNIT3_WIN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x2914)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      输入数据选择。
             0：表示使用实时数据；
             1：表示使用缓存的数据
             
   UNION结构:  CBBP_UNIT3_DATA_SEL_UNION */
#define CBBP_UNIT3_DATA_SEL_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2918)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
             0表示连续存储，
             1表示每1024chip存储64chip，
             2表示每1024chip存储96chip，
             3表示每1024chip存储128chip，
             4表示每1024chip存储256chip
             5表示每1024chip存储512chip，
             
   UNION结构:  CBBP_UNIT3_DATA_STORE_MODE_UNION */
#define CBBP_UNIT3_DATA_STORE_MODE_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x291C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度
             
   UNION结构:  CBBP_UNIT3_DATA_POS_UNION */
#define CBBP_UNIT3_DATA_POS_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x2920)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      使用实时数据时有效。
             0：表示可以就近开始搜索；
             1：必须等待Unit0_data_pos时，才能开始搜索；
             
   UNION结构:  CBBP_UNIT3_DATA_POS_SEL_UNION */
#define CBBP_UNIT3_DATA_POS_SEL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2924)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    输入数据取数方式：
             0表示连续取数，
             1表示每1024chip取数64chip，
             2表示每1024chip取数96chip，
             3表示每1024chip取数128chip，
             4表示每1024chip取数256chip
             5表示每1024chip存储512chip，
             
             说明：
             对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
             对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。
             
   UNION结构:  CBBP_UNIT3_DATA_MODE_UNION */
#define CBBP_UNIT3_DATA_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x2928)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    Pn列表小区搜索时，pn offset个数，支持1~16个
   UNION结构:  CBBP_UNIT3_PN_NUM_UNION */
#define CBBP_UNIT3_PN_NUM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x292C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    相干长度
             0：32
             1：64
             2：96
             3：128
             4：256
             5：96*4=384
             6：64*12=768
             7：512
             算法推荐：
             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。
             
   UNION结构:  CBBP_UNIT3_CORR_LENGTH_UNION */
#define CBBP_UNIT3_CORR_LENGTH_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2930)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    非相干长度
             0：1
             1：2
             2：3
             3：4
             4：8
             5：16
             6：32
             7：96
             
             
             
             
   UNION结构:  CBBP_UNIT3_NCORR_LENGTH_UNION */
#define CBBP_UNIT3_NCORR_LENGTH_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2934)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   绝对噪声门限
   UNION结构:  CBBP_UNIT3_ABS_TH_UNION */
#define CBBP_UNIT3_ABS_TH_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x2938)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索单元使能信号
   UNION结构:  CBBP_UNIT3_EN_UNION */
#define CBBP_UNIT3_EN_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x293C)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   单元0本次小区搜索上报的噪声门限
   UNION结构:  CBBP_UNIT3_NOISE_ENERGY_UNION */
#define CBBP_UNIT3_NOISE_ENERGY_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x2940)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
             0：表示上报搜索窗与配置搜索窗完全一致
             1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip
             
   UNION结构:  CBBP_UNIT3_FRAME_SHIFT_UNION */
#define CBBP_UNIT3_FRAME_SHIFT_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x2944)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
             如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN0_FRAME_POS_UNION */
#define CBBP_UNIT3_PN0_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2948)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN1_FRAME_POS_UNION */
#define CBBP_UNIT3_PN1_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x294C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN2_FRAME_POS_UNION */
#define CBBP_UNIT3_PN2_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2950)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN3_FRAME_POS_UNION */
#define CBBP_UNIT3_PN3_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2954)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN4_FRAME_POS_UNION */
#define CBBP_UNIT3_PN4_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2958)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN5_FRAME_POS_UNION */
#define CBBP_UNIT3_PN5_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x295C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN6_FRAME_POS_UNION */
#define CBBP_UNIT3_PN6_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2960)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN7_FRAME_POS_UNION */
#define CBBP_UNIT3_PN7_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2964)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN8_FRAME_POS_UNION */
#define CBBP_UNIT3_PN8_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x2968)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN9_FRAME_POS_UNION */
#define CBBP_UNIT3_PN9_FRAME_POS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x296C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN10_FRAME_POS_UNION */
#define CBBP_UNIT3_PN10_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2970)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN11_FRAME_POS_UNION */
#define CBBP_UNIT3_PN11_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2974)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN12_FRAME_POS_UNION */
#define CBBP_UNIT3_PN12_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2978)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN13_FRAME_POS_UNION */
#define CBBP_UNIT3_PN13_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x297C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN14_FRAME_POS_UNION */
#define CBBP_UNIT3_PN14_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2980)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
             如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置
             
   UNION结构:  CBBP_UNIT3_PN15_FRAME_POS_UNION */
#define CBBP_UNIT3_PN15_FRAME_POS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2984)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      搜索模式选择
             0表示1x搜索
             1表示evdo搜索
   UNION结构:  CBBP_UNIT3_CS_1X_MODE_UNION */
#define CBBP_UNIT3_CS_1X_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x2988)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2]      搜索单元上报模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[1]      搜索单元排队模块时钟门控
             0表示时钟门控有效
             1表示时钟常开
 bit[0]      搜索单元控制部分时钟门控bypass
             0表示时钟门控有效
             1表示时钟常开
   UNION结构:  CBBP_UNIT3_SRCH_CK_BYPASS_UNION */
#define CBBP_UNIT3_SRCH_CK_BYPASS_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x298C)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    噪声门限滤波系数：
             0：1/2
             1:1/16
             2:1/32
             3:1/64
             4:1/128
             5:1/256
   UNION结构:  CBBP_UNIT3_NOISE_ALPHER_COEF_UNION */
#define CBBP_UNIT3_NOISE_ALPHER_COEF_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0x2990)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    从缓存数据中取数偏移，chip单位。
             使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定
   UNION结构:  CBBP_UNIT3_DATA_STORE_OFF_UNION */
#define CBBP_UNIT3_DATA_STORE_OFF_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x2994)



/***======================================================================***
                     (9/20) register_define_c_cs_mps_mem
 ***======================================================================***/
/* 寄存器说明：多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
 bit[31:16]  多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
             小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。
 bit[15:0]   多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
             小区测量（完成相干累加与非相干累加）时为非相干累加能量
             小区搜索时为小区能量
   UNION结构:  CBBP_UNIT0_RPT_UNION */
#define CBBP_UNIT0_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3000)
#define CBBP_UNIT0_RPT_MEMDEPTH  (128)

/* 寄存器说明：多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
 bit[31:16]  多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
             小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。
 bit[15:0]   多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
             小区测量（完成相干累加与非相干累加）时为非相干累加能量
             小区搜索时为小区能量
   UNION结构:  CBBP_UNIT1_RPT_UNION */
#define CBBP_UNIT1_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3200)
#define CBBP_UNIT1_RPT_MEMDEPTH  (128)

/* 寄存器说明：多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
 bit[31:16]  多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
             小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。
 bit[15:0]   多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
             小区测量（完成相干累加与非相干累加）时为非相干累加能量
             小区搜索时为小区能量
   UNION结构:  CBBP_UNIT2_RPT_UNION */
#define CBBP_UNIT2_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3400)
#define CBBP_UNIT2_RPT_MEMDEPTH  (128)

/* 寄存器说明：多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
 bit[31:16]  多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
             小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。
 bit[15:0]   多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
             小区测量（完成相干累加与非相干累加）时为非相干累加能量
             小区搜索时为小区能量
   UNION结构:  CBBP_UNIT3_RPT_UNION */
#define CBBP_UNIT3_RPT_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x3600)
#define CBBP_UNIT3_RPT_MEMDEPTH  (128)



/***======================================================================***
                     (10/20) register_define_c_dldec
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      译码建立使能，必须在所有译码参数配置完成后配置为1
   UNION结构:  CBBP_DLDEC_ESTB_IND_UNION */
#define CBBP_DLDEC_ESTB_IND_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x4008)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      译码启动信号，必须在所有译码参数和译码建立使能配置完成后配置
   UNION结构:  CBBP_DLDEC_DEC_START_UNION */
#define CBBP_DLDEC_DEC_START_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x400C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  信息比特长度
 bit[15:12]  超长码块分段译码非尾段或者寻呼、同步信道译码时该参数配置为0，其他信道该参数配置为8或6. 
 bit[11:9]   保留
 bit[8]      reserve_bit指示，1表示存在reserve比特
 bit[7:5]    保留
 bit[4]      CRC内部寄存器初始化状态；
             0：全0；1：全1。
             
 bit[3:0]    CRC
   UNION结构:  CBBP_PACKET_PARA_UNION */
#define CBBP_PACKET_PARA_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4010)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     纯Turbo译码模式下，harq合并使能。1，表示如果此时为旧数据，则进行harq合并。否则不进行合并。0，表示禁止合并
 bit[15:13]  保留
 bit[12]     C工作模式：0表示1X，1表示EVDO
 bit[11]     保留
 bit[10:8]   0: 1X下行卷积码块完整流程译码; 1: 1X下行TURBO码块完整流程译码;2: EVDO下行完整流程译码; 3: 1X 解交织解打孔解重复处理加速模式; 4: 纯VTB译码加速模式; 5: 纯TURBO译码加速模式。
 bit[7:5]    保留
 bit[4]      1X turbo编码模式，0表示默认模式，1表示补充模式。
 bit[3]      保留
 bit[2:0]    编码率，编码率为1/R时，配置为R。
   UNION结构:  CBBP_DEC_MODE_UNION */
#define CBBP_DEC_MODE_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x4014)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   扰码初始化状态。
   UNION结构:  CBBP_SCR_INIT_STATE_UNION */
#define CBBP_SCR_INIT_STATE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x4018)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:8]   block交织m参数。
 bit[7:0]    block交织j参数。
   UNION结构:  CBBP_BLOCK_INTL_PARA_UNION */
#define CBBP_BLOCK_INTL_PARA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x401C)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:4]    permuting交织m参数。
 bit[3]      保留
 bit[2:0]    permuting交织k参数。
   UNION结构:  CBBP_PERMUTING_INTL_PARA_UNION */
#define CBBP_PERMUTING_INTL_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4020)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:12]  matrix交织k参数
 bit[11:8]   matrix交织m参数
 bit[7]      保留
 bit[6:4]    matrix交织r参数
 bit[3:0]    matrix交织d参数
   UNION结构:  CBBP_MATRIX_INTL_PARA_UNION */
#define CBBP_MATRIX_INTL_PARA_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x4024)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  0：Matrix Interleave交织（EVDO 上下行使用）；1：下行Symbol Permuting交织（EVDO使用）；2：下行Bit-Reversal Order Interleave交织（1X使用）；3：下行Forward-Backwards Bit-Reversal Order Interleave交织（FOR_FCH_CCSH_INTERLEAVER_TYPE = 0,1X使用）；4：下行Forward-Backwards Bit-Reversal Order Interleave交织（FOR_FCH_CCSH_INTERLEAVER_TYPE = 1,1X使用）；5：上行TYPE1 Block Interleave交织（1X使用）（译码模块禁止配置）；6：上行TYPE2 Block Interleave交织（1X使用）（译码模块禁止配置）；7：上行Reverse Interleave（EVDO使用）（译码模块禁止配置）
 bit[15]     保留
 bit[14:0]   交织长度
   UNION结构:  CBBP_INTL_PAPA_UNION */
#define CBBP_INTL_PAPA_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x4028)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:0]   打孔图案，最低比特为第一个状态指示。例如打孔图案为11010时，表示第一个、第三个数据打孔，其余数据通过。
   UNION结构:  CBBP_PUNC_PATTERN_UNION */
#define CBBP_PUNC_PATTERN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x402C)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:8]    0:根据打孔图样产生打孔信息（包括ERAM模式下需要通过打孔图样产生打孔信息的场景）
             1：非ERAM模式下，根据公式计算打孔信息
             2：ERAM模式下，根据公式计算打孔信息
             
 bit[7:5]    保留
 bit[4:0]    打孔周期
   UNION结构:  CBBP_PUNC_PERIOD_UNION */
#define CBBP_PUNC_PERIOD_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4030)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   打孔前长度，即重复后长度
   UNION结构:  CBBP_DLDEC_LEN_BEF_PUNC_UNION */
#define CBBP_DLDEC_LEN_BEF_PUNC_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4034)

/* 寄存器说明：
 bit[31]     超常vtb译码模式,1表示超常vtb译码模式。
 bit[30:15]  保留
 bit[14:0]   超长维特比译码前LLR RAM的基地址。非超长vtb译码时配置为0,超长码块时根据实际LLR起始位置配置。例如超长码块第一次译码长度为768，如果训练序列长度为128，则第二次译码基地址配置为（（768-128）*code_rate/4）-1。
   UNION结构:  CBBP_DLDEC_LONG_VTB_PARA_UNION */
#define CBBP_DLDEC_LONG_VTB_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4038)

/* 寄存器说明：
 bit[31]     维特比译码初始化状态有效使能
 bit[30:8]   保留
 bit[7:0]    维特比初始化状态，根据前次上报的对应时隙状态配置。
   UNION结构:  CBBP_VTB_INIT_STATE_UNION */
#define CBBP_VTB_INIT_STATE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x403C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      增强vtb使能
 bit[3:0]    增强vtb回溯次数，支持1~8。例如配置为4时，表示除第一次译码外，最多还有3次译码。
   UNION结构:  CBBP_EVTB_EN_UNION */
#define CBBP_EVTB_EN_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0x4040)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      vtb回溯模式，0表示从0状态开始回溯，1表示从最大度量状态开始回溯。
   UNION结构:  CBBP_VTB_TB_MODE_UNION */
#define CBBP_VTB_TB_MODE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4044)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8:0]    vtb回溯状态上报时隙，在超长码块、寻呼信道、同步信道时需要根据训练长度进行配置。
   UNION结构:  CBBP_VTB_TB_RPT_SLOT_UNION */
#define CBBP_VTB_TB_RPT_SLOT_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x4048)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      译码超时保护使能
 bit[7:6]    保留
 bit[5:0]    译码模块超时周期配置值，0值不可配置，实际超时周期值为dldec_overtime_cfg *8192，，推荐配置值为16
   UNION结构:  CBBP_DLDEC_OVERTIME_CFG_UNION */
#define CBBP_DLDEC_OVERTIME_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x404C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     Turbo译码器CRC正确提前停止迭代使能0：禁止
             1：使能
             
 bit[15:13]  保留
 bit[12:8]   Turbo译码的最大处理次数，例如配置成16代表最多16次处理（无论是否收敛都停止迭代）
 bit[7:4]    保留
 bit[3:0]    Turbo译码的最小处理次数，例如配置成9代表最少需要9次处理才会停止迭代
   UNION结构:  CBBP_TURBO_ITER_NUM_C_UNION */
#define CBBP_TURBO_ITER_NUM_C_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x4050)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[23:22]  保留
 bit[21:16]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[15:14]  保留
 bit[13:8]   16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[7:6]    保留
 bit[5:0]    16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
   UNION结构:  CBBP_TURBO_SCALE_1_4_C_UNION */
#define CBBP_TURBO_SCALE_1_4_C_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4054)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[23:22]  保留
 bit[21:16]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[15:14]  保留
 bit[13:8]   16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[7:6]    保留
 bit[5:0]    16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
   UNION结构:  CBBP_TURBO_SCALE_5_8_C_UNION */
#define CBBP_TURBO_SCALE_5_8_C_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4058)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[23:22]  保留
 bit[21:16]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[15:14]  保留
 bit[13:8]   16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[7:6]    保留
 bit[5:0]    16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
   UNION结构:  CBBP_TURBO_SCALE_9_12_C_UNION */
#define CBBP_TURBO_SCALE_9_12_C_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x405C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[23:22]  保留
 bit[21:16]  16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[15:14]  保留
 bit[13:8]   16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
 bit[7:6]    保留
 bit[5:0]    16个scale因子，每个因子位宽6bit
             SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
             SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数
   UNION结构:  CBBP_TURBO_SCALE_13_16_C_UNION */
#define CBBP_TURBO_SCALE_13_16_C_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4060)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1，表示EVDO HARQ合并后四舍五入1位再饱和至6位；否则直接饱和至6位。
   UNION结构:  CBBP_HARQ_COMB_SHIFT_IND_UNION */
#define CBBP_HARQ_COMB_SHIFT_IND_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x4064)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    LLR下发数据类型指示。0，表示SDR处理器下发的解调后LLR信息；1，表示1X模式下完成解交织解打孔解重复后的LLR信息，也即VTB译码前LLR信息；2，表示EVDO模式下某个进程的HARQ后的LLR信息（此信息同时也是用于TURBO译码前的LLR信息）；
             
   UNION结构:  CBBP_DLDEC_WR_LLR_ORIG_UNION */
#define CBBP_DLDEC_WR_LLR_ORIG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4068)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    译码前LLR下发水线，也即下发LLR时的burst类型，不支持配置为1。典型配置为2/4/8/16。例如16，表示LLR下发为burst16类型,DMA数据位宽必须为64。
   UNION结构:  CBBP_DLDEC_WR_WATERLINE_UNION */
#define CBBP_DLDEC_WR_WATERLINE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x406C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    LLR上报数据类型指示。0，表示SDR处理器上报解调后LLR信息；1，表示EVDO模式下上报某个进程的HARQ后的LLR信息（此信息同时也是用于TURBO译码前的LLR信息）；2，表示1X模式下完成解交织解打孔解重复后的LLR信息上报；
   UNION结构:  CBBP_DLDEC_RD_LLR_ORIG_UNION */
#define CBBP_DLDEC_RD_LLR_ORIG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4070)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    LLR回读水线，也即回读时总线burst类型，不支持配置为1。典型配置为2/4/8/16。例如16，表示LLR回读为burst16类型，DMA数据位宽必须为64。
   UNION结构:  CBBP_DLDEC_RD_WATERLINE_UNION */
#define CBBP_DLDEC_RD_WATERLINE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x4074)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20]     DMA读请求状态上报
 bit[19:17]  保留
 bit[16]     DMA写请求状态上报
 bit[15:13]  保留
 bit[12]     回读LLR通道空状态上报
 bit[11:9]   保留
 bit[8]      回读LLR通道满状态上报
 bit[7:5]    保留
 bit[4]      下发LLR通道空状态上报
 bit[3:1]    保留
 bit[0]      下发LLR通道满状态上报
   UNION结构:  CBBP_LLR_TRANS_FLAG_UNION */
#define CBBP_LLR_TRANS_FLAG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x407C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      译码bler可维可测统计使能
   UNION结构:  CBBP_BLER_ENABLE_UNION */
#define CBBP_BLER_ENABLE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4080)

/* 寄存器说明：
   详      述：译码次数统计
   UNION结构 ：无 */
#define CBBP_DLDEC_DEC_TOTAL_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x4084)

/* 寄存器说明：
   详      述：译码CRC结果错误次数统计
   UNION结构 ：无 */
#define CBBP_DLDEC_DEC_CRC_NOK_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4088)

/* 寄存器说明：
   详      述：译码完成后上报中断个数统计
   UNION结构 ：无 */
#define CBBP_DLDEC_RPT_INT_NUM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x408C)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      vtb译码忙标志
 bit[7:5]    保留
 bit[4]      译码超时标志
 bit[3:0]    译码状态机上报
   UNION结构:  CBBP_DLDEC_STATE_UNION */
#define CBBP_DLDEC_STATE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0x4090)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      LLR下发四舍五入指示，为1表示8位LLR四舍五入1位再饱和至6位，为0表示直接截取低6位。如果是LLR首次下发，则需要配置为1；如果是回读前次译码的LLR值，因为已经是6位，故再次下发时不需要处理，此时配置为0。
   UNION结构:  CBBP_LLR_CLIP_IND_UNION */
#define CBBP_LLR_CLIP_IND_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x4094)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      重复模式选择，0表示FIX DATA RATE重复模式，1表示flexible重复模式。
   UNION结构:  CBBP_DLDEC_REPEAT_MODE_UNION */
#define CBBP_DLDEC_REPEAT_MODE_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x4098)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      LLR回读启动脉冲，只有在译码完成后或不在译码状态时才可配置。寻呼信道或同步信道在译码中断后配置。
   UNION结构:  CBBP_DLDEC_LLR_RD_START_UNION */
#define CBBP_DLDEC_LLR_RD_START_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x409C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      EVDO新码块指示，1表示该码块为新数据；0，表示旧数据
   UNION结构:  CBBP_DLDEC_NEW_BLK_IND_UNION */
#define CBBP_DLDEC_NEW_BLK_IND_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x40A0)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      reserve比特上报使能，1表示上报reserve比特；0表示不上报
 bit[3:1]    保留
 bit[0]      上报模式，1表示小端模式；0表示大端模式
   UNION结构:  CBBP_RPT_MODE_UNION */
#define CBBP_RPT_MODE_ADDR                            (SOC_BBP_CDMA_BASE_ADDR + 0x40A4)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   软件下发LLR个数，为实际LLR个数除以4，再向上取整。
   UNION结构:  CBBP_DLDEC_WR_LENGTH_UNION */
#define CBBP_DLDEC_WR_LENGTH_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x40AC)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   软件回读LLR个数，为实际LLR个数除以4，再向上取整。
   UNION结构:  CBBP_DLDEC_RD_LENGTH_UNION */
#define CBBP_DLDEC_RD_LENGTH_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0x40B0)

/* 寄存器说明：
 bit[31]     CRC校验结果上报
 bit[30:24]  保留
 bit[23:0]   CRC校验比特上报
   UNION结构:  CBBP_CRC_RPT_UNION */
#define CBBP_CRC_RPT_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0x40B4)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      测试模式时，软件不通过DMA，直接通过总线读取LLR软值。1表示有一个BURST的LLR可以读取。0，表示没有LLR可读取。
 bit[3:1]    保留
 bit[0]      测试模式时，软件不通过DMA，直接通过总线下发LLR软值。1表示有一个BURST的LLR可以下发。0，表示LLR不能下发。
   UNION结构:  CBBP_LLR_READY_UNION */
#define CBBP_LLR_READY_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x40B8)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      测试模式时，软件可不通过DMA，直接通过总线读取LLR软值。当读完一个burst数据时，产生该脉冲,把dldec_llr_rd_ready清0
 bit[3:1]    保留
 bit[0]      测试模式时，软件可不通过DMA，直接通过总线下发LLR软值。当下发完一个burst数据时，产生该清脉冲，把dldec_llr_wr_ready_clr清0
   UNION结构:  CBBP_LLR_READY_CLR_UNION */
#define CBBP_LLR_READY_CLR_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x40BC)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7:0]    vtb状态上报，用于下一次vtb译码状态度量初始化。在本次译码中断后下次译码启动前有效。
   UNION结构:  CBBP_C_VTB_ST_RPT_UNION */
#define CBBP_C_VTB_ST_RPT_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x40C0)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11:0]   盲检测或HARQ重传时turbo译码前数据的偏移地址。HARQ重传时，根据进程号计算，例如0进程时，该地址配置为0；进程n，则配置为641*n，支持最大4个进程。盲检测时，根据实际LLR数据长度计算。
   UNION结构:  CBBP_C2TUBO_BASE_ADDR_UNION */
#define CBBP_C2TUBO_BASE_ADDR_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40C4)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8:0]    时钟门控旁路使能
   UNION结构:  CBBP_DLDEC_CKG_BYPASS_UNION */
#define CBBP_DLDEC_CKG_BYPASS_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40C8)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BER统计使能
   UNION结构:  CBBP_DLDEC_BER_EN_UNION */
#define CBBP_DLDEC_BER_EN_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0x40CC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      当重复率为1时，ber统计需要计算打孔位置，此时，该信号配1。否则，配0。
   UNION结构:  CBBP_DLDEC_RFPUN_EN_UNION */
#define CBBP_DLDEC_RFPUN_EN_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x40D0)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   最后时刻幸存路径度量值与零状态度量值之差
   UNION结构:  CBBP_C_BLID_CM0_UNION */
#define CBBP_C_BLID_CM0_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40D4)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   最后时刻幸存路径度量值与次优路径度量值之差
   UNION结构:  CBBP_C_BLID_CM1_UNION */
#define CBBP_C_BLID_CM1_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40D8)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   C模盲译码最后时刻次优路径度量值上报
   UNION结构:  CBBP_C_BLID_CM2_UNION */
#define CBBP_C_BLID_CM2_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0x40DC)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   盲检测BER错误bit数统计结果
   UNION结构:  CBBP_DLDEC_BER_UNION */
#define CBBP_DLDEC_BER_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0x40E0)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   盲检测用于统计BER的总比特数
   UNION结构:  CBBP_DLDEC_TOTAL_BERBIT_UNION */
#define CBBP_DLDEC_TOTAL_BERBIT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0x40E4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      byte内大小端指示。0表示小端模式，即byte内最低位放低位数据。1表示大端模式，byte内最低位放最高位数据。
   UNION结构:  CBBP_BIT_ORDER_REVERSE_UNION */
#define CBBP_BIT_ORDER_REVERSE_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0x40E8)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      W模软化turbo译码器收敛判断方法的切换开关，默认打开
             0：比较连续两次的迭代处理结果，一致则认为收敛；
             1：比较连续三次的迭代处理结果，一致则认为收敛；
 bit[3:1]    保留
 bit[0]      W模软化Turbo译码器提前停止迭代使能0：禁止
             1：使能
             
   UNION结构:  CBBP_TURBO_ITER_NUM_W_SDR_UNION */
#define CBBP_TURBO_ITER_NUM_W_SDR_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0x40EC)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      1X或EVDO时盲检测指示，1表示当前码块需要进行盲检测译码
   UNION结构:  CBBP_BLIND_DETECT_IND_UNION */
#define CBBP_BLIND_DETECT_IND_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0x40F0)

/* 寄存器说明：
   详      述：超时码块个数上报
   UNION结构 ：无 */
#define CBBP_DLDEC_OVERTIME_CB_CNT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0x40F4)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      CPU直接下发LLR模式，此时不通过DMA下发数据，BBP DMA请求不拉高。
 bit[3:1]    保留
 bit[0]      CPU直接读取LLR模式，此时不通过DMA读取数据，BBP DMA请求不拉高。
   UNION结构:  CBBP_CPU_ACCESS_LLR_MODE_UNION */
#define CBBP_CPU_ACCESS_LLR_MODE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0x40F8)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    LLR数据下发模式指示:0，表示DMA burst下发模式；1，表示DMA FLASH模式；2，表示BBPMST模式。
             DMA FLASH模式和BBPMST模式不支持纯TURBO LLR数据下发。
   UNION结构:  CBBP_LLR_TRANS_MODE_UNION */
#define CBBP_LLR_TRANS_MODE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x40FC)



/***======================================================================***
                     (11/20) register_define_c_dldec_mem
 ***======================================================================***/
/* 寄存器说明：C上报数据RAM
   详      述：C模数据上报的数据RAM，深度为194，位宽为32bit。每个32位上报值占用地址空间一个地址，即上报值0地址为0x5000，上报值1地址为0x5004，……，依此类推，上报值193地址为0x5304。
   UNION结构 ：无 */
#define CBBP_C_RPT_DATA_RAM_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0x5000)
#define CBBP_C_RPT_DATA_RAM_MEMDEPTH  (194)

/* 寄存器说明：LLR下发FIFO
   详      述：C模LLR下发FIFO写数据，每次DMA搬运反复访问该地址写入一次请求数据。
   UNION结构 ：无 */
#define CBBP_C_WR_LLR_FIFO_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x5400)

/* 寄存器说明：LLR上报FIFO
   详      述：C模LLR回读FIFO读数据，每次DMA搬运反复访问该地址读出一次请求数据。
   UNION结构 ：无 */
#define CBBP_C_RD_LLR_FIFO_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x5408)



/***======================================================================***
                     (12/20) register_define_c_ulcode
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行编码模块使能，必须在所有上行编码参数配置完成后配置为1。
   UNION结构:  CBBP_ULCODE_EN_UNION */
#define CBBP_ULCODE_EN_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xB000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行编码启动信号，必须在所有上行编码参数和上行编码建立使能配置完成后配置
   UNION结构:  CBBP_ULCODE_START_UNION */
#define CBBP_ULCODE_START_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB004)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     编码数据下发小端比特逆序格式；1：表示小端比特逆序模式生效，0：表示小端比特逆序模式无效；默认值：0；
             编码数据下发小端比特逆序模式和小端模式不能同时生效；此配置对编码后数据上报格式无影响。
 bit[15:1]   保留
 bit[0]      编码数据下发格式和编码后数据上报格式；1：表示小端模式（默认模式），0：表示大端模式；默认值：1；
   UNION结构:  CBBP_ULCODE_BIT_MODE_UNION */
#define CBBP_ULCODE_BIT_MODE_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB008)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     Reverse bit的取值；取值0或1。
 bit[15:1]   保留
 bit[0]      1X模式下Reverse bit添加使能开关；EVDO模式下该参数配置为0。
   UNION结构:  CBBP_ULCODE_RESERVE_BIT_UNION */
#define CBBP_ULCODE_RESERVE_BIT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB00C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      通信模式类型指示；1：EVDO，0:1X；默认值：0。
   UNION结构:  CBBP_ULCODE_TRAFFIC_TYPE_UNION */
#define CBBP_ULCODE_TRAFFIC_TYPE_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB010)

/* 寄存器说明：
 bit[31:19]  保留
 bit[18:16]  上行编码器编码率；
             2：1/2；
             3：1/3；
             4：1/4；
             5：1/5；（卷积编码无1/5）。
 bit[15:1]   保留
 bit[0]      编码器类型指示；1：TURBO，0:VTB；
             默认值：0。
   UNION结构:  CBBP_ULCODE_CODER_PARA_UNION */
#define CBBP_ULCODE_CODER_PARA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xB014)

/* 寄存器说明：
 bit[31:14]  保留
 bit[13:0]   信息位长度；
             卷积编码下不含CRC、Reverse bit、TAIL bit 长度；TURBO编码下不含“00”，CRC、Reverse bit、TAIL bit 长度。
   UNION结构:  CBBP_ULCODE_LEN_PARA1_UNION */
#define CBBP_ULCODE_LEN_PARA1_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB018)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     CRC寄存器初始化值；1：全1，0：全0；
             默认值：0。
 bit[15:4]   保留
 bit[3:0]    CRC校验类型：
             0:CRC-0；
             1:CRC-16-1；
             2:CRC-12；
             3:CRC-10；
             4:CRC-8；
             5:CRC-6-1；
             6:CRC-6-2；
             7:CRC-24；
             8:CRC-16-2；
             默认值：0。
   UNION结构:  CBBP_ULCODE_CRC_PARA_UNION */
#define CBBP_ULCODE_CRC_PARA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB01C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   扰码产生器初相；
             SDR处理器根据EVDO协议定义的扰码器初相配置给上行编码模块。
             1X下固定配置为全0。
   UNION结构:  CBBP_ULCODE_SCR_INIT_UNION */
#define CBBP_ULCODE_SCR_INIT_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB020)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    交织器工作模式；
             0： Matrix Interleave交织；
             1： Symbol Permuting交织；
             2：下行TYPE1 Block Interleave交织；
             3：下行TYPE2 Block Interleave交织；
             4：下行TYPE3 Block Interleave交织；
             5：上行TYPE1 Block Interleave交织：
             6：上行TYPE2 Block Interleave交织；
             7：上行Reverse Interleave。
   UNION结构:  CBBP_ULCODE_INTL_MODE_UNION */
#define CBBP_ULCODE_INTL_MODE_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB024)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:24]  上行Matrix Interleave交织参数（EVDO使用）D参数（兼顾下行译码需求）。
 bit[23:19]  保留
 bit[18:16]  上行Matrix Interleave交织参数（EVDO使用）R参数。
 bit[15:12]  保留
 bit[11:8]   上行Matrix Interleave交织参数（EVDO使用）M参数。V0/V0`，V1/V1`硬件使用时自行加1处理。
 bit[7:3]    保留
 bit[2:0]    上行Matrix Interleave交织参数（EVDO使用）K参数。
   UNION结构:  CBBP_ULCODE_MATRIX_PARA_UNION */
#define CBBP_ULCODE_MATRIX_PARA_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB028)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    上行Reverse Interleave 交织参数（EVDO使用）m参数；
             数值表示实际参与逆序位宽参数。
   UNION结构:  CBBP_ULCODE_REVERSE_PARA_UNION */
#define CBBP_ULCODE_REVERSE_PARA_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB02C)

/* 寄存器说明：
 bit[31:24]  上行Block Interleave交织参数（1X使用）j参数。
 bit[23:20]  保留
 bit[19:16]  上行Block Interleave交织参数（1X使用）m参数。
 bit[15:2]   保留
 bit[1:0]    上行TYPE1 Block Interleave交织映射表选择；
             0：At 9600 or 14400 bps 
             1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
             1：At 4800 or 7200 bps 
             1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16 17 19 18 20 21 23 22 24 25 27 26 28 29 31 30 32
             2：At 2400 or 3600 bps 
             1 5 2 6 3 7 4 8 9 13 10 14 11 15 12 16 17 21 18 22 19 23 20 24 25 29 26 30 27 31 28 32
             3：At 1200 or 1800 bps 
             1 9 2 10 3 11 4 12 5 13 6 14 7 15 8 16 17 25 18 26 19 27 20 28 21 29 22 30 23 31 24 32
   UNION结构:  CBBP_ULCODE_BLOCK_PARA_UNION */
#define CBBP_ULCODE_BLOCK_PARA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xB030)

/* 寄存器说明：
 bit[31:16]  1X下使用，1X下即是协议定义的Symbol Repeation后长度；EVDO下由硬件自行计算得到。
 bit[15:0]   1X下行信道交织长度，EVDO下由硬件自行推算得到。
   UNION结构:  CBBP_ULCODE_LEN_PARA2_UNION */
#define CBBP_ULCODE_LEN_PARA2_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xB034)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24:0]   1X下使用，1X下无打孔则配置全1，有打孔按照实际的图样配置；EVDO下硬件固定使用全1图样。
   UNION结构:  CBBP_ULCODE_PUNC_PATTERN_UNION */
#define CBBP_ULCODE_PUNC_PATTERN_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB038)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:16]  Symbol Puncture打孔图样有效长度；
             5,9,12,18,24,25即是打孔图样一个循环周期内有效指示bit数。
 bit[15:2]   保留
 bit[1:0]    打孔模式；
             0： 根据打孔图样产生打孔信息（包括ERAM模式下需要通过打孔图样产生打孔信息的场景）；
             1：非ERAM模式下，根据公式计算打孔信息；
             2：ERAM模式下，根据公式计算打孔信息；
             
   UNION结构:  CBBP_ULCODE_PUNC_PATTERN_LEN_UNION */
#define CBBP_ULCODE_PUNC_PATTERN_LEN_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xB03C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0:0]    重复模式：
             0：Fix Data Rate模式下symbol repeat操作模式；
             1：Variable或Flexible Data Rate模式下 symbol repeat操作模式；
   UNION结构:  CBBP_ULCODE_REPEAT_MODE_UNION */
#define CBBP_ULCODE_REPEAT_MODE_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xB040)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:0]    编码模块超时周期配置值，0值不可配置，实际超时周期值为ulcod_overtime_cfg*8192，推荐配置值为15（静态）
   UNION结构:  CBBP_ULCODE_OVERTIME_CFG_UNION */
#define CBBP_ULCODE_OVERTIME_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB044)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行编码统计计数使能。
   UNION结构:  CBBP_ULCODE_TIMES_EN_UNION */
#define CBBP_ULCODE_TIMES_EN_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xB048)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      忙或空闲状态上报；
             0：空 1：忙。
   UNION结构:  CBBP_ULCODE_CODER_STATUS_UNION */
#define CBBP_ULCODE_CODER_STATUS_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xB04C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      表示发生编码过程超时。
   UNION结构:  CBBP_ULCODE_OVERTIME_FLAG_UNION */
#define CBBP_ULCODE_OVERTIME_FLAG_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xB050)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    上行编码状态上报。
   UNION结构:  CBBP_ULCODE_STATE_UNION */
#define CBBP_ULCODE_STATE_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB054)

/* 寄存器说明：
 bit[31:16]  编码启动次数上报；复位清零。
 bit[15:0]   编码中断次数上报；复位清零。
   UNION结构:  CBBP_ULCODE_TIMES_UNION */
#define CBBP_ULCODE_TIMES_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xB058)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    上行编码控制部分时钟门控bypass
             [0]:CRC模块门控bypass
             [1]:COD模块门控bypass
             [2]:RM模块门控bypass
             [3]:INTL模块门控bypass
             0：表示时钟门控有效。
             1：表示时钟常开。
   UNION结构:  CBBP_ULCODE_CKG_UNION */
#define CBBP_ULCODE_CKG_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xB05C)



/***======================================================================***
                     (13/20) register_define_c_ulcode_mem
 ***======================================================================***/
/* 寄存器说明：上行编码上报RAM
   详      述：上行编码上报RAM通过CPU接口上报；上行编码上报RAM深度为1281，位宽32bit。每个上报字占用地址空间一个地址。首地址为0x8000，依此类推，尾地址为0x9400。
            0x8000的bit[15:0]上报编码后数据长度，bit[31:16]无意义。
            0x8004~0x9400为上报编码后数据。
   UNION结构 ：无 */
#define CBBP_ULCOD_RPT_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0x8000)
#define CBBP_ULCOD_RPT_RAM_MEMDEPTH  (1281)

/* 寄存器说明：上行编码下发RAM
   详      述：上行编码带编码数据通过CPU接口下发给编码下发RAM；上行编码下发RAM深度为384，位宽32bit。每个字占用地址空间一个地址。首地址为0xA000，依此类推，尾地址为0xA5FC。
   UNION结构 ：无 */
#define CBBP_ULCOD_CODEC_RAM_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xA000)
#define CBBP_ULCOD_CODEC_RAM_MEMDEPTH  (384)



/***======================================================================***
                     (14/20) register_define_c_fe_sdr_if
 ***======================================================================***/
/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     下行DMA搬运模式。0，一次burst请求搬运32x32bit；1，一次burst请求搬运16x32bit。
 bit[27:25]  保留
 bit[24]     下行搬运模式。0，DMA方式；1，BBPMaster方式。
 bit[23:21]  保留
 bit[20]     下行SDR IF模块搬运停止模式。0，配置停止脉冲后立即停止搬运；1，达到cpu_dlfe_sdr_data_length定义的搬运数据量后自动停止搬运。
 bit[19:17]  保留
 bit[16]     下行SDR IF模块搬运启动模式。0，配置启动脉冲后立即启动搬运；1，配置启动脉冲后到cpu_dlfe_sdr_start_time定义的时刻启动搬运。
             该参数仅在G模软化时有效。
 bit[15:13]  保留
 bit[12]     下行SDR IF模块接收分集模式。0，非接收分集；1，接收分集。
 bit[11:10]  保留
 bit[9:8]    下行SDR IF模块工作模式。0和1表示非C模；2表示1X；3表示EVDO。
             该参数仅在C模时有效。
 bit[7:5]    保留
 bit[4]      下行SDR IF模块搬运启停模式。0，主分集都用主集启停信号；1，主分集用各自启停信号。
 bit[3:1]    保留
 bit[0]      下行SDR IF模块使能，高电平有效。
   UNION结构:  CBBP_DLFE_SDR_EN_UNION */
#define CBBP_DLFE_SDR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xE000)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      下行搬数时钟门控bypass信号，高电平有效，表示时钟常开。
   UNION结构:  CBBP_DLFE_SDR_CKG_BYS_UNION */
#define CBBP_DLFE_SDR_CKG_BYS_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xE004)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28]     下行分集BBPMaster搬运复位脉冲。
 bit[27:25]  保留
 bit[24]     下行分集搬运强制停止脉冲。在检测到下行分集搬运出错后配置。
 bit[23:21]  保留
 bit[20]     下行分集搬运停止脉冲。
 bit[19:17]  保留
 bit[16]     下行分集搬运启动脉冲。
 bit[15:13]  保留
 bit[12]     下行主集BBPMaster搬运复位脉冲。
 bit[11:9]   保留
 bit[8]      下行主集搬运强制停止脉冲。在检测到下行主集搬运出错后配置。
 bit[7:5]    保留
 bit[4]      下行主集搬运停止脉冲。
 bit[3:1]    保留
 bit[0]      下行主集搬运启动脉冲。
   UNION结构:  CBBP_DLFE_SDR_START_STOP_UNION */
#define CBBP_DLFE_SDR_START_STOP_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE008)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  下行时隙头相对sys_cnt时隙边界的提前量，单位chip。
             该参数仅在C模时有效。
 bit[15:12]  保留
 bit[11:0]   下行Buffer深度，单位32word，用于计算Buffer首地址的时间戳。
             C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
   UNION结构:  CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION */
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE00C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  下行搬运数据量，单位32word。
             该参数仅在cpu_dlfe_sdr_stop_mode为1时有效。
 bit[15:13]  保留
 bit[12:0]   G模软化时，gtc_timebase上的搬运启动时刻，单位Qb，范围0~4999。
   UNION结构:  CBBP_DLFE_SDR_TIME_CTRL_UNION */
#define CBBP_DLFE_SDR_TIME_CTRL_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xE010)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   下行Buffer深度，单位word。
             C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
             建议在G模软化时使用。
   UNION结构:  CBBP_DLFE_SDR_WORD_DEPTH_UNION */
#define CBBP_DLFE_SDR_WORD_DEPTH_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE014)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    下行天线1当前搬运word数。
   UNION结构:  CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE040)

/* 寄存器说明：
 bit[31:12]  下行天线1当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。
 bit[11:0]   下行天线1当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。
   UNION结构:  CBBP_DLFE_SDR_AT1_RD_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE044)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5:0]    下行天线2当前搬运word数。
   UNION结构:  CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE048)

/* 寄存器说明：
 bit[31:12]  下行天线2当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。
 bit[11:0]   下行天线2当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。
   UNION结构:  CBBP_DLFE_SDR_AT2_RD_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xE04C)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线1启动搬运后第一个数据对应时间戳。
             C模时间戳为c_base_cnt，单位chip。
             bit[14:0]：计数范围0~32767chip，时间长度80/3ms（32768chip）；
             bit[16:15]：计数范围0~2，时间长度80ms；
             bit[21:17]：计数范围0~24，时间长度2s；
             bit[27:22]：固定为0。
             G模软化时间戳为gtc_tdma_qb上的帧号和gtc_timebase上的Qb号。
             bit[12:0]：gtc_timebase上的帧内Qb计数，计数范围0~4999Qb；
             bit[23:13]：gtc_tdma_qb上的fn_low帧计数，计数范围0~1325帧。
             bit[27:24]：固定为0。
             U模软化时间戳为base_cnt和cfn。
             bit[7:0]：symbol内chip计数，计数范围0~255chip；
             bit[11:8]：slot内symbol计数，计数范围0~9symbol；
             bit[15:12]：帧内slot计数，计数范围0~14slot；
             bit[27:16]：cfn。
   UNION结构:  CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE050)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线2启动搬运后第一个数据对应base_cnt时间戳，单位chip。
             时间戳含义同上。
   UNION结构:  CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xE054)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线1启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
             时间戳含义同上。
             C模1x时隙头即PCG头；C模EV-DO时隙头即实际时隙头；G模软化时隙头即gtc_tdma_qb上的burst头；U模软化时隙头即实际时隙头。
   UNION结构:  CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0xE058)

/* 寄存器说明：
 bit[31:28]  保留
 bit[27:0]   下行天线2启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
             时间戳含义同上。
             时隙头含义同上。
   UNION结构:  CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_CDMA_BASE_ADDR + 0xE05C)

/* 寄存器说明：
   详      述：下行天线1接收数据。
            C模和U模软化时采集DAGC后数据，一个word对应一个chip，格式如下。
            bit[7:0]：chip内样点0 I路；
            bit[15:8]：chip内样点0 Q路；
            bit[23:16]：chip内样点1 I路；
            bit[31:24]：chip内样点1 Q路。
            G模软化时采集AD后数据，一个word对应一个Qb，格式如下。
            bit[15:0]：Qb I路；
            bit[31:16]：Qb Q路。
   UNION结构 ：无 */
#define CBBP_DLFE_SDR_AT1_DATA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xE060)

/* 寄存器说明：
   详      述：下行天线2接收数据。
            C模和U模软化时采集DAGC后数据，一个word对应一个chip，格式如下。
            bit[7:0]：chip内样点0 I路；
            bit[15:8]：chip内样点0 Q路；
            bit[23:16]：chip内样点1 I路；
            bit[31:24]：chip内样点1 Q路。
            G模软化时采集AD后数据，一个word对应一个Qb，格式如下。
            bit[15:0]：Qb I路；
            bit[31:16]：Qb Q路。
   UNION结构 ：无 */
#define CBBP_DLFE_SDR_AT2_DATA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xE068)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      下行天线1搬运出错指示。
 bit[3:1]    保留
 bit[0]      下行天线1搬运状态。
   UNION结构:  CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE070)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      下行天线2搬运出错指示。
 bit[3:1]    保留
 bit[0]      下行天线2搬运状态。
   UNION结构:  CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE074)

/* 寄存器说明：
 bit[31:16]  下行天线1当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
 bit[15:0]   下行天线1当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
   UNION结构:  CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION */
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE078)

/* 寄存器说明：
 bit[31:16]  下行天线2当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
 bit[15:0]   下行天线2当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
             建议在G模软化时使用。
   UNION结构:  CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION */
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_ADDR            (SOC_BBP_CDMA_BASE_ADDR + 0xE07C)

/* 寄存器说明：
 bit[31:25]  保留
 bit[24]     上行搬运模式。0，DMA方式；1，BBPMaster方式。
 bit[23:17]  保留
 bit[16]     G模软化上行发送定时选择。0，基于gtc_timebase；1，基于gtc_tdma_qb。
 bit[15:13]  保留
 bit[12]     G模软化上行发送模式。0，正常模式；1，连续模式。
 bit[11:10]  保留
 bit[9:8]    上行SDR IF模块工作模式。0和1表示非C模；2表示1X；3表示EVDO。
             该参数仅在C模时有效。
 bit[7:5]    保留
 bit[4]      上行da_on，高电平有效。BBP经sys_cnt时隙边界同步再使用。
             该参数仅在C模时有效。
 bit[3:1]    保留
 bit[0]      上行SDR IF模块使能，高电平有效。
   UNION结构:  CBBP_ULFE_SDR_EN_UNION */
#define CBBP_ULFE_SDR_EN_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xE100)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      上行搬数时钟门控bypass信号，高电平有效，表示时钟常开。
   UNION结构:  CBBP_ULFE_SDR_CKG_UNION */
#define CBBP_ULFE_SDR_CKG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xE104)

/* 寄存器说明：
 bit[31:6]   保留
 bit[5]      BBPMaster搬运复位脉冲。
 bit[4]      BBPMaster搬运方式下，C模数据搬运启动脉冲。
 bit[3:2]    保留
 bit[1]      上行取数发送停止脉冲。
             该参数仅在G模软化时有效。
 bit[0]      上行取数发送启动脉冲。
             该参数仅在G模软化时有效。
   UNION结构:  CBBP_ULFE_SDR_START_UNION */
#define CBBP_ULFE_SDR_START_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xE108)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  C模时，表示上行ACH时隙头相对sys_cnt时隙边界延迟量，单位chip。
             G模软化时，bit[22:16]表示启动数据发送的Qb内clk时刻；bit[26:23]无意义。
 bit[15:13]  保留
 bit[12:0]   C模时，表示上行时隙头相对sys_cnt时隙边界提前量，单位1/4chip。
             G模软化时，表示gtc_tdma_qb上的启动数据发送时刻，单位Qb，范围0~4999。
   UNION结构:  CBBP_ULFE_SDR_OFFSET_UNION */
#define CBBP_ULFE_SDR_OFFSET_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xE10C)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  C模时，表示上行相位补偿提前时隙头生效位置，单位1/4chip。
             G模软化时，bit[27:16]表示发送数据最后一个burst结束样点，取值范围0~2499；bit[28]无意义。
 bit[15:13]  保留
 bit[12:0]   C模时，表示上行dbb控制字提前时隙头生效位置，单位1/4chip。
             G模软化时，bit[11:0]表示发送数据第一个burst起始样点，取值范围0~2499；bit[12]无意义。
   UNION结构:  CBBP_ULFE_SDR_ACTIVE_TIME_UNION */
#define CBBP_ULFE_SDR_ACTIVE_TIME_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xE110)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    G模软化时，发送数据包含的burst个数，取值范围0~5。配置值加1表示实际burst个数。
   UNION结构:  CBBP_ULFE_SDR_G_CFG_UNION */
#define CBBP_ULFE_SDR_G_CFG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xE114)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      上行BBPMaster搬运完成指示。
 bit[7:5]    保留
 bit[4]      上行BBPMaster搬运出错指示。
 bit[3:1]    保留
 bit[0]      上行搬运状态。
   UNION结构:  CBBP_ULFE_SDR_DUMP_EN_RPT_UNION */
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ADDR                (SOC_BBP_CDMA_BASE_ADDR + 0xE140)



/***======================================================================***
                     (15/20) register_define_c_fe_sdr_if_mem
 ***======================================================================***/
/* 寄存器说明：
 bit[31:28]  保留
 bit[27:16]  C模时，表示上行前端数据Q路，12比特有符号数，软件每1/4 PCG或slot写一遍。
             G模软化时，表示上行发送数据Q路，12比特有符号数，软件每1/5 burst写一遍。
 bit[15:12]  保留
 bit[11:0]   C模时，表示上行前端数据I路，12比特有符号数，软件每1/4 PCG或slot写一遍。
             G模软化时，表示上行发送数据I路，12比特有符号数，软件每1/5 burst写一遍。
   UNION结构:  CBBP_ULFE_SDR_RAM_UNION */
#define CBBP_ULFE_SDR_RAM_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xE800)
#define CBBP_ULFE_SDR_RAM_MEMDEPTH  (512)



/***======================================================================***
                     (16/20) register_define_c_fe_ctrl
 ***======================================================================***/
/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  c_fe_ctrl模块工作模式：0和1表示非C模，2表示1X，3表示EVDO。
 bit[15]     保留
 bit[14]     C主模时，c2com_intrasys_valid_delay上升沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。
 bit[13]     C主模时，c2com_intrasys_valid_delay下降沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。
 bit[12]     C从模时，com2c_master_intrasys_valid 下降沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。
 bit[11:9]   保留
 bit[8]      软件配置intersys_ingap_pre_ind信号值。
 bit[7:5]    保留
 bit[4]      软件配置异频异系统测量使能信号值。
 bit[3:2]    保留
 bit[1:0]    C测量类型：0异频，1异系统，2从模。
   UNION结构:  CBBP_CTU_CFG_UNION */
#define CBBP_CTU_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF000)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置异频异系统测量使能信号在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_MEAS_ACT_TIME_UNION */
#define CBBP_CTU_MEAS_ACT_TIME_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF004)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置intersys_ingap_pre_ind信号在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_INGAP_ACT_TIME_UNION */
#define CBBP_CTU_INGAP_ACT_TIME_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF008)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置intrasys_valid信号置0在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_INTRA_CLR_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_CLR_ACT_TIME_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF00C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置intrasys_valid信号置1在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_INTRA_SET_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_SET_ACT_TIME_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF010)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置intrasys_valid_delay信号置0在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xF014)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置intrasys_valid_delay信号置1在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION */
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_ADDR          (SOC_BBP_CDMA_BASE_ADDR + 0xF018)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置ssi_mipi_stop信号置0在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_STOP_CLR_ACT_TIME_UNION */
#define CBBP_CTU_STOP_CLR_ACT_TIME_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xF01C)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16:0]   软件配置ssi_mipi_stop信号置1在sys_cnt生效时刻，单位chip。
   UNION结构:  CBBP_CTU_STOP_SET_ACT_TIME_UNION */
#define CBBP_CTU_STOP_SET_ACT_TIME_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xF020)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   rfic_ssi每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对RFIC SSI RAM翻页，并开始根据RAM控制字发送数据。注意：在G SDR模式，该参数不能与active_time相同
   UNION结构:  CBBP_RFIC_START_TIME_UNION */
#define CBBP_RFIC_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF040)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。
 bit[11]     翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。
 bit[10:4]   每个乒乓RAM中data_buffer起始地址。
 bit[3]      保留
 bit[2]      0:每个ctrl_buff对应最多7个数据。1:每个ctrl_buff对应最多3个数据。
 bit[1]      0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零
 bit[0]      0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。此模式必须配置cpu_rfic_ssi_buffer_clr_mode为1
             1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。
             
   UNION结构:  CBBP_RFIC_SSI_STA_CFG_UNION */
#define CBBP_RFIC_SSI_STA_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF044)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7]      停止发送模式，0表示立即停止不发送新数据，1表示当前ctrl_buff对应数据发送完成后再停止。
 bit[6]      1表示停止发送当前RAM中数据并清除当前RAM所有数据。
 bit[5]      保留
 bit[4]      1表示暂停发送当前RAM中数据。当此信号生效时，软件如需要改写RAM中的数据，不需要手动翻页，直接在当前页操作。Hold结束后，BBP会从头开始重新执行CtrlBuffer的指令
 bit[3:1]    保留
 bit[0]      模块工作使能，高电平有效。
   UNION结构:  CBBP_RFIC_SSI_DYN_CFG_UNION */
#define CBBP_RFIC_SSI_DYN_CFG_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF048)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     C_FE_RFIC 强制发送脉冲。cpu_rfic_ssi_force_en=1时才有效。
 bit[15:1]   保留
 bit[0]      写1产生脉冲信号，手动启动指令页执行，cpu_rfic_ssi_auto_run=0时才有效。
   UNION结构:  CBBP_RFIC_SSI_START_UNION */
#define CBBP_RFIC_SSI_START_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF04C)

/* 寄存器说明：
 bit[31]     C_FE_RFIC 强制发送使能。关闭cpu_rfic_ssi_pro_en时使用，或者工作状态先配cpu_rfic_ssi_hold_page暂停后使用。
 bit[30:25]  保留
 bit[24:0]   C_FE_RFIC 强制发送数据，cpu_rfic_ssi_force_en=1时才有效。
   UNION结构:  CBBP_RFIC_SSI_FORCE_UNION */
#define CBBP_RFIC_SSI_FORCE_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF050)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:12]  异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
             [12]work_mode_sel被异常改写
             [13]buffer_clr_mode被异常改写
             [14]data_buffer_start_addr被异常改写
 bit[11:5]   当前执行到的rfic_ctrl buff的地址
 bit[4]      BBP当前使用乒乓RAM状态上报。
 bit[3]      保留
 bit[2:0]    rfic_ssi RAM访问状态上报。
   UNION结构:  CBBP_RFIC_STATE_RPT_UNION */
#define CBBP_RFIC_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF054)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   mipi每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对MIPI RAM翻页，并开始根据RAM控制字发送数据。
             
   UNION结构:  CBBP_MIPI_START_TIME_UNION */
#define CBBP_MIPI_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF070)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12]     自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。
 bit[11]     翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。
 bit[10:4]   每个乒乓RAM中data_buffer起始地址。
 bit[3]      保留
 bit[2]      0:每个ctrl_buff对应最多3个数据。1:每个ctrl_buff对应最多1个数据。
 bit[1]      0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零
 bit[0]      0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。
             1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。
             
   UNION结构:  CBBP_MIPI_STA_CFG_UNION */
#define CBBP_MIPI_STA_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF074)

/* 寄存器说明：
 bit[31:8]   保留
 bit[7]      停止发送模式，0表示立即停止不发送新数据，1表示当前ctrl_buff对应数据发送完成后再停止。
 bit[6]      1表示停止发送当前RAM中数据并清除当前RAM所有数据。
 bit[5]      保留
 bit[4]      1表示暂停发送当前RAM中数据。用法见cpu_rfic_ssi_hold_page
 bit[3:1]    保留
 bit[0]      模块工作使能，高电平有效。
   UNION结构:  CBBP_MIPI_DYN_CFG_UNION */
#define CBBP_MIPI_DYN_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF078)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      C_FE_MIPI 强制发送脉冲。cpu_mipi_force_en=1时才有效。
 bit[3:1]    保留
 bit[0]      写1产生脉冲信号，手动启动指令页执行，cpu_mipi_auto_run=0时才有效。
   UNION结构:  CBBP_MIPI_START_UNION */
#define CBBP_MIPI_START_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF07C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      C_FE_MIPI 强制发送使能。关闭cpu_mipi_pro_en时使用，或者工作状态先配cpu_mipi_hold_page暂停后使用。
             强配时，mipi_force_data必须配置64bit（高低都配置），如果数据不足32bit，则配置在高32bit，且低32bit配置为0。
   UNION结构:  CBBP_MIPI_FORCE_EN_UNION */
#define CBBP_MIPI_FORCE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF080)

/* 寄存器说明：
   详      述：C_FE_MIPI 强制发送数据(高半部分)，cpu_mipi_force_en=1时才有效。
   UNION结构 ：无 */
#define CBBP_MIPI_FORCE_DATA_H_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF084)

/* 寄存器说明：
   详      述：C_FE_MIPI 强制发送数据(低半部分)，cpu_mipi_force_en=1时才有效。
   UNION结构 ：无 */
#define CBBP_MIPI_FORCE_DATA_L_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF088)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:12]  异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
             [12]work_mode_sel被异常改写
             [13]buffer_clr_mode被异常改写
             [14]data_buffer_start_addr被异常改写
 bit[11:5]   当前执行到的rfic_ctrl buff的地址
 bit[4]      BBP当前使用RAM的乒乓状态上报。
 bit[3]      保留
 bit[2:0]    mipi RAM控制的状态机上报。
   UNION结构:  CBBP_MIPI_STATE_RPT_UNION */
#define CBBP_MIPI_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF08C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   GPIO每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对GPIO RAM翻页，并开始根据RAM控制字发送数据。
             
   UNION结构:  CBBP_GPIO_START_TIME_UNION */
#define CBBP_GPIO_START_TIME_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF0A0)

/* 寄存器说明：
 bit[31:12]  保留
 bit[11]     自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。
 bit[10]     翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。
 bit[9:4]    每个乒乓RAM中data_buffer起始地址。
 bit[3:2]    保留
 bit[1]      0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零
 bit[0]      0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。
             1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。
             
   UNION结构:  CBBP_GPIO_STA_CFG_UNION */
#define CBBP_GPIO_STA_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF0A4)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      1表示停止发送当前RAM中数据并清除当前RAM所有数据。
 bit[7:5]    保留
 bit[4]      1表示暂停发送当前RAM中数据。
 bit[3:1]    保留
 bit[0]      模块工作使能，高电平有效。
   UNION结构:  CBBP_GPIO_DYN_CFG_UNION */
#define CBBP_GPIO_DYN_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF0A8)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      C_FE_GPIO 强制发送脉冲，cpu_gpio_force_en=1时才有效。
 bit[3:1]    保留
 bit[0]      写1产生脉冲信号，手动启动指令页执行，cpu_gpio_auto_run=0时才有效。
   UNION结构:  CBBP_GPIO_START_UNION */
#define CBBP_GPIO_START_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF0AC)

/* 寄存器说明：
 bit[31]     C_FE_GPIO 强制发送使能，关闭cpu_gpio_pro_en时使用，或者工作状态先配cpu_gpio_hold_page暂停后使用。
 bit[30:0]   保留
   UNION结构:  CBBP_GPIO_FORCE_EN_UNION */
#define CBBP_GPIO_FORCE_EN_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0B0)

/* 寄存器说明：
   详      述：C_FE_GPIO 强制发送数据，cpu_gpio_force_en=1时才有效。[31]=0表示ant_pa_sel数据，[31]=1表示abb_en等其他线控值。当[31]=1时，bit0~bit9依次表示：
            bit[0]:c_abb0_rxa_en,ABB A通道接收使能
            bit[1]:c_abb0_rxb_en,ABB B通道接收使能
            bit[2]:c_abb0_rxa_blk_en,ABB A通道Block计算使能
            bit[3]:c_abb0_rxb_blk_en,ABB B通道Block计算使能
            bit[4]:c_abb0_tx_en,ABB 上行通道发送使能
            bit[5]:c2com_rf0_tcvr_on,RF 总工作使能
            bit[6]:c2com_rf0_tx_en,RF TX工作使能
            bit[7]:保留
            bit[9:8]:ABB通道选择，
            00：表示A通道为主集，B通道为分集；11：表示A通道为分集，B通道为主集；
            bit[30:10]:保留
            bit[31]:为0时，表示公共线控ant_pa_sel数据
            为1时表示专用线控，每个bit的含义如上述bit[9:0]描述
   UNION结构 ：无 */
#define CBBP_GPIO_FORCE_DATA_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF0B4)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:12]  异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
             [12]work_mode_sel被异常改写
             [13]buffer_clr_mode被异常改写
             [14]data_buffer_start_addr被异常改写
 bit[11]     保留
 bit[10:5]   当前执行到的gpio_ctrl buff的地址
 bit[4]      BBP当前使用乒乓RAM状态上报。
 bit[3]      保留
 bit[2:0]    gpio RAM访问状态上报。
   UNION结构:  CBBP_GPIO_STATE_RPT_UNION */
#define CBBP_GPIO_STATE_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0B8)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   公共线控(antpa)控制上报。
   UNION结构:  CBBP_GPIO_ANTPA_RPT_UNION */
#define CBBP_GPIO_ANTPA_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0BC)

/* 寄存器说明：
 bit[31]     保留
 bit[30:0]   专用线控（gpio线控）上报。bit[0]:c_abb0_rxa_en,ABB A通道接收使能
             bit[1]:c_abb0_rxb_en,ABB B通道接收使能
             bit[2]:c_abb0_rxa_blk_en,ABB A通道Block计算使能
             bit[3]:c_abb0_rxb_blk_en,ABB B通道Block计算使能
             bit[4]:c_abb0_tx_en,ABB 上行通道发送使能
             bit[5]:c2com_rf0_tcvr_on,RF 总工作使能
             bit[6]:c2com_rf0_tx_en,RF TX工作使能
             bit[30:7]:保留
   UNION结构:  CBBP_GPIO_LINE_CTRL_RPT_UNION */
#define CBBP_GPIO_LINE_CTRL_RPT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF0C0)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   HKADC SSI每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对HKADC SSI RAM重新发送，并开始根据RAM控制字发送数据。
             注意：在G SDR模式，该参数不能与active_time相同
   UNION结构:  CBBP_HKADC_START_TIME_UNION */
#define CBBP_HKADC_START_TIME_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF0D0)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19]     自动运行使能，0：软件配置脉冲手动运行，1：在软件配置时刻自动运行。
 bit[18:16]  hkadc ssi延时调整，单位ssi clock周期。
 bit[15:11]  保留
 bit[10:4]   每个乒乓RAM中data_buffer起始地址。
 bit[3:0]    保留
   UNION结构:  CBBP_HKADC_STA_CFG_UNION */
#define CBBP_HKADC_STA_CFG_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0D4)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      1表示停止发送当前RAM中数据并清除当前RAM所有数据。
 bit[7:5]    保留
 bit[4]      1表示暂停发送当前RAM中数据。用法同cpu_rfic_ssi_hold_page
 bit[3:1]    保留
 bit[0]      模块工作使能，高电平有效。
   UNION结构:  CBBP_HKADC_DYN_CFG_UNION */
#define CBBP_HKADC_DYN_CFG_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0D8)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4:1]    保留
 bit[0]      写1产生脉冲信号，手动启动指令页执行，cpu_hkadc_ssi_auto_run=0时才有效。
   UNION结构:  CBBP_HKADC_START_UNION */
#define CBBP_HKADC_START_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xF0DC)

/* 寄存器说明：
 bit[31]     C_HKADC_SSI 强制发送使能，需同时配置cpu_hkadc_ssi_pro_en=1，或者工作状态先配cpu_hkadc_ssi_hold_page暂停后使用。
 bit[30]     C_HKADC_SSI 强制发送脉冲
 bit[29:17]  保留
 bit[16:0]   C_HKADC_SSI 强制发送数据，cpu_hkadc_force_en=1时才有效。
   UNION结构:  CBBP_HKADC_FORCE_UNION */
#define CBBP_HKADC_FORCE_ADDR                         (SOC_BBP_CDMA_BASE_ADDR + 0xF0E0)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8:0]    读延迟时间，单位 19Mclock个数
   UNION结构:  CBBP_HKADC_RD_WAIT_UNION */
#define CBBP_HKADC_RD_WAIT_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xF0E4)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      PD结果有效标志清零脉冲
 bit[3:1]    保留
 bit[0]      PD超时标志清零脉冲
   UNION结构:  CBBP_HKADC_CLR_UNION */
#define CBBP_HKADC_CLR_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF0E8)

/* 寄存器说明：
 bit[31:23]  保留
 bit[22:20]  异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
             [20]work_mode_sel被异常改写
             [21]buffer_clr_mode被异常改写
             [22]data_buffer_start_addr被异常改写
 bit[19:18]  保留
 bit[17:11]  当前执行到的hkadc_ctrl buff的地址
 bit[10:8]   SSI RAM访问状态上报。
 bit[7:5]    保留
 bit[4]      PD结果有效标志，高电平有效。
 bit[3:1]    保留
 bit[0]      PD超时标志，高电平有效。
   UNION结构:  CBBP_HKADC_FLAG_RPT_UNION */
#define CBBP_HKADC_FLAG_RPT_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF0EC)

/* 寄存器说明：
 bit[31:16]  本时隙第1次PD回读结果,[13:8]表示读地址，[7:0]表示读数据，无符号数，下同。
 bit[15:0]   本时隙第0次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT0_1_UNION */
#define CBBP_HKADC_RESULT0_1_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF100)

/* 寄存器说明：
 bit[31:16]  本时隙第3次PD回读结果。
 bit[15:0]   本时隙第2次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT2_3_UNION */
#define CBBP_HKADC_RESULT2_3_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF104)

/* 寄存器说明：
 bit[31:16]  本时隙第5次PD回读结果。
 bit[15:0]   本时隙第4次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT4_5_UNION */
#define CBBP_HKADC_RESULT4_5_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF108)

/* 寄存器说明：
 bit[31:16]  本时隙第7次PD回读结果。
 bit[15:0]   本时隙第6次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT6_7_UNION */
#define CBBP_HKADC_RESULT6_7_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF10C)

/* 寄存器说明：
 bit[31:16]  本时隙第9次PD回读结果。
 bit[15:0]   本时隙第8次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT8_9_UNION */
#define CBBP_HKADC_RESULT8_9_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xF110)

/* 寄存器说明：
 bit[31:16]  本时隙第11次PD回读结果。
 bit[15:0]   本时隙第10次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT10_11_UNION */
#define CBBP_HKADC_RESULT10_11_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF114)

/* 寄存器说明：
 bit[31:16]  本时隙第13次PD回读结果。
 bit[15:0]   本时隙第12次PD回读结果。
   UNION结构:  CBBP_HKADC_RESUL12_13_UNION */
#define CBBP_HKADC_RESUL12_13_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xF118)

/* 寄存器说明：
 bit[31:16]  本时隙第15次PD回读结果。
 bit[15:0]   本时隙第14次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT14_15_UNION */
#define CBBP_HKADC_RESULT14_15_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF11C)

/* 寄存器说明：
 bit[31:16]  本时隙第17次PD回读结果。
 bit[15:0]   本时隙第16次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT16_17_UNION */
#define CBBP_HKADC_RESULT16_17_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF120)

/* 寄存器说明：
 bit[31:16]  本时隙第19次PD回读结果。
 bit[15:0]   本时隙第08次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT18_19_UNION */
#define CBBP_HKADC_RESULT18_19_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF124)

/* 寄存器说明：
 bit[31:16]  本时隙第21次PD回读结果。
 bit[15:0]   本时隙第20次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT20_21_UNION */
#define CBBP_HKADC_RESULT20_21_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF128)

/* 寄存器说明：
 bit[31:16]  本时隙第23次PD回读结果。
 bit[15:0]   本时隙第22次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT22_23_UNION */
#define CBBP_HKADC_RESULT22_23_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF12C)

/* 寄存器说明：
 bit[31:16]  本时隙第25次PD回读结果。
 bit[15:0]   本时隙第24次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT24_25_UNION */
#define CBBP_HKADC_RESULT24_25_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF130)

/* 寄存器说明：
 bit[31:16]  本时隙第27次PD回读结果。
 bit[15:0]   本时隙第26次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT26_27_UNION */
#define CBBP_HKADC_RESULT26_27_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF134)

/* 寄存器说明：
 bit[31:16]  本时隙第29次PD回读结果。
 bit[15:0]   本时隙第28次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT28_29_UNION */
#define CBBP_HKADC_RESULT28_29_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF138)

/* 寄存器说明：
 bit[31:16]  本时隙第31次PD回读结果。
 bit[15:0]   本时隙第30次PD回读结果。
   UNION结构:  CBBP_HKADC_RESULT30_31_UNION */
#define CBBP_HKADC_RESULT30_31_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF13C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   每时隙/PCG上行PA vbias控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。
   UNION结构:  CBBP_AUXDAC_START_TIME_UNION */
#define CBBP_AUXDAC_START_TIME_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF160)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:8]   每时隙软件配置的vbias控制字，无符号数。
 bit[7:1]    保留
 bit[0]      AUXDAC模块使能，高电平有效。
   UNION结构:  CBBP_AUXDAC_SSI_CFG_UNION */
#define CBBP_AUXDAC_SSI_CFG_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF164)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      w1_pulse，软件写1时产生脉冲，用于发送aucxdac vbias控制字。cpu_auxdac_force_en=1时才有效。
   UNION结构:  CBBP_AUXDAC_START_UNION */
#define CBBP_AUXDAC_START_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF168)

/* 寄存器说明：
 bit[31]     auxdac ssi强制发送使能，高电平有效。
 bit[30:1]   保留
 bit[0]      vbias控制字地址
   UNION结构:  CBBP_AUXDAC_FORCE_UNION */
#define CBBP_AUXDAC_FORCE_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xF16C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  auxdac关闭控制字。
 bit[15:11]  保留
 bit[10:0]   auxdac启动控制字。
   UNION结构:  CBBP_AUXDAC_CFG_UNION */
#define CBBP_AUXDAC_CFG_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xF170)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   每时隙/PCG上行PA APT控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。
   UNION结构:  CBBP_APT_START_TIME_UNION */
#define CBBP_APT_START_TIME_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF180)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:8]   每时隙软件配置的APT控制字，无符号数。
 bit[7:1]    保留
 bit[0]      APT模块使能，高电平有效。同时输出给作为快速DCDC芯片使能。
   UNION结构:  CBBP_APT_CFG_UNION */
#define CBBP_APT_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF184)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      w1_pulse，软件写1时产生脉冲，用于 强制发送apt控制字。
   UNION结构:  CBBP_APT_START_UNION */
#define CBBP_APT_START_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF188)

/* 寄存器说明：
 bit[31]     apt pdm强制发送使能，高电平有效。
 bit[30:1]   保留
 bit[0]      apt pdm脉冲格式选择，0：PWM，1：PDM
   UNION结构:  CBBP_APT_FORCE_UNION */
#define CBBP_APT_FORCE_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF18C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:0]   每时隙afc控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。
   UNION结构:  CBBP_AFC_START_TIME_UNION */
#define CBBP_AFC_START_TIME_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF1A0)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:8]   每时隙软件配置的AFC控制字，无符号数。
 bit[7:2]    保留
 bit[1]      afc pdm控制字位宽选择 0：12bit 1：13bit.
 bit[0]      AFC PDM/PWM模式选择，0:PDM模式，1：PWM方式
   UNION结构:  CBBP_AFC_CFG_UNION */
#define CBBP_AFC_CFG_ADDR                             (SOC_BBP_CDMA_BASE_ADDR + 0xF1A4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      w1_pulse，软件写1时产生脉冲，用于强制发送afc控制字。
   UNION结构:  CBBP_AFC_START_UNION */
#define CBBP_AFC_START_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF1A8)

/* 寄存器说明：
 bit[31]     AFC PDM强制更新使能，高电平有效。
 bit[30:0]   保留
   UNION结构:  CBBP_AFC_FORCE_UNION */
#define CBBP_AFC_FORCE_ADDR                           (SOC_BBP_CDMA_BASE_ADDR + 0xF1AC)

/* 寄存器说明：
 bit[31:3]   保留
 bit[2:0]    前端控制模块的自动时钟门控旁路信号，1表示旁路时钟门控，即时钟常开；0表示自动时钟门控生效。
             [0] MIPI的自动时钟门控旁路控制
             [1] RFIC_SSI的自动时钟门控旁路控制
             [2] GPIO的自动时钟门控旁路控制
   UNION结构:  CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION */
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF1B0)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      异常配置状态清除，用于清除异常状态上报结果（0x54[14:12], 0x8c[14:12], 0xb8[14:12], 0xec[22:20]）。如果不清除，则异常结果一直保持。
   UNION结构:  CBBP_ERR_CONFIG_CLR_UNION */
#define CBBP_ERR_CONFIG_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xF1B4)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_gpio_ctrl_valid_cfg之后配置本信号
 bit[7:5]    保留
 bit[4]      RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_mipi_ctrl_valid_cfg之后配置本信号
 bit[3:1]    保留
 bit[0]      RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_ssi_ctrl_valid_cfg之后配置本信号
   UNION结构:  CBBP_CTRL_VALID_IND_CFG_UNION */
#define CBBP_CTRL_VALID_IND_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1B8)

/* 寄存器说明：
   详      述：RF SSI控制指令有效标志配置，在完成控制指令配置后，配置本信号，用于指示有多少有效的控制指令。每bit对应1条控制指令。举例：0x0001则表示只有第0行的指令有效，0x1001则表示第0行和第12行的指令有效。
   UNION结构 ：无 */
#define CBBP_SSI_CTRL_VALID_CFG_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1BC)

/* 寄存器说明：
   详      述：MIPI控制指令有效标志配置，在完成控制指令配置后，配置本信号，用于指示有多少有效的控制指令。每bit对应1条控制指令。举例：0x0001则表示只有第0行的指令有效，0x1001则表示第0行和第12行的指令有效。
   UNION结构 ：无 */
#define CBBP_MIPI_CTRL_VALID_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1C0)

/* 寄存器说明：
   详      述：GPIO控制指令有效标志配置，在完成控制指令配置后，配置本信号，用于指示有多少有效的控制指令。每bit对应1条控制指令。举例：0x0001则表示只有第0行的指令有效，0x1001则表示第0行和第12行的指令有效。
   UNION结构 ：无 */
#define CBBP_GPIO_CTRL_VALID_CFG_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1C4)

/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      GPIO控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。
 bit[7:5]    保留
 bit[4]      MIPI控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。
 bit[3:1]    保留
 bit[0]      RF SSI控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。
   UNION结构:  CBBP_CTRL_VALID_FORCE_RESET_UNION */
#define CBBP_CTRL_VALID_FORCE_RESET_ADDR              (SOC_BBP_CDMA_BASE_ADDR + 0xF1CC)

/* 寄存器说明：
   详      述：RF SSI当前页面的CTRL_VALID标志上报
   UNION结构 ：无 */
#define CBBP_SSI_CTRL_VALID_RPT_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xF1D0)

/* 寄存器说明：
   详      述：MIPI当前页面的CTRL_VALID标志上报
   UNION结构 ：无 */
#define CBBP_MIPI_CTRL_VALID_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1D4)

/* 寄存器说明：
   详      述：GPIO当前页面的CTRL_VALID标志上报
   UNION结构 ：无 */
#define CBBP_GPIO_CTRL_VALID_RPT_ADDR                 (SOC_BBP_CDMA_BASE_ADDR + 0xF1D8)



/***======================================================================***
                     (17/20) register_define_c_fe_ctrl_mem
 ***======================================================================***/
/* 寄存器说明：乒乓RAM，ctrl指令最大可配置16个
 bit[31:27]  保留
 bit[26:24]  本条控制指令对应的rfic配置指令的个数，3bit，0~7对应配置个数为0~7，即0表示不发送
 bit[23:17]  保留
 bit[16]     rfic指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效
 bit[15:11]  保留
 bit[10:0]   rfic指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
             二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
             配置绝对时标不等于定时绝对时标，则继续等待。
   UNION结构:  CBBP_RFIC_SSI_CTRL_RAM_UNION */
#define CBBP_RFIC_SSI_CTRL_RAM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF800)
#define CBBP_RFIC_SSI_CTRL_RAM_MEMDEPTH  (16)

/* 寄存器说明：乒乓RAM
 bit[31:25]  保留
 bit[24]     WR RF SSI读写标志，1表示读，0表示写
 bit[23:16]  Addr RF SSI地址信息
 bit[15:0]   该部分有2种可能的格式
             1）写格式：[15:0]Data RF SSI写操作时的数据信息
             2) 读格式：
             [15:12]Buf Addr,即RF SSI读操作时回读结果缓存Buffer对应的位置，该缓存Buffer位于公共前端模块，即bbp_comm_fe
             [11]E RF SSI读操作时，用于指示最后一个读操作，1有效。
             [10:0]保留
   UNION结构:  CBBP_RFIC_SSI_DATA_RAM_UNION */
#define CBBP_RFIC_SSI_DATA_RAM_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xF840)
#define CBBP_RFIC_SSI_DATA_RAM_MEMDEPTH  (112)

/* 寄存器说明：乒乓RAM，ctrl指令最大可配置16个
 bit[31:26]  保留
 bit[25:24]  本条控制指令对应的mipi配置指令的个数，2bit，0~3对应配置个数为0~3，即0表示不发送
 bit[23:17]  保留
 bit[16]     mipi指令生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效
 bit[15:11]  保留
 bit[10:0]   mipi指令生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
             二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
             配置绝对时标不等于定时绝对时标，则继续等待。
   UNION结构:  CBBP_MIPI_CTRL_RAM_UNION */
#define CBBP_MIPI_CTRL_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFA00)
#define CBBP_MIPI_CTRL_RAM_MEMDEPTH  (16)

/* 寄存器说明：乒乓RAM
   详      述：MIPI指令的数据缓存区，共96行，格式见接口说明书
   UNION结构 ：无 */
#define CBBP_MIPI_DATA_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFA40)
#define CBBP_MIPI_DATA_RAM_MEMDEPTH  (96)

/* 寄存器说明：乒乓RAM，ctrl指令最大可配置32个
 bit[31:25]  GPIO一共64个地址,其中ctrl_buff和data_buff地址个数按照1:1分配，数据格式见接口说明书。不需要使用的地址须填零。Data的bit内容同GPIO_FORCE_DATA寄存器的内容
 bit[24]     本条控制指令对应的GPIO配置指令的个数，1bit，1对应配置个数为1，0表示不发送
 bit[23:17]  保留
 bit[16]     GPIO指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效
 bit[15:11]  保留
 bit[10:0]   GPIO指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
             二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
             配置绝对时标不等于定时绝对时标，则继续等待。
   UNION结构:  CBBP_GPIO_CTRL_RAM_UNION */
#define CBBP_GPIO_CTRL_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFC00)
#define CBBP_GPIO_CTRL_RAM_MEMDEPTH  (32)

/* 寄存器说明：乒乓RAM
 bit[31]     为0时，表示公共线控ant_pa_sel数据
             为1时表示专用线控，每个bit的含义如上述bit[6:0]描述
 bit[30:0]   线控配置数据
   UNION结构:  CBBP_GPIO_DATA_RAM_UNION */
#define CBBP_GPIO_DATA_RAM_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xFC80)
#define CBBP_GPIO_DATA_RAM_MEMDEPTH  (32)

/* 寄存器说明：ctrl指令最大可配置16个
 bit[31:25]  保留
 bit[24]     本条控制指令对应的GPIO配置指令的个数，3bit，0~7对应配置个数为0~7，即0表示不发送
 bit[23:17]  保留
 bit[16]     hkadc指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效
 bit[15:11]  保留
 bit[10:0]   hkadc指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
             二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
             配置绝对时标不等于定时绝对时标，则继续等待。
   UNION结构:  CBBP_HKADC_SSI_CTRL_RAM_UNION */
#define CBBP_HKADC_SSI_CTRL_RAM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xFD00)
#define CBBP_HKADC_SSI_CTRL_RAM_MEMDEPTH  (64)

/* 寄存器说明：
 bit[31:17]  保留
 bit[16]     配置指令的类型，0表示为HKADC SSI操作指令，1表示为HKADC通道请求操作指令
 bit[15:0]   该部分有3种可能的格式，分别如下：
             1. 当hkadc_cfg_type=0时，如果bit[15]=0,表示写操作，[14:8]为写地址，[7:0]为写数据
             2. 当hkadc_cfg_type=0时，如果bit[15]=1,表示读操作，[14:8]为写地址，[7:3]表示HKADC SSI读操作时回读结果缓存Buffer对应的位置，该缓存Buffer位于本模块内部，缓存区大小设置为32
             [2]HKADC SSI读操作时，用于指示最后一个读操作，1有效，当该bit有效，前端控制模块在本次HKADC SSI读操作完成后产生中断上报，触发软件读取HKADC SSI回读结果
             3. 当hkadc_cfg_type=1时，如果bit[15]=0,表示HKADC通道请求操作指令，[15:1]为保留位，[0]为请求是否生效
   UNION结构:  CBBP_HKADC_SSI_DATA_RAM_UNION */
#define CBBP_HKADC_SSI_DATA_RAM_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xFE00)
#define CBBP_HKADC_SSI_DATA_RAM_MEMDEPTH  (64)



/***======================================================================***
                     (18/20) register_define_sdr_gdrx_gauge
 ***======================================================================***/
/* 寄存器说明：
 bit[31]     GDRX停止脉冲，写1停止。自清零，写0无意义。
 bit[30]     时钟校准使能，写1开启。自清零，写0无意义。
 bit[29:17]  保留
 bit[16:0]   时钟校准32KHz时钟个数
   UNION结构:  CBBP_GDRX_GAUGE_EN_CNF_UNION */
#define CBBP_GDRX_GAUGE_EN_CNF_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC000)

/* 寄存器说明：
 bit[31]     睡眠状态查询。1，正在睡眠。
 bit[30]     测量状态查询。1，正在测量。
 bit[29:28]  保留
 bit[27:0]   时钟校准结果，测量周期内104M钟个数
   UNION结构:  CBBP_GAUGE_RESULT_RPT_UNION */
#define CBBP_GAUGE_RESULT_RPT_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC004)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   IMI时钟中断上报时GTC的TDMA QB计数，测试用
   UNION结构:  CBBP_IMI_INT_TDMA_QB_UNION */
#define CBBP_IMI_INT_TDMA_QB_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC008)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   32K时钟中断上报时GTC的TDMA QB计数，测试用
   UNION结构:  CBBP_SLEEP_INT_TDMA_QB_UNION */
#define CBBP_SLEEP_INT_TDMA_QB_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC00C)



/***======================================================================***
                     (19/20) register_define_sdr_g_timing
 ***======================================================================***/
/* 寄存器说明：
 bit[31:9]   保留
 bit[8]      1表示DRX测试模式使能，此时GTC时钟应不关闭，用于DRX唤醒后的定时维护情况的比对。正常使用下该信号应该被置0，测试用
 bit[7:0]    保留
   UNION结构:  CBBP_DRX_TEST_CFG_UNION */
#define CBBP_DRX_TEST_CFG_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xC200)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   帧中断与TimeBase时间偏差，单位qb，测试用
   UNION结构:  CBBP_G2_GTC_FRM_OFFSET_RPT_UNION */
#define CBBP_G2_GTC_FRM_OFFSET_RPT_ADDR               (SOC_BBP_CDMA_BASE_ADDR + 0xC204)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  精简帧号维护机制中的T3初始值，该参数值与cpu_gtc_t1_cnt，
             cpu_gtc_t2_cnt，cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T3值
             
 bit[23:21]  保留
 bit[20:16]  精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t1_cnt，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号
             cpu_gtc_t3_cnt，cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T2值
             
 bit[15:11]  保留
 bit[10:0]   精简帧号维护机制中的T1初始值，该参数值与cpu_gtc_t2_cnt，cpu_gtc_t3_cnt，
             cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T1值
   UNION结构:  CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION */
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xC208)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:24]  GTC内部维护的T3计数器上报
 bit[23:21]  保留
 bit[20:16]  GTC内部维护的T2计数器上报
 bit[15:11]  保留
 bit[10:0]   GTC内部维护的T1计数器上报
   UNION结构:  CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION */
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_ADDR             (SOC_BBP_CDMA_BASE_ADDR + 0xC20C)

/* 寄存器说明：
 bit[31]     CPU配置的cpu_gtc_frm_offset，cpu_gtc_frm_it_offset立即生效指示信号，逻辑自清零。(不同类型寄存器，能否在同一地址生成)
 bit[30:29]  保留
 bit[28:16]  CPU配置的gtc_frm_it_offset参数
 bit[15:13]  保留
 bit[12:0]   CPU配置的gtc_frm_offset参数
   UNION结构:  CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION */
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_ADDR           (SOC_BBP_CDMA_BASE_ADDR + 0xC210)

/* 寄存器说明：
 bit[31]     帧号初始化信号，1有效，逻辑自清零，只有当需要T1,T2,T3，fn_low，fn_high都写入后方可对该bit置1
 bit[30:27]  保留
 bit[26:16]  CPU配置TDMA帧号高位0~2047循环计数，低位计满后，高位才加1；CPU配置后，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号
 bit[15:11]  保留
 bit[10:0]   CPU配置的TDMA帧号低位0~26x51-1循环计数, CPU配置后，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号
   UNION结构:  CBBP_G2_CPU_GTC_FN_CFG_UNION */
#define CBBP_G2_CPU_GTC_FN_CFG_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC214)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  GTC此时实际帧号高位
 bit[15:11]  保留
 bit[10:0]   GTC此时实际帧号低位
   UNION结构:  CBBP_G2_GTC_FN_RPT_UNION */
#define CBBP_G2_GTC_FN_RPT_ADDR                       (SOC_BBP_CDMA_BASE_ADDR + 0xC218)

/* 寄存器说明：
 bit[31:29]  保留
 bit[28:16]  绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用
 bit[15:13]  保留
 bit[12:0]   当前时刻TDMA的QB计数值
   UNION结构:  CBBP_GTC_QB_RPT_UNION */
#define CBBP_GTC_QB_RPT_ADDR                          (SOC_BBP_CDMA_BASE_ADDR + 0xC21C)

/* 寄存器说明：
 bit[31:27]  保留
 bit[26:16]  绝对时标帧号上报，该值变化时刻在gtc_timebase_qb为4999处，计数范围0~2047，测试用
 bit[15:13]  保留
 bit[12:0]   绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用
   UNION结构:  CBBP_TIMEBASE_RPT_UNION */
#define CBBP_TIMEBASE_RPT_ADDR                        (SOC_BBP_CDMA_BASE_ADDR + 0xC220)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断请求，1表示中断请求，0表示无中断请求，下同
             [1] GTC PAGE中断请求
             [2] 同步搜索中断请求
             [3] 译码数据上报中断请求
             [4] 时隙0中断请求，1有效
             [5] 时隙1中断请求
             [6] 时隙2中断请求
             [7] 时隙3中断请求
             [8] 时隙4中断请求
             [9] 时隙5中断请求
             [10] 时隙6中断请求
             [11] 时隙7中断请求
             [12] 可编程中断0请求
             [13] 可编程中断1请求
             [14] 可编程中断2请求
             [15] 可编程中断3请求
             [16] 可编程中断4请求
             [17] 可编程中断5请求
             [18] 可编程中断6请求
             [19] 可编程中断7请求
             [23:20]保留
             [24] 时钟测量中断
             [28] 电平测量结束中断
             [29] 解调结束中断
   UNION结构:  CBBP_G2_CPU_INT_STA_UNION */
#define CBBP_G2_CPU_INT_STA_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC224)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断屏蔽信号，1表示中断请求屏蔽，0表示该中断不屏蔽，下同
             [1] GTC PAGE中断屏蔽寄存器
             [2] 同步搜索中断屏蔽寄存器
             [3] 译码数据上报中断屏蔽寄存器
             [4] 时隙0中断屏蔽寄存器，1有效
             [5] 时隙1中断屏蔽寄存器
             [6] 时隙2中断屏蔽寄存器
             [7] 时隙3中断屏蔽寄存器
             [8] 时隙4中断屏蔽寄存器
             [9] 时隙5中断屏蔽寄存器
             [10] 时隙6中断屏蔽寄存器
             [11] 时隙7中断屏蔽寄存器
             [12] 可编程中断0屏蔽寄存器
             [13] 可编程中断1屏蔽寄存器
             [14] 可编程中断2屏蔽寄存器
             [15] 可编程中断3屏蔽寄存器
             [16] 可编程中断4屏蔽寄存器
             [17] 可编程中断5屏蔽寄存器
             [18] 可编程中断6屏蔽寄存器
             [19] 可编程中断7屏蔽寄存器
             [24] 时钟测量中断屏蔽寄存器
             [28] 电平测量结束中断屏蔽寄存器
             [29] 解调结束中断屏蔽寄存器
   UNION结构:  CBBP_G2_CPU_INT_MASK_UNION */
#define CBBP_G2_CPU_INT_MASK_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC228)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断清零信号，1表示中断请求清除，0表示该中断不清除
             下面描述相同
             [1] GTC PAGE中断清零寄存器
             [2] 同步搜索中断清零信号
             [3] 译码数据上报中断清零信号
             [4] 时隙0中断清零信号，1有效
             [5] 时隙1中断清零信号
             [6] 时隙2中断清零信号
             [7] 时隙3中断清零信号
             [8] 时隙4中断清零信号
             [9] 时隙5中断清零信号
             [10] 时隙6中断清零信号
             [11] 时隙7中断清零信号
             [12] 可编程中断0清零信号
             [13] 可编程中断1清零信号
             [14] 可编程中断2清零信号
             [15] 可编程中断3清零信号
             [16] 可编程中断4清零信号
             [17] 可编程中断5清零信号
             [18] 可编程中断6清零信号
             [19] 可编程中断7清零信号
             [24] 时钟测量中断清零信号
             [28] 电平测量结束中断清零信号
             [29] 解调结束中断清零信号
   UNION结构:  CBBP_G2_CPU_INT_CLR_UNION */
#define CBBP_G2_CPU_INT_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC22C)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断请求，1表示中断请求，0表示无中断请求，下同
             [1] GTC PAGE中断请求
             [2] 同步搜索中断请求
             [3] 译码数据上报中断请求
             [4] 时隙0中断请求，1有效
             [5] 时隙1中断请求
             [6] 时隙2中断请求
             [7] 时隙3中断请求
             [8] 时隙4中断请求
             [9] 时隙5中断请求
             [10] 时隙6中断请求
             [11] 时隙7中断请求
             [12] 可编程中断0请求
             [13] 可编程中断1请求
             [14] 可编程中断2请求
             [15] 可编程中断3请求
             [16] 可编程中断4请求
             [17] 可编程中断5请求
             [18] 可编程中断6请求
             [19] 可编程中断7请求
             [24] CTU异系统测量中断0
             [25] CTU异系统测量中断1
             [26] CTU异系统测量中断2
             [27] 时钟测量中断
             [28] 电平测量结束中断
             [29]  解调结束中断
   UNION结构:  CBBP_G2_DSP_INT_STA_UNION */
#define CBBP_G2_DSP_INT_STA_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC230)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断屏蔽信号，1表示中断请求屏蔽，0表示该中断不屏蔽
             [1] GTC PAGE中断屏蔽寄存器
             [2] 同步搜索中断屏蔽寄存器
             [3] 译码数据上报中断屏蔽寄存器
             [4] 时隙0中断屏蔽寄存器，1有效
             [5] 时隙1中断屏蔽寄存器
             [6] 时隙2中断屏蔽寄存器
             [7] 时隙3中断屏蔽寄存器
             [8] 时隙4中断屏蔽寄存器
             [9] 时隙5中断屏蔽寄存器
             [10] 时隙6中断屏蔽寄存器
             [11] 时隙7中断屏蔽寄存器
             [12] 可编程中断0屏蔽寄存器
             [13] 可编程中断1屏蔽寄存器
             [14] 可编程中断2屏蔽寄存器
             [15] 可编程中断3屏蔽寄存器
             [16] 可编程中断4屏蔽寄存器
             [17] 可编程中断5屏蔽寄存器
             [18] 可编程中断6屏蔽寄存器
             [19] 可编程中断7屏蔽寄存器
             [24] CTU异系统测量中断0
             [25] CTU异系统测量中断1
             [26] CTU异系统测量中断2
             [27] 时钟测量中断
             [28] 电平测量结束中断屏蔽寄存器
             [29] 解调结束中断屏蔽寄存器
   UNION结构:  CBBP_G2_DSP_INT_MASK_UNION */
#define CBBP_G2_DSP_INT_MASK_ADDR                     (SOC_BBP_CDMA_BASE_ADDR + 0xC234)

/* 寄存器说明：
 bit[31:30]  保留
 bit[29:0]   [0] TDMA帧中断清零信号，1表示中断请求清除，0表示该中断不清除
             [1] GTC PAGE中断清零寄存器
             [2] 同步搜索中断清零信号
             [3] 译码数据上报中断清零信号
             [4] 时隙0中断清零信号，1有效
             [5] 时隙1中断清零信号
             [6] 时隙2中断清零信号
             [7] 时隙3中断清零信号
             [8] 时隙4中断清零信号
             [9] 时隙5中断清零信号
             [10] 时隙6中断清零信号
             [11] 时隙7中断清零信号
             [12] 可编程中断0清零信号
             [13] 可编程中断1清零信号
             [14] 可编程中断2清零信号
             [15] 可编程中断3清零信号
             [16] 可编程中断4清零信号
             [17] 可编程中断5清零信号
             [18] 可编程中断6清零信号
             [19] 可编程中断7清零信号
             [23:20]保留
             [24] CTU异系统测量中断0
             [25] CTU异系统测量中断1
             [26] CTU异系统测量中断2
             [27] 时钟测量中断
             [28] 电平测量结束中断清零信号
             [29] 解调结束中断清零信号
   UNION结构:  CBBP_G2_DSP_INT_CLR_UNION */
#define CBBP_G2_DSP_INT_CLR_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC238)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G软化可配置定时中断mask：
             bit16，1表示屏蔽tdma帧内时隙0内中断；
             bit17，1表示屏蔽tdma帧内时隙1内中断；
             …
 bit[15:10]  保留
 bit[9:0]    G软化可配置定时中断时隙内位置，取值范围0~624，单位Qb
   UNION结构:  CBBP_TDMA_SLOT_INT1_UNION */
#define CBBP_TDMA_SLOT_INT1_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC240)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G软化可配置定时中断mask：
             bit16，1表示屏蔽tdma帧内时隙0内中断；
             bit17，1表示屏蔽tdma帧内时隙1内中断；
             …
 bit[15:10]  保留
 bit[9:0]    G软化可配置定时中断时隙内位置，取值范围0~624，单位Qb
   UNION结构:  CBBP_TDMA_SLOT_INT2_UNION */
#define CBBP_TDMA_SLOT_INT2_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC244)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   定点睡眠模式下，睡眠起始Qb时刻（TDMA）时刻，该参数是基于TDMA时标gtc_tdma_qb的。
   UNION结构:  CBBP_GDRX_SLEEP_POINT_UNION */
#define CBBP_GDRX_SLEEP_POINT_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC248)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9:0]    DRX连线优化，ON区到OFF区补偿，单位Qb，默认值16
   UNION结构:  CBBP_CPU_TRANS_COMP_UNION */
#define CBBP_CPU_TRANS_COMP_ADDR                      (SOC_BBP_CDMA_BASE_ADDR + 0xC24C)



/***======================================================================***
                     (20/20) register_define_sdr_g_int
 ***======================================================================***/
/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      送给DSP的g软化中断使能，1表示打开中断
   UNION结构:  CBBP_DSP_SDR_G_INT_EN_UNION */
#define CBBP_DSP_SDR_G_INT_EN_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC400)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断清零信号，软件配置1，清除相应的bit
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_DSP_SDR_G_INT_CLR_UNION */
#define CBBP_DSP_SDR_G_INT_CLR_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC404)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断mask信号，软件配置1，相应的bit中断不产生
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_DSP_SDR_G_INT_MASK_UNION */
#define CBBP_DSP_SDR_G_INT_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xC408)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断状态信号，1表示相应的中断上报
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_DSP_SDR_G_INT_STA_UNION */
#define CBBP_DSP_SDR_G_INT_STA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC40C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      送给ARM的g软化中断使能，1表示打开中断
   UNION结构:  CBBP_ARM_SDR_G_INT_EN_UNION */
#define CBBP_ARM_SDR_G_INT_EN_ADDR                    (SOC_BBP_CDMA_BASE_ADDR + 0xC410)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    ARM中断清零信号，软件配置1，清除相应的bit
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_ARM_SDR_G_INT_CLR_UNION */
#define CBBP_ARM_SDR_G_INT_CLR_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC414)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    ARM中断mask信号，软件配置1，相应的bit中断不产生
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_ARM_SDR_G_INT_MASK_UNION */
#define CBBP_ARM_SDR_G_INT_MASK_ADDR                  (SOC_BBP_CDMA_BASE_ADDR + 0xC418)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    ARM中断状态信号，1表示相应的中断上报
             bit0：可配置g定时中断1；
             bit1：可配置g定时中断2；
             
   UNION结构:  CBBP_ARM_SDR_G_INT_STA_UNION */
#define CBBP_ARM_SDR_G_INT_STA_ADDR                   (SOC_BBP_CDMA_BASE_ADDR + 0xC41C)





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
                     (1/20) register_define_c_glb
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_VIRAGE_RM_CTRL_C_0_UNION
 结构说明  : VIRAGE_RM_CTRL_C_0 寄存器结构定义。地址偏移量:0x00，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      virage_rm_ctrl_c_0_reg;
    struct
    {
        unsigned long  mem_ctrl_s_c      : 16; /* bit[0-15] : 单口RAM延时控制。 */
        unsigned long  mem_ctrl_d_1w2r_c : 16; /* bit[16-31]: 1w2r双口RAM延时控制。 */
    } reg;
} CBBP_VIRAGE_RM_CTRL_C_0_UNION;
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_s_c_START       (0)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_s_c_END         (15)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_d_1w2r_c_START  (16)
#define CBBP_VIRAGE_RM_CTRL_C_0_mem_ctrl_d_1w2r_c_END    (31)


/*****************************************************************************
 结构名    : CBBP_VIRAGE_RM_CTRL_C_1_UNION
 结构说明  : VIRAGE_RM_CTRL_C_1 寄存器结构定义。地址偏移量:0x04，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      virage_rm_ctrl_c_1_reg;
    struct
    {
        unsigned long  mem_ctrl_d_1rw2rw_c : 16; /* bit[0-15] : 1rw2rw双口RAM延时控制。 */
        unsigned long  rom_ctrl_c          : 8;  /* bit[16-23]: ROM延时控制。 */
        unsigned long  reserved            : 8;  /* bit[24-31]: 保留 */
    } reg;
} CBBP_VIRAGE_RM_CTRL_C_1_UNION;
#define CBBP_VIRAGE_RM_CTRL_C_1_mem_ctrl_d_1rw2rw_c_START  (0)
#define CBBP_VIRAGE_RM_CTRL_C_1_mem_ctrl_d_1rw2rw_c_END    (15)
#define CBBP_VIRAGE_RM_CTRL_C_1_rom_ctrl_c_START           (16)
#define CBBP_VIRAGE_RM_CTRL_C_1_rom_ctrl_c_END             (23)


/*****************************************************************************
 结构名    : CBBP_SYS_RST_CTRL_C_UNION
 结构说明  : SYS_RST_CTRL_C 寄存器结构定义。地址偏移量:0x08，初值:0x007F0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_rst_ctrl_c_reg;
    struct
    {
        unsigned long  sys_rst_ctrl_c_timing       : 1;  /* bit[0]    : 系统时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit复位为0。
                                                                        定时模块。 */
        unsigned long  sys_rst_ctrl_c_intr         : 1;  /* bit[1]    : 中断模块。 */
        unsigned long  sys_rst_ctrl_c_srch         : 1;  /* bit[2]    : 搜索测量模块。 */
        unsigned long  sys_rst_ctrl_c_dldec        : 1;  /* bit[3]    : 译码模块。 */
        unsigned long  sys_rst_ctrl_c_ulcode       : 1;  /* bit[4]    : 编码模块。 */
        unsigned long  sys_rst_ctrl_c_fe_sdr_if    : 1;  /* bit[5]    : 前端数据接口模块。 */
        unsigned long  sys_rst_ctrl_c_fe_ctrl      : 1;  /* bit[6]    : 射频前端控制模块。 */
        unsigned long  sys_rst_ctrl_sdr_gdrx_gauge : 1;  /* bit[7]    : G软化时钟测量 */
        unsigned long  sys_rst_ctrl_sdr_g_timing   : 1;  /* bit[8]    : G软化定时 */
        unsigned long  sys_rst_ctrl_sdr_g_int      : 1;  /* bit[9]    : G软化中断 */
        unsigned long  sys_rst_ctrl_sdr_g_fe_abb   : 1;  /* bit[10]   : G软化前端数据 */
        unsigned long  reserved_0                  : 5;  /* bit[11-15]: 保留 */
        unsigned long  sys_clk_ctrl_c_timing       : 1;  /* bit[16]   : 系统时钟域CLK控制。在对各模块进行时钟控制时，将对应bit置1表示打开该模块的时钟；反之，将对应bit置0表示关闭该模块的时钟。
                                                                        定时模块。 */
        unsigned long  sys_clk_ctrl_c_intr         : 1;  /* bit[17]   : 中断模块。 */
        unsigned long  sys_clk_ctrl_c_srch         : 1;  /* bit[18]   : 搜索测量模块。 */
        unsigned long  sys_clk_ctrl_c_dldec        : 1;  /* bit[19]   : 译码模块。 */
        unsigned long  sys_clk_ctrl_c_ulcode       : 1;  /* bit[20]   : 编码模块。 */
        unsigned long  sys_clk_ctrl_c_fe_sdr_if    : 1;  /* bit[21]   : 前端数据接口模块。 */
        unsigned long  sys_clk_ctrl_c_fe_ctrl      : 1;  /* bit[22]   : 射频前端控制模块。 */
        unsigned long  sys_clk_ctrl_sdr_gdrx_gauge : 1;  /* bit[23]   : G软化时钟测量 */
        unsigned long  sys_clk_ctrl_sdr_g_timing   : 1;  /* bit[24]   : G软化定时 */
        unsigned long  sys_clk_ctrl_sdr_g_int      : 1;  /* bit[25]   : G软化中断 */
        unsigned long  sys_clk_ctrl_sdr_g_fe_abb   : 1;  /* bit[26]   : G软化前端数据 */
        unsigned long  reserved_1                  : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_SYS_RST_CTRL_C_UNION;
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_timing_START        (0)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_timing_END          (0)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_intr_START          (1)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_intr_END            (1)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_srch_START          (2)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_srch_END            (2)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_dldec_START         (3)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_dldec_END           (3)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_ulcode_START        (4)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_ulcode_END          (4)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_sdr_if_START     (5)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_sdr_if_END       (5)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_ctrl_START       (6)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_c_fe_ctrl_END         (6)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_gdrx_gauge_START  (7)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_gdrx_gauge_END    (7)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_timing_START    (8)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_timing_END      (8)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_int_START       (9)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_int_END         (9)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_fe_abb_START    (10)
#define CBBP_SYS_RST_CTRL_C_sys_rst_ctrl_sdr_g_fe_abb_END      (10)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_timing_START        (16)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_timing_END          (16)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_intr_START          (17)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_intr_END            (17)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_srch_START          (18)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_srch_END            (18)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_dldec_START         (19)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_dldec_END           (19)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_ulcode_START        (20)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_ulcode_END          (20)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_sdr_if_START     (21)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_sdr_if_END       (21)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_ctrl_START       (22)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_c_fe_ctrl_END         (22)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_gdrx_gauge_START  (23)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_gdrx_gauge_END    (23)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_timing_START    (24)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_timing_END      (24)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_int_START       (25)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_int_END         (25)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_fe_abb_START    (26)
#define CBBP_SYS_RST_CTRL_C_sys_clk_ctrl_sdr_g_fe_abb_END      (26)


/*****************************************************************************
 结构名    : CBBP_IMI_RST_CTRL_C_UNION
 结构说明  : IMI_RST_CTRL_C 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      imi_rst_ctrl_c_reg;
    struct
    {
        unsigned long  imi_rst_ctrl_c_timing        : 1;  /* bit[0]    : IMI时钟域RST控制。在对各模块进行复位时，将对应bit置1，之后再将对应bit复位为0。
                                                                         定时模块。 */
        unsigned long  imi_rst_ctrl_c_intr          : 1;  /* bit[1]    : 中断模块。 */
        unsigned long  imi_rst_ctrl_c_srch          : 1;  /* bit[2]    : 搜索测量模块。 */
        unsigned long  imi_rst_ctrl_c_dldec         : 1;  /* bit[3]    : 译码模块。 */
        unsigned long  imi_rst_ctrl_c_ulcode        : 1;  /* bit[4]    : 编码模块。 */
        unsigned long  imi_rst_ctrl_c_fe_sdr_if     : 1;  /* bit[5]    : 前端数据接口模块。 */
        unsigned long  imi_rst_ctrl_c_fe_ctrl       : 1;  /* bit[6]    : 射频前端控制模块。 */
        unsigned long  imi_rst_ctrl_sdr_gdrx_gauge  : 1;  /* bit[7]    : G软化时钟测量 */
        unsigned long  imi_rst_ctrl_sdr_g_timing    : 1;  /* bit[8]    : G软化定时 */
        unsigned long  imi_rst_ctrl_sdr_g_int       : 1;  /* bit[9]    : G软化中断 */
        unsigned long  reserved_0                   : 6;  /* bit[10-15]: 保留 */
        unsigned long  imi_addr_ctrl_c_timing       : 1;  /* bit[16]   : IMI地址片选控制屏蔽使能，高电平有效。该信号有效表示对应模块未被选中时屏蔽BBP内部该模块IMI地址。
                                                                         定时模块。 */
        unsigned long  imi_addr_ctrl_c_intr         : 1;  /* bit[17]   : 中断模块。 */
        unsigned long  imi_addr_ctrl_c_srch         : 1;  /* bit[18]   : 搜索测量模块。 */
        unsigned long  imi_addr_ctrl_c_dldec        : 1;  /* bit[19]   : 译码模块。 */
        unsigned long  imi_addr_ctrl_c_ulcode       : 1;  /* bit[20]   : 编码模块。 */
        unsigned long  imi_addr_ctrl_c_fe_sdr_if    : 1;  /* bit[21]   : 前端数据接口模块。 */
        unsigned long  imi_addr_ctrl_c_fe_ctrl      : 1;  /* bit[22]   : 射频前端控制模块。 */
        unsigned long  imi_addr_ctrl_sdr_gdrx_gauge : 1;  /* bit[23]   : G软化时钟测量 */
        unsigned long  imi_addr_ctrl_sdr_g_timing   : 1;  /* bit[24]   : G软化定时 */
        unsigned long  imi_addr_ctrl_sdr_g_int      : 1;  /* bit[25]   : G软化中断 */
        unsigned long  reserved_1                   : 6;  /* bit[26-31]: 保留 */
    } reg;
} CBBP_IMI_RST_CTRL_C_UNION;
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_timing_START         (0)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_timing_END           (0)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_intr_START           (1)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_intr_END             (1)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_srch_START           (2)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_srch_END             (2)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_dldec_START          (3)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_dldec_END            (3)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_ulcode_START         (4)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_ulcode_END           (4)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_sdr_if_START      (5)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_sdr_if_END        (5)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_ctrl_START        (6)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_c_fe_ctrl_END          (6)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_gdrx_gauge_START   (7)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_gdrx_gauge_END     (7)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_timing_START     (8)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_timing_END       (8)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_int_START        (9)
#define CBBP_IMI_RST_CTRL_C_imi_rst_ctrl_sdr_g_int_END          (9)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_timing_START        (16)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_timing_END          (16)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_intr_START          (17)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_intr_END            (17)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_srch_START          (18)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_srch_END            (18)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_dldec_START         (19)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_dldec_END           (19)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_ulcode_START        (20)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_ulcode_END          (20)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_sdr_if_START     (21)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_sdr_if_END       (21)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_ctrl_START       (22)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_c_fe_ctrl_END         (22)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_gdrx_gauge_START  (23)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_gdrx_gauge_END    (23)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_timing_START    (24)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_timing_END      (24)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_int_START       (25)
#define CBBP_IMI_RST_CTRL_C_imi_addr_ctrl_sdr_g_int_END         (25)


/***======================================================================***
                     (2/20) register_define_c_timing
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_C_CK_MSR_PERIOD_UNION
 结构说明  : C_CK_MSR_PERIOD 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_ck_msr_period_reg;
    struct
    {
        unsigned long  c_ck_msr_period : 18; /* bit[0-17] : 时钟测量时间，32k时钟个数。最长支持5.12s。
                                                            说明：取值为0无意义。 */
        unsigned long  reserved        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_C_CK_MSR_PERIOD_UNION;
#define CBBP_C_CK_MSR_PERIOD_c_ck_msr_period_START  (0)
#define CBBP_C_CK_MSR_PERIOD_c_ck_msr_period_END    (17)


/*****************************************************************************
 结构名    : CBBP_C_CK_MSR_EN_UNION
 结构说明  : C_CK_MSR_EN 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_ck_msr_en_reg;
    struct
    {
        unsigned long  c_ck_msr_en : 1;  /* bit[0]   : 时钟测量使能。BBP检测上升沿，启动时钟测量。如果软件配置为0，BBP停止时钟测量。 */
        unsigned long  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_C_CK_MSR_EN_UNION;
#define CBBP_C_CK_MSR_EN_c_ck_msr_en_START  (0)
#define CBBP_C_CK_MSR_EN_c_ck_msr_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_CK_MSR_RPT_UNION
 结构说明  : CK_MSR_RPT 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ck_msr_rpt_reg;
    struct
    {
        unsigned long  ck_msr_rpt : 31; /* bit[0-30]: 时钟测量结果。上报了在ck_msr_period内的122.88MHz时钟个数 */
        unsigned long  reserved   : 1;  /* bit[31]  : 保留 */
    } reg;
} CBBP_CK_MSR_RPT_UNION;
#define CBBP_CK_MSR_RPT_ck_msr_rpt_START  (0)
#define CBBP_CK_MSR_RPT_ck_msr_rpt_END    (30)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_GET_POS_UNION
 结构说明  : SYS_CNT_1X_GET_POS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_pos_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_pos_1_4chip : 5;  /* bit[0-4]  : 更新sys_cnt_1x的时刻：
                                                                       [28:24]，base_cnt_2s上的时刻，取值范围0~24；
                                                                       [23:22]，base_cnt_80ms上的时刻，取值范围0~2；
                                                                       [21:5]，base_cnt_26ms上的时刻，取值范围0~32768*4-1；
                                                                       [4:0]，1/4chip内计数，取值范围0~24 */
        unsigned long  sys_cnt_1x_get_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_get_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_1x_get_pos_2s      : 5;  /* bit[24-28]:  */
        unsigned long  reserved                   : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_GET_POS_UNION;
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_26ms_START     (5)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_26ms_END       (21)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_80ms_START     (22)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_80ms_END       (23)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_2s_START       (24)
#define CBBP_SYS_CNT_1X_GET_POS_sys_cnt_1x_get_pos_2s_END         (28)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_GET_VALUE_UNION
 结构说明  : SYS_CNT_1X_GET_VALUE 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_value_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_value_1_4chip : 5;  /* bit[0-4]  : sys_cnt_get_pos时刻sys_cnt_1x的值：
                                                                         [29:24]，sys_cnt_1x_5p12s的值；
                                                                         [23:18]，sys_cnt_1x_80ms的值；
                                                                         [17:5]，sys_cnt_1x_1p25ms的值，取值范围0~1536*4-1；
                                                                         [4:0]，1/4chip内计数，取值范围0~24 */
        unsigned long  sys_cnt_1x_get_value_26ms    : 13; /* bit[5-17] :  */
        unsigned long  sys_cnt_1x_get_value_80ms    : 6;  /* bit[18-23]:  */
        unsigned long  sys_cnt_1x_get_value_5p12s   : 6;  /* bit[24-29]:  */
        unsigned long  reserved                     : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_GET_VALUE_UNION;
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_26ms_START     (5)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_26ms_END       (17)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_80ms_START     (18)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_80ms_END       (23)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_5p12s_START    (24)
#define CBBP_SYS_CNT_1X_GET_VALUE_sys_cnt_1x_get_value_5p12s_END      (29)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION
 结构说明  : SYS_CNT_1X_80MS_POS_CFG 寄存器结构定义。地址偏移量:0x00C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_cfg_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_1_4chip_cfg : 5;  /* bit[0-4]  : 1X定时突变后sys_cnt_1x  80ms帧头在base_cnt上的位置。
                                                                            Bit[4:0]：1/4chip内计数0~24
                                                                            bit[21:5]：26ms内计数0~32768*4-1
                                                                            bit[23:22]：80ms内计数0~2 */
        unsigned long  sys_cnt_1x_80ms_pos_26ms_cfg    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_80ms_pos_80ms_cfg    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                        : 8;  /* bit[24-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_CFG_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_1_4chip_cfg_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_1_4chip_cfg_END    (4)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_26ms_cfg_START     (5)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_26ms_cfg_END       (21)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_80ms_cfg_START     (22)
#define CBBP_SYS_CNT_1X_80MS_POS_CFG_sys_cnt_1x_80ms_pos_80ms_cfg_END       (23)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_GET_RDY_UNION
 结构说明  : SYS_CNT_1X_GET_RDY 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_get_rdy_reg;
    struct
    {
        unsigned long  sys_cnt_1x_get_rdy : 1;  /* bit[0]   : Sys_cnt_1x定时获取指示。
                                                              BBP接收到此指示后，等待base_cnt上sys_cnt_1x_get_pos时刻，将sys_cnt_1x更新为sys_cnt_1x_get_value。 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_GET_RDY_UNION;
#define CBBP_SYS_CNT_1X_GET_RDY_sys_cnt_1x_get_rdy_START  (0)
#define CBBP_SYS_CNT_1X_GET_RDY_sys_cnt_1x_get_rdy_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_1X_CHANGE_DIRECTION_UNION
 结构说明  : SYS_1X_CHANGE_DIRECTION 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_1x_change_direction_reg;
    struct
    {
        unsigned long  sys_1x_change_direction : 1;  /* bit[0]   : 系统定时调整方向。
                                                                   0：表示往左边调整6clk；
                                                                   1：表示往右边调整6clk；
                                                                   说明：定时采用100倍时钟，因此，6clk时间为6/100chip */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_1X_CHANGE_DIRECTION_UNION;
#define CBBP_SYS_1X_CHANGE_DIRECTION_sys_1x_change_direction_START  (0)
#define CBBP_SYS_1X_CHANGE_DIRECTION_sys_1x_change_direction_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_1X_CHANGE_RDY_UNION
 结构说明  : SYS_1X_CHANGE_RDY 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_1x_change_rdy_reg;
    struct
    {
        unsigned long  sys_1x_change_rdy : 1;  /* bit[0]   : 系统定时调整指示。
                                                             BBP在接收到此指示后，在最近的PCG完成系统定时 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_1X_CHANGE_RDY_UNION;
#define CBBP_SYS_1X_CHANGE_RDY_sys_1x_change_rdy_START  (0)
#define CBBP_SYS_1X_CHANGE_RDY_sys_1x_change_rdy_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_80MS_POS_RD_UNION
 结构说明  : SYS_CNT_1X_80MS_POS_RD 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_rd_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_rd : 1;  /* bit[0]   : 软件读取sys_cnt_1x_80ms_pos的指示，BBP接收到此信号后锁存本地的计数值 */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_RD_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_RD_sys_cnt_1x_80ms_pos_rd_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_RD_sys_cnt_1x_80ms_pos_rd_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_80MS_POS_UNION
 结构说明  : SYS_CNT_1X_80MS_POS 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_1_4chip : 5;  /* bit[0-4]  : sys_cnt_1x  80ms帧头在base_cnt上的位置。
                                                                        Bit[4:0]：1/4chip内计数0~24
                                                                        bit[21:5]：26ms内计数0~32768*4-1
                                                                        bit[23:22]：80ms内计数0~2 */
        unsigned long  sys_cnt_1x_80ms_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_1x_80ms_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_1x_80ms_pos_valid   : 1;  /* bit[24]   : sys_cnt_1x_80ms_pos有效指示，1表示读取的结果有效 */
        unsigned long  reserved                    : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_26ms_START     (5)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_26ms_END       (21)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_80ms_START     (22)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_80ms_END       (23)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_valid_START    (24)
#define CBBP_SYS_CNT_1X_80MS_POS_sys_cnt_1x_80ms_pos_valid_END      (24)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION
 结构说明  : SYS_CNT_1X_80MS_POS_VALID_CLR 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_80ms_pos_valid_clr_reg;
    struct
    {
        unsigned long  sys_cnt_1x_80ms_pos_valid_clr : 1;  /* bit[0]   : sys_cnt_1x_80ms_pos_valid清零信号，在完成sys_cnt_1x_80ms_pos读取后，使用此寄存器将其有效标志清除 */
        unsigned long  reserved                      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_UNION;
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_sys_cnt_1x_80ms_pos_valid_clr_START  (0)
#define CBBP_SYS_CNT_1X_80MS_POS_VALID_CLR_sys_cnt_1x_80ms_pos_valid_clr_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT_1X_MASK_UNION
 结构说明  : TIMING_INT_1X_MASK 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_1x_mask_reg;
    struct
    {
        unsigned long  timing_int_1x_mask : 1;  /* bit[0]   : 定时突变时，定时中断的mask指示。
                                                              0：表示不mask；
                                                              1：表示mask配置范围内的中断； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT_1X_MASK_UNION;
#define CBBP_TIMING_INT_1X_MASK_timing_int_1x_mask_START  (0)
#define CBBP_TIMING_INT_1X_MASK_timing_int_1x_mask_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT_1X_MASK_DIS_UNION
 结构说明  : TIMING_INT_1X_MASK_DIS 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_1x_mask_dis_reg;
    struct
    {
        unsigned long  timing_int_1x_mask_dis : 11; /* bit[0-10] : 定时突变时，定时中断的mask区间，chip为单位。 */
        unsigned long  reserved               : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_TIMING_INT_1X_MASK_DIS_UNION;
#define CBBP_TIMING_INT_1X_MASK_DIS_timing_int_1x_mask_dis_START  (0)
#define CBBP_TIMING_INT_1X_MASK_DIS_timing_int_1x_mask_dis_END    (10)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT1_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int1_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int1在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int1_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT1_SYS_CNT_1X_POS_timing_int1_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_1X_PERIOD_UNION
 结构说明  : TIMING_INT1_1X_PERIOD 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_1x_period_reg;
    struct
    {
        unsigned long  timing_int1_1x_period : 4;  /* bit[0-3] : Int1中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_1X_PERIOD_UNION;
#define CBBP_TIMING_INT1_1X_PERIOD_timing_int1_1x_period_START  (0)
#define CBBP_TIMING_INT1_1X_PERIOD_timing_int1_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_1X_EN_UNION
 结构说明  : TIMING_INT1_1X_EN 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_1x_en_reg;
    struct
    {
        unsigned long  timing_int1_1x_en : 1;  /* bit[0]   : 定时中断int1的使能。
                                                             0：表示不产生int1中断；
                                                             1：表示产生int1中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_1X_EN_UNION;
#define CBBP_TIMING_INT1_1X_EN_timing_int1_1x_en_START  (0)
#define CBBP_TIMING_INT1_1X_EN_timing_int1_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT2_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int2_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int2_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT2_SYS_CNT_1X_POS_timing_int2_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_1X_PERIOD_UNION
 结构说明  : TIMING_INT2_1X_PERIOD 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_1x_period_reg;
    struct
    {
        unsigned long  timing_int2_1x_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_1X_PERIOD_UNION;
#define CBBP_TIMING_INT2_1X_PERIOD_timing_int2_1x_period_START  (0)
#define CBBP_TIMING_INT2_1X_PERIOD_timing_int2_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_1X_EN_UNION
 结构说明  : TIMING_INT2_1X_EN 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_1x_en_reg;
    struct
    {
        unsigned long  timing_int2_1x_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                             0：表示不产生int中断；
                                                             1：表示产生int中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_1X_EN_UNION;
#define CBBP_TIMING_INT2_1X_EN_timing_int2_1x_en_START  (0)
#define CBBP_TIMING_INT2_1X_EN_timing_int2_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT3_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int3_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int3_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT3_SYS_CNT_1X_POS_timing_int3_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_1X_PERIOD_UNION
 结构说明  : TIMING_INT3_1X_PERIOD 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_1x_period_reg;
    struct
    {
        unsigned long  timing_int3_1x_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_1X_PERIOD_UNION;
#define CBBP_TIMING_INT3_1X_PERIOD_timing_int3_1x_period_START  (0)
#define CBBP_TIMING_INT3_1X_PERIOD_timing_int3_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_1X_EN_UNION
 结构说明  : TIMING_INT3_1X_EN 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_1x_en_reg;
    struct
    {
        unsigned long  timing_int3_1x_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                             0：表示不产生int中断；
                                                             1：表示产生int中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_1X_EN_UNION;
#define CBBP_TIMING_INT3_1X_EN_timing_int3_1x_en_START  (0)
#define CBBP_TIMING_INT3_1X_EN_timing_int3_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT4_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int4_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int4_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT4_SYS_CNT_1X_POS_timing_int4_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_1X_PERIOD_UNION
 结构说明  : TIMING_INT4_1X_PERIOD 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_1x_period_reg;
    struct
    {
        unsigned long  timing_int4_1x_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_1X_PERIOD_UNION;
#define CBBP_TIMING_INT4_1X_PERIOD_timing_int4_1x_period_START  (0)
#define CBBP_TIMING_INT4_1X_PERIOD_timing_int4_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_1X_EN_UNION
 结构说明  : TIMING_INT4_1X_EN 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_1x_en_reg;
    struct
    {
        unsigned long  timing_int4_1x_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                             0：表示不产生int中断；
                                                             1：表示产生int中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_1X_EN_UNION;
#define CBBP_TIMING_INT4_1X_EN_timing_int4_1x_en_START  (0)
#define CBBP_TIMING_INT4_1X_EN_timing_int4_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT5_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int5_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int5_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT5_SYS_CNT_1X_POS_timing_int5_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_1X_PERIOD_UNION
 结构说明  : TIMING_INT5_1X_PERIOD 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_1x_period_reg;
    struct
    {
        unsigned long  timing_int5_1x_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_1X_PERIOD_UNION;
#define CBBP_TIMING_INT5_1X_PERIOD_timing_int5_1x_period_START  (0)
#define CBBP_TIMING_INT5_1X_PERIOD_timing_int5_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_1X_EN_UNION
 结构说明  : TIMING_INT5_1X_EN 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_1x_en_reg;
    struct
    {
        unsigned long  timing_int5_1x_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                             0：表示不产生int中断；
                                                             1：表示产生int中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_1X_EN_UNION;
#define CBBP_TIMING_INT5_1X_EN_timing_int5_1x_en_START  (0)
#define CBBP_TIMING_INT5_1X_EN_timing_int5_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION
 结构说明  : TIMING_INT6_SYS_CNT_1X_POS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_sys_cnt_1x_pos_reg;
    struct
    {
        unsigned long  timing_int6_sys_cnt_1x_1p25ms_pos : 11; /* bit[0-10] : Int在sys_cnt_1x上的位置：
                                                                              [21:16]，sys_cnt_1x_80ms的值；
                                                                              [10:0]，sys_cnt_1x_1p25ms[15:5]的值,chip精度； */
        unsigned long  reserved_0                        : 5;  /* bit[11-15]: 保留 */
        unsigned long  timing_int6_sys_cnt_1x_80ms_pos   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                        : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_SYS_CNT_1X_POS_UNION;
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_1p25ms_pos_START  (0)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_1p25ms_pos_END    (10)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_80ms_pos_START    (16)
#define CBBP_TIMING_INT6_SYS_CNT_1X_POS_timing_int6_sys_cnt_1x_80ms_pos_END      (21)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_1X_PERIOD_UNION
 结构说明  : TIMING_INT6_1X_PERIOD 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_1x_period_reg;
    struct
    {
        unsigned long  timing_int6_1x_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                 0：表示中断周期为64chip；
                                                                 1：表示中断周期为128chip；
                                                                 2：表示中断周期为256chip；
                                                                 3：表示中断周期为512chip；
                                                                 4：表示中断周期为1.25ms；
                                                                 5：表示中断周期为5ms；
                                                                 6：表示中断周期为10ms；
                                                                 7：表示中断周期为20ms；
                                                                 8：表示中断周期为40ms；
                                                                 9：表示中断周期为80ms；
                                                                 10:表示中断周期为384chip； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_1X_PERIOD_UNION;
#define CBBP_TIMING_INT6_1X_PERIOD_timing_int6_1x_period_START  (0)
#define CBBP_TIMING_INT6_1X_PERIOD_timing_int6_1x_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_1X_EN_UNION
 结构说明  : TIMING_INT6_1X_EN 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_1x_en_reg;
    struct
    {
        unsigned long  timing_int6_1x_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                             0：表示不产生int中断；
                                                             1：表示产生int中断； */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_1X_EN_UNION;
#define CBBP_TIMING_INT6_1X_EN_timing_int6_1x_en_START  (0)
#define CBBP_TIMING_INT6_1X_EN_timing_int6_1x_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION
 结构说明  : SYS_CNT_1X_RPT_INT1_MASK 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int1_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int1_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_1x值的mask：
                                                                    bit0，为1表示上报中断1时刻的定时；
                                                                    bit1，为1表示上报中断2时刻的定时；
                                                                    …
                                                                    注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT1_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_sys_cnt_1x_rpt_int1_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT1_MASK_sys_cnt_1x_rpt_int1_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT1_UNION
 结构说明  : SYS_CNT_1X_RPT_INT1 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int1_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int1 : 5;  /* bit[0-4]  : 软件配置的第一个上报定时信息的中断时刻的sys_cnt_1x的值：
                                                                       
                                                                       [21:16]，sys_cnt_1x_80ms的值；
                                                                       [4:0]，sys_cnt_1x_1p25ms的值,64chip精度； */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : 保留 */
        unsigned long  sys_cnt_1x_80ms_rpt_int1   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT1_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_1p25ms_rpt_int1_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_1p25ms_rpt_int1_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_80ms_rpt_int1_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT1_sys_cnt_1x_80ms_rpt_int1_END      (21)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION
 结构说明  : SYS_CNT_1X_RPT_INT2_MASK 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int2_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int2_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_1x值的mask：
                                                                    bit0，为1表示上报中断1时刻的定时；
                                                                    bit1，为1表示上报中断2时刻的定时；
                                                                    …
                                                                    注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT2_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_sys_cnt_1x_rpt_int2_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT2_MASK_sys_cnt_1x_rpt_int2_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT2_UNION
 结构说明  : SYS_CNT_1X_RPT_INT2 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int2_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int2 : 5;  /* bit[0-4]  : 软件配置的第2个上报定时信息的中断时刻的sys_cnt_1x的值：
                                                                       
                                                                       [21:16]，sys_cnt_1x_80ms的值；
                                                                       [4:0]，sys_cnt_1x_1p25ms的值,64chip精度； */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : 保留 */
        unsigned long  sys_cnt_1x_80ms_rpt_int2   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT2_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_1p25ms_rpt_int2_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_1p25ms_rpt_int2_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_80ms_rpt_int2_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT2_sys_cnt_1x_80ms_rpt_int2_END      (21)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION
 结构说明  : SYS_CNT_1X_RPT_INT3_MASK 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int3_mask_reg;
    struct
    {
        unsigned long  sys_cnt_1x_rpt_int3_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_1x值的mask：
                                                                    bit0，为1表示上报中断1时刻的定时；
                                                                    bit1，为1表示上报中断2时刻的定时；
                                                                    …
                                                                    注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                 : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT3_MASK_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_sys_cnt_1x_rpt_int3_mask_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT3_MASK_sys_cnt_1x_rpt_int3_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT_INT3_UNION
 结构说明  : SYS_CNT_1X_RPT_INT3 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt_int3_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt_int3 : 5;  /* bit[0-4]  : 软件配置的第3个上报定时信息的中断时刻的sys_cnt_1x的值：
                                                                       
                                                                       [21:16]，sys_cnt_1x_80ms的值；
                                                                       [4:0]，sys_cnt_1x_1p25ms的值,64chip精度； */
        unsigned long  reserved_0                 : 11; /* bit[5-15] : 保留 */
        unsigned long  sys_cnt_1x_80ms_rpt_int3   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 10; /* bit[22-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT_INT3_UNION;
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_1p25ms_rpt_int3_START  (0)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_1p25ms_rpt_int3_END    (4)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_80ms_rpt_int3_START    (16)
#define CBBP_SYS_CNT_1X_RPT_INT3_sys_cnt_1x_80ms_rpt_int3_END      (21)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_PERIOD_UNION
 结构说明  : SYS_CNT_1X_PERIOD 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_period_reg;
    struct
    {
        unsigned long  sys_cnt_1x_period : 1;  /* bit[0]   : 1x系统计数器sys_cnt_1x的周期
                                                             0表示周期为2s；
                                                             1表示周期为5.12s */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_PERIOD_UNION;
#define CBBP_SYS_CNT_1X_PERIOD_sys_cnt_1x_period_START  (0)
#define CBBP_SYS_CNT_1X_PERIOD_sys_cnt_1x_period_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_RPT2_UNION
 结构说明  : SYS_CNT_1X_RPT2 寄存器结构定义。地址偏移量:0x00B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_rpt2_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_rpt2 : 11; /* bit[0-10] : sys_cnt_1x的值：
                                                                   [29:24]，sys_cnt_1x_5p12s的值；
                                                                   [21:16]，sys_cnt_1x_80ms的值；
                                                                   [10:0]，sys_cnt_1x_1p25ms的值,chip精度；
                                                                   
                                                                   软件直接读取，BBP未做锁存处理；建议软件读取2~3次，确认读取到稳定的结果再使用 */
        unsigned long  reserved_0             : 5;  /* bit[11-15]: 保留 */
        unsigned long  sys_cnt_1x_80ms_rpt2   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1             : 2;  /* bit[22-23]: 保留 */
        unsigned long  sys_cnt_1x_5p12s_rpt2  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2             : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_RPT2_UNION;
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_1p25ms_rpt2_START  (0)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_1p25ms_rpt2_END    (10)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_80ms_rpt2_START    (16)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_80ms_rpt2_END      (21)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_5p12s_rpt2_START   (24)
#define CBBP_SYS_CNT_1X_RPT2_sys_cnt_1x_5p12s_rpt2_END     (29)


/*****************************************************************************
 结构名    : CBBP_C_TIMING_MODE_1X_UNION
 结构说明  : C_TIMING_MODE_1X 寄存器结构定义。地址偏移量:0x00C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_mode_1x_reg;
    struct
    {
        unsigned long  c_timing_mode_1x : 1;  /* bit[0]   : 当前系统中是否存在1x定时。
                                                            1：表示存在1x定时； */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_C_TIMING_MODE_1X_UNION;
#define CBBP_C_TIMING_MODE_1X_c_timing_mode_1x_START  (0)
#define CBBP_C_TIMING_MODE_1X_c_timing_mode_1x_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_TIME_1X_UNION
 结构说明  : SLEEP_TIME_1X 寄存器结构定义。地址偏移量:0x00C8，初值:0x00000000，宽度:32
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
} CBBP_SLEEP_TIME_1X_UNION;
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_START  (0)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_1p25ms_END    (10)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_START    (16)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_80ms_END      (21)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_START   (24)
#define CBBP_SLEEP_TIME_1X_sleep_time_1x_5p12s_END     (29)


/*****************************************************************************
 结构名    : CBBP_SSI_TRANS_COMP_1X_UNION
 结构说明  : SSI_TRANS_COMP_1X 寄存器结构定义。地址偏移量:0x00D0，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ssi_trans_comp_1x_reg;
    struct
    {
        unsigned long  ssi_trans_comp_1x : 5;  /* bit[0-4] : 唤醒时，使用串行口传输定时信息的时间，单位chip */
        unsigned long  reserved          : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_SSI_TRANS_COMP_1X_UNION;
#define CBBP_SSI_TRANS_COMP_1X_ssi_trans_comp_1x_START  (0)
#define CBBP_SSI_TRANS_COMP_1X_ssi_trans_comp_1x_END    (4)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_GET_POS_UNION
 结构说明  : SYS_CNT_EVDO_GET_POS 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_pos_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_pos_1_4chip : 5;  /* bit[0-4]  : 更新sys_cnt_evdo的时刻：
                                                                         [28:24]，base_cnt_2s上的时刻，，取值范围0~24；
                                                                         [23:22]，base_cnt_80ms上的时刻，取值范围0~2；
                                                                         [21:5]，base_cnt_26ms上的时刻，取值范围0~32768*32-1；
                                                                         [4:0],1/4chip内计数，取值范围0~24 */
        unsigned long  sys_cnt_evdo_get_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_get_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_evdo_get_pos_2s      : 5;  /* bit[24-28]:  */
        unsigned long  reserved                     : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_POS_UNION;
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_2s_START       (24)
#define CBBP_SYS_CNT_EVDO_GET_POS_sys_cnt_evdo_get_pos_2s_END         (28)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_GET_VALUE_UNION
 结构说明  : SYS_CNT_EVDO_GET_VALUE 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_value_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_value_1_4chip : 5;  /* bit[0-4]  : sys_cnt_evdo_get_pos时刻sys_cnt_evdo的值：
                                                                           [28:24]，sys_cnt_evdo_5p12s的值；
                                                                           [31:22]，sys_cnt_evdo_80ms的值；
                                                                           [21:5]，sys_cnt_evdo_26ms的值；
                                                                           [4:0]，1/4chip内计数，0~24 */
        unsigned long  sys_cnt_evdo_get_value_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_get_value_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  sys_cnt_evdo_get_value_5p12s   : 6;  /* bit[24-29]:  */
        unsigned long  reserved                       : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_VALUE_UNION;
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_5p12s_START    (24)
#define CBBP_SYS_CNT_EVDO_GET_VALUE_sys_cnt_evdo_get_value_5p12s_END      (29)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION
 结构说明  : SYS_CNT_EVDO_80MS_POS_CFG 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_cfg_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_1_4chip_cfg : 5;  /* bit[0-4]  : 定时突变后sys_cnt_evdo  80ms帧头在base_cnt上的位置。
                                                                              Bit[4:0]：1/4chip内计数0~24
                                                                              bit[21:5]：26ms内计数0~32768*4-1
                                                                              bit[23:22]：80ms内计数0~2 */
        unsigned long  sys_cnt_evdo_80ms_pos_26ms_cfg    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_80ms_pos_80ms_cfg    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                          : 8;  /* bit[24-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_CFG_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_1_4chip_cfg_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_1_4chip_cfg_END    (4)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_26ms_cfg_START     (5)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_26ms_cfg_END       (21)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_80ms_cfg_START     (22)
#define CBBP_SYS_CNT_EVDO_80MS_POS_CFG_sys_cnt_evdo_80ms_pos_80ms_cfg_END       (23)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_GET_RDY_UNION
 结构说明  : SYS_CNT_EVDO_GET_RDY 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_get_rdy_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_get_rdy : 1;  /* bit[0]   : Sys_cnt_evdo定时获取指示。
                                                                BBP接收到此指示后，等待base_cnt上sys_cnt_evdo_get_pos时刻，将sys_cnt_evdo更新为sys_cnt_evdo_get_value。 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_GET_RDY_UNION;
#define CBBP_SYS_CNT_EVDO_GET_RDY_sys_cnt_evdo_get_rdy_START  (0)
#define CBBP_SYS_CNT_EVDO_GET_RDY_sys_cnt_evdo_get_rdy_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION
 结构说明  : SYS_EVDO_CHANGE_DIRECTION 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_evdo_change_direction_reg;
    struct
    {
        unsigned long  sys_evdo_change_direction : 1;  /* bit[0]   : 系统定时调整方向。
                                                                     0：表示往左边调整6clk；
                                                                     1：表示往右边调整6clk；
                                                                     说明：定时采用100倍时钟，因此，6clk时间为6/100chip */
        unsigned long  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_EVDO_CHANGE_DIRECTION_UNION;
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_sys_evdo_change_direction_START  (0)
#define CBBP_SYS_EVDO_CHANGE_DIRECTION_sys_evdo_change_direction_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_EVDO_CHANGE_RDY_UNION
 结构说明  : SYS_EVDO_CHANGE_RDY 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_evdo_change_rdy_reg;
    struct
    {
        unsigned long  sys_evdo_change_rdy : 1;  /* bit[0]   : 系统定时调整指示。
                                                               BBP在接收到此指示后，在最近的时隙头完成系统定时调整。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_EVDO_CHANGE_RDY_UNION;
#define CBBP_SYS_EVDO_CHANGE_RDY_sys_evdo_change_rdy_START  (0)
#define CBBP_SYS_EVDO_CHANGE_RDY_sys_evdo_change_rdy_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION
 结构说明  : SYS_CNT_EVDO_80MS_POS_RD 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_rd_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_rd : 1;  /* bit[0]   : 软件读取sys_cnt_evdo_80ms_pos的指示 */
        unsigned long  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_RD_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_sys_cnt_evdo_80ms_pos_rd_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_RD_sys_cnt_evdo_80ms_pos_rd_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_80MS_POS_UNION
 结构说明  : SYS_CNT_EVDO_80MS_POS 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_1_4chip : 5;  /* bit[0-4]  : sys_cnt_evdo  80ms帧头在base_cnt上的位置。
                                                                          Bit[4:0]：1/4chip内计数0~24
                                                                          bit[21:5]：26ms内计数0~32768*4-1
                                                                          bit[23:22]：80ms内计数0~2 */
        unsigned long  sys_cnt_evdo_80ms_pos_26ms    : 17; /* bit[5-21] :  */
        unsigned long  sys_cnt_evdo_80ms_pos_80ms    : 2;  /* bit[22-23]:  */
        unsigned long  reserved                      : 7;  /* bit[24-30]: 保留 */
        unsigned long  sys_cnt_evdo_80ms_pos_valid   : 1;  /* bit[31]   : 读取sys_cnt_evdo_80ms_pos有效指示，1有效 */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_1_4chip_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_1_4chip_END    (4)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_26ms_START     (5)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_26ms_END       (21)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_80ms_START     (22)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_80ms_END       (23)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_valid_START    (31)
#define CBBP_SYS_CNT_EVDO_80MS_POS_sys_cnt_evdo_80ms_pos_valid_END      (31)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION
 结构说明  : SYS_CNT_EVDO_80MS_POS_VALID_CLR 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_80ms_pos_valid_clr_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_80ms_pos_valid_clr : 1;  /* bit[0]   : sys_cnt_evdo_80ms_pos_valid清零信号 */
        unsigned long  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_UNION;
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_sys_cnt_evdo_80ms_pos_valid_clr_START  (0)
#define CBBP_SYS_CNT_EVDO_80MS_POS_VALID_CLR_sys_cnt_evdo_80ms_pos_valid_clr_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT_EVDO_MASK_UNION
 结构说明  : TIMING_INT_EVDO_MASK 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_evdo_mask_reg;
    struct
    {
        unsigned long  timing_int_evdo_mask : 1;  /* bit[0]   : 定时突变时，定时中断的mask。
                                                                0：表示不mask；
                                                                1：表示mask配置范围内的中断； */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT_EVDO_MASK_UNION;
#define CBBP_TIMING_INT_EVDO_MASK_timing_int_evdo_mask_START  (0)
#define CBBP_TIMING_INT_EVDO_MASK_timing_int_evdo_mask_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT_EVDO_MASK_DIS_UNION
 结构说明  : TIMING_INT_EVDO_MASK_DIS 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int_evdo_mask_dis_reg;
    struct
    {
        unsigned long  timing_int_evdo_mask_dis : 11; /* bit[0-10] : 定时突变时，定时中断的mask区间，chip为单位。 */
        unsigned long  reserved                 : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_TIMING_INT_EVDO_MASK_DIS_UNION;
#define CBBP_TIMING_INT_EVDO_MASK_DIS_timing_int_evdo_mask_dis_START  (0)
#define CBBP_TIMING_INT_EVDO_MASK_DIS_timing_int_evdo_mask_dis_END    (10)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT1_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int1_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int1_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT1_SYS_CNT_EVDO_POS_timing_int1_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT1_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_evdo_period_reg;
    struct
    {
        unsigned long  timing_int1_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT1_EVDO_PERIOD_timing_int1_evdo_period_START  (0)
#define CBBP_TIMING_INT1_EVDO_PERIOD_timing_int1_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT1_EVDO_EN_UNION
 结构说明  : TIMING_INT1_EVDO_EN 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int1_evdo_en_reg;
    struct
    {
        unsigned long  timing_int1_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT1_EVDO_EN_UNION;
#define CBBP_TIMING_INT1_EVDO_EN_timing_int1_evdo_en_START  (0)
#define CBBP_TIMING_INT1_EVDO_EN_timing_int1_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT2_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int2_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int2_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT2_SYS_CNT_EVDO_POS_timing_int2_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT2_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_evdo_period_reg;
    struct
    {
        unsigned long  timing_int2_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT2_EVDO_PERIOD_timing_int2_evdo_period_START  (0)
#define CBBP_TIMING_INT2_EVDO_PERIOD_timing_int2_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT2_EVDO_EN_UNION
 结构说明  : TIMING_INT2_EVDO_EN 寄存器结构定义。地址偏移量:0x013C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int2_evdo_en_reg;
    struct
    {
        unsigned long  timing_int2_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT2_EVDO_EN_UNION;
#define CBBP_TIMING_INT2_EVDO_EN_timing_int2_evdo_en_START  (0)
#define CBBP_TIMING_INT2_EVDO_EN_timing_int2_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT3_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int3_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int3_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT3_SYS_CNT_EVDO_POS_timing_int3_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT3_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_evdo_period_reg;
    struct
    {
        unsigned long  timing_int3_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT3_EVDO_PERIOD_timing_int3_evdo_period_START  (0)
#define CBBP_TIMING_INT3_EVDO_PERIOD_timing_int3_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT3_EVDO_EN_UNION
 结构说明  : TIMING_INT3_EVDO_EN 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int3_evdo_en_reg;
    struct
    {
        unsigned long  timing_int3_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT3_EVDO_EN_UNION;
#define CBBP_TIMING_INT3_EVDO_EN_timing_int3_evdo_en_START  (0)
#define CBBP_TIMING_INT3_EVDO_EN_timing_int3_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT4_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int4_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int4_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT4_SYS_CNT_EVDO_POS_timing_int4_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT4_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_evdo_period_reg;
    struct
    {
        unsigned long  timing_int4_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT4_EVDO_PERIOD_timing_int4_evdo_period_START  (0)
#define CBBP_TIMING_INT4_EVDO_PERIOD_timing_int4_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT4_EVDO_EN_UNION
 结构说明  : TIMING_INT4_EVDO_EN 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int4_evdo_en_reg;
    struct
    {
        unsigned long  timing_int4_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT4_EVDO_EN_UNION;
#define CBBP_TIMING_INT4_EVDO_EN_timing_int4_evdo_en_START  (0)
#define CBBP_TIMING_INT4_EVDO_EN_timing_int4_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT5_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x0158，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int5_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int5_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT5_SYS_CNT_EVDO_POS_timing_int5_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT5_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x015C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_evdo_period_reg;
    struct
    {
        unsigned long  timing_int5_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT5_EVDO_PERIOD_timing_int5_evdo_period_START  (0)
#define CBBP_TIMING_INT5_EVDO_PERIOD_timing_int5_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT5_EVDO_EN_UNION
 结构说明  : TIMING_INT5_EVDO_EN 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int5_evdo_en_reg;
    struct
    {
        unsigned long  timing_int5_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT5_EVDO_EN_UNION;
#define CBBP_TIMING_INT5_EVDO_EN_timing_int5_evdo_en_START  (0)
#define CBBP_TIMING_INT5_EVDO_EN_timing_int5_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION
 结构说明  : TIMING_INT6_SYS_CNT_EVDO_POS 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_sys_cnt_evdo_pos_reg;
    struct
    {
        unsigned long  timing_int6_sys_cnt_evdo_26ms_pos : 15; /* bit[0-14] : Int在sys_cnt_evdo上的位置：
                                                                              [17:16]，sys_cnt_evdo_80ms的值；
                                                                              [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                        : 1;  /* bit[15]   : 保留 */
        unsigned long  timing_int6_sys_cnt_evdo_80ms_pos : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_UNION;
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_26ms_pos_START  (0)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_26ms_pos_END    (14)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_80ms_pos_START  (16)
#define CBBP_TIMING_INT6_SYS_CNT_EVDO_POS_timing_int6_sys_cnt_evdo_80ms_pos_END    (17)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_EVDO_PERIOD_UNION
 结构说明  : TIMING_INT6_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x0168，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_evdo_period_reg;
    struct
    {
        unsigned long  timing_int6_evdo_period : 4;  /* bit[0-3] : Int中断周期选择：
                                                                   0：表示中断周期为64chip；
                                                                   1：表示中断周期为128chip；
                                                                   2：表示中断周期为256chip；
                                                                   3：表示中断周期为512chip；
                                                                   4：表示中断周期为1024chip；
                                                                   5：表示中断周期为2048chip；
                                                                   6：表示中断周期为4096chip；
                                                                   7：表示中断周期为8192chip；
                                                                   8：表示中断周期为16384chip；
                                                                   9：表示中断周期为32768chip；
                                                                   10：表示中断周期为80ms； */
        unsigned long  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_EVDO_PERIOD_UNION;
#define CBBP_TIMING_INT6_EVDO_PERIOD_timing_int6_evdo_period_START  (0)
#define CBBP_TIMING_INT6_EVDO_PERIOD_timing_int6_evdo_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_TIMING_INT6_EVDO_EN_UNION
 结构说明  : TIMING_INT6_EVDO_EN 寄存器结构定义。地址偏移量:0x016C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timing_int6_evdo_en_reg;
    struct
    {
        unsigned long  timing_int6_evdo_en : 1;  /* bit[0]   : 定时中断int的使能。
                                                               0：表示不产生int中断；
                                                               1：表示产生int中断； */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_TIMING_INT6_EVDO_EN_UNION;
#define CBBP_TIMING_INT6_EVDO_EN_timing_int6_evdo_en_START  (0)
#define CBBP_TIMING_INT6_EVDO_EN_timing_int6_evdo_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT1_MASK 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int1_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int1_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_evdo值的mask：
                                                                      bit0，为1表示上报中断1时刻的定时；
                                                                      bit1，为1表示上报中断2时刻的定时；
                                                                      …
                                                                      注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_sys_cnt_evdo_rpt_int1_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT1_MASK_sys_cnt_evdo_rpt_int1_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT1_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT1 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int1_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int1 : 11; /* bit[0-10] : 软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
                                                                  
                                                                  [10:0]，sys_cnt_evdo的值，64chip精度； */
        unsigned long  reserved              : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT1_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT1_sys_cnt_evdo_rpt_int1_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT1_sys_cnt_evdo_rpt_int1_END    (10)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT2_MASK 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int2_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int2_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_evdo值的mask：
                                                                      bit0，为1表示上报中断1时刻的定时；
                                                                      bit1，为1表示上报中断2时刻的定时；
                                                                      …
                                                                      注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_sys_cnt_evdo_rpt_int2_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT2_MASK_sys_cnt_evdo_rpt_int2_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT2_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT2 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int2_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int2 : 11; /* bit[0-10] : 软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
                                                                  
                                                                  [10:0]，sys_cnt_evdo的值，64chip精度； */
        unsigned long  reserved              : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT2_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT2_sys_cnt_evdo_rpt_int2_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT2_sys_cnt_evdo_rpt_int2_END    (10)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_PERIOD_UNION
 结构说明  : SYS_CNT_EVDO_PERIOD 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_period_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_period : 1;  /* bit[0]   : 1x系统计数器sys_cnt_evdo的周期
                                                               0表示周期为2s；
                                                               1表示周期为5.12s */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_PERIOD_UNION;
#define CBBP_SYS_CNT_EVDO_PERIOD_sys_cnt_evdo_period_START  (0)
#define CBBP_SYS_CNT_EVDO_PERIOD_sys_cnt_evdo_period_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT2_UNION
 结构说明  : SYS_CNT_EVDO_RPT2 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt2_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_26ms_rpt2  : 15; /* bit[0-14] : sys_cnt_evdo的值：
                                                                    [29:24]，sys_cnt_evdo_5p12s的值；
                                                                    [17:16]，sys_cnt_evdo_80ms的值；
                                                                    [14:0]，sys_cnt_evdo_26ms的值，chip精度；
                                                                    
                                                                    软件直接读取BBP结果，BBP未做锁存处理，建议软件读取2~3次，确保读取到稳定结果 */
        unsigned long  reserved_0              : 1;  /* bit[15]   : 保留 */
        unsigned long  sys_cnt_evdo_80ms_rpt2  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1              : 6;  /* bit[18-23]: 保留 */
        unsigned long  sys_cnt_evdo_5p12s_rpt2 : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2              : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT2_UNION;
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_26ms_rpt2_START   (0)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_26ms_rpt2_END     (14)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_80ms_rpt2_START   (16)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_80ms_rpt2_END     (17)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_5p12s_rpt2_START  (24)
#define CBBP_SYS_CNT_EVDO_RPT2_sys_cnt_evdo_5p12s_rpt2_END    (29)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT3_MASK 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int3_mask_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int3_mask : 6;  /* bit[0-5] : 软件配置上报中断时刻sys_cnt_evdo值的mask：
                                                                      bit0，为1表示上报中断1时刻的定时；
                                                                      bit1，为1表示上报中断2时刻的定时；
                                                                      …
                                                                      注意：同一时刻只能有1bit为1 */
        unsigned long  reserved                   : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_sys_cnt_evdo_rpt_int3_mask_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT3_MASK_sys_cnt_evdo_rpt_int3_mask_END    (5)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_RPT_INT3_UNION
 结构说明  : SYS_CNT_EVDO_RPT_INT3 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_rpt_int3_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_rpt_int3 : 11; /* bit[0-10] : 软件配置的第1个上报定时信息的中断时刻的sys_cnt_evdo的值：
                                                                  
                                                                  [10:0]，sys_cnt_evdo的值，64chip精度； */
        unsigned long  reserved              : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_RPT_INT3_UNION;
#define CBBP_SYS_CNT_EVDO_RPT_INT3_sys_cnt_evdo_rpt_int3_START  (0)
#define CBBP_SYS_CNT_EVDO_RPT_INT3_sys_cnt_evdo_rpt_int3_END    (10)


/*****************************************************************************
 结构名    : CBBP_C_TIMING_MODE_EVDO_UNION
 结构说明  : C_TIMING_MODE_EVDO 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_mode_evdo_reg;
    struct
    {
        unsigned long  c_timing_mode_evdo : 1;  /* bit[0]   : 当前系统中是否存在evdo定时。
                                                              1：表示存在evdo定时； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_C_TIMING_MODE_EVDO_UNION;
#define CBBP_C_TIMING_MODE_EVDO_c_timing_mode_evdo_START  (0)
#define CBBP_C_TIMING_MODE_EVDO_c_timing_mode_evdo_END    (0)


/*****************************************************************************
 结构名    : CBBP_C_TIMING_SEL_DBG_UNION
 结构说明  : C_TIMING_SEL_DBG 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_timing_sel_dbg_reg;
    struct
    {
        unsigned long  c_timing_sel_dbg : 1;  /* bit[0]   : C DBG模块定时选择，0表示选择1x定时，1表示选择evdo定时 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_C_TIMING_SEL_DBG_UNION;
#define CBBP_C_TIMING_SEL_DBG_c_timing_sel_dbg_START  (0)
#define CBBP_C_TIMING_SEL_DBG_c_timing_sel_dbg_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_BOTH_RD_UNION
 结构说明  : SYS_CNT_BOTH_RD 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd : 1;  /* bit[0]   : 软件同时读取1x与evdo定时的指示信号 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_UNION;
#define CBBP_SYS_CNT_BOTH_RD_sys_cnt_both_rd_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_sys_cnt_both_rd_END    (0)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_BOTH_RD_VALID_UNION
 结构说明  : SYS_CNT_BOTH_RD_VALID 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_valid_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd_valid : 1;  /* bit[0]   : 软件同时读取1x与evdo定时的有效信号，1表示上报的结果有效 */
        unsigned long  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_VALID_UNION;
#define CBBP_SYS_CNT_BOTH_RD_VALID_sys_cnt_both_rd_valid_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_VALID_sys_cnt_both_rd_valid_END    (0)


/*****************************************************************************
 结构名    : CBBP_BASE_CNT_BOTH_RPT_UNION
 结构说明  : BASE_CNT_BOTH_RPT 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      base_cnt_both_rpt_reg;
    struct
    {
        unsigned long  base_cnt_26ms_both_rpt : 15; /* bit[0-14] : base_cnt的值：
                                                                   [28:24]，base_cnt_2s上的时刻，，取值范围0~24；
                                                                   [17:16]，base_cnt_80ms上的时刻，取值范围0~2；
                                                                   [14:0]，base_cnt_26ms上的时刻，取值范围0~32767，chip精度； */
        unsigned long  reserved_0             : 1;  /* bit[15]   : 保留 */
        unsigned long  base_cnt_80ms_both_rpt : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1             : 6;  /* bit[18-23]: 保留 */
        unsigned long  base_cnt_2s_both_rpt   : 5;  /* bit[24-28]:  */
        unsigned long  reserved_2             : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_BASE_CNT_BOTH_RPT_UNION;
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_26ms_both_rpt_START  (0)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_26ms_both_rpt_END    (14)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_80ms_both_rpt_START  (16)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_80ms_both_rpt_END    (17)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_2s_both_rpt_START    (24)
#define CBBP_BASE_CNT_BOTH_RPT_base_cnt_2s_both_rpt_END      (28)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_1X_BOTH_RPT_UNION
 结构说明  : SYS_CNT_1X_BOTH_RPT 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_1x_both_rpt_reg;
    struct
    {
        unsigned long  sys_cnt_1x_1p25ms_both_rpt : 11; /* bit[0-10] : sys_cnt_1x的值：
                                                                       [29:24]，sys_cnt_1x_5p12s的值；
                                                                       [21:16]，sys_cnt_1x_80ms的值；
                                                                       [10:0]，sys_cnt_1x_1p25ms的值,chip精度； */
        unsigned long  reserved_0                 : 5;  /* bit[11-15]: 保留 */
        unsigned long  sys_cnt_1x_80ms_both_rpt   : 6;  /* bit[16-21]:  */
        unsigned long  reserved_1                 : 2;  /* bit[22-23]: 保留 */
        unsigned long  sys_cnt_1x_5p12s_both_rpt  : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2                 : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_1X_BOTH_RPT_UNION;
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_1p25ms_both_rpt_START  (0)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_1p25ms_both_rpt_END    (10)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_80ms_both_rpt_START    (16)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_80ms_both_rpt_END      (21)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_5p12s_both_rpt_START   (24)
#define CBBP_SYS_CNT_1X_BOTH_RPT_sys_cnt_1x_5p12s_both_rpt_END     (29)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION
 结构说明  : SYS_CNT_EVDO_BOTH_RPT 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_evdo_both_rpt_reg;
    struct
    {
        unsigned long  sys_cnt_evdo_26ms_both_rpt  : 15; /* bit[0-14] : sys_cnt_evdo的值：
                                                                        [29:24]，sys_cnt_evdo_5p12s的值；
                                                                        [17:16]，sys_cnt_evdo_80ms的值；
                                                                        [14:0]，sys_cnt_evdo_26ms的值，chip精度； */
        unsigned long  reserved_0                  : 1;  /* bit[15]   : 保留 */
        unsigned long  sys_cnt_evdo_80ms_both_rpt  : 2;  /* bit[16-17]:  */
        unsigned long  reserved_1                  : 6;  /* bit[18-23]: 保留 */
        unsigned long  sys_cnt_evdo_5p12s_both_rpt : 6;  /* bit[24-29]:  */
        unsigned long  reserved_2                  : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_EVDO_BOTH_RPT_UNION;
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_26ms_both_rpt_START   (0)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_26ms_both_rpt_END     (14)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_80ms_both_rpt_START   (16)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_80ms_both_rpt_END     (17)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_5p12s_both_rpt_START  (24)
#define CBBP_SYS_CNT_EVDO_BOTH_RPT_sys_cnt_evdo_5p12s_both_rpt_END    (29)


/*****************************************************************************
 结构名    : CBBP_SYS_CNT_BOTH_RD_CLR_UNION
 结构说明  : SYS_CNT_BOTH_RD_CLR 寄存器结构定义。地址偏移量:0x0220，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sys_cnt_both_rd_clr_reg;
    struct
    {
        unsigned long  sys_cnt_both_rd_clr : 1;  /* bit[0]   : 软件同时读取1x与evdo定时的有效指示信号的清零信号 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_SYS_CNT_BOTH_RD_CLR_UNION;
#define CBBP_SYS_CNT_BOTH_RD_CLR_sys_cnt_both_rd_clr_START  (0)
#define CBBP_SYS_CNT_BOTH_RD_CLR_sys_cnt_both_rd_clr_END    (0)


/*****************************************************************************
 结构名    : CBBP_SLEEP_TIME_EVDO_UNION
 结构说明  : SLEEP_TIME_EVDO 寄存器结构定义。地址偏移量:0x0228，初值:0x00000000，宽度:32
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
} CBBP_SLEEP_TIME_EVDO_UNION;
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_START   (0)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_26ms_END     (14)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_START   (16)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_80ms_END     (17)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_START  (24)
#define CBBP_SLEEP_TIME_EVDO_sleep_time_evdo_5p12s_END    (29)


/*****************************************************************************
 结构名    : CBBP_SSI_TRANS_COMP_EVDO_UNION
 结构说明  : SSI_TRANS_COMP_EVDO 寄存器结构定义。地址偏移量:0x022C，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ssi_trans_comp_evdo_reg;
    struct
    {
        unsigned long  ssi_trans_comp_evdo : 5;  /* bit[0-4] : 唤醒时，使用串行口传输定时信息的时间，单位chip */
        unsigned long  reserved            : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_SSI_TRANS_COMP_EVDO_UNION;
#define CBBP_SSI_TRANS_COMP_EVDO_ssi_trans_comp_evdo_START  (0)
#define CBBP_SSI_TRANS_COMP_EVDO_ssi_trans_comp_evdo_END    (4)


/***======================================================================***
                     (3/20) register_define_c_intr
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_ARM_INT04_EN_UNION
 结构说明  : ARM_INT04_EN 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int04_en_reg;
    struct
    {
        unsigned long  c_arm_int04_en : 1;  /* bit[0]   : 中断04使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ARM_INT04_EN_UNION;
#define CBBP_ARM_INT04_EN_c_arm_int04_en_START  (0)
#define CBBP_ARM_INT04_EN_c_arm_int04_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_ARM_OVERTIME_CFG_UNION
 结构说明  : ARM_OVERTIME_CFG 寄存器结构定义。地址偏移量:0x10，初值:0x0000001E，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_overtime_cfg_reg;
    struct
    {
        unsigned long  c_arm_int04_overtime : 7;  /* bit[0-6] : ARM_INT04超时时间。
                                                                超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE */
        unsigned long  c_arm_int04_oten     : 1;  /* bit[7]   : ARM_INT04超时使能，高电平有效。 */
        unsigned long  reserved             : 24; /* bit[8-31]: 保留 */
    } reg;
} CBBP_ARM_OVERTIME_CFG_UNION;
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_overtime_START  (0)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_overtime_END    (6)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_oten_START      (7)
#define CBBP_ARM_OVERTIME_CFG_c_arm_int04_oten_END        (7)


/*****************************************************************************
 结构名    : CBBP_INT_DELAY_CLK_UNION
 结构说明  : INT_DELAY_CLK 寄存器结构定义。地址偏移量:0x18，初值:0x0000000F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      int_delay_clk_reg;
    struct
    {
        unsigned long  c_int_dly_clk : 16; /* bit[0-15] : 防中断漏检的延迟时间，单位IMI时钟。0，禁止配置；1，表示延迟一个IMI时钟；……。必须配置为非0值。 */
        unsigned long  reserved      : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_INT_DELAY_CLK_UNION;
#define CBBP_INT_DELAY_CLK_c_int_dly_clk_START  (0)
#define CBBP_INT_DELAY_CLK_c_int_dly_clk_END    (15)


/*****************************************************************************
 结构名    : CBBP_ARM_INT4_OT_NUM_UNION
 结构说明  : ARM_INT4_OT_NUM 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_int4_ot_num_reg;
    struct
    {
        unsigned long  c_arm_int04_ot_num : 16; /* bit[0-15] : arm_int04中断超时次数。 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_ARM_INT4_OT_NUM_UNION;
#define CBBP_ARM_INT4_OT_NUM_c_arm_int04_ot_num_START  (0)
#define CBBP_ARM_INT4_OT_NUM_c_arm_int04_ot_num_END    (15)


/*****************************************************************************
 结构名    : CBBP_OVERTIME_BASE_UNION
 结构说明  : OVERTIME_BASE 寄存器结构定义。地址偏移量:0x20，初值:0x00030D40，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      overtime_base_reg;
    struct
    {
        unsigned long  c_overtime_base : 18; /* bit[0-17] : 1ms内IMI时钟个数。软件根据当前IMI时钟频率配置，默认值为IMI时钟频率为200MHz时的1ms内时钟个数。 */
        unsigned long  reserved        : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_OVERTIME_BASE_UNION;
#define CBBP_OVERTIME_BASE_c_overtime_base_START  (0)
#define CBBP_OVERTIME_BASE_c_overtime_base_END    (17)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT03_STA_UNION
 结构说明  : BBE16_INT03_STA 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_sta_reg;
    struct
    {
        unsigned long  bbe16_int03_sta : 7;  /* bit[0-6] : 多径搜索/小区测量中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
                                                           bit[0] 多径搜索/小区测量单元0中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)       
                                                           bit[1] 多径搜索/小区测量单元1中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
                                                           bit[2] 多径搜索/小区测量单元2中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
                                                           bit[3] 多径搜索/小区测量单元3中断，上报周期为768chip(1x)/1024chip(evdo)/4096(evdo)；       
                                                           bit[4] 小区搜索和多径搜索数据存储结束中断；
                                                           bit[5] 小区和多径搜索合并中断0
                                                           bit[6] 小区和多径搜索合并中断1
                                                           如果配置了中断合并，如单元0和单元1合并上报，则只上报合并中断，不单独上报单元0，1的中断。 */
        unsigned long  reserved        : 25; /* bit[7-31]: 保留 */
    } reg;
} CBBP_BBE16_INT03_STA_UNION;
#define CBBP_BBE16_INT03_STA_bbe16_int03_sta_START  (0)
#define CBBP_BBE16_INT03_STA_bbe16_int03_sta_END    (6)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT03_MASK_UNION
 结构说明  : BBE16_INT03_MASK 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_mask_reg;
    struct
    {
        unsigned long  bbe16_int03_mask : 7;  /* bit[0-6] : 多径搜索/小区测量中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved         : 25; /* bit[7-31]: 保留 */
    } reg;
} CBBP_BBE16_INT03_MASK_UNION;
#define CBBP_BBE16_INT03_MASK_bbe16_int03_mask_START  (0)
#define CBBP_BBE16_INT03_MASK_bbe16_int03_mask_END    (6)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT03_EN_UNION
 结构说明  : BBE16_INT03_EN 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_en_reg;
    struct
    {
        unsigned long  bbe16_int03_en : 1;  /* bit[0]   : 中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BBE16_INT03_EN_UNION;
#define CBBP_BBE16_INT03_EN_bbe16_int03_en_START  (0)
#define CBBP_BBE16_INT03_EN_bbe16_int03_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT03_CLR_UNION
 结构说明  : BBE16_INT03_CLR 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int03_clr_reg;
    struct
    {
        unsigned long  bbe16_int03_clr : 7;  /* bit[0-6] : 多径搜索/小区测量中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved        : 25; /* bit[7-31]: 保留 */
    } reg;
} CBBP_BBE16_INT03_CLR_UNION;
#define CBBP_BBE16_INT03_CLR_bbe16_int03_clr_START  (0)
#define CBBP_BBE16_INT03_CLR_bbe16_int03_clr_END    (6)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT04_EN_UNION
 结构说明  : BBE16_INT04_EN 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int04_en_reg;
    struct
    {
        unsigned long  bbe16_int04_en : 1;  /* bit[0]   : 中断04使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BBE16_INT04_EN_UNION;
#define CBBP_BBE16_INT04_EN_bbe16_int04_en_START  (0)
#define CBBP_BBE16_INT04_EN_bbe16_int04_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT05_STA_UNION
 结构说明  : BBE16_INT05_STA 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_sta_reg;
    struct
    {
        unsigned long  bbe16_int05_sta : 5;  /* bit[0-4] : 译码/编码中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
                                                           bit[0]下行译码完成中断；
                                                           bit[1] Reserve for timing       
                                                           bit[2] Reserve for timing
                                                           bit[3] Reserve for timing
                                                           bit[4]编码上报中断，通知软件读取编码数据；  */
        unsigned long  reserved        : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT05_STA_UNION;
#define CBBP_BBE16_INT05_STA_bbe16_int05_sta_START  (0)
#define CBBP_BBE16_INT05_STA_bbe16_int05_sta_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT05_MASK_UNION
 结构说明  : BBE16_INT05_MASK 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_mask_reg;
    struct
    {
        unsigned long  bbe16_int05_mask : 5;  /* bit[0-4] : 译码/编码中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved         : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT05_MASK_UNION;
#define CBBP_BBE16_INT05_MASK_bbe16_int05_mask_START  (0)
#define CBBP_BBE16_INT05_MASK_bbe16_int05_mask_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT05_EN_UNION
 结构说明  : BBE16_INT05_EN 寄存器结构定义。地址偏移量:0x58，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_en_reg;
    struct
    {
        unsigned long  bbe16_int05_en : 1;  /* bit[0]   : 中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BBE16_INT05_EN_UNION;
#define CBBP_BBE16_INT05_EN_bbe16_int05_en_START  (0)
#define CBBP_BBE16_INT05_EN_bbe16_int05_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT05_CLR_UNION
 结构说明  : BBE16_INT05_CLR 寄存器结构定义。地址偏移量:0x5C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int05_clr_reg;
    struct
    {
        unsigned long  bbe16_int05_clr : 5;  /* bit[0-4] : 译码/编码中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved        : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT05_CLR_UNION;
#define CBBP_BBE16_INT05_CLR_bbe16_int05_clr_START  (0)
#define CBBP_BBE16_INT05_CLR_bbe16_int05_clr_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT06_STA_UNION
 结构说明  : BBE16_INT06_STA 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_sta_reg;
    struct
    {
        unsigned long  bbe16_int06_sta : 5;  /* bit[0-4] : 射频上报/数据搬移中断状态寄存器。1，表示相应比特位置有中断；0，表示相应比特位置没有中断。
                                                           bit[0]每个时隙产生一次，DSP收到此中断后读取PD结果再计算；
                                                           bit[1]下行天线1前端数据搬运出错上报中断；   
                                                           bit[2]下行天线2前端数据搬运出错上报中断；     
                                                           bit[3]上行前端数据搬运出错上报中断； 
                                                           bit[4]上行前端数据BBPMST搬运完成中断。 */
        unsigned long  reserved        : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT06_STA_UNION;
#define CBBP_BBE16_INT06_STA_bbe16_int06_sta_START  (0)
#define CBBP_BBE16_INT06_STA_bbe16_int06_sta_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT06_MASK_UNION
 结构说明  : BBE16_INT06_MASK 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_mask_reg;
    struct
    {
        unsigned long  bbe16_int06_mask : 5;  /* bit[0-4] : 射频上报/数据搬移中断屏蔽寄存器。1，表示屏蔽相应比特位置的中断；0，表示不屏蔽相应比特位置的中断。 */
        unsigned long  reserved         : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT06_MASK_UNION;
#define CBBP_BBE16_INT06_MASK_bbe16_int06_mask_START  (0)
#define CBBP_BBE16_INT06_MASK_bbe16_int06_mask_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT06_EN_UNION
 结构说明  : BBE16_INT06_EN 寄存器结构定义。地址偏移量:0x68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_en_reg;
    struct
    {
        unsigned long  bbe16_int06_en : 1;  /* bit[0]   : 中断使能寄存器。1，表示使能中断；0，表示不使能中断。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BBE16_INT06_EN_UNION;
#define CBBP_BBE16_INT06_EN_bbe16_int06_en_START  (0)
#define CBBP_BBE16_INT06_EN_bbe16_int06_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT06_CLR_UNION
 结构说明  : BBE16_INT06_CLR 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int06_clr_reg;
    struct
    {
        unsigned long  bbe16_int06_clr : 5;  /* bit[0-4] : 射频上报/数据搬移中断清除寄存器。1，表示清除相应比特位置中断；0，表示不清除相应比特位置的中断。 */
        unsigned long  reserved        : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_BBE16_INT06_CLR_UNION;
#define CBBP_BBE16_INT06_CLR_bbe16_int06_clr_START  (0)
#define CBBP_BBE16_INT06_CLR_bbe16_int06_clr_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_OVERTIME_CFG_UNION
 结构说明  : BBE16_OVERTIME_CFG 寄存器结构定义。地址偏移量:0x70，初值:0x1E1E1E1E，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_overtime_cfg_reg;
    struct
    {
        unsigned long  bbe16_int03_overtime : 7;  /* bit[0-6]  : bbe16_INT03超时时间。
                                                                 超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE */
        unsigned long  bbe16_int03_oten     : 1;  /* bit[7]    : bbe16_INT03超时使能，高电平有效。 */
        unsigned long  bbe16_int04_overtime : 7;  /* bit[8-14] : bbe16_INT04超时时间。
                                                                 超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE */
        unsigned long  bbe16_int04_oten     : 1;  /* bit[15]   : bbe16_INT04超时使能，高电平有效。 */
        unsigned long  bbe16_int05_overtime : 7;  /* bit[16-22]: bbe16_INT05超时时间。
                                                                 超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE */
        unsigned long  bbe16_int05_oten     : 1;  /* bit[23]   : bbe16_INT05超时使能，高电平有效。 */
        unsigned long  bbe16_int06_overtime : 7;  /* bit[24-30]: BBE16_INT06超时时间。
                                                                 超时时间单位取决于OVERTIME_BASE，软件应首先配置OVERTIME_BASE */
        unsigned long  bbe16_int06_oten     : 1;  /* bit[31]   : BBE16_INT06超时使能，高电平有效。 */
    } reg;
} CBBP_BBE16_OVERTIME_CFG_UNION;
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_overtime_START  (0)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_overtime_END    (6)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_oten_START      (7)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int03_oten_END        (7)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_overtime_START  (8)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_overtime_END    (14)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_oten_START      (15)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int04_oten_END        (15)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_overtime_START  (16)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_overtime_END    (22)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_oten_START      (23)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int05_oten_END        (23)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_overtime_START  (24)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_overtime_END    (30)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_oten_START      (31)
#define CBBP_BBE16_OVERTIME_CFG_bbe16_int06_oten_END        (31)


/*****************************************************************************
 结构名    : CBBP_INT_OVERTIME_FLAG_UNION
 结构说明  : INT_OVERTIME_FLAG 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      int_overtime_flag_reg;
    struct
    {
        unsigned long  int_overtime_set : 5;  /* bit[0-4] : 中断超时指示，高电平有效。
                                                            bit[0]：bbe16_INT03。
                                                            bit[1]：bbe16_INT04。
                                                            bit[2]：bbe16_INT05。
                                                            bit[3]：bbe16_INT06。
                                                            bit[4]：arm_INT04。 */
        unsigned long  reserved         : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_INT_OVERTIME_FLAG_UNION;
#define CBBP_INT_OVERTIME_FLAG_int_overtime_set_START  (0)
#define CBBP_INT_OVERTIME_FLAG_int_overtime_set_END    (4)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT34_OT_NUM_UNION
 结构说明  : BBE16_INT34_OT_NUM 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int34_ot_num_reg;
    struct
    {
        unsigned long  bbe16_int03_ot_num : 16; /* bit[0-15] : bbe16_int03中断超时次数。 */
        unsigned long  bbe16_int04_ot_num : 16; /* bit[16-31]: BBE16_int04中断超时次数。 */
    } reg;
} CBBP_BBE16_INT34_OT_NUM_UNION;
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int03_ot_num_START  (0)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int03_ot_num_END    (15)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int04_ot_num_START  (16)
#define CBBP_BBE16_INT34_OT_NUM_bbe16_int04_ot_num_END    (31)


/*****************************************************************************
 结构名    : CBBP_BBE16_INT56_OT_NUM_UNION
 结构说明  : BBE16_INT56_OT_NUM 寄存器结构定义。地址偏移量:0x7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bbe16_int56_ot_num_reg;
    struct
    {
        unsigned long  bbe16_int05_ot_num : 16; /* bit[0-15] : bbe16_int05中断超时次数。 */
        unsigned long  bbe16_int06_ot_num : 16; /* bit[16-31]: BBE16_int06中断超时次数。 */
    } reg;
} CBBP_BBE16_INT56_OT_NUM_UNION;
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int05_ot_num_START  (0)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int05_ot_num_END    (15)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int06_ot_num_START  (16)
#define CBBP_BBE16_INT56_OT_NUM_bbe16_int06_ot_num_END    (31)


/*****************************************************************************
 结构名    : CBBP_CS_MPS_GRP_INT_MODE_UNION
 结构说明  : CS_MPS_GRP_INT_MODE 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cs_mps_grp_int_mode_reg;
    struct
    {
        unsigned long  cs_mps_grp0_int_mode : 5;  /* bit[0-4]  : 小区和多径搜索Group0中断合并上报模式，[3:0]表示对应单元3~0中断，bit[4]表示存储单元中断；
                                                                 对应bit配置为1表示对应单元中断在Group1合并上报。合并中断的配置说明，见接口说明书的《中断》章节 */
        unsigned long  cs_mps_grp1_int_mode : 5;  /* bit[5-9]  : 小区和多径搜索Group1中断合并上报模式，[8:5]表示对应单元3~0中断，bit[9]表示存储单元中断；
                                                                 对应bit配置为1表示对应单元中断在Group1合并上报。合并中断的配置说明，见接口说明书的《中断》章节 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_CS_MPS_GRP_INT_MODE_UNION;
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp0_int_mode_START  (0)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp0_int_mode_END    (4)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp1_int_mode_START  (5)
#define CBBP_CS_MPS_GRP_INT_MODE_cs_mps_grp1_int_mode_END    (9)


/***======================================================================***
                     (4/20) register_define_c_cs_mps_store
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_DATA_STORE_LENGTH_UNION
 结构说明  : DATA_STORE_LENGTH 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_length_reg;
    struct
    {
        unsigned long  data_store_length : 13; /* bit[0-12] : 存储数据长度，chip单位，
                                                              按照目前算法：
                                                              1x小区搜索时，存储长度2048chip
                                                              Evdo小区搜索时，存储长度64x32=2048chip或64x16=1024chip或64x8=512chip
                                                              1x小区测量时，64x12（相干）x4（非相干）=3072chip；
                                                              Evdo小区测量时，96x4（相干）x8（非相干）=3072chip。 */
        unsigned long  reserved          : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_LENGTH_UNION;
#define CBBP_DATA_STORE_LENGTH_data_store_length_START  (0)
#define CBBP_DATA_STORE_LENGTH_data_store_length_END    (12)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_MODE_UNION
 结构说明  : DATA_STORE_MODE 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_mode_reg;
    struct
    {
        unsigned long  data_store_mode : 3;  /* bit[0-2] : 数据存储方式：
                                                           0表示连续存储，
                                                           1表示每1024chip缓存64chip，
                                                           2表示每1024chip缓存96chip，
                                                           3表示每1024chip缓存128chip，
                                                           4表示每1024chip缓存256chip，
                                                           5表示每1024chip缓存512chip， */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_MODE_UNION;
#define CBBP_DATA_STORE_MODE_data_store_mode_START  (0)
#define CBBP_DATA_STORE_MODE_data_store_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_POS_UNION
 结构说明  : DATA_STORE_POS 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_pos_reg;
    struct
    {
        unsigned long  data_store_pos : 16; /* bit[0-15] : 存储数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度 */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_POS_UNION;
#define CBBP_DATA_STORE_POS_data_store_pos_START  (0)
#define CBBP_DATA_STORE_POS_data_store_pos_END    (15)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_ANT_UNION
 结构说明  : DATA_STORE_ANT 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_ant_reg;
    struct
    {
        unsigned long  data_store_ant : 1;  /* bit[0]   : 存储数据天线选择：
                                                          为0表示存储接收天线1的数据
                                                          为1表示存储接收天线2的数据 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_ANT_UNION;
#define CBBP_DATA_STORE_ANT_data_store_ant_START  (0)
#define CBBP_DATA_STORE_ANT_data_store_ant_END    (0)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_POS_SEL_UNION
 结构说明  : DATA_STORE_POS_SEL 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_pos_sel_reg;
    struct
    {
        unsigned long  data_store_pos_sel : 1;  /* bit[0]   : 存储数据起始位置选择信号，
                                                              0表示可以就近开始存储数据；
                                                              1表示必须等到 Data_store_pos，才能开始存储数据； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_POS_SEL_UNION;
#define CBBP_DATA_STORE_POS_SEL_data_store_pos_sel_START  (0)
#define CBBP_DATA_STORE_POS_SEL_data_store_pos_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_CK_BYPASS_UNION
 结构说明  : DATA_STORE_CK_BYPASS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_ck_bypass_reg;
    struct
    {
        unsigned long  data_store_ck_bypass : 1;  /* bit[0]   : 自动时钟门控bypass，1表示时钟常开 */
        unsigned long  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_CK_BYPASS_UNION;
#define CBBP_DATA_STORE_CK_BYPASS_data_store_ck_bypass_START  (0)
#define CBBP_DATA_STORE_CK_BYPASS_data_store_ck_bypass_END    (0)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_EN_UNION
 结构说明  : DATA_STORE_EN 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_en_reg;
    struct
    {
        unsigned long  data_store_en : 1;  /* bit[0]   : 数据存储模块使能，作为本模块的总使能，并控制本模块的时钟开关
                                                         在 Data_store_start之前配置为1，在接收到中断后，配置为0 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_EN_UNION;
#define CBBP_DATA_STORE_EN_data_store_en_START  (0)
#define CBBP_DATA_STORE_EN_data_store_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_DATA_STORE_START_UNION
 结构说明  : DATA_STORE_START 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      data_store_start_reg;
    struct
    {
        unsigned long  data_store_start : 1;  /* bit[0]   : 存储数据启动脉冲信号 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DATA_STORE_START_UNION;
#define CBBP_DATA_STORE_START_data_store_start_START  (0)
#define CBBP_DATA_STORE_START_data_store_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_DSP_RD_DATA_START_UNION
 结构说明  : DSP_RD_DATA_START 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_rd_data_start_reg;
    struct
    {
        unsigned long  dsp_rd_data_start : 1;  /* bit[0]   : FPGA专用
                                                             物理层读取缓存数据的开始信号，BBP检测到此信号后，将读取地址恢复到第一个数据的位置 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DSP_RD_DATA_START_UNION;
#define CBBP_DSP_RD_DATA_START_dsp_rd_data_start_START  (0)
#define CBBP_DSP_RD_DATA_START_dsp_rd_data_start_END    (0)


/***======================================================================***
                     (5/20) register_define_c_cs_mps_unit0
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_UNIT0_CLK_MODE_UNION
 结构说明  : UNIT0_CLK_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_clk_mode_reg;
    struct
    {
        unsigned long  unit0_clk_mode : 1;  /* bit[0]   : 搜索单元时钟频率选择
                                                          0：表示搜索单元128倍时钟；
                                                          1：表示搜索单元64倍时钟
                                                          默认不需要软件配置 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_CLK_MODE_UNION;
#define CBBP_UNIT0_CLK_MODE_unit0_clk_mode_START  (0)
#define CBBP_UNIT0_CLK_MODE_unit0_clk_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_CORR_RPT_PERIOD_UNION
 结构说明  : UNIT0_CORR_RPT_PERIOD 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit0_corr_rpt_period : 4;  /* bit[0-3] : 使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
                                                                 此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
                                                                 对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
                                                                 对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
                                                                 对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT0_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT0_CORR_RPT_PERIOD_unit0_corr_rpt_period_START  (0)
#define CBBP_UNIT0_CORR_RPT_PERIOD_unit0_corr_rpt_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT0_CORR_WAIT_CHIP_UNION
 结构说明  : UNIT0_CORR_WAIT_CHIP 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit0_corr_wait_chip : 11; /* bit[0-10] : 使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
                                                                 此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
                                                                 仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置 */
        unsigned long  reserved             : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_UNIT0_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT0_CORR_WAIT_CHIP_unit0_corr_wait_chip_START  (0)
#define CBBP_UNIT0_CORR_WAIT_CHIP_unit0_corr_wait_chip_END    (10)


/*****************************************************************************
 结构名    : CBBP_UNIT0_ANT_SEL_UNION
 结构说明  : UNIT0_ANT_SEL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_ant_sel_reg;
    struct
    {
        unsigned long  unit0_ant_sel : 1;  /* bit[0]   : 输入数据天线选择
                                                         0：表示输入接收天线1的数据；
                                                         1：表示输入接收天线2的数据； */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_ANT_SEL_UNION;
#define CBBP_UNIT0_ANT_SEL_unit0_ant_sel_START  (0)
#define CBBP_UNIT0_ANT_SEL_unit0_ant_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_MODE_UNION
 结构说明  : UNIT0_MODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_mode_reg;
    struct
    {
        unsigned long  unit0_mode : 2;  /* bit[0-1] : 模式选择。
                                                      0：表示初始小区搜索
                                                      1：表示pn列表小区搜索
                                                      2：表示多径搜索、小区测量（仅完成相干累加）
                                                      3：表示小区测量（完成相干累加与非相干累加） */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_UNIT0_MODE_UNION;
#define CBBP_UNIT0_MODE_unit0_mode_START  (0)
#define CBBP_UNIT0_MODE_unit0_mode_END    (1)


/*****************************************************************************
 结构名    : CBBP_UNIT0_WIN_UNION
 结构说明  : UNIT0_WIN 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_win_reg;
    struct
    {
        unsigned long  unit0_win : 10; /* bit[0-9]  : 搜索窗宽，单位为64chip，配置范围为1~512。
                                                      
                                                      初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
                                                      PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
                                                      多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
                                                      小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT0_WIN_UNION;
#define CBBP_UNIT0_WIN_unit0_win_START  (0)
#define CBBP_UNIT0_WIN_unit0_win_END    (9)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_SEL_UNION
 结构说明  : UNIT0_DATA_SEL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_sel_reg;
    struct
    {
        unsigned long  unit0_data_sel : 1;  /* bit[0]   : 输入数据选择。
                                                          0：表示使用实时数据；
                                                          1：表示使用缓存的数据 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_SEL_UNION;
#define CBBP_UNIT0_DATA_SEL_unit0_data_sel_START  (0)
#define CBBP_UNIT0_DATA_SEL_unit0_data_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_STORE_MODE_UNION
 结构说明  : UNIT0_DATA_STORE_MODE 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_store_mode_reg;
    struct
    {
        unsigned long  unit0_data_store_mode : 3;  /* bit[0-2] : 缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
                                                                 0表示连续存储，
                                                                 1表示每1024chip存储64chip，
                                                                 2表示每1024chip存储96chip，
                                                                 3表示每1024chip存储128chip，
                                                                 4表示每1024chip存储256chip，
                                                                 5表示每1024chip存储512chip， */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_STORE_MODE_UNION;
#define CBBP_UNIT0_DATA_STORE_MODE_unit0_data_store_mode_START  (0)
#define CBBP_UNIT0_DATA_STORE_MODE_unit0_data_store_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_POS_UNION
 结构说明  : UNIT0_DATA_POS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_pos_reg;
    struct
    {
        unsigned long  unit0_data_pos : 16; /* bit[0-15] : 使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度 */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_POS_UNION;
#define CBBP_UNIT0_DATA_POS_unit0_data_pos_START  (0)
#define CBBP_UNIT0_DATA_POS_unit0_data_pos_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_POS_SEL_UNION
 结构说明  : UNIT0_DATA_POS_SEL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_pos_sel_reg;
    struct
    {
        unsigned long  unit0_data_pos_sel : 1;  /* bit[0]   : 使用实时数据时有效。
                                                              0：表示可以就近开始搜索；
                                                              1：必须等待Unit0_data_pos时，才能开始搜索； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_POS_SEL_UNION;
#define CBBP_UNIT0_DATA_POS_SEL_unit0_data_pos_sel_START  (0)
#define CBBP_UNIT0_DATA_POS_SEL_unit0_data_pos_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_MODE_UNION
 结构说明  : UNIT0_DATA_MODE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_mode_reg;
    struct
    {
        unsigned long  unit0_data_mode : 3;  /* bit[0-2] : 输入数据取数方式：
                                                           0表示连续取数，
                                                           1表示每1024chip取数64chip，
                                                           2表示每1024chip取数96chip，
                                                           3表示每1024chip取数128chip，
                                                           4表示每1024chip取数256chip，
                                                           5表示每1024chip存储512chip，
                                                           
                                                           说明：
                                                           对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
                                                           对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。 */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_MODE_UNION;
#define CBBP_UNIT0_DATA_MODE_unit0_data_mode_START  (0)
#define CBBP_UNIT0_DATA_MODE_unit0_data_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN_NUM_UNION
 结构说明  : UNIT0_PN_NUM 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn_num_reg;
    struct
    {
        unsigned long  unit0_pn_num : 5;  /* bit[0-4] : Pn列表小区搜索时，pn offset个数，支持1~16个 */
        unsigned long  reserved     : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN_NUM_UNION;
#define CBBP_UNIT0_PN_NUM_unit0_pn_num_START  (0)
#define CBBP_UNIT0_PN_NUM_unit0_pn_num_END    (4)


/*****************************************************************************
 结构名    : CBBP_UNIT0_CORR_LENGTH_UNION
 结构说明  : UNIT0_CORR_LENGTH 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_corr_length_reg;
    struct
    {
        unsigned long  unit0_corr_length : 4;  /* bit[0-3] : 相干长度
                                                             0：32
                                                             1：64
                                                             2：96
                                                             3：128
                                                             4：256
                                                             5：96*4=384
                                                             6：64*12=768
                                                             7：512
                                                             算法推荐：
                                                             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
                                                             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
                                                             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
                                                             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。 */
        unsigned long  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT0_CORR_LENGTH_UNION;
#define CBBP_UNIT0_CORR_LENGTH_unit0_corr_length_START  (0)
#define CBBP_UNIT0_CORR_LENGTH_unit0_corr_length_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT0_NCORR_LENGTH_UNION
 结构说明  : UNIT0_NCORR_LENGTH 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_ncorr_length_reg;
    struct
    {
        unsigned long  unit0_ncorr_lenth : 3;  /* bit[0-2] : 非相干长度
                                                             0：1
                                                             1：2
                                                             2：3
                                                             3：4
                                                             4：8
                                                             5：16
                                                             6：32
                                                             7：96 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT0_NCORR_LENGTH_UNION;
#define CBBP_UNIT0_NCORR_LENGTH_unit0_ncorr_lenth_START  (0)
#define CBBP_UNIT0_NCORR_LENGTH_unit0_ncorr_lenth_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT0_ABS_TH_UNION
 结构说明  : UNIT0_ABS_TH 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_abs_th_reg;
    struct
    {
        unsigned long  unit0_abs_th : 16; /* bit[0-15] : 绝对噪声门限 */
        unsigned long  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT0_ABS_TH_UNION;
#define CBBP_UNIT0_ABS_TH_unit0_abs_th_START  (0)
#define CBBP_UNIT0_ABS_TH_unit0_abs_th_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT0_EN_UNION
 结构说明  : UNIT0_EN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_en_reg;
    struct
    {
        unsigned long  unit0_en : 1;  /* bit[0]   : 搜索单元使能信号 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_EN_UNION;
#define CBBP_UNIT0_EN_unit0_en_START  (0)
#define CBBP_UNIT0_EN_unit0_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_NOISE_ENERGY_UNION
 结构说明  : UNIT0_NOISE_ENERGY 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_noise_energy_reg;
    struct
    {
        unsigned long  unit0_noise_energy : 16; /* bit[0-15] : 单元0本次小区搜索上报的噪声门限 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT0_NOISE_ENERGY_UNION;
#define CBBP_UNIT0_NOISE_ENERGY_unit0_noise_energy_START  (0)
#define CBBP_UNIT0_NOISE_ENERGY_unit0_noise_energy_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT0_FRAME_SHIFT_UNION
 结构说明  : UNIT0_FRAME_SHIFT 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_frame_shift_reg;
    struct
    {
        unsigned long  unit0_frame_shft : 1;  /* bit[0]   : 单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
                                                            0：表示上报搜索窗与配置搜索窗完全一致
                                                            1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_FRAME_SHIFT_UNION;
#define CBBP_UNIT0_FRAME_SHIFT_unit0_frame_shft_START  (0)
#define CBBP_UNIT0_FRAME_SHIFT_unit0_frame_shft_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN0_FRAME_POS_UNION
 结构说明  : UNIT0_PN0_FRAME_POS 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn0_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
                                                                如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN0_FRAME_POS_UNION;
#define CBBP_UNIT0_PN0_FRAME_POS_unit0_pn0_frame_pos_START  (0)
#define CBBP_UNIT0_PN0_FRAME_POS_unit0_pn0_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN1_FRAME_POS_UNION
 结构说明  : UNIT0_PN1_FRAME_POS 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn1_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN1_FRAME_POS_UNION;
#define CBBP_UNIT0_PN1_FRAME_POS_unit0_pn1_frame_pos_START  (0)
#define CBBP_UNIT0_PN1_FRAME_POS_unit0_pn1_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN2_FRAME_POS_UNION
 结构说明  : UNIT0_PN2_FRAME_POS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn2_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN2_FRAME_POS_UNION;
#define CBBP_UNIT0_PN2_FRAME_POS_unit0_pn2_frame_pos_START  (0)
#define CBBP_UNIT0_PN2_FRAME_POS_unit0_pn2_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN3_FRAME_POS_UNION
 结构说明  : UNIT0_PN3_FRAME_POS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn3_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN3_FRAME_POS_UNION;
#define CBBP_UNIT0_PN3_FRAME_POS_unit0_pn3_frame_pos_START  (0)
#define CBBP_UNIT0_PN3_FRAME_POS_unit0_pn3_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN4_FRAME_POS_UNION
 结构说明  : UNIT0_PN4_FRAME_POS 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn4_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN4_FRAME_POS_UNION;
#define CBBP_UNIT0_PN4_FRAME_POS_unit0_pn4_frame_pos_START  (0)
#define CBBP_UNIT0_PN4_FRAME_POS_unit0_pn4_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN5_FRAME_POS_UNION
 结构说明  : UNIT0_PN5_FRAME_POS 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn5_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN5_FRAME_POS_UNION;
#define CBBP_UNIT0_PN5_FRAME_POS_unit0_pn5_frame_pos_START  (0)
#define CBBP_UNIT0_PN5_FRAME_POS_unit0_pn5_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN6_FRAME_POS_UNION
 结构说明  : UNIT0_PN6_FRAME_POS 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn6_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN6_FRAME_POS_UNION;
#define CBBP_UNIT0_PN6_FRAME_POS_unit0_pn6_frame_pos_START  (0)
#define CBBP_UNIT0_PN6_FRAME_POS_unit0_pn6_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN7_FRAME_POS_UNION
 结构说明  : UNIT0_PN7_FRAME_POS 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn7_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN7_FRAME_POS_UNION;
#define CBBP_UNIT0_PN7_FRAME_POS_unit0_pn7_frame_pos_START  (0)
#define CBBP_UNIT0_PN7_FRAME_POS_unit0_pn7_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN8_FRAME_POS_UNION
 结构说明  : UNIT0_PN8_FRAME_POS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn8_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN8_FRAME_POS_UNION;
#define CBBP_UNIT0_PN8_FRAME_POS_unit0_pn8_frame_pos_START  (0)
#define CBBP_UNIT0_PN8_FRAME_POS_unit0_pn8_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN9_FRAME_POS_UNION
 结构说明  : UNIT0_PN9_FRAME_POS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn9_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN9_FRAME_POS_UNION;
#define CBBP_UNIT0_PN9_FRAME_POS_unit0_pn9_frame_pos_START  (0)
#define CBBP_UNIT0_PN9_FRAME_POS_unit0_pn9_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN10_FRAME_POS_UNION
 结构说明  : UNIT0_PN10_FRAME_POS 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn10_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN10_FRAME_POS_UNION;
#define CBBP_UNIT0_PN10_FRAME_POS_unit0_pn10_frame_pos_START  (0)
#define CBBP_UNIT0_PN10_FRAME_POS_unit0_pn10_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN11_FRAME_POS_UNION
 结构说明  : UNIT0_PN11_FRAME_POS 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn11_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN11_FRAME_POS_UNION;
#define CBBP_UNIT0_PN11_FRAME_POS_unit0_pn11_frame_pos_START  (0)
#define CBBP_UNIT0_PN11_FRAME_POS_unit0_pn11_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN12_FRAME_POS_UNION
 结构说明  : UNIT0_PN12_FRAME_POS 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn12_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN12_FRAME_POS_UNION;
#define CBBP_UNIT0_PN12_FRAME_POS_unit0_pn12_frame_pos_START  (0)
#define CBBP_UNIT0_PN12_FRAME_POS_unit0_pn12_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN13_FRAME_POS_UNION
 结构说明  : UNIT0_PN13_FRAME_POS 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn13_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN13_FRAME_POS_UNION;
#define CBBP_UNIT0_PN13_FRAME_POS_unit0_pn13_frame_pos_START  (0)
#define CBBP_UNIT0_PN13_FRAME_POS_unit0_pn13_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN14_FRAME_POS_UNION
 结构说明  : UNIT0_PN14_FRAME_POS 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn14_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN14_FRAME_POS_UNION;
#define CBBP_UNIT0_PN14_FRAME_POS_unit0_pn14_frame_pos_START  (0)
#define CBBP_UNIT0_PN14_FRAME_POS_unit0_pn14_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_PN15_FRAME_POS_UNION
 结构说明  : UNIT0_PN15_FRAME_POS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit0_pn15_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT0_PN15_FRAME_POS_UNION;
#define CBBP_UNIT0_PN15_FRAME_POS_unit0_pn15_frame_pos_START  (0)
#define CBBP_UNIT0_PN15_FRAME_POS_unit0_pn15_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT0_CS_1X_MODE_UNION
 结构说明  : UNIT0_CS_1X_MODE 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit0_cs_1x_mode : 1;  /* bit[0]   : 搜索模式选择
                                                            0表示1x搜索
                                                            1表示evdo搜索 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT0_CS_1X_MODE_UNION;
#define CBBP_UNIT0_CS_1X_MODE_unit0_cs_1x_mode_START  (0)
#define CBBP_UNIT0_CS_1X_MODE_unit0_cs_1x_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT0_SRCH_CK_BYPASS_UNION
 结构说明  : UNIT0_SRCH_CK_BYPASS 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit0_ctrl_pass   : 1;  /* bit[0]   : 搜索单元控制部分时钟门控bypass
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit0_sort_bypass : 1;  /* bit[1]   : 搜索单元排队模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit0_rpt_bypass  : 1;  /* bit[2]   : 搜索单元上报模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT0_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_ctrl_pass_START    (0)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_ctrl_pass_END      (0)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_sort_bypass_START  (1)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_sort_bypass_END    (1)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_rpt_bypass_START   (2)
#define CBBP_UNIT0_SRCH_CK_BYPASS_unit0_rpt_bypass_END     (2)


/*****************************************************************************
 结构名    : CBBP_UNIT0_NOISE_ALPHER_COEF_UNION
 结构说明  : UNIT0_NOISE_ALPHER_COEF 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit0_noise_alpher_coef : 3;  /* bit[0-2] : 噪声门限滤波系数：
                                                                   0：1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT0_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT0_NOISE_ALPHER_COEF_unit0_noise_alpher_coef_START  (0)
#define CBBP_UNIT0_NOISE_ALPHER_COEF_unit0_noise_alpher_coef_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT0_DATA_STORE_OFF_UNION
 结构说明  : UNIT0_DATA_STORE_OFF 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit0_data_store_off_reg;
    struct
    {
        unsigned long  unit0_data_store_off : 10; /* bit[0-9]  : 从缓存数据中取数偏移，chip单位。
                                                                 使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT0_DATA_STORE_OFF_UNION;
#define CBBP_UNIT0_DATA_STORE_OFF_unit0_data_store_off_START  (0)
#define CBBP_UNIT0_DATA_STORE_OFF_unit0_data_store_off_END    (9)


/***======================================================================***
                     (6/20) register_define_c_cs_mps_unit1
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_UNIT1_CLK_MODE_UNION
 结构说明  : UNIT1_CLK_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_clk_mode_reg;
    struct
    {
        unsigned long  unit1_clk_mode : 1;  /* bit[0]   : 搜索单元时钟频率选择
                                                          0：表示搜索单元128倍时钟；
                                                          1：表示搜索单元64倍时钟
                                                          默认不需要软件配置 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_CLK_MODE_UNION;
#define CBBP_UNIT1_CLK_MODE_unit1_clk_mode_START  (0)
#define CBBP_UNIT1_CLK_MODE_unit1_clk_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_CORR_RPT_PERIOD_UNION
 结构说明  : UNIT1_CORR_RPT_PERIOD 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit1_corr_rpt_period : 4;  /* bit[0-3] : 使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
                                                                 此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
                                                                 对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
                                                                 对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
                                                                 对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT1_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT1_CORR_RPT_PERIOD_unit1_corr_rpt_period_START  (0)
#define CBBP_UNIT1_CORR_RPT_PERIOD_unit1_corr_rpt_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT1_CORR_WAIT_CHIP_UNION
 结构说明  : UNIT1_CORR_WAIT_CHIP 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit1_corr_wait_chip : 11; /* bit[0-10] : 使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
                                                                 此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
                                                                 仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置 */
        unsigned long  reserved             : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_UNIT1_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT1_CORR_WAIT_CHIP_unit1_corr_wait_chip_START  (0)
#define CBBP_UNIT1_CORR_WAIT_CHIP_unit1_corr_wait_chip_END    (10)


/*****************************************************************************
 结构名    : CBBP_UNIT1_ANT_SEL_UNION
 结构说明  : UNIT1_ANT_SEL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_ant_sel_reg;
    struct
    {
        unsigned long  unit1_ant_sel : 1;  /* bit[0]   : 输入数据天线选择
                                                         0：表示输入接收天线1的数据；
                                                         1：表示输入接收天线2的数据； */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_ANT_SEL_UNION;
#define CBBP_UNIT1_ANT_SEL_unit1_ant_sel_START  (0)
#define CBBP_UNIT1_ANT_SEL_unit1_ant_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_MODE_UNION
 结构说明  : UNIT1_MODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_mode_reg;
    struct
    {
        unsigned long  unit1_mode : 2;  /* bit[0-1] : 模式选择。
                                                      0：表示初始小区搜索
                                                      1：表示pn列表小区搜索
                                                      2：表示多径搜索、小区测量（仅完成相干累加）
                                                      3：表示小区测量（完成相干累加与非相干累加） */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_UNIT1_MODE_UNION;
#define CBBP_UNIT1_MODE_unit1_mode_START  (0)
#define CBBP_UNIT1_MODE_unit1_mode_END    (1)


/*****************************************************************************
 结构名    : CBBP_UNIT1_WIN_UNION
 结构说明  : UNIT1_WIN 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_win_reg;
    struct
    {
        unsigned long  unit1_win : 10; /* bit[0-9]  : 搜索窗宽，单位为64chip，配置范围为1~512。
                                                      
                                                      初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
                                                      PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
                                                      多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
                                                      小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT1_WIN_UNION;
#define CBBP_UNIT1_WIN_unit1_win_START  (0)
#define CBBP_UNIT1_WIN_unit1_win_END    (9)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_SEL_UNION
 结构说明  : UNIT1_DATA_SEL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_sel_reg;
    struct
    {
        unsigned long  unit1_data_sel : 1;  /* bit[0]   : 输入数据选择。
                                                          0：表示使用实时数据；
                                                          1：表示使用缓存的数据 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_SEL_UNION;
#define CBBP_UNIT1_DATA_SEL_unit1_data_sel_START  (0)
#define CBBP_UNIT1_DATA_SEL_unit1_data_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_STORE_MODE_UNION
 结构说明  : UNIT1_DATA_STORE_MODE 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_store_mode_reg;
    struct
    {
        unsigned long  unit1_data_store_mode : 3;  /* bit[0-2] : 缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
                                                                 0表示连续存储，
                                                                 1表示每1024chip存储64chip，
                                                                 2表示每1024chip存储96chip，
                                                                 3表示每1024chip存储128chip，
                                                                 4表示每1024chip存储256chip
                                                                 5表示每1024chip存储512chip， */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_STORE_MODE_UNION;
#define CBBP_UNIT1_DATA_STORE_MODE_unit1_data_store_mode_START  (0)
#define CBBP_UNIT1_DATA_STORE_MODE_unit1_data_store_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_POS_UNION
 结构说明  : UNIT1_DATA_POS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_pos_reg;
    struct
    {
        unsigned long  unit1_data_pos : 16; /* bit[0-15] : 使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度 */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_POS_UNION;
#define CBBP_UNIT1_DATA_POS_unit1_data_pos_START  (0)
#define CBBP_UNIT1_DATA_POS_unit1_data_pos_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_POS_SEL_UNION
 结构说明  : UNIT1_DATA_POS_SEL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_pos_sel_reg;
    struct
    {
        unsigned long  unit1_data_pos_sel : 1;  /* bit[0]   : 使用实时数据时有效。
                                                              0：表示可以就近开始搜索；
                                                              1：必须等待Unit0_data_pos时，才能开始搜索； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_POS_SEL_UNION;
#define CBBP_UNIT1_DATA_POS_SEL_unit1_data_pos_sel_START  (0)
#define CBBP_UNIT1_DATA_POS_SEL_unit1_data_pos_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_MODE_UNION
 结构说明  : UNIT1_DATA_MODE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_mode_reg;
    struct
    {
        unsigned long  unit1_data_mode : 3;  /* bit[0-2] : 输入数据取数方式：
                                                           0表示连续取数，
                                                           1表示每1024chip取数64chip，
                                                           2表示每1024chip取数96chip，
                                                           3表示每1024chip取数128chip，
                                                           4表示每1024chip取数256chip
                                                           5表示每1024chip存储512chip，
                                                           
                                                           说明：
                                                           对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
                                                           对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。 */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_MODE_UNION;
#define CBBP_UNIT1_DATA_MODE_unit1_data_mode_START  (0)
#define CBBP_UNIT1_DATA_MODE_unit1_data_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN_NUM_UNION
 结构说明  : UNIT1_PN_NUM 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn_num_reg;
    struct
    {
        unsigned long  unit1_pn_num : 5;  /* bit[0-4] : Pn列表小区搜索时，pn offset个数，支持1~16个 */
        unsigned long  reserved     : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN_NUM_UNION;
#define CBBP_UNIT1_PN_NUM_unit1_pn_num_START  (0)
#define CBBP_UNIT1_PN_NUM_unit1_pn_num_END    (4)


/*****************************************************************************
 结构名    : CBBP_UNIT1_CORR_LENGTH_UNION
 结构说明  : UNIT1_CORR_LENGTH 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_corr_length_reg;
    struct
    {
        unsigned long  unit1_corr_length : 4;  /* bit[0-3] : 相干长度
                                                             0：32
                                                             1：64
                                                             2：96
                                                             3：128
                                                             4：256
                                                             5：96*4=384
                                                             6：64*12=768
                                                             7：512
                                                             算法推荐：
                                                             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
                                                             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
                                                             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
                                                             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。 */
        unsigned long  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT1_CORR_LENGTH_UNION;
#define CBBP_UNIT1_CORR_LENGTH_unit1_corr_length_START  (0)
#define CBBP_UNIT1_CORR_LENGTH_unit1_corr_length_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT1_NCORR_LENGTH_UNION
 结构说明  : UNIT1_NCORR_LENGTH 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_ncorr_length_reg;
    struct
    {
        unsigned long  unit1_ncorr_lenth : 3;  /* bit[0-2] : 非相干长度
                                                             0：1
                                                             1：2
                                                             2：3
                                                             3：4
                                                             4：8
                                                             5：16
                                                             6：32
                                                             7：96 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT1_NCORR_LENGTH_UNION;
#define CBBP_UNIT1_NCORR_LENGTH_unit1_ncorr_lenth_START  (0)
#define CBBP_UNIT1_NCORR_LENGTH_unit1_ncorr_lenth_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT1_ABS_TH_UNION
 结构说明  : UNIT1_ABS_TH 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_abs_th_reg;
    struct
    {
        unsigned long  unit1_abs_th : 16; /* bit[0-15] : 绝对噪声门限 */
        unsigned long  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT1_ABS_TH_UNION;
#define CBBP_UNIT1_ABS_TH_unit1_abs_th_START  (0)
#define CBBP_UNIT1_ABS_TH_unit1_abs_th_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT1_EN_UNION
 结构说明  : UNIT1_EN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_en_reg;
    struct
    {
        unsigned long  unit1_en : 1;  /* bit[0]   : 搜索单元使能信号 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_EN_UNION;
#define CBBP_UNIT1_EN_unit1_en_START  (0)
#define CBBP_UNIT1_EN_unit1_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_NOISE_ENERGY_UNION
 结构说明  : UNIT1_NOISE_ENERGY 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_noise_energy_reg;
    struct
    {
        unsigned long  unit1_noise_energy : 16; /* bit[0-15] : 单元0本次小区搜索上报的噪声门限 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT1_NOISE_ENERGY_UNION;
#define CBBP_UNIT1_NOISE_ENERGY_unit1_noise_energy_START  (0)
#define CBBP_UNIT1_NOISE_ENERGY_unit1_noise_energy_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT1_FRAME_SHIFT_UNION
 结构说明  : UNIT1_FRAME_SHIFT 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_frame_shift_reg;
    struct
    {
        unsigned long  unit1_frame_shft : 1;  /* bit[0]   : 单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
                                                            0：表示上报搜索窗与配置搜索窗完全一致
                                                            1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_FRAME_SHIFT_UNION;
#define CBBP_UNIT1_FRAME_SHIFT_unit1_frame_shft_START  (0)
#define CBBP_UNIT1_FRAME_SHIFT_unit1_frame_shft_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN0_FRAME_POS_UNION
 结构说明  : UNIT1_PN0_FRAME_POS 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn0_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
                                                                如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN0_FRAME_POS_UNION;
#define CBBP_UNIT1_PN0_FRAME_POS_unit1_pn0_frame_pos_START  (0)
#define CBBP_UNIT1_PN0_FRAME_POS_unit1_pn0_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN1_FRAME_POS_UNION
 结构说明  : UNIT1_PN1_FRAME_POS 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn1_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN1_FRAME_POS_UNION;
#define CBBP_UNIT1_PN1_FRAME_POS_unit1_pn1_frame_pos_START  (0)
#define CBBP_UNIT1_PN1_FRAME_POS_unit1_pn1_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN2_FRAME_POS_UNION
 结构说明  : UNIT1_PN2_FRAME_POS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn2_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN2_FRAME_POS_UNION;
#define CBBP_UNIT1_PN2_FRAME_POS_unit1_pn2_frame_pos_START  (0)
#define CBBP_UNIT1_PN2_FRAME_POS_unit1_pn2_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN3_FRAME_POS_UNION
 结构说明  : UNIT1_PN3_FRAME_POS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn3_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN3_FRAME_POS_UNION;
#define CBBP_UNIT1_PN3_FRAME_POS_unit1_pn3_frame_pos_START  (0)
#define CBBP_UNIT1_PN3_FRAME_POS_unit1_pn3_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN4_FRAME_POS_UNION
 结构说明  : UNIT1_PN4_FRAME_POS 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn4_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN4_FRAME_POS_UNION;
#define CBBP_UNIT1_PN4_FRAME_POS_unit1_pn4_frame_pos_START  (0)
#define CBBP_UNIT1_PN4_FRAME_POS_unit1_pn4_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN5_FRAME_POS_UNION
 结构说明  : UNIT1_PN5_FRAME_POS 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn5_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN5_FRAME_POS_UNION;
#define CBBP_UNIT1_PN5_FRAME_POS_unit1_pn5_frame_pos_START  (0)
#define CBBP_UNIT1_PN5_FRAME_POS_unit1_pn5_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN6_FRAME_POS_UNION
 结构说明  : UNIT1_PN6_FRAME_POS 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn6_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN6_FRAME_POS_UNION;
#define CBBP_UNIT1_PN6_FRAME_POS_unit1_pn6_frame_pos_START  (0)
#define CBBP_UNIT1_PN6_FRAME_POS_unit1_pn6_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN7_FRAME_POS_UNION
 结构说明  : UNIT1_PN7_FRAME_POS 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn7_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN7_FRAME_POS_UNION;
#define CBBP_UNIT1_PN7_FRAME_POS_unit1_pn7_frame_pos_START  (0)
#define CBBP_UNIT1_PN7_FRAME_POS_unit1_pn7_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN8_FRAME_POS_UNION
 结构说明  : UNIT1_PN8_FRAME_POS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn8_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN8_FRAME_POS_UNION;
#define CBBP_UNIT1_PN8_FRAME_POS_unit1_pn8_frame_pos_START  (0)
#define CBBP_UNIT1_PN8_FRAME_POS_unit1_pn8_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN9_FRAME_POS_UNION
 结构说明  : UNIT1_PN9_FRAME_POS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn9_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN9_FRAME_POS_UNION;
#define CBBP_UNIT1_PN9_FRAME_POS_unit1_pn9_frame_pos_START  (0)
#define CBBP_UNIT1_PN9_FRAME_POS_unit1_pn9_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN10_FRAME_POS_UNION
 结构说明  : UNIT1_PN10_FRAME_POS 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn10_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN10_FRAME_POS_UNION;
#define CBBP_UNIT1_PN10_FRAME_POS_unit1_pn10_frame_pos_START  (0)
#define CBBP_UNIT1_PN10_FRAME_POS_unit1_pn10_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN11_FRAME_POS_UNION
 结构说明  : UNIT1_PN11_FRAME_POS 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn11_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN11_FRAME_POS_UNION;
#define CBBP_UNIT1_PN11_FRAME_POS_unit1_pn11_frame_pos_START  (0)
#define CBBP_UNIT1_PN11_FRAME_POS_unit1_pn11_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN12_FRAME_POS_UNION
 结构说明  : UNIT1_PN12_FRAME_POS 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn12_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN12_FRAME_POS_UNION;
#define CBBP_UNIT1_PN12_FRAME_POS_unit1_pn12_frame_pos_START  (0)
#define CBBP_UNIT1_PN12_FRAME_POS_unit1_pn12_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN13_FRAME_POS_UNION
 结构说明  : UNIT1_PN13_FRAME_POS 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn13_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN13_FRAME_POS_UNION;
#define CBBP_UNIT1_PN13_FRAME_POS_unit1_pn13_frame_pos_START  (0)
#define CBBP_UNIT1_PN13_FRAME_POS_unit1_pn13_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN14_FRAME_POS_UNION
 结构说明  : UNIT1_PN14_FRAME_POS 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn14_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN14_FRAME_POS_UNION;
#define CBBP_UNIT1_PN14_FRAME_POS_unit1_pn14_frame_pos_START  (0)
#define CBBP_UNIT1_PN14_FRAME_POS_unit1_pn14_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_PN15_FRAME_POS_UNION
 结构说明  : UNIT1_PN15_FRAME_POS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit1_pn15_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT1_PN15_FRAME_POS_UNION;
#define CBBP_UNIT1_PN15_FRAME_POS_unit1_pn15_frame_pos_START  (0)
#define CBBP_UNIT1_PN15_FRAME_POS_unit1_pn15_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT1_CS_1X_MODE_UNION
 结构说明  : UNIT1_CS_1X_MODE 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit1_cs_1x_mode : 1;  /* bit[0]   : 搜索模式选择
                                                            0表示1x搜索
                                                            1表示evdo搜索 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT1_CS_1X_MODE_UNION;
#define CBBP_UNIT1_CS_1X_MODE_unit1_cs_1x_mode_START  (0)
#define CBBP_UNIT1_CS_1X_MODE_unit1_cs_1x_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT1_SRCH_CK_BYPASS_UNION
 结构说明  : UNIT1_SRCH_CK_BYPASS 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit1_ctrl_pass   : 1;  /* bit[0]   : 搜索单元控制部分时钟门控bypass
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit1_sort_bypass : 1;  /* bit[1]   : 搜索单元排队模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit1_rpt_bypass  : 1;  /* bit[2]   : 搜索单元上报模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT1_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_ctrl_pass_START    (0)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_ctrl_pass_END      (0)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_sort_bypass_START  (1)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_sort_bypass_END    (1)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_rpt_bypass_START   (2)
#define CBBP_UNIT1_SRCH_CK_BYPASS_unit1_rpt_bypass_END     (2)


/*****************************************************************************
 结构名    : CBBP_UNIT1_NOISE_ALPHER_COEF_UNION
 结构说明  : UNIT1_NOISE_ALPHER_COEF 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit1_noise_alpher_coef : 3;  /* bit[0-2] : 噪声门限滤波系数：
                                                                   0：1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT1_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT1_NOISE_ALPHER_COEF_unit1_noise_alpher_coef_START  (0)
#define CBBP_UNIT1_NOISE_ALPHER_COEF_unit1_noise_alpher_coef_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT1_DATA_STORE_OFF_UNION
 结构说明  : UNIT1_DATA_STORE_OFF 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit1_data_store_off_reg;
    struct
    {
        unsigned long  unit1_data_store_off : 10; /* bit[0-9]  : 从缓存数据中取数偏移，chip单位。
                                                                 使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT1_DATA_STORE_OFF_UNION;
#define CBBP_UNIT1_DATA_STORE_OFF_unit1_data_store_off_START  (0)
#define CBBP_UNIT1_DATA_STORE_OFF_unit1_data_store_off_END    (9)


/***======================================================================***
                     (7/20) register_define_c_cs_mps_unit2
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_UNIT2_CLK_MODE_UNION
 结构说明  : UNIT2_CLK_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_clk_mode_reg;
    struct
    {
        unsigned long  unit2_clk_mode : 1;  /* bit[0]   : 搜索单元时钟频率选择
                                                          0：表示搜索单元128倍时钟；
                                                          1：表示搜索单元64倍时钟
                                                          默认不需要软件配置 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_CLK_MODE_UNION;
#define CBBP_UNIT2_CLK_MODE_unit2_clk_mode_START  (0)
#define CBBP_UNIT2_CLK_MODE_unit2_clk_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_CORR_RPT_PERIOD_UNION
 结构说明  : UNIT2_CORR_RPT_PERIOD 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit2_corr_rpt_period : 4;  /* bit[0-3] : 使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
                                                                 此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
                                                                 对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
                                                                 对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
                                                                 对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT2_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT2_CORR_RPT_PERIOD_unit2_corr_rpt_period_START  (0)
#define CBBP_UNIT2_CORR_RPT_PERIOD_unit2_corr_rpt_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT2_CORR_WAIT_CHIP_UNION
 结构说明  : UNIT2_CORR_WAIT_CHIP 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit2_corr_wait_chip : 11; /* bit[0-10] : 使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
                                                                 此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
                                                                 仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置 */
        unsigned long  reserved             : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_UNIT2_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT2_CORR_WAIT_CHIP_unit2_corr_wait_chip_START  (0)
#define CBBP_UNIT2_CORR_WAIT_CHIP_unit2_corr_wait_chip_END    (10)


/*****************************************************************************
 结构名    : CBBP_UNIT2_ANT_SEL_UNION
 结构说明  : UNIT2_ANT_SEL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_ant_sel_reg;
    struct
    {
        unsigned long  unit2_ant_sel : 1;  /* bit[0]   : 输入数据天线选择
                                                         0：表示输入接收天线1的数据；
                                                         1：表示输入接收天线2的数据； */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_ANT_SEL_UNION;
#define CBBP_UNIT2_ANT_SEL_unit2_ant_sel_START  (0)
#define CBBP_UNIT2_ANT_SEL_unit2_ant_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_MODE_UNION
 结构说明  : UNIT2_MODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_mode_reg;
    struct
    {
        unsigned long  unit2_mode : 2;  /* bit[0-1] : 模式选择。
                                                      0：表示初始小区搜索
                                                      1：表示pn列表小区搜索
                                                      2：表示多径搜索、小区测量（仅完成相干累加）
                                                      3：表示小区测量（完成相干累加与非相干累加） */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_UNIT2_MODE_UNION;
#define CBBP_UNIT2_MODE_unit2_mode_START  (0)
#define CBBP_UNIT2_MODE_unit2_mode_END    (1)


/*****************************************************************************
 结构名    : CBBP_UNIT2_WIN_UNION
 结构说明  : UNIT2_WIN 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_win_reg;
    struct
    {
        unsigned long  unit2_win : 10; /* bit[0-9]  : 搜索窗宽，单位为64chip，配置范围为1~512。
                                                      
                                                      初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
                                                      PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
                                                      多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
                                                      小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip */
        unsigned long  reserved  : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT2_WIN_UNION;
#define CBBP_UNIT2_WIN_unit2_win_START  (0)
#define CBBP_UNIT2_WIN_unit2_win_END    (9)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_SEL_UNION
 结构说明  : UNIT2_DATA_SEL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_sel_reg;
    struct
    {
        unsigned long  unit2_data_sel : 1;  /* bit[0]   : 输入数据选择。
                                                          0：表示使用实时数据；
                                                          1：表示使用缓存的数据 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_SEL_UNION;
#define CBBP_UNIT2_DATA_SEL_unit2_data_sel_START  (0)
#define CBBP_UNIT2_DATA_SEL_unit2_data_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_STORE_MODE_UNION
 结构说明  : UNIT2_DATA_STORE_MODE 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_store_mode_reg;
    struct
    {
        unsigned long  unit2_data_store_mode : 3;  /* bit[0-2] : 缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
                                                                 0表示连续存储，
                                                                 1表示每1024chip存储64chip，
                                                                 2表示每1024chip存储96chip，
                                                                 3表示每1024chip存储128chip，
                                                                 4表示每1024chip存储256chip
                                                                 5表示每1024chip存储512chip， */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_STORE_MODE_UNION;
#define CBBP_UNIT2_DATA_STORE_MODE_unit2_data_store_mode_START  (0)
#define CBBP_UNIT2_DATA_STORE_MODE_unit2_data_store_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_POS_UNION
 结构说明  : UNIT2_DATA_POS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_pos_reg;
    struct
    {
        unsigned long  unit2_data_pos : 16; /* bit[0-15] : 使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度 */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_POS_UNION;
#define CBBP_UNIT2_DATA_POS_unit2_data_pos_START  (0)
#define CBBP_UNIT2_DATA_POS_unit2_data_pos_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_POS_SEL_UNION
 结构说明  : UNIT2_DATA_POS_SEL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_pos_sel_reg;
    struct
    {
        unsigned long  unit2_data_pos_sel : 1;  /* bit[0]   : 使用实时数据时有效。
                                                              0：表示可以就近开始搜索；
                                                              1：必须等待Unit0_data_pos时，才能开始搜索； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_POS_SEL_UNION;
#define CBBP_UNIT2_DATA_POS_SEL_unit2_data_pos_sel_START  (0)
#define CBBP_UNIT2_DATA_POS_SEL_unit2_data_pos_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_MODE_UNION
 结构说明  : UNIT2_DATA_MODE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_mode_reg;
    struct
    {
        unsigned long  unit2_data_mode : 3;  /* bit[0-2] : 输入数据取数方式：
                                                           0表示连续取数，
                                                           1表示每1024chip取数64chip，
                                                           2表示每1024chip取数96chip，
                                                           3表示每1024chip取数128chip，
                                                           4表示每1024chip取数256chip
                                                           5表示每1024chip存储512chip，
                                                           
                                                           说明：
                                                           对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
                                                           对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。 */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_MODE_UNION;
#define CBBP_UNIT2_DATA_MODE_unit2_data_mode_START  (0)
#define CBBP_UNIT2_DATA_MODE_unit2_data_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN_NUM_UNION
 结构说明  : UNIT2_PN_NUM 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn_num_reg;
    struct
    {
        unsigned long  unit2_pn_num : 5;  /* bit[0-4] : Pn列表小区搜索时，pn offset个数，支持1~16个 */
        unsigned long  reserved     : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN_NUM_UNION;
#define CBBP_UNIT2_PN_NUM_unit2_pn_num_START  (0)
#define CBBP_UNIT2_PN_NUM_unit2_pn_num_END    (4)


/*****************************************************************************
 结构名    : CBBP_UNIT2_CORR_LENGTH_UNION
 结构说明  : UNIT2_CORR_LENGTH 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_corr_length_reg;
    struct
    {
        unsigned long  unit2_corr_length : 4;  /* bit[0-3] : 相干长度
                                                             0：32
                                                             1：64
                                                             2：96
                                                             3：128
                                                             4：256
                                                             5：96*4=384
                                                             6：64*12=768
                                                             7：512
                                                             算法推荐：
                                                             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
                                                             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
                                                             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
                                                             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。 */
        unsigned long  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT2_CORR_LENGTH_UNION;
#define CBBP_UNIT2_CORR_LENGTH_unit2_corr_length_START  (0)
#define CBBP_UNIT2_CORR_LENGTH_unit2_corr_length_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT2_NCORR_LENGTH_UNION
 结构说明  : UNIT2_NCORR_LENGTH 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_ncorr_length_reg;
    struct
    {
        unsigned long  unit2_ncorr_lenth : 3;  /* bit[0-2] : 非相干长度
                                                             0：1
                                                             1：2
                                                             2：3
                                                             3：4
                                                             4：8
                                                             5：16
                                                             6：32
                                                             7：96 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT2_NCORR_LENGTH_UNION;
#define CBBP_UNIT2_NCORR_LENGTH_unit2_ncorr_lenth_START  (0)
#define CBBP_UNIT2_NCORR_LENGTH_unit2_ncorr_lenth_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT2_ABS_TH_UNION
 结构说明  : UNIT2_ABS_TH 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_abs_th_reg;
    struct
    {
        unsigned long  unit2_abs_th : 16; /* bit[0-15] : 绝对噪声门限 */
        unsigned long  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT2_ABS_TH_UNION;
#define CBBP_UNIT2_ABS_TH_unit2_abs_th_START  (0)
#define CBBP_UNIT2_ABS_TH_unit2_abs_th_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT2_EN_UNION
 结构说明  : UNIT2_EN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_en_reg;
    struct
    {
        unsigned long  unit2_en : 1;  /* bit[0]   : 搜索单元使能信号 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_EN_UNION;
#define CBBP_UNIT2_EN_unit2_en_START  (0)
#define CBBP_UNIT2_EN_unit2_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_NOISE_ENERGY_UNION
 结构说明  : UNIT2_NOISE_ENERGY 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_noise_energy_reg;
    struct
    {
        unsigned long  unit2_noise_energy : 16; /* bit[0-15] : 单元0本次小区搜索上报的噪声门限 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT2_NOISE_ENERGY_UNION;
#define CBBP_UNIT2_NOISE_ENERGY_unit2_noise_energy_START  (0)
#define CBBP_UNIT2_NOISE_ENERGY_unit2_noise_energy_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT2_FRAME_SHIFT_UNION
 结构说明  : UNIT2_FRAME_SHIFT 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_frame_shift_reg;
    struct
    {
        unsigned long  unit2_frame_shft : 1;  /* bit[0]   : 单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
                                                            0：表示上报搜索窗与配置搜索窗完全一致
                                                            1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_FRAME_SHIFT_UNION;
#define CBBP_UNIT2_FRAME_SHIFT_unit2_frame_shft_START  (0)
#define CBBP_UNIT2_FRAME_SHIFT_unit2_frame_shft_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN0_FRAME_POS_UNION
 结构说明  : UNIT2_PN0_FRAME_POS 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn0_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
                                                                如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN0_FRAME_POS_UNION;
#define CBBP_UNIT2_PN0_FRAME_POS_unit2_pn0_frame_pos_START  (0)
#define CBBP_UNIT2_PN0_FRAME_POS_unit2_pn0_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN1_FRAME_POS_UNION
 结构说明  : UNIT2_PN1_FRAME_POS 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn1_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN1_FRAME_POS_UNION;
#define CBBP_UNIT2_PN1_FRAME_POS_unit2_pn1_frame_pos_START  (0)
#define CBBP_UNIT2_PN1_FRAME_POS_unit2_pn1_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN2_FRAME_POS_UNION
 结构说明  : UNIT2_PN2_FRAME_POS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn2_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN2_FRAME_POS_UNION;
#define CBBP_UNIT2_PN2_FRAME_POS_unit2_pn2_frame_pos_START  (0)
#define CBBP_UNIT2_PN2_FRAME_POS_unit2_pn2_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN3_FRAME_POS_UNION
 结构说明  : UNIT2_PN3_FRAME_POS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn3_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN3_FRAME_POS_UNION;
#define CBBP_UNIT2_PN3_FRAME_POS_unit2_pn3_frame_pos_START  (0)
#define CBBP_UNIT2_PN3_FRAME_POS_unit2_pn3_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN4_FRAME_POS_UNION
 结构说明  : UNIT2_PN4_FRAME_POS 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn4_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN4_FRAME_POS_UNION;
#define CBBP_UNIT2_PN4_FRAME_POS_unit2_pn4_frame_pos_START  (0)
#define CBBP_UNIT2_PN4_FRAME_POS_unit2_pn4_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN5_FRAME_POS_UNION
 结构说明  : UNIT2_PN5_FRAME_POS 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn5_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN5_FRAME_POS_UNION;
#define CBBP_UNIT2_PN5_FRAME_POS_unit2_pn5_frame_pos_START  (0)
#define CBBP_UNIT2_PN5_FRAME_POS_unit2_pn5_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN6_FRAME_POS_UNION
 结构说明  : UNIT2_PN6_FRAME_POS 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn6_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN6_FRAME_POS_UNION;
#define CBBP_UNIT2_PN6_FRAME_POS_unit2_pn6_frame_pos_START  (0)
#define CBBP_UNIT2_PN6_FRAME_POS_unit2_pn6_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN7_FRAME_POS_UNION
 结构说明  : UNIT2_PN7_FRAME_POS 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn7_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN7_FRAME_POS_UNION;
#define CBBP_UNIT2_PN7_FRAME_POS_unit2_pn7_frame_pos_START  (0)
#define CBBP_UNIT2_PN7_FRAME_POS_unit2_pn7_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN8_FRAME_POS_UNION
 结构说明  : UNIT2_PN8_FRAME_POS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn8_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN8_FRAME_POS_UNION;
#define CBBP_UNIT2_PN8_FRAME_POS_unit2_pn8_frame_pos_START  (0)
#define CBBP_UNIT2_PN8_FRAME_POS_unit2_pn8_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN9_FRAME_POS_UNION
 结构说明  : UNIT2_PN9_FRAME_POS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn9_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN9_FRAME_POS_UNION;
#define CBBP_UNIT2_PN9_FRAME_POS_unit2_pn9_frame_pos_START  (0)
#define CBBP_UNIT2_PN9_FRAME_POS_unit2_pn9_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN10_FRAME_POS_UNION
 结构说明  : UNIT2_PN10_FRAME_POS 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn10_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN10_FRAME_POS_UNION;
#define CBBP_UNIT2_PN10_FRAME_POS_unit2_pn10_frame_pos_START  (0)
#define CBBP_UNIT2_PN10_FRAME_POS_unit2_pn10_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN11_FRAME_POS_UNION
 结构说明  : UNIT2_PN11_FRAME_POS 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn11_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN11_FRAME_POS_UNION;
#define CBBP_UNIT2_PN11_FRAME_POS_unit2_pn11_frame_pos_START  (0)
#define CBBP_UNIT2_PN11_FRAME_POS_unit2_pn11_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN12_FRAME_POS_UNION
 结构说明  : UNIT2_PN12_FRAME_POS 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn12_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN12_FRAME_POS_UNION;
#define CBBP_UNIT2_PN12_FRAME_POS_unit2_pn12_frame_pos_START  (0)
#define CBBP_UNIT2_PN12_FRAME_POS_unit2_pn12_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN13_FRAME_POS_UNION
 结构说明  : UNIT2_PN13_FRAME_POS 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn13_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN13_FRAME_POS_UNION;
#define CBBP_UNIT2_PN13_FRAME_POS_unit2_pn13_frame_pos_START  (0)
#define CBBP_UNIT2_PN13_FRAME_POS_unit2_pn13_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN14_FRAME_POS_UNION
 结构说明  : UNIT2_PN14_FRAME_POS 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn14_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN14_FRAME_POS_UNION;
#define CBBP_UNIT2_PN14_FRAME_POS_unit2_pn14_frame_pos_START  (0)
#define CBBP_UNIT2_PN14_FRAME_POS_unit2_pn14_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_PN15_FRAME_POS_UNION
 结构说明  : UNIT2_PN15_FRAME_POS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit2_pn15_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT2_PN15_FRAME_POS_UNION;
#define CBBP_UNIT2_PN15_FRAME_POS_unit2_pn15_frame_pos_START  (0)
#define CBBP_UNIT2_PN15_FRAME_POS_unit2_pn15_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT2_CS_1X_MODE_UNION
 结构说明  : UNIT2_CS_1X_MODE 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit2_cs_1x_mode : 1;  /* bit[0]   : 搜索模式选择
                                                            0表示1x搜索
                                                            1表示evdo搜索 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT2_CS_1X_MODE_UNION;
#define CBBP_UNIT2_CS_1X_MODE_unit2_cs_1x_mode_START  (0)
#define CBBP_UNIT2_CS_1X_MODE_unit2_cs_1x_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT2_SRCH_CK_BYPASS_UNION
 结构说明  : UNIT2_SRCH_CK_BYPASS 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit2_ctrl_pass   : 1;  /* bit[0]   : 搜索单元控制部分时钟门控bypass
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit2_sort_bypass : 1;  /* bit[1]   : 搜索单元排队模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit2_rpt_bypass  : 1;  /* bit[2]   : 搜索单元上报模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT2_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_ctrl_pass_START    (0)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_ctrl_pass_END      (0)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_sort_bypass_START  (1)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_sort_bypass_END    (1)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_rpt_bypass_START   (2)
#define CBBP_UNIT2_SRCH_CK_BYPASS_unit2_rpt_bypass_END     (2)


/*****************************************************************************
 结构名    : CBBP_UNIT2_NOISE_ALPHER_COEF_UNION
 结构说明  : UNIT2_NOISE_ALPHER_COEF 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit2_noise_alpher_coef : 3;  /* bit[0-2] : 噪声门限滤波系数：
                                                                   0：1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT2_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT2_NOISE_ALPHER_COEF_unit2_noise_alpher_coef_START  (0)
#define CBBP_UNIT2_NOISE_ALPHER_COEF_unit2_noise_alpher_coef_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT2_DATA_STORE_OFF_UNION
 结构说明  : UNIT2_DATA_STORE_OFF 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit2_data_store_off_reg;
    struct
    {
        unsigned long  unit2_data_store_off : 10; /* bit[0-9]  : 从缓存数据中取数偏移，chip单位。
                                                                 使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT2_DATA_STORE_OFF_UNION;
#define CBBP_UNIT2_DATA_STORE_OFF_unit2_data_store_off_START  (0)
#define CBBP_UNIT2_DATA_STORE_OFF_unit2_data_store_off_END    (9)


/***======================================================================***
                     (8/20) register_define_c_cs_mps_unit3
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_UNIT3_CLK_MODE_UNION
 结构说明  : UNIT3_CLK_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_clk_mode_reg;
    struct
    {
        unsigned long  unit3_clk_mode : 1;  /* bit[0]   : 搜索单元时钟频率选择
                                                          0：表示搜索单元128倍时钟；
                                                          1：表示搜索单元64倍时钟
                                                          默认不需要软件配置 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_CLK_MODE_UNION;
#define CBBP_UNIT3_CLK_MODE_unit3_clk_mode_START  (0)
#define CBBP_UNIT3_CLK_MODE_unit3_clk_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_CORR_RPT_PERIOD_UNION
 结构说明  : UNIT3_CORR_RPT_PERIOD 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_rpt_period_reg;
    struct
    {
        unsigned long  unit3_corr_rpt_period : 4;  /* bit[0-3] : 使用连续数据多径搜索（或小区测量）时，多少个相干累加结果上报一次。
                                                                 此接口主要是解决afc失锁时（1x下相干累加长度为64chip），相干结果上报周期太密集的问题。
                                                                 对于1x，afc失锁时，方案建议取12，即每64x12=768chip内，上报第一个64chip数据相干结果；
                                                                 对于1x，afc锁定时，方案建议取1，即每64x12=768chip上报一次相干累加结果；
                                                                 对于evdo时，方案建议取1，即每1024chip（afc失锁）或4096chip（afc锁定）上报一次相干结果； */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT3_CORR_RPT_PERIOD_UNION;
#define CBBP_UNIT3_CORR_RPT_PERIOD_unit3_corr_rpt_period_START  (0)
#define CBBP_UNIT3_CORR_RPT_PERIOD_unit3_corr_rpt_period_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT3_CORR_WAIT_CHIP_UNION
 结构说明  : UNIT3_CORR_WAIT_CHIP 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_wait_chip_reg;
    struct
    {
        unsigned long  unit3_corr_wait_chip : 11; /* bit[0-10] : 使用离散缓存数据小区测量时，每处理1024chip内的一段数据，等待多长时间，进行下一次1024chip处理，单位chip。
                                                                 此接口主要解决使用离散缓存的数据做小区测量时，中断上报密集的情况。
                                                                 仅在多径搜索模式（BBP仅完成相干累加）做测量时，需用配置 */
        unsigned long  reserved             : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_UNIT3_CORR_WAIT_CHIP_UNION;
#define CBBP_UNIT3_CORR_WAIT_CHIP_unit3_corr_wait_chip_START  (0)
#define CBBP_UNIT3_CORR_WAIT_CHIP_unit3_corr_wait_chip_END    (10)


/*****************************************************************************
 结构名    : CBBP_UNIT3_ANT_SEL_UNION
 结构说明  : UNIT3_ANT_SEL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_ant_sel_reg;
    struct
    {
        unsigned long  unit3_ant_sel : 1;  /* bit[0]   : 输入数据天线选择
                                                         0：表示输入接收天线1的数据；
                                                         1：表示输入接收天线2的数据； */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_ANT_SEL_UNION;
#define CBBP_UNIT3_ANT_SEL_unit3_ant_sel_START  (0)
#define CBBP_UNIT3_ANT_SEL_unit3_ant_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_MODE_UNION
 结构说明  : UNIT3_MODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_mode_reg;
    struct
    {
        unsigned long  unit3_mode : 2;  /* bit[0-1] : 模式选择。
                                                      0：表示初始小区搜索
                                                      1：表示pn列表小区搜索
                                                      2：表示多径搜索、小区测量（仅完成相干累加）
                                                      3：表示小区测量（完成相干累加与非相干累加） */
        unsigned long  reserved   : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_UNIT3_MODE_UNION;
#define CBBP_UNIT3_MODE_unit3_mode_START  (0)
#define CBBP_UNIT3_MODE_unit3_mode_END    (1)


/*****************************************************************************
 结构名    : CBBP_UNIT3_WIN_UNION
 结构说明  : UNIT3_WIN 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_win_reg;
    struct
    {
        unsigned long  unit3_win : 10; /* bit[0-9]  : 搜索窗宽，单位为64chip，配置范围为1~512。
                                                      
                                                      初始小区搜索时，仅支持离线数据搜索，配置为128，即搜索窗为64*128=8192chip；
                                                      PN列表小区搜索时，仅支持离线数据搜索，搜索窗宽固定为64chip；
                                                      多径搜索，仅支持实时数据搜索，搜索窗宽固定50chip；
                                                      小区搜索模式的小区测量，仅支持离线数据测量，窗宽固定为64chip； */
        unsigned long  reserved  : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT3_WIN_UNION;
#define CBBP_UNIT3_WIN_unit3_win_START  (0)
#define CBBP_UNIT3_WIN_unit3_win_END    (9)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_SEL_UNION
 结构说明  : UNIT3_DATA_SEL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_sel_reg;
    struct
    {
        unsigned long  unit3_data_sel : 1;  /* bit[0]   : 输入数据选择。
                                                          0：表示使用实时数据；
                                                          1：表示使用缓存的数据 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_SEL_UNION;
#define CBBP_UNIT3_DATA_SEL_unit3_data_sel_START  (0)
#define CBBP_UNIT3_DATA_SEL_unit3_data_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_STORE_MODE_UNION
 结构说明  : UNIT3_DATA_STORE_MODE 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_store_mode_reg;
    struct
    {
        unsigned long  unit3_data_store_mode : 3;  /* bit[0-2] : 缓存数据的模式，此参数必须与最近一次缓存数据时的参数Data_store_mode相同
                                                                 0表示连续存储，
                                                                 1表示每1024chip存储64chip，
                                                                 2表示每1024chip存储96chip，
                                                                 3表示每1024chip存储128chip，
                                                                 4表示每1024chip存储256chip
                                                                 5表示每1024chip存储512chip， */
        unsigned long  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_STORE_MODE_UNION;
#define CBBP_UNIT3_DATA_STORE_MODE_unit3_data_store_mode_START  (0)
#define CBBP_UNIT3_DATA_STORE_MODE_unit3_data_store_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_POS_UNION
 结构说明  : UNIT3_DATA_POS 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_pos_reg;
    struct
    {
        unsigned long  unit3_data_pos : 16; /* bit[0-15] : 使用实时数据时，接收数据的起始位置，在base_cnt[21:6]上的位置，1/2chip精度 */
        unsigned long  reserved       : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_POS_UNION;
#define CBBP_UNIT3_DATA_POS_unit3_data_pos_START  (0)
#define CBBP_UNIT3_DATA_POS_unit3_data_pos_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_POS_SEL_UNION
 结构说明  : UNIT3_DATA_POS_SEL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_pos_sel_reg;
    struct
    {
        unsigned long  unit3_data_pos_sel : 1;  /* bit[0]   : 使用实时数据时有效。
                                                              0：表示可以就近开始搜索；
                                                              1：必须等待Unit0_data_pos时，才能开始搜索； */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_POS_SEL_UNION;
#define CBBP_UNIT3_DATA_POS_SEL_unit3_data_pos_sel_START  (0)
#define CBBP_UNIT3_DATA_POS_SEL_unit3_data_pos_sel_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_MODE_UNION
 结构说明  : UNIT3_DATA_MODE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_mode_reg;
    struct
    {
        unsigned long  unit3_data_mode : 3;  /* bit[0-2] : 输入数据取数方式：
                                                           0表示连续取数，
                                                           1表示每1024chip取数64chip，
                                                           2表示每1024chip取数96chip，
                                                           3表示每1024chip取数128chip，
                                                           4表示每1024chip取数256chip
                                                           5表示每1024chip存储512chip，
                                                           
                                                           说明：
                                                           对于使用缓存数据，根据Unit0_data_store_mode确定输入数据的情况，且必须满足Unit0_data_mode<=Unit0_data_store_mode。
                                                           对于使用实时数据，如果实际启动时刻已经错过了Unit0_data_pos时刻，则对于连续取数时，从实际启动时刻开始取数；对于每1024chip间隔取数，从最近的64/96chip/128chip/256chip取数位置开始取数。 */
        unsigned long  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_MODE_UNION;
#define CBBP_UNIT3_DATA_MODE_unit3_data_mode_START  (0)
#define CBBP_UNIT3_DATA_MODE_unit3_data_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN_NUM_UNION
 结构说明  : UNIT3_PN_NUM 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn_num_reg;
    struct
    {
        unsigned long  unit3_pn_num : 5;  /* bit[0-4] : Pn列表小区搜索时，pn offset个数，支持1~16个 */
        unsigned long  reserved     : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN_NUM_UNION;
#define CBBP_UNIT3_PN_NUM_unit3_pn_num_START  (0)
#define CBBP_UNIT3_PN_NUM_unit3_pn_num_END    (4)


/*****************************************************************************
 结构名    : CBBP_UNIT3_CORR_LENGTH_UNION
 结构说明  : UNIT3_CORR_LENGTH 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_corr_length_reg;
    struct
    {
        unsigned long  unit3_corr_length : 4;  /* bit[0-3] : 相干长度
                                                             0：32
                                                             1：64
                                                             2：96
                                                             3：128
                                                             4：256
                                                             5：96*4=384
                                                             6：64*12=768
                                                             7：512
                                                             算法推荐：
                                                             1x小区搜索相干累加长度可配置为64、128、256，对应的非相干累加长度为32、16、8；
                                                             evdo小区搜索相干长度为64，非相干累加长度为32/16/8；
                                                             1x多径搜索相干长度为64x12=768（afc锁定）与64x1=64（afc失锁）两种，对应的非相干累加长度分别为8与96；
                                                             Evdo多径搜索相干长度96x4=384（afc锁定）与96x1=96（afc失锁），对应的非相干累加长度分别为8与32。 */
        unsigned long  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_UNIT3_CORR_LENGTH_UNION;
#define CBBP_UNIT3_CORR_LENGTH_unit3_corr_length_START  (0)
#define CBBP_UNIT3_CORR_LENGTH_unit3_corr_length_END    (3)


/*****************************************************************************
 结构名    : CBBP_UNIT3_NCORR_LENGTH_UNION
 结构说明  : UNIT3_NCORR_LENGTH 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_ncorr_length_reg;
    struct
    {
        unsigned long  unit3_ncorr_lenth : 3;  /* bit[0-2] : 非相干长度
                                                             0：1
                                                             1：2
                                                             2：3
                                                             3：4
                                                             4：8
                                                             5：16
                                                             6：32
                                                             7：96 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT3_NCORR_LENGTH_UNION;
#define CBBP_UNIT3_NCORR_LENGTH_unit3_ncorr_lenth_START  (0)
#define CBBP_UNIT3_NCORR_LENGTH_unit3_ncorr_lenth_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT3_ABS_TH_UNION
 结构说明  : UNIT3_ABS_TH 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_abs_th_reg;
    struct
    {
        unsigned long  unit3_abs_th : 16; /* bit[0-15] : 绝对噪声门限 */
        unsigned long  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT3_ABS_TH_UNION;
#define CBBP_UNIT3_ABS_TH_unit3_abs_th_START  (0)
#define CBBP_UNIT3_ABS_TH_unit3_abs_th_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT3_EN_UNION
 结构说明  : UNIT3_EN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_en_reg;
    struct
    {
        unsigned long  unit3_en : 1;  /* bit[0]   : 搜索单元使能信号 */
        unsigned long  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_EN_UNION;
#define CBBP_UNIT3_EN_unit3_en_START  (0)
#define CBBP_UNIT3_EN_unit3_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_NOISE_ENERGY_UNION
 结构说明  : UNIT3_NOISE_ENERGY 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_noise_energy_reg;
    struct
    {
        unsigned long  unit3_noise_energy : 16; /* bit[0-15] : 单元0本次小区搜索上报的噪声门限 */
        unsigned long  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_UNIT3_NOISE_ENERGY_UNION;
#define CBBP_UNIT3_NOISE_ENERGY_unit3_noise_energy_START  (0)
#define CBBP_UNIT3_NOISE_ENERGY_unit3_noise_energy_END    (15)


/*****************************************************************************
 结构名    : CBBP_UNIT3_FRAME_SHIFT_UNION
 结构说明  : UNIT3_FRAME_SHIFT 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_frame_shift_reg;
    struct
    {
        unsigned long  unit3_frame_shft : 1;  /* bit[0]   : 单元0本次上报搜索窗偏移1/2chip指示，多径搜索或小区测量时有效。
                                                            0：表示上报搜索窗与配置搜索窗完全一致
                                                            1：表示上报搜索窗相对于配置搜索窗偏移了1/2chip，即在原来配置的位置，往右偏移了1/2chip */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_FRAME_SHIFT_UNION;
#define CBBP_UNIT3_FRAME_SHIFT_unit3_frame_shft_START  (0)
#define CBBP_UNIT3_FRAME_SHIFT_unit3_frame_shft_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN0_FRAME_POS_UNION
 结构说明  : UNIT3_PN0_FRAME_POS 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn0_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn0_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是多径搜索、小区测量、初始小区搜索时，表示本单元的搜索窗窗尾对应的f-pich帧头位置。
                                                                如果是Pn列表小区搜索，表示第一个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN0_FRAME_POS_UNION;
#define CBBP_UNIT3_PN0_FRAME_POS_unit3_pn0_frame_pos_START  (0)
#define CBBP_UNIT3_PN0_FRAME_POS_unit3_pn0_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN1_FRAME_POS_UNION
 结构说明  : UNIT3_PN1_FRAME_POS 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn1_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn1_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第2个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN1_FRAME_POS_UNION;
#define CBBP_UNIT3_PN1_FRAME_POS_unit3_pn1_frame_pos_START  (0)
#define CBBP_UNIT3_PN1_FRAME_POS_unit3_pn1_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN2_FRAME_POS_UNION
 结构说明  : UNIT3_PN2_FRAME_POS 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn2_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn2_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第3个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN2_FRAME_POS_UNION;
#define CBBP_UNIT3_PN2_FRAME_POS_unit3_pn2_frame_pos_START  (0)
#define CBBP_UNIT3_PN2_FRAME_POS_unit3_pn2_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN3_FRAME_POS_UNION
 结构说明  : UNIT3_PN3_FRAME_POS 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn3_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn3_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[19:5]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第4个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN3_FRAME_POS_UNION;
#define CBBP_UNIT3_PN3_FRAME_POS_unit3_pn3_frame_pos_START  (0)
#define CBBP_UNIT3_PN3_FRAME_POS_unit3_pn3_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN4_FRAME_POS_UNION
 结构说明  : UNIT3_PN4_FRAME_POS 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn4_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn4_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第5个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN4_FRAME_POS_UNION;
#define CBBP_UNIT3_PN4_FRAME_POS_unit3_pn4_frame_pos_START  (0)
#define CBBP_UNIT3_PN4_FRAME_POS_unit3_pn4_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN5_FRAME_POS_UNION
 结构说明  : UNIT3_PN5_FRAME_POS 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn5_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn5_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第6个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN5_FRAME_POS_UNION;
#define CBBP_UNIT3_PN5_FRAME_POS_unit3_pn5_frame_pos_START  (0)
#define CBBP_UNIT3_PN5_FRAME_POS_unit3_pn5_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN6_FRAME_POS_UNION
 结构说明  : UNIT3_PN6_FRAME_POS 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn6_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn6_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第7个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN6_FRAME_POS_UNION;
#define CBBP_UNIT3_PN6_FRAME_POS_unit3_pn6_frame_pos_START  (0)
#define CBBP_UNIT3_PN6_FRAME_POS_unit3_pn6_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN7_FRAME_POS_UNION
 结构说明  : UNIT3_PN7_FRAME_POS 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn7_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn7_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第8个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN7_FRAME_POS_UNION;
#define CBBP_UNIT3_PN7_FRAME_POS_unit3_pn7_frame_pos_START  (0)
#define CBBP_UNIT3_PN7_FRAME_POS_unit3_pn7_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN8_FRAME_POS_UNION
 结构说明  : UNIT3_PN8_FRAME_POS 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn8_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn8_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第9个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN8_FRAME_POS_UNION;
#define CBBP_UNIT3_PN8_FRAME_POS_unit3_pn8_frame_pos_START  (0)
#define CBBP_UNIT3_PN8_FRAME_POS_unit3_pn8_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN9_FRAME_POS_UNION
 结构说明  : UNIT3_PN9_FRAME_POS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn9_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn9_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                如果是Pn列表小区搜索，表示第10个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved            : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN9_FRAME_POS_UNION;
#define CBBP_UNIT3_PN9_FRAME_POS_unit3_pn9_frame_pos_START  (0)
#define CBBP_UNIT3_PN9_FRAME_POS_unit3_pn9_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN10_FRAME_POS_UNION
 结构说明  : UNIT3_PN10_FRAME_POS 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn10_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn10_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第11个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN10_FRAME_POS_UNION;
#define CBBP_UNIT3_PN10_FRAME_POS_unit3_pn10_frame_pos_START  (0)
#define CBBP_UNIT3_PN10_FRAME_POS_unit3_pn10_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN11_FRAME_POS_UNION
 结构说明  : UNIT3_PN11_FRAME_POS 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn11_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn11_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第12个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN11_FRAME_POS_UNION;
#define CBBP_UNIT3_PN11_FRAME_POS_unit3_pn11_frame_pos_START  (0)
#define CBBP_UNIT3_PN11_FRAME_POS_unit3_pn11_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN12_FRAME_POS_UNION
 结构说明  : UNIT3_PN12_FRAME_POS 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn12_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn12_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第13个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN12_FRAME_POS_UNION;
#define CBBP_UNIT3_PN12_FRAME_POS_unit3_pn12_frame_pos_START  (0)
#define CBBP_UNIT3_PN12_FRAME_POS_unit3_pn12_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN13_FRAME_POS_UNION
 结构说明  : UNIT3_PN13_FRAME_POS 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn13_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn13_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第14个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN13_FRAME_POS_UNION;
#define CBBP_UNIT3_PN13_FRAME_POS_unit3_pn13_frame_pos_START  (0)
#define CBBP_UNIT3_PN13_FRAME_POS_unit3_pn13_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN14_FRAME_POS_UNION
 结构说明  : UNIT3_PN14_FRAME_POS 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn14_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn14_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第15个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN14_FRAME_POS_UNION;
#define CBBP_UNIT3_PN14_FRAME_POS_unit3_pn14_frame_pos_START  (0)
#define CBBP_UNIT3_PN14_FRAME_POS_unit3_pn14_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_PN15_FRAME_POS_UNION
 结构说明  : UNIT3_PN15_FRAME_POS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_pn15_frame_pos_reg;
    struct
    {
        unsigned long  unit3_pn15_frame_pos : 15; /* bit[0-14] : 搜索窗窗尾对应的f-pich信道帧头位置，在base_cnt[21:7]上的位置，chip精度。
                                                                 如果是Pn列表小区搜索，表示第16个pn offset对应的搜索窗窗尾的f-pich信道帧头位置 */
        unsigned long  reserved             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_UNIT3_PN15_FRAME_POS_UNION;
#define CBBP_UNIT3_PN15_FRAME_POS_unit3_pn15_frame_pos_START  (0)
#define CBBP_UNIT3_PN15_FRAME_POS_unit3_pn15_frame_pos_END    (14)


/*****************************************************************************
 结构名    : CBBP_UNIT3_CS_1X_MODE_UNION
 结构说明  : UNIT3_CS_1X_MODE 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_cs_1x_mode_reg;
    struct
    {
        unsigned long  unit3_cs_1x_mode : 1;  /* bit[0]   : 搜索模式选择
                                                            0表示1x搜索
                                                            1表示evdo搜索 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_UNIT3_CS_1X_MODE_UNION;
#define CBBP_UNIT3_CS_1X_MODE_unit3_cs_1x_mode_START  (0)
#define CBBP_UNIT3_CS_1X_MODE_unit3_cs_1x_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_UNIT3_SRCH_CK_BYPASS_UNION
 结构说明  : UNIT3_SRCH_CK_BYPASS 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_srch_ck_bypass_reg;
    struct
    {
        unsigned long  unit3_ctrl_pass   : 1;  /* bit[0]   : 搜索单元控制部分时钟门控bypass
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit3_sort_bypass : 1;  /* bit[1]   : 搜索单元排队模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  unit3_rpt_bypass  : 1;  /* bit[2]   : 搜索单元上报模块时钟门控
                                                             0表示时钟门控有效
                                                             1表示时钟常开 */
        unsigned long  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT3_SRCH_CK_BYPASS_UNION;
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_ctrl_pass_START    (0)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_ctrl_pass_END      (0)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_sort_bypass_START  (1)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_sort_bypass_END    (1)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_rpt_bypass_START   (2)
#define CBBP_UNIT3_SRCH_CK_BYPASS_unit3_rpt_bypass_END     (2)


/*****************************************************************************
 结构名    : CBBP_UNIT3_NOISE_ALPHER_COEF_UNION
 结构说明  : UNIT3_NOISE_ALPHER_COEF 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_noise_alpher_coef_reg;
    struct
    {
        unsigned long  unit3_noise_alpher_coef : 3;  /* bit[0-2] : 噪声门限滤波系数：
                                                                   0：1/2
                                                                   1:1/16
                                                                   2:1/32
                                                                   3:1/64
                                                                   4:1/128
                                                                   5:1/256 */
        unsigned long  reserved                : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_UNIT3_NOISE_ALPHER_COEF_UNION;
#define CBBP_UNIT3_NOISE_ALPHER_COEF_unit3_noise_alpher_coef_START  (0)
#define CBBP_UNIT3_NOISE_ALPHER_COEF_unit3_noise_alpher_coef_END    (2)


/*****************************************************************************
 结构名    : CBBP_UNIT3_DATA_STORE_OFF_UNION
 结构说明  : UNIT3_DATA_STORE_OFF 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      unit3_data_store_off_reg;
    struct
    {
        unsigned long  unit3_data_store_off : 10; /* bit[0-9]  : 从缓存数据中取数偏移，chip单位。
                                                                 使用场景：超远小区测量，连续缓存4096chip数据，测量时，每1024chip抽取部分数据，抽取位置由此寄存器确定 */
        unsigned long  reserved             : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_UNIT3_DATA_STORE_OFF_UNION;
#define CBBP_UNIT3_DATA_STORE_OFF_unit3_data_store_off_START  (0)
#define CBBP_UNIT3_DATA_STORE_OFF_unit3_data_store_off_END    (9)


/***======================================================================***
                     (9/20) register_define_c_cs_mps_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_UNIT0_RPT_UNION
 结构说明  : UNIT0_RPT 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
*****************************************************************************/
typedef union
{
    unsigned long      unit0_rpt_reg;
    struct
    {
        unsigned long  unit0_rpt_low  : 16; /* bit[0-15] : 多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
                                                           小区测量（完成相干累加与非相干累加）时为非相干累加能量
                                                           小区搜索时为小区能量 */
        unsigned long  unit0_rpt_high : 16; /* bit[16-31]: 多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
                                                           小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。 */
    } reg;
} CBBP_UNIT0_RPT_UNION;
#define CBBP_UNIT0_RPT_unit0_rpt_low_START   (0)
#define CBBP_UNIT0_RPT_unit0_rpt_low_END     (15)
#define CBBP_UNIT0_RPT_unit0_rpt_high_START  (16)
#define CBBP_UNIT0_RPT_unit0_rpt_high_END    (31)


/*****************************************************************************
 结构名    : CBBP_UNIT1_RPT_UNION
 结构说明  : UNIT1_RPT 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
*****************************************************************************/
typedef union
{
    unsigned long      unit1_rpt_reg;
    struct
    {
        unsigned long  unit1_rpt_low  : 16; /* bit[0-15] : 多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
                                                           小区测量（完成相干累加与非相干累加）时为非相干累加能量
                                                           小区搜索时为小区能量 */
        unsigned long  unit1_rpt_high : 16; /* bit[16-31]: 多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
                                                           小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。 */
    } reg;
} CBBP_UNIT1_RPT_UNION;
#define CBBP_UNIT1_RPT_unit1_rpt_low_START   (0)
#define CBBP_UNIT1_RPT_unit1_rpt_low_END     (15)
#define CBBP_UNIT1_RPT_unit1_rpt_high_START  (16)
#define CBBP_UNIT1_RPT_unit1_rpt_high_END    (31)


/*****************************************************************************
 结构名    : CBBP_UNIT2_RPT_UNION
 结构说明  : UNIT2_RPT 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: 多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
*****************************************************************************/
typedef union
{
    unsigned long      unit2_rpt_reg;
    struct
    {
        unsigned long  unit2_rpt_low  : 16; /* bit[0-15] : 多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
                                                           小区测量（完成相干累加与非相干累加）时为非相干累加能量
                                                           小区搜索时为小区能量 */
        unsigned long  unit2_rpt_high : 16; /* bit[16-31]: 多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
                                                           小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。 */
    } reg;
} CBBP_UNIT2_RPT_UNION;
#define CBBP_UNIT2_RPT_unit2_rpt_low_START   (0)
#define CBBP_UNIT2_RPT_unit2_rpt_low_END     (15)
#define CBBP_UNIT2_RPT_unit2_rpt_high_START  (16)
#define CBBP_UNIT2_RPT_unit2_rpt_high_END    (31)


/*****************************************************************************
 结构名    : CBBP_UNIT3_RPT_UNION
 结构说明  : UNIT3_RPT 寄存器结构定义。地址偏移量:0x0600，初值:0x00000000，宽度:32
 寄存器说明: 多径搜索、小区测量（仅完成相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的相干结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的相干结果，…..。
            Bit[31:16]为Q路结果；
            Bit[15:0]为I路结果；
            
            小区测量（完成相干累加与非相干累加）时，上报128个结果：
            第一个存储结果为f-pich帧头为Unit0_pn0_frame_pos的结果，第二个存储结果为f-pich帧头为(Unit0_frame_pos-1/2chip)的结果，…..。
            Bit[15:0]为非相干累加结果；
            
            
            小区搜索时，使用地址0~31，上报32个结果：
            Bit[31:16]为搜索到的小区pilot信道帧头在base_cnt[19:4]上位置；
            Bit[15:0]为搜索到小区上报能量
*****************************************************************************/
typedef union
{
    unsigned long      unit3_rpt_reg;
    struct
    {
        unsigned long  unit3_rpt_low  : 16; /* bit[0-15] : 多径搜索、小区测量（仅完成相干累加）时为I路想干结果；
                                                           小区测量（完成相干累加与非相干累加）时为非相干累加能量
                                                           小区搜索时为小区能量 */
        unsigned long  unit3_rpt_high : 16; /* bit[16-31]: 多径搜索、小区测量（仅完成相干累加）时为Q路想干结果
                                                           小区搜索时为小区pilot信道帧头在base_cnt[21:6]上的位置，1/2chip精度。 */
    } reg;
} CBBP_UNIT3_RPT_UNION;
#define CBBP_UNIT3_RPT_unit3_rpt_low_START   (0)
#define CBBP_UNIT3_RPT_unit3_rpt_low_END     (15)
#define CBBP_UNIT3_RPT_unit3_rpt_high_START  (16)
#define CBBP_UNIT3_RPT_unit3_rpt_high_END    (31)


/***======================================================================***
                     (10/20) register_define_c_dldec
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_DLDEC_ESTB_IND_UNION
 结构说明  : DLDEC_ESTB_IND 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_estb_ind_reg;
    struct
    {
        unsigned long  dldec_estb_ind : 1;  /* bit[0]   : 译码建立使能，必须在所有译码参数配置完成后配置为1 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_ESTB_IND_UNION;
#define CBBP_DLDEC_ESTB_IND_dldec_estb_ind_START  (0)
#define CBBP_DLDEC_ESTB_IND_dldec_estb_ind_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_DEC_START_UNION
 结构说明  : DLDEC_DEC_START 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_dec_start_reg;
    struct
    {
        unsigned long  dldec_dec_start : 1;  /* bit[0]   : 译码启动信号，必须在所有译码参数和译码建立使能配置完成后配置 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_DEC_START_UNION;
#define CBBP_DLDEC_DEC_START_dldec_dec_start_START  (0)
#define CBBP_DLDEC_DEC_START_dldec_dec_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_PACKET_PARA_UNION
 结构说明  : PACKET_PARA 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      packet_para_reg;
    struct
    {
        unsigned long  dldec_crc_type              : 4;  /* bit[0-3]  : CRC */
        unsigned long  dldec_crc_init_state        : 1;  /* bit[4]    : CRC内部寄存器初始化状态；
                                                                        0：全0；1：全1。 */
        unsigned long  reserved_0                  : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dldec_reserve_bit_exist_ind : 1;  /* bit[8]    : reserve_bit指示，1表示存在reserve比特 */
        unsigned long  reserved_1                  : 3;  /* bit[9-11] : 保留 */
        unsigned long  dldec_tail_len              : 4;  /* bit[12-15]: 超长码块分段译码非尾段或者寻呼、同步信道译码时该参数配置为0，其他信道该参数配置为8或6.  */
        unsigned long  dldec_info_len              : 13; /* bit[16-28]: 信息比特长度 */
        unsigned long  reserved_2                  : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_PACKET_PARA_UNION;
#define CBBP_PACKET_PARA_dldec_crc_type_START               (0)
#define CBBP_PACKET_PARA_dldec_crc_type_END                 (3)
#define CBBP_PACKET_PARA_dldec_crc_init_state_START         (4)
#define CBBP_PACKET_PARA_dldec_crc_init_state_END           (4)
#define CBBP_PACKET_PARA_dldec_reserve_bit_exist_ind_START  (8)
#define CBBP_PACKET_PARA_dldec_reserve_bit_exist_ind_END    (8)
#define CBBP_PACKET_PARA_dldec_tail_len_START               (12)
#define CBBP_PACKET_PARA_dldec_tail_len_END                 (15)
#define CBBP_PACKET_PARA_dldec_info_len_START               (16)
#define CBBP_PACKET_PARA_dldec_info_len_END                 (28)


/*****************************************************************************
 结构名    : CBBP_DEC_MODE_UNION
 结构说明  : DEC_MODE 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dec_mode_reg;
    struct
    {
        unsigned long  dldec_code_rate    : 3;  /* bit[0-2]  : 编码率，编码率为1/R时，配置为R。 */
        unsigned long  reserved_0         : 1;  /* bit[3]    : 保留 */
        unsigned long  turbo_mode         : 1;  /* bit[4]    : 1X turbo编码模式，0表示默认模式，1表示补充模式。 */
        unsigned long  reserved_1         : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dldec_dec_mode     : 3;  /* bit[8-10] : 0: 1X下行卷积码块完整流程译码; 1: 1X下行TURBO码块完整流程译码;2: EVDO下行完整流程译码; 3: 1X 解交织解打孔解重复处理加速模式; 4: 纯VTB译码加速模式; 5: 纯TURBO译码加速模式。 */
        unsigned long  reserved_2         : 1;  /* bit[11]   : 保留 */
        unsigned long  dldec_traffic_type : 1;  /* bit[12]   : C工作模式：0表示1X，1表示EVDO */
        unsigned long  reserved_3         : 3;  /* bit[13-15]: 保留 */
        unsigned long  dldec_harq_mode    : 1;  /* bit[16]   : 纯Turbo译码模式下，harq合并使能。1，表示如果此时为旧数据，则进行harq合并。否则不进行合并。0，表示禁止合并 */
        unsigned long  reserved_4         : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_DEC_MODE_UNION;
#define CBBP_DEC_MODE_dldec_code_rate_START     (0)
#define CBBP_DEC_MODE_dldec_code_rate_END       (2)
#define CBBP_DEC_MODE_turbo_mode_START          (4)
#define CBBP_DEC_MODE_turbo_mode_END            (4)
#define CBBP_DEC_MODE_dldec_dec_mode_START      (8)
#define CBBP_DEC_MODE_dldec_dec_mode_END        (10)
#define CBBP_DEC_MODE_dldec_traffic_type_START  (12)
#define CBBP_DEC_MODE_dldec_traffic_type_END    (12)
#define CBBP_DEC_MODE_dldec_harq_mode_START     (16)
#define CBBP_DEC_MODE_dldec_harq_mode_END       (16)


/*****************************************************************************
 结构名    : CBBP_SCR_INIT_STATE_UNION
 结构说明  : SCR_INIT_STATE 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      scr_init_state_reg;
    struct
    {
        unsigned long  dldec_scramble_init_state : 17; /* bit[0-16] : 扰码初始化状态。 */
        unsigned long  reserved                  : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_SCR_INIT_STATE_UNION;
#define CBBP_SCR_INIT_STATE_dldec_scramble_init_state_START  (0)
#define CBBP_SCR_INIT_STATE_dldec_scramble_init_state_END    (16)


/*****************************************************************************
 结构名    : CBBP_BLOCK_INTL_PARA_UNION
 结构说明  : BLOCK_INTL_PARA 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      block_intl_para_reg;
    struct
    {
        unsigned long  dldec_block_intl_j_para : 8;  /* bit[0-7]  : block交织j参数。 */
        unsigned long  dldec_block_intl_m_para : 4;  /* bit[8-11] : block交织m参数。 */
        unsigned long  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_BLOCK_INTL_PARA_UNION;
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_j_para_START  (0)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_j_para_END    (7)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_m_para_START  (8)
#define CBBP_BLOCK_INTL_PARA_dldec_block_intl_m_para_END    (11)


/*****************************************************************************
 结构名    : CBBP_PERMUTING_INTL_PARA_UNION
 结构说明  : PERMUTING_INTL_PARA 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      permuting_intl_para_reg;
    struct
    {
        unsigned long  dldec_permuting_intl_k_para : 3;  /* bit[0-2] : permuting交织k参数。 */
        unsigned long  reserved_0                  : 1;  /* bit[3]   : 保留 */
        unsigned long  dldec_permuting_intl_m_para : 4;  /* bit[4-7] : permuting交织m参数。 */
        unsigned long  reserved_1                  : 24; /* bit[8-31]: 保留 */
    } reg;
} CBBP_PERMUTING_INTL_PARA_UNION;
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_k_para_START  (0)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_k_para_END    (2)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_m_para_START  (4)
#define CBBP_PERMUTING_INTL_PARA_dldec_permuting_intl_m_para_END    (7)


/*****************************************************************************
 结构名    : CBBP_MATRIX_INTL_PARA_UNION
 结构说明  : MATRIX_INTL_PARA 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      matrix_intl_para_reg;
    struct
    {
        unsigned long  dldec_matrix_intl_d_para : 4;  /* bit[0-3]  : matrix交织d参数 */
        unsigned long  dldec_matrix_intl_r_para : 3;  /* bit[4-6]  : matrix交织r参数 */
        unsigned long  reserved_0               : 1;  /* bit[7]    : 保留 */
        unsigned long  dldec_matrix_intl_m_para : 4;  /* bit[8-11] : matrix交织m参数 */
        unsigned long  dldec_matrix_intl_k_para : 3;  /* bit[12-14]: matrix交织k参数 */
        unsigned long  reserved_1               : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_MATRIX_INTL_PARA_UNION;
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_d_para_START  (0)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_d_para_END    (3)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_r_para_START  (4)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_r_para_END    (6)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_m_para_START  (8)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_m_para_END    (11)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_k_para_START  (12)
#define CBBP_MATRIX_INTL_PARA_dldec_matrix_intl_k_para_END    (14)


/*****************************************************************************
 结构名    : CBBP_INTL_PAPA_UNION
 结构说明  : INTL_PAPA 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      intl_papa_reg;
    struct
    {
        unsigned long  dldec_block_intl_len : 15; /* bit[0-14] : 交织长度 */
        unsigned long  reserved_0           : 1;  /* bit[15]   : 保留 */
        unsigned long  dldec_intl_mode      : 3;  /* bit[16-18]: 0：Matrix Interleave交织（EVDO 上下行使用）；1：下行Symbol Permuting交织（EVDO使用）；2：下行Bit-Reversal Order Interleave交织（1X使用）；3：下行Forward-Backwards Bit-Reversal Order Interleave交织（FOR_FCH_CCSH_INTERLEAVER_TYPE = 0,1X使用）；4：下行Forward-Backwards Bit-Reversal Order Interleave交织（FOR_FCH_CCSH_INTERLEAVER_TYPE = 1,1X使用）；5：上行TYPE1 Block Interleave交织（1X使用）（译码模块禁止配置）；6：上行TYPE2 Block Interleave交织（1X使用）（译码模块禁止配置）；7：上行Reverse Interleave（EVDO使用）（译码模块禁止配置） */
        unsigned long  reserved_1           : 13; /* bit[19-31]: 保留 */
    } reg;
} CBBP_INTL_PAPA_UNION;
#define CBBP_INTL_PAPA_dldec_block_intl_len_START  (0)
#define CBBP_INTL_PAPA_dldec_block_intl_len_END    (14)
#define CBBP_INTL_PAPA_dldec_intl_mode_START       (16)
#define CBBP_INTL_PAPA_dldec_intl_mode_END         (18)


/*****************************************************************************
 结构名    : CBBP_PUNC_PATTERN_UNION
 结构说明  : PUNC_PATTERN 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      punc_pattern_reg;
    struct
    {
        unsigned long  dldec_punc_pattern : 25; /* bit[0-24] : 打孔图案，最低比特为第一个状态指示。例如打孔图案为11010时，表示第一个、第三个数据打孔，其余数据通过。 */
        unsigned long  reserved           : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_PUNC_PATTERN_UNION;
#define CBBP_PUNC_PATTERN_dldec_punc_pattern_START  (0)
#define CBBP_PUNC_PATTERN_dldec_punc_pattern_END    (24)


/*****************************************************************************
 结构名    : CBBP_PUNC_PERIOD_UNION
 结构说明  : PUNC_PERIOD 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      punc_period_reg;
    struct
    {
        unsigned long  dldec_punc_period : 5;  /* bit[0-4]  : 打孔周期 */
        unsigned long  reserved_0        : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dldec_punc_mode   : 2;  /* bit[8-9]  : 0:根据打孔图样产生打孔信息（包括ERAM模式下需要通过打孔图样产生打孔信息的场景）
                                                              1：非ERAM模式下，根据公式计算打孔信息
                                                              2：ERAM模式下，根据公式计算打孔信息 */
        unsigned long  reserved_1        : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_PUNC_PERIOD_UNION;
#define CBBP_PUNC_PERIOD_dldec_punc_period_START  (0)
#define CBBP_PUNC_PERIOD_dldec_punc_period_END    (4)
#define CBBP_PUNC_PERIOD_dldec_punc_mode_START    (8)
#define CBBP_PUNC_PERIOD_dldec_punc_mode_END      (9)


/*****************************************************************************
 结构名    : CBBP_DLDEC_LEN_BEF_PUNC_UNION
 结构说明  : DLDEC_LEN_BEF_PUNC 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_len_bef_punc_reg;
    struct
    {
        unsigned long  dldec_len_bef_punc : 15; /* bit[0-14] : 打孔前长度，即重复后长度 */
        unsigned long  reserved           : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_DLDEC_LEN_BEF_PUNC_UNION;
#define CBBP_DLDEC_LEN_BEF_PUNC_dldec_len_bef_punc_START  (0)
#define CBBP_DLDEC_LEN_BEF_PUNC_dldec_len_bef_punc_END    (14)


/*****************************************************************************
 结构名    : CBBP_DLDEC_LONG_VTB_PARA_UNION
 结构说明  : DLDEC_LONG_VTB_PARA 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_long_vtb_para_reg;
    struct
    {
        unsigned long  dldec_vtb_llr_base_addr : 15; /* bit[0-14] : 超长维特比译码前LLR RAM的基地址。非超长vtb译码时配置为0,超长码块时根据实际LLR起始位置配置。例如超长码块第一次译码长度为768，如果训练序列长度为128，则第二次译码基地址配置为（（768-128）*code_rate/4）-1。 */
        unsigned long  reserved                : 16; /* bit[15-30]: 保留 */
        unsigned long  dldec_long_vtb_mode     : 1;  /* bit[31]   : 超常vtb译码模式,1表示超常vtb译码模式。 */
    } reg;
} CBBP_DLDEC_LONG_VTB_PARA_UNION;
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_vtb_llr_base_addr_START  (0)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_vtb_llr_base_addr_END    (14)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_long_vtb_mode_START      (31)
#define CBBP_DLDEC_LONG_VTB_PARA_dldec_long_vtb_mode_END        (31)


/*****************************************************************************
 结构名    : CBBP_VTB_INIT_STATE_UNION
 结构说明  : VTB_INIT_STATE 寄存器结构定义。地址偏移量:0x03C，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_init_state_reg;
    struct
    {
        unsigned long  dldec_vtb_init_state    : 8;  /* bit[0-7] : 维特比初始化状态，根据前次上报的对应时隙状态配置。 */
        unsigned long  reserved                : 23; /* bit[8-30]: 保留 */
        unsigned long  dldec_vtb_init_state_en : 1;  /* bit[31]  : 维特比译码初始化状态有效使能 */
    } reg;
} CBBP_VTB_INIT_STATE_UNION;
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_START     (0)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_END       (7)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_en_START  (31)
#define CBBP_VTB_INIT_STATE_dldec_vtb_init_state_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_EVTB_EN_UNION
 结构说明  : EVTB_EN 寄存器结构定义。地址偏移量:0x040，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      evtb_en_reg;
    struct
    {
        unsigned long  evtb_traceback_num : 4;  /* bit[0-3] : 增强vtb回溯次数，支持1~8。例如配置为4时，表示除第一次译码外，最多还有3次译码。 */
        unsigned long  evtb_en            : 1;  /* bit[4]   : 增强vtb使能 */
        unsigned long  reserved           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_EVTB_EN_UNION;
#define CBBP_EVTB_EN_evtb_traceback_num_START  (0)
#define CBBP_EVTB_EN_evtb_traceback_num_END    (3)
#define CBBP_EVTB_EN_evtb_en_START             (4)
#define CBBP_EVTB_EN_evtb_en_END               (4)


/*****************************************************************************
 结构名    : CBBP_VTB_TB_MODE_UNION
 结构说明  : VTB_TB_MODE 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_tb_mode_reg;
    struct
    {
        unsigned long  dldec_vtb_tb_mode : 1;  /* bit[0]   : vtb回溯模式，0表示从0状态开始回溯，1表示从最大度量状态开始回溯。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_VTB_TB_MODE_UNION;
#define CBBP_VTB_TB_MODE_dldec_vtb_tb_mode_START  (0)
#define CBBP_VTB_TB_MODE_dldec_vtb_tb_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_VTB_TB_RPT_SLOT_UNION
 结构说明  : VTB_TB_RPT_SLOT 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      vtb_tb_rpt_slot_reg;
    struct
    {
        unsigned long  vtb_tb_rpt_slot : 9;  /* bit[0-8] : vtb回溯状态上报时隙，在超长码块、寻呼信道、同步信道时需要根据训练长度进行配置。 */
        unsigned long  reserved        : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_VTB_TB_RPT_SLOT_UNION;
#define CBBP_VTB_TB_RPT_SLOT_vtb_tb_rpt_slot_START  (0)
#define CBBP_VTB_TB_RPT_SLOT_vtb_tb_rpt_slot_END    (8)


/*****************************************************************************
 结构名    : CBBP_DLDEC_OVERTIME_CFG_UNION
 结构说明  : DLDEC_OVERTIME_CFG 寄存器结构定义。地址偏移量:0x04C，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_overtime_cfg_reg;
    struct
    {
        unsigned long  dldec_overtime_cfg : 6;  /* bit[0-5] : 译码模块超时周期配置值，0值不可配置，实际超时周期值为dldec_overtime_cfg *8192，，推荐配置值为16 */
        unsigned long  reserved_0         : 2;  /* bit[6-7] : 保留 */
        unsigned long  dldec_overtime_en  : 1;  /* bit[8]   : 译码超时保护使能 */
        unsigned long  reserved_1         : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_DLDEC_OVERTIME_CFG_UNION;
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_cfg_START  (0)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_cfg_END    (5)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_en_START   (8)
#define CBBP_DLDEC_OVERTIME_CFG_dldec_overtime_en_END     (8)


/*****************************************************************************
 结构名    : CBBP_TURBO_ITER_NUM_C_UNION
 结构说明  : TURBO_ITER_NUM_C 寄存器结构定义。地址偏移量:0x050，初值:0x00011009，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_iter_num_c_reg;
    struct
    {
        unsigned long  c_turbo_min_iter_num : 4;  /* bit[0-3]  : Turbo译码的最小处理次数，例如配置成9代表最少需要9次处理才会停止迭代 */
        unsigned long  reserved_0           : 4;  /* bit[4-7]  : 保留 */
        unsigned long  c_turbo_max_iter_num : 5;  /* bit[8-12] : Turbo译码的最大处理次数，例如配置成16代表最多16次处理（无论是否收敛都停止迭代） */
        unsigned long  reserved_1           : 3;  /* bit[13-15]: 保留 */
        unsigned long  c_tc_crcok_stop_en   : 1;  /* bit[16]   : Turbo译码器CRC正确提前停止迭代使能0：禁止
                                                                 1：使能 */
        unsigned long  reserved_2           : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_TURBO_ITER_NUM_C_UNION;
#define CBBP_TURBO_ITER_NUM_C_c_turbo_min_iter_num_START  (0)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_min_iter_num_END    (3)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_max_iter_num_START  (8)
#define CBBP_TURBO_ITER_NUM_C_c_turbo_max_iter_num_END    (12)
#define CBBP_TURBO_ITER_NUM_C_c_tc_crcok_stop_en_START    (16)
#define CBBP_TURBO_ITER_NUM_C_c_tc_crcok_stop_en_END      (16)


/*****************************************************************************
 结构名    : CBBP_TURBO_SCALE_1_4_C_UNION
 结构说明  : TURBO_SCALE_1_4_C 寄存器结构定义。地址偏移量:0x054，初值:0x29292323，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_1_4_c_reg;
    struct
    {
        unsigned long  c_turbo_scale01 : 6;  /* bit[0-5]  : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : 保留 */
        unsigned long  c_turbo_scale02 : 6;  /* bit[8-13] : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: 保留 */
        unsigned long  c_turbo_scale03 : 6;  /* bit[16-21]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: 保留 */
        unsigned long  c_turbo_scale04 : 6;  /* bit[24-29]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_TURBO_SCALE_1_4_C_UNION;
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale01_START  (0)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale01_END    (5)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale02_START  (8)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale02_END    (13)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale03_START  (16)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale03_END    (21)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale04_START  (24)
#define CBBP_TURBO_SCALE_1_4_C_c_turbo_scale04_END    (29)


/*****************************************************************************
 结构名    : CBBP_TURBO_SCALE_5_8_C_UNION
 结构说明  : TURBO_SCALE_5_8_C 寄存器结构定义。地址偏移量:0x058，初值:0x30302C2C，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_5_8_c_reg;
    struct
    {
        unsigned long  c_turbo_scale05 : 6;  /* bit[0-5]  : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : 保留 */
        unsigned long  c_turbo_scale06 : 6;  /* bit[8-13] : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: 保留 */
        unsigned long  c_turbo_scale07 : 6;  /* bit[16-21]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: 保留 */
        unsigned long  c_turbo_scale08 : 6;  /* bit[24-29]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_TURBO_SCALE_5_8_C_UNION;
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale05_START  (0)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale05_END    (5)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale06_START  (8)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale06_END    (13)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale07_START  (16)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale07_END    (21)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale08_START  (24)
#define CBBP_TURBO_SCALE_5_8_C_c_turbo_scale08_END    (29)


/*****************************************************************************
 结构名    : CBBP_TURBO_SCALE_9_12_C_UNION
 结构说明  : TURBO_SCALE_9_12_C 寄存器结构定义。地址偏移量:0x05C，初值:0x33333030，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_9_12_c_reg;
    struct
    {
        unsigned long  c_turbo_scale09 : 6;  /* bit[0-5]  : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : 保留 */
        unsigned long  c_turbo_scale10 : 6;  /* bit[8-13] : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: 保留 */
        unsigned long  c_turbo_scale11 : 6;  /* bit[16-21]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: 保留 */
        unsigned long  c_turbo_scale12 : 6;  /* bit[24-29]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_TURBO_SCALE_9_12_C_UNION;
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale09_START  (0)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale09_END    (5)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale10_START  (8)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale10_END    (13)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale11_START  (16)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale11_END    (21)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale12_START  (24)
#define CBBP_TURBO_SCALE_9_12_C_c_turbo_scale12_END    (29)


/*****************************************************************************
 结构名    : CBBP_TURBO_SCALE_13_16_C_UNION
 结构说明  : TURBO_SCALE_13_16_C 寄存器结构定义。地址偏移量:0x060，初值:0x39393636，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_scale_13_16_c_reg;
    struct
    {
        unsigned long  c_turbo_scale13 : 6;  /* bit[0-5]  : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_0      : 2;  /* bit[6-7]  : 保留 */
        unsigned long  c_turbo_scale14 : 6;  /* bit[8-13] : 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_1      : 2;  /* bit[14-15]: 保留 */
        unsigned long  c_turbo_scale15 : 6;  /* bit[16-21]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_2      : 2;  /* bit[22-23]: 保留 */
        unsigned long  c_turbo_scale16 : 6;  /* bit[24-29]: 16个scale因子，每个因子位宽6bit
                                                            SISO1：sf[i]=sf[2i-2]，（1<=i<=8）； sf[i]=sf[14]，（9<=i<=16），其中i为迭代次数
                                                            SISO2： sf[i]=sf[2i-1]，（1<=i<=8）； sf[i]=sf[15]，（9<=i<=16），其中i为迭代次数 */
        unsigned long  reserved_3      : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_TURBO_SCALE_13_16_C_UNION;
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale13_START  (0)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale13_END    (5)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale14_START  (8)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale14_END    (13)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale15_START  (16)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale15_END    (21)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale16_START  (24)
#define CBBP_TURBO_SCALE_13_16_C_c_turbo_scale16_END    (29)


/*****************************************************************************
 结构名    : CBBP_HARQ_COMB_SHIFT_IND_UNION
 结构说明  : HARQ_COMB_SHIFT_IND 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      harq_comb_shift_ind_reg;
    struct
    {
        unsigned long  harq_comb_shift_ind : 1;  /* bit[0]   : 1，表示EVDO HARQ合并后四舍五入1位再饱和至6位；否则直接饱和至6位。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_HARQ_COMB_SHIFT_IND_UNION;
#define CBBP_HARQ_COMB_SHIFT_IND_harq_comb_shift_ind_START  (0)
#define CBBP_HARQ_COMB_SHIFT_IND_harq_comb_shift_ind_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_WR_LLR_ORIG_UNION
 结构说明  : DLDEC_WR_LLR_ORIG 寄存器结构定义。地址偏移量:0x068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_llr_orig_reg;
    struct
    {
        unsigned long  dldec_wr_llr_orig : 2;  /* bit[0-1] : LLR下发数据类型指示。0，表示SDR处理器下发的解调后LLR信息；1，表示1X模式下完成解交织解打孔解重复后的LLR信息，也即VTB译码前LLR信息；2，表示EVDO模式下某个进程的HARQ后的LLR信息（此信息同时也是用于TURBO译码前的LLR信息）； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_DLDEC_WR_LLR_ORIG_UNION;
#define CBBP_DLDEC_WR_LLR_ORIG_dldec_wr_llr_orig_START  (0)
#define CBBP_DLDEC_WR_LLR_ORIG_dldec_wr_llr_orig_END    (1)


/*****************************************************************************
 结构名    : CBBP_DLDEC_WR_WATERLINE_UNION
 结构说明  : DLDEC_WR_WATERLINE 寄存器结构定义。地址偏移量:0x06C，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_waterline_reg;
    struct
    {
        unsigned long  dldec_wr_waterline : 5;  /* bit[0-4] : 译码前LLR下发水线，也即下发LLR时的burst类型，不支持配置为1。典型配置为2/4/8/16。例如16，表示LLR下发为burst16类型,DMA数据位宽必须为64。 */
        unsigned long  reserved           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_DLDEC_WR_WATERLINE_UNION;
#define CBBP_DLDEC_WR_WATERLINE_dldec_wr_waterline_START  (0)
#define CBBP_DLDEC_WR_WATERLINE_dldec_wr_waterline_END    (4)


/*****************************************************************************
 结构名    : CBBP_DLDEC_RD_LLR_ORIG_UNION
 结构说明  : DLDEC_RD_LLR_ORIG 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_llr_orig_reg;
    struct
    {
        unsigned long  dldec_rd_llr_orig : 2;  /* bit[0-1] : LLR上报数据类型指示。0，表示SDR处理器上报解调后LLR信息；1，表示EVDO模式下上报某个进程的HARQ后的LLR信息（此信息同时也是用于TURBO译码前的LLR信息）；2，表示1X模式下完成解交织解打孔解重复后的LLR信息上报； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_DLDEC_RD_LLR_ORIG_UNION;
#define CBBP_DLDEC_RD_LLR_ORIG_dldec_rd_llr_orig_START  (0)
#define CBBP_DLDEC_RD_LLR_ORIG_dldec_rd_llr_orig_END    (1)


/*****************************************************************************
 结构名    : CBBP_DLDEC_RD_WATERLINE_UNION
 结构说明  : DLDEC_RD_WATERLINE 寄存器结构定义。地址偏移量:0x074，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_waterline_reg;
    struct
    {
        unsigned long  dldec_rd_waterline : 5;  /* bit[0-4] : LLR回读水线，也即回读时总线burst类型，不支持配置为1。典型配置为2/4/8/16。例如16，表示LLR回读为burst16类型，DMA数据位宽必须为64。 */
        unsigned long  reserved           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_DLDEC_RD_WATERLINE_UNION;
#define CBBP_DLDEC_RD_WATERLINE_dldec_rd_waterline_START  (0)
#define CBBP_DLDEC_RD_WATERLINE_dldec_rd_waterline_END    (4)


/*****************************************************************************
 结构名    : CBBP_LLR_TRANS_FLAG_UNION
 结构说明  : LLR_TRANS_FLAG 寄存器结构定义。地址偏移量:0x07C，初值:0x00001010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_trans_flag_reg;
    struct
    {
        unsigned long  dldec_wr_chnl_full  : 1;  /* bit[0]    : 下发LLR通道满状态上报 */
        unsigned long  reserved_0          : 3;  /* bit[1-3]  : 保留 */
        unsigned long  dldec_wr_chnl_empty : 1;  /* bit[4]    : 下发LLR通道空状态上报 */
        unsigned long  reserved_1          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  dldec_rd_chnl_full  : 1;  /* bit[8]    : 回读LLR通道满状态上报 */
        unsigned long  reserved_2          : 3;  /* bit[9-11] : 保留 */
        unsigned long  dldec_rd_chnl_empty : 1;  /* bit[12]   : 回读LLR通道空状态上报 */
        unsigned long  reserved_3          : 3;  /* bit[13-15]: 保留 */
        unsigned long  dldec_dma_wr_breq   : 1;  /* bit[16]   : DMA写请求状态上报 */
        unsigned long  reserved_4          : 3;  /* bit[17-19]: 保留 */
        unsigned long  dldec_dma_rd_breq   : 1;  /* bit[20]   : DMA读请求状态上报 */
        unsigned long  reserved_5          : 11; /* bit[21-31]: 保留 */
    } reg;
} CBBP_LLR_TRANS_FLAG_UNION;
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_full_START   (0)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_full_END     (0)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_empty_START  (4)
#define CBBP_LLR_TRANS_FLAG_dldec_wr_chnl_empty_END    (4)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_full_START   (8)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_full_END     (8)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_empty_START  (12)
#define CBBP_LLR_TRANS_FLAG_dldec_rd_chnl_empty_END    (12)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_wr_breq_START    (16)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_wr_breq_END      (16)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_rd_breq_START    (20)
#define CBBP_LLR_TRANS_FLAG_dldec_dma_rd_breq_END      (20)


/*****************************************************************************
 结构名    : CBBP_BLER_ENABLE_UNION
 结构说明  : BLER_ENABLE 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bler_enable_reg;
    struct
    {
        unsigned long  dldec_bler_en : 1;  /* bit[0]   : 译码bler可维可测统计使能 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BLER_ENABLE_UNION;
#define CBBP_BLER_ENABLE_dldec_bler_en_START  (0)
#define CBBP_BLER_ENABLE_dldec_bler_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_STATE_UNION
 结构说明  : DLDEC_STATE 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_state_reg;
    struct
    {
        unsigned long  dldec_state         : 4;  /* bit[0-3] : 译码状态机上报 */
        unsigned long  dldec_overtime_flag : 1;  /* bit[4]   : 译码超时标志 */
        unsigned long  reserved_0          : 3;  /* bit[5-7] : 保留 */
        unsigned long  c_vtb_busy          : 1;  /* bit[8]   : vtb译码忙标志 */
        unsigned long  reserved_1          : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_DLDEC_STATE_UNION;
#define CBBP_DLDEC_STATE_dldec_state_START          (0)
#define CBBP_DLDEC_STATE_dldec_state_END            (3)
#define CBBP_DLDEC_STATE_dldec_overtime_flag_START  (4)
#define CBBP_DLDEC_STATE_dldec_overtime_flag_END    (4)
#define CBBP_DLDEC_STATE_c_vtb_busy_START           (8)
#define CBBP_DLDEC_STATE_c_vtb_busy_END             (8)


/*****************************************************************************
 结构名    : CBBP_LLR_CLIP_IND_UNION
 结构说明  : LLR_CLIP_IND 寄存器结构定义。地址偏移量:0x094，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_clip_ind_reg;
    struct
    {
        unsigned long  dldec_trans_llr_clip_ind : 1;  /* bit[0]   : LLR下发四舍五入指示，为1表示8位LLR四舍五入1位再饱和至6位，为0表示直接截取低6位。如果是LLR首次下发，则需要配置为1；如果是回读前次译码的LLR值，因为已经是6位，故再次下发时不需要处理，此时配置为0。 */
        unsigned long  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_LLR_CLIP_IND_UNION;
#define CBBP_LLR_CLIP_IND_dldec_trans_llr_clip_ind_START  (0)
#define CBBP_LLR_CLIP_IND_dldec_trans_llr_clip_ind_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_REPEAT_MODE_UNION
 结构说明  : DLDEC_REPEAT_MODE 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_repeat_mode_reg;
    struct
    {
        unsigned long  dldec_repeat_mode : 1;  /* bit[0]   : 重复模式选择，0表示FIX DATA RATE重复模式，1表示flexible重复模式。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_REPEAT_MODE_UNION;
#define CBBP_DLDEC_REPEAT_MODE_dldec_repeat_mode_START  (0)
#define CBBP_DLDEC_REPEAT_MODE_dldec_repeat_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_LLR_RD_START_UNION
 结构说明  : DLDEC_LLR_RD_START 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_llr_rd_start_reg;
    struct
    {
        unsigned long  dldec_llr_rd_start : 1;  /* bit[0]   : LLR回读启动脉冲，只有在译码完成后或不在译码状态时才可配置。寻呼信道或同步信道在译码中断后配置。 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_LLR_RD_START_UNION;
#define CBBP_DLDEC_LLR_RD_START_dldec_llr_rd_start_START  (0)
#define CBBP_DLDEC_LLR_RD_START_dldec_llr_rd_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_NEW_BLK_IND_UNION
 结构说明  : DLDEC_NEW_BLK_IND 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_new_blk_ind_reg;
    struct
    {
        unsigned long  dldec_new_blk_ind : 1;  /* bit[0]   : EVDO新码块指示，1表示该码块为新数据；0，表示旧数据 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_NEW_BLK_IND_UNION;
#define CBBP_DLDEC_NEW_BLK_IND_dldec_new_blk_ind_START  (0)
#define CBBP_DLDEC_NEW_BLK_IND_dldec_new_blk_ind_END    (0)


/*****************************************************************************
 结构名    : CBBP_RPT_MODE_UNION
 结构说明  : RPT_MODE 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rpt_mode_reg;
    struct
    {
        unsigned long  dldec_rpt_mode           : 1;  /* bit[0]   : 上报模式，1表示小端模式；0表示大端模式 */
        unsigned long  reserved_0               : 3;  /* bit[1-3] : 保留 */
        unsigned long  dldec_reserve_bit_rpt_en : 1;  /* bit[4]   : reserve比特上报使能，1表示上报reserve比特；0表示不上报 */
        unsigned long  reserved_1               : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_RPT_MODE_UNION;
#define CBBP_RPT_MODE_dldec_rpt_mode_START            (0)
#define CBBP_RPT_MODE_dldec_rpt_mode_END              (0)
#define CBBP_RPT_MODE_dldec_reserve_bit_rpt_en_START  (4)
#define CBBP_RPT_MODE_dldec_reserve_bit_rpt_en_END    (4)


/*****************************************************************************
 结构名    : CBBP_DLDEC_WR_LENGTH_UNION
 结构说明  : DLDEC_WR_LENGTH 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_wr_length_reg;
    struct
    {
        unsigned long  dldec_wr_length : 13; /* bit[0-12] : 软件下发LLR个数，为实际LLR个数除以4，再向上取整。 */
        unsigned long  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_DLDEC_WR_LENGTH_UNION;
#define CBBP_DLDEC_WR_LENGTH_dldec_wr_length_START  (0)
#define CBBP_DLDEC_WR_LENGTH_dldec_wr_length_END    (12)


/*****************************************************************************
 结构名    : CBBP_DLDEC_RD_LENGTH_UNION
 结构说明  : DLDEC_RD_LENGTH 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rd_length_reg;
    struct
    {
        unsigned long  dldec_rd_length : 13; /* bit[0-12] : 软件回读LLR个数，为实际LLR个数除以4，再向上取整。 */
        unsigned long  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_DLDEC_RD_LENGTH_UNION;
#define CBBP_DLDEC_RD_LENGTH_dldec_rd_length_START  (0)
#define CBBP_DLDEC_RD_LENGTH_dldec_rd_length_END    (12)


/*****************************************************************************
 结构名    : CBBP_CRC_RPT_UNION
 结构说明  : CRC_RPT 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      crc_rpt_reg;
    struct
    {
        unsigned long  dldec_crc_bit_rpt : 24; /* bit[0-23] : CRC校验比特上报 */
        unsigned long  reserved          : 7;  /* bit[24-30]: 保留 */
        unsigned long  dldec_crc_result  : 1;  /* bit[31]   : CRC校验结果上报 */
    } reg;
} CBBP_CRC_RPT_UNION;
#define CBBP_CRC_RPT_dldec_crc_bit_rpt_START  (0)
#define CBBP_CRC_RPT_dldec_crc_bit_rpt_END    (23)
#define CBBP_CRC_RPT_dldec_crc_result_START   (31)
#define CBBP_CRC_RPT_dldec_crc_result_END     (31)


/*****************************************************************************
 结构名    : CBBP_LLR_READY_UNION
 结构说明  : LLR_READY 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_ready_reg;
    struct
    {
        unsigned long  dldec_llr_wr_ready : 1;  /* bit[0]   : 测试模式时，软件不通过DMA，直接通过总线下发LLR软值。1表示有一个BURST的LLR可以下发。0，表示LLR不能下发。 */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned long  dldec_llr_rd_ready : 1;  /* bit[4]   : 测试模式时，软件不通过DMA，直接通过总线读取LLR软值。1表示有一个BURST的LLR可以读取。0，表示没有LLR可读取。 */
        unsigned long  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_LLR_READY_UNION;
#define CBBP_LLR_READY_dldec_llr_wr_ready_START  (0)
#define CBBP_LLR_READY_dldec_llr_wr_ready_END    (0)
#define CBBP_LLR_READY_dldec_llr_rd_ready_START  (4)
#define CBBP_LLR_READY_dldec_llr_rd_ready_END    (4)


/*****************************************************************************
 结构名    : CBBP_LLR_READY_CLR_UNION
 结构说明  : LLR_READY_CLR 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_ready_clr_reg;
    struct
    {
        unsigned long  dldec_llr_wr_ready_clr : 1;  /* bit[0]   : 测试模式时，软件可不通过DMA，直接通过总线下发LLR软值。当下发完一个burst数据时，产生该清脉冲，把dldec_llr_wr_ready_clr清0 */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : 保留 */
        unsigned long  dldec_llr_rd_ready_clr : 1;  /* bit[4]   : 测试模式时，软件可不通过DMA，直接通过总线读取LLR软值。当读完一个burst数据时，产生该脉冲,把dldec_llr_rd_ready清0 */
        unsigned long  reserved_1             : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_LLR_READY_CLR_UNION;
#define CBBP_LLR_READY_CLR_dldec_llr_wr_ready_clr_START  (0)
#define CBBP_LLR_READY_CLR_dldec_llr_wr_ready_clr_END    (0)
#define CBBP_LLR_READY_CLR_dldec_llr_rd_ready_clr_START  (4)
#define CBBP_LLR_READY_CLR_dldec_llr_rd_ready_clr_END    (4)


/*****************************************************************************
 结构名    : CBBP_C_VTB_ST_RPT_UNION
 结构说明  : C_VTB_ST_RPT 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_vtb_st_rpt_reg;
    struct
    {
        unsigned long  c_vtb_st_rpt : 8;  /* bit[0-7] : vtb状态上报，用于下一次vtb译码状态度量初始化。在本次译码中断后下次译码启动前有效。 */
        unsigned long  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} CBBP_C_VTB_ST_RPT_UNION;
#define CBBP_C_VTB_ST_RPT_c_vtb_st_rpt_START  (0)
#define CBBP_C_VTB_ST_RPT_c_vtb_st_rpt_END    (7)


/*****************************************************************************
 结构名    : CBBP_C2TUBO_BASE_ADDR_UNION
 结构说明  : C2TUBO_BASE_ADDR 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c2tubo_base_addr_reg;
    struct
    {
        unsigned long  c2tubo_base_addr : 12; /* bit[0-11] : 盲检测或HARQ重传时turbo译码前数据的偏移地址。HARQ重传时，根据进程号计算，例如0进程时，该地址配置为0；进程n，则配置为641*n，支持最大4个进程。盲检测时，根据实际LLR数据长度计算。 */
        unsigned long  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_C2TUBO_BASE_ADDR_UNION;
#define CBBP_C2TUBO_BASE_ADDR_c2tubo_base_addr_START  (0)
#define CBBP_C2TUBO_BASE_ADDR_c2tubo_base_addr_END    (11)


/*****************************************************************************
 结构名    : CBBP_DLDEC_CKG_BYPASS_UNION
 结构说明  : DLDEC_CKG_BYPASS 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ckg_bypass_reg;
    struct
    {
        unsigned long  dldec_ckg_bypass : 9;  /* bit[0-8] : 时钟门控旁路使能 */
        unsigned long  reserved         : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_DLDEC_CKG_BYPASS_UNION;
#define CBBP_DLDEC_CKG_BYPASS_dldec_ckg_bypass_START  (0)
#define CBBP_DLDEC_CKG_BYPASS_dldec_ckg_bypass_END    (8)


/*****************************************************************************
 结构名    : CBBP_DLDEC_BER_EN_UNION
 结构说明  : DLDEC_BER_EN 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ber_en_reg;
    struct
    {
        unsigned long  dldec_ber_en : 1;  /* bit[0]   : BER统计使能 */
        unsigned long  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_BER_EN_UNION;
#define CBBP_DLDEC_BER_EN_dldec_ber_en_START  (0)
#define CBBP_DLDEC_BER_EN_dldec_ber_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLDEC_RFPUN_EN_UNION
 结构说明  : DLDEC_RFPUN_EN 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_rfpun_en_reg;
    struct
    {
        unsigned long  dldec_rfpun_en : 1;  /* bit[0]   : 当重复率为1时，ber统计需要计算打孔位置，此时，该信号配1。否则，配0。 */
        unsigned long  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLDEC_RFPUN_EN_UNION;
#define CBBP_DLDEC_RFPUN_EN_dldec_rfpun_en_START  (0)
#define CBBP_DLDEC_RFPUN_EN_dldec_rfpun_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_C_BLID_CM0_UNION
 结构说明  : C_BLID_CM0 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm0_reg;
    struct
    {
        unsigned long  c_blid_cm0 : 13; /* bit[0-12] : 最后时刻幸存路径度量值与零状态度量值之差 */
        unsigned long  reserved   : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_C_BLID_CM0_UNION;
#define CBBP_C_BLID_CM0_c_blid_cm0_START  (0)
#define CBBP_C_BLID_CM0_c_blid_cm0_END    (12)


/*****************************************************************************
 结构名    : CBBP_C_BLID_CM1_UNION
 结构说明  : C_BLID_CM1 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm1_reg;
    struct
    {
        unsigned long  c_blid_cm1 : 13; /* bit[0-12] : 最后时刻幸存路径度量值与次优路径度量值之差 */
        unsigned long  reserved   : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_C_BLID_CM1_UNION;
#define CBBP_C_BLID_CM1_c_blid_cm1_START  (0)
#define CBBP_C_BLID_CM1_c_blid_cm1_END    (12)


/*****************************************************************************
 结构名    : CBBP_C_BLID_CM2_UNION
 结构说明  : C_BLID_CM2 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      c_blid_cm2_reg;
    struct
    {
        unsigned long  c_blid_cm2 : 13; /* bit[0-12] : C模盲译码最后时刻次优路径度量值上报 */
        unsigned long  reserved   : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_C_BLID_CM2_UNION;
#define CBBP_C_BLID_CM2_c_blid_cm2_START  (0)
#define CBBP_C_BLID_CM2_c_blid_cm2_END    (12)


/*****************************************************************************
 结构名    : CBBP_DLDEC_BER_UNION
 结构说明  : DLDEC_BER 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_ber_reg;
    struct
    {
        unsigned long  dldec_ber : 15; /* bit[0-14] : 盲检测BER错误bit数统计结果 */
        unsigned long  reserved  : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_DLDEC_BER_UNION;
#define CBBP_DLDEC_BER_dldec_ber_START  (0)
#define CBBP_DLDEC_BER_dldec_ber_END    (14)


/*****************************************************************************
 结构名    : CBBP_DLDEC_TOTAL_BERBIT_UNION
 结构说明  : DLDEC_TOTAL_BERBIT 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dldec_total_berbit_reg;
    struct
    {
        unsigned long  dldec_total_berbit : 15; /* bit[0-14] : 盲检测用于统计BER的总比特数 */
        unsigned long  reserved           : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_DLDEC_TOTAL_BERBIT_UNION;
#define CBBP_DLDEC_TOTAL_BERBIT_dldec_total_berbit_START  (0)
#define CBBP_DLDEC_TOTAL_BERBIT_dldec_total_berbit_END    (14)


/*****************************************************************************
 结构名    : CBBP_BIT_ORDER_REVERSE_UNION
 结构说明  : BIT_ORDER_REVERSE 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      bit_order_reverse_reg;
    struct
    {
        unsigned long  bit_order_reverse : 1;  /* bit[0]   : byte内大小端指示。0表示小端模式，即byte内最低位放低位数据。1表示大端模式，byte内最低位放最高位数据。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BIT_ORDER_REVERSE_UNION;
#define CBBP_BIT_ORDER_REVERSE_bit_order_reverse_START  (0)
#define CBBP_BIT_ORDER_REVERSE_bit_order_reverse_END    (0)


/*****************************************************************************
 结构名    : CBBP_TURBO_ITER_NUM_W_SDR_UNION
 结构说明  : TURBO_ITER_NUM_W_SDR 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000011，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      turbo_iter_num_w_sdr_reg;
    struct
    {
        unsigned long  wsdr_turbo_iter_over_en    : 1;  /* bit[0]   : W模软化Turbo译码器提前停止迭代使能0：禁止
                                                                      1：使能 */
        unsigned long  reserved_0                 : 3;  /* bit[1-3] : 保留 */
        unsigned long  wsdr_conv_judge_enhance_en : 1;  /* bit[4]   : W模软化turbo译码器收敛判断方法的切换开关，默认打开
                                                                      0：比较连续两次的迭代处理结果，一致则认为收敛；
                                                                      1：比较连续三次的迭代处理结果，一致则认为收敛； */
        unsigned long  reserved_1                 : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_TURBO_ITER_NUM_W_SDR_UNION;
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_turbo_iter_over_en_START     (0)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_turbo_iter_over_en_END       (0)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_conv_judge_enhance_en_START  (4)
#define CBBP_TURBO_ITER_NUM_W_SDR_wsdr_conv_judge_enhance_en_END    (4)


/*****************************************************************************
 结构名    : CBBP_BLIND_DETECT_IND_UNION
 结构说明  : BLIND_DETECT_IND 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      blind_detect_ind_reg;
    struct
    {
        unsigned long  blind_detect_ind : 1;  /* bit[0]   : 1X或EVDO时盲检测指示，1表示当前码块需要进行盲检测译码 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_BLIND_DETECT_IND_UNION;
#define CBBP_BLIND_DETECT_IND_blind_detect_ind_START  (0)
#define CBBP_BLIND_DETECT_IND_blind_detect_ind_END    (0)


/*****************************************************************************
 结构名    : CBBP_CPU_ACCESS_LLR_MODE_UNION
 结构说明  : CPU_ACCESS_LLR_MODE 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_access_llr_mode_reg;
    struct
    {
        unsigned long  cpu_access_llr_rd_mode : 1;  /* bit[0]   : CPU直接读取LLR模式，此时不通过DMA读取数据，BBP DMA请求不拉高。 */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_access_llr_wr_mode : 1;  /* bit[4]   : CPU直接下发LLR模式，此时不通过DMA下发数据，BBP DMA请求不拉高。 */
        unsigned long  reserved_1             : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_CPU_ACCESS_LLR_MODE_UNION;
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_rd_mode_START  (0)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_rd_mode_END    (0)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_wr_mode_START  (4)
#define CBBP_CPU_ACCESS_LLR_MODE_cpu_access_llr_wr_mode_END    (4)


/*****************************************************************************
 结构名    : CBBP_LLR_TRANS_MODE_UNION
 结构说明  : LLR_TRANS_MODE 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      llr_trans_mode_reg;
    struct
    {
        unsigned long  llr_trans_mode : 2;  /* bit[0-1] : LLR数据下发模式指示:0，表示DMA burst下发模式；1，表示DMA FLASH模式；2，表示BBPMST模式。
                                                          DMA FLASH模式和BBPMST模式不支持纯TURBO LLR数据下发。 */
        unsigned long  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_LLR_TRANS_MODE_UNION;
#define CBBP_LLR_TRANS_MODE_llr_trans_mode_START  (0)
#define CBBP_LLR_TRANS_MODE_llr_trans_mode_END    (1)


/***======================================================================***
                     (11/20) register_define_c_dldec_mem
 ***======================================================================***/
/***======================================================================***
                     (12/20) register_define_c_ulcode
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_ULCODE_EN_UNION
 结构说明  : ULCODE_EN 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_en_reg;
    struct
    {
        unsigned long  cpu_ulcode_en : 1;  /* bit[0]   : 上行编码模块使能，必须在所有上行编码参数配置完成后配置为1。 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_EN_UNION;
#define CBBP_ULCODE_EN_cpu_ulcode_en_START  (0)
#define CBBP_ULCODE_EN_cpu_ulcode_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_START_UNION
 结构说明  : ULCODE_START 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_start_reg;
    struct
    {
        unsigned long  cpu_ulcode_start : 1;  /* bit[0]   : 上行编码启动信号，必须在所有上行编码参数和上行编码建立使能配置完成后配置 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_START_UNION;
#define CBBP_ULCODE_START_cpu_ulcode_start_START  (0)
#define CBBP_ULCODE_START_cpu_ulcode_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_BIT_MODE_UNION
 结构说明  : ULCODE_BIT_MODE 寄存器结构定义。地址偏移量:0x0008，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_bit_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_bit_mode          : 1;  /* bit[0]    : 编码数据下发格式和编码后数据上报格式；1：表示小端模式（默认模式），0：表示大端模式；默认值：1； */
        unsigned long  reserved_0                   : 15; /* bit[1-15] : 保留 */
        unsigned long  cpu_ulcode_bit_order_reverse : 1;  /* bit[16]   : 编码数据下发小端比特逆序格式；1：表示小端比特逆序模式生效，0：表示小端比特逆序模式无效；默认值：0；
                                                                         编码数据下发小端比特逆序模式和小端模式不能同时生效；此配置对编码后数据上报格式无影响。 */
        unsigned long  reserved_1                   : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_ULCODE_BIT_MODE_UNION;
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_mode_START           (0)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_mode_END             (0)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_order_reverse_START  (16)
#define CBBP_ULCODE_BIT_MODE_cpu_ulcode_bit_order_reverse_END    (16)


/*****************************************************************************
 结构名    : CBBP_ULCODE_RESERVE_BIT_UNION
 结构说明  : ULCODE_RESERVE_BIT 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_reserve_bit_reg;
    struct
    {
        unsigned long  cpu_ulcode_reserve_bit_exist_ind : 1;  /* bit[0]    : 1X模式下Reverse bit添加使能开关；EVDO模式下该参数配置为0。 */
        unsigned long  reserved_0                       : 15; /* bit[1-15] : 保留 */
        unsigned long  cpu_ulcode_reserve_bit_value     : 1;  /* bit[16]   : Reverse bit的取值；取值0或1。 */
        unsigned long  reserved_1                       : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_ULCODE_RESERVE_BIT_UNION;
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_exist_ind_START  (0)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_exist_ind_END    (0)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_value_START      (16)
#define CBBP_ULCODE_RESERVE_BIT_cpu_ulcode_reserve_bit_value_END        (16)


/*****************************************************************************
 结构名    : CBBP_ULCODE_TRAFFIC_TYPE_UNION
 结构说明  : ULCODE_TRAFFIC_TYPE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_traffic_type_reg;
    struct
    {
        unsigned long  cpu_ulcode_traffic_type : 1;  /* bit[0]   : 通信模式类型指示；1：EVDO，0:1X；默认值：0。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_TRAFFIC_TYPE_UNION;
#define CBBP_ULCODE_TRAFFIC_TYPE_cpu_ulcode_traffic_type_START  (0)
#define CBBP_ULCODE_TRAFFIC_TYPE_cpu_ulcode_traffic_type_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_CODER_PARA_UNION
 结构说明  : ULCODE_CODER_PARA 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_coder_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_coder_type : 1;  /* bit[0]    : 编码器类型指示；1：TURBO，0:VTB；
                                                                  默认值：0。 */
        unsigned long  reserved_0            : 15; /* bit[1-15] : 保留 */
        unsigned long  cpu_ulcode_coder_rate : 3;  /* bit[16-18]: 上行编码器编码率；
                                                                  2：1/2；
                                                                  3：1/3；
                                                                  4：1/4；
                                                                  5：1/5；（卷积编码无1/5）。 */
        unsigned long  reserved_1            : 13; /* bit[19-31]: 保留 */
    } reg;
} CBBP_ULCODE_CODER_PARA_UNION;
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_type_START  (0)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_type_END    (0)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_rate_START  (16)
#define CBBP_ULCODE_CODER_PARA_cpu_ulcode_coder_rate_END    (18)


/*****************************************************************************
 结构名    : CBBP_ULCODE_LEN_PARA1_UNION
 结构说明  : ULCODE_LEN_PARA1 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_len_para1_reg;
    struct
    {
        unsigned long  cpu_ulcode_info_len : 14; /* bit[0-13] : 信息位长度；
                                                                卷积编码下不含CRC、Reverse bit、TAIL bit 长度；TURBO编码下不含“00”，CRC、Reverse bit、TAIL bit 长度。 */
        unsigned long  reserved            : 18; /* bit[14-31]: 保留 */
    } reg;
} CBBP_ULCODE_LEN_PARA1_UNION;
#define CBBP_ULCODE_LEN_PARA1_cpu_ulcode_info_len_START  (0)
#define CBBP_ULCODE_LEN_PARA1_cpu_ulcode_info_len_END    (13)


/*****************************************************************************
 结构名    : CBBP_ULCODE_CRC_PARA_UNION
 结构说明  : ULCODE_CRC_PARA 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_crc_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_crc_type       : 4;  /* bit[0-3]  : CRC校验类型：
                                                                      0:CRC-0；
                                                                      1:CRC-16-1；
                                                                      2:CRC-12；
                                                                      3:CRC-10；
                                                                      4:CRC-8；
                                                                      5:CRC-6-1；
                                                                      6:CRC-6-2；
                                                                      7:CRC-24；
                                                                      8:CRC-16-2；
                                                                      默认值：0。 */
        unsigned long  reserved_0                : 12; /* bit[4-15] : 保留 */
        unsigned long  cpu_ulcode_crc_init_state : 1;  /* bit[16]   : CRC寄存器初始化值；1：全1，0：全0；
                                                                      默认值：0。 */
        unsigned long  reserved_1                : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_ULCODE_CRC_PARA_UNION;
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_type_START        (0)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_type_END          (3)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_init_state_START  (16)
#define CBBP_ULCODE_CRC_PARA_cpu_ulcode_crc_init_state_END    (16)


/*****************************************************************************
 结构名    : CBBP_ULCODE_SCR_INIT_UNION
 结构说明  : ULCODE_SCR_INIT 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_scr_init_reg;
    struct
    {
        unsigned long  cpu_ulcode_scramble_init_state : 17; /* bit[0-16] : 扰码产生器初相；
                                                                           SDR处理器根据EVDO协议定义的扰码器初相配置给上行编码模块。
                                                                           1X下固定配置为全0。 */
        unsigned long  reserved                       : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_ULCODE_SCR_INIT_UNION;
#define CBBP_ULCODE_SCR_INIT_cpu_ulcode_scramble_init_state_START  (0)
#define CBBP_ULCODE_SCR_INIT_cpu_ulcode_scramble_init_state_END    (16)


/*****************************************************************************
 结构名    : CBBP_ULCODE_INTL_MODE_UNION
 结构说明  : ULCODE_INTL_MODE 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_intl_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_intl_mode : 3;  /* bit[0-2] : 交织器工作模式；
                                                                0： Matrix Interleave交织；
                                                                1： Symbol Permuting交织；
                                                                2：下行TYPE1 Block Interleave交织；
                                                                3：下行TYPE2 Block Interleave交织；
                                                                4：下行TYPE3 Block Interleave交织；
                                                                5：上行TYPE1 Block Interleave交织：
                                                                6：上行TYPE2 Block Interleave交织；
                                                                7：上行Reverse Interleave。 */
        unsigned long  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_ULCODE_INTL_MODE_UNION;
#define CBBP_ULCODE_INTL_MODE_cpu_ulcode_intl_mode_START  (0)
#define CBBP_ULCODE_INTL_MODE_cpu_ulcode_intl_mode_END    (2)


/*****************************************************************************
 结构名    : CBBP_ULCODE_MATRIX_PARA_UNION
 结构说明  : ULCODE_MATRIX_PARA 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_matrix_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_matrix_intl_k_para : 3;  /* bit[0-2]  : 上行Matrix Interleave交织参数（EVDO使用）K参数。 */
        unsigned long  reserved_0                    : 5;  /* bit[3-7]  : 保留 */
        unsigned long  cpu_ulcode_matrix_intl_m_para : 4;  /* bit[8-11] : 上行Matrix Interleave交织参数（EVDO使用）M参数。V0/V0`，V1/V1`硬件使用时自行加1处理。 */
        unsigned long  reserved_1                    : 4;  /* bit[12-15]: 保留 */
        unsigned long  cpu_ulcode_matrix_intl_r_para : 3;  /* bit[16-18]: 上行Matrix Interleave交织参数（EVDO使用）R参数。 */
        unsigned long  reserved_2                    : 5;  /* bit[19-23]: 保留 */
        unsigned long  cpu_ulcode_matrix_intl_d_para : 4;  /* bit[24-27]: 上行Matrix Interleave交织参数（EVDO使用）D参数（兼顾下行译码需求）。 */
        unsigned long  reserved_3                    : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_ULCODE_MATRIX_PARA_UNION;
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_k_para_START  (0)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_k_para_END    (2)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_m_para_START  (8)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_m_para_END    (11)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_r_para_START  (16)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_r_para_END    (18)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_d_para_START  (24)
#define CBBP_ULCODE_MATRIX_PARA_cpu_ulcode_matrix_intl_d_para_END    (27)


/*****************************************************************************
 结构名    : CBBP_ULCODE_REVERSE_PARA_UNION
 结构说明  : ULCODE_REVERSE_PARA 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_reverse_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_reverse_intl_m_para : 4;  /* bit[0-3] : 上行Reverse Interleave 交织参数（EVDO使用）m参数；
                                                                          数值表示实际参与逆序位宽参数。 */
        unsigned long  reserved                       : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_ULCODE_REVERSE_PARA_UNION;
#define CBBP_ULCODE_REVERSE_PARA_cpu_ulcode_reverse_intl_m_para_START  (0)
#define CBBP_ULCODE_REVERSE_PARA_cpu_ulcode_reverse_intl_m_para_END    (3)


/*****************************************************************************
 结构名    : CBBP_ULCODE_BLOCK_PARA_UNION
 结构说明  : ULCODE_BLOCK_PARA 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_block_para_reg;
    struct
    {
        unsigned long  cpu_ulcode_ty1_blk_intl_table_sel : 2;  /* bit[0-1]  : 上行TYPE1 Block Interleave交织映射表选择；
                                                                              0：At 9600 or 14400 bps 
                                                                              1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32
                                                                              1：At 4800 or 7200 bps 
                                                                              1 3 2 4 5 7 6 8 9 11 10 12 13 15 14 16 17 19 18 20 21 23 22 24 25 27 26 28 29 31 30 32
                                                                              2：At 2400 or 3600 bps 
                                                                              1 5 2 6 3 7 4 8 9 13 10 14 11 15 12 16 17 21 18 22 19 23 20 24 25 29 26 30 27 31 28 32
                                                                              3：At 1200 or 1800 bps 
                                                                              1 9 2 10 3 11 4 12 5 13 6 14 7 15 8 16 17 25 18 26 19 27 20 28 21 29 22 30 23 31 24 32 */
        unsigned long  reserved_0                        : 14; /* bit[2-15] : 保留 */
        unsigned long  cpu_ulcode_block_intl_m_para      : 4;  /* bit[16-19]: 上行Block Interleave交织参数（1X使用）m参数。 */
        unsigned long  reserved_1                        : 4;  /* bit[20-23]: 保留 */
        unsigned long  cpu_ulcode_block_intl_j_para      : 8;  /* bit[24-31]: 上行Block Interleave交织参数（1X使用）j参数。 */
    } reg;
} CBBP_ULCODE_BLOCK_PARA_UNION;
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_ty1_blk_intl_table_sel_START  (0)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_ty1_blk_intl_table_sel_END    (1)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_m_para_START       (16)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_m_para_END         (19)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_j_para_START       (24)
#define CBBP_ULCODE_BLOCK_PARA_cpu_ulcode_block_intl_j_para_END         (31)


/*****************************************************************************
 结构名    : CBBP_ULCODE_LEN_PARA2_UNION
 结构说明  : ULCODE_LEN_PARA2 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_len_para2_reg;
    struct
    {
        unsigned long  cpu_ulcode_intl_len     : 16; /* bit[0-15] : 1X下行信道交织长度，EVDO下由硬件自行推算得到。 */
        unsigned long  cpu_ulcode_len_bef_punc : 16; /* bit[16-31]: 1X下使用，1X下即是协议定义的Symbol Repeation后长度；EVDO下由硬件自行计算得到。 */
    } reg;
} CBBP_ULCODE_LEN_PARA2_UNION;
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_intl_len_START      (0)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_intl_len_END        (15)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_len_bef_punc_START  (16)
#define CBBP_ULCODE_LEN_PARA2_cpu_ulcode_len_bef_punc_END    (31)


/*****************************************************************************
 结构名    : CBBP_ULCODE_PUNC_PATTERN_UNION
 结构说明  : ULCODE_PUNC_PATTERN 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_punc_pattern_reg;
    struct
    {
        unsigned long  cpu_ulcode_punc_pattern : 25; /* bit[0-24] : 1X下使用，1X下无打孔则配置全1，有打孔按照实际的图样配置；EVDO下硬件固定使用全1图样。 */
        unsigned long  reserved                : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_ULCODE_PUNC_PATTERN_UNION;
#define CBBP_ULCODE_PUNC_PATTERN_cpu_ulcode_punc_pattern_START  (0)
#define CBBP_ULCODE_PUNC_PATTERN_cpu_ulcode_punc_pattern_END    (24)


/*****************************************************************************
 结构名    : CBBP_ULCODE_PUNC_PATTERN_LEN_UNION
 结构说明  : ULCODE_PUNC_PATTERN_LEN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_punc_pattern_len_reg;
    struct
    {
        unsigned long  cpu_ulcode_punc_mode        : 2;  /* bit[0-1]  : 打孔模式；
                                                                        0： 根据打孔图样产生打孔信息（包括ERAM模式下需要通过打孔图样产生打孔信息的场景）；
                                                                        1：非ERAM模式下，根据公式计算打孔信息；
                                                                        2：ERAM模式下，根据公式计算打孔信息； */
        unsigned long  reserved_0                  : 14; /* bit[2-15] : 保留 */
        unsigned long  cpu_ulcode_punc_pattern_len : 5;  /* bit[16-20]: Symbol Puncture打孔图样有效长度；
                                                                        5,9,12,18,24,25即是打孔图样一个循环周期内有效指示bit数。 */
        unsigned long  reserved_1                  : 11; /* bit[21-31]: 保留 */
    } reg;
} CBBP_ULCODE_PUNC_PATTERN_LEN_UNION;
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_mode_START         (0)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_mode_END           (1)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_pattern_len_START  (16)
#define CBBP_ULCODE_PUNC_PATTERN_LEN_cpu_ulcode_punc_pattern_len_END    (20)


/*****************************************************************************
 结构名    : CBBP_ULCODE_REPEAT_MODE_UNION
 结构说明  : ULCODE_REPEAT_MODE 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_repeat_mode_reg;
    struct
    {
        unsigned long  cpu_ulcode_repeat_mode : 1;  /* bit[0-0] : 重复模式：
                                                                  0：Fix Data Rate模式下symbol repeat操作模式；
                                                                  1：Variable或Flexible Data Rate模式下 symbol repeat操作模式； */
        unsigned long  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_REPEAT_MODE_UNION;
#define CBBP_ULCODE_REPEAT_MODE_cpu_ulcode_repeat_mode_START  (0)
#define CBBP_ULCODE_REPEAT_MODE_cpu_ulcode_repeat_mode_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_OVERTIME_CFG_UNION
 结构说明  : ULCODE_OVERTIME_CFG 寄存器结构定义。地址偏移量:0x0044，初值:0x0000000F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_overtime_cfg_reg;
    struct
    {
        unsigned long  cpu_ulcode_overtime_cfg : 5;  /* bit[0-4] : 编码模块超时周期配置值，0值不可配置，实际超时周期值为ulcod_overtime_cfg*8192，推荐配置值为15（静态） */
        unsigned long  reserved                : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_ULCODE_OVERTIME_CFG_UNION;
#define CBBP_ULCODE_OVERTIME_CFG_cpu_ulcode_overtime_cfg_START  (0)
#define CBBP_ULCODE_OVERTIME_CFG_cpu_ulcode_overtime_cfg_END    (4)


/*****************************************************************************
 结构名    : CBBP_ULCODE_TIMES_EN_UNION
 结构说明  : ULCODE_TIMES_EN 寄存器结构定义。地址偏移量:0x0048，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_times_en_reg;
    struct
    {
        unsigned long  cpu_ulcode_times_en : 1;  /* bit[0]   : 上行编码统计计数使能。 */
        unsigned long  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_TIMES_EN_UNION;
#define CBBP_ULCODE_TIMES_EN_cpu_ulcode_times_en_START  (0)
#define CBBP_ULCODE_TIMES_EN_cpu_ulcode_times_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_CODER_STATUS_UNION
 结构说明  : ULCODE_CODER_STATUS 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_coder_status_reg;
    struct
    {
        unsigned long  ulcode_coder_status_cpu : 1;  /* bit[0]   : 忙或空闲状态上报；
                                                                   0：空 1：忙。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_CODER_STATUS_UNION;
#define CBBP_ULCODE_CODER_STATUS_ulcode_coder_status_cpu_START  (0)
#define CBBP_ULCODE_CODER_STATUS_ulcode_coder_status_cpu_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_OVERTIME_FLAG_UNION
 结构说明  : ULCODE_OVERTIME_FLAG 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_overtime_flag_reg;
    struct
    {
        unsigned long  ulcode_overtime_flag_cpu : 1;  /* bit[0]   : 表示发生编码过程超时。 */
        unsigned long  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULCODE_OVERTIME_FLAG_UNION;
#define CBBP_ULCODE_OVERTIME_FLAG_ulcode_overtime_flag_cpu_START  (0)
#define CBBP_ULCODE_OVERTIME_FLAG_ulcode_overtime_flag_cpu_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULCODE_STATE_UNION
 结构说明  : ULCODE_STATE 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_state_reg;
    struct
    {
        unsigned long  ulcode_state_cpu : 3;  /* bit[0-2] : 上行编码状态上报。 */
        unsigned long  reserved         : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_ULCODE_STATE_UNION;
#define CBBP_ULCODE_STATE_ulcode_state_cpu_START  (0)
#define CBBP_ULCODE_STATE_ulcode_state_cpu_END    (2)


/*****************************************************************************
 结构名    : CBBP_ULCODE_TIMES_UNION
 结构说明  : ULCODE_TIMES 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_times_reg;
    struct
    {
        unsigned long  ulcode_int_times_cpu   : 16; /* bit[0-15] : 编码中断次数上报；复位清零。 */
        unsigned long  ulcode_start_times_cpu : 16; /* bit[16-31]: 编码启动次数上报；复位清零。 */
    } reg;
} CBBP_ULCODE_TIMES_UNION;
#define CBBP_ULCODE_TIMES_ulcode_int_times_cpu_START    (0)
#define CBBP_ULCODE_TIMES_ulcode_int_times_cpu_END      (15)
#define CBBP_ULCODE_TIMES_ulcode_start_times_cpu_START  (16)
#define CBBP_ULCODE_TIMES_ulcode_start_times_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_ULCODE_CKG_UNION
 结构说明  : ULCODE_CKG 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulcode_ckg_reg;
    struct
    {
        unsigned long  cpu_ulcode_ckg_bypass : 4;  /* bit[0-3] : 上行编码控制部分时钟门控bypass
                                                                 [0]:CRC模块门控bypass
                                                                 [1]:COD模块门控bypass
                                                                 [2]:RM模块门控bypass
                                                                 [3]:INTL模块门控bypass
                                                                 0：表示时钟门控有效。
                                                                 1：表示时钟常开。 */
        unsigned long  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} CBBP_ULCODE_CKG_UNION;
#define CBBP_ULCODE_CKG_cpu_ulcode_ckg_bypass_START  (0)
#define CBBP_ULCODE_CKG_cpu_ulcode_ckg_bypass_END    (3)


/***======================================================================***
                     (13/20) register_define_c_ulcode_mem
 ***======================================================================***/
/***======================================================================***
                     (14/20) register_define_c_fe_sdr_if
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_EN_UNION
 结构说明  : DLFE_SDR_EN 寄存器结构定义。地址偏移量:0x000，初值:0x00001000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_en_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_en              : 1;  /* bit[0]    : 下行SDR IF模块使能，高电平有效。 */
        unsigned long  reserved_0                   : 3;  /* bit[1-3]  : 保留 */
        unsigned long  cpu_dlfe_sdr_start_stop_mode : 1;  /* bit[4]    : 下行SDR IF模块搬运启停模式。0，主分集都用主集启停信号；1，主分集用各自启停信号。 */
        unsigned long  reserved_1                   : 3;  /* bit[5-7]  : 保留 */
        unsigned long  cpu_dlfe_sdr_mode            : 2;  /* bit[8-9]  : 下行SDR IF模块工作模式。0和1表示非C模；2表示1X；3表示EVDO。
                                                                         该参数仅在C模时有效。 */
        unsigned long  reserved_2                   : 2;  /* bit[10-11]: 保留 */
        unsigned long  cpu_dlfe_sdr_rx_mode         : 1;  /* bit[12]   : 下行SDR IF模块接收分集模式。0，非接收分集；1，接收分集。 */
        unsigned long  reserved_3                   : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_dlfe_sdr_start_mode      : 1;  /* bit[16]   : 下行SDR IF模块搬运启动模式。0，配置启动脉冲后立即启动搬运；1，配置启动脉冲后到cpu_dlfe_sdr_start_time定义的时刻启动搬运。
                                                                         该参数仅在G模软化时有效。 */
        unsigned long  reserved_4                   : 3;  /* bit[17-19]: 保留 */
        unsigned long  cpu_dlfe_sdr_stop_mode       : 1;  /* bit[20]   : 下行SDR IF模块搬运停止模式。0，配置停止脉冲后立即停止搬运；1，达到cpu_dlfe_sdr_data_length定义的搬运数据量后自动停止搬运。 */
        unsigned long  reserved_5                   : 3;  /* bit[21-23]: 保留 */
        unsigned long  cpu_dlfe_sdr_trans_mode      : 1;  /* bit[24]   : 下行搬运模式。0，DMA方式；1，BBPMaster方式。 */
        unsigned long  reserved_6                   : 3;  /* bit[25-27]: 保留 */
        unsigned long  cpu_dlfe_sdr_dma_mode        : 1;  /* bit[28]   : 下行DMA搬运模式。0，一次burst请求搬运32x32bit；1，一次burst请求搬运16x32bit。 */
        unsigned long  reserved_7                   : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_EN_UNION;
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_en_START               (0)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_en_END                 (0)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_stop_mode_START  (4)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_stop_mode_END    (4)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_mode_START             (8)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_mode_END               (9)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_rx_mode_START          (12)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_rx_mode_END            (12)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_START       (16)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_END         (16)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_START        (20)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_END          (20)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_START       (24)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_END         (24)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_START         (28)
#define CBBP_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_END           (28)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_CKG_BYS_UNION
 结构说明  : DLFE_SDR_CKG_BYS 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_ckg_bys_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_ckg_bypass : 1;  /* bit[0]   : 下行搬数时钟门控bypass信号，高电平有效，表示时钟常开。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_CKG_BYS_UNION;
#define CBBP_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_START  (0)
#define CBBP_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_START_STOP_UNION
 结构说明  : DLFE_SDR_START_STOP 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_start_stop_reg;
    struct
    {
        unsigned long  cpu_dlfe_at1_sdr_start      : 1;  /* bit[0]    : 下行主集搬运启动脉冲。 */
        unsigned long  reserved_0                  : 3;  /* bit[1-3]  : 保留 */
        unsigned long  cpu_dlfe_at1_sdr_stop       : 1;  /* bit[4]    : 下行主集搬运停止脉冲。 */
        unsigned long  reserved_1                  : 3;  /* bit[5-7]  : 保留 */
        unsigned long  cpu_dlfe_at1_sdr_force_stop : 1;  /* bit[8]    : 下行主集搬运强制停止脉冲。在检测到下行主集搬运出错后配置。 */
        unsigned long  reserved_2                  : 3;  /* bit[9-11] : 保留 */
        unsigned long  cpu_dlfe_at1_sdr_trans_clr  : 1;  /* bit[12]   : 下行主集BBPMaster搬运复位脉冲。 */
        unsigned long  reserved_3                  : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_dlfe_at2_sdr_start      : 1;  /* bit[16]   : 下行分集搬运启动脉冲。 */
        unsigned long  reserved_4                  : 3;  /* bit[17-19]: 保留 */
        unsigned long  cpu_dlfe_at2_sdr_stop       : 1;  /* bit[20]   : 下行分集搬运停止脉冲。 */
        unsigned long  reserved_5                  : 3;  /* bit[21-23]: 保留 */
        unsigned long  cpu_dlfe_at2_sdr_force_stop : 1;  /* bit[24]   : 下行分集搬运强制停止脉冲。在检测到下行分集搬运出错后配置。 */
        unsigned long  reserved_6                  : 3;  /* bit[25-27]: 保留 */
        unsigned long  cpu_dlfe_at2_sdr_trans_clr  : 1;  /* bit[28]   : 下行分集BBPMaster搬运复位脉冲。 */
        unsigned long  reserved_7                  : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_START_STOP_UNION;
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_START       (0)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_END         (0)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_START        (4)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_END          (4)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_START  (8)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_END    (8)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_START   (12)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_END     (12)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_start_START       (16)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_start_END         (16)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_stop_START        (20)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_stop_END          (20)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_force_stop_START  (24)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_force_stop_END    (24)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_trans_clr_START   (28)
#define CBBP_DLFE_SDR_START_STOP_cpu_dlfe_at2_sdr_trans_clr_END     (28)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION
 结构说明  : DLFE_SDR_OFFSET_BUFF_DEPTH 寄存器结构定义。地址偏移量:0x00C，初值:0x0000007F，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_offset_buff_depth_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_buffer_depth : 12; /* bit[0-11] : 下行Buffer深度，单位32word，用于计算Buffer首地址的时间戳。
                                                                      C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。 */
        unsigned long  reserved_0                : 4;  /* bit[12-15]: 保留 */
        unsigned long  cpu_dlfe_slot_head_offset : 11; /* bit[16-26]: 下行时隙头相对sys_cnt时隙边界的提前量，单位chip。
                                                                      该参数仅在C模时有效。 */
        unsigned long  reserved_1                : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION;
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_START  (0)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_END    (11)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_slot_head_offset_START  (16)
#define CBBP_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_slot_head_offset_END    (26)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_TIME_CTRL_UNION
 结构说明  : DLFE_SDR_TIME_CTRL 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_time_ctrl_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_start_time  : 13; /* bit[0-12] : G模软化时，gtc_timebase上的搬运启动时刻，单位Qb，范围0~4999。 */
        unsigned long  reserved_0               : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_dlfe_sdr_data_length : 12; /* bit[16-27]: 下行搬运数据量，单位32word。
                                                                     该参数仅在cpu_dlfe_sdr_stop_mode为1时有效。 */
        unsigned long  reserved_1               : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_TIME_CTRL_UNION;
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_START   (0)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_END     (12)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_data_length_START  (16)
#define CBBP_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_data_length_END    (27)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_WORD_DEPTH_UNION
 结构说明  : DLFE_SDR_WORD_DEPTH 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_word_depth_reg;
    struct
    {
        unsigned long  cpu_dlfe_sdr_word_depth : 16; /* bit[0-15] : 下行Buffer深度，单位word。
                                                                    C模和U模软化时，一个word对应一个chip；G模软化时，一个word对应一个Qb。
                                                                    建议在G模软化时使用。 */
        unsigned long  reserved                : 16; /* bit[16-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_WORD_DEPTH_UNION;
#define CBBP_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_START  (0)
#define CBBP_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_END    (15)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_CHIP_RPT 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_chip_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_chip_cnt_cpu : 6;  /* bit[0-5] : 下行天线1当前搬运word数。 */
        unsigned long  reserved                     : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_RD_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_RPT 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_block_cnt_cpu : 12; /* bit[0-11] : 下行天线1当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。 */
        unsigned long  dlfe_sdr_at1_rd_page_cnt_cpu  : 20; /* bit[12-31]: 下行天线1当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。 */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_END    (11)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_START   (12)
#define CBBP_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION
 结构说明  : DLFE_SDR_AT2_RD_CHIP_RPT 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_chip_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_chip_cnt_cpu : 6;  /* bit[0-5] : 下行天线2当前搬运word数。 */
        unsigned long  reserved                     : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_dlfe_sdr_at2_rd_chip_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_CHIP_RPT_dlfe_sdr_at2_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_RD_RPT_UNION
 结构说明  : DLFE_SDR_AT2_RD_RPT 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_block_cnt_cpu : 12; /* bit[0-11] : 下行天线2当前搬运块数。根据cpu_dlfe_sdr_buffer_depth统计。 */
        unsigned long  dlfe_sdr_at2_rd_page_cnt_cpu  : 20; /* bit[12-31]: 下行天线2当前搬运页数。根据cpu_dlfe_sdr_buffer_depth统计。 */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_block_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_block_cnt_cpu_END    (11)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_page_cnt_cpu_START   (12)
#define CBBP_DLFE_SDR_AT2_RD_RPT_dlfe_sdr_at2_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_1ST_STAMP_RPT 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_1st_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_1st_stamp_cpu : 28; /* bit[0-27] : 下行天线1启动搬运后第一个数据对应时间戳。
                                                                       C模时间戳为c_base_cnt，单位chip。
                                                                       bit[14:0]：计数范围0~32767chip，时间长度80/3ms（32768chip）；
                                                                       bit[16:15]：计数范围0~2，时间长度80ms；
                                                                       bit[21:17]：计数范围0~24，时间长度2s；
                                                                       bit[27:22]：固定为0。
                                                                       G模软化时间戳为gtc_tdma_qb上的帧号和gtc_timebase上的Qb号。
                                                                       bit[12:0]：gtc_timebase上的帧内Qb计数，计数范围0~4999Qb；
                                                                       bit[23:13]：gtc_tdma_qb上的fn_low帧计数，计数范围0~1325帧。
                                                                       bit[27:24]：固定为0。
                                                                       U模软化时间戳为base_cnt和cfn。
                                                                       bit[7:0]：symbol内chip计数，计数范围0~255chip；
                                                                       bit[11:8]：slot内symbol计数，计数范围0~9symbol；
                                                                       bit[15:12]：帧内slot计数，计数范围0~14slot；
                                                                       bit[27:16]：cfn。 */
        unsigned long  reserved                   : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT2_1ST_STAMP_RPT 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_1st_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_1st_stamp_cpu : 28; /* bit[0-27] : 下行天线2启动搬运后第一个数据对应base_cnt时间戳，单位chip。
                                                                       时间戳含义同上。 */
        unsigned long  reserved                   : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_dlfe_sdr_at2_1st_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_1ST_STAMP_RPT_dlfe_sdr_at2_1st_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT1_BUFFER_STAMP_RPT 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_buffer_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_bufferhead_stamp_cpu : 28; /* bit[0-27] : 下行天线1启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
                                                                              时间戳含义同上。
                                                                              C模1x时隙头即PCG头；C模EV-DO时隙头即实际时隙头；G模软化时隙头即gtc_tdma_qb上的burst头；U模软化时隙头即实际时隙头。 */
        unsigned long  reserved                          : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION
 结构说明  : DLFE_SDR_AT2_BUFFER_STAMP_RPT 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_buffer_stamp_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_bufferhead_stamp_cpu : 28; /* bit[0-27] : 下行天线2启动搬运后Buffer首地址数据对应时间戳，经过时隙头锁存。
                                                                              时间戳含义同上。
                                                                              时隙头含义同上。 */
        unsigned long  reserved                          : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_dlfe_sdr_at2_bufferhead_stamp_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_BUFFER_STAMP_RPT_dlfe_sdr_at2_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION
 结构说明  : DLFE_SDR_AT1_DUMP_EN_RPT 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_dump_en_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_dump_en : 1;  /* bit[0]   : 下行天线1搬运状态。 */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned long  dlfe_sdr_at1_err_sta : 1;  /* bit[4]   : 下行天线1搬运出错指示。 */
        unsigned long  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_START  (0)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_END    (0)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_START  (4)
#define CBBP_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_END    (4)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION
 结构说明  : DLFE_SDR_AT2_DUMP_EN_RPT 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_dump_en_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_dump_en : 1;  /* bit[0]   : 下行天线2搬运状态。 */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned long  dlfe_sdr_at2_err_sta : 1;  /* bit[4]   : 下行天线2搬运出错指示。 */
        unsigned long  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_dump_en_START  (0)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_dump_en_END    (0)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_err_sta_START  (4)
#define CBBP_DLFE_SDR_AT2_DUMP_EN_RPT_dlfe_sdr_at2_err_sta_END    (4)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION
 结构说明  : DLFE_SDR_AT1_RD_WORD_RPT 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at1_rd_word_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at1_rd_word_cnt_cpu : 16; /* bit[0-15] : 下行天线1当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
                                                                         建议在G模软化时使用。 */
        unsigned long  dlfe_sdr_at1_rd_seg_cnt_cpu  : 16; /* bit[16-31]: 下行天线1当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
                                                                         建议在G模软化时使用。 */
    } reg;
} CBBP_DLFE_SDR_AT1_RD_WORD_RPT_UNION;
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_END    (15)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_START   (16)
#define CBBP_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION
 结构说明  : DLFE_SDR_AT2_RD_WORD_RPT 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dlfe_sdr_at2_rd_word_rpt_reg;
    struct
    {
        unsigned long  dlfe_sdr_at2_rd_word_cnt_cpu : 16; /* bit[0-15] : 下行天线2当前搬运字数。根据cpu_dlfe_sdr_word_depth统计。
                                                                         建议在G模软化时使用。 */
        unsigned long  dlfe_sdr_at2_rd_seg_cnt_cpu  : 16; /* bit[16-31]: 下行天线2当前搬运页数。根据cpu_dlfe_sdr_word_depth统计。
                                                                         建议在G模软化时使用。 */
    } reg;
} CBBP_DLFE_SDR_AT2_RD_WORD_RPT_UNION;
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_word_cnt_cpu_START  (0)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_word_cnt_cpu_END    (15)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_seg_cnt_cpu_START   (16)
#define CBBP_DLFE_SDR_AT2_RD_WORD_RPT_dlfe_sdr_at2_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_EN_UNION
 结构说明  : ULFE_SDR_EN 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_en_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_en            : 1;  /* bit[0]    : 上行SDR IF模块使能，高电平有效。 */
        unsigned long  reserved_0                 : 3;  /* bit[1-3]  : 保留 */
        unsigned long  cpu_ulfe_sdr_da_on         : 1;  /* bit[4]    : 上行da_on，高电平有效。BBP经sys_cnt时隙边界同步再使用。
                                                                       该参数仅在C模时有效。 */
        unsigned long  reserved_1                 : 3;  /* bit[5-7]  : 保留 */
        unsigned long  cpu_ulfe_sdr_mode          : 2;  /* bit[8-9]  : 上行SDR IF模块工作模式。0和1表示非C模；2表示1X；3表示EVDO。
                                                                       该参数仅在C模时有效。 */
        unsigned long  reserved_2                 : 2;  /* bit[10-11]: 保留 */
        unsigned long  cpu_ulfe_sdr_g_mode        : 1;  /* bit[12]   : G模软化上行发送模式。0，正常模式；1，连续模式。 */
        unsigned long  reserved_3                 : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_ulfe_sdr_g_timing_mode : 1;  /* bit[16]   : G模软化上行发送定时选择。0，基于gtc_timebase；1，基于gtc_tdma_qb。 */
        unsigned long  reserved_4                 : 7;  /* bit[17-23]: 保留 */
        unsigned long  cpu_ulfe_sdr_trans_mode    : 1;  /* bit[24]   : 上行搬运模式。0，DMA方式；1，BBPMaster方式。 */
        unsigned long  reserved_5                 : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_EN_UNION;
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_en_START             (0)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_en_END               (0)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_da_on_START          (4)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_da_on_END            (4)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_mode_START           (8)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_mode_END             (9)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_START         (12)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_END           (12)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_START  (16)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_END    (16)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_START     (24)
#define CBBP_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_END       (24)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_CKG_UNION
 结构说明  : ULFE_SDR_CKG 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_ckg_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_ckg_bypass : 1;  /* bit[0]   : 上行搬数时钟门控bypass信号，高电平有效，表示时钟常开。 */
        unsigned long  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_CKG_UNION;
#define CBBP_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_START  (0)
#define CBBP_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_START_UNION
 结构说明  : ULFE_SDR_START 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_start_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_g_start     : 1;  /* bit[0]   : 上行取数发送启动脉冲。
                                                                    该参数仅在G模软化时有效。 */
        unsigned long  cpu_ulfe_sdr_g_stop      : 1;  /* bit[1]   : 上行取数发送停止脉冲。
                                                                    该参数仅在G模软化时有效。 */
        unsigned long  reserved_0               : 2;  /* bit[2-3] : 保留 */
        unsigned long  cpu_ulfe_sdr_trans_start : 1;  /* bit[4]   : BBPMaster搬运方式下，C模数据搬运启动脉冲。 */
        unsigned long  cpu_ulfe_sdr_trans_clr   : 1;  /* bit[5]   : BBPMaster搬运复位脉冲。 */
        unsigned long  reserved_1               : 26; /* bit[6-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_START_UNION;
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_start_START      (0)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_start_END        (0)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_START       (1)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_END         (1)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_start_START  (4)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_start_END    (4)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_START    (5)
#define CBBP_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_END      (5)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_OFFSET_UNION
 结构说明  : ULFE_SDR_OFFSET 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_offset_reg;
    struct
    {
        unsigned long  cpu_ulfe_slot_offset : 13; /* bit[0-12] : C模时，表示上行时隙头相对sys_cnt时隙边界提前量，单位1/4chip。
                                                                 G模软化时，表示gtc_tdma_qb上的启动数据发送时刻，单位Qb，范围0~4999。 */
        unsigned long  reserved_0           : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_ulfe_ach_offset  : 11; /* bit[16-26]: C模时，表示上行ACH时隙头相对sys_cnt时隙边界延迟量，单位chip。
                                                                 G模软化时，bit[22:16]表示启动数据发送的Qb内clk时刻；bit[26:23]无意义。 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_OFFSET_UNION;
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_START  (0)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_END    (12)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_START   (16)
#define CBBP_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_END     (26)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_ACTIVE_TIME_UNION
 结构说明  : ULFE_SDR_ACTIVE_TIME 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_active_time_reg;
    struct
    {
        unsigned long  cpu_ulfe_dbb_active_time        : 13; /* bit[0-12] : C模时，表示上行dbb控制字提前时隙头生效位置，单位1/4chip。
                                                                            G模软化时，bit[11:0]表示发送数据第一个burst起始样点，取值范围0~2499；bit[12]无意义。 */
        unsigned long  reserved_0                      : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_ulfe_phase_comp_active_time : 13; /* bit[16-28]: C模时，表示上行相位补偿提前时隙头生效位置，单位1/4chip。
                                                                            G模软化时，bit[27:16]表示发送数据最后一个burst结束样点，取值范围0~2499；bit[28]无意义。 */
        unsigned long  reserved_1                      : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_ACTIVE_TIME_UNION;
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_START         (0)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_END           (12)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_START  (16)
#define CBBP_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_END    (28)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_G_CFG_UNION
 结构说明  : ULFE_SDR_G_CFG 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_g_cfg_reg;
    struct
    {
        unsigned long  cpu_ulfe_sdr_g_burst_num : 3;  /* bit[0-2] : G模软化时，发送数据包含的burst个数，取值范围0~5。配置值加1表示实际burst个数。 */
        unsigned long  reserved                 : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_G_CFG_UNION;
#define CBBP_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_START  (0)
#define CBBP_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_END    (2)


/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_DUMP_EN_RPT_UNION
 结构说明  : ULFE_SDR_DUMP_EN_RPT 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_dump_en_rpt_reg;
    struct
    {
        unsigned long  ulfe_sdr_dump_en   : 1;  /* bit[0]   : 上行搬运状态。 */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned long  ulfe_sdr_err_sta   : 1;  /* bit[4]   : 上行BBPMaster搬运出错指示。 */
        unsigned long  reserved_1         : 3;  /* bit[5-7] : 保留 */
        unsigned long  ulfe_sdr_trans_sta : 1;  /* bit[8]   : 上行BBPMaster搬运完成指示。 */
        unsigned long  reserved_2         : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_DUMP_EN_RPT_UNION;
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_START    (0)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_END      (0)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_START    (4)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_END      (4)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_START  (8)
#define CBBP_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_END    (8)


/***======================================================================***
                     (15/20) register_define_c_fe_sdr_if_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_ULFE_SDR_RAM_UNION
 结构说明  : ULFE_SDR_RAM 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ulfe_sdr_ram_reg;
    struct
    {
        unsigned long  ulfe_sdr_data_i : 12; /* bit[0-11] : C模时，表示上行前端数据I路，12比特有符号数，软件每1/4 PCG或slot写一遍。
                                                            G模软化时，表示上行发送数据I路，12比特有符号数，软件每1/5 burst写一遍。 */
        unsigned long  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned long  ulfe_sdr_data_q : 12; /* bit[16-27]: C模时，表示上行前端数据Q路，12比特有符号数，软件每1/4 PCG或slot写一遍。
                                                            G模软化时，表示上行发送数据Q路，12比特有符号数，软件每1/5 burst写一遍。 */
        unsigned long  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} CBBP_ULFE_SDR_RAM_UNION;
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_i_START  (0)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_i_END    (11)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_q_START  (16)
#define CBBP_ULFE_SDR_RAM_ulfe_sdr_data_q_END    (27)


/***======================================================================***
                     (16/20) register_define_c_fe_ctrl
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_CTU_CFG_UNION
 结构说明  : CTU_CFG 寄存器结构定义。地址偏移量:0x000，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_cfg_reg;
    struct
    {
        unsigned long  cpu_ctu_meas_type                   : 2;  /* bit[0-1]  : C测量类型：0异频，1异系统，2从模。 */
        unsigned long  reserved_0                          : 2;  /* bit[2-3]  : 保留 */
        unsigned long  cpu_ctu_meas_en_value               : 1;  /* bit[4]    : 软件配置异频异系统测量使能信号值。 */
        unsigned long  reserved_1                          : 3;  /* bit[5-7]  : 保留 */
        unsigned long  cpu_ctu_intersys_ingap_value        : 1;  /* bit[8]    : 软件配置intersys_ingap_pre_ind信号值。 */
        unsigned long  reserved_2                          : 3;  /* bit[9-11] : 保留 */
        unsigned long  cpu_ctu_master_meas_c_en            : 1;  /* bit[12]   : C从模时，com2c_master_intrasys_valid 下降沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。 */
        unsigned long  cpu_ctu_intrasys_valid_delay_neg_en : 1;  /* bit[13]   : C主模时，c2com_intrasys_valid_delay下降沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。 */
        unsigned long  cpu_ctu_intrasys_valid_delay_pos_en : 1;  /* bit[14]   : C主模时，c2com_intrasys_valid_delay上升沿启动SSI、MIPI、GPIO RAM发送使能，高点平有效。 */
        unsigned long  reserved_3                          : 1;  /* bit[15]   : 保留 */
        unsigned long  cpu_c_fe_ctrl_mode                  : 2;  /* bit[16-17]: c_fe_ctrl模块工作模式：0和1表示非C模，2表示1X，3表示EVDO。 */
        unsigned long  reserved_4                          : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_CTU_CFG_UNION;
#define CBBP_CTU_CFG_cpu_ctu_meas_type_START                    (0)
#define CBBP_CTU_CFG_cpu_ctu_meas_type_END                      (1)
#define CBBP_CTU_CFG_cpu_ctu_meas_en_value_START                (4)
#define CBBP_CTU_CFG_cpu_ctu_meas_en_value_END                  (4)
#define CBBP_CTU_CFG_cpu_ctu_intersys_ingap_value_START         (8)
#define CBBP_CTU_CFG_cpu_ctu_intersys_ingap_value_END           (8)
#define CBBP_CTU_CFG_cpu_ctu_master_meas_c_en_START             (12)
#define CBBP_CTU_CFG_cpu_ctu_master_meas_c_en_END               (12)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_neg_en_START  (13)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_neg_en_END    (13)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_pos_en_START  (14)
#define CBBP_CTU_CFG_cpu_ctu_intrasys_valid_delay_pos_en_END    (14)
#define CBBP_CTU_CFG_cpu_c_fe_ctrl_mode_START                   (16)
#define CBBP_CTU_CFG_cpu_c_fe_ctrl_mode_END                     (17)


/*****************************************************************************
 结构名    : CBBP_CTU_MEAS_ACT_TIME_UNION
 结构说明  : CTU_MEAS_ACT_TIME 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_meas_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_meas_en_active_time : 17; /* bit[0-16] : 软件配置异频异系统测量使能信号在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                    : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_MEAS_ACT_TIME_UNION;
#define CBBP_CTU_MEAS_ACT_TIME_cpu_ctu_meas_en_active_time_START  (0)
#define CBBP_CTU_MEAS_ACT_TIME_cpu_ctu_meas_en_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_INGAP_ACT_TIME_UNION
 结构说明  : CTU_INGAP_ACT_TIME 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_ingap_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intersys_ingap_active_time : 17; /* bit[0-16] : 软件配置intersys_ingap_pre_ind信号在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                           : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_INGAP_ACT_TIME_UNION;
#define CBBP_CTU_INGAP_ACT_TIME_cpu_ctu_intersys_ingap_active_time_START  (0)
#define CBBP_CTU_INGAP_ACT_TIME_cpu_ctu_intersys_ingap_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_INTRA_CLR_ACT_TIME_UNION
 结构说明  : CTU_INTRA_CLR_ACT_TIME 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_clr_active_time : 17; /* bit[0-16] : 软件配置intrasys_valid信号置0在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                               : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_INTRA_CLR_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_CLR_ACT_TIME_cpu_ctu_intrasys_valid_clr_active_time_START  (0)
#define CBBP_CTU_INTRA_CLR_ACT_TIME_cpu_ctu_intrasys_valid_clr_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_INTRA_SET_ACT_TIME_UNION
 结构说明  : CTU_INTRA_SET_ACT_TIME 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_set_active_time : 17; /* bit[0-16] : 软件配置intrasys_valid信号置1在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                               : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_INTRA_SET_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_SET_ACT_TIME_cpu_ctu_intrasys_valid_set_active_time_START  (0)
#define CBBP_CTU_INTRA_SET_ACT_TIME_cpu_ctu_intrasys_valid_set_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION
 结构说明  : CTU_INTRA_DLY_CLR_ACT_TIME 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_dly_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_delay_clr_active_time : 17; /* bit[0-16] : 软件配置intrasys_valid_delay信号置0在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                                     : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_cpu_ctu_intrasys_valid_delay_clr_active_time_START  (0)
#define CBBP_CTU_INTRA_DLY_CLR_ACT_TIME_cpu_ctu_intrasys_valid_delay_clr_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION
 结构说明  : CTU_INTRA_DLY_SET_ACT_TIME 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_intra_dly_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_intrasys_valid_delay_set_active_time : 17; /* bit[0-16] : 软件配置intrasys_valid_delay信号置1在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                                     : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_INTRA_DLY_SET_ACT_TIME_UNION;
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_cpu_ctu_intrasys_valid_delay_set_active_time_START  (0)
#define CBBP_CTU_INTRA_DLY_SET_ACT_TIME_cpu_ctu_intrasys_valid_delay_set_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_STOP_CLR_ACT_TIME_UNION
 结构说明  : CTU_STOP_CLR_ACT_TIME 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_stop_clr_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_ssi_mipi_stop_clr_active_time : 17; /* bit[0-16] : 软件配置ssi_mipi_stop信号置0在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                              : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_STOP_CLR_ACT_TIME_UNION;
#define CBBP_CTU_STOP_CLR_ACT_TIME_cpu_ctu_ssi_mipi_stop_clr_active_time_START  (0)
#define CBBP_CTU_STOP_CLR_ACT_TIME_cpu_ctu_ssi_mipi_stop_clr_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_CTU_STOP_SET_ACT_TIME_UNION
 结构说明  : CTU_STOP_SET_ACT_TIME 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctu_stop_set_act_time_reg;
    struct
    {
        unsigned long  cpu_ctu_ssi_mipi_stop_set_active_time : 17; /* bit[0-16] : 软件配置ssi_mipi_stop信号置1在sys_cnt生效时刻，单位chip。 */
        unsigned long  reserved                              : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_CTU_STOP_SET_ACT_TIME_UNION;
#define CBBP_CTU_STOP_SET_ACT_TIME_cpu_ctu_ssi_mipi_stop_set_active_time_START  (0)
#define CBBP_CTU_STOP_SET_ACT_TIME_cpu_ctu_ssi_mipi_stop_set_active_time_END    (16)


/*****************************************************************************
 结构名    : CBBP_RFIC_START_TIME_UNION
 结构说明  : RFIC_START_TIME 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_start_time_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_auto_run_time : 11; /* bit[0-10] : rfic_ssi每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对RFIC SSI RAM翻页，并开始根据RAM控制字发送数据。注意：在G SDR模式，该参数不能与active_time相同 */
        unsigned long  reserved                   : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_RFIC_START_TIME_UNION;
#define CBBP_RFIC_START_TIME_cpu_rfic_ssi_auto_run_time_START  (0)
#define CBBP_RFIC_START_TIME_cpu_rfic_ssi_auto_run_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_STA_CFG_UNION
 结构说明  : RFIC_SSI_STA_CFG 寄存器结构定义。地址偏移量:0x044，初值:0x00001902，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_work_mode_sel          : 1;  /* bit[0]    : 0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。此模式必须配置cpu_rfic_ssi_buffer_clr_mode为1
                                                                                1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。 */
        unsigned long  cpu_rfic_ssi_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零 */
        unsigned long  cpu_rfic_ssi_buffer_mode            : 1;  /* bit[2]    : 0:每个ctrl_buff对应最多7个数据。1:每个ctrl_buff对应最多3个数据。 */
        unsigned long  reserved_0                          : 1;  /* bit[3]    : 保留 */
        unsigned long  cpu_rfic_ssi_data_buffer_start_addr : 7;  /* bit[4-10] : 每个乒乓RAM中data_buffer起始地址。 */
        unsigned long  cpu_rfic_ssi_page_switch_en         : 1;  /* bit[11]   : 翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。 */
        unsigned long  cpu_rfic_ssi_auto_run               : 1;  /* bit[12]   : 自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。 */
        unsigned long  reserved_1                          : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_RFIC_SSI_STA_CFG_UNION;
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_work_mode_sel_START           (0)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_work_mode_sel_END             (0)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_clr_mode_START         (1)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_clr_mode_END           (1)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_mode_START             (2)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_buffer_mode_END               (2)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_data_buffer_start_addr_START  (4)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_data_buffer_start_addr_END    (10)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_page_switch_en_START          (11)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_page_switch_en_END            (11)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_auto_run_START                (12)
#define CBBP_RFIC_SSI_STA_CFG_cpu_rfic_ssi_auto_run_END                  (12)


/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_DYN_CFG_UNION
 结构说明  : RFIC_SSI_DYN_CFG 寄存器结构定义。地址偏移量:0x048，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_pro_en    : 1;  /* bit[0]   : 模块工作使能，高电平有效。 */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_rfic_ssi_hold_page : 1;  /* bit[4]   : 1表示暂停发送当前RAM中数据。当此信号生效时，软件如需要改写RAM中的数据，不需要手动翻页，直接在当前页操作。Hold结束后，BBP会从头开始重新执行CtrlBuffer的指令 */
        unsigned long  reserved_1             : 1;  /* bit[5]   : 保留 */
        unsigned long  cpu_rfic_ssi_stop_page : 1;  /* bit[6]   : 1表示停止发送当前RAM中数据并清除当前RAM所有数据。 */
        unsigned long  cpu_rfic_ssi_stop_mode : 1;  /* bit[7]   : 停止发送模式，0表示立即停止不发送新数据，1表示当前ctrl_buff对应数据发送完成后再停止。 */
        unsigned long  reserved_2             : 24; /* bit[8-31]: 保留 */
    } reg;
} CBBP_RFIC_SSI_DYN_CFG_UNION;
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_pro_en_START     (0)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_pro_en_END       (0)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_hold_page_START  (4)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_hold_page_END    (4)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_page_START  (6)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_page_END    (6)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_mode_START  (7)
#define CBBP_RFIC_SSI_DYN_CFG_cpu_rfic_ssi_stop_mode_END    (7)


/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_START_UNION
 结构说明  : RFIC_SSI_START 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_start_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_page_start  : 1;  /* bit[0]    : 写1产生脉冲信号，手动启动指令页执行，cpu_rfic_ssi_auto_run=0时才有效。 */
        unsigned long  reserved_0               : 15; /* bit[1-15] : 保留 */
        unsigned long  cpu_rfic_ssi_force_pulse : 1;  /* bit[16]   : C_FE_RFIC 强制发送脉冲。cpu_rfic_ssi_force_en=1时才有效。 */
        unsigned long  reserved_1               : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_RFIC_SSI_START_UNION;
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_page_start_START   (0)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_page_start_END     (0)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_force_pulse_START  (16)
#define CBBP_RFIC_SSI_START_cpu_rfic_ssi_force_pulse_END    (16)


/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_FORCE_UNION
 结构说明  : RFIC_SSI_FORCE 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_force_reg;
    struct
    {
        unsigned long  cpu_rfic_ssi_force_data : 25; /* bit[0-24] : C_FE_RFIC 强制发送数据，cpu_rfic_ssi_force_en=1时才有效。 */
        unsigned long  reserved                : 6;  /* bit[25-30]: 保留 */
        unsigned long  cpu_rfic_ssi_force_en   : 1;  /* bit[31]   : C_FE_RFIC 强制发送使能。关闭cpu_rfic_ssi_pro_en时使用，或者工作状态先配cpu_rfic_ssi_hold_page暂停后使用。 */
    } reg;
} CBBP_RFIC_SSI_FORCE_UNION;
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_data_START  (0)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_data_END    (24)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_en_START    (31)
#define CBBP_RFIC_SSI_FORCE_cpu_rfic_ssi_force_en_END      (31)


/*****************************************************************************
 结构名    : CBBP_RFIC_STATE_RPT_UNION
 结构说明  : RFIC_STATE_RPT 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      rfic_state_rpt_reg;
    struct
    {
        unsigned long  rfic_ssi_curr_state_rpt : 3;  /* bit[0-2]  : rfic_ssi RAM访问状态上报。 */
        unsigned long  reserved_0              : 1;  /* bit[3]    : 保留 */
        unsigned long  rfic_ssi_page_sel_rpt   : 1;  /* bit[4]    : BBP当前使用乒乓RAM状态上报。 */
        unsigned long  rfic_rd_ctrl_buff_addr  : 7;  /* bit[5-11] : 当前执行到的rfic_ctrl buff的地址 */
        unsigned long  rfic_err_config_rpt     : 3;  /* bit[12-14]: 异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
                                                                    [12]work_mode_sel被异常改写
                                                                    [13]buffer_clr_mode被异常改写
                                                                    [14]data_buffer_start_addr被异常改写 */
        unsigned long  reserved_1              : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_RFIC_STATE_RPT_UNION;
#define CBBP_RFIC_STATE_RPT_rfic_ssi_curr_state_rpt_START  (0)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_curr_state_rpt_END    (2)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_page_sel_rpt_START    (4)
#define CBBP_RFIC_STATE_RPT_rfic_ssi_page_sel_rpt_END      (4)
#define CBBP_RFIC_STATE_RPT_rfic_rd_ctrl_buff_addr_START   (5)
#define CBBP_RFIC_STATE_RPT_rfic_rd_ctrl_buff_addr_END     (11)
#define CBBP_RFIC_STATE_RPT_rfic_err_config_rpt_START      (12)
#define CBBP_RFIC_STATE_RPT_rfic_err_config_rpt_END        (14)


/*****************************************************************************
 结构名    : CBBP_MIPI_START_TIME_UNION
 结构说明  : MIPI_START_TIME 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_start_time_reg;
    struct
    {
        unsigned long  cpu_mipi_auto_run_time : 11; /* bit[0-10] : mipi每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对MIPI RAM翻页，并开始根据RAM控制字发送数据。 */
        unsigned long  reserved               : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_MIPI_START_TIME_UNION;
#define CBBP_MIPI_START_TIME_cpu_mipi_auto_run_time_START  (0)
#define CBBP_MIPI_START_TIME_cpu_mipi_auto_run_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_MIPI_STA_CFG_UNION
 结构说明  : MIPI_STA_CFG 寄存器结构定义。地址偏移量:0x074，初值:0x00001902，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_mipi_work_mode_sel          : 1;  /* bit[0]    : 0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。
                                                                            1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。 */
        unsigned long  cpu_mipi_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零 */
        unsigned long  cpu_mipi_buffer_mode            : 1;  /* bit[2]    : 0:每个ctrl_buff对应最多3个数据。1:每个ctrl_buff对应最多1个数据。 */
        unsigned long  reserved_0                      : 1;  /* bit[3]    : 保留 */
        unsigned long  cpu_mipi_data_buffer_start_addr : 7;  /* bit[4-10] : 每个乒乓RAM中data_buffer起始地址。 */
        unsigned long  cpu_mipi_page_switch_en         : 1;  /* bit[11]   : 翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。 */
        unsigned long  cpu_mipi_auto_run               : 1;  /* bit[12]   : 自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。 */
        unsigned long  reserved_1                      : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_MIPI_STA_CFG_UNION;
#define CBBP_MIPI_STA_CFG_cpu_mipi_work_mode_sel_START           (0)
#define CBBP_MIPI_STA_CFG_cpu_mipi_work_mode_sel_END             (0)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_clr_mode_START         (1)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_clr_mode_END           (1)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_mode_START             (2)
#define CBBP_MIPI_STA_CFG_cpu_mipi_buffer_mode_END               (2)
#define CBBP_MIPI_STA_CFG_cpu_mipi_data_buffer_start_addr_START  (4)
#define CBBP_MIPI_STA_CFG_cpu_mipi_data_buffer_start_addr_END    (10)
#define CBBP_MIPI_STA_CFG_cpu_mipi_page_switch_en_START          (11)
#define CBBP_MIPI_STA_CFG_cpu_mipi_page_switch_en_END            (11)
#define CBBP_MIPI_STA_CFG_cpu_mipi_auto_run_START                (12)
#define CBBP_MIPI_STA_CFG_cpu_mipi_auto_run_END                  (12)


/*****************************************************************************
 结构名    : CBBP_MIPI_DYN_CFG_UNION
 结构说明  : MIPI_DYN_CFG 寄存器结构定义。地址偏移量:0x078，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_mipi_pro_en    : 1;  /* bit[0]   : 模块工作使能，高电平有效。 */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_mipi_hold_page : 1;  /* bit[4]   : 1表示暂停发送当前RAM中数据。用法见cpu_rfic_ssi_hold_page */
        unsigned long  reserved_1         : 1;  /* bit[5]   : 保留 */
        unsigned long  cpu_mipi_stop_page : 1;  /* bit[6]   : 1表示停止发送当前RAM中数据并清除当前RAM所有数据。 */
        unsigned long  cpu_mipi_stop_mode : 1;  /* bit[7]   : 停止发送模式，0表示立即停止不发送新数据，1表示当前ctrl_buff对应数据发送完成后再停止。 */
        unsigned long  reserved_2         : 24; /* bit[8-31]: 保留 */
    } reg;
} CBBP_MIPI_DYN_CFG_UNION;
#define CBBP_MIPI_DYN_CFG_cpu_mipi_pro_en_START     (0)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_pro_en_END       (0)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_hold_page_START  (4)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_hold_page_END    (4)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_page_START  (6)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_page_END    (6)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_mode_START  (7)
#define CBBP_MIPI_DYN_CFG_cpu_mipi_stop_mode_END    (7)


/*****************************************************************************
 结构名    : CBBP_MIPI_START_UNION
 结构说明  : MIPI_START 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_start_reg;
    struct
    {
        unsigned long  cpu_mipi_page_start  : 1;  /* bit[0]   : 写1产生脉冲信号，手动启动指令页执行，cpu_mipi_auto_run=0时才有效。 */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_mipi_force_pulse : 1;  /* bit[4]   : C_FE_MIPI 强制发送脉冲。cpu_mipi_force_en=1时才有效。 */
        unsigned long  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_MIPI_START_UNION;
#define CBBP_MIPI_START_cpu_mipi_page_start_START   (0)
#define CBBP_MIPI_START_cpu_mipi_page_start_END     (0)
#define CBBP_MIPI_START_cpu_mipi_force_pulse_START  (4)
#define CBBP_MIPI_START_cpu_mipi_force_pulse_END    (4)


/*****************************************************************************
 结构名    : CBBP_MIPI_FORCE_EN_UNION
 结构说明  : MIPI_FORCE_EN 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_force_en_reg;
    struct
    {
        unsigned long  cpu_mipi_force_en : 1;  /* bit[0]   : C_FE_MIPI 强制发送使能。关闭cpu_mipi_pro_en时使用，或者工作状态先配cpu_mipi_hold_page暂停后使用。
                                                             强配时，mipi_force_data必须配置64bit（高低都配置），如果数据不足32bit，则配置在高32bit，且低32bit配置为0。 */
        unsigned long  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_MIPI_FORCE_EN_UNION;
#define CBBP_MIPI_FORCE_EN_cpu_mipi_force_en_START  (0)
#define CBBP_MIPI_FORCE_EN_cpu_mipi_force_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_MIPI_STATE_RPT_UNION
 结构说明  : MIPI_STATE_RPT 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      mipi_state_rpt_reg;
    struct
    {
        unsigned long  mipi_curr_state_rpt    : 3;  /* bit[0-2]  : mipi RAM控制的状态机上报。 */
        unsigned long  reserved_0             : 1;  /* bit[3]    : 保留 */
        unsigned long  mipi_page_sel_rpt      : 1;  /* bit[4]    : BBP当前使用RAM的乒乓状态上报。 */
        unsigned long  mipi_rd_ctrl_buff_addr : 7;  /* bit[5-11] : 当前执行到的rfic_ctrl buff的地址 */
        unsigned long  mipi_err_config_rpt    : 3;  /* bit[12-14]: 异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
                                                                   [12]work_mode_sel被异常改写
                                                                   [13]buffer_clr_mode被异常改写
                                                                   [14]data_buffer_start_addr被异常改写 */
        unsigned long  reserved_1             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_MIPI_STATE_RPT_UNION;
#define CBBP_MIPI_STATE_RPT_mipi_curr_state_rpt_START     (0)
#define CBBP_MIPI_STATE_RPT_mipi_curr_state_rpt_END       (2)
#define CBBP_MIPI_STATE_RPT_mipi_page_sel_rpt_START       (4)
#define CBBP_MIPI_STATE_RPT_mipi_page_sel_rpt_END         (4)
#define CBBP_MIPI_STATE_RPT_mipi_rd_ctrl_buff_addr_START  (5)
#define CBBP_MIPI_STATE_RPT_mipi_rd_ctrl_buff_addr_END    (11)
#define CBBP_MIPI_STATE_RPT_mipi_err_config_rpt_START     (12)
#define CBBP_MIPI_STATE_RPT_mipi_err_config_rpt_END       (14)


/*****************************************************************************
 结构名    : CBBP_GPIO_START_TIME_UNION
 结构说明  : GPIO_START_TIME 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_start_time_reg;
    struct
    {
        unsigned long  cpu_gpio_auto_run_time : 11; /* bit[0-10] : GPIO每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对GPIO RAM翻页，并开始根据RAM控制字发送数据。 */
        unsigned long  reserved               : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_GPIO_START_TIME_UNION;
#define CBBP_GPIO_START_TIME_cpu_gpio_auto_run_time_START  (0)
#define CBBP_GPIO_START_TIME_cpu_gpio_auto_run_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_GPIO_STA_CFG_UNION
 结构说明  : GPIO_STA_CFG 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000600，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_sta_cfg_reg;
    struct
    {
        unsigned long  cpu_gpio_work_mode_sel          : 1;  /* bit[0]    : 0:轮询模式，DSP写完RAM后启动发送，BBP循环遍历解析ctrlbuffer，直到全部数据发送完成。
                                                                            1:软件排序模式，DSP把下时隙需要发送的所有数据按生效时刻由前到后排序放在RAM中，BBP只遍历一次ctrlbuffer，依次执行。 */
        unsigned long  cpu_gpio_buffer_clr_mode        : 1;  /* bit[1]    : 0:ctrl_buff执行完后不清零，1:ctrl_buff执行完后清零 */
        unsigned long  reserved_0                      : 2;  /* bit[2-3]  : 保留 */
        unsigned long  cpu_gpio_data_buffer_start_addr : 6;  /* bit[4-9]  : 每个乒乓RAM中data_buffer起始地址。 */
        unsigned long  cpu_gpio_page_switch_en         : 1;  /* bit[10]   : 翻页使能，0:不翻页，软件和BBP都使用低段RAM；1：翻页，软件和BBP乒乓使用高低两段RAM。 */
        unsigned long  cpu_gpio_auto_run               : 1;  /* bit[11]   : 自动翻页使能，0：软件配置脉冲手动翻页，1：在软件配置时刻自动翻页。 */
        unsigned long  reserved_1                      : 20; /* bit[12-31]: 保留 */
    } reg;
} CBBP_GPIO_STA_CFG_UNION;
#define CBBP_GPIO_STA_CFG_cpu_gpio_work_mode_sel_START           (0)
#define CBBP_GPIO_STA_CFG_cpu_gpio_work_mode_sel_END             (0)
#define CBBP_GPIO_STA_CFG_cpu_gpio_buffer_clr_mode_START         (1)
#define CBBP_GPIO_STA_CFG_cpu_gpio_buffer_clr_mode_END           (1)
#define CBBP_GPIO_STA_CFG_cpu_gpio_data_buffer_start_addr_START  (4)
#define CBBP_GPIO_STA_CFG_cpu_gpio_data_buffer_start_addr_END    (9)
#define CBBP_GPIO_STA_CFG_cpu_gpio_page_switch_en_START          (10)
#define CBBP_GPIO_STA_CFG_cpu_gpio_page_switch_en_END            (10)
#define CBBP_GPIO_STA_CFG_cpu_gpio_auto_run_START                (11)
#define CBBP_GPIO_STA_CFG_cpu_gpio_auto_run_END                  (11)


/*****************************************************************************
 结构名    : CBBP_GPIO_DYN_CFG_UNION
 结构说明  : GPIO_DYN_CFG 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_gpio_pro_en    : 1;  /* bit[0]   : 模块工作使能，高电平有效。 */
        unsigned long  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_gpio_hold_page : 1;  /* bit[4]   : 1表示暂停发送当前RAM中数据。 */
        unsigned long  reserved_1         : 3;  /* bit[5-7] : 保留 */
        unsigned long  cpu_gpio_stop_page : 1;  /* bit[8]   : 1表示停止发送当前RAM中数据并清除当前RAM所有数据。 */
        unsigned long  reserved_2         : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_GPIO_DYN_CFG_UNION;
#define CBBP_GPIO_DYN_CFG_cpu_gpio_pro_en_START     (0)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_pro_en_END       (0)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_hold_page_START  (4)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_hold_page_END    (4)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_stop_page_START  (8)
#define CBBP_GPIO_DYN_CFG_cpu_gpio_stop_page_END    (8)


/*****************************************************************************
 结构名    : CBBP_GPIO_START_UNION
 结构说明  : GPIO_START 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_start_reg;
    struct
    {
        unsigned long  cpu_gpio_page_start  : 1;  /* bit[0]   : 写1产生脉冲信号，手动启动指令页执行，cpu_gpio_auto_run=0时才有效。 */
        unsigned long  reserved_0           : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_gpio_force_pulse : 1;  /* bit[4]   : C_FE_GPIO 强制发送脉冲，cpu_gpio_force_en=1时才有效。 */
        unsigned long  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_GPIO_START_UNION;
#define CBBP_GPIO_START_cpu_gpio_page_start_START   (0)
#define CBBP_GPIO_START_cpu_gpio_page_start_END     (0)
#define CBBP_GPIO_START_cpu_gpio_force_pulse_START  (4)
#define CBBP_GPIO_START_cpu_gpio_force_pulse_END    (4)


/*****************************************************************************
 结构名    : CBBP_GPIO_FORCE_EN_UNION
 结构说明  : GPIO_FORCE_EN 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_force_en_reg;
    struct
    {
        unsigned long  reserved          : 31; /* bit[0-30]: 保留 */
        unsigned long  cpu_gpio_force_en : 1;  /* bit[31]  : C_FE_GPIO 强制发送使能，关闭cpu_gpio_pro_en时使用，或者工作状态先配cpu_gpio_hold_page暂停后使用。 */
    } reg;
} CBBP_GPIO_FORCE_EN_UNION;
#define CBBP_GPIO_FORCE_EN_cpu_gpio_force_en_START  (31)
#define CBBP_GPIO_FORCE_EN_cpu_gpio_force_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_GPIO_STATE_RPT_UNION
 结构说明  : GPIO_STATE_RPT 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_state_rpt_reg;
    struct
    {
        unsigned long  gpio_curr_state_rpt    : 3;  /* bit[0-2]  : gpio RAM访问状态上报。 */
        unsigned long  reserved_0             : 1;  /* bit[3]    : 保留 */
        unsigned long  gpio_page_sel_rpt      : 1;  /* bit[4]    : BBP当前使用乒乓RAM状态上报。 */
        unsigned long  gpio_rd_ctrl_buff_addr : 6;  /* bit[5-10] : 当前执行到的gpio_ctrl buff的地址 */
        unsigned long  reserved_1             : 1;  /* bit[11]   : 保留 */
        unsigned long  gpio_err_config_rpt    : 3;  /* bit[12-14]: 异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
                                                                   [12]work_mode_sel被异常改写
                                                                   [13]buffer_clr_mode被异常改写
                                                                   [14]data_buffer_start_addr被异常改写 */
        unsigned long  reserved_2             : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_GPIO_STATE_RPT_UNION;
#define CBBP_GPIO_STATE_RPT_gpio_curr_state_rpt_START     (0)
#define CBBP_GPIO_STATE_RPT_gpio_curr_state_rpt_END       (2)
#define CBBP_GPIO_STATE_RPT_gpio_page_sel_rpt_START       (4)
#define CBBP_GPIO_STATE_RPT_gpio_page_sel_rpt_END         (4)
#define CBBP_GPIO_STATE_RPT_gpio_rd_ctrl_buff_addr_START  (5)
#define CBBP_GPIO_STATE_RPT_gpio_rd_ctrl_buff_addr_END    (10)
#define CBBP_GPIO_STATE_RPT_gpio_err_config_rpt_START     (12)
#define CBBP_GPIO_STATE_RPT_gpio_err_config_rpt_END       (14)


/*****************************************************************************
 结构名    : CBBP_GPIO_ANTPA_RPT_UNION
 结构说明  : GPIO_ANTPA_RPT 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_antpa_rpt_reg;
    struct
    {
        unsigned long  gpio_antpa_sel_rpt : 31; /* bit[0-30]: 公共线控(antpa)控制上报。 */
        unsigned long  reserved           : 1;  /* bit[31]  : 保留 */
    } reg;
} CBBP_GPIO_ANTPA_RPT_UNION;
#define CBBP_GPIO_ANTPA_RPT_gpio_antpa_sel_rpt_START  (0)
#define CBBP_GPIO_ANTPA_RPT_gpio_antpa_sel_rpt_END    (30)


/*****************************************************************************
 结构名    : CBBP_GPIO_LINE_CTRL_RPT_UNION
 结构说明  : GPIO_LINE_CTRL_RPT 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gpio_line_ctrl_rpt_reg;
    struct
    {
        unsigned long  gpio_line_ctrl_rpt : 31; /* bit[0-30]: 专用线控（gpio线控）上报。bit[0]:c_abb0_rxa_en,ABB A通道接收使能
                                                              bit[1]:c_abb0_rxb_en,ABB B通道接收使能
                                                              bit[2]:c_abb0_rxa_blk_en,ABB A通道Block计算使能
                                                              bit[3]:c_abb0_rxb_blk_en,ABB B通道Block计算使能
                                                              bit[4]:c_abb0_tx_en,ABB 上行通道发送使能
                                                              bit[5]:c2com_rf0_tcvr_on,RF 总工作使能
                                                              bit[6]:c2com_rf0_tx_en,RF TX工作使能
                                                              bit[30:7]:保留 */
        unsigned long  reserved           : 1;  /* bit[31]  : 保留 */
    } reg;
} CBBP_GPIO_LINE_CTRL_RPT_UNION;
#define CBBP_GPIO_LINE_CTRL_RPT_gpio_line_ctrl_rpt_START  (0)
#define CBBP_GPIO_LINE_CTRL_RPT_gpio_line_ctrl_rpt_END    (30)


/*****************************************************************************
 结构名    : CBBP_HKADC_START_TIME_UNION
 结构说明  : HKADC_START_TIME 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_start_time_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_auto_run_time : 11; /* bit[0-10] : HKADC SSI每时隙t2位置(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip，BBP在此位置对HKADC SSI RAM重新发送，并开始根据RAM控制字发送数据。
                                                                        注意：在G SDR模式，该参数不能与active_time相同 */
        unsigned long  reserved                    : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_HKADC_START_TIME_UNION;
#define CBBP_HKADC_START_TIME_cpu_hkadc_ssi_auto_run_time_START  (0)
#define CBBP_HKADC_START_TIME_cpu_hkadc_ssi_auto_run_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_HKADC_STA_CFG_UNION
 结构说明  : HKADC_STA_CFG 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000400，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_sta_cfg_reg;
    struct
    {
        unsigned long  reserved_0                           : 4;  /* bit[0-3]  : 保留 */
        unsigned long  cpu_hkadc_ssi_data_buffer_start_addr : 7;  /* bit[4-10] : 每个乒乓RAM中data_buffer起始地址。 */
        unsigned long  reserved_1                           : 5;  /* bit[11-15]: 保留 */
        unsigned long  cpu_hkadc_ssi_clk_cfg                : 3;  /* bit[16-18]: hkadc ssi延时调整，单位ssi clock周期。 */
        unsigned long  cpu_hkadc_ssi_auto_run               : 1;  /* bit[19]   : 自动运行使能，0：软件配置脉冲手动运行，1：在软件配置时刻自动运行。 */
        unsigned long  reserved_2                           : 12; /* bit[20-31]: 保留 */
    } reg;
} CBBP_HKADC_STA_CFG_UNION;
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_data_buffer_start_addr_START  (4)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_data_buffer_start_addr_END    (10)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_clk_cfg_START                 (16)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_clk_cfg_END                   (18)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_auto_run_START                (19)
#define CBBP_HKADC_STA_CFG_cpu_hkadc_ssi_auto_run_END                  (19)


/*****************************************************************************
 结构名    : CBBP_HKADC_DYN_CFG_UNION
 结构说明  : HKADC_DYN_CFG 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_dyn_cfg_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_pro_en    : 1;  /* bit[0]   : 模块工作使能，高电平有效。 */
        unsigned long  reserved_0              : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_hkadc_ssi_hold_page : 1;  /* bit[4]   : 1表示暂停发送当前RAM中数据。用法同cpu_rfic_ssi_hold_page */
        unsigned long  reserved_1              : 3;  /* bit[5-7] : 保留 */
        unsigned long  cpu_hkadc_ssi_stop_page : 1;  /* bit[8]   : 1表示停止发送当前RAM中数据并清除当前RAM所有数据。 */
        unsigned long  reserved_2              : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_HKADC_DYN_CFG_UNION;
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_pro_en_START     (0)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_pro_en_END       (0)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_hold_page_START  (4)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_hold_page_END    (4)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_stop_page_START  (8)
#define CBBP_HKADC_DYN_CFG_cpu_hkadc_ssi_stop_page_END    (8)


/*****************************************************************************
 结构名    : CBBP_HKADC_START_UNION
 结构说明  : HKADC_START 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_start_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_page_start : 1;  /* bit[0]   : 写1产生脉冲信号，手动启动指令页执行，cpu_hkadc_ssi_auto_run=0时才有效。 */
        unsigned long  reserved_0               : 4;  /* bit[1-4] : 保留 */
        unsigned long  reserved_1               : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_HKADC_START_UNION;
#define CBBP_HKADC_START_cpu_hkadc_ssi_page_start_START  (0)
#define CBBP_HKADC_START_cpu_hkadc_ssi_page_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_HKADC_FORCE_UNION
 结构说明  : HKADC_FORCE 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_force_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_force_data  : 17; /* bit[0-16] : C_HKADC_SSI 强制发送数据，cpu_hkadc_force_en=1时才有效。 */
        unsigned long  reserved                  : 13; /* bit[17-29]: 保留 */
        unsigned long  cpu_hkadc_ssi_force_pulse : 1;  /* bit[30]   : C_HKADC_SSI 强制发送脉冲 */
        unsigned long  cpu_hkadc_ssi_force_en    : 1;  /* bit[31]   : C_HKADC_SSI 强制发送使能，需同时配置cpu_hkadc_ssi_pro_en=1，或者工作状态先配cpu_hkadc_ssi_hold_page暂停后使用。 */
    } reg;
} CBBP_HKADC_FORCE_UNION;
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_data_START   (0)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_data_END     (16)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_pulse_START  (30)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_pulse_END    (30)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_en_START     (31)
#define CBBP_HKADC_FORCE_cpu_hkadc_ssi_force_en_END       (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RD_WAIT_UNION
 结构说明  : HKADC_RD_WAIT 寄存器结构定义。地址偏移量:0x0E4，初值:0x0000002A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_rd_wait_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_rd_wait_time : 9;  /* bit[0-8] : 读延迟时间，单位 19Mclock个数 */
        unsigned long  reserved                   : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_HKADC_RD_WAIT_UNION;
#define CBBP_HKADC_RD_WAIT_cpu_hkadc_ssi_rd_wait_time_START  (0)
#define CBBP_HKADC_RD_WAIT_cpu_hkadc_ssi_rd_wait_time_END    (8)


/*****************************************************************************
 结构名    : CBBP_HKADC_CLR_UNION
 结构说明  : HKADC_CLR 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_clr_reg;
    struct
    {
        unsigned long  cpu_hkadc_ssi_rd_overtime_clr    : 1;  /* bit[0]   : PD超时标志清零脉冲 */
        unsigned long  reserved_0                       : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_hkadc_ssi_rd_result_flag_clr : 1;  /* bit[4]   : PD结果有效标志清零脉冲 */
        unsigned long  reserved_1                       : 27; /* bit[5-31]: 保留 */
    } reg;
} CBBP_HKADC_CLR_UNION;
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_overtime_clr_START     (0)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_overtime_clr_END       (0)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_result_flag_clr_START  (4)
#define CBBP_HKADC_CLR_cpu_hkadc_ssi_rd_result_flag_clr_END    (4)


/*****************************************************************************
 结构名    : CBBP_HKADC_FLAG_RPT_UNION
 结构说明  : HKADC_FLAG_RPT 寄存器结构定义。地址偏移量:0x0EC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_flag_rpt_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_overtime_flag_cpu : 1;  /* bit[0]    : PD超时标志，高电平有效。 */
        unsigned long  reserved_0                     : 3;  /* bit[1-3]  : 保留 */
        unsigned long  hkadc_ssi_rd_result_flag_cpu   : 1;  /* bit[4]    : PD结果有效标志，高电平有效。 */
        unsigned long  reserved_1                     : 3;  /* bit[5-7]  : 保留 */
        unsigned long  hkadc_ssi_curr_state_rpt       : 3;  /* bit[8-10] : SSI RAM访问状态上报。 */
        unsigned long  hkadc_rd_ctrl_buff_addr        : 7;  /* bit[11-17]: 当前执行到的hkadc_ctrl buff的地址 */
        unsigned long  reserved_2                     : 2;  /* bit[18-19]: 保留 */
        unsigned long  hkadc_err_config_rpt           : 3;  /* bit[20-22]: 异常配置状态上报，如果在当前指令没有执行完，静态配置被改写，则会触发异常上报。各bit含义分别如下：
                                                                           [20]work_mode_sel被异常改写
                                                                           [21]buffer_clr_mode被异常改写
                                                                           [22]data_buffer_start_addr被异常改写 */
        unsigned long  reserved_3                     : 9;  /* bit[23-31]: 保留 */
    } reg;
} CBBP_HKADC_FLAG_RPT_UNION;
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_overtime_flag_cpu_START  (0)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_overtime_flag_cpu_END    (0)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_result_flag_cpu_START    (4)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_rd_result_flag_cpu_END      (4)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_curr_state_rpt_START        (8)
#define CBBP_HKADC_FLAG_RPT_hkadc_ssi_curr_state_rpt_END          (10)
#define CBBP_HKADC_FLAG_RPT_hkadc_rd_ctrl_buff_addr_START         (11)
#define CBBP_HKADC_FLAG_RPT_hkadc_rd_ctrl_buff_addr_END           (17)
#define CBBP_HKADC_FLAG_RPT_hkadc_err_config_rpt_START            (20)
#define CBBP_HKADC_FLAG_RPT_hkadc_err_config_rpt_END              (22)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT0_1_UNION
 结构说明  : HKADC_RESULT0_1 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result0_1_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_0_cpu : 16; /* bit[0-15] : 本时隙第0次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_1_cpu : 16; /* bit[16-31]: 本时隙第1次PD回读结果,[13:8]表示读地址，[7:0]表示读数据，无符号数，下同。 */
    } reg;
} CBBP_HKADC_RESULT0_1_UNION;
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_0_cpu_START  (0)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_0_cpu_END    (15)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_1_cpu_START  (16)
#define CBBP_HKADC_RESULT0_1_hkadc_ssi_rd_result_1_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT2_3_UNION
 结构说明  : HKADC_RESULT2_3 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result2_3_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_2_cpu : 16; /* bit[0-15] : 本时隙第2次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_3_cpu : 16; /* bit[16-31]: 本时隙第3次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT2_3_UNION;
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_2_cpu_START  (0)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_2_cpu_END    (15)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_3_cpu_START  (16)
#define CBBP_HKADC_RESULT2_3_hkadc_ssi_rd_result_3_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT4_5_UNION
 结构说明  : HKADC_RESULT4_5 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result4_5_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_4_cpu : 16; /* bit[0-15] : 本时隙第4次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_5_cpu : 16; /* bit[16-31]: 本时隙第5次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT4_5_UNION;
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_4_cpu_START  (0)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_4_cpu_END    (15)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_5_cpu_START  (16)
#define CBBP_HKADC_RESULT4_5_hkadc_ssi_rd_result_5_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT6_7_UNION
 结构说明  : HKADC_RESULT6_7 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result6_7_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_6_cpu : 16; /* bit[0-15] : 本时隙第6次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_7_cpu : 16; /* bit[16-31]: 本时隙第7次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT6_7_UNION;
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_6_cpu_START  (0)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_6_cpu_END    (15)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_7_cpu_START  (16)
#define CBBP_HKADC_RESULT6_7_hkadc_ssi_rd_result_7_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT8_9_UNION
 结构说明  : HKADC_RESULT8_9 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result8_9_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_8_cpu : 16; /* bit[0-15] : 本时隙第8次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_9_cpu : 16; /* bit[16-31]: 本时隙第9次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT8_9_UNION;
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_8_cpu_START  (0)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_8_cpu_END    (15)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_9_cpu_START  (16)
#define CBBP_HKADC_RESULT8_9_hkadc_ssi_rd_result_9_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT10_11_UNION
 结构说明  : HKADC_RESULT10_11 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result10_11_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_10_cpu : 16; /* bit[0-15] : 本时隙第10次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_11_cpu : 16; /* bit[16-31]: 本时隙第11次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT10_11_UNION;
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_10_cpu_START  (0)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_10_cpu_END    (15)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_11_cpu_START  (16)
#define CBBP_HKADC_RESULT10_11_hkadc_ssi_rd_result_11_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESUL12_13_UNION
 结构说明  : HKADC_RESUL12_13 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_resul12_13_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_12_cpu : 16; /* bit[0-15] : 本时隙第12次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_13_cpu : 16; /* bit[16-31]: 本时隙第13次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESUL12_13_UNION;
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_12_cpu_START  (0)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_12_cpu_END    (15)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_13_cpu_START  (16)
#define CBBP_HKADC_RESUL12_13_hkadc_ssi_rd_result_13_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT14_15_UNION
 结构说明  : HKADC_RESULT14_15 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result14_15_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_14_cpu : 16; /* bit[0-15] : 本时隙第14次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_15_cpu : 16; /* bit[16-31]: 本时隙第15次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT14_15_UNION;
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_14_cpu_START  (0)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_14_cpu_END    (15)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_15_cpu_START  (16)
#define CBBP_HKADC_RESULT14_15_hkadc_ssi_rd_result_15_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT16_17_UNION
 结构说明  : HKADC_RESULT16_17 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result16_17_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_16_cpu : 16; /* bit[0-15] : 本时隙第16次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_17_cpu : 16; /* bit[16-31]: 本时隙第17次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT16_17_UNION;
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_16_cpu_START  (0)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_16_cpu_END    (15)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_17_cpu_START  (16)
#define CBBP_HKADC_RESULT16_17_hkadc_ssi_rd_result_17_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT18_19_UNION
 结构说明  : HKADC_RESULT18_19 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result18_19_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_18_cpu : 16; /* bit[0-15] : 本时隙第08次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_19_cpu : 16; /* bit[16-31]: 本时隙第19次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT18_19_UNION;
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_18_cpu_START  (0)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_18_cpu_END    (15)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_19_cpu_START  (16)
#define CBBP_HKADC_RESULT18_19_hkadc_ssi_rd_result_19_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT20_21_UNION
 结构说明  : HKADC_RESULT20_21 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result20_21_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_20_cpu : 16; /* bit[0-15] : 本时隙第20次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_21_cpu : 16; /* bit[16-31]: 本时隙第21次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT20_21_UNION;
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_20_cpu_START  (0)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_20_cpu_END    (15)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_21_cpu_START  (16)
#define CBBP_HKADC_RESULT20_21_hkadc_ssi_rd_result_21_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT22_23_UNION
 结构说明  : HKADC_RESULT22_23 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result22_23_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_22_cpu : 16; /* bit[0-15] : 本时隙第22次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_23_cpu : 16; /* bit[16-31]: 本时隙第23次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT22_23_UNION;
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_22_cpu_START  (0)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_22_cpu_END    (15)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_23_cpu_START  (16)
#define CBBP_HKADC_RESULT22_23_hkadc_ssi_rd_result_23_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT24_25_UNION
 结构说明  : HKADC_RESULT24_25 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result24_25_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_24_cpu : 16; /* bit[0-15] : 本时隙第24次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_25_cpu : 16; /* bit[16-31]: 本时隙第25次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT24_25_UNION;
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_24_cpu_START  (0)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_24_cpu_END    (15)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_25_cpu_START  (16)
#define CBBP_HKADC_RESULT24_25_hkadc_ssi_rd_result_25_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT26_27_UNION
 结构说明  : HKADC_RESULT26_27 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result26_27_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_26_cpu : 16; /* bit[0-15] : 本时隙第26次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_27_cpu : 16; /* bit[16-31]: 本时隙第27次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT26_27_UNION;
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_26_cpu_START  (0)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_26_cpu_END    (15)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_27_cpu_START  (16)
#define CBBP_HKADC_RESULT26_27_hkadc_ssi_rd_result_27_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT28_29_UNION
 结构说明  : HKADC_RESULT28_29 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result28_29_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_28_cpu : 16; /* bit[0-15] : 本时隙第28次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_29_cpu : 16; /* bit[16-31]: 本时隙第29次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT28_29_UNION;
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_28_cpu_START  (0)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_28_cpu_END    (15)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_29_cpu_START  (16)
#define CBBP_HKADC_RESULT28_29_hkadc_ssi_rd_result_29_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_RESULT30_31_UNION
 结构说明  : HKADC_RESULT30_31 寄存器结构定义。地址偏移量:0x013C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_result30_31_reg;
    struct
    {
        unsigned long  hkadc_ssi_rd_result_30_cpu : 16; /* bit[0-15] : 本时隙第30次PD回读结果。 */
        unsigned long  hkadc_ssi_rd_result_31_cpu : 16; /* bit[16-31]: 本时隙第31次PD回读结果。 */
    } reg;
} CBBP_HKADC_RESULT30_31_UNION;
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_30_cpu_START  (0)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_30_cpu_END    (15)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_31_cpu_START  (16)
#define CBBP_HKADC_RESULT30_31_hkadc_ssi_rd_result_31_cpu_END    (31)


/*****************************************************************************
 结构名    : CBBP_AUXDAC_START_TIME_UNION
 结构说明  : AUXDAC_START_TIME 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_start_time_reg;
    struct
    {
        unsigned long  cpu_auxdac_active_time : 11; /* bit[0-10] : 每时隙/PCG上行PA vbias控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。 */
        unsigned long  reserved               : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_AUXDAC_START_TIME_UNION;
#define CBBP_AUXDAC_START_TIME_cpu_auxdac_active_time_START  (0)
#define CBBP_AUXDAC_START_TIME_cpu_auxdac_active_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_AUXDAC_SSI_CFG_UNION
 结构说明  : AUXDAC_SSI_CFG 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_ssi_cfg_reg;
    struct
    {
        unsigned long  cpu_auxdac_en   : 1;  /* bit[0]    : AUXDAC模块使能，高电平有效。 */
        unsigned long  reserved_0      : 7;  /* bit[1-7]  : 保留 */
        unsigned long  cpu_auxdac_data : 10; /* bit[8-17] : 每时隙软件配置的vbias控制字，无符号数。 */
        unsigned long  reserved_1      : 14; /* bit[18-31]: 保留 */
    } reg;
} CBBP_AUXDAC_SSI_CFG_UNION;
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_en_START    (0)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_en_END      (0)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_data_START  (8)
#define CBBP_AUXDAC_SSI_CFG_cpu_auxdac_data_END    (17)


/*****************************************************************************
 结构名    : CBBP_AUXDAC_START_UNION
 结构说明  : AUXDAC_START 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_start_reg;
    struct
    {
        unsigned long  cpu_auxdac_start : 1;  /* bit[0]   : w1_pulse，软件写1时产生脉冲，用于发送aucxdac vbias控制字。cpu_auxdac_force_en=1时才有效。 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_AUXDAC_START_UNION;
#define CBBP_AUXDAC_START_cpu_auxdac_start_START  (0)
#define CBBP_AUXDAC_START_cpu_auxdac_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_AUXDAC_FORCE_UNION
 结构说明  : AUXDAC_FORCE 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_force_reg;
    struct
    {
        unsigned long  cpu_auxdac_addr     : 1;  /* bit[0]   : vbias控制字地址 */
        unsigned long  reserved            : 30; /* bit[1-30]: 保留 */
        unsigned long  cpu_auxdac_force_en : 1;  /* bit[31]  : auxdac ssi强制发送使能，高电平有效。 */
    } reg;
} CBBP_AUXDAC_FORCE_UNION;
#define CBBP_AUXDAC_FORCE_cpu_auxdac_addr_START      (0)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_addr_END        (0)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_force_en_START  (31)
#define CBBP_AUXDAC_FORCE_cpu_auxdac_force_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_AUXDAC_CFG_UNION
 结构说明  : AUXDAC_CFG 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      auxdac_cfg_reg;
    struct
    {
        unsigned long  cpu_auxdac_open_cfg  : 11; /* bit[0-10] : auxdac启动控制字。 */
        unsigned long  reserved_0           : 5;  /* bit[11-15]: 保留 */
        unsigned long  cpu_auxdac_close_cfg : 11; /* bit[16-26]: auxdac关闭控制字。 */
        unsigned long  reserved_1           : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_AUXDAC_CFG_UNION;
#define CBBP_AUXDAC_CFG_cpu_auxdac_open_cfg_START   (0)
#define CBBP_AUXDAC_CFG_cpu_auxdac_open_cfg_END     (10)
#define CBBP_AUXDAC_CFG_cpu_auxdac_close_cfg_START  (16)
#define CBBP_AUXDAC_CFG_cpu_auxdac_close_cfg_END    (26)


/*****************************************************************************
 结构名    : CBBP_APT_START_TIME_UNION
 结构说明  : APT_START_TIME 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_start_time_reg;
    struct
    {
        unsigned long  cpu_apt_active_time : 11; /* bit[0-10] : 每时隙/PCG上行PA APT控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。 */
        unsigned long  reserved            : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_APT_START_TIME_UNION;
#define CBBP_APT_START_TIME_cpu_apt_active_time_START  (0)
#define CBBP_APT_START_TIME_cpu_apt_active_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_APT_CFG_UNION
 结构说明  : APT_CFG 寄存器结构定义。地址偏移量:0x184，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_cfg_reg;
    struct
    {
        unsigned long  cpu_apt_en   : 1;  /* bit[0]    : APT模块使能，高电平有效。同时输出给作为快速DCDC芯片使能。 */
        unsigned long  reserved_0   : 7;  /* bit[1-7]  : 保留 */
        unsigned long  cpu_apt_data : 7;  /* bit[8-14] : 每时隙软件配置的APT控制字，无符号数。 */
        unsigned long  reserved_1   : 17; /* bit[15-31]: 保留 */
    } reg;
} CBBP_APT_CFG_UNION;
#define CBBP_APT_CFG_cpu_apt_en_START    (0)
#define CBBP_APT_CFG_cpu_apt_en_END      (0)
#define CBBP_APT_CFG_cpu_apt_data_START  (8)
#define CBBP_APT_CFG_cpu_apt_data_END    (14)


/*****************************************************************************
 结构名    : CBBP_APT_START_UNION
 结构说明  : APT_START 寄存器结构定义。地址偏移量:0x188，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_start_reg;
    struct
    {
        unsigned long  cpu_apt_start : 1;  /* bit[0]   : w1_pulse，软件写1时产生脉冲，用于 强制发送apt控制字。 */
        unsigned long  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_APT_START_UNION;
#define CBBP_APT_START_cpu_apt_start_START  (0)
#define CBBP_APT_START_cpu_apt_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_APT_FORCE_UNION
 结构说明  : APT_FORCE 寄存器结构定义。地址偏移量:0x18C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      apt_force_reg;
    struct
    {
        unsigned long  cpu_apt_pwm_sel  : 1;  /* bit[0]   : apt pdm脉冲格式选择，0：PWM，1：PDM */
        unsigned long  reserved         : 30; /* bit[1-30]: 保留 */
        unsigned long  cpu_apt_force_en : 1;  /* bit[31]  : apt pdm强制发送使能，高电平有效。 */
    } reg;
} CBBP_APT_FORCE_UNION;
#define CBBP_APT_FORCE_cpu_apt_pwm_sel_START   (0)
#define CBBP_APT_FORCE_cpu_apt_pwm_sel_END     (0)
#define CBBP_APT_FORCE_cpu_apt_force_en_START  (31)
#define CBBP_APT_FORCE_cpu_apt_force_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_AFC_START_TIME_UNION
 结构说明  : AFC_START_TIME 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_start_time_reg;
    struct
    {
        unsigned long  cpu_afc_active_time : 11; /* bit[0-10] : 每时隙afc控制字发送时刻(sys_cnt)，无符号数，范围[0,1535或2047]，单位chip。 */
        unsigned long  reserved            : 21; /* bit[11-31]: 保留 */
    } reg;
} CBBP_AFC_START_TIME_UNION;
#define CBBP_AFC_START_TIME_cpu_afc_active_time_START  (0)
#define CBBP_AFC_START_TIME_cpu_afc_active_time_END    (10)


/*****************************************************************************
 结构名    : CBBP_AFC_CFG_UNION
 结构说明  : AFC_CFG 寄存器结构定义。地址偏移量:0x1A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_cfg_reg;
    struct
    {
        unsigned long  cpu_c_afc_pdmpwm_sel : 1;  /* bit[0]    : AFC PDM/PWM模式选择，0:PDM模式，1：PWM方式 */
        unsigned long  cpu_c_afc_width_sel  : 1;  /* bit[1]    : afc pdm控制字位宽选择 0：12bit 1：13bit. */
        unsigned long  reserved_0           : 6;  /* bit[2-7]  : 保留 */
        unsigned long  cpu_c_afc_data       : 13; /* bit[8-20] : 每时隙软件配置的AFC控制字，无符号数。 */
        unsigned long  reserved_1           : 11; /* bit[21-31]: 保留 */
    } reg;
} CBBP_AFC_CFG_UNION;
#define CBBP_AFC_CFG_cpu_c_afc_pdmpwm_sel_START  (0)
#define CBBP_AFC_CFG_cpu_c_afc_pdmpwm_sel_END    (0)
#define CBBP_AFC_CFG_cpu_c_afc_width_sel_START   (1)
#define CBBP_AFC_CFG_cpu_c_afc_width_sel_END     (1)
#define CBBP_AFC_CFG_cpu_c_afc_data_START        (8)
#define CBBP_AFC_CFG_cpu_c_afc_data_END          (20)


/*****************************************************************************
 结构名    : CBBP_AFC_START_UNION
 结构说明  : AFC_START 寄存器结构定义。地址偏移量:0x1A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_start_reg;
    struct
    {
        unsigned long  cpu_c_afc_start : 1;  /* bit[0]   : w1_pulse，软件写1时产生脉冲，用于强制发送afc控制字。 */
        unsigned long  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_AFC_START_UNION;
#define CBBP_AFC_START_cpu_c_afc_start_START  (0)
#define CBBP_AFC_START_cpu_c_afc_start_END    (0)


/*****************************************************************************
 结构名    : CBBP_AFC_FORCE_UNION
 结构说明  : AFC_FORCE 寄存器结构定义。地址偏移量:0x1AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      afc_force_reg;
    struct
    {
        unsigned long  reserved           : 31; /* bit[0-30]: 保留 */
        unsigned long  cpu_c_afc_force_en : 1;  /* bit[31]  : AFC PDM强制更新使能，高电平有效。 */
    } reg;
} CBBP_AFC_FORCE_UNION;
#define CBBP_AFC_FORCE_cpu_c_afc_force_en_START  (31)
#define CBBP_AFC_FORCE_cpu_c_afc_force_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION
 结构说明  : CPU_FE_CTRL_CKG_BYPASS 寄存器结构定义。地址偏移量:0x1B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_fe_ctrl_ckg_bypass_reg;
    struct
    {
        unsigned long  cpu_fe_ctrl_ckg_bypass : 3;  /* bit[0-2] : 前端控制模块的自动时钟门控旁路信号，1表示旁路时钟门控，即时钟常开；0表示自动时钟门控生效。
                                                                  [0] MIPI的自动时钟门控旁路控制
                                                                  [1] RFIC_SSI的自动时钟门控旁路控制
                                                                  [2] GPIO的自动时钟门控旁路控制 */
        unsigned long  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} CBBP_CPU_FE_CTRL_CKG_BYPASS_UNION;
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_cpu_fe_ctrl_ckg_bypass_START  (0)
#define CBBP_CPU_FE_CTRL_CKG_BYPASS_cpu_fe_ctrl_ckg_bypass_END    (2)


/*****************************************************************************
 结构名    : CBBP_ERR_CONFIG_CLR_UNION
 结构说明  : ERR_CONFIG_CLR 寄存器结构定义。地址偏移量:0x1B4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      err_config_clr_reg;
    struct
    {
        unsigned long  cpu_err_config_clr : 1;  /* bit[0]   : 异常配置状态清除，用于清除异常状态上报结果（0x54[14:12], 0x8c[14:12], 0xb8[14:12], 0xec[22:20]）。如果不清除，则异常结果一直保持。 */
        unsigned long  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ERR_CONFIG_CLR_UNION;
#define CBBP_ERR_CONFIG_CLR_cpu_err_config_clr_START  (0)
#define CBBP_ERR_CONFIG_CLR_cpu_err_config_clr_END    (0)


/*****************************************************************************
 结构名    : CBBP_CTRL_VALID_IND_CFG_UNION
 结构说明  : CTRL_VALID_IND_CFG 寄存器结构定义。地址偏移量:0x1B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctrl_valid_ind_cfg_reg;
    struct
    {
        unsigned long  cpu_ssi_valid_cfg_ind  : 1;  /* bit[0]   : RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_ssi_ctrl_valid_cfg之后配置本信号 */
        unsigned long  reserved_0             : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_mipi_valid_cfg_ind : 1;  /* bit[4]   : RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_mipi_ctrl_valid_cfg之后配置本信号 */
        unsigned long  reserved_1             : 3;  /* bit[5-7] : 保留 */
        unsigned long  cpu_gpio_valid_cfg_ind : 1;  /* bit[8]   : RF SSI控制指令有效标志配置使能，脉冲信号，在cpu_gpio_ctrl_valid_cfg之后配置本信号 */
        unsigned long  reserved_2             : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_CTRL_VALID_IND_CFG_UNION;
#define CBBP_CTRL_VALID_IND_CFG_cpu_ssi_valid_cfg_ind_START   (0)
#define CBBP_CTRL_VALID_IND_CFG_cpu_ssi_valid_cfg_ind_END     (0)
#define CBBP_CTRL_VALID_IND_CFG_cpu_mipi_valid_cfg_ind_START  (4)
#define CBBP_CTRL_VALID_IND_CFG_cpu_mipi_valid_cfg_ind_END    (4)
#define CBBP_CTRL_VALID_IND_CFG_cpu_gpio_valid_cfg_ind_START  (8)
#define CBBP_CTRL_VALID_IND_CFG_cpu_gpio_valid_cfg_ind_END    (8)


/*****************************************************************************
 结构名    : CBBP_CTRL_VALID_FORCE_RESET_UNION
 结构说明  : CTRL_VALID_FORCE_RESET 寄存器结构定义。地址偏移量:0x1CC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      ctrl_valid_force_reset_reg;
    struct
    {
        unsigned long  cpu_ssi_valid_reset_ind  : 1;  /* bit[0]   : RF SSI控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。 */
        unsigned long  reserved_0               : 3;  /* bit[1-3] : 保留 */
        unsigned long  cpu_mipi_valid_reset_ind : 1;  /* bit[4]   : MIPI控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。 */
        unsigned long  reserved_1               : 3;  /* bit[5-7] : 保留 */
        unsigned long  cpu_gpio_valid_reset_ind : 1;  /* bit[8]   : GPIO控制指令有效标志强制复位，脉冲信号。1有效；配置后，所有没有被清除的控制指令，都会再次执行。 */
        unsigned long  reserved_2               : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_CTRL_VALID_FORCE_RESET_UNION;
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_ssi_valid_reset_ind_START   (0)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_ssi_valid_reset_ind_END     (0)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_mipi_valid_reset_ind_START  (4)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_mipi_valid_reset_ind_END    (4)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_gpio_valid_reset_ind_START  (8)
#define CBBP_CTRL_VALID_FORCE_RESET_cpu_gpio_valid_reset_ind_END    (8)


/***======================================================================***
                     (17/20) register_define_c_fe_ctrl_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_CTRL_RAM_UNION
 结构说明  : RFIC_SSI_CTRL_RAM 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: 乒乓RAM，ctrl指令最大可配置16个
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_ctrl_ram_reg;
    struct
    {
        unsigned long  rfic_start_time : 11; /* bit[0-10] : rfic指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
                                                            二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
                                                            配置绝对时标不等于定时绝对时标，则继续等待。 */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: 保留 */
        unsigned long  rfic_s_value    : 1;  /* bit[16]   : rfic指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效 */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: 保留 */
        unsigned long  rfic_num        : 3;  /* bit[24-26]: 本条控制指令对应的rfic配置指令的个数，3bit，0~7对应配置个数为0~7，即0表示不发送 */
        unsigned long  reserved_2      : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_RFIC_SSI_CTRL_RAM_UNION;
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_start_time_START  (0)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_start_time_END    (10)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_s_value_START     (16)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_s_value_END       (16)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_num_START         (24)
#define CBBP_RFIC_SSI_CTRL_RAM_rfic_num_END           (26)


/*****************************************************************************
 结构名    : CBBP_RFIC_SSI_DATA_RAM_UNION
 结构说明  : RFIC_SSI_DATA_RAM 寄存器结构定义。地址偏移量:0x840，初值:0x00000000，宽度:32
 寄存器说明: 乒乓RAM
*****************************************************************************/
typedef union
{
    unsigned long      rfic_ssi_data_ram_reg;
    struct
    {
        unsigned long  rfic_ssi_data    : 16; /* bit[0-15] : 该部分有2种可能的格式
                                                             1）写格式：[15:0]Data RF SSI写操作时的数据信息
                                                             2) 读格式：
                                                             [15:12]Buf Addr,即RF SSI读操作时回读结果缓存Buffer对应的位置，该缓存Buffer位于公共前端模块，即bbp_comm_fe
                                                             [11]E RF SSI读操作时，用于指示最后一个读操作，1有效。
                                                             [10:0]保留 */
        unsigned long  rfic_data_addr   : 8;  /* bit[16-23]: Addr RF SSI地址信息 */
        unsigned long  rfic_ssi_wr_flag : 1;  /* bit[24]   : WR RF SSI读写标志，1表示读，0表示写 */
        unsigned long  reserved         : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_RFIC_SSI_DATA_RAM_UNION;
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_data_START     (0)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_data_END       (15)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_data_addr_START    (16)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_data_addr_END      (23)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_wr_flag_START  (24)
#define CBBP_RFIC_SSI_DATA_RAM_rfic_ssi_wr_flag_END    (24)


/*****************************************************************************
 结构名    : CBBP_MIPI_CTRL_RAM_UNION
 结构说明  : MIPI_CTRL_RAM 寄存器结构定义。地址偏移量:0xA00，初值:0x00000000，宽度:32
 寄存器说明: 乒乓RAM，ctrl指令最大可配置16个
*****************************************************************************/
typedef union
{
    unsigned long      mipi_ctrl_ram_reg;
    struct
    {
        unsigned long  mipi_start_time : 11; /* bit[0-10] : mipi指令生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
                                                            二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
                                                            配置绝对时标不等于定时绝对时标，则继续等待。 */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: 保留 */
        unsigned long  mipi_s_value    : 1;  /* bit[16]   : mipi指令生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效 */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: 保留 */
        unsigned long  mipi_num        : 2;  /* bit[24-25]: 本条控制指令对应的mipi配置指令的个数，2bit，0~3对应配置个数为0~3，即0表示不发送 */
        unsigned long  reserved_2      : 6;  /* bit[26-31]: 保留 */
    } reg;
} CBBP_MIPI_CTRL_RAM_UNION;
#define CBBP_MIPI_CTRL_RAM_mipi_start_time_START  (0)
#define CBBP_MIPI_CTRL_RAM_mipi_start_time_END    (10)
#define CBBP_MIPI_CTRL_RAM_mipi_s_value_START     (16)
#define CBBP_MIPI_CTRL_RAM_mipi_s_value_END       (16)
#define CBBP_MIPI_CTRL_RAM_mipi_num_START         (24)
#define CBBP_MIPI_CTRL_RAM_mipi_num_END           (25)


/*****************************************************************************
 结构名    : CBBP_GPIO_CTRL_RAM_UNION
 结构说明  : GPIO_CTRL_RAM 寄存器结构定义。地址偏移量:0xC00，初值:0x00000000，宽度:32
 寄存器说明: 乒乓RAM，ctrl指令最大可配置32个
*****************************************************************************/
typedef union
{
    unsigned long      gpio_ctrl_ram_reg;
    struct
    {
        unsigned long  gpio_start_time : 11; /* bit[0-10] : GPIO指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
                                                            二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
                                                            配置绝对时标不等于定时绝对时标，则继续等待。 */
        unsigned long  reserved_0      : 5;  /* bit[11-15]: 保留 */
        unsigned long  gpio_s_value    : 1;  /* bit[16]   : GPIO指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效 */
        unsigned long  reserved_1      : 7;  /* bit[17-23]: 保留 */
        unsigned long  gpio_num        : 1;  /* bit[24]   : 本条控制指令对应的GPIO配置指令的个数，1bit，1对应配置个数为1，0表示不发送 */
        unsigned long  gpio_ram_value  : 7;  /* bit[25-31]: GPIO一共64个地址,其中ctrl_buff和data_buff地址个数按照1:1分配，数据格式见接口说明书。不需要使用的地址须填零。Data的bit内容同GPIO_FORCE_DATA寄存器的内容 */
    } reg;
} CBBP_GPIO_CTRL_RAM_UNION;
#define CBBP_GPIO_CTRL_RAM_gpio_start_time_START  (0)
#define CBBP_GPIO_CTRL_RAM_gpio_start_time_END    (10)
#define CBBP_GPIO_CTRL_RAM_gpio_s_value_START     (16)
#define CBBP_GPIO_CTRL_RAM_gpio_s_value_END       (16)
#define CBBP_GPIO_CTRL_RAM_gpio_num_START         (24)
#define CBBP_GPIO_CTRL_RAM_gpio_num_END           (24)
#define CBBP_GPIO_CTRL_RAM_gpio_ram_value_START   (25)
#define CBBP_GPIO_CTRL_RAM_gpio_ram_value_END     (31)


/*****************************************************************************
 结构名    : CBBP_GPIO_DATA_RAM_UNION
 结构说明  : GPIO_DATA_RAM 寄存器结构定义。地址偏移量:0xC80，初值:0x00000000，宽度:32
 寄存器说明: 乒乓RAM
*****************************************************************************/
typedef union
{
    unsigned long      gpio_data_ram_reg;
    struct
    {
        unsigned long  gpio_data      : 31; /* bit[0-30]: 线控配置数据 */
        unsigned long  gpio_data_head : 1;  /* bit[31]  : 为0时，表示公共线控ant_pa_sel数据
                                                          为1时表示专用线控，每个bit的含义如上述bit[6:0]描述 */
    } reg;
} CBBP_GPIO_DATA_RAM_UNION;
#define CBBP_GPIO_DATA_RAM_gpio_data_START       (0)
#define CBBP_GPIO_DATA_RAM_gpio_data_END         (30)
#define CBBP_GPIO_DATA_RAM_gpio_data_head_START  (31)
#define CBBP_GPIO_DATA_RAM_gpio_data_head_END    (31)


/*****************************************************************************
 结构名    : CBBP_HKADC_SSI_CTRL_RAM_UNION
 结构说明  : HKADC_SSI_CTRL_RAM 寄存器结构定义。地址偏移量:0xD00，初值:0x00000000，宽度:32
 寄存器说明: ctrl指令最大可配置16个
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_ssi_ctrl_ram_reg;
    struct
    {
        unsigned long  hkadc_start_time : 11; /* bit[0-10] : hkadc指令的生效时刻，该域当S配置为0时有效，其配置内容为系统时标对应的位置，定时模块需要根据软件的配置选取当前工作的系统时标输出给前端控制模块，精度为chip，CBBP根据配置内容与定时模块输出的绝对时标进行比较，其存在二种情况：
                                                             二者相等或配置绝对时标小于定时绝对时标时，则读取数据Buffer内容，并发送；
                                                             配置绝对时标不等于定时绝对时标，则继续等待。 */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned long  hkadc_s_value    : 1;  /* bit[16]   : hkadc指令的生效方式，1表示立即生效，0表示按照Acitive Timing域指示时间位置生效 */
        unsigned long  reserved_1       : 7;  /* bit[17-23]: 保留 */
        unsigned long  hkadc_num        : 1;  /* bit[24]   : 本条控制指令对应的GPIO配置指令的个数，3bit，0~7对应配置个数为0~7，即0表示不发送 */
        unsigned long  reserved_2       : 7;  /* bit[25-31]: 保留 */
    } reg;
} CBBP_HKADC_SSI_CTRL_RAM_UNION;
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_start_time_START  (0)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_start_time_END    (10)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_s_value_START     (16)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_s_value_END       (16)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_num_START         (24)
#define CBBP_HKADC_SSI_CTRL_RAM_hkadc_num_END           (24)


/*****************************************************************************
 结构名    : CBBP_HKADC_SSI_DATA_RAM_UNION
 结构说明  : HKADC_SSI_DATA_RAM 寄存器结构定义。地址偏移量:0xD40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      hkadc_ssi_data_ram_reg;
    struct
    {
        unsigned long  hkadc_data     : 16; /* bit[0-15] : 该部分有3种可能的格式，分别如下：
                                                           1. 当hkadc_cfg_type=0时，如果bit[15]=0,表示写操作，[14:8]为写地址，[7:0]为写数据
                                                           2. 当hkadc_cfg_type=0时，如果bit[15]=1,表示读操作，[14:8]为写地址，[7:3]表示HKADC SSI读操作时回读结果缓存Buffer对应的位置，该缓存Buffer位于本模块内部，缓存区大小设置为32
                                                           [2]HKADC SSI读操作时，用于指示最后一个读操作，1有效，当该bit有效，前端控制模块在本次HKADC SSI读操作完成后产生中断上报，触发软件读取HKADC SSI回读结果
                                                           3. 当hkadc_cfg_type=1时，如果bit[15]=0,表示HKADC通道请求操作指令，[15:1]为保留位，[0]为请求是否生效 */
        unsigned long  hkadc_cfg_type : 1;  /* bit[16]   : 配置指令的类型，0表示为HKADC SSI操作指令，1表示为HKADC通道请求操作指令 */
        unsigned long  reserved       : 15; /* bit[17-31]: 保留 */
    } reg;
} CBBP_HKADC_SSI_DATA_RAM_UNION;
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_data_START      (0)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_data_END        (15)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_cfg_type_START  (16)
#define CBBP_HKADC_SSI_DATA_RAM_hkadc_cfg_type_END    (16)


/***======================================================================***
                     (18/20) register_define_sdr_gdrx_gauge
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_GDRX_GAUGE_EN_CNF_UNION
 结构说明  : GDRX_GAUGE_EN_CNF 寄存器结构定义。地址偏移量:0x0000，初值:0x0000000A，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_gauge_en_cnf_reg;
    struct
    {
        unsigned long  gdrx_gauge_len  : 17; /* bit[0-16] : 时钟校准32KHz时钟个数 */
        unsigned long  reserved        : 13; /* bit[17-29]: 保留 */
        unsigned long  gdrx_gauge_en   : 1;  /* bit[30]   : 时钟校准使能，写1开启。自清零，写0无意义。 */
        unsigned long  gdrx_gauge_stop : 1;  /* bit[31]   : GDRX停止脉冲，写1停止。自清零，写0无意义。 */
    } reg;
} CBBP_GDRX_GAUGE_EN_CNF_UNION;
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_START   (0)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_len_END     (16)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_START    (30)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_en_END      (30)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_START  (31)
#define CBBP_GDRX_GAUGE_EN_CNF_gdrx_gauge_stop_END    (31)


/*****************************************************************************
 结构名    : CBBP_GAUGE_RESULT_RPT_UNION
 结构说明  : GAUGE_RESULT_RPT 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gauge_result_rpt_reg;
    struct
    {
        unsigned long  gdrx_gauge_result : 28; /* bit[0-27] : 时钟校准结果，测量周期内104M钟个数 */
        unsigned long  reserved          : 2;  /* bit[28-29]: 保留 */
        unsigned long  gdrx_gauge_state  : 1;  /* bit[30]   : 测量状态查询。1，正在测量。 */
        unsigned long  gdrx_sleep_state  : 1;  /* bit[31]   : 睡眠状态查询。1，正在睡眠。 */
    } reg;
} CBBP_GAUGE_RESULT_RPT_UNION;
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_START  (0)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_result_END    (27)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_START   (30)
#define CBBP_GAUGE_RESULT_RPT_gdrx_gauge_state_END     (30)
#define CBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_START   (31)
#define CBBP_GAUGE_RESULT_RPT_gdrx_sleep_state_END     (31)


/*****************************************************************************
 结构名    : CBBP_IMI_INT_TDMA_QB_UNION
 结构说明  : IMI_INT_TDMA_QB 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      imi_int_tdma_qb_reg;
    struct
    {
        unsigned long  imi_int_tdma_qb : 13; /* bit[0-12] : IMI时钟中断上报时GTC的TDMA QB计数，测试用 */
        unsigned long  reserved        : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_IMI_INT_TDMA_QB_UNION;
#define CBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_START  (0)
#define CBBP_IMI_INT_TDMA_QB_imi_int_tdma_qb_END    (12)


/*****************************************************************************
 结构名    : CBBP_SLEEP_INT_TDMA_QB_UNION
 结构说明  : SLEEP_INT_TDMA_QB 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      sleep_int_tdma_qb_reg;
    struct
    {
        unsigned long  sleep_int_tdma_qb : 13; /* bit[0-12] : 32K时钟中断上报时GTC的TDMA QB计数，测试用 */
        unsigned long  reserved          : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_SLEEP_INT_TDMA_QB_UNION;
#define CBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_START  (0)
#define CBBP_SLEEP_INT_TDMA_QB_sleep_int_tdma_qb_END    (12)


/***======================================================================***
                     (19/20) register_define_sdr_g_timing
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_DRX_TEST_CFG_UNION
 结构说明  : DRX_TEST_CFG 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      drx_test_cfg_reg;
    struct
    {
        unsigned long  reserved_0           : 8;  /* bit[0-7] : 保留 */
        unsigned long  cpu_drx_test_mode_en : 1;  /* bit[8]   : 1表示DRX测试模式使能，此时GTC时钟应不关闭，用于DRX唤醒后的定时维护情况的比对。正常使用下该信号应该被置0，测试用 */
        unsigned long  reserved_1           : 23; /* bit[9-31]: 保留 */
    } reg;
} CBBP_DRX_TEST_CFG_UNION;
#define CBBP_DRX_TEST_CFG_cpu_drx_test_mode_en_START  (8)
#define CBBP_DRX_TEST_CFG_cpu_drx_test_mode_en_END    (8)


/*****************************************************************************
 结构名    : CBBP_G2_GTC_FRM_OFFSET_RPT_UNION
 结构说明  : G2_GTC_FRM_OFFSET_RPT 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_frm_offset_rpt_reg;
    struct
    {
        unsigned long  gtc_frm_it_offset : 13; /* bit[0-12] : 帧中断与TimeBase时间偏差，单位qb，测试用 */
        unsigned long  reserved          : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_G2_GTC_FRM_OFFSET_RPT_UNION;
#define CBBP_G2_GTC_FRM_OFFSET_RPT_gtc_frm_it_offset_START  (0)
#define CBBP_G2_GTC_FRM_OFFSET_RPT_gtc_frm_it_offset_END    (12)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION
 结构说明  : G2_CPU_GTC_T1_T2_T3_CNG 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_t1_t2_t3_cng_reg;
    struct
    {
        unsigned long  cpu_gtc_t1_cnt : 11; /* bit[0-10] : 精简帧号维护机制中的T1初始值，该参数值与cpu_gtc_t2_cnt，cpu_gtc_t3_cnt，
                                                           cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T1值 */
        unsigned long  reserved_0     : 5;  /* bit[11-15]: 保留 */
        unsigned long  cpu_gtc_t2_cnt : 5;  /* bit[16-20]: 精简帧号维护机制中的T2初始值，该参数值与cpu_gtc_t1_cnt，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号
                                                           cpu_gtc_t3_cnt，cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T2值 */
        unsigned long  reserved_1     : 3;  /* bit[21-23]: 保留 */
        unsigned long  cpu_gtc_t3_cnt : 6;  /* bit[24-29]: 精简帧号维护机制中的T3初始值，该参数值与cpu_gtc_t1_cnt，
                                                           cpu_gtc_t2_cnt，cpu_gtc_fn_low，cpu_gtc_fn_high一起用于GTC内部帧号维护寄存器的初始化，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号的T3值 */
        unsigned long  reserved_2     : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_CPU_GTC_T1_T2_T3_CNG_UNION;
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_START  (0)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t1_cnt_END    (10)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_START  (16)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t2_cnt_END    (20)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_START  (24)
#define CBBP_G2_CPU_GTC_T1_T2_T3_CNG_cpu_gtc_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION
 结构说明  : G2_GTC_T1_T2_T3_RPT_CPU 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_t1_t2_t3_rpt_cpu_reg;
    struct
    {
        unsigned long  gtc_t1_cnt : 11; /* bit[0-10] : GTC内部维护的T1计数器上报 */
        unsigned long  reserved_0 : 5;  /* bit[11-15]: 保留 */
        unsigned long  gtc_t2_cnt : 5;  /* bit[16-20]: GTC内部维护的T2计数器上报 */
        unsigned long  reserved_1 : 3;  /* bit[21-23]: 保留 */
        unsigned long  gtc_t3_cnt : 6;  /* bit[24-29]: GTC内部维护的T3计数器上报 */
        unsigned long  reserved_2 : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_GTC_T1_T2_T3_RPT_CPU_UNION;
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_START  (0)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t1_cnt_END    (10)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_START  (16)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t2_cnt_END    (20)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_START  (24)
#define CBBP_G2_GTC_T1_T2_T3_RPT_CPU_gtc_t3_cnt_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION
 结构说明  : G2_CPU_GTC_FRM_OFFSET_CFG 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_frm_offset_cfg_reg;
    struct
    {
        unsigned long  cpu_gtc_frm_offset       : 13; /* bit[0-12] : CPU配置的gtc_frm_offset参数 */
        unsigned long  reserved_0               : 3;  /* bit[13-15]: 保留 */
        unsigned long  cpu_gtc_frm_it_offset    : 13; /* bit[16-28]: CPU配置的gtc_frm_it_offset参数 */
        unsigned long  reserved_1               : 2;  /* bit[29-30]: 保留 */
        unsigned long  cpu_gtc_frm_offset_wr_en : 1;  /* bit[31]   : CPU配置的cpu_gtc_frm_offset，cpu_gtc_frm_it_offset立即生效指示信号，逻辑自清零。(不同类型寄存器，能否在同一地址生成) */
    } reg;
} CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_UNION;
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_START        (0)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_END          (12)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_START     (16)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_it_offset_END       (28)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_START  (31)
#define CBBP_G2_CPU_GTC_FRM_OFFSET_CFG_cpu_gtc_frm_offset_wr_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_GTC_FN_CFG_UNION
 结构说明  : G2_CPU_GTC_FN_CFG 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_gtc_fn_cfg_reg;
    struct
    {
        unsigned long  cpu_gtc_fn_low   : 11; /* bit[0-10] : CPU配置的TDMA帧号低位0~26x51-1循环计数, CPU配置后，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号 */
        unsigned long  reserved_0       : 5;  /* bit[11-15]: 保留 */
        unsigned long  cpu_gtc_fn_high  : 11; /* bit[16-26]: CPU配置TDMA帧号高位0~2047循环计数，低位计满后，高位才加1；CPU配置后，在GTC的TDMA帧边界处生效,所以应配置为下一帧的帧号 */
        unsigned long  reserved_1       : 4;  /* bit[27-30]: 保留 */
        unsigned long  cpu_gtc_fn_wr_en : 1;  /* bit[31]   : 帧号初始化信号，1有效，逻辑自清零，只有当需要T1,T2,T3，fn_low，fn_high都写入后方可对该bit置1 */
    } reg;
} CBBP_G2_CPU_GTC_FN_CFG_UNION;
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_low_START    (0)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_low_END      (10)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_high_START   (16)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_high_END     (26)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_wr_en_START  (31)
#define CBBP_G2_CPU_GTC_FN_CFG_cpu_gtc_fn_wr_en_END    (31)


/*****************************************************************************
 结构名    : CBBP_G2_GTC_FN_RPT_UNION
 结构说明  : G2_GTC_FN_RPT 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_gtc_fn_rpt_reg;
    struct
    {
        unsigned long  gtc_fn_low  : 11; /* bit[0-10] : GTC此时实际帧号低位 */
        unsigned long  reserved_0  : 5;  /* bit[11-15]: 保留 */
        unsigned long  gtc_fn_high : 11; /* bit[16-26]: GTC此时实际帧号高位 */
        unsigned long  reserved_1  : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_G2_GTC_FN_RPT_UNION;
#define CBBP_G2_GTC_FN_RPT_gtc_fn_low_START   (0)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_low_END     (10)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_high_START  (16)
#define CBBP_G2_GTC_FN_RPT_gtc_fn_high_END    (26)


/*****************************************************************************
 结构名    : CBBP_GTC_QB_RPT_UNION
 结构说明  : GTC_QB_RPT 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gtc_qb_rpt_reg;
    struct
    {
        unsigned long  gtc_tdma_qb  : 13; /* bit[0-12] : 当前时刻TDMA的QB计数值 */
        unsigned long  reserved_0   : 3;  /* bit[13-15]: 保留 */
        unsigned long  gtc_timebase : 13; /* bit[16-28]: 绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用 */
        unsigned long  reserved_1   : 3;  /* bit[29-31]: 保留 */
    } reg;
} CBBP_GTC_QB_RPT_UNION;
#define CBBP_GTC_QB_RPT_gtc_tdma_qb_START   (0)
#define CBBP_GTC_QB_RPT_gtc_tdma_qb_END     (12)
#define CBBP_GTC_QB_RPT_gtc_timebase_START  (16)
#define CBBP_GTC_QB_RPT_gtc_timebase_END    (28)


/*****************************************************************************
 结构名    : CBBP_TIMEBASE_RPT_UNION
 结构说明  : TIMEBASE_RPT 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      timebase_rpt_reg;
    struct
    {
        unsigned long  gtc_timebase_qb     : 13; /* bit[0-12] : 绝对时标QB上报，计数范围0~4999，对应一帧的长度。该值只与复位时刻有关，测试用 */
        unsigned long  reserved_0          : 3;  /* bit[13-15]: 保留 */
        unsigned long  gtc_timebase_fn_low : 11; /* bit[16-26]: 绝对时标帧号上报，该值变化时刻在gtc_timebase_qb为4999处，计数范围0~2047，测试用 */
        unsigned long  reserved_1          : 5;  /* bit[27-31]: 保留 */
    } reg;
} CBBP_TIMEBASE_RPT_UNION;
#define CBBP_TIMEBASE_RPT_gtc_timebase_qb_START      (0)
#define CBBP_TIMEBASE_RPT_gtc_timebase_qb_END        (12)
#define CBBP_TIMEBASE_RPT_gtc_timebase_fn_low_START  (16)
#define CBBP_TIMEBASE_RPT_gtc_timebase_fn_low_END    (26)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_INT_STA_UNION
 结构说明  : G2_CPU_INT_STA 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_sta_reg;
    struct
    {
        unsigned long  int_state_cpu : 30; /* bit[0-29] : [0] TDMA帧中断请求，1表示中断请求，0表示无中断请求，下同
                                                          [1] GTC PAGE中断请求
                                                          [2] 同步搜索中断请求
                                                          [3] 译码数据上报中断请求
                                                          [4] 时隙0中断请求，1有效
                                                          [5] 时隙1中断请求
                                                          [6] 时隙2中断请求
                                                          [7] 时隙3中断请求
                                                          [8] 时隙4中断请求
                                                          [9] 时隙5中断请求
                                                          [10] 时隙6中断请求
                                                          [11] 时隙7中断请求
                                                          [12] 可编程中断0请求
                                                          [13] 可编程中断1请求
                                                          [14] 可编程中断2请求
                                                          [15] 可编程中断3请求
                                                          [16] 可编程中断4请求
                                                          [17] 可编程中断5请求
                                                          [18] 可编程中断6请求
                                                          [19] 可编程中断7请求
                                                          [23:20]保留
                                                          [24] 时钟测量中断
                                                          [28] 电平测量结束中断
                                                          [29] 解调结束中断 */
        unsigned long  reserved      : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_CPU_INT_STA_UNION;
#define CBBP_G2_CPU_INT_STA_int_state_cpu_START  (0)
#define CBBP_G2_CPU_INT_STA_int_state_cpu_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_INT_MASK_UNION
 结构说明  : G2_CPU_INT_MASK 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_mask_reg;
    struct
    {
        unsigned long  cpu_int_mask : 30; /* bit[0-29] : [0] TDMA帧中断屏蔽信号，1表示中断请求屏蔽，0表示该中断不屏蔽，下同
                                                         [1] GTC PAGE中断屏蔽寄存器
                                                         [2] 同步搜索中断屏蔽寄存器
                                                         [3] 译码数据上报中断屏蔽寄存器
                                                         [4] 时隙0中断屏蔽寄存器，1有效
                                                         [5] 时隙1中断屏蔽寄存器
                                                         [6] 时隙2中断屏蔽寄存器
                                                         [7] 时隙3中断屏蔽寄存器
                                                         [8] 时隙4中断屏蔽寄存器
                                                         [9] 时隙5中断屏蔽寄存器
                                                         [10] 时隙6中断屏蔽寄存器
                                                         [11] 时隙7中断屏蔽寄存器
                                                         [12] 可编程中断0屏蔽寄存器
                                                         [13] 可编程中断1屏蔽寄存器
                                                         [14] 可编程中断2屏蔽寄存器
                                                         [15] 可编程中断3屏蔽寄存器
                                                         [16] 可编程中断4屏蔽寄存器
                                                         [17] 可编程中断5屏蔽寄存器
                                                         [18] 可编程中断6屏蔽寄存器
                                                         [19] 可编程中断7屏蔽寄存器
                                                         [24] 时钟测量中断屏蔽寄存器
                                                         [28] 电平测量结束中断屏蔽寄存器
                                                         [29] 解调结束中断屏蔽寄存器 */
        unsigned long  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_CPU_INT_MASK_UNION;
#define CBBP_G2_CPU_INT_MASK_cpu_int_mask_START  (0)
#define CBBP_G2_CPU_INT_MASK_cpu_int_mask_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_CPU_INT_CLR_UNION
 结构说明  : G2_CPU_INT_CLR 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_cpu_int_clr_reg;
    struct
    {
        unsigned long  cpu_int_clr : 30; /* bit[0-29] : [0] TDMA帧中断清零信号，1表示中断请求清除，0表示该中断不清除
                                                        下面描述相同
                                                        [1] GTC PAGE中断清零寄存器
                                                        [2] 同步搜索中断清零信号
                                                        [3] 译码数据上报中断清零信号
                                                        [4] 时隙0中断清零信号，1有效
                                                        [5] 时隙1中断清零信号
                                                        [6] 时隙2中断清零信号
                                                        [7] 时隙3中断清零信号
                                                        [8] 时隙4中断清零信号
                                                        [9] 时隙5中断清零信号
                                                        [10] 时隙6中断清零信号
                                                        [11] 时隙7中断清零信号
                                                        [12] 可编程中断0清零信号
                                                        [13] 可编程中断1清零信号
                                                        [14] 可编程中断2清零信号
                                                        [15] 可编程中断3清零信号
                                                        [16] 可编程中断4清零信号
                                                        [17] 可编程中断5清零信号
                                                        [18] 可编程中断6清零信号
                                                        [19] 可编程中断7清零信号
                                                        [24] 时钟测量中断清零信号
                                                        [28] 电平测量结束中断清零信号
                                                        [29] 解调结束中断清零信号 */
        unsigned long  reserved    : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_CPU_INT_CLR_UNION;
#define CBBP_G2_CPU_INT_CLR_cpu_int_clr_START  (0)
#define CBBP_G2_CPU_INT_CLR_cpu_int_clr_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_DSP_INT_STA_UNION
 结构说明  : G2_DSP_INT_STA 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_sta_reg;
    struct
    {
        unsigned long  dsp_int_sta : 30; /* bit[0-29] : [0] TDMA帧中断请求，1表示中断请求，0表示无中断请求，下同
                                                        [1] GTC PAGE中断请求
                                                        [2] 同步搜索中断请求
                                                        [3] 译码数据上报中断请求
                                                        [4] 时隙0中断请求，1有效
                                                        [5] 时隙1中断请求
                                                        [6] 时隙2中断请求
                                                        [7] 时隙3中断请求
                                                        [8] 时隙4中断请求
                                                        [9] 时隙5中断请求
                                                        [10] 时隙6中断请求
                                                        [11] 时隙7中断请求
                                                        [12] 可编程中断0请求
                                                        [13] 可编程中断1请求
                                                        [14] 可编程中断2请求
                                                        [15] 可编程中断3请求
                                                        [16] 可编程中断4请求
                                                        [17] 可编程中断5请求
                                                        [18] 可编程中断6请求
                                                        [19] 可编程中断7请求
                                                        [24] CTU异系统测量中断0
                                                        [25] CTU异系统测量中断1
                                                        [26] CTU异系统测量中断2
                                                        [27] 时钟测量中断
                                                        [28] 电平测量结束中断
                                                        [29]  解调结束中断 */
        unsigned long  reserved    : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_DSP_INT_STA_UNION;
#define CBBP_G2_DSP_INT_STA_dsp_int_sta_START  (0)
#define CBBP_G2_DSP_INT_STA_dsp_int_sta_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_DSP_INT_MASK_UNION
 结构说明  : G2_DSP_INT_MASK 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_mask_reg;
    struct
    {
        unsigned long  dsp_int_mask : 30; /* bit[0-29] : [0] TDMA帧中断屏蔽信号，1表示中断请求屏蔽，0表示该中断不屏蔽
                                                         [1] GTC PAGE中断屏蔽寄存器
                                                         [2] 同步搜索中断屏蔽寄存器
                                                         [3] 译码数据上报中断屏蔽寄存器
                                                         [4] 时隙0中断屏蔽寄存器，1有效
                                                         [5] 时隙1中断屏蔽寄存器
                                                         [6] 时隙2中断屏蔽寄存器
                                                         [7] 时隙3中断屏蔽寄存器
                                                         [8] 时隙4中断屏蔽寄存器
                                                         [9] 时隙5中断屏蔽寄存器
                                                         [10] 时隙6中断屏蔽寄存器
                                                         [11] 时隙7中断屏蔽寄存器
                                                         [12] 可编程中断0屏蔽寄存器
                                                         [13] 可编程中断1屏蔽寄存器
                                                         [14] 可编程中断2屏蔽寄存器
                                                         [15] 可编程中断3屏蔽寄存器
                                                         [16] 可编程中断4屏蔽寄存器
                                                         [17] 可编程中断5屏蔽寄存器
                                                         [18] 可编程中断6屏蔽寄存器
                                                         [19] 可编程中断7屏蔽寄存器
                                                         [24] CTU异系统测量中断0
                                                         [25] CTU异系统测量中断1
                                                         [26] CTU异系统测量中断2
                                                         [27] 时钟测量中断
                                                         [28] 电平测量结束中断屏蔽寄存器
                                                         [29] 解调结束中断屏蔽寄存器 */
        unsigned long  reserved     : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_DSP_INT_MASK_UNION;
#define CBBP_G2_DSP_INT_MASK_dsp_int_mask_START  (0)
#define CBBP_G2_DSP_INT_MASK_dsp_int_mask_END    (29)


/*****************************************************************************
 结构名    : CBBP_G2_DSP_INT_CLR_UNION
 结构说明  : G2_DSP_INT_CLR 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      g2_dsp_int_clr_reg;
    struct
    {
        unsigned long  dsp_int_clr : 30; /* bit[0-29] : [0] TDMA帧中断清零信号，1表示中断请求清除，0表示该中断不清除
                                                        [1] GTC PAGE中断清零寄存器
                                                        [2] 同步搜索中断清零信号
                                                        [3] 译码数据上报中断清零信号
                                                        [4] 时隙0中断清零信号，1有效
                                                        [5] 时隙1中断清零信号
                                                        [6] 时隙2中断清零信号
                                                        [7] 时隙3中断清零信号
                                                        [8] 时隙4中断清零信号
                                                        [9] 时隙5中断清零信号
                                                        [10] 时隙6中断清零信号
                                                        [11] 时隙7中断清零信号
                                                        [12] 可编程中断0清零信号
                                                        [13] 可编程中断1清零信号
                                                        [14] 可编程中断2清零信号
                                                        [15] 可编程中断3清零信号
                                                        [16] 可编程中断4清零信号
                                                        [17] 可编程中断5清零信号
                                                        [18] 可编程中断6清零信号
                                                        [19] 可编程中断7清零信号
                                                        [23:20]保留
                                                        [24] CTU异系统测量中断0
                                                        [25] CTU异系统测量中断1
                                                        [26] CTU异系统测量中断2
                                                        [27] 时钟测量中断
                                                        [28] 电平测量结束中断清零信号
                                                        [29] 解调结束中断清零信号 */
        unsigned long  reserved    : 2;  /* bit[30-31]: 保留 */
    } reg;
} CBBP_G2_DSP_INT_CLR_UNION;
#define CBBP_G2_DSP_INT_CLR_dsp_int_clr_START  (0)
#define CBBP_G2_DSP_INT_CLR_dsp_int_clr_END    (29)


/*****************************************************************************
 结构名    : CBBP_TDMA_SLOT_INT1_UNION
 结构说明  : TDMA_SLOT_INT1 寄存器结构定义。地址偏移量:0x40，初值:0x00FF0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tdma_slot_int1_reg;
    struct
    {
        unsigned long  tdma_slot_int1_offset : 10; /* bit[0-9]  : G软化可配置定时中断时隙内位置，取值范围0~624，单位Qb */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: 保留 */
        unsigned long  tdma_slot_int1_mask   : 8;  /* bit[16-23]: G软化可配置定时中断mask：
                                                                  bit16，1表示屏蔽tdma帧内时隙0内中断；
                                                                  bit17，1表示屏蔽tdma帧内时隙1内中断；
                                                                  … */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: 保留 */
    } reg;
} CBBP_TDMA_SLOT_INT1_UNION;
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_offset_START  (0)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_offset_END    (9)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_mask_START    (16)
#define CBBP_TDMA_SLOT_INT1_tdma_slot_int1_mask_END      (23)


/*****************************************************************************
 结构名    : CBBP_TDMA_SLOT_INT2_UNION
 结构说明  : TDMA_SLOT_INT2 寄存器结构定义。地址偏移量:0x44，初值:0x00FF0000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      tdma_slot_int2_reg;
    struct
    {
        unsigned long  tdma_slot_int2_offset : 10; /* bit[0-9]  : G软化可配置定时中断时隙内位置，取值范围0~624，单位Qb */
        unsigned long  reserved_0            : 6;  /* bit[10-15]: 保留 */
        unsigned long  tdma_slot_int2_mask   : 8;  /* bit[16-23]: G软化可配置定时中断mask：
                                                                  bit16，1表示屏蔽tdma帧内时隙0内中断；
                                                                  bit17，1表示屏蔽tdma帧内时隙1内中断；
                                                                  … */
        unsigned long  reserved_1            : 8;  /* bit[24-31]: 保留 */
    } reg;
} CBBP_TDMA_SLOT_INT2_UNION;
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_offset_START  (0)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_offset_END    (9)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_mask_START    (16)
#define CBBP_TDMA_SLOT_INT2_tdma_slot_int2_mask_END      (23)


/*****************************************************************************
 结构名    : CBBP_GDRX_SLEEP_POINT_UNION
 结构说明  : GDRX_SLEEP_POINT 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      gdrx_sleep_point_reg;
    struct
    {
        unsigned long  gdrx_sleep_point : 13; /* bit[0-12] : 定点睡眠模式下，睡眠起始Qb时刻（TDMA）时刻，该参数是基于TDMA时标gtc_tdma_qb的。 */
        unsigned long  reserved         : 19; /* bit[13-31]: 保留 */
    } reg;
} CBBP_GDRX_SLEEP_POINT_UNION;
#define CBBP_GDRX_SLEEP_POINT_gdrx_sleep_point_START  (0)
#define CBBP_GDRX_SLEEP_POINT_gdrx_sleep_point_END    (12)


/*****************************************************************************
 结构名    : CBBP_CPU_TRANS_COMP_UNION
 结构说明  : CPU_TRANS_COMP 寄存器结构定义。地址偏移量:0x04C，初值:0x00000010，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      cpu_trans_comp_reg;
    struct
    {
        unsigned long  cpu_trans_comp : 10; /* bit[0-9]  : DRX连线优化，ON区到OFF区补偿，单位Qb，默认值16 */
        unsigned long  reserved       : 22; /* bit[10-31]: 保留 */
    } reg;
} CBBP_CPU_TRANS_COMP_UNION;
#define CBBP_CPU_TRANS_COMP_cpu_trans_comp_START  (0)
#define CBBP_CPU_TRANS_COMP_cpu_trans_comp_END    (9)


/***======================================================================***
                     (20/20) register_define_sdr_g_int
 ***======================================================================***/
/*****************************************************************************
 结构名    : CBBP_DSP_SDR_G_INT_EN_UNION
 结构说明  : DSP_SDR_G_INT_EN 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_en_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_en : 1;  /* bit[0]   : 送给DSP的g软化中断使能，1表示打开中断 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_DSP_SDR_G_INT_EN_UNION;
#define CBBP_DSP_SDR_G_INT_EN_dsp_sdr_g_int_en_START  (0)
#define CBBP_DSP_SDR_G_INT_EN_dsp_sdr_g_int_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_DSP_SDR_G_INT_CLR_UNION
 结构说明  : DSP_SDR_G_INT_CLR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_clr_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_clr : 2;  /* bit[0-1] : 中断清零信号，软件配置1，清除相应的bit
                                                             bit0：可配置g定时中断1；
                                                             bit1：可配置g定时中断2； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_DSP_SDR_G_INT_CLR_UNION;
#define CBBP_DSP_SDR_G_INT_CLR_dsp_sdr_g_int_clr_START  (0)
#define CBBP_DSP_SDR_G_INT_CLR_dsp_sdr_g_int_clr_END    (1)


/*****************************************************************************
 结构名    : CBBP_DSP_SDR_G_INT_MASK_UNION
 结构说明  : DSP_SDR_G_INT_MASK 寄存器结构定义。地址偏移量:0x0008，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_mask_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_mask : 2;  /* bit[0-1] : 中断mask信号，软件配置1，相应的bit中断不产生
                                                              bit0：可配置g定时中断1；
                                                              bit1：可配置g定时中断2； */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_DSP_SDR_G_INT_MASK_UNION;
#define CBBP_DSP_SDR_G_INT_MASK_dsp_sdr_g_int_mask_START  (0)
#define CBBP_DSP_SDR_G_INT_MASK_dsp_sdr_g_int_mask_END    (1)


/*****************************************************************************
 结构名    : CBBP_DSP_SDR_G_INT_STA_UNION
 结构说明  : DSP_SDR_G_INT_STA 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      dsp_sdr_g_int_sta_reg;
    struct
    {
        unsigned long  dsp_sdr_g_int_sta : 2;  /* bit[0-1] : 中断状态信号，1表示相应的中断上报
                                                             bit0：可配置g定时中断1；
                                                             bit1：可配置g定时中断2； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_DSP_SDR_G_INT_STA_UNION;
#define CBBP_DSP_SDR_G_INT_STA_dsp_sdr_g_int_sta_START  (0)
#define CBBP_DSP_SDR_G_INT_STA_dsp_sdr_g_int_sta_END    (1)


/*****************************************************************************
 结构名    : CBBP_ARM_SDR_G_INT_EN_UNION
 结构说明  : ARM_SDR_G_INT_EN 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_en_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_en : 1;  /* bit[0]   : 送给ARM的g软化中断使能，1表示打开中断 */
        unsigned long  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} CBBP_ARM_SDR_G_INT_EN_UNION;
#define CBBP_ARM_SDR_G_INT_EN_arm_sdr_g_int_en_START  (0)
#define CBBP_ARM_SDR_G_INT_EN_arm_sdr_g_int_en_END    (0)


/*****************************************************************************
 结构名    : CBBP_ARM_SDR_G_INT_CLR_UNION
 结构说明  : ARM_SDR_G_INT_CLR 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_clr_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_clr : 2;  /* bit[0-1] : ARM中断清零信号，软件配置1，清除相应的bit
                                                             bit0：可配置g定时中断1；
                                                             bit1：可配置g定时中断2； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_ARM_SDR_G_INT_CLR_UNION;
#define CBBP_ARM_SDR_G_INT_CLR_arm_sdr_g_int_clr_START  (0)
#define CBBP_ARM_SDR_G_INT_CLR_arm_sdr_g_int_clr_END    (1)


/*****************************************************************************
 结构名    : CBBP_ARM_SDR_G_INT_MASK_UNION
 结构说明  : ARM_SDR_G_INT_MASK 寄存器结构定义。地址偏移量:0x0018，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_mask_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_mask : 2;  /* bit[0-1] : ARM中断mask信号，软件配置1，相应的bit中断不产生
                                                              bit0：可配置g定时中断1；
                                                              bit1：可配置g定时中断2； */
        unsigned long  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_ARM_SDR_G_INT_MASK_UNION;
#define CBBP_ARM_SDR_G_INT_MASK_arm_sdr_g_int_mask_START  (0)
#define CBBP_ARM_SDR_G_INT_MASK_arm_sdr_g_int_mask_END    (1)


/*****************************************************************************
 结构名    : CBBP_ARM_SDR_G_INT_STA_UNION
 结构说明  : ARM_SDR_G_INT_STA 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned long      arm_sdr_g_int_sta_reg;
    struct
    {
        unsigned long  arm_sdr_g_int_sta : 2;  /* bit[0-1] : ARM中断状态信号，1表示相应的中断上报
                                                             bit0：可配置g定时中断1；
                                                             bit1：可配置g定时中断2； */
        unsigned long  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} CBBP_ARM_SDR_G_INT_STA_UNION;
#define CBBP_ARM_SDR_G_INT_STA_arm_sdr_g_int_sta_START  (0)
#define CBBP_ARM_SDR_G_INT_STA_arm_sdr_g_int_sta_END    (1)




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

#endif /* end of bbp_cdma_interface.h */
