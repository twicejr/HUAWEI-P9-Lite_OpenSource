/*************************************************************************
*   版权所有(C) 2008-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  clk_balong_debug.c
*
*   作    者 :  huangxianke h00277960
*
*   描    述 :  clk 调试
*
*   修改记录 : 2014年9月15日  v1.00  h00277960  创建
**************************************************************************/

/*lint --e{530,525,628,666,801,830,144,413, 813, 737, 574, 534, 586 } */

#include <osl_list.h>
#include <bsp_om.h>
#include <clk_balong_core.h>
#include <bsp_hardtimer.h>

struct hi_divclk {
	struct clk_hw	hw;
	u32     reg;                /* 分频寄存器地址 */
	u8      shift;              /* 分频bit开始的bit索引，如果bit10-8表示分频bit，那么此值为8 */
	u8      width;              /* 分频bit数，如果bit10-8表示分频bit，那么此值为3 */
	u8      is_n_plus_1_div;    /* 是否是N+1分频器 */
	u32      mbits;             /* mask bits in divider register */
	u32     en_ref_before_set_div; /* 设置分频前要先打开参考时钟 */
	const struct clk_div_table *table;
	spinlock_t *lock;
};

struct hi_gateclk {
	struct clk_hw   hw;
	u32             reg;             /* 门控使能寄存器基址 */
	u8              bit_idx;          /* 门控使能位 */
	u8              flags;
	u8              is_virtual;       /* 是否是虚拟时钟 */
	u8              auto_gate_bit;    /* 自动门控控制位 */
	u32             auto_gate_base;  /* 自动门控寄存器基址 */
	u32             auto_gate_offset; /* 自动门控寄存器偏移 */
	spinlock_t      *lock;
};

struct drv_clk_mux {
	struct clk_hw   hw;
	u32             reg;
	u32             *table;
	u32             mask;
	u8              shift;
	u8              flags;
	spinlock_t      *lock;
};

extern struct list_head balong_clocks ;
extern struct hlist_head  clk_balong_root_list;
extern unsigned int g_status_reg_offset_to_enable;

static  unsigned int clk_debug_clk_fls(unsigned int x)
{
	unsigned int r = 32;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {

		r -= 1;
	}
	return r;
}

void clk_debug_get(const char* clk_name)
{
	struct clk *ptr_clk = NULL;

	ptr_clk = clk_get(NULL, clk_name);
	if (IS_ERR(ptr_clk))
	{
		clk_printf("clk_get %s err\n", clk_name);
		return ;
	}

	clk_printf("clk_get %s ok\n", clk_name);

	return ;
}
void clk_debug_show_reg(unsigned int reg_addr)
{
	unsigned int reg_val = 0;

	reg_val = readl(reg_addr);
	clk_printf("addr 0x%08x = 0x%08x\n", reg_addr, reg_val);

	return ;
}

void clk_debug_show_clks_in_root_hlist(void)
{
	struct clk *ptr_clk = NULL;
	static unsigned int   u32_cnt_in_root_hlist = 0;

	/*lint -save -e160 -e40 */
	/* search the 'proper' clk tree first */
	hlist_for_each_entry(ptr_clk, &clk_balong_root_list, child_node)
	{
		clk_printf("in root hlist no = %d name = %s\n", u32_cnt_in_root_hlist, ptr_clk->name);
		u32_cnt_in_root_hlist++;
	}
	/*lint -restore +e160 +e40 */

	return ;
}

void clk_debug_show_clks_in_list(void)
{
	struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		clk_printf("in list no = %d name = %s\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
	}

	return ;
}

void clk_debug_show_all_clks_rate(void)
{
	struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		clk_printf("in list no=%d name=%s rate=%d\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id,
														ptr_clk_lookup->clk->rate);
	}

	return ;
}

void clk_debug_enable_clk(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			(void)clk_enable(ptr_clk);

			clk_printf("clk_enable ok\n");

		}
	}



	return ;
}

/*lint -save -e144 -e413 */
void clk_debug_disable_clk(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			clk_disable(ptr_clk);

			clk_printf("clk_disable end\n");

		}
	}

	return ;
}
/*lint -restore +e144 +e413 */

void clk_debug_is_enabled(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	int ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			ret = clk_is_enabled(ptr_clk);
			if (false == ret)
			{
				clk_printf("%s is disabled\n", clk_name);
			}
			else
			{
				clk_printf("%s is enabled\n", clk_name);
			}

		}
	}

	return ;
}

void clk_debug_set_rate(unsigned int clk_no_in_list, unsigned long req_rate)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	int ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			ret = clk_set_rate(ptr_clk, req_rate);
			if (ret)
			{
				clk_printf("%s set rate to %d err ret = %d\n", clk_name, req_rate, ret);
			}
			else
			{
				clk_printf("%s set rate to %d ok\n", clk_name, req_rate);
			}


		}
	}

	return ;
}

void clk_debug_get_rate(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;
	unsigned long rate_get = 0;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			rate_get = clk_get_rate(ptr_clk);
			clk_printf("get rate = %d\n", rate_get);


		}
	}

	return ;
}

void clk_debug_set_parent(unsigned int clk_no_in_list, unsigned int parent_clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	struct clk            *ptr_parent_clk = NULL;
	char                  *clk_name = NULL;
	char                  *parent_clk_name = NULL;
	int                   ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);
		}

		if (parent_clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			parent_clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_parent_clk = clk_get(NULL, parent_clk_name);
			if (NULL == ptr_parent_clk)
			{
				clk_printf("clk_get parent %s err\n", parent_clk_name);
				return ;
			}

			clk_printf("clk_get parent %s ok\n", parent_clk_name);
		}
	}

	ret = clk_set_parent(ptr_clk, ptr_parent_clk);
	if (ret)
	{
		clk_printf("%s set parent to %s err ret=%d\n", clk_name, parent_clk_name, ret);
		return ;
	}
	else
	{
		clk_printf("%s set parent to %s ok\n", clk_name, parent_clk_name);
	}

	return ;
}

