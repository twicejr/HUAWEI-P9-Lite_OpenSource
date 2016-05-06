/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  clk_balong_core.c
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  clk框架核心
*
*   修改记录 : 2014年9月15日  v1.00  h00277960  创建
**************************************************************************/
 
/*lint --e{530,525,628,666,801,830} */
 
#include <clk_balong_core.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>

static spinlock_t clk_spinlock;
static osl_sem_id clk_mutex;
static unsigned int g_clk_cnt = 0; /* 添加到链表中的时钟计数 */

LIST_HEAD(balong_clocks);  /* 所有时钟都会添加到此链表中 */


HLIST_HEAD(clk_balong_root_list);
HLIST_HEAD(clk_balong_orphan_list);

/* 局部函数声明 */
static int _drv_clk_register(const char * dev, struct clk_hw *hw, struct clk *clk);
static int __drv_clk_init(const char * dev, struct clk *clk);
static int __drv_clk_speculate_rates(struct clk *clk, unsigned long parent_rate);
static u8 drv_clk_fetch_parent_index(struct clk *clk, struct clk *parent);
static void __drv_clk_reparent(struct clk *clk, struct clk *new_parent);
static struct clk *__drv_clk_init_parent(struct clk *clk);
static int __drv_clk_disable_auto_gating(struct clk *ptr_clk);
static int __drv_clk_enable_auto_gating(struct clk *ptr_clk);
static void drv_clk_change_rate(struct clk *clk);
static int __drv_clk_set_parent(struct clk *clk, struct clk *parent, u8 p_index);
static void drv_clk_reparent(struct clk *clk, struct clk *new_parent);
static struct clk *drv_clk_calc_new_rates(struct clk *clk, unsigned long rate);
static void drv_clk_calc_subtree(struct clk *clk, unsigned long new_rate);
static void __drv_clk_recalc_rates(struct clk *clk);
//static int __drv_clk_enable(struct clk *ptr_clk);
//static void __drv_clk_disable(struct clk *ptr_clk);
static struct clk *__drv_clk_lookup(const char *name);
static struct clk *__drv_clk_lookup_subtree(const char *name, struct clk *ptr_clk);
static bool __drv_clk_is_enabled(struct clk *clk);
static unsigned long __drv_clk_get_rate(struct clk *clk);
static struct clk *drv_clk_get_sys(const char *dev_id, const char *con_id);
static struct clk_lookup *drv_clk_find(const char *dev_id, const char *con_id);
static int drv_clk_strcmp(const char *cs, const char *ct);
static unsigned long drv_clk_enable_lock(void);
static inline void __drv_clk_pm_log(struct clk *clk, enum clk_op_type  op_type);
static void drv_clk_enable_unlock(unsigned long flags);


/* 函数实现 */
static int _drv_clk_register(const char * dev, struct clk_hw *hw, struct clk *clk)
{
	int i, ret;

	clk->name = clk_alloc_copy(hw->init->name);
	if (!clk->name) 
	{
		clk_printf("%s: could not allocate clk->name\n", __func__);
		ret = -ENOMEM;
		goto fail_name;
	}
	clk->ops = hw->init->ops;
	clk->hw = hw;
	clk->flags = hw->init->flags;
	clk->num_parents = hw->init->num_parents;
	hw->clk = clk;

	if (clk->num_parents)  /* 父时钟个数非0 */
	{
		clk->parent_names = osl_malloc((sizeof(char*) * clk->num_parents));
		if (clk->parent_names)
		{
		    (void)memset_s(clk->parent_names, sizeof(char*) * clk->num_parents, 0, sizeof(char*) * clk->num_parents);
		}

		if (!clk->parent_names) 
		{
			clk_printf("%s: could not allocate clk->parent_names\n", __func__);
			ret = -ENOMEM;
			goto fail_parent_names;
		}
	}
	else
	{
	    clk->parent_names = NULL;
	}


	/* 处理每个父时钟的名字 */
	for (i = 0; i < clk->num_parents; i++) 
	{
		clk->parent_names[i] = clk_alloc_copy(hw->init->parent_names[i]);
		if (!clk->parent_names[i]) 
		{
			clk_printf("%s: could not copy parent_names\n", __func__);
			ret = -ENOMEM;
			goto fail_parent_names_copy;
		}
	}

	ret = __drv_clk_init(dev, clk);
	if (!ret)
		return 0;

fail_parent_names_copy:
	while (--i >= 0)
		osl_free((void *)clk->parent_names[i]);
	osl_free((void *)clk->parent_names);
fail_parent_names:
	osl_free((void *)clk->name);
fail_name:
	return ret;
}

/*lint -save -e10 -e160 -e26 -e40 -e516 -e613 -e438 */
static int __drv_check_ops(struct clk *clk)
{
    
	/* 要求ops齐全 */
	if (clk->ops->set_rate &&
			!(clk->ops->round_rate && clk->ops->recalc_rate)) 
	{
		clk_printf("%s: %s must implement .round_rate & .recalc_rate\n",
				__func__, clk->name);
		return (-EINVAL);
	}

	if (clk->ops->set_parent && !clk->ops->get_parent) 
	{
		clk_printf("%s: %s must implement .get_parent & .set_parent\n",
				__func__, clk->name);
		return (-EINVAL);
	}

    return 0;
}

