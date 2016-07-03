

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FBDRAW_INTERFACE_H__
#define __SOC_ISP_FBDRAW_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) FBDRAW
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBDRAW_FBD_CFG1_UNION */
#define SOC_ISP_FBDRAW_FBD_CFG1_ADDR(base)            ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBDRAW_FBD_CFG2_UNION */
#define SOC_ISP_FBDRAW_FBD_CFG2_ADDR(base)            ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBDRAW_FBD_STATUS_UNION */
#define SOC_ISP_FBDRAW_FBD_STATUS_ADDR(base)          ((base) + (0x0008))

/* 寄存器说明：Crop Left-Right
   位域定义UNION结构:  SOC_ISP_FBDRAW_CROPLR_UNION */
#define SOC_ISP_FBDRAW_CROPLR_ADDR(base)              ((base) + (0x0010))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_CFG_UNION */
#define SOC_ISP_FBDRAW_VP_RD_CFG_ADDR(base)           ((base) + (0x14))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_LWG_UNION */
#define SOC_ISP_FBDRAW_VP_RD_LWG_ADDR(base)           ((base) + (0x18))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_FHG_UNION */
#define SOC_ISP_FBDRAW_VP_RD_FHG_ADDR(base)           ((base) + (0x1C))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_AXI_FS_UNION */
#define SOC_ISP_FBDRAW_VP_RD_AXI_FS_ADDR(base)        ((base) + (0x20))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_AXI_LINE_UNION */
#define SOC_ISP_FBDRAW_VP_RD_AXI_LINE_ADDR(base)      ((base) + (0x24))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_FBDRAW_VP_RD_PREFETCH_UNION */
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_ADDR(base)      ((base) + (0x28))





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
                     (1/1) FBDRAW
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_FBD_CFG1_UNION
 结构说明  : FBD_CFG1 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass       : 1;  /* bit[0-0]  : Bypass:
                                                        0: the module is active
                                                        1: the module is bypassed */
        unsigned int  reserved_0   : 1;  /* bit[1-1]  :  */
        unsigned int  pix_size     : 2;  /* bit[2-3]  : 0: 10bits
                                                        others: 12bits */
        unsigned int  reserved_1   : 4;  /* bit[4-7]  :  */
        unsigned int  extra_budget : 6;  /* bit[8-13] : extra budget for encoded bitstream in D64 */
        unsigned int  reserved_2   : 2;  /* bit[14-15]:  */
        unsigned int  line_width   : 13; /* bit[16-28]: Line width of the uncompressed input frame, must be even.
                                                        Line width-1 (max = 5360-1) */
        unsigned int  reserved_3   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBDRAW_FBD_CFG1_UNION;
#endif
#define SOC_ISP_FBDRAW_FBD_CFG1_bypass_START        (0)
#define SOC_ISP_FBDRAW_FBD_CFG1_bypass_END          (0)
#define SOC_ISP_FBDRAW_FBD_CFG1_pix_size_START      (2)
#define SOC_ISP_FBDRAW_FBD_CFG1_pix_size_END        (3)
#define SOC_ISP_FBDRAW_FBD_CFG1_extra_budget_START  (8)
#define SOC_ISP_FBDRAW_FBD_CFG1_extra_budget_END    (13)
#define SOC_ISP_FBDRAW_FBD_CFG1_line_width_START    (16)
#define SOC_ISP_FBDRAW_FBD_CFG1_line_width_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_FBD_CFG2_UNION
 结构说明  : FBD_CFG2 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  step_size      : 7;  /* bit[0-6]  : step size between RST markers (in number of segment = 64 pixels) and 0< step_size*64 <= line_width. */
        unsigned int  reserved_0     : 1;  /* bit[7]    :  */
        unsigned int  nb_rstmkr      : 6;  /* bit[8-13] : Number of RST marker.
                                                          Firmware should compute this parameter as follows: 1 + ceil ((line_width+1) / (step_size<<6))
                                                          MAX:
                                                          35 if supporting line up to 5360
                                                          21 if supporting line up to 2304 */
        unsigned int  reserved_1     : 2;  /* bit[14-15]:  */
        unsigned int  encoding_width : 13; /* bit[16-28]: Number of pixels to be encoded per RST Marker=encodingwidth +1.
                                                          Must be even and step_size*64 <= encoding_width+1 <= line_width+1. */
        unsigned int  reserved_2     : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBDRAW_FBD_CFG2_UNION;
