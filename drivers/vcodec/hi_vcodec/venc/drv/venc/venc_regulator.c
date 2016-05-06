
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>

#include "venc_regulator.h"
#include "hi_drv_mem.h"
#include <linux/hisi/hisi-iommu.h>
#include "drv_venc.h"
#include "drv_venc_efl.h"

#define REGULATOR_NAME          "ldo_venc"
#define MATCH_TABLE_TYPE        "hisi,kirin960-venc"
#define REGULATOR_DRIVER_NAME   "venc_regulator"

struct regulator *g_VencRegulator = NULL;
VeduEfl_DTS_CONFIG_S g_VencDtsConfig;

static int VENC_Enable_Iommu(struct platform_device *pdev)
{
	struct iommu_domain *hisi_domain      = NULL;
	struct iommu_domain_data* domain_data = NULL;
	struct device *dev    = NULL;
	uint64_t phy_pgd_base = 0;

	if (pdev == NULL)
	{
		HI_ERR_VENC("%s,  invalid Parameters!\n", __func__);
		return -1;
	}

	dev = &pdev->dev;

	/* create iommu domain */
	hisi_domain = iommu_domain_alloc(dev->bus);
	if (!hisi_domain) {
		HI_ERR_VENC("%s, iommu_domain_alloc failed!\n", __func__);
		return -EINVAL;
	}

	iommu_attach_device(hisi_domain, dev);
	g_hisi_mmu_domain = hisi_domain;

	domain_data = (struct iommu_domain_data *)(g_hisi_mmu_domain->priv);
    if(NULL != domain_data)
    {
        phy_pgd_base = (uint64_t)(domain_data->phy_pgd_base);
        HI_INFO_VENC("%s, phy_pgd_base:0x%x\n", __func__, phy_pgd_base);
    }

	return 0;
}

static int VENC_Disable_Iommu(struct platform_device *pdev)
{
    if((NULL != g_hisi_mmu_domain) && (NULL != pdev))
    {
        iommu_detach_device(g_hisi_mmu_domain, &pdev->dev);
        iommu_domain_free(g_hisi_mmu_domain);
        g_hisi_mmu_domain = NULL;
        return 0;
    }

    return -1;
}

