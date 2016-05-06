/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_user.c
  版 本 号   : 初稿
  作    者   : huxiaotong
  生成日期   : 2012年10月19日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月19日
    作    者   : huxiaotong
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
#include "oam_ext_if.h"
#include "dmac_user.h"
#include "dmac_11i.h"
#include "dmac_wep.h"
#include "dmac_alg.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_tx_complete.h"
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

#include "dmac_11w.h"
#endif
#include "oam_ext_if.h"
#include "dmac_beacon.h"
#include "dmac_psm_sta.h"
#include "dmac_device.h"
#include "dmac_resource.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_USER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 函 数 名  : dmac_user_track_init
 功能描述  : 单用户跟踪初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_track_init(dmac_user_stru  *pst_dmac_user)
{
    pst_dmac_user->st_txrx_protocol.en_rx_flg = OAL_TRUE;
    pst_dmac_user->st_txrx_protocol.en_tx_flg = OAL_TRUE;

    OAL_MEMZERO(&pst_dmac_user->st_user_track_ctx, OAL_SIZEOF(mac_user_track_ctx_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_check_txrx_protocol_change
 功能描述  : 检查接收或者发送数据帧所使用的协议模式有没有变化，如果变化则上
             报sdt
 输入参数  : pst_dmac_user: dmac user结构
             en_present_mode :接收或者发送当前帧使用的协议模式
             en_type:  表明是tx还是rx
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月23日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_check_txrx_protocol_change(
                                  dmac_user_stru *pst_dmac_user,
                                  oal_uint8      uc_present_mode,
                                  oam_user_info_change_type_enum_uint8  en_type)
{
    mac_user_stru *pst_mac_user = (mac_user_stru *)pst_dmac_user;
    if (OAL_PTR_NULL == pst_mac_user)
    {
        MAC_ERR_LOG(0, "pst_mac_user is null!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch (en_type)
    {
        case OAM_USER_INFO_CHANGE_TYPE_TX_PROTOCOL:
            /* 如果是第一次记录，则直接赋值，不用比较上报 */
            if (OAL_TRUE == pst_dmac_user->st_txrx_protocol.en_tx_flg)
            {
                pst_dmac_user->st_txrx_protocol.uc_tx_protocol = uc_present_mode;
                pst_dmac_user->st_txrx_protocol.en_tx_flg = OAL_FALSE;
            }
            else if (uc_present_mode == pst_dmac_user->st_txrx_protocol.uc_tx_protocol)
            {
                ;
            }
            else
            {
                mac_user_change_info_event(pst_mac_user->auc_user_mac_addr,
                                           pst_mac_user->uc_vap_id,
                                           (oal_uint32)pst_dmac_user->st_txrx_protocol.uc_tx_protocol,
                                           (oal_uint32)uc_present_mode,
                                           OAM_MODULE_ID_DMAC,
                                           en_type);
                pst_dmac_user->st_txrx_protocol.uc_tx_protocol = uc_present_mode;
            }
        break;

        case OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL:
            if (OAL_TRUE == pst_dmac_user->st_txrx_protocol.en_rx_flg)
            {
                pst_dmac_user->st_txrx_protocol.uc_rx_protocol = uc_present_mode;
                pst_dmac_user->st_txrx_protocol.en_rx_flg = OAL_FALSE;
            }
            else if (uc_present_mode == pst_dmac_user->st_txrx_protocol.uc_rx_protocol)
            {
                ;
            }
            else
            {
                mac_user_change_info_event(pst_mac_user->auc_user_mac_addr,
                                           pst_mac_user->uc_vap_id,
                                           (oal_uint32)pst_dmac_user->st_txrx_protocol.uc_rx_protocol,
                                           (oal_uint32)uc_present_mode,
                                           OAM_MODULE_ID_DMAC,
                                           en_type);
                pst_dmac_user->st_txrx_protocol.uc_rx_protocol = uc_present_mode;
            }
        break;

        default:
        break;
    }

    return OAL_SUCC;
}


#endif

/*****************************************************************************
 函 数 名  : dmac_user_init
 功能描述  : 初始化DMAC 用户
 输入参数  : 指向用户的指针
 输出参数  : 失败原因或成功
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : 康国昌53369
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_init(dmac_user_stru *pst_dmac_user)
{
    mac_vap_stru            *pst_mac_vap;

    /* 清空dmac user结构体 */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_user) + OAL_SIZEOF(mac_user_stru), OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru));

    /* 设置dmac user的节能模式 */
    pst_dmac_user->bit_ps_mode     = OAL_FALSE;

    /* RSSI统计量初始化 */
    pst_dmac_user->c_rx_rssi = WLAN_RSSI_DUMMY_MARKER;
    pst_dmac_user->uc_max_key_index = 0;

    /* 初始化时间戳 */
    pst_dmac_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 初始化seq num缓存 */
    OAL_MEMZERO(pst_dmac_user->aus_txseqs, WLAN_TID_MAX_NUM * OAL_SIZEOF(pst_dmac_user->aus_txseqs[0]));
    OAL_MEMZERO(pst_dmac_user->aus_txseqs_frag, WLAN_TID_MAX_NUM * OAL_SIZEOF(pst_dmac_user->aus_txseqs_frag[0]));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    /* 初始化非QOS帧的seq_num 12位全为1 */
    pst_dmac_user->us_non_qos_seq_frag_num = 65535;
#endif
    /* DMAC USER TID 初始化 */
    dmac_tid_tx_queue_init(pst_dmac_user->ast_tx_tid_queue, &(pst_dmac_user->st_user_base_info));

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL  == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_TX, "{dmac_user_init::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 设置mac_user_stru中的gruopid和partial aid两个成员变量,beaforming和txop ps会用到 */
    dmac_user_set_groupid_partial_aid(pst_mac_vap,pst_dmac_user);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* 清除usr统计信息 */
    oam_stats_clear_user_stat_info(pst_dmac_user->st_user_base_info.us_assoc_id);
#endif
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    /* 初始化维测用的信息 */
    dmac_user_track_init(pst_dmac_user);
#endif

    /* 初始化默认不强制关闭RTS */
    pst_dmac_user->bit_forbid_rts = OAL_FALSE;

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : mac_res_get_dmac_user
 功能描述  : 获取对应DMAC USER索引的内存,由HMAC层强转为自己的内存解析
 输入参数  : 对应DMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : chenwenfeng
    修改内容   : 新生成函数

*****************************************************************************/
void*  mac_res_get_dmac_user(oal_uint16 us_idx)
{
    return  mac_res_get_mac_user(us_idx);
}

/*****************************************************************************
 函 数 名  : mac_res_get_dmac_user_alloc
 功能描述  : 获取对应DMAC USER索引的内存,只用于第一次申请user内存时调用
 输入参数  : 对应DMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : lingxuemeng
    修改内容   : 新生成函数

*****************************************************************************/
void*  mac_res_get_dmac_user_alloc(oal_uint16 us_idx)
{
    mac_user_stru*  pst_mac_user;

    pst_mac_user = (mac_user_stru*)_mac_res_get_mac_user(us_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{mac_res_get_dmac_user_alloc::pst_mac_user null,user_idx=%d.}", us_idx);
        return OAL_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 重复申请异常,避免影响业务，暂时打印error但正常申请 */
    if (MAC_USER_ALLOCED == pst_mac_user->uc_is_user_alloced)
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_dmac_user_alloc::[E]user has been alloced,user_idx=%d.}", us_idx);
    }
#endif

    /* mac_user_stru是dmac_user_stru首元素，可强转 */
    return  (void*)pst_mac_user;
}

/*****************************************************************************
 函 数 名  : dmac_user_alloc
 功能描述  : 申请device user id对应的内存
 输入参数  : 对应DMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : lingxuemeng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_user_alloc(oal_uint16 us_user_idx)
{
    oal_uint32        ul_ret = 0;
    dmac_user_stru *  pst_dmac_user;

    /* 申请dmac user */
    ul_ret = mac_res_alloc_dmac_user(us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_user_alloc::dmac_user_alloc failed[%d] userindx[%d].", ul_ret, us_user_idx);
        return ul_ret;
    }

    /* 获取dmac user */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user_alloc(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_user_alloc::pst_dmac_user null, userindx[%d].}", us_user_idx);
        mac_res_free_mac_user(us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 初始清0 */
    OAL_MEMZERO(&(pst_dmac_user->st_user_base_info), OAL_SIZEOF(mac_user_stru));
#endif
    /* 设置alloc标志 */
    pst_dmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_ALLOCED;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_free
 功能描述  : 释放device user id对应的内存
 输入参数  : 对应DMAC USER内存索引
 输出参数  : 无
 返 回 值  : 对应内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : lingxuemeng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_user_free(oal_uint16 us_user_idx)
{
    dmac_user_stru*  pst_dmac_user;
    oal_uint32       ul_ret = 0;

    pst_dmac_user = (dmac_user_stru*)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_user_free::pst_dmac_user null, userindx[%d].}", us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 重复释放异常, 继续释放不返回 */
    if (MAC_USER_FREED == pst_dmac_user->st_user_base_info.uc_is_user_alloced)
    {
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        /*lint -e718*//*lint -e746*/
        OAM_WARNING_LOG2(0, OAM_SF_UM, "{dmac_user_free::[E]user has been freed,user_idx=%d, func[%x].}", us_user_idx, (oal_uint32)__return_address());
        /*lint +e718*//*lint +e746*/
#else
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{dmac_user_free::[E]user has been freed,user_idx=%d.}", us_user_idx);
#endif
    }
#endif

    ul_ret = mac_res_free_mac_user(us_user_idx);
    if(OAL_SUCC == ul_ret)
    {
        /* 清除alloc标志 */
        pst_dmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_FREED;
    }

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_user_add_multi_user
 功能描述  : dmac创建组播用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_multi_user_idx)
{
    dmac_user_stru  *pst_dmac_multi_user;
    oal_uint16       us_user_idx;
    dmac_vap_stru   *pst_dmac_vap;
    oal_uint32       ul_ret;

    us_user_idx = us_multi_user_idx;

    /* 申请dmac user */
    ul_ret = dmac_user_alloc(us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_user_add_multi_user::mac_res_alloc_dmac_user failed[%d], userindex[%d].", ul_ret, us_user_idx);
        return ul_ret;
    }

    pst_dmac_multi_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_multi_user)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_init(&pst_dmac_multi_user->st_user_base_info, us_user_idx, OAL_PTR_NULL, pst_mac_vap->uc_chip_id,  pst_mac_vap->uc_device_id, pst_mac_vap->uc_vap_id);
#endif

    dmac_user_init(pst_dmac_multi_user);

    /* 组播用户都是活跃的 */
    pst_dmac_multi_user->bit_active_user = OAL_TRUE;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    dmac_alg_add_assoc_user_notify(pst_dmac_vap, pst_dmac_multi_user);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        ul_ret = dmac_psm_user_ps_structure_init(pst_dmac_multi_user);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_user_add_multi_user, user index[%d].}", us_user_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_del_multi_user
 功能描述  : 删除用户的调测命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_del_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx)
{
    mac_device_stru                *pst_mac_device;
    dmac_user_stru                 *pst_dmac_user;
    dmac_vap_stru                  *pst_dmac_vap;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_config_del_user::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* dmac user相关操作去注册 */
    dmac_alg_del_assoc_user_notify(pst_dmac_vap, pst_dmac_user);

    /* 删除tid队列中的所有信息 */
    dmac_tid_clear(&(pst_dmac_user->st_user_base_info), pst_mac_device);
    dmac_tid_tx_queue_exit(pst_dmac_user);

    /* 删除用户节能结构 */
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_psm_user_ps_structure_destroy(pst_dmac_user);
    }

    /* 清零user */
    OAL_MEMZERO((oal_uint8 *)pst_dmac_user + OAL_SIZEOF(mac_user_stru), OAL_SIZEOF(dmac_user_stru)- OAL_SIZEOF(mac_user_stru));

    dmac_user_free(us_user_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_get_tid_by_num
 功能描述  : 根据tid num获取dmac user下的tid队列指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : t00231215
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_get_tid_by_num(mac_user_stru *pst_mac_user, oal_uint8 uc_tid_num, dmac_tid_stru **ppst_tid_queue)
{
    dmac_user_stru     *pst_dmac_user;

    if ((OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == ppst_tid_queue))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_user_get_tid_by_num::param null, pst_mac_user=%d, ppst_tid_queue=%d.}",
                       pst_mac_user, ppst_tid_queue);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_tid_by_num::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_num]);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_is_user_in_smartant_training
 功能描述  : 获取当前用户是否在智能天线训练状态
 输入参数  : pst_user: 指向user的指针
 输出参数  : pen_is_training: 返回状态
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_user_get_smartant_training_state(
                mac_user_stru                          *pst_user,
                dmac_user_smartant_training_enum_uint8 *pen_training_state)
{
    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_training_state::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *pen_training_state = pst_dmac_user->en_smartant_training;

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 函 数 名  : dmac_set_user_in_smartant_training
 功能描述  : 设置当前在智能天线训练状态
 输入参数  : pst_user      : 指向用户的指针
             en)is_training: 要设置的状态
 输出参数  : 无
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_set_smartant_training_state(
                mac_user_stru                              *pst_user,
                dmac_user_smartant_training_enum_uint8      en_training_state)
{
    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_training_state::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_smartant_training = en_training_state;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_user_get_smartant_normal_rate_stats
 功能描述  : 读取用户的当前速率统计信息
 输入参数  : pst_mac_user        : 指向用户的指针
 输出参数  : ppst_rate_stats_info: 指向速率统计信息
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_get_smartant_normal_rate_stats(
                mac_user_stru                      *pst_mac_user,
                dmac_tx_normal_rate_stats_stru    **ppst_rate_stats_info)
{

    dmac_user_stru     *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_get_smartant_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *ppst_rate_stats_info = &(pst_dmac_user->st_smartant_rate_stats);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
/*****************************************************************************
 函 数 名  : dmac_user_set_smartant_normal_rate_stats
 功能描述  : 设置用户的当前速率统计信息
 输入参数  : pst_mac_user: 指向用户的指针
 输出参数  : pst_rate_stats_info: 速率统计信息
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_set_smartant_normal_rate_stats(
                mac_user_stru                  *pst_mac_user,
                dmac_tx_normal_rate_stats_stru *pst_rate_stats_info)
{

    dmac_tx_normal_rate_stats_stru *pst_rate_stats;
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{dmac_user_set_smartant_normal_rate_stats::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rate_stats = &(pst_dmac_user->st_smartant_rate_stats);

    pst_rate_stats->ul_best_rate_goodput_kbps = pst_rate_stats_info->ul_best_rate_goodput_kbps;

    pst_rate_stats->ul_rate_kbps        = pst_rate_stats_info->ul_rate_kbps;
    pst_rate_stats->uc_aggr_subfrm_size = pst_rate_stats_info->uc_aggr_subfrm_size;
    pst_rate_stats->uc_per              = pst_rate_stats_info->uc_per;

    return OAL_SUCC;
}
#endif
#if 0
/*****************************************************************************
 函 数 名  : dmac_user_get_txchain_mask
 功能描述  : 获取不同空间流下的TX CHAIN MASK
 输入参数  : pst_user: 指向用户的指针
             en_nss: 空间流枚举
 输出参数  : puc_chainmask: tx chain mask
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_get_txchain_mask(
                mac_user_stru          *pst_user,
                wlan_nss_enum_uint8     en_nss,
                oal_uint8              *puc_chainmask)
{
    dmac_user_stru                 *pst_dmac_user;

    if (en_nss >= WLAN_NSS_BUTT)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_get_txchain_mask::invalid en_nss[%d].", en_nss);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_get_txchain_mask::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_chainmask = pst_dmac_user->auc_txchain_mask[en_nss];

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_set_txchain_mask
 功能描述  : 获取不同空间流下的TX CHAIN MASK
 输入参数  : pst_user: 指向用户的指针
             en_nss: 空间流枚举
 输出参数  : puc_chainmask: tx chain mask
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_set_txchain_mask(
                mac_user_stru          *pst_user,
                wlan_nss_enum_uint8     en_nss,
                oal_uint8               uc_chainmask)
{
    dmac_user_stru                 *pst_dmac_user;

    if (en_nss >= WLAN_NSS_BUTT)
    {
        OAM_ERROR_LOG1(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_set_txchain_mask::invalid en_nss[%d].", en_nss);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_TX_CHAIN, "{dmac_user_set_txchain_mask::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->auc_txchain_mask[en_nss] = uc_chainmask;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_user_get_vip_flag
 功能描述  : 读取用户的VIP属性
 输入参数  : pst_user      : 指向user用户的指针
 输出参数  :
 返 回 值  : true - vip; false - 非vip
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_user_get_vip_flag(mac_user_stru  *pst_user)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_get_vip_flag::pst_dmac_user null.}");

        return OAL_FALSE;
    }

    return pst_dmac_user->en_vip_flag;
}


/*****************************************************************************
 函 数 名  : dmac_user_get_ps_mode
 功能描述  : 读取用户的ps_mode
 输入参数  : pst_user      : 指向user用户的指针
 输出参数  :
 返 回 值  : true - 处于ps_mode;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8  dmac_user_get_ps_mode(mac_user_stru  *pst_user)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_get_ps_mode::pst_dmac_user null.}");

        return OAL_FALSE;
    }

    return (oal_bool_enum_uint8)(pst_dmac_user->bit_ps_mode);
}

/*****************************************************************************
 函 数 名  : dmac_user_get_vip_flag
 功能描述  : 读取用户的VIP属性
 输入参数  : pst_user      : 指向user用户的指针
 输出参数  : pen_vip_flag
 返 回 值  : 错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年2月5日
    作    者   : chenyan
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_set_vip_flag(
                mac_user_stru               *pst_user,
                oal_bool_enum_uint8          en_vip_flag)
{
    dmac_user_stru                 *pst_dmac_user;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_user->us_assoc_id);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_set_vip_flag::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_user->en_vip_flag = en_vip_flag;

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_init_slottime
 功能描述  : 根据用户状态设置slottime类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月27日
    作    者   : y00196452
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_user_init_slottime(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    hal_to_dmac_device_stru    *pst_hal_device;

    hal_get_hal_to_dmac_device(pst_mac_vap->uc_chip_id, pst_mac_vap->uc_device_id, &pst_hal_device);
    if (OAL_PTR_NULL == pst_hal_device)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_user_init_slottime::hal dev null, fail to update slot time, chip[%d],mac_dev[%d].}",
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id);
        return;
    }

    if (WLAN_LEGACY_11B_MODE == pst_mac_user->en_cur_protocol_mode)
    {
        hal_cfg_slottime_type(pst_hal_device, 1);
    }
    else
    {
        hal_cfg_slottime_type(pst_hal_device, 0);
    }
}

/*****************************************************************************
 函 数 名  : dmac_user_inactive
 功能描述  : 设置用户为非活跃
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_inactive(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_mac_vap;
#ifdef  _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_stru       *pst_mac_vap_proxysta;
#endif
    oal_uint32          ul_ret;

    /* 已经是非活跃用户，直接返回 */
    if (OAL_FALSE == pst_dmac_user->bit_active_user)
    {
        return OAL_SUCC;
    }

    //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_inactive::one user will be set inactive, user aid=%d.}",
    //              pst_dmac_user->st_user_base_info.us_assoc_id);

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_inactive::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 归还lut index */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    /* 删除密钥 */
    pst_mac_vap_proxysta = mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_main_proxysta))
        {
        }
        else
        {
            mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
        }
    }
    else
    {
        mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
    }
