

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

/* 寄存器说明：
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
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_0_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_ADDR(base)   ((base) + (0x20))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_ADDR(base) ((base) + (0x24))

/* 寄存器说明：Reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_1_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_ADDR(base)   ((base) + (0x28))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_ADDR(base) ((base) + (0x2c))

/* 寄存器说明：Reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_2_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_ADDR(base)   ((base) + (0x30))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_ADDR(base) ((base) + (0x34))

/* 寄存器说明：Reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_6_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_ADDR(base)   ((base) + (0x50))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_ADDR(base) ((base) + (0x54))

/* 寄存器说明：Reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_7_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_ADDR(base)   ((base) + (0x58))

/* 寄存器说明：Min space reformatter configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_ADDR(base) ((base) + (0x5c))

/* 寄存器说明：End Of Line counter interruopt event configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_EOL_CNT_UNION */
#define SOC_ISP_STREAM_ROUTER_EOL_CNT_ADDR(base)      ((base) + (0x60))

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

/* 寄存器说明：used to configure the sensor (Height, Width, Start/Stop)
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_UNION */
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_ADDR(base, NumGen_Range)  ((base) + (0x140+0x10*(NumGen_Range)))

/* 寄存器说明：used to control the speed of the sensor generator (PCLK, blanking)
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_UNION */
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_ADDR(base, NumGen_Range)  ((base) + (0x144+0x10*(NumGen_Range)))

/* 寄存器说明：used to control the pixel data
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_UNION */
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_ADDR(base, NumGen_Range)  ((base) + (0x148+0x10*(NumGen_Range)))

/* 寄存器说明：Pixfrag extraction kernel configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_UNION */
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_ADDR(base) ((base) + (0x200))

/* 寄存器说明：Pixfrag extraction position
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_UNION */
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_ADDR(base, NumExtract0_Range)  ((base) + (0x204+0x4*(NumExtract0_Range)))

/* 寄存器说明：Pixfrag extraction kernel configuration
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_UNION */
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_ADDR(base) ((base) + (0x290))

/* 寄存器说明：Pixfrag extraction position
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_UNION */
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_ADDR(base, NumExtract1_Range)  ((base) + (0x294+0x4*(NumExtract1_Range)))

/* 寄存器说明：Debug information related to the reformatters
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_ADDR(base) ((base) + (0x320))

/* 寄存器说明：Debug information related to the reformatters
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_ADDR(base) ((base) + (0x324))

/* 寄存器说明：Debug information related to the reformatters
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_ADDR(base) ((base) + (0x328))

/* 寄存器说明：Debug information related to the reformatters
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_ADDR(base) ((base) + (0x338))

/* 寄存器说明：Debug information related to the reformatters
   位域定义UNION结构:  SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_UNION */
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_ADDR(base) ((base) + (0x33c))





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
 结构名    : SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION
 结构说明  : CSIFILTER_GO 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_go : 8;  /* bit[0-7] : Go bits (Write only). 
                                                    This register allows to control the frames which need to be transmitted. These bits are write only 1.
                                                    0: no effect
                                                    1: implies that next incoming frame will have to be transmitted
                                                    The software must re-arm the go bit for every frame and can do it as soon as the first line of the current frame is received. 
                                                    If a current frame is already under processing, writing into this bit, implies that next frame will have to be processed also.
                                                    We have 8 bits since 4 filters on every of the 2 CSI cameras.
                                                     7:4 : CSIB camera - filters 3 (bit 7), 2 (bit 6),1 (bit 5),0 (bit 4) 
                                                     3:0 : CSIA camera - filters 3 (bit 3), 2 (bit 2),1 (bit 1),0 (bit 0)  */
        unsigned int  reserved  : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_START  (0)
