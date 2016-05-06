/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_stream_router_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:07
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_STREAM_ROUTER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_STREAM_ROUTER_INTERFACE_H__
#define __SOC_ISP_STREAM_ROUTER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) STREAM_ROUTER
 ****************************************************************************/
/* 寄存器说明：CSI2 VC/DT filtering for CSIA interface
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CSIFILTER_A_UNION */
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_ADDR(base)  ((base) + (0x0))

/* 寄存器说明：CSI2 VC/DT filtering for CSIB interface
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CSIFILTER_B_UNION */
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_ADDR(base)  ((base) + (0x4))

/* 寄存器说明：CSI2 VC/DT filtering for CSIC interface
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CSIFILTER_C_UNION */
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_ADDR(base)  ((base) + (0x8))

/* 寄存器说明：CSI2 stream go bits
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION */
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_ADDR(base) ((base) + (0xC))

/* 寄存器说明：Pressure start configuration register
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION */
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_ADDR(base) ((base) + (0x10))

/* 寄存器说明：Pressure stop configuration register
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION */
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_ADDR(base) ((base) + (0x14))

/* 寄存器说明：ID router configuration (field 0)
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_UNION */
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_ADDR(base)  ((base) + (0x18))

/* 寄存器说明：ID router configuration (field 1)
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_UNION */
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_ADDR(base)  ((base) + (0x1C))

/* 寄存器说明：Reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_ADDR(base, ReformatRange)  ((base) + (0x20+0x8*(ReformatRange)))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_ADDR(base, ReformatRange)  ((base) + (0x24+0x8*(ReformatRange)))

/* 寄存器说明：End Of Line counter interruopt event configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_EOL_CNT_UNION */
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_ADDR(base)      ((base) + (0x60))

/* 寄存器说明：InFraRed processing
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PROCESSING_IR_UNION */
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_ADDR(base) ((base) + (0x64))

/* 寄存器说明：LeftRight processing:
            Bloc0: first bloc (to be configured when 4 strides)
            Bloc1: second bloc (to be configured when 3 or 4 strides)
            Bloc2: thrird bloc (to be configured when 2, 3 or 4 strides)
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PROCESSING_LR_UNION */
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_ADDR(base, LR_Range)  ((base) + (0x68+0x4*(LR_Range)))

/* 寄存器说明：Line Buffer management
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_UNION */
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_ADDR(base) ((base) + (0x74))

/* 寄存器说明：DPCM config register
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_DPCM_UNION */
#define SOC_ISP_STREAM_ROUTER_DPCM_ADDR(base)         ((base) + (0x78))

/* 寄存器说明：Video port router configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_UNION */
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_ADDR(base)  ((base) + (0x7C))

/* 寄存器说明：Video port router configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_UNION */
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_ADDR(base)  ((base) + (0x80))

/* 寄存器说明：Video port router configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_UNION */
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_ADDR(base)  ((base) + (0x84))

/* 寄存器说明：Video port router configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_UNION */
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_ADDR(base)  ((base) + (0x88))

/* 寄存器说明：pixfrag conversion before sending the data out of stream router
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_UNION */
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_ADDR(base) ((base) + (0x8C))

/* 寄存器说明：register used to enable the FIFO peak mechanism
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PEAK_CTRL_UNION */
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_ADDR(base)    ((base) + (0x90))

/* 寄存器说明：FIFO peak information
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PEAK_STATUS_UNION */
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_ADDR(base)  ((base) + (0x94))

/* 寄存器说明：Back pressure FIFO CSI source
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_BP_SOURCE_UNION */
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_ADDR(base)    ((base) + (0x98))

/* 寄存器说明：Back pressure FIFO B and C extension
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_BP_EXTENSION_UNION */
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_ADDR(base) ((base) + (0x9C))

/* 寄存器说明：DFS configuration register
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_DFS_CFG_UNION */
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_ADDR(base)      ((base) + (0x100))

/* 寄存器说明：Vertical Crop configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CROPV_UNION */
#define SOC_ISP_STREAM_ROUTER_CROPV_ADDR(base, Range2)  ((base) + (0x104+0x8*(Range2)))

/* 寄存器说明：Horizontal Crop configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_CROPH_UNION */
#define SOC_ISP_STREAM_ROUTER_CROPH_ADDR(base, Range2)  ((base) + (0x108+0x8*(Range2)))

