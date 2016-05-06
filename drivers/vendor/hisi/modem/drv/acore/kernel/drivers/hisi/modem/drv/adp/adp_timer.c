

/*lint --e{537,648 }*/
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/slab.h>
#include <linux/printk.h>

#include <osl_module.h>
#include <osl_bio.h>

#include <mdrv_timer.h>
#include <drv_comm.h>

#include <bsp_hardtimer.h>
#include <bsp_om.h>


#define ADP_TIMER_ENABLE_TIMES 30
#define ADP_TIMER_CALLBACK_TIMES 30
#define ADP_TIMER_GET_TIMES 50

struct adp_timer_enable_dbg {
	u32  enable_cnt;
	u32  enable_slice[ADP_TIMER_ENABLE_TIMES];
	u32  disable_slice[ADP_TIMER_ENABLE_TIMES];
	u32  init_time[ADP_TIMER_ENABLE_TIMES];
	u32  expect_cb_slice[ADP_TIMER_ENABLE_TIMES];
};

struct adp_timer_callback_dbg{
	u32  callback_slice_cnt;
	u32  callback_slice[ADP_TIMER_CALLBACK_TIMES];
};

struct adp_timer_get_dbg{
	u32  get_cnt;
	u32  get_times[ADP_TIMER_GET_TIMES][2];
};
struct adp_timer_control{
	char* name;
	FUNCPTR_1 routine;
	int       args;
	u32       irq_num;
	struct bsp_hardtimer_control my_hardtimer;
	/*for debug*/
	struct adp_timer_enable_dbg       stEnable  ;
	struct adp_timer_callback_dbg    stCallback;
	struct adp_timer_get_dbg            stGet;
	FUNCPTR_1 debug_routine;
	int       debug_args;
};


struct adp_timer_control  adp_timer_ctrl[TIMER_ID_MAX];

void timer_enable_stamp_dbg(u32 clkid, u32 init_time)
{
      struct adp_timer_enable_dbg *pstEnable_dbg = &adp_timer_ctrl[clkid].stEnable;
      pstEnable_dbg->enable_slice[pstEnable_dbg->enable_cnt] = bsp_get_slice_value();
      pstEnable_dbg->init_time[pstEnable_dbg->enable_cnt] = init_time;
	  pstEnable_dbg->expect_cb_slice[pstEnable_dbg->enable_cnt] = init_time+pstEnable_dbg->enable_slice[pstEnable_dbg->enable_cnt];
}
void timer_disable_stamp_dbg(u32 clkid)
{
	struct adp_timer_enable_dbg *pstEnable_dbg = &adp_timer_ctrl[clkid].stEnable;
	pstEnable_dbg->disable_slice[pstEnable_dbg->enable_cnt] = bsp_get_slice_value();
	pstEnable_dbg->enable_cnt++;
	if (pstEnable_dbg->enable_cnt >=ADP_TIMER_ENABLE_TIMES)
		pstEnable_dbg->enable_cnt = 0;
}

static void timer_callback_stamp_dbg(u32 clkid)
{
	struct adp_timer_callback_dbg *pstCallback_dbg = &adp_timer_ctrl[clkid].stCallback;
	pstCallback_dbg->callback_slice[pstCallback_dbg->callback_slice_cnt] = bsp_get_slice_value();
	pstCallback_dbg->callback_slice_cnt++;
	if (pstCallback_dbg->callback_slice_cnt >= ADP_TIMER_CALLBACK_TIMES)
	{
		pstCallback_dbg->callback_slice_cnt = 0;
	}
}
void timer_get_stamp_dbg(u32 clkid, u32 curtime)
{
	struct adp_timer_get_dbg *pstGet_dbg = &adp_timer_ctrl[clkid].stGet;
	pstGet_dbg->get_times[pstGet_dbg->get_cnt][0]= bsp_get_slice_value();
	pstGet_dbg->get_times[pstGet_dbg->get_cnt][1]= curtime;
	pstGet_dbg->get_cnt++;
	if (pstGet_dbg->get_cnt >= ADP_TIMER_GET_TIMES)
	{
	   	pstGet_dbg->get_cnt = 0;
	}
}
OSL_IRQ_FUNC(static irqreturn_t,adp_timer_handler,irq,para)
{
	u32 ret_value = 0;
	u32 timer_id;
	timer_id = (u32)(unsigned long)para;
	timer_callback_stamp_dbg(timer_id);
	ret_value = bsp_hardtimer_int_status(timer_id);
	if(0x0 !=ret_value)
	{
		bsp_hardtimer_int_clear(timer_id);
		if(adp_timer_ctrl[timer_id].my_hardtimer.mode == TIMER_ONCE_COUNT)
		(void)bsp_hardtimer_disable(timer_id);
		if(NULL!=adp_timer_ctrl[timer_id].routine)
		{
			adp_timer_ctrl[timer_id].routine(adp_timer_ctrl[timer_id].args);
		}
	}

	return IRQ_HANDLED;
}

/*****************************************************************************
* 函数  : mdrv_timer_get_accuracy_timestamp
* 功能  : 获取BBP定时器的值。用于OAM 时戳
* 输入  : void
* 输出  :
			pulLow32bitValue指针参数不能为空，否则会返回失败。
			pulHigh32bitValue如果为空， 则只返回低32bit的值。
* 返回  : int
*****************************************************************************/
int mdrv_timer_get_accuracy_timestamp(unsigned int  *pulHigh32bitValue,  unsigned int  *pulLow32bitValue)
{
	BSP_U64 CurTime = 0;

	if(BSP_NULL == pulLow32bitValue)
	{
		return -1;
	}

	if(bsp_slice_getcurtime(&CurTime))
	{
		return MDRV_ERROR;
	}

	if(BSP_NULL != pulHigh32bitValue)
	{
		*pulHigh32bitValue = (CurTime>>32);
	}

	*pulLow32bitValue = CurTime & 0xffffffff;

	return 0;
}

