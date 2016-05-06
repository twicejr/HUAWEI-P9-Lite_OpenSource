/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_acs_test.c
  版 本 号   : 初稿
  作    者   : 王山博
  生成日期   : 2014年4月21日
  最近修改   :
  功能描述   : 芯片验证空闲功率、信道繁忙度功能的dmac层测试代码等
  函数列表   :
  修改历史   :
  1.日    期   : 2014年4月21日
    作    者   : w00196298
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"

#if  defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include "dmac_acs_test.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ACS_TEST_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
acs_hw_verify_stru                g_st_acs_verify_info;
OAL_STATIC struct proc_dir_entry *g_pst_acs_proc_entry = NULL;

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : Linux 的PROC 接口定义
 功能描述  : Linux 的PROC实现所需的所有相关函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月21日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_int32 dmac_acs_seq_show(struct seq_file *f, void *v)
{
    acs_hw_statics_stru  *pst_dv_stats = &((acs_hw_verify_stru *)v)->st_acs_stats_result;
    acs_hw_verify_stru   *pst_hw_vi = (acs_hw_verify_stru *)v;
    oal_uint32            ul_cycles, ul_idx;

    if ((ACS_SUMMARY_TEST_MODE == pst_hw_vi->ul_test_mode) || (ACS_STATS_TEST_MODE == pst_hw_vi->ul_test_mode))
    {
        /* sorting */
        if ((1 == pst_hw_vi->ul_test_running) && (ACS_SUMMARY_TEST_MODE == pst_hw_vi->ul_test_mode))
        {
            oal_int32   *apul_list[6], exch;
            oal_uint32   ii, jj, idx;
            oal_uint32   rest_len, margin, cuttoff;

            pst_hw_vi->ul_test_running = 0;
            apul_list[0] = pst_hw_vi->pul_20m_freepwr;
            apul_list[3] = pst_hw_vi->pul_20m_freetime;
            apul_list[1] = pst_hw_vi->pul_40m_freepwr;
            apul_list[4] = pst_hw_vi->pul_40m_freetime;
            apul_list[2] = pst_hw_vi->pul_80m_freepwr;
            apul_list[5] = pst_hw_vi->pul_80m_freetime;

            for (idx = 0; idx < 6; idx++)
            {
                for (ii = 0; ii < pst_hw_vi->ul_curr_idx; ii++)
                {
                    for (jj = 0; jj < pst_hw_vi->ul_curr_idx - ii - 1; jj++)
                    {
                        if (apul_list[idx][jj] > apul_list[idx][jj + 1])
                        {
                            exch = apul_list[idx][jj];
                            apul_list[idx][jj] = apul_list[idx][jj + 1];
                            apul_list[idx][jj + 1] = exch;
                        }
                    }
                }
            }

            cuttoff  = pst_hw_vi->ul_curr_idx >> 2;
            margin   = cuttoff >> 1;
            rest_len = pst_hw_vi->ul_curr_idx - 2 * margin;
            OAM_INFO_LOG2(0, OAM_SF_ANY, "[kernel]margin=%d, rest_len=%d\n", margin, rest_len);
            pst_hw_vi->st_acs_stats_result.aul_meas_cnt[0]  = 1;
            pst_hw_vi->st_acs_stats_result.aul_meas_cnt[1]  = 1;
            pst_hw_vi->st_acs_stats_result.aul_meas_cnt[2]  = 1;
            pst_hw_vi->st_acs_stats_result.aul_stats_cnt[0] = 1;
            pst_hw_vi->st_acs_stats_result.aul_stats_cnt[1] = 1;
            pst_hw_vi->st_acs_stats_result.aul_stats_cnt[2] = 1;
            for (idx = 0; idx < 6; idx++)
            {
                for (ii = margin + 1; ii < (pst_hw_vi->ul_curr_idx - margin); ii++)
                {
                    if (idx <= 2)
                    {
                        if (ii == (margin+1))
                        {
                            if (apul_list[idx][margin] >= 0)
                            {
                                apul_list[idx][margin] = 0;
                                pst_hw_vi->st_acs_stats_result.aul_meas_cnt[idx] = 0;
                            }
                        }

                        if (apul_list[idx][ii] >= 0)
                        {
                            continue;
                        }

                        apul_list[idx][margin] +=  apul_list[idx][ii];
                        pst_hw_vi->st_acs_stats_result.aul_meas_cnt[idx] += 1;
                    }
                    else
                    {
                        apul_list[idx][margin] +=  apul_list[idx][ii];
                        pst_hw_vi->st_acs_stats_result.aul_stats_cnt[idx - 3] += 1;
                    }
                }
            }

            pst_hw_vi->st_acs_stats_result.l_pri20_idle_power = apul_list[0][margin];
            pst_hw_vi->st_acs_stats_result.l_pri40_idle_power = apul_list[1][margin];
            pst_hw_vi->st_acs_stats_result.l_pri80_idle_power = apul_list[2][margin];
            pst_hw_vi->st_acs_stats_result.ul_pri20_free_time_us = apul_list[3][margin];
            pst_hw_vi->st_acs_stats_result.ul_pri40_free_time_us = apul_list[4][margin];
            pst_hw_vi->st_acs_stats_result.ul_pri80_free_time_us = apul_list[5][margin];

            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_20m_freepwr);
            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_40m_freepwr);
            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_80m_freepwr);
            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_20m_freetime);
            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_40m_freetime);
            ACS_HW_INFO_CLEAR(pst_hw_vi->pul_80m_freetime);
        }
    }

    if (ACS_SUMMARY_TEST_MODE == pst_hw_vi->ul_test_mode) /* summarize mode */
    {
        /* start ts */
        seq_printf(f, "test_cnt     %d\n",   pst_dv_stats->ul_test_cnt);
        seq_printf(f, "20m_free_us  %d\n",   pst_dv_stats->ul_pri20_free_time_us);
        seq_printf(f, "40m_free_us  %d\n",   pst_dv_stats->ul_pri40_free_time_us);
        seq_printf(f, "80m_free_us  %d\n",   pst_dv_stats->ul_pri80_free_time_us);
        seq_printf(f, "20m_free_pwr %d\n",   pst_dv_stats->l_pri20_idle_power);
        seq_printf(f, "40m_free_pwr %d\n",   pst_dv_stats->l_pri40_idle_power);
        seq_printf(f, "80m_free_pwr %d\n",   pst_dv_stats->l_pri80_idle_power);
        seq_printf(f, "tx_us        %d\n",   pst_dv_stats->ul_ch_tx_time_us);
        seq_printf(f, "rx_us        %d\n",   pst_dv_stats->ul_ch_rx_time_us);
        seq_printf(f, "stats_cnt    %d %d %d\n",   pst_dv_stats->aul_stats_cnt[0], pst_dv_stats->aul_stats_cnt[1], pst_dv_stats->aul_stats_cnt[2]);
        seq_printf(f, "meas_cnt     %d %d %d\n",   pst_dv_stats->aul_meas_cnt[0], pst_dv_stats->aul_meas_cnt[1], pst_dv_stats->aul_meas_cnt[2]);
    }
    else if (ACS_STATS_TEST_MODE == pst_hw_vi->ul_test_mode) /* statistics mode */
    {
        ul_cycles = pst_hw_vi->ul_cycles_backup;

        seq_printf(f, "test_cnt     %d\n", pst_dv_stats->ul_test_cnt);
        seq_printf(f, "run_cycles   %d\n", ul_cycles);

        ACS_SHOW_HW_INFO("20m_free_us:\n", pul_20m_freetime);

        ACS_SHOW_HW_INFO("40m_free_us:\n", pul_40m_freetime);

        ACS_SHOW_HW_INFO("80m_free_us:\n", pul_80m_freetime);

        ACS_SHOW_HW_INFO("20m_free_pwr:\n", pul_20m_freepwr);

        ACS_SHOW_HW_INFO("40m_free_pwr:\n", pul_40m_freepwr);

        ACS_SHOW_HW_INFO("80m_free_pwr:\n", pul_80m_freepwr);
    }
    else if(ACS_TX_TIME_TEST_MODE == pst_hw_vi->ul_test_mode)
    {
        seq_printf(f, "test_cnt     %d\n", pst_dv_stats->ul_test_cnt);
        seq_printf(f, "stats_us     %d\n",   pst_dv_stats->aul_stats_cnt[0]);
        seq_printf(f, "tx_us        %d\n",   pst_dv_stats->ul_ch_tx_time_us);
        seq_printf(f, "rx_us        %d\n",   pst_dv_stats->ul_ch_rx_time_us);
    }
    else if (ACS_READ_REG_MODE == pst_hw_vi->ul_test_mode)
    {
        seq_printf(f, "reg_data 0x%08X\n", g_st_acs_verify_info.ul_reg_data);
    }
    else
    {
        seq_printf(f, "Unknown display mode.\n");
    }

    return 0;
}

