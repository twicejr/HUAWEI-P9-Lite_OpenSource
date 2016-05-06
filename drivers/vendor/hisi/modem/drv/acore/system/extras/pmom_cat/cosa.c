/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cosa.c
  版 本 号   : 初稿
  作    者   : s00207770
  生成日期   : 2015年3月21日
  最近修改   :
  功能描述   : cosa PM信息解析
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月21日
    作    者   : s00207770
    修改内容   : 创建文件

******************************************************************************/
#include <stdio.h>
#include "pmom_cat.h"
#include "cosa.h"

/*****************************************************************************
 函 数 名  : pm_cosa_main_parse
 功能描述  : COSA PM信息解析总入口
 输入参数  : char *in_buf
             unsigned int len
 输出参数  : char *out_buf
             unsigned int *out_ptr
 返 回 值  : int PMOM_OK
                 PMOM_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月21日
    作    者   : s00207770
    修改内容   : 新生成函数

*****************************************************************************/
int pm_cosa_main_parse( char *in_buf, unsigned int len, char *out_buf, unsigned int *out_ptr )
{
    PM_LOG_COSA_PAM_ENUM_UINT32         enModuleType;
    unsigned int                        ulData_len = 0;
    PM_LOG_RTC_TIMER                   *stInfo;

    if ( 0 == in_buf || 0 == out_buf || 0 == out_ptr)
    {
        return PMOM_ERR;
    }

    enModuleType    = *((PM_LOG_COSA_PAM_ENUM_UINT32 *)in_buf);

    /* 移除Main type内容 */
    in_buf  += sizeof(PM_LOG_COSA_PAM_ENUM_UINT32);
    len     -= sizeof(PM_LOG_COSA_PAM_ENUM_UINT32);

    switch(enModuleType)
    {
        case PM_LOG_COSA_PAM_TIMER:
            stInfo  = (PM_LOG_RTC_TIMER *)in_buf;

            ulData_len = snprintf(&out_buf[*out_ptr], PMOM_PARSE_STR_BUFSIZ,
                "Pid is %d, Timer Id is %x\r\n", stInfo->ulPid, stInfo->ulTimerId);

            *out_ptr = *out_ptr + ulData_len;
            break;

        default:
            break;
    }

    return PMOM_OK;
}