#else
    mac_user_del_ra_lut_index(pst_mac_device->auc_ra_lut_index_table, pst_dmac_user->uc_lut_index);
#endif

    pst_dmac_user->bit_active_user = OAL_FALSE;

#if 0
    if (pst_mac_device->uc_active_user_cnt)
    {
        pst_mac_device->uc_active_user_cnt--;
    }
#else
    mac_device_dec_active_user(pst_mac_device);
#endif

    /* 删除密钥 */
    pst_mac_vap = mac_res_get_mac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "dmac_user_del::pst_mac_vap==NULL\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = dmac_11i_remove_key_from_user(pst_mac_vap, pst_dmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "dmac_user_del::dmac_11i_remove_key_from_user=%u\r\n",ul_ret);
        return ul_ret;
    }

    /* 将gtk的乒乓指示位清0 注意:此位ap无作用，sta使用*/
    dmac_reset_gtk_token(pst_mac_vap);

    /*从硬件表中删除用户MAC 地址，l00218984 add 2013-10-18*/
    OAM_INFO_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_WPA, "dmac_user_del::lutidx %u, usridx %u\r\n", pst_dmac_user->uc_lut_index, pst_dmac_user->st_user_base_info.us_assoc_id);

    ul_ret = dmac_11i_del_peer_macaddr(pst_mac_vap,pst_dmac_user->uc_lut_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_WPA, "dmac_user_del::dmac_11i_del_peer_macaddr=%u\r\n",ul_ret);
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_active_timer
 功能描述  : 活跃定时器到期处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_user_active_timer(void *p_arg)
{
    mac_device_stru     *pst_mac_device = (mac_device_stru *)p_arg;
    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint32           ul_present_time;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_active_timer::p_arg null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* 遍历device下所有用户，对超过活跃时间的用户作非活跃处理 */
    /* 业务vap从1开始 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_active_timer::pst_mac_vap null.");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 活跃用户管理只针对AP模式，非AP模式则跳出 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
            if (OAL_PTR_NULL == pst_dmac_user_tmp)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{dmac_user_active_timer::pst_dmac_user_tmp null.");
                return OAL_ERR_CODE_PTR_NULL;
            }

            if ((oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_user_tmp->ul_last_active_timestamp, ul_present_time) > WLAN_USER_ACTIVE_TO_INACTIVE_TIME)
            {
                dmac_user_inactive(pst_dmac_user_tmp);
            }
        }
    }

    /* 如果活跃用户小于规格-1，关闭转非活跃定时器 */
    if (pst_mac_device->uc_active_user_cnt < WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->st_active_user_timer));
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_active
 功能描述  : 设置用户为活跃
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_active(dmac_user_stru *pst_dmac_user)
{
    oal_uint8           uc_lut_idx;
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_mac_vap;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_stru       *pst_mac_vap_proxysta;
#endif
    mac_user_stru      *pst_mac_user;

    pst_mac_user = &(pst_dmac_user->st_user_base_info);

    /* 已经是活跃用户，直接返回 */
    if (OAL_TRUE == pst_dmac_user->bit_active_user)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_user->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM.}");
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    pst_mac_vap_proxysta = mac_res_get_mac_vap(pst_mac_user->uc_vap_id);

    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        if ((OAL_TRUE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap_proxysta->st_vap_proxysta.en_is_main_proxysta))
        {
            uc_lut_idx = pst_mac_vap_proxysta->st_vap_proxysta.uc_lut_idx;
        }
        else
        {
            uc_lut_idx = mac_user_get_ra_lut_index_proxysta(pst_mac_device->auc_ra_lut_index_table);
        }
    }
    else
    {
    /* 申请lut index */
    uc_lut_idx = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
    }
