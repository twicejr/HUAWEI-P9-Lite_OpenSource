/*************************************************************************
*   版权所有(C) 2010-2015, 深圳华为技术有限公司.
*
*   文 件 名 :  dsp_balong.c
*
*   作    者 :  c00326366
*
*   描    述 :  本文件主要完成DSP镜像的加载及低功耗处理
*
*   修改记录 :  2015年5月7日  v1.00  c00326366  创建
*************************************************************************/
/*lint --e{537} */
#include <product_config.h>
#include "securec.h"
#include <osl_types.h>
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_wait.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>


#include <hi_base.h>
#include <hi_pwrctrl.h>
#include <hi_dsp.h>

#include <bsp_shared_ddr.h>

#include <bsp_om.h>
#include <bsp_edma.h>
#include <bsp_dpm.h>
#include <bsp_version.h>
#include <bsp_sysctrl.h>
#include <bsp_hardtimer.h>
#include <bsp_memrepair.h>
#include <bsp_pm_om.h>
#include <bsp_hw_spinlock.h>
#include <hi_pwrctrl_interface.h>
#include <mdrv_pm.h>

#include <of.h>

#include "dsp_balong.h"
#include <bsp_dspload.h>
#include <bsp_nvim_mem.h>

#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_nvim.h"
#include "bsp_hwadp.h"
#include <bsp_reset.h>
#include <socp_balong.h>

#ifdef CONFIG_CBBE

enum dsp_store_state_en{
    DSP_STORE_IDLE = 0,
    DSP_STORE_NEED,
    DSP_STORE_DOING,
    DSP_STORE_HAD,
    DSP_RESTORE_DOING
};


struct dsp_ctrl_state
{
    spinlock_t spin_lock;
    u32 restore_edma_channel_id;
    u32 store_edma_channel_id;
    u32 dsp_power_on_count;
    u32 dsp_unreset_count;
    u32 dsp_clock_enable_count;
    u32 dsp_suspend_count;
    u32 dsp_resume_count;
    u32 dsp_sem_up_count;
    u32 dsp_sem_down_count;
    u32 dsp_run_count;
    u32 dsp_stop_count;
    u32 dsp_restore_count;
    u32 dsp_restore_succ_count;
    u32 dsp_store_count;
    u32 dsp_store_succ_count;

    u32 is_bsp_bbe_load_called :1; /*1:协议栈调用了bsp_bbe_load接口 0:协议栈没有调用bsp_bbe_load接口*/
    u32 is_dsp_power_on     :1;  /* 1 for power on */
    u32 is_dsp_clock_enable :1;  /* 1 for clock enable */
    u32 is_dsp_unreset      :1;  /* 1 for unreset */
    u32 is_bbe_power_on     :1;  /* 1 for power on */
    u32 is_bbe_clock_enable :1;  /* 1 for clock enable */
    u32 is_bbe_unreset      :1;  /* 1 for unreset */
    u32 is_dsp_running      :1;
    u32 is_dsp_deep_sleep   :1;
    u32 is_dsp_store_state  :3;  /* 0-idle; 1-need store; 2-storing; 3-has store; 4-restoring */
};

struct dsp_sectinfo{
    u32                         imageaddr;      /* 镜像在DDR中的首地址 */
    u32                         ba_tcmnum;      /* 需要备份的DTCM段个数 */
    u32                         re_tcmnum;      /* 需要恢复的DTCM/ITCM段个数 */
    struct list_head            oncehead;       /* 只需要加载1次的段的链表头 */
    struct list_head            secthead;       /* 每次都需要加载的段的链表头 */
    struct edma_cb             *pba_edmacb;     /* 备份TCM的EDMA链表首地址 */
    struct edma_cb             *pre_edmacb;     /* 恢复TCM的EDMA链表首地址 */
};

struct dsp_cbbe_pm_om_qos_log {
    unsigned int load_start;
    unsigned int load_end;
    unsigned int msp_store;
    unsigned int dpm_store;
    unsigned int dsp_store;
    unsigned int dsp_store_end;
    unsigned int poweroff;
    unsigned int poweron;
    unsigned int dpm_wait_store_ok;
    unsigned int dpm_restore;
    unsigned int dsp_restore;
    unsigned int msp_restore;
    unsigned int msp_restore_ok;
};

struct dsp_mainctrl{
    struct dsp_ctrl             tcm_info;
    struct dsp_sysctrl          reg_sysctrl[DSP_DTS_REG_BUTT];
    struct dsp_pwc_ctrl         pwc_ctrl;
    struct dsp_ctrl_state       ctrl_state;
    struct dsp_cbbe_pm_om_qos_log    dsp_timedump;
    struct dsp_cbbe_pm_om_qos_log   *dsp_timedump_addr;
    struct dsp_sectinfo         sect_info;
};


struct dsp_sect_node{
    struct dsp_sect_desc_stru   sectinfo;
    struct list_head            sectlist;
};


struct dsp_mainctrl g_dsp_ctrl[BSP_DSP_BUTT];

struct cdsp_drx_debug{
    u32 drx_cbbe16_pd;
    u32 drx_cbbe16_pll;
};

struct cdsp_drx_debug g_cdsp_drx = {0};

static inline void dsp_get_reg(unsigned int *value, struct dsp_sysctrl *pstreg)
{
    unsigned int mask = 0;
    unsigned int temp = 0;
    unsigned int reg    = pstreg->base_addr + pstreg->offset;

    temp   = readl(reg);
    mask   = ((1U << (pstreg->end_bit - pstreg->start_bit + 1)) -1) << pstreg->start_bit;
    *value = temp & mask;
    *value = (*value) >> pstreg->start_bit;
}

static inline void dsp_set_reg(unsigned int value, struct dsp_sysctrl *pstreg)
{
    unsigned int reg    = pstreg->base_addr + pstreg->offset;
    unsigned int temp   = 0;
    unsigned int mask   = 0;

    temp   = readl(reg);
    mask   = ((1U << (pstreg->end_bit - pstreg->start_bit + 1)) -1) << pstreg->start_bit;
    value  = (temp & (~mask)) | ((value <<pstreg->start_bit) & mask);
    writel(value  ,reg);
}

#if 0   /* 测试用代码 */

u32 dsp_load_get_reg(u32 base_addr, u32 offset, u32 start_bit, u32 end_bit)
{
    struct dsp_sysctrl streg;
    u32 value;

    streg.base_addr = base_addr;
    streg.offset    = offset;
    streg.start_bit = start_bit;
    streg.end_bit   = end_bit;

    dsp_get_reg(&value, &streg);

    return value;
}


u32 dsp_load_set_reg(u32 value, u32 base_addr, u32 offset, u32 start_bit, u32 end_bit)
{
    struct dsp_sysctrl streg;

    streg.base_addr = base_addr;
    streg.offset    = offset;
    streg.start_bit = start_bit;
    streg.end_bit   = end_bit;

    dsp_set_reg(value, &streg);

    return value;
}
#endif