static void __drv_init_parents(struct clk *clk)
{
    int i = 0;

    /* 此时钟有父时钟 */
	if (clk->num_parents >= 1 && !clk->parents) 
	{
		clk->parents = osl_malloc((sizeof(struct clk*) * clk->num_parents));
		if (clk->parents)
		{
		    (void)memset_s(clk->parents, sizeof(struct clk*) * clk->num_parents, 0, sizeof(struct clk*) * clk->num_parents);
		}

        /* 查找其各父时钟 */
		if (clk->parents)
		{
			for (i = 0; i < clk->num_parents; i++)
			{
				clk->parents[i] = __drv_clk_lookup(clk->parent_names[i]);
			}
		}
	}

	clk->parent = __drv_clk_init_parent(clk);
}
/*lint -restore +e10 +e160 +e26 +e40 +e516 +e613 +e438 */


/*****************************************************************************
* 函 数 名  :  __drv_clk_init
*
* 功能描述  :  初始化时钟
*
* 输入参数  :  dev:设备
               clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  0，操作成功；其他值，操作失败
*
*****************************************************************************/
/*lint -save -e10 -e160 -e26 -e40 -e516 -e613 -e438 */
static int __drv_clk_init(const char * dev, struct clk *clk)
{
	int i, ret = 0;
	struct clk *orphan;
	struct hlist_node *tmp2;

	if (!clk)
		return -EINVAL;

	osl_sem_down(&clk_mutex);

	/* 如果时钟已被初始化 */
	if (__drv_clk_lookup(clk->name)) 
	{
		clk_printf("%s: clk %s already initialized\n",
				__func__, clk->name);
		ret = -EEXIST;
		goto out;
	}

    if (__drv_check_ops(clk))
    {
		clk_printf("clk %s check ops err\n", clk->name);
		ret = -EINVAL;
		goto out;
    }

    __drv_init_parents(clk);
	
	if (clk->parent)
	{
	    //__asm__ __volatile__ ("b .");
		hlist_add_head(&clk->child_node, &clk->parent->children);
	}
	else if (clk->flags & CLK_IS_ROOT)
	{
	    //__asm__ __volatile__ ("b .");
		hlist_add_head(&clk->child_node, &clk_balong_root_list);
	}
	else
	{
		hlist_add_head(&clk->child_node, &clk_balong_orphan_list);
	}

	//clk_printf("##############---return ------\n");
	//return 0;

    /* 初始化时钟频率 */
	if (clk->ops->recalc_rate)
	{
		clk->rate = clk->ops->recalc_rate(clk->hw, __drv_clk_get_rate(clk->parent));
	}
	else if (clk->parent)
	{
		clk->rate = clk->parent->rate;
	}
	else
	{
		clk->rate = 0;
	}


	hlist_for_each_entry_safe(orphan, tmp2, &clk_balong_orphan_list, child_node) /*lint !e144*/
	{
		if (orphan->ops->get_parent) 
		{
			i = orphan->ops->get_parent(orphan->hw);
			if (!drv_clk_strcmp(clk->name, orphan->parent_names[i]))
			{
				__drv_clk_reparent(orphan, clk);
			}
			continue;
		}

		for (i = 0; i < orphan->num_parents; i++)
			if (!drv_clk_strcmp(clk->name, orphan->parent_names[i])) 
			{
				__drv_clk_reparent(orphan, clk);
				break;
			}
	 }

out:
	osl_sem_up(&clk_mutex);

	return ret;
}

/*****************************************************************************
* 函 数 名  :  __drv_clk_speculate_rates
*
* 功能描述  :  初始化父时钟
*
* 输入参数  :  clk:时钟子树的首个时钟
               parent_rate:父时钟的未来的频率
               
* 输出参数  :  无
*
* 返 回 值  :  0，操作成功；其他值，操作失败
*
*****************************************************************************/
static int __drv_clk_speculate_rates(struct clk *clk, unsigned long parent_rate)
{
	struct clk *child;
	unsigned long new_rate = 0;
	int ret = 0;

    clk_printf_info("clk name = %s\n", clk->name);

	if (clk->ops->recalc_rate)
	{
		new_rate = clk->ops->recalc_rate(clk->hw, parent_rate);
	}
	else
	{
		new_rate = parent_rate;
	}


	/*lint -save -e10 -e160 -e26 -e40 -e516 -e530 -e666 -e413 */
	hlist_for_each_entry(child, &clk->children, child_node) /*lint !e144*/
	{
	    clk_printf_info("clk name = %s\n", child->name);
		
		ret = __drv_clk_speculate_rates(child, new_rate);
		if (ret & NOTIFY_STOP_MASK)
			break;
	}
	/*lint -restore +e10 +e160 +e26 +e40 +e516 +e530 +e666 +e413 */

	return ret;
}

