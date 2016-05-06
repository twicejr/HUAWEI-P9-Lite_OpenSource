/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名 :  bbp_balong.c
*
*   作    者    :  w00149837
*
*   描    述    :  本文件主要实现BBP 毫秒中断 功能
*
*   修改记录 :  2013年2月20日 创建
*************************************************************************/
/*lint --e{124,537}*/

#include <bsp_version.h>
#include <bsp_sysctrl.h>
#include <bsp_memmap.h>
#include <osl_types.h>
#include <of.h>
#include <bsp_hardtimer.h>

struct timerslice_control{
	u32 timerslice_base_addr;
	u32 timerslice_hrt_base_addr;   /*udelay timer stamp addr*/
	u32 timerslice_base_addr_phy;  /*时间戳实地址*/	
	u32 hrt_slice_is_increase;
	u32 slice_is_increase;
	u32 hrt_slice_offset[2];                     /*udelay timer stamp 偏移*/
	u32 slice_offset[2];/*32 k slice offset*/
	u32 hrt_slice_clock_freq;
	u32 slice_clock_freq;
	u64 slice_judgetime;
	u32 version_id;
	u32 is_inited_flag ;
};

struct timerslice_control timeslice_ctrl=
{
	0,
	0,
	0,
	0,
	0,
	{0,0},
	{0,0},
	0,
	0,
	0x50000,/*default 10s*/
	0,
	0,
};
void slice_set_judgetime(u64 time_s)
{
	if(timeslice_ctrl.is_inited_flag){
    	timeslice_ctrl.slice_judgetime = timeslice_ctrl.slice_clock_freq*time_s;
		return;
	}
	else
		return;
}

/*****************************************************************************
* 函数  : bbp_get_curtime
* 功能  : 被PS调用，用来获取系统精确时间
* 输入  : void
* 输出  : u64 *pcurtime
* 返回  : u32
*****************************************************************************/
u32 bsp_slice_getcurtime(u64 *pcurtime)
{
	/*lint -save -e958*/
	u64  timervalue[4];
	/*lint -restore*/
	if(timeslice_ctrl.is_inited_flag){
		timervalue[0] = (u64)readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
		timervalue[1] = (u64)readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[1]);
		if(timervalue[0]>=(0xffffffff-timeslice_ctrl.slice_judgetime))
		{
			timervalue[2] = (u64)readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
			timervalue[3] = (u64)readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[1]);

			if(timervalue[2] < timervalue[0])
			{
				(*pcurtime) = ((timervalue[3] - 1) << 32) | timervalue[0];
			}
			else
			{
				(*pcurtime) = (timervalue[1] << 32) | timervalue[0];
			}
		}
		else
			(*pcurtime) = (timervalue[1] << 32) | timervalue[0];
	}
	return 0;
}


u32 bsp_get_slice_value_hrt(void){
	if(timeslice_ctrl.is_inited_flag ){
		if(timeslice_ctrl.hrt_slice_is_increase){
				return readl((u32)timeslice_ctrl.timerslice_hrt_base_addr+timeslice_ctrl.hrt_slice_offset[0]);
			}
			else{
				return (0xFFFFFFFF - readl((u32)timeslice_ctrl.timerslice_hrt_base_addr+timeslice_ctrl.hrt_slice_offset[0]));
			}
	}
	else
		return 0;
}
u32 bsp_get_hrtimer_freq(void)
{
    return timeslice_ctrl.hrt_slice_clock_freq;
}

