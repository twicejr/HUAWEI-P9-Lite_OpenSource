/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_pctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:29
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_PCTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_PCTRL_INTERFACE_H__
#define __SOC_PCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) PCTRL
 ****************************************************************************/
/* 寄存器说明：G3D光栅控制寄存器。
   位域定义UNION结构:  SOC_PCTRL_G3D_RASTER_UNION */
#define SOC_PCTRL_G3D_RASTER_ADDR(base)               ((base) + (0x000))

/* 寄存器说明：通用外设控制寄存器0。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL0_UNION */
#define SOC_PCTRL_PERI_CTRL0_ADDR(base)               ((base) + (0x004))

/* 寄存器说明：通用外设控制寄存器1。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL1_UNION */
#define SOC_PCTRL_PERI_CTRL1_ADDR(base)               ((base) + (0x008))

/* 寄存器说明：通用外设控制寄存器2。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL2_UNION */
#define SOC_PCTRL_PERI_CTRL2_ADDR(base)               ((base) + (0x00C))

/* 寄存器说明：通用外设控制寄存器3。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL3_UNION */
#define SOC_PCTRL_PERI_CTRL3_ADDR(base)               ((base) + (0x010))

/* 寄存器说明：通用外设控制寄存器4。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL4_UNION */
#define SOC_PCTRL_PERI_CTRL4_ADDR(base)               ((base) + (0x014))

/* 寄存器说明：通用外设控制寄存器12。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL12_UNION */
#define SOC_PCTRL_PERI_CTRL12_ADDR(base)              ((base) + (0x034))

/* 寄存器说明：通用外设控制寄存器13。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL13_UNION */
#define SOC_PCTRL_PERI_CTRL13_ADDR(base)              ((base) + (0x038))

/* 寄存器说明：通用外设控制寄存器14。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL14_UNION */
#define SOC_PCTRL_PERI_CTRL14_ADDR(base)              ((base) + (0x03C))

/* 寄存器说明：通用外设控制寄存器15。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL15_UNION */
#define SOC_PCTRL_PERI_CTRL15_ADDR(base)              ((base) + (0x040))

/* 寄存器说明：通用外设控制寄存器16。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL16_UNION */
#define SOC_PCTRL_PERI_CTRL16_ADDR(base)              ((base) + (0x044))

/* 寄存器说明：通用外设控制寄存器17。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL17_UNION */
#define SOC_PCTRL_PERI_CTRL17_ADDR(base)              ((base) + (0x048))

/* 寄存器说明：通用外设控制寄存器18。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL18_UNION */
#define SOC_PCTRL_PERI_CTRL18_ADDR(base)              ((base) + (0x04C))

/* 寄存器说明：通用外设控制寄存器19。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL19_UNION */
#define SOC_PCTRL_PERI_CTRL19_ADDR(base)              ((base) + (0x050))

/* 寄存器说明：通用外设控制寄存器20。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL20_UNION */
#define SOC_PCTRL_PERI_CTRL20_ADDR(base)              ((base) + (0x054))

/* 寄存器说明：通用外设控制寄存器21。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL21_UNION */
#define SOC_PCTRL_PERI_CTRL21_ADDR(base)              ((base) + (0x058))

/* 寄存器说明：通用外设控制寄存器22。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL22_UNION */
#define SOC_PCTRL_PERI_CTRL22_ADDR(base)              ((base) + (0x05C))

/* 寄存器说明：通用外设控制寄存器23。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL23_UNION */
#define SOC_PCTRL_PERI_CTRL23_ADDR(base)              ((base) + (0x060))

/* 寄存器说明：通用外设控制寄存器24。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL24_UNION */
#define SOC_PCTRL_PERI_CTRL24_ADDR(base)              ((base) + (0x064))

/* 寄存器说明：通用外设控制寄存器25。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL25_UNION */
#define SOC_PCTRL_PERI_CTRL25_ADDR(base)              ((base) + (0x068))

/* 寄存器说明：通用外设控制寄存器26。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL26_UNION */
#define SOC_PCTRL_PERI_CTRL26_ADDR(base)              ((base) + (0x06C))

/* 寄存器说明：通用外设控制寄存器27。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL27_UNION */
#define SOC_PCTRL_PERI_CTRL27_ADDR(base)              ((base) + (0x070))

/* 寄存器说明：通用外设控制寄存器28。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL28_UNION */
#define SOC_PCTRL_PERI_CTRL28_ADDR(base)              ((base) + (0x074))

/* 寄存器说明：通用外设控制寄存器29。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL29_UNION */
#define SOC_PCTRL_PERI_CTRL29_ADDR(base)              ((base) + (0x078))

/* 寄存器说明：通用外设控制寄存器30。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL30_UNION */
#define SOC_PCTRL_PERI_CTRL30_ADDR(base)              ((base) + (0x07C))

/* 寄存器说明：通用外设控制寄存器31。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL31_UNION */
#define SOC_PCTRL_PERI_CTRL31_ADDR(base)              ((base) + (0x080))

/* 寄存器说明：通用外设控制寄存器32。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL32_UNION */
#define SOC_PCTRL_PERI_CTRL32_ADDR(base)              ((base) + (0x084))

/* 寄存器说明：通用外设控制寄存器33。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL33_UNION */
#define SOC_PCTRL_PERI_CTRL33_ADDR(base)              ((base) + (0x088))

/* 寄存器说明：通用外设状态寄存器0。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT0_UNION */
#define SOC_PCTRL_PERI_STAT0_ADDR(base)               ((base) + (0x094))

/* 寄存器说明：通用外设状态寄存器1。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT1_UNION */
#define SOC_PCTRL_PERI_STAT1_ADDR(base)               ((base) + (0x098))

/* 寄存器说明：通用外设状态寄存器2。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT2_UNION */
#define SOC_PCTRL_PERI_STAT2_ADDR(base)               ((base) + (0x09C))

/* 寄存器说明：通用外设状态寄存器3。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT3_UNION */
#define SOC_PCTRL_PERI_STAT3_ADDR(base)               ((base) + (0x0A0))

/* 寄存器说明：通用外设状态寄存器4。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT4_UNION */
#define SOC_PCTRL_PERI_STAT4_ADDR(base)               ((base) + (0x0A4))

/* 寄存器说明：通用外设状态寄存器5。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT5_UNION */
#define SOC_PCTRL_PERI_STAT5_ADDR(base)               ((base) + (0x0A8))

/* 寄存器说明：通用外设状态寄存器6。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT6_UNION */
#define SOC_PCTRL_PERI_STAT6_ADDR(base)               ((base) + (0x0AC))

/* 寄存器说明：通用外设状态寄存器7。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT7_UNION */
#define SOC_PCTRL_PERI_STAT7_ADDR(base)               ((base) + (0x0B0))

/* 寄存器说明：通用外设状态寄存器8。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT8_UNION */
#define SOC_PCTRL_PERI_STAT8_ADDR(base)               ((base) + (0x0B4))

/* 寄存器说明：通用外设状态寄存器9。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT9_UNION */
#define SOC_PCTRL_PERI_STAT9_ADDR(base)               ((base) + (0x0B8))

/* 寄存器说明：通用外设状态寄存器10。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT10_UNION */
#define SOC_PCTRL_PERI_STAT10_ADDR(base)              ((base) + (0x0BC))

/* 寄存器说明：通用外设状态寄存器11。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT11_UNION */
#define SOC_PCTRL_PERI_STAT11_ADDR(base)              ((base) + (0x0C0))

/* 寄存器说明：通用外设状态寄存器12。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT12_UNION */
#define SOC_PCTRL_PERI_STAT12_ADDR(base)              ((base) + (0x0C4))

/* 寄存器说明：通用外设状态寄存器13。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT13_UNION */
#define SOC_PCTRL_PERI_STAT13_ADDR(base)              ((base) + (0x0C8))

/* 寄存器说明：通用外设状态寄存器14。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT14_UNION */
#define SOC_PCTRL_PERI_STAT14_ADDR(base)              ((base) + (0x0CC))

/* 寄存器说明：通用外设状态寄存器15。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT15_UNION */
#define SOC_PCTRL_PERI_STAT15_ADDR(base)              ((base) + (0x0D0))

/* 寄存器说明：通用外设状态寄存器16。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT16_UNION */
#define SOC_PCTRL_PERI_STAT16_ADDR(base)              ((base) + (0x0D4))

/* 寄存器说明：通用外设状态寄存器17。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT17_UNION */
#define SOC_PCTRL_PERI_STAT17_ADDR(base)              ((base) + (0x0D8))

/* 寄存器说明：通用外设状态寄存器18。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT18_UNION */
#define SOC_PCTRL_PERI_STAT18_ADDR(base)              ((base) + (0x0DC))

/* 寄存器说明：通用外设状态寄存器19。
   位域定义UNION结构:  SOC_PCTRL_PERI_STAT19_UNION */
#define SOC_PCTRL_PERI_STAT19_ADDR(base)              ((base) + (0x0E0))

/* 寄存器说明：USB2 HOST控制寄存器0。
   位域定义UNION结构:  SOC_PCTRL_USB2_HOST_CTRL0_UNION */
#define SOC_PCTRL_USB2_HOST_CTRL0_ADDR(base)          ((base) + (0x0F0))

/* 寄存器说明：USB2 HOST控制寄存器1。
   位域定义UNION结构:  SOC_PCTRL_USB2_HOST_CTRL1_UNION */
#define SOC_PCTRL_USB2_HOST_CTRL1_ADDR(base)          ((base) + (0x0F4))

/* 寄存器说明：USB2 HOST控制寄存器2。
   位域定义UNION结构:  SOC_PCTRL_USB2_HOST_CTRL2_UNION */
#define SOC_PCTRL_USB2_HOST_CTRL2_ADDR(base)          ((base) + (0x0F8))

/* 寄存器说明：通用资源锁定寄存器0。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE0_LOCK_UNION */
#define SOC_PCTRL_RESOURCE0_LOCK_ADDR(base)           ((base) + (0x400))

/* 寄存器说明：通用资源解锁寄存器0。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE0_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE0_UNLOCK_ADDR(base)         ((base) + (0x404))

/* 寄存器说明：通用资源锁状态寄存器0。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE0_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE0_LOCK_ST_ADDR(base)        ((base) + (0x408))

/* 寄存器说明：通用资源锁定寄存器1。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE1_LOCK_UNION */
#define SOC_PCTRL_RESOURCE1_LOCK_ADDR(base)           ((base) + (0x40C))

/* 寄存器说明：通用资源解锁寄存器1。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE1_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE1_UNLOCK_ADDR(base)         ((base) + (0x410))

/* 寄存器说明：通用资源锁状态寄存器1。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE1_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE1_LOCK_ST_ADDR(base)        ((base) + (0x414))

/* 寄存器说明：通用资源锁定寄存器2。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE2_LOCK_UNION */
#define SOC_PCTRL_RESOURCE2_LOCK_ADDR(base)           ((base) + (0x418))

/* 寄存器说明：通用资源解锁寄存器2。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE2_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE2_UNLOCK_ADDR(base)         ((base) + (0x41C))

/* 寄存器说明：通用资源锁状态寄存器2。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE2_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE2_LOCK_ST_ADDR(base)        ((base) + (0x420))

/* 寄存器说明：通用资源锁定寄存器3。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE3_LOCK_UNION */
#define SOC_PCTRL_RESOURCE3_LOCK_ADDR(base)           ((base) + (0x424))

/* 寄存器说明：通用资源解锁寄存器3。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE3_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE3_UNLOCK_ADDR(base)         ((base) + (0x428))

/* 寄存器说明：通用资源锁状态寄存器3。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE3_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE3_LOCK_ST_ADDR(base)        ((base) + (0x42C))

/* 寄存器说明：通用资源锁定寄存器4。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE4_LOCK_UNION */
#define SOC_PCTRL_RESOURCE4_LOCK_ADDR(base)           ((base) + (0x800))

/* 寄存器说明：通用资源解锁寄存器4。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE4_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE4_UNLOCK_ADDR(base)         ((base) + (0x804))

/* 寄存器说明：通用资源锁状态寄存器4。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE4_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE4_LOCK_ST_ADDR(base)        ((base) + (0x808))

/* 寄存器说明：通用资源锁定寄存器5。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE5_LOCK_UNION */
#define SOC_PCTRL_RESOURCE5_LOCK_ADDR(base)           ((base) + (0x80C))

/* 寄存器说明：通用资源解锁寄存器5。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE5_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE5_UNLOCK_ADDR(base)         ((base) + (0x810))

/* 寄存器说明：通用资源锁状态寄存器5。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE5_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE5_LOCK_ST_ADDR(base)        ((base) + (0x814))

/* 寄存器说明：通用资源锁定寄存器6。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE6_LOCK_UNION */
#define SOC_PCTRL_RESOURCE6_LOCK_ADDR(base)           ((base) + (0x818))

/* 寄存器说明：通用资源解锁寄存器6。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE6_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE6_UNLOCK_ADDR(base)         ((base) + (0x81C))

/* 寄存器说明：通用资源锁状态寄存器6。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE6_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE6_LOCK_ST_ADDR(base)        ((base) + (0x820))

/* 寄存器说明：通用资源锁定寄存器7。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE7_LOCK_UNION */
#define SOC_PCTRL_RESOURCE7_LOCK_ADDR(base)           ((base) + (0x824))

/* 寄存器说明：通用资源解锁寄存器7。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE7_UNLOCK_UNION */
#define SOC_PCTRL_RESOURCE7_UNLOCK_ADDR(base)         ((base) + (0x828))

/* 寄存器说明：通用资源锁状态寄存器7。
   位域定义UNION结构:  SOC_PCTRL_RESOURCE7_LOCK_ST_UNION */
#define SOC_PCTRL_RESOURCE7_LOCK_ST_ADDR(base)        ((base) + (0x82C))

/* 寄存器说明：通用外设控制寄存器5
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL5_UNION */
#define SOC_PCTRL_PERI_CTRL5_ADDR(base)               ((base) + (0xC00))

/* 寄存器说明：通用外设控制寄存器6。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL6_UNION */
#define SOC_PCTRL_PERI_CTRL6_ADDR(base)               ((base) + (0xC04))

/* 寄存器说明：通用外设控制寄存器7。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL7_UNION */
#define SOC_PCTRL_PERI_CTRL7_ADDR(base)               ((base) + (0xC08))

/* 寄存器说明：通用外设控制寄存器8。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL8_UNION */
#define SOC_PCTRL_PERI_CTRL8_ADDR(base)               ((base) + (0xC0C))

/* 寄存器说明：通用外设控制寄存器9。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL9_UNION */
#define SOC_PCTRL_PERI_CTRL9_ADDR(base)               ((base) + (0xC10))

/* 寄存器说明：通用外设控制寄存器10。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL10_UNION */
#define SOC_PCTRL_PERI_CTRL10_ADDR(base)              ((base) + (0xC14))

/* 寄存器说明：通用外设控制寄存器11。
   位域定义UNION结构:  SOC_PCTRL_PERI_CTRL11_UNION */
#define SOC_PCTRL_PERI_CTRL11_ADDR(base)              ((base) + (0xC18))





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
                     (1/1) PCTRL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_PCTRL_G3D_RASTER_UNION
 结构说明  : G3D_RASTER 寄存器结构定义。地址偏移量:0x000，初值:0x00000221，宽度:32
 寄存器说明: G3D光栅控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_div            : 10; /* bit[0-9]  : G3D光栅刷新率分频周期。
                                                              由32.768KHz时钟作分频，实际周期为配置值加1，例如，60Hz对应的配置值为0x221。
                                                              注意：有效配置范围为0x1~0x3FF，禁止配置0x0。 */
        unsigned int  portrait_landscape : 1;  /* bit[10]   : 旋转使能。
                                                              0：不使能；
                                                              1：使能。 */
        unsigned int  lcd_3d_2d          : 1;  /* bit[11]   : 3D或2D模式选择。
                                                              0：3D模式；
                                                              1：2D模式。 */
        unsigned int  g3d_raster_en      : 1;  /* bit[12]   : G3D光栅控制使能。
                                                              0：不使能；
                                                              1：使能。 */
        unsigned int  lcd_3d_sw_inv      : 4;  /* bit[13-16]: G3D光栅输出取反使能。比特0~3分别对应输出信号0~3。
                                                              0：不使能；
                                                              1：使能。 */
        unsigned int  reserved           : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_PCTRL_G3D_RASTER_UNION;
