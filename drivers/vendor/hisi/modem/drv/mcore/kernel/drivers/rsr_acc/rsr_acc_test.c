#include <osl_common.h>
#include <bsp_rsracc.h>
#include <bsp_slice.h>

#define MOD_NAME "rsracc"
#define rsracc_print(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_RSRACC, "<%s> "fmt" ", MOD_NAME, ##__VA_ARGS__))

static s32 suspend_start_cb_level0(rsr_acc_description *bd_descri)
{
	rsracc_print("suspend_start level0,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
	return BSP_OK;
}
static s32 suspend_start_cb_level1(rsr_acc_description *bd_descri)
{
	rsracc_print("suspend_start level1,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
	return BSP_OK;
}

static void suspend_end_cb_level0(rsr_acc_description *bd_descri)
{
	rsracc_print("suspend_end level0,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
	
}
static void suspend_end_cb_level1(rsr_acc_description *bd_descri)
{
	rsracc_print("suspend_end level1,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
}

static void resume_start_cb_level0(rsr_acc_description *bd_descri)
{
	rsracc_print("resume_start level0,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
}
static void resume_start_cb_level1(rsr_acc_description *bd_descri)
{
	rsracc_print("resume_start level1,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
}

static void resume_end_cb_level0(rsr_acc_description *bd_descri)
{
	rsracc_print("resume_end level0,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
}
static void resume_end_cb_level1(rsr_acc_description *bd_descri)
{
	rsracc_print("resume_end level1,slice_hrt=%d,name=0x%s\n",bsp_get_slice_value_hrt(),bd_descri->name);
}
struct rsracc_cb_s test_ops0 = {
	.suspend_begin = suspend_start_cb_level0,
	.suspend_end   = suspend_end_cb_level0,
	.resume_begin  = resume_start_cb_level0,
	.resume_end    = resume_end_cb_level0,
};
struct rsracc_cb_s test_ops1 = {
	.suspend_begin = suspend_start_cb_level1,
	.suspend_end   = suspend_end_cb_level1,
	.resume_begin  = resume_start_cb_level1,
	.resume_end    = resume_end_cb_level1,
};


rsr_acc_description test_rsracc_wait_bd[] = 
{
	{/*0*/
		.level = rsracc_bd_level_0,
		.name = "waitbd100",
		.ops = &test_ops0,
		.bd_valid_flow    = both_save_and_resume_flow,
		.is_wait_bd = true,
		.wait_cycle    = 100,
	},
	{/*1*/
		.level = rsracc_bd_level_0,
		.name = "onlyopsbd0",
		.ops = &test_ops0,
		.only_ops_in_bd     = true,
	},
	{/*2*/
		.level = rsracc_bd_level_1,
		.name = "save1",
		.ops = &test_ops1,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = both_save_and_resume_flow,
	},
	{/*3*/
		.level = rsracc_bd_level_1,
		.name = "save5",
		.ops = &test_ops1,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = both_save_and_resume_flow,
	},
	{/*4*/
		.level = rsracc_bd_level_0,
		.name = "save8",
		.ops = &test_ops0,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = both_save_and_resume_flow,
	},
	{/*5*/
		.level = rsracc_bd_level_0,
		.name = "save2",
		.ops = &test_ops0,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = both_save_and_resume_flow,
	},
	{/*6*/
		.level = rsracc_bd_level_0,
		.name = "negate1",
		.ops = &test_ops0,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = only_valid_resume_flow,
		.is_negation_resume = true,
		.negation_resume_bitmask = 0x3,
	},
	{/*7*/
		.level = rsracc_bd_level_0,
		.name = "negate2",
		.ops = &test_ops0,
		.only_ops_in_bd 	= false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow	  = only_valid_resume_flow,
		.is_negation_resume = true,
		.negation_resume_bitmask = 0xFFFFFFFF,
	},
	{/*8*/
		.level = rsracc_bd_level_0,
		.name = "waitbd20",
		.ops = &test_ops0,
		.bd_valid_flow    = both_save_and_resume_flow,
		.is_wait_bd = true,
		.wait_cycle    = 20,
	},
	{/*9*/
		.level = rsracc_bd_level_0,
		.name = "save4",
		.ops = &test_ops0,
		.only_ops_in_bd     = false,
		.need_rsracc_assign_bakaddr = false,
		.bd_valid_flow    = both_save_and_resume_flow,
	},
	
};
#define PRE_MALLOC_DDR_SIZE 23
u32 test_pre_reg[PRE_MALLOC_DDR_SIZE];
u32 test_bak_addr[PRE_MALLOC_DDR_SIZE];
u32 test_inited = 0;
#define check_inited() \
	do{\
		if(!test_inited) \
			rsracc_print("not test inited\n");\
	}while(0)
s32 rsracc_test_init()
{
	u32 i = 0;
	/*test_pre_reg[0] test for negate resume*/
	for(i=0;i<PRE_MALLOC_DDR_SIZE;i++)
		test_pre_reg[i] = 0x5A5A5A5A;
	test_rsracc_wait_bd[2].reg_addr = test_pre_reg+3;
	test_rsracc_wait_bd[2].reg_num  = 1;
	test_rsracc_wait_bd[2].bak_addr  = test_bak_addr+3;
	test_rsracc_wait_bd[3].reg_addr = test_pre_reg+4;
	test_rsracc_wait_bd[3].reg_num  = 5;
	test_rsracc_wait_bd[3].bak_addr  = test_bak_addr+4;
	test_rsracc_wait_bd[4].reg_addr = test_pre_reg+9;
	test_rsracc_wait_bd[4].reg_num  = 8;
	test_rsracc_wait_bd[4].bak_addr  = test_bak_addr+9;
	test_rsracc_wait_bd[5].reg_addr = test_pre_reg+17;
	test_rsracc_wait_bd[5].reg_num  = 2;
	test_rsracc_wait_bd[5].bak_addr  = test_bak_addr+17;
	test_rsracc_wait_bd[6].reg_addr = test_pre_reg;
	test_rsracc_wait_bd[6].reg_num  = 1;
	test_rsracc_wait_bd[6].bak_addr = test_pre_reg+1;
	test_rsracc_wait_bd[7].reg_addr = test_pre_reg;
	test_rsracc_wait_bd[7].reg_num  = 1;
	test_rsracc_wait_bd[7].bak_addr = test_pre_reg+2;
	test_rsracc_wait_bd[9].reg_addr = test_pre_reg+19;
	test_rsracc_wait_bd[9].reg_num  = 4;
	test_rsracc_wait_bd[9].bak_addr  = test_bak_addr+19;
	test_inited = 1;
	return 0;
}
extern void bsp_rsracc_show();
/*test register/unregister*/
s32 rsracc_test_case01(void)
{
	s32 ret = 0;
	check_inited();
	ret = bsp_rsracc_register(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	bsp_rsracc_show();
	ret = bsp_rsracc_unregister(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	bsp_rsracc_show();
	return 0;
}
s32 rsracc_test_case02(void)
{
	s32 ret = 0;
	check_inited();
	ret = bsp_rsracc_register(test_rsracc_wait_bd,5);
	if(ret)
		return -1;
	bsp_rsracc_show();
	ret = bsp_rsracc_suspend_begin();
	if(ret)
		return -1;
	bsp_rsracc_suspend_end();
	bsp_rsracc_resume_begin();
	bsp_rsracc_resume_end();
	ret = bsp_rsracc_unregister(test_rsracc_wait_bd,5);
	if(ret)
		return -1;
	return 0;
}
s32 rsracc_test_case03(void)
{
	s32 ret = 0;
	check_inited();
	ret = bsp_rsracc_register(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	bsp_rsracc_show();
	ret = bsp_rsracc_suspend_begin();
	if(ret)
		return -1;
	bsp_rsracc_suspend_end();
	bsp_rsracc_resume_begin();
	bsp_rsracc_resume_end();
	ret = bsp_rsracc_unregister(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	return 0;
}
s32 rsracc_test_case04(void)
{
	s32 ret = 0;
	check_inited();
	ret = bsp_rsracc_register(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	bsp_rsracc_show();
	ret = bsp_rsracc_suspend_begin();
	if(ret)
		return -1;
	bsp_rsracc_suspend_halt();
	ret = bsp_rsracc_unregister(test_rsracc_wait_bd,10);
	if(ret)
		return -1;
	return 0;
}