void clk_debug_get_parent(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);
		}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

	ptr_parent_clk = clk_get_parent(ptr_clk);
	if (IS_ERR(ptr_parent_clk))
	{
		/*lint -save -e613*/
		clk_printf("get %s parent err\n", ptr_clk->name);
		/*lint -restore +e613*/
		return ;
	}
	else
	{
		/*lint -save -e613*/
		clk_printf("get %s parent %s ok\n", ptr_clk->name, ptr_parent_clk->name);
		/*lint -restore +e613*/
	}

	return ;
}

void clk_debug_show_clk_parents(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			//clk_printf("clk_get %s ok\n", clk_name);
		}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

	/*lint -save -e613*/
	clk_printf(" %s  \n", ptr_clk->name);
	/*lint -restore +e613*/

	while ((ptr_parent_clk = clk_get_parent(ptr_clk)))
	{
		clk_printf(" %s  \n", ptr_parent_clk->name);
		ptr_clk = ptr_parent_clk;
	}


	return ;
}

void clk_debug_show_clks_enable_count(void)
{
	struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		clk_printf("in list no=%d name=%s enable_count=%d\n",
			ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_clk_lookup->clk->enable_count);
	}

	return ;
}

void clk_debug_show_clk_info(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

			clk_printf("clk_get %s ok\n", clk_name);

			clk_printf("clk no=%d name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d",
						 clk_no_in_list, ptr_clk->name, ptr_clk->rate,
						 ptr_clk->is_virtual_clk, ptr_clk->aux_flag, ptr_clk->enable_count);

		}
	}

	return ;
}

void clk_debug_show_clk_from_leaf_info(unsigned int leaf_clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk            *ptr_clk = NULL;
	char                  *clk_name = NULL;
	struct clk            *ptr_parent_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (leaf_clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
			if (NULL == ptr_clk)
			{
				clk_printf("clk_get %s err\n", clk_name);
				return ;
			}

		}
	}

	if (NULL == ptr_clk)
	{
		clk_printf("search clk err\n");
		return ;
	}

	/*lint -save -e613*/
	clk_printf("clk name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",
				 ptr_clk->name, ptr_clk->rate,
				 ptr_clk->is_virtual_clk, ptr_clk->aux_flag, ptr_clk->enable_count);
	/*lint -restore +e613*/
	while ((ptr_parent_clk = clk_get_parent(ptr_clk)))
	{
		clk_printf("clk name=%s rate=%d is_virtual=%d aux_flag=%d enable_count=%d\n",
					 ptr_parent_clk->name, ptr_parent_clk->rate,
					 ptr_parent_clk->is_virtual_clk, ptr_parent_clk->aux_flag, ptr_parent_clk->enable_count);
		ptr_clk = ptr_parent_clk;
	}


	return ;
}

void clk_debug_show_children(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk_lookup     *ptr_clk_lookup_2nd_time = NULL;
	struct clk            *ptr_parent_clk = NULL;
	struct clk            *ptr_child_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			ptr_parent_clk = ptr_clk_lookup->clk;

			/* 遍历链表 */
			list_for_each_entry(ptr_clk_lookup_2nd_time, &balong_clocks, node)  /*lint !e613*/
			{
				ptr_child_clk = ptr_clk_lookup_2nd_time->clk;
				if (ptr_parent_clk == ptr_child_clk->parent)
				{
					clk_printf("no %d clk %s is parent of no %d %s\n",
						ptr_clk_lookup->clk_no, ptr_parent_clk->name,
						ptr_clk_lookup_2nd_time->clk_no, ptr_child_clk->name);
				}
			}
		}
	}

	return ;
}

void clk_debug_show_all_children(void)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk_lookup     *ptr_clk_lookup_2nd_time = NULL;
	struct clk            *ptr_parent_clk = NULL;
	struct clk            *ptr_child_clk = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		ptr_parent_clk = ptr_clk_lookup->clk;

		/* 遍历链表 */
		list_for_each_entry(ptr_clk_lookup_2nd_time, &balong_clocks, node)  /*lint !e613*/
		{
			ptr_child_clk = ptr_clk_lookup_2nd_time->clk;
			if (ptr_parent_clk == ptr_child_clk->parent)
			{
				clk_printf("no %d clk %s is parent of no %d %s\n",
					ptr_clk_lookup->clk_no, ptr_parent_clk->name,
					ptr_clk_lookup_2nd_time->clk_no, ptr_child_clk->name);

			}
		}
		clk_printf("\n\n");
	}

	return ;
}

void clk_debug_enable_auto_gating(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	int                   ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			ret = clk_enable_auto_gating(ptr_clk_lookup->clk);
			if (ret)
			{
				clk_printf("no %d name %s enable_auto_gating err\n",
							 ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				return ;
			}
			clk_printf("no %d name %s enable_auto_gating ok\n",
						 ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);

		}
	}

	return ;
}

void clk_debug_disable_auto_gating(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	int                   ret = -1;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			ret = clk_disable_auto_gating(ptr_clk_lookup->clk);
			if (ret)
			{
				clk_printf("no %d name %s disable_auto_gating err\n",
							 ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
				return ;
			}
			clk_printf("no %d name %s disable_auto_gating ok\n",   /* [false alarm]:屏蔽Fortify错误 */
						 ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);

		}
	}

	return ;
}

void clk_debug_show_all_maybe_parents(void)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk_lookup     *ptr_clk_lookup_parent = NULL;
	int                   i = 0;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		clk_printf("clk no = %d name = %s num_parents = %d\n",
					 ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id, ptr_clk_lookup->clk->num_parents);

		for (i = 0; i < ptr_clk_lookup->clk->num_parents; i++) /*lint !e830*/
		{
			//clk_printf("parent %d  name = %s\n",
			//			i,  ptr_clk_lookup->clk->parents[i]->name);

			/* 遍历链表 */
			list_for_each_entry(ptr_clk_lookup_parent, &balong_clocks, node) /*lint !e613*/
			{
				/* 是父时钟 */
				if (ptr_clk_lookup_parent->clk == ptr_clk_lookup->clk->parents[i])
				{
					/* 还是当前父时钟 */
					if (ptr_clk_lookup_parent->clk == ptr_clk_lookup->clk->parent)
					{
						clk_printf("parent %d  no = %d name = %s----current parent\n",
									i,  ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
					}
					else  /* 只是父时钟，非当前父时钟 */
					{
						clk_printf("parent %d  no = %d name = %s\n",
									i,  ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
					}
				}
		
			}

			//ptr_clk_lookup_parent = container_of(&(ptr_clk_lookup->clk->parents[i]), struct clk_lookup, clk);
			//clk_printf("parent %d no = %d name = %s\n",
			//			i, ptr_clk_lookup_parent->clk_no, ptr_clk_lookup_parent->con_id);
		}

		clk_printf("\n\n"); /*lint !e539*/
	}


	return ;
}

