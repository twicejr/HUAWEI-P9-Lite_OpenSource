
/*************************************************************************
*   版权所有(C) 2008-2013, 深圳华为技术有限公司.
*
*   文 件 名    :  bbp_balong_test.c
*
*   作    者    :  x00195528
*
*   描    述    :  本文件主要实现BBP 模块测试 功能
*
*   修改记录    :  2014年3月3日 创建
*************************************************************************/
/*lint --e{537}*/
#include "product_config.h"
#include <string.h>
#include <stdlib.h>
#include "securec.h"
#include <osl_thread.h>
#include <osl_malloc.h>
#include "bsp_bbp.h"
#include "bsp_memmap.h"
#include "hi_base.h"
#include "hi_bbp_dma.h"
#include <bsp_shared_ddr.h>
#include <bsp_hardtimer.h>
#include <bsp_busstress.h>
#include "bsp_dpm.h"
#include "soc_memmap.h"
#include <soc_memmap.h>
#include "hi_bbp_reg.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "bbp_balong.h"

extern struct bbp_info g_bbpinfo;

#ifndef BBP_PWR_NULL
#define BBP_PWR_NULL 0xff /*电源阈无效值*/
#endif

#ifndef BBP_CLK_NULL
#define BBP_CLK_NULL 0xff /*时钟阈无效值*/
#endif


/*压力测试相关*/
struct bbp_stress_info
{
    s32 stat;               /*压力测试状态，开始or 停止*/
    u32 interval ;          /*压力测试中间间歇时长*/
    u32 test_cnts ;         /*测试次数*/
    u32 err_cnts ;           /*失败次数*/
};
struct bbp_test_info
{
    struct bbp_dma_cfg dma;          /*dma搬移压力测试*/
    struct bbp_stress_info stress;   /*压力测试*/
};

struct bbp_test_info g_bbptestinfo;

extern int sysClkRateGet(void);
extern unsigned long bsp_random(void);

static __inline__ unsigned int bbp_bit_chk_temp(u32 addr,unsigned int mask)
{
    return (mask == (readl((unsigned)addr)&mask));
}


static void bbp_msleep(int x)
{
    osl_task_delay(sysClkRateGet()*x/1000+1);
}

void bbp_test_init(void)
{
    /*都上电*/
    bbp_poweron();
}

