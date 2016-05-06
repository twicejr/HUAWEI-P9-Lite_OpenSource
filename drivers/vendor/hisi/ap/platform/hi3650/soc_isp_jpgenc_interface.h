/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_jpgenc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:06
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_JPGENC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_JPGENC_INTERFACE_H__
#define __SOC_ISP_JPGENC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) JPGENC
 ****************************************************************************/
/* 寄存器说明：Encode enable.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ENCODE_UNION */
#define SOC_ISP_JPGENC_JPE_ENCODE_ADDR(base)          ((base) + (0x0004))

/* 寄存器说明：SW force update update.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_INIT_UNION */
#define SOC_ISP_JPGENC_JPE_INIT_ADDR(base)            ((base) + (0x0008))

/* 寄存器说明：JPEG codec horizontal image size for encoding.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_UNION */
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_ADDR(base)     ((base) + (0x0018))

/* 寄存器说明：JPEG codec vertical image size for encoding.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_UNION */
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_ADDR(base)     ((base) + (0x001C))

/* 寄存器说明：JPEG picture encoding format.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_PIC_FORMAT_UNION */
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_ADDR(base)      ((base) + (0x0020))

/* 寄存器说明：restart marker insertion register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_UNION */
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_ADDR(base) ((base) + (0x0024))

/* 寄存器说明：Q-table selector 0, quant table for Y component.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_UNION */
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_ADDR(base)     ((base) + (0x0028))

/* 寄存器说明：Q-table selector 1, quant table for U component.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TQ_U_SELECT_UNION */
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_ADDR(base)     ((base) + (0x002C))

/* 寄存器说明：Q-table selector 2, quant table for V component.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TQ_V_SELECT_UNION */
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_ADDR(base)     ((base) + (0x0030))

/* 寄存器说明：Huffman table selector for DC values.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_UNION */
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_ADDR(base) ((base) + (0x0034))

/* 寄存器说明：Huffman table selector for AC value.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_UNION */
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ADDR(base) ((base) + (0x0038))

/* 寄存器说明：table programming register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TABLE_DATA_UNION */
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_ADDR(base)      ((base) + (0x003C))

/* 寄存器说明：table programming select register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TABLE_ID_UNION */
#define SOC_ISP_JPGENC_JPE_TABLE_ID_ADDR(base)        ((base) + (0x0040))

/* 寄存器说明：Huffman AC table 0 length.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TAC0_LEN_UNION */
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_ADDR(base)        ((base) + (0x0044))

/* 寄存器说明：Huffman DC table 0 length.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TDC0_LEN_UNION */
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_ADDR(base)        ((base) + (0x0048))

/* 寄存器说明：Huffman AC table 1 length.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TAC1_LEN_UNION */
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_ADDR(base)        ((base) + (0x0004C))

/* 寄存器说明：Huffman DC table 1 length.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_TDC1_LEN_UNION */
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_ADDR(base)        ((base) + (0x0050))

/* 寄存器说明：encode mode.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ENCODER_MODE_UNION */
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_ADDR(base)    ((base) + (0x0060))

/* 寄存器说明：debug information register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_DEBUG_UNION */
#define SOC_ISP_JPGENC_JPE_DEBUG_ADDR(base)           ((base) + (0x0064))

/* 寄存器说明：JPEG error interrupt mask register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ERROR_IMR_UNION */
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_ADDR(base)       ((base) + (0x0068))

/* 寄存器说明：JPEG error raw interrupt status register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ERROR_RIS_UNION */
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_ADDR(base)       ((base) + (0x006C))

/* 寄存器说明：JPEG error masked interrupt status register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ERROR_MIS_UNION */
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_ADDR(base)       ((base) + (0x0070))

/* 寄存器说明：JPEG error interrupt clear regisger.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ERROR_ICR_UNION */
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_ADDR(base)       ((base) + (0x0074))

/* 寄存器说明：JPEG error interrupt set register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ERROR_ISR_UNION */
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_ADDR(base)       ((base) + (0x0078))

/* 寄存器说明：JPEG status interrupt mask register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_STATUS_IMR_UNION */
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_ADDR(base)      ((base) + (0x007C))

/* 寄存器说明：JPEG status raw interrupt status register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_STATUS_RIS_UNION */
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_ADDR(base)      ((base) + (0x0080))

/* 寄存器说明：JPEG status masked interrupt status register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_STATUS_MIS_UNION */
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_ADDR(base)      ((base) + (0x0084))

/* 寄存器说明：JPEG status interrupt clear register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_STATUS_ICR_UNION */
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_ADDR(base)      ((base) + (0x0088))

/* 寄存器说明：JPEG status interrrupt set register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_STATUS_ISR_UNION */
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_ADDR(base)      ((base) + (0x008C))

/* 寄存器说明：JPEG configuration register.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_CONFIG_UNION */
#define SOC_ISP_JPGENC_JPE_CONFIG_ADDR(base)          ((base) + (0x0090))

/* 寄存器说明：Y Buffer address.
   位域定义UNION结构:  SOC_ISP_JPGENC_ADDRESS_Y_UNION */
#define SOC_ISP_JPGENC_ADDRESS_Y_ADDR(base)           ((base) + (0x0094))

/* 寄存器说明：UV Buffer addresss.
   位域定义UNION结构:  SOC_ISP_JPGENC_ADDRESS_UV_UNION */
#define SOC_ISP_JPGENC_ADDRESS_UV_ADDR(base)          ((base) + (0x00098))

/* 寄存器说明：Address stride in bytes.
   位域定义UNION结构:  SOC_ISP_JPGENC_STRIDE_UNION */
#define SOC_ISP_JPGENC_STRIDE_ADDR(base)              ((base) + (0x009C))

/* 寄存器说明：Source Synchronization configuration.
   位域定义UNION结构:  SOC_ISP_JPGENC_SYNCCFG_UNION */
#define SOC_ISP_JPGENC_SYNCCFG_ADDR(base)             ((base) + (0x0100))

/* 寄存器说明：Picture from pipe2 Hsize.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_UNION */
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_ADDR(base)     ((base) + (0x0104))

/* 寄存器说明：Number of encoded bytes sent to video port.
   位域定义UNION结构:  SOC_ISP_JPGENC_JPG_BYTE_CNT_UNION */
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_ADDR(base)        ((base) + (0x0108))

/* 寄存器说明：Prefetch configuration.
   位域定义UNION结构:  SOC_ISP_JPGENC_PREFETCH_UNION */
#define SOC_ISP_JPGENC_PREFETCH_ADDR(base)            ((base) + (0x010C))

