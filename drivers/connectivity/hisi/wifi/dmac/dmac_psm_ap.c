    /******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_psm_ap.c
  版 本 号   : 初稿
  作    者   : 邹洪良
  生成日期   : 2013年9月2日
  最近修改   :
  功能描述   : PSM特性处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年9月2日
    作    者   : 邹洪良
    修改内容   : 创建文件
  2.日    期   : 2014年11月1日
    作    者   : g00260350
    修改内容   : 修改timie设置

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_net.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_vap.h"
#include "dmac_main.h"
#include "dmac_user.h"
#include "dmac_psm_ap.h"
#include "dmac_uapsd.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_rx_data.h"
#include "hal_ext_if.h"
#include "dmac_blockack.h"
#include "dmac_tx_complete.h"
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PSM_AP_C
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
extern oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
extern oal_uint32  dmac_encap_beacon(
                dmac_vap_stru               *pst_dmac_vap,
                oal_uint8                   *puc_beacon_buf,
                oal_uint16                  *pus_beacon_len);

/*****************************************************************************
 函 数 名  : dmac_psm_set_more_data
 功能描述  : 如果节能队列中还有缓存帧，则设置帧头的more data位为1
 输入参数  : pst_net_buf:要被发送的net_buff
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void dmac_psm_set_more_data(oal_netbuf_stru *pst_net_buf)
{
    mac_tx_ctl_stru     *pst_tx_ctrl;
    mac_ieee80211_frame_stru    *pst_frame_hdr;

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_ctrl);
    pst_frame_hdr->st_frame_control.bit_more_data = 0x01;
}

/*****************************************************************************
 函 数 名  : dmac_psm_set_local_bitmap
 功能描述  : 设置tim_bitmap中的相应位
 输入参数  : pst_dmac_vap
             pst_dmac_user
             uc_bitmap_flg:需要将bitmap相应位置上的值(0或者1)
 输出参数  : 无
 返 回 值  : OAL_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2014年11月22日
    作    者   : g00260350
    修改内容   : 增加组播的bmc的处理

*****************************************************************************/
oal_void dmac_psm_set_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_bitmap_flg)
{
    oal_uint16          us_user_assoc_id;
    oal_uint8           uc_tim_byte_idx;
    oal_uint8           uc_tim_bit_mask;
    oal_uint8           uc_tim_offset;
    oal_uint8           uc_PVBitmap_len;
    oal_uint8           uc_tim_min_offset;
    oal_uint8           uc_tim_max_offset;
    oal_uint8           uc_index;

    if (OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::param null.}");
        return;
    }
    /***************************************************************************
     ---------------------------------------------------------------------------
     |TIM bitmap len |Bitmap Control            |Partial Virtual Bitmap|
     ---------------------------------------------------------------------------
     |1              |1 (bit1-7=offset bit0=BMC)|1~251                 |
     ---------------------------------------------------------------------------
    ***************************************************************************/

    /* the Partial Virtual Bitmap field consists of octets numbered N1 to N2
       of the traffic indication virtual bitmap, where N1 is the largest even
       number such that bits numbered 1 to (N1 * 8) - 1 in the bitmap are all
       0 and N2 is the smallest number such that bits numbered (N2 + 1) * 8 to
       2007 in the bitmap are all 0. In this  case, the Bitmap Offset subfield
       value contains the number N1/2 */
    uc_PVBitmap_len  = pst_dmac_vap->puc_tim_bitmap[0];
    uc_tim_offset    = 2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0));

    /* 长度校验 */
    if (uc_PVBitmap_len + uc_tim_offset > pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::tim_offset[%d] + len[%d] >= bitmap_len[%d].}",
                       uc_tim_offset, uc_PVBitmap_len, pst_dmac_vap->uc_tim_bitmap_len);
        OAL_MEMZERO(pst_dmac_vap->puc_tim_bitmap, pst_dmac_vap->uc_tim_bitmap_len);
        /* TIM bitmap len is default 1*/
        pst_dmac_vap->puc_tim_bitmap[0] = 1;
        uc_PVBitmap_len = 1;
    }

    /* 如果是组播用户，修改Bitmap Control的bit0，
       否则根据用户关联id找到用户在Partial Virtual Bitmap中的字节位置与比特位置 */
    if (OAL_TRUE == pst_dmac_user->st_user_base_info.en_is_multi_user)
    {
        uc_tim_byte_idx          = 1;
        uc_tim_bit_mask          = (oal_uint8)(BIT0);
    }
    else
    {
        us_user_assoc_id         = pst_dmac_user->st_user_base_info.us_assoc_id;
        uc_tim_byte_idx          = 2 + (oal_uint8)(us_user_assoc_id >> 3);
        uc_tim_bit_mask          = (oal_uint8)(BIT0 << (us_user_assoc_id & 0x07));
    }
    if (uc_tim_byte_idx >= pst_dmac_vap->uc_tim_bitmap_len)
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_set_local_bitmap::usr[%d] tim_byte_idx[%d] >= bitmap_len[%d].}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, uc_tim_byte_idx, pst_dmac_vap->uc_tim_bitmap_len);
        return;
    }
    /* 修改相应的bit的值 */
    if (0 == uc_bitmap_flg)
    {
        pst_dmac_vap->puc_tim_bitmap[uc_tim_byte_idx] &= (oal_uint8)(~uc_tim_bit_mask);
    }
    else
    {
        pst_dmac_vap->puc_tim_bitmap[uc_tim_byte_idx] |= (oal_uint8)uc_tim_bit_mask;
    }

    /* 若是组播，则不涉及修改dtim */
    if (1 == uc_tim_byte_idx)
    {
        return;
    }
    uc_tim_min_offset = OAL_MIN(uc_tim_byte_idx, uc_tim_offset);
    uc_tim_max_offset = OAL_MAX(uc_tim_byte_idx, uc_tim_offset + uc_PVBitmap_len - 1);
    /* 找到最小的非0的作为tim_offset(必须是偶数)，为了减少循环次数，只比较本次修改所涉及的字节 */
    uc_tim_offset     = 2;
    for (uc_index = uc_tim_min_offset; uc_index <= uc_tim_max_offset; uc_index++)
    {
        if (0 != pst_dmac_vap->puc_tim_bitmap[uc_index])
        {
            uc_tim_offset = uc_index & (~1);
            break;
        }
    }

    /* 找到最大的非0的用来计算PVBitmap_len */
    for (uc_index = uc_tim_max_offset; uc_index > uc_tim_offset; uc_index--)
    {
        if (0 != pst_dmac_vap->puc_tim_bitmap[uc_index])
        {
            break;
        }
    }
    /*更新PVBitmap_len及Bitmap Control(bit1-bit7表示offset；bit0表示BMC */
    pst_dmac_vap->puc_tim_bitmap[0] = (uc_index - uc_tim_offset) + 1;
    pst_dmac_vap->puc_tim_bitmap[1] &= (oal_uint8)(BIT0);
    pst_dmac_vap->puc_tim_bitmap[1] += uc_tim_offset - 2;
}
#if 0
/*****************************************************************************
 函 数 名  : dmac_psm_get_local_bitmap
 功能描述  : 获取tim_bitmap中的相应位
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_get_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint16          us_user_assoc_id;
    oal_uint8           uc_byte_idx;
    oal_uint8           uc_bit_mask = (oal_uint8)(BIT0);

    /* Bitmap Control的bit0表示组播用户 */
    if (pst_dmac_user->st_user_base_info.en_is_multi_user)
    {
        return ((pst_dmac_vap->puc_tim_bitmap[1] & uc_bit_mask) == uc_bit_mask);
    }

    /* 根据用户关联id找到用户在bitmap中的字节位置与比特位置 */
    us_user_assoc_id = pst_dmac_user->st_user_base_info.us_assoc_id;
    uc_byte_idx      = 2 + (oal_uint8)(us_user_assoc_id >> 3);
    uc_bit_mask      = (oal_uint8)(BIT0 << (us_user_assoc_id & 0x07));
    if (uc_byte_idx >= pst_dmac_vap->uc_tim_bitmap_len)
    {
        return 0;
    }

    return ((pst_dmac_vap->puc_tim_bitmap[uc_byte_idx] & uc_bit_mask) == uc_bit_mask);
}