static u8 drv_clk_fetch_parent_index(struct clk *clk, struct clk *parent)
{
	u8 i;

	if (!clk->parents)
	{
		clk->parents = osl_malloc((sizeof(struct clk*) * clk->num_parents));
        if (clk->parents)
    	{
			(void)memset_s(clk->parents, sizeof(struct clk*) * clk->num_parents, 0, sizeof(struct clk*) * clk->num_parents);
    	}
	}

    /* 查找父时钟索引 */
	for (i = 0; i < clk->num_parents; i++) 
	{
		if (clk->parents && clk->parents[i] == parent)
		{
			break;
		}
		else if (!drv_clk_strcmp(clk->parent_names[i], parent->name)) /* 名字一样 */
		{
			if (clk->parents)
			{
				clk->parents[i] = __drv_clk_lookup(parent->name);
			}
			break;
		}
	}

	return i;
}

static void __drv_clk_reparent(struct clk *clk, struct clk *new_parent)
{
	drv_clk_reparent(clk, new_parent);

	__drv_clk_recalc_rates(clk);
}

/*****************************************************************************
* 函 数 名  :  __drv_clk_init_parent
*
* 功能描述  :  初始化父时钟
*
* 输入参数  :  clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  父时钟
*
*****************************************************************************/
static struct clk *__drv_clk_init_parent(struct clk *clk)
{
	struct clk *ret = NULL;
	u8 idx;

    /* 父时钟个数为0 */
	if (!clk->num_parents)
		goto out;

	if (clk->num_parents == 1) {
		if ((!clk->parent)||( (unsigned long) (clk->parent)) < (unsigned long)0xffff)
			ret = clk->parent = __drv_clk_lookup(clk->parent_names[0]);
		ret = clk->parent;
		goto out;
	}

	if (!clk->ops->get_parent) 
	{
		clk_printf("%s: multi-parent clocks must implement .get_parent\n",
			__func__);
		goto out;
	};

    /* 得到父时钟索引 */
	idx = clk->ops->get_parent(clk->hw);
	if (idx >= clk->num_parents)/* idx为u8,必然>=0，这里只判断上限 */
    {
        goto out;
    }

	if (!clk->parents)
	{
		clk->parents = osl_malloc((sizeof(struct clk*) * clk->num_parents));
		if (clk->parents)
		{
		    (void)memset_s(clk->parents, sizeof(struct clk*) * clk->num_parents, 0, sizeof(struct clk*) * clk->num_parents);
		}
	}

	if (!clk->parents)
	{
		ret = __drv_clk_lookup(clk->parent_names[idx]);
	}
	else if (!clk->parents[idx])
		ret = clk->parents[idx] =
			__drv_clk_lookup(clk->parent_names[idx]);
	else
		ret = clk->parents[idx];

out:
	return ret;
}

static int __drv_clk_disable_auto_gating(struct clk *ptr_clk)
{
    int     ret = -1;

	if (!ptr_clk)
	{
	    return -1;
	}

    if (ptr_clk->ops->disable_auto_gating)  /* 有自动门控关闭函数 */
	{
	    ret = ptr_clk->ops->disable_auto_gating(ptr_clk->hw);
	}
	else
	{
	    ret = 0;
	}

    return ret;
}

static int __drv_clk_enable_auto_gating(struct clk *ptr_clk)
{
    int     ret = -1;

	if (!ptr_clk)
	{
	    return -1;
	}

    if (ptr_clk->ops->enable_auto_gating)  /* 有自动门控打开函数 */
	{
	    ret = ptr_clk->ops->enable_auto_gating(ptr_clk->hw);
	}
	else
	{
	    ret = 0;
	}

    return ret;
}

/*****************************************************************************
* 函 数 名  :  drv_clk_change_rate
*
* 功能描述  :  改变频率
*
* 输入参数  :  clk:时钟结构体指针
               
               
* 输出参数  :  无
*
* 返 回 值  :  无
*
*****************************************************************************/
static void drv_clk_change_rate(struct clk *clk)
{
	struct clk *child;

	unsigned long best_parent_rate = 0;



	if (clk->new_parent && clk->new_parent != clk->parent)
	{
		(void)__drv_clk_set_parent(clk, clk->new_parent, clk->new_parent_index);
	}

	if (clk->parent)
	{
		best_parent_rate = clk->parent->rate;
	}

	if (clk->ops->set_rate)
	{
		(void)clk->ops->set_rate(clk->hw, clk->new_rate, best_parent_rate);
	}

	if (clk->ops->recalc_rate)
	{
		clk->rate = clk->ops->recalc_rate(clk->hw, best_parent_rate);
	}
	else
	{
		clk->rate = best_parent_rate;
	}

    /*lint -save -e40 -e160 */
	hlist_for_each_entry(child, &clk->children, child_node) /*lint !e144*/
	{
		if (child->new_parent && child->new_parent != clk)
		{
			continue;
		}
		drv_clk_change_rate(child);
	}
	/*lint -restore +e40 +e160 */

	if (clk->new_child)
	{
		drv_clk_change_rate(clk->new_child);
	}

	return ;
}