#endif
#define SOC_PCTRL_G3D_RASTER_g3d_div_START             (0)
#define SOC_PCTRL_G3D_RASTER_g3d_div_END               (9)
#define SOC_PCTRL_G3D_RASTER_portrait_landscape_START  (10)
#define SOC_PCTRL_G3D_RASTER_portrait_landscape_END    (10)
#define SOC_PCTRL_G3D_RASTER_lcd_3d_2d_START           (11)
#define SOC_PCTRL_G3D_RASTER_lcd_3d_2d_END             (11)
#define SOC_PCTRL_G3D_RASTER_g3d_raster_en_START       (12)
#define SOC_PCTRL_G3D_RASTER_g3d_raster_en_END         (12)
#define SOC_PCTRL_G3D_RASTER_lcd_3d_sw_inv_START       (13)
#define SOC_PCTRL_G3D_RASTER_lcd_3d_sw_inv_END         (16)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL0_UNION
 结构说明  : PERI_CTRL0 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_1wire_e     : 1;  /* bit[0]    : bit[0]：uart5 1wire_en；
                                                          0:one wire disable 1:one wire enable
                                                          注意：只有在对应的mask位同时写1时，写操作才有效。 */
        unsigned int  peri_ctrl0_cmd : 15; /* bit[1-15] : bit[15:1]：reserved
                                                          注意：只有在对应的mask位同时写1时，写操作才有效。 */
        unsigned int  peri_ctrl0_msk : 16; /* bit[16-31]: 通用外设控制mask掩码。
                                                          与bit[15:0]命令位一一对应。
                                                          0：屏蔽命令位，命令位写操作无效；
                                                          1：使能命令位，命令位写操作有效。 */
    } reg;
} SOC_PCTRL_PERI_CTRL0_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL0_sc_1wire_e_START      (0)
#define SOC_PCTRL_PERI_CTRL0_sc_1wire_e_END        (0)
#define SOC_PCTRL_PERI_CTRL0_peri_ctrl0_cmd_START  (1)
#define SOC_PCTRL_PERI_CTRL0_peri_ctrl0_cmd_END    (15)
#define SOC_PCTRL_PERI_CTRL0_peri_ctrl0_msk_START  (16)
#define SOC_PCTRL_PERI_CTRL0_peri_ctrl0_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL1_UNION
 结构说明  : PERI_CTRL1 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  test_point_sel : 7;  /* bit[0-6]  : bit[6:0] :test_point_sel 管脚测试相关，具体含义参考测试管脚配置相关描述。 */
        unsigned int  peri_ctrl0_cmd : 9;  /* bit[7-15] : 保留。 */
        unsigned int  peri_ctrl1_msk : 16; /* bit[16-31]: 通用外设控制mask掩码。
                                                          与bit[15:0]命令位一一对应。
                                                          0：屏蔽命令位，命令位写操作无效；
                                                          1：使能命令位，命令位写操作有效。 */
    } reg;
} SOC_PCTRL_PERI_CTRL1_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL1_test_point_sel_START  (0)
#define SOC_PCTRL_PERI_CTRL1_test_point_sel_END    (6)
#define SOC_PCTRL_PERI_CTRL1_peri_ctrl0_cmd_START  (7)
#define SOC_PCTRL_PERI_CTRL1_peri_ctrl0_cmd_END    (15)
#define SOC_PCTRL_PERI_CTRL1_peri_ctrl1_msk_START  (16)
#define SOC_PCTRL_PERI_CTRL1_peri_ctrl1_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL2_UNION
 结构说明  : PERI_CTRL2 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_ctrl2_cmd : 16; /* bit[0-15] : 保留。 */
        unsigned int  peri_ctrl2_msk : 16; /* bit[16-31]: 通用外设控制mask掩码。
                                                          与bit[15:0]命令位一一对应。
                                                          0：屏蔽命令位，命令位写操作无效；
                                                          1：使能命令位，命令位写操作有效。 */
    } reg;
} SOC_PCTRL_PERI_CTRL2_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL2_peri_ctrl2_cmd_START  (0)
#define SOC_PCTRL_PERI_CTRL2_peri_ctrl2_cmd_END    (15)
#define SOC_PCTRL_PERI_CTRL2_peri_ctrl2_msk_START  (16)
#define SOC_PCTRL_PERI_CTRL2_peri_ctrl2_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL3_UNION
 结构说明  : PERI_CTRL3 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 6;  /* bit[0-5]  : 保留。 */
        unsigned int  venc_force_clk_enable : 1;  /* bit[6]    : bit[6]:venc_force_clk_enable
                                                                 0:disable 1:enable。 */
        unsigned int  vdec_force_clk_enable : 1;  /* bit[7]    : bit[7]:vdec_force_clk_enable
                                                                 0:disable 1:enable。 */
        unsigned int  reserved_1            : 8;  /* bit[8-15] : 保留。 */
        unsigned int  peri_ctrl3_msk        : 16; /* bit[16-31]: 通用外设控制mask掩码。
                                                                 与bit[15:0]命令位一一对应。
                                                                 0：屏蔽命令位，命令位写操作无效；
                                                                 1：使能命令位，命令位写操作有效。 */
    } reg;
} SOC_PCTRL_PERI_CTRL3_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL3_venc_force_clk_enable_START  (6)
#define SOC_PCTRL_PERI_CTRL3_venc_force_clk_enable_END    (6)
#define SOC_PCTRL_PERI_CTRL3_vdec_force_clk_enable_START  (7)
#define SOC_PCTRL_PERI_CTRL3_vdec_force_clk_enable_END    (7)
#define SOC_PCTRL_PERI_CTRL3_peri_ctrl3_msk_START         (16)
#define SOC_PCTRL_PERI_CTRL3_peri_ctrl3_msk_END           (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL4_UNION
 结构说明  : PERI_CTRL4 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_pctrl_qos : 32; /* bit[0-31]: sc_pctrl_qos。 */
    } reg;
} SOC_PCTRL_PERI_CTRL4_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL4_sc_pctrl_qos_START  (0)
#define SOC_PCTRL_PERI_CTRL4_sc_pctrl_qos_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL12_UNION
 结构说明  : PERI_CTRL12 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cssys_araddr_cohe    : 1;  /* bit[0]    : cssys_araddr_cohe 暂未使用。 */
        unsigned int  cssys_awaddr_cohe    : 1;  /* bit[1]    : cssys_awaddr_cohe 暂未使用。 */
        unsigned int  noc_emmc1_haddr_cohe : 1;  /* bit[2]    : noc_emmc1_haddr_cohe 暂未使用。 */
        unsigned int  noc_sd3_haddr_cohe   : 1;  /* bit[3]    : noc_sd3_haddr_cohe 暂未使用。 */
        unsigned int  noc_sdio0_haddr_cohe : 1;  /* bit[4]    : noc_sdio0_haddr_cohe 暂未使用。 */
        unsigned int  iomcu_haddr_cohe     : 1;  /* bit[5]    : iomcu_haddr_cohe 暂未使用。 */
        unsigned int  secp_araddr_cohe     : 1;  /* bit[6]    : secp_araddr_cohe 暂未使用。 */
        unsigned int  secp_awaddr_cohe     : 1;  /* bit[7]    : secp_awaddr_cohe 暂未使用。 */
        unsigned int  secs_araddr_cohe     : 1;  /* bit[8]    : secs_araddr_cohe 暂未使用。 */
        unsigned int  secs_awaddr_cohe     : 1;  /* bit[9]    : secs_awaddr_cohe 暂未使用。 */
        unsigned int  usb3otg_araddr_cohe  : 1;  /* bit[10]   : usb3otg_araddr_cohe 暂未使用。 */
        unsigned int  usb3otg_awaddr_cohe  : 1;  /* bit[11]   : usb3otg_awaddr_cohe 暂未使用。 */
        unsigned int  socp_araddr_cohe     : 1;  /* bit[12]   : socp_araddr_cohe 暂未使用。 */
        unsigned int  socp_awaddr_cohe     : 1;  /* bit[13]   : socp_awaddr_cohe 暂未使用。 */
        unsigned int  emmc0_araddr_cohe    : 1;  /* bit[14]   : emmc0_araddr_cohe 暂未使用。 */
        unsigned int  emmc0_awaddr_cohe    : 1;  /* bit[15]   : emmc0_awaddr_cohe 暂未使用。 */
        unsigned int  noc_sdio1_haddr_cohe : 1;  /* bit[16]   : noc_sdio1_haddr_cohe 暂未使用。 */
        unsigned int  reserved             : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL12_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL12_cssys_araddr_cohe_START     (0)
#define SOC_PCTRL_PERI_CTRL12_cssys_araddr_cohe_END       (0)
#define SOC_PCTRL_PERI_CTRL12_cssys_awaddr_cohe_START     (1)
#define SOC_PCTRL_PERI_CTRL12_cssys_awaddr_cohe_END       (1)
#define SOC_PCTRL_PERI_CTRL12_noc_emmc1_haddr_cohe_START  (2)
#define SOC_PCTRL_PERI_CTRL12_noc_emmc1_haddr_cohe_END    (2)
#define SOC_PCTRL_PERI_CTRL12_noc_sd3_haddr_cohe_START    (3)
#define SOC_PCTRL_PERI_CTRL12_noc_sd3_haddr_cohe_END      (3)
#define SOC_PCTRL_PERI_CTRL12_noc_sdio0_haddr_cohe_START  (4)
#define SOC_PCTRL_PERI_CTRL12_noc_sdio0_haddr_cohe_END    (4)
#define SOC_PCTRL_PERI_CTRL12_iomcu_haddr_cohe_START      (5)
#define SOC_PCTRL_PERI_CTRL12_iomcu_haddr_cohe_END        (5)
#define SOC_PCTRL_PERI_CTRL12_secp_araddr_cohe_START      (6)
#define SOC_PCTRL_PERI_CTRL12_secp_araddr_cohe_END        (6)
#define SOC_PCTRL_PERI_CTRL12_secp_awaddr_cohe_START      (7)
#define SOC_PCTRL_PERI_CTRL12_secp_awaddr_cohe_END        (7)
#define SOC_PCTRL_PERI_CTRL12_secs_araddr_cohe_START      (8)
#define SOC_PCTRL_PERI_CTRL12_secs_araddr_cohe_END        (8)
#define SOC_PCTRL_PERI_CTRL12_secs_awaddr_cohe_START      (9)
#define SOC_PCTRL_PERI_CTRL12_secs_awaddr_cohe_END        (9)
#define SOC_PCTRL_PERI_CTRL12_usb3otg_araddr_cohe_START   (10)
#define SOC_PCTRL_PERI_CTRL12_usb3otg_araddr_cohe_END     (10)
#define SOC_PCTRL_PERI_CTRL12_usb3otg_awaddr_cohe_START   (11)
#define SOC_PCTRL_PERI_CTRL12_usb3otg_awaddr_cohe_END     (11)
#define SOC_PCTRL_PERI_CTRL12_socp_araddr_cohe_START      (12)
#define SOC_PCTRL_PERI_CTRL12_socp_araddr_cohe_END        (12)
#define SOC_PCTRL_PERI_CTRL12_socp_awaddr_cohe_START      (13)
#define SOC_PCTRL_PERI_CTRL12_socp_awaddr_cohe_END        (13)
#define SOC_PCTRL_PERI_CTRL12_emmc0_araddr_cohe_START     (14)
#define SOC_PCTRL_PERI_CTRL12_emmc0_araddr_cohe_END       (14)
#define SOC_PCTRL_PERI_CTRL12_emmc0_awaddr_cohe_START     (15)
#define SOC_PCTRL_PERI_CTRL12_emmc0_awaddr_cohe_END       (15)
#define SOC_PCTRL_PERI_CTRL12_noc_sdio1_haddr_cohe_START  (16)
#define SOC_PCTRL_PERI_CTRL12_noc_sdio1_haddr_cohe_END    (16)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL13_UNION
 结构说明  : PERI_CTRL13 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_pctrl_cohe0 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL13_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL13_sc_pctrl_cohe0_START  (0)
#define SOC_PCTRL_PERI_CTRL13_sc_pctrl_cohe0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL14_UNION
 结构说明  : PERI_CTRL14 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_pctrl_cohe1 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL14_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL14_sc_pctrl_cohe1_START  (0)
#define SOC_PCTRL_PERI_CTRL14_sc_pctrl_cohe1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL15_UNION
 结构说明  : PERI_CTRL15 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器15。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_pctrl_cohe2 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL15_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL15_sc_pctrl_cohe2_START  (0)
#define SOC_PCTRL_PERI_CTRL15_sc_pctrl_cohe2_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL16_UNION
 结构说明  : PERI_CTRL16 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器16。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL16_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL17_UNION
 结构说明  : PERI_CTRL17 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器17。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL17_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL18_UNION
 结构说明  : PERI_CTRL18 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器18。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL18_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL19_UNION
 结构说明  : PERI_CTRL19 寄存器结构定义。地址偏移量:0x050，初值:0x7F009211，宽度:32
 寄存器说明: 通用外设控制寄存器19。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_barrierdisable                : 1;  /* bit[0]    : bit[0]:g3d barrierdisable default:0X1
                                                                             not used。 */
        unsigned int  g3d_slp_ext0                      : 1;  /* bit[1]    : bit[1]:g3d_slp_ext0 default:0X0
                                                                             not used。 */
        unsigned int  g3d_slp_ext1                      : 1;  /* bit[2]    : bit[2]:g3d_slp_ext1 default:0X0
                                                                             not used。 */
        unsigned int  g3d_sd_ext                        : 1;  /* bit[3]    : bit[3]:g3d_sd_ext default:0X0
                                                                             not used。 */
        unsigned int  g3d_pw_sel                        : 1;  /* bit[4]    : bit[4]:g3d_pw_sel default:0X1
                                                                             0：硬件自动控制g3d memory lowpower
                                                                             1：软件配置PERI_CTRL26寄存器控制g3d memory lowpower。 */
        unsigned int  g3d_slp_sel                       : 1;  /* bit[5]    : bit[5]:g3d_slp_sel default:0X0
                                                                             0：硬件自动控制g3d memory lowpower
                                                                             1：软件配置PERI_CTRL26寄存器控制g3d memory lowpower。 */
        unsigned int  reserved_0                        : 3;  /* bit[6-8]  : 保留。 */
        unsigned int  gpu_striping_granule              : 3;  /* bit[9-11] : bit[11:9]:gpu_striping_granule default:0X1
                                                                             gpu_1to2_axi总线的交织粒度
                                                                             000：128B；001：256B；010：512B；
                                                                             011：1KB；100：2KB；101：4KB；others：reserved。 */
        unsigned int  mediabus_interleave_stripe_select : 3;  /* bit[12-14]: bit[14:12]:mediabus_interleave_stripe_select default:0X1
                                                                             000：128B；001：256B；010：512B；
                                                                             011：1KB；100：2KB；101：4KB；others：reserved。 */
        unsigned int  vivobus_interleave_stripe_select  : 3;  /* bit[15-17]: bit[17:15]:vivobus_interleave_stripe_select default:0X1
                                                                             000：128B；001：256B；010：512B；
                                                                             011：1KB；100：2KB；101：4KB；others：reserved。 */
        unsigned int  reserved_1                        : 1;  /* bit[18]   : 保留。 */
        unsigned int  isp_csi_sel                       : 1;  /* bit[19]   : bit[19]:isp_csi_sel default:0X0
                                                                             not used。 */
        unsigned int  isp_fsin0_oen                     : 1;  /* bit[20]   : bit[20]:isp_fsin0_oen default:0X0
                                                                             not used。 */
        unsigned int  isp_fsin1_oen                     : 1;  /* bit[21]   : bit[21]:isp_fsin1_oen default:0X0
                                                                             not used。 */
        unsigned int  p_csi_dphy_sel                    : 1;  /* bit[22]   : bit[22]:p_csi_dphy_sel default:0X0
                                                                             not used。 */
        unsigned int  s_csi_dphy_sel                    : 1;  /* bit[23]   : bit[23]:s_csi_dphy_sel default:0X0
                                                                             not used。 */
        unsigned int  isp_p_csi_clk_gate                : 1;  /* bit[24]   : bit[24]:isp_p_csi_clk_gate default:0X1
                                                                             not used。 */
        unsigned int  isp_s_csi_clk_gate                : 1;  /* bit[25]   : bit[25]:isp_s_csi_clk_gate default:0X1
                                                                             not used。 */
        unsigned int  isp_dw_axi_s1_cg_en               : 1;  /* bit[26]   : bit[26]:isp_dw_axi_s1_cg_en default:0X1
                                                                             not used。 */
        unsigned int  isp_dw_axi_cg_en                  : 1;  /* bit[27]   : bit[27]:isp_dw_axi_cg_en default:0X1
                                                                             not used。 */
        unsigned int  dphy1_clk_gate                    : 1;  /* bit[28]   : bit[28]:dphy1_clk_gate default:0X1
                                                                             not used。 */
        unsigned int  dphy2_clk_gate                    : 1;  /* bit[29]   : bit[29]:dphy2_clk_gate default:0X1
                                                                             not used。 */
        unsigned int  dphy3_clk_gate                    : 1;  /* bit[30]   : bit[30]:dphy3_clk_gate default:0X1
                                                                             not used。 */
        unsigned int  reserved_2                        : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL19_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL19_g3d_barrierdisable_START                 (0)
