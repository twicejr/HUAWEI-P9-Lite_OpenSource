
#include <boot.h>
#include <debug.h>
#include <hi_modem.h>
#include <module.h>
#include <modemid.h>
#include <module_level.h>

#include <modem.h>
#include <nv_boot.h>
#include <pintrl_balong.h>
#include <sys.h>
#include <gpio.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_memrepair.h>
#include <bsp_icc.h>
#include <bsp_temperature.h>
#include <fastboot_interface.h>
#include <pm_om_smem.h>
#include <bsp_sram.h>
#include <bsp_version.h>
#include <param_cfg_to_sec.h>

#define MODEM_CSHELL_DEFAULT	0x0
#define PRT_FLAG_EN_MAGIC_M		0x24680136

//lint --e{717,835}


void startup_modem(void)
{
}

int set_modem_cshell_mod(unsigned int mod)
{
//lint --e{715}
	writel(mod, SHM_BASE_ADDR + SHM_OFFSET_CHSELL_FLAG);
	return 0;
}

void shared_flag_clear(void)
{
	unsigned int i;
	memset((void *)SHM_ADDR_ICC, 0, SHM_SIZE_ICC);/* [false alarm]:屏蔽Fortify错误 */

	/****sync shmem clear***/
	memset((void*)(SHM_BASE_ADDR+SHM_OFFSET_SYNC),0, SHM_SIZE_SYNC);/* [false alarm]:屏蔽Fortify错误 */

	/****memrepair shmem clear***/
	for(i=0;i<SHM_SIZE_MEMREPAIR;){
		writel(MR_POWERON_FLAG, SHM_MEM_MEMREPAIR_ADDR+i);
		i+=4;
	}

	/****uart shmem clear***/
	memset((void*)((unsigned long)SHM_BASE_ADDR+SHM_OFFSET_UART_FLAG),0, SHM_SIZE_UART_FLAG);/* [false alarm]:屏蔽Fortify错误 */

    /****via modem is active flag clean***/
    memset((void *)(SHM_BASE_ADDR+SHM_OFFSET_RFFE_VIA_LP_FLAG),0 , SHM_SIZE_RFFE_VIA_LP_FLAG);/* [false alarm]:屏蔽Fortify错误 */

}

void fastboot_set_modem_cshell()
{
	set_modem_cshell_mod(PRT_FLAG_EN_MAGIC_M);
}

/* set socp encsrc chan for security */
void set_socp_sec_config(void)
{
    /* set 4-9 12-14,14-31 encsrc chan to secure access */
    writel(0xffff7bf0, HI_SOCP_REGBASE_ADDR + 0x30);
}