/* 寄存器说明：Prefetch ID configuration (Y Buffer).
   位域定义UNION结构:  SOC_ISP_JPGENC_PREFETCH_IDY0_UNION */
#define SOC_ISP_JPGENC_PREFETCH_IDY0_ADDR(base)       ((base) + (0x0110))

/* 寄存器说明：Prefetch ID configuration (Y Buffer).
   位域定义UNION结构:  SOC_ISP_JPGENC_PREFETCH_IDY1_UNION */
#define SOC_ISP_JPGENC_PREFETCH_IDY1_ADDR(base)       ((base) + (0x0114))

/* 寄存器说明：Prefetch ID configuration (UV Buffer).
   位域定义UNION结构:  SOC_ISP_JPGENC_PREFETCH_IDUV0_UNION */
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_ADDR(base)      ((base) + (0x0118))

/* 寄存器说明：Prefetch ID configuration (UV Buffer).
   位域定义UNION结构:  SOC_ISP_JPGENC_PREFETCH_IDUVY_UNION */
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_ADDR(base)      ((base) + (0x011C))

/* 寄存器说明：Number of preread MCU configuration.
   位域定义UNION结构:  SOC_ISP_JPGENC_PREREAD_UNION */
#define SOC_ISP_JPGENC_PREREAD_ADDR(base)             ((base) + (0x0120))

/* 寄存器说明：used to force the clock which is generally controlled by HW.
   位域定义UNION结构:  SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_ADDR(base)    ((base) + (0x0130))

/* 寄存器说明：debug regiser0.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_0_UNION */
#define SOC_ISP_JPGENC_DBG_0_ADDR(base)               ((base) + (0x0200))

/* 寄存器说明：debug regiser1.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_1_UNION */
#define SOC_ISP_JPGENC_DBG_1_ADDR(base)               ((base) + (0x0204))

/* 寄存器说明：debug register2.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_2_UNION */
#define SOC_ISP_JPGENC_DBG_2_ADDR(base)               ((base) + (0x0208))

/* 寄存器说明：debug register3.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_3_UNION */
#define SOC_ISP_JPGENC_DBG_3_ADDR(base)               ((base) + (0x020c))

/* 寄存器说明：debug register4.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_4_UNION */
#define SOC_ISP_JPGENC_DBG_4_ADDR(base)               ((base) + (0x0210))

/* 寄存器说明：debug register5.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_5_UNION */
#define SOC_ISP_JPGENC_DBG_5_ADDR(base)               ((base) + (0x0214))

/* 寄存器说明：debug register6.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_6_UNION */
#define SOC_ISP_JPGENC_DBG_6_ADDR(base)               ((base) + (0x0218))

/* 寄存器说明：debug register7.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_7_UNION */
#define SOC_ISP_JPGENC_DBG_7_ADDR(base)               ((base) + (0x021c))

/* 寄存器说明：debug register8.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_8_UNION */
#define SOC_ISP_JPGENC_DBG_8_ADDR(base)               ((base) + (0x0220))

/* 寄存器说明：debug register9.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_9_UNION */
#define SOC_ISP_JPGENC_DBG_9_ADDR(base)               ((base) + (0x0224))

/* 寄存器说明：debug register10.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_10_UNION */
#define SOC_ISP_JPGENC_DBG_10_ADDR(base)              ((base) + (0x0228))

/* 寄存器说明：debug register11.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_11_UNION */
#define SOC_ISP_JPGENC_DBG_11_ADDR(base)              ((base) + (0x022c))

/* 寄存器说明：debug register12.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_12_UNION */
#define SOC_ISP_JPGENC_DBG_12_ADDR(base)              ((base) + (0x0230))

/* 寄存器说明：debug register13.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_13_UNION */
#define SOC_ISP_JPGENC_DBG_13_ADDR(base)              ((base) + (0x0234))

/* 寄存器说明：debug register14.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_14_UNION */
#define SOC_ISP_JPGENC_DBG_14_ADDR(base)              ((base) + (0x0238))

/* 寄存器说明：debug register15.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_15_UNION */
#define SOC_ISP_JPGENC_DBG_15_ADDR(base)              ((base) + (0x023c))

/* 寄存器说明：debug writable register.
   位域定义UNION结构:  SOC_ISP_JPGENC_DBG_RW_0_UNION */
#define SOC_ISP_JPGENC_DBG_RW_0_ADDR(base)            ((base) + (0x0300))





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
                     (1/1) JPGENC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ENCODE_UNION
 结构说明  : JPE_ENCODE 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: Encode enable.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  encode   : 1;  /* bit[0]   : Encode enable- HW clears enable when it starts encoding.SW must set enable =1 at the end of a valid JPEG configuration 
                                                   0: encode disabled
                                                   1: encode enabled */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ENCODE_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENCODE_encode_START    (0)
#define SOC_ISP_JPGENC_JPE_ENCODE_encode_END      (0)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_INIT_UNION
 结构说明  : JPE_INIT 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: SW force update update.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jp_init  : 1;  /* bit[0]   : Shadowed registers forced update
                                                   Write 1: force update of shadowed registers, auto reset to zero after one clock cycle
                                                   Write 0: no effect */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_INIT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_INIT_jp_init_START   (0)
#define SOC_ISP_JPGENC_JPE_INIT_jp_init_END     (0)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_UNION
 结构说明  : JPE_ENC_HRIGHT1 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: JPEG codec horizontal image size for encoding.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_hright1 : 13; /* bit[0-12] : number of pixels in left input ( from pipe1) picture, must be an even number of pixels
                                                       0: no encode from left pipe 
                                                       1: 2 pixels
                                                       2N-1: 2N pixels , hsize1 = enc_hright+1
                                                       [Note]
                                                       when two pictures exist, left picture width should be 128-bit aligned which means
                                                       YUV422:hsize1[2:0]=0
                                                       YUv420:hsize1[3:0]=0
                                                       in SRAM mode,4<(enc_hright1+enc_hright2)<5376
                                                       in DRAM mode,4<(enc_hright1+enc_hright2)<8192
                                                       [end] */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_enc_hright1_START  (0)
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT1_enc_hright1_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_UNION
 结构说明  : JPE_ENC_VBOTTOM 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: JPEG codec vertical image size for encoding.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_vbottom : 13; /* bit[0-12] : JPEG codec vertical image size 
                                                       N: N+1 lines , vsize = enc_vbottom+1
                                                       [Note]
                                                       range: 2<(enc_vbottom+1)<=8192
                                                       YUV420: this field must be odd
                                                       [end] */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_enc_vbottom_START  (0)