#endif
#define SOC_ISP_FBDRAW_FBD_CFG2_step_size_START       (0)
#define SOC_ISP_FBDRAW_FBD_CFG2_step_size_END         (6)
#define SOC_ISP_FBDRAW_FBD_CFG2_nb_rstmkr_START       (8)
#define SOC_ISP_FBDRAW_FBD_CFG2_nb_rstmkr_END         (13)
#define SOC_ISP_FBDRAW_FBD_CFG2_encoding_width_START  (16)
#define SOC_ISP_FBDRAW_FBD_CFG2_encoding_width_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_FBD_STATUS_UNION
 结构说明  : FBD_STATUS 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_error : 1;  /* bit[0-0] : default is 0. In case the FBD hardware detects the stream is corrupted, it stream_error is asserted high. It is the FW responsibility to clear this bit */
        unsigned int  rstmkr_error : 1;  /* bit[1-1] : 1: indicates that at least one restart marker is corrupted,
                                                       0: no errors on restart markers */
        unsigned int  replica_flag : 1;  /* bit[2-2] : 1: indicates that at least one line has not been compressed in the allocated budget, and that some pixels at the end of the current line are replicated. */
        unsigned int  reserved     : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_FBDRAW_FBD_STATUS_UNION;
#endif
#define SOC_ISP_FBDRAW_FBD_STATUS_stream_error_START  (0)
#define SOC_ISP_FBDRAW_FBD_STATUS_stream_error_END    (0)
#define SOC_ISP_FBDRAW_FBD_STATUS_rstmkr_error_START  (1)
#define SOC_ISP_FBDRAW_FBD_STATUS_rstmkr_error_END    (1)
#define SOC_ISP_FBDRAW_FBD_STATUS_replica_flag_START  (2)
#define SOC_ISP_FBDRAW_FBD_STATUS_replica_flag_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_CROPLR_UNION
 结构说明  : CROPLR 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: Crop Left-Right
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cleft    : 13; /* bit[0-12] : if bypass = 0:
                                                    Crop left (can be odd or even)
                                                    Cleft must be < ((nb_rstmkr1)*step_size*64)+encoding_width+1 AND 
                                                    Cleft must be < line_width+1
                                                    if bypass = 1:
                                                    cleft + vprd_line_size + 1 <= 8191 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_FBDRAW_CROPLR_UNION;
#endif
#define SOC_ISP_FBDRAW_CROPLR_cleft_START     (0)
#define SOC_ISP_FBDRAW_CROPLR_cleft_END       (12)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_CFG_UNION
 结构说明  : VP_RD_CFG 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format    : 3;  /* bit[0-2] : Pixel formats supported (only for bypass)
                                                               "0:2->1PF8:1PF12"
                                                               4->2PF8 (YUV422)
                                                               Others -> not supported */
        unsigned int  reserved_0           : 1;  /* bit[3]   :  */
        unsigned int  vprd_pixel_expansion : 1;  /* bit[4]   : Pixel expansion (only for bypass)
                                                               0: no expansion
                                                               1: expansion on 16 bits */
        unsigned int  reserved_1           : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_CFG_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_CFG_vprd_pixel_format_START     (0)