int clk_debug_get_curr_children_no(unsigned int clk_no_in_list, unsigned int *buf, unsigned int *children_sum)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk_lookup     *ptr_clk_lookup_2nd_time = NULL;
	struct clk            *ptr_parent_clk = NULL;
	struct clk            *ptr_child_clk = NULL;
	unsigned int          this_children_sum = 0;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			ptr_parent_clk = ptr_clk_lookup->clk;

			/* 遍历链表 */
			list_for_each_entry(ptr_clk_lookup_2nd_time, &balong_clocks, node)	/*lint !e613*/
			{
				ptr_child_clk = ptr_clk_lookup_2nd_time->clk;
				if (ptr_parent_clk == ptr_child_clk->parent)
				{
					buf[this_children_sum] = ptr_clk_lookup_2nd_time->clk_no;
					this_children_sum++;

				}
			}
		}
	}

	*children_sum = this_children_sum;

	return 0;

}

char *clk_debug_get_name_with_no(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	char *clk_name = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
		}
	}

	return clk_name;

}

struct clk* clk_debug_get_with_no(unsigned int clk_no_in_list)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	struct clk  *ptr_clk = NULL;
	char *clk_name = NULL;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (clk_no_in_list == ptr_clk_lookup->clk_no)
		{
			clk_name = clk_alloc_copy(ptr_clk_lookup->con_id);
			ptr_clk = clk_get(NULL, clk_name);
		}
	}

	return ptr_clk;
}

typedef enum tag_enum_clk_type
{
	ENUM_CLK_TYPE_FIXED_RATE,
	ENUM_CLK_TYPE_GATE,
	ENUM_CLK_TYPE_MUX,
	ENUM_CLK_TYPE_DIV,
	ENUM_CLK_TYPE_FIXED_FACTOR,
	ENUM_CLK_TYPE_BUTT
}enum_clk_type;

#define CLK_TYPE_STR_CHARS_CNT      14
#define CLK_STATUS_REG_ADDR_STR_CHARS_CNT 14
#define CLK_STATUS_REG_VAL_STR_CHARS_CNT  14
#define CLK_STATUS_REG_START_BIT_STR_CHARS_CNT  2
#define CLK_STATUS_REG_END_BIT_STR_CHARS_CNT  2

enum_clk_type clk_debug_get_clk_type_val(unsigned int clk_no_in_list)
{
	struct clk	*clk = NULL;

	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || (IS_ERR(clk)))
	{
		return ENUM_CLK_TYPE_BUTT;
	}

	if (clk->flags & CLK_IS_ROOT)  /* fixed_rate */
	{
		return ENUM_CLK_TYPE_FIXED_RATE;
	}
	else if (clk->ops->enable) /* gate */
	{
		return ENUM_CLK_TYPE_GATE;
	}
	else if (clk->ops->set_parent) /* mux */
	{
		return ENUM_CLK_TYPE_MUX;
	}
	else //if (clk->ops->set_rate) /* div/fixed_factor*/
	{
		if (CLK_IS_BASIC & clk->flags)
		{
			return ENUM_CLK_TYPE_FIXED_FACTOR;
		}
		else
		{
			return ENUM_CLK_TYPE_DIV;
		}
	}
}

char * clk_debug_get_clk_type_str(unsigned int clk_no_in_list)
{
	enum_clk_type clk_type = 0;
	char * clk_type_str = "[invalid_clk ]";

	clk_type = clk_debug_get_clk_type_val(clk_no_in_list);

	switch (clk_type)
	{
		case ENUM_CLK_TYPE_FIXED_RATE:
			clk_type_str = "[fixed_rate  ]";
			break;
		case ENUM_CLK_TYPE_GATE:
			clk_type_str = "[gate        ]";
			break;
		case ENUM_CLK_TYPE_MUX:
			clk_type_str = "[mux         ]";
			break;
		case ENUM_CLK_TYPE_DIV:
			clk_type_str = "[div         ]";
			break;
		case ENUM_CLK_TYPE_FIXED_FACTOR:
			clk_type_str = "[fixed_factor]";
			break;
		default:
			clk_type_str = "[invalid_clk ]";
			break;

	}

	return clk_type_str;
}

unsigned long clk_debug_get_status_reg_addr_val(unsigned int clk_no_in_list)
{
	enum_clk_type clk_type = 0;
	unsigned long status_reg_addr = 0x0;
	struct clk *clk = NULL;

	clk_type = clk_debug_get_clk_type_val(clk_no_in_list);
	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || IS_ERR(clk))
	{
		return 0x0;
	}

	switch (clk_type)
	{
		case ENUM_CLK_TYPE_GATE:
			if (1 == clk->hw->isvirtual)
			{
				status_reg_addr = 0x0;
			}
			else
			{
				status_reg_addr = (unsigned long)(container_of(clk->hw, struct hi_gateclk, hw)->reg) + g_status_reg_offset_to_enable;
			}
			break;
		case ENUM_CLK_TYPE_MUX:
			status_reg_addr = (unsigned long)(container_of(clk->hw, struct drv_clk_mux, hw)->reg);
			break;
		case ENUM_CLK_TYPE_DIV:
			status_reg_addr = (unsigned long)(container_of(clk->hw, struct hi_divclk, hw)->reg);
			break;
		default:
			status_reg_addr = 0x0;
			break;

	}

	return status_reg_addr;
}

char g_status_reg_addr_str[CLK_STATUS_REG_ADDR_STR_CHARS_CNT + 1] = {'\0'};

