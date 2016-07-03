/*lint --e{522,534,537} */
#include <of.h>

#include <osl_bio.h>
#include <osl_types.h>
#include <osl_thread.h>
#include <osl_malloc.h>
#include <securec.h>

#include <drv_nv_id.h>
#include <drv_nv_def.h>

#include <bsp_om.h>
#include <bsp_bbp.h>
#include <bsp_dpm.h>
#include <bsp_nvim.h>
#include <bsp_cross_mipi.h>
#include <bsp_hardtimer.h>
#include <hi_cross_mipi.h>

#ifdef CROSS_MIPI_HI3650

u32 g_is_cross_mipi_inited = 0;

u32 g_cross_mipi_ctu_base_addr = 0;
u32 g_cross_mipi_mem_base_addr = 0;
u32 g_cross_mipi_ctrl_base_addr = 0;

#ifdef CONFIG_CCORE_PM

int bsp_cross_mipi_prepare(struct dpm_device *dev)
{
    writel(0, g_cross_mipi_ctrl_base_addr + CROSS_MIPI_EN_OFFSET);

    return 0;
}

int bsp_cross_mipi_resume(struct dpm_device *dev)
{
    bsp_cross_mipi_init();

    return 0;
}

static struct dpm_device g_cross_mipi_dpm_device = {
    .device_name = "cross_mipi",
    .prepare = bsp_cross_mipi_prepare,
    .suspend_early= NULL,
    .suspend = NULL,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume = NULL,
    .resume_late = NULL,
    .complete = bsp_cross_mipi_resume,
};
#endif

void bsp_cross_mipi_init(void)
{
    u32 i = 0;
    int ret = 0;

    static NV_CROSS_MIPI_MEM cross_mipi_mem;
    static NV_CROSS_MIPI_CTRL cross_mipi_ctrl;

    if (!g_is_cross_mipi_inited) {
        (void)memset_s((void*)&cross_mipi_mem, sizeof(cross_mipi_mem), 0, sizeof(cross_mipi_mem));
        (void)memset_s((void*)&cross_mipi_ctrl, sizeof(cross_mipi_ctrl), 0, sizeof(cross_mipi_ctrl));

        ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_MEM_ID, (u8*)&cross_mipi_mem, sizeof(cross_mipi_mem));
        if (ret) {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CROSS_MIPI, "fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_MEM_ID);
            return;
        }

        ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_CTRL_ID, (u8*)&cross_mipi_ctrl, sizeof(cross_mipi_ctrl));
        if (ret) {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CROSS_MIPI, "fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_CTRL_ID);
            return;
        }

        g_cross_mipi_ctu_base_addr = (u32)bsp_bbp_part_addr_get(BBP_CTU);
        g_cross_mipi_mem_base_addr = (u32)bsp_bbp_part_addr_get(BBP_CROSS_MIPI_MEM);
        g_cross_mipi_ctrl_base_addr = (u32)bsp_bbp_part_addr_get(BBP_CROSS_MIPI_CTRL);

#ifdef CONFIG_CCORE_PM
        ret = bsp_device_pm_add(&g_cross_mipi_dpm_device);
        if (ret) {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CROSS_MIPI, "fail to add cross_mipi dpm device\r\n");
            return;
        }
#endif
    }

    if (cross_mipi_ctrl.tuner_en) {
        writel(cross_mipi_ctrl.tuner_en, g_cross_mipi_ctrl_base_addr + CROSS_MIPI_EN_OFFSET);
        writel(cross_mipi_ctrl.tuner_req_en, g_cross_mipi_ctrl_base_addr + CROSS_MIPI_REQ_EN_OFFSET);

        writel(~cross_mipi_ctrl.reg.tuner_mipi_mask, g_cross_mipi_ctu_base_addr + CROSS_MIPI_MASK_OFFSET);
        writel(~cross_mipi_ctrl.reg.gpio_primary_en, g_cross_mipi_ctu_base_addr + CROSS_MIPI_M0_LINE_P_MASK_OFFSET);
        writel(~cross_mipi_ctrl.reg.gpio_secondary_en, g_cross_mipi_ctu_base_addr + CROSS_MIPI_M0_LINE_S_MASK_OFFSET);
        writel(~cross_mipi_ctrl.reg.gpio_modem1_en, g_cross_mipi_ctu_base_addr + CROSS_MIPI_M1_LINE_MASK_OFFSET);

        for (i = 0; i < sizeof(cross_mipi_mem.gpio_buffer)/sizeof(cross_mipi_mem.gpio_buffer[0][0]); i++)
            writel(cross_mipi_mem.gpio_buffer[0][i], g_cross_mipi_mem_base_addr + CROSS_MIPI_GPIO_MEM_OFFSET + i*4);

        for (i = 0; i < sizeof(cross_mipi_mem.mipi_buffer)/sizeof(cross_mipi_mem.mipi_buffer[0][0]); i++)
            writel(cross_mipi_mem.mipi_buffer[0][i], g_cross_mipi_mem_base_addr + CROSS_MIPI_MIPI_MEM_OFFSET + i*4);
        writel(0x7,   g_cross_mipi_ctu_base_addr + CROSS_MIPI_FORCE_OUTPUT_OFFSET);
        writel(0x700, g_cross_mipi_ctu_base_addr + CROSS_MIPI_OUTPUT_VALUE_OFFSET);
        udelay(1);

        writel(0x0,   g_cross_mipi_ctu_base_addr + CROSS_MIPI_OUTPUT_VALUE_OFFSET);
        writel(0x0,   g_cross_mipi_ctu_base_addr + CROSS_MIPI_FORCE_OUTPUT_OFFSET);
    }

    if (!g_is_cross_mipi_inited) {
        g_is_cross_mipi_inited = 1;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CROSS_MIPI, "cross mipi init ok\n");
    }
}

