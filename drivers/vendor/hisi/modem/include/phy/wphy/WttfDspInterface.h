/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : WttfDspInterface.h
  版 本 号   : V1.00
  作    者   : 查鸣峰
  生成日期   : 2007年7月13日
  最近修改   :
  功能描述   : WttfDspInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2007年7月13日
    作    者   : 查鸣峰
    修改内容   : 创建文件

  2.日    期   : 2007年10月10日
    作    者   : 查鸣峰
    修改内容   : 根据讨论的新接口方案，ARM只与DSP存在接口，
                 ARM与BBP无接口，更新用户面接口

  3.日    期   : 2008年02月25日
    作    者   : 查鸣峰
    修改内容   : 增加HSUPA接口

  3.日    期   : 2008年5月20日
    作    者   : changyuhui
    修改内容   : AT2D003457

  4.日    期   : 2008年6月17日
    作    者   : shijieke
    修改内容   : 在WTTFPHY_MAC_DPCCH_PWR_IND_STRU消息中添加网络侧限制最大
                 上行发射功率sAllowUlMaxPower接口
******************************************************************************/

#ifndef __WTTFDSPINTERFACE_H__
#define __WTTFDSPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "WUeSpec.h"
#include "DspInterface.h"
#include "product_config.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define WTTFPHY_WAIT_WTTF_NEW_MACE_ACTIVE_FLAG          (0x33553355)
#define WTTFPHY_NOTICE_WTTF_MACE_REL_FLAG               (0x55335533)

#define WTTFPHY_SLOT_NUM_PER_FRAME                  (15)            /*每帧时隙数是15个*/
#define WTTFPHY_IVALID_TX_POWER                     (0x7fff)        /* DSP上报的表示无效值的发射功率 */

#define WTTFPHY_INVALID_SFN                         (0xffff)        /*无效SFN*/


/* MAC E 规格定义 */
#define WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM                (4)             /* 协议栈 与DSP 协定好的MAC E/I 实体 信令RB个数 */

#define WTTFPHY_MAC_UPA_MAX_CS_RB_NUM                 (3)             /* 协议栈 与DSP 协定好的MAC E 实体 CS RB个数 */

#define WTTFPHY_MAC_UPA_MAX_PS_RB_NUM                 (5)             /* 协议栈 与DSP 协定好的MAC E 实体 业务RB个数:
                                                                    V3R2/V7, PS RB个数扩展为5个
                                                                    当协议栈配置DSP的个数大于WTTFPHY_MAC_UPA_MAX_PS_RB_NUM 时，DSP会做检查，返回配置失败 */



/*R4相关功能宏定义*/
#define WTTFPHY_MAX_PHY_DATA_REQ_HEAD_CTRL_LEN      (52)            /* 单位:字节,ID_MAC_PHY_DATA_REQ原语控制头长度*/
#define WTTFPHY_MAX_PHY_DATA_REQ_LEN                (1024)          /* MAC_PHY_DATA_REQ R99数据最大长度,384*1024/(100*8) = 491(BYTE),为保留余量，取值1024 */
#define WTTFPHY_MAX_PHY_DATA_REQ_EXPT_CTRL_LEN      (36)            /* 单位:字节,ID_MAC_PHY_DATA_REQ原语异常控制部分长度*/
#define WTTFPHY_MAX_PHY_DATA_REQ_RESERVE_LEN        (36)                        /* 单位:字节,ID_MAC_PHY_DATA_REQ原语保留部分长度，供扩展使用*/

/* 1152,单位:字节,ID_MAC_PHY_DATA_REQ原语占用邮箱空间总长度 */
#define WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN          ((WTTFPHY_MAX_PHY_DATA_REQ_HEAD_CTRL_LEN) \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_LEN)           \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_EXPT_CTRL_LEN) \
                                                    +(WTTFPHY_MAX_PHY_DATA_REQ_RESERVE_LEN))

#define WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN        (4)                         /* 邮箱1总体的互斥标志，占4字节 */
#define WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN       (4)                         /* 邮箱2总体的互斥标志，占4字节 */

/* BBP译码数据各RAM大小 */
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_HEAD_LEN     (24*4)          /* 单位:字节,PHY_MAC_DATA_IND TURBO译码 RAM控制信息最大长度*/
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN     (256*4)         /* PHY_MAC_DATA_IND 数据最大长度,单位字节:256*4,256－Turbo译码数据区空间,BBP规格  */

/* 单位:字节,PHY_MAC_DATA_IND TURBO译码RAM总邮箱空间总长度,BBP规格 */
#define WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN    ( (WTTFPHY_MAX_PHY_DATA_IND_TURBO_HEAD_LEN) \
                                                    + (WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN))

#define WTTFPHY_MAX_VTB_RAM_LEN                     (128*4)         /* 单位:字节,PHY_MAC_DATA_IND 维特比译码 RAM总空间长度,BBP规格  */
#define WTTFPHY_MAX_VTB_BCH_LEN                     (32*4)          /* 单位:字节,BBP提供的维特比译码空间中PCCPCH(也即系统信息)占据32个字(32bit)，这部分BBP直接提供给WRR，WTTF用户面接口不涉及。*/
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN       (24*4)          /* 单位:字节,PHY_MAC_DATA_IND 维特比译码 RAM控制信息最大长度 */
/*单位:字节,PHY_MAC_DATA_IND 维特比译码数据部分占用邮箱空间最大长度 */
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN       ((WTTFPHY_MAX_VTB_RAM_LEN   \
                                                    - WTTFPHY_MAX_VTB_BCH_LEN)  \
                                                    - WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN)

/* 单位:字节,PHY_MAC_DATA_IND 维特比译码RAM去掉PCCPCH译码数据后占用邮箱总空间长度,BBP规格  */
#define WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN      ( (WTTFPHY_MAX_PHY_DATA_IND_VTB_HEAD_LEN)   \
                                                    + (WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN))

#define WTTFPHY_MAX_AMR_DATA_REQ_LEN                (256-8)                     /* 单位:字节,PHY_RLC_AMR_DATA_REQ 数据最大长度，实际所需36个字节，这里留有余量,8个字节是控制头长度 */
#define WTTFPHY_MAX_AMR_DATA_REQ_TOTAL_LEN          (WTTFPHY_MAX_AMR_DATA_REQ_LEN + 8)          /* 单位:字节,PHY_RLC_AMR_DATA_REQ原语占用邮箱总空间长度,8个字节是控制头长度 */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_LEN         (256-8)                     /* 单位:字节,WTTFPHY_MAC_DL_AMR_DECIPHER_BUF 数据最大长度，实际所需36个字节，这里留有余量,8个字节是控制头长度 */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_TOTAL_LEN   (WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_LEN + 8)          /* 单位:字节,WTTFPHY_MAC_DL_AMR_DECIPHER_BUF原语占用邮箱总空间长度,8个字节是控制头长度  */
#define WTTFPHY_MAX_AMR_DATA_IND_LEN                (256-8)                     /* 单位:字节,MAC_PHY_AMR_DATA_IND 数据最大长度，实际所需36个字节，这里留有余量,8个字节是控制头长度 */

#define WTTFPHY_MAX_TFC_BCBD_IND_TOTAL_LEN          (8 + ( PS_WUE_MAX_UL_TFC_NUM * 2 ) )

#define WTTFPHY_MAX_DPCCH_PWR_IND_LEN               (36)                        /* 单位:字节*/
#define WTTFPHY_MAX_DPCCH_PWR_IND_TOTAL_LEN         (WTTFPHY_MAX_DPCCH_PWR_IND_LEN) /* 单位:字节*/
#define WTTFPHY_MAX_BETA_HS_IND_LEN                 8
#define WTTFPHY_MAX_BETA_HS_IND_RESERVE_LEN         (72)                        /* 单位:字节*/
#define WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN           ( WTTFPHY_MAX_BETA_HS_IND_LEN                \
                                                    + WTTFPHY_MAX_BETA_HS_IND_RESERVE_LEN)

#define WTTFPHY_MAX_MAIL_BOX_RESERVE_LEN            (512)                       /* 单位:字节*/
#define WTTFPHY_MAX_MAIL_BOX_TOTAL_LEN              ( WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN        \
                                                    + WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN       \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN  \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN    \
                                                    + WTTFPHY_MAX_AMR_DATA_REQ_TOTAL_LEN        \
                                                    + WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_TOTAL_LEN        \
                                                    + WTTFPHY_MAX_TFC_BCBD_IND_TOTAL_LEN        \
                                                    + WTTFPHY_MAX_DPCCH_PWR_IND_TOTAL_LEN       \
                                                    + WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN         \
                                                    + WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN      \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN  \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN)       /* 单位:字节 */


#define WTTFPHY_MAC_PHY_DATA_REQ_ADDR               (ARM_DSP_R99_DATA_BASE_ADDR)

/* 第1块译码邮箱地址 */
#define WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR       ( WTTFPHY_MAC_PHY_DATA_REQ_ADDR             \
                                                    + WTTFPHY_MAX_PHY_DATA_REQ_TOTAL_LEN)

#define WTTFPHY_MAC_DATA_IND_FIRST_TURBO_ADDR       ( WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_ADDR      \
                                                    + WTTFPHY_MAC_DATA_IND_FIRST_MUTEX_LEN)

#define WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR         ( WTTFPHY_MAC_DATA_IND_FIRST_TURBO_ADDR     \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN)

