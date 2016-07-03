


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "oal_mem.h"
#include "oal_net.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"
//#include "mac_regdomain.h"
#include "mac_data.h"
//#include "mac_frame.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_DATA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

 OAL_INLINE oal_bool_enum_uint8 mac_is_dhcp_port(udp_hdr_stru *pst_udp_hdr)
{
    if (OAL_NET2HOST_SHORT(pst_udp_hdr->us_des_port) == 67
        || OAL_NET2HOST_SHORT(pst_udp_hdr->us_des_port) == 68)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}



oal_bool_enum_uint8 mac_is_nd(oal_ipv6hdr_stru  *pst_ipv6hdr)
{
    oal_icmp6hdr_stru      *pst_icmp6hdr;

    if (OAL_IPPROTO_ICMPV6 == pst_ipv6hdr->nexthdr)
    {
        pst_icmp6hdr = (oal_icmp6hdr_stru *)(pst_ipv6hdr + 1);

        if((MAC_ND_RSOL == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_RADVT == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_NSOL == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_NADVT == pst_icmp6hdr->icmp6_type) ||
            (MAC_ND_RMES == pst_icmp6hdr->icmp6_type))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}


oal_bool_enum_uint8 mac_is_dhcp6(oal_ipv6hdr_stru  *pst_ipv6hdr)
{
    udp_hdr_stru           *pst_udp_hdr;

    if (MAC_UDP_PROTOCAL == pst_ipv6hdr->nexthdr)
    {
        pst_udp_hdr = (udp_hdr_stru *)(pst_ipv6hdr + 1);

        if (pst_udp_hdr->us_des_port == OAL_HOST2NET_SHORT(MAC_IPV6_UDP_DES_PORT)
            || pst_udp_hdr->us_des_port == OAL_HOST2NET_SHORT(MAC_IPV6_UDP_SRC_PORT))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

OAL_STATIC mac_data_type_enum_uint8 mac_get_arp_type_by_arphdr(oal_eth_arphdr_stru  *pst_rx_arp_hdr)
{
    if (MAC_ARP_REQUEST == OAL_NET2HOST_SHORT(pst_rx_arp_hdr->us_ar_op))
    {
        return MAC_DATA_ARP_REQ;
    }
    else if (MAC_ARP_RESPONSE == OAL_NET2HOST_SHORT(pst_rx_arp_hdr->us_ar_op))
    {
        return MAC_DATA_ARP_RSP;
    }

    return MAC_DATA_BUTT;

}


oal_uint8 mac_get_data_type_from_8023(oal_uint8 *puc_frame_hdr, mac_netbuff_payload_type uc_hdr_type)
{

    mac_ip_header_stru     *pst_ip;
    udp_hdr_stru           *pst_udp_hdr;
    oal_uint8              *puc_frame_body;
    oal_uint16              us_ether_type;
    oal_uint8               uc_datatype = MAC_DATA_BUTT;

    if (OAL_PTR_NULL == puc_frame_hdr)
    {
        return uc_datatype;
    }

    if (MAC_NETBUFF_PAYLOAD_ETH == uc_hdr_type)
    {
        us_ether_type  = ((mac_ether_header_stru *)puc_frame_hdr)->us_ether_type;
        puc_frame_body = puc_frame_hdr + (oal_uint16)OAL_SIZEOF(mac_ether_header_stru);
    }
    else if (MAC_NETBUFF_PAYLOAD_SNAP == uc_hdr_type)
    {
        us_ether_type = ((mac_llc_snap_stru *)puc_frame_hdr)->us_ether_type;
        puc_frame_body = puc_frame_hdr + (oal_uint16)OAL_SIZEOF(mac_llc_snap_stru);
    }
    else
    {
        return uc_datatype;
    }

    switch (us_ether_type)
    {
        /*lint -e778*//* 屏蔽Info -- Constant expression evaluates to 0 in operation '&' */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_IP):
            /* 从IP TOS字段寻找优先级 */
            /*----------------------------------------------------------------------
                tos位定义
             ----------------------------------------------------------------------
            | bit7~bit5 | bit4 |  bit3  |  bit2  |   bit1   | bit0 |
            | 包优先级  | 时延 | 吞吐量 | 可靠性 | 传输成本 | 保留 |
             ----------------------------------------------------------------------*/
            pst_ip = (mac_ip_header_stru *)puc_frame_body;      /* 偏移一个以太网头，取ip头 */
            if (MAC_UDP_PROTOCAL == pst_ip->uc_protocol)
            {
                pst_udp_hdr = (udp_hdr_stru *)(pst_ip + 1);
                /* 如果是DHCP帧，则进入VO队列发送 */
                if (OAL_TRUE == mac_is_dhcp_port(pst_udp_hdr))
                {
                    uc_datatype = MAC_DATA_DHCP;
                }
            }
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6):
            /* 从IPv6 traffic class字段获取优先级 */
            /*----------------------------------------------------------------------
                IPv6包头 前32为定义
             -----------------------------------------------------------------------
            | 版本号 | traffic class   | 流量标识 |
            | 4bit   | 8bit(同ipv4 tos)|  20bit   |
            -----------------------------------------------------------------------*/
            /* 如果是ND帧，则进入VO队列发送 */
            if (OAL_TRUE == mac_is_nd((oal_ipv6hdr_stru *)puc_frame_body))
            {
                uc_datatype = MAC_DATA_ND;
            }

            /* 如果是DHCPV6帧 */
            else if (OAL_TRUE == mac_is_dhcp6((oal_ipv6hdr_stru *)puc_frame_body))
            {
                uc_datatype = MAC_DATA_DHCPV6;
            }

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_PAE):
            /* 如果是EAPOL帧，则进入VO队列发送 */
            uc_datatype = MAC_DATA_EAPOL; /* eapol */
            break;

        /* TDLS帧处理，建链保护，入高优先级TID队列 */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_TDLS):
            uc_datatype = MAC_DATA_TDLS;
            break;

        /* PPPOE帧处理，建链保护(发现阶段, 会话阶段)，入高优先级TID队列 */
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_DISC):
        case OAL_HOST2NET_SHORT(ETHER_TYPE_PPP_SES):
            uc_datatype = MAC_DATA_PPPOE;
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_WAI):
            uc_datatype = MAC_DATA_WAPI;
            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_VLAN):
            uc_datatype = MAC_DATA_VLAN;

            break;

        case OAL_HOST2NET_SHORT(ETHER_TYPE_ARP):
            /* 如果是ARP帧，则进入VO队列发送 */
            uc_datatype =  mac_get_arp_type_by_arphdr((oal_eth_arphdr_stru *)puc_frame_body);
            break;

        /*lint +e778*/
        default:
            uc_datatype = MAC_DATA_BUTT;
            break;
    }

    return uc_datatype;
}


