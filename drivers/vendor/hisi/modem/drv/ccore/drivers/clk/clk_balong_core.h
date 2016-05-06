/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  clk_balong_core.h
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  clk_balong_core.c使用的头文件
*
*   修改记录 : 2014年9月15日  v1.00  h00277960  创建
**************************************************************************/

/*lint --e{762} */

#ifndef CLK_BALONG_CORE_H
#define CLK_BALONG_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "bsp_clk.h"
#include <of.h>

#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include "securec.h"

#define  clk_printf(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))

//#define  CLK_EN_INFO_PRINT
#ifdef   CLK_EN_INFO_PRINT
#define  clk_printf_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))
#else
#define  clk_printf_info(fmt, ...)    
#endif

typedef void (*drv_of_clk_init_cb_t)(struct device_node *);

enum clk_op_type{
    CLK_OP_TYPE_ENAB = 0x454E4142,  /* clk_enable              */
    CLK_OP_TYPE_DISA = 0x44495341,  /* clk_disable             */
    CLK_OP_TYPE_SETR = 0x53455452,  /* clk_set_rate            */
    CLK_OP_TYPE_SETP = 0x53455450,  /* clk_set_parent          */
    CLK_OP_TYPE_ENAU = 0x454E4155,  /* clk_enable_auto_gating  */
    CLK_OP_TYPE_DIAU = 0x44494155   /* clk_disable_auto_gating */
};

#define LOG_CLK_NAME_LEN   8  /* 记录时钟名字的前8个字符 */

struct clk_op_entry{
    OSL_TASK_ID       task_id;                         /* 操作者任务ID */
	char              clk_name[LOG_CLK_NAME_LEN];      /* 被操作的时钟名字 */
	unsigned int      op_type;                         /* 操作类型 */
	unsigned int      enable_count_before_op;          /* 操作前的应用计数 */
};

#define NOTIFY_STOP_MASK	0x8000		

static inline char *clk_alloc_copy(const char *src_str)
{
	unsigned int len;
	char         *dst_str = NULL;

	if (!src_str)
	{
		return NULL;
	}

	len = strlen(src_str) + 1;
	dst_str = osl_malloc(len);
	if (dst_str)
	{
		memcpy_s(dst_str, len, src_str, len);
	}
	
	return dst_str;
}





#ifndef BIT
#define BIT(nr)			(1UL << (nr))
#endif



/* 时钟flag */
#define CLK_SET_RATE_GATE	     BIT(0) /* 改变时钟频率时应该被关断 */
#define CLK_SET_PARENT_GATE	     BIT(1) /* 设置父时钟时应该被关断 */
#define CLK_SET_RATE_PARENT	     BIT(2) /* 频率改变时，向父时钟蔓延一级 */
#define CLK_IGNORE_UNUSED	     BIT(3) /* 不使用也不关断 */
#define CLK_IS_ROOT		         BIT(4) /* 根时钟，没有父时钟 */
#define CLK_IS_BASIC		     BIT(5) /* 基础时钟，没有to_clk_xxx()操作 */
#define CLK_GET_RATE_NOCACHE	 BIT(6) /* 不使用缓存的时钟频率 */



struct clk_div_table {
	unsigned int	val_to_reg; /* 应该写到寄存器中的值，N+1分频时为div_val-1 */  
	unsigned int	div_val;    /* 分频值 */
};



#define CLK_MUX_INDEX_ONE		BIT(0) /* 以1索引，例如0,1,2,3... */
#define CLK_MUX_INDEX_BIT		BIT(1) /* 以2的幂索引，例如2^0,2^1,2^2... */
#define CLK_MUX_HIWORD_MASK		BIT(2)


/***********************************************************************
*功能:注册时钟
*参数:设置字符串，硬件指定时钟
*返回:时钟结构体指针
************************************************************************/
struct clk *drv_clk_register(const char * dev, struct clk_hw *hw);


/***********************************************************************
*功能:获取时钟名字
*参数:时钟结构体指针
*返回:时钟名字
************************************************************************/
const char *__drv_clk_get_name(struct clk *clk);

/***********************************************************************
*功能:获取父时钟个数
*参数:时钟结构体指针
*返回:父时钟个数
************************************************************************/
u8 __drv_clk_get_num_parents(struct clk *clk);

/***********************************************************************
*功能:获取父时钟
*参数:时钟结构体指针
*返回:父时钟结构体指针
************************************************************************/
struct clk *__drv_clk_get_parent(struct clk *clk);

/***********************************************************************
*功能:获取时钟标志
*参数:时钟结构体指针
*返回:时钟标志
************************************************************************/
unsigned long __drv_clk_get_flags(struct clk *clk);


/***********************************************************************
*功能:round时钟频率
*参数:时钟结构体指针，时钟频率
*返回:round后的时钟频率
************************************************************************/
unsigned long __drv_clk_round_rate(struct clk *clk, unsigned long rate);

/***********************************************************************
*功能:通过of接口获取父时钟名字
*参数:设备节点指针，父时钟索引
*返回:父时钟字符串
************************************************************************/
const char *drv_of_clk_get_parent_name(struct device_node *np, int index);

/***********************************************************************
*功能:通过of接口初始化时钟
*参数:of_device_id结构体指针
*返回:无
************************************************************************/
void drv_of_clk_init(const struct of_device_id *matches);

/***********************************************************************
*功能:将时钟添加到链表中
*参数:时钟查找结构体指针
*返回:无
************************************************************************/
void drv_clkdev_add(struct clk_lookup *cl);

/***********************************************************************
*功能:打开时钟
*参数:时钟结构体指针
*返回:0，成功；其他值，失败
************************************************************************/
int __drv_clk_enable(struct clk *ptr_clk);

/***********************************************************************
*功能:关闭时钟
*参数:时钟结构体指针
*返回:无
************************************************************************/
void __drv_clk_disable(struct clk *ptr_clk);



#ifdef __cplusplus
}
#endif


#endif