/* BELTA hs 对应地址 */
#define WTTFPHY_MAC_BETA_HS_IND_ADDR                ( WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR       \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_VTB_TOTAL_LEN)

/* 第2块译码邮箱地址 */
#define WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR       ( WTTFPHY_MAC_BETA_HS_IND_ADDR              \
                                                    + WTTFPHY_MAX_BETA_HS_IND_TOTAL_LEN)

#define WTTFPHY_MAC_DATA_IND_SECOND_TURBO_ADDR      ( WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_ADDR     \
                                                    + WTTFPHY_MAC_DATA_IND_SECOND_MUTEX_LEN)

#define WTTFPHY_MAC_DATA_IND_SECOND_VTB_ADDR        ( WTTFPHY_MAC_DATA_IND_SECOND_TURBO_ADDR    \
                                                    + WTTFPHY_MAX_PHY_DATA_IND_TURBO_TOTAL_LEN)


/**********************************************************************************
    R5 HSDPA interface start
**********************************************************************************/
/*(8 + 3 + 1),按照最大进程数应定义8，为降低由于ARM处理性能带来的丢数概率，增加3块，
  另外,实现队列需要判断队列满而增加额外的1块 */
#define WTTFPHY_MAX_HS_PDU_BUF_NUM              (12)

/* 单位:字节,我司UE 7.2Mbps能力上报为等级8， 3.6Mbps能力上报为等级5，14.4Mbps能力上报为等级10，
   BalongV3支持的规格是14.4Mbps，对应等级为10，对应协议上定义的MAC-HS PDU最大为27952 bit,
   为确保是4字节的整数倍，定义为27968 bit，也即3496个字节,也即874字(32bit) */
#define WTTFPHY_MAX_HS_PDU_LEN                  (3496)


/* 由于采用硬件解MAC HS头方案，每个MAC-HS 头协议字段都要以字节为单位存放，而引入
   的额外增加空间计算如下:
   MAC-HS字段   实际所需空间(bit)     硬件解头方案  组数  硬件解头方案增加
                                      需要空间(bit)       空间长度（bit）
 V、QUEUE ID、TSN     10                     32       1        22
 N SID                10                     32       8        176
 CT                   4                      32       70       1960
 凑足4字节            1                      32       70       2170

 额外增加空间为:22+176+1960+2170 = 4328(bit) = 541(BYTE),考虑到能被4整除，
 因此,最后取值:544(BYTE) = 136 (32bit WORD)      */
#define WTTFPHY_MAX_HS_PDU_BUF_LEN              ( WTTFPHY_MAX_HS_PDU_LEN + 544 )/* 单位:字节, 支持7.2M为 2352 BYTE,588 WORD(32bit),
                                                                                支持14.4M为 4044 BYTE,1011 WORD(32bit) */

/*
#define WTTFPHY_MAC_HS_DATA_IND_CTRL_BUF_ADDR   (ARM_DSP_R5_SHARE_MEM_CTRL_BASE_ADDR)
*/
/**********************************************************************************
    R5 HSDPA interface end
**********************************************************************************/

/**********************************************************************************
    HSUPA interface start
**********************************************************************************/
/* 支持几个载波, 对这个变量可以增加一个编译开关 */
#if 0
#if (FEATURE_ON == FEATURE_DC_UPA)
#define PS_WUE_MAX_CARRIER_CNT                        (2)    /* Dual Carrier */
#else
#define PS_WUE_MAX_CARRIER_CNT                        (1)    /* Singal Carrier */
#endif
#endif

/*联调*/
#define PS_WUE_MAX_CARRIER_CNT                        (1)    /* Singal Carrier */

/*  V7支持 E-DCH category7, 每个载波上 即10ms TB_SIZE=20000 bit，考虑到 DSP是10ms就要取一次数据，
    考虑10ms TTI, ARM有能力实时下发数据, 所以缓存1个10ms TTI，即 20000/8 = 2500(Byte)
    10ms TTI只能是单载波 */
#define PS_WUE_MAX_E_DCH_10MS_PER_PS_RB_BUF_BYTE_SIZE    (2500)

/*  V7支持 E-DCH category9, 即2ms TB_SIZE=22996 bit，考虑到 DSP是2ms就要取一次数据，
    所以缓存需要额外多处一些用来保证DSP有数据可取，经过推导，缓存需要达到
    8个2ms TTI，即 22996*8/8 = 22,996(Byte)*/
#define PS_WUE_MAX_E_DCH_2MS_PER_PS_RB_BUF_BYTE_SIZE     ((VOS_UINT32)(20000)*(PS_WUE_MAX_CARRIER_CNT))

#define PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE         (PS_WUE_MAX_E_DCH_2MS_PER_PS_RB_BUF_BYTE_SIZE)


/* 每个信令RB缓存空间,单位:字节(DSP是16bit读写,DSP对于奇数地址需要特殊读取),
   13.6 Kbps(信令RB典型最高速率) * 4(对于10ms TTI,4个进程) * 8(最大重传次数) * 10 (10ms TTI)
   = 4352 bit = 544字节, 实际少使用1个字节，用来表达循环缓存满 */
#define PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE         (544)

/* CS域业务RB：对一个RB，UM RB准备一个TTI的数据,
   64Kbps(CS RB典型最高速率) * 8(对于2ms TTI,8个进程) * 10 (10ms TTI) = 640 bit = 80Byte */
#define PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE         (80)

/*  假设一个信令数据量是27.2kbps, 10ms内准备的数据量: 27200bits / (1000ms/10ms) = 272bits
    以协议上最小rlc pdu大小16bits为例(考虑信号极其恶劣场景)
    需要准备rlc pdu个数: 272bits/16bits  */
#define PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH             (20)

/*  假设一个CS域业务数据量是64kbps, 10ms内准备的数据量: 64000bits / (1000ms/10ms) = 640bits
    以协议上最小rlc pdu大小16bits为例(考虑信号极其恶劣场景)
    需要准备rlc pdu个数: 640bits/16bits */
#define PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH            (40)


/* 对单个载波, 如果是弹性size，按照category准备8个TTI，需要25558bit * 8个进程 / 640bit = 320个
   640bit是根据SE提供的DS中提及, 配置640bit以上时考虑峰值性能的达成 */
#define PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH            ((320) * (PS_WUE_MAX_CARRIER_CNT))


/* 物理层要数接口(G值)，要数缓存个数为8个 */
#define PS_WUE_MAC_E_DCH_STATUS_IND_BUF_SIZE                (8)

/* 当MAC没有历史G值时, 使用约定值来计算向RLC的要数量，约定值为发送10个Pdu的数据
   对于fixed pdu size, 按照144bit考虑, 对于flexible pdu size, 按照最小pdu档位size 176bit考虑
   一般都是在RRC刚好新配置PHY或者信号很差时, 因此取两者最小值144bit来设计, 10个pdu共1440bits
   注意此时无论是多载波还是单载波, 只按照单载波考虑 */
#define PS_WUE_E_DCH_STATUS_IND_DEFAULT_G                (1440)

/**********************************************************************************
    HSUPA interface end
**********************************************************************************/


/*V3 R7_7C1 Start */
/**********************************************************************************
    MAC-EHS PHY interface start
**********************************************************************************/
/* V5性能优化后，MAC只先将邮箱中MAC-ehs头部信息解析出来，待RLC解密时才配置CICOM将
   数据从邮箱中读出，考虑MAC-ehs rPdu乱序、均衡递交的因素，需要扩大邮箱规格。
   根据协议规定T1定时器的协议时长最大值为400ms，即MAC-ehs PDU译码数据在MAC-ehs
   重排序队列缓存中可能停留的最长时间为400ms。按照84Mbps协议规格，
   实际需要缓存的PDU个数 = 一个TTI内最大TB块数 * T1时间内的TTI数
                         =  (4 TB per TTI) * ( 400/2 )  = 800
   考虑内部时延需要做一定的均衡，扩展系数1.2，800 * 1.2 = 960 */
#if (FEATURE_OFF == FEATURE_DC_MIMO)
#define WTTFPHY_MAX_EHS_PDU_BUF_NUM             (440)    /* Mem Reduce */
#else
#define WTTFPHY_MAX_EHS_PDU_BUF_NUM             (880)
#endif

/* 单位:字节,HSPA+能力上报为等级14，
   对应协议上定义的MAC-EHS PDU最大为42192 bit,
   考虑BBPMASTER要求8字节的整数倍，取42240 bit,即5280个字节,也即1320字(32bit) */
#define WTTFPHY_MAX_EHS_PDU_LEN                 (5280)

/* 由于采用硬件解MAC EHS头方案，每个MAC-EHS 头协议字段都要以字节为单位存放，而引入
   的额外增加空间计算如下:
   MAC-EHS字段   实际所需空间(bit)     硬件解头方案  组数  硬件解头方案增加需要空间长度(bit)

 BCCH指示，rPDU总数   0                      32       1        32
 TSN,SI               16                     32       3        48
 LCH-ID,LI,F          16                     32       44       704
 RLC Header           16                     32       44       704
 凑足4字节            8                      32       44       1056
 (备注: 按照协议原则RLC SDU的长度为8Bit的整数倍,由于RLC SDU的长度为变长，不能确定其实际的
 空间开销，而实际可能占用的BIT数 8bit/16bit/24bit/32bit因此 为了保证空间足够，取最小的占用BIT
 来保证)
 额外增加空间为:32+48+704+704+1056 = 2544(bit) = 318(BYTE) 取4字节对齐为320Byte
*/
#define WTTFPHY_MAX_EHS_PDU_BUF_LEN             ( WTTFPHY_MAX_EHS_PDU_LEN + 320 )/* 单位:字节,5596 BYTE,1399 WORD(32bit) */