/*****************************************************************************
 函 数 名  : dmac_psm_get_bitmap_len
 功能描述  : 获取tim_bitmap len
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_get_bitmap_len(dmac_vap_stru *pst_dmac_vap)
{
    return pst_dmac_vap->puc_tim_bitmap[0];
}

/*****************************************************************************
 函 数 名  : dmac_psm_get_bitmap_offset
 功能描述  : 获取tim_bitmap len
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00260350
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_get_bitmap_offset(dmac_vap_stru *pst_dmac_vap)
{
    return (oal_uint8)(2 + (pst_dmac_vap->puc_tim_bitmap[1] & (oal_uint8)(~BIT0)));
}
#endif

/*****************************************************************************
 函 数 名  : dmac_psm_dequeue_first_mpdu
 功能描述  : 从队列中取出第一个mpdu,将它从队列删除并返回，一个mpdu中可能有多个skb
 输入参数  : st_queue_head: 队列头
 输出参数  : 无
 返 回 值  : oal_netbuf_stru*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_netbuf_stru* dmac_psm_dequeue_first_mpdu(dmac_user_ps_stru  *pst_ps_structure)
{
    oal_netbuf_stru        *pst_first_net_buf;
    oal_netbuf_stru        *pst_tmp_net_buf;
    oal_netbuf_stru        *pst_net_buf;
    mac_tx_ctl_stru        *pst_tx_ctrl;
    oal_uint8               uc_netbuf_num_per_mpdu;
    oal_netbuf_head_stru   *pst_ps_queue_head;

    pst_ps_queue_head = &pst_ps_structure->st_ps_queue_head;

    pst_first_net_buf = OAL_NETBUF_HEAD_NEXT(pst_ps_queue_head);
    pst_tx_ctrl       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_first_net_buf);

    /* mpdu不是a-msdu，返回第一个net_buff即可 */
    if (OAL_FALSE == mac_get_cb_is_amsdu(pst_tx_ctrl))
    {
        pst_first_net_buf = oal_netbuf_delist(pst_ps_queue_head);
        oal_atomic_dec(&pst_ps_structure->uc_mpdu_num);
        return pst_first_net_buf;
    }

    if (OAL_FALSE == MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl))
    {
        /* 这个错误只有踩内存才会出现，如果出现就无法恢复，以太网来的包无法释放，
           软件复位也没用，内存也会泄漏
        */
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_dequeue_first_mpdu::not the first msdu.}");
        return OAL_PTR_NULL;
    }

    /* 节能队列中的第一个mpdu是a-msdu，获取skb个数 */
    uc_netbuf_num_per_mpdu = MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);

    /* 将第一个mpdu中的所有skb从节能队列中取出，然后组成一个net_buff链 */
    pst_first_net_buf = oal_netbuf_delist(pst_ps_queue_head);
    uc_netbuf_num_per_mpdu--;

    pst_tmp_net_buf = pst_first_net_buf;
    while (0 != uc_netbuf_num_per_mpdu)
    {
        pst_net_buf = oal_netbuf_delist(pst_ps_queue_head);
        oal_set_netbuf_prev(pst_net_buf, pst_tmp_net_buf);
        oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

        oal_set_netbuf_next(pst_tmp_net_buf, pst_net_buf);

        pst_tmp_net_buf = pst_net_buf;

        uc_netbuf_num_per_mpdu--;
    }

    oal_atomic_dec(&pst_ps_structure->uc_mpdu_num);

    return pst_first_net_buf;

}


/*****************************************************************************
 函 数 名  : dmac_psm_user_ps_structure_init
 功能描述  : 初始化user的节能结构
 输入参数  : pst_ps_structure: 指向用户节能结构的指针
 输出参数  : 无
 返 回 值  : OAL_SUCC或者是其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月29日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_user_ps_structure_init(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru *pst_ps_structure;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

    oal_spin_lock_init(&(pst_ps_structure->st_lock_ps));

    oal_netbuf_list_head_init(&(pst_ps_structure->st_ps_queue_head));

    oal_atomic_set(&pst_ps_structure->uc_mpdu_num, 0);

    pst_ps_structure->en_is_pspoll_rsp_processing = OAL_FALSE;

#ifdef _PRE_WLAN_DFT_STAT
    /* 申请维测统计结构的内存 */
    pst_ps_structure->pst_psm_stats = (dmac_user_psm_stats_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                                               OAL_SIZEOF(dmac_user_psm_stats_stru),
                                                                               OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ps_structure->pst_psm_stats))
    {
        OAM_ERROR_LOG1(0, OAM_SF_PWR, "{dmac_psm_user_ps_structure_init::alloc pst_ps_stats mem fail, size[%d].}", OAL_SIZEOF(dmac_user_psm_stats_stru));
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(pst_ps_structure->pst_psm_stats, OAL_SIZEOF(dmac_user_psm_stats_stru));
#endif

    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : dmac_psm_clear_ps_queue
 功能描述  : 清空节能队列的数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月26日
    作    者   : z00273164
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_clear_ps_queue(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru   *pst_ps_structure;
    oal_netbuf_stru     *pst_net_buf;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

    /* 节能队列不为空的情况下，释放节能队列中的mpdu */
    while (oal_atomic_read(&pst_ps_structure->uc_mpdu_num))
    {
        oal_spin_lock(&pst_ps_structure->st_lock_ps);

        /* 由于节能队列中的mpdu可能来自wlan也可能来自lan，在释放的时候需要区分，
           因此不能将队列中的mpdu一次性释放，而是应该以mpdu为单位进行释放
        */
        pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);
    }

}

/*****************************************************************************
 函 数 名  : dmac_psm_user_ps_structure_destroy
 功能描述  : 删除用户前，将用户结构体下的节能结构释放掉
 输入参数  : pst_ps_structure: 指向用户节能结构的指针
 输出参数  :
 返 回 值  : OAL_SUCC或者是其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_user_ps_structure_destroy(dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru   *pst_ps_structure;
    oal_netbuf_stru     *pst_net_buf;

    pst_ps_structure = &(pst_dmac_user->st_ps_structure);

#ifdef _PRE_WLAN_DFT_STAT
    if (OAL_PTR_NULL != pst_ps_structure->pst_psm_stats)
    {
        OAL_MEM_FREE(pst_ps_structure->pst_psm_stats, OAL_TRUE);
        pst_ps_structure->pst_psm_stats = OAL_PTR_NULL;
    }
#endif

    pst_ps_structure->en_is_pspoll_rsp_processing = OAL_FALSE;

    /* 节能队列不为空的情况下，释放节能队列中的mpdu */
    while (oal_atomic_read(&pst_ps_structure->uc_mpdu_num))
    {
        oal_spin_lock(&pst_ps_structure->st_lock_ps);

        /* 由于节能队列中的mpdu可能来自wlan也可能来自lan，在释放的时候需要区分，
           因此不能将队列中的mpdu一次性释放，而是应该以mpdu为单位进行释放
        */
        pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);

        dmac_tx_excp_free_netbuf(pst_net_buf);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);
    }

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
/*****************************************************************************
 函 数 名  : dmac_is_null_data
 功能描述  : 判断一个netbuffer 是否为null data 帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_TURE       是null data
             OAL_FALSE      非null data
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月10日
    作    者   : d00194999
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_is_null_data(oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                       uc_mgmt_type;
    oal_uint8                       uc_mgmt_subtype;

    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf);
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    return (WLAN_DATA_BASICTYPE == uc_mgmt_type && WLAN_NULL_FRAME == uc_mgmt_subtype);
}
#endif

/*****************************************************************************
 函 数 名  : dmac_psm_pkt_need_buff
 功能描述  : 判断一个帧是否需要入节能队列，入参的net_buff有可能是一个net_buff
             链，这个链肯定是发给同一个用户的，所有的net_buff有关节能的特征
             都是相同的，因此只需要判断第一个net_buff就可以了。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_TURE或者OAL_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint8 dmac_psm_pkt_need_buff(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    mac_tx_ctl_stru                *pst_tx_ctrl;
    mac_ieee80211_frame_stru       *pst_mac_header;
    oal_uint8                       uc_mgmt_type;
    oal_uint8                       uc_mgmt_subtype;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user || OAL_PTR_NULL == pst_net_buf))
    {
        return OAL_FALSE;
    }

    /* 非ap模式下不需要缓存 */
    if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return OAL_FALSE;
    }

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);

    if (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl))
    {
        /*
           如果是单播帧，则有两种情况下该帧不需要缓存:
           1、用户不节能
           2、用户处于节能模式但是这个帧是刚从节能队列取出来的
        */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        /* DTS2015100906242 如果是AP 发送的keepalive null 帧，则直接放入节能队列 */
        if (IS_AP(&(pst_dmac_vap->st_vap_base_info))
            && (OAL_FALSE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
            && (OAL_TRUE == dmac_is_null_data(pst_net_buf)))
        {
            return OAL_TRUE;
        }
#endif
        if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
        {
            return OAL_FALSE;
        }

        if (OAL_TRUE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
        {
            return OAL_FALSE;
        }
    }
    else
    {
        /*
           如果是组播帧，则有两种情况下该帧不需要缓存:
           1、所有关联用户都不节能
           2、有用户处于节能模式但是这个帧是刚从节能队列取出来的
        */
        if (0 == pst_dmac_vap->uc_ps_user_num)
        {
            return OAL_FALSE;
        }

        if (OAL_TRUE == MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl))
        {
            return OAL_FALSE;
        }
    }

    /* ACS AP扫描发probe req时不需要节能 */
    pst_mac_header  = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf);
    uc_mgmt_type    = mac_frame_get_type_value((oal_uint8 *)pst_mac_header);
    uc_mgmt_subtype = mac_frame_get_subtype_value((oal_uint8 *)pst_mac_header);

    if (WLAN_WME_AC_MGMT == mac_get_cb_ac(pst_tx_ctrl) && WLAN_MANAGEMENT == uc_mgmt_type && WLAN_PROBE_REQ == uc_mgmt_subtype)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 函 数 名  : dmac_psm_enqueue
 功能描述  : 把帧入节能队列
 输入参数  : pst_dmac_vap
             pst_dmac_user
             pst_net_buf:需要入队的ampdu/mpdu首个netbuf的地址。每一个ampud可以包含多个mpdu，每个mpdu可以包含多个netbuf
 输出参数  : 无
 返 回 值  : oal_uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2014年11月14日
    作    者   : g00260350
    修改内容   : 部分mpdu失败也算失败
  3.日    期   : 2015年1月16日
    作    者   : g00306640
    修改内容   : vipframe放到important psm队列
