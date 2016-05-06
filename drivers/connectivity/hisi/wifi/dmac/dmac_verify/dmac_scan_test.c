/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_scan_test.c
  版 本 号   : 初稿
  作    者   : 王山博
  生成日期   : 2014年4月21日
  最近修改   :
  功能描述   : 验证扫描模块的相关功能而开发的PRCO接口函数及处理函数
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

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_SCAN_TEST_C
#if 0 /* 扫描上移到请求下发与结果上移到HMAC，DMAC不再支持原有的芯片测试代码 */
#if defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include "dmac_scan_test.h"


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

dmac_scanner_procfs_stru          g_st_scanner_record;
OAL_STATIC struct proc_dir_entry *g_pst_scan_proc_entry;

OAL_CONST oal_int8 *g_apc_err_msg_map[] =
{
    "All OK.",
    "Proc command has non-numeric characters.",
    "Incomplete command.",
    "Invalid band, must be 200(2g) or 205(5g)",
    "Invalid scan mode"
};

OAL_CONST oal_int8 *g_apc_func_name_map[] =
{
    "NULL",
    "FREE_PWR_MEAS",
    "FREE_TIME_STATS",
    "FREE_PWR_MEAS & FREE_TIME_STATS",
    "RADAR_DETECTION",
    "FREE_PWR_MEAS & RADAR_DETECTION",
    "FREE_TIME_STATS & RADAR_DETECTION",
    "FREE_PWR_MEAS & FREE_TIME_STATS & RADAR_DETECTION",
    "BSS_SCAN",
    "FREE_PWR_MEAS & BSS_SCAN",
    "FREE_TIME_STATS & BSS_SCAN",
    "FREE_PWR_MEAS & FREE_TIME_STATS & BSS_SCAN",
    "RADAR_DETECTION & BSS_SCAN",
    "FREE_PWR_MEAS & RADAR_DETECTION & BSS_SCAN",
    "FREE_TIME_STATS & RADAR_DETECTION & BSS_SCAN",
    "FREE_PWR_MEAS & FREE_TIME_STATS & RADAR_DETECTION & BSS_SCAN"
};

extern oal_uint32 dmac_scan_add_req(mac_device_stru *pst_mac_device, mac_scan_req_stru *pst_scan_req);

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
OAL_STATIC oal_int32 dmac_scan_seq_show(struct seq_file *f, void *v)
{
    dmac_scanner_procfs_stru *pst_scan_record = (dmac_scanner_procfs_stru *)v;
    oal_uint8   uc_chan_idx, uc_bss_idx;

    seq_printf(f, "%-16s %s\n", "last_error", g_apc_err_msg_map[pst_scan_record->uc_curr_status]);
    seq_printf(f, "%-16s %d\n", "proc_write", (int)pst_scan_record->uc_write_cnt);
    seq_printf(f, "%-16s %d\n", "proc_read", (int)pst_scan_record->uc_read_cnt);
    seq_printf(f, "%-16s %d\n", "bcast_probe", (int)pst_scan_record->uc_bcast_probe_cnt);
    seq_printf(f, "%-16s %d\n", "enable_stats", (int)pst_scan_record->uc_enable_chan_stats_cnt);
    seq_printf(f, "%-16s %d\n", "enable_radar", (int)pst_scan_record->uc_enable_radar_det_cnt);
    seq_printf(f, "%-16s %d\n", "scan_cb", (int)pst_scan_record->uc_scan_cb_cnt);
    seq_printf(f, "%-16s\n", "last result:");
    for (uc_chan_idx = 0; uc_chan_idx < pst_scan_record->uc_nchans; uc_chan_idx++)
    {
        seq_printf(f, "Channel %d\n", pst_scan_record->ast_channel_results[uc_chan_idx].uc_channel_number);
        seq_printf(f, "\t%-20s %d\n", "[20M_free_time]", pst_scan_record->ast_channel_results[uc_chan_idx].ul_total_free_time_20M_us);
        seq_printf(f, "\t%-20s %d\n", "[40M_free_time]", pst_scan_record->ast_channel_results[uc_chan_idx].ul_total_free_time_40M_us);
        seq_printf(f, "\t%-20s %d\n", "[80M_free_time]", pst_scan_record->ast_channel_results[uc_chan_idx].ul_total_free_time_80M_us);

        seq_printf(f, "\t%-20s %d\n", "[20M_free_pwr]", pst_scan_record->ast_channel_results[uc_chan_idx].s_free_power_stats_20M);
        seq_printf(f, "\t%-20s %d\n", "[40M_free_pwr]", pst_scan_record->ast_channel_results[uc_chan_idx].s_free_power_stats_40M);
        seq_printf(f, "\t%-20s %d\n", "[80M_free_pwr]", pst_scan_record->ast_channel_results[uc_chan_idx].s_free_power_stats_80M);

        seq_printf(f, "\t%-20s %d\n", "[Radar_detected]", pst_scan_record->ast_channel_results[uc_chan_idx].uc_radar_detected);
        seq_printf(f, "\t%-20s %d\n", "[Ch_stats_cnt]", pst_scan_record->ast_channel_results[uc_chan_idx].uc_stats_cnt);
        seq_printf(f, "\t%-20s %d\n", "[Ch_meas_cnt]", pst_scan_record->ast_channel_results[uc_chan_idx].uc_free_power_cnt);
    }

    seq_printf(f, "%-16s %d\n", "BSS result", pst_scan_record->us_nbss);
    for (uc_bss_idx = 0; uc_bss_idx < pst_scan_record->us_nbss; uc_bss_idx++)
    {
        seq_printf(f, "\tBSS%-3d: [chan=%d, mac=%02X:XX:XX:%02X:%02X:%02X, rssi=%d]\n",
                        uc_bss_idx + 1,
                        pst_scan_record->ast_bss_results[uc_bss_idx].uc_channel_number,
                        pst_scan_record->ast_bss_results[uc_bss_idx].auc_bssid[0],
                        pst_scan_record->ast_bss_results[uc_bss_idx].auc_bssid[3],
                        pst_scan_record->ast_bss_results[uc_bss_idx].auc_bssid[4],
                        pst_scan_record->ast_bss_results[uc_bss_idx].auc_bssid[5],
                        pst_scan_record->ast_bss_results[uc_bss_idx].c_rssi);
    }

    return 0;
}