#define WTTFPHY_MAC_EHS_RPDU_MAX_NUM            (3)    /*the max number of rpdu*/

/*  if the TSN field extension is configured(此条件与DC+MIMO支持等价), 每个TTI内最多可达到44个RSDU
    按照V9R1芯片规格(仅支持DC)，rSdu个数最多只有26个
*/
#define WTTFPHY_MAC_EHS_RSDU_MAX_NUM            (26)   /*the max number of rsdu */

#define WTTFPHY_MAC_EHS_RSDUHEAD_PAD_LEN        (2)    /*每个RSDU头前面空出的两个字节 */

#define WTTFPHY_MAC_EHS_SDU_4BYTE_LEN           ((WTTFPHY_MAX_EHS_PDU_BUF_LEN/4) - 48)    /* 1344字(32bit),48:MAC-EHS协议头硬件解析后所占空间 */

#define WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_CTRL_BASE_ADDR)
/*
#define WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_CTRL_BASE_ADDR)
#define WTTFPHY_MAC_EHS_DATA_IND_DATA_BUF_ADDR  (ARM_DSP_R7_SHARE_MEM_DATA_BASE_ADDR)
*/
/* ========================================================================
   BBP Master方案中根据硬件提供的接口约束 R5和 R7的规格按照最大 EHS定义如下:
   TB HEAD 的大小为64 WORD 的整数倍 TB DATA的大小为1.5K WORD

   BBP和协议栈之间新的接口规定如下:
        8bit   8bit       8bit  8bit
        保留   BCCH/PCCH  RSDU  RPDU
        RPDU1  QUEUE ID   TSN1  SI1
        RPDU2  QUEUE ID   TSN2  SI2
        RPDU3  QUEUE ID   TSN3  SI3
        保留   LCH_ID1    L1(11bit)
        保留   LCH_ID2    L2
        保留   LCH_ID3    L3
        ...
        保留   LCH_ID44   L44              Total(48 WORD)
 =========================================================================*/
/* 与硬件的规格约定,片上SRAM头需要64 WORD详细结构如上表。按照V9R1芯片规格，TB Head大小由256字节裁剪为128字节 */
#define WTTFPHY_MAC_HSDPA_TB_HEAD_SIZE                  (128) /* 32 WORD = 128 Byte */

/* 计算方法 缓存 = 60ms / 2ms * 4(TTI内TB块的个数)
    具体的个数需要根据调测的具体值进行设定 */
#if (FEATURE_OFF == FEATURE_DC_MIMO)
#define WTTFPHY_MAC_HSDPA_TB_HEAD_NUM                   (440)  /* Mem Reduce */
#else
#define WTTFPHY_MAC_HSDPA_TB_HEAD_NUM                   (880)
#endif

/* 单位:字节,HSPA+能力上报为等级14，
   对应协议上定义的MAC-EHS PDU最大为42192 bit,即5274个字节
   考虑8字节的整数倍，取5280个字节,也即1320字(32bit)
   由于采用硬件解码，所有存储TB块数据需增加额外的空间，按照WTTFPHY_MAC_EHS_SDU_4BYTE_LEN计算，为5408字节
*/
#define WTTFPHY_MAC_HSDPA_TB_DATA_SIZE                  (WTTFPHY_MAC_EHS_SDU_4BYTE_LEN * 4)

/* TB头部黄线个数，预留3帧，即30块，再加上10块余量
   这样黄线大小为400，数据区块数与黄线值一致
*/
#if(FEATURE_ON == FEATURE_SMALL_MAILBOX)
#define WTTFPHY_MAC_HSDPA_TB_DATA_NUM                   (51) /* 出于CPU占有率考虑小邮箱方案只用在42M */
#else
    #if (FEATURE_OFF == FEATURE_DC_MIMO)
    #define WTTFPHY_MAC_HSDPA_TB_DATA_NUM               (440) /* 数据TB块的个数 */  /* Mem Reduce */
    #else
    #define WTTFPHY_MAC_HSDPA_TB_DATA_NUM               (880) /* 数据TB块的个数 */
    #endif
#endif

/**********************************************************************************
    MAC-EHS PHY interface end
**********************************************************************************/
/*WCDMA CS Transmission Delay Optimize begin*/

#define WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM       (3)
#define WTTF_PHY_DL_MAX_AMR_DECIPHER_KEY_BYTE_SIZE  (52) /* CLASS B 最大405bit = 52byte */
#define WTTF_PHY_DL_MAX_AMR_DECIPHER_PARAM_NUM      (3)

/*WCDMA CS Transmission Delay Optimize end*/

/* V3 R7_7C1 End */

/* 定义WTTF和PHY之间的API调用，包括回调函数，参数不超过8个 */
#define WTTFPHY_ITF_API_MAX_PARA_CNT                (8)

/*  一般在判断是否到达激活时间等场景，都是判断一个范围，
    而不是一个点，以提高软件的健壮性 */
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE          (12)
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE_DSDS     (20)
#define  WTTFPHY_CFG_ACT_CFN_PROTECT_RANGE_GCF      (8)

/* CBT模式中，R99 Mailbox VTB译码数据地址 */
#define WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_ZERO    (0)
#define WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_FIRST   (WTTFPHY_MAC_DATA_IND_FIRST_VTB_ADDR)
#define WTTFPHY_MAC_R99MAILBOX_VTB_ADDR_SECOND  (WTTFPHY_MAC_DATA_IND_SECOND_VTB_ADDR)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum WTTFPHY_CCTRCH_ENUM
{
    WTTFPHY_PCCPCH                      = 0,
    WTTFPHY_SCCPCH                      = 1,
    WTTFPHY_DL_DPCH                     = 2,
    WTTFPHY_PRACH                       = 3,
    WTTFPHY_UL_DPCH                     = 4,
    WTTFPHY_CCTRCH_BUTT
};
typedef VOS_UINT16 WTTFPHY_CCTRCH_ENUM_UINT16;


enum WTTFPHY_ACCESS_ENUM
{
    WTTFPHY_AICH_NACK                   = 0,                /* 物理层收到AICH NACK */
    WTTFPHY_AICH_ACK                    = 1,                /* 物理层收到AICH ACK，并且消息部分也发送成功 */
    WTTFPHY_AICH_NO_ACK                 = 2,                /* 物理层没有收到AICH的响应*/
    WTTFPHY_AICH_NO_PRACH               = 3,                /* a.PRACH信道不存在;
                                                                b.MAC_PHY_ACCESS_REQ参数错误，或者，物理层在异常的状态收到了MAC_PHY_ACCESS_REQ消息。MAC_PHY_ACCESS_REQ错误场景下，不再发起前导接入过程; */
    WTTFPHY_ACCESS_BUTT                                     /* 用这个统一的BUTT，作为最后一个枚举值。*/
} ;
typedef VOS_UINT16 WTTFPHY_ACCESS_ENUM_UINT16;


enum WTTFPHY_MUTEX_ENUM
{
    WTTFPHY_MUTEX_DATA_NOT_EXIST        = 0,                /* 共享变量中无数据，  可写，不可读;*/
    WTTFPHY_MUTEX_DATA_EXIST            = 1,                /* 共享变量中有数据，不可写，  可读;*/
    WTTFPHY_MUTEX_BUTT
};
typedef VOS_UINT16 WTTFPHY_MUTEX_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WTTFPHY_RF_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : RF是否存在标志
*****************************************************************************/
enum WTTFPHY_RF_ENUM
{
    WTTFPHY_RF_NOT_EXIST        = 0,                        /* RF资源不存在 */
    WTTFPHY_RF_EXIST            = 1,                        /* RF资源存在 */
    WTTFPHY_RF_BUTT
};
typedef VOS_UINT16 WTTFPHY_RF_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WTTFPHY_MAC_RESET_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 配置reset类型
*****************************************************************************/
enum WTTFPHY_MAC_RESET_TYPE_ENUM
{
    WTTFPHY_MAC_EHS_RESET                      = 0,            /* 指示reset mac ehs 实体*/
    WTTFPHY_MAC_RESET_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_MAC_RESET_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WTTFPHY_MAC_RESET_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MAC实体复位指示回复

*****************************************************************************/
enum WTTFPHY_MAC_RESET_RESULT_ENUM
{
    WTTFPHY_MAC_RESET_SUCCESS                  = 0,                /* MAC实体复位成功 */
    WTTFPHY_MAC_RESET_ERROR                    = 1,                /* MAC实体复位失败 */
    WTTFPHY_MAC_RESET_RESULT_BUTT
} ;
typedef VOS_UINT16 WTTFPHY_MAC_RESET_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WTTFPHY_MAC_STATUS_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 通知 MAC底层状态信息,收到后MAC停止本次发送

*****************************************************************************/
enum WTTFPHY_MAC_STATUS_IND_ENUM
{
    WTTFPHY_MAC_STATUS_IND_OUT_OF_SYNC                = 1,                 /* a L1 synchronisation failure */
    WTTFPHY_MAC_STATUS_IND_MAX_EDCH_RESOURCE          = 2,                  /* the maximum E-DCH resource allocation for CCCH */
    WTTFPHY_MAC_STATUS_IND_NO_MACI_FOR_TRANS          = 3,                 /* no MAC-i PDU for transmission */
    WTTFPHY_MAC_STATUS_IND_RL_RELEASE                 = 4,                 /* 信道释放(包含PHY链路释放和重配置) */
    WTTFPHY_MAC_STATUS_IND_MAX_PERIOD_COLLISION       = 5,                 /* the maximum  period for collision resolution and no E-AGCH with the UE's E-RNTI */
    WTTFPHY_MAC_STATUS_IND_EXPLICIT_RELEASE           = 6,                 /* explicit common E-DCH resource release */
    WTTFPHY_MAC_STATUS_IND_IMPLICIT_RELEASE           = 7,                 /* implicit common E-DCH resource release */
    WTTFPHY_MAC_STATUS_IND_BUTT                                           /* 用这个统一的BUTT，作为最后一个枚举值 */
};
typedef VOS_UINT16 WTTFPHY_MAC_STATUS_IND_ENUM_UINT16;


/*****************************************************************************
 枚举名    : WTTFPHY_MAC_STATUS_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 通知 MAC底层状态信息,收到后MAC停止本次发送

*****************************************************************************/
enum WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM
{
    WTTFPHY_UL_EFACH_LOCH_TYPE_CCCH                        = 1,                 /* 上行增强FACH发送使用CCCH逻辑信道类型 */
    WTTFPHY_UL_EFACH_LOCH_TYPE_DCCH_DTCH                   = 2,                 /* 上行增强FACH发送使用DCCH逻辑信道类型 */

