/******************************************************************************

                 版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cicom_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2014-11-29 15:28:32
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年11月29日
    作    者   : y00265681
    修改内容   : 从《Hi3650V100 SOC寄存器手册_CICOM.xml》的工作表"CICOM"自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CICOM_INTERFACE_H__
#define __SOC_CICOM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CICOM
 ****************************************************************************/
/* 寄存器说明：[加解密共用]CICOM软复位寄存器。
            软件发现CICOM异常时，向该寄存器的bit[0]写入1'b1，对CICOM模块进行软复位。
            读该寄存器返回值为0x0。
   位域定义UNION结构:  SOC_CICOM_STATE_RESET_UNION */
#define SOC_CICOM_STATE_RESET_ADDR(base)        ((base) + (0x0000))

/* 寄存器说明：[加解密共用]仲裁策略选择寄存器。
            写该寄存器设置加密请求与解密请求的仲裁策略。
            注：在加解密处理过程中，允许软件对该寄存器进行改写，以更新仲裁策略。但是频繁切换仲裁策略会导致加解密反复交替进行。因此建议软件不要频繁更新仲裁策略。
   位域定义UNION结构:  SOC_CICOM_PRIOR_SELECT_UNION */
#define SOC_CICOM_PRIOR_SELECT_ADDR(base)       ((base) + (0x0004))

/* 寄存器说明：[加密]参数链表起始地址寄存器。
            该寄存器用于设置加密时，第一个PDU包对应的参数链表的起始地址。
            在加密处理过程中，该寄存器的值由硬件自动更新为当前正在加密的PDU包对应的参数链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_PARAM_ADDR_UL_UNION */
#define SOC_CICOM_LLI_PARAM_ADDR_UL_ADDR(base)  ((base) + (0x0008))

/* 寄存器说明：[加密]全局加密参数配置寄存器。
            该寄存器用于配置一次运行只需配置一次，不需按照PDU包粒度更新的加密参数。
   位域定义UNION结构:  SOC_CICOM_GLOBAL_CFG_UL_UNION */
#define SOC_CICOM_GLOBAL_CFG_UL_ADDR(base)      ((base) + (0x000C))

/* 寄存器说明：[加密]环形缓存信道首地址寄存器。
            W模加密时，软件根据当次运行所需操作的信道配置CHL_FST_ADDR_UL和CHL_LST_ADDR_UL寄存器。
            当需要向DST2中写入加密目的数据时，硬件根据DST2目的数据段起始地址DST2_SEG_ADDR_UL和数据段长度DST2_SEG_LEN_UL以及环形缓存信道首、末地址自动判断是否需要绕回。若需要绕回，则绕回后从该配置地址续写。
   位域定义UNION结构:  SOC_CICOM_CHL_FST_ADDR_UL_UNION */
#define SOC_CICOM_CHL_FST_ADDR_UL_ADDR(base)    ((base) + (0x0010))

/* 寄存器说明：[加密]环形缓存信道末地址寄存器。
            W模加密时，软件根据当次运行所需操作的信道配置CHL_FST_ADDR_UL和CHL_LST_ADDR_UL寄存器。
            当需要向DST2中写入加密目的数据时，硬件根据DST2目的数据段起始地址DST2_SEG_ADDR_UL和数据段长度DST2_SEG_LEN_UL以及环形缓存信道首、末地址自动判断是否需要绕回。若需要绕回，则写到该配置地址时开始绕回。
   位域定义UNION结构:  SOC_CICOM_CHL_LST_ADDR_UL_UNION */
#define SOC_CICOM_CHL_LST_ADDR_UL_ADDR(base)    ((base) + (0x0014))

/* 寄存器说明：[加密]中断使能/屏蔽寄存器。
            写该寄存器设置各加密中断使能或屏蔽。
   位域定义UNION结构:  SOC_CICOM_INT_EN_UL_UNION */
#define SOC_CICOM_INT_EN_UL_ADDR(base)          ((base) + (0x0018))

/* 寄存器说明：[加密]原始中断状态寄存器。
            读该寄存器返回各中断的原始中断状态。
   位域定义UNION结构:  SOC_CICOM_INT_RAW_UL_UNION */
#define SOC_CICOM_INT_RAW_UL_ADDR(base)         ((base) + (0x001C))

/* 寄存器说明：[加密]中断状态清除寄存器。
            向该寄存器的相应bit写1'b1清除对应加密中断，写1'b0无影响。
            读该寄存器返回值为0x0。
   位域定义UNION结构:  SOC_CICOM_INT_CLR_UL_UNION */
#define SOC_CICOM_INT_CLR_UL_ADDR(base)         ((base) + (0x0020))

/* 寄存器说明：[加密]屏蔽后的加密中断状态寄存器。
            读该寄存器返回各加密中断的屏蔽后中断状态。
   位域定义UNION结构:  SOC_CICOM_INT_MSK_UL_UNION */
#define SOC_CICOM_INT_MSK_UL_ADDR(base)         ((base) + (0x0024))

/* 寄存器说明：[加密]使能寄存器。
            软件准备好链表并配置好加密参数寄存器之后，向该寄存器的bit[0]写入1'b1启动加密操作。
            加密操作完成后，由硬件自动对该寄存器清零。
            加密过程出错时，硬件也会对该寄存器自动清零，使内部状态机返回IDLE状态。
            读该寄存器返回加密处理状态。
                返回值为0x0，表示CICOM没有进行加密处理。
                返回值为0x1，表示CICOM正在进行加密处理；
   位域定义UNION结构:  SOC_CICOM_EN_UL_UNION */
#define SOC_CICOM_EN_UL_ADDR(base)              ((base) + (0x0028))

/* 寄存器说明：[加密]CK参数在外部Memory中的地址寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数存放于外部Memory中的起始地址。
   位域定义UNION结构:  SOC_CICOM_CK_ADDR_UL_UNION */
#define SOC_CICOM_CK_ADDR_UL_ADDR(base)         ((base) + (0x002C))

/* 寄存器说明：[加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[31:0]。
   位域定义UNION结构:  SOC_CICOM_CK_31_0_UL_UNION */
#define SOC_CICOM_CK_31_0_UL_ADDR(base)         ((base) + (0x0030))

/* 寄存器说明：[加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[63:32]。
   位域定义UNION结构:  SOC_CICOM_CK_63_32_UL_UNION */
#define SOC_CICOM_CK_63_32_UL_ADDR(base)        ((base) + (0x0034))

/* 寄存器说明：[加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[95:64]。
   位域定义UNION结构:  SOC_CICOM_CK_95_64_UL_UNION */
#define SOC_CICOM_CK_95_64_UL_ADDR(base)        ((base) + (0x0038))

/* 寄存器说明：[加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[127:96]。
   位域定义UNION结构:  SOC_CICOM_CK_127_96_UL_UNION */
#define SOC_CICOM_CK_127_96_UL_ADDR(base)       ((base) + (0x003C))

/* 寄存器说明：[加密]CC参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CC参数。
   位域定义UNION结构:  SOC_CICOM_CC_UL_UNION */
#define SOC_CICOM_CC_UL_ADDR(base)              ((base) + (0x0040))

/* 寄存器说明：[加密]PDU包数据总长度寄存器。
            读该寄存器返回当前正在加密的PDU包的数据总长度，以比特数为单位。
   位域定义UNION结构:  SOC_CICOM_PDU_TOTAL_LEN_UL_UNION */
#define SOC_CICOM_PDU_TOTAL_LEN_UL_ADDR(base)   ((base) + (0x0044))

/* 寄存器说明：[加密]处理方式寄存器。
            读该寄存器返回当前正在加密的PDU包的数据处理方式。包括该PDU包的源数据是否分段、目的数据是否分段、是否产生密钥、是否将产生的密钥与源数据相异或等。
   位域定义UNION结构:  SOC_CICOM_CUSTOM_CFG_UL_UNION */
#define SOC_CICOM_CUSTOM_CFG_UL_ADDR(base)      ((base) + (0x0048))

/* 寄存器说明：[加密]源数据段起始地址寄存器。
            读该寄存器返回当前正在加密的源数据段的起始地址。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_ADDR_UL_UNION */
#define SOC_CICOM_SRC_SEG_ADDR_UL_ADDR(base)    ((base) + (0x004C))

/* 寄存器说明：[加密]源数据段长度寄存器。
            读该寄存器返回当前正在加密的源数据段的长度，以比特数为单位。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_LEN_UL_UNION */
#define SOC_CICOM_SRC_SEG_LEN_UL_ADDR(base)     ((base) + (0x0050))

/* 寄存器说明：[加密]下一个SRC链表起始地址寄存器。
            读该寄存器返回下一个SRC链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_ADDR(base) ((base) + (0x0054))

/* 寄存器说明：[加密]目的数据段存放于DST1 Memory的起始地址寄存器。
            读该寄存器返回当前正在写入DST1 Memory的目的数据段的起始地址。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_ADDR_UL_UNION */
#define SOC_CICOM_DST1_SEG_ADDR_UL_ADDR(base)   ((base) + (0x0058))

/* 寄存器说明：[加密]存放于DST1 Memory的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST1 Memory中的目的数据段的长度。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_LEN_UL_UNION */
#define SOC_CICOM_DST1_SEG_LEN_UL_ADDR(base)    ((base) + (0x005C))

/* 寄存器说明：[加密]下一个DST1链表起始地址寄存器。
            读该寄存器返回下一个DST1链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_ADDR(base) ((base) + (0x0060))

/* 寄存器说明：[加密]目的数据段存放于DST2中的起始地址寄存器。
            读该寄存器返回当前正在写入DST2中的目的数据段的起始地址。
   位域定义UNION结构:  SOC_CICOM_DST2_SEG_ADDR_UL_UNION */
#define SOC_CICOM_DST2_SEG_ADDR_UL_ADDR(base)   ((base) + (0x0064))

/* 寄存器说明：[加密]存放于DST2中的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST2中的目的数据段的长度。
   位域定义UNION结构:  SOC_CICOM_DST2_SEG_LEN_UL_UNION */
#define SOC_CICOM_DST2_SEG_LEN_UL_ADDR(base)    ((base) + (0x0068))

/* 寄存器说明：[加密]下一个DST2链表起始地址寄存器。
            读该寄存器返回下一个DST2链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION */
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_ADDR(base) ((base) + (0x006C))

/* 寄存器说明：[加密]出错地址寄存器。
            读该寄存器返回加密过程中AXI SLAVE侧反馈ERROR响应时的访问地址。
   位域定义UNION结构:  SOC_CICOM_ERROR_ADDR_UL_UNION */
#define SOC_CICOM_ERROR_ADDR_UL_ADDR(base)      ((base) + (0x0070))

/* 寄存器说明：[加密]源数据段当前读地址寄存器。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION */
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_ADDR(base) ((base) + (0x0074))

/* 寄存器说明：[加密]当前源数据段中剩余未读取数据长度寄存器。以字节（Byte）数为单位。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0078))

/* 寄存器说明：[加密]DST1目的数据段当前写地址寄存器。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION */
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_ADDR(base) ((base) + (0x007C))

/* 寄存器说明：[加密]当前DST1目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：[加密]DST2目的数据段当前写地址寄存器。
   位域定义UNION结构:  SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION */
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：[加密]当前DST2目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
   位域定义UNION结构:  SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION */
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_ADDR(base) ((base) + (0x0088))

