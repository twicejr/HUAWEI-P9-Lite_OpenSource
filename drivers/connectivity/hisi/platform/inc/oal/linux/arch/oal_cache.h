

#ifndef __OAL_LINUX_CACHE_H__
#define __OAL_LINUX_CACHE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <linux/version.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    /*TBD*/
#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
#include <arch/arm/mach-sd5115h-v100f/include/mach/cache-hil2.h>
#else
//#include <arch/arm/mach-sd56xx/include/mach/cache-hil2.h>
#if((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
   ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
   ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
#include <mach/cache-hil2.h>
#else
#include <../arch/arm/mach-hsan/include/mach/hi_cache.h>
#endif
#endif

#include <asm/cacheflush.h>
#if (defined(_PRE_BOARD_SD5610) || defined(_PRE_BOARD_SD5115))
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
#include <mach/platform.h>
#else
#include <../arch/arm/mach-hsan/include/mach/hi_map.h>
#endif
#endif
#include <linux/device.h>
#include <linux/compiler.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/cache.h>

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define oal_cacheline_aligned   ____cacheline_aligned

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern void __iomem *g_l2cache_base;

/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    /*TBD*/
#else
extern struct cpu_cache_fns cpu_cache;

OAL_STATIC OAL_INLINE oal_void oal_l1cache_flush(oal_void)
{
    cpu_cache.flush_kern_all();
}


OAL_STATIC OAL_INLINE oal_void  oal_l2cache_dcache_lock(oal_bool_enum_uint8 en_flag, oal_uint32 ul_way)
{
    oal_uint32 ul_reg;

#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    ul_reg = readl(g_l2cache_base + REG_L2_DLOCKWAY);
#else
    ul_reg = readl(g_l2cache_base + HI_REG_L2_DLOCKWAY);
#endif

    ul_reg = (ul_reg & (~(1 << ul_way))) | (en_flag << ul_way);

#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    writel(ul_reg, g_l2cache_base + REG_L2_DLOCKWAY);
#else
    writel(ul_reg, g_l2cache_base + HI_REG_L2_DLOCKWAY);
#endif

    return;
}


OAL_STATIC OAL_INLINE oal_void  oal_l2cache_icache_lock(oal_bool_enum_uint8 en_flag, oal_uint32 ul_way)
{
    oal_uint32 ul_reg;
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    ul_reg = readl(g_l2cache_base + REG_L2_ILOCKWAY);
#else
    ul_reg = readl(g_l2cache_base + HI_REG_L2_ILOCKWAY);
#endif
    ul_reg = (ul_reg & (~(1 << ul_way))) | (en_flag << ul_way);

#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    writel(ul_reg, g_l2cache_base + REG_L2_ILOCKWAY);
#else
    writel(ul_reg, g_l2cache_base + HI_REG_L2_ILOCKWAY);
#endif
    return;

}


OAL_STATIC OAL_INLINE oal_void  oal_cache_flush_all(oal_void)
{
    flush_cache_all();
}


OAL_STATIC OAL_INLINE oal_void  oal_cache_rxtx_lock(oal_void)
{
#if ((_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_VSPM310DMB == _PRE_CONFIG_TARGET_PRODUCT)\
    ||(_PRE_TARGET_PRODUCT_TYPE_WS835DMB == _PRE_CONFIG_TARGET_PRODUCT))
    g_l2cache_base = (void __iomem *)ioremap(REG_BASE_L2CACHE, OAL_SIZEOF(void *));
#else
    g_l2cache_base = (void __iomem *)ioremap(HI_REG_BASE_L2CACHE, OAL_SIZEOF(void *));
#endif
}
#endif

/*****************************************************************************
  10 函数声明
*****************************************************************************/











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_cache.h */