OAL_STATIC oal_void *dmac_scan_seq_start(struct seq_file *f, loff_t *pos)
{
    if (0 == *pos)
    {
        g_st_scanner_record.uc_read_cnt += 1;
        return &g_st_scanner_record;
    }
    else
    {
        return NULL;
    }
}

OAL_STATIC oal_void *dmac_scan_seq_next(struct seq_file *f, void *v, loff_t *pos)
{
    return NULL;
}

OAL_STATIC oal_void dmac_scan_seq_stop(struct seq_file *f, void *v)
{
    /* Nothing to do */
}

OAL_STATIC OAL_CONST struct seq_operations dmac_scan_seq_ops = {
    .start = dmac_scan_seq_start,
    .next  = dmac_scan_seq_next,
    .stop  = dmac_scan_seq_stop,
    .show  = dmac_scan_seq_show
};

OAL_STATIC oal_int32 dmac_scan_seq_open(struct inode *inode, struct file *filp)
{
    return seq_open(filp, &dmac_scan_seq_ops);
}

OAL_STATIC ssize_t dmac_scan_proc_write(struct file *file,
        const char __user *buffer, size_t count, loff_t *ppos)
{
    oal_uint8   auc_buffer[64];
    oal_int8    ac_cmd[128], c_size;
    oal_uint8   uc_bidx = 0;
    oal_uint8   uc_state, uc_tmp, uc_device_id;
    oal_uint32  ul_cnt;
    oal_uint8   uc_band, uc_num, uc_chan_cnt = 0;
    mac_scan_req_stru  st_scan_req;
    mac_device_stru   *pst_mac_device;

    c_size = count;
    if (count > 127)
    {
        c_size = 127;
    }

    if (copy_from_user(ac_cmd, buffer, c_size) != 0)
    {
        return -EFAULT;
    }
    ac_cmd[c_size] = '\0';

    uc_state = 0;
    uc_tmp   = 0;
    OAL_MEMZERO(&st_scan_req, OAL_SIZEOF(st_scan_req));
    g_st_scanner_record.uc_write_cnt += 1;
    for (ul_cnt = 0; ul_cnt < count; ul_cnt++)
    {
        if (0 == uc_state)
        {
            if (' ' == ac_cmd[ul_cnt])
            {
                continue;
            }
            else if ((ac_cmd[ul_cnt] >= '0') && (ac_cmd[ul_cnt] <= '9'))
            {
                uc_state = 1;
                ul_cnt  -= 1;
            }
            else if (('\0' == ac_cmd[ul_cnt]) || ('\n' == ac_cmd[ul_cnt]))
            {
                g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_ALL_OK;
                break;
            }
            else
            {
                g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INVALID_CHAR;
                break;
            }
        }
        else if (1 == uc_state)
        {

            if (' ' == ac_cmd[ul_cnt])
            {
                uc_state = 0;
                auc_buffer[uc_bidx++] = uc_tmp;
                uc_tmp = 0;
            }
            else
            {
                if ((ac_cmd[ul_cnt] >= '0') && (ac_cmd[ul_cnt] <= '9'))
                {
                    uc_tmp = uc_tmp * 10 + ac_cmd[ul_cnt] - '0';
                }
                else if (('\0' == ac_cmd[ul_cnt]) || ('\n' == ac_cmd[ul_cnt]))
                {
                    auc_buffer[uc_bidx++] = uc_tmp;
                    uc_state = 0;
                    g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_ALL_OK;
                    break;
                }
                else
                {
                    g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INVALID_CHAR;
                    uc_state = 0;
                    break;
                }
            }
        }
    }

    if (uc_state)
    {
        auc_buffer[uc_bidx++] = uc_tmp;
    }

#if 1
    OAM_INFO_LOG0(0, OAM_SF_ANY,"%d numbers.\n", uc_bidx);
    for (ul_cnt = 0; ul_cnt < uc_bidx; ul_cnt++)
    {

        OAL_IO_PRINT("..[%d].\n", auc_buffer[ul_cnt]);
    }
#endif

    /* 解析命令 */
    /* 命令格式(以字节为单位) */
    /* scan_mode(1 byte) + scan_type(1 byte) + func_mode(1 byte) + band(1 byte) + channel_num(1byte) + 具体的信道列表(variable) */
    st_scan_req.en_scan_mode = auc_buffer[1];
    st_scan_req.en_scan_type = auc_buffer[2];
    if (auc_buffer[3] & 0xf0)
    {
        g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INVALID_MODE;
        OAM_INFO_LOG1(0, OAM_SF_ANY,"abnormal, auc_buffer[3] is %d\n", auc_buffer[3]);
        goto out;
    }
    st_scan_req.uc_scan_func = auc_buffer[3];
    ul_cnt = 4;
    uc_bidx -= 4;
    while(1)
    {
        if (uc_bidx && (uc_bidx < 2))
        {
            g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INCOMP_CMD;
            OAM_INFO_LOG1(0, OAM_SF_ANY,"abnormal, uc_bidx is %d\n", uc_bidx);
            goto out;
        }

        uc_band = auc_buffer[ul_cnt++];
        uc_num  = auc_buffer[ul_cnt++];
        OAM_INFO_LOG2(0, OAM_SF_ANY,"Add %d channels for band %d.\n", uc_num, uc_band);

        if ((PROC_SCANNER_BAND_2G != uc_band) && (PROC_SCANNER_BAND_5G != uc_band))
        {
            g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INVALID_BAND;
            OAM_INFO_LOG1(0, OAM_SF_ANY,"abnormal, uc_band is %d\n", uc_band);
            goto out;
        }

        if (PROC_SCANNER_BAND_2G == uc_band)
        {
            uc_band = WLAN_BAND_2G;
        }
        else
        {
            uc_band = WLAN_BAND_5G;
        }

        uc_bidx -= 2;
        if (uc_bidx < uc_num)
        {
            g_st_scanner_record.uc_curr_status = PROC_ERROR_TYPE_INCOMP_CMD;
            break;
        }

        /* 提取信道列表 */
        if (uc_num)
        {
            st_scan_req.uc_channel_nums += uc_num;
            uc_tmp = 0;
            while(uc_tmp < uc_num)
            {
                st_scan_req.ast_channel_list[uc_chan_cnt].en_band      = uc_band;
                st_scan_req.ast_channel_list[uc_chan_cnt].en_bandwidth = WLAN_BAND_WIDTH_20M;
                st_scan_req.ast_channel_list[uc_chan_cnt].uc_chan_number = auc_buffer[ul_cnt + uc_tmp];
                mac_get_channel_idx_from_num(uc_band, auc_buffer[ul_cnt + uc_tmp], &st_scan_req.ast_channel_list[uc_chan_cnt].uc_idx);

                uc_tmp++;
                uc_chan_cnt++;
            }

            ul_cnt += uc_num;
        }

        uc_bidx -= uc_num;

        /* 提交扫描请求 */
        if (!uc_bidx)
        {
            oal_uint8  uc_tmp_i;
            for (uc_tmp_i = 0; uc_tmp_i < st_scan_req.uc_channel_nums; uc_tmp_i++)
            {
                OAM_INFO_LOG4(0, OAM_SF_ANY,"[%-6s:%4d]\n",
                st_scan_req.ast_channel_list[uc_tmp_i].en_band == WLAN_BAND_2G?"2.4G":"5G",
                st_scan_req.ast_channel_list[uc_tmp_i].uc_chan_number);
            }

            break;
        }
    }

    st_scan_req.p_fn_cb = dmac_scan_verify_cb;
    uc_device_id   = auc_buffer[0];
    pst_mac_device = mac_res_get_dev(uc_device_id);
    dmac_scan_add_req(pst_mac_device, &st_scan_req);

out:

    return count;
}