/* 寄存器说明：[解密]参数链表起始地址寄存器。
            该寄存器用于设置解密时，第一个PDU包对应的参数链表的起始地址。
            在解密处理过程中，该寄存器的值由硬件自动更新为当前正在解密的PDU包对应的参数链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_PARAM_ADDR_DL_UNION */
#define SOC_CICOM_LLI_PARAM_ADDR_DL_ADDR(base)  ((base) + (0x0108))

/* 寄存器说明：[解密]全局解密参数配置寄存器。
            该寄存器用于配置一次运行只需配置一次，不需按照PDU包粒度更新的解密参数。
   位域定义UNION结构:  SOC_CICOM_GLOBAL_CFG_DL_UNION */
#define SOC_CICOM_GLOBAL_CFG_DL_ADDR(base)      ((base) + (0x010C))

/* 寄存器说明：[解密]中断使能/屏蔽寄存器。
            写该寄存器设置各解密中断使能或屏蔽。
   位域定义UNION结构:  SOC_CICOM_INT_EN_DL_UNION */
#define SOC_CICOM_INT_EN_DL_ADDR(base)          ((base) + (0x0118))

/* 寄存器说明：[解密]原始中断状态寄存器。
            读该寄存器返回各中断的原始中断状态。
   位域定义UNION结构:  SOC_CICOM_INT_RAW_DL_UNION */
#define SOC_CICOM_INT_RAW_DL_ADDR(base)         ((base) + (0x011C))

/* 寄存器说明：[解密]中断状态清除寄存器。
            向该寄存器的相应bit写1'b1清除对应解密中断，写1'b0无影响。
            读该寄存器返回值为0x0。
   位域定义UNION结构:  SOC_CICOM_INT_CLR_DL_UNION */
#define SOC_CICOM_INT_CLR_DL_ADDR(base)         ((base) + (0x0120))

/* 寄存器说明：[解密]屏蔽后的解密中断状态寄存器。
            读该寄存器返回各解密中断的屏蔽后中断状态。
   位域定义UNION结构:  SOC_CICOM_INT_MSK_DL_UNION */
#define SOC_CICOM_INT_MSK_DL_ADDR(base)         ((base) + (0x0124))

/* 寄存器说明：[解密]使能寄存器。
            软件准备好链表并配置好解密参数寄存器之后，向该寄存器的bit[0]写入1'b1启动解密操作。
            解密操作完成后，由硬件自动对该寄存器清零。
            解密过程出错时，硬件也会对该寄存器自动清零，使内部状态机返回IDLE状态。
            读该寄存器返回解密处理状态。
                返回值为0x0，表示CICOM没有进行解密处理。
                返回值为0x1，表示CICOM正在进行解密处理；
   位域定义UNION结构:  SOC_CICOM_EN_DL_UNION */
#define SOC_CICOM_EN_DL_ADDR(base)              ((base) + (0x0128))

/* 寄存器说明：[解密]CK参数在外部Memory中的地址寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数存放于外部Memory中的起始地址。
   位域定义UNION结构:  SOC_CICOM_CK_ADDR_DL_UNION */
#define SOC_CICOM_CK_ADDR_DL_ADDR(base)         ((base) + (0x012C))

/* 寄存器说明：[解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[31:0]。
   位域定义UNION结构:  SOC_CICOM_CK_31_0_DL_UNION */
#define SOC_CICOM_CK_31_0_DL_ADDR(base)         ((base) + (0x0130))

/* 寄存器说明：[解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[63:32]。
   位域定义UNION结构:  SOC_CICOM_CK_63_32_DL_UNION */
#define SOC_CICOM_CK_63_32_DL_ADDR(base)        ((base) + (0x0134))

/* 寄存器说明：[解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[95:64]。
   位域定义UNION结构:  SOC_CICOM_CK_95_64_DL_UNION */
#define SOC_CICOM_CK_95_64_DL_ADDR(base)        ((base) + (0x0138))

/* 寄存器说明：[解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[127:96]。
   位域定义UNION结构:  SOC_CICOM_CK_127_96_DL_UNION */
#define SOC_CICOM_CK_127_96_DL_ADDR(base)       ((base) + (0x013C))

/* 寄存器说明：[解密]CC参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CC参数。
   位域定义UNION结构:  SOC_CICOM_CC_DL_UNION */
#define SOC_CICOM_CC_DL_ADDR(base)              ((base) + (0x0140))

/* 寄存器说明：[解密]PDU包数据总长度寄存器。
            读该寄存器返回当前正在解密的PDU包的数据总长度，以比特数为单位。
   位域定义UNION结构:  SOC_CICOM_PDU_TOTAL_LEN_DL_UNION */
#define SOC_CICOM_PDU_TOTAL_LEN_DL_ADDR(base)   ((base) + (0x0144))

/* 寄存器说明：[解密]处理方式寄存器。
            读该寄存器返回当前正在解密的PDU包的数据处理方式。包括该PDU包的源数据是否分段、目的数据是否分段、是否产生密钥、是否将产生的密钥与源数据相异或等。
   位域定义UNION结构:  SOC_CICOM_CUSTOM_CFG_DL_UNION */
#define SOC_CICOM_CUSTOM_CFG_DL_ADDR(base)      ((base) + (0x0148))

/* 寄存器说明：[解密]源数据段起始地址寄存器。
            读该寄存器返回当前正在解密的源数据段的起始地址。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_ADDR_DL_UNION */
#define SOC_CICOM_SRC_SEG_ADDR_DL_ADDR(base)    ((base) + (0x014C))

/* 寄存器说明：[解密]源数据段长度寄存器。
            读该寄存器返回当前正在解密的源数据段的长度，以比特数为单位。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_LEN_DL_UNION */
#define SOC_CICOM_SRC_SEG_LEN_DL_ADDR(base)     ((base) + (0x0150))

/* 寄存器说明：[解密]下一个SRC链表起始地址寄存器。
            读该寄存器返回下一个SRC链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION */
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_ADDR(base) ((base) + (0x0154))

/* 寄存器说明：[解密]目的数据段存放于DST1 Memory的起始地址寄存器。
            读该寄存器返回当前正在写入DST1 Memory的目的数据段的起始地址。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_ADDR_DL_UNION */
#define SOC_CICOM_DST1_SEG_ADDR_DL_ADDR(base)   ((base) + (0x0158))

/* 寄存器说明：[解密]存放于DST1 Memory的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST1 Memory中的目的数据段的长度。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_LEN_DL_UNION */
#define SOC_CICOM_DST1_SEG_LEN_DL_ADDR(base)    ((base) + (0x015C))

/* 寄存器说明：[解密]下一个DST1链表起始地址寄存器。
            读该寄存器返回下一个DST1链表的起始地址。
   位域定义UNION结构:  SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION */
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_ADDR(base) ((base) + (0x0160))

/* 寄存器说明：[解密]出错地址寄存器。
            读该寄存器返回解密过程中AXI SLAVE侧反馈ERROR响应时的访问地址。
   位域定义UNION结构:  SOC_CICOM_ERROR_ADDR_DL_UNION */
#define SOC_CICOM_ERROR_ADDR_DL_ADDR(base)      ((base) + (0x0170))

/* 寄存器说明：[解密]源数据段当前读地址寄存器。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION */
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_ADDR(base) ((base) + (0x0174))

/* 寄存器说明：[解密]当前源数据段中剩余未读取数据长度寄存器。以字节（Byte）数为单位。
   位域定义UNION结构:  SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION */
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_ADDR(base) ((base) + (0x0178))

/* 寄存器说明：[解密]DST1目的数据段当前写地址寄存器。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION */
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_ADDR(base) ((base) + (0x017C))

/* 寄存器说明：[解密]当前DST1目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
   位域定义UNION结构:  SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION */
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_ADDR(base) ((base) + (0x0180))





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
                     (1/1) CICOM
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CICOM_STATE_RESET_UNION
 结构说明  : STATE_RESET 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: [加解密共用]CICOM软复位寄存器。
            软件发现CICOM异常时，向该寄存器的bit[0]写入1'b1，对CICOM模块进行软复位。
            读该寄存器返回值为0x0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cicom_state_reset : 1;  /* bit[0]   : 向该bit位写入1'b1实现对CICOM的软复位，写0无影响。
                                                            读时返回0。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CICOM_STATE_RESET_UNION;
#endif
#define SOC_CICOM_STATE_RESET_cicom_state_reset_START  (0)
#define SOC_CICOM_STATE_RESET_cicom_state_reset_END    (0)


/*****************************************************************************
 结构名    : SOC_CICOM_PRIOR_SELECT_UNION
 结构说明  : PRIOR_SELECT 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: [加解密共用]仲裁策略选择寄存器。
            写该寄存器设置加密请求与解密请求的仲裁策略。
            注：在加解密处理过程中，允许软件对该寄存器进行改写，以更新仲裁策略。但是频繁切换仲裁策略会导致加解密反复交替进行。因此建议软件不要频繁更新仲裁策略。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prior_select : 2;  /* bit[0-1] : 加密请求与解密请求的仲裁策略选择信号。
                                                       2'b00：先到先服务。即加密请求先有效则先处理加密；解密请求先有效，则先处理解密。正在处理的加密处理和解密过程都不允许被打断。后配置使能的加密或者解密必须等先配置使能的加密或者解密的处理完毕后，才能开始处理。
                                                       2'b01：加密优先。解密过程允许被加密请求打断。如果解密进行过程中，加密请求有效，则将当前PDU包解密完成后，切换到加密处理。加密处理不允许被解密请求打断。须等当次加密的所有PDU包都处理完毕后，才能切换到解密处理。
                                                       2'b10：解密优先。加密过程允许被解密请求打断。如果加密进行过程中，解密请求有效，则将当前PDU包加密完成后，切换到解密处理。解密处理不允许被加密请求打断。须等当次解密的所有PDU包都处理完毕后，才能切换到加密处理。
                                                       2'b11：非法配置。 */
        unsigned int  reserved     : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_CICOM_PRIOR_SELECT_UNION;