#ifdef DSP_LOAD_WITH_EDMA
/*lint -save -e525*/
int dsp_edma_lli_start(enum bsp_dsp_type_e etype, struct edma_cb *pedmacb)
{
    s32                   edmaid      = 0;
    struct edma_cb       *pedmahead   = NULL;

    /* 申请通道，注册通道中断回调函数 */
    edmaid = bsp_edma_channel_init(EDMA_PWC_CDSP_TCM, NULL, 0, 0);
	if (edmaid < 0)
    {
        cdsp_print("bsp_edma_channel_init EDMA_PWC_CDSP_TCM failed %d. \n", edmaid);
        return 1;
    }

    g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id = (u32)edmaid;

    /* 获取edma 链表首节点地址 */
    pedmahead = bsp_edma_channel_get_lli_addr((u32)edmaid);
    if (NULL == pedmahead)
    {
        cdsp_print("bsp_edma_channel_get_lli_addr EDMA_PWC_CDSP_TCM failed. \n");
        bsp_edma_channel_free((u32)edmaid);
        return 1;
    }

    /* 配置首节点寄存器，寄存器操作不使用memcpy */
    pedmahead->lli      = pedmacb->lli;
    pedmahead->config   = pedmacb->config & 0xFFFFFFFE;
    pedmahead->src_addr = pedmacb->src_addr;
    pedmahead->des_addr = pedmacb->des_addr;
    pedmahead->cnt0     = pedmacb->cnt0;
    pedmahead->bindx    = pedmacb->bindx;
    pedmahead->cindx    = pedmacb->cindx;
    pedmahead->cnt1     = pedmacb->cnt1;

    /* 启动EDMA传输后即返回 */
    if (bsp_edma_channel_lli_async_start((u32)edmaid))
    {
        cdsp_print("bsp_edma_channel_lli_async_start EDMA_PWC_CDSP_TCM failed!\n");
        bsp_edma_channel_free((u32)edmaid);

        return 1;
    }

    return 0;
}
/*lint -restore*/

/*lint -save -e506*/
/*****************************************************************************
* 函 数 名  : dsp_store_edma_lli_init
*
* 功能描述  : 设置TCM备份时的EDMA链表
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 只在开机加载时配置一次，链表空间不释放
*
*****************************************************************************/
int dsp_store_edma_lli_init(enum bsp_dsp_type_e etype)
{
    u32 i = 0;
    u32 bcount = 0, acount = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct edma_cb       *pedmacb     = NULL;
    struct dsp_bin_header_stru *pheader;

    if(0 == g_dsp_ctrl[etype].sect_info.ba_tcmnum)
    {
        return 1;
    }

    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].sect_info.imageaddr;

    /* 多申请32个字节，保证地址对齐 */
    pedmacb = (struct edma_cb *)osl_cachedma_malloc((g_dsp_ctrl[etype].sect_info.ba_tcmnum * sizeof(struct edma_cb)) + 32);

    if (NULL == pedmacb)
    {
        cdsp_print("osl_cachedma_malloc failed. \n");
        return 1;
    }

    pedmacb = (struct edma_cb *)(((u32)pedmacb+0x1f) & 0xFFFFFFE0);
    g_dsp_ctrl[etype].sect_info.pba_edmacb = pedmacb;

    /* TODO: 考虑是否需要信号量保护 */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        /* 只需要备份DTCM */
        if(1 != psect->sectinfo.ucTcmType)
        {
            continue;
        }

        i++;

        /* TODO : 应触发复位 */
        if(i > g_dsp_ctrl[etype].sect_info.ba_tcmnum)
        {
            cdsp_print("backup tcm number error i %d, ba_tcmnum %d. \n"
                ,i, g_dsp_ctrl[etype].sect_info.ba_tcmnum);
            return 1;
        }

        /* 避免拷贝越界，应触发重启 TODO */
        if((pheader->ulFileSize - psect->sectinfo.ulFileOffset) < psect->sectinfo.ulSectSize)
        {
            cdsp_print( "ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x. \n",
                pheader->ulFileSize, psect->sectinfo.ulFileOffset, psect->sectinfo.ulSectSize);
            continue;
        }

        if(psect->sectinfo.ulSectSize >= BBE_SECT_LEN_64K)
        {
            acount = psect->sectinfo.ulSectSize & 0x3ff;
            bcount = psect->sectinfo.ulSectSize >> 10;

            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->cnt0       = ((bcount - 1)<<16) | BBE_SECT_LEN_1K;
            pedmacb->bindx      = (BBE_SECT_LEN_1K<<16) |BBE_SECT_LEN_1K;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;

            pedmacb++;

            if(acount)
            {
                i++;

                pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
                pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
                pedmacb->src_addr   = psect->sectinfo.ulTargetAddr + (bcount * BBE_SECT_LEN_1K);
                pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr \
                                    + psect->sectinfo.ulFileOffset \
                                    + (bcount * BBE_SECT_LEN_1K));
                pedmacb->cnt0       = acount;
                pedmacb->bindx      = 0;
                pedmacb->cindx      = 0;
                pedmacb->cnt1       = 0;

                pedmacb++;
            }
        }
        else
        {
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pba_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.ba_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->des_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->cnt0       = psect->sectinfo.ulSectSize;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;

            pedmacb++;
        }
    }

    return 0;
}

/*****************************************************************************
* 函 数 名  : dsp_restore_edma_lli_init
*
* 功能描述  : 设置TCM恢复时的EDMA链表
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 只在开机加载时配置一次，链表空间不释放
*
*****************************************************************************/
int dsp_restore_edma_lli_init(enum bsp_dsp_type_e etype)
{
    u32 i = 0;
    u32 bcount = 0, acount = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct edma_cb       *pedmacb = NULL;

    if(0 == g_dsp_ctrl[etype].sect_info.re_tcmnum)
    {
        return 1;
    }

    /* 多申请32个字节，保证地址对齐 */
    pedmacb = (struct edma_cb *)osl_cachedma_malloc((g_dsp_ctrl[etype].sect_info.re_tcmnum * sizeof(struct edma_cb)) + 32);

    if (NULL == pedmacb)
    {
        cdsp_print("osl_cachedma_malloc failed. \n");
        return 1;
    }

    pedmacb = (struct edma_cb *)(((u32)pedmacb+0x1f) & 0xFFFFFFE0);
    g_dsp_ctrl[etype].sect_info.pre_edmacb = pedmacb;

    /* TODO: 考虑是否需要信号量保护 */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        i++;

        /* TODO : 应触发复位 */
        if(i > g_dsp_ctrl[etype].sect_info.re_tcmnum)
        {
            cdsp_print("backup tcm number error i %d, re_tcmnum %d. \n"
                ,i, g_dsp_ctrl[etype].sect_info.re_tcmnum);
            return 1;
        }

        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        if(psect->sectinfo.ulSectSize >= BBE_SECT_LEN_64K)
        {
            acount = psect->sectinfo.ulSectSize & 0x3ff;
            bcount = psect->sectinfo.ulSectSize >> 10;

            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->des_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->cnt0       = ((bcount - 1)<<16) | BBE_SECT_LEN_1K;
            pedmacb->bindx      = (BBE_SECT_LEN_1K<<16) |BBE_SECT_LEN_1K;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;

            pedmacb++;

            if(acount)
            {

                i++;

                pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
                pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
                pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr \
                                  + psect->sectinfo.ulFileOffset \
                                  + (bcount * BBE_SECT_LEN_1K));
                pedmacb->des_addr   = psect->sectinfo.ulTargetAddr + (bcount * BBE_SECT_LEN_1K);
                pedmacb->cnt0       = acount;
                pedmacb->bindx      = 0;
                pedmacb->cindx      = 0;
                pedmacb->cnt1       = 0;

                pedmacb++;
            }
        }
        else
        {
            pedmacb->lli        = EDMA_SET_LLI((g_dsp_ctrl[etype].sect_info.pre_edmacb + i), \
                                                ((i < g_dsp_ctrl[etype].sect_info.re_tcmnum)?0:1));
            pedmacb->config     = EDMA_SET_CONFIG(EDMA_PWC_CDSP_TCM, EDMA_M2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
            pedmacb->src_addr   = (g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset);
            pedmacb->des_addr   = psect->sectinfo.ulTargetAddr;
            pedmacb->cnt0       = psect->sectinfo.ulSectSize;
            pedmacb->bindx      = 0;
            pedmacb->cindx      = 0;
            pedmacb->cnt1       = 0;

            pedmacb++;
        }
    }

    return 0;
}
/*lint -restore*/