*****************************************************************************/
oal_uint32 dmac_psm_enqueue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    oal_netbuf_stru        *pst_next_net_buf     = OAL_PTR_NULL;
    mac_tx_ctl_stru        *pst_tx_ctrl          = OAL_PTR_NULL;
    oal_int32               l_ps_mpdu_num        = 0;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user
        || OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_rx_process_data::param is null.vap=[%d], \
                       user=[%d],buf=[%d]}.", (oal_uint32)pst_dmac_vap, (oal_uint32)pst_dmac_user,
                       (oal_uint32)pst_net_buf);
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_enqueue::psm_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* 判断节能队列是不是overrun */
    l_ps_mpdu_num = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    if (l_ps_mpdu_num + MAC_GET_CB_MPDU_NUM(pst_tx_ctrl) > MAX_MPDU_NUM_IN_PS_QUEUE)
    {
        return OAL_ERR_CODE_PS_QUEUE_OVERRUN;
    }

    /* 更新用户的pvb */
    dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
    /* DTS2015110922066,当帧进入节能队列时，设置完本地bitmap，及时更新beacon的tim信息元素 */
    dmac_encap_beacon(pst_dmac_vap, pst_dmac_vap->pauc_beacon_buffer[pst_dmac_vap->uc_beacon_idx], &(pst_dmac_vap->us_beacon_len));

    /* 对节能队列进行操作，加锁保护 */
    oal_spin_lock(&pst_dmac_user->st_ps_structure.st_lock_ps);

    /* 更新节能队列中mpdu的个数 */
    l_ps_mpdu_num += MAC_GET_CB_MPDU_NUM(pst_tx_ctrl);
    oal_atomic_set(&pst_dmac_user->st_ps_structure.uc_mpdu_num, l_ps_mpdu_num);

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats->ul_psm_enqueue_succ_cnt     += MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl);
#endif

    /* 将所有netbuf都挂到节能队列尾部 */
    while (OAL_PTR_NULL != pst_net_buf)
    {
        pst_next_net_buf = oal_get_netbuf_next(pst_net_buf);
        oal_netbuf_add_to_list_tail(pst_net_buf, &pst_dmac_user->st_ps_structure.st_ps_queue_head);
        pst_net_buf = pst_next_net_buf;
    }

    oal_spin_unlock(&pst_dmac_user->st_ps_structure.st_lock_ps);

    OAM_INFO_LOG3(0, OAM_SF_PWR, "{dmac_psm_enqueue::user[%d] enqueue %d & total %d.}",
                  pst_dmac_user->st_user_base_info.us_assoc_id, MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl), l_ps_mpdu_num);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_queue_send
 功能描述  : 从节能队列取出一个缓存帧(一个mpdu)，然后调用相应接口发送出去
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月2日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_psm_queue_send(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    dmac_user_ps_stru       *pst_ps_structure;
    oal_netbuf_stru         *pst_net_buf;
    oal_int32                l_ps_mpdu_num;
    mac_tx_ctl_stru         *pst_tx_ctrl;
    oal_uint32               ul_ret;
    mac_device_stru         *pst_mac_device;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif

    pst_ps_structure = &pst_dmac_user->st_ps_structure;

#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_ps_structure->pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_send::psm_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* 对节能队列进行操作，需要加锁保护 */
    oal_spin_lock(&pst_ps_structure->st_lock_ps);

    /* 从节能队列中取出一个mpdu,并将队列中mpdu数目减1 */
    pst_net_buf = dmac_psm_dequeue_first_mpdu(pst_ps_structure);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_queue_send::pst_net_buf null.}");

        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_dequeue_fail_cnt);

        oal_spin_unlock(&pst_ps_structure->st_lock_ps);

        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_spin_unlock(&pst_ps_structure->st_lock_ps);

    DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_dequeue_succ_cnt);

    l_ps_mpdu_num = oal_atomic_read(&pst_ps_structure->uc_mpdu_num);

    /* 判断节能队列中是否还有缓存帧，如果有，设置帧头里的MORE DATA位为1，如果队列
       已空，并且此次发送的是单播缓存帧，则关闭tim_bitmap的相应位 */
    if (0 != l_ps_mpdu_num)
    {
        dmac_psm_set_more_data(pst_net_buf);
    }
    else
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
    }

    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);

    /* DTS2015052005404,组播数据的判断方式应该采用以下形式 */
    if(OAL_TRUE == MAC_GET_CB_IS_MCAST(pst_tx_ctrl))
    {
        mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_MGMT);
    }

    if (0 == MAC_GET_CB_MPDU_NUM(pst_tx_ctrl))
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{dmac_psm_queue_send::tid %d, uc_dscr_num is zero.}", mac_get_cb_tid(pst_tx_ctrl));
    }

    /*
       置这一位的原因是:接下来要调用dmac_tx_process_data，而进入这个函数之后会判断
       是否需要将mpdu入队，如果没有下面的这个判断，会导致循环入队，这个mpdu在pspoll
       节能机制下将永远发不出去
    */
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl) = OAL_TRUE;
    /* 根据帧的类型，调用相应发送接口 */
    if (WLAN_DATA_BASICTYPE == MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl))
    {
        pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_send:: mac_res_get_dev is null.}");
            dmac_tx_excp_free_netbuf(pst_net_buf);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_data_fail_cnt);
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* DTS2015032407588,防止数据发送出去后，BA窗没有移动，造成后续收到数据出现窗错误 */
        if (OAL_FALSE == pst_dmac_user->st_user_base_info.en_is_multi_user && OAL_TRUE == dmac_user_get_ps_mode(&pst_dmac_user->st_user_base_info))
        {
            dmac_tid_resume(pst_mac_device->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctrl)], DMAC_TID_PAUSE_RESUME_TYPE_PS);
        }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        /* DTS2015082808094 1102 aput keepalive, 发送null data 帧调用dmac_tx_mgmt 函数 */
        if (MAC_GET_CB_EN_FRAME_SUBTYPE(pst_tx_ctrl) == WLAN_NULL_FRAME)
        {
            ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl));
            if (OAL_SUCC != ul_ret)
            {
                oal_netbuf_free(pst_net_buf);

                OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                 "{dmac_psm_queue_send::null data from ps queue. failed[%d].}", ul_ret);
                DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_mgmt_fail_cnt);

                //return ul_ret;
            }
            else
            {
                OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                                "{dmac_psm_queue_send::null data from ps queue.succ}");
            }
            return ul_ret;
        }
#endif
        ul_ret = dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_net_buf);
        if (OAL_SUCC != ul_ret)
        {
            pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
            OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                            "{dmac_psm_queue_send::dmac_tx_process_data failed[%d],dev_mpdu_num = %d}", ul_ret, pst_mac_device->us_total_mpdu_num);
            OAM_WARNING_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_queue_send:: be = %d, bk = %d, vi = %d, vo = %d}",
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                             pst_mac_device->aus_ac_mpdu_num[WLAN_WME_AC_VO]);
            dmac_tx_excp_free_netbuf(pst_net_buf);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_data_fail_cnt);

            return ul_ret;
        }
    }
    else
    {
        ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, MAC_GET_CB_MPDU_LEN(pst_tx_ctrl) + MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl));
        if (OAL_SUCC != ul_ret)
        {
            oal_netbuf_free(pst_net_buf);

            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_queue_send::dmac_tx_mgmt failed[%d].}", ul_ret);
            DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_send_mgmt_fail_cnt);

            return ul_ret;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_queue_flush
 功能描述  : ap收到用户改变节能模式为非节能的帧，将为用户缓存的所有帧都发给
             用户
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2015年1月17日
    作    者   : g00306640
    修改内容   : 增加部分维测

*****************************************************************************/
oal_void dmac_psm_queue_flush(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_int32       l_ps_mpdu_num;
    oal_uint32      ul_tid_num;
    oal_int32       l_ps_mpdu_send_succ = 0;
    oal_int32       l_ps_mpdu_send_fail = 0;
    oal_uint32      ul_ret;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;
#endif

    l_ps_mpdu_num       = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);

    if (l_ps_mpdu_num == 0)
    {
        /* DTS2015112606564 tid和ps队列都没有包清pvb */
        ul_tid_num      = dmac_psm_tid_mpdu_num(pst_dmac_user);

        if (0 == ul_tid_num)
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
        else
        {
            OAM_WARNING_LOG1(0,OAM_SF_PWR,"dmac_psm_queue_flush::ps queue is 0,but tid num is [%d]",ul_tid_num);
        }

        return;
    }
    /* 循环将节能队列中的所有帧发给用户 */
    while (l_ps_mpdu_num-- > 0)
    {
        ul_ret = dmac_psm_queue_send(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_psm_queue_flush::dmac_psm_queue_send fail[%d].}", ul_ret);
            l_ps_mpdu_send_fail++;
        }
        else
        {
            l_ps_mpdu_send_succ++;
        }
    }
