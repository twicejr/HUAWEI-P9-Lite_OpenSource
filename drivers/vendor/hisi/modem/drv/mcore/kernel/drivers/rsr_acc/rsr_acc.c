#include <bsp_slice.h>
#include <bsp_rsracc.h>
#include <bsp_sysctrl.h>
#include <bsp_shared_ddr.h>

#include <libfdt.h>
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
};

struct rsracc_ctrl_s{
	void* base;
	struct list_head sus_end_list;
	struct list_head    desc_list;
	u32 desc_bd_cnt;		 /*the number of bd descriptor  */
	u32		 bd_cnt;		/*the number valid bd to rsracc*/
	u32 support_rsracc;
	bool is_inited;
	bool lazy_build_bd;
	bool is_rsracc_enabled;
	bool need_check_result;
	struct rsr_acc_bd_s *bds_base;
	struct rsracc_debug_s debug;
	u32 clk_cfg[5];/*sysctrl_index,enable_offset,disable_offset,status_offset,bit_of_cfg*/
	void*  clk_sysctrl_base;
}rsracc_ctrl;
static inline void rsracc_clk_enable(void)
{
	u32 ret = (u32)0x1<<rsracc_ctrl.clk_cfg[4],temp = 0;
	writel(ret,(u32)(rsracc_ctrl.clk_sysctrl_base+rsracc_ctrl.clk_cfg[1]));
	do{
		temp = readl((u32)(rsracc_ctrl.clk_sysctrl_base+rsracc_ctrl.clk_cfg[3]));
	}while(!(temp&ret));
}
static inline void rsracc_clk_disable(void)
{
	u32 ret = (u32)0x1<<rsracc_ctrl.clk_cfg[4],temp = 0;
	writel(ret,(u32)(rsracc_ctrl.clk_sysctrl_base+rsracc_ctrl.clk_cfg[2]));
	do{
		temp = readl((u32)(rsracc_ctrl.clk_sysctrl_base+rsracc_ctrl.clk_cfg[3]));
	}while(temp&ret);
}		
static s32 __rsracc_build_bd(struct rsr_acc_bd_s *bds_base,rsr_acc_description *bd_descri)
{
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
		bds_base->cfg.bd_oper = 3;
		bds_base->bd_flow_operation = bd_descri->negation_resume_bitmask;/*È¡·´bitÎ»*/
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
	/*in M3 must set bak_addr*/
	if((!bd_descri->bak_addr&&bd_descri->need_rsracc_assign_bakaddr)&&!bd_descri->is_wait_bd)
	{
		return BSP_ERROR;
	}
	else
	{
		bds_base->ddr_baddr = bd_descri->bak_addr;
		rsracc_ctrl.bd_cnt++;
		return BSP_OK;
	}
}
static s32 rsracc_build_bd(void)
{
	rsr_acc_description *p;
	s32 ret = 0;
	u32 i = 0;
	struct rsr_acc_bd_s *last_bd = NULL;
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
				rsracc_print("bd build err,bd_des name = %s\n",p->name);
				return BSP_ERROR;
			}
			i++;
		}
	}
	last_bd = rsracc_ctrl.bds_base+rsracc_ctrl.bd_cnt -1;
	if(only_valid_resume_flow == (rsr_acc_valid_flow)last_bd->cfg.bd_flow )
	{
		rsracc_print("last bd not resume only\n");
		return BSP_ERROR;
	}
	return BSP_OK;
}

s32 bsp_rsracc_register(rsr_acc_description *bd_descri,u32 cnt)
{
	int ret = BSP_OK;
	unsigned long flags = 0;
	u32 i = 0;
	rsr_acc_description *p = NULL;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("not init\n");
		return BSP_ERROR;
	}
	local_irq_save(flags);
	for(i = 0;i < cnt; i++)
	{
		if(!bd_descri->only_ops_in_bd && rsracc_ctrl.bd_cnt >= MAX_RSR_ACC_BD_CNT)
		{
			local_irq_restore(flags);
			rsracc_print("BD cnt overflow,bd_name=%s\n",bd_descri->name);
			return BSP_ERROR;
		}
		list_for_each_entry(p,&rsracc_ctrl.desc_list,entry)
		{
			if(p->level > bd_descri->level)
				break;
		}
		list_add_tail(&bd_descri->entry,&p->entry);
		rsracc_ctrl.desc_bd_cnt++;
		bd_descri++;
	}
	local_irq_restore(flags);
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
		rsracc_print("not init\n");
		return BSP_ERROR;
	}
	local_irq_save(flags);
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
	local_irq_restore(flags);
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
static void result_compare(void* source,void* dest,u32 count){
	u32* temp1=NULL,*temp2=NULL;
	u32 cnt = 0;
	temp1 = (u32*)source;
	temp2 = (u32*)dest;
	rsracc_print("check:src:0x%x,dest:0x%x\n",source,dest);
	while(cnt < count){
		if(*temp1 != *temp2){
			rsracc_print("error at %d data,source=0x%x,dest=0x%x\n",cnt,*temp1,*temp2);
		}
		temp1++;
		temp2++;
		cnt++;
	}
}