void dmac_scan_verify_cb(wlan_scan_event_enum_uint8 en_event, void *pst_scan_event_data)
{
    mac_scan_event_stru *pst_scan_event;
    oal_uint             ul_idx;

    if (OAL_PTR_NULL == pst_scan_event_data)
    {
        return;
    }

    OAM_INFO_LOG0(0, OAM_SF_ANY,"SCAN comp!\n");

    pst_scan_event = (mac_scan_event_stru *)pst_scan_event_data;
    g_st_scanner_record.uc_scan_cb_cnt += 1;

    g_st_scanner_record.uc_nchans = pst_scan_event->uc_nchans;
    for (ul_idx = 0; ul_idx < g_st_scanner_record.uc_nchans; ul_idx++)
    {
        g_st_scanner_record.ast_channel_results[ul_idx] = pst_scan_event->past_channel_results[ul_idx];
    }

    g_st_scanner_record.us_nbss   = pst_scan_event->us_nbss;
    for (ul_idx = 0; ul_idx < g_st_scanner_record.us_nbss; ul_idx++)
    {
        g_st_scanner_record.ast_bss_results[ul_idx] = pst_scan_event->past_bss_results[ul_idx];
    }

    g_st_scanner_record.st_time_cost  = pst_scan_event->st_time_cost;
    g_st_scanner_record.ul_request_id = pst_scan_event->ul_request_id;
    g_st_scanner_record.ul_scan_id    = pst_scan_event->ul_scan_id;
    g_st_scanner_record.uc_scan_func  = pst_scan_event->uc_scan_func;
}