#define SOC_PCTRL_PERI_CTRL19_g3d_barrierdisable_END                   (0)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_ext0_START                       (1)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_ext0_END                         (1)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_ext1_START                       (2)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_ext1_END                         (2)
#define SOC_PCTRL_PERI_CTRL19_g3d_sd_ext_START                         (3)
#define SOC_PCTRL_PERI_CTRL19_g3d_sd_ext_END                           (3)
#define SOC_PCTRL_PERI_CTRL19_g3d_pw_sel_START                         (4)
#define SOC_PCTRL_PERI_CTRL19_g3d_pw_sel_END                           (4)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_sel_START                        (5)
#define SOC_PCTRL_PERI_CTRL19_g3d_slp_sel_END                          (5)
#define SOC_PCTRL_PERI_CTRL19_gpu_striping_granule_START               (9)
#define SOC_PCTRL_PERI_CTRL19_gpu_striping_granule_END                 (11)
#define SOC_PCTRL_PERI_CTRL19_mediabus_interleave_stripe_select_START  (12)
#define SOC_PCTRL_PERI_CTRL19_mediabus_interleave_stripe_select_END    (14)
#define SOC_PCTRL_PERI_CTRL19_vivobus_interleave_stripe_select_START   (15)
#define SOC_PCTRL_PERI_CTRL19_vivobus_interleave_stripe_select_END     (17)
#define SOC_PCTRL_PERI_CTRL19_isp_csi_sel_START                        (19)
#define SOC_PCTRL_PERI_CTRL19_isp_csi_sel_END                          (19)
#define SOC_PCTRL_PERI_CTRL19_isp_fsin0_oen_START                      (20)
#define SOC_PCTRL_PERI_CTRL19_isp_fsin0_oen_END                        (20)
#define SOC_PCTRL_PERI_CTRL19_isp_fsin1_oen_START                      (21)
#define SOC_PCTRL_PERI_CTRL19_isp_fsin1_oen_END                        (21)
#define SOC_PCTRL_PERI_CTRL19_p_csi_dphy_sel_START                     (22)
#define SOC_PCTRL_PERI_CTRL19_p_csi_dphy_sel_END                       (22)
#define SOC_PCTRL_PERI_CTRL19_s_csi_dphy_sel_START                     (23)
#define SOC_PCTRL_PERI_CTRL19_s_csi_dphy_sel_END                       (23)
#define SOC_PCTRL_PERI_CTRL19_isp_p_csi_clk_gate_START                 (24)
#define SOC_PCTRL_PERI_CTRL19_isp_p_csi_clk_gate_END                   (24)
#define SOC_PCTRL_PERI_CTRL19_isp_s_csi_clk_gate_START                 (25)
#define SOC_PCTRL_PERI_CTRL19_isp_s_csi_clk_gate_END                   (25)
#define SOC_PCTRL_PERI_CTRL19_isp_dw_axi_s1_cg_en_START                (26)
#define SOC_PCTRL_PERI_CTRL19_isp_dw_axi_s1_cg_en_END                  (26)
#define SOC_PCTRL_PERI_CTRL19_isp_dw_axi_cg_en_START                   (27)
#define SOC_PCTRL_PERI_CTRL19_isp_dw_axi_cg_en_END                     (27)
#define SOC_PCTRL_PERI_CTRL19_dphy1_clk_gate_START                     (28)
#define SOC_PCTRL_PERI_CTRL19_dphy1_clk_gate_END                       (28)
#define SOC_PCTRL_PERI_CTRL19_dphy2_clk_gate_START                     (29)
#define SOC_PCTRL_PERI_CTRL19_dphy2_clk_gate_END                       (29)
#define SOC_PCTRL_PERI_CTRL19_dphy3_clk_gate_START                     (30)
#define SOC_PCTRL_PERI_CTRL19_dphy3_clk_gate_END                       (30)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL20_UNION
 结构说明  : PERI_CTRL20 寄存器结构定义。地址偏移量:0x054，初值:0x10200350，宽度:32
 寄存器说明: 通用外设控制寄存器20。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_ctrl20_cmd  : 16; /* bit[0-15] : socp atpram mem ctrl 具体参考memory控制说明。 */
        unsigned int  socpsprammemctrl : 16; /* bit[16-31]: socp spram mem ctrl 具体参考memory控制说明。 */
    } reg;
} SOC_PCTRL_PERI_CTRL20_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL20_peri_ctrl20_cmd_START   (0)
#define SOC_PCTRL_PERI_CTRL20_peri_ctrl20_cmd_END     (15)
#define SOC_PCTRL_PERI_CTRL20_socpsprammemctrl_START  (16)
#define SOC_PCTRL_PERI_CTRL20_socpsprammemctrl_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL21_UNION
 结构说明  : PERI_CTRL21 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器21。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL21_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL22_UNION
 结构说明  : PERI_CTRL22 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器22。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  venc_designer_field2 : 16; /* bit[0-15] : venc designer field，具体含义参考venc说明文档。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL22_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL22_venc_designer_field2_START  (0)
#define SOC_PCTRL_PERI_CTRL22_venc_designer_field2_END    (15)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL23_UNION
 结构说明  : PERI_CTRL23 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器23。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  venc_mem_limited_throughput : 1;  /* bit[0]   : venc_mem_limited_throughput，含义如下：
                                                                      0：正常；
                                                                      1：会降低它发数据的速率，只发一些必要的操作，阻塞VENC的低优先级操作发出来。 */
        unsigned int  vdec_mem_limited_throughput : 1;  /* bit[1]   : vdec_mem_limited_throughput，含义如下：
                                                                      0：正常；
                                                                      1：会降低它发数据的速率，只发一些必要的操作，阻塞VDEC的低优先级操作发出来。 */
        unsigned int  dmac_ckgt_dis               : 1;  /* bit[2]   : dmac_ckgt_dis
                                                                      0：clk sc vote disable 1：clk sc vote enable。 */
        unsigned int  pctrl_dphytx_ulpsexit0      : 1;  /* bit[3]   : pctrl_dphytx_ulpsexit0，控制dphy的clock lane ulps exit信号，高有效。 */
        unsigned int  pctrl_dphytx_ulpsexit1      : 1;  /* bit[4]   : pctrl_dphytx_ulpsexit1，控制dphy的clock lane ulps exit信号，高有效。 */
        unsigned int  reserved                    : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL23_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL23_venc_mem_limited_throughput_START  (0)
#define SOC_PCTRL_PERI_CTRL23_venc_mem_limited_throughput_END    (0)
#define SOC_PCTRL_PERI_CTRL23_vdec_mem_limited_throughput_START  (1)
#define SOC_PCTRL_PERI_CTRL23_vdec_mem_limited_throughput_END    (1)
#define SOC_PCTRL_PERI_CTRL23_dmac_ckgt_dis_START                (2)
#define SOC_PCTRL_PERI_CTRL23_dmac_ckgt_dis_END                  (2)
#define SOC_PCTRL_PERI_CTRL23_pctrl_dphytx_ulpsexit0_START       (3)
#define SOC_PCTRL_PERI_CTRL23_pctrl_dphytx_ulpsexit0_END         (3)
#define SOC_PCTRL_PERI_CTRL23_pctrl_dphytx_ulpsexit1_START       (4)
#define SOC_PCTRL_PERI_CTRL23_pctrl_dphytx_ulpsexit1_END         (4)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL24_UNION
 结构说明  : PERI_CTRL24 寄存器结构定义。地址偏移量:0x064，初值:0x10118079，宽度:32
 寄存器说明: 通用外设控制寄存器24。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmussi_mst_cnt           : 3;  /* bit[0-2]  : bit[2:0]:pmussi mst cnt default:0X1
                                                                    000：1.5 clk； 
                                                                    001：2.0 clk；
                                                                    010：2.5 clk；
                                                                    011：3.0 clk；
                                                                    100：3.5 clk；
                                                                    101：4.0 clk；
                                                                    110：4.5 clk；
                                                                    111：5.0 clk。 */
        unsigned int  djtag_mst_pstrb          : 4;  /* bit[3-6]  : bit[6:3]:djtag mst pstrb default:0XF 具体参考djtag调试相关说明。 */
        unsigned int  i2c_freq_sel             : 1;  /* bit[7]    : bit[7]: i2c freq sel default:0X0
                                                                    0：clk_sys_ini；1：occ_leak_clk。 */
        unsigned int  reserved_0               : 1;  /* bit[8]    : 保留。 */
        unsigned int  sdio0_resp_ctrl          : 1;  /* bit[9]    : bit[9]:sdio0 resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  sd3_resp_ctrl            : 1;  /* bit[10]   : bit[10]:sd3 resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  sdio1_resp_ctrl          : 1;  /* bit[11]   : bit[11]:sdio1 resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  lpmcu_resp_ctrl          : 1;  /* bit[12]   : bit[12]:lpmcu resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  iomcu_cfgbus_resp_ctrl   : 1;  /* bit[13]   : bit[13]:iomcu cfgbus resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  iomcu_sysbus_resp_ctrl   : 1;  /* bit[14]   : bit[14]:iomcu sysbus resp ctrl default:0X0
                                                                    0：no response； 1：response valid。 */
        unsigned int  isp_axi_xdcdr_sel        : 1;  /* bit[15]   : bit[15]:isp_axi_xdcdr_sel default:0x1
                                                                    0：sys_slv 1：sys_slave_all masked。 */
        unsigned int  pmussi1_mst_cnt          : 3;  /* bit[16-18]: bit[18:16]:pmussi1_mst_cnt default:0X1
                                                                    000：1.5 clk； 
                                                                    001：2.0 clk；
                                                                    010：2.5 clk；
                                                                    011：3.0 clk；
                                                                    100：3.5 clk；
                                                                    101：4.0 clk；
                                                                    110：4.5 clk；
                                                                    111：5.0 clk。 */
        unsigned int  reserved_1               : 1;  /* bit[19]   : 保留。 */
        unsigned int  codecssi_mst_cnt         : 3;  /* bit[20-22]: bit[22:20]:codecssi_mst_cnt default:0X1
                                                                    000：1.5 clk； 
                                                                    001：2.0 clk；
                                                                    010：2.5 clk；
                                                                    011：3.0 clk；
                                                                    100：3.5 clk；
                                                                    101：4.0 clk；
                                                                    110：4.5 clk；
                                                                    111：5.0 clk。 */
        unsigned int  reserved_2               : 1;  /* bit[23]   : 保留。 */
        unsigned int  sc_usb3phy_abb_gt_en     : 1;  /* bit[24]   : bit[24]: sc_usb3phy_abb_gt_en default:0X0
                                                                    0：clk disable； 1：clk enable。 */
        unsigned int  sc_clk_usb3phy_3mux1_sel : 2;  /* bit[25-26]: bit[26:25]: sc_clk_usb3phy_3mux1_sel default:0X0
                                                                    00:19.2MHz from IO；
                                                                    01：19.2MHz from PPLL0；
                                                                    10：19.2MHz from ABB buffer；
                                                                    11：19.2MHz from IO。 */
        unsigned int  reserved_3               : 1;  /* bit[27]   : 保留。 */
        unsigned int  sc_usb3phy_ioclk_gt_en   : 1;  /* bit[28]   : bit[28]: sc_usb3phy_ioclk_gt_en default:0X1
                                                                    0：clk disable； 1：clk enable。 */
        unsigned int  reserved_4               : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL24_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL24_pmussi_mst_cnt_START            (0)
#define SOC_PCTRL_PERI_CTRL24_pmussi_mst_cnt_END              (2)
#define SOC_PCTRL_PERI_CTRL24_djtag_mst_pstrb_START           (3)
#define SOC_PCTRL_PERI_CTRL24_djtag_mst_pstrb_END             (6)
#define SOC_PCTRL_PERI_CTRL24_i2c_freq_sel_START              (7)
#define SOC_PCTRL_PERI_CTRL24_i2c_freq_sel_END                (7)
#define SOC_PCTRL_PERI_CTRL24_sdio0_resp_ctrl_START           (9)
#define SOC_PCTRL_PERI_CTRL24_sdio0_resp_ctrl_END             (9)
#define SOC_PCTRL_PERI_CTRL24_sd3_resp_ctrl_START             (10)
#define SOC_PCTRL_PERI_CTRL24_sd3_resp_ctrl_END               (10)
#define SOC_PCTRL_PERI_CTRL24_sdio1_resp_ctrl_START           (11)
#define SOC_PCTRL_PERI_CTRL24_sdio1_resp_ctrl_END             (11)
#define SOC_PCTRL_PERI_CTRL24_lpmcu_resp_ctrl_START           (12)
#define SOC_PCTRL_PERI_CTRL24_lpmcu_resp_ctrl_END             (12)
#define SOC_PCTRL_PERI_CTRL24_iomcu_cfgbus_resp_ctrl_START    (13)
#define SOC_PCTRL_PERI_CTRL24_iomcu_cfgbus_resp_ctrl_END      (13)
#define SOC_PCTRL_PERI_CTRL24_iomcu_sysbus_resp_ctrl_START    (14)
#define SOC_PCTRL_PERI_CTRL24_iomcu_sysbus_resp_ctrl_END      (14)
#define SOC_PCTRL_PERI_CTRL24_isp_axi_xdcdr_sel_START         (15)
#define SOC_PCTRL_PERI_CTRL24_isp_axi_xdcdr_sel_END           (15)
#define SOC_PCTRL_PERI_CTRL24_pmussi1_mst_cnt_START           (16)
#define SOC_PCTRL_PERI_CTRL24_pmussi1_mst_cnt_END             (18)
#define SOC_PCTRL_PERI_CTRL24_codecssi_mst_cnt_START          (20)
#define SOC_PCTRL_PERI_CTRL24_codecssi_mst_cnt_END            (22)
#define SOC_PCTRL_PERI_CTRL24_sc_usb3phy_abb_gt_en_START      (24)
#define SOC_PCTRL_PERI_CTRL24_sc_usb3phy_abb_gt_en_END        (24)
#define SOC_PCTRL_PERI_CTRL24_sc_clk_usb3phy_3mux1_sel_START  (25)
#define SOC_PCTRL_PERI_CTRL24_sc_clk_usb3phy_3mux1_sel_END    (26)
#define SOC_PCTRL_PERI_CTRL24_sc_usb3phy_ioclk_gt_en_START    (28)
#define SOC_PCTRL_PERI_CTRL24_sc_usb3phy_ioclk_gt_en_END      (28)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL25_UNION
 结构说明  : PERI_CTRL25 寄存器结构定义。地址偏移量:0x068，初值:0x0760E800，宽度:32
 寄存器说明: 通用外设控制寄存器25。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_qos_0                    : 2;  /* bit[0-1]  : bit[1:0]:vdec_qos_0 default:0X0 具体配置参考总线相关说明。 */
        unsigned int  vdec_qos_1                    : 2;  /* bit[2-3]  : bit[3:2]:vdec_qos_1 default:0X0 具体配置参考总线相关说明。 */
        unsigned int  venc_qos_0                    : 2;  /* bit[4-5]  : bit[5:4]:venc_qos_0 default:0X0 具体配置参考总线相关说明。 */
        unsigned int  venc_qos_1                    : 2;  /* bit[6-7]  : bit[7:6]:venc_qos_1 default:0X0 具体配置参考总线相关说明。 */
        unsigned int  secp_mem_ctrl_sd              : 1;  /* bit[8]    : bit[8]: secp_mem_ctrl_sd default:0X0
                                                                         暂未使用。 */
        unsigned int  secs_mem_ctrl_sd              : 1;  /* bit[9]    : bit[9]: secs_mem_ctrl_sd default:0X0
                                                                         暂未使用。 */
        unsigned int  mmbuf_sram_sd                 : 1;  /* bit[10]   : bit[10]: mmbuf_sram_sd default:0X0
                                                                         暂未使用。 */
        unsigned int  smmu_integ_sec_override       : 1;  /* bit[11]   : bit[11]: smmu_integ_sec_override default:0x1
                                                                         暂未使用。 */
        unsigned int  reserved_0                    : 1;  /* bit[12]   : 保留。 */
        unsigned int  dphy2l_rx_enableclk           : 1;  /* bit[13]   : bit[13]: dphy2l_rx_enableclk default:0x1
                                                                         暂未使用。 */
        unsigned int  dphy4l_rx_enableclk0          : 1;  /* bit[14]   : bit[14]: dphy4l_rx_enableclk0 default:0x1
                                                                         暂未使用。 */
        unsigned int  dphy4l_rx_enableclk1          : 1;  /* bit[15]   : bit[15]: dphy4l_rx_enableclk1 default:0x1
                                                                         暂未使用。 */
        unsigned int  reserved_1                    : 1;  /* bit[16]   : 保留。 */
        unsigned int  sc_g3d_dw_axi_m1_cg_en        : 1;  /* bit[17]   : bit[17]: sc_g3d_dw_axi_m1_cg_en default:0x0
                                                                         0：clk enable 1：clk disable。 */
        unsigned int  sc_g3d_dw_axi_s0_cg_en        : 1;  /* bit[18]   : bit[18]: sc_g3d_dw_axi_s0_cg_en default:0x0
                                                                         0：clk enable 1：clk disable。 */
        unsigned int  sc_g3d_dw_axi_s1_cg_en        : 1;  /* bit[19]   : bit[19]: sc_g3d_dw_axi_s1_cg_en default:0x0
                                                                         0：clk enable 1：clk disable。 */
        unsigned int  sc_g3d_dw_axi_s2_cg_en        : 1;  /* bit[20]   : bit[20]: sc_g3d_dw_axi_s2_cg_en default:0x0
                                                                         0：clk enable 1：clk disable。 */
        unsigned int  sc_div_usb3phy                : 6;  /* bit[21-26]: bit[26:21]: sc_div_usb3phy[5:0] default:0x3b 分频比=配置值+1。 */
        unsigned int  sc_usb3phy_pll_div_en         : 1;  /* bit[27]   : bit[27]: sc_usb3phy_pll_div_en default:0x0
                                                                         0：disable 1：enable。 */
        unsigned int  reserved_2                    : 1;  /* bit[28]   : 保留。 */
        unsigned int  sc_modem_ipc_auto_clk_gate_en : 1;  /* bit[29]   : bit[29]: sc_modem_ipc_auto_clk_gate_en default:0x0
                                                                         0：auto clkgate disable；1：auto clkgate enable。 */
        unsigned int  sc_modem_ipc_soft_gate_clk_en : 1;  /* bit[30]   : bit[30]: sc_modem_ipc_soft_gate_clk_en default:0x0
                                                                         0：clk enable；1：clk gate。 */
        unsigned int  peri_ctrl25_cmd               : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL25_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL25_vdec_qos_0_START                     (0)
