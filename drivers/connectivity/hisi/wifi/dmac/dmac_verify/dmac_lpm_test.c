/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_chip_test.c
  版 本 号   : 初稿
  作    者   : 邹嵘
  生成日期   : 2012年9月18日
  最近修改   :
  功能描述   : 芯片验证的dmac层测试代码、桩函数等
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月18日
    作    者   : z52447
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
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "dmac_ext_if.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_test_main.h"
#include "dmac_lpm_test.h"
#include "dmac_mgmt_ap.h"
#include "dmac_scan.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_LPM_TEST_C

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern oal_uint32  dmac_scan_send_probe_req_frame(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_bssid, oal_int8 *pc_ssid);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : dmac_test_lpm_sleep_timer
 功能描述  : wow睡眠后定时检查GPIO管脚上是否有唤醒信号
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_test_lpm_sleep_timer(oal_void *p_arg)
{

#ifdef _PRE_BOARD_SD5115

         mac_device_stru *pst_device = (mac_device_stru *)p_arg;
         hi_gpio_bit_attr_s          st_attr;
         oal_uint32                  ul_wow_set_bitmap = 0;
         hal_wow_param_stru          st_wow_para;
         dmac_vap_stru               *pst_dmac_vap;
         oal_uint8                   uc_vap_idx;

         /*WOW唤醒GPIO管脚为GPIO 62，对应HI_GPIO_PORT1_E, HI_GPIO_BIT30_E*/
         HI_GPIO_PORT_E              em_port     = HI_GPIO_PORT1_E;
         HI_GPIO_BIT_E               em_bit      = HI_GPIO_BIT30_E;

         /*初始化为低电平*/
         HI_LEVEL_E                  em_level    = HI_LOW_LEVEL_E;

          /*将GPIO管脚设置为INPUT模式*/
         st_attr.em_mode = HI_GPIO_WORK_MODE_INPUT_E;

         hi_kernel_gpio_bit_attr_set(em_port, em_bit, &st_attr);

        /*获取属性*/
         hi_kernel_gpio_bit_attr_get(em_port, em_bit, &st_attr);

         /*读信号*/
         hi_kernel_gpio_bit_read( em_port,  em_bit, &em_level);

         if(HI_HIGH_LEVEL_E == em_level)
         {
            OAM_INFO_LOG0(0, OAM_SF_ANY, "wow wakeup\n");
            ul_wow_set_bitmap = 0;
            for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_release_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_release_null_data(pst_dmac_vap);
            }

            hal_set_wow_en(pst_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(g_st_dmac_test_mng.st_sleep_timer));


         }

#endif

#if (_PRE_TARGET_PRODUCT_TYPE_5610EVB == _PRE_CONFIG_TARGET_PRODUCT)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

        mac_device_stru *pst_device = (mac_device_stru *)p_arg;
        oal_uint32                  ul_wow_set_bitmap = 0;
        hal_wow_param_stru          st_wow_para;
        dmac_vap_stru               *pst_dmac_vap;
        oal_uint8                   uc_vap_idx;
        oal_uint32          ul_val = 0x0;

        /*GPIO 47*/
        /*1.设置成软件模式*/
        ul_val = oal_readl(g_pst_5610_mode + 0x1a4);
        ul_val |= BIT15;
        oal_writel(ul_val, g_pst_5610_mode + 0x1a4);

        /*2.设置数据方向in*/
        ul_val =  oal_readl(g_pst_5610_gpio + 0x4);
        ul_val &= ~BIT15;
        oal_writel(ul_val, g_pst_5610_gpio + 0x4);

        /*读数据寄存器*/
        ul_val =  oal_readl(g_pst_5610_gpio + 0x50);

        if(ul_val&BIT15)
        {

            OAL_IO_PRINT("wow wakeup\n");
            ul_wow_set_bitmap = 0;
            for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
            {

                pst_dmac_vap =  mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
                if (OAL_PTR_NULL == pst_dmac_vap)
                {
                    return OAL_ERR_CODE_PTR_NULL;
                }
                dmac_test_lpm_wow_release_probe_resp(pst_dmac_vap);
                dmac_test_lpm_wow_release_null_data(pst_dmac_vap);
            }

            hal_set_wow_en(pst_device->pst_device_stru,ul_wow_set_bitmap,&st_wow_para);

            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(g_st_dmac_test_mng.st_sleep_timer));
        }
        else
        {
            //OAL_IO_PRINT("GPIO 47 0x10107000 = 0x%x \n",ul_val);
        }
