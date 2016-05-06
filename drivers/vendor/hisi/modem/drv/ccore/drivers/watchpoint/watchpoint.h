/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  watchpoint.h
*
*   作    者 :  z67193
*
*   描    述 :  临终遗言功能头文件
*
*   修改记录 :  2012年04月14日  v1.00  z67193  创建
*************************************************************************/
#ifndef	__WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "osl_types.h"
#include "osl_spinlock.h"
#include "bsp_om.h"
#include "bsp_wp.h"

enum
{
    WATCHPOINT_UNALLOC = 0,
    WATCHPOINT_ALLOCED = 1,
};

typedef struct
{
    u32         alloc;
    wp_cfg_t    cfg;
}wp_info_t;

typedef struct
{
    wp_info_t * wp_info;
    u32         wp_cnt;
    bool        init_flag;
    spinlock_t  lock;
    u32         wp_hit_cnt;
}wp_ctrl_t;

typedef struct
{
    u32     dscr;
    u32     wvr_reg[16];
    u32     wcr_reg[16];
}wp_reg_back_t;

#define wp_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_WATCHPOINT, "[watchpoint]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

/*lint -save -e762 */
s32 bsp_wp_register(wp_cfg_t * cfg);
s32 bsp_wp_unregister(s32 wp_id);
s32 bsp_wp_enable(s32 wp_id);
s32 bsp_wp_disable(s32 wp_id);
/*lint -restore +e762*/
void wp_debug(void);
void wp_show(void);

#endif //__WATCHPOINT_H__

