/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_gcd_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:44
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_GCD.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_GCD_INTERFACE_H__
#define __SOC_ISP_GCD_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/2) GCD
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GCD_CONFIG_UNION */
#define SOC_ISP_GCD_GCD_CONFIG_ADDR(base)             ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GKM_IHLEFT_UNION */
#define SOC_ISP_GCD_GKM_IHLEFT_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GKM_IVTOP_UNION */
#define SOC_ISP_GCD_GKM_IVTOP_ADDR(base)              ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GKM_IHRIGHT_UNION */
#define SOC_ISP_GCD_GKM_IHRIGHT_ADDR(base)            ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GKM_IVBOTTOM_UNION */
#define SOC_ISP_GCD_GKM_IVBOTTOM_ADDR(base)           ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_DMS_UNION */
#define SOC_ISP_GCD_DMS_ADDR(base)                    ((base) + (0x0014))

/* 寄存器说明：False Color Removal parameters
   位域定义UNION结构:  SOC_ISP_GCD_FCR_UNION */
#define SOC_ISP_GCD_FCR_ADDR(base)                    ((base) + (0x0018))

/* 寄存器说明：Green Equilibrium Enables
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_ENA_UNION */
#define SOC_ISP_GCD_GEQ_ENA_ADDR(base)                ((base) + (0x001C))

/* 寄存器说明：Green Equilibrium WE
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_WEI_1_UNION */
#define SOC_ISP_GCD_GEQ_WEI_1_ADDR(base)              ((base) + (0x0020))

/* 寄存器说明：Green Equilibrium WE
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_WEI_2_UNION */
#define SOC_ISP_GCD_GEQ_WEI_2_ADDR(base)              ((base) + (0x0024))

/* 寄存器说明：Green Equilibrium thresolds
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_THR_1_UNION */
#define SOC_ISP_GCD_GEQ_THR_1_ADDR(base)              ((base) + (0x0028))

/* 寄存器说明：Green Equilibrium thresolds
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_THR_2_UNION */
#define SOC_ISP_GCD_GEQ_THR_2_ADDR(base)              ((base) + (0x002C))

/* 寄存器说明：Green Equilibrium thresolds
   位域定义UNION结构:  SOC_ISP_GCD_GEQ_THR_3_UNION */
#define SOC_ISP_GCD_GEQ_THR_3_ADDR(base)              ((base) + (0x0030))

/* 寄存器说明：False Color Suppression
   位域定义UNION结构:  SOC_ISP_GCD_FCS_UNION */
#define SOC_ISP_GCD_FCS_ADDR(base)                    ((base) + (0x0034))

/* 寄存器说明：Color Aberration Removal
   位域定义UNION结构:  SOC_ISP_GCD_CAC_EN_UNION */
#define SOC_ISP_GCD_CAC_EN_ADDR(base)                 ((base) + (0x0038))

/* 寄存器说明：Color Aberration Removal
   位域定义UNION结构:  SOC_ISP_GCD_CAC_CEN_UNION */
#define SOC_ISP_GCD_CAC_CEN_ADDR(base)                ((base) + (0x003C))

/* 寄存器说明：Color Aberration Removal
   位域定义UNION结构:  SOC_ISP_GCD_CAC_RAD_UNION */
#define SOC_ISP_GCD_CAC_RAD_ADDR(base)                ((base) + (0x0040))

/* 寄存器说明：Color Aberration Removal
   位域定义UNION结构:  SOC_ISP_GCD_CAC_WEI_UNION */
#define SOC_ISP_GCD_CAC_WEI_ADDR(base)                ((base) + (0x0044))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_CAC_THR_UNION */
#define SOC_ISP_GCD_CAC_THR_ADDR(base)                ((base) + (0x0048))

/* 寄存器说明：Global CAC Control
   位域定义UNION结构:  SOC_ISP_GCD_GCAC_CTRL_UNION */
#define SOC_ISP_GCD_GCAC_CTRL_ADDR(base)              ((base) + (0x004C))

