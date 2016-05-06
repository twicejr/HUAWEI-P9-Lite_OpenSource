#ifndef HISI_HI6521__CHARGER_POWER_H
#define HISI_HI6521__CHARGER_POWER_H

extern int scharger_power_status(int id);
extern int scharger_power_on(int id);
extern int scharger_power_off(int id);
extern int scharger_power_set_voltage(unsigned int vset_regs,unsigned int mask,int shift,int index);
extern int scharger_power_get_voltage_index(unsigned int vget_regs,unsigned int mask,int shift);
extern int scharger_power_set_current_limit(unsigned int vset_regs,unsigned int mask,int shift,int index);
extern int scharger_power_get_current_limit_index(unsigned int vget_regs,unsigned int mask,int shift);
extern int scharger_flash_led_timeout_enable(void);
extern int scharger_flash_led_timeout_disable(void);
extern int scharger_flash_led_timeout_config(unsigned int timeoutMs);
extern int scharger_flash_torch_timeout_config(unsigned int timeoutSec);
#endif
