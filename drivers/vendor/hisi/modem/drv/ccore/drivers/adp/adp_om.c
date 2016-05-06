
#include <string.h>
#include "bsp_dump.h"
#include "bsp_om.h"
#include "securec.h" 

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ENABLE_BUILD_OM
void mdrv_om_system_error(int mod_id, int arg1, int arg2, char * arg3, int arg3_len)
{
    return;
}

u8 * mdrv_om_register_field(u32 field_id, char * field_name, void * virt_addr, void * phy_addr, u32 length, u16 version)
{
    return 0;
}

u8 * mdrv_om_get_field_addr(u32 field_id)
{
    return 0;
}

u8 * mdrv_om_get_field_phy_addr(u32 field_id)
{
    return 0;
}

dump_handle mdrv_om_register_callback(char * name, dump_hook p_func)
{
    return 0;
}

s32  mdrv_om_unregister_callback(dump_handle handle)
{
    return 0;
}

void mdrv_om_set_hsoflag(u32 flag)
{
    return;
}

u32  mdrv_om_set_sysview_swt(u32 set_type, u32 set_swt, u32 period)
{
    return 0;
}

u32  mdrv_om_get_alltaskinfo(void * p_task_stru, u32 param_len)
{
    return 0;
}

s32  mdrv_om_get_rootfs(char * data, u32 len)
{
	strncpy_s(data, len,"/modem_log", len - 1);
    return 0;
}

s32  mdrv_om_get_system_reset_info(DRV_OM_SYSTEM_RESET_S * info)
{
    return 0;
}
s32 mdrv_om_set_voicestate(unsigned int flag)
{
    return 0;
}

#else
void mdrv_om_system_error(int mod_id, int arg1, int arg2, char * arg3, int arg3_len)
{
    system_error((u32)mod_id, (u32)arg1, (u32)arg2, (char *)arg3, (u32)arg3_len);
}

unsigned char * mdrv_om_register_field(unsigned int field_id, char * field_name, void * virt_addr, void * phy_addr, unsigned int length, unsigned short version)
{
    return bsp_dump_register_field(field_id, field_name, virt_addr, phy_addr, length, version);
}

unsigned char * mdrv_om_get_field_addr(unsigned int field_id)
{
    return bsp_dump_get_field_addr(field_id);
}

unsigned char * mdrv_om_get_field_phy_addr(unsigned int field_id)
{
    return bsp_dump_get_field_phy_addr(field_id);
}

dump_handle mdrv_om_register_callback(char * name, dump_hook p_func)
{
    return bsp_dump_register_hook(name, p_func);
}

int mdrv_om_unregister_callback(dump_handle handle)
{
#ifndef __CMSIS_RTOS
    return bsp_dump_unregister_hook(handle);
#else
    return 0;
#endif
}

void mdrv_om_set_hsoflag(unsigned int flag)
{
    /*bsp_om_set_hso_conn_flag(flag);*/
}

unsigned int mdrv_om_set_sysview_swt(unsigned int set_type, unsigned int set_swt, unsigned int period)
{
	return 0;
}

unsigned int mdrv_om_get_alltaskinfo(void * p_task_stru, unsigned int param_len)
{
	return 0;
}

int mdrv_om_get_rootfs(char * data, unsigned int len)
{
	(void)strncpy(data, "/modem_log", len);
    return 0;
}

int mdrv_om_get_system_reset_info(DRV_OM_SYSTEM_RESET_S * info)
{
    return 0;
}
int mdrv_om_set_voicestate(unsigned int flag)
{
    return (int)bsp_dump_mark_voice(flag);
}
#endif

#ifdef __cplusplus
}
#endif