#else
    /* 申请lut index */
    uc_lut_idx = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
#endif
    if (uc_lut_idx >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{dmac_user_active::uc_lut_idx >= WLAN_ACTIVE_USER_MAX_NUM.}");
        return OAL_FAIL;
    }
    pst_dmac_user->uc_lut_index = uc_lut_idx;
    pst_dmac_user->bit_active_user   = OAL_TRUE;

#if 0
    pst_mac_device->uc_active_user_cnt++;
#else
    mac_device_inc_active_user(pst_mac_device);
#endif

    /* 设置hal lut index */
    hal_machw_seq_num_index_update_per_tid(pst_mac_device->pst_device_stru, uc_lut_idx, OAL_TRUE);

    /* 如果活跃用户达到规格-1，启动转非活跃机制 */
    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        if (OAL_FALSE == pst_mac_device->st_active_user_timer.en_is_registerd)
        {
            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_active_user_timer,
                                   dmac_user_active_timer,
                                   WLAN_USER_ACTIVE_TRIGGER_TIME,               /* 1000ms触发一次 */
                                   pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }

    /* 设置密钥 */
    pst_mac_vap = mac_res_get_mac_vap(pst_mac_user->uc_vap_id);
    return dmac_11i_add_key_from_user(pst_mac_vap, pst_dmac_user);

}

/*****************************************************************************
 函 数 名  : dmac_psm_tid_mpdu_num
 功能描述  : 判断某一个用户的所有tid是否都为空，只要有一个tid不为空就返回false
 输入参数  : 无
 输出参数  : 无
 返 回 值  : true:所有tid都为空   false:有tid不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月29日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_tid_mpdu_num(dmac_user_stru  *pst_dmac_user)
{
    oal_uint8                     uc_tid_idx         = 0;
    oal_uint32                    ul_tid_mpdu_num    = 0;

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        ul_tid_mpdu_num += pst_dmac_user->ast_tx_tid_queue[uc_tid_idx].us_mpdu_num;
    }

    return ul_tid_mpdu_num;
}

/*****************************************************************************
 函 数 名  : dmac_psm_is_psm_empty
 功能描述  : 判断某一个用户的psm是否都为空
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月17日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_psm_is_psm_empty(dmac_user_stru *pst_dmac_user)
{
    return (0 == oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num));
}

/*****************************************************************************
 函 数 名  : dmac_psm_is_uapsd_empty
 功能描述  : 判断某一个用户的uspsd队列是否都为空，如果非空就返回false
 输入参数  : 无
 输出参数  : 无
 返 回 值  : true:uapsd 为空   false:uapsd 不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : duankaiyong 00194999
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_psm_is_uapsd_empty(dmac_user_stru  *pst_dmac_user)
{
    return (0 == oal_atomic_read(&pst_dmac_user->st_uapsd_stru.uc_mpdu_num));
}

/*****************************************************************************
 函 数 名  : dmac_psm_is_tid_empty
 功能描述  : 判断某一个用户的所有tid是否都为空，只要有一个tid不为空就返回false
 输入参数  : 无
 输出参数  : 无
 返 回 值  : true:所有tid都为空   false:有tid不为空
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月23日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_bool_enum_uint8 dmac_psm_is_tid_empty(dmac_user_stru  *pst_dmac_user)
{
    return (0 == dmac_psm_tid_mpdu_num(pst_dmac_user));
}

/*****************************************************************************
 函 数 名  : dmac_send_null_frame_to_sta
 功能描述  : keepalive超时发送null帧函数
 输入参数  : pst_mac_vap:  指向VAP的指针
             pst_mac_user: 指向用户的指针
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月29日
    作    者   : w00269675
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_send_null_frame_to_sta(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    dmac_vap_stru             *pst_dmac_vap;
    dmac_user_stru            *pst_dmac_user;
#ifdef _PRE_WLAN_FEATURE_UAPSD
    oal_uint8                  uc_ac          =  WLAN_WME_AC_VO;
    oal_uint8                  uc_uapsd_flag  =  OAL_FALSE;
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
	oal_int8                   c_i;
#endif

    /* 获取vap结构信息 */
    pst_dmac_vap  = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta::pst_dmac_vap null.}");
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    /* 获取user结构信息 */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_mac_user->us_assoc_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta::pst_dmac_user null. user idx = [%d]}",
                               pst_mac_user->us_assoc_id);
        return OAL_ERR_CODE_KEEPALIVE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_AP ==  pst_mac_vap->en_vap_mode)
    {
    #ifdef _PRE_WLAN_FEATURE_UAPSD
        /* AP侧根据user节能状态下选择发null帧还是Qos null帧 */
        uc_uapsd_flag = pst_dmac_user->uc_uapsd_flag;

        if (OAL_FALSE != (uc_uapsd_flag & MAC_USR_UAPSD_EN))
        {
            for(c_i = MAC_AC_PARAM_LEN - 1; c_i >= 0; c_i--)
            {
                if (OAL_TRUE == pst_dmac_user->st_uapsd_status.uc_ac_trigger_ena[c_i])
                {
                    uc_ac = (oal_uint8)c_i;
                    break;
                }
            }
            return dmac_send_qosnull(pst_dmac_vap, pst_dmac_user, uc_ac, OAL_FALSE);
        }
    #endif
        /* 用户处于非节能状态 */
        return dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_send_null_frame_to_sta:: vap mode %d is wrong.}", pst_dmac_vap->st_vap_base_info.en_vap_mode);
    }

    return OAL_FAIL;

}