#endif
#define SOC_CICOM_PRIOR_SELECT_prior_select_START  (0)
#define SOC_CICOM_PRIOR_SELECT_prior_select_END    (1)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_PARAM_ADDR_UL_UNION
 结构说明  : LLI_PARAM_ADDR_UL 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: [加密]参数链表起始地址寄存器。
            该寄存器用于设置加密时，第一个PDU包对应的参数链表的起始地址。
            在加密处理过程中，该寄存器的值由硬件自动更新为当前正在加密的PDU包对应的参数链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_param_addr_ul : 32; /* bit[0-31]: 写该寄存器配置加密时第一个参数链表的起始地址。注意：该地址要求8字节（64bit）对齐。
                                                            读该寄存器返回当前正在加密的PDU包对应的参数链表起始地址。
                                                            后续链表的起始地址由硬件从前一个链表中读取，并更新到该寄存器中供软件查询，便于调试时获知当前正在加密的PDU包对应的参数链表起始地址。 */
    } reg;
} SOC_CICOM_LLI_PARAM_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_PARAM_ADDR_UL_lli_param_addr_ul_START  (0)
#define SOC_CICOM_LLI_PARAM_ADDR_UL_lli_param_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_GLOBAL_CFG_UL_UNION
 结构说明  : GLOBAL_CFG_UL 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: [加密]全局加密参数配置寄存器。
            该寄存器用于配置一次运行只需配置一次，不需按照PDU包粒度更新的加密参数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alg_sel_ul    : 2;  /* bit[0-1]  : 用于设置加密算法。
                                                         2'b00：W模下不选择算法；G模下不选择算法；
                                                         2'b01：W模下选择UEA1算法；G模下选择GEA1算法；
                                                         2'b10：W模下选择UEA2算法；G模下选择GEA2算法；
                                                         2'b11：W模下不选择算法；G模下选择GEA3算法； */
        unsigned int  reserved_0    : 6;  /* bit[2-7]  : 保留 */
        unsigned int  offset_len_ul : 4;  /* bit[8-11] : 用于设置加密时的数据偏移长度。以字节数位单位。
                                                         举例而言，若该域配置为4'b0011，则当次加密的各个PDU包都偏移3个字节进行加密处理。即各个PDU包中最先读入的3个字节不进行加密处理，直接写到DDR中。而未偏移的部分则需与对应的密钥异或之后，再写到DDR中。 */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: 保留 */
        unsigned int  bearer_ul     : 5;  /* bit[16-20]: 用于设置W模加密参数CB即BAERER。 */
        unsigned int  reserved_2    : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_CICOM_GLOBAL_CFG_UL_UNION;
#endif
#define SOC_CICOM_GLOBAL_CFG_UL_alg_sel_ul_START     (0)
#define SOC_CICOM_GLOBAL_CFG_UL_alg_sel_ul_END       (1)
#define SOC_CICOM_GLOBAL_CFG_UL_offset_len_ul_START  (8)
#define SOC_CICOM_GLOBAL_CFG_UL_offset_len_ul_END    (11)
#define SOC_CICOM_GLOBAL_CFG_UL_bearer_ul_START      (16)
#define SOC_CICOM_GLOBAL_CFG_UL_bearer_ul_END        (20)


