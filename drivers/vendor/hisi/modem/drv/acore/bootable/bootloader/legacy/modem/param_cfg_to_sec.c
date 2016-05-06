#include <osl_types.h>
#include <bsp_shared_ddr.h>
#include <param_cfg_to_sec.h>

/* set secure os param cfg*/
void set_param_cfg_to_sec(void)
{
#ifdef SHM_SEC_BASE_ADDR
    u64 cfg_base;

    /*lint -save -e835*/
    cfg_base = SHM_SEC_BASE_ADDR + SHM_OFFSET_PARAM_CFG;
    g_param_cfg *param_cfg = ((g_param_cfg * )(cfg_base));

    *(volatile u64 *) (BALONG_PARAM_BASE_ADDR + PARAM_MAGIC_OFFSET) = 0xdeadbeef;
    *(volatile u64 *) (BALONG_PARAM_BASE_ADDR + PARAM_CFG_OFFSET) = (cfg_base);

    param_cfg->magic = 0xdeadbeef;

    param_cfg->param_cfg_size = SHM_SIZE_PARAM_CFG;

    param_cfg->icc_channel_base_addr = SHM_SEC_BASE_ADDR + SHM_OFFSET_SEC_ICC;
    /*lint -restore*/

    param_cfg->icc_channel_max_size = SHM_SIZE_SEC_ICC;
#endif
}


