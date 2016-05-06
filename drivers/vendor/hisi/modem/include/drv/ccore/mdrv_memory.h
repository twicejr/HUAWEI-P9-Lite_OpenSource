
/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  mdrv_memory.h
*
*   作    者 :  yangzhi
*
*   描    述 :  本文件命名为"mdrv.h", 给出V7R1底软和协议栈之间的API接口统计
*
*   修改记录 :  2011年1月18日  v1.00  yangzhi创建
*************************************************************************/

#ifndef __MDRV_CCORE_MEMORY_H__
#define __MDRV_CCORE_MEMORY_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_memory_common.h>


typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_HUTAF,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_TDS_LH2,
    BSP_DDR_SECT_TYPE_SOCP,
    BSP_DDR_SECT_TYPE_ECS_TEE,
    BSP_DDR_SECT_TYPE_MODEM_SR_STAMP,
    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;

typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;

typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;


typedef struct tagBSP_DDR_SECT_QUERY_S
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    unsigned int                 ulSectSize;
}BSP_DDR_SECT_QUERY_S;

typedef struct tagBSP_DDR_SECT_INFO_S
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    void *                 pSectVirtAddr;
    void *                 pSectPhysAddr;
    unsigned int           ulSectSize;
}BSP_DDR_SECT_INFO_S;


typedef enum tagBSP_AXI_SECT_TYPE_E
{
    BSP_AXI_SECT_TYPE_ACORE_DEEPSLEEP = 0x0,
    BSP_AXI_SECT_TYPE_FLASH_SEM,
    BSP_AXI_SECT_TYPE_IFC,
    BSP_AXI_SECT_TYPE_ICC,
    BSP_AXI_SECT_TYPE_MEMMGR_FLAG,
    BSP_AXI_SECT_TYPE_DYNAMIC,
    BSP_AXI_SECT_TYPE_SOFT_FLAG,
    BSP_AXI_SECT_TYPE_IPF,
    BSP_AXI_SECT_TYPE_TEMPERATURE,
    BSP_AXI_SECT_TYPE_ONOFF,
    BSP_AXI_SECT_TYPE_DICC,
    BSP_AXI_SECT_TYPE_HIFI,
    BSP_AXI_SECT_TYPE_DDR_CAPACITY,
    BSP_AXI_SECT_TYPE_PTABLE,
    BSP_AXI_SECT_TYPE_RESERVE,
    BSP_AXI_SECT_TYPE_DLOAD_AUTOINSTALL,
    BSP_AXI_SECT_TYPE_DLOAD,
    BSP_AXI_SECT_TYPE_CCORE_DEEPSLEEP ,
    BSP_AXI_SECT_TYPE_TTF_BBP,
    BSP_AXI_SECT_TYPE_CPHY_SRAM,
    BSP_AXI_SECT_TYPE_BUTTOM
}BSP_AXI_SECT_TYPE_E;

/* 定义所有需要查询的MEM类型 */
typedef enum tagBSP_DDR_TYPE_E
{
    BSP_DDR_TYPE_DDR_GU = 0x0,          /*DDR:GU预留*/
    BSP_DDR_TYPE_DDR_TLPHY_IMAGE,       /*DDR:TL DSP 镜像*/
    BSP_DDR_TYPE_DDR_LPHY_SDR,          /*DDR:SDR小区搜索*/
    BSP_DDR_TYPE_DDR_TLPHY_LCS,         /*DDR:TL DSP LCS*/
    BSP_DDR_TYPE_DDR_TLPHY_BANDNV,      /*DDR:TL DSP BAND*/
    BSP_DDR_TYPE_DDR_TPHY_TABLE,        /*DDR:TL TDS TABLE*/
    BSP_DDR_TYPE_DDR_HIFI,              /*DDR:HIFI*/
    BSP_DDR_TYPE_SRAM_TLPHY,            /*SRAM:TL DSP*/
    BSP_DDR_TYPE_SHM_TEMPERATURE,       /*共享内存:温饱*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,   /*共享内存:BBE16->HIFI邮箱头*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,   /*共享内存:HIFI->BBE16邮箱头*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,  /*共享内存:BBE16->HIFI邮箱队列*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,  /*共享内存:HIFI->BBE16邮箱队列*/
    BSP_DDR_TYPE_SHM_TIMESTAMP,         /*DDR:LDSP LP*/
    BSP_DDR_TYPE_SHM_AFC_TEMPCOMP,      /*LPHY温保与频偏*/
    BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,   /*LPHY邮箱保护标志*/
    BSP_DDR_TYPE_SRAM_DSP_MNTN_INFO,    /*SRAM:DSP可维可测信息*/
    BSP_DDR_TYPE_SRAM_XMAILBOX_PROTECT_FLG,/*CPHY邮箱保护标志*/    
    BSP_DDR_TYPE_SRAM_CDSP_MNTN_INFO,    /*SRAM:CDSP可维可测信息*/
    BSP_DDR_TYPE_SRAM_TLDSP_SHARED,		/*SRAM:TL DSPmem，第一个4字节是睡眠唤醒标记*/

    BSP_DDR_TYPE_BUTTOM
}BSP_DDR_TYPE_E;