/* 寄存器说明：X,Y scaling and normalization factor
   位域定义UNION结构:  SOC_ISP_GCD_GCAC_NORM_UNION */
#define SOC_ISP_GCD_GCAC_NORM_ADDR(base)              ((base) + (0x0050))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GCAC_A_UNION */
#define SOC_ISP_GCD_GCAC_A_ADDR(base)                 ((base) + (0x0054))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GCAC_B_UNION */
#define SOC_ISP_GCD_GCAC_B_ADDR(base)                 ((base) + (0x0058))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GCD_GCAC_C_UNION */
#define SOC_ISP_GCD_GCAC_C_ADDR(base)                 ((base) + (0x005C))

/* 寄存器说明：select active table:
            0: LSC_LUT_0 is used by the HW
            1: LSC_LUT_1 is used by the HW
   位域定义UNION结构:  SOC_ISP_GCD_LSC_TABLE_ACTIVE_UNION */
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_ADDR(base)       ((base) + (0x0060))

/* 寄存器说明：LookUp Table, 256 entries
   位域定义UNION结构:  SOC_ISP_GCD_LSC_LUT_0_UNION */
#define SOC_ISP_GCD_LSC_LUT_0_ADDR(base, Range256)    ((base) + (0x0100+0x4*(Range256)))

/* 寄存器说明：LookUp Table, 256 entries
   位域定义UNION结构:  SOC_ISP_GCD_LSC_LUT_1_UNION */
#define SOC_ISP_GCD_LSC_LUT_1_ADDR(base, Range256)    ((base) + (0x0500+0x4*(Range256)))



/****************************************************************************
                     (2/2) STATDIS
 ****************************************************************************/




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
                     (1/2) GCD
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCD_CONFIG_UNION
 结构说明  : GCD_CONFIG 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0-0] : Bypass:
                                                   0: the module is active
                                                   1: the module is bypassed
                                                   the configuration is taken into account on a SOF.
                                                   (Same HW behavior as RW_SHADOW) */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_GCD_GCD_CONFIG_UNION;
#endif
#define SOC_ISP_GCD_GCD_CONFIG_bypass_START    (0)
#define SOC_ISP_GCD_GCD_CONFIG_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GKM_IHLEFT_UNION
 结构说明  : GKM_IHLEFT 寄存器结构定义。地址偏移量:0x0004，初值:0x00001FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gkm_crop_left : 13; /* bit[0-12] : Crop Left */
        unsigned int  reserved      : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_GCD_GKM_IHLEFT_UNION;
#endif
#define SOC_ISP_GCD_GKM_IHLEFT_gkm_crop_left_START  (0)
#define SOC_ISP_GCD_GKM_IHLEFT_gkm_crop_left_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GKM_IVTOP_UNION
 结构说明  : GKM_IVTOP 寄存器结构定义。地址偏移量:0x0008，初值:0x00001FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gkm_crop_top : 13; /* bit[0-12] : Crop Top */
        unsigned int  reserved     : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_GCD_GKM_IVTOP_UNION;
#endif
#define SOC_ISP_GCD_GKM_IVTOP_gkm_crop_top_START  (0)
#define SOC_ISP_GCD_GKM_IVTOP_gkm_crop_top_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GKM_IHRIGHT_UNION
 结构说明  : GKM_IHRIGHT 寄存器结构定义。地址偏移量:0x000C，初值:0x00001FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gkm_crop_right : 13; /* bit[0-12] : Crop Right */
        unsigned int  reserved       : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_GCD_GKM_IHRIGHT_UNION;
#endif
#define SOC_ISP_GCD_GKM_IHRIGHT_gkm_crop_right_START  (0)
#define SOC_ISP_GCD_GKM_IHRIGHT_gkm_crop_right_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GKM_IVBOTTOM_UNION
 结构说明  : GKM_IVBOTTOM 寄存器结构定义。地址偏移量:0x0010，初值:0x00001FFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gkm_crop_bottom : 13; /* bit[0-12] : Crop Bottom */
        unsigned int  reserved        : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_GCD_GKM_IVBOTTOM_UNION;