#ifdef _PRE_WLAN_DFT_STAT
    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_queue_flush::psm_stats is null.}");
        return;
    }
    pst_psm_stats->ul_psm_dequeue_succ_cnt = (oal_uint32)l_ps_mpdu_send_succ;
    pst_psm_stats->ul_psm_dequeue_fail_cnt = (oal_uint32)l_ps_mpdu_send_fail;
#endif
    if (l_ps_mpdu_send_fail)
    {
        OAM_WARNING_LOG3(0, OAM_SF_PWR, "{dmac_psm_queue_flush::user[%d] send %d & fail %d}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_send_succ, l_ps_mpdu_send_fail);
    }

    OAM_INFO_LOG3(0, OAM_SF_PWR, "{dmac_psm_queue_flush::user[%d] send %d & fail %d}",
                  pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_send_succ, l_ps_mpdu_send_fail);

}

/*****************************************************************************
 函 数 名  : dmac_psm_tx_set_more_data
 功能描述  : 发送流程中，判断如果用户处于节能状态，则需要设置当前帧的more
             data，告诉sta是否还有节能缓存帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月24日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_tx_set_more_data(dmac_user_stru *pst_dmac_user,
                                               mac_tx_ctl_stru *pst_tx_cb)
{
    oal_int32               l_ps_mpdu_num;
    oal_bool_enum_uint8     en_tid_empty;
    mac_ieee80211_frame_stru  *pst_frame_hdr = OAL_PTR_NULL;

    if ((OAL_TRUE == pst_dmac_user->bit_ps_mode)
        && (OAL_TRUE == pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing))
    {
        l_ps_mpdu_num = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
        en_tid_empty  = dmac_psm_is_tid_empty(pst_dmac_user);

        if ((0 != l_ps_mpdu_num) || (OAL_FALSE == en_tid_empty))
        {
            pst_frame_hdr = mac_get_cb_frame_hdr(pst_tx_cb);
            if (OAL_LIKELY(OAL_PTR_NULL != pst_frame_hdr))
            {
                mac_get_cb_frame_hdr(pst_tx_cb)->st_frame_control.bit_more_data = 0x01;
            }
        }
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 函 数 名  : dmac_psm_enable_user_to_psm_back
 输入参数  : ap收到sta的节能帧，设置硬件寄存器
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_enable_user_to_psm_back(dmac_vap_stru *pst_dmac_vap,
                                                        mac_device_stru *pst_mac_device,
                                                        dmac_user_stru *pst_dmac_user)
{
    hal_to_dmac_device_stru      *pst_hal_device;

    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device)) {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_enable_user_to_psm_back::pst_hal_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_tx_enable_peer_sta_ps_ctrl(pst_hal_device, pst_dmac_user->uc_lut_index);

//    dmac_psm_flush_txq_to_psm(pst_dmac_vap, pst_dmac_user);

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : dmac_psm_set_user_to_psm_back
 输入参数  : ap收到sta的非节能，设置硬件描述符为DMAC_TX_SOFT_PSM_BACK
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_disable_user_to_psm_back(mac_device_stru *pst_mac_device,
                                                        dmac_user_stru *pst_dmac_user)
{
    hal_to_dmac_device_stru      *pst_hal_device;

    pst_hal_device = pst_mac_device->pst_device_stru;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device)) {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_disable_user_to_psm_back::pst_hal_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_tx_disable_peer_sta_ps_ctrl(pst_hal_device, pst_dmac_user->uc_lut_index);

    return OAL_SUCC;

}
#if 0
/*****************************************************************************
 函 数 名  : dmac_psm_flush_txq_to_psm
 输入参数  : 用户tid的帧插入到ps队列中
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月16日
    作    者   : g00306640
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_flush_txq_to_psm(dmac_vap_stru  *pst_dmac_vap,
                                                        dmac_user_stru *pst_dmac_user)
{
    oal_int8                      c_queue_idx;
    hal_tx_dscr_stru             *pst_tx_dscr;
    oal_dlist_head_stru          *pst_dlist_pos;
    oal_dlist_head_stru          *pst_dlist_n;
    oal_netbuf_stru              *pst_netbuf;

    /* 遍历user的8个tid，将每个tid队列的帧放到psm队列 */
    for (c_queue_idx = WLAN_TIDNO_BEST_EFFORT; c_queue_idx < WLAN_TIDNO_BUTT; c_queue_idx++) {
        /* UAPSD队列不需要获取 */
        if (WLAN_TIDNO_UAPSD == c_queue_idx) {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH_SAFE (pst_dlist_pos, pst_dlist_n, &pst_dmac_user->ast_tx_tid_queue[c_queue_idx].st_hdr) {
            pst_tx_dscr = OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
            oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
            OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);

            dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_netbuf);
            (pst_dmac_user->ast_tx_tid_queue[c_queue_idx].us_mpdu_num)--;
        }
    }
    return OAL_SUCC;

}
#endif
#else
/*****************************************************************************
 函 数 名  : dmac_psm_flush_txq_to_tid
 输入参数  : ap收到sta的节能帧，将硬件队列上属于该sta的帧放回相应的tid队列
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月23日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_psm_flush_txq_to_tid(mac_device_stru *pst_mac_device,
                                                        dmac_vap_stru  *pst_dmac_vap,
                                                        dmac_user_stru *pst_dmac_user)
{
    oal_uint8                     uc_q_idx           = 0;
    hal_tx_dscr_stru             *pst_tx_dscr        = OAL_PTR_NULL;
    mac_tx_ctl_stru              *pst_cb             = OAL_PTR_NULL;
    dmac_tid_stru                *pst_tid_queue      = OAL_PTR_NULL;
    hal_to_dmac_device_stru      *pst_hal_device     = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_pos      = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_n        = OAL_PTR_NULL;
    oal_netbuf_stru              *pst_mgmt_buf       = OAL_PTR_NULL;
    dmac_user_stru               *pst_mcast_user     = OAL_PTR_NULL;
    oal_dlist_head_stru           ast_pending_q[WLAN_TID_MAX_NUM];
    oal_uint8                     auc_mpdu_num[WLAN_TID_MAX_NUM];
    oal_uint8                     uc_tid             = 0;
    oal_uint32                    ul_ret             = 0;
    oal_uint16                    us_seq_num         = 0;
    dmac_ba_tx_stru              *pst_ba_hdl;
    oal_uint8                     uc_dscr_status     = DMAC_TX_INVALID;
    hal_tx_dscr_stru             *pst_tx_dscr_next   = OAL_PTR_NULL;

    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_mac_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;
    if(OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_hal_device is null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 遍历高优先级发送队列，将属于节能用户的管理帧的描述符释放，并把帧放到节能队列 */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].st_header)
    {
        pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
        pst_cb       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_mgmt_buf);
        /* 如果不是本用户的帧，不需要挪到节能队列 */
        if (MAC_GET_CB_TX_USER_IDX(pst_cb) != pst_dmac_user->st_user_base_info.us_assoc_id)
        {
            continue;
        }
        hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);
        /* 如果该帧已经发送过了，不需要挪到节能队列 */
        if (DMAC_TX_INVALID != uc_dscr_status)
        {
            continue;
        }
        /* 释放描述符 */
        oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
        OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);

        /* 放到节能队列，此时节能队列为空，enqueue操作后，数据排序同硬件队列的先后顺序 */
        dmac_psm_enqueue(pst_dmac_vap, pst_dmac_user, pst_mgmt_buf);

        /* 从硬件队列删除ppdu后，需要将ppducnt减1 */
        pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].uc_ppdu_cnt
                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_HI].uc_ppdu_cnt, 1);

    }
    /* 初始化临时队列 */
    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        oal_dlist_init_head(&ast_pending_q[uc_tid]);
        auc_mpdu_num[uc_tid] = 0;
    }

    /* 遍历其余4个发送队列，将属于该节能用户的mpud从硬件队列删除并添加到临时队列中 */
    for (uc_q_idx = HAL_TX_QUEUE_BK; uc_q_idx < HAL_TX_QUEUE_HI; uc_q_idx++)
    {
        oal_bool_enum en_dscr_list_is_ampdu       = OAL_FALSE;  /*当前硬件队列的描述符链类型是否是ampdu类型*/
        oal_bool_enum en_dscr_list_first_flag     = OAL_TRUE;   /*是否是描述符链的第一个描述符*/
        oal_bool_enum en_dscr_list_back_flag      = OAL_FALSE;   /*描述符链是否需要放回tid队列*/
        oal_bool_enum en_curr_dscr_back_flag      = OAL_FALSE;   /*当前描述符是否需要放回tid队列*/

        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header)
        {
            pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            pst_cb       = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_tx_dscr->pst_skb_start_addr);

            /* 如果不是本用户的帧，不需要挪到TID队列 */
            if (MAC_GET_CB_TX_USER_IDX(pst_cb) != pst_dmac_user->st_user_base_info.us_assoc_id)
            {
                continue;
            }

            /*如果是描述符链的第一个描述符，则需要确定是amdpu描述链还是mpdu描述符链*/
            if (OAL_TRUE == en_dscr_list_first_flag)
            {
                en_dscr_list_is_ampdu = (0 == pst_tx_dscr->bit_is_ampdu)? OAL_FALSE : OAL_TRUE;
            }

            /* 如果是ampdu链的第一个描述符，或者是mpdu链的第一个未处理描述符 */
            if (((OAL_TRUE == en_dscr_list_is_ampdu) &&  (OAL_TRUE == en_dscr_list_first_flag))
                 || (OAL_FALSE == en_dscr_list_is_ampdu))
            {
                /* 获取发送状态位 */
                hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);

                /* 如果硬件没有发送，或者发生状态为9(软件需要再次挂到硬件，硬件才能发送)，软件需要放回TID队列 */
                if ((DMAC_TX_INVALID == uc_dscr_status)||(DMAC_TX_PENDING == uc_dscr_status))
                {
                    /* 从硬件队列删除ppdu后，需要将ppducnt减1 */
                    pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt
                                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt, 1);

                    en_dscr_list_back_flag = OAL_TRUE;  /*指示AMPDU链需要放回TID队列， MPDU链不需要使用*/
                    en_curr_dscr_back_flag = OAL_TRUE;  /*指示本描述符需要放回TID队列， AMPDU链/MPDU链都要使用*/
                }
                else /*已经发送过的AMPDU链， 或者MPDU链中的元素， 不需要放回tid队列*/
                {
                    en_dscr_list_back_flag = OAL_FALSE; /*指示AMPDU链不需要放回TID队列， MPDU链不需要使用*/
                    en_curr_dscr_back_flag = OAL_FALSE; /*指示本描述符不需要放回TID队列， AMPDU链/MPDU链都要使用*/

                    /*
                        MPDU描述符链，发送过的MPDU的next指针要指向空，防止后续硬件未发送的帧重新挂到硬件时，
                        已发送的最后一个帧的next指向了新挂进来的第一帧，造成无法正确找到新挂到硬件的第一帧。
                        AMPDU没有此问题。
                    */
                    if(OAL_FALSE == en_dscr_list_is_ampdu)
                    {
                        hal_tx_ctrl_dscr_unlink(pst_hal_device, pst_tx_dscr);
                    }
                }

            }
            else /*AMPDU的后续帧处理与AMPDU的第一帧保持一致*/
            {
                en_curr_dscr_back_flag = en_dscr_list_back_flag;
            }

            /*根据flag指示， 将描述从dev队列中删除，放入临时队列中*/
            if (OAL_TRUE == en_curr_dscr_back_flag)
            {
                /* 将device队列中的描述符删除 */
                oal_dlist_delete_entry(&pst_tx_dscr->st_entry);

                /* 设置软件重发标记 */
                pst_tx_dscr->bit_is_retried = OAL_TRUE;
                MAC_GET_CB_RETRIED_NUM(pst_cb)++;

                /* 将描述符放入临时队列，待统一增加到tid头部 */
                oal_dlist_add_tail(&pst_tx_dscr->st_entry, &ast_pending_q[mac_get_cb_tid(pst_cb)]);
                /* 统计每一个临时变量的mpdu个数 */
                auc_mpdu_num[mac_get_cb_tid(pst_cb)]++;
            }

            /* 获取新的dscr list开始 */
            hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr, &pst_tx_dscr_next);
            en_dscr_list_first_flag = (pst_tx_dscr_next == OAL_PTR_NULL) ? OAL_TRUE : OAL_FALSE;
        }
    }

    /* 将临时队列中的mpdu插入tid的头部 */
    for (uc_tid = 0; uc_tid < WLAN_TID_MAX_NUM; uc_tid++)
    {
        if (oal_dlist_is_empty(&ast_pending_q[uc_tid]))
        {
            continue;
        }
        pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

        ul_ret = dmac_tid_tx_queue_enqueue_head(pst_tid_queue, &ast_pending_q[uc_tid], auc_mpdu_num[uc_tid]);
        if (OAL_SUCC == ul_ret)
        {
            pst_tid_queue->uc_retry_num += auc_mpdu_num[uc_tid];
            /* 入队成功时需要通知算法 */
            dmac_alg_tid_update_notify(pst_tid_queue);
            OAM_INFO_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                          "{dmac_psm_flush_txq_to_tid:: uc_tid[%d] mpdu_num[%d]} OK!", uc_tid, auc_mpdu_num[uc_tid]);
        #ifdef _PRE_WLAN_DFT_STAT
            if (OAL_PTR_NULL != pst_tid_queue->pst_tid_stats)
            {
                DMAC_TID_STATS_INCR(pst_tid_queue->pst_tid_stats->ul_tid_retry_enqueue_cnt, auc_mpdu_num[uc_tid]);
            }
        #endif
        }
        else
        {
            /* 入队失败需要设置ba会话标志位 */
            pst_ba_hdl = pst_tid_queue->pst_ba_tx_hdl;
            if (OAL_PTR_NULL != pst_ba_hdl)
            {
                OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &ast_pending_q[uc_tid])
                {
                    pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                    hal_tx_get_dscr_seq_num(pst_hal_device, pst_tx_dscr, &us_seq_num);
                    dmac_ba_update_baw(pst_ba_hdl, us_seq_num);
                }
            }

            pst_dmac_vap->st_vap_base_info.st_vap_stats.ul_tx_dropped_packets += auc_mpdu_num[uc_tid];
            OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_flush_txq_to_tid::uc_tid[%d] mpdu_num[%d]} failed[%d].}", uc_tid, auc_mpdu_num[uc_tid], ul_ret);
            dmac_tx_excp_free_dscr(&ast_pending_q[uc_tid], pst_hal_device);
        }
    }

    /* 将VO队列中的组播\广播帧也需要回收到当前vap下的组播用户的对应tid里面 */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].st_header)
    {
        pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        pst_cb       = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_tx_dscr->pst_skb_start_addr);

        /* 如果是组播\广播帧，并且属于当前vap(入参vap)，则回收到vap的组播用户的tid里面 */
        if ((OAL_TRUE != MAC_GET_CB_IS_MCAST(pst_cb)) || (MAC_GET_CB_TX_VAP_INDEX(pst_cb) == pst_dmac_vap->st_vap_base_info.uc_vap_id))
        {
            continue;
        }

        /* 从硬件队列拿下来的mcast和bcast放回相应的vap的组播用户的相应tid队列 */
        pst_mcast_user = mac_res_get_dmac_user(MAC_GET_CB_TX_USER_IDX(pst_cb));
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mcast_user))
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_flush_txq_to_tid::pst_mcast_user is null.}");
            continue;
        }
        /* 将该mpdu从硬件队列拿下来，并将ppducnt减1 */
        oal_dlist_delete_entry(&pst_tx_dscr->st_entry);
        pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].uc_ppdu_cnt
                = OAL_SUB(pst_hal_device->ast_tx_dscr_queue[HAL_TX_QUEUE_VO].uc_ppdu_cnt, 1);

        pst_tid_queue = &pst_mcast_user->ast_tx_tid_queue[mac_get_cb_tid(pst_cb)];
    #ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
        pst_tx_dscr->bit_is_retried = OAL_TRUE;
        /* 入重传队列 */
        oal_dlist_join_head(&pst_tid_queue->st_retry_q, &pst_tx_dscr->st_entry);
    #else
        oal_dlist_add_head(&pst_tx_dscr->st_entry, &pst_tid_queue->st_hdr);
    #endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */

        /* 更新tid信息，可以使用dmac_tid_tx_queue_enqueue_head进行优化 */
        pst_tid_queue->us_mpdu_num++;
        pst_mac_device->us_total_mpdu_num++;
        pst_mac_device->aus_vap_mpdu_num[pst_tid_queue->uc_vap_id]++;
        pst_mac_device->aus_ac_mpdu_num[WLAN_WME_TID_TO_AC(pst_tid_queue->uc_tid)]++;
        if (OAL_TRUE == pst_tx_dscr->bit_is_retried)
        {
            pst_tid_queue->uc_retry_num++;
        }

    #ifdef _PRE_WLAN_FEATURE_FLOWCTL
        dmac_alg_flowctl_backp_notify(&pst_dmac_vap->st_vap_base_info,
                                      pst_mac_device->us_total_mpdu_num,
                                      pst_mac_device->aus_ac_mpdu_num);
    #endif

    }
    /* 清空硬件发送队列，并重新将各队列通知mac */
    hal_clear_hw_fifo(pst_hal_device);

    /*将还没有来得及处理的描述符挂回给硬件， 软件ppdu num不需要修改*/
    for (uc_q_idx = 0; uc_q_idx < HAL_TX_QUEUE_BUTT; uc_q_idx++)
    {
        oal_bool_enum en_dscr_list_is_ampdu   = OAL_FALSE;  /*当前挂给硬件的描述符链类型是否是ampdu类型*/
        oal_bool_enum en_dscr_list_first_flag = OAL_TRUE;   /*是否是描述符链的第一个描述符*/
        oal_bool_enum en_mpdu_list_put_flag   = OAL_FALSE;  /*表示mpdu描述符链是否已经挂给硬件*/

        OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header)
        {
            pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
            if (OAL_TRUE == en_dscr_list_first_flag)
            {
                en_dscr_list_is_ampdu = (0 == pst_tx_dscr->bit_is_ampdu)? OAL_FALSE : OAL_TRUE;
                en_mpdu_list_put_flag = OAL_FALSE;
            }

            /*如果是ampdu链的第一个描述符， 或者是mpdu链的第一个未处理描述符，则需要处理*/
            if (((OAL_TRUE == en_dscr_list_is_ampdu) && (OAL_TRUE == en_dscr_list_first_flag))
               || ((OAL_FALSE == en_dscr_list_is_ampdu) && (OAL_FALSE == en_mpdu_list_put_flag)))
            {
                /* 获取发送状态位 */
                hal_tx_get_dscr_status(pst_hal_device, pst_tx_dscr, &uc_dscr_status);

                /* 如果硬件没有发送，软件需要重新通知到硬件FIFO */
                /* 如果硬件已经发送，软件不需要通知到硬件FIFO，等着中断上来直接处理 */
                if ((DMAC_TX_INVALID == uc_dscr_status)||(DMAC_TX_PENDING == uc_dscr_status))
                {
                    hal_tx_put_dscr(pst_hal_device, uc_q_idx, pst_tx_dscr);
                    if (OAL_FALSE == en_dscr_list_is_ampdu)
                    {
                        en_mpdu_list_put_flag = OAL_TRUE;
                    }
                }
            }

            /* 获取新的dscr list开始 */
            hal_get_tx_dscr_next(pst_hal_device, pst_tx_dscr, &pst_tx_dscr_next);
            en_dscr_list_first_flag = (pst_tx_dscr_next == OAL_PTR_NULL) ? OAL_TRUE : OAL_FALSE;
        }
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 函 数 名  : dmac_psm_reset
 功能描述  : 复位一个用户的节能状态
             1) 用户状态置为不节能
             2) 清空用户节能队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月19日
    作    者   : zhangheng
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_reset(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    oal_uint16              *pus_user_id;
    dmac_user_stru          *pst_dmac_user;
    dmac_vap_stru           *pst_dmac_vap;
    oal_int32                ul_uapsd_qdepth = 0;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_macdev;
#endif

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_reset::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    pus_user_id     = (oal_uint16 *)pst_event->auc_event_data;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(*pus_user_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::pst_dmac_user null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
    {
        /* 用户是非节能的，直接返回成功 */

        return OAL_SUCC;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif
    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_PWR, "{dmac_psm_reset::user changes ps mode to active.}");

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_FALSE);


    /* 问题单号:DTS2014121207447 修改用户在节能情况下，不去关联直接重新认证、关联导致节能状态未清除 */
    pst_dmac_vap->uc_ps_user_num = OAL_SUB(pst_dmac_vap->uc_ps_user_num, 1);    /* 节能用户个数清除 */
    dmac_user_resume(pst_dmac_user);                                            /* 恢复user，恢复该user的每一个tid */
    dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);                  /* 该修改体现在beacon中的信息 */


    dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_user);
