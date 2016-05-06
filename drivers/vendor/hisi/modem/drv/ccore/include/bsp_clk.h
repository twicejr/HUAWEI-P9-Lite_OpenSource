/*************************************************************************
*   版权所有(C) 2010-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  bsp_clk.h
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  给其他驱动模块使用的头文件
*               clk模块给其他驱动及上层提供的接口一致，放在drv_clk.h中
*
*   修改记录 :
*
*************************************************************************/
#ifndef BSP_CLK_H
#define BSP_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "osl_types.h"
#include "osl_list.h"


#if defined(__OS_RTOSCK__)

struct clk_hw;

struct clk {
	const char		        *name;
	const struct clk_ops	*ops;
	struct clk_hw		    *hw;
	struct clk		        *parent;
	const char		        **parent_names;
	struct clk		        **parents;
	u8			            num_parents;
	u8			            new_parent_index;
	unsigned long		    rate;
	unsigned long		    new_rate;
	unsigned long		    flags;
	struct hlist_head	    children;
	struct hlist_node	    child_node;
	u32                     enable_count;
	struct clk		        *new_parent;
	struct clk		        *new_child;
	unsigned char           is_virtual_clk;      /* 是否为虚拟时钟 */
    unsigned char           aux_flag;
	unsigned char           leaf_flag; /* 叶子时钟，即最末端时钟，一般是gate clk */
};



struct clk_ops {
	int		        (*enable)(struct clk_hw *hw);
	void	        (*disable)(struct clk_hw *hw);
	int		        (*is_enabled)(struct clk_hw *hw);
	unsigned long	(*recalc_rate)(struct clk_hw *hw, unsigned long parent_rate);
	long		    (*round_rate)(struct clk_hw *hw, unsigned long, unsigned long *);
	int		        (*set_parent)(struct clk_hw *hw, u8 index);
	u8		        (*get_parent)(struct clk_hw *hw);
	int		        (*set_rate)(struct clk_hw *hw, unsigned long,unsigned long);

	int		        (*check_divreg)(struct clk_hw *hw);
	void  *  (*get_reg)(struct clk_hw *hw);
	int		        (*enable_auto_gating)(struct clk_hw *hw);
	int		        (*disable_auto_gating)(struct clk_hw *hw);
};

/**
 * struct clk_init_data - holds init data that's common to all clocks and is
 * shared between the clock provider and the common clock framework.
 *
 * @name: clock name
 * @ops: operations this clock supports
 * @parent_names: array of string names for all possible parents
 * @num_parents: number of possible parents
 * @flags: framework-level hints and quirks
 */
struct clk_init_data {
	const char		        *name;
	const struct clk_ops	*ops;
	const char		        **parent_names;
	u8			            num_parents;
	unsigned long		    flags;
};

/**
 * struct clk_hw - handle for traversing from a struct clk to its corresponding
 * hardware-specific structure.  struct clk_hw should be declared within struct
 * clk_foo and then referenced by the struct clk instance that uses struct
 * clk_foo's clk_ops
 *
 * @clk: pointer to the struct clk instance that points back to this struct
 * clk_hw instance
 *
 * @init: pointer to struct clk_init_data that contains the init data shared
 * with the common clock framework.
 */
struct clk_hw {
	struct clk                 *clk;
	const struct clk_init_data *init;
	unsigned char              isvirtual;
	unsigned char              aux_flag;
	unsigned char              leaf_flag;
};

/*
 * DOC: Basic clock implementations common to many platforms
 *
 * Each basic clock hardware type is comprised of a structure describing the
 * clock hardware, implementations of the relevant callbacks in struct clk_ops,
 * unique flags for that hardware type, a registration function and an
 * alternative macro for static initialization
 */

struct clk_lookup {
	struct list_head	node;
	const char		    *dev_id;
	const char		    *con_id;
	unsigned int        clk_no; /* 时钟编号，依添加顺序确定 */
	struct clk		    *clk;
};

#ifdef CONFIG_BALONG_CCLK  /* 编译实际操作函数，非桩函数 */

/***********************************************************************
*功能:获取时钟
*参数:dev:NULL,  id:该时钟注册时的名字
*返回:时钟结构体指针
************************************************************************/
struct clk *drv_clk_get(const char * dev, const char *id);
#define clk_get(dev, id)  drv_clk_get(dev, id)

/***********************************************************************
*功能:打开时钟
*参数:时钟结构体指针
*返回:成功为0，失败非0
************************************************************************/
int drv_clk_enable(struct clk *clk);
#define clk_enable(clk)  drv_clk_enable(clk)


/***********************************************************************
*功能:关闭时钟
*参数:时钟结构体指针
*返回:无
************************************************************************/
void drv_clk_disable(struct clk *clk);
#define clk_disable(clk) drv_clk_disable(clk)

