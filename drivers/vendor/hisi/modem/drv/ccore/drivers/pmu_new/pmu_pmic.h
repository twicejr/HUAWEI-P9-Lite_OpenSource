/*************************************************************************
*   版权所有(C) 1987-2004, 深圳华为技术有限公司.
*
*   文 件 名 :  pmu_pmic.h
*
*   作    者 :  x00195528
*
*   描    述 :  PMU模块电源芯片头文件
*************************************************************************/
#ifndef _PMU_PMIC_H_
#define _PMU_PMIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <osl_list.h>
#include <osl_spinlock.h>
#include <mdrv_pmu.h>
#include <hi_pmu.h>
#include <bsp_pmu.h>

typedef unsigned long pmic_voltflags_t;

struct pmic_reg_cfg
{
    u32 addr;
    u32 value;
};
struct pmic_volt_reg
{
    u32 en_reg;
    u32 en_bit;
    u32 dis_reg;
    u32 dis_bit;
    u32 state_reg;
    u32 state_bit;
    u32 voltage_reg;
    u32 voltage_mask;
};
enum pmic_volt_enum{
    VOLT_TABLE,
    VOLT_LINEAR,
    VOLT_CONST,
};

struct pmic_volt_ocp
{
	struct list_head   list;
	PMU_OCP_FUNCPTR func;
};
struct pmic_volt_ctrl
{
    u32 id;
    const char *name;
    u32 voltage_flag;/*0:table;1:linear;others:consts*/
    u32 voltage_nums;
    u32 voltage_const;/*const voltage value*/
    u32 voltage_base;/*linear voltage base*/
    u32 voltage_step;/*linear voltage step*/
    const u32 *voltage_table;
    struct pmic_volt_reg volt_reg;
    spinlock_t volt_lock;
    u32 off_on_delay;/*struct timeval last_off_time;*/
    struct list_head ocp_list;
};
struct pmic_volt_info
{
    u32 magic_start;
    int volt_min;
    int volt_max;
    struct pmic_volt_ctrl *volt_ctrl;
    u32 magic_end;
};
struct xorf_reg_ctrl
{
    u32 reg_base;
    u32 reg_bit;
};/* rf时钟操作的基址和bit */
struct xorf_freq_ctrl
{
    u32 freq_addr;
    u32 freq_mask;
    u32 freq_offset;
    u32 freq_value;
};/* 控制rf的驱动能力 */
struct pmic_xorf_ctrl
{
    u32 rf_id;
    struct xorf_freq_ctrl rf_clk;
    struct xorf_reg_ctrl reg_ctrl;
    struct xorf_freq_ctrl freq_ctrl;
};
struct xo_reg_ctrl
{
    u32 c1_base;
    u32 c2_base;
    u32 c2_mask;
    u32 c2_offset;
};/* 控制rf的 c1 c2 */
struct pmic_xo_info
{
    spinlock_t xo_lock;
    struct xo_reg_ctrl xo_ctrl;/*c1c2*/
    u32 xorf_num;
    spinlock_t xorf_lock;
    struct pmic_xorf_ctrl *xorf_ctrl;
};/* 控制rf */
struct dcdc_ctrl
{
    u32 id;
    const char *name;
    u32 gpio_id;
};
struct dcdc_info
{
    u32 dc_num;
    struct dcdc_ctrl *dc_ctrl;
};

void pmic_reg_write(u32 addr, u32 value);
void pmic_reg_read(u32 addr, u32 *pValue);
void pmic_reg_write_mask(u32 addr, u32 value, u32 mask);
int pmic_reg_show(u32 addr);
u32 pmic_get_base_addr(void);

#define FEATURE_DRV_SINGLE_XO
void pmic_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
void pmic_volt_init(void);
void pmic_ocp_init(void);
void pmic_volt_dts_init(void);
void pmic_xo_dts_init(void);
void dcdc_dts_init(void);
int pmic_ocp_register(int volt_id,PMU_OCP_FUNCPTR func);
void pmic_dcxo_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);

/*test/debug use*/
int pmic_volt_enable(int volt_id);
int pmic_volt_disable(int volt_id);
int pmic_volt_is_enabled(int volt_id);
int pmic_volt_get_voltage(int volt_id);
int pmic_volt_set_voltage(int volt_id, int min_uV, int max_uV,unsigned *selector);
int pmic_volt_list_voltage(int volt_id, unsigned selector);
int dcdc_volt_enable(int dc_id);
int dcdc_volt_disable(int dc_id);
int dcdc_volt_is_enabled(int dc_id);
void pmic_rfclk_enable(u32 rf_id);
void pmic_rfclk_disable(u32 rf_id);
int pmic_rfclk_is_enabled(u32 rf_id);
u32 pmic_dcxo_compensate_get(DCXO_COMPENSATE_ID_E dcxoId);
u32 pmic_rffreq_get(u32 rf_id);
char* pmic_version_get(void);

#ifdef CONFIG_AVOID_RFIC6362_LDO27_LEAK
int pmic_set_ldo27_ao(int ao);
#endif


#ifdef __cplusplus
}
#endif

#endif /* end #define _PMU_TEST_H_*/