/*****************************************************************************
 函 数 名  : dmac_user_keepalive_timer
 功能描述  : 用户keepalive定时器到期处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月30日
    作    者   : w00269675
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_keepalive_timer(void *p_arg)
{
    mac_device_stru     *pst_mac_device;
    oal_uint8            uc_vap_idx;
    mac_vap_stru        *pst_mac_vap;
    oal_dlist_head_stru *pst_entry;
    oal_dlist_head_stru *pst_user_list_head;
    mac_user_stru       *pst_user_tmp;
    dmac_user_stru      *pst_dmac_user_tmp;
    oal_uint32           ul_runtime;
    oal_uint32           ul_present_time;
    oal_uint32           ul_list_count = 0;
    oal_uint32           ul_aging_time;
    oal_uint32           ul_send_null_frame_time;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_btcoex_btble_status_stru *pst_btcoex_btble_status;
#endif

    if (OAL_PTR_NULL == p_arg)
    {
        OAM_ERROR_LOG0(0, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = (mac_device_stru *)p_arg;

    ul_present_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();


    /* 遍历device下的所有用户，将到期老化的删除掉 */
    /* 业务vap从1开始 */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::pst_mac_vap null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* 用户老化只针对AP模式，非AP模式则跳出 或没有keepalive能力则跳出 */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        /* 如果keepalive 开关已关, 此时定时器还是开启的话就关闭定时器 */
        if (OAL_FALSE ==  pst_mac_vap->st_cap_flag.bit_keepalive)
        {
            if (OAL_TRUE == pst_mac_device->st_keepalive_timer.en_is_registerd)
            {
               FRW_TIMER_DESTROY_TIMER(&(pst_mac_device->st_keepalive_timer));
            }
            continue;
        }


        ul_aging_time           = WLAN_AP_USER_AGING_TIME;
        ul_send_null_frame_time = WLAN_AP_KEEPALIVE_INTERVAL;

#ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_GO(pst_mac_vap))
        {
            ul_aging_time           = WLAN_P2PGO_USER_AGING_TIME;
#ifdef _PRE_WLAN_FEATURE_BTCOEX
            pst_btcoex_btble_status = &(pst_mac_device->pst_device_stru->st_btcoex_btble_status);
            if(pst_btcoex_btble_status->un_ble_status.st_ble_status.bit_bt_ba)
            {
                ul_aging_time           = 2*WLAN_P2PGO_USER_AGING_TIME;
            }
#endif
            ul_send_null_frame_time = WLAN_GO_KEEPALIVE_INTERVAL;
        }
#endif

        pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);

        for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
        {
            pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            pst_dmac_user_tmp = mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);

            /* 指向双向链表下一个节点 */
            pst_entry = pst_entry->pst_next;

            if (OAL_PTR_NULL == pst_dmac_user_tmp)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "pst_dmac_user_tmp is null. us_assoc_id is %d", pst_user_tmp->us_assoc_id);
                return OAL_ERR_CODE_PTR_NULL;
            }

            ul_runtime = (oal_uint32)OAL_TIME_GET_RUNTIME(pst_dmac_user_tmp->ul_last_active_timestamp, ul_present_time);

            if (ul_runtime > ul_aging_time)
            {
                dmac_send_disasoc_misc_event(pst_mac_vap,pst_user_tmp->us_assoc_id, DMAC_DISASOC_MISC_KEEPALIVE);
            }
            else if(ul_runtime > ul_send_null_frame_time)
            {
                /* 发送队列与节能队列无数据缓冲，发送null 帧触发keepalive ; 否则不发送null 帧 */
                if ((OAL_TRUE == dmac_psm_is_psm_empty(pst_dmac_user_tmp))
                    && (OAL_TRUE == dmac_psm_is_tid_empty(pst_dmac_user_tmp))
                    && (OAL_TRUE == dmac_psm_is_uapsd_empty(pst_dmac_user_tmp)))
                {
                    dmac_send_null_frame_to_sta(pst_mac_vap, pst_user_tmp);
                    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::send null frame to %02X:XX:XX:%02X:%02X:%02X.}",
                            pst_user_tmp->auc_user_mac_addr[0],
                            pst_user_tmp->auc_user_mac_addr[3],
                            pst_user_tmp->auc_user_mac_addr[4],
                            pst_user_tmp->auc_user_mac_addr[5]);
                }
                else
                {
                    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer::tx queue have buffered data.do not send null frame to %02X:XX:XX:%02X:%02X:%02X.}",
                            pst_user_tmp->auc_user_mac_addr[0],
                            pst_user_tmp->auc_user_mac_addr[3],
                            pst_user_tmp->auc_user_mac_addr[4],
                            pst_user_tmp->auc_user_mac_addr[5]);
                }

            }

            if(ul_list_count++ > WLAN_ACTIVE_USER_MAX_NUM)
            {
#ifdef _PRE_WLAN_DFT_STAT
                OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_KEEPALIVE, "{dmac_user_keepalive_timer:st_mac_user_list_head ul_hash_cnt = %d ul_dlist_cnt = %d.}",pst_mac_vap->ul_hash_cnt,pst_mac_vap->ul_dlist_cnt);
#endif
                break;
            }
        }
    }

    return OAL_SUCC;
}

oal_uint32 dmac_alg_distance_notify_hook(mac_user_stru *pst_user, dmac_alg_distance_notify_info_stru *pst_distance_info)
{
    dmac_device_stru        *pst_dmac_device;
    dmac_alg_stat_stru      *pst_dmac_alg_stat;

    pst_dmac_device   = dmac_res_get_mac_dev(pst_user->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_alg_distance_notify_hook:: pst_dmac_device null. device_id[%d]}", pst_user->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_alg_stat = &pst_dmac_device->st_dmac_alg_stat;

    if(pst_dmac_alg_stat->en_dmac_device_distance_enum != pst_distance_info->en_old_distance)
    {
        OAM_INFO_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_alg_distance_notify_hook::alg distance status is out of the way1.old:%d, new:%d}",
                        pst_distance_info->en_old_distance, pst_distance_info->en_new_distance);
    }

    if(pst_distance_info->en_new_distance > DMAC_ALG_TPC_BUTT_DISTANCE)
    {
        OAM_WARNING_LOG2(pst_user->uc_vap_id, OAM_SF_ANY, "{dmac_alg_distance_notify_hook::alg distance status is out of the way2.old:%d, new:%d}",
                        pst_distance_info->en_old_distance, pst_distance_info->en_new_distance);
    }

    pst_dmac_alg_stat->en_dmac_device_distance_enum = pst_distance_info->en_new_distance;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    /* PHY算法频偏问题规避,近场时提升1*1improve门限至22,远场恢复门限至16 */
    if(DMAC_ALG_TPC_NEAR_DISTANCE == pst_dmac_alg_stat->en_dmac_device_distance_enum)
    {
        hal_set_improve_ce_threshold(pst_dmac_device->pst_device_base_info->pst_device_stru, 22);
    }
    else
    {
        hal_set_improve_ce_threshold(pst_dmac_device->pst_device_base_info->pst_device_stru, 16);
    }
#endif
    return OAL_SUCC;
}

oal_uint32 dmac_alg_co_intf_notify_hook(mac_device_stru *pst_device, oal_bool_enum_uint8 en_intf_state_cur, oal_bool_enum_uint8 en_intf_state_old)
{
    dmac_device_stru        *pst_dmac_device;
    dmac_alg_stat_stru      *pst_dmac_alg_stat;

    pst_dmac_device   = dmac_res_get_mac_dev(pst_device->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_alg_co_intf_notify_hook:: pst_dmac_device null. device_id[%d]}", pst_device->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_alg_stat = &pst_dmac_device->st_dmac_alg_stat;

    if(pst_dmac_alg_stat->en_co_intf_state != en_intf_state_old)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_alg_co_intf_notify_hook::alg co_intf status is out of the way.old:%d, new:%d}",
                        en_intf_state_old, en_intf_state_cur);
    }

    pst_dmac_alg_stat->en_co_intf_state = en_intf_state_cur;

    return OAL_SUCC;
}