    WTTFPHY_UL_EFACH_LOCH_TYPE_BUTT                                             /* 最后一个枚举值 */
};
typedef VOS_UINT16 WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : WTTFPHY_MAC_RACH_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 通知 MAC底层状态信息,收到后MAC停止本次发送

*****************************************************************************/
enum WTTFPHY_MAC_RACH_TYPE_ENUM
{
    WTTFPHY_MAC_RACH_TYPE_NORMAL                           = 1,                 /* 上行随机接入类型为普通方式  */
    WTTFPHY_MAC_RACH_TYPE_EFACH                            = 2,                 /* 上行随机接入类型为上行增强FACH方式 */

    WTTFPHY_MAC_RACH_TYPE_BUTT                                                  /* 最后一个枚举值 */
};
typedef VOS_UINT16 WTTFPHY_MAC_RACH_TYPE_ENUM_UINT16;

enum WTTFPHY_PDU_SIZE_TYPE_ENUM
{
    WTTFPHY_PDU_SIZE_FIXED_SIZE_TYPE         = 0,   /*PDU Size固定长度类型*/
    WTTFPHY_PDU_SIZE_FLEX_SIZE_TYPE          = 1,   /*PDU Size可变长度类型*/

    WTTFPHY_PDU_SIZE_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16;


/* 本枚举值用来作为WTTF和PHY之间的变参函数入参数组下标，数组成员个数不能超过WTTFPHY_ITF_API_MAX_PARA_CNT */
enum WTTFPHY_SLOT0_ISR_PARA_TYPE_ENUM
{
    WTTFPHY_SLOT0_ISR_SFN               = 0,    /* 回调函数的第1个参数为SFN */
    WTTFPHY_SLOT0_ISR_CFN               = 1,    /* 回调函数的第2个参数为CFN */
    WTTFPHY_SLOT0_ISR_BUTT
};
typedef VOS_UINT16 WTTFPHY_SLOT0_ISR_PARA_TYPE_ENUM_UINT16;

enum WTTFPHY_RL_STATUS_TYPE_ENUM
{
    WTTFPHY_RL_STATUS_USEABLE           = 0,   /*对能提供可靠传输的RL，则RL可用*/
    WTTFPHY_RL_STATUS_UNUSEABLE         = 1,   /*不能提供可靠传输的RL，则RL不可用*/

    WTTFPHY_RL_STATUS_TYPE_BUTT
};
typedef VOS_UINT16 WTTFPHY_RL_STATUS_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
enum WTTFPHY_MSG_TYPE_ENUM
{
    ID_MAC_PHY_ACCESS_REQ               = 0x1109,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_REQ_STRU */
    ID_PHY_MAC_ACCESS_CNF               = 0x3002,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_CNF_STRU */

    ID_MAC_PHY_E_ACCESS_REQ             = 0x1110,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_REQ_STRU */
    ID_PHY_MAC_E_ACCESS_CNF             = 0x3016,           /* _H2ASN_MsgChoice WTTFPHY_ACCESS_CNF_STRU */

    ID_MAC_PHY_AMR_DATA_IND             = 0x1101,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU */
    ID_PHY_RLC_AMR_DATA_REQ             = 0x3101,           /* _H2ASN_MsgChoice WTTFPHY_AMR_DATA_REQ_BUF_STRU */

    ID_MAC_PHY_DATA_REQ                 = 0x1301,           /* _H2ASN_MsgChoice WTTFPHY_PHY_DATA_REQ_BUF_STRU */
    ID_PHY_MAC_DATA_IND                 = 0x3001,           /* _H2ASN_MsgChoice WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU */

    ID_PHY_MAC_TFC_BCBD_IND             = 0x3003,           /* _H2ASN_MsgChoice WTTFPHY_MAC_TFC_BCBD_IND_STRU */
    ID_PHY_MAC_DPCCH_PWR_IND            = 0x3004,           /* _H2ASN_MsgChoice WTTFPHY_MAC_DPCCH_PWR_IND_STRU */

    ID_PHY_MAC_HS_PDU_DATA_IND          = 0x3005,           /* _H2ASN_MsgChoice WTTFPHY_MAC_HS_DATA_IND_DATA_BUF_STRU */

    ID_PHY_MAC_BETA_HS_IND              = 0x3006,           /* _H2ASN_MsgChoice WTTFPHY_MAC_BETA_HS_IND_STRU */

    ID_PHY_MAC_COMPRESS_MODE_UPDATE_IND = 0x3008,           /* _H2ASN_MsgChoice WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU */

    ID_MAC_PHY_FLUSH_VITUAL_BO_REQ      = 0x3010,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_E_FLUSH_VIRTUAL_BO_REQ_STRU */

    ID_PHY_MAC_EHS_PDU_DATA_IND         = 0x4001,           /* _H2ASN_MsgChoice WTTFPHY_MAC_EHS_PDU_STRU */

    ID_MAC_PHY_MAC_RESET_REQ            = 0x4004,           /* _H2ASN_MsgChoice WTTFPHY_MAC_RESET_REQ_STRU */
    ID_PHY_MAC_MAC_RESET_CNF            = 0x3018,           /* _H2ASN_MsgChoice WTTFPHY_MAC_RESET_CNF_STRU */

    ID_PHY_MAC_UPA_DATA_STATUS_IND      = 0x3019,           /* _H2ASN_Skip */

    ID_PHY_MAC_RL_STATUS_IND            = 0x3020,           /* _H2ASN_MsgChoice WTTFPHY_PHY_RL_STATUS_IND_STRU */

    ID_MAC_PHY_UPA_PDU_DATA_REQ         = 0x3054,           /* _H2ASN_MsgChoice WTTFMAC_PHY_UPA_DATA_STRU */

    ID_PHY_MAC_UPA_SCHED_STATUS_IND     = 0x3055,           /* _H2ASN_MsgChoice WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU */

    ID_RTT_STUB_WTTF_PHY_DATA_REQ       = 0x300e,           /* _H2ASN_Skip */   /* _H2ASN_MsgChoice RTT_STUB_WTTF_PHY_DATA_REQ_STRU */  /*消息通信*/
    ID_RTT_STUB_PHY_WTTF_DATA_IND       = 0x300f,           /* _H2ASN_Skip */   /* _H2ASN_MsgChoice RTT_STUB_PHY_WTTF_DATA_IND_STRU */  /*消息通信*/

    ID_WTTF_PHY_DL_DECIPHER_PARAM_REQ   = 0x5001,           /* _H2ASN_MsgChoice WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU */

    ID_MAC_PHY_AMR_DATA_READY_IND       = 0x5002,           /* _H2ASN_MsgChoice WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU */

    WTTFPHY_MSG_TYPE_BUTT
} ;
typedef VOS_UINT16  WTTFPHY_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/******************************************************************************************************
结构名    : WTTFPHY_ACCESS_REQ_STRU
结构说明  : DSP(PHY)与ARM(HPA)共享邮箱中的数据部分内容
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /*消息类型*/
    VOS_UINT16                          usOpId;             /*操作标识*/
    VOS_UINT16                          usAscNum;           /*[0,7],接入业务类号，对应物理层随机接入的资源:接入时隙、前导签名,类型定为VOS_UINT16是为了与6511物理层兼容*/
    VOS_INT16                           sPowerPpm;          /*[-5,10],dB,消息控制部分(理解为DPCCH)和最后一次Preamble的发射功率之差,类型定为VOS_INT16是为了与6511物理层兼容*/
} WTTFPHY_ACCESS_REQ_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_ACCESS_CNF_STRU
结构说明  : DSP(PHY)与ARM(HPA)共享邮箱中的数据部分内容
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /*消息类型*/
    VOS_UINT16                          usOpId;             /*操作标识*/
    WTTFPHY_ACCESS_ENUM_UINT16          enAccessInfoInd;    /*取值:MAC_ACCESS_ENUM*/
    WTTFPHY_RF_ENUM_UINT16              enRfExistFlag;      /*RF资源存在标志*/
} WTTFPHY_ACCESS_CNF_STRU;

