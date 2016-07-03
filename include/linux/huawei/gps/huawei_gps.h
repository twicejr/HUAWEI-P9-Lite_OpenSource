#ifndef _HUAWEI_GPS_H
#define _HUAWEI_GPS_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
    #if __cplusplus
        extern "C"{
    #endif
#endif

typedef enum _gps_modem_id_enum
{
    gps_modem_id_0,
    gps_modem_id_1,
    gps_modem_id_2,
    gps_modem_id_butt
} gps_modem_id_enum;

typedef enum _gps_rat_mode_enum
{
    gps_rat_mode_gsm,
    gps_rat_mode_wcdma,
    gps_rat_mode_lte,
    gps_rat_mode_tdscdma,
    gps_rat_mode_cdma,
    gps_rat_mode_butt
} gps_rat_mode_enum;


typedef int (*GPS_SET_REF_CLK_FUNC)(bool enable, gps_modem_id_enum modem_id, gps_rat_mode_enum rat_mode);

void register_gps_set_ref_clk_func(void* pFunc);
int set_gps_ref_clk_enable(bool enable, gps_modem_id_enum modem_id, gps_rat_mode_enum rat_mode);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