static int __drv_clk_set_parent(struct clk *clk, struct clk *parent, u8 p_index)
{
	unsigned long flags;
	int ret = 0;
	struct clk *old_parent = clk->parent;
	bool migrated_enable = false;


	flags = drv_clk_enable_lock();

	/* 引用计数不为0 */
	if (clk->enable_count) 
	{
		(void)__drv_clk_enable(parent);
		migrated_enable = true;
	}

	/* 更新时钟树拓扑 */
	drv_clk_reparent(clk, parent);

	drv_clk_enable_unlock(flags);

	/* 设置父时钟 */
	if (parent && clk->ops->set_parent)
	{
		ret = clk->ops->set_parent(clk->hw, p_index);
	}

	if (ret) 
	{
        /* 操作失败，恢复原状态 */
		flags = drv_clk_enable_lock();

		drv_clk_reparent(clk, old_parent);

		if (migrated_enable && clk->enable_count) 
		{
			__drv_clk_disable(parent);
		} 
		else if (migrated_enable && (clk->enable_count == 0)) 
		{
			__drv_clk_disable(old_parent);
		} 
		else if (!migrated_enable && (clk->enable_count))  
		{
			__drv_clk_disable(parent);
			(void)__drv_clk_enable(old_parent);
		}

		drv_clk_enable_unlock(flags);


		return ret;
	}

	if (migrated_enable) 
	{
		flags = drv_clk_enable_lock();
		__drv_clk_disable(old_parent);
		drv_clk_enable_unlock(flags);
	}




	return 0;
}

static void drv_clk_reparent(struct clk *clk, struct clk *new_parent)
{
	hlist_del(&clk->child_node);

	if (new_parent)
		hlist_add_head(&clk->child_node, &new_parent->children);
	else
		hlist_add_head(&clk->child_node, &clk_balong_orphan_list);

	clk->parent = new_parent;
}

/*****************************************************************************
* 函 数 名  :  drv_clk_calc_new_rates
*
* 功能描述  :  重新计算时钟频率
*
* 输入参数  :  clk:时钟结构体指针
               rate:时钟频率
               
* 输出参数  :  无
*
* 返 回 值  :  会被改变的时钟树最顶部的时钟
*
*****************************************************************************/
static struct clk *drv_clk_calc_new_rates(struct clk *clk, unsigned long rate)
{
	struct clk    *top = clk;
	unsigned long best_parent_rate = 0;
	unsigned long new_rate;

	if (!clk)
	{
		return NULL;
	}

	/* 如果有父时钟，将频率存下来 */
	if (clk->parent)
	{
		best_parent_rate = clk->parent->rate;
	}

	/* 不是通过父时钟改变频率 */
	if (!(clk->flags & CLK_SET_RATE_PARENT)) 
	{
		if (!clk->ops->round_rate) 
		{
			clk->new_rate = clk->rate;
			return NULL;
		}
		new_rate = (unsigned long)(clk->ops->round_rate(clk->hw, rate, &best_parent_rate));
		goto out;
	}

	/* 如果没有父时钟 */
	if (!clk->parent) 
	{
		clk_printf("%s: %s has NULL parent\n", __func__, clk->name);
		return NULL;
	}

	if (!clk->ops->round_rate) 
	{
		top = drv_clk_calc_new_rates(clk->parent, rate);
		new_rate = clk->parent->new_rate;

		goto out;
	}

	new_rate = (unsigned long)(clk->ops->round_rate(clk->hw, rate, &best_parent_rate));

	if (best_parent_rate != clk->parent->rate) 
	{
		top = drv_clk_calc_new_rates(clk->parent, best_parent_rate);

		goto out;
	}

out:
	drv_clk_calc_subtree(clk, new_rate);

	return top;
}

static void drv_clk_calc_subtree(struct clk *clk, unsigned long new_rate)
{
	struct clk *child;

	clk->new_rate = new_rate;
	
	/*lint -save -e40 -e160 */
	hlist_for_each_entry(child, &clk->children, child_node) {/*lint !e144*/
		if (child->ops->recalc_rate)
			child->new_rate = child->ops->recalc_rate(child->hw, new_rate);
		else
			child->new_rate = new_rate;
		drv_clk_calc_subtree(child, child->new_rate);
	}
	/*lint -restore +e40 +e160 */
}

/*****************************************************************************
* 函 数 名  :  __drv_clk_recalc_rates
*
* 功能描述  :  重新计算时钟频率
*
* 输入参数  :  clk:时钟树开始的时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  无
*
*****************************************************************************/
static void __drv_clk_recalc_rates(struct clk *clk)
{
	unsigned long parent_rate = 0;
	struct clk *child;


	if (clk->parent)
	{
		parent_rate = clk->parent->rate;
	}

	if (clk->ops->recalc_rate)
	{
		clk->rate = clk->ops->recalc_rate(clk->hw, parent_rate);
	}
	else
	{
		clk->rate = parent_rate;
	}

	/*lint -save -e40 -e160 */
	hlist_for_each_entry(child, &clk->children, child_node)/*lint !e144*/
	{
		__drv_clk_recalc_rates(child);
	}
	/*lint -restore +e40 +e160 */
	return ;
}

