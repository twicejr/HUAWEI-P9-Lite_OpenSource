

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_GUC_BBPMST_INTERFACE_H__
#define __BBP_GUC_BBPMST_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_guc_bbpmst
 ***======================================================================***/
/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch0_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC000)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC004)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH0_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC008)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH0_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC00C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（系统位）配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（系统位）配置内部写通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC010)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC014)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC018)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch1_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC020)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC024)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH1_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC028)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH1_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC02C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（第一校验位）配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（第一校验位）配置内部写通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC030)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC034)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC038)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch2_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC040)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC044)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH2_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC048)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH2_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC04C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（第二校验位）配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（第二校验位）配置内部写通道使用的异步fifo偏移地址，默认值为0x20
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC050)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC054)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC058)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch3_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC060)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC064)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH3_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC068)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH3_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC06C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码上报外移（data部分）配置内部写通道使用的异步fifo深度，默认值为0x07
 bit[15:8]   U模译码上报外移（data部分）配置内部写通道使用的异步fifo偏移地址，默认值为0x30
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC070)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC074)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC078)

/* 寄存器说明：
 bit[31:16]  读通道的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
 bit[15:0]   写通道的空闲/忙碌状态：
             1'b0：通道已排空，处于空闲态
             1'b1：通道处于忙碌状态
   UNION结构:  BBPCOMM_BBPMST_CH_BUSY_UNION */
#define BBPCOMM_BBPMST_CH_BUSY_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC098)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch0_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC100)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC104)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH0_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC108)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（系统位）配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（系统位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC10C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC110)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC114)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC118)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch1_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC120)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC124)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH1_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC128)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（第一校验位）配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（第一校验位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC12C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC130)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC134)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道1每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC138)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch2_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC140)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC144)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH2_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC148)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码harq外移（第二校验位）配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模译码harq外移（第二校验位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC14C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC150)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC154)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道2每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC158)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch3_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC160)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC164)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH3_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC168)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模SDR_TX配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模SDR_TX配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC16C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC170)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC174)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道3每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC178)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch5_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH5_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH5_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC200)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH5_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC204)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH5_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC208)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH5_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC20C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模RX1_dump配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模RX1_dump配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC210)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC214)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC218)

/* 寄存器说明：
 bit[31:16]  分别对应bbpmst读通道0-15时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
 bit[15:0]   分别对应bbpmst写通道0-15时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
   UNION结构:  BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION */
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC224)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10]     axi口0的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[9]      axi口0读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[8]      axi口0写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[7:0]    保留
   UNION结构:  BBPCOMM_BBPMST_AXI0_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI0_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC300)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10]     axi口1的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[9]      axi口1读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[8]      axi口1写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
             1’b0：空闲，总线已被释放掉
             1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电
             
 bit[7:0]    保留
             
   UNION结构:  BBPCOMM_BBPMST_AXI1_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI1_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC304)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型0
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC308)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型1
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC30C)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型2
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC310)

/* 寄存器说明：
 bit[31:4]   保留
 bit[3:0]    当bbpmst写error发生时，临近的burst的类型3
   UNION结构:  BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC314)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址0
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR0_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC318)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址1
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR1_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC31C)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址2
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR2_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC320)

/* 寄存器说明：
   详      述：当bbpmst写error发生时，临近的burst的基地址3
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR3_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC324)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      bbpmst读写错误中断清除寄存器。当BBPMST读写发生错误时，bbpmst_error_int会直接拉成电平送给BBE16\CCPU，软件收到中断后配置该寄存器清除中断电平。
   UNION结构:  BBPCOMM_BBPMST_ERROR_INT_CLR_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC328)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL0_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL0_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC32C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  BBPCOMM_MEM_CTRL1_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL1_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC330)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST写通道写请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC334)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST读通道读请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC338)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST写通道写请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC33C)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST读通道读请求的响应个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC340)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口0当前写响应ID
 bit[7:5]    保留
 bit[4]      AXI口0当前写响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口0当前写响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_WR0_STATE_UNION */
#define BBPCOMM_AXI_WR0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC344)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口0当前读响应ID
 bit[7:5]    保留
 bit[4]      AXI口0当前读响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口0当前读响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_RD0_STATE_UNION */
#define BBPCOMM_AXI_RD0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC348)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口1当前写响应ID
 bit[7:5]    保留
 bit[4]      AXI口1当前写响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口1当前写响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_WR1_STATE_UNION */
#define BBPCOMM_AXI_WR1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC34C)

/* 寄存器说明：
 bit[31:11]  保留
 bit[10:8]   AXI口1当前读响应ID
 bit[7:5]    保留
 bit[4]      AXI口1当前读响应数据有效指示
 bit[3:1]    保留
 bit[0]      AXI口1当前读响应可接收数据指示
   UNION结构:  BBPCOMM_AXI_RD1_STATE_UNION */
#define BBPCOMM_AXI_RD1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC350)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST写通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC354)

/* 寄存器说明：
   详      述：AXI口0对所有BBPMST读通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC358)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST写通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_WR1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC35C)

/* 寄存器说明：
   详      述：AXI口1对所有BBPMST读通道数据传输个数统计
   UNION结构 ：无 */
#define BBPCOMM_AXI_RD1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC360)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写错误中断使能
   UNION结构:  BBPCOMM_BBPMST_ERROR_INT_EN_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_EN_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC364)

/* 寄存器说明：
 bit[31:10]  
 bit[9]      所有可维可测功能的使能信号，为1时打开所有可维可测寄存器，为0时对所有可维可测寄存器进行清零
 bit[8]      用于可维可测，产生脉冲信号用于内部计数器计数，测试时钟和复位信号
 bit[7:4]    
 bit[3:0]    用于可维可测功能，对bbpmst_maintain_pulse进行计数
   UNION结构:  BBPCOMM_BBPMST_MAINTAIN_CFG_UNION */
#define BBPCOMM_BBPMST_MAINTAIN_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC368)

/* 寄存器说明：
 bit[31:24]  
 bit[23:16]  对中断2产生个数进行计数，用于可维可测
 bit[15:8]   对中断1产生个数进行计数，用于可维可测
 bit[7:0]    对中断0产生个数进行计数，用于可维可测
   UNION结构:  BBPCOMM_BBPMST_INT_CNT_UNION */
#define BBPCOMM_BBPMST_INT_CNT_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC36C)

/* 寄存器说明：
   详      述：中断0的屏蔽位：
               [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理写通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC370)

/* 寄存器说明：
   详      述：中断0的清中断位：
               [15:0]：分别对应各个物理写通道中断的清中断，脉冲有效。
               [31:16]：分别对应各个物理读通道中断的清中断，脉冲有效。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC374)

/* 寄存器说明：
   详      述：中断0的中断标志，为经过屏蔽后的结果：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC378)

/* 寄存器说明：
   详      述：中断0的中断标志，为屏蔽前的原始中断标志：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC37C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写通道中断0使能
   UNION结构:  BBPCOMM_BBPMST_INT0_EN_UNION */
#define BBPCOMM_BBPMST_INT0_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC380)

