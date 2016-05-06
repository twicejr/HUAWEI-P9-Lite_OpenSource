/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mtcmos_driver_inner.h
  版 本 号   : 初稿
  作    者   : 王振伟 176398
  生成日期   : 2012年12月22日
  最近修改   :
  功能描述   : mtcmos_driver.c 的内部头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月22日
    作    者   : 王振伟 176398
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <regulator_info.h>

#ifndef __MTCMOS_DRIVER_INNER_H__
#define __MTCMOS_DRIVER_INNER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*mtcmos 对应的寄存器*/
#if defined(CHIP_BB_HI6210)
/*B050 Modify*/
#else
#define CALC_REG_OFFSET_BASE_ADDR 0

#define SC_MTCMOS_STAT0 SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_MTCMOS_STAT1 SOC_AO_SCTRL_SC_MTCMOS_STAT1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_EN0 SOC_AO_SCTRL_SC_PW_EN0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_EN1 SOC_AO_SCTRL_SC_PW_EN1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_DIS0 SOC_AO_SCTRL_SC_PW_DIS0_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#define SC_PW_DIS1 SOC_AO_SCTRL_SC_PW_DIS1_ADDR(CALC_REG_OFFSET_BASE_ADDR)
#endif


#define MTCMOS_ON_STATUS 1
/*计算对应的msk值*/
#define CALC_REG_MSK(bit_start, bit_end) \
    (((0x1 << (bit_end - bit_start + 1)) - 1) << bit_start)

/*mtcmos 稳定时间*/
#define TCXO_FREQ 19200000 //19.2Mhz
#define MTCMOS_PWON_TIME 10 //10us
#define MTCMOS_PWON_TIME_COUNTER (TCXO_FREQ * MTCMOS_PWON_TIME / 1000000)
#define MTCMOS_PWON_STATE_CHECK_COUNTER 200

/*mtcmos平台起始ID值*/
#define PLATFORM_MTCMOS_BEGIN_ID MTCMOS_ID_BEGIN

#define lock(x) mutex_lock(x)
#define unlock(x)  mutex_unlock(x)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
#if defined(CHIP_BB_HI6210)
/*B050 Modify*/
enum mcmos_vcc_enum {
/*MTCMOS Block 1*/
    VCC_ENUM_BEGIN = 0,
    VCC_BLOCK1_START = VCC_ENUM_BEGIN,
    VCC_PERI = VCC_BLOCK1_START,
    VCC_G3D,
    VCC_CODECISP,
    VCC_MCPU,
    VCC_BBPHARQMEM,
    VCC_HIFI,
    VCC_ACPUCLUSTER,
    VCC_BLOCK1_END,
/*MTCMOS in acpu_sc*/
    VCC_ACPU1 = VCC_BLOCK1_END,
    VCC_ACPU2,
    VCC_ACPU3,
    VCC_ENUM_END,
};
#else
enum mcmos_vcc_enum {
/*MTCMOS Block 1*/
    VCC_ENUM_BEGIN = 0,
    VCC_BLOCK1_START = VCC_ENUM_BEGIN,
    VCC_G2D = VCC_BLOCK1_START,
    VCC_EDC0,
    VCC_EDC1,
    VCC_ISP,
    VCC_ENC,
    VCC_DEC,
    VCC_HIFI,
    VCC_VPP,
    VCC_DSPBBE,
    VCC_GBBP1,
    VCC_GBBP2,
    VCC_LTEBBP,
    VCC_BBPCOMM2,
    VCC_WTDBBP1,
    VCC_WTDBBP2,
    VCC_BLOCK1_END,
/*MTCMOS Block 2*/
    VCC_BLOCK2_START = VCC_BLOCK1_END,
    VCC_ACPU1 = VCC_BLOCK2_START,
    VCC_ACPU2,
    VCC_ACPU3,
    VCC_CM3MEM,
    VCC_MCPU,
    VCC_BLOCK2_END,
    VCC_ENUM_END = VCC_BLOCK2_END,
};
#endif

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*mtcmos电源稳定计数器寄存器数据结构*/
struct mtcmos_pwup_time_reg_stru {
    unsigned int pwup_time_reg;  //mtcmos电源稳定计数器寄存器
    unsigned int pwup_time_mask; //mtcmos电源稳定计数器寄存器屏蔽位
    unsigned int pwup_time_start_bit;//mtcmos电源稳定计数器寄存器起始位
};
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

/*****************************************************************************
 函 数 名  : mtcoms_power_is_on
 功能描述  : 检查当前mtcoms是否是打开状态
 输入参数  : int id //mtcmos id
 输出参数  : 无
 返 回 值  : int    //0:成功  其它值:失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月25日
    作    者   : 王振伟 176398
    修改内容   : 新生成函数

*****************************************************************************/
extern int mtcmos_power_is_on( int id );

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mtcmos_driver_inner.h */