int __drv_clk_enable(struct clk *ptr_clk)
{
	int   ret = 0;

	if (!ptr_clk)
	{
		return 0;
	}

	clk_printf_info("---------clk name = %s\n", ptr_clk->name);

	if (ptr_clk->aux_flag)
	{
			if(0 == ptr_clk->enable_count)  /* 时钟是关闭的 */
			{
				ret = __drv_clk_enable(ptr_clk->parent); /* [false alarm]:fortify */
				if (ret)
				{
					return ret;
				}

				/* 打开本时钟 */
				if (ptr_clk->ops->enable) 
				{
					ret = ptr_clk->ops->enable(ptr_clk->hw);
					if (ret) /* 打开操作失败 */
					{
						__drv_clk_disable(ptr_clk->parent);
						return ret;
					}

					/* 打开操作成功 */
					ptr_clk->enable_count = 1;
				}
			}
			else  /* 时钟已经是打开的 */
			{
				/* do nothing */
			}
		}
		else
		{
		    clk_printf_info("clk %s enable_count=%d\n", ptr_clk->name, ptr_clk->enable_count);
			if (ptr_clk->enable_count == 0) 
			{
				ret = __drv_clk_enable(ptr_clk->parent); /* [false alarm]:fortify */

				if (ret)
				{
					return ret;
				}

				if (ptr_clk->ops->enable) 
				{
					ret = ptr_clk->ops->enable(ptr_clk->hw);
					if (ret) 
					{
						__drv_clk_disable(ptr_clk->parent);
						return ret;
					}
				}
			}

			ptr_clk->enable_count++;
		}
	
	
	return 0;
}

void __drv_clk_disable(struct clk *ptr_clk)
{


	if (!ptr_clk)
	{
		return;
	}

	if (ptr_clk->aux_flag)
	{
		if(1 == ptr_clk->enable_count)  /* 时钟是打开的 */
		{
			/* 关闭本时钟 */
			if (ptr_clk->ops->disable) 
			{
				ptr_clk->ops->disable(ptr_clk->hw);
				ptr_clk->enable_count = 0;
			}
			__drv_clk_disable(ptr_clk->parent);  /* 关闭父时钟 */
			
		}
		else  /* 时钟已经是关闭的 */
		{
			/* do nothing */
		}
	}
	else
	{

		if (0 == ptr_clk->enable_count)  /* 时钟是关闭的 */
		{
			return;
		}

		if (--ptr_clk->enable_count > 0) /* 时钟还不应该被关闭 */
		{
			return;
		}

		if (ptr_clk->ops->disable)  /* 时钟可以关闭 */
		{
			ptr_clk->ops->disable(ptr_clk->hw);
		}

		__drv_clk_disable(ptr_clk->parent);  /* 关闭父时钟 */
	}

	return ;

}

/*lint -save -e10 -e160 -e26 -e40 -e516 -e413 */
static struct clk *__drv_clk_lookup(const char *name)
{
	struct clk *root_clk;
	struct clk *ret;

	if (!name)
	{
		return NULL;
	}

	hlist_for_each_entry(root_clk, &clk_balong_root_list, child_node) /*lint !e144*/
	{
		ret = __drv_clk_lookup_subtree(name, root_clk);
		if (ret)
		{
			return ret;
		}
	}

	hlist_for_each_entry(root_clk, &clk_balong_orphan_list, child_node) /*lint !e144*/
	{
		ret = __drv_clk_lookup_subtree(name, root_clk);
		if (ret)
		{
			return ret;
		}
	}

	return NULL;
}
/*lint -restore +e10 +e160 +e26 +e40 +e516 +e413 */

/*lint -save -e10 -e160 -e26 -e40 -e516 -e413 */
static struct clk *__drv_clk_lookup_subtree(const char *name, struct clk *ptr_clk)
{
	struct clk *child;
	struct clk *ret;

	if (!drv_clk_strcmp(ptr_clk->name, name))  /* 名字一样 */ 
	{
		return ptr_clk;
	}
	hlist_for_each_entry(child, &ptr_clk->children, child_node) /*lint !e144*/
	{
		ret = __drv_clk_lookup_subtree(name, child);
		if (ret)
		{
			return ret;
		}
	}
	return NULL;
}
/*lint -restore +e10 +e160 +e26 +e40 +e516 +e413 */

static bool __drv_clk_is_enabled(struct clk *clk)
{
	int ret;

	if (!clk)
	{
		return false;
	}

    /* 如果时钟没有is_enabled函数，根据引用计数判断时钟是否是打开的 */
	if (!clk->ops->is_enabled) 
	{
		ret = clk->enable_count ? 1 : 0;
		goto out;
	}

	ret = clk->ops->is_enabled(clk->hw);
out:
	return (bool)(!!ret);
}

static unsigned long __drv_clk_get_rate(struct clk *clk)
{
	unsigned long ret;

	if (!clk) {
		ret = 0;
		goto out;
	}

	ret = clk->rate;

	if (clk->flags & CLK_IS_ROOT)
		goto out;

	if (!clk->parent)
		ret = 0;

out:
	return ret;
}

static struct clk *drv_clk_get_sys(const char *dev_id, const char *con_id)
{
	struct clk_lookup *ptr_clk_lookup = NULL;

	osl_sem_down(&clk_mutex);
	ptr_clk_lookup = drv_clk_find(dev_id, con_id);
	if (IS_ERR(ptr_clk_lookup))
	{
		ptr_clk_lookup = NULL;
	}
	osl_sem_up(&clk_mutex);