/*****************************************************************************
* 函 数 : bbp_dma_testchn_set
* 功 能 : 设置测试要用的bbp_dma通道
* 输 入 : edma_chn:BBP EDMA通道号,默认是使用通道0
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
void bbp_dma_testchn_set(int edma_chn)
{
    g_bbptestinfo.dma.chan = edma_chn;
    bbp_print_info("bbp_edma_test_chn is  %d!\n",g_bbptestinfo.dma.chan);
}

unsigned int g_bbp_busstress_test_ok_cnt = 0;
unsigned int g_bbp_busstress_test_fail_cnt = 0;

/*****************************************************************************
* 函 数 : bbp_dma_stress_test
* 功 能 : 逻辑要求bbp dma的验证
* 输 入 : addr : 源地址；len:数据长度;times:压力测试次数;edma_chn:通道号
* 输 出 : void
* 返 回 :
* 说 明 :初始化一段ddr空间，数据随机，从ddr搬移到RFIN指定地址，
         从RFIN地址搬回DDR空间，对比DDR两段空间数据，如果不一致，打印错误。退出
*****************************************************************************/
void bbp_dma_stress_test(u32 bbp_addr,u32 len, u32 times,u32 edma_chn)
{
    u32 *pbbp_ddr0;
    u32 *pbbp_ddr1;
    u32 *pbbp_ddr0_temp;
    u32 *pbbp_ddr1_temp;
    u32 i = 0;
    //u32 test_time = 0;

	/* bbp解复位 */
	/* writel(0xffffffff, 0xe020007c); */

    pbbp_ddr0 = (u32*)osl_cachedma_malloc(len);
    pbbp_ddr1 = (u32*)osl_cachedma_malloc(len);

    if(NULL == pbbp_ddr0)
    {
        bbp_print_error("ddr0 len %d malloc fail,change smaller len for test!",len);
        goto out;
    }
    if (NULL == pbbp_ddr1)
    {
        bbp_print_error("ddr1 len %d malloc fail,change smaller len for test!",len);
        goto out2;
    }
    /*ddr0为随机数*/
    pbbp_ddr0_temp = pbbp_ddr0;
    for(i = 0;i<(len/4);i++)
    {
        *pbbp_ddr0_temp = bsp_random();
        pbbp_ddr0_temp++;
    }

    g_bbptestinfo.dma.bbp_addr = bbp_addr;
    g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr0;
    g_bbptestinfo.dma.size = len;
    g_bbptestinfo.dma.type = 1;
    g_bbptestinfo.dma.chan = edma_chn;


    for ( ; ; )//(test_time = 0; test_time < times ; test_time++)
    {
        /*初始化ddr1为0*/
        memset_s(pbbp_ddr1,len,0,len);
        /*DDR0->RFIN*/
        g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr0;
        g_bbptestinfo.dma.type = 0;
        bbp_dma_tran(g_bbptestinfo.dma);
        bbp_dma_finish(g_bbptestinfo.dma);
        /*RFIN->DDR1*/
        g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr1;
        g_bbptestinfo.dma.type = 1;
        bbp_dma_tran(g_bbptestinfo.dma);
        bbp_dma_finish(g_bbptestinfo.dma);

        pbbp_ddr0_temp = pbbp_ddr0;
        pbbp_ddr1_temp = pbbp_ddr1;
        /*比较*/
        for(i = 0;i < (len/4);i++)
        {
            if(*pbbp_ddr0_temp != *pbbp_ddr1_temp)
            {
                bbp_print_error("offset %d not equle,write is %x,read is %x.\n",i,*pbbp_ddr0_temp,*pbbp_ddr1_temp);
				g_bbp_busstress_test_fail_cnt++;
                goto out1;
            }
            pbbp_ddr0_temp++;
            pbbp_ddr1_temp++;
        }
		g_bbp_busstress_test_ok_cnt++;

		osl_task_delay(20);
    }
    bbp_print_error("test ok!\n");

out1:
    osl_cachedma_free(pbbp_ddr1);
out2:
    osl_cachedma_free(pbbp_ddr0);
out:
    return;
}
/*****************************************************************************
* 函 数 : bbp_dma_test
* 功 能 : 逻辑要求bbp dma的验证
* 输 入 : addr : 源地址；len:数据长度;edma_chn:通道号
* 输 出 : void
* 返 回 :
* 说 明 :初始化一段ddr空间，数据随机，从ddr搬移到RFIN指定地址，
         从RFIN地址搬回DDR空间，对比DDR两段空间数据，如果不一致，打印错误。退出
*****************************************************************************/
void bbp_dma_test(u32 bbp_addr,u32 len, u32 edma_chn)
{
    u32 *pbbp_ddr0;
    u32 *pbbp_ddr1;
    u32 *pbbp_ddr0_temp;
    u32 *pbbp_ddr1_temp;
    u32 i = 0;

    pbbp_ddr0 = (u32*)osl_cachedma_malloc(len);
    pbbp_ddr1 = (u32*)osl_cachedma_malloc(len);

    if(NULL == pbbp_ddr0)
    {
        bbp_print_error("ddr0 len %d malloc fail,change smaller len for test!",len);
        goto out;
    }
    if (NULL == pbbp_ddr1)
    {
        bbp_print_error("ddr1 len %d malloc fail,change smaller len for test!",len);
        goto out2;
    }
    /*ddr0为随机数*/
    pbbp_ddr0_temp = pbbp_ddr0;
    for(i = 0;i<(len/4);i++)
    {
        *pbbp_ddr0_temp = bsp_random();
        pbbp_ddr0_temp++;
    }

    g_bbptestinfo.dma.bbp_addr = bbp_addr;
    g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr0;
    g_bbptestinfo.dma.size = len;
    g_bbptestinfo.dma.type = 1;
    g_bbptestinfo.dma.chan = edma_chn;

    /*初始化ddr1为0*/
    memset_s(pbbp_ddr1,len,0,len);
    /*DDR0->BBP*/
    g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr0;
    g_bbptestinfo.dma.type = 0;
    bbp_dma_tran(g_bbptestinfo.dma);
    bbp_dma_finish(g_bbptestinfo.dma);
    /*BBP->DDR1*/
    g_bbptestinfo.dma.soc_addr=(u32)pbbp_ddr1;
    g_bbptestinfo.dma.type = 1;
    bbp_dma_tran(g_bbptestinfo.dma);
    bbp_dma_finish(g_bbptestinfo.dma);

    pbbp_ddr0_temp = pbbp_ddr0;
    pbbp_ddr1_temp = pbbp_ddr1;
    /*比较*/
    for(i = 0;i < (len/4);i++)
    {
        if(*pbbp_ddr0_temp != *pbbp_ddr1_temp)
        {
            g_bbptestinfo.stress.err_cnts++;
            bbp_print_error("offset %d not equle,write is %x,read is %x.\n",i,*pbbp_ddr0_temp,*pbbp_ddr1_temp);
            goto out1;
        }
        pbbp_ddr0_temp++;
        pbbp_ddr1_temp++;
    }

    bbp_print_error("test ok!\n");

out1:
    osl_cachedma_free(pbbp_ddr1);
out2:
    osl_cachedma_free(pbbp_ddr0);
out:
    return;
}