/*****************************************************************************
 结构名    : SOC_CICOM_CHL_FST_ADDR_UL_UNION
 结构说明  : CHL_FST_ADDR_UL 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: [加密]环形缓存信道首地址寄存器。
            W模加密时，软件根据当次运行所需操作的信道配置CHL_FST_ADDR_UL和CHL_LST_ADDR_UL寄存器。
            当需要向DST2中写入加密目的数据时，硬件根据DST2目的数据段起始地址DST2_SEG_ADDR_UL和数据段长度DST2_SEG_LEN_UL以及环形缓存信道首、末地址自动判断是否需要绕回。若需要绕回，则绕回后从该配置地址续写。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chl_fst_addr_ul : 32; /* bit[0-31]: 用于设置W模加密时环形缓存信道的首地址。
                                                          注意：CHL_FST_ADDR_UL和（CHL_LST_ADDR_UL+32'h1）要求8字节（64bit）对齐。 */
    } reg;
} SOC_CICOM_CHL_FST_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CHL_FST_ADDR_UL_chl_fst_addr_ul_START  (0)
#define SOC_CICOM_CHL_FST_ADDR_UL_chl_fst_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CHL_LST_ADDR_UL_UNION
 结构说明  : CHL_LST_ADDR_UL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: [加密]环形缓存信道末地址寄存器。
            W模加密时，软件根据当次运行所需操作的信道配置CHL_FST_ADDR_UL和CHL_LST_ADDR_UL寄存器。
            当需要向DST2中写入加密目的数据时，硬件根据DST2目的数据段起始地址DST2_SEG_ADDR_UL和数据段长度DST2_SEG_LEN_UL以及环形缓存信道首、末地址自动判断是否需要绕回。若需要绕回，则写到该配置地址时开始绕回。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chl_lst_addr_ul : 32; /* bit[0-31]: 用于设置W模加密时环形缓存信道的末地址。
                                                          注意：CHL_FST_ADDR_UL和（CHL_LST_ADDR_UL+32'h1）要求8字节（64bit）对齐。 */
    } reg;
} SOC_CICOM_CHL_LST_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CHL_LST_ADDR_UL_chl_lst_addr_ul_START  (0)
#define SOC_CICOM_CHL_LST_ADDR_UL_chl_lst_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_EN_UL_UNION
 结构说明  : INT_EN_UL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: [加密]中断使能/屏蔽寄存器。
            写该寄存器设置各加密中断使能或屏蔽。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_en_ul                : 1;  /* bit[0]   : 加密完成中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  src_addr_error_en_ul     : 1;  /* bit[1]   : 加密源数据地址配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  axi_error_en_ul          : 1;  /* bit[2]   : 加密AXI出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  chl_addr_error_en_ul     : 1;  /* bit[3]   : 加密信道地址配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  src_seg_len_error_en_ul  : 1;  /* bit[4]   : 加密源数据段长度配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  dst1_seg_len_error_en_ul : 1;  /* bit[5]   : 加密DST1目的数据段长度配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  dst2_seg_len_error_en_ul : 1;  /* bit[6]   : 加密DST2目的数据段长度配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  ck_addr_error_en_ul      : 1;  /* bit[7]   : 加密CK地址配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  reserved                 : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_EN_UL_UNION;
#endif
#define SOC_CICOM_INT_EN_UL_end_en_ul_START                 (0)
#define SOC_CICOM_INT_EN_UL_end_en_ul_END                   (0)
#define SOC_CICOM_INT_EN_UL_src_addr_error_en_ul_START      (1)
#define SOC_CICOM_INT_EN_UL_src_addr_error_en_ul_END        (1)
#define SOC_CICOM_INT_EN_UL_axi_error_en_ul_START           (2)
#define SOC_CICOM_INT_EN_UL_axi_error_en_ul_END             (2)
#define SOC_CICOM_INT_EN_UL_chl_addr_error_en_ul_START      (3)
#define SOC_CICOM_INT_EN_UL_chl_addr_error_en_ul_END        (3)
#define SOC_CICOM_INT_EN_UL_src_seg_len_error_en_ul_START   (4)
#define SOC_CICOM_INT_EN_UL_src_seg_len_error_en_ul_END     (4)
#define SOC_CICOM_INT_EN_UL_dst1_seg_len_error_en_ul_START  (5)
#define SOC_CICOM_INT_EN_UL_dst1_seg_len_error_en_ul_END    (5)
#define SOC_CICOM_INT_EN_UL_dst2_seg_len_error_en_ul_START  (6)
#define SOC_CICOM_INT_EN_UL_dst2_seg_len_error_en_ul_END    (6)
#define SOC_CICOM_INT_EN_UL_ck_addr_error_en_ul_START       (7)
#define SOC_CICOM_INT_EN_UL_ck_addr_error_en_ul_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_RAW_UL_UNION
 结构说明  : INT_RAW_UL 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: [加密]原始中断状态寄存器。
            读该寄存器返回各中断的原始中断状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_raw_ul                : 1;  /* bit[0]   : 原始加密完成中断状态。
                                                                    当次加密运行的所有PDU包都处理完毕时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_addr_error_raw_ul     : 1;  /* bit[1]   : 原始加密源数据地址配置出错中断状态。
                                                                    加密时，参数链表中配置的PDU包总长度大于0，且下一个SRC链表地址为0时，该中断有效。或者SRC链表中配置的源数据段长度大于0，但是数据段地址为0时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  axi_error_raw_ul          : 1;  /* bit[2]   : 原始加密AXI出错中断状态。
                                                                    加密时，AXI侧反馈ERROR响应时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  chl_addr_error_raw_ul     : 1;  /* bit[3]   : 原始加密信道地址配置出错中断状态。
                                                                    加密时，链表中配置的DST2目的数据段地址不在寄存器CHL_FST_ADDR_UL和CHL_LST_ADDR_UL的配置值范围内时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_seg_len_error_raw_ul  : 1;  /* bit[4]   : 原始加密源数据段长度配置出错中断状态。
                                                                    SRC链表中配置的各源数据段长度之和不等于PDU包总长度时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst1_seg_len_error_raw_ul : 1;  /* bit[5]   : 原始加密DST1目的数据段长度配置出错中断状态。
                                                                    加密时，DST1链表中配置的各DST1目的数据段长度之和不等于PDU包总长度时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst2_seg_len_error_raw_ul : 1;  /* bit[6]   : 原始加密DST2目的数据段长度配置出错中断状态。
                                                                    加密时，DST2链表中配置的各DST2目的数据段长度之和不等于PDU包总长度时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  ck_addr_error_raw_ul      : 1;  /* bit[7]   : 原始加密密钥地址配置出错中断状态。
                                                                    加密时，参数链表第四项CUSTOM_CFG的bit[1:0]配置为2'b01或者2'b11，且参数链表第一项CK_ADDR配置为32'h0，或者非8字节对齐即CK_ADDR的bit[2:0]不等于3'b000时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_RAW_UL_UNION;
#endif
#define SOC_CICOM_INT_RAW_UL_end_raw_ul_START                 (0)
#define SOC_CICOM_INT_RAW_UL_end_raw_ul_END                   (0)
#define SOC_CICOM_INT_RAW_UL_src_addr_error_raw_ul_START      (1)
#define SOC_CICOM_INT_RAW_UL_src_addr_error_raw_ul_END        (1)
#define SOC_CICOM_INT_RAW_UL_axi_error_raw_ul_START           (2)
#define SOC_CICOM_INT_RAW_UL_axi_error_raw_ul_END             (2)
#define SOC_CICOM_INT_RAW_UL_chl_addr_error_raw_ul_START      (3)
#define SOC_CICOM_INT_RAW_UL_chl_addr_error_raw_ul_END        (3)
#define SOC_CICOM_INT_RAW_UL_src_seg_len_error_raw_ul_START   (4)
#define SOC_CICOM_INT_RAW_UL_src_seg_len_error_raw_ul_END     (4)
#define SOC_CICOM_INT_RAW_UL_dst1_seg_len_error_raw_ul_START  (5)
#define SOC_CICOM_INT_RAW_UL_dst1_seg_len_error_raw_ul_END    (5)
#define SOC_CICOM_INT_RAW_UL_dst2_seg_len_error_raw_ul_START  (6)
#define SOC_CICOM_INT_RAW_UL_dst2_seg_len_error_raw_ul_END    (6)
#define SOC_CICOM_INT_RAW_UL_ck_addr_error_raw_ul_START       (7)
#define SOC_CICOM_INT_RAW_UL_ck_addr_error_raw_ul_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_CLR_UL_UNION
 结构说明  : INT_CLR_UL 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: [加密]中断状态清除寄存器。
            向该寄存器的相应bit写1'b1清除对应加密中断，写1'b0无影响。
            读该寄存器返回值为0x0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_clr_ul                : 1;  /* bit[0]   : 加密完成中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  src_addr_error_clr_ul     : 1;  /* bit[1]   : 加密源数据地址配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  axi_error_clr_ul          : 1;  /* bit[2]   : 加密AXI出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  chl_addr_error_clr_ul     : 1;  /* bit[3]   : 加密信道地址配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  src_seg_len_error_clr_ul  : 1;  /* bit[4]   : 加密源数据段长度配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  dst1_seg_len_error_clr_ul : 1;  /* bit[5]   : 加密DST1目的数据段长度配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  dst2_seg_len_error_clr_ul : 1;  /* bit[6]   : 加密DST2目的数据段长度配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  ck_addr_error_clr_ul      : 1;  /* bit[7]   : 加密密钥地址配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_CLR_UL_UNION;
#endif
#define SOC_CICOM_INT_CLR_UL_end_clr_ul_START                 (0)
#define SOC_CICOM_INT_CLR_UL_end_clr_ul_END                   (0)
#define SOC_CICOM_INT_CLR_UL_src_addr_error_clr_ul_START      (1)
#define SOC_CICOM_INT_CLR_UL_src_addr_error_clr_ul_END        (1)
#define SOC_CICOM_INT_CLR_UL_axi_error_clr_ul_START           (2)
#define SOC_CICOM_INT_CLR_UL_axi_error_clr_ul_END             (2)
#define SOC_CICOM_INT_CLR_UL_chl_addr_error_clr_ul_START      (3)
#define SOC_CICOM_INT_CLR_UL_chl_addr_error_clr_ul_END        (3)
#define SOC_CICOM_INT_CLR_UL_src_seg_len_error_clr_ul_START   (4)
#define SOC_CICOM_INT_CLR_UL_src_seg_len_error_clr_ul_END     (4)
#define SOC_CICOM_INT_CLR_UL_dst1_seg_len_error_clr_ul_START  (5)
#define SOC_CICOM_INT_CLR_UL_dst1_seg_len_error_clr_ul_END    (5)
#define SOC_CICOM_INT_CLR_UL_dst2_seg_len_error_clr_ul_START  (6)
#define SOC_CICOM_INT_CLR_UL_dst2_seg_len_error_clr_ul_END    (6)
#define SOC_CICOM_INT_CLR_UL_ck_addr_error_clr_ul_START       (7)
#define SOC_CICOM_INT_CLR_UL_ck_addr_error_clr_ul_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_MSK_UL_UNION
 结构说明  : INT_MSK_UL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: [加密]屏蔽后的加密中断状态寄存器。
            读该寄存器返回各加密中断的屏蔽后中断状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_msk_ul                : 1;  /* bit[0]   : 屏蔽后的加密完成中断状态。
                                                                    当次加密运行的所有PDU包都处理完毕，且该中断未被屏蔽时有效。。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_addr_error_msk_ul     : 1;  /* bit[1]   : 屏蔽后的加密源数据地址配置出错中断状态。
                                                                    加密时，参数链表中配置的PDU包总长度大于0，且下一个SRC链表地址为0；或者SRC链表中配置的源数据段长度大于0，但是数据段地址为0，且该中断未被屏蔽时有效。。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  axi_error_msk_ul          : 1;  /* bit[2]   : 屏蔽后的加密AXI出错中断状态。
                                                                    加密时，AXI侧反馈ERROR响应，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  chl_addr_error_msk_ul     : 1;  /* bit[3]   : 屏蔽后的加密信道地址配置出错中断状态。
                                                                    加密时，链表中配置的DST2目的数据段地址不在寄存器CHL_FST_ADDR_UL和CHL_LST_ADDR_UL的配置值范围内，且该中断未被屏蔽时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_seg_len_error_msk_ul  : 1;  /* bit[4]   : 屏蔽后的加密源数据段长度配置出错中断状态。
                                                                    SRC链表中配置的各源数据段长度之和不等于PDU包总长度，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst1_seg_len_error_msk_ul : 1;  /* bit[5]   : 屏蔽后的加密DST1目的数据段长度配置出错中断状态。
                                                                    加密时，DST1链表中配置的各DST1目的数据段长度之和不等于PDU包总长度，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst2_seg_len_error_msk_ul : 1;  /* bit[6]   : 屏蔽后的加密DST2目的数据段长度配置出错中断状态。
                                                                    加密时，DST2链表中配置的各DST2目的数据段长度之和不等于PDU包总长度，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  ck_addr_error_msk_ul      : 1;  /* bit[7]   : 屏蔽后的加密密钥地址配置出错中断状态。
                                                                    加密时，参数链表第四项CUSTOM_CFG的bit[1:0]配置为2'b01或者2'b11，且参数链表第一项CK_ADDR配置为32'h0，或者非8字节对齐即CK_ADDR的bit[2:0]不等于3'b000，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_MSK_UL_UNION;
#endif
#define SOC_CICOM_INT_MSK_UL_end_msk_ul_START                 (0)
#define SOC_CICOM_INT_MSK_UL_end_msk_ul_END                   (0)
#define SOC_CICOM_INT_MSK_UL_src_addr_error_msk_ul_START      (1)
#define SOC_CICOM_INT_MSK_UL_src_addr_error_msk_ul_END        (1)
#define SOC_CICOM_INT_MSK_UL_axi_error_msk_ul_START           (2)
#define SOC_CICOM_INT_MSK_UL_axi_error_msk_ul_END             (2)
#define SOC_CICOM_INT_MSK_UL_chl_addr_error_msk_ul_START      (3)
#define SOC_CICOM_INT_MSK_UL_chl_addr_error_msk_ul_END        (3)
#define SOC_CICOM_INT_MSK_UL_src_seg_len_error_msk_ul_START   (4)
#define SOC_CICOM_INT_MSK_UL_src_seg_len_error_msk_ul_END     (4)
#define SOC_CICOM_INT_MSK_UL_dst1_seg_len_error_msk_ul_START  (5)
#define SOC_CICOM_INT_MSK_UL_dst1_seg_len_error_msk_ul_END    (5)
#define SOC_CICOM_INT_MSK_UL_dst2_seg_len_error_msk_ul_START  (6)
#define SOC_CICOM_INT_MSK_UL_dst2_seg_len_error_msk_ul_END    (6)
#define SOC_CICOM_INT_MSK_UL_ck_addr_error_msk_ul_START       (7)
#define SOC_CICOM_INT_MSK_UL_ck_addr_error_msk_ul_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_EN_UL_UNION
 结构说明  : EN_UL 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: [加密]使能寄存器。
            软件准备好链表并配置好加密参数寄存器之后，向该寄存器的bit[0]写入1'b1启动加密操作。
            加密操作完成后，由硬件自动对该寄存器清零。
            加密过程出错时，硬件也会对该寄存器自动清零，使内部状态机返回IDLE状态。
            读该寄存器返回加密处理状态。
                返回值为0x0，表示CICOM没有进行加密处理。
                返回值为0x1，表示CICOM正在进行加密处理；
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en_ul    : 1;  /* bit[0]   : 写时设置加密使能：
                                                   0：不使能加密处理；
                                                   1：使能加密处理；
                                                   读时返回加密处理状态：
                                                   0：未在进行加密处理；
                                                   1：正在进行加密处理； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CICOM_EN_UL_UNION;
#endif
#define SOC_CICOM_EN_UL_en_ul_START     (0)
#define SOC_CICOM_EN_UL_en_ul_END       (0)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_ADDR_UL_UNION
 结构说明  : CK_ADDR_UL 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: [加密]CK参数在外部Memory中的地址寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数存放于外部Memory中的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_addr_ul : 32; /* bit[0-31]: 当前正在加密的PDU包对应的CK参数在外部Memory中存放的起始地址。 */
    } reg;
} SOC_CICOM_CK_ADDR_UL_UNION;
#endif
#define SOC_CICOM_CK_ADDR_UL_ck_addr_ul_START  (0)
#define SOC_CICOM_CK_ADDR_UL_ck_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_31_0_UL_UNION
 结构说明  : CK_31_0_UL 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: [加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[31:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_31_0_ul : 32; /* bit[0-31]: W模时，当前正在加密的PDU包对应的CK参数即CONF_KEY的bit[31:0]。
                                                     G模时，当前正在加密的PDU包对应的CK参数即KC_LOW。 */
    } reg;
} SOC_CICOM_CK_31_0_UL_UNION;
#endif
#define SOC_CICOM_CK_31_0_UL_ck_31_0_ul_START  (0)
#define SOC_CICOM_CK_31_0_UL_ck_31_0_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_63_32_UL_UNION
 结构说明  : CK_63_32_UL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: [加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[63:32]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_63_32_ul : 32; /* bit[0-31]: W模时，当前正在加密的PDU包对应的CK参数即CONF_KEY的bit[63:32]。
                                                      G模时，当前正在加密的PDU包对应的CK参数即KC_HIGH。 */
    } reg;
} SOC_CICOM_CK_63_32_UL_UNION;
#endif
#define SOC_CICOM_CK_63_32_UL_ck_63_32_ul_START  (0)
#define SOC_CICOM_CK_63_32_UL_ck_63_32_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_95_64_UL_UNION
 结构说明  : CK_95_64_UL 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: [加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[95:64]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_95_64_ul : 32; /* bit[0-31]: W模时，当前正在加密的PDU包对应的CK参数即CONF_KEY的bit[95:64]。
                                                      G模时，返回值为0x0。 */
    } reg;
} SOC_CICOM_CK_95_64_UL_UNION;
#endif
#define SOC_CICOM_CK_95_64_UL_ck_95_64_ul_START  (0)
#define SOC_CICOM_CK_95_64_UL_ck_95_64_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_127_96_UL_UNION
 结构说明  : CK_127_96_UL 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: [加密]CK参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CK参数的bit[127:96]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_127_96_ul : 32; /* bit[0-31]: W模时，当前正在加密的PDU包对应的CK参数即CONF_KEY的bit[127:96]。
                                                       G模时，返回值为0x0。 */
    } reg;
} SOC_CICOM_CK_127_96_UL_UNION;
#endif
#define SOC_CICOM_CK_127_96_UL_ck_127_96_ul_START  (0)
#define SOC_CICOM_CK_127_96_UL_ck_127_96_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CC_UL_UNION
 结构说明  : CC_UL 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: [加密]CC参数寄存器。
            读该寄存器返回当前正在加密的PDU包对应的CC参数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_ul : 32; /* bit[0-31]: W模时，当前正在加密的PDU包对应的CC参数即COUNT。
                                                G模时，当前正在加密的PDU包对应的CC参数即Message_key */
    } reg;
} SOC_CICOM_CC_UL_UNION;
#endif
#define SOC_CICOM_CC_UL_cc_ul_START  (0)
#define SOC_CICOM_CC_UL_cc_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_PDU_TOTAL_LEN_UL_UNION
 结构说明  : PDU_TOTAL_LEN_UL 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: [加密]PDU包数据总长度寄存器。
            读该寄存器返回当前正在加密的PDU包的数据总长度，以比特数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdu_total_len_ul : 16; /* bit[0-15] : 当前正在加密的PDU包的数据总长度。
                                                            单位为比特数（bit）。 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_PDU_TOTAL_LEN_UL_UNION;
#endif
#define SOC_CICOM_PDU_TOTAL_LEN_UL_pdu_total_len_ul_START  (0)
#define SOC_CICOM_PDU_TOTAL_LEN_UL_pdu_total_len_ul_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_CUSTOM_CFG_UL_UNION
 结构说明  : CUSTOM_CFG_UL 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: [加密]处理方式寄存器。
            读该寄存器返回当前正在加密的PDU包的数据处理方式。包括该PDU包的源数据是否分段、目的数据是否分段、是否产生密钥、是否将产生的密钥与源数据相异或等。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key_xor_src_ul : 2;  /* bit[0-1]  : 当前正在加密的PDU包的数据处理方式：
                                                          2'b00:不做任何操作。
                                                          2'b01: 仅生成密钥：根据参数配置生成密钥，并将密钥搬运到指定目的地址。
                                                          2'b10: 仅搬运源数据：不生成密钥，仅将源数据搬运到指定目的地址。
                                                          2'b11: 机密操作：根据参数配置生成密钥，将生成的密钥与对应的源数据异或，得到加解密的目的数据，并将目的数据搬运到指定目的地址。 */
        unsigned int  reserved_0     : 6;  /* bit[2-7]  : 保留。 */
        unsigned int  src_seg_en_ul  : 1;  /* bit[8]    : 当前正在加密的PDU包数据的源数据是否分段：
                                                          0:不分段；
                                                          1:分段； */
        unsigned int  reserved_1     : 7;  /* bit[9-15] : 保留。 */
        unsigned int  dst1_seg_en_ul : 1;  /* bit[16]   : 当前正在加密的PDU包搬运到DST1 Memory中的目的数据是否分段：
                                                          0:不分段；
                                                          1:分段； */
        unsigned int  reserved_2     : 7;  /* bit[17-23]: 保留。 */
        unsigned int  dst2_seg_en_ul : 1;  /* bit[24]   : 当前正在加密的PDU包搬运到DST2中的目的数据是否分段：
                                                          0:不分段；
                                                          1:分段； */
        unsigned int  reserved_3     : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_CICOM_CUSTOM_CFG_UL_UNION;
