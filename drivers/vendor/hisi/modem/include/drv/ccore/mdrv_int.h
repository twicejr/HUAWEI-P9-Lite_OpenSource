#ifndef __MDRV_CCORE_INT_H__
#define __MDRV_CCORE_INT_H__
#ifdef __cplusplus
extern "C"
{
#endif


#include "mdrv_public.h"
#include "mdrv_int_comm.h"

enum nmi_int_dst_core
{
	NMI_INT_TO_ACPU,
	NMI_INT_TO_CCPU,
	NMI_INT_TO_MCPU,
	NMI_INT_TO_TLPHY,
	NMI_INT_TO_XPHY,
	NMI_INT_CORE_NUM
};

    /*****************************************************************************
     *  函 数 名  : mdrv_int_is_inside_context
     *  功能描述  :  C CORE 检测是否为中断上下文
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :  0:      非中断上下文
     *              非零:    中断上下文
     *
     ******************************************************************************/
    unsigned int mdrv_int_is_inside_context(void);

    /*****************************************************************************
     *  函 数 名  : mdrv_int_send_nmi
     *  功能描述  :  发送一个NMI中断。(代码中是打桩请确认是否需要)
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :
     *
     ******************************************************************************/
    void mdrv_int_send_nmi(enum nmi_int_dst_core core_type, unsigned int status);

    /*****************************************************************************
     *  函 数 名  : mdrv_int_register_exithook
     *  功能描述  : 注册系统中断退出钩子函数
     *  输入参数  : pFUNCPTR p_Func 钩子函数
     *
     *  输出参数  : 无
     *  返 回 值  :
     *
     ******************************************************************************/
    void mdrv_int_register_exithook(FUNCPTR_1 p_Func);

    /*****************************************************************************
     *  函 数 名  : mdrv_int_unregister_exithook
     *  功能描述  :  注销系统中断退出钩子函数
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :
     *
     ******************************************************************************/
    void mdrv_int_unregister_exithook(void);

    /*****************************************************************************
     *  函 数 名  : mdrv_int_unregister_exithook
     *  功能描述  :  注册系统中断进入钩子函数
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :
     *
     ******************************************************************************/
    void mdrv_int_register_enterhook(FUNCPTR_1 p_Func);

    /*****************************************************************************
     *  函 数 名  : mdrv_int_unregister_exithook
     *  功能描述  :  注销系统中断进入钩子函数
     *  输入参数  :
     *
     *  输出参数  : 无
     *  返 回 值  :
     *
     ******************************************************************************/
    void mdrv_int_unregister_enterhook(void);

#ifdef __cplusplus
}
#endif

#endif