#define SOC_ISP_STREAM_ROUTER_CSIFILTER_GO_filter_go_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION
 结构说明  : PRESSURE_START 寄存器结构定义。地址偏移量:0x10，初值:0x0000C0C0，宽度:32
 寄存器说明: Pressure start configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pressure_threshold_start_a : 8;  /* bit[0-7]  : camera A is expected to work up to 6Gb/s. 
                                                                      Priority request generated if the fifo level > 2*threshold
                                                                      Max threshold : 255 (= fifo level higher than 510)  */
        unsigned int  pressure_threshold_start_b : 8;  /* bit[8-15] : camera B is expected to work up to 6Gb/s. 
                                                                      Max threshold : 255 */
        unsigned int  reserved                   : 15; /* bit[16-30]: reserved */
        unsigned int  pressure_enable            : 1;  /* bit[31]   : Enable the pressure_bit request generation based on threshold registers */
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_START_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_a_END    (7)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_START  (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_threshold_start_b_END    (15)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_START             (31)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_START_pressure_enable_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION
 结构说明  : PRESSURE_STOP 寄存器结构定义。地址偏移量:0x14，初值:0x00004040，宽度:32
 寄存器说明: Pressure stop configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pressure_threshold_stop_a : 8;  /* bit[0-7]  : Camera A
                                                                     Priority request stopped if the fifo level < 2*threshold_stop
                                                                     Max threshold : 255 */
        unsigned int  pressure_threshold_stop_b : 8;  /* bit[8-15] : Camera B
                                                                     Priority request stopped if the fifo level < 2*threshold_stop
                                                                     Max threshold : 255 */
        unsigned int  reserved                  : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_a_END    (7)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_START  (8)
#define SOC_ISP_STREAM_ROUTER_PRESSURE_STOP_pressure_threshold_stop_b_END    (15)


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
        unsigned int  reserved_2         : 11; /* bit[21-31]: reserved */
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
        unsigned int  reserved_0         : 16; /* bit[0-15] : reserved */
        unsigned int  idr_input_stream_6 : 4;  /* bit[16-19]:  */
        unsigned int  idr_enable_6       : 1;  /* bit[20]   :  */
        unsigned int  reserved_1         : 3;  /* bit[21-23]: reserved */
        unsigned int  idr_input_stream_7 : 4;  /* bit[24-27]:  */
        unsigned int  idr_enable_7       : 1;  /* bit[28]   :  */
        unsigned int  reserved_2         : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_START  (16)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_6_END    (19)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_START        (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_6_END          (20)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_START  (24)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_input_stream_7_END    (27)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_START        (28)
#define SOC_ISP_STREAM_ROUTER_ID_ROUTER_1_idr_enable_7_END          (28)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_0_UNION
 结构说明  : REFORMAT_0 寄存器结构定义。地址偏移量:0x20，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines_0     : 13; /* bit[0-12] : Number of lines in the picture
                                                                    0: 1 line
                                                                    1: 2 line
                                                                    …
                                                                    0x1FFF: 8192 lines */
        unsigned int  reformat_pixel_reorder_0 : 3;  /* bit[13-15]: Pixel reordering functionality: 0x0,0x2,0x3,0x4 follow the CSI2 spec.
                                                                    0x0: 8 bit format - CSI2 compatible (first pixel starting on LSByte). Used for RAW8, Generic 8 bit
                                                                    0x1: 8 bit format - non-CSI2 compatible (first pixel starting on MSByte). Used for YUV422 8-bit.
                                                                    0x2: 10 bit format (first pixel starting on LSB). Used for YUV422 10-bit, RAW10
                                                                    0x3: 12 bit format (first pixel starting on LSB). Used for RAW12
                                                                    0x4: 14 bit format (first pixel starting on LSB). Used for RAW14 */
        unsigned int  reformat_num_pixels_0    : 13; /* bit[16-28]: Number of pixfrags per line
                                                                    0: 1 pixfrag
                                                                    1: 2 pixfrag
                                                                    …
                                                                    0x1FFF: 8192 pixfrags
                                                                    [note] should be even[end] */
        unsigned int  reserved                 : 2;  /* bit[29-30]: reserved */
        unsigned int  reformat_enable_0        : 1;  /* bit[31]   : Enable the reformat functionality
                                                                    1: enabled
                                                                    0: bypassed */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_num_lines_0_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_num_lines_0_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_pixel_reorder_0_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_pixel_reorder_0_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_num_pixels_0_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_num_pixels_0_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_enable_0_START         (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_0_reformat_enable_0_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_UNION
 结构说明  : REFORMAT_MINSPACE_0 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space_0 : 6;  /* bit[0-5] : Minimum space between 2 frames is min_vertical_space*num_pixels clock cycles
                                                                        0x0: no space allowed
                                                                        0x1: one line space minimum (in clock cycles)
                                                                        …
                                                                        0x3F: 63 lines space minimum */
        unsigned int  reserved                      : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_reformat_min_vertical_space_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_0_reformat_min_vertical_space_0_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_1_UNION
 结构说明  : REFORMAT_1 寄存器结构定义。地址偏移量:0x28，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines_1     : 13; /* bit[0-12] :  */
        unsigned int  reformat_pixel_reorder_1 : 3;  /* bit[13-15]:  */
        unsigned int  reformat_num_pixels_1    : 13; /* bit[16-28]:  */
        unsigned int  reserved                 : 2;  /* bit[29-30]:  */
        unsigned int  reformat_enable_1        : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_num_lines_1_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_num_lines_1_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_pixel_reorder_1_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_pixel_reorder_1_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_num_pixels_1_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_num_pixels_1_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_enable_1_START         (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_1_reformat_enable_1_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_UNION
 结构说明  : REFORMAT_MINSPACE_1 寄存器结构定义。地址偏移量:0x2c，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space_1 : 6;  /* bit[0-5] :  */
        unsigned int  reserved                      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_reformat_min_vertical_space_1_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_1_reformat_min_vertical_space_1_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_2_UNION
 结构说明  : REFORMAT_2 寄存器结构定义。地址偏移量:0x30，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines_2     : 13; /* bit[0-12] :  */
        unsigned int  reformat_pixel_reorder_2 : 3;  /* bit[13-15]:  */
        unsigned int  reformat_num_pixels_2    : 13; /* bit[16-28]:  */
        unsigned int  reserved                 : 2;  /* bit[29-30]:  */
        unsigned int  reformat_enable_2        : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_2_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_num_lines_2_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_num_lines_2_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_pixel_reorder_2_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_pixel_reorder_2_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_num_pixels_2_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_num_pixels_2_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_enable_2_START         (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_2_reformat_enable_2_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_UNION
 结构说明  : REFORMAT_MINSPACE_2 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space_2 : 6;  /* bit[0-5] :  */
        unsigned int  reserved                      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_reformat_min_vertical_space_2_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_2_reformat_min_vertical_space_2_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_6_UNION
 结构说明  : REFORMAT_6 寄存器结构定义。地址偏移量:0x50，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines_6     : 13; /* bit[0-12] :  */
        unsigned int  reformat_pixel_reorder_6 : 3;  /* bit[13-15]:  */
        unsigned int  reformat_num_pixels_6    : 13; /* bit[16-28]:  */
        unsigned int  reserved                 : 2;  /* bit[29-30]:  */
        unsigned int  reformat_enable_6        : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_6_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_num_lines_6_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_num_lines_6_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_pixel_reorder_6_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_pixel_reorder_6_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_num_pixels_6_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_num_pixels_6_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_enable_6_START         (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_6_reformat_enable_6_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_UNION
 结构说明  : REFORMAT_MINSPACE_6 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space_6 : 6;  /* bit[0-5] :  */
        unsigned int  reserved                      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_reformat_min_vertical_space_6_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_6_reformat_min_vertical_space_6_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_7_UNION
 结构说明  : REFORMAT_7 寄存器结构定义。地址偏移量:0x58，初值:0x1FFF1FFF，宽度:32
 寄存器说明: Reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_num_lines_7     : 13; /* bit[0-12] :  */
        unsigned int  reformat_pixel_reorder_7 : 3;  /* bit[13-15]:  */
        unsigned int  reformat_num_pixels_7    : 13; /* bit[16-28]:  */
        unsigned int  reserved                 : 2;  /* bit[29-30]:  */
        unsigned int  reformat_enable_7        : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_7_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_num_lines_7_START      (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_num_lines_7_END        (12)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_pixel_reorder_7_START  (13)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_pixel_reorder_7_END    (15)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_num_pixels_7_START     (16)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_num_pixels_7_END       (28)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_enable_7_START         (31)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_7_reformat_enable_7_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_UNION
 结构说明  : REFORMAT_MINSPACE_7 寄存器结构定义。地址偏移量:0x5c，初值:0x00000000，宽度:32
 寄存器说明: Min space reformatter configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_min_vertical_space_7 : 6;  /* bit[0-5] :  */
        unsigned int  reserved                      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_reformat_min_vertical_space_7_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_MINSPACE_7_reformat_min_vertical_space_7_END    (5)


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
                                                          0: from DPCM 0
                                                          1: from DPCM 1
                                                          2: from Formater 2
                                                          3: NA
                                                          4: NA
                                                          5: NA
                                                          6: NA
                                                          7: NA
                                                          8: from pixfrag extract 0 module
                                                          9: NA
                                                          10: NA
                                                          11: NA
                                                          12: NA
                                                          13: Crop 0
                                                          14: Crop 1
                                                          15: from pixfrag extract 1 module */
        unsigned int  vpr_enable_0   : 1;  /* bit[4]    : Output #0:Enables input_vp_0 programmation
                                                          [note] vp_enable_0 should be programed 0 before you change another channel
                                                          [end] */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : reserved */
        unsigned int  vpr_input_vp_1 : 4;  /* bit[8-11] :  */
        unsigned int  vpr_enable_1   : 1;  /* bit[12]   :  */
        unsigned int  reserved_1     : 11; /* bit[13-23]: reserved */
        unsigned int  vpr_input_vp_3 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_3   : 1;  /* bit[28]   :  */
        unsigned int  reserved_2     : 3;  /* bit[29-31]: reserved */
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
        unsigned int  reserved_0     : 11; /* bit[5-15] : reserved */
        unsigned int  vpr_input_vp_6 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_6   : 1;  /* bit[20]   :  */
        unsigned int  reserved_1     : 3;  /* bit[21-23]: reserved */
        unsigned int  vpr_input_vp_7 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_7   : 1;  /* bit[28]   :  */
        unsigned int  reserved_2     : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_START  (0)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_4_END    (3)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_START    (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_4_END      (4)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_6_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_6_END      (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_START  (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_input_vp_7_END    (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_START    (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_1_vpr_enable_7_END      (28)


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
        unsigned int  reserved_0      : 16; /* bit[0-15] : reserved */
        unsigned int  vpr_input_vp_14 : 4;  /* bit[16-19]:  */
        unsigned int  vpr_enable_14   : 1;  /* bit[20]   :  */
        unsigned int  reserved_1      : 3;  /* bit[21-23]: reserved */
        unsigned int  vpr_input_vp_15 : 4;  /* bit[24-27]:  */
        unsigned int  vpr_enable_15   : 1;  /* bit[28]   :  */
        unsigned int  reserved_2      : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_START  (16)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_14_END    (19)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_START    (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_14_END      (20)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_15_START  (24)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_input_vp_15_END    (27)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_15_START    (28)
#define SOC_ISP_STREAM_ROUTER_VP_ROUTER_3_vpr_enable_15_END      (28)


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
        unsigned int  reserved_0: 1;  /* bit[2]   :  */
        unsigned int  fe2_out  : 1;  /* bit[3]   :  */
        unsigned int  fe1_out  : 1;  /* bit[4]   : bit used to select how the data must be sent out on output (FE1, FE2, dma1. dma2, dma3)
                                                   0: 1PF
                                                   1: format unchanged */
        unsigned int  reserved_1: 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_START  (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma3_out_END    (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_START  (1)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_CONVERT_dma2_out_END    (1)
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
                                                       010: NA
                                                       011: NA
                                                       100: NA
                                                       101: NA
                                                       110: NA
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
 结构说明  : BP_SOURCE 寄存器结构定义。地址偏移量:0x98，初值:0x00000004，宽度:32
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
                                                      2: NA
                                                      3: NA  */
        unsigned int  bp_source_b : 2;  /* bit[2-3] : see bp_source_a */
        unsigned int  reserved    : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_STREAM_ROUTER_BP_SOURCE_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_START  (0)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_a_END    (1)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_START  (2)
#define SOC_ISP_STREAM_ROUTER_BP_SOURCE_bp_source_b_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_DFS_CFG_UNION
 结构说明  : DFS_CFG 寄存器结构定义。地址偏移量:0x100，初值:0xFF8003FF，宽度:32
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
                                                                0x3FF: wait 1024 clock cycles */
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
 结构名    : SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_UNION
 结构说明  : SENSORGEN_CFG 寄存器结构定义。地址偏移量:0x140+0x10*(NumGen_Range)，初值:0x02CF013F，宽度:32
 寄存器说明: used to configure the sensor (Height, Width, Start/Stop)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sensorgen_hsize : 12; /* bit[0-11] : Number of 32-bits data per line (horizontal)
                                                           0: 1 32-bits
                                                           …
                                                           0x7FF: 4096 32-bits */
        unsigned int  reserved_0      : 4;  /* bit[12-15]:  */
        unsigned int  sensorgen_vsize : 13; /* bit[16-28]: Number of lines in the frame (vertical)
                                                           0: 1 line
                                                           …
                                                           0xFFF: 8192 lines */
        unsigned int  reserved_1      : 1;  /* bit[29]   :  */
        unsigned int  sensorgen_mode  : 1;  /* bit[30]   : Used to configure the way the 32 bits data is sent.
                                                           0: fixed pattern using SENSORGEN_DATA
                                                           1: incremental mode, 32-bits data starting from sensorgen_data[15:0] and incremented by sensorgen_data[23:16]. In this mode, the counter is only reseted to sensorgen_data[15:0] at frame start.  */
        unsigned int  sensorgen_start : 1;  /* bit[31]   : The software must set the bit to 1 to start the emulated sensor interface.
                                                           The software must clear the bit to 0 to stop the emulated sensor interface.
                                                           Note that, the harware will start/stop immediately based on SW decision.
                                                           When the software clears the bit, then the harware stops immediatly, and get back to idle state (VVALID, DVALID to 0). */
    } reg;
} SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_hsize_START  (0)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_hsize_END    (11)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_vsize_START  (16)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_vsize_END    (28)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_mode_START   (30)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_mode_END     (30)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_start_START  (31)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CFG_sensorgen_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_UNION
 结构说明  : SENSORGEN_CTRL 寄存器结构定义。地址偏移量:0x144+0x10*(NumGen_Range)，初值:0x00000000，宽度:32
 寄存器说明: used to control the speed of the sensor generator (PCLK, blanking)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sensorgen_dataen_pattern : 16; /* bit[0-15] : Pattern to use to generate the traffic.
                                                                    Note that the configuration of this pattern depends on the targeted Pixel clock as well as the pixel type and also impacts the vertical blanking duration.
                                                                    C-code is provided into the HLD.
                                                                    The bits are used in following order: from bit 15 to bit 0 (bit 15 is evaluated first) */
        unsigned int  sensorgen_vblanking      : 8;  /* bit[16-23]: Number of vertical blanking lines (duration is based on idigen_dataen_pattern and idi_hblanking)
                                                                    0: 2 lines
                                                                    1: 4 lines
                                                                    2: 6 lines
                                                                    ….
                                                                    255: 512 lines */
        unsigned int  sensorgen_hblanking      : 8;  /* bit[24-31]: Number of horizontal blanking clock cycles (starting as soon as the number of generated data is completed)
                                                                    0: 2 cycles
                                                                    1: 4 cycles
                                                                    2: 6 cycles
                                                                    ….
                                                                    255: 512 cycles */
    } reg;
} SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_dataen_pattern_START  (0)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_dataen_pattern_END    (15)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_vblanking_START       (16)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_vblanking_END         (23)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_hblanking_START       (24)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_CTRL_sensorgen_hblanking_END         (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_UNION
 结构说明  : SENSORGEN_DATA 寄存器结构定义。地址偏移量:0x148+0x10*(NumGen_Range)，初值:0x04030201，宽度:32
 寄存器说明: used to control the pixel data
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sensorgen_data : 32; /* bit[0-31]: IDI pixel data.
                                                         If sensorgen_mode=0: csi_data[31:0] = sensorgen_data (fixed pattern)
                                                         If sensorgen_mode=1: csi_data[31:0] is resetted to sensorgen_data[15:0] at frame start, then incremented by sensorgen_data[23:16] at every valid csi_data.  */
    } reg;
} SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_sensorgen_data_START  (0)
#define SOC_ISP_STREAM_ROUTER_SENSORGEN_DATA_sensorgen_data_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_UNION
 结构说明  : PIXFRAG_EXTRACT0_CFG 寄存器结构定义。地址偏移量:0x200，初值:0x00003FFF，宽度:32
 寄存器说明: Pixfrag extraction kernel configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extract0_vsize : 8;  /* bit[0-7]  : Vertical Kernel size:
                                                          0: 1 line
                                                          1: 2 lines
                                                          …
                                                          255: 256 lines */
        unsigned int  extract0_hsize : 6;  /* bit[8-13] : Horizontal Kernel size:
                                                          0: 1 pixel
                                                          1: 2 pixels
                                                          …
                                                          63: 64 pixels */
        unsigned int  reserved       : 17; /* bit[14-30]:  */
        unsigned int  extract0_mode  : 1;  /* bit[31]   : mode of operation
                                                          0: single data stream generated (1 frame of 1 line)
                                                          1: multiple lines generated - based on h_end (1 frame of N lines)  */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_vsize_START  (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_vsize_END    (7)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_hsize_START  (8)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_hsize_END    (13)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_mode_START   (31)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_CFG_extract0_mode_END     (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_UNION
 结构说明  : PIXFRAG_EXTRACT0_POS 寄存器结构定义。地址偏移量:0x204+0x4*(NumExtract0_Range)，初值:0x00000000，宽度:32
 寄存器说明: Pixfrag extraction position
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extract0_vpos       : 8;  /* bit[0-7]  : position Y (vertical) */
        unsigned int  extract0_hpos       : 6;  /* bit[8-13] : position X (horizontal) */
        unsigned int  reserved            : 17; /* bit[14-30]:  */
        unsigned int  extract0_pos_enable : 1;  /* bit[31]   : enable pixfrag extraction from location (extract_pos_x,extract_pos_y) */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_vpos_START        (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_vpos_END          (7)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_hpos_START        (8)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_hpos_END          (13)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_pos_enable_START  (31)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT0_POS_extract0_pos_enable_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_UNION
 结构说明  : PIXFRAG_EXTRACT1_CFG 寄存器结构定义。地址偏移量:0x290，初值:0x00003FFF，宽度:32
 寄存器说明: Pixfrag extraction kernel configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extract1_vsize : 8;  /* bit[0-7]  :  */
        unsigned int  extract1_hsize : 6;  /* bit[8-13] :  */
        unsigned int  reserved       : 17; /* bit[14-30]:  */
        unsigned int  extract1_mode  : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_vsize_START  (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_vsize_END    (7)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_hsize_START  (8)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_hsize_END    (13)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_mode_START   (31)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_CFG_extract1_mode_END     (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_UNION
 结构说明  : PIXFRAG_EXTRACT1_POS 寄存器结构定义。地址偏移量:0x294+0x4*(NumExtract1_Range)，初值:0x00000000，宽度:32
 寄存器说明: Pixfrag extraction position
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extract1_vpos       : 8;  /* bit[0-7]  :  */
        unsigned int  extract1_hpos       : 6;  /* bit[8-13] :  */
        unsigned int  reserved            : 17; /* bit[14-30]:  */
        unsigned int  extract1_pos_enable : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_vpos_START        (0)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_vpos_END          (7)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_hpos_START        (8)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_hpos_END          (13)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_pos_enable_START  (31)
#define SOC_ISP_STREAM_ROUTER_PIXFRAG_EXTRACT1_POS_extract1_pos_enable_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_UNION
 结构说明  : REFORMAT_DEBUG_0 寄存器结构定义。地址偏移量:0x320，初值:0x00000000，宽度:32
 寄存器说明: Debug information related to the reformatters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_debug_0 : 32; /* bit[0-31]: debug information from the reformatters */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_reformat_debug_0_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_0_reformat_debug_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_UNION
 结构说明  : REFORMAT_DEBUG_1 寄存器结构定义。地址偏移量:0x324，初值:0x00000000，宽度:32
 寄存器说明: Debug information related to the reformatters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_debug_1 : 32; /* bit[0-31]: debug information from the reformatters */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_reformat_debug_1_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_1_reformat_debug_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_UNION
 结构说明  : REFORMAT_DEBUG_2 寄存器结构定义。地址偏移量:0x328，初值:0x00000000，宽度:32
 寄存器说明: Debug information related to the reformatters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_debug_2 : 32; /* bit[0-31]: debug information from the reformatters */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_reformat_debug_2_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_2_reformat_debug_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_UNION
 结构说明  : REFORMAT_DEBUG_6 寄存器结构定义。地址偏移量:0x338，初值:0x00000000，宽度:32
 寄存器说明: Debug information related to the reformatters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_debug_6 : 32; /* bit[0-31]: debug information from the reformatters */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_reformat_debug_6_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_6_reformat_debug_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_UNION
 结构说明  : REFORMAT_DEBUG_7 寄存器结构定义。地址偏移量:0x33c，初值:0x00000000，宽度:32
 寄存器说明: Debug information related to the reformatters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reformat_debug_7 : 32; /* bit[0-31]: debug information from the reformatters */
    } reg;
} SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_UNION;
#endif
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_reformat_debug_7_START  (0)
#define SOC_ISP_STREAM_ROUTER_REFORMAT_DEBUG_7_reformat_debug_7_END    (31)






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