/* 寄存器说明：
   详      述：中断1的屏蔽位：
               [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理写通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC384)

/* 寄存器说明：
   详      述：中断1的清中断位：
               [15:0]：分别对应各个物理写通道中断的清中断，脉冲有效。
               [31:16]：分别对应各个物理读通道中断的清中断，脉冲有效。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC388)

/* 寄存器说明：
   详      述：中断1的中断标志，为经过屏蔽后的结果：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC38C)

/* 寄存器说明：
   详      述：中断1的中断标志，为屏蔽前的原始中断标志：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC390)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写通道中断1使能
   UNION结构:  BBPCOMM_BBPMST_INT1_EN_UNION */
#define BBPCOMM_BBPMST_INT1_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC394)

/* 寄存器说明：
   详      述：中断2的屏蔽位：
               [15:0]：分别为各个物理写通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理写通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC398)

/* 寄存器说明：
   详      述：中断2的清中断位：
               [15:0]：分别对应各个物理写通道中断的清中断，脉冲有效。
               [31:16]：分别对应各个物理读通道中断的清中断，脉冲有效。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC39C)

/* 寄存器说明：
   详      述：中断2的中断标志，为经过屏蔽后的结果：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC3A0)

/* 寄存器说明：
   详      述：中断2的中断标志，为屏蔽前的原始中断标志：
               [15:0]：分别对应各个物理写通道中断的中断标志。
               [31:16]：分别对应各个物理读通道中断的中断标志。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3A4)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      BBPMST读写通道中断2使能
   UNION结构:  BBPCOMM_BBPMST_INT2_EN_UNION */
#define BBPCOMM_BBPMST_INT2_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC3A8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch6_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH6_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH6_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3B0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH6_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3B4)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH6_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3B8)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH6_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3BC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模RX2_dump配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   U模RX2_dump配置内部写通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC3C0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3C4)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3C8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch7_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH7_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH7_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3D0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH7_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3D4)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH7_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3D8)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH7_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3DC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模副卡译码harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模副卡译码harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x20
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC3E0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3E4)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3E8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch8_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH8_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH8_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3F0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH8_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3F4)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH8_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3F8)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH8_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3FC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模SDR_RX1配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模SDR_RX1配置内部写通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC400)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC404)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC408)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch9_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH9_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH9_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC410)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH9_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC414)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH9_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC418)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH9_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC41C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模SDR_RX2配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模SDR_RX2配置内部写通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC420)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC424)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC428)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch10_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH10_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH10_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC430)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH10_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC434)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH10_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC438)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH10_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC43C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模译码harq外移/1x_VTB回读配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模译码harq外移/1x_VTB回读配置内部写通道使用的异步fifo偏移地址，默认值为0x20
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC440)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC444)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC448)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch11_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH11_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH11_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC450)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH11_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC454)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH11_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC458)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH11_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC45C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G1模harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   G1模harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC460)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC464)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC468)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch12_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH12_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH12_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC470)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH12_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC474)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH12_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC478)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH12_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC47C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G1模dump配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   G1模dump配置内部写通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC480)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC484)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC488)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch13_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH13_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH13_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC490)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH13_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC494)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH13_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC498)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH13_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC49C)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G2模harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   G2模harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    保留
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
   UNION结构:  BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC4A0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC4A4)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4A8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      该写物理通道的使能：
             1’b0：关闭
             1’b1：使能
 bit[8]      1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch4_base_addr”指向的地址
             1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4B0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4B4)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的基地址（以Byte为单位）
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH4_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4B8)

/* 寄存器说明：
   详      述：写通道支持循环空间写，本寄存器为该通道在DDR中对应的循环地址空间的结束地址（以Byte为单位）；软件确保基地址和结束地址之间的该空间必须是8byte的整数倍，当数据达到结束地址时master将自动绕回到基地址并写入新的数据
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_WR_CH4_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC4BC)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  U模译码上报外移（head部分）配置内部写通道使用的异步fifo深度，默认值为0x07
 bit[15:8]   U模译码上报外移（head部分）配置内部写通道使用的异步fifo偏移地址，默认值为0x38
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4C0)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个写通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4C4)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该写物理通道产生中断的方式：取值范围0~3
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             两种中断可以都使能。
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4C8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch4_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4D0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4D4)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH4_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4D8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模待译码数据下发配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模待译码数据下发配置内部读通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4DC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4E0)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4E4)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC4E8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch5_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH5_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH5_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4F0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH5_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4F4)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH5_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4F8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x20
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4FC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC500)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC504)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC508)

/* 寄存器说明：
   详      述：中断0的屏蔽位：
               [15:0]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理读通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC514)

/* 寄存器说明：
   详      述：中断0的屏蔽位：
               [0]：对应GUC_MST AXI0错误中断，1表示屏蔽。
               [1]：对应GUC_MST AXI1错误中断，1表示屏蔽。
               [16]：对应GUC_MST AXI0错误中断屏蔽位的写使能。
               [17]：对应GUC_MST AXI1错误中断屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT0_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC518)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断0的清中断位：
             [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。
   UNION结构:  BBPCOMM_BBPMST_INT0_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT0_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC51C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断0的中断标志，为经过屏蔽后的结果：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT0_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT0_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC520)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断0的中断标志，为屏蔽前的原始中断标志：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC524)

/* 寄存器说明：
   详      述：中断1的屏蔽位：
               [15:0]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理读通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC528)

/* 寄存器说明：
   详      述：中断1的屏蔽位：
               [0]：对应GUC_MST AXI0错误中断，1表示屏蔽。
               [1]：对应GUC_MST AXI1错误中断，1表示屏蔽。
               [16]：对应GUC_MST AXI0错误中断屏蔽位的写使能。
               [17]：对应GUC_MST AXI1错误中断屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT1_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC52C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断1的清中断位：
             [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。
   UNION结构:  BBPCOMM_BBPMST_INT1_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT1_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC530)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断1的中断标志，为经过屏蔽后的结果：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT1_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT1_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC534)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断1的中断标志，为屏蔽前的原始中断标志：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC538)

/* 寄存器说明：
   详      述：中断2的屏蔽位：
               [15:0]：分别为各个物理读通道对应中断的屏蔽位，1表示屏蔽。
               [31:16]：分别为各个物理读通道屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC53C)

/* 寄存器说明：
   详      述：中断2的屏蔽位：
               [0]：对应GUC_MST AXI0错误中断，1表示屏蔽。
               [1]：对应GUC_MST AXI1错误中断，1表示屏蔽。
               [16]：对应GUC_MST AXI0错误中断屏蔽位的写使能。
               [17]：对应GUC_MST AXI1错误中断屏蔽位的写使能。
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_INT2_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC540)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断2的清中断位：
             [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。
   UNION结构:  BBPCOMM_BBPMST_INT2_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT2_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC544)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断2的中断标志，为经过屏蔽后的结果：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT2_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT2_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC548)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    中断2的中断标志，为屏蔽前的原始中断标志：
             [1:0]：分别对应AXI0/1通道中断的中断标志。
   UNION结构:  BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC54C)

/* 寄存器说明：
 bit[31:5]   保留
 bit[4]      bbpmst sram if时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
 bit[3]      bbpmst AXI1口读通道时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
 bit[2]      bbpmst AXI1口写通道时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
 bit[1]      bbpmst AXI0口读通道时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
 bit[0]      bbpmst AXI0口写通道时钟门控旁路单元：
             1：旁路时钟门控；
             0：打开时钟门控；
   UNION结构:  BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION */
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC550)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch6_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH6_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH6_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC560)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH6_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC564)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH6_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC568)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模SDR_TX配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模SDR_TX配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC56C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC570)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC574)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC578)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch7_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH7_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH7_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC580)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH7_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC584)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH7_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC588)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模待译码数据下发配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模待译码数据下发配置内部读通道使用的异步fifo偏移地址，默认值为0x10
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC58C)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC590)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC594)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC598)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch8_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH8_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH8_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC5A0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH8_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5A4)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH8_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5A8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  C模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   C模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x20
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5AC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5B0)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5B4)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC5B8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch9_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH9_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH9_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC5C0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH9_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5C4)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH9_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5C8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G1模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   G1模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5CC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5D0)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5D4)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC5D8)

