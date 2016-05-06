#ifndef __HISI_IPC_H__
#define __HISI_IPC_H__
void hisi_ipc_core_suspend(unsigned int core, unsigned int cluster, unsigned int affinity_level);
void hisi_ipc_pm_suspend(unsigned int core, unsigned int cluster, unsigned int affinity_level);

#endif
