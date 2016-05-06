/*lint --e{123,413,506,774}*/
#include <securec.h>
#include <sre_mem.h>
#include <osl_spinlock.h>
#include <osl_bug.h>
#include <osl_err.h>
#include <bsp_dpm.h>
#include <bsp_slice.h>
#include <bsp_rsracc.h>
#include <bsp_clk.h>
#include <of.h>
#include "rsr_acc.h"

#define MOD_NAME "rsracc"
#define rsracc_print(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RSRACC, "<%s> "fmt" ", MOD_NAME, ##__VA_ARGS__))

#define trace_slice(p) \
	do{ \
		p = bsp_get_slice_value(); \
	}while(0)
struct rsracc_debug_s
{
	u32 suspend_begin_slice[2];/*suspend_begin start(0)\end(1) slice		*/
	u32 suspend_end_slice[2];  /*suspend_end start(0)\end(1) slice			*/
	u32 resume_begin_slice[2]; /*resume_begin start(0)\end(1) slice			*/
	u32 resume_end_slice[2];   /*resume_end  start(0)\end(1) slice			*/
	u32 wait_finish_slice[2];  /*rsracc wait finish  start(0)\end(1) slice	*/
	u32 wait_finish_max;       /*max rsracc wait finish						*/
	u32 suspend_begin_fail_cnt;/*suspend begin fail times						*/
};

struct rsracc_ctrl_s{
	void* base;
	struct list_head sus_end_list;
	struct list_head    desc_list;
	u32 desc_bd_cnt;		 /*the number of bd descriptor  */
	u32		 bd_cnt;		 /*the number valid bd to rsracc*/
	u32 support_rsracc;
	struct clk *rsracc_clk;
	spinlock_t lock;
	struct rsr_acc_bd_s *bds_base;
	void*   pre_alloc_uncache_ddr;/*rsracc pre-alloc unchache ddr,assign to bd which needed*/
	u32          pre_alloc_cursor;/*the index of pre_alloc_uncache_ddr assined			*/
	bool      is_inited;
	bool  lazy_build_bd;
	bool is_rsracc_enabled;
	bool need_check_result;
	struct rsracc_debug_s debug;
}rsracc_ctrl;

static inline s32 rsracc_assign_bak_addr(rsr_acc_description *bd_descri)
{
	if(rsracc_ctrl.pre_alloc_cursor+bd_descri->reg_num>= PRE_MALLOC_UNCACHE_DDR_SIZE)
	{
		rsracc_print("space overflow,cannot assign bak addr,%s\n",bd_descri->name);
		rsracc_print("cursor:0x%x,reg_num:0x%x\n",rsracc_ctrl.pre_alloc_cursor,bd_descri->reg_num);
		return BSP_ERROR;
	}
	bd_descri->bak_addr = (u32*)rsracc_ctrl.pre_alloc_uncache_ddr + rsracc_ctrl.pre_alloc_cursor;
	rsracc_ctrl.pre_alloc_cursor += bd_descri->reg_num;
	return BSP_OK;
}
static s32 __rsracc_build_bd(struct rsr_acc_bd_s *bds_base,rsr_acc_description *bd_descri)
{
	s32 ret = BSP_OK;
	/*wait */
	if(bd_descri->is_wait_bd)
	{
		bds_base->cfg.bd_oper = 4;/*wait*/
		bds_base->bd_flow_operation = bd_descri->wait_cycle;/*wait cycle*/
		bds_base->cfg.bd_type = 3;
	}
	/*negation_resume*/
	else if(bd_descri->is_negation_resume)
	{
		bds_base->cfg.bd_oper = 3;/*取反restore*/
		bds_base->bd_flow_operation = bd_descri->negation_resume_bitmask;/*取反bit位*/
		bds_base->cfg.bd_type = 2;
	}
	/*save&restore*/
	else if(bd_descri->reg_num)
	{
		bds_base->cfg.bd_oper = bd_descri->bd_valid_flow-1;
		bds_base->cfg.bd_type = 1;
		bds_base->bd_flow_operation = bd_descri->reg_num;
	}
	else
	{}
	bds_base->cfg.bd_flow = bd_descri->bd_valid_flow;
	bds_base->reg_baddr = bd_descri->reg_addr;
	if(bd_descri->need_rsracc_assign_bakaddr)
	{
		ret = rsracc_assign_bak_addr(bd_descri);
		if(ret)
			return BSP_ERROR;
	}
	bds_base->ddr_baddr = bd_descri->bak_addr;
	rsracc_ctrl.bd_cnt++;
	return BSP_OK;
}
static s32 rsracc_build_bd(void)
{
	rsr_acc_description *p = NULL;
	s32 ret = 0;
	u32 i = 0;
	struct rsr_acc_bd_s *last_bd = NULL;
	rsracc_ctrl.pre_alloc_cursor = 0;/*assign from index 0*/
	if(!rsracc_ctrl.desc_bd_cnt)
		return BSP_OK;
	list_for_each_entry(p,&rsracc_ctrl.desc_list,entry)
	{
		if(p->only_ops_in_bd)
			continue;
		else
		{
			ret = __rsracc_build_bd((struct rsr_acc_bd_s *)(rsracc_ctrl.bds_base+i),p);
			if(ret)
			{
				rsracc_print("bd build fail,bd_des name = %s\n",p->name);
				return BSP_ERROR;
			}
			i++;
		}
	}
	last_bd = rsracc_ctrl.bds_base+rsracc_ctrl.bd_cnt -1;
	if(only_valid_resume_flow == (rsr_acc_valid_flow)last_bd->cfg.bd_flow )
	{
		/*in 722chip,there is a use limit,the last bd should not be resume only,otherwise rsracc cannot end the flow*/
		rsracc_print("last bd should not resume only\n");
		BUG_ON(1);/*lint  !e123*/
		return BSP_ERROR;
	}
	return BSP_OK;
}