#endif
#define SOC_ISP_GCD_GKM_IVBOTTOM_gkm_crop_bottom_START  (0)
#define SOC_ISP_GCD_GKM_IVBOTTOM_gkm_crop_bottom_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_DMS_UNION
 结构说明  : DMS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dms_wei1 : 9;  /* bit[0-8]  :  */
        unsigned int  dms_wei2 : 7;  /* bit[9-15] :  */
        unsigned int  dms_cho  : 2;  /* bit[16-17]:  */
        unsigned int  dms_thr1 : 10; /* bit[18-27]:  */
        unsigned int  reserved : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_GCD_DMS_UNION;
#endif
#define SOC_ISP_GCD_DMS_dms_wei1_START  (0)
#define SOC_ISP_GCD_DMS_dms_wei1_END    (8)
#define SOC_ISP_GCD_DMS_dms_wei2_START  (9)
#define SOC_ISP_GCD_DMS_dms_wei2_END    (15)
#define SOC_ISP_GCD_DMS_dms_cho_START   (16)
#define SOC_ISP_GCD_DMS_dms_cho_END     (17)
#define SOC_ISP_GCD_DMS_dms_thr1_START  (18)
#define SOC_ISP_GCD_DMS_dms_thr1_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_FCR_UNION
 结构说明  : FCR 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: False Color Removal parameters
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fcr_ena0 : 1;  /* bit[0-0]  :  */
        unsigned int  fcr_ena1 : 1;  /* bit[1-1]  :  */
        unsigned int  fcr_ena2 : 1;  /* bit[2-2]  :  */
        unsigned int  fcr_cho  : 3;  /* bit[3-5]  :  */
        unsigned int  reserved_0: 2;  /* bit[6-7]  :  */
        unsigned int  fcr_wei1 : 8;  /* bit[8-15] :  */
        unsigned int  fcr_wei2 : 6;  /* bit[16-21]:  */
        unsigned int  reserved_1: 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_GCD_FCR_UNION;
#endif
#define SOC_ISP_GCD_FCR_fcr_ena0_START  (0)
#define SOC_ISP_GCD_FCR_fcr_ena0_END    (0)
#define SOC_ISP_GCD_FCR_fcr_ena1_START  (1)
#define SOC_ISP_GCD_FCR_fcr_ena1_END    (1)
#define SOC_ISP_GCD_FCR_fcr_ena2_START  (2)
#define SOC_ISP_GCD_FCR_fcr_ena2_END    (2)
#define SOC_ISP_GCD_FCR_fcr_cho_START   (3)
#define SOC_ISP_GCD_FCR_fcr_cho_END     (5)
#define SOC_ISP_GCD_FCR_fcr_wei1_START  (8)
#define SOC_ISP_GCD_FCR_fcr_wei1_END    (15)
#define SOC_ISP_GCD_FCR_fcr_wei2_START  (16)
#define SOC_ISP_GCD_FCR_fcr_wei2_END    (21)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_ENA_UNION
 结构说明  : GEQ_ENA 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium Enables
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ena0     : 1;  /* bit[0-0]  :  */
        unsigned int  ena1     : 1;  /* bit[1-1]  :  */
        unsigned int  ena2     : 1;  /* bit[2-2]  :  */
        unsigned int  ena3     : 1;  /* bit[3-3]  :  */
        unsigned int  ena4     : 1;  /* bit[4-4]  :  */
        unsigned int  ena5     : 1;  /* bit[5-5]  :  */
        unsigned int  ena6     : 1;  /* bit[6-6]  :  */
        unsigned int  ena7     : 1;  /* bit[7-7]  :  */
        unsigned int  ena8     : 1;  /* bit[8-8]  :  */
        unsigned int  ena9     : 1;  /* bit[9-9]  :  */
        unsigned int  ena10    : 1;  /* bit[10-10]:  */
        unsigned int  reserved : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_ENA_UNION;