#define SOC_PCTRL_PERI_CTRL25_vdec_qos_0_END                       (1)
#define SOC_PCTRL_PERI_CTRL25_vdec_qos_1_START                     (2)
#define SOC_PCTRL_PERI_CTRL25_vdec_qos_1_END                       (3)
#define SOC_PCTRL_PERI_CTRL25_venc_qos_0_START                     (4)
#define SOC_PCTRL_PERI_CTRL25_venc_qos_0_END                       (5)
#define SOC_PCTRL_PERI_CTRL25_venc_qos_1_START                     (6)
#define SOC_PCTRL_PERI_CTRL25_venc_qos_1_END                       (7)
#define SOC_PCTRL_PERI_CTRL25_secp_mem_ctrl_sd_START               (8)
#define SOC_PCTRL_PERI_CTRL25_secp_mem_ctrl_sd_END                 (8)
#define SOC_PCTRL_PERI_CTRL25_secs_mem_ctrl_sd_START               (9)
#define SOC_PCTRL_PERI_CTRL25_secs_mem_ctrl_sd_END                 (9)
#define SOC_PCTRL_PERI_CTRL25_mmbuf_sram_sd_START                  (10)
#define SOC_PCTRL_PERI_CTRL25_mmbuf_sram_sd_END                    (10)
#define SOC_PCTRL_PERI_CTRL25_smmu_integ_sec_override_START        (11)
#define SOC_PCTRL_PERI_CTRL25_smmu_integ_sec_override_END          (11)
#define SOC_PCTRL_PERI_CTRL25_dphy2l_rx_enableclk_START            (13)
#define SOC_PCTRL_PERI_CTRL25_dphy2l_rx_enableclk_END              (13)
#define SOC_PCTRL_PERI_CTRL25_dphy4l_rx_enableclk0_START           (14)
#define SOC_PCTRL_PERI_CTRL25_dphy4l_rx_enableclk0_END             (14)
#define SOC_PCTRL_PERI_CTRL25_dphy4l_rx_enableclk1_START           (15)
#define SOC_PCTRL_PERI_CTRL25_dphy4l_rx_enableclk1_END             (15)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_m1_cg_en_START         (17)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_m1_cg_en_END           (17)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s0_cg_en_START         (18)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s0_cg_en_END           (18)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s1_cg_en_START         (19)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s1_cg_en_END           (19)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s2_cg_en_START         (20)
#define SOC_PCTRL_PERI_CTRL25_sc_g3d_dw_axi_s2_cg_en_END           (20)
#define SOC_PCTRL_PERI_CTRL25_sc_div_usb3phy_START                 (21)
#define SOC_PCTRL_PERI_CTRL25_sc_div_usb3phy_END                   (26)
#define SOC_PCTRL_PERI_CTRL25_sc_usb3phy_pll_div_en_START          (27)
#define SOC_PCTRL_PERI_CTRL25_sc_usb3phy_pll_div_en_END            (27)
#define SOC_PCTRL_PERI_CTRL25_sc_modem_ipc_auto_clk_gate_en_START  (29)
#define SOC_PCTRL_PERI_CTRL25_sc_modem_ipc_auto_clk_gate_en_END    (29)
#define SOC_PCTRL_PERI_CTRL25_sc_modem_ipc_soft_gate_clk_en_START  (30)
#define SOC_PCTRL_PERI_CTRL25_sc_modem_ipc_soft_gate_clk_en_END    (30)
#define SOC_PCTRL_PERI_CTRL25_peri_ctrl25_cmd_START                (31)
#define SOC_PCTRL_PERI_CTRL25_peri_ctrl25_cmd_END                  (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL26_UNION
 结构说明  : PERI_CTRL26 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器26。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pack_dbg_mode_en         : 4;  /* bit[0-3]  : [3:0]pack_dbg_mode_en default:0x0
                                                                    {packd_dbg_mode,packc_dbg_mode,packb_dbg_mode,packa_dbg_mode}
                                                                    0:diable 1:enable。 */
        unsigned int  pack_dbg_mode_sel        : 5;  /* bit[4-8]  : [8:4]pack_dbg_mode_sel default:0x0
                                                                    00000~11100：packa_dbg_mode=packa_dbg_mode00~28；
                                                                    others:packa_dbg_mode=16'h0。 */
        unsigned int  reserved_0               : 5;  /* bit[9-13] : 保留。 */
        unsigned int  isp_dw_axi_gatedclock_en : 1;  /* bit[14]   : [14]: isp_dw_axi_gatedclock_en default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  reserved_1               : 1;  /* bit[15]   : 保留。 */
        unsigned int  spi_tprf_slp             : 1;  /* bit[16]   : [16]: spi_tprf_slp memory sleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  spi_tprf_dslp            : 1;  /* bit[17]   : [17]: spi_tprf_dslp memory deepsleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  spi_tprf_sd              : 1;  /* bit[18]   : [18]: spi_tprf_sd memory shutdown default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_tprf_slp             : 1;  /* bit[19]   : [19]: g3d_tprf_slp memory sleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_tprf_dslp            : 1;  /* bit[20]   : [20]: g3d_tprf_dslp memory deepsleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_tprf_sd              : 1;  /* bit[21]   : [21]: g3d_tprf_sd memory shutdown default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_spsram_slp           : 1;  /* bit[22]   : [22]: g3d_spsram_slp memory sleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_spsram_dslp          : 1;  /* bit[23]   : [23]: g3d_spsram_dslp memory deepsleep default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  g3d_spsram_sd            : 1;  /* bit[24]   : [24]: g3d_spsram_sd memory shutdown default:0x0
                                                                    0：disable 1：enable。 */
        unsigned int  reserved_2               : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL26_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL26_pack_dbg_mode_en_START          (0)
#define SOC_PCTRL_PERI_CTRL26_pack_dbg_mode_en_END            (3)
#define SOC_PCTRL_PERI_CTRL26_pack_dbg_mode_sel_START         (4)
#define SOC_PCTRL_PERI_CTRL26_pack_dbg_mode_sel_END           (8)
#define SOC_PCTRL_PERI_CTRL26_isp_dw_axi_gatedclock_en_START  (14)
#define SOC_PCTRL_PERI_CTRL26_isp_dw_axi_gatedclock_en_END    (14)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_slp_START              (16)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_slp_END                (16)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_dslp_START             (17)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_dslp_END               (17)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_sd_START               (18)
#define SOC_PCTRL_PERI_CTRL26_spi_tprf_sd_END                 (18)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_slp_START              (19)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_slp_END                (19)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_dslp_START             (20)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_dslp_END               (20)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_sd_START               (21)
#define SOC_PCTRL_PERI_CTRL26_g3d_tprf_sd_END                 (21)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_slp_START            (22)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_slp_END              (22)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_dslp_START           (23)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_dslp_END             (23)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_sd_START             (24)
#define SOC_PCTRL_PERI_CTRL26_g3d_spsram_sd_END               (24)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL27_UNION
 结构说明  : PERI_CTRL27 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器27。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_sft_fiq    : 1;  /* bit[0]   : isp sft fiq
                                                         0:fiq int disable
                                                         1:fiq int enable
                                                         每次配置先，先配置为0，再配置为1。 */
        unsigned int  isp_sys_ctrl_0 : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL27_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL27_isp_sft_fiq_START     (0)
#define SOC_PCTRL_PERI_CTRL27_isp_sft_fiq_END       (0)
#define SOC_PCTRL_PERI_CTRL27_isp_sys_ctrl_0_START  (1)
#define SOC_PCTRL_PERI_CTRL27_isp_sys_ctrl_0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL28_UNION
 结构说明  : PERI_CTRL28 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器28。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_sys_ctrl_1 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL28_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL28_isp_sys_ctrl_1_START  (0)
#define SOC_PCTRL_PERI_CTRL28_isp_sys_ctrl_1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL29_UNION
 结构说明  : PERI_CTRL29 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器29。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pctrl_dphytx_stopcnt0 : 32; /* bit[0-31]: DPHY4L Tx dphy输出 stopstate信号为高的时间，timer用pctrl的apb时钟做计数；default值为0。动态调频时，dphy输出 stopstate信号为高的时间，计数到配置值，则dphytx_pctrl_trstop_flag为高，计数时钟为120MHz。 */
    } reg;
} SOC_PCTRL_PERI_CTRL29_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL29_pctrl_dphytx_stopcnt0_START  (0)
#define SOC_PCTRL_PERI_CTRL29_pctrl_dphytx_stopcnt0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL30_UNION
 结构说明  : PERI_CTRL30 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器30。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pctrl_dphytx_ctrl0 : 16; /* bit[0-15] : DPHY4L Tx 是pctrl给dphy的控制寄存器位，default值为0，[14] lock sel bypass；为1时，dphy输出的lanebyteclk在送给控制器dsi时，在dphy外部不做门控；为0时，根据bit 13 lock sel选择门控使能的信号；
                                                              [13] lock sel；
                                                              bit 14 lock sel bypass = 1时，该bit无效；
                                                              bit 14 lock sel bypass = 0时，lock sel 为1，bit12 lock state为lanebyteclk在dphy外部的门控使能；lock sel 为0，选择dphy的输出lock信号作为lanebyteclk在dphy外部的门控使能；dphy lock=1：时钟使能；dphy lock = 0：时钟关闭，不会送到DSI；
                                                              [12] lock state；bit 14 lock sel bypass = 0，lock sel = 1时，lanebyteclk的门控使能信号，1：时钟使能；0：时钟关闭，不会送到DSI；
                                                              [9] lanebyte rst switch；lanebyteclk门控逻辑的复位选择；
                                                              1：lanebyteclk门控逻辑的复位来自寄存器bit 8 lanebyte rst cfg的配置；
                                                              0：lanebyteclk们控逻辑的复位即pctrl的preset_n;
                                                              [8] lanebyte rst cfg; lanebyte rst switch = 1时，控制lanebyteclk门控逻辑的复位；
                                                               1：解复位；
                                                               0：复位；
                                                              [7:3] stopstate mask; dphy输出的时钟和数据lane的stopstate状态信号的mask位；根据lane数目的配置以及auto clk是否打开，配置stopstate状态信号的mask位；
                                                               bit3 clklane的stopstate mask，
                                                               bit4 lane0的stopstate mask，
                                                               bit5 lane1的stopstate mask，
                                                               bit6 lane2的stopstate mask，
                                                               bit7 lane3的stopstate mask
                                                              [1] stopstate clear；bit 0 stopstate enable=1时有效；
                                                              1：dphytx_pctrl_trstop_flag的清除以及stopstate计数清0；
                                                              [0] stopstate enable;stopstate为高的计数功能使能；使能后stopstate计数逻辑才开始根据dphy输出的stopstate信号状态开始计数；
                                                              Others：Reserved。 */
        unsigned int  pctrl_dphytx_ctrl1 : 16; /* bit[16-31]: DPHY4L Tx 是pctrl给dphy的控制寄存器位，default值为0，[14] lock sel bypass；为1时，dphy输出的lanebyteclk在送给控制器dsi时，在dphy外部不做门控；为0时，根据bit 13 lock sel选择门控使能的信号；
                                                              [13] lock sel；
                                                              bit 14 lock sel bypass = 1时，该bit无效；
                                                              bit 14 lock sel bypass = 0时，lock sel 为1，bit12 lock state为lanebyteclk在dphy外部的门控使能；lock sel 为0，选择dphy的输出lock信号作为lanebyteclk在dphy外部的门控使能；dphy lock=1：时钟使能；dphy lock = 0：时钟关闭，不会送到DSI；
                                                              [12] lock state；bit 14 lock sel bypass = 0，lock sel = 1时，lanebyteclk的门控使能信号，1：时钟使能；0：时钟关闭，不会送到DSI；
                                                              [9] lanebyte rst switch；lanebyteclk门控逻辑的复位选择；
                                                              1：lanebyteclk门控逻辑的复位来自寄存器bit 8 lanebyte rst cfg的配置；
                                                              0：lanebyteclk们控逻辑的复位即pctrl的preset_n;
                                                              [8] lanebyte rst cfg; lanebyte rst switch = 1时，控制lanebyteclk门控逻辑的复位；
                                                               1：解复位；
                                                               0：复位；
                                                              [7:3] stopstate mask; dphy输出的时钟和数据lane的stopstate状态信号的mask位；根据lane数目的配置以及auto clk是否打开，配置stopstate状态信号的mask位；
                                                               bit3 clklane的stopstate mask，
                                                               bit4 lane0的stopstate mask，
                                                               bit5 lane1的stopstate mask，
                                                               bit6 lane2的stopstate mask，
                                                               bit7 lane3的stopstate mask
                                                              [1] stopstate clear；bit 0 stopstate enable=1时有效；
                                                              1：dphytx_pctrl_trstop_flag的清除以及stopstate计数清0；
                                                              [0] stopstate enable;stopstate为高的计数功能使能；使能后stopstate计数逻辑才开始根据dphy输出的stopstate信号状态开始计数；
                                                              Others：Reserved。 */
    } reg;
} SOC_PCTRL_PERI_CTRL30_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL30_pctrl_dphytx_ctrl0_START  (0)
#define SOC_PCTRL_PERI_CTRL30_pctrl_dphytx_ctrl0_END    (15)
#define SOC_PCTRL_PERI_CTRL30_pctrl_dphytx_ctrl1_START  (16)
#define SOC_PCTRL_PERI_CTRL30_pctrl_dphytx_ctrl1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL31_UNION
 结构说明  : PERI_CTRL31 寄存器结构定义。地址偏移量:0x080，初值:0x05350715，宽度:32
 寄存器说明: 通用外设控制寄存器31。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_spram_rtsel    : 2;  /* bit[0-1]  : peri_spram_rtsel 具体参考memory控制说明。 */
        unsigned int  peri_spram_wtsel    : 2;  /* bit[2-3]  : peri_spram_wtsel 具体参考memory控制说明。 */
        unsigned int  peri_spmbsram_rtsel : 2;  /* bit[4-5]  : peri_spmbsram_rtsel 具体参考memory控制说明。 */
        unsigned int  peri_spmbsram_wtsel : 2;  /* bit[6-7]  : peri_spmbsram_wtsel 具体参考memory控制说明。 */
        unsigned int  peri_rom_rtsel      : 2;  /* bit[8-9]  : peri_rom_rtsel 具体参考memory控制说明。 */
        unsigned int  peri_rom_ptsel      : 2;  /* bit[10-11]: peri_rom_ptsel 具体参考memory控制说明。 */
        unsigned int  peri_rom_trb        : 2;  /* bit[12-13]: peri_rom_trb 具体参考memory控制说明。 */
        unsigned int  peri_rom_tm         : 1;  /* bit[14]   : peri_rom_tm 具体参考memory控制说明。 */
        unsigned int  reserved_0          : 1;  /* bit[15]   : 保留。 */
        unsigned int  peri_tprf_rct       : 2;  /* bit[16-17]: peri_tprf_rct 具体参考memory控制说明。 */
        unsigned int  peri_tprf_wct       : 2;  /* bit[18-19]: peri_tprf_wct 具体参考memory控制说明。 */
        unsigned int  peri_tprf_kp        : 3;  /* bit[20-22]: peri_tprf_kp 具体参考memory控制说明。 */
        unsigned int  reserved_1          : 1;  /* bit[23]   : 保留。 */
        unsigned int  peri_dpsram_rtsel   : 2;  /* bit[24-25]: peri_dpsram_rtsel 具体参考memory控制说明。 */
        unsigned int  peri_dpsram_wtsel   : 2;  /* bit[26-27]: peri_dpsram_wtsel 具体参考memory控制说明。 */
        unsigned int  reserved_2          : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL31_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL31_peri_spram_rtsel_START     (0)
