#include <of.h>
#include <osl_malloc.h>
#include <bsp_dsp.h>
#include <hi_dsp.h>
#include <c_sys_bus_core.h>
#include <c_sys_bus_pressure.h>
#include <c_sys_dsp.h>
#include <TLPhyDspTestInterface.h>
#include <string.h>


#define TL_PHY_INFINITE_CYCLE_MEMCPY       0     /* BBE16无限循环搬移内存         */
#define TL_PHY_MEMCPY_RESULTE_ADDR_OFFSET  0x40  /* BBE16内存搬移次数返回地址偏移 */

struct dsp_press g_dsp_press;

static int bsp_bbe_stress_writeReadTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
    if(((mailBody1 >= DDR_LPHY_SDR_ADDR) && ((mailBody1 + mailBody2) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody1 >= BBE_TCM_ADDR) && ((mailBody1 + mailBody2) <= (BBE_TCM_ADDR + BBE_TCM_SIZE))))
    {
        
        mailHead.ulReg32 = readl(g_dsp_press.DEMEM_addr);
        mailHead.bits.ulPPTR++;
        mailHead.bits.ulMsgID = WRITE_READ_TEST;
        writel(mailBody1, g_dsp_press.DEMEM_addr + 0x4);
        writel(mailBody2, g_dsp_press.DEMEM_addr + 0x8);
        writel(mailBody3, g_dsp_press.DEMEM_addr + 0xC);
        writel(mailHead.ulReg32, g_dsp_press.DEMEM_addr);

        return 0;
    }
    else
    {
        sys_bus_trace("Invalid addr input !\n");
        return -1;
    }   
}

static int bsp_bbe_stress_readWriteTest_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3, UINT32 mailBody4)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
	/*
    if((((mailBody1 >= DDR_LPHY_SDR_ADDR) && ((mailBody1 + mailBody3) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody1 >= BBE_TCM_ADDR) && ((mailBody1 + mailBody3) <= (BBE_TCM_ADDR + BBE_TCM_SIZE)))) &&
        (((mailBody2 >= DDR_LPHY_SDR_ADDR && ((mailBody2 + mailBody3) <= (DDR_LPHY_SDR_ADDR + DDR_LPHY_SDR_SIZE))) || 
        ((mailBody2 >= BBE_TCM_ADDR) && ((mailBody2 + mailBody3) <= (BBE_TCM_ADDR + BBE_TCM_SIZE))))) )
    {*/
        
        mailHead.ulReg32 = readl(g_dsp_press.DEMEM_addr);
        mailHead.bits.ulPPTR++;
        mailHead.bits.ulMsgID = READ_WRITE_TEST;
        writel(mailBody1, g_dsp_press.DEMEM_addr + 0x4);
        writel(mailBody2, g_dsp_press.DEMEM_addr + 0x8);
        writel(mailBody3, g_dsp_press.DEMEM_addr + 0xC);
        writel(mailBody4, g_dsp_press.DEMEM_addr + 0x10);
        writel(mailHead.ulReg32, g_dsp_press.DEMEM_addr);

        return 0;
    /*}
    else
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_DSP, "Invalid addr input !\n");
        return -1;
    }*/
}


static int bsp_bbe_stress_funcCycleCalc_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3)
{
    
    DSP_DRV_MAIL_HEAD mailHead;
    
    mailHead.ulReg32 = readl(g_dsp_press.DEMEM_addr);
    mailHead.bits.ulPPTR++;
    mailHead.bits.ulMsgID = FUNC_CYCLE_CALC;
    writel(mailBody1, g_dsp_press.DEMEM_addr + 0x4);
    /* 
            writel(mailBody2, DEMEM1_START_FOR_BUS_PRESS_TEST + 0x8);
            writel(mailBody3, DEMEM1_START_FOR_BUS_PRESS_TEST + 0xC);
       */
    writel(mailHead.ulReg32, g_dsp_press.DEMEM_addr);

    return 0;
    
}