/***********************************************************************************************
结构名    : WTTFPHY_EFACH_ACCESS_REQ_STRU
结构说明  : WDSP(PHY)与ARM(MAC)共享邮箱中的增强随机接入请求内容
***********************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16            enMsgName;          /*消息类型*/
    VOS_UINT16                              usOpId;             /*操作标识*/
    VOS_UINT16                              usAscNum;           /*[0,7],接入业务类号，对应物理层随机接入的资源:接入时隙、前导签名,类型定为VOS_UINT16是为了与6511物理层兼容*/
    WTTFPHY_UL_EFACH_LOCH_TYPE_ENUM_UINT16  usEFachLochType;    /*[0x1,0x2], 0x1:CCCH; 0x2:DCCH/DTCH */
} WTTFPHY_EFACH_ACCESS_REQ_STRU;

/***********************************************************************************************
结构名    : WTTFPHY_EFACH_ACCESS_CNF_STRU
结构说明  : WDSP(PHY)与ARM(HPA)共享邮箱中的增强随机接入回复内容
***********************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16         enMsgName;             /*消息类型*/
    VOS_UINT16                           usOpId;                /*操作标识*/
    WTTFPHY_ACCESS_ENUM_UINT16           enAccessInfoInd;       /*取值:MAC_ACCESS_ENUM*/
    WTTFPHY_MAC_STATUS_IND_ENUM_UINT16   enAccessStatusInd;     /*取值:MAC_E_ACCESS_ENUM 仅当enAccessInfoInd 为WTTFPHY_AICH_ACK时，enAccessStatusInd才有效
                                                                  enAccessInfoInd 为WTTFPHY_AICH_ACK时, 已经分配E-DCH信道资源, 具体有两种情况:
                                                                  (1)NW回复UE access ACK
                                                                  (2)NW回复UE access NACK+有效EAI
                                                                */
} WTTFPHY_EFACH_ACCESS_CNF_STRU;

/***********************************************************************************************
结构名    : WTTFPHY_EFACH_ACCESS_INFO_STRU
结构说明  : WDSP(PHY)与ARM(MAC)共享邮箱中的增强随机接入内容
***********************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16            enMutexFlag;        /* 读写标记*/
    VOS_UINT16                           ausReserve1[1];     /* 4字节对齐，保留 */
    WTTFPHY_EFACH_ACCESS_REQ_STRU        stEAccessReq;       /* 增强随机接入请求 */
    VOS_UINT16                           ausMagicNum1[4];     /* 保留待今后扩展, 目前固定为0x55AA55AA */
    WTTFPHY_EFACH_ACCESS_CNF_STRU        stEAccessCnf;         /* 增强随机接入回复 */
    VOS_UINT16                           ausMagicNum2[4];     /*保留待今后扩展, 目前固定为0x55AA55AA */
} WTTFPHY_EFACH_ACCESS_INFO_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU
结构说明  : DSP(PHY)与ARM(RLC)共享邮箱中的数据部分内容
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 原语标识  */
    VOS_UINT16                          usIf1Head;          /* IF1语音帧头信息 */
    VOS_UINT16                          ausAmrData[2];      /* AMR语音帧数据 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU
结构说明  : DSP(PHY)与ARM(MAC)共享邮箱中的数据部分内容
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;          /* 原语标识 */
    VOS_UINT16                          usIf1Head;          /* IF1语音帧头信息 */
    VOS_UINT16                          ausAmrData[2];      /* AMR语音帧数据 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_AMR_DATA_REQ_BUF_STRU
 结构说明  : DSP(PHY)与ARM(RLC)间上行AMR语音共享缓存
             aucData[WTTFPHY_MAX_PHY_DATA_REQ_LEN]指示的数据部分内容详见:WTTFPHY_PHY_RLC_AMR_DATA_REQ_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          enMsgName;              /* 消息标志 ID_CODEC_MAC_AMR_DATA_IND */
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* 读写标记*/
    VOS_UINT16                          enCodecType;            /* 0:NB,1:WB 说明：NB包括AMR-NB和AMR-NB2，WB指AMR-WB */
    VOS_UINT16                          enFrameType;            /* AMR编码帧类型 取值范围:0-15 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTFPHY_AMR_DATA_REQ_BUF_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_AMR_DATA_IND_BUF_STRU
 结构说明  : DSP(PHY)与ARM(MAC)间下行AMR语音共享缓存

             ARM(MAC): 提前把AMR语音数据写入WTTFPHY_AMR_DATA_IND_BUF_STRU的相应数据部分，并置WTTFPHY_MUTEX_DATA_EXIST,
             DSP(PHY): 在6ms中断服务程序读走该AMR数据,并置WTTFPHY_MUTEX_DATA_NOT_EXIST;

             aucData[WTTFPHY_MAX_AMR_DATA_IND_LEN]指示的数据部分内容详见:WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausReserve1[1];         /* 4字节对齐，保留*/
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* 读写标记*/
    VOS_UINT16                          usDataLen;              /* [0..36],aucData[]部分长度,单位:字节，数值上是4的倍数 */
    VOS_UINT16                          ausReserve2[1];         /* 4字节对齐，保留*/
    VOS_UINT8                           aucData[WTTFPHY_MAX_AMR_DATA_IND_LEN]; /* 下行数据，内容详见:WTTFPHY_MAC_PHY_AMR_DATA_IND_STRU */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
}WTTFPHY_AMR_DATA_IND_BUF_STRU;
/* 071101 z44034 ARM & DSP New Interface for 6720 end */


/******************************************************************************************************
结构名    : WTTFPHY_UL_TRCH_DATA_STRU
结构说明  : 上行传输信道参数:usTfi、usTrchId
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                          usTrchId;           /* [1,32],传输信道标识*/
    VOS_UINT16                          usTfi;              /* [0,63],传输格式标识 */
} WTTFPHY_UL_TRCH_DATA_STRU;


/* WTTFPHY_DL_TRCH_DATA_STRU */
typedef struct
{
    VOS_UINT32                          ulCrcBitMap;        /* 每比特指示一个传输块的CRC结果,例如:bit0 =1 表明第1个传输块CRC校验正确，bit3 =0 表明第4个传输块CRC校验不正确 */
    VOS_UINT16                          usTrchDataLen;      /* [0，352],单位:字(32BIT)，本传输信道数据的长度 */
    VOS_UINT8                           ucTfi;              /* [0,63],传输格式标识 */
    VOS_UINT8                           ucTrchId;           /* [1,32],传输信道ID*/
}WTTFPHY_DL_TRCH_DATA_STRU;


/*****************************************************************************
 结构名    : WTTFPHY_UL_OVER_TIMER_CFG_STRU
 结构说明  : CELL_DCH态该结构才有效
             DSP在6ms中断时，读到上行数传邮箱互斥标记为DATA_NOT_EXIST,
             则将ARM提供的该超时异常保护参数配置BBP;
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurrSchedCfn;     /* 连接帧号, 当前调度时刻的CFN */
    VOS_UINT16                          usCurrSchedTrchCnt; /* 当前调度时刻上行传输信道个数;只对应DCH，由是否到达TTI边界调度时刻决定;*/
    WTTFPHY_UL_TRCH_DATA_STRU           astCurrSchedTrchInfo[PS_WUE_MAX_DCH_NUM];  /* 当前调度时刻传输信道对应的TFI列表,对应速率为0bps，一般TFI=0 */

} WTTFPHY_UL_OVER_TIME_CFG_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_PHY_DATA_REQ_BUF_STRU
 结构说明  : DSP与ARM间上行DPCH/P-RACH信道共享缓存结构

             ARM(MAC): 提前1帧写入数据,并置WTTFPHY_MUTEX_DATA_EXIST,
             DSP(PHY): DSP在6ms中断服务程序首先读走数据，写入DSP与BBP的共享缓存,并置WTTFPHY_MUTEX_DATA_NOT_EXIST;
*****************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* 读写标记 */
    VOS_UINT16                          ausReserve1[1];         /* 4字节对齐，保留字段，不使用 */

    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /* 原语ID */
    WTTFPHY_CCTRCH_ENUM_UINT16          enCctrchID;             /* 码组合信道标识 */
    VOS_UINT16                          usCFN;                  /* 当前CFN,只在CELL-DCH状态下有效 */
    VOS_UINT16                          usUlTrchCnt;            /* 上行传输信道个数 */
    WTTFPHY_UL_TRCH_DATA_STRU           astUlTrchDataInfo[PS_WUE_MAX_DCH_NUM];  /* 传输信道当前使用的TFI列表 */
    VOS_UINT32                          ulSerialNum;            /* ARM从0顺序递增,DSP判断该值是否顺序递增1，如果非顺序递增1，则DSP提供丢消息的出错信息*/

    VOS_UINT16                          ausReserve2[1];         /* 4字节对齐，保留字段，不使用 */
    VOS_UINT16                          usDataLen;              /* 数据长度,单位:字节,在数值上是4的整数倍,范围[0..WTTFPHY_MAX_PHY_DATA_REQ_LEN-1] */
    VOS_UINT8                           aucData[WTTFPHY_MAX_PHY_DATA_REQ_LEN];   /* 上行数据块 */

    WTTFPHY_UL_OVER_TIME_CFG_STRU       stUlOverTimeCfg;        /* DSP在6ms中断时，读到上行数传邮箱互斥标记为DATA_NOT_EXIST,则将ARM提供的该超时异常保护参数配置BBP;*/

    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_PHY_DATA_REQ_BUF_STRU;