u32 bsp_get_slice_value(void){
	if(timeslice_ctrl.is_inited_flag ){
		if(timeslice_ctrl.slice_is_increase)
			return readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
		else
			return 0xFFFFFFFF - readl((u32)timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
	}
	else
		return 0;
}

u32 bsp_get_elapse_ms(void)
{
	u64 tmp=0;
	unsigned long timer_get = 0;
	if(timeslice_ctrl.is_inited_flag ){
		timer_get = bsp_get_slice_value();
		tmp = (u64)(timer_get & 0xFFFFFFFF);
		tmp = tmp*1000;
		tmp = div_u64(tmp,timeslice_ctrl.slice_clock_freq);
		return (u32)tmp;
	}
	else
		return 0;
}
void udelay(unsigned us)
{
	unsigned int begin = 0,addr = 0;
	u64 delta = 0;
	if(timeslice_ctrl.is_inited_flag){
		delta = (u64)us*timeslice_ctrl.hrt_slice_clock_freq/1000000;
		addr = (u32)timeslice_ctrl.timerslice_hrt_base_addr+timeslice_ctrl.hrt_slice_offset[0];
		begin = readl(addr);/* [false alarm]:误报 dead code*/
		 if(timeslice_ctrl.hrt_slice_is_increase){/*increase*/
		 	while(get_timer_slice_delta(begin,readl(addr))<delta){}/*lint !e666*//* [false alarm]:误报 dead code*/
		 }
		 else {/*decrease*/
		 	while(get_timer_slice_delta(readl(addr),begin)<delta){}/*lint !e666*//* [false alarm]:误报 dead code*/
		 }
	}
	else
		return ;
}

void* bsp_get_stamp_addr(void)
{
	if(timeslice_ctrl.is_inited_flag )
		return (void*)(timeslice_ctrl.timerslice_base_addr+timeslice_ctrl.slice_offset[0]);
	else
		return (void*)NULL;
}
void* bsp_get_stamp_addr_phy(void)
{
	if(timeslice_ctrl.is_inited_flag )
		return (void*)timeslice_ctrl.timerslice_base_addr_phy+timeslice_ctrl.slice_offset[0];
	else
		return (void*)NULL;
}

u32 bsp_get_slice_freq(void)
{
	return timeslice_ctrl.slice_clock_freq;
}
int slice_init(void){
	struct device_node *node = NULL;
	void *iomap_node = NULL;
	u32 remap_flag=0;
	s32 ret = 0;
	/*p532 fpga 与p532 asic读取同一套dts，所以通过版本号区分slice来源;
	 * porting timer slice also source timer*/
	if(BSP_BOARD_TYPE_SOC == bsp_get_version_info()->board_type|| \
		BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type)
	{
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_stamp_mdm");
	}
	else
	{
		node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_slice_mdm");
	}
	if(!node)
	{
		hardtimer_print_error("timer slice/stamp of_find_compatible_node failed.\r\n");
		return BSP_ERROR;
	}
	if(!of_device_is_available(node)){
		hardtimer_print_error("timer slice dts status is not ok.\n");
		return BSP_ERROR;
	}
	ret = of_property_read_u32(node, "increase_count_flag", &timeslice_ctrl.slice_is_increase);
	ret |= of_property_read_u32_array(node, "offset", timeslice_ctrl.slice_offset, 2);
	ret |= of_property_read_u32(node, "clock-frequency", &timeslice_ctrl.slice_clock_freq);
	ret |= of_property_read_u32(node, "reg", (u32*)&timeslice_ctrl.timerslice_base_addr_phy);
	if(ret)
	{
		hardtimer_print_error("timer slice property get failed.\r\n");
		return BSP_ERROR;
	}
	if(of_property_read_u32(node, "need_map", &remap_flag))
	{
		hardtimer_print_error("timer slice need_map get failed.\n");
		return BSP_ERROR;
	}
	if(remap_flag){
		iomap_node = of_iomap(node, 0);
		if (NULL == iomap_node)
		{
			hardtimer_print_error("timer slice of_iomap failed.\n");
			return BSP_ERROR;
		}
		timeslice_ctrl.timerslice_base_addr=(u32)iomap_node;
	}
	else
		timeslice_ctrl.timerslice_base_addr=timeslice_ctrl.timerslice_base_addr_phy;
	
	return BSP_OK;
}
int hrt_slice_init(void){
	struct device_node *node = NULL;
	char* hrttimer_slice = "hisilicon,hrttimer_slice_mdm";
	void *iomap_node = NULL;
	u32 remap_flag=0;
	s32 ret = 0;
	node = of_find_compatible_node(NULL, NULL, hrttimer_slice);
	if(!node)
	{
		hardtimer_print_error("timer_hrtslice of_find_compatible_node failed.\n");
		return BSP_ERROR;
	}
	if(!of_device_is_available(node)){
		hardtimer_print_error("timer hrtslice dts status is not ok.\n");
		return BSP_ERROR;
	}
	ret = of_property_read_u32(node, "increase_count_flag", &timeslice_ctrl.hrt_slice_is_increase);
	ret |= of_property_read_u32(node, "clock-frequency", &timeslice_ctrl.hrt_slice_clock_freq);
	ret |= of_property_read_u32_array(node, "offset", timeslice_ctrl.hrt_slice_offset, 2);
	if(ret)
	{
		hardtimer_print_error("timer_hrtslice get property failed.\n");
		return BSP_ERROR;
	}
	if(of_property_read_u32(node, "need_map", &remap_flag))
	{
		hardtimer_print_error("need_map get failed in dts\n");
		return BSP_ERROR;
	}
	if(remap_flag){
		/* 内存映射，获得基址 */
		iomap_node = of_iomap(node, 0);
		if (NULL == iomap_node)
		{
			hardtimer_print_error("hrttimer_app of_iomap failed.\n");
			return BSP_ERROR;
		}
		timeslice_ctrl.timerslice_hrt_base_addr = (u32)iomap_node;
	}
	else
	{
		if(of_property_read_u32(node, "reg", &timeslice_ctrl.timerslice_hrt_base_addr))
		{
			hardtimer_print_error("timer hrtslice reg get failed.\r\n");
			return BSP_ERROR;
		}
	}
	return BSP_OK;
}
int bsp_slice_init(void)
{
	int ret = 0;
	ret=slice_init();
	ret|=hrt_slice_init();
	if(ret){
		hardtimer_print_error("failed.\n");
		return BSP_ERROR;
	}
	timeslice_ctrl.is_inited_flag = 1;
	hardtimer_print_error("ok.\n");
	return BSP_OK;
}

int test_timer_slice(void)
{
	u32 low=0,high=0;
	if(mdrv_timer_get_accuracy_timestamp(&high,&low))
		return -1;
	else{
		hardtimer_print_error("low =0x%x\n",low);
		hardtimer_print_error("high =0x%x\n",high);
	}
	return 0;
}