	return ptr_clk_lookup ? ptr_clk_lookup->clk : ERR_PTR(-ENOENT);
}

/*****************************************************************************
* 函 数 名  :  drv_clk_find
*
* 功能描述  :  查找时钟
*
* 输入参数  :  dev_id:设备ID
               con_id:时钟名字
* 输出参数  :  无
*
* 返 回 值  :  时钟查找结构体指针
*
*****************************************************************************/
static struct clk_lookup *drv_clk_find(const char *dev_id, const char *con_id)
{
	struct clk_lookup *p, *cl = NULL;
	int match, best_found = 0, best_possible = 0;

	if (dev_id)
		best_possible += 2;
	if (con_id)
		best_possible += 1;

	list_for_each_entry(p, &balong_clocks, node) { /*lint !e144*/
		match = 0;
		if (p->dev_id) {
			if (!dev_id || drv_clk_strcmp(p->dev_id, dev_id))
				continue;/*lint !e144*/
			match += 2;
		}
		if (p->con_id) {
			if (!con_id || drv_clk_strcmp(p->con_id, con_id))
				continue;/*lint !e144*/
			match += 1;
		}

		if (match > best_found) {
			cl = p;
			if (match != best_possible)
				best_found = match;
			else
				break;
		}
	}
	return cl;
}