#define SOC_ISP_JPGENC_JPE_ENC_VBOTTOM_enc_vbottom_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_PIC_FORMAT_UNION
 结构说明  : JPE_PIC_FORMAT 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: JPEG picture encoding format.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_pic_format : 3;  /* bit[0-2] : Picture format:
                                                         0: YUV422 (UYVY in DRAM)
                                                         1: YUV420 (NV12 in DRAM)
                                                         others : reserved */
        unsigned int  reserved       : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_PIC_FORMAT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_enc_pic_format_START  (0)
#define SOC_ISP_JPGENC_JPE_PIC_FORMAT_enc_pic_format_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_UNION
 结构说明  : JPE_RESTART_INTERVAL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: restart marker insertion register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  restart_interval : 16; /* bit[0-15] : Number of MCU in reset interval via host
                                                            0: no RST marker insterted
                                                            N: 1 RST marker after N encoded MCU */
        unsigned int  reserved         : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_restart_interval_START  (0)
#define SOC_ISP_JPGENC_JPE_RESTART_INTERVAL_restart_interval_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_UNION
 结构说明  : JPE_TQ_Y_SELECT 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: Q-table selector 0, quant table for Y component.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tq0_select : 2;  /* bit[0-1] : "00"=qtable 0
                                                     "01"=reserved
                                                     "10"=qtable2
                                                     "11"=reserved */
        unsigned int  reserved   : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_tq0_select_START  (0)
#define SOC_ISP_JPGENC_JPE_TQ_Y_SELECT_tq0_select_END    (1)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TQ_U_SELECT_UNION
 结构说明  : JPE_TQ_U_SELECT 寄存器结构定义。地址偏移量:0x002C，初值:0x00000001，宽度:32
 寄存器说明: Q-table selector 1, quant table for U component.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tq1_select : 2;  /* bit[0-1] : "00"=reserved
                                                     "01"=qtable1
                                                     "10"=reserved
                                                     "11"=qtable3 */
        unsigned int  reserved   : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_U_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_tq1_select_START  (0)
#define SOC_ISP_JPGENC_JPE_TQ_U_SELECT_tq1_select_END    (1)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TQ_V_SELECT_UNION
 结构说明  : JPE_TQ_V_SELECT 寄存器结构定义。地址偏移量:0x0030，初值:0x00000001，宽度:32
 寄存器说明: Q-table selector 2, quant table for V component.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tq2_select : 2;  /* bit[0-1] : "00"=reserved
                                                     "01"=qtable1
                                                     "10"=reserved
                                                     "11"=qtable3
                                                     for header generation tq2_select must be equal to tq1_select */
        unsigned int  reserved   : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TQ_V_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_tq2_select_START  (0)
#define SOC_ISP_JPGENC_JPE_TQ_V_SELECT_tq2_select_END    (1)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_UNION
 结构说明  : JPE_DC_TABLE_SELECT 寄存器结构定义。地址偏移量:0x0034，初值:0x00000006，宽度:32
 寄存器说明: Huffman table selector for DC values.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dc_table_select_y : 1;  /* bit[0]   : "0"=dc table 0; color component 0(Y)
                                                            "1"=reserved */
        unsigned int  dc_table_select_u : 1;  /* bit[1]   : "0"=reserved
                                                            "1"=dc table 1; color component 1(U) */
        unsigned int  dc_table_select_v : 1;  /* bit[2]   : "0"=reserved
                                                            "1"=dc table 1; color component 2(V) */
        unsigned int  reserved          : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_y_START  (0)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_y_END    (0)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_u_START  (1)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_u_END    (1)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_v_START  (2)
#define SOC_ISP_JPGENC_JPE_DC_TABLE_SELECT_dc_table_select_v_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_UNION
 结构说明  : JPE_AC_TABLE_SELECT 寄存器结构定义。地址偏移量:0x0038，初值:0x00000006，宽度:32
 寄存器说明: Huffman table selector for AC value.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ac_table_select_y : 1;  /* bit[0]   : "0"=ac table 0; component 0(Y)
                                                            "1"=reserved */
        unsigned int  ac_table_select_u : 1;  /* bit[1]   : "0"=reserved
                                                            "1"=ac table 1; component 1(U) */
        unsigned int  ac_table_select_v : 1;  /* bit[2]   : "0"=reserved
                                                            "1"=ac table 1; component 2(V) */
        unsigned int  reserved          : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_y_START  (0)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_y_END    (0)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_u_START  (1)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_u_END    (1)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_v_START  (2)
#define SOC_ISP_JPGENC_JPE_AC_TABLE_SELECT_ac_table_select_v_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TABLE_DATA_UNION
 结构说明  : JPE_TABLE_DATA 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: table programming register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  table_wdata_l : 8;  /* bit[0-7]  : Table data LSB */
        unsigned int  table_wdata_h : 8;  /* bit[8-15] : Table data MSB */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TABLE_DATA_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_l_START  (0)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_l_END    (7)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_h_START  (8)
#define SOC_ISP_JPGENC_JPE_TABLE_DATA_table_wdata_h_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TABLE_ID_UNION
 结构说明  : JPE_TABLE_ID 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: table programming select register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  table_id : 4;  /* bit[0-3] : select table
                                                   "0000":Q-table 0
                                                   "0001":Q-table 1
                                                   "0010":Q-table 2
                                                   "0011":Q-table 3
                                                   "0100":VLC DC-table 0
                                                   "0101":VLC AC-table 0
                                                   "0110":VLC DC-table 1
                                                   "0111":VLC AC-table 1
                                                   "1xxx":reserved for debug */
        unsigned int  reserved : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TABLE_ID_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TABLE_ID_table_id_START  (0)
#define SOC_ISP_JPGENC_JPE_TABLE_ID_table_id_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TAC0_LEN_UNION
 结构说明  : JPE_TAC0_LEN 寄存器结构定义。地址偏移量:0x0044，初值:0x000000B2，宽度:32
 寄存器说明: Huffman AC table 0 length.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tac0_len : 8;  /* bit[0-7] : Huffman table length for ac0 table */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TAC0_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_tac0_len_START  (0)
#define SOC_ISP_JPGENC_JPE_TAC0_LEN_tac0_len_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TDC0_LEN_UNION
 结构说明  : JPE_TDC0_LEN 寄存器结构定义。地址偏移量:0x0048，初值:0x0000001C，宽度:32
 寄存器说明: Huffman DC table 0 length.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tdc0_len : 8;  /* bit[0-7] : Huffman table length for dc0 table */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TDC0_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_tdc0_len_START  (0)