#define SOC_ISP_FBDRAW_VP_RD_CFG_vprd_pixel_format_END       (2)
#define SOC_ISP_FBDRAW_VP_RD_CFG_vprd_pixel_expansion_START  (4)
#define SOC_ISP_FBDRAW_VP_RD_CFG_vprd_pixel_expansion_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_LWG_UNION
 结构说明  : VP_RD_LWG 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size : 13; /* bit[0-12] : Even number of pixels per line to fetch (up to 8191 pixels)
                                                          vprd_line_size+1 = number of pixels, must be even.
                                                          If bypass = 0: 
                                                          value= min[floor(Cleft/step_size*64),(nb_rstmkr-1)]
                                                          
                                                          (Cleft+vprd_line_size+1)<=(encoding_width+1) + value*step_size*64
                                                          if bypass = 1:
                                                          cleft + vprd_line_size + 1 <= 8191 */
        unsigned int  reserved       : 19; /* bit[13-31]: reserved */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_LWG_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_LWG_vprd_line_size_START  (0)
#define SOC_ISP_FBDRAW_VP_RD_LWG_vprd_line_size_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_FHG_UNION
 结构说明  : VP_RD_FHG 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size : 12; /* bit[0-11] : number of lines per frame to fetch(up to 4096 lines)
                                                           vprd_frame_size+1 = number of lines and vprd_frame_size+1 >= 2 */
        unsigned int  reserved        : 20; /* bit[12-31]: reserved */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_FHG_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_FHG_vprd_frame_size_START  (0)
#define SOC_ISP_FBDRAW_VP_RD_FHG_vprd_frame_size_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_AXI_FS_UNION
 结构说明  : VP_RD_AXI_FS 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved             : 4;  /* bit[0-3] : reserved */
        unsigned int  vprd_axi_frame_start : 28; /* bit[4-31]: Start address of the frame (in 16 bytes boundary).
                                                               Since we are 128-bits, the 4 lowest bits on the AXI address are always 0. */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_AXI_FS_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_AXI_FS_vprd_axi_frame_start_START  (4)
#define SOC_ISP_FBDRAW_VP_RD_AXI_FS_vprd_axi_frame_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_AXI_LINE_UNION
 结构说明  : VP_RD_AXI_LINE 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride : 10; /* bit[0-9]  : Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)
                                                            0: NOT SUPPORTED
                                                            1: 2*16 bytes
                                                            …
                                                            1023 : 1024*16 bytes */
        unsigned int  reserved         : 22; /* bit[10-31]: reserved */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_AXI_LINE_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_AXI_LINE_vprd_line_stride_START  (0)
#define SOC_ISP_FBDRAW_VP_RD_AXI_LINE_vprd_line_stride_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_FBDRAW_VP_RD_PREFETCH_UNION
 结构说明  : VP_RD_PREFETCH 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0       : 7;  /* bit[0-6]  : configurable index ID 0 */
        unsigned int  reserved_0           : 1;  /* bit[7]    :  */
        unsigned int  vprd_index_id1       : 7;  /* bit[8-14] : configurable index ID 1 */
        unsigned int  reserved_1           : 1;  /* bit[15]   :  */
        unsigned int  vprd_stream_id       : 6;  /* bit[16-21]: configurable stream ID */
        unsigned int  reserved_2           : 9;  /* bit[22-30]:  */
        unsigned int  vprd_prefetch_bypass : 1;  /* bit[31]   : Enables to bypass the prefetch mechanism.
                                                                0: prefetch functionality is enabled
                                                                1: prefetch functionality is bypassed (Stream ID is always stream_id0) */
    } reg;
} SOC_ISP_FBDRAW_VP_RD_PREFETCH_UNION;
#endif
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_index_id0_START        (0)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_index_id0_END          (6)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_index_id1_START        (8)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_index_id1_END          (14)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_stream_id_START        (16)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_stream_id_END          (21)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_prefetch_bypass_START  (31)
#define SOC_ISP_FBDRAW_VP_RD_PREFETCH_vprd_prefetch_bypass_END    (31)






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

#endif /* end of soc_isp_fbdraw_interface.h */