#endif
#define SOC_ISP_GCD_GEQ_ENA_ena0_START      (0)
#define SOC_ISP_GCD_GEQ_ENA_ena0_END        (0)
#define SOC_ISP_GCD_GEQ_ENA_ena1_START      (1)
#define SOC_ISP_GCD_GEQ_ENA_ena1_END        (1)
#define SOC_ISP_GCD_GEQ_ENA_ena2_START      (2)
#define SOC_ISP_GCD_GEQ_ENA_ena2_END        (2)
#define SOC_ISP_GCD_GEQ_ENA_ena3_START      (3)
#define SOC_ISP_GCD_GEQ_ENA_ena3_END        (3)
#define SOC_ISP_GCD_GEQ_ENA_ena4_START      (4)
#define SOC_ISP_GCD_GEQ_ENA_ena4_END        (4)
#define SOC_ISP_GCD_GEQ_ENA_ena5_START      (5)
#define SOC_ISP_GCD_GEQ_ENA_ena5_END        (5)
#define SOC_ISP_GCD_GEQ_ENA_ena6_START      (6)
#define SOC_ISP_GCD_GEQ_ENA_ena6_END        (6)
#define SOC_ISP_GCD_GEQ_ENA_ena7_START      (7)
#define SOC_ISP_GCD_GEQ_ENA_ena7_END        (7)
#define SOC_ISP_GCD_GEQ_ENA_ena8_START      (8)
#define SOC_ISP_GCD_GEQ_ENA_ena8_END        (8)
#define SOC_ISP_GCD_GEQ_ENA_ena9_START      (9)
#define SOC_ISP_GCD_GEQ_ENA_ena9_END        (9)
#define SOC_ISP_GCD_GEQ_ENA_ena10_START     (10)
#define SOC_ISP_GCD_GEQ_ENA_ena10_END       (10)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_WEI_1_UNION
 结构说明  : GEQ_WEI_1 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium WE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  geq_wei1 : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  geq_wei2 : 9;  /* bit[16-24]:  */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_WEI_1_UNION;
#endif
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei1_START  (0)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei1_END    (8)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei2_START  (16)
#define SOC_ISP_GCD_GEQ_WEI_1_geq_wei2_END    (24)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_WEI_2_UNION
 结构说明  : GEQ_WEI_2 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium WE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  geq_wei3 : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  geq_wei4 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_WEI_2_UNION;
#endif
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei3_START  (0)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei3_END    (8)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei4_START  (16)
#define SOC_ISP_GCD_GEQ_WEI_2_geq_wei4_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_THR_1_UNION
 结构说明  : GEQ_THR_1 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium thresolds
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  geq_thr1 : 10; /* bit[0-9]  :  */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  geq_thr2 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_THR_1_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr1_START  (0)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr1_END    (9)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr2_START  (16)
#define SOC_ISP_GCD_GEQ_THR_1_geq_thr2_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_THR_2_UNION
 结构说明  : GEQ_THR_2 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium thresolds
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  geq_thr3 : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  geq_thr4 : 12; /* bit[16-27]:  */
        unsigned int  reserved_1: 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_THR_2_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr3_START  (0)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr3_END    (8)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr4_START  (16)
#define SOC_ISP_GCD_GEQ_THR_2_geq_thr4_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GEQ_THR_3_UNION
 结构说明  : GEQ_THR_3 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: Green Equilibrium thresolds
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  geq_thr5 : 11; /* bit[0-10] :  */
        unsigned int  reserved_0: 5;  /* bit[11-15]:  */
        unsigned int  geq_thr6 : 11; /* bit[16-26]:  */
        unsigned int  reserved_1: 5;  /* bit[27-31]:  */
    } reg;
} SOC_ISP_GCD_GEQ_THR_3_UNION;
#endif
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr5_START  (0)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr5_END    (10)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr6_START  (16)
#define SOC_ISP_GCD_GEQ_THR_3_geq_thr6_END    (26)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_FCS_UNION
 结构说明  : FCS 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: False Color Suppression
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fcs_ena0 : 1;  /* bit[0-0]  :  */
        unsigned int  fcs_ena1 : 1;  /* bit[1-1]  :  */
        unsigned int  reserved_0: 6;  /* bit[2-7]  :  */
        unsigned int  fcs_wei1 : 5;  /* bit[8-12] :  */
        unsigned int  reserved_1: 3;  /* bit[13-15]:  */
        unsigned int  fcs_thr1 : 10; /* bit[16-25]:  */
        unsigned int  reserved_2: 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_GCD_FCS_UNION;