#endif
#define SOC_CICOM_CUSTOM_CFG_UL_key_xor_src_ul_START  (0)
#define SOC_CICOM_CUSTOM_CFG_UL_key_xor_src_ul_END    (1)
#define SOC_CICOM_CUSTOM_CFG_UL_src_seg_en_ul_START   (8)
#define SOC_CICOM_CUSTOM_CFG_UL_src_seg_en_ul_END     (8)
#define SOC_CICOM_CUSTOM_CFG_UL_dst1_seg_en_ul_START  (16)
#define SOC_CICOM_CUSTOM_CFG_UL_dst1_seg_en_ul_END    (16)
#define SOC_CICOM_CUSTOM_CFG_UL_dst2_seg_en_ul_START  (24)
#define SOC_CICOM_CUSTOM_CFG_UL_dst2_seg_en_ul_END    (24)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_ADDR_UL_UNION
 结构说明  : SRC_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: [加密]源数据段起始地址寄存器。
            读该寄存器返回当前正在加密的源数据段的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_addr_ul : 32; /* bit[0-31]: 当前正在加密的源数据段的起始地址。 */
    } reg;
} SOC_CICOM_SRC_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_ADDR_UL_src_seg_addr_ul_START  (0)
#define SOC_CICOM_SRC_SEG_ADDR_UL_src_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_LEN_UL_UNION
 结构说明  : SRC_SEG_LEN_UL 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: [加密]源数据段长度寄存器。
            读该寄存器返回当前正在加密的源数据段的长度，以比特数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_len_ul : 16; /* bit[0-15] : 当前正在加密的源数据段的长度。
                                                          单位为比特数（bit）。 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_SRC_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEN_UL_src_seg_len_ul_START  (0)
#define SOC_CICOM_SRC_SEG_LEN_UL_src_seg_len_ul_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION
 结构说明  : LLI_SRC_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: [加密]下一个SRC链表起始地址寄存器。
            读该寄存器返回下一个SRC链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_src_seg_addr_ul : 32; /* bit[0-31]: 下一个SRC链表的起始地址。 */
    } reg;
} SOC_CICOM_LLI_SRC_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_lli_src_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_SRC_SEG_ADDR_UL_lli_src_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_ADDR_UL_UNION
 结构说明  : DST1_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: [加密]目的数据段存放于DST1 Memory的起始地址寄存器。
            读该寄存器返回当前正在写入DST1 Memory的目的数据段的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_addr_ul : 32; /* bit[0-31]: 当前正在加写入DST1 Memory中的目的数据段的起始地址。 */
    } reg;
} SOC_CICOM_DST1_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_ADDR_UL_dst1_seg_addr_ul_START  (0)
#define SOC_CICOM_DST1_SEG_ADDR_UL_dst1_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_LEN_UL_UNION
 结构说明  : DST1_SEG_LEN_UL 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: [加密]存放于DST1 Memory的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST1 Memory中的目的数据段的长度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_len_ul : 16; /* bit[0-15] : 当前正在写入DST1 Memory中的目的数据段的长度。
                                                           单位为比特数（bit）。 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_DST1_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEN_UL_dst1_seg_len_ul_START  (0)
#define SOC_CICOM_DST1_SEG_LEN_UL_dst1_seg_len_ul_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION
 结构说明  : LLI_DST1_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: [加密]下一个DST1链表起始地址寄存器。
            读该寄存器返回下一个DST1链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst1_seg_addr_ul : 32; /* bit[0-31]: 下一个DST1链表的起始地址。 */
    } reg;
} SOC_CICOM_LLI_DST1_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_lli_dst1_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_DST1_SEG_ADDR_UL_lli_dst1_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST2_SEG_ADDR_UL_UNION
 结构说明  : DST2_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: [加密]目的数据段存放于DST2中的起始地址寄存器。
            读该寄存器返回当前正在写入DST2中的目的数据段的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_addr_ul : 32; /* bit[0-31]: 当前正在写入DST2的目的数据段的起始地址。 */
    } reg;
} SOC_CICOM_DST2_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_ADDR_UL_dst2_seg_addr_ul_START  (0)
#define SOC_CICOM_DST2_SEG_ADDR_UL_dst2_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST2_SEG_LEN_UL_UNION
 结构说明  : DST2_SEG_LEN_UL 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: [加密]存放于DST2中的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST2中的目的数据段的长度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_len_ul : 16; /* bit[0-15] : 当前正在写入DST2的目的数据段的长度。
                                                           单位为比特数（bit）。 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_DST2_SEG_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_LEN_UL_dst2_seg_len_ul_START  (0)
#define SOC_CICOM_DST2_SEG_LEN_UL_dst2_seg_len_ul_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION
 结构说明  : LLI_DST2_SEG_ADDR_UL 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: [加密]下一个DST2链表起始地址寄存器。
            读该寄存器返回下一个DST2链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst2_seg_addr_ul : 32; /* bit[0-31]: 下一个DST2链表的起始地址。 */
    } reg;
} SOC_CICOM_LLI_DST2_SEG_ADDR_UL_UNION;
#endif
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_lli_dst2_seg_addr_ul_START  (0)
#define SOC_CICOM_LLI_DST2_SEG_ADDR_UL_lli_dst2_seg_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_ERROR_ADDR_UL_UNION
 结构说明  : ERROR_ADDR_UL 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: [加密]出错地址寄存器。
            读该寄存器返回加密过程中AXI SLAVE侧反馈ERROR响应时的访问地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  error_addr_ul : 32; /* bit[0-31]: 加密过程中发生错误时的访问地址。 */
    } reg;
} SOC_CICOM_ERROR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_ERROR_ADDR_UL_error_addr_ul_START  (0)
#define SOC_CICOM_ERROR_ADDR_UL_error_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION
 结构说明  : SRC_SEG_RD_ADDR_UL 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: [加密]源数据段当前读地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_rd_addr_ul : 32; /* bit[0-31]: 加密过程中源数据段的当前读地址。 */
    } reg;
} SOC_CICOM_SRC_SEG_RD_ADDR_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_src_seg_rd_addr_ul_START  (0)
#define SOC_CICOM_SRC_SEG_RD_ADDR_UL_src_seg_rd_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION
 结构说明  : SRC_SEG_LEAVE_LEN_UL 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: [加密]当前源数据段中剩余未读取数据长度寄存器。以字节（Byte）数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_leave_len_ul : 14; /* bit[0-13] : 加密过程中当前源数据段中剩余未读取数据字节个数。 */
        unsigned int  reserved             : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_src_seg_leave_len_ul_START  (0)
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_UL_src_seg_leave_len_ul_END    (13)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION
 结构说明  : DST1_SEG_WR_ADDR_UL 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: [加密]DST1目的数据段当前写地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_wr_addr_ul : 32; /* bit[0-31]: 加密过程中DST1目的数据段当前写地址。 */
    } reg;
} SOC_CICOM_DST1_SEG_WR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_dst1_seg_wr_addr_ul_START  (0)
#define SOC_CICOM_DST1_SEG_WR_ADDR_UL_dst1_seg_wr_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION
 结构说明  : DST1_SEG_LEAVE_LEN_UL 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: [加密]当前DST1目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_leave_len_ul : 14; /* bit[0-13] : 加密过程中当前DST1目的数据段中剩余未写数据字节个数。 */
        unsigned int  reserved              : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_dst1_seg_leave_len_ul_START  (0)
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_UL_dst1_seg_leave_len_ul_END    (13)


/*****************************************************************************
 结构名    : SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION
 结构说明  : DST2_SEG_WR_ADDR_UL 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: [加密]DST2目的数据段当前写地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_wr_addr_ul : 32; /* bit[0-31]: 加密过程中DST2目的数据段当前写地址。 */
    } reg;
} SOC_CICOM_DST2_SEG_WR_ADDR_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_dst2_seg_wr_addr_ul_START  (0)
#define SOC_CICOM_DST2_SEG_WR_ADDR_UL_dst2_seg_wr_addr_ul_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION
 结构说明  : DST2_SEG_LEAVE_LEN_UL 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: [加密]当前DST2目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst2_seg_leave_len_ul : 14; /* bit[0-13] : 加密过程中当前DST2目的数据段中剩余未写数据字节个数。 */
        unsigned int  reserved              : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_UNION;
#endif
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_dst2_seg_leave_len_ul_START  (0)
#define SOC_CICOM_DST2_SEG_LEAVE_LEN_UL_dst2_seg_leave_len_ul_END    (13)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_PARAM_ADDR_DL_UNION
 结构说明  : LLI_PARAM_ADDR_DL 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: [解密]参数链表起始地址寄存器。
            该寄存器用于设置解密时，第一个PDU包对应的参数链表的起始地址。
            在解密处理过程中，该寄存器的值由硬件自动更新为当前正在解密的PDU包对应的参数链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_param_addr_dl : 32; /* bit[0-31]: 写该寄存器配置解密时第一个参数链表的起始地址。注意：该地址要求8字节（64bit）对齐。
                                                            读该寄存器返回当前正在解密的PDU包对应的参数链表起始地址。
                                                            后续链表的起始地址由硬件从前一个链表中读取，并更新到该寄存器中供软件查询，便于调试时获知当前正在解密的PDU包对应的参数链表起始地址。 */
    } reg;
} SOC_CICOM_LLI_PARAM_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_PARAM_ADDR_DL_lli_param_addr_dl_START  (0)
#define SOC_CICOM_LLI_PARAM_ADDR_DL_lli_param_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_GLOBAL_CFG_DL_UNION
 结构说明  : GLOBAL_CFG_DL 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: [解密]全局解密参数配置寄存器。
            该寄存器用于配置一次运行只需配置一次，不需按照PDU包粒度更新的解密参数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alg_sel_dl    : 2;  /* bit[0-1]  : 用于设置解密算法。
                                                         2'b00：W模下不选择算法；G模下不选择算法；
                                                         2'b01：W模下选择UEA1算法；G模下选择GEA1算法；
                                                         2'b10：W模下选择UEA2算法；G模下选择GEA2算法；
                                                         2'b11：W模下不选择算法；G模下选择GEA3算法； */
        unsigned int  reserved_0    : 6;  /* bit[2-7]  : 保留 */
        unsigned int  offset_len_dl : 4;  /* bit[8-11] : 用于设置解密时的数据偏移长度。以字节数位单位。
                                                         举例而言，若该域配置为4'b0011，则当次解密的各个PDU包都偏移3个字节进行解密处理。即各个PDU包中最先读入的3个字节不进行解密处理，直接写到DDR中。而未偏移的部分则需与对应的密钥异或之后，再写到DDR中。 */
        unsigned int  reserved_1    : 4;  /* bit[12-15]: 保留 */
        unsigned int  bearer_dl     : 5;  /* bit[16-20]: 用于设置W模解密参数CB即BAERER。 */
        unsigned int  reserved_2    : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_CICOM_GLOBAL_CFG_DL_UNION;