#endif
#endif



    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_create_sleep_timer
 功能描述  : 软件寄存器方式sleep，创建睡眠定时器，根据输入参数设定睡眠时间
 输入参数  : us_sleep_time,毫秒为单位的睡眠时间
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_create_sleep_timer(mac_device_stru *pst_device,oal_uint16 us_sleep_time)
{
    FRW_TIMER_CREATE_TIMER(&(g_st_dmac_test_mng.st_sleep_timer),
                               dmac_test_lpm_sleep_timer,
                               us_sleep_time,
                               pst_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,
                               pst_device->ul_core_id);
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_smps_set_rate
 功能描述  : SMPS测试打桩，根据输入条件，设置发送的11n的速率、RTS使能. 组合起来可以测试SMPS的行为是否正确:
             1. 单流发送，应该可以通
             2. 双流发送，不发RTS，应该不能通
             3. 双流发送，先发RTS，应该可以通
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_smps_set_rate(mac_tx_ctl_stru *pst_tx_ctl, hal_tx_txop_alg_stru *pst_txop_alg,dmac_test_stub_opera_enum_uint8 en_opera)
{
    dmac_lpm_smps_tx_stub_stru          *pst_smps_stub ;
    hal_tx_txop_per_rate_params_union   *past_rate_param;

    pst_smps_stub = &g_st_dmac_test_mng.st_lpm_smps_stub;
    past_rate_param = pst_txop_alg->ast_per_rate;

    if ((0 == pst_smps_stub->uc_stub_type)||(OAL_PTR_NULL == pst_tx_ctl))
    {
        return;
    }

    /*广播或组播包，如果发RTS的话，对端不会回CTS*/
    if(OAL_TRUE == pst_tx_ctl->en_ismcast)
    {
        return;
    }

    /*打桩开始，保存原始数据，打桩数据*/
    if (DMAC_TEST_STUB_BEGIN == en_opera)
    {
        pst_smps_stub->ul_rate_real[0] = pst_txop_alg->ast_per_rate[0].ul_value;
        pst_smps_stub->ul_rate_real[1] = pst_txop_alg->ast_per_rate[1].ul_value;
        pst_smps_stub->ul_rate_real[2] = pst_txop_alg->ast_per_rate[2].ul_value;
        pst_smps_stub->ul_rate_real[3] = pst_txop_alg->ast_per_rate[3].ul_value;

        past_rate_param[0].rate_bit_stru.bit_tx_count = 1;
        past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode = WLAN_HT_PHY_PROTOCOL_MODE;

        /*单流速率发送*/
        if (1 == pst_smps_stub->uc_stub_type)
        {
            /*mcs5,11n为单流*/
            past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 5;
            past_rate_param[0].rate_bit_stru.bit_tx_chain_selection = 0x1;
        }

        /*双流速率发送*/
        if (2 == pst_smps_stub->uc_stub_type)
        {
            /*mcs10,11n为双流*/
            past_rate_param[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 10;

             /* 发送通道选择 (单通道:0x1, 双通道:0x3, 三通道:0x7, 四通道:0xf) */
            past_rate_param[0].rate_bit_stru.bit_tx_chain_selection = 0x3;
        }

        past_rate_param[0].rate_bit_stru.bit_rts_cts_enable = (pst_smps_stub->uc_rts_en)?1:0;
        past_rate_param[1].rate_bit_stru.bit_tx_count = 0;
        past_rate_param[2].rate_bit_stru.bit_tx_count = 0;
        past_rate_param[3].rate_bit_stru.bit_tx_count = 0;
    }
    else
    {
         pst_txop_alg->ast_per_rate[0].ul_value = pst_smps_stub->ul_rate_real[0];
         pst_txop_alg->ast_per_rate[1].ul_value = pst_smps_stub->ul_rate_real[1];
         pst_txop_alg->ast_per_rate[2].ul_value = pst_smps_stub->ul_rate_real[2] ;
         pst_txop_alg->ast_per_rate[3].ul_value = pst_smps_stub->ul_rate_real[3];
    }

    return;

}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_txopps_en
 功能描述  : TXOP PS测试开关,置1时,接收端才会统计接收到得测试报文的个数。开关关闭时，
             计数器清零。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_txopps_en(oal_uint8 uc_en)
{
    g_st_dmac_test_mng.uc_txop_ps_en = uc_en;
    if(0 == uc_en)
    {
        g_st_dmac_test_mng.us_txop_rx_cnt = 0;
    }

}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_txopps_rx_count()
 功能描述  : TXOP PS测试开关置1时,接收端统计接收到的测试报文的个数。简单起见，统计长度大于
             128字节的报文,测试时，要求AP侧发128以上字节的报文。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_txopps_rx_count(oal_uint16 us_pkt_len)
{
    if ((1 == g_st_dmac_test_mng.uc_txop_ps_en)&& (us_pkt_len>=128))
    {
        g_st_dmac_test_mng.us_txop_rx_cnt++;
    }
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_txopps_debug()
 功能描述  : 打印接收端统计接收到的测试报文的个数。简单起见，统计长度大于
             128字节的报文,测试时，要求AP侧发128以上字节的报文。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_txopps_debug(oal_void)
{
   OAM_INFO_LOG1(0, OAM_SF_ANY, "Receive test pkt cnt = %d\n",g_st_dmac_test_mng.us_txop_rx_cnt);
}


/*****************************************************************************
 函 数 名  : dmac_test_lpm_txopps_set_partial_aid
 功能描述  : TXOP PS测试打桩，打桩开始时，对Partial AID打桩；打桩结束时，恢复原来的值
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_txopps_set_partial_aid(dmac_vap_stru         *pst_dmac_vap,
                                                          dmac_user_stru        *pst_dmac_user,
                                                          dmac_test_stub_opera_enum_uint8 en_opera)
{
    dmac_lpm_txopps_tx_stub_stru* pst_txop_stub;

    pst_txop_stub = &g_st_dmac_test_mng.st_lpm_txop_stub;

    /*0:off, 1:on*/
    if (0 == pst_txop_stub->uc_stub_on)
    {
        return;
    }

    /*打桩开始，保存原始数据，打桩数据*/
    if (DMAC_TEST_STUB_BEGIN == en_opera)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_txopps_set_partial_aid::start %d}\r\n",
                            pst_txop_stub->us_curr_num);
        pst_txop_stub->us_curr_num++;
        if (pst_txop_stub->us_begin_num != pst_txop_stub->us_curr_num)
        {
            return;
        }

        /*设置错误的partial aid,STA在收到PAID不是和自身匹配后，进入TXOP节能 */
        pst_txop_stub->us_partial_aid_real =  pst_dmac_user->us_partial_aid;
        pst_dmac_user->us_partial_aid = 123;

     }
     else if (DMAC_TEST_STUB_END == en_opera)
     {
        /*打桩结束，数据恢复*/
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_txopps_set_partial_aid::end}\r\n");
        if (pst_txop_stub->us_begin_num == pst_txop_stub->us_curr_num)
        {
            pst_dmac_user->us_partial_aid = pst_txop_stub->us_partial_aid_real;
        }
     }

     return ;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_send_probe_requst
 功能描述  : 测试命令控制主动发送probe request报文，WOW测试用
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_test_lpm_send_probe_requst(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_positive,oal_uint8* puc_bssid)
{
    oal_int8    ac_ssid[4] = {'\0'};
    oal_uint32  ul_ret;

    /* 被动方式，第三地址为广播地址 */
    if (0 == uc_positive)
    {

        ul_ret = dmac_scan_send_probe_req_frame(pst_dmac_vap, BROADCAST_MACADDR, ac_ssid);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_send_probe_requst::failed to send broadcast probe req! ul_ret=%d}\r\n", ul_ret);
        }
    }
    /* 主动方式，第三地址为指定BSSID */
    else
    {
        ul_ret = dmac_scan_send_probe_req_frame(pst_dmac_vap, puc_bssid, ac_ssid);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_test_lpm_send_probe_requst::failed to send bssid probe req! ul_ret=%d}\r\n", ul_ret);
        }
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_int_proc
 功能描述  : wow主CPU唤醒中断处理函数,测试仅计数,以验证wifi芯片是否发了唤醒信号
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_wow_int_proc(oal_void)
{
    g_st_dmac_test_mng.ul_wow_int_cnt++;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_init
 功能描述  : wow测试初始化，在主CPU中注册唤醒中断处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_wow_init(oal_void)
{
#ifdef _PRE_BOARD_SD5115
    hi_gpio_bit_attr_s          st_attr;

    /*WOW唤醒GPIO管脚为GPIO 62，对应HI_GPIO_PORT1_E, HI_GPIO_BIT30_E*/
    HI_GPIO_PORT_E              em_port     = HI_GPIO_PORT1_E;
    HI_GPIO_BIT_E               em_bit      = HI_GPIO_BIT30_E;

    /*1. 获取属性*/
    hi_kernel_gpio_bit_attr_get(em_port, em_bit, &st_attr);

    /*将GPIO管脚设置为INPUT模式*/
    st_attr.em_mode = HI_GPIO_WORK_MODE_INPUT_E;

    hi_kernel_gpio_bit_attr_set(em_port, em_bit, &st_attr);


#endif
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_set_wow_en
 功能描述  : 设置全局wow使能开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_set_wow_en(oal_uint8 uc_en)
{
     g_st_dmac_test_mng.uc_wow_en = uc_en;

     if(OAL_FALSE == uc_en)
     {
        g_st_dmac_test_mng.ul_wow_int_cnt = 0;
     }

}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_get_wow_en
 功能描述  : 获取全局wow使能开关
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_test_lpm_get_wow_en(oal_void)
{
     return g_st_dmac_test_mng.uc_wow_en ;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_debug
 功能描述  : WOW调试，显示中断次数统计
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_wow_debug(oal_void)
{

#ifdef _PRE_BOARD_SD5115

     hi_gpio_bit_attr_s          st_attr;

     /*WOW唤醒GPIO管脚为GPIO 62，对应HI_GPIO_PORT1_E, HI_GPIO_BIT30_E*/
     HI_GPIO_PORT_E              em_port     = HI_GPIO_PORT1_E;
     HI_GPIO_BIT_E               em_bit      = HI_GPIO_BIT30_E;

     /*初始化为低电平*/
     HI_LEVEL_E                  em_level    = HI_LOW_LEVEL_E;

      /*将GPIO管脚设置为INPUT模式*/
     st_attr.em_mode = HI_GPIO_WORK_MODE_INPUT_E;

     hi_kernel_gpio_bit_attr_set(em_port, em_bit, &st_attr);

    /*获取属性*/
     hi_kernel_gpio_bit_attr_get(em_port, em_bit, &st_attr);

     OAM_INFO_LOG1(0, OAM_SF_ANY, "GPIO_62 attribute = %d\n",st_attr.em_mode);

     /*读信号*/
     hi_kernel_gpio_bit_read( em_port,  em_bit, &em_level);

     if(HI_HIGH_LEVEL_E == em_level)
     {
        g_st_dmac_test_mng.ul_wow_int_cnt++;
     }
     OAM_INFO_LOG1(0, OAM_SF_ANY, "Current wow wakeup int count = %d\n",g_st_dmac_test_mng.ul_wow_int_cnt);

#endif
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_prepare_probe_resp
 功能描述  : wow测试用，准备probe response帧
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_test_lpm_wow_prepare_probe_resp(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8       ast_dest_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};

    if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_probe_resp)
    {
        pst_dmac_vap->pst_wow_probe_resp = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
        if (OAL_PTR_NULL ==  pst_dmac_vap->pst_wow_probe_resp)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_wow_prepare_probe_resp::alloc mgmt buffer failed!}\r\n");
            return OAL_ERR_CODE_PTR_NULL;
        }

        OAL_NETBUF_PREV(pst_dmac_vap->pst_wow_probe_resp) = OAL_PTR_NULL;
        OAL_NETBUF_NEXT(pst_dmac_vap->pst_wow_probe_resp) = OAL_PTR_NULL;
    }

    /* 封装probe response帧 */
    pst_dmac_vap->us_wow_probe_resp_len = dmac_mgmt_encap_probe_response(pst_dmac_vap, pst_dmac_vap->pst_wow_probe_resp, &ast_dest_addr[0], OAL_FALSE);

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_release_probe_resp
 功能描述  : 退出wow模式时，释放为mac准备的probe response帧。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_wow_release_probe_resp(dmac_vap_stru *pst_dmac_vap)
{
    if(OAL_PTR_NULL != pst_dmac_vap->pst_wow_probe_resp)
    {
        oal_netbuf_free(pst_dmac_vap->pst_wow_probe_resp);
        pst_dmac_vap->pst_wow_probe_resp    = OAL_PTR_NULL;
        pst_dmac_vap->us_wow_probe_resp_len = 0;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_prepare_null_data
 功能描述  : WOW测试用，为mac准备空帧。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_test_lpm_wow_prepare_null_data(dmac_vap_stru *pst_dmac_vap)
{
    dmac_user_stru* pst_dmac_user;

    /*仅需要为STA模式的VAP准备null data帧，做keep alive*/
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            return OAL_FAIL;
        }

        if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_null_data)
        {
            /* 申请net_buff */
            pst_dmac_vap->pst_wow_null_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
            if (OAL_PTR_NULL == pst_dmac_vap->pst_wow_null_data)
            {
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_wow_prepare_null_data::alloc pst_net_buf fail!}\r\n");
                return OAL_ERR_CODE_ALLOC_MEM_FAIL;
            }

            OAL_NETBUF_PREV(pst_dmac_vap->pst_wow_null_data) = OAL_PTR_NULL;
            OAL_NETBUF_NEXT(pst_dmac_vap->pst_wow_null_data) = OAL_PTR_NULL;
        }

        /* 填写帧头,其中from ds为1，to ds为0，因此frame control的第二个字节为02 */
        mac_hdr_set_frame_control(oal_netbuf_header(pst_dmac_vap->pst_wow_null_data), (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | 0x0200);

        /* 设置ADDR1为目的地址 */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 4), pst_dmac_user->st_user_base_info.auc_user_mac_addr);

        /* 设置ADDR2为SA */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 10),pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* 设置ADDR3为BSSID */
        oal_set_mac_addr((oal_netbuf_header(pst_dmac_vap->pst_wow_null_data) + 16), pst_dmac_vap->st_vap_base_info.auc_bssid);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_wow_release_null_data
 功能描述  : 释放为MAC准备的null data帧。
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_lpm_wow_release_null_data(dmac_vap_stru *pst_dmac_vap)
{
    if (OAL_PTR_NULL != pst_dmac_vap->pst_wow_null_data)
    {
        oal_netbuf_free(pst_dmac_vap->pst_wow_null_data);
        pst_dmac_vap->pst_wow_null_data = OAL_PTR_NULL;
    }
}