int dsp_edma_lli_store(enum bsp_dsp_type_e etype)
{
    /* 如果恢复链表中没有需要加载的段 */
    if(NULL == g_dsp_ctrl[etype].sect_info.pba_edmacb)
    {
        cdsp_print("dsp_edma_lli_store no backup section. \n");
        return 1;
    }

    return dsp_edma_lli_start(etype, g_dsp_ctrl[etype].sect_info.pba_edmacb);
}


int dsp_edma_lli_restore(enum bsp_dsp_type_e etype)
{
    /* 如果备份链表中没有需要加载的段 */
    if(NULL == g_dsp_ctrl[etype].sect_info.pre_edmacb)
    {
        cdsp_print("dsp_edma_lli_restore no restore section. \n");
        return 1;
    }

    return dsp_edma_lli_start(etype, g_dsp_ctrl[etype].sect_info.pre_edmacb);
}

#endif

/*****************************************************************************
* 函 数 名  : bsp_bbe_load
*
* 功能描述  : DSP镜像加载到TCM(用于协议栈开机时调用)
*
* 返 回 值  : 0，成功；1，失败
*
*****************************************************************************/
int bsp_bbe_load(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    g_dsp_ctrl[etype].ctrl_state.is_bsp_bbe_load_called = 1;
    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret  = bsp_bbe_power_on_ex(etype);
        ret |= bsp_dsp_clk_enable(etype);
        ret |= bsp_dsp_unreset_ex(etype);
    }

    ret |= bsp_bbe_clk_enable(etype);
    ret |= bsp_bbe_unreset_ex(etype);

    if (ret)
    {
        cdsp_print("fail to setup bbe16\r\n");
        return -1;
    }

    /* 开机时向tcm中拷数据之前做打点 */

    /* 解析出需要加载的段信息 */
    ret = dsp_parse_image_header(etype);

    dsp_load_once_sect(etype);

#ifdef DSP_LOAD_WITH_EDMA
    /* 根据段信息申请EDMA链表空间 */
    dsp_store_edma_lli_init(etype);
    dsp_restore_edma_lli_init(etype);
#endif

    ret |= bsp_bbe_restore_ex(etype);

    ret |= bsp_bbe_wait_restore_over(etype);

    /* 开机时向tcm中拷数据之后做打点 */

    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 0;

    return ret;
}

/*****************************************************************************
* 函 数 名  : dsp_parse_image_header
*
* 功能描述  : 解析镜像头(把需要底软加载的段信息加入链表)
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 只需要加载一次的段和每次都需要加载的段分开存储
*               1.方便只需要加载一次的段加载后删除
*               2.方便根据每次都需要加载的段的个数来申请EDMA链表空间
*
*****************************************************************************/
int dsp_parse_image_header(enum bsp_dsp_type_e etype)
{
    u32 i,num;
    struct dsp_bin_header_stru *pheader;
    struct dsp_sect_desc_stru *psect;
    struct dsp_sect_node *pstsectnode;

    INIT_LIST_HEAD(&g_dsp_ctrl[etype].sect_info.secthead);
    INIT_LIST_HEAD(&g_dsp_ctrl[etype].sect_info.oncehead);

    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr;

    if(NULL == pheader)
    {
        cdsp_print("dsp_parse_image_header failed :pheader 0x%p.\n", pheader);
        return 1;
    }

    g_dsp_ctrl[etype].sect_info.imageaddr = (u32)pheader;
    g_dsp_ctrl[etype].sect_info.ba_tcmnum = 0;
    g_dsp_ctrl[etype].sect_info.re_tcmnum = 0;

    for(i = 0; i < pheader->ulSectNum; i++)
    {
        psect = &pheader->astSect[i];

        /* 镜像中可能有size为0的段 */
        if(0 == psect->ulSectSize)
        {
            continue;
        }

        if(0 == psect->ucLoadType)  /* 每次低功耗上电都需要加载，由EDMA搬移 */
        {
            /* 由于EDMA节点的长度限制，长度大于等于64K时需要拆分成两段搬移 */
            num = (psect->ulSectSize >= BBE_SECT_LEN_64K) ? 2 : 1;

            g_dsp_ctrl[etype].sect_info.re_tcmnum += num;

            if(1 == psect->ucTcmType)
            {
                g_dsp_ctrl[etype].sect_info.ba_tcmnum += num;
                if((psect->ulFileOffset > pheader->ulFileSize)
                || ((psect->ulFileOffset + psect->ulSectSize) > pheader->ulFileSize)
                || (psect->ulTargetAddr < CPHY_PUB_DTCM_BASE)
                || (psect->ulTargetAddr > (CPHY_PUB_DTCM_BASE+CPHY_PUB_DTCM_SIZE))
                )
                {
                    cdsp_print("dsp_parse_image_header fail : ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x, ulTargetAddr 0x%x.\n",
                    pheader->ulFileSize, psect->ulFileOffset, psect->ulSectSize, psect->ulTargetAddr);
                    return 1;
                }
            }
            else
            {
                if((psect->ulFileOffset > pheader->ulFileSize)
                || ((psect->ulFileOffset + psect->ulSectSize) > pheader->ulFileSize)
                || (psect->ulTargetAddr < CPHY_PUB_ITCM_BASE)
                || (psect->ulTargetAddr > (CPHY_PUB_ITCM_BASE+CPHY_PUB_ITCM_SIZE))
                )
                {
                    cdsp_print("dsp_parse_image_header fail : ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x, ulTargetAddr 0x%x.\n",
                    pheader->ulFileSize, psect->ulFileOffset, psect->ulSectSize, psect->ulTargetAddr);
                    return 1;
                }
            }
            pstsectnode = osl_malloc(sizeof(struct dsp_sect_node));
            if(NULL == pstsectnode)
            {
                return 1;
            }

            memcpy_s((void*)&pstsectnode->sectinfo, sizeof(struct dsp_sect_desc_stru),
                   (void*)psect, sizeof(struct dsp_sect_desc_stru));
            /*由于bbe16和ARM看到的DTCM基址不一致，需要做偏移*/
            pstsectnode->sectinfo.ulTargetAddr = pstsectnode->sectinfo.ulTargetAddr - CPHY_PUB_DTCM_BASE + (u32)g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr;

            list_add(&pstsectnode->sectlist, &g_dsp_ctrl[etype].sect_info.secthead);
        }
        else if(1 == psect->ucLoadType)  /* 只在开机时加载，采用MEMCPY */
        {
            if(1 == psect->ucTcmType)
            {
                if((psect->ulFileOffset > pheader->ulFileSize)
                || ((psect->ulFileOffset + psect->ulSectSize) > pheader->ulFileSize)
                || (psect->ulTargetAddr < CPHY_PUB_DTCM_BASE)
                || (psect->ulTargetAddr > (CPHY_PUB_DTCM_BASE+CPHY_PUB_DTCM_SIZE))
                )
                {
                    cdsp_print("dsp_parse_image_header fail : ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x, ulTargetAddr 0x%x.\n",
                    pheader->ulFileSize, psect->ulFileOffset, psect->ulSectSize, psect->ulTargetAddr);
                    return 1;
                }
            }
            else
            {
                if((psect->ulFileOffset > pheader->ulFileSize)
                || ((psect->ulFileOffset + psect->ulSectSize) > pheader->ulFileSize)
                || (psect->ulTargetAddr < CPHY_PUB_ITCM_BASE)
                || (psect->ulTargetAddr > (CPHY_PUB_ITCM_BASE+CPHY_PUB_ITCM_SIZE))
                )
                {
                    cdsp_print("dsp_parse_image_header fail : ulFileSize 0x%x, ulFileOffset 0x%x, ulSectSize 0x%x, ulTargetAddr 0x%x.\n",
                    pheader->ulFileSize, psect->ulFileOffset, psect->ulSectSize, psect->ulTargetAddr);
                    return 1;
                }
            }
            pstsectnode = osl_malloc(sizeof(struct dsp_sect_node));
            if(NULL == pstsectnode)
            {
                return 1;
            }

            memcpy_s((void*)&pstsectnode->sectinfo, sizeof(struct dsp_sect_desc_stru),
                   (void*)psect, sizeof(struct dsp_sect_desc_stru));
            /*由于bbe16和ARM看到的DTCM基址不一致，需要做偏移*/
            pstsectnode->sectinfo.ulTargetAddr = pstsectnode->sectinfo.ulTargetAddr - CPHY_PUB_DTCM_BASE + (u32)g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr;

            list_add(&pstsectnode->sectlist, &g_dsp_ctrl[etype].sect_info.oncehead);
        }
        else
        {
            /* do nothing */
        }
    }

    return 0;
}


