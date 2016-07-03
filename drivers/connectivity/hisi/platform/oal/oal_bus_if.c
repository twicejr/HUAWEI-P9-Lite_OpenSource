

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_bus_if.h"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 实际chip数量 */
OAL_STATIC oal_uint8         g_uc_bus_chip_num = 0;
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT))||(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151))
#ifdef _PRE_WLAN_FEATURE_DOUBLE_CHIP
OAL_STATIC oal_bus_chip_stru g_st_bus_chip[WLAN_CHIP_MAX_NUM_PER_BOARD] = {{0},{0}};
#else
OAL_STATIC oal_bus_chip_stru g_st_bus_chip[WLAN_CHIP_MAX_NUM_PER_BOARD] = {{0}};
#endif
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
OAL_STATIC oal_int8         *g_pac_irq_pc_name[4] = {"wlan1", "wlan2", "wlan3", "wlan4"};


/*****************************************************************************
  3 函数实现
*****************************************************************************/


oal_void  oal_bus_find_dev_instance(oal_bus_dev_stru **ppst_bus_dev, oal_void *p_dev)
{
    oal_uint8  uc_chip_index;
    oal_uint8  uc_device_index;

    for(uc_chip_index = 0; uc_chip_index < g_uc_bus_chip_num; uc_chip_index++)
    {
        for(uc_device_index = 0; uc_device_index < g_st_bus_chip[uc_chip_index].uc_device_num; uc_device_index++)
        {
            /* 两个地址相等 */
            if(g_st_bus_chip[uc_chip_index].st_bus_dev[uc_device_index].p_dev == p_dev)
            {
                *ppst_bus_dev = &g_st_bus_chip[uc_chip_index].st_bus_dev[uc_device_index];
                return;
            }
        }
    }

    *ppst_bus_dev = OAL_PTR_NULL;
}

OAL_STATIC oal_bus_dev_stru * oal_bus_get_dev_instance(oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_chip_stru          *pst_bus_chip;

    if(uc_chip_id >= WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        OAL_IO_PRINT("oal_bus_register_irq: uc_chip_id = %d\n", uc_chip_id);
        return OAL_PTR_NULL;
    }

    pst_bus_chip = &g_st_bus_chip[uc_chip_id];

    if(uc_device_id >= pst_bus_chip->uc_device_num)
    {
        OAL_IO_PRINT("oal_bus_register_irq: uc_device_id = %d\n", uc_device_id);
        return OAL_PTR_NULL;
    }

    return &pst_bus_chip->st_bus_dev[uc_device_id];
}

oal_void oal_bus_unregister_irq(oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_dev_stru           *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);
    if(OAL_PTR_NULL == pst_bus_dev)
    {
        return;
    }

    oal_irq_free(&pst_bus_dev->st_irq_info);
}

oal_uint32  oal_bus_register_irq(oal_void *pst, oal_irq_intr_func p_func, oal_uint8 uc_chip_id, oal_uint8 uc_device_id)
{
    oal_bus_dev_stru           *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);
    if(OAL_PTR_NULL == pst_bus_dev)
    {
        return OAL_FAIL;
    }

    OAL_IRQ_INIT_MAC_DEV(pst_bus_dev->st_irq_info,
                         pst_bus_dev->ul_irq_num,
                         OAL_SA_SHIRQ,
                         g_pac_irq_pc_name[uc_chip_id * WLAN_DEVICE_MAX_NUM_PER_CHIP + uc_device_id],
                         pst,
                         p_func);

    if (oal_irq_setup(&pst_bus_dev->st_irq_info))
    {
        return OAL_FAIL;
    }

    return OAL_SUCC;
}


oal_void  oal_bus_get_chip_instance(oal_bus_chip_stru **ppst_bus_chip, oal_uint8 uc_index)
{
    if(uc_index < WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        *ppst_bus_chip = &g_st_bus_chip[uc_index];
    }
    else
    {
        *ppst_bus_chip = OAL_PTR_NULL;
        OAL_IO_PRINT("oal_bus_get_chip_instance: uc_index = %d\n", uc_index);
    }
}


#endif


oal_uint8  oal_bus_get_chip_num(oal_void)
{
    return g_uc_bus_chip_num;
}


oal_uint32  oal_bus_inc_chip_num(oal_void)
{
    if(g_uc_bus_chip_num < WLAN_CHIP_MAX_NUM_PER_BOARD)
    {
        g_uc_bus_chip_num++;
    }
    else
    {
        OAL_IO_PRINT("oal_bus_inc_chip_num FAIL: g_uc_bus_chip_num = %d\n", g_uc_bus_chip_num);
        return OAL_FAIL;
    }

    /* WINDOWS下UT代码 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    g_st_bus_chip[0].uc_device_num = g_uc_bus_chip_num;
#endif

    return OAL_SUCC;
}

oal_void oal_bus_init_chip_num(oal_void)
{
    g_uc_bus_chip_num = 0;

    /* WINDOWS下UT代码 */
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
    g_st_bus_chip[0].uc_device_num = g_uc_bus_chip_num;
#endif
    return;
}


#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT

oal_void oal_bus_irq_affinity_init(oal_uint8 uc_chip_id, oal_uint8 uc_device_id, oal_uint32 ul_core_id)
{
	oal_bus_dev_stru *pst_bus_dev;

    pst_bus_dev = oal_bus_get_dev_instance(uc_chip_id, uc_device_id);

    oal_irq_set_affinity(pst_bus_dev->st_irq_info.ul_irq, ul_core_id);
}
#endif

/*lint -e19*/
oal_module_symbol(oal_bus_get_chip_num);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
oal_module_symbol(oal_bus_get_chip_instance);
oal_module_symbol(oal_bus_register_irq);
oal_module_symbol(oal_bus_unregister_irq);
#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(oal_bus_irq_affinity_init);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

