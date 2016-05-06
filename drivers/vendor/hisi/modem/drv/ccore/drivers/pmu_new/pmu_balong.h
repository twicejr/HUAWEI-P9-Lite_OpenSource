/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  pmu_test.h
*
*   作    者 :  x00195528
*
*   描    述 :  PMU模块测试模块头文件
*************************************************************************/
#ifndef _PMU_BALONG_H_
#define _PMU_BALONG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_pmu.h>
#include <bsp_icc.h>
#include <bsp_om.h>

#define  INVALIED_VALUE                 0xFF

/*print*/
#define  pmu_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  pmu_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct pmu_adp_ops{
    char* (*version_get)(void);
    int (*sim_upres_disable)(u32 sim_id);
    void (*dcxo_compensate)(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
    void (*rfclk_enable)(u32 rf_id);
    void (*rfclk_disable)(u32 rf_id);
    int (*rfclk_is_enabled)(u32 rf_id);
    u32 (*get_rtc_value)(void);
    int (*ocp_register)(int volt_id,PMU_OCP_FUNCPTR func);
};

/*函数声明*/
void pmu_pmic_init(void);
void pmu_dcdc_init(void);
int pmu_adpops_register(struct pmu_adp_ops *pmic_ops);

void pmic_log_level_set_debug(u32 level);
u32 pmic_log_level_get_debug(void);
void pmic_volt_set_debug(int volt_id, int voltage);
void pmic_addr_debug(void);
void pmic_voltage_table_debug();
void pmic_volt_id_debug(void);
void pmic_volt_state_debug(void);
void dcdc_state_debug(void);
void pmic_xo_reg_debug(void);
void pmic_xo_state_debug(void);
void pmu_regulator_debug(void);
void pmic_get_shm_mem_debug(void);
void pmu_help(void);
void dummy_pmu_init(void);
u32 dummy_info_get_handler(void);
char* dummy_version_get(void);
int dummy_sim_upres_disable(u32 para);
void dummy_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
void dummy_rfclk_onoff(u32 para);
int dummy_get_rfclk_status(u32 rfid);
u32 dummy_get_rtc_value(void);
int dummy_ocp_register(int volt_id,PMU_OCP_FUNCPTR func);

#ifdef __cplusplus
}
#endif

#endif /* end #define _PMU_TEST_H_*/