static inline void check_result(struct list_head *list,enum rsracc_flow_e __flow)
{
	rsr_acc_description *p = NULL;
	list_for_each_entry(p,list,entry)
	{
		if(p->reg_num&&p->bd_valid_flow == both_save_and_resume_flow)
		{
			result_compare((void*)p->bak_addr,(void*)p->reg_addr,p->reg_num);
		}
		if(__flow == resume_flow)
		{
			if(p->is_negation_resume)
			{
				if((*(p->bak_addr))&(*(p->reg_addr))&p->negation_resume_bitmask)
				{
					rsracc_print("negate res err,bak=0x%x,reg=0x%x,bitmask=0x%x\n",*(p->bak_addr),*(p->reg_addr),p->negation_resume_bitmask);
				}
			}
		}
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
	local_irq_save(flags);
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
	rsracc_clk_disable();
	local_irq_restore(flags);
}
s32 bsp_rsracc_suspend_begin(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL ,*next = NULL;
	s32 ret = BSP_OK;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("not init\n");
		return BSP_ERROR;
	}
	local_irq_save(flags);
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
					local_irq_restore(flags);
					rsracc_print("slice:0x%x,%s sus_begin err,ret = 0x%x\n",bsp_get_slice_value(),p->name,ret);
					bsp_rsracc_suspend_halt();
					return BSP_ERROR;
				}
				else
					list_move_tail(&p->entry,&rsracc_ctrl.sus_end_list);
			}		
		}
		rsracc_clk_enable();
		rsracc_enable_trans(suspend_flow);
		
	}
	trace_slice(rsracc_ctrl.debug.suspend_begin_slice[1]);
	local_irq_restore(flags);
	return BSP_OK;
}
void bsp_rsracc_suspend_end(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	local_irq_save(flags);
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
	rsracc_clk_disable();
	if(rsracc_ctrl.need_check_result)
		check_result(&rsracc_ctrl.sus_end_list,suspend_flow);
	local_irq_restore(flags);
}

void bsp_rsracc_resume_begin(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p;
	local_irq_save(flags);
	trace_slice(rsracc_ctrl.debug.resume_begin_slice[0]);
	rsracc_clk_enable();
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
	local_irq_restore(flags);
}
void bsp_rsracc_resume_end(void)
{
	unsigned long flags = 0;
	rsr_acc_description *p = NULL;
	local_irq_save(flags);
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
	rsracc_clk_disable();
	if(rsracc_ctrl.need_check_result)
		check_result(&rsracc_ctrl.desc_list,resume_flow);
	local_irq_restore(flags);
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
	u32 temp = 0;
	(void)memset((void*)&rsracc_ctrl,0x0,sizeof(struct rsracc_ctrl_s));
	rsracc_ctrl.bds_base =(struct rsr_acc_bd_s *)(SHM_BASE_ADDR + SHM_OFFSET_M3RSRACC_BD);
	(void)memset((void*)(SHM_BASE_ADDR + SHM_OFFSET_M3RSRACC_BD),0x0,SHM_SIZE_M3RSRACC_BD);
	node = of_find_compatible_node(NULL, NULL, rsr_acc_name);
	if(!node)
	{
		rsracc_print("find node err\n");
		return ;
	}
	iomap_node = of_iomap(node, 0);
	if (NULL == iomap_node)
	{
		rsracc_print("of_iomap err.\n");
		return ;
	}
	ret = of_property_read_u32_array(node, "support", &rsracc_ctrl.support_rsracc,1);
	ret |= of_property_read_u32_array(node, "clk_cfg", rsracc_ctrl.clk_cfg,5);
	if (ret)
	{
		rsracc_print("sup/clk_cfg rd err.\n");
		return ;
	}
	rsracc_ctrl.base = iomap_node;
	rsracc_ctrl.clk_sysctrl_base = bsp_sysctrl_addr_byindex(rsracc_ctrl.clk_cfg[0]);
	rsracc_clk_enable();
	temp = readl((unsigned)(rsracc_ctrl.base+DMA_CTRL_OFFSET));
	writel(temp|0x3f,(unsigned)(rsracc_ctrl.base+DMA_CTRL_OFFSET));
	rsracc_clk_disable();
	INIT_LIST_HEAD(&(rsracc_ctrl.sus_end_list));
	INIT_LIST_HEAD(&(rsracc_ctrl.desc_list));
	(void)memset((void*)rsracc_ctrl.bds_base,0x0,sizeof(struct rsr_acc_bd_s)*MAX_RSR_ACC_BD_CNT);
	rsracc_ctrl.is_inited = true;
	rsracc_ctrl.lazy_build_bd = true;
	rsracc_ctrl.need_check_result = false;
	rsracc_print("init ok\n");
}

/*build bd*/
void bsp_rsracc_init_late(void)
{
	s32 ret = 0;
	unsigned long flags = 0;
	if(!rsracc_ctrl.is_inited)
	{
		rsracc_print("init err\n");
		return;
	}
	local_irq_save(flags);
	ret = rsracc_build_bd();
	if(ret)
	{
		rsracc_print("init late err\n");
		rsracc_ctrl.is_inited = false;
		local_irq_restore(flags);
		return;
	}
	rsracc_ctrl.lazy_build_bd = false;
	local_irq_restore(flags);
	rsracc_print("init late ok\n");
}
void bsp_rsracc_set_checkflag(bool flag)
{
	rsracc_ctrl.need_check_result = flag;
}

void bsp_rsracc_show(void)
{
	/*
	rsr_acc_description *p = NULL;
	rsracc_print("name    level  bak_addr   reg_base reg_num \n");
	list_for_each_entry(p,&rsracc_ctrl.desc_list,entry)
	{
		rsracc_print("%s   %d   0x%x    0x%x   %d\n",p->name,p->level,p->bak_addr,p->reg_addr,p->reg_num);
	}
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
	rsracc_print("wait_finish_max    :0x%x \n",rsracc_ctrl.debug.wait_finish_max);*/
}