#define SOC_PCTRL_PERI_CTRL31_peri_spram_rtsel_END       (1)
#define SOC_PCTRL_PERI_CTRL31_peri_spram_wtsel_START     (2)
#define SOC_PCTRL_PERI_CTRL31_peri_spram_wtsel_END       (3)
#define SOC_PCTRL_PERI_CTRL31_peri_spmbsram_rtsel_START  (4)
#define SOC_PCTRL_PERI_CTRL31_peri_spmbsram_rtsel_END    (5)
#define SOC_PCTRL_PERI_CTRL31_peri_spmbsram_wtsel_START  (6)
#define SOC_PCTRL_PERI_CTRL31_peri_spmbsram_wtsel_END    (7)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_rtsel_START       (8)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_rtsel_END         (9)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_ptsel_START       (10)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_ptsel_END         (11)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_trb_START         (12)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_trb_END           (13)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_tm_START          (14)
#define SOC_PCTRL_PERI_CTRL31_peri_rom_tm_END            (14)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_rct_START        (16)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_rct_END          (17)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_wct_START        (18)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_wct_END          (19)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_kp_START         (20)
#define SOC_PCTRL_PERI_CTRL31_peri_tprf_kp_END           (22)
#define SOC_PCTRL_PERI_CTRL31_peri_dpsram_rtsel_START    (24)
#define SOC_PCTRL_PERI_CTRL31_peri_dpsram_rtsel_END      (25)
#define SOC_PCTRL_PERI_CTRL31_peri_dpsram_wtsel_START    (26)
#define SOC_PCTRL_PERI_CTRL31_peri_dpsram_wtsel_END      (27)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL32_UNION
 结构说明  : PERI_CTRL32 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器32。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pctrl_dphytx_stopcnt1 : 32; /* bit[0-31]: DPHY4L Tx 是timer的计数值配置寄存器，timer用pctrl的apb时钟做计数；default值为0。 */
    } reg;
} SOC_PCTRL_PERI_CTRL32_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL32_pctrl_dphytx_stopcnt1_START  (0)
#define SOC_PCTRL_PERI_CTRL32_pctrl_dphytx_stopcnt1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL33_UNION
 结构说明  : PERI_CTRL33 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器33。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL33_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT0_UNION
 结构说明  : PERI_STAT0 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat0                : 30; /* bit[0-29]: bit[29]:保留
                                                                    bit[27]:int sysbus ddrc packet probe mainstatalarm
                                                                    bit[26]:int venc transaction probe mainstatalarm
                                                                    bit[25]:保留
                                                                    bit[18]:intr dss1 wr transaction probe mainstatalarm
                                                                    bit[17]:intr dss1 rd transaction probe mainstatalarm
                                                                    bit[16]:int dss0 wr transaction probe mainstatalarm
                                                                    bit[15]:int dss0 rd transaction probe mainstatalarm
                                                                    bit[14]:保留
                                                                    bit[13]:int modem transaction probe mainstatalarm
                                                                    bit[12]:reserved
                                                                    bit[11]:保留
                                                                    bit[10]:保留
                                                                    bit[9]:int mmc1bus error probe observer mainfault0
                                                                    bit[8]:int mmc0bus error probe observer mainfault0
                                                                    bit[7]:int cfgbus error probe observer mainfault0
                                                                    bit[6]:int vivobus error probe observer mainfault0
                                                                    bit[5]:int vcodec bus error probe observer mainfault0
                                                                    bit[4]:int dbgbus error probe observer mainfault0
                                                                    bit[3]:int modem cfg error probe observer mainfault0
                                                                    bit[2]:保留
                                                                    bit[1]:int sysbus error probe observer mainfault0
                                                                    bit[0]:int dmabus error probe observer mainfault0
                                                                    具体参考总线相关说明。 */
        unsigned int  dphytx_pctrl_trstop_flag1 : 1;  /* bit[30]  : 1bit X 2套DPHY4L Tx 标示1clk+4data lane 的stopstate持续为高timer计数值，则flag为1。 */
        unsigned int  dphytx_pctrl_trstop_flag0 : 1;  /* bit[31]  : 1bit X 2套DPHY4L Tx 标示1clk+4data lane 的stopstate持续为高timer计数值，则flag为1。 */
    } reg;
} SOC_PCTRL_PERI_STAT0_UNION;
#endif
#define SOC_PCTRL_PERI_STAT0_peri_stat0_START                 (0)
#define SOC_PCTRL_PERI_STAT0_peri_stat0_END                   (29)
#define SOC_PCTRL_PERI_STAT0_dphytx_pctrl_trstop_flag1_START  (30)
#define SOC_PCTRL_PERI_STAT0_dphytx_pctrl_trstop_flag1_END    (30)
#define SOC_PCTRL_PERI_STAT0_dphytx_pctrl_trstop_flag0_START  (31)
#define SOC_PCTRL_PERI_STAT0_dphytx_pctrl_trstop_flag0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT1_UNION
 结构说明  : PERI_STAT1 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dphytx_pctrl_status0 : 32; /* bit[0-31]: 32 bit X 2套DPHY4L Tx 可以读出timer的当前计数值。 */
    } reg;
} SOC_PCTRL_PERI_STAT1_UNION;
#endif
#define SOC_PCTRL_PERI_STAT1_dphytx_pctrl_status0_START  (0)
#define SOC_PCTRL_PERI_STAT1_dphytx_pctrl_status0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT2_UNION
 结构说明  : PERI_STAT2 寄存器结构定义。地址偏移量:0x09C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 通用外设状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat2                 : 31; /* bit[0-30]: bit[30]:vdec service target mainnopendingtrans
                                                                     bit[29]:保留
                                                                     bit[28]:noc mmc0bus sdio0 I mainnopendingtrans
                                                                     bit[27]:noc vcodec cfg I mainnopendingtrans
                                                                     bit[23]:noc a7tovivobus wr i mainnopendingtrans
                                                                     bit[22]:noc a7tovivobus rd i mainnopendingtrans
                                                                     bit[21]:noc isp wr i mainnopendingtrans
                                                                     bit[20]:noc isp rd i mainnopendingtrans
                                                                     bit[19]:isp service target mainnopendingtrans
                                                                     bit[18]:noc dmac mst i mainnopendingtrans
                                                                     bit[17]:dmabus service target mainnopendingtrans
                                                                     bit[16]:noc vivo cfg i mainnopendingtrans
                                                                     bit[15]:noc dss1 wr i mainnopendingtrans
                                                                     bit[14]:保留
                                                                     bit[13]:noc dss1 rd i mainnopendingtrans
                                                                     bit[12]:noc dss0 wr i mainnopendingtrans
                                                                     bit[11]:noc dss0 rd i mainnopendingtrans
                                                                     bit[10]:dss service target mainnopendingtrans
                                                                     bit[9]:noc top cssys i mainnopendingtrans
                                                                     bit[8]:noc socp i mainnopendingtrans
                                                                     bit[7]:noc secs i mainnopendingtrans
                                                                     bit[6]:noc secp i mainnopendingtrans
                                                                     bit[5]:noc usb3 i mainnopendingtrans
                                                                     bit[4]:dbgbus service target mainnopendingtrans
                                                                     bit[3]:noc lpm3 mst i mainnopendingtrans
                                                                     bit[2]:noc perf stat i mainnopendingtrans
                                                                     bit[1]:noc djtag mst i mainnopendingtrans
                                                                     bit[0]:cfgbus service target mainnopendingtrans
                                                                     具体参考总线相关说明。 */
        unsigned int  nocvencimainnopendingtrans : 1;  /* bit[31]  : bit[31]:noc venc I mainnopendingtrans 具体参考总线相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT2_UNION;
#endif
#define SOC_PCTRL_PERI_STAT2_peri_stat2_START                  (0)
#define SOC_PCTRL_PERI_STAT2_peri_stat2_END                    (30)
#define SOC_PCTRL_PERI_STAT2_nocvencimainnopendingtrans_START  (31)
#define SOC_PCTRL_PERI_STAT2_nocvencimainnopendingtrans_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT3_UNION
 结构说明  : PERI_STAT3 寄存器结构定义。地址偏移量:0x0A0，初值:0x0003FFFF，宽度:32
 寄存器说明: 通用外设状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat3 : 32; /* bit[0-31]: bit[31]:intr_a7_rd_transaction_probe_mainstatalarm
                                                     bit[30]:intr_a7_wr_transaction_probe_mainstatalarm
                                                     bit[29]:intr_isp_rd_transaction_probe_mainstatalarm
                                                     bit[28]:intr_isp_wr_transaction_probe_mainstatalarm
                                                     bit[27:23]:reserved
                                                     bit[22]:intr_ivp32_peri_bus_error_probe_observer_mainfault_0
                                                     bit[21]:reserved
                                                     bit[20]:sc noc vcodecbus target mainnopendingtrans
                                                     bit[19]:sc noc vdec i mainnopendingtrans
                                                     bit[18]:sc noc a7tocfg i mainnopendingtrans
                                                     bit[17]:保留
                                                     bit[16]:sc nocivp32 mst i mainnopendingtrans
                                                     bit[15]:sc ivp32 peri bus service mainnopendingtrans
                                                     bit[14]:sc noc emmc1 i mainnopendingtrans
                                                     bit[13]:sc noc emmc0 i mainnopendingtrans
                                                     bit[12]:sc mmc1bus service target mainnopendingtrans
                                                     bit[11]:mmc0bus service target mainnopendingtrans
                                                     bit[10]:sysbus service target mainnopendingtrans
                                                     bit[9]:noc modem mst I mainnopendingtrans
                                                     bit[7]:noc cci2sysbus i mainnopendingtrans
                                                     bit[6]:保留
                                                     bit[5]:modembus service target mainnopendingtrans
                                                     bit[4]:保留
                                                     bit[0]:venc service target mainnopendingtrans 
                                                     具体参考总线相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT3_UNION;
#endif
#define SOC_PCTRL_PERI_STAT3_peri_stat3_START  (0)
#define SOC_PCTRL_PERI_STAT3_peri_stat3_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT4_UNION
 结构说明  : PERI_STAT4 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat4 : 23; /* bit[0-22] : bit[22]: intr_cci400_err 
                                                      0：error 1：normal；
                                                      bit[21:19]:modem ipc clk state[2:0]
                                                      000：start 001：wait 010：access 011：busy
                                                      100：IDLE othes：no meaning。
                                                      bit[18]:ivp32 dwaxi dlock irq具体参考总线相关说明
                                                      bit[17]:ivp32 dwaxi dlock wr具体参考总线相关说明
                                                      bit[16:13]:ivp32 dwaxi dlock id[3:0]具体参考总线相关说明
                                                      bit[12:10]:ivp32 dwaxi dlock slv[2:0]具体参考总线相关说明
                                                      bit[9]:ivp32 dwaxi dlock mst具体参考总线相关说明
                                                      bit[8]:保留
                                                      bit[7]:保留
                                                      bit[6]:socp idle
                                                      0：busy 1：idle；
                                                      bit[5]:venc mem req priority
                                                      bit[4]:venc idle
                                                      0：busy 1：idle；
                                                      bit[3]:vdec mem req priority
                                                      bit[2]:vdec idle
                                                      0：busy 1：idle；
                                                      bit[1]:保留
                                                      bit[0]:保留。 */
        unsigned int  reserved   : 9;  /* bit[23-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_STAT4_UNION;
#endif
#define SOC_PCTRL_PERI_STAT4_peri_stat4_START  (0)
#define SOC_PCTRL_PERI_STAT4_peri_stat4_END    (22)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT5_UNION
 结构说明  : PERI_STAT5 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_mdm2ap_states : 32; /* bit[0-31]: sc_mdm2ap_states[31:0] modem testpin具体参考modem管脚调试说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT5_UNION;
#endif
#define SOC_PCTRL_PERI_STAT5_sc_mdm2ap_states_START  (0)
#define SOC_PCTRL_PERI_STAT5_sc_mdm2ap_states_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT6_UNION
 结构说明  : PERI_STAT6 寄存器结构定义。地址偏移量:0x0AC，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_mdm2ap_states : 32; /* bit[0-31]: sc_mdm2ap_states[63:32]暂未使用。 */
    } reg;
} SOC_PCTRL_PERI_STAT6_UNION;
#endif
#define SOC_PCTRL_PERI_STAT6_sc_mdm2ap_states_START  (0)
#define SOC_PCTRL_PERI_STAT6_sc_mdm2ap_states_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT7_UNION
 结构说明  : PERI_STAT7 寄存器结构定义。地址偏移量:0x0B0，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_mdm2ap_states : 32; /* bit[0-31]: sc_mdm2ap_states[95:64]暂未使用。 */
    } reg;
} SOC_PCTRL_PERI_STAT7_UNION;
#endif
#define SOC_PCTRL_PERI_STAT7_sc_mdm2ap_states_START  (0)
#define SOC_PCTRL_PERI_STAT7_sc_mdm2ap_states_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT8_UNION
 结构说明  : PERI_STAT8 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_mdm2ap_states : 32; /* bit[0-31]: sc_mdm2ap_states[127:96]暂未使用。 */
    } reg;
} SOC_PCTRL_PERI_STAT8_UNION;
#endif
#define SOC_PCTRL_PERI_STAT8_sc_mdm2ap_states_START  (0)
#define SOC_PCTRL_PERI_STAT8_sc_mdm2ap_states_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT9_UNION
 结构说明  : PERI_STAT9 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s0_grp : 16; /* bit[0-15] : bit[15:0]:tp_s0_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s1_grp : 16; /* bit[16-31]: bit[31:16]:tp_s1_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT9_UNION;
#endif
#define SOC_PCTRL_PERI_STAT9_tp_s0_grp_START  (0)
#define SOC_PCTRL_PERI_STAT9_tp_s0_grp_END    (15)
#define SOC_PCTRL_PERI_STAT9_tp_s1_grp_START  (16)
#define SOC_PCTRL_PERI_STAT9_tp_s1_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT10_UNION
 结构说明  : PERI_STAT10 寄存器结构定义。地址偏移量:0x0BC，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s2_grp : 16; /* bit[0-15] : bit[15:0]:tp_s2_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s7_grp : 16; /* bit[16-31]: bit[31:16]:tp_s7_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT10_UNION;
#endif
#define SOC_PCTRL_PERI_STAT10_tp_s2_grp_START  (0)
#define SOC_PCTRL_PERI_STAT10_tp_s2_grp_END    (15)
#define SOC_PCTRL_PERI_STAT10_tp_s7_grp_START  (16)
#define SOC_PCTRL_PERI_STAT10_tp_s7_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT11_UNION
 结构说明  : PERI_STAT11 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s8_grp : 16; /* bit[0-15] : bit[15:0]:tp_s8_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s9_grp : 16; /* bit[16-31]: bit[31:16]:tp_s9_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT11_UNION;
#endif
#define SOC_PCTRL_PERI_STAT11_tp_s8_grp_START  (0)
#define SOC_PCTRL_PERI_STAT11_tp_s8_grp_END    (15)
#define SOC_PCTRL_PERI_STAT11_tp_s9_grp_START  (16)
#define SOC_PCTRL_PERI_STAT11_tp_s9_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT12_UNION
 结构说明  : PERI_STAT12 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s10_grp : 16; /* bit[0-15] : bit[15:0]:tp_s10_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s11_grp : 16; /* bit[16-31]: bit[31:16]:tp_s11_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT12_UNION;
#endif
#define SOC_PCTRL_PERI_STAT12_tp_s10_grp_START  (0)
#define SOC_PCTRL_PERI_STAT12_tp_s10_grp_END    (15)
#define SOC_PCTRL_PERI_STAT12_tp_s11_grp_START  (16)
#define SOC_PCTRL_PERI_STAT12_tp_s11_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT13_UNION
 结构说明  : PERI_STAT13 寄存器结构定义。地址偏移量:0x0C8，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s12_grp : 16; /* bit[0-15] : bit[15:0]:tp_s12_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s13_grp : 16; /* bit[16-31]: bit[31:16]:tp_s13_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT13_UNION;
#endif
#define SOC_PCTRL_PERI_STAT13_tp_s12_grp_START  (0)
#define SOC_PCTRL_PERI_STAT13_tp_s12_grp_END    (15)
#define SOC_PCTRL_PERI_STAT13_tp_s13_grp_START  (16)
#define SOC_PCTRL_PERI_STAT13_tp_s13_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT14_UNION
 结构说明  : PERI_STAT14 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_s14_grp : 16; /* bit[0-15] : bit[15:0]:tp_s14_grp[15:0] 具体配置参考管脚测试相关说明。 */
        unsigned int  tp_s15_grp : 16; /* bit[16-31]: bit[31:16]:tp_s15_grp[15:0] 具体配置参考管脚测试相关说明。 */
    } reg;
} SOC_PCTRL_PERI_STAT14_UNION;
#endif
#define SOC_PCTRL_PERI_STAT14_tp_s14_grp_START  (0)
#define SOC_PCTRL_PERI_STAT14_tp_s14_grp_END    (15)
#define SOC_PCTRL_PERI_STAT14_tp_s15_grp_START  (16)
#define SOC_PCTRL_PERI_STAT14_tp_s15_grp_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT15_UNION
 结构说明  : PERI_STAT15 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器15。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_isp_dlock : 11; /* bit[0-10] : [10]:axi_isp_dlock_wr
                                                         具体参考总线相关说明
                                                         [9:4]:axi_isp_dlock_id
                                                         具体参考总线相关说明
                                                         [3:1]:axi_isp_dlock_slv
                                                         具体参考总线相关说明
                                                         [0]:axi_isp_dlock_mst
                                                         具体参考总线相关说明。 */
        unsigned int  peri_stat15   : 21; /* bit[11-31]: others:reserved
                                                         [13]:vdm_clk_en_2
                                                         0：clk disable 1：clk enable；
                                                         [12]:vdm_clk_en_1
                                                         0：clk disable 1：clk enable；
                                                         [11]:vdm_clk_en_0
                                                         0：clk disable 1：clk enable。 */
    } reg;
} SOC_PCTRL_PERI_STAT15_UNION;
#endif
#define SOC_PCTRL_PERI_STAT15_axi_isp_dlock_START  (0)
#define SOC_PCTRL_PERI_STAT15_axi_isp_dlock_END    (10)
#define SOC_PCTRL_PERI_STAT15_peri_stat15_START    (11)
#define SOC_PCTRL_PERI_STAT15_peri_stat15_END      (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT16_UNION
 结构说明  : PERI_STAT16 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器16。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dphytx_pctrl_status1 : 32; /* bit[0-31]: 32 bit X 2套DPHY4L Tx 可以读出timer的当前计数值。 */
    } reg;
} SOC_PCTRL_PERI_STAT16_UNION;
#endif
#define SOC_PCTRL_PERI_STAT16_dphytx_pctrl_status1_START  (0)
#define SOC_PCTRL_PERI_STAT16_dphytx_pctrl_status1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT17_UNION
 结构说明  : PERI_STAT17 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器17。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat17 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_STAT17_UNION;