s32 bsp_rsracc_register(rsr_acc_description *bd_descri,u32 cnt)
{
	int ret = BSP_OK;
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	u32 i = 0;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("init failed,cannot register\n");
		return BSP_ERROR;
	}
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	for(i = 0;i < cnt; i++)
	{
		if(!bd_descri->only_ops_in_bd && rsracc_ctrl.bd_cnt >= MAX_RSR_ACC_BD_CNT)
		{
			spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
			rsracc_print("BD cnt overflow,bd_name=%s\n",bd_descri->name);
			return BSP_ERROR;
		}
		list_for_each_entry(p,&rsracc_ctrl.desc_list,entry)/*lint !e613*/
		{
			if(p->level > bd_descri->level)
				break;
		}
		list_add_tail(&bd_descri->entry,&p->entry);
		rsracc_ctrl.desc_bd_cnt++;
		bd_descri++;
	}
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
	/*if register bd after init_late,should rebuild bd*/	
	if(!rsracc_ctrl.lazy_build_bd)
	{
		rsracc_ctrl.bd_cnt = 0;
		ret = rsracc_build_bd();
	}
	return ret;
}
s32 bsp_rsracc_unregister(rsr_acc_description *bd_descri,u32 cnt)
{
	int ret = BSP_OK;
	unsigned long flags = 0;
	u32 i = 0;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("init failed,cannot unregister\n");
		return BSP_ERROR;
	}
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	for(i = 0;i < cnt; i++)
	{
		list_del(&bd_descri->entry);
		bd_descri++;
	}
	rsracc_ctrl.desc_bd_cnt -= cnt;
	/*if unregister occured after init_late,should rebuild bd*/
	if(!rsracc_ctrl.lazy_build_bd)
	{
		rsracc_ctrl.bd_cnt = 0;
		ret = rsracc_build_bd();
	}
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
	return ret;
}

static void rsracc_enable_trans(enum rsracc_flow_e __flow)
{
	/*if channel has no bd,no need to enable to trans,else set the bd number to reg*/
	if(rsracc_ctrl.bd_cnt)
		writel(rsracc_ctrl.bd_cnt,(u32)rsracc_ctrl.base+BD_LEN_OFFSET(RSR_ACC_CHANNEL_0));
	else
		return;
	/*set bd base addr to reg*/
	writel((u32)rsracc_ctrl.bds_base,(u32)rsracc_ctrl.base+BD_BASE_OFFSET(RSR_ACC_CHANNEL_0));
	/*start suspend or resume,begin to trans bd data*/
	writel((u32)__flow,(u32)rsracc_ctrl.base+CTRL_OFFSET(RSR_ACC_CHANNEL_0));
	rsracc_ctrl.is_rsracc_enabled = true;
}
static s32 result_compare(void* source,void* dest,u32 count){
	u32* temp1=NULL,*temp2=NULL;
	u32 cnt = 0;
	s32 flag = 0;
	temp1 = (u32*)source;
	temp2 = (u32*)dest;
	rsracc_print("check:src:0x%x,dest:0x%x\n",source,dest);
	while(cnt < count){
		if(*temp1 != *temp2){
			flag = -1;
			rsracc_print("result_compare error at %d data,source=0x%x,dest=0x%x\n",cnt,*temp1,*temp2);
		}
		temp1++;
		temp2++;
		cnt++;
	}
	return flag;
}

