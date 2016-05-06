
#include<sre_shell.h>
#include <bsp_thermal.h>

u32 g_thermal_core_num = 4;

int mdrv_thermal_up(unsigned int core_num)
{
    int ret = 0;
    u32 icc_info = 0;
    g_thermal_core_num = core_num;
    icc_info = SYSTEM_HEATING_BEGIN | g_thermal_core_num;
    ret = bsp_icc_send((u32)ICC_CPU_APP, (u32)SYSTEM_HEADING_CHAN_ID,(u8*)&icc_info, sizeof(u32));
    if(ret > 0)
    {
        return THERMAL_UP_OK;
    }
    thermal_print("core num = %d,bsp_icc_send errNo = 0x%x\n", g_thermal_core_num, ret);
    return THERMAL_UP_ERROR;
}
int mdrv_thermal_down(unsigned int core_num)
{
    int ret = 0;
    u32 icc_info = SYSTEM_HEATING_END | g_thermal_core_num;
    ret = bsp_icc_send((u32)ICC_CPU_APP, (u32)SYSTEM_HEADING_CHAN_ID,(u8*)&icc_info, sizeof(u32));
    if(ret > 0)
    {
        return THERMAL_UP_OK;
    }
    thermal_print("core num = %d,bsp_icc_send errNo = 0x%x\n", g_thermal_core_num, ret);
    return THERMAL_UP_ERROR;
}