#endif
#define SOC_CICOM_GLOBAL_CFG_DL_alg_sel_dl_START     (0)
#define SOC_CICOM_GLOBAL_CFG_DL_alg_sel_dl_END       (1)
#define SOC_CICOM_GLOBAL_CFG_DL_offset_len_dl_START  (8)
#define SOC_CICOM_GLOBAL_CFG_DL_offset_len_dl_END    (11)
#define SOC_CICOM_GLOBAL_CFG_DL_bearer_dl_START      (16)
#define SOC_CICOM_GLOBAL_CFG_DL_bearer_dl_END        (20)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_EN_DL_UNION
 结构说明  : INT_EN_DL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: [解密]中断使能/屏蔽寄存器。
            写该寄存器设置各解密中断使能或屏蔽。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_en_dl                : 1;  /* bit[0]   : 解密完成中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  src_addr_error_en_dl     : 1;  /* bit[1]   : 解密源数据地址配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  axi_error_en_dl          : 1;  /* bit[2]   : 解密AXI出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  reserved_0               : 1;  /* bit[3]   : 保留。 */
        unsigned int  src_seg_len_error_en_dl  : 1;  /* bit[4]   : 解密源数据段长度配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  dst1_seg_len_error_en_dl : 1;  /* bit[5]   : 解密DST1目的数据段长度配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  reserved_1               : 1;  /* bit[6]   : 保留。 */
        unsigned int  ck_addr_error_en_dl      : 1;  /* bit[7]   : 解密CK地址配置出错中断使能/屏蔽。
                                                                   0：中断屏蔽；
                                                                   1：中断使能； */
        unsigned int  reserved_2               : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_EN_DL_UNION;
#endif
#define SOC_CICOM_INT_EN_DL_end_en_dl_START                 (0)
#define SOC_CICOM_INT_EN_DL_end_en_dl_END                   (0)
#define SOC_CICOM_INT_EN_DL_src_addr_error_en_dl_START      (1)
#define SOC_CICOM_INT_EN_DL_src_addr_error_en_dl_END        (1)
#define SOC_CICOM_INT_EN_DL_axi_error_en_dl_START           (2)
#define SOC_CICOM_INT_EN_DL_axi_error_en_dl_END             (2)
#define SOC_CICOM_INT_EN_DL_src_seg_len_error_en_dl_START   (4)
#define SOC_CICOM_INT_EN_DL_src_seg_len_error_en_dl_END     (4)
#define SOC_CICOM_INT_EN_DL_dst1_seg_len_error_en_dl_START  (5)
#define SOC_CICOM_INT_EN_DL_dst1_seg_len_error_en_dl_END    (5)
#define SOC_CICOM_INT_EN_DL_ck_addr_error_en_dl_START       (7)
#define SOC_CICOM_INT_EN_DL_ck_addr_error_en_dl_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_RAW_DL_UNION
 结构说明  : INT_RAW_DL 寄存器结构定义。地址偏移量:0x011C，初值:0x00000000，宽度:32
 寄存器说明: [解密]原始中断状态寄存器。
            读该寄存器返回各中断的原始中断状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_raw_dl                : 1;  /* bit[0]   : 原始解密完成中断状态。
                                                                    当次解密运行的所有PDU包都处理完毕时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_addr_error_raw_dl     : 1;  /* bit[1]   : 原始解密源数据地址配置出错中断状态。
                                                                    解密时，参数链表中配置的PDU包总长度大于0，且下一个SRC链表地址为0时，该中断有效。或者SRC链表中配置的源数据段长度大于0，但是数据段地址为0时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  axi_error_raw_dl          : 1;  /* bit[2]   : 原始解密AXI出错中断状态。
                                                                    解密过程中，AXI侧反馈ERROR响应时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_0                : 1;  /* bit[3]   : 保留。 */
        unsigned int  src_seg_len_error_raw_dl  : 1;  /* bit[4]   : 原始解密源数据段长度配置出错中断状态。
                                                                    解密时，SRC链表中配置的各源数据段长度之和不等于PDU包总长度时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst1_seg_len_error_raw_dl : 1;  /* bit[5]   : 原始解密DST1目的数据段长度配置出错中断状态。
                                                                    解密时，DST1链表中配置的各DST1目的数据段长度之和不等于PDU包总长度时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_1                : 1;  /* bit[6]   : 保留。 */
        unsigned int  ck_addr_error_raw_dl      : 1;  /* bit[7]   : 原始解密密钥地址配置出错中断状态。
                                                                    解密时，参数链表第四项CUSTOM_CFG的bit[1:0]配置为2'b01或者2'b11，且参数链表第一项CK_ADDR配置为32'h0，或者非8字节对齐即CK_ADDR的bit[2:0]不等于3'b000时，该中断有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_2                : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_RAW_DL_UNION;
#endif
#define SOC_CICOM_INT_RAW_DL_end_raw_dl_START                 (0)
#define SOC_CICOM_INT_RAW_DL_end_raw_dl_END                   (0)
#define SOC_CICOM_INT_RAW_DL_src_addr_error_raw_dl_START      (1)
#define SOC_CICOM_INT_RAW_DL_src_addr_error_raw_dl_END        (1)
#define SOC_CICOM_INT_RAW_DL_axi_error_raw_dl_START           (2)
#define SOC_CICOM_INT_RAW_DL_axi_error_raw_dl_END             (2)
#define SOC_CICOM_INT_RAW_DL_src_seg_len_error_raw_dl_START   (4)
#define SOC_CICOM_INT_RAW_DL_src_seg_len_error_raw_dl_END     (4)
#define SOC_CICOM_INT_RAW_DL_dst1_seg_len_error_raw_dl_START  (5)
#define SOC_CICOM_INT_RAW_DL_dst1_seg_len_error_raw_dl_END    (5)
#define SOC_CICOM_INT_RAW_DL_ck_addr_error_raw_dl_START       (7)
#define SOC_CICOM_INT_RAW_DL_ck_addr_error_raw_dl_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_CLR_DL_UNION
 结构说明  : INT_CLR_DL 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: [解密]中断状态清除寄存器。
            向该寄存器的相应bit写1'b1清除对应解密中断，写1'b0无影响。
            读该寄存器返回值为0x0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_clr_dl                : 1;  /* bit[0]   : 解密完成中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  src_addr_error_clr_dl     : 1;  /* bit[1]   : 解密源数据地址配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  axi_error_clr_dl          : 1;  /* bit[2]   : 解密AXI出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  reserved_0                : 1;  /* bit[3]   : 保留。 */
        unsigned int  src_seg_len_error_clr_dl  : 1;  /* bit[4]   : 解密源数据段长度配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  dst1_seg_len_error_clr_dl : 1;  /* bit[5]   : 解密DST1目的数据段长度配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  reserved_1                : 1;  /* bit[6]   : 保留。 */
        unsigned int  ck_addr_error_clr_dl      : 1;  /* bit[7]   : 解密密钥地址配置出错中断状态清除。
                                                                    写1'b1清除中断，写1'b0无影响。 */
        unsigned int  reserved_2                : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_CLR_DL_UNION;
#endif
#define SOC_CICOM_INT_CLR_DL_end_clr_dl_START                 (0)
#define SOC_CICOM_INT_CLR_DL_end_clr_dl_END                   (0)
#define SOC_CICOM_INT_CLR_DL_src_addr_error_clr_dl_START      (1)
#define SOC_CICOM_INT_CLR_DL_src_addr_error_clr_dl_END        (1)
#define SOC_CICOM_INT_CLR_DL_axi_error_clr_dl_START           (2)
#define SOC_CICOM_INT_CLR_DL_axi_error_clr_dl_END             (2)
#define SOC_CICOM_INT_CLR_DL_src_seg_len_error_clr_dl_START   (4)
#define SOC_CICOM_INT_CLR_DL_src_seg_len_error_clr_dl_END     (4)
#define SOC_CICOM_INT_CLR_DL_dst1_seg_len_error_clr_dl_START  (5)
#define SOC_CICOM_INT_CLR_DL_dst1_seg_len_error_clr_dl_END    (5)
#define SOC_CICOM_INT_CLR_DL_ck_addr_error_clr_dl_START       (7)
#define SOC_CICOM_INT_CLR_DL_ck_addr_error_clr_dl_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_INT_MSK_DL_UNION
 结构说明  : INT_MSK_DL 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: [解密]屏蔽后的解密中断状态寄存器。
            读该寄存器返回各解密中断的屏蔽后中断状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  end_msk_dl                : 1;  /* bit[0]   : 屏蔽后的解密完成中断状态。
                                                                    当次解密运行的所有PDU包都处理完毕，且该中断未被屏蔽时有效。。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  src_addr_error_msk_dl     : 1;  /* bit[1]   : 屏蔽后的解密源数据地址配置出错中断状态。
                                                                    解密时，参数链表中配置的PDU包总长度大于0，且下一个SRC链表地址为0；或者SRC链表中配置的源数据段长度大于0，但是数据段地址为0，且该中断未被屏蔽时有效。。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  axi_error_msk_dl          : 1;  /* bit[2]   : 屏蔽后的解密AXI出错中断状态。
                                                                    解密时，AXI侧反馈ERROR响应，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_0                : 1;  /* bit[3]   : 保留。 */
        unsigned int  src_seg_len_error_msk_dl  : 1;  /* bit[4]   : 屏蔽后的解密源数据段长度配置出错中断状态。
                                                                    解密时，SRC链表中配置的各源数据段长度之和不等于PDU包总长度，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  dst1_seg_len_error_msk_dl : 1;  /* bit[5]   : 屏蔽后的解密DST1目的数据段长度配置出错中断状态。
                                                                    解密时，DST1链表中配置的各DST1目的数据段长度之和不等于PDU包总长度，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_1                : 1;  /* bit[6]   : 保留。 */
        unsigned int  ck_addr_error_msk_dl      : 1;  /* bit[7]   : 屏蔽后的解密密钥地址配置出错中断状态。
                                                                    解密时，参数链表第四项CUSTOM_CFG的bit[1:0]配置为2'b01或者2'b11，且参数链表第一项CK_ADDR配置为32'h0，或者非8字节对齐即CK_ADDR的bit[2:0]不等于3'b000，且该中断未被屏蔽时有效。
                                                                    0：中断无效；
                                                                    1：中断有效； */
        unsigned int  reserved_2                : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_CICOM_INT_MSK_DL_UNION;