char * clk_debug_get_status_reg_addr_str(unsigned int clk_no_in_list)
{
	unsigned long reg_addr = 0x0;
	struct clk	*clk = NULL;

	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || (IS_ERR(clk)))
	{
		return "[invalid_clk ]";
	}

	reg_addr = clk_debug_get_status_reg_addr_val(clk_no_in_list);
	if (0x0 != reg_addr)
	{
		(void)sprintf_s((char*)(&g_status_reg_addr_str[0]), CLK_STATUS_REG_ADDR_STR_CHARS_CNT + 1,
					 "[a:0x%08x]", reg_addr);
		return &g_status_reg_addr_str[0];
	}
	else
	{
		return "[a:0x********]";
	}

}

unsigned int clk_debug_get_status_reg_val(unsigned int clk_no_in_list)
{
	unsigned long status_reg_addr = 0x0;
	unsigned int status_reg_val = 0x0;

	status_reg_addr = clk_debug_get_status_reg_addr_val(clk_no_in_list);
	if (0x0 == status_reg_addr)
	{
		return 0x0;
	}

	status_reg_val = readl((unsigned int)(status_reg_addr));

	return status_reg_val;
}

char g_status_reg_val_str[CLK_STATUS_REG_VAL_STR_CHARS_CNT + 1] = {'\0'};
char * clk_debug_get_status_reg_val_str(unsigned int clk_no_in_list)
{
	unsigned long reg_val = 0x0;
	struct clk *clk = NULL;

	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || (IS_ERR(clk)))
	{
		return "[invalid_clk ]";
	}

	if (((ENUM_CLK_TYPE_GATE == clk_debug_get_clk_type_val(clk_no_in_list) && (1 == clk->hw->isvirtual))
		 ||(ENUM_CLK_TYPE_FIXED_RATE == clk_debug_get_clk_type_val(clk_no_in_list))
		 ||(ENUM_CLK_TYPE_FIXED_FACTOR == clk_debug_get_clk_type_val(clk_no_in_list))))
	{
		return "[v:0x********]";
	}
	else
	{
		reg_val = clk_debug_get_status_reg_val(clk_no_in_list);
		(void)sprintf_s((char*)(&g_status_reg_val_str[0]), CLK_STATUS_REG_VAL_STR_CHARS_CNT + 1,
					 "[v:0x%08x]", reg_val);

		return &g_status_reg_val_str[0];
	}

}

int clk_debug_status_reg_start_bit_val(unsigned int clk_no_in_list)
{
	enum_clk_type clk_type = 0;
	int status_reg_start_bit = 0;
	struct clk *clk = NULL;

	clk_type = clk_debug_get_clk_type_val(clk_no_in_list);
	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || IS_ERR(clk))
	{
		return -1;
	}

	switch (clk_type)
	{
		case ENUM_CLK_TYPE_GATE:
			status_reg_start_bit = (int)(container_of(clk->hw, struct hi_gateclk, hw)->bit_idx);
			break;
		case ENUM_CLK_TYPE_MUX:
			status_reg_start_bit = (int)(container_of(clk->hw, struct drv_clk_mux, hw)->shift);
			break;
		case ENUM_CLK_TYPE_DIV:
			status_reg_start_bit = (int)(container_of(clk->hw, struct hi_divclk, hw)->shift);
			break;
		default:
			status_reg_start_bit = -1;
			break;

	}

	return status_reg_start_bit;
}

char g_status_reg_start_bit_str[CLK_STATUS_REG_START_BIT_STR_CHARS_CNT + 1] = {'\0'};
char * clk_debug_status_reg_start_bit_str(unsigned int clk_no_in_list)
{
	int start_bit = 0;
	struct clk *clk = NULL;
	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || (IS_ERR(clk)))
	{
		return "**";
	}

	if (  (ENUM_CLK_TYPE_GATE == clk_debug_get_clk_type_val(clk_no_in_list) && (1 == clk->hw->isvirtual))
		||(ENUM_CLK_TYPE_FIXED_RATE == clk_debug_get_clk_type_val(clk_no_in_list))
		||(ENUM_CLK_TYPE_FIXED_FACTOR == clk_debug_get_clk_type_val(clk_no_in_list)))
	{
			return "**";
	}


	start_bit = clk_debug_status_reg_start_bit_val(clk_no_in_list);
	if (-1 != start_bit)
	{
		(void)sprintf_s((char*)(&g_status_reg_start_bit_str[0]), CLK_STATUS_REG_START_BIT_STR_CHARS_CNT + 1,
					 "%02d", start_bit);
	}

	return &g_status_reg_start_bit_str[0];
}

int clk_debug_status_reg_end_bit_val(unsigned int clk_no_in_list)
{
	enum_clk_type clk_type = 0;
	int status_reg_end_bit = 0;
	struct clk *clk = NULL;
	unsigned int mux_mask = 0;
	unsigned int mux_shift = 0;
	unsigned int div_shift = 0;
	unsigned int div_width = 0;

	clk_type = clk_debug_get_clk_type_val(clk_no_in_list);
	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || IS_ERR(clk))
	{
		return -1;
	}

	switch (clk_type)
	{
		case ENUM_CLK_TYPE_GATE:
			status_reg_end_bit = (int)(container_of(clk->hw, struct hi_gateclk, hw)->bit_idx);
			break;
		case ENUM_CLK_TYPE_MUX:
			mux_mask = container_of(clk->hw, struct drv_clk_mux, hw)->mask;
			mux_shift = (unsigned int)(container_of(clk->hw, struct drv_clk_mux, hw)->shift);
			status_reg_end_bit = (int)(mux_shift + clk_debug_clk_fls(mux_mask) - 1);
			break;
		case ENUM_CLK_TYPE_DIV:
			div_shift = (unsigned int)container_of(clk->hw, struct hi_divclk, hw)->shift;
			div_width = (unsigned int)container_of(clk->hw, struct hi_divclk, hw)->width;
			status_reg_end_bit = (int)(div_shift + div_width - 1);
			break;
		default:
			status_reg_end_bit = -1;
			break;

	}

	return status_reg_end_bit;
}

