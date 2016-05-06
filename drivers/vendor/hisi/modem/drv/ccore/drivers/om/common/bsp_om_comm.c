/*************************************************************************
*   版权所有(C) 1987-2009, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_om_comm.c
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言功能
*
*   修改记录 :  2013年1月11日  v1.00  z67193  创建
*************************************************************************/
/*lint -save -e537 -e451*/
#ifdef __OS_VXWORKS_
#include <stdio.h>
#include <logLib.h>
#else 
#include "sre_libc.h"
#include "sre_shell.h"
#endif

#include <stdarg.h>
#include "osl_types.h"
#include "drv_comm.h"
#include "bsp_memmap.h"
#include "bsp_om_api.h"
#include "bsp_hardtimer.h"
#include <bsp_om.h>
/*lint -restore*/
#define OM_TIMER_STAMP_BASE HI_TIMER_10_REGBASE_ADDR		/*timer10*/

/*lint -save -e18*/
u32 om_timer_get(void)
{
	return bsp_get_slice_value();
}
/*lint -restore +e18*/
u32 om_timer_tick_get(void)
{
    u32 omTimerValue;
    /*lint -save -e958*/
	u64 omTick;

	omTimerValue = bsp_get_slice_value();
	omTick=((unsigned long long)omTimerValue*100)>>(15);
    /*lint -restore*/
	return (UINT32)omTick;
}

/*lint -save -e586*/
void bsp_om_debug( u32 level, char *fmt,...)
{
        /*lint -save -e830*/
        va_list arglist;/*lint !e40 !e522*/
        /*lint -restore +e830*/
        s32 _args[6];
        u32 i;
        /*lint -save -e530*/
        va_start(arglist, fmt);
        /*lint -restore +e530*/
        for(i = 0; i < 6; i++)
        {
            _args[i] = va_arg(arglist, s32);
        }
        va_end(arglist);
        #ifdef __OS_VXWORKS__
        logMsg((char*)fmt, _args[0], _args[1],_args[2],_args[3],_args[4],_args[5]);
        #else 
        (void)SRE_Printf(fmt, _args[0], _args[1],_args[2],_args[3],_args[4],_args[5]);
        #endif

        return;
}
/*lint -restore*/

