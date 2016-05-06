/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_om_log.c
*
*   作    者 :  h00135900
*
*   描    述 :  C核打印输出处理函数
*
*   修改记录 :  2013年03月04日  v1.00  h00135900  创建
*************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
/*lint -save -e537 -e451 -e830 -e539 -e661*/



#ifdef __OS_VXWORKS__
#include <vxWorks.h>
#include <logLib.h>
#include <errnoLib.h>
#include <stdio.h>
#else 
#include "sre_shell.h"
#include "sre_err.h"
#include "sre_libc.h"
#endif
#include "securec.h" 

#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_malloc.h"
#include "osl_irq.h"
#include "sre_libc.h"

#include <stdarg.h>
#include <string.h>
#include <bsp_uart.h>
#include "bsp_om_api.h"
#include "bsp_om.h"
#include "bsp_socp.h"
#include "bsp_bbp.h"
#include "bsp_om_log.h"
#include "bsp_hardtimer.h"
#include "bsp_rtc.h"
/*lint -restore*/
#define    THIS_MODU_ID        BSP_MODU_LOG

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

bsp_log_swt_cfg_s  g_mod_peint_level_info[BSP_MODU_MAX]    =
{
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}
};

u32 bsp_log_level_set(bsp_log_level_e log_level);

char log_buf_temp[BSP_LOG_BUF_LEN] = {0};
bsp_log_buf_ctrl_s g_log_buf_ctrl;
bool log_init_flag = false;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_get
*
* 功能描述  : 查询模块当前设置的打印级别
*
* 输入参数  : mod_id:被查询模块ID
*
* 输出参数  : 无
*
* 返 回 值  : 打印级别
*****************************************************************************/

u32 bsp_log_module_cfg_get(bsp_module_e mod_id)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    return g_mod_peint_level_info[mod_id].print_level;
}

/*****************************************************************************
* 函 数 名  : bsp_mod_level_set
*
* 功能描述  : 设置单个模块的打印级别
*
* 输入参数  : mod_id:模块ID
*                         print_level: 打印级别
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/

u32 bsp_mod_level_set(bsp_module_e  mod_id ,u32 print_level)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    if(print_level > BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    g_mod_peint_level_info[mod_id].print_level = print_level;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : bsp_log_level_set
*
* 功能描述  : 设置所有模块的打印级别
*
* 输入参数  : print_level: 打印级别
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/
u32 bsp_log_level_set(bsp_log_level_e log_level)
{
    u32 mod_id = 0;

    if(log_level >BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    for(mod_id = 0; mod_id < BSP_MODU_MAX; mod_id++)
    {
        g_mod_peint_level_info[mod_id].print_level = log_level;
    }

    return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : bsp_log_level_reset
*
* 功能描述  : 将所有模块的打印级别设置为默认值
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/

void bsp_log_level_reset(void)
{
    u32 i;

    for(i = 0; i < BSP_MODU_MAX;i++)
    {
        g_mod_peint_level_info[i].print_level= BSP_LOG_LEVEL_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : bsp_trace
*
* 功能描述  : 底软打印输出处理接口
*
* 输入参数  :  mod_id: 输出模块
*                           print_level: 打印级别
*                           fmt :打印输入参数
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void bsp_trace(bsp_log_level_e log_level, bsp_module_e mod_id,char *fmt,...)
{
    s32 _args[6];
    s32 i;
    u32 time_cur =0;
    int sprint_len = 0;
    int fmt_len = 0;    
    struct rtc_time tm = {0};    
    va_list arglist;
    char  buf_trans_temp[BSP_TRACE_BUF_LEN_MAX+1] = {0};
#if defined(__OS_VXWORKS__)
    char* ptr_log_msg = NULL;
    u32 buf_back_len = 0;
#endif

    if(mod_id >= BSP_MODU_MAX )
    {
        return ;
    }

    if(g_mod_peint_level_info[mod_id].print_level > log_level )
    {
        return ;
    }
#if defined( __OS_RTOSCK__)

    /*lint -save -e530 -e586*/
    va_start(arglist, fmt); 
    for(i = 0; i < 6; i++)
    {
        _args[i] = va_arg(arglist, s32);
    }
    va_end(arglist);
    /*lint -restore*/    
    (void)mdrv_rtc_read_time(&tm);   
    time_cur = bsp_get_slice_value();
    sprint_len = snprintf_s(buf_trans_temp,(BSP_TRACE_BUF_LEN_MAX+1),BSP_TRACE_BUF_LEN_MAX, "[0x%08x(%.4d-%.2d-%.2d %.2d:%.2d:%.2d)]",\
        time_cur,(tm.tm_year), (tm.tm_mon),tm.tm_mday,(tm.tm_hour),tm.tm_min,tm.tm_sec);/* [false alarm]:fortify  */
    if(sprint_len > BSP_TRACE_BUF_LEN_MAX)
    {
        return ;
    }
    va_start(arglist, fmt);/* [false alarm]:fortify  */
    for(i = 0; i < 6; i++)
    {
        _args[i] = va_arg(arglist, s32);/* [false alarm]:fortify  */
    }
    va_end(arglist);/* [false alarm]:fortify  */
     /*lint -save -e830 -e539 -e661*/
    fmt_len = snprintf_s(buf_trans_temp+sprint_len,(BSP_TRACE_BUF_LEN_MAX+1),(u32)(BSP_TRACE_BUF_LEN_MAX - sprint_len),fmt,_args[0],_args[1],\
        _args[2],_args[3],_args[4],_args[5]);/* [false alarm]:fortify  */
    if(fmt_len > BSP_TRACE_BUF_LEN_MAX)
    {
        return ;
    }
    fmt_len = fmt_len +sprint_len;
    if(fmt_len > BSP_TRACE_BUF_LEN_MAX)
    {
        return;
    }
	buf_trans_temp[fmt_len +1] = '\0';/* [false alarm]:fortify  */
    (void)SRE_Printf("%s",buf_trans_temp);
    /*lint -restore*/    
    
