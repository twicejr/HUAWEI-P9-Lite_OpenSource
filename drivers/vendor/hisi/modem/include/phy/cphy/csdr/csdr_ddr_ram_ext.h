/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : csdr_ddr_ram_ext.h
  版 本 号   : 初稿
  作    者   : 常宝 00184186
  生成日期   : 2013年9月30日
  最近修改   :
  功能描述   : 定义ZSP使用的外部DDR地址的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月30日
    作    者   : 常宝 00184186
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CSDR_DDR_RAM_EXT_H__
#define __CSDR_DDR_RAM_EXT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CSDR_DDR_RAM_MAX_SIZE               ( 0x10000 )                         /* CTTF-CSDR共享DDR总空间大小为64k，4K字节对齐 */
#define CSDR_DDR_HARQ_RAM_MAX_SIZE          ( 0x10000 )                         /* CSDR HARQ需要的DDR总空间大小为64k，4K字节对齐 */

/****************************************************************************
 *                     ZSP使用DDR中地址的定义                               *
 *                                                                          *
*****************************************************************************/
/*************** HRPD DDR中SDR与CTTF的共享数据地址 ****************/
#define CSDR_CTTF_HRPD_REQUIRE_LEN          ( 0x4 )     /* 单位:Byte */
#define CSDR_CTTF_HRPD_F_DATA_BUFFER_LEN    ( 0xF00 )   /* 下行共有6片数据buffer，每片大小为640 Byte，共3840 Byte */
#define CSDR_CTTF_HRPD_R_DATA_BUFFER_LEN    ( 0x600 )   /* 上行最大的MAC layer packet为12288 bit，即1536 Byte */

#define CSDR_HRPD_DDR_RAM_BASE              ( CSDR_DDR_RAM_BASE + 0x0 )

/**
 * This address is used to require share-memory address between SDR and MAC in
 * HRPD. To read it, user can know where to inquire the address of
 * CSDR_HRPD_ADDR_INFO_STRU. The start address of CSDR_HRPD_ADDR_INFO_STRU is
 * stored into CSDR_HRPD_REQUIRE_ADDR. So user first read the address stored in
 * CSDR_HRPD_ADDR_INFO_STRU, then jump to CSDR_HRPD_ADDR_INFO_STRU. It's
 * familiar with HSUPA and 1x.
 */
#define CSDR_HRPD_REQUIRE_ADDR              ( CSDR_HRPD_DDR_RAM_BASE )

/* HRPD, CTTF与CSDR 下行decode,译码数据对应 buffer */
#define CSDR_CTTF_HRPD_F_DATA_BUFFER_ADDR   (  CSDR_HRPD_REQUIRE_ADDR \
                                             + CSDR_CTTF_HRPD_REQUIRE_LEN )

/* HRPD, CTTF与CSDR 上行encode, MAC层包的buffer */
#define CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR   ( CSDR_CTTF_HRPD_F_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_HRPD_F_DATA_BUFFER_LEN )


/*************** 1X DDR中SDR与CTTF的共享数据地址 ****************/
#define CSDR_CTTF_1X_REQUIRE_LEN            ( 0x4 )
#define CSDR_CTTF_1X_F_DATA_BUFFER_LEN      ( 0xA48 )
#define CSDR_DDR_RAM_FCH_PING_LEN           ( 0x300 )
#define CSDR_DDR_RAM_FCH_PANG_LEN           ( 0x300 )
#define CSDR_DDR_RAM_SCH_PING_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCH_PANG_LEN           ( 0x3000 )
#define CSDR_DDR_RAM_SCCH_PING_LEN          ( 0x180 )
#define CSDR_DDR_RAM_SCCH_PANG_LEN          ( 0x180 )
#define CSDR_DDR_RAM_DCCH_PING_LEN          ( 0x300 )
#define CSDR_DDR_RAM_DCCH_PANG_LEN          ( 0x300 )
#define CSDR_DDR_RAM_BCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_BCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PING_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_CCCH_PANG_LEN          ( 0xC00 )
#define CSDR_DDR_RAM_PCH_PING_LEN           ( 0x180 )
#define CSDR_DDR_RAM_PCH_PANG_LEN           ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PING_LEN         ( 0x180 )
#define CSDR_DDR_RAM_SYNCH_PANG_LEN         ( 0x180 )

/* 1X和HRPD地址间隔*/
#define CSDR_DDR_RAM_HRPD_1X_PROTECTION_LEN ( 0x10 )

/* 1X的DDR共享数据地址排在HRPD之后 */
#define CSDR_1X_DDR_RAM_BASE                ( CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_HRPD_R_DATA_BUFFER_LEN \
                                             + CSDR_DDR_RAM_HRPD_1X_PROTECTION_LEN )


/* CTTF与SDR 下行decode和上行encode头部地址信息,对应结构CTTF_CSDR_1X_ADDR_INFO_STRU */
#define CSDR_CTTF_1X_REQUIRE_ADDR           ( CSDR_1X_DDR_RAM_BASE )

/**
 * This address is used to require share-memory address between SDR and MAC in
 * 1x. To read it, user can know where to inquire the address of
 * CTTF_CSDR_1X_ADDR_INFO_STRU. The start address of
 * CTTF_CSDR_1X_ADDR_INFO_STRU is stored into CTTF_CSDR_1X_REQUIRE_ADDR. So
 * user first read the address stored in CTTF_CSDR_1X_REQUIRE_ADDR, then jump
 * to CTTF_CSDR_1X_ADDR_INFO_STRU. It's familiar with HSUPA.
 */