/*****************************************************************************
 结构名    : WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU
 结构说明  : DSP与ARM间下行DPCH/S-CCPCH信道共享缓存控制部分结构
******************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* 读写标记*/
    VOS_UINT16                          usDataLen;          /* [0..232],单位:字(32BIT),不包括头信息,也即只包含aucData[]部分数据长度 */

    WTTFPHY_CCTRCH_ENUM_UINT16          enCctrchId;         /* 码组合信道标识 */
    VOS_UINT8                           ucCfn;              /* [0..255],CFN */
    VOS_UINT8                           ucDlTrchNum;        /* [0..7],当前译码上报的下行传输信道的个数 */

    WTTFPHY_MSG_TYPE_ENUM_UINT16       enMsgName;          /* 原语ID */
    VOS_UINT16                          usCctrchIndex;      /* 下行数据在哪套cctrch配置中收到,现在WRR会同时配置多套cctrch配置,通过该索引区分*/
    VOS_UINT32                          ulSerialNum;        /* 用于调试功能,PHY从0起，顺序递增加1，MAC判断连续2次处理是否递增1，如果不是，则MAC提供异常出错信息; */

    WTTFPHY_DL_TRCH_DATA_STRU           astDlTrchDataInfo[PS_WUE_MAX_DCH_NUM]; /* 传输信道数据信息单元 */

    VOS_UINT16                          usSfn;              /*  [0..4095],物理层收到数据时对应的SFN */
    VOS_UINT8                           aucReserve1[2];

    VOS_UINT32                          aulReserve2[3];     /* 接口保留*/

    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU;


/*****************************************************************************
 结构名    : WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU
 结构说明  : DSP与ARM间DPCH/S-CCPCH信道下行译码共享缓存结构

             DSP(PHY): DSP收到BBP下行译码中断后,将BBP数据搬移到该缓存中,并置WTTFPHY_MUTEX_DATA_EXIST;

             ARM(HPA): HPA收到来自0ms中断服务程序的PHY_MAC_INFO_IND消息后,将该共享缓存内的下行数据放入环形队列，
                       处理完毕置WTTFPHY_MUTEX_DATA_NOT_EXIST.
******************************************************************************/
typedef struct
{
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU    stPhyMacDataIndCtrlParam;   /*DSP与ARM间下行DPCH/S-CCPCH信道共享缓存控制部分结构*/
    VOS_UINT8                               aucData[WTTFPHY_MAX_PHY_DATA_IND_TURBO_DATA_LEN];  /*enCctrchId和usTrchId指定的传输信道上的传输数据,每个TB块数据后面紧跟CRC是否正确的指示,具体数据存放方式请见<Hi4131V100R001-子系统接口说明书-WTTF-PHY.doc>说明 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_TURBO_BUF_STRU;



/*****************************************************************************
 结构名    : WTTFPHY_MAC_DATA_IND_VITERBI_BUF_STRU
 结构说明  : DSP与ARM间下行DPCH/S-CCPCH信道下行译码共享缓存结构

             DSP(PHY): DSP收到BBP下行译码中断后,将BBP数据搬移到该缓存中,并置WTTFPHY_MUTEX_DATA_EXIST;

             ARM(HPA): HPA收到来自0ms中断服务程序的PHY_MAC_INFO_IND消息后,将该共享缓存内的下行数据放入环形队列，
                       处理完毕置WTTFPHY_MUTEX_DATA_NOT_EXIST.
******************************************************************************/
typedef struct
{
    WTTFPHY_MAC_DATA_IND_CTRL_PARAM_STRU    stPhyMacDataIndCtrlParam;   /*DSP与ARM间下行DPCH/S-CCPCH信道共享缓存控制部分结构*/
    VOS_UINT8                               aucData[WTTFPHY_MAX_PHY_DATA_IND_VTB_DATA_LEN];  /*enCctrchId和usTrchId指定的传输信道上的传输数据,每个TB块数据后面紧跟CRC是否正确的指示,具体数据存放方式请见<Hi4131V100R001-子系统接口说明书-WTTF-PHY.doc>说明 */
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/

} WTTFPHY_MAC_DATA_IND_VITERBI_BUF_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_MAC_TFC_BCBD_IND_STRU
结构说明  : PHY每次收到RRC的配置后上报一次
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* 读写标记*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_UINT16                          ausReserve[1];     /* 4字节对齐,接口保留*/
    VOS_UINT16                          usTfcNum;
    VOS_UINT16                          ausTfcBcBd[PS_WUE_MAX_UL_TFC_NUM];/*低8bit为Bc(目前实现Bc固定为15),高8bit为Bd[1..225]，数组下标即为TFCI，RRC保证物理层、MAC数组下标的一致性*/
} WTTFPHY_MAC_TFC_BCBD_IND_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_BETA_HS_IND_STRU
结构说明  : PHY每次收到RRC的配置后上报一次
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* 读写标记*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_UINT16                          ausReserve[1];      /* 4字节对齐,接口保留*/
    VOS_UINT16                          usBetaHs;           /* 25.213 4.2.1.2, 有效值[5,6,8,9,12,15,19,24,30] */
} WTTFPHY_MAC_BETA_HS_IND_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_DPCCH_PWR_IND_STRU
结构说明  : PHY每帧9ms时刻都要上报
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;        /* 读写标记*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;
    VOS_INT16                           asDpcchPwr[WTTFPHY_SLOT_NUM_PER_FRAME]; /*[-500..330],单位：0.1dBm，0x7fff该时隙对应的发射功率无效，比如压模时隙 */
    VOS_INT16                           sAllowUlMaxPower;  /* 物理层通知的上行允许的最大发射功率，用于TFC功率限制选择 单位：0.1dBm */
} WTTFPHY_MAC_DPCCH_PWR_IND_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_HS_DATA_IND_BUF_STRU
结构说明  : R5 HSDPA接口
******************************************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPhyMacHsDataHead;
    VOS_UINT32                          ulPhyMacHsDataTail;
} WTTFPHY_MAC_HS_DATA_IND_CTRL_BUF_STRU;

typedef struct
{
    VOS_UINT8                           aucHsDschData[WTTFPHY_MAX_HS_PDU_BUF_NUM][WTTFPHY_MAX_HS_PDU_BUF_LEN];
} WTTFPHY_MAC_HS_DATA_IND_DATA_BUF_STRU;

typedef struct
{
    VOS_UINT32                          ulPhyMacEhsDataHead;   /*MAC-ehs header pointer*/
    VOS_UINT32                          ulPhyMacEhsDataTail;
} WTTFPHY_MAC_EHS_DATA_IND_CTRL_BUF_STRU;

typedef struct
{
    VOS_UINT8                           aucEhsDschData[WTTFPHY_MAX_EHS_PDU_BUF_NUM][WTTFPHY_MAX_EHS_PDU_BUF_LEN];
} WTTFPHY_MAC_EHS_DATA_IND_DATA_BUF_STRU;

/*****************************************************************************
 结构名    : WTTF_PHY_DL_DECIPHER_PARAM_STRU
 结构说明  : DSP(PHY)与ARM(MAC)间下行AMR解密序列共享缓存
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHfn;                  /* 可维可测用，以得知countC*/
    VOS_UINT16                          usCfn;                  /* 当前CFN */
    VOS_UINT16                          ausReserve[1];
    VOS_UINT16                          ausDecipherData[WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM][WTTF_PHY_DL_MAX_AMR_DECIPHER_KEY_BYTE_SIZE/2];/*PHY不能识别VOS_UINT8*/
    /******************************************************************************************************
        _H2ASN_Array2String
    ******************************************************************************************************/
} WTTF_PHY_DL_DECIPHER_PARAM_STRU;

typedef struct
{
    WTTFPHY_MUTEX_ENUM_UINT16           enMutexFlag;            /* 读写标记*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /* 原语标识 */
    VOS_UINT16                          usTrchCnt;              /* AMR总传输信道数 */
    VOS_UINT16                          ausTrchId[WTTF_PHY_DL_MAX_AMR_DECIPHER_TRCH_NUM];
    WTTF_PHY_DL_DECIPHER_PARAM_STRU     astDeCipherPara[WTTF_PHY_DL_MAX_AMR_DECIPHER_PARAM_NUM];
} WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU;

/* V3 R7_7C1 End */