/***********************************************************************
*功能:查看时钟是否是打开的
*参数:时钟结构体指针
*返回:1，时钟是打开的；0，时钟是关闭的
************************************************************************/
int drv_clk_is_enabled(struct clk *clk);
#define clk_is_enabled(clk) drv_clk_is_enabled(clk)

/***********************************************************************
*功能:获取时钟频率
*参数:时钟结构体指针
*返回:时钟频率
************************************************************************/
unsigned long drv_clk_get_rate(struct clk *clk);
#define clk_get_rate(clk) drv_clk_get_rate(clk)


/***********************************************************************
*功能:round时钟频率
*参数:时钟结构体指针，给定的频率
*返回:round后的时钟频率
************************************************************************/
long drv_clk_round_rate(struct clk *clk, unsigned long rate);
#define clk_round_rate(clk, rate) drv_clk_round_rate(clk, rate)

/***********************************************************************
*功能:设置时钟频率
*参数:时钟结构体指针，给定的频率值
*返回:成功为0，失败非0
************************************************************************/
int drv_clk_set_rate(struct clk *clk, unsigned long rate);
#define clk_set_rate(clk, rate) drv_clk_set_rate(clk, rate)

/***********************************************************************
*功能:设置时钟父级
*参数:时钟结构体指针，父级时钟结构体指针
*返回:成功为0，失败非0
************************************************************************/
int drv_clk_set_parent(struct clk *clk, struct clk *parent);
#define clk_set_parent(clk, parent) drv_clk_set_parent(clk, parent)

/***********************************************************************
*功能:获取时钟父级
*参数:时钟结构体指针
*返回:父级时钟结构体指针
************************************************************************/
struct clk *drv_clk_get_parent(struct clk *clk);
#define clk_get_parent(clk) drv_clk_get_parent(clk)


/***********************************************************************
*功能:打开时钟的自动门控
*参数:时钟结构体指针
*返回:0，成功；其他值，失败
************************************************************************/
int drv_clk_enable_auto_gating(struct clk *clk);
#define clk_enable_auto_gating(clk) drv_clk_enable_auto_gating(clk)

/***********************************************************************
*功能:关闭时钟的自动门控
*参数:时钟结构体指针
*返回:0，成功；其他值，失败
************************************************************************/
int drv_clk_disable_auto_gating(struct clk *clk);
#define clk_disable_auto_gating(clk) drv_clk_disable_auto_gating(clk)


/***********************************************************************
*功能:CLK模块初始化
*参数:无
*返回:void
************************************************************************/
void bsp_clk_init(void);

/***********************************************************************
*功能:初始化某些时钟，这些时钟在C核控制打开或关闭，但还被其他核的IP使用
*参数:无
*返回:void
************************************************************************/
void bsp_remote_clk_init(void);



#else  /* 以下是打桩函数 */
static inline struct clk *drv_clk_get(const char * dev, const char *id){return NULL;}
#define clk_get(dev, id)  drv_clk_get(dev, id)

static inline int drv_clk_enable(struct clk *clk){return 0;}
#define clk_enable(clk) drv_clk_enable(clk)

static inline void drv_clk_disable(struct clk *clk){return ;}
#define clk_disable(clk) drv_clk_disable(clk)

static inline int drv_clk_is_enabled(struct clk *clk){return true;}
#define clk_is_enabled(clk) drv_clk_is_enabled(clk)

static inline unsigned long drv_clk_get_rate(struct clk *clk){return 0;}
#define clk_get_rate(clk) drv_clk_get_rate(clk)

static inline long drv_clk_round_rate(struct clk *clk, unsigned long rate){return 0;}
#define clk_round_rate(clk, rate) drv_clk_round_rate(clk, rate)

static inline int drv_clk_set_rate(struct clk *clk, unsigned long rate){return 0;}
#define clk_set_rate(clk, rate) drv_clk_set_rate(clk, rate)

static inline int drv_clk_set_parent(struct clk *clk, struct clk *parent){return 0;}
#define clk_set_parent(clk, parent) drv_clk_set_parent(clk, parent)

static inline struct clk *drv_clk_get_parent(struct clk *clk){return NULL;}
#define clk_get_parent(clk) drv_clk_get_parent(clk)

static inline int drv_clk_enable_auto_gating(struct clk *clk){return 0;}
#define clk_enable_auto_gating(clk) drv_clk_enable_auto_gating(clk)

static inline int drv_clk_disable_auto_gating(struct clk *clk){return 0;}
#define clk_disable_auto_gating(clk) drv_clk_disable_auto_gating(clk)
static inline void bsp_clk_init(void){return ;}
static inline void bsp_remote_clk_init(void){return ;}


#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