char g_status_reg_end_bit_str[CLK_STATUS_REG_END_BIT_STR_CHARS_CNT + 1] = {'\0'};
char * clk_debug_status_reg_end_bit_str(unsigned int clk_no_in_list)
{
	int end_bit = 0;
	struct clk *clk = NULL;
	clk = clk_debug_get_with_no(clk_no_in_list);
	if ((NULL == clk) || (IS_ERR(clk)))
	{
		return "**";
	}

	if (  (ENUM_CLK_TYPE_GATE == clk_debug_get_clk_type_val(clk_no_in_list) && (1 == clk->hw->isvirtual))
		||(ENUM_CLK_TYPE_FIXED_RATE == clk_debug_get_clk_type_val(clk_no_in_list))
		||(ENUM_CLK_TYPE_FIXED_FACTOR == clk_debug_get_clk_type_val(clk_no_in_list)))
	{
			return "**";
	}


	end_bit = clk_debug_status_reg_end_bit_val(clk_no_in_list);
	if (-1 != end_bit)
	{
		(void)sprintf_s((char*)(&g_status_reg_end_bit_str[0]), CLK_STATUS_REG_END_BIT_STR_CHARS_CNT + 1,
					 "%02d", end_bit);
	}

	return &g_status_reg_end_bit_str[0];
}

#define CLK_STR_LEN     53  /* 52个字符 + 结束符 */
char g_clk_str[CLK_STR_LEN] = {"[fixed_factor][a:0x00000000][v:0x00000000][bit00-00]"};
char * clk_debug_clk_str(unsigned int clk_no_in_list)
{
	char *clk_str = NULL;

	/* 时钟类型 14个字符*/
	clk_str = clk_debug_get_clk_type_str(clk_no_in_list);
	(void)memcpy_s((void *)(&(g_clk_str[0])),
					CLK_TYPE_STR_CHARS_CNT,
					 (const void *)clk_str,
					 CLK_TYPE_STR_CHARS_CNT);

	/* 状态寄存器基址 14个字符 */
	clk_str = clk_debug_get_status_reg_addr_str(clk_no_in_list);
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT])),
					CLK_STATUS_REG_ADDR_STR_CHARS_CNT,
					 (const void *)clk_str,
					 CLK_STATUS_REG_ADDR_STR_CHARS_CNT);


	/* 状态寄存器值 14个字符 */
	clk_str = clk_debug_get_status_reg_val_str(clk_no_in_list);
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT])),
					 CLK_STATUS_REG_VAL_STR_CHARS_CNT,
					 (const void *)clk_str,
					 CLK_STATUS_REG_VAL_STR_CHARS_CNT);

	/* [bit 4个字符 */
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT + CLK_STATUS_REG_VAL_STR_CHARS_CNT])),
					4,
					 (const void *)("[bit"),
					 4);
	/* 结束bit 2个字符*/
	clk_str = clk_debug_status_reg_end_bit_str(clk_no_in_list);
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT + CLK_STATUS_REG_VAL_STR_CHARS_CNT + 4])),
					CLK_STATUS_REG_END_BIT_STR_CHARS_CNT,
					 (const void *)clk_str,
					 CLK_STATUS_REG_END_BIT_STR_CHARS_CNT);
	/* -  1个字符 */
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT + CLK_STATUS_REG_VAL_STR_CHARS_CNT + 4 + CLK_STATUS_REG_END_BIT_STR_CHARS_CNT])),
					1,
					 (const void *)("-"),
					 1);


	/* 开始bit 2个字符 */
	clk_str = clk_debug_status_reg_start_bit_str(clk_no_in_list);
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT + CLK_STATUS_REG_VAL_STR_CHARS_CNT + 4 + CLK_STATUS_REG_END_BIT_STR_CHARS_CNT + 1])),
					CLK_STATUS_REG_START_BIT_STR_CHARS_CNT,
					 (const void *)clk_str,
					 CLK_STATUS_REG_START_BIT_STR_CHARS_CNT);
	/* ] 1个字符 + 结束符*/
	(void)memcpy_s((void *)(&(g_clk_str[0 + CLK_TYPE_STR_CHARS_CNT + CLK_STATUS_REG_ADDR_STR_CHARS_CNT + CLK_STATUS_REG_VAL_STR_CHARS_CNT + 4 + CLK_STATUS_REG_END_BIT_STR_CHARS_CNT + 1 + CLK_STATUS_REG_START_BIT_STR_CHARS_CNT])),
					2,
					 (const void *)("]"),
					 2);

	return (char *)(&(g_clk_str[0]));
}

void clk_debug_print_children_clk(unsigned int clk_no_in_list)
{
	unsigned int buf[50] = {0};
	unsigned int children_sum = 0;
	unsigned int clk_no = 0;
	unsigned int i = 0;
	static unsigned int clk_level = 0;

	for (i = 0; i < clk_level * 20; i++)
	{
		printf(" ");
	}



	printf("%d-%s-%s ", clk_level, clk_debug_clk_str(clk_no_in_list), clk_debug_get_name_with_no(clk_no_in_list));

	clk_no = clk_no_in_list;
	(void)clk_debug_get_curr_children_no(clk_no, (unsigned int *)(&(buf[0])), (unsigned int *)&children_sum);
	if (0 == children_sum)  /* 没有子时钟 */
	{
		printf("\n");
		return ;
	}
	else
	{
		clk_level++;
		for (i = 0; i < children_sum; i++)
		{
			clk_no = buf[i];
			clk_debug_print_children_clk(clk_no);
		}
		clk_level--;
	}



	return ;
}

void clk_debug_show_clk_tree(void)
{
	struct clk_lookup     *ptr_clk_lookup = NULL;
	unsigned int          fixed_rate_clk_sum = 0;      /* fixed-rate 时钟总数 */
	unsigned int          fixed_rate_clk_no[20] = {0}; /* fixed-rate时钟的编号 */
	unsigned int          i = 0;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		if (CLK_IS_ROOT & ptr_clk_lookup->clk->flags)
		{
			fixed_rate_clk_no[fixed_rate_clk_sum] = ptr_clk_lookup->clk_no;
			fixed_rate_clk_sum++;
			printf("root clk no = %d name = %s\n", ptr_clk_lookup->clk_no, ptr_clk_lookup->con_id);
		}
	}

	for (i = 0; i < fixed_rate_clk_sum; i++)
	{
		clk_debug_print_children_clk(fixed_rate_clk_no[i]);
	}


	return ;
}