void set_bbp_test_stat(int run_or_stop)
{
	g_bbptestinfo.stress.stat = run_or_stop;
}
int get_bbp_test_stat(void)
{
    return g_bbptestinfo.stress.stat;
}
/*****************************************************************************
* 函 数 : bbp_stress_test_routine
* 功 能 : 循环使用bbp_dma快速配置cqi寄存器,使得edma所在的bbp master持续工作
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 : 主要为了验证在多master同时工作时总线是否正常
*****************************************************************************/
int bbp_stress_test_routine(void)
{
    while(get_bbp_test_stat()){
        g_bbptestinfo.stress.test_cnts++;
        /*使用通道8，cqi寄存器进行测试*/
        bbp_dma_test(0x20000000,1024,8);
        bbp_msleep(g_bbptestinfo.stress.interval);
    }

    return 0;
}
/*****************************************************************************
* 函 数 : bbp_stress_test_start
* 功 能 : bbp压力测试开始
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
s32 bbp_stress_test_start(u32 priority , u32 interval)
{
    OSL_TASK_ID task_id;

    bbp_test_init();
    set_bbp_test_stat(TEST_RUN);
    g_bbptestinfo.stress.interval = interval;

    osl_task_init("BbpStressTask",priority,BBP_TASK_STK_SIZE,(OSL_TASK_FUNC)bbp_stress_test_routine,NULL,&task_id);

    return 0;
}
/*****************************************************************************
* 函 数 : lcd_emi_edma_stress_test_stop
* 功 能 : bbp压力测试结束
* 输 入 : void
* 输 出 : void
* 返 回 :
* 说 明 :
*****************************************************************************/
s32 bbp_stress_test_stop()
{
    set_bbp_test_stat(TEST_STOP);
    /*输出测试结果*/
    //bbp_print_error("test %d times, fail %d times!\n",test_num,test_err_num);

	return 0;
}

/*压力测试代码结束*/
/*上下电测试*/
/*实际代码中处于执行效率的考虑，只查看了部分的状态，测试代码中需要查看所有状态*/
unsigned int bbp_pwrctrl_is_enabled_test(int pwr_id)
{
    unsigned int state;

    state = bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit))\
           &bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.rdy_bit))\
           &bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit))\
           &~(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit)))\
           &~(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_bit)));

    return state;
}
unsigned int bbp_pwrctrl_is_disabled_test(int pwr_id)
{
    unsigned int state;

    state = ~(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].mos_ctrl.state_bit)))\
           &~(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].clk_ctrl.state_bit)))\
           &(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].rst_ctrl.state_bit)))\
           &(bbp_bit_chk_temp(g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_reg,(0x1 << g_bbpinfo.pwr.pwr_act[pwr_id].iso_ctrl.state_bit)));

    return state;
}

int bbp_pwr_enable_test(void)
{
    int pwr_id = 0;
    u32 enalbe_state = 0;
    u32 iret = BBP_OK;

    for(pwr_id = BBP_PWR_MIN;pwr_id <= BBP_PWR_MAX;pwr_id++)
    {
        bbp_pwrctrl_enable(pwr_id);
        enalbe_state = bbp_pwrctrl_is_enabled_test(pwr_id);
        if(!enalbe_state)/*没有开*/
        {
            bbp_print_error("mode %d: enable failed!\n", pwr_id);
            return pwr_id;
        }
    }
    bbp_print_error("test ok!");

    return iret;
}
int bbp_pwr_disable_test(void)
{
    int pwr_id = 0;
    u32 disable_state = 0;
    u32 iret = BBP_OK;

    for(pwr_id = BBP_PWR_MIN;pwr_id <= BBP_PWR_MAX;pwr_id++)
    {
        bbp_pwrctrl_disable(pwr_id);
        disable_state = bbp_pwrctrl_is_disabled_test(pwr_id);
        if(!disable_state)/*没有关*/
        {
            bbp_print_error("mode %d: disable failed!\n", pwr_id);
            return pwr_id;
        }
    }
    bbp_print_error("test ok!\n");
    return iret;
}