#define CTTF_CSDR_1X_REQUIRE_ADDR           ( CSDR_CTTF_1X_REQUIRE_ADDR )

/* CTTF与SDR 下行decode,译码数据对应 buffer 对应结构CSDR_CTTF_1X_F_DATA_BUFFER_STRU */
#define CSDR_CTTF_1X_F_DATA_BUFFER_ADDR     (  CSDR_CTTF_1X_REQUIRE_ADDR \
                                             + CSDR_CTTF_1X_REQUIRE_LEN )

/* DPP输出FCH信道LLR结果ping存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_FCH_PING_ADDR          (  CSDR_CTTF_1X_F_DATA_BUFFER_ADDR \
                                             + CSDR_CTTF_1X_F_DATA_BUFFER_LEN )

/* DPP输出FCH信道LLR结果pang存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_FCH_PANG_ADDR          (  CSDR_DDR_RAM_FCH_PING_ADDR \
                                             + CSDR_DDR_RAM_FCH_PING_LEN )

//#if ( _CHIP_BB_HI6250CS == _DSP_CHIP_BB_TYPE )
#if 0
/* DALLAS版本动态右移在BBP中已经实现 */
/* DPP输出SCH信道LLR结果ping存放空间, 总大小12288个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SCH_PING_ADDR          (  CSDR_DDR_RAM_FCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

#else
/* 非DALLAS版本动态右移暂时还需软件规避 */
/* 增加1个FCH LLR空间，分别存放 */
/* DPP输出FCH信道LLR结果ping存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_FCH_PING_RSHIFT1_ADDR  (  CSDR_DDR_RAM_FCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

/* DPP输出FCH信道LLR结果pang存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_FCH_PANG_RSHIFT1_ADDR  (  CSDR_DDR_RAM_FCH_PING_RSHIFT1_ADDR \
                                             + CSDR_DDR_RAM_FCH_PING_LEN )

/* DPP输出SCH信道LLR结果ping存放空间, 总大小12288个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SCH_PING_ADDR          (  CSDR_DDR_RAM_FCH_PANG_RSHIFT1_ADDR \
                                             + CSDR_DDR_RAM_FCH_PANG_LEN )

#endif

/* DPP输出SCH信道LLR结果pang存放空间, 总大小12288个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SCH_PANG_ADDR          (  CSDR_DDR_RAM_SCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCH_PING_LEN )

/* DPP输出SCCH信道LLR结果ping存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SCCH_PING_ADDR         (  CSDR_DDR_RAM_SCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCH_PANG_LEN )

/* DPP输出SCCH信道LLR结果pang存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SCCH_PANG_ADDR         (  CSDR_DDR_RAM_SCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PING_LEN )

/* DPP输出DCCH信道LLR结果ping存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_DCCH_PING_ADDR         (  CSDR_DDR_RAM_SCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SCCH_PANG_LEN )

/* DPP输出DCCH信道LLR结果pang存放空间, 总大小768个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_DCCH_PANG_ADDR         (  CSDR_DDR_RAM_DCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PING_LEN )

/* DPP输出BCCH信道LLR结果ping存放空间, 总大小3072个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_BCCH_PING_ADDR         (  CSDR_DDR_RAM_DCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_DCCH_PANG_LEN )

/* DPP输出BCCH信道LLR结果pang存放空间, 总大小3072个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_BCCH_PANG_ADDR         (  CSDR_DDR_RAM_BCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PING_LEN )

/* DPP输出CCCH信道LLR结果ping存放空间, 总大小3072个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_CCCH_PING_ADDR         (  CSDR_DDR_RAM_BCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_BCCH_PANG_LEN )

/* DPP输出CCCH信道LLR结果pang存放空间, 总大小3072个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_CCCH_PANG_ADDR         (  CSDR_DDR_RAM_CCCH_PING_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PING_LEN )

/* DPP输出PCH信道LLR结果ping存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_PCH_PING_ADDR          (  CSDR_DDR_RAM_CCCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_CCCH_PANG_LEN )

/* DPP输出PCH信道LLR结果pang存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_PCH_PANG_ADDR          (  CSDR_DDR_RAM_PCH_PING_ADDR \
                                             + CSDR_DDR_RAM_PCH_PING_LEN )

/* DPP输出SYNCH信道LLR结果ping存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SYNCH_PING_ADDR        (  CSDR_DDR_RAM_PCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_PCH_PANG_LEN )

/* DPP输出SYNCH信道LLR结果pang存放空间, 总大小384个symbol，每个symbol占8bit */
#define CSDR_DDR_RAM_SYNCH_PANG_ADDR        (  CSDR_DDR_RAM_SYNCH_PING_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PING_LEN )

/* CTTF与ENC编码前数据存放空间 */
#define CTTF_CSDR_1X_R_DATA_BUFFER_ADDR     ( CSDR_DDR_RAM_SYNCH_PANG_ADDR \
                                             + CSDR_DDR_RAM_SYNCH_PANG_LEN )

//#if ( CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR % 4 != 0 )
//#error "CSDR_CTTF_HRPD_R_DATA_BUFFER_ADDR needs to be 4 byte aligned!"
//#endif
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


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/












#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of csdr_ddr_ram_ext.h */