/*****************************************************************************
* 函 数 名  : dsp_load_once_sect
*
* 功能描述  : 加载只需要加载一次的段
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
void dsp_load_once_sect(enum bsp_dsp_type_e etype)
{
    struct list_head *p, *n;
    struct dsp_sect_node *psect;

    /* TODO: 考虑是否需要信号量保护 */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.oncehead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        cdsp_print("dsp_load_once_sect src 0x%x: , dst : 0x%x. \n",
            (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), (void*)psect->sectinfo.ulTargetAddr);

        memcpy_s((void*)psect->sectinfo.ulTargetAddr, psect->sectinfo.ulSectSize,
               (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), psect->sectinfo.ulSectSize);

        /* ucLoadType = 0的段只需要加载一次 */
        list_del(&psect->sectlist);
        osl_free(psect);
    }

    return ;
}

/*****************************************************************************
* 函 数 名  : bsp_bbe_store_ex
*
* 功能描述  : 完成指定BBE16的DTCM的备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 用于低功耗场景、对外接口场景
*
*****************************************************************************/
int bsp_bbe_store_ex(enum bsp_dsp_type_e etype)
{
    g_dsp_ctrl[etype].ctrl_state.dsp_store_count++;
#ifdef DSP_LOAD_WITH_EDMA

    return dsp_edma_lli_store(etype);

#else
    int ret = 0;
    struct list_head *p, *n;
    struct dsp_sect_node *psect;
    struct dsp_bin_header_stru *pheader;

    pheader = (struct dsp_bin_header_stru *)g_dsp_ctrl[etype].sect_info.imageaddr;

    /* TODO: 考虑是否需要信号量保护 */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        /* 备份DTCM */
        if(1 == psect->sectinfo.ucTcmType)
        {
            memcpy_s((void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset),
                    (pheader->ulFileSize - psect->sectinfo.ulFileOffset),
                   (void*)psect->sectinfo.ulTargetAddr, psect->sectinfo.ulSectSize);
        }
    }

    return ret;
#endif
}