#endif
#define SOC_PCTRL_PERI_STAT17_peri_stat17_START  (0)
#define SOC_PCTRL_PERI_STAT17_peri_stat17_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT18_UNION
 结构说明  : PERI_STAT18 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器18。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat18 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_STAT18_UNION;
#endif
#define SOC_PCTRL_PERI_STAT18_peri_stat18_START  (0)
#define SOC_PCTRL_PERI_STAT18_peri_stat18_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_STAT19_UNION
 结构说明  : PERI_STAT19 寄存器结构定义。地址偏移量:0x0E0，初值:0x00000000，宽度:32
 寄存器说明: 通用外设状态寄存器19。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat19 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_STAT19_UNION;
#endif
#define SOC_PCTRL_PERI_STAT19_peri_stat19_START  (0)
#define SOC_PCTRL_PERI_STAT19_peri_stat19_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_USB2_HOST_CTRL0_UNION
 结构说明  : USB2_HOST_CTRL0 寄存器结构定义。地址偏移量:0x0F0，初值:0x00000000，宽度:32
 寄存器说明: USB2 HOST控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb2_host_ctrl0 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_USB2_HOST_CTRL0_UNION;
#endif
#define SOC_PCTRL_USB2_HOST_CTRL0_usb2_host_ctrl0_START  (0)
#define SOC_PCTRL_USB2_HOST_CTRL0_usb2_host_ctrl0_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_USB2_HOST_CTRL1_UNION
 结构说明  : USB2_HOST_CTRL1 寄存器结构定义。地址偏移量:0x0F4，初值:0x0000240C，宽度:32
 寄存器说明: USB2 HOST控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb2_host_ctrl1 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_USB2_HOST_CTRL1_UNION;
#endif
#define SOC_PCTRL_USB2_HOST_CTRL1_usb2_host_ctrl1_START  (0)
#define SOC_PCTRL_USB2_HOST_CTRL1_usb2_host_ctrl1_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_USB2_HOST_CTRL2_UNION
 结构说明  : USB2_HOST_CTRL2 寄存器结构定义。地址偏移量:0x0F8，初值:0x00000000，宽度:32
 寄存器说明: USB2 HOST控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usb2_host_ctrl2 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_PCTRL_USB2_HOST_CTRL2_UNION;