/******************************************************************************************************
结构名    : WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU
结构说明  : HSUPA ARM-DSP间逻辑信道缓存的控制信息
******************************************************************************************************/
typedef struct
{
    /* [1..15], 只要映射到E-DCH信道,逻辑信道ID一定存在, 15表示CCCH */
    VOS_UINT16                          usLochId;

    /*
       此逻辑信道对应的数据允许存放的数据上限, 单位: 字节
       无论使用MAC-e/i, PS RB:都根据UE category来填写峰值速率下内存, PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE
                         CS RB:PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE
                         信令:PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE
                         RB0:PS_WUE_MAX_E_DCH_CCCH_BUF_BYTE_SIZE
    */
    VOS_UINT16                          usMacPduDataBufLen;

    /* 逻辑信道上承载的PDU size类型: fix or flexible */
    WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16   enPduSizeType;

    /* 单位:字节,在正常处理过程中, pdu size是唯一值,
       当Loch存在多个PDU SIZE时, 约定使用最小的PDU SIZE
       CCCH一定只有一个PDU SIZE, 并且为PDU SIZE当中包含一个字节的CRC
       仅在fix size时使用
    */
    VOS_UINT16                          usPduSizeByteLen;

    /* 此逻辑信道对应的数据允许存放的首地址, 为固定值, 不是此次数据放入的起始地址 */
    VOS_UINT32                          ulLochDataBufBaseAddr;

    /*
       ARM写,物理层读
       仅在flexible size时使用:
       ARM侧的Virtual MAC-is/i实体写入MAC-PDU时更新。即下一个待写的PduInfo表索引
       MacPduInfoHeadIdx为对应逻辑信道PduInfo表的数组下标。
       要求: ARM侧写入PDU数据内存和MAC PDU表要同步。PHY以usMacPduDataBufHeadIdx发生变化, 认为ARM侧有数据下发
    */
    volatile VOS_UINT16                 usMacPduInfoHeadIdx;

    /*
       ARM写,物理层读
       flexible size时:
       ARM侧的Virtual MAC-is/i实体写入数据后更新。其值为下一次数据放入的起始地址相对ulLochDataBufBaseAddr的偏移, 单位:Byte
       fix size时:
       ARM侧的Virtual MAC-es/e or Virtual MAC-is/i实体写入数据后更新。其值为下一次数据放入的起始地址相对ulLochDataBufBaseAddr的偏移, 单位:Byte
       PHY以usMacPduDataBufHeadIdx发生变化, 认为ARM侧有数据下发
    */
    volatile VOS_UINT16                  usMacPduDataBufHeadIdx;

    /*
       物理层写,ARM读
       flexible size时:
       [0,15]: MAC PDU Info中下一个待读MAC PDU Info的索引(MacPduInfoTailIdx), MacPduInfoTailIdx为对应逻辑信道PduInfo表的数组下标
       [16,31]: 下一次数据放入的起始地址相对ulMacPduDataBufBaseAddr的偏移(MacPduDataBufTailIdx), 单位:Byte
       要求: PHY侧读取PDU数据内存和MAC PDU表要同步。同时更新MacPduInfoTailIdx和MacPduDataBufTailIdx
       fix size时:
       [0,15]: 无效
       [16,31]: 下一次数据放入的起始地址相对ulMacPduDataBufBaseAddr的偏移(MacPduDataBufTailIdx), 单位:Byte
                增加量的单位是字节,usLochBufTailIdx增加的量在数值上始终是usPduSizeByteLen的整数倍
     */
    volatile VOS_UINT32                  ulMacPduInfoTailIdxAndMacPduDataBufTailIdx;

    /*
       ARM写,物理层读
       RLC共享给MAC的该逻辑信道的BO, 单位:Byte,
       (ulRlcBoBitLen + Virtual MAC-es/e or Virtual MAC-is/i Loch BO )表示该逻辑信道实际总共需要发送的数据量
    */
    VOS_UINT32                          ulBoByteLen;
} WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU
结构说明  : HSUPA ARM-DSP间逻辑信道缓存的控制信息
******************************************************************************************************/
typedef struct
{
    /*****************************************************************************
    [0..255],ARM UPA上行处理完毕后，更新CFN值,10ms内必须更新一次。
    当ulNewParaFlag 为零值时，DSP MAC_E/I实体在每个子帧处理时会判断该uwCfn
    是否与DSP看到的当前CFN一致，如果在10ms内仍然没有一致，则作异常统计。
    *****************************************************************************/
    VOS_UINT32                          ulCfn;

    /*****************************************************************************
    [0,0x33553355]该参数主要起到了DSP、ARM间建立或重配Mac-E/I时同步互斥的作用。
    DSP在建立MAC-E/I实体或者重配MAC-E/I实体的激活时刻到时，设置ulNewParaFlag标记
    为0x33553355。之后在调度中断中判断该标记如果为0x3355335，则不进行异常统计，
    同时不进行上行数据发送，如果为0，则进行异常统计，进行上行数据发送。
    ARM在接收到MAC-E/I建立或重配MAC-E/I实体的激活时刻到时,如果ulNewParaFlag标记
    为0x33553355，则清空原有的共享缓存中的数据，如果有则下发新数据到共享缓存，设置该标记
    为0，否则按照旧参数进行上行数据发送。
    *****************************************************************************/
    VOS_UINT32                          ulNewParaFlag;

    /*****************************************************************************
    [0,0x55335533]该参数主要起到了DSP、ARM间释放Mac-E/I时同步互斥的作用。
    DSP在释放MAC-E/I实体的激活时刻到时，设置ulRelParaFlag标记为0x55335533，
    之后就不进行异常统计，不进行上行数据发送。
    ARM在释放MAC-E/I实体的激活时刻到时, 如果判断ulRelParaFlag标记为0x55335533，
    则清空缓存中的数据，释放Mac-E/I实体，设置该标记为0，否则进行上行数据发送。
    *****************************************************************************/
    VOS_UINT32                          ulRelParaFlag;

    /* CCCH数据 */
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  stMacEDchCCCHRbBuf;

    /* 数组下标范围:[0..PS_WUE_MAX_LOCH_NUM-1],下标加1为Loch ID值,
    数组元素值范围:[0..WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM-1],值为astMacEDchSignalRbBuf[]的下标,
    也是MAC PDU Info表中astMacSRbTable[]的下标 */
    VOS_UINT32                          aulSignalLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchSRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM]  */
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchSignalRbBuf[WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM];


    /* 数组下标范围:[0..PS_WUE_MAX_LOCH_NUM-1],下标加1为Loch ID值,
    数组元素值范围:[0..WTTFPHY_MAC_UPA_MAX_CS_RB_NUM-1]，值为astMacEDchCsRbBuf[]的下标,
    也是MAC PDU Info表中astMacCsRbTable[]的下标 */
    VOS_UINT32                          aulCsLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchCsRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_CS_RB_NUM]*/
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchCsRbBuf[WTTFPHY_MAC_UPA_MAX_CS_RB_NUM];


    /* 数组下标范围:[0..PS_WUE_MAX_LOCH_NUM-1],下标加1为Loch ID值,
    数组元素值范围:[0..WTTFPHY_MAC_UPA_MAX_PS_RB_NUM-1]，值为astMacEDchPsRbBuf[]的下标,
    也是MAC PDU Info表中astMacPsRbTable[]的下标 */
    VOS_UINT32                          aulPsLochIdx[PS_WUE_MAX_LOCH_NUM];
    VOS_UINT32                          ulEDchPsRbCnt;   /* [0..WTTFPHY_MAC_UPA_MAX_PS_RB_NUM]*/
    WTTFPHY_MAC_UPA_LOCH_BUF_INFO_STRU  astMacEDchPsRbBuf[WTTFPHY_MAC_UPA_MAX_PS_RB_NUM];
} WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU
结构说明  : HSUPA ARM-DSP间给数接口,MAC PDU表项结构
             usMacPduSize: 变长size, MAC PDU数据长度, 单位bytes
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                          usMacPduSize;   /* MAC PDU数据长度，单位bytes*/
}WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU
结构说明  : 每个逻辑信道中MAC PDU Info表,个数为PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU
结构说明  : 每个逻辑信道中MAC PDU Info表,个数为PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU
结构说明  : 每个逻辑信道中MAC PDU Info表,个数为PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_PDU_INFO_STRU  astPduInfoList[PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH];
}WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU
结构说明  : 全部逻辑信道的MAC PDU Info表,
            SRB   WTTFPHY_MAC_E_MAX_S_RB_NUM个
            CS RB WTTFPHY_MAC_UPA_MAX_CS_RB_NUM个
            PS RB WTTFPHY_MAC_UPA_MAX_PS_RB_NUM个
******************************************************************************************************/
typedef struct
{
    WTTFPHY_MAC_FLEXIBLE_S_RB_PDU_INFO_TABLE_STRU     astMacSRbTable[WTTFPHY_MAC_UPA_MAX_SRB_RB_NUM];
    WTTFPHY_MAC_FLEXIBLE_CS_RB_PDU_INFO_TABLE_STRU    astMacCsRbTable[WTTFPHY_MAC_UPA_MAX_CS_RB_NUM];
    WTTFPHY_MAC_FLEXIBLE_PS_RB_PDU_INFO_TABLE_STRU    astMacPsRbTable[WTTFPHY_MAC_UPA_MAX_PS_RB_NUM];
}WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU
结构说明  : 载波要数子结构
            usGp          载波上Gp
            usGs          载波上Gs
            usGn          载波上Gn
******************************************************************************************************/
typedef struct
{
    VOS_UINT16     usGp;  /* 载频最大剩余负载(Gp), [0, 22996], 单位bit */
    VOS_UINT16     usGs;  /* 载频可用的调度负载(Gs), [0, 22996], 单位bit */
    VOS_UINT16     usGn;  /* 载频可用的非调度负载(Gn), 单位bit */
    VOS_UINT16     ausReserve[1];
}WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU
结构说明  : 多载波要数子结构
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                                      usCfn;           /* [0..255], 由PHY在放入G值时填写 */
    VOS_UINT16                                      usCarrierCnt;    /* 载频个数, 无辅载频时, 填1, 目前最多2个 */
    /*各载频上要数的数据量: 其中astPerCarrierValue[0]为主载频, 之后的为辅载频*/
    WTTFPHY_PHY_UPA_SCHED_PER_CARRIER_VALUE_STRU    astPerCarrierValue[PS_WUE_MAX_CARRIER_CNT];
    VOS_UINT16                                      ausExt[4];       /* 预留4个16bit待扩展 */
}WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU
结构说明  : 物理层要数接口,包含8个要数子结构的环形缓存
            ulHeadIdx 物理层待写索引
            ulTailIdx 协议栈待读索引
            读索引等于写索引时代表没有新的要数信息