/*==========================性能测试开始================================*/
#define CLK_CNT_MAX    100  /* 一般不会超过100个时钟 */
const char *g_clk_name[CLK_CNT_MAX] = {NULL};

#define CLK_PERF_TEST_CNT  1000

unsigned int g_slice_start[CLK_PERF_TEST_CNT] = {0};
unsigned int g_slice_end[CLK_PERF_TEST_CNT] = {0};
unsigned int g_slice_delta[CLK_PERF_TEST_CNT] = {0};

unsigned int g_max_slice_delta[CLK_CNT_MAX] = {0};  /* 每个时钟的最大操作slice时间 */
unsigned int g_min_slice_delta[CLK_CNT_MAX] = {0};  /* 每个时钟的最小操作slice时间 */
unsigned int g_avg_slice_delta[CLK_CNT_MAX] = {0};  /* 每个时钟的平均操作slice时间 */

enum enum_perf_type{
	ENUM_PERF_GET,
	ENUM_PERF_EN,
	ENUM_PERF_DIS,
	ENUM_PERF_GET_RATE,
	ENUM_PERF_ROUND_RATE,
	ENUM_PERF_SET_RATE,
	ENUM_PERF_GET_PARENT,
	ENUM_PERF_SET_PARENT
};

void clk_debug_init_clk_names(void)
{
	struct clk_lookup     *ptr_clk_lookup;

	list_for_each_entry(ptr_clk_lookup, &balong_clocks, node)
	{
		g_clk_name[ptr_clk_lookup->clk_no] = ptr_clk_lookup->con_id;
	}

	return ;
}

int clk_debug_get_max(unsigned int data_array[], unsigned int valid_data_cnt, unsigned int* max_val)
{
	unsigned int this_max = data_array[0];
	unsigned int j = 0;

	for (j = 0; j < valid_data_cnt; j++)
	{
		if (this_max < data_array[j])
		{
			this_max = data_array[j];
		}

	}

	*max_val = this_max;

	return 0;
}

int clk_debug_get_min(unsigned int data_array[], unsigned int valid_data_cnt, unsigned int* min_val)
{
	unsigned int this_min = data_array[0];
	unsigned int j = 0;

	for (j = 0; j < valid_data_cnt; j++)
	{

		if (this_min > data_array[j])
		{
			this_min = data_array[j];
		}

	}

	*min_val = this_min;

	return 0;
}

int clk_debug_get_avg(unsigned int data_array[], unsigned int valid_data_cnt, unsigned int* avg)
{
	unsigned int this_avg = 0;
	unsigned long long sum = 0;
	unsigned int j = 0;

	for (j = 0; j < valid_data_cnt; j++)
	{
		sum += (unsigned long long)data_array[j];
	}

	this_avg = (unsigned int)(sum / valid_data_cnt);

	*avg = this_avg;

	return 0;
}

void clk_print_perf_result(double max_val, double min_val, double avg)
{
	clk_printf("max = %f ns\n", max_val);
	clk_printf("min = %f ns\n", min_val);
	clk_printf("avg = %f ns\n", avg);

	return ;
}

struct clk* g_clk[CLK_CNT_MAX] = {NULL};
unsigned int g_clks_cnt = 0;
//spinlock_t g_spin_lock;
unsigned long g_flags = 0;

#define get_max_min_avg   \
	(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[i]);  \
	(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[i]);  \
	(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[i]);

#define get_max_min_avg_print  \
	(void)clk_debug_get_max(g_max_slice_delta, cnt, &all_clks_delta_max);  \
	(void)clk_debug_get_min(g_min_slice_delta, cnt, &all_clks_delta_min);  \
	(void)clk_debug_get_avg(g_avg_slice_delta, cnt, &all_clks_delta_avg);  \
	time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;  \
	time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;  \
	time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;  \
	clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

void clk_debug_get_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	unsigned int cnt = 0;

	clk_printf("clk_debug_get_perf starting...\n");

	for (i = 0; i < CLK_CNT_MAX; i++)
	{
		if (g_clk_name[i])
		{
			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{
				start_slice[j] = bsp_get_slice_value_hrt();
				g_clk[i] = clk_get(NULL, g_clk_name[i]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

			}

			get_max_min_avg;
		}
		else
		{
			break;  /* 遇到第一个NULL就不再继续 */
		}
	}

	/* 此时的i就是时钟的个数 */
	g_clks_cnt = i;
	cnt = g_clks_cnt;
	get_max_min_avg_print;

	clk_printf("clk_debug_get_perf end\n");

	return ;
}

/* 可用于测试开关的时钟 */
const char * g_clks_used_to_test_en_dis[] =
{
	"tm9_clk",
	"hsuart_clk",
	"uicc_clk"
};

/* 可用于测试频率相关的时钟 */
const char * g_clks_used_to_test_rate[] =
{
	"cipher_clk"
};

/* 可用于测试父时钟相关的时钟 */
const char * g_clks_used_to_test_parent[] =
{
	"a9_refclk"
};

void clk_debug_show_en_cnt(void)
{
	unsigned int i = 0 ;

	for (i = 0; i < g_clks_cnt; i++)
	{
		clk_printf("i = %d name = %s en_cnt = %d\n", i, g_clk[i]->name, g_clk[i]->enable_count);
	}
	return ;
}

void clk_debug_en_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	unsigned int original_en_cnt = 0;
	struct clk *pclk = NULL;
	unsigned int cnt = 0;


	clk_printf("clk_debug_en_perf starting...\n");

	for (i = 0; i < sizeof(g_clks_used_to_test_en_dis) / sizeof(const char *); i++)
	{
			/* 将原来的引用计数记下来 */
			pclk = clk_get(NULL, g_clks_used_to_test_en_dis[i]);
			if (IS_ERR(pclk))
			{
				continue ;
			}
			original_en_cnt = pclk->enable_count;
			for (k = 0; k < original_en_cnt; k++)
			{
				clk_disable(pclk);
			}

			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{

				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_enable(pclk);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

				/* 关闭 */
				clk_disable(pclk);

			}

			/* 恢复时钟原来的引用计数 */
			for (k = 0; k < original_en_cnt; k++)
			{
				clk_enable(pclk);
			}

			get_max_min_avg;
	}

	cnt = sizeof(g_clks_used_to_test_en_dis) / sizeof(const char *);
	get_max_min_avg_print
	clk_printf("clk_debug_en_perf end\n");

	return ;
}