#else
#define cross_mipi_print_error(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_LOG_LEVEL_ERROR, "[CROSSMIPI]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

struct cross_mipi_info{
    u32 is_inited;                     /*是否初始化完成*/
    u32 ctu_base;                      /*ctu基地址*/
    u32 mem_base;                      /*cross mipi memory 基地址*/
    u32 ctrl_base;                     /*cross mipi 控制信息配置基地址*/
    struct bbp_dma_cfg      dma_mipi;  /*cross mipi 使用bbp dma控制信息*/
    struct bbp_dma_cfg      dma_gpio;  /*cross gpio 使用bbp dma控制信息*/
    NV_CROSS_MIPI_GPIO_CTRL ctrl_info; /*从nv 中读取的tuner配置信息*/
    u32  *gpio_mem;                    /*从nv 中读取的cross gpio memory 配置*/
    u32  *mipi_mem;                    /*从nv 中读取的cross mipi memory 配置*/
    u32   mipi_mem_len;                /*从nv 中读取的cross mipi memory len*/
    u32 resume_flag;
};


int bsp_cross_mipi_prepare(struct dpm_device *dev)
{
    struct cross_mipi_info *tuner = dev->platform_data;
    writel(0, tuner->ctrl_base + CROSS_MIPI_EN_OFFSET);

    return 0;
}

int bsp_cross_mipi_resume(struct dpm_device *dev)
{
    struct cross_mipi_info *tuner = dev->platform_data;
    bsp_cross_mipi_init();

    tuner->resume_flag = 1;
    return 0;
}

int bsp_cross_mipi_complete(struct dpm_device *dev)
{
    struct cross_mipi_info *tuner = dev->platform_data;
    if(tuner->resume_flag && tuner->ctrl_info.tuner_en){/*depands resume*/
        bsp_bbp_dma_finish(&(tuner->dma_gpio));
        bsp_bbp_dma_finish(&(tuner->dma_mipi));
        tuner->resume_flag = 0;
    }
    writel(tuner->ctrl_info.tuner_en, tuner->ctrl_base + CROSS_MIPI_EN_OFFSET);
    return 0;

}
static struct dpm_device g_tuner_dpm_device = {
    .device_name = "cross_mipi",
    .prepare = bsp_cross_mipi_prepare,
    .suspend_early= NULL,
    .suspend = NULL,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume = NULL,
    .resume_late = bsp_cross_mipi_resume,
    .complete = bsp_cross_mipi_complete,
};

static int cross_mipi_read_nv(struct cross_mipi_info *tuner)
{
    u32   nv_len         = 0;
    u32   mipi_tuner_len = 0;
    u32   gpio_tuner_len = 0;
    int   ret            = 0;
    void *nv_addr        = NULL;

    nv_len = sizeof(tuner->ctrl_info);
    ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_GPIO_CTRL_ID, (u8*)&tuner->ctrl_info, nv_len);
    if (ret) {
        cross_mipi_print_error("fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_GPIO_CTRL_ID);
        return ret;
    }

    gpio_tuner_len = tuner->ctrl_info.gpio_tuner_len;
    mipi_tuner_len = tuner->ctrl_info.mipi_tuner0_len \
                   + tuner->ctrl_info.mipi_tuner1_len \
                   + tuner->ctrl_info.mipi_tuner2_len;
    tuner->mipi_mem_len = mipi_tuner_len;

    tuner->mipi_mem = osl_cachedma_malloc(mipi_tuner_len * 4);
    tuner->gpio_mem = osl_cachedma_malloc(gpio_tuner_len * 4);

    if((NULL == tuner->mipi_mem) ||(NULL == tuner->gpio_mem )){
        cross_mipi_print_error("cross mipi malloc mem fail,size%d\n", mipi_tuner_len*4);
        if(tuner->gpio_mem)
            free(tuner->gpio_mem);

        if(tuner->mipi_mem)
            free(tuner->mipi_mem);
        return -1;
    }

    (void)memset_s(tuner->mipi_mem , mipi_tuner_len*4, 0, mipi_tuner_len*4);
    (void)memset_s(tuner->gpio_mem , gpio_tuner_len*4, 0, gpio_tuner_len*4);

    nv_len = tuner->ctrl_info.mipi_tuner0_len *4;
    ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_TUNER0_MEM_ID, (u8*)tuner->mipi_mem , nv_len);
    if (ret) {
        cross_mipi_print_error("fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_TUNER0_MEM_ID);
        return ret;
    }

    nv_len    = tuner->ctrl_info.mipi_tuner1_len *4;
    nv_addr = (void *)(tuner->mipi_mem + tuner->ctrl_info.mipi_tuner0_len);
    ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_TUNER1_MEM_ID, (u8 *)nv_addr, nv_len);
    if (ret) {
        cross_mipi_print_error("fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_TUNER1_MEM_ID);
        return ret;
    }

    nv_len    = tuner->ctrl_info.mipi_tuner2_len *4;
    nv_addr = (void *)(tuner->mipi_mem + tuner->ctrl_info.mipi_tuner0_len + tuner->ctrl_info.mipi_tuner1_len);
    ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_MIPI_TUNER2_MEM_ID, (u8 *)nv_addr, nv_len);
    if (ret) {
        cross_mipi_print_error("fail to read cross mipi nv, id: %d\n", NV_GU_RF_CROSS_MIPI_TUNER2_MEM_ID);
        return ret;
    }

    ret = (int)bsp_nvm_read(NV_GU_RF_CROSS_GPIO_TUNER_MEM_ID, (u8*)tuner->gpio_mem, gpio_tuner_len*4);
    if (ret) {
        cross_mipi_print_error("fail to read cross gpio nv, id: %d\n", NV_GU_RF_CROSS_GPIO_TUNER_MEM_ID);
        return ret;
    }

    return ret;
}