static int drv_clk_strcmp(const char *cs, const char *ct)
{
	char c1, c2;

	while (1) {			/*lint !e716*/
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}

static unsigned long drv_clk_enable_lock(void)
{
	unsigned long flags;

	spin_lock_irqsave(&clk_spinlock, flags);
	return flags;
}


static inline void __drv_clk_pm_log(struct clk *clk, enum clk_op_type  op_type)
{
    struct clk_op_entry stru_clk_op_entry;

	stru_clk_op_entry.task_id = (OSL_TASK_ID)osl_task_self();
	if (clk)
	{
	    (void)memcpy_s((void *)stru_clk_op_entry.clk_name, LOG_CLK_NAME_LEN, (const void *)clk->name, LOG_CLK_NAME_LEN);
		stru_clk_op_entry.enable_count_before_op = clk->enable_count;
	}
	stru_clk_op_entry.op_type = op_type;
	(void)bsp_pm_log(PM_OM_CCLK, sizeof(struct clk_op_entry), (void *)&stru_clk_op_entry);
}



static void drv_clk_enable_unlock(unsigned long flags)
{
	spin_unlock_irqrestore(&clk_spinlock, flags);
}


struct clk *drv_clk_get(const char * dev, const char *con_id)
{
	const char *dev_id = dev ? NULL : NULL;
	struct clk *ptr_clk = NULL;

	ptr_clk = drv_clk_get_sys(dev_id, con_id);
	if (IS_ERR(ptr_clk))
	{
		clk_printf("drv_clk_get function can't find %s,may be you should register it firstly!!\n", con_id);
	}
	return ptr_clk;


}


const char *__drv_clk_get_name(struct clk *clk)
{
	return !clk ? NULL : clk->name;
}



u8 __drv_clk_get_num_parents(struct clk *clk)
{
	return (!clk) ? 0 : clk->num_parents; /* [false alarm]:fortify */
}

struct clk *__drv_clk_get_parent(struct clk *clk)
{
	return !clk ? NULL : clk->parent;
}


unsigned long __drv_clk_get_flags(struct clk *clk)
{
	return !clk ? 0 : clk->flags;
}


/*****************************************************************************
* 函 数 名  :  drv_clk_disable
*
* 功能描述  :  关闭时钟
*
* 输入参数  :  clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  无
*
*****************************************************************************/
void drv_clk_disable(struct clk *clk)
{
	unsigned long flags;
	
	/***** pm log *****/
	__drv_clk_pm_log(clk, CLK_OP_TYPE_DISA);

	flags = drv_clk_enable_lock();
	__drv_clk_disable(clk);
	drv_clk_enable_unlock(flags);
	
}

int drv_clk_is_enabled(struct clk *clk)
{
	unsigned long flags;
	bool          is_enabled = false;

	flags = drv_clk_enable_lock();
	is_enabled = __drv_clk_is_enabled(clk);
	drv_clk_enable_unlock(flags);

	return is_enabled;

}

/*****************************************************************************
* 函 数 名  :  drv_clk_enable
*
* 功能描述  :  打开时钟
*
* 输入参数  :  clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  0，打开成功；其他值，打开失败
*
*****************************************************************************/
int drv_clk_enable(struct clk *clk)
{
	unsigned long flags;
	int ret;
	
	/***** pm log *****/
	__drv_clk_pm_log(clk, CLK_OP_TYPE_ENAB);

	flags = drv_clk_enable_lock();
	ret = __drv_clk_enable(clk);
	drv_clk_enable_unlock(flags);

	return ret;
}

/*****************************************************************************
* 函 数 名  :  __drv_clk_round_rate
*
* 功能描述  :  round时钟频率
*
* 输入参数  :  clk:时钟结构体指针
               rate:round前的时钟频率
               
* 输出参数  :  无
*
* 返 回 值  :  round后的时钟频率
*
*****************************************************************************/
unsigned long __drv_clk_round_rate(struct clk *clk, unsigned long rate)
{
	unsigned long parent_rate = 0;

	if (!clk)
	{
		return 0;
	}

	if (!clk->ops->round_rate)  /* 时钟没有round函数 */
	{
		if (clk->flags & CLK_SET_RATE_PARENT)  
		{
			return __drv_clk_round_rate(clk->parent, rate);
		}
		else
		{
			return clk->rate;
		}
	}

	
    /* 有round函数 */
	if (clk->parent)
	{
		parent_rate = clk->parent->rate;
	}

	return (unsigned long)(clk->ops->round_rate(clk->hw, rate, &parent_rate));
}

/*****************************************************************************
* 函 数 名  :  drv_clk_round_rate
*
* 功能描述  :  round时钟频率
*
* 输入参数  :  clk:时钟结构体指针
               rate:round前的时钟频率
               
* 输出参数  :  无
*
* 返 回 值  :  round后的时钟频率
*
*****************************************************************************/
long drv_clk_round_rate(struct clk *clk, unsigned long rate)
{
	unsigned long ret;

	osl_sem_down(&clk_mutex);
	ret = __drv_clk_round_rate(clk, rate);
	osl_sem_up(&clk_mutex);

	return (long)ret;
}


/*****************************************************************************
* 函 数 名  :  drv_clk_get_rate
*
* 功能描述  :  获取时钟频率
*
* 输入参数  :  clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  时钟频率
*
*****************************************************************************/
unsigned long drv_clk_get_rate(struct clk *clk)
{
	unsigned long rate;
	
	osl_sem_down(&clk_mutex);

	if (clk && (clk->flags & CLK_GET_RATE_NOCACHE))
		__drv_clk_recalc_rates(clk);

	rate = __drv_clk_get_rate(clk);
	osl_sem_up(&clk_mutex);

	return rate;
}



/*****************************************************************************
* 函 数 名  :  drv_clk_set_rate
*
* 功能描述  :  设置时钟频率
*
* 输入参数  :  clk:时钟结构体指针
               rate:欲设置成的时钟频率
               
* 输出参数  :  无
*
* 返 回 值  :  0，操作成功；其他值，操作失败
*
*****************************************************************************/

int drv_clk_set_rate(struct clk *clk, unsigned long rate)
{

	struct clk *top;
	int ret = 0;
	
	/***** pm log *****/
	__drv_clk_pm_log(clk, CLK_OP_TYPE_SETP);

	osl_sem_down(&clk_mutex);

	/* 欲设置成的频率和原频率相等 */
	if (rate == clk->rate)
		goto out;

	if (clk->flags & CLK_SET_RATE_GATE) 
	{
		ret = -EBUSY;
		goto out;
	}

	/* 得到时钟树最顶部的会被改变频率的时钟 */
	top = drv_clk_calc_new_rates(clk, rate);
	if (!top) 
	{
		ret = -EINVAL;
		goto out;
	}


	/* 改变频率 */
	drv_clk_change_rate(top);

out:
	osl_sem_up(&clk_mutex);

	return ret;
}

/*****************************************************************************
* 函 数 名  :  drv_clk_get_parent
*
* 功能描述  :  获取父时钟
*
* 输入参数  :  clk:时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  父时钟
*
*****************************************************************************/
struct clk *drv_clk_get_parent(struct clk *clk)
{
	struct clk *parent;

	osl_sem_down(&clk_mutex);
	parent = __drv_clk_get_parent(clk);
	osl_sem_up(&clk_mutex);

	return parent;
}


int drv_clk_enable_auto_gating(struct clk *ptr_clk)
{
    int    ret = -1;
	
	/***** pm log *****/
	__drv_clk_pm_log(ptr_clk, CLK_OP_TYPE_ENAU);


	osl_sem_down(&clk_mutex);
	ret = __drv_clk_enable_auto_gating(ptr_clk);
	osl_sem_up(&clk_mutex);

    return ret;
}


int drv_clk_disable_auto_gating(struct clk *ptr_clk)
{
    int    ret = -1;
	
	/***** pm log *****/
	__drv_clk_pm_log(ptr_clk, CLK_OP_TYPE_DIAU);


	osl_sem_down(&clk_mutex);
	ret = __drv_clk_disable_auto_gating(ptr_clk);
	osl_sem_up(&clk_mutex);

    return ret;
}


/*****************************************************************************
* 函 数 名  :  drv_clk_set_parent
*
* 功能描述  :  设置父时钟
*
* 输入参数  :  clk:时钟结构体指针
               parent:欲设置成的父时钟
               
* 输出参数  :  无
*
* 返 回 值  :  0，操作成功；其他值，操作失败
*
*****************************************************************************/
int drv_clk_set_parent(struct clk *clk, struct clk *parent)
{

	int ret = 0;
	u8 p_index = 0;
	unsigned long p_rate = 0;
	
	/***** pm log *****/
	__drv_clk_pm_log(clk, CLK_OP_TYPE_SETP);

	if (!clk || !clk->ops)
		return -EINVAL;

	/* 父时钟个数大于1，但是没有set_parent的ops */
	if ((clk->num_parents > 1) && (!clk->ops->set_parent))
		return -ENOSYS;

	osl_sem_down(&clk_mutex);

	if (clk->parent == parent)
		goto out;

	if ((clk->flags & CLK_SET_PARENT_GATE))   /* 必须在非使用状态下才能设置父时钟 */
	{
		ret = -EBUSY;
		goto out;
	}

	/* 找父时钟的索引 */
	if (parent) 
	{
		p_index = drv_clk_fetch_parent_index(clk, parent);
		clk_printf_info("p_index = %d\n", p_index);
		
		p_rate = parent->rate;
		clk_printf_info("p_rate = %d\n", p_rate);
		if (p_index == clk->num_parents) 
		{
			clk_printf("%s: clk %s can not be parent of clk %s\n",
					__func__, parent->name, clk->name);
			ret = -EINVAL;
			goto out;
		}
	}

    (void)__drv_clk_speculate_rates(clk, p_rate); 


	/* 重新设置父 */
	(void)__drv_clk_set_parent(clk, parent, p_index); 

	/* 重新计算频率 */
	__drv_clk_recalc_rates(clk);

out:
	osl_sem_up(&clk_mutex);

	return ret;
}


/*lint -restore +e10 +e160 +e26 +e40 +e516 +e613 +e438 */


/*****************************************************************************
* 函 数 名  :  drv_clk_register
*
* 功能描述  :  注册时钟
*
* 输入参数  :  ptr_device:设备
               ptr_clk_hw:硬件指定时钟结构体指针
               
* 输出参数  :  无
*
* 返 回 值  :  时钟结构体指针
*
*****************************************************************************/
struct clk *drv_clk_register(const char * ptr_device, struct clk_hw *ptr_clk_hw)
{
	int ret;
	struct clk *ptr_clk;

	ptr_clk = osl_malloc(sizeof(struct clk));
	if (!ptr_clk) 
	{
		clk_printf("%s: could not allocate clk\n", __func__);
		ret = -ENOMEM;
		goto fail_out;
	}

	/* 申请成功 */
	(void)memset_s(ptr_clk, sizeof(struct clk), 0, sizeof(struct clk));

	/* 将所有时钟的enable_count设置为1，默认都是打开的 */
	//ptr_clk->enable_count = 1;

	/* 是否是虚拟时钟 */
	ptr_clk->is_virtual_clk = ptr_clk_hw->isvirtual;

	/* 是否带有aux_flag标志 */
	ptr_clk->aux_flag = ptr_clk_hw->aux_flag;

	/* 是否是叶子节点 */
	ptr_clk->leaf_flag = ptr_clk_hw->leaf_flag;


	ret = _drv_clk_register(ptr_device, ptr_clk_hw, ptr_clk);
	if (!ret)
		return ptr_clk;

	osl_free((void *)ptr_clk);
fail_out:
	return ERR_PTR(ret);
}

void drv_clkdev_add(struct clk_lookup *ptr_clk_lookup)
{
	osl_sem_down(&clk_mutex);
	ptr_clk_lookup->clk_no = g_clk_cnt;
	list_add_tail(&ptr_clk_lookup->node, &balong_clocks);
	g_clk_cnt++;
	osl_sem_up(&clk_mutex);

	return ;
}



/*lint -save -e578 -e713 -e10 -e160 -e26 -e40 -e516 -e613 -e438*/
const char *drv_of_clk_get_parent_name(struct device_node *np, int index)
{
	struct of_phandle_args clkspec = {0};
	const char *clk_name = NULL;
	int rc = 0;

	if (index < 0)
		return NULL;

	rc = of_parse_phandle_with_args(np, "clocks", "#clock-cells", index,
					&clkspec);
	if (rc)
		return NULL;

	if (of_property_read_string_index(clkspec.np, "clock-output-names",
					  clkspec.args_count ? clkspec.args[0] : 0,
					  &clk_name) < 0)
	{
	    if (NULL != clkspec.np)
    	{
			clk_name = clkspec.np->name;
    	}
	}

	of_node_put(clkspec.np);
	return clk_name;
}

/*lint -restore +e578 +e713 +e10 +e160 +e26 +e40 +e516 +e613 +e438*/

/*****************************************************************************
* 函 数 名	:  drv_of_clk_init
*
* 功能描述	:  通过of接口初始化时钟
*
* 输入参数	:  matches:匹配的of_device_id
			   
* 输出参数	:  无
*
* 返 回 值	:  无
*
*****************************************************************************/
void  drv_of_clk_init(const struct of_device_id *matches)
{
	struct device_node *np;

	spin_lock_init(&clk_spinlock);
    osl_sem_init(1, &clk_mutex);

	if (!matches)
	{
	    return ;
	}

	for_each_matching_node(np, matches) 
	{
		if (!(drv_clk_strcmp("ccore_clk_last_node", np->name)))
		{
			break;
		}
		
		const struct of_device_id *match = of_match_node(matches, np);
		drv_of_clk_init_cb_t clk_init_cb = match->data; /*lint !e158*/
		clk_init_cb(np);
	}

	//clk_init_enable_count();

	return ;
}