void clk_debug_dis_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	int k = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	unsigned int original_en_cnt = 0;
	struct clk *pclk = NULL;
	unsigned int cnt = 0;


	clk_printf("clk_debug_dis_perf starting...\n");

	for (i = 0; i < sizeof(g_clks_used_to_test_en_dis) / sizeof(const char *); i++)
	{

			/* 将原来的引用计数记下来 */
			pclk = clk_get(NULL, g_clks_used_to_test_en_dis[i]);
			if (IS_ERR(pclk))
			{
				continue ;
			}
			original_en_cnt = pclk->enable_count;
			for (k = 0; k < original_en_cnt; k++)
			{
				clk_disable(pclk);
			}

			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{
				(void)clk_enable(pclk);
				start_slice[j] = bsp_get_slice_value_hrt();
				clk_disable(pclk);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

			}

			/* 恢复时钟原来的引用计数 */
			for (k = 0; k < original_en_cnt; k++)
			{
				clk_enable(pclk);
			}

			get_max_min_avg;
	}

	cnt = sizeof(g_clks_used_to_test_en_dis) / sizeof(const char *);
	get_max_min_avg_print

	clk_printf("clk_debug_dis_perf end\n");

	return ;
}

void clk_debug_get_rate_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;


	clk_printf("clk_debug_get_rate_perf starting...\n");

	for (i = 0; i < g_clks_cnt; i++)
	{
			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{
				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_get_rate(g_clk[i]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

			}

			(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[i]);
			(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[i]);
			(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[i]);
	}

	(void)clk_debug_get_max(g_max_slice_delta, g_clks_cnt, &all_clks_delta_max);
	(void)clk_debug_get_min(g_min_slice_delta, g_clks_cnt, &all_clks_delta_min);
	(void)clk_debug_get_avg(g_avg_slice_delta, g_clks_cnt, &all_clks_delta_avg);

	time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;
	time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;
	time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;

	clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

	clk_printf("clk_debug_get_rate_perf end\n");

	return ;
}

#define VALID_DIV_VAL_CNT_MAX   32

int clk_debug_get_valid_rate(struct clk* pclk, unsigned long *valid_rate, unsigned int *rate_cnt)
{
	const struct clk_div_table * div_table = (const struct clk_div_table *)(container_of(pclk->hw, struct hi_divclk, hw)->table);
	const struct clk_div_table * pdiv_table;
	unsigned int local_rate_cnt = 0;
	unsigned long curr_rate = 0;
	unsigned int curr_div_val = 0;
	unsigned int valid_div_val[VALID_DIV_VAL_CNT_MAX] = {0};
	int i = 0;

	curr_rate = clk_get_rate(pclk);
	if (0 == curr_rate)
	{
		clk_printf("rate is 0\n");
		return 1;
	}
	curr_div_val = clk_get_parent(pclk)->rate / curr_rate;


	for (pdiv_table = div_table; pdiv_table->div_val; pdiv_table++)
	{
		valid_div_val[local_rate_cnt] = pdiv_table->div_val;
		local_rate_cnt++;
	}

	*rate_cnt = local_rate_cnt;

	for (i = 0; i < local_rate_cnt; i++)
	{
		if (0 == valid_div_val[i])
		{
			continue;
		}
		valid_rate[i] = curr_rate * curr_div_val / valid_div_val[i];
		clk_printf("valid_div_val = %d rate = %d\n", valid_div_val[i], valid_rate[i]);
	}

	return 0;

}

void clk_debug_round_rate_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	struct clk *pclk = NULL;
	unsigned long rate_to_round[VALID_DIV_VAL_CNT_MAX] = {0};
	unsigned int actual_rate_to_round_cnt = 0;
	int rate_index = 0;


	clk_printf("clk_debug_round_rate_perf starting...\n");

	for (i = 0; i < sizeof(g_clks_used_to_test_rate) / sizeof(const char *); i++)
	{

		clk_printf("dealing clk %s...\n", g_clks_used_to_test_rate[i]);
		pclk = clk_get(NULL, g_clks_used_to_test_rate[i]);
		if (IS_ERR(pclk))
		{
			continue ;
		}

		(void)clk_debug_get_valid_rate(pclk, &(rate_to_round[0]), &actual_rate_to_round_cnt);
		for (rate_index = 0; rate_index < actual_rate_to_round_cnt; rate_index++)
		{
			clk_printf("dealing rate %d...\n", rate_to_round[rate_index]);
			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{
				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_round_rate(pclk, rate_to_round[rate_index]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);
			}
			/* 本时钟，本频率 */
			(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[rate_index]);
			(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[rate_index]);
			(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[rate_index]);
		}

		/* 本时钟，在这几个rate里找*/
		(void)clk_debug_get_max(g_max_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_max);
		(void)clk_debug_get_min(g_min_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_min);
		(void)clk_debug_get_avg(g_avg_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_avg);

		time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;
		time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;
		time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;

		clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

	}

	clk_printf("clk_debug_round_rate_perf end\n");

	return ;
}