/* 寄存器说明：
 bit[31:10]  保留
 bit[9]      读通道使能信号：
             1'b0:关闭；
             1'b1:打开；
 bit[8]      1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch10_base_addr”指向的地址
             1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供
 bit[7]      1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
             1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP；
 bit[6:0]    保留
   UNION结构:  BBPCOMM_BBPMST_RD_CH10_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH10_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC5E0)

/* 寄存器说明：
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH10_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC5E4)

/* 寄存器说明：
   详      述：该读通道在DDR中对应的地址空间的基地址（以Byte为单位），读通道不支持循环读，无需配置空间结束地址，由于读取数据的长度也由软件决定，故软件需确保读通道对应的地址空间不被其他软件进程误操作
   UNION结构 ：无 */
#define BBPCOMM_BBPMST_RD_CH10_INIT_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5E8)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  G2模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f
 bit[15:8]   G2模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x00
 bit[7:4]    
 bit[3:0]    用Master方式完成DPA上报时，单个burst的类型，含义如下：
             burst_beat==0， burst1
             burst_beat==3， burst4
             burst_beat==7， burst8
             burst_beat==15，burst16
             如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8 
             
   UNION结构:  BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC5EC)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    各个读通道所选择使用的master（ram）口选择：
             2'b00：该通道使用master口1
             2'b01：该通道使用master口2
             2'b10：该通道使用ram口1
             如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口
   UNION结构:  BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC5F0)

