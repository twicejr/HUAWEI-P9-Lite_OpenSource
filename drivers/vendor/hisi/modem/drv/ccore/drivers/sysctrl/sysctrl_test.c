/*************************************************************************
*   版权所有(C) 2008-2014, 深圳华为技术有限公司.
*
*   文 件 名 :  sysctrl_test.c
*
*   作    者 :  n00261894
*
*   描    述 :  系统控制器测试模
*
*   修改记录 :  2014年11月12日  v1.00  n00261894  创建
*************************************************************************/
#include <mdrv_sysctrl.h>
#include <osl_types.h>
#include <bsp_om.h>
#include <bsp_sysctrl.h>

#define HI_SC_CTRL0_OFFSET 0x400

#define  sc_test(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SYSCTRL, "[sysctrl_test]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

void sysctrl_virt_test(void* phy_addr)
{   
	sc_test("sysctrl virt addr = 0x%x\n", bsp_sysctrl_addr_get(phy_addr));
}

void sysctrl_virt_byindex(BSP_SYSCTRL_INDEX index)
{
    sc_test("sysctrl virt addr = 0x%x\n",bsp_sysctrl_addr_byindex(index));
} 

int sysctrl_test_judge(unsigned int setData)
{
    unsigned int getData = 0;

    if(mdrv_sysctrl_set_regval(HI_SC_CTRL0_OFFSET, setData)) {
        sc_test("sysctrl set failed!\n");
        return -1;
    }
    if(!mdrv_sysctrl_get_regval(HI_SC_CTRL0_OFFSET, &getData)) {
        if((getData&0x1) == (setData&0x1)) {
            sc_test("sysctrl test success!\n");
            return 0;
        }
        else {
            sc_test("sysctrl test failed! setData = 0x%x,getData = 0x%x\n",setData,getData);
            return -1;
        }
    }
    else
        return -1;
}

int sysctrl_mdrv_api_test(void)
{
    unsigned int getData = 0;
    unsigned int tmp;

    if(!mdrv_sysctrl_get_regval(HI_SC_CTRL0_OFFSET, &getData)) {
	    tmp = getData & 0x1;
        if(tmp == 0x0) {
            if(0 != sysctrl_test_judge(0x1|getData))
                return -1;
            /*resume*/
            if(0 != sysctrl_test_judge(0xfffe&getData))
                return -1;
        }
        else {          
            if(0 != sysctrl_test_judge(0xfffe&getData))
                return -1;
            /*resume*/
            if(0 != sysctrl_test_judge(0x1|getData))
                return -1;
        }
    }
    else
        return -1;

    return 0;
}