#endif
#define SOC_ISP_GCD_FCS_fcs_ena0_START  (0)
#define SOC_ISP_GCD_FCS_fcs_ena0_END    (0)
#define SOC_ISP_GCD_FCS_fcs_ena1_START  (1)
#define SOC_ISP_GCD_FCS_fcs_ena1_END    (1)
#define SOC_ISP_GCD_FCS_fcs_wei1_START  (8)
#define SOC_ISP_GCD_FCS_fcs_wei1_END    (12)
#define SOC_ISP_GCD_FCS_fcs_thr1_START  (16)
#define SOC_ISP_GCD_FCS_fcs_thr1_END    (25)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_CAC_EN_UNION
 结构说明  : CAC_EN 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Color Aberration Removal
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cac_ena0 : 1;  /* bit[0-0]  :  */
        unsigned int  reserved_0: 1;  /* bit[1-1]  :  */
        unsigned int  cac_ena2 : 1;  /* bit[2-2]  :  */
        unsigned int  cac_ena3 : 1;  /* bit[3-3]  :  */
        unsigned int  cac_ena4 : 1;  /* bit[4-4]  :  */
        unsigned int  cacgena0 : 1;  /* bit[5-5]  :  */
        unsigned int  cacgena1 : 1;  /* bit[6-6]  :  */
        unsigned int  reserved_1: 1;  /* bit[7-7]  :  */
        unsigned int  cac_rad2 : 21; /* bit[8-28] :  */
        unsigned int  reserved_2: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_GCD_CAC_EN_UNION;
#endif
#define SOC_ISP_GCD_CAC_EN_cac_ena0_START  (0)
#define SOC_ISP_GCD_CAC_EN_cac_ena0_END    (0)
#define SOC_ISP_GCD_CAC_EN_cac_ena2_START  (2)
#define SOC_ISP_GCD_CAC_EN_cac_ena2_END    (2)
#define SOC_ISP_GCD_CAC_EN_cac_ena3_START  (3)
#define SOC_ISP_GCD_CAC_EN_cac_ena3_END    (3)
#define SOC_ISP_GCD_CAC_EN_cac_ena4_START  (4)
#define SOC_ISP_GCD_CAC_EN_cac_ena4_END    (4)
#define SOC_ISP_GCD_CAC_EN_cacgena0_START  (5)
#define SOC_ISP_GCD_CAC_EN_cacgena0_END    (5)
#define SOC_ISP_GCD_CAC_EN_cacgena1_START  (6)
#define SOC_ISP_GCD_CAC_EN_cacgena1_END    (6)
#define SOC_ISP_GCD_CAC_EN_cac_rad2_START  (8)
#define SOC_ISP_GCD_CAC_EN_cac_rad2_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_CAC_CEN_UNION
 结构说明  : CAC_CEN 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: Color Aberration Removal
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cac_cen1 : 14; /* bit[0-13] :  */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  cac_cen2 : 13; /* bit[16-28]:  */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_GCD_CAC_CEN_UNION;
#endif
#define SOC_ISP_GCD_CAC_CEN_cac_cen1_START  (0)
#define SOC_ISP_GCD_CAC_CEN_cac_cen1_END    (13)
#define SOC_ISP_GCD_CAC_CEN_cac_cen2_START  (16)
#define SOC_ISP_GCD_CAC_CEN_cac_cen2_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_CAC_RAD_UNION
 结构说明  : CAC_RAD 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: Color Aberration Removal
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cac_rad1 : 13; /* bit[0-12] :  */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_GCD_CAC_RAD_UNION;
#endif
#define SOC_ISP_GCD_CAC_RAD_cac_rad1_START  (0)
#define SOC_ISP_GCD_CAC_RAD_cac_rad1_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_CAC_WEI_UNION
 结构说明  : CAC_WEI 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: Color Aberration Removal
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cac_wei1 : 8;  /* bit[0-7]  :  */
        unsigned int  cac_wei2 : 6;  /* bit[8-13] :  */
        unsigned int  reserved : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_GCD_CAC_WEI_UNION;