#define SOC_ISP_JPGENC_JPE_TDC0_LEN_tdc0_len_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TAC1_LEN_UNION
 结构说明  : JPE_TAC1_LEN 寄存器结构定义。地址偏移量:0x0004C，初值:0x000000B2，宽度:32
 寄存器说明: Huffman AC table 1 length.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tac1_len : 8;  /* bit[0-7] : Huffman table length for ac1 table */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TAC1_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_tac1_len_START  (0)
#define SOC_ISP_JPGENC_JPE_TAC1_LEN_tac1_len_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_TDC1_LEN_UNION
 结构说明  : JPE_TDC1_LEN 寄存器结构定义。地址偏移量:0x0050，初值:0x0000001C，宽度:32
 寄存器说明: Huffman DC table 1 length.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tdc1_len : 8;  /* bit[0-7] : Huffman table length for dc1 table */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_TDC1_LEN_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_tdc1_len_START  (0)
#define SOC_ISP_JPGENC_JPE_TDC1_LEN_tdc1_len_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ENCODER_MODE_UNION
 结构说明  : JPE_ENCODER_MODE 寄存器结构定义。地址偏移量:0x0060，初值:0x00000001，宽度:32
 寄存器说明: encode mode.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  encode_mode : 1;  /* bit[0]   : always "1" */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ENCODER_MODE_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_encode_mode_START  (0)
#define SOC_ISP_JPGENC_JPE_ENCODER_MODE_encode_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_DEBUG_UNION
 结构说明  : JPE_DEBUG 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: debug information register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 2;  /* bit[0-1] :  */
        unsigned int  deb_qiq_table_acc    : 1;  /* bit[2]   : Debug Signal only (QIQ table access) */
        unsigned int  deb_vlc_encode_busy  : 1;  /* bit[3]   : Debug Signal only (vlc encode processing active) */
        unsigned int  deb_r2b_memory_full  : 1;  /* bit[4]   : Debug sinal only (line memory status of r2b) */
        unsigned int  deb_vlc_table_busy   : 1;  /* bit[5]   : Debug signal only (vlc access to huff-tables) */
        unsigned int  reserved_1           : 2;  /* bit[6-7] :  */
        unsigned int  deb_bad_table_access : 1;  /* bit[8]   : Debug signal only (set if an access to the TABLE_DATA or to the TABLE_ID register is performed, when the JPEG_ENCODER is busy. In this case a default PVCI Acknowledge is generated. Thus the configuration bus is not blocked) */
        unsigned int  reserved_2           : 23; /* bit[9-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_DEBUG_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_qiq_table_acc_START     (2)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_qiq_table_acc_END       (2)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_encode_busy_START   (3)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_encode_busy_END     (3)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_r2b_memory_full_START   (4)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_r2b_memory_full_END     (4)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_table_busy_START    (5)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_vlc_table_busy_END      (5)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_bad_table_access_START  (8)
#define SOC_ISP_JPGENC_JPE_DEBUG_deb_bad_table_access_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ERROR_IMR_UNION
 结构说明  : JPE_ERROR_IMR 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: JPEG error interrupt mask register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 4;  /* bit[0-3]  :  */
        unsigned int  vlc_symbol_err_imr   : 1;  /* bit[4]    : "1"=interrupt is activated(masked in) */
        unsigned int  reserved_1           : 2;  /* bit[5-6]  :  */
        unsigned int  dct_err_imr          : 1;  /* bit[7]    : "1"=interrupt is activated(masked in) */
        unsigned int  reserved_2           : 1;  /* bit[8]    :  */
        unsigned int  r2b_img_size_err_imr : 1;  /* bit[9]    : "1"=interrupt is activated(masked in) */
        unsigned int  vlc_table_err_imr    : 1;  /* bit[10]   : "1"=interrupt is activated(masked in) */
        unsigned int  reserved_3           : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_IMR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_symbol_err_imr_START    (4)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_symbol_err_imr_END      (4)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_dct_err_imr_START           (7)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_dct_err_imr_END             (7)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_r2b_img_size_err_imr_START  (9)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_r2b_img_size_err_imr_END    (9)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_table_err_imr_START     (10)
#define SOC_ISP_JPGENC_JPE_ERROR_IMR_vlc_table_err_imr_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ERROR_RIS_UNION
 结构说明  : JPE_ERROR_RIS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: JPEG error raw interrupt status register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 4;  /* bit[0-3]  :  */
        unsigned int  vlc_symbol_err_ris   : 1;  /* bit[4]    : "1"=illegal symbol detected(encoding) */
        unsigned int  reserved_1           : 2;  /* bit[5-6]  :  */
        unsigned int  dct_err_ris          : 1;  /* bit[7]    : "1"=block start mismatch */
        unsigned int  reserved_2           : 1;  /* bit[8]    :  */
        unsigned int  r2b_img_size_err_ris : 1;  /* bit[9]    : "1"=mismatch of predefined h_size and v_size value with calculated values (encode mode) */
        unsigned int  vlc_table_err_ris    : 1;  /* bit[10]   : "1"=illegal table detected */
        unsigned int  reserved_3           : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_RIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_symbol_err_ris_START    (4)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_symbol_err_ris_END      (4)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_dct_err_ris_START           (7)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_dct_err_ris_END             (7)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_r2b_img_size_err_ris_START  (9)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_r2b_img_size_err_ris_END    (9)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_table_err_ris_START     (10)
#define SOC_ISP_JPGENC_JPE_ERROR_RIS_vlc_table_err_ris_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ERROR_MIS_UNION
 结构说明  : JPE_ERROR_MIS 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: JPEG error masked interrupt status register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 4;  /* bit[0-3]  :  */
        unsigned int  vlc_symbol_err_mis   : 1;  /* bit[4]    : "1"=illegal symbol detected(encoding) */
        unsigned int  reserved_1           : 2;  /* bit[5-6]  :  */
        unsigned int  dct_err_mis          : 1;  /* bit[7]    : "1"=block start mismatch */
        unsigned int  reserved_2           : 1;  /* bit[8]    :  */
        unsigned int  r2b_img_size_err_mis : 1;  /* bit[9]    : "1"=mismatch of predefined h_size and v_size value with calculated values (encode mode) */
        unsigned int  vlc_table_err_mis    : 1;  /* bit[10]   : "1"=illegal table detected */
        unsigned int  reserved_3           : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_MIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_symbol_err_mis_START    (4)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_symbol_err_mis_END      (4)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_dct_err_mis_START           (7)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_dct_err_mis_END             (7)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_r2b_img_size_err_mis_START  (9)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_r2b_img_size_err_mis_END    (9)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_table_err_mis_START     (10)