OAL_STATIC OAL_CONST struct file_operations dmac_scan_proc_fops = {
    .open       = dmac_scan_seq_open,
    .read       = seq_read,
    .llseek     = seq_lseek,
    .release    = seq_release,
    .write      = dmac_scan_proc_write,
};

/*****************************************************************************
 函 数 名  : dmac_scan_verify_update
 功能描述  : SCAN验证功能更新统计变量的函数
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
oal_void dmac_scan_verify_update(oal_uint8 uc_scan_func, oal_uint8 uc_band, oal_uint8 uc_scan_type)
{
    oal_uint8   uc_do_stats;
    oal_uint8   uc_do_meas;
    oal_uint8   uc_do_radar_det;
    oal_uint8   uc_do_bss_scan;
    oal_uint8   uc_active;

    uc_do_stats     = uc_scan_func & MAC_SCAN_FUNC_STATS;
    uc_do_meas      = uc_scan_func & MAC_SCAN_FUNC_MEAS;
    uc_do_radar_det = uc_scan_func & MAC_SCAN_FUNC_RADAR;
    uc_do_bss_scan  = uc_scan_func & MAC_SCAN_FUNC_BSS;
    uc_active       = (WLAN_SCAN_TYPE_ACTIVE == uc_scan_type);

    g_st_scanner_record.uc_bcast_probe_cnt += uc_do_bss_scan && uc_active;
    g_st_scanner_record.uc_enable_chan_stats_cnt += uc_do_stats || uc_do_meas;
    g_st_scanner_record.uc_enable_radar_det_cnt += (WLAN_BAND_5G == uc_band) && uc_do_radar_det;
}

/*****************************************************************************
 函 数 名  : dmac_scan_verify_init
 功能描述  : SCAN验证功能初始化函数
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
oal_void  dmac_scan_verify_init(oal_void)
{
#if defined(_PRE_WLAN_CHIP_TEST) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    /* 创建PROC目录 */
    g_pst_scan_proc_entry = SCANNER_CREATE_PROC_ENTRY(SCANNER_VERIFY_PROC_NAME, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, NULL);
    if (OAL_PTR_NULL == g_pst_scan_proc_entry)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN,"dmac_scan_verify: proc entry init failed");
        return;
    }

    g_pst_scan_proc_entry->data  = 0;
    g_pst_scan_proc_entry->nlink = 1;        /* linux创建proc默认值 */
    g_pst_scan_proc_entry->proc_fops  = &dmac_scan_proc_fops;

    OAL_MEMZERO(&g_st_scanner_record, OAL_SIZEOF(g_st_scanner_record));
#endif
}

#endif /*_PRE_WLAN_CHIP_TEST*/
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
