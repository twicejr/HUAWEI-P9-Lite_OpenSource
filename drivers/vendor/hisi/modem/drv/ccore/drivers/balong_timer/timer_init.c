#include <of.h>
#include <securec.h>
#include <soc_timer.h>
#include <bsp_hardtimer.h>
#include <bsp_slice.h>

struct timer_clk_ctrl_s{
	u32 disable_clk[2];	/*disable_clk[0]:value of disable timer clk;disable_clk[1]:addr to operate*/
	u32 set_clk[2];		/*set_clk[0]:value of timer clk set;set_clk[1]:addr to operate*/
	u32 enable_clk[2];	/*enable_clk[0]:value of enable timer clk;enable_clk[1]:addr to operate*/
	u32 clk_set_flag;	/*the flag of need change timer clk,in some version,no need to set timer clk*/
}timer_clk_ctrl;
static void timer_init_addr(const char* timer_feature_name)
{
	struct device_node *node = NULL;
	void* timer_iomap=NULL;
	node = of_find_compatible_node(NULL, NULL, timer_feature_name);
	if(node)
	{
		timer_iomap = of_iomap(node, 0);
		if (NULL == timer_iomap)
		{
			hardtimer_print_error("timer of_iomap failed.\n");
			return ;
		}
		else
			hardtimer_print_error("%s remap ok\n",timer_feature_name);
		return;
	}
}
void set_timer_clk(void)
{
	if(timer_clk_ctrl.clk_set_flag){
		writel(timer_clk_ctrl.disable_clk[0],timer_clk_ctrl.disable_clk[1]);
		writel(timer_clk_ctrl.set_clk[0],timer_clk_ctrl.set_clk[1]);
		writel(timer_clk_ctrl.enable_clk[0],timer_clk_ctrl.enable_clk[1]);
	}
}
void bsp_timer_iomap_and_clk_cfg(void)
{
	struct device_node *node = NULL;
	s32 ret = 0;
	(void)memset_s((void*)&timer_clk_ctrl,(size_t)sizeof(struct timer_clk_ctrl_s),0x0,(size_t)sizeof(struct timer_clk_ctrl_s));
	/*timer addr map*/
	timer_init_addr("hisilicon,timer_addr1");
	timer_init_addr("hisilicon,timer_addr2");
	node = of_find_compatible_node(NULL, NULL, "hisilicon,mdm_timer_clk_cfg");
	if(node)
	{
		ret = of_property_read_u32(node, "need_set_clk", &timer_clk_ctrl.clk_set_flag);
		ret |= of_property_read_u32_array(node, "disable_clk_cfg", timer_clk_ctrl.disable_clk,2);
		ret |= of_property_read_u32_array(node, "set_clk_cfg", timer_clk_ctrl.set_clk,2);
		ret |= of_property_read_u32_array(node, "enable_clk_cfg", timer_clk_ctrl.enable_clk,2);
		if(ret){
			hardtimer_print_error("mdm_timer_clk_set get properity failed\n");
			return;
		}
	}
	else{
		hardtimer_print_error("no need set mdm timer clk\n");
	}
	/*cfg mdm timer clk*/
	set_timer_clk();
	/*init slice*/
	if(bsp_slice_init())
		hardtimer_print_error("err\n");
	hardtimer_print_error("ok\n");
}

void timer_clk_cfg_show(void)
{
	hardtimer_print_error("timer clk cfg flag:0x%x\n",timer_clk_ctrl.clk_set_flag);	
	hardtimer_print_error("disable clk:value:0x%x,addr:0x%x\n",timer_clk_ctrl.disable_clk[0],timer_clk_ctrl.disable_clk[1]);	
	hardtimer_print_error("cfg clk:value:0x%x,addr:0x%x\n",timer_clk_ctrl.set_clk[0],timer_clk_ctrl.set_clk[1]);
	hardtimer_print_error("enable clk:value:0x%x,addr:0x%xn",timer_clk_ctrl.enable_clk[0],timer_clk_ctrl.enable_clk[1]);
}