static inline void check_result(struct list_head *list,enum rsracc_flow_e __flow)
{
	s32 ret = 0;
	rsr_acc_description *p = NULL;
	list_for_each_entry(p,list,entry)
	{
		if(p->reg_num&&p->bd_valid_flow == both_save_and_resume_flow)
		{
			ret = result_compare((void*)p->bak_addr,(void*)p->reg_addr,p->reg_num);
		}
		if(__flow == resume_flow)
		{
			if(p->is_negation_resume)
			{
				if((*(p->bak_addr))&(*(p->reg_addr))&p->negation_resume_bitmask)
				{
					rsracc_print("negate resume failed,bak=0x%x,reg=0x%x,bitmask=0x%x\n",*(p->bak_addr),*(p->reg_addr),p->negation_resume_bitmask);
					ret = 1;
				}
			}
		}
		if(ret)
			BUG_ON(1);/*lint !e123*/
	}
}
static inline void rsracc_wait_finish_and_disable(void)
{
	u32 ret = 0,delta = 0;
	/*only enabled before,wait finish is meaningful*/
	if(rsracc_ctrl.is_rsracc_enabled)
	{
		trace_slice(rsracc_ctrl.debug.wait_finish_slice[0]);
		do{
			ret = readl((u32)rsracc_ctrl.base+INT_STATUS_OFFSET);
		}while(ret!=0x1);
		trace_slice(rsracc_ctrl.debug.wait_finish_slice[1]);
		delta = get_timer_slice_delta(rsracc_ctrl.debug.wait_finish_slice[0],rsracc_ctrl.debug.wait_finish_slice[1]);
		if(delta>rsracc_ctrl.debug.wait_finish_max)
			rsracc_ctrl.debug.wait_finish_max = delta;
		writel(0x0,(unsigned)rsracc_ctrl.base+CTRL_OFFSET(RSR_ACC_CHANNEL_0));
		rsracc_ctrl.is_rsracc_enabled = false;
	}
}
void bsp_rsracc_suspend_halt(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	rsracc_wait_finish_and_disable();
	list_for_each_entry_reverse(p,&rsracc_ctrl.sus_end_list,entry)
	{
		if(p->ops->resume_end)
		{
			trace_slice(p->ops->debug.resume_end_slice[0]);
			p->ops->resume_end(p);
			trace_slice(p->ops->debug.resume_end_slice[1]);
		}
	}
	list_splice_init(&rsracc_ctrl.sus_end_list,&rsracc_ctrl.desc_list);
	if(drv_clk_is_enabled(rsracc_ctrl.rsracc_clk))
		clk_disable(rsracc_ctrl.rsracc_clk);
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
}
s32 bsp_rsracc_suspend_begin(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL ,*next = NULL;
	s32 ret = BSP_OK;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("not init \n");
		return BSP_ERROR;
	}
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	trace_slice(rsracc_ctrl.debug.suspend_begin_slice[0]);
	if(rsracc_ctrl.desc_bd_cnt)
	{
		list_for_each_entry_safe(p,next,&rsracc_ctrl.desc_list,entry)
		{
			if(p->ops->suspend_begin)
			{
				trace_slice(p->ops->debug.suspend_begin_slice[0]);
				ret = p->ops->suspend_begin(p);
				trace_slice(p->ops->debug.suspend_begin_slice[1]);
				if(ret)
				{
					p->ops->debug.suspend_begin_fail_times++;
					trace_slice(p->ops->debug.suspend_begin_fail_slice);
					rsracc_ctrl.debug.suspend_begin_fail_cnt++;
					spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
					bsp_rsracc_suspend_halt();
					return BSP_ERROR;
				}
				else
					list_move_tail(&p->entry,&rsracc_ctrl.sus_end_list);
			}		
		}
		if(clk_enable(rsracc_ctrl.rsracc_clk))
		{
			rsracc_print("enable clk failed\n");
			return BSP_ERROR;
		}
		rsracc_enable_trans(suspend_flow);
	}
	trace_slice(rsracc_ctrl.debug.suspend_begin_slice[1]);
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
	return BSP_OK;
}
void bsp_rsracc_suspend_end(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	trace_slice(rsracc_ctrl.debug.suspend_end_slice[0]);
	if(rsracc_ctrl.desc_bd_cnt)
	{	
		rsracc_wait_finish_and_disable();
		list_for_each_entry(p,&rsracc_ctrl.sus_end_list,entry)
		{
			if(p->ops->suspend_end)
			{
				trace_slice(p->ops->debug.suspend_end_slice[0]);
				p->ops->suspend_end(p);
				trace_slice(p->ops->debug.suspend_end_slice[1]);
			}
		}	
	}
	trace_slice(rsracc_ctrl.debug.suspend_end_slice[1]);
	clk_disable(rsracc_ctrl.rsracc_clk);
	if(rsracc_ctrl.need_check_result)
		check_result(&rsracc_ctrl.sus_end_list,suspend_flow);
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
}