oal_uint32 dmac_alg_cca_intf_notify_hook(mac_device_stru *pst_device, oal_uint8 uc_intf_mode_old,
                oal_uint8 uc_intf_mode_new, oal_int8 c_cca_opt_avg_rssi_20, oal_int8 c_cca_opt_avg_rssi_40, oal_int8 c_cca_opt_avg_rssi_80)
{
    dmac_device_stru        *pst_dmac_device;
    dmac_alg_stat_stru      *pst_dmac_alg_stat;

    pst_dmac_device   = dmac_res_get_mac_dev(pst_device->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_alg_cca_intf_notify_hook:: pst_dmac_device null. device_id[%d]}", pst_device->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_alg_stat = &pst_dmac_device->st_dmac_alg_stat;

    if(pst_dmac_alg_stat->en_cca_intf_state != uc_intf_mode_old)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_alg_co_intf_notify_hook::alg cca_intf status is out of the way.old:%d, new:%d}",
                        uc_intf_mode_old, uc_intf_mode_new);
    }

    pst_dmac_alg_stat->en_cca_intf_state = uc_intf_mode_new;

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
oal_void dmac_rx_compatibility_show_stat(dmac_user_stru *pst_dmac_user)
{
    dmac_device_stru        *pst_dmac_device;

    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_rx_compatibility_show_stat:: pst_dmac_device null, user maybe deleted. device_id[%d]}",
                                 pst_dmac_user->st_user_base_info.uc_device_id);
        return;
    }
    OAM_WARNING_LOG3(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_rx_compatibility_show_stat::%d(0:normal,1:compatibity),txopenb:%d,tx_ba_num:%d.}",
                    pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_stat,
                    pst_dmac_device->pst_device_base_info->en_txop_enable,
                    pst_dmac_device->pst_device_base_info->uc_tx_ba_num);
    OAM_WARNING_LOG3(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_rx_show_alg_stat::distance:%d,cca_intr:%d,co_intr:%d.}",
                    pst_dmac_device->st_dmac_alg_stat.en_dmac_device_distance_enum,
                    pst_dmac_device->st_dmac_alg_stat.en_cca_intf_state,
                    pst_dmac_device->st_dmac_alg_stat.en_co_intf_state);

    return;
}

oal_void dmac_rx_compatibility_identify(dmac_user_stru *pst_dmac_user, oal_uint32 ul_rate_kbps)
{
    oal_uint32                          ul_rate_kbps_average;
    dmac_device_stru                   *pst_dmac_device;
    dmac_compatibility_stat_stru       *pst_dmac_compatibility_stat;
    dmac_alg_stat_stru                 *pst_dmac_alg_stat;
    wlan_protocol_enum_uint8            en_protocol_mode;
    wlan_bw_cap_enum_uint8              en_bandwidth;

    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_rx_compatibility_identify:: pst_dmac_device null. device_id[%d]}",
                                 pst_dmac_user->st_user_base_info.uc_device_id);
        return;
    }
    pst_dmac_compatibility_stat = &pst_dmac_device->st_dmac_compatibility_stat;

    if(OAL_FALSE == pst_dmac_compatibility_stat->en_compatibility_enable)
    {
        return;
    }
    if(OAL_TRUE == pst_dmac_compatibility_stat->en_compatibility_stat)
    {
        return;
    }

    pst_dmac_alg_stat           = &pst_dmac_device->st_dmac_alg_stat;

    if(DMAC_ALG_TPC_NEAR_DISTANCE != pst_dmac_alg_stat->en_dmac_device_distance_enum ||
       DMAC_ALG_CCA_OPT_NO_INTF != pst_dmac_alg_stat->en_cca_intf_state ||
       OAL_FALSE != pst_dmac_alg_stat->en_co_intf_state)
    {
        pst_dmac_compatibility_stat->ul_rx_rate = 0;
        pst_dmac_compatibility_stat->us_rx_rate_stat_count = 0;
        return;
    }

    if (0 != ul_rate_kbps)
    {
        pst_dmac_compatibility_stat->ul_rx_rate += ul_rate_kbps;
        pst_dmac_compatibility_stat->us_rx_rate_stat_count++;
    }

    if(DMAC_COMPATIBILITY_PKT_NUM_LIMIT != pst_dmac_compatibility_stat->us_rx_rate_stat_count)
    {
        return;
    }

    ul_rate_kbps_average = pst_dmac_compatibility_stat->ul_rx_rate/pst_dmac_compatibility_stat->us_rx_rate_stat_count;

    en_protocol_mode = pst_dmac_user->st_user_base_info.en_cur_protocol_mode;
    en_bandwidth     = pst_dmac_user->st_user_base_info.en_cur_bandwidth;

    if(ul_rate_kbps_average < pst_dmac_compatibility_stat->aul_compatibility_rate_limit[en_bandwidth][en_protocol_mode])
    {
        hal_set_acc_symb_num(pst_dmac_device->pst_device_base_info->pst_device_stru, 1);
        pst_dmac_compatibility_stat->en_compatibility_stat = OAL_TRUE;
        OAM_WARNING_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_rx_compatibility_identify::compability status change to %d. (0:normal;1:compatibity mode)}",
                    pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_stat);
        OAM_WARNING_LOG3(0, OAM_SF_ANY, "{dmac_rx_compatibility_identify:average rx rate:%ukbp/s, protocol:%u, bandwidth:%u.}",
                  ul_rate_kbps_average, en_protocol_mode, en_bandwidth);
    }

    pst_dmac_compatibility_stat->ul_rx_rate = 0;
    pst_dmac_compatibility_stat->us_rx_rate_stat_count = 0;

    return;
}

/*****************************************************************************
 函 数 名  : dmac_compatibility_handler
 功能描述  : 兼容性问题特殊配置处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月7日
    作    者   : s00304087
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_void dmac_compatibility_handler(dmac_vap_stru *pst_dmac_vap, mac_ap_type_enum_uint8 en_ap_type, oal_bool_enum_uint8 en_is_add_user)
{
    dmac_device_stru *pst_dmac_device;

    pst_dmac_device = dmac_res_get_mac_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_compatibility_handler:: pst_dmac_device null. device_id[%d]}",
                                 pst_dmac_vap->st_vap_base_info.uc_device_id);
        return;
    }

    if(en_is_add_user)
    {
        switch (en_ap_type)
        {
            case MAC_AP_TYPE_GOLDENAP:
                hal_enable_sigB(pst_dmac_vap->pst_hal_device, OAL_TRUE);
                hal_enable_improve_ce(pst_dmac_vap->pst_hal_device, OAL_FALSE);
                break;
            case MAC_AP_TYPE_NORMAL:
                pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_enable = OAL_TRUE;
                break;
            default:
                break;
        }
    }
    else
    {
        switch (en_ap_type)
        {
            case MAC_AP_TYPE_GOLDENAP:
                hal_enable_sigB(pst_dmac_vap->pst_hal_device, OAL_FALSE);
                hal_enable_improve_ce(pst_dmac_vap->pst_hal_device, OAL_TRUE);
                break;
            case MAC_AP_TYPE_NORMAL:
                hal_set_acc_symb_num(pst_dmac_vap->pst_hal_device, 3);
                hal_set_improve_ce_threshold(pst_dmac_vap->pst_hal_device, 16);
                pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_enable = OAL_FALSE;
                pst_dmac_device->st_dmac_compatibility_stat.en_compatibility_stat   = OAL_FALSE;
                break;
            default:
                break;
        }
    }

    return;
}
#endif
/*****************************************************************************
 函 数 名  : dmac_user_add
 功能描述  : DMAC用户添加用户同步操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月6日
    作    者   : huxiaotong
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_add(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16                      us_user_idx;
    dmac_user_stru                 *pst_dmac_user;
    frw_event_stru                 *pst_event;
    dmac_ctx_add_user_stru         *pst_add_user_payload;
    oal_uint32                      ul_ret;
    oal_uint8                       uc_lut_index;
    mac_device_stru                *pst_mac_device;
    oal_uint16                      us_max_asoc_user;
    mac_vap_stru                    *pst_mac_vap;
    dmac_vap_stru                   *pst_dmac_vap;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_event_mem)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_add::pst_event_mem null.}");
        return OAL_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    us_user_idx          = pst_add_user_payload->us_user_idx;
    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 申请dmac user */
    ul_ret = dmac_user_alloc(us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(pst_event->st_event_hdr.uc_vap_id, OAM_SF_ANY, "{dmac_user_add::mac_res_alloc_dmac_user failed[%d], userindx[%d].", ul_ret, us_user_idx);
        return ul_ret;
    }

    pst_dmac_vap = mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_user_add::null pointer,pst_dmac_vap[%d].}",
                    pst_event->st_event_hdr.uc_vap_id);
        dmac_user_free(us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = &pst_dmac_vap->st_vap_base_info;
    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{dmac_user_add::null pointer,pst_dmac_user[%d].}",
                    us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }



    /* mac user初始化 */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_user_init(&(pst_dmac_user->st_user_base_info), us_user_idx, pst_add_user_payload->auc_user_mac_addr,
                  pst_event->st_event_hdr.uc_chip_id,
                  pst_event->st_event_hdr.uc_device_id,
                  pst_event->st_event_hdr.uc_vap_id);

    ul_ret = mac_vap_add_assoc_user(pst_mac_vap, us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        dmac_user_free(us_user_idx);
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_add::mac_vap_add_assoc_user fail.}");
        return OAL_FAIL;
    }

    pst_mac_device->uc_asoc_user_cnt++;

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_mac_vap, (oal_uint8)us_user_idx);

        /* 关联前向平台注册,保证入网过程中work票不睡眠 */
        hal_pm_wlan_servid_register(pst_dmac_vap->pst_hal_vap, &ul_ret);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
             "{dmac_user_add:hal_pm_wlan_servid_register hal vap:[%d]fail",pst_dmac_vap->pst_hal_vap->uc_vap_id);

        }

        /* staut注册后立刻开前端 */
        dmac_pm_enable_front_end(pst_mac_device,OAL_TRUE);
    }

    /* 重新关联用户的时候，重置乒乓位 */
    dmac_reset_gtk_token(pst_mac_vap);