#endif
#define SOC_ISP_GCD_CAC_WEI_cac_wei1_START  (0)
#define SOC_ISP_GCD_CAC_WEI_cac_wei1_END    (7)
#define SOC_ISP_GCD_CAC_WEI_cac_wei2_START  (8)
#define SOC_ISP_GCD_CAC_WEI_cac_wei2_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_CAC_THR_UNION
 结构说明  : CAC_THR 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cac_cho1 : 2;  /* bit[0-1]  :  */
        unsigned int  cac_cho2 : 2;  /* bit[2-3]  :  */
        unsigned int  cac_cho3 : 3;  /* bit[4-6]  :  */
        unsigned int  reserved_0: 9;  /* bit[7-15] :  */
        unsigned int  cac_thr  : 13; /* bit[16-28]:  */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_GCD_CAC_THR_UNION;
#endif
#define SOC_ISP_GCD_CAC_THR_cac_cho1_START  (0)
#define SOC_ISP_GCD_CAC_THR_cac_cho1_END    (1)
#define SOC_ISP_GCD_CAC_THR_cac_cho2_START  (2)
#define SOC_ISP_GCD_CAC_THR_cac_cho2_END    (3)
#define SOC_ISP_GCD_CAC_THR_cac_cho3_START  (4)
#define SOC_ISP_GCD_CAC_THR_cac_cho3_END    (6)
#define SOC_ISP_GCD_CAC_THR_cac_thr_START   (16)
#define SOC_ISP_GCD_CAC_THR_cac_thr_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCAC_CTRL_UNION
 结构说明  : GCAC_CTRL 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: Global CAC Control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gcac_enable      : 1;  /* bit[0-0] :  */
        unsigned int  gcac_v_clip_mode : 2;  /* bit[1-2] :  */
        unsigned int  gcac_h_clip_mode : 1;  /* bit[3-3] :  */
        unsigned int  cv_mask          : 2;  /* bit[4-5] :  */
        unsigned int  reserved         : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_GCD_GCAC_CTRL_UNION;
#endif
#define SOC_ISP_GCD_GCAC_CTRL_gcac_enable_START       (0)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_enable_END         (0)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_v_clip_mode_START  (1)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_v_clip_mode_END    (2)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_h_clip_mode_START  (3)
#define SOC_ISP_GCD_GCAC_CTRL_gcac_h_clip_mode_END    (3)
#define SOC_ISP_GCD_GCAC_CTRL_cv_mask_START           (4)
#define SOC_ISP_GCD_GCAC_CTRL_cv_mask_END             (5)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCAC_NORM_UNION
 结构说明  : GCAC_NORM 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: X,Y scaling and normalization factor
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_nf     : 5;  /* bit[0-4]  :  */
        unsigned int  reserved_0: 3;  /* bit[5-7]  :  */
        unsigned int  x_ns     : 4;  /* bit[8-11] :  */
        unsigned int  reserved_1: 4;  /* bit[12-15]:  */
        unsigned int  y_nf     : 5;  /* bit[16-20]:  */
        unsigned int  reserved_2: 3;  /* bit[21-23]:  */
        unsigned int  y_ns     : 4;  /* bit[24-27]:  */
        unsigned int  reserved_3: 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_GCD_GCAC_NORM_UNION;
