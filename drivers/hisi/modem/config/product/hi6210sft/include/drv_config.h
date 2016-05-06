/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_config.h
  版 本 号   : 初稿
  作    者   : 袁旦 00145322
  生成日期   : 2013年11月19日
  最近修改   :
  功能描述   : drv_config.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年11月19日
    作    者   : 袁旦 00145322
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__


/******************************** SRAM-OFF内存区配置内存规划*********************************/
/*SRAM-OFF配置内存起始地址*/
#define CONFIG_DATA_BASE               (MEMORY_AXI_CONFIG_ADDR)

#define CONFIG_MBFULLMNTN_ADDR         (CONFIG_DATA_BASE)
#define CONFIG_MBFULLMNTN_SIZE         (0x1)

#define CONFIG_NOC_ERRLOG_ADDR         (CONFIG_MBFULLMNTN_ADDR + CONFIG_MBFULLMNTN_SIZE)
#define CONFIG_NOC_ERRLOG_SIZE         (0x1)

#define CONFIG_CCPU_GPIO_INT_GROUP     (CONFIG_NOC_ERRLOG_ADDR + CONFIG_NOC_ERRLOG_SIZE)
#define CONFIG_CCPU_GPIO_INT_SIZE      (0x1)

#define CONFIG_LOAD_DDR_ADDR          (CONFIG_CCPU_GPIO_INT_GROUP + CONFIG_CCPU_GPIO_INT_SIZE)
#define CONFIG_LOAD_DDR_SIZE         (0x1)

#define CONFIG_LOAD_PORT_ADDR          (CONFIG_LOAD_DDR_ADDR + CONFIG_LOAD_DDR_SIZE)
#define CONFIG_LOAD_PORT_SIZE         (0x1)

#define CONFIG_LOAD_PORT_IDMASK_ADDR         (CONFIG_LOAD_PORT_ADDR + CONFIG_LOAD_PORT_SIZE)
#define CONFIG_LOAD_PORT_IDMASK_SIZE         (0x4)

#define CONFIG_LOAD_DDR_SINGLE_PORT_ADDR         (CONFIG_LOAD_PORT_IDMASK_ADDR + CONFIG_LOAD_PORT_IDMASK_SIZE)
#define CONFIG_LOAD_DDR_SINGLE_PORT_SIZE         (0x1)

#define CONFIG_TELE_MNTN_ADDR         (CONFIG_LOAD_DDR_SINGLE_PORT_ADDR + CONFIG_LOAD_DDR_SINGLE_PORT_SIZE)
#define CONFIG_TELE_MNTN_SIZE         (16)
#endif