#define SOC_ISP_JPGENC_JPE_ERROR_MIS_vlc_table_err_mis_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ERROR_ICR_UNION
 结构说明  : JPE_ERROR_ICR 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: JPEG error interrupt clear regisger.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 4;  /* bit[0-3]  :  */
        unsigned int  vlc_symbol_err_icr   : 1;  /* bit[4]    : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  reserved_1           : 2;  /* bit[5-6]  :  */
        unsigned int  dct_err_icr          : 1;  /* bit[7]    : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  reserved_2           : 1;  /* bit[8]    :  */
        unsigned int  r2b_img_size_err_icr : 1;  /* bit[9]    : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  vlc_table_err_icr    : 1;  /* bit[10]   : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  reserved_3           : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_ICR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_symbol_err_icr_START    (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_symbol_err_icr_END      (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_dct_err_icr_START           (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_dct_err_icr_END             (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_r2b_img_size_err_icr_START  (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_r2b_img_size_err_icr_END    (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_table_err_icr_START     (10)
#define SOC_ISP_JPGENC_JPE_ERROR_ICR_vlc_table_err_icr_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ERROR_ISR_UNION
 结构说明  : JPE_ERROR_ISR 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: JPEG error interrupt set register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 4;  /* bit[0-3]  :  */
        unsigned int  vlc_symbol_err_isr   : 1;  /* bit[4]    : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  reserved_1           : 2;  /* bit[5-6]  :  */
        unsigned int  dct_err_isr          : 1;  /* bit[7]    : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  reserved_2           : 1;  /* bit[8]    :  */
        unsigned int  r2b_img_size_err_isr : 1;  /* bit[9]    : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  vlc_table_err_isr    : 1;  /* bit[10]   : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  reserved_3           : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ERROR_ISR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_symbol_err_isr_START    (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_symbol_err_isr_END      (4)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_dct_err_isr_START           (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_dct_err_isr_END             (7)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_r2b_img_size_err_isr_START  (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_r2b_img_size_err_isr_END    (9)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_table_err_isr_START     (10)
#define SOC_ISP_JPGENC_JPE_ERROR_ISR_vlc_table_err_isr_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_STATUS_IMR_UNION
 结构说明  : JPE_STATUS_IMR 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: JPEG status interrupt mask register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] :  */
        unsigned int  encode_done_imr     : 1;  /* bit[4]   : "1"=interrupt is activated(masked in) */
        unsigned int  gen_header_done_imr : 1;  /* bit[5]   : "1"=interrupt is activated(masked in) */
        unsigned int  reserved_1          : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_IMR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_encode_done_imr_START      (4)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_encode_done_imr_END        (4)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_gen_header_done_imr_START  (5)
#define SOC_ISP_JPGENC_JPE_STATUS_IMR_gen_header_done_imr_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_STATUS_RIS_UNION
 结构说明  : JPE_STATUS_RIS 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: JPEG status raw interrupt status register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] :  */
        unsigned int  encode_done_ris     : 1;  /* bit[4]   : "1"=Encode processing finished */
        unsigned int  gen_header_done_ris : 1;  /* bit[5]   : "1"=Stream header generation finished */
        unsigned int  reserved_1          : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_RIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_encode_done_ris_START      (4)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_encode_done_ris_END        (4)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_gen_header_done_ris_START  (5)
#define SOC_ISP_JPGENC_JPE_STATUS_RIS_gen_header_done_ris_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_STATUS_MIS_UNION
 结构说明  : JPE_STATUS_MIS 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: JPEG status masked interrupt status register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] :  */
        unsigned int  encode_done_mis     : 1;  /* bit[4]   : "1"=Encode processing finished */
        unsigned int  gen_header_done_mis : 1;  /* bit[5]   : "1"=Stream header generation finished */
        unsigned int  reserved_1          : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_MIS_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_encode_done_mis_START      (4)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_encode_done_mis_END        (4)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_gen_header_done_mis_START  (5)