#endif
#define SOC_PCTRL_USB2_HOST_CTRL2_usb2_host_ctrl2_START  (0)
#define SOC_PCTRL_USB2_HOST_CTRL2_usb2_host_ctrl2_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE0_LOCK_UNION
 结构说明  : RESOURCE0_LOCK 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource0lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁0的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id0  : 3;  /* bit[1-3]  : 通用资源锁0的锁定master ID号0。 */
        unsigned int  resource0lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁0的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id1  : 3;  /* bit[5-7]  : 通用资源锁0的锁定master ID号1。 */
        unsigned int  resource0lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁0的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id2  : 3;  /* bit[9-11] : 通用资源锁0的锁定master ID号2。 */
        unsigned int  resource0lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁0的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id3  : 3;  /* bit[13-15]: 通用资源锁0的锁定master ID号3。 */
        unsigned int  resource0lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁0的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id4  : 3;  /* bit[17-19]: 通用资源锁0的锁定master ID号4。 */
        unsigned int  resource0lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁0的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id5  : 3;  /* bit[21-23]: 通用资源锁0的锁定master ID号5。 */
        unsigned int  resource0lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁0的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id6  : 3;  /* bit[25-27]: 通用资源锁0的锁定master ID号6。 */
        unsigned int  resource0lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁0的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource0lock_id7  : 3;  /* bit[29-31]: 通用资源锁0的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE0_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE0_LOCK_resource0lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE0_UNLOCK_UNION
 结构说明  : RESOURCE0_UNLOCK 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource0unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁0的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁0的解锁master ID号0。 */
        unsigned int  resource0unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁0的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁0的解锁master ID号1。 */
        unsigned int  resource0unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁0的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id2  : 3;  /* bit[9-11] : 通用资源锁0的解锁master ID号2。 */
        unsigned int  resource0unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁0的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id3  : 3;  /* bit[13-15]: 通用资源锁0的解锁master ID号3。 */
        unsigned int  resource0unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁0的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id4  : 3;  /* bit[17-19]: 通用资源锁0的解锁master ID号4。 */
        unsigned int  resource0unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁0的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id5  : 3;  /* bit[21-23]: 通用资源锁0的解锁master ID号5。 */
        unsigned int  resource0unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁0的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id6  : 3;  /* bit[25-27]: 通用资源锁0的解锁master ID号6。 */
        unsigned int  resource0unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁0的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource0unlock_id7  : 3;  /* bit[29-31]: 通用资源锁0的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE0_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE0_UNLOCK_resource0unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE0_LOCK_ST_UNION
 结构说明  : RESOURCE0_LOCK_ST 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource0lock_st0    : 1;  /* bit[0-0]  : 通用资源锁0的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁0的锁定状态master ID号0。 */
        unsigned int  resource0lock_st1    : 1;  /* bit[4-4]  : 通用资源锁0的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁0的锁定状态master ID号1。 */
        unsigned int  resource0lock_st2    : 1;  /* bit[8-8]  : 通用资源锁0的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁0的锁定状态master ID号2。 */
        unsigned int  resource0lock_st3    : 1;  /* bit[12-12]: 通用资源锁0的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁0的锁定状态master ID号3。 */
        unsigned int  resource0lock_st4    : 1;  /* bit[16-16]: 通用资源锁0的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁0的锁定状态master ID号4。 */
        unsigned int  resource0lock_st5    : 1;  /* bit[20-20]: 通用资源锁0的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁0的锁定状态master ID号5。 */
        unsigned int  resource0lock_st6    : 1;  /* bit[24-24]: 通用资源锁0的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁0的锁定状态master ID号6。 */
        unsigned int  resource0lock_st7    : 1;  /* bit[28-28]: 通用资源锁0的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource0lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁0的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE0_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE0_LOCK_ST_resource0lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE1_LOCK_UNION
 结构说明  : RESOURCE1_LOCK 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource1lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁1的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id0  : 3;  /* bit[1-3]  : 通用资源锁1的锁定master ID号0。 */
        unsigned int  resource1lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁1的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id1  : 3;  /* bit[5-7]  : 通用资源锁1的锁定master ID号1。 */
        unsigned int  resource1lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁1的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id2  : 3;  /* bit[9-11] : 通用资源锁1的锁定master ID号2。 */
        unsigned int  resource1lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁1的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id3  : 3;  /* bit[13-15]: 通用资源锁1的锁定master ID号3。 */
        unsigned int  resource1lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁1的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id4  : 3;  /* bit[17-19]: 通用资源锁1的锁定master ID号4。 */
        unsigned int  resource1lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁1的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id5  : 3;  /* bit[21-23]: 通用资源锁1的锁定master ID号5。 */
        unsigned int  resource1lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁1的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id6  : 3;  /* bit[25-27]: 通用资源锁1的锁定master ID号6。 */
        unsigned int  resource1lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁1的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource1lock_id7  : 3;  /* bit[29-31]: 通用资源锁1的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE1_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE1_LOCK_resource1lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE1_UNLOCK_UNION
 结构说明  : RESOURCE1_UNLOCK 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource1unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁1的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁1的解锁master ID号0。 */
        unsigned int  resource1unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁1的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁1的解锁master ID号1。 */
        unsigned int  resource1unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁1的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id2  : 3;  /* bit[9-11] : 通用资源锁1的解锁master ID号2。 */
        unsigned int  resource1unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁1的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id3  : 3;  /* bit[13-15]: 通用资源锁1的解锁master ID号3。 */
        unsigned int  resource1unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁1的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id4  : 3;  /* bit[17-19]: 通用资源锁1的解锁master ID号4。 */
        unsigned int  resource1unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁1的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id5  : 3;  /* bit[21-23]: 通用资源锁1的解锁master ID号5。 */
        unsigned int  resource1unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁1的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id6  : 3;  /* bit[25-27]: 通用资源锁1的解锁master ID号6。 */
        unsigned int  resource1unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁1的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource1unlock_id7  : 3;  /* bit[29-31]: 通用资源锁1的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE1_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE1_UNLOCK_resource1unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE1_LOCK_ST_UNION
 结构说明  : RESOURCE1_LOCK_ST 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource1lock_st0    : 1;  /* bit[0-0]  : 通用资源锁1的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁1的锁定状态master ID号0。 */
        unsigned int  resource1lock_st1    : 1;  /* bit[4-4]  : 通用资源锁1的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁1的锁定状态master ID号1。 */
        unsigned int  resource1lock_st2    : 1;  /* bit[8-8]  : 通用资源锁1的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁1的锁定状态master ID号2。 */
        unsigned int  resource1lock_st3    : 1;  /* bit[12-12]: 通用资源锁1的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁1的锁定状态master ID号3。 */
        unsigned int  resource1lock_st4    : 1;  /* bit[16-16]: 通用资源锁1的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁1的锁定状态master ID号4。 */
        unsigned int  resource1lock_st5    : 1;  /* bit[20-20]: 通用资源锁1的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁1的锁定状态master ID号5。 */
        unsigned int  resource1lock_st6    : 1;  /* bit[24-24]: 通用资源锁1的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁1的锁定状态master ID号6。 */
        unsigned int  resource1lock_st7    : 1;  /* bit[28-28]: 通用资源锁1的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource1lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁1的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE1_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE1_LOCK_ST_resource1lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE2_LOCK_UNION
 结构说明  : RESOURCE2_LOCK 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource2lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁2的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id0  : 3;  /* bit[1-3]  : 通用资源锁2的锁定master ID号0。 */
        unsigned int  resource2lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁2的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id1  : 3;  /* bit[5-7]  : 通用资源锁2的锁定master ID号1。 */
        unsigned int  resource2lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁2的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id2  : 3;  /* bit[9-11] : 通用资源锁2的锁定master ID号2。 */
        unsigned int  resource2lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁2的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id3  : 3;  /* bit[13-15]: 通用资源锁2的锁定master ID号3。 */
        unsigned int  resource2lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁2的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id4  : 3;  /* bit[17-19]: 通用资源锁2的锁定master ID号4。 */
        unsigned int  resource2lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁2的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id5  : 3;  /* bit[21-23]: 通用资源锁2的锁定master ID号5。 */
        unsigned int  resource2lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁2的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id6  : 3;  /* bit[25-27]: 通用资源锁2的锁定master ID号6。 */
        unsigned int  resource2lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁2的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource2lock_id7  : 3;  /* bit[29-31]: 通用资源锁2的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE2_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE2_LOCK_resource2lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE2_UNLOCK_UNION
 结构说明  : RESOURCE2_UNLOCK 寄存器结构定义。地址偏移量:0x41C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource2unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁2的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁2的解锁master ID号0。 */
        unsigned int  resource2unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁2的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁2的解锁master ID号1。 */
        unsigned int  resource2unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁2的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id2  : 3;  /* bit[9-11] : 通用资源锁2的解锁master ID号2。 */
        unsigned int  resource2unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁2的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id3  : 3;  /* bit[13-15]: 通用资源锁2的解锁master ID号3。 */
        unsigned int  resource2unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁2的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id4  : 3;  /* bit[17-19]: 通用资源锁2的解锁master ID号4。 */
        unsigned int  resource2unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁2的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id5  : 3;  /* bit[21-23]: 通用资源锁2的解锁master ID号5。 */
        unsigned int  resource2unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁2的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id6  : 3;  /* bit[25-27]: 通用资源锁2的解锁master ID号6。 */
        unsigned int  resource2unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁2的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource2unlock_id7  : 3;  /* bit[29-31]: 通用资源锁2的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE2_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE2_UNLOCK_resource2unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE2_LOCK_ST_UNION
 结构说明  : RESOURCE2_LOCK_ST 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource2lock_st0    : 1;  /* bit[0-0]  : 通用资源锁2的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁2的锁定状态master ID号0。 */
        unsigned int  resource2lock_st1    : 1;  /* bit[4-4]  : 通用资源锁2的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁2的锁定状态master ID号1。 */
        unsigned int  resource2lock_st2    : 1;  /* bit[8-8]  : 通用资源锁2的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁2的锁定状态master ID号2。 */
        unsigned int  resource2lock_st3    : 1;  /* bit[12-12]: 通用资源锁2的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁2的锁定状态master ID号3。 */
        unsigned int  resource2lock_st4    : 1;  /* bit[16-16]: 通用资源锁2的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁2的锁定状态master ID号4。 */
        unsigned int  resource2lock_st5    : 1;  /* bit[20-20]: 通用资源锁2的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁2的锁定状态master ID号5。 */
        unsigned int  resource2lock_st6    : 1;  /* bit[24-24]: 通用资源锁2的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁2的锁定状态master ID号6。 */
        unsigned int  resource2lock_st7    : 1;  /* bit[28-28]: 通用资源锁2的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource2lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁2的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE2_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE2_LOCK_ST_resource2lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE3_LOCK_UNION
 结构说明  : RESOURCE3_LOCK 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource3lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁3的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id0  : 3;  /* bit[1-3]  : 通用资源锁3的锁定master ID号0。 */
        unsigned int  resource3lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁3的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id1  : 3;  /* bit[5-7]  : 通用资源锁3的锁定master ID号1。 */
        unsigned int  resource3lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁3的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id2  : 3;  /* bit[9-11] : 通用资源锁3的锁定master ID号2。 */
        unsigned int  resource3lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁3的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id3  : 3;  /* bit[13-15]: 通用资源锁3的锁定master ID号3。 */
        unsigned int  resource3lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁3的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id4  : 3;  /* bit[17-19]: 通用资源锁3的锁定master ID号4。 */
        unsigned int  resource3lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁3的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id5  : 3;  /* bit[21-23]: 通用资源锁3的锁定master ID号5。 */
        unsigned int  resource3lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁3的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id6  : 3;  /* bit[25-27]: 通用资源锁3的锁定master ID号6。 */
        unsigned int  resource3lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁3的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource3lock_id7  : 3;  /* bit[29-31]: 通用资源锁3的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE3_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE3_LOCK_resource3lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE3_UNLOCK_UNION
 结构说明  : RESOURCE3_UNLOCK 寄存器结构定义。地址偏移量:0x428，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource3unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁3的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁3的解锁master ID号0。 */
        unsigned int  resource3unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁3的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁3的解锁master ID号1。 */
        unsigned int  resource3unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁3的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id2  : 3;  /* bit[9-11] : 通用资源锁3的解锁master ID号2。 */
        unsigned int  resource3unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁3的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id3  : 3;  /* bit[13-15]: 通用资源锁3的解锁master ID号3。 */
        unsigned int  resource3unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁3的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id4  : 3;  /* bit[17-19]: 通用资源锁3的解锁master ID号4。 */
        unsigned int  resource3unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁3的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id5  : 3;  /* bit[21-23]: 通用资源锁3的解锁master ID号5。 */
        unsigned int  resource3unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁3的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id6  : 3;  /* bit[25-27]: 通用资源锁3的解锁master ID号6。 */
        unsigned int  resource3unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁3的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource3unlock_id7  : 3;  /* bit[29-31]: 通用资源锁3的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE3_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE3_UNLOCK_resource3unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE3_LOCK_ST_UNION
 结构说明  : RESOURCE3_LOCK_ST 寄存器结构定义。地址偏移量:0x42C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource3lock_st0    : 1;  /* bit[0-0]  : 通用资源锁3的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁3的锁定状态master ID号0。 */
        unsigned int  resource3lock_st1    : 1;  /* bit[4-4]  : 通用资源锁3的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁3的锁定状态master ID号1。 */
        unsigned int  resource3lock_st2    : 1;  /* bit[8-8]  : 通用资源锁3的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁3的锁定状态master ID号2。 */
        unsigned int  resource3lock_st3    : 1;  /* bit[12-12]: 通用资源锁3的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁3的锁定状态master ID号3。 */
        unsigned int  resource3lock_st4    : 1;  /* bit[16-16]: 通用资源锁3的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁3的锁定状态master ID号4。 */
        unsigned int  resource3lock_st5    : 1;  /* bit[20-20]: 通用资源锁3的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁3的锁定状态master ID号5。 */
        unsigned int  resource3lock_st6    : 1;  /* bit[24-24]: 通用资源锁3的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁3的锁定状态master ID号6。 */
        unsigned int  resource3lock_st7    : 1;  /* bit[28-28]: 通用资源锁3的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource3lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁3的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE3_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE3_LOCK_ST_resource3lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE4_LOCK_UNION
 结构说明  : RESOURCE4_LOCK 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource4lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁4的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id0  : 3;  /* bit[1-3]  : 通用资源锁4的锁定master ID号0。 */
        unsigned int  resource4lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁4的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id1  : 3;  /* bit[5-7]  : 通用资源锁4的锁定master ID号1。 */
        unsigned int  resource4lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁4的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id2  : 3;  /* bit[9-11] : 通用资源锁4的锁定master ID号2。 */
        unsigned int  resource4lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁4的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id3  : 3;  /* bit[13-15]: 通用资源锁4的锁定master ID号3。 */
        unsigned int  resource4lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁4的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id4  : 3;  /* bit[17-19]: 通用资源锁4的锁定master ID号4。 */
        unsigned int  resource4lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁4的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id5  : 3;  /* bit[21-23]: 通用资源锁4的锁定master ID号5。 */
        unsigned int  resource4lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁4的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id6  : 3;  /* bit[25-27]: 通用资源锁4的锁定master ID号6。 */
        unsigned int  resource4lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁4的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource4lock_id7  : 3;  /* bit[29-31]: 通用资源锁4的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE4_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE4_LOCK_resource4lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE4_UNLOCK_UNION
 结构说明  : RESOURCE4_UNLOCK 寄存器结构定义。地址偏移量:0x804，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource4unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁4的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁4的解锁master ID号0。 */
        unsigned int  resource4unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁4的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁4的解锁master ID号1。 */
        unsigned int  resource4unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁4的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id2  : 3;  /* bit[9-11] : 通用资源锁4的解锁master ID号2。 */
        unsigned int  resource4unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁4的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id3  : 3;  /* bit[13-15]: 通用资源锁4的解锁master ID号3。 */
        unsigned int  resource4unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁4的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id4  : 3;  /* bit[17-19]: 通用资源锁4的解锁master ID号4。 */
        unsigned int  resource4unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁4的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id5  : 3;  /* bit[21-23]: 通用资源锁4的解锁master ID号5。 */
        unsigned int  resource4unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁4的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id6  : 3;  /* bit[25-27]: 通用资源锁4的解锁master ID号6。 */
        unsigned int  resource4unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁4的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource4unlock_id7  : 3;  /* bit[29-31]: 通用资源锁4的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE4_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE4_UNLOCK_resource4unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE4_LOCK_ST_UNION
 结构说明  : RESOURCE4_LOCK_ST 寄存器结构定义。地址偏移量:0x808，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource4lock_st0    : 1;  /* bit[0-0]  : 通用资源锁4的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁4的锁定状态master ID号0。 */
        unsigned int  resource4lock_st1    : 1;  /* bit[4-4]  : 通用资源锁4的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁4的锁定状态master ID号1。 */
        unsigned int  resource4lock_st2    : 1;  /* bit[8-8]  : 通用资源锁4的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁4的锁定状态master ID号2。 */
        unsigned int  resource4lock_st3    : 1;  /* bit[12-12]: 通用资源锁4的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁4的锁定状态master ID号3。 */
        unsigned int  resource4lock_st4    : 1;  /* bit[16-16]: 通用资源锁4的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁4的锁定状态master ID号4。 */
        unsigned int  resource4lock_st5    : 1;  /* bit[20-20]: 通用资源锁4的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁4的锁定状态master ID号5。 */
        unsigned int  resource4lock_st6    : 1;  /* bit[24-24]: 通用资源锁4的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁4的锁定状态master ID号6。 */
        unsigned int  resource4lock_st7    : 1;  /* bit[28-28]: 通用资源锁4的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource4lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁4的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE4_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE4_LOCK_ST_resource4lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE5_LOCK_UNION
 结构说明  : RESOURCE5_LOCK 寄存器结构定义。地址偏移量:0x80C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource5lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁5的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id0  : 3;  /* bit[1-3]  : 通用资源锁5的锁定master ID号0。 */
        unsigned int  resource5lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁5的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id1  : 3;  /* bit[5-7]  : 通用资源锁5的锁定master ID号1。 */
        unsigned int  resource5lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁5的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id2  : 3;  /* bit[9-11] : 通用资源锁5的锁定master ID号2。 */
        unsigned int  resource5lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁5的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id3  : 3;  /* bit[13-15]: 通用资源锁5的锁定master ID号3。 */
        unsigned int  resource5lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁5的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id4  : 3;  /* bit[17-19]: 通用资源锁5的锁定master ID号4。 */
        unsigned int  resource5lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁5的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id5  : 3;  /* bit[21-23]: 通用资源锁5的锁定master ID号5。 */
        unsigned int  resource5lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁5的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id6  : 3;  /* bit[25-27]: 通用资源锁5的锁定master ID号6。 */
        unsigned int  resource5lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁5的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource5lock_id7  : 3;  /* bit[29-31]: 通用资源锁5的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE5_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE5_LOCK_resource5lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE5_UNLOCK_UNION
 结构说明  : RESOURCE5_UNLOCK 寄存器结构定义。地址偏移量:0x810，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource5unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁5的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁5的解锁master ID号0。 */
        unsigned int  resource5unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁5的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁5的解锁master ID号1。 */
        unsigned int  resource5unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁5的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id2  : 3;  /* bit[9-11] : 通用资源锁5的解锁master ID号2。 */
        unsigned int  resource5unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁5的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id3  : 3;  /* bit[13-15]: 通用资源锁5的解锁master ID号3。 */
        unsigned int  resource5unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁5的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id4  : 3;  /* bit[17-19]: 通用资源锁5的解锁master ID号4。 */
        unsigned int  resource5unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁5的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id5  : 3;  /* bit[21-23]: 通用资源锁5的解锁master ID号5。 */
        unsigned int  resource5unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁5的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id6  : 3;  /* bit[25-27]: 通用资源锁5的解锁master ID号6。 */
        unsigned int  resource5unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁5的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource5unlock_id7  : 3;  /* bit[29-31]: 通用资源锁5的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE5_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE5_UNLOCK_resource5unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE5_LOCK_ST_UNION
 结构说明  : RESOURCE5_LOCK_ST 寄存器结构定义。地址偏移量:0x814，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource5lock_st0    : 1;  /* bit[0-0]  : 通用资源锁5的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁5的锁定状态master ID号0。 */
        unsigned int  resource5lock_st1    : 1;  /* bit[4-4]  : 通用资源锁5的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁5的锁定状态master ID号1。 */
        unsigned int  resource5lock_st2    : 1;  /* bit[8-8]  : 通用资源锁5的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁5的锁定状态master ID号2。 */
        unsigned int  resource5lock_st3    : 1;  /* bit[12-12]: 通用资源锁5的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁5的锁定状态master ID号3。 */
        unsigned int  resource5lock_st4    : 1;  /* bit[16-16]: 通用资源锁5的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁5的锁定状态master ID号4。 */
        unsigned int  resource5lock_st5    : 1;  /* bit[20-20]: 通用资源锁5的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁5的锁定状态master ID号5。 */
        unsigned int  resource5lock_st6    : 1;  /* bit[24-24]: 通用资源锁5的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁5的锁定状态master ID号6。 */
        unsigned int  resource5lock_st7    : 1;  /* bit[28-28]: 通用资源锁5的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource5lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁5的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE5_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE5_LOCK_ST_resource5lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE6_LOCK_UNION
 结构说明  : RESOURCE6_LOCK 寄存器结构定义。地址偏移量:0x818，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource6lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁6的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id0  : 3;  /* bit[1-3]  : 通用资源锁6的锁定master ID号0。 */
        unsigned int  resource6lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁6的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id1  : 3;  /* bit[5-7]  : 通用资源锁6的锁定master ID号1。 */
        unsigned int  resource6lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁6的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id2  : 3;  /* bit[9-11] : 通用资源锁6的锁定master ID号2。 */
        unsigned int  resource6lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁6的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id3  : 3;  /* bit[13-15]: 通用资源锁6的锁定master ID号3。 */
        unsigned int  resource6lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁6的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id4  : 3;  /* bit[17-19]: 通用资源锁6的锁定master ID号4。 */
        unsigned int  resource6lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁6的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id5  : 3;  /* bit[21-23]: 通用资源锁6的锁定master ID号5。 */
        unsigned int  resource6lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁6的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id6  : 3;  /* bit[25-27]: 通用资源锁6的锁定master ID号6。 */
        unsigned int  resource6lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁6的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource6lock_id7  : 3;  /* bit[29-31]: 通用资源锁6的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE6_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE6_LOCK_resource6lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE6_UNLOCK_UNION
 结构说明  : RESOURCE6_UNLOCK 寄存器结构定义。地址偏移量:0x81C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource6unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁6的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁6的解锁master ID号0。 */
        unsigned int  resource6unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁6的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁6的解锁master ID号1。 */
        unsigned int  resource6unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁6的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id2  : 3;  /* bit[9-11] : 通用资源锁6的解锁master ID号2。 */
        unsigned int  resource6unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁6的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id3  : 3;  /* bit[13-15]: 通用资源锁6的解锁master ID号3。 */
        unsigned int  resource6unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁6的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id4  : 3;  /* bit[17-19]: 通用资源锁6的解锁master ID号4。 */
        unsigned int  resource6unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁6的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id5  : 3;  /* bit[21-23]: 通用资源锁6的解锁master ID号5。 */
        unsigned int  resource6unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁6的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id6  : 3;  /* bit[25-27]: 通用资源锁6的解锁master ID号6。 */
        unsigned int  resource6unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁6的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource6unlock_id7  : 3;  /* bit[29-31]: 通用资源锁6的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE6_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE6_UNLOCK_resource6unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE6_LOCK_ST_UNION
 结构说明  : RESOURCE6_LOCK_ST 寄存器结构定义。地址偏移量:0x820，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource6lock_st0    : 1;  /* bit[0-0]  : 通用资源锁6的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁6的锁定状态master ID号0。 */
        unsigned int  resource6lock_st1    : 1;  /* bit[4-4]  : 通用资源锁6的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁6的锁定状态master ID号1。 */
        unsigned int  resource6lock_st2    : 1;  /* bit[8-8]  : 通用资源锁6的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁6的锁定状态master ID号2。 */
        unsigned int  resource6lock_st3    : 1;  /* bit[12-12]: 通用资源锁6的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁6的锁定状态master ID号3。 */
        unsigned int  resource6lock_st4    : 1;  /* bit[16-16]: 通用资源锁6的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁6的锁定状态master ID号4。 */
        unsigned int  resource6lock_st5    : 1;  /* bit[20-20]: 通用资源锁6的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁6的锁定状态master ID号5。 */
        unsigned int  resource6lock_st6    : 1;  /* bit[24-24]: 通用资源锁6的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁6的锁定状态master ID号6。 */
        unsigned int  resource6lock_st7    : 1;  /* bit[28-28]: 通用资源锁6的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource6lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁6的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE6_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE6_LOCK_ST_resource6lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE7_LOCK_UNION
 结构说明  : RESOURCE7_LOCK 寄存器结构定义。地址偏移量:0x824，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁定寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource7lock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁7的锁定命令位0。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id0  : 3;  /* bit[1-3]  : 通用资源锁7的锁定master ID号0。 */
        unsigned int  resource7lock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁7的锁定命令位1。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id1  : 3;  /* bit[5-7]  : 通用资源锁7的锁定master ID号1。 */
        unsigned int  resource7lock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁7的锁定命令位2。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id2  : 3;  /* bit[9-11] : 通用资源锁7的锁定master ID号2。 */
        unsigned int  resource7lock_cmd3 : 1;  /* bit[12-12]: 通用资源锁7的锁定命令位3。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id3  : 3;  /* bit[13-15]: 通用资源锁7的锁定master ID号3。 */
        unsigned int  resource7lock_cmd4 : 1;  /* bit[16-16]: 通用资源锁7的锁定命令位4。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id4  : 3;  /* bit[17-19]: 通用资源锁7的锁定master ID号4。 */
        unsigned int  resource7lock_cmd5 : 1;  /* bit[20-20]: 通用资源锁7的锁定命令位5。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id5  : 3;  /* bit[21-23]: 通用资源锁7的锁定master ID号5。 */
        unsigned int  resource7lock_cmd6 : 1;  /* bit[24-24]: 通用资源锁7的锁定命令位6。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id6  : 3;  /* bit[25-27]: 通用资源锁7的锁定master ID号6。 */
        unsigned int  resource7lock_cmd7 : 1;  /* bit[28-28]: 通用资源锁7的锁定命令位7。
                                                              0：无效；
                                                              1：锁定。 */
        unsigned int  resource7lock_id7  : 3;  /* bit[29-31]: 通用资源锁7的锁定master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE7_LOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id0_START   (1)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id0_END     (3)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id1_START   (5)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id1_END     (7)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id2_START   (9)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id2_END     (11)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id3_START   (13)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id3_END     (15)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id4_START   (17)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id4_END     (19)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id5_START   (21)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id5_END     (23)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id6_START   (25)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id6_END     (27)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id7_START   (29)
#define SOC_PCTRL_RESOURCE7_LOCK_resource7lock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE7_UNLOCK_UNION
 结构说明  : RESOURCE7_UNLOCK 寄存器结构定义。地址偏移量:0x828，初值:0x00000000，宽度:32
 寄存器说明: 通用资源解锁寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource7unlock_cmd0 : 1;  /* bit[0-0]  : 通用资源锁7的解锁命令位0。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id0  : 3;  /* bit[1-3]  : 通用资源锁7的解锁master ID号0。 */
        unsigned int  resource7unlock_cmd1 : 1;  /* bit[4-4]  : 通用资源锁7的解锁命令位1。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id1  : 3;  /* bit[5-7]  : 通用资源锁7的解锁master ID号1。 */
        unsigned int  resource7unlock_cmd2 : 1;  /* bit[8-8]  : 通用资源锁7的解锁命令位2。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id2  : 3;  /* bit[9-11] : 通用资源锁7的解锁master ID号2。 */
        unsigned int  resource7unlock_cmd3 : 1;  /* bit[12-12]: 通用资源锁7的解锁命令位3。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id3  : 3;  /* bit[13-15]: 通用资源锁7的解锁master ID号3。 */
        unsigned int  resource7unlock_cmd4 : 1;  /* bit[16-16]: 通用资源锁7的解锁命令位4。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id4  : 3;  /* bit[17-19]: 通用资源锁7的解锁master ID号4。 */
        unsigned int  resource7unlock_cmd5 : 1;  /* bit[20-20]: 通用资源锁7的解锁命令位5。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id5  : 3;  /* bit[21-23]: 通用资源锁7的解锁master ID号5。 */
        unsigned int  resource7unlock_cmd6 : 1;  /* bit[24-24]: 通用资源锁7的解锁命令位6。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id6  : 3;  /* bit[25-27]: 通用资源锁7的解锁master ID号6。 */
        unsigned int  resource7unlock_cmd7 : 1;  /* bit[28-28]: 通用资源锁7的解锁命令位7。
                                                                0：无效；
                                                                1：锁定。 */
        unsigned int  resource7unlock_id7  : 3;  /* bit[29-31]: 通用资源锁7的解锁master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE7_UNLOCK_UNION;
#endif
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd0_START  (0)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd0_END    (0)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id0_START   (1)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id0_END     (3)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd1_START  (4)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd1_END    (4)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id1_START   (5)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id1_END     (7)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd2_START  (8)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd2_END    (8)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id2_START   (9)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id2_END     (11)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd3_START  (12)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd3_END    (12)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id3_START   (13)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id3_END     (15)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd4_START  (16)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd4_END    (16)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id4_START   (17)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id4_END     (19)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd5_START  (20)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd5_END    (20)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id5_START   (21)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id5_END     (23)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd6_START  (24)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd6_END    (24)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id6_START   (25)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id6_END     (27)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd7_START  (28)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_cmd7_END    (28)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id7_START   (29)
#define SOC_PCTRL_RESOURCE7_UNLOCK_resource7unlock_id7_END     (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_RESOURCE7_LOCK_ST_UNION
 结构说明  : RESOURCE7_LOCK_ST 寄存器结构定义。地址偏移量:0x82C，初值:0x00000000，宽度:32
 寄存器说明: 通用资源锁状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  resource7lock_st0    : 1;  /* bit[0-0]  : 通用资源锁7的锁定状态0。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id0 : 3;  /* bit[1-3]  : 通用资源锁7的锁定状态master ID号0。 */
        unsigned int  resource7lock_st1    : 1;  /* bit[4-4]  : 通用资源锁7的锁定状态1。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id1 : 3;  /* bit[5-7]  : 通用资源锁7的锁定状态master ID号1。 */
        unsigned int  resource7lock_st2    : 1;  /* bit[8-8]  : 通用资源锁7的锁定状态2。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id2 : 3;  /* bit[9-11] : 通用资源锁7的锁定状态master ID号2。 */
        unsigned int  resource7lock_st3    : 1;  /* bit[12-12]: 通用资源锁7的锁定状态3。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id3 : 3;  /* bit[13-15]: 通用资源锁7的锁定状态master ID号3。 */
        unsigned int  resource7lock_st4    : 1;  /* bit[16-16]: 通用资源锁7的锁定状态4。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id4 : 3;  /* bit[17-19]: 通用资源锁7的锁定状态master ID号4。 */
        unsigned int  resource7lock_st5    : 1;  /* bit[20-20]: 通用资源锁7的锁定状态5。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id5 : 3;  /* bit[21-23]: 通用资源锁7的锁定状态master ID号5。 */
        unsigned int  resource7lock_st6    : 1;  /* bit[24-24]: 通用资源锁7的锁定状态6。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id6 : 3;  /* bit[25-27]: 通用资源锁7的锁定状态master ID号6。 */
        unsigned int  resource7lock_st7    : 1;  /* bit[28-28]: 通用资源锁7的锁定状态7。
                                                                0：未锁定；
                                                                1：锁定。 */
        unsigned int  resource7lock_st_id7 : 3;  /* bit[29-31]: 通用资源锁7的锁定状态master ID号7。 */
    } reg;
} SOC_PCTRL_RESOURCE7_LOCK_ST_UNION;
#endif
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st0_START     (0)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st0_END       (0)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id0_START  (1)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id0_END    (3)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st1_START     (4)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st1_END       (4)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id1_START  (5)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id1_END    (7)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st2_START     (8)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st2_END       (8)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id2_START  (9)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id2_END    (11)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st3_START     (12)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st3_END       (12)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id3_START  (13)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id3_END    (15)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st4_START     (16)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st4_END       (16)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id4_START  (17)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id4_END    (19)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st5_START     (20)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st5_END       (20)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id5_START  (21)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id5_END    (23)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st6_START     (24)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st6_END       (24)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id6_START  (25)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id6_END    (27)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st7_START     (28)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st7_END       (28)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id7_START  (29)
#define SOC_PCTRL_RESOURCE7_LOCK_ST_resource7lock_st_id7_END    (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL5_UNION
 结构说明  : PERI_CTRL5 寄存器结构定义。地址偏移量:0xC00，初值:0x1E941C20，宽度:32
 寄存器说明: 通用外设控制寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpm3_mid       : 5;  /* bit[0-4]  : bit[4:0]:lpm3_mid default:00000 具体配置参考总线相关说明。 */
        unsigned int  iomcu_mid      : 5;  /* bit[5-9]  : bit[9:5]:iomcu_mid default:00001 具体配置参考总线相关说明。 */
        unsigned int  noc_emmc01_mid : 5;  /* bit[10-14]: bit[14:10]:noc_emmc01_mid default:00111 具体配置参考总线相关说明。 */
        unsigned int  sd3_mid        : 5;  /* bit[15-19]: bit[19:15]:sd3_mid default:01000 具体配置参考总线相关说明。 */
        unsigned int  sdio0_mid      : 5;  /* bit[20-24]: bit[24:20]:sdio0_mid default:01001 具体配置参考总线相关说明。 */
        unsigned int  dmac_mid       : 5;  /* bit[25-29]: bit[29:25]:dmac_mid default:01111 具体配置参考总线相关说明。 */
        unsigned int  reserved       : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL5_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL5_lpm3_mid_START        (0)