#endif
#define SOC_ISP_GCD_GCAC_NORM_x_nf_START      (0)
#define SOC_ISP_GCD_GCAC_NORM_x_nf_END        (4)
#define SOC_ISP_GCD_GCAC_NORM_x_ns_START      (8)
#define SOC_ISP_GCD_GCAC_NORM_x_ns_END        (11)
#define SOC_ISP_GCD_GCAC_NORM_y_nf_START      (16)
#define SOC_ISP_GCD_GCAC_NORM_y_nf_END        (20)
#define SOC_ISP_GCD_GCAC_NORM_y_ns_START      (24)
#define SOC_ISP_GCD_GCAC_NORM_y_ns_END        (27)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCAC_A_UNION
 结构说明  : GCAC_A 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a_red    : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  a_blue   : 9;  /* bit[16-24]:  */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_GCD_GCAC_A_UNION;
#endif
#define SOC_ISP_GCD_GCAC_A_a_red_START     (0)
#define SOC_ISP_GCD_GCAC_A_a_red_END       (8)
#define SOC_ISP_GCD_GCAC_A_a_blue_START    (16)
#define SOC_ISP_GCD_GCAC_A_a_blue_END      (24)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCAC_B_UNION
 结构说明  : GCAC_B 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_red    : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  b_blue   : 9;  /* bit[16-24]:  */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_GCD_GCAC_B_UNION;
#endif
#define SOC_ISP_GCD_GCAC_B_b_red_START     (0)
#define SOC_ISP_GCD_GCAC_B_b_red_END       (8)
#define SOC_ISP_GCD_GCAC_B_b_blue_START    (16)
#define SOC_ISP_GCD_GCAC_B_b_blue_END      (24)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_GCAC_C_UNION
 结构说明  : GCAC_C 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  c_red    : 9;  /* bit[0-8]  :  */
        unsigned int  reserved_0: 7;  /* bit[9-15] :  */
        unsigned int  c_blue   : 9;  /* bit[16-24]:  */
        unsigned int  reserved_1: 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_GCD_GCAC_C_UNION;
#endif
#define SOC_ISP_GCD_GCAC_C_c_red_START     (0)
#define SOC_ISP_GCD_GCAC_C_c_red_END       (8)
#define SOC_ISP_GCD_GCAC_C_c_blue_START    (16)
#define SOC_ISP_GCD_GCAC_C_c_blue_END      (24)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_LSC_TABLE_ACTIVE_UNION
 结构说明  : LSC_TABLE_ACTIVE 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: select active table:
            0: LSC_LUT_0 is used by the HW
            1: LSC_LUT_1 is used by the HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsc_table_active : 1;  /* bit[0-0] :  */
        unsigned int  reserved         : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_GCD_LSC_TABLE_ACTIVE_UNION;
#endif
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_lsc_table_active_START  (0)
#define SOC_ISP_GCD_LSC_TABLE_ACTIVE_lsc_table_active_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_LSC_LUT_0_UNION
 结构说明  : LSC_LUT_0 寄存器结构定义。地址偏移量:0x0100+0x4*(Range256)，初值:0x00000000，宽度:32
 寄存器说明: LookUp Table, 256 entries
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lcsgain  : 11; /* bit[0-10] :  */
        unsigned int  reserved : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_GCD_LSC_LUT_0_UNION;
#endif
#define SOC_ISP_GCD_LSC_LUT_0_lcsgain_START   (0)
#define SOC_ISP_GCD_LSC_LUT_0_lcsgain_END     (10)


/*****************************************************************************
 结构名    : SOC_ISP_GCD_LSC_LUT_1_UNION
 结构说明  : LSC_LUT_1 寄存器结构定义。地址偏移量:0x0500+0x4*(Range256)，初值:0x00000000，宽度:32
 寄存器说明: LookUp Table, 256 entries
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lcsgain  : 11; /* bit[0-10] :  */
        unsigned int  reserved : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_GCD_LSC_LUT_1_UNION;
#endif
#define SOC_ISP_GCD_LSC_LUT_1_lcsgain_START   (0)
#define SOC_ISP_GCD_LSC_LUT_1_lcsgain_END     (10)




/****************************************************************************
                     (2/2) STATDIS
 ****************************************************************************/




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

#endif /* end of soc_isp_gcd_interface.h */