#endif

    /* dmac user初始化 */
    dmac_user_init(pst_dmac_user);

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        ul_ret = dmac_psm_user_ps_structure_init(pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            dmac_user_free(us_user_idx);
            return ul_ret;
        }
    }
    /* 初始化linkloss的状态 */
    dmac_vap_linkloss_clean(pst_dmac_vap);

    /* 启用keepalive定时器, 若定时器已开启, 则不用再开启 */
    if ((OAL_FALSE == pst_mac_device->st_keepalive_timer.en_is_registerd) &&
        (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_keepalive))
    {
        FRW_TIMER_CREATE_TIMER(&(pst_mac_device->st_keepalive_timer),
                               dmac_user_keepalive_timer,
                               WLAN_AP_KEEPALIVE_TRIGGER_TIME,                /* 30s触发一次(1101中60s触发一次) TBD:参数待定 */
                               pst_mac_device,
                               OAL_TRUE,
                               OAM_MODULE_ID_DMAC,
                               pst_mac_device->ul_core_id);
    }

#ifdef _PRE_WLAN_FEATURE_UAPSD
    ul_ret = dmac_uapsd_user_init(pst_dmac_user);
    if(OAL_SUCC!= ul_ret)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::dmac_uapsd_user_init failed.}");
        dmac_user_free(us_user_idx);
        return ul_ret;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PM
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        dmac_pm_post_event(pst_dmac_vap,AP_PWR_EVENT_USR_ASSOC,0,OAL_PTR_NULL);
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
    {
        /* 申请lut index,如果启动Proxy STA，则为ap0的user为0~15,proxysta为16~31,如果不启用，user则为0~31 */
        if ((OAL_TRUE == pst_mac_vap->st_vap_proxysta.en_is_proxysta) &&(OAL_FALSE == pst_mac_vap->st_vap_proxysta.en_is_main_proxysta))
        {
            uc_lut_index = pst_mac_vap->st_vap_proxysta.uc_lut_idx;
        }
        else
        {
            uc_lut_index = mac_user_get_ra_lut_index_proxysta(pst_mac_device->auc_ra_lut_index_table);
        }
    }
    else
    {
        /* 申请lut index */
        uc_lut_index = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
    }
#else
    /* 申请lut index */
    uc_lut_index = mac_user_get_ra_lut_index(pst_mac_device->auc_ra_lut_index_table);
#endif
    if (uc_lut_index >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::add failed,uc_lut_index=%d,us_user_idx=%d.}",
                            uc_lut_index, us_user_idx);

        /* 异常释放内存 */
        dmac_user_free(us_user_idx);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    //OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::uc_lut_index=%d.}", uc_lut_index);

    /* 活跃用户数+1 */
    pst_mac_device->uc_active_user_cnt++;
    pst_dmac_user->bit_active_user = OAL_TRUE;
    pst_dmac_user->uc_lut_index    = uc_lut_index;


    /* 清零芯片维护的序列号 */
    hal_set_tx_sequence_num(pst_mac_device->pst_device_stru, uc_lut_index, 0, 0, 0);

    /* 如果活跃用户达到规格-1，启动转非活跃机制 */
    us_max_asoc_user = mac_res_get_max_asoc_user();
    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM - 1)
    {
        if (us_max_asoc_user <= WLAN_ACTIVE_USER_MAX_NUM)
        {
            /* 最大关联用户小于32，不开启转非活跃 */
            /* do nothing */
        }
        else if (OAL_FALSE == pst_mac_device->st_active_user_timer.en_is_registerd)
        {
            /* 如果定时器没被使能，说明定时器没被创建，创建定时器 */

            //OAM_INFO_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_add::start active user timer.}\r\n");

            FRW_TIMER_CREATE_TIMER(&pst_mac_device->st_active_user_timer,
                                   dmac_user_active_timer,
                                   WLAN_USER_ACTIVE_TRIGGER_TIME,               /* 1000ms触发一次 */
                                   pst_mac_device,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }

#ifdef _PRE_WLAN_FEATURE_ROAM
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        dmac_sta_roam_trigger_init((dmac_vap_stru *)pst_mac_vap);
    }
#endif //_PRE_WLAN_FEATURE_ROAM
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    dmac_compatibility_handler(pst_dmac_vap, pst_add_user_payload->en_ap_type, OAL_TRUE);
    OAM_WARNING_LOG_ALTER(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                 "{dmac_user_add::add user[%d] SUCC! vap user nums[%d],device user nums[%d], user mac_addr:%02x:xx:xx:xx:%02x:%02x.}",
                 6 ,us_user_idx, pst_mac_vap->us_user_nums, pst_mac_device->uc_asoc_user_cnt,
                 pst_add_user_payload->auc_user_mac_addr[0],
                 pst_add_user_payload->auc_user_mac_addr[4],
                 pst_add_user_payload->auc_user_mac_addr[5]);
#else
    OAM_WARNING_LOG4(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                 "{dmac_user_add::add user[%d] SUCC! vap user nums[%d],device user nums[%d], user mac_addr:xx:xx:xx:xx:xx:%02x.}",
                 us_user_idx, pst_mac_vap->us_user_nums, pst_mac_device->uc_asoc_user_cnt, pst_add_user_payload->auc_user_mac_addr[5]);

#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hal_set_btcoex_soc_gpreg1(OAL_TRUE, BIT2, 2);   // 入网流程开始
#endif

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_full_phy_freq_user_add
 功能描述  : 在DMAC OFFLOAD模式下,phy降频处理
 输入参数  : mac_vap_stru *pst_mac_vap,dmac_user_stru *pst_dmac_user
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月5日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_full_phy_freq_user_add(mac_vap_stru *pst_mac_vap,dmac_user_stru *pst_dmac_user)
{
    mac_device_stru         *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_full_phy_freq_user_add::pst_mac_device[%d] null!}", pst_mac_vap->uc_device_id);
        return;
    }

    /* 支持vht ht uc_full_phy_freq_user_cnt++ */
    if (OAL_TRUE == DMAC_GET_USER_SUPPORT_VHT(&(pst_dmac_user->st_user_base_info)) ||
          (OAL_TRUE == DMAC_GET_USER_SUPPORT_HT(&(pst_dmac_user->st_user_base_info))))
    {
        pst_mac_device->pst_device_stru->uc_full_phy_freq_user_cnt++;
    }

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"dmac_full_phy_freq_user_add::remain[%d]user",pst_mac_device->pst_device_stru->uc_full_phy_freq_user_cnt);

    /*phy 降频处理 */
    hal_process_phy_freq(pst_mac_device->pst_device_stru);
}
#endif

/*****************************************************************************
 函 数 名  : dmac_user_add_notify_alg
 功能描述  : 通知算法增加user
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月25日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_add_notify_alg(frw_event_mem_stru *pst_event_mem)
{
    oal_uint32               ul_ret;
    dmac_vap_stru           *pst_dmac_vap;
    frw_event_stru          *pst_event;
    dmac_user_stru          *pst_dmac_user;
    dmac_ctx_add_user_stru  *pst_add_user_payload;

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* 通知算法 */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_add_notify_alg::mac_res_get_dmac_vap failed.vap_idx:[%u].", pst_event->st_event_hdr.uc_vap_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    //oal_memcmp(pst_dmac_vap->st_vap_base_info.auc_bssid, pst_add_user_payload->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_add_user_payload->us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_add_notify_alg::mac_res_get_dmac_user failed.user_idx:[%u].", pst_add_user_payload->us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }
    mac_vap_set_aid(&pst_dmac_vap->st_vap_base_info, pst_add_user_payload->us_sta_aid);
    mac_user_set_assoc_id(&pst_dmac_user->st_user_base_info, pst_add_user_payload->us_user_idx);

    mac_user_set_ht_hdl(&pst_dmac_user->st_user_base_info, &pst_add_user_payload->st_ht_hdl);
    mac_user_set_vht_hdl(&pst_dmac_user->st_user_base_info, &pst_add_user_payload->st_vht_hdl);
    if (pst_dmac_user->st_user_base_info.st_vht_hdl.bit_vht_txop_ps)
    {
        pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_txop_ps = OAL_TRUE;
    }

    ul_ret = dmac_alg_add_assoc_user_notify(pst_dmac_vap, pst_dmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_add_notify_alg::dmac_alg_add_assoc_user_notify failed[%d].", ul_ret);
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_alg_vap_up_notify(&(pst_dmac_vap->st_vap_base_info));

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        dmac_full_phy_freq_user_add(&(pst_dmac_vap->st_vap_base_info), pst_dmac_user);
#endif
    }

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_user_del_offload
 功能描述  : 在DMAC OFFLOAD模式下dmac侧删除user的添加操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月22日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_del_offload(mac_vap_stru* pst_vap, oal_uint16 us_user_idx)
{
    mac_device_stru   *pst_mac_device;
    oal_uint32         ul_ret;

    /* 从vap中删除用户 */
    ul_ret = mac_vap_del_user(pst_vap, us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_del::vap del failed.}");
    }

    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_user_del_offload::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 释放用户内存 */
    ul_ret = dmac_user_free(us_user_idx);
    if (OAL_SUCC == ul_ret)
    {
        /* offload模式下device下已关联user个数-- */
        pst_mac_device->uc_asoc_user_cnt--;

    }
    else
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_user_del_offload::mac_res_free_mac_user failed[%d].", ul_ret);
    }

    /* STA模式下将关联的VAP的id置为非法值 */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_vap, 0xff);
    }

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_full_phy_freq_user_del
 功能描述  : 在DMAC OFFLOAD模式下user ldpc能力标志位清零
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月5日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_full_phy_freq_user_del(dmac_user_stru *pst_dmac_user,mac_device_stru *pst_mac_device)
{
    if (OAL_TRUE == DMAC_GET_USER_SUPPORT_VHT(&(pst_dmac_user->st_user_base_info)) ||
        (OAL_TRUE == DMAC_GET_USER_SUPPORT_HT(&(pst_dmac_user->st_user_base_info))))
    {
        if (pst_mac_device->pst_device_stru->uc_full_phy_freq_user_cnt > 0)
        {
            pst_mac_device->pst_device_stru->uc_full_phy_freq_user_cnt--;
        }
        else
        {
            OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,"vht support user cnt should not be 0");
        }
    }
    OAM_WARNING_LOG1(0,OAM_SF_PWR,"dmac_full_phy_freq_user_del::remain[%d]user",pst_mac_device->pst_device_stru->uc_full_phy_freq_user_cnt);

    /*phy 降频处理 */
    hal_process_phy_freq(pst_mac_device->pst_device_stru);

}