int bsp_bbe_stress_test_start(UINT32 mailBody1, UINT32 mailBody2, UINT32 mailBody3, UINT32 mailBody4, UINT16 msgID)
{
    if(WRITE_READ_TEST == msgID)
    {
        return bsp_bbe_stress_writeReadTest_start(mailBody1, mailBody2, mailBody3);
    }
    else if(READ_WRITE_TEST == msgID)
    {
        return bsp_bbe_stress_readWriteTest_start(mailBody1, mailBody2, mailBody3, mailBody4);
    }
    else if(FUNC_CYCLE_CALC == msgID)
    {
        return bsp_bbe_stress_funcCycleCalc_start(mailBody1, mailBody2, mailBody3);
    }
    else
    {
        sys_bus_trace("Invalid msgID !\n");
        return -1;
    }
    
}


void sys_dsp_start(struct master* master)
{
    int ret = 0; 
    void *src_addr = NULL;
	void *dst_addr = NULL;
    
    ret = bsp_bbe_load_muti();    
    if (ret)
    {
        sys_bus_trace("bsp_bbe_load_muti failed.\n");
        return;
    }
    writel(0, g_dsp_press.DEMEM_addr);
    bsp_bbe_run();

    if (0 == g_dsp_press.press_type)
	{
		src_addr = osl_cachedma_malloc(0x20000);
        if(NULL == src_addr)
        {
            sys_bus_trace("src_addr malloc failed.\n");
            return;
        }
		dst_addr = osl_cachedma_malloc(0x20000);
        if(NULL == dst_addr)
        {
            sys_bus_trace("dst_addr malloc failed.\n");
            osl_cachedma_free(src_addr);
            return;
        }
        sys_bus_trace("[dsp]ddr_src_addr is 0x%x.\n", (u32)src_addr);
        sys_bus_trace("[dsp]ddr_dst_addr is 0x%x.\n", (u32)dst_addr);
	}
	else if (1 == g_dsp_press.press_type)
	{
		src_addr = osl_cachedma_malloc(0x20000);
        if(NULL == src_addr)
        {
            sys_bus_trace("src_addr malloc failed.\n");
            return;
        }
		dst_addr = (void*)g_dsp_press.dtcm_dest_addr;
	}
	else
	{
		sys_bus_trace("Invalid bbe16_move_type %d.\n", g_dsp_press.press_type);
		return ;
	}
	
    memset((void*)src_addr, 0x5a, 0x20000);
	/* 切记:此处传给phy的是U32的长度，非byte的长度 */
    ret = bsp_bbe_stress_test_start((u32)src_addr, (u32)dst_addr, (0x20000)/4, TL_PHY_INFINITE_CYCLE_MEMCPY, READ_WRITE_TEST); 
    if(ret)
    {
        sys_bus_trace("bsp_bbe_stress_test_start failed.\n");
    }
}

void sys_dsp_stop(struct master* master)
{
    int ret;
    ret = bsp_bbe_stop();
    if(ret)
    {
        sys_bus_trace("bsp_bbe_stop failed.\n");
    }
    return;
}

void sys_dsp_report(struct master* master)
{
    u32 ret;
    ret = readl(g_dsp_press.DEMEM_addr + TL_PHY_MEMCPY_RESULTE_ADDR_OFFSET);
    sys_bus_trace("bbe stress result(num of bbe transit data) is %d.\n",ret);
    return;
}

void sys_dsp_init(struct master* master)
{
    int ret;
    
    master->start = sys_dsp_start;
    master->stop = sys_dsp_stop;
    master->record = NULL;
    master->report = sys_dsp_report;

    
    ret = of_property_read_u32_index(master->np, "DEMEM_addr", 0, &g_dsp_press.DEMEM_addr);
    if(ret)
    {
        sys_bus_trace("read DEMEM_addr err\n");
        return;
    }

    ret = of_property_read_u32_index(master->np, "press_type", 0, &g_dsp_press.press_type);
    if(ret)
    {
        sys_bus_trace("read press_type err\n");
        return;
    }

    ret = of_property_read_u32_index(master->np, "DTCM_dest_addr", 0, &g_dsp_press.dtcm_dest_addr);
    if(ret)
    {
        sys_bus_trace("read DTCM_dest_addr err\n");
        return;
    }
    

    master->init_flag = 1;
    sys_bus_trace("ok\n");
}