/*lint -save -e774 -e525*/
/*****************************************************************************
* 函 数 名  : bsp_bbe_store_dtcm_ex
*
* 功能描述  : 完成BBE16的DTCM的备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 用于dump保存场景
*
*****************************************************************************/
int bsp_bbe_store_dtcm_ex(enum bsp_dsp_type_e etype)
{
    s32 ret = 0;
#ifdef DSP_LOAD_WITH_EDMA
    s32 edmaid = 0;
    u32 size_align = 0;
    /* coverity[assignment] */
    u32 len = CPHY_PUB_DTCM_SIZE;
    /* coverity[const] */ /* coverity[dead_error_condition] */
    if((len & 0x1fff) == 0)
    {
        size_align = SZ_8K;
    }
    /* coverity[dead_error_line] */
    else if((len & 0xfff) == 0)
    {
        size_align = SZ_4K;
    }
    else
    {
        size_align = SZ_1K;
    }

    /* 申请通道，注册通道中断回调函数 */
    edmaid = bsp_edma_channel_init(EDMA_PWC_CDSP_TCM, NULL, 0, 0);
	if (edmaid < 0)
    {
        cdsp_print("bsp_edma_channel_init EDMA_PWC_CDSP_TCM failed %d. \n", edmaid);
        return (-1);
    }

    g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id = (u32)edmaid;

    ret = bsp_edma_channel_set_config(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id, EDMA_M2M,EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
    if(ret)
    {
        cdsp_print("bsp_edma_channel_set_config store_edma_channel_id dtcm failed.\n");
        return (-1);
    }

    ret = bsp_edma_channel_2vec_start(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id,
        (u32)g_dsp_ctrl[etype].tcm_info.tcm_dtcm_base_addr,
        (u32)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr,
        CPHY_PUB_DTCM_SIZE, size_align);

#else
    memcpy_s((void*)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr,
            CPHY_PUB_DTCM_SIZE,
           (void *)g_dsp_ctrl[etype].tcm_info.tcm_dtcm_base_addr,
           CPHY_PUB_DTCM_SIZE);

#endif

    return ret;
}

/*****************************************************************************
* 函 数 名  : bsp_bbe_store_itcm_ex
*
* 功能描述  : 完成BBE16的ITCM的备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  : 用于dump保存场景
*
*****************************************************************************/
int bsp_bbe_store_itcm_ex(enum bsp_dsp_type_e etype)
{
    s32 ret = 0;
#ifdef DSP_LOAD_WITH_EDMA
    s32 edmaid = 0;
    u32 size_align = 0;
    /* coverity[assignment] */
    u32 len = CPHY_PUB_ITCM_SIZE;
    /* coverity[const] */ /* coverity[dead_error_condition] */
    if((len & 0x1fff) == 0)
    {
        size_align = SZ_8K;
    }
    /* coverity[dead_error_line] */
    else if((len & 0xfff) == 0)
    {
        size_align = SZ_4K;
    }
    else
    {
        size_align = SZ_1K;
    }

    /* 申请通道，注册通道中断回调函数 */
    edmaid = bsp_edma_channel_init(EDMA_PWC_CDSP_TCM, NULL, 0, 0);
	if (edmaid < 0)
    {
        cdsp_print("bsp_edma_channel_init EDMA_PWC_CDSP_TCM failed %d. \n", edmaid);
        return (-1);
    }

    g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id = (u32)edmaid;

    ret = bsp_edma_channel_set_config(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id, EDMA_M2M,EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
    if(ret)
    {
        cdsp_print("bsp_edma_channel_set_config store_edma_channel_id itcm failed. \n");
        return (-1);
    }

    ret = bsp_edma_channel_2vec_start(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id,
        (u32)g_dsp_ctrl[etype].tcm_info.tcm_itcm_base_addr,
        (u32)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr + CPHY_PUB_DTCM_SIZE,
        CPHY_PUB_ITCM_SIZE, size_align);

#else
    memcpy_s((void*)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_itcm_addr,
            CPHY_PUB_ITCM_SIZE,
           (void *)g_dsp_ctrl[etype].tcm_info.tcm_itcm_base_addr,
           CPHY_PUB_ITCM_SIZE);

#endif

    return ret;
}
/*lint -restore*/


/*****************************************************************************
* 函 数 名  : bsp_bbe_restore_ex
*
* 功能描述  : 恢复TCM(根据链表中的段信息从DDR恢复到TCM中，并填充TCM头)
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_bbe_restore_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    g_dsp_ctrl[etype].ctrl_state.dsp_restore_count++;
#ifdef DSP_LOAD_WITH_EDMA
    ret = dsp_edma_lli_restore(etype);
    if(ret)
    {
        return ret;
    }
#else
    struct list_head *p, *n;
    struct dsp_sect_node *psect;

    /* TODO: 考虑是否需要信号量保护 */
    list_for_each_safe(p, n, &g_dsp_ctrl[etype].sect_info.secthead)
    {
        psect = list_entry(p, struct dsp_sect_node ,sectlist);

        if(0 == psect->sectinfo.ucLoadType)
        {
            memcpy_s((void*)psect->sectinfo.ulTargetAddr, psect->sectinfo.ulSectSize,
                   (void*)(g_dsp_ctrl[etype].sect_info.imageaddr + psect->sectinfo.ulFileOffset), psect->sectinfo.ulSectSize);
        }
    }
#endif

    return ret;
}

int dsp_wait_edma_over(enum bsp_dsp_type_e etype)
{
    int ret = 0;

#ifdef DSP_LOAD_WITH_EDMA

    while(!bsp_edma_channel_is_idle(g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id)) ;

    ret = bsp_edma_channel_free(g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id);
    g_dsp_ctrl[etype].ctrl_state.restore_edma_channel_id = 0;
    if (ret)
    {
        cdsp_print("fail to free edma channel\r\n");
    }
#endif

    return ret;
}

int bsp_bbe_wait_store_over(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    ret = dsp_wait_edma_over(etype);
    if(ret)
    {
        return ret;
    }
    g_dsp_ctrl[etype].ctrl_state.dsp_store_succ_count++;

    return ret;
}

int bsp_bbe_wait_restore_over(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    ret = dsp_wait_edma_over(etype);
    if(ret)
    {
        return ret;
    }
    g_dsp_ctrl[etype].ctrl_state.dsp_restore_succ_count++;

    return ret;
}

int bsp_bbe_wait_store_tcm_over(enum bsp_dsp_type_e etype)
{
    int ret = 0;
#ifdef DSP_LOAD_WITH_EDMA
    while(!bsp_edma_channel_is_idle(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id)) ;

    ret = bsp_edma_channel_free(g_dsp_ctrl[etype].ctrl_state.store_edma_channel_id);
#endif

    return ret;
}

/*****************************************************************************
* 函 数 名  : bsp_bbe_power_on_ex
*
* 功能描述  : 给BBE上电，内部调用接口
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_bbe_power_on_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;
    int ret = 0;
    unsigned int  tmp;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_EN]);
    }

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_RDY_STAT].base_addr))
    {
        do
        {
            dsp_get_reg(&tmp, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_RDY_STAT]);
        }
        while(!tmp);
    }

    udelay(30);
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_DIS]);
    }

    /* TODO: memrepair*/

    g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on = 1;
    g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return ret;
}

/*****************************************************************************
* 函 数 名  : bsp_bbe_power_off_ex
*
* 功能描述  : 给BBE下电，内部调用接口
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_bbe_power_off_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_ISO_CTRL_EN]);
    }

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_MTCMOS_CTRL_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on = 0;
    g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}


/*****************************************************************************
* 函 数 名  : bsp_bbe_power_up_ex
*
* 功能描述  : 给BBE上电，外部调用接口
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_bbe_power_up_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
       ret =  bsp_bbe_power_on_ex(etype);
       ret |= bsp_dsp_clk_enable(etype);
       ret |= bsp_dsp_unreset_ex(etype);
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_bbe_power_up_ex
*
* 功能描述  : 给BBE下电，外部调用接口
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_bbe_power_down_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if(1 == g_cdsp_drx.drx_cbbe16_pd)
    {
        return ret;
    }
    else
    {
        if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
        {
           ret  = bsp_dsp_reset_ex(etype);
           ret |= bsp_dsp_clk_disable(etype);
           ret |= bsp_bbe_power_off_ex(etype);
        }

        return ret;
    }
}


int bsp_bbe_run_ex(enum bsp_dsp_type_e etype)
{
    /* 让bbe开始工作 */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_running = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_stop_ex(enum bsp_dsp_type_e etype)
{
    /* 让bbe停止工作 */
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);


    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_RUNSTALL]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_running = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_clk_enable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* enable clock */

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_CORE_CLK_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_CORE_CLK_EN]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_clk_disable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* disable clock */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_CORE_CLK_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_CORE_CLK_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_unreset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* unreset BBE16 */

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_bbe_reset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* reset BBE16 */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_SRST_EN]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clk_enable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* enable clock */

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_EN]);
    }
    //sc_dsp_clock_enable(1);

    g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_clk_disable(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* disable clock */

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_CLK_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_status_ex(enum bsp_dsp_type_e etype)
{
    unsigned int data = 0;

    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //K3、V7R5
        dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);
    }

    return (int)data;
}

int bsp_dsp_pll_enable_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;
    unsigned int data;
    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* open dsp pll */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //K3、V7R5
        dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);

        if(!data)
        {
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PLL_EN]);
            dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_BP]);
            do
            {
                dsp_get_reg(&data, &g_dsp_ctrl[etype].reg_sysctrl[PLL_LOCK]);
            }
            while(!data);

            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PLL_CLK_GT]);
        }
    }
    else if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PD].base_addr))
    {
        //P532
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PD]);
    }
    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_pll_disable_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);
    /* close dsp dfs */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PLL_EN].base_addr))
    {
        //k3、V7R5
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_CLK_GT]);
        dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[PLL_EN]);
    }
    else if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[PD].base_addr))
    {
        //P532
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[PD]);
    }
    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