/* 寄存器说明：used to force the clock which is generally controlled by HW
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x120))





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

/****************************************************************************
                     (1/1) STREAM_ROUTER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CSIFILTER_A_UNION
 结构说明  : CSIFILTER_A 寄存器结构定义。地址偏移量:0x0，初值:0xC0804000，宽度:32
 寄存器说明: CSI2 VC/DT filtering for CSIA interface
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csia_data_type_0  : 6;  /* bit[0-5]  : Filter 0: Data Type used
                                                             Is it expected that 2 filters do not have the same {VT:DT} configuration */
        unsigned int  csia_virtual_ch_0 : 2;  /* bit[6-7]  : Filter 0: Virtual Channel used */
        unsigned int  csia_data_type_1  : 6;  /* bit[8-13] : Filter 1: Data Type used */
        unsigned int  csia_virtual_ch_1 : 2;  /* bit[14-15]: Filter 1: Virtual Channel used */
        unsigned int  csia_data_type_2  : 6;  /* bit[16-21]: Filter 2: Data Type used */
        unsigned int  csia_virtual_ch_2 : 2;  /* bit[22-23]: Filter 2: Virtual Channel used */
        unsigned int  csia_data_type_3  : 6;  /* bit[24-29]: Filter 3: Data Type used */
        unsigned int  csia_virtual_ch_3 : 2;  /* bit[30-31]: Filter 3: Virtual Channel used */
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_A_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_0_START   (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_0_END     (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_0_START  (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_0_END    (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_1_START   (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_1_END     (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_1_START  (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_1_END    (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_2_START   (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_2_END     (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_2_START  (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_2_END    (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_3_START   (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_data_type_3_END     (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_3_START  (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_A_csia_virtual_ch_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CSIFILTER_B_UNION
 结构说明  : CSIFILTER_B 寄存器结构定义。地址偏移量:0x4，初值:0xC0804000，宽度:32
 寄存器说明: CSI2 VC/DT filtering for CSIB interface
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csib_data_type_0  : 6;  /* bit[0-5]  : Filter 0: Data Type used
                                                             Is it expected that 2 filters do not have the same {VT:DT} configuration */
        unsigned int  csib_virtual_ch_0 : 2;  /* bit[6-7]  : Filter 0: Virtual Channel used */
        unsigned int  csib_data_type_1  : 6;  /* bit[8-13] : Filter 1: Data Type used */
        unsigned int  csib_virtual_ch_1 : 2;  /* bit[14-15]: Filter 1: Virtual Channel used */
        unsigned int  csib_data_type_2  : 6;  /* bit[16-21]: Filter 2: Data Type used */
        unsigned int  csib_virtual_ch_2 : 2;  /* bit[22-23]: Filter 2: Virtual Channel used */
        unsigned int  csib_data_type_3  : 6;  /* bit[24-29]: Filter 3: Data Type used */
        unsigned int  csib_virtual_ch_3 : 2;  /* bit[30-31]: Filter 3: Virtual Channel used */
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_B_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_0_START   (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_0_END     (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_0_START  (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_0_END    (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_1_START   (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_1_END     (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_1_START  (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_1_END    (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_2_START   (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_2_END     (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_2_START  (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_2_END    (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_3_START   (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_data_type_3_END     (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_3_START  (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_B_csib_virtual_ch_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CSIFILTER_C_UNION
 结构说明  : CSIFILTER_C 寄存器结构定义。地址偏移量:0x8，初值:0xC0804000，宽度:32
 寄存器说明: CSI2 VC/DT filtering for CSIC interface
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csic_data_type_0  : 6;  /* bit[0-5]  : Filter 0: Data Type used
                                                             Is it expected that 2 filters do not have the same {VT:DT} configuration */
        unsigned int  csic_virtual_ch_0 : 2;  /* bit[6-7]  : Filter 0: Virtual Channel used */
        unsigned int  csic_data_type_1  : 6;  /* bit[8-13] : Filter 1: Data Type used */
        unsigned int  csic_virtual_ch_1 : 2;  /* bit[14-15]: Filter 1: Virtual Channel used */
        unsigned int  csic_data_type_2  : 6;  /* bit[16-21]: Filter 2: Data Type used */
        unsigned int  csic_virtual_ch_2 : 2;  /* bit[22-23]: Filter 2: Virtual Channel used */
        unsigned int  csic_data_type_3  : 6;  /* bit[24-29]: Filter 3: Data Type used */
        unsigned int  csic_virtual_ch_3 : 2;  /* bit[30-31]: Filter 3: Virtual Channel used */
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_C_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_0_START   (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_0_END     (5)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_0_START  (6)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_0_END    (7)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_1_START   (8)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_1_END     (13)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_1_START  (14)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_1_END    (15)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_2_START   (16)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_2_END     (21)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_2_START  (22)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_2_END    (23)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_3_START   (24)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_data_type_3_END     (29)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_3_START  (30)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_C_csic_virtual_ch_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION
 结构说明  : CSIFILTER_GO 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: CSI2 stream go bits
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_go : 12; /* bit[0-11] : Go bits (Write only). 
                                                     This register allows to control the frames which need to be transmitted. These bits are write only 1.
                                                     0: no effect
                                                     1: implies that next incoming frame will have to be transmitted
                                                     The software must re-arm the go bit for every frame and can do it as soon as the first line of the current frame is received. 
                                                     If a current frame is already under processing, writing into this bit, implies that next frame will have to be processed also.
                                                     We have 12 bits since 4 filters on every of the 3 CSI cameras.
                                                     11:8 : CSIC camera - filters 3 (bit 11),2 (bit 10),1 (bit 9),0 (bit 8) 
                                                      7:4 : CSIB camera - filters 3 (bit 7), 2 (bit 6),1 (bit 5),0 (bit 4) 
                                                      3:0 : CSIA camera - filters 3 (bit 3), 2 (bit 2),1 (bit 1),0 (bit 0)  */
        unsigned int  reserved  : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_START  (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION
 结构说明  : PRESSURE_START 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: Pressure start configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pressure_threshold_start_a : 7;  /* bit[0-6]  : camera A is expected to work up to 6Gb/s. 
                                                                      Priority request generated if the fifo level > 2*threshold
                                                                      Max threshold : 127 (= fifo level higher than 254)  */
        unsigned int  reserved_0                 : 1;  /* bit[7]    : reserved */
        unsigned int  pressure_threshold_start_b : 7;  /* bit[8-14] : camera B is expected to work up to 6Gb/s. 
                                                                      Max threshold : 127 */
        unsigned int  reserved_1                 : 1;  /* bit[15]   : reserved */
        unsigned int  pressure_threshold_start_c : 7;  /* bit[16-22]: camera C is expected to work up to 1Gb/s. 
                                                                      Max threshold : 127 */
        unsigned int  reserved_2                 : 8;  /* bit[23-30]: reserved */
        unsigned int  pressure_enable            : 1;  /* bit[31]   : Enable the pressure_bit request generation based on threshold registers */
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_END    (6)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_START  (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_END    (14)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_c_START  (16)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_c_END    (22)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_START             (31)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION
 结构说明  : PRESSURE_STOP 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: Pressure stop configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pressure_threshold_stop_a : 4;  /* bit[0-3]  : Camera A
                                                                     Priority request stopped if the fifo level < 2*threshold_stop
                                                                     Max threshold : 15 */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : reserved */
        unsigned int  pressure_threshold_stop_b : 4;  /* bit[8-11] : Camera B
                                                                     Priority request stopped if the fifo level < 2*threshold_stop
                                                                     Max threshold : 15 */
        unsigned int  reserved_1                : 4;  /* bit[12-15]: reserved */
        unsigned int  pressure_threshold_stop_c : 4;  /* bit[16-19]: Camera C
                                                                     Priority request stopped if the fifo level < 2*threshold_stop
                                                                     Max threshold : 15 */
        unsigned int  reserved_2                : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_END    (3)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_START  (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_END    (11)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_c_START  (16)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_c_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_UNION
 结构说明  : ID_ROUTER_0 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: ID router configuration (field 0)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idr_input_stream_0 : 4;  /* bit[0-3]  : Output #0:Enables to select the input stream ID:
                                                              3:2: input camera ID (A: 00, B:01, C:10, Value 11 unsupported)
                                                              1:0: input stream ID (as provided by the CSI2 module) */
        unsigned int  idr_enable_0       : 1;  /* bit[4]    : Output #0:Enables INPUT_STREAM programmation */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : reserved */
        unsigned int  idr_input_stream_1 : 4;  /* bit[8-11] :  */
        unsigned int  idr_enable_1       : 1;  /* bit[12]   :  */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: reserved */
        unsigned int  idr_input_stream_2 : 4;  /* bit[16-19]:  */
        unsigned int  idr_enable_2       : 1;  /* bit[20]   :  */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: reserved */
        unsigned int  idr_input_stream_3 : 4;  /* bit[24-27]:  */
        unsigned int  idr_enable_3       : 1;  /* bit[28]   :  */
        unsigned int  reserved_3         : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_0_END    (3)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_0_START        (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_0_END          (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_1_START  (8)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_1_END    (11)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_1_START        (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_1_END          (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_2_START  (16)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_2_END    (19)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_2_START        (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_2_END          (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_3_START  (24)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_input_stream_3_END    (27)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_3_START        (28)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_0_idr_enable_3_END          (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_UNION
 结构说明  : ID_ROUTER_1 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: ID router configuration (field 1)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idr_input_stream_4 : 4;  /* bit[0-3]  :  */
        unsigned int  idr_enable_4       : 1;  /* bit[4]    :  */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : reserved */
        unsigned int  idr_input_stream_5 : 4;  /* bit[8-11] :  */
        unsigned int  idr_enable_5       : 1;  /* bit[12]   :  */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: reserved */
        unsigned int  idr_input_stream_6 : 4;  /* bit[16-19]:  */
        unsigned int  idr_enable_6       : 1;  /* bit[20]   :  */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: reserved */
        unsigned int  idr_input_stream_7 : 4;  /* bit[24-27]:  */
        unsigned int  idr_enable_7       : 1;  /* bit[28]   :  */
        unsigned int  reserved_3         : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_4_START  (0)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_4_END    (3)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_4_START        (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_4_END          (4)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_5_START  (8)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_5_END    (11)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_5_START        (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_5_END          (12)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_START  (16)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_END    (19)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_START        (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_END          (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_START  (24)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_END    (27)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_START        (28)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_END          (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_UNION
 结构说明  : REFORMAT 寄存器结构定义。地址偏移量:0x20+0x8*(ReformatRange)，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines     : 13; /* bit[0-12] : Number of lines in the picture
                                                                  0: 1 line
                                                                  1: 2 line
                                                                  …
                                                                  0x1FFF: 8192 lines */
        unsigned int  reformat_pixel_reorder : 3;  /* bit[13-15]: Pixel reordering functionality: 0x0,0x2,0x3,0x4 follow the CSI2 spec.
                                                                  0x0: 8 bit format - CSI2 compatible (first pixel starting on LSByte). Used for RAW8, Generic 8 bit
                                                                  0x1: 8 bit format - non-CSI2 compatible (first pixel starting on MSByte). Used for YUV422 8-bit.
                                                                  0x2: 10 bit format (first pixel starting on LSB). Used for YUV422 10-bit, RAW10
                                                                  0x3: 12 bit format (first pixel starting on LSB). Used for RAW12
                                                                  0x4: 14 bit format (first pixel starting on LSB). Used for RAW14 */
        unsigned int  reformat_num_pixels    : 13; /* bit[16-28]: Number of pixfrags per line
                                                                  0: 1 pixfrag
                                                                  1: 2 pixfrag
                                                                  …
                                                                  0x1FFF: 8192 pixfrags */
        unsigned int  reserved               : 2;  /* bit[29-30]: reserved */
        unsigned int  enable                 : 1;  /* bit[31]   : Enable the reformat functionality
                                                                  1: enabled
                                                                  0: bypassed */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_lines_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_lines_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_pixel_reorder_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_pixel_reorder_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_pixels_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_reformat_num_pixels_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_enable_START                  (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_enable_END                    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_UNION
 结构说明  : REFORMAT_MINSPACE 寄存器结构定义。地址偏移量:0x24+0x8*(ReformatRange)，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space : 6;  /* bit[0-5] : Minimum space between 2 frames is min_vertical_space*num_pixels clock cycles
                                                                      0x0: no space allowed
                                                                      0x1: one line space minimum (in clock cycles)
                                                                      …
                                                                      0x3F: 63 lines space minimum */
        unsigned int  reserved                    : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_reformat_min_vertical_space_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_reformat_min_vertical_space_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_EOL_CNT_UNION
 结构说明  : EOL_CNT 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: End Of Line counter interruopt event configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  eol_num_lines_0 : 13; /* bit[0-12] : End Of line event generation (module 0)
                                                           0: no event to generate
                                                           1: 1 line
                                                           …
                                                           0x1FFF: 8191 lines */
        unsigned int  reserved_0      : 3;  /* bit[13-15]: reserved */
        unsigned int  eol_num_lines_1 : 13; /* bit[16-28]: End Of line event generation (module 1)
                                                           0: no event to generate
                                                           1: 1 line
                                                           …
                                                           0x1FFF: 8191 lines */
        unsigned int  reserved_1      : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_EOL_CNT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_0_END    (12)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_1_START  (16)
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_eol_num_lines_1_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PROCESSING_IR_UNION
 结构说明  : PROCESSING_IR 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: InFraRed processing
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last_line : 12; /* bit[0-11] : Last IR Line Number:
                                                     0x0: line 0
                                                     0x1: line 1
                                                     …
                                                     0xFFF: line 4095 */
        unsigned int  reserved_0: 4;  /* bit[12-15]: reserved */
        unsigned int  location  : 2;  /* bit[16-17]: IR location:
                                                     0x0:even pixel, even line (Ix_yz)
                                                     0x1:odd pixel, even line (wI_yz)
                                                     0x2:even pixel, odd line (wx_Iz)
                                                     0x3: odd pixel odd line (wx_yI) */
        unsigned int  reserved_1: 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_PROCESSING_IR_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_last_line_START  (0)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_last_line_END    (11)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_location_START   (16)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_IR_location_END     (17)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PROCESSING_LR_UNION
 结构说明  : PROCESSING_LR 寄存器结构定义。地址偏移量:0x68+0x4*(LR_Range)，初值:0x00000000，宽度:32
 寄存器说明: LeftRight processing:
            Bloc0: first bloc (to be configured when 4 strides)
            Bloc1: second bloc (to be configured when 3 or 4 strides)
            Bloc2: thrird bloc (to be configured when 2, 3 or 4 strides)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lr_left_size : 12; /* bit[0-11] : Number of pixfrags to copy into the left side of a line.
                                                        The total number of pixfrags copied for each FrontEnd interface is:
                                                        - left : left_size + overlap
                                                        - right : starting when left_size pixels are written into the left buffer. All pixels received until the end of line are copied into the right buffer.
                                                        0x0: 0 pixfrags (all pixfrags are transmitted to the right side)
                                                        0x1: 2 pixfrags
                                                        ...
                                                        0xFFF : 8190 pixfrags
                                                        Note: lr_overlap = 0 and lr_left_size = 0 is a valid combination  */
        unsigned int  reserved_0   : 4;  /* bit[12-15]: reserved */
        unsigned int  lr_overlap   : 7;  /* bit[16-22]: Number of pixfrags to use for the left/right overlap (from 0 to 254 pixfrags).
                                                        0: 0 overlap
                                                        1: 2 pixfrags overlap
                                                        …
                                                        127: 254 pixfrags overlap */
        unsigned int  reserved_1   : 9;  /* bit[23-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_PROCESSING_LR_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_left_size_START  (0)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_left_size_END    (11)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_overlap_START    (16)
#define SOC_ISP_STREAM_ROUTER_PROCESSING_LR_lr_overlap_END      (22)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_UNION
 结构说明  : LINE_BUFFER_MGNT 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: Line Buffer management
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lbm_threshold_0 : 9;  /* bit[0-8]  : Threshold to use to push the data out (the data is pushed automatically when the end of line is received) : the buffer is flushed if the fifo_level > threshold_buf0
                                                           When threshold_buf0 = 0, this is like the threshold functionality is not used.
                                                           Max is 0x1FF: 511 locations */
        unsigned int  reserved_0      : 7;  /* bit[9-15] : reserved */
        unsigned int  lbm_threshold_1 : 9;  /* bit[16-24]: Threshold to use to push the data out (the data is pushed automatically when the end of line is received) : the buffer is flushed if the fifo_level > threshold_buf1
                                                           When threshold_buf1 = 0, this is like the threshold functionality is not used.
                                                           Max is 0x1FF: 511 locations */
        unsigned int  reserved_1      : 7;  /* bit[25-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_0_END    (8)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_1_START  (16)
#define SOC_ISP_STREAM_ROUTER_LINE_BUFFER_MGNT_lbm_threshold_1_END    (24)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_DPCM_UNION
 结构说明  : DPCM 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: DPCM config register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 14; /* bit[0-13] : reserved */
        unsigned int  dpcm_enable_0 : 1;  /* bit[14]   : enables the dpcm function or not.
                                                         If 0, the dpcm decompression is bypassed and the data is forwarded to th ecrop functionl. */
        unsigned int  dpcm_format_0 : 1;  /* bit[15]   : DPCM format to decode (DPCM instance 1) - always assumes Predictor1 selection
                                                         0: from 8 to 10
                                                         1: from 8 to 12 */
        unsigned int  reserved_1    : 14; /* bit[16-29]: reserved */
        unsigned int  dpcm_enable_1 : 1;  /* bit[30]   : enables the dpcm function or not.
                                                         If 0, the dpcm decompression is bypassed and the data is forwarded to th ecrop functionl. */
        unsigned int  dpcm_format_1 : 1;  /* bit[31]   : DPCM format to decode (DPCM instance 1) - always assumes Predictor1 selection
                                                         0: from 8 to 10
                                                         1: from 8 to 12 */
    } reg;
} SOC_ISP_STREAM_ROUTER_DPCM_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_0_START  (14)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_0_END    (14)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_0_START  (15)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_0_END    (15)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_1_START  (30)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_enable_1_END    (30)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_1_START  (31)
#define SOC_ISP_STREAM_ROUTER_DPCM_dpcm_format_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_UNION
 结构说明  : VP_ROUTER_0 寄存器结构定义。地址偏移量:0x7C，初值:0x00000000，宽度:32
 寄存器说明: Video port router configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpr_input_vp_0 : 4;  /* bit[0-3]  : Output #0:Enables to select the input video port source:
                                                          0: from Formatter 0
                                                          1: from Formater 1
                                                          2: from Formater 2
                                                          3: from Formater 3
                                                          4: from Formater 4
                                                          5: from Formater 5
                                                          6: from left/right processing: left image
                                                          7: from left/right processing: right image
                                                          8: from IR processing
                                                          9: from 1/4 line buffer 0
                                                          10: from 1/4 line buffer 1
                                                          11: pixel interleave instance 0
                                                          12: pixel interleave instance 1
                                                          13: DPCM convertion instance 0
                                                          14: DPCM convertion instance 1 */
        unsigned int  vpr_enable_0   : 1;  /* bit[4]    : Output #0:Enables input_vp_0 programmation */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : reserved */
        unsigned int  vpr_input_vp_1 : 4;  /* bit[8-11] :  */
        unsigned int  vpr_enable_1   : 1;  /* bit[12]   :  */
        unsigned int  reserved_1     : 3;  /* bit[13-15]: reserved */
        unsigned int  vpr_input_vp_2 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_2   : 1;  /* bit[20]   :  */
        unsigned int  reserved_2     : 3;  /* bit[21-23]: reserved */
        unsigned int  vpr_input_vp_3 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_3   : 1;  /* bit[28]   :  */
        unsigned int  reserved_3     : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_0_END    (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_0_START    (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_0_END      (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_1_START  (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_1_END    (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_1_START    (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_1_END      (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_2_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_2_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_2_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_2_END      (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_3_START  (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_input_vp_3_END    (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_3_START    (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_0_vpr_enable_3_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_UNION
 结构说明  : VP_ROUTER_1 寄存器结构定义。地址偏移量:0x80，初值:0x00000000，宽度:32
 寄存器说明: Video port router configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpr_input_vp_4 : 4;  /* bit[0-3]  :  */
        unsigned int  vpr_enable_4   : 1;  /* bit[4]    :  */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : reserved */
        unsigned int  vpr_input_vp_5 : 4;  /* bit[8-11] :  */
        unsigned int  vpr_enable_5   : 1;  /* bit[12]   :  */
        unsigned int  reserved_1     : 3;  /* bit[13-15]: reserved */
        unsigned int  vpr_input_vp_6 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_6   : 1;  /* bit[20]   :  */
        unsigned int  reserved_2     : 3;  /* bit[21-23]: reserved */
        unsigned int  vpr_input_vp_7 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_7   : 1;  /* bit[28]   :  */
        unsigned int  reserved_3     : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_START  (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_END    (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_START    (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_END      (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_5_START  (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_5_END    (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_5_START    (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_5_END      (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_END      (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_START  (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_END    (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_START    (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_UNION
 结构说明  : VP_ROUTER_2 寄存器结构定义。地址偏移量:0x84，初值:0x00000000，宽度:32
 寄存器说明: Video port router configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpr_input_vp_8  : 4;  /* bit[0-3]  :  */
        unsigned int  vpr_enable_8    : 1;  /* bit[4]    :  */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  : reserved */
        unsigned int  vpr_input_vp_9  : 4;  /* bit[8-11] :  */
        unsigned int  vpr_enable_9    : 1;  /* bit[12]   :  */
        unsigned int  reserved_1      : 3;  /* bit[13-15]: reserved */
        unsigned int  vpr_input_vp_10 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_10   : 1;  /* bit[20]   :  */
        unsigned int  reserved_2      : 3;  /* bit[21-23]: reserved */
        unsigned int  vpr_input_vp_11 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_11   : 1;  /* bit[28]   :  */
        unsigned int  reserved_3      : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_8_START   (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_8_END     (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_8_START     (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_8_END       (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_9_START   (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_9_END     (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_9_START     (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_9_END       (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_10_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_10_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_10_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_10_END      (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_11_START  (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_input_vp_11_END    (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_11_START    (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_2_vpr_enable_11_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_UNION
 结构说明  : VP_ROUTER_3 寄存器结构定义。地址偏移量:0x88，初值:0x00000000，宽度:32
 寄存器说明: Video port router configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpr_input_vp_12 : 4;  /* bit[0-3]  :  */
        unsigned int  vpr_enable_12   : 1;  /* bit[4]    :  */
        unsigned int  reserved_0      : 3;  /* bit[5-7]  : reserved */
        unsigned int  vpr_input_vp_13 : 4;  /* bit[8-11] :  */
        unsigned int  vpr_enable_13   : 1;  /* bit[12]   :  */
        unsigned int  reserved_1      : 3;  /* bit[13-15]: reserved */
        unsigned int  vpr_input_vp_14 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_14   : 1;  /* bit[20]   :  */
        unsigned int  reserved_2      : 3;  /* bit[21-23]: reserved */
        unsigned int  reserved_3      : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_12_START  (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_12_END    (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_12_START    (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_12_END      (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_13_START  (8)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_13_END    (11)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_13_START    (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_13_END      (12)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_END      (20)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_UNION
 结构说明  : PIXFRAG_CONVERT 寄存器结构定义。地址偏移量:0x8C，初值:0x00000000，宽度:32
 寄存器说明: pixfrag conversion before sending the data out of stream router
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma3_out : 1;  /* bit[0]   :  */
        unsigned int  dma2_out : 1;  /* bit[1]   :  */
        unsigned int  dma1_out : 1;  /* bit[2]   :  */
        unsigned int  fe2_out  : 1;  /* bit[3]   :  */
        unsigned int  fe1_out  : 1;  /* bit[4]   : bit used to select how the data must be sent out on output (FE1, FE2, dma1. dma2, dma3)
                                                   0: 1PF
                                                   1: format unchanged */
        unsigned int  reserved : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_START  (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_END    (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_START  (1)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_END    (1)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma1_out_START  (2)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma1_out_END    (2)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe2_out_START   (3)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe2_out_END     (3)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe1_out_START   (4)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_fe1_out_END     (4)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PEAK_CTRL_UNION
 结构说明  : PEAK_CTRL 寄存器结构定义。地址偏移量:0x90，初值:0x00000000，宽度:32
 寄存器说明: register used to enable the FIFO peak mechanism
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peak_fifo_id : 3;  /* bit[0-2] : Enable bit to select the FIFO source:
                                                       000: back pressure FIFO A
                                                       001: back pressure FIFO B
                                                       010: back pressure FIFO C
                                                       011: QuarterLine Buffer 0
                                                       100: QuarterLine Buffer 1
                                                       101: extension back pressure FIFO B
                                                       110: extension back pressure FIFO C
                                                       111: AsyncFIFO CSI A (ISP domain) */
        unsigned int  reserved_0   : 5;  /* bit[3-7] : reserved */
        unsigned int  peak_enable  : 1;  /* bit[8]   : Enable bit to implement the fifo peak mechanism */
        unsigned int  reserved_1   : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_PEAK_CTRL_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_fifo_id_START  (0)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_fifo_id_END    (2)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_enable_START   (8)
#define SOC_ISP_STREAM_ROUTER_PEAK_CTRL_peak_enable_END     (8)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PEAK_STATUS_UNION
 结构说明  : PEAK_STATUS 寄存器结构定义。地址偏移量:0x94，初值:0x00000000，宽度:32
 寄存器说明: FIFO peak information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peak_fifo_status : 12; /* bit[0-11] : FIFO level peak for fifo_peak_id */
        unsigned int  reserved         : 17; /* bit[12-28]: reserved */
        unsigned int  csi_afifo_status : 3;  /* bit[29-31]: afifo full state */
    } reg;
} SOC_ISP_STREAM_ROUTER_PEAK_STATUS_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_peak_fifo_status_START  (0)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_peak_fifo_status_END    (11)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_csi_afifo_status_START  (29)
#define SOC_ISP_STREAM_ROUTER_PEAK_STATUS_csi_afifo_status_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_BP_SOURCE_UNION
 结构说明  : BP_SOURCE 寄存器结构定义。地址偏移量:0x98，初值:0x00000024，宽度:32
 寄存器说明: Back pressure FIFO CSI source
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bp_source_a : 2;  /* bit[0-1] : Static configuration register:
                                                      0: CSI A
                                                      1: CSI B
                                                      2: CSI C
                                                      3: reserved (default CSI C)  */
        unsigned int  bp_source_b : 2;  /* bit[2-3] : see bp_source_a */
        unsigned int  bp_source_c : 2;  /* bit[4-5] : see bp_source_a */
        unsigned int  reserved    : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_BP_SOURCE_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_END    (1)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_START  (2)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_END    (3)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_c_START  (4)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_c_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_BP_EXTENSION_UNION
 结构说明  : BP_EXTENSION 寄存器结构定义。地址偏移量:0x9C，初值:0x00000000，宽度:32
 寄存器说明: Back pressure FIFO B and C extension
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pressure_threshold_start_dfs_b : 12; /* bit[0-11] : Priority request generated if the fifo level > threshold when DFS window is active
                                                                          Max threshold : 4K locations of 128 bits (64KBytes) */
        unsigned int  reserved_0                     : 3;  /* bit[12-14]:  */
        unsigned int  bp_extension_b_enable          : 1;  /* bit[15]   : used to enable the external DFS buffer of 4K locations of 128 bits (default disabled) for back pressure FIFO B */
        unsigned int  pressure_threshold_start_dfs_c : 12; /* bit[16-27]:  */
        unsigned int  reserved_1                     : 3;  /* bit[28-30]:  */
        unsigned int  bp_extension_c_enable          : 1;  /* bit[31]   : used to enable the external DFS buffer of 4K locations of 128 bits (default disabled) for back pressure FIFO C */
    } reg;
} SOC_ISP_STREAM_ROUTER_BP_EXTENSION_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_b_START  (0)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_b_END    (11)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_b_enable_START           (15)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_b_enable_END             (15)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_c_START  (16)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_pressure_threshold_start_dfs_c_END    (27)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_c_enable_START           (31)
#define SOC_ISP_STREAM_ROUTER_BP_EXTENSION_bp_extension_c_enable_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_DFS_CFG_UNION
 结构说明  : DFS_CFG 寄存器结构定义。地址偏移量:0x100，初值:0xFF80003F，宽度:32
 寄存器说明: DFS configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfs_granularity      : 10; /* bit[0-9]  : on 10 bits: granularity used (number of clock cycles) to measure the dfs_trig* registers when the functionality is enabled
                                                                0: wait 1 clock cycle
                                                                0x3F: wait 1024 clock cycles */
        unsigned int  dfs_trig_wait_before : 2;  /* bit[10-11]: Number of dfs_granularity delay to wait before de-assertion of the dfs_trig signal.
                                                                0: no delay
                                                                1: wait 1*dfs_granularity clock cycles
                                                                …
                                                                0x11: 3 * dfs_granularity */
        unsigned int  dfs_enable           : 11; /* bit[12-22]: length of dfs_trig signal, expressed in dfs_granularity delay .
                                                                0: disabled (no dfs generated) ) DFS_TRIG signal is at '1' (but at 0 when pictures are received: VVSYNC=1)
                                                                1: wait 1*dfs_granularity clock cycles
                                                                …
                                                                0x7FE: 2046 * dfs_granularity
                                                                0x7FF: DFS_TRIG forced to '0' */
        unsigned int  dfs_trig_wait_after  : 9;  /* bit[23-31]: Number of dfs_granularity delay to wait after de-assertion of the dfs_trig signal.
                                                                0: no delay
                                                                1: wait 1*dfs_granularity clock cycles
                                                                …
                                                                0x1FF: 511 * dfs_granularity */
    } reg;
} SOC_ISP_STREAM_ROUTER_DFS_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_granularity_START       (0)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_granularity_END         (9)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_before_START  (10)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_before_END    (11)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_enable_START            (12)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_enable_END              (22)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_after_START   (23)
#define SOC_ISP_STREAM_ROUTER_DFS_CFG_dfs_trig_wait_after_END     (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CROPV_UNION
 结构说明  : CROPV 寄存器结构定义。地址偏移量:0x104+0x8*(Range2)，初值:0x1FFF0000，宽度:32
 寄存器说明: Vertical Crop configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cropv_start_0 : 13; /* bit[0-12] : First valid line number
                                                         0:first valid line is line 0
                                                         …
                                                         0x1FFF: first valid line is line 8191 */
        unsigned int  reserved_0    : 3;  /* bit[13-15]:  */
        unsigned int  cropv_end_0   : 13; /* bit[16-28]: Last valid line:
                                                         0: last valid line is line 0
                                                         …
                                                         0x1FFF: last valid line is line 8191 
                                                         note:
                                                         cropv_start_0 ==0 & croph_start_0 == 0 & cropv_end_0 ==0x1FFF & croph_end_0 ==0xFFF:the crop function is bypaaed and the input video port is forwarded directly to the output */
        unsigned int  reserved_1    : 2;  /* bit[29-30]:  */
        unsigned int  reserved_2    : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_CROPV_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_start_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_start_0_END    (12)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_end_0_START    (16)
#define SOC_ISP_STREAM_ROUTER_CROPV_cropv_end_0_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_CROPH_UNION
 结构说明  : CROPH 寄存器结构定义。地址偏移量:0x108+0x8*(Range2)，初值:0x0FFF0000，宽度:32
 寄存器说明: Horizontal Crop configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  croph_start_0 : 12; /* bit[0-11] : First valid pixel in the line
                                                         0:first valid pixel/pixfrag is pixel 0
                                                         1: first valid pixel/pixfrag is pixel 2
                                                         …
                                                         0xFFF: first valid pixel/pixfrag is pixel 8190 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  croph_end_0   : 12; /* bit[16-27]: Last valid pixel in the line
                                                         0:last valid pixel/pixfrag is pixel 1
                                                         1: last valid pixel/pixfrag is pixel 3
                                                         …
                                                         0xFFF: last valid pixel/pixfrag is pixel 8191 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_CROPH_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_start_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_start_0_END    (11)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_end_0_START    (16)
#define SOC_ISP_STREAM_ROUTER_CROPH_croph_end_0_END      (27)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_UNION
 结构说明  : FORCE_CLK_ON_CFG 寄存器结构定义。地址偏移量:0x120，初值:0x00000001，宽度:32
 寄存器说明: used to force the clock which is generally controlled by HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_clk_on : 1;  /* bit[0]   : 0: local clock gating is controlled by idle_detector
                                                       1: local clock gating is disabled (clock is ON) */
        unsigned int  reserved     : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_force_clk_on_START  (0)
#define SOC_ISP_STREAM_ROUTER_FORCE_CLK_ON_CFG_force_clk_on_END    (0)






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

#endif /* end of soc_isp_stream_router_interface.h */