******************************************************************************************************/
typedef struct
{
   VOS_UINT32                                   ulHeadIdx;    /*物理层待写索引*/
   VOS_UINT32                                   ulTailIdx;    /*协议栈待读索引*/
   WTTFPHY_PHY_UPA_SCHED_STATUS_IND_VALUE_STRU  astDCSchedStatusInd[PS_WUE_MAC_E_DCH_STATUS_IND_BUF_SIZE];
}WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU
结构说明  : 物理层共享数据其实地址结构
            包含3个地址
            1\PHY Data REQ缓存首地址
            2\PDU Info表首地址
            3\PHY要数信息首地址
******************************************************************************************************/
typedef struct
{
    VOS_UINT32      ulPhyDataReqBufAddr; /*WTTFPHY_MAC_UPA_DATA_REQ_BUF_STRU */
    VOS_UINT32      ulPduInfoTableAddr;  /*WTTFPHY_MAC_FLEXIBLE_PDU_INFO_TABLE_STRU*/
    VOS_UINT32      ulSchedStatsIndAddr; /*WTTFPHY_PHY_UPA_SCHED_STATUS_IND_STRU*/
}WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU;


/******************************************************************************************************
结构名    : WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU
结构说明  : 硬切换回退后，DSP负责调整压模的信息，保证正确性。异系统切换回退目前不支持
******************************************************************************************************/
typedef struct
{
    VOS_UINT16                                  usTGPSI;                        /* TGPS标识       */
    VOS_UINT16                                  usTGPSStaus;                    /* TGPS状态标志   */
    VOS_UINT16                                  ulTGCnt;                        /* 记录该TGPS已激活帧数 */
    VOS_UINT16                                  usReserve1;
} WTTFPHY_TGPS_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16            enMsgName;          /*消息类型*/        /*_H2ASN_Skip*/
    VOS_UINT16                              usOpId;             /*操作标识*/
    VOS_UINT16                              usCfn;
    VOS_UINT16                              usTGPSCnt;                              /* TGPS个数 */
    WTTFPHY_TGPS_INFO_STRU                  astTGPSInfo[PS_WUE_MAX_TGPS_NUM];
} WTTFPHY_PHY_MAC_COMPRESS_MODE_UPDATE_IND_STRU;


/******************************************************************************************************
结构名    : MAC_FLUSH_DATA_PER_LOCH_STRU
结构说明  : WTTF MAC发消息通知DSP清除Vitual BO
             固定/弹性size, 都将MAC当前最新Data Buf Head和Pdu Info Head告诉PHY
******************************************************************************************************/
typedef struct
{
    WTTFPHY_PDU_SIZE_TYPE_ENUM_UINT16   enPduSizeType;          /* 逻辑信道上承载的PDU size类型: fix or flexible */
    VOS_UINT16                          usLochLabel;            /* 范围:[2..65]*/

    VOS_UINT16                          usDataBufEndPos;        /* 表示Data Buf Head
                                                                   SRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_S_RB_BUF_BYTE_SIZE),
                                                                   CS TRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_CS_RB_BUF_BYTE_SIZE)
                                                                   PS TRB:usEndPos<=(PS_WUE_MAX_E_DCH_PER_PS_RB_BUF_BYTE_SIZE);
                                                                */
    VOS_UINT16                          usPduInfoEndPos;        /* 表示Pdu Info Head
                                                                   SRB:usEndPos<=(PS_WUE_S_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH),
                                                                   CS TRB:usEndPos<=(PS_WUE_CS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH)
                                                                   PS TRB:usEndPos<=(PS_WUE_PS_RB_MAX_FLEXIBLE_PDU_NUM_PER_UL_LOCH)
                                                                */
}MAC_FLUSH_DATA_PER_LOCH_STRU;

/******************************************************************************************************
结构名    : WTTFPHY_MAC_PHY_UPA_FLUSH_VIRTUAL_BO_REQ_STRU
结构说明  : WTTF MAC发消息通知DSP清除Vitual BO 直至 usEndPos位置。
            目前应用场景:
            (1)当RLC发生Reset时，将已有的Vitual BO清除，以便发送Reset/Reset ACK PDU;
            (2)对AM/UM RLC实体的重建（单边重建或者全部重建的时候）, 清除旧的rlc pdu size pdu
******************************************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    WTTFPHY_MSG_TYPE_ENUM_UINT16        enMsgName;              /*消息类型*/    /*_H2ASN_Skip*/
    VOS_UINT16                          usLochCnt;              /* 范围:[1.. PS_WUE_MAX_E_DCH_LOCH_NUM],PS_WUE_MAX_E_DCH_LOCH_NUM =12 */
    MAC_FLUSH_DATA_PER_LOCH_STRU        astEFlushDataPerLoch[PS_WUE_MAX_E_DCH_LOCH_NUM];
} WTTFPHY_MAC_PHY_UPA_FLUSH_VIRTUAL_BO_REQ_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_MAC_RESET_REQ_STRU
 协议表格  : 11.6.4.8, 25.321, R7
 ASN.1描述 :
 结构说明  : MAC实体复位指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    VOS_INT16                                 sActiveTime;      /* 激活时间:
                                                                   目前是只有MAC-ehs Treset定时器超时场景,
                                                                   固定为-1, 立即激活 */
    WTTFPHY_MAC_RESET_TYPE_ENUM_UINT16        enResetType;      /* 复位类型:
                                                                   虽然从25.321上看, 目前只有MAC-ehs复位,
                                                                   但是考虑到协议演进,
                                                                   还是定义出enResetType, 以备扩展 */
    VOS_UINT16                                ausFeedback[4];   /* 回带信息(由MAC填写) */
}WTTFPHY_MAC_RESET_REQ_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_MAC_RESET_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC实体复位指示响应
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    WTTFPHY_MAC_RESET_RESULT_ENUM_UINT16      enIndicator;      /* 配置结果,0代表成功, 其它代表失败 */
    VOS_UINT16                                ausFeedback[4];   /* 回带信息(由PHY填写,
                                                                   内容与WTTFPHY_MAC_RESET_REQ_STRU中ausFeedback[4]相同) */
    VOS_UINT16                                usReserve1;
}WTTFPHY_MAC_RESET_CNF_STRU;

/* BBPMASTER提供物理层上下电注册回调函数类型 */
typedef void (*PVOIDFUNC)(void);

/* 带有参数的函数回调类型 */
typedef VOS_UINT32 (*PRARAFUNC)(VOS_UINT32 ulParaCnt, VOS_UINT32 aulParaValue[]);

/*****************************************************************************
 结构名    : WTTFPHY_PHY_RL_STATUS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY的RL Status指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usOPID;           /* 操作标识 */
    WTTFPHY_RL_STATUS_TYPE_ENUM_UINT16        enRlStatus;       /* RL Status,0代表可用, 1代表不可用 */
    VOS_UINT16                                usReserve1;
}WTTFPHY_PHY_RL_STATUS_IND_STRU;

/*****************************************************************************
 结构名    : WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC发给PHY的上行语音数据Ready消息指示
 *****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    WTTFPHY_MSG_TYPE_ENUM_UINT16              enMsgID;          /* 原语类型 */ /*_H2ASN_Skip*/
    VOS_UINT16                                usReserve1;
}WTTFPHY_MAC_PHY_AMR_DATA_READY_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 全局变量声明
*****************************************************************************/
/* AMR数据地址 */
#define WTTFPHY_MAC_DL_AMR_DECIPHER_BUF_ADDR()    WTTF_GetPhyMacDlAmrDecipherAddr()

/* TFCI对应BcBd地址 */
#define WTTFPHY_MAC_DPCCH_PWR_IND_ADDR()          WTTF_GetPhyMacDpcchPwrIndAddr()

/*****************************************************************************
  11 函数声明
*****************************************************************************/
#ifdef FEATURE_DSP2ARM
extern WTTFPHY_PHY_UPA_BASE_ADDR_INFO_STRU* WPHY_GetMacPhyUpaBaseAddrInfo(VOS_VOID);
#endif

extern WTTF_PHY_DL_DECIPHER_PARAM_REQ_STRU* WTTF_GetPhyMacDlAmrDecipherAddr(VOS_VOID);
extern WTTFPHY_MAC_DPCCH_PWR_IND_STRU* WTTF_GetPhyMacDpcchPwrIndAddr(VOS_VOID);

/* BBPMASTER提供物理层上下电注册回调函数 */
extern VOS_UINT32 PHY_REG_ElectrifyCallFun(PVOIDFUNC   pElectrifyFun);
extern VOS_UINT32 PHY_REG_UnelectrifyCallFun(PVOIDFUNC   pUnelectrifyFun);

/* UPA提供的要数注册回调函数 */
extern VOS_UINT32 PHY_REG_UpaStatusIndCallFun(PVOIDFUNC   pUpaStatusIndFun);

/* DPA译码提供的注册回调函数 */
extern VOS_UINT32 PHY_REG_DpaRptCallFun(PVOIDFUNC   pDpaRptFun);

/* Slot0时PHY通知TTF的注册回调函数,在中断程序中调用注册的回调函数 */
extern VOS_UINT32 PHY_REG_WcdmaSlot0IsrCallFun(PRARAFUNC pWcdmaSlot0Fun);


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

#endif /* end of WttfDspInterface.h */