OAL_STATIC oal_void *dmac_acs_seq_start(struct seq_file *f, loff_t *pos)
{
    if (0 == *pos)
    {
        return &g_st_acs_verify_info;
    }
    else
    {
        return NULL;
    }
}

OAL_STATIC oal_void *dmac_acs_seq_next(struct seq_file *f, void *v, loff_t *pos)
{
    return NULL;
}

OAL_STATIC oal_void dmac_acs_seq_stop(struct seq_file *f, void *v)
{
    /* Nothing to do */
}

OAL_STATIC OAL_CONST struct seq_operations dmac_acs_seq_ops = {
    .start = dmac_acs_seq_start,
    .next  = dmac_acs_seq_next,
    .stop  = dmac_acs_seq_stop,
    .show  = dmac_acs_seq_show
};

OAL_STATIC oal_int32 dmac_acs_seq_open(struct inode *inode, struct file *filp)
{
    return seq_open(filp, &dmac_acs_seq_ops);
}

OAL_STATIC ssize_t dmac_acs_proc_write(struct file *file,
        const char __user *buffer, size_t count, loff_t *ppos)
{
    oal_uint32         tmp, i, ul_cnt;
    mac_device_stru   *pst_mac_dev;
    oal_int8           ac_cmd[64], c_size, c_flag;
    oal_uint32         aul_nums[4], ul_num_idx;

    c_size = count;
    if (c_size > 63)
    {
        c_size = 63;
    }

    if (copy_from_user(ac_cmd, buffer, c_size) != 0)
    {
        return -EFAULT;
    }
    ac_cmd[c_size] = '\0';

    i = 0;
    tmp = 0;
    ul_num_idx = 0;
    c_flag = 0;
    while(1)
    {
        if ((ac_cmd[i] == '\n') || (ac_cmd[i] == '\0'))
        {
            if (c_flag)
                aul_nums[ul_num_idx++] = tmp;
            break;
        }

        if (ac_cmd[i] == ' ')
        {
            if (c_flag)
            {
                aul_nums[ul_num_idx++] = tmp;
                tmp = 0;
                c_flag = 0;
            }

            if (ul_num_idx > 3)
            {
                break;
            }
            i += 1;
        }
        else
        {
            if (!((ac_cmd[i] >= '0') && (ac_cmd[i] <= '9')))
            {
                g_st_acs_verify_info.ul_cycles = 0;
                goto out;
            }

            tmp = tmp * 10 + ac_cmd[i] - '0';
            c_flag = 1;
            i     += 1;
        }
    }

    if (ul_num_idx != 3)
    {
        goto out;
    }
    OAM_INFO_LOG3(0, OAM_SF_ANY,"[kernel]Input numbers: %d %d %d\n", aul_nums[0], aul_nums[1], aul_nums[2]);

    if (0 == aul_nums[2])/* CHIP TEST */
    {
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_20m_freepwr);
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_40m_freepwr);
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_80m_freepwr);
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_20m_freetime);
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_40m_freetime);
        ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_80m_freetime);

        ul_cnt = g_st_acs_verify_info.st_acs_stats_result.ul_test_cnt;
        OAL_MEMZERO(&g_st_acs_verify_info.st_acs_stats_result, OAL_SIZEOF(g_st_acs_verify_info.st_acs_stats_result));
        g_st_acs_verify_info.st_acs_stats_result.ul_test_cnt = ul_cnt;
        g_st_acs_verify_info.ul_cycles        = aul_nums[0];
        g_st_acs_verify_info.ul_cycles_backup = aul_nums[0];
        g_st_acs_verify_info.ul_test_mode     = aul_nums[1];

        g_st_acs_verify_info.pul_20m_freepwr  = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.pul_40m_freepwr  = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.pul_80m_freepwr  = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.pul_20m_freetime = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.pul_40m_freetime = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.pul_80m_freetime = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(oal_int32) * aul_nums[0], OAL_TRUE);
        g_st_acs_verify_info.ul_curr_idx      = 0;

        OAM_INFO_LOG2(0, OAM_SF_ANY, "[kernel]Begin acs hw test(cycles=%d, mode=%d).\n", aul_nums[0], aul_nums[1]);
        pst_mac_dev = mac_res_get_dev(0);
        hal_set_ch_statics_period(pst_mac_dev->pst_device_stru, 8000);
        hal_set_ch_measurement_period(pst_mac_dev->pst_device_stru, 8);
        hal_enable_ch_statics(pst_mac_dev->pst_device_stru, 1);
        g_st_acs_verify_info.ul_test_running = 1;
    }
    else if (1 == aul_nums[2]) /* tx time test */
    {
        OAM_INFO_LOG1(0, OAM_SF_ANY, "[kernel]Begin hw tx time test(time=%d ms).\n", aul_nums[0]);
        pst_mac_dev = mac_res_get_dev(0);
        hal_set_ch_statics_period(pst_mac_dev->pst_device_stru, 1000 * aul_nums[0]);
        hal_set_ch_measurement_period(pst_mac_dev->pst_device_stru, 8);
        hal_enable_ch_statics(pst_mac_dev->pst_device_stru, 1);
        g_st_acs_verify_info.ul_test_mode = aul_nums[1];
        OAL_MEMZERO(&g_st_acs_verify_info.st_acs_stats_result, OAL_SIZEOF(g_st_acs_verify_info.st_acs_stats_result));
        g_st_acs_verify_info.st_acs_stats_result.aul_stats_cnt[0] = 1000 * aul_nums[0];
    }
    else if (2 == aul_nums[2]) /* read register */
    {
        pst_mac_dev = mac_res_get_dev(0);
        g_st_acs_verify_info.ul_test_mode = aul_nums[1];
        OAM_INFO_LOG1(0, OAM_SF_ANY,"Read register @address 0x%08X.\n", aul_nums[0]);
        hal_reg_info(pst_mac_dev->pst_device_stru, aul_nums[0], &g_st_acs_verify_info.ul_reg_data);
    }

