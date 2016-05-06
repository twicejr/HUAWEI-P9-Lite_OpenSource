/******************************************************************************
  文 件 名   : mdrv_thermal.h
  版 本 号   : 初稿
  作    者   : 徐经翠x00221564
  生成日期   : 2015年10月26日
  功能描述   : 用于定义A\C核共用的定义体
  修改历史   :
  1.日    期   :  徐经翠x00221564
    作    者   : 2015年10月26日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MDRV_THERMAL_H__
#define __MDRV_THERMAL_H__

int mdrv_thermal_up(unsigned int  core_num);
int mdrv_thermal_down(unsigned int core_num);

#endif