/* 0:dsp pll   1:ccpu/peri pll*/
void bsp_bbe_chose_pll_ex(enum bsp_dsp_type_e etype, u32 flag)
{
    u32 tmp = 0;
    if(0 == flag)
    {
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            //AUSTIN X模
            tmp = readl(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first: bbe sel dsp pll */
            tmp &= ~0x30;
            tmp |= 0x300020;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=1 */
            tmp &= ~0xF;
            tmp |= 0xF0000;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW]);
            dsp_set_reg(0, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_CLK_DIV]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_FREQMODE]);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);
        }
    }
    else
    {
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr))
        {
            //AUSTIN X模
            tmp = readl(g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            /* first :div [3:0] div=2 */
            tmp &= ~0xF;
            tmp |= 0xF0001;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
            udelay(1);
            /* bbe sel ccpu pll */
            tmp &= ~0x30;
            tmp |= 0x300010;
            writel(tmp, g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].base_addr + g_dsp_ctrl[etype].reg_sysctrl[SEL_MODEM_BBE16].offset);
        }
        if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW].base_addr))
        {
            //V7R5
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_CORE_CLK_DIV]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_FREQMODE]);
            udelay(1);
            dsp_set_reg(2, &g_dsp_ctrl[etype].reg_sysctrl[DSP0_REFCLK_SW]);
            dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);
        }
    }
}

int bsp_dsp_dfs_pll_status_ex(enum bsp_dsp_type_e etype)
{
    int ret = PWRCTRL_COMM_ON;

    if(1 == g_cdsp_drx.drx_cbbe16_pll)
    {
        return ret;
    }
    else
    {
        ret = bsp_dsp_pll_status_ex(etype);

        if(ret == 1)
        {
            ret = PWRCTRL_COMM_ON;
        }
        else
        {
            ret = PWRCTRL_COMM_OFF;
        }

        return ret;
    }
}

int bsp_dsp_dfs_pll_enable_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    if(g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll)
    {
        if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V8R5 == bsp_get_version_info()->chip_type)
        {
            return ret;
        }
        else
        {
            ret = bsp_dsp_pll_enable_ex(etype);
            bsp_bbe_chose_pll_ex(etype, 0);
        }
    }
    return ret;
}

int bsp_dsp_dfs_pll_disable_ex(enum bsp_dsp_type_e etype)
{
    int ret = 0;
    if(1 == g_cdsp_drx.drx_cbbe16_pll)
    {
        return ret;
    }
    else
    {
        if(g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll)
        {
            if(PLAT_ASIC == bsp_get_version_info()->plat_type && CHIP_V8R5 == bsp_get_version_info()->chip_type)
            {
                return ret;
            }
            else
            {
                bsp_bbe_chose_pll_ex(etype, 1);
                ret = bsp_dsp_pll_disable_ex(etype);
            }
        }
        return ret;
    }
}

void bsp_bbe_refclk_enable_ex(enum bsp_dsp_type_e etype)
{
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN].base_addr))
    {
        //k3
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_EN]);
    }
}

void bsp_bbe_refclk_disable_ex(enum bsp_dsp_type_e etype)
{
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS].base_addr))
    {
        //k3
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE_REFCLK_DIS]);
    }
}

int bsp_dsp_unreset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* unreset BBE16 */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_DIS].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_DIS]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset = 1;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}