#ifdef _PRE_WLAN_FEATURE_UAPSD
    ul_uapsd_qdepth = dmac_uapsd_flush_queue(pst_dmac_vap, pst_dmac_user);
    if(ul_uapsd_qdepth < 0)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_uapsd_flush_queue:: return value is -1.}");
        return OAL_FAIL;
    }
    /*uc_uapsd_send = dmac_uapsd_flush_queue(pst_dmac_vap, pst_dmac_user, &uc_uapsd_left);
    OAM_INFO_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_reset::dmac_uapsd_flush_queue %d send & %d left}", uc_uapsd_send, uc_uapsd_left);*/
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_process_user_awake
 功能描述  : user从节能状态转化为非节能状态时ap的相关处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月22日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_psm_awake(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru     *pst_macdev;
#endif

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_FALSE);

    pst_dmac_vap->uc_ps_user_num--;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif
    /* 恢复user，恢复该user的每一个tid */
    dmac_user_resume(pst_dmac_user);

    /* 将所有的缓存帧发送出去 */
    dmac_psm_queue_flush(pst_dmac_vap, pst_dmac_user);

    OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_awake::user[%d] is active.}\r\n", pst_dmac_user->st_user_base_info.us_assoc_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_process_user_doze
 功能描述  : 用户进入节能状态，ap做相应的一些处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月22日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_psm_doze(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    mac_device_stru     *pst_macdev;

    DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_TRUE);

    pst_dmac_vap->uc_ps_user_num++;

    /* suspend硬件队列 */
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#else
    hal_set_machw_tx_suspend(pst_macdev->pst_device_stru);