void bsp_rsracc_resume_begin(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	trace_slice(rsracc_ctrl.debug.resume_begin_slice[0]);
	if(clk_enable(rsracc_ctrl.rsracc_clk))
	{
		BUG();
	}
	/*ensure rsracc disabled*/
	writel(0x0,(unsigned)rsracc_ctrl.base+CTRL_OFFSET(RSR_ACC_CHANNEL_0));
	if(rsracc_ctrl.desc_bd_cnt)
	{	
		list_for_each_entry_reverse(p,&rsracc_ctrl.sus_end_list,entry)
		{
			if(p->ops->resume_begin)
			{
				trace_slice(p->ops->debug.resume_begin_slice[0]);
				p->ops->resume_begin(p);
				trace_slice(p->ops->debug.resume_begin_slice[1]);
			}
		}
		list_splice_init(&rsracc_ctrl.sus_end_list,&rsracc_ctrl.desc_list);
		rsracc_enable_trans(resume_flow);
	}
	trace_slice(rsracc_ctrl.debug.resume_begin_slice[1]);
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
}
void bsp_rsracc_resume_end(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	trace_slice(rsracc_ctrl.debug.resume_end_slice[0]);
	if(rsracc_ctrl.desc_bd_cnt)
	{
		rsracc_wait_finish_and_disable();
		list_for_each_entry_reverse(p,&rsracc_ctrl.desc_list,entry)
		{
			if(p->ops->resume_end)
			{
				trace_slice(p->ops->debug.resume_end_slice[0]);
				p->ops->resume_end(p);
				trace_slice(p->ops->debug.resume_end_slice[1]);
			}
		}
	}
	trace_slice(rsracc_ctrl.debug.resume_end_slice[1]);
	clk_disable(rsracc_ctrl.rsracc_clk);
	if(rsracc_ctrl.need_check_result)
		check_result(&rsracc_ctrl.desc_list,resume_flow);
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
}
bool bsp_rsracc_support(void)
{
	return rsracc_ctrl.support_rsracc;
}