#ifdef CONFIG_CCORE_PM
extern int bbp_dpm_prepare(struct dpm_device *dev);
extern int bbp_dpm_suspend(struct dpm_device *dev);
extern int bbp_dpm_resume(struct dpm_device *dev);
extern int bbp_dpm_complete(struct dpm_device *dev);
/*低功耗测试*/
extern struct dpm_device  g_bbp_dpm_device;
/*测试suspend流程*/
u32 bbp_dpm_test_001(void)
{
    u32 iret = BBP_OK;

    bbp_dpm_prepare(&g_bbp_dpm_device);
    bbp_dpm_suspend(&g_bbp_dpm_device);
    /*对比保存数据是否正确*/

    return iret;
}
/*测试resume流程*/
u32 bbp_dpm_test_002(void)
{
    u32 iret = BBP_OK;

    bbp_dpm_resume(&g_bbp_dpm_device);
    bbp_dpm_complete(&g_bbp_dpm_device);
    /*对比恢复数据是否正确*/

    return iret;
}
#endif

/*测试对外上下电接口*/
/*参数检查*/
u32 bbp_para_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u8 mode_id,module_id,modem_id,flag = 0;

    /*MODE参数检查*/
    for(mode_id = PWC_COMM_MODE_GSM;mode_id <= PWC_COMM_MODE_BUTT;mode_id++)
    {
        if((mode_id < BBP_PWC_MODE_MIN)||(mode_id > BBP_PWC_MODE_MAX))
            flag = 1;/*错误参数*/
        else
            flag = 0;

        for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
        {
            for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
            {
                iret = bbp_power_up(mode_id,module_id,modem_id)&bsp_bbp_power_down(mode_id,module_id,modem_id)&bsp_bbp_power_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bbp_clk_enable(mode_id,module_id,modem_id)&bbp_clk_disable(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bsp_bbp_dfs_enable(mode_id,module_id,modem_id)&bsp_bbp_dfs_disable(mode_id,module_id,modem_id)&bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
            }
        }
    }
    /*MODULE参数检查*/
    for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
    {
        for(module_id = PWC_COMM_MODULE_PA;module_id <= PWC_COMM_MODULE_BUTT; module_id++)
        {
            if((module_id < BBP_PWC_MODULE_MIN)||(module_id > BBP_PWC_MODULE_MAX))
                flag = 1;/*错误参数*/
            else
                flag = 0;

            for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
            {
                iret = bsp_bbp_power_up(mode_id,module_id,modem_id)&bsp_bbp_power_down(mode_id,module_id,modem_id)&bsp_bbp_power_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bbp_clk_enable(mode_id,module_id,modem_id)&bbp_clk_disable(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bsp_bbp_dfs_enable(mode_id,module_id,modem_id)&bsp_bbp_dfs_disable(mode_id,module_id,modem_id)&bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
            }
        }
    }
    /*MODEM参数检查*/
    for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
    {
        for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
        {
            for(modem_id = PWC_COMM_MODEM_0;modem_id <= PWC_COMM_MODEM_BUTT; modem_id++)
            {
                if((modem_id < BBP_PWC_MODEM_MIN)||(modem_id > BBP_PWC_MODEM_MAX))
                    flag = 1;/*错误参数*/
                else
                    flag = 0;

                iret = bsp_bbp_power_up(mode_id,module_id,modem_id)&bsp_bbp_power_down(mode_id,module_id,modem_id)&bsp_bbp_power_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bbp_clk_enable(mode_id,module_id,modem_id)&bbp_clk_disable(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
                iret = bsp_bbp_dfs_enable(mode_id,module_id,modem_id)&bsp_bbp_dfs_disable(mode_id,module_id,modem_id)&bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                if((flag&&(BBP_ERR_PARAM_INVALID != iret)) || ((!flag)&&(BBP_ERR_PARAM_INVALID == iret)))
                {
                    test_result = BBP_ERR;
                    goto out;
                }
            }
        }
    }
out:
    if(test_result)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return test_result;
}
/*bbp_power*/
u32 bbp_power_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 pwr_id = 0;
    int pwr_status = PWRCTRL_COMM_OFF;
    u8 mode_id,module_id,modem_id= 0;

    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                pwr_id = g_bbpinfo.pwr.pwr_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pwr[0];
                if (BBP_PWR_NULL == pwr_id)
                {
                    iret = bsp_bbp_power_up(mode_id,module_id,modem_id);
                    pwr_status = bsp_bbp_power_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pwr_status)
                    {
                        bbp_print_error("mode %d module %d modem %d power up error,should be off!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bsp_bbp_power_down(mode_id,module_id,modem_id);
                    pwr_status = bsp_bbp_power_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pwr_status)
                    {
                        bbp_print_error("mode %d module %d modem %d power down error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
                else
                {
                    iret |= bsp_bbp_power_up(mode_id,module_id,modem_id);
                    pwr_status = bsp_bbp_power_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_ON != pwr_status)
                    {
                        bbp_print_error("mode %d module %d modem %d power up error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bsp_bbp_power_down(mode_id,module_id,modem_id);
                    pwr_status = bsp_bbp_power_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pwr_status)
                    {
                        bbp_print_error("mode %d module %d modem %d power down error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return (test_result|iret);
}
/*bbp_clk*/
u32 bbp_clk_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 clk_id = 0;
    int clk_status = PWRCTRL_COMM_OFF;
    u8 mode_id,module_id,modem_id = 0;

    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                clk_id = g_bbpinfo.clk.clk_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_clk[0];
                if (BBP_CLK_NULL == clk_id)
                {
                    iret |= bbp_clk_enable(mode_id,module_id,modem_id);
                    clk_status = bbp_clk_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != clk_status)
                    {
                        bbp_print_error("mode %d module %d modem %d clk enable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bbp_clk_disable(mode_id,module_id,modem_id);
                    clk_status = bbp_clk_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != clk_status)
                    {
                        bbp_print_error("mode %d module %d modem %d clk disable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
                else
                {
                    iret |= bbp_clk_enable(mode_id,module_id,modem_id);
                    clk_status = bbp_clk_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_ON != clk_status)
                    {
                        bbp_print_error("mode %d module %d modem %d clk enable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bbp_clk_disable(mode_id,module_id,modem_id);
                    clk_status = bbp_clk_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != clk_status)
                    {
                        bbp_print_error("mode %d module %d modem %d clk disable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return (test_result|iret);
}
#if 0
/*bbp_pll*/
u32 bbp_pll_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 pll_flag = 0;
    int pll_status = PWRCTRL_COMM_OFF;
    u8 mode_id,module_id,modem_id = 0;

    for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
    {
        for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
        {
            for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
            {
                pll_flag = g_bbpinfo.pll.pll_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pll;
                if (!pll_flag)
                {
                    iret |= bsp_bbp_dfs_enable(mode_id,module_id,modem_id);
                    pll_status = bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pll_status)
                    {
                        bbp_print_error("mode %d module %d modem %d pll enable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bsp_bbp_dfs_disable(mode_id,module_id,modem_id);
                    pll_status = bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pll_status)
                    {
                        bbp_print_error("mode %d module %d modem %d pll disable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
                else
                {
                    iret |= bsp_bbp_dfs_enable(mode_id,module_id,modem_id);
                    pll_status = bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_ON != pll_status)
                    {
                        bbp_print_error("mode %d module %d modem %d pll enable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    iret |= bsp_bbp_dfs_disable(mode_id,module_id,modem_id);
                    pll_status = bsp_bbp_dfs_status(mode_id,module_id,modem_id);
                    if(PWRCTRL_COMM_OFF != pll_status)
                    {
                        bbp_print_error("mode %d module %d modem %d pll disable error!\n",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return (test_result|iret);
}

#endif

u32 bbp_power_vote_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 pwr_id = 0;
    u32 pwr_cnt[BBP_PWR_MAX - BBP_PWR_MIN + 1] = {0};
    bool pwron_flag = true;/*电源状态是否为开启*/
    u8 mode_id,module_id,modem_id,i = 0;

    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                iret = bsp_bbp_power_up(mode_id,module_id,modem_id);
                /*找到操作的pwrid*/
                for (i = BBP_PWR_MIN ;i <= BBP_PWR_MAX ;i++ )
                {
                    pwr_id = g_bbpinfo.pwr.pwr_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pwr[i-BBP_PWR_MIN];
                    if (BBP_PWR_NULL == pwr_id)
                    {
                        break;
                    }
                    else
                    {
                        pwr_cnt[pwr_id - BBP_PWR_MIN]++;
                    }
                }
            }
        }
    }
    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                iret = bsp_bbp_power_down(mode_id,module_id,modem_id);

                /*找到操作的pwrid*/
                for (i = BBP_PWR_MIN ;i <= BBP_PWR_MAX ;i++ )
                {
                    pwr_id = g_bbpinfo.pwr.pwr_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pwr[i-BBP_PWR_MIN];
                    if (BBP_PWR_NULL == pwr_id)
                    {
                        if(BBP_PWR_MIN == i)/*没有可操作的pwrid默认返回off状态*/
                            pwron_flag = false;
                        break;
                    }
                    else
                    {
                        if(--pwr_cnt[pwr_id - BBP_PWR_MIN])/*该pwrid还有投票，不能关闭；查看下一个pwrid是否关闭*/
                            pwron_flag &= true;
                        else
                            pwron_flag &= false;   /*其中一个pwrid已经无投票，关闭，则整体应该返回off；*/
                    }
                }

                if(false == pwron_flag)
                {
                    if(PWRCTRL_COMM_OFF != bsp_bbp_power_status(mode_id,module_id,modem_id))
                    {
                        bbp_print_error("mode %d module %d modem %d vote error,should be off!",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                    pwron_flag = true;
                }
                else
                {
                    if(PWRCTRL_COMM_ON != bsp_bbp_power_status(mode_id,module_id,modem_id))
                    {
                        bbp_print_error("mode %d module %d modem %d vote error,should be on!",mode_id,module_id,modem_id);
                        test_result = BBP_ERR;
                        goto out;
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return (test_result|iret);
}

#if 0
u32 bbp_pll_vote_test(void)
{
    u32 test_result = BBP_OK;
    u32 iret = BBP_OK;
    u32 pll_flag = 0;
    u8 mode_id,module_id,modem_id,cnt = 0;

    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                pll_flag = g_bbpinfo.pll.pll_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pll;
                iret = bsp_bbp_dfs_enable(mode_id,module_id,modem_id);

                if (pll_flag)
                {
                    cnt++;
                }
            }
        }
    }
    for(module_id = BBP_PWC_MODULE_MIN;module_id <= BBP_PWC_MODULE_MAX; module_id++)
    {
        for(modem_id = BBP_PWC_MODEM_MIN;modem_id <= BBP_PWC_MODEM_MAX; modem_id++)
        {
            for(mode_id = BBP_PWC_MODE_MIN;mode_id <= BBP_PWC_MODE_MAX;mode_id++)
            {
                iret |= bsp_bbp_dfs_disable(mode_id,module_id,modem_id);
                pll_flag = g_bbpinfo.pll.pll_list[module_id-BBP_PWC_MODULE_MIN][modem_id-BBP_PWC_MODEM_MIN][mode_id-BBP_PWC_MODE_MIN].pwc_pll;
                if (pll_flag)
                {
                    if(--cnt)
                    {
                        if(PWRCTRL_COMM_ON != bsp_bbp_dfs_status(mode_id,module_id,modem_id))
                        {
                            test_result = BBP_ERR;
                            goto out;
                        }
                    }
                    else
                    {
                        if(PWRCTRL_COMM_OFF != bsp_bbp_dfs_status(mode_id,module_id,modem_id))
                        {
                            test_result = BBP_ERR;
                            goto out;
                        }
                    }
                }
            }
        }
    }

out:
    if(test_result || iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return iret;
}

#endif

/*bbp_addr*/
/*测试获取bbp各部分基地址的接口是否正确*/
u32 bbp_addr_test(void)
{
    u32 iret = BBP_OK;
    u32 part_id = 0;

    for(part_id = BBP_PART_TOP; part_id < BBP_PART_BUTT; part_id++)
    {
        if(bsp_bbp_part_addr_get(part_id) != (void*)g_bbpinfo.part[part_id].reg_base)
        {
            bbp_print_error("bbp part %d get addr error!",part_id);
            iret = BBP_ERR;
            goto out;
        }
    }
out:
    if(iret)
        bbp_print_error("test error!");
    else
        bbp_print_error("test ok!");

    return iret;
}