static HI_S32 VENC_GetDtsConfigInfo(struct platform_device *pdev, VeduEfl_DTS_CONFIG_S *pDtsConfig)
{
    HI_S32 ret = HI_FAILURE;
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    struct resource res;
    struct iommu_domain_data *domain_data = NULL;
    if (HI_NULL == dev)
    {
        HI_ERR_VENC("%s, the deviceis null\n", __func__);
        return HI_FAILURE;
    }

    memset(&res, 0, sizeof(res));

    if (HI_NULL == np)
    {
        HI_ERR_VENC("%s, the device node is null\n", __func__);
        return HI_FAILURE;
    }

    if (HI_NULL == pDtsConfig)
    {
        HI_ERR_VENC("%s, pDtsConfig is null\n", __func__);
        return HI_FAILURE;
    }

    //Get irq num, return 0 if failed
    pDtsConfig->VeduIrqNum = irq_of_parse_and_map(np, 0);
    if (0 == pDtsConfig->VeduIrqNum)
    {
        HI_ERR_VENC("%s, irq_of_parse_and_map VeduIrqNum failed!\n", __func__);
        return HI_FAILURE;
    }

    pDtsConfig->MmuIrqNum = irq_of_parse_and_map(np, 1);
    if (0 == pDtsConfig->MmuIrqNum)
    {
        HI_ERR_VENC("%s, irq_of_parse_and_map MmuIrqNum failed!\n", __func__);
        return HI_FAILURE;
    }

    pDtsConfig->VedusecIrqNum  = irq_of_parse_and_map(np, 2);
    if (0 == pDtsConfig->VedusecIrqNum)
    {
        HI_ERR_VENC("%s, irq_of_parse_and_map VedusecIrqNum failed!\n", __func__);
        //return HI_FAILURE;
    }

    pDtsConfig->MmusecIrqNum = irq_of_parse_and_map(np, 3);
    if (0 == pDtsConfig->MmusecIrqNum)
    {
        HI_ERR_VENC("%s, irq_of_parse_and_map MmusecIrqNum failed!\n", __func__);
        //return HI_FAILURE;
    }

    //Get reg base addr & size, return 0 if success
    ret = of_address_to_resource(np, 0, &res);
    if (ret)
    {
        HI_ERR_VENC("%s of_address_to_resource failed! ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }
    pDtsConfig->VencRegBaseAddr = res.start;
    pDtsConfig->VencRegRange    = resource_size(&res);

    ret = of_property_read_u32(np, "venc_fpga", &pDtsConfig->IsFPGA);

    if (ret)
    {
        HI_INFO_VENC("%s, read failed!\n", __func__);
    }

    domain_data = (struct iommu_domain_data *)(g_hisi_mmu_domain->priv);
    if(NULL != domain_data)
    {
        pDtsConfig->SmmuPageBaseAddr = (uint64_t)(domain_data->phy_pgd_base);
        HI_INFO_VENC("%s, SmmuPageBaseAddr:0x%x\n", __func__, pDtsConfig->SmmuPageBaseAddr);
    }

    if (0 == pDtsConfig->SmmuPageBaseAddr)
    {
        HI_ERR_VENC("%s, Regulator_GetSmmuBasePhy failed!\n", __func__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Venc_Regulator_Config(struct platform_device *pdev)
{
    HI_S32 ret = HI_FAILURE;
    HI_INFO_VENC("enter %s!\n", __func__);

    g_VencRegulator = HI_NULL;
    g_VencRegulator = devm_regulator_get(&pdev->dev, REGULATOR_NAME);
    if (HI_NULL == g_VencRegulator)
    {
        HI_ERR_VENC("%s, get regulator failed!\n", __func__);
        return HI_FAILURE;
    }
    else if (IS_ERR(g_VencRegulator))
    {
        HI_ERR_VENC("%s, get regulator failed, error no = %ld!\n", __func__, PTR_ERR(g_VencRegulator));
        g_VencRegulator = HI_NULL;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 Venc_Regulator_Init(struct platform_device *pdev)
{
    HI_S32 ret = 0;

    if(NULL == pdev)
    {
        HI_ERR_VENC("%s, invalid argument!!\n", __func__);
        return HI_FAILURE;
    }

    ret = Venc_Regulator_Config(pdev);
	if (ret < 0)
    {
        HI_ERR_VENC("%s, Venc_Regulator_config failed!\n", __func__);
        return HI_FAILURE;
	}

    ret = VENC_Enable_Iommu(pdev);
    if(ret < 0)
    {
        HI_ERR_VENC("%s, VENC_Enable_Iommu failed!\n", __func__);
        return HI_FAILURE;
    }

    memset(&g_VencDtsConfig, 0, sizeof(VeduEfl_DTS_CONFIG_S));
    ret = VENC_GetDtsConfigInfo(pdev, &g_VencDtsConfig);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_VENC("%s VENC_GetDtsConfigInfo failed.\n", __func__);
        return HI_FAILURE;
    }

    ret = VENC_SetDtsConfig(&g_VencDtsConfig);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_VENC("%s VENC_SetDtsConfig failed.\n", __func__);
        return HI_FAILURE;
    }

#ifdef MODULE
    HI_ERR_VENC("Load hi_venc.ko ok!!.\t(%s)\n", VERSION_STRING);
#endif

    HI_INFO_VENC("exit %s()\n", __func__);
    return HI_SUCCESS;
}

HI_VOID Venc_Regulator_Deinit(struct platform_device *pdev)
{
    if(NULL != pdev)
    {
        VENC_Disable_Iommu(pdev);
    }

	return;
}

HI_S32 Venc_Regulator_Enable(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    if (HI_NULL == g_VencRegulator)
    {
        HI_ERR_VENC("%s, get regulator failed!\n", __func__);
        return HI_FAILURE;
    }
    else if (IS_ERR(g_VencRegulator))
    {
        HI_ERR_VENC("%s, get regulator failed, error no = %ld!\n", __func__, PTR_ERR(g_VencRegulator));
        g_VencRegulator = HI_NULL;
        return HI_FAILURE;
    }

    ret = regulator_enable(g_VencRegulator);
    if (ret != 0)
    {
        HI_ERR_VENC("%s, enable regulator failed!\n", __func__);
        return HI_FAILURE;
    }

    HI_INFO_VENC("%s, enable regulator success! \n", __func__);
    return HI_SUCCESS;
}

HI_S32 Venc_Regulator_Disable(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_INFO_VENC("%s, Venc_Regulator_Disable g_VencRegulator:0x%x\n", __func__, g_VencRegulator);
    ret = regulator_disable(g_VencRegulator);
    if (ret != 0)
    {
        HI_ERR_VENC("%s, disable regulator failed!\n", __func__);
        return HI_FAILURE;
    }

    HI_INFO_VENC("%s, disable regulator success!\n", __func__);

    return HI_SUCCESS;
}