/* 寄存器说明：
 bit[31:18]  保留
 bit[17:16]  该读物理通道产生中断的方式：
             [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
             [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
             
 bit[15:0]   当多次中断使能有效时，N的取值
   UNION结构:  BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5F4)

/* 寄存器说明：
 bit[31:2]   保留
 bit[1:0]    读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据；
   UNION结构:  BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xC5F8)





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
                     (1/1) register_define_guc_bbpmst
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_MODE_UNION
 结构说明  : BBPMST_WR_CH0_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch0_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch0_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch0_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch0_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH0_BURST_BEAT 寄存器结构定义。地址偏移量:0x0010，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch0_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（系统位）配置内部写通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_wr_ch0_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（系统位）配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH0_AXI_SEL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH0_INTR_MODE 寄存器结构定义。地址偏移量:0x0018，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch0_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_MODE_UNION
 结构说明  : BBPMST_WR_CH1_MODE 寄存器结构定义。地址偏移量:0x0020，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch1_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch1_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch1_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch1_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH1_BURST_BEAT 寄存器结构定义。地址偏移量:0x0030，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch1_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（第一校验位）配置内部写通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_wr_ch1_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（第一校验位）配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH1_AXI_SEL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH1_INTR_MODE 寄存器结构定义。地址偏移量:0x0038，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch1_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_MODE_UNION
 结构说明  : BBPMST_WR_CH2_MODE 寄存器结构定义。地址偏移量:0x0040，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch2_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch2_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch2_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch2_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH2_BURST_BEAT 寄存器结构定义。地址偏移量:0x0050，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch2_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（第二校验位）配置内部写通道使用的异步fifo偏移地址，默认值为0x20 */
        unsigned int  bbpmst_wr_ch2_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（第二校验位）配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH2_AXI_SEL 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH2_INTR_MODE 寄存器结构定义。地址偏移量:0x0058，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch2_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_MODE_UNION
 结构说明  : BBPMST_WR_CH3_MODE 寄存器结构定义。地址偏移量:0x0060，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch3_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch3_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch3_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch3_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH3_BURST_BEAT 寄存器结构定义。地址偏移量:0x0070，初值:0x00073002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch3_fifo_baddr : 8;  /* bit[8-15] : U模译码上报外移（data部分）配置内部写通道使用的异步fifo偏移地址，默认值为0x30 */
        unsigned int  bbpmst_wr_ch3_fifo_depth : 8;  /* bit[16-23]: U模译码上报外移（data部分）配置内部写通道使用的异步fifo深度，默认值为0x07 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH3_AXI_SEL 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH3_INTR_MODE 寄存器结构定义。地址偏移量:0x0078，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch3_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_CH_BUSY_UNION
 结构说明  : BBPMST_CH_BUSY 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_ch_busy_reg;
    struct
    {
        unsigned int  wr_ch_busy : 16; /* bit[0-15] : 写通道的空闲/忙碌状态：
                                                      1'b0：通道已排空，处于空闲态
                                                      1'b1：通道处于忙碌状态 */
        unsigned int  rd_ch_busy : 16; /* bit[16-31]: 读通道的空闲/忙碌状态：
                                                      1'b0：通道已排空，处于空闲态
                                                      1'b1：通道处于忙碌状态 */
    } reg;
} BBPCOMM_BBPMST_CH_BUSY_UNION;
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch_busy_START  (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch_busy_END    (15)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch_busy_START  (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch_busy_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_MODE_UNION
 结构说明  : BBPMST_RD_CH0_MODE 寄存器结构定义。地址偏移量:0x0100，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch0_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch0_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch0_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch0_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH0_BURST_BEAT 寄存器结构定义。地址偏移量:0x010C，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch0_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（系统位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch0_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（系统位）配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH0_AXI_SEL 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH0_INTR_MODE 寄存器结构定义。地址偏移量:0x0114，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch0_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH0_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0118，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_MODE_UNION
 结构说明  : BBPMST_RD_CH1_MODE 寄存器结构定义。地址偏移量:0x0120，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch1_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch1_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch1_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch1_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH1_BURST_BEAT 寄存器结构定义。地址偏移量:0x012C，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch1_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（第一校验位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch1_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（第一校验位）配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH1_AXI_SEL 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH1_INTR_MODE 寄存器结构定义。地址偏移量:0x0134，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch1_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH1_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0138，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_bit_width_ind : 2;  /* bit[0-1] : 读通道1每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_MODE_UNION
 结构说明  : BBPMST_RD_CH2_MODE 寄存器结构定义。地址偏移量:0x0140，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch2_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch2_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch2_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch2_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH2_BURST_BEAT 寄存器结构定义。地址偏移量:0x014C，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch2_fifo_baddr : 8;  /* bit[8-15] : U模译码harq外移（第二校验位）配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch2_fifo_depth : 8;  /* bit[16-23]: U模译码harq外移（第二校验位）配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH2_AXI_SEL 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH2_INTR_MODE 寄存器结构定义。地址偏移量:0x0154，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch2_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH2_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0158，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_bit_width_ind : 2;  /* bit[0-1] : 读通道2每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_MODE_UNION
 结构说明  : BBPMST_RD_CH3_MODE 寄存器结构定义。地址偏移量:0x0160，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch3_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch3_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch3_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch3_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH3_BURST_BEAT 寄存器结构定义。地址偏移量:0x016C，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch3_fifo_baddr : 8;  /* bit[8-15] : C模SDR_TX配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch3_fifo_depth : 8;  /* bit[16-23]: C模SDR_TX配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH3_AXI_SEL 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH3_INTR_MODE 寄存器结构定义。地址偏移量:0x0174，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch3_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH3_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0178，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_bit_width_ind : 2;  /* bit[0-1] : 读通道3每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH5_MODE_UNION
 结构说明  : BBPMST_WR_CH5_MODE 寄存器结构定义。地址偏移量:0x0200，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch5_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch5_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch5_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch5_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH5_BURST_BEAT 寄存器结构定义。地址偏移量:0x0210，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch5_fifo_baddr : 8;  /* bit[8-15] : U模RX1_dump配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_wr_ch5_fifo_depth : 8;  /* bit[16-23]: U模RX1_dump配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH5_AXI_SEL 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_bbpmst_wr_ch5_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_bbpmst_wr_ch5_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH5_INTR_MODE 寄存器结构定义。地址偏移量:0x0218，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch5_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION
 结构说明  : BBPMST_CH_CLK_BYPASS 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_ch_clk_bypass_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch_ckg_bypass : 16; /* bit[0-15] : 分别对应bbpmst写通道0-15时钟门控旁路单元：
                                                                   1：旁路时钟门控；
                                                                   0：打开时钟门控； */
        unsigned int  bbpmst_rd_ch_ckg_bypass : 16; /* bit[16-31]: 分别对应bbpmst读通道0-15时钟门控旁路单元：
                                                                   1：旁路时钟门控；
                                                                   0：打开时钟门控； */
    } reg;
} BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION;
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_wr_ch_ckg_bypass_START  (0)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_wr_ch_ckg_bypass_END    (15)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_rd_ch_ckg_bypass_START  (16)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_rd_ch_ckg_bypass_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_AXI0_STATUS_UNION
 结构说明  : BBPMST_AXI0_STATUS 寄存器结构定义。地址偏移量:0x0300，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi0_status_reg;
    struct
    {
        unsigned int  reserved_0            : 8;  /* bit[0-7]  : 保留 */
        unsigned int  bbpmst_axi0_wr_status : 1;  /* bit[8]    : axi口0写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  bbpmst_axi0_rd_status : 1;  /* bit[9]    : axi口0读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  bbpmst_axi0_status    : 1;  /* bit[10]   : axi口0的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  reserved_1            : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_AXI0_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_START  (8)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_END    (8)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_START  (9)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_END    (9)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_START     (10)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_END       (10)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_AXI1_STATUS_UNION
 结构说明  : BBPMST_AXI1_STATUS 寄存器结构定义。地址偏移量:0x0304，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi1_status_reg;
    struct
    {
        unsigned int  reserved_0            : 8;  /* bit[0-7]  : 保留 */
        unsigned int  bbpmst_axi1_wr_status : 1;  /* bit[8]    : axi口1写通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  bbpmst_axi1_rd_status : 1;  /* bit[9]    : axi口1读通道的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  bbpmst_axi1_status    : 1;  /* bit[10]   : axi口1的空闲状态标志： 软件可根据各个axi口的空闲状态决定是否能发起掉电或其他低功耗流程
                                                                 1’b0：空闲，总线已被释放掉
                                                                 1’b1：非空闲，总线未释放，此状态下master不可以复位/关时钟/掉电 */
        unsigned int  reserved_1            : 21; /* bit[11-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_AXI1_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_START  (8)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_END    (8)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_START  (9)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_END    (9)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_START     (10)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_END       (10)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION
 结构说明  : BBPMST_ERROR_BURST_BEAT0 寄存器结构定义。地址偏移量:0x0308，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_burst_beat0_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat0 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型0 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
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
    unsigned int      bbpmst_error_burst_beat1_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat1 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型1 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
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
    unsigned int      bbpmst_error_burst_beat2_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat2 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型2 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
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
    unsigned int      bbpmst_error_burst_beat3_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat3 : 4;  /* bit[0-3] : 当bbpmst写error发生时，临近的burst的类型3 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
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
    unsigned int      bbpmst_error_int_clr_reg;
    struct
    {
        unsigned int  bbpmst_error_int_clr : 1;  /* bit[0]   : bbpmst读写错误中断清除寄存器。当BBPMST读写发生错误时，bbpmst_error_int会直接拉成电平送给BBE16\CCPU，软件收到中断后配置该寄存器清除中断电平。 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
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
    unsigned int      mem_ctrl0_bbpmst_reg;
    struct
    {
        unsigned int  mem_ctrl_s_bbpmst      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned int  mem_ctrl_d_1w2r_bbpmst : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
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
    unsigned int      mem_ctrl1_bbpmst_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_bbpmst : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned int  rom_ctrl_bbpmst          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned int  reserved                 : 8;  /* bit[24-31]: 保留 */
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
    unsigned int      axi_wr0_state_reg;
    struct
    {
        unsigned int  axi_wr0_ready  : 1;  /* bit[0]    : AXI口0当前写响应可接收数据指示 */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned int  axi_wr0_valid  : 1;  /* bit[4]    : AXI口0当前写响应数据有效指示 */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned int  axi_wr0_cur_id : 3;  /* bit[8-10] : AXI口0当前写响应ID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: 保留 */
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
    unsigned int      axi_rd0_state_reg;
    struct
    {
        unsigned int  axi_rd0_ready  : 1;  /* bit[0]    : AXI口0当前读响应可接收数据指示 */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned int  axi_rd0_valid  : 1;  /* bit[4]    : AXI口0当前读响应数据有效指示 */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned int  axi_rd0_cur_id : 3;  /* bit[8-10] : AXI口0当前读响应ID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: 保留 */
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
    unsigned int      axi_wr1_state_reg;
    struct
    {
        unsigned int  axi_wr1_ready  : 1;  /* bit[0]    : AXI口1当前写响应可接收数据指示 */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned int  axi_wr1_valid  : 1;  /* bit[4]    : AXI口1当前写响应数据有效指示 */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned int  axi_wr1_cur_id : 3;  /* bit[8-10] : AXI口1当前写响应ID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: 保留 */
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
    unsigned int      axi_rd1_state_reg;
    struct
    {
        unsigned int  axi_rd1_ready  : 1;  /* bit[0]    : AXI口1当前读响应可接收数据指示 */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : 保留 */
        unsigned int  axi_rd1_valid  : 1;  /* bit[4]    : AXI口1当前读响应数据有效指示 */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : 保留 */
        unsigned int  axi_rd1_cur_id : 3;  /* bit[8-10] : AXI口1当前读响应ID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: 保留 */
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
    unsigned int      bbpmst_error_int_en_reg;
    struct
    {
        unsigned int  bbpmst_error_int_en : 1;  /* bit[0]   : BBPMST读写错误中断使能 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_EN_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_MAINTAIN_CFG_UNION
 结构说明  : BBPMST_MAINTAIN_CFG 寄存器结构定义。地址偏移量:0x0368，初值:0x00000200，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_maintain_cfg_reg;
    struct
    {
        unsigned int  bbpmst_maintain_cnt   : 4;  /* bit[0-3]  : 用于可维可测功能，对bbpmst_maintain_pulse进行计数 */
        unsigned int  reserved_0            : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_maintain_pulse : 1;  /* bit[8]    : 用于可维可测，产生脉冲信号用于内部计数器计数，测试时钟和复位信号 */
        unsigned int  bbpmst_maintain_en    : 1;  /* bit[9]    : 所有可维可测功能的使能信号，为1时打开所有可维可测寄存器，为0时对所有可维可测寄存器进行清零 */
        unsigned int  reserved_1            : 22; /* bit[10-31]:  */
    } reg;
} BBPCOMM_BBPMST_MAINTAIN_CFG_UNION;
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_cnt_START    (0)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_cnt_END      (3)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_pulse_START  (8)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_pulse_END    (8)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_en_START     (9)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_en_END       (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT_CNT_UNION
 结构说明  : BBPMST_INT_CNT 寄存器结构定义。地址偏移量:0x036C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int_cnt_reg;
    struct
    {
        unsigned int  bbpmst_int0_cnt : 8;  /* bit[0-7]  : 对中断0产生个数进行计数，用于可维可测 */
        unsigned int  bbpmst_int1_cnt : 8;  /* bit[8-15] : 对中断1产生个数进行计数，用于可维可测 */
        unsigned int  bbpmst_int2_cnt : 8;  /* bit[16-23]: 对中断2产生个数进行计数，用于可维可测 */
        unsigned int  reserved        : 8;  /* bit[24-31]:  */
    } reg;
} BBPCOMM_BBPMST_INT_CNT_UNION;
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int0_cnt_START  (0)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int0_cnt_END    (7)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int1_cnt_START  (8)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int1_cnt_END    (15)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int2_cnt_START  (16)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int2_cnt_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT0_EN_UNION
 结构说明  : BBPMST_INT0_EN 寄存器结构定义。地址偏移量:0x0380，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_en_reg;
    struct
    {
        unsigned int  bbpmst_int0_en : 1;  /* bit[0]   : BBPMST读写通道中断0使能 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT0_EN_UNION;
#define BBPCOMM_BBPMST_INT0_EN_bbpmst_int0_en_START  (0)
#define BBPCOMM_BBPMST_INT0_EN_bbpmst_int0_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT1_EN_UNION
 结构说明  : BBPMST_INT1_EN 寄存器结构定义。地址偏移量:0x0394，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_en_reg;
    struct
    {
        unsigned int  bbpmst_int1_en : 1;  /* bit[0]   : BBPMST读写通道中断1使能 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT1_EN_UNION;
#define BBPCOMM_BBPMST_INT1_EN_bbpmst_int1_en_START  (0)
#define BBPCOMM_BBPMST_INT1_EN_bbpmst_int1_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT2_EN_UNION
 结构说明  : BBPMST_INT2_EN 寄存器结构定义。地址偏移量:0x03A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_en_reg;
    struct
    {
        unsigned int  bbpmst_int2_en : 1;  /* bit[0]   : BBPMST读写通道中断2使能 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT2_EN_UNION;
#define BBPCOMM_BBPMST_INT2_EN_bbpmst_int2_en_START  (0)
#define BBPCOMM_BBPMST_INT2_EN_bbpmst_int2_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH6_MODE_UNION
 结构说明  : BBPMST_WR_CH6_MODE 寄存器结构定义。地址偏移量:0x03B0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch6_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch6_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch6_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch6_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH6_BURST_BEAT 寄存器结构定义。地址偏移量:0x03C0，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch6_fifo_baddr : 8;  /* bit[8-15] : U模RX2_dump配置内部写通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_wr_ch6_fifo_depth : 8;  /* bit[16-23]: U模RX2_dump配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH6_AXI_SEL 寄存器结构定义。地址偏移量:0x03C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_bbpmst_wr_ch6_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_bbpmst_wr_ch6_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH6_INTR_MODE 寄存器结构定义。地址偏移量:0x03C8，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch6_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH7_MODE_UNION
 结构说明  : BBPMST_WR_CH7_MODE 寄存器结构定义。地址偏移量:0x03D0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch7_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch7_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch7_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch7_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH7_BURST_BEAT 寄存器结构定义。地址偏移量:0x03E0，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch7_fifo_baddr : 8;  /* bit[8-15] : C模副卡译码harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x20 */
        unsigned int  bbpmst_wr_ch7_fifo_depth : 8;  /* bit[16-23]: C模副卡译码harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH7_AXI_SEL 寄存器结构定义。地址偏移量:0x03E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_bbpmst_wr_ch7_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_bbpmst_wr_ch7_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH7_INTR_MODE 寄存器结构定义。地址偏移量:0x03E8，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch7_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH8_MODE_UNION
 结构说明  : BBPMST_WR_CH8_MODE 寄存器结构定义。地址偏移量:0x03F0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch8_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch8_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch8_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch8_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH8_BURST_BEAT 寄存器结构定义。地址偏移量:0x0400，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch8_fifo_baddr : 8;  /* bit[8-15] : C模SDR_RX1配置内部写通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_wr_ch8_fifo_depth : 8;  /* bit[16-23]: C模SDR_RX1配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH8_AXI_SEL 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_bbpmst_wr_ch8_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_bbpmst_wr_ch8_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH8_INTR_MODE 寄存器结构定义。地址偏移量:0x0408，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch8_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH9_MODE_UNION
 结构说明  : BBPMST_WR_CH9_MODE 寄存器结构定义。地址偏移量:0x0410，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch9_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch9_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch9_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch9_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH9_BURST_BEAT 寄存器结构定义。地址偏移量:0x0420，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch9_fifo_baddr : 8;  /* bit[8-15] : C模SDR_RX2配置内部写通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_wr_ch9_fifo_depth : 8;  /* bit[16-23]: C模SDR_RX2配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH9_AXI_SEL 寄存器结构定义。地址偏移量:0x0424，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_bbpmst_wr_ch9_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_bbpmst_wr_ch9_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH9_INTR_MODE 寄存器结构定义。地址偏移量:0x0428，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch9_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH10_MODE_UNION
 结构说明  : BBPMST_WR_CH10_MODE 寄存器结构定义。地址偏移量:0x0430，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch10_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                        1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch10_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch10_base_addr”指向的地址
                                                                        1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch10_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                        1’b0：关闭
                                                                        1’b1：使能 */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH10_BURST_BEAT 寄存器结构定义。地址偏移量:0x0440，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                     burst_beat==0， burst1
                                                                     burst_beat==3， burst4
                                                                     burst_beat==7， burst8
                                                                     burst_beat==15，burst16
                                                                     如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch10_fifo_baddr : 8;  /* bit[8-15] : C模译码harq外移/1x_VTB回读配置内部写通道使用的异步fifo偏移地址，默认值为0x20 */
        unsigned int  bbpmst_wr_ch10_fifo_depth : 8;  /* bit[16-23]: C模译码harq外移/1x_VTB回读配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH10_AXI_SEL 寄存器结构定义。地址偏移量:0x0444，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                 2'b00：该通道使用master口1
                                                                 2'b01：该通道使用master口2
                                                                 2'b10：该通道使用ram口1
                                                                 如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_bbpmst_wr_ch10_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_bbpmst_wr_ch10_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH10_INTR_MODE 寄存器结构定义。地址偏移量:0x0448，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch10_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                     [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                     [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                     两种中断可以都使能。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH11_MODE_UNION
 结构说明  : BBPMST_WR_CH11_MODE 寄存器结构定义。地址偏移量:0x0450，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch11_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                        1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch11_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch11_base_addr”指向的地址
                                                                        1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch11_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                        1’b0：关闭
                                                                        1’b1：使能 */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH11_BURST_BEAT 寄存器结构定义。地址偏移量:0x0460，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                     burst_beat==0， burst1
                                                                     burst_beat==3， burst4
                                                                     burst_beat==7， burst8
                                                                     burst_beat==15，burst16
                                                                     如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch11_fifo_baddr : 8;  /* bit[8-15] : G1模harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_wr_ch11_fifo_depth : 8;  /* bit[16-23]: G1模harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH11_AXI_SEL 寄存器结构定义。地址偏移量:0x0464，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                 2'b00：该通道使用master口1
                                                                 2'b01：该通道使用master口2
                                                                 2'b10：该通道使用ram口1
                                                                 如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_bbpmst_wr_ch11_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_bbpmst_wr_ch11_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH11_INTR_MODE 寄存器结构定义。地址偏移量:0x0468，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch11_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                     [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                     [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                     两种中断可以都使能。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH12_MODE_UNION
 结构说明  : BBPMST_WR_CH12_MODE 寄存器结构定义。地址偏移量:0x0470，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch12_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                        1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch12_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch12_base_addr”指向的地址
                                                                        1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch12_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                        1’b0：关闭
                                                                        1’b1：使能 */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH12_BURST_BEAT 寄存器结构定义。地址偏移量:0x0480，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                     burst_beat==0， burst1
                                                                     burst_beat==3， burst4
                                                                     burst_beat==7， burst8
                                                                     burst_beat==15，burst16
                                                                     如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch12_fifo_baddr : 8;  /* bit[8-15] : G1模dump配置内部写通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_wr_ch12_fifo_depth : 8;  /* bit[16-23]: G1模dump配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH12_AXI_SEL 寄存器结构定义。地址偏移量:0x0484，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                 2'b00：该通道使用master口1
                                                                 2'b01：该通道使用master口2
                                                                 2'b10：该通道使用ram口1
                                                                 如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_bbpmst_wr_ch12_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_bbpmst_wr_ch12_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH12_INTR_MODE 寄存器结构定义。地址偏移量:0x0488，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch12_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                     [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                     [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                     两种中断可以都使能。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH13_MODE_UNION
 结构说明  : BBPMST_WR_CH13_MODE 寄存器结构定义。地址偏移量:0x0490，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch13_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                        1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch13_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch13_base_addr”指向的地址
                                                                        1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch13_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                        1’b0：关闭
                                                                        1’b1：使能 */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH13_BURST_BEAT 寄存器结构定义。地址偏移量:0x04A0，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                     burst_beat==0， burst1
                                                                     burst_beat==3， burst4
                                                                     burst_beat==7， burst8
                                                                     burst_beat==15，burst16
                                                                     如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : 保留 */
        unsigned int  bbpmst_wr_ch13_fifo_baddr : 8;  /* bit[8-15] : G2模harq外移配置内部写通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_wr_ch13_fifo_depth : 8;  /* bit[16-23]: G2模harq外移配置内部写通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH13_AXI_SEL 寄存器结构定义。地址偏移量:0x04A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                 2'b00：该通道使用master口1
                                                                 2'b01：该通道使用master口2
                                                                 2'b10：该通道使用ram口1
                                                                 如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_bbpmst_wr_ch13_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_bbpmst_wr_ch13_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH13_INTR_MODE 寄存器结构定义。地址偏移量:0x04A8，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch13_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                     [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                     [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                     两种中断可以都使能。 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_MODE_UNION
 结构说明  : BBPMST_WR_CH4_MODE 寄存器结构定义。地址偏移量:0x04B0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_wr_ch4_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_wr_ch4_addr_mode     : 1;  /* bit[8]    : 1’b0：该写物理通道每次搬数的起始地址为“bbpmst_wr_ch4_base_addr”指向的地址
                                                                       1’b1：该写物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_wr_ch4_en            : 1;  /* bit[9]    : 该写物理通道的使能：
                                                                       1’b0：关闭
                                                                       1’b1：使能 */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION
 结构说明  : BBPMST_WR_CH4_BURST_BEAT 寄存器结构定义。地址偏移量:0x04C0，初值:0x00073802，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch4_fifo_baddr : 8;  /* bit[8-15] : U模译码上报外移（head部分）配置内部写通道使用的异步fifo偏移地址，默认值为0x38 */
        unsigned int  bbpmst_wr_ch4_fifo_depth : 8;  /* bit[16-23]: U模译码上报外移（head部分）配置内部写通道使用的异步fifo深度，默认值为0x07 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION
 结构说明  : BBPMST_WR_CH4_AXI_SEL 寄存器结构定义。地址偏移量:0x04C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_axi_sel : 2;  /* bit[0-1] : 各个写通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION
 结构说明  : BBPMST_WR_CH4_INTR_MODE 寄存器结构定义。地址偏移量:0x04C8，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_wr_ch4_intr_mode  : 2;  /* bit[16-17]: 该写物理通道产生中断的方式：取值范围0~3
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能
                                                                    两种中断可以都使能。 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH4_MODE_UNION
 结构说明  : BBPMST_RD_CH4_MODE 寄存器结构定义。地址偏移量:0x04D0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch4_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch4_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch4_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch4_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH4_BURST_BEAT 寄存器结构定义。地址偏移量:0x04DC，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch4_fifo_baddr : 8;  /* bit[8-15] : C模待译码数据下发配置内部读通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_rd_ch4_fifo_depth : 8;  /* bit[16-23]: C模待译码数据下发配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH4_AXI_SEL 寄存器结构定义。地址偏移量:0x04E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_bbpmst_rd_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_bbpmst_rd_ch4_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH4_INTR_MODE 寄存器结构定义。地址偏移量:0x04E4，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch4_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH4_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x04E8，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_bbpmst_rd_ch4_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_bbpmst_rd_ch4_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH5_MODE_UNION
 结构说明  : BBPMST_RD_CH5_MODE 寄存器结构定义。地址偏移量:0x04F0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch5_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch5_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch5_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch5_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH5_BURST_BEAT 寄存器结构定义。地址偏移量:0x04FC，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch5_fifo_baddr : 8;  /* bit[8-15] : C模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x20 */
        unsigned int  bbpmst_rd_ch5_fifo_depth : 8;  /* bit[16-23]: C模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH5_AXI_SEL 寄存器结构定义。地址偏移量:0x0500，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_bbpmst_rd_ch5_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_bbpmst_rd_ch5_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH5_INTR_MODE 寄存器结构定义。地址偏移量:0x0504，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch5_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH5_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0508，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_bbpmst_rd_ch5_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_bbpmst_rd_ch5_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT0_CLR_E_UNION
 结构说明  : BBPMST_INT0_CLR_E 寄存器结构定义。地址偏移量:0x051C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_clr_e : 2;  /* bit[0-1] : 中断0的清中断位：
                                                            [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT0_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT0_CLR_E_bbpmst_int0_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT0_CLR_E_bbpmst_int0_clr_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT0_STATE_E_UNION
 结构说明  : BBPMST_INT0_STATE_E 寄存器结构定义。地址偏移量:0x0520，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_state_e : 2;  /* bit[0-1] : 中断0的中断标志，为经过屏蔽后的结果：
                                                              [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT0_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT0_STATE_E_bbpmst_int0_state_e_START  (0)
#define BBPCOMM_BBPMST_INT0_STATE_E_bbpmst_int0_state_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION
 结构说明  : BBPMST_INT0_STATE_RAW_E 寄存器结构定义。地址偏移量:0x0524，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_state_raw_e : 2;  /* bit[0-1] : 中断0的中断标志，为屏蔽前的原始中断标志：
                                                                  [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_bbpmst_int0_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_bbpmst_int0_state_raw_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT1_CLR_E_UNION
 结构说明  : BBPMST_INT1_CLR_E 寄存器结构定义。地址偏移量:0x0530，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_clr_e : 2;  /* bit[0-1] : 中断1的清中断位：
                                                            [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT1_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT1_CLR_E_bbpmst_int1_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT1_CLR_E_bbpmst_int1_clr_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT1_STATE_E_UNION
 结构说明  : BBPMST_INT1_STATE_E 寄存器结构定义。地址偏移量:0x0534，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_state_e : 2;  /* bit[0-1] : 中断1的中断标志，为经过屏蔽后的结果：
                                                              [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT1_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT1_STATE_E_bbpmst_int1_state_e_START  (0)
#define BBPCOMM_BBPMST_INT1_STATE_E_bbpmst_int1_state_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION
 结构说明  : BBPMST_INT1_STATE_RAW_E 寄存器结构定义。地址偏移量:0x0538，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_state_raw_e : 2;  /* bit[0-1] : 中断1的中断标志，为屏蔽前的原始中断标志：
                                                                  [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_bbpmst_int1_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_bbpmst_int1_state_raw_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT2_CLR_E_UNION
 结构说明  : BBPMST_INT2_CLR_E 寄存器结构定义。地址偏移量:0x0544，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_clr_e : 2;  /* bit[0-1] : 中断2的清中断位：
                                                            [1:0]：分别对应AXI 0/1错误中断的清中断，脉冲有效。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT2_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT2_CLR_E_bbpmst_int2_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT2_CLR_E_bbpmst_int2_clr_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT2_STATE_E_UNION
 结构说明  : BBPMST_INT2_STATE_E 寄存器结构定义。地址偏移量:0x0548，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_state_e : 2;  /* bit[0-1] : 中断2的中断标志，为经过屏蔽后的结果：
                                                              [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT2_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT2_STATE_E_bbpmst_int2_state_e_START  (0)
#define BBPCOMM_BBPMST_INT2_STATE_E_bbpmst_int2_state_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION
 结构说明  : BBPMST_INT2_STATE_RAW_E 寄存器结构定义。地址偏移量:0x054C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_state_raw_e : 2;  /* bit[0-1] : 中断2的中断标志，为屏蔽前的原始中断标志：
                                                                  [1:0]：分别对应AXI0/1通道中断的中断标志。 */
        unsigned int  reserved                : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_bbpmst_int2_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_bbpmst_int2_state_raw_e_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION
 结构说明  : BBPMST_AXI_CLK_BYPASS 寄存器结构定义。地址偏移量:0x0550，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi_clk_bypass_reg;
    struct
    {
        unsigned int  bbpmst_wr_axi0_if_ckg_bypass : 1;  /* bit[0]   : bbpmst AXI0口写通道时钟门控旁路单元：
                                                                       1：旁路时钟门控；
                                                                       0：打开时钟门控； */
        unsigned int  bbpmst_rd_axi0_if_ckg_bypass : 1;  /* bit[1]   : bbpmst AXI0口读通道时钟门控旁路单元：
                                                                       1：旁路时钟门控；
                                                                       0：打开时钟门控； */
        unsigned int  bbpmst_wr_axi1_if_ckg_bypass : 1;  /* bit[2]   : bbpmst AXI1口写通道时钟门控旁路单元：
                                                                       1：旁路时钟门控；
                                                                       0：打开时钟门控； */
        unsigned int  bbpmst_rd_axi1_if_ckg_bypass : 1;  /* bit[3]   : bbpmst AXI1口读通道时钟门控旁路单元：
                                                                       1：旁路时钟门控；
                                                                       0：打开时钟门控； */
        unsigned int  bbpmst_sram_if_ckg_bypass    : 1;  /* bit[4]   : bbpmst sram if时钟门控旁路单元：
                                                                       1：旁路时钟门控；
                                                                       0：打开时钟门控； */
        unsigned int  reserved                     : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION;
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi0_if_ckg_bypass_START  (0)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi0_if_ckg_bypass_END    (0)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi0_if_ckg_bypass_START  (1)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi0_if_ckg_bypass_END    (1)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi1_if_ckg_bypass_START  (2)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi1_if_ckg_bypass_END    (2)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi1_if_ckg_bypass_START  (3)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi1_if_ckg_bypass_END    (3)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_sram_if_ckg_bypass_START     (4)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_sram_if_ckg_bypass_END       (4)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH6_MODE_UNION
 结构说明  : BBPMST_RD_CH6_MODE 寄存器结构定义。地址偏移量:0x0560，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch6_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch6_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch6_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch6_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH6_BURST_BEAT 寄存器结构定义。地址偏移量:0x056C，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch6_fifo_baddr : 8;  /* bit[8-15] : C模SDR_TX配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch6_fifo_depth : 8;  /* bit[16-23]: C模SDR_TX配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH6_AXI_SEL 寄存器结构定义。地址偏移量:0x0570，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_bbpmst_rd_ch6_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_bbpmst_rd_ch6_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH6_INTR_MODE 寄存器结构定义。地址偏移量:0x0574，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch6_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH6_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0578，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_bbpmst_rd_ch6_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_bbpmst_rd_ch6_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH7_MODE_UNION
 结构说明  : BBPMST_RD_CH7_MODE 寄存器结构定义。地址偏移量:0x0580，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch7_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch7_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch7_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch7_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH7_BURST_BEAT 寄存器结构定义。地址偏移量:0x058C，初值:0x000F1005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch7_fifo_baddr : 8;  /* bit[8-15] : C模待译码数据下发配置内部读通道使用的异步fifo偏移地址，默认值为0x10 */
        unsigned int  bbpmst_rd_ch7_fifo_depth : 8;  /* bit[16-23]: C模待译码数据下发配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH7_AXI_SEL 寄存器结构定义。地址偏移量:0x0590，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_bbpmst_rd_ch7_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_bbpmst_rd_ch7_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH7_INTR_MODE 寄存器结构定义。地址偏移量:0x0594，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch7_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH7_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x0598，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_bbpmst_rd_ch7_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_bbpmst_rd_ch7_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH8_MODE_UNION
 结构说明  : BBPMST_RD_CH8_MODE 寄存器结构定义。地址偏移量:0x05A0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch8_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch8_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch8_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch8_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH8_BURST_BEAT 寄存器结构定义。地址偏移量:0x05AC，初值:0x000F2005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch8_fifo_baddr : 8;  /* bit[8-15] : C模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x20 */
        unsigned int  bbpmst_rd_ch8_fifo_depth : 8;  /* bit[16-23]: C模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH8_AXI_SEL 寄存器结构定义。地址偏移量:0x05B0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_bbpmst_rd_ch8_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_bbpmst_rd_ch8_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH8_INTR_MODE 寄存器结构定义。地址偏移量:0x05B4，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch8_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH8_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x05B8，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_bbpmst_rd_ch8_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_bbpmst_rd_ch8_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH9_MODE_UNION
 结构说明  : BBPMST_RD_CH9_MODE 寄存器结构定义。地址偏移量:0x05C0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch9_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                       1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch9_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch9_base_addr”指向的地址
                                                                       1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch9_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                       1'b0:关闭；
                                                                       1'b1:打开； */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH9_BURST_BEAT 寄存器结构定义。地址偏移量:0x05CC，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                    burst_beat==0， burst1
                                                                    burst_beat==3， burst4
                                                                    burst_beat==7， burst8
                                                                    burst_beat==15，burst16
                                                                    如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch9_fifo_baddr : 8;  /* bit[8-15] : G1模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch9_fifo_depth : 8;  /* bit[16-23]: G1模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH9_AXI_SEL 寄存器结构定义。地址偏移量:0x05D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                2'b00：该通道使用master口1
                                                                2'b01：该通道使用master口2
                                                                2'b10：该通道使用ram口1
                                                                如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_bbpmst_rd_ch9_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_bbpmst_rd_ch9_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH9_INTR_MODE 寄存器结构定义。地址偏移量:0x05D4，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch9_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                    [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                    [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                 : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH9_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x05D8，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                    : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_bbpmst_rd_ch9_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_bbpmst_rd_ch9_bit_width_ind_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH10_MODE_UNION
 结构说明  : BBPMST_RD_CH10_MODE 寄存器结构定义。地址偏移量:0x05E0，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : 保留 */
        unsigned int  bbpmst_rd_ch10_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:该通道的status（通道以及AXI口是否释放）会反馈给所服务的bus口对接的IP；
                                                                        1'b0:该通道的status（通道以及AXI口是否释放）不会反馈给所服务的bus口对接的IP； */
        unsigned int  bbpmst_rd_ch10_addr_mode     : 1;  /* bit[8]    : 1’b0：该读物理通道每次搬数的起始地址为“bbpmst_rd_ch10_base_addr”指向的地址
                                                                        1’b1：该读物理通道每次搬数的起始地址由BBP的接口随路提供 */
        unsigned int  bbpmst_rd_ch10_en            : 1;  /* bit[9]    : 读通道使能信号：
                                                                        1'b0:关闭；
                                                                        1'b1:打开； */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_en_END               (9)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION
 结构说明  : BBPMST_RD_CH10_BURST_BEAT 寄存器结构定义。地址偏移量:0x05EC，初值:0x000F0005，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_burst_beat : 4;  /* bit[0-3]  : 用Master方式完成DPA上报时，单个burst的类型，含义如下：
                                                                     burst_beat==0， burst1
                                                                     burst_beat==3， burst4
                                                                     burst_beat==7， burst8
                                                                     burst_beat==15，burst16
                                                                     如果决定使用burst8， 则此种配置下硬件在读写DDR时会固定向总线发出burst8请求，同时硬件支持数据块的尾部不是一个完整的burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch10_fifo_baddr : 8;  /* bit[8-15] : G2模harq外移配置内部读通道使用的异步fifo偏移地址，默认值为0x00 */
        unsigned int  bbpmst_rd_ch10_fifo_depth : 8;  /* bit[16-23]: G2模harq外移配置内部读通道使用的异步fifo深度，默认值为0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_depth_END    (23)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION
 结构说明  : BBPMST_RD_CH10_AXI_SEL 寄存器结构定义。地址偏移量:0x05F0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_axi_sel : 2;  /* bit[0-1] : 各个读通道所选择使用的master（ram）口选择：
                                                                 2'b00：该通道使用master口1
                                                                 2'b01：该通道使用master口2
                                                                 2'b10：该通道使用ram口1
                                                                 如果所有通道只需要1个master口，则在代码中可用宏定义方式减少一个master口 */
        unsigned int  reserved               : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_bbpmst_rd_ch10_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_bbpmst_rd_ch10_axi_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION
 结构说明  : BBPMST_RD_CH10_INTR_MODE 寄存器结构定义。地址偏移量:0x05F4，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_intr_thres : 16; /* bit[0-15] : 当多次中断使能有效时，N的取值 */
        unsigned int  bbpmst_rd_ch10_intr_mode  : 2;  /* bit[16-17]: 该读物理通道产生中断的方式：
                                                                     [1]：多次中断的使能开关， 1'b1表示一次搬数过程中，每搬完N个byte就产生一次中断，1'b0表示关闭该功能
                                                                     [0]：单次中断的使能开关，1'b1表示一次搬数完全结束后产生一次中断，1'b0表示关闭该功能 */
        unsigned int  reserved                  : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_mode_END     (17)


/*****************************************************************************
 结构名    : BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION
 结构说明  : BBPMST_RD_CH10_BIT_WIDTH_IND 寄存器结构定义。地址偏移量:0x05F8，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_bit_width_ind : 2;  /* bit[0-1] : 读通道0每个32比特读数据有效数据个数指示：0，表示每个32比特读数据含5个有效数据；1，表示每个32比特读数据含8个有效数据；2，表示每个32比特读数据含1个有效数据；3，表示每个32比特读数据含4个有效数据； */
        unsigned int  reserved                     : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_bbpmst_rd_ch10_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_bbpmst_rd_ch10_bit_width_ind_END    (1)




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

#endif /* end of bbp_guc_bbpmst_interface.h */