void bsp_rsracc_init(void)
{
	struct device_node *node = NULL;
	char* rsr_acc_name = "hisilicon,rsr_acc_balong";
	void *iomap_node = NULL;
	s32 ret = 0;
	(void)memset_s((void*)&rsracc_ctrl,sizeof(struct rsracc_ctrl_s),0x0,sizeof(struct rsracc_ctrl_s));
	node = of_find_compatible_node(NULL, NULL, rsr_acc_name);
	if(!node)
	{
		rsracc_print("find node failed\n");
		return ;
	}
	iomap_node = of_iomap(node, 0);
	if (NULL == iomap_node)
	{
		rsracc_print("of_iomap failed.\n");
		return ;
	}
	ret = of_property_read_u32(node, "support", &rsracc_ctrl.support_rsracc);
	if (ret)
	{
		rsracc_print("support read failed.\n");
		return ;
	}
	rsracc_ctrl.base = iomap_node;
	rsracc_ctrl.rsracc_clk = (struct clk *)clk_get(NULL,"rsracc_clk");
	if(IS_ERR(rsracc_ctrl.rsracc_clk))
	{
		rsracc_print("rsracc clk cannot get, 0x%x.\n", rsracc_ctrl.rsracc_clk);
		return ;
	}
	spin_lock_init(&rsracc_ctrl.lock);
	INIT_LIST_HEAD(&(rsracc_ctrl.sus_end_list));
	INIT_LIST_HEAD(&(rsracc_ctrl.desc_list));
	rsracc_ctrl.bds_base = (struct rsr_acc_bd_s*)SRE_MemUncacheAlloc(sizeof(struct rsr_acc_bd_s)*MAX_RSR_ACC_BD_CNT,MEM_ADDR_ALIGN_4K);
	rsracc_ctrl.pre_alloc_uncache_ddr = (void*)SRE_MemUncacheAlloc(sizeof(u32)*PRE_MALLOC_UNCACHE_DDR_SIZE,MEM_ADDR_ALIGN_4K);
	if(!rsracc_ctrl.bds_base||!rsracc_ctrl.pre_alloc_uncache_ddr)
	{
		rsracc_print("malloc failed\n");
		return;
	}
	(void)memset_s((void*)rsracc_ctrl.bds_base,(size_t)(sizeof(struct rsr_acc_bd_s)*MAX_RSR_ACC_BD_CNT),0x0,(size_t)(sizeof(struct rsr_acc_bd_s)*MAX_RSR_ACC_BD_CNT));
	(void)memset_s((void*)rsracc_ctrl.pre_alloc_uncache_ddr,(size_t)(sizeof(u32)*PRE_MALLOC_UNCACHE_DDR_SIZE),0x0,(size_t)(sizeof(u32)*PRE_MALLOC_UNCACHE_DDR_SIZE));
	rsracc_ctrl.is_inited = true;
	rsracc_ctrl.lazy_build_bd = true;
	rsracc_ctrl.need_check_result = false;
	rsracc_print("init ok\n");
}

void bsp_rsracc_init_late(void)
{
	s32 ret = 0;
	unsigned long flags = 0;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("init failed\n");
		return;
	}
	spin_lock_irqsave(&rsracc_ctrl.lock,flags);
	ret = rsracc_build_bd();
	if(ret)
	{
		rsracc_print("init late(build bd) failed\n");
		rsracc_ctrl.is_inited = false;
		spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
		return;
	}
	rsracc_ctrl.lazy_build_bd = false;
	spin_unlock_irqrestore(&rsracc_ctrl.lock,flags);
	rsracc_print("init late ok\n");
}
void bsp_rsracc_set_checkflag(bool flag)
{
	rsracc_ctrl.need_check_result = flag;
}

void bsp_rsracc_show(void)
{
	rsr_acc_description *p = NULL;
	rsracc_print("name    level  bak_addr   reg_base reg_num \n");
	list_for_each_entry(p,&rsracc_ctrl.desc_list,entry)
	{
		rsracc_print("%s   %d   0x%x    0x%x   %d\n",p->name,p->level,p->bak_addr,p->reg_addr,p->reg_num);
	}
	rsracc_print("current cursor:0x%x\n",rsracc_ctrl.pre_alloc_cursor);
	rsracc_print("suspend begin fail    :0x%x \n",rsracc_ctrl.debug.suspend_begin_fail_cnt);
	rsracc_print("suspend_begin_start:0x%x \n",rsracc_ctrl.debug.suspend_begin_slice[0]);
	rsracc_print("suspend_begin_end  :0x%x \n",rsracc_ctrl.debug.suspend_begin_slice[1]);
	rsracc_print("suspend_end_start  :0x%x \n",rsracc_ctrl.debug.suspend_end_slice[0]);
	rsracc_print("suspend_end_end    :0x%x \n",rsracc_ctrl.debug.suspend_end_slice[1]);
	rsracc_print("resume_begin_start :0x%x \n",rsracc_ctrl.debug.resume_begin_slice[0]);
	rsracc_print("resume_begin_end   :0x%x \n",rsracc_ctrl.debug.resume_begin_slice[1]);
	rsracc_print("resume_end_start   :0x%x \n",rsracc_ctrl.debug.resume_begin_slice[0]);
	rsracc_print("resume_end_end     :0x%x \n",rsracc_ctrl.debug.resume_end_slice[1]);
	rsracc_print("wait_finish_start  :0x%x \n",rsracc_ctrl.debug.wait_finish_slice[0]);
	rsracc_print("wait_finish_end    :0x%x \n",rsracc_ctrl.debug.wait_finish_slice[1]);
	rsracc_print("wait_finish_max    :0x%x \n",rsracc_ctrl.debug.wait_finish_max);
}

