#include <fastboot_interface.h>
#include <boot.h>
#include <nv_boot.h>
#include <bsp_pm_om.h>

struct pm_om_fastboot
{
	struct pm_om_smem_cfg *smem;
	int init_flag;
};

struct pm_om_fastboot g_pm_om_fastboot;

void pm_om_smem_init(void)
{
	u32 mem_size = 0;
	struct pm_om_smem_cfg *smem = NULL;
	DRV_PM_OM_CFG_STRU nv_cfg;

	/* NV控制是否打开pm log */
	memset((void *)&nv_cfg, 0, (u32)sizeof(nv_cfg));
	if(NV_OK != bsp_nvm_read(NV_ID_DRV_PM_OM, (u8*)&(nv_cfg), (u32)sizeof(nv_cfg)))
	{
		cprintf("[%s]: nv[0x%x] read fail\n", __FUNCTION__, NV_ID_DRV_PM_OM);
	}

	smem     = (struct pm_om_smem_cfg *)PM_OM_LOG_AREA; /*lint !e838 !e826 !e835*/
	mem_size = SHM_SIZE_PM_OM;/*lint !e838*/
	smem->file_head.reserved = PM_OM_PROT_MAGIC1;
	if (PM_OM_USE_NORMAL_DDR == nv_cfg.mem_ctrl && 1 == bsp_socpmem_enable())
	{	/* 如果modem nv配置成使用socp内存, 并且ap侧预留了这块内存 */
		smem->file_head.reserved = PM_OM_PROT_MAGIC2;

		smem     = (struct pm_om_smem_cfg *)(DDR_SOCP_ADDR + PM_OM_SOCP_OFFSET);
		mem_size = (DDR_SOCP_SIZE - PM_OM_SOCP_OFFSET) ;
		smem->file_head.reserved = PM_OM_PROT_MAGIC1;
	}

	/* 文件头初始化 */
	smem->file_head.magic    = PM_OM_MAGIC_PMLG;
	smem->file_head.len      = mem_size;
	smem->file_head.version  = 0;

	smem->sn                 = 0;
	memcpy((void *)&(smem->nv_cfg), (void *)&nv_cfg, (u32)sizeof(nv_cfg));

	/* log: ring buffer信息结构初始化 */
	smem->mem_info.magic         = PM_OM_PROT_MAGIC1;
	smem->mem_info.read          = 0;
	smem->mem_info.write         = 0;
	smem->mem_info.size          = mem_size - (u32)sizeof(struct pm_om_smem_cfg);
	smem->mem_info.app_is_active = 0;

	g_pm_om_fastboot.smem = smem;
	g_pm_om_fastboot.init_flag = 1;
}