#define SOC_ISP_JPGENC_JPE_STATUS_MIS_gen_header_done_mis_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_STATUS_ICR_UNION
 结构说明  : JPE_STATUS_ICR 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: JPEG status interrupt clear register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] :  */
        unsigned int  encode_done_icr     : 1;  /* bit[4]   : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  gen_header_done_icr : 1;  /* bit[5]   : "1"=clear status bit, bit is reset to zero after 1clk */
        unsigned int  reserved_1          : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_ICR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_encode_done_icr_START      (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_encode_done_icr_END        (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_gen_header_done_icr_START  (5)
#define SOC_ISP_JPGENC_JPE_STATUS_ICR_gen_header_done_icr_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_STATUS_ISR_UNION
 结构说明  : JPE_STATUS_ISR 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: JPEG status interrrupt set register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] :  */
        unsigned int  encode_done_isr     : 1;  /* bit[4]   : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  gen_header_done_isr : 1;  /* bit[5]   : "1"=set error bit, bit is reset to zero after 1 clk */
        unsigned int  reserved_1          : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_STATUS_ISR_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_encode_done_isr_START      (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_encode_done_isr_END        (4)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_gen_header_done_isr_START  (5)
#define SOC_ISP_JPGENC_JPE_STATUS_ISR_gen_header_done_isr_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_CONFIG_UNION
 结构说明  : JPE_CONFIG 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: JPEG configuration register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 4;  /* bit[0-3] :  */
        unsigned int  speedview_en : 1;  /* bit[4]   : 1:speed view enabled */
        unsigned int  reserved_1   : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_CONFIG_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_CONFIG_speedview_en_START  (4)
#define SOC_ISP_JPGENC_JPE_CONFIG_speedview_en_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_ADDRESS_Y_UNION
 结构说明  : ADDRESS_Y 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: Y Buffer address.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved  : 4;  /* bit[0-3] :  */
        unsigned int  address_y : 28; /* bit[4-31]: Address of Y Buffer in external memory. 
                                                    0: 0
                                                    1: 1 << 4 = 1 * 16
                                                    N: N << 4 = N * 16
                                                    [Note]
                                                    Address is on 32-bit with 7 lowest bits=0 when encoding from SRAM ( 128-byte alignment ) and 4 lowest bits= 0 when encoding from DRAM (128-bit alignment).ADDRESS_Y.address_Y are the MSB
                                                    [end] */
    } reg;
} SOC_ISP_JPGENC_ADDRESS_Y_UNION;
#endif
#define SOC_ISP_JPGENC_ADDRESS_Y_address_y_START  (4)
#define SOC_ISP_JPGENC_ADDRESS_Y_address_y_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_ADDRESS_UV_UNION
 结构说明  : ADDRESS_UV 寄存器结构定义。地址偏移量:0x00098，初值:0x00000000，宽度:32
 寄存器说明: UV Buffer addresss.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved   : 4;  /* bit[0-3] :  */
        unsigned int  address_uv : 28; /* bit[4-31]: Address of UV Buffer in external memory. 
                                                     0: 0
                                                     1: 1 << 4 = 1 * 16 
                                                     N: N << 4 = N * 16
                                                     [Note]
                                                     Address is on 32-bit with 7 lowest bits=0 when encoding from SRAM ( 128-byte alignment ) and 4 lowest bits= 0 when encoding from DRAM (128-bit alignment).ADDRESS_UV.address_UV are the MSB
                                                     [end] */
    } reg;
} SOC_ISP_JPGENC_ADDRESS_UV_UNION;
#endif
#define SOC_ISP_JPGENC_ADDRESS_UV_address_uv_START  (4)
#define SOC_ISP_JPGENC_ADDRESS_UV_address_uv_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_STRIDE_UNION
 结构说明  : STRIDE 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: Address stride in bytes.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 4;  /* bit[0-3]  :  */
        unsigned int  stride   : 11; /* bit[4-14] : Address stride in bytes while encoding from DRAM- Stride must be a multiple of 128-bit when encoding from DRAM with 4 lowest bits = 0. STRIDE.stride is the MSB. When MMU prefetch used, stride should be less than 16KB for YUV422, and 8KB for YUV420. 
                                                    0: 0 bytes
                                                    1: (1<<4) bytes = 1*16 bytes
                                                    N: (N<<4) bytes = N*16 bytes
                                                    in SRAM mode, this parameter is ignored */
        unsigned int  reserved_1: 17; /* bit[15-31]:  */
    } reg;
} SOC_ISP_JPGENC_STRIDE_UNION;
#endif
#define SOC_ISP_JPGENC_STRIDE_stride_START    (4)
#define SOC_ISP_JPGENC_STRIDE_stride_END      (14)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_SYNCCFG_UNION
 结构说明  : SYNCCFG 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: Source Synchronization configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  source     : 1;  /* bit[0-0] : Encoding source : 
                                                     0: SRAM , internal synchronization
                                                     1: DRAM, FCM is used for synchronization */
        unsigned int  reserved_0 : 1;  /* bit[1-1] :  */
        unsigned int  sram_noopt : 1;  /* bit[2-2] : SRAM usage Optimization configuration
                                                     0: SRAM usage optimization ON, synchronization sharing 1 slice for RD/WR 
                                                     1: SRAM usage optimization OFF, ping-pong synchronization */
        unsigned int  reserved_1 : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_JPGENC_SYNCCFG_UNION;
#endif
#define SOC_ISP_JPGENC_SYNCCFG_source_START      (0)
#define SOC_ISP_JPGENC_SYNCCFG_source_END        (0)
#define SOC_ISP_JPGENC_SYNCCFG_sram_noopt_START  (2)
#define SOC_ISP_JPGENC_SYNCCFG_sram_noopt_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_UNION
 结构说明  : JPE_ENC_HRIGHT2 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: Picture from pipe2 Hsize.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_hright2 : 13; /* bit[0-12] : Number of pixels in the picture from pipe2. Number of pixels is always even
                                                       0: no encode from pipe2
                                                       1: 2 pixels
                                                       2N-1:2xN pixels enc_hright2= hsize2-1
                                                       in SRAM mode,max(enc_hright1+enc_hright2)<5376
                                                       in DRAM mode,max(enc_hright1+enc_hright2)<8192 */
        unsigned int  reserved    : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_UNION;
#endif
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_enc_hright2_START  (0)
#define SOC_ISP_JPGENC_JPE_ENC_HRIGHT2_enc_hright2_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_JPG_BYTE_CNT_UNION
 结构说明  : JPG_BYTE_CNT 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: Number of encoded bytes sent to video port.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  byte_cnt : 30; /* bit[0-29] : Number of encoded bytes sent to output video port- The value is updated by HW once by frame at end of encoding
                                                    0: 0 bytes
                                                    1: 1 byte
                                                    N: N bytes */
        unsigned int  reserved : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_JPGENC_JPG_BYTE_CNT_UNION;
#endif
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_byte_cnt_START  (0)
#define SOC_ISP_JPGENC_JPG_BYTE_CNT_byte_cnt_END    (29)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREFETCH_UNION
 结构说明  : PREFETCH 寄存器结构定义。地址偏移量:0x010C，初值:0x00000974，宽度:32
 寄存器说明: Prefetch configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prefetch_en    : 1;  /* bit[0]    : Prefetch Enable
                                                          0: Prefetch disabled 
                                                          1: Prefetch enabled */
        unsigned int  prefetch_delay : 11; /* bit[1-11] : Minimum number of cycles between 2 prefetch commands typical value is 1210 (decimal)
                                                          0: 0 cycle
                                                          N: N cycles */
        unsigned int  reserved       : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_JPGENC_PREFETCH_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_prefetch_en_START     (0)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_en_END       (0)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_delay_START  (1)
#define SOC_ISP_JPGENC_PREFETCH_prefetch_delay_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREFETCH_IDY0_UNION
 结构说明  : PREFETCH_IDY0 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: Prefetch ID configuration (Y Buffer).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id0_y    : 7;  /* bit[0-6]  : Y Buffer ID0 configuration. 
                                                    N:N */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  id1_y    : 7;  /* bit[8-14] : Y Buffer ID1 configuration. 
                                                    N:N */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  id2_y    : 7;  /* bit[16-22]: Y Buffer ID2 configuration. 
                                                    N:N */
        unsigned int  reserved_2: 1;  /* bit[23]   :  */
        unsigned int  id3_y    : 7;  /* bit[24-30]: Y Buffer ID3 configuration. 
                                                    N:N  */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDY0_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id0_y_START     (0)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id0_y_END       (6)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id1_y_START     (8)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id1_y_END       (14)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id2_y_START     (16)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id2_y_END       (22)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id3_y_START     (24)
#define SOC_ISP_JPGENC_PREFETCH_IDY0_id3_y_END       (30)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREFETCH_IDY1_UNION
 结构说明  : PREFETCH_IDY1 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: Prefetch ID configuration (Y Buffer).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id4_y    : 7;  /* bit[0-6]  : Y Buffer ID4 configuration. 
                                                    N:N */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  id5_y    : 7;  /* bit[8-14] : Y Buffer ID5 configuration. 
                                                    N:N */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  id6_y    : 7;  /* bit[16-22]: Y Buffer ID6 configuration. 
                                                    N:N */
        unsigned int  reserved_2: 1;  /* bit[23]   :  */
        unsigned int  id7_y    : 7;  /* bit[24-30]: Y Buffer ID7 configuration. 
                                                    N:N */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDY1_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id4_y_START     (0)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id4_y_END       (6)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id5_y_START     (8)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id5_y_END       (14)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id6_y_START     (16)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id6_y_END       (22)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id7_y_START     (24)