#elif defined(__OS_VXWORKS__)
    if(false == log_init_flag)
    {
        g_log_buf_ctrl.buf_offset= 0;
        (void)memset_s(log_buf_temp,BSP_LOG_BUF_LEN,0,BSP_LOG_BUF_LEN);
        g_log_buf_ctrl.write_ptr = log_buf_temp;
        log_init_flag = true;
    }
    time_cur = bsp_get_slice_value();
    sprint_len = snprintf_s(buf_trans_temp,(BSP_TRACE_BUF_LEN_MAX+1),BSP_TRACE_BUF_LEN_MAX,"[%08x(dec:%d)]",time_cur,time_cur);
    if(sprint_len > BSP_TRACE_BUF_LEN_MAX)
    {
        return ;
    }
    va_start(arglist, fmt);
    for(i = 0; i < 6; i++)
    {
        _args[i] = va_arg(arglist, s32);
    }
    va_end(arglist);/* [false alarm]:fortify  */
    fmt_len = snprintf_s(buf_trans_temp+sprint_len,(BSP_TRACE_BUF_LEN_MAX+1),(u32)(BSP_TRACE_BUF_LEN_MAX - sprint_len),fmt,_args[0],_args[1],\
        _args[2],_args[3],_args[4],_args[5]);/* [false alarm]:fortify  */
    if(sprint_len > BSP_TRACE_BUF_LEN_MAX)
    {
        return ;
    }
    fmt_len = fmt_len +sprint_len;
	buf_trans_temp[fmt_len +1] = '\0';
    fmt_len +=1;
    flag = intLock();
     /* 如果当前处于锁中断或者是中断上下文*/
    if(VXWORKS_INT_LOCK_FLAG&flag)
    {
        printksync((char*)buf_trans_temp,0,0,0,0,0,0);
    }
    else
    {
        if(NULL != g_log_buf_ctrl.write_ptr)
        {
            ptr_log_msg = g_log_buf_ctrl.write_ptr;
            if((g_log_buf_ctrl.buf_offset + fmt_len)>= BSP_LOG_BUF_LEN)
            {
                buf_back_len = BSP_LOG_BUF_LEN-g_log_buf_ctrl.buf_offset;
                (void)memcpy_s(g_log_buf_ctrl.write_ptr, buf_back_len,buf_trans_temp, buf_back_len);
                g_log_buf_ctrl.write_ptr = log_buf_temp;
                (void)memcpy_s(g_log_buf_ctrl.write_ptr, (u32)(fmt_len - buf_back_len),buf_trans_temp+buf_back_len, (u32)(fmt_len - buf_back_len));
                buf_back_len = fmt_len - buf_back_len;
                g_log_buf_ctrl.buf_offset= buf_back_len;
                g_log_buf_ctrl.write_ptr +=buf_back_len;
    }
            else
            {
                (void)memcpy_s(g_log_buf_ctrl.write_ptr,fmt_len,buf_trans_temp,fmt_len);
                g_log_buf_ctrl.write_ptr +=fmt_len;
                g_log_buf_ctrl.buf_offset += fmt_len; 
            }
    
            logMsg(ptr_log_msg, 0,0,0,0,0,0); 
        }
        else
        {
            logMsg((char*)buf_trans_temp, 0,0,0,0,0,0);
        }
    }
    intUnlock(flag);
#endif
    return ;
}


void bsp_print2dmsg(char *fmt, ...)
{
    va_list vaList;
    s32     len    = 0;
    char    buf[256];
    
    va_start(vaList, fmt);/*lint !e530*/
    len = vsnprintf_s(buf, 256, 256, fmt, vaList); /* [false alarm]:屏蔽Fortify错误 */
    va_end(vaList);

    dmesg_write(buf, (u32)len);

    return;
}

#ifdef ENABLE_BUILD_OM
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_set
*
* 功能描述  : HSO设置底软打印级别处理函数
*
* 输入参数  : log_swt_stru:各个模块的打印级别值
*                         data_len:      参数log_swt_stru的长度
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 成功;其他 失败
*****************************************************************************/

u32 bsp_log_module_cfg_set(bsp_log_swt_cfg_s *log_swt_stru ,u32 data_len)
{
    u32 mod_num = 0;
    u32 i;

    if((NULL == log_swt_stru )||( 0 == data_len)||((data_len % sizeof(bsp_log_swt_cfg_s) != 0)))
    {
       bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  data_len = %d\n",data_len);
       return BSP_ERR_LOG_INVALID_PARAM;
    }

    mod_num = data_len / sizeof(bsp_log_swt_cfg_s);

    if(mod_num > BSP_MODU_MAX )
    {
        bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  mod_num = %d\n",mod_num);
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    for(i = 0; i < mod_num; i++)
    {
        if(log_swt_stru[i].print_level <= BSP_LOG_LEVEL_MAX)
        {
            g_mod_peint_level_info[i].print_level = log_swt_stru[i].print_level;
        }
        else
        {
            bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set   log_swt_stru[i].print_level = %d\n",log_swt_stru[i].print_level);
            return BSP_ERR_LOG_INVALID_LEVEL ;
        }

    }

    return BSP_OK;
}




#endif