#endif
    /* pause该用户,但是不能pause uapsd专用tid */
    dmac_user_pause(pst_dmac_user);
    dmac_tid_resume(pst_macdev->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[WLAN_TIDNO_UAPSD], DMAC_TID_PAUSE_RESUME_TYPE_PS);


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* 遍历硬件队列，将属于该用户的帧都放回psm */
    dmac_psm_enable_user_to_psm_back(pst_dmac_vap, pst_macdev, pst_dmac_user);
    /* 如果psm不为空，则设置PVB */
    if ((OAL_FALSE == dmac_psm_is_psm_empty(pst_dmac_user))
        || (OAL_FALSE == dmac_psm_is_tid_empty(pst_dmac_user)))
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_doze::user[%d].%d mpdu in tid.}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num));
    }
#else
    /* 遍历硬件队列，将属于该用户的帧都放回tid */
    dmac_psm_flush_txq_to_tid(pst_macdev, pst_dmac_vap, pst_dmac_user);

    /* 如果tid不为空，则设置PVB */
    if (OAL_FALSE == dmac_psm_is_tid_empty(pst_dmac_user))
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 1);
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_doze::user[%d].%d mpdu in tid.}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, dmac_psm_tid_mpdu_num(pst_dmac_user));
    }
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#else
    /* 恢复硬件队列 */
    hal_set_machw_tx_resume(pst_macdev->pst_device_stru);
#endif

    OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR,
                  "{dmac_psm_doze::user[%d] is doze.}\r\n", pst_dmac_user->st_user_base_info.us_assoc_id);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_rx_process_data
 功能描述  : AP接收到数据帧后，要对帧头的节能位进行检查，修改相应的用户节能
             模式，并决定是否需要发送缓存帧
 输入参数  : pst_dmac_vap
             pst_dmac_user
             pst_net_buf
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月10日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_void dmac_psm_rx_process(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf)
{
    mac_ieee80211_frame_stru        *pst_mac_header;
    mac_rx_ctl_stru                 *pst_rx_ctrl;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap || OAL_PTR_NULL == pst_dmac_user || OAL_PTR_NULL == pst_net_buf))
    {
        OAM_ERROR_LOG3(0, OAM_SF_PWR, "{dmac_psm_rx_process_data::param is null.vap=[%d], user=[%d],buf=[%d]}.",
                       (oal_uint32)pst_dmac_vap, (oal_uint32)pst_dmac_user, (oal_uint32)pst_net_buf);
        return;
    }

    pst_rx_ctrl = (mac_rx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    pst_mac_header = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(pst_rx_ctrl);
    /*
       如果节能位开启(bit_power_mgmt == 1),同时之前处于非节能模式，则修改节能
       模式为节能,否则什么都不做，因为用户仍在节能，ap继续为其缓存帧就可以了;
       如果节能位关闭(bit_power_mgmt == 0),同时之前处于节能模式，则修改节能模
       式为非节能，并且将相应节能队列中的所有缓存帧都发给该用户，否则，什么都
       不做，用户一直都是非节能的，ap与用户之间正常收发数据
    */
    if ((OAL_TRUE == pst_mac_header->st_frame_control.bit_power_mgmt)
         && (OAL_FALSE == pst_dmac_user->bit_ps_mode))
    {
        dmac_psm_doze(pst_dmac_vap, pst_dmac_user);
    }
    if ((OAL_FALSE == pst_mac_header->st_frame_control.bit_power_mgmt)
         && (OAL_TRUE == pst_dmac_user->bit_ps_mode))
    {
        dmac_psm_awake(pst_dmac_vap, pst_dmac_user);
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P GO关连设备停止节能，P2P OppPS暂停*/
    if ((OAL_FALSE == pst_mac_header->st_frame_control.bit_power_mgmt)&&
        (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        pst_dmac_vap->st_p2p_ops_param.en_pause_ops = OAL_TRUE;
    }
    /* P2P GO关连设备使能节能，允许P2P OppPS*/
    if ((OAL_TRUE == pst_mac_header->st_frame_control.bit_power_mgmt)&&
        (IS_P2P_GO(&pst_dmac_vap->st_vap_base_info))&&
        (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
    {
        pst_dmac_vap->st_p2p_ops_param.en_pause_ops = OAL_FALSE;

    }

#endif
}

/*****************************************************************************
 函 数 名  : dmac_psm_set_ucast_mgmt_tx_rate
 功能描述  : 设置vap结构体下单播管理帧发送速率
 输入参数  : dmac_vap_stru *pst_dmac_vap,
             wlan_channel_band_enum_uint8 en_band,
             oal_uint8 uc_legacy_rate,
             wlan_phy_protocol_enum_uint8 en_protocol_mode
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月6日
    作    者   : l00279018
    修改内容   : 新生成函数

*****************************************************************************/
OAL_INLINE oal_void dmac_psm_set_ucast_mgmt_tx_rate(dmac_vap_stru *pst_dmac_vap,
                                                    wlan_channel_band_enum_uint8 en_band,
                                                    oal_uint8 uc_legacy_rate,
                                                    wlan_phy_protocol_enum_uint8 en_protocol_mode)
{
    oal_uint8 uc_loop;
    /* 参数合法性检查 */
    if ((OAL_PTR_NULL == pst_dmac_vap) || (en_band >= WLAN_BAND_BUTT))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "{dmac_psm_set_ucast_mgmt_tx_rate::input param error, pst_dmac_vap[%p], band[%d].}",
                       pst_dmac_vap, en_band);
        return;
    }

    pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = en_protocol_mode;
    for (uc_loop = 1; uc_loop < HAL_TX_RATE_MAX_NUM; uc_loop++)
    {
        pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[uc_loop].ul_value = pst_dmac_vap->ast_tx_mgmt_ucast[en_band].ast_per_rate[0].ul_value;
    }
    return;
}

/*****************************************************************************
 函 数 名  : dmac_psm_send_null_data_ap
 功能描述  : 1.ap收到ps-poll，节能队列为空，ap向sta发送Null Data
             2.ap定时KeepAlive流程
 输入参数  : pst_dmac_vap
             pst_dmac_user
 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32  dmac_psm_send_null_data(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_bool_enum_uint8 en_ps)
{
    oal_netbuf_stru                 *pst_net_buf;
    mac_tx_ctl_stru                 *pst_tx_ctrl;
    oal_uint32                       ul_ret;
    oal_uint16                       us_tx_direction = WLAN_FRAME_FROME_AP;
    mac_ieee80211_frame_stru        *pst_mac_header;
    oal_uint8                        uc_legacy_rate;
    wlan_phy_protocol_enum_uint8     en_protocol_mode;
    oal_uint8                        uc_null_protocol_mode;
    oal_uint8                        uc_null_legacy_rate;
    mac_device_stru                 *pst_mac_device;

    /* begin: DTS2015042504620 ,解决null 帧发错信道，修改为扫描状态不发送null 帧 */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                        "dmac_psm_send_null_data: mac_device is null.device_id[%d]",
                        pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
        (MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state))
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                        "dmac_psm_send_null_data: device is scaning and vap status is pause, do not send null!vap_mode[%d]",
                        pst_dmac_vap->st_vap_base_info.en_vap_mode);
        return OAL_FAIL;
    }
    /* end: DTS2015042504620 ,解决null 帧发错信道，修改为扫描状态不发送null 帧 */

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_DEV_MODE == mac_get_p2p_mode(&pst_dmac_vap->st_vap_base_info))
    {
        return OAL_FAIL;
    }