/*****************************************************************************
 函 数 名  : dmac_test_lpm_tx_null_data
 功能描述  : 测试用，主动发送null data帧
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月13日
    作    者   : z52447
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_test_lpm_send_nulldata(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_psm,oal_uint8* puc_da)
{
    oal_netbuf_stru             *pst_null_data;
    mac_tx_ctl_stru             *pst_tx_ctrl;
    oal_uint32                   ul_ret;
    mac_ieee80211_frame_stru    *pst_frame_hdr;
    dmac_user_stru              *pst_dmac_user;
    oal_uint16                   us_user_index;


    /* 申请net_buff */
    pst_null_data = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_null_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata::alloc pst_net_buf fail!}\r\n");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_NETBUF_PREV(pst_null_data) = OAL_PTR_NULL;
    OAL_NETBUF_NEXT(pst_null_data) = OAL_PTR_NULL;

    /* 填写帧头,其中from ds为1，to ds为0，因此frame control的第二个字节为02 */
    mac_hdr_set_frame_control(oal_netbuf_header(pst_null_data), (oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | 0x0200);

    /* 设置ADDR1为目的地址 */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 4), puc_da);

    /* 设置ADDR2为SA */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 10),pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* 设置ADDR3为BSSID */
    oal_set_mac_addr((oal_netbuf_header(pst_null_data) + 16), pst_dmac_vap->st_vap_base_info.auc_bssid);

    pst_frame_hdr = (mac_ieee80211_frame_stru*)oal_netbuf_header(pst_null_data);

    /* 设置节能标记*/
    pst_frame_hdr->st_frame_control.bit_power_mgmt = uc_psm;

    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_null_data);
    OAL_MEMZERO(pst_tx_ctrl, OAL_NETBUF_CB_SIZE());

    /* 填写tx部分 */
    pst_tx_ctrl->en_ack_policy            = WLAN_TX_NORMAL_ACK;
    pst_tx_ctrl->en_event_type            = FRW_EVENT_TYPE_WLAN_DTX;
    pst_tx_ctrl->en_is_bar                = OAL_FALSE;
    pst_tx_ctrl->uc_ac                    = WLAN_WME_AC_BE;
    pst_tx_ctrl->uc_is_first_msdu         = OAL_TRUE;
    pst_tx_ctrl->uc_retried_num           = 0;
    pst_tx_ctrl->uc_tid                   = WLAN_TID_FOR_DATA;
    pst_tx_ctrl->uc_tx_vap_index          = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_tx_ctrl->us_tx_user_idx       = pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id;

        pst_frame_hdr->st_frame_control.bit_from_ds = 0;
        pst_frame_hdr->st_frame_control.bit_to_ds   = 1;
    }
    else
    {
       /* 获取用户对应的索引 */
        ul_ret = mac_vap_find_user_by_macaddr(&pst_dmac_vap->st_vap_base_info,puc_da, &us_user_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata:: not find user!");
            dmac_tx_excp_free_netbuf(pst_null_data);

            return ul_ret;
        }
        pst_dmac_user                     = (dmac_user_stru*)mac_res_get_dmac_user(us_user_index);
        pst_tx_ctrl->us_tx_user_idx       = pst_dmac_user->st_user_base_info.us_assoc_id;

        pst_frame_hdr->st_frame_control.bit_from_ds = 1;
        pst_frame_hdr->st_frame_control.bit_to_ds   = 0;

    }

    /* 填写tx rx公共部分 */
    //pst_tx_ctrl->en_frame_type             = WLAN_DATA_NULL;
    pst_tx_ctrl->en_ismcast                = OAL_FALSE;
    pst_tx_ctrl->en_is_amsdu               = OAL_FALSE;
    pst_tx_ctrl->en_is_get_from_ps_queue   = OAL_TRUE;
    pst_tx_ctrl->en_is_probe_data          = OAL_FALSE;
    pst_tx_ctrl->en_use_4_addr             = OAL_FALSE;
    pst_tx_ctrl->pst_frame_header          = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_null_data);
    pst_tx_ctrl->uc_frame_header_length    = OAL_SIZEOF(mac_ieee80211_frame_stru);
    pst_tx_ctrl->uc_mpdu_num               = 1;
    pst_tx_ctrl->uc_netbuf_num             = 1;
    pst_tx_ctrl->us_mpdu_len               = 0;

    ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_null_data);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_test_lpm_send_nulldata::sending null data fail!}\r\n");
        dmac_tx_excp_free_netbuf(pst_null_data);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_test_always_tx
 功能描述  : 将发送描述符中的NEXT描述符字段指向本身
 输入参数  : pst_tx_dscr:描述符
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月12日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_test_always_tx(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr)
{
    /* 获取设备 */
    if (OAL_SWITCH_ON == pst_hal_device->uc_al_tx_flag)
    {
         hal_rf_test_enable_al_tx(pst_hal_device, pst_tx_dscr);
    }
}
/*****************************************************************************
 函 数 名  : dmac_test_dfx_set_tx_cnt
 功能描述  : 设置重传次数为3
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年3月21日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_test_dfx_set_tx_cnt(hal_tx_txop_alg_stru *pst_txop_alg)
{
    hal_tx_txop_per_rate_params_union   *past_rate_param;

    if (OAL_SWITCH_OFF == g_st_dmac_test_mng.en_cfg_tx_cnt)
    {
        return;
    }

    past_rate_param = pst_txop_alg->ast_per_rate;

    past_rate_param[0].rate_bit_stru.bit_tx_count = 3;
    past_rate_param[1].rate_bit_stru.bit_tx_count = 0;
    past_rate_param[2].rate_bit_stru.bit_tx_count = 0;
    past_rate_param[3].rate_bit_stru.bit_tx_count = 0;
}


#endif /*_PRE_WLAN_CHIP_TEST*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

