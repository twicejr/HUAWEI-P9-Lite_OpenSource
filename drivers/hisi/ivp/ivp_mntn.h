#ifndef __IVP_MNTN_H__
#define __IVP_MNTN_H__
//#define IVP_DEBUGFS
extern void ivp_reg_dump_wdg(void);
extern void ivp_reg_dump_smmu(void);
extern void ivp_reg_dump_cfg(void);
extern int ivp_debugfs_register(void);
extern int ivp_debugfs_unregister(void);
#endif