out:
    return count;
}

OAL_STATIC OAL_CONST struct file_operations st_acs_proc_fops = {
    .open       = dmac_acs_seq_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = seq_release,
    .write      = dmac_acs_proc_write
};

/*****************************************************************************
 函 数 名  : dmac_acs_channel_meas_comp_handler
 功能描述  : 处理信道测量结果
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_void    dmac_acs_channel_meas_comp_handler(mac_device_stru *pst_mac_dev, hal_ch_statics_irq_event_stru *pst_mac_stats_result)
{
    oal_uint32  ul_cnt, ul_idx;

    if (ACS_TX_TIME_TEST_MODE == g_st_acs_verify_info.ul_test_mode)
    {
        g_st_acs_verify_info.st_acs_stats_result.ul_ch_rx_time_us   = pst_mac_stats_result->ul_ch_rx_time_us;
        g_st_acs_verify_info.st_acs_stats_result.ul_ch_tx_time_us   = pst_mac_stats_result->ul_ch_tx_time_us;
        g_st_acs_verify_info.st_acs_stats_result.ul_test_cnt        = 1;

        return;
    }

    if (0 == g_st_acs_verify_info.ul_test_running)
    {
        return;
    }

    ul_cnt = g_st_acs_verify_info.st_acs_stats_result.ul_test_cnt;
    ul_idx = g_st_acs_verify_info.ul_curr_idx;
    g_st_acs_verify_info.pul_20m_freepwr[ul_idx]  = pst_mac_stats_result->c_pri20_idle_power;
    g_st_acs_verify_info.pul_40m_freepwr[ul_idx]  = pst_mac_stats_result->c_pri40_idle_power;
    g_st_acs_verify_info.pul_80m_freepwr[ul_idx]  = pst_mac_stats_result->c_pri80_idle_power;
    g_st_acs_verify_info.pul_20m_freetime[ul_idx] = pst_mac_stats_result->ul_pri20_free_time_us;
    g_st_acs_verify_info.pul_40m_freetime[ul_idx] = pst_mac_stats_result->ul_pri40_free_time_us;
    g_st_acs_verify_info.pul_80m_freetime[ul_idx] = pst_mac_stats_result->ul_pri80_free_time_us;
    g_st_acs_verify_info.st_acs_stats_result.ul_ch_rx_time_us      += pst_mac_stats_result->ul_ch_rx_time_us;
    g_st_acs_verify_info.st_acs_stats_result.ul_ch_tx_time_us      += pst_mac_stats_result->ul_ch_tx_time_us;

    g_st_acs_verify_info.st_acs_stats_result.ul_test_cnt = ul_cnt + 1;
    g_st_acs_verify_info.ul_curr_idx += 1;

    g_st_acs_verify_info.ul_cycles        -= 1;
    if (g_st_acs_verify_info.ul_cycles)
    {
        hal_set_ch_statics_period(pst_mac_dev->pst_device_stru, 8000);
        hal_set_ch_statics_period(pst_mac_dev->pst_device_stru, 8000);
        hal_set_ch_measurement_period(pst_mac_dev->pst_device_stru, 8);
        hal_set_ch_measurement_period(pst_mac_dev->pst_device_stru, 8);
        hal_enable_ch_statics(pst_mac_dev->pst_device_stru, 1);
        hal_enable_ch_statics(pst_mac_dev->pst_device_stru, 1);
    }
    else
    {
        g_st_acs_verify_info.ul_test_running = 0;

        /* sorting */
        if (ACS_SUMMARY_TEST_MODE == g_st_acs_verify_info.ul_test_mode)
        {
            oal_int32   *apul_list[6], exch;
            oal_uint32   ii, jj, idx;
            oal_uint32   rest_len, margin, cuttoff;

            apul_list[0] = g_st_acs_verify_info.pul_20m_freepwr;
            apul_list[3] = g_st_acs_verify_info.pul_20m_freetime;
            apul_list[1] = g_st_acs_verify_info.pul_40m_freepwr;
            apul_list[4] = g_st_acs_verify_info.pul_40m_freetime;
            apul_list[2] = g_st_acs_verify_info.pul_80m_freepwr;
            apul_list[5] = g_st_acs_verify_info.pul_80m_freetime;

            for (idx = 0; idx < 6; idx++)
            {
                for (ii = 0; ii < g_st_acs_verify_info.ul_cycles_backup; ii++)
                {
                    for (jj = 0; jj < g_st_acs_verify_info.ul_cycles_backup - ii - 1; jj++)
                    {
                        if (apul_list[idx][jj] > apul_list[idx][jj + 1])
                        {
                            exch = apul_list[idx][jj];
                            apul_list[idx][jj] = apul_list[idx][jj + 1];
                            apul_list[idx][jj + 1] = exch;
                        }
                    }
                }
            }

            cuttoff  = g_st_acs_verify_info.ul_cycles_backup >> 2;
            margin   = cuttoff >> 1;
            rest_len = g_st_acs_verify_info.ul_cycles_backup - 2 * margin;
            g_st_acs_verify_info.st_acs_stats_result.aul_meas_cnt[0]  = 1;
            g_st_acs_verify_info.st_acs_stats_result.aul_meas_cnt[1]  = 1;
            g_st_acs_verify_info.st_acs_stats_result.aul_meas_cnt[2]  = 1;
            g_st_acs_verify_info.st_acs_stats_result.aul_stats_cnt[0] = 1;
            g_st_acs_verify_info.st_acs_stats_result.aul_stats_cnt[1] = 1;
            g_st_acs_verify_info.st_acs_stats_result.aul_stats_cnt[2] = 1;
            for (idx = 0; idx < 6; idx++)
            {
                for (ii = margin + 1; ii < (g_st_acs_verify_info.ul_cycles_backup - margin); ii++)
                {
                    if (idx <= 2)
                    {
                        if (ii == (margin+1))
                        {
                            if (apul_list[idx][margin] >= 0)
                            {
                                apul_list[idx][margin] = 0;
                                g_st_acs_verify_info.st_acs_stats_result.aul_meas_cnt[idx] = 0;
                            }
                        }

                        if (apul_list[idx][ii] >= 0)
                        {
                            continue;
                        }

                        apul_list[idx][margin] +=  apul_list[idx][ii];
                        g_st_acs_verify_info.st_acs_stats_result.aul_meas_cnt[idx] += 1;
                    }
                    else
                    {
                        apul_list[idx][margin] +=  apul_list[idx][ii];
                        g_st_acs_verify_info.st_acs_stats_result.aul_stats_cnt[idx - 3] += 1;
                    }
                }
            }

            g_st_acs_verify_info.st_acs_stats_result.l_pri20_idle_power = apul_list[0][margin];
            g_st_acs_verify_info.st_acs_stats_result.l_pri40_idle_power = apul_list[1][margin];
            g_st_acs_verify_info.st_acs_stats_result.l_pri80_idle_power = apul_list[2][margin];
            g_st_acs_verify_info.st_acs_stats_result.ul_pri20_free_time_us = apul_list[3][margin];
            g_st_acs_verify_info.st_acs_stats_result.ul_pri40_free_time_us = apul_list[4][margin];
            g_st_acs_verify_info.st_acs_stats_result.ul_pri80_free_time_us = apul_list[5][margin];

            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_20m_freepwr);
            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_40m_freepwr);
            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_80m_freepwr);
            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_20m_freetime);
            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_40m_freetime);
            ACS_HW_INFO_CLEAR(g_st_acs_verify_info.pul_80m_freetime);
        }
    }
}