#endif
#define SOC_CICOM_INT_MSK_DL_end_msk_dl_START                 (0)
#define SOC_CICOM_INT_MSK_DL_end_msk_dl_END                   (0)
#define SOC_CICOM_INT_MSK_DL_src_addr_error_msk_dl_START      (1)
#define SOC_CICOM_INT_MSK_DL_src_addr_error_msk_dl_END        (1)
#define SOC_CICOM_INT_MSK_DL_axi_error_msk_dl_START           (2)
#define SOC_CICOM_INT_MSK_DL_axi_error_msk_dl_END             (2)
#define SOC_CICOM_INT_MSK_DL_src_seg_len_error_msk_dl_START   (4)
#define SOC_CICOM_INT_MSK_DL_src_seg_len_error_msk_dl_END     (4)
#define SOC_CICOM_INT_MSK_DL_dst1_seg_len_error_msk_dl_START  (5)
#define SOC_CICOM_INT_MSK_DL_dst1_seg_len_error_msk_dl_END    (5)
#define SOC_CICOM_INT_MSK_DL_ck_addr_error_msk_dl_START       (7)
#define SOC_CICOM_INT_MSK_DL_ck_addr_error_msk_dl_END         (7)


/*****************************************************************************
 结构名    : SOC_CICOM_EN_DL_UNION
 结构说明  : EN_DL 寄存器结构定义。地址偏移量:0x0128，初值:0x00000000，宽度:32
 寄存器说明: [解密]使能寄存器。
            软件准备好链表并配置好解密参数寄存器之后，向该寄存器的bit[0]写入1'b1启动解密操作。
            解密操作完成后，由硬件自动对该寄存器清零。
            解密过程出错时，硬件也会对该寄存器自动清零，使内部状态机返回IDLE状态。
            读该寄存器返回解密处理状态。
                返回值为0x0，表示CICOM没有进行解密处理。
                返回值为0x1，表示CICOM正在进行解密处理；
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en_dl    : 1;  /* bit[0]   : 写时设置解密使能：
                                                   0：不使能解密处理；
                                                   1：使能解密处理；
                                                   读时返回解密处理状态：
                                                   0：未在进行解密处理；
                                                   1：正在进行解密处理； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CICOM_EN_DL_UNION;
#endif
#define SOC_CICOM_EN_DL_en_dl_START     (0)
#define SOC_CICOM_EN_DL_en_dl_END       (0)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_ADDR_DL_UNION
 结构说明  : CK_ADDR_DL 寄存器结构定义。地址偏移量:0x012C，初值:0x00000000，宽度:32
 寄存器说明: [解密]CK参数在外部Memory中的地址寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数存放于外部Memory中的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_addr_dl : 32; /* bit[0-31]: 当前正在解密的PDU包对应的CK参数在外部Memory中存放的起始地址。 */
    } reg;
} SOC_CICOM_CK_ADDR_DL_UNION;
#endif
#define SOC_CICOM_CK_ADDR_DL_ck_addr_dl_START  (0)
#define SOC_CICOM_CK_ADDR_DL_ck_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_31_0_DL_UNION
 结构说明  : CK_31_0_DL 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: [解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[31:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_31_0_dl : 32; /* bit[0-31]: W模时，当前正在解密的PDU包对应的CK参数即CONF_KEY的bit[31:0]。
                                                     G模时，当前正在解密的PDU包对应的CK参数即KC_LOW。 */
    } reg;
} SOC_CICOM_CK_31_0_DL_UNION;
#endif
#define SOC_CICOM_CK_31_0_DL_ck_31_0_dl_START  (0)
#define SOC_CICOM_CK_31_0_DL_ck_31_0_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_63_32_DL_UNION
 结构说明  : CK_63_32_DL 寄存器结构定义。地址偏移量:0x0134，初值:0x00000000，宽度:32
 寄存器说明: [解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[63:32]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_63_32_dl : 32; /* bit[0-31]: W模时，当前正在解密的PDU包对应的CK参数即CONF_KEY的bit[63:32]。
                                                      G模时，当前正在解密的PDU包对应的CK参数即KC_HIGH。 */
    } reg;
} SOC_CICOM_CK_63_32_DL_UNION;
#endif
#define SOC_CICOM_CK_63_32_DL_ck_63_32_dl_START  (0)
#define SOC_CICOM_CK_63_32_DL_ck_63_32_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_95_64_DL_UNION
 结构说明  : CK_95_64_DL 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: [解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[95:64]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_95_64_dl : 32; /* bit[0-31]: W模时，当前正在解密的PDU包对应的CK参数即CONF_KEY的bit[95:64]。
                                                      G模时，返回值为0x0。 */
    } reg;
} SOC_CICOM_CK_95_64_DL_UNION;
#endif
#define SOC_CICOM_CK_95_64_DL_ck_95_64_dl_START  (0)
#define SOC_CICOM_CK_95_64_DL_ck_95_64_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CK_127_96_DL_UNION
 结构说明  : CK_127_96_DL 寄存器结构定义。地址偏移量:0x013C，初值:0x00000000，宽度:32
 寄存器说明: [解密]CK参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CK参数的bit[127:96]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ck_127_96_dl : 32; /* bit[0-31]: W模时，当前正在解密的PDU包对应的CK参数即CONF_KEY的bit[127:96]。
                                                       G模时，返回值为0x0。 */
    } reg;
} SOC_CICOM_CK_127_96_DL_UNION;
#endif
#define SOC_CICOM_CK_127_96_DL_ck_127_96_dl_START  (0)
#define SOC_CICOM_CK_127_96_DL_ck_127_96_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_CC_DL_UNION
 结构说明  : CC_DL 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: [解密]CC参数寄存器。
            读该寄存器返回当前正在解密的PDU包对应的CC参数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cc_dl : 32; /* bit[0-31]: W模时，当前正在解密的PDU包对应的CC参数即COUNT。
                                                G模时，当前正在解密的PDU包对应的CC参数即Message_key */
    } reg;
} SOC_CICOM_CC_DL_UNION;
#endif
#define SOC_CICOM_CC_DL_cc_dl_START  (0)
#define SOC_CICOM_CC_DL_cc_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_PDU_TOTAL_LEN_DL_UNION
 结构说明  : PDU_TOTAL_LEN_DL 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: [解密]PDU包数据总长度寄存器。
            读该寄存器返回当前正在解密的PDU包的数据总长度，以比特数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pdu_total_len_dl : 16; /* bit[0-15] : 当前正在解密的PDU包的数据总长度。
                                                            单位为比特数（bit）。 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_PDU_TOTAL_LEN_DL_UNION;
#endif
#define SOC_CICOM_PDU_TOTAL_LEN_DL_pdu_total_len_dl_START  (0)
#define SOC_CICOM_PDU_TOTAL_LEN_DL_pdu_total_len_dl_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_CUSTOM_CFG_DL_UNION
 结构说明  : CUSTOM_CFG_DL 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: [解密]处理方式寄存器。
            读该寄存器返回当前正在解密的PDU包的数据处理方式。包括该PDU包的源数据是否分段、目的数据是否分段、是否产生密钥、是否将产生的密钥与源数据相异或等。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key_xor_src_dl : 2;  /* bit[0-1]  : 当前正在解密的PDU包的数据处理方式：
                                                          2'b00:不做任何操作。
                                                          2'b01: 仅生成密钥：根据参数配置生成密钥，并将密钥搬运到指定目的地址。
                                                          2'b10: 仅搬运源数据：不生成密钥，仅将源数据搬运到指定目的地址。
                                                          2'b11: 机密操作：根据参数配置生成密钥，将生成的密钥与对应的源数据异或，得到加解密的目的数据，并将目的数据搬运到指定目的地址。 */
        unsigned int  reserved_0     : 6;  /* bit[2-7]  : 保留。 */
        unsigned int  src_seg_en_dl  : 1;  /* bit[8]    : 当前正在解密的PDU包数据的源数据是否分段：
                                                          0:不分段；
                                                          1:分段； */
        unsigned int  reserved_1     : 7;  /* bit[9-15] : 保留。 */
        unsigned int  dst1_seg_en_dl : 1;  /* bit[16]   : 当前正在解密的PDU包搬运到DST1 Memory中的目的数据是否分段：
                                                          0:不分段；
                                                          1:分段； */
        unsigned int  reserved_2     : 7;  /* bit[17-23]: 保留。 */
        unsigned int  reserved_3     : 1;  /* bit[24]   : 保留。 */
        unsigned int  reserved_4     : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_CICOM_CUSTOM_CFG_DL_UNION;
#endif
#define SOC_CICOM_CUSTOM_CFG_DL_key_xor_src_dl_START  (0)
#define SOC_CICOM_CUSTOM_CFG_DL_key_xor_src_dl_END    (1)
#define SOC_CICOM_CUSTOM_CFG_DL_src_seg_en_dl_START   (8)
#define SOC_CICOM_CUSTOM_CFG_DL_src_seg_en_dl_END     (8)
#define SOC_CICOM_CUSTOM_CFG_DL_dst1_seg_en_dl_START  (16)
#define SOC_CICOM_CUSTOM_CFG_DL_dst1_seg_en_dl_END    (16)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_ADDR_DL_UNION
 结构说明  : SRC_SEG_ADDR_DL 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: [解密]源数据段起始地址寄存器。
            读该寄存器返回当前正在解密的源数据段的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_addr_dl : 32; /* bit[0-31]: 当前正在解密的源数据段的起始地址。 */
    } reg;
} SOC_CICOM_SRC_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_ADDR_DL_src_seg_addr_dl_START  (0)
#define SOC_CICOM_SRC_SEG_ADDR_DL_src_seg_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_LEN_DL_UNION
 结构说明  : SRC_SEG_LEN_DL 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: [解密]源数据段长度寄存器。
            读该寄存器返回当前正在解密的源数据段的长度，以比特数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_len_dl : 16; /* bit[0-15] : 当前正在解密的源数据段的长度。
                                                          单位为比特数（bit）。 */
        unsigned int  reserved       : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_SRC_SEG_LEN_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEN_DL_src_seg_len_dl_START  (0)
