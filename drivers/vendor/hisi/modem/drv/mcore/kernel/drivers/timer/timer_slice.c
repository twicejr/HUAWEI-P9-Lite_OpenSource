#include <osl_common.h>
#include <bsp_version.h>
#include <bsp_slice.h>
#include <libfdt.h>
struct timer_slice_ctrl{
	void* slice_addr;
	void* hrt_slice_addr;
	void* hrt_slice_addr_ap;
	u32 slice_offset[2];
	u32 hrt_slice_offset[2];
	u32 hrt_sr_flag;
	u32 hrt_clk_cfg[2];
	u32 hrt_enable_cfg[2];
	u32 hrt_sr_flag_ap;
	u32 hrt_clk_cfg_ap[2];
	u32 hrt_enable_cfg_ap[2];
	u32 version_id ;
	u32 is_hrt_slice_increase_count;
	u32 is_slice_increase_count;
	u32 hrt_slice_freq;
	u32 slice_freq;
	u32 is_inited_flag;
}timer_slice_control={NULL,NULL,NULL,{0,0},{0,0},0,{0,0},{0,0},0,{0,0},{0,0},0,0,0,0,0,0};
u32 bsp_get_slice_value_hrt(void){
	if(timer_slice_control.is_inited_flag){
		 if(timer_slice_control.is_hrt_slice_increase_count)
		 	return  readl((unsigned)timer_slice_control.hrt_slice_addr+timer_slice_control.hrt_slice_offset[0]);
		 else 
			return 0xFFFFFFFF - readl((unsigned)timer_slice_control.hrt_slice_addr+timer_slice_control.hrt_slice_offset[0]);
		}
	else
		return 0;
}
u32 bsp_get_slice_value(void){
	if(timer_slice_control.is_inited_flag){
		if(timer_slice_control.is_slice_increase_count)
			return readl((unsigned)timer_slice_control.slice_addr+timer_slice_control.slice_offset[0]);
		else
			return 0xFFFFFFFF - readl((unsigned)timer_slice_control.slice_addr+timer_slice_control.slice_offset[0]);
	}
	else
		return 0;
}
void udelay(unsigned int us){
	unsigned int begin = 0;
	unsigned int delta = 0,addr = 0;
	if(timer_slice_control.is_inited_flag){
		delta = us*(timer_slice_control.hrt_slice_freq/1000000);
		addr = (unsigned)timer_slice_control.hrt_slice_addr+timer_slice_control.hrt_slice_offset[0];
		begin = readl(addr);
		 if(timer_slice_control.is_hrt_slice_increase_count){
		 	while(get_timer_slice_delta(begin,readl(addr))<delta){}
		}
		 else {
		 	while(get_timer_slice_delta(readl(addr),begin)<delta){}
		}
	}
	else
		return ;
}
static int slice_init(void){
	struct device_node *node = NULL;
	s32 ret = 0;
	/*porting timer slice also come from timer*/
	if(BSP_BOARD_TYPE_SOC == bsp_get_version_info()->board_type|| \
		BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type){
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_stamp_m3");
	}
	else
	{
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_slice_m3");
	}
	
	if(!node)
	{
		return -1;
	}
	timer_slice_control.slice_addr=of_iomap(node,0);
	ret = of_property_read_u32_array(node, "increase_count_flag", (unsigned int *)&timer_slice_control.is_slice_increase_count,1);
	ret |= of_property_read_u32_array(node, "clock-frequency", (unsigned int *)&timer_slice_control.slice_freq,1);
	ret |= of_property_read_u32_array(node, "offset", timer_slice_control.slice_offset, 2);
	if(ret)
	{
		return -1;
	}
	return 0;
	
}
void slice_resume(void){
	if(timer_slice_control.hrt_sr_flag){
		writel(timer_slice_control.hrt_clk_cfg[0],timer_slice_control.hrt_clk_cfg[1]);
		writel(timer_slice_control.hrt_enable_cfg[0],timer_slice_control.hrt_enable_cfg[1]);

	}
	if(timer_slice_control.hrt_sr_flag_ap){
		writel(timer_slice_control.hrt_clk_cfg_ap[0],timer_slice_control.hrt_clk_cfg_ap[1]);
		writel(timer_slice_control.hrt_enable_cfg_ap[0],timer_slice_control.hrt_enable_cfg_ap[1]);

	}
}
static int hrt_slice_init(void){
	struct device_node *node = NULL;
	s32 ret = 0;
	node = of_find_compatible_node(NULL, NULL, "hisilicon,hrttimer_slice_m3");
	if(!node)
	{
		return -1;
	}
	timer_slice_control.hrt_slice_addr=of_iomap(node,0);
	ret = of_property_read_u32_array(node, "increase_count_flag", (unsigned int *)&timer_slice_control.is_hrt_slice_increase_count,1);	
	ret |= of_property_read_u32_array(node, "clock-frequency", (unsigned int *)&timer_slice_control.hrt_slice_freq,1);
	ret |= of_property_read_u32_array(node, "offset", timer_slice_control.hrt_slice_offset, 2);
	if(ret)
	{
		return -1;
	}
	ret = of_property_read_u32_array(node, "sr_flag", &timer_slice_control.hrt_sr_flag, 1);
	if(!ret&&timer_slice_control.hrt_sr_flag){
		ret = of_property_read_u32_array(node, "clk_cfg", timer_slice_control.hrt_clk_cfg, 2);
		ret |= of_property_read_u32_array(node, "enable_cfg", timer_slice_control.hrt_enable_cfg, 2);
		if(ret)
		{
			return -1;
		}	
	}
	node = of_find_compatible_node(NULL, NULL, "hisilicon,hrttimer_slice_ap");
	if(node)
	{
		timer_slice_control.hrt_slice_addr_ap=of_iomap(node,0);
		ret = of_property_read_u32_array(node, "sr_flag", &timer_slice_control.hrt_sr_flag_ap, 1);
		if(!ret&&timer_slice_control.hrt_sr_flag_ap){
			ret = of_property_read_u32_array(node, "clk_cfg", timer_slice_control.hrt_clk_cfg_ap, 2);
			ret |= of_property_read_u32_array(node, "enable_cfg", timer_slice_control.hrt_enable_cfg_ap, 2);
			if(ret)
			{
				return -1;
			}	
		}
	}
	
	return 0;
}
int bsp_slice_init(void)
{
	int ret = 0;
	ret = slice_init();
	ret|=hrt_slice_init();
	if(ret){
		return ret;
	}
	timer_slice_control.is_inited_flag = 1;
	printk("slice ok\n");
	return ret;
}