#endif

    /* 申请net_buff */
    pst_net_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_net_buf)
    {
        /* DTS2015101302075 staut要保证null内存可以申请到,error级别 */
        /* DTS2015111903929 BT和WLAN共存进行iperf冲包，1)Beacon帧中携带PVB不正常
        2)STAUT醒来的情况下Beacon中携带PVB置为1，发送nulldata失败，分析无影响，将日志降级 */
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_psm_send_null_data::pst_net_buf null.}");
        /* device netbuf 申请不到维测，以后删除， l00324381 20150902 */
        OAL_MEM_INFO_PRINT(OAL_MEM_POOL_ID_NETBUF);
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEM_NETBUF_TRACE(pst_net_buf, OAL_TRUE);

    oal_set_netbuf_prev(pst_net_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_net_buf, OAL_PTR_NULL);

    /* null帧发送方向From AP || To AP */
    us_tx_direction = (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) ? WLAN_FRAME_FROME_AP : WLAN_FRAME_TO_AP;
    /* 填写帧头,其中from ds为1，to ds为0，因此frame control的第二个字节为02 */
    mac_null_data_encap(OAL_NETBUF_HEADER(pst_net_buf),
                        ((oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_NODATA) | us_tx_direction),
                        pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                        pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    pst_mac_header = (mac_ieee80211_frame_stru*)OAL_NETBUF_HEADER(pst_net_buf);

    /*  NB: power management bit is never sent by an AP */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_mac_header->st_frame_control.bit_power_mgmt = en_ps;
    }

    /* 填写cb字段 */
    pst_tx_ctrl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_net_buf);
    OAL_MEMZERO(pst_tx_ctrl, OAL_SIZEOF(mac_tx_ctl_stru));

    /* 填写tx部分 */
    mac_set_cb_ack_policy(pst_tx_ctrl, WLAN_TX_NORMAL_ACK);
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctrl)         = FRW_EVENT_TYPE_WLAN_DTX;
    mac_set_cb_is_bar(pst_tx_ctrl, OAL_FALSE);
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctrl)         = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctrl)           = 0;
    mac_set_cb_tid(pst_tx_ctrl, WLAN_TID_FOR_DATA);
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctrl)          = pst_dmac_vap->st_vap_base_info.uc_vap_id;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctrl)           = (oal_uint8) pst_dmac_user->st_user_base_info.us_assoc_id;

    /* 填写tx rx公共部分 */
    //MAC_GET_CB_FRAME_TYPE(pst_tx_ctrl)          = WLAN_DATA_NULL;
    MAC_GET_CB_IS_MCAST(pst_tx_ctrl)            = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctrl, OAL_FALSE);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    /* DTS2015082808094 1102 aput keepalive, null data tx cb is_get_from_ps_queue 赋值为FALSE */
    if (IS_AP(&(pst_dmac_vap->st_vap_base_info)))
    {
        MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_FALSE;/* AP 发送null 帧放入节能队列 */
    }
    else
#endif  /* (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV) */
    {
        MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctrl)   = OAL_TRUE;
    }
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctrl)       = OAL_FALSE;
    mac_set_cb_is_use_4_addr(pst_tx_ctrl, OAL_FALSE);
    mac_set_cb_frame_hdr(pst_tx_ctrl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_net_buf));
    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctrl)    = OAL_SIZEOF(mac_ieee80211_frame_stru);
    MAC_GET_CB_MPDU_NUM(pst_tx_ctrl)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctrl)             = 1;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctrl)               = 0;
    mac_set_cb_ac(pst_tx_ctrl, WLAN_WME_AC_MGMT);


    /* 2.4G初始化为11b 1M, long preable, 发送null帧时修改为11g/a的速率 */
    uc_legacy_rate   = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate;
    en_protocol_mode = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode;
    dmac_change_null_data_rate(pst_dmac_vap,pst_dmac_user,&uc_null_protocol_mode, &uc_null_legacy_rate);

    dmac_psm_set_ucast_mgmt_tx_rate(pst_dmac_vap, WLAN_BAND_2G, uc_null_legacy_rate, uc_null_protocol_mode);

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_net_buf, OAL_SIZEOF(mac_ieee80211_frame_stru));

    /* 发送完成后恢复默认值: 2.4G初始化为11b 1M, long preable */
    dmac_psm_set_ucast_mgmt_tx_rate(pst_dmac_vap, WLAN_BAND_2G, uc_legacy_rate, en_protocol_mode);

    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_send_null_data::dmac_tx_mgmt failed[%d].}", ul_ret);
        if (OAL_LIKELY(OAL_PTR_NULL != pst_dmac_user->st_ps_structure.pst_psm_stats))
        {
            DMAC_PSM_STATS_INCR(pst_dmac_user->st_ps_structure.pst_psm_stats->ul_psm_send_null_fail_cnt);
        }

        dmac_tx_excp_free_netbuf(pst_net_buf);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_sch_tid_queue
 功能描述  : 收到sta发的pspoll，tid里面有数据，调度一个发出去，
             如果tid中还有其他数据或者psm队列不为空。设置moredata标志
 输入参数  : l_ps_mpdu_num psm节能队列中缓存的数据个数
 输出参数  : puc_more_data 发完一帧后，tid队列或者psm节能队列中还有更多的数据
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月26日
    作    者   : z00237171
    修改内容   : 新生成函数
  2.日    期   : 2014年11月25日
    作    者   : g00260350
    修改内容   : 增加设置moredata操作并返回moredata值，以便设置bitmap

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_psm_sch_tid_queue(dmac_user_stru  *pst_dmac_user, oal_uint32 ul_ps_mpdu_num)
{
    mac_device_stru              *pst_macdev         = OAL_PTR_NULL;
    oal_dlist_head_stru          *pst_dlist_pos      = OAL_PTR_NULL;
    hal_tx_dscr_stru             *pst_tx_dscr        = OAL_PTR_NULL;
    oal_netbuf_stru              *pst_mgmt_buf       = OAL_PTR_NULL;
    oal_uint8                     uc_tid_idx         = 0;
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    dmac_tid_stru                *pst_txtid;
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    pst_macdev = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_sch_tid_queue:: mac_device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    /* 先遍历重传队列 */
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        pst_txtid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx];
        if (OAL_TRUE == oal_dlist_is_empty(&pst_txtid->st_retry_q))
        {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_txtid->st_retry_q)
        {
            /* 发送的是该用户任意非空TID队列中的第一个 */
            dmac_tid_resume(pst_macdev->pst_device_stru, pst_txtid, DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* 节能队列非空或该用户TID队列还有其他mpdu，需要设置moredata */
            if (ul_ps_mpdu_num > 1)
            {
                pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
                dmac_psm_set_more_data(pst_mgmt_buf);
            }

            return OAL_SUCC;
        }
    }


    /* 再遍历缓存队列 */
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        pst_txtid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx];
        if (OAL_TRUE == oal_netbuf_list_empty(&pst_txtid->st_buff_head))
        {
            continue;
        }

        OAL_NETBUF_SEARCH_FOR_EACH(pst_mgmt_buf, &pst_txtid->st_buff_head)
        {
            /* 发送的是该用户任意非空TID队列中的第一个 */
            dmac_tid_resume(pst_macdev->pst_device_stru, pst_txtid, DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* 节能队列非空或该用户TID队列还有其他mpdu，需要设置moredata */
            if (ul_ps_mpdu_num > 1)
            {
                dmac_psm_set_more_data(pst_mgmt_buf);
            }

            return OAL_SUCC;
        }
    }