oal_uint8 mac_get_data_type_from_80211(oal_netbuf_stru *pst_netbuff, oal_uint16 us_mac_hdr_len)
{
    oal_uint8               uc_datatype = MAC_DATA_BUTT;
    mac_llc_snap_stru      *pst_snap;

    if(OAL_PTR_NULL == pst_netbuff)
    {
        return MAC_DATA_BUTT;
    }

    pst_snap = (mac_llc_snap_stru *)(OAL_NETBUF_DATA(pst_netbuff) + us_mac_hdr_len);

    uc_datatype = mac_get_data_type_from_8023((oal_uint8 *)pst_snap, MAC_NETBUFF_PAYLOAD_SNAP);

    return uc_datatype;

}


oal_uint8 mac_get_data_type(oal_netbuf_stru *pst_netbuff)
{
    oal_uint8               uc_datatype = MAC_DATA_BUTT;
    mac_llc_snap_stru             *pst_snap;

    if(OAL_PTR_NULL == pst_netbuff)
    {
        return MAC_DATA_BUTT;
    }

    pst_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuff);
    if(OAL_PTR_NULL == pst_snap)
    {
        return MAC_DATA_BUTT;
    }

    uc_datatype = mac_get_data_type_from_8023((oal_uint8 *)pst_snap, MAC_NETBUFF_PAYLOAD_SNAP);

    return uc_datatype;

}


oal_uint16 mac_get_eapol_keyinfo(oal_netbuf_stru *pst_netbuff)
{
    oal_uint8                      uc_datatype = MAC_DATA_BUTT;
    oal_uint8                     *puc_payload;

    uc_datatype = mac_get_data_type(pst_netbuff);

    if(MAC_DATA_EAPOL != uc_datatype)
    {
        return 0;
    }

    puc_payload = oal_netbuf_payload(pst_netbuff);
    if(OAL_PTR_NULL == puc_payload)
    {
        return 0;
    }


    return *(oal_uint16 *)(puc_payload + OAL_EAPOL_INFO_POS);

}


oal_uint8 mac_get_eapol_type(oal_netbuf_stru *pst_netbuff)
{
    oal_uint8                      uc_datatype = MAC_DATA_BUTT;
    oal_uint8                     *puc_payload;

    uc_datatype = mac_get_data_type(pst_netbuff);

    if(MAC_DATA_EAPOL != uc_datatype)
    {
        return 0;
    }

    puc_payload = oal_netbuf_payload(pst_netbuff);
    if(OAL_PTR_NULL == puc_payload)
    {
        return 0;
    }


    return *(puc_payload + OAL_EAPOL_TYPE_POS);

}



oal_bool_enum_uint8 mac_is_eapol_key_ptk(mac_eapol_header_stru  *pst_eapol_header)
{
    mac_eapol_key_stru *pst_key;

    if (IEEE802_1X_TYPE_EAPOL_KEY == pst_eapol_header->uc_type)
    {
        if ((oal_uint16)(OAL_NET2HOST_SHORT(pst_eapol_header->us_length)) >= (oal_uint16)OAL_SIZEOF(mac_eapol_key_stru))
        {
            pst_key = (mac_eapol_key_stru *)(pst_eapol_header + 1);

            if (pst_key->auc_key_info[1] & WPA_KEY_INFO_KEY_TYPE)
            {
                return OAL_TRUE;
            }
        }
    }
    return OAL_FALSE;
}

/*lint -e19*/
oal_module_symbol(mac_is_dhcp_port);
oal_module_symbol(mac_is_dhcp6);
oal_module_symbol(mac_is_nd);
oal_module_symbol(mac_get_data_type_from_8023);
oal_module_symbol(mac_is_eapol_key_ptk);
oal_module_symbol(mac_get_data_type_from_80211);
oal_module_symbol(mac_get_data_type);



/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