int modem_main()
{
    unsigned int cshell_nv = 0;

	PRINT_ERROR("modem_main start\n");


	shared_flag_clear();

    /*modem nv xml解析依赖版本号 ，获取版本号需要提前 yuyangyang*/
    bsp_version_ddr_init();
    /*modem nv初始化，加载nv数据到共享内存，解析xml*/
	nv_init();

	/* 温饱初始化，放在NV初始化之后 */
	bsp_temperature_init();

    set_socp_sec_config();
    if(bsp_nvm_read(NV_ID_DRV_UART_SHELL_FLAG, (u8 *)&cshell_nv, (u32)sizeof(cshell_nv)))
    {
        PRINT_ERROR("read NV error\n");
        cshell_nv |= (0x1UL << 8);
    }
	(void)set_modem_cshell_mod(cshell_nv & (0x1UL << 8) ? PRT_FLAG_EN_MAGIC_M : MODEM_CSHELL_DEFAULT);

	pm_om_smem_init();

	set_param_cfg_to_sec();

	/* modem相关镜像加载和安全校验已挪到Kernel中实现 */

	PRINT_ERROR("modem_main end\n");
	return 0;
}
/*
修改此函数时请本地请注意消除pclint和编译waring
*/
void modem_config_info(int coreid, void* pconfig)
{
	struct modem_mcu_config *pmcuconfig;
	struct modem_hifi_config *phificonfig;

	if (coreid == MODEM_CONFIG_MCU) {
		pmcuconfig = (struct modem_mcu_config *)pconfig;
		/*C核启动地址*/
		pmcuconfig->ccpu_startup.addr = (u32)MCORE_TEXT_START_ADDR;

		/*温保地址*/
		pmcuconfig->temprature.addr = (u32)(SHM_BASE_ADDR + SHM_OFFSET_TEMPERATURE);
		pmcuconfig->temprature.size = (u32)(SHM_SIZE_TEMPERATURE);
		/*ICC地址*/
		pmcuconfig->icc_ccpu2mcu.addr = (u32)(unsigned long)ADDR_MCCORE_RECV;
		pmcuconfig->icc_ccpu2mcu.size = (u32)(STRU_SIZE + ICC_MCCORE_SIZE);
		pmcuconfig->icc_mcu2ccpu.addr = (u32)(unsigned long)ADDR_MCCORE_SEND;
		pmcuconfig->icc_mcu2ccpu.size = (u32)(STRU_SIZE + ICC_MCCORE_SIZE);
		/*SRAM备份地址*/
		pmcuconfig->sram_backup.addr = (u32)(SHM_BASE_ADDR + SHM_OFFSET_RESTORE_AXI);
        #ifdef CPHY_SRAM_SIZE
		pmcuconfig->sram_backup.size= (u32)(DRV_SRAM_SIZE+CPHY_SRAM_SIZE);
        #else
		pmcuconfig->sram_backup.size= (u32)(DRV_SRAM_SIZE);
        #endif

		pmcuconfig->modem_pm_stats.addr = (u32)(SHM_BASE_ADDR + SHM_OFFSET_MODEM_SR_STAMP);
		pmcuconfig->modem_pm_stats.size= (u32)SHM_SIZE_MODEM_SR_STAMP;

		pmcuconfig->bbe16_sleep_flag_0.addr = (u32)(SRAM_BASE_ADDR + SRAM_OFFSET_TLDSP_SHARED);
#ifdef CPHY_SRAM_ADDR
		pmcuconfig->bbe16_sleep_flag_1.addr = (u32)(CPHY_SRAM_ADDR);
#endif

		PRINT_ERROR("ccpu_startup.addr 0x%x\n", pmcuconfig->ccpu_startup.addr);

		PRINT_ERROR("temprature.addr 0x%x\n", pmcuconfig->temprature.addr);
		PRINT_ERROR("temprature.size 0x%x\n", pmcuconfig->temprature.size);

		PRINT_ERROR("icc_ccpu2mcu.addr 0x%x\n", pmcuconfig->icc_ccpu2mcu.addr);
		PRINT_ERROR("icc_ccpu2mcu.size 0x%x\n", pmcuconfig->icc_ccpu2mcu.size);

		PRINT_ERROR("icc_mcu2ccpu.addr 0x%x\n", pmcuconfig->icc_mcu2ccpu.addr);
		PRINT_ERROR("icc_mcu2ccpu.size 0x%x\n", pmcuconfig->icc_mcu2ccpu.size);

		PRINT_ERROR("sram_backup.addr 0x%x\n", pmcuconfig->sram_backup.addr);
		PRINT_ERROR("sram_backup.size 0x%x\n", pmcuconfig->sram_backup.size);

		PRINT_ERROR("modem_pm_stats.addr 0x%x\n", pmcuconfig->modem_pm_stats.addr);
		PRINT_ERROR("modem_pm_stats.size 0x%x\n", pmcuconfig->modem_pm_stats.size);

		PRINT_ERROR("bbe16_sleep_flag_0.addr 0x%x\n", pmcuconfig->bbe16_sleep_flag_0.addr);
		PRINT_ERROR("bbe16_sleep_flag_1.addr 0x%x\n", pmcuconfig->bbe16_sleep_flag_1.addr);
		return;
	}

	if (coreid == MODEM_CONFIG_HIFI) {
		phificonfig = (struct modem_hifi_config *)pconfig;
		phificonfig->icc_ccpu2hifi.addr = (u32)(unsigned long)ADDR_HIFI_VOS_MSG_RECV;
		phificonfig->icc_ccpu2hifi.size = (u32)(STRU_SIZE + ICC_HIFI_VOS_SIZE);
		phificonfig->icc_hifi2ccpu.addr = (u32)(unsigned long)(ADDR_HIFI_VOS_MSG_SEND);
		phificonfig->icc_hifi2ccpu.size = (u32)(STRU_SIZE + ICC_HIFI_VOS_SIZE);
		phificonfig->icc_tphy2hifi.addr = (u32)(unsigned long)ADDR_HIFI_TPHY_MSG_RECV;
		phificonfig->icc_tphy2hifi.size = (u32)(STRU_SIZE + ICC_HIFI_TPHY_SIZE);
		phificonfig->icc_hifi2tphy.addr = (u32)(unsigned long)ADDR_HIFI_TPHY_MSG_SEND;
		phificonfig->icc_hifi2tphy.size = (u32)(STRU_SIZE + ICC_HIFI_TPHY_SIZE);
		PRINT_ERROR("icc_ccpu2hifi.addr 0x%x\n", phificonfig->icc_ccpu2hifi.addr);
		PRINT_ERROR("icc_ccpu2hifi.size 0x%x\n", phificonfig->icc_ccpu2hifi.size);

		PRINT_ERROR("icc_hifi2ccpu.addr 0x%x\n", phificonfig->icc_hifi2ccpu.addr);
		PRINT_ERROR("icc_hifi2ccpu.size 0x%x\n", phificonfig->icc_hifi2ccpu.size);
		PRINT_ERROR("icc_tphy2hifi.addr 0x%x\n", phificonfig->icc_tphy2hifi.addr);
		PRINT_ERROR("icc_tphy2hifi.size 0x%x\n", phificonfig->icc_tphy2hifi.size);

		PRINT_ERROR("icc_hifi2tphy.addr 0x%x\n", phificonfig->icc_hifi2tphy.addr);
		PRINT_ERROR("icc_hifi2tphy.size 0x%x\n", phificonfig->icc_hifi2tphy.size);

		return;
	}


}
int load_modem_init(struct system_table *systable)
{
//lint --e{715,818}
	return OK;
}

static struct load_modem_operators load_modem_ops = {
	.modem_main	= (MODEM_MAIN)modem_main,
	.fastboot_set_modem_cshell	= fastboot_set_modem_cshell,
	.startup_modem	= startup_modem,
    .modem_get_config = modem_config_info,
};

static struct module_data load_modem_prv_data = {
	.name		= MODEM_MODULE_NAME_STR,
	.level		= MODEM_MODULE_LEVEL,
	.init 		= load_modem_init,
	.operators 	= &load_modem_ops,
};

MODULE_INIT(MODEM_MODULE_NAME, load_modem_prv_data);