void clk_debug_set_rate_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	struct clk *pclk = NULL;
	unsigned long rate_to_round[VALID_DIV_VAL_CNT_MAX] = {0};
	unsigned int actual_rate_to_round_cnt = 0;
	int rate_index = 0;
	unsigned long curr_rate = 0;

	clk_printf("clk_debug_set_rate_perf starting...\n");
	for (i = 0; i < sizeof(g_clks_used_to_test_rate) / sizeof(const char *); i++)
	{
		clk_printf("dealing clk %s...\n", g_clks_used_to_test_rate[i]);
		pclk = clk_get(NULL, g_clks_used_to_test_rate[i]);
		if (IS_ERR(pclk))
		{
			continue ;
		}

		curr_rate = clk_get_rate(pclk);

		(void)clk_debug_get_valid_rate(pclk, &(rate_to_round[0]), &actual_rate_to_round_cnt);
		for (rate_index = 0; rate_index < actual_rate_to_round_cnt; rate_index++)
		{
			clk_printf("dealing rate %d...\n", rate_to_round[rate_index]);
			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{
				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_set_rate(pclk, rate_to_round[rate_index]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

				/* 恢复原频率 */
				(void)clk_set_rate(pclk, curr_rate);
			}
			/* 本时钟，本频率 */
			(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[rate_index]);
			(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[rate_index]);
			(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[rate_index]);

		}

		/* 本时钟，在这几个rate里找*/
		(void)clk_debug_get_max(g_max_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_max);
		(void)clk_debug_get_min(g_min_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_min);
		(void)clk_debug_get_avg(g_avg_slice_delta, actual_rate_to_round_cnt, &all_clks_delta_avg);

		time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;
		time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;
		time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;

		clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

	}

	clk_printf("clk_debug_set_rate_perf end\n");

	return ;
}

void clk_debug_get_parent_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;


	clk_printf("clk_debug_get_parent_perf starting...\n");

	for (i = 0; i < g_clks_cnt; i++)
	{

			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{

				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_get_parent(g_clk[i]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

			}

			(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[i]);
			(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[i]);
			(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[i]);
	}

	(void)clk_debug_get_max(g_max_slice_delta, g_clks_cnt, &all_clks_delta_max);
	(void)clk_debug_get_min(g_min_slice_delta, g_clks_cnt, &all_clks_delta_min);
	(void)clk_debug_get_avg(g_avg_slice_delta, g_clks_cnt, &all_clks_delta_avg);

	time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;
	time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;
	time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;

	clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

	clk_printf("clk_debug_get_parent_perf end\n");

	return ;
}

#define VALID_PARENTS_CNT  10

void clk_debug_set_parent_perf(void)
{
	unsigned int start_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int end_slice[CLK_PERF_TEST_CNT] = {0};
	unsigned int delta_slice[CLK_PERF_TEST_CNT] = {0};
	double time_max_in_ns = 0.0;
	double time_min_in_ns = 0.0;
	double time_avg_in_ns = 0.0;
	int i = 0;
	int j = 0;
	unsigned int all_clks_delta_max = 0;
	unsigned int all_clks_delta_min = 0;
	unsigned int all_clks_delta_avg = 0;
	struct clk* curr_parent = NULL;
	struct clk* pclk = NULL;
	unsigned int parents_cnt = 0;
	int parent_index = 0;

	clk_printf("clk_debug_set_parent_perf starting...\n");
	for (i = 0; i < sizeof(g_clks_used_to_test_parent) / sizeof(const char *); i++)
	{
		pclk = clk_get(NULL, g_clks_used_to_test_parent[i]);
		if (IS_ERR(pclk))
		{
			continue ;
		}
		clk_printf("dealing clk %s\n", pclk->name);

		parents_cnt = pclk->num_parents;
		curr_parent = clk_get_parent(pclk);

		for (parent_index = 0; parent_index < parents_cnt; parent_index++)
		{
			clk_printf("dealing parent %s\n", pclk->parents[parent_index]->name);
			for (j = 0; j < CLK_PERF_TEST_CNT; j++)
			{

				start_slice[j] = bsp_get_slice_value_hrt();
				(void)clk_set_parent(pclk, pclk->parents[parent_index]);
				end_slice[j] = bsp_get_slice_value_hrt();
				delta_slice[j] = get_timer_slice_delta(start_slice[j], end_slice[j]);

				/* 恢复原父时钟 */
				(void)clk_set_parent(pclk, curr_parent);
			}
			(void)clk_debug_get_max(delta_slice, CLK_PERF_TEST_CNT, &g_max_slice_delta[parent_index]);
			(void)clk_debug_get_min(delta_slice, CLK_PERF_TEST_CNT, &g_min_slice_delta[parent_index]);
			(void)clk_debug_get_avg(delta_slice, CLK_PERF_TEST_CNT, &g_avg_slice_delta[parent_index]);

		}
		(void)clk_debug_get_max(g_max_slice_delta, parents_cnt, &all_clks_delta_max);
		(void)clk_debug_get_min(g_min_slice_delta, parents_cnt, &all_clks_delta_min);
		(void)clk_debug_get_avg(g_avg_slice_delta, parents_cnt, &all_clks_delta_avg);

		time_max_in_ns = (double)all_clks_delta_max * 1000 / 19.2;
		time_min_in_ns = (double)all_clks_delta_min * 1000 / 19.2;
		time_avg_in_ns = (double)all_clks_delta_avg * 1000 / 19.2;

		clk_print_perf_result(time_max_in_ns, time_min_in_ns, time_avg_in_ns);

	}

	clk_printf("clk_debug_set_parent_perf end\n");

	return ;
}

void clk_debug_interface_perf(void)
{
	//spin_lock_init(&g_spin_lock);

	/* 获取时钟的名字 */
	clk_debug_init_clk_names();

	/* clk_get */
	clk_debug_get_perf();

	/* clk_enable */
	clk_debug_en_perf();

	/* clk_disable */
	clk_debug_dis_perf();

	/* clk_get_rate */
	clk_debug_get_rate_perf();

	/* clk_round_rate */
	clk_debug_round_rate_perf();

	/* clk_set_rate */
	clk_debug_set_rate_perf();

	/* clk_get_parent */
	clk_debug_get_parent_perf();

	/* clk_set_parent */
	clk_debug_set_parent_perf();

}

/*==========================性能测试结束================================*/

#define CRG_DFS6_PD_SHIFT         (0)
#define CRG_DFS6_CTRL3            (u32)(0x90000000+0x244)
void clk_debug_close_usbpll(void)
{
	u32 val = 0;
	val = readl(CRG_DFS6_CTRL3);
	val |= (1 << CRG_DFS6_PD_SHIFT);
	writel(val, CRG_DFS6_CTRL3);
}