typedef struct tagBSP_AXI_SECT_INFO_S
{
    void *                      pSectVirtAddr;
    void *                      pSectPhysAddr;
    BSP_AXI_SECT_TYPE_E         enSectType;
    unsigned int                ulSectSize;
}BSP_AXI_SECT_INFO_S;

/*tlps use*/
typedef struct BSP_MEMADDR_INFO_S
{
    BSP_DDR_TYPE_E         mem_type;
    unsigned int           mem_base;
    unsigned int           mem_size;
}BSP_MEMADDR_INFO_S;

/*****************************************************************************
* 函 数 名  : mdrv_memcpy
*
* 功能描述  : 数据拷贝接口，底层基于汇编实现的最优化接口，只能用于memory到
*             memory的拷贝
* 约束条件  :
*             只能用于memory 到memory的拷贝，不能用于memory到寄存器的拷贝
*             需要4字节对齐
*             在A核 ARMv8 架构中，需要8字节对齐或者是normal memory 属性，
*             采用ioremap_wc映射的 uncachable 的内存 或者cachable的内存
*
* 输入参数  : dest :  拷贝的目的地址
*             src  :  拷贝的源地址
*             count:  拷贝数据的大小
* 输出参数  : 无
* 返 回 值  :  无
****************************************************************************/
void * mdrv_memcpy(void * dest, const void * src, unsigned long count);

/*****************************************************************************
* 函 数 名  : mdrv_cachedmem_alloc
*
* 功能描述  :为DMA设备或者驱动分配一个cache安全的内存。
*
* 输入参数  : bytes: 需要分配的字节的数量
*
* 输出参数  : 无
* 返 回 值  :  NULL :    分配内存失败
*            非NULL指针: 分配内存成功，该指针指向分配的内存块的指针
****************************************************************************/
void* mdrv_cachedmem_alloc (unsigned int  bytes);

/*****************************************************************************
* 函 数 名  : mdrv_cachedmem_free
*
* 功能描述  :释放由mdrv_cachedmem_alloc分配的内存。
*
* 输入参数  : pBuf:指向要释放的内存块的指针
*
* 输出参数  : 无
* 返 回 值  :  0: 成功
*             -1: 失败
****************************************************************************/
int mdrv_cachedmem_free(void*  pBuf);

/*****************************************************************************
* 函 数 名  : mdrv_get_fix_ddr_addr
*
* 功能描述  :DDR内存段查询接口。
*
* 输入参数  : pstSectQuery: 需要查询内存段的属性，类型
*             pstSectInfo:  查询到的内存段信息
*
* 输出参数  : 无
* 返 回 值  :  无
****************************************************************************/
int mdrv_get_fix_ddr_addr (BSP_DDR_SECT_QUERY_S *pstSectQuery, BSP_DDR_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* 函 数 名  : mdrv_get_fix_axi_addr
*
* 功能描述  :AXI内存段查询接口。
*
* 输入参数  : enSectType: 需要查询的内存段类型
*            pstSectInfo: 查询到的内存段信息
* 输出参数  : 无
* 返 回 值  :  无
****************************************************************************/
int mdrv_get_fix_axi_addr (BSP_AXI_SECT_TYPE_E enSectType,BSP_AXI_SECT_INFO_S *pstSectInfo);

/*****************************************************************************
* 函 数 名  : mdrv_smalloc
*
* 功能描述  :为分配一个内存。
*
* 输入参数  : size: 需要分配的字节的数量
*
* 输出参数  : 无
* 返 回 值  :     NULL : 分配内存失败
*            非NULL指针: 分配内存成功，该指针指向分配的内存块的指针
****************************************************************************/
void* mdrv_smalloc (unsigned int size,MEM_POOL_TYPE flags);

/*****************************************************************************
* 函 数 名  : mdrv_sfree
*
* 功能描述  :释放由mdrv_smalloc分配的内存。
*
* 输入参数  : pBuf:指向要释放的内存块的指针
*
* 输出参数  : 无
* 返 回 值  :  0: 成功
*             -1: 失败
****************************************************************************/
int mdrv_sfree(void*  pBuf);
/*****************************************************************************
 函 数 名  : mdrv_getmeminfo
 功能描述  : 获取mem地址和大小信息
 输入参数  : enDdrType: 需要查询的mem类型
 输出参数  : addr 地址
             size 大小
 返回值    ：0    查询成功
             -1   查询失败
*****************************************************************************/
int mdrv_getmeminfo(BSP_DDR_TYPE_E enDdrType, unsigned int *addr, unsigned int *size);

/*****************************************************************************
 函 数 名  : mdrv_get_freeblockmem
 功能描述  : 释放mem
 输入参数  : 
 输出参数  : 

 返回值    ：0    成功
             -1   失败
*****************************************************************************/
int mdrv_get_freeblockmem(void);

#ifdef __cplusplus
}
#endif
#endif
