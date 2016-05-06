
#include <symbol.h>
#include <m3_dump.h>
#include <product_config.h>
#include <bsp_rsracc.h>
/*lint --e{18, 532, 546} */
extern int help();
extern int d();
extern int m();
extern void system_error (unsigned int mod_id, unsigned int arg1, unsigned int arg2, char *data, unsigned int length);
extern void bsp_wdt_print_debug(void);
extern int bsp_wdt_stop(void);
extern void cpufreq_print_debug(int flag);
extern void dump_wdt_hook(signed int core);
#ifdef CONFIG_M3PM
extern void pm_set_debug(unsigned int type, unsigned int flag);
extern int pm_print_debug();
extern int pm_wakeup_acore();
extern int pm_wakeup_ccore();
#endif
#ifdef CONFIG_M3PM_TEST
extern void set_pm_test_timer(unsigned int timeout);
extern void m3_send_a_ipc(void);
extern void m3_send_c_ipc(void);
#endif
extern int busstress_test_start(void);
extern int busstress_test_stop(void);
extern int change_port(int id);
extern void dfs_set_profile(u32 profile);


struct symbol kallsyms[] = {
	{"help", (unsigned long)&help},
	{"d", (unsigned long)&d},
	{"m", (unsigned long)&m},
	{"system_error", (unsigned long)&system_error},
	{"cpufreq_print_debug", (unsigned long)&cpufreq_print_debug},
    {"dump_wdt_hook", (unsigned long)&dump_wdt_hook},
    {"bsp_wdt_print_debug", (unsigned long)&bsp_wdt_print_debug},
#ifdef CONFIG_M3PM
	{"pm_set_debug", (unsigned long)&pm_set_debug},
	{"pm_print_debug", (unsigned long)&pm_print_debug},
	{"pm_wakeup_acore", (unsigned long)&pm_wakeup_acore},
	{"pm_wakeup_ccore", (unsigned long)&pm_wakeup_ccore},
#endif
#ifdef CONFIG_M3PM_TEST
    {"set_pm_test_timer", (unsigned long)&set_pm_test_timer},
    {"m3_send_a_ipc", (unsigned long)&m3_send_a_ipc},
    {"m3_send_c_ipc", (unsigned long)&m3_send_c_ipc},
#endif
   // {"udelay", (unsigned long)&udelay},
    //{"bsp_get_slice_value", (unsigned long)&bsp_get_slice_value},
    //{"bsp_get_slice_value_hrt", (unsigned long)&bsp_get_slice_value_hrt},
    {"dfs_set_profile", (unsigned long)&dfs_set_profile},
    {"change_port", (unsigned long)&change_port},
    {"rsracc_checkflag", (unsigned long)&bsp_rsracc_set_checkflag},
#ifdef CONFIG_MODULE_BUSSTRESS
	{"busstress_test_start", (unsigned long)&busstress_test_start},
	{"busstress_test_stop", (unsigned long)&busstress_test_stop},	
#endif
};

unsigned kallsyms_count = sizeof(kallsyms)/sizeof(kallsyms[0]);