/*****************************************************************************
 函 数 名  : dmac_acs_verify_init
 功能描述  : ACS芯片验证功能初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月19日
    作    者   : w00196298
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_verify_init(oal_void)
{
    if(g_pst_acs_proc_entry)
    {
        return;
    }
    /* 创建PROC目录 */
    g_pst_acs_proc_entry = ACS_CREATE_PROC_ENTRY(ACS_VERIFY_PROC_NAME, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, NULL);
    if (OAL_PTR_NULL == g_pst_acs_proc_entry)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ACS, "dmac_acs_verify_init: proc entry init failed");
    }

    g_pst_acs_proc_entry->data  = 0;
    g_pst_acs_proc_entry->nlink = 1;        /* linux创建proc默认值 */
    g_pst_acs_proc_entry->proc_fops  = &st_acs_proc_fops;

    OAL_MEMZERO(&g_st_acs_verify_info, OAL_SIZEOF(g_st_acs_verify_info));
}
/*****************************************************************************
 函 数 名  : dmac_acs_verify_exit
 功能描述  : 退出时清理ACS PROC
 输入参数  : oal_void
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月5日
    作    者   : gaolin
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_acs_verify_exit(oal_void)
{
    if (!g_pst_acs_proc_entry)
    {
        return;
    }
    g_pst_acs_proc_entry = OAL_PTR_NULL;
    ACS_REMOVE_PROC_ENTRY(ACS_VERIFY_PROC_NAME, NULL);

    OAL_MEMZERO(&g_st_acs_verify_info, OAL_SIZEOF(g_st_acs_verify_info));
}

#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
