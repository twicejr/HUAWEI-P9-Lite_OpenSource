


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "dmac_resource.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RESOURCE_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
dmac_res_stru    g_st_dmac_res;

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
/*****************************************************************************
  3 函数实现
*****************************************************************************/



oal_uint32  dmac_res_alloc_mac_dev(oal_uint32    ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_res_alloc_dmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])++;

    return OAL_SUCC;
}


oal_uint32  dmac_res_free_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_free_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])--;

    if (0 != g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])
    {
        return OAL_SUCC;
    }

    /* 入队索引值需要加1操作 */
    oal_queue_enqueue(&(g_st_dmac_res.st_dmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_dev_idx + 1));

    return OAL_SUCC;
}


dmac_device_stru  *dmac_res_get_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_res_get_dmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_PTR_NULL;
    }

    return &(g_st_dmac_res.st_dmac_dev_res.ast_dmac_dev_info[ul_dev_idx]);
}


oal_uint32  dmac_res_init(oal_void)
{
    oal_uint32      ul_loop;

    OAL_MEMZERO(&g_st_dmac_res, OAL_SIZEOF(g_st_dmac_res));

    /***************************************************************************
            初始化DMAC DEV的资源管理内容
    ***************************************************************************/
    oal_queue_set(&(g_st_dmac_res.st_dmac_dev_res.st_queue),
                  g_st_dmac_res.st_dmac_dev_res.aul_idx,
                  MAC_RES_MAX_DEV_NUM);

    for (ul_loop = 0; ul_loop < MAC_RES_MAX_DEV_NUM; ul_loop++)
    {
        /* 初始值保存的是对应数组下标值加1 */
        oal_queue_enqueue(&(g_st_dmac_res.st_dmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_loop + 1));

        /* 初始化对应的引用计数值为0 */
        g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_loop] = 0;
    }

    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