int bsp_dsp_reset_ex(enum bsp_dsp_type_e etype)
{
    unsigned long irq_flags;

    spin_lock_irqsave(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    /* reset BBE16 */
    if(IS_VALID_ADDR(g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_EN].base_addr))
    {
        dsp_set_reg(1, &g_dsp_ctrl[etype].reg_sysctrl[BBE16_PD_SRST_EN]);
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset = 0;

    spin_unlock_irqrestore(&(g_dsp_ctrl[etype].ctrl_state.spin_lock), irq_flags);

    return 0;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_store_tcm_force
*
* 功能描述  : 强制进行BBE16的DTCM的备份，用于dump模块备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_store_tcm_force(void)
{
    int ret = 0;
    struct cdsp_dump_proc_flag *flag;

    flag = (struct cdsp_dump_proc_flag *)((unsigned int)SHM_BASE_ADDR + SHM_OFFSET_CDSP_FLAG);
    flag->cdsp_dump_flag = 0;

    ret = (int)(g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_dsp_power_on &&
                g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_dsp_clock_enable &&
                g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_dsp_unreset &&
                g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_bbe_power_on &&
                g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_bbe_clock_enable &&
                g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.is_bbe_unreset);

    if (!ret)
    {
        cdsp_print("store CBBE dtcm fail : dsp is in deep sleep!\r\n");
        return (-1);
    }

    flag->cdsp_dump_flag = SAVE_CBBE_TCM_BEGIN;

    /*ARM发送NMI中断给CBBE，通知DSP保存寄存器信息*/
    bsp_int_send_nmi(NMI_INT_TO_XPHY, 0);
    udelay(10);

    ret  = bsp_bbe_stop_ex(BSP_DSP_CBBE);
    ret |= bsp_bbe_store_dtcm_ex(BSP_DSP_CBBE);
    ret |= bsp_bbe_wait_store_tcm_over(BSP_DSP_CBBE);
    ret |= bsp_bbe_store_itcm_ex(BSP_DSP_CBBE);
    ret |= bsp_bbe_wait_store_tcm_over(BSP_DSP_CBBE);
    if (ret)
    {
        cdsp_print("fail to store CBBE dtcm\r\n");
        return (-1);
    }
    flag->cdsp_dump_flag = SAVE_CBBE_TCM_END;

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_store_dtcm_normal
*
* 功能描述  : DSP正常睡眠时BBE16的DTCM的备份，用于MSP低功耗模块备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_store_dtcm_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_NEED;

    if(!g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        ret = bsp_bbe_store_ex(etype);

        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_DOING;
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 1;

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_wait_store_over_normal
*
* 功能描述  : 等待备份完成
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_wait_store_over_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if (DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_wait_store_over(etype);

        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_HAD;
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_restore_tcm_normal
*
* 功能描述  : DSP正常睡眠时BBE16的TCM的恢复，用于MSP低功耗模块做DSP备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_restore_tcm_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if(DSP_STORE_HAD == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_restore_ex(etype);

        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_RESTORE_DOING;
    }

    g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep = 0;

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_wait_restore_over_normal
*
* 功能描述  : 等待恢复完成
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_wait_restore_over_normal(enum bsp_dsp_type_e etype)
{
    int ret = 0;

    if (DSP_RESTORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
    {
        ret = bsp_bbe_wait_restore_over(etype);

        g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_IDLE;
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_get_addr_info
*
* 功能描述  : 获取DSP相关地址信息
*
* 输入参数  : pAddrInfo
* 输出参数  : pAddrInfo
*
* 返 回 值  : 0-成功; 1-失败
* 其它说明  : 如果调用此接口时镜像加载驱动还没有初始化，则返回失败
*
*****************************************************************************/
int bsp_dsp_get_addr_info(enum bsp_dsp_type_e etype, BSP_DSP_ADDR_INFO_STRU *pAddrInfo)
{
    if(NULL == pAddrInfo)
    {
        return 1;
    }

    if(BSP_DSP_CBBE == etype)
    {
        if(0 != g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr)
        {
            pAddrInfo->load_addr    = (u32)g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr;
            pAddrInfo->backup_addr  = (u32)(g_dsp_ctrl[etype].tcm_info.bbe_ddr_pub_dtcm_addr + CBBE_1X_DATA_OFFSET);

            return 0;
        }
    }

    return 1;
}

#ifdef CONFIG_CCORE_PM

/*****************************************************************************
* 函 数 名  : bsp_dsp_dpm_prepare
*
* 功能描述  : dpm prepare流程中BBE16的DTCM的备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_dpm_prepare(struct dpm_device *dev)
{
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(DSP_STORE_NEED == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_clk_enable(etype);
            ret |= bsp_bbe_unreset_ex(etype);

            /* save public image's data */
            ret |= bsp_bbe_store_ex(etype);
            g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_DOING;
        }
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_dpm_suspend_late
*
* 功能描述  : dpm late流程中BBE16的DTCM的备份
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_dpm_suspend_late(struct dpm_device *dev)
{
    /* 在设备进入睡眠模式之前判断是否真的存储完成，如果完成，则将bbe下电 */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_wait_store_over(etype);
            g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state = DSP_STORE_HAD;

            ret |= bsp_bbe_reset_ex(etype);
            ret |= bsp_bbe_clk_disable(etype);
        }

        ret |= bsp_dsp_reset_ex(etype);
        ret |= bsp_dsp_clk_disable(etype);

#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_disable_ex(etype);
#else
        ret |= bsp_dsp_pll_disable_ex(etype);
#endif
        if(g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_off_ex(etype);
        }
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_disable_ex(etype);
#else
        /* V7R5路径，bbe16单独上下电，DPM只负责关闭DSP PLL，
           但是V7R5在DSP下电时已经切到peri_pll，dsp_pll随dsp上电时打开，并切换回来，此处代码删除 */
//        ret |= bsp_dsp_pll_disable_ex(etype);
#endif
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_dpm_resume_early
*
* 功能描述  : dpm resume early流程中BBE16的TCM的恢复
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_dpm_resume_early(struct dpm_device *dev)
{
    /* dsp上电 */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        if(g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep)
        {
            ret |= bsp_bbe_power_on_ex(etype);
        }

#if defined(CONFIG_G_POWER_OPTIMIZE)
        bsp_bbe_refclk_enable_ex(etype);
#else
        ret |= bsp_dsp_pll_enable_ex(etype);
#endif

        ret |= bsp_dsp_clk_enable(etype);
        ret |= bsp_dsp_unreset_ex(etype);
    }
    else
    {
#if defined(CONFIG_G_POWER_OPTIMIZE)
        /* K3V5路径，bbe16单独上下电，DPM只负责打开bbp子系统参考时钟 */
        bsp_bbe_refclk_enable_ex(etype);
#else
        /* V7R5路径，bbe16单独上下电，DPM只负责打开DSP PLL，
           但是V7R5在DSP下电时已经切到peri_pll，dsp_pll随dsp上电时打开，并切换回来，此处代码删除 */
//      ret |= bsp_dsp_pll_enable_ex(etype);
#endif
    }

    return ret;
}


/*****************************************************************************
* 函 数 名  : bsp_dsp_dpm_resume_early
*
* 功能描述  : dpm complete流程中BBE16
*
* 返 回 值  : 0，成功；1，失败
*
* 其它说明  :
*
*****************************************************************************/
int bsp_dsp_dpm_complete(struct dpm_device *dev)
{
    /* dsp上电后关bbe */
    int ret = 0;
    enum bsp_dsp_type_e etype = BSP_DSP_CBBE;

    if(g_dsp_ctrl[etype].pwc_ctrl.is_pmctrl_in_dpm)
    {
        /* 避免其他模块suspend有失败导致bsp_dsp_dpm_suspend_late没走到 */
        if(DSP_STORE_DOING == g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state)
        {
            ret = bsp_bbe_wait_store_over(etype);
            ret |= bsp_bbe_reset_ex(etype);
            ret |= bsp_bbe_clk_disable(etype);
        }
    }

    return ret;
}


static struct dpm_device g_dsp_dpm_device = {
    .device_name = "dsp_dpm",
    .prepare        = bsp_dsp_dpm_prepare,
    .suspend_early  = NULL,
    .suspend        = NULL,
    .suspend_late   = bsp_dsp_dpm_suspend_late,
    .resume_early   = bsp_dsp_dpm_resume_early,
    .resume         = NULL,
    .resume_late    = NULL,
    .complete       = bsp_dsp_dpm_complete,
};
#endif

/*****************************************************************************
 函 数 名  : ccpu_reset_cbbe16_and_wait_idle
 功能描述  : c核复位后关闭并等cbbe16进入空闲态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : ccpu_reset_cbbe16_and_wait_idle
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    修改内容   : 新生成函数

*****************************************************************************/
int ccpu_halt_cbbe16_and_wait_idle(void)
{
    int ret = 0;
#ifndef CONFIG_HI3650_TLBBP_DS
    unsigned int regvalue = 0;
#endif

    bsp_reset_timestamp(0x1, STAMP_RESET_CBBE16_ENTER_IDLE);
    /*ARM发送NMI中断给CBBE，通知DSP保存寄存器信息*/
    bsp_int_send_nmi(NMI_INT_TO_XPHY, 0);
    udelay(10);
    
    ret  = bsp_bbe_stop_ex(BSP_DSP_CBBE);
    if(ret)
    {
        return (-1);
    }
    bsp_reset_timestamp(0x2, STAMP_RESET_CBBE16_ENTER_IDLE);
    
#ifndef CONFIG_HI3650_TLBBP_DS
	/* stop socp channel to prevent data transferring when cbbe16 powered down */
	regvalue = readl(SOCP_REG_BASEADDR + SOCP_REG_ENCSRC_BUFCFG1(SOCP_CODER_SRC_XDSP));
	writel((regvalue & 0xfffffffe), (SOCP_REG_BASEADDR + SOCP_REG_ENCSRC_BUFCFG1(SOCP_CODER_SRC_XDSP)));
	while(readl(SOCP_REG_BASEADDR + SOCP_REG_ENCSTAT) & (1 << (SOCP_CODER_SRC_XDSP)))
	{

	}
#endif

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_CBBE16_ENTER_IDLE);
    
    return ret;    
}

int ccpu_reset_cbbe16_sysbus(void)
{
    int ret = 0;
    /*reset cbbe16*/
    ret = bsp_bbe_reset_ex(BSP_DSP_CBBE);
    ret |= bsp_dsp_reset_ex(BSP_DSP_CBBE);
    if(ret)
    {
        return (-1);
    }
    
    return ret;
}



/*lint -save -e525*/
void dsp_load_init(void)
{
    int ret = 0;
    int i = 0;
    u32 reg_addr[4];
    struct device_node *dev_node = NULL;
    char* node_name[2] = {
        "hisilicon,cdsp_balong_dtcm",
        "hisilicon,cdsp_balong_itcm"
    };
    ST_PWC_SWITCH_STRU cfg;
    char *reg_name[DSP_DTS_REG_BUTT] = {
                            "bbe16_pd_clk_en",
                            "bbe16_pd_clk_dis",
                            "bbe16_pd_srst_dis",
                            "bbe16_pd_srst_en",
                            "bbe16_core_srst_dis",
                            "bbe16_dbg_srst_dis",
                            "bbe16_core_srst_en",
                            "bbe16_dbg_srst_en",
                            "pd",
                            "bbe16_runstall",
                            "bbe_refclk_en",
                            "bbe_refclk_dis",
                            "pll_lock",
                            "pll_en",
                            "pll_bp",
                            "pll_postdivpd",
                            "pll_clk_gt",
                            "pll_dfs1",
                            "pll_dfs2",
                            "div_modem_bbe16",
                            "sel_modem_bbe16",
                            "clkdivmasken",
                            "dsp0_core_clk_dis",
                            "dsp0_dbg_clk_dis",
                            "bbe_core_clk_en",
                            "dsp0_dbg_clk_en",
                            "bbe16_mtcmos_ctrl_en",
                            "bbe16_mtcmos_rdy_stat",
                            "bbe16_iso_ctrl_dis",
                            "bbe16_mtcmos_ctrl_dis",
                            "bbe16_iso_ctrl_en",
                            "bbe16_waiti_en",
                            "bbe16_waiti_div",
                            "bbe16_core_clk_div",
                            "dsp0_freqmode",
                            "dsp0_refclk_sw"
                            };

    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)&cfg, sizeof(ST_PWC_SWITCH_STRU)))
	{
        cdsp_print("Dsp_balong get NV_ID_DRV_NV_PWC_SWITCH failed!\n");
	}
    else
    {
        g_cdsp_drx.drx_cbbe16_pd = cfg.drx_cbbe16_pd;
        g_cdsp_drx.drx_cbbe16_pll =  cfg.drx_cbbe16_pll;
    }

    memset_s(&g_dsp_ctrl[BSP_DSP_TLBBE], sizeof(g_dsp_ctrl), 0, sizeof(g_dsp_ctrl));

    dev_node = of_find_compatible_node(NULL,NULL,node_name[0]);
    if(!dev_node)
    {
        cdsp_print("dsp init failed : get cdsp_balong_dtcm node failed!\n");
        return;
    }

    /* 内存映射，获得基址 */
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_dtcm_base_addr)
    {
        cdsp_print("dsp init failed : cdsp_balong_dtcm iomap failed!\n");
        return;
    }

    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.lphy_pub_dtcm_size = CPHY_PUB_DTCM_SIZE;

    ret  = of_property_read_u32(dev_node, "is_pmctrl_in_dpm", &g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.is_pmctrl_in_dpm);
    ret |= of_property_read_u32(dev_node, "can_switch_pll", &g_dsp_ctrl[BSP_DSP_CBBE].pwc_ctrl.can_switch_pll);
    if(ret)
    {
        cdsp_print("dsp init failed : dtcm dev_node read failed!\n");
        return;
    }

    dev_node = of_find_compatible_node(NULL,NULL,node_name[1]);
    if(!dev_node)
    {
        cdsp_print("dsp init failed : get dsp_balong_itcm node faileded!\n");
        return;
    }

    /* 内存映射，获得基址 */
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_itcm_base_addr = (char *)of_iomap(dev_node, 0);
    if (NULL == g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.tcm_itcm_base_addr)
    {
        cdsp_print("dsp init failed : dsp_balong_itcm iomap failed!\n");
        return;
    }
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.lphy_pub_itcm_size = CPHY_PUB_ITCM_SIZE;

    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_dtcm_addr = (int)ioremap_wc((MMU_VA_T)DDR_CBBE_IMAGE_ADDR, DDR_CBBE_IMAGE_SIZE);
    g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_itcm_addr = g_dsp_ctrl[BSP_DSP_CBBE].tcm_info.bbe_ddr_pub_dtcm_addr + CPHY_PUB_DTCM_SIZE;

    for(i = 0; i < DSP_DTS_REG_BUTT; i++)
    {
        ret = of_property_read_u32_array(dev_node, reg_name[i], reg_addr, DSP_ADDR_BUTT);
        if(ret)
        {
            cdsp_print("dsp init failed : itcm dev_node reg read failed!\n");
            return;
        }

        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[DSP_BASE_ADDR]);
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].offset    = reg_addr[DSP_OFFSET];
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].start_bit = reg_addr[DSP_START_BIT];
        g_dsp_ctrl[BSP_DSP_CBBE].reg_sysctrl[i].end_bit   = reg_addr[DSP_END_BIT];
    }

    spin_lock_init(&(g_dsp_ctrl[BSP_DSP_CBBE].ctrl_state.spin_lock));

    (void)bsp_register_master_idle(CBBE16_IDLE, ccpu_halt_cbbe16_and_wait_idle);

    (void)bsp_register_master_idle(CBBE16_SYSBUS, ccpu_reset_cbbe16_sysbus);