#else
    for (uc_tid_idx = 0; uc_tid_idx < WLAN_TID_MAX_NUM; uc_tid_idx ++)
    {
        if (OAL_TRUE == oal_dlist_is_empty(&pst_dmac_user->ast_tx_tid_queue[uc_tid_idx].st_hdr))
        {
            continue;
        }
        OAL_DLIST_SEARCH_FOR_EACH(pst_dlist_pos, &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx].st_hdr)
        {
            /* 发送的是该用户任意非空TID队列中的第一个 */
            dmac_tid_resume(pst_macdev->pst_device_stru, &pst_dmac_user->ast_tx_tid_queue[uc_tid_idx], DMAC_TID_PAUSE_RESUME_TYPE_PS);

            /* 节能队列非空或该用户TID队列还有其他mpdu，需要设置moredata */
            if (ul_ps_mpdu_num > 1)
            {
                pst_tx_dscr  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
                pst_mgmt_buf = pst_tx_dscr->pst_skb_start_addr;
                dmac_psm_set_more_data(pst_mgmt_buf);
            }
            break;
        }
    }
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_sch_psm_queue
 功能描述  : 收到sta的pspoll，tid为空，从节能队列调度一个包出来发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月26日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_psm_sch_psm_queue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru  *pst_dmac_user)
{
    oal_int32              l_ps_mpdu_num;
    oal_uint32             ul_ret;

    l_ps_mpdu_num       = oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);

    if (l_ps_mpdu_num > 0)
    {
        ul_ret = dmac_psm_queue_send(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG3(0, OAM_SF_PWR, "{dmac_psm_sch_psm_queue::user[%d] send fail[%d] & %d left.}",
                           pst_dmac_user->st_user_base_info.us_assoc_id, ul_ret, l_ps_mpdu_num - 1);
            return ul_ret;
        }
        OAM_INFO_LOG2(0, OAM_SF_PWR, "{dmac_psm_sch_psm_queue::user[%d] send 1 & %d left}",
                       pst_dmac_user->st_user_base_info.us_assoc_id, l_ps_mpdu_num - 1);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : dmac_psm_handle_pspoll
 功能描述  : ap收到sta的pspoll，缓存不为空，回复一个缓存帧
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月23日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_psm_handle_pspoll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru  *pst_dmac_user, oal_uint8 *puc_extra_qosnull)
{
    oal_uint32                    ul_ret            = OAL_SUCC;
    oal_uint32                    ul_tid_mpud_num   = 0;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    mac_device_stru             *pst_macdev;
#endif

    /* 如果tid不为空 */
    ul_tid_mpud_num  = dmac_psm_tid_mpdu_num(pst_dmac_user);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_macdev = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_macdev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_doze:: mac_dev is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
    dmac_psm_disable_user_to_psm_back(pst_macdev,pst_dmac_user);
#endif

    if (ul_tid_mpud_num)
    {
        ul_tid_mpud_num += (oal_uint32)oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num);
        ul_ret = dmac_psm_sch_tid_queue(pst_dmac_user, ul_tid_mpud_num);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(0, OAM_SF_PWR, "{dmac_psm_handle_pspoll::dmac_psm_sch_tid_queue fail[%d].}", ul_ret);
            return ul_ret;
        }
        if (ul_tid_mpud_num == 1)
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
    }
    /* 如果psm节能不为空 */
    else if(oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num))
    {
        ul_ret = dmac_psm_sch_psm_queue(pst_dmac_vap, pst_dmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR, "{dmac_psm_handle_pspoll::dmac_psm_sch_psm_queue fail[%d].}", ul_ret);
            return ul_ret;
        }
        if (0 == oal_atomic_read(&pst_dmac_user->st_ps_structure.uc_mpdu_num))
        {
            dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        }
    }
    else
    {
        *puc_extra_qosnull = 1;
        return OAL_SUCC;
    }
    pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing = OAL_TRUE;

    return ul_ret;
}

/*****************************************************************************
 函 数 名  : dmac_psm_resv_ps_poll
 功能描述  : ap收到sta发的ps-poll，从相应的节能队列中取出一个缓存帧（mpdu）
             发给sta，如果节能队列为空，则发送一个Null Data给sta。并设置相应
             的more data位和tim_bitmap
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月4日
    作    者   : z00237171
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_resv_ps_poll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user)
{
    oal_uint32          ul_ret;
    oal_uint8           uc_extra_qosnull = 0;
#ifdef _PRE_WLAN_DFT_STAT
    dmac_user_psm_stats_stru *pst_psm_stats;

    pst_psm_stats = pst_dmac_user->st_ps_structure.pst_psm_stats;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_psm_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "{dmac_psm_resv_ps_poll::psm_stats is null!.}");
        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

    /* 检查vap模式 */
    if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::ap is not in ap mode.}");
        return OAL_SUCC;
    }

    /* 检查是否有ps-poll没处理完，如果有，则忽略当前的ps-poll，直接返回 */
    if (OAL_TRUE == pst_dmac_user->st_ps_structure.en_is_pspoll_rsp_processing)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::ignor excess ps-poll.}");
        return OAL_SUCC;
    }

    ul_ret = dmac_psm_handle_pspoll(pst_dmac_vap, pst_dmac_user, &uc_extra_qosnull);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                         "{dmac_psm_resv_ps_poll::hand_pspoll return [%d].}", ul_ret);
        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_rsp_pspoll_fail_cnt);
        return ul_ret;
    }

    if (uc_extra_qosnull)
    {
        dmac_psm_set_local_bitmap(pst_dmac_vap, pst_dmac_user, 0);
        DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_resv_pspoll_send_null);
        ul_ret = dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR,
                             "{dmac_psm_resv_ps_poll::user[%d] send_null fail[%d].}", ul_ret);
        }
        return ul_ret;
    }

    DMAC_PSM_STATS_INCR(pst_psm_stats->ul_psm_rsp_pspoll_succ_cnt);
    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 函 数 名  : dmac_psm_opmode_notify_process
 功能描述  : AP收到Operating Mode Notification帧，Power Management为1，需要通知DMAC修改用户的节能信息
             (如果当前用户的bit_ps_mode为TRUE,直接退出;如果为FALSE,设置bit_ps_mode为TRUE.)
 输入参数  : pst_event_mem事件指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月12日
    作    者   : z00241943
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 dmac_psm_opmode_notify_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    oal_uint16              *pus_user_id;
    dmac_user_stru          *pst_dmac_user;
    dmac_vap_stru           *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_event_mem is NULL!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* 获取事件、事件头以及事件payload结构体 */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);
    pus_user_id     = (oal_uint16 *)pst_event->auc_event_data;

    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(*pus_user_id);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_mac_user is null, user id is = [%d]!}\r\n", *pus_user_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_psm_opmode_notify_process::pst_dmac_vap is NULL!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_dmac_user->bit_ps_mode)
    {
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{mac_ie_proc_opmode_field::user changes ps mode to powersave!}\r\n");
        DMAC_PSM_CHANGE_USER_PS_STATE(pst_dmac_user->bit_ps_mode, OAL_TRUE);
        pst_dmac_vap->uc_ps_user_num++;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 函 数 名  : dmac_change_null_data_rate
 功能描述  : 1.根据不同的协议模式更改null frame 的速率
 输入参数  : pst_dmac_vap

 输出参数  : 无
 返 回 值  : OAL_SUCC或者其它错误码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月19日
    作    者   : c00221210
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  dmac_change_null_data_rate(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 *uc_protocol_mode,oal_uint8 *uc_legacy_rate)
{
    switch (pst_dmac_user->st_user_base_info.en_avail_protocol_mode)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
            if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
            {
                *uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                *uc_legacy_rate   = 0x1;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P 设备接收到管理帧 */
                if (!IS_LEGACY_VAP((&pst_dmac_vap->st_vap_base_info)))
                {
                    *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                    *uc_legacy_rate   = 0xB;
                }
#endif
            }
            else
            {
                *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                *uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            *uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            *uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            *uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_change_null_data_rate::invalid en_protocol[%d].}", pst_dmac_user->st_user_base_info.en_avail_protocol_mode);
            return;
    }


}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