#define SOC_ISP_JPGENC_PREFETCH_IDY1_id7_y_END       (30)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREFETCH_IDUV0_UNION
 结构说明  : PREFETCH_IDUV0 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: Prefetch ID configuration (UV Buffer).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id0_uv   : 7;  /* bit[0-6]  : UV Buffer ID0 configuration. 
                                                    N:N */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  id1_uv   : 7;  /* bit[8-14] : UV Buffer ID1 configuration. 
                                                    N:N */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  id2_uv   : 7;  /* bit[16-22]: UV Buffer ID2 configuration. 
                                                    N:N */
        unsigned int  reserved_2: 1;  /* bit[23]   :  */
        unsigned int  id3_uv   : 7;  /* bit[24-30]: UV Buffer ID3 configuration. 
                                                    N:N */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDUV0_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id0_uv_START    (0)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id0_uv_END      (6)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id1_uv_START    (8)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id1_uv_END      (14)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id2_uv_START    (16)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id2_uv_END      (22)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id3_uv_START    (24)
#define SOC_ISP_JPGENC_PREFETCH_IDUV0_id3_uv_END      (30)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREFETCH_IDUVY_UNION
 结构说明  : PREFETCH_IDUVY 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: Prefetch ID configuration (UV Buffer).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id4_uv   : 7;  /* bit[0-6]  : UV Buffer ID4 configuration. 
                                                    N:N */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  id8_y    : 7;  /* bit[8-14] : Y Buffer ID8 configuration. 
                                                    N:N */
        unsigned int  reserved_1: 17; /* bit[15-31]: UV Buffer ID7 configuration. 
                                                     N:N */
    } reg;
} SOC_ISP_JPGENC_PREFETCH_IDUVY_UNION;
#endif
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id4_uv_START    (0)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id4_uv_END      (6)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id8_y_START     (8)
#define SOC_ISP_JPGENC_PREFETCH_IDUVY_id8_y_END       (14)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_PREREAD_UNION
 结构说明  : PREREAD 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: Number of preread MCU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  preread  : 4;  /* bit[0-3] : Number of MCUs read from external memory with no available place in JPEGENC MCU buffer ( pre-read).
                                                   0: No pre read - Should be configured when encoding from SRAM or encoding YUV422 from DRAM
                                                   1: 1 MCU pre READ
                                                   N: N pre READ - Recommended value is 4 when encoding YUV420 from DRAM- It can be tuned according to DRAM latency */
        unsigned int  reserved : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_JPGENC_PREREAD_UNION;