#endif
/*****************************************************************************
 函 数 名  : dmac_user_del
 功能描述  : 删除用户
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月22日
    作    者   : zhangheng
    修改内容   : 新生成函数
  2.日    期   : 2014年6月19日
    作    者   : z00273164
    修改内容   : 增加sa query timer的删除

*****************************************************************************/
oal_uint32  dmac_user_del(frw_event_mem_stru *pst_event_mem)
{
    oal_uint16                      us_user_idx;
    dmac_user_stru                 *pst_dmac_user;
    dmac_vap_stru                  *pst_dmac_vap;
    frw_event_stru                 *pst_event;
    dmac_ctx_del_user_stru         *pst_del_user_payload;
    mac_device_stru                *pst_mac_device;
    oal_uint32                      ul_rslt = OAL_FAIL;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_event_mem)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_del::pst_event_mem null.}");
        return OAL_FAIL;
    }
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    pst_del_user_payload = (dmac_ctx_del_user_stru *)pst_event->auc_event_data;
    us_user_idx          = pst_del_user_payload->us_user_idx;

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG, "{dmac_user_del::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap   = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event->st_event_hdr.uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event->st_event_hdr.uc_vap_id, OAM_SF_CFG, "{dmac_user_del::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 下发无效user idx，用mac地址查找user */
    if (MAC_INVALID_USER_ID == us_user_idx)
    {
        ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), pst_del_user_payload->auc_user_mac_addr, &us_user_idx);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_ERROR_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,"{dmac_user_del::Cannot find user by idx[%d],and mac_addr[%02x XX XX XX %02x %02x]!.}",
                        us_user_idx,
                        pst_del_user_payload->auc_user_mac_addr[0],
                        pst_del_user_payload->auc_user_mac_addr[4],
                        pst_del_user_payload->auc_user_mac_addr[5]);
            return OAL_ERR_CODE_PTR_NULL;
        }
    }

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_del::pst_dmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    /* AP 侧硬件PMF控制开关填写 */
    dmac_11w_update_users_status(pst_dmac_vap, &pst_dmac_user->st_user_base_info, OAL_FALSE);
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

    /* 删除tid队列中的所有信息 */
    dmac_tid_clear(&(pst_dmac_user->st_user_base_info), pst_mac_device);
    dmac_tid_tx_queue_exit(pst_dmac_user);

    /* dmac user相关操作去注册 */
    dmac_alg_del_assoc_user_notify(pst_dmac_vap, pst_dmac_user);

    /* 如果是STA删除用户，表示此STA去关联了，调用vap down通知链 */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_alg_vap_down_notify(&(pst_dmac_vap->st_vap_base_info));

#ifdef _PRE_WLAN_FEATURE_STA_PM
        mac_vap_set_aid(&(pst_dmac_vap->st_vap_base_info), 0);
        dmac_pm_sta_post_event(pst_dmac_vap, STA_PWR_EVENT_DEASSOCIATE, 0, OAL_PTR_NULL);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        dmac_full_phy_freq_user_del(pst_dmac_user, pst_mac_device);
#endif

    }

    #ifdef _PRE_WLAN_FEATURE_UAPSD
    dmac_uapsd_user_destroy(pst_dmac_user);
    #endif

    /* 删除用户节能结构,清除vap保存的该用户的tim_bitmap信息 */
    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        dmac_psm_user_ps_structure_destroy(pst_dmac_user);
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);

        if (OAL_TRUE == pst_dmac_user->bit_ps_mode)
        {
            pst_dmac_vap->uc_ps_user_num--;
        }
    }

    dmac_user_inactive(pst_dmac_user);

    /* 如果VAP模式是STA，则需要恢复STA寄存器到初始状态 */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (OAL_TRUE == pst_mac_device->st_cap_flag.bit_proxysta)
        {
            if (OAL_TRUE ==pst_dmac_vap->st_vap_base_info.st_vap_proxysta.en_is_main_proxysta)
            {
                dmac_vap_sta_reset(pst_dmac_vap);
            }
            else
            {
                /* do nothing，不删除user */
            }
        }
        else
        {
            dmac_vap_sta_reset(pst_dmac_vap);
        }
#else
        dmac_vap_sta_reset(pst_dmac_vap);

#endif
    }

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    /* 单用户跟踪删除定时器 */
    if (OAL_TRUE == pst_dmac_user->st_user_track_ctx.st_txrx_param_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_dmac_user->st_user_track_ctx.st_txrx_param_timer);
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#ifdef _PRE_WLAN_FEATURE_SMPS
    /* 删除用户，更新SMPS能力 */
    mac_user_set_sm_power_save(&pst_dmac_user->st_user_base_info, 0);
#endif

    dmac_psm_disable_user_to_psm_back(pst_mac_device,pst_dmac_user);
    dmac_user_del_offload(&pst_dmac_vap->st_vap_base_info, us_user_idx);
#else
    /* 非offload模式下，device下用户数已经在hmac侧--，这里不需要再判断返回值做用户数--动作 */
    dmac_user_free(us_user_idx);
#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    /* DTS2015100700205,特殊网卡兼容性问题规避方案，用户去关联后暂时关闭该规避 */
    pst_mac_device->st_dataflow_brk_bypass.en_brk_limit_aggr_enable = OAL_FALSE;
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    dmac_compatibility_handler(pst_dmac_vap, pst_del_user_payload->en_ap_type, OAL_FALSE);
    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_UM, "{dmac_user_del::Del user[%d] SUCC! vap user nums:%d,device user nums:%d, user mac_addr:%02x:xx:xx:xx:%02x:%02x.}",
                    6,
                    us_user_idx,
                    pst_dmac_vap->st_vap_base_info.us_user_nums,
                    pst_mac_device->uc_asoc_user_cnt,
                    pst_del_user_payload->auc_user_mac_addr[0],
                    pst_del_user_payload->auc_user_mac_addr[4],
                    pst_del_user_payload->auc_user_mac_addr[5]);
#else
    OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_UM, "{dmac_user_del::Del user[%d] SUCC! vap user nums:%d,device user nums:%d, user mac_addr:xx:xx:xx:xx:xx:%02x.}",
                    us_user_idx,
                    pst_dmac_vap->st_vap_base_info.us_user_nums,
                    pst_mac_device->uc_asoc_user_cnt,
                    pst_del_user_payload->auc_user_mac_addr[5]);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_user_key_search_fail_handler
 功能描述  : 接收帧key search fail处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月26日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_user_key_search_fail_handler(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;

    /* 如果用户不存在，什么都不做 */
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_user_key_search_fail_handler::pst_dmac_user null.}");
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_user_key_search_fail_handler::pst_mac_device null.}");
        return;
    }

    /* 如果活跃用户数没有满规格，则将此用户转为活跃用户 */
    if (pst_mac_device->uc_active_user_cnt < WLAN_ACTIVE_USER_MAX_NUM)
    {
        dmac_user_active(pst_dmac_user);
        return;
    }
}


