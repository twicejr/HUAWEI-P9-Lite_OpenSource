/****************************************************************************
  文 件 名   : hi6xxx_mntn.h
  版 本 号   : 初稿
  作    者   : liuyi
  生成日期   : 2014年11月1日
  最近修改   :
  功能描述   : 描述可维可测模块头文件
  注意事项   ：！！！！！！！！！！！！
               该文件为BSP.h 的备份
			   修改该文件时注意同步修改
			   ！！！！！！！！！！！！
*****************************************************************************/

/*修改此文件要同时修改 BSP.h*/

/*liuyi++ temp*/
#ifndef __HI6XXX_MNTN_H__
#define __HI6XXX_MNTN_H__
/*liuyi-- temp*/
#ifdef __cplusplus
extern "C"
{
#endif

/*BSP_MODULE_E是BSP.h的一份copy，请注意同步修改 begin*/
/* 底软模块枚举定义 */
typedef enum tagBSP_MODULE_E
{
    BSP_MODU_NANDF = 0x0, /* 0x0 */
    BSP_MODU_TIMER, /* 0x1 */
    BSP_MODU_VIC,   /* 0x2 */
    BSP_MODU_UART,  /* 0x3 */
    BSP_MODU_YAFFS, /* 0x4 */
    BSP_MODU_ETH,   /* 0x5 */
    BSP_MODU_DMAC,  /* 0x6 */
    BSP_MODU_SPI,   /* 0x7 */
    BSP_MODU_GPIO,  /* 0x8 */
    BSP_MODU_WDT,   /* 0x9 */
    BSP_MODU_SCI,   /* 0xA */
    BSP_MODU_USB,   /* 0xB */
    BSP_MODU_DRX,   /* 0xC */
    BSP_MODU_SDIO,  /* 0xD */
    BSP_MODU_FTP,   /* 0xE */
    BSP_MODU_GMAC,      /* 0xF */
    BSP_MODU_SEEKER,    /* 0x10 */
    BSP_MODU_UPGRADE,   /* 0x11 */
    BSP_MODU_AXI,       /* 0x12 */
    BSP_MODU_NET,       /* 0x13 */
    BSP_MODU_USB_ACM,   /* 0x14 */
    BSP_MODU_USB_NCM,   /* 0x15 */
    BSP_MODU_AXI_MONITOR,
    BSP_MODU_IFC,
    BSP_MODU_ICC,
    BSP_MODU_IPF,
    BSP_MODU_ACC,       /* 0x1A */
    BSP_MODU_BBP,
    BSP_MODU_MEM,
    BSP_MODU_UDI,
    BSP_MODU_DLOAD,
    BSP_MODU_SOCP,
    BSP_MODU_IFCP,      /* 0x20 */
    BSP_MODU_PWRCTRL,
    BSP_MODU_SERIAL_UPGRADE,
    BSP_MODU_SYNC,
    BSP_MODU_IPC,
    BSP_MODU_MNTN,
    BSP_MODU_SSI,       /*增加SSI模块，added by z00187553*/
    BSP_MODU_HKADC,     /*增加HKADC模块，added by zkf37782   */
    BSP_MODU_PMU,       /*增加PMU模块，added by z00187553*/
    BSP_MODU_HIFI,      /*0x29*//*增加HIFI模块，added by w00193956*/
    BSP_MODU_AUDIO,
    BSP_MODU_CHGC,
    BSP_MODU_MAILBOX,
    BSP_MODU_SLAVE,
    BSP_MODU_MIPI,
    BSP_MODU_SKU,
    BSP_MODU_THERMAL,   /*温保模块*/
    BSP_MODU_MBX,
    BSP_MODU_DORESET,   /*当处理C核或者hifi单独复位出现异常时，A核主动复位， added by l00212112*/
    BSP_MODU_EDMA,      /*0x33*/
	BSP_MODU_WM8990,	/*wm8990模块*/
    BSP_MODU_LED,		/*LED模块*/
    BSP_MODU_ABB,		/*ABB模块*/
	BSP_MODU_RFILE,     /*add rfile system，add by l00201187*/
	BSP_MODU_SSDMA,     /*安全模块*/
	BSP_MODU_OSAL,
	BSP_MODU_TUNER,
	BSP_MODU_BBE,
    BSP_MODU_CIPHER,
	BSP_MODU_RST,
	BSP_MODU_EMMC,
	/*新加模块请从尾端开始，同时请勿改变上边各模块的位置*/
    BSP_MODU_ALL,       /* 代表所有的模块 */
    BSP_MODU_MAX        /* 边界值 */
} BSP_MODULE_E;

#define  BSP_MNTN_CACHE_FLUSH   0x8765abcd
/*BSP_MODULE_E是BSP.h的一份copy，请注意同步修改 end*/

#ifdef __cplusplus
}
#endif

#endif