#endif
#define SOC_ISP_JPGENC_PREREAD_preread_START   (0)
#define SOC_ISP_JPGENC_PREREAD_preread_END     (3)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_UNION
 结构说明  : FORCE_CLK_ON_CFG 寄存器结构定义。地址偏移量:0x0130，初值:0x00000001，宽度:32
 寄存器说明: used to force the clock which is generally controlled by HW.
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
} SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_force_clk_on_START  (0)
#define SOC_ISP_JPGENC_FORCE_CLK_ON_CFG_force_clk_on_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_0_UNION
 结构说明  : DBG_0 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: debug regiser0.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_0 : 32; /* bit[0-31]: sram_rd debug
                                                [31]:mcubuf_full
                                                [30]:rd_cmd_fifo_full
                                                [29:16]:row_cnt[13:0]
                                                [15:8]:blk_cnt[7:0]
                                                [7]:mb_valid
                                                [6:4]:line_cnt[2:0]
                                                [3:0]:cur_st[3:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_0_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_0_dbg_0_START  (0)
#define SOC_ISP_JPGENC_DBG_0_dbg_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_1_UNION
 结构说明  : DBG_1 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: debug regiser1.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_1 : 32; /* bit[0-31]: sram_rd debug 1
                                                [31:2]:0
                                                [1]:slice_sel
                                                [0]:wait_slice_done */
    } reg;
} SOC_ISP_JPGENC_DBG_1_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_1_dbg_1_START  (0)
#define SOC_ISP_JPGENC_DBG_1_dbg_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_2_UNION
 结构说明  : DBG_2 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: debug register2.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_2 : 32; /* bit[0-31]: dram_rd debug 0
                                                [31]:fcm_slice_vld
                                                [30]:slice_rd_end
                                                [29]:cfifo_full
                                                [28:16]:row_cnt[12:0]
                                                [15:8]:blk_cnt[7:0]
                                                [7]:mcubuf_full
                                                [6:4]:line_cnt
                                                [3:0]:cur_st */
    } reg;
} SOC_ISP_JPGENC_DBG_2_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_2_dbg_2_START  (0)
#define SOC_ISP_JPGENC_DBG_2_dbg_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_3_UNION
 结构说明  : DBG_3 寄存器结构定义。地址偏移量:0x020c，初值:0x00000000，宽度:32
 寄存器说明: debug register3.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_3 : 32; /* bit[0-31]: prefetch debug 0
                                                [31]:one_ongoing
                                                [30:28]:cur_st[2:0]
                                                [27:26]:status_uv[4]
                                                [25:24]:status_uv[3]
                                                [23:22]:status_uv[2]
                                                [21:20]:status_uv[1]
                                                [19:18]:status_uv[0]
                                                [17:16]:status_y[8]
                                                [15:14]:status_y[7]
                                                [13:12]:status_y[6]
                                                [11:10]:status_y[5]
                                                [9:8]:status_y[4]
                                                [7:6]:status_y[3]
                                                [5:4]:status_y[2]
                                                [3:2]:status_y[1]
                                                [1:0]:status_y[0] */
    } reg;
} SOC_ISP_JPGENC_DBG_3_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_3_dbg_3_START  (0)
#define SOC_ISP_JPGENC_DBG_3_dbg_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_4_UNION
 结构说明  : DBG_4 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: debug register4.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_4 : 32; /* bit[0-31]: left sram_wr debug 0
                                                [31:30]:0
                                                [29:16]:row_cnt[13:0]
                                                [15:8]:blk_cnt[7:0]
                                                [7:4]:line_cnt[3:0]
                                                [3:0]:cur_st[3:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_4_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_4_dbg_4_START  (0)
#define SOC_ISP_JPGENC_DBG_4_dbg_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_5_UNION
 结构说明  : DBG_5 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: debug register5.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_5 : 32; /* bit[0-31]: left sram_wr debug 1
                                                [31]:uv_cm_rdy
                                                [30]:uv_cmd_rdy
                                                [29:16]:uv_kblk_vld_num[13:0]
                                                [15]:cmd_rdy
                                                [14]:cmd_rdy
                                                [13:0]:kblk_vld_num[13:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_5_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_5_dbg_5_START  (0)
#define SOC_ISP_JPGENC_DBG_5_dbg_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_6_UNION
 结构说明  : DBG_6 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
 寄存器说明: debug register6.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_6 : 32; /* bit[0-31]: right sram_wr debug 0
                                                [31:30]:0
                                                [29:16]:row_cnt[13:0]
                                                [15:8]:blk_cnt[7:0]
                                                [7:4]:line_cnt[3:0]
                                                [3:0]:cur_st[3:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_6_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_6_dbg_6_START  (0)
#define SOC_ISP_JPGENC_DBG_6_dbg_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_7_UNION
 结构说明  : DBG_7 寄存器结构定义。地址偏移量:0x021c，初值:0x00000000，宽度:32
 寄存器说明: debug register7.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_7 : 32; /* bit[0-31]: right sram_wr debug 1
                                                [31]:uv_cm_rdy
                                                [30]:uv_cmd_rdy
                                                [29:16]:uv_kblk_vld_num[13:0]
                                                [15]:cmd_rdy
                                                [14]:cmd_rdy
                                                [13:0]:kblk_vld_num[13:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_7_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_7_dbg_7_START  (0)
#define SOC_ISP_JPGENC_DBG_7_dbg_7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_8_UNION
 结构说明  : DBG_8 寄存器结构定义。地址偏移量:0x0220，初值:0x00000000，宽度:32
 寄存器说明: debug register8.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_8 : 32; /* bit[0-31]: mcubuf_wr debug 0
                                                [31:19]:0
                                                [18:14]:mcubuf_blk_num[4:0]
                                                [13]:mcubuf_full
                                                [12]:mcubuf_wr_rdy
                                                [11]:cmd_fifo_empty
                                                [10:9]:page_cnt[1:0]
                                                [8:6]:line_cnt[2:0]
                                                [5:3]:burst_cnt[2:0]
                                                [2:0]:cur_st[2:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_8_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_8_dbg_8_START  (0)
#define SOC_ISP_JPGENC_DBG_8_dbg_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_9_UNION
 结构说明  : DBG_9 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: debug register9.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_9 : 32; /* bit[0-31]: mcubuf_rd debug 0
                                                [31:28]:0
                                                [27]:fifo3_full
                                                [26]:fifo2_full
                                                [25]:fifo1_full
                                                [24]:fifo0_full
                                                [23:16]:restart_cnt[7:0]
                                                [15:14]:mcubuf_mb_cnt[1:0]
                                                [13]:mcubuf_mb_vld
                                                [12:10]:mcu_cnt[2:0]
                                                [9:7]:line_cnt[2:0]
                                                [6:5]:page_cnt[1:0]
                                                [4:0]:cur_st[4:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_9_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_9_dbg_9_START  (0)
#define SOC_ISP_JPGENC_DBG_9_dbg_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_10_UNION
 结构说明  : DBG_10 寄存器结构定义。地址偏移量:0x0228，初值:0x00000000，宽度:32
 寄存器说明: debug register10.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_10 : 32; /* bit[0-31]: mcubuf_rd debug 1
                                                 [31:28]:0
                                                 [27:14]:frame_row_cnt[13:0]
                                                 [13:0]:frame_col_cnt[13:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_10_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_10_dbg_10_START  (0)
#define SOC_ISP_JPGENC_DBG_10_dbg_10_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_11_UNION
 结构说明  : DBG_11 寄存器结构定义。地址偏移量:0x022c，初值:0x00000000，宽度:32
 寄存器说明: debug register11.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_11 : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_ISP_JPGENC_DBG_11_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_11_dbg_11_START  (0)
#define SOC_ISP_JPGENC_DBG_11_dbg_11_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_12_UNION
 结构说明  : DBG_12 寄存器结构定义。地址偏移量:0x0230，初值:0x00000000，宽度:32
 寄存器说明: debug register12.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_12 : 32; /* bit[0-31]: left vp_s2p
                                                 [31]:0
                                                 [30:28]:cur_st[2:0]
                                                 [27:14]:err_row_cnt[13:0]
                                                 [13:0]:err_col_cnt[13:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_12_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_12_dbg_12_START  (0)
#define SOC_ISP_JPGENC_DBG_12_dbg_12_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_13_UNION
 结构说明  : DBG_13 寄存器结构定义。地址偏移量:0x0234，初值:0x00000000，宽度:32
 寄存器说明: debug register13.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_13 : 32; /* bit[0-31]: right vp_s2p
                                                 [31]:0
                                                 [30:28]:cur_st[2:0]
                                                 [27:14]:err_row_cnt[13:0]
                                                 [13:0]:err_col_cnt[13:0] */
    } reg;
} SOC_ISP_JPGENC_DBG_13_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_13_dbg_13_START  (0)
#define SOC_ISP_JPGENC_DBG_13_dbg_13_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_14_UNION
 结构说明  : DBG_14 寄存器结构定义。地址偏移量:0x0238，初值:0x0000，宽度:32
 寄存器说明: debug register14.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_14 : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_ISP_JPGENC_DBG_14_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_14_dbg_14_START  (0)
#define SOC_ISP_JPGENC_DBG_14_dbg_14_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_15_UNION
 结构说明  : DBG_15 寄存器结构定义。地址偏移量:0x023c，初值:0x0000，宽度:32
 寄存器说明: debug register15.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_15 : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_ISP_JPGENC_DBG_15_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_15_dbg_15_START  (0)
#define SOC_ISP_JPGENC_DBG_15_dbg_15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_JPGENC_DBG_RW_0_UNION
 结构说明  : DBG_RW_0 寄存器结构定义。地址偏移量:0x0300，初值:0x0000，宽度:32
 寄存器说明: debug writable register.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rw_0 : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_ISP_JPGENC_DBG_RW_0_UNION;
#endif
#define SOC_ISP_JPGENC_DBG_RW_0_dbg_rw_0_START  (0)
#define SOC_ISP_JPGENC_DBG_RW_0_dbg_rw_0_END    (31)






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

#endif /* end of soc_isp_jpgenc_interface.h */