/*****************************************************************************
 函 数 名  : dmac_user_tx_inactive_user_handler
 功能描述  : 发送流程非活跃用户处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月26日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_tx_inactive_user_handler(dmac_user_stru *pst_dmac_user)
{
    mac_device_stru    *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_tx_inactive_user_handler::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_CFG,
                         "{dmac_user_tx_inactive_user_handler::active user >= WLAN_ACTIVE_USER_MAX_NUMl.}");
        return OAL_FAIL;
    }

    return dmac_user_active(pst_dmac_user);

}

#ifdef _PRE_WLAN_DFT_EVENT
/*****************************************************************************
 函 数 名  : dmac_event_pause_user
 功能描述  : 暂停或者恢复user事件消息上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_user_status_change_to_sdt(
                                       dmac_user_stru       *pst_dmac_user,
                                       oal_bool_enum_uint8   en_is_user_paused )
{
    oal_uint8       auc_event[50] = {0};
    auc_event[0] = en_is_user_paused;

    DMAC_EVENT_PAUSE_OR_RESUME_USER(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                    pst_dmac_user->st_user_base_info.uc_vap_id,
                                    OAM_EVENT_PAUSE_OR_RESUME_USER,
                                    auc_event);
}
#endif

/*****************************************************************************
 函 数 名  : dmac_user_pause
 功能描述  : 暂停用户所有TID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_pause(dmac_user_stru *pst_dmac_user)
{
    oal_uint8       uc_tid_idx;
    dmac_tid_stru  *pst_tid;
    oal_uint32      ul_ret;

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_pause::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
    /* DTS2015081802876 防止用户已经删除后，P2P NOA中断事件才得到处理，pause和resume状态不匹配 */
    if (MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_DFT_EVENT
    dmac_user_status_change_to_sdt(pst_dmac_user, OAL_TRUE);
#endif

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx++)
    {
        pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_idx]);

        ul_ret = dmac_tid_pause(pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_PS);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 函 数 名  : dmac_user_resume
 功能描述  : 恢复用户所有TID
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月27日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_resume(dmac_user_stru *pst_dmac_user)
{
    oal_uint8       uc_tid_idx;
    dmac_tid_stru  *pst_tid;
    oal_uint32      ul_ret;
    mac_device_stru *pst_mac_device = OAL_PTR_NULL;


    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_user_resume::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* DTS2015081802876 防止用户已经删除后，P2P NOA中断事件才得到处理，导致device获取失败 */
    if (MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)
    {
        return OAL_SUCC;
    }

    pst_mac_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_user_resume::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_DFT_EVENT
    dmac_user_status_change_to_sdt(pst_dmac_user, OAL_FALSE);
#endif

    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx++)
    {
        pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid_idx]);

        ul_ret = dmac_tid_resume(pst_mac_device->pst_device_stru, pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_PS);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
    }

    return OAL_SUCC;

}


/*****************************************************************************
 函 数 名  : dmac_user_set_groupid_partial_aid
 功能描述  : 设置user的groupid 和 partial aid(11ac Draft 6.0中9.17a)
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : y00184180
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_user_set_groupid_partial_aid(mac_vap_stru  *pst_mac_vap,
                                                      dmac_user_stru *pst_dmac_user)
{
    oal_uint16     us_temp_partial_aid;
    oal_uint16     us_temp_aid;
    oal_uint8      uc_temp_bssid;


    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_dmac_user->uc_groupid     = 0;

        /* 取BSSID[39:47] */
        us_temp_partial_aid = OAL_MAKE_WORD16(pst_mac_vap->auc_bssid[4], pst_mac_vap->auc_bssid[5]);

        /* 把bssid中48个bit的高9bit对应的10进制值作为paid */
        pst_dmac_user->us_partial_aid = (us_temp_partial_aid & 0xFF80) >> 7;

    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        pst_dmac_user->uc_groupid     = 63;

        us_temp_aid   = pst_dmac_user->st_user_base_info.us_assoc_id & 0x1FF;
        uc_temp_bssid = (pst_mac_vap->auc_bssid[5] & 0x0F) ^ ((pst_mac_vap->auc_bssid[5] & 0xF0) >> 4);
        pst_dmac_user->us_partial_aid = (us_temp_aid + (uc_temp_bssid << 5) ) & ((1 << 9) -1);
    }
    else
    {
        pst_dmac_user->uc_groupid     = 63;
        pst_dmac_user->us_partial_aid = 0;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 函 数 名  : dmac_user_set_smps_mode
 功能描述  : 设置获取user的smps模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月9日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_user_get_smps_mode(mac_vap_stru  *pst_mac_vap, mac_user_stru *pst_mac_user)
{
    wlan_mib_mimo_power_save_enum_uint8 en_vap_smps;
    wlan_mib_mimo_power_save_enum_uint8 en_user_smps;

    if (OAL_TRUE != pst_mac_user->st_ht_hdl.en_ht_capable)
    {
       return WLAN_MIB_MIMO_POWER_SAVE_MIMO;
    }

    en_vap_smps  = pst_mac_vap->st_cap_flag.bit_smps;
    en_user_smps = (wlan_mib_mimo_power_save_enum_uint8)pst_mac_user->st_ht_hdl.bit_sm_power_save;

    return (oal_uint8)((en_vap_smps >= en_user_smps)? en_user_smps : en_vap_smps);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 函 数 名  : dmac_ap_pause_all_user
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_ap_pause_all_user(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru                  *pst_entry;
    oal_dlist_head_stru                  *pst_user_list_head;
    mac_user_stru                        *pst_user_tmp;
    dmac_user_stru                       *pst_dmac_user_tmp;
    mac_device_stru                      *pst_mac_device;

    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_ap_pause_all_user}");
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_ap_pause_all_user::pst_device_base_info[%d] null!}", pst_mac_vap->uc_device_id);
        return;
    }
    /* 遍历vap下所有用户,pause tid 队列 */
    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = (dmac_user_stru *)mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
        if (OAL_PTR_NULL == pst_dmac_user_tmp)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY,"{dmac_ap_pause_all_user::mac_res_get_dmac_user failed.assoc_id:[%u].",pst_user_tmp->us_assoc_id);
            continue;
        }

        /* 指向双向链表下一个 */
        pst_entry = pst_entry->pst_next;

        /* pause tid */
        dmac_user_pause(pst_dmac_user_tmp);

        /* 暂停该vap下的所有用户的硬件队列的发送, 硬件上报psm_back,软件再回收 */
        hal_tx_enable_peer_sta_ps_ctrl(pst_mac_device->pst_device_stru, pst_dmac_user_tmp->uc_lut_index);
    }
}
/*****************************************************************************
 函 数 名  : dmac_ap_resume_all_user
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : oal_uint8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月10日
    作    者   : l00280485
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_ap_resume_all_user(mac_vap_stru *pst_mac_vap)
{
    oal_dlist_head_stru                  *pst_entry;
    oal_dlist_head_stru                  *pst_user_list_head;
    mac_user_stru                        *pst_user_tmp;
    dmac_user_stru                       *pst_dmac_user_tmp;
    mac_device_stru                      *pst_mac_device;
    //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{dmac_ap_resume_all_user}");
    pst_mac_device  = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_ap_resume_all_user::pst_device_base_info[%d] null!}", pst_mac_vap->uc_device_id);
        return;
    }
    /* 遍历vap下所有用户,pause tid 队列 */
    pst_user_list_head = &(pst_mac_vap->st_mac_user_list_head);
    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_dmac_user_tmp = (dmac_user_stru *)mac_res_get_dmac_user(pst_user_tmp->us_assoc_id);
        if (OAL_PTR_NULL == pst_dmac_user_tmp)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY,"{dmac_ap_resume_all_user::mac_res_get_dmac_user failed.assoc_id:[%u].",pst_user_tmp->us_assoc_id);
            continue;
        }


        /* 指向双向链表下一个 */
        pst_entry = pst_entry->pst_next;

        /* pause tid */
        dmac_user_resume(pst_dmac_user_tmp);

        /* 恢复该vap下的所有用户的硬件队列的发送 */
        hal_tx_disable_peer_sta_ps_ctrl(pst_mac_device->pst_device_stru, pst_dmac_user_tmp->uc_lut_index);
    }
}
#endif

/*****************************************************************************
 函 数 名  : mac_vap_get_dmac_user_by_addr
 功能描述  : 根据mac地址获取mac_user指针
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月8日
    作    者   : l00324381
    修改内容   : 新生成函数

*****************************************************************************/
dmac_user_stru  *mac_vap_get_dmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr)
{
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx   = 0xffff;
    dmac_user_stru         *pst_dmac_user = OAL_PTR_NULL;

    /*根据mac addr找sta索引*/
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if(OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_vap_get_dmac_user_by_addr::find_user_by_macaddr failed[%d].}", ul_ret);
        if (OAL_PTR_NULL != puc_mac_addr)
        {
            OAM_WARNING_LOG3(0, OAM_SF_ANY,"{mac_vap_get_dmac_user_by_addr:: mac_addr[%02x XX XX XX %02x %02x]!.}",
                                puc_mac_addr[0], puc_mac_addr[4], puc_mac_addr[5]);
        }
        return OAL_PTR_NULL;
    }

    /*根据sta索引找到user内存区域*/
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_get_dmac_user_by_addr::user ptr null.}");
    }
    return pst_dmac_user;
}


/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_user_get_tid_by_num);
oal_module_symbol(dmac_user_get_smartant_training_state);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_user_set_smartant_training_state);
#endif
oal_module_symbol(dmac_user_get_smartant_normal_rate_stats);
#ifdef _PRE_WLAN_FEATURE_SMARTANT
oal_module_symbol(dmac_user_set_smartant_normal_rate_stats);
#endif
oal_module_symbol(dmac_user_get_vip_flag);
oal_module_symbol(dmac_user_set_vip_flag);
oal_module_symbol(dmac_user_get_ps_mode);
oal_module_symbol(dmac_alg_distance_notify_hook);
oal_module_symbol(dmac_alg_co_intf_notify_hook);
oal_module_symbol(dmac_alg_cca_intf_notify_hook);
oal_module_symbol(mac_res_get_dmac_user);
oal_module_symbol(mac_vap_get_dmac_user_by_addr);


#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(dmac_user_get_smps_mode);
#endif
/*lint +e578*//*lint +e19*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