#ifdef CONFIG_CCORE_PM
    ret = bsp_device_pm_add(&g_dsp_dpm_device);
#endif
    if (ret)
    {
        cdsp_print("dsp init failed : bsp_device_pm_add failed!\n");
        return;
    }

    cdsp_print("dsp_load_init success .\n");
}
/*lint -restore*/

/*****************************************************************************
* 函 数 名  : dsp_load_help
*
* 功能描述  : DSP加载模块的帮助
*
* 其它说明  :
*
*****************************************************************************/
void dsp_load_help(enum bsp_dsp_type_e etype)
{
    cdsp_print("bsp_bbe_load is called: %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bsp_bbe_load_called);
    cdsp_print("dsp_restore_count : %d \n", g_dsp_ctrl[etype].ctrl_state.dsp_restore_count);
    cdsp_print("dsp_restore_succ_count : %d \n", g_dsp_ctrl[etype].ctrl_state.dsp_restore_succ_count);
    cdsp_print("dsp_store_count : %d \n", g_dsp_ctrl[etype].ctrl_state.dsp_store_count);
    cdsp_print("dsp_store_succ_count : %d \n", g_dsp_ctrl[etype].ctrl_state.dsp_store_succ_count);
    cdsp_print("is_dsp_power_on %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_power_on);
    cdsp_print("is_dsp_clock_enable %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_clock_enable);
    cdsp_print("is_dsp_unreset %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_unreset);
    cdsp_print("is_bbe_power_on %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_power_on);
    cdsp_print("is_bbe_clock_enable %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_clock_enable);
    cdsp_print("is_bbe_unreset %d.\n", g_dsp_ctrl[etype].ctrl_state.is_bbe_unreset);
    cdsp_print("is_dsp_running %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_running);
    cdsp_print("is_dsp_deep_sleep %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_deep_sleep);
    cdsp_print("is_dsp_store_state %d.\n", g_dsp_ctrl[etype].ctrl_state.is_dsp_store_state);
    cdsp_print("DDR_CBBE_IMAGE_ADDR is : 0x%x, DDR_CBBE_IMAGE_SIZE is : 0x%x. \n", DDR_CBBE_IMAGE_ADDR, DDR_CBBE_IMAGE_SIZE);
    cdsp_print("TCM_DTCM_BASE_ADDR is : 0x%p\n", g_dsp_ctrl[etype].tcm_info.tcm_dtcm_base_addr);
    cdsp_print("cphy_dtcm_size is : 0x%x\n", CPHY_PUB_DTCM_SIZE);
    cdsp_print("TCM_ITCM_BASE_ADDR is : 0x%p\n", g_dsp_ctrl[etype].tcm_info.tcm_itcm_base_addr);
    cdsp_print("cphy_itcm_size is : 0x%x\n", CPHY_PUB_ITCM_SIZE);
}
#endif