#define SOC_PCTRL_PERI_CTRL5_lpm3_mid_END          (4)
#define SOC_PCTRL_PERI_CTRL5_iomcu_mid_START       (5)
#define SOC_PCTRL_PERI_CTRL5_iomcu_mid_END         (9)
#define SOC_PCTRL_PERI_CTRL5_noc_emmc01_mid_START  (10)
#define SOC_PCTRL_PERI_CTRL5_noc_emmc01_mid_END    (14)
#define SOC_PCTRL_PERI_CTRL5_sd3_mid_START         (15)
#define SOC_PCTRL_PERI_CTRL5_sd3_mid_END           (19)
#define SOC_PCTRL_PERI_CTRL5_sdio0_mid_START       (20)
#define SOC_PCTRL_PERI_CTRL5_sdio0_mid_END         (24)
#define SOC_PCTRL_PERI_CTRL5_dmac_mid_START        (25)
#define SOC_PCTRL_PERI_CTRL5_dmac_mid_END          (29)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL6_UNION
 结构说明  : PERI_CTRL6 寄存器结构定义。地址偏移量:0xC04，初值:0x1C36B16A，宽度:32
 寄存器说明: 通用外设控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  secp_mid         : 5;  /* bit[0-4]  : bit[4:0]:secp_mid default:01010 具体配置参考总线相关说明。 */
        unsigned int  secs_mid         : 5;  /* bit[5-9]  : bit[9:5]:secs_mid default:01011 具体配置参考总线相关说明。 */
        unsigned int  socp_mid         : 5;  /* bit[10-14]: bit[14:10]:socp_mid default:01100 具体配置参考总线相关说明。 */
        unsigned int  usb3otg_mid      : 5;  /* bit[15-19]: bit[19:15]:usb3otg_mid default:01101 具体配置参考总线相关说明。 */
        unsigned int  sc_perf_stat_mid : 5;  /* bit[20-24]: bit[24:20]:sc_perf_stat_mid default:00011 具体配置参考总线相关说明。 */
        unsigned int  cssys_mid        : 5;  /* bit[25-29]: bit[29:25]:cssys_mid default:01110 具体配置参考总线相关说明。 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL6_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL6_secp_mid_START          (0)
#define SOC_PCTRL_PERI_CTRL6_secp_mid_END            (4)
#define SOC_PCTRL_PERI_CTRL6_secs_mid_START          (5)
#define SOC_PCTRL_PERI_CTRL6_secs_mid_END            (9)
#define SOC_PCTRL_PERI_CTRL6_socp_mid_START          (10)
#define SOC_PCTRL_PERI_CTRL6_socp_mid_END            (14)
#define SOC_PCTRL_PERI_CTRL6_usb3otg_mid_START       (15)
#define SOC_PCTRL_PERI_CTRL6_usb3otg_mid_END         (19)
#define SOC_PCTRL_PERI_CTRL6_sc_perf_stat_mid_START  (20)
#define SOC_PCTRL_PERI_CTRL6_sc_perf_stat_mid_END    (24)
#define SOC_PCTRL_PERI_CTRL6_cssys_mid_START         (25)
#define SOC_PCTRL_PERI_CTRL6_cssys_mid_END           (29)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL7_UNION
 结构说明  : PERI_CTRL7 寄存器结构定义。地址偏移量:0xC08，初值:0x2111E000，宽度:32
 寄存器说明: 通用外设控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_arqos  : 5;  /* bit[0-4]  : bit[4]:保留 default:0
                                                        bit[3:0]:modem arqos default:0000 具体配置参考总线相关说明。 */
        unsigned int  modem_awqos  : 5;  /* bit[5-9]  : bit[9]:保留 default:0
                                                        bit[8:5]:modem awqos default:0000 具体配置参考总线相关说明。 */
        unsigned int  modemcpu_mid : 5;  /* bit[10-14]: bit[14:10]:modem cpu mid default:11000 具体配置参考总线相关说明。 */
        unsigned int  reserved_0   : 5;  /* bit[15-19]: 保留。 */
        unsigned int  a53_mid1     : 5;  /* bit[20-24]: bit[24:20]:a53 mid1 default:10001 具体配置参考总线相关说明。 */
        unsigned int  a57_mid0     : 5;  /* bit[25-29]: bit[29:25]:a57 mid0 default:10000 具体配置参考总线相关说明。 */
        unsigned int  reserved_1   : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL7_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL7_modem_arqos_START   (0)
#define SOC_PCTRL_PERI_CTRL7_modem_arqos_END     (4)
#define SOC_PCTRL_PERI_CTRL7_modem_awqos_START   (5)
#define SOC_PCTRL_PERI_CTRL7_modem_awqos_END     (9)
#define SOC_PCTRL_PERI_CTRL7_modemcpu_mid_START  (10)
#define SOC_PCTRL_PERI_CTRL7_modemcpu_mid_END    (14)
#define SOC_PCTRL_PERI_CTRL7_a53_mid1_START      (20)
#define SOC_PCTRL_PERI_CTRL7_a53_mid1_END        (24)
#define SOC_PCTRL_PERI_CTRL7_a57_mid0_START      (25)
#define SOC_PCTRL_PERI_CTRL7_a57_mid0_END        (29)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL8_UNION
 结构说明  : PERI_CTRL8 寄存器结构定义。地址偏移量:0xC0C，初值:0x063E737B，宽度:32
 寄存器说明: 通用外设控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_armid0 : 5;  /* bit[0-4]  : bit[4:0]:g3d armid0 default:11011 具体配置参考总线相关说明。 */
        unsigned int  g3d_awmid0 : 5;  /* bit[5-9]  : bit[9:5]:g3d awmid0 default:11011 具体配置参考总线相关说明。 */
        unsigned int  g3d_armid1 : 5;  /* bit[10-14]: bit[14:10]:g3d armid1 default:11100 具体配置参考总线相关说明。 */
        unsigned int  g3d_awmid1 : 5;  /* bit[15-19]: bit[19:15]:g3d awmid1 default:11100 具体配置参考总线相关说明。 */
        unsigned int  g3d_arqos  : 4;  /* bit[20-23]: bit[23:20]:g3d arqos default:0011 具体配置参考总线相关说明。 */
        unsigned int  reserved_0 : 1;  /* bit[24]   : 保留。 */
        unsigned int  g3d_awqos  : 4;  /* bit[25-28]: bit[28:25]:g3d awqos default:0011 具体配置参考总线相关说明。 */
        unsigned int  reserved_1 : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL8_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL8_g3d_armid0_START  (0)
#define SOC_PCTRL_PERI_CTRL8_g3d_armid0_END    (4)
#define SOC_PCTRL_PERI_CTRL8_g3d_awmid0_START  (5)
#define SOC_PCTRL_PERI_CTRL8_g3d_awmid0_END    (9)
#define SOC_PCTRL_PERI_CTRL8_g3d_armid1_START  (10)
#define SOC_PCTRL_PERI_CTRL8_g3d_armid1_END    (14)
#define SOC_PCTRL_PERI_CTRL8_g3d_awmid1_START  (15)
#define SOC_PCTRL_PERI_CTRL8_g3d_awmid1_END    (19)
#define SOC_PCTRL_PERI_CTRL8_g3d_arqos_START   (20)
#define SOC_PCTRL_PERI_CTRL8_g3d_arqos_END     (23)
#define SOC_PCTRL_PERI_CTRL8_g3d_awqos_START   (25)
#define SOC_PCTRL_PERI_CTRL8_g3d_awqos_END     (28)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL9_UNION
 结构说明  : PERI_CTRL9 寄存器结构定义。地址偏移量:0xC10，初值:0x0B39525F，宽度:32
 寄存器说明: 通用外设控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_mid           : 5;  /* bit[0-4]  : bit[4:0]:asp mid default:11111 具体配置参考总线相关说明。 */
        unsigned int  reserved          : 5;  /* bit[5-9]  : 保留。 */
        unsigned int  venc_mid          : 5;  /* bit[10-14]: bit[14:10]:venc mid default:10100 具体配置参考总线相关说明。 */
        unsigned int  a7_toviviobus_mid : 5;  /* bit[15-19]: bit[19:15]:a7_toviviobus_mid default:10010 具体配置参考总线相关说明。 */
        unsigned int  a7_cfg_mid        : 5;  /* bit[20-24]: bit[24:20]:a7_cfg_mid default:10011 具体配置参考总线相关说明。 */
        unsigned int  djtag_mid         : 5;  /* bit[25-29]: bit[29:25]:djtag mid default:00101 具体配置参考总线相关说明。 */
        unsigned int  dss0_mid          : 1;  /* bit[30]   : bit[30]:dss0 mid default:0 具体配置参考总线相关说明。 */
        unsigned int  dss1_mid          : 1;  /* bit[31]   : bit[31]:dss1 mid default:0 具体配置参考总线相关说明。 */
    } reg;
} SOC_PCTRL_PERI_CTRL9_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL9_asp_mid_START            (0)
#define SOC_PCTRL_PERI_CTRL9_asp_mid_END              (4)
#define SOC_PCTRL_PERI_CTRL9_venc_mid_START           (10)
#define SOC_PCTRL_PERI_CTRL9_venc_mid_END             (14)
#define SOC_PCTRL_PERI_CTRL9_a7_toviviobus_mid_START  (15)
#define SOC_PCTRL_PERI_CTRL9_a7_toviviobus_mid_END    (19)
#define SOC_PCTRL_PERI_CTRL9_a7_cfg_mid_START         (20)
#define SOC_PCTRL_PERI_CTRL9_a7_cfg_mid_END           (24)
#define SOC_PCTRL_PERI_CTRL9_djtag_mid_START          (25)
#define SOC_PCTRL_PERI_CTRL9_djtag_mid_END            (29)
#define SOC_PCTRL_PERI_CTRL9_dss0_mid_START           (30)
#define SOC_PCTRL_PERI_CTRL9_dss0_mid_END             (30)
#define SOC_PCTRL_PERI_CTRL9_dss1_mid_START           (31)
#define SOC_PCTRL_PERI_CTRL9_dss1_mid_END             (31)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL10_UNION
 结构说明  : PERI_CTRL10 寄存器结构定义。地址偏移量:0xC14，初值:0xCD52063F，宽度:32
 寄存器说明: 通用外设控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrc0_mid        : 1;  /* bit[0]    : bit[0]:ddrc0_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc1_mid        : 1;  /* bit[1]    : bit[1]:ddrc1_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc2_mid        : 1;  /* bit[2]    : bit[2]:ddrc2_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc3_mid        : 1;  /* bit[3]    : bit[3]:ddrc3_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc4_mid        : 1;  /* bit[4]    : bit[4]:ddrc4_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc5_mid        : 1;  /* bit[5]    : bit[5]:ddrc5_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc6_mid        : 1;  /* bit[6]    : bit[6]:ddrc6_mid default:0 具体配置参考总线相关说明。 */
        unsigned int  ddrc7_mid        : 1;  /* bit[7]    : bit[7]:ddrc7_mid default:0 具体配置参考总线相关说明。 */
        unsigned int  ddrc8_mid        : 1;  /* bit[8]    : bit[8]:ddrc8_mid default:0 具体配置参考总线相关说明。 */
        unsigned int  ddrc9_mid        : 1;  /* bit[9]    : bit[9]:ddrc9_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  ddrc10_mid       : 1;  /* bit[10]   : bit[10]:ddrc10_mid default:1 具体配置参考总线相关说明。 */
        unsigned int  reserved_0       : 4;  /* bit[11-14]: 保留。 */
        unsigned int  sdio1_mid        : 5;  /* bit[15-19]: bit[19:15]:sdio1_mid default:00100 具体配置参考总线相关说明。 */
        unsigned int  sc_vdec_mid      : 5;  /* bit[20-24]: bit[24:20]:sc_vdec_mid default:10101 具体配置参考总线相关说明。 */
        unsigned int  sc_iomcu_dma_mid : 5;  /* bit[25-29]: bit[29:25]:sc_iomcu_dma_mid default:00110 具体配置参考总线相关说明。 */
        unsigned int  reserved_1       : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL10_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL10_ddrc0_mid_START         (0)
#define SOC_PCTRL_PERI_CTRL10_ddrc0_mid_END           (0)
#define SOC_PCTRL_PERI_CTRL10_ddrc1_mid_START         (1)
#define SOC_PCTRL_PERI_CTRL10_ddrc1_mid_END           (1)
#define SOC_PCTRL_PERI_CTRL10_ddrc2_mid_START         (2)
#define SOC_PCTRL_PERI_CTRL10_ddrc2_mid_END           (2)
#define SOC_PCTRL_PERI_CTRL10_ddrc3_mid_START         (3)
#define SOC_PCTRL_PERI_CTRL10_ddrc3_mid_END           (3)
#define SOC_PCTRL_PERI_CTRL10_ddrc4_mid_START         (4)
#define SOC_PCTRL_PERI_CTRL10_ddrc4_mid_END           (4)
#define SOC_PCTRL_PERI_CTRL10_ddrc5_mid_START         (5)
#define SOC_PCTRL_PERI_CTRL10_ddrc5_mid_END           (5)
#define SOC_PCTRL_PERI_CTRL10_ddrc6_mid_START         (6)
#define SOC_PCTRL_PERI_CTRL10_ddrc6_mid_END           (6)
#define SOC_PCTRL_PERI_CTRL10_ddrc7_mid_START         (7)
#define SOC_PCTRL_PERI_CTRL10_ddrc7_mid_END           (7)
#define SOC_PCTRL_PERI_CTRL10_ddrc8_mid_START         (8)
#define SOC_PCTRL_PERI_CTRL10_ddrc8_mid_END           (8)
#define SOC_PCTRL_PERI_CTRL10_ddrc9_mid_START         (9)
#define SOC_PCTRL_PERI_CTRL10_ddrc9_mid_END           (9)
#define SOC_PCTRL_PERI_CTRL10_ddrc10_mid_START        (10)
#define SOC_PCTRL_PERI_CTRL10_ddrc10_mid_END          (10)
#define SOC_PCTRL_PERI_CTRL10_sdio1_mid_START         (15)
#define SOC_PCTRL_PERI_CTRL10_sdio1_mid_END           (19)
#define SOC_PCTRL_PERI_CTRL10_sc_vdec_mid_START       (20)
#define SOC_PCTRL_PERI_CTRL10_sc_vdec_mid_END         (24)
#define SOC_PCTRL_PERI_CTRL10_sc_iomcu_dma_mid_START  (25)
#define SOC_PCTRL_PERI_CTRL10_sc_iomcu_dma_mid_END    (29)


/*****************************************************************************
 结构名    : SOC_PCTRL_PERI_CTRL11_UNION
 结构说明  : PERI_CTRL11 寄存器结构定义。地址偏移量:0xC18，初值:0x00000000，宽度:32
 寄存器说明: 通用外设控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_ctrl11_cmd : 16; /* bit[0-15] : mcpu boot addr 
                                                           MODEM启动地址配置寄存器。 */
        unsigned int  reserved        : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PCTRL_PERI_CTRL11_UNION;
#endif
#define SOC_PCTRL_PERI_CTRL11_peri_ctrl11_cmd_START  (0)
#define SOC_PCTRL_PERI_CTRL11_peri_ctrl11_cmd_END    (15)






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

#endif /* end of soc_pctrl_interface.h */