void bsp_cross_mipi_init(void)
{
    int   ret     = 0;
    static struct cross_mipi_info g_tuner = {0};

    if (!g_tuner.is_inited) {
        ret = cross_mipi_read_nv(&g_tuner);
        if (ret) {
            cross_mipi_print_error("read nv fail ,ret: %d\n", ret);
            return ;
        }
        g_tuner.ctu_base  = (u32)bsp_bbp_part_addr_get(BBP_CTU);
        g_tuner.mem_base  = (u32)bsp_bbp_part_addr_get(BBP_CROSS_MIPI_MEM);
        g_tuner.ctrl_base = (u32)bsp_bbp_part_addr_get(BBP_CROSS_MIPI_CTRL);

       // CROSS_MIPI_USE_BBP_DMA
        g_tuner.dma_mipi.bbp_addr = g_tuner.mem_base  + CROSS_MIPI_MIPI_MEM_OFFSET;
        g_tuner.dma_mipi.soc_addr = (u32)g_tuner.mipi_mem;
        g_tuner.dma_mipi.chan     = CROSS_MIPI_BBP_DMA_CHN;
        g_tuner.dma_mipi.size     = 4 * g_tuner.mipi_mem_len;
        g_tuner.dma_mipi.type     = 0;

        g_tuner.dma_gpio.bbp_addr = g_tuner.mem_base  + CROSS_MIPI_GPIO_MEM_OFFSET;
        g_tuner.dma_gpio.soc_addr = (u32)g_tuner.gpio_mem;
        g_tuner.dma_gpio.chan      = CROSS_GPIO_BBP_DMA_CHN;
        g_tuner.dma_gpio.size      = 4 * g_tuner.ctrl_info.gpio_tuner_len;
        g_tuner.dma_gpio.type      = 0;

        g_tuner_dpm_device.platform_data = &g_tuner;
        ret = bsp_device_pm_add(&g_tuner_dpm_device);
        if (ret) {
            cross_mipi_print_error("fail to add cross_mipi dpm device!\r\n");
            return;
        }
    }

    if (g_tuner.ctrl_info.tuner_en) {
        writel(g_tuner.ctrl_info.tuner_en,             (u32)g_tuner.ctrl_base + CROSS_MIPI_EN_OFFSET);
        writel(g_tuner.ctrl_info.tuner_req_en,         (u32)g_tuner.ctrl_base + CROSS_MIPI_REQ_EN_OFFSET);
        writel((u32)!g_tuner.ctrl_info.gpio_cross_en,  (u32)g_tuner.ctrl_base + CROSS_GPIO_EN_OFFSET);

        writel(~g_tuner.ctrl_info.reg.tuner_mipi_mask, (u32)g_tuner.ctu_base  + CROSS_MIPI_MASK_OFFSET);
        writel(~g_tuner.ctrl_info.reg.gpio_mask,       (u32)g_tuner.ctu_base  + CROSS_MIPI_GPIO_MASK_OFFSET);
        writel(g_tuner.ctrl_info.tas_ind_en,           (u32)g_tuner.ctu_base + TUNER_TAS_IND_OFFSET);

       // CROSS_MIPI_USE_BBP_DMA
        bsp_bbp_dma_tran(&g_tuner.dma_gpio);
        bsp_bbp_dma_tran(&g_tuner.dma_mipi);
        if (!g_tuner.is_inited){
            bsp_bbp_dma_finish(&g_tuner.dma_gpio);
            bsp_bbp_dma_finish(&g_tuner.dma_mipi);
        }
    }

    if (!g_tuner.is_inited) {
        g_tuner.is_inited = 1;
        cross_mipi_print_error("cross mipi init ok!g_tuner addr :0x%x\n", (u32)&g_tuner);
    }
}

#endif
