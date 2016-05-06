
#include <securec.h>
#include <sre_shell.h>
#include <bsp_slice.h>
#include <bsp_ipc.h>
#include <bsp_modem_log.h>

#define IPC_ACPU_INT_SRC_CCPU_MODEM_LOG (IPC_ACPU_INT_SRC_CCPU_PM_OM)

#define modem_log_pr_err(fmt, ...)      SRE_Printf("[modem log]: " fmt, ##__VA_ARGS__)
//#define modem_log_pr_debug(fmt, ...)    SRE_Printf("[modem log]: " fmt, ##__VA_ARGS__)

struct modem_log
{
	u32 wakeup_interval;
	u32 timestamp;
	u32 init_flag;
};

struct modem_log g_modem_log;

/**
 * bsp_modem_log_fwrite_trigger - wakeup acore(if neccessary) trigger file write from ring buffer to log record file
 * @usr_info: information regitered to modem log 
 */
void bsp_modem_log_fwrite_trigger(struct log_usr_info *usr_info)

{
	u32 timestamp = 0;
	u32 wakeup_interval = 0;

	/* if no application, do not wakeup acore */
	if (usr_info && usr_info->mem && usr_info->mem->app_is_active)
	{
		timestamp = bsp_get_slice_value();
		wakeup_interval = (usr_info->wake_interval? usr_info->wake_interval: g_modem_log.wakeup_interval);
		if ((timestamp - g_modem_log.timestamp) > wakeup_interval)
		{
			(void)bsp_ipc_int_send((IPC_INT_CORE_E)IPC_CORE_ACORE, (IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_MODEM_LOG);
		}

		g_modem_log.timestamp = timestamp;
	}
}

/**
 * modem_log_fwrite_trigger_force - wakeup acore and trigger file write from ring buffer to log record file
 */
void modem_log_fwrite_trigger_force(void)
{
	(void)bsp_ipc_int_send((IPC_INT_CORE_E)IPC_CORE_ACORE, (IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_MODEM_LOG);
}

int bsp_modem_log_init(void)
{
	memset_s((void*)&g_modem_log, sizeof(g_modem_log), 0, sizeof(g_modem_log));
	g_modem_log.timestamp       = bsp_get_slice_value();
	g_modem_log.wakeup_interval = MODEM_LOG_WAKEUP_INTERVAL;
	g_modem_log.init_flag       = 1;

	modem_log_pr_err("init ok\n");
	return 0;
}