#define SOC_CICOM_SRC_SEG_LEN_DL_src_seg_len_dl_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION
 结构说明  : LLI_SRC_SEG_ADDR_DL 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: [解密]下一个SRC链表起始地址寄存器。
            读该寄存器返回下一个SRC链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_src_seg_addr_dl : 32; /* bit[0-31]: 下一个SRC链表的起始地址。 */
    } reg;
} SOC_CICOM_LLI_SRC_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_lli_src_seg_addr_dl_START  (0)
#define SOC_CICOM_LLI_SRC_SEG_ADDR_DL_lli_src_seg_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_ADDR_DL_UNION
 结构说明  : DST1_SEG_ADDR_DL 寄存器结构定义。地址偏移量:0x0158，初值:0x00000000，宽度:32
 寄存器说明: [解密]目的数据段存放于DST1 Memory的起始地址寄存器。
            读该寄存器返回当前正在写入DST1 Memory的目的数据段的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_addr_dl : 32; /* bit[0-31]: 当前正在加写入DST1 Memory中的目的数据段的起始地址。 */
    } reg;
} SOC_CICOM_DST1_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_ADDR_DL_dst1_seg_addr_dl_START  (0)
#define SOC_CICOM_DST1_SEG_ADDR_DL_dst1_seg_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_LEN_DL_UNION
 结构说明  : DST1_SEG_LEN_DL 寄存器结构定义。地址偏移量:0x015C，初值:0x00000000，宽度:32
 寄存器说明: [解密]存放于DST1 Memory的目的数据段长度寄存器。
            读该寄存器返回当前正在写入DST1 Memory中的目的数据段的长度。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_len_dl : 16; /* bit[0-15] : 当前正在写入DST1 Memory中的目的数据段的长度。
                                                           单位为比特数（bit）。 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CICOM_DST1_SEG_LEN_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEN_DL_dst1_seg_len_dl_START  (0)
#define SOC_CICOM_DST1_SEG_LEN_DL_dst1_seg_len_dl_END    (15)


/*****************************************************************************
 结构名    : SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION
 结构说明  : LLI_DST1_SEG_ADDR_DL 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: [解密]下一个DST1链表起始地址寄存器。
            读该寄存器返回下一个DST1链表的起始地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lli_dst1_seg_addr_dl : 32; /* bit[0-31]: 下一个DST1链表的起始地址。 */
    } reg;
} SOC_CICOM_LLI_DST1_SEG_ADDR_DL_UNION;
#endif
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_lli_dst1_seg_addr_dl_START  (0)
#define SOC_CICOM_LLI_DST1_SEG_ADDR_DL_lli_dst1_seg_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_ERROR_ADDR_DL_UNION
 结构说明  : ERROR_ADDR_DL 寄存器结构定义。地址偏移量:0x0170，初值:0x00000000，宽度:32
 寄存器说明: [解密]出错地址寄存器。
            读该寄存器返回解密过程中AXI SLAVE侧反馈ERROR响应时的访问地址。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  error_addr_dl : 32; /* bit[0-31]: 解密过程中发生错误时的访问地址。 */
    } reg;
} SOC_CICOM_ERROR_ADDR_DL_UNION;
#endif
#define SOC_CICOM_ERROR_ADDR_DL_error_addr_dl_START  (0)
#define SOC_CICOM_ERROR_ADDR_DL_error_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION
 结构说明  : SRC_SEG_RD_ADDR_DL 寄存器结构定义。地址偏移量:0x0174，初值:0x00000000，宽度:32
 寄存器说明: [解密]源数据段当前读地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_rd_addr_dl : 32; /* bit[0-31]: 解密过程中源数据段的当前读地址。 */
    } reg;
} SOC_CICOM_SRC_SEG_RD_ADDR_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_src_seg_rd_addr_dl_START  (0)
#define SOC_CICOM_SRC_SEG_RD_ADDR_DL_src_seg_rd_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION
 结构说明  : SRC_SEG_LEAVE_LEN_DL 寄存器结构定义。地址偏移量:0x0178，初值:0x00000000，宽度:32
 寄存器说明: [解密]当前源数据段中剩余未读取数据长度寄存器。以字节（Byte）数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  src_seg_leave_len_dl : 14; /* bit[0-13] : 解密过程中当前源数据段中剩余未读取数据字节个数。 */
        unsigned int  reserved             : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_UNION;
#endif
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_src_seg_leave_len_dl_START  (0)
#define SOC_CICOM_SRC_SEG_LEAVE_LEN_DL_src_seg_leave_len_dl_END    (13)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION
 结构说明  : DST1_SEG_WR_ADDR_DL 寄存器结构定义。地址偏移量:0x017C，初值:0x00000000，宽度:32
 寄存器说明: [解密]DST1目的数据段当前写地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_wr_addr_dl : 32; /* bit[0-31]: 解密过程中DST1目的数据段当前写地址。 */
    } reg;
} SOC_CICOM_DST1_SEG_WR_ADDR_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_dst1_seg_wr_addr_dl_START  (0)
#define SOC_CICOM_DST1_SEG_WR_ADDR_DL_dst1_seg_wr_addr_dl_END    (31)


/*****************************************************************************
 结构名    : SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION
 结构说明  : DST1_SEG_LEAVE_LEN_DL 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: [解密]当前DST1目的数据段中剩余未写数据长度寄存器。以字节（Byte）数为单位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dst1_seg_leave_len_dl : 14; /* bit[0-13] : 解密过程中当前DST1目的数据段中剩余未写数据字节个数。 */
        unsigned int  reserved              : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_UNION;
#endif
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_dst1_seg_leave_len_dl_START  (0)
#define SOC_CICOM_DST1_SEG_LEAVE_LEN_DL_dst1_seg_leave_len_dl_END    (13)

/* 以下为转定义寄存器，非自动生成 */
#define SOC_CIPHER_REG_ADDR(base, offset) ((base)+(offset))
#define SOC_CIPHER_CICOM_STATE_RESET(BaseAddr)                     SOC_CICOM_STATE_RESET_ADDR(BaseAddr)
#define SOC_CIPHER_PRIOR_SELECT(BaseAddr)                          SOC_CICOM_PRIOR_SELECT_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_PARAM_ADDR_UL(BaseAddr)                     SOC_CICOM_LLI_PARAM_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_GLOBAL_CFG_UL(BaseAddr)                         SOC_CICOM_GLOBAL_CFG_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CHL_FST_ADDR_UL(BaseAddr)                       SOC_CICOM_CHL_FST_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CHL_LST_ADDR_UL(BaseAddr)                       SOC_CICOM_CHL_LST_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_EN_UL(BaseAddr)                             SOC_CICOM_INT_EN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_RAW_UL(BaseAddr)                            SOC_CICOM_INT_RAW_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_CLR_UL(BaseAddr)                            SOC_CICOM_INT_CLR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_INT_MSK_UL(BaseAddr)                            SOC_CICOM_INT_MSK_UL_ADDR(BaseAddr)
#define SOC_CIPHER_EN_UL(BaseAddr)                                 SOC_CICOM_EN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_ADDR_UL(BaseAddr)                            SOC_CICOM_CK_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_31_0_UL(BaseAddr)                            SOC_CICOM_CK_31_0_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_63_32_UL(BaseAddr)                           SOC_CICOM_CK_63_32_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_95_64_UL(BaseAddr)                           SOC_CICOM_CK_95_64_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CK_127_96_UL(BaseAddr)                          SOC_CICOM_CK_127_96_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CC_UL(BaseAddr)                                 SOC_CICOM_CC_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_TOTAL_LEN_UL(BaseAddr)                  SOC_CICOM_PDU_TOTAL_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_CUSTOM_CFG_UL(BaseAddr)                         SOC_CICOM_CUSTOM_CFG_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_SRC_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_PDU_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_SRC_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_SRC_PDU_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_SRC_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_TTF_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_DST1_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_TTF_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_DST1_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_DST_TTF_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_DST1_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_MBX_SEG_ADDR_UL(BaseAddr)                   SOC_CICOM_DST2_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_DST_MBX_SEG_LEN_UL(BaseAddr)                    SOC_CICOM_DST2_SEG_LEN_UL_ADDR(BaseAddr)
#define SOC_CIPHER_LLI_DST_MBX_SEG_ADDR_UL(BaseAddr)               SOC_CICOM_LLI_DST2_SEG_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_ERROR_ADDR_UL(BaseAddr)                         SOC_CICOM_ERROR_ADDR_UL_ADDR(BaseAddr)
#define SOC_CIPHER_SRC_SEG_RD_ADDR_UL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0074)
#define SOC_CIPHER_SRC_SEG_LEAVE_LEN_UL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0078)
#define SOC_CIPHER_DST1_SEG_WR_ADDR_UL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x007c)
#define SOC_CIPHER_DST1_SEG_LEAVE_LEN_UL(BaseAddr)                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0080)
#define SOC_CIPHER_DST2_SEG_WR_ADDR_UL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0084)
#define SOC_CIPHER_DST2_SEG_LEAVE_LEN_UL(BaseAddr)                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0088)


#define SOC_CIPHER_LLI_PARAM_ADDR_DL(BaseAddr)                     SOC_CIPHER_REG_ADDR(BaseAddr,0x0108)
#define SOC_CIPHER_GLOBAL_CFG_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x010C)
#define SOC_CIPHER_CHL_FST_ADDR_DL(BaseAddr)                       SOC_CIPHER_REG_ADDR(BaseAddr,0x0110)
#define SOC_CIPHER_CHL_LST_ADDR_DL(BaseAddr)                       SOC_CIPHER_REG_ADDR(BaseAddr,0x0114)
#define SOC_CIPHER_INT_EN_DL(BaseAddr)                             SOC_CIPHER_REG_ADDR(BaseAddr,0x0118)
#define SOC_CIPHER_INT_RAW_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x011C)
#define SOC_CIPHER_INT_CLR_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0120)
#define SOC_CIPHER_INT_MSK_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0124)
#define SOC_CIPHER_EN_DL(BaseAddr)                                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0128)
#define SOC_CIPHER_CK_ADDR_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x012C)
#define SOC_CIPHER_CK_31_0_DL(BaseAddr)                            SOC_CIPHER_REG_ADDR(BaseAddr,0x0130)
#define SOC_CIPHER_CK_63_32_DL(BaseAddr)                           SOC_CIPHER_REG_ADDR(BaseAddr,0x0134)
#define SOC_CIPHER_CK_95_64_DL(BaseAddr)                           SOC_CIPHER_REG_ADDR(BaseAddr,0x0138)
#define SOC_CIPHER_CK_127_96_DL(BaseAddr)                          SOC_CIPHER_REG_ADDR(BaseAddr,0x013c)
#define SOC_CIPHER_CC_DL(BaseAddr)                                 SOC_CIPHER_REG_ADDR(BaseAddr,0x0140)
#define SOC_CIPHER_SRC_PDU_TOTAL_LEN_DL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0144)
#define SOC_CIPHER_CUSTOM_CFG_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x0148)
#define SOC_CIPHER_SRC_PDU_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x014c)
#define SOC_CIPHER_SRC_PDU_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0150)
#define SOC_CIPHER_LLI_SRC_PDU_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x0154)
#define SOC_CIPHER_DST_TTF_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0158)
#define SOC_CIPHER_DST_TTF_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x015c)
#define SOC_CIPHER_LLI_DST_TTF_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x0160)
#define SOC_CIPHER_DST_MBX_SEG_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0164)
#define SOC_CIPHER_DST_MBX_SEG_LEN_DL(BaseAddr)                    SOC_CIPHER_REG_ADDR(BaseAddr,0x0168)
#define SOC_CIPHER_LLI_DST_MBX_SEG_ADDR_DL(BaseAddr)               SOC_CIPHER_REG_ADDR(BaseAddr,0x016C)
#define SOC_CIPHER_ERROR_ADDR_DL(BaseAddr)                         SOC_CIPHER_REG_ADDR(BaseAddr,0x0170)
#define SOC_CIPHER_SRC_RD_ADDR_DL(BaseAddr)                        SOC_CIPHER_REG_ADDR(BaseAddr,0x0174)
#define SOC_CIPHER_SRC_SEG_LEFT_LEN_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x0178)
#define SOC_CIPHER_DST1_SEG_WR_ADDR_DL(BaseAddr)                   SOC_CIPHER_REG_ADDR(BaseAddr,0x017C)
#define SOC_CIPHER_DST1_SEG_LEFT_LEN_DL(BaseAddr)                  SOC_CIPHER_REG_ADDR(BaseAddr,0x0180)



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

#endif /* end of soc_cicom_interface.h */