unsigned int mdrv_timer_get_normal_timestamp(void){
	 return bsp_get_slice_value();
}
unsigned int mdrv_timer_get_hrt_timestamp(void)
{
	 return bsp_get_slice_value_hrt();
}


int mdrv_timer_start(unsigned int usrClkId,FUNCPTR_1 routine,int arg,unsigned int timerValue,unsigned int mode,unsigned int unitType)
{
    s32 ret = 0;
    adp_timer_ctrl[usrClkId].my_hardtimer.func = NULL;
    adp_timer_ctrl[usrClkId].my_hardtimer.para = NULL;
    adp_timer_ctrl[usrClkId].my_hardtimer.mode = mode;
	adp_timer_ctrl[usrClkId].my_hardtimer.unit = unitType;
	adp_timer_ctrl[usrClkId].my_hardtimer.timeout = timerValue;
    adp_timer_ctrl[usrClkId].my_hardtimer.timerId = usrClkId;
    adp_timer_ctrl[usrClkId].routine = routine;
    adp_timer_ctrl[usrClkId].args = arg;
	timer_enable_stamp_dbg(usrClkId,adp_timer_ctrl[usrClkId].my_hardtimer.timeout);
    ret = bsp_hardtimer_start(&adp_timer_ctrl[usrClkId].my_hardtimer);
    return ret;
}
int mdrv_timer_stop(unsigned int usrClkId)
{
	timer_disable_stamp_dbg(usrClkId);
    return bsp_hardtimer_disable(usrClkId);
}

int mdrv_timer_get_rest_time(unsigned int usrClkId,unsigned int unitType,unsigned int * pRestTime)
{
    int ret=0;
    ret = bsp_get_timer_rest_time(usrClkId,unitType,pRestTime);
    timer_get_stamp_dbg(usrClkId,*pRestTime);
    return ret;

}


BSP_VOID mdrv_timer_debug_register(unsigned int usrClkId,FUNCPTR_1 routine, int arg)
{
	adp_timer_ctrl[usrClkId].debug_routine = routine;
	adp_timer_ctrl[usrClkId].debug_args = arg;
}

static void get_timer_int_stat(void)
{
	unsigned int i = 0;
	pr_info("%s +\n", __func__);
	for(i = 0;i <TIMER_ID_MAX;i++){
		if(adp_timer_ctrl[i].debug_routine)
		{
			if(bsp_hardtimer_int_status(i))
				adp_timer_ctrl[i].debug_routine(adp_timer_ctrl[i].debug_args);
		}
	}
	pr_info("%s -\n", __func__);
}

static struct syscore_ops debug_timer_dpm_ops = {
	.resume = get_timer_int_stat,
	};
static void timer_handler_connect(DRV_TIMER_ID timer_id,const char* timer_name,unsigned long flags)
{
	s32 ret = 0;
	ret = request_irq(adp_timer_ctrl[timer_id].irq_num, (irq_handler_t)adp_timer_handler,flags,timer_name,(void*)timer_id);
	if(ret)
	{
		hardtimer_print_error("timer_emun_id=%d  , timer name %s request_irq failed\n",timer_id,timer_name);
		return;
	}
}
static int connect_timer_isr(void){
	struct device_node *node = NULL, *child_node=NULL;
	u32 request_id = 0,wake_flag = 0,flag=0;
	int ret_value = 0;
	node = of_find_compatible_node(NULL, NULL, "hisilicon,timer_device");
	if(node)
	{
		for_each_available_child_of_node(node, child_node)
		{
			ret_value = of_property_read_u32(child_node, "request_id", &request_id) ;
			if(ret_value)
			{
				hardtimer_print_error("request_id get failed.\n");
				return BSP_ERROR;
			}
			ret_value=of_property_read_u32(child_node, "need_adp_connect_isr", &flag);
			if(!ret_value){
				if(flag)
				{
					if(of_property_read_u32(child_node,"wakesrc",&wake_flag))
					{
						return BSP_ERROR;
					}
					if(of_property_read_string(child_node, "timer_name", (const char**)&adp_timer_ctrl[request_id].name))
			    	{
			        	hardtimer_print_error("timer request_id %d of_property_read_string failed.\n",request_id);
						return BSP_ERROR;
			    	}
					adp_timer_ctrl[request_id].irq_num=irq_of_parse_and_map(child_node, 0);
					if(wake_flag)
							timer_handler_connect(request_id,adp_timer_ctrl[request_id].name,IRQF_NO_SUSPEND);
						else
							timer_handler_connect(request_id,adp_timer_ctrl[request_id].name,0);
				}
			}
			else
			{
				hardtimer_print_error("timer %d need_adp_connect_isr get failed.\n",request_id);
				return BSP_ERROR;
			}
		}/*for_each_available_child_of_node*/
	}/*if(node)*/
	return BSP_OK;
}
int set_adp_timer_isr_and_pm(void)
{
	(void)memset((void*)adp_timer_ctrl,0x0,sizeof(struct adp_timer_control)*TIMER_ID_MAX);
	if(connect_timer_isr()){
		hardtimer_print_error("get dts failed,set_adp_timer_isr_and_pm failed\n");
		return BSP_ERROR;
	}
	register_syscore_ops(&debug_timer_dpm_ops);
	hardtimer_print_error(" ok\n");
	return BSP_OK;
}
void adp_timer_show(void){
	u32 i = 0;
	hardtimer_print_error("name\n");
	for(i=0;i<TIMER_ID_MAX;i++)
		hardtimer_print_error("%s\n",adp_timer_ctrl[i].name);
}

/*lint -restore +e19*/